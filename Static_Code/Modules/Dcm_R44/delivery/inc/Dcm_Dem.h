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
**  SRC-MODULE: Dcm_Dem.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Dem.c                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   LamNV10        AR440 Implementation                **
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DEM_H
#define DCM_DEM_H

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
  uint32 DTC
  , Dem_UdsStatusByteType DTCStatusOld
  , Dem_UdsStatusByteType DTCStatusNew);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_DEM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
