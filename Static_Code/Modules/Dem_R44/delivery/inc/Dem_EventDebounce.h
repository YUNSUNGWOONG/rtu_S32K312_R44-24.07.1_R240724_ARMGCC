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
**  SRC-MODULE: Dem_EventDebounce.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_EventDebounce.c                              **
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
#ifndef DEM_EVENTDEBOUNCE_H
#define DEM_EVENTDEBOUNCE_H
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

extern FUNC(void, DEM_CODE) Dem_InitDebounce(void);

#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
extern FUNC(void, DEM_CODE)Dem_ProcessDebounceTimer(void);
#endif

extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetFDCDebounceTimeBased(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_VAR) FDC);

extern FUNC(void, DEM_CODE) Dem_ResetFaultDectectionCounter(
  Dem_EventIdType EventId);

#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
extern  FUNC(boolean, DEM_CODE) Dem_ProcessDebounceCounterBased(
  const Dem_NumOfDebounceType DebounceId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
extern FUNC(boolean, DEM_CODE)Dem_ProcessDebounceTimeBased(
  const Dem_NumOfDebounceType DebounceId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DEM_INDICATOR_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


