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
**  SRC-MODULE: Os_Arch_Timer.c                                               **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of timer specific functionality                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308
SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00410 SRS_BSW_00441 SRS_Os_11012 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.1.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           29-Jun-2023    HJ.Kim       Jira    CP44-2457                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:8.4:Not a defect:Justify with annotations> External linkage is defined in other location */
/* polyspace:begin<MISRA-C3:8.7:Not a defect:Justify with annotations> Function may be referenced in other features */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Timer.h"
#include "Os_Arch_Interrupt.h"
#include "Os_Ram.h"
#include "Os_Kernel.h"
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"
#include "Os_Error.h"
#include "Os_Arch_Context.h"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
static FUNC(void, OS_CODE) Os_InitSysTick(void);
#endif

#if (OS_TIMING_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_InitRTC(void);
static FUNC(void, OS_CODE) Os_InitSTM(void);
#endif
/***************************************************************************//**
 * Function             : Os_InitTimer
 *
 * Service ID           : NA
 *
 * Description          : This function initializes the Hardware counter
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Interrupt is disabled
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulStmClock
 *
 *                        Function(s) invoked    :
 *                         Os_InitTimer0()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
/* @Trace: SRS_Frt_00020 SRS_Frt_00032 */
FUNC(void, OS_CODE) Os_InitTimer(void)
{
  /* Init Os_GulStmClock */
  Os_GulStmClock = OS_TIMER_CLOCK;
  #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  OS_GET_CORE_ID(OS_CORE_ID);
  /* Init SysTick Timer */
  /* @Trace: SafeOs_SUD_API_29101*/
  Os_InitSysTick();
  #if (OS_MULTICORE == STD_ON)
  if (OS_CORE_ID == OS_ZERO)
  #endif
  {
    /* Init System Timer for Counter */
    /* @Trace: SafeOs_SUD_API_29102*/
    Os_InitTimer0();
  }
  #if (OS_MULTICORE == STD_ON)
  if (OS_CORE_ID == OS_ONE)
  {
    /* Init System Timer for Counter */
    Os_InitTimer1();
  }
  #if (OS_CORE_COUNT >= OS_THREE)
  if (OS_CORE_ID == OS_TWO)
  {
    /* Init System Timer for Counter */
    Os_InitTimer2();
  }
  #if (OS_CORE_COUNT >= OS_FOUR)
  if (OS_CORE_ID == OS_THREE)
  {
    /* Init System Timer for Counter */
    Os_InitTimer3();
  }
  #endif /* (OS_CORE_COUNT >= OS_FOUR) */
  #endif /* (OS_CORE_COUNT >= OS_THREE) */
  #endif /* (OS_MULTICORE == STD_ON) */ 
  #endif /* #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO) */
  #if (OS_TIMING_PROTECTION == STD_ON)
  /* @Trace: SafeOs_SUD_API_29103*/
  Os_InitRTC();
  /* @Trace: SafeOs_SUD_API_29104*/
  Os_InitSTM();
  #endif
}

