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
**  FILE-NAME: Os_MemmMap.h                                                   **
**                                                                            **
**  MODULE-NAME: AUTOSAR Os Module                                            **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**  Module version : 1.3.0.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_Os.arxml              
*                  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml    
*                  Static_Code\Modules\Os_S32K31x_R44\generator\Bswmdt_Os.template
*                  Static_Code\Modules\Os_S32K31x_R44\generator\Swcdt_Bsw_Os.template
* GENERATED ON: The time-stamp is removed
*/

#ifdef __cplusplus
extern "C" 
{

#endif


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Major Version */
#define OS_MEMMAP_AR_RELEASE_MAJOR_VERSION                    0x04

/* AUTOSAR Minor Version */
#define OS_MEMMAP_AR_RELEASE_MINOR_VERSION                    0x04

/* AUTOSAR Revision Version */
#define OS_MEMMAP_AR_RELEASE_REVISION_VERSION                 0x00

/* Software Major Version */
#define OS_MEMMAP_SW_MAJOR_VERSION                            0x01

/* Software Minor Version */
#define OS_MEMMAP_SW_MINOR_VERSION                            0x00


/*******************************************************************************
**                      Memory Mapping macro                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00437 */
/* @Trace: SafeOs_SUD_API_000399 */
#if defined (START_OS_MEMMAP)

#elif defined (OS_START_SEC_CODE_OsApplication0)
   #undef      OS_START_SEC_CODE_OsApplication0
   #pragma ghs section "OsApplication0_CODE"
#elif defined (OS_STOP_SEC_CODE_OsApplication0)
   #undef      OS_STOP_SEC_CODE_OsApplication0
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_Adc_Sar_0_Isr)
   #undef      OS_START_SEC_CODE_Adc_Sar_0_Isr
   #pragma ghs section "Adc_Sar_0_Isr_CODE"
#elif defined (OS_STOP_SEC_CODE_Adc_Sar_0_Isr)
   #undef      OS_STOP_SEC_CODE_Adc_Sar_0_Isr
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_Adc_Sar_1_Isr)
   #undef      OS_START_SEC_CODE_Adc_Sar_1_Isr
   #pragma ghs section "Adc_Sar_1_Isr_CODE"
#elif defined (OS_STOP_SEC_CODE_Adc_Sar_1_Isr)
   #undef      OS_STOP_SEC_CODE_Adc_Sar_1_Isr
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_CAN0_ORED_0_31_MB_IRQHandler)
   #undef      OS_START_SEC_CODE_CAN0_ORED_0_31_MB_IRQHandler
   #pragma ghs section "CAN0_ORED_0_31_MB_IRQHandler_CODE"
#elif defined (OS_STOP_SEC_CODE_CAN0_ORED_0_31_MB_IRQHandler)
   #undef      OS_STOP_SEC_CODE_CAN0_ORED_0_31_MB_IRQHandler
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_CAN0_ORED_32_63_MB_IRQHandler)
   #undef      OS_START_SEC_CODE_CAN0_ORED_32_63_MB_IRQHandler
   #pragma ghs section "CAN0_ORED_32_63_MB_IRQHandler_CODE"
#elif defined (OS_STOP_SEC_CODE_CAN0_ORED_32_63_MB_IRQHandler)
   #undef      OS_STOP_SEC_CODE_CAN0_ORED_32_63_MB_IRQHandler
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_CAN0_ORED_IRQHandler)
   #undef      OS_START_SEC_CODE_CAN0_ORED_IRQHandler
   #pragma ghs section "CAN0_ORED_IRQHandler_CODE"
#elif defined (OS_STOP_SEC_CODE_CAN0_ORED_IRQHandler)
   #undef      OS_STOP_SEC_CODE_CAN0_ORED_IRQHandler
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_EMIOS0_1_IRQ)
   #undef      OS_START_SEC_CODE_EMIOS0_1_IRQ
   #pragma ghs section "EMIOS0_1_IRQ_CODE"
