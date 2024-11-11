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
**  File Name : Rte.c                                                         **
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
/*                              File Inclusions                               */
/******************************************************************************/
#define RTE_ALLOW_CROSS_HEADER_INCLUSION
#include "Com.h"
#include "ComXf.h"
#include "E2EXf.h"
#include "Rte_App_Lin_LIN1.h"
#include "Rte_BswM_Partition_Main.h"
#include "Rte_CDD_LIN.h"
#include "Rte_ComM.h"
#include "Rte_Csm.h"
#include "Rte_DET.h"
#include "Rte_Dcm.h"
#include "Rte_Dem.h"
#include "Rte_EcuM.h"
#include "Rte_FiM.h"
#include "Rte_Fota.h"
#include "Rte_IoHwAb.h"
#include "Rte_KeyM.h"
#include "Rte_NvM.h"
#include "Rte_Os_Master.h"
#include "Rte_SWC_AppMode.h"
#include "Rte_SWC_DiagnosticMonitor.h"
#include "Rte_SWC_DiagnosticService.h"
#include "Rte_SWC_E2EXf.h"
#include "Rte_SWC_WdgMTest.h"
#include "Rte_StbM.h"
#include "Rte_WdgM.h"
#include "SchM_Adc.h"
#include "SchM_BswM.h"
#include "SchM_CanCM.h"
#include "SchM_CanIf.h"
#include "SchM_CanNm.h"
#include "SchM_CanSM.h"
#include "SchM_CanTp.h"
#include "SchM_CanTrcv.h"
#include "SchM_Can_43_FLEXCAN.h"
#include "SchM_Com.h"
#include "SchM_ComM.h"
#include "SchM_Crypto.h"
#include "SchM_Crypto_76_HaeModule.h"
#include "SchM_Csm.h"
#include "SchM_Dcm.h"
#include "SchM_Dem.h"
#include "SchM_Det.h"
#include "SchM_Dio.h"
#include "SchM_EcuM.h"
#include "SchM_Fee.h"
#include "SchM_FiM.h"
#include "SchM_Fls.h"
#include "SchM_Fota.h"
#include "SchM_Gpt.h"
#include "SchM_Icu.h"
#include "SchM_IoHwAb.h"
#include "SchM_IpduM.h"
#include "SchM_KeyM.h"
#include "SchM_LinIf.h"
#include "SchM_LinSM.h"
#include "SchM_LinTrcv.h"
#include "SchM_Lin_43_LPUART_FLEXIO.h"
#include "SchM_Mcl.h"
#include "SchM_Mcu.h"
#include "SchM_Nm.h"
#include "SchM_NvM.h"
#include "SchM_PduR.h"
#include "SchM_Port.h"
#include "SchM_Pwm.h"
#include "SchM_Spi.h"
#include "SchM_StbM.h"
#include "SchM_WdgM.h"
#include "SchM_Wdg_43_Instance0.h"
#include "SchM_Wdg_76_Acw_76_Acw.h"
#include "Rte_Hook.h"
#include "Rte_Main.h"
#include "Rte_Cbk.h"
#include "Rte_Internal.h"
#include "Rte_User.h"
#include "Rte_Static.h"

/******************************************************************************/
/*                          Initialization of Macros                          */
/******************************************************************************/
#define RTE_START_SET_SR_FLAGS_DEFAULTPARTITION

/******************************************************************************/
/*                         RTE Global Variables START                         */
/******************************************************************************/

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32= {RTE_MODE_MDG_PduGroup_STOP, RTE_MODE_MDG_PduGroup_STOP, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmApplicationUpdated, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated= {RTE_MODE_DcmApplicationUpdated_APP_NOT_UPDATED, RTE_MODE_DcmApplicationUpdated_APP_NOT_UPDATED, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmSecurityAccess, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess= {RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED, RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmModeRapidPowerShutDown, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown= {RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN, RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_VAR_CLEARED_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gdt_MSQ_c5d478a01163f838[RTE_MAXQSIZE_c5d478a01163f838];
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32= {RTE_MODE_MDG_PduGroup_STOP, RTE_MODE_MDG_PduGroup_STOP, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_VAR_CLEARED_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gdt_WriteCntr_c5d478a01163f838;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_VAR_CLEARED_ASIL_D_32
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gu8_InitFlag[4];
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_MSFlagType, RTE_DATA) Rte_Gst_MSFlags_Tx_WdgM_globalMode_currentMode;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_MSFlagType, RTE_DATA) Rte_Gst_MSFlags_Rx_WdgM_globalMode_currentMode;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32= Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier= {RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED, RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gu8_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1= Rte_InitValue_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_VAR_CLEARED_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gdt_ReadCntr_c5d478a01163f838;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_VAR_CLEARED_ASIL_D_32
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_KeyM_BswSE_KeyM_MainFunction_DisablingFlagType, RTE_DATA) Rte_Gun_BitVector_KeyM_BswSE_KeyM_MainFunction;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1= {RTE_MODE_MDG_CanSMBORState_initmode, RTE_MODE_MDG_CanSMBORState_initmode, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmResponseOnEvent_OnDTCStatusChange, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange= {RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED, RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2= Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_KeyM_BswSE_KeyM_MainBackgroundFunction_DisablingFlagType, RTE_DATA) Rte_Gun_BitVector_KeyM_BswSE_KeyM_MainBackgroundFunction;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmDiagnosticSessionControl, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl= {RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION, RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_InitState_InitState, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState= {RTE_MODE_MDG_InitState_START, RTE_MODE_MDG_InitState_START, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1= {RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM, RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2= {RTE_MODE_MDG_ComMMode_NO_COM, RTE_MODE_MDG_ComMMode_NO_COM, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gu8_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2= Rte_InitValue_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_CanCM_BswSE_CanCM_MainFunction_DisablingFlagType, RTE_DATA) Rte_Gun_BitVector_CanCM_BswSE_CanCM_MainFunction;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_EcuM_currentMode_currentMode, RTE_DATA) Rte_Gst_ActiveMode_EcuM_currentMode_currentMode= {RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE, RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32= {RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION, RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmControlDTCSetting, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting= {RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING, RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_SWC_AppMode_AppMode_Test_DisablingFlagType, RTE_DATA) Rte_Gun_BitVector_SWC_AppMode_AppMode_Test;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_modeSwitchPort_CurrentMode, RTE_DATA) Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode= {RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE, RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_WdgM_mode_SE_Init_currentMode, RTE_DATA) Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode= {RTE_MODE_WdgM_Mode_SUPERVISION_OK, RTE_MODE_WdgM_Mode_SUPERVISION_OK, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"
static VAR(uint8, RTE_DATA) Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1= Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_VAR_INIT_ASIL_D_8
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_WdgM_globalMode_currentMode, RTE_DATA) Rte_Gst_ActiveMode_WdgM_globalMode_currentMode= {RTE_MODE_WdgM_Mode_SUPERVISION_OK, RTE_MODE_WdgM_Mode_SUPERVISION_OK, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_WdgM_BswSE_WdgM_MainFunction_DisablingFlagType, RTE_DATA) Rte_Gun_BitVector_WdgM_BswSE_WdgM_MainFunction;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_Dcm_DcmEcuReset, RTE_DATA) Rte_Gst_ActiveMode_Dcm_DcmEcuReset= {RTE_MODE_DcmEcuReset_DCM_NONE, RTE_MODE_DcmEcuReset_DCM_NONE, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_Csm_BswSE_Csm_MainFunction_DisablingFlagType, RTE_DATA) Rte_Gun_BitVector_Csm_BswSE_Csm_MainFunction;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent= {RTE_MODE_MDG_WakeupEvent_INITIAL_MODE, RTE_MODE_MDG_WakeupEvent_INITIAL_MODE, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1, RTE_DATA) Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1= {RTE_MODE_MDG_ComMMode_NO_COM, RTE_MODE_MDG_ComMMode_NO_COM, 0, RTE_FALSE};
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Fota_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_Fota_EventFlagType, RTE_DATA) Rte_Fota_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Fota_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_EcuM_EventFlagType, RTE_DATA) Rte_EcuM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_KeyM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_KeyM_EventFlagType, RTE_DATA) Rte_KeyM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_KeyM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_NvM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_NvM_EventFlagType, RTE_DATA) Rte_NvM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_NvM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_SWC_DiagnosticService_EventFlagType, RTE_DATA) Rte_SWC_DiagnosticService_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_BswM_Partition_Main_EventFlagType, RTE_DATA) Rte_BswM_Partition_Main_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_SWC_WdgMTest_EventFlagType, RTE_DATA) Rte_SWC_WdgMTest_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_IoHwAb_EventFlagType, RTE_DATA) Rte_IoHwAb_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_StbM_EventFlagType, RTE_DATA) Rte_StbM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_WdgM_EventFlagType, RTE_DATA) Rte_WdgM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Csm_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_Csm_EventFlagType, RTE_DATA) Rte_Csm_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Csm_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_App_Lin_LIN1_EventFlagType, RTE_DATA) Rte_App_Lin_LIN1_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_E2EXf_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_SWC_E2EXf_EventFlagType, RTE_DATA) Rte_SWC_E2EXf_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_E2EXf_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_CDD_LIN_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_CDD_LIN_EventFlagType, RTE_DATA) Rte_CDD_LIN_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_CDD_LIN_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_Dem_EventFlagType, RTE_DATA) Rte_Dem_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_SWC_DiagnosticMonitor_EventFlagType, RTE_DATA) Rte_SWC_DiagnosticMonitor_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_FiM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_FiM_EventFlagType, RTE_DATA) Rte_FiM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_FiM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_SWC_AppMode_EventFlagType, RTE_DATA) Rte_SWC_AppMode_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_Dcm_EventFlagType, RTE_DATA) Rte_Dcm_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Os_Master_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_Os_Master_EventFlagType, RTE_DATA) Rte_Os_Master_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Os_Master_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_DET_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_DET_EventFlagType, RTE_DATA) Rte_DET_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_DET_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(Rte_ComM_EventFlagType, RTE_DATA) Rte_ComM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_CanIf_EventFlagType, RTE_DATA) SchM_Default_CanIf_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_LinSM_EventFlagType, RTE_DATA) SchM_Default_LinSM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Lin_43_LPUART_FLEXIO_EventFlagType, RTE_DATA) SchM_Default_Lin_43_LPUART_FLEXIO_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_CanTrcv_EventFlagType, RTE_DATA) SchM_Default_CanTrcv_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Icu_EventFlagType, RTE_DATA) SchM_Default_Icu_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Det_EventFlagType, RTE_DATA) SchM_Default_Det_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_ComM_EventFlagType, RTE_DATA) SchM_Default_ComM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Wdg_43_Instance0_EventFlagType, RTE_DATA) SchM_Default_Wdg_43_Instance0_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Crypto_76_HaeModule_EventFlagType, RTE_DATA) SchM_Default_Crypto_76_HaeModule_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Dio_EventFlagType, RTE_DATA) SchM_Default_Dio_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_IoHwAb_EventFlagType, RTE_DATA) SchM_Default_IoHwAb_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_EcuM_EventFlagType, RTE_DATA) SchM_Default_EcuM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Gpt_EventFlagType, RTE_DATA) SchM_Default_Gpt_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Mcu_EventFlagType, RTE_DATA) SchM_Default_Mcu_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_KeyM_EventFlagType, RTE_DATA) SchM_Default_KeyM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_BswM_EventFlagType, RTE_DATA) SchM_Default_BswM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Com_EventFlagType, RTE_DATA) SchM_Default_Com_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_StbM_EventFlagType, RTE_DATA) SchM_Default_StbM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_WdgM_EventFlagType, RTE_DATA) SchM_Default_WdgM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_CanNm_EventFlagType, RTE_DATA) SchM_Default_CanNm_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_CanTp_EventFlagType, RTE_DATA) SchM_Default_CanTp_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Can_43_FLEXCAN_EventFlagType, RTE_DATA) SchM_Default_Can_43_FLEXCAN_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Port_EventFlagType, RTE_DATA) SchM_Default_Port_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Fee_EventFlagType, RTE_DATA) SchM_Default_Fee_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_LinTrcv_EventFlagType, RTE_DATA) SchM_Default_LinTrcv_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Mcl_EventFlagType, RTE_DATA) SchM_Default_Mcl_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Wdg_76_Acw_76_Acw_EventFlagType, RTE_DATA) SchM_Default_Wdg_76_Acw_76_Acw_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_NvM_EventFlagType, RTE_DATA) SchM_Default_NvM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_FiM_EventFlagType, RTE_DATA) SchM_Default_FiM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_CanCM_EventFlagType, RTE_DATA) SchM_Default_CanCM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Dem_EventFlagType, RTE_DATA) SchM_Default_Dem_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Spi_EventFlagType, RTE_DATA) SchM_Default_Spi_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Adc_EventFlagType, RTE_DATA) SchM_Default_Adc_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Crypto_EventFlagType, RTE_DATA) SchM_Default_Crypto_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_CanSM_EventFlagType, RTE_DATA) SchM_Default_CanSM_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_PduR_EventFlagType, RTE_DATA) SchM_Default_PduR_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Dcm_EventFlagType, RTE_DATA) SchM_Default_Dcm_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_LinIf_EventFlagType, RTE_DATA) SchM_Default_LinIf_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Csm_EventFlagType, RTE_DATA) SchM_Default_Csm_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Fls_EventFlagType, RTE_DATA) SchM_Default_Fls_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
static VAR(SchM_Pwm_EventFlagType, RTE_DATA) SchM_Default_Pwm_Gdt_EventFlagType;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_CLEARED_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_FD_CAN1_BswTE_ComM_MainFunction_ComMChannel_FD_CAN1 = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_Dcm_MainFunction_BswTE_Dcm_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_LinSM_MainFunction_BswTE_LinSM_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_StbM_MainFunction_BswTE_StbM_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN1_BswTE_ComM_MainFunction_ComMChannel_LIN1 = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN2_BswTE_ComM_MainFunction_ComMChannel_LIN2 = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN1_BswTE_LinIf_MainFunction_LinIfChannel_LIN1 = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN2_BswTE_LinIf_MainFunction_LinIfChannel_LIN2 = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_CanSM_MainFunction_BswTE_CanSM_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_CanTrcv_MainFunction_BswTE_CanTrcv_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_CanTp_MainFunction_BswTE_CanTp_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_Com_MainFunctionRx_BswTE_Com_MainFunctionRx = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_Com_MainFunctionTx_BswTE_Com_MainFunctionTx = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_CanCM_MainFunction_BswTE_CanCM_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
static VAR(uint32, RTE_DATA) Rte_Gu32Counter_BswSE_CanNm_MainFunction_BswSE_CanNm_MainFunction = 0;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_VAR_INIT_ASIL_D_32
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:8.9 [Justified:Low] "all counters are declared as global variables to belong in SPECIFIC memory block" */

/******************************************************************************/
/*                         RTE Global Variables STOP                          */
/******************************************************************************/

