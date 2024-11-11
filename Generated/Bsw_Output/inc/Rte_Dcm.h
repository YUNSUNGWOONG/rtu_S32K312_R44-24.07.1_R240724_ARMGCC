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
**  File Name : Rte_Dcm.h                                                     **
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
#ifndef RTE_DCM_H
#define RTE_DCM_H
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
#include "Rte_Dcm_Type.h"
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
struct Rte_CDS_Dcm
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_Dcm Rte_CDS_Dcm;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_Dcm, RTE_CONST, RTE_CONST) Rte_Inst_Dcm;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_GetActiveProtocol
#define RTE_RUNNABLE_GetActiveProtocol Dcm_GetActiveProtocol
#endif

#ifndef RTE_RUNNABLE_GetSecurityLevel
#define RTE_RUNNABLE_GetSecurityLevel Dcm_GetSecurityLevel
#endif

#ifndef RTE_RUNNABLE_GetSesCtrlType
#define RTE_RUNNABLE_GetSesCtrlType Dcm_GetSesCtrlType
#endif

#ifndef RTE_RUNNABLE_MainFunction
#define RTE_RUNNABLE_MainFunction Dcm_MainFunction
#endif

#ifndef RTE_RUNNABLE_ResetToDefaultSession
#define RTE_RUNNABLE_ResetToDefaultSession Dcm_ResetToDefaultSession
#endif

#ifndef RTE_RUNNABLE_SetActiveDiagnostic
#define RTE_RUNNABLE_SetActiveDiagnostic Dcm_SetActiveDiagnostic
#endif

#ifndef RTE_RUNNABLE_TriggerOnEvent
#define RTE_RUNNABLE_TriggerOnEvent Dcm_Runnable_TriggerOnEvent
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocolType, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) ConnectionId, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) TesterSourceAddress);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, Dcm_CODE) Dcm_MainFunction(void);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, Dcm_CODE) Dcm_SetActiveDiagnostic(VAR(boolean, AUTOMATIC) ArgumentDataPrototype0);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, Dcm_CODE) Dcm_Runnable_TriggerOnEvent(VAR(uint8, AUTOMATIC) PDA_1);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

#ifndef Rte_Call_DataServices_ActuatorControl_WriteData
#define Rte_Call_DataServices_ActuatorControl_WriteData Rte_Call_Dcm_DataServices_ActuatorControl_WriteData
#endif

#ifndef Rte_Call_DataServices_ActuatorControl_ReadData
#define Rte_Call_DataServices_ActuatorControl_ReadData Rte_Call_Dcm_DataServices_ActuatorControl_ReadData
#endif

#ifndef Rte_Call_CallbackDCMRequestServices_ECU1_StartProtocol
#define Rte_Call_CallbackDCMRequestServices_ECU1_StartProtocol Rte_Call_Dcm_CallbackDCMRequestServices_ECU1_StartProtocol
#endif

#ifndef Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication
#define Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication
#endif

#ifndef Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation
#define Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation
#endif

#ifndef Rte_Call_RequestFileTransfer_ReadFileOrDir
#define Rte_Call_RequestFileTransfer_ReadFileOrDir Rte_Call_Dcm_RequestFileTransfer_ReadFileOrDir
#endif

#ifndef Rte_Call_DataServices_RPM_ReadData
#define Rte_Call_DataServices_RPM_ReadData Rte_Call_Dcm_DataServices_RPM_ReadData
#endif

#ifndef Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData
#define Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData
#endif

#ifndef Rte_Call_DataServices_VINDataIdentifier_ConditionCheckRead
#define Rte_Call_DataServices_VINDataIdentifier_ConditionCheckRead Rte_Call_Dcm_DataServices_VINDataIdentifier_ConditionCheckRead
#endif

#ifndef Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData
#define Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData
#endif

#ifndef Rte_Call_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead
#define Rte_Call_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead Rte_Call_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead
#endif

#ifndef Rte_Call_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation
#define Rte_Call_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation Rte_Call_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation
#endif