#elif defined (OS_STOP_SEC_CODE_EMIOS0_1_IRQ)
   #undef      OS_STOP_SEC_CODE_EMIOS0_1_IRQ
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_EMIOS0_4_IRQ)
   #undef      OS_START_SEC_CODE_EMIOS0_4_IRQ
   #pragma ghs section "EMIOS0_4_IRQ_CODE"
#elif defined (OS_STOP_SEC_CODE_EMIOS0_4_IRQ)
   #undef      OS_STOP_SEC_CODE_EMIOS0_4_IRQ
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_EMIOS0_5_IRQ)
   #undef      OS_START_SEC_CODE_EMIOS0_5_IRQ
   #pragma ghs section "EMIOS0_5_IRQ_CODE"
#elif defined (OS_STOP_SEC_CODE_EMIOS0_5_IRQ)
   #undef      OS_STOP_SEC_CODE_EMIOS0_5_IRQ
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_EMIOS1_5_IRQ)
   #undef      OS_START_SEC_CODE_EMIOS1_5_IRQ
   #pragma ghs section "EMIOS1_5_IRQ_CODE"
#elif defined (OS_STOP_SEC_CODE_EMIOS1_5_IRQ)
   #undef      OS_STOP_SEC_CODE_EMIOS1_5_IRQ
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_LPUART0_LIN_IP_RxTx_IRQHandler)
   #undef      OS_START_SEC_CODE_LPUART0_LIN_IP_RxTx_IRQHandler
   #pragma ghs section "LPUART0_LIN_IP_RxTx_IRQHandler_CODE"
#elif defined (OS_STOP_SEC_CODE_LPUART0_LIN_IP_RxTx_IRQHandler)
   #undef      OS_STOP_SEC_CODE_LPUART0_LIN_IP_RxTx_IRQHandler
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_Mu_Ip_Mu0_OredGP_Isr)
   #undef      OS_START_SEC_CODE_Mu_Ip_Mu0_OredGP_Isr
   #pragma ghs section "Mu_Ip_Mu0_OredGP_Isr_CODE"
#elif defined (OS_STOP_SEC_CODE_Mu_Ip_Mu0_OredGP_Isr)
   #undef      OS_STOP_SEC_CODE_Mu_Ip_Mu0_OredGP_Isr
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_Mu_Ip_Mu0_OredRx_Isr)
   #undef      OS_START_SEC_CODE_Mu_Ip_Mu0_OredRx_Isr
   #pragma ghs section "Mu_Ip_Mu0_OredRx_Isr_CODE"
#elif defined (OS_STOP_SEC_CODE_Mu_Ip_Mu0_OredRx_Isr)
   #undef      OS_STOP_SEC_CODE_Mu_Ip_Mu0_OredRx_Isr
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_Mu_Ip_Mu1_OredGP_Isr)
   #undef      OS_START_SEC_CODE_Mu_Ip_Mu1_OredGP_Isr
   #pragma ghs section "Mu_Ip_Mu1_OredGP_Isr_CODE"
#elif defined (OS_STOP_SEC_CODE_Mu_Ip_Mu1_OredGP_Isr)
   #undef      OS_STOP_SEC_CODE_Mu_Ip_Mu1_OredGP_Isr
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_Mu_Ip_Mu1_OredRx_Isr)
   #undef      OS_START_SEC_CODE_Mu_Ip_Mu1_OredRx_Isr
   #pragma ghs section "Mu_Ip_Mu1_OredRx_Isr_CODE"
#elif defined (OS_STOP_SEC_CODE_Mu_Ip_Mu1_OredRx_Isr)
   #undef      OS_STOP_SEC_CODE_Mu_Ip_Mu1_OredRx_Isr
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_PIT_0_ISR)
   #undef      OS_START_SEC_CODE_PIT_0_ISR
   #pragma ghs section "PIT_0_ISR_CODE"
