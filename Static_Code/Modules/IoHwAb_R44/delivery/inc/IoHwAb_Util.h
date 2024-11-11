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
**  SRC-MODULE: IoHwAb_Util.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : Time constant definitions for IOHWAB                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.7.0     05-Mar-2024  YongEun.Lee       #CP44-3784                        **
** 1.6.2     15-Aug-2023  KhaLN1            #CP44-2683, #CP44-2684            **
** 1.6.0     07-Jul-2023  KhaLN1            #CP44-2241                        **
** 1.4.0.1   21-Sep-2022  Manje.Woo         #CP44-859                         **
** 1.4.0     22-Aug-2022  KhaLN1            #CP44-485                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.2.0     18-Nov-2021  PhucNHM           R44-Redmine #18098                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.1     26-Feb-2020  YangJin.Kim       R40-Redmine #28531                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/
#ifndef IOHWAB_UTIL_H
#define IOHWAB_UTIL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Cfg.h"

#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#include "Reg_eSys_Stm.h"
#include "Reg_eSys_Rtc.h"
#include "Reg_eSys_SIUL.h"
#include "Reg_eSys_ADCDig.h"
#include "Reg_Macros.h"

#elif defined(IOHWAB_MCAL_ST_SPC58XCX)
#include "Reg_eSys_Stm.h"
#include "Reg_eSys_Rtc.h"
#include "Reg_eSys_SIUL.h"
#include "Reg_eSys_ADCDigv2.h"
#include "Reg_Macros.h"

#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC33X) || defined(IOHWAB_MCAL_INFINEON_TC36X) \
    || defined(IOHWAB_MCAL_INFINEON_TC37X) || defined(IOHWAB_MCAL_INFINEON_TC38X) \
    || defined(IOHWAB_MCAL_INFINEON_TC39X))
#include "Os_Arch_Regs.h"
#include "IfxPort_reg.h"
#include "IfxSrc_reg.h"

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J32XX))
#include "s6j3200_ADC12B.h"
#include "Adc_Stream.h"
#include "s6j3200_RLT.h"

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX))
#include "s6j3300_ADC12B.h"
#include "Adc_Stream.h"
#include "s6j3300_RLT.h"

#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#include "Adc_Reg_eSys_Adcdig.h"
#include "Reg_eSys_Stm.h"
#include "Reg_eSys_Rtc.h"
#include "Reg_eSys_SIUL2.h"
#include "StdRegMacros.h"

#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
    || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#include "Adc_Private.h"

#elif (defined(IOHWAB_MCAL_RENESAS_RH850U2A))
#include "Adc_Cfg.h"
#include ADC_HWIP_PBTYPES_H_FILE
#include "Adc_PBTypes.h"
#include "Adc_LLDriver.h"

#elif (defined(IOHWAB_MCAL_NXP_S32K14X))
#include "Os.h"
#include "StdRegMacros.h"
#include "Adc_Reg_eSys_Adc12bsarv2.h"

#elif (defined(IOHWAB_MCAL_NXP_S32G2X))
#include "Reg_eSys_Rtc.h"
#include "Os.h"
#include "StdRegMacros.h"

#elif(defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
#include "Adc_Data.h"
#include "Adc_Internal.h"
#include "Adc_Regs.h"

#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Multiple to convert sec to msec */
#define IOHWAB_SEC_TO_MSEC      (1000u)

/* Multiple to convert msec to usec */
#define IOHWAB_MSEC_TO_USEC     (1000u)

/* Multiple to convert sec to usec */
#define IOHWAB_SEC_TO_USEC      (1000000u)

typedef uint32	IoHwAb_DelayUsecType;
typedef uint16	IoHwAb_DelayMsecType;
typedef float32 IoHwAb_DelaySecType;

typedef uint32	IoHwAb_StmTickType;
typedef uint32	IoHwAb_GptTickType;
#if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB) || (defined(IOHWAB_MCAL_ST_SPC58XCX)))
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation */
typedef unsigned long long  IoHwAb_LongType;
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation */
#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC33X) || defined(IOHWAB_MCAL_INFINEON_TC36X) \
    || defined(IOHWAB_MCAL_INFINEON_TC37X) || defined(IOHWAB_MCAL_INFINEON_TC38X) \
    || defined(IOHWAB_MCAL_INFINEON_TC39X))
