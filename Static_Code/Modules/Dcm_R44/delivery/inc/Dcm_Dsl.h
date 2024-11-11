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
**  SRC-MODULE: Dcm_Dsl.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Dsl                                          **
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
** 0.0.2     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.3     13-Oct-2020   LanhLT         Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DSL_H
#define DCM_DSL_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_DslSetParameters(void);

extern FUNC(void, DCM_CODE) Dcm_DslTransmit(
  PduIdType TxPduId
  , boolean IsPeriodicTransmission
  , boolean IsRoeTransmission);

extern FUNC(void, DCM_CODE) Dcm_DslStatusReset(void);

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_DslCopyPeriodicTxData(
  PduIdType DcmTxPduId,
  PduInfoConstPtrType PduInfoPtr,
  PduLengthPtrType TxDataCntPtr);
#endif

#if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) \
     && (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DslCopyROETxData(
  PduInfoConstPtrType PduInfoPtr,
  PduLengthPtrType TxDataCntPtr);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
