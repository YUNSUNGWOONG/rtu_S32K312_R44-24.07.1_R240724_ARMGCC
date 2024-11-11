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
**  SRC-MODULE: Dcm_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Config                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Add getter for Did configuration    **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 1.4.1     01-Apr-2024   DanhTQ1        Refer #CP44-3362                    **
*******************************************************************************/
#ifndef DCM_CONFIG_H
#define DCM_CONFIG_H

#include "Dcm.h"
#include "Dcm_Externals.h"
#include "Dcm_PCTypes.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_WriteSigTypeSenderReceiver(
  Dcm_DataConfigConstPtrType pDataConfig,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  Dcm_NrcPtrType pErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) ||\
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_ReadSigTypeEcuSignal(
  Dcm_DataConfigConstPtrType pDataConfig,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer);
#endif

#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_IOControlSigTypeEcuSignal(
  Dcm_DataConfigConstPtrType pDataConfig,
  uint8 Action,
  P2CONST(void, AUTOMATIC, DCM_APPL_CONST) pInBuffer,
  Dcm_NrcPtrType pErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_ReadSigTypeSenderReceiver(
  Dcm_DataConfigConstPtrType pDataConfig,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer);
#endif

#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
extern FUNC(Dcm_DidRangeConfigPtrType, DCM_CODE) 
  Dcm_CfgInternal_GetDidRangeConfig(uint16 DidIndex);
#endif

#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
extern FUNC(Dcm_DidParaConfigConstPtrType, DCM_CODE) 
  Dcm_CfgInternal_GetDidConfig(uint16 DidIndex);
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Dcm_PeriodicDidInfoPtrType, DCM_CODE) 
  Dcm_CfgInternal_GetPdidInfo(uint16 PdidIndex);
#endif

#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
extern FUNC(Dcm_DynDidInfoPtrType, DCM_CODE) 
  Dcm_CfgInternal_GetDynDidInfo(uint16 DynDidIndex);
#endif

#endif /* DCM_CONFIG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
