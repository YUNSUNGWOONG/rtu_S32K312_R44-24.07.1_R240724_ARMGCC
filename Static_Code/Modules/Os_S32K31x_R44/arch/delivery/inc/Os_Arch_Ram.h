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
**  SRC-MODULE: Os_Arch_Ram.h                                                 **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related global var                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:      Yes                                     **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:   No                                      **
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
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-2442                    ** 
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

#ifndef OS_ARCH_RAM_H_
#define OS_ARCH_RAM_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"
extern VAR(uint32, OS_VAR) Os_GulUserSP[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulUserSPBtm[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulUserSPTop[OS_CORE_COUNT];
/* @Trace: SRS_BSW_00410 */
#if (OS_APPLICATION == STD_ON)
/* polyspace-begin MISRA-C:8.12 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
extern VAR(uint32, OS_VAR) Os_GulOsAppSP[];
extern VAR(uint32, OS_VAR) Os_GulOsAppSPBtm[];
extern VAR(uint32, OS_VAR) Os_GulOsAppSPTop[];
/* polyspace-end MISRA-C:8.12 */
#endif /* End of #if (OS_APPLICATION == STD_ON) */

#if (OS_MULTICORE == STD_ON)
extern VAR(uint32, OS_VAR) Os_GulSpinlocks[];
#endif /* End of if (OS_MULTICORE == STD_ON) */
extern VAR(uint32, OS_VAR) Os_GulKernelSP[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulKernelSPBase[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulSaveSp[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulSaveSp_NTISR[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulSaveLR[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulSaveLR_NTISR[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulSavesvcSp[OS_CORE_COUNT];
#if (OS_FPU_SUPPORT == STD_ON)
extern VAR(Os_Reg32, OS_VAR) Os_GddTaskInitFPSCR;
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
/** This global variable is used to Memory Protection when a MPU Setting . */
extern VAR(ApplicationType, OS_VAR) Os_GddPrevAppId[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"
extern VAR(uint16, OS_VAR) Os_GusLastCat1IsrNumber[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucInCat1Isr[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucInKernel[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucSchedReq[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucNestingCAT1ISR[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucNestingCAT2ISR[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucCheckCAT2IsrTF[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucKillCAT2ISR[OS_CORE_COUNT];

/** Variable to hold size of periphral */
extern VAR(uint8, OS_VAR) Os_GulPeripheralSize[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GddPeripheralSupport;
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"
/*Os_GusCurrentIsrNumber will be used to clear pending state of this interrupt
 * when entering into thread mode for executing HOOK function  */
extern VAR(uint16, OS_VAR) Os_GusCurrentIsrNumber;
extern VAR(uint16, OS_VAR) Os_GusPreserveBasepri;
extern VAR(uint16, OS_VAR) Os_GusPreserveControl;

#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"

#if (OS_APPLICATION == STD_ON)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack0[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
#if (OS_MULTICORE == STD_ON)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE1_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack1[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE1_UNSPECIFIED
#include "MemMap.h"
#if (OS_CORE_COUNT >= OS_THREE)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE2_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack2[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE2_UNSPECIFIED
#include "MemMap.h"
#if (OS_CORE_COUNT >= OS_FOUR)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE3_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack3[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE3_UNSPECIFIED
#include "MemMap.h"
#endif /*FOUR*/
#endif /*THREE*/
#endif /* #if (OS_MULTICORE == STD_ON) */
#else  /* #if (OS_APPLICATION == STD_ON) */
/* @Trace: SRS_BSW_00351 */
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
/* polyspace<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack[OS_USER_STACK_SIZE];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_APPLICATION == STD_ON) */

/* Variable to hold STM Clock Frequency in MHz unit */
#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32
#include "MemMap.h"
extern VAR(uint32, OS_VAR) Os_GulStmClock;
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_TrapInfoType, OS_VAR) Os_GddTrapInfo[OS_CORE_COUNT];
#if (OS_MULTICORE == STD_ON)
extern Os_MessageQueueType Os_GaaInterCoreMsgQ[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern VAR(Tdd_Os_HardwareCounter, OS_VAR) Os_GaaHardwareCounter[]; 
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO) */

#if (OS_APPLICATION == STD_OFF)
#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
/* polyspace<MISRA-C3:8.11:Not a defect:Justify with annotations> for array with external linkage , size would come from configuration files hence not specified explicitly */
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack[];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_APPLICATION == STD_OFF) */

#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
/* OS-Application Stack for Core0 */
/* @Trace: SafeOs_SUD_API_000110 */
extern VAR(Os_StackType, OS_VAR) Os_GaaRamOsAppStackSize0[];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"

#define OS_STACK_START_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"
/* OS-Task Stack for Core0 */
/* @Trace: SafeOs_SUD_API_000111 */
extern VAR(Os_StackType, OS_VAR) Os_GaaRamTaskStackSize0[];
#define OS_STACK_STOP_SEC_VAR_CLEARED_ASIL_D_LOCAL_CORE0_UNSPECIFIED
#include "MemMap.h"

#endif /* OS_ARCH_RAM_H_ */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
