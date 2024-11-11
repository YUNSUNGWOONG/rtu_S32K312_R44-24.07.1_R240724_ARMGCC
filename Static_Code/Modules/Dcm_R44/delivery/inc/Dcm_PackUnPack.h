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
**  SRC-MODULE: Dcm_PackUnPack.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_PackUnPack                                   **
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
** 0.0.2     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.3     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
*******************************************************************************/

#ifndef DCM_PACKUNPACK_H
#define DCM_PACKUNPACK_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(uint16, DCM_CODE) Dcm_UnPack2Byte(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData);

extern FUNC(uint16, DCM_CODE) Dcm_UnPack2ByteOrder(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData);

extern FUNC(uint32, DCM_CODE) Dcm_UnPack4Byte(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData);

extern FUNC(uint32, DCM_CODE) Dcm_UnPack4ByteOrder(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData);

extern FUNC(void, DCM_CODE) Dcm_UnPack1ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData);

extern FUNC(void, DCM_CODE) Dcm_UnPack2ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData);

extern FUNC(void, DCM_CODE) Dcm_UnPack4ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData);

extern FUNC(void, DCM_CODE) Dcm_Pack2Byte(
  uint16 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData);

extern FUNC(void, DCM_CODE) Dcm_Pack2ByteOrder(
  uint16 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData);

extern FUNC(void, DCM_CODE) Dcm_Pack4Byte(
  uint32 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData);

extern FUNC(void, DCM_CODE) Dcm_Pack4ByteOrder(
  uint32 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData);

extern FUNC(void, DCM_CODE) Dcm_Pack1ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData);

extern FUNC(void, DCM_CODE) Dcm_Pack2ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData);

extern FUNC(void, DCM_CODE) Dcm_Pack4ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