#ifndef Rte_Call_UploadDownloadServices_ProcessRequestTransferExit
#define Rte_Call_UploadDownloadServices_ProcessRequestTransferExit Rte_Call_Dcm_UploadDownloadServices_ProcessRequestTransferExit
#endif

#ifndef Rte_Call_DataServices_VehicleSpeed_ReadData
#define Rte_Call_DataServices_VehicleSpeed_ReadData Rte_Call_Dcm_DataServices_VehicleSpeed_ReadData
#endif

#ifndef Rte_Call_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication
#define Rte_Call_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication Rte_Call_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication
#endif

#ifndef Rte_Call_DataServices_SystemSupplierECUSoftwareNumber_ReadData
#define Rte_Call_DataServices_SystemSupplierECUSoftwareNumber_ReadData Rte_Call_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ReadData
#endif

#ifndef Rte_Call_InfotypeServices_VINInfoData_GetInfotypeValueData
#define Rte_Call_InfotypeServices_VINInfoData_GetInfotypeValueData Rte_Call_Dcm_InfotypeServices_VINInfoData_GetInfotypeValueData
#endif

#ifndef Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation
#define Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation
#endif

#ifndef Rte_Call_UploadDownloadServices_ProcessRequestUpload
#define Rte_Call_UploadDownloadServices_ProcessRequestUpload Rte_Call_Dcm_UploadDownloadServices_ProcessRequestUpload
#endif

#ifndef Rte_Call_DataServices_RPM_FreezeCurrentState
#define Rte_Call_DataServices_RPM_FreezeCurrentState Rte_Call_Dcm_DataServices_RPM_FreezeCurrentState
#endif

#ifndef Rte_Call_RoutineServices_RID_0200h_CalibrationActuator_Start
#define Rte_Call_RoutineServices_RID_0200h_CalibrationActuator_Start Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Start
#endif

#ifndef Rte_Call_DataServices_RPM_ReturnControlToECU
#define Rte_Call_DataServices_RPM_ReturnControlToECU Rte_Call_Dcm_DataServices_RPM_ReturnControlToECU
#endif

#ifndef Rte_Call_DataServices_ECT_WriteData
#define Rte_Call_DataServices_ECT_WriteData Rte_Call_Dcm_DataServices_ECT_WriteData
#endif

#ifndef Rte_Call_RequestControlServices_Tid1_RequestControl
#define Rte_Call_RequestControlServices_Tid1_RequestControl Rte_Call_Dcm_RequestControlServices_Tid1_RequestControl
#endif

#ifndef Rte_Call_DataServices_ActuatorControl_ReturnControlToECU
#define Rte_Call_DataServices_ActuatorControl_ReturnControlToECU Rte_Call_Dcm_DataServices_ActuatorControl_ReturnControlToECU
#endif

#ifndef Rte_Call_RequestFileTransfer_ProcessRequestReplaceFile
#define Rte_Call_RequestFileTransfer_ProcessRequestReplaceFile Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReplaceFile
#endif

#ifndef Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable
#define Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable
#endif

#ifndef Rte_Call_DataServices_RPM_WriteData
#define Rte_Call_DataServices_RPM_WriteData Rte_Call_Dcm_DataServices_RPM_WriteData
#endif

#ifndef Rte_Call_UploadDownloadServices_ProcessRequestDownload
#define Rte_Call_UploadDownloadServices_ProcessRequestDownload Rte_Call_Dcm_UploadDownloadServices_ProcessRequestDownload
#endif

#ifndef Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength
#define Rte_Call_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength
#endif

#ifndef Rte_Call_DataServices_BatVolt_ReadData
#define Rte_Call_DataServices_BatVolt_ReadData Rte_Call_Dcm_DataServices_BatVolt_ReadData
#endif

#ifndef Rte_Call_DataServices_ECT_ConditionCheckRead
#define Rte_Call_DataServices_ECT_ConditionCheckRead Rte_Call_Dcm_DataServices_ECT_ConditionCheckRead
#endif

