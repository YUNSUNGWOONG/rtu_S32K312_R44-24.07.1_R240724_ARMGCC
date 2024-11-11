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
**  SRC-MODULE: Os_PortTypes.h                                                **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related register                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:       Yes                                    **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:    No                                     **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.3   20-Jul-2022    TinHV        Jira    CP44-661                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/* @Trace: SRS_Os_80006 SRS_PSRS_00002 */
#ifndef OS_PORTTYPES_H
#define OS_PORTTYPES_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
/* polyspace:begin<MISRA-C3:2.4:Not a defect:Justify with annotations> Tags may be used for cross reference */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Informative macro is defined */
/* polyspace:begin<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace-begin CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace:begin<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Types.h"
#include "Os_Arch_Ram.h"
#include "Os_Arch_SystemCall.h"
#include "Os_Arch_Context.h"
#include "Os_Arch_Init.h"
#include "Os_Arch_Interrupt.h"
#include "Os_Arch_Timer.h"

#if (OS_MULTICORE == STD_ON)
#include "Os_Arch_Multicore.h"
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_Arch_TimingProtection.h"
#endif
#if(OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Arch_MemPro.h"
#endif
#include "Os_Arch_Idle.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#endif /* End of ifndef OS_PORTTYPES_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:D4.8 */
/* polyspace:end<MISRA-C3:2.4:Not a defect:Justify with annotations> Tags may be used for cross reference */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Informative macro is defined */
/* polyspace-end CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace:end<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:end<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
