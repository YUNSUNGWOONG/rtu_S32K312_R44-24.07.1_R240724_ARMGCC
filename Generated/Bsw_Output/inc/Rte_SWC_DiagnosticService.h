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
**  File Name : Rte_SWC_DiagnosticService.h                                   **
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
#ifndef RTE_SWC_DIAGNOSTICSERVICE_H
#define RTE_SWC_DIAGNOSTICSERVICE_H
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
#include "Rte_SWC_DiagnosticService_Type.h"
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
struct Rte_CDS_SWC_DiagnosticService
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_SWC_DiagnosticService Rte_CDS_SWC_DiagnosticService;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_SWC_DiagnosticService, RTE_CONST, RTE_CONST) Rte_Inst_SWC_DiagnosticService;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_ActuatorContro_FreezeCurrentState
#define RTE_RUNNABLE_ActuatorContro_FreezeCurrentState AppDcm_FreezeCurrentState_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_ActuatorControl_ConditionCheckRead
#define RTE_RUNNABLE_ActuatorControl_ConditionCheckRead AppDcm_ConditionCheckRead_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_ActuatorControl_ReadData
#define RTE_RUNNABLE_ActuatorControl_ReadData AppDcm_ReadData_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_ActuatorControl_ResetToDefault
#define RTE_RUNNABLE_ActuatorControl_ResetToDefault AppDcm_ResetToDefault_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_ActuatorControl_ReturnControlToECU
#define RTE_RUNNABLE_ActuatorControl_ReturnControlToECU AppDcm_ReturnControlToECU_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_ActuatorControl_ShortTermAdjustment
#define RTE_RUNNABLE_ActuatorControl_ShortTermAdjustment AppDcm_ShortTermAdjustment_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_ActuatorControl_WriteData
#define RTE_RUNNABLE_ActuatorControl_WriteData AppDcm_WriteData_ActuatorControl
#endif

#ifndef RTE_RUNNABLE_BatVolt_ConditionCheckRead
#define RTE_RUNNABLE_BatVolt_ConditionCheckRead AppDcm_ConditionCheckRead_BatVolt
#endif

#ifndef RTE_RUNNABLE_BatVolt_ReadData
#define RTE_RUNNABLE_BatVolt_ReadData AppDcm_ReadData_BatVolt
#endif

#ifndef RTE_RUNNABLE_BatVolt_WriteData
#define RTE_RUNNABLE_BatVolt_WriteData AppDcm_WriteData_BatVolt
#endif

#ifndef RTE_RUNNABLE_CallbackDCMRequestServices_StartProtocol
#define RTE_RUNNABLE_CallbackDCMRequestServices_StartProtocol AppDcm_StartProtocol
#endif

#ifndef RTE_RUNNABLE_CallbackDCMRequestServices_StopProtocol
#define RTE_RUNNABLE_CallbackDCMRequestServices_StopProtocol AppDcm_StopProtocol
#endif

#ifndef RTE_RUNNABLE_DID_0100h_0110h_IsDidAvailable
#define RTE_RUNNABLE_DID_0100h_0110h_IsDidAvailable AppDcm_IsDidAvailable_DID_0100h_0110h
#endif

#ifndef RTE_RUNNABLE_DID_0100h_0110h_ReadDidData
#define RTE_RUNNABLE_DID_0100h_0110h_ReadDidData AppDcm_ReadDidData_DID_0100h_0110h
#endif

#ifndef RTE_RUNNABLE_DID_0100h_0110h_ReadDidRangeDataLength
#define RTE_RUNNABLE_DID_0100h_0110h_ReadDidRangeDataLength AppDcm_ReadDidRangeDataLength_DID_0100h_0110h
#endif

#ifndef RTE_RUNNABLE_DID_0100h_0110h_WriteDidData
#define RTE_RUNNABLE_DID_0100h_0110h_WriteDidData AppDcm_WriteDidData_DID_0100h_0110h
#endif

#ifndef RTE_RUNNABLE_DO_NOT_REMPOVE
#define RTE_RUNNABLE_DO_NOT_REMPOVE AppDcm_Runnable
#endif