/***************************************************************************//**
 * Function             : Os_GetCurrentRTC
 *
 * Service ID           : NA
 *
 * Description          : Get current RTC count
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @return              : Current RTC Tick
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K14X_006}
 *
 * @ingroup               OS_S32K14X_ESDD_005
 ******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(TickType, OS_CODE) Os_GetCurrentRTC(void)
{
  TickType LddCurrentRTC;
  /* @Trace: SafeOs_SUD_API_30201 */
  LddCurrentRTC = RTC->RTCCNT;

  return LddCurrentRTC;
}
#endif /* #if (OS_TIMING_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_GetTimeElapsedService
 *
 * Service ID           : NA
 *
 * Description          : This service is used to measure the time elapsed of
 *                        watchdog
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]           TimerType Budget Timer or Time Frame Timer
 * @param[in]           TimeElapsed Elapsed Time after measure
 *
 * @return              : TRUE - Timer is running, FALSE - Timer expired
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulBudgetTimerCount, Os_GulTFTimerCount
 *
 *                        Function(s) invoked    :
 *                        Os_CheckTimerExpired(), Os_GetElapsedTick()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(boolean, OS_CODE) Os_GetTimeElapsedService(uint8 TimerType,
                                                        TickRefType TimeElapsed)
{
  TickType LddLoadvalueTick;
  TickType LddCurrentTick;
  boolean LblReturnValue;
  boolean LblTimeExpired;

  /* @Trace:  SafeOs_SUD_API_29402 */
  LblReturnValue = OS_TRUE;
  *TimeElapsed = (TickType)OS_ZERO;

  if (TimerType == OS_BUDGET_WATCHDOG)
  {
    LblTimeExpired = Os_CheckTimerExpired(OS_STM0);
    if (LblTimeExpired == OS_TRUE)
    {
      /* @Trace:  SafeOs_SUD_API_29403 */
      LblReturnValue = OS_FALSE;
    }
    else
    {
      /* @Trace:  SafeOs_SUD_API_29404 */
      LddLoadvalueTick = Os_GulBudgetTimerCount[OS_CORE_ID];
      LddCurrentTick = OS_STM0_CNT;
      *TimeElapsed = Os_GetElapsedTick(LddLoadvalueTick, LddCurrentTick, OS_STM_CNT_MAX);
    }
  } /* End of if (TimerType == OS_BUDGET_WATCHDOG) */
  else
  {
    LblTimeExpired = Os_CheckTimerExpired(OS_RTC);
    if (LblTimeExpired == OS_TRUE)
    {
      /* @Trace:  SafeOs_SUD_API_29405 */
      LblReturnValue = OS_FALSE;
    }
    else
    {
      /* @Trace:  SafeOs_SUD_API_29406 */
      LddLoadvalueTick = Os_GulTFTimerCount[OS_CORE_ID];
      LddCurrentTick = OS_RTC_CNT;
      *TimeElapsed = Os_GetElapsedTick(LddLoadvalueTick, LddCurrentTick,
          OS_RTC_CNT_MAX);
    }
  } /* End of else */
  /* @Trace:  SafeOs_SUD_API_29407 */
  return LblReturnValue;
} /* End of Os_GetTimeElapsedService(uint8 TimerType, TickRefType TimeElapsed)
   **/
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function             : Os_InitSysTick
 *
 * Service ID           : NA
 *
 * Description          : This function initializes SysTick
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Interrupt is disabled
 *
 * @remarks             : Global Variable(s)     :
 *
 *
 *                        Function(s) invoked    :
 *
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
static FUNC(void, OS_CODE) Os_InitSysTick(void)
{
  /* @Trace: SafeOs_SUD_API_29701 */
  OS_SYST_CSR.CLKSOURCE = OS_SYST_CSR_CLKSOURCE_PROCESSOR;
}
#endif

/***************************************************************************//**
 * Function             : Os_InitRTC
 *
 * Service ID           : NA
 *
 * Description          : This function initializes RTC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Interrupt is disabled
 *
 * @remarks             : Global Variable(s)     :
 *
 *
 *                        Function(s) invoked    :
 *
 *
 * {Ref: SWR_OS_S32K14X_006}
 *
 * @ingroup               OS_S32K14X_ESDD_005
 ******************************************************************************/
/* @Trace: SRS_PSRS_00002 */
#if (OS_TIMING_PROTECTION == STD_ON)  
static FUNC(void, OS_CODE) Os_InitRTC(void)
{
  /* Init RTC for Time Frame */
  RTC->RTCSUPV = OS_RTCSUPV_SUPV(0);  /* Run in both user as well ase supervisor mode */
  /* Select clock source
   * 0 : SXOSC 32,768 kHz
   * 1 : SIRC 32kHz
   * 2 : FIRC : 48Mhz
   * 3 : FXOSC : 16Mhz
   */
  /* @Trace:  SafeOs_SUD_API_29801*/
  OS_RTCC.B.CLKSEL = (uint8)0x2u; /* Select clock source */
  OS_RTCC.B.DIV32EN = (uint8)0x0u; /* Divide by 32 */
  OS_RTCC.B.DIV512EN = (uint8)0x0u; /* Divide by 512 */
  OS_RTCC.B.FRZEN = 0x1u; /* Freeze Enable */
}
#endif /* #if (OS_TIMING_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function             : Os_InitSTM
 *
 * Service ID           : NA
 *
 * Description          : This function initializes STM
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Interrupt is disabled
 *
 * @remarks             : Global Variable(s)     :
 *
 *
 *                        Function(s) invoked    :
 *
 *
 * {Ref: SWR_OS_S32K14X_006}
 *
 * @ingroup               OS_S32K14X_ESDD_005
 ******************************************************************************/
