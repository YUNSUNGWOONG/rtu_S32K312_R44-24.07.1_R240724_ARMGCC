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
**  SRC-MODULE: Dcm_DspReadSSDTCInfo.h                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspReadSSDTCInfo                             **
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
** 0.0.2     05-May-2019   LamNV10        Add new function                    **
**                                        Dcm_DspProcessSubFFDataOrExtData    **
** 0.0.3     13-Oct-2020    LanhLT        Changes made as per #15766          **
** 1.0.12    30-Jun-2023    SY Kim        Refer #CP44-2255                    **
*******************************************************************************/

#ifndef DCM_DSPREADSSDTCINFO_H
#define DCM_DSPREADSSDTCINFO_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if ((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON) || \
     (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
extern FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecByDTCNum(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif

extern FUNC(uint32, DCM_CODE) Dcm_DspRepDTCSnapRecID(
  uint32 LulBufferSize);

extern FUNC(uint32, DCM_CODE) Dcm_DspProcessSubFFDataOrExtData(
  uint8 LucRecordNumber, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspUpdateBasicsOfEventData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_DSPREADSSDTCINFO_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
