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
**  SRC-MODULE: Os_Arch_Interrupt.h                                           **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related Interrupt API                 **
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
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
**           31-Jan-2024    HJ.Kim       Jira    CP44-4440                    **
** 1.1.0      6-Sep-2023    HJ.Kim       Jira    CP44-1033                    ** 
**           29-Aug-2023    HJ.Kim       Jira    CP44-1712                    **
**            5-Jul-2023    HJ.Kim       Jira    CP44-2457                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace-begin CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:8.4:Not a defect:Justify with annotations> Inline functions should be implemented in header file  */
/* polyspace:begin<MISRA-C3:8.11:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:begin<MISRA-C3:9.5:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C:2.1:Not a defect:Justify with annotations> Coexistence of assembly is needed for readability  */

#ifndef OS_ARCH_INTERRUPT_H_
#define OS_ARCH_INTERRUPT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PCfg.h"
#include "Os_Arch_Regs.h"
#include "Os_Multicore.h"
#include "Os_Interrupt.h"
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
#include "Os_TimingProtection.h"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_S32K31X_ESDD
 * @{ */
/** Macro to define the lowest ISR priority value supported by the hardware
 *  \n{Ref: SWR_OS_S32K31X_003} */
#define OS_INT_MIN_PRIORITY              (15U)

 /** Macro to define Invalid index value of ISR Table
  *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_INVALID_ISR_ID               (uint16)0xFFFFu

/** @} */

typedef void  (*T_IsrFuncPtr)(void);
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL
#include "MemMap.h"
extern CONST(T_IsrFuncPtr, OS_CONST) Os_ExceptionVectorTable[NUM_ELE_VECTOR_TABLE];
#define OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_MULTICORE == STD_ON)
#define OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_CORE1_GLOBAL
#include "MemMap.h"
extern CONST(T_IsrFuncPtr, OS_CONST) Os_ExceptionVectorTableCore1[NUM_ELE_VECTOR_TABLE];
#define OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_CORE1_GLOBAL
#include "MemMap.h"
#if (OS_CORE_COUNT >= OS_THREE)
#define OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_CORE2_GLOBAL
#include "MemMap.h"
extern CONST(T_IsrFuncPtr, OS_CONST) Os_ExceptionVectorTableCore2[NUM_ELE_VECTOR_TABLE];
#define OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_CORE2_GLOBAL
#include "MemMap.h"
#if (OS_CORE_COUNT >= OS_FOUR)
#define OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_CORE3_GLOBAL
#include "MemMap.h"
extern CONST(T_IsrFuncPtr, OS_CONST) Os_ExceptionVectorTableCore3[NUM_ELE_VECTOR_TABLE];
#define OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_CORE3_GLOBAL
#include "MemMap.h"
#endif /* (OS_CORE_COUNT <= OS_FOUR) */
#endif /* (OS_CORE_COUNT <= OS_THREE) */
#endif /*(OS_MULTICORE == STD_ON)*/
#if (OS_ISR_COUNT != OS_PRE_ZERO)

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SRS_BSW_00309 */
extern CONST(Tdd_Os_ISRPriority, OS_CONST) Os_GaaISRPriority[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern CONST(Tdd_Os_ISRIndex, OS_CONST) Os_GaaISRIndex[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"
#if (OS_MULTICORE == STD_OFF)
extern CONST(uint32, OS_CONST) OS_COUNTER_ISRID;
#else
extern CONST(uint32, OS_CONST) OS_COUNTER_ISRID[];
#endif
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint16, OS_CONST) Os_GaaISRTable[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern CONST(Os_Cat1IsrPtrType, OS_CONST) Os_GaaCat1ISRTable[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#endif

#define OS_NUM_NVIC_EXTERNAL 255
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00410 */
#if (OS_RES_INT_SHARE == STD_ON)
extern FUNC(uint32, OS_CODE) Os_OriginalPriority
                         (P2CONST(Tdd_Os_Resource, AUTOMATIC, OS_CONST) LpResource);

extern FUNC(uint32, OS_CODE) Os_RaisePriority
          (P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource, uint32 LulHwPrio);
#endif /* End of if (OS_RES_INT_SHARE == STD_ON) */

extern FUNC(uint8, OS_CODE) Os_CAT2ISRHandler(uint32 LulIsrIdx, uint32 LulNestOnEntry);
extern FUNC(void, OS_CODE) Os_ExitCAT2ISRHandler(void);                            
extern FUNC(void, OS_CODE) Os_IntSetEnable(uint32 intrNum);
extern FUNC(void, OS_CODE) Os_IntSetDisable(uint32 intrNum);
extern FUNC(void, OS_CODE) Os_IntClearPend(uint32 intrNum);
extern FUNC(boolean, OS_CODE) OS_NOT_IN_CAT1(void);
extern FUNC(boolean, OS_CODE) OS_IN_CAT1(void);
extern FUNC(Os_IntStatus_T, OS_CODE) Os_IntDisableConditional(void);
extern FUNC(boolean, OS_CODE) Os_CheckISR(uint8 LulIsrIdx);
extern FUNC(void, OS_CODE) Os_SetISRPriority(void);
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00410 */
/* @Trace: SRS_BSW_00330 */
#if(OS_CAT2_ISR_COUNT != OS_ZERO)
extern FUNC(StatusType, OS_CODE) Os_EnableInterruptSource (ISRType ISRID,
                                                        boolean ClearPending);
extern FUNC(StatusType, OS_CODE) Os_DisableInterruptSource (ISRType ISRID);
extern FUNC(StatusType, OS_CODE) Os_ClearPendingInterruptSource (ISRType ISRID);

OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_DISABLECURRENTCAT2ISR (ISRType IsrCAT2Id)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_CONST) LpISRPriority;
  P2CONST(Tdd_Os_ISRIndex, AUTOMATIC, OS_CONST) LpISRIndex;
  uint8 LucIsrCount;
  uint32 LulIsrNumber_Sub;
  uint32 LulIsrNumber;

  LpISRIndex = &Os_GaaISRIndex[Os_MyCore()];
  LucIsrCount = LpISRIndex->ucIsrCount;
  LpISRPriority = &Os_GaaISRPriority[LpISRIndex->ucIsrStartIdx];

  while (LucIsrCount != OS_ZERO)
  {
    if(IsrCAT2Id == LpISRPriority->ddTaskId)
    {
      /* @Trace: SafeOs_SUD_API_33705 */
      *(LpISRPriority->pICRAddress) = (LpISRPriority->usISRPriorityMask)<<4;
      LulIsrNumber_Sub = (uint32)LpISRPriority->pICRAddress;
      LulIsrNumber = (uint32)(LulIsrNumber_Sub - (OS_ARM_M_IRQ_IPR_START * sizeof(uint8)));
      Os_IntSetDisable(LulIsrNumber);
#ifdef GHS
      __asm("dsb");
      __asm("isb");
#elif __GCC__
      __asm("isb");
      __asm("dsb");
#endif
    }
    LpISRPriority++;
    LucIsrCount--;
  }
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_ENABLECURRENTCAT2ISR (ISRType IsrCAT2Id)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_CONST) LpISRPriority;
  P2CONST(Tdd_Os_ISRIndex, AUTOMATIC, OS_CONST) LpISRIndex;
  uint8 LucIsrCount;
  uint32 LulIsrNumber_Sub;
  uint32 LulIsrNumber;

  LpISRIndex = &Os_GaaISRIndex[Os_MyCore()];
  LucIsrCount = LpISRIndex->ucIsrCount;
  LpISRPriority = &Os_GaaISRPriority[LpISRIndex->ucIsrStartIdx];

  while (LucIsrCount != OS_ZERO)
  {
    if(IsrCAT2Id == LpISRPriority->ddTaskId)
    {
      /* @Trace: SafeOs_SUD_API_33705 */
      *(LpISRPriority->pICRAddress) = (LpISRPriority->usISRPriorityMask)<<4;
      LulIsrNumber_Sub = (uint32)LpISRPriority->pICRAddress;
      LulIsrNumber = (uint32)(LulIsrNumber_Sub - (OS_ARM_M_IRQ_IPR_START * sizeof(uint8)));
      Os_IntSetEnable(LulIsrNumber);
#ifdef GHS
      __asm("isb");
#elif __GCC__
      __asm("isb");
#endif
    }
    LpISRPriority++;
    LucIsrCount--;
  }
}
#else
/* Empty function for being referenced by service Os_CAT2ISRHandler */
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_DISABLECURRENTCAT2ISR (ISRType IsrCAT2Id){}
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_ENABLECURRENTCAT2ISR (ISRType IsrCAT2Id){}
#endif
/***************************************************************************//**
 * Function Name        : OS_DISABLEINTERRUPTS
 *
 * Service ID           : NA
 *
 * Description          : Disable External interrupts
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
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
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_DISABLEINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_34501 */


#ifdef GHS
	__CPS(__CPS_DISABLE, __CPS_F, __CPS_DEFAULT);
	__asm("isb");
	__asm("dsb");
#elif __GCC__
	__asm("isb");
	__asm("dsb");
#endif
}

