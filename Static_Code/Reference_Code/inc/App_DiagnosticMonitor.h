/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/

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
**  FILE-NAME : App_DiagnosticMonitor.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Dem                                                   **
**                                                                            **
**  PURPOSE   : Sample code for testing Dem module                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/
#ifndef DEM_DIAGMON_H
#define DEM_DIAGMON_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"                  /* Standard type header */

#include "Dem.h"
#include "Dem_Ram.h"
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_8
#include "SWC_DiagnosticMonitor_MemMap.h"

extern uint8 Dem_TestCaseResult[15];

extern uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPriMem;
extern uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPerMem;
extern uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesMirMem;
extern uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesUDMem;

extern uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesPriMem;
extern uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesPerMem;
extern uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesMirMem;
extern uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesUDMem;
extern uint8 SwcDem_ClearEventAllowedInvoked;
extern sint8 AppDiagnosticMonitor_FaultDetectionCounter;
extern VAR(uint8, RTE_DATA) AppDiagnosticMonitor_MonitorStatus;
extern uint8 SwcDem_InitMonitorForEventInvoked;
extern uint8 SwcDem_EventStatusChangedInvoked;

extern VAR(uint8, RTE_DATA) LaaDestBuffer[];



extern VAR(Dem_IndicatorStatusType, RTE_DATA) IndicatorStatus;

#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_8
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_16
#include "SWC_DiagnosticMonitor_MemMap.h"
extern VAR(uint16, RTE_DATA) LaaBufSize;
#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_16
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_BOOLEAN
#include "SWC_DiagnosticMonitor_MemMap.h"

extern boolean AppDiagnosticMonitor_OverflowIndication;
extern boolean AppDiagnosticMonitor_ComponentFailed;
extern boolean AppDiagnosticMonitor_SuppressionStatus;
extern boolean AppDiagnosticMonitor_FiMPermission;

#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_BOOLEAN
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_32
#include "SWC_DiagnosticMonitor_MemMap.h"

extern uint32 SwcDem_TestPhase;
extern uint32 SwcDem_TestFailedCtr;

extern uint32 Distance;

#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_32
#include "SWC_DiagnosticMonitor_MemMap.h"


#endif 

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
