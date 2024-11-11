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
**  SRC-MODULE: IoHwAb_DigIn.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : C header for DigIn                                            **
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
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

#ifndef IOHWAB_DIGIN_H
#define IOHWAB_DIGIN_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define IOHWAB_DIGIN_COUNT_BIT_MASK              (0x0FU)
#define IOHWAB_DIGIN_FILT_BIT_MASK               (0x10U)
#define IOHWAB_DIGIN_RAW_BIT_MASK                (0x20U)
#define IOHWAB_DIGIN_RESULT_SET_BIT_MASK         (0x30U)
#define IOHWAB_DIGIN_FREEZE_BIT_MASK             (0x40U)
#define IOHWAB_DIGIN_UNFREEZE_BIT_MASK           (0xBFU)
#define IOHWAB_DIGIN_RESULT_COUNT_CLEAR_BIT_MASK (0xC0U)

/*******************************************************************************
**                      Macro                                                 **
*******************************************************************************/
/* polyspace<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
#define IOHWAB_DIGIN_GET_FILT_VAL(x)      (((x) & IOHWAB_DIGIN_FILT_BIT_MASK) >> 4)
/* polyspace<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
#define IOHWAB_DIGIN_GET_RAW_VAL(x)       (((x) & IOHWAB_DIGIN_RAW_BIT_MASK)  >> 5)
/* polyspace<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
#define IOHWAB_DIGIN_GET_FREEZE_VAL(x)    (((x) & IOHWAB_DIGIN_FREEZE_BIT_MASK) >> 6)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (IOHWAB_USE_DIG_IN == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, IOHWAB_VAR) IoHwAb_DigInFilteringStart;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (IOHWAB_USE_DIG_IN == STD_ON)

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,IOHWAB_CODE)IoHwAb_DigInInit1(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,IOHWAB_CODE)IoHwAb_DigInInit2(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,IOHWAB_CODE)IoHwAb_DigInH2L(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,IOHWAB_CODE)IoHwAb_DigInSampleLP(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,IOHWAB_CODE)IoHwAb_DigInReadHwInputs(boolean blFast);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,IOHWAB_CODE)IoHwAb_DigInDebounce(IoHwAb_IndexType Idx,
  IoHwAb_IndexType NumFilt);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

#endif /* IOHWAB_ANAIN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
