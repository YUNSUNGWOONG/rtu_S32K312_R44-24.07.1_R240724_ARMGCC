/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : Rte_Dem.h                                                     **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/
/******************************************************************************/
/*                 Multiple Header Inclusion Protection Start                 */
/******************************************************************************/
#ifndef RTE_DEM_H
#define RTE_DEM_H
#ifndef RTE_ALLOW_CROSS_HEADER_INCLUSION
#ifdef RTE_APPLICATION_HEADER_FILE
#error Multiple Application Header Files included.
#endif
#define RTE_APPLICATION_HEADER_FILE
#endif

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_User.h"
#include "Rte_Dem_Type.h"
#include "Rte_Static.h"
#include "Rte_DataHandleType.h"
#include "Rte_Hook.h"
#include "Rte_IntMacros.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                                Init Macros                                 */
/******************************************************************************/

/******************************************************************************/
/*                          Component Data Structure                          */
/******************************************************************************/
struct Rte_CDS_Dem
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_Dem Rte_CDS_Dem;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_Dem, RTE_CONST, RTE_CONST) Rte_Inst_Dem;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_ClearDTC
#define RTE_RUNNABLE_ClearDTC Dem_ClearDTC
#endif

#ifndef RTE_RUNNABLE_GetCycleQualified
#define RTE_RUNNABLE_GetCycleQualified Dem_GetCycleQualified
#endif

#ifndef RTE_RUNNABLE_GetDTCOfEvent
#define RTE_RUNNABLE_GetDTCOfEvent Dem_GetDTCOfEvent
#endif

#ifndef RTE_RUNNABLE_GetDTCSuppression
#define RTE_RUNNABLE_GetDTCSuppression Dem_GetDTCSuppression
#endif

#ifndef RTE_RUNNABLE_GetDebouncingOfEvent
#define RTE_RUNNABLE_GetDebouncingOfEvent Dem_GetDebouncingOfEvent
#endif

#ifndef RTE_RUNNABLE_GetEventExtendedDataRecordEx
#define RTE_RUNNABLE_GetEventExtendedDataRecordEx Dem_GetEventExtendedDataRecordEx
#endif

#ifndef RTE_RUNNABLE_GetEventFreezeFrameDataEx
#define RTE_RUNNABLE_GetEventFreezeFrameDataEx Dem_GetEventFreezeFrameDataEx
#endif

#ifndef RTE_RUNNABLE_GetEventMemoryOverflow
#define RTE_RUNNABLE_GetEventMemoryOverflow Dem_GetEventMemoryOverflow
#endif

#ifndef RTE_RUNNABLE_GetEventUdsStatus
#define RTE_RUNNABLE_GetEventUdsStatus Dem_GetEventUdsStatus
#endif

#ifndef RTE_RUNNABLE_GetFaultDetectionCounter
#define RTE_RUNNABLE_GetFaultDetectionCounter Dem_GetFaultDetectionCounter
#endif

#ifndef RTE_RUNNABLE_GetIndicatorStatus
#define RTE_RUNNABLE_GetIndicatorStatus Dem_GetIndicatorStatus
#endif

#ifndef RTE_RUNNABLE_GetMonitorStatus
#define RTE_RUNNABLE_GetMonitorStatus Dem_GetMonitorStatus
#endif

#ifndef RTE_RUNNABLE_GetNumberOfEventMemoryEntries
#define RTE_RUNNABLE_GetNumberOfEventMemoryEntries Dem_GetNumberOfEventMemoryEntries
#endif

#ifndef RTE_RUNNABLE_MainFunction
#define RTE_RUNNABLE_MainFunction Dem_MainFunction
#endif

#ifndef RTE_RUNNABLE_ResetEventDebounceStatus
#define RTE_RUNNABLE_ResetEventDebounceStatus Dem_ResetEventDebounceStatus
#endif

#ifndef RTE_RUNNABLE_ResetEventStatus
#define RTE_RUNNABLE_ResetEventStatus Dem_ResetEventStatus
#endif

#ifndef RTE_RUNNABLE_RestartOperationCycle
#define RTE_RUNNABLE_RestartOperationCycle Dem_RestartOperationCycle
#endif

