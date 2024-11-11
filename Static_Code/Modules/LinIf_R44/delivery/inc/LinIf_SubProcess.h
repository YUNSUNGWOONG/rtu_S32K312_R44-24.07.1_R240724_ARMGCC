/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: LinIf_SubProcess.h                                            **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LINIF Sub Processing Functions types.            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By              Description                      **
********************************************************************************
** 1.0.13      21-Aug-2023   KhaLN1          #CP44-2481                       **
** 1.0.6       17-Oct-2022   KhaLN1          #CP44-563                        **
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/

#ifndef LINIF_SUBPROCESS_H
#define LINIF_SUBPROCESS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinIf.h"                /* LinIf header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: LinIf_SUD_MACRO_002 */
/*
 * AUTOSAR specification version information
 */
#define LINIF_SUBPROCESS_AR_RELEASE_MAJOR_VERSION  \
  (LINIF_AR_RELEASE_MAJOR_VERSION)
#define LINIF_SUBPROCESS_AR_RELEASE_MINOR_VERSION  \
  (LINIF_AR_RELEASE_MINOR_VERSION)
#define LINIF_SUBPROCESS_AR_RELEASE_REVISION_VERSION  \
  (LINIF_AR_RELEASE_REVISION_VERSION)

/*
 * File version information
 */
#define LINIF_SUBPROCESS_SW_MAJOR_VERSION  (LINIF_SW_MAJOR_VERSION)
#define LINIF_SUBPROCESS_SW_MINOR_VERSION  (LINIF_SW_MINOR_VERSION)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/** Redmine #13950: fixed MISRA violation **/
extern CONST(LinIf_FrameInfo, LINIF_DATA) LinIf_GaaFixedFrameInfo [LINIF_TWO];

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"
#if(LINTP_SUPPORT == STD_ON)
extern FUNC(void, LINIF_CODE) LinIf_SleepReqMainFunction (
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(void, AUTOMATIC, LINIF_CONST) LpTpChannelPtr,
  NetworkHandleType LddChnlIndex);

extern FUNC(void, LINIF_CODE) LinIf_ProcessPrevStatus(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelPtr,
  NetworkHandleType LddChnlIndex);

extern FUNC(void, LINIF_CODE) LinIf_ChangeToNullSchedule(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST) LpTpChannelPtr);

extern FUNC(void, LINIF_CODE) LinIf_SendFrame(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  VAR(uint16, LINIF_CONST) LusSchEntry,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelPtr,
  NetworkHandleType LddChnlIndex);
#else
extern FUNC(void, LINIF_CODE) LinIf_SleepReqMainFunction (
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex);

extern FUNC(void, LINIF_CODE) LinIf_ProcessPrevStatus(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex);

extern FUNC(void, LINIF_CODE) LinIf_ChangeToNullSchedule(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr);

extern FUNC(void, LINIF_CODE) LinIf_SendFrame(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  VAR(uint16, LINIF_CONST) LusSchEntry,
  NetworkHandleType LddChnlIndex);
#endif

extern FUNC(void, LINIF_CODE) LinIf_ChangeSchedule
  (P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex);

extern FUNC(uint8, LINIF_CODE) LinIf_CheckForIdToServe(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex);

extern FUNC(Std_ReturnType, LINIF_CODE) LinTp_TransmitDetCheck
  (PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, LINTP_APPL_CONST)
  PduInfoPtr);

extern FUNC(void, LINIF_CODE) LinTp_MainFunc (NetworkHandleType LddChnlIndex);

#if(LINTP_SUPPORT == STD_ON)
extern FUNC(void, LINIF_CODE) LinIf_ProcessStatusSRF
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr, P2CONST(LinTp_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpTpChannelPtr);

extern FUNC(void, LINIF_CODE) LinIf_ProcessStatusMRF
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr, P2CONST(LinTp_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpTpChannelPtr);
#endif /* #if(LINTP_SUPPORT == STD_ON) */

extern FUNC(void, LINIF_CODE) LinIf_ProcessStatusEventTrig
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr);

extern FUNC(void, LINIF_CODE) LinIf_ProcessStatusSporadic
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr);

extern FUNC(void, LINIF_CODE) LinIf_ProcessStatusUncond
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr);

#if((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON))
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */  
extern FUNC(P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST), LINIF_CODE)
                              LinIf_AssociatedBinarySearch(PduIdType LddPduId);
/* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */                              
#endif

#if (LINIF_SLAVE_SUPPORT == STD_ON)
extern FUNC(uint8, LINIF_CODE) LinIf_GetFrameIndex
                                (NetworkHandleType Channel, uint8 ddFrameId);
#endif

#if (STD_ON == LINIF_MASTER_SUPPORT)
extern FUNC(void, LINIF_CODE) LinIf_ProcessWakeUpConfirm(NetworkHandleType Channel);
extern FUNC(void, LINIF_CODE) LinIf_ProcessScheduleChanging(NetworkHandleType Channel
		, LinIf_SchHandleType* LddScheduler);
#endif

#if ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && (LINIF_DEV_ERROR_DETECT == STD_ON))
extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_DetGetTrcvWakeupReason(
  NetworkHandleType Channel,
  P2CONST(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINIF_APPL_DATA)
    TrcvWuReasonPtr);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_DetSetTrcvWakeupMode(
  NetworkHandleType Channel,
  LinTrcv_TrcvWakeupModeType LinTrcvWakeupMode);
#endif /* ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && (LINIF_DEV_ERROR_DETECT == STD_ON)) */

#if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
extern FUNC(boolean, LINIF_CODE) LinIf_InitAllChannels (void);
#else
extern FUNC(void, LINIF_CODE) LinIf_InitAllChannels (void);
#endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */

#if (LINIF_MASTER_SUPPORT == STD_ON)
extern FUNC(void, LINIF_CODE) LinIf_MainFunctionMaster (
  NetworkHandleType Channel,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr);

#if (LINTP_SUPPORT == STD_ON)
extern FUNC(void, LINIF_CODE) LinIf_SleepRequestedHandle (
  LinIf_SchHandleType Scheduler,
  NetworkHandleType Channel,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo);
#else
extern FUNC(void, LINIF_CODE) LinIf_SleepRequestedHandle (
  LinIf_SchHandleType Scheduler,
  NetworkHandleType Channel,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr);
#endif /* (LINTP_SUPPORT == STD_ON) */

#endif /* (LINIF_MASTER_SUPPORT == STD_ON) */

#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* LINIF_SUBPROCESS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
