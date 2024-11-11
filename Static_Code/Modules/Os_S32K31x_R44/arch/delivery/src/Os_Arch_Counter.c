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
**  SRC-MODULE: Os_Arch_Counter.c                                             **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of HW Counter specific functionality                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:begin<RTE:NIP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:8.13:Not a defect:Justify with annotations> The pointer points const-qualified type */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00410 */
#include "Os_Arch_Timer.h"
#include "Os_PortTypes.h"
#include "Os_Ram.h"
#include "Os_Gen.h"
#include "Os_Counter.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Os_GetNextTick
 *
 * Service ID           : NA
 *
 * Description          : This function calculates the next tick from
 *                        current tick and distance.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddCurrentTick Current tick
 * @param [in]            LddDistance    Distance from current tick
 * @param [in]            LddMaxAllowed  Maximum tick value
 *
 * @return              : Next tick value
 *
 * @pre                 : LddCurrentTick <= LddMaxAllowed,
 *                        LddDistance    <= LddMaxAllowed
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
FUNC(TickType, OS_CODE) Os_GetNextTick(TickType LddCurrentTick,
               TickType LddDistance, 
               TickType LddMaxAllowed)
{
  TickType LddNextTick;
  TickType LddRange = LddMaxAllowed + (TickType)OS_ONE;

  LddNextTick = LddCurrentTick + LddDistance;
  /* Check whether the offset is greater than the maximum allowed value
   * of the underlying counter */
  if (LddNextTick > LddMaxAllowed)
  {
    /* @Trace: SafeOs_SUD_API_28301 */
    /** If value exceeds then adjust the offset */
    LddNextTick -= LddRange;
  }
  /* @Trace: SafeOs_SUD_API_28302 */
  return LddNextTick;
}

/***************************************************************************//**
 * Function             : Os_GetElapsedTick
 *
 * Service ID           : NA
 *
 * Description          : This function calculates the elapsed ticks between
 *                        previous and current tick.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddPrevTick    Previous tick
 * @param [in]            LddCurrentTick Current tick
 * @param [in]            LddMaxAllowed  Maximum tick value
 *
 * @return              : Elapsed tick value
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
FUNC(TickType, OS_CODE) Os_GetElapsedTick(TickType LddPrevTick,
            TickType LddCurrentTick, 
            TickType LddMaxAllowed)
{
  TickType LddDistance;

  if (LddCurrentTick < LddPrevTick)
  { 
    /* @Trace: SafeOs_SUD_API_28401 */
    /* Increment counter -> overflow case */
    LddDistance = (LddMaxAllowed - (LddPrevTick - LddCurrentTick)) + OS_ONE;
  }
  else {
    /* @Trace: SafeOs_SUD_API_28402 */
    LddDistance = LddCurrentTick - LddPrevTick;
  }

  return LddDistance;
}

#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
/***************************************************************************//**
 * Function             : Os_UpdateHwCounter
 *
 * Service ID           : NA
 *
 * Description          : Update counter tick
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LpHwCounter     Pointer of HW counter info
 *
 * @return              : void return but CurrentCounter is updated
 *
 * @pre                 : Os_InitTimer() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
FUNC(void, OS_CODE) Os_UpdateHwCounter(P2CONST(Tdd_Os_HardwareCounter, AUTOMATIC, 
                                                            OS_CONST) LpHwCounter)
{
  /* In case of reload timer, do nothing */
  /* polyspace<RTE: UNR : Not a defect : Justify with annotations > NULL pointer check */
  /* @Trace: SafeOs_SUD_API_28501 */
  OS_UNUSED_PTR(LpHwCounter);
}

/***************************************************************************//**
 * Function             : Os_UpdateCountInCounterISR
 *
 * Service ID           : NA
 *
 * Description          : Update counter tick. This function is called in
 *                        timer interrupt that drive the counter.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [out]           LpStaticCounter Pointer of counter to be updated
 * @param [in]            LpHwCounter     Pointer of HW counter info
 *
 * @return              : void
 *
 * @pre                 : Os_InitTimer() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
FUNC(void, OS_CODE) Os_UpdateCountInCounterISR(P2CONST(Tdd_Os_StaticCounter, 
                                           AUTOMATIC, OS_CONST) LpStaticCounter,
                   P2CONST(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter)
{
  /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
  /* @Trace: SafeOs_SUD_API_28603 */
  LpStaticCounter->pCounter->ddCurrentCount = LpHwCounter->ddNextCount;
}