/***************************************************************************//**
 * Function Name        : OS_ENABLEINTERRUPTS
 *
 * Service ID           : NA
 *
 * Description          : Enable External interrupts
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
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
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_ENABLEINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_34601 */
#ifdef GHS
	__CPS(__CPS_DISABLE, __CPS_F, __CPS_DEFAULT);

#elif __GCC__

#endif
}

/***************************************************************************//**
 * Function Name        : OS_DISABLE_AND_SAVE_INTERRUPTS
 *
 * Service ID           : NA
 *
 * Description          : set faultmask and return current state of faultmask
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Previous faultmask state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(Os_OldLevel_T, OS_CODE) OS_DISABLE_AND_SAVE_INTERRUPTS(void)
{
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
  //Os_OldLevel_T LddOldVal = __MRS(__FAULTMASK);
  Os_OldLevel_T LddOldVal;
	__asm("MRS %0, FAULTMASK" : "=r"(LddOldVal));
  /* @Trace: SafeOs_SUD_API_34701 */
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */

#ifdef GHS
	__CPS(__CPS_DISABLE, __CPS_F, __CPS_DEFAULT);
	__asm("isb");
#elif __GCC__
	__asm("isb");
#endif
  return LddOldVal;
}

/***************************************************************************//**
 * Function Name        : OS_RESTORE_INTERRUPTS
 *
 * Service ID           : NA
 *
 * Description          : restore faultmask state with previous value
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddOldVal
 *
 * @return              : None
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_RESTORE_INTERRUPTS(Os_OldLevel_T LddOldVal)
{
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
  /* @Trace: SafeOs_SUD_API_34801 */
  //__MSR(__FAULTMASK, LddOldVal);
  __asm("MSR FAULTMASK, %0" :: "r"(LddOldVal));
  //__asm("isb");
  __asm("isb");
}