#ifndef RTE_RUNNABLE_SelectDTC
#define RTE_RUNNABLE_SelectDTC Dem_SelectDTC
#endif

#ifndef RTE_RUNNABLE_SetCycleQualified
#define RTE_RUNNABLE_SetCycleQualified Dem_SetCycleQualified
#endif

#ifndef RTE_RUNNABLE_SetDTCSuppression
#define RTE_RUNNABLE_SetDTCSuppression Dem_SetDTCSuppression
#endif

#ifndef RTE_RUNNABLE_SetEnableCondition
#define RTE_RUNNABLE_SetEnableCondition Dem_SetEnableCondition
#endif

#ifndef RTE_RUNNABLE_SetEventAvailable
#define RTE_RUNNABLE_SetEventAvailable Dem_SetEventAvailable
#endif

#ifndef RTE_RUNNABLE_SetEventStatus
#define RTE_RUNNABLE_SetEventStatus Dem_SetEventStatus
#endif

#ifndef RTE_RUNNABLE_SetEventStatusWithMonitorData
#define RTE_RUNNABLE_SetEventStatusWithMonitorData Dem_SetEventStatusWithMonitorData
#endif

#ifndef RTE_RUNNABLE_SetStorageCondition
#define RTE_RUNNABLE_SetStorageCondition Dem_SetStorageCondition
#endif

#ifndef RTE_RUNNABLE_SetWIRStatus
#define RTE_RUNNABLE_SetWIRStatus Dem_SetWIRStatus
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_ClearDTC(VAR(uint8, AUTOMATIC) ClientId);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetCycleQualified(VAR(uint8, AUTOMATIC) OperationCycleId, P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) isQualified);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetDTCOfEvent(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) DTCOfEvent);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetDTCSuppression(VAR(uint8, AUTOMATIC) ClientId, P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) SuppressionStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetDebouncingOfEvent(VAR(Dem_EventIdType, AUTOMATIC) EventId, P2VAR(Dem_DebouncingStateType, AUTOMATIC, RTE_APPL_DATA) DebouncingState);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetEventExtendedDataRecordEx(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(uint8, AUTOMATIC) RecordNumber, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestBuffer, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) BufSize);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetEventFreezeFrameDataEx(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(uint8, AUTOMATIC) RecordNumber, VAR(uint16, AUTOMATIC) DataId, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestBuffer, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) BufSize);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetEventMemoryOverflow(VAR(uint8, AUTOMATIC) ClientId, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin, P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetEventUdsStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, P2VAR(Dem_UdsStatusByteType, AUTOMATIC, RTE_APPL_DATA) UDSStatusByte);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetFaultDetectionCounter(VAR(Dem_EventIdType, AUTOMATIC) EventId, P2VAR(sint8, AUTOMATIC, RTE_APPL_DATA) FaultDetectionCounter);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetIndicatorStatus(VAR(Dem_IndicatorStatusType, AUTOMATIC) IndicatorId, P2VAR(Dem_IndicatorStatusType, AUTOMATIC, RTE_APPL_DATA) IndicatorStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetMonitorStatus(VAR(Dem_EventIdType, AUTOMATIC) EventID, P2VAR(Dem_MonitorStatusType, AUTOMATIC, RTE_APPL_DATA) MonitorStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_GetNumberOfEventMemoryEntries(VAR(uint8, AUTOMATIC) ClientId, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) NumberOfEventMemoryEntries);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, Dem_CODE) Dem_MainFunction(void);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_ResetEventDebounceStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_DebounceResetStatusType, AUTOMATIC) DebounceResetStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_ResetEventStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_RestartOperationCycle(VAR(uint8, AUTOMATIC) OperationCycleId);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SelectDTC(VAR(uint8, AUTOMATIC) ClientId, VAR(uint32, AUTOMATIC) DTC, VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat, VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetCycleQualified(VAR(uint8, AUTOMATIC) OperationCycleId);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetDTCSuppression(VAR(uint8, AUTOMATIC) ClientId, VAR(boolean, AUTOMATIC) SuppressionStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetEnableCondition(VAR(uint8, AUTOMATIC) EnableConditionID, VAR(boolean, AUTOMATIC) ConditionFulfilled);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetEventAvailable(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(boolean, AUTOMATIC) AvailableStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetEventStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetEventStatusWithMonitorData(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventIdType, AUTOMATIC) EventStatus, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData1);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetStorageCondition(VAR(uint8, AUTOMATIC) StorageConditionID, VAR(boolean, AUTOMATIC) ConditionFulfilled);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define Dem_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, Dem_CODE) Dem_SetWIRStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(boolean, AUTOMATIC) WIRStatus);
#define Dem_STOP_SEC_CODE
#include "Dem_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

