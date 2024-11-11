/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_Main.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of scheduled functions.                             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.1.11.0  10-Oct-2023   PhucNHM     CP44-2759                              **
** 1.1.10.0  30-May-2023   PhucNHM     CP44-2125 CP44-2038                    **
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267 CP44-1601                     **
** 1.1.8.0   15-Feb-2023   PhucNHM     CP44-1599 CP44-1600                    **
** 1.1.6.0   10-Dec-2022   PhucNHM     CP44-1243                              **
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-772                               **
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #29406 #28007 #28012       **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     06-Apr-2022   PhucNHM     R44-Redmine #24776 #25654              **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

/* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Main.h"     /* Com Main header file */
#include "Com_TxIpdu.h"   /* Com Tx I-PDU header file */
#include "Com_Pack.h"     /* Com Pack header file */
#include "Com_UnPack.h"   /* Com UnPack header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "PduR_Com.h"     /* PduR Com header file */
#include "Com_Error.h"    /* Com Error header file */
#include "Com_IpduGrp.h"  /* Com Ipdu Group header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif
#if(COM_IDSM_SUPPORT == STD_ON)
#include "IdsM_Cbk.h"     /* IdsM Cbk header file */
#endif
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This global array holds the memory size of signal based on its type */
/* polyspace +1 VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
CONST(uint8, COM_CONST) Com_GaaSigMemSize[COM_FIVE] 
= {COM_ONE, COM_TWO, COM_FOUR, COM_FOUR, COM_ZERO};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Declarations                                 **
*******************************************************************************/

#if((COM_TX_IPDU == STD_ON) && (COM_TX_TP_SUPPORT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_UpdrTpIpduSts(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR)  LpTransmitFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_IPDU == STD_ON) &&\
((COM_TX_RETRY_REQUEST == STD_ON) ||\
(COM_MAINFUNC_BASED_TRANSMIT == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_UpdrTxFlg(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL == STD_ON) &&\
((COM_RX_SIGNAL_FILTER == STD_ON) ||\
(COM_RX_SIGNAL_INVALID == STD_ON) ||\
(COM_RX_SIGNAL_UBDMREPLACE == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if (COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxSigProc_FltrAndUpdrBuffer(
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalData, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig,
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform,
  Com_SignalIdType LddRxSignalIndex);
#else
FUNC(void, COM_CODE) Com_RxSigProc_FltrAndUpdrBuffer(
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalData, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL == STD_ON) && (COM_RX_SIGNAL_NOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxSigProc_RxSigNotif(
P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal,
uint8 LucSigConfig);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_SIGNAL == STD_ON)
#if ((COM_RX_SIGNAL_FILTER == STD_ON) ||\
  (COM_RX_SIGNAL_INVALID == STD_ON) ||\
  (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if (COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxSigProc_SingleRxSigProc(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  PduLengthType LddSignalMemSize,
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig,
  Com_SignalIdType LddRxSignalIndex);
#else
FUNC(void, COM_CODE) Com_RxSigProc_SingleRxSigProc(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  PduLengthType LddSignalMemSize,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig,
  Com_SignalIdType LddRxSignalIndex);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_FILTER == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxGrpProc_SigGrpFltr(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpFltOutFlag,
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform);
#else
FUNC(void, COM_CODE) Com_RxGrpProc_SigGrpFltr(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpFltOutFlag);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_INVALID == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_SigGrpInv(
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_INVALID == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_SglInGrpProc(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) LpRxSigInGrp,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpInvalidFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_INVALID == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_SglGrpProc(
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig,
  P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST) LpRxInvOrFltSigGrp,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_UB == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_UpdrBitProc(
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_DM == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_DirectMainTransmit_TxStsUpd(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_IPDU_DM == STD_ON) && (COM_SIG_ERR_CBK_NOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxUpdateDmTimers_DmErrNotif(
  PduIdType LddNoOfTxIpduDm);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Transmit_IpduCntUpdr(PduIdType LddTxIpduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Transmit_IpduCalloutUpdr(
  PduIdType LddTxIpduId,
  P2VAR(Std_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpCalloutValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP == STD_ON) &&\
  ((COM_RX_SIGGROUP_UB == STD_ON) || \
  (COM_RX_SIGGROUP_INVALID == STD_ON) || \
  (COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON) || \
  (COM_RX_SIGGROUP_FILTER == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_RxGrpBuffUpdr(
  uint8 LucSigGroupConfig,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_IPDU == STD_ON) &&\
    ((COM_TX_IPDU_REPETITION == STD_ON) ||\
    ((COM_TX_IPDU_DM == STD_ON) || \
      ((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
      (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)))))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_TxModeHndl(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag,
  uint16 LusTxIpduStatusBit,
  PduIdType LddNoOfTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTimer);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_IPDU_PT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_PeriodicTmrUpdr(
  uint16 LusTxIpduStatusBit, 
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if((COM_TX_IPDU_PT == STD_ON) &&\
  (COM_TX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_UpdtPdTmrAndRept(
P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag,
P2VAR(uint16, AUTOMATIC, COM_VAR) LpTimer,
PduIdType LddNoOfTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP == STD_ON) &&\
  (COM_RX_SIGGROUP_NOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_RxGrpNotif(
  uint8 LucSigGroupConfig,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_PendingStatus(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if((COM_TX_IPDU == STD_ON) &&\
  (COM_TX_IPDU_REPETITION ==STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_RepeatCount(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_IPDU == STD_ON) &&\
  (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_MinDelayCheck(
  uint8 LucIpduConfig,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_ResetTimer(
  uint8 LucIpduConfig,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL_GW == STD_ON) ||\
 (COM_RX_SIGINGROUP_GW == STD_ON) ||\
 (COM_RX_SIGNAL_GW_DES == STD_ON))
#if((COM_RX_SIGNAL_UB == STD_ON) && (COM_RX_SIGNAL_GW_UB == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGWSigProcessing_UBCheck(
  P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST) LpRxGWIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpProcessFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if((COM_RX_SIGNAL_GW == STD_ON) ||\
 (COM_RX_SIGINGROUP_GW == STD_ON) ||\
 (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGWSigProcessing_SigGWBuff(
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) LpSignalMemSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_MainFunctionRx                                  **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This function perform the processing of the Com     **
**                        reception activities that are not directly initiated**
**                        by the calls from the RTE and PDU Router.           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxIpdu              **
**                                                 Com_GaaRxPduInfoPtr        **
**                                                 Com_GaaRxGWIpduStatus      **
**                                                 Com_GaaRxDMTimer           **
**                                                 Com_GaaInvRangeSigList     **
**                                                 Com_GblIsInvRangeSigPdu    **
**                                                 Com_GucInvRangeSigListIndex**
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_RxSigProcessing()      **
**                                                 Com_RxSigGrpProcessing()   **
**                                                 Com_RxUpdateDmTimers()     **
*******************************************************************************/
/* @Trace: SWS_Com_00471 SWS_Com_00224 
SWS_Com_00486 SWS_Com_00534 SWS_Com_00225 SWS_Com_00308 SWS_Com_00664 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFunctionRx(void)
{
  /* @Trace: Com_SUD_API_00306 */ 
  #if(COM_RX_IPDU == STD_ON)
  #if((COM_RX_IPDU_DEFERRED == STD_ON) || (COM_RX_IPDU_DM == STD_ON))
  /* Pointer to Rx I-Pdu structure */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Local variable to store Rx config */
  uint8 LucRxConfig;
  /* Local variable to store Rx PduId */
  PduIdType LddComRxPduId;
  #endif
  /* Local variable to store write index  
  uint16 LusWriteIndex;*/
  /* Redmine #15053: Local variable to iterate Com_GaaInvRangeSigList */
  #if(COM_IDSM_SUPPORT == STD_ON)
  Com_IdsMInfo LddIdsMInfo;
  uint8 LucInvRangeSigListIndex;
  #endif
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  
  CoreId = GetCoreID();
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  if(Com_GddComStatus == COM_UNINIT)
  {
    /* @Trace: Com_SUD_API_00307 */
    LucReturnValue = (uint8)E_NOT_OK;
  }
  if(LucReturnValue == (uint8)E_OK)
  {
    /* mainfunction is prcoess all notify remaining */
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    if(COM_TRUE == Com_GaaMulticoreMainNotifyFlag[CoreId])
    {
      /* @Trace: Com_SUD_API_00308 */
      Com_MulticoreMainNotify(CoreId);
      /* Clear request on this core */
      Com_GaaMulticoreMainNotifyFlag[CoreId] = COM_FALSE;
    }
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    
    #if(!((COM_RX_IPDU_DEFERRED == STD_ON) || (COM_RX_IPDU_DM == STD_ON)))
    /* @Trace: Com_SUD_API_01327 */
    /* clear all Ipdu List */
    Com_ResetReceiveIpduList();
    #else
    while(E_OK == LucReturnValue)
    {
      /* @Trace: Com_SUD_API_00309 */ 
      /* Getting RX PduId in local variable */
      LucReturnValue = Com_ReadReceiveIpduList(&LddComRxPduId);
      if(E_OK == LucReturnValue)
      {  
        /* @Trace: Com_SUD_API_00310 */
        /* Get the pointer to first Rx L-PDU in the receive history list */
        LpRxIpdu = &Com_GaaRxIpdu[LddComRxPduId];
        /* Get the configuration data for Rx Ipdu */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        LucRxConfig = LpRxIpdu->ucRxConfig;
        
        #if(COM_IDSM_SUPPORT == STD_ON)
        LddIdsMInfo.blIsInvRangeSigPdu = COM_FALSE;
        LddIdsMInfo.ucInvRangeSigListIndex = COM_ZERO;
        /* @Trace: Com_SUD_API_00311 */ 
        /* @Trace: Com_SUD_API_00312 */ 
        for(LucInvRangeSigListIndex = 0;
			LucInvRangeSigListIndex < 4; 
			LucInvRangeSigListIndex++)
        { 
          /* @Trace: Com_SUD_API_00313 */   
          LddIdsMInfo.aaInvRangeSigList[LucInvRangeSigListIndex] = 
			COM_SIG_RANGECHECK_DEF_ID;
        }
        #endif
        
        #if(COM_RX_IPDU_DEFERRED == STD_ON)
        /* Check whether Rx I-PDU status is Deferred */
        if((LucRxConfig & COM_RX_IPDU_DEFERRED_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_00314 */
          #if (STD_ON == COM_MULTI_CORE_SUPPORT)
          /* Clear Com_GaaMulticoreTriggerNotifyFlag before call Com_RxSigProcessing */
          Com_ClearTriggerNotifyFlag(COM_FALSE);
          #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
          #if(COM_RX_SIGNAL == STD_ON)
          /* Check whether  Rx signals are configured */
          if((LucRxConfig & COM_RX_IPDU_SIGNAL_CONFIG_MASK) != COM_FALSE)
          {
            /* Invoke Com_RxSigProcessing() function to process all the
            signals configured in an I-PDU */
            #if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
            /* @Trace: Com_SUD_API_00315 */
            Com_RxSigProcessing(LpRxIpdu,
                *(PduLengthType *)Com_GaaRxPduInfoPtr[LddComRxPduId].SduLength, 
				&LddIdsMInfo);
            #else
            /* @Trace: Com_SUD_API_01328 */
            Com_RxSigProcessing(LpRxIpdu,
                *(PduLengthType *)Com_GaaRxPduInfoPtr[LddComRxPduId].SduLength);
            #endif 
          }
          #endif /* #if(COM_RX_SIGNAL == STD_ON) */
          #if(COM_RX_SIGGROUP == STD_ON)
          /* Check whether  Rx signal groups are configured */
          if((LucRxConfig & COM_RX_IPDU_SIGGRP_CONFIG_MASK) != COM_FALSE)
          {
            
            /* Invoke Com_RxSigGrpProcessing() function to process all
            the signal groups configured in an I-PDU */
            #if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
            /* @Trace: Com_SUD_API_00316 */
            Com_RxSigGrpProcessing(LpRxIpdu,
                *(PduLengthType *)Com_GaaRxPduInfoPtr[LddComRxPduId].SduLength,
				&LddIdsMInfo);
            #else
            /* @Trace: Com_SUD_API_01329 */
            Com_RxSigGrpProcessing(LpRxIpdu,
                *(PduLengthType *)Com_GaaRxPduInfoPtr[LddComRxPduId].SduLength);
            #endif     
          }
          #endif /* #if(COM_RX_SIGGROUP == STD_ON) */
          #if (STD_ON == COM_MULTI_CORE_SUPPORT)
          /* @Trace: Com_SUD_API_00317 */ 
          /* Check Com_GaaMulticoreTriggerNotifyFlag after call Com_RxSigProcessing */
          Com_ProcessTriggerNotifyFlag();
          #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
          
          /* Redmine #15053: If IdsM is supported and this PDU has out-ranged signals/group signals, Report to IdsM */
          #if(COM_IDSM_SUPPORT == STD_ON)
          if(LddIdsMInfo.blIsInvRangeSigPdu == COM_TRUE)
          {
            /* @Trace: Com_SUD_API_00318 */
            /* Report to IdsM */
            IdsM_SigRangeCheckErrorReport(LddComRxPduId,
            (P2CONST(uint16, AUTOMATIC, COM_CONST)) 
				&LddIdsMInfo.aaInvRangeSigList[COM_ZERO], 
            (P2CONST(uint8, AUTOMATIC, COM_CONST)) 
				Com_GaaRxPduInfoPtr[LddComRxPduId].SduDataPtr,
            *(PduLengthType *)Com_GaaRxPduInfoPtr[LddComRxPduId].SduLength);
          }
          #endif
          
          #if(((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) &&\
            (COM_RX_SIG_GATEWAY == STD_ON)) || (COM_RX_SIGNAL_GW_DES == STD_ON))
          /* Check whether signal based gateway is configured */
          if((LucRxConfig & COM_RX_IPDU_GATEWAY_CONFIG_MASK) != COM_FALSE)
          {
            /* @Trace: Com_SUD_API_00319 */
            SchM_Enter_Com_RX_GW_STS_PROTECTION_AREA();
            /* Set the gateway I-PDU status */
            /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
            Com_GaaRxGWIpduStatus[LpRxIpdu->ucRxGWStsIndex]
                                                   |= LpRxIpdu->ucRxGWStsMask;
            #if (STD_ON == COM_MULTI_CORE_SUPPORT)
            Com_GaaRxGWIpduMulticoreStatus[LpRxIpdu->ucRxGWStsIndex] = 
                              (COM_ONE<<(COM_MULTI_CORE_MAX+COM_ONE)) - COM_ONE;
            #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
            SchM_Exit_Com_RX_GW_STS_PROTECTION_AREA();
          }
          #endif        
        } /* Check whether Rx I-PDU is configured as deferred or not */
        #endif /* #if(COM_RX_IPDU_DEFERRED == STD_ON) */
          
        #if(COM_RX_IPDU_DM == STD_ON)
        /* Check whether deadline monitoring is configured for Rx I-PDU */
        if((LucRxConfig & COM_RX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_00320 */
          #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Enter_Com_RX_DM_STS_PROTECTION_AREA();
          #endif
          Com_GaaRxDMTimer[LpRxIpdu->ddRxIpduDmIndex] = COM_INVALID_DM_TIMER;
          #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Exit_Com_RX_DM_STS_PROTECTION_AREA();
          #endif
        }
        #endif
      } 
    } /* Check for all received PDUs */
    #endif /* !((COM_RX_IPDU_DEFERRED == STD_ON) || (COM_RX_IPDU_DM == STD_ON)) */
    #if((COM_RX_IPDU_DM == STD_ON) || \
         (COM_RX_SIGNAL_UBDM == STD_ON) || \
         (COM_RX_SIGGROUP_UBDM == STD_ON))
    /*
      Check whether Rx deadline monitoring is configured for Rx I-PDU
      groups
    */
    /* @Trace: Com_SUD_API_00321 */
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    /* Clear Com_GaaMulticoreTriggerNotifyFlag before call Com_RxUpdateDmTimers */
    Com_ClearTriggerNotifyFlag(COM_FALSE);
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    Com_RxUpdateDmTimers();
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    /* Check Com_GaaMulticoreTriggerNotifyFlag after call Com_RxUpdateDmTimers */
    Com_ProcessTriggerNotifyFlag();
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    #endif
  } /* Check whether module is initialized */
  #endif  
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* @Traceability END -- SRS: SWS_Com_00471 SWS_Com_00224 
SWS_Com_00486 SWS_Com_00534 SWS_Com_00225 SWS_Com_00308 SWS_Com_00664 */

/*******************************************************************************
** Function Name        : Com_RxUpdateDmTimers                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is Com internal function. This function updates**
**                        deadline monitoring timers of Rx I-PDUs and signals **
**                        with an update bit.                                 **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxDm                **
**                                                 Com_GaaRxDmStatus          **
**                                                 Com_GaaRxDMTimer           **
**                        Function(s) invoked    : Com_RxSigNotifyOrReplace() **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if((COM_RX_IPDU_DM == STD_ON) || \
   (COM_RX_SIGNAL_UBDM == STD_ON) || \
   (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxUpdateDmTimers(void)
{ 
  /* @Trace: Com_SUD_API_00322 */
  /* Pointer to Rx deadline monitoring structure */
  P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm;
  #if(COM_RX_SIG_GATEWAY == STD_ON)
  /* Pointer to Rx Ipdu structure */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Pointer to Rx I-PDU configured for gateway structure */
  P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST) LpRxGWIpdu;
  #endif    
  /* Local variable to store timer value */
  uint32 LulTimer;
  /* Local variable to store number of Rx deadline monitoring counts */
  uint8 LucNoOfRxDm;
  /* Local variable to store deadline monitoring timer value */
  uint8 LddDmCount;
  /* Local variable to store status count */
  uint8 LucCount;
  uint8 LucRxDmIndex;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 LucReturnValue;
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  
  LddDmCount = COM_ZERO;
  /* Get the number of Rx deadline monitoring counts */
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01330 */
  LucNoOfRxDm = (uint8)COM_RX_IPDU_DM_COUNT;
  #else
  /* @Trace: Com_SUD_API_01331 */
  LucNoOfRxDm = (uint8)Com_GlNoOfRxIpduDMCnt;
  #endif
  /* @Trace: Com_SUD_API_01332 */
  /* Get the pointer to Rx deadline monitoring structure */
  LucRxDmIndex = COM_ZERO;
  LpRxDm = &Com_GaaRxDm[LucRxDmIndex];
  /* Loop for number of Rx deadline monitoring counts */
  do
  {
    if((Com_GaaRxIpduStatus[LpRxDm->ddRxpduId] != (PduIdType)COM_ZERO) 
      && (Com_GaaRxDmStatus[LddDmCount] != (PduIdType)COM_ZERO))
    {
      /* @Trace: Com_SUD_API_00323 */
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      COM_RXPDUID_CHECK_COREID((LpRxDm->ddRxpduId),LucReturnValue);

      if(LucReturnValue == (uint8)E_OK)
      #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
      {
        /* @Trace: Com_SUD_API_00324 */
        LucCount = LpRxDm->ucRxDmCount;
        do
        {
          /* @Trace: Com_SUD_API_00002 */
          /* Get the deadline monitoring timer value to local variable */
          LulTimer = Com_GaaRxDMTimer[LddDmCount];
          if(COM_INVALID_DM_TIMER == LulTimer)
          {
            /* @Trace: Com_SUD_API_00325 */
            #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
            SchM_Enter_Com_RX_DM_STS_PROTECTION_AREA();
            #endif
            /* Load the local value of deadline monitoring timer to Rx deadline
              monitoring timer  */
            Com_GaaRxDMTimer[LddDmCount] = (LpRxDm->ulRxDmTimeout);
            /* Decrement the count of the number of signals configured for Rx
                                                          deadline monitoring */
            #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
            SchM_Exit_Com_RX_DM_STS_PROTECTION_AREA();
            #endif
          }
          else if((uint16)COM_ZERO != LulTimer)
          {
            /* @Trace: Com_SUD_API_00326 */
            /* Decrement the deadline monitoring timer */
            LulTimer--;
            /* Check whether Rx deadline monitoring timer is equal to zero */
            if((uint32)COM_ZERO == LulTimer)
            {
              /* @Trace: Com_SUD_API_00327 */
              /* Copy the Rx deadline monitoring timeout value to local variable*/
              LulTimer = (LpRxDm->ulRxDmTimeout);
              Com_RxSigNotifyOrReplace(LpRxDm);
              #if(COM_RX_SIGNAL_FILTER == STD_ON)     
              /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter
              , when Rx Timeout is occurred - Fixed by AUTRON START*/
              Com_RxSigDMFilterReset(LpRxDm);
              /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter
              , when Rx Timeout is occurred - Fixed by AUTRON END*/     
              #endif
              #if(COM_RX_SIG_GATEWAY == STD_ON)
              LpRxIpdu = &Com_GaaRxIpdu[LpRxDm->ddRxpduId];
              if((LpRxIpdu->ucRxConfig & COM_RX_IPDU_GATEWAY_CONFIG_MASK) != 
                                                                      COM_FALSE)
              {
                /* @Trace: Com_SUD_API_00328 */
                LpRxGWIpdu = &Com_GaaRxGWIpdu[LpRxIpdu->ddRxGWIpduIndex];
                
                #if((COM_RX_SIGNAL_GW == STD_ON) ||\
				(COM_RX_SIGINGROUP_GW == STD_ON) ||\
				(COM_RX_SIGNAL_GW_DES == STD_ON))
                /* Invoke Com_RxGWSigProcessing() function to process all Rx
                signals configured for gateway */
                Com_RxGWSigProcessing(LpRxGWIpdu, COM_SIG_GW_STATUS_TOUT);
                #endif
              }
              #endif
              
            } /* Check whether Rx deadline monitoring timer is equal to zero */
            /* @Trace: Com_SUD_API_00330 */
            #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
            SchM_Enter_Com_RX_DM_STS_PROTECTION_AREA();
            #endif
            /* Load the local value of deadline monitoring timer to Rx deadline
              monitoring timer  */
            Com_GaaRxDMTimer[LddDmCount] = LulTimer;
            /* Decrement the count of the number of signals configured for Rx
                                                          deadline monitoring */
            #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
            SchM_Exit_Com_RX_DM_STS_PROTECTION_AREA();
            #endif
          } 
          else
          {
            /* Dummy loop to avoid QAC warning */
          }
          /* @Trace: Com_SUD_API_00331 */
          LucNoOfRxDm--;
          /* Get the pointer to n Rx deadline monitoring structure */
          LucRxDmIndex++;
          LpRxDm = &Com_GaaRxDm[LucRxDmIndex];
          LddDmCount++;
          --LucCount;
        }while (LucCount != COM_ZERO);
      }
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      else
      {
        /* @Trace: Com_SUD_API_00332 */
        LucNoOfRxDm -= LpRxDm->ucRxDmCount;
        LddDmCount += LpRxDm->ucRxDmCount;
        /* Get the pointer to n Rx deadline monitoring structure */
        LucRxDmIndex += LpRxDm->ucRxDmCount;
        LpRxDm = &Com_GaaRxDm[LucRxDmIndex];   
      }
      #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
    }
    else
    {
      /* @Trace: Com_SUD_API_00333 */
      LucNoOfRxDm -= LpRxDm->ucRxDmCount;
      LddDmCount += LpRxDm->ucRxDmCount;
      /* Get the pointer to n Rx deadline monitoring structure */
      LucRxDmIndex += LpRxDm->ucRxDmCount;
      LpRxDm = &Com_GaaRxDm[LucRxDmIndex];   
    }
  }while(LucNoOfRxDm != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_MainFunctionTx                                  **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : This function perform the processing of the Com     **
**                        transmission activities that are not directly       **
**                        initiated by the calls from the RTE and PDU Router. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxIpduStatus      **
**                                                   Com_GaaTxIpdu            **
**                                                   Com_GaaTxIpduStatusBit   **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxMode            **
**                                                   Com_GaaTxPeriodicTimer   **
**                                                   Com_GaaTxReptTimer       **
**                                                   Com_GaaTxReptCount       **
**                        Function(s) invoked    :   Det_ReportError()        **
**                                                   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
**                                                   SchM_Exit_Com()          **
**                                                   Com_Transmit()           **
**                                                   Com_TxUpdateDmTimers()   **
*******************************************************************************/

/* @Trace: SWS_Com_00478 
SWS_Com_00773 SWS_Com_00697 SWS_Com_00708 SWS_Com_00304
SWS_Com_00739 SWS_Com_00399 SWS_Com_00665 */
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02093, SRS_Multicore_Com_00001, SRS_Multicore_Com_00002,
  SRS_Multicore_Com_00003, SRS_Multicore_Com_00004, SRS_Multicore_Com_00005,
  SRS_Multicore_Com_00006, SRS_Multicore_Com_00007, SRS_Multicore_Com_00008,
  SRS_Multicore_Com_00009, SRS_Multicore_Com_00010
 */
FUNC(void, COM_CODE) Com_MainFunctionTx(void)
{
  /* @Trace: Com_SUD_API_00334 */
  /* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Code structure for optimal performance */
  #if(COM_TX_IPDU == STD_ON)
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  #if((COM_TX_IPDU_PT == STD_ON) ||\
    (COM_TX_IPDU_REPETITION == STD_ON) ||\
    ((COM_TX_IPDU_DM == STD_ON) || \
    ((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
    (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))))
  uint16 LusTimer;
  #endif
  
  /* Local variable to store no. of Tx Pdu */
  PduIdType LddNoOfTxIpdu;

  uint8 LucTxMode;

  uint16 LusTxIpduStatusBit;
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

  /* Initializing variable to None mode */
  boolean LblTransmitFlag;
  /* Check whether module is initialized */
  
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  if(Com_GddComStatus == COM_UNINIT)  
  {
    /* @Trace: Com_SUD_API_00335 */
    LucReturnValue = (uint8)E_NOT_OK;
  }
  if(LucReturnValue == (uint8)E_OK)
  {
    
    #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
    /* @Trace: Com_SUD_API_00336 */
    /* Get the number of Tx I-PDU  */
    LddNoOfTxIpdu = Com_GlNoOfTxIpdu;
    #else
    /* @Trace: Com_SUD_API_01333 */
    /* Get the number of Tx I-PDU  */
    LddNoOfTxIpdu = (PduIdType)COM_TX_IPDU_COUNT;
    #endif
    /* Loop for number of Tx I-PDU  */
    do
    {
      /* @Trace: Com_SUD_API_00337 */
      LddNoOfTxIpdu--;
      /* Get the pointer to Tx Ipdu */
      LpTxIpdu = &Com_GaaTxIpdu[LddNoOfTxIpdu];
      /* Get Mode of IPDu*/
      LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];

      #if((COM_TX_IPDU_TMS_SIG_BASED != STD_ON) && \
      (COM_TX_IPDU_TMS_EXPLICIT != STD_ON) && \
      (COM_TX_RETRY_REQUEST != STD_ON) && \
      (COM_TX_IPDU_REPETITION != STD_ON) && \
      (COM_TX_IPDU_MINDELAY_ENABLED != STD_ON) && \
      (COM_TX_IPDU_PT != STD_ON))
      if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
      #endif     
      {
        /* @Trace: Com_SUD_API_00338 */ 
        LblTransmitFlag = COM_FALSE;  
      }
      
      /* @Trace: Com_SUD_API_00339 */
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      COM_TXPDUID_CHECK_COREID(LddNoOfTxIpdu,LucReturnValue);
      #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
      /* Check whether I-PDU group is started */
      if(
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
       (LucReturnValue == (uint8)E_OK)&&
      #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
         (Com_GaaTxIpduStatus[LddNoOfTxIpdu] != (PduIdType)COM_ZERO))
      {
        /* @Trace: Com_SUD_API_00340 */
        SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        #if((COM_TX_IPDU_DEFERRED != STD_ON) && \
            (COM_TX_IPDU_DM != STD_ON) && \
            (COM_TX_IPDU_TMS_SIG_BASED != STD_ON) && \
            (COM_TX_IPDU_TMS_EXPLICIT != STD_ON) && \
            (COM_TX_RETRY_REQUEST != STD_ON) && \
            (COM_TX_IPDU_REPETITION != STD_ON))
        if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
        #endif
        {
          /* @Trace: Com_SUD_API_00341 */
          LusTxIpduStatusBit = Com_GaaTxIpduStatusBit[LddNoOfTxIpdu];
        }
        /* @Trace: Com_SUD_API_00342 */
        Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &= ((uint16)
                                       (COM_TX_CONFIRM_STATUS_CLEAR_MASK & 
                                        COM_TX_PT_STATUS_CLEAR_MASK & 
                                        COM_TX_RETRY_STATUS_CLEAR_MASK & 
                                        COM_TX_DM_STATUS_CLEAR_MASK &
                                        COM_TX_MAINFUNC_SEND_STATUS_CLEAR_MASK &
                                        COM_TX_REPT_CONFIRM_HANDLE_CLEAR_MASK &
                                        COM_TX_REPT_STATUS_CLEAR_MASK));
        SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      
        #if((COM_TX_IPDU_DEFERRED == STD_ON) || (COM_TX_IPDU_DM == STD_ON))
        #if(COM_MAINFUNC_BASED_TRANSMIT == STD_ON)
        /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and could be changed in another configuration" */
        if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
        {
          /* @Trace: Com_SUD_API_00343 */
          Com_DirectMainTransmit(
            LusTxIpduStatusBit, LpTxIpdu, LpTxMode, LddNoOfTxIpdu);
        }
        else
        #endif
        {
          #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
          /* @Trace: Com_SUD_API_00344 */
          Com_IndirectMainTransmit(
            LusTxIpduStatusBit, LpTxIpdu, LddNoOfTxIpdu);
          #endif
        }
        #endif
        
        #if((COM_TX_IPDU_TMS_SIG_BASED != STD_ON) && \
          (COM_TX_IPDU_TMS_EXPLICIT != STD_ON) &&\
          (COM_TX_RETRY_REQUEST != STD_ON) && \
          (COM_TX_IPDU_REPETITION != STD_ON) && \
          (COM_TX_IPDU_MINDELAY_ENABLED != STD_ON) && \
          (COM_TX_IPDU_PT != STD_ON))
        if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
        #endif        
        { 
          #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
            (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
          /* Check if the transmission mode is configured as true/false */
          if((LusTxIpduStatusBit & COM_TX_TMS_STATUS_MASK) == COM_FALSE)
          {
            /* @Trace: Com_SUD_API_00346 */
            LpTxMode = 
                &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex
                +(PduIdType)COM_ONE];
          }

          /* @Trace: Com_SUD_API_00348 */
          #if(COM_TX_IPDU_PT == STD_ON)
          Com_MainFuncTx_PeriodicTmrUpdr(LusTxIpduStatusBit, LpTxMode, LpTxIpdu);
          #endif
          #endif

          LucTxMode = LpTxMode->ucTxMode;
          /* Check whether current Tx mode is none */
          if(LucTxMode != COM_TX_NONE_MODE)
          {
            /* @Trace: Com_SUD_API_01420 */
            #if(COM_TX_IPDU_PT == STD_ON)
            Com_MainFuncTx_UpdtPdTmrAndRept(LpTxMode, LpTxIpdu, 
              &LblTransmitFlag, &LusTimer, LddNoOfTxIpdu);
            #endif
            
            #if((COM_TX_IPDU_REPETITION == STD_ON) ||\
              ((COM_TX_IPDU_DM == STD_ON) || \
              ((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
              (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))))
            Com_MainFuncTx_TxModeHndl(LpTxMode, LpTxIpdu, &LblTransmitFlag, 
              LusTxIpduStatusBit, LddNoOfTxIpdu, &LusTimer);
            #endif

          } /* Check whether current Tx mode is not none */

          #if((COM_TX_RETRY_REQUEST == STD_ON) ||\
            (COM_MAINFUNC_BASED_TRANSMIT == STD_ON))
          /* @Trace: Com_SUD_API_01421 */
          Com_MainFuncTx_UpdrTxFlg(LusTxIpduStatusBit, LpTxMode, 
            &LblTransmitFlag);
          #endif
        }
        /* @Trace: Com_SUD_API_01422 */
        #if(COM_TX_TP_SUPPORT == STD_ON)
        Com_MainFuncTx_UpdrTpIpduSts(LpTxIpdu, LddNoOfTxIpdu, 
          &LblTransmitFlag);
        #endif
        #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
        /* Check whether Ipdu is transmitted successfully */
        if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != (COM_ZERO))
        {
          /* @Trace: Com_SUD_API_00362 */
          Com_MinDelayTxHandle(LpTxIpdu, LddNoOfTxIpdu, &LblTransmitFlag); 
        }
        #endif
        #if((COM_TX_IPDU_TMS_SIG_BASED != STD_ON) && \
          (COM_TX_IPDU_TMS_EXPLICIT != STD_ON) &&\
          (COM_TX_RETRY_REQUEST != STD_ON) && \
          (COM_TX_IPDU_REPETITION != STD_ON) && \
          (COM_TX_IPDU_MINDELAY_ENABLED != STD_ON)&& \
          (COM_TX_IPDU_PT != STD_ON) && (COM_TX_TP_SUPPORT != STD_ON))
        if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
        #endif
        {
          /* Check whether Tx bit is set to one */
          if(COM_TRUE == LblTransmitFlag)
          {  
            /* @Trace: Com_SUD_API_00363 */      
            (void)Com_Transmit(LddNoOfTxIpdu);
          }    
        }    
      } /* Check whether Tx I-PDUs is active or not */
    }while (LddNoOfTxIpdu != (PduIdType)COM_ZERO);
  
    #if(COM_TX_IPDU_DM == STD_ON)
    /* @Trace: Com_SUD_API_00364 */
    Com_TxUpdateDmTimers();
    #endif
  } /* Check whether module is initialized */

  #if((COM_TX_IPDU_DEFERRED != STD_ON) && \
    (COM_TX_IPDU_TMS_SIG_BASED != STD_ON) && \
    (COM_TX_IPDU_TMS_EXPLICIT != STD_ON) && \
    (COM_TX_IPDU_REPETITION != STD_ON) && \
    (COM_TX_IPDU_DM != STD_ON) && \
    (COM_TX_IPDU_MINDELAY_ENABLED != STD_ON) && \
    (COM_TX_RETRY_REQUEST != STD_ON))
  COM_UNUSED(LusTxIpduStatusBit);
  #endif
  #endif
}
  /* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Code structure for optimal performance */  
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* @Traceability END -- SRS:  SWS_Com_00478 
SWS_Com_00773 SWS_Com_00697 SWS_Com_00708 SWS_Com_00304
SWS_Com_00739 SWS_Com_00399 SWS_Com_00665 */

/*******************************************************************************
** Function Name        : Com_Transmit                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function initiate Tx request for an I-PDU to   **
**                        the lower layer. It also invokes I-PDU callout to   **
**                        the upper layer if configured.                      **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant for same Tx I-PDU.                    **
**                        Reentrant for different Tx I-PDUs.                  **
**                                                                            **
** Input Parameters     : LpTxIpdu                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaTxPduInfoPtr       **
**                                                  Com_GaaTxIpduCounter      **
**                                                  Com_GaaTxTPIpdu           **
**                                                  Com_GaaTxDynSigLength     **
**                                                  Com_GaaTxMDTimer          **
**                                                  Com_GaaTxMDTimeout        **
**                                                  Com_GaaTxUpdateBit        **
**                                                  Com_GaaTxIpduStatusBit    **
**                                                  Com_GaaTxTPStatus         **
**                                                  Com_GaaCounterStatusFlag  **
**                        Function(s) invoked    :  SchM_Enter_xxx()          **
**                                                  SchM_Exit_xxx()           **
**                                                  PduR_ComTransmit()        **
**                                                  Com_TxCounterUpdate()     **
**                                                  Com_TxClearUpdateBit()    **
**                                                  Com_TransIpduCounter()    **
**                                                  pIpduCallout              **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_Transmit
  (PduIdType LddTxIpduId)
{
  /* @Trace: Com_SUD_API_00365 */
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr;
  #if(COM_TX_TP_SUPPORT == STD_ON)
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  #endif
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  /* Local variable to store return value */
  Std_ReturnType LddReturnValue;
  #if(COM_TX_IPDU_CALLOUT == STD_ON)
  boolean LblCalloutValue;
  #endif
  LpTxIpdu = &Com_GaaTxIpdu[LddTxIpduId];
  /* Get the pointer to PduInfoPtr structure */
  LpPduInfoPtr = &Com_GaaTxPduInfoPtr[LddTxIpduId];  

  #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
  Com_Transmit_IpduCntUpdr(LddTxIpduId);
  #endif

  #if(COM_TX_IPDU_CALLOUT == STD_ON)
  Com_Transmit_IpduCalloutUpdr(LddTxIpduId, &LddReturnValue, &LblCalloutValue);
  #endif

  #if((COM_TX_IPDU_CALLOUT == STD_ON))
  /* Check whether I-PDU callout return value is E_OK */
  if(COM_TRUE == LblCalloutValue)
  #endif
  {
    /* @Trace: Com_SUD_API_00369 */
    SchM_Enter_Com_TX_IPDU_DATA_PROTECTION();
    #if(COM_TX_DYN_SUPPORT == STD_ON)
    if((LpTxIpdu->ucIpduType == COM_DYN_IPDU) 
      && (LpTxIpdu->ddTxIpduDynLegthRef != COM_INVALID_TXID_PARAM))
    {
      /* @Trace: Com_SUD_API_00370 */
      LpPduInfoPtr->SduLength = 
                              (PduLengthType)((LpTxIpdu->ddTxNonDynLength) +
        Com_GaaTxDynSigLength[LpTxIpdu->ddTxIpduDynLegthRef]);
    }
    #endif
    /* @Trace: Com_SUD_API_00371 */
    LddReturnValue = PduR_ComTransmit(LpTxIpdu->ddTxIpduId, LpPduInfoPtr);
    /* Check whether lower layer's return value is E_OK and
       update bit needs to be cleared */
    if((uint8)E_OK == LddReturnValue)
    {
      /* @Trace: Com_SUD_API_00372 */
      Com_GaaTxIpduStatusBit[LddTxIpduId] &= (uint16)
                                        (COM_TX_RETRY_STATUS_CLEAR_MASK & 
                                         COM_TX_CONFIRM_STATUS_CLEAR_MASK);
      Com_GaaTxIpduStatusBit[LddTxIpduId] |= (COM_TX_REQ_STATUS_MASK);
      
      #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
      /* Check whether minimum delay timer is configured */
      if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_ZERO)
      {
        /* Check whether minimum delay timer is equal to zero */
        if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] == (uint16)COM_ZERO)
        {
          /* Load minimum delay timer with the configured value plus one */
          /* #1517 : remove the plus one code for preventing MDT delay */
          /* leave the FEATURE in order to specify major point 
          of both transmit mode */
          /* #2022 MDTForCyclicTransmission related compile error 
          & incorrect operation is fixed(ref 4.2.1 Com Spec) */
          #if(COM_ENABLE_MDT_CYCLIC == STD_ON)
          /* @Trace: Com_SUD_API_01335 */
          Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex]  =
                       Com_GaaTxMDTimeout[LpTxIpdu->ddTxMDTimerIndex];
          #else
          if((Com_GaaTxIpduStatusBit[LddTxIpduId] 
            & COM_TX_REPT_CONFIRM_HANDLE_MASK) == COM_FALSE)
          {
            /* @Trace: Com_SUD_API_00373 */
            Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] =
            Com_GaaTxMDTimeout[LpTxIpdu->ddTxMDTimerIndex];
          }
          #endif
        }
      }
      #endif
      #if(COM_TX_SIGNAL_UB == STD_ON)
      /* Check whether update bit needs to be cleared */
      if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_UB_CONFIG_MASK) != COM_ZERO)
      {
        #if(COM_TX_TP_SUPPORT == STD_ON)
        if(LpTxIpdu->ucTxTPRef == COM_INVALID_NONE)
        #endif
        {
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          if(Com_GaaTxUpdateBit[LpTxIpdu->ddTxIpduUbIndex].ucUBConfig ==
                                            COM_TX_IPDU_UB_TRANSMIT_CONFIG_MASK)
          {
            /* @Trace: Com_SUD_API_00374 */
            Com_TxClearUpdateBit(LpTxIpdu, LpPduInfoPtr->SduDataPtr);
          }
        }
      }
      #endif/*#if(COM_TX_SIGNAL_UB == STD_ON)*/

      #if(COM_TX_TP_SUPPORT == STD_ON)
      /* If IPDU is TP or DYN, lock the buffer */
      if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
      {
        /* @Trace: Com_SUD_API_00375 */
        /* Get the pointer to TP structure  */
        LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
        Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] |=
                                                (LpTxTPIpdu->ucTxTPStatusMask);
      }
      #endif
    } /* Check whether lower layer's return value is E_OK */
    else
    {

    /*SWS_Com_00698*/
      #if((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) &&\
        (COM_TX_RETRY_REQUEST == STD_OFF))
      /* Check whether minimum delay timer is configured */
      if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_ZERO)
      {
        /* Check whether minimum delay timer is equal to zero */
        if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] == (uint16)COM_ZERO)
        {
          /* Load minimum delay timer with the configured value plus one */
          /* #1517 : remove the plus one code for preventing MDT delay */
          /* leave the FEATURE in order to specify major point 
          of both transmit mode */
          /* #2022 MDTForCyclicTransmission related compile error 
          & incorrect operation is fixed(ref 4.2.1 Com Spec) */
          #if(COM_ENABLE_MDT_CYCLIC == STD_ON)
          /* @Trace: Com_SUD_API_01336 */
          Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex]  =
                       Com_GaaTxMDTimeout[LpTxIpdu->ddTxMDTimerIndex];
          #else
          if((Com_GaaTxIpduStatusBit[LddTxIpduId] 
            & COM_TX_REPT_CONFIRM_HANDLE_MASK) == COM_FALSE)
          {
            /* @Trace: Com_SUD_API_00376 */
            Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] =
            Com_GaaTxMDTimeout[LpTxIpdu->ddTxMDTimerIndex];
          }
          #endif
        }
      }
      #endif
    
    
      #if(COM_TX_RETRY_REQUEST == STD_ON)
      /* @Trace: Com_SUD_API_00377 */
      /* Set Retry Bit */
      Com_GaaTxIpduStatusBit[LddTxIpduId] |= COM_TX_RETRY_STATUS_MASK;
      #endif
      
      #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
      if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
      {
        /* @Trace: Com_SUD_API_00378 */
        Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter] = 
                                                          COM_COUNTER_E_PENDING;
        Com_TransIpduCounter(LpTxIpdu);
      }
      #endif
    }
    /* @Trace: Com_SUD_API_00379 */
    SchM_Exit_Com_TX_IPDU_DATA_PROTECTION();
  }
  #if((COM_TX_IPDU_CALLOUT == STD_ON))
  else
  {
    #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
    if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
    {
      /* @Trace: Com_SUD_API_00380 */ 
      Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter] = 
                                                        COM_COUNTER_E_PENDING;
      Com_TransIpduCounter(LpTxIpdu);
    }
    #endif  
  }
  #endif
  /* @Trace: Com_SUD_API_00381 */
  return(LddReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_MainFunctionRouteSignals                        **
**                                                                            **
** Service ID           : 0x1A                                                **
**                                                                            **
** Description          : This function forwards the received signals, which  **
**                        are to be routed from received I-PDUs to transmit   **
**                        I-PDUs.                                             **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxGWIpdu            **
**                                                 Com_GaaRxGWIpduStatus      **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 Com_RxGWSigProcessing()    **
*******************************************************************************/
#if((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) &&\
  ((COM_RX_SIGNAL_GW == STD_ON) ||\
  (COM_RX_SIGINGROUP_GW == STD_ON) ||\
  (COM_RX_SIGNAL_GW_DES == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void)
{  
  /* @Trace: Com_SUD_API_00382 */
  /* Pointer to Rx I-PDU configured for gateway structure */
  P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST) LpRxGWIpdu;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpIpduStatus;
  /* Local variable to store signal count */
  uint8 LucNoOfIpduStsCount;
  /* Local variable to store Ipdu status */
  uint8 LucIpduStatus;
  /* Local variable to store count */
  uint8 LucCount;
  PduIdType LddRxGWIpduIndex;
  PduIdType LddRxGWIpduStatusIndex;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  uint8 CoreIdMask;
  /* Pointer to Rx I-PDU configured for gateway structure */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpIpduMulticoreStatus;
  /* Local variable to store Ipdu status */
  uint8 LucIpduMulticoreStatus;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  /* Check whether module is initialized */

   /* Local variable to store return value */
  uint8 LucReturnValue;
  LucReturnValue = (uint8)E_OK;
  /* Initialize error flag to false */
  if(Com_GddComStatus == COM_UNINIT)  
  {
    /* @Trace: Com_SUD_API_00383 */
    LucReturnValue = (uint8)E_NOT_OK;
  }
  /* Check whether module is initialized */
  if(LucReturnValue == (uint8)E_OK)
  {
    /* @Trace: Com_SUD_API_00384 */
    /* Get the pointer to gateway I-PDU status */
    LddRxGWIpduStatusIndex = (PduIdType)COM_ZERO;
    /* Get the pointer to first gateway Rx I-PDU structure */
    LddRxGWIpduIndex = (PduIdType)COM_ZERO;
    
    /* Get the number of Rx I-PDUs configured for gateway */
    LucNoOfIpduStsCount = COM_RX_IPDU_GWSTATUS_COUNT;
    /* Initialize counter to zero */
    LucCount = COM_ZERO;
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    CoreId = GetCoreID();
    CoreIdMask = COM_ONE<<CoreId;
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    /* Loop for the number of gateway Rx I-PDUs (I-PDUs configured for gateway)
    */
    do
    {
      /* @Trace: Com_SUD_API_00385 */
      /* Get the pointer to n I-PDU status */
      LpIpduStatus = &Com_GaaRxGWIpduStatus[LddRxGWIpduStatusIndex];
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      LpIpduMulticoreStatus = &Com_GaaRxGWIpduMulticoreStatus[LddRxGWIpduStatusIndex];
      #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    
      /* Get the pointer to n gatewayed Rx I-PDU structure */
      LddRxGWIpduIndex = LddRxGWIpduIndex + (PduIdType)LucCount;
      /* Initialize counter to eight */
      LucCount = COM_EIGHT;
      /* Get the I-PDU status of gatewayed I-PDU to local variable */
      LucIpduStatus = *LpIpduStatus;
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      LucIpduMulticoreStatus = *LpIpduMulticoreStatus;
      #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
      /* Check whether I-PDU status is set */
      if((LucIpduStatus != COM_ZERO)
        #if (STD_ON == COM_MULTI_CORE_SUPPORT)
          &&((LucIpduMulticoreStatus & CoreIdMask)!= COM_ZERO)
        #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
        )
      {
        /* @Trace: Com_SUD_API_00386 */
        #if (STD_ON == COM_MULTI_CORE_SUPPORT)
        LucIpduMulticoreStatus &= ~CoreIdMask;
        /* Reset the I-PDU status */
        *LpIpduMulticoreStatus = LucIpduMulticoreStatus;
        /* Check whether I-PDU status is set */
        if(COM_ZERO == LucIpduMulticoreStatus) 
        #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
        {
          /* @Trace: Com_SUD_API_00387 */
          SchM_Enter_Com_RX_GW_STS_PROTECTION_AREA();
          /* Reset the I-PDU status */
          *LpIpduStatus = COM_ZERO;
          SchM_Exit_Com_RX_GW_STS_PROTECTION_AREA();
        }
        /* Loop for all I-PDU status */
        while (LucIpduStatus != COM_ZERO)
        {
          /* Check whether the status of gatewayed I-PDU is not false */
          if((LucIpduStatus & (COM_ONE)) != COM_FALSE)
          {
            /* @Trace: Com_SUD_API_00388 */
            LpRxGWIpdu = 
            (P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST))
            &Com_GaaRxGWIpdu[LddRxGWIpduIndex];
            
            #if((COM_RX_SIGNAL_GW == STD_ON) ||\
              (COM_RX_SIGINGROUP_GW == STD_ON) ||\
              (COM_RX_SIGNAL_GW_DES == STD_ON))
            /* Invoke Com_RxGWSigProcessing() function to process all Rx
            signals configured for gateway */
            Com_RxGWSigProcessing(LpRxGWIpdu, COM_SIG_GW_STATUS_NORMAL);
            #endif
          }
          /* Get the pointer to the n gatewayed Rx I-PDU */
          /* @Trace: Com_SUD_API_00390 */
          LddRxGWIpduIndex++;
          #if (COM_RX_GW_COUNT > COM_MACRO_ONE)
          if(LddRxGWIpduIndex < (PduIdType)COM_RX_GW_COUNT)
          {
            /* @Trace: Com_SUD_API_00391 */
            /* Shift I-PDU status right by one to get the n status */
            LucIpduStatus >>= COM_ONE;
          }
          else
          #endif
          {
            /* @Trace: Com_SUD_API_00392 */
            /* Set I-PDU status as zero */
            LucIpduStatus = COM_ZERO;
          }

          /* @Trace: Com_SUD_API_00393 */
          /* Decrement the counter */
          LucCount--;
        }
      } /* Check whether I-PDU status is set */
      /* Decrement the count of the number of Rx I-PDUs configured for
      gateway */
      /* @Trace: Com_SUD_API_00394 */
      LucNoOfIpduStsCount--;
      LddRxGWIpduStatusIndex++;

    }while(LucNoOfIpduStsCount != COM_ZERO);
  } /* Report to DET, if module is not initialized */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_TxUpdateDmTimers                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function update deadline monitoring timers of  **
