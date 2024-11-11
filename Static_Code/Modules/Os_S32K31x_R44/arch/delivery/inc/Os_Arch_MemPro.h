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
**  SRC-MODULE: Os_Arch_MemPro.h                                              **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S3231K related memory protection API          **
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
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.1.0      8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/
#ifndef OS_ARCH_MEMPRO_H_
#define OS_ARCH_MEMPRO_H_

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Regs.h"
#include "Os_Arch_Interrupt.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (OS_MEMORY_PROTECTION == STD_ON)
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SRS_BSW_00309 */
extern CONST(Tdd_Os_MemoryBlock, OS_CONST) Os_GaaStaticMemBlock[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif /*#if (OS_MEMORY_PROTECTION == STD_ON)*/
/* polyspace-end MISRA-C:8.12 */

#if (OS_MEMORY_PROTECTION == STD_ON)
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"
extern CONST(uint32, OS_CONST) Os_MemBlk_Count;
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"
#endif /*#if (OS_MEMORY_PROTECTION == STD_ON)*/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#if(OS_MEMORY_PROTECTION == STD_ON)
extern FUNC(void, OS_CODE) Os_HandleMemoryBlock(P2CONST(Tdd_Os_StaticTask,
    AUTOMATIC, OS_CONST) LpStaticTask);
extern FUNC(void, OS_CODE) Os_InitializeDedicatedMemBlock(void);

#if (OS_SCALABILITY_CLASS >= OS_SC3)
extern FUNC(AccessType, OS_CODE) Os_CheckMemoryAccessService(ObjectTypeType
        LddTaskID, MemoryStartAddressType LddStartAddr, MemorySizeType LulSize);
#endif
#if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
extern FUNC(void, OS_CODE) Os_DisableAppInterrupts(ApplicationType Application);
extern FUNC(void, OS_CODE) Os_EnableAppInterrupts(void);
#endif
#endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) */

#endif /* OS_ARCH_MEMPRO_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
