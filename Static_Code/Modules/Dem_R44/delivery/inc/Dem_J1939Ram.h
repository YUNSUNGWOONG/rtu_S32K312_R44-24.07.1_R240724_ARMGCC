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
**  SRC-MODULE: Dem_J1939Ram.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Config.c                                     **
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

#ifndef DEM_J1939RAM_H
#define DEM_J1939RAM_H
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Necessary in logic */
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */

#include "Dem.h"

#if (DEM_J1939_SUPPORT == STD_ON)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
Dem_PriEvMemChronoOrder[DEM_MAX_NUMBER_EVENT_ENTRY_PRI];
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
Dem_UDEvMemChronoOrder[DEM_MAX_NUMBER_EVENT_ENTRY_UD];
#endif
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
    Dem_PriEvMemChronoOrderNextLoc;
#if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
    Dem_UDEvMemChronoOrderNextLoc;
#endif
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
    Dem_J1939FirstDtcLoc[DEM_NUMBER_OF_DEM_CLIENT];
#endif
#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
extern VAR(uint8, DEM_VAR) Dem_J1939NextRatioIndex;
#endif
#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#endif


/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Necessary in logic */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */


#endif