#ifndef RTE_RUNNABLE_DcmDsdServiceRequestManufacturerNotification0_Confirmation
#define RTE_RUNNABLE_DcmDsdServiceRequestManufacturerNotification0_Confirmation ServiceRequestManufacturerNotification_Confirmation
#endif

#ifndef RTE_RUNNABLE_DcmDsdServiceRequestManufacturerNotification0_Indication
#define RTE_RUNNABLE_DcmDsdServiceRequestManufacturerNotification0_Indication ServiceRequestManufacturerNotification_Indication
#endif

#ifndef RTE_RUNNABLE_DcmDsdServiceRequestSupplierNotification0_Confirmation
#define RTE_RUNNABLE_DcmDsdServiceRequestSupplierNotification0_Confirmation ServiceRequestSupplierNotification_Confirmation
#endif

#ifndef RTE_RUNNABLE_DcmDsdServiceRequestSupplierNotification0_Indication
#define RTE_RUNNABLE_DcmDsdServiceRequestSupplierNotification0_Indication ServiceRequestSupplierNotification_Indication
#endif

#ifndef RTE_RUNNABLE_DiagnosticSessionControlNotification
#define RTE_RUNNABLE_DiagnosticSessionControlNotification AppDcm_DiagnosticSessionControlNotification
#endif

#ifndef RTE_RUNNABLE_ECT_ConditionCheckRead
#define RTE_RUNNABLE_ECT_ConditionCheckRead AppDcm_ConditionCheckRead_ECT
#endif

#ifndef RTE_RUNNABLE_ECT_ReadData
#define RTE_RUNNABLE_ECT_ReadData AppDcm_ReadData_ECT
#endif

#ifndef RTE_RUNNABLE_ECT_WriteData
#define RTE_RUNNABLE_ECT_WriteData AppDcm_WriteData_ECT
#endif

#ifndef RTE_RUNNABLE_InfotypeServices_VINInfoData_GetInfotypeValueData
#define RTE_RUNNABLE_InfotypeServices_VINInfoData_GetInfotypeValueData AppDcm_InfotypeServices_VINInfoData_GetInfotypeValueData
#endif

#ifndef RTE_RUNNABLE_L9_CompareKey
#define RTE_RUNNABLE_L9_CompareKey AppDcm_CompareKey_L9
#endif

#ifndef RTE_RUNNABLE_L9_GetSeed
#define RTE_RUNNABLE_L9_GetSeed AppDcm_GetSeed_L9
#endif

#ifndef RTE_RUNNABLE_RID_0200h_CalibrationActuator_RequestResults
#define RTE_RUNNABLE_RID_0200h_CalibrationActuator_RequestResults AppDcm_RequestResults_CalibrationActuator
#endif

#ifndef RTE_RUNNABLE_RID_0200h_CalibrationActuator_Start
#define RTE_RUNNABLE_RID_0200h_CalibrationActuator_Start AppDcm_Start_CalibrationActuator
#endif

#ifndef RTE_RUNNABLE_RID_0200h_CalibrationActuator_Stop
#define RTE_RUNNABLE_RID_0200h_CalibrationActuator_Stop AppDcm_Stop_CalibrationActuator
#endif

#ifndef RTE_RUNNABLE_RPM_ConditionCheckRead
#define RTE_RUNNABLE_RPM_ConditionCheckRead AppDcm_ConditionCheckRead_RPM
#endif

#ifndef RTE_RUNNABLE_RPM_FreezeCurrentState
#define RTE_RUNNABLE_RPM_FreezeCurrentState AppDcm_FreezeCurrentState_RPM
#endif

#ifndef RTE_RUNNABLE_RPM_ReadData
#define RTE_RUNNABLE_RPM_ReadData AppDcm_ReadData_RPM
#endif

#ifndef RTE_RUNNABLE_RPM_ReturnControlToECU
#define RTE_RUNNABLE_RPM_ReturnControlToECU AppDcm_ReturnControlToECU_RPM
#endif

