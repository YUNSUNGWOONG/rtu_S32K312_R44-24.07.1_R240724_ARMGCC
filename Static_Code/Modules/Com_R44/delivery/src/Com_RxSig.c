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
**  SRC-MODULE: Com_RxSig.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of receive functions and their functionality.       **
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
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-771                               **
** 1.1.4     02-Jun-2022   DuyNHP2     R44-Redmine #27636                     **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139 #19314              **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Com.h"          /* Com header file */
#include "Com_Main.h"     /* Com Main header file */
#include "Com_Pack.h"     /* Com Pack header file */
#include "Com_Error.h"    /* Com Error header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                 /* Det header file */
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

#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSigGrp_PackSigBuffer(
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL == STD_ON)||(COM_RX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSig_UnPackSigBuffer(
  Com_SignalIdType SignalId,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue,
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveDynSig_UnPackSigBuffer(
  P2VAR(uint16, AUTOMATIC, COM_VAR) length,
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal, 
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_DEV_ERROR_DETECT ==  STD_ON)
#if((COM_RX_DYN_SUPPORT == STD_ON) ||\
 (COM_RX_SIGNAL == STD_ON) ||\
 (COM_RX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSig_DetCheck(
  Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  Com_ServiceIdType ServiceId,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif
#if(COM_DEV_ERROR_DETECT ==  STD_ON)
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSigGrp_DetCheck(
  Com_SignalGroupIdType SignalGroupId,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_ReceiveSignal                                   **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Com_ReceiveSignal copies the data of the signal     **
**                        identified by SignalId to the location specified by **
**                        SignalDataPtr.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : SignalId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SignalDataPtr                                       **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxSignal            **
**                                                 Com_GaaRxUnpack            **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaWrFuncPtr           **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 pWrFuncPtr                 **
**                                                 pRdFuncPtr                 **
**                                                 Com_ShadowSignalCopy()     **
*******************************************************************************/
/* @Trace: SWS_Com_00007 SWS_Com_00810 
SWS_Com_00472 SWS_Com_00472 SWS_Com_00008 
SWS_Com_00723 SWS_Com_00579 
SWS_Com_00352 SWS_Com_00580 SWS_Com_00325 SWS_Com_00380 
SWS_Com_00866 SWS_Com_00603 SWS_Com_00604 SWS_Com_00680 
SWS_Com_00681 SWS_Com_00870 SWS_Com_00059
SWS_Com_00843 */

#if((COM_RX_SIGNAL == STD_ON)||(COM_RX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02037, SRS_Com_02079, SRS_Com_02087,
SRS_Com_02086, SRS_Com_02088, SRS_Com_02089 */
FUNC(uint8, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId,
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_00834 */
  #if((COM_RX_SIGNAL == STD_ON) && (COM_RX_TP_SUPPORT == STD_ON))
  /* Pointer to Rx Signal structure */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal;
  #endif
  #if(COM_RX_TP_SUPPORT == STD_ON)
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  #endif
  #if(COM_RX_TP_SUPPORT == STD_ON)
  #if(COM_RX_SIGGROUP == STD_ON)
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup;
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) LpRxSigInGrp;
  #endif
  #endif
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Initialize DET error flag to false */
  LucReturnValue = (uint8)E_OK;

  #if(COM_DEV_ERROR_DETECT == STD_ON)
  Com_ReceiveSig_DetCheck(SignalId, SignalDataPtr,
    COMSERVICEID_RECEIVESIGNAL, &LucReturnValue);
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    #if(COM_RX_TP_SUPPORT == STD_ON)
    #if((COM_RX_SIGNAL == STD_ON) && (COM_RX_SIGGROUP == STD_ON))
    if(SignalId >= COM_RX_SIG_GRPSIG_BOUNDARY)
    {
      /* @Trace: Com_SUD_API_00835 */
      /* Get the pointer to  Rx signal in Grp */
      LpRxSigInGrp = &Com_GaaRxSigInGrp[SignalId - COM_RX_SIG_GRPSIG_BOUNDARY];
      
      /* Get the pointer to  Rx signal Grp */
      LpRxSigGroup = &Com_GaaRxSigGroup[LpRxSigInGrp->ddSigGrpIndex];
      
      /* Get the pointer to Tx IPdu structure */
      LpRxIpdu =  &Com_GaaRxIpdu[LpRxSigGroup->ddRxpduId];
    }
    else
    #endif /* #if(COM_RX_SIGGROUP == STD_ON) && (COM_RX_SIGGROUP == STD_ON)) */
    #if(COM_RX_SIGNAL == STD_ON)
    { 
      /* @Trace: Com_SUD_API_00836 */
      /* Get the pointer to  Rx signal */
      LpRxSignal = &Com_GaaRxSignal[SignalId];
      
      /* Get the pointer to Tx IPdu structure */
      LpRxIpdu =  &Com_GaaRxIpdu[LpRxSignal->ddRxpduId];
    }
    if(LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_00837 */
      /* Get the pointer to TP structure  */
      LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
      if((Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] 
      & (LpRxTPIpdu->ucRxTPStatusMask)) != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00838 */
        LucReturnValue = (uint8)COM_BUSY;
      }
    }
    #endif /* #if(COM_RX_SIGNAL == STD_ON) */
    if(LucReturnValue == (uint8)E_OK)
    #endif /* #if(COM_RX_TP_SUPPORT == STD_ON) */
    {
      /* @Trace: Com_SUD_API_01446 */
      Com_ReceiveSig_UnPackSigBuffer(SignalId, &LucReturnValue, SignalDataPtr);
    } /* Check whether any development error has occurred */
  }
  /* @Trace: Com_SUD_API_00844 */
  /* Return value */
  return(LucReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Traceability END -- SRS: SRS: SWS_Com_00007 SWS_Com_00810 
SWS_Com_00472 SWS_Com_00472 SWS_Com_00008 
SWS_Com_00723 SWS_Com_00579 
SWS_Com_00352 SWS_Com_00580 SWS_Com_00325 SWS_Com_00380 
SWS_Com_00866 SWS_Com_00603 SWS_Com_00604 SWS_Com_00680 
SWS_Com_00681 SWS_Com_00870 SWS_Com_00059
SWS_Com_00843 */
/*******************************************************************************
** Function Name        : Com_ReceiveDynSignal                                **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : The service Com_ReceiveDynSignal returns in Length  **
**                        the length of the dynamical length signal and in    **
**                        SignalDataPtr a pointer to the data of the signal   **
**                        identified by SignalId.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : SignalId                                            **
**                                                                            **
** InOut parameter      : length                                              **
**                                                                            **
** Output Parameters    : SignalDataPtr                                       **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxSignal            **
**                                                 Com_GaaRxIpdu              **
**                                                 Com_GaaRxTPIpdu            **
**                                                 Com_GaaRxUnpack            **
**                                                 Com_GaaRxTPStatus          **
**                                                 Com_GaaRxDynSigLength      **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaWrFuncPtr           **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 pRdFuncPtr                 **
**                                                 pWrFuncPtr                 **
*******************************************************************************/
#if(COM_RX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02092, SRS_Com_02095*/
FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(Com_SignalIdType SignalId, 
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr, 
  P2VAR(uint16, AUTOMATIC, COM_VAR) length)
{
  /* @Trace: Com_SUD_API_00845 */
  /* Pointer to Rx Signal structure */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal;
  /* Pointer to Rx Ipdu */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;

  /* #2142 : separate DYN PDU from TP */
  #if(COM_RX_TP_SUPPORT == STD_ON)
  /* Pointer to Rx TP structure */
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  #endif
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Variable to hold the existing length of the dynamic signal */
  
  /* Initialize DET error flag to false */
  LucReturnValue = (uint8)E_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  Com_ReceiveSig_DetCheck(SignalId, SignalDataPtr,
    COMSERVICEID_RECEIVEDYNSIGNAL, &LucReturnValue);
  /* Check whether Common pointer is NULL */
  COM_DET_COMMON_PTR_CHECK_FLAG(length, COMSERVICEID_RECEIVEDYNSIGNAL);
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_00846 */
    /* Get the pointer to  Rx signal */
    LpRxSignal = &Com_GaaRxSignal[SignalId];
    /* Get the pointer to  Rx Ipdu */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    LpRxIpdu = &Com_GaaRxIpdu[LpRxSignal->ddRxpduId];
    /* #2142 : separate DYN PDU from TP */
    #if(COM_RX_TP_SUPPORT == STD_ON)
    /* Get the pointer to Rx TP structure */
    LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
    #endif

    if(LpRxIpdu->ucIpduType == COM_DYN_IPDU)
    {
      #if(COM_RX_TP_SUPPORT == STD_ON)    
      if(LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
      {
        if(COM_ZERO != (Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] & 
                       (LpRxTPIpdu->ucRxTPStatusMask)))
        {
          /* @Trace: Com_SUD_API_00847 */
          /* If TP Buffer is locked, return COM_BUSY */
          LucReturnValue = (uint8)COM_BUSY;
        }
      }
      #endif

      if(LucReturnValue == (uint8)E_OK)
      {
        Com_ReceiveDynSig_UnPackSigBuffer(length, LpRxIpdu, LpRxSignal, 
         SignalDataPtr, &LucReturnValue);
      }
    }
    else
    {
      /* @Trace: Com_SUD_API_00853 */
      /* Set return value to "E_NOT_OK" */
      LucReturnValue = (uint8)E_NOT_OK;
    }
  } /* Check whether any development error has occurred */
  /* @Trace: Com_SUD_API_00854 */
  /* Return value */
  return(LucReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ReceiveSignalGroup                              **
**                                                                            **
** Service ID           : 0x0E                                                **
**                                                                            **
** Description          : This function copies the received signal group from **
**                        the I-PDU to the shadow buffer. After this call,    **
**                        the signals from this signal group could be copied  **
**                        from the shadow buffer to the upper layer by a call **
**                        of Com_ReceiveShadowSignal().                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signal groups.              **
**                        Non-Reentrant for the same signal group.            **
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
** Remarks              : Global Variable(s)     :  Com_GaaRxSigGroup         **
**                                                  Com_GaaRxIpduStatus       **
**                        Function(s) invoked    :  Det_ReportError()         **
**                                                  pWrFuncPtr                **
*******************************************************************************/
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02041*/
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup
  (Com_SignalGroupIdType SignalGroupId)
{
  /* @Trace: Com_SUD_API_01279 */
  /* Pointer to Rx Signal Group structure */
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup;
  #if(COM_RX_TP_SUPPORT == STD_ON)
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  #endif
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  Com_ReceiveSigGrp_DetCheck(SignalGroupId, 
    &LucReturnValue);
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_01280 */
    /* Get the pointer to  Rx signal group structure */
    LpRxSigGroup = &Com_GaaRxSigGroup[SignalGroupId];
    #if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
      (COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON))
    if(LpRxSigGroup->blArrayAccess == COM_TRUE)
    {
      /* @Trace: Com_SUD_API_01281 */
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
    }

    if(LucReturnValue == (uint8)E_OK)
    #endif
    {
      #if(COM_RX_TP_SUPPORT == STD_ON)
      /* @Trace: Com_SUD_API_01282 */
      /* Get the pointer to Tx IPdu structure */
      LpRxIpdu =  &Com_GaaRxIpdu[LpRxSigGroup->ddRxpduId];
      
      if(LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
      {
        /* @Trace: Com_SUD_API_01283 */
        /* Get the pointer to TP structure  */
        LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
        if((Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] 
        & (LpRxTPIpdu->ucRxTPStatusMask)) != COM_ZERO)
        {
          /* @Trace: Com_SUD_API_01284 */
          LucReturnValue = (uint8)COM_BUSY;
        }
      }
      if(LucReturnValue == (uint8)E_OK)
      #endif
      {
        /* Check whether Rx I-PDU is enabled */
        if((PduIdType)COM_ZERO == Com_GaaRxIpduStatus[LpRxSigGroup->ddRxpduId])
        {
          /* @Trace: Com_SUD_API_01285 */
          /* Set return value to "COM_TRUE" */
          LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
        }

        Com_ReceiveSigGrp_PackSigBuffer(LpRxSigGroup);
      } /* Check whether any development error has occurred */
    }
  }
  /* @Trace: Com_SUD_API_01289 */
  /* Return value */
  return(LucReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_ReceiveSignalGroupArray                         **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : This function copies the received signal group from **
**                        the I-PDU to the shadow buffer. After this call,    **
**                        the signals from this signal group could be copied  **
**                        from the shadow buffer to the upper layer by a call **
**                        of Com_ReceiveShadowSignal().                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signal groups.              **
**                        Non-Reentrant for the same signal group.            **
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
** Remarks              : Global Variable(s)     :  Com_GaaRxSigGroup         **
**                                                  Com_GaaRxIpduStatus       **
**                        Function(s) invoked    :  Det_ReportError()         **
**                                                  pWrFuncPtr                **
*******************************************************************************/

#if(COM_RX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02112, SRS_Com_02041*/
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray(
    Com_SignalGroupIdType SignalGroupId, 
    P2VAR (uint8, AUTOMATIC, COM_VAR) SignalGroupArrayPtr)
{
  /* @Trace: Com_SUD_API_01290 */
  /* Pointer to Rx Signal Group structure */
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup;
  /* Pointer to Pack signal group  structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpPackSigGroup;
  #if(COM_RX_TP_SUPPORT == STD_ON)
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  #endif
  /* Local variable to store return value */
  uint8 LucReturnValue;
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_RECEIVESIGNALGROUPARRAY);
  /* Check whether signal group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01674 */
  COM_DET_RXSIGNALGROUPID_RANGE_CHECK_FLAG(
    COMSERVICEID_RECEIVESIGNALGROUPARRAY);
  #else
  /* @Trace: Com_SUD_API_01675 */
  COM_DET_RXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(
    COMSERVICEID_RECEIVESIGNALGROUPARRAY);
  #endif
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* @Trace: Com_SUD_API_01291 */
    /* Get the pointer to  Rx signal group structure */
    LpRxSigGroup = &Com_GaaRxSigGroup[SignalGroupId];  
    #if(COM_RX_TP_SUPPORT == STD_ON)
    /* Get the pointer to Tx IPdu structure */
    LpRxIpdu =  &Com_GaaRxIpdu[LpRxSigGroup->ddRxpduId];
    
    if(LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_01292 */
      /* Get the pointer to TP structure  */
      LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
      if((Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] 
      & (LpRxTPIpdu->ucRxTPStatusMask)) != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_01293 */
        LucReturnValue = (uint8)COM_BUSY;
      }
    }
    if(LucReturnValue == (uint8)E_OK)
    #endif
    {
      /* Check whether Rx I-PDU is enabled */
      if((PduIdType)COM_ZERO == Com_GaaRxIpduStatus[LpRxSigGroup->ddRxpduId])
      {
        /* @Trace: Com_SUD_API_01294 */
        /* Set return value to "COM_TRUE" */
        LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
      }
      /* @Trace: Com_SUD_API_01295 */
      /* Get the pointer to PackSigGroup structure */
      LpPackSigGroup = LpRxSigGroup->pPackShadowBuffer;
      /* Redmine #13931: when Rx Signal Group passed the filter, I-PDU data are copied to pPackSigGrpBuffer*/
      #if((COM_RX_SIGGROUP_INVALID == STD_ON) || \
          (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON)|| \
          (COM_RX_SIGGROUP_FILTER == STD_ON))
      /* Check whether timeout replacement value is configured */
      
      if((LpRxSigGroup->pPackSigGrpBuffer) != NULL_PTR)
      {
        /* @Trace: Com_SUD_API_01296 */
        /* Invoke the write function to pack the signal group buffer into shadow
        buffer */
        /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
        (void)Com_PackSigGrpArray(LpPackSigGroup, 
          LpRxSigGroup->pPackSigGrpBuffer->pWrBuffer, SignalGroupArrayPtr);
        /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
      }
      else
      #endif
      /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
      {
        /* @Trace: Com_SUD_API_01297 */
        /* Invoke the pack function to pack the I-PDU buffer into shadow buffer
        */
        (void)Com_PackSigGrpArray(LpPackSigGroup, 
          LpRxSigGroup->pIpduBuffer, SignalGroupArrayPtr);
      }
    } /* Check whether any development error has occurred */
  }
  /* @Trace: Com_SUD_API_01298 */
  /* Return value */
  return(LucReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/* #7525, #7744, #7803 end */
/*******************************************************************************
** Function Name        : Com_ShadowSignalCopy                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies the received signal group from **
**                        the I-PDU to the shadow buffer. After this call,    **
**                        the signals from this signal group could be copied  **
**                        from the shadow buffer to the upper layer by a call **
**                        of Com_ReceiveShadowSignal().                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signal groups.              **
**                        Non-Reentrant for the same signal group.            **
**                                                                            **
** Input Parameters     : SignalId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SignalDataPtr                                       **
**                                                                            **
** Return parameter     : LucReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  Com_GaaRxSigInGrp         **
**                                                  Com_GaaRxUnpack           **
**                        Function(s) invoked    :  pRdFuncPtr                **
*******************************************************************************/
/* #7525 start */
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_ShadowSignalCopy
(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01299 */
  /* Pointer to Rx Signal Group structure */
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) LpRxSigInGrp;
  /* Pointer to Rx Unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  #if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
    (COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON))
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup;
  #endif

  uint8 LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;

  /* Get the pointer to  Rx signal in group */
  LpRxSigInGrp = &Com_GaaRxSigInGrp[SignalId];

  #if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
    (COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON))
  LpRxSigGroup = &Com_GaaRxSigGroup[LpRxSigInGrp->ddSigGrpIndex];
  if(LpRxSigGroup->blArrayAccess != COM_TRUE)  
  #endif
  { 
    /* @Trace: Com_SUD_API_01300 */ 
    /* Get the pointer to RxUnpack structure */
    LpRxUnpack = &Com_GaaRxUnpack[LpRxSigInGrp->ddRxUnpackIndex];
    /* Invoke read function to unpack the data from the I-PDU buffer to
    SignalDataPtr */
    #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
    (void)Com_UnPackRequestRead(LpRxUnpack, SignalDataPtr);
    #endif
    LucReturnValue = (uint8)E_OK;
  }
  /* @Trace: Com_SUD_API_01301 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* #7525 end */

/*******************************************************************************
** Function Name        : Com_ReceiveSigGrp_PackSigBuffer                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_ReceiveSignalGroup              **
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
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSigGrp_PackSigBuffer(
  P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) LpRxSigGroup)
{
  /* @Trace: Com_SUD_API_01286 */
  /* Pointer to Pack signal group  structure */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpPackSigGroup;
  /* Get the pointer to PackSigGroup structure */
  /* Redmine #13931: when Rx Signal Group passed the filter, I-PDU data are copied to pPackSigGrpBuffer*/
  LpPackSigGroup = LpRxSigGroup->pPackShadowBuffer;
  #if((COM_RX_SIGGROUP_INVALID == STD_ON) || \
      (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON) || \
      (COM_RX_SIGGROUP_FILTER == STD_ON))
  /* Check whether timeout replacement value is configured */
  
  if((LpRxSigGroup->pPackSigGrpBuffer) != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_01287 */
    /* Invoke the write function to pack the signal group buffer into shadow
    buffer */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    (void)Com_PackSigGrpArray(LpPackSigGroup, 
      LpRxSigGroup->pPackSigGrpBuffer->pWrBuffer, 
      LpPackSigGroup->pWrBuffer); 
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
  }
  else
  #endif
  /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  {
    /* @Trace: Com_SUD_API_01288 */
    /* Invoke the pack function to pack the I-PDU buffer into shadow buffer
    */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    (void)Com_PackSigGrpArray(LpPackSigGroup, LpRxSigGroup->pIpduBuffer, 
      LpPackSigGroup->pWrBuffer);
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_ReceiveSig_UnPackSigBuffer                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_ReceiveSignal                   **
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
#if((COM_RX_SIGNAL == STD_ON)||(COM_RX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSig_UnPackSigBuffer(
  Com_SignalIdType SignalId,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue,
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_01466 */
  #if(COM_RX_SIGNAL == STD_ON)
  /* Pointer to Rx Signal structure */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal;
  /* Pointer to Rx Unpack structure */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  #endif

  #if((COM_RX_SIGNAL == STD_ON) && (COM_RX_SIGGROUP == STD_ON))
  if(SignalId >= COM_RX_SIG_GRPSIG_BOUNDARY)
  #endif
  #if(COM_RX_SIGGROUP == STD_ON)
  {
    /* @Trace: Com_SUD_API_00839 */
    *LpReturnValue = 
      Com_ShadowSignalCopy(SignalId - COM_RX_SIG_GRPSIG_BOUNDARY,
        SignalDataPtr);
  }
  #endif /* #if((COM_RX_SIGNAL == STD_ON) */
  #if((COM_RX_SIGNAL == STD_ON) && (COM_RX_SIGGROUP == STD_ON))
  else
  #endif /* #if((COM_RX_SIGNAL == STD_ON) && (COM_RX_SIGGROUP == STD_ON)) */
  #if(COM_RX_SIGNAL == STD_ON)
  {
    /* @Trace: Com_SUD_API_00840 */
    /* Get the pointer to  Rx signal */
    LpRxSignal = &Com_GaaRxSignal[SignalId];
    /* Get the pointer to RxUnpack structure */
    LpRxUnpack = &Com_GaaRxUnpack[LpRxSignal->ddRxUnpackIndex];
    #if((COM_RX_SIGNAL_UBDMREPLACE == STD_ON)|| \
          (COM_RX_SIGNAL_FILTER == STD_ON) || \
          (COM_RX_SIGNAL_INVALID == STD_ON))
    /* Check whether signal buffer is equal to NULL */
    if(LpRxSignal->pSignalBuffer != NULL_PTR)
    {
      /* @Trace: Com_SUD_API_00841 */
      /* Invoke the write function to unpack the data from the signal buffer
      and copy to SignalDataPtr */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaWrFuncPtr[LpRxUnpack->ucSignalType].pWrFuncPtr
        (LpRxSignal->pSignalBuffer, SignalDataPtr,LpRxUnpack->ddSignalSize);
    }
    
    else 
    #endif
    {
      /* @Trace: Com_SUD_API_00842 */
      #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
      /* Invoke the unpack function for the signal */
      (void)Com_UnPackRequestRead(LpRxUnpack, SignalDataPtr);    
      #endif                                               
    }
    /* Check whether Rx I-PDU is enabled */
    if((PduIdType)COM_ZERO == Com_GaaRxIpduStatus[LpRxSignal->ddRxpduId])
    {
      /* @Trace: Com_SUD_API_00843 */
      /* Set return value to "COM_SERVICE_NOT_AVAILABLE" */
      *LpReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
    }
  }
  #endif /*#if(COM_RX_SIGNAL == STD_ON)*/
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ReceiveDynSig_UnPackSigBuffer                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_ReceiveDynSignal                **
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
#if(COM_RX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveDynSig_UnPackSigBuffer(
  P2VAR(uint16, AUTOMATIC, COM_VAR) length,
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) LpRxSignal, 
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue)
{ 
  /* @Trace: Com_SUD_API_01463 */
  P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack;
  /* Get the pointer to RxUnpack structure */
  LpRxUnpack = &Com_GaaRxUnpack[LpRxSignal->ddRxUnpackIndex];
  /* polyspace +3 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
  /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(*length >= 
    (uint16)Com_GaaRxDynSigLength[LpRxIpdu->ddRxIpduDynLegthRef])
  {
    /* @Trace: Com_SUD_API_00848 */
    /* Get the dynamic signal length */
    *length = 
      (uint16)Com_GaaRxDynSigLength[LpRxIpdu->ddRxIpduDynLegthRef];
    #if((COM_RX_SIGNAL_UBDMREPLACE == STD_ON)|| \
                    (COM_RX_SIGNAL_FILTER == STD_ON) || \
                      (COM_RX_SIGNAL_INVALID == STD_ON))
    /* Check whether signal buffer is equal to NULL */
    if(LpRxSignal->pSignalBuffer != NULL_PTR)
    {
      /* @Trace: Com_SUD_API_00849 */
      /* Invoke the write function to unpack the data from the signal buffer
      and copy to SignalDataPtr */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaWrFuncPtr[LpRxUnpack->ucSignalType].pWrFuncPtr
        (LpRxSignal->pSignalBuffer, SignalDataPtr, 
        (PduLengthType)(*length));
    }
    else 
    #endif
    {
      /* @Trace: Com_SUD_API_00850 */
      /* Invoke the unpack function for the signal */
      #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO) 
      (void)Com_UnPackRequestRead(LpRxUnpack, SignalDataPtr);
      #endif
    }
    /* Check whether Rx I-PDU is enabled */
    if((PduIdType)COM_ZERO == Com_GaaRxIpduStatus[LpRxSignal->ddRxpduId])
    {
      /* @Trace: Com_SUD_API_00851 */
      /* Set return value to "COM_SERVICE_NOT_AVAILABLE" */
      *LpReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;
    }
  }
  else
  {
    /* @Trace: Com_SUD_API_00852 */
    /* Set return value to "E_NOT_OK" */
    *LpReturnValue = (uint8)E_NOT_OK;
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ReceiveSig_DetCheck                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_ReceiveDynSignal,               **
**                            Com_ReceiveSignal, Com_ReceiveSignalGroup       **
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
#if(COM_DEV_ERROR_DETECT ==  STD_ON)
#if((COM_RX_DYN_SUPPORT == STD_ON) ||\
 (COM_RX_SIGNAL == STD_ON) ||\
 (COM_RX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSig_DetCheck(
  Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr,
  Com_ServiceIdType ServiceId,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue)
{
  /* @Trace: Com_SUD_API_01464 */
  uint8 LucReturnValue = *LpReturnValue;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(ServiceId);
  /* Check whether signal ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01669 */
  COM_DET_RX_SIGNALID_RANGE_CHECK_FLAG(ServiceId);
  #else
  /* @Trace: Com_SUD_API_01670 */
  COM_DET_RX_SIGNALID_RANGE_CHECK_FLAG_PB(ServiceId);
  #endif
  /* @Trace: Com_SUD_API_01671 */
  /* Check whether signal data pointer is equal to NULL */
  COM_DET_SIGNAL_DATA_PTR(ServiceId);
  /* Check whether any development error has occurred */
  *LpReturnValue = LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_ReceiveSigGrp_DetCheck                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of  Com_ReceiveSignalGroup             **
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
#if(COM_DEV_ERROR_DETECT ==  STD_ON)
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveSigGrp_DetCheck(
  Com_SignalGroupIdType SignalGroupId,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpReturnValue)
{
  /* @Trace: Com_SUD_API_01465 */
  uint8 LucReturnValue = *LpReturnValue;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_RECEIVESIGNALGROUP);
  /* Check whether signal group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01672 */
  COM_DET_RXSIGNALGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_RECEIVESIGNALGROUP);
  #else
  /* @Trace: Com_SUD_API_01673 */
  COM_DET_RXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(COMSERVICEID_RECEIVESIGNALGROUP);
  #endif

  *LpReturnValue = LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
