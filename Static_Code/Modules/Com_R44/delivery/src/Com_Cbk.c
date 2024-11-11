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
**  SRC-MODULE: Com_Cbk.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
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
** 1.1.10.0  30-May-2023   PhucNHM     CP44-2038                              **
** 1.1.9.0   10-Apr-2023   PhucNHM     CP44-267 CP44-1806                     **
** 1.1.8.0   15-Feb-2023   PhucNHM     CP44-1599 CP44-1600                    **
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #28007                     **
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
#include "Com_Main.h"     /* Com Main header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "Com_Error.h"    /* Com Error header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif
#if(COM_IDSM_SUPPORT == STD_ON)
#include "IdsM_Cbk.h"     /* IdsM Cbk header file */
#endif
#include "string.h"       /* memcpy() */
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_TrigTx_InputValidate(PduIdType ComTxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr, 
  P2VAR(Std_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_IPDU == STD_ON)
#if((COM_TX_SIGNAL_UB == STD_ON) || \
  (COM_TX_SIGGROUP_UB == STD_ON) || \
  (COM_TX_IPDU_COUNTER_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TrigTx_ProcUpdBitAndIpduCnt(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSourcePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_IPDU == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_RxInd_InputValidate(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
  (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxInd_RxProcessing(PduIdType ComRxPduId, 
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, 
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo);
#else
FUNC(void, COM_CODE) Com_RxInd_RxProcessing(PduIdType ComRxPduId, 
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_TxConfirmation                                  **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : This function called by the lower layer after the   **
**                        PDU has been transmitted on the network. This       **
**                        function generates the notification for the         **
**                        configured signals.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : ComTxPduId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxIpdu              **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_TxIpduConfirmation()   **
**                                                 Com_TxSigConfirmation()    **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02044*/
FUNC(void, COM_CODE) Com_TxConfirmation(
  PduIdType ComTxPduId, Std_ReturnType result)
{
  if(result == E_OK)
  {
    /* @Trace: Com_SUD_API_00001 */
    /* #7707 */
    #if(COM_DEV_ERROR_DETECT == STD_ON)
    /* Local variable to store return value */
    uint8 LucReturnValue;
    #endif
    #if(COM_TX_IPDU_REPETITION == STD_ON)
    boolean LblReturnValue;
    #endif
    #if(COM_DEV_ERROR_DETECT == STD_ON)
    /* Initialize DET error flag to false */
      LucReturnValue = (uint8)E_OK;
      /* Check whether module is initialized */
      COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_TXCONFIRMATION);
      /* Check whether Tx PDU ID is out of range */
      COM_DET_TXPDUID_RANGE_CHECK_FLAG(ComTxPduId, COMSERVICEID_TXCONFIRMATION);
    if(LucReturnValue == (uint8)E_OK)
    #endif /* COM_DEV_ERROR_DETECT */
    {
      /* Check whether Tx I-PDU is started */
      if((Com_GaaTxIpduStatusBit[ComTxPduId] & COM_TX_REQ_STATUS_MASK) !=
                                                                     COM_FALSE)
      {
        #if((COM_TX_SIGNAL_UB == STD_ON) || \
            (COM_TX_SIGGROUP_UB == STD_ON) || \
            (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
            (COM_TX_IPDU_REPETITION == STD_ON))
        #if(COM_TX_IPDU_REPETITION == STD_ON)
        /* @Trace: Com_SUD_API_00003 */
        LblReturnValue = Com_TxIpduConfirmation(ComTxPduId);
        #else
        /* @Trace: Com_SUD_API_01302 */
        (void)Com_TxIpduConfirmation(ComTxPduId);
        #endif
        #endif
        #if(COM_TX_IPDU_REPETITION == STD_ON)
        if(LblReturnValue == COM_TRUE)
        #endif/*#if(COM_TX_IPDU_UPDATEBIT == STD_ON)*/      
        {
          /* @Trace: Com_SUD_API_00004 */
          /* Update confirmation status mask */
          #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
          #endif
          Com_GaaTxIpduStatusBit[ComTxPduId] |= COM_TX_CONFIRM_STATUS_MASK;
          Com_GaaTxIpduStatusBit[ComTxPduId] &= (uint16)
                                            (COM_TX_REQ_STATUS_CLEAR_MASK);
          #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
          #endif
  
          #if(COM_TX_SIGNAL_IMMEDIATENOTIFY == STD_ON)
          if((Com_GaaTxIpdu[ComTxPduId].ucTxConfig & 
            COM_TX_IPDU_DEF_NOTIFY_CONFIG_MASK)==COM_TX_IPDU_NOTIFY_CONFIG_MASK)
          {
            /* @Trace: Com_SUD_API_00005 */
            Com_TxSigConfirmation(&Com_GaaTxIpdu[ComTxPduId]);
          }
          #endif /* #if(COM_TX_SIGNAL_IMMEDIATENOTIFY == STD_ON) */
        }  
      } /* Check whether Tx I-PDU is started */
    } /* Check whether any development error has occurred */
  } /* @End if(result == E_OK) */
  else
  {
    /*nothing to do*/
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TrigTx_InputValidate                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TriggerTransmit                 **
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
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_TrigTx_InputValidate(PduIdType ComTxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr, 
  P2VAR(Std_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue)
{
  /* @Trace: Com_SUD_API_01406 */
  uint8 LucReturnValue;
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_TRIGGERTRANSMIT);
  /* Check whether PduInfoPtr pointer is NULL */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  COM_DET_PDUINFOPTR_PTR_CHECK_FLAG(PduInfoPtr, COMSERVICEID_TRIGGERTRANSMIT);
  /* Check whether Tx PDU ID is out of range */
  COM_DET_TXPDUID_RANGE_CHECK_FLAG(ComTxPduId, COMSERVICEID_TRIGGERTRANSMIT);
  if(LucReturnValue != (uint8)E_OK)
  {
    /* @Trace: Com_SUD_API_00007 */
    /* Specification of AUTOSASR for return value of Com_TriggerTransmit func*/
    *LpReturnValue = (uint8)E_NOT_OK;
  }

  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TrigTx_ProcUpdBitAndIpduCnt                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TriggerTransmit                 **
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
#if((COM_TX_SIGNAL_UB == STD_ON) || \
  (COM_TX_SIGGROUP_UB == STD_ON) || \
  (COM_TX_IPDU_COUNTER_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TrigTx_ProcUpdBitAndIpduCnt(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSourcePtr)
{
  #if((COM_TX_SIGNAL_UB == STD_ON) || \
    (COM_TX_SIGGROUP_UB == STD_ON))
  /* Check whether update bit needs to be cleared */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_UB_CONFIG_MASK) != COM_ZERO)
  {
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if(COM_TX_IPDU_UB_TRIGGER_CONFIG_MASK == 
      (Com_GaaTxUpdateBit[LpTxIpdu->ddTxIpduUbIndex].ucUBConfig))
    {
      /* @Trace: Com_SUD_API_00013 */
      Com_TxClearUpdateBit(LpTxIpdu, LpSourcePtr);
    }
  }
  #endif /*#if(COM_TX_SIGNAL_UB == STD_ON)*/
  
  #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
  if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
  {
    if(COM_COUNTER_TRIGTX == 
                          Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter])
    {
      /* @Trace: Com_SUD_API_00014 */
      Com_TransIpduCounter(LpTxIpdu);
    }
  }
  #endif
  #if((COM_TX_SIGNAL_UB == STD_OFF) && \
    (COM_TX_SIGGROUP_UB == STD_OFF))
  COM_UNUSED_PTR(LpSourcePtr);
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TriggerTransmit                                 **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : The lower layer calls this function when a Com      **
**                        I-PDU shall be transmitted. Within this function,   **
**                        Com shall copy the contents of its I-PDU transmit   **
**                        buffer to the L-PDU buffer given by SduPtr.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : ComTxPduId, PduInfoPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SduPtr                                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                                                 Com_GaaTxPduInfoPtr        **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxUpdateBit         **
**                                                 Com_GaaCounterStatusFlag   **
**                                                 Com_GaaTxIpduStatus        **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_TxClearUpdateBit()     **
**                                                 Com_TransIpduCounter()     **
**                                                 pIpduCallout               **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02045*/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit (PduIdType ComTxPduId,
                   P2VAR(PduInfoType, AUTOMATIC, COM_VAR) PduInfoPtr)
{
  /* @Trace: Com_SUD_API_00006 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSourcePtr;
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  /* Callout function input value is changed in 4.1.1 com specification 
  - Fixed by AUTRON START*/          
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr;
  /* Callout function input value is changed in 4.1.1 com specification 
  - Fixed by AUTRON END*/             

  /* Local variable to store no. of byte */
  PduLengthType LddNoOfByte;

  /* Local variable to store return value */
  Std_ReturnType LddReturnValue;
  /* #7707 */
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #endif  
  /* Initialize return value */
  LddReturnValue = (uint8)E_OK;
  
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_TrigTx_InputValidate(ComTxPduId, PduInfoPtr, &LddReturnValue);
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_00008 */
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON START*/        
    LpPduInfoPtr = (PduInfoType*)&Com_GaaTxPduInfoPtr[ComTxPduId];
  
    /* Get the pointer to I-PDU buffer */
    LpSourcePtr = LpPduInfoPtr->SduDataPtr;

    /* Get the size of I-PDU data buffer to local variable */
    LddNoOfByte = LpPduInfoPtr->SduLength;
    /* Callout function input value is changed in 4.1.1 com specification 
    - Fixed by AUTRON END*/ 
    /* Check PduInfoPtr->SduLength is smaller than the actual PDU-length */
    if(PduInfoPtr->SduLength < LddNoOfByte) 
    {
      /* @Trace: Com_SUD_API_00009 */
      LddReturnValue = (uint8)E_NOT_OK;
    }
    else
    {
        /* @Trace: Com_SUD_API_00010 */
      PduInfoPtr->SduLength = LddNoOfByte;
      LpTxIpdu = &Com_GaaTxIpdu[ComTxPduId];
    
      /* Enter protection area */
      SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();

      #if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
      /* Check whether I-PDU callout is configured */
      if(LpTxIpdu->ddIpduTriggerCalloutIndex != COM_INVALID_TXID_PARAM)
      {
        /* @Trace: Com_SUD_API_00011 */
        (void)Com_TxIpduTriggerCallout(ComTxPduId, 
          (PduInfoType *) LpPduInfoPtr);
      }
      #endif

      /* @Trace: Com_SUD_API_00012 */
      /* Copy the data buffer */
      /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
      memcpy(
        (P2VAR(void, AUTOMATIC, COM_VAR))(PduInfoPtr->SduDataPtr),
        (P2CONST(void, AUTOMATIC, COM_CONST))(&LpSourcePtr[COM_ZERO]),
        LddNoOfByte);
      
      /* Exit protection area */
      SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();

      #if((COM_TX_SIGNAL_UB == STD_ON) || \
        (COM_TX_SIGGROUP_UB == STD_ON) || \
        (COM_TX_IPDU_COUNTER_ENABLED == STD_ON))
      Com_TrigTx_ProcUpdBitAndIpduCnt(LpTxIpdu, LpSourcePtr);
      #endif
      /* polyspace:begin<MISRA-C3:2.1:Not a defect:Low>Not always a dead code. ucTxMode can be COM_TX_NONE_MODE*/
      /* Set the Ipdu Status even if Mode is None */
      if(Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex].ucTxMode == COM_TX_NONE_MODE)
      {
        /* @Trace: Com_SUD_API_00015 */
        SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
        Com_GaaTxIpduStatusBit[ComTxPduId] |= (uint16) (COM_TX_REQ_STATUS_MASK);
        SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      }
      /* polyspace:end<MISRA-C3:2.1:Not a defect:Low>Not always a dead code. ucTxMode can be COM_TX_NONE_MODE*/

      /* Check whether Tx I-PDU is enabled */
      if(Com_GaaTxIpduStatus[ComTxPduId] == (PduIdType)COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00016 */
        /* Specification of AUTOSASR for return value of Com_TriggerTransmit func*/
        LddReturnValue = (uint8)E_NOT_OK;
      }
    }/* else of if(PduInfoPtr->SduLength < LddNoOfByte) */
  } /* Check whether any development error has occurred */
  /* @Trace: Com_SUD_API_00017 */
  return(LddReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_RxInd_InputValidate                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxIndication                    **
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
#if(COM_RX_IPDU == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_RxInd_InputValidate(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr)
{
  /* @Trace: Com_SUD_API_01403 */
  uint8 LucReturnValue;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  /* Local variable to store return value */
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_RXINDICATION);
  /* Check whether PduInfoPtr pointer is NULL */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  COM_DET_PDUINFOPTR_PTR_CHECK_FLAG(PduInfoPtr, COMSERVICEID_RXINDICATION);
  /* Check whether Tx PDU ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01303 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId, COMSERVICEID_RXINDICATION);
  #else
  /* @Trace: Com_SUD_API_01304 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG_PB(ComRxPduId, COMSERVICEID_RXINDICATION);
  #endif

  /* @Trace: Com_SUD_API_00019 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  COM_RXPDUID_CHECK_COREID(ComRxPduId,LucReturnValue);
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_RxInd_RxProcessing                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_RxIndication                    **
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
#if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
  (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
FUNC(void, COM_CODE) Com_RxInd_RxProcessing(PduIdType ComRxPduId, 
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, 
  P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo)
#else
FUNC(void, COM_CODE) Com_RxInd_RxProcessing(PduIdType ComRxPduId, 
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu)
#endif
{
  /* @Trace: Com_SUD_API_00030 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  /* Clear Com_GaaMulticoreTriggerNotifyFlag before call Com_RxSigProcessing */
  Com_ClearTriggerNotifyFlag(COM_TRUE);
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #if(COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON)
  /* Check whether Rx  signals are present */
  /* Polyspace Useless if [A defect:Medium] This is a base code and the structure 
    * "Com_GaaRxIpdu is verified and generated by Generator Tool"*/
  if(LpRxIpdu->usNoOfRxSignal != COM_ZERO)
  {
    /* Invoke Com_RxSigProcessing() function to process all the
      signals configured in an I-PDU */
    #if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
    /* @Trace: Com_SUD_API_00031 */
    Com_RxSigProcessing(LpRxIpdu,
      *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength, 
      LpIdsMInfo);
    #else
    /* @Trace: Com_SUD_API_01306 */
    Com_RxSigProcessing(LpRxIpdu,
      *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength);
    #endif 
  }
  #endif

  #if(COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON)
  /* Check whether Rx signal groups are present */
  if(LpRxIpdu->ucNoOfRxSigGroup != COM_ZERO)
  {
    /* Invoke Com_RxSigGrpProcessing() function to process all
    the signal groups configured in an I-PDU */
    #if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
    /* @Trace: Com_SUD_API_00032 */
    Com_RxSigGrpProcessing(LpRxIpdu,
      *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength, 
      LpIdsMInfo);
    #else
    /* @Trace: Com_SUD_API_01308 */
    Com_RxSigGrpProcessing(LpRxIpdu,
      *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength);
    #endif
  }
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_RxIndication                                    **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : This function is called by the lower layer when an  **
**                        I-PDU shall be received. Within this function, COM  **
**                        Module shall copy the contents of its received      **
**                        I-PDU buffer from the L-PDU buffer given by SduPtr. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : ComRxPduId, PduInfoPtr                              **
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
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaRxPduInfoPtr        **
**                                                 Com_GaaRxGWIpduStatus      **
**                                                 Com_GaaInvRangeSigList     **
**                                                 Com_GblIsInvRangeSigPdu    **
**                                                 Com_GucInvRangeSigListIndex**
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_RxIpduValidate()       **
**                                                 Com_RxSigProcessing()      **
**                                                 Com_RxSigGrpProcessing()   **
*******************************************************************************/
/* @Trace: SWS_Com_00324 SWS_Com_00802 
SWS_Com_00587 SWS_Com_00123 SWS_Com_00300 SWS_Com_00301 
SWS_Com_00574 SWS_Com_00870 SWS_Com_00794 SWS_Com_00575 */

#if(COM_RX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02043, SRS_Com_02046*/
FUNC(void, COM_CODE) Com_RxIndication(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr)
{ 
  /* @Trace: Com_SUD_API_00018 */ 
  /* Pointer to Rx Ipdu structure */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Local variable to store size count */
  PduLengthType LddSize;
  /* #7707 */
  #if((COM_DEV_ERROR_DETECT == STD_ON)||(STD_ON == COM_MULTI_CORE_SUPPORT))
  uint8 LucReturnValue;
  #endif
  #if((COM_RX_IPDU_CALLOUT == STD_ON) || \
      (COM_RX_REPLICATION == STD_ON)  || \
      (COM_RX_IPDU_COUNTER_ENABLED == STD_ON))
  boolean LblReturnValue;
  #endif
  /* Redmine #15053: Local variable to store index of Com_GaaInvRangeSigList */
  #if(COM_IDSM_SUPPORT == STD_ON)
  Com_IdsMInfo LddIdsMInfo;
  uint8 LucInvRangeSigListIndex;
  #endif
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_RxInd_InputValidate(ComRxPduId, PduInfoPtr);
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_00020 */
    /* Get the pointer to Tx Ipdu */
    LpRxIpdu = &Com_GaaRxIpdu[ComRxPduId];
    /* Check whether Rx I-PDU is started */
    if(Com_GaaRxIpduStatus[ComRxPduId] != (PduIdType)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00021 */
      #if((COM_RX_IPDU_CALLOUT == STD_ON) || \
          (COM_RX_REPLICATION == STD_ON)  || \
          (COM_RX_IPDU_COUNTER_ENABLED == STD_ON)) 
      LblReturnValue = Com_RxIpduValidate(ComRxPduId, PduInfoPtr);
      if(LblReturnValue == COM_TRUE)
      #endif
      {
        if(LpRxIpdu->ddRxIpduLength < PduInfoPtr->SduLength)
        {
          /* @Trace: Com_SUD_API_00022 */
          /* The maximum allowed length of the I-pdu */
          LddSize = LpRxIpdu->ddRxIpduLength;
        }
        else
        {
          /* @Trace: Com_SUD_API_00023 */
          /* Get the length of an I-PDU */
          LddSize = PduInfoPtr->SduLength;
        }

        /* @Trace: Com_SUD_API_00024 */
        *Com_GaaRxPduInfoPtr[ComRxPduId].SduLength = LddSize;
        /* Copy the data buffer */
        /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
        memcpy(
        (P2VAR(void, AUTOMATIC, COM_VAR))(
          Com_GaaRxPduInfoPtr[ComRxPduId].SduDataPtr),
        (P2CONST(void, AUTOMATIC, COM_CONST))(PduInfoPtr->SduDataPtr),
        LddSize);

        /*Meta Data*/   
        #if (COM_META_DATA_SUPPORT == STD_ON)     
        if((PduInfoPtr->MetaDataPtr != NULL_PTR) &&\
          (Com_GaaRxPduInfoPtr[ComRxPduId].MetaDataPtr != NULL_PTR))
        {
          /* @Trace: Com_SUD_API_00025 */
          memcpy(
          (P2VAR(void, AUTOMATIC, COM_VAR))(
            Com_GaaRxPduInfoPtr[ComRxPduId].MetaDataPtr),
          (P2CONST(void, AUTOMATIC, COM_CONST))(PduInfoPtr->MetaDataPtr),
          LpRxIpdu -> ddMetaDataLength);      
        }
        else
        {
          /*do nothing*/
        }
        #endif
        /* @Trace: Com_SUD_API_00026 */
         Com_WriteReceiveIpduList((PduIdType)ComRxPduId);
        #if(COM_IDSM_SUPPORT == STD_ON)
        LddIdsMInfo.blIsInvRangeSigPdu = COM_FALSE;
        LddIdsMInfo.ucInvRangeSigListIndex = COM_ZERO;
        /* @Trace: Com_SUD_API_00027 */
        /* @Trace: Com_SUD_API_00028 */
        for(LucInvRangeSigListIndex = 0; 
          LucInvRangeSigListIndex < 4; 
          LucInvRangeSigListIndex++)
        {   
          /* @Trace: Com_SUD_API_00029 */
          LddIdsMInfo.aaInvRangeSigList[LucInvRangeSigListIndex] = 
            COM_SIG_RANGECHECK_DEF_ID;
        }
        #endif
        
        #if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) ||\
            (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
        {
          if((COM_FALSE == (Com_GaaRxIpdu[ComRxPduId].ucRxConfig &\
                              COM_RX_IPDU_DEFERRED_CONFIG_MASK)))
          {
            #if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
            /* @Trace: Com_SUD_API_01404 */
            Com_RxInd_RxProcessing(ComRxPduId, LpRxIpdu, &LddIdsMInfo);
            #else
            /* @Trace: Com_SUD_API_01405 */
            Com_RxInd_RxProcessing(ComRxPduId, LpRxIpdu);
            #endif
            /* Redmine #15053: If IdsM is supported and this PDU has out-ranged signals/group signals, Report to IdsM */
            #if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) ||\
              (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
            #if(COM_IDSM_SUPPORT == STD_ON)
            if(LddIdsMInfo.blIsInvRangeSigPdu == COM_TRUE)
            {
              /* @Trace: Com_SUD_API_00033 */
              /* Report to IdsM */
              IdsM_SigRangeCheckErrorReport(ComRxPduId,
              (P2CONST(uint16, AUTOMATIC, COM_CONST)) 
                &LddIdsMInfo.aaInvRangeSigList[COM_ZERO], 
              (P2CONST(uint8, AUTOMATIC, COM_CONST)) 
                Com_GaaRxPduInfoPtr[ComRxPduId].SduDataPtr, 
              LddSize);
            }
            #endif
            #if (STD_ON == COM_MULTI_CORE_SUPPORT)
            /* @Trace: Com_SUD_API_00034 */
            /* Check Com_GaaMulticoreTriggerNotifyFlag after call Com_RxSigProcessing */
            Com_ProcessTriggerNotifyFlag();
            #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
            #endif

            #if(((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) &&\
              (COM_RX_SIG_GATEWAY == STD_ON)) || (COM_RX_SIGNAL_GW_DES == STD_ON))
            /* Check whether signal based gateway is configured */
            if((LpRxIpdu->ucRxConfig & COM_RX_IPDU_GATEWAY_CONFIG_MASK) != 
                                                                      COM_FALSE)
            {
              /* @Trace: Com_SUD_API_00035 */
              SchM_Enter_Com_RX_GW_STS_PROTECTION_AREA();
              /* Set the gateway I-PDU status */
              /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
              Com_GaaRxGWIpduStatus[LpRxIpdu->ucRxGWStsIndex] |= 
                                                    LpRxIpdu->ucRxGWStsMask;
              #if (STD_ON == COM_MULTI_CORE_SUPPORT)
              Com_GaaRxGWIpduMulticoreStatus[LpRxIpdu->ucRxGWStsIndex] = 
                              (COM_ONE<<(COM_MULTI_CORE_MAX+COM_ONE)) - COM_ONE;
              #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
              SchM_Exit_Com_RX_GW_STS_PROTECTION_AREA();
            }
            #endif            
          }
        }
        #endif /*         #if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
            (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))  */
          
        #if((COM_RX_REPLICATION == STD_ON) && \
          (COM_RX_IPDU_COUNTER_ENABLED == STD_ON))
        /* @Trace: Com_SUD_API_00036 */
        Com_GblNoConfirmation = COM_FALSE;
        #endif
      }  /* Check return value of I-PDU call out */
    } /* Check whether Rx I-PDU group is started */
  } /* Check whether any development error has occurred */
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Traceability END -- SRS: SWS_Com_00324 SWS_Com_00802 
SWS_Com_00587 SWS_Com_00123 SWS_Com_00300 SWS_Com_00301 
SWS_Com_00574 SWS_Com_00870 SWS_Com_00794 SWS_Com_00575 */

