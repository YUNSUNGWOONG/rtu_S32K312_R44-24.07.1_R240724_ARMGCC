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
**  SRC-MODULE: Com_Main.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of main functions.                   **
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
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-772                               **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

#ifndef COM_MAIN_H
#define COM_MAIN_H
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                      **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(COM_TX_SIGNAL == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignalService
  (Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


#if(COM_TX_SIGGROUP_TMS == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_TxSigGrpModeSelect
                       (P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp);

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_IPDU_DM == STD_ON) || \
   (COM_RX_SIGNAL_UBDM == STD_ON) || \
   (COM_RX_SIGGROUP_UBDM == STD_ON))                      
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_RxUpdateDmTimers (void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_DM == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxUpdateDmTimers (void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL_GW == STD_ON) ||\
 (COM_RX_SIGINGROUP_GW == STD_ON) ||\
 (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_RxGWSigProcessing
            (P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST) LpRxGWIpdu, uint8 
           lucGWStatus);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_Transmit
  (PduIdType LddTxIpduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGNAL_NOTIFY == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxSigConfirmation
                          (P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* Redmine #15053: parameter RxIpduId is removed because it is always unused */
#if(COM_RX_SIGNAL == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
extern FUNC(void, COM_CODE) Com_RxSigProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength,
                P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo);
#else
extern FUNC(void, COM_CODE) Com_RxSigProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* Redmine #15053: parameter RxIpduId is removed because it is always unused */
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
extern FUNC(void, COM_CODE) Com_RxSigGrpProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength,
                P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo);
#else
extern FUNC(void, COM_CODE) Com_RxSigGrpProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxClearUpdateBit(
                  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
                  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSourcePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_RxIpduCounterChk(PduIdType ComRxPduId, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_RxReplication(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UpdateShadowSignalService
          (Com_SignalIdType SignalId,
           P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ShadowSignalCopy
  (Com_SignalIdType SignalId, 
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

 #if((COM_TX_SIGNAL_UB == STD_ON) || \
     (COM_TX_SIGGROUP_UB == STD_ON) || \
     (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
     (COM_TX_IPDU_REPETITION == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"      
extern FUNC(boolean, COM_CODE) Com_TxIpduConfirmation(PduIdType LddComTxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_IPDU_CALLOUT == STD_ON) || \
    (COM_RX_REPLICATION == STD_ON)  || \
    (COM_RX_IPDU_COUNTER_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"    
extern FUNC(boolean, COM_CODE) Com_RxIpduValidate(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) 
                Com_DoubleBufferCall(P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST)
          LpRxTPIpdu, P2VAR(Com_RxPduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr,
                                 P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TpTxConfMDT
  (P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_REPETITION == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TPIpduRept(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST)LpTxMode, 
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TransIpduCounter
  (P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) 
  Com_SendSigTMS(P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST)
  LpTxSignal, P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_IPDU_DM == STD_ON) || \
   (COM_RX_SIGNAL_UBDM == STD_ON) || \
   (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_RxSigNotifyOrReplace(
                        P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
when Rx Timeout is occurred - Fixed by AUTRON START*/
#if((COM_RX_IPDU_DM == STD_ON) && (COM_RX_SIGNAL_FILTER == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_RxSigDMFilterReset(
                         P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif                         
/* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
when Rx Timeout is occurred - Fixed by AUTRON END*/

#if(COM_RX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern boolean Com_RxIpduCallout(PduIdType PduId, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern boolean Com_TxIpduCallout(PduIdType PduId, 
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern boolean Com_TxIpduTriggerCallout(PduIdType PduId, 
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackRequestWrite
    (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,         
    P2CONST (void, AUTOMATIC, COM_CONST) LpDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
    
#if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackRequestRead
  (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,         
  P2VAR(void, AUTOMATIC, COM_VAR) LpDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == COM_MULTI_CORE_SUPPORT)
	
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_MulticoreNotify(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_NotifyList_Init(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_MulticoreMainNotify(uint8 CoreId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_ClearTriggerNotifyFlag(boolean lblDirectMode);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_ProcessTriggerNotifyFlag(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_DirectMainTransmit(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  PduIdType LddNoOfTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_IndirectMainTransmit(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if(COM_TX_IPDU_REPETITION == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_NTimesTxModeHandle(
  uint16 LusTxIpduStatusBit,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  PduIdType LddNoOfTxIpdu,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpTimer,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_MinDelayTxHandle(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  PduIdType LddNoOfTxIpdu,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

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
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTransmitFlag);  
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#endif /* COM_MAIN_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
