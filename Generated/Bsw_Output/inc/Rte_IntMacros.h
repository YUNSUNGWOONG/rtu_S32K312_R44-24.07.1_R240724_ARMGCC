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
**  File Name : Rte_IntMacros.h                                               **
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
#ifndef RTE_INTMACROS_H
#define RTE_INTMACROS_H

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                                 RTE Macro                                  */
/******************************************************************************/

/******************************************************************************/
/*     Port Defined Argument Value Macros for Client Server communication     */
/******************************************************************************/
#define RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode_1   1

#define RTE_PDA_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached_CP_Init_AS0     0

#define RTE_PDA_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached_SE_Init         300

#define RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus_1       2

#define RTE_PDA_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus_1  0

#define RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode_1   2

#define RTE_PDA_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode_1  0

#define RTE_PDA_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus_1       1

/******************************************************************************/
/*             Maximum Queue Size Macros Required for Mode Switch             */
/******************************************************************************/
#define RTE_MAXQSIZE_c5d478a01163f838 1U

/******************************************************************************/
/*                    Macros for Asynchronous Mode Switch                     */
/******************************************************************************/
#define ONEXIT 0U
#define ONTRANSITION 1U
#define ONENTRY 2U

/******************************************************************************/
/*                        Initialization Flag Indices                         */
/******************************************************************************/
/* Enum for SchM and Rte initialization */
#define RTE_SCHM_INIT                                                         0U

/* To start the periodic events for BSW module */
#define RTE_SCHM_START                                                        1U

/* To start the BSW module */
#define RTE_SCHM_STARTTIMING                                                  2U

/* To start the periodic events of Rte module */
#define RTE_START                                                             3U
/******************************************************************************/
/*                    Macros for RTE Timing Event periods                     */
/******************************************************************************/
#define RTE_PERIOD_SWC_DiagnosticMonitor_DiagnosticMonitor_TimingEvent_DiagnosticMonitor 1U

#define RTE_PERIOD_Os_Master_Os_MeasureCPULoad_Os_TE_10ms_Master 1U

#define RTE_PERIOD_SWC_WdgMTest_RE_WdgMTest_TE_RE_WdgMTest 1U

#define RTE_PERIOD_SWC_AppMode_AppMode_Test_TE_AppMode_Test 1U

/******************************************************************************/
/*                   Macros for SchM Timing Event periods                     */
/******************************************************************************/
#define RTE_PERIOD_BswM_BswSE_BswM_MainFunction_BswTE_BswM_MainFunction 1U

#define RTE_PERIOD_CanCM_BswSE_CanCM_MainFunction_BswTE_CanCM_MainFunction 1U

#define RTE_PERIOD_CanNm_BswSE_CanNm_MainFunction_BswSE_CanNm_MainFunction 1U

#define RTE_PERIOD_CanSM_BswSE_CanSM_MainFunction_BswTE_CanSM_MainFunction 2U

#define RTE_PERIOD_CanTp_BswSE_CanTp_MainFunction_BswTE_CanTp_MainFunction 1U

#define RTE_PERIOD_CanTrcv_BswSE_CanTrcv_MainFunction_BswTE_CanTrcv_MainFunction 1U

#define RTE_PERIOD_ComM_BswSE_ComM_MainFunction_ComMChannel_FD_CAN1_BswTE_ComM_MainFunction_ComMChannel_FD_CAN1 1U

#define RTE_PERIOD_ComM_BswSE_ComM_MainFunction_ComMChannel_LIN1_BswTE_ComM_MainFunction_ComMChannel_LIN1 1U

#define RTE_PERIOD_ComM_BswSE_ComM_MainFunction_ComMChannel_LIN2_BswTE_ComM_MainFunction_ComMChannel_LIN2 1U

#define RTE_PERIOD_Com_BswSE_Com_MainFunctionRx_BswTE_Com_MainFunctionRx 1U

#define RTE_PERIOD_Com_BswSE_Com_MainFunctionTx_BswTE_Com_MainFunctionTx 1U

#define RTE_PERIOD_Crypto_BswSE_Crypto_HaeCryptoLib_MainFunction_BswTE_Crypto_HaeCryptoLib_MainFunction 1U

#define RTE_PERIOD_Csm_BswSE_Csm_MainFunction_BswTE_Csm_MainFunction 1U

#define RTE_PERIOD_Dcm_BswSE_Dcm_MainFunction_BswTE_Dcm_MainFunction 1U