/*******************************************************************************
** Function Name        : Com_RxReplication                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the Com module when the  **
**                        I-PDU is configured for I-PDU replication. Within   **
**                        this function, Com module shall perform the         **
**                        Communication Protection mechanism for I-PDUs       **
**                        received.                                           **
**                                                                            **
** Re-entrancy          : Non Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : LpRxIpdu, LpSduDataPtr                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :  Com_GaaRxRepliCount,         **
**                                               Com_GaaRxIpduReplication     **
**                                               Com_GaaRamIpduRepliSts       **
**                        Function(s) invoked :                               **
**                        SchM_Enter_xxx,  SchM_Exit_xxx                      **
*******************************************************************************/
#if(COM_RX_REPLICATION == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_RxReplication(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduDataPtr)
{
  /* @Trace: Com_SUD_API_00037 */
  P2CONST(Com_RxIpduReplication, AUTOMATIC, COM_CONST)
    LpRxIpduRepli;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpRepliSts;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpIpduTempBuff;
  /* uint8 -> PduLengthType for variable which has Pdu Length info 
  - Fixed by AUTRON START*/        
  PduLengthType LddSizeOrCount;
  /* uint8 -> PduLengthType for variable which has Pdu Length info 
  - Fixed by AUTRON END*/        
  uint8 LucRepliCount;
  boolean LblReturnValue;
  PduLengthType LddBufferIndex;

  LddBufferIndex = (PduLengthType)COM_ZERO;
  /* Set return value to FALSE */
  LblReturnValue = COM_FALSE;
  /* Load the pointer for Rx Replication stucture */
  LpRxIpduRepli = &Com_GaaRxIpduReplication[LpRxIpdu->ucRxIpduRepliIndex];
  /* Get the length of I-PDU */
  LddSizeOrCount = LpRxIpdu->ddRxIpduLength;
  /* Load the pointer for replicated I-PDU buffer */
  /* polyspace +3 CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
  /* polyspace +2 MISRA2012:11.5 [Not a defect:Low] "Pointer conversion is safe. Checked by unittest" */
  LpIpduTempBuff = (LpRxIpduRepli->pIpduBuffer);
  /* Get the actual replication count */
  LucRepliCount = Com_GaaRxRepliCount[LpRxIpduRepli->ucIpduRepliCountIndex];
  /* Shift to get the value */
  LucRepliCount >>= (LpRxIpduRepli->ucIpduRepliCountShift);
  LucRepliCount &= COM_REPLICATION_MASK;

  /* Check whether received I-PDU is first replicated I-PDU */
  if(COM_ZERO == LucRepliCount)
  {
    /* @Trace: Com_SUD_API_00038 */
    /* Enter protection area */
    SchM_Enter_Com_RX_IPDU_DATA_PROTECTION_AREA();
    /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
    memcpy(
    (P2VAR(void, AUTOMATIC, COM_VAR))(LpIpduTempBuff), 
    (P2CONST(void, AUTOMATIC, COM_CONST))(LpSduDataPtr), 
    (PduLengthType)LddSizeOrCount);
    /* Exit protection area */
    SchM_Exit_Com_RX_IPDU_DATA_PROTECTION_AREA();
    /* Load the replication count */
    LucRepliCount = LpRxIpduRepli->ucIpduRepliCount;
  }
  /* Is received I-PDU is not the first replicated I-PDU */
  else
  {
    /* @Trace: Com_SUD_API_00039 */
    /* Get the pointer to Rx Replication status */
    LpRepliSts = &Com_GaaRamIpduRepliSts[LpRxIpduRepli->ucIpduRepliStsIndex];
    /* Check replicated status of the I-PDU for mismatch in I-PDU */
    if(COM_ZERO == ((*LpRepliSts) & LpRxIpduRepli->ucIpduRepliEnMask))
    {
        /*
       * Compare each byte pointed by LpSduDataPtr with data byte which is
       * present in replicated I-PDU buffer
       */
      while(LddSizeOrCount != (PduLengthType)COM_ZERO)
      {
        /* Compare each data byte with data already stored in buffer */
        /* polyspace +2 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Access index is in-bound" */
        if(LpIpduTempBuff[LddBufferIndex] != LpSduDataPtr[LddBufferIndex])
        {
          /* @Trace: Com_SUD_API_00040 */
          /* Enter protection area */
          SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
          /* Set replicated status mask */
          (*LpRepliSts) |= LpRxIpduRepli->ucIpduRepliEnMask;
          /* Exit protection area */
          SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();
          /* Load with Zero to break the loop */
          LddSizeOrCount = (PduLengthType)COM_ZERO;
        }
        else
        {
          /* @Trace: Com_SUD_API_00041 */
          /* Decrement I-PDU size count variable */
          LddSizeOrCount--;
          /* Increment pointer index */
          LddBufferIndex++;
        }
      } /* End while(LucSizeOrCount != COM_ZERO) */
    } /* check whether any mismatch in replicated I-PDUs */

    /* @Trace: Com_SUD_API_00042 */
    /* Decrement Replication Count variable */
    LucRepliCount-- ;

    /* Check whether all replicated I-PDUs are received */
    if(COM_ZERO == LucRepliCount)
    {
      /*
       * Check replicated status mask for any data mismatch in any of the
       * replicated I-PDUs
       */
      if(((*LpRepliSts) & LpRxIpduRepli->ucIpduRepliEnMask) == COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00043 */
        LblReturnValue = COM_TRUE;
      }

      /* @Trace: Com_SUD_API_00044 */
      /* Enter protection area */
      SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
      /* Reset replicated status mask */
      (*LpRepliSts) &= (uint8)(~LpRxIpduRepli->ucIpduRepliEnMask);
      /* Exit protection area */
      SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();
    } /* @End if(LucRepliCount == COM_ZERO) */

  } /* Check whether Replicated I-PDU is not received for first time */

  /* @Trace: Com_SUD_API_00045 */
  /* Load the present replication count */
  LucRepliCount = 
    (uint8)(LucRepliCount << (LpRxIpduRepli->ucIpduRepliCountShift));
  /* Original value copied into a local variable */
 
  /* Load the timer with updated timer value */
  Com_GaaRxRepliCount[LpRxIpduRepli->ucIpduRepliCountIndex] = LucRepliCount;
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_RxIpduCounterChk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the Com module when the  **
**                        I-PDU is configured for I-PDU replication. Within   **
**                        this function, Com module shall perform the         **
**                        Communication Protection mechanism for I-PDUs       **
**                        received                                            **
**                                                                            **
** Re-entrancy          : Non Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : ComRxPduId, LpSduDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaRxIpdu                 **
**                                              Com_GaaRxIpduCounter          **
**                                              Com_GaaRxUnpack               **
**                                              Com_GaaRxIpduCountVal         **
**                                              Com_GaaRamIpduCounterSts      **
**                                              Com_GaaRxCntNotify            **
**                        Function(s) invoked : SchM_Enter_xxx()              **
**                                              SchM_Exit_xxx()               **
*******************************************************************************/
#if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON) 
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_RxIpduCounterChk(PduIdType ComRxPduId, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduDataPtr)
{
  /* @Trace: Com_SUD_API_00046 */
  P2CONST(Com_RxIpduCounter, AUTOMATIC, COM_CONST) LpRxIpduCounter;
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  uint8 LucExpCount;
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  uint8 LucIpduData;
  uint8 LucRxCountData;
  uint8 LucMaxExpCount;
  boolean LblReturnValue;
  LpRxIpdu = &Com_GaaRxIpdu[ComRxPduId];
  /* Set default return value */
  LblReturnValue = COM_TRUE;

  if (((COM_INVALID_TXID_PARAM) != LpRxIpdu->ddRxIpduCounter) && 
    ((PduIdType)(COM_RX_IPDU_COUNTER_SIZE) > LpRxIpdu->ddRxIpduCounter))
  {
    /* @Trace: Com_SUD_API_01798 */
    /* Load pointer for required Rx I-PDU counter structure */
    LpRxIpduCounter = &Com_GaaRxIpduCounter[LpRxIpdu->ddRxIpduCounter];
    /* Load pointer for RxUnpack structure */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Access index is in-bound" */
    LpRxUnpack = &Com_GaaRxUnpack[LpRxIpduCounter->ddRxUnpackIndex];
    /* Get the I-PDU buffer data to a local I-PDU variable */
    /* polyspace +3 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Access index is in-bound" */
    /* polyspace +1 MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
    LucIpduData = LpSduDataPtr[(Com_PtrType)LpRxUnpack->ucByteIndex];
    /*
    * Shift the local I-PDU variable by the number of shift bits to the get
    * the start position of counter data
    */
    /* polyspace +1 RTE:SHF [Not a defect:Low] "Shift amount is inside its bounds. This is assured by generator */
    LucIpduData = (uint8)(LucIpduData >> (LpRxUnpack->ucNoOfShiftBits));

    /* Get the counter data */
    LucRxCountData = LucIpduData;
    /* Apply the end mask to clear unoccupied area of counter */
    LucRxCountData &= LpRxUnpack->ucRdEndMask;

    /* Load the pointer for Expected I-PDU Count */
    LucExpCount = Com_GaaRxIpduCountVal[LpRxIpduCounter->ucRxIpduCountData];
    LucExpCount = 
              (uint8)(LucExpCount >> LpRxIpduCounter->ucRxIpduCounterShiftBits);
    LucExpCount &= LpRxIpduCounter->ucRxIpduCntWrpMask;

    /* Get maximum expected value with threshold */
    LucMaxExpCount = LucExpCount +(LpRxIpduCounter->ucIPduCounterThreshold);
    /* Get maximum count with counter wrap around */
    LucMaxExpCount &= LpRxIpduCounter->ucRxIpduCntWrpMask;


    /* Enter protection area */
    SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
    /* Check counter status whether I-PDU is received for first time */
    if(COM_ZERO == 
            ((Com_GaaRamIpduCounterSts[LpRxIpduCounter->ucIpduCnterStsIndex]) & 
                                          LpRxIpduCounter->ucIpduCounterEnMask))
    {
      /* @Trace: Com_SUD_API_00047 */
      /* Set the status bit indicating that the first Rx is over */
      Com_GaaRamIpduCounterSts[LpRxIpduCounter->ucIpduCnterStsIndex] 
        |= LpRxIpduCounter->ucIpduCounterEnMask;
    }
    else
    {
      /* Check for expected counter without counter wrap around */
      if(LucExpCount <= LucMaxExpCount)
      {
        /*
        * Discard the I-PDU when (received counter < expected counter) or
        * (received counter > expected counter with threshold)
        */
        if((LucRxCountData < LucExpCount) || (LucRxCountData > LucMaxExpCount))
        {
          /* @Trace: Com_SUD_API_00048 */
          LblReturnValue = COM_FALSE;
        }
      }
      /* Check for expected counter with counter wrap around */
      else
      {
        /*
        * Discard the I-PDU when (received counter < expected counter) and
        * (received counter > expected counter with threshold)
        */
        if((LucRxCountData < LucExpCount) 
          && (LucRxCountData > LucMaxExpCount))
        {
          /* @Trace: Com_SUD_API_00049 */
          LblReturnValue = COM_FALSE;
        }
      }
    }
    /* @Trace: Com_SUD_API_01921 */
    /* Exit protection area */
    SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();

    /* Set expected counter if LblReturnValue is not reset */
    if(COM_TRUE == LblReturnValue)
    {
      /* @Trace: Com_SUD_API_00050 */
      /* Increment counter data for setting expected value */
      LucMaxExpCount = LucRxCountData + COM_ONE;
      /* Apply Threshold */
      LucMaxExpCount &= LpRxIpduCounter->ucRxIpduCntWrpMask; 
      /* Shift the value */
      LucMaxExpCount = 
        (uint8)(LucMaxExpCount << (LpRxIpduCounter->ucRxIpduCounterShiftBits));
      LucExpCount = Com_GaaRxIpduCountVal[LpRxIpduCounter->ucRxIpduCountData];
      LucExpCount &= 
      (uint8)(~((uint8)((LpRxIpduCounter->ucRxIpduCntWrpMask)<<
        (LpRxIpduCounter->ucRxIpduCounterShiftBits))));
      /* Load the expected count value respecting counter wrap around */
      Com_GaaRxIpduCountVal[LpRxIpduCounter->ucRxIpduCountData] =LucMaxExpCount;
      Com_GaaRxIpduCountVal[LpRxIpduCounter->ucRxIpduCountData] |= LucExpCount;
    }
    #if(COM_RX_COUNTER_NOTIFY == STD_ON)
    else
    {
      /* Check whether counter notification is configured */
      if(LpRxIpduCounter->ucRxCntNotifIndx != COM_INVALID_NONE)
      {
        /* @Trace: Com_SUD_API_00051 */
        /* Invoke counter notification function*/
        (*Com_GaaRxCntNotify[LpRxIpduCounter->ucRxCntNotifIndx])(ComRxPduId,
          Com_GaaRxIpduCountVal[LpRxIpduCounter->ucRxIpduCountData], 
          LucRxCountData);
      }
    }
    #endif
  }
  else
  {
    /* @Trace: Com_SUD_API_01800 */
    LblReturnValue = COM_FALSE;
  }
  
  /* @Trace: Com_SUD_API_00052 */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_RxIpduValidate                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                        It validates Ipdu callout and also the counter      **
**                        value                                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : ComRxPduId, PduInfoPtr                              **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaRxIpdu             **
**                        Function(s) invoked    :  pIpduCallout              **
**                                                  Com_RxReplication()       **
**                                                  Com_RxIpduCounterChk()    **
*******************************************************************************/
#if((COM_RX_IPDU_CALLOUT == STD_ON) || \
    (COM_RX_REPLICATION == STD_ON)  || \
    (COM_RX_IPDU_COUNTER_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"    
FUNC(boolean, COM_CODE) Com_RxIpduValidate(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr)
{
  /* @Trace: Com_SUD_API_00053 */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Set LblReturnFlag to TRUE */
  boolean LblReturnFlag = COM_TRUE;
  /* Get the pointer to Tx Ipdu */
  LpRxIpdu = &Com_GaaRxIpdu[ComRxPduId];  
  
  #if(COM_RX_IPDU_CALLOUT == STD_ON)
  /* Check whether I-PDU callout is configured */
  /* Polyspace Useless if [A defect:Medium] This is a base code and the structure
   * "Com_GaaRxIpdu is verified and generated by Generator Tool" */
  if((LpRxIpdu->ddIpduCalloutIndex) != COM_INVALID_RXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00054 */
    LblReturnFlag = Com_RxIpduCallout(ComRxPduId, 
    (P2CONST(PduInfoType, AUTOMATIC, COM_CONST)) PduInfoPtr);
  }
  if(COM_TRUE == LblReturnFlag)
  #endif
  {
    #if((COM_RX_REPLICATION == STD_ON) \
    &&(COM_RX_IPDU_COUNTER_ENABLED == STD_ON) )
    /* Check whether Rx Replication is configured for this I-PDU */  
    if(LpRxIpdu->ucRxIpduRepliIndex != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_00055 */
      /* Invoke Com_RxReplication() to check I-PDU Replication */
      LblReturnFlag = Com_RxReplication(
      (P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST)) LpRxIpdu, 
      (P2CONST(uint8, AUTOMATIC, COM_CONST)) PduInfoPtr->SduDataPtr);
    }
    else
    {
      /* @Trace: Com_SUD_API_00056 */
      LblReturnFlag = COM_TRUE;
    }
  
    if(COM_TRUE == LblReturnFlag)
    #endif
    {
      #if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
      /* Check whether I-PDU counter is configured */
      if(LpRxIpdu->ddRxIpduCounter != COM_INVALID_RXID_PARAM)
      {        
        /* @Trace: Com_SUD_API_00057 */
        /* Invoke Com_RxIpduCounterChk() to check I-PDU counter */
        LblReturnFlag = 
          Com_RxIpduCounterChk(ComRxPduId, 
            (P2CONST(uint8, AUTOMATIC, COM_CONST)) PduInfoPtr->SduDataPtr);
        #if(COM_RX_REPLICATION == STD_ON)
        #endif
      }      
      else
      {
        /* @Trace: Com_SUD_API_00058 */
        LblReturnFlag = COM_TRUE;
      }
      #endif 
    }     
  }
  /* @Trace: Com_SUD_API_00059 */
  return(LblReturnFlag);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h" 
#endif

/*******************************************************************************
** Function Name        : Com_TxIpduConfirmation                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                        It performs setting of update bit and updating      **
**                        of repetition counter                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LddComTxPduId                                       **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaTxIpdu             **
**                                                  Com_GaaTxMDTimer          **
**                                                  Com_GaaTxMDTimeout        **
**                                                  Com_GaaTxUpdateBit        **
**                                                  Com_GaaTxMode             **
**                                                  Com_GaaTxIpduStatusBit    **
**                                                  Com_GaaTxReptCount        **
**                        Function(s) invoked    :  SchM_Enter_xxx()          **
**                                                  SchM_Exit_xxx()           **
**                                                  Com_TxClearUpdateBit()    **
*******************************************************************************/
 #if((COM_TX_SIGNAL_UB == STD_ON) || \
     (COM_TX_SIGGROUP_UB == STD_ON) || \
     (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
     (COM_TX_IPDU_REPETITION == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"      
FUNC(boolean, COM_CODE) Com_TxIpduConfirmation(PduIdType LddComTxPduId)
{
  /* @Trace: Com_SUD_API_00060 */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  #if(COM_TX_IPDU_REPETITION == STD_ON)
  /* Pointer to Tx Mode structure */
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  /* Local variable to store repetition value */
  uint8 LucReptCount;
  /* Local variable to store repetition sub value */
  uint8 LucReptSubCount;
  #endif
  #if((COM_TX_SIGNAL_UB == STD_ON) || \
      (COM_TX_SIGGROUP_UB == STD_ON))
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSduDataPtr;
  #endif
  
  boolean LblReturnValue;
  
  LblReturnValue = COM_TRUE;
  /* Get the pointer to Tx Ipdu */
  LpTxIpdu = &Com_GaaTxIpdu[LddComTxPduId];
  #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
  /* Check whether minimum delay timer is configured */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_ZERO)
  {
    /* Check whether minimum delay timer is equal to zero */
    if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] != (uint16)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00061 */
      #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Enter_Com_TX_MDT_PROTECTION_AREA();
      #endif
      /* Load minimum delay timer with the configured value plus one */
      /* #1517 : remove the plus one code for preventing MDT delay */
      /* leave the FEATURE in order to specify major point 
      of both transmit mode */
      /* #2022 MDTForCyclicTransmission related compile error 
      & incorrect operation is fixed(ref 4.2.1 Com Spec) */
      #if(COM_ENABLE_MDT_CYCLIC == STD_ON)
      /* @Trace: Com_SUD_API_01309 */
      Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex]  =
      Com_GaaTxMDTimeout[LpTxIpdu->ddTxMDTimerIndex];
      #else
      if((Com_GaaTxIpduStatusBit[LddComTxPduId] 
        & COM_TX_REPT_CONFIRM_HANDLE_MASK) == COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00062 */
        Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex]  =
        Com_GaaTxMDTimeout[LpTxIpdu->ddTxMDTimerIndex];
      }
      else
      {
        /* @Trace: Com_SUD_API_00063 */
        Com_GaaTxIpduStatusBit[LddComTxPduId] 
          &= (uint16)(~COM_TX_REPT_CONFIRM_HANDLE_MASK);
      }
     
      #endif
      #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
      /* @Trace: Com_SUD_API_00064 */
      SchM_Exit_Com_TX_MDT_PROTECTION_AREA();
      #endif
    }
  }
  #endif
  #if((COM_TX_SIGNAL_UB == STD_ON) || \
          (COM_TX_SIGGROUP_UB == STD_ON))
  /* @Trace: Com_SUD_API_00329 */
  LpSduDataPtr = Com_GaaTxPduInfoPtr[LddComTxPduId].SduDataPtr;
  /* Check whether update bit needs to be cleared */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_UB_CONFIG_MASK) != COM_ZERO)
  {
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if(Com_GaaTxUpdateBit[LpTxIpdu->ddTxIpduUbIndex].ucUBConfig ==
      COM_TX_IPDU_UB_CONFIRM_CONFIG_MASK)
    {
      /* @Trace: Com_SUD_API_00065 */
      Com_TxClearUpdateBit(LpTxIpdu, LpSduDataPtr);
    }
  }
  #endif
  
  #if(COM_TX_IPDU_REPETITION == STD_ON)
  /* @Trace: Com_SUD_API_00066 */
  /* Get the pointer to true Tx mode */
  LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
  /* Check whether TMS is configured */
  if((Com_GaaTxIpduStatusBit[LddComTxPduId] & COM_TX_TMS_STATUS_MASK) ==
                                                                  COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00067 */
    LpTxMode = 
    &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
  }
  #endif /* #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))*/

  /* Check whether repetition count is configured */
  if(LpTxMode->ucReptCount != COM_ZERO)
  {
    #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
    /* #1518 : Clear the status bit for repetition count and prevent updating repetition count */
    if((LpTxMode->ucDirectMainTransmit == COM_TX_DIRECT_TRANS) && 
        ((Com_GaaTxIpduStatusBit[LddComTxPduId] &
        COM_TX_REPT_COUNT_HANDLE_MASK) != COM_FALSE))
    {
      /* @Trace: Com_SUD_API_00068 */
      #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      #endif
      Com_GaaTxIpduStatusBit[LddComTxPduId] &= 
                                (uint16)(COM_TX_REPT_COUNT_HANDLE_CLEAR_MASK);
      #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();  
      #endif
      LblReturnValue = COM_FALSE;
    }
    else
    #endif
    {
      /* @Trace: Com_SUD_API_00069 */
      /* Get the repetition count value to local variable */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      LucReptCount = Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex];
      LucReptSubCount = Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex];
      /* Check whether repetition count value is greater than zero */
      if(LucReptCount != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00070 */
        /* Decrement the repetition count */
        LucReptCount--;
        /* Set the repetition count */
        Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] = LucReptCount;
        /* Check whether repetition count is not equal to zero */
        if((LucReptCount != COM_ZERO) || (LucReptSubCount != COM_ZERO))
        {
          /* @Trace: Com_SUD_API_00071 */
          LblReturnValue = COM_FALSE;
          /* Reset the Tx Request Bit */
          #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
          #endif
          Com_GaaTxIpduStatusBit[LddComTxPduId] &= 
                                        (uint16)(COM_TX_REQ_STATUS_CLEAR_MASK);
          #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();            
          #endif
        }
      }
    }
  } /* Check whether repetition count is configured */
  #endif
  /* @Trace: Com_SUD_API_00072 */
  return(LblReturnValue);    
}
#define COM_STOP_SEC_CODE
#include "MemMap.h" 
#endif

