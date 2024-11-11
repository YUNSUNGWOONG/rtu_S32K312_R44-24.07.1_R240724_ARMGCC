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
**  SRC-MODULE: FiM_InternalFunc.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : c Header for FiM_InternalFunc.c                               **
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
** 0.0.5    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.4     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.3    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/
#ifndef FIM_INTERNALFUNC_H
#define FIM_INTERNALFUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_Ram.h"  /* Ram header file */

/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, FIM_CODE) FiM_CalcAllFidsPermissions(void);

extern FUNC(void, FIM_CODE) FiM_CalcFidPermission( Dem_MonitorStatusType
  LddMonitorStatus, FiM_EventsSizeType LddEvent);

#if (FIM_TOTAL_NUM_OF_FUNCTION_ID_COMPONENT > FIM_ZERO)
extern FUNC(void, FIM_CODE) FiM_CalcFidPermissionByComponent (
  boolean ComponentFailedStatus,
  FiM_ComponentSizeType LddComponentArrayIndex);
#endif /* FIM_TOTAL_NUM_OF_FUNCTION_ID_COMPONENT > FIM_ZERO */

extern FUNC(void, FIM_CODE) FiM_Report_Error(uint8 sid, uint8 type);

#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of FIM_INTERNALFUNC_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
