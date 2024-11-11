/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  FILE-NAME:  Dcm_APIs.h                                                    **
**                                                                            **
**  MODULE-NAME: AUTOSAR DCM Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Module version: 1.4.2.0
**  Framework version: 1.1.5
********************************************************************************

********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Csm.arxml             
*                  Configuration\Ecu\Ecud_Dcm.arxml             
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_KeyM.arxml            
*                  Configuration\Ecu\Ecud_NvM.arxml             
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml   
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Csm_R44\generator\Csm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dcm_R44\generator\Dcm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\KeyM_R44\generator\KeyM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\NvM_R44\generator\NvM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifndef DCM_APIS_H
#define DCM_APIS_H

/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_APIs_RoutineControlFunc(
  uint8 ctrlType,
  uint16 routineId,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pCurrentDataLen,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);
#define DCM_STOP_SEC_CODE
#include "MemMap.h"



#endif /* DCM_APIS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