typedef uint32  IoHwAb_LongType;
#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
    || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
typedef uint8  IoHwAb_StmStatusType;
typedef uint32 IoHwAb_LongType;

#elif (defined(IOHWAB_MCAL_RENESAS_RH850U2A))
typedef uint32 IoHwAb_LongType;

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX))
typedef uint32 IoHwAb_LongType;

#endif

/*******************************************************************************
**                      Mcu Dependent Macros                                  **
*******************************************************************************/
/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
/* polyspace-begin MISRA-C3:10.7 [Justified:Low] "Validated by test cases. It works as intended." */
/* Freescale Bolero */
#if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB) || (defined(IOHWAB_MCAL_ST_SPC58XCX)))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */
/* Upper limit of STM ticks */
#define IOHWAB_STM_TICK_MAX     ((IoHwAb_StmTickType) STM_CNT_MAX_VALUE)
/* Upper limit of GPT ticks */
#define IOHWAB_GPT_TICK_MAX     ((IoHwAb_GptTickType) RTC_API_RTCC_APIVAL_MAX_VALUE)

#define IOHWAB_NOP()            do{__asm("  nop");} \
                                while(0)
#define IOHWAB_ADC_ISR_ECH      (0x00000001U)

#if (ADC_SW_MAJOR_VERSION_REG > 1)
  #define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
      (REG_READ32(ADC_ISR_REG(ADC_ADDRESS(ADC_HWUNIT_NUM)))&(IOHWAB_ADC_ISR_ECH))
  #define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
      (REG_WRITE32( ADC_ISR_REG(ADC_ADDRESS(ADC_HWUNIT_NUM)),IOHWAB_ADC_ISR_ECH))
#else
  #define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
      (REG_READ32(ADC_ISR_REG(ADC_HWUNIT_NUM))&(IOHWAB_ADC_ISR_ECH))
  #define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
      (REG_WRITE32( ADC_ISR_REG(ADC_HWUNIT_NUM),IOHWAB_ADC_ISR_ECH))
#endif

/* Bolero do not need.*/
/* #define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  IOHWAB_NOP() */

/* Infineon AURIX */
#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X))
extern uint32 Os_GulStmClock;
#define IOHWAB_STM_FREQ_HZ      (Os_GulStmClock * 1000000)
#define IOHWAB_GPT_FREQ_HZ      (24414u)  /* GTM_FIXED_CLOCK_3 : 100MHz / 2^12 */
#define IOHWAB_NOP()            __nop()
#define IOHWAB_GET_TIMESTAMP()  OS_STM0_TIM0.U
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xF0038984ul
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(((uint32)(*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<24))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<25));} \
while(0)
#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrSrn1AdcRS1(ADC_HWUNIT_NUM);}\
while(0)

/* TC38X, TC39X */
#elif (defined(IOHWAB_MCAL_INFINEON_TC33X)) || (defined(IOHWAB_MCAL_INFINEON_TC36X)) \
   || (defined(IOHWAB_MCAL_INFINEON_TC37X)) || (defined(IOHWAB_MCAL_INFINEON_TC38X)) \
   || (defined(IOHWAB_MCAL_INFINEON_TC39X))
extern uint32 Os_GulStmClock;
#define IOHWAB_STM_FREQ_HZ      (Os_GulStmClock * 1000000)
#define IOHWAB_GPT_FREQ_HZ      (24414u)  /* GTM_FIXED_CLOCK_3 : 100MHz / 2^12 */
#define IOHWAB_NOP()            __nop()
#define IOHWAB_GET_TIMESTAMP()  OS_STM0_TIM0.U
#ifndef TESTING_MODE
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xF0038670u
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(((uint32)(*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<24))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<25));}\
while(0)
#endif
#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_RS0EventInterruptHandler(ADC_HWUNIT_NUM);}\
while(0)

/* Renesas RH850F1L */
#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (8000000u) /* 8M/80 */
#define IOHWAB_GPT_FREQ_HZ      (8000000u) /* 8M/80 */

