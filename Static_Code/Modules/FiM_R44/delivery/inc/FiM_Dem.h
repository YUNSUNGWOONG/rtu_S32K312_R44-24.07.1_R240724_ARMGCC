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
**  SRC-MODULE: FiM_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
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
** 0.0.4    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.3    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    18-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/
#ifndef FIM_DEM_H
#define FIM_DEM_H
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_Types.h"     /* FiM Types Definition Header File */
#include "Dem_Types.h"     /* Dem Types Definition Header File */
#include "FiM_Cfg.h"       /* FiM Cfg Definition Header File */
#include "FiM_Config.h"
#include "FiM_Version.h"
#include "Dem.h"
#include "FiM.h"
#include "Rte_Dem_Type.h"


#define FIM_START_SEC_CODE
#include "MemMap.h"

/* Extern for FiM_DemInit */
extern FUNC(void, FIM_CODE) FiM_DemInit(void);

#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/* Extern for FiM_DemTriggerOnEventStatus */
#if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, FIM_CODE) FiM_DemTriggerOnMonitorStatus(
  Dem_EventIdType EventId);

#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON */

#if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
#define FIM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, FIM_CODE) FiM_DemTriggerOnComponentStatus(
  Dem_ComponentIdType ComponentId,
  VAR(boolean, FIM_VAR_NOINIT) ComponentFailedStatus);

#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT >0 */
#endif /* FIM_DEM_H */
