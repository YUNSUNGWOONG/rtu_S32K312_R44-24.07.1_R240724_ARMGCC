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
**  SRC-MODULE: Dem_NvData.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_NvData.h                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/



#ifndef DEM_NVDATA_H
#define DEM_NVDATA_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"
#include "NvM.h"              /* NVRAM manager symbols Header File */

#define DEM_START_SEC_CODE
#include "MemMap.h"

/* @Trace: DEM_SUD_DATATYPE_003 */
extern FUNC(NvM_RequestResultType, DEM_CODE)
Dem_NvData_GetNvMErrorStatus(NvM_BlockIdType BlockId);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_GetNvMBlockId(
  const Dem_NvDataIdType NvDataId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_NumOfEventMemoryEntryType MemLocation,  
  P2VAR(NvM_BlockIdType, AUTOMATIC, DEM_APPL_DATA) BlockId);
  
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_ReadNonVolatileData(
  const Dem_NvDataIdType NvDataId);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_WriteNonVolatileData(
  const Dem_NvDataIdType NvDataId);

extern FUNC(boolean, DEM_CODE) Dem_NvData_WaitNvmFinishJob(
  const uint8 Filter,
  const boolean Direction);
  
#define DEM_STOP_SEC_CODE
#include "MemMap.h"


#endif