#ifndef Rte_Call_DataServices_ActuatorControl_ConditionCheckRead
#define Rte_Call_DataServices_ActuatorControl_ConditionCheckRead Rte_Call_Dcm_DataServices_ActuatorControl_ConditionCheckRead
#endif

#ifndef Rte_Call_DataServices_BatVolt_ConditionCheckRead
#define Rte_Call_DataServices_BatVolt_ConditionCheckRead Rte_Call_Dcm_DataServices_BatVolt_ConditionCheckRead
#endif

#ifndef Rte_Call_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead
#define Rte_Call_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead Rte_Call_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead
#endif

#ifndef Rte_Call_RequestFileTransfer_WriteFile
#define Rte_Call_RequestFileTransfer_WriteFile Rte_Call_Dcm_RequestFileTransfer_WriteFile
#endif

#ifndef Rte_Call_DataServices_ActuatorControl_FreezeCurrentState
#define Rte_Call_DataServices_ActuatorControl_FreezeCurrentState Rte_Call_Dcm_DataServices_ActuatorControl_FreezeCurrentState
#endif

#ifndef Rte_Call_RequestFileTransfer_ProcessRequestReadFile
#define Rte_Call_RequestFileTransfer_ProcessRequestReadFile Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReadFile
#endif

#ifndef Rte_Call_UploadDownloadServices_ProcessTransferDataWrite
#define Rte_Call_UploadDownloadServices_ProcessTransferDataWrite Rte_Call_Dcm_UploadDownloadServices_ProcessTransferDataWrite
#endif

#ifndef Rte_Call_DataServices_VINDataIdentifier_GetScalingInformation
#define Rte_Call_DataServices_VINDataIdentifier_GetScalingInformation Rte_Call_Dcm_DataServices_VINDataIdentifier_GetScalingInformation
#endif

#ifndef Rte_Call_RequestFileTransfer_ProcessRequestAddFile
#define Rte_Call_RequestFileTransfer_ProcessRequestAddFile Rte_Call_Dcm_RequestFileTransfer_ProcessRequestAddFile
#endif

#ifndef Rte_Call_DataServices_ActuatorControl_ResetToDefault
#define Rte_Call_DataServices_ActuatorControl_ResetToDefault Rte_Call_Dcm_DataServices_ActuatorControl_ResetToDefault
#endif

#ifndef Rte_Call_DataServices_VINDataIdentifier_ReadData
#define Rte_Call_DataServices_VINDataIdentifier_ReadData Rte_Call_Dcm_DataServices_VINDataIdentifier_ReadData
#endif

#ifndef Rte_Call_DataServices_VINDataIdentifier_WriteData
#define Rte_Call_DataServices_VINDataIdentifier_WriteData Rte_Call_Dcm_DataServices_VINDataIdentifier_WriteData
#endif

#ifndef Rte_Call_SecurityAccess_L9_CompareKey
#define Rte_Call_SecurityAccess_L9_CompareKey Rte_Call_Dcm_SecurityAccess_L9_CompareKey
#endif

#ifndef Rte_Call_RequestFileTransfer_ProcessRequestReadDir
#define Rte_Call_RequestFileTransfer_ProcessRequestReadDir Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReadDir
#endif

#ifndef Rte_Call_CallbackDCMRequestServices_ECU1_StopProtocol
#define Rte_Call_CallbackDCMRequestServices_ECU1_StopProtocol Rte_Call_Dcm_CallbackDCMRequestServices_ECU1_StopProtocol
#endif

#ifndef Rte_Call_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead
#define Rte_Call_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead Rte_Call_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead
#endif

#ifndef Rte_Call_DataServices_ECT_ReadData
#define Rte_Call_DataServices_ECT_ReadData Rte_Call_Dcm_DataServices_ECT_ReadData
#endif

#ifndef Rte_Call_RequestFileTransfer_ProcessRequestDeleteFile
#define Rte_Call_RequestFileTransfer_ProcessRequestDeleteFile Rte_Call_Dcm_RequestFileTransfer_ProcessRequestDeleteFile
#endif

