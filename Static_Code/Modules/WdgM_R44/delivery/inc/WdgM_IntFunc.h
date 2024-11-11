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
**  SRC-MODULE: WdgM_IntFunc.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Provision of Prototypes of WdgM module internal functions     **
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
** 0.0.1     16-Sep-2019   ThanhNT      Initial version                       **
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.4     24-Oct-2019   ThanhNT      Update coding convention              **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     27-Nov-2019   ThanhNT      Fix misra warning                     **
** 0.0.9     11-Mar-2020   TienVD       Update traceability                   **
** 0.0.10    10-Sept-2020  ThanhNH5     Added WdgM_GetCoreIndex (#15739)      **
** 0.0.11    12-Sep-2020   LanBT        Update to use common function         **
**                                      signature with CoreId in prama(#15485)**
** 0.0.12    16-Sep-2020   ThanhNH5     Added DeInit time out for each core   **
**                                      (#15843)                              **
** 0.0.13    16-Oct-2020   ThanhNT      Update MemMap ASIL_D (#16306)         **
** 0.0.14    30-Oct-2020   ThanhNH5     Updated Exclusive areas (#16306)      **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */

#ifndef WDGM_INT_FUNC_H
#define WDGM_INT_FUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_IntTypes.h"               /* WdgM Types Header file */


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

extern FUNC_P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CODE)  WdgM_SEIDBinarySearch(    VAR(CoreIdType, AUTOMATIC) coreId,     VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId  );

#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(boolean, WDGM_CODE) WdgM_SEIndexBinarySearch(
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId,
  P2VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC, WDGM_DATA) ptrSEIndex
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(boolean, WDGM_CODE) WdgM_InternalSetMode(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_ModeType, AUTOMATIC) modeIdx
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if(WDGM_ENABLE_TRIGGER == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_TriggerWdgIf(
  VAR(CoreIdType, AUTOMATIC) coreId,
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrMode,
  VAR(WdgM_TriggerModeType, AUTOMATIC) triggerMode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_ClearActivityFlag(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrCurrentMode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformAliveIndication(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_ModeType, AUTOMATIC) currentMode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformAliveSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformDeadlineSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx,
  VAR(WdgM_ModeType, AUTOMATIC) currentMode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformIntLogicalSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformExtLogicalSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId,
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx,
  VAR(WdgM_ModeType, AUTOMATIC) currentMode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_EvaluateLocalStatus(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) ptrSEFailedFlag,
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) ptrSEExpiredFlag
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_EvaluateGlobalStatus(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(boolean, AUTOMATIC) failedFlag, 
  VAR(boolean, AUTOMATIC) expiredFlag
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetCoreIndex(
  P2VAR(WdgM_CoreIdType, AUTOMATIC, WDGM_DATA) ptrCoreId
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_ValidateOffMode(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrNewMode,
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId, VAR(uint8, AUTOMATIC) serviceId
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#endif /* WDGM_INT_FUNC_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
