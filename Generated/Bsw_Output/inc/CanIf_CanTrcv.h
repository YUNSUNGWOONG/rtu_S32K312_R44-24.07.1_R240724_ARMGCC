
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
**  SRC-MODULE:           CanIf_CanTrcv.h                                     **
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

#ifndef CANIF_CANTRCV_H
#define CANIF_CANTRCV_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTrcv.h"
#include "CanIf_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    CANIF_CANTRCV_H_AR_RELEASE_MAJOR_VERSION      0x04u
#define    CANIF_CANTRCV_H_AR_RELEASE_MINOR_VERSION      0x04u
#define    CANIF_CANTRCV_H_AR_RELEASE_REVISION_VERSION   0x00u
#define    CANIF_CANTRCV_H_SW_MAJOR_VERSION              0x01u
#define    CANIF_CANTRCV_H_SW_MINOR_VERSION              0x00u
#define    CANIF_CANTRCV_H_SW_PATCH_VERSION              0x0Bu




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
/* Trcv Mode Controller event referring to a CANTRCV Controller */
extern FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication 
       (uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);       
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANIF_PN_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability (
                                           VAR(uint8, CANIF_VAR) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication(
                                           VAR(uint8, CANIF_VAR) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication (
                                           VAR(uint8, CANIF_VAR) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