#elif defined (OS_STOP_SEC_CODE_PIT_0_ISR)
   #undef      OS_STOP_SEC_CODE_PIT_0_ISR
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_PIT_1_ISR)
   #undef      OS_START_SEC_CODE_PIT_1_ISR
   #pragma ghs section "PIT_1_ISR_CODE"
#elif defined (OS_STOP_SEC_CODE_PIT_1_ISR)
   #undef      OS_STOP_SEC_CODE_PIT_1_ISR
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_STM_0_ISR)
   #undef      OS_START_SEC_CODE_STM_0_ISR
   #pragma ghs section "STM_0_ISR_CODE"
#elif defined (OS_STOP_SEC_CODE_STM_0_ISR)
   #undef      OS_STOP_SEC_CODE_STM_0_ISR
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_LPUART5_LIN_IP_RxTx_IRQHandler)
   #undef      OS_START_SEC_CODE_LPUART5_LIN_IP_RxTx_IRQHandler
   #pragma ghs section "LPUART5_LIN_IP_RxTx_IRQHandler_CODE"
#elif defined (OS_STOP_SEC_CODE_LPUART5_LIN_IP_RxTx_IRQHandler)
   #undef      OS_STOP_SEC_CODE_LPUART5_LIN_IP_RxTx_IRQHandler
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_WKPU_EXT_IRQ_SINGLE_ISR)
   #undef      OS_START_SEC_CODE_WKPU_EXT_IRQ_SINGLE_ISR
   #pragma ghs section "WKPU_EXT_IRQ_SINGLE_ISR_CODE"
#elif defined (OS_STOP_SEC_CODE_WKPU_EXT_IRQ_SINGLE_ISR)
   #undef      OS_STOP_SEC_CODE_WKPU_EXT_IRQ_SINGLE_ISR
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_ASW_FG1_100ms)
   #undef      OS_START_SEC_CODE_OsTask_ASW_FG1_100ms
   #pragma ghs section "OsTask_ASW_FG1_100ms_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_ASW_FG1_100ms)
   #undef      OS_STOP_SEC_CODE_OsTask_ASW_FG1_100ms
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_ASW_FG1_10ms)
   #undef      OS_START_SEC_CODE_OsTask_ASW_FG1_10ms
   #pragma ghs section "OsTask_ASW_FG1_10ms_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_ASW_FG1_10ms)
   #undef      OS_STOP_SEC_CODE_OsTask_ASW_FG1_10ms
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_FG1_10ms)
   #undef      OS_START_SEC_CODE_OsTask_BSW_FG1_10ms
   #pragma ghs section "OsTask_BSW_FG1_10ms_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_FG1_10ms)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_FG1_10ms
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_Init)
   #undef      OS_START_SEC_CODE_OsTask_BSW_Init
   #pragma ghs section "OsTask_BSW_Init_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_Init)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_Init
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_Mem_Process)
   #undef      OS_START_SEC_CODE_OsTask_BSW_Mem_Process
   #pragma ghs section "OsTask_BSW_Mem_Process_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_Mem_Process)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_Mem_Process
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_FG1_5ms_Com)
   #undef      OS_START_SEC_CODE_OsTask_BSW_FG1_5ms_Com
   #pragma ghs section "OsTask_BSW_FG1_5ms_Com_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_FG1_5ms_Com)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_FG1_5ms_Com
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_FG3_ComMModeRequest)
   #undef      OS_START_SEC_CODE_OsTask_BSW_FG3_ComMModeRequest
   #pragma ghs section "OsTask_BSW_FG3_ComMModeRequest_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_FG3_ComMModeRequest)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_FG3_ComMModeRequest
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_BG_KeyM_Main)
   #undef      OS_START_SEC_CODE_OsTask_BSW_BG_KeyM_Main
   #pragma ghs section "OsTask_BSW_BG_KeyM_Main_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_BG_KeyM_Main)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_BG_KeyM_Main
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_BG_Crypto_Main)
   #undef      OS_START_SEC_CODE_OsTask_BSW_BG_Crypto_Main
   #pragma ghs section "OsTask_BSW_BG_Crypto_Main_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_BG_Crypto_Main)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_BG_Crypto_Main
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_FG3_BswM_Action_Main)
   #undef      OS_START_SEC_CODE_OsTask_BSW_FG3_BswM_Action_Main
   #pragma ghs section "OsTask_BSW_FG3_BswM_Action_Main_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_FG3_BswM_Action_Main)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_FG3_BswM_Action_Main
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_FG2_LinScheduleRequest)
   #undef      OS_START_SEC_CODE_OsTask_BSW_FG2_LinScheduleRequest
   #pragma ghs section "OsTask_BSW_FG2_LinScheduleRequest_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_FG2_LinScheduleRequest)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_FG2_LinScheduleRequest
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsTask_BSW_BG_Fota)
   #undef      OS_START_SEC_CODE_OsTask_BSW_BG_Fota
   #pragma ghs section "OsTask_BSW_BG_Fota_CODE"
