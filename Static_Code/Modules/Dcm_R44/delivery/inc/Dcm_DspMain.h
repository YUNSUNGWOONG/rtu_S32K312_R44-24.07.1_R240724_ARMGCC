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
**  SRC-MODULE: Dcm_DspMain.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspMain                                      **
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
** 0.0.2     13-Oct-2020   HueKM          Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DSPMAIN_H
#define DCM_DSPMAIN_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* To update page */
extern FUNC(void, DCM_CODE) Dcm_DspUpdatePage(
  Dcm_MsgType PageBufPtr, Dcm_MsgLenType PageLen);

/* To process update page */
extern FUNC(void, DCM_CODE) Dcm_DspProcessUpdatePage(void);

extern FUNC(void, DCM_CODE) Dcm_DspCancelPagedBufferProcessing(void);
#endif

/* To provide confirmation */
extern FUNC(void, DCM_CODE) DspInternal_DcmConfirmation(
  Dcm_IdContextType IdContext
  , PduIdType RxPduId
  // , uint16 ConnectionId // TODO update later
  , Dcm_ConfirmationStatusType ConfirmStatus);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_DSPMAIN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
