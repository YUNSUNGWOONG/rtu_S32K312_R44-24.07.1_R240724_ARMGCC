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
**  SRC-MODULE: Dcm_Cbk.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Cbk                                          **
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
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.3     17-Nov-2020   HueKM          Changes Dcm_CopyTxData prototype    **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1637                    **
*******************************************************************************/

#ifndef DCM_CBK_H
#define DCM_CBK_H

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtrType;

typedef P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoConstPtrType;

typedef P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtrType;

typedef P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_CONST) RetryInfoConstPtrType;

typedef P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) PduLengthPtrType;

typedef P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) SduDataPtrType;

typedef P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) PduIdPtrType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                        Interface for PDU Router                            **
*******************************************************************************/
extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_StartOfReception(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthType TpSduLength
  , PduLengthPtrType BufferSizePtr);

extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyRxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

extern FUNC(void, DCM_APPL_CODE) Dcm_TpRxIndication(
  PduIdType Id
  , Std_ReturnType Result);

extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyTxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

extern FUNC(void, DCM_APPL_CODE) Dcm_TpTxConfirmation(
  PduIdType Id
  , Std_ReturnType Result);

extern FUNC(void, DCM_APPL_CODE) Dcm_TxConfirmation(
  PduIdType Id
  , Std_ReturnType Result);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