#elif defined (OS_STOP_SEC_CODE_OsTask_BSW_BG_Fota)
   #undef      OS_STOP_SEC_CODE_OsTask_BSW_BG_Fota
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsErrorHook_OsApplication0)
   #undef      OS_START_SEC_CODE_OsErrorHook_OsApplication0
   #pragma ghs section "OsApplication0_CODE"
#elif defined (OS_STOP_SEC_CODE_OsErrorHook_OsApplication0)
   #undef      OS_STOP_SEC_CODE_OsErrorHook_OsApplication0
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsStartupHook_OsApplication0)
   #undef      OS_START_SEC_CODE_OsStartupHook_OsApplication0
   #pragma ghs section "OsApplication0_CODE"
#elif defined (OS_STOP_SEC_CODE_OsStartupHook_OsApplication0)
   #undef      OS_STOP_SEC_CODE_OsStartupHook_OsApplication0
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsShutdownHook_OsApplication0)
   #undef      OS_START_SEC_CODE_OsShutdownHook_OsApplication0
   #pragma ghs section "OsApplication0_CODE"
#elif defined (OS_STOP_SEC_CODE_OsShutdownHook_OsApplication0)
   #undef      OS_STOP_SEC_CODE_OsShutdownHook_OsApplication0
   #pragma ghs section restore
#elif defined (OS_START_SEC_CODE_OsProfilingHook_OsApplication0)
   #undef      OS_START_SEC_CODE_OsProfilingHook_OsApplication0
   #pragma ghs section "OsApplication0_CODE"
#elif defined (OS_STOP_SEC_CODE_OsProfilingHook_OsApplication0)
   #undef      OS_STOP_SEC_CODE_OsProfilingHook_OsApplication0
   #pragma ghs section restore

#elif defined (OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8)
  #undef       OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8)
  #undef       OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16)
  #undef       OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"

#elif defined (OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16)
  #undef       OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32)
  #undef       OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"

#elif defined (OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32)
  #undef       OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"

#elif defined (OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN)
  #undef       OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"

#elif defined (OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN)
  #undef       OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8)
  #undef       OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"

#elif defined (OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8)
  #undef       OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16)
  #undef       OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"

#elif defined (OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16)
  #undef       OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32)
  #undef       OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"

#elif defined (OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32)
  #undef       OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"

#elif defined (OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section

#elif defined (OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED)
  #undef       OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
  #pragma ghs section bss=".bss.OS_RAM_STACK_CORE0_CLEARED_UNSPECIFIED"

#elif defined (OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED)
  #undef       OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32)
  #undef       OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32
  #pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"

#elif defined (OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32)
  #undef       OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32
  #pragma ghs section

#elif defined (OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"

#elif defined (OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section

#elif defined (OS_START_SEC_CONST_ASIL_D_GLOBAL_32)
  #undef       OS_START_SEC_CONST_ASIL_D_GLOBAL_32
  #pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"

