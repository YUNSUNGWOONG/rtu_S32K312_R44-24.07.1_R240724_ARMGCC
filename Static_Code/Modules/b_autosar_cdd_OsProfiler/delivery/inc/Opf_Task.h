/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Opf_Task.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Type definetion for OS Profiler                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.5.8     10-Aug-2022    JC.Kim        Redmine #36752                      **
** 1.5.7.1   29-Jun-2022    HJ.Kim        CP44-390                            **
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448, #33412              **
** 1.1.0     30-Nov-2016    SH.Yoo        Redmine #6755                       **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

#ifndef OPF_TASK_H
#define OPF_TASK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Types.h"
#include "Opf_Port.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
extern FUNC(void, OPF_CODE) Opf_UpdateTaskInfo(const Tdd_Opf_Event *pEvent);
extern FUNC(void, OPF_CODE) Opf_ValidateTask(OpfTaskIDType LddTaskID);
/* polyspace-end MISRA-C3:D4.5 */


#endif /* OPF_TASK_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