**                        Tx I-PDUs .                                         **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxIpduDm            **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaTxDMTimer           **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxMode              **
**                                                 Com_GaaTxMDTimer           **
**                                                 Com_GaaSigErrorCbk         **
**                                                 Com_GaaTxReptCount         **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxTPStatus          **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 PduR_ComCancelTransmit()   **
**                                                 pSigErrorCbk               **
*******************************************************************************/
#if(COM_TX_IPDU_DM == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxUpdateDmTimers(void)
{
  /* @Trace: Com_SUD_API_00395 */
  #if(COM_TX_CANCEL_SUPPORT == STD_ON)
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  #if(COM_TX_TP_SUPPORT == STD_ON)
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  #endif
  #endif
  PduIdType LddTxIpduIndex;
  /* Local variable to store no. of TxIpdu configured for Deadline monitoring */
  PduIdType LddNoOfTxIpduDm;
  /* Local variable to store timer */
  uint16 LusTimer;  
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  Std_ReturnType LucReturnValue;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

  /* Get the number of Tx I-PDUs configured for deadline monitoring */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01337 */
  LddNoOfTxIpduDm = COM_TX_IPDU_DM_COUNT;
  #else
  /* @Trace: Com_SUD_API_01338 */
  LddNoOfTxIpduDm = Com_GlNoOfTxIpduDMCnt;
  #endif
  /* Loop for the number of Tx I-PDUs configured for deadline monitoring */  
  while(LddNoOfTxIpduDm != (PduIdType)COM_ZERO)
  {  
    /* @Trace: Com_SUD_API_00396 */
    --LddNoOfTxIpduDm;
    LddTxIpduIndex = Com_GaaTxIpduDm[LddNoOfTxIpduDm].ddComTxPduId;
    #if(COM_TX_CANCEL_SUPPORT == STD_ON)
    LpTxIpdu = &Com_GaaTxIpdu[LddTxIpduIndex];
    #endif
    if(Com_GaaTxIpduStatus[LddTxIpduIndex] != (PduIdType)COM_ZERO)
    {
      {
        /* @Trace: Com_SUD_API_00397 */
        LusTimer = 
                Com_GaaTxDMTimer[Com_GaaTxIpdu[LddTxIpduIndex].ddTxIpduDmIndex];
        if(LusTimer != (uint16)COM_ZERO)
        {
          #if (STD_ON == COM_MULTI_CORE_SUPPORT)
          /* @Trace: Com_SUD_API_01448 */
          COM_TXPDUID_CHECK_COREID((LddTxIpduIndex),LucReturnValue);

          if(LucReturnValue == (uint8)E_OK)
          #endif
          {
            /* @Trace: Com_SUD_API_00398 */
            --LusTimer;

            if((uint16)COM_ZERO == LusTimer)
            {
              /* @Trace: Com_SUD_API_00399 */
              /* Reset Retry bit after deadline monitoring is over */
              SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
              Com_GaaTxIpduStatusBit[LddTxIpduIndex] &=
                (uint16)(~(COM_TX_RETRY_STATUS_MASK | COM_TX_REQ_STATUS_MASK));
              SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
              #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON)||\
                (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
              if(((Com_GaaTxIpdu[LddTxIpduIndex].ucTxConfig &
                                    COM_TX_IPDU_TMS_CONFIG_MASK) == COM_FALSE)\
                ||(Com_GaaTxIpdu[LddTxIpduIndex].ucTxConfigExtn == COM_FALSE))
              #endif
              {
                if(Com_GaaTxMode[Com_GaaTxIpdu[LddTxIpduIndex].
                  ddTrueTxModeIndex].ucTxMode == COM_TX_NONE_MODE)
                {
                  /* @Trace: Com_SUD_API_00400 */
                  LusTimer = Com_GaaTxIpduDm[LddNoOfTxIpduDm].usDmTimeout;
                  SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
                  Com_GaaTxIpduStatusBit[LddTxIpduIndex] |=
                                                      (COM_TX_REQ_STATUS_MASK);
                  SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
                }
              }
              #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
              /* Check whether minimum delay timer is configured for I-PDU */
              if((Com_GaaTxIpdu[LddTxIpduIndex].ucTxConfig &
                                      COM_TX_IPDU_MDT_CONFIG_MASK) != COM_FALSE)
              {
                /* @Trace: Com_SUD_API_00401 */
                SchM_Enter_Com_TX_MDT_PROTECTION_AREA();
                /* Reset minimum delay timer to zero */
                Com_GaaTxMDTimer[Com_GaaTxIpdu[LddTxIpduIndex].ddTxMDTimerIndex]
                                                       = (uint16)COM_ZERO;
                SchM_Exit_Com_TX_MDT_PROTECTION_AREA();
              }
              #endif
              #if(COM_TX_IPDU_REPETITION == STD_ON)
              /* Reset Repetition count*/
              if((Com_GaaTxIpdu[LddTxIpduIndex].ddTxReptIndex)
                != COM_INVALID_TXID_PARAM)
              {
                /* @Trace: Com_SUD_API_00402 */
                Com_GaaTxReptCount[
                  Com_GaaTxIpdu[LddTxIpduIndex].ddTxReptIndex] = COM_ZERO;
                Com_GaaTxReptSubCount[
                  Com_GaaTxIpdu[LddTxIpduIndex].ddTxReptIndex] = COM_ZERO;
              }
              #endif
              /* @Trace: Com_SUD_API_01423 */
              #if(COM_SIG_ERR_CBK_NOTIFY == STD_ON)
              Com_TxUpdateDmTimers_DmErrNotif(LddNoOfTxIpduDm);
              #endif /*#if(COM_SIG_ERR_CBK_NOTIFY == STD_ON)*/
              #if(COM_TX_CANCEL_SUPPORT == STD_ON)
              /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of blCancelTxFlag is generated by generator and has checked manual and it is not having any impact" */
              if(COM_TRUE == Com_GaaTxIpduDm[LddNoOfTxIpduDm].blCancelTxFlag)
              {
                /* @Trace: Com_SUD_API_00409 */
                (void) PduR_ComCancelTransmit(LpTxIpdu->ddTxIpduId);
                #if(COM_TX_TP_SUPPORT == STD_ON)
                if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
                {
                  /* @Trace: Com_SUD_API_00410 */
                  LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
                  if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] &
                    (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
                  {
                    /* @Trace: Com_SUD_API_00411 */
                    SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
                    /* Unlock the buffer */
                    Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] &=
                                      (uint8)(~(LpTxTPIpdu->ucTxTPStatusMask));
                    SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
                  }
                }
                #endif
              }
              #endif
            } /* Check whether deadline monitoring timer value is equal to zero */
            /* @Trace: Com_SUD_API_00412 */
            Com_GaaTxDMTimer[LddNoOfTxIpduDm] = LusTimer;
          }
        }
      }
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_TxSigConfirmation                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function generates transmit confirmation       **
**                        notification per signal for the "deferred" Tx I-PDUs**
**                        of the Tx I-PDU group.                              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpTxIpdu                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaTxIpduConfirm      **
**                                                  Com_GaaSigNotifCbk        **
**                        Function(s) invoked    :  pSigNotifCbk              **
*******************************************************************************/

#if(COM_TX_SIGNAL_NOTIFY == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigConfirmation(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_00413 */
  /* Pointer to Tx confirmation structure */
  P2CONST(Com_TxIpduConfirm, AUTOMATIC, COM_CONST) LpTxIpduConfirm;
  /* Pointer to notification call-back structure */
  P2CONST(Com_SigNotifCbk, AUTOMATIC, COM_CONST) LpSigNotifCbk;
  /* Local variable to store notification error call-back */
  uint8 LucNoOfSigCallback;
  Com_NotifCountType LddSigNotifCbkIndex;
   
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreIdMask;
  uint8 CoreIdCheck;
  uint8 CoreMaskCheck;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */ 
  /* Get the pointer to confirmation structure */
  LpTxIpduConfirm = &Com_GaaTxIpduConfirm[LpTxIpdu->ddTxPduConfirmIndex];
  /* Get the number of call-back functions */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  LucNoOfSigCallback =  LpTxIpduConfirm->ucNoOfSigCallback;
  /* Get the pointer to signal notification call-back structure */
  LddSigNotifCbkIndex = LpTxIpduConfirm->ddSigNotifCbkIndex;
  LpSigNotifCbk = &Com_GaaSigNotifCbk[LddSigNotifCbkIndex];
  /* Loop for number of signals configured for call-back */
  while(LucNoOfSigCallback != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00414 */
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    CoreMaskCheck = Com_GaaSigNotifCbkPositionMask[LddSigNotifCbkIndex];
    if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
    {
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    /* @Trace: Com_SUD_API_00415 */
    /* Invoke signal notification call-back function */
    (LpSigNotifCbk->pSigNotifCbk)();		
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)	
    }
    else
    {
      /* @Trace: Com_SUD_API_00416 */
      SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
      Com_GaaSigNotifCbkFlag[LddSigNotifCbkIndex] = CoreMaskCheck;  
      SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      /* Get ptr of notify function */
      CoreIdCheck = CoreMaskCheck >> COM_ONE;
      /* Trigger Ioc write */
      (void)Com_GaaMulticoreNotifyList[CoreIdCheck](COM_TRUE);
	}    
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    /* @Trace: Com_SUD_API_00417 */
    /* Decrement the number of signal call-back count */
    LucNoOfSigCallback--;
    /* Get pointer to n signal notification call-back structure */
    LddSigNotifCbkIndex++;
    LpSigNotifCbk = &Com_GaaSigNotifCbk[LddSigNotifCbkIndex];
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxClearUpdateBit                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function clears update bit for all signals     **
**                        configured for a particular I-PDU.                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant for same Tx I-PDU.                    **
**                        Reentrant for different Tx I-PDUs.                  **
**                                                                            **
** Input Parameters     : LpTxIpdu, LpSourcePtr                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxUpdateBit         **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if((COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxClearUpdateBit(
                  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
                  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSourcePtr)
{
  /* @Trace: Com_SUD_API_00418 */
  /* Pointer to Tx confirmation structure */
  P2CONST(Com_TxUpdateBit, AUTOMATIC, COM_CONST) LpTxUpdateBit;
  /* Pointer to Tx confirmation structure */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpUBitsTxIpduMask;
  /* Local variable to store no. of byte */
  uint16 LusNoOfByte;
  uint16 LusBufferIndex;
  uint16 LusUBitsTxIpduMaskIndex;

  LusBufferIndex = (uint16)COM_ZERO;
  /* Get the pointer to Tx Update bit Structure */
  LpTxUpdateBit = &Com_GaaTxUpdateBit[LpTxIpdu->ddTxIpduUbIndex];
  /* Get the pointer to I-PDU SduDataPtr */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  LusBufferIndex = LusBufferIndex + (LpTxUpdateBit->ucStartPosition);
  LusNoOfByte = LpTxUpdateBit->ucEndPosition;
  LpUBitsTxIpduMask = LpTxUpdateBit->pUbitsTxIpduMask;
  LusUBitsTxIpduMaskIndex = (uint16)COM_ZERO; 

  /* Enter protection area */
  SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
  /* Loop for number of bytes of data in I-PDU */
  do
  {
    /* @Trace: Com_SUD_API_00419 */
    /* Reset update bits in I-PDU by applying mask */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    (LpSourcePtr[LusBufferIndex]) &= 
      (LpUBitsTxIpduMask[LusUBitsTxIpduMaskIndex]);
    /* Increase the index of buffer */
    LusBufferIndex++;
    LusUBitsTxIpduMaskIndex++;
    /* Decrement the number of bytes in I-PDU count */
    LusNoOfByte--;
  }while(LusNoOfByte != (uint16)COM_ZERO);
  /* @Trace: Com_SUD_API_00420 */
  /* Exit protection area */
  SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_RxSigProcessing                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function process all signals configured for    **
**                        particular I-PDU.                                   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant for same Rx I-PDU.                    **
**                        Reentrant for different Rx I-PDUs.                  **
**                                                                            **
** Input Parameters     : LpRxIpdu                                            **
**                                                                            **
** InOut parameter      : LddLength                                           **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxTPIpdu            **
**                                                 Com_GaaRxSignal            **
**                                                 Com_GaaRxDMTimer           **
**                                                 Com_GaaRxUnpack            **
**                                                 Com_GaaRxInvalid           **
**                                                 Com_GaaInvalidFuncPtr      **
**                                                 Com_GaaInvNotifCbk         **
**                                                 Com_GaaWrFuncPtr           **
**                                                 Com_GaaSigNotifCbk         **
**                                                 Com_GaaRxDynSigLength      **
**                                                 Com_GaaInvRangeSigList     **
**                                                 Com_GucInvRangeSigListIndex**
**                                                 Com_GblIsInvRangeSigPdu    **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 pRdFuncPtr                 **
**                                                 pInvalidFuncPtr            **
**                                                 pFilterFuncPtr             **
**                                                 pWrFuncPtr                 **
**                                                 pSigNotifCbk               **
*******************************************************************************/
#if (COM_RX_SIGNAL == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if (COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxSigProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength,
                P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo)
#else
FUNC(void, COM_CODE) Com_RxSigProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength)
#endif
{
  /* @Trace: Com_SUD_API_00421 */
  /* Pointer to Rx Signal structure */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal;
  #if(COM_RX_DYN_SUPPORT == STD_ON)
  /* Pointer to Rx TP structure */
  PduLengthType LddDynSigLength;
  #endif
  #if ((COM_RX_SIGNAL_FILTER == STD_ON) || (COM_RX_SIGNAL_INVALID == STD_ON) \
                                    ||  (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
  /* Pointer to Rx unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  #endif
  #if ((COM_RX_SIGNAL_FILTER == STD_ON) || (COM_RX_SIGNAL_INVALID == STD_ON)\
                                      ||(COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
  PduLengthType LddSignalMemSize;
  #endif
  #if ((COM_RX_SIGNAL_UB == STD_ON) || (COM_RX_SIGNAL_UBDM == STD_ON) || \
       (COM_RX_SIGNAL_FILTER == STD_ON) || (COM_RX_SIGNAL_INVALID == STD_ON)\
                                      ||(COM_RX_SIGNAL_UBDMREPLACE == STD_ON)\
                                            ||(COM_RX_SIGNAL_NOTIFY == STD_ON))
  /* Local variable to store signal configuration */
  uint8 LucSigConfig;
  #endif
  #if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform;
  #endif
  uint16 LusNoOfSignal;
  Com_SignalIdType LddRxSignalIndex;

  /* #1504 : Update Dynamic signal length before invoking callback function */
  #if(COM_RX_DYN_SUPPORT == STD_ON)
  /* #2142 : separate DYN PDU from TP */
  if(COM_DYN_IPDU == LpRxIpdu->ucIpduType)
  {
    /* @Trace: Com_SUD_API_00422 */
    LddDynSigLength = (PduLengthType)(LddLength - LpRxIpdu->ddRxNonDynLength);
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    Com_GaaRxDynSigLength[LpRxIpdu->ddRxIpduDynLegthRef] = LddDynSigLength;
  }
  #endif
  
  /* @Trace: Com_SUD_API_00423 */
  /* Get the number of  Rx signals */
  LusNoOfSignal = LpRxIpdu->usNoOfRxSignal;
  /* Get the pointer to  Rx signal structure */
  LddRxSignalIndex = LpRxIpdu->ddRxSigIndex;
  LpRxSignal = &Com_GaaRxSignal[LddRxSignalIndex]; 
  #if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
  LpIdsMInform = LpIdsMInfo;
  #endif
  
  /* Loop for number of  Rx signals */
  do
  {
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    if(LddLength >= LpRxSignal->ddSignalEndByte)
    {
      #if ((COM_RX_SIGNAL_UB == STD_ON) || \
      (COM_RX_SIGNAL_UBDM == STD_ON) || \
        (COM_RX_SIGNAL_FILTER == STD_ON) || \
        (COM_RX_SIGNAL_INVALID == STD_ON) || \
        (COM_RX_SIGNAL_UBDMREPLACE == STD_ON) || \
        (COM_RX_SIGNAL_NOTIFY == STD_ON))
      /* @Trace: Com_SUD_API_00424 */  
      /* Get the signal configuration */
      LucSigConfig = LpRxSignal->ucRxSigConfig;
      #endif                          
      /* Each bit represent signal configuration in an I-PDU
        0x01 : Notification
        0x02 : IdsM
        0x04 : Update bit
        0x08 : Update bit deadline monitoring
        0x10 : Update bit deadline monitoring with timeout replacement
        0x20 : Filtering
        0x40 : Invalidation
        0x80 : Invalidation replacement with init value */
      #if (COM_RX_SIGNAL_UB == STD_ON)
      /* Check whether update bit is configured */
      if((LucSigConfig & COM_RX_SIGNAL_UB_CONFIG_MASK) != COM_FALSE)
      {
        /* Check whether signal is received with an update bit */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        if(COM_FALSE == (*(LpRxSignal->pUBit) & (LpRxSignal->ucUbitMask)))
        {
          /* @Trace: Com_SUD_API_00425 */
          /* return if update bit is not set */
          LucSigConfig = COM_ZERO;
        }
        #if (COM_RX_SIGNAL_UBDM == STD_ON)
        /* Check whether signal has been configured for deadline monitoring */
        else if((LucSigConfig & COM_RX_SIGNAL_UBDM_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_00426 */
          #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Enter_Com_RX_DM_STS_PROTECTION_AREA();
          #endif
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          Com_GaaRxDMTimer[LpRxSignal->ucRxUbDmIndex] = COM_INVALID_DM_TIMER;
          #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Exit_Com_RX_DM_STS_PROTECTION_AREA();
          #endif
        }
        else
        {
          /* Dummy loop to avoid QAC warning */
        }
        #endif
      }
      if(LucSigConfig != COM_ZERO)
      #endif
      {
        /* #7803 */
        #if ((COM_RX_SIGNAL_FILTER == STD_ON) ||\
          (COM_RX_SIGNAL_INVALID == STD_ON) ||\
          (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
        /* Check whether signal is configured for invalidation/filtering/UB
        deadline monitoring with timeout replacement */
        if(LucSigConfig >= COM_RX_SIGNAL_UBDMREPLACE_CONFIG_MASK)
        {
          /* @Trace: Com_SUD_API_00427 */
          /* Get the pointer to Rx unpack structure */
          LpRxUnpack = &Com_GaaRxUnpack[LpRxSignal->ddRxUnpackIndex];

          if(LpRxUnpack->ucSignalType < COM_FOUR)
          {
            /* @Trace: Com_SUD_API_00428 */
            LddSignalMemSize = (PduLengthType)Com_GaaSigMemSize[LpRxUnpack->ucSignalType];
          }
          else
          {
            /* @Trace: Com_SUD_API_00429 */
            LddSignalMemSize = LpRxUnpack->ddSignalSize;
          }          

          #if (COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
          /* @Trace: Com_SUD_API_01424 */
          Com_RxSigProc_SingleRxSigProc(LpRxIpdu, LddSignalMemSize, 
            LpIdsMInform, &LucSigConfig,
            LddRxSignalIndex);
          #else
          /* @Trace: Com_SUD_API_01425 */
          Com_RxSigProc_SingleRxSigProc(LpRxIpdu, LddSignalMemSize, 
            &LucSigConfig, LddRxSignalIndex);
          #endif
        }
        #endif/*#if ((COM_RX_SIGNAL_FILTER == STD_ON) ||
                          (COM_RX_SIGNAL_INVALID == STD_ON))*/
        /* @Trace: Com_SUD_API_01426 */
        #if (COM_RX_SIGNAL_NOTIFY == STD_ON)
        Com_RxSigProc_RxSigNotif(LpRxSignal, LucSigConfig);
        #endif
      } /* if(LddLength > LpRxSignal->ucEndPosition) */
    }
    /* @Trace: Com_SUD_API_00464 */
    /* Decrement the count of number of signals */
    LusNoOfSignal--;
    /* Get the pointer to n  Rx signal structure */
    LddRxSignalIndex++;
    LpRxSignal = &Com_GaaRxSignal[LddRxSignalIndex];  
  }while(LusNoOfSignal != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_RxSigGrpProcessing                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function process all Rx signal groups          **
**                        configured for the I-PDU.                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant for same Rx I-PDU.                    **
**                        Reentrant for different Rx I-PDUs.                  **
**                                                                            **
** Input Parameters     : LpRxIpdu                                            **
**                                                                            **
** InOut parameter      : LddLength                                           **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxSigGroup          **
**                                                 Com_GaaRxDMTimer           **
**                                                 Com_GaaRxInvOrFltSigGroup  **
**                                                 Com_GaaRxSigInGrp          **
**                                                 Com_GaaRxSigInGrpInvOrFlt  **
**                                                 Com_GaaRxUnpack            **
**                                                 Com_GaaInvalidFuncPtr      **
**                                                 Com_GaaInvNotifCbk         **
**                                                 Com_GaaSigNotifCbk         **
**                                                 Com_GaaInvRangeSigList     **
**                                                 Com_GucInvRangeSigListIndex**
**                                                 Com_GblIsInvRangeSigPdu    **
**                        Function(s) invoked    : SchM_Enter_Com()           **
**                                                 SchM_Exit_Com()            **
**                                                 pRdFuncPtr                 **
**                                                 pInvalidFuncPtr            **
**                                                 pWrFuncPtr                 **
**                                                 pSigNotifCbk               **
*******************************************************************************/
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
FUNC( void, COM_CODE) Com_RxSigGrpProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength,
                P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo)

#else
FUNC( void, COM_CODE) Com_RxSigGrpProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength)
#endif
{
  /* @Trace: Com_SUD_API_00465 */
  #if((COM_RX_SIGGROUP_FILTER == STD_ON) || \
    (COM_RX_SIGGROUP_INVALID == STD_ON))
  #if (COM_RX_TP_SUPPORT == STD_ON)
  PduIdType LucRxPduId;
  #endif
  #endif
  /* Pointer to Rx Signal Group structure */
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup;
  #if(COM_RX_SIGGROUP_INVALID == STD_ON)
  /* Pointer to Rx Invalid or Filter Signal Group structure */
  P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST) LpRxInvOrFltSigGrp;
  /* Pointer to Rx Signal InGroup structure */
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) LpRxSigInGrp;
  /* Local variable to store no of signal or size */
  uint16 LusNoOfSigOrSize;
  /* Local variable to store Rx Signal InGroup index */
  Com_SignalIdType LddRxSigInGrpIndex;
  #endif
  #if((COM_RX_SIGGROUP_INVALID == STD_ON) || (COM_RX_SIGGROUP_FILTER == STD_ON))
  /* Pointer to Signal Data structure */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData = NULL_PTR;
  #endif
  /* Local variable to store signal group */
  uint8 LucNoOfSigGroup;
  #if((COM_RX_SIGGROUP_UB == STD_ON) || \
      (COM_RX_SIGGROUP_INVALID == STD_ON) || \
      (COM_RX_SIGGROUP_NOTIFY == STD_ON)  || \
      (COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON) || \
      (COM_RX_SIGGROUP_FILTER == STD_ON))
  /* Local variable to store signal group configuration */
  uint8 LucSigGroupConfig;
  #endif
  #if(COM_RX_SIGGROUP_INVALID == STD_ON)
  /* Local variable to store Invalid flag */
  boolean LblInvalidFlag = COM_FALSE;
  #endif
  #if(COM_RX_SIGGROUP_FILTER == STD_ON)
  /* Local variable to store Filter Out flag */
  boolean LblFltOutFlag = COM_FALSE;
  #endif
  #if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform;
  #endif
  Com_SignalGroupIdType LddRxSigGroupIndex;
  /* Get the number of  Rx signal groups */
  LucNoOfSigGroup = LpRxIpdu->ucNoOfRxSigGroup;
  /* Get the pointer to  Rx signal group structure */
  LddRxSigGroupIndex = LpRxIpdu->ddRxSigGrpIndex;
  LpRxSigGroup = &Com_GaaRxSigGroup[LddRxSigGroupIndex];
  #if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
  LpIdsMInform = LpIdsMInfo;
  #endif
  /* Loop for number of  Rx signal groups */
  do
  {
    /* Check length of received Ipdu is part of signal configuration */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is inside its bound. This is assured by generator" */
    if(LddLength >= LpRxSigGroup->ddSignalEndByte)
    {
      /* @Trace: Com_SUD_API_00466 */
      #if((COM_RX_SIGGROUP_UB == STD_ON) || \
          (COM_RX_SIGGROUP_INVALID == STD_ON) || \
          (COM_RX_SIGGROUP_NOTIFY == STD_ON)  || \
          (COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON) || \
          (COM_RX_SIGGROUP_FILTER == STD_ON))
      /* Get the signal group configuration */
      LucSigGroupConfig = LpRxSigGroup->ucSigGroupConfig;
      #endif

      #if(COM_RX_SIGGROUP_UB == STD_ON)
      /* Signal group configuration:
         0x01: Notification
         0x02: Update bit
         0x04: Update bit with timeout
         0x08: Invalid configuration
         0x10: Replace the value (Invalid replacement )
         0x20: Replace the value (Timeout/Invalid Replacement)
     0x40: Filtering */
      /* Check whether update bit is configured */
      if((LucSigGroupConfig & COM_RX_SIGGRP_UB_CONFIG_MASK) != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_01427 */
        Com_RxGrpProc_UpdrBitProc(LpRxSigGroup, &LucSigGroupConfig);
      }
      #endif
      
      /* Redmine #13931: Support Rx Group Signal Filtering. */
      #if((COM_RX_SIGGROUP_INVALID == STD_ON) ||\
        (COM_RX_SIGGROUP_FILTER == STD_ON))
      /* Check whether signal group is configured for invalidation */
      /* Redmine #13931: Also check whether filtering is configured */
      if(((LucSigGroupConfig & COM_RX_SIGGRP_INVALID_CONFIG_MASK)
        |(LucSigGroupConfig & COM_RX_SIGGRP_FILTER_CONFIG_MASK)) != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00469 */
        #if(COM_RX_SIGGROUP_INVALID == STD_ON)
        /* Set InvalidFlag of this signal group to 'COM_FALSE' */
        LblInvalidFlag = COM_FALSE;
        #endif
    
        #if(COM_RX_SIGGROUP_FILTER == STD_ON)
        /* Set FltOutFlag of this signal group to 'COM_FALSE' */
        LblFltOutFlag = COM_FALSE;
        #endif
    
        if(COM_FALSE 
          == (LpRxIpdu->ucRxConfig & COM_RX_IPDU_DEFERRED_CONFIG_MASK))
        {    
          /* @Trace: Com_SUD_API_00470 */        
          #if(COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON) 
          LpSignalData = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                                    &Com_GaaSignalValidCKBufferIM[COM_ZERO];
          #endif
        }
        else
        {
          /* @Trace: Com_SUD_API_00471 */
          #if(COM_RX_IPDU_DEFERRED == STD_ON)
          LpSignalData = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                                    &Com_GaaSignalValidCKBufferDE[COM_ZERO];
          #endif
        }
      }
      /* Req 839, 838*/
      /* @Trace: Com_SUD_API_00472 */
      #if(COM_RX_TP_SUPPORT == STD_ON)
      LucRxPduId = LpRxSigGroup->ddRxpduId;
      if(Com_GaaRxTPflg[LucRxPduId] != COM_ZERO)
      {
        /*Com_GaaRxTPflg[LucRxPduId] = COM_ZERO;*/
        #if(COM_RX_SIGGROUP_INVALID == STD_ON)
        /*********************** Start Invalidation ************************/
        if((LucSigGroupConfig & COM_RX_SIGGRP_INVALID_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_01428 */
          Com_RxGrpProc_SigGrpInv(LpRxSigGroup, &LucSigGroupConfig);
        }/* End of if((LucSigGroupConfig & COM_RX_SIGGRP_INVALID_CONFIG_MASK) != COM_FALSE) */
        #endif /* End of #if(COM_RX_SIGGROUP_INVALID == STD_ON) */
        /*********************** End of Invalidation **************************/
      }
      else   
      #endif /* #if(COM_RX_TP_SUPPORT == STD_ON)*/
      {
        #if(COM_RX_SIGGROUP_INVALID == STD_ON)
        /*********************** Start Invalidation ************************/
        if((LucSigGroupConfig & COM_RX_SIGGRP_INVALID_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_00481 */
          /* Get below structure to fetch the number of group signals, 
          and the position of the first group signal, Notification Index and Init value */    
          LpRxInvOrFltSigGrp = 
           &(Com_GaaRxInvOrFltSigGroup[LpRxSigGroup->usInvOrFltIndex]);
        
          /* Get the number of Rx Group Signals and the position of the first one 
            for this signal group */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
          LusNoOfSigOrSize = LpRxInvOrFltSigGrp->usNoOfSignal;
          LddRxSigInGrpIndex = LpRxInvOrFltSigGrp->ddRxSigInGrpIndex;
            
          /* Get the first Rx group signal of this signal group */
          LpRxSigInGrp = &(Com_GaaRxSigInGrp[LddRxSigInGrpIndex]);
      
          /* Loop all of the rx group signal of this Signal Group until invalid one is not detected. */
          do
          {
            /* #7803 */
            /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
            if(LpRxSigInGrp->usSigInGrpInvOrFltIndex != COM_INVALID_NONE)
            {
              /* @Trace: Com_SUD_API_01429 */
              Com_RxGrpProc_SglInGrpProc(LpRxIpdu, LpRxSigInGrp, LpSignalData, 
                &LblInvalidFlag);
            } /* End of if(LpRxSigInGrp->usSigInGrpInvOrFltIndex != COM_INVALID_NONE) */
            /* @Trace: Com_SUD_API_00494 */
            /* Decrement the count of number of Rx Group Signals to be iterated */
            LusNoOfSigOrSize--;
            /* Increment the Index of Rx Group Signal by one and get the next one. */
            LddRxSigInGrpIndex++;
            LpRxSigInGrp = &(Com_GaaRxSigInGrp[LddRxSigInGrpIndex]);
          }while((LusNoOfSigOrSize != COM_ZERO) && (LblInvalidFlag !=COM_TRUE));
            
          /* Check whether Invalid Rx Group Signal had been detected for this Signal Group. */
          if(COM_TRUE == LblInvalidFlag)
          {
            /* @Trace: Com_SUD_API_01430 */
            Com_RxGrpProc_SglGrpProc(&LucSigGroupConfig, LpRxInvOrFltSigGrp, 
              LpRxSigGroup);
          } /* End of if(COM_TRUE == LblInvalidFlag) */
        }/* End of if((LucSigGroupConfig & COM_RX_SIGGRP_INVALID_CONFIG_MASK) != COM_FALSE) */
        #endif /* End of #if(COM_RX_SIGGROUP_INVALID == STD_ON) */
        /*********************** End of Invalidation **************************/
      
        /*********************** Redmine #13931: Start of Filtering ***************************/
        #if(COM_RX_SIGGROUP_FILTER == STD_ON)
        if((LucSigGroupConfig & COM_RX_SIGGRP_FILTER_CONFIG_MASK) != COM_ZERO)
        {
          #if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
          /* @Trace: Com_SUD_API_01432 */
          Com_RxGrpProc_SigGrpFltr(LpRxIpdu, LpRxSigGroup, LpSignalData, 
            &LucSigGroupConfig, &LblFltOutFlag, LpIdsMInform);
          #else
          /* @Trace: Com_SUD_API_01433 */
          Com_RxGrpProc_SigGrpFltr(LpRxIpdu, LpRxSigGroup, LpSignalData, 
            &LucSigGroupConfig, &LblFltOutFlag);
          #endif
        } /* End of if((LucSigGroupConfig & COM_RX_SIGGRP_FILTER_CONFIG_MASK) != COM_ZERO) */
        #endif /* End of #if (COM_RX_SIGGROUP_FILTER == STD_ON) */
        /************************* End of Filtering ***************************/
      } /* else for tp data*/
      #endif /* End of #if((COM_RX_SIGGROUP_INVALID == STD_ON) || (COM_RX_SIGGROUP_FILTER == STD_ON)) */
      /* @Trace: Com_SUD_API_01434 */
      #if((COM_RX_SIGGROUP_UB == STD_ON) || \
           (COM_RX_SIGGROUP_INVALID == STD_ON) || \
           (COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON) || \
           (COM_RX_SIGGROUP_FILTER == STD_ON))
      Com_RxGrpProc_RxGrpBuffUpdr(LucSigGroupConfig, LpRxSigGroup);
      #endif

      #if(COM_RX_SIGGROUP_NOTIFY == STD_ON)
      /* Check whether signal group is configured for notification */
      Com_RxGrpProc_RxGrpNotif(LucSigGroupConfig, LpRxSigGroup);
      #endif
    }
    /* @Trace: Com_SUD_API_00523 */
    /* Decrement the count of number of  signal groups */
    LucNoOfSigGroup--;
    /* Get the pointer to n  Rx signal group structure */
    LddRxSigGroupIndex++;
    LpRxSigGroup = &Com_GaaRxSigGroup[LddRxSigGroupIndex];
  }while(LucNoOfSigGroup != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_RxGWSigProcessing                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes all signals in the I-PDU    **
**                        that are configured for gateway, based on the signal**
**                        transfer property.                                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpRxGWIpdu                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxGWSignal          **
**                                                 Com_GaaRxUnpack            **
**                        Function(s) invoked    : pRdFuncPtr                 **
**                                                 Com_SendSignal()           **
*******************************************************************************/
#if((COM_RX_SIGNAL_GW == STD_ON) ||\
 (COM_RX_SIGINGROUP_GW == STD_ON) ||\
 (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_ES91821_06E_SWP_00014, SRS_ES91821_06E_SWP_00043 */
/* @Trace: SRS_ES91821_06E_SWP_00047, SRS_ES91821_06E_SWP_00116 */
/* @Trace: SRS_ES91821_06E_SWP_00130, SRS_ES91821_06E_SWP_00131 */
FUNC(void, COM_CODE) Com_RxGWSigProcessing
           (P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST) LpRxGWIpdu, 
           uint8 lucGWStatus)
{
  /* @Trace: Com_SUD_API_00524 */
  /* Pointer to Gate Way Rx Signal structure */
  P2CONST(Com_RxGWSignal, AUTOMATIC, COM_CONST) LpGWRxSignal;

  /* Pointer to Rx Unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  /* Local variable to store Tx signal ID */
  Com_SignalIdType LddTxSignalId;
  /* Local variable to store no. of Gateway signal  */
  uint8 LucNoOfGWSignal;
  /* Local variable to store no. of route signal */
  uint8 LucNoOfRouteSignal;
  
  PduLengthType LddSignalMemSize;
  /* Local variable to store the tx index */
  Com_SignalIdType LddRouteTxIndex;

  Com_SignalIdType LddRxGWSignalIndex;

  #if(COM_TX_GW_CALLOUT_SUPPORT == STD_ON)
  boolean LblSigCalloutResult;
  /* buffer Loop Index */  
  PduLengthType LddBufferIndex;
  #endif
  
  /* Local variable to store return value */
  #if((COM_RX_SIGNAL_UB == STD_ON) && (COM_RX_SIGNAL_GW_UB == STD_ON))
  /* Local variable to store process flag */
  boolean LblProcessFlag;
  #endif
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  uint8 LucReturnValue;
  
  PduIdType LddTxPduId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

  #if(COM_TX_SIG_INGRP_GW_MAX > COM_MACRO_ZERO)
  uint16 LucNoOfTxSignal;
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01339 */
  LucNoOfTxSignal = (uint16)COM_TX_SIGNAL_COUNT;
  #else
  /* @Trace: Com_SUD_API_01340 */
  LucNoOfTxSignal = (uint16)COM_TX_SIGNAL_COUNT_MAX;
  #endif
  #endif
  /* @Trace: Com_SUD_API_01341 */
  /* Get the number of Rx gateway signals */
  LucNoOfGWSignal = LpRxGWIpdu->ucNoOfRxGWSignal;
  /* Get the pointer to  Rx gateway signal structure */
  LddRxGWSignalIndex = LpRxGWIpdu->ddGWRxSigIndex;

  /* Loop for all  Rx signals that are configured for gateway */
  /* Because this function is invoke, when Signal number is over one.
  So, LucNoOfGWSignal variable is always over one. 
  And, it's fine to use "do-while" operation */
  do
  {
    /* @Trace: Com_SUD_API_00525 */
    /* Get the pointer to n  Rx gateway signal structure */
    LpGWRxSignal = &Com_GaaRxGWSignal[LddRxGWSignalIndex];
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    if((lucGWStatus == COM_SIG_GW_STATUS_TOUT) && 
      (LpGWRxSignal->blDMTrigger == COM_FALSE))
    {
      /* Do nothing */
    }
    else
    {
      /* @Trace: Com_SUD_API_00526 */
      #if((COM_RX_SIGNAL_UB == STD_ON) && (COM_RX_SIGNAL_GW_UB == STD_ON))
      Com_RxGWSigProcessing_UBCheck(LpRxGWIpdu, &LblProcessFlag);
      /* Check whether process flag is true */
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of LblProcessFlag is checked manual and it is not having any impact" */
      if(COM_TRUE == LblProcessFlag)
      #endif
      {
        /* @Trace: Com_SUD_API_00528 */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        LpRxUnpack = &(Com_GaaRxUnpack[LpGWRxSignal->ddRxUnpackIndex]);
        
        Com_RxGWSigProcessing_SigGWBuff(LpRxUnpack, &LddSignalMemSize);
        
        /* @Trace: Com_SUD_API_00534 */
        /* Invoke read function to unpack the signal from an I-PDU */
        /* @Trace: SWS_Com_00352 */
        #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
        (void)Com_UnPackRequestRead(LpRxUnpack, 
          (P2VAR(void, AUTOMATIC, COM_VAR)) &Com_GaaSignalGWBuffer[COM_ZERO]);
        #endif
        /* Get the number of signals to be routed */
        LucNoOfRouteSignal = LpGWRxSignal->ucNoOfRouteSignal;
        /* Get the index of Tx Signal handleID structure */
        LddRouteTxIndex = LpGWRxSignal->ddTxSigIndex;
      
        
        /* Loop for number of Tx signals to be routed */
        do
        {     
          /* @Trace: Com_SUD_API_00535 */   
          /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          LddTxSignalId = 
            (Com_SignalIdType)Com_GaaTxGWSignal[LddRouteTxIndex].ddGWTxSigIndex;
          #if (STD_ON == COM_MULTI_CORE_SUPPORT)
          /* Check core id of  Tx IPdu*/
          LddTxPduId = Com_GaaTxSignal[LddTxSignalId].ddTxIpduIndex;
          COM_TXPDUID_CHECK_COREID(LddTxPduId,LucReturnValue);
          /* only formward TxPdu that is configurated in this core*/
		      if(LucReturnValue == (uint8)E_OK)
          #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */ 
          {
            /* @Trace: Com_SUD_API_00536 */
            /* @Trace: Com_SUD_API_00537 */
            #if(COM_TX_GW_CALLOUT_SUPPORT == STD_ON)
            for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
                                            LddSignalMemSize; LddBufferIndex++) 
            {
              /* @Trace: Com_SUD_API_00538 */
              Com_GaaSignalGWBufferSub[LddBufferIndex] = 
              Com_GaaSignalGWBuffer[LddBufferIndex];
            }  
            /* @Trace: Com_SUD_API_00539 */              
            LblSigCalloutResult = COM_TRUE;
            if(Com_GaaTxGWSignal[LddRouteTxIndex].ucGWCalloutAction != 
                                                  COM_SIG_GW_CALLOUT_ACT_NONE)
            {
              if(!((COM_SIG_GW_STATUS_NORMAL == lucGWStatus) && 
              (Com_GaaTxGWSignal[LddRouteTxIndex].ucGWCalloutAction == 
              COM_SIG_GW_CALLOUT_ACT_TOUTONLY)))
              {
                if(Com_GaaTxGWSignal[LddRouteTxIndex].ddGWCalloutFunctionPtr != 
                NULL_PTR)
                {
                  /* @Trace: Com_SUD_API_00540 */
                  /* polyspace:begin<RTE : COR : Not a defect : Justify with annotations> Configured function pointer */            
                  LblSigCalloutResult = 
                  (Com_GaaTxGWSignal[LddRouteTxIndex].ddGWCalloutFunctionPtr)
                  (&Com_GaaSignalGWBufferSub[COM_ZERO], lucGWStatus);
                  /* polyspace:end<RTE : COR : Not a defect : Justify with annotations> Configured function pointer */
                }
                else
                {
                  /* @Trace: Com_SUD_API_00541 */
                  LblSigCalloutResult = COM_FALSE;
                }
              }
            }
            else
            #endif
            {
              /* in case of callout function is not configured. */
            }

            #if(COM_TX_GW_CALLOUT_SUPPORT == STD_ON)
            if(LblSigCalloutResult == COM_TRUE)
            #endif
            {
              #if(COM_RX_SIGNAL_GW_DES == STD_ON)
              if(LddTxSignalId > COM_TX_SIGNAL_SIGINGRP_COUNT)
              {
                /* @Trace: Com_SUD_API_00542 */
                (void)Com_SendSignalService((LddTxSignalId- 
                  (COM_TX_SIGNAL_SIGINGRP_COUNT - COM_TX_SIG_GRPSIG_BOUNDARY)
                    - COM_ONE),&Com_GaaSignalGWBuffer[COM_ZERO]);
              }
              else
              #endif
              {
                #if(COM_TX_SIG_INGRP_GW_MAX > COM_MACRO_ZERO)
                /* Polyspace Useless if [A defect:Low] this is a base code, Com_GaaTxGWSignal and "COM_TX_SIGNAL_COUNT" are
                    verified and generated by Generator Tool */
                if(LddTxSignalId >= LucNoOfTxSignal)
                {
                  #if(COM_TX_SIGGROUP == STD_ON)
                  /* Invoke Com_UpdateShadowSignalService() function to update the data into
                  shadow buffer with signal data */
                  #if(COM_TX_GW_CALLOUT_SUPPORT == STD_ON)
                  /* @Trace: Com_SUD_API_00543 */
                  Com_UpdateShadowSignalService(
                    LddTxSignalId - COM_TX_SIG_GRPSIG_BOUNDARY, 
                    (P2VAR(void, AUTOMATIC, COM_VAR))
                      &Com_GaaSignalGWBufferSub[COM_ZERO]);
                  (void)Com_SendSignalGroup
                  (Com_GaaTxSigInGrp[LddTxSignalId-LucNoOfTxSignal]
                  .ddSigGrpIndex);
                  #else
                  /* @Trace: Com_SUD_API_01342 */
                  Com_UpdateShadowSignalService(
                    LddTxSignalId - COM_TX_SIG_GRPSIG_BOUNDARY, 
                    (P2VAR(void, AUTOMATIC, COM_VAR))
                      &Com_GaaSignalGWBuffer[COM_ZERO]);
                  (void)Com_SendSignalGroup
                  (Com_GaaTxSigInGrp[LddTxSignalId-LucNoOfTxSignal]
                  .ddSigGrpIndex);
                  #endif
                  #endif
                }
                else
                #endif
                {
                  #if(COM_TX_GW_CALLOUT_SUPPORT == STD_ON)
                  /* @Trace: Com_SUD_API_00544 */
                  (void)Com_SendSignal(LddTxSignalId, 
                  &Com_GaaSignalGWBufferSub[COM_ZERO]);
                  #else
                  /* @Trace: Com_SUD_API_01343 */
                  (void)Com_SendSignal(LddTxSignalId, 
                  &Com_GaaSignalGWBuffer[COM_ZERO]);
                  #endif
                }
              }
            }
          }
          /* @Trace: Com_SUD_API_00545 */
          /* Decrement the count of number of signals to be routed */
          LucNoOfRouteSignal--;

          /* Increase the index of routed tx signal */
          LddRouteTxIndex++;

        }while(LucNoOfRouteSignal != COM_ZERO);
      } /* Check whether process flag is true */
    }

    /* @Trace: Com_SUD_API_00546 */
    LddRxGWSignalIndex++;

    /* Decrement count of number of gateway signals */
    LucNoOfGWSignal--;
  }while(LucNoOfGWSignal != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SwitchIpduTxMode                                **
**                                                                            **
** Service ID           : 0x27                                                **
**                                                                            **
** Description          : The service Com_SwitchIpduTxMode sets the           **
**                        transmission mode of the I-PDU referenced by PduId  **
**                        to Mode. In case the transmission mode changes, the **
**                        new mode shall immediately be effective. In case the**
**                        requested transmission mode was already active for  **
**                        this I-PDU, the call will have no effect.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduId, Mode                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : It shall only be used from within I-PDU callout.    **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxIpdu              **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxMode              **
**                                                 Com_GaaTxReptCount         **
**                                                 Com_GaaTxMDTimer           **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 Com_Transmit()             **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02082*/
FUNC(void, COM_CODE) Com_SwitchIpduTxMode(PduIdType PduId,
  boolean txMode)
{
  /* @Trace: Com_SUD_API_00577 */
  /* Pointer to Tx mode structure */
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #endif
  /* Local variable to store Ipdu config */
  uint8 LucIpduConfig;
  /* Flag to check if transmission is needed or not */
  boolean LblTransmitFlag;
  /* Local status of the Ipdu */
  uint16 LusTxIpduStatusBit;
  LblTransmitFlag = COM_FALSE;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_SWITCHIPDUTXMODE);
  /* Check whether I-PDU group ID is out of range */
  COM_DET_TXPDUID_RANGE_CHECK_FLAG(PduId, COMSERVICEID_SWITCHIPDUTXMODE);
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_00578 */
    LpTxIpdu = &Com_GaaTxIpdu[PduId];
    /* Get the status in a local variable */
    LusTxIpduStatusBit = Com_GaaTxIpduStatusBit[PduId];
    /* Get a pointer to TRUE mode */
    LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
    /* Get the Ipdu configuration */
    LucIpduConfig = LpTxIpdu->ucTxConfig;
    /* If the Tx Ipdu has been started */
    if(Com_GaaTxIpduStatus[PduId] > COM_ZERO)
    {
      /* Check if the status are different */
      if((Com_GaaTxIpduStatusBit[PduId] & COM_TX_TMS_STATUS_MASK) != txMode)
      {
        /* @Trace: Com_SUD_API_01435 */
        #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
        Com_SwIpduTxMode_PendingStatus(LpTxIpdu, &LusTxIpduStatusBit);
        #endif
        /* If mode is False */
        if(COM_FALSE == txMode)
        {
          /* @Trace: Com_SUD_API_00580 */
          /* Set the status flag to indicate that TMS has evaluated to false */
          LusTxIpduStatusBit &= (uint16)(COM_TX_TMS_STATUS_CLEAR_MASK);
          /* Get the pointer to false Tx mode */
          LpTxMode = 
          &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
        }/* If mode is False */
        else
        {
          /* @Trace: Com_SUD_API_00581 */
          /* Set the status flag to indicate that TMS has evaluated to true */
          LusTxIpduStatusBit |= (uint16)(COM_TX_TMS_STATUS_MASK);
        }
        /* @Trace: Com_SUD_API_01436 */
        Com_SwIpduTxMode_ResetTimer(LucIpduConfig, LpTxIpdu, &LusTxIpduStatusBit, LpTxMode,
          &LblTransmitFlag);
        if(COM_TRUE == LblTransmitFlag)
        {
          /* @Trace: Com_SUD_API_00590 */
          LusTxIpduStatusBit |= COM_TX_MAINFUNC_SEND_STATUS_MASK;
          #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
          /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and has checked manual and it is not having any impact" */
          if(LpTxMode->ucDirectMainTransmit == COM_TX_DIRECT_TRANS)
          {
            /* @Trace: Com_SUD_API_00591 */
            (void)Com_Transmit((PduIdType)PduId);
          }
          #endif
        }
        /* @Trace: Com_SUD_API_00592 */
        SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        Com_GaaTxIpduStatusBit[PduId] = LusTxIpduStatusBit;
        SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      }/* Check if the status are different */
    }/* If the Tx Ipdu has been started */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_RxSigNotifyOrReplace                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LpRxDm                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaSigReplace          **
**                                                 Com_GaaInvNotifCbk         **
**                                                 Com_GaaSigErrorCbk         **
**                                                 Com_GaaTxPack              **
**                        Function(s) invoked    : pWrFuncPtr                 **
**                                                 pSigErrorCbk               **
*******************************************************************************/
#if((COM_RX_IPDU_DM == STD_ON) || \
   (COM_RX_SIGNAL_UBDM == STD_ON) || \
   (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxSigNotifyOrReplace(
                         P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm)
{
  /* @Trace: Com_SUD_API_00593 */
  #if(COM_SIG_ERR_CBK_NOTIFY == STD_ON)
  /* Pointer to notification error call-back structure */
  P2CONST(Com_SigErrorCbk, AUTOMATIC, COM_CONST) LpSigErrorCbk;
  Com_ErrCbkCountType LddSigErrorCbkIndex;
  #endif  
  #if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
     (COM_RX_SIGGROUP_REPLACE == STD_ON) || \
     (COM_RX_SIGNAL_UBDMREPLACE == STD_ON) || \
     (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON)||\
     (COM_RX_SIGNAL_SUBSTITUTE == STD_ON))
  /* #7744 start */
  /* Pointer to structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpPackTimeout;
  uint8 LucSigReplaceIndex;  
  #endif  
  #if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
     (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
  /* Pointer to signal replace structure */
  P2CONST(Com_SigReplace, AUTOMATIC, COM_CONST) LpSigReplace;       
  #endif

  #if((COM_RX_SIGGROUP_REPLACE == STD_ON) || \
     (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON))
  /* Pointer to signal group replace structure */
  P2CONST(Com_SigGrpReplace, AUTOMATIC, COM_CONST) LpSigGrpReplace;       
  /* Pointer to Rx Signal Group structure */
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup;  
  #endif
  
  #if(COM_RX_SIGNAL_SUBSTITUTE == STD_ON)
  /* Pointer to signal group substitute structure */
  P2CONST(Com_SigSub, AUTOMATIC, COM_CONST) LpSigSub;
  uint8 LucSigSubIndex;
  #endif

    /* Local variable to store signal count */
  #if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
       (COM_RX_SIGGROUP_REPLACE == STD_ON) || \
       (COM_RX_SIGNAL_UBDMREPLACE == STD_ON) || \
       (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON) || \
       (COM_SIG_ERR_CBK_NOTIFY == STD_ON))|| \
       (COM_RX_SIGNAL_SUBSTITUTE == STD_ON)
  uint8 LucNoOfSigCount;
  #endif  
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreIdMask;
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
     (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
  LucNoOfSigCount = LpRxDm->ucNoOfSigReplace;
  /* Check whether any replacement is configured */
  if(LucNoOfSigCount != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00594 */
    /* Get the pointer to LpSigReplace structure */
    LucSigReplaceIndex = LpRxDm->ucSigReplaceIndex;
    LpSigReplace = &Com_GaaSigReplace[LucSigReplaceIndex];
    do
    {
      /* @Trace: Com_SUD_API_00595 */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      LpPackTimeout = &Com_GaaTxPack[LpSigReplace->ddTxPackIndex];
      #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
      /* Invoke write function to pack the initial value into
         I-PDU/signal buffer */
      (void)Com_PackRequestWrite(LpPackTimeout, LpSigReplace->pInitValue);
      #endif
      /* Increment the index */
      LucSigReplaceIndex++;
      LpSigReplace = &Com_GaaSigReplace[LucSigReplaceIndex];
      /* Decrement the signal count*/
      LucNoOfSigCount--;
    }while(LucNoOfSigCount != COM_ZERO);
  }
  #endif

  /* @Trace: Com_SUD_API_00596 */
  #if(COM_RX_SIGNAL_SUBSTITUTE == STD_ON)
  LucNoOfSigCount = LpRxDm->ucNoOfSigSub;
  /* Check whether any replacement is configured */
  if(LucNoOfSigCount != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00597 */
    /* Get the pointer to LpSigSub structure */
    LucSigSubIndex = LpRxDm->ucSigSubIndex;
    LpSigSub = &Com_GaaSigSub[LucSigSubIndex];
    do
    {
      /* @Trace: Com_SUD_API_00598 */
      LpPackTimeout = &Com_GaaTxPack[LpSigSub->ddTxPackIndex];
      #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
      /* Invoke write function to pack the initial value into
         I-PDU/signal buffer */
      (void)Com_PackRequestWrite(LpPackTimeout, LpSigSub->pSubstitutionValue);
      #endif
      /* Increment the index */
      LucSigSubIndex++;
      LpSigSub = &Com_GaaSigSub[LucSigSubIndex];
      /* Decrement the signal count*/
      LucNoOfSigCount--;
    }while(LucNoOfSigCount != COM_ZERO);
  }
  #endif
  #if((COM_RX_SIGGROUP_REPLACE == STD_ON) || \
     (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON))
  /* @Trace: Com_SUD_API_00599 */
  LucNoOfSigCount = LpRxDm->ucNoOfSigGrpReplace;
  /* Check whether any replacement is configured */
  if(LucNoOfSigCount != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00600 */
    /* Get the pointer to LpSigReplace structure */
    LucSigReplaceIndex = LpRxDm->ucSigGrpReplaceIndex;
    LpSigGrpReplace = &Com_GaaSigGrpReplace[LucSigReplaceIndex];
    do
    {
      /* @Trace: Com_SUD_API_00601 */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      LpPackTimeout = &Com_GaaTxPack[LpSigGrpReplace->ddTxPackIndex];
      LpRxSigGroup = &Com_GaaRxSigGroup[LpSigGrpReplace->ddSigGrpIndex];
      /* Invoke write function to pack the initial value into
         I-PDU/signal buffer */
      (void)Com_PackSigGrp(LpPackTimeout, LpSigGrpReplace->pInitValue, 
        LpPackTimeout->pWrBuffer, LpRxSigGroup->pMaskingBuffer);
      
      /* Increment the index */
      LucSigReplaceIndex++;
      LpSigGrpReplace = &Com_GaaSigGrpReplace[LucSigReplaceIndex];
      /* Decrement the signal count*/
      LucNoOfSigCount--;
    }while(LucNoOfSigCount != COM_ZERO);
  }  
  #endif
  /* #7744 end */
  #if(COM_SIG_ERR_CBK_NOTIFY == STD_ON)
  /* @Trace: Com_SUD_API_00602 */
  /* Get the number of signals configured for error notification
  call-back */
  LucNoOfSigCount = LpRxDm->ucNoOfSigCallback;
  /* Check whether signal is configured for error notification
                                                         call-back */
  if(LucNoOfSigCount != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00603 */
    /* Get the pointer to SigErrorCbk structure */
    LddSigErrorCbkIndex = LpRxDm->ddSigErrCbkIndex;
    LpSigErrorCbk = &Com_GaaSigErrorCbk[LddSigErrorCbkIndex];
    /* Loop for all the signals configured for error notification
    (timeout) */
    do
    {
      /* @Trace: Com_SUD_API_00604 */
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      CoreMaskCheck = Com_GaaSigErrorCbkPositionMask[LddSigErrorCbkIndex];
      if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
      {
      #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
        /* @Trace: Com_SUD_API_00605 */
        /* Invoke the error notification call-back function with
                                        COM_TIMEOUT as a parameter */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        (LpSigErrorCbk->pSigErrorCbk)();
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)	
      }
      else
      {
        if(COM_TRUE == Com_GaaMulticoreDirectMode)
        {
          /* @Trace: Com_SUD_API_00606 */
          SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
          Com_GaaSigErrorCbkFlag[LddSigErrorCbkIndex] = CoreMaskCheck;
          SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
        }
        else
        {
          /* @Trace: Com_SUD_API_00607 */
          SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
          Com_GaaMainSigErrorCbkFlag[LddSigErrorCbkIndex] = CoreMaskCheck;
          SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
        }
        /* @Trace: Com_SUD_API_00608 */
        /* Get ptr of notify function */
        CoreIdCheck = CoreMaskCheck >> COM_ONE;
        /* Set Com_GaaMulticoreTriggerNotifyFlag */
        Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
      }    
      #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

      /* @Trace: Com_SUD_API_00609 */
      /* Get the pointer to n SigErrorCbk structure */
      LddSigErrorCbkIndex++;
      LpSigErrorCbk = &Com_GaaSigErrorCbk[LddSigErrorCbkIndex];
      /* Decrement the count of the number of signals configured for
                                    error notification call-back */
      LucNoOfSigCount--;
    }while(LucNoOfSigCount != COM_ZERO);
  } /* Check whether signal is configured for error notification */
  #endif /*#if(COM_SIG_ERR_CBK_NOTIFY == STD_ON) */
} 
#define COM_STOP_SEC_CODE
#include "MemMap.h" 
#endif
/*******************************************************************************
** Function Name        : Com_RxSigDMFilterReset                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LpRxDm                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxIpdu              **
**                                                 Com_GaaRxSignal            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
when Rx Timeout is occurred - Fixed by AUTRON START*/
#if((COM_RX_IPDU_DM == STD_ON) && (COM_RX_SIGNAL_FILTER == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxSigDMFilterReset(
                         P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm)
{
  /* @Trace: Com_SUD_API_00610 */
  /* Local variable to store signal configuration */
  uint8 LucSigConfig;
  uint16 LusNoOfSignal;
  /* Pointer to Rx I-Pdu structure */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Pointer to Rx Signal structure */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal;

  Com_SignalIdType LddRxSignalIndex;
  uint16 LddPeriod;
  
  if(LpRxDm != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_00611 */
    LpRxIpdu = &Com_GaaRxIpdu[LpRxDm->ddRxpduId];

    /* Get the number of  Rx signals */
    LusNoOfSignal = LpRxIpdu->usNoOfRxSignal;
    /* Internal Redmine #696 */
    /* Polyspace Useless if [A defect:Medium] This is a base code and the structure
     * "Com_GaaRxIpdu" is verified and generated by Generator Tool */
    if(LusNoOfSignal != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00612 */
      /* Get the pointer to  Rx signal structure */
      LddRxSignalIndex = LpRxIpdu->ddRxSigIndex;
      LpRxSignal = &Com_GaaRxSignal[LddRxSignalIndex];
      /* Loop for number of  Rx signals */
      do
      { 
        /* @Trace: Com_SUD_API_00613 */
        /* @Trace: SWS_Com_00694, SWS_Com_00325, SWS_Com_00380, SWS_Com_00439*/
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        LucSigConfig = LpRxSignal->ucRxSigConfig;
        LddPeriod = LpRxSignal->usPeriod;
        if((LucSigConfig & COM_RX_SIGNAL_FILTER_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_00614 */
          /* polyspace +3 RTE:COR [Not a defect:Low] "NULL pointer was assured by generator" */
          /* polyspace +2 RTE:IDP [Not a defect:Low] "NULL pointer was assured by generator" */
          (((P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST))
            (LpRxSignal->pFilter))->pFilterFuncPtr)
            (LpRxSignal->pFilter, NULL_PTR, COM_INVALID_PARAM, LddPeriod);
        }

        /* @Trace: Com_SUD_API_00615 */
        /* Decrement the count of number of signals */
        LusNoOfSignal--;

        /* Get the pointer to n Rx signal structure */
        LddRxSignalIndex++;
        LpRxSignal = &Com_GaaRxSignal[LddRxSignalIndex];
      }while(LusNoOfSignal != COM_ZERO);
    }
  }
} 
#define COM_STOP_SEC_CODE
#include "MemMap.h" 
#endif
/* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
when Rx Timeout is occurred - Fixed by AUTRON END*/


