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
**  SRC-MODULE: Com_TxSig.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of send, invalidate and update functions and their  **
**              functionality.                                                **
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
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.8.0   15-Feb-2023   PhucNHM     CP44-1599 CP44-1600                    **
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-771                               **
** 1.1.4     02-Jun-2022   DuyNHP2     R44-Redmine #27636 #28012              **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     25-Apr-2022   PhucNHM     R44-Redmine #25654                     **
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
#include "Com_Ram.h"          /* Com header file */
#include "Com_Main.h"     /* Com Main header file */
#include "Com_TxIpdu.h"   /* Com Tx I-PDU header file */
#include "Com_Pack.h"     /* Com Pack header file */
#include "Com_Invalid.h"  /* Com Invalid header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "Com_Error.h"    /* Com Error header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/

#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_DEV_ERROR_DETECT == STD_ON)
FUNC(uint8, COM_CODE) Com_SendSigGrpArr_InputValidate(
  Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if(COM_TX_DYN_SUPPORT == STD_ON)
#if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendDynSig_ProcSigOnChg(uint8 LucSigConfig, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr, 
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


#if(COM_TX_SIGGROUP == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrp_InputValidate(
  Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrp_UpdateTpStatus(
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrpArr_UpdtTpSts(
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendSigGrpArr_ProcSigOnChg(uint8 LucSigGrpProperty,
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) SignalGroupArrayPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if(COM_TX_DYN_SUPPORT == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)    
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendDynSig_UpdateTpStatus(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_DYN_SUPPORT == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendDynSig_InputValidate(Com_SignalIdType SignalId, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_UINT32(
  uint16 signalSize, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_SINT32(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_UINT16(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_SINT16(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_UINT8(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_SINT8(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendSigGrp_ProcSigOnChg(uint8 LucSigGrpProperty, 
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
FUNC(void, COM_CODE) Com_SendDynSig_ProcTxRequest(uint8 LucSigConfig,
  P2VAR(uint8, AUTOMATIC, COM_CONST) LpReturnValue,
  boolean LblReturnFlag, P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal);
#else
FUNC(void, COM_CODE) Com_SendDynSig_ProcTxRequest(uint8 LucSigConfig,
  P2VAR(uint8, AUTOMATIC, COM_CONST) LpReturnValue,
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_IPDU_REPETITION == STD_ON) && \
  (COM_MAINFUNC_BASED_TRANSMIT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SendSigSrv_ProcTxRept(uint8 LucSigProperty, 
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON) &&\
  (COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UpdtShdwSigSrv_VldtSignal(
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST(Com_TxSigInGrp, AUTOMATIC, COM_CONST) LpTxSigInGrp,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendSigSrv_ProcTrigOnChg(uint8 LucSigProperty, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack, 
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_SendSignal                                      **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : This function updates the signal object identified  **
**                        by SignalId with data referenced by SignalDataPtr.  **
**                        If the signal has the "triggered" transfer property,**
**                        the associated I-PDU will be transmitted immediately**
**                        after the update, except when the signal is packed  **
**                        into an I-PDU with "periodic" transmission mode; in **
**                        this case, no transmission is initiated by the call **
**                        to this service. If the signal has the "pending"    **
**                        transfer property, no transmission is caused by the **
**                        update. All the notification flags will be reset.   **
**                                                                            **
* Sync/Async           : Asynchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : SignalId, SignalDataPtr                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSignal            **
**                                                 Com_GaaTxPack              **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxTPStatus          **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaValidateValue       **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_SendSigTMS()           **
**                                                 Com_TxRequest()            **
**                                                 Com_ShadowBufferUpdate()   **
**                                                 pWrFuncPtr                 **
**                                                 pValidateDataPtr           **
*******************************************************************************/
/* @Trace: SWS_Com_00007 SWS_Com_00810  SWS_Com_00472 
SWS_Com_00221 SWS_Com_00580 SWS_Com_00330 SWS_Com_00767 SWS_Com_00734 
SWS_Com_00768 SWS_Com_00762 SWS_Com_00135 SWS_Com_00741 
SWS_Com_00769 SWS_Com_00676 SWS_Com_00677 SWS_Com_00678 
SWS_Com_00679 SWS_Com_00605 SWS_Com_00245 SWS_Com_00763 
SWS_Com_00813 SWS_Com_00032 SWS_Com_00799 SWS_Com_00238 
SWS_Com_00239 SWS_Com_00244 SWS_Com_00582 SWS_Com_00467 
SWS_Com_00279 SWS_Com_00305 SWS_Com_00334 SWS_Com_00698 
SWS_Com_00828 SWS_Com_00469 SWS_Com_00812 SWS_Com_00445 
SWS_Com_00138 SWS_Com_00059 SWS_Com_00061 SWS_Com_00062 
SWS_Com_00577 SWS_Com_00578 SWS_Com_00197 
SWS_Com_00624 SWS_Com_00625 SWS_Com_00843 */

#if((COM_TX_SIGNAL == STD_ON) || (COM_TX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02037, SRS_Com_02080, SRS_Com_02083, SRS_Com_02084*/
FUNC(uint8, COM_CODE) Com_SendSignal (Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01000 */
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Initialize return value to E_OK */
  LucReturnValue = (uint8)E_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_SENDSIGNAL);
  /* Check whether signal ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01687 */
  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG(COMSERVICEID_SENDSIGNAL);
  #else
  /* @Trace: Com_SUD_API_01688 */
  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG_PB(COMSERVICEID_SENDSIGNAL);
  #endif
  /* @Trace: Com_SUD_API_01689 */
  /* Check whether signal data pointer is equal to NULL */
  COM_DET_SIGNAL_DATA_PTR(COMSERVICEID_SENDSIGNAL);
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    #if((COM_TX_SIGGROUP == STD_ON)&&(COM_TX_SIGNAL == STD_ON))
    /* If the Id is actually a signal */
    if(SignalId < COM_TX_SIG_GRPSIG_BOUNDARY)
    #endif
    {
      /* @Trace: Com_SUD_API_01001 */
      #if (COM_TX_SIGNAL == STD_ON)
      LucReturnValue = Com_SendSignalService(SignalId, SignalDataPtr);
      #endif
    }
    #if((COM_TX_SIGGROUP == STD_ON)&&(COM_TX_SIGNAL == STD_ON))
    else
    #endif
    {
      /* @Trace: Com_SUD_API_01002 */
      #if(COM_TX_SIGGROUP == STD_ON)
      /* Internal function to copy the data into I-PDU buffer 
      and check conditions to initiate transmissions */
      Com_UpdateShadowSignalService(SignalId - COM_TX_SIG_GRPSIG_BOUNDARY, 
                                                                 SignalDataPtr);
      #endif
    }
  }
  /* @Trace: Com_SUD_API_01003 */
  /* Return value */
  return(LucReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Traceability END -- SRS: SWS_Com_00007 SWS_Com_00810  SWS_Com_00472 
SWS_Com_00221 SWS_Com_00580 SWS_Com_00330 SWS_Com_00767 SWS_Com_00734 
SWS_Com_00768 SWS_Com_00762 SWS_Com_00135 SWS_Com_00741 
SWS_Com_00769 SWS_Com_00676 SWS_Com_00677 SWS_Com_00678 
SWS_Com_00679 SWS_Com_00605 SWS_Com_00245 SWS_Com_00763 
SWS_Com_00813 SWS_Com_00032 SWS_Com_00799 SWS_Com_00238 
SWS_Com_00239 SWS_Com_00244 SWS_Com_00582 SWS_Com_00467 
SWS_Com_00279 SWS_Com_00305 SWS_Com_00334 SWS_Com_00698 
SWS_Com_00828 SWS_Com_00469 SWS_Com_00812 SWS_Com_00445 
SWS_Com_00138 SWS_Com_00059 SWS_Com_00061 SWS_Com_00062 
SWS_Com_00577 SWS_Com_00578 SWS_Com_00197 
SWS_Com_00624 SWS_Com_00625 SWS_Com_00843 */

/*******************************************************************************
** Function Name        : Com_SendDynSig_InputValidate                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendDynSignal                   **
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
#if(COM_TX_DYN_SUPPORT == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendDynSig_InputValidate(Com_SignalIdType SignalId, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01524 */
  uint8 LucReturnValue = E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_SENDDYNSIGNAL);
  /* Check whether signal ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01690 */
  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG(COMSERVICEID_SENDDYNSIGNAL);
  #else
  /* @Trace: Com_SUD_API_01691 */
  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG_PB(COMSERVICEID_SENDDYNSIGNAL);
  #endif
  /* @Trace: Com_SUD_API_01692 */
  /* Check whether signal data pointer is equal to NULL */
  COM_DET_SIGNAL_DATA_PTR(COMSERVICEID_SENDDYNSIGNAL);

  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendDynSig_UpdateTpStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendDynSignal                   **
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
#if(COM_TX_DYN_SUPPORT == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)    
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendDynSig_UpdateTpStatus(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01525 */
  /* #2142 : separate DYN PDU from TP */
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;

  uint8 LucReturnValue = E_OK;

  if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
  {
    /* @Trace: Com_SUD_API_01007 */
    /* Get the pointer to TP structure  */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    
    if(((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef]) & 
    (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_01008 */
      LucReturnValue = (uint8)COM_BUSY;
    }
  }

  /* @Trace: Com_SUD_API_01596 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendDynSig_ProcSigOnChg                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendDynSignal                   **
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
#if(COM_TX_DYN_SUPPORT == STD_ON)
#if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendDynSig_ProcSigOnChg(uint8 LucSigConfig, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr, 
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal)
{
  /* @Trace: Com_SUD_API_01526 */
  uint8 LucSigProperty;
  boolean LblReturnFlag = COM_TRUE;
  /* Mask the signal configuration to get signal property */
  LucSigProperty = LucSigConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK;
  if((LucSigProperty >= COM_TX_SIG_TRIGGERED_ON_CHANGE))
  {
    /* Check whether old value is equal to new value or not */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if(Com_GaaValidateValue[LpTxPack->ddSignalType].pValidateDataPtr 
      != NULL_PTR)
    {
      /* @Trace: Com_SUD_API_01012 */
      /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
      LblReturnFlag = 
        ((Com_GaaValidateValue[LpTxPack->ddSignalType].pValidateDataPtr)
        (SignalDataPtr,LpTxSignal->pSignalBuffer,
        LpTxPack->ddSigTypeOrSize));
      /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
    }
  }

  return LblReturnFlag;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendDynSig_ProcTxRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendDynSignal                   **
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
#if(COM_TX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
FUNC(void, COM_CODE) Com_SendDynSig_ProcTxRequest(uint8 LucSigConfig,
  P2VAR(uint8, AUTOMATIC, COM_CONST) LpReturnValue,
  boolean LblReturnFlag, P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal)
#else
FUNC(void, COM_CODE) Com_SendDynSig_ProcTxRequest(uint8 LucSigConfig,
  P2VAR(uint8, AUTOMATIC, COM_CONST) LpReturnValue,
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal)
#endif
{
  /* @Trace: Com_SUD_API_01527 */
  *LpReturnValue = COM_SERVICE_NOT_AVAILABLE;

  uint8 LucSigProperty;
  /* Check whether Tx I-PDU is enabled */
  if(Com_GaaTxIpduStatus[LpTxSignal->ddTxIpduIndex] != 
    (PduIdType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01013 */
    /* Set return value to E_OK */
    *LpReturnValue = (uint8)E_OK;
    /* Mask the signal configuration to get signal property */
    LucSigProperty = LucSigConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK;
    #if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
    if(LblReturnFlag == COM_TRUE)
    #endif
    {
      /* Check whether signal transfer property is triggered or
          transmission mode selection is configured */                
      if(LucSigProperty  > COM_TX_SIG_PENDING_PROPERTY)
      {
          #if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
            (COM_TX_IPDU_REPETITION == STD_ON) || \
            (COM_TX_IPDU_GW == STD_ON))
        /* @Trace: Com_SUD_API_01014 */
        *LpReturnValue = Com_TxRequest(LpTxSignal->ddTxIpduIndex, 
          LucSigConfig);
        #else
        /* @Trace: Com_SUD_API_01693 */
        *LpReturnValue = Com_TxRequest(LpTxSignal->ddTxIpduIndex);
        #endif
      } /* signal transfer property is triggered */
    } /* Check whether Tx I-PDU group is enabled */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SendDynSignal                                   **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : The service Com_SendDynSignal updates the signal    **
**                        object identified by SignalId with the signal       **
**                        referenced by the SignalDataPtr parameter.          **
**                                                                            **
* Sync/Async           : Asynchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : SignalId, SignalDataPtr, Length                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LucReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSignal            **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxTPStatus          **
**                                                 Com_GaaTxPack              **
**                                                 Com_GaaTxDynSigLength      **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaValidateValue       **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_TxRequest()            **
**                                                 pWrFuncPtr                 **
**                                                 pFilterFuncPtr             **
**                                                 pValidateDataPtr           **
*******************************************************************************/
#if(COM_TX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02095*/
FUNC(uint8, COM_CODE) Com_SendDynSignal(Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr, uint16 Length)
{
  /* @Trace: Com_SUD_API_01004 */
  /* Pointer to Tx signal structure */
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal;
  /* Pointer to Tx pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Local variable to store signal config */
  uint8 LucSigConfig;
  #if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
  boolean LblReturnFlag = COM_TRUE;
  #endif

  #if(COM_DEV_ERROR_DETECT == STD_OFF)
  /* @Trace: Com_SUD_API_01528 */
  /* Initialize return value to E_OK */
  LucReturnValue = (uint8)E_OK;
  #else
  /* @Trace: Com_SUD_API_01529 */
  LucReturnValue = Com_SendDynSig_InputValidate(SignalId, SignalDataPtr);
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_01005 */
    /* Get the pointer to Tx signal structure */
    LpTxSignal = &Com_GaaTxSignal[SignalId];
    /* Get the pointer to Tx IPdu structure */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    LpTxIpdu =  &Com_GaaTxIpdu[LpTxSignal->ddTxIpduIndex];
    /* Get the pointer toTxPack structure */
    LpTxPack = &(Com_GaaTxPack[LpTxSignal->ddTxPackIndex]);
    if(LpTxPack->ddSigTypeOrSize < (PduLengthType)Length)
    {
      /* @Trace: Com_SUD_API_01006 */
      LucReturnValue = (uint8)E_NOT_OK;
    }
    if(LucReturnValue != (uint8)E_NOT_OK)
    {
      /* #2142 : separate DYN PDU from TP */
      if(LpTxIpdu->ucIpduType == COM_DYN_IPDU)
      {
        /* @Trace: Com_SUD_API_01530 */
        #if(COM_TX_TP_SUPPORT == STD_ON)    
        LucReturnValue = Com_SendDynSig_UpdateTpStatus(LpTxIpdu);
        if(LucReturnValue != (uint8)COM_BUSY)        
        #endif      
        {
          /* @Trace: Com_SUD_API_01009 */
          /* Setting the length */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          Com_GaaTxDynSigLength[LpTxPack->ddTxIpduDynLegthRef] = 
          (PduLengthType)Length;
          /* @Trace: SWS_Com_00472, SWS_Com_00674, SWS_Com_00829 */
          /* Invoke write function to pack data referred by SignalDataPtr to I-PDU
          buffer */
          #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
          (void)Com_PackRequestWrite(LpTxPack, SignalDataPtr);
          /* Get the signal configuration into local variable */
          LucSigConfig = LpTxSignal->ucTxSigConfig;
          #endif

          #if(COM_TX_SIGNAL_UB == STD_ON)
          /* Check whether update bit is configured */
          if((LucSigConfig & COM_TX_SIGNAL_UB_CONFIG_MASK) != COM_FALSE)
          {
            /* @Trace: Com_SUD_API_01010 */
            /* Enter protection area */
            SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
            /* Set update bit to one */
            /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
            *(LpTxSignal->pUbit) |= LpTxSignal->ucUbitMask;
            /* Exit protection area */
            SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
          }
          #endif
          
          /* @Trace: Com_SUD_API_01011 */
          /* Set return value to COM_SERVICE_NOT_AVAILABLE */
          LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;

          #if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
          /* @Trace: Com_SUD_API_01531 */
          LblReturnFlag = Com_SendDynSig_ProcSigOnChg(LucSigConfig, LpTxPack, 
            SignalDataPtr, LpTxSignal);

          Com_SendDynSig_ProcTxRequest(LucSigConfig, &LucReturnValue,
            LblReturnFlag, LpTxSignal);
          #else
          /* @Trace: Com_SUD_API_01532 */
          Com_SendDynSig_ProcTxRequest(LucSigConfig, &LucReturnValue,
            LpTxSignal);
          #endif
        }
      }
      else
      {
        /* @Trace: Com_SUD_API_01015 */
        /* Set return value to "E_NOT_OK" */
        LucReturnValue = (uint8)E_NOT_OK;      
      }
    } /* Check whether any development error has occurred */
  }
  /* @Trace: Com_SUD_API_01016 */
  /* Return value */
  return(LucReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_InvalidateSignal                                **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : Sender side AUTOSAR Software Component indicates    **
**                        via the RTE to AUTOSAR COM that is not able to      **
**                        provide a valid value for the corresponding signal. **
**                        This function replaces the actual value with the    **
**                        invalid value for the signal.                       **
**                                                                            **
* Sync/Async           : Asynchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : SignalId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaTxSignal           **
**                        Function(s) invoked    :  Com_SendSignal()          **
**                                                  Det_ReportError()         **
*******************************************************************************/
#if((COM_TX_SIGNAL_INVALID == STD_ON) && (COM_TX_SIGNAL == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02077*/
FUNC(uint8, COM_CODE) Com_InvalidateSignal(Com_SignalIdType SignalId)
{
  /* @Trace: Com_SUD_API_01017 */
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Initializing return value to E_OK */
  LucReturnValue = (uint8)E_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_INVALIDATESIGNAL);
  /* Check whether signal ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01694 */
  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG(COMSERVICEID_INVALIDATESIGNAL);
  #else
  /* @Trace: Com_SUD_API_01695 */
  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG_PB(COMSERVICEID_INVALIDATESIGNAL);
  #endif
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)COM_ZERO)
  #endif
  {
    if(SignalId < COM_TX_SIG_GRPSIG_BOUNDARY)
    {
      /* @Trace: Com_SUD_API_01018 */
      /* Invoke Com_SendSignal() function with signal ID and invalid data
         value as input parameters */
      LucReturnValue = 
        Com_SendSignal(SignalId, Com_GaaTxSignal[SignalId].pInvalidData);
    }
    #if(COM_TX_SIGINGROUP_INVALID == STD_ON)
    else
    {
      /* @Trace: Com_SUD_API_01019 */
     Com_UpdateShadowSignalService(SignalId - COM_TX_SIG_GRPSIG_BOUNDARY, 
        Com_GaaTxSigInGrp[SignalId - COM_TX_SIG_GRPSIG_BOUNDARY].pInvalidData);
    }
    #endif
  }
  /* @Trace: Com_SUD_API_01020 */
  /* Return value */
  return(LucReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_InvalidateSignalGroup                           **
**                                                                            **
** Service ID           : 0x1B                                                **
**                                                                            **
** Description          : Sender side AUTOSAR Software Component indicates    **
**                        via the RTE to AUTOSAR COM that is not able to      **
**                        provide a valid value for the corresponding signal  **
**                        group. After Invalidating the actual signal group   **
**                        data a Com_SendSignalGroup is performed internally. **
**                                                                            **
* Sync/Async           : Asynchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal group.            **
**                        Reentrant for different signal groups.              **
**                                                                            **
** Input Parameters     : SignalGroupId                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)   : Com_GaaTxSigGroup            **
**                                               Com_GaaTxGroupSignal         **
**                        Function(s) invoked  : Com_InvalidateShadowSignal() **
**                                               Det_ReportError()            **
**                                               Com_SendSignalGroup()        **
*******************************************************************************/
#if(COM_TX_SIGINGROUP_INVALID == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02077*/
FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup
                                           (Com_SignalGroupIdType SignalGroupId)
{
  /* @Trace: Com_SUD_API_01021 */
  #if(COM_TX_TP_SUPPORT == STD_ON)
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu; 
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  #endif
  /* Pointer to Tx signal group structure */
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp;
  /* Pointer to Tx group signal structure */
  P2CONST(Com_TxGroupSignal, AUTOMATIC, COM_CONST) LpTxGroupSignal;
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Local variable to store group signal count */
  uint8 LucGroupSignalCount;

  Com_SignalIdType LddTxGroupSignalIndex;
  /* Initialize return value to COM_SERVICE_NOT_AVAILABLE */
  LucReturnValue = (uint8)E_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_INVALIDATESIGNALGROUP);
  /* Check whether signal group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01696 */
  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_INVALIDATESIGNALGROUP);
  #else
  /* @Trace: Com_SUD_API_01697 */
  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(
    COMSERVICEID_INVALIDATESIGNALGROUP);
  #endif
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_01022 */
    /* Get the pointer to Tx signal group structure */
    LpTxSigGrp = &Com_GaaTxSigGroup[SignalGroupId];
    
    #if(COM_TX_TP_SUPPORT == STD_ON)
   /* Get the pointer to Tx IPdu structure */
    LpTxIpdu =  &Com_GaaTxIpdu[LpTxSigGrp->ddTxIpduIndex];
    
    if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_01023 */
      /* Get the pointer to TP structure  */
      LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
      if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
      & (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01024 */
        LucReturnValue = (uint8)COM_BUSY;
      }
    }
    if(LucReturnValue == (uint8)E_OK)
    #endif
    {
      /* @Trace: Com_SUD_API_01025 */
      /* Get the number of Group Signals */
      LucGroupSignalCount = LpTxSigGrp->ucGroupSignalCount;
      /* Get the pointer to Group Signal */
      LddTxGroupSignalIndex = LpTxSigGrp->ddTxGrpSigIndex;
      LpTxGroupSignal =
                    &Com_GaaTxGroupSignal[LddTxGroupSignalIndex];
      while(LucGroupSignalCount != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01026 */
        /* Invoke Com_UpdateShadowSignalService() function with Signal Id as input
         * parameter */
        /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        Com_UpdateShadowSignalService(
          LpTxGroupSignal->ddSignalId - COM_TX_SIG_GRPSIG_BOUNDARY,
          Com_GaaTxSigInGrp[
            LpTxGroupSignal->ddSignalId - COM_TX_SIG_GRPSIG_BOUNDARY].
            pInvalidData);
        
        LddTxGroupSignalIndex++;
        LpTxGroupSignal =
          &Com_GaaTxGroupSignal[LddTxGroupSignalIndex];
        LucGroupSignalCount--;
      }
      /* @Trace: Com_SUD_API_01027 */
      /* Invoke Com_SendSignalGroup() function with SignalGroup ID*/
      LucReturnValue = Com_SendSignalGroup(SignalGroupId);
    }
  }
  /* @Trace: Com_SUD_API_01028 */
  return(LucReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SendSigGrp_InputValidate                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalGroup                 **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrp_InputValidate(
  Com_SignalGroupIdType SignalGroupId)
{
  /* @Trace: Com_SUD_API_01533 */
  uint8 LucReturnValue;

  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_SENDSIGNALGROUP);
  /* Check whether signal group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01698 */
  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_SENDSIGNALGROUP);
  #else
  /* @Trace: Com_SUD_API_01699 */
  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(COMSERVICEID_SENDSIGNALGROUP);
  #endif

  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendSigGrp_UpdateTpStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalGroup                 **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrp_UpdateTpStatus(
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp)
{  
  /* @Trace: Com_SUD_API_01534 */
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu; 
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;

  uint8 LucReturnValue;

  LucReturnValue = E_OK;
  /* Get the pointer to Tx IPdu structure */
  LpTxIpdu =  &Com_GaaTxIpdu[LpTxSigGrp->ddTxIpduIndex];
  
  if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
  {
    /* @Trace: Com_SUD_API_01033 */
    /* Get the pointer to TP structure  */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
    & (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_01034 */
      LucReturnValue = (uint8)COM_BUSY;
    }
  }

  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendSigGrp_ProcSigOnChg                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalGroup                 **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendSigGrp_ProcSigOnChg(uint8 LucSigGrpProperty, 
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack)
{
  /* @Trace: Com_SUD_API_01535 */
  boolean LblReturnFlag = COM_TRUE;

  if(LucSigGrpProperty >= COM_TX_SIG_TRIGGERED_ON_CHANGE)
  {
    #if(COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON)
    /* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
    if(LpTxSigGrp->pOnChangeStatus != NULL_PTR)
    {
      if(*(LpTxSigGrp->pOnChangeStatus) != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01036 */
        (void)Com_PackSigGrp(LpTxPack, 
          (P2CONST(void, AUTOMATIC, COM_CONST))
          LpTxSigGrp->pShadowBuffer, LpTxPack->pWrBuffer, 
          LpTxSigGrp->pMaskingBuffer);
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        *(LpTxSigGrp->pOnChangeStatus) = COM_ZERO;
      }
      else
      {
        /* @Trace: Com_SUD_API_01037 */
        LblReturnFlag = COM_FALSE;
      }
    }
    else
    /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
    #endif
    {
      /* @Trace: Com_SUD_API_01038 */
      LblReturnFlag = Com_PackAndValidateSigGrp(LpTxPack, 
        (P2CONST(void, AUTOMATIC, COM_CONST))
        LpTxSigGrp->pShadowBuffer, LpTxPack->pWrBuffer, 
        LpTxSigGrp->pMaskingBuffer);                    
    }
  }
  else
  {
    /* @Trace: Com_SUD_API_01039 */
    (void)Com_PackSigGrp(LpTxPack, (P2CONST(void, AUTOMATIC, COM_CONST))
      LpTxSigGrp->pShadowBuffer, LpTxPack->pWrBuffer, 
      LpTxSigGrp->pMaskingBuffer);
  }
  /* @Trace: Com_SUD_API_01587 */
  return LblReturnFlag;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendSignalGroup                                 **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : This function copies the contents of the associated **
**                        shadow buffer to the associated I-PDU.              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal group.            **
**                        Reentrant for different signal groups.              **
**                                                                            **
** Input Parameters     : SignalGroupId                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : All signals should be updated in the shadow buffer  **
**                        by the call of Com_UpdateShadowSignal().            **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSigGroup          **
**                                                 Com_GaaTxPack              **
**                                                 Com_GaaTxSigGrpModeSel     **
**                                                 Com_GaaFilterStatus        **
**                                                 Com_GaaTxIpduStatus        **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Det_ReportError()          **
**                                                 Com_PackAndValidateSigGrp()**
**                                                 Com_TxRequest()            **
*******************************************************************************/
#if(COM_TX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02041*/
FUNC(uint8, COM_CODE) Com_SendSignalGroup (Com_SignalGroupIdType SignalGroupId)
{
  /* @Trace: Com_SUD_API_01029 */
  /* Pointer to Tx pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
  /* Pointer to Tx signal Group structure */
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp;
  /* Local variable to store return value */
  uint8 LucReturnValue = (uint8)E_OK;
  /* Local variable to store signal group config */
  uint8 LucSigGrpConfig;
  /* Local variable to store signal group property */
  uint8 LucSigGrpProperty;
  #if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
  boolean LblReturnFlag = COM_TRUE;
  #endif
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_SendSigGrp_InputValidate(SignalGroupId);
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_01030 */
    /* Get the pointer to Tx signal group structure */
    LpTxSigGrp = &Com_GaaTxSigGroup[SignalGroupId];
    /* #7525 */
    #if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
      (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
    if(LpTxSigGrp->blArrayAccess == COM_TRUE)
    {
      /* @Trace: Com_SUD_API_01031 */
      /* AUTOSAR dose not define the behavior of illegally calling*/
      /* Discard the request */
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
    }  

    if(LucReturnValue == (uint8)E_OK)
    #endif
    {
      /* @Trace: Com_SUD_API_01032 */
      #if(COM_TX_TP_SUPPORT == STD_ON)
      LucReturnValue = Com_SendSigGrp_UpdateTpStatus(LpTxSigGrp);
     
      if(LucReturnValue == (uint8)E_OK)
      #endif
      {
        /* @Trace: Com_SUD_API_01035 */
        LpTxPack = &(Com_GaaTxPack[LpTxSigGrp->ddTxSigGrpPackIndex]);
        /* Get the signal group configuration */
        LucSigGrpConfig = LpTxSigGrp->ucTxSigGrpConfig;
        /* Extract the signal property - first 5 bits of signal configuration */
        LucSigGrpProperty = LucSigGrpConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK;
        /* Invoke Com_PackAndValidateSigGrp() function to pack and validate signal
        group data from shadow buffer to I-PDU buffer */
        /* #7709 start */
        #if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
        /* @Trace: Com_SUD_API_01536 */
        LblReturnFlag = Com_SendSigGrp_ProcSigOnChg(LucSigGrpProperty, LpTxSigGrp, LpTxPack);
        #else
        /* @Trace: Com_SUD_API_01700 */
        (void)Com_PackSigGrp(LpTxPack, (P2CONST(void, AUTOMATIC, COM_CONST))
          LpTxSigGrp->pShadowBuffer, LpTxPack->pWrBuffer, 
          LpTxSigGrp->pMaskingBuffer);
        /* #7709 end */  
        #endif
        #if(COM_TX_SIGGROUP_UB == STD_ON)
        /* Check whether update bit is configured */
        if((LucSigGrpConfig & COM_TX_SIGNAL_UB_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_01040 */
          /* Enter protection area */
          SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
          /* Set the update bit */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */         
          *(LpTxSigGrp->pUbit) |= LpTxSigGrp->ucUbitMask;
          /* Exit protection area */
          SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
        }
        #endif
        #if(COM_TX_SIGGROUP_TMS == STD_ON)
        /* @Trace: Com_SUD_API_01041 */
        LucSigGrpConfig = Com_TxSigGrpModeSelect(LpTxSigGrp);
        #endif
        /* Set return value to COM_SERVICE_NOT_AVAILABLE */
        LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
        /* Check whether I-PDU group is started */
        if(Com_GaaTxIpduStatus[LpTxSigGrp->ddTxIpduIndex] != 
          (PduIdType)COM_ZERO)
        {
          /* @Trace: Com_SUD_API_01042 */
          /* Set return value to E_OK */
          LucReturnValue = (uint8)E_OK;
          #if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
          if(LblReturnFlag == COM_TRUE)
          #endif
          {
            if((LucSigGrpProperty) > COM_TX_SIG_PENDING_PROPERTY)
            {
              #if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
                (COM_TX_IPDU_REPETITION == STD_ON) || \
                (COM_TX_IPDU_GW == STD_ON))
              /* @Trace: Com_SUD_API_01043 */
              (void)Com_TxRequest(LpTxSigGrp->ddTxIpduIndex, LucSigGrpConfig);
              
              #else
              /* @Trace: Com_SUD_API_01701 */
              (void)Com_TxRequest(LpTxSigGrp->ddTxIpduIndex);
              #endif
            } /* Check whether signal group property is triggered */
          } /* Check whether I-PDU group is started */
        }
      }
    }
  } /* DET Check */
  /* @Trace: Com_SUD_API_01044 */
  /* Return value */
  return(LucReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SendSigGrpArr_InputValidate                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalGroupArray            **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrpArr_InputValidate(
  Com_SignalGroupIdType SignalGroupId)
{
  /* @Trace: Com_SUD_API_01537 */
  uint8 LucReturnValue;
  /*  return value to COM_SERVICE_NOT_AVAILABLE */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_SENDSIGNALGROUPARRAY);
  /* Check whether signal group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01702 */
  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_SENDSIGNALGROUPARRAY);
  #else
  /* @Trace: Com_SUD_API_01703 */
  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(
    COMSERVICEID_SENDSIGNALGROUPARRAY);
  #endif
  /* @Trace: Com_SUD_API_01595 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendSigGrpArr_UpdtTpSts                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalGroupArray            **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigGrpArr_UpdtTpSts(
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp)
{
  /* @Trace: Com_SUD_API_01048 */
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu; 
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;

  uint8 LucReturnValue = E_OK;
  /* Get the pointer to Tx IPdu structure */
  LpTxIpdu =  &Com_GaaTxIpdu[LpTxSigGrp->ddTxIpduIndex];
  
  if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
  {
    /* @Trace: Com_SUD_API_01049 */
    /* Get the pointer to TP structure  */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
    & (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_01050 */
      LucReturnValue = (uint8)COM_BUSY;
    }
  }
  /* @Trace: Com_SUD_API_01594 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

/*******************************************************************************
** Function Name        : Com_SendSigGrpArr_ProcSigOnChg                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalGroupArray            **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendSigGrpArr_ProcSigOnChg(uint8 LucSigGrpProperty,
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) SignalGroupArrayPtr)
{
  /* @Trace: Com_SUD_API_01538 */
  boolean LblReturnFlag = COM_TRUE;

  if(LucSigGrpProperty >= COM_TX_SIG_TRIGGERED_ON_CHANGE)
  {
    /* @Trace: Com_SUD_API_01052 */
    LblReturnFlag = Com_PackAndValidateSigGrpArray(LpTxPack, 
      SignalGroupArrayPtr, LpTxPack->pWrBuffer);        
  }
  else
  {
    /* @Trace: Com_SUD_API_01053 */
    (void)Com_PackSigGrpArray(LpTxPack, SignalGroupArrayPtr, 
      LpTxPack->pWrBuffer);
  }
  /* @Trace: Com_SUD_API_01593 */
  return LblReturnFlag;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

/* #7525 #7709 start */
/*******************************************************************************
** Function Name        : Com_SendSignalGroupArray                            **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : This function copies the contents of the associated **
**                        shadow buffer to the associated I-PDU.              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal group.            **
**                        Reentrant for different signal groups.              **
**                                                                            **
** Input Parameters     : SignalGroupId                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SignalGroupArrayPtr                                 **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : All signals should be updated in the shadow buffer  **
**                        by the call of Com_UpdateShadowSignal().            **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSigGroup          **
**                                                 Com_GaaTxPack              **
**                                                 Com_GaaTxSigGrpModeSel     **
**                                                 Com_GaaFilterStatus        **
**                                                 Com_GaaTxIpduStatus        **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Det_ReportError()          **
**                                                 Com_PackAndValidateSigGrp()**
**                                                 Com_TxRequest()            **
*******************************************************************************/
#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02112, SRS_Com_02041, SRS_Com_00177*/
FUNC(uint8, COM_CODE) Com_SendSignalGroupArray (
  Com_SignalGroupIdType SignalGroupId, 
  P2CONST (uint8, AUTOMATIC, COM_CONST) SignalGroupArrayPtr )
{
  /* @Trace: Com_SUD_API_01045 */
  /* Pointer to Tx pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
   /* Pointer to Tx signal Group structure */
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp;
  /* Local variable to store return value */
  uint8 LucReturnValue = (uint8)E_OK;
  /* Local variable to store signal group config */
  uint8 LucSigGrpConfig;
  /* Local variable to store signal group property */
  uint8 LucSigGrpProperty;
  #if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
  boolean LblReturnFlag = COM_TRUE;
  #endif

  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_SendSigGrpArr_InputValidate(SignalGroupId);
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_01046 */
    /* Get the pointer to Tx signal group structure */
    LpTxSigGrp = &Com_GaaTxSigGroup[SignalGroupId];

    /* [SWS_Com_00843] */
    if(LpTxSigGrp->blArrayAccess != COM_TRUE)
    {
      /* @Trace: Com_SUD_API_01047 */
      /* AUTOSAR dose not define the behavior of illegally calling*/
      /* Discard the request */
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
    }
    else
    {      
      /* @Trace: Com_SUD_API_01048 */
      #if(COM_TX_TP_SUPPORT == STD_ON)
      LucReturnValue = Com_SendSigGrpArr_UpdtTpSts(LpTxSigGrp);
      if(LucReturnValue == (uint8)E_OK)
      #endif
      {
        /* @Trace: Com_SUD_API_01051 */
        LpTxPack = &(Com_GaaTxPack[LpTxSigGrp->ddTxSigGrpPackIndex]);
        /* Get the signal group configuration */
        LucSigGrpConfig = LpTxSigGrp->ucTxSigGrpConfig;
        /* Extract the signal property - first 5 bits of signal configuration */
        LucSigGrpProperty = LucSigGrpConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK;
        /* Invoke Com_PackAndValidateSigGrp() function to pack and validate signal
        group data from shadow buffer to I-PDU buffer */
        #if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
        /* @Trace: Com_SUD_API_01539 */
        LblReturnFlag = Com_SendSigGrpArr_ProcSigOnChg(LucSigGrpProperty, 
          LpTxPack, SignalGroupArrayPtr);
        #else
        /* @Trace: Com_SUD_API_01704 */
        (void)Com_PackSigGrpArray(LpTxPack, SignalGroupArrayPtr, 
          LpTxPack->pWrBuffer);
        #endif
        #if(COM_TX_SIGGROUP_UB == STD_ON)
        /* Check whether update bit is configured */
        if((LucSigGrpConfig & COM_TX_SIGNAL_UB_CONFIG_MASK) != COM_FALSE)
        {
          /* @Trace: Com_SUD_API_01054 */
          /* Enter protection area */
          SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
          /* Set the update bit */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
          *(LpTxSigGrp->pUbit) |= LpTxSigGrp->ucUbitMask;
          /* Exit protection area */
          SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
        }
        #endif
        
        /* @Trace: Com_SUD_API_01055 */
        #if(COM_TX_SIGGROUP_ARRAY_TMS == STD_ON)
        (void)Com_SigGrpArrayTMS(LpTxSigGrp);
        #endif
        #if(COM_TX_SIGGROUP_TMS == STD_ON)
        LucSigGrpConfig = Com_TxSigGrpModeSelect(LpTxSigGrp);
        #endif
        /* Set return value to COM_SERVICE_NOT_AVAILABLE */
        LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
        /* Check whether I-PDU group is started */
        if(Com_GaaTxIpduStatus[LpTxSigGrp->ddTxIpduIndex] != 
          (PduIdType)COM_ZERO)
        {
          /* @Trace: Com_SUD_API_01056 */
          /* Set return value to E_OK */
          LucReturnValue = (uint8)E_OK;
          #if(COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON)
          if(LblReturnFlag == COM_TRUE)
          #endif
          {
            if((LucSigGrpProperty) > COM_TX_SIG_PENDING_PROPERTY)
            {
              #if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
                (COM_TX_IPDU_REPETITION == STD_ON) || \
                (COM_TX_IPDU_GW == STD_ON))
              /* @Trace: Com_SUD_API_01057 */
              (void)Com_TxRequest(LpTxSigGrp->ddTxIpduIndex, LucSigGrpConfig);
              
              #else
              /* @Trace: Com_SUD_API_01705 */
              (void)Com_TxRequest(LpTxSigGrp->ddTxIpduIndex);
              #endif
            } /* Check whether signal group property is triggered */
          } /* Check whether I-PDU group is started */
        }
      } /* DET Check */
    }
  }
  /* @Trace: Com_SUD_API_01058 */
  /* Return value */
  return(LucReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/* #7525 #7709 end */

/*******************************************************************************
** Function Name        : Com_UpdtShdwSigSrv_VldtSignal                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_UpdateShadowSignalService       **
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
#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON) &&\
  (COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UpdtShdwSigSrv_VldtSignal(
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST(Com_TxSigInGrp, AUTOMATIC, COM_CONST) LpTxSigInGrp,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01540 */
  #if(COM_TX_IPDU_REPETITION == STD_ON) 
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpduRep;
  /* Local variable to store signal group config */
  uint8 LucSigGrpConfig;
  #endif  
  boolean LblReturnFlag;

  if(LpTxSigGrp->pOnChangeStatus != NULL_PTR)
  {
    if(COM_TX_SIG_TRIGGERED_ON_CHANGE == 
      (LpTxSigInGrp->ucTxSigConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK))
    {
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      if(Com_GaaValidateValue[LpTxPack->ddSignalType].pValidateDataPtr != 
        NULL_PTR)
      {
        /* @Trace: Com_SUD_API_01063 */
        /* Check whether old value is equal to new value or not */
        /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
        LblReturnFlag =
          ((Com_GaaValidateValue[LpTxPack->ddSignalType].pValidateDataPtr)
          (SignalDataPtr,LpTxSigInGrp->pSignalBuffer,
          LpTxPack->ddSigTypeOrSize));
        /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
        if(LblReturnFlag == COM_TRUE)
        {
          /* @Trace: Com_SUD_API_01064 */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
          *(LpTxSigGrp->pOnChangeStatus) = COM_ONE;
        }
      }
    }
  }
  /* @Trace: Com_SUD_API_01065 */
  #if(COM_TX_IPDU_REPETITION == STD_ON) 
  LpTxIpdu =  &Com_GaaTxIpdu[LpTxSigGrp->ddTxIpduIndex];
  LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
  if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
  {
    /* @Trace: Com_SUD_API_01066 */
    LucSigGrpConfig = LpTxSigGrp->ucTxSigGrpConfig;
    LpTxIpduRep = &Com_GaaTxIpdu[LpTxSigGrp->ddTxIpduIndex];
    LpTxMode = &Com_GaaTxMode[LpTxIpduRep->ddTrueTxModeIndex];
    if ((LucSigGrpConfig >= COM_TX_SIG_TRIGGERED) &&
        (LpTxMode->ucTxMode >= COM_TX_MIXED_MODE))
    {
      if (Com_GaaReptStatus[LpTxSigGrp->ddTxIpduIndex] == 0)
      {
        /* @Trace: Com_SUD_API_01067 */
        Com_GaaReptStatus[LpTxSigGrp->ddTxIpduIndex] = 1;
      }
      else
      {
        /*Do nothing*/
      }
    }
  }
  #endif /* (COM_TX_IPDU_REPETITION == STD_ON) */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_UpdateShadowSignalService                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                        Updates shadow buffers                              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : SignalId, SignalDataPtr                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaTxSigInGrp         **
**                                                  Com_GaaTxPack             **
**                        Function(s) invoked    :  pWrFuncPtr                **
**                                                  pFilterFuncPtr            **
*******************************************************************************/
#if(COM_TX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UpdateShadowSignalService(Com_SignalIdType SignalId,
           P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01059 */
  /* #7525 #7705 start */
  /* Pointer to Tx signal In Group structure */
  P2CONST(Com_TxSigInGrp, AUTOMATIC, COM_CONST) LpTxSigInGrp;
  #if(((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
    (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON)) ||\
    ((COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON) &&\
    (COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON)))
  /* Pointer to Tx signal Group structure */
  P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp;
  #endif
  /* Pointer to Tx Pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) && \
    (COM_TX_SIGINGRP_FILTER_SUPPORT == STD_ON))
  /* Pointer to filter structure */
  P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST) LpFilter;
  uint16 lddPeriod;
  #endif
  #if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
  /* Variable for Com_TxSigValidationCheck result */
  uint8 LucTxSigCheck;
  /* Initialize LucTxSigCheck with E_OK */
  LucTxSigCheck = E_OK;
  #endif
  /* Get the pointer to Tx signal in group structure */
  LpTxSigInGrp = &Com_GaaTxSigInGrp[SignalId];
  /* Get the pointer to TxPack structure */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  LpTxPack = &(Com_GaaTxPack[LpTxSigInGrp->ddTxPackIndex]);
  /* Invoke the write function to pack signal data into shadow buffer */

  #if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
  /* Fix the input value(#644) - 14.03.03 by Chan Kim START */ 
  /*
  adding range check for HMC specification - by Chan Kim 2013.09.11-START
  */
  if(COM_TRUE != Com_TxSigValidationCheck(LpTxSigInGrp->usBitSize, 
    LpTxSigInGrp->ucType, SignalDataPtr))
  {
    /* @Trace: Com_SUD_API_01060 */
    LucTxSigCheck = E_NOT_OK;
  }
  /*
  adding range check for HMC specification - by Chan Kim 2013.09.11-END
  */
  /* Fix the input value(#644) - 14.03.03 by Chan Kim END */ 
  if (LucTxSigCheck == E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_01061 */
    #if(((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
      (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON)) ||\
      ((COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON) &&\
      (COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON)))
    LpTxSigGrp = &Com_GaaTxSigGroup[LpTxSigInGrp->ddSigGrpIndex];
    #endif

    #if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
      (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
    /* AUTOSAR dose not define the behavior of illegally calling*/
    /* Discard the request */
    if(LpTxSigGrp->blArrayAccess != COM_TRUE)
    #endif
    {  
      /* @Trace: Com_SUD_API_01062 */
      /* @Trace: SWS_Com_00472, SWS_Com_00674, SWS_Com_00829 */
      #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
      (void)Com_PackRequestWrite(LpTxPack, SignalDataPtr);
      #endif      
      #if((COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON) &&\
        (COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON))
      Com_UpdtShdwSigSrv_VldtSignal(LpTxSigGrp, LpTxPack, 
        LpTxSigInGrp, SignalDataPtr);
      #endif  /* ((COM_TX_SIGGROUP_TRIGONCHANGE == STD_ON) && (COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON))*/
      #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
      /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
      /* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
      /* Check whether filter is configured */
      #if(COM_TX_SIGINGRP_FILTER_SUPPORT == STD_ON)
      if(LpTxSigInGrp->pFilter != NULL_PTR)
      {
        /* @Trace: Com_SUD_API_01068 */
        lddPeriod = LpTxSigInGrp->usPeriod;
        LpFilter = (P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST))
                                                    (LpTxSigInGrp->pFilter);                      
        if((LpFilter->ucFltrStsMask) != COM_ZERO)
        {
          /* Invoke filter function and check the return value */
          /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter,
          when Rx Timeout is occurred - Fixed by AUTRON START*/      
          /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
          if((LpFilter->pFilterFuncPtr)(
            LpFilter, SignalDataPtr, COM_ZERO, lddPeriod) == COM_TRUE)
          /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
          /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter,
          when Rx Timeout is occurred - Fixed by AUTRON END*/      
          {
            /* @Trace: Com_SUD_API_01069 */
            SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
            /* Set the filter status to true */
            /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
            *(LpFilter->pFilterStatus) |= (LpFilter->ucFltrStsMask);
            SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
          }
          else
          {
            /* @Trace: Com_SUD_API_01070 */
            SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
            /* Set the filter status of the group signal to false by masking it
             * with the filter status mask value.*/
            /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
            *(LpFilter->pFilterStatus) &= (uint8)(~(LpFilter->ucFltrStsMask));
            SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
          }
        }
      } /* Check whether filter is configured */
      #endif
      /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
      /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
      #endif /*  #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON) */
    }  
    /* #7525 #7705 end */
  }
  #if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
  else
  {
    /* Do nothing */
  }
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SendSigSrv_ProcTrigOnChg                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalService               **
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
#if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_SendSigSrv_ProcTrigOnChg(uint8 LucSigProperty, 
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack, 
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01541 */
  boolean LblReturnFlag = COM_TRUE;

  if((LucSigProperty >= COM_TX_SIG_TRIGGERED_ON_CHANGE))
  {
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if(Com_GaaValidateValue[LpTxPack->ddSignalType].pValidateDataPtr != 
    NULL_PTR)
    {
      /* @Trace: Com_SUD_API_01080 */
      /* Check whether old value is equal to new value or not */
      /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
      LblReturnFlag = 
        ((Com_GaaValidateValue[LpTxPack->ddSignalType].pValidateDataPtr)
          (SignalDataPtr,LpTxSignal->pSignalBuffer,
          LpTxPack->ddSigTypeOrSize));
      /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
    }
  }
  /* @Trace: Com_SUD_API_01592 */
  return LblReturnFlag;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SendSigSrv_ProcTxRept                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_SendSignalService               **
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
#if((COM_TX_IPDU_REPETITION == STD_ON) && \
  (COM_MAINFUNC_BASED_TRANSMIT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SendSigSrv_ProcTxRept(uint8 LucSigProperty, 
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal)
{
  /* @Trace: Com_SUD_API_01081 */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpduRep;
  /* Pointer to Tx Mode structure */
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  LpTxIpduRep = &Com_GaaTxIpdu[LpTxSignal->ddTxIpduIndex];
  LpTxMode = &Com_GaaTxMode[LpTxIpduRep->ddTrueTxModeIndex];
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and could be changed in another configuration" */
  if(LpTxMode->ucDirectMainTransmit == COM_TX_MAINFUNC_TRANS)
  {
    if ((LucSigProperty == COM_TX_SIG_TRIGGERED) &&
      (LpTxMode->ucTxMode >= COM_TX_MIXED_MODE))
    {
      if (Com_GaaReptStatus[LpTxSignal->ddTxIpduIndex] == 0)
      {
        /* @Trace: Com_SUD_API_01082 */
        Com_GaaReptStatus[LpTxSignal->ddTxIpduIndex] = 1;
      }
      else
      {
        /*Do nothing*/
      }
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_SendSignalService                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
* Sync/Async           : Asynchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : SignalId, SignalDataPtr                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSignal            **
**                                                 Com_GaaTxPack              **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxTPStatus          **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaValidateValue       **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_SendSigTMS()           **
**                                                 Com_TxRequest()            **
**                                                 pWrFuncPtr                 **
**                                                 pValidateDataPtr           **
*******************************************************************************/
#if (COM_TX_SIGNAL == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSignalService (Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01071 */
  /* Pointer to Tx signal structure */
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) LpTxSignal;
  /* Pointer to Tx pack structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
  #if(COM_TX_TP_SUPPORT == STD_ON)
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  #endif 
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Local variable to store signal config */
  uint8 LucSigConfig;
  /* Local variable to store signal property */
  uint8 LucSigProperty;
  #if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
  boolean LblReturnFlag = COM_TRUE;
  #endif

  #if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
  /* Variable for Com_TxSigValidationCheck result */
  uint8 LucTxSigCheck;
  /* Initialize LucTxSigCheck with E_OK */
  LucTxSigCheck = E_OK;
  #endif
  /* Get the pointer to Tx signal structure */
  LpTxSignal = &Com_GaaTxSignal[SignalId];

  #if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
  /*
  adding range check for HMC specification - by Chan Kim 2013.09.11-START
  */
  if(COM_TRUE != Com_TxSigValidationCheck(LpTxSignal->usBitSize, 
      LpTxSignal->ucType, SignalDataPtr))
  {
    /* @Trace: Com_SUD_API_01072 */
    LucTxSigCheck = E_NOT_OK;
    LucReturnValue = E_NOT_OK;
  }
  /*
  adding range check for HMC specification - by Chan Kim 2013.09.11-END
  */
  if (LucTxSigCheck == E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_01073 */
    /* Get the pointer toTxPack structure */
    LpTxPack = &(Com_GaaTxPack[LpTxSignal->ddTxPackIndex]);
    #if(COM_TX_TP_SUPPORT == STD_ON)
    LucReturnValue = (uint8)E_OK;
    /* Get the pointer to Tx IPdu structure */
    LpTxIpdu =  &Com_GaaTxIpdu[LpTxSignal->ddTxIpduIndex];
    
    if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_01074 */
      /* Get the pointer to TP structure  */
      LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
      if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
      & (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01075 */
        LucReturnValue = (uint8)COM_BUSY;
      }
    }
    /* Req 863*/
    #if(COM_DEV_ERROR_DETECT == STD_ON)
    if(LucReturnValue != (uint8)E_OK)
    {
      /* @Trace: Com_SUD_API_01076 */
      COM_DET_TP_SKIP_TRANSMISSION(COMSERVICEID_SENDSIGNAL);
    }
    else
    #endif
    #endif
    {
      /* @Trace: Com_SUD_API_01077 */
      #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
      /* @Trace: SWS_Com_00472, SWS_Com_00674, SWS_Com_00829 */
      /* Invoke write function to pack data referred by SignalDataPtr to I-PDU
      buffer */
      (void)Com_PackRequestWrite(LpTxPack, SignalDataPtr);
      #endif
      #if((COM_TX_SIGNAL_UB == STD_ON) ||\
         (COM_TX_IPDU_TMS_SIG_BASED == STD_OFF))
      /* Get the signal configuration into local variable */
      LucSigConfig = LpTxSignal->ucTxSigConfig;
      #endif
      #if(COM_TX_SIGNAL_UB == STD_ON)
      /* Check whether update bit is configured */
      if((LucSigConfig & COM_TX_SIGNAL_UB_CONFIG_MASK) != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_01078 */
        /* Enter protection area */
        SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
        /* Set update bit to one */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        *(LpTxSignal->pUbit) |= LpTxSignal->ucUbitMask;
        /* Exit protection area */
        SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
      }
      #endif
      /* @Trace: Com_SUD_API_01079 */
      /* @Trace: SWS_Com_00602, SWS_Com_00325 */
      #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
      LucSigConfig = Com_SendSigTMS(LpTxSignal, SignalDataPtr);
      #endif
      /* Set return value to COM_SERVICE_NOT_AVAILABLE */
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;

      /* Mask the signal configuration to get signal property */
      LucSigProperty = LucSigConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK;
      
      #if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
      LblReturnFlag = Com_SendSigSrv_ProcTrigOnChg(LucSigProperty, LpTxPack, 
        LpTxSignal, SignalDataPtr);
      #endif
        
      #if((COM_TX_IPDU_REPETITION == STD_ON) && \
        (COM_MAINFUNC_BASED_TRANSMIT == STD_ON))
      Com_SendSigSrv_ProcTxRept(LucSigProperty, LpTxSignal);
      #endif
      /* Check whether Tx I-PDU is enabled */
      if(Com_GaaTxIpduStatus[LpTxSignal->ddTxIpduIndex] != (PduIdType)COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01083 */
        /* Set return value to E_OK */
        LucReturnValue = (uint8)E_OK;

        #if(COM_TX_SIGNAL_TRIGONCHANGE == STD_ON)
        if(LblReturnFlag == COM_TRUE)
        #endif
        {
          /* Check whether signal transfer property is triggered or
            transmission mode selection is configured */           
          if(LucSigProperty  > COM_TX_SIG_PENDING_PROPERTY)
          {  
            #if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
              (COM_TX_IPDU_REPETITION == STD_ON) || \
              (COM_TX_IPDU_GW == STD_ON))
            /* @Trace: Com_SUD_API_01084 */
            LucReturnValue = Com_TxRequest(LpTxSignal->ddTxIpduIndex, 
              LucSigConfig);
            #else
            /* @Trace: Com_SUD_API_01706 */
            LucReturnValue = Com_TxRequest(LpTxSignal->ddTxIpduIndex);
            #endif
          } /* signal transfer property is triggered */
        } /* Check whether Tx I-PDU group is enabled */
      } /* Check whether any development error has occurred */
    }    
  }
  #if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
  else
  {
    /* Do nothing */
  }
  #endif
  /* @Trace: Com_SUD_API_01085 */
  /* Return value */
  return(LucReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigGrpModeSelect                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function determines the transmission mode.     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal group.            **
**                        Reentrant for different signal groups.              **
**                                                                            **
** Input Parameters     : LpTxSigGrp                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : All signals should be updated in the shadow buffer  **
**                        by the call of Com_UpdateShadowSignal().            **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSigGrpModeSel     **
**                                                 Com_GaaFilterStatus        **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if(COM_TX_SIGGROUP_TMS == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_TxSigGrpModeSelect
                       (P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp)
{
  /* @Trace: Com_SUD_API_01086 */
  P2CONST(Com_TxSigGrpModeSel, AUTOMATIC, COM_CONST) LpTxSigGrpModeSel;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpFilterStatus;
  uint8 LucFilterStatusCount;
  uint8 LucSigGrpConfig;
  uint8 LucFilterStatusIndex;
  boolean LblResult;
  LucSigGrpConfig = LpTxSigGrp->ucTxSigGrpConfig ;
  /* Check whether update bit is configured */
  if((LucSigGrpConfig & COM_TX_SIG_TMS_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_01087 */
    LblResult = COM_FALSE;
    /* Get the pointer to Tx Mode Select structure*/
    LpTxSigGrpModeSel =
                &Com_GaaTxSigGrpModeSel[LpTxSigGrp->ucTxSigGrpModeSelIndex];
    /* Get the pointer to filter status */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    LucFilterStatusIndex = LpTxSigGrpModeSel->ucFilterStatusIndex;
    LpFilterStatus =
               &Com_GaaFilterStatus[LucFilterStatusIndex];
    /* Get the counter */
    LucFilterStatusCount = LpTxSigGrpModeSel->ucNoOfFilterStsByte;
    /* Loop for all the signals configured for filtering */
    do
    {
      /* @Trace: Com_SUD_API_01088 */
      /* Decrement the filter status count */
      LucFilterStatusCount--;
      /* Check whether filter status is set to true */
   
      if(*LpFilterStatus != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01089 */
        LblResult = COM_TRUE;
        /* Set filter result to true */
        LucSigGrpConfig |= COM_TX_SIG_TMS_STATUS_MASK;
        /* Enter protection area */
        SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
        
        Com_GaaFilterStatus[LpTxSigGrpModeSel->ucIpduFilterStsIndex] |=
        LpTxSigGrpModeSel->ucFilterStatusMask;
        /* Exit protection area */
        SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
        /* Set filter status count to zero to break the loop */
        LucFilterStatusCount = COM_ZERO;
      }

      /* Increment the filter status pointer to point to n filter status
         area */
      /* @Trace: Com_SUD_API_01090 */
      LucFilterStatusIndex++;
      LpFilterStatus =
               &Com_GaaFilterStatus[LucFilterStatusIndex];
    }while(LucFilterStatusCount != COM_ZERO);
  
    if(LblResult != COM_TRUE)
    {
      /* @Trace: Com_SUD_API_01091 */
      /* Enter protection area */
      SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
      /* Update the filter Staatus */
      Com_GaaFilterStatus[LpTxSigGrpModeSel->ucIpduFilterStsIndex] &=
                            (uint8)~(LpTxSigGrpModeSel->ucFilterStatusMask);
      /* Exit protection area */
      SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
    }
  }
  /* @Trace: Com_SUD_API_01092 */
  return(LucSigGrpConfig);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : Com_TxSigValidationCheck                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function check the signal data is valid or not.  **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non-Reentrant for the same signal group.              **
**                      Reentrant for different signal groups.                **
**                                                                            **
** Input Parameters   : signalSize, signalType, SignalDataPtr                 **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : All signals should be updated in the shadow buffer    **
**                      by the call of Com_UpdateShadowSignal().              **
**                                                                            **
** Remarks            : Global Variable(s)    : None                          **
**                      Function(s) invoked   : None                          **
*******************************************************************************/
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_TxSigValidationCheck
(uint16 signalSize, uint8 signalType, 
P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01093 */
  boolean LblSigTypeBooleanVar = COM_ZERO;
  
  boolean LblTypeValueValid = COM_TRUE;

  if(SignalDataPtr != NULL_PTR)
  {
    switch(signalType)
    {
      case COM_SIG_TYPE_BOOLEAN:
        /* @Trace: Com_SUD_API_01094 */
        LblSigTypeBooleanVar = *(const boolean*)(SignalDataPtr);
        if((LblSigTypeBooleanVar >> COM_ONE) > COM_ZERO)
        {
          /* @Trace: Com_SUD_API_01095 */
          LblTypeValueValid = COM_FALSE;
        }
        /* @Trace: Com_SUD_API_01096 */
        break;

      case COM_SIG_TYPE_UINT8:
        /* @Trace: Com_SUD_API_01097 */
        Com_TxSigValidationCheck_UINT8(signalSize, 
          SignalDataPtr, &LblTypeValueValid);
        break;

      case COM_SIG_TYPE_SINT8:
        /* @Trace: Com_SUD_API_01101 */
        Com_TxSigValidationCheck_SINT8(signalSize, 
          SignalDataPtr, &LblTypeValueValid);
        break;

      case COM_SIG_TYPE_UINT16:
        /* @Trace: Com_SUD_API_01547 */
        Com_TxSigValidationCheck_UINT16(signalSize,
          SignalDataPtr, &LblTypeValueValid);
        break;

      case COM_SIG_TYPE_SINT16:
        /* @Trace: Com_SUD_API_01110 */
        Com_TxSigValidationCheck_SINT16(signalSize,
          SignalDataPtr, &LblTypeValueValid);
        break;

      case COM_SIG_TYPE_UINT32:
        /* @Trace: Com_SUD_API_01545 */
        Com_TxSigValidationCheck_UINT32(signalSize, 
          SignalDataPtr, &LblTypeValueValid);
        break;

      case COM_SIG_TYPE_SINT32:
        /* @Trace: Com_SUD_API_01119 */
        Com_TxSigValidationCheck_SINT32(signalSize, 
          SignalDataPtr, &LblTypeValueValid);
        break;

      case COM_SIG_TYPE_FLOAT32:
        /* @Trace: Com_SUD_API_01124 */    
        break;
      
      case COM_SIG_TYPE_UINT8_N:    
        /* @Trace: Com_SUD_API_01125 */
        break;
      
      case COM_SIG_TYPE_FLOAT64:  
        /* @Trace: Com_SUD_API_01126 */  
        break;
      
      case COM_SIG_TYPE_UINT8_DYN:  
        /* @Trace: Com_SUD_API_01127 */  
        break;    

      default:
        /* @Trace: Com_SUD_API_01128 */
        LblTypeValueValid = COM_FALSE;    
        break;
    }
  }
  else
  {
    /* @Trace: Com_SUD_API_01129 */
    LblTypeValueValid = COM_FALSE;    
  }
  /* @Trace: Com_SUD_API_01130 */
  return LblTypeValueValid;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"  
#endif

/*******************************************************************************
** Function Name        : Com_TxSigGrpModeSelect                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function determines the transmission mode.     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal group.            **
**                        Reentrant for different signal groups.              **
**                                                                            **
** Input Parameters     : LpTxSigGrp                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : All signals should be updated in the shadow buffer  **
**                        by the call of Com_UpdateShadowSignal().            **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxSigGrpModeSel     **
**                                                 Com_GaaFilterStatus        **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if(COM_TX_SIGGROUP_ARRAY_TMS == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_SigGrpArrayTMS
(P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp)
{
  /* @Trace: Com_SUD_API_01131 */
  /* Pointer to filter structure */
  P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST) LpFilter;
  /* Pointer to Rx Unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  /* Pointer to Signal Data structure */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignalData = NULL_PTR;
  /* Pointer to Rx Invalid or Filter Signal Group structure */
  P2CONST(Com_TxSigInGrp, AUTOMATIC, COM_CONST) LpTxSigInGrp;
  /* Local variable to store no of signal or size */
  uint16 LusNoOfSigOrSize;
  /* Local variable to store buffer index */
  PduLengthType LddBufferIndex; 
  /* Local variable to store Rx Signal InGroup index */
  Com_SignalIdType LddTxSigInGrpIndex;
  /* Time periodic filter */
  uint16 lddPeriod;
  /* Local variable to store MemSize*/
  PduLengthType LddSignalMemSize; 
  LusNoOfSigOrSize = LpTxSigGrp->ucGroupSignalCount;
  LddTxSigInGrpIndex = LpTxSigGrp->ddTxGrpSigIndex;
  LpTxSigInGrp = &Com_GaaTxSigInGrp[LddTxSigInGrpIndex];
  do
  {
    /* If pFilter is exists, filtering should be processed for this group signal */
    if(LpTxSigInGrp->pFilter != NULL_PTR)
    {
      /* @Trace: Com_SUD_API_01132 */
      /**************** Start of unpacking procedure  *******************/
      /* Get below structure to fetch the position of RxUnpack structure of this group signal */
      
      /* Get RxUnpack structure of this group signal */
      LpRxUnpack = &Com_GaaRxUnpack[LpTxSigInGrp->ddTxUnpackIndex];
      /* Get the size of this group signal */
      if(LpRxUnpack->ucSignalType < COM_FOUR)
      {
        /* @Trace: Com_SUD_API_01133 */
        LddSignalMemSize = 
          (PduLengthType)Com_GaaSigMemSize[LpRxUnpack->ucSignalType];
      }
      else
      {
        /* @Trace: Com_SUD_API_01134 */
        LddSignalMemSize = LpRxUnpack->ddSignalSize;
      }
      /* @Trace: Com_SUD_API_01135 */
      /* @Trace: Com_SUD_API_01136 */
      for(LddBufferIndex = (PduLengthType)COM_ZERO; LddBufferIndex < 
      LddSignalMemSize; LddBufferIndex++)
      {
        /* @Trace: Com_SUD_API_01137 */
        Com_GaaSignalGrpSigArray[LddBufferIndex] = COM_ZERO;
      }
      /* @Trace: Com_SUD_API_01138 */
      LpSignalData = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                            &Com_GaaSignalGrpSigArray[COM_ZERO];
        /*Invoke read function to unpack this Rx Group Signal data from I-PDU buffer 
      to LpSignalData */
      #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
      (void)Com_UnPackRequestRead(LpRxUnpack, LpSignalData);
      #endif
      LpFilter = (P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST))
                                                  (LpTxSigInGrp->pFilter);
      if((LpFilter->ucFltrStsMask) != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01139 */
        lddPeriod = LpTxSigInGrp->usPeriod;
        /* Invoke filter function and check the return value */
        /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter,
        when Rx Timeout is occurred - Fixed by AUTRON START*/      
        /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
        if((LpFilter->pFilterFuncPtr)(
            LpFilter, LpSignalData, COM_ZERO, lddPeriod) == COM_TRUE)
        /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
        /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter,
        when Rx Timeout is occurred - Fixed by AUTRON END*/      
        {
          /* @Trace: Com_SUD_API_01140 */
          SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
          /* Set the filter status to true */
          *(LpFilter->pFilterStatus) |= (LpFilter->ucFltrStsMask);
          SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
        }
        else
        {
          /* @Trace: Com_SUD_API_01141 */
          SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
          /* Set the filter status of the group signal to false by masking it
              with the filter status mask value.*/
          *(LpFilter->pFilterStatus) &= (uint8)(~(LpFilter->ucFltrStsMask));
          SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
        }
      }
    } /* Check whether filter is configured */
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
    
    /* @Trace: Com_SUD_API_01142 */
    LusNoOfSigOrSize--;
    /* Increment the Index of Rx Group Signal by one and get the next one. */
    LddTxSigInGrpIndex++;
    LpTxSigInGrp = &(Com_GaaTxSigInGrp[LddTxSigInGrpIndex]);
  }while(LusNoOfSigOrSize != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigValidationCheck_UINT32                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxSigValidationCheck int32      **
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
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_UINT32(
  uint16 signalSize, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid)
{
  /* @Trace: Com_SUD_API_01543 */
  uint32 LulSigTypeUint32Var = (uint32)COM_ZERO;
  LulSigTypeUint32Var = *(const uint32*)(SignalDataPtr);   
  if(signalSize > (uint16)COM_THIRTY_TWO)
  {
    /* @Trace: Com_SUD_API_01116 */
    *LpTypeValueValid = COM_FALSE;
  }
  else
  {    
    if((signalSize != (uint16)COM_THIRTY_TWO) 
      && ((LulSigTypeUint32Var >> signalSize) > COM_ZERO))
    {
      /* @Trace: Com_SUD_API_01117 */
      *LpTypeValueValid = COM_FALSE;
    }    
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigValidationCheck_SINT32                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxSigValidationCheck int32      **
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
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_SINT32(
  uint16 signalSize, 
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid)
{
  /* @Trace: Com_SUD_API_01543 */
  uint32 LulSigTypeUint32Var = (uint32)COM_ZERO;
  sint32 LslSigTypeSint32Var = (sint32)COM_ZERO;  
  sint32 LscSigTypeSint32VarUP = (sint32)COM_ONE;
  sint32 LscSigTypeSint32VarLO = (sint32)COM_ZERO;
  LslSigTypeSint32Var = *(const sint32*)(SignalDataPtr);  
  if((signalSize > (uint16)COM_THIRTY_TWO) || 
    (signalSize == (uint16)COM_ZERO))
  {
    /* @Trace: Com_SUD_API_01120 */
    *LpTypeValueValid = COM_FALSE;
  }
  else
  {
    if(signalSize != (uint16)COM_THIRTY_TWO) 
    {
      /* @Trace: Com_SUD_API_01121 */
      LulSigTypeUint32Var = ((uint32)((uint32)COM_MACRO_ONE << 
        (signalSize - (uint32)COM_MACRO_ONE))) & COM_SINT32_MAX_MASK;
      LscSigTypeSint32VarLO = (sint32)LulSigTypeUint32Var;
      LscSigTypeSint32VarLO = (sint32)(COM_ZERO) - LscSigTypeSint32VarLO;
      LscSigTypeSint32VarUP = (sint32)
        ((sint32)LulSigTypeUint32Var - (sint32)(COM_ONE));
      if((LslSigTypeSint32Var > LscSigTypeSint32VarUP) 
        || (LslSigTypeSint32Var < LscSigTypeSint32VarLO))
      {
        /* @Trace: Com_SUD_API_01122 */
        *LpTypeValueValid = COM_FALSE;
      }      
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigValidationCheck_INT16                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxSigValidationCheck int16      **
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
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_UINT16(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid)
{  
  /* @Trace: Com_SUD_API_01546 */
  uint16 LusSigTypeUint16Var = (uint16)COM_ZERO;
  LusSigTypeUint16Var = *(const uint16*)(SignalDataPtr);
  if(signalSize > (uint16)COM_SIXTEEN)
  {
    /* @Trace: Com_SUD_API_01107 */
    *LpTypeValueValid = COM_FALSE;
  }
  else
  {    
    if((signalSize != (uint16)COM_SIXTEEN) 
      && ((LusSigTypeUint16Var >> signalSize) > COM_ZERO))
    {
      /* @Trace: Com_SUD_API_01108 */
      *LpTypeValueValid = COM_FALSE;
    }   
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigValidationCheck_SINT16                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxSigValidationCheck int16      **
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
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_SINT16(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid)
{  
  /* @Trace: Com_SUD_API_01546 */
  uint16 LusSigTypeUint16Var = (uint16)COM_ZERO;
  sint16 LssSigTypeSint16Var = (sint16)COM_ZERO;
  sint16 LscSigTypeSint16VarUP = (sint16)COM_ONE;
  sint16 LscSigTypeSint16VarLO = (sint16)COM_ZERO;
  LssSigTypeSint16Var = *(const sint16*)(SignalDataPtr);
  if((signalSize > (uint16)COM_SIXTEEN) || 
    (signalSize == (uint16)COM_ZERO))
  {
    /* @Trace: Com_SUD_API_01111 */
    *LpTypeValueValid = COM_FALSE;
  }
  else
  {
    if(signalSize != (uint16)COM_SIXTEEN) 
    {
      /* @Trace: Com_SUD_API_01112 */
      LusSigTypeUint16Var = ((uint16)((uint16)COM_MACRO_ONE << 
        (signalSize - (uint16)COM_MACRO_ONE))) & COM_SINT16_MAX_MASK;
      LscSigTypeSint16VarLO = -((sint16)(LusSigTypeUint16Var));
      LscSigTypeSint16VarUP = (sint16)
        ((sint16)LusSigTypeUint16Var - (sint16)COM_MACRO_ONE);
      if((LssSigTypeSint16Var > LscSigTypeSint16VarUP) 
        || (LssSigTypeSint16Var < LscSigTypeSint16VarLO))
      {
        /* @Trace: Com_SUD_API_01113 */
        *LpTypeValueValid = COM_FALSE;
      }    
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigValidationCheck_UINT8                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxSigValidationCheck int8       **
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
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_UINT8(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid)
{
  /* @Trace: Com_SUD_API_01548 */
  uint8 LucSigTypeUint8Var = COM_ZERO;
  LucSigTypeUint8Var = *(const uint8*)(SignalDataPtr);
  if(signalSize > (uint16)COM_EIGHT)
  {
    /* @Trace: Com_SUD_API_01098 */
    *LpTypeValueValid = COM_FALSE;
  }
  else
  {
    if((signalSize != (uint16)COM_EIGHT) 
      && ((LucSigTypeUint8Var >> signalSize) > COM_ZERO))
    {
      /* @Trace: Com_SUD_API_01099 */
      *LpTypeValueValid = COM_FALSE;
    }    
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxSigValidationCheck_SINT8                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxSigValidationCheck int8       **
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
#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxSigValidationCheck_SINT8(
  uint16 signalSize,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpTypeValueValid)
{
  /* @Trace: Com_SUD_API_01549 */
  uint8 LucSigTypeUint8Var = COM_ZERO;
  sint8 LscSigTypeSint8Var = (sint8)COM_ZERO;
  sint8 LscSigTypeSint8VarUP = (sint8)COM_ONE;
  sint8 LscSigTypeSint8VarLO = (sint8)COM_ZERO;

  LscSigTypeSint8Var = *(const sint8*)(SignalDataPtr);    
  if((signalSize > (uint16)COM_EIGHT) || (signalSize == (uint16)COM_ZERO))
  {
    /* @Trace: Com_SUD_API_01102 */
    *LpTypeValueValid = COM_FALSE;
  }
  else
  {
    if(signalSize != (uint16)COM_EIGHT) 
    {
      /* @Trace: Com_SUD_API_01103 */
      LucSigTypeUint8Var = 
        (COM_ONE << (signalSize-COM_ONE)) & COM_SINT8_MAX_MASK;
      LscSigTypeSint8VarLO = -((sint8)(LucSigTypeUint8Var));
      LscSigTypeSint8VarUP = (sint8)
        ((sint8)LucSigTypeUint8Var - (sint8)COM_MACRO_ONE);
      if((LscSigTypeSint8Var > LscSigTypeSint8VarUP) 
        || (LscSigTypeSint8Var < LscSigTypeSint8VarLO))
      {
        /* @Trace: Com_SUD_API_01104 */
        *LpTypeValueValid = COM_FALSE;
      }
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
