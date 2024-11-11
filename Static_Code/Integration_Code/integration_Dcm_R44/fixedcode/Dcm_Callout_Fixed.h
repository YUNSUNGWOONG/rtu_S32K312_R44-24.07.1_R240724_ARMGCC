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
**  SRC-MODULE: Dcm_Callout_Fixed.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the declaration for Dcm callout functions  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 1.0.0   27-10-2021    K.H Kim          Initial Version                     **
*******************************************************************************/

#ifndef DCM_CALLOUT_FIXED_H
#define DCM_CALLOUT_FIXED_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Version.h"
#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
#include "Dcm_Externals.h"
#else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
#include "Dcm_CallOuts.h"
#endif

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"
extern FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_Internal_GetProgConditions
  (P2VAR(Dcm_ProgConditionsType, AUTOMATIC,DCM_APPL_DATA) ProgConditions);

extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Internal_SetProgConditions
  (P2CONST(Dcm_ProgConditionsType, AUTOMATIC,DCM_APPL_CONST) ProgConditions);
#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION != 4)
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_GetImagePublicKey
  (P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ImagePublicKey);
#endif

#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

#endif /* End DCM_CALLOUT_FIXED_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
