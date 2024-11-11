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
**  File Name : Rte_SWC_DiagnosticMonitor.h                                   **
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
#ifndef RTE_SWC_DIAGNOSTICMONITOR_H
#define RTE_SWC_DIAGNOSTICMONITOR_H
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
#include "Rte_SWC_DiagnosticMonitor_Type.h"
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
struct Rte_CDS_SWC_DiagnosticMonitor
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_SWC_DiagnosticMonitor Rte_CDS_SWC_DiagnosticMonitor;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_SWC_DiagnosticMonitor, RTE_CONST, RTE_CONST) Rte_Inst_SWC_DiagnosticMonitor;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_CBClrEvt_DEM_E_TEST_EVENT1
#define RTE_RUNNABLE_CBClrEvt_DEM_E_TEST_EVENT1 CBClrEvt_DEM_E_TEST_EVENT1
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0001
#define RTE_RUNNABLE_CBReadData_DE_0001 CBReadData_DE_0001
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0002
#define RTE_RUNNABLE_CBReadData_DE_0002 CBReadData_DE_0002
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0003
#define RTE_RUNNABLE_CBReadData_DE_0003 CBReadData_DE_0003
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0004
#define RTE_RUNNABLE_CBReadData_DE_0004 CBReadData_DE_0004
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0005
#define RTE_RUNNABLE_CBReadData_DE_0005 CBReadData_DE_0005
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0006
#define RTE_RUNNABLE_CBReadData_DE_0006 CBReadData_DE_0006
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0008
#define RTE_RUNNABLE_CBReadData_DE_0008 CBReadData_DE_0008
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0009
#define RTE_RUNNABLE_CBReadData_DE_0009 CBReadData_DE_0009
#endif

#ifndef RTE_RUNNABLE_CBReadData_DE_0010
#define RTE_RUNNABLE_CBReadData_DE_0010 CBReadData_DE_0010
#endif

#ifndef RTE_RUNNABLE_CBStatusEvt_DEM_E_TEST_EVENT1
#define RTE_RUNNABLE_CBStatusEvt_DEM_E_TEST_EVENT1 CBStatusEvt_DEM_E_TEST_EVENT1
#endif

#ifndef RTE_RUNNABLE_CBStatusEvt_E_MODE_CHANGE_HS_CAN1
#define RTE_RUNNABLE_CBStatusEvt_E_MODE_CHANGE_HS_CAN1 CBStatusEvt_E_MODE_CHANGE_HS_CAN1
#endif

#ifndef RTE_RUNNABLE_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0
#define RTE_RUNNABLE_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0 ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0
#endif

#ifndef RTE_RUNNABLE_DianosticMonitor
#define RTE_RUNNABLE_DianosticMonitor DiagnosticMonitor
#endif