#ifndef RTE_RUNNABLE_RPM_ShortTermAdjustment
#define RTE_RUNNABLE_RPM_ShortTermAdjustment AppDcm_ShortTermAdjustment_RPM
#endif

#ifndef RTE_RUNNABLE_RPM_WriteData
#define RTE_RUNNABLE_RPM_WriteData AppDcm_WriteData_RPM
#endif

#ifndef RTE_RUNNABLE_RequestControlServices_Tid1_RequestControl
#define RTE_RUNNABLE_RequestControlServices_Tid1_RequestControl AppDcm_RequestControlServices_Tid1_RequestControl
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_ProcessRequestAddFile
#define RTE_RUNNABLE_RequestFileTransfer_ProcessRequestAddFile AppDcm_RequestFileTransfer_ProcessRequestAddFile
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_ProcessRequestDeleteFile
#define RTE_RUNNABLE_RequestFileTransfer_ProcessRequestDeleteFile AppDcm_RequestFileTransfer_ProcessRequestDeleteFile
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_ProcessRequestReadDir
#define RTE_RUNNABLE_RequestFileTransfer_ProcessRequestReadDir AppDcm_RequestFileTransfer_ProcessRequestReadDir
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_ProcessRequestReadFile
#define RTE_RUNNABLE_RequestFileTransfer_ProcessRequestReadFile AppDcm_RequestFileTransfer_ProcessRequestReadFile
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_ProcessRequestReplaceFile
#define RTE_RUNNABLE_RequestFileTransfer_ProcessRequestReplaceFile AppDcm_RequestFileTransfer_ProcessRequestReplaceFile
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_ReadFileOrDir
#define RTE_RUNNABLE_RequestFileTransfer_ReadFileOrDir AppDcm_RequestFileTransfer_ReadFileOrDir
#endif

#ifndef RTE_RUNNABLE_RequestFileTransfer_WriteFile
#define RTE_RUNNABLE_RequestFileTransfer_WriteFile App_Dcm_RequestFileTransfer_WriteFile
#endif

#ifndef RTE_RUNNABLE_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead
#define RTE_RUNNABLE_SystemSupplierECUHardwareVersionNumber_ConditionCheckRead AppDcm_ConditionCheckRead_SystemSupplierECUHardwareVersionNumber
#endif

#ifndef RTE_RUNNABLE_SystemSupplierECUHardwareVersionNumber_ReadData
#define RTE_RUNNABLE_SystemSupplierECUHardwareVersionNumber_ReadData AppDcm_ReadData_SystemSupplierECUHardwareVersionNumber
#endif

#ifndef RTE_RUNNABLE_SystemSupplierECUSoftwareNumber_ConditionCheckRead
#define RTE_RUNNABLE_SystemSupplierECUSoftwareNumber_ConditionCheckRead AppDcm_ConditionCheckRead_SystemSupplierECUSoftwareNumber
#endif

#ifndef RTE_RUNNABLE_SystemSupplierECUSoftwareNumber_ReadData
#define RTE_RUNNABLE_SystemSupplierECUSoftwareNumber_ReadData AppDcm_ReadData_SystemSupplierECUSoftwareNumber
#endif

#ifndef RTE_RUNNABLE_UploadDownloadServices_ProcessRequestDownload
#define RTE_RUNNABLE_UploadDownloadServices_ProcessRequestDownload AppDcm_UploadDownloadServices_ProcessRequestDownload
#endif

#ifndef RTE_RUNNABLE_UploadDownloadServices_ProcessRequestTransferExit
#define RTE_RUNNABLE_UploadDownloadServices_ProcessRequestTransferExit AppDcm_UploadDownloadServices_ProcessRequestTransferExit
#endif

#ifndef RTE_RUNNABLE_UploadDownloadServices_ProcessRequestUpload
#define RTE_RUNNABLE_UploadDownloadServices_ProcessRequestUpload AppDcm_UploadDownloadServices_ProcessRequestUpload
#endif

#ifndef RTE_RUNNABLE_UploadDownloadServices_ProcessTransferDataRead
#define RTE_RUNNABLE_UploadDownloadServices_ProcessTransferDataRead AppDcm_UploadDownloadServices_ProcessTransferDataRead
#endif

