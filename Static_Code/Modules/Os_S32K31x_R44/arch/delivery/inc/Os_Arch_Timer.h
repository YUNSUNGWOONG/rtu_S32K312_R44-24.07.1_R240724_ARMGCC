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
**  SRC-MODULE: Os_Arch_Timer.h                                               **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related (OS) Timer API                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:     Yes                                      **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     02-Feb-2024    HJ.Kim       Jira    CP44-4166                    **
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-2442                    ** 
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/
#ifndef OS_ARCH_TIMER_H_
#define OS_ARCH_TIMER_H_

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<MISRA-C3:2.3:Not a defect:Justify with annotations> Informative typedef used */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"
#include "Os_Arch_Regs.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_S32K31X_ESDD
 * @{ */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

extern FUNC(void, OS_CODE) Os_StartTimerHw(Os_TimerIdType timerId,
                                                             uint32 timerCount);

extern FUNC(void, OS_CODE) Os_AdjustTimerInterrupt(TickType LddNewAbsCount,
                  P2CONST(Tdd_Os_HardwareCounter, AUTOMATIC, OS_CONST) LpHwCounter);
extern FUNC(void, OS_CODE) Os_UpdateHwCounter(
                  P2CONST(Tdd_Os_HardwareCounter, AUTOMATIC, OS_CONST) LpHwCounter);
extern FUNC(void, OS_CODE) Os_StartHwCounter(TickType LddNanoSecPerTick,
                  P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter);
extern FUNC(boolean, OS_CODE) Os_CheckTimerExpired(Os_TimerIdType LddTimerId);
extern FUNC(void, OS_CODE) Os_ClearTimerIntFlag(Os_TimerIdType LddTimerId);
extern FUNC(TickType, OS_CODE) Os_GetElapsedTick(TickType LddPrevTick,
                               TickType LddCurrentTick, TickType LddMaxAllowed);
extern FUNC(uint32, OS_CODE) Os_GetElapsedTime(void);
extern FUNC(uint32, OS_CODE) Os_GetReloadTime(void);
#if (OS_TIMING_PROTECTION == STD_ON)
extern FUNC(void, OS_CODE) Os_ForceTimingCore(CoreIDType CoreID);
extern FUNC(void, OS_CODE) Os_EnableBudgetTimer(void);
extern FUNC(TickType, OS_CODE) Os_GetCurrentRTC(void);
#if ((OS_TASK_TP_EB == STD_ON) || \
     (OS_ISR_TP_EB == STD_ON) || \
     (OS_INTLOCK_TP_EB == STD_ON) || \
     (OS_ALLINTLOCK_TP_EB == STD_ON) || \
     (OS_RES_TP_EB == STD_ON))
extern FUNC(void, OS_CODE) Os_TimingBudgetIsr(void);
#endif
#endif
/* @Trace: SRS_BSW_00410 */
#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
extern FUNC(void, OS_CODE) Os_InitTimer0(void);
#endif

/** Enum for SCG asynchronous clock type
 *  Implements scg_async_clock_type_t_Class
 *  \n{Ref: SWR_OS_S32K31X_007} */
typedef enum
{
  SCG_ASYNC_CLOCK_DIV1,   /**< Clock divider 1 */
  SCG_ASYNC_CLOCK_DIV2,   /**< Clock divider 2 */
  SCG_ASYNC_CLOCK_MAX,    /**< Max value */
} scg_async_clock_type_t;

/** Enum for SCG system clock type.
 *  Implements scg_system_clock_type_t_Class
 *  \n{Ref: SWR_OS_S32K31X_007} */
typedef enum
{
  SCG_SYSTEM_CLOCK_CORE,  /**< Core clock.        */
  SCG_SYSTEM_CLOCK_BUS,   /**< BUS clock.         */
  SCG_SYSTEM_CLOCK_SLOW,  /**< System slow clock. */
  SCG_SYSTEM_CLOCK_MAX,   /**< Max value.         */
} scg_system_clock_type_t;

/** Enum for PCC clock source select
 *  Implements peripheral_clock_source_t_Class
 *  \n{Ref: SWR_OS_S32K31X_007} */
typedef enum
{
  CLK_SRC_OFF   = 0x00U,  /**<Clock is off */
  CLK_SRC_SOSC  = 0x01U,  /**<OSCCLK - System OSC Bus Clock */
  CLK_SRC_SIRC  = 0x02U,  /**<SCGIRCLK - Slow IRC Clock */
  CLK_SRC_FIRC  = 0x03U,  /**<SCGFIRCLK - Fast IRC Clock */
  CLK_SRC_SPLL  = 0x06U   /**<SCGPCLK System PLL clock */
} peripheral_clock_source_t;

