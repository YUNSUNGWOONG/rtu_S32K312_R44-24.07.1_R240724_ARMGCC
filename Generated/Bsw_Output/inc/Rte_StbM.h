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
**  File Name : Rte_StbM.h                                                    **
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
#ifndef RTE_STBM_H
#define RTE_STBM_H
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
#include "Rte_StbM_Type.h"
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
#define Rte_InitValue_StbM_GlobalTime_StatusEvent_Client0_eventNotification 0U

#define Rte_InitValue_GlobalTime_StatusEvent_Client0_eventNotification Rte_InitValue_StbM_GlobalTime_StatusEvent_Client0_eventNotification

/******************************************************************************/
/*                          Component Data Structure                          */
/******************************************************************************/
struct Rte_CDS_StbM
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_StbM Rte_CDS_StbM;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_StbM, RTE_CONST, RTE_CONST) Rte_Inst_StbM;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_BusGetCurrentTime
#define RTE_RUNNABLE_BusGetCurrentTime StbM_BusGetCurrentTime
#endif

#ifndef RTE_RUNNABLE_BusSetGlobalTime
#define RTE_RUNNABLE_BusSetGlobalTime StbM_BusSetGlobalTime
#endif

#ifndef RTE_RUNNABLE_GetCurrentTime
#define RTE_RUNNABLE_GetCurrentTime StbM_GetCurrentTime
#endif

#ifndef RTE_RUNNABLE_GetCurrentTimeExtended
#define RTE_RUNNABLE_GetCurrentTimeExtended StbM_GetCurrentTimeExtended
#endif

#ifndef RTE_RUNNABLE_GetCurrentVirtualLocalTime
#define RTE_RUNNABLE_GetCurrentVirtualLocalTime StbM_GetCurrentVirtualLocalTime
#endif

#ifndef RTE_RUNNABLE_GetMasterConfig
#define RTE_RUNNABLE_GetMasterConfig StbM_GetMasterConfig
#endif

#ifndef RTE_RUNNABLE_GetOffset
#define RTE_RUNNABLE_GetOffset StbM_GetOffset
#endif

#ifndef RTE_RUNNABLE_GetOffsetTimeRecordHead
#define RTE_RUNNABLE_GetOffsetTimeRecordHead StbM_GetOffsetTimeRecordHead
#endif

#ifndef RTE_RUNNABLE_GetRateDeviation
#define RTE_RUNNABLE_GetRateDeviation StbM_GetRateDeviation
#endif

#ifndef RTE_RUNNABLE_GetSyncTimeRecordHead
#define RTE_RUNNABLE_GetSyncTimeRecordHead StbM_GetSyncTimeRecordHead
#endif

#ifndef RTE_RUNNABLE_GetTimeBaseStatus
#define RTE_RUNNABLE_GetTimeBaseStatus StbM_GetTimeBaseStatus
#endif

#ifndef RTE_RUNNABLE_GetTimeBaseUpdateCounter
#define RTE_RUNNABLE_GetTimeBaseUpdateCounter StbM_GetTimeBaseUpdateCounter
#endif

#ifndef RTE_RUNNABLE_GetTimeLeap
#define RTE_RUNNABLE_GetTimeLeap StbM_GetTimeLeap
#endif

#ifndef RTE_RUNNABLE_MainFunction
#define RTE_RUNNABLE_MainFunction StbM_MainFunction
#endif

#ifndef RTE_RUNNABLE_SetGlobalTime
#define RTE_RUNNABLE_SetGlobalTime StbM_SetGlobalTime
#endif

#ifndef RTE_RUNNABLE_SetOffset
#define RTE_RUNNABLE_SetOffset StbM_SetOffset
#endif

#ifndef RTE_RUNNABLE_SetRateCorrection
#define RTE_RUNNABLE_SetRateCorrection StbM_SetRateCorrection
#endif

#ifndef RTE_RUNNABLE_SetUserData
#define RTE_RUNNABLE_SetUserData StbM_SetUserData
#endif

#ifndef RTE_RUNNABLE_StartTimer
#define RTE_RUNNABLE_StartTimer StbM_StartTimer
#endif

#ifndef RTE_RUNNABLE_StbM_Required_Port
#define RTE_RUNNABLE_StbM_Required_Port StbM_Required_Ports_Call
#endif

#ifndef RTE_RUNNABLE_TriggerTimeTransmission
#define RTE_RUNNABLE_TriggerTimeTransmission StbM_TriggerTimeTransmission
#endif

