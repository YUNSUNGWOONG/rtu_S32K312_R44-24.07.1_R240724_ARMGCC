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
**  SRC-MODULE: Os_Ioc.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Alarm.c file containing the declaration of **
**              Alarm related functions.                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C  10.7               **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_IOC_H
#define OS_IOC_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_IOCLOCKBASE_UNQUEUED (OS_MESSAGEQLOCKBASE + OS_CORE_COUNT)
#define OS_IOCLOCKBASE_QUEUED   (OS_MESSAGEQLOCKBASE + OS_CORE_COUNT \
                                                        + (uint32)Os_Ioc_Count_Unqueued)

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00410 */
#if (OS_APPLICATION == STD_ON)
extern FUNC(void, OS_CODE) Os_DoIocPullCB(
    P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID);
#endif /* @(OS_APPLICATION == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_APPLICATION == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_CallIocRead(uint32 IocID, P2VAR(void, AUTOMATIC, OS_VAR) data[]);
extern FUNC(StatusType, OS_CODE) Os_CallIocWrite(uint32 IocID,
                                 CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_CallIocReceive(uint32 IocID,
                                      P2VAR(void, AUTOMATIC, OS_VAR) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_CallIocSend(uint32 IocID, CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_CallIocEmptyQueue(uint32 IocID);
extern FUNC(void, OS_CODE) Os_CallIocPullCB(P2FUNC(void, OS_CONST, pIocPullCB) (void),
    ApplicationType recvAppID);
#endif /* (OS_APPLICATION == STD_ON) */
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_ALARM_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