#ifndef Rte_Call_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged
#define Rte_Call_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged Rte_Call_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#define Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#define Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_DataServices_DE_0005_ReadData
#define Rte_Call_DataServices_DE_0005_ReadData Rte_Call_Dem_DataServices_DE_0005_ReadData
#endif

#ifndef Rte_Call_DataServices_DE_0003_ReadData
#define Rte_Call_DataServices_DE_0003_ReadData Rte_Call_Dem_DataServices_DE_0003_ReadData
#endif

#ifndef Rte_Call_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed
#define Rte_Call_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed Rte_Call_Dem_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed
#endif

#ifndef Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#define Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_DataServices_DE_0001_ReadData
#define Rte_Call_DataServices_DE_0001_ReadData Rte_Call_Dem_DataServices_DE_0001_ReadData
#endif

#ifndef Rte_Call_DataServices_DE_0008_ReadData
#define Rte_Call_DataServices_DE_0008_ReadData Rte_Call_Dem_DataServices_DE_0008_ReadData
#endif

#ifndef Rte_Call_GeneralCBDataEvt_EventDataChanged
#define Rte_Call_GeneralCBDataEvt_EventDataChanged Rte_Call_Dem_GeneralCBDataEvt_EventDataChanged
#endif

#ifndef Rte_Call_DataServices_DE_0010_ReadData
#define Rte_Call_DataServices_DE_0010_ReadData Rte_Call_Dem_DataServices_DE_0010_ReadData
#endif

#ifndef Rte_Call_DataServices_DE_0006_ReadData
#define Rte_Call_DataServices_DE_0006_ReadData Rte_Call_Dem_DataServices_DE_0006_ReadData
#endif

#ifndef Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#define Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#define Rte_Call_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged Rte_Call_Dem_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification
#define Rte_Call_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification Rte_Call_Dem_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification
#endif

#ifndef Rte_Call_DataServices_DE_0004_ReadData
#define Rte_Call_DataServices_DE_0004_ReadData Rte_Call_Dem_DataServices_DE_0004_ReadData
#endif

#ifndef Rte_Call_DataServices_DE_0002_ReadData
#define Rte_Call_DataServices_DE_0002_ReadData Rte_Call_Dem_DataServices_DE_0002_ReadData
#endif

#ifndef Rte_Call_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent
#define Rte_Call_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent Rte_Call_Dem_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent
#endif

#ifndef Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#define Rte_Call_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged
#endif

