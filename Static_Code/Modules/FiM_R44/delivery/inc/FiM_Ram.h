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
**  SRC-MODULE: FiM_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : c Header for Fim_Ram.c                                        **
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

#ifndef FIM_RAM_H
#define FIM_RAM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_PCTypes.h"  /* PCTypes header file */
/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
/* @Trace: FiM_SUD_GLOBALVAR_001*/
#define FIM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


/* Global Variable to store configuration data */
extern P2VAR(FiM_FunctionIdMask, AUTOMATIC, FIM_APPL_CONST)
  FiM_GpFunctionIdMask;

/* Global Variable to store configuration data */
extern P2VAR(FiM_FunctionIdComponent, AUTOMATIC, FIM_APPL_CONST)
  FiM_GpFunctionIdComponent;

#define FIM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#define FIM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Global Variable to store FIM Initialization status */
extern VAR(uint8, FIM_VAR) FiM_GucInitStatus;

#define FIM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"


#if(FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO)
#define FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SWS_Fim_00020 */
/* @Trace: SRS_Fim_04713 */
/* Global array to store FID permission state */
extern VAR(boolean, FIM_VAR_NOINIT)
  FiM_GaaFidPermissionState[FIM_TOTAL_NUM_OF_FIDS];

/* Global array to store FID Available state */
#if(FIM_AVAILABILITY_SUPPORT == STD_ON)
extern VAR(boolean, FIM_VAR_NOINIT)
  FiM_GaaFidAvailableState[FIM_TOTAL_NUM_OF_FIDS];
#endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */

#define FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define FIM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global array to store inhibition counter for all FID's */
extern VAR(FiM_FidsSizeType, FIM_VAR_NOINIT)
  FiM_GaaFidInhibitCounter[FIM_TOTAL_NUM_OF_FIDS];

#define FIM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO */



#if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
#define FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* Global array to store Dem component FAILED state */
extern VAR(boolean, FIM_VAR_NOINIT)
  FiM_GaaComponentFailedState[FIM_TOTAL_NUM_OF_DEM_COMPONENT];

#define FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* End of FIM_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