/***************************************************************************//**
 * Function Name        : Os_IntRestore
 *
 * Service ID           : NA
 *
 * Description          : Restores a FAULTMASK with previously-saved status.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            os_p : Previously-saved interrupt status
 *
 * @return              : Previous interrupt state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_CAT2_Max_Priority
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_IntRestore(Os_IntStatus_T os_p)
{
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
  /* @Trace: SafeOs_SUD_API_34901 */
  //__MSR(__BASEPRI, os_p);
  __asm("MSR BASEPRI, %0" :: "r"(os_p));
  //__asm("isb");
  __asm("isb");
}

/***************************************************************************//**
 * Function Name        : Os_SetInterruptPriority
 *
 * Service ID           : NA
 *
 * Description          : Set priority of an interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            intval : priority of an interrupt
 *
 * @return              : Previous interrupt priority
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(Os_IntStatus_T, OS_CODE) Os_SetInterruptPriority
                                                         (Os_IntStatus_T intval)
{
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
  //Os_IntStatus_T oldval = __MRS(__BASEPRI);
  Os_IntStatus_T oldval;
	__asm("MRS %0, BASEPRI" : "=r"(oldval));
  /* @Trace: SafeOs_SUD_API_48201 */
  //__MSR(__BASEPRI, intval);
  __asm("MSR BASEPRI, %0" :: "r"(intval));
  return oldval;
}

/***************************************************************************//**
 * Function Name        : Os_IntDisable
 *
 * Service ID           : NA
 *
 * Description          : Sets the IRQPLM to Os_CAT2_Max_Priority
 *                        (to disable CAT2 ISR) and returns the previous state.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Previous interrupt state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_CAT2_Max_Priority
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(Os_IntStatus_T, OS_CODE) Os_IntDisable(void)
{
  Os_IntStatus_T intval;
  /* @Trace: SafeOs_SUD_API_48301 */
  intval = Os_SetInterruptPriority((Os_IntStatus_T)Os_CAT2_Max_Priority << OS_IPR_LSB);
  //__asm("isb");
  __asm("isb");
  return intval;
}

/***************************************************************************//**
 * Function Name        : Os_IntDisableAll
 *
 * Service ID           : NA
 *
 * Description          : Sets the BASEPRI to MAX ISR Priority value (to disable all
 *                        interrupts) and returns the previous state.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Previous interrupt state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(Os_IntStatus_T, OS_CODE) Os_IntDisableAll(void)
{
  Os_IntStatus_T intval;
  /* @Trace: SafeOs_SUD_API_48401 */
  intval = Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
  //__asm("isb");
  __asm("isb");
  return intval;
}

/***************************************************************************//**
 * Function Name        : Os_SuspendInterrupts
 *
 * Service ID           : NA
 *
 * Description          : This function is used by Os_KernSuspendInterrupts(),
 *                                                 SuspendOSInterrupts(),
 *                                                 Os_RunTask(),
 *                        "It disable at the specified level" both in the calling
 *                        context and in the current context.
 *                        No special mechanism is in place to avoid multiple
 *                        evaluations of the parameters.
 *                        However,
 *                        in practice each parameter is only used once.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non re-entrant
 *
 * @param [in]            lvl : New priority level
 *
 * @param [out]           olp : Previous priority level
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
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_SuspendInterrupts(Os_OldLevel_T* olp,
                                                         uint32 lvl)
{
  /* Get old priority level by setting highest priority */
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
  //*olp = __MRS(__BASEPRI);
  __asm("MRS %0, BASEPRI" : "=r"(*olp));
  if (*olp != 0u)
  {
    if (lvl != 0u)
    {
      if (lvl < *olp)  /* Cortex-M4, BASEPRI=0 has no effect */
      {
        /* @Trace: SafeOs_SUD_API_49001 */
        /* Set new priority level */
        (void)Os_SetInterruptPriority(lvl << OS_IPR_LSB);
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_49002 */
        /* Restore old priority level */
        (void)Os_SetInterruptPriority(*olp);
      }
    }
    else
    /* polyspace<RTE:UNR:Not a defect:Justify with annotations> Below code is verified and not a defect. */
    {
      /* maintain highest priority */
      /* @Trace: SafeOs_SUD_API_49003 */
      (void)Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
    }
  }
  else
  {
    if (lvl != 0u)
    {
      /* @Trace: SafeOs_SUD_API_49004 */
      /* Set new priority level */
      (void)Os_SetInterruptPriority(lvl << OS_IPR_LSB);
    }
    else
    /* polyspace<RTE:UNR:Not a defect:Justify with annotations> Below code is verified and not a defect. */
    {
      /* @Trace: SafeOs_SUD_API_49005 */
      (void)Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
      /* maintain highest priority */
    }
  }
  //__asm("isb");
  __asm("isb");
}

