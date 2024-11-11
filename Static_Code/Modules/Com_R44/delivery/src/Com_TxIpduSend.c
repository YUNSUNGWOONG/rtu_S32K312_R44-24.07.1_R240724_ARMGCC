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
**  SRC-MODULE: Com_TxIpduSend.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of I-PDU sending functions.                         **
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
** 1.1.4     02-Jun-2022   DuyNHP2     R44-Redmine #27636 #28007              **
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
#include <string.h>
#include "Com.h"          /* Com header file */
#include "Com_TxIpdu.h"   /* Com Tx I-PDU header file */
#include "Com_Main.h"     /* Com Main header file */
#include "Com_Pack.h"     /* Com Pack header file */
#include "Com_Error.h"    /* SchM Com header file */
#include "SchM_Com.h"     /* Com Error header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
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

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_UpdateTpIpduStatus                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates the TP I-PDU status        .  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : ComTxPduId, LpTxIpdu                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxTPStatus          **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxIpduStatusBit     **
**                        Function(s) invoked    : N/A                        **
**                                                                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_UpdateTpIpduStatus(PduIdType ComTxPduId,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01506 */
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;

  if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
  {  
    /* @Trace: Com_SUD_API_00931 */
    /* Get the pointer to TP structure  */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
    & (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
    {  
      /* @Trace: Com_SUD_API_00932 */      
      Com_GaaTxIpduStatusBit[ComTxPduId] |= COM_TX_TP_BUFFER_STATUS_MASK; 
      #if(COM_DEV_ERROR_DETECT == STD_ON)
      COM_DET_TP_SKIP_TRANSMISSION(COMSERVICEID_TRIGGERIPDUSEND);
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_UpdateMdtIpduStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates the I-PDU status on MDT based **
**                        arrays                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : ComTxPduId, LpTxIpdu                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxMDTimer           **
**                                                 Com_GaaTxIpduStatusBit     **
**                        Function(s) invoked    : SchM_Enter_Com_xxx()       **
**                        Function(s) invoked    : SchM_Exit_Com_xxx()        **
**                                                                            **
*******************************************************************************/
#if((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COM_CODE) Com_UpdateMdtIpduStatus(PduIdType ComTxPduId,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_00933 */
  /* Local variable to store Ipdu config */
  uint8 LucIpduConfig;

  boolean LblReturnFlag;

  LblReturnFlag = COM_TRUE;
  LucIpduConfig = LpTxIpdu->ucTxConfig;
  if((LucIpduConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_FALSE)
  {
    /* Check whether minimum delay timer is set to zero */
    if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] != (uint16)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00934 */
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      Com_GaaTxIpduStatusBit[ComTxPduId] |= COM_TX_PENDING_STATUS_MASK;
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      LblReturnFlag = COM_FALSE;
    }
  } /* Check whether minimum delay timer is configured for I-PDU */

  return LblReturnFlag;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ProcessTriggerCallout                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function process the trigger of callout for Tx **
**                        of IPDU                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : ComTxPduId, LpTxIpdu                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxPduInfoPtr        **
**                                                 Com_GaaTxIpduStatusBit     **
**                        Function(s) invoked    : SchM_Enter_Com_xxx()       **
**                                                 SchM_Exit_Com_xxx()        **
**                                                 Com_TxIpduTriggerCallout() **
**                                                                            **
*******************************************************************************/
#if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_ProcessTriggerCallout(PduIdType ComTxPduId, 
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_00935 */
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr;
  /* Get the pointer to PduInfoPtr structure */
  LpPduInfoPtr = &Com_GaaTxPduInfoPtr[ComTxPduId];

  /* Check whether I-PDU callout is configured */
  if(LpTxIpdu->ddIpduTriggerCalloutIndex != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00936 */
    /* Enter protection area */
    SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();      
    (void)Com_TxIpduTriggerCallout(ComTxPduId, 
      (PduInfoType *)LpPduInfoPtr);
    /* Exit Critical Area */
    SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TriggerIPDUSend                                 **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This function triggers the I-PDU with the given ID  **
*                         for transmission.                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ComTxPduId                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : It shall only be used from within I-PDU callout.    **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxMDTimer           **
**                                                 Com_GaaTxIpdu[]            **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxPduInfoPtr        **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_Transmit()             **
**                                                 pIpduCallout()             **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02037*/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType ComTxPduId)
{
  /* @Trace: Com_SUD_API_00929 */
  /* Local variable to store return value */
  Std_ReturnType LddReturnValue;
  /* Initialize return value */
  LddReturnValue = (uint8)E_NOT_OK;
  #if((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
      (COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)) || (COM_TX_TP_SUPPORT == STD_ON)
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  #endif
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #endif
  #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
  boolean LblReturnFlag;
  #endif
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_TRIGGERIPDUSEND);
  /* Check whether Tx PDU ID is out of range */
  COM_DET_TXPDUID_RANGE_CHECK_FLAG(ComTxPduId, COMSERVICEID_TRIGGERIPDUSEND);
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* Check that IPDU is already start */
    if(Com_GaaTxIpduStatus[ComTxPduId] != (PduIdType)COM_ZERO)
    {
      #if((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
        (COM_TX_IPDU_TRIGGERCALLOUT == STD_ON))|| (COM_TX_TP_SUPPORT == STD_ON)
      /* @Trace: Com_SUD_API_00930 */
      /* Get the pointer to TxIpdu strcuture */
      LpTxIpdu = &Com_GaaTxIpdu[ComTxPduId];
      #endif
      /* TP data req 867 */
      #if(COM_TX_TP_SUPPORT == STD_ON)
      Com_UpdateTpIpduStatus(ComTxPduId, LpTxIpdu);
      if((Com_GaaTxIpduStatusBit[ComTxPduId] & COM_TX_TP_BUFFER_STATUS_MASK) ==
        COM_FALSE)
      #endif
      {
        /* @Trace: Com_SUD_API_01508 */
        /* Invoke Com_TxRequest() function to trigger I-PDU for transmission */
        #if((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
        LblReturnFlag = Com_UpdateMdtIpduStatus(ComTxPduId, LpTxIpdu);

        if(LblReturnFlag == COM_TRUE)
        #endif
        {
          /* @Trace: Com_SUD_API_00937 */
          #if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
          Com_ProcessTriggerCallout(ComTxPduId, LpTxIpdu);
          #endif
          /* Reduce the invoking count of Protection Area - by AUTRON END */  
          /* Invoke the Com_Transmit() function to transmit an I-PDU to the lower
            layer */
          LddReturnValue = Com_Transmit((PduIdType)ComTxPduId);
        }
      }
    }/* Check that IPDU is already start*/
  }/* Check whether any development error has occurred */
  /* @Trace: Com_SUD_API_00938 */
  return(LddReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType ComTxPduId)
{
  /* @Trace: Com_SUD_API_01684 */
  COM_UNUSED(ComTxPduId);
  /* #1204 : Dummy Function for integration with BswM Module */
  return E_OK;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ProcessIpduWithMetaData                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function process the trigger of callout for Tx **
**                        of IPDU                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : LpTxIpdu, LpPduInfoPtr, MetaData                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : N/A                        **
**                                                                            **
**                        Function(s) invoked    : memcpy()                   **
**                                                                            **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) && (COM_META_DATA_SUPPORT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COM_CODE) Com_ProcessIpduWithMetaData(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr,
  P2CONST(uint8, AUTOMATIC, COM_CONST) MetaData)
{
  /* @Trace: Com_SUD_API_01509 */
  boolean LblNullPtrCheck;

  LblNullPtrCheck = COM_TRUE;

  if (LpPduInfoPtr->MetaDataPtr != NULL_PTR)
  {
    /* No explicit meta data is given for a send request - ECUC_Com_10005*/
    if( MetaData == NULL_PTR)
    {
      if((LpTxIpdu->pDefaultMetaDataValue != NULL_PTR) && 
        (LpTxIpdu->ddTxMetaDataLength != COM_INVALID_NONE))
      {
        /* @Trace: Com_SUD_API_00941 */
        /* Copying the metadata from the given position and with respect to 
        length of the globally configured MetaDataType of this I-PDU - ECUC_Com_10005 */
        /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
        memcpy(
        (P2VAR(void, AUTOMATIC, COM_VAR))(LpPduInfoPtr->MetaDataPtr),
        (P2CONST(void, AUTOMATIC, COM_CONST))
          (LpTxIpdu->pDefaultMetaDataValue),
        LpTxIpdu->ddTxMetaDataLength);
      }
      else
      {
        /* @Trace: Com_SUD_API_00942 */
        LblNullPtrCheck = COM_FALSE;
      }
    }
    else
    {
      if(LpTxIpdu->ddTxMetaDataLength != COM_INVALID_NONE)
      {
        /* @Trace: Com_SUD_API_00943 */
        /* Copying the metadata from the given position and with respect to 
        length of the globally configured MetaDataType of this I-PDU -SWS_Com_00858 */
        /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
        memcpy(
        (P2VAR(void, AUTOMATIC, COM_VAR))(LpPduInfoPtr->MetaDataPtr),
        (P2CONST(void, AUTOMATIC, COM_CONST))(MetaData),
        LpTxIpdu->ddTxMetaDataLength);
      }
      else
      {
        /* @Trace: Com_SUD_API_00944 */
        LblNullPtrCheck = COM_FALSE;
      }
    }
  }
  else
  {
    /* @Trace: Com_SUD_API_00945 */
    LblNullPtrCheck = COM_FALSE;
  }

  return LblNullPtrCheck;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ProcessTpIpduStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates for TP IPDU status before Tx  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : PduId, LpTxIpdu                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxTPStatus          **
**                                                 Com_GaaTxTPIpdu            **
**                                                                            **
**                        Function(s) invoked    : N/A                        **
**                                                                            **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) && (COM_META_DATA_SUPPORT == STD_ON))
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_ProcessTpIpduStatus(PduIdType PduId,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01510 */
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  if(LpTxIpdu->ucTxTPRef != COM_INVALID_NONE)
  {
    /* @Trace: Com_SUD_API_00946 */
    /* Get the pointer to TP structure  */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    if((Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] 
    & (LpTxTPIpdu->ucTxTPStatusMask)) != COM_ZERO)
    {    
      /* @Trace: Com_SUD_API_00947 */    
      Com_GaaTxIpduStatusBit[PduId] |= COM_TX_TP_BUFFER_STATUS_MASK;
      #if(COM_DEV_ERROR_DETECT == STD_ON)
      COM_DET_TP_SKIP_TRANSMISSION(
        COMSERVICEID_TRIGGERIPDUSENDWITHMETADATA);
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TriggerIPDUSendWithMetaData                     **
**                                                                            **
** Service ID           : 0x28                                                **
**                                                                            **
** Description          : This function triggers the I-PDU with the given ID  **
*                         and MetaData for transmission.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduId, MetaData                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : It shall only be used from within I-PDU callout.    **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxMDTimer           **
**                                                 Com_GaaTxIpdu[]            **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxPduInfoPtr        **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_Transmit()             **
**                                                 pIpduCallout()             **
*******************************************************************************/
#if((COM_TX_IPDU == STD_ON) && (COM_META_DATA_SUPPORT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02037*/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSendWithMetaData(PduIdType PduId, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) MetaData)
{
  /* @Trace: Com_SUD_API_00939 */
  /* Local variable to store return value */
  Std_ReturnType LddReturnValue;
  /* Initialize return value */
  LddReturnValue = (uint8)E_NOT_OK;
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;

  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr;

  #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
  /* Local variable to store Ipdu config */
  uint8 LucIpduConfig;
  #endif
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #endif
  #if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
  boolean LblReturnFlag;
  LblReturnFlag = COM_TRUE;
  #endif
  boolean LblNullPtrCheck;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_TRIGGERIPDUSENDWITHMETADATA);
  /* Check whether Tx PDU ID is out of range */
  COM_DET_TXPDUID_RANGE_CHECK_FLAG(PduId, 
    COMSERVICEID_TRIGGERIPDUSENDWITHMETADATA);
  
  /* Check whether any development error has occurred */
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* Check that IPDU is already start*/
    if(Com_GaaTxIpduStatus[PduId] != (PduIdType)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00940 */
      /* Get the pointer to PduInfoPtr structure */
      LpPduInfoPtr = &Com_GaaTxPduInfoPtr[PduId];
      /* Get the pointer to TxIpdu strcuture */
      LpTxIpdu = &Com_GaaTxIpdu[PduId];

      LblNullPtrCheck = Com_ProcessIpduWithMetaData(LpTxIpdu, LpPduInfoPtr, MetaData);

      /* Check if MetaDataPtr exists */
      if (LblNullPtrCheck == COM_TRUE)
      {
        /* @Trace: Com_SUD_API_01511 */
        /* TP data req 868*/
        #if(COM_TX_TP_SUPPORT == STD_ON)
        Com_ProcessTpIpduStatus(PduId, LpTxIpdu);
        
        if((Com_GaaTxIpduStatusBit[PduId] & COM_TX_TP_BUFFER_STATUS_MASK) ==
          COM_FALSE)
        #endif
        {
          /* @Trace: Com_SUD_API_00948 */
          /* Invoke Com_TxRequest() function to trigger I-PDU for transmission */
          #if((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
          LucIpduConfig = LpTxIpdu->ucTxConfig;
          if((LucIpduConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_FALSE)
          {
            /* @Trace: Com_SUD_API_00949 */
            LblReturnFlag = COM_TRUE;
            /* Check whether minimum delay timer is set to zero */
            if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] != (uint16)COM_ZERO)
            {
              /* @Trace: Com_SUD_API_00950 */
              SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
              Com_GaaTxIpduStatusBit[PduId] |= COM_TX_PENDING_STATUS_MASK;
              SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
              LblReturnFlag = COM_FALSE;
            }
          } /* Check whether minimum delay timer is configured for I-PDU */
          if(LblReturnFlag == COM_TRUE)
          #endif
          {
            /* Reduce the invoking count of Protection Area - by AUTRON START */  
            #if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
            /* Check whether I-PDU callout is configured */
            if(LpTxIpdu->ddIpduTriggerCalloutIndex != COM_INVALID_TXID_PARAM)
            {
              /* @Trace: Com_SUD_API_00951 */
              /* Enter protection area */
              SchM_Enter_Com_TX_IPDU_BUFFER_PROTECTION_AREA();      
              (void)Com_TxIpduTriggerCallout(PduId, 
                (PduInfoType *)LpPduInfoPtr);
              /* Exit Critical Area */
              SchM_Exit_Com_TX_IPDU_BUFFER_PROTECTION_AREA();
            }
            #endif
            /* Reduce the invoking count of Protection Area - by AUTRON END */  

            /* Invoke the Com_Transmit() function to transmit an I-PDU to the lower
              layer */
            /* @Trace: Com_SUD_API_00952 */
            LddReturnValue = Com_Transmit((PduIdType)PduId);
          }
        }    
      }
      else
      {
        /* Do nothing */
      }
    }/* Check that IPDU is already start*/
  }/* Check whether any development error has occurred */
  /* @Trace: Com_SUD_API_00953 */
  return(LddReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_InitReptTxMode                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates for repetition counters at    **
**                        the first direct transmission                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : LpTxMode, LpTxIpdu, LusTxIpduStatusBit, LucConfig   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxReptCount         **
**                                                 Com_GaaTxReptSubCount      **
**                                                                            **
**                        Function(s) invoked    : N/A                        **
**                                                                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if (COM_TX_IPDU_REPETITION == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_InitReptTxMode(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode, 
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu, 
  P2VAR(uint16, AUTOMATIC, COM_VAR) LusTxIpduStatusBit, uint8 LucConfig)
{
  /* @Trace: Com_SUD_API_01512 */
  uint16 LusLocalTxIpduStatusBit;

  LusLocalTxIpduStatusBit = *LusTxIpduStatusBit;
  #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION == COM_TX_MAINFUNC)
  COM_UNUSED_PTR(LpTxIpdu);
  #endif
  /* Check whether repetition counter is not zero */
  if((((LpTxMode->ucTxMode) >= COM_TX_MIXEDNTIMES_MODE) &&
      ((LpTxMode->ucTxMode) != COM_TX_DIRECT_MODE)) && 
      ((LucConfig & COM_TX_SIGPROP_WOREPT_CONFIG_MASK) !=
                                          COM_TX_SIGPROP_WOREPT_CONFIG_MASK))
  {
    /* @Trace: Com_SUD_API_00962 */
    LusLocalTxIpduStatusBit |= COM_TX_REPT_STATUS_MASK;
    *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
    #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and has checked manual and it is not having any impact" */
    if(LpTxMode->ucDirectMainTransmit == COM_TX_DIRECT_TRANS)
    {
      /* @Trace: Com_SUD_API_00963 */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] = LpTxMode->ucReptCount;
      if(LpTxMode->ucReptCount != COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00964 */
        Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] 
            = LpTxMode->ucReptCount - COM_ONE;
      }
      else
      {
        /* @Trace: Com_SUD_API_00965 */
        Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] = COM_ZERO;
      }
      if ((LusLocalTxIpduStatusBit & COM_TX_REQ_STATUS_MASK) != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_01832 */
        LusLocalTxIpduStatusBit |= COM_TX_REPT_COUNT_HANDLE_MASK;
        *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
      }
    }
    #endif
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TransmitIpdu                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates IPDU status before calling    **
**                        transmit function                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : LpTxMode, CoreId, LusTxIpduStatusBit, LddTxPduId    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxReptCount         **
**                                                 Com_GaaTxReptSubCount      **
**                                                 Com_GaaDirectTriggerList   **
**                                                 Com_GaaTxIpduTransmitFlag  **
**                                                                            **
**                        Function(s) invoked    : Com_Transmit()             **
**                                                 SchM_Enter_Com_xxx()       **
**                                                 SchM_Exit_Com_xxx()        **
**                                                                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if((STD_ON == COM_MULTI_CORE_SUPPORT) && \
  (COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC))
static FUNC(Std_ReturnType, COM_CODE) Com_TransmitIpdu(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LusTxIpduStatusBit, 
  PduIdType LddTxPduId, CoreIdType CoreId)
#else
static FUNC(Std_ReturnType, COM_CODE) Com_TransmitIpdu(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LusTxIpduStatusBit, 
  PduIdType LddTxPduId)
#endif
{
  /* @Trace: Com_SUD_API_00972 */
  /* Local variable to store return value */
  Std_ReturnType LenReturnValue;

  uint16 LusLocalTxIpduStatusBit;
  #if((STD_ON == COM_MULTI_CORE_SUPPORT) && \
    (COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC))
  CoreIdType CoreIdCheck;
  #endif
  LenReturnValue = E_OK;

  LusLocalTxIpduStatusBit = *LusTxIpduStatusBit;
  LusLocalTxIpduStatusBit |= COM_TX_MAINFUNC_SEND_STATUS_MASK;
  *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
  Com_GaaTxIpduStatusBit[LddTxPduId] = LusLocalTxIpduStatusBit;
  #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of ucDirectMainTransmit is generated by generator and has checked manual and it is not having any impact" */
  if(LpTxMode->ucDirectMainTransmit == COM_TX_DIRECT_TRANS)
  {
    /* @Trace: Com_SUD_API_00973 */
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    CoreIdCheck = Com_GaaTxIpduCorePosition[LddTxPduId];
    if(CoreId == CoreIdCheck)
    {
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
      /* @Trace: Com_SUD_API_00974 */
      LenReturnValue = Com_Transmit(LddTxPduId);
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    }
    else
    {
      /* @Trace: Com_SUD_API_00975 */
      SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
      Com_GaaTxIpduTransmitFlag[LddTxPduId] = (uint8)COM_ONE;
      SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
      /* Trigger Ioc write and call Com_DirectTrigger */
      (void)Com_GaaDirectTriggerList[CoreIdCheck](COM_TRUE);
    }
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  }
  #else
  COM_UNUSED_PTR(LpTxMode);
  #endif

  /* @Trace: Com_SUD_API_01507 */

  return LenReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ProcessWithMdtOrDm                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxRequest                       **
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
#if ((COM_TX_IPDU_DM == STD_ON) || \
  (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
  (COM_TX_IPDU_GW == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
  (COM_TX_IPDU_REPETITION == STD_ON) || \
  (COM_TX_IPDU_GW == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessWithMdtOrDm(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu, 
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode, 
  P2VAR(uint16, AUTOMATIC, COM_VAR) LusTxIpduStatusBit, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LucTransmitFlag, 
  uint8 LucIpduConfig, uint8 LucConfig)
#else
static FUNC(void, COM_CODE) Com_ProcessWithMdtOrDm(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu, 
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode, 
  P2VAR(uint16, AUTOMATIC, COM_VAR) LusTxIpduStatusBit, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LucTransmitFlag, 
  uint8 LucIpduConfig)
#endif
{
  /* @Trace: Com_SUD_API_01513 */
  uint16 LusLocalTxIpduStatusBit;

  LusLocalTxIpduStatusBit = *LusTxIpduStatusBit;

  #if (COM_TX_IPDU_DM == STD_ON)
  /* Check whether deadline monitoring is configured */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
  {
    /* Check whether timer is equal to zero or Tx mode is direct */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if(((Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex]) == (uint16)COM_ZERO) ||
                            (LpTxMode->ucTxMode >= COM_TX_MIXEDNTIMES_MODE))
    {
      /* @Trace: Com_SUD_API_00966 */
      LusLocalTxIpduStatusBit |= COM_TX_DM_STATUS_MASK;
      *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
    }
  }
  #endif
  #if (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
  /* Check whether minimum delay timer is configured for I-PDU */
  if((LucIpduConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_FALSE)
  {
    /* Check whether minimum delay timer is set to zero */
    if(Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] != (uint16)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00967 */
      LusLocalTxIpduStatusBit |= COM_TX_PENDING_STATUS_MASK;
      *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
      *LucTransmitFlag = COM_FALSE;
      #if (COM_TX_IPDU_GW == STD_ON)
      LucConfig = COM_ZERO;
      #endif
    }
  } /* Check whether minimum delay timer is configured for I-PDU */
  #endif
  #if (COM_TX_IPDU_GW == STD_ON)
  if(((LucConfig & COM_TX_SIG_GW_CONFIG_MASK) != COM_FALSE))
  {
    /* @Trace: Com_SUD_API_00970 */
    LusLocalTxIpduStatusBit |= COM_TX_RETRY_STATUS_MASK;
    *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
    *LucTransmitFlag = COM_FALSE;
  }
  #endif
  #if (COM_TX_IPDU_DM == STD_OFF)
  COM_UNUSED_PTR(LpTxMode);
  #endif
  #if (COM_TX_IPDU_MINDELAY_ENABLED == STD_OFF) && \
    (COM_TX_IPDU_GW == STD_OFF)
  COM_UNUSED_PTR(LucTransmitFlag);
  #endif
  #if (COM_TX_IPDU_MINDELAY_ENABLED == STD_OFF)
  COM_UNUSED(LucIpduConfig);
  #endif
  #if (((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
    (COM_TX_IPDU_REPETITION == STD_ON)) && \
    (COM_TX_IPDU_GW == STD_OFF))
  COM_UNUSED(LucConfig);
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxRequest                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function triggers the I-PDU with the given ID  **
*                         for transmission.                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-IDs.                    **
**                                                                            **
** Input Parameters     : LpTxIpdu                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : It shall only be used from within I-PDU callout.    **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxIpdu              **
**                                                 Com_GaaTxMode              **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxReptCount         **
**                                                 Com_GaaTxDMTimer           **
**                                                 Com_GaaTxMDTimer           **                                                   
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_Transmit()             **
**                                                 Com_TxIpduTMSCalc          **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
  (COM_TX_IPDU_REPETITION == STD_ON) || \
  (COM_TX_IPDU_GW == STD_ON))
FUNC(Std_ReturnType, COM_CODE) Com_TxRequest(
  PduIdType LddTxPduId, uint8 LucConfig)
#else
FUNC(Std_ReturnType, COM_CODE) Com_TxRequest(PduIdType LddTxPduId)
#endif
{
  /* @Trace: Com_SUD_API_00954 */
  /* Pointer to Tx mode structure */
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  /* Local variable to store return value */
  Std_ReturnType LenReturnValue;
  #if ((COM_TX_IPDU_DM == STD_ON) || \
    (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
    (COM_TX_IPDU_GW == STD_ON) || \
    (COM_TX_IPDU_TMS_SIG_BASED == STD_ON))
  /* Local variable to store Ipdu config */
  uint8 LucIpduConfig;
  #endif
  #if(COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC)
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #endif

  /* Initialize IpduStatusBit */
  uint16 LusTxIpduStatusBit = (uint16)COM_ZERO;

  /* Local variable to store transmit flag */
  /* Initialize Transmit Flag */  
  uint8 LucTransmitFlag = COM_FALSE;

  /* Initializing return value to zero */
  LenReturnValue = (uint8)E_OK;
  /* Get the pointer to Tx Ipdu */
  LpTxIpdu = &Com_GaaTxIpdu[LddTxPduId];
  /* Get the pointer to True Tx mode */
  LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
  #if ((COM_TX_IPDU_DM == STD_ON) || \
    (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
    (COM_TX_IPDU_GW == STD_ON) || \
    (COM_TX_IPDU_TMS_SIG_BASED == STD_ON))
  /* Get the Tx Ipdu configuration */
  LucIpduConfig = LpTxIpdu->ucTxConfig;
  #endif
  #if (COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
  if((LucIpduConfig & COM_TX_IPDU_TMS_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00955 */
    LucTransmitFlag = Com_TxIpduTMSCalc(LddTxPduId, LucConfig);
    if(LucTransmitFlag == COM_MODE_TRANSMIT_MASK)
    {
      /* @Trace: Com_SUD_API_00956 */
      LpTxMode = 
      &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
    }
  }
  else
  {
    #if(COM_TX_IPDU_TMS_EXPLICIT == STD_ON)
    if((Com_GaaTxIpduStatusBit[LddTxPduId] & COM_TX_TMS_STATUS_MASK)
                                                                   == COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00957 */
      LpTxMode = 
      &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
    }
    #endif
    if(((LpTxMode->ucTxMode > COM_TX_PERIODIC_MODE)))
    {
      /* @Trace: Com_SUD_API_00958 */
      LucTransmitFlag = COM_TRUE;
    }
  }
  #else
  {
    #if(COM_TX_IPDU_TMS_EXPLICIT == STD_ON)
    if((Com_GaaTxIpduStatusBit[LddTxPduId] & COM_TX_TMS_STATUS_MASK)
                                                                   == COM_FALSE)
    {
      /* @Trace: Com_SUD_API_01685 */
      LpTxMode = 
      &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
    }
    #endif
    if(((LpTxMode->ucTxMode > COM_TX_PERIODIC_MODE)))
    {
      /* @Trace: Com_SUD_API_01686 */
      LucTransmitFlag = COM_TRUE;
    }
  }  
  #endif
  if((LucTransmitFlag & (COM_ONE)) != COM_FALSE)
  {
    #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON)||(COM_TX_IPDU_DM == STD_ON) \
       ||(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
       (COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || \
       (COM_TX_IPDU_REPETITION == STD_ON) || \
       (COM_TX_IPDU_GW == STD_ON))
    /* @Trace: Com_SUD_API_00961 */
    LusTxIpduStatusBit = Com_GaaTxIpduStatusBit[LddTxPduId];
    #endif
    
    #if (COM_TX_IPDU_REPETITION == STD_ON)
    Com_InitReptTxMode(LpTxMode, LpTxIpdu, &LusTxIpduStatusBit, LucConfig);
    #endif

    #if ((COM_TX_IPDU_DM == STD_ON) || \
      (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
      (COM_TX_IPDU_GW == STD_ON))
    #if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
      (COM_TX_IPDU_REPETITION == STD_ON) || \
      (COM_TX_IPDU_GW == STD_ON))
    /* @Trace: Com_SUD_API_01514 */ 
    Com_ProcessWithMdtOrDm(LpTxIpdu, LpTxMode, &LusTxIpduStatusBit, 
      &LucTransmitFlag, LucIpduConfig, LucConfig);
    #else
    /* @Trace: Com_SUD_API_01515 */
    Com_ProcessWithMdtOrDm(LpTxIpdu, LpTxMode, &LusTxIpduStatusBit, 
      &LucTransmitFlag, LucIpduConfig);
    #endif
    #endif
    /* @Trace: Com_SUD_API_00971 */
    /* #2275 : Polyspace Runtime Error Red fixed */
    SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    
    #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON)||(COM_TX_IPDU_DM == STD_ON) \
       ||(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
       (COM_TX_IPDU_REPETITION == STD_ON) || \
       (COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || \
       (COM_TX_IPDU_GW == STD_ON))
    Com_GaaTxIpduStatusBit[LddTxPduId] = LusTxIpduStatusBit;
    #endif

    
    /* Invoke the Com_Transmit() function to transmit an I-PDU to the lower
    layer */
    #if ((COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || (COM_TX_IPDU_GW == STD_ON))
    if(LucTransmitFlag != COM_FALSE)
    #endif
    {
      #if((STD_ON == COM_MULTI_CORE_SUPPORT) && \
        (COM_GLOBAL_TRANSMIT_MODE_SELECTION != COM_TX_MAINFUNC))
        /* @Trace: Com_SUD_API_01516 */
      LenReturnValue = Com_TransmitIpdu(LpTxMode, &LusTxIpduStatusBit, 
        LddTxPduId, CoreId);
      #else
      /* @Trace: Com_SUD_API_01517 */
      LenReturnValue = Com_TransmitIpdu(LpTxMode, &LusTxIpduStatusBit, 
        LddTxPduId);
      #endif
    }
    
    /* @Trace: Com_SUD_API_00976 */
    SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
  }/* if(LucTransmitFlag == COM_TRUE) */
  /* @Trace: Com_SUD_API_00977 */
  return(LenReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_SendSigTMS                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                        It validates TMS for a signal when Com_SendSignal   ** 
**                        is called Ipdu callout                              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : SignalDataPtr,LpTxSignal                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  None                      **  
**                        Function(s) invoked    :  SchM_Enter_xxx()          **
**                                                  SchM_Exit_xxx             **                                                                                       
*******************************************************************************/
#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSigTMS(P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST)
  LpTxSignal, P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr)
{
  /* @Trace: Com_SUD_API_00978 */
  /* Pointer to Filter structure */
  P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST) LpFilter;
  uint8 LucSigConfig;
  uint16 LddPeriod;
  LucSigConfig = LpTxSignal->ucTxSigConfig;
  /* Check whether filter is configured */
  if((LucSigConfig & COM_TX_SIG_FILTER_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00979 */
    LddPeriod = LpTxSignal->usPeriod;
    LpFilter =(P2CONST(Com_FilterNever, AUTOMATIC, COM_CONST))
    (LpTxSignal->pFilter);
    /* Invoke filter function and get the return value */
    /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
    when Rx Timeout is occurred - Fixed by AUTRON START*/ 
    /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    /* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    if(COM_TRUE == 
      (LpFilter->pFilterFuncPtr)(LpFilter, SignalDataPtr, COM_ZERO, LddPeriod))
    /* Reset the previous value in MASKED_NEW_DIFFERS_MASKED_OLD filter, 
    when Rx Timeout is occurred - Fixed by AUTRON END*/   
    {
      /* @Trace: Com_SUD_API_00980 */
      /* Signal bit(1ST bit) will be turned true */
      LucSigConfig |= COM_TX_SIG_TMS_STATUS_MASK;
      /* Enter protection area */
      SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
      /* Set the filter status to true */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      *(LpFilter->pFilterStatus) |= (LpFilter->ucFltrStsMask);
      /* Exit protection area */
      SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
    }
    else
    {
      /* @Trace: Com_SUD_API_00981 */
      /* Enter protection area */
      SchM_Enter_Com_TX_TMS_STATUS_PROTECTION_AREA();
      /* Set the filter status to false */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      *(LpFilter->pFilterStatus) &= (uint8) (~(LpFilter->ucFltrStsMask));
      /* Exit protection area */
      SchM_Exit_Com_TX_TMS_STATUS_PROTECTION_AREA();
    }
    /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Initialized pointer */
    /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
    
    /* #3434 cyclic PDU handling in case of TMS switch */
    if((uint8)(LucSigConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK) == 
    COM_TX_SIG_PENDING_PROPERTY)
    {
      /* @Trace: Com_SUD_API_00982 */
      (void)Com_TxIpduTMSCalc(LpTxSignal->ddTxIpduIndex, LucSigConfig);
    }
  } /* Check whether filter is configured */
  /* @Trace: Com_SUD_API_00983 */
  return(LucSigConfig);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxIpduTMSSearch                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxIpduTMSCalc                   **
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
#if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) && (COM_TX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COM_CODE) Com_TxIpduTMSSearch(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_00986 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpFilterStatus;
  uint8 LucFltrStatusCount;
  uint8 LucFilterStatusIndex;
  boolean LblFilterResult;
  LblFilterResult = COM_FALSE;
  /* Get the pointer to filter status */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  LucFilterStatusIndex = LpTxIpdu->pTxModeSelect->ucFilterStatusIndex;
  LpFilterStatus =
    &Com_GaaFilterStatus[LucFilterStatusIndex];
  /* Get the counter */
  LucFltrStatusCount = LpTxIpdu->pTxModeSelect->ucFilterStatusCount;
  /* Loop for all the signals configured for filtering */
  do
  {
    /* @Trace: Com_SUD_API_00987 */
    /* Decrement the filter status count */
    LucFltrStatusCount--;
    /* Check whether filter status is set to true */
    if(*LpFilterStatus != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00988 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
      /* Set filter status count to zero to break the loop */
      LucFltrStatusCount = COM_ZERO;
    }

    /* Increment the filter status pointer to point to n filter status
        area */
    /* @Trace: Com_SUD_API_00989 */
    LucFilterStatusIndex++;
    LpFilterStatus =
    &Com_GaaFilterStatus[LucFilterStatusIndex];
  }while(LucFltrStatusCount != COM_ZERO);

  /* @Trace: Com_SUD_API_01597 */
  return LblFilterResult;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxIpduStatusUpdate                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TxIpduTMSCalc                   **
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
#if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) && (COM_TX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_TxIpduStatusUpdate(
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LucTransmitFlag,
  P2VAR(uint16, AUTOMATIC, COM_VAR) LusTxIpduStatusBit)
{
  /* @Trace: Com_SUD_API_01518 */
  uint8 LucLocalTransmitFlag;
  uint16 LusLocalTxIpduStatusBit;
  LucLocalTransmitFlag = *LucTransmitFlag;
  LusLocalTxIpduStatusBit = *LusTxIpduStatusBit;
  /* Check whether transmission mode is none */
  if((LpTxMode->ucTxMode != COM_TX_NONE_MODE) && (LpTxMode->ucTxMode != 
  COM_TX_PERIODIC_MODE))
  {
    /* @Trace: Com_SUD_API_00992 */
    /* Transmission flag true */
    LucLocalTransmitFlag |= COM_TRUE;
    *LucTransmitFlag = LucLocalTransmitFlag;
  }
  #if (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
  /* Check whether minimum delay timer is configured */
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00993 */
    /* Clear Tx Pending Status Mask */
    LusLocalTxIpduStatusBit &= (uint16)(COM_TX_PENDING_STATUS_CLEAR_MASK);
    *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
  }
  #endif
  /* Check whether its periodic or mixed */
  if((LpTxMode->ucTxMode <= COM_TX_MIXEDNTIMES_MODE) &&
      (LpTxMode->ucTxMode != COM_TX_NONE_MODE))
  {
    /* @Trace: Com_SUD_API_00994 */
    /* Set status bit to reset periodic timer */
    LusLocalTxIpduStatusBit |= COM_TX_PT_STATUS_MASK;
    *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
  }
  else
  {
    /* @Trace: Com_SUD_API_00995 */
    /* Clear Periodic timer status bit */
    LusLocalTxIpduStatusBit &= (uint16)(COM_TX_PT_STATUS_CLEAR_MASK);
    *LusTxIpduStatusBit = LusLocalTxIpduStatusBit;
  }
  #if (COM_TX_IPDU_MINDELAY_ENABLED == STD_OFF)
  COM_UNUSED_PTR(LpTxIpdu);
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxIpduTMSCalc                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal function to calculate transmission mode    **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LddTxPduId                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaTxIpduStatusBit,       **
**                                              Com_GaaFilterStatus           **
**                                              Com_GaaTxIpdu                 **
**                                              Com_GaaTxMode                 **
**                        Function(s) invoked : SchM_Enter_xxx,               **
**                                              SchM_Exit_xxx                 **
*******************************************************************************/
#if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) && (COM_TX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_TxIpduTMSCalc(PduIdType LddTxPduId, uint8 LucConfig)
{
  /* @Trace: Com_SUD_API_00984 */
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  uint16 LusTxIpduStatusBit;
  boolean LblFilterResult;
  uint8 LucTransmitFlag;
  uint8 LucTMSResult;  
  LucTransmitFlag = COM_ZERO;
  LblFilterResult = COM_TRUE;
  LucTMSResult = (LucConfig & COM_TX_SIG_TMS_STATUS_MASK);
  /* Get the pointer to Tx Ipdu */
  LpTxIpdu = &Com_GaaTxIpdu[LddTxPduId];  
  /* Get the pointer to True Tx mode */
  LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
  if(((Com_GaaTxIpduStatusBit[LddTxPduId] & COM_TX_TMS_STATUS_MASK) !=
                                                                LucTMSResult))
  {
    /* @Trace: Com_SUD_API_00985 */
    SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
    LusTxIpduStatusBit = Com_GaaTxIpduStatusBit[LddTxPduId];
    /* Initialize filter status to false */
    LblFilterResult = COM_FALSE;
    if(COM_FALSE == LucTMSResult)
    {
      /* @Trace: Com_SUD_API_01504 */
      LblFilterResult = Com_TxIpduTMSSearch(LpTxIpdu);

      /* Check whether filter result is set to true */
      if(COM_FALSE == LblFilterResult)
      {
        /* @Trace: Com_SUD_API_00990 */
        LusTxIpduStatusBit &= (uint16)(COM_TX_TMS_STATUS_CLEAR_MASK);
        /* Get the pointer to false Tx mode */
        LpTxMode = 
        &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
        LucTransmitFlag |= COM_FALSE_MODE_INDICATION_MASK;
      }
    }
    else
    {
      /* @Trace: Com_SUD_API_00991 */
      /* Set True Mode Status */
      LusTxIpduStatusBit |= COM_TX_TMS_STATUS_MASK;
    }
    /* Check whether filter output is false */
    if(COM_FALSE == LblFilterResult)
    {
      /* @Trace: Com_SUD_API_01505 */
      Com_TxIpduStatusUpdate(LpTxMode, LpTxIpdu, &LucTransmitFlag, 
        &LusTxIpduStatusBit);
    }
    /* @Trace: Com_SUD_API_00996 */
    /* Update the status bits into global variable */
    Com_GaaTxIpduStatusBit[LddTxPduId] = LusTxIpduStatusBit;
    SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
  }
  else if(COM_FALSE == LucTMSResult)
  {
    /* @Trace: Com_SUD_API_00997 */
    /* Get the pointer to false transmission mode */
    LpTxMode = 
    &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex+(PduIdType)COM_ONE];
    LucTransmitFlag |= COM_FALSE_MODE_INDICATION_MASK;
  }
  else
  {
    /* To avoid QAC warning */
  }
  if(COM_TRUE == LblFilterResult)
  {
    if(((LucConfig & COM_TX_SIG_PROPERTY_CONFIG_MASK) >
        COM_TX_SIG_PENDING_PROPERTY) &&
       ((LpTxMode->ucTxMode > COM_TX_PERIODIC_MODE)))
    {
      /* @Trace: Com_SUD_API_00998 */
      LucTransmitFlag |= COM_TRUE;
    }
  }  
  /* @Trace: Com_SUD_API_00999 */
  return(LucTransmitFlag);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