/* @Trace: SRS_PSRS_00002 */
#if (OS_TIMING_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_InitSTM(void)
{
  VAR(uint32, OS_VAR) cr;
  /* @Trace:  SafeOs_SUD_API_28701*/
  OS_STM0_CH0_CIR = OS_STM_CIR_CIF_MASK;
  /*No Prescalar and Freeze while debug*/
  cr = OS_STM_CR_CPS(0) | OS_STM_CR_FRZ(OS_TRUE);
  OS_STM0_CR.U = cr;
  /*startValue from 0*/
  OS_STM0_CNT = 0;
}
#endif
/***************************************************************************//**
 * Function             : Os_StartTimerHw
 *
 * Service ID           : NA
 *
 * Description          : Start a timer interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            timerId    Timer interrupt channel id
 * @param [in]            timerCount Next relative Timer count for interrupt
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
/* @Trace: SRS_PSRS_00002 */
FUNC(void, OS_CODE) Os_StartTimerHw(Os_TimerIdType timerId, uint32 timerCount)
{
  switch (timerId)
  {
    case OS_SYSTICK:
      /* @Trace: SafeOs_SUD_API_29501 */
      /** 1. Program reload value */
      OS_SYST_RVR = timerCount - 1u;
      /** 2. Clear current value */
      OS_SYST_CVR = 0u;
      /** 3. Program Control and Status register */
      OS_SYST_CSR.TICKINT = STD_ON;
      OS_SYST_CSR.ENABLE = STD_ON;
      break;
    #if (OS_TIMING_PROTECTION==STD_ON)
    case OS_RTC:
      /* @Trace: SafeOs_SUD_API_29502 */
      OS_RTCC.B.CNTEN = 0u; /* Stop running counter */
      RTC->RTCVAL = timerCount; /* Program reload compare value */
      OS_RTCS.B.INV_RTC = 0u; /* Clear invalid bit */
      OS_RTCC.B.RTCIE = 1u; /* Enable ISR */
      OS_RTCC.B.CNTEN = 1u; /* Start running counter */
      break;
    case OS_STM0:
      /* @Trace: SafeOs_SUD_API_29503 */
      OS_STM0_CNT = 0u;
      /* Compare value for channel selected */
      OS_STM0_CH0_CMP = timerCount;
      /* Enable channel */
      OS_STM0_CH0_CCR = OS_STM_CCR_CEN_MASK;
      Os_IntSetEnable((uint16)OS_STM0_IRQn);
      /* Timer counter is started */
      OS_STM0_CR.U |= OS_STM_CR_TEN_MASK;
      break;
    #endif
    default:
      /* @Trace: SafeOs_SUD_API_29504 */
      /* Do nothing */
      break;
  }
}

/***************************************************************************//**
 * Function             : Os_StartRTC
 *
 * Service ID           : NA
 *
 * Description          : Start specified RTC interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K14X_006}
 *
 * @ingroup               OS_S32K14X_ESDD_005
 ******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_StartRTC(uint32 LulTimerCount)
{
  /* @Trace:  SafeOs_SUD_API_29901*/
  OS_RTCC.B.CNTEN = 0; /* Stop running counter */
  RTC->RTCVAL = LulTimerCount; /* Progrram reload compare value */
  OS_RTCS.B.INV_RTC = 0u; /* Clear invalid bit */
  OS_RTCC.B.RTCIE = 1; /* Enable ISR */
  OS_RTCC.B.CNTEN = 1; /* Start running counter */

}
#endif /* #if (OS_TIMING_PROTECTION == STD_ON) */

