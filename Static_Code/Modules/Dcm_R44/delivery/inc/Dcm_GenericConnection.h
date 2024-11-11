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
**  SRC-MODULE: Dcm_GenericConnection.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_GenericConnection                            **
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
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_GENERIC_CONNECTION_H
#define DCM_GENERIC_CONNECTION_H

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_InitGenericConnection(
  Dcm_ConfigConstPtrType pConfig);

extern FUNC(boolean, DCM_CODE) Dcm_ChkRxMetaDataPtr(
  uint8 ApiId
  , PduIdType Id
  , PduInfoConstPtrType Info);

extern FUNC(boolean, DCM_CODE) Dcm_ChkRxTargetAddress(
  PduIdType Id
  , PduInfoConstPtrType Info);

extern FUNC(void, DCM_CODE) Dcm_StoreSourceTesterAddress(
  PduIdType Id
  , PduInfoConstPtrType Info);

extern FUNC(void, DCM_CODE) Dcm_GetTxMetaDataPtr(
  PduIdType Id
  , PduInfoPtrType Info);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