#elif defined (OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32)
  #undef       OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32
  #pragma ghs section

#elif defined (OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"

#elif defined (OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section

#elif defined (OS_START_SEC_CODE_ASIL_D_GLOBAL)
  #undef       OS_START_SEC_CODE_ASIL_D_GLOBAL
  #pragma ghs section text=".text.DEFAULT_CODE"
  #pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"

#elif defined (OS_STOP_SEC_CODE_ASIL_D_GLOBAL)
  #undef       OS_STOP_SEC_CODE_ASIL_D_GLOBAL
  #pragma ghs section

#elif defined (OS_API_START_SEC_CODE_ASIL_D_GLOBAL)
  #undef       OS_API_START_SEC_CODE_ASIL_D_GLOBAL
  #pragma ghs section text=".text.OS_API_CODE"

#elif defined (OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL)
  #undef       OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
  #pragma ghs section

#elif defined (OS_USERIF_START_SEC_CODE_ASIL_D_GLOBAL)
  #undef       OS_USERIF_START_SEC_CODE_ASIL_D_GLOBAL
  #pragma ghs section text=".text.OS_API_CODE"

#elif defined (OS_USERIF_STOP_SEC_CODE_ASIL_D_GLOBAL)
  #undef       OS_USERIF_STOP_SEC_CODE_ASIL_D_GLOBAL
  #pragma ghs section

#elif defined (OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL)
  #undef       OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL
  #pragma ghs section rodata=".vector.EXCEPTION"

#elif defined (OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL)
  #undef       OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL
  #pragma ghs section

#elif defined (OS_START_SEC_INTERRUPT_VECTOR_ASIL_D_GLOBAL)
  #undef       OS_START_SEC_INTERRUPT_VECTOR_ASIL_D_GLOBAL
  #pragma ghs section text=".vector.INTERRUPT"

#elif defined (OS_STOP_SEC_INTERRUPT_VECTOR_ASIL_D_GLOBAL)
  #undef       OS_STOP_SEC_INTERRUPT_VECTOR_ASIL_D_GLOBAL
  #pragma ghs section

/* OS IOC - INIT_UNSPECIFIED */
#elif defined (OS_IOC_START_SEC_VAR_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED)
  #undef       OS_IOC_START_SEC_VAR_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED
  #pragma ghs section data=".data.IOC_RAM_VAR_INIT_CORE0_UNSPECIFIED"

#elif defined (OS_IOC_STOP_SEC_VAR_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED)
  #undef       OS_IOC_STOP_SEC_VAR_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED
  #pragma ghs section

#elif defined (OS_IOC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_IOC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section data=".data.IOC_RAM_VAR_INIT_UNSPECIFIED"

#elif defined (OS_IOC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_IOC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section

/* OS IOC - NO_INIT_UNSPECIFIED */
#elif defined (OS_IOC_START_SEC_VAR_NO_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED)
  #undef       OS_IOC_START_SEC_VAR_NO_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED
  #pragma ghs section bss=".bss.IOC_RAM_VAR_NO_INIT_CORE0_UNSPECIFIED"
  #pragma noclear

#elif defined (OS_IOC_STOP_SEC_VAR_NO_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED)
  #undef       OS_IOC_STOP_SEC_VAR_NO_INIT_ASIL_D_LOCAL_CORE0_UNSPECIFIED
  #pragma clear
  #pragma ghs section

#elif defined (OS_IOC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_IOC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma ghs section bss=".bss.IOC_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma noclear

#elif defined (OS_IOC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       OS_IOC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  #pragma clear
  #pragma ghs section
#else
/*To be used if no memory section is found */
#if !defined(OS_DO_NOT_RAISE_ERROR)
    #error "Os_Memmap.h: No valid section define found"
#else
    #define SECTION_NOT_FOUND
#endif
#endif


/******************************************************************************/
/*               Compatibility between C/C++ Languages End                    */
/******************************************************************************/
#ifdef __cplusplus
}
#endif


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