#ifndef RTE_RUNNABLE_UploadDownloadServices_ProcessTransferDataWrite
#define RTE_RUNNABLE_UploadDownloadServices_ProcessTransferDataWrite AppDcm_UploadDownloadServices_ProcessTransferDataWrite
#endif

#ifndef RTE_RUNNABLE_VINDataIdentifier_ConditionCheckRead
#define RTE_RUNNABLE_VINDataIdentifier_ConditionCheckRead AppDcm_ConditionCheckRead_VINDataIdentifier
#endif

#ifndef RTE_RUNNABLE_VINDataIdentifier_GetScalingInformation
#define RTE_RUNNABLE_VINDataIdentifier_GetScalingInformation AppDcm_GetScalingInformation_VINDataIdentifier
#endif

#ifndef RTE_RUNNABLE_VINDataIdentifier_ReadData
#define RTE_RUNNABLE_VINDataIdentifier_ReadData AppDcm_ReadData_VINDataIdentifier
#endif

#ifndef RTE_RUNNABLE_VINDataIdentifier_WriteData
#define RTE_RUNNABLE_VINDataIdentifier_WriteData AppDcm_WriteData_VINDataIdentifier
#endif

#ifndef RTE_RUNNABLE_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead
#define RTE_RUNNABLE_VehicleManufacturerECUSoftwareVersionNumber_ConditionCheckRead AppDcm_ConditionCheckRead_VehicleManufacturerECUSoftwareVersionNumber
#endif

#ifndef RTE_RUNNABLE_VehicleManufacturerECUSoftwareVersionNumber_ReadData
#define RTE_RUNNABLE_VehicleManufacturerECUSoftwareVersionNumber_ReadData AppDcm_ReadData_VehicleManufacturerECUSoftwareVersionNumber
#endif

#ifndef RTE_RUNNABLE_VehicleSpeed_ConditionCheckRead
#define RTE_RUNNABLE_VehicleSpeed_ConditionCheckRead AppDcm_ConditionCheckRead_VehicleSpeed
#endif

#ifndef RTE_RUNNABLE_VehicleSpeed_GetScalingInformation
#define RTE_RUNNABLE_VehicleSpeed_GetScalingInformation AppDcm_GetScalingInformation_VehicleSpeed
#endif

