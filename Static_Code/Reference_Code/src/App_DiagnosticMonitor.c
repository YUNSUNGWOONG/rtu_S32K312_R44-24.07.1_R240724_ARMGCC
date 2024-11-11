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
**  FILE-NAME : App_DiagnosticMonitor.c                                       **
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

/*******************************************************************************
 **                      Include Section                                      **
 ******************************************************************************/
#include "Rte_SWC_DiagnosticMonitor.h"
#include "App_DiagnosticMonitor.h"
#include "Det.h"
#include "Dem.h"

/*******************************************************************************
 **                       Global Data                                          **
 *******************************************************************************/
#define TC01_OPERATION_CYCLE          5U
#define TC02_STORE_EVENT_FAILED       6U
#define TC03_EVENT_STATUS_CHANGED     7U

enum App_Diagnostic_Monitor_TestStep_e
{

  APP_DIAGNOSTIC_MONITOR_Dem_SetOperationCycleState_OpertationCycle_01 = 1,
  APP_DIAGNOSTIC_MONITOR_Dem_EnableCondtion_0_SetEnableCondition_TRUE = 3,
  APP_DIAGNOSTIC_MONITOR_Dem_EnableCondtion_0_SetEnableCondition_FALSE = 4,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT1_FAILED = 5,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT2_FAILED = 6,

  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT1_PASSED = 9,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT2_PASSED = 10,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT3_PASSED = 11,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT4_PASSED = 12,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT3_FAILED = 14,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT4_FAILED = 15,
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_EVENT01 = 16,
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_UDS_ALL_DTC = 17,
  /* 18 is reserve for Clear Client Id 1*/
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_OBD_ALL_DTC = 19,
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient1_SelectDTC_USERDEFINED = 20,
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_UDS_ALL_DTC_MIRROR = 21,
  /* 22 is reserve for Clear Client Id 1*/
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient1_SelectDTC_UDS_ALL_DTC = 23,
  APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_EVENT06 = 24,

  /*DET ID*/
  APP_DIAGNOSTIC_MONITOR_DET_ReportError = 46,
  APP_DIAGNOSTIC_MONITOR_DET_ReportRuntimeError = 47,
  APP_DIAGNOSTIC_MONITOR_DET_ReportTransientFault = 48,

  APP_DIAGNOSTIC_MONITOR_INITIALIZED = 49,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_1_FAILED = 50,
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_2_FAILED, /*51*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_3_FAILED, /*52*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_1_PASSED, /*53*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_2_PASSED, /*54*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_3_PASSED, /*55*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_PRIMARY, /*56*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_MIRROR, /*57*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_PERMANENT,/*58*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_USERDEFINED,/*59*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_PRIMARY,/*60*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_MIRROR,/*61*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_PERMANENT,/*62*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_USERDEFINED,/*63*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_PRIMARY,/*64*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_MIRROR,/*65*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_PERMANENT,/*66*/
  APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_USERDEFINED,/*67*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_PRIMARY,/*68*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_MIRROR,/*69*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_PERMANENT,/*70*/
  APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_USERDEFINED,/*71*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT7_FAILED,/*72*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT8_FAILED,/*73*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT9_FAILED,/*74*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT10_FAILED,/*75*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT11_FAILED,/*76*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT12_FAILED,/*77*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT7_PASSED,/*78*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT8_PASSED,/*79*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT9_PASSED,/*80*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT10_PASSED,/*81*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT11_PASSED,/*82*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT12_PASSED,/*83*/
  APP_DIAGNOSTIC_MONITOR_SetStorageCondition_StorageGroup1_TRUE,/*84*/
  APP_DIAGNOSTIC_MONITOR_SetStorageCondition_StorageGroup1_FALSE,/*85*/

  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_FAILED,/*86*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_FAILED,/*87*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_PASSED,/*88*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_PASSED,/*89*/

  APP_DIAGNOSTIC_MONITOR_Dem_SetDtr_DTR_Dtr0,/*90*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetDtr_DTR_Dtr1_OUTSIDE_LOW,/*91*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetDtr_DTR_Dtr1_OUTSIDE_HIGH,/*92*/

  APP_DIAGNOSTIC_MONITOR_Dem_ControlDTCSuppression_GetDTCSuppression,/*93*/
  APP_DIAGNOSTIC_MONITOR_Dem_ControlDTCSuppression_SetDTCSuppression_TRUE,/*94*/
  APP_DIAGNOSTIC_MONITOR_Dem_ControlDTCSuppression_SetDTCSuppression_FALSE,/*95*/

