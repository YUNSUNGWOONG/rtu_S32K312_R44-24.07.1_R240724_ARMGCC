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
**  SRC-MODULE: Dcm_DspMemoryServices.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspMemoryService                             **
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
** 0.0.1     31-Dec-2019   HueKM          AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Changes made as per #14836          **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#ifndef DCM_DSPMEMORYSERVICES_H
#define DCM_DSPMEMORYSERVICES_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))

#if (0 < DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG)
extern FUNC(boolean, DCM_CODE) Dcm_IsAddrLenFormatIdSupported(
  uint8 AddressLenFormatId);
#endif

extern FUNC(uint32, DCM_CODE) Dcm_ReadMemoryAddressFromReqData(
  Dcm_Uint8ConstPtrType pReqData
  , uint8 MemAddrBytes);

extern FUNC(uint32, DCM_CODE) Dcm_ReadMemorySizeFromReqData(
  Dcm_Uint8ConstPtrType pReqData
  , uint8 MemSizeBytes);
#endif

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))

/* @Trace: SWS_Dcm_01158 will be implemented in generator */
extern FUNC(boolean, DCM_CODE) Dcm_IsReadMemoryRangeValid(
  uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_Uint8PtrType pFoundMemRngIndex);

extern  FUNC(uint8, DCM_CODE) Dcm_GetMemoryIdByRange(
  uint32 ulMemoryAddr,
  uint32 ulMemorySize);
#endif

#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadMemoryByAddress(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE)Dcm_DcmReadMemoryCall(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmWriteMemoryByAddress(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_DcmWriteMemoryCall(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