#ifndef RTE_RUNNABLE_UpdateGlobalTime
#define RTE_RUNNABLE_UpdateGlobalTime StbM_UpdateGlobalTime
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_BusGetCurrentTime(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_BusSetGlobalTime(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetCurrentTime(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_TimeStampType, AUTOMATIC, RTE_APPL_DATA) timeStamp, P2VAR(StbM_UserDataType, AUTOMATIC, RTE_APPL_DATA) userData);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetCurrentTimeExtended(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_TimeStampExtendedType, AUTOMATIC, RTE_APPL_DATA) timeStamp, P2VAR(StbM_UserDataType, AUTOMATIC, RTE_APPL_DATA) userData);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_GetCurrentVirtualLocalTime(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetMasterConfig(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_MasterConfigType, AUTOMATIC, RTE_APPL_DATA) masterConfig);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_GetOffset(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_GetOffsetTimeRecordHead(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetRateDeviation(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_RateDeviationType, AUTOMATIC, RTE_APPL_DATA) rateDeviation);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetSyncTimeRecordHead(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_SyncRecordTableHeadType, AUTOMATIC, RTE_APPL_DATA) syncRecordTableHead);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetTimeBaseStatus(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, RTE_APPL_DATA) syncTimeBaseStatus, P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, RTE_APPL_DATA) offsetTimeBaseStatus);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_GetTimeBaseUpdateCounter(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_GetTimeLeap(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2VAR(StbM_TimeDiffType, AUTOMATIC, RTE_APPL_DATA) timeJump);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_MainFunction(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_SetGlobalTime(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, RTE_APPL_CONST) timeStamp, P2CONST(StbM_UserDataType, AUTOMATIC, RTE_APPL_CONST) userData);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_SetOffset(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, RTE_APPL_CONST) timeStamp, P2CONST(StbM_UserDataType, AUTOMATIC, RTE_APPL_CONST) userData);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_SetRateCorrection(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, VAR(StbM_RateDeviationType, AUTOMATIC) rateDeviation);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_SetUserData(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2CONST(StbM_UserDataType, AUTOMATIC, RTE_APPL_CONST) userData);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_StartTimer(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(void, StbM_CODE) StbM_Required_Ports_Call(void);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_TriggerTimeTransmission(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

#define StbM_START_SEC_CODE
#include "StbM_MemMap.h"
FUNC(Std_ReturnType, StbM_CODE) StbM_UpdateGlobalTime(VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC) timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, RTE_APPL_CONST) timeStamp, P2CONST(StbM_UserDataType, AUTOMATIC, RTE_APPL_CONST) userData);
#define StbM_STOP_SEC_CODE
#include "StbM_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/
#ifndef Rte_Write_GlobalTime_StatusEvent_Client0_eventNotification
#define Rte_Write_GlobalTime_StatusEvent_Client0_eventNotification Rte_Write_StbM_GlobalTime_StatusEvent_Client0_eventNotification
#endif

#ifndef Rte_Call_MeasurementNotification_Client0_SetSyncTimeRecordTable
#define Rte_Call_MeasurementNotification_Client0_SetSyncTimeRecordTable Rte_Call_StbM_MeasurementNotification_Client0_SetSyncTimeRecordTable
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_StbM_GlobalTime_StatusEvent_Client0_eventNotification(CONST(StbM_TimeBaseNotificationType, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_StbM_MeasurementNotification_Client0_SetSyncTimeRecordTable(P2CONST(StbM_SyncRecordTableBlockType, AUTOMATIC, RTE_APPL_CONST) syncRecordTableBlock);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_StbM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_GlobalTime_Master_Provider1_E_OK 0U

#define RTE_E_GlobalTime_Master_Offset0_E_NOT_OK 1U

#define RTE_E_MeasurementNotification_Client0_E_NOT_OK 1U

#define RTE_E_GlobalTime_Master_Provider0_E_OK 0U

#define RTE_E_GlobalTime_Slave_Offset0_E_NOT_OK 1U

#define RTE_E_GlobalTime_Master_CertTime_E_NOT_OK 1U

#define RTE_E_GlobalTime_Master_CertTime_E_OK 0U

#define RTE_E_GlobalTime_Slave_Client0_E_OK 0U

#define RTE_E_GlobalTime_Slave_Provider1_E_OK 0U

#define RTE_E_GlobalTime_Slave_Provider1_E_NOT_OK 1U

#define RTE_E_MeasurementNotification_Client0_E_OK 0U

#define RTE_E_GlobalTime_Master_Provider0_E_NOT_OK 1U

#define RTE_E_GlobalTime_Slave_CertTime_E_OK 0U

#define RTE_E_GlobalTime_Slave_CertTime_E_NOT_OK 1U

#define RTE_E_GlobalTime_Master_Provider1_E_NOT_OK 1U

#define RTE_E_GlobalTime_Slave_Provider0_E_OK 0U

#define RTE_E_GlobalTime_Master_Offset0_E_OK 0U

#define RTE_E_GlobalTime_Slave_Provider0_E_NOT_OK 1U

#define RTE_E_GlobalTime_Slave_Offset0_E_OK 0U

#define RTE_E_GlobalTime_Slave_Client0_E_NOT_OK 1U

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