  APP_DIAGNOSTIC_MONITOR_ControlEventAvailable_SetEventAvailable_DEM_E_TEST_EVENT6_TRUE ,/*96*/
  APP_DIAGNOSTIC_MONITOR_ControlEventAvailable_SetEventAvailable_DEM_E_TEST_EVENT6_FALSE ,/*97*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_PREFAILED ,/*98*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_PREPASSED ,/*99*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_PREFAILED ,/*100*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_PREPASSED ,/*101*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_GetFaultDetectionCounter ,/*102*/
  APP_DIAGNOSTIC_MONITOR_IUPMR_SET ,/*103*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_PrestoreFreezeFrame ,/*104*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_ClearPrestoredFreezeFrame ,/*105*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx ,/*106*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx ,/*107*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT3_SetWIRStatus_TRUE ,/*108*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT3_SetWIRStatus_FALSE ,/*109*/
  APP_DIAGNOSTIC_MONITOR_Indicator0_GetIndicatorStatus,  /*110*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData_FAILED, /*111*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData_PASSED, /*112*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_GetEventExtendedDataRecordEx, /*113*/
  APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_GetMonitorStatus, /*114*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_PASSED,/*115*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_FAILED,/*116*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_GetFaultDetectionCounter, /*117*/
  APP_DIAGNOSTIC_MONITOR_DemComponent0_Dem_GetComponentFailed, /*118*/
  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_GetEventUdsStatus, /*119 */

  APP_DIAGNOSTIC_MONITOR_FIM_FiMFID0_GetFunctionPermission = 200,  /*200*/
  APP_DIAGNOSTIC_MONITOR_FIM_FiMFID0_SetFunctionAvailable_TRUE,  /*201*/
  APP_DIAGNOSTIC_MONITOR_FIM_FiMFID0_SetFunctionAvailable_FALSE,  /*202*/

  APP_DIAGNOSTIC_MONITOR_FIM_FiMFID1_GetFunctionPermission,  /*203*/
  APP_DIAGNOSTIC_MONITOR_FIM_FiMFID1_SetFunctionAvailable_TRUE,  /*204*/
  APP_DIAGNOSTIC_MONITOR_FIM_FiMFID1_SetFunctionAvailable_FALSE,  /*205*/



} App_Diagnostic_Monitor_TestStep_e;


#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_8
#include "SWC_DiagnosticMonitor_MemMap.h"
uint8 Dem_TestCaseResult[15] =
{ 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };
uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPriMem = 0U;
uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPerMem = 0U;
uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesMirMem = 0U;
uint8 AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesUDMem = 0U;
uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesPriMem = 0U;
uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesPerMem = 0U;
uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesMirMem = 0U;
uint8 AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesUDMem = 0U;

uint8 AppDiagnosticMonitor_UDSStatus = 0U;

sint8 AppDiagnosticMonitor_FaultDetectionCounter = 0;
uint8 SwcDem_InitMonitorForEventInvoked = 0U;
uint8 SwcDem_ComponentStatusChangedInvoked = 0U;
uint8 SwcDem_EventStatusChangedInvoked = 0U;
uint8 SwcDem_ClearEventAllowedInvoked = 0U;
VAR(uint8, RTE_DATA) AppDiagnosticMonitor_MonitorStatus = 0U;
VAR(uint8, RTE_DATA) LaaDestBuffer[DEM_SIZE_OF_EVENT_DATA];
VAR(Dem_IndicatorStatusType, RTE_DATA) IndicatorStatus;

#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_8
#include "SWC_DiagnosticMonitor_MemMap.h"


#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_16
#include "SWC_DiagnosticMonitor_MemMap.h"
VAR(uint16, RTE_DATA) LaaBufSize = 20U;
#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_16
#include "SWC_DiagnosticMonitor_MemMap.h"


#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_BOOLEAN
#include "SWC_DiagnosticMonitor_MemMap.h"
boolean AppDiagnosticMonitor_OverflowIndication = FALSE;
boolean AppDiagnosticMonitor_ComponentFailed = FALSE;

boolean AppDiagnosticMonitor_SuppressionStatus = FALSE;
boolean AppDiagnosticMonitor_FiMPermission = FALSE;
#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_BOOLEAN
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_VAR_INIT_32
#include "SWC_DiagnosticMonitor_MemMap.h"
uint32 SwcDem_TestPhase = 0U;
uint32 SwcDem_TestFailedCtr = 0U;
#define SWC_DiagnosticMonitor_STOP_SEC_VAR_INIT_32
#include "SWC_DiagnosticMonitor_MemMap.h"


#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

/*******************************************************************************
 **                      Function Definitions                                  **
 *******************************************************************************/

/*******************************************************************************
 ** Function Name        : InitMonitorForEvent_DEM_E_TEST                      **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : The Dem module provides the interface               **
 **                        InitMonitorForEvent* to trigger the initalization   **
 **                        of a diagnostic monitor                             **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : InitMonitorReason                                   **
 **                        - DEM_INIT_MONITOR_CLEAR: Event was cleared         **
 **                          and all internal values and states are reset      **
 **                                                                            **
 **                        - DEM_INIT_MONITOR_RESTART: Operation cycle of      **
 **                          the event was (re-)started.                       **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     : RTE_E_OK                                            **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) InitMonitorForEvent_DEM_E_TEST(
 VAR(Dem_InitMonitorReasonType, AUTOMATIC) InitMonitorReason)
{
  switch (InitMonitorReason)
  {
  case DEM_INIT_MONITOR_CLEAR:
    break;
  case DEM_INIT_MONITOR_RESTART:
    break;
  default:
    break;
  }

  SwcDem_InitMonitorForEventInvoked = 1;

  return RTE_E_OK;
}



/*******************************************************************************
 **                      Function Definitions                                  **
 *******************************************************************************/

