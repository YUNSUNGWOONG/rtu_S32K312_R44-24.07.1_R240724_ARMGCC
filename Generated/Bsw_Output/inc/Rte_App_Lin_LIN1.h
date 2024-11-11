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
**  File Name : Rte_App_Lin_LIN1.h                                            **
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
#ifndef RTE_APP_LIN_LIN1_H
#define RTE_APP_LIN_LIN1_H
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
#include "Rte_App_Lin_LIN1_Type.h"
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
#define Rte_InitValue_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2 0
#define Rte_InitValue_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1 0

#define Rte_InitValue_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1 Rte_InitValue_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1
#define Rte_InitValue_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2 Rte_InitValue_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2

/******************************************************************************/
/*                          Component Data Structure                          */
/******************************************************************************/
struct Rte_CDS_App_Lin_LIN1
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_App_Lin_LIN1 Rte_CDS_App_Lin_LIN1;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_App_Lin_LIN1, RTE_CONST, RTE_CONST) Rte_Inst_App_Lin_LIN1;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_Lin_LIN1_ScheduleRequest
#define RTE_RUNNABLE_Lin_LIN1_ScheduleRequest Sym_LinScheduleRequest_LIN1
#endif

#ifndef RTE_RUNNABLE_Lin_LIN1_ScheduleSwitch
#define RTE_RUNNABLE_Lin_LIN1_ScheduleSwitch Sym_LinScheduleSwitch_LIN1
#endif

#ifndef RTE_RUNNABLE_Lin_LIN2_ScheduleRequest
#define RTE_RUNNABLE_Lin_LIN2_ScheduleRequest Sym_LinScheduleRequest_LIN2
#endif

#ifndef RTE_RUNNABLE_Lin_LIN2_ScheduleSwitch
#define RTE_RUNNABLE_Lin_LIN2_ScheduleSwitch Sym_LinScheduleSwitch_LIN2
#endif

#ifndef RTE_RUNNABLE_RE_after_schedule
#define RTE_RUNNABLE_RE_after_schedule lin_after_schedule
#endif

#ifndef RTE_RUNNABLE_RE_cbk_err
#define RTE_RUNNABLE_RE_cbk_err lin_cbk_err
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define App_Lin_LIN1_START_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleRequest_LIN1(void);
#define App_Lin_LIN1_STOP_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"

#define App_Lin_LIN1_START_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleSwitch_LIN1(void);
#define App_Lin_LIN1_STOP_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"

#define App_Lin_LIN1_START_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleRequest_LIN2(void);
#define App_Lin_LIN1_STOP_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"

#define App_Lin_LIN1_START_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleSwitch_LIN2(void);
#define App_Lin_LIN1_STOP_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"

#define App_Lin_LIN1_START_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"
FUNC(void, App_Lin_LIN1_CODE) lin_after_schedule(VAR(uint8, AUTOMATIC) channelId, VAR(uint8, AUTOMATIC) schId, VAR(uint8, AUTOMATIC) schEntryNum, VAR(uint8, AUTOMATIC) frameId);
#define App_Lin_LIN1_STOP_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"

#define App_Lin_LIN1_START_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"
FUNC(void, App_Lin_LIN1_CODE) lin_cbk_err(VAR(uint8, AUTOMATIC) channelId, VAR(uint8, AUTOMATIC) errcode, VAR(uint8, AUTOMATIC) schEntryNum, VAR(uint8, AUTOMATIC) frameId);
#define App_Lin_LIN1_STOP_SEC_CODE
#include "App_Lin_LIN1_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/
#ifndef Rte_Write_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1
#define Rte_Write_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1 Rte_Write_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1
#endif

#ifndef Rte_Write_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2
#define Rte_Write_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2 Rte_Write_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2
#endif

#ifndef Rte_Mode_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2
#define Rte_Mode_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2 Rte_Mode_App_Lin_LIN1_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2
#endif

#ifndef Rte_Mode_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1
#define Rte_Mode_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1 Rte_Mode_App_Lin_LIN1_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_App_Lin_LIN1_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_App_Lin_LIN1_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_App_Lin_LIN1_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_App_Lin_LIN1_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_App_Lin_LIN1_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

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
