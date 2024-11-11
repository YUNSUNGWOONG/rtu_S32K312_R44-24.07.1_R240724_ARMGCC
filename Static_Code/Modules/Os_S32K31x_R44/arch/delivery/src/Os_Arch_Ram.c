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
**  SRC-MODULE: OS_Arch_Ram.c                                                 **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of constant specific functionality                  **
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
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Arch_Ram.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
/**
 * @addtogroup OS_S32K31X_ESDD
 * @{ */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"
/** This global variable is used to define in kernel mode
 *  \n{Ref: SWR_OS_S32K31X_006} */
VAR(uint8, OS_VAR) Os_GucInKernel[OS_CORE_COUNT];

/** This global variable is used to define schedule request
 *  \n{Ref: SWR_OS_S32K31X_006} */ 
VAR(uint8, OS_VAR) Os_GucSchedReq[OS_CORE_COUNT];

/** This is global array which signifies the count which gets modified if any
 *  Cagegory1 ISR comes in or it gets completed
 *  \n{Ref: SWR_OS_S32K31X_002} */
VAR(uint8, OS_VAR) Os_GucNestingCAT1ISR[OS_CORE_COUNT];

/** This is global array which signifies the count which gets modified if any
 *  Category2 ISR comes in or it gets completed
 *  \n{Ref: SWR_OS_S32K31X_002} */ 
VAR(uint8, OS_VAR) Os_GucNestingCAT2ISR[OS_CORE_COUNT];

VAR(uint8, OS_VAR) Os_GucCheckCAT2IsrTF[OS_CORE_COUNT];
/* This global variable is used to check if CAT2ISR is killed
 * Because of timing protection
 *  \n{Ref: SWR_OS_S32K31X_006} */
VAR(uint8, OS_VAR) Os_GucKillCAT2ISR[OS_CORE_COUNT];
VAR(uint16, OS_VAR) Os_GusLastCat1IsrNumber[OS_CORE_COUNT];
VAR(uint8, OS_VAR) Os_GucInCat1Isr[OS_CORE_COUNT]; 

/** Variable to hold size of periphral */
VAR(uint8, OS_VAR) Os_GulPeripheralSize[OS_CORE_COUNT];
VAR(uint8, OS_VAR) Os_GddPeripheralSupport = OS_PERIPHERAL;
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"
/*Os_GusCurrentIsrNumber will be used to clear pending state of this interrupt
 * when entering into thread mode for executing HOOK function  */
VAR(uint16, OS_VAR) Os_GusCurrentIsrNumber;
VAR(uint16, OS_VAR) Os_GusPreserveBasepri;
VAR(uint16, OS_VAR) Os_GusPreserveControl;

#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"

#if (OS_MULTICORE == STD_ON)
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* polyspace<MISRA-C:3.4:Not a defect:Justify with annotations> It is used to make 32byte alignment  */
VAR(Os_MessageQueueType, OS_VAR) Os_GaaInterCoreMsgQ[OS_CORE_COUNT];
/* polyspace<MISRA-C:3.4:Not a defect:Justify with annotations> It is used to return pragma level as the previous pragma level  */
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"
VAR(uint32, OS_VAR) Os_GulUserSP[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulUserSPBtm[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulUserSPTop[OS_CORE_COUNT];
/* @Trace: SRS_BSW_00410 */
#if (OS_APPLICATION == STD_ON)
VAR(uint32, OS_VAR) Os_GulOsAppSP[OS_APPLICATION_COUNT];
VAR(uint32, OS_VAR) Os_GulOsAppSPBtm[OS_APPLICATION_COUNT];
VAR(uint32, OS_VAR) Os_GulOsAppSPTop[OS_APPLICATION_COUNT];
#endif /* End of (OS_APPLICATION == STD_ON) */
#if (OS_MULTICORE == STD_ON)
/* OS_ONE : For Os sync
 * OS_CORE_COUNT : For message between core
 * OS_SPINLOCK_COUNT : For user
 */
VAR(uint32, OS_VAR) Os_GulSpinlocks[OS_SPINLOCK_COUNT];
#endif /* End  (OS_MULTICORE == STD_ON) */
/** This global variable is used to save kernel stack pointer
 *  \n{Ref: SWR_OS_S32K31X_011} */
VAR(uint32, OS_VAR) Os_GulKernelSP[OS_CORE_COUNT];

/** This global variable is used to save kernel stack base address
 *  \n{Ref: SWR_OS_S32K31X_011} */ 
VAR(uint32, OS_VAR) Os_GulKernelSPBase[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulSaveSp[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulSaveSp_NTISR[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulSaveLR[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulSaveLR_NTISR[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulSavesvcSp[OS_CORE_COUNT];

#if (OS_FPU_SUPPORT == STD_ON)
/** This global variable is used to set FPSCR when a Task is start. */
VAR(Os_Reg32, OS_VAR) Os_GddTaskInitFPSCR;
#endif

#if (OS_MEMORY_PROTECTION == STD_ON)
/** This global variable is used to Memory Protection when a MPU Setting . */
VAR(ApplicationType, OS_VAR) Os_GddPrevAppId[OS_CORE_COUNT];
#endif

#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32
#include "MemMap.h"

#if (OS_APPLICATION == STD_ON)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to make user stack space for Os_Sleep0
 *  \n{Ref: SWR_OS_S32K31X_009} */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack0[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
#if (OS_MULTICORE == STD_ON)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE1_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to make user stack space for Os_Sleep1 */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack1[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE1_UNSPECIFIED
#include "MemMap.h"
#if (OS_CORE_COUNT >= OS_THREE)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE2_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to make user stack space for Os_Sleep1 */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack2[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE2_UNSPECIFIED
#include "MemMap.h"
#endif
#if (OS_CORE_COUNT >= OS_FOUR)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE3_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to make user stack space for Os_Sleep1 */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack3[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE3_UNSPECIFIED
#include "MemMap.h"
#endif
#endif /* #if (OS_MULTICORE == STD_ON) */
#else  /* #if (OS_APPLICATION == STD_ON) */
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
/* This global variable is used to make user stack space when OS-Application is not used
 *  \n{Ref: SWR_OS_S32K31X_009} */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_APPLICATION == STD_ON) */

/** This global variable is used to hold STM Clock Frequency in MHz unit
 *  \n{Ref: SWR_OS_S32K31X_007} */ 
VAR(uint32, OS_VAR) Os_GulStmClock = OS_TIMER_CLOCK;
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to save exception information
 *  \n{Ref: SWR_OS_S32K31X_004} */ 
VAR(Os_TrapInfoType, OS_VAR) Os_GddTrapInfo[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/** @} */
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
