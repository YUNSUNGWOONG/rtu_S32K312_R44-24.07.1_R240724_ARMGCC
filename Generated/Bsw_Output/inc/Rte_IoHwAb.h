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
**  File Name : Rte_IoHwAb.h                                                  **
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
#ifndef RTE_IOHWAB_H
#define RTE_IOHWAB_H
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
#include "Rte_IoHwAb_Type.h"
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
struct Rte_CDS_IoHwAb
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_IoHwAb Rte_CDS_IoHwAb;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_IoHwAb, RTE_CONST, RTE_CONST) Rte_Inst_IoHwAb;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_IoHwAb_Re_AnaInDir_ReadDirect
#define RTE_RUNNABLE_IoHwAb_Re_AnaInDir_ReadDirect IoHwAb_AnaInDirReadDirect
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_DigDir_IsInput
#define RTE_RUNNABLE_IoHwAb_Re_DigDir_IsInput IoHwAb_DigDirIsInput
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_DigDir_IsOutput
#define RTE_RUNNABLE_IoHwAb_Re_DigDir_IsOutput IoHwAb_DigDirIsOutput
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_DigDir_ReadDirect
#define RTE_RUNNABLE_IoHwAb_Re_DigDir_ReadDirect IoHwAb_DigDirReadDirect
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_DigDir_SetToInput
#define RTE_RUNNABLE_IoHwAb_Re_DigDir_SetToInput IoHwAb_DigDirSetToInput
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_DigDir_SetToOutput
#define RTE_RUNNABLE_IoHwAb_Re_DigDir_SetToOutput IoHwAb_DigDirSetToOutput
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_DigDir_WriteDirect
#define RTE_RUNNABLE_IoHwAb_Re_DigDir_WriteDirect IoHwAb_DigDirWriteDirect
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_DisableNotification
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_DisableNotification IoHwAb_GptDisableNotification
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_EnableNotification
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_EnableNotification IoHwAb_GptEnableNotification
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_GetTimeElapsed
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_GetTimeElapsed IoHwAb_GptGetTimeElapsed
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_GetTimeRemaining
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_GetTimeRemaining IoHwAb_GptGetTimeRemaining
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_GptChannelConfiguration_IoHwAbTest_Cbk_Cbk
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_GptChannelConfiguration_IoHwAbTest_Cbk_Cbk GptChannelConfiguration_IoHwAbTest_Cbk
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_StartTimer
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_StartTimer IoHwAb_GptStartTimer
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Gpt_StopTimer
#define RTE_RUNNABLE_IoHwAb_Re_Gpt_StopTimer IoHwAb_GptStopTimer
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_DisableEdgeCount
#define RTE_RUNNABLE_IoHwAb_Re_Icu_DisableEdgeCount IoHwAb_IcuDisableEdgeCount
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_DisableEdgeDetection
#define RTE_RUNNABLE_IoHwAb_Re_Icu_DisableEdgeDetection IoHwAb_IcuDisableEdgeDetection
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_DisableNotification
#define RTE_RUNNABLE_IoHwAb_Re_Icu_DisableNotification IoHwAb_IcuDisableNotification
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_EnableEdgeCount
#define RTE_RUNNABLE_IoHwAb_Re_Icu_EnableEdgeCount IoHwAb_IcuEnableEdgeCount
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_EnableEdgeDetection
#define RTE_RUNNABLE_IoHwAb_Re_Icu_EnableEdgeDetection IoHwAb_IcuEnableEdgeDetection
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_EnableNotification
#define RTE_RUNNABLE_IoHwAb_Re_Icu_EnableNotification IoHwAb_IcuEnableNotification
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_GetDutyCycleValues
#define RTE_RUNNABLE_IoHwAb_Re_Icu_GetDutyCycleValues IoHwAb_IcuGetDutyCycleValues
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_GetEdgeNumbers
#define RTE_RUNNABLE_IoHwAb_Re_Icu_GetEdgeNumbers IoHwAb_IcuGetEdgeNumbers
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_GetInputState
#define RTE_RUNNABLE_IoHwAb_Re_Icu_GetInputState IoHwAb_IcuGetInputState
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_GetTimeElapsed
#define RTE_RUNNABLE_IoHwAb_Re_Icu_GetTimeElapsed IoHwAb_IcuGetTimeElapsed
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_GetTimestampIndex
#define RTE_RUNNABLE_IoHwAb_Re_Icu_GetTimestampIndex IoHwAb_IcuGetTimestampIndex
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_IcuSignalEdgeDetection_Cbk_Cbk
#define RTE_RUNNABLE_IoHwAb_Re_Icu_IcuSignalEdgeDetection_Cbk_Cbk IcuSignalEdgeDetection_Cbk
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_IcuTimestampMeasurement_Cbk_Cbk
#define RTE_RUNNABLE_IoHwAb_Re_Icu_IcuTimestampMeasurement_Cbk_Cbk IcuTimestampMeasurement_Cbk
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_ResetEdgeCount
#define RTE_RUNNABLE_IoHwAb_Re_Icu_ResetEdgeCount IoHwAb_IcuResetEdgeCount
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_SetActivationCondition
#define RTE_RUNNABLE_IoHwAb_Re_Icu_SetActivationCondition IoHwAb_IcuSetActivationCondition
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_StartSignalMeasurement
#define RTE_RUNNABLE_IoHwAb_Re_Icu_StartSignalMeasurement IoHwAb_IcuStartSignalMeasurement
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_StartTimestamp
#define RTE_RUNNABLE_IoHwAb_Re_Icu_StartTimestamp IoHwAb_IcuStartTimestamp
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_StopSignalMeasurement
#define RTE_RUNNABLE_IoHwAb_Re_Icu_StopSignalMeasurement IoHwAb_IcuStopSignalMeasurement
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Icu_StopTimestamp
#define RTE_RUNNABLE_IoHwAb_Re_Icu_StopTimestamp IoHwAb_IcuStopTimestamp
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Pwm_DisableNotification
#define RTE_RUNNABLE_IoHwAb_Re_Pwm_DisableNotification IoHwAb_PwmDisableNotification
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Pwm_EnableNotification
#define RTE_RUNNABLE_IoHwAb_Re_Pwm_EnableNotification IoHwAb_PwmEnableNotification
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Pwm_SetDutyCycle
#define RTE_RUNNABLE_IoHwAb_Re_Pwm_SetDutyCycle IoHwAb_PwmSetDutyCycle
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Pwm_SetOutputToIdle
#define RTE_RUNNABLE_IoHwAb_Re_Pwm_SetOutputToIdle IoHwAb_PwmSetOutputToIdle
#endif