/*****************************************************************************
 * Function             : Os_StopTimerHw
 *
 * Service ID           : NA
 *
 * Description          : Stop timer interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            timerId    Timer interrupt channel id
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K_006}
 *
 * @ingroup               OS_S32K_ESDD_005
 ******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_StopTimerHw(Os_TimerIdType timerId)
{
  switch (timerId)
  {
    #if (OS_HARDWARE_COUNTER_COUNT != OS_ZERO)
      case OS_SYSTICK:
        /* @Trace: SafeOs_SUD_API_49701 */
        OS_SYST_CSR.TICKINT = STD_OFF;
        OS_SYST_CSR.ENABLE = STD_OFF;
      break;
    #endif
    #if (OS_TIMING_PROTECTION==STD_ON)
      case OS_RTC:
        /* @Trace: SafeOs_SUD_API_49702 */
        OS_RTCC.B.CNTEN = 0; /* Stop running counter */
        Os_IntClearPend((uint16)OS_RTC_IRQn);
      break;
      case OS_STM0:
        /* @Trace: SafeOs_SUD_API_49703 */
        /* stop Timer */
        OS_STM0_CR.U &= ~OS_STM_CR_TEN_MASK;
        OS_STM0_CH0_CIR = OS_STM_CIR_CIF_MASK;
        Os_IntClearPend((uint16)OS_STM0_IRQn);
      break;
    #endif
        default:
      /* @Trace: SafeOs_SUD_API_49704 */
      /*default case*/
      break;
  }
}
#endif
/***************************************************************************//**
 * Function             : Os_CheckTimerExpired
 *
 * Service ID           : NA
 *
 * Description          : Check Timer interrupt flag was set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddTimerId    FTM interrupt channel id
 *
 * @return              : TRUE - Timer Interrupt flag set,
 *                        FALSE - Timer Interrupt flag not set
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
FUNC(boolean, OS_CODE) Os_CheckTimerExpired(Os_TimerIdType LddTimerId)
{
  boolean LblExpired = OS_FALSE;
  uint32 LucTimerIntFlag = OS_ZERO;
  
  switch (LddTimerId)
  {
    case OS_SYSTICK:
      /* @Trace: SafeOs_SUD_API_30101 */
      LucTimerIntFlag = OS_SYST_CSR.COUNTFLAG;
      break;
    case OS_RTC:
      /* @Trace: SafeOs_SUD_API_30102 */
      LucTimerIntFlag = OS_RTCS.B.RTCF;
      break;
    case OS_STM0:
      /* @Trace: SafeOs_SUD_API_30103 */
      LucTimerIntFlag = (uint8)OS_STM0_CH0_CIR;
      break;
    default:
      /* @Trace: SafeOs_SUD_API_30104 */
      LucTimerIntFlag = OS_ZERO;
      break;
  }
  
  if(LucTimerIntFlag != OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_30105 */
    LblExpired = OS_TRUE;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_30106 */
    LblExpired = OS_FALSE;
  }

  return LblExpired;
}

/***************************************************************************//**
 * Function             : Os_ClearTimerIntFlag
 *
 * Service ID           : NA
 *
 * Description          : Clear Timer interrupt flag in register
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddTimerId    FTM interrupt channel id
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ClearTimerIntFlag(Os_TimerIdType LddTimerId)
{
  switch (LddTimerId)
  {
    case OS_SYSTICK:
      /* @Trace: SafeOs_SUD_API_30001 */
      OS_SYST_CSR.COUNTFLAG = 0u;
      break;
    #if (OS_TIMING_PROTECTION==STD_ON)
    case OS_RTC:
      /* @Trace: SafeOs_SUD_API_30002 */
      // OS_RTCS.B.ROVRF = 1u;  counter roll over isr flag 
      OS_RTCS.B.RTCF = 1u; /* RTC Instrrupt Flag */
      // OS_RTCC.B.CNTEN = 0u;  Stop running counter 
      Os_IntClearPend((uint16)OS_RTC_IRQn);
      break;
    case OS_STM0:
      /* @Trace: SafeOs_SUD_API_30003 */
      OS_STM0_CH0_CIR = OS_STM_CIR_CIF_MASK;
      Os_IntClearPend((uint16)OS_STM0_IRQn);
      break;
    #endif
    default:
      /* @Trace: SafeOs_SUD_API_30004 */
      /* Do nothing */
      break;
  }
}


