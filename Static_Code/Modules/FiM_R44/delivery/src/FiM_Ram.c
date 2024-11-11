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
**  SRC-MODULE: FiM_Ram.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Global RAM Variables of FiM                                   **
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
** 1.0.1     06-Dec-2021   LanhLT          Changes made As per Redmine #22518 **
** 0.0.4    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.3     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_Ram.h"     /* Ram header file */
/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
#define FIM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global Variable to store FIM Initialization status */
/* Shall be initialized with value 0 before any APIs of the FiM is called */
VAR(uint8, FIM_VAR) FiM_GucInitStatus = FIM_NOT_INITIALIZED;

#define FIM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"


#if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
#define FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: FiM_SUD_GLOBALVAR_001*/
/* Global array to store Dem component FAILED state */
VAR(boolean, FIM_VAR_NOINIT) FiM_GaaComponentFailedState
  [FIM_TOTAL_NUM_OF_DEM_COMPONENT];
#define FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO */

#if (FIM_TOTAL_NUM_OF_FIDS>0)
#define FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global array to store FID permission state */
VAR(boolean, FIM_VAR_NOINIT) FiM_GaaFidPermissionState[FIM_TOTAL_NUM_OF_FIDS];
#define FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define FIM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global array to store inhibition counter for all FID */
VAR(FiM_FidsSizeType, FIM_VAR_NOINIT)
  FiM_GaaFidInhibitCounter[FIM_TOTAL_NUM_OF_FIDS];
#define FIM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#if (FIM_AVAILABILITY_SUPPORT == STD_ON)
#define FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global array to store FID Available state */
/* @Trace: SWS_Fim_00015 */
/* @Trace: SWS_Fim_00009 */
/* @Trace: SRS_Fim_04713 */
VAR(boolean, FIM_VAR_NOINIT) FiM_GaaFidAvailableState[FIM_TOTAL_NUM_OF_FIDS];
#define FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */

#endif /* FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