#define RTE_PERIOD_Dem_BswSE_Dem_MainFunction_BswTE_Dem_MainFunction 1U

#define RTE_PERIOD_EcuM_BswSE_EcuM_MainFunction_BswTE_EcuM_MainFunction 1U

#define RTE_PERIOD_FiM_BswSE_FiM_MainFunction_BswTE_FiM_MainFunction 1U

#define RTE_PERIOD_KeyM_BswSE_KeyM_MainBackgroundFunction_BswTE_KeyM_MainBackgroundFunction 1U

#define RTE_PERIOD_KeyM_BswSE_KeyM_MainFunction_BswTE_KeyM_MainFunction 1U

#define RTE_PERIOD_LinIf_BswSE_LinIf_MainFunction_LinIfChannel_LIN1_BswTE_LinIf_MainFunction_LinIfChannel_LIN1 1U

#define RTE_PERIOD_LinIf_BswSE_LinIf_MainFunction_LinIfChannel_LIN2_BswTE_LinIf_MainFunction_LinIfChannel_LIN2 1U

#define RTE_PERIOD_LinSM_BswSE_LinSM_MainFunction_BswTE_LinSM_MainFunction 2U

#define RTE_PERIOD_StbM_BswSE_StbM_MainFunction_BswTE_StbM_MainFunction 2U

#define RTE_PERIOD_WdgM_BswSE_WdgM_MainFunction_BswTE_WdgM_MainFunction 1U

#define RTE_PERIOD_Fota_BswSchedulableEntity_Fota_BswTimingEvent_Fota 1U

#define RTE_PERIOD_Crypto_Crypto_MainFunction_Crypto_TimingEvent_MainFunction 1U

/******************************************************************************/
/*                  Macros for Runnable Internal Identifiers                  */
/******************************************************************************/
#define RTE_RUNNABLE_ID_EcuM_ReleaseRUN 1U

#define RTE_RUNNABLE_ID_WdgM_GetGlobalStatus 2U

#define RTE_RUNNABLE_ID_EcuM_RequestReset 3U

#define RTE_RUNNABLE_ID_EcuM_GetCurrentTime 4U

#define RTE_RUNNABLE_ID_EcuM_RequestSleep 5U

#define RTE_RUNNABLE_ID_EcuM_GetLastShutdownTarget 6U

#define RTE_RUNNABLE_ID_EcuM_SelectShutdownTarget 7U

#define RTE_RUNNABLE_ID_AppMode_Test 8U

#define RTE_RUNNABLE_ID_EcuM_ReleasePOST_RUN 9U

#define RTE_RUNNABLE_ID_WdgM_GetFirstExpiredSEID 10U

#define RTE_RUNNABLE_ID_WdgM_SetMode 11U

#define RTE_RUNNABLE_ID_EcuM_GetShutdownTarget 12U

#define RTE_RUNNABLE_ID_EcuM_GetWakeupTime 13U

#define RTE_RUNNABLE_ID_EcuM_GetBootTarget 14U

#define RTE_RUNNABLE_ID_ComM_GetInhibitionStatus 15U

#define RTE_RUNNABLE_ID_EcuM_RequestRUN 16U

#define RTE_RUNNABLE_ID_DiagnosticMonitor 17U

#define RTE_RUNNABLE_ID_EcuM_RequestOff 18U

#define RTE_RUNNABLE_ID_BswM_Immediate_ComMMode_LIN1 19U

#define RTE_RUNNABLE_ID_BswM_Immediate_LinSchedule_LIN1 20U

#define RTE_RUNNABLE_ID_ComM_LimitChannelToNoComMode 21U

#define RTE_RUNNABLE_ID_Os_MeasureCPULoad 22U

#define RTE_RUNNABLE_ID_BswM_Immediate_LinSchedule_LIN2 23U

#define RTE_RUNNABLE_ID_EcuM_RequestPOST_RUN 24U

#define RTE_RUNNABLE_ID_BswM_Immediate_ComMMode_LIN2 25U

#define RTE_RUNNABLE_ID_BswM_Immediate_ComMMode_PNC32 26U

#define RTE_RUNNABLE_ID_WdgM_CheckpointReached 27U

#define RTE_RUNNABLE_ID_EcuM_SelectBootTarget 28U

#define RTE_RUNNABLE_ID_RE_WdgMTest 29U

#ifndef RTE_CHECKINITFLAG_FUNC
#define RTE_CHECKINITFLAG_FUNC
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(boolean, RTE_CODE) Rte_CheckInitFlag(uint8 FunctionType);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
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