/***************************************************************************//**
 * Function Name        : Os_StartTimer
 *
 * Service ID           : NA
 *
 * Description          : This service is used to start the timer based on the
 *                        channel passed
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]           TimerType Budget Timer or Time Frame Timer
 * @param[in]           LddTickValue Timer interrupt period
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulBudgetTimerCount, Os_GulTFTimerCount
 *
 *                        Function(s) invoked    :
 *                        Os_StartTimer()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_StartTimer(uint8 TimerType, TickType LddTickValue)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  /* @Trace: SafeOs_SUD_API_29201*/
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif

  if (TimerType == OS_BUDGET_WATCHDOG)
  {
    /* @Trace: SafeOs_SUD_API_29204*/
    Os_StartTimerHw(OS_STM0, LddTickValue);
    Os_GulBudgetTimerCount[OS_CORE_ID] = OS_STM0_CNT;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_29205*/
    Os_StartTimerHw(OS_RTC, LddTickValue);
    Os_GulTFTimerCount[OS_CORE_ID] = OS_RTC_CNT;
  }
} /* End of Os_StartTimer(uint8 TimerType, TickType LddTickValue) */
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_StopTimer
 *
 * Service ID           : NA
 *
 * Description          : This service is used to stop the timer based on the
 *                        channel passed
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]           TimerType Budget Timer or Time Frame Timer
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_StopFTM()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 ******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_StopTimer(uint8 TimerType)
{
  if (TimerType == OS_BUDGET_WATCHDOG)
  {
    /* @Trace: SafeOs_SUD_API_29303*/
    /* Stop the timer */
    Os_StopTimerHw(OS_STM0);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_29304*/
    /* Stop the timer */
    Os_StopTimerHw(OS_RTC);
  }
} /* End of Os_StopTimer(uint8 TimerType) */
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */


/***************************************************************************//**
 * Function Name        : Os_TimingBudgetIsr
 *
 * Service ID           : NA
 *
 * Description          : This service is used to service TPS budget interrupt
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GblTPSFlag
 *
 *                        Function(s) invoked    :
 *                        Os_ClearTimerIntFlag()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 *******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
#if ((OS_TASK_TP_EB == STD_ON) || \
     (OS_ISR_TP_EB == STD_ON) || \
     (OS_INTLOCK_TP_EB == STD_ON) || \
     (OS_ALLINTLOCK_TP_EB == STD_ON) || \
     (OS_RES_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_TimingBudgetIsr(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
    /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
  if ((Os_GddFaultyTask[OS_CORE_ID] != INVALID_TASK) &&
      (Os_GaaTask[Os_GddFaultyTask[OS_CORE_ID]].ddState == SUSPENDED))
  {
    /* @Trace: SafeOs_SUD_API_50001 */
    Os_GddFaultyTask[OS_CORE_ID] = INVALID_TASK;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_50002 */
    Os_GblTPSFlag[OS_CORE_ID] = OS_TRUE;
  }
  /* @Trace: SafeOs_SUD_API_50003 */
  Os_ClearTimerIntFlag(OS_STM0);
} /* End of Os_TimingBudgetIsr(void) */
#endif /* End of if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STN_ON) || (OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_RES_TP_EB == STD_ON)) */
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_TimeFrameIsr
 *
 * Service ID           : NA
 *
 * Description          : TPS time frame interrupt service routine
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_TimeFrameHandler(), Os_ClearTimerIntFlag()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 *******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
#if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON))
FUNC(void, OS_CODE) Os_TimeFrameIsr(void)
{
  /* @Trace: SafeOs_SUD_API_30401 */
  Os_TimeFrameHandler();
  Os_ClearTimerIntFlag(OS_RTC);
} /* End of Os_TimeFrameIsr(void) */
#endif /* ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON)) */
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_EnableBudgetTimer
 *
 * Service ID           : NA
 *
 * Description          : Check budget violation and Excute the budget handler
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *                        Interrupt should be disabled
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GblTPSFlag, Os_GucInKernel,
 *                        Os_GpStaticTask, Os_GulKernelSP, Os_GulKernelSPBase
 *
 *                        Function(s) invoked    :
 *                        Os_OsWdgHandler(), Os_DoContextSwitch()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_005
 *******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_EnableBudgetTimer(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewTaskISR;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if(OS_ISR_COUNT > OS_ZERO)
  Os_OldLevel_T LddDefaultLevel = (Os_OldLevel_T) OS_INT_MIN_PRIORITY;
  #endif
  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  uint32 LulCtrl;
  #endif

  /* @Trace: SafeOs_SUD_API_29601*/
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  if ((Os_GblTPSFlag[OS_CORE_ID] == OS_TRUE) &&
      (Os_GucNestingCAT1ISR[OS_CORE_ID] == (uint8)OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_29602*/
    Os_GblTPSFlag[OS_CORE_ID] = OS_FALSE;

    /* Jump to watchdog handler. Previous Task or ISR will be killed */
    Os_OsWdgHandler();
    Os_GddFaultyTask[OS_CORE_ID] = INVALID_TASK;
    /* Running Task or ISR was killed. Need Context switching */
    LpNewTaskISR = Os_GpStaticTask[OS_CORE_ID];
    /* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
    if (LpNewTaskISR->usType != OS_ISR2)
    {
      /* @Trace: SafeOs_SUD_API_29603*/
      Os_GusCallevelCheck[OS_CORE_ID] = (uint16)CONTEXT_SWITCHING_NONE;
      /* Discard kernel stack(stacked by ISR) */
      Os_GulKernelSP[OS_CORE_ID] = Os_GulKernelSPBase[OS_CORE_ID];

      #if(OS_ISR_COUNT > OS_ZERO)
      /* @Trace: SafeOs_SUD_API_29604*/
      /* Set lowest priority */
      Os_ResumeInterrupts(&LddDefaultLevel);
      #endif      
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_29605*/
      Os_GusCallevelCheck[OS_CORE_ID] = (uint16)OS_CONTEXT_CAT2ISR;
    }
    /* polyspace-end MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
    Os_GucInKernel[OS_CORE_ID] = (uint8)OS_ZERO;
    Os_GucSchedReq[OS_CORE_ID] = (uint8)OS_ZERO;

    if(Os_GucKillCAT2ISR[OS_CORE_ID] == (uint8)OS_ZERO)
    {
      #if (OS_APP_MEMBLK_CNT != OS_ZERO)
      /* polyspace +2 RTE:NIP [Justified:Medium] "ptr points to a valid value and code is verified manually" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
      LulCtrl = __MRS(__CONTROL);
      /* If Application is non-trusted, set privileged mode to user */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
      if (LpNewTaskISR->ddAppId < (ApplicationType)Os_Trusted_Start_Indx)
      {
        /* @Trace: SafeOs_SUD_API_37002 */
        /* CTRL.nPRIV = 1 which means Thread mode has unprivileged access */
        LulCtrl |= 0x00000001u;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_37003 */
        /* CTRL.nPRIV = 0 which means Thread mode has privileged access */
        LulCtrl &= 0xFFFFFFFEu;
      }
      __MSR(__CONTROL, LulCtrl);
      #endif
      /* @Trace: SafeOs_SUD_API_29606*/
      Os_DoContextSwitch(LpNewTaskISR->pContext);
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_29607*/
      /* Increase BASEPRI for Preventing Nesting Problem while Kill ISR */
      (void)Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
      /* Need to go to the killed ISR to solve nesting problem */
      Os_DoContextSwitch_ToCAT2();
    }
  }
}
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

#if (OS_TIMING_PROTECTION == STD_ON)
/*******************************************************************************
** Function Name        : Os_ForceTimingCore                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Trigger interrupt timing violation Call Trusted     **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_80005 SRS_Os_80015 */
FUNC(void, OS_CODE) Os_ForceTimingCore(CoreIDType CoreID)
{
  /*for unused parameter but need as argument.*/
  OS_UNUSED(CoreID);
  /* @Trace: SafeOs_SUD_API_30301 */
  /* Enable budget timer: OS565, OS564 */
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The context of external API which reference by assembly */
  Os_EnableBudgetTimer();  
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The context of external API which reference by assembly */
}
#endif

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:8.4:Not a defect:Justify with annotations> External linkage is defined in other location */
/* polyspace:end<MISRA-C3:8.7:Not a defect:Justify with annotations> Function may be referenced in other features */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