/*******************************************************************************
** Function Name        : Com_RxIpduCallout                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduInfoPtr, PduId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaRxIpdu                 **
**                                              Com_GaaRxIpduCallOut          **
**                        Function(s) invoked : pIpduCallout                  **
*******************************************************************************/
#if(COM_RX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
boolean Com_RxIpduCallout(PduIdType PduId, 
P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr)
{
  /* @Trace: Com_SUD_API_00616 */
  boolean LblCalloutFlag;
  /* Pointer to Rx Ipdu structure */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  
  LblCalloutFlag = COM_TRUE;
  LpRxIpdu = &Com_GaaRxIpdu[PduId];
  
  /* Check the function pointer is vaild before invoke the function 
  - Fixed by AUTRON START*/
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
  if(Com_GaaRxIpduCallOut[LpRxIpdu->ddIpduCalloutIndex].pIpduCallout 
  != NULL_PTR)  
  {
    /* @Trace: Com_SUD_API_00617 */
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON START*/            
    /* Invoke I-PDU callout function to upper layer */
    /* polyspace +2 CERT-C:DCL39-C [Justified:Low] "PduInfoType: Type of PduInfoPtr is defined by Autosar, it can not be modified. No impact" */
    LblCalloutFlag = (Com_GaaRxIpduCallOut[LpRxIpdu->ddIpduCalloutIndex].
    pIpduCallout)(PduId, PduInfoPtr);
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON END*/           
  }
  /* @Trace: Com_SUD_API_00618 */
  /* Check the function pointer is vaild before invoke the function 
  - Fixed by AUTRON END*/   
  return(LblCalloutFlag);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxIpduCallout                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduInfoPtr, PduId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaTxIpdu                 **
**                                              Com_GaaTxIpduCallOut          **
**                        Function(s) invoked : pIpduCallout                  **
*******************************************************************************/
#if(COM_TX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* polyspace +2 MISRA2012:8.13 [Justified:Low] "No impact of this rule violation" */
boolean Com_TxIpduCallout(PduIdType PduId, 
P2VAR(PduInfoType, AUTOMATIC, COM_VAR) PduInfoPtr)
{
  /* @Trace: Com_SUD_API_00619 */
  boolean LblCalloutFlag;
  /* Pointer to Rx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  
  LblCalloutFlag = COM_TRUE;
  LpTxIpdu = &Com_GaaTxIpdu[PduId];  

  /* Check the function pointer is vaild before invoke the function 
  - Fixed by AUTRON START*/
  if(Com_GaaTxIpduCallOut[LpTxIpdu->ddIpduCalloutIndex].pIpduCallout 
  != NULL_PTR)  
  {
    /* @Trace: Com_SUD_API_00620 */
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON START*/            
    /* Invoke I-PDU callout function to upper layer */
    LblCalloutFlag = (Com_GaaTxIpduCallOut[LpTxIpdu->ddIpduCalloutIndex].
    pIpduCallout)(PduId, PduInfoPtr);
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON END*/           
  }
  /* @Trace: Com_SUD_API_00621 */
  /* Check the function pointer is vaild before invoke the function 
  - Fixed by AUTRON END*/   
  return(LblCalloutFlag);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_TxIpduTriggerCallout                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduInfoPtr, PduId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaTxIpdu                 **
**                                              Com_GaaTxIpduCallOut          **
**                        Function(s) invoked : pIpduCallout                  **
*******************************************************************************/
#if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* polyspace +2 MISRA2012:8.13 [Justified:Low] "No impact of this rule violation" */
boolean Com_TxIpduTriggerCallout(PduIdType PduId, 
P2VAR(PduInfoType, AUTOMATIC, COM_VAR) PduInfoPtr)
{
  /* @Trace: Com_SUD_API_00622 */
  boolean LblCalloutFlag;
  /* Pointer to Rx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  
  LblCalloutFlag = COM_TRUE;
  LpTxIpdu = &Com_GaaTxIpdu[PduId];
  
  /* Check the function pointer is vaild before invoke the function 
  - Fixed by AUTRON START*/
  if(Com_GaaTxIpduCallOut[LpTxIpdu->ddIpduTriggerCalloutIndex].pIpduCallout 
  != NULL_PTR)  
  {
    /* @Trace: Com_SUD_API_00623 */
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON START*/            
    /* Invoke I-PDU callout function to upper layer */
    LblCalloutFlag = (Com_GaaTxIpduCallOut
    [LpTxIpdu->ddIpduTriggerCalloutIndex].pIpduCallout)(PduId, PduInfoPtr);
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON END*/           
  }
  /* @Trace: Com_SUD_API_00624 */
  /* Check the function pointer is vaild before invoke the function 
  - Fixed by AUTRON END*/   
  return(LblCalloutFlag);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_PackRequestWrite                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function invoke the configured packing         **
**                        function.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : LpTxPack, LpDataPtr                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaSigWrFuncPtr        **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
FUNC(void, COM_CODE) Com_PackRequestWrite
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpDataPtr)
{
  /* @Trace: Com_SUD_API_00625 */
  /* @Trace: SWS_Com_00472, SWS_Com_00674, SWS_Com_00829 */
  /* Invoke write function to pack data to buffer */
  /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  (Com_GaaSigWrFuncPtr[LpTxPack->ucWrFuncIndex].pWrFuncPtr)(LpTxPack,
  (P2CONST(void, AUTOMATIC, COM_CONST)) LpDataPtr);
  
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackRequestRead                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function invokes the configured unpacking      **
**                        function.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpDataPtr                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaSigRdFuncPtr        **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
/* polyspace:begin<MISRA-C:16.7:Not a defect:Justify with annotations>
 No Impact of this rule violation */
FUNC(void, COM_CODE) Com_UnPackRequestRead
  (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,         
  P2VAR(void, AUTOMATIC, COM_VAR) LpDataPtr)
{
  /* @Trace: Com_SUD_API_00626 */
  /* Invoke read function to unpack data from buffer */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
  (Com_GaaSigRdFuncPtr[LpRxUnpack->ucRdFuncIndex].pRdFuncPtr)
                                 (LpRxUnpack, LpDataPtr);  
}
/* polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations> 
No Impact of this rule violation */
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_MulticoreMainNotify                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function invokes the configured Notify         **
**                        function. Only support for multicore. This function **
**                        is invoke by MainFunctionRx                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaMainSigNotifCbk,    **
**                             Com_GaaSigErrorCbk, Com_GaaMainInvNotifCbk,    **
**                                                 Com_GaaMainSigNotifCbkMask,**
**                             Com_GaaSigErrorCbkMask, Com_GaaInvNotifCbkMask,**
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
	
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_MulticoreMainNotify(uint8 CoreId)
{
  /* @Trace: Com_SUD_API_00627 */
  #if((COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO))
  uint16 LulCount;  
  uint8 CoreIdMask;
  
  if(Com_GddComStatus != COM_UNINIT) 
  { 
    /* @Trace: Com_SUD_API_00628 */
    /* create mask of core id */
    CoreIdMask = COM_ONE<<CoreId;
    #if(COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
    /* Trigger all SigNotifCbk when its flag is set */
    /* @Trace: Com_SUD_API_00629 */
    /* @Trace: Com_SUD_API_00630 */
    for(LulCount=COM_ZERO; LulCount<COM_SIG_NOTIF_CBK_COUNT; LulCount++)
    {
      if(COM_ZERO != (Com_GaaMainSigNotifCbkFlag[LulCount] & CoreIdMask))
      {
        /* @Trace: Com_SUD_API_00631 */
        /* Invoke call-back function */
        (Com_GaaSigNotifCbk[LulCount].pSigNotifCbk)();
        /* Clear flag */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaMainSigNotifCbkFlag[LulCount] &= ~CoreIdMask;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
    }
    #endif /* (COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO) */
    #if(COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)
    /* Trigger all SigErrorCbk when its flag is set */
    /* @Trace: Com_SUD_API_00632 */
    /* @Trace: Com_SUD_API_00633 */
    for(LulCount=COM_ZERO; LulCount<COM_SIG_ERROR_CBK_COUNT; LulCount++)
    {
      if(COM_ZERO != (Com_GaaMainSigErrorCbkFlag[LulCount] & CoreIdMask))
      {
        /* @Trace: Com_SUD_API_00634 */
        /* Invoke call-back function */
        (Com_GaaSigErrorCbk[LulCount].pSigErrorCbk)();
        /* Clear flag */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaMainSigErrorCbkFlag[LulCount] &= ~CoreIdMask;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
    }
    #endif /* (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO) */
    #if(COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
    /* Trigger all InvNotifCbk when its flag is set */
    /* @Trace: Com_SUD_API_00635 */
    /* @Trace: Com_SUD_API_00636 */
    for(LulCount=COM_ZERO; LulCount<COM_INV_NOTIF_CBK_COUNT; LulCount++)
    {
      if(COM_ZERO != (Com_GaaMainInvNotifCbkFlag[LulCount] & CoreIdMask))
      {
        /* @Trace: Com_SUD_API_00637 */
        /* Invoke call-back function */
        (*(Com_GaaInvNotifCbk[LulCount]))();
        /* Clear flag */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaMainInvNotifCbkFlag[LulCount] &= ~CoreIdMask;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
    }
    #endif /* (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO) */
  }

  #endif /* ((COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)) */
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
/*******************************************************************************
** Function Name        : Com_MulticoreNotify                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function invokes the configured Notify         **
**                        function. Only support for multicore                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaSigNotifCbk,        **
**                             Com_GaaSigErrorCbk, Com_GaaInvNotifCbk,        **
**                                                 Com_GaaSigNotifCbkMask,    **
**                             Com_GaaSigErrorCbkMask, Com_GaaInvNotifCbkMask,**
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
	
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_MulticoreNotify(void)
{
  /* @Trace: Com_SUD_API_00638 */
  #if((COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO))
  uint16 LulCount;  
  uint8 CoreIdMask;
  CoreIdType CoreId;
  
  if(Com_GddComStatus != COM_UNINIT) 
  { 
    /* @Trace: Com_SUD_API_00639 */
    /* create mask of core id */
    CoreId = GetCoreID();
    CoreIdMask = COM_ONE<<CoreId;
    #if(COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
    /* Trigger all SigNotifCbk when its flag is set */
    /* @Trace: Com_SUD_API_00640 */
    /* @Trace: Com_SUD_API_00641 */
    for(LulCount=COM_ZERO; LulCount<COM_SIG_NOTIF_CBK_COUNT; LulCount++)
    {
      if(COM_ZERO != (Com_GaaSigNotifCbkFlag[LulCount] & CoreIdMask))
      {
        /* @Trace: Com_SUD_API_00642 */
        /* Invoke call-back function */
        (Com_GaaSigNotifCbk[LulCount].pSigNotifCbk)();
        /* Clear flag */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaSigNotifCbkFlag[LulCount] &= ~CoreIdMask;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
    }
    #endif /* (COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO) */
    #if(COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)
    /* Trigger all SigErrorCbk when its flag is set */
    /* @Trace: Com_SUD_API_00643 */
    /* @Trace: Com_SUD_API_00644 */
    for(LulCount=COM_ZERO; LulCount<COM_SIG_ERROR_CBK_COUNT; LulCount++)
    {
      if(COM_ZERO != (Com_GaaSigErrorCbkFlag[LulCount] & CoreIdMask))
      {
        /* @Trace: Com_SUD_API_00645 */
        /* Invoke call-back function */
        (Com_GaaSigErrorCbk[LulCount].pSigErrorCbk)();
        /* Clear flag */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaSigErrorCbkFlag[LulCount] &= ~CoreIdMask;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
    }
    #endif /* (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO) */
    #if(COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
    /* Trigger all InvNotifCbk when its flag is set */
    /* @Trace: Com_SUD_API_00646 */
    /* @Trace: Com_SUD_API_00647 */
    for(LulCount=COM_ZERO; LulCount<COM_INV_NOTIF_CBK_COUNT; LulCount++)
    {
      if(COM_ZERO != (Com_GaaInvNotifCbkFlag[LulCount] & CoreIdMask))
      {
        /* @Trace: Com_SUD_API_00648 */
        /* Invoke call-back function */
        (*(Com_GaaInvNotifCbk[LulCount]))();
        /* Clear flag */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaInvNotifCbkFlag[LulCount] &= ~CoreIdMask;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
    }
    #endif /* (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO) */
  }

  #endif /* ((COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)) */
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */


/*******************************************************************************
** Function Name        : Com_NotifyList_Init                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function invokes the configured Notify         **
**                        function. Only support for multicore                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaSigNotifCbk,        **
**                             Com_GaaSigErrorCbk, Com_GaaInvNotifCbk,        **
**                                                 Com_GaaSigNotifCbkMask,    **
**                             Com_GaaSigErrorCbkMask, Com_GaaInvNotifCbkMask,**
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
	
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_NotifyList_Init(void)
{
  /* @Trace: Com_SUD_API_00654 */
  #if((COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_TX_IPDU_COUNT > COM_MACRO_ZERO))
  uint16 LulCount;  
  #if(COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
  /* clear all SigNotifCbk when its flag is set */
  /* @Trace: Com_SUD_API_00655 */
  for(LulCount=COM_ZERO; LulCount<COM_SIG_NOTIF_CBK_COUNT; LulCount++)
  {
    /* Clear flag */
    /* @Trace: Com_SUD_API_00656 */
    Com_GaaSigNotifCbkFlag[LulCount] = COM_ZERO;
    Com_GaaMainSigNotifCbkFlag[LulCount] = COM_ZERO;
  }
  #endif /* (COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO) */
  #if(COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)
  /* Trigger all SigErrorCbk when its flag is set */
  /* @Trace: Com_SUD_API_00657 */
  /* @Trace: Com_SUD_API_00658 */
  for(LulCount=COM_ZERO; LulCount<COM_SIG_ERROR_CBK_COUNT; LulCount++)
  {
    /* Clear flag */
    /* @Trace: Com_SUD_API_00659 */
    Com_GaaSigErrorCbkFlag[LulCount] = COM_ZERO;
    Com_GaaMainSigErrorCbkFlag[LulCount] = COM_ZERO;
  }
  #endif /* (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO) */
  #if(COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
  /* Trigger all InvNotifCbk when its flag is set */
  /* @Trace: Com_SUD_API_00660 */
  /* @Trace: Com_SUD_API_00661 */
  for(LulCount=COM_ZERO; LulCount<COM_INV_NOTIF_CBK_COUNT; LulCount++)
  {
    /* @Trace: Com_SUD_API_00662 */
    /* Clear flag */
    Com_GaaInvNotifCbkFlag[LulCount] = COM_ZERO;
    Com_GaaMainInvNotifCbkFlag[LulCount] = COM_ZERO;
  }
  #endif /* (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO) */
  #if(COM_TX_IPDU_COUNT > COM_MACRO_ZERO)
  /* Trigger all TxIPdu when its flag is set */
  /* @Trace: Com_SUD_API_00663 */
  /* @Trace: Com_SUD_API_00664 */
  for(LulCount=COM_ZERO; LulCount<COM_TX_IPDU_COUNT; LulCount++)
  {
    /* @Trace: Com_SUD_API_00665 */
    /* Clear flag */
    Com_GaaTxIpduTransmitFlag[LulCount] = COM_ZERO;
  }
  #endif /* (COM_TX_IPDU_COUNT > COM_MACRO_ZERO) */
  
  #endif /* ((COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_SIG_ERROR_CBK_COUNT > COM_MACRO_ZERO)|| \
      (COM_INV_NOTIF_CBK_COUNT > COM_MACRO_ZERO)) */
  /* loop all core ID for clear Com_GaaMulticoreTriggerNotifyFlag*/
  /* @Trace: Com_SUD_API_00666 */
  /* @Trace: Com_SUD_API_00667 */
  for(LulCount = COM_ZERO; 
      LulCount < COM_MULTI_CORE_NUMBER; LulCount++)
  {
    /* @Trace: Com_SUD_API_00668 */
    Com_GaaMulticoreTriggerNotifyFlag[LulCount] = COM_FALSE;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

/*******************************************************************************
** Function Name        : Com_ClearTriggerNotifyFlag                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function clear all                             **
**                          Com_GaaMulticoreTriggerNotifyFlag                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                             Com_GaaMulticoreTriggerNotifyFlag              **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
	
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_ClearTriggerNotifyFlag(boolean lblDirectMode)
{
  /* @Trace: Com_SUD_API_00669 */ 
  Com_GaaMulticoreDirectMode = lblDirectMode;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

/*******************************************************************************
** Function Name        : Com_ProcessTriggerNotifyFlag                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function clear all                             **
**                          Com_GaaMulticoreTriggerNotifyFlag                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                             Com_GaaMulticoreTriggerNotifyFlag              **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
	
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_ProcessTriggerNotifyFlag(void)
{
  /* @Trace: Com_SUD_API_00670 */
  uint8 lucCountCoreId;
  /* loop all core ID */
  /* @Trace: Com_SUD_API_00671 */
  /* @Trace: Com_SUD_API_00672 */
  for(lucCountCoreId = COM_ZERO; 
      lucCountCoreId < COM_MULTI_CORE_NUMBER; lucCountCoreId++)
  {
    if(COM_TRUE == Com_GaaMulticoreTriggerNotifyFlag[lucCountCoreId])
    {
      if(COM_TRUE == Com_GaaMulticoreDirectMode)
      {
        /* @Trace: Com_SUD_API_00673 */
        /* Trigger Ioc write */
        (void)Com_GaaMulticoreNotifyList[lucCountCoreId](COM_TRUE);
        /* Clear Com_GaaMulticoreTriggerNotifyFlag after call Ioc */
        Com_GaaMulticoreTriggerNotifyFlag[lucCountCoreId] = COM_FALSE;
        /* Clear Com_GaaMulticoreDirectMode */
		    Com_GaaMulticoreDirectMode = COM_FALSE;
      }
      else
	    {
        /* @Trace: Com_SUD_API_00674 */
		    /* set Com_GaaMulticoreMainNotifyFlag */
        Com_GaaMulticoreMainNotifyFlag[lucCountCoreId] = COM_TRUE;
        /* Clear Com_GaaMulticoreTriggerNotifyFlag after set flag*/
        Com_GaaMulticoreTriggerNotifyFlag[lucCountCoreId] = COM_FALSE;
      }
    }
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

#if(COM_TX_IPDU == STD_ON)
/* polyspace-begin MISRA-C3:17.8 [Justified:Low] "Pointer update is expectation action. Tested by unit test." */
/*******************************************************************************
** Function Name        : Com_DirectMainTransmit                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes global data prepare for     **
**                        IPDU transmission directly                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   Com_TxSigConfirmation()  **
**                                                   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_DirectMainTransmit(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  PduIdType LddNoOfTxIpdu)
{
  #if((COM_TX_IPDU_DEFERRED == STD_ON) || (COM_TX_IPDU_DM == STD_ON))
  /* Check whether Tx Ipdu is transmitted successfully */
  if((LusTxIpduStatusBit & COM_TX_CONFIRM_STATUS_MASK) != COM_FALSE)
  {
    #if(COM_TX_IPDU_DM == STD_ON)
    /* Check whether Pdu is configured for deadline monitoring */
    if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00675 */
      /* Reset deadline monitoring timer to zero */
      Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] = (uint16)COM_ZERO;
    }
    #endif    
    /* Check whether TMS is configured */
    #if(COM_TX_IPDU_DM == STD_ON)
    
    if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
    {
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      if(((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK) == COM_FALSE) || (LpTxIpdu->ucTxConfigExtn!=COM_FALSE))
      #endif
      {
        if(LpTxMode->ucTxMode == COM_TX_NONE_MODE)
        {
          /* @Trace: Com_SUD_API_00676 */
          Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] =
          Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].usDmTimeout + (uint16)COM_ONE;
          
          SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
          Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] |= COM_TX_REQ_STATUS_MASK;
          SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();        
        }
      }
    }
    #else /* #if(COM_TX_IPDU_DM == STD_ON)*/
    /* @Trace: Com_SUD_API_01344 */
    COM_UNUSED(LddNoOfTxIpdu);
    COM_UNUSED_PTR(LpTxMode);
    COM_UNUSED_PTR(LpTxIpdu);
    #endif
    #if((COM_TX_IPDU_DEFERRED == STD_ON) && \
      (COM_TX_SIGNAL_NOTIFY  == STD_ON))
    /* Check whether Tx Ipdu is configured for deferred or immediate */
    if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DEF_NOTIFY_CONFIG_MASK)
                                    == COM_TX_IPDU_DEF_NOTIFY_CONFIG_MASK)
    {
      /* @Trace: Com_SUD_API_00677 */
      Com_TxSigConfirmation(LpTxIpdu);
    }
    #endif /* #if((COM_TX_IPDU_DEFERRED == STD_ON) && \
      (COM_TX_SIGNAL_NOTIFY  == STD_ON))*/
  }
  #else
  /* @Trace: Com_SUD_API_01345 */
  COM_UNUSED(LddNoOfTxIpdu);
  COM_UNUSED_PTR(LpTxIpdu);
  COM_UNUSED_PTR(LpTxMode);
  #endif
  #if(COM_TX_IPDU_DM == STD_ON)
  /* Check whether Deadline monitoring Status reset bit is set to true */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_01437 */
    Com_DirectMainTransmit_TxStsUpd(LusTxIpduStatusBit, LpTxIpdu, LddNoOfTxIpdu);   
  }
  #else
  /* @Trace: Com_SUD_API_01346 */
  COM_UNUSED(LusTxIpduStatusBit);
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_IndirectMainTransmit                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes global data prepare for     **
**                        IPDU transmission indirectly                        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   Com_TxSigConfirmation()  **
**                                                   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_IndirectMainTransmit(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu)
{
  /* @Trace: Com_SUD_API_01438 */
  #if(COM_TX_IPDU_DM == STD_ON)
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  #endif

  #if(COM_TX_IPDU_DM == STD_ON)
  /* Check whether Deadline monitoring Status reset bit is set to true */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator. " */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_01439 */
    Com_DirectMainTransmit_TxStsUpd(LusTxIpduStatusBit, LpTxIpdu, LddNoOfTxIpdu);
  }
  #else
  /* @Trace: Com_SUD_API_01347 */
  COM_UNUSED(LddNoOfTxIpdu);
  COM_UNUSED_PTR(LpTxIpdu);
  #endif
  #if((COM_TX_IPDU_DEFERRED == STD_ON) || (COM_TX_IPDU_DM == STD_ON))
  /* Check whether Tx Ipdu is transmitted successfully */
  if((LusTxIpduStatusBit & COM_TX_CONFIRM_STATUS_MASK) != COM_FALSE)
  {
    #if(COM_TX_IPDU_DM == STD_ON)
    /* @Trace: Com_SUD_API_00687 */
    LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
    /* Check whether Pdu is configured for deadline monitoring */
    if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00686 */
      /* Reset deadline monitoring timer to zero */
	  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
      Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] = (uint16)COM_ZERO;
    }
    #endif    
    /* Check whether TMS is configured */
    #if(COM_TX_IPDU_DM == STD_ON)
    if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
    {
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      if(((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK) 
        == COM_FALSE)||(LpTxIpdu->ucTxConfigExtn==COM_FALSE))
      #endif
      {
		/* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator. " */
        if(LpTxMode->ucTxMode == COM_TX_NONE_MODE)
        {
          /* @Trace: Com_SUD_API_00688 */
          Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] =
            Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].usDmTimeout + 
            (uint16)COM_ONE;
          SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
		  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
          Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] |= COM_TX_REQ_STATUS_MASK;
          SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        }
      }
    }
    #else
    /* @Trace: Com_SUD_API_01348 */
    COM_UNUSED(LddNoOfTxIpdu);
    #endif /*#if(COM_TX_IPDU_DM == STD_ON)*/
    #if((COM_TX_IPDU_DEFERRED == STD_ON) \
      && (COM_TX_SIGNAL_NOTIFY  == STD_ON))
    /* Check whether Tx Ipdu is configured for deferred or immediate */
    if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DEF_NOTIFY_CONFIG_MASK)
                                    == COM_TX_IPDU_DEF_NOTIFY_CONFIG_MASK)
    {
      /* @Trace: Com_SUD_API_00689 */
      Com_TxSigConfirmation(LpTxIpdu);
    }
    #endif /* #if((COM_TX_IPDU_DEFERRED == STD_ON) \
      && (COM_TX_SIGNAL_NOTIFY  == STD_ON))*/
  }
  #else
  /* @Trace: Com_SUD_API_01349 */
  COM_UNUSED_PTR(LpTxIpdu);
  COM_UNUSED(LusTxIpduStatusBit);
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_NTimesTxModeHandle                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes global data prepare for     **
**                        N-Times Tx Mode IPDU handling                       **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxReptTimer       **
**                                                   Com_GaaTxReptCount       **
**                                                   Com_GaaTxReptSubCount    **
**                                                   Com_GaaReptStatus        **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if(COM_TX_IPDU_REPETITION == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_NTimesTxModeHandle(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  PduIdType LddNoOfTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTimer,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag)      
{
  /* @Trace: Com_SUD_API_00690 */
  uint8 LucReptSubCount;

  uint16 LusTimer;

  /* Reset the counter and timer if send request is called from
      application */
  if((LusTxIpduStatusBit & COM_TX_REPT_STATUS_MASK) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00691 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] =
                                            LpTxMode->usReptTimerValue;
    if (LpTxMode->ucDirectMainTransmit == COM_TX_DIRECT_TRANS)   
    {                                  
      if((LusTxIpduStatusBit & COM_TX_MAINFUNC_SEND_STATUS_MASK) 
        != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00692 */
        Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] 
          = Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] - (uint16)COM_ONE;
      }
    }
    else
    {
      /* @Trace: Com_SUD_API_00693 */
      Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] 
          = LpTxMode->ucReptCount;
      if(LpTxMode->ucReptCount != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00694 */
        Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex]
            = LpTxMode->ucReptCount - COM_ONE;

        if(Com_GaaReptStatus[LddNoOfTxIpdu] != COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00695 */
          Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex]
            = LpTxMode->ucReptCount;
          Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex]++;
          Com_GaaReptStatus[LddNoOfTxIpdu] = COM_ZERO;
        }
      }
      else
      {
        /* @Trace: Com_SUD_API_00696 */
        Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] = COM_ZERO;
      }
    }
  }
  else
  {
    /* Check whether repetition count is not equal to zero */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if((Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO) 
    || (Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO))
    {
      /* @Trace: Com_SUD_API_00697 */
      /* Get the repetition timer value to a local variable */
      *LpTimer = (Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex]);
      /* Decrement the repetition timer value in local variable */
      (*LpTimer)--;
      LusTimer = LpTimer[COM_ZERO];
      /* Check whether repetition timer in local variable is equal
      to zero */
      if(LusTimer == (uint16)COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00698 */
        /* Load the configured repetition timer value to local
        variable */
        *LpTimer = (LpTxMode->usReptTimerValue);
        /* Set Transmit flag to true */
        *LpTransmitFlag = COM_TRUE;
        LucReptSubCount = Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex];
        if(LucReptSubCount != COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00699 */
          /* Decrement the repetition count */
          LucReptSubCount--;
          /* Set the repetition count */
          Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] = LucReptSubCount;
        }
        #if(COM_ENABLE_MDT_CYCLIC == STD_OFF)
        /* @Trace: Com_SUD_API_00700 */
        SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] 
          |= COM_TX_REPT_CONFIRM_HANDLE_MASK;
        SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        #endif                  
      } /* Check whether repetition timer in local variable is
            equal to zero */
      /* Load the repetition timer value from local variable to
        the repetition timer */
      /* @Trace: Com_SUD_API_00701 */
      Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] = *LpTimer;
    }
  } /* Check whether repetition count is not equal to zero */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_MinDelayTxHandle                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes global data prepare for     **