#ifndef RTE_RUNNABLE_InitMonitorForEvent_DEM_E_TEST
#define RTE_RUNNABLE_InitMonitorForEvent_DEM_E_TEST InitMonitorForEvent_DEM_E_TEST
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBClrEvt_DEM_E_TEST_EVENT1(P2VAR(AUTOSAR_boolean, AUTOMATIC, RTE_APPL_DATA) Allowed);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0001(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0002(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0003(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0004(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0005(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0006(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0008(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0009(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) CBReadData_DE_0010(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(void, SWC_DiagnosticMonitor_CODE) CBStatusEvt_DEM_E_TEST_EVENT1(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(void, SWC_DiagnosticMonitor_CODE) CBStatusEvt_E_MODE_CHANGE_HS_CAN1(VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteOld, VAR(Dem_UdsStatusByteType, AUTOMATIC) EventStatusByteNew);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(void, SWC_DiagnosticMonitor_CODE) ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0(void);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(void, SWC_DiagnosticMonitor_CODE) DiagnosticMonitor(void);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

#define SWC_DiagnosticMonitor_START_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticMonitor_CODE) InitMonitorForEvent_DEM_E_TEST(VAR(Dem_InitMonitorReasonType, AUTOMATIC) InitMonitorReason);
#define SWC_DiagnosticMonitor_STOP_SEC_CODE
#include "SWC_DiagnosticMonitor_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

#ifndef Rte_Call_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus
#endif

#ifndef Rte_Call_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow
#define Rte_Call_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow
#endif

#ifndef Rte_Call_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus
#define Rte_Call_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus Rte_Call_SWC_DiagnosticMonitor_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus
#endif

#ifndef Rte_Call_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow
#define Rte_Call_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT10_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT10_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT10_SetEventStatus
#endif

#ifndef Rte_Call_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT9_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT9_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT9_SetEventStatus
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT2_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT2_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT2_SetEventStatus
#endif

#ifndef Rte_Call_DS000_ReportError
#define Rte_Call_DS000_ReportError Rte_Call_SWC_DiagnosticMonitor_DS000_ReportError
#endif

#ifndef Rte_Call_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect
#define Rte_Call_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect
#endif

#ifndef Rte_Call_EnableCond_EnableCondtion_0_SetEnableCondition
#define Rte_Call_EnableCond_EnableCondtion_0_SetEnableCondition Rte_Call_SWC_DiagnosticMonitor_EnableCond_EnableCondtion_0_SetEnableCondition
#endif

#ifndef Rte_Call_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect
#define Rte_Call_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect
#endif

#ifndef Rte_Call_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect
#define Rte_Call_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect
#endif

#ifndef Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow
#define Rte_Call_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT12_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT12_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT12_SetEventStatus
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT4_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT4_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT4_SetEventStatus
#endif

#ifndef Rte_Call_StorageCond_DemStorageCondition1_SetStorageCondition
#define Rte_Call_StorageCond_DemStorageCondition1_SetStorageCondition Rte_Call_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition1_SetStorageCondition
#endif

#ifndef Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow
#define Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow
#endif

#ifndef Rte_Call_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_ClearDTC_DemClient1_ClearDTC
#define Rte_Call_ClearDTC_DemClient1_ClearDTC Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient1_ClearDTC
#endif

#ifndef Rte_Call_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable
#define Rte_Call_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable Rte_Call_SWC_DiagnosticMonitor_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable
#endif

#ifndef Rte_Call_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx
#define Rte_Call_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT6_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT6_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT6_SetEventStatus
#endif

#ifndef Rte_Call_ControlDTCSuppression_SetDTCSuppression
#define Rte_Call_ControlDTCSuppression_SetDTCSuppression Rte_Call_SWC_DiagnosticMonitor_ControlDTCSuppression_SetDTCSuppression
#endif

#ifndef Rte_Call_FiM00_ControlFunctionAvailable_SetFunctionAvailable
#define Rte_Call_FiM00_ControlFunctionAvailable_SetFunctionAvailable Rte_Call_SWC_DiagnosticMonitor_FiM00_ControlFunctionAvailable_SetFunctionAvailable
#endif

#ifndef Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow
#define Rte_Call_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow
#endif

#ifndef Rte_Call_DTR_Dtr0_SetDTR
#define Rte_Call_DTR_Dtr0_SetDTR Rte_Call_SWC_DiagnosticMonitor_DTR_Dtr0_SetDTR
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus
#endif

#ifndef Rte_Call_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_FiM00_FunctionInhibition_GetFunctionPermission
#define Rte_Call_FiM00_FunctionInhibition_GetFunctionPermission Rte_Call_SWC_DiagnosticMonitor_FiM00_FunctionInhibition_GetFunctionPermission
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT8_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT8_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT8_SetEventStatus
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT1_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT1_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT1_SetEventStatus
#endif

#ifndef Rte_Call_ClearDTC_DemClient0_SelectDTC
#define Rte_Call_ClearDTC_DemClient0_SelectDTC Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient0_SelectDTC
#endif

#ifndef Rte_Call_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition
#define Rte_Call_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition Rte_Call_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition
#endif

#ifndef Rte_Call_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData
#define Rte_Call_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData Rte_Call_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData
#endif

#ifndef Rte_Call_IndStatus_DemIndicator_0_GetIndicatorStatus
#define Rte_Call_IndStatus_DemIndicator_0_GetIndicatorStatus Rte_Call_SWC_DiagnosticMonitor_IndStatus_DemIndicator_0_GetIndicatorStatus
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus
#endif

#ifndef Rte_Call_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx
#define Rte_Call_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx
#endif

#ifndef Rte_Call_ClearDTC_DemClient0_ClearDTC
#define Rte_Call_ClearDTC_DemClient0_ClearDTC Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient0_ClearDTC
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT11_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT11_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT11_SetEventStatus
#endif

#ifndef Rte_Call_StorageCond_DemStorageCondition0_SetStorageCondition
#define Rte_Call_StorageCond_DemStorageCondition0_SetStorageCondition Rte_Call_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition0_SetStorageCondition
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT3_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT3_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT3_SetEventStatus
#endif

#ifndef Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_OpCycle_POWER_CYCLE_RestartOperationCycle
#define Rte_Call_OpCycle_POWER_CYCLE_RestartOperationCycle Rte_Call_SWC_DiagnosticMonitor_OpCycle_POWER_CYCLE_RestartOperationCycle
#endif

#ifndef Rte_Call_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter
#define Rte_Call_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter
#endif

#ifndef Rte_Call_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition
#define Rte_Call_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition Rte_Call_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition
#endif

#ifndef Rte_Call_FiM01_FunctionInhibition_GetFunctionPermission
#define Rte_Call_FiM01_FunctionInhibition_GetFunctionPermission Rte_Call_SWC_DiagnosticMonitor_FiM01_FunctionInhibition_GetFunctionPermission
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT13_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT13_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT13_SetEventStatus
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT5_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT5_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT5_SetEventStatus
#endif

#ifndef Rte_Call_DTR_Dtr1_SetDTR
#define Rte_Call_DTR_Dtr1_SetDTR Rte_Call_SWC_DiagnosticMonitor_DTR_Dtr1_SetDTR
#endif

#ifndef Rte_Call_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification
#define Rte_Call_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification Rte_Call_SWC_DiagnosticMonitor_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification
#endif

#ifndef Rte_Call_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries
#define Rte_Call_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries
#endif

#ifndef Rte_Call_ClearDTC_DemClient1_SelectDTC
#define Rte_Call_ClearDTC_DemClient1_SelectDTC Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient1_SelectDTC
#endif

#ifndef Rte_Call_ControlDTCSuppression_GetDTCSuppression
#define Rte_Call_ControlDTCSuppression_GetDTCSuppression Rte_Call_SWC_DiagnosticMonitor_ControlDTCSuppression_GetDTCSuppression
#endif

#ifndef Rte_Call_FiM01_ControlFunctionAvailable_SetFunctionAvailable
#define Rte_Call_FiM01_ControlFunctionAvailable_SetFunctionAvailable Rte_Call_SWC_DiagnosticMonitor_FiM01_ControlFunctionAvailable_SetFunctionAvailable
#endif

#ifndef Rte_Call_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow
#define Rte_Call_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow
#endif

#ifndef Rte_Call_DS000_ReportRuntimeError
#define Rte_Call_DS000_ReportRuntimeError Rte_Call_SWC_DiagnosticMonitor_DS000_ReportRuntimeError
#endif

#ifndef Rte_Call_Event_DEM_E_TEST_EVENT7_SetEventStatus
#define Rte_Call_Event_DEM_E_TEST_EVENT7_SetEventStatus Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT7_SetEventStatus
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_2_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventStatus_DEM_E_TEST_EVENT3_SetWIRStatus(VAR(boolean, AUTOMATIC) WIRStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT10_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient0_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT9_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT2_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DS000_ReportError(VAR(uint8, AUTOMATIC) ApiId,VAR(uint8, AUTOMATIC) ErrorId);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio02_RepIUMPRFaultDetect(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EnableCond_EnableCondtion_0_SetEnableCondition(VAR(boolean, AUTOMATIC) ConditionFulfilled);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio01_RepIUMPRFaultDetect(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRNumerator_Ratio00_RepIUMPRFaultDetect(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT12_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT4_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition1_SetStorageCondition(VAR(boolean, AUTOMATIC) ConditionFulfilled);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient1_ClearDTC(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ControlEventAvailable_DEM_E_TEST_EVENT6_SetEventAvailable(VAR(boolean, AUTOMATIC) AvailableStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventExtendedDataRecordEx(VAR(uint8, AUTOMATIC) RecordNumber,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestBuffer,P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) BufSize);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT6_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ControlDTCSuppression_SetDTCSuppression(VAR(uint8, AUTOMATIC) ClientID,VAR(boolean, AUTOMATIC) SuppressionStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM00_ControlFunctionAvailable_SetFunctionAvailable(VAR(boolean, AUTOMATIC) Availability);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient1_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DTR_Dtr0_SetDTR(VAR(sint32, AUTOMATIC) TestResult,VAR(sint32, AUTOMATIC) LowerLimit,VAR(sint32, AUTOMATIC) UpperLimit,VAR(Dem_DTRControlType, AUTOMATIC) Ctrlval);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_1_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndUserDefinedMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM00_FunctionInhibition_GetFunctionPermission(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) Permission);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT8_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT1_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient0_SelectDTC(VAR(uint32, AUTOMATIC) DTC,VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat,VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPermanentMemory_DemClient1_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_OBDCOND_SetIUMPRDenCondition(VAR(Dem_IumprDenomCondStatusType, AUTOMATIC) ConditionStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_MonitorData_DEM_E_TEST_EVENT11_SetEventStatusWithMonitorData(VAR(Dem_EventIdType, AUTOMATIC) EventStatus,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData0,VAR(Dem_MonitorDataType, AUTOMATIC) monitorData1);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IndStatus_DemIndicator_0_GetIndicatorStatus(P2VAR(Dem_IndicatorStatusType, AUTOMATIC, RTE_APPL_DATA) IndicatorStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_OBD_EVENT_3_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT5_GetEventFreezeFrameDataEx(VAR(uint8, AUTOMATIC) RecordNumber,VAR(uint16, AUTOMATIC) DataId,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestBuffer,P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) BufSize);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient0_ClearDTC(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT11_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_StorageCond_DemStorageCondition0_SetStorageCondition(VAR(boolean, AUTOMATIC) ConditionFulfilled);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT3_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndPrimaryMemory_DemClient0_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OpCycle_POWER_CYCLE_RestartOperationCycle(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_EventInfo_DEM_E_TEST_EVENT6_GetFaultDetectionCounter(P2VAR(sint8, AUTOMATIC, RTE_APPL_DATA) FaultDetectionCounter);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_IUMPRDenominatorCondition_DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR_SetIUMPRDenCondition(VAR(Dem_IumprDenomCondStatusType, AUTOMATIC) ConditionStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM01_FunctionInhibition_GetFunctionPermission(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) Permission);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT13_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT5_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DTR_Dtr1_SetDTR(VAR(sint32, AUTOMATIC) TestResult,VAR(sint32, AUTOMATIC) LowerLimit,VAR(sint32, AUTOMATIC) UpperLimit,VAR(Dem_DTRControlType, AUTOMATIC) Ctrlval);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDtcNotification_EventMemorySet0_DemClearDTCNotification0_ClearDtcNotification(VAR(uint32, AUTOMATIC) DTC,VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat,VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetNumberOfEventMemoryEntries(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) GetNumberOfEventMemoryEntries);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ClearDTC_DemClient1_SelectDTC(VAR(uint32, AUTOMATIC) DTC,VAR(Dem_DTCFormatType, AUTOMATIC) DTCFormat,VAR(Dem_DTCOriginType, AUTOMATIC) DTCOrigin);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_ControlDTCSuppression_GetDTCSuppression(VAR(uint8, AUTOMATIC) ClientID,P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) SuppressionStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_FiM01_ControlFunctionAvailable_SetFunctionAvailable(VAR(boolean, AUTOMATIC) Availability);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_OverflowIndMirrorMemory_DemClient0_GetEventMemoryOverflow(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) OverflowIndication);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_DS000_ReportRuntimeError(VAR(uint8, AUTOMATIC) ApiId,VAR(uint8, AUTOMATIC) ErrorId);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticMonitor_Event_DEM_E_TEST_EVENT7_SetEventStatus(VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticMonitor_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_EvMemOverflowIndication_E_OK 0U

#define RTE_E_DataServices_DE_0006_E_OK 0U

#define RTE_E_DataServices_DE_0008_E_OK 0U

#define RTE_E_DETService_E_OK 0U

#define RTE_E_StorageCondition_E_OK 0U

#define RTE_E_DataServices_DE_0005_E_OK 0U

#define RTE_E_DataServices_DE_0009_E_OK 0U

#define RTE_E_DataServices_DE_0002_E_OK 0U

#define RTE_E_DataServices_DE_0004_E_OK 0U

#define RTE_E_EventAvailable_E_OK 0U

#define RTE_E_DTRCentralReport_E_OK 0U

#define RTE_E_CallbackInitMonitorForEvent_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0003_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0003_E_OK 0U

#define RTE_E_CallbackClearEventAllowed_E_NOT_OK 1U

#define RTE_E_EnableCondition_E_OK 0U

#define RTE_E_EvMemOverflowIndication_E_NOT_OK 1U

#define RTE_E_DTCSuppression_DEM_WRONG_DTC 8U

#define RTE_E_OperationCycle_E_OK 0U

#define RTE_E_ClearDTC_DEM_CLEAR_FAILED 7U

#define RTE_E_IUMPRNumerator_E_OK 0U

#define RTE_E_DataServices_DE_0004_E_NOT_OK 1U

#define RTE_E_DTCSuppression_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_WRONG_DTC 8U

#define RTE_E_IndicatorStatus_E_OK 0U

#define RTE_E_CallbackInitMonitorForEvent_E_OK 0U

#define RTE_E_DataServices_DE_0010_E_NOT_OK 1U

#define RTE_E_DiagnosticInfo_E_OK 0U

#define RTE_E_DTCSuppression_DEM_PENDING 4U

#define RTE_E_OperationCycle_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_CLEAR_MEMORY_ERROR 6U

#define RTE_E_DataServices_DE_0010_E_OK 0U

#define RTE_E_DTRCentralReport_E_NOT_OK 1U

#define RTE_E_DTCSuppression_DEM_WRONG_DTCORIGIN 9U

#define RTE_E_FunctionInhibition_E_OK 0U

#define RTE_E_DataServices_DE_0001_E_OK 0U

#define RTE_E_DataServices_DE_0002_E_NOT_OK 1U

#define RTE_E_DiagnosticMonitor_MonitorData_E_OK 0U

#define RTE_E_ClearDtcNotification_E_OK 0U

#define RTE_E_EventStatus_E_NOT_OK 1U

#define RTE_E_ControlFunctionAvailable_E_NOT_OK 1U

#define RTE_E_IUMPRDenominatorCondition_E_NOT_OK 1U

#define RTE_E_IUMPRDenominatorCondition_E_OK 0U

#define RTE_E_DataServices_DE_0005_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0008_E_NOT_OK 1U

#define RTE_E_CallbackClearEventAllowed_E_OK 0U

#define RTE_E_DiagnosticInfo_DEM_NO_SUCH_ELEMENT 48U

#define RTE_E_DiagnosticMonitor_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_WRONG_DTCORIGIN 9U

#define RTE_E_IndicatorStatus_E_NOT_OK 1U

#define RTE_E_DiagnosticMonitor_E_OK 0U

#define RTE_E_ClearDTC_DEM_BUSY 22U

#define RTE_E_EventAvailable_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0001_E_NOT_OK 1U

#define RTE_E_DiagnosticInfo_E_NOT_OK 1U

#define RTE_E_IUMPRNumerator_E_NOT_OK 1U

#define RTE_E_ControlFunctionAvailable_E_OK 0U

#define RTE_E_StorageCondition_E_NOT_OK 1U

#define RTE_E_ClearDTC_DEM_PENDING 4U

#define RTE_E_DataServices_DE_0006_E_NOT_OK 1U

#define RTE_E_ClearDTC_E_NOT_OK 1U

#define RTE_E_DataServices_DE_0009_E_NOT_OK 1U

#define RTE_E_DiagnosticInfo_DEM_BUFFER_TOO_SMALL 21U

#define RTE_E_EventStatus_E_OK 0U

#define RTE_E_DiagnosticMonitor_MonitorData_E_NOT_OK 1U

#define RTE_E_FunctionInhibition_E_NOT_OK 1U

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