/* polyspace-begin MISRA-C3:5.8 [Justified:Low] "Rte is using 'Data' as common name for input parameter in almost functions" */
/******************************************************************************/
/*                      Generated RTE Internal Functions                      */
/******************************************************************************/
/* Internal API to check whether RTE on the calling core is running or not */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(boolean, RTE_CODE) Rte_CheckInitFlag(uint8 FunctionType)
{
  return(Rte_Gu8_InitFlag[FunctionType]);
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin MISRA-C3:5.2 [Justified:Low] "Many Rte factors (variables, functions) have same prefix-name" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_ONE(CONST(boolean, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  Rte_Gun_BitVector_SWC_AppMode_AppMode_Test.bl_B.EcuM_currentMode_EcuMode_ECUM_STATE_STARTUP_ONE = Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:5.2 [Justified:Low] "Many Rte factors (variables, functions) have same prefix-name" */

/* polyspace-begin MISRA-C3:5.2 [Justified:Low] "Many Rte factors (variables, functions) have same prefix-name" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_THREE(CONST(boolean, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  Rte_Gun_BitVector_SWC_AppMode_AppMode_Test.bl_B.EcuM_currentMode_EcuMode_ECUM_STATE_STARTUP_THREE = Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:5.2 [Justified:Low] "Many Rte factors (variables, functions) have same prefix-name" */

/* polyspace-begin MISRA-C3:5.2 [Justified:Low] "Many Rte factors (variables, functions) have same prefix-name" */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_TWO(CONST(boolean, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  Rte_Gun_BitVector_SWC_AppMode_AppMode_Test.bl_B.EcuM_currentMode_EcuMode_ECUM_STATE_STARTUP_TWO = Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end MISRA-C3:5.2 [Justified:Low] "Many Rte factors (variables, functions) have same prefix-name" */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) Rte_ModeMachineInitialization(void)
{
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_requestedMode = RTE_MODE_MDG_CanSMBORState_initmode;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode = RTE_MODE_MDG_CanSMBORState_initmode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_requestedMode = RTE_MODE_MDG_ComMMode_NO_COM;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode = RTE_MODE_MDG_ComMMode_NO_COM;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_requestedMode = RTE_MODE_MDG_ComMMode_NO_COM;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode = RTE_MODE_MDG_ComMMode_NO_COM;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_requestedMode = RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode = RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_requestedMode = RTE_MODE_MDG_InitState_START;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode = RTE_MODE_MDG_InitState_START;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_requestedMode = RTE_MODE_MDG_PduGroup_STOP;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode = RTE_MODE_MDG_PduGroup_STOP;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_requestedMode = RTE_MODE_MDG_PduGroup_STOP;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode = RTE_MODE_MDG_PduGroup_STOP;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_requestedMode = RTE_MODE_MDG_WakeupEvent_INITIAL_MODE;
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode = RTE_MODE_MDG_WakeupEvent_INITIAL_MODE;

  Rte_Gst_ActiveMode_WdgM_globalMode_currentMode.dt_requestedMode = RTE_MODE_WdgM_Mode_SUPERVISION_OK;
  Rte_Gst_ActiveMode_WdgM_globalMode_currentMode.dt_currentMode = RTE_MODE_WdgM_Mode_SUPERVISION_OK;

  Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.dt_requestedMode = RTE_MODE_WdgM_Mode_SUPERVISION_OK;
  Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.dt_currentMode = RTE_MODE_WdgM_Mode_SUPERVISION_OK;

  Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode = RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE;
  Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode = RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE;

  /* @RUNNABLES: Invoke runnables for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Start();

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  AppMode_ComMModeSwitched_LIN1();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Return();

  /* @RUNNABLES: Invoke runnables for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Start();

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  AppMode_ComMModeSwitched_LIN2();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Return();

  /* @RUNNABLES: Invoke runnables for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Start();

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  AppMode_ComMModeSwitched_FD_CAN1_PNC32();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Return();

  /* @RUNNABLES: Invoke runnables for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx_Start();

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx_Return();

  /* @RUNNABLES: Invoke runnables for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx_Start();

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx_Return();

  /* @RUNNABLES: Invoke runnables for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_WdgMTest_RE_WdgMTestGlobalMode_Start();

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  RE_WdgMTestGlobalMode();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Runnable_SWC_WdgMTest_RE_WdgMTestGlobalMode_Return();

  Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_ONE(1);
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) SchM_MgrToggleModeDisabling_modeNotificationPort_CsmEcuShutdown_ECUM_STATE_SHUTDOWN(CONST(boolean, RTE_APPL_CONST) Data)
{
  Rte_Gun_BitVector_Csm_BswSE_Csm_MainFunction.bl_B.EcuMode_ECUM_STATE_SHUTDOWN = Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) SchM_MgrToggleModeDisabling_modeNotificationPort_EcuMode_ECUM_STATE_SHUTDOWN(CONST(boolean, RTE_APPL_CONST) Data)
{
  Rte_Gun_BitVector_WdgM_BswSE_WdgM_MainFunction.bl_B.EcuMode_ECUM_STATE_SHUTDOWN = Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) SchM_MgrToggleModeDisabling_modeNotificationPort_KeyMEcuShutdown_ECUM_STATE_SHUTDOWN(CONST(boolean, RTE_APPL_CONST) Data)
{
  Rte_Gun_BitVector_KeyM_BswSE_KeyM_MainBackgroundFunction.bl_B.EcuMode_ECUM_STATE_SHUTDOWN = Data;
  Rte_Gun_BitVector_KeyM_BswSE_KeyM_MainFunction.bl_B.EcuMode_ECUM_STATE_SHUTDOWN = Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(void, RTE_CODE) SchM_ModeMachineInitialization(void)
{
  Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.dt_requestedMode = RTE_MODE_DcmApplicationUpdated_APP_NOT_UPDATED;
  Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.dt_currentMode = RTE_MODE_DcmApplicationUpdated_APP_NOT_UPDATED;

  Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_requestedMode = RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM;
  Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode = RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM;

  Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_requestedMode = RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING;
  Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode = RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING;

  Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_requestedMode = RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION;
  Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode = RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION;

  Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_requestedMode = RTE_MODE_DcmEcuReset_DCM_NONE;
  Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode = RTE_MODE_DcmEcuReset_DCM_NONE;

  Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_requestedMode = RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN;
  Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode = RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN;

  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.dt_requestedMode = RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED;
  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.dt_currentMode = RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED;

  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.dt_requestedMode = RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED;
  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.dt_currentMode = RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED;

  Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.dt_requestedMode = RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED;
  Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.dt_currentMode = RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED;

  Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode = RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE;
  Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode = RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE;

  /* @MODULEENTITIES: Invoke schedulable entities for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

  BswM_Immediate_DcmCommunicationControl_FD_CAN1();
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

  /* @MODULEENTITIES: Invoke schedulable entities for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmControlDTCSetting_Start();

  BswM_Immediate_DcmControlDTCSetting();
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmControlDTCSetting_Return();

  /* @MODULEENTITIES: Invoke schedulable entities for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

  BswM_Immediate_DcmDiagnosticSessionControl();
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

  /* @MODULEENTITIES: Invoke schedulable entities for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

  BswM_Immediate_DcmEcuReset();
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

  /* @MODULEENTITIES: Invoke schedulable entities for Initial Mode */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmModeRapidPowerShutDown_Start();

  BswM_Immediate_DcmModeRapidPowerShutDown();
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_Schedulable_BswM_Immediate_DcmModeRapidPowerShutDown_Return();

}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                        Generated RTE and SchM APIs                         */
/******************************************************************************/

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(EcuM_StateType, RTE_CODE) SchM_Mode_Csm_modeNotificationPort_CsmEcuShutdown(P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(EcuM_StateType, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Csm_modeNotificationPort_CsmEcuShutdown_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Csm_modeNotificationPort_CsmEcuShutdown_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_BswM_modeNotificationPort_DcmEcuReset(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmEcuReset_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmEcuReset;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmEcuReset.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmEcuReset;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmEcuReset_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(EcuM_StateType, RTE_CODE) SchM_Mode_WdgM_modeNotificationPort_EcuMode(P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(EcuM_StateType, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_WdgM_modeNotificationPort_EcuMode_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_WdgM_modeNotificationPort_EcuMode_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmResponseOnEvent_OnDTCStatusChange(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmResponseOnEvent_OnDTCStatusChange(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmResponseOnEvent_OnDTCStatusChange_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED:
      case RTE_MODE_DcmResponseOnEvent_DCM_EVENT_STARTED:
      case RTE_MODE_DcmResponseOnEvent_DCM_EVENT_STOPPED:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmResponseOnEvent_OnDTCStatusChange */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmResponseOnEvent_OnDTCStatusChange(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmResponseOnEvent_OnDTCStatusChange_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmResponseOnEvent_OnDTCStatusChange(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmResponseOnEvent_OnDTCStatusChange_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmResponseOnEvent;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmResponseOnEvent;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnDTCStatusChange.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmResponseOnEvent_OnDTCStatusChange_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_BswM_modeNotificationPort_DcmControlDTCSetting(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmControlDTCSetting_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmControlDTCSetting;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmControlDTCSetting;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmControlDTCSetting_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(EcuM_StateType, RTE_CODE) SchM_Mode_CanCM_CanCM_EM_R(void)
{
  VAR(EcuM_StateType, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_CanCM_CanCM_EM_R_Start();
  /* @UNCONNECTED:Return INITIAL Mode*/

  Ldt_Data = RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE;
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_CanCM_CanCM_EM_R_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmDiagnosticSessionControl(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @ONENTRY: Invoke all ONENTRY Module Entitites */
  switch(Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_requestedMode)
  {
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    case RTE_MODE_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Start();

      BswM_Immediate_DcmDiagnosticSessionControl();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmDiagnosticSessionControl_Return();

      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmDiagnosticSessionControl(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmDiagnosticSessionControl_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION:
      case RTE_MODE_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmDiagnosticSessionControl */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmDiagnosticSessionControl(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmDiagnosticSessionControl_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmDiagnosticSessionControl(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmDiagnosticSessionControl_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmDiagnosticSessionControl;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmDiagnosticSessionControl;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmDiagnosticSessionControl_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmEcuReset(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmEcuReset.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @ONENTRY: Invoke all ONENTRY Module Entitites */
  switch(Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_requestedMode)
  {
    case RTE_MODE_DcmEcuReset_DCM_JUMPTOSYSSUPPLIERBOOTLOADER:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    case RTE_MODE_DcmEcuReset_DCM_NONE:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    case RTE_MODE_DcmEcuReset_DCM_SOFT:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    case RTE_MODE_DcmEcuReset_DCM_HARD:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    case RTE_MODE_DcmEcuReset_DCM_EXECUTE:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    case RTE_MODE_DcmEcuReset_DCM_KEYONOFF:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    case RTE_MODE_DcmEcuReset_DCM_JUMPTOBOOTLOADER:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Start();

      BswM_Immediate_DcmEcuReset();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmEcuReset_Return();

      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmEcuReset.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmEcuReset(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmEcuReset_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmEcuReset_DCM_EXECUTE:
      case RTE_MODE_DcmEcuReset_DCM_HARD:
      case RTE_MODE_DcmEcuReset_DCM_JUMPTOBOOTLOADER:
      case RTE_MODE_DcmEcuReset_DCM_JUMPTOSYSSUPPLIERBOOTLOADER:
      case RTE_MODE_DcmEcuReset_DCM_KEYONOFF:
      case RTE_MODE_DcmEcuReset_DCM_NONE:
      case RTE_MODE_DcmEcuReset_DCM_SOFT:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmEcuReset */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmEcuReset(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmEcuReset_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmEcuReset(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmEcuReset_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmEcuReset;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmEcuReset.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmEcuReset;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmEcuReset.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmEcuReset_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @ONENTRY: Invoke all ONENTRY Module Entitites */
  switch(Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_requestedMode)
  {
    case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Start();

      BswM_Immediate_DcmCommunicationControl_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmCommunicationControl_FD_CAN1_Return();

      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM:
      case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL:
      case RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM:
      case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM:
      case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM:
      case RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1 */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmCommunicationControl;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmCommunicationControl;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_BswM_modeNotificationPort_DcmDiagnosticSessionControl(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmDiagnosticSessionControl_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmDiagnosticSessionControl;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmDiagnosticSessionControl;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmDiagnosticSessionControl.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmDiagnosticSessionControl_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_BswM_modeSwitchPort_CurrentMode(CONST(EcuM_StateType, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

    /* @ACTIVATE MODE DISABLINGS: Invoke SchM_ToggleModeDisabling for all module entities having disabling dependency */
    switch(Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode)
    {
      case RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN:
      {

        SchM_MgrToggleModeDisabling_modeNotificationPort_CsmEcuShutdown_ECUM_STATE_SHUTDOWN(1);

        SchM_MgrToggleModeDisabling_modeNotificationPort_EcuMode_ECUM_STATE_SHUTDOWN(1);

        SchM_MgrToggleModeDisabling_modeNotificationPort_KeyMEcuShutdown_ECUM_STATE_SHUTDOWN(1);
        break;
      }

      default:
      {
        break;
      }
    }
  if(Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode != Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode)
  {
    /* @DEACTIVATE MODE DISABLINGS: Invoke SchM_ToggleModeDisabling for all module entities having disabling dependency */
    switch(Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode)
    {
      case RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN:
      {

        SchM_MgrToggleModeDisabling_modeNotificationPort_CsmEcuShutdown_ECUM_STATE_SHUTDOWN(0);

        SchM_MgrToggleModeDisabling_modeNotificationPort_EcuMode_ECUM_STATE_SHUTDOWN(0);

        SchM_MgrToggleModeDisabling_modeNotificationPort_KeyMEcuShutdown_ECUM_STATE_SHUTDOWN(0);
        break;
      }

      default:
      {
        break;
      }
    }
  }
  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_BswM_modeSwitchPort_CurrentMode(CONST(EcuM_StateType, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_BswM_modeSwitchPort_CurrentMode_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE:
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_TWO:
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_THREE:
      case RTE_MODE_EcuMode_ECUM_STATE_RUN:
      case RTE_MODE_EcuMode_ECUM_STATE_APP_RUN:
      case RTE_MODE_EcuMode_ECUM_STATE_APP_POST_RUN:
      case RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN:
      case RTE_MODE_EcuMode_ECUM_STATE_PREP_SHUTDOWN:
      case RTE_MODE_EcuMode_ECUM_STATE_SLEEP:
      case RTE_MODE_EcuMode_ECUM_STATE_OFF:
      case RTE_MODE_EcuMode_ECUM_STATE_RESET:
      {
        /* @INVOKE: SchM_ModeMachine_BswM_modeSwitchPort_CurrentMode */
        Lu16_ReturnStatus = SchM_ModeMachine_BswM_modeSwitchPort_CurrentMode(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_BswM_modeSwitchPort_CurrentMode_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(EcuM_StateType, RTE_CODE) SchM_Mode_KeyM_modeNotificationPort_KeyMEcuShutdown(P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(EcuM_StateType, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_KeyM_modeNotificationPort_KeyMEcuShutdown_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_modeSwitchPort_CurrentMode.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_KeyM_modeNotificationPort_KeyMEcuShutdown_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmModeRapidPowerShutDown(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmModeRapidPowerShutDown_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmModeRapidPowerShutDown;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmModeRapidPowerShutDown;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmModeRapidPowerShutDown_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmModeRapidPowerShutDown(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @ONENTRY: Invoke all ONENTRY Module Entitites */
  switch(Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_requestedMode)
  {
    case RTE_MODE_DcmModeRapidPowerShutDown_DCM_DISABLE_RAPIDPOWERSHUTDOWN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmModeRapidPowerShutDown_Start();

      BswM_Immediate_DcmModeRapidPowerShutDown();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmModeRapidPowerShutDown_Return();

      break;
    }
    case RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmModeRapidPowerShutDown_Start();

      BswM_Immediate_DcmModeRapidPowerShutDown();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmModeRapidPowerShutDown_Return();

      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmModeRapidPowerShutDown(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmModeRapidPowerShutDown_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmModeRapidPowerShutDown_DCM_DISABLE_RAPIDPOWERSHUTDOWN:
      case RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmModeRapidPowerShutDown */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmModeRapidPowerShutDown(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmModeRapidPowerShutDown_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_BswM_modeNotificationPort_DcmModeRapidPowerShutDown(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmModeRapidPowerShutDown_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmModeRapidPowerShutDown;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmModeRapidPowerShutDown;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmModeRapidPowerShutDown.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmModeRapidPowerShutDown_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmApplicationUpdated(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmApplicationUpdated_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmApplicationUpdated;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmApplicationUpdated;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmApplicationUpdated_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmApplicationUpdated(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmApplicationUpdated.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmApplicationUpdated(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmApplicationUpdated_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmApplicationUpdated_APP_NOT_UPDATED:
      case RTE_MODE_DcmApplicationUpdated_APP_UPDATED:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmApplicationUpdated */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmApplicationUpdated(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmApplicationUpdated_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmControlDTCSetting(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmControlDTCSetting_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmControlDTCSetting;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmControlDTCSetting;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmControlDTCSetting_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmControlDTCSetting(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @ONENTRY: Invoke all ONENTRY Module Entitites */
  switch(Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_requestedMode)
  {
    case RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmControlDTCSetting_Start();

      BswM_Immediate_DcmControlDTCSetting();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmControlDTCSetting_Return();

      break;
    }
    case RTE_MODE_DcmControlDTCSetting_DCM_DISABLEDTCSETTING:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmControlDTCSetting_Start();

      BswM_Immediate_DcmControlDTCSetting();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_BswM_Immediate_DcmControlDTCSetting_Return();

      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmControlDTCSetting.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmControlDTCSetting(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmControlDTCSetting_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmControlDTCSetting_DCM_DISABLEDTCSETTING:
      case RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmControlDTCSetting */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmControlDTCSetting(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmControlDTCSetting_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_BswM_modeNotificationPort_DcmCommunicationControl_FD_CAN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmCommunicationControl_FD_CAN1_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmCommunicationControl;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmCommunicationControl;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_BswM_modeNotificationPort_DcmCommunicationControl_FD_CAN1_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmResponseOnEvent;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmResponseOnEvent;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmResponseOnEvent_DCM_EVENT_CLEARED:
      case RTE_MODE_DcmResponseOnEvent_DCM_EVENT_STARTED:
      case RTE_MODE_DcmResponseOnEvent_DCM_EVENT_STOPPED:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) SchM_Mode_Dcm_DcmSecurityAccess(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmSecurityAccess_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    Ldt_Data = RTE_TRANSITION_DcmSecurityAccess;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_DcmSecurityAccess;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.dt_currentMode;
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_ModeHook_Dcm_DcmSecurityAccess_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) SchM_ModeMachine_Dcm_DcmSecurityAccess(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK*/
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.dt_requestedMode = Data;

  Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.bl_isInTransition = RTE_TRUE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.dt_currentMode = Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.dt_requestedMode;

  Rte_Gst_ActiveMode_Dcm_DcmSecurityAccess.bl_isInTransition = RTE_FALSE;
  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) SchM_Switch_Dcm_DcmSecurityAccess(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with SCHM_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)SCHM_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmSecurityAccess_Start(Data);
  /* @INVALID API INVOCATION : If RTE_SCHM_INIT flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_SCHM_INIT))
  {
    /* @RETURN: Return SCHM_E_UNINIT */
    Lu16_ReturnStatus = SCHM_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_L9:
      case RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED:
      {
        /* @INVOKE: SchM_ModeMachine_Dcm_DcmSecurityAccess */
        Lu16_ReturnStatus = SchM_ModeMachine_Dcm_DcmSecurityAccess(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return SCHM_E_INVALID */
        Lu16_ReturnStatus = (uint16)SCHM_E_INVALID;

        break;
      }
    }

  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_SwitchHook_Dcm_DcmSecurityAccess_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA(void)
{
  (void) SuspendAllInterrupts();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA(void)
{
  (void) ResumeAllInterrupts();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Enter_LinSM_CHANNEL_STATUS_PROTECTION_0(void)
{
  (void) SuspendAllInterrupts();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Exit_LinSM_CHANNEL_STATUS_PROTECTION_0(void)
{
  (void) ResumeAllInterrupts();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Enter_LinSM_CHANNEL_STATUS_PROTECTION_1(void)
{
  (void) SuspendAllInterrupts();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Exit_LinSM_CHANNEL_STATUS_PROTECTION_1(void)
{
  (void) ResumeAllInterrupts();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_StartTiming(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_StartTimingHook_Start();

    Rte_Gu8_InitFlag[RTE_SCHM_STARTTIMING] = RTE_SET;

    /* Activate Task OsTask_BSW_BG_KeyM_Main: Extended Task */
    SCHMSTARTAPI_M_OSActivateTask(OsTask_BSW_BG_KeyM_Main);

    /* Activate Task OsTask_BSW_BG_Fota: Extended Task */
    SCHMSTARTAPI_M_OSActivateTask(OsTask_BSW_BG_Fota);

    /* Activate Task OsTask_BSW_BG_Crypto_Main: Extended Task */
    SCHMSTARTAPI_M_OSActivateTask(OsTask_BSW_BG_Crypto_Main);

    /* Set Alarm OsAlarm_BSW_10ms */
    SCHMSTARTAPI_M_OSSetRelAlarm(OsAlarm_BSW_10ms, 4U, 8U);

    /* Set Alarm OsAlarm_BG_Fota */
    SCHMSTARTAPI_M_OSSetRelAlarm(OsAlarm_BG_Fota, 1U, 4U);

    /* Set Alarm OsAlarm_BSW_BG_Crypto_Main */
    SCHMSTARTAPI_M_OSSetRelAlarm(OsAlarm_BSW_BG_Crypto_Main, 1U, 80U);

    /* Set Alarm OsAlarm_BSW_5ms_Com */
    SCHMSTARTAPI_M_OSSetRelAlarm(OsAlarm_BSW_5ms_Com, 2U, 4U);

    /* Set Alarm OsAlarm_BSW_BG_KeyM_Main */
    SCHMSTARTAPI_M_OSSetRelAlarm(OsAlarm_BSW_BG_KeyM_Main, 1U, 80U);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_StartTimingHook_Return();

}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Init(P2CONST(SchM_ConfigType,AUTOMATIC,RTE_CONST) ConfigPtr)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_InitHook_Start();

  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(ConfigPtr);
  Rte_Gu8_InitFlag[RTE_SCHM_INIT] = RTE_SET;

  (void)SchM_ModeMachineInitialization();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_InitHook_Return();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Start(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_StartHook_Start();

  Rte_Gu8_InitFlag[RTE_SCHM_START] = RTE_SET;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_StartHook_Return();

}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) SchM_Deinit(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_DeinitHook_Start();

  Rte_Gu8_InitFlag[RTE_SCHM_STARTTIMING] = RTE_CLEAR;
  Rte_Gu8_InitFlag[RTE_SCHM_START] = RTE_CLEAR;
  Rte_Gu8_InitFlag[RTE_SCHM_INIT] = RTE_CLEAR;

  /* Cancel Alarm OsAlarm_BG_Fota */
  SCHMDEINITAPI_M_OSCancelAlarm(OsAlarm_BG_Fota);

  /* Cancel Alarm OsAlarm_BSW_BG_KeyM_Main */
  SCHMDEINITAPI_M_OSCancelAlarm(OsAlarm_BSW_BG_KeyM_Main);

  /* Cancel Alarm OsAlarm_BSW_BG_Crypto_Main */
  SCHMDEINITAPI_M_OSCancelAlarm(OsAlarm_BSW_BG_Crypto_Main);

  /* Cancel Alarm OsAlarm_BSW_10ms */
  SCHMDEINITAPI_M_OSCancelAlarm(OsAlarm_BSW_10ms);

  /* Cancel Alarm OsAlarm_BSW_5ms_Com */
  SCHMDEINITAPI_M_OSCancelAlarm(OsAlarm_BSW_5ms_Com);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  SchM_DeinitHook_Return();

}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_Start_DefaultPartition(void)
{
  Std_ReturnType Ldt_ReturnStatus;

  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  Ldt_ReturnStatus = RTE_E_OK;

  RTE_START_SET_SR_FLAGS_DEFAULTPARTITION;

  Rte_Gu8_InitFlag[RTE_START] = RTE_SET;

  (void)Rte_ModeMachineInitialization();

  /* Set Alarm OsAlarm_ASW_100ms */
  RTESTARTAPI_M_OSSetRelAlarm(OsAlarm_ASW_100ms, 15U, 80U, Ldt_ReturnStatus);

  /* Set Alarm OsAlarm_ASW_10ms */
  RTESTARTAPI_M_OSSetRelAlarm(OsAlarm_ASW_10ms, 3U, 8U, Ldt_ReturnStatus);

  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void)
{
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_StartHook_Start();
  if(Rte_CheckInitFlag(RTE_SCHM_INIT) == RTE_CLEAR)
  {
    Ldt_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    Ldt_ReturnStatus = Rte_Start_DefaultPartition();
    if(RTE_E_OK != Ldt_ReturnStatus)
    {
      Rte_Gu8_InitFlag[RTE_START] = RTE_CLEAR;
    }
  }
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_StartHook_Return();

  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_Stop_DefaultPartition(void)
{
  Std_ReturnType Ldt_ReturnStatus;

  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  Ldt_ReturnStatus = RTE_E_OK;

  /* Cancel Alarm OsAlarm_ASW_100ms */
  RTESTOPAPI_M_OSCancelAlarm(OsAlarm_ASW_100ms, Ldt_ReturnStatus);
  /* Cancel Alarm OsAlarm_ASW_10ms */
  RTESTOPAPI_M_OSCancelAlarm(OsAlarm_ASW_10ms, Ldt_ReturnStatus);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void)
{
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_StopHook_Start();

  Rte_Gu8_InitFlag[RTE_START] = RTE_CLEAR;
  Ldt_ReturnStatus = Rte_Stop_DefaultPartition();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_StopHook_Return();

  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_ComM_UM_ComMUser_LIN1_currentMode(CONST(ComM_ModeType, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_ComM_UM_ComMUser_LIN1_currentMode_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_ComM_UM_ComMUser_LIN1_currentMode_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }

  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    /* @Data Buffer Handling: Copy Data into global buffer */
    Rte_Gu8_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1 = Data;
    /* @DRE: Set the data received event flag */
    Rte_App_Lin_LIN1_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a = (RTE_SET)^(Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a);

    /* End of Critical Section */
    ResumeAllInterrupts();

    /* @ActivateTask: Activate task */
    RTEAPI_M_OSActivateTask(OsTask_BSW_FG2_LinScheduleRequest, Lu16_ReturnStatus, RTE_WRITE_SERVICEID);

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1_Return(Data);
  /* Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_ComM_UM_ComMUser_LIN2_currentMode(CONST(ComM_ModeType, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_ComM_UM_ComMUser_LIN2_currentMode_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_ComM_UM_ComMUser_LIN2_currentMode_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_requestedMode)
  {
    case RTE_MODE_MDG_ComMMode_SILENT_COM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_LIN2();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_FULL_COM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_LIN2();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_NO_COM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_LIN2();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN2_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_ComMMode_NO_COM:
      case RTE_MODE_MDG_ComMMode_SILENT_COM:
      case RTE_MODE_MDG_ComMMode_FULL_COM:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2 */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }

  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    /* @Data Buffer Handling: Copy Data into global buffer */
    Rte_Gu8_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2 = Data;
    /* @DRE: Set the data received event flag */
    Rte_App_Lin_LIN1_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0 = (RTE_SET)^(Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0);

    /* End of Critical Section */
    ResumeAllInterrupts();

    /* @ActivateTask: Activate task */
    RTEAPI_M_OSActivateTask(OsTask_BSW_FG3_ComMModeRequest, Lu16_ReturnStatus, RTE_WRITE_SERVICEID);

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2_Return(Data);
  /* Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_requestedMode)
  {
    case RTE_MODE_MDG_PduGroup_START:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx_Return();
      break;
    }
    case RTE_MODE_MDG_PduGroup_STOP:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_PduGroup_STOP:
      case RTE_MODE_MDG_PduGroup_START:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32 */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_requestedMode)
  {
    case RTE_MODE_MDG_ComMMode_PNC_PNC_PREPARE_SLEEP:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_FD_CAN1_PNC32();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_FD_CAN1_PNC32();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_PNC_PNC_READY_SLEEP:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_FD_CAN1_PNC32();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_PNC_PNC_FULL_COMMUNICATION:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_FD_CAN1_PNC32();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_PNC_PNC_REQUESTED:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_FD_CAN1_PNC32();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_FD_CAN1_PNC32_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_ComMMode_PNC_PNC_REQUESTED:
      case RTE_MODE_MDG_ComMMode_PNC_PNC_READY_SLEEP:
      case RTE_MODE_MDG_ComMMode_PNC_PNC_PREPARE_SLEEP:
      case RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION:
      case RTE_MODE_MDG_ComMMode_PNC_PNC_FULL_COMMUNICATION:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32 */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_requestedMode)
  {
    case RTE_MODE_MDG_PduGroup_START:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx_Return();
      break;
    }
    case RTE_MODE_MDG_PduGroup_STOP:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_PduGroup_STOP:
      case RTE_MODE_MDG_PduGroup_START:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32 */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_WdgM_globalMode_currentMode(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_WdgM_Mode_SUPERVISION_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_WdgM_globalMode_currentMode_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_WdgM_Mode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_WdgM_globalMode_currentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_WdgM_Mode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_WdgM_globalMode_currentMode.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_WdgM_globalMode_currentMode_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* Internal API to Queue Modes */
/* Rte_ModeMachine_<ASWC_Provider Name>_<Provider PortName>_<MDGP Name> */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_WdgM_globalMode_currentMode(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  if(Rte_Gst_MSFlags_Tx_WdgM_globalMode_currentMode.bl_OvfFlag == Rte_Gst_MSFlags_Rx_WdgM_globalMode_currentMode.bl_OvfFlag)
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    /* @DATA BUFFER HANDLING: Copy Data into global buffer */
    Rte_Gdt_MSQ_c5d478a01163f838[Rte_Gdt_WriteCntr_c5d478a01163f838] = Data;

    /* End of Critical Section */
    ResumeAllInterrupts();

    /* @INCREMENT: Increment the Send pointer index */
    Rte_Gdt_WriteCntr_c5d478a01163f838 = ((Rte_Gdt_WriteCntr_c5d478a01163f838 + RTE_ONE) % RTE_MAXQSIZE_c5d478a01163f838);

    /* @FLAG HANDLING: Set Overflow flag if queue is full */
    if(Rte_Gdt_WriteCntr_c5d478a01163f838 == Rte_Gdt_ReadCntr_c5d478a01163f838)
    {
      /* Start Critical Section */
      SuspendAllInterrupts();

      Rte_Gst_MSFlags_Tx_WdgM_globalMode_currentMode.bl_OvfFlag = (Rte_Gst_MSFlags_Rx_WdgM_globalMode_currentMode.bl_OvfFlag)^RTE_SET;

      /* End of Critical Section */
      ResumeAllInterrupts();

    }
  }
  else
  {
    /* @RETURN: Return Lu16_ReturnStatus with RTE_E_LIMIT */
    Lu16_ReturnStatus = (uint16)RTE_E_LIMIT;
  }
  if(RTE_E_OK == Lu16_ReturnStatus)
  {
  }

  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_WdgM_globalMode_currentMode(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_WdgM_globalMode_currentMode_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_WdgM_Mode_SUPERVISION_DEACTIVATED:
      case RTE_MODE_WdgM_Mode_SUPERVISION_EXPIRED:
      case RTE_MODE_WdgM_Mode_SUPERVISION_FAILED:
      case RTE_MODE_WdgM_Mode_SUPERVISION_OK:
      case RTE_MODE_WdgM_Mode_SUPERVISION_STOPPED:
      {
        /* @INVOKE: Rte_ModeMachine_WdgM_globalMode_currentMode */
        Lu16_ReturnStatus = Rte_ModeMachine_WdgM_globalMode_currentMode(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_WdgM_globalMode_currentMode_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_StbM_GlobalTime_StatusEvent_Client0_eventNotification(CONST(StbM_TimeBaseNotificationType, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_StbM_GlobalTime_StatusEvent_Client0_eventNotification_Start(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_StbM_GlobalTime_StatusEvent_Client0_eventNotification_Return(Data);

  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }

  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    /* @Data Buffer Handling: Copy Data into global buffer */
    Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 = Data;
    /* @DRE: Set the data received event flag */
    Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a = (RTE_SET)^(Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a);

    /* End of Critical Section */
    ResumeAllInterrupts();

    /* @ActivateTask: Activate task */
    RTEAPI_M_OSActivateTask(OsTask_BSW_FG3_ComMModeRequest, Lu16_ReturnStatus, RTE_WRITE_SERVICEID);

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_Return(Data);
  /* Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(CONST(uint8, RTE_APPL_CONST) Data)
{
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }

  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    /* @Data Buffer Handling: Copy Data into global buffer */
    Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 = Data;
    /* @DRE: Set the data received event flag */
    Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050 = (RTE_SET)^(Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050);

    /* End of Critical Section */
    ResumeAllInterrupts();

    /* @ActivateTask: Activate task */
    RTEAPI_M_OSActivateTask(OsTask_BSW_FG3_ComMModeRequest, Lu16_ReturnStatus, RTE_WRITE_SERVICEID);

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_Return(Data);
  /* Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }

  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    /* @Data Buffer Handling: Copy Data into global buffer */
    Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 = Data;
    /* @DRE: Set the data received event flag */
    Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440 = (RTE_SET)^(Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440);

    /* End of Critical Section */
    ResumeAllInterrupts();

    /* @ActivateTask: Activate task */
    RTEAPI_M_OSActivateTask(OsTask_BSW_FG3_ComMModeRequest, Lu16_ReturnStatus, RTE_WRITE_SERVICEID);

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_WriteHook_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_Return(Data);
  /* Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_requestedMode)
  {
    case RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX_POLL:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_WakeupEventValidated();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Return();
      break;
    }
    case RTE_MODE_MDG_WakeupEvent_LIN1_RX:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_WakeupEventValidated();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Return();
      break;
    }
    case RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_WakeupEventValidated();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Return();
      break;
    }
    case RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_WakeupEventValidated();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Return();
      break;
    }
    case RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX_POLL:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_WakeupEventValidated();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_WakeupEventValidated_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_WakeupEvent_POWER:
      case RTE_MODE_MDG_WakeupEvent_RESET:
      case RTE_MODE_MDG_WakeupEvent_INTERNAL_RESET:
      case RTE_MODE_MDG_WakeupEvent_INTERNAL_WDG:
      case RTE_MODE_MDG_WakeupEvent_EXTERNAL_WDG:
      case RTE_MODE_MDG_WakeupEvent_GPT:
      case RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX:
      case RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX_POLL:
      case RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX:
      case RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX_POLL:
      case RTE_MODE_MDG_WakeupEvent_LIN1_RX:
      case RTE_MODE_MDG_WakeupEvent_INITIAL_MODE:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
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
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_InitState_InitState(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_requestedMode)
  {
    case RTE_MODE_MDG_InitState_COMPLETE:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_InitCompleted_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_InitCompleted();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_InitCompleted_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_InitState_InitState(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_InitState_InitState_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_InitState_START:
      case RTE_MODE_MDG_InitState_COMPLETE:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_InitState_InitState */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_InitState_InitState(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_InitState_InitState_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_WdgM_mode_SE_Init_currentMode(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_WdgM_Mode_SUPERVISION_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_WdgM_mode_SE_Init_currentMode_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_WdgM_Mode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_WdgM_Mode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_WdgM_mode_SE_Init_currentMode_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_WdgM_mode_SE_Init_currentMode(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect. This flag is used to check the Mode which is in transition for another APIs" */
  Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.bl_isInTransition = RTE_TRUE;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.dt_currentMode = Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.dt_requestedMode;

  Rte_Gst_ActiveMode_WdgM_mode_SE_Init_currentMode.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_WdgM_mode_SE_Init_currentMode(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_WdgM_mode_SE_Init_currentMode_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_WdgM_Mode_SUPERVISION_DEACTIVATED:
      case RTE_MODE_WdgM_Mode_SUPERVISION_EXPIRED:
      case RTE_MODE_WdgM_Mode_SUPERVISION_FAILED:
      case RTE_MODE_WdgM_Mode_SUPERVISION_OK:
      case RTE_MODE_WdgM_Mode_SUPERVISION_STOPPED:
      {
        /* @INVOKE: Rte_ModeMachine_WdgM_mode_SE_Init_currentMode */
        Lu16_ReturnStatus = Rte_ModeMachine_WdgM_mode_SE_Init_currentMode(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_WdgM_mode_SE_Init_currentMode_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_WdgM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_ComM_UM_ComMUser_PNC32_currentMode(CONST(ComM_ModeType, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_ComM_UM_ComMUser_PNC32_currentMode_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_ComM_UM_ComMUser_PNC32_currentMode_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_ComM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_EcuM_currentMode_currentMode(CONST(EcuM_StateType, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.bl_isInTransition = RTE_TRUE;

    /* @ACTIVATE MODE DISABLINGS: Invoke RTE_ToggleModeDisabling for all runnables having disabling dependency */
    switch(Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode)
    {
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE:
      {
        Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_ONE(1);

        break;
      }
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_THREE:
      {
        Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_THREE(1);

        break;
      }
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_TWO:
      {
        Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_TWO(1);

        break;
      }
      default:
      {
        break;
      }
    }
  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode)
  {
    case RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_SLEEP:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_OFF:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_RUN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_PREP_SHUTDOWN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_RESET:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_APP_POST_RUN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    case RTE_MODE_EcuMode_ECUM_STATE_APP_RUN:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_EcuModeSwitched();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_EcuModeSwitched_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  if(Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode != Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode)
  {
    /* @DEACTIVATE MODE DISABLINGS: Invoke RTE_ToggleModeDisabling for all runnables having disabling dependency */
    switch(Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode)
    {
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE:
      {
        Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_ONE(0);

        break;
      }
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_THREE:
      {
        Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_THREE(0);

        break;
      }
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_TWO:
      {
        Rte_MgrToggleModeDisabling_EcuM_currentMode_currentMode_ECUM_STATE_STARTUP_TWO(0);

        break;
      }
      default:
      {
        break;
      }
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode;

  Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_EcuM_currentMode_currentMode(CONST(EcuM_StateType, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_EcuM_currentMode_currentMode_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE:
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_TWO:
      case RTE_MODE_EcuMode_ECUM_STATE_STARTUP_THREE:
      case RTE_MODE_EcuMode_ECUM_STATE_RUN:
      case RTE_MODE_EcuMode_ECUM_STATE_APP_RUN:
      case RTE_MODE_EcuMode_ECUM_STATE_APP_POST_RUN:
      case RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN:
      case RTE_MODE_EcuMode_ECUM_STATE_PREP_SHUTDOWN:
      case RTE_MODE_EcuMode_ECUM_STATE_SLEEP:
      case RTE_MODE_EcuMode_ECUM_STATE_OFF:
      case RTE_MODE_EcuMode_ECUM_STATE_RESET:
      {
        /* @INVOKE: Rte_ModeMachine_EcuM_currentMode_currentMode */
        Lu16_ReturnStatus = Rte_ModeMachine_EcuM_currentMode_currentMode(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_EcuM_currentMode_currentMode_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_requestedMode)
  {
    case RTE_MODE_MDG_ComMMode_FULL_COM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_LIN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_NO_COM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_LIN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Return();
      break;
    }
    case RTE_MODE_MDG_ComMMode_SILENT_COM:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_ComMModeSwitched_LIN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_ComMModeSwitched_LIN1_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_ComMMode_NO_COM:
      case RTE_MODE_MDG_ComMMode_SILENT_COM:
      case RTE_MODE_MDG_ComMMode_FULL_COM:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1 */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
static FUNC(Std_ReturnType, RTE_CODE) Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy Data into global buffer */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_requestedMode = Data;

  /* End of Critical Section */
  ResumeAllInterrupts();

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.bl_isInTransition = RTE_TRUE;

  /* @ONENTRY: Invoke all ONENTRY Runnable Entitites */
  switch(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_requestedMode)
  {
    case RTE_MODE_MDG_CanSMBORState_COMPLETE:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_CanSMBorStateSwitched_FD_CAN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_CanSMBorStateSwitched_FD_CAN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_CanSMBorStateSwitched_FD_CAN1_Return();
      break;
    }
    case RTE_MODE_MDG_CanSMBORState_START:
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_CanSMBorStateSwitched_FD_CAN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_CanSMBorStateSwitched_FD_CAN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_CanSMBorStateSwitched_FD_CAN1_Return();
      break;
    }
    default:
    {
      break;
    }
  }

  /* Start Critical Section */
  SuspendAllInterrupts();

  /* @DATA BUFFER HANDLING: Copy requestedMode into currentMode */
  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_requestedMode;

  Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.bl_isInTransition = RTE_FALSE;

  /* End of Critical Section */
  ResumeAllInterrupts();

  /* @RETURN: Return the status */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data)
{
  /* @DECLARATION: Declare variable to return status Initialize Lu16_ReturnStatus with RTE_E_OK */
  uint16 Lu16_ReturnStatus = (uint16)RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  else
  {
    switch(Data)
    {
      case RTE_MODE_MDG_CanSMBORState_COMPLETE:
      case RTE_MODE_MDG_CanSMBORState_START:
      case RTE_MODE_MDG_CanSMBORState_initmode:
      {
        /* @INVOKE: Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1 */
        Lu16_ReturnStatus = Rte_ModeMachine_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(Data);
        break;
      }
      default:
      {
        /* @RETURN: Return RTE_E_INVALID */
        Lu16_ReturnStatus = (uint16)RTE_E_INVALID;

        break;
      }
    }

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_Return(Data);
  /* @RETURN: Return Lu16_ReturnStatus */
  return (Std_ReturnType) Lu16_ReturnStatus;
}
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2(CONST(uint8, RTE_APPL_CONST) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2_Start(Data);
  /*LDRA_INSPECTED 203 S ; Source: MISRA:2012 R.11.8 */
  RTE_UNUSED(Data);

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_SwitchHook_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2_Return(Data);
  /* @RETURN: Return RTE_E_OK */
  return RTE_E_OK;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_WriteData_Start(Data, ErrorCode);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_WriteData_Return(Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_CallbackDCMRequestServices_ECU1_StartProtocol(VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress, VAR(uint16, AUTOMATIC) ConnectionId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_CallbackDCMRequestServices_ECU1_StartProtocol_Start(ProtocolType, TesterSourceAddress, ConnectionId);

  RTE_UNUSED(ProtocolType);

  RTE_UNUSED(TesterSourceAddress);

  RTE_UNUSED(ConnectionId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_CallbackDCMRequestServices_ECU1_StartProtocol_Return(ProtocolType, TesterSourceAddress, ConnectionId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestSleep(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestSleep_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_RequestSleep_Start();
    Ldt_ReturnStatus = EcuM_RequestSleep(user);
    Rte_Runnable_EcuM_EcuM_RequestSleep_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestSleep_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_GetSesCtrlType_Start(SesCtrlType);

  RTE_UNUSED(SesCtrlType);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_GetSesCtrlType_Return(SesCtrlType);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /* Local variable declaration Local variable initialization */
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Data)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Lu16_ReturnStatus = RTE_E_INVALID_ARGS;
  }
  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    *Data = Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1;

    /* End of Critical Section */
    ResumeAllInterrupts();

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_Return(Data);
  /* Return the status */
  return (Std_ReturnType)Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_CDD_LIN_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_CDD_LIN_CallbackAfterSchedule_lin_after_schedule(VAR(uint8, AUTOMATIC) channelId, VAR(uint8, AUTOMATIC) schId, VAR(uint8, AUTOMATIC) schEntryNum, VAR(uint8, AUTOMATIC) frameId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_CDD_LIN_CallbackAfterSchedule_lin_after_schedule_Start(channelId, schId, schEntryNum, frameId);

  RTE_UNUSED(channelId);

  RTE_UNUSED(schId);

  RTE_UNUSED(schEntryNum);

  RTE_UNUSED(frameId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_CDD_LIN_CallbackAfterSchedule_lin_after_schedule_Return(channelId, schId, schEntryNum, frameId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_CDD_LIN_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged_Start(EventId, EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventId);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged_Return(EventId, EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication(VAR(uint8, AUTOMATIC) SID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, VAR(uint16, AUTOMATIC) DataSize, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication_Start(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if((NULL_PTR == RequestData) || (NULL_PTR == ErrorCode))
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestSupplierNotification_Indication_Start();
    Ldt_ReturnStatus = ServiceRequestSupplierNotification_Indication(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestSupplierNotification_Indication_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication_Return(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow_Start(OverflowIndication);

  RTE_UNUSED(OverflowIndication);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow_Return(OverflowIndication);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /* Local variable declaration Local variable initialization */
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Data)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Lu16_ReturnStatus = RTE_E_INVALID_ARGS;
  }
  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    *Data = Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2;

    /* End of Critical Section */
    ResumeAllInterrupts();

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_Return(Data);
  /* Return the status */
  return (Std_ReturnType)Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Start(EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Return(EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus(VAR(boolean, AUTOMATIC) WIRStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus_Start(WIRStatus);

  RTE_UNUSED(WIRStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus_Return(WIRStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow_Start(OverflowIndication);

  RTE_UNUSED(OverflowIndication);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow_Return(OverflowIndication);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation(VAR(uint8, AUTOMATIC) SID, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation_Start(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestSupplierNotification_Confirmation_Start();
    Ldt_ReturnStatus = ServiceRequestSupplierNotification_Confirmation(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestSupplierNotification_Confirmation_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation_Return(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT10_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT10_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT10_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ReadFileOrDir(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) DataLength, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ReadFileOrDir_Start(OpStatus, DataLength, Data, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataLength);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ReadFileOrDir_Return(OpStatus, DataLength, Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_modeLimitation_LimitECUToNoComMode(VAR(boolean, AUTOMATIC) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_modeLimitation_LimitECUToNoComMode_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_LimitECUToNoComMode_Start();
    Ldt_ReturnStatus = ComM_LimitECUToNoComMode(Status);
    Rte_Runnable_ComM_ComM_LimitECUToNoComMode_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_modeLimitation_LimitECUToNoComMode_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(EcuM_StateType, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_currentMode_currentMode(P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(EcuM_StateType, RTE_DATA) Ldt_Data = RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_currentMode_currentMode_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_EcuMode;
    *previousMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_EcuM_currentMode_currentMode.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_currentMode_currentMode_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT9_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT9_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT9_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_App_Lin_LIN1_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_App_Lin_LIN1_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2_Start(previousMode, nextMode);
  /* @UNCONNECTED: Return INITIAL Mode */
  Ldt_Data = RTE_MODE_MDG_LinSchedule_LIN2_NULL;
  *previousMode = RTE_MODE_MDG_LinSchedule_LIN2_NULL;
  *nextMode = RTE_MODE_MDG_LinSchedule_LIN2_NULL;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_App_Lin_LIN1_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT2_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT2_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT2_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Start(EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Return(EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_EcuMTime_GetCurrentTime(P2VAR(EcuM_TimeType, AUTOMATIC, RTE_APPL_DATA) time)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_EcuMTime_GetCurrentTime_Start(time);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == time)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_GetCurrentTime_Start();
    Ldt_ReturnStatus = EcuM_GetCurrentTime(time);
    Rte_Runnable_EcuM_EcuM_GetCurrentTime_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_EcuMTime_GetCurrentTime_Return(time);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_IoHwAb_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_IoHwAb_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_IoHwAb_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData(VAR(uint16, AUTOMATIC) DID, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData_Start(DID, Data, OpStatus, DataLength, ErrorCode);

  RTE_UNUSED(DID);

  RTE_UNUSED(Data);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData_Return(DID, Data, OpStatus, DataLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_BootTarget_SelectBootTarget(VAR(EcuM_BootTargetType, AUTOMATIC) target)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_BootTarget_SelectBootTarget_Start(target);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_SelectBootTarget_Start();
    Ldt_ReturnStatus = EcuM_SelectBootTarget(target);
    Rte_Runnable_EcuM_EcuM_SelectBootTarget_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_BootTarget_SelectBootTarget_Return(target);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData(VAR(uint16, AUTOMATIC) DID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) DataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData_Start(DID, Data, OpStatus, DataLength, ErrorCode);

  RTE_UNUSED(DID);

  RTE_UNUSED(Data);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData_Return(DID, Data, OpStatus, DataLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DS000_ReportError(VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DS000_ReportError_Start(ApiId, ErrorId);

  RTE_UNUSED(ApiId);

  RTE_UNUSED(ErrorId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DS000_ReportError_Return(ApiId, ErrorId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EnableCond_EnableCondtion_0_SetEnableCondition(VAR(boolean, AUTOMATIC) ConditionFulfilled)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EnableCond_EnableCondtion_0_SetEnableCondition_Start(ConditionFulfilled);

  RTE_UNUSED(ConditionFulfilled);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EnableCond_EnableCondtion_0_SetEnableCondition_Return(ConditionFulfilled);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation(VAR(uint8, AUTOMATIC) SID, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation_Start(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestManufacturerNotification_Confirmation_Start();
    Ldt_ReturnStatus = ServiceRequestManufacturerNotification_Confirmation(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestManufacturerNotification_Confirmation_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation_Return(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_BootTarget_GetBootTarget(P2VAR(EcuM_BootTargetType, AUTOMATIC, RTE_APPL_DATA) target)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_BootTarget_GetBootTarget_Start(target);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == target)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_GetBootTarget_Start();
    Ldt_ReturnStatus = EcuM_GetBootTarget(target);
    Rte_Runnable_EcuM_EcuM_GetBootTarget_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_BootTarget_GetBootTarget_Return(target);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_DiagnosticService_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_DiagnosticService_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface_Start(previousMode, nextMode);
  /* @UNCONNECTED: Return INITIAL Mode */
  Ldt_Data = RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION;
  *previousMode = RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION;
  *nextMode = RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_DiagnosticService_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) resultBuffer, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) resultLength)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate_Start(resultBuffer, resultLength);

  RTE_UNUSED(resultBuffer);

  RTE_UNUSED(resultLength);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate_Return(resultBuffer, resultLength);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0005_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0005_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0005_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow_Start(OverflowIndication);

  RTE_UNUSED(OverflowIndication);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow_Return(OverflowIndication);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessRequestTransferExit(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessRequestTransferExit_Start(OpStatus, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessRequestTransferExit_Return(OpStatus, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT12_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT12_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT12_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleSpeed_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleSpeed_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleSpeed_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication(VAR(uint8, AUTOMATIC) SID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, VAR(uint16, AUTOMATIC) DataSize, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication_Start(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if((NULL_PTR == RequestData) || (NULL_PTR == ErrorCode))
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestManufacturerNotification_Indication_Start();
    Ldt_ReturnStatus = ServiceRequestManufacturerNotification_Indication(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);
    Rte_Runnable_SWC_DiagnosticService_ServiceRequestManufacturerNotification_Indication_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication_Return(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT4_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT4_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT4_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_InfotypeServices_VINInfoData_GetInfotypeValueData(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBuffer, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBufferSize)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_InfotypeServices_VINInfoData_GetInfotypeValueData_Start(OpStatus, DataValueBuffer, DataValueBufferSize);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataValueBuffer);

  RTE_UNUSED(DataValueBufferSize);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_InfotypeServices_VINInfoData_GetInfotypeValueData_Return(OpStatus, DataValueBuffer, DataValueBufferSize);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition1_SetStorageCondition(VAR(boolean, AUTOMATIC) ConditionFulfilled)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition1_SetStorageCondition_Start(ConditionFulfilled);

  RTE_UNUSED(ConditionFulfilled);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition1_SetStorageCondition_Return(ConditionFulfilled);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation(VAR(uint8, AUTOMATIC) SID, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation_Start(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);

  RTE_UNUSED(SID);

  RTE_UNUSED(ReqType);

  RTE_UNUSED(ConnectionId);

  RTE_UNUSED(ConfirmationStatus);

  RTE_UNUSED(ProtocolType);

  RTE_UNUSED(TesterSourceAddress);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation_Return(SID, ReqType, ConnectionId, ConfirmationStatus, ProtocolType, TesterSourceAddress);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow_Start(OverflowIndication);

  RTE_UNUSED(OverflowIndication);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow_Return(OverflowIndication);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessRequestUpload(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) DataFormatIdentifier, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessRequestUpload_Start(OpStatus, DataFormatIdentifier, MemoryIdentifier, MemoryAddress, MemorySize, BlockLength, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataFormatIdentifier);

  RTE_UNUSED(MemoryIdentifier);

  RTE_UNUSED(MemoryAddress);

  RTE_UNUSED(MemorySize);

  RTE_UNUSED(BlockLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessRequestUpload_Return(OpStatus, DataFormatIdentifier, MemoryIdentifier, MemoryAddress, MemorySize, BlockLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0003_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0003_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0003_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_InitState_InitState(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_InitState_START;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_InitState_InitState_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_InitState;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_InitState;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_InitState_InitState.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_InitState_InitState_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_FreezeCurrentState(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_FreezeCurrentState_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_FreezeCurrentState_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient1_ClearDTC(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient1_ClearDTC_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient1_ClearDTC_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable(VAR(boolean, AUTOMATIC) AvailableStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable_Start(AvailableStatus);

  RTE_UNUSED(AvailableStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable_Return(AvailableStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_GetLastShutdownTarget(P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, RTE_APPL_DATA) shutdownTarget, P2VAR(EcuM_ShutdownModeType, AUTOMATIC, RTE_APPL_DATA) shutdownMode)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_ShutdownTarget_GetLastShutdownTarget_Start(shutdownTarget, shutdownMode);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if((NULL_PTR == shutdownTarget) || (NULL_PTR == shutdownMode))
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_GetLastShutdownTarget_Start();
    Ldt_ReturnStatus = EcuM_GetLastShutdownTarget(shutdownTarget, shutdownMode);
    Rte_Runnable_EcuM_EcuM_GetLastShutdownTarget_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_ShutdownTarget_GetLastShutdownTarget_Return(shutdownTarget, shutdownMode);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Start(VAR(Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignalType, AUTOMATIC) DataIn_RID_0200h_StartInSignal, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StartOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Start_Start(DataIn_RID_0200h_StartInSignal, OpStatus, DataOut_RID_0200h_StartOutSignal, ErrorCode);

  RTE_UNUSED(DataIn_RID_0200h_StartInSignal);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataOut_RID_0200h_StartOutSignal);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Start_Return(DataIn_RID_0200h_StartInSignal, OpStatus, DataOut_RID_0200h_StartOutSignal, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx(VAR(uint8, AUTOMATIC) RecordNumber, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestBuffer, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) BufSize)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx_Start(RecordNumber, DestBuffer, BufSize);

  RTE_UNUSED(RecordNumber);

  RTE_UNUSED(DestBuffer);

  RTE_UNUSED(BufSize);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx_Return(RecordNumber, DestBuffer, BufSize);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_EcuMTime_GetWakeupTime(P2VAR(EcuM_TimeType, AUTOMATIC, RTE_APPL_DATA) time)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_EcuMTime_GetWakeupTime_Start(time);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == time)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_GetWakeupTime_Start();
    Ldt_ReturnStatus = EcuM_GetWakeupTime(time);
    Rte_Runnable_EcuM_EcuM_GetWakeupTime_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_EcuMTime_GetWakeupTime_Return(time);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ReturnControlToECU(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ReturnControlToECU_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ReturnControlToECU_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus(P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_APPL_DATA) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Status)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_GetInhibitionStatus_Start();
    Ldt_ReturnStatus = ComM_GetInhibitionStatus(RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus_1, Status);
    Rte_Runnable_ComM_ComM_GetInhibitionStatus_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed(P2VAR(AUTOSAR_boolean, AUTOMATIC, RTE_APPL_DATA) Allowed)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed_Start(Allowed);

  RTE_UNUSED(Allowed);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed_Return(Allowed);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT6_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT6_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT6_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Start(EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Return(EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /* Local variable declaration Local variable initialization */
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Data)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Lu16_ReturnStatus = RTE_E_INVALID_ARGS;
  }
  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    *Data = Rte_Gu8_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32;

    /* End of Critical Section */
    ResumeAllInterrupts();

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_Return(Data);
  /* Return the status */
  return (Std_ReturnType)Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ECT_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ECT_WriteData_Start(Data, ErrorCode);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ECT_WriteData_Return(Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_IoHwAb_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_IoHwAb_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_IoHwAb_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ControlDTCSuppression_SetDTCSuppression(VAR(uint8, AUTOMATIC) ClientID, VAR(boolean, AUTOMATIC) SuppressionStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ControlDTCSuppression_SetDTCSuppression_Start(ClientID, SuppressionStatus);

  RTE_UNUSED(ClientID);

  RTE_UNUSED(SuppressionStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ControlDTCSuppression_SetDTCSuppression_Return(ClientID, SuppressionStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM00_ControlFunctionAvailable_SetFunctionAvailable(VAR(boolean, AUTOMATIC) Availability)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM00_ControlFunctionAvailable_SetFunctionAvailable_Start(Availability);

  RTE_UNUSED(Availability);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM00_ControlFunctionAvailable_SetFunctionAvailable_Return(Availability);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_WdgMTest_globalMode_currentMode(void)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_WdgM_Mode_SUPERVISION_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_WdgMTest_globalMode_currentMode_Start();
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_WdgM_Mode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_WdgM_globalMode_currentMode.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_WdgM_Mode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_WdgM_globalMode_currentMode.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_WdgMTest_globalMode_currentMode_Return();
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow_Start(OverflowIndication);

  RTE_UNUSED(OverflowIndication);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow_Return(OverflowIndication);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestControlServices_Tid1_RequestControl(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) OutBuffer, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) InBuffer)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestControlServices_Tid1_RequestControl_Start(OutBuffer, InBuffer);

  RTE_UNUSED(OutBuffer);

  RTE_UNUSED(InBuffer);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestControlServices_Tid1_RequestControl_Return(OutBuffer, InBuffer);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_GetShutdownTarget(P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, RTE_APPL_DATA) shutdownTarget, P2VAR(EcuM_ShutdownModeType, AUTOMATIC, RTE_APPL_DATA) shutdownMode)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_ShutdownTarget_GetShutdownTarget_Start(shutdownTarget, shutdownMode);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if((NULL_PTR == shutdownTarget) || (NULL_PTR == shutdownMode))
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_GetShutdownTarget_Start();
    Ldt_ReturnStatus = EcuM_GetShutdownTarget(shutdownTarget, shutdownMode);
    Rte_Runnable_EcuM_EcuM_GetShutdownTarget_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_ShutdownTarget_GetShutdownTarget_Return(shutdownTarget, shutdownMode);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DTR_Dtr0_SetDTR(VAR(sint32, AUTOMATIC) TestResult, VAR(sint32, AUTOMATIC) LowerLimit, VAR(sint32, AUTOMATIC) UpperLimit, VAR(Dem_DTRControlType, AUTOMATIC) Ctrlval)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DTR_Dtr0_SetDTR_Start(TestResult, LowerLimit, UpperLimit, Ctrlval);

  RTE_UNUSED(TestResult);

  RTE_UNUSED(LowerLimit);

  RTE_UNUSED(UpperLimit);

  RTE_UNUSED(Ctrlval);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DTR_Dtr0_SetDTR_Return(TestResult, LowerLimit, UpperLimit, Ctrlval);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /* Local variable declaration Local variable initialization */
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Data)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Lu16_ReturnStatus = RTE_E_INVALID_ARGS;
  }
  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    *Data = Rte_Gu8_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2;

    /* End of Critical Section */
    ResumeAllInterrupts();

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_Return(Data);
  /* Return the status */
  return (Std_ReturnType)Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0001_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0001_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0001_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_ComMMode_NO_COM;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_ComMMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_ComMMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /* Local variable declaration Local variable initialization */
  uint16 Lu16_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_Start(Data);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_UNINIT */
    Lu16_ReturnStatus = RTE_E_UNINIT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Data)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Lu16_ReturnStatus = RTE_E_INVALID_ARGS;
  }
  else
  {
    /* Start Critical Section */
    SuspendAllInterrupts();

    *Data = Rte_Gu8_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1;

    /* End of Critical Section */
    ResumeAllInterrupts();

  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ReadHook_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_Return(Data);
  /* Return the status */
  return (Std_ReturnType)Lu16_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_IoHwAb_R_IoHwAbGptLogical0_Cbk_Notification(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_IoHwAb_R_IoHwAbGptLogical0_Cbk_Notification_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_IoHwAb_R_IoHwAbGptLogical0_Cbk_Notification_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ReturnControlToECU(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ReturnControlToECU_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ReturnControlToECU_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReplaceFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, VAR(uint8, AUTOMATIC) dataFormatIdentifier, VAR(uint64, AUTOMATIC) fileSizeUncompressed, VAR(uint64, AUTOMATIC) fileSizeCompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestReplaceFile_Start(OpStatus, filePathAndNameLength, filePathAndName, dataFormatIdentifier, fileSizeUncompressed, fileSizeCompressed, maxNumberOfBlockLength, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(filePathAndNameLength);

  RTE_UNUSED(filePathAndName);

  RTE_UNUSED(dataFormatIdentifier);

  RTE_UNUSED(fileSizeUncompressed);

  RTE_UNUSED(fileSizeCompressed);

  RTE_UNUSED(maxNumberOfBlockLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestReplaceFile_Return(OpStatus, filePathAndNameLength, filePathAndName, dataFormatIdentifier, fileSizeUncompressed, fileSizeCompressed, maxNumberOfBlockLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_ReleasePOST_RUN(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_ReleasePOST_RUN_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_ReleasePOST_RUN_Start();
    Ldt_ReturnStatus = EcuM_ReleasePOST_RUN(user);
    Rte_Runnable_EcuM_EcuM_ReleasePOST_RUN_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_ReleasePOST_RUN_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable(VAR(uint16, AUTOMATIC) DID, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_DidSupportedType, AUTOMATIC, RTE_APPL_DATA) Supported)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable_Start(DID, OpStatus, Supported);

  RTE_UNUSED(DID);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(Supported);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable_Return(DID, OpStatus, Supported);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_WriteData_Start(Data, ErrorCode);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_WriteData_Return(Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WdgMTest_WdgM_GlobalSupervision_GetGlobalStatus(P2VAR(WdgM_GlobalStatusType, AUTOMATIC, RTE_APPL_DATA) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_WdgM_GlobalSupervision_GetGlobalStatus_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Status)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_WdgM_WdgM_GetGlobalStatus_Start();
    Ldt_ReturnStatus = WdgM_GetGlobalStatus(Status);
    Rte_Runnable_WdgM_WdgM_GetGlobalStatus_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_WdgM_GlobalSupervision_GetGlobalStatus_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0008_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0008_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0008_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessRequestDownload(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) DataFormatIdentifier, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessRequestDownload_Start(OpStatus, DataFormatIdentifier, MemoryIdentifier, MemoryAddress, MemorySize, BlockLength, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataFormatIdentifier);

  RTE_UNUSED(MemoryIdentifier);

  RTE_UNUSED(MemoryAddress);

  RTE_UNUSED(MemorySize);

  RTE_UNUSED(BlockLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessRequestDownload_Return(OpStatus, DataFormatIdentifier, MemoryIdentifier, MemoryAddress, MemorySize, BlockLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength(VAR(uint16, AUTOMATIC) DID, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength_Start(DID, OpStatus, DataLength);

  RTE_UNUSED(DID);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataLength);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength_Return(DID, OpStatus, DataLength);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_BatVolt_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_BatVolt_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_BatVolt_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM00_FunctionInhibition_GetFunctionPermission(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) Permission)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM00_FunctionInhibition_GetFunctionPermission_Start(Permission);

  RTE_UNUSED(Permission);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM00_FunctionInhibition_GetFunctionPermission_Return(Permission);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT8_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT8_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT8_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ECT_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ECT_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ECT_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT1_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT1_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT1_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_PduGroup_STOP;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_PduGroup;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_PduGroup;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_SelectShutdownTarget(VAR(EcuM_ShutdownTargetType, AUTOMATIC) shutdownTarget, VAR(EcuM_ShutdownModeType, AUTOMATIC) shutdownMode)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_ShutdownTarget_SelectShutdownTarget_Start(shutdownTarget, shutdownMode);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_SelectShutdownTarget_Start();
    Ldt_ReturnStatus = EcuM_SelectShutdownTarget(shutdownTarget, shutdownMode);
    Rte_Runnable_EcuM_EcuM_SelectShutdownTarget_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_requirePort_ShutdownTarget_SelectShutdownTarget_Return(shutdownTarget, shutdownMode);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_ComMMode_PNC;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_ComMMode_PNC;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_BatVolt_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_BatVolt_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_BatVolt_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode(VAR(boolean, AUTOMATIC) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_LimitChannelToNoComMode_Start();
    Ldt_ReturnStatus = ComM_LimitChannelToNoComMode(RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode_1, Status);
    Rte_Runnable_ComM_ComM_LimitChannelToNoComMode_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient0_SelectDTC(VAR(uint32, AUTOMATIC) DTC, VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient0_SelectDTC_Start(DTC, DTCFormat, DTCOrigin);

  RTE_UNUSED(DTC);

  RTE_UNUSED(DTCFormat);

  RTE_UNUSED(DTCOrigin);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient0_SelectDTC_Return(DTC, DTCFormat, DTCOrigin);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WdgMTest_WdgM_GlobalSupervision_GetFirstExpiredSEID(P2VAR(WdgM_SupervisedEntityIdType, AUTOMATIC, RTE_APPL_DATA) SEID)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_WdgM_GlobalSupervision_GetFirstExpiredSEID_Start(SEID);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == SEID)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_WdgM_WdgM_GetFirstExpiredSEID_Start();
    Ldt_ReturnStatus = WdgM_GetFirstExpiredSEID(SEID);
    Rte_Runnable_WdgM_WdgM_GetFirstExpiredSEID_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_WdgM_GlobalSupervision_GetFirstExpiredSEID_Return(SEID);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_CsmKeyManagement_RandomSeed_L9_RandomSeed(VAR(Csm_ConstDataPtr, AUTOMATIC) seedPtr, VAR(uint32, AUTOMATIC) seedLength)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_CsmKeyManagement_RandomSeed_L9_RandomSeed_Start(seedPtr, seedLength);

  RTE_UNUSED(seedPtr);

  RTE_UNUSED(seedLength);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_CsmKeyManagement_RandomSeed_L9_RandomSeed_Return(seedPtr, seedLength);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_GeneralCBDataEvt_EventDataChanged(VAR(Dem_EventIdType, AUTOMATIC) EventId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_GeneralCBDataEvt_EventDataChanged_Start(EventId);

  RTE_UNUSED(EventId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_GeneralCBDataEvt_EventDataChanged_Return(EventId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_KeyM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_KeyM_KeyMCryptoKeyNotification_CryptoKeyUpdateCallbackNotification(VAR(KeyM_ResultType, AUTOMATIC) Result, VAR(uint16, AUTOMATIC) ResponseDataLength, VAR(KeyM_CryptoKeyDataType, AUTOMATIC) ResponseData)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_KeyM_KeyMCryptoKeyNotification_CryptoKeyUpdateCallbackNotification_Start(Result, ResponseDataLength, ResponseData);

  RTE_UNUSED(Result);

  RTE_UNUSED(ResponseDataLength);

  RTE_UNUSED(ResponseData);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_KeyM_KeyMCryptoKeyNotification_CryptoKeyUpdateCallbackNotification_Return(Result, ResponseDataLength, ResponseData);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_KeyM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_WriteFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint64, AUTOMATIC) DataLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_WriteFile_Start(OpStatus, DataLength, Data, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataLength);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_WriteFile_Return(OpStatus, DataLength, Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_FreezeCurrentState(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_FreezeCurrentState_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_FreezeCurrentState_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_modeLimitation_SetECUGroupClassification(VAR(ComM_InhibitionStatusType, AUTOMATIC) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_modeLimitation_SetECUGroupClassification_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_SetECUGroupClassification_Start();
    Ldt_ReturnStatus = ComM_SetECUGroupClassification(Status);
    Rte_Runnable_ComM_ComM_SetECUGroupClassification_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_modeLimitation_SetECUGroupClassification_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReadFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, VAR(uint8, AUTOMATIC) dataFormatIdentifier, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeUncompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeCompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestReadFile_Start(OpStatus, filePathAndNameLength, filePathAndName, dataFormatIdentifier, fileSizeUncompressed, fileSizeCompressed, maxNumberOfBlockLength, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(filePathAndNameLength);

  RTE_UNUSED(filePathAndName);

  RTE_UNUSED(dataFormatIdentifier);

  RTE_UNUSED(fileSizeUncompressed);

  RTE_UNUSED(fileSizeCompressed);

  RTE_UNUSED(maxNumberOfBlockLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestReadFile_Return(OpStatus, filePathAndNameLength, filePathAndName, dataFormatIdentifier, fileSizeUncompressed, fileSizeCompressed, maxNumberOfBlockLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_PduGroup_STOP;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_PduGroup;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_PduGroup;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_GetSecurityLevel_Start(SecLevel);

  RTE_UNUSED(SecLevel);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_GetSecurityLevel_Return(SecLevel);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessTransferDataWrite(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) MemoryData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessTransferDataWrite_Start(OpStatus, MemoryIdentifier, MemoryAddress, MemorySize, MemoryData, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(MemoryIdentifier);

  RTE_UNUSED(MemoryAddress);

  RTE_UNUSED(MemorySize);

  RTE_UNUSED(MemoryData);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessTransferDataWrite_Return(OpStatus, MemoryIdentifier, MemoryAddress, MemorySize, MemoryData, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_GetScalingInformation(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_GetScalingInformation_Start(ScalingInfo, ErrorCode);

  RTE_UNUSED(ScalingInfo);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_GetScalingInformation_Return(ScalingInfo, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus(P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_APPL_DATA) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Status)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_GetInhibitionStatus_Start();
    Ldt_ReturnStatus = ComM_GetInhibitionStatus(RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus_1, Status);
    Rte_Runnable_ComM_ComM_GetInhibitionStatus_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition(VAR(Dem_IumprDenomCondStatusType, AUTOMATIC) ConditionStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition_Start(ConditionStatus);

  RTE_UNUSED(ConditionStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition_Return(ConditionStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData(VAR(Dem_EventIdType, AUTOMATIC) EventStatus, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData1)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData_Start(EventStatus, monitorData0, monitorData1);

  RTE_UNUSED(EventStatus);

  RTE_UNUSED(monitorData0);

  RTE_UNUSED(monitorData1);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData_Return(EventStatus, monitorData0, monitorData1);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Fota_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Fota_Fota_StateRequest_RequestReset(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Fota_Fota_StateRequest_RequestReset_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_RequestReset_Start();
    Ldt_ReturnStatus = EcuM_RequestReset(user);
    Rte_Runnable_EcuM_EcuM_RequestReset_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Fota_Fota_StateRequest_RequestReset_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Fota_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IndStatus_DemIndicator_0_GetIndicatorStatus(P2VAR(Dem_IndicatorStatusType, AUTOMATIC, RTE_APPL_DATA) IndicatorStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IndStatus_DemIndicator_0_GetIndicatorStatus_Start(IndicatorStatus);

  RTE_UNUSED(IndicatorStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IndStatus_DemIndicator_0_GetIndicatorStatus_Return(IndicatorStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestAddFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, VAR(uint8, AUTOMATIC) dataFormatIdentifier, VAR(uint64, AUTOMATIC) fileSizeUncompressed, VAR(uint64, AUTOMATIC) fileSizeCompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestAddFile_Start(OpStatus, filePathAndNameLength, filePathAndName, dataFormatIdentifier, fileSizeUncompressed, fileSizeCompressed, maxNumberOfBlockLength, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(filePathAndNameLength);

  RTE_UNUSED(filePathAndName);

  RTE_UNUSED(dataFormatIdentifier);

  RTE_UNUSED(fileSizeUncompressed);

  RTE_UNUSED(fileSizeCompressed);

  RTE_UNUSED(maxNumberOfBlockLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestAddFile_Return(OpStatus, filePathAndNameLength, filePathAndName, dataFormatIdentifier, fileSizeUncompressed, fileSizeCompressed, maxNumberOfBlockLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0010_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0010_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0010_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ResetToDefault(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ResetToDefault_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ResetToDefault_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode(VAR(boolean, AUTOMATIC) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_LimitChannelToNoComMode_Start();
    Ldt_ReturnStatus = ComM_LimitChannelToNoComMode(RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode_1, Status);
    Rte_Runnable_ComM_ComM_LimitChannelToNoComMode_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_WriteData_Start(Data, ErrorCode);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VINDataIdentifier_WriteData_Return(Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0006_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0006_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0006_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx(VAR(uint8, AUTOMATIC) RecordNumber, VAR(uint16, AUTOMATIC) DataId, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestBuffer, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) BufSize)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx_Start(RecordNumber, DataId, DestBuffer, BufSize);

  RTE_UNUSED(RecordNumber);

  RTE_UNUSED(DataId);

  RTE_UNUSED(DestBuffer);

  RTE_UNUSED(BufSize);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx_Return(RecordNumber, DataId, DestBuffer, BufSize);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Start(EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Return(EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_SecurityAccess_L9_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Key, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_SecurityAccess_L9_CompareKey_Start(Key, OpStatus, ErrorCode);

  RTE_UNUSED(Key);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_SecurityAccess_L9_CompareKey_Return(Key, OpStatus, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestRUN(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestRUN_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_RequestRUN_Start();
    Ldt_ReturnStatus = EcuM_RequestRUN(user);
    Rte_Runnable_EcuM_EcuM_RequestRUN_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestRUN_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_WakeupEvent_WakeupEvent(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_WakeupEvent_INITIAL_MODE;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_WakeupEvent_WakeupEvent_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_WakeupEvent;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_WakeupEvent;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_WakeupEvent_WakeupEvent_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient0_ClearDTC(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient0_ClearDTC_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient0_ClearDTC_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT11_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT11_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT11_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition0_SetStorageCondition(VAR(boolean, AUTOMATIC) ConditionFulfilled)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition0_SetStorageCondition_Start(ConditionFulfilled);

  RTE_UNUSED(ConditionFulfilled);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition0_SetStorageCondition_Return(ConditionFulfilled);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT3_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT3_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT3_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReadDir(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) dirInfoLength, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestReadDir_Start(OpStatus, filePathAndNameLength, filePathAndName, dirInfoLength, maxNumberOfBlockLength, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(filePathAndNameLength);

  RTE_UNUSED(filePathAndName);

  RTE_UNUSED(dirInfoLength);

  RTE_UNUSED(maxNumberOfBlockLength);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestReadDir_Return(OpStatus, filePathAndNameLength, filePathAndName, dirInfoLength, maxNumberOfBlockLength, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_CallbackDCMRequestServices_ECU1_StopProtocol(VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress, VAR(uint16, AUTOMATIC) ConnectionId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_CallbackDCMRequestServices_ECU1_StopProtocol_Start(ProtocolType, TesterSourceAddress, ConnectionId);

  RTE_UNUSED(ProtocolType);

  RTE_UNUSED(TesterSourceAddress);

  RTE_UNUSED(ConnectionId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_CallbackDCMRequestServices_ECU1_StopProtocol_Return(ProtocolType, TesterSourceAddress, ConnectionId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode(VAR(boolean, AUTOMATIC) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_LimitChannelToNoComMode_Start();
    Ldt_ReturnStatus = ComM_LimitChannelToNoComMode(RTE_PDA_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode_1, Status);
    Rte_Runnable_ComM_ComM_LimitChannelToNoComMode_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Start(EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Return(EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ECT_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ECT_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ECT_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_ResetToDefaultSession(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_ResetToDefaultSession_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_ResetToDefaultSession_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestOff(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestOff_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_RequestOff_Start();
    Ldt_ReturnStatus = EcuM_RequestOff(user);
    Rte_Runnable_EcuM_EcuM_RequestOff_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestOff_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached(void)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached_Start();
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_WdgM_WdgM_CheckpointReached_Start();
    Ldt_ReturnStatus = WdgM_CheckpointReached(RTE_PDA_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached_SE_Init, RTE_PDA_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached_CP_Init_AS0);
    Rte_Runnable_WdgM_WdgM_CheckpointReached_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached_Return();
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocolType, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) ConnectionId, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) TesterSourceAddress)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_GetActiveProtocol_Start(ActiveProtocolType, ConnectionId, TesterSourceAddress);

  RTE_UNUSED(ActiveProtocolType);

  RTE_UNUSED(ConnectionId);

  RTE_UNUSED(TesterSourceAddress);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticService_DCM_Services_GetActiveProtocol_Return(ActiveProtocolType, ConnectionId, TesterSourceAddress);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestDeleteFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestDeleteFile_Start(OpStatus, filePathAndNameLength, filePathAndName, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(filePathAndNameLength);

  RTE_UNUSED(filePathAndName);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RequestFileTransfer_ProcessRequestDeleteFile_Return(OpStatus, filePathAndNameLength, filePathAndName, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_CanSMBORState_initmode;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_CanSMBORState;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_CanSMBORState;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification(VAR(uint32, AUTOMATIC) DTC, VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification_Start(DTC, DTCFormat, DTCOrigin);

  RTE_UNUSED(DTC);

  RTE_UNUSED(DTCFormat);

  RTE_UNUSED(DTCOrigin);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification_Return(DTC, DTCFormat, DTCOrigin);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_ReleaseRUN(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_ReleaseRUN_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_ReleaseRUN_Start();
    Ldt_ReturnStatus = EcuM_ReleaseRUN(user);
    Rte_Runnable_EcuM_EcuM_ReleaseRUN_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_ReleaseRUN_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0004_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0004_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0004_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OpCycle_POWER_CYCLE_RestartOperationCycle(void)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OpCycle_POWER_CYCLE_RestartOperationCycle_Start();

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OpCycle_POWER_CYCLE_RestartOperationCycle_Return();

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestReset(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestReset_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_RequestReset_Start();
    Ldt_ReturnStatus = EcuM_RequestReset(user);
    Rte_Runnable_EcuM_EcuM_RequestReset_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestReset_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestPOST_RUN(VAR(EcuM_UserType, AUTOMATIC) user)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestPOST_RUN_Start(user);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_EcuM_EcuM_RequestPOST_RUN_Start();
    Ldt_ReturnStatus = EcuM_RequestPOST_RUN(user);
    Rte_Runnable_EcuM_EcuM_RequestPOST_RUN_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_clientPort_StateRequest_RequestPOST_RUN_Return(user);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter(P2VAR(sint8, AUTOMATIC, RTE_APPL_DATA) FaultDetectionCounter)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter_Start(FaultDetectionCounter);

  RTE_UNUSED(FaultDetectionCounter);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter_Return(FaultDetectionCounter);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition(VAR(Dem_IumprDenomCondStatusType, AUTOMATIC) ConditionStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition_Start(ConditionStatus);

  RTE_UNUSED(ConditionStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition_Return(ConditionStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM01_FunctionInhibition_GetFunctionPermission(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) Permission)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM01_FunctionInhibition_GetFunctionPermission_Start(Permission);

  RTE_UNUSED(Permission);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM01_FunctionInhibition_GetFunctionPermission_Return(Permission);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT13_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT13_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT13_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ShortTermAdjustment(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ShortTermAdjustment_Start(ControlStateInfo, ErrorCode);

  RTE_UNUSED(ControlStateInfo);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_ActuatorControl_ShortTermAdjustment_Return(ControlStateInfo, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessTransferDataRead(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) MemoryData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessTransferDataRead_Start(OpStatus, MemoryIdentifier, MemoryAddress, MemorySize, MemoryData, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(MemoryIdentifier);

  RTE_UNUSED(MemoryAddress);

  RTE_UNUSED(MemorySize);

  RTE_UNUSED(MemoryData);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_UploadDownloadServices_ProcessTransferDataRead_Return(OpStatus, MemoryIdentifier, MemoryAddress, MemorySize, MemoryData, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_App_Lin_LIN1_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_App_Lin_LIN1_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1_Start(previousMode, nextMode);
  /* @UNCONNECTED: Return INITIAL Mode */
  Ldt_Data = RTE_MODE_MDG_LinSchedule_LIN1_NULL;
  *previousMode = RTE_MODE_MDG_LinSchedule_LIN1_NULL;
  *nextMode = RTE_MODE_MDG_LinSchedule_LIN1_NULL;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_App_Lin_LIN1_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleSpeed_GetScalingInformation(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleSpeed_GetScalingInformation_Start(ScalingInfo, ErrorCode);

  RTE_UNUSED(ScalingInfo);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleSpeed_GetScalingInformation_Return(ScalingInfo, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Stop(VAR(Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignalType, AUTOMATIC) DataIn_RID_0200h_StopInSignal, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StopOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Stop_Start(DataIn_RID_0200h_StopInSignal, OpStatus, DataOut_RID_0200h_StopOutSignal, ErrorCode);

  RTE_UNUSED(DataIn_RID_0200h_StopInSignal);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataOut_RID_0200h_StopOutSignal);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Stop_Return(DataIn_RID_0200h_StopInSignal, OpStatus, DataOut_RID_0200h_StopOutSignal, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT5_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT5_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT5_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_CDD_LIN_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_CDD_LIN_CallbackError_lin_cbk_err(VAR(uint8, AUTOMATIC) channelId, VAR(uint8, AUTOMATIC) errcode, VAR(uint8, AUTOMATIC) schEntryNum, VAR(uint8, AUTOMATIC) frameId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_CDD_LIN_CallbackError_lin_cbk_err_Start(channelId, errcode, schEntryNum, frameId);

  RTE_UNUSED(channelId);

  RTE_UNUSED(errcode);

  RTE_UNUSED(schEntryNum);

  RTE_UNUSED(frameId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_CDD_LIN_CallbackError_lin_cbk_err_Return(channelId, errcode, schEntryNum, frameId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_CDD_LIN_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DTR_Dtr1_SetDTR(VAR(sint32, AUTOMATIC) TestResult, VAR(sint32, AUTOMATIC) LowerLimit, VAR(sint32, AUTOMATIC) UpperLimit, VAR(Dem_DTRControlType, AUTOMATIC) Ctrlval)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DTR_Dtr1_SetDTR_Start(TestResult, LowerLimit, UpperLimit, Ctrlval);

  RTE_UNUSED(TestResult);

  RTE_UNUSED(LowerLimit);

  RTE_UNUSED(UpperLimit);

  RTE_UNUSED(Ctrlval);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DTR_Dtr1_SetDTR_Return(TestResult, LowerLimit, UpperLimit, Ctrlval);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification(VAR(uint32, AUTOMATIC) DTC, VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification_Start(DTC, DTCFormat, DTCOrigin);

  RTE_UNUSED(DTC);

  RTE_UNUSED(DTCFormat);

  RTE_UNUSED(DTCOrigin);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification_Return(DTC, DTCFormat, DTCOrigin);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries_Start(GetNumberOfEventMemoryEntries);

  RTE_UNUSED(GetNumberOfEventMemoryEntries);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries_Return(GetNumberOfEventMemoryEntries);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient1_SelectDTC(VAR(uint32, AUTOMATIC) DTC, VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient1_SelectDTC_Start(DTC, DTCFormat, DTCOrigin);

  RTE_UNUSED(DTC);

  RTE_UNUSED(DTCFormat);

  RTE_UNUSED(DTCOrigin);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ClearDTC_DemClient1_SelectDTC_Return(DTC, DTCFormat, DTCOrigin);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ControlDTCSuppression_GetDTCSuppression(VAR(uint8, AUTOMATIC) ClientID, P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) SuppressionStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ControlDTCSuppression_GetDTCSuppression_Start(ClientID, SuppressionStatus);

  RTE_UNUSED(ClientID);

  RTE_UNUSED(SuppressionStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_ControlDTCSuppression_GetDTCSuppression_Return(ClientID, SuppressionStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WdgMTest_WdgM_GlobalSupervision_SetMode(VAR(WdgM_ModeType, AUTOMATIC) Mode)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_WdgM_GlobalSupervision_SetMode_Start(Mode);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_WdgM_WdgM_SetMode_Start();
    Ldt_ReturnStatus = WdgM_SetMode(Mode);
    Rte_Runnable_WdgM_WdgM_SetMode_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_WdgMTest_WdgM_GlobalSupervision_SetMode_Return(Mode);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_WdgMTest_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0002_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0002_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0002_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM01_ControlFunctionAvailable_SetFunctionAvailable(VAR(boolean, AUTOMATIC) Availability)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM01_ControlFunctionAvailable_SetFunctionAvailable_Start(Availability);

  RTE_UNUSED(Availability);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_FiM01_ControlFunctionAvailable_SetFunctionAvailable_Return(Availability);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_BatVolt_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_BatVolt_WriteData_Start(Data, ErrorCode);

  RTE_UNUSED(Data);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_BatVolt_WriteData_Return(Data, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_RequestResults(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_RequestOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RoutineServices_RID_0200h_CalibrationActuator_RequestResults_Start(OpStatus, DataOut_RID_0200h_RequestOutSignal, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(DataOut_RID_0200h_RequestOutSignal);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_RoutineServices_RID_0200h_CalibrationActuator_RequestResults_Return(OpStatus, DataOut_RID_0200h_RequestOutSignal, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode)
{
  VAR(uint8, RTE_DATA) Ldt_Data = RTE_MODE_MDG_ComMMode_NO_COM;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_Start(previousMode, nextMode);
  /* @INITIALIZATION: If mode machine instance is not yet initialized */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    Ldt_Data = RTE_TRANSITION_MDG_ComMMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_requestedMode;
  }
  /* @INTRANSITION: If mode machine is in transition */
  else if(Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.bl_isInTransition != RTE_FALSE)
  {
    Ldt_Data = RTE_TRANSITION_MDG_ComMMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_requestedMode;
  }
  /* @INDEFINEDMODE: If mode machine is in a defined mode */
  else
  {
    Ldt_Data = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode;
    *previousMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode;
    *nextMode = Rte_Gst_ActiveMode_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1.dt_currentMode;
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_ModeHook_SWC_AppMode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_Return(previousMode, nextMode);
  /* @RETURN: Return Ldt_Data */
  return Ldt_Data;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent(VAR(Dem_InitMonitorReasonType, AUTOMATIC) InitMonitorReason)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent_Start(InitMonitorReason);

  RTE_UNUSED(InitMonitorReason);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent_Return(InitMonitorReason);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData_Start(Data);

  RTE_UNUSED(Data);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData_Return(Data);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_StbM_MeasurementNotification_Client0_SetSyncTimeRecordTable(P2CONST(StbM_SyncRecordTableBlockType, AUTOMATIC, RTE_APPL_CONST) syncRecordTableBlock)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_StbM_MeasurementNotification_Client0_SetSyncTimeRecordTable_Start(syncRecordTableBlock);

  RTE_UNUSED(syncRecordTableBlock);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_StbM_MeasurementNotification_Client0_SetSyncTimeRecordTable_Return(syncRecordTableBlock);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus(P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_APPL_DATA) Status)
{
  /* Declare Ldt_ReturnStatus Initialize Ldt_ReturnStatus with RTE_E_OK */
  Std_ReturnType Ldt_ReturnStatus = RTE_E_OK;

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus_Start(Status);
  /* @INVALID API INVOCATION : If RTE_START flag is clear */
  if(RTE_CLEAR == Rte_CheckInitFlag(RTE_START))
  {
    /* @RETURN: Return RTE_E_TIMEOUT */
    Ldt_ReturnStatus = RTE_E_TIMEOUT;
  }
  /* @NULL_PTR: NULL_PTR check in case of composite data type or transformerError */
  else if(NULL_PTR == Status)
  {
    /* @RETURN: Return RTE_E_INVALID_ARGS */
    Ldt_ReturnStatus = RTE_E_INVALID_ARGS;
  }

  else
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Rte_Runnable_ComM_ComM_GetInhibitionStatus_Start();
    Ldt_ReturnStatus = ComM_GetInhibitionStatus(RTE_PDA_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus_1, Status);
    Rte_Runnable_ComM_ComM_GetInhibitionStatus_Return();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  }

  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus_Return(Status);
  /* Return the status */
  return Ldt_ReturnStatus;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow_Start(OverflowIndication);

  RTE_UNUSED(OverflowIndication);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow_Return(OverflowIndication);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Start(EventStatusByteOld, EventStatusByteNew);

  RTE_UNUSED(EventStatusByteOld);

  RTE_UNUSED(EventStatusByteNew);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged_Return(EventStatusByteOld, EventStatusByteNew);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication(VAR(uint8, AUTOMATIC) SID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, VAR(uint16, AUTOMATIC) DataSize, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication_Start(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);

  RTE_UNUSED(SID);

  RTE_UNUSED(RequestData);

  RTE_UNUSED(DataSize);

  RTE_UNUSED(ReqType);

  RTE_UNUSED(ConnectionId);

  RTE_UNUSED(ErrorCode);

  RTE_UNUSED(ProtocolType);

  RTE_UNUSED(TesterSourceAddress);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication_Return(SID, RequestData, DataSize, ReqType, ConnectionId, ErrorCode, ProtocolType, TesterSourceAddress);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleSpeed_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleSpeed_ConditionCheckRead_Start(ErrorCode);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_VehicleSpeed_ConditionCheckRead_Return(ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DS000_ReportRuntimeError(VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DS000_ReportRuntimeError_Start(ApiId, ErrorId);

  RTE_UNUSED(ApiId);

  RTE_UNUSED(ErrorId);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_DS000_ReportRuntimeError_Return(ApiId, ErrorId);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0009_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0009_ReadData_Start(Data, monitorData0);

  RTE_UNUSED(Data);

  RTE_UNUSED(monitorData0);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dem_DataServices_DE_0009_ReadData_Return(Data, monitorData0);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ShortTermAdjustment(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ShortTermAdjustment_Start(ControlStateInfo, ErrorCode);

  RTE_UNUSED(ControlStateInfo);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_DataServices_RPM_ShortTermAdjustment_Return(ControlStateInfo, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_SecurityAccess_L9_GetSeed(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_SecurityAccess_L9_GetSeed_Start(OpStatus, Seed, ErrorCode);

  RTE_UNUSED(OpStatus);

  RTE_UNUSED(Seed);

  RTE_UNUSED(ErrorCode);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_Dcm_SecurityAccess_L9_GetSeed_Return(OpStatus, Seed, ErrorCode);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-begin CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT7_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT7_SetEventStatus_Start(EventStatus);

  RTE_UNUSED(EventStatus);
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_CallHook_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT7_SetEventStatus_Return(EventStatus);

  /* Return RTE_E_UNCONNECTED */
  return RTE_E_UNCONNECTED;
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
/* polyspace-end CERT-C:DCL37-C [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:21.2 [Justified:Low] "Some Rte_Call_ functions are generated to adapt some AUTOSAR APIs of BSW modules. Therefore, naming of parameters is basing on it." */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As SWS_Rte_01334, in case required port is unconnected, Rte_Call must to return RTE_E_UNCONNECTED immediately, so all parameters are NOT used and changed." */

/* polyspace-end MISRA-C3:5.8 [Justified:Low] "Rte is using 'Data' as common name for input parameter in almost functions" */

/******************************************************************************/
/*                           Generated Task Bodies                            */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_ASW_FG1_100ms
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_ASW_FG1_100ms)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_RteStartFlag = &Rte_Gu8_InitFlag[RTE_START];
  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Dispatch_Internal(OsTask_ASW_FG1_100ms);
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "BitVector flag will be changed by another uinon type in another APIs." */
    if(Rte_Gun_BitVector_SWC_AppMode_AppMode_Test.u32_BitVector == 0U)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_Test_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      AppMode_Test();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_SWC_AppMode_AppMode_Test_Return();
    }
  }

  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Terminate_Internal(OsTask_ASW_FG1_100ms);

  RTE_M_OSTerminateTask();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_ASW_FG1_100ms
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_ASW_FG1_10ms
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_ASW_FG1_10ms)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_RteStartFlag = &Rte_Gu8_InitFlag[RTE_START];
  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Dispatch_Internal(OsTask_ASW_FG1_10ms);
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Runnable_Os_Master_Os_MeasureCPULoad_Start();

    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Os_MeasureCPULoad();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Runnable_Os_Master_Os_MeasureCPULoad_Return();
  }
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Runnable_SWC_WdgMTest_RE_WdgMTest_Start();

    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    RE_WdgMTest();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Runnable_SWC_WdgMTest_RE_WdgMTest_Return();
  }
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Runnable_SWC_DiagnosticMonitor_DiagnosticMonitor_Start();

    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    DiagnosticMonitor();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Runnable_SWC_DiagnosticMonitor_DiagnosticMonitor_Return();
  }

  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Terminate_Internal(OsTask_ASW_FG1_10ms);

  RTE_M_OSTerminateTask();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_ASW_FG1_10ms
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_BG_Crypto_Main
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_BG_Crypto_Main)
{
  EventMaskType Rte_LdtEventMaskValue;
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_SchMInitFlag = &Rte_Gu8_InitFlag[RTE_SCHM_INIT];

  Rte_LdtEventMaskValue = RTE_CLEAR;
  /*LDRA_INSPECTED 28 D ; Source: MISRA:2012 R.2.1 */
  while(1)
  {
    RTE_M_OSWaitEvent(OsTask_BSW_BG_Crypto_Main, OsEvent_BSW_Crypto_Main );
    RTE_M_OSGetEvent(OsTask_BSW_BG_Crypto_Main, &Rte_LdtEventMaskValue);
    RTE_M_OSClearEvent(Rte_LdtEventMaskValue);

    /* Invocation of VFB Trace Hook functions */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Task_Dispatch_Internal(OsTask_BSW_BG_Crypto_Main);

    if(RTE_SET == *Lpu8_SchMInitFlag)
    {
      if((Rte_LdtEventMaskValue & OsEvent_BSW_Crypto_Main) == OsEvent_BSW_Crypto_Main)
      {
        /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
        SchM_Schedulable_Crypto_76_HaeModule_HaeCryptoLib_MainFunction_Start();

        Crypto_76_HaeModule_HaeCryptoLib_MainFunction();
        /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
        SchM_Schedulable_Crypto_76_HaeModule_HaeCryptoLib_MainFunction_Return();

      }
    }
    Rte_LdtEventMaskValue = RTE_CLEAR;
    /* Invocation of VFB Trace Hook functions */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Task_Terminate_Internal(OsTask_BSW_BG_Crypto_Main);
  }
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_BG_Crypto_Main
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_BG_Fota
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_BG_Fota)
{
  EventMaskType Rte_LdtEventMaskValue;
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_SchMInitFlag = &Rte_Gu8_InitFlag[RTE_SCHM_INIT];

  Rte_LdtEventMaskValue = RTE_CLEAR;
  /*LDRA_INSPECTED 28 D ; Source: MISRA:2012 R.2.1 */
  while(1)
  {
    RTE_M_OSWaitEvent(OsTask_BSW_BG_Fota, OsEvent_BG_Fota );
    RTE_M_OSGetEvent(OsTask_BSW_BG_Fota, &Rte_LdtEventMaskValue);
    RTE_M_OSClearEvent(Rte_LdtEventMaskValue);

    /* Invocation of VFB Trace Hook functions */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Task_Dispatch_Internal(OsTask_BSW_BG_Fota);

    if(RTE_SET == *Lpu8_SchMInitFlag)
    {
      if((Rte_LdtEventMaskValue & OsEvent_BG_Fota) == OsEvent_BG_Fota)
      {
        /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
        SchM_Schedulable_Fota_MainFunction_Start();

        Fota_MainFunction();
        /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
        SchM_Schedulable_Fota_MainFunction_Return();

      }
    }
    Rte_LdtEventMaskValue = RTE_CLEAR;
    /* Invocation of VFB Trace Hook functions */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Task_Terminate_Internal(OsTask_BSW_BG_Fota);
  }
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_BG_Fota
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_BG_KeyM_Main
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_BG_KeyM_Main)
{
  EventMaskType Rte_LdtEventMaskValue;
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_SchMInitFlag = &Rte_Gu8_InitFlag[RTE_SCHM_INIT];

  Rte_LdtEventMaskValue = RTE_CLEAR;
  /*LDRA_INSPECTED 28 D ; Source: MISRA:2012 R.2.1 */
  while(1)
  {
    RTE_M_OSWaitEvent(OsTask_BSW_BG_KeyM_Main, OsEvent_BSW_KeyM_Main );
    RTE_M_OSGetEvent(OsTask_BSW_BG_KeyM_Main, &Rte_LdtEventMaskValue);
    RTE_M_OSClearEvent(Rte_LdtEventMaskValue);

    /* Invocation of VFB Trace Hook functions */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Task_Dispatch_Internal(OsTask_BSW_BG_KeyM_Main);

    if(RTE_SET == *Lpu8_SchMInitFlag)
    {
      if((Rte_LdtEventMaskValue & OsEvent_BSW_KeyM_Main) == OsEvent_BSW_KeyM_Main)
      {
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "BitVector flag will be changed by another uinon type in another APIs." */
        if(Rte_Gun_BitVector_KeyM_BswSE_KeyM_MainBackgroundFunction.u32_BitVector == 0U)
        {
          /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
          SchM_Schedulable_KeyM_MainBackgroundFunction_Start();

          KeyM_MainBackgroundFunction();
          /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
          SchM_Schedulable_KeyM_MainBackgroundFunction_Return();

        }
      }
    }
    Rte_LdtEventMaskValue = RTE_CLEAR;
    /* Invocation of VFB Trace Hook functions */
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    Rte_Task_Terminate_Internal(OsTask_BSW_BG_KeyM_Main);
  }
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_BG_KeyM_Main
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_FG1_10ms
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_FG1_10ms)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_SchMInitFlag = &Rte_Gu8_InitFlag[RTE_SCHM_INIT];
  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Dispatch_Internal(OsTask_BSW_FG1_10ms);
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_Crypto_MainFunction_Start();

    Crypto_MainFunction();
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_Crypto_MainFunction_Return();

  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_BswM_MainFunction_Start();

    BswM_MainFunction();
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_BswM_MainFunction_Return();

  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_EcuM_MainFunction_Start();

    EcuM_MainFunction();
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_EcuM_MainFunction_Return();

  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "BitVector flag will be changed by another uinon type in another APIs." */
    if(Rte_Gun_BitVector_KeyM_BswSE_KeyM_MainFunction.u32_BitVector == 0U)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_KeyM_MainFunction_Start();

      KeyM_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_KeyM_MainFunction_Return();

    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "BitVector flag will be changed by another uinon type in another APIs." */
    if(Rte_Gun_BitVector_Csm_BswSE_Csm_MainFunction.u32_BitVector == 0U)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Csm_MainFunction_Start();

      Csm_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Csm_MainFunction_Return();

    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "BitVector flag will be changed by another uinon type in another APIs." */
    if(Rte_Gun_BitVector_WdgM_BswSE_WdgM_MainFunction.u32_BitVector == 0U)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_WdgM_MainFunction_Start();

      WdgM_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_WdgM_MainFunction_Return();

    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_Dem_MainFunction_Start();

    Dem_MainFunction();
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_Dem_MainFunction_Return();

  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_FiM_MainFunction_Start();

    FiM_MainFunction();
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
    SchM_Schedulable_FiM_MainFunction_Return();

  }

  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Terminate_Internal(OsTask_BSW_FG1_10ms);

  RTE_M_OSTerminateTask();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_FG1_10ms
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_FG1_5ms_Com
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_FG1_5ms_Com)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_SchMInitFlag = &Rte_Gu8_InitFlag[RTE_SCHM_INIT];
  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Dispatch_Internal(OsTask_BSW_FG1_5ms_Com);
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_FD_CAN1_BswTE_ComM_MainFunction_ComMChannel_FD_CAN1++;
    if(RTE_PERIOD_ComM_BswSE_ComM_MainFunction_ComMChannel_FD_CAN1_BswTE_ComM_MainFunction_ComMChannel_FD_CAN1 == Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_FD_CAN1_BswTE_ComM_MainFunction_ComMChannel_FD_CAN1)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_ComM_MainFunction_ComMChannel_FD_CAN1_Start();

      ComM_MainFunction_ComMChannel_FD_CAN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_ComM_MainFunction_ComMChannel_FD_CAN1_Return();

      Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_FD_CAN1_BswTE_ComM_MainFunction_ComMChannel_FD_CAN1 = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN1_BswTE_ComM_MainFunction_ComMChannel_LIN1++;
    if(RTE_PERIOD_ComM_BswSE_ComM_MainFunction_ComMChannel_LIN1_BswTE_ComM_MainFunction_ComMChannel_LIN1 == Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN1_BswTE_ComM_MainFunction_ComMChannel_LIN1)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_ComM_MainFunction_ComMChannel_LIN1_Start();

      ComM_MainFunction_ComMChannel_LIN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_ComM_MainFunction_ComMChannel_LIN1_Return();

      Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN1_BswTE_ComM_MainFunction_ComMChannel_LIN1 = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN2_BswTE_ComM_MainFunction_ComMChannel_LIN2++;
    if(RTE_PERIOD_ComM_BswSE_ComM_MainFunction_ComMChannel_LIN2_BswTE_ComM_MainFunction_ComMChannel_LIN2 == Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN2_BswTE_ComM_MainFunction_ComMChannel_LIN2)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_ComM_MainFunction_ComMChannel_LIN2_Start();

      ComM_MainFunction_ComMChannel_LIN2();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_ComM_MainFunction_ComMChannel_LIN2_Return();

      Rte_Gu32Counter_BswSE_ComM_MainFunction_ComMChannel_LIN2_BswTE_ComM_MainFunction_ComMChannel_LIN2 = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_CanCM_MainFunction_BswTE_CanCM_MainFunction++;
    if(RTE_PERIOD_CanCM_BswSE_CanCM_MainFunction_BswTE_CanCM_MainFunction == Rte_Gu32Counter_BswSE_CanCM_MainFunction_BswTE_CanCM_MainFunction)
    {
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "BitVector flag will be changed by another uinon type in another APIs." */
      if(Rte_Gun_BitVector_CanCM_BswSE_CanCM_MainFunction.u32_BitVector == 0U)
      {
        /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
        SchM_Schedulable_CanCM_MainFunction_Start();

        CanCM_MainFunction();
        /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
        SchM_Schedulable_CanCM_MainFunction_Return();

      }
      Rte_Gu32Counter_BswSE_CanCM_MainFunction_BswTE_CanCM_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_CanTrcv_MainFunction_BswTE_CanTrcv_MainFunction++;
    if(RTE_PERIOD_CanTrcv_BswSE_CanTrcv_MainFunction_BswTE_CanTrcv_MainFunction == Rte_Gu32Counter_BswSE_CanTrcv_MainFunction_BswTE_CanTrcv_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanTrcv_MainFunction_Start();

      CanTrcv_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanTrcv_MainFunction_Return();

      Rte_Gu32Counter_BswSE_CanTrcv_MainFunction_BswTE_CanTrcv_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_Com_MainFunctionRx_BswTE_Com_MainFunctionRx++;
    if(RTE_PERIOD_Com_BswSE_Com_MainFunctionRx_BswTE_Com_MainFunctionRx == Rte_Gu32Counter_BswSE_Com_MainFunctionRx_BswTE_Com_MainFunctionRx)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Com_MainFunctionRx_Start();

      Com_MainFunctionRx();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Com_MainFunctionRx_Return();

      Rte_Gu32Counter_BswSE_Com_MainFunctionRx_BswTE_Com_MainFunctionRx = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_Com_MainFunctionTx_BswTE_Com_MainFunctionTx++;
    if(RTE_PERIOD_Com_BswSE_Com_MainFunctionTx_BswTE_Com_MainFunctionTx == Rte_Gu32Counter_BswSE_Com_MainFunctionTx_BswTE_Com_MainFunctionTx)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Com_MainFunctionTx_Start();

      Com_MainFunctionTx();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Com_MainFunctionTx_Return();

      Rte_Gu32Counter_BswSE_Com_MainFunctionTx_BswTE_Com_MainFunctionTx = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_CanSM_MainFunction_BswTE_CanSM_MainFunction++;
    if(RTE_PERIOD_CanSM_BswSE_CanSM_MainFunction_BswTE_CanSM_MainFunction == Rte_Gu32Counter_BswSE_CanSM_MainFunction_BswTE_CanSM_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanSM_MainFunction_Start();

      CanSM_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanSM_MainFunction_Return();

      Rte_Gu32Counter_BswSE_CanSM_MainFunction_BswTE_CanSM_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_CanNm_MainFunction_BswSE_CanNm_MainFunction++;
    if(RTE_PERIOD_CanNm_BswSE_CanNm_MainFunction_BswSE_CanNm_MainFunction == Rte_Gu32Counter_BswSE_CanNm_MainFunction_BswSE_CanNm_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanNm_MainFunction_Start();

      CanNm_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanNm_MainFunction_Return();

      Rte_Gu32Counter_BswSE_CanNm_MainFunction_BswSE_CanNm_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_Dcm_MainFunction_BswTE_Dcm_MainFunction++;
    if(RTE_PERIOD_Dcm_BswSE_Dcm_MainFunction_BswTE_Dcm_MainFunction == Rte_Gu32Counter_BswSE_Dcm_MainFunction_BswTE_Dcm_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Dcm_MainFunction_Start();

      Dcm_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_Dcm_MainFunction_Return();

      Rte_Gu32Counter_BswSE_Dcm_MainFunction_BswTE_Dcm_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_CanTp_MainFunction_BswTE_CanTp_MainFunction++;
    if(RTE_PERIOD_CanTp_BswSE_CanTp_MainFunction_BswTE_CanTp_MainFunction == Rte_Gu32Counter_BswSE_CanTp_MainFunction_BswTE_CanTp_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanTp_MainFunction_Start();

      CanTp_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_CanTp_MainFunction_Return();

      Rte_Gu32Counter_BswSE_CanTp_MainFunction_BswTE_CanTp_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_LinSM_MainFunction_BswTE_LinSM_MainFunction++;
    if(RTE_PERIOD_LinSM_BswSE_LinSM_MainFunction_BswTE_LinSM_MainFunction == Rte_Gu32Counter_BswSE_LinSM_MainFunction_BswTE_LinSM_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_LinSM_MainFunction_Start();

      LinSM_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_LinSM_MainFunction_Return();

      Rte_Gu32Counter_BswSE_LinSM_MainFunction_BswTE_LinSM_MainFunction = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN1_BswTE_LinIf_MainFunction_LinIfChannel_LIN1++;
    if(RTE_PERIOD_LinIf_BswSE_LinIf_MainFunction_LinIfChannel_LIN1_BswTE_LinIf_MainFunction_LinIfChannel_LIN1 == Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN1_BswTE_LinIf_MainFunction_LinIfChannel_LIN1)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_LinIf_MainFunction_LinIfChannel_LIN1_Start();

      LinIf_MainFunction_LinIfChannel_LIN1();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_LinIf_MainFunction_LinIfChannel_LIN1_Return();

      Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN1_BswTE_LinIf_MainFunction_LinIfChannel_LIN1 = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN2_BswTE_LinIf_MainFunction_LinIfChannel_LIN2++;
    if(RTE_PERIOD_LinIf_BswSE_LinIf_MainFunction_LinIfChannel_LIN2_BswTE_LinIf_MainFunction_LinIfChannel_LIN2 == Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN2_BswTE_LinIf_MainFunction_LinIfChannel_LIN2)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_LinIf_MainFunction_LinIfChannel_LIN2_Start();

      LinIf_MainFunction_LinIfChannel_LIN2();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_LinIf_MainFunction_LinIfChannel_LIN2_Return();

      Rte_Gu32Counter_BswSE_LinIf_MainFunction_LinIfChannel_LIN2_BswTE_LinIf_MainFunction_LinIfChannel_LIN2 = 0;
    }
  }
  if(RTE_SET == *Lpu8_SchMInitFlag)
  {
    Rte_Gu32Counter_BswSE_StbM_MainFunction_BswTE_StbM_MainFunction++;
    if(RTE_PERIOD_StbM_BswSE_StbM_MainFunction_BswTE_StbM_MainFunction == Rte_Gu32Counter_BswSE_StbM_MainFunction_BswTE_StbM_MainFunction)
    {
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_StbM_MainFunction_Start();

      StbM_MainFunction();
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      SchM_Schedulable_StbM_MainFunction_Return();

      Rte_Gu32Counter_BswSE_StbM_MainFunction_BswTE_StbM_MainFunction = 0;
    }
  }

  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Terminate_Internal(OsTask_BSW_FG1_5ms_Com);

  RTE_M_OSTerminateTask();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_FG1_5ms_Com
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_FG2_LinScheduleRequest
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_FG2_LinScheduleRequest)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_RteStartFlag = &Rte_Gu8_InitFlag[RTE_START];
  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Dispatch_Internal(OsTask_BSW_FG2_LinScheduleRequest);
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    if(Rte_App_Lin_LIN1_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a != Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a)
    {
      /* Start Critical Section */
      SuspendAllInterrupts();

      Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a = Rte_App_Lin_LIN1_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a;
      /* End of Critical Section */
      ResumeAllInterrupts();

      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_LinSchedule_LIN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      BswM_Immediate_LinSchedule_LIN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_LinSchedule_LIN1_Return();
    }

  }

  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Terminate_Internal(OsTask_BSW_FG2_LinScheduleRequest);

  RTE_M_OSTerminateTask();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_FG2_LinScheduleRequest
#include "Os_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_START_SEC_CODE_OsTask_BSW_FG3_ComMModeRequest
#include "Os_MemMap.h"
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
TASK(OsTask_BSW_FG3_ComMModeRequest)
{
  /*LDRA_INSPECTED 8 D ; Source: MISRA:2012 R.2.2 */
  volatile uint8 * Lpu8_RteStartFlag = &Rte_Gu8_InitFlag[RTE_START];
  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Dispatch_Internal(OsTask_BSW_FG3_ComMModeRequest);
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    if(Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440 != Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440)
    {
      /* Start Critical Section */
      SuspendAllInterrupts();

      Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440 = Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440;
      /* End of Critical Section */
      ResumeAllInterrupts();

      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_ComMMode_LIN1_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      BswM_Immediate_ComMMode_LIN1();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_ComMMode_LIN1_Return();
    }

  }
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    if(Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050 != Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050)
    {
      /* Start Critical Section */
      SuspendAllInterrupts();

      Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050 = Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050;
      /* End of Critical Section */
      ResumeAllInterrupts();

      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_ComMMode_PNC32_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      BswM_Immediate_ComMMode_PNC32();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_ComMMode_PNC32_Return();
    }

  }
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    if(Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a != Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a)
    {
      /* Start Critical Section */
      SuspendAllInterrupts();

      Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a = Rte_SWC_AppMode_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a;
      /* End of Critical Section */
      ResumeAllInterrupts();

      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_ComMMode_LIN2_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      BswM_Immediate_ComMMode_LIN2();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_ComMMode_LIN2_Return();
    }

  }
  if(RTE_SET == *Lpu8_RteStartFlag)
  {
    if(Rte_App_Lin_LIN1_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0 != Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0)
    {
      /* Start Critical Section */
      SuspendAllInterrupts();

      Rte_BswM_Partition_Main_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0 = Rte_App_Lin_LIN1_Gdt_EventFlagType.RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0;
      /* End of Critical Section */
      ResumeAllInterrupts();

      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_LinSchedule_LIN2_Start();

      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      BswM_Immediate_LinSchedule_LIN2();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
      Rte_Runnable_BswM_Partition_Main_BswM_Immediate_LinSchedule_LIN2_Return();
    }

  }

  /* Invocation of VFB Trace Hook functions */
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */
  Rte_Task_Terminate_Internal(OsTask_BSW_FG3_ComMModeRequest);

  RTE_M_OSTerminateTask();
}
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
#define OS_STOP_SEC_CODE_OsTask_BSW_FG3_ComMModeRequest
#include "Os_MemMap.h"