/** Enum for SCG system clock source.
 *  Implements scg_system_clock_src_t_Class
 *  \n{Ref: SWR_OS_S32K31X_007} */
typedef enum
{
  SCG_SYSTEM_CLOCK_SRC_SYS_OSC = 1U,  /**< System OSC. */
  SCG_SYSTEM_CLOCK_SRC_SIRC    = 2U,  /**< Slow IRC.   */
  SCG_SYSTEM_CLOCK_SRC_FIRC    = 3U,  /**< Fast IRC.   */
  SCG_SYSTEM_CLOCK_SRC_SYS_PLL = 6U,  /**< System PLL. */
  SCG_SYSTEM_CLOCK_SRC_NONE           /**< MAX value.  */
} scg_system_clock_src_t;


/** Enum for LPTMR DRV API return status
 *  \n{Ref: SWR_OS_S32K31X_007} */
typedef enum
{
    LPTMR_DRV_SUCCESS,                  /*!< Success */
    LPTMR_DRV_WARNING_INCORRECT_TIMING, /*!< Timing might not be correct*/
    LPTMR_DRV_WARNING_EVENT_EXPIRED,    /*!< Event might be lost */
    LPTMR_DRV_FAIL_CANNOT_CONFIGURE,    /*!< Error, the timer already started */
    LPTMR_DRV_FAIL_MODE_MISMATCH,       /*!< Incorrect mode already configured*/
    LPTMR_DRV_FAIL_INVALID_CLOCK,       /*!< No clock source */
} lptmr_status_t;

/** Enum for Prescaler Selection
 *  \n{Ref: SWR_OS_S32K31X_007} */
typedef enum {
    LPTMR_PRESCALE_2                        = 0x00u, /*!< Timer mode: prescaler 2, Glitch filter mode: invalid */
    LPTMR_PRESCALE_4_GLITCHFILTER_2         = 0x01u, /*!< Timer mode: prescaler 4, Glitch filter mode: 2 clocks */
    LPTMR_PRESCALE_8_GLITCHFILTER_4         = 0x02u, /*!< Timer mode: prescaler 8, Glitch filter mode: 4 clocks */
    LPTMR_PRESCALE_16_GLITCHFILTER_8        = 0x03u, /*!< Timer mode: prescaler 16, Glitch filter mode: 8 clocks */
    LPTMR_PRESCALE_32_GLITCHFILTER_16       = 0x04u, /*!< Timer mode: prescaler 32, Glitch filter mode: 16 clocks */
    LPTMR_PRESCALE_64_GLITCHFILTER_32       = 0x05u, /*!< Timer mode: prescaler 64, Glitch filter mode: 32 clocks */
    LPTMR_PRESCALE_128_GLITCHFILTER_64      = 0x06u, /*!< Timer mode: prescaler 128, Glitch filter mode: 64 clocks */
    LPTMR_PRESCALE_256_GLITCHFILTER_128     = 0x07u, /*!< Timer mode: prescaler 256, Glitch filter mode: 128 clocks */
    LPTMR_PRESCALE_512_GLITCHFILTER_256     = 0x08u, /*!< Timer mode: prescaler 512, Glitch filter mode: 256 clocks */
    LPTMR_PRESCALE_1024_GLITCHFILTER_512    = 0x09u, /*!< Timer mode: prescaler 1024, Glitch filter mode: 512 clocks */
    LPTMR_PRESCALE_2048_GLITCHFILTER_1024   = 0x0Au, /*!< Timer mode: prescaler 2048, Glitch filter mode: 1024 clocks */
    LPTMR_PRESCALE_4096_GLITCHFILTER_2048   = 0x0Bu, /*!< Timer mode: prescaler 4096, Glitch filter mode: 2048 clocks */
    LPTMR_PRESCALE_8192_GLITCHFILTER_4096   = 0x0Cu, /*!< Timer mode: prescaler 8192, Glitch filter mode: 4096 clocks */
    LPTMR_PRESCALE_16384_GLITCHFILTER_8192  = 0x0Du, /*!< Timer mode: prescaler 16384, Glitch filter mode: 8192 clocks */
    LPTMR_PRESCALE_32768_GLITCHFILTER_16384 = 0x0Eu, /*!< Timer mode: prescaler 32768, Glitch filter mode: 16384 clocks */
    LPTMR_PRESCALE_65536_GLITCHFILTER_32768 = 0x0Fu  /*!< Timer mode: prescaler 65536, Glitch filter mode: 32768 clocks */
} lptmr_prescaler_t;

/** @} */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_ARCH_TIMER_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<MISRA-C3:2.3:Not a defect:Justify with annotations> Informative typedef used */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


