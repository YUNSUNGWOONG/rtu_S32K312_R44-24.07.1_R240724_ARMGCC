
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           CanIf_Can.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Interface Module                        **
**                                                                            **
**  PURPOSE   :           This file contain externs function body for generic **
**                        public API's.                                       **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**                                                                            **
**  Module version : 1.1.0.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Definition\Can_43_FLEXCAN_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_CanTp.arxml           
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\Ecu\Mcal\Ecud_Can.arxml        
*                  Configuration\System\Bswmd\Bswmd_Can.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTp_R44\generator\CanTp_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:54:55                       
*/

#ifndef CANIF_CAN_H
#define CANIF_CAN_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Can.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    CANIF_CAN_H_AR_RELEASE_MAJOR_VERSION          0x04u
#define    CANIF_CAN_H_AR_RELEASE_MINOR_VERSION          0x07u
#define    CANIF_CAN_H_AR_RELEASE_REVISION_VERSION       0x00u
#define    CANIF_CAN_H_SW_MAJOR_VERSION                  0x03u
#define    CANIF_CAN_H_SW_MINOR_VERSION                  0x00u
#define    CANIF_CAN_H_SW_PATCH_VERSION                  0x00u


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Configuration Set Handles                             **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* TxConfirmaton event referring to a CAN Controller */
extern FUNC(void, CANIF_CODE) CanIf_TxConfirmation (PduIdType CanTxPduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* RxIndication event referring to a CAN Controller for AUTOSAR 4.4.0*/
extern FUNC(void, CANIF_CODE) CanIf_RxIndication(
                          P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
                          P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* BusOff event referring to a CAN Controller */
extern FUNC(void, CANIF_CODE) CanIf_ControllerBusOff (uint8 ControllerId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* Mode Controller event referring to a CAN Controller */
extern FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication 
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
(CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE)) 
(uint8 ControllerId, Can_ControllerStateType ControllerMode);
#else
(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
#endif       
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_CurrentIcomConfiguration 
(uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