/***************************************************************************//**
 * Function Name        : Os_ResumeInterrupts
 *
 * Service ID           : NA
 *
 * Description          : This function is used by Os_KernResumeInterrupts()
 *                        It restores the old priority level both in the calling
 *                        context and in the current context.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non re-entrant
 *
 * @param [in]            olp : Previous priority level
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
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ResumeInterrupts(const Os_OldLevel_T* olp)
{
  /* @Trace: SafeOs_SUD_API_49301 */
  (void)Os_SetInterruptPriority((uint32)*(olp));
  //__asm("isb");
  __asm("isb");
}

/***************************************************************************//**
 * Function Name        : Os_GetCurPrivMode
 *
 * Service ID           : NA
 *
 * Description          : This function is called to get current privilege level
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Current privilege mode
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(Os_PrivModeType, OS_CODE) Os_GetCurPrivMode(void)
{
  Os_PrivModeType LenPrivMode = OS_PRIV_UNKNOWN;
  Os_Reg32 IPSR_val;
  Os_Reg32 CONTROL_val;
  CONST(Os_Reg32, OS_CONST) CONTROL_nPRIV_BIT = 0x1u;


  /* Get IPSR register */
  /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
  //IPSR_val = __MRS(__IPSR);
  __asm("MRS %0, IPSR" : "=r"(IPSR_val));

  if(IPSR_val == OS_ZERO)
  {
    /* Thread Mode */
    /* polyspace<MISRA-C3:D2.1:Not a defect:Justify with annotations> Green Hills provides support for the system registers used by the Cortex-M family */
    //CONTROL_val = __MRS(__CONTROL);
    __asm("MRS %0, CONTROL" : "=r"(CONTROL_val));
    if((CONTROL_val & CONTROL_nPRIV_BIT) == (Os_Reg32)OS_ONE)
    {
      /* @Trace: SafeOs_SUD_API_49401 */
      /* CONTROL.nPRIV = 1 */
      LenPrivMode = OS_PRIV_USER;
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_49402 */
      /* CONTROL.nPRIV = 0 */
      LenPrivMode = OS_PRIV_SUPERVISOR;
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_49403 */
    /* Handler Mode */
    LenPrivMode = OS_PRIV_SUPERVISOR;
  }
  return LenPrivMode;
}

/***************************************************************************//**
 * Function Name        : Os_IntDisableCat2Isr
 *
 * Service ID           : NA
 *
 * Description          : If current priority is less than Os_CAT2_Max_Priority,
 *                        sets the BASEPRI to Os_CAT2_Max_Priority
 *                        (to disable CAT2 ISR) and returns the previous state.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Previous interrupt state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_CAT2_Max_Priority
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(Os_IntStatus_T, OS_CODE) Os_IntDisableCat2Isr(void)
{
  Os_IntStatus_T intval;

  /* Get old priority level by setting highest priority */
  intval = Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
  if (intval > Os_CAT2_Max_Priority)
  {
    /* @Trace: SafeOs_SUD_API_49501 */
    (void)Os_SetInterruptPriority((Os_IntStatus_T)Os_CAT2_Max_Priority << OS_IPR_LSB);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_49502 */
    (void)Os_SetInterruptPriority(intval << OS_IPR_LSB);
  }
  /* @Trace: SafeOs_SUD_API_49503 */
  //__asm("isb");
  __asm("isb");
  return intval;
}

extern VAR(boolean, OS_VAR) Os_GblISRLock[];
extern VAR(Os_IsrLockType, OS_VAR) Os_GddISRLock[];
extern VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendAll[];
extern VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendOs[];
extern VAR(Os_IsrLockType, OS_VAR) Os_GddISR2Lock[];
extern P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) Os_GpLinkTask[];

