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
**  FILE-NAME: Os_PCfg.c                                                      **
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
* INPUT FILE:      Configuration\Ecu\Ecud_Os.arxml              
*                  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml    
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Static_Code\Modules\Os_S32K31x_R44\generator\Bswmdt_Os.template
*                  Static_Code\Modules\Os_S32K31x_R44\generator\Swcdt_Bsw_Os.template
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
* @Trace: SRS_BSW_00334 SRS_BSW_00423
* GENERATED ON: The time-stamp is removed
*/
/* @Trace: SRS_BSW_00419 */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<RTE: ABS_ADDR : Not a defect : Justify with annotations> Absolute address is needed to access MCU register */
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> For implementation, uint64 is needed for stack address */
/* polyspace:begin<MISRA-C:9.2:Not a defect:Justify with annotations> This variable is not used. The code is checked manually*/
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Gen.h"
#include "Os_PortTypes.h"

#if (OS_HARDWARE_COUNTER_COUNT != 0)
#include "Os_Arch_Timer.h"
#include "Os_Arch_Regs.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Tasks/Isrs                                            **
*******************************************************************************/
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Os Category 2 Isr's */
/* @Trace: SafeOs_SUD_API_000283 */
/* @Trace: SafeOs_SUD_API_000284 */
/* @Trace: SafeOs_SUD_API_000286 */
/* @Trace: SafeOs_SUD_API_000287 */
/* @Trace: SafeOs_SUD_API_000288 */
CONST(Tdd_Os_ISRPriority, OS_CONST) Os_GaaISRPriority[] =
{     
  /* CAT Isr : 0 - Adc_Sar_0_Isr */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E4B4u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    13u
  },
  /* CAT Isr : 1 - Adc_Sar_1_Isr */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E4B5u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    14u
  },
  /* CAT Isr : 2 - CAN0_ORED_0_31_MB_IRQHandler */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E46Eu,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    15u
  },
  /* CAT Isr : 3 - CAN0_ORED_32_63_MB_IRQHandler */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E46Fu,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    16u
  },
  /* CAT Isr : 4 - CAN0_ORED_IRQHandler */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E46Du,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    17u
  },
  /* CAT Isr : 5 - EMIOS0_1_IRQ */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E43Eu,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    18u
  },
  /* CAT Isr : 6 - EMIOS0_4_IRQ */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E441u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    19u
  },
  /* CAT Isr : 7 - EMIOS0_5_IRQ */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E442u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    20u
  },
  /* CAT Isr : 8 - EMIOS1_5_IRQ */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E44Au,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    21u
  },
  /* CAT Isr : 9 - LPUART0_LIN_IP_RxTx_IRQHandler */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E48Du,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    22u
  },
  /* CAT Isr : 10 - Mu_Ip_Mu0_OredGP_Isr */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E4C2u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    23u
  },
  /* CAT Isr : 11 - Mu_Ip_Mu0_OredRx_Isr */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E4C1u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    24u
  },
  /* CAT Isr : 12 - Mu_Ip_Mu1_OredGP_Isr */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E4C5u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    25u
  },
  /* CAT Isr : 13 - Mu_Ip_Mu1_OredRx_Isr */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E4C4u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    26u
  },
  /* CAT Isr : 14 - PIT_0_ISR */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E460u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    27u
  },
  /* CAT Isr : 15 - PIT_1_ISR */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E461u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    28u
  },
  /* CAT Isr : 16 - STM_0_ISR */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E427u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    29u
  },
  /* CAT Isr : 17 - LPUART5_LIN_IP_RxTx_IRQHandler */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E492u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    30u
  },
  /* CAT Isr : 18 - WKPU_EXT_IRQ_SINGLE_ISR */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000E453u,
    
    /* usISRPrioritymask */
    (uint8)
    0x03,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    31u
  },
  /* CAT Isr : 19 - OsCounter_Main */
  {
    /* pSRCAddress */
    (uint8*)
    0xE000ED23u,
    
    /* usISRPrioritymask */
    (uint8)
    0x02,
    
    /* ucType */
    OS_CAT2_ISR,
    
    /* ddTaskId */
    32u
  }
};
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Isr Index                                             **
*******************************************************************************/
/* Os ISR Index and Count for respective cores structure */
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SafeOs_SUD_API_000289 */
/* @Trace: SafeOs_SUD_API_000290 */
/* @Trace: SafeOs_SUD_API_000291 */
CONST(Tdd_Os_ISRIndex, OS_CONST) Os_GaaISRIndex[] =
{
  /* Isr Index 0 - Core_0 */
  {
    /* ucIsrCount */
    (uint8)
    0x14u,
    /* ucIsrStartIdx */
    (uint8)
    0x00u
  }
};
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Resources                                             **
*******************************************************************************/
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SafeOs_SUD_API_000281 */
/* @Trace: SafeOs_SUD_API_000282 */
CONST(Tdd_Os_HardWareResource, OS_CONST) Os_GaaHardWareResource[] =
{
  /* Hardware Priority: 0 - DEFAULT */
  {
    /* ulHardwarePriority */
    (uint32)
    0xFFFFFFFFu
  }
};
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Counters                                              **
*******************************************************************************/
/* Os Hardware counter structure */
#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SafeOs_SUD_API_000292 */
/* @Trace: SafeOs_SUD_API_000293 */
/* @Trace: SafeOs_SUD_API_000294 */
/* @Trace: SafeOs_SUD_API_000295 */
/* @Trace: SafeOs_SUD_API_000296 */
/* @Trace: SafeOs_SUD_API_000297 */
VAR(Tdd_Os_HardwareCounter, OS_VAR) Os_GaaHardwareCounter
  [OS_HARDWARE_COUNTER_COUNT] =
{
  /* Hardware Counter : 0 - OsCounter_Main */
  {
    /* *pNextInterruptTick */
    (uint32*)
    &OS_SYST_RVR,
    
    /* *pStaticCounter */
    &Os_GaaStaticCounter[0],
    
    /* ddNextCount */
    (TickType)
    0x00000000u,
    
    /* ddTicksPerBase */
    (TickType)
    0x00000000u,
    
    /* enChannelId */
    OS_SYSTICK
  }
};
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Memory                                                **
*******************************************************************************/


/*******************************************************************************
**                      Functions                                             **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/* @Trace: SRS_Frt_00022 */
/* @Trace: SafeOs_SUD_API_000298 */
void Os_InitTimer0(void)
{
  TickType LddNanoSecPerTick;
  
  LddNanoSecPerTick = OS_TICKS2NS_OsCounter_Main(1);
  Os_StartHwCounter(LddNanoSecPerTick, &Os_GaaHardwareCounter[0]);
}
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"



/*******************************************************************************
**                      Applications                                          **
*******************************************************************************/


/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<RTE: ABS_ADDR : Not a defect : Justify with annotations> Absolute address is needed to access MCU register */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> For implementation, uint64 is needed for stack address */
/* polyspace:end<MISRA-C:9.2:Not a defect:Justify with annotations> This variable is not used. The cord is checked manually*/
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