#ifndef Rte_Call_DataServices_DE_0009_ReadData
#define Rte_Call_DataServices_DE_0009_ReadData Rte_Call_Dem_DataServices_DE_0009_ReadData
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged(VAR(Dem_EventIdType, AUTOMATIC) EventId,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_HS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0005_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0003_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBClrEvt_DEM_E_TEST_EVENT1_ClearEventAllowed(P2VAR(AUTOSAR_boolean, AUTOMATIC, RTE_APPL_DATA) Allowed);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_FD_CAN2_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0001_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0008_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_GeneralCBDataEvt_EventDataChanged(VAR(Dem_EventIdType, AUTOMATIC) EventId);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0010_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0006_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_Project_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_DEM_E_TEST_EVENT1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_ClearDtcNotification_DemEventMemorySet0_DemClearDTCNotification0_ClearDtcNotification(VAR(uint32, AUTOMATIC) DTC,VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat,VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0004_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0002_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBInitEvt_DEM_E_TEST_EVENT1_InitMonitorForEvent(VAR(Dem_InitMonitorReasonType, AUTOMATIC) InitMonitorReason);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_CBEventUdsStatusChanged_CANSM_E_MODE_CHANGE_LS_CAN1_DemCallbackEventUdsStatusChanged0_CallbackEventUdsStatusChanged(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld,VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dem_DataServices_DE_0009_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dem_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_EvMemOverflowIndication_E_OK 0U

#define RTE_E_DataServices_DE_0006_E_OK 0U

#define RTE_E_DataServices_DE_0008_E_OK 0U

#define RTE_E_DataServices_DE_0005_E_OK 0U

#define RTE_E_DataServices_DE_0009_E_OK 0U

#define RTE_E_GeneralDiagnosticInfo_DEM_E_NO_DTC_AVAILABLE 10U

#define RTE_E_StorageCondition_E_OK 0U

#define RTE_E_DataServices_DE_0002_E_OK 0U

#define RTE_E_DataServices_DE_0004_E_OK 0U

#define RTE_E_EventAvailable_E_OK 0U

#define RTE_E_CallbackInitMonitorForEvent_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0003_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0003_E_OK 0U

#define RTE_E_CallbackClearEventAllowed_E_NOT_OK 1U

#define RTE_E_DTCSuppression_DEM_WRONG_DTC 8U

#define RTE_E_EnableCondition_E_OK 0U

#define RTE_E_EvMemOverflowIndication_E_NOT_OK 1U

#define RTE_E_OperationCycle_E_OK 0U

#define RTE_E_ClearDTC_DEM_CLEAR_FAILED 7U

#define RTE_E_DataServices_DE_0004_E_NOT_OK 1U

#define RTE_E_GeneralDiagnosticInfo_E_NOT_OK 1U

#define RTE_E_DTCSuppression_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_WRONG_DTC 8U

#define RTE_E_CallbackInitMonitorForEvent_E_OK 0U

#define RTE_E_DataServices_DE_0010_E_NOT_OK 1U

#define RTE_E_IndicatorStatus_E_OK 0U

#define RTE_E_DiagnosticInfo_E_OK 0U

#define RTE_E_DTCSuppression_DEM_PENDING 4U

#define RTE_E_OperationCycle_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0010_E_OK 0U

#define RTE_E_ClearDTC_DEM_CLEAR_MEMORY_ERROR 6U

#define RTE_E_GeneralDiagnosticInfo_E_OK 0U

#define RTE_E_DTCSuppression_DEM_WRONG_DTCORIGIN 9U

#define RTE_E_DataServices_DE_0001_E_OK 0U

#define RTE_E_DataServices_DE_0002_E_NOT_OK 1U

#define RTE_E_DiagnosticMonitor_MonitorData_E_OK 0U

#define RTE_E_ClearDtcNotification_E_OK 0U

#define RTE_E_EventStatus_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0005_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0008_E_NOT_OK 1U

#define RTE_E_CallbackClearEventAllowed_E_OK 0U

#define RTE_E_DiagnosticInfo_DEM_NO_SUCH_ELEMENT 48U

#define RTE_E_DiagnosticMonitor_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_WRONG_DTCORIGIN 9U

#define RTE_E_IndicatorStatus_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_BUSY 22U

#define RTE_E_DiagnosticMonitor_E_OK 0U

#define RTE_E_EventAvailable_E_NOT_OK 1U

#define RTE_E_GeneralDiagnosticInfo_DEM_E_NO_FDC_AVAILABLE 14U

#define RTE_E_DataServices_DE_0001_E_NOT_OK 1U

#define RTE_E_DiagnosticInfo_E_NOT_OK 1U

#define RTE_E_StorageCondition_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_PENDING 4U

#define RTE_E_DataServices_DE_0006_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0009_E_NOT_OK 1U

#define RTE_E_ClearDTC_E_NOT_OK 1U

#define RTE_E_DiagnosticInfo_DEM_BUFFER_TOO_SMALL 21U

#define RTE_E_DiagnosticMonitor_MonitorData_E_NOT_OK 1U

#define RTE_E_EventStatus_E_OK 0U

#define RTE_E_DiagnosticInfo_DEM_E_NO_FDC_AVAILABLE 14U

#define RTE_E_ClearDTC_DEM_CLEAR_BUSY 5U

#define RTE_E_ClearDTC_E_OK 0U

#define RTE_E_EnableCondition_E_NOT_OK 1U

#define RTE_E_DTCSuppression_E_OK 0U

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/

