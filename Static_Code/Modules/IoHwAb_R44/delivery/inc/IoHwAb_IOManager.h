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
**  SRC-MODULE: IoHwAb_IOManager.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : C header for IO Manager                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.0.1     26-Feb-2020  YangJin.Kim       R40-Redmine #28531                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/
#ifndef IOHWAB_IOMANAGER_H
#define IOHWAB_IOMANAGER_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "Os.h"


#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#include "CoSvAb_FastTimer.h"
#endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */

#if (IOHWAB_USE_PM_MODULE == STD_ON)
extern FUNC(Std_ReturnType, Pm_CODE) Pm_GetPowerMode(P2VAR(Pm_PowerModeType, AUTOMATIC, RTE_APPL_DATA) mode);
#endif /* (IOHWAB_USE_PM_MODULE == STD_ON) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/*polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283)*/

#if (IOHWAB_USE_IO_MAN == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMDeInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMAnaInAcqEnd(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOML2H(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMH2L(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMInputsLP(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMOutputsLP(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMOnTimer(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMDelayTicks(uint32 ticks);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOM_5ms(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOM_10ms(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#if defined(IOHWAB_IOM_TASK_FG2)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern IOHWAB_IOM_TASK_FG2_FUNC;
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_IOM_TASK_FG2)      */

#if defined(IOHWAB_IOM_TASK_FG1)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern IOHWAB_IOM_TASK_FG1_FUNC;
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_IOM_TASK_FG1)      */

#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
/*polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283)*/
#endif /* IOHWAB_IOMANAGER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
