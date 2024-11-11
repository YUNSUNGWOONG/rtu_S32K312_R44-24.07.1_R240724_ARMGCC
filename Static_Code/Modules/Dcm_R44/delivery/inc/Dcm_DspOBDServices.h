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
**  SRC-MODULE: Dcm_DspOBDServices.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspOBDServices                               **
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
** 0.0.1     31-Dec-2019   LamNV10        AR440 Implementation                **
** 0.0.2     13-Oct-2020   HueKM          Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DSPOBDSERVICES_H
#define DCM_DSPOBDSERVICES_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqCurrentPowerTrainDiagData(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqPowerTrainFreezeFrameData(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) \
     || (DCM_OBD_GETDTC_07_SERVICE == STD_ON) \
     || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDGetDTC(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_OBD_GETDTC_07_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DcmOBDGetDTC_07(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_OBD_GETDTC_0A_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DcmOBDGetDTC_0A(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDClrResetEmissionDiagInfo(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqOnboadMonitorResult(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_InternalOBDReqOnboadMonitorResultCall(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer,
  uint8 LucOBDMIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpResLength);
#endif

#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqCtlrOnboadSystem(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDRegVehicleInfo(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_DcmOBDRegVehicleInfoCall(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pReqData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  uint8 TxBufferSize,
  uint8 VIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pRespLength);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