/*******************************************************************************
** Function Name        : Com_TransIpduCounter                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                        It sets the next expected counter value             **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LpTxIpdu                                            **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxIpduCounter       **
**                                                 Com_GaaTxIpduCountVal      **
**                                                 Com_GaaCounterStatusFlag   **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
        Com_TransIpduCounter(P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_00073 */
  P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) LpTxIpduCounter;
  uint8 LucTxIpduCountValue;

  LpTxIpduCounter = &Com_GaaTxIpduCounter[LpTxIpdu->ddTxIpduCounter];
  /* Check whether Tx I-PDU counter is configured */
  if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00074 */
    /* Get the present counter data */
    LucTxIpduCountValue = 
                      Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData];
    if(COM_COUNTER_E_PENDING == 
                          Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter])
    {
      /* @Trace: Com_SUD_API_00075 */
      /* Decrement I-PDU count value */
      LucTxIpduCountValue--;
      SchM_Enter_Com_IPDU_COUNTER_PROTECTION();
      Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter] =COM_COUNTER_TRIGTX;
      SchM_Exit_Com_IPDU_COUNTER_PROTECTION();
    }
    else if(Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter] 
      == COM_COUNTER_TRIGTX)
    {
      /* @Trace: Com_SUD_API_00076 */
      /* Increment I-PDU count value */
      LucTxIpduCountValue++;
      Com_GaaCounterStatusFlag[LpTxIpdu->ddTxIpduCounter] = COM_ZERO;
      
    }
    else
    {
      /* Do nothing */
    }
    /* @Trace: Com_SUD_API_00077 */
    /* Apply wrap around mask to the counter data */
    LucTxIpduCountValue &= LpTxIpduCounter->ucTxIpduCntWrpMask;
  }
  else
  {
    /* @Trace: Com_SUD_API_00078 */
    LucTxIpduCountValue = LpTxIpduCounter->ucTxIpduCntWrpMask;
  }
   /* Enter protection area */
   /* @Trace: Com_SUD_API_00079 */
  SchM_Enter_Com_IPDU_COUNTER_PROTECTION();
  /* Load present counter data in buffer */
  Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData] 
    = LucTxIpduCountValue;
  /* Exit Critical Area */
  SchM_Exit_Com_IPDU_COUNTER_PROTECTION();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
