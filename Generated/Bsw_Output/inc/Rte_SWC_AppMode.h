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
**  File Name : Rte_SWC_AppMode.h                                             **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:29 KST                               **
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
#ifndef RTE_SWC_APPMODE_H
#define RTE_SWC_APPMODE_H
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
#include "Rte_SWC_AppMode_Type.h"
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
#define Rte_InitValue_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 0
#define Rte_InitValue_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 0
#define Rte_InitValue_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 0

#define Rte_InitValue_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 Rte_InitValue_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32
#define Rte_InitValue_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 Rte_InitValue_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2
#define Rte_InitValue_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 Rte_InitValue_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1

/******************************************************************************/
/*                          Component Data Structure                          */
/******************************************************************************/
struct Rte_CDS_SWC_AppMode
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_SWC_AppMode Rte_CDS_SWC_AppMode;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_SWC_AppMode, RTE_CONST, RTE_CONST) Rte_Inst_SWC_AppMode;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_CanSMBorStateSwitched_FD_CAN1
#define RTE_RUNNABLE_CanSMBorStateSwitched_FD_CAN1 AppMode_CanSMBorStateSwitched_FD_CAN1
#endif

#ifndef RTE_RUNNABLE_ComMModeSwitched_FD_CAN1_PNC32
#define RTE_RUNNABLE_ComMModeSwitched_FD_CAN1_PNC32 AppMode_ComMModeSwitched_FD_CAN1_PNC32
#endif

#ifndef RTE_RUNNABLE_ComMModeSwitched_LIN1
#define RTE_RUNNABLE_ComMModeSwitched_LIN1 AppMode_ComMModeSwitched_LIN1
#endif

#ifndef RTE_RUNNABLE_ComMModeSwitched_LIN2
#define RTE_RUNNABLE_ComMModeSwitched_LIN2 AppMode_ComMModeSwitched_LIN2
#endif

#ifndef RTE_RUNNABLE_EcuModeSwitched
#define RTE_RUNNABLE_EcuModeSwitched AppMode_EcuModeSwitched
#endif

#ifndef RTE_RUNNABLE_InitCompleted
#define RTE_RUNNABLE_InitCompleted AppMode_InitCompleted
#endif

#ifndef RTE_RUNNABLE_PduGroupSwitched_FD_CAN1_PNC32_Rx
#define RTE_RUNNABLE_PduGroupSwitched_FD_CAN1_PNC32_Rx AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx
#endif

#ifndef RTE_RUNNABLE_PduGroupSwitched_FD_CAN1_PNC32_Tx
#define RTE_RUNNABLE_PduGroupSwitched_FD_CAN1_PNC32_Tx AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx
#endif

#ifndef RTE_RUNNABLE_Test
#define RTE_RUNNABLE_Test AppMode_Test
#endif