#if(OS_SPINLOCK == STD_ON)
OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchReleaseSpinlock(SpinlockIdType SpinlockId)
{
  P2VAR(Tdd_Os_Spinlock, AUTOMATIC, OS_VAR) LpSpinlock;
  Os_SpinlockMethod LenLockMethod = LOCK_NOTHING;
  Os_OldLevel_T LddGlobalIE;
  Os_IntStatus_T is;

  #if(OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_35001 */
  /* Get curent Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace: SafeOs_SUD_API_35002 */
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  LenLockMethod = Os_GaaSpinlock[SpinlockId].enSpinMethod;

  /* @Trace: SafeOs_SUD_API_35003 */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS(); 

  /* @Trace: SafeOs_SUD_API_35004 */
  /* Take Spinlock into local variable */
  LpSpinlock = &Os_GaaSpinlock[SpinlockId];
  /* Update taskID into Spinlock structure */
  LpSpinlock->ddTaskId = OS_INVALID_VALUE;
  /* Update Spinlock id in Task structure with next Spinlock ID */
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock = LpSpinlock->ddNextSpinIndex;

  /* @Trace: SafeOs_SUD_API_35005 */
  /* Release the Spinlock */
  Os_ReleaseSpinlock(SpinlockId);

  switch (LenLockMethod)
  {
    /* Lock all Interrupt */
    case LOCK_ALL_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        if (Os_GddISRLock[OS_CORE_ID] == OS_ONE)
        {
          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          /* Process timing protection */
          /* @Trace: SafeOs_SUD_API_35006 */
          Os_StopAllLockMonitor();
          #endif
          /* @Trace: SafeOs_SUD_API_35007 */
          is = Os_GddOldSuspendAll[OS_CORE_ID];
          Os_GddISRLock[OS_CORE_ID] = OS_ZERO;
          Os_IntRestore(is);
        }
        else if (Os_GddISRLock[OS_CORE_ID] > OS_ZERO)
        {
          /* @Trace: SafeOs_SUD_API_35008 */
          Os_GddISRLock[OS_CORE_ID]--;
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_35009 */
          /* Do nothing */
        }
      }
      break;
    /* Lock CAT2 Interrupt */
    #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
    case LOCK_CAT2_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        if ((Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
              && (Os_GddISR2Lock[OS_CORE_ID] == OS_ONE))
        {
          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          /* Process timing protection */
          /* @Trace: SafeOs_SUD_API_35010 */
          Os_StopOsLockMonitor();
          #endif
          /* @Trace: SafeOs_SUD_API_35011 */
          is = Os_GddOldSuspendOs[OS_CORE_ID];
          Os_GddISR2Lock[OS_CORE_ID] = OS_ZERO;
          Os_IntRestore(is);
        }
        else if (Os_GddISR2Lock[OS_CORE_ID] > OS_ZERO)
        {
          /* @Trace: SafeOs_SUD_API_35012 */
          Os_GddISR2Lock[OS_CORE_ID]--;
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_35013 */
          /* Do nothing */
        }
      }
      break;
    #endif
    /* Lock RES_SCHEDULER */
    #if (OS_RES_SCHEDULER == STD_ON)
    case LOCK_WITH_RES_SCHEDULER:
      /* @Trace: SafeOs_SUD_API_35014 */
      /* Do Nothing */
      break;
    #endif
    /* Lock NOTHING */
    case LOCK_NOTHING:
      /* @Trace: SafeOs_SUD_API_35015 */
      /* Do Nothing */
      break;
    /* polyspace +1 RTE:UNR [No action planned:Low] "Default switch-case with no unlock methods of spinlock" */
    default:
      /* @Trace: SafeOs_SUD_API_35016 */
      /* Do Nothing */
      break;
  } /* End of switch (LenLockMethod) */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  /* @Trace: SafeOs_SUD_API_35017 */
  OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchTryToGetSpinlock(SpinlockIdType SpinlockId,
                       P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success)
{
  P2VAR(Tdd_Os_Spinlock, AUTOMATIC, OS_VAR) LpSpinlock;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  boolean LblStatus;
  boolean LblLockFlag = OS_ZERO;
  Os_SpinlockMethod LenLockMethod = LOCK_NOTHING;
  Os_OldLevel_T LddGlobalIE;
  Os_OldLevel_T is;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_35101 */
  /* Get curent Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace: SafeOs_SUD_API_35102 */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

  /* @Trace: SafeOs_SUD_API_35103 */
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  LpTask = &Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];

  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  LenLockMethod = Os_GaaSpinlock[SpinlockId].enSpinMethod;
  switch (LenLockMethod)
  {
    /* Lock all Interrupt */
    case LOCK_ALL_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        if (Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
        {
          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          /* Process timing protection */
          /* @Trace : SafeOs_SUD_API_35104 */
          Os_StartAllLockMonitor();
          #endif
          /* @Trace : SafeOs_SUD_API_35105 */
          is = (Os_OldLevel_T)Os_IntDisableAll();
          Os_GddISRLock[OS_CORE_ID] = OS_ONE;
          Os_GddOldSuspendAll[OS_CORE_ID] = is;
        }
        else if (Os_GddISRLock[OS_CORE_ID] < (Os_IsrLockType)OS_SUSPENDNESTLIMIT)
        {
          /* @Trace : SafeOs_SUD_API_35106 */
          Os_GddISRLock[OS_CORE_ID]++;
        }
        else
        {
          /* @Trace : SafeOs_SUD_API_35107 */
          /* Do nothing */
        }
      }
      break;
    /* Lock CAT2 Interrupt */
    #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
    case LOCK_CAT2_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        if ((Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
            && (Os_GddISR2Lock[OS_CORE_ID] == OS_ZERO))
        {
          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          /* Process timing protection */
          /* @Trace: SafeOs_SUD_API_35108 */
          Os_StartOsLockMonitor();
          #endif
          /* @Trace: SafeOs_SUD_API_35109 */
          is = (Os_OldLevel_T)Os_IntDisable();
          Os_GddISR2Lock[OS_CORE_ID] = OS_ONE;
          Os_GddOldSuspendOs[OS_CORE_ID] = is;
        }
        else if (Os_GddISR2Lock[OS_CORE_ID] < (Os_IsrLockType)OS_SUSPENDNESTLIMIT)
        {
          /* @Trace: SafeOs_SUD_API_35110 */
          /* No need to restore the interrupt state here - they remain blocked
          * at the expected level. */
          Os_GddISR2Lock[OS_CORE_ID]++;
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_35111 */
          /* Do nothing */
        }
      }
      break;
    #endif
    /* Lock RES_SCHEDULER */
    #if (OS_RES_SCHEDULER == STD_ON)
    case LOCK_WITH_RES_SCHEDULER:
      /* @Trace: SafeOs_SUD_API_35112 */
      break;
    #endif
    /* Lock NOTHING */
    case LOCK_NOTHING:
      /* @Trace: SafeOs_SUD_API_35113 */
      /* Do Nothing */
      break;
    /* polyspace +1 RTE:UNR [No action planned:Low] "Default switch-case with no lock methods of spinlock" */
    default:
      /* @Trace: SafeOs_SUD_API_35114 */
      /* Do Nothing */
      break;
  } /* End of switch (LenLockMethod) */

  /* @Trace: SafeOs_SUD_API_35115 */
  /* Init status of the Spinlock  */
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "*Success have been checked before using" */
  *Success = TRYTOGETSPINLOCK_NOSUCCESS;

  /* Try to get The Spinlock */
  (void)Os_TryToGetSpinlock(SpinlockId, &LblStatus);

  /* Check if Spinlock is aquired */
  if (LblStatus == OS_TRUE)
  {
    /* @Trace: SafeOs_SUD_API_35116  */
    /* Update status of the Spinlock  */
    *Success = TRYTOGETSPINLOCK_SUCCESS;
    /* Take Spinlock into local variable */
    LpSpinlock = &Os_GaaSpinlock[SpinlockId];
    /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
    /* Update TaskID into Spinlock structure */
    LpSpinlock->ddTaskId = Os_GpLinkTask[OS_CORE_ID]->ddTaskID;
    /* Update ddNextSpinIndex with Index of the previously aquired Spinlock */
    LpSpinlock->ddNextSpinIndex = LpTask->ddSpinlock;
    /* Update Spinlock ID in Task structure */
    LpTask->ddSpinlock = SpinlockId;

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace : SafeOs_SUD_API_35117 */
    OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (LblStatus == OS_TRUE) */
  else
  {
    switch (LenLockMethod)
    {
      /* Lock all Interrupt */
      case LOCK_ALL_INTERRUPTS:
        /* Check if DisableAllInterrupts() is not called */
        if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
        {
          if (Os_GddISRLock[OS_CORE_ID] == OS_ONE)
          {
            #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
            /* Process timing protection */
            /* @Trace: SafeOs_SUD_API_35118 */
            Os_StopAllLockMonitor();
            #endif
            /* @Trace: SafeOs_SUD_API_35119 */
            is = Os_GddOldSuspendAll[OS_CORE_ID];
            Os_GddISRLock[OS_CORE_ID] = OS_ZERO;
            Os_IntRestore(is);
          }
          else if (Os_GddISRLock[OS_CORE_ID] > OS_ZERO)
          {
            /* @Trace: SafeOs_SUD_API_35120 */
            Os_GddISRLock[OS_CORE_ID]--;
          }
          else
          {
            /* @Trace: SafeOs_SUD_API_35121 */
            /* Do nothing */
          }
        }
        break;
      /* Lock CAT2 Interrupt */
      #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
      case LOCK_CAT2_INTERRUPTS:
        /* Check if DisableAllInterrupts() is not called */
        if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
        {
          if ((Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
                && (Os_GddISR2Lock[OS_CORE_ID] == OS_ONE))
          {
            #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
            /* Process timing protection */
            /* @Trace : SafeOs_SUD_API_35122 */
            Os_StopOsLockMonitor();
            #endif
            /* @Trace : SafeOs_SUD_API_35123 */
            Os_GddISR2Lock[OS_CORE_ID] = OS_ZERO;
            Os_IntRestore(is);
          }
          else if (Os_GddISR2Lock[OS_CORE_ID] > OS_ZERO)
          {
            /* @Trace : SafeOs_SUD_API_35124 */
            Os_GddISR2Lock[OS_CORE_ID]--;
          }
          else
          {
            /* @Trace : SafeOs_SUD_API_35125 */
            /* Do nothing */
          }
        }
        break;
      #endif
      /* Lock RES_SCHEDULER */
      #if (OS_RES_SCHEDULER == STD_ON)
      case LOCK_WITH_RES_SCHEDULER:
        /* @Trace: SafeOs_SUD_API_35126 */
        /* Do Nothing */
        break;
      #endif
      /* Lock NOTHING */
      case LOCK_NOTHING:
        /* @Trace: SafeOs_SUD_API_35127 */
        /* Do Nothing */
        break;
      /* polyspace +1 RTE:UNR [No action planned:Low] "Default switch-case with no unlock methods of spinlock" */
      default:
        /* @Trace: SafeOs_SUD_API_35128 */
        /* Do Nothing */
        break;
    } /* End of switch (LenLockMethod) */

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace : SafeOs_SUD_API_35129 */
    OS_RESTORE_INTERRUPTS(LddGlobalIE);
  }
}
#endif /* OS_SPINLOCK == STD_ON */

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchEnableAllInterrupts(void)
{
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_35201 */
  CoreIDType OS_CORE_ID;
  #endif

  Os_OldLevel_T LddGlobalIE;
  Os_IntStatus_T is;
  /* @Trace : SafeOs_SUD_API_35202 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace : SafeOs_SUD_API_35203 */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

  /* Check if DisableAllInterrupts() is called */
  if (Os_GblISRLock[OS_CORE_ID] == OS_TRUE)
	{
	  #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
	  /* Process timing protection */
	  /* @Trace : SafeOs_SUD_API_35204 */
	  Os_StopAllLockMonitor();
	  #endif
	  /* @Trace : SafeOs_SUD_API_35205 */
	  is = Os_GddOldSuspendAll[OS_CORE_ID];
	  Os_GddISRLock[OS_CORE_ID] = OS_ZERO;
	  Os_GblISRLock[OS_CORE_ID] = OS_FALSE;
    Os_IntRestore(is);
  }
	/* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	/* @Trace : SafeOs_SUD_API_35206 */
	(void)OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchDisableAllInterrupts(void)
{
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_35301 */
  CoreIDType OS_CORE_ID;
  #endif

  Os_OldLevel_T LddGlobalIE;
  Os_OldLevel_T is;
  /* @Trace : SafeOs_SUD_API_35302 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace : SafeOs_SUD_API_35303 */
	/* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();
	/* Check if DisableAll, SuspendAll and SuspendOs are not called */
	if ((Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
	   && (Os_GddISR2Lock[OS_CORE_ID] == OS_ZERO)
	   && (Os_GblISRLock[OS_CORE_ID] == OS_FALSE))
	{
	  #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
	  /* Process timing protection */
	  /* @Trace : SafeOs_SUD_API_35304 */
	  Os_StartAllLockMonitor();
	  #endif
	  /* @Trace : SafeOs_SUD_API_35305 */
    is = (Os_OldLevel_T)Os_IntDisableAll();
	  Os_GddISRLock[OS_CORE_ID] = OS_ONE;
	  Os_GblISRLock[OS_CORE_ID] = OS_TRUE;
	  Os_GddOldSuspendAll[OS_CORE_ID] = is;
	}
	/* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	/* @Trace : SafeOs_SUD_API_35306 */
	(void)OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchResumeAllInterrupts(void)
{
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_35401 */
  CoreIDType OS_CORE_ID;
  #endif

  Os_OldLevel_T LddGlobalIE;
  Os_IntStatus_T is;
  /* @Trace : SafeOs_SUD_API_35402 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace : SafeOs_SUD_API_35403 */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

  /* Check if DisableAllInterrupts() is not called */
  if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
  {
    /* Check if SuspendAllInterrupts() is called */
    if (Os_GddISRLock[OS_CORE_ID] == OS_ONE)
    {
      #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
      /* Process timing protection */
      /* @Trace : SafeOs_SUD_API_35404 */
      Os_StopAllLockMonitor();
      #endif
      /* @Trace : SafeOs_SUD_API_35405 */
      is = Os_GddOldSuspendAll[OS_CORE_ID];
      Os_GddISRLock[OS_CORE_ID] = OS_ZERO;
      Os_IntRestore(is);
    }
    /* Check if SuspendAllInterrupts() is nested */
    else if (Os_GddISRLock[OS_CORE_ID] > 0)
    {
      /* @Trace : SafeOs_SUD_API_35406 */
      Os_GddISRLock[OS_CORE_ID]--;
    }
    else
    {
      /* @Trace : SafeOs_SUD_API_35407 */
      /* Do nothing */
    }
  }
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  /* @Trace : SafeOs_SUD_API_35408 */
  OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchSuspendAllInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_35509 */
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_35501 */
  CoreIDType OS_CORE_ID;
  #endif

  Os_OldLevel_T LddGlobalIE;
  Os_OldLevel_T is;
  /* @Trace : SafeOs_SUD_API_35502 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace : SafeOs_SUD_API_35503 */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

  /* Check if DisableAllInterrupts() is not called */
  if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
  {
    /* Check if SuspendAllInterrupts() is not called */
    if (Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
    {
      #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
      /* Process timing protection */
      /* @Trace : SafeOs_SUD_API_35504 */
      Os_StartAllLockMonitor();
      #endif
      /* @Trace : SafeOs_SUD_API_35505 */
      is = (Os_OldLevel_T)Os_IntDisableAll();
      Os_GddISRLock[OS_CORE_ID] = OS_ONE;
      Os_GddOldSuspendAll[OS_CORE_ID] = is;
    }
    else if (Os_GddISRLock[OS_CORE_ID] < (uint8)OS_SUSPENDNESTLIMIT)
    {
      /* @Trace : SafeOs_SUD_API_35506 */
      Os_GddISRLock[OS_CORE_ID]++;
    }
    else
    {
      /* @Trace : SafeOs_SUD_API_35507 */
      /* Do nothing */
    }
  } /* End of if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE) */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  /* @Trace : SafeOs_SUD_API_35508 */
  OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchResumeOSInterrupts(void)
{
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_35601 */
  CoreIDType OS_CORE_ID;
  #endif

  Os_OldLevel_T LddGlobalIE;
  Os_IntStatus_T is;

  /* Get The coreID */
  /* @Trace : SafeOs_SUD_API_35602 */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* @Trace : SafeOs_SUD_API_35603 */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();
  /* Check if DisableAllInterrupts() is not called */
  if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
  {
    /* Check if SuspendOS is called and SuspendAll is not called */
    if ((Os_GddISR2Lock[OS_CORE_ID] == OS_ONE)
        && (Os_GddISRLock[OS_CORE_ID] == OS_ZERO))
    {
      #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
      /* Process timing protection */
      /* @Trace : SafeOs_SUD_API_35604 */
      Os_StopOsLockMonitor();
      #endif
      /* @Trace : SafeOs_SUD_API_35605 */
      is = Os_GddOldSuspendOs[OS_CORE_ID];
      Os_GddISR2Lock[OS_CORE_ID] = OS_ZERO;
      Os_IntRestore(is);
    }
    /* Check if SuspendOSInterrupts() is nested */
    else if (Os_GddISR2Lock[OS_CORE_ID] > 0)
    {
      /* @Trace : SafeOs_SUD_API_35606 */
      Os_GddISR2Lock[OS_CORE_ID]--;
    }
    else
    {
      /* @Trace : SafeOs_SUD_API_35607 */
      /* Do nothing */
    }
  } /* End of if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE) */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  /* @Trace : SafeOs_SUD_API_35608 */
  OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

OS_LOCAL_INLINE FUNC(void, OS_CODE) Os_ArchSuspendOSInterrupts(void)
{
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_35701 */
  CoreIDType OS_CORE_ID;
  #endif

  Os_OldLevel_T LddGlobalIE;
  Os_OldLevel_T is;

  /* Get The coreID */
  /* @Trace : SafeOs_SUD_API_35702 */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  /* @Trace : SafeOs_SUD_API_35703 */
  LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

  /* Check if DisableAllInterrupts() is not called */
  if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
  {
    /* Check if SuspendAll and SuspendOS are not called */
    if ((Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
        && (Os_GddISR2Lock[OS_CORE_ID] == OS_ZERO))
    {
      #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
      /* Process timing protection */
      /* @Trace : SafeOs_SUD_API_35704 */
      Os_StartOsLockMonitor();
      #endif
      /* @Trace : SafeOs_SUD_API_35705 */
      is = (Os_OldLevel_T)Os_IntDisable();
      Os_GddISR2Lock[OS_CORE_ID] = OS_ONE;
      Os_GddOldSuspendOs[OS_CORE_ID] = is;
    }
    /* Check if SuspendOSInterrupts() is already called */
    else if (Os_GddISR2Lock[OS_CORE_ID] < (uint8)OS_SUSPENDNESTLIMIT)
    {
      /* @Trace : SafeOs_SUD_API_35706 */
      Os_GddISR2Lock[OS_CORE_ID]++;
    }
    else
    {
      /* @Trace : SafeOs_SUD_API_35707 */
      /* Do nothing */
    }
  } /* End of if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE) */
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  /* @Trace : SafeOs_SUD_API_35708 */
  OS_RESTORE_INTERRUPTS(LddGlobalIE);
}

#endif /* OS_ARCH_INTERRUPT_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace-end CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:8.4:Not a defect:Justify with annotations> Inline functions should be implemented in header file  */
/* polyspace:end<MISRA-C3:8.11:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:end<MISRA-C3:9.5:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C:2.1:Not a defect:Justify with annotations> Coexistence of assembly is needed for readability  */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