#ifndef RTE_RUNNABLE_VehicleSpeed_ReadData
#define RTE_RUNNABLE_VehicleSpeed_ReadData AppDcm_ReadData_VehicleSpeed
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_FreezeCurrentState_ActuatorControl(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_ActuatorControl(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_ActuatorControl(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ResetToDefault_ActuatorControl(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReturnControlToECU_ActuatorControl(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ShortTermAdjustment_ActuatorControl(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_WriteData_ActuatorControl(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_BatVolt(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_BatVolt(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_WriteData_BatVolt(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_StartProtocol(VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress, VAR(uint16, AUTOMATIC) ConnectionId);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_StopProtocol(VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress, VAR(uint16, AUTOMATIC) ConnectionId);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_IsDidAvailable_DID_0100h_0110h(VAR(uint16, AUTOMATIC) DID, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_DidSupportedType, AUTOMATIC, RTE_APPL_DATA) Supported);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadDidData_DID_0100h_0110h(VAR(uint16, AUTOMATIC) DID, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadDidRangeDataLength_DID_0100h_0110h(VAR(uint16, AUTOMATIC) DID, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_WriteDidData_DID_0100h_0110h(VAR(uint16, AUTOMATIC) DID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) DataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(void, SWC_DiagnosticService_CODE) AppDcm_Runnable(void);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) ServiceRequestManufacturerNotification_Confirmation(VAR(uint8, AUTOMATIC) SID, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) ServiceRequestManufacturerNotification_Indication(VAR(uint8, AUTOMATIC) SID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, VAR(uint16, AUTOMATIC) DataSize, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) ServiceRequestSupplierNotification_Confirmation(VAR(uint8, AUTOMATIC) SID, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) ServiceRequestSupplierNotification_Indication(VAR(uint8, AUTOMATIC) SID, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, VAR(uint16, AUTOMATIC) DataSize, VAR(uint8, AUTOMATIC) ReqType, VAR(uint16, AUTOMATIC) ConnectionId, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(void, SWC_DiagnosticService_CODE) AppDcm_DiagnosticSessionControlNotification(void);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_ECT(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_ECT(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_WriteData_ECT(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_InfotypeServices_VINInfoData_GetInfotypeValueData(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBuffer, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBufferSize);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_CompareKey_L9(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Key, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_GetSeed_L9(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestResults_CalibrationActuator(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_RequestOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_Start_CalibrationActuator(VAR(Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignalType, AUTOMATIC) DataIn_RID_0200h_StartInSignal, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StartOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_Stop_CalibrationActuator(VAR(Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignalType, AUTOMATIC) DataIn_RID_0200h_StopInSignal, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignalType, AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StopOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_RPM(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_FreezeCurrentState_RPM(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_RPM(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReturnControlToECU_RPM(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ShortTermAdjustment_RPM(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_WriteData_RPM(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestControlServices_Tid1_RequestControl(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) OutBuffer, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) InBuffer);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestFileTransfer_ProcessRequestAddFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, VAR(uint8, AUTOMATIC) dataFormatIdentifier, VAR(uint64, AUTOMATIC) fileSizeUncompressed, VAR(uint64, AUTOMATIC) fileSizeCompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestFileTransfer_ProcessRequestDeleteFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestFileTransfer_ProcessRequestReadDir(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) dirInfoLength, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestFileTransfer_ProcessRequestReadFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, VAR(uint8, AUTOMATIC) dataFormatIdentifier, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeUncompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeCompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestFileTransfer_ProcessRequestReplaceFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint16, AUTOMATIC) filePathAndNameLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, VAR(uint8, AUTOMATIC) dataFormatIdentifier, VAR(uint64, AUTOMATIC) fileSizeUncompressed, VAR(uint64, AUTOMATIC) fileSizeCompressed, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_RequestFileTransfer_ReadFileOrDir(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) DataLength, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) App_Dcm_RequestFileTransfer_WriteFile(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint64, AUTOMATIC) DataLength, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_SystemSupplierECUHardwareVersionNumber(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_SystemSupplierECUHardwareVersionNumber(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_SystemSupplierECUSoftwareNumber(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_SystemSupplierECUSoftwareNumber(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_UploadDownloadServices_ProcessRequestDownload(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) DataFormatIdentifier, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_UploadDownloadServices_ProcessRequestTransferExit(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_UploadDownloadServices_ProcessRequestUpload(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) DataFormatIdentifier, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_UploadDownloadServices_ProcessTransferDataRead(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) MemoryData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_UploadDownloadServices_ProcessTransferDataWrite(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, VAR(uint8, AUTOMATIC) MemoryIdentifier, VAR(uint32, AUTOMATIC) MemoryAddress, VAR(uint32, AUTOMATIC) MemorySize, P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) MemoryData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_VINDataIdentifier(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_GetScalingInformation_VINDataIdentifier(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_VINDataIdentifier(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_WriteData_VINDataIdentifier(P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_VehicleManufacturerECUSoftwareVersionNumber(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_VehicleManufacturerECUSoftwareVersionNumber(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ConditionCheckRead_VehicleSpeed(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_GetScalingInformation_VehicleSpeed(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_ReadData_VehicleSpeed(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

#ifndef Rte_Call_DCM_Services_GetSesCtrlType
#define Rte_Call_DCM_Services_GetSesCtrlType Rte_Call_SWC_DiagnosticService_DCM_Services_GetSesCtrlType
#endif

#ifndef Rte_Mode_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface
#define Rte_Mode_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface Rte_Mode_SWC_DiagnosticService_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface
#endif

#ifndef Rte_Call_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate
#define Rte_Call_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate Rte_Call_SWC_DiagnosticService_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate
#endif

#ifndef Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed
#define Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed Rte_Call_SWC_DiagnosticService_CsmKeyManagement_RandomSeed_L9_RandomSeed
#endif

#ifndef Rte_Call_DCM_Services_GetSecurityLevel
#define Rte_Call_DCM_Services_GetSecurityLevel Rte_Call_SWC_DiagnosticService_DCM_Services_GetSecurityLevel
#endif

#ifndef Rte_Call_DCM_Services_ResetToDefaultSession
#define Rte_Call_DCM_Services_ResetToDefaultSession Rte_Call_SWC_DiagnosticService_DCM_Services_ResetToDefaultSession
#endif

#ifndef Rte_Call_DCM_Services_GetActiveProtocol
#define Rte_Call_DCM_Services_GetActiveProtocol Rte_Call_SWC_DiagnosticService_DCM_Services_GetActiveProtocol
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(uint8, RTE_CODE) Rte_Mode_SWC_DiagnosticService_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) previousMode,P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) nextMode);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) resultBuffer,P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) resultLength);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_CsmKeyManagement_RandomSeed_L9_RandomSeed(VAR(Csm_ConstDataPtr, AUTOMATIC) seedPtr,VAR(uint32, AUTOMATIC) seedLength);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_ResetToDefaultSession(void);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_DiagnosticService_DCM_Services_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocolType,P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) ConnectionId,P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) TesterSourceAddress);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_SWC_DiagnosticService_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_DataServices_VehicleSpeed_E_OK 0U

#define RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_NOT_OK 1U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_CSM_E_BUSY 2U

#define RTE_E_RequestFileTransfer_E_OK 0U

#define RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_OK 0U

#define RTE_E_DataServices_BatVolt_E_NOT_OK 1U

#define RTE_E_DataServices_RPM_E_NOT_OK 1U

#define RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_PENDING 10U

#define RTE_E_DataServices_RPM_E_OK 0U

#define RTE_E_SecurityAccess_L9_DCM_E_COMPARE_KEY_FAILED 11U

#define RTE_E_DataServices_ECT_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_E_OK 0U

#define RTE_E_UploadDownloadServices_DCM_E_PENDING 10U

#define RTE_E_ServiceRequestNotification_E_OK 0U

#define RTE_E_UploadDownloadServices_DCM_E_FORCE_RCRRP 12U

#define RTE_E_DataServices_VINDataIdentifier_E_OK 0U

#define RTE_E_DataServices_ECT_E_OK 0U

#define RTE_E_UploadDownloadServices_E_OK 0U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_E_NOT_OK 1U

#define RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_DCM_E_PENDING 10U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_BUSY 2U

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

#define RTE_E_DCMServices_E_NOT_OK 1U

#define RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_NOT_OK 1U

#define RTE_E_SecurityAccess_L9_E_NOT_OK 1U

#define RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP 12U

#define RTE_E_RequestFileTransfer_E_NOT_OK 1U

#define RTE_E_RequestControlServices_Tid1_E_NOT_OK 1U

#define RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_OK 0U

#define RTE_E_InfotypeServices_VINInfoData_E_OK 0U

#define RTE_E_RequestControlServices_Tid1_E_OK 0U

#define RTE_E_UploadDownloadServices_E_NOT_OK 1U

#define RTE_E_DataServices_ActuatorControl_E_OK 0U

#define RTE_E_DataServices_BatVolt_E_OK 0U

#define RTE_E_ServiceRequestNotification_E_REQUEST_NOT_ACCEPTED 8U

#define RTE_E_SecurityAccess_L9_DCM_E_PENDING 10U

#define RTE_E_DataServices_VehicleSpeed_E_NOT_OK 1U

#define RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_FORCE_RCRRP 12U

#define RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_OK 0U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_E_NOT_OK 1U

#define RTE_E_InfotypeServices_VINInfoData_DCM_E_PENDING 10U

#define RTE_E_DCMServices_E_OK 0U

#define RTE_E_ServiceRequestNotification_E_NOT_OK 1U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_CSM_E_ENTROPY_EXHAUSTION 4U

#define RTE_E_CallbackDCMRequestServices_E_NOT_OK 1U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_E_OK 0U

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