#ifndef RTE_RUNNABLE_WakeupEventValidated
#define RTE_RUNNABLE_WakeupEventValidated AppMode_WakeupEventValidated
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_CanSMBorStateSwitched_FD_CAN1(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_ComMModeSwitched_FD_CAN1_PNC32(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_ComMModeSwitched_LIN1(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_ComMModeSwitched_LIN2(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_EcuModeSwitched(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_InitCompleted(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_Test(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) AppMode_WakeupEventValidated(void);
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/
#ifndef Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2
#define Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2
#endif

#ifndef Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32
#define Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32
#endif

#ifndef Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1
#define Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1
#endif

#ifndef Rte_Call_clientPort_StateRequest_RequestSleep
#define Rte_Call_clientPort_StateRequest_RequestSleep Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestSleep
#endif

#ifndef Rte_Call_R_modeLimitation_LimitECUToNoComMode
#define Rte_Call_R_modeLimitation_LimitECUToNoComMode Rte_Call_SWC_AppMode_R_modeLimitation_LimitECUToNoComMode
#endif

#ifndef Rte_Mode_modeNotificationPort_currentMode_currentMode
#define Rte_Mode_modeNotificationPort_currentMode_currentMode Rte_Mode_SWC_AppMode_modeNotificationPort_currentMode_currentMode
#endif

#ifndef Rte_Call_requirePort_EcuMTime_GetCurrentTime
#define Rte_Call_requirePort_EcuMTime_GetCurrentTime Rte_Call_SWC_AppMode_requirePort_EcuMTime_GetCurrentTime
#endif

#ifndef Rte_Call_requirePort_BootTarget_SelectBootTarget
#define Rte_Call_requirePort_BootTarget_SelectBootTarget Rte_Call_SWC_AppMode_requirePort_BootTarget_SelectBootTarget
#endif

#ifndef Rte_Call_requirePort_BootTarget_GetBootTarget
#define Rte_Call_requirePort_BootTarget_GetBootTarget Rte_Call_SWC_AppMode_requirePort_BootTarget_GetBootTarget
#endif

#ifndef Rte_Mode_modeNotificationPort_InitState_InitState
#define Rte_Mode_modeNotificationPort_InitState_InitState Rte_Mode_SWC_AppMode_modeNotificationPort_InitState_InitState
#endif

#ifndef Rte_Call_requirePort_ShutdownTarget_GetLastShutdownTarget
#define Rte_Call_requirePort_ShutdownTarget_GetLastShutdownTarget Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_GetLastShutdownTarget
#endif

#ifndef Rte_Call_requirePort_EcuMTime_GetWakeupTime
#define Rte_Call_requirePort_EcuMTime_GetWakeupTime Rte_Call_SWC_AppMode_requirePort_EcuMTime_GetWakeupTime
#endif

#ifndef Rte_Call_R_CL_ComMChannel_LIN2_GetInhibitionStatus
#define Rte_Call_R_CL_ComMChannel_LIN2_GetInhibitionStatus Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus
#endif

#ifndef Rte_Call_requirePort_ShutdownTarget_GetShutdownTarget
#define Rte_Call_requirePort_ShutdownTarget_GetShutdownTarget Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_GetShutdownTarget
#endif

#ifndef Rte_Mode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2
#define Rte_Mode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2 Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2
#endif

#ifndef Rte_Call_clientPort_StateRequest_ReleasePOST_RUN
#define Rte_Call_clientPort_StateRequest_ReleasePOST_RUN Rte_Call_SWC_AppMode_clientPort_StateRequest_ReleasePOST_RUN
#endif

#ifndef Rte_Mode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32
#define Rte_Mode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32 Rte_Mode_SWC_AppMode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32
#endif

#ifndef Rte_Call_requirePort_ShutdownTarget_SelectShutdownTarget
#define Rte_Call_requirePort_ShutdownTarget_SelectShutdownTarget Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_SelectShutdownTarget
#endif

#ifndef Rte_Mode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32
#define Rte_Mode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32 Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32
#endif

#ifndef Rte_Call_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode
#define Rte_Call_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode
#endif

#ifndef Rte_Call_R_modeLimitation_SetECUGroupClassification
#define Rte_Call_R_modeLimitation_SetECUGroupClassification Rte_Call_SWC_AppMode_R_modeLimitation_SetECUGroupClassification
#endif

#ifndef Rte_Mode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32
#define Rte_Mode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32 Rte_Mode_SWC_AppMode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32
#endif

#ifndef Rte_Call_R_CL_ComMChannel_LIN1_GetInhibitionStatus
#define Rte_Call_R_CL_ComMChannel_LIN1_GetInhibitionStatus Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus
#endif

#ifndef Rte_Call_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode
#define Rte_Call_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode
#endif

#ifndef Rte_Call_clientPort_StateRequest_RequestRUN
#define Rte_Call_clientPort_StateRequest_RequestRUN Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestRUN
#endif

#ifndef Rte_Mode_modeNotificationPort_WakeupEvent_WakeupEvent
#define Rte_Mode_modeNotificationPort_WakeupEvent_WakeupEvent Rte_Mode_SWC_AppMode_modeNotificationPort_WakeupEvent_WakeupEvent
#endif

#ifndef Rte_Call_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode
#define Rte_Call_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode Rte_Call_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode
#endif

#ifndef Rte_Call_clientPort_StateRequest_RequestOff
#define Rte_Call_clientPort_StateRequest_RequestOff Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestOff
#endif

#ifndef Rte_Mode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1
#define Rte_Mode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1 Rte_Mode_SWC_AppMode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1
#endif

#ifndef Rte_Call_clientPort_StateRequest_ReleaseRUN
#define Rte_Call_clientPort_StateRequest_ReleaseRUN Rte_Call_SWC_AppMode_clientPort_StateRequest_ReleaseRUN
#endif

#ifndef Rte_Call_clientPort_StateRequest_RequestReset
#define Rte_Call_clientPort_StateRequest_RequestReset Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestReset
#endif

#ifndef Rte_Call_clientPort_StateRequest_RequestPOST_RUN
#define Rte_Call_clientPort_StateRequest_RequestPOST_RUN Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestPOST_RUN
#endif

#ifndef Rte_Mode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1
#define Rte_Mode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1 Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1
#endif

#ifndef Rte_Call_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus
#define Rte_Call_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus Rte_Call_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_AppMode_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_GetInhibitionStatus(P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_APPL_DATA) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode(VAR(boolean, AUTOMATIC) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_GetInhibitionStatus(P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_APPL_DATA) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode(VAR(boolean, AUTOMATIC) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_GetInhibitionStatus(P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_APPL_DATA) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode(VAR(boolean, AUTOMATIC) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_modeLimitation_LimitECUToNoComMode(VAR(boolean, AUTOMATIC) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_R_modeLimitation_SetECUGroupClassification(VAR(ComM_InhibitionStatusType, AUTOMATIC) Status);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_ReleasePOST_RUN(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_ReleaseRUN(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestOff(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestPOST_RUN(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestRUN(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestReset(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_clientPort_StateRequest_RequestSleep(VAR(EcuM_UserType, AUTOMATIC) user);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_BootTarget_GetBootTarget(P2VAR(EcuM_BootTargetType, AUTOMATIC, RTE_APPL_DATA) target);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_BootTarget_SelectBootTarget(VAR(EcuM_BootTargetType, AUTOMATIC) target);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_EcuMTime_GetCurrentTime(P2VAR(EcuM_TimeType, AUTOMATIC, RTE_APPL_DATA) time);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_EcuMTime_GetWakeupTime(P2VAR(EcuM_TimeType, AUTOMATIC, RTE_APPL_DATA) time);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_GetLastShutdownTarget(P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, RTE_APPL_DATA) shutdownTarget,P2VAR(EcuM_ShutdownModeType, AUTOMATIC, RTE_APPL_DATA) shutdownMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_GetShutdownTarget(P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, RTE_APPL_DATA) shutdownTarget,P2VAR(EcuM_ShutdownModeType, AUTOMATIC, RTE_APPL_DATA) shutdownMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_AppMode_requirePort_ShutdownTarget_SelectShutdownTarget(VAR(EcuM_ShutdownTargetType, AUTOMATIC) shutdownTarget,VAR(EcuM_ShutdownModeType, AUTOMATIC) shutdownMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_InitState_InitState(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_WakeupEvent_WakeupEvent(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(EcuM_StateType, RTE_CODE) Rte_Mode_SWC_AppMode_modeNotificationPort_currentMode_currentMode(P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(EcuM_StateType, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_AppMode_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_EcuM_BootTarget_E_NOT_OK 1U

#define RTE_E_EcuM_ShutdownTarget_E_OK 0U

#define RTE_E_ComM_ChannelLimitation_E_NOT_OK 1U

#define RTE_E_EcuM_StateRequest_E_OK 0U

#define RTE_E_ComM_ECUModeLimitation_E_OK 0U

#define RTE_E_ComM_ChannelLimitation_E_OK 0U

#define RTE_E_EcuM_ShutdownTarget_E_NOT_OK 1U

#define RTE_E_ComM_ECUModeLimitation_E_NOT_OK 1U

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