/*******************************************************************************
 ** Function Name        : CallbackComponentStatusChanged_ComponentStatusChanged**
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Callback Component Status Changed                   **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : ComponentFailedStatus                               **
 **                        - DEM_INIT_MONITOR_CLEAR: Event was cleared         **
 **                          and all internal values and states are reset      **
 **                                                                            **
 **                        - DEM_INIT_MONITOR_RESTART: Operation cycle of      **
 **                          the event was (re-)started.                       **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     : RTE_E_OK                                            **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CallbackComponentStatusChanged_ComponentStatusChanged(
 VAR(boolean, AUTOMATIC) ComponentFailedStatus)
{
	SwcDem_ComponentStatusChangedInvoked++;
	AppDiagnosticMonitor_ComponentFailed = ComponentFailedStatus;
    return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBClrEvt_DEM_E_TEST_EVENT1                          **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : The Dem module provides the interface               **
 **                        CallbackClearEventAllowed* to gets the permission   **
 **                        to clear a specific event from the SW-C             **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Allowed                                             **
 **                        - TRUE:  Permission                                 **
 **                                                                            **
 **                        - FALSE: No permission                              **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     : RTE_E_OK                                            **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBClrEvt_DEM_E_TEST_EVENT1(
 P2VAR(AUTOSAR_boolean, AUTOMATIC, RTE_APPL_DATA) Allowed)
{
  *Allowed = RTE_TRUE;
  SwcDem_ClearEventAllowedInvoked = 1U;
  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBStatusEvt_DEM_E_TEST_EVENT1                       **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Triggers on changes of the event status byte        **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : EventStatusOld                                      **
 **                        - UDS DTC status byte of event before change        **
 **                        EventStatusNew                                      **
 **                       - UDS DTC status byte of event after change          **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     : RTE_E_OK                                            **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(void, SWC_DiagnosticMonitor_CODE) CBStatusEvt_DEM_E_TEST_EVENT1(
 VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,
 VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
  SwcDem_EventStatusChangedInvoked = 1;
//  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBStatusEvt_E_MODE_CHANGE_HS_CAN1                   **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Triggers on changes of the event status byte        **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : EventStatusOld                                      **
 **                        - UDS DTC status byte of event before change        **
 **                        EventStatusNew                                      **
 **                       - UDS DTC status byte of event after change          **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     : RTE_E_OK                                            **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(void, SWC_DiagnosticMonitor_CODE) CBStatusEvt_E_MODE_CHANGE_HS_CAN1(
 VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,
 VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew)
{
//  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0001                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0001_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0001(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0xA5;
  Data[1] = 0xB5;
  Data[2] = 0xC5;

  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0002                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0002_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/

FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0002(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,
 VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0x01;
  Data[1] = 0x02;
  Data[2] = 0x03;

  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0003                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0003_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0003(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0xA9;
  Data[1] = 0xB9;
  Data[2] = 0xC9;

  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0004                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0004_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0004(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0xA6;

  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0005                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0005_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0005(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0xA7;
  Data[1] = 0xB7;
  Data[2] = 0xC7;

  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0006                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0006_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0006(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0xA8;

  return RTE_E_OK;
}


/*******************************************************************************
 ** Function Name        : CBReadData_DE_0008                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current value of the data element      **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0008_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0008(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = 0xA9;
  Data[1] = 0xB9;
  Data[2] = 0xC9;
  Data[3] = 0xE9;
  Data[4] = 0xF9;
  Data[5] = 0x19;
  Data[6] = 0x39;
  Data[7] = 0x59;

  return RTE_E_OK;
}


/*******************************************************************************
 ** Function Name        : CBReadData_DE_0009                                  **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current distance value of the data     **
 **                         element                                            **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0009_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
uint32 Distance  = 0;
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0009(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = Distance&0x00FFU;
  Data[1] = (Distance&0xFF00U)>>8U;
  Data[2] = (Distance&0xFF0000U)>>16U;
  Data[3] = (Distance&0xFF000000U)>>24U;
  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : CBReadData_DE_0010                                 **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Requests the current Time value of the data     **
 **                         element                                            **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : Data -containing the value of the data element      **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     :                                                     **
 **  - RTE_E_OK : Operation was successful                                     **
 *  - RTE_E_CSDataServices_DE_0010_E_NOT_OK : Operation failed                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/
uint32 TimeSpan = 0;
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0010(
 P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,  VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0)
{
  Data[0] = TimeSpan&0x00FFU;
  Data[1] = (TimeSpan&0xFF00U)>>8U;
  Data[2] = (TimeSpan&0xFF0000U)>>16U;
  Data[3] = (TimeSpan&0xFF000000U)>>24U;
  return RTE_E_OK;
}

/*******************************************************************************
 ** Function Name        : DiagnosticMonitor                                   **
 **                                                                            **
 ** Service ID           : None                                                **
 **                                                                            **
 ** Description          : Sample runnable                                     **
 **                                                                            **
 ** Sync/Async           : Synchronous                                         **
 **                                                                            **
 ** Re-entrancy          : Non Reentrant                                       **
 **                                                                            **
 ** Input Parameters     : None                                                **
 **                                                                            **
 ** InOut parameter      : None                                                **
 **                                                                            **
 ** Output Parameters    : None                                                **
 **                                                                            **
 ** Return parameter     : None                                                **
 **                                                                            **
 ** Preconditions        :                                                     **
 **                                                                            **
 ** Remarks              :                                                     **
 *******************************************************************************/