/***************************************************************************//**
 * Function             : Os_ResetTimer
 *
 * Service ID           : NA
 *
 * Description          : Set next timer interrupt and clear interrupt flag
 *                        If no Alarm, set next interrupt to MAX period
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticCounter Pointer of counter that has alarm info
 * @param [in]            LpHwCounter Pointer of HW counter info
 *
 * @return              : void
 *
 * @pre                 : Os_InitTimer() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_ClearTimerIntFlag()
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ResetTimer(CONSTP2CONST(Tdd_Os_StaticCounter, AUTOMATIC, 
                                                      OS_CONST) LpStaticCounter,
              CONSTP2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter)
{
  /* Check whether next count has reached to maximum allowed value */
  if (LpHwCounter->ddNextCount == LpStaticCounter->ddMaxAllowedValue)
  {
    /* Reset the next count */
    /* @Trace: SafeOs_SUD_API_28801 */
    LpHwCounter->ddNextCount = OS_ZERO;
  }
  else
  {
    /* Increment next count */
    /* @Trace: SafeOs_SUD_API_28802 */
    LpHwCounter->ddNextCount++;
  }
  /* @Trace: SafeOs_SUD_API_28803 */
  Os_ClearTimerIntFlag(LpHwCounter->enChannelId);
} /* End of Os_ResetTimer() */

/***************************************************************************//**
 * Function             : Os_AdjustTimerInterrupt
 *
 * Service ID           : NA
 *
 * Description          : Update next timer interrupt when new Alarm is inserted
 *                        at head.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddNewAbsCount Counter Tick(Absolute) to be set next
 * @param [in]            LpHwCounter    Pointer of HW counter info
 *
 * @return              : void
 *
 * @pre                 : Os_InitTimer() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
/* @Trace: SRS_AUTRON_00010 */
#if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
FUNC(void, OS_CODE) Os_AdjustTimerInterrupt(TickType LddNewAbsCount,
                   P2CONST(Tdd_Os_HardwareCounter, AUTOMATIC, OS_CONST) LpHwCounter)
{
  /* @Trace: SafeOs_SUD_API_28901 */
  /* In case of reload timer, do nothing */
  OS_UNUSED(LddNewAbsCount);
  /* polyspace<RTE: UNR : Not a defect : Justify with annotations > NULL pointer check */
  OS_UNUSED_PTR(LpHwCounter);
}
#endif

/***************************************************************************//**
 * Function             : Os_StartHwCounter
 *
 * Service ID           : NA
 *
 * Description          : Initializes the info of hardware counter
 *                        and start timer interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddNanoSecPerTick Nanoseconds per 1 counter tick
 * @param [in, out]       LpHwCounter       Pointer of HW counter info
 *
 * @return              : void
 *
 * @pre                 : Os_InitTimer() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulStmClock
 *
 *                        Function(s) invoked    :
 *                        Os_StartTimerHw()
 *
 * {Ref: SWR_OS_S32K31X_007}
 *
 * @ingroup               OS_S32K31X_ESDD_004
 ******************************************************************************/
FUNC(void, OS_CODE) Os_StartHwCounter(TickType LddNanoSecPerTick,
                   P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter)
{
  /** TicksPerBase = SYSTICK / Counter_Ticks
   *   = (SYSTICK / sec) / (Counter_Ticks / sec)
   *   = (System_Clock) / (1 / SecondsPerTick)
   *   = System_Clock * SecondsPerTick
   *   = System_Clock * NanoSecondsPerTick / 1000000000
   *   = Os_GulStmClock * 1000000 * NanoSecondsPerTick / 1000000000
   *   = Os_GulStmClock * NanoSecondsPerTick / 1000
   *
   * The STM_Clock Max frequency is 64MHz and TickType is 4byte in MPC56xx.
   * So maximum valid value(not overflow) of LddNanoSecPerTick is 67108863.
   * Valid TicksPerBase value is an unsigned integer greater than or equal to 1.
   */
  TickType LddTicksPerBase = (Os_GulStmClock * LddNanoSecPerTick) /
                                                                OS_THOUSAND;
  TickType LddNextIntTick;

  /** If TicksPerBase is invalid, set as default value 1 */
  if (LddTicksPerBase < (TickType)OS_ONE)
  /* polyspace<RTE: UNR : Not a defect : Justify with annotations > Although it is unreachable code, fail-safety code is necessary. */
  {
    /* @Trace: SafeOs_SUD_API_29002 */
    LddTicksPerBase = (TickType)OS_ONE;
  }
  LpHwCounter->ddTicksPerBase = LddTicksPerBase;

  /** If Timer type is Reload Timer, interrupt will occur each OS Counter period */
  LddNextIntTick = LddTicksPerBase;
  LpHwCounter->ddNextCount = (TickType)OS_ONE;

  /** Start a Counter */
  /* @Trace: SafeOs_SUD_API_29003 */
  Os_StartTimerHw(LpHwCounter->enChannelId, LddNextIntTick);
}
#endif /* (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:end<RTE:NIP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:8.13:Not a defect:Justify with annotations> The pointer points const-qualified type */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
