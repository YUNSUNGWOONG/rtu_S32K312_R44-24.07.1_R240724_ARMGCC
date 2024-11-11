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
**  SRC-MODULE: IoHwAb_Config.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : IoHwAb module const variable definitions for                  **
**              making a library                                              **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDENT [yes/no]: no                                           **
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
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/
/* polyspace-begin VARIABLE:* [Not a defect:Low] "System intended for multitasking" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Config.h"
#include "Rte_IoHwAb.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00441 */
/* @Trace: SWS_IoHwAb_00102 */
#define IOHWAB_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(IoHwAb_JobResultType, IOHWAB_VAR) IoHwAb_GddJobResult = IOHWAB_JOB_UNINIT;
#define IOHWAB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (IOHWAB_USE_IO_MAN == STD_ON)

#if (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
  || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#define IOHWAB_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(TaskType, IOHWAB_VAR) IoHwAb_GddIOMTaskFG1 = 0U;
#define IOHWAB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#define IOHWAB_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(TaskType, IOHWAB_VAR) IoHwAb_GddIOMTaskFG2 = 0U;
#define IOHWAB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#else /* All but RH850 */

/* IOHWAB_IOM_TASK_FG1 */
#if defined(IOHWAB_IOM_TASK_FG1)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(TaskType, IOHWAB_CONST) IoHwAb_GddIOMTaskFG1
  = IOHWAB_IOM_TASK_FG1;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (IOHWAB_IOM_TASK_FG1)      */

/* IOHWAB_IOM_TASK_FG2 */
#if defined(IOHWAB_IOM_TASK_FG2)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(TaskType, IOHWAB_CONST) IoHwAb_GddIOMTaskFG2
  = IOHWAB_IOM_TASK_FG2;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (IOHWAB_IOM_TASK_FG2)      */
#endif /* RH850 */

#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */


#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)

#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_DIG_SWITCH_DELAY */
CONST(CoSvAb_FastTimerDelay, IOHWAB_CONST) IoHwAb_GddISupplyDigSwitchDelay
  = IOHWAB_ISUPPLY_DIG_SWITCH_DELAY;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#elif (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_DIG_SWITCH_DELAY */
CONST(IoHwAb_GptValueType, IOHWAB_CONST) IoHwAb_GddISupplyDigSwitchDelay
  = IOHWAB_ISUPPLY_DIG_SWITCH_DELAY;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */

#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */


#if (IOHWAB_USE_ANA_SUP_SWT == STD_ON)

#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_ANA_SWITCH_DELAY */
CONST(CoSvAb_FastTimerDelay, IOHWAB_CONST) IoHwAb_GddISupplyAnaSwitchDelay
  = IOHWAB_ISUPPLY_ANA_SWITCH_DELAY;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#elif (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_ANA_SWITCH_DELAY */
CONST(IoHwAb_GptValueType, IOHWAB_CONST) IoHwAb_GddISupplyAnaSwitchDelay
  = IOHWAB_ISUPPLY_ANA_SWITCH_DELAY;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */


#if (IOHWAB_USE_IO_MAN == STD_ON)
#if (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
  || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_IOManager_AssignTaskID(void)
{
	IoHwAb_GddIOMTaskFG1 = IOHWAB_IOM_TASK_FG1;
	IoHwAb_GddIOMTaskFG2 = IOHWAB_IOM_TASK_FG2;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* RH850 */
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

#if (IOHWAB_USE_DIG_OUT == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, IOHWAB_VAR) IoHwAb_GaaDigitalSignal_Locked[IOHWAB_NUM_DIGOUT_RESULT_BUFFER];
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

/* polyspace-end VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

