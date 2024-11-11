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
**  SRC-MODULE: IoHwAb_Config.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : IoHwAb module const variable declarations for                 **
**              making a library                                              **
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
** 1.7.0     05-Mar-2024  YongEun.Lee       #CP44-3784                        **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

#ifndef IOHWAB_CONFIG_H
#define IOHWAB_CONFIG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#if (IOHWAB_USE_IO_MAN == STD_ON)
#include "Os.h"
#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#include "CoSvAb_GenExterns.h"
#endif
#if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
#include "Gpt.h"
#endif

#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
#include "Rte_Type.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern VAR(IoHwAb_JobResultType, IOHWAB_VAR) IoHwAb_GddJobResult;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#if (IOHWAB_USE_IO_MAN == STD_ON)
#if (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
  || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#define IOHWAB_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(TaskType, IOHWAB_VAR) IoHwAb_GddIOMTaskFG1;
#define IOHWAB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#define IOHWAB_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(TaskType, IOHWAB_VAR) IoHwAb_GddIOMTaskFG2;
#define IOHWAB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#else /* All but RH850 */
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_IOM_TASK_FG1 */
extern CONST(TaskType, IOHWAB_CONST) IoHwAb_GddIOMTaskFG1;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_IOM_TASK_FG2 */
extern CONST(TaskType, IOHWAB_CONST) IoHwAb_GddIOMTaskFG2;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */




#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)


#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_DIG_SWITCH_DELAY */
extern CONST(CoSvAb_FastTimerDelay, IOHWAB_CONST) IoHwAb_GddISupplyDigSwitchDelay;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#elif (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_DIG_SWITCH_DELAY */
extern CONST(IoHwAb_GptValueType, IOHWAB_CONST) IoHwAb_GddISupplyDigSwitchDelay;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */


#if (IOHWAB_USE_ANA_SUP_SWT == STD_ON)


#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_ANA_SWITCH_DELAY */
extern CONST(CoSvAb_FastTimerDelay, IOHWAB_CONST) IoHwAb_GddISupplyAnaSwitchDelay;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#elif (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
#define IOHWAB_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* IOHWAB_ISUPPLY_ANA_SWITCH_DELAY */
extern CONST(IoHwAb_GptValueType, IOHWAB_CONST) IoHwAb_GddISupplyAnaSwitchDelay;
#define IOHWAB_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */



/* IOHWAB_USE_DIG_OUT */
#if (IOHWAB_USE_DIG_OUT == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, IOHWAB_VAR) IoHwAb_GaaDigitalSignal_Locked[IOHWAB_NUM_DIGOUT_RESULT_BUFFER];
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

/*******************************************************************************
**                      MCU Dependency feature                                **
*******************************************************************************/
/* Bolero */
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_PORT_A	(0U)
#define IOHWAB_PORT_B	(16U)
#define IOHWAB_PORT_C	(32U)
#define IOHWAB_PORT_D	(48U)
#define IOHWAB_PORT_E	(64U)
#define IOHWAB_PORT_F	(80U)
#define IOHWAB_PORT_G	(96U)
#define IOHWAB_PORT_H	(112U)
#define IOHWAB_PORT_I	(128U)
#define IOHWAB_PORT_J	(144U)
#endif 

/* RH850F1L/K */
#if (IOHWAB_USE_IO_MAN == STD_ON)
#if (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
  || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOManager_AssignTaskID(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* RH850F1L/K */
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
#endif /* IOHWAB_CONFIG_H */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

