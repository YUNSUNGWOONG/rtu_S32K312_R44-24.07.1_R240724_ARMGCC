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
**  SRC-MODULE: Dcm_DspResponseOnEvent.h                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspResponseOnEvent                           **
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
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.3     02-Nov-2020   LanhLT         Changes made as per #16832          **
*******************************************************************************/

#ifndef DCM_DSPRESPONSEONEVENT_H
#define DCM_DSPRESPONSEONEVENT_H

#include "Dcm_PCTypes.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspReadROEDIDValue(
  uint16 DIDValue, 
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DIDSize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pBuffer);

#endif /*DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON*/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmResponseOnEvent(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_DspROEProcessSessionChange(void);

extern FUNC(void, DCM_CODE) Dcm_InitROE(void);

#if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
extern FUNC(void, DCM_CODE) Dcm_ReadRoeNonVolatileData(void);
#endif

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CheckRoeEventTriggered(void);

extern FUNC(void, DCM_CODE) Dcm_StoreRoeEventTriggeredInfo(
  uint8 Index);

extern FUNC(void, DCM_CODE) Dcm_ClearRoeEventTriggeredInfo(void);

extern FUNC(void, DCM_CODE) Dcm_SetFirstActivatedEvent(void);

extern FUNC(void, DCM_CODE) Dcm_SetNextActivatedEvent(void);

extern FUNC(uint8, DCM_CODE) Dcm_GetCurrentROEEventIndex(void);

extern FUNC(uint8, DCM_CODE) Dcm_GetROEEventTriggerdFlag(uint8 index);

#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspManagedDIDInternally(void);
#endif
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif /*DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON*/
#endif /* DCM_DSPRESPONSEONEVENT_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
