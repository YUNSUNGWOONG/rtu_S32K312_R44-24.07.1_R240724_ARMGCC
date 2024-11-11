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
**  PURPOSE   : Configurable const variable definition                        **
**              of Function Inhibition Manager                                **
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
** 0.0.3    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

#ifndef FIM_CONFIG_H
#define FIM_CONFIG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_FiM_Type.h"
#include "FiM_Cfg.h"        /* FiM Cfg Definition Header File */
#include "FiM_PCTypes.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, FIM_CODE) FiM_EventIdSearch(
  Dem_EventIdType LddEventId,
  P2VAR(FiM_EventsSizeType, AUTOMATIC, FIM_VAR)LpEventIndex);

extern FUNC(boolean, FIM_CODE) FiM_FidSearch(
  FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR)LddFidArrayIndex);

#if(FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
extern FUNC(boolean, FIM_CODE) FiM_ComponentIdSearch(
  Dem_ComponentIdType LddComponentId,
  P2VAR(uint16, AUTOMATIC, FIM_VAR)LpComponentIndex);
#endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO */

#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_CONFIG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
