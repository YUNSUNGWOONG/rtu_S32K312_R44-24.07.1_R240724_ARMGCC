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
**  SRC-MODULE: Dcm_DspNonPagedDTCSubFct.h                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspNonPagedDTCSubFct                         **
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

#ifndef DCM_DSPNONPAGEDDTCSUBFCT_H
#define DCM_DSPNONPAGEDDTCSUBFCT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm_PCTypes.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if(DCM_RPT_NOOFDTC == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspRptNoOfDTC(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_DemGetNumberOfFilteredDtc(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif

extern FUNC(void, DCM_CODE) Dcm_DspRptFailedConfirmedDTCInfo(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecIdentfn(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_DSPNONPAGEDDTCSUBFCT_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