#ifndef Rte_Call_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData
#define Rte_Call_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData Rte_Call_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData
#endif

#ifndef Rte_Call_DataServices_ActuatorControl_ShortTermAdjustment
#define Rte_Call_DataServices_ActuatorControl_ShortTermAdjustment Rte_Call_Dcm_DataServices_ActuatorControl_ShortTermAdjustment
#endif

#ifndef Rte_Call_DataServices_RPM_ConditionCheckRead
#define Rte_Call_DataServices_RPM_ConditionCheckRead Rte_Call_Dcm_DataServices_RPM_ConditionCheckRead
#endif

#ifndef Rte_Call_UploadDownloadServices_ProcessTransferDataRead
#define Rte_Call_UploadDownloadServices_ProcessTransferDataRead Rte_Call_Dcm_UploadDownloadServices_ProcessTransferDataRead
#endif

#ifndef Rte_Call_DataServices_VehicleSpeed_GetScalingInformation
#define Rte_Call_DataServices_VehicleSpeed_GetScalingInformation Rte_Call_Dcm_DataServices_VehicleSpeed_GetScalingInformation
#endif

#ifndef Rte_Call_RoutineServices_RID_0200h_CalibrationActuator_Stop
#define Rte_Call_RoutineServices_RID_0200h_CalibrationActuator_Stop Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Stop
#endif

#ifndef Rte_Call_DataServices_BatVolt_WriteData
#define Rte_Call_DataServices_BatVolt_WriteData Rte_Call_Dcm_DataServices_BatVolt_WriteData
#endif

#ifndef Rte_Call_RoutineServices_RID_0200h_CalibrationActuator_RequestResults
#define Rte_Call_RoutineServices_RID_0200h_CalibrationActuator_RequestResults Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_RequestResults
#endif

#ifndef Rte_Call_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData
#define Rte_Call_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData Rte_Call_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData
#endif

#ifndef Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication
#define Rte_Call_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication
#endif

#ifndef Rte_Call_DataServices_VehicleSpeed_ConditionCheckRead
#define Rte_Call_DataServices_VehicleSpeed_ConditionCheckRead Rte_Call_Dcm_DataServices_VehicleSpeed_ConditionCheckRead
#endif

#ifndef Rte_Call_DataServices_RPM_ShortTermAdjustment
#define Rte_Call_DataServices_RPM_ShortTermAdjustment Rte_Call_Dcm_DataServices_RPM_ShortTermAdjustment
#endif