FUNC(void, SWC_DiagnosticMonitor_CODE) DiagnosticMonitor(void)
{
  VAR(Std_ReturnType, RTE_DATA) LddRetVal = RTE_E_OK;

  switch (SwcDem_TestPhase)
  {
  case APP_DIAGNOSTIC_MONITOR_DET_ReportError:
    LddRetVal = Rte_Call_DS000_ReportError(0x80, 0x11);
    if (RTE_E_OK == LddRetVal)
    {
      /* Do nothing */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_DET_ReportRuntimeError:
    LddRetVal = Rte_Call_DS000_ReportRuntimeError(0x80, 0x12);
    if (RTE_E_OK == LddRetVal)
    {
      /* Do nothing */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_DET_ReportTransientFault:
    LddRetVal = Det_ReportTransientFault(0x1001, 0x00, 0x80, 0x15);
    if (RTE_E_OK == LddRetVal)
    {
      /* Do nothing */
    }
    break;

  /******************************************************************************************/
  case APP_DIAGNOSTIC_MONITOR_Dem_SetOperationCycleState_OpertationCycle_01:
    LddRetVal = Rte_Call_OpCycle_POWER_CYCLE_RestartOperationCycle();
    if (RTE_E_OK == LddRetVal)
    {
      Dem_TestCaseResult[TC01_OPERATION_CYCLE] = 1U;
    }

    break;

    /******************************************************************************************/
    /*                    Enable Condition                                                    */
    /******************************************************************************************/
  case APP_DIAGNOSTIC_MONITOR_Dem_EnableCondtion_0_SetEnableCondition_TRUE:
    LddRetVal = Rte_Call_EnableCond_EnableCondtion_0_SetEnableCondition(TRUE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_EnableCondtion_0_SetEnableCondition_FALSE:
    LddRetVal = Rte_Call_EnableCond_EnableCondtion_0_SetEnableCondition(FALSE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

    /******************************************************************************************/
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT1_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT1_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK == LddRetVal)
    {
      Dem_TestCaseResult[TC02_STORE_EVENT_FAILED] = 1U;
    }

    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT2_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT2_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case 7:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT1_SetEventStatus(
    DEM_EVENT_STATUS_PREFAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case 8:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT2_SetEventStatus(
    DEM_EVENT_STATUS_PREFAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT3_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT3_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT4_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT4_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT7_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT7_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT8_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT8_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT9_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT9_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT10_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT10_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT11_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT11_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT12_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT12_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

    /*OBD*/
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_1_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_2_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_3_FAILED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus(
    DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT1_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT1_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK == LddRetVal)
    {
      Dem_TestCaseResult[TC03_EVENT_STATUS_CHANGED] = 1U;
    }

    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT2_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT2_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT3_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT1_SetEventStatus(
    DEM_EVENT_STATUS_PREPASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT4_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT2_SetEventStatus(
    DEM_EVENT_STATUS_PREPASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT7_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT7_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT8_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT8_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT9_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT9_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT10_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT10_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT11_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT11_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT12_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT12_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_1_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_2_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_OBD_EVENT_3_PASSED:
    LddRetVal = Rte_Call_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus(
    DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case   APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_FAILED:/*86*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT5_SetEventStatus(
        DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_FAILED:/*87*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT6_SetEventStatus(
        DEM_EVENT_STATUS_FAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_PASSED:/*88*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT5_SetEventStatus(
        DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_PASSED:/*89*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT6_SetEventStatus(
        DEM_EVENT_STATUS_PASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
    /******************************************************************************************/

    /******************************************************************************************/
  case APP_DIAGNOSTIC_MONITOR_Indicator0_GetIndicatorStatus:
  {
    /**
     * Dem_IndicatorStatusType
     *
     * DEM_INDICATOR_OFF : Indicator off mode
     * DEM_INDICATOR_CONTINUOUS: Indicator continuously on mode
     * DEM_INDICATOR_BLINKING: Indicator blinking mode
     * DEM_INDICATOR_BLINK_CONT: Indicator blinking or continuously on mode
     */
//    VAR(Dem_IndicatorStatusType, RTE_DATA) IndicatorStatus;

    /* Refer to the dem configuration
     * (1) DemGeneral/Indicator
     * (2) DemConfigSet/DemEventParamenter(DEM_E_TEST_EVENT1,DEM_E_TEST_EVENT2)
     *     /DemEventClass/DemIndicatorAttribute/DemIndicatorRef
     */
    LddRetVal = Rte_Call_IndStatus_DemIndicator_0_GetIndicatorStatus(
        &IndicatorStatus);
    if (RTE_E_OK == LddRetVal)
    {
//      if (DEM_INDICATOR_OFF != IndicatorStatus)
//      {
//        /* Do something */
//      }
    }

    break;
  }

    /********************************** QT ClearDTC *******************************************/
  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_EVENT01:
    LddRetVal = Rte_Call_ClearDTC_DemClient0_SelectDTC(0xDD01,
        DEM_DTC_FORMAT_UDS,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }

//    LddRetVal = Dem_GetDTCSelectionResultForClearDTC(0U);
//    if (RTE_E_OK != LddRetVal)
//    {
//      /* do something */
//    }

    LddRetVal = Rte_Call_ClearDTC_DemClient0_ClearDTC();

    if (4U == LddRetVal)
    {
      SwcDem_TestPhase = 18;
    }
    break;


    /********************************** QT ClearDTC *******************************************/
  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_EVENT06:
    LddRetVal = Rte_Call_ClearDTC_DemClient0_SelectDTC(0x400F01,
        DEM_DTC_FORMAT_UDS,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }

    LddRetVal = Rte_Call_ClearDTC_DemClient0_ClearDTC();

    if (4U == LddRetVal)
    {
      SwcDem_TestPhase = 18;
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient1_SelectDTC_USERDEFINED:
    LddRetVal = Rte_Call_ClearDTC_DemClient1_SelectDTC(0x800F01,
        DEM_DTC_FORMAT_UDS, 0x0101U);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }

    LddRetVal = Rte_Call_ClearDTC_DemClient1_ClearDTC();
    if (4U == LddRetVal)
    {
      SwcDem_TestPhase = 22;
    }
    break;

    /******************************************************************************************/
    /*                    Clear DTC                                                           */
    /******************************************************************************************/
  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_UDS_ALL_DTC_MIRROR:
    LddRetVal = Rte_Call_ClearDTC_DemClient0_SelectDTC(0xFFFFFF,
           DEM_DTC_FORMAT_UDS,
           DEM_DTC_ORIGIN_MIRROR_MEMORY);
       if (RTE_E_OK != LddRetVal)
       {
         /* do something */
       }

   //    LddRetVal = Dem_GetDTCSelectionResultForClearDTC(0U);
   //    if (RTE_E_OK != LddRetVal)
   //    {
   //      /* do something */
   //    }

       LddRetVal = Rte_Call_ClearDTC_DemClient0_ClearDTC();
       if (4U == LddRetVal)
       {
         SwcDem_TestPhase = 18;
       }
       break;

  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_UDS_ALL_DTC:
    LddRetVal = Rte_Call_ClearDTC_DemClient0_SelectDTC(0xFFFFFF,
        DEM_DTC_FORMAT_UDS,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }

//    LddRetVal = Dem_GetDTCSelectionResultForClearDTC(0U);
//    if (RTE_E_OK != LddRetVal)
//    {
//      /* do something */
//    }

    LddRetVal = Rte_Call_ClearDTC_DemClient0_ClearDTC();
    if (4U == LddRetVal)
    {
      SwcDem_TestPhase = 18;
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient1_SelectDTC_UDS_ALL_DTC:
    LddRetVal = Rte_Call_ClearDTC_DemClient1_SelectDTC(0xFFFFFF,
        DEM_DTC_FORMAT_UDS,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }

//    LddRetVal = Dem_GetDTCSelectionResultForClearDTC(0U);
//    if (RTE_E_OK != LddRetVal)
//    {
//      /* do something */
//    }

    LddRetVal = Rte_Call_ClearDTC_DemClient1_ClearDTC();
    if (4U == LddRetVal)
    {
      SwcDem_TestPhase = 22;
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_ClearDTC_DemClient0_SelectDTC_OBD_ALL_DTC:
    LddRetVal = Rte_Call_ClearDTC_DemClient0_SelectDTC(0xFFFFFF,
        DEM_DTC_FORMAT_OBD,
        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }

    LddRetVal = Rte_Call_ClearDTC_DemClient0_ClearDTC();
    if (4U == LddRetVal)
    {
      SwcDem_TestPhase = 18;
    }
    break;

  case 18:
    LddRetVal = Rte_Call_ClearDTC_DemClient0_ClearDTC();
    if (RTE_E_OK == LddRetVal)
    {
      SwcDem_TestPhase = 0U;
    }
    break;

  case 22:
    LddRetVal = Rte_Call_ClearDTC_DemClient1_ClearDTC();
    if (RTE_E_OK == LddRetVal)
    {
      SwcDem_TestPhase = 0U;
    }
    break;
    /********************************** QT Storage Condition ************************************/

    /******************************* QT Aging Diagnostic ***********************************/
    /* Configure DemAgingCycleCounterThreshold is 1 and DemAgingCycleCounterThresholdForTFSLC is 2 for DemDTCAttributes0
     * Configure DemStatusBitHandlingTestFailedSinceLastClear (overview) is DEM_STATUS_BIT_AGING_AND_DISPLACEMENT
     * Configure DEM_E_TEST_EVENT1 refer UDS_DTC_0xDD01/DemDTCAttributes0
     * Perform test to set failed event status for DEM_E_TEST_EVENT1
     * Call RestartOperationCycle first time
     * Call RestartOperationCycle second time */

    /***********************************************************************************/
  case 28:
  {
    VAR(uint8, RTE_DATA) NumberOfEventMemoryEntriesClientId0 = 0U;
    LddRetVal =
        Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries(
            &NumberOfEventMemoryEntriesClientId0);
    if (RTE_E_OK != LddRetVal)
    {
      if (1U != NumberOfEventMemoryEntriesClientId0)
      {
        /* do something */
      }
    }
    break;
  }

  case 29:
  {
    VAR(uint8, RTE_DATA) NumberOfEventMemoryEntriesClientId1 = 0U;
    LddRetVal =
        Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries(
            &NumberOfEventMemoryEntriesClientId1);

    if (RTE_E_OK != LddRetVal)
    {
      if (1U != NumberOfEventMemoryEntriesClientId1)
      {
        /* do something */
      }
    }
    break;
  }

  case 30:
  {
    boolean LblOverflowIndication;
//    LddRetVal = Dem_GetEventMemoryOverflow(0U, DEM_DTC_ORIGIN_PRIMARY_MEMORY,
//        &LblOverflowIndication);
    LddRetVal =
        Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow(
            &LblOverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      if (RTE_TRUE != LblOverflowIndication)
      {
        /* do something */
      }
    }
    break;
  }

  case APP_DIAGNOSTIC_MONITOR_SetStorageCondition_StorageGroup1_TRUE:/*84*/

    LddRetVal = Rte_Call_StorageCond_DemStorageCondition1_SetStorageCondition(
        TRUE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_SetStorageCondition_StorageGroup1_FALSE:/*85*/
    LddRetVal = Rte_Call_StorageCond_DemStorageCondition1_SetStorageCondition(
        FALSE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_INITIALIZED:
    AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPriMem = 0U;
    AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPerMem = 0U;
    AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesMirMem = 0U;
    AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesUDMem = 0U;
    AppDiagnosticMonitor_OverflowIndication = FALSE;

    break;

  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_PRIMARY:
    LddRetVal =
    Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries(
        &AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPriMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_MIRROR:
    LddRetVal =
    Rte_Call_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries(
        &AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesMirMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_PERMANENT:
    LddRetVal =
        Rte_Call_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries(
            &AppDiagnosticMonitor_Client0_NumOfStoredEvtMemEntryiesPerMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_0_USERDEFINED:
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_PRIMARY:
    LddRetVal =
    Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow(
        &AppDiagnosticMonitor_OverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_MIRROR:
    LddRetVal =
    Rte_Call_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow(
        &AppDiagnosticMonitor_OverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_PERMANENT:
    LddRetVal =
    Rte_Call_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow(
        &AppDiagnosticMonitor_OverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_0_USERDEFINED:
    break;
  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_PRIMARY:
    LddRetVal =
    Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries(
        &AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesPriMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_MIRROR:
    LddRetVal =
    Rte_Call_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries(
        &AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesMirMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_PERMANENT:
    LddRetVal =
        Rte_Call_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries(
            &AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesPerMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_GetNumberOfEventMemoryEntries_Client_1_USERDEFINED:

    LddRetVal =
        Rte_Call_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries(
            &AppDiagnosticMonitor_Client1_NumOfStoredEvtMemEntryiesUDMem);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_PRIMARY:
    LddRetVal =
    Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow(
        &AppDiagnosticMonitor_OverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_MIRROR:
    LddRetVal =
    Rte_Call_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow(
        &AppDiagnosticMonitor_OverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_PERMANENT:
    LddRetVal =
    Rte_Call_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow(
        &AppDiagnosticMonitor_OverflowIndication);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_GetEventMemoryOverflow_Client_1_USERDEFINED:
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetDtr_DTR_Dtr0:
        LddRetVal =
            Rte_Call_DTR_Dtr0_SetDTR(
                10 /*TestResult*/,
                5 /*LowerLimit*/,
                20 /*UpperLimit*/,
                DEM_DTR_CTL_NORMAL /*Ctrlval*/
                );
            if (RTE_E_OK != LddRetVal)
            {
              /* do something */
            }

    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetDtr_DTR_Dtr1_OUTSIDE_LOW:
    LddRetVal =
        Rte_Call_DTR_Dtr1_SetDTR(
            1 /*TestResult*/,
            2 /*LowerLimit*/,
            100 /*UpperLimit*/,
            DEM_DTR_CTL_NORMAL /*Ctrlval*/);
        if (RTE_E_OK != LddRetVal)
        {
          /* do something */
        }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetDtr_DTR_Dtr1_OUTSIDE_HIGH:
    LddRetVal =
        Rte_Call_DTR_Dtr1_SetDTR(
            99 /*TestResult*/,
            2 /*LowerLimit*/,
            98 /*UpperLimit*/,
            DEM_DTR_CTL_NORMAL /*Ctrlval*/);
        if (RTE_E_OK != LddRetVal)
        {
          /* do something */
        }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_ControlDTCSuppression_GetDTCSuppression:

    LddRetVal = Rte_Call_ControlDTCSuppression_GetDTCSuppression(0,
        &AppDiagnosticMonitor_SuppressionStatus);

    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_ControlDTCSuppression_SetDTCSuppression_TRUE:

    LddRetVal = Rte_Call_ClearDTC_DemClient0_SelectDTC(0x400F01,
        DEM_DTC_FORMAT_UDS,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }


    LddRetVal = Rte_Call_ControlDTCSuppression_SetDTCSuppression(0, TRUE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_ControlDTCSuppression_SetDTCSuppression_FALSE:
    LddRetVal = Rte_Call_ControlDTCSuppression_SetDTCSuppression(0, FALSE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_ControlEventAvailable_SetEventAvailable_DEM_E_TEST_EVENT6_TRUE:
    LddRetVal =
        Rte_Call_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable(
            TRUE);
        if (RTE_E_OK != LddRetVal)
        {
          /* do something */
        }
    break;

  case APP_DIAGNOSTIC_MONITOR_ControlEventAvailable_SetEventAvailable_DEM_E_TEST_EVENT6_FALSE:
    LddRetVal =
        Rte_Call_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable(
            FALSE);
        if (RTE_E_OK != LddRetVal)
        {
          /* do something */
        }
    break;

  case  APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_PREFAILED:/*98*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT5_SetEventStatus(
        DEM_EVENT_STATUS_PREFAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT5_PREPASSED: /*99*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT5_SetEventStatus(
        DEM_EVENT_STATUS_PREPASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_PREFAILED:/*100*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT6_SetEventStatus(
        DEM_EVENT_STATUS_PREFAILED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_PREPASSED: /*101*/
    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT6_SetEventStatus(
        DEM_EVENT_STATUS_PREPASSED);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT6_GetFaultDetectionCounter:
    Dem_GetFaultDetectionCounter(60, &AppDiagnosticMonitor_FaultDetectionCounter);
    break;

  case APP_DIAGNOSTIC_MONITOR_IUPMR_SET:
    Rte_Call_OpCycle_POWER_CYCLE_RestartOperationCycle();
    Rte_Call_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition(DEM_IUMPR_DEN_STATUS_REACHED);
    Rte_Call_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition(DEM_IUMPR_DEN_STATUS_REACHED);
    Rte_Call_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect();
    Rte_Call_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect();
    Rte_Call_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect();
    Rte_Call_OpCycle_POWER_CYCLE_RestartOperationCycle();
    break;

//  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_PrestoreFreezeFrame:/*104*/
//    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT5_PrestoreFreezeFrame();
//    if (RTE_E_OK != LddRetVal)
//    {
//      /* do something */
//    }
//    break;
//
//  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_ClearPrestoredFreezeFrame:/*105*/
//    LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT5_ClearPrestoredFreezeFrame();
//    if (RTE_E_OK != LddRetVal)
//    {
//      /* do something */
//    }
//    break;

  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx:/*106*/
    LaaBufSize = DEM_SIZE_OF_EVENT_DATA;

    for (uint8 i = 0; i < DEM_SIZE_OF_EVENT_DATA; i++)
    {
      LaaDestBuffer[i] = 0;
    }

//    LddRetVal = Rte_Call_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx(
//        1, 0x4710, &LaaDestBuffer, &LaaBufSize);
    LddRetVal = Dem_GetEventFreezeFrameDataEx(DemConf_DemEventParameter_DEM_E_TEST_EVENT5,
        1, 0x4710, &LaaDestBuffer, &LaaBufSize);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx:/*107*/
    LaaBufSize = DEM_SIZE_OF_EVENT_DATA;
    for (uint8 i = 0; i < DEM_SIZE_OF_EVENT_DATA; i++)
    {
      LaaDestBuffer[i] = 0;
    }

//    LddRetVal =
//        Rte_Call_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx(0x05,
//            &LaaDestBuffer, &LaaBufSize);
    LddRetVal =
        Dem_GetEventExtendedDataRecordEx(DemConf_DemEventParameter_DEM_E_TEST_EVENT5,0x05,
             &LaaDestBuffer, &LaaBufSize);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
    /* End Data */

    /* Healing */

  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT3_SetWIRStatus_TRUE:/*108*/
    LddRetVal = Rte_Call_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus(TRUE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT3_SetWIRStatus_FALSE:/*109*/
    LddRetVal = Rte_Call_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus(FALSE);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;
    /* End Healing */


  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData_FAILED:
    LddRetVal = Rte_Call_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData(DEM_EVENT_STATUS_FAILED,
        100, 0);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData_PASSED:
    LddRetVal = Rte_Call_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData(DEM_EVENT_STATUS_PASSED,
        100, 0);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_PASSED:/*115*/
	  LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT13_SetEventStatus( DEM_EVENT_STATUS_PREPASSED);
	  break;
  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_FAILED:/*116*/
	  LddRetVal = Rte_Call_Event_DEM_E_TEST_EVENT13_SetEventStatus( DEM_EVENT_STATUS_PREFAILED);
	  break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_GetFaultDetectionCounter:/*117*/
	  LddRetVal = Dem_GetFaultDetectionCounter(DemConf_DemEventParameter_DEM_E_TEST_EVENT13, &AppDiagnosticMonitor_FaultDetectionCounter);
	  break;

  case APP_DIAGNOSTIC_MONITOR_Dem_SetEventStatus_DEM_E_TEST_EVENT13_GetEventUdsStatus:/*119*/
	  LddRetVal = Dem_GetEventUdsStatus(DemConf_DemEventParameter_DEM_E_TEST_EVENT13, &AppDiagnosticMonitor_UDSStatus);
	  break;

  case APP_DIAGNOSTIC_MONITOR_DemComponent0_Dem_GetComponentFailed:/*118*/
	  LddRetVal = Dem_GetComponentFailed(1, &AppDiagnosticMonitor_OverflowIndication);
	  break;

  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_GetEventExtendedDataRecordEx:
    LddRetVal = Dem_GetEventExtendedDataRecordEx(DemConf_DemEventParameter_DEM_E_TEST_EVENT11, 7, &LaaDestBuffer[0],
        &LaaBufSize);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;

  case APP_DIAGNOSTIC_MONITOR_DEM_E_TEST_EVENT11_GetMonitorStatus:
    LddRetVal = Dem_GetMonitorStatus(DemConf_DemEventParameter_DEM_E_TEST_EVENT11, &AppDiagnosticMonitor_MonitorStatus);
    if (RTE_E_OK != LddRetVal)
    {
      /* do something */
    }
    break;


  case APP_DIAGNOSTIC_MONITOR_FIM_FiMFID0_GetFunctionPermission:  /*200*/
	  Rte_Call_FiM00_FunctionInhibition_GetFunctionPermission(&AppDiagnosticMonitor_FiMPermission);
	  break;
  case APP_DIAGNOSTIC_MONITOR_FIM_FiMFID0_SetFunctionAvailable_TRUE:  /*201*/
	  Rte_Call_FiM00_ControlFunctionAvailable_SetFunctionAvailable(TRUE);
	  break;
  case APP_DIAGNOSTIC_MONITOR_FIM_FiMFID0_SetFunctionAvailable_FALSE:  /*202*/
	  Rte_Call_FiM00_ControlFunctionAvailable_SetFunctionAvailable(FALSE);
	  break;
  case APP_DIAGNOSTIC_MONITOR_FIM_FiMFID1_GetFunctionPermission:  /*203*/
	  Rte_Call_FiM01_FunctionInhibition_GetFunctionPermission(&AppDiagnosticMonitor_FiMPermission);
	  break;
  case APP_DIAGNOSTIC_MONITOR_FIM_FiMFID1_SetFunctionAvailable_TRUE:  /*204*/
	  Rte_Call_FiM01_ControlFunctionAvailable_SetFunctionAvailable(TRUE);
	  break;
  case APP_DIAGNOSTIC_MONITOR_FIM_FiMFID1_SetFunctionAvailable_FALSE:  /*205*/
	  Rte_Call_FiM01_ControlFunctionAvailable_SetFunctionAvailable(FALSE);
	  break;
  case 206:  /*206*/
  	  (void)Dem_SetEventStatus(104, DEM_EVENT_STATUS_FAILED);
  	  break;
  case 207:  /*207*/
  	  (void)Dem_SetEventStatus(105, DEM_EVENT_STATUS_FAILED);
  	  break;
  case 208:  /*208*/
  	  (void)Dem_SetEventStatus(106, DEM_EVENT_STATUS_FAILED);
  	  break;
  case 209:  /*209*/
  	  (void)Dem_SetEventStatus(107, DEM_EVENT_STATUS_FAILED);
  	  break;

  case 210:  /*210*/
  	  (void)Dem_SetEventStatus(108, DEM_EVENT_STATUS_FAILED);
  	  break;

  case 211:  /*211*/
  	  (void)Dem_SetEventStatus(109, DEM_EVENT_STATUS_FAILED);
  	  break;

  case 218:  /*218*/
  	  (void)Dem_SetEventStatus(110, DEM_EVENT_STATUS_FAILED);
  	  break;

  case 219:  /*219*/
  	  (void)Dem_SetEventStatus(111, DEM_EVENT_STATUS_FAILED);
  	  break;

  case 220:  /*220*/
  	  (void)Dem_SetEventStatus(112, DEM_EVENT_STATUS_FAILED);
  	  break;



  case 212:  /*212*/
  	  (void)Dem_SetEventStatus(104, DEM_EVENT_STATUS_PASSED);
  	  break;
  case 213:  /*213*/
  	  (void)Dem_SetEventStatus(105, DEM_EVENT_STATUS_PASSED);
  	  break;
  case 214:  /*214*/
  	  (void)Dem_SetEventStatus(106, DEM_EVENT_STATUS_PASSED);
  	  break;

  case 215:  /*215*/
  	  (void)Dem_SetEventStatus(107, DEM_EVENT_STATUS_PASSED);
  	  break;

  case 216:  /*216*/
  	  (void)Dem_SetEventStatus(108, DEM_EVENT_STATUS_PASSED);
  	  break;

  case 217:  /*217*/
  	  (void)Dem_SetEventStatus(109, DEM_EVENT_STATUS_PASSED);
  	  break;


  case 221:  /*221*/
  	  (void)Dem_SetEventStatus(110, DEM_EVENT_STATUS_PASSED);
  	  break;

  case 222:  /*222*/
  	  (void)Dem_SetEventStatus(111, DEM_EVENT_STATUS_PASSED);
  	  break;

  case 223:  /*223*/
  	  (void)Dem_SetEventStatus(112, DEM_EVENT_STATUS_PASSED);
  	  break;

  default:
    break;
  }

  if (RTE_E_OK != LddRetVal)
  {
    if (SwcDem_TestFailedCtr < 0xFFU)
    {
      SwcDem_TestFailedCtr++;
    }
  }

  if ((18U != SwcDem_TestPhase) && (22U != SwcDem_TestPhase))
  {
    SwcDem_TestPhase = 0U;
  }
}

#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/