#ifndef RTE_RUNNABLE_IoHwAb_Re_Pwm_SetPeriodAndDuty
#define RTE_RUNNABLE_IoHwAb_Re_Pwm_SetPeriodAndDuty IoHwAb_PwmSetPeriodAndDuty
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_AnaInDirReadDirect(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, P2VAR(IoHwAb_ValueType, AUTOMATIC, RTE_APPL_DATA) Value, VAR(IoHwAb_LengthType, AUTOMATIC) AnaInDirLength);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IoHwAb_DigDirIsInput(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_APPL_DATA) blResult);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IoHwAb_DigDirIsOutput(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_APPL_DATA) blResult);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IoHwAb_DigDirReadDirect(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, P2VAR(IoHwAb_LevelType, AUTOMATIC, RTE_APPL_DATA) Level);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IoHwAb_DigDirSetToInput(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IoHwAb_DigDirSetToOutput(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IoHwAb_DigDirWriteDirect(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, VAR(IoHwAb_LevelType, AUTOMATIC) Level);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_GptDisableNotification(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_GptEnableNotification(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_GptGetTimeElapsed(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_GptValueType, AUTOMATIC, RTE_APPL_DATA) Value);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_GptGetTimeRemaining(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_GptValueType, AUTOMATIC, RTE_APPL_DATA) Value);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) GptChannelConfiguration_IoHwAbTest_Cbk(void);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_GptStartTimer(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, VAR(IoHwAb_GptValueType, AUTOMATIC) Value);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_GptStopTimer(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuDisableEdgeCount(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuDisableEdgeDetection(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuDisableNotification(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuEnableEdgeCount(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuEnableEdgeDetection(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuEnableNotification(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuGetDutyCycleValues(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_IcuDutyCycleType, AUTOMATIC, RTE_APPL_DATA) DutyCycle);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuGetEdgeNumbers(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_IcuEdgeNumberType, AUTOMATIC, RTE_APPL_DATA) Num);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuGetInputState(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_IcuStateType, AUTOMATIC, RTE_APPL_DATA) State);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuGetTimeElapsed(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_IcuValueType, AUTOMATIC, RTE_APPL_DATA) Time);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuGetTimestampIndex(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_IcuIndexType, AUTOMATIC, RTE_APPL_DATA) TimestampIdx);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IcuSignalEdgeDetection_Cbk(void);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(void, IoHwAb_CODE) IcuTimestampMeasurement_Cbk(void);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuResetEdgeCount(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuSetActivationCondition(VAR(IoHwAb_IndexType, AUTOMATIC) ChIdx, VAR(IoHwAb_IcuActivationType, AUTOMATIC) Activation);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuStartSignalMeasurement(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuStartTimestamp(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, P2VAR(IoHwAb_IcuValueType, AUTOMATIC, RTE_APPL_DATA) BufPtr, VAR(uint16, AUTOMATIC) BufSize, VAR(uint16, AUTOMATIC) NotiItv);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuStopSignalMeasurement(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_IcuStopTimestamp(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_PwmDisableNotification(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_PwmEnableNotification(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, VAR(IoHwAb_PwmEdgeType, AUTOMATIC) NotificationEdge);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_PwmSetDutyCycle(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, VAR(uint16, AUTOMATIC) Duty);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_PwmSetOutputToIdle(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

#define IoHwAb_START_SEC_CODE
#include "IoHwAb_MemMap.h"
FUNC(Std_ReturnType, IoHwAb_CODE) IoHwAb_PwmSetPeriodAndDuty(VAR(IoHwAb_IndexType, AUTOMATIC) PDA_1, VAR(IoHwAb_PwmPeriodType, AUTOMATIC) Period, VAR(uint16, AUTOMATIC) Duty);
#define IoHwAb_STOP_SEC_CODE
#include "IoHwAb_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

#ifndef Rte_Call_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification
#define Rte_Call_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification Rte_Call_IoHwAb_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification
#endif

#ifndef Rte_Call_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification
#define Rte_Call_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification Rte_Call_IoHwAb_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification
#endif

#ifndef Rte_Call_R_IoHwAbGptLogical0_Cbk_Notification
#define Rte_Call_R_IoHwAbGptLogical0_Cbk_Notification Rte_Call_IoHwAb_R_IoHwAbGptLogical0_Cbk_Notification
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_IoHwAb_R_IoHwAbIcuLogical1_EdgeDetect_Cbk_Notification(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_IoHwAb_R_IoHwAbIcuLogical2_Timestamp_Cbk_Notification(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_IoHwAb_R_IoHwAbGptLogical0_Cbk_Notification(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_IoHwAb_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED 11U

#define RTE_E_IoHwAb_If_AnaInDir_E_WRONG_LENGTH 5U

#define RTE_E_IoHwAb_If_AnaInDir_E_SETUP_BUFFER_FAIL 6U

#define RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED 9U

#define RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED 10U

#define RTE_E_IoHwAb_If_AnaInDir_E_BUSY 4U

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

