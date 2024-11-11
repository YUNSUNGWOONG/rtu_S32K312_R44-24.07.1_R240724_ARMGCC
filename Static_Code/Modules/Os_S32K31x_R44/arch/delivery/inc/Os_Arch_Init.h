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
**  SRC-MODULE: Os_Arch_Init.h                                                **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S3231K related Init API                       **
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
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

#ifndef OS_ARCH_INIT_H_
#define OS_ARCH_INIT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/** Macro for initializing the port
 * @ingroup OS_S32K31X_ESDD_005 */

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"
extern CONST(uint32, OS_CONST) Os_User_Stack_Size;
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, OS_CODE) OS_PORTINITIALIZE(void);
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_ARCH_INIT_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
