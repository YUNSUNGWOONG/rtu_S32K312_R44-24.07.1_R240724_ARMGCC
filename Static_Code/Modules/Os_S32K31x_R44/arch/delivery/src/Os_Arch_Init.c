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
**  SRC-MODULE: Os_Arch_Init.c                                                **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of port specific functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
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
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-2205                    **
**            5-Jul-2023    HJ.Kim       Jira    CP44-2457                    **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#if (OS_MULTICORE == STD_ON)
#include "Os_Arch_Multicore.h"    /* Os Multi-core header file */
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/***************************************************************************//**
 * Function Name        : Os_PortInit
 *
 * Service ID           : NA
 *
 * Description          : This service is used to initialize Port
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
 *                        Os_GulKernelSP, Os_Task_Count, Os_CAT2_ISR_Count,
 *                        Os_Core_Count, Os_GaaStaticTask, Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        Os_GetMSP(), Os_GetMSP(), Os_SetISRPriority(), 
 *                        Os_InitTimer()
 *
 * {Ref: SWR_OS_S32K31X_009}
 *
 * @ingroup               OS_S32K31X_ESDD_001
 ******************************************************************************/
 /* @Trace: SRS_BSW_00351 */
FUNC(void, OS_CODE) OS_PORTINITIALIZE(void)
{
  #if (OS_EVENT == STD_ON)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #endif
  #if ((OS_EVENT == STD_ON) || (OS_APPLICATION == STD_ON))
  P2CONST (Tdd_Os_Stack, AUTOMATIC, OS_CONST) LpStack;
  uint32 LulCount;
  #endif
  #if (OS_APPLICATION == STD_ON)
  P2CONST(Tdd_Os_Application, AUTOMATIC, OS_CONST) LpStaticApplication;
  #endif

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  OS_GET_CORE_ID(OS_CORE_ID);
  
  #if (OS_MULTICORE == STD_ON)
  if(OS_CORE_ID == OS_ZERO)
  {
    /* Set interrupt for core0 */
    OS_IPC_REG.INTR_STRUCT[OS_IC_0_IPC_INDEX].INTR_SET.B.NOTIFY = 1u;
    /* Set interrupt for core1 */
    OS_IPC_REG.INTR_STRUCT[OS_IC_1_IPC_INDEX].INTR_SET.B.NOTIFY = 1u;

    #if (OS_CORE_COUNT >= OS_THREE)
    /* Set interrupt for core0 */
    OS_IPC_REG.INTR_STRUCT[OS_IC_2_IPC_INDEX].INTR_SET.B.NOTIFY = 1u;
    #if (OS_CORE_COUNT >= OS_FOUR)
    /* Set interrupt for core1 */
    OS_IPC_REG.INTR_STRUCT[OS_IC_3_IPC_INDEX].INTR_SET.B.NOTIFY = 1u;
    #endif /* FOUR */
    #endif /* THREE */
  }
  #endif
  
  /** Initialize Kernel stack pointer */
  Os_GulKernelSP[OS_CORE_ID] = Os_GetMSP();
  Os_GulKernelSPBase[OS_CORE_ID] = Os_GetMSP();

  /* polyspace:begin<MISRA-C3:14.3:Not a defect: justify with annotation> It is determined by configuration */
  /* polyspace<RTE: UNR : Not a defect : Justify with annotations > Value of OS_CORE_ID depends on Multi-Core */
  /* polyspace:begin<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of OS_CORE_ID depends on Multi-Core */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of OS_CORE_ID depends on Multi-Core" */
  if (OS_CORE_ID == OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_51020 */
    #if (OS_EVENT == STD_ON)
    /* @Trace: SafeOs_SUD_API_51021 */
    /** Initialize stack pattern for Extended Task stack */
    LulCount = (Os_Task_Count + Os_CAT2_ISR_Count + Os_Core_Count);
    do
    {
      /* Decrement loop count */
      LulCount--;
      /* Take a pointer to Static Task */
      LpStaticTask = &Os_GaaStaticTask[LulCount];
      /* polyspace<RTE:IDP:Not a defect:Justify with annotations> configured memory access index */
      if (LpStaticTask->usType == OS_TASK_EXTENDED)
      {/* @Trace: SafeOs_SUD_API_51022 */
        LpStack = &Os_GaaStack[LpStaticTask->ucStackIndex];
        /* Writing stack pattern at the bottom of stack area */
        /* polyspace<RTE:IDP:Not a defect:Justify with annotations> configured memory access index */
        /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
        /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "To handle the stack" */
        /* @Trace: SafeOs_SUD_API_51023 */
        *(LpStack->pStackArea) = OS_STACK_PATTERN;
        /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
      }
    } while (LulCount != (uint32)OS_ZERO);
    #endif
    /* polyspace:end<MISRA-C3:14.3:Not a defect: justify with annotation> It is determined by configuration */

    /**
     * Initialize Stack Pointer
     */
    #if(OS_APPLICATION == STD_ON)
    #if(OS_STACK_MONITORING == STD_ON)
    /* @Trace: SafeOs_SUD_API_51024 */
    /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
    /* polyspace<MISRA-C:11.4:Not a defect:Justify with annotations> This is intended to handle stack address  */
    /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
    Os_GaaRamUserStack0[0] = OS_STACK_PATTERN;
    #endif
    /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "This is intended to handle stack address" */
    /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "To handle the stack" */
    /* @Trace: SafeOs_SUD_API_51025 */
    Os_GulUserSPTop[OS_ZERO] = (uint32)&Os_GaaRamUserStack0[0];
    Os_GulUserSPBtm[OS_ZERO] = (uint32)Os_GulUserSPTop[OS_ZERO] + Os_User_Stack_Size;
    Os_GulUserSP[OS_ZERO] = Os_GulUserSPBtm[OS_ZERO];
    /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    #if (OS_MULTICORE == STD_ON)
    #if(OS_STACK_MONITORING == STD_ON)
    /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
    /* polyspace<MISRA-C:11.4:Not a defect:Justify with annotations> This is intended to handle stack address  */
    /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
    Os_GaaRamUserStack1[0] = OS_STACK_PATTERN;
    #endif
    /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "This is intended to handle stack address" */
    /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "To handle the stack" */
    Os_GulUserSPTop[OS_ONE] = (uint32)&Os_GaaRamUserStack1[0];
    Os_GulUserSPBtm[OS_ONE] = (uint32)Os_GulUserSPTop[OS_ONE] + Os_User_Stack_Size;
    Os_GulUserSP[OS_ONE] = Os_GulUserSPBtm[OS_ONE];
    /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    #if (OS_CORE_COUNT >= OS_THREE)
    #if(OS_STACK_MONITORING == STD_ON)
    /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
    /* polyspace<MISRA-C:11.4:Not a defect:Justify with annotations> This is intended to handle stack address  */
    /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
    Os_GaaRamUserStack2[0] = OS_STACK_PATTERN;
    #endif
    /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "This is intended to handle stack address" */
    /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "To handle the stack" */
    Os_GulUserSPTop[OS_TWO] = (uint32)&Os_GaaRamUserStack2[0];
    Os_GulUserSPBtm[OS_TWO] = (uint32)Os_GulUserSPTop[OS_TWO] + Os_User_Stack_Size;
    Os_GulUserSP[OS_TWO] = Os_GulUserSPBtm[OS_TWO];
    /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    #if (OS_CORE_COUNT >= OS_FOUR)
    #if(OS_STACK_MONITORING == STD_ON)
    /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
    /* polyspace<MISRA-C:11.4:Not a defect:Justify with annotations> This is intended to handle stack address  */
    /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
    Os_GaaRamUserStack3[0] = OS_STACK_PATTERN;
    #endif
    /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "This is intended to handle stack address" */
    /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "To handle the stack" */
    Os_GulUserSPTop[OS_THREE] = (uint32)&Os_GaaRamUserStack3[0];
    Os_GulUserSPBtm[OS_THREE] = (uint32)Os_GulUserSPTop[OS_THREE] + Os_User_Stack_Size;
    Os_GulUserSP[OS_THREE] = Os_GulUserSPBtm[OS_THREE];
    /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    #endif /* FOUR */
    #endif /* THREE */
    #endif /* End of #if (OS_MULTICORE == STD_ON) */
    #else
    #if(OS_STACK_MONITORING == STD_ON)
    /* @Trace: SafeOs_SUD_API_51026 */
    Os_GaaRamUserStack[0] = OS_STACK_PATTERN;
    #endif
    /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "To handle the stack" */
    /* @Trace: SafeOs_SUD_API_51027 */
    Os_GulUserSPTop[OS_ZERO] = (uint32)&Os_GaaRamUserStack[0];
    /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "This is intended to handle stack address" */
    Os_GulUserSPBtm[OS_ZERO] = (uint32)Os_GulUserSPTop[OS_ZERO] + Os_User_Stack_Size;
    Os_GulUserSP[OS_ZERO] = Os_GulUserSPBtm[OS_ZERO];
    /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To handle the stack */
    #endif

    #if (OS_APPLICATION == STD_ON)
    /* @Trace: SafeOs_SUD_API_51028 */
    LulCount = Os_Application_Count;
    do
    {
      LulCount--;

      LpStaticApplication = &Os_GaaStaticApplication[LulCount];
      /* polyspace:begin<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
      LpStack = &Os_GaaStack[LpStaticApplication->ucStackIndex];
      /* polyspace:end<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
      /* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
      /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
      Os_GulOsAppSPTop[LulCount] = (uint32)LpStack->pStackArea;
      /* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
      /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
      /* polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> Pointer arithmetic used to achieve better throughput. */
      /* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
      /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
      Os_GulOsAppSPBtm[LulCount] =
        (uint32)(&(((Os_StackType*)LpStack->pStackArea)[(Os_Sint_T)LpStack->usStackSize]));
      /* polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> Pointer arithmetic used to achieve better throughput. */
      /* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
      /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
      Os_GulOsAppSP[LulCount] = Os_GulOsAppSPBtm[LulCount];

      #if(OS_STACK_MONITORING == STD_ON)
      /* Writing stack pattern at the bottom of stack area */
      /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
      /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
      *(LpStack->pStackArea) = OS_STACK_PATTERN;
      #endif
      /* polyspace:end<MISRA-C3:D4.1> */
    } while(LulCount != OS_ZERO);
    #endif
  }
  /* polyspace:end<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of OS_CORE_ID depends on Multi-Core */
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of OS_CORE_ID depends on Multi-Core" */


  /* Enable system handlers - USAGE, BUS, MEM */
  /* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To access registers */
  /* polyspace +3 MISRA-C3:11.4 [Justified:Medium] "To access registers" */
  /* @Trace: SafeOs_SUD_API_51050 */
  *((volatile uint32 *)OS_ARM_M_SYSHANDLER_CTRL_ADDR) |= (OS_ARM_M_USAGE_F_ENA |
                                             OS_ARM_M_BUS_F_ENA | OS_ARM_M_MEM_F_ENA);
  /* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To access registers */

  
  /* Enable divide by integer zero fault detection */
  OS_SCB_CCR.B.DIV_0_TRP = 1U;
  
  /* Enable entering Thread mode with exceptions active because of a controlled return value */
  OS_SCB_CCR.B.NONBASETHRDENA = 1U;
  
  #if (OS_FPU_SUPPORT == STD_ON)
  OS_SCB_CPACR.B.CP10 = OS_SCB_CPACR_CP10_FULL_ACCESS;
  OS_SCB_CPACR.B.CP11 = OS_SCB_CPACR_CP11_FULL_ACCESS;

  OS_FPU_FPCCR.B.LSPEN = OS_FPU_FPCCR_LSPEN_DISABLE;
  OS_FPU_FPCCR.B.ASPEN = OS_FPU_FPCCR_ASPEN_DISABLE;

  __asm("dsb");
  __asm("isb");
	
  /** Save initial FPSCR value */
  Os_GddTaskInitFPSCR = Os_GetFpscr();
  #else

  OS_SCB_CPACR.B.CP10 = OS_SCB_CPACR_CP10_ACCESS_DENIED;
  OS_SCB_CPACR.B.CP11 = OS_SCB_CPACR_CP11_ACCESS_DENIED;

  OS_FPU_FPCCR.B.LSPEN = OS_FPU_FPCCR_LSPEN_DISABLE;
  OS_FPU_FPCCR.B.ASPEN = OS_FPU_FPCCR_ASPEN_DISABLE;

  __asm("dsb");
  __asm("isb");
  #endif /* if (OS_FPU_SUPPORT == STD_ON) */

  #if (OS_ISR_COUNT != OS_PRE_ZERO)
  /* @Trace: SafeOs_SUD_API_21209 */
  /* Set Priority of ISRs*/
  Os_SetISRPriority();
  #endif

  /* Call to InitTimer */
  Os_InitTimer();
}

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:18.1 */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
