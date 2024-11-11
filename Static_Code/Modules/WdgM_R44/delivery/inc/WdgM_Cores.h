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
**  SRC-MODULE: WdgM_Cores.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Watchdog Manager Cores specific                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 0.0.1     27-Apr-2020   ThanhNH5     Initial version                       **
** 0.0.2     10-Sep-2020   ThanhNH5     Replace macro WDGM_CORE_INFO (#15739) **
** 0.0.3     12-Sep-2020   LanBT        Update to use common macro signature  **
**                                      with coreId in prama (#15485)         **
** 0.0.4     12-Sep-2020   LanBT        To remove WdgM_PtrConfig global       **
**                                      variable and use locally only (#15485)**
** 0.0.5     16-Sep-2020   ThanhNH5     Added DeInit time out for each core   **
**                                      (#15843)                              **
** 0.0.6     21-Sep-2020   ThanhNH5     Fixed memory sections issue(#15934)   **
** 0.0.7     05-Oct-2020   ThanhNH5     Merge variables in single and         **
**                                      multi core (#15485)                   **
** 0.0.30    16-Oct-2020   ThanhNT      Update MemMap ASIL_D (#16306)         **
** 0.0.31    16-Oct-2020   ThanhNT      Update global variables multicore     **
**                                      (#16286)                              **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace:begin<CERT-C:PRE00-C:Not a defect:Justify with annotations> Macro is used to improve the readability of code */

#ifndef WDGM_CORES_H
#define WDGM_CORES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_IntTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/

/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "macro is used according to user configuration" */
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "macro is used to improve the readability of code" */
/* Post build not implemented */
#define GET_CONFIG_PTR(coreId)      WdgM_Config[(coreId)]

/* Get the current actice mode ID */
#define WDGM_READ_CURRENT_MODE(coreId) (*(WdgM_CurrentMode[(coreId)]))
/* Update active mode ID */
#define WDGM_WRITE_CURRENT_MODE(coreId,modeID) (*(WdgM_CurrentMode[(coreId)])) = (modeID)

/* Get SE status */
#define WDGM_READ_SE_STATUS(seIndex) (*WdgM_SEStatus[(seIndex)])
/* Get SE status pointer*/
#define WDGM_READ_SE_STATUS_PTR(seIndex) (WdgM_SEStatus[(seIndex)])
/* Update SE status */
#define WDGM_WRITE_SE_STATUS(seIndex, status) (*WdgM_SEStatus[(seIndex)]) = (status)

/* Get the current Global Supervision Status pointer */
#define WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId) (WdgM_GlobalSupervisionStatus[(coreId)])

/* Get the current Invert Global Supervision Status */
#define WDGM_GET_INV_GLOBAL_SUPERVISION_STATUS_PTR(coreId) (WdgM_InvGlobalSupervisionStatus[(coreId)])

/* Get the Exp Supervision Cycle Counter pointer*/
#define WDGM_GET_EXP_SUPERVISION_CYCLE_COUNTER_PTR(coreId) (WdgM_ExpSupervisionCycleCounter[(coreId)])
/* Update the Exp Supervision Cycle Counter  */
#define WDGM_WRITE_EXP_SUPERVISION_CYCLE_COUNTER(coreId,value) (*(WdgM_ExpSupervisionCycleCounter[(coreId)])) = (value)

/* Get the Free Running Counter pointer*/
#define WDGM_GET_FREE_RUNNING_COUNTER_PTR(coreId) (WdgM_FreeRunningCounter[(coreId)])
/* Update the Free Running Counter */
#define WDGM_WRITE_FREE_RUNNING_COUNTER(coreId,value) (*(WdgM_FreeRunningCounter[(coreId)])) = (value)

/* Get the Alive Indication Status */
#define WDGM_GET_ALIVE_INDICATION_STATUS_PTR(coreId) WdgM_AliveIndicationStatus[(coreId)]

/* Update the Deadline Supervision Status */
#define WDGM_GET_DEADLINE_SUPERVISON_STATUS_PTR(coreId, index) &WdgM_DeadlineSupervisionStatus[(coreId)][(index)]

/* Update the Internal Logical Supervision Status */
#define WDGM_GET_INTLOGICAL_SUPERVISON_STATUS_PTR(coreId, index) &WdgM_IntLogicalSupervisionStatus[(coreId)][(index)]

/* Update the External Logical Supervision Status */
#define WDGM_GET_EXTLOGICAL_SUPERVISON_STATUS_PTR(coreId, index) &WdgM_ExtLogicalSupervisionStatus[(coreId)][(index)]
/* polyspace-end MISRA-C3:D4.9 */
/* polyspace-end MISRA-C3:2.5 */
/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00310 SRS_ModeMgm_09110 SRS_BSW_00323 */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store the current mode of watchdog manager */
extern CONSTP2VAR(WdgM_ModeType, AUTOMATIC, WDGM_CONST) WdgM_CurrentMode[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace:  */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern CONSTP2VAR(uint8, AUTOMATIC, WDGM_CONST) WdgM_SEStatus[WDGM_TOTAL_SES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_ModeMgm_09112 */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store the overall supervision status */
extern CONSTP2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_CONST)
  WdgM_GlobalSupervisionStatus[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_ModeMgm_09112 */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store the inverse overall supervision status */
extern CONSTP2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_CONST)
  WdgM_InvGlobalSupervisionStatus[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: WdgM_SRS_ECUC_00329 */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store the amount of expired supervision cycles for how
  long the blocking of watchdog triggering shall be postponed in a given mode */
extern CONSTP2VAR(WdgM_ExpSupCycleTolType, AUTOMATIC, WDGM_CONST)
  WdgM_ExpSupervisionCycleCounter[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_ModeMgm_09112 */
#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store the WdgM_MainFunction call count */
extern CONSTP2VAR(uint32, AUTOMATIC, WDGM_CONST) WdgM_FreeRunningCounter[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: WdgM_SRS_ECUC_00327 */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global array to store the failed cycles of each supervised entity */
extern CONSTP2VAR(WdgM_FailureTolType, AUTOMATIC, WDGM_CONST)
  WdgM_FailedRefCycleCounter[WDGM_TOTAL_SES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace:  */
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store error occurrence in performing alive supervisions */
extern CONSTP2VAR(boolean, AUTOMATIC, WDGM_CONST) WdgM_AlreadyUpdated[WDGM_TOTAL_SES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: SRS_ModeMgm_09112 SRS_ModeMgm_09160 SRS_ModeMgm_09221 SRS_ModeMgm_09143 */
#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store Alive Indication status */
extern CONSTP2VAR(WdgM_ExAliveIndicationsCountType, AUTOMATIC, WDGM_CONST)
  WdgM_AliveIndicationStatus[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
#if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store Deadline Monitoring status */
extern CONSTP2VAR(WdgM_DeadlineSupervisionStatusType, AUTOMATIC, WDGM_CONST)
  WdgM_DeadlineSupervisionStatus[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store Internal Logical Supervision status */
extern CONSTP2VAR(WdgM_IntLogicalSupervisionStatusType, AUTOMATIC, WDGM_CONST)
  WdgM_IntLogicalSupervisionStatus[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Pointer to Global variable to store External Logical Supervision status */
extern CONSTP2VAR(WdgM_ExtLogicalSupervisionStatusType, AUTOMATIC, WDGM_CONST)
  WdgM_ExtLogicalSupervisionStatus[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

#define WDGM_START_SEC_CONST_ASIL_D_GLOBAL_8
#include "MemMap.h"
extern CONST(uint8, WDGM_CONST) StatusSeverity[WDGM_GLOBALSTATUS_TOTAL];
#define WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_8
#include "MemMap.h"

#endif /* WDGM_CORES_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */
/* polyspace:end<CERT-C:PRE00-C> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
