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
**  SRC-MODULE: Dcm_DspOBDInternals.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspOBDInternals                              **
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
** 0.0.2     25-Apr-2020   LamNV10        Add pre-compile for Dcm_GetIDIndex()**
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DSPOBDINTERNALS_H
#define DCM_DSPOBDINTERNALS_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON))
extern FUNC(uint8, DCM_CODE) Dcm_DspGetAvailibiltyIDStatus(
  uint8 IDType,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pReqBuffer,
  uint8 IDCount,
  uint8 SID);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetConfigIDS1(
  uint8 IDValue,
  uint8 IDType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pIDSize);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSizeOfIDS(
  uint8 IDType,
  uint8 IDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pIDsSize,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxBuffer,
  uint8 SID);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetIDIndex(
  uint8 IDType,
  uint8 IDValue,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pIDIndex);

extern FUNC(uint32, DCM_CODE) Dcm_DspReadOBD_AvlInfo(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  uint32 BufferSize,
  uint8 IDCount,
  uint8 IDType);

extern FUNC(uint16, DCM_CODE) Dcm_DspReadOBD_1_DemInfo(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pRespLength,
  uint8 PIDCount);
#endif

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
extern FUNC(uint8, DCM_CODE) Dcm_GetMaskValue(uint8 IDValue);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetConfigIDS(
  uint8 IDValue,
  uint8 IDType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pIDSize);
#endif

#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadPIDData(
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) pPIDDataCfg);
#endif

#if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
/* To get the number of Filtered OBD DTCs for services 0x03,0x07,0x0A */
extern FUNC(void, DCM_CODE) Dcm_DemGetNumberOfOBDDTC(void);

/* To get the Filtered OBD DTCs for services 0x03,0x07,0x0A */
extern FUNC(uint32, DCM_CODE) Dcm_DspReadOBDDTCInfo(uint32 LulBufferSize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpNumOfDTCs);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_DSPOBDINTERNALS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