#ifndef Rte_Call_SecurityAccess_L9_GetSeed
#define Rte_Call_SecurityAccess_L9_GetSeed Rte_Call_Dcm_SecurityAccess_L9_GetSeed
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_CallbackDCMRequestServices_ECU1_StartProtocol(VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress,VAR(uint16, AUTOMATIC) ConnectionId);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ReadFileOrDir(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) DataLength,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidData(VAR(uint16, AUTOMATIC) DID,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_WriteDidData(VAR(uint16, AUTOMATIC) DID,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint16, AUTOMATIC) DataLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessRequestTransferExit(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleSpeed_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUSoftwareNumber_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_InfotypeServices_VINInfoData_GetInfotypeValueData(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBuffer,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBufferSize);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Confirmation(VAR(uint8, AUTOMATIC) SID,VAR(uint8, AUTOMATIC) ReqType,VAR(uint16, AUTOMATIC) ConnectionId,VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus,VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessRequestUpload(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint8, AUTOMATIC) DataFormatIdentifier,VAR(uint8, AUTOMATIC) MemoryIdentifier,VAR(uint32, AUTOMATIC) MemoryAddress,VAR(uint32, AUTOMATIC) MemorySize,P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_FreezeCurrentState(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Start(VAR(Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignalType, AUTOMATIC) DataIn_RID_0200h_StartInSignal,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StartOutSignal,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ReturnControlToECU(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ECT_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestControlServices_Tid1_RequestControl(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) OutBuffer,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) InBuffer);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ReturnControlToECU(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReplaceFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint16, AUTOMATIC) filePathAndNameLength,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName,VAR(uint8, AUTOMATIC) dataFormatIdentifier,VAR(uint64, AUTOMATIC) fileSizeUncompressed,VAR(uint64, AUTOMATIC) fileSizeCompressed,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_IsDidAvailable(VAR(uint16, AUTOMATIC) DID,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_DidSupportedType, AUTOMATIC, RTE_APPL_DATA) Supported);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessRequestDownload(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint8, AUTOMATIC) DataFormatIdentifier,VAR(uint8, AUTOMATIC) MemoryIdentifier,VAR(uint32, AUTOMATIC) MemoryAddress,VAR(uint32, AUTOMATIC) MemorySize,P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_DIDRange_DIDs_0100h_0110h_ReadDidRangeDataLength(VAR(uint16, AUTOMATIC) DID,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_BatVolt_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ECT_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_BatVolt_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_WriteFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint64, AUTOMATIC) DataLength,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_FreezeCurrentState(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReadFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint16, AUTOMATIC) filePathAndNameLength,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName,VAR(uint8, AUTOMATIC) dataFormatIdentifier,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeUncompressed,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeCompressed,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessTransferDataWrite(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint8, AUTOMATIC) MemoryIdentifier,VAR(uint32, AUTOMATIC) MemoryAddress,VAR(uint32, AUTOMATIC) MemorySize,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) MemoryData,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_GetScalingInformation(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestAddFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint16, AUTOMATIC) filePathAndNameLength,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName,VAR(uint8, AUTOMATIC) dataFormatIdentifier,VAR(uint64, AUTOMATIC) fileSizeUncompressed,VAR(uint64, AUTOMATIC) fileSizeCompressed,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ResetToDefault(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VINDataIdentifier_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_SecurityAccess_L9_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestReadDir(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint16, AUTOMATIC) filePathAndNameLength,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) dirInfoLength,P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_CallbackDCMRequestServices_ECU1_StopProtocol(VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress,VAR(uint16, AUTOMATIC) ConnectionId);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ECT_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RequestFileTransfer_ProcessRequestDeleteFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint16, AUTOMATIC) filePathAndNameLength,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_SystemSupplierECUHardwareVersionNumber_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_ActuatorControl_ShortTermAdjustment(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_UploadDownloadServices_ProcessTransferDataRead(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,VAR(uint8, AUTOMATIC) MemoryIdentifier,VAR(uint32, AUTOMATIC) MemoryAddress,VAR(uint32, AUTOMATIC) MemorySize,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) MemoryData,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleSpeed_GetScalingInformation(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_Stop(VAR(Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignalType, AUTOMATIC) DataIn_RID_0200h_StopInSignal,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StopOutSignal,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_BatVolt_WriteData(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_RID_0200h_CalibrationActuator_RequestResults(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_RequestOutSignal,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleManufacturerECUSoftwareVersionNumber_ReadData(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification1_Indication(VAR(uint8, AUTOMATIC) SID,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData,VAR(uint16, AUTOMATIC) DataSize,VAR(uint8, AUTOMATIC) ReqType,VAR(uint16, AUTOMATIC) ConnectionId,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode,VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_VehicleSpeed_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_DataServices_RPM_ShortTermAdjustment(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_SecurityAccess_L9_GetSeed(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Confirmation(VAR(uint8, AUTOMATIC) SID,VAR(uint8, AUTOMATIC) ReqType,VAR(uint16, AUTOMATIC) ConnectionId,VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus,VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestManufacturerNotification_DcmDsdServiceRequestManufacturerNotification0_Indication(VAR(uint8, AUTOMATIC) SID,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData,VAR(uint16, AUTOMATIC) DataSize,VAR(uint8, AUTOMATIC) ReqType,VAR(uint16, AUTOMATIC) ConnectionId,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode,VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Confirmation(VAR(uint8, AUTOMATIC) SID,VAR(uint8, AUTOMATIC) ReqType,VAR(uint16, AUTOMATIC) ConnectionId,VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus,VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_ServiceRequestSupplierNotification_DcmDsdServiceRequestSupplierNotification0_Indication(VAR(uint8, AUTOMATIC) SID,P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData,VAR(uint16, AUTOMATIC) DataSize,VAR(uint8, AUTOMATIC) ReqType,VAR(uint16, AUTOMATIC) ConnectionId,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode,VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,VAR(uint16, AUTOMATIC) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Dcm_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_DataServices_VehicleSpeed_E_OK 0U

#define RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_NOT_OK 1U

#define RTE_E_RequestFileTransfer_E_OK 0U

#define RTE_E_DataServices_BatVolt_E_NOT_OK 1U

#define RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_OK 0U

#define RTE_E_DataServices_RPM_E_NOT_OK 1U

#define RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_PENDING 10U

#define RTE_E_DataServices_RPM_E_OK 0U

#define RTE_E_SecurityAccess_L9_DCM_E_COMPARE_KEY_FAILED 11U

#define RTE_E_DataServices_ECT_E_NOT_OK 1U

#define RTE_E_UploadDownloadServices_DCM_E_PENDING 10U

#define RTE_E_ServiceRequestNotification_E_OK 0U

#define RTE_E_UploadDownloadServices_DCM_E_FORCE_RCRRP 12U

#define RTE_E_DataServices_VINDataIdentifier_E_OK 0U

#define RTE_E_DataServices_ECT_E_OK 0U

#define RTE_E_UploadDownloadServices_E_OK 0U

#define RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_DCM_E_PENDING 10U

#define RTE_E_DataServices_ActuatorControl_E_NOT_OK 1U

#define RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_NOT_OK 1U

#define RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_OK 0U

#define RTE_E_DataServices_VINDataIdentifier_E_NOT_OK 1U

#define RTE_E_RequestFileTransfer_DCM_E_PENDING 10U

#define RTE_E_CallbackDCMRequestServices_E_PROTOCOL_NOT_ALLOWED 5U

#define RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK 1U

#define RTE_E_InfotypeServices_VINInfoData_E_NOT_OK 1U

#define RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_OK 0U

#define RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK 1U

#define RTE_E_DCM_Roe_E_NOT_OK 1U

#define RTE_E_DCMServices_E_NOT_OK 1U

#define RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_NOT_OK 1U

#define RTE_E_SecurityAccess_L9_E_NOT_OK 1U

#define RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP 12U

#define RTE_E_RequestFileTransfer_E_NOT_OK 1U

#define RTE_E_RequestControlServices_Tid1_E_NOT_OK 1U

#define RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_OK 0U

#define RTE_E_InfotypeServices_VINInfoData_E_OK 0U

#define RTE_E_RequestControlServices_Tid1_E_OK 0U

#define RTE_E_DataServices_ActuatorControl_E_OK 0U

#define RTE_E_UploadDownloadServices_E_NOT_OK 1U

#define RTE_E_DataServices_BatVolt_E_OK 0U

#define RTE_E_SecurityAccess_L9_DCM_E_PENDING 10U

#define RTE_E_ServiceRequestNotification_E_REQUEST_NOT_ACCEPTED 8U

#define RTE_E_DCM_Roe_E_OK 0U

#define RTE_E_DataServices_VehicleSpeed_E_NOT_OK 1U

#define RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_FORCE_RCRRP 12U

#define RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_OK 0U

#define RTE_E_InfotypeServices_VINInfoData_DCM_E_PENDING 10U

#define RTE_E_DCMServices_E_OK 0U

#define RTE_E_ServiceRequestNotification_E_NOT_OK 1U

#define RTE_E_CallbackDCMRequestServices_E_NOT_OK 1U

#define RTE_E_CallbackDCMRequestServices_E_OK 0U

#define RTE_E_SecurityAccess_L9_E_OK 0U

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

