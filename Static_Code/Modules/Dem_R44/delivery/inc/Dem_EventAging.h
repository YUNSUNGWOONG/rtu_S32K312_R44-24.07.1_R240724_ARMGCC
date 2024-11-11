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
**  SRC-MODULE: Dem_EventAging.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_EventAging.c                                 **
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

#ifndef DEM_EVENTAGING_H
#define DEM_EVENTAGING_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(boolean, DEM_CODE) Dem_EventAgingOnEventPassed(
  const Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  Dem_NumOfEventMemoryEntryType MemLocation);  

extern FUNC(void, DEM_CODE) Dem_EventAgingOnOperationCycleChanged(
  Dem_EventIdType EventId,
  Dem_EventMemoryEntryPtrType MemEntry,
  const Dem_DTCOriginType DTCOrigin,
  const uint8 OperationCycleId);

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DEM_INDICATOR_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/