**                        Minimum delay IPDU transmission handling            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxMDTimer         **
**                                                   Com_GaaTxMode            **
**                                                   Com_GaaTxReptTimer       **
**                                                   Com_GaaTxReptCount       **
**                                                   Com_GaaTxReptSubCount    **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MinDelayTxHandle(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag)         
{
  /* @Trace: Com_SUD_API_00702 */
  uint16 LusTimer;
  uint16 LusTxIpduStatusBit;
  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_REPETITION == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  /* Get the pointer to Tx Mode */
  LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
  #endif
      
  LusTimer = Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex];

  LusTxIpduStatusBit = Com_GaaTxIpduStatusBit[LddNoOfTxIpdu];

  if(LusTimer != (uint16)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00703 */
    /* Decrement periodic timer */
    --LusTimer;
    /* Check whether minimum delay timer is equal to zero */
    if((uint16)COM_ZERO == LusTimer)
    {
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      /* Check if the transmission mode is configured as true/false */
      if((LusTxIpduStatusBit & COM_TX_TMS_STATUS_MASK) == COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00705 */
        LpTxMode = 
        &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex
        +(PduIdType)COM_ONE];          
      }
      #endif
      
      /* Check whether Tx pending flag is true */
      if(((LusTxIpduStatusBit & COM_TX_PENDING_STATUS_MASK) 
        != COM_FALSE))
      {
        /* @Trace: Com_SUD_API_00706 */
        *LpTransmitFlag = COM_TRUE;
        SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &=
                                (uint16)(COM_TX_PENDING_STATUS_CLEAR_MASK);
                    
        /* #2022 MDTForCyclicTransmission related compile error 
        & incorrect operation is fixed(ref 4.2.1 Com Spec) */                     
        #if(COM_ENABLE_MDT_CYCLIC == STD_OFF)
        Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] 
        &= (uint16)(~COM_TX_REPT_CONFIRM_HANDLE_MASK);
        #endif
        SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();

        #if(COM_TX_IPDU_REPETITION == STD_ON)
        if((LpTxMode->ucTxMode == COM_TX_DIRECTNTIMES_MODE) ||
        (LpTxMode->ucTxMode == COM_TX_MIXEDNTIMES_MODE))
        {
          /* Check whether repetition counter is not equal to zero */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          if((Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO) 
          || (Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO))
          {
            /* @Trace: Com_SUD_API_00707 */
            /* Load the Tx repetition timer value from the configured
            repetition value */
            Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] =
                                            LpTxMode->usReptTimerValue;
          }
        }
        #endif /*(COM_TX_IPDU_REPETITION == STD_ON)*/
      } /* Check Tx pending flag is set to true */
    } /* Check whether minimum delay timer is equal to zero */
    /* @Trace: Com_SUD_API_00708 */
    SchM_Enter_Com_TX_MDT_PROTECTION_AREA();
    /* Reset minimum delay timer to zero */
    Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] = LusTimer;
    SchM_Exit_Com_TX_MDT_PROTECTION_AREA();
  } /* Check whether minimum delay timer is configured */
  else if(((LusTxIpduStatusBit & COM_TX_PENDING_STATUS_MASK) != COM_FALSE))
  /* Check whether Tx pending flag is true */
  {
    /* @Trace: Com_SUD_API_00709 */
    *LpTransmitFlag = COM_TRUE;
    SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &=
                            (uint16)(COM_TX_PENDING_STATUS_CLEAR_MASK);
                
    /* #2022 MDTForCyclicTransmission related compile error 
    & incorrect operation is fixed(ref 4.2.1 Com Spec) */                     
    #if(COM_ENABLE_MDT_CYCLIC == STD_OFF)
    Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] 
    &= (uint16)(~COM_TX_REPT_CONFIRM_HANDLE_MASK);
    #endif
    SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();

    #if(COM_TX_IPDU_REPETITION == STD_ON)
    if((LpTxMode->ucTxMode == COM_TX_DIRECTNTIMES_MODE) ||
    (LpTxMode->ucTxMode == COM_TX_MIXEDNTIMES_MODE))
    {
      /* Check whether repetition counter is not equal to zero */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      if((Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO) 
      || (Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO))
      {
        /* @Trace: Com_SUD_API_00710 */
        /* Load the Tx repetition timer value from the configured
        repetition value */
        Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] =
                                        LpTxMode->usReptTimerValue;
      }
    }
    #endif /*(COM_TX_IPDU_REPETITION == STD_ON)*/
  } /* Check Tx pending flag is set to true */
  else
  {
    /* Do nothing */
  }

  /* @Trace: Com_SUD_API_00711 */
  #if(COM_TX_IPDU_REPETITION == STD_OFF)
  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
  COM_UNUSED_PTR(LpTxMode);
  #endif
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_IPduTxDmDelayHandle                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function update global data prepare for        **
**                        deadline monitoring and minimum delay               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxMDTimer         **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_TX_IPDU_DM == STD_ON) || ((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
  (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_IPduTxDmDelayHandle(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  uint16 LusTxIpduStatusBit,
  uint8 LucTxConfig,
  uint8 LucTxMode,
  PduIdType LddNoOfTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag)       
{
  #if(COM_TX_IPDU_DM == STD_ON)
  /* Check whether Tx deadline monitoring is configured */
  if((LucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
  {
    if(LucTxMode <= COM_TX_MIXEDNTIMES_MODE)
    {
      /* Check whether deadline monitoring timer is zero */
      if((Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex]) == (uint16)COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00712 */
        /* Load the deadline monitoring timer with the deadline
        monitoring timeout value */
        Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] =
        Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].usDmTimeout 
        + (uint16)COM_ONE;
      }
    }
  } /* Check whether Tx deadline monitoring is configured */
  #endif /* #if(COM_TX_IPDU_DM == STD_ON) */

  /* #2022 MDTForCyclicTransmission related compile error 
  & incorrect operation is fixed(ref 4.2.1 Com Spec) */
  #if((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
    (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
  /* Check whether minimum delay timer is configured */
  if((LucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00713 */
    *LpTransmitFlag = COM_FALSE;
    /* Check whether minimum delay timer is reset to zero */
    if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] == (uint16)COM_ZERO)
    {
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      if((LucTxMode != COM_TX_PERIODIC_MODE) ||
        ((LusTxIpduStatusBit & COM_TX_PENDING_STATUS_MASK) == COM_FALSE))
      {
        /* @Trace: Com_SUD_API_00714 */
        /* Invoke Com_Transmit to transmit an Ipdu to the lower
          layer */
        *LpTransmitFlag = COM_TRUE;
      }
      #else
      /* @Trace: Com_SUD_API_01350 */
      /* Invoke Com_Transmit to transmit an Ipdu to the lower
          layer */
      *LpTransmitFlag = COM_TRUE;
      COM_UNUSED(LusTxIpduStatusBit);
      COM_UNUSED(LucTxMode);
      #endif /* #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || (COM_TX_IPDU_TMS_EXPLICIT == STD_ON)) */
    }
    else
    {
      /* @Trace: Com_SUD_API_00715 */
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] 
        |= COM_TX_PENDING_STATUS_MASK;
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    }
  }
  #else
  /* @Trace: Com_SUD_API_01351 */
  COM_UNUSED(LusTxIpduStatusBit);
  COM_UNUSED(LddNoOfTxIpdu);
  COM_UNUSED_PTR(LpTransmitFlag);

  #if(COM_TX_IPDU_DM == STD_OFF)
  /* @Trace: Com_SUD_API_01831 */
  COM_UNUSED_PTR(LpTxIpdu);
  COM_UNUSED(LucTxConfig);
  COM_UNUSED(LucTxMode);
  #endif
  #endif 
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end MISRA-C3:17.8 [Justified:Low] "Pointer update is expectation action. Tested by unit test." */
#endif /* End of #if(COM_TX_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : Com_MainFuncTx_UpdtPdTmrAndRept                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_TX_IPDU_PT == STD_ON) &&\
  (COM_TX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_UpdtPdTmrAndRept(
P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag,
P2VAR(uint16, AUTOMATIC, COM_VAR) LpTimer,
PduIdType LddNoOfTxIpdu)
{
  /* Check whether current Tx mode is periodic or mixed */
  if(LpTxMode->ucTxMode <= COM_TX_MIXEDNTIMES_MODE)
  {
    /* @Trace: Com_SUD_API_00349 */
    /* Get the Tx periodic timer value to local variable */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    *LpTimer = 
      Com_GaaTxPeriodicTimer[LpTxIpdu->ddTxPeriodicTimerIndex];
    /* Decrement the Tx periodic timer value in the local
    variable */
    *LpTimer = (*LpTimer) - 1;
    /* Check whether Tx periodic timer value is equal to zero */
    if(*LpTimer == (uint16)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00350 */
      *LpTimer = LpTxMode->usPeriodicValue;
      *LpTransmitFlag = COM_TRUE;

      /* #3447 handling overlap condition of MIXED type PDU */
      if(LpTxMode->ucTxMode == COM_TX_MIXEDNTIMES_MODE)
      {
        #if(COM_TX_REPT_COUNT > COM_MACRO_ZERO)
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
        if((Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO) 
        || (Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] != COM_ZERO))
        {
          /* @Trace: Com_SUD_API_00351 */
          *LpTransmitFlag = COM_FALSE;
        }
        #endif
      }
      
      /* #2022 MDTForCyclicTransmission related compile error 
      & incorrect operation is fixed(ref 4.2.1 Com Spec) */
      #if(COM_ENABLE_MDT_CYCLIC == STD_OFF)
      /* @Trace: Com_SUD_API_00352 */
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] 
        |= COM_TX_REPT_CONFIRM_HANDLE_MASK;
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      #else
      COM_UNUSED(LddNoOfTxIpdu);
      #endif
    }
    /* Load the periodic timer value in the local variable to the
      Tx periodic timer */
    /* @Trace: Com_SUD_API_00353 */
    Com_GaaTxPeriodicTimer[LpTxIpdu->ddTxPeriodicTimerIndex] = 
      *LpTimer;
  } /* Check whether current Tx mode is periodic or mixed */
} /* Check whether current Tx mode is not none */
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_MainFuncTx_UpdrTpIpduSts                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxTPIpdu          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) && (COM_TX_TP_SUPPORT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_UpdrTpIpduSts(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR)  LpTransmitFlag)       
{
  /* @Trace: Com_SUD_API_01440 */
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
  {
    if((Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &
        COM_TX_TP_BUFFER_STATUS_MASK) != COM_FALSE)
    /* CHeck TP data is pending due to TP buffer lock*/
    {
      /* @Trace: Com_SUD_API_00358 */
      /* Get the pointer to TP structure */
      LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
      /* check TP buffer is already unlock*/
      if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
      & (LpTxTPIpdu->ucTxTPStatusMask)) == COM_ZERO)
      {        
        #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
        /* Check whether Ipdu is transmitted successfully */
          if((LpTxIpdu->ucTxConfig & 
          COM_TX_IPDU_MDT_CONFIG_MASK) != (COM_ZERO))
          { 
              /* @Trace: Com_SUD_API_00359 */
              Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] |= 
                  COM_TX_PENDING_STATUS_MASK;
          }
          else
          {
              /* @Trace: Com_SUD_API_00360 */
              *LpTransmitFlag = COM_TRUE;
          }
        #else /*(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)*/
        /* @Trace: Com_SUD_API_01334 */
        *LpTransmitFlag = COM_TRUE;
        #endif /*(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)*/
        /* @Trace: Com_SUD_API_00361 */
        Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &=~ 
            COM_TX_TP_BUFFER_STATUS_MASK; 
      }
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_MainFuncTx_UpdrTxFlg                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if((COM_TX_RETRY_REQUEST == STD_ON) ||\
(COM_MAINFUNC_BASED_TRANSMIT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_UpdrTxFlg(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag)
{

  #if(COM_TX_RETRY_REQUEST == STD_ON)
  /* Check whether Tx RETRY bit is set to one */
  if(((LusTxIpduStatusBit & COM_TX_RETRY_STATUS_MASK) != COM_FALSE) && 
      (LpTxMode->ucTxMode != COM_TX_NONE_MODE))
  {
    /* @Trace: Com_SUD_API_00356 */
    /* If so transmit an I-PDU once again to lower layer */
    *LpTransmitFlag = COM_TRUE;
  }
  #endif
  /* #1463 : Add mainfunction transmit option for trigger on change 
  transfer type */
  #if(COM_MAINFUNC_BASED_TRANSMIT == STD_ON)
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and could be changed in another configuration" */
  if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
  {
    if(((LusTxIpduStatusBit & COM_TX_MAINFUNC_SEND_STATUS_MASK) 
      != COM_FALSE) && (LpTxMode->ucTxMode != COM_TX_NONE_MODE))
    {
      /* @Trace: Com_SUD_API_00357 */
      /* If so transmit an I-PDU once again to lower layer */
      *LpTransmitFlag = COM_TRUE;
    }
  }
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


/*******************************************************************************
** Function Name        : Com_RxSigProc_FltrAndUpdrBuffer                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaRxUnpack          **
**                                                   Com_GaaRxInvalid         **
**                                                   Com_GaaRxTPflg           **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_RX_SIGNAL == STD_ON) &&\
((COM_RX_SIGNAL_FILTER == STD_ON) ||\
(COM_RX_SIGNAL_INVALID == STD_ON) ||\
(COM_RX_SIGNAL_UBDMREPLACE == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxSigProc_FltrAndUpdrBuffer(
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalData, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig, 
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform,
  Com_SignalIdType LddRxSignalIndex)
#else
FUNC(void, COM_CODE) Com_RxSigProc_FltrAndUpdrBuffer(
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalData, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig)
#endif
{
  /* @Trace: Com_SUD_API_01441 */
  #if (COM_RX_INVALIDNOTIFY == STD_ON)
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #endif
 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalDataRep = LpSignalData;
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  LpRxUnpack = &Com_GaaRxUnpack[LpRxSignal->ddRxUnpackIndex];

  #if(((COM_RX_SIGNAL_FILTER == STD_ON) ||\
    (COM_RX_SIGNAL_INVALID == STD_ON) ||\
    (COM_RX_SIGNAL_UBDMREPLACE == STD_ON)) &&\
    (COM_RX_TP_SUPPORT == STD_ON))
  PduIdType LucRxPduId;
  #endif
  #if ((COM_RX_SIGNAL_FILTER == STD_ON) || (COM_RX_SIGNAL_INVALID == STD_ON)\
                                      ||(COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
  /* Local variable to store signal size */
  PduLengthType LddSignalSize;
  /* Local variable to store signal type */
  uint8 LucSignalType;
  /* Get the type of the signal */
  LucSignalType = LpRxUnpack->ucSignalType;
  /* Get the size of the signal */
  LddSignalSize = LpRxUnpack->ddSignalSize;
  #endif
  #if(COM_RX_SIGNAL_INVALID == STD_ON)
  /* Pointer to Rx Invalid structure */
  P2CONST(Com_RxInvalid, AUTOMATIC, COM_CONST) LpRxInvalid;
  #endif
  #if(COM_RX_SIGNAL_FILTER == STD_ON)
  uint16 LddPeriod;
  #endif
    /* Reqs 838, 839*/ 
  #if(COM_RX_TP_SUPPORT == STD_ON) 
  LucRxPduId = LpRxSignal->ddRxpduId;
  if(Com_GaaRxTPflg[LucRxPduId] != COM_ZERO)
  {
    #if (COM_RX_SIGNAL_INVALID == STD_ON)
    /* Check whether invalidation has been configured */
    if((*LpSigConfig & COM_RX_SIGNAL_INVALID_CONFIG_MASK) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00439 */
      LpRxInvalid = &(Com_GaaRxInvalid[LpRxSignal->ucInvIndex]);
      /* Check whether invalidation with replacement
      has been configured */
      if((*LpSigConfig & COM_RX_SIGNAL_INVREPLACE_CONFIG_MASK) 
      != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00440 */
        /* Get the pointer to init value */
        /* polyspace:begin<MISRA-C:11.5:Not a defect:Justify with annotations> No Impact of this rule violation */
        /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        LpSignalDataRep = (P2CONST(uint8, AUTOMATIC, COM_CONST))
          (LpRxInvalid->pInitValue);
        /* polyspace:end<MISRA-C:11.5:Not a defect:Justify with annotations> No Impact of this rule violation */
      }
      else
      {
        /* @Trace: Com_SUD_API_00441 */
        #if (COM_RX_INVALIDNOTIFY == STD_ON)
        #if (STD_ON == COM_MULTI_CORE_SUPPORT)
        CoreMaskCheck = Com_GaaInvNotifCbkPositionMask[
          LpRxInvalid->ddInvNotifCbkIndex];
        if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
        {
        #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
          /* @Trace: Com_SUD_API_00442 */
          /* Invoke invalid notification call-back function */
          /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
          (*(Com_GaaInvNotifCbk[LpRxInvalid->ddInvNotifCbkIndex]))();
        #if (STD_ON == COM_MULTI_CORE_SUPPORT)		
        }
        else
        {
          if(COM_TRUE == Com_GaaMulticoreDirectMode)
          {
              /* @Trace: Com_SUD_API_00443 */
            SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
            Com_GaaInvNotifCbkFlag[LpRxInvalid->ddInvNotifCbkIndex] = 
              CoreMaskCheck;
            SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
          }
          else
          {
              /* @Trace: Com_SUD_API_00444 */
            SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
            Com_GaaMainInvNotifCbkFlag[LpRxInvalid->ddInvNotifCbkIndex] = 
              CoreMaskCheck;
            SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
          }
          /* @Trace: Com_SUD_API_00445 */
          /* Get ptr of notify function */
          CoreIdCheck = CoreMaskCheck >> COM_ONE;
          /* Set Com_GaaMulticoreTriggerNotifyFlag */
          Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
        }    
        #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
        #endif
        #if (COM_RX_SIGNAL_NOTIFY == STD_ON)
        /* @Trace: Com_SUD_API_00446 */
        /* Set signal configuration to zero */
        *LpSigConfig = COM_ZERO; 
        #endif
      } /* Invoke invalid function and check the return value */
    } /* Check whether invalidation has been configured */
    #endif /*((COM_RX_SIGNAL_INVALID == STD_ON))*/
  }   
  else /* loop for callout */
  #endif /*(COM_RX_TP_SUPPORT == STD_ON) && (COM_RX_IPDU_CALLOUT == STD_ON)*/
  {
    #if (COM_RX_SIGNAL_INVALID == STD_ON)
    /* Check whether invalidation has been configured */
    if((*LpSigConfig & COM_RX_SIGNAL_INVALID_CONFIG_MASK) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00447 */
      LpRxInvalid = &(Com_GaaRxInvalid[LpRxSignal->ucInvIndex]);
      /* Invoke invalid function and check the return value */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      if((Com_GaaInvalidFuncPtr[LucSignalType].pInvalidFuncPtr)
      (LpRxInvalid->pInvalidValue,LpSignalDataRep,LddSignalSize)
                                                          != COM_FALSE)
      {
        /* Check whether invalidation with replacement
        has been configured */
        if((*LpSigConfig & COM_RX_SIGNAL_INVREPLACE_CONFIG_MASK) 
          != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_00448 */
          /* Get the pointer to init value */
          /* polyspace:begin<MISRA-C:11.5:Not a defect:Justify with annotations> No Impact of this rule violation */
          LpSignalDataRep = 
              (P2CONST(uint8, AUTOMATIC, COM_CONST))(LpRxInvalid->pInitValue);
          /* polyspace:end<MISRA-C:11.5:Not a defect:Justify with annotations> No Impact of this rule violation */                    
          /* Negation of sixth bit for getting 
          original signal configuration */
          *LpSigConfig &= (uint8)(COM_RX_SIGNAL_FILTER_CONFIG_CLEAR_MASK);
        }
        else
        {
          /* @Trace: Com_SUD_API_00449 */
          #if (COM_RX_INVALIDNOTIFY == STD_ON)
          #if (STD_ON == COM_MULTI_CORE_SUPPORT)
          CoreMaskCheck = 
            Com_GaaInvNotifCbkPositionMask[LpRxInvalid->ddInvNotifCbkIndex];
          if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
          {
          #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
            /* @Trace: Com_SUD_API_00450 */
            /* Invoke invalid notification call-back function */
            /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
            (*(Com_GaaInvNotifCbk[LpRxInvalid->ddInvNotifCbkIndex]))();
          #if (STD_ON == COM_MULTI_CORE_SUPPORT)		
          }
          else
          {
            if(COM_TRUE == Com_GaaMulticoreDirectMode)
            {
              /* @Trace: Com_SUD_API_00451 */
              SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
              Com_GaaInvNotifCbkFlag[
                LpRxInvalid->ddInvNotifCbkIndex] = CoreMaskCheck;
              SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
            }
            else
            {
              /* @Trace: Com_SUD_API_00452 */
              SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
              Com_GaaMainInvNotifCbkFlag[
                LpRxInvalid->ddInvNotifCbkIndex] = CoreMaskCheck;
              SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
            }
            /* @Trace: Com_SUD_API_00453 */
            /* Get ptr of notify function */
            CoreIdCheck = CoreMaskCheck >> COM_ONE;
            /* Set Com_GaaMulticoreTriggerNotifyFlag */
            Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
          }
          #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
          #endif
          /* @Trace: Com_SUD_API_00454 */
          /* Set signal configuration to zero */
          *LpSigConfig = COM_ZERO;
        }
      } /* Invoke invalid function and check the return value */
    } /* Check whether invalidation has been configured */
    #endif/*#if (COM_RX_SIGNAL_INVALID == STD_ON)*/

    #if (COM_RX_SIGNAL_FILTER == STD_ON)
    /* @Trace: SWS_Com_00695 */
    /* Check whether filtering is configured for signal */
    if((*LpSigConfig & COM_RX_SIGNAL_FILTER_CONFIG_MASK) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00455 */
      LddPeriod = LpRxSignal->usPeriod;
      /* @Trace: SWS_Com_00694, SWS_Com_00325, SWS_Com_00380, SWS_Com_00439*/
      /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
      when Rx Timeout is occurred - Fixed by AUTRON START*/     
      /* Invoke filter function and check the return value */
      /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
      /* polyspace:begin<RTE: COR : Not a defect : No Action Planned> Not Null Pointer */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      if(COM_FALSE == (((P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST))
        (LpRxSignal->pFilter))->pFilterFuncPtr)
        (LpRxSignal->pFilter, LpSignalDataRep, COM_ZERO,LddPeriod ))
      {
        /* @Trace: Com_SUD_API_00456 */
        /* Set signal configuration to zero */
        *LpSigConfig = COM_ZERO;
        #if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
        {
          if((LpRxSignal->ucRxSigConfig & COM_RX_SIGNAL_IDSM_MASK) != COM_ZERO)
          {
            /* Redmine #15053: Store IdsM Informations to global variables */
            if(LpIdsMInform->ucInvRangeSigListIndex < COM_FOUR)
            {
              /* @Trace: Com_SUD_API_00457 */
              LpIdsMInform->blIsInvRangeSigPdu = COM_TRUE;
              LpIdsMInform->aaInvRangeSigList[
                LpIdsMInform->ucInvRangeSigListIndex]
                = (uint16)LddRxSignalIndex;
              LpIdsMInform->ucInvRangeSigListIndex ++;
            }
          }
        }
        #endif
      }
      /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
      /* polyspace:end<RTE: COR : Not a defect : No Action Planned> Not Null Pointer */            
      /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
      when Rx Timeout is occurred - Fixed by AUTRON END*/           
    }
    #endif
    /* Check whether signal configuration is equal to zero */
    if(*LpSigConfig != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00458 */
      /* Invoke write function to pack signal data into signal buffer */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaWrFuncPtr[LucSignalType].pWrFuncPtr
                  (LpSignalDataRep, LpRxSignal->pSignalBuffer, LddSignalSize);

    }
  }/* Check whether signal is configured for invalidation/filtering/update
  bit deadline monitoring with timeout replacement */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxSigProc_RxSigNotif                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigProcessing                 **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaSigNotifCbk       **
**                                                   Com_GaaSigNotifCbkFlag   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_RX_SIGNAL == STD_ON) && (COM_RX_SIGNAL_NOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxSigProc_RxSigNotif(
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal,
  uint8 LucSigConfig)
{
  /* @Trace: Com_SUD_API_01442 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  
  /* Check whether notification has been configured for signal */
  if((LucSigConfig & COM_RX_SIGNAL_NOTIF_CONFIG_MASK) != COM_FALSE)
  {
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    /* @Trace: Com_SUD_API_00459 */
    CoreMaskCheck = 
      Com_GaaSigNotifCbkPositionMask[LpRxSignal->ddNotifCbkIndex];
    Com_GaaSigNotifCbkFlag[LpRxSignal->ddNotifCbkIndex] = 
      Com_GaaSigNotifCbkPositionMask[LpRxSignal->ddNotifCbkIndex];
    if(COM_ZERO != (Com_GaaSigNotifCbkPositionMask[
      LpRxSignal->ddNotifCbkIndex] & CoreIdMask))
    {
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
      /* @Trace: Com_SUD_API_00460 */
      /* Invoke notification call-back function */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      (Com_GaaSigNotifCbk[LpRxSignal->ddNotifCbkIndex].pSigNotifCbk)();
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    }
    else
    {
      if(COM_TRUE == Com_GaaMulticoreDirectMode)
      {
        /* @Trace: Com_SUD_API_00461 */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaSigNotifCbkFlag[
          LpRxSignal->ddNotifCbkIndex] = CoreMaskCheck;	  
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
      else
      {
        /* @Trace: Com_SUD_API_00462 */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaMainSigNotifCbkFlag[
          LpRxSignal->ddNotifCbkIndex] = CoreMaskCheck;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
      /* @Trace: Com_SUD_API_00463 */
      /* Get ptr of notify function */
      CoreIdCheck = CoreMaskCheck >> COM_ONE;
      /* Set Com_GaaMulticoreTriggerNotifyFlag */
      Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
    }
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxSigProc_SingleRxSigProc                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigProcessing                 **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaRxUnpack          **
**                                                   Com_GaaRxSignal          **
**                        Function(s) invoked: Com_RxSigProc_FltrAndUpdrBuffer**
*******************************************************************************/
#if(COM_RX_SIGNAL == STD_ON)
#if ((COM_RX_SIGNAL_FILTER == STD_ON) ||\
  (COM_RX_SIGNAL_INVALID == STD_ON) ||\
  (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if (COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxSigProc_SingleRxSigProc(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  PduLengthType LddSignalMemSize,
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig,
  Com_SignalIdType LddRxSignalIndex)
#else
FUNC(void, COM_CODE) Com_RxSigProc_SingleRxSigProc(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  PduLengthType LddSignalMemSize,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigConfig,
  Com_SignalIdType LddRxSignalIndex)
#endif
{
  /* @Trace: Com_SUD_API_01443 */
  /* buffer Loop Index */  
  PduLengthType LddBufferIndex;
  
  #if((COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) ||\
    ((COM_RX_SIGNAL_FILTER == STD_ON) ||\
    (COM_RX_SIGNAL_INVALID == STD_ON) ||\
    (COM_RX_SIGNAL_UBDMREPLACE == STD_ON)))
  /* Pointer to Rx Signal structure */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal;
  LpRxSignal = &Com_GaaRxSignal[LddRxSignalIndex]; 
  #endif
  
  #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO)
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  LpRxUnpack = &Com_GaaRxUnpack[LpRxSignal->ddRxUnpackIndex];
  #endif

  /* Pointer to Rx unpack structure */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalData = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalDataVar = NULL_PTR;

  if(COM_FALSE 
    == (LpRxIpdu->ucRxConfig & COM_RX_IPDU_DEFERRED_CONFIG_MASK))
  {    
    /* @Trace: Com_SUD_API_00430 */
    /* @Trace: Com_SUD_API_00431 */   
    #if(COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) 
    for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
    LddSignalMemSize; LddBufferIndex++)
    {
      /* @Trace: Com_SUD_API_00432 */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaSignalValidCKBufferIM[LddBufferIndex] = COM_ZERO;
    }

    /* @Trace: Com_SUD_API_00433 */
    LpSignalDataVar = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                              &Com_GaaSignalValidCKBufferIM[COM_ZERO];
    LpSignalData = (P2CONST(uint8, AUTOMATIC, COM_CONST))LpSignalDataVar;
    #endif
  }
  else
  {
    #if(COM_RX_IPDU_DEFERRED == STD_ON)
    /* @Trace: Com_SUD_API_00434 */
    /* @Trace: Com_SUD_API_00435 */
    for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
    LddSignalMemSize; LddBufferIndex++)
    {
      /* @Trace: Com_SUD_API_00436 */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaSignalValidCKBufferDE[LddBufferIndex] = COM_ZERO;
    }

    /* @Trace: Com_SUD_API_00437 */
    LpSignalDataVar = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                              &Com_GaaSignalValidCKBufferDE[COM_ZERO];
    LpSignalData = (P2CONST(uint8, AUTOMATIC, COM_CONST))LpSignalDataVar;
    #endif
  }
  
  /* @Trace: Com_SUD_API_00438 */
  /* Invoke read function to unpack signal data from I-PDU buffer */
  /* @Trace: SWS_Com_00352 */
  #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO)
  (void)Com_UnPackRequestRead(LpRxUnpack, LpSignalDataVar);
  #endif
  
  #if (COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
  /* @Trace: Com_SUD_API_01444 */
  Com_RxSigProc_FltrAndUpdrBuffer(LpRxSignal, LpSignalData,
    LpSigConfig, LpIdsMInform, LddRxSignalIndex);
  #else
  /* @Trace: Com_SUD_API_01445 */
  Com_RxSigProc_FltrAndUpdrBuffer(LpRxSignal, LpSignalData,
    LpSigConfig);
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_SigGrpFltr                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigProcessing                 **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :   Com_GaaSignalValidCKBufferIM **
**                                               Com_GaaSignalValidCKBufferDE **
**                        Function(s) invoked    :   Com_UnPackRequestRead()  **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_FILTER == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxGrpProc_SigGrpFltr(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpFltOutFlag,
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInform)
#else
FUNC(void, COM_CODE) Com_RxGrpProc_SigGrpFltr(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpFltOutFlag)
#endif
{
  /* @Trace: Com_SUD_API_00502 */
  /* Pointer to Rx Invalid or Filter Signal Group structure */
  P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST) LpRxInvOrFltSigGrp;
  /* Pointer to Rx Signal InGroup structure */
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) LpRxSigInGrp;
  /* Pointer to Rx Signal InGroup Invalid or Filter structure */
  P2CONST(Com_RxSigInGrpInvOrFlt, AUTOMATIC, COM_CONST) LpRxSigInGrpInvOrFlt;
  /* Pointer to Rx Unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  /* Local variable to store MemSize*/
  PduLengthType LddSignalMemSize;  
  /* Local variable to store no of signal or size */
  uint16 LusNoOfSigOrSize;
  /* Local variable to store Rx Signal InGroup index */
  Com_SignalIdType LddRxSigInGrpIndex;
  /* Local variable to store buffer index */
  PduLengthType LddBufferIndex;
  uint16 LddPeriod;

  /* Get below structure to fetch the number of Rx Group Signals, and the position
  of the first Rx Group Signal of this Signal Group */
  LpRxInvOrFltSigGrp = 
    &(Com_GaaRxInvOrFltSigGroup[LpRxSigGroup->usInvOrFltIndex]);

  /* Get the number of Rx Group Signals and the position of the first one 
  for this signal group */
  LusNoOfSigOrSize = LpRxInvOrFltSigGrp->usNoOfSignal;
  LddRxSigInGrpIndex = LpRxInvOrFltSigGrp->ddRxSigInGrpIndex;
  
  /* Get the first Rx Group Signal of this Signal Group */
  LpRxSigInGrp = &(Com_GaaRxSigInGrp[LddRxSigInGrpIndex]);

  /* Loop all of the Rx Group Signal of this Signal Group until filter out is occurred. */
  do
  {
    /* If pFilter is exists, filtering should be processed for this group signal */
    if(LpRxSigInGrp->pFilter != NULL_PTR)
    {
      /**************** Start of unpacking procedure  *******************/
      /* @Trace: Com_SUD_API_00503 */
      /* Get below structure to fetch the position of RxUnpack structure of this group signal */
      LpRxSigInGrpInvOrFlt = &(Com_GaaRxSigInGrpInvOrFlt[
        LpRxSigInGrp->usSigInGrpInvOrFltIndex]);
      /* Get RxUnpack structure of this group signal */
      LpRxUnpack = 
        &Com_GaaRxUnpack[LpRxSigInGrpInvOrFlt->ddRxUnpackIndex];

      /* Get the size of this group signal */
      if(LpRxUnpack->ucSignalType < COM_FOUR)
      {
        /* @Trace: Com_SUD_API_00504 */
        LddSignalMemSize = 
          (PduLengthType)Com_GaaSigMemSize[LpRxUnpack->ucSignalType];
      }
      else
      {
        /* @Trace: Com_SUD_API_00505 */
        LddSignalMemSize = LpRxUnpack->ddSignalSize;
      }

      /* If the I-PDU which contains this group signal is configured with 'IMMEDIATE', 
      Initialize Check Buffer for 'IMMEDIATE' I-PDU */
      if(COM_FALSE 
        == (LpRxIpdu->ucRxConfig & COM_RX_IPDU_DEFERRED_CONFIG_MASK))
      {            
        /* @Trace: Com_SUD_API_00506 */
        /* @Trace: Com_SUD_API_00507 */
        #if(COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) 
        for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
                                    LddSignalMemSize; LddBufferIndex++)
        {
          /* @Trace: Com_SUD_API_00508 */
          Com_GaaSignalValidCKBufferIM[LddBufferIndex] = COM_ZERO;
        }
        #endif
      }
      /* If the I-PDU which contains this group signal is configured with 'DEFFERED', 
      Initialize Check Buffer for 'DEFFERED' I-PDU */
      else
      {
        /* @Trace: Com_SUD_API_00509 */
        /* @Trace: Com_SUD_API_00510 */
        #if(COM_RX_IPDU_DEFERRED == STD_ON)
        for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
                                    LddSignalMemSize; LddBufferIndex++)
        {
          /* @Trace: Com_SUD_API_00511 */
          Com_GaaSignalValidCKBufferDE[LddBufferIndex] = COM_ZERO;
        }
        #endif
      }          

      /* Invoke read function to unpack this Rx Group Signal data from I-PDU buffer 
      to LpSignalData */
      /* @Trace: Com_SUD_API_00512 */
      #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
      (void)Com_UnPackRequestRead(LpRxUnpack, LpSignalData);
      #endif
      /**************** End of unpacking procedure **********************/
      /* Invoke the corresponding filtering function for this Rx Group Signal 
      and check the return value. (COM_TRUE: PASSED / COM_FALSE: FILTERED OUT) */
      LddPeriod = LpRxSigInGrp->usPeriod;
      /* @Trace: SWS_Com_00694, SWS_Com_00325, SWS_Com_00380, SWS_Com_00439*/
      if(COM_FALSE == (((P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST))
        (LpRxSigInGrp->pFilter))->pFilterFuncPtr)
        (LpRxSigInGrp->pFilter, LpSignalData, COM_ZERO, LddPeriod))
      {
        /* @Trace: Com_SUD_API_00513 */
        /* If this Rx Group Signal had been filtered out, Set FltOutFlag to 'COM_TRUE'. */
        *LpFltOutFlag = COM_TRUE;

        #if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
        {
          /* Check whether the filter out information has to be reported to IdsM 
          for this Rx Group Signal */
          if(LpRxSigInGrp->blIdsMReport != COM_FALSE)
          {
            /* Redmine #15051 (will be changed): Store IdsM Information to the Global variable 
            for this Rx Group Signal */
            if(LpIdsMInform->ucInvRangeSigListIndex < COM_FOUR)
            {
              /* @Trace: Com_SUD_API_00514 */
              LpIdsMInform->blIsInvRangeSigPdu = COM_TRUE;
              LpIdsMInform->aaInvRangeSigList[
                LpIdsMInform->ucInvRangeSigListIndex]
                  = (uint16)(LddRxSigInGrpIndex + COM_RX_SIGNAL_COUNT);
              LpIdsMInform->ucInvRangeSigListIndex ++;
            }
          }
        }
        #endif
      }
    }
      
    /* @Trace: Com_SUD_API_00515 */  
    /* Decrement the count of number of Rx Group Signals to be iterated */
    LusNoOfSigOrSize--;
    /* Increment the Index of Rx Group Signal by one and get the next one. */
    LddRxSigInGrpIndex++;
    LpRxSigInGrp = &(Com_GaaRxSigInGrp[LddRxSigInGrpIndex]);
  }while(LusNoOfSigOrSize != COM_ZERO);

  if(COM_TRUE == *LpFltOutFlag)
  {
    /* @Trace: Com_SUD_API_00516 */
    /* Reset signal group configuration to zero to abort this Signal Group.
    No further processing is performed. (Notification) */
    *LpSigGroupConfig = COM_ZERO;
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_SigGrpInv                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigGrpProcessing              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Com_GaaInvNotifCbkPositionMask **
**                                            Com_GaaInvNotifCbkFlag          **
**                                        Com_GaaMulticoreTriggerNotifyFlag   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_INVALID == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_SigGrpInv(
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig)
{
  /* @Trace: Com_SUD_API_00473 */
  #if(COM_RX_INVALIDNOTIFY == STD_ON)
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #endif

  #if((COM_RX_INVALIDNOTIFY == STD_ON) ||\
    (COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON))
  /* Pointer to Rx Invalid or Filter Signal Group structure */
  P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST) LpRxInvOrFltSigGrp;
  LpRxInvOrFltSigGrp = 
    &(Com_GaaRxInvOrFltSigGroup[LpRxSigGroup->usInvOrFltIndex]);
  #else
  COM_UNUSED_PTR(LpRxSigGroup);
  #endif

  #if(COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON)
  /* Pointer to Pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpPackSigGroup; 
  #endif

  #if(COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON)
  if((*LpSigGroupConfig & COM_RX_SIGGRP_INVREPLACE_CONFIG_MASK) ==
                                                            COM_FALSE)
  #endif
  {
    /* @Trace: Com_SUD_API_00474 */
    #if(COM_RX_INVALIDNOTIFY == STD_ON)
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    CoreMaskCheck = Com_GaaInvNotifCbkPositionMask[
      LpRxInvOrFltSigGrp->ddInvNotifCbkIndex];
    if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
    {
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
      /* @Trace: Com_SUD_API_00475 */
      /* Invoke Invalid Notification call-back function of this Signal Group */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not NULL. This is assured by generator" */
      (*(Com_GaaInvNotifCbk[LpRxInvOrFltSigGrp->ddInvNotifCbkIndex]))();
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)	
    }
    else
    {
      if(COM_TRUE == Com_GaaMulticoreDirectMode)
      {
        /* @Trace: Com_SUD_API_00476 */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaInvNotifCbkFlag[
          LpRxInvOrFltSigGrp->ddInvNotifCbkIndex] = CoreMaskCheck;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
      else
      {
        /* @Trace: Com_SUD_API_00477 */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaMainInvNotifCbkFlag[
          LpRxInvOrFltSigGrp->ddInvNotifCbkIndex] = CoreMaskCheck;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
      /* @Trace: Com_SUD_API_00478 */
      /* Get ptr of notify function */
      CoreIdCheck = CoreMaskCheck >> COM_ONE;
      /* Set Com_GaaMulticoreTriggerNotifyFlag */
      Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
    }   
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    #endif
    /* @Trace: Com_SUD_API_00479 */
    /* Reset signal group configuration to zero to abort this Signal Group.
    No further processing is performed. (Filtering, Notification) */
    *LpSigGroupConfig = COM_ZERO;
  }
  /* In case this Signal Group is configured for 'Invalid Replacement' */
  #if(COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON)
  else
  {
    /* @Trace: Com_SUD_API_00480 */
    /* Invoke write function to pack Init Value of this Signal Group into I-PDU buffer */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    LpPackSigGroup = LpRxSigGroup->pPackIPduBuffer;
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    (void)Com_PackSigGrp(LpPackSigGroup, LpRxInvOrFltSigGrp->pInitValue,
      LpPackSigGroup->pWrBuffer, LpRxSigGroup->pMaskingBuffer);   
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
  }
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_SglInGrpProc                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigGrpProcessing              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)    :Com_GaaSignalValidCKBufferIM **
**                                               Com_GaaSignalValidCKBufferDE **
**                        Function(s) invoked    :   Com_UnPackRequestRead()  **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_INVALID == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_SglInGrpProc(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) LpRxSigInGrp,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpInvalidFlag)
{
  /* @Trace: Com_SUD_API_00482 */
  /************** Start Unpacking Procedure  *******************/
  /* Pointer to Rx Signal InGroup Invalid or Filter structure */
  P2CONST(Com_RxSigInGrpInvOrFlt, AUTOMATIC, COM_CONST) LpRxSigInGrpInvOrFlt;
  /* Pointer to Rx Unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  /* Local variable to store MemSize*/
  PduLengthType LddSignalMemSize;
  /* Local variable to store buffer index */
  PduLengthType LddBufferIndex; 
  /* Get below structure to fetch the position of RxUnpack structure 
  and Invalid Value of this group signal */
  LpRxSigInGrpInvOrFlt = 
    &(Com_GaaRxSigInGrpInvOrFlt[LpRxSigInGrp->usSigInGrpInvOrFltIndex]);

  /* If Invalid Value is configured, Data Invalidation should be processed for this group signal */
  if (LpRxSigInGrpInvOrFlt->pInvalidValue != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_00483 */
    /* Get RxUnpack structure of this group signal */
    LpRxUnpack = 
      &Com_GaaRxUnpack[LpRxSigInGrpInvOrFlt->ddRxUnpackIndex];
    
    /* Get the size of this group signal */
    if(LpRxUnpack->ucSignalType < COM_FOUR)
    {
      /* @Trace: Com_SUD_API_00484 */
      LddSignalMemSize = 
        (PduLengthType)Com_GaaSigMemSize[LpRxUnpack->ucSignalType];
    }
    else
    {
      /* @Trace: Com_SUD_API_00485 */
      LddSignalMemSize = LpRxUnpack->ddSignalSize;
    }

    /* If the I-PDU which contains this group signal is configured with 'IMMEDIATE', 
    Initialize Check Buffer for 'IMMEDIATE' I-PDU */
    if(COM_FALSE 
      == (LpRxIpdu->ucRxConfig & COM_RX_IPDU_DEFERRED_CONFIG_MASK))
    {            
      #if(COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) 
      /* @Trace: Com_SUD_API_00486 */
      /* @Trace: Com_SUD_API_00487 */
      for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
                                  LddSignalMemSize; LddBufferIndex++)
      {
        /* @Trace: Com_SUD_API_00488 */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
        Com_GaaSignalValidCKBufferIM[LddBufferIndex] = COM_ZERO;
      }
      #endif
    }
    /* If the I-PDU which contains this group signal is configured with 'DEFFERED', 
    Initialize Check Buffer for 'DEFFERED' I-PDU */
    else
    {
      #if(COM_RX_IPDU_DEFERRED == STD_ON)
      /* @Trace: Com_SUD_API_00489 */
      /* @Trace: Com_SUD_API_00490 */
      for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
                                  LddSignalMemSize; LddBufferIndex++)
      {
        /* @Trace: Com_SUD_API_00491 */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
        Com_GaaSignalValidCKBufferDE[LddBufferIndex] = COM_ZERO;
      }
      #endif
    }          

    /* Invoke read function to unpack this Rx Group Signal data from I-PDU buffer 
    to LpSignalData */
    #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
    /* @Trace: Com_SUD_API_00492 */
    (void)Com_UnPackRequestRead(LpRxUnpack, LpSignalData);
    #endif
    /**************** End of unpacking procedure **********************/
    /* Invoke the corresponding invalid function for this Rx Group Signal and 
    * check the return value. (COM_TRUE: Inalid / COM_FALSE: Valid) */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if(((Com_GaaInvalidFuncPtr[LpRxUnpack->ucSignalType].
      pInvalidFuncPtr)(LpRxSigInGrpInvOrFlt->pInvalidValue, 
        LpSignalData,LpRxUnpack->ddSignalSize)) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00493 */
      /* #1329 : Remove invalid notification function call. */ 
      /* If this Rx Group Signal has an invalid data, Set Invalid Flag to 'COM_TRUE'. */
      *LpInvalidFlag = COM_TRUE;
    }
  }/* End of if (LpRxSigInGrpInvOrFlt->pInvalidValue != NULL_PTR) */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_SglGrpProc                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigGrpProcessing              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Com_GaaInvNotifCbkPositionMask **
