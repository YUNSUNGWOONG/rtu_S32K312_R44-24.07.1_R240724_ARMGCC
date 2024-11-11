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
**  File Name : Rte_EcuM.h                                                    **
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
#ifndef RTE_ECUM_H
#define RTE_ECUM_H
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
#include "Rte_EcuM_Type.h"
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
struct Rte_CDS_EcuM
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_EcuM Rte_CDS_EcuM;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_EcuM, RTE_CONST, RTE_CONST) Rte_Inst_EcuM;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_ClearWakeupEvent
#define RTE_RUNNABLE_ClearWakeupEvent EcuM_ClearWakeupEvent
#endif

#ifndef RTE_RUNNABLE_DisableWakeupSources
#define RTE_RUNNABLE_DisableWakeupSources EcuM_DisableWakeupSources
#endif

#ifndef RTE_RUNNABLE_EnableWakeupSources
#define RTE_RUNNABLE_EnableWakeupSources EcuM_EnableWakeupSources
#endif

#ifndef RTE_RUNNABLE_GetBootTarget
#define RTE_RUNNABLE_GetBootTarget EcuM_GetBootTarget
#endif

#ifndef RTE_RUNNABLE_GetCurrentTime
#define RTE_RUNNABLE_GetCurrentTime EcuM_GetCurrentTime
#endif

#ifndef RTE_RUNNABLE_GetLastShutdownTarget
#define RTE_RUNNABLE_GetLastShutdownTarget EcuM_GetLastShutdownTarget
#endif

#ifndef RTE_RUNNABLE_GetShutdownCause
#define RTE_RUNNABLE_GetShutdownCause EcuM_GetShutdownCause
#endif

#ifndef RTE_RUNNABLE_GetShutdownTarget
#define RTE_RUNNABLE_GetShutdownTarget EcuM_GetShutdownTarget
#endif

#ifndef RTE_RUNNABLE_GetWakeupTime
#define RTE_RUNNABLE_GetWakeupTime EcuM_GetWakeupTime
#endif

#ifndef RTE_RUNNABLE_GoDownHaltPoll
#define RTE_RUNNABLE_GoDownHaltPoll EcuM_GoDownHaltPoll
#endif

#ifndef RTE_RUNNABLE_ReleasePOST_RUN
#define RTE_RUNNABLE_ReleasePOST_RUN EcuM_ReleasePOST_RUN
#endif

#ifndef RTE_RUNNABLE_ReleaseRUN
#define RTE_RUNNABLE_ReleaseRUN EcuM_ReleaseRUN
#endif

#ifndef RTE_RUNNABLE_RequestOff
#define RTE_RUNNABLE_RequestOff EcuM_RequestOff
#endif

#ifndef RTE_RUNNABLE_RequestPOST_RUN
#define RTE_RUNNABLE_RequestPOST_RUN EcuM_RequestPOST_RUN
#endif

#ifndef RTE_RUNNABLE_RequestRUN
#define RTE_RUNNABLE_RequestRUN EcuM_RequestRUN
#endif

#ifndef RTE_RUNNABLE_RequestReset
#define RTE_RUNNABLE_RequestReset EcuM_RequestReset
#endif

#ifndef RTE_RUNNABLE_RequestSleep
#define RTE_RUNNABLE_RequestSleep EcuM_RequestSleep
#endif

#ifndef RTE_RUNNABLE_Rte_Switch_currentMode_currentMode
#define RTE_RUNNABLE_Rte_Switch_currentMode_currentMode Rte_Switch_currentMode_currentMode
#endif

#ifndef RTE_RUNNABLE_SelectBootTarget
#define RTE_RUNNABLE_SelectBootTarget EcuM_SelectBootTarget
#endif

#ifndef RTE_RUNNABLE_SelectShutdownCause
#define RTE_RUNNABLE_SelectShutdownCause EcuM_SelectShutdownCause
#endif

#ifndef RTE_RUNNABLE_SelectShutdownTarget
#define RTE_RUNNABLE_SelectShutdownTarget EcuM_SelectShutdownTarget
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(void, EcuM_CODE) EcuM_ClearWakeupEvent(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(void, EcuM_CODE) EcuM_DisableWakeupSources(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(void, EcuM_CODE) EcuM_EnableWakeupSources(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GetBootTarget(P2VAR(EcuM_BootTargetType, AUTOMATIC, RTE_APPL_DATA) target);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GetCurrentTime(P2VAR(EcuM_TimeType, AUTOMATIC, RTE_APPL_DATA) time);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GetLastShutdownTarget(P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, RTE_APPL_DATA) shutdownTarget, P2VAR(EcuM_ShutdownModeType, AUTOMATIC, RTE_APPL_DATA) shutdownMode);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GetShutdownCause(P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, RTE_APPL_DATA) shutdownCause);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GetShutdownTarget(P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, RTE_APPL_DATA) shutdownTarget, P2VAR(EcuM_ShutdownModeType, AUTOMATIC, RTE_APPL_DATA) shutdownMode);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GetWakeupTime(P2VAR(EcuM_TimeType, AUTOMATIC, RTE_APPL_DATA) time);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_GoDownHaltPoll(VAR(EcuM_CallerType, AUTOMATIC) caller);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_ReleasePOST_RUN(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_ReleaseRUN(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_RequestOff(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_RequestPOST_RUN(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_RequestRUN(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_RequestReset(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_RequestSleep(VAR(EcuM_UserType, AUTOMATIC) user);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(void, EcuM_CODE) Rte_Switch_currentMode_currentMode(void);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_SelectBootTarget(VAR(EcuM_BootTargetType, AUTOMATIC) target);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_SelectShutdownCause(VAR(EcuM_ShutdownCauseType, AUTOMATIC) shutdownCause);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define EcuM_START_SEC_CODE
#include "EcuM_MemMap.h"
FUNC(Std_ReturnType, EcuM_CODE) EcuM_SelectShutdownTarget(VAR(EcuM_ShutdownTargetType, AUTOMATIC) shutdownTarget, VAR(EcuM_ShutdownModeType, AUTOMATIC) shutdownMode);
#define EcuM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/
#ifndef Rte_Switch_currentMode_currentMode
#define Rte_Switch_currentMode_currentMode Rte_Switch_EcuM_currentMode_currentMode
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_EcuM_currentMode_currentMode(CONST(EcuM_StateType, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_EcuM_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_EcuM_BootTarget_E_NOT_OK 1U

#define RTE_E_EcuM_ShutdownTarget_E_OK 0U

#define RTE_E_EcuM_StateRequest_E_OK 0U

#define RTE_E_EcuM_ShutdownTarget_E_NOT_OK 1U

#define RTE_E_EcuM_Time_E_NOT_OK 1U

#define RTE_E_EcuM_Time_E_OK 0U

#define RTE_E_EcuM_BootTarget_E_OK 0U

#define RTE_E_EcuM_StateRequest_E_NOT_OK 1U

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