#define IOHWAB_NOP()            do{__asm("nop");}\
while(0)

#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xFFFF9014ul

/* Incase of INT sequence */
/* SG1 only for AdcReadDirect */
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
((uint32)(*(volatile uint32*)(0xfff20308ul + (0x1000ul*(ADC_HWUNIT_NUM)))&((uint32)0x0002u)))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint16*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x1186ul*(ADC_HWUNIT_NUM)))))&=( (uint16)0xEFFFu ));}\
while(0)
#define IOHWAB_ADC_CONV_PROC( ADC_HWUNIT_NUM )  do{Adc_Isr( (uint8)(ADC_HWUNIT_NUM), 0U );}\
while(0)

/* Renesas RH850F1K */
#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM)) 
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (8000000u) /* 8M/80 */
#define IOHWAB_GPT_FREQ_HZ      (8000000u) /* 8M/80 */

#define IOHWAB_NOP()            do{__asm("nop");}\
while(0)


#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xFFFEEA24ul

/* Incase of INT sequence */
/* SG1 only for AdcReadDirect */
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)((*(volatile uint32*)(0xffd6d308ul + (0x1b3000ul*(((ADC_HWUNIT_NUM)+1u)&0x0001u))))&((uint32)0x0002u))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint16*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0xc786ul*(ADC_HWUNIT_NUM)))))&=( (uint16)0xEFFFu ));}\
while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_Isr( (uint8)(ADC_HWUNIT_NUM), 0U );}\
while(0)

/* Renesas RH850U2A */
#elif (defined(IOHWAB_MCAL_RENESAS_RH850U2A)) 
#define IOHWAB_STM_FREQ_HZ      (80000000u) /* 80M */
#define IOHWAB_GPT_FREQ_HZ      (10000000u) /* 80M/8 */

#define IOHWAB_NOP()            do{__asm("nop");}\
while(0)

/* EIC227 : SG0 end interrupt control*/
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xFFF801C6ul

/* Incase of INT sequence */
/* SG0 only for AdcReadDirect */
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)((*(volatile uint16*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0xCul*(ADC_HWUNIT_NUM))))&(0x1000u))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint16*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0xCul*(ADC_HWUNIT_NUM)))))&=( (uint16)0xEFFFu ));}\
while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_Isr( (uint8)(ADC_HWUNIT_NUM), (uint8)(ADC_HWUNIT_NUM) );}\
while(0)


/* Cypress S6J3200 */
#elif (defined(IOHWAB_MCAL_CYPRESS_S6J32XX))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xB48C0300UL /* ADC12B0_CDONEIRQ0 */

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)( (*(volatile uint32*)(0xB48C0300UL)) + (*(volatile uint32*)(0xB48C0304UL)) )
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) do{}\
while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrGroupConversionFinished(ADC_HWUNIT_NUM);}\
while(0)



/* Cypress S6J3300 */
#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_NOP()            
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xB48C0300UL /* ADC12B0_CDONEIRQ0 */

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)( (*(volatile uint32*)(0xB48C0300UL)) + (*(volatile uint32*)(0xB48C0304UL)) )
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) do{}\
while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrGroupConversionFinished(ADC_HWUNIT_NUM);}\
while(0)

/* Freescale MPC574XR */
#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) 
#define IOHWAB_GPT_FREQ_HZ      (1000000u) 

#define IOHWAB_NOP()            do{__asm("  nop");}\
while(0)
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
        (REG_READ32(ADCDIG_ISR_REG_ADDR32(ADC_HWUNIT_NUM))&(ADCDIG_ISR_END_CHAIN_NORM_CLEAN_U32))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
        (REG_WRITE32( ADCDIG_ISR_REG_ADDR32(ADC_HWUNIT_NUM),ADCDIG_ISR_END_CHANNEL_NORM_CONV_U32))

#elif (defined(IOHWAB_MCAL_NXP_S32K14X))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */
/* Upper limit of STM ticks */
#define IOHWAB_STM_TICK_MAX     ((IoHwAb_StmTickType) STM_CNT_MAX_VALUE)
/* Upper limit of GPT ticks */
#define IOHWAB_GPT_TICK_MAX     ((IoHwAb_GptTickType) RTC_API_RTCC_APIVAL_MAX_VALUE)