**                                                 Com_GaaMulticoreDirectMode **
**                                                 Com_GaaInvNotifCbkFlag     **
**                        Function(s) invoked    :   Com_PackSigGrp()         **
**                                                   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_INVALID == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_SglGrpProc(
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig,
  P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST) LpRxInvOrFltSigGrp,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup)
{
  /* @Trace: Com_SUD_API_01447 */
  #if(COM_RX_INVALIDNOTIFY == STD_ON)
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #endif

  #if(COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON)
  /* Pointer to Pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpPackSigGroup;
  #endif
  /* Check whether this Signal Group is configured for 'Invalid Notification' */
  #if(COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON)
  if((*LpSigGroupConfig & COM_RX_SIGGRP_INVREPLACE_CONFIG_MASK) ==
                                                            COM_FALSE)
  #endif
  {
    #if(COM_RX_INVALIDNOTIFY == STD_ON)
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    /* @Trace: Com_SUD_API_00495 */
    CoreMaskCheck = Com_GaaInvNotifCbkPositionMask[
      LpRxInvOrFltSigGrp->ddInvNotifCbkIndex];
    if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
    {
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
      /* @Trace: Com_SUD_API_00496 */
      /* Invoke Invalid Notification call-back function of this Signal Group */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      (*(Com_GaaInvNotifCbk[
        LpRxInvOrFltSigGrp->ddInvNotifCbkIndex]))();
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)	
    }
    else
    {
      if(COM_TRUE == Com_GaaMulticoreDirectMode)
      {
        /* @Trace: Com_SUD_API_00497 */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaInvNotifCbkFlag[
          LpRxInvOrFltSigGrp->ddInvNotifCbkIndex] = CoreMaskCheck;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
      else
      {
        /* @Trace: Com_SUD_API_00498 */
        SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
        Com_GaaMainInvNotifCbkFlag[
          LpRxInvOrFltSigGrp->ddInvNotifCbkIndex] = CoreMaskCheck;
        SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      }
      /* @Trace: Com_SUD_API_00499 */
      /* Get ptr of notify function */
      CoreIdCheck = CoreMaskCheck >> COM_ONE;
      /* Set Com_GaaMulticoreTriggerNotifyFlag */
      Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
    }  
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    #endif
    /* Reset signal group configuration to zero to abort this Signal Group.
    No further processing is performed. (Filtering, Notification) */
    /* @Trace: Com_SUD_API_00500 */
    *LpSigGroupConfig = COM_ZERO;
  }
  /* In case this Signal Group is configured for 'Invalid Replacement' */
  #if(COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON)
  else
  {
    /* @Trace: Com_SUD_API_00501 */
    /* Invoke write function to pack Init Value of this Signal Group into I-PDU buffer */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    LpPackSigGroup = LpRxSigGroup->pPackIPduBuffer;
    (void)Com_PackSigGrp(LpPackSigGroup, 
      LpRxInvOrFltSigGrp->pInitValue, LpPackSigGroup->pWrBuffer, 
        LpRxSigGroup->pMaskingBuffer);   
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
  }
  #endif
  COM_UNUSED_PTR(LpRxSigGroup);
  COM_UNUSED_PTR(LpRxInvOrFltSigGrp);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_UpdrBitProc                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigGrpProcessing              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaRxDMTimer         **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP_UB == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_UpdrBitProc(
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigGroupConfig)
{
  /* Check whether signal group is received with an update bit */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null inside its bound. This is assured by generator" */
  if(COM_FALSE == (*(LpRxSigGroup->pUBit) & (LpRxSigGroup->ucUbitMask)))
  {
    /* @Trace: Com_SUD_API_00467 */
    /* Set signal group configuration to zero */
    *LpSigGroupConfig = COM_ZERO;
  }
  #if(COM_RX_SIGGROUP_UBDM == STD_ON)
  /* Check whether update bit with deadline monitoring is configured */
  else if((*LpSigGroupConfig & COM_RX_SIGGRP_UBDM_CONFIG_MASK)
                                                            != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00468 */
    #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_RX_DM_STS_PROTECTION_AREA();
    #endif
    /* Update Rx deadline monitoring status */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    Com_GaaRxDMTimer[LpRxSigGroup->ucRxUbDmIndex] = COM_INVALID_DM_TIMER;
    #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_RX_DM_STS_PROTECTION_AREA();
    #endif
  }
  else
  {
    /* Dummy loop to avoid QAC warning */
  }
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_DirectMainTransmit_TxStsUpd                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if(COM_TX_IPDU_DM == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_DirectMainTransmit_TxStsUpd(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu)
{
  /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
  if(((LusTxIpduStatusBit & COM_TX_DM_STATUS_MASK_1ST) != COM_FALSE) &&\
    ((Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].ulTxDmFirstTimeout) != 
      COM_ZERO))
  {
    /* @Trace: Com_SUD_API_00678 */
    /* Reset the deadline monitoring */
    Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] =
      Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].ulTxDmFirstTimeout + 
        (uint16)COM_ONE;
    SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
    Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &= COM_TX_DM_STATUS_MASK_1ST_NEG;
    SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
  }
  /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
  else if(((LusTxIpduStatusBit & COM_TX_DM_STATUS_MASK) != COM_FALSE) ||
    (((Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].ulTxDmFirstTimeout) == 
      COM_ZERO) &&
    ((LusTxIpduStatusBit & COM_TX_DM_STATUS_MASK_1ST) != COM_FALSE)))
  {
    /* @Trace: Com_SUD_API_00679 */
    /* Reset the deadline monitoring */
  /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
    Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] =
    Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].usDmTimeout + (uint16)COM_ONE;
    if((LusTxIpduStatusBit & COM_TX_DM_STATUS_MASK_1ST) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00680 */
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &= COM_TX_DM_STATUS_MASK_1ST_NEG;
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    }
    else
    {
      /* @Trace: Com_SUD_API_00681 */
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bound. This is assured by generator" */
      Com_GaaTxIpduStatusBit[LddNoOfTxIpdu] &= COM_TX_DM_STATUS_MASK_NEG;
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    }
  }
  else
  {
    /* Do nothing */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_TxUpdateDmTimers_DmErrNotif                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_TX_IPDU_DM == STD_ON) && (COM_SIG_ERR_CBK_NOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxUpdateDmTimers_DmErrNotif(
  PduIdType LddNoOfTxIpduDm)
{
  /* @Trace: Com_SUD_API_00404 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

  #if(COM_SIG_ERR_CBK_NOTIFY == STD_ON)
  /* Pointer to notification error call-back structure */
  P2CONST(Com_SigErrorCbk, AUTOMATIC, COM_CONST) LpSigErrorCbk;
  Com_ErrCbkCountType LddSigErrorCbkIndex;
  #endif
  /* Local variable to store notification error call-back */
  uint8 LucNoOfSigCallback;
  /* Get the number of error notification call-back functions for
  corresponding signals configured for notification */
  LucNoOfSigCallback =
              Com_GaaTxIpduDm[LddNoOfTxIpduDm].ucNoOfSigErrorCbk;
  /* Get the pointer to SigErrorCbk structure */
  LddSigErrorCbkIndex = 
    Com_GaaTxIpduDm[LddNoOfTxIpduDm].ddSigErrCbkIndex;
  LpSigErrorCbk = &Com_GaaSigErrorCbk[LddSigErrorCbkIndex];
  /* Loop for all the signals configured for notification (timeout) */
  do
  {
    /* @Trace: Com_SUD_API_00405 */
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    CoreMaskCheck = 
      Com_GaaSigErrorCbkPositionMask[LddSigErrorCbkIndex];
    if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
    {
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    /* @Trace: Com_SUD_API_00406 */
    /* Invoke the error notification call-back function */
    (LpSigErrorCbk->pSigErrorCbk)();
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    }
    else
    {
      /* @Trace: Com_SUD_API_00407 */
      SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
      Com_GaaSigErrorCbkFlag[LddSigErrorCbkIndex] = CoreMaskCheck; 
      SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      /* Get ptr of notify function */
      CoreIdCheck = CoreMaskCheck >> COM_ONE;
      /* Trigger Ioc write */
      (void)Com_GaaMulticoreNotifyList[CoreIdCheck](COM_TRUE);
    }    
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    /* @Trace: Com_SUD_API_00408 */
    /* Get the pointer to n SigErrorCbk structure */
    LddSigErrorCbkIndex++;
    LpSigErrorCbk = &Com_GaaSigErrorCbk[LddSigErrorCbkIndex];
    /* Decrement the count of number of signals configured for
    notification */
    LucNoOfSigCallback--;
  }while(LucNoOfSigCallback != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_MainFuncTx_PeriodicTmrUpdr                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_IPDU_PT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_PeriodicTmrUpdr(
  uint16 LusTxIpduStatusBit, 
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  if((LusTxIpduStatusBit & COM_TX_PT_STATUS_MASK) != COM_FALSE)
  {
    /* #3434 cyclic PDU handling in case of TMS switch */
    if(((LpTxMode->ucTxMode) <= COM_TX_MIXEDNTIMES_MODE)  &&
                        ((LpTxMode->ucTxMode) != COM_TX_NONE_MODE))
    {
      /* @Trace: Com_SUD_API_00347 */
      Com_GaaTxPeriodicTimer[LpTxIpdu->ddTxPeriodicTimerIndex] =
                              LpTxMode->usOffsetValue;
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


/*******************************************************************************
** Function Name        : Com_MainFuncTx_TxModeHndl                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_MainFunctionTx                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) &&\
    ((COM_TX_IPDU_REPETITION == STD_ON) ||\
    ((COM_TX_IPDU_DM == STD_ON) || \
      ((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
      (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)))))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MainFuncTx_TxModeHndl(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag,
  uint16 LusTxIpduStatusBit,
  PduIdType LddNoOfTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTimer)
{
  #if(COM_TX_IPDU_REPETITION == STD_ON)
  /* Check whether current Tx Mode is n-times (direct/mixed) */
  if ((LpTxMode->ucTxMode == COM_TX_DIRECTNTIMES_MODE) ||\
      (LpTxMode->ucTxMode == COM_TX_MIXEDNTIMES_MODE))
  {
    /* @Trace: Com_SUD_API_00354 */
    Com_NTimesTxModeHandle(LusTxIpduStatusBit, LpTxIpdu, LpTxMode,
      LddNoOfTxIpdu, LpTimer, LpTransmitFlag);
  }
  #else
  /* @Trace: Com_SUD_API_01461 */
  COM_UNUSED_PTR(LpTimer);
  #endif
  /* Check whether Transmit flag is true */
  /* polyspace:begin<MISRA-C3:2.1:Not a defect:Low>Not always a dead code. */
  if(COM_TRUE == (*LpTransmitFlag))
  /* polyspace:end<MISRA-C3:2.1:Not a defect:Low>Not always a dead code. */
  {  
    /* @Trace: Com_SUD_API_00355 */
    #if((COM_TX_IPDU_DM == STD_ON) || \
      ((COM_ENABLE_MDT_CYCLIC == STD_ON) && \
      (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)))
    Com_IPduTxDmDelayHandle(LpTxIpdu, LusTxIpduStatusBit, 
      LpTxIpdu->ucTxConfig, LpTxMode->ucTxMode, LddNoOfTxIpdu, LpTransmitFlag);
    #endif
  } /* Check whether Transmit flag is true */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_Transmit_IpduCntUpdr                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_Transmit                        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Transmit_IpduCntUpdr(PduIdType LddTxIpduId)
{
  /* @Trace: Com_SUD_API_01449 */
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  LpTxIpdu = &Com_GaaTxIpdu[LddTxIpduId];
  P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) LpTxIpduCounter;
  /* Check whether Tx I-PDU counter is configured */
  if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00366 */
    /* Get the pointer to Tx I-PDU counter structure */
    LpTxIpduCounter = &Com_GaaTxIpduCounter[LpTxIpdu->ddTxIpduCounter];
    Com_TxCounterUpdate(LpTxIpduCounter);
  } /* if(LpTxIpdu->pTxIpduCounter != NULL_PTR) */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_Transmit_IpduCalloutUpdr                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_Transmit                        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_TX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Transmit_IpduCalloutUpdr(
  PduIdType LddTxIpduId,
  P2VAR(Std_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpCalloutValue)
{
  /* @Trace: Com_SUD_API_00367 */
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr;
  LpTxIpdu = &Com_GaaTxIpdu[LddTxIpduId];
  /* Get the pointer to PduInfoPtr structure */
  LpPduInfoPtr = &Com_GaaTxPduInfoPtr[LddTxIpduId];
  /* Initialize return value to E_OK */
  *LpReturnValue = (uint8)E_OK;
  /* Initialize IPDU_CALLOUT return value to COM_TRUE */
  *LpCalloutValue = COM_TRUE;
  /* Check whether I-PDU callout is configured */
  if(LpTxIpdu->ddIpduCalloutIndex != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00368 */
    /* Exit Critical Area */
    SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
    *LpCalloutValue = Com_TxIpduCallout(LddTxIpduId, 
      (PduInfoType *) LpPduInfoPtr);
    /* Exit Critical Area */
    SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_RxGrpBuffUpdr                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSigGrpProcessing              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) &&\
  ((COM_RX_SIGGROUP_UB == STD_ON) || \
  (COM_RX_SIGGROUP_INVALID == STD_ON) || \
  (COM_RX_SIGGROUP_INVALIDREPLACE == STD_ON) || \
  (COM_RX_SIGGROUP_FILTER == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_RxGrpBuffUpdr(
  uint8 LucSigGroupConfig,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup)
{
  /* @Trace: Com_SUD_API_01451 */
  /* Pointer to Pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpPackSigGroup; 
  /* Pointer to I-PDU Buffer */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpIpduBuffer; 
  /* Get the pointer to I-PDU buffer */
  LpIpduBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST))
                                                LpRxSigGroup->pIpduBuffer;
  /* Check whether signal group is configured for timeout or invalid
  replacement */
  /* #7744, #7830 */
  /* Redmine #13931: Also Check whether signal group is configured for filtering */
  if(((LucSigGroupConfig & COM_RX_SIGGRP_UB_CONFIG_MASK) != COM_FALSE) ||\
  ((LucSigGroupConfig & COM_RX_SIGGRP_INVREPLACE_CONFIG_MASK)!=COM_FALSE)||\
  ((LucSigGroupConfig & COM_RX_SIGGRP_INVALID_CONFIG_MASK) != COM_FALSE) ||\
  ((LucSigGroupConfig & COM_RX_SIGGRP_FILTER_CONFIG_MASK) != COM_FALSE))
  {
    /* @Trace: Com_SUD_API_00517 */
    /* Invoke write function to pack I-PDU Buffer into Signal Group buffer */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    LpPackSigGroup = LpRxSigGroup->pPackSigGrpBuffer;
    (void)Com_PackSigGrp(LpPackSigGroup, LpIpduBuffer, 
      LpPackSigGroup->pWrBuffer, LpRxSigGroup->pMaskingBuffer);
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGrpProc_RxGrpNotif                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxSiggrpProcessing              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_RX_SIGGROUP == STD_ON) &&\
  (COM_RX_SIGGROUP_NOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGrpProc_RxGrpNotif(
  uint8 LucSigGroupConfig,
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup)
{
  /* @Trace: Com_SUD_API_01452 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

  if((LucSigGroupConfig & COM_RX_SIGGRP_NOTIF_CONFIG_MASK) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00518 */
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)
      CoreMaskCheck = 
        Com_GaaSigNotifCbkPositionMask[LpRxSigGroup->ddNotifCbkIndex];
      Com_GaaSigNotifCbkFlag[LpRxSigGroup->ddNotifCbkIndex] = 
        Com_GaaSigNotifCbkPositionMask[LpRxSigGroup->ddNotifCbkIndex];
      if(COM_ZERO != 
        (Com_GaaSigNotifCbkPositionMask[LpRxSigGroup->ddNotifCbkIndex] & CoreIdMask))
      {
      #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
        /* @Trace: Com_SUD_API_00519 */
        /* Invoke notification call-back function */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
        (Com_GaaSigNotifCbk[LpRxSigGroup->ddNotifCbkIndex].pSigNotifCbk)();
      #if (STD_ON == COM_MULTI_CORE_SUPPORT)	
      }
      else
      {
        if(COM_TRUE == Com_GaaMulticoreDirectMode)
        {
          /* @Trace: Com_SUD_API_00520 */
          SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
          Com_GaaSigNotifCbkFlag[
            LpRxSigGroup->ddNotifCbkIndex] = CoreMaskCheck;	  
          SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
        }
        else
        {
          /* @Trace: Com_SUD_API_00521 */
          SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
          Com_GaaMainSigNotifCbkFlag[
            LpRxSigGroup->ddNotifCbkIndex] = CoreMaskCheck;		  
          SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
        }
        /* @Trace: Com_SUD_API_00522 */
        /* Get ptr of notify function */
        CoreIdCheck = CoreMaskCheck >> COM_ONE;
        /* Set Com_GaaMulticoreTriggerNotifyFlag */
        Com_GaaMulticoreTriggerNotifyFlag[CoreIdCheck] = COM_TRUE;
      }   
      #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_SwIpduTxMode_PendingStatus                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SwitchIpduTxMode                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_PendingStatus(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit)
{
  /* @Trace: Com_SUD_API_01453 */
  /* Local status of the Ipdu */
  uint16 LusTxIpduStatusBit;

  LusTxIpduStatusBit = *LpTxIpduStatusBit;

  /* The mode is changing, so reset pending flag for MDT */
  /* Local variable to store Ipdu config */
  uint8 LucIpduConfig;
  /* Get the Ipdu configuration */
  LucIpduConfig = LpTxIpdu->ucTxConfig;

  /* Check whether minimum delay timer is configured */
  if((LucIpduConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00579 */
    /* Clear Tx Pending Status Mask */
    LusTxIpduStatusBit &= (uint16)(COM_TX_PENDING_STATUS_CLEAR_MASK);
    *LpTxIpduStatusBit = LusTxIpduStatusBit;
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


/*******************************************************************************
** Function Name        : Com_SwIpduTxMode_RepeatCount                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SwitchIpduTxMode                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) &&\
  (COM_TX_IPDU_REPETITION ==STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_RepeatCount(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode)
{
  /* @Trace: Com_SUD_API_01454 */
  /* Local status of the Ipdu */
  uint16 LusTxIpduStatusBit;

  LusTxIpduStatusBit = *LpTxIpduStatusBit;
  /* Check whether repetition counter is not zero */
  /* Prepare for  n-times Tx */
  if((LpTxMode->ucTxMode) == COM_TX_DIRECTNTIMES_MODE)
  {
    /* @Trace: Com_SUD_API_00584 */
    LusTxIpduStatusBit |= COM_TX_REPT_STATUS_MASK;
    *LpTxIpduStatusBit = LusTxIpduStatusBit;
    #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and has checked manual and it is not having any impact" */
    if(LpTxMode->ucDirectMainTransmit == COM_TX_DIRECT_TRANS)
    {
      /* @Trace: Com_SUD_API_00585 */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] = 
        LpTxMode->ucReptCount;
      if(LpTxMode->ucReptCount != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00586 */
        Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] 
            = LpTxMode->ucReptCount - COM_ONE;
      }
      else
      {
        /* @Trace: Com_SUD_API_00587 */
        Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] = COM_ZERO;
      }
    }
    #else
    COM_UNUSED_PTR(LpTxIpdu);
    #endif
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_SwIpduTxMode_MinDelayCheck                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SwitchIpduTxMode                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) &&\
  (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_MinDelayCheck(
  uint8 LucIpduConfig,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag)
{
  /* @Trace: Com_SUD_API_01455 */
  /* Local status of the Ipdu */
  uint16 LusTxIpduStatusBit = *LpTxIpduStatusBit;
  /* Check whether minimum delay timer is configured for I-PDU */
  if((LucIpduConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_FALSE)
  {
    /* Check whether minimum delay timer is set to zero */
    if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] != (uint16)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00588 */
      LusTxIpduStatusBit |= COM_TX_PENDING_STATUS_MASK;
      *LpTransmitFlag = COM_FALSE;
      #if (COM_TX_IPDU_DM == STD_ON)
      if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != 
      COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00589 */
        LusTxIpduStatusBit |= COM_TX_DM_STATUS_MASK_1ST;
      }
      #endif
    }
  } /* Check whether minimum delay timer is configured for I-PDU */
  *LpTxIpduStatusBit = LusTxIpduStatusBit;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_SwIpduTxMode_ResetTimer                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SwitchIpduTxMode                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SwIpduTxMode_ResetTimer(
  uint8 LucIpduConfig,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTxIpduStatusBit,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag)
{
  /* @Trace: Com_SUD_API_01456 */
  /* Local status of the Ipdu */
  uint16 LusTxIpduStatusBit = *LpTxIpduStatusBit;
  /* Resetting timers if the mode is PERIODIC or MIXED (COM244)*/
  /* polyspace:begin<MISRA-C3:2.1:Not a defect:Low>Not always a dead code. 
      ucTxMode is decided by the configuration of Com module */
  if((LpTxMode->ucTxMode <= COM_TX_MIXEDNTIMES_MODE)  &&
        (LpTxMode->ucTxMode != COM_TX_NONE_MODE))
  {
    /* @Trace: Com_SUD_API_00582 */
    /* Set status bit to reset periodic timer */
    /* Timer will then be reset in main function */
    LusTxIpduStatusBit |= COM_TX_PT_STATUS_MASK;
  }
  /* polyspace:end<MISRA-C3:2.1:Not a defect:Low>Not always a dead code. 
      ucTxMode is decided by the configuration of Com module */

  /* Check if the mode is MIXED or DIRECT */
  if(LpTxMode->ucTxMode > COM_TX_MIXEDNTIMES_MODE)
  {
    /* @Trace: Com_SUD_API_00583 */
    *LpTransmitFlag = COM_TRUE;
    #if(COM_TX_IPDU_REPETITION == STD_ON)
    Com_SwIpduTxMode_RepeatCount(LpTxIpdu, &LusTxIpduStatusBit, LpTxMode);
    #endif
    #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
    Com_SwIpduTxMode_MinDelayCheck(LucIpduConfig, &LusTxIpduStatusBit,
      LpTxIpdu, LpTransmitFlag);
    #endif
  } /* Check if the mode is MIXED or DIRECT */
  /* @Trace: Com_SUD_API_01458 */
  *LpTxIpduStatusBit = LusTxIpduStatusBit;
  COM_UNUSED_PTR(LpTxIpdu);
  COM_UNUSED(LucIpduConfig);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxGWSigProcessing_UBCheck                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxGWSigProcessing               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_RX_SIGNAL_GW == STD_ON) ||\
 (COM_RX_SIGINGROUP_GW == STD_ON) ||\
 (COM_RX_SIGNAL_GW_DES == STD_ON))
#if((COM_RX_SIGNAL_UB == STD_ON) && (COM_RX_SIGNAL_GW_UB == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGWSigProcessing_UBCheck(
  P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST) LpRxGWIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpProcessFlag)
{
  /* @Trace: Com_SUD_API_01459 */
  /* Pointer to Gate Way Rx Signal structure */
  P2CONST(Com_RxGWSignal, AUTOMATIC, COM_CONST) LpGWRxSignal;
  /* Get the pointer to n  Rx gateway signal structure */
  LpGWRxSignal = &Com_GaaRxGWSignal[LpRxGWIpdu->ddGWRxSigIndex];
  /* Set the process flag to true */
  *LpProcessFlag = COM_TRUE;
  /* Check whether update bit is configured signal */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  if((LpGWRxSignal->ucUbitMask) != COM_ZERO)
  {
    /* Check whether signal is received with an update bit */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    if(COM_FALSE == (*(LpGWRxSignal->pUBit) & (LpGWRxSignal->ucUbitMask)))
    {
      /* @Trace: Com_SUD_API_00527 */
      /* Set the process flag to false */
      *LpProcessFlag = COM_FALSE;
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


/*******************************************************************************
** Function Name        : Com_RxGWSigProcessing_SigGWBuff                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxGWSigProcessing               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if((COM_RX_SIGNAL_GW == STD_ON) ||\
 (COM_RX_SIGINGROUP_GW == STD_ON) ||\
 (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxGWSigProcessing_SigGWBuff(
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) LpSignalMemSize)
{
  /* @Trace: Com_SUD_API_01460 */
  /* buffer Loop Index */  
  PduLengthType LddBufferIndex;

  if(LpRxUnpack->ucSignalType < COM_FOUR)
  {
    /* @Trace: Com_SUD_API_00529 */
    *LpSignalMemSize = 
      (PduLengthType)Com_GaaSigMemSize[LpRxUnpack->ucSignalType];
  }
  else
  {
    /* @Trace: Com_SUD_API_00530 */
    *LpSignalMemSize = LpRxUnpack->ddSignalSize;
  }

  /* @Trace: Com_SUD_API_00531 */
  /* @Trace: Com_SUD_API_00532 */
  for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
  *LpSignalMemSize; LddBufferIndex++)
  {
    /* @Trace: Com_SUD_API_00533 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    Com_GaaSignalGWBuffer[LddBufferIndex] = COM_ZERO;
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