#define IOHWAB_NOP()            do { \
                                  __asm("  nop"); \
                                }while(0)
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM, ADC_GROUP_LENGH)  (REG_READ32(ADC12BSARV2_SC1_REG_ADDR32((ADC_HWUNIT_NUM), (uint32)ADC_GROUP_LENGH)) & (0x00000080UL))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) ((*(volatile uint32*)((ADC12BSARV2_SC1_REG_ADDR32((ADC_HWUNIT_NUM), (uint32)0)))) &= (0xFFFFFFFFUL - 0xC0UL) )

/* NXP S32G2X */
#elif (defined(IOHWAB_MCAL_NXP_S32G2X))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */
/* Upper limit of STM ticks */
#define IOHWAB_STM_TICK_MAX     ((IoHwAb_StmTickType) STM_CNT_MAX_VALUE_U32)
/* Upper limit of GPT ticks */
#define IOHWAB_GPT_TICK_MAX     ((IoHwAb_GptTickType) RTC_API_RTCC_APIVAL_MAX_VALUE_U32)

#define IOHWAB_NOP()            do { \
                                  __asm("  nop"); \
                                }while(0)
#ifndef TESTING_MODE
#define IOHWAB_ADC_BASE         (0x401F8000u)
#define IOHWAB_ADC_ISR_OFFSET   (0x00000010u)
#define IOHWAB_ADC_ISR_ADDRESS  (IOHWAB_ADC_BASE + IOHWAB_ADC_ISR_OFFSET)
#define IOHWAB_ADC_HWUNIT_OFFSET (0x000F0000u)

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) (((uint32)(*(volatile uint32*)((IOHWAB_ADC_ISR_ADDRESS) + (IOHWAB_ADC_HWUNIT_OFFSET*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<0))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) do { \
                                                  (((*(volatile uint32*)(IOHWAB_ADC_ISR_ADDRESS + (IOHWAB_ADC_HWUNIT_OFFSET*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<0)); \
                                                }while(0)
#endif

/* NXP S32K31X */
#elif ((defined(IOHWAB_MCAL_NXP_S32K31X)) || (defined(IOHWAB_MCAL_NXP_S32K31X_3_0_0_P01_HF01)))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_NOP()            do { \
                                  __asm("  nop"); \
                                }while(0)

#ifndef TESTING_MODE
#define IOHWAB_ADC_BASE         (0x400A0000u)
#define IOHWAB_ADC_ISR_OFFSET   (0x00000010u)
#define IOHWAB_ADC_ISR_ADDRESS  (IOHWAB_ADC_BASE + IOHWAB_ADC_ISR_OFFSET)
#define IOHWAB_ADC_HWUNIT_OFFSET (0x00004000u)

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) (((uint32)(*(volatile uint32*)((IOHWAB_ADC_ISR_ADDRESS) + (IOHWAB_ADC_HWUNIT_OFFSET*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<0))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM)
#endif

/* Cypress CYTXXX */
#elif (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrGroupConversionFinished(ADC_HWUNIT_NUM);}\
while(0)

#define IOHWAB_ADC_CONV_COMPLETED(IOHWAB_ADC_BASE_ADDRESS) ((uint32)( (*(volatile uint32*)((IOHWAB_ADC_BASE_ADDRESS) + 0x10UL)) ))

#endif

/*******************************************************************************
**                      Upper limit ticks                                     **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
/* Upper limit of GPT time in sec */
#define IOHWAB_GPT_DELAY_MAX_SEC \
    ((IoHwAb_DelaySecType) IOHWAB_GPT_TICK_MAX / IOHWAB_GPT_FREQ_HZ)
#endif


/*******************************************************************************
**                      Convert STM ticks to time                             **
*******************************************************************************/
/* Convert STM ticks to time in sec */
#define IOHWAB_STM_TICK_TO_SEC(tick) \
    (((IoHwAb_DelaySecType) (tick)) / IOHWAB_STM_FREQ_HZ)

/* Convert STM ticks to time in msec */
#define IOHWAB_STM_TICK_TO_MSEC(tick) \
    ((IoHwAb_DelayMsecType) ((((IoHwAb_LongType)(tick))*IOHWAB_SEC_TO_MSEC) / IOHWAB_STM_FREQ_HZ))

/* Convert STM ticks to time in usec */
#define IOHWAB_STM_TICK_TO_USEC(tick) \
    ((IoHwAb_DelayUsecType) ((((uint32)(tick))*IOHWAB_SEC_TO_USEC) / IOHWAB_STM_FREQ_HZ))


/*******************************************************************************
**                      Convert time to STM ticks                             **
*******************************************************************************/
/* Convert Time in sec to STM ticks */
#define IOHWAB_SEC_TO_STM_TICK(time) \
    ((IoHwAb_StmTickType) ((time) * IOHWAB_STM_FREQ_HZ))

/* Convert Time in msec to STM ticks */
#define IOHWAB_MSEC_TO_STM_TICK(time) \
    ((IoHwAb_StmTickType) (((IoHwAb_LongType)(time) * IOHWAB_STM_FREQ_HZ) / IOHWAB_SEC_TO_MSEC))

/* Convert Time in usec to STM ticks */
#define IOHWAB_USEC_TO_STM_TICK(time) \
    ((IoHwAb_StmTickType) (((IoHwAb_LongType)(time) * IOHWAB_STM_FREQ_HZ) / IOHWAB_SEC_TO_USEC))


/*******************************************************************************
**                      Convert GPT ticks to time                             **
*******************************************************************************/
/* Convert GPT ticks to time in sec */
#define IOHWAB_GPT_TICK_TO_SEC(tick) \
    ((IoHwAb_DelaySecType) (tick) / IOHWAB_GPT_FREQ_HZ)

/* Convert GPT ticks to time in msec */
#define IOHWAB_GPT_TICK_TO_MSEC(tick) \
    ((IoHwAb_DelayMsecType) (((IoHwAb_LongType)(tick)*IOHWAB_SEC_TO_MSEC) / IOHWAB_GPT_FREQ_HZ))

/* Convert GPT ticks to time in usec */
#define IOHWAB_GPT_TICK_TO_USEC(tick) \
    ((IoHwAb_DelayUsecType) (((IoHwAb_LongType)(tick)*IOHWAB_SEC_TO_USEC) / IOHWAB_GPT_FREQ_HZ))


/*******************************************************************************
**                      Convert time to GPT ticks                             **
*******************************************************************************/
/* Convert Time in sec to GPT ticks */
#define IOHWAB_SEC_TO_GPT_TICK(time) \
    ((IoHwAb_GptTickType) ((time) * IOHWAB_GPT_FREQ_HZ))
    
/* Convert Time in msec to GPT ticks */
#define IOHWAB_MSEC_TO_GPT_TICK(time) \
    ((IoHwAb_GptTickType) (((IoHwAb_LongType)(time) * IOHWAB_GPT_FREQ_HZ) / IOHWAB_SEC_TO_MSEC))

/* Convert Time in usec to GPT ticks */
#define IOHWAB_USEC_TO_GPT_TICK(time) \
    ((IoHwAb_GptTickType) (((IoHwAb_LongType)(time) * IOHWAB_GPT_FREQ_HZ) / IOHWAB_SEC_TO_USEC))


/*******************************************************************************
**                      Convert between GPT ans STM ticks                     **
*******************************************************************************/
/* Convert STM ticks to GPT ticks */
#define IOHWAB_STM_TICK_TO_GPT_TICK(tick) \
    ((IoHwAb_GptTickType) (((IoHwAb_LongType)(tick) * IOHWAB_GPT_FREQ_HZ) / IOHWAB_STM_FREQ_HZ))

/* Convert GPT ticks to STM ticks */
#define IOHWAB_GPT_TICK_TO_STM_TICK(tick) \
    ((IoHwAb_StmTickType) (((IoHwAb_LongType)(tick) * IOHWAB_STM_FREQ_HZ) / IOHWAB_GPT_FREQ_HZ))


/*******************************************************************************
**                      Current STM Clock in ticks or time                    **
*******************************************************************************/
/* Current STM Clock in ticks */
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_STM_BASE_ADDRESS         (0xFFF3C004UL)
#define IOHWAB_CURRENT_CLOCK_TICK()     ((IoHwAb_StmTickType)(REG_READ32((uint32)IOHWAB_STM_BASE_ADDRESS)))

#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC33X) || defined(IOHWAB_MCAL_INFINEON_TC36X) \
    || defined(IOHWAB_MCAL_INFINEON_TC37X) || defined(IOHWAB_MCAL_INFINEON_TC38X) \
    || defined(IOHWAB_MCAL_INFINEON_TC39X))
#define IOHWAB_CURRENT_CLOCK_TICK()     ((IoHwAb_StmTickType) IOHWAB_GET_TIMESTAMP())

#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#define IOHWAB_CURRENT_CLOCK_TICK()     ((IoHwAb_StmTickType) STM_GET_COUNTER())

#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413))
#define IOHWAB_CURRENT_CLOCK_TICK()   ((IoHwAb_StmTickType)(*(volatile uint32*)(0xFFEC0004ul))) 

#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#define IOHWAB_CURRENT_CLOCK_TICK()   ((IoHwAb_StmTickType)(*(volatile uint32*)(0xFFD70004ul))) 

#elif (defined(IOHWAB_MCAL_RENESAS_RH850U2A))
/* OSTM0 counter register */
#define IOHWAB_CURRENT_CLOCK_TICK()   ((IoHwAb_StmTickType)(*(volatile uint32*)(0xFFBF0004ul))) 

#elif (defined(IOHWAB_MCAL_ST_SPC58XCX))
  #if (REG_ESYS_STM_SW_MAJOR_VERSION > 1)
    #define IOHWAB_CURRENT_CLOCK_TICK()   STM_CNT(0xF4068000UL)
  #else
    #define IOHWAB_CURRENT_CLOCK_TICK()   STM_CNT(0)
  #endif

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J32XX))
#define IOHWAB_CURRENT_CLOCK_TICK()   RLT32_TMR

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX))
#define IOHWAB_CURRENT_CLOCK_TICK()   RLT0_TMR

#endif

#ifndef IOHWAB_MCAL_NXP_S32K14X
/* Current STM Clock in sec */
#define IOHWAB_CURRENT_CLOCK_SEC()      (IOHWAB_STM_TICK_TO_SEC(IOHWAB_CURRENT_CLOCK_TICK()))

/* Current STM Clock in msec */
#define IOHWAB_CURRENT_CLOCK_MSEC()     (IOHWAB_STM_TICK_TO_MSEC(IOHWAB_CURRENT_CLOCK_TICK()))

/* Current STM Clock in usec */
#define IOHWAB_CURRENT_CLOCK_USEC()     (IOHWAB_STM_TICK_TO_USEC(IOHWAB_CURRENT_CLOCK_TICK()))
#endif
/*******************************************************************************
**                      DIO Util                                              **
*******************************************************************************/
#if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB)||defined(IOHWAB_MCAL_ST_SPC58XCX))
#define IOHWAB_WRITE_CH(id, value)      do{REG_WRITE8(SIUL_GPDO((id)), (value));}\
while(0)

#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC33X) || defined(IOHWAB_MCAL_INFINEON_TC36X) \
    || defined(IOHWAB_MCAL_INFINEON_TC37X) || defined(IOHWAB_MCAL_INFINEON_TC38X) \
    || defined(IOHWAB_MCAL_INFINEON_TC39X))

#define IOHWAB_WRITE_CH(id, value)      do{(id) = (value);}\
while(0) 

#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#define IOHWAB_WRITE_CH(id, value)      do{REG_WRITE8(SIUL2_GPDO_ADDR8((id)), (value));}\
while(0)

#endif

/*******************************************************************************
**                      For MISRA-C                                           **
*******************************************************************************/
#define IOHWAB_UNUSED(x) do { if((uint32)(x) != (uint32)0) {}} while(0)
#define IOHWAB_UNUSED_PTR(x) do { if((x) != NULL_PTR) {}} while(0)
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation */
/* polyspace-end MISRA-C3:10.7 [Justified:Low] "Validated by test cases. It works as intended." */
#endif /* IOHWAB_UTIL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
