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
**  SRC-MODULE: Com_TPCbk.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of TP callback functions and their functionality.   **
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
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.6.0   10-Dec-2022   PhucNHM     CP44-1243                              **
** 1.1.4     02-Jun-2022   DuyNHP2     R44-Redmine #27636 #28007              **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     25-Apr-2022   PhucNHM     R44-Redmine #25516 #25654              **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

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
#include "string.h"       /* memcpy() */
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

#if((COM_RX_TP_SUPPORT == STD_ON)|| (COM_TX_TP_SUPPORT == STD_ON))
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/

#if(COM_RX_TP_SUPPORT == STD_ON)
#if((COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
  (COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
  (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TpRxInd_ProcIpduCnt(PduIdType ComRxPduId, 
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
  (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ProcessRxSignalAndGW(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, 
  PduIdType ComRxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_TpRxInd_InputValidate(PduIdType ComRxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#if(COM_RX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ProcessIpduCallout(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, PduIdType ComRxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TpRxInd_UpdateRxIpduSts(PduIdType ComRxPduId, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData_ProcDynBuff(
  PduIdType ComRxPduId, P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_DEV_ERROR_DETECT == STD_ON)
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_CopyRxData_InputValidate(PduIdType ComRxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2CONST(PduLengthType, AUTOMATIC, COM_CONST) RxBufferSizePtr,
  P2VAR(BufReq_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#if (COM_META_DATA_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_StartOfRcpt_CopyMetaData(
  BufReq_ReturnType LddReturnValue,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2CONST(Com_RxPduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr,
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_StartOfRcpt_InputValidate(PduIdType ComRxPduId, 
  P2CONST(PduLengthType, AUTOMATIC, COM_CONST) RxBufferSizePtr,
  P2VAR(BufReq_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if (CPU_TYPE == CPU_TYPE_8)
FUNC(uint8, COM_CODE) Com_StartOfRcpt_ProcDynBuff(
  PduIdType ComRxPduId, PduLengthType TpSduLength, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr);
#elif (CPU_TYPE == CPU_TYPE_16)
FUNC(uint16, COM_CODE) Com_StartOfRcpt_ProcDynBuff(
  PduIdType ComRxPduId, PduLengthType TpSduLength, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr);
#elif (CPU_TYPE == CPU_TYPE_32)
FUNC(uint32, COM_CODE) Com_StartOfRcpt_ProcDynBuff(
  PduIdType ComRxPduId, PduLengthType TpSduLength, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_StartOfRcpt_ProcDynBuff                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartOfReception                **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if (CPU_TYPE == CPU_TYPE_8)
FUNC(uint8, COM_CODE) Com_StartOfRcpt_ProcDynBuff(
  PduIdType ComRxPduId, PduLengthType TpSduLength, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr)
#elif (CPU_TYPE == CPU_TYPE_16)
FUNC(uint16, COM_CODE) Com_StartOfRcpt_ProcDynBuff(
  PduIdType ComRxPduId, PduLengthType TpSduLength, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr)
#elif (CPU_TYPE == CPU_TYPE_32)
FUNC(uint32, COM_CODE) Com_StartOfRcpt_ProcDynBuff(
  PduIdType ComRxPduId, PduLengthType TpSduLength, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr)
#endif
{
  #if (CPU_TYPE == CPU_TYPE_8)
  /* @Trace: Com_SUD_API_01467 */
  uint8 LucPduInfoPtr;
  #elif (CPU_TYPE == CPU_TYPE_16)
  /* @Trace: Com_SUD_API_01468 */
  uint16 LucPduInfoPtr;
  #elif (CPU_TYPE == CPU_TYPE_32)
  /* @Trace: Com_SUD_API_01469 */
  uint32 LucPduInfoPtr;
  #endif

  /* @Trace: Com_SUD_API_01599 */
  PduLengthType LdTpLength;

  P2CONST(Com_RxPduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr;
  LpPduInfoPtr = NULL_PTR;

  if (TpSduLength == 0)
  {
    /* @Trace: Com_SUD_API_00860 */
    LdTpLength = LpRxTPIpdu->ddRxTPMaxIpduSize;
  }
  else
  {
    /* @Trace: Com_SUD_API_00861 */
    LdTpLength = TpSduLength;
  }

  #if((COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON))
  /* Polyspace Useless if [A defect:Low] this is a base code,
    * Com_GaaRxTPIIpdu is verified and generated by Generator 
    Toolare verified and generated by Generator Tool */
  if((LpRxTPIpdu->pDoubleIpduBuffer) != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_00862 */
    /* Get the pointer to temporary internal buffer if counter or 
    replication is configured */
    LpPduInfoPtr = LpRxTPIpdu->pDoubleIpduBuffer;
  }
  else
  #endif
  {
    /* @Trace: Com_SUD_API_00863 */
    /* Get the pointer to internal buffers */
    LpPduInfoPtr = &Com_GaaRxPduInfoPtr[ComRxPduId];
  }
  /* @Trace: Com_SUD_API_00864 */
  /* Store the size of the (dynamic) Ipdu */
  /* COM656 */
  *LpPduInfoPtr->SduLength = LdTpLength;
  /* Update length */
  /* COM657 */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  *RxBufferSizePtr = (PduLengthType) LpRxTPIpdu->ddRxTPMaxIpduSize;

  /* Set the TP buffer status to "locked" */
  Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] |= 
                                        LpRxTPIpdu->ucRxTPStatusMask;

  /* polyspace-begin MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  #if (CPU_TYPE == CPU_TYPE_8)
  /* @Trace: Com_SUD_API_01470 */
  LucPduInfoPtr = (uint8)LpPduInfoPtr;
  #elif (CPU_TYPE == CPU_TYPE_16)
  /* @Trace: Com_SUD_API_01471 */
  LucPduInfoPtr = (uint16)LpPduInfoPtr;
  #elif (CPU_TYPE == CPU_TYPE_32)
  /* @Trace: Com_SUD_API_01472 */
  LucPduInfoPtr = (uint32)LpPduInfoPtr;
  #endif
  /* polyspace-end MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* @Trace: Com_SUD_API_01473 */
  return LucPduInfoPtr;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_StartOfRcpt_InputValidate                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartOfReception                **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_StartOfRcpt_InputValidate(PduIdType ComRxPduId, 
  P2CONST(PduLengthType, AUTOMATIC, COM_CONST) RxBufferSizePtr,
  P2VAR(BufReq_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue)
{
  /* @Trace: Com_SUD_API_01474 */
  uint8 LucReturnValue;
  /* Initialize DET error flag to E_OK */
  LucReturnValue = (uint8)E_OK;  
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_STARTOFRECEPTION);
  /* Check whether Ipdu ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01676 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId, COMSERVICEID_STARTOFRECEPTION);
  #else
  /* @Trace: Com_SUD_API_01677 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG_PB(ComRxPduId,COMSERVICEID_STARTOFRECEPTION);
  #endif
  /* @Trace: Com_SUD_API_01678 */
  /* Check whether Ipdu ID is out of TP range */
  COM_DET_TP_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId, 
                                                 COMSERVICEID_STARTOFRECEPTION);
  /* Check whether input buffer is NULL  */
  COM_DET_COMMON_PTR_CHECK_FLAG(RxBufferSizePtr, COMSERVICEID_STARTOFRECEPTION);
  if(LucReturnValue != (uint8)E_OK)
  {
    /* @Trace: Com_SUD_API_00856 */
    *LpReturnValue = BUFREQ_E_NOT_OK;
  }
  /* @Trace: Com_SUD_API_01475 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_StartOfRcpt_CopyMetaData                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartOfReception                **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#if (COM_META_DATA_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_StartOfRcpt_CopyMetaData(
  BufReq_ReturnType LddReturnValue,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2CONST(Com_RxPduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr,
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu)
{
  /* Check metadata in PduInfoPointer and Com_GaaRxPduInfoPtr */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* polyspace +5 RTE:NIP [Not a defect:Low] "Pointer initialized with configuration data" */
  /* polyspace +4 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  if((BUFREQ_OK == LddReturnValue) && 
    (PduInfoPointer != NULL_PTR) &&
    (PduInfoPointer->MetaDataPtr != NULL_PTR) &&
    (LpPduInfoPtr->MetaDataPtr != NULL_PTR))
  {
    /* @Trace: Com_SUD_API_00867 */
    /*Copy Meta Data to internal Pdu Buffer*/
    /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointer are available and in range. this is assured by generator" */
    memcpy(
      (P2VAR(void, AUTOMATIC, COM_VAR))
      (LpPduInfoPtr->MetaDataPtr),
      (P2CONST(void, AUTOMATIC, COM_CONST))(PduInfoPointer->MetaDataPtr),
      LpRxIpdu->ddMetaDataLength); 
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_StartOfReception                                **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This function returns the pointer to the size of    **
**                        the AUTOSAR COM module�s internal receive buffer    **
**                        for the I-PDU with the ID ComRxPduId.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : ComRxPduId, TpSduLength                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RxBufferSizePtr                                     **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaRxIpdu              **
**                                                 Com_GaaRxTPIpdu            **
**                                                 Com_GaaRxTPStatus          **
**                                                 Com_GaaRxPduInfoPtr        **
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/
/* @Trace: SRS_Com_02091, SRS_Com_02094, SRS_Com_02095, SWS_Com_00657,
SWS_Com_00691*/

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02095*/
FUNC(BufReq_ReturnType, COM_CODE)
Com_StartOfReception(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer,
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr)
{
  /* @Trace: Com_SUD_API_00855 */
  #if (COM_META_DATA_SUPPORT != STD_ON)
  COM_UNUSED_PTR(PduInfoPointer);
  #endif
  /* Pointer to Ipdu Buffer */
  P2CONST(Com_RxPduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr;
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Pointer to Rx TP structure */
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  /* Return value */
  BufReq_ReturnType LddReturnValue;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  #endif  
  /* Initialize return value */
  LddReturnValue = BUFREQ_OK;
  /* Initialize PduInfo pointer */
  LpPduInfoPtr = NULL_PTR;

  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_StartOfRcpt_InputValidate(ComRxPduId, RxBufferSizePtr, 
    &LddReturnValue);
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    if(Com_GaaRxIpduStatus[ComRxPduId] != (PduIdType)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00857 */
      /* Get the pointer to  Rx Ipdu */
      LpRxIpdu = &Com_GaaRxIpdu[ComRxPduId];
      if (LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
      {
        /* @Trace: Com_SUD_API_00858 */
        /* Get the pointer to Rx TP structure */
        LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
        /* Check if buffer is locked */
        if(COM_ZERO == ((Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef]) & 
          (LpRxTPIpdu->ucRxTPStatusMask)))
        {
          /* If length is greater than maximum length for the Ipdu */
          if(TpSduLength > (LpRxTPIpdu->ddRxTPMaxIpduSize))
          {
            /* @Trace: Com_SUD_API_00859 */
            LddReturnValue = BUFREQ_E_OVFL;
          }
          else
          {
            /* @Trace: Com_SUD_API_01476 */
            /* polyspace +2 MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
            /* polyspace +1 CERT-C:INT36-C [Justified:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
            LpPduInfoPtr = (Com_RxPduInfoType *)Com_StartOfRcpt_ProcDynBuff(
              ComRxPduId, TpSduLength, LpRxTPIpdu, RxBufferSizePtr);
          }
        }
        else
        {
          /* @Trace: Com_SUD_API_00865 */
          LddReturnValue = BUFREQ_E_NOT_OK;
        }
      }
      else
      {
        /* @Trace: Com_SUD_API_00866 */
        LddReturnValue = BUFREQ_E_NOT_OK;
      }
      /* @Trace: Com_SUD_API_01477 */
      #if (COM_META_DATA_SUPPORT == STD_ON)
      Com_StartOfRcpt_CopyMetaData(LddReturnValue, PduInfoPointer, LpPduInfoPtr, LpRxIpdu);
      #endif
    }
    else
    {
      /* @Trace: Com_SUD_API_00868 */
      LddReturnValue = BUFREQ_E_NOT_OK; 
    }
  }
  /* @Trace: Com_SUD_API_00869 */
  #if(COM_META_DATA_SUPPORT == STD_OFF)
  COM_UNUSED_PTR(LpPduInfoPtr);
  #endif
  return(LddReturnValue);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Traceability END -- SRS: SWS_Com_00657, SWS_Com_00691*/

/*******************************************************************************
** Function Name        : Com_CopyRxData_InputValidate                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartOfReception                **
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
#if(COM_DEV_ERROR_DETECT == STD_ON)
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_CopyRxData_InputValidate(PduIdType ComRxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2CONST(PduLengthType, AUTOMATIC, COM_CONST) RxBufferSizePtr,
  P2VAR(BufReq_ReturnType, AUTOMATIC, COM_VAR) LpReturnValue)
{
  /* @Trace: Com_SUD_API_01478 */
  uint8 LucReturnValue;
  /* Initialize DET error flag to E_OK */
  LucReturnValue = (uint8)E_OK;  
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_COPYRXDATA);
  /* Check whether Ipdu ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01679 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId, COMSERVICEID_COPYRXDATA);
  #else
  /* @Trace: Com_SUD_API_01680 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG_PB(ComRxPduId, COMSERVICEID_COPYRXDATA);
  #endif
  /* @Trace: Com_SUD_API_01681 */
  /* Check whether input buffer is NULL  */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  COM_DET_PDUINFOPTR_LENGTH_CHECK_FLAG(PduInfoPointer, COMSERVICEID_COPYRXDATA);
  /* Check whether input buffer is NULL  */
  COM_DET_COMMON_PTR_CHECK_FLAG(RxBufferSizePtr, COMSERVICEID_COPYRXDATA);
  if(LucReturnValue != (uint8)E_OK)
  {
    /* @Trace: Com_SUD_API_00871 */
    *LpReturnValue = BUFREQ_E_NOT_OK;
  } 
  /* @Trace: Com_SUD_API_01479 */
  return LucReturnValue;
}  
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_CopyRxData_ProcDynBuff                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_CopyRxData                      **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData_ProcDynBuff(
  PduIdType ComRxPduId, P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr)
{
  /* @Trace: Com_SUD_API_01480 */
  BufReq_ReturnType LddReturnValue;
  /* Initialize return value */
  LddReturnValue = BUFREQ_OK;
  /* Pointer to Ipdu Buffer */
  P2CONST(Com_RxPduInfoType, AUTOMATIC, COM_CONST)
  LpPduInfoPtr;

  #if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)
  if((LpRxTPIpdu->pDoubleIpduBuffer) != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_00874 */
    LpPduInfoPtr = LpRxTPIpdu->pDoubleIpduBuffer;
  }
  else
  #endif
  {
    /* @Trace: Com_SUD_API_00875 */
    /* Get the pointer to PduInfoPtr structure */
    LpPduInfoPtr = &Com_GaaRxPduInfoPtr[ComRxPduId];
  }
  if ((Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef] +
      PduInfoPointer->SduLength) <= (*LpPduInfoPtr->SduLength))
  {
    /* Check if Ipdu has been started */
    if (Com_GaaRxIpduStatus[ComRxPduId] != (PduIdType)COM_ZERO)
    {
      if(PduInfoPointer->SduLength > COM_ZERO)
      {
        /* @Trace: Com_SUD_API_00876 */
        /* Copy data from PduR buffer to Com internal Ipdu Buffer */
        /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
        memcpy(
        (P2VAR(void, AUTOMATIC, COM_VAR))(&(LpPduInfoPtr->SduDataPtr
        [Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef]])), 
        (P2CONST(void, AUTOMATIC, COM_CONST))(PduInfoPointer->SduDataPtr),
        PduInfoPointer->SduLength);              
      }
      /* @Trace: Com_SUD_API_00877 */
      Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef] += 
      (PduLengthType)(PduInfoPointer->SduLength);
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
      *RxBufferSizePtr = (PduLengthType)(*LpPduInfoPtr->SduLength) -
                    Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef];
    }
    else
    {
      /* @Trace: Com_SUD_API_00878 */
      LddReturnValue = BUFREQ_E_NOT_OK;
    }
  }   
  else
  {
    /* @Trace: Com_SUD_API_00879 */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  /* @Trace: Com_SUD_API_01481 */
  return LddReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_CopyRxData                                      **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : Called once upon reception of each segment. Within  **
**                        this call, the received data is copied to the       **
**                        receive TP buffer. The API might only be called     **
**                        with an SduLength greater 0 if RxBufferSizePtr      **
**                        returned by the previous API call indicates         **
**                        sufficient receive buffer                           **
**                        (SduLength&lt= RxBufferSizePtr). The function must  **
**                        only be called if the connection has been accepted  **
**                        by an initial call to Com_StartOfReception.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddComRxpduId, PduInfoPointer                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RxBufferSizePtr                                     **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxIpdu              **
**                                                 Com_GaaRxTPIpdu            **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaRxPduInfoPtr        **
**                                                 Com_GaaRxIpduTPLength      **
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/

/* @Trace:SRS_Com_02091, SRS_Com_02094, SRS_Com_02095, SWS_Com_00692 */

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02095*/
FUNC(BufReq_ReturnType, COM_CODE)
Com_CopyRxData(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr)
{
  /* @Trace: Com_SUD_API_00870 */
  /* Pointer to Com_RxIpdu */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST)
  LpRxIpdu;
  /* Pointer to Rx TP structure */
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST)
  LpRxTPIpdu;
  /* Return value */
  BufReq_ReturnType LddReturnValue;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  #endif  
  /* Initialize return value */
  LddReturnValue = BUFREQ_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_CopyRxData_InputValidate(ComRxPduId, PduInfoPointer, 
    RxBufferSizePtr, &LddReturnValue);
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_00872 */
    /* Get the pointer to Rx Ipdu structure */
    LpRxIpdu = &Com_GaaRxIpdu[ComRxPduId];
    if (LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_00873 */
      /* Get the pointer to Rx TP structure */
      /* Polyspace Useless if [A defect:Low] this is a base code,
       * Com_GaaRxTPIIpdu is verified and generated by Generator 
       Toolare verified and generated by Generator Tool */
      LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];

      LddReturnValue = Com_CopyRxData_ProcDynBuff(ComRxPduId, LpRxTPIpdu, 
        PduInfoPointer, RxBufferSizePtr);
    }
  }
  /* @Trace: Com_SUD_API_00880 */
  return(LddReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Traceability END -- SRS: SRS_Com_02091, SRS_Com_02094, SRS_Com_02095,
SWS_Com_00692 */

/*******************************************************************************
** Function Name        : Com_CopyTxData_ValidateInput                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_CopyTxData                      **
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
#if(COM_DEV_ERROR_DETECT == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint8, COM_CODE) Com_CopyTxData_ValidateInput(
  PduIdType id, P2CONST(PduInfoType, AUTOMATIC, COM_CONST) info,
  P2CONST(RetryInfoType, AUTOMATIC, COM_CONST) retry, 
  P2CONST(PduLengthType, AUTOMATIC, COM_CONST) availableDataPtr)
{
  /* @Trace: Com_SUD_API_01482 */
  uint8 LucReturnValue = E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_COPYTXDATA);
  /* Check whether Ipdu ID is out of range */
  COM_DET_TXPDUID_RANGE_CHECK_FLAG(id, COMSERVICEID_COPYTXDATA);
  /* Check whether input buffer is NULL  */
  COM_DET_COMMON_PTR_CHECK_FLAG(availableDataPtr, COMSERVICEID_COPYTXDATA);
  if((info) == NULL_PTR)
  {
    /* @Trace: Com_SUD_API_00882 */
    (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,
                              COMSERVICEID_COPYTXDATA, COM_E_PARAM_POINTER);
    LucReturnValue = COM_SERVICE_NOT_AVAILABLE;
  }
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  else if(!((((info)->SduDataPtr) == NULL_PTR) && (retry == NULL_PTR)))
  {
    if(((info)->SduDataPtr) == NULL_PTR)
    {
      /* @Trace: Com_SUD_API_00883 */
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,
        COMSERVICEID_COPYTXDATA, COM_E_PARAM_POINTER);
      LucReturnValue = COM_SERVICE_NOT_AVAILABLE;
    }
  }
  else
  {
    /* Do nothing */
  }
  /* @Trace: Com_SUD_API_01483 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_CopyTxData_GetAvblLength                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_CopyTxData                      **
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
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_DYN_SUPPORT == STD_ON)
static FUNC(PduLengthType, COM_CODE) Com_CopyTxData_GetAvblLength(
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr, 
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
#else
static FUNC(PduLengthType, COM_CODE) Com_CopyTxData_GetAvblLength(
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr)
#endif
{
  /* @Trace: Com_SUD_API_01484 */
  PduLengthType LdAvailableLength;
  /* Update the length parameter with the remaining number of before copy*/
  #if(COM_TX_DYN_SUPPORT == STD_ON)
  /* #2142 : separate DYN PDU from TP */
  if((LpTxIpdu->ucIpduType == COM_DYN_IPDU) && 
                (LpTxIpdu->ddTxIpduDynLegthRef != COM_INVALID_TXID_PARAM))
  {
    /* @Trace: Com_SUD_API_00887 */
    /* polyspace +3 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    LdAvailableLength = (PduLengthType)(LpTxIpdu->ddTxNonDynLength  + 
      Com_GaaTxDynSigLength[LpTxIpdu->ddTxIpduDynLegthRef] - 
      Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef]);
  }
  else
  #endif
  {
    /* @Trace: Com_SUD_API_00888 */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    LdAvailableLength = (PduLengthType)(LpPduInfoPtr->SduLength - 
                    Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef]);
  }
  /* @Trace: Com_SUD_API_01485 */
  return LdAvailableLength;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_CopyTxData_RetryPreProcess                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_CopyTxData                      **
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
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COM_CODE) Com_CopyTxData_RetryPreProcess(
  P2CONST(RetryInfoType, AUTOMATIC, COM_CONST) retry)
{
  /* @Trace: Com_SUD_API_01486 */
  boolean LucRetryData;

  if(retry == NULL_PTR)
  {
    /* @Trace: Com_SUD_API_00890 */
    LucRetryData = COM_FALSE;
  }
  else
  {
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    if(TP_DATARETRY == retry->TpDataState)
    {
      /* @Trace: Com_SUD_API_00891 */
      LucRetryData = COM_TRUE;
    }
    else
    {
      /* @Trace: Com_SUD_API_00892 */
      LucRetryData = COM_FALSE;
    }
  }
  /* @Trace: Com_SUD_API_01487 */
  return LucRetryData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_CopyTxData_RetryProcessTrue                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_CopyTxData                      **
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
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, COM_CODE)  Com_CopyTxData_RetryProcessTrue(
  P2CONST(RetryInfoType, AUTOMATIC, COM_CONST) retry, 
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) info, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) availableDataPtr, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr)
{
  /* @Trace: Com_SUD_API_01488 */
  BufReq_ReturnType LddReturnValue;
  LddReturnValue = BUFREQ_OK;
  PduLengthType LdAvailableLength;

  if((retry->TxTpDataCnt != COM_ZERO) && 
    (retry->TxTpDataCnt <= 
                Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef]))
  {
    /* @Trace: Com_SUD_API_00893 */
    /* get index of when retry is call (sws 00693) */
    Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef] = 
        Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef] - 
                                    (PduLengthType)(retry->TxTpDataCnt);
    /* copy data retry to info->SduDataPtr */
    /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
    memcpy(
    (P2VAR(void, AUTOMATIC, COM_VAR))(info->SduDataPtr), 
    (P2CONST(void, AUTOMATIC, COM_CONST))
                      (&(LpPduInfoPtr->SduDataPtr[Com_GaaTxIpduTPLength
    [LpTxTPIpdu->ucTxIpduTPLengthRef]])),        
    info->SduLength);
    /* Update the length parameter with the remaining number of bytes 
    yet to be copied */
    Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef] += 
                                                        info->SduLength;
    /* Calculate available length after copy data */
    LdAvailableLength = (PduLengthType)(LpPduInfoPtr->SduLength - 
                Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef]);
    /* Update availble length to argument  */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    *availableDataPtr = LdAvailableLength;
  }
  else /* if retry->TpDataState is RETRY but TxTpDataCnt = 0 or 
        TxTpDataCnt > actual written TxIpdu length */
  {
    /* @Trace: Com_SUD_API_00894 */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  /* @Trace: Com_SUD_API_01489 */
  return LddReturnValue;  
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_CopyTxData_RetryProcFalse                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_CopyTxData                      **
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
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_DYN_SUPPORT == STD_ON)
static FUNC(BufReq_ReturnType, COM_CODE)  Com_CopyTxData_RetryProcFalse(
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu, 
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) info, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) availableDataPtr, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr,
  PduLengthType LdAvailableLength)
#else
static FUNC(BufReq_ReturnType, COM_CODE)  Com_CopyTxData_RetryProcFalse(
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) info, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) availableDataPtr, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) LpPduInfoPtr,
  PduLengthType LdAvailableLength)
#endif
{
  /* @Trace: Com_SUD_API_01490 */
  BufReq_ReturnType LddReturnValue;
  LddReturnValue = BUFREQ_OK;

  if(LdAvailableLength < info->SduLength )
  {
    /* @Trace: Com_SUD_API_00895 */
    LddReturnValue = BUFREQ_E_BUSY;
  }
  else /* LdAvailableLength > info->SduLength  */
  {
    /* @Trace: Com_SUD_API_00896 */
    /* Copy data from internal buffer to the buffer 
      * specified by PduR */
    /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
    memcpy(
      (P2VAR(void, AUTOMATIC, COM_VAR))(info->SduDataPtr), 
      (P2CONST(void, AUTOMATIC, COM_CONST))
      (&(LpPduInfoPtr->SduDataPtr[Com_GaaTxIpduTPLength
      [LpTxTPIpdu->ucTxIpduTPLengthRef]])) ,        
      info->SduLength);

    /* Update the length parameter with the remaining number
      * of bytes yet to be copied */
    /* Update the number of bytes already copied */
    Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef] += 
      (PduLengthType)(info->SduLength);
    #if(COM_TX_DYN_SUPPORT == STD_ON)
    /* #2142 : separate DYN PDU from TP */
    if((LpTxIpdu->ucIpduType == COM_DYN_IPDU) && 
      (LpTxIpdu->ddTxIpduDynLegthRef != COM_INVALID_TXID_PARAM))
    {
      /* @Trace: Com_SUD_API_00897 */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
      *availableDataPtr = (PduLengthType)(LpTxIpdu->ddTxNonDynLength + 
        Com_GaaTxDynSigLength[LpTxIpdu->ddTxIpduDynLegthRef] - 
        Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef]);
    }
    else
    #endif
    {
      /* @Trace: Com_SUD_API_00898 */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
      *availableDataPtr = (PduLengthType)(LpPduInfoPtr->SduLength - 
        Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef]);
    }      
  }
  /* @Trace: Com_SUD_API_01491 */
  return LddReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_CopyTxData                                      **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : At invocation of Com_CopyTxData the AUTOSAR COM     **
**                        module copy the requested transmit data of the      **
**                        large IPDU with ID PduId from its internal transmit **
**                        buffer to the location specified by the PduInfoPtr. **
**                        The function Com_CopyTxData also calculates and     **
**                        sets the TxDataCntPtr to the amount of remaining    **
**                        bytes for the transmission of this large I-PDU.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : PduId, PduInfoPtr, RetryInfoPtr                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : TxDataCntPtr                                        **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxPduInfoPtr        **
**                                                 Com_GaaTxIpduTPLength      **
**                                                 Com_GaaTxDynSigLength      **
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/
/* @Trace: SRS_Com_02091, SRS_Com_02094, SRS_Com_02095, SWS_Com_00693 */

#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02095*/
/* polyspace:begin<MISRA-C:16.7:Not a defect:Justify 
with annotations> Not a defect, AUTOSAR specification */
FUNC(BufReq_ReturnType, COM_CODE)
Com_CopyTxData(PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) info,
  P2CONST(RetryInfoType, AUTOMATIC, COM_CONST) retry, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) availableDataPtr)
{
  /* @Trace: Com_SUD_API_00881 */
  /* Available length of this IPDU */
  PduLengthType LdAvailableLength;
  /* Cnt index when retry state is TP_DATARETRY */
  boolean LucRetryData;
  /*PduLengthType LdTxTpCntIndex;*/
  /* Pointer to Ipdu Buffer */
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR)
  LpPduInfoPtr;
  /* Pointer to Com_TxIpdu */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST)
  LpTxIpdu;
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST)
  LpTxTPIpdu;
  /* Return value */
  BufReq_ReturnType LddReturnValue;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  #endif    
  LddReturnValue = BUFREQ_OK;
  #if(COM_DEV_ERROR_DETECT == STD_ON)

  LucReturnValue = Com_CopyTxData_ValidateInput(id, info, retry, 
    availableDataPtr);

  if(LucReturnValue != (uint8)E_OK)
  {
    /* @Trace: Com_SUD_API_00884 */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  if((uint8)E_OK == LucReturnValue)
  #endif
  {  
    /* @Trace: Com_SUD_API_00885 */  
    /* Get pointer to Ipdu structure */
    LpTxIpdu = &Com_GaaTxIpdu[id];
    /* Get the pointer to TP structure  */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    /* Check if Ipdu has been started */
    if((PduIdType)COM_ZERO != Com_GaaTxIpduStatus[id])
    {
      /* @Trace: Com_SUD_API_00886 */
      /* Get the pointer to PduInfoPtr structure */
      LpPduInfoPtr = &Com_GaaTxPduInfoPtr[id];   

      #if(COM_TX_DYN_SUPPORT == STD_ON)
      /* @Trace: Com_SUD_API_01492 */
      LdAvailableLength = Com_CopyTxData_GetAvblLength(LpTxTPIpdu, LpPduInfoPtr, 
        LpTxIpdu);
      #else
      /* @Trace: Com_SUD_API_01493 */
      LdAvailableLength = Com_CopyTxData_GetAvblLength(LpTxTPIpdu, LpPduInfoPtr);
      #endif
      /* An info->SduLength = 0 and retry = NULL for check the 
       remaining number of bytes that are available */
      if((info)->SduLength == 0)
      {
        /* @Trace: Com_SUD_API_00889 */
        /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
        *availableDataPtr = LdAvailableLength;
      }
      else
      {
        /* @Trace: Com_SUD_API_01494 */
        LucRetryData = Com_CopyTxData_RetryPreProcess(retry);

        if(COM_TRUE == LucRetryData)
        {
          /* @Trace: Com_SUD_API_01495 */
          LddReturnValue = Com_CopyTxData_RetryProcessTrue(retry, LpTxTPIpdu, 
            info, availableDataPtr, LpPduInfoPtr);
        }
        else
        {
          #if(COM_TX_DYN_SUPPORT == STD_ON)
          /* @Trace: Com_SUD_API_01496 */
          LddReturnValue = Com_CopyTxData_RetryProcFalse(LpTxTPIpdu, 
            LpTxIpdu, info, availableDataPtr, LpPduInfoPtr, LdAvailableLength);
          #else
          /* @Trace: Com_SUD_API_01497 */
          LddReturnValue = Com_CopyTxData_RetryProcFalse(LpTxTPIpdu, 
            info, availableDataPtr, LpPduInfoPtr, LdAvailableLength);
          #endif
        } 
      }
    }
    else
    {
      /* @Trace: Com_SUD_API_00899 */
      LddReturnValue = BUFREQ_E_NOT_OK;
    }
  }
  /* @Trace: Com_SUD_API_00900 */
  return(LddReturnValue);
}
/* polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations> 
Not a defect, AUTOSAR specification */

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Traceability END -- SRS: SRS_Com_02091, SRS_Com_02094, SRS_Com_02095,
SWS_Com_00693 */

/*******************************************************************************
** Function Name        : Com_ProcessRxSignalAndGW                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TPRxIndication                  **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
  (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ProcessRxSignalAndGW(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, 
  PduIdType ComRxPduId)
{
  /* @Trace: Com_SUD_API_01498 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  /* Clear Com_GaaMulticoreTriggerNotifyFlag before call Com_RxSigProcessing */
  Com_ClearTriggerNotifyFlag(COM_TRUE);
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #if(COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON)
  /* Check whether Rx  signals are present */
  if(LpRxIpdu->usNoOfRxSignal != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00917 */ 
    /* Invoke Com_RxSigProcessing() function to process 
      Rx signals */
    Com_RxSigProcessing(LpRxIpdu, 
    *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength);
  }
  #endif

  #if(COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON)
  /* Check whether Rx signal groups are present */
  if(LpRxIpdu->ucNoOfRxSigGroup != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00918 */ 
    Com_RxSigGrpProcessing(LpRxIpdu, 
      *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength);
  }
  #endif

  #if((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) && \
    (COM_RX_SIG_GATEWAY == STD_ON))
  /* Check whether signal based gateway is configured */
  if((LpRxIpdu->ucRxConfig & COM_RX_IPDU_GATEWAY_CONFIG_MASK) != 
                                                    COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00919 */ 
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
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  /* @Trace: Com_SUD_API_00920 */ 
  /* Check Com_GaaMulticoreTriggerNotifyFlag after call Com_RxSigProcessing */
  Com_ProcessTriggerNotifyFlag();
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */    
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_ProcessIpduCallout                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TPRxIndication                  **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#if(COM_RX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_ProcessIpduCallout(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, PduIdType ComRxPduId)
{
  /* @Trace: Com_SUD_API_01598 */  
  /* Local variable to store callout flag */
  boolean LblCalloutFlag;
  PduInfoType LddPduCalloutInfo;

  LblCalloutFlag = COM_TRUE;
  /* Check whether I-PDU callout is configured */
  /* Polyspace Useless if [A defect:Medium] This is a base code and 
  the structure "Com_GaaRxIpdu" is verified and generated by Generator 
  Tool */
  if((LpRxIpdu->ddIpduCalloutIndex) != COM_INVALID_RXID_PARAM)
  {   
    /* @Trace: Com_SUD_API_00908 */   
    LddPduCalloutInfo.SduDataPtr = 
    Com_GaaRxPduInfoPtr[ComRxPduId].SduDataPtr;
    LddPduCalloutInfo.SduLength = 
    (PduLengthType)(*Com_GaaRxPduInfoPtr[ComRxPduId].SduLength);
    /* Check that Metadata is available or not */
    #if (COM_META_DATA_SUPPORT == STD_ON)
    /* Check metadata in Com_GaaRxPduInfoPtr */
    if(Com_GaaRxPduInfoPtr[ComRxPduId].MetaDataPtr != NULL_PTR)
    /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
    {
      /* @Trace: Com_SUD_API_00909 */ 
      /*Copy Meta Data to callout function*/
      LddPduCalloutInfo.MetaDataPtr = 
                  Com_GaaRxPduInfoPtr[ComRxPduId].MetaDataPtr;
    }
    #endif  
    /* @Trace: Com_SUD_API_00910 */ 
    LblCalloutFlag = Com_RxIpduCallout(ComRxPduId, 
    (PduInfoType *)&LddPduCalloutInfo);
  }
  
  if(COM_TRUE == LblCalloutFlag)
  {
    /* @Trace: Com_SUD_API_00911 */ 
    Com_GaaRxTPflg[ComRxPduId] = COM_ZERO;
  }
  else
  {
    /* @Trace: Com_SUD_API_00912 */ 
    Com_GaaRxTPflg[ComRxPduId] = COM_ONE;
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TpRxInd_InputValidate                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TPRxIndication                  **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#if(COM_DEV_ERROR_DETECT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COM_CODE) Com_TpRxInd_InputValidate(PduIdType ComRxPduId)
{
  /* @Trace: Com_SUD_API_01499 */
  uint8 LucReturnValue;
  /* Initialize error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_TPRXINDICATION);
  /* Check whether Tx PDU ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01682 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId, COMSERVICEID_TPRXINDICATION);
  #else
  /* @Trace: Com_SUD_API_01683 */
  COM_DET_RXPDUID_RANGE_CHECK_FLAG_PB(ComRxPduId, COMSERVICEID_TPRXINDICATION);
  #endif
  /* @Trace: Com_SUD_API_01500 */
  return LucReturnValue;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : Com_TpRxInd_UpdateRxIpduSts                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TPRxIndication                  **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TpRxInd_UpdateRxIpduSts(PduIdType ComRxPduId, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu)
{
  /* @Trace: Com_SUD_API_00904 */
  /* Unlock the buffer */
  Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] 
    &= (uint8)(~(LpRxTPIpdu->ucRxTPStatusMask));

  /* For handling SoAd TP message, when Header option is disabled 
  by AUTRON #818 */
  if(*(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength == 
                                                (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00905 */
    *(PduLengthType *)Com_GaaRxPduInfoPtr[ComRxPduId].SduLength 
    = Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef];
  }

  /* @Trace: Com_SUD_API_00906 */
  /* Set the length of Ipdu copied to zero */
  Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef] = COM_ZERO;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TpRxInd_ProcIpduCnt                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_TPRxIndication                  **
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
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if((COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
  (COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
  (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
FUNC(void, COM_CODE) Com_TpRxInd_ProcIpduCnt(PduIdType ComRxPduId, 
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu, 
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu)
#else
FUNC(void, COM_CODE) Com_TpRxInd_ProcIpduCnt(PduIdType ComRxPduId)
#endif
{
  /* @Trace: Com_SUD_API_01501 */
  #if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
    (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpLocalRxIpdu;
  #endif
  #if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)
  /* Pointer to Ipdu Buffer */
  P2VAR(Com_RxPduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr;
  /* Load SduDataPtr in local pointer */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduPtr;
  boolean LblCounterFlag;
  
  LblCounterFlag = COM_TRUE;
  LpSduPtr = NULL_PTR; 
  /* Check whether I-PDU counter is configured */
  /* Polyspace Useless if [A defect:Low] "this is a base code, Com_GaaRxTPIIpdu is verified and generated by Generator Toolare verified and generated by Generator Tool" */
  if(LpRxIpdu->ddRxIpduCounter != COM_INVALID_RXID_PARAM)
  {
    if(LpRxTPIpdu->pDoubleIpduBuffer != NULL_PTR)
    {
      /* @Trace: Com_SUD_API_00914 */ 
      /* Load SduDataPtr in local pointer */
      LpSduPtr = (LpRxTPIpdu->pDoubleIpduBuffer->SduDataPtr);
    
      /* Invoke Com_RxIpduCounterChk() to check I-PDU counter */
      LblCounterFlag = Com_RxIpduCounterChk(ComRxPduId, LpSduPtr);
    }        
  }
  /* Polyspace Useless if [A defect:Medium] "this is a base code, Com_GaaRxTPIpdu is verified and generated by Generator Tool" */
  if(COM_TRUE == LblCounterFlag)
  #endif
  {
    /* @Trace: Com_SUD_API_00915 */ 
    #if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)
    /* Get the pointer to */
    /* polyspace +2 MISRA2012:11.8 [Not a defect:Low] "Pointer conversion is safe. Checked by unittest" */
    LpPduInfoPtr = 
          (Com_RxPduInfoType *)&Com_GaaRxPduInfoPtr[ComRxPduId];

    Com_DoubleBufferCall(LpRxTPIpdu, LpPduInfoPtr, LpSduPtr);
    #endif
    
    Com_WriteReceiveIpduList((PduIdType)ComRxPduId);
    #if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
        (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
    if((COM_FALSE == (Com_GaaRxIpdu[ComRxPduId].ucRxConfig &
                    COM_RX_IPDU_DEFERRED_CONFIG_MASK)))
    {
      /* @Trace: Com_SUD_API_00916 */ 
      /* Get the pointer to RxIpdu structure */
      LpLocalRxIpdu = &Com_GaaRxIpdu[ComRxPduId];
      Com_ProcessRxSignalAndGW(LpLocalRxIpdu, ComRxPduId);
    }
    #endif /* #if(COM_RX_IPDU_DEFERRED == STD_ON)  */
  } /* Check if counter flag is set */ 
  
  #if((COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
    (COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
    (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
  #if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_OFF)
  COM_UNUSED_PTR(LpRxTPIpdu);
  COM_UNUSED_PTR(LpRxIpdu);
  #endif
  #if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_OFF) && \
    (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_OFF))
  COM_UNUSED_PTR(LpLocalRxIpdu);
  #endif
  #endif
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TpRxIndication                                  **
**                                                                            **
** Service ID           : 0x1E                                                **
**                                                                            **
** Description          : By a call to Com_TpRxIndication the AUTOSAR COM     **
**                        module starts the processing of the received large  **
**                        or dynamic length IPDU                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : PduId, Result                                       **
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
**                                                 Com_GaaRxTPIpdu            **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaRxTPStatus          **
**                                                 Com_GaaRxPduInfoPtr        **
**                                                 Com_GaaRxIpduTPLength      **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_RxIpduCallout()        **
**                                                 Com_RxIpduCounterChk()     **
**                                                 Com_DoubleBufferCall()     **
**                                                 Com_RxSigProcessing()      **
**                                                 Com_RxSigGrpProcessing()   **
*******************************************************************************/
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02091, SWS_Com_00693, SWS_Com_02095 */
FUNC(void, COM_CODE) Com_TpRxIndication(PduIdType ComRxPduId, 
  Std_ReturnType result)
{
  /* @Trace: Com_SUD_API_00901 */
  /* Pointer to Rx Ipdu structure */
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  /* Pointer to Rx TP structure */
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  #if((COM_DEV_ERROR_DETECT == STD_ON)||(STD_ON == COM_MULTI_CORE_SUPPORT))
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #endif
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

  #if(COM_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Com_TpRxInd_InputValidate(ComRxPduId);
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  COM_RXPDUID_CHECK_COREID(ComRxPduId,LucReturnValue);
  
  if(LucReturnValue == (uint8)E_OK)
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  {
    /* @Trace: Com_SUD_API_00902 */
    /* Check if Result from PduR is "ok". Otherwise Ipdu will not be processed 
       the Ipdu */
    /* Get the pointer to Tx Ipdu */
    LpRxIpdu = &Com_GaaRxIpdu[ComRxPduId];
    if (LpRxIpdu->ucRxTPRef != COM_INVALID_NONE)
    {
      /* @Trace: Com_SUD_API_00903 */
      /* Get the pointer to Rx TP structure */
      LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
      /* Check whether Rx I-PDU is started */
      if(Com_GaaRxIpduStatus[ComRxPduId] != (PduIdType)COM_ZERO)
      { 
        /* If TP Buffer is locked i.e any TP Tx is in progress */
        if((Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] & 
        (LpRxTPIpdu->ucRxTPStatusMask)) != COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00907 */
          Com_TpRxInd_UpdateRxIpduSts(ComRxPduId, LpRxTPIpdu);
          #if(COM_RX_IPDU_CALLOUT == STD_ON)
          Com_ProcessIpduCallout(LpRxIpdu, ComRxPduId);
          #endif
          if(E_OK != result)
          {
            /* @Trace: Com_SUD_API_00913 */ 
            Com_GaaRxTPflg[ComRxPduId] = COM_ONE;
          }
          
          #if((COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
            (COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
            (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
          /* @Trace: Com_SUD_API_01502 */
          Com_TpRxInd_ProcIpduCnt(ComRxPduId, LpRxIpdu, LpRxTPIpdu);
          #else
          /* @Trace: Com_SUD_API_01503 */
          Com_TpRxInd_ProcIpduCnt(ComRxPduId);
          #endif
        } /* Check if TP buffer is locked */  
      }  /* Check if Result from PduR is "ok" */  
    }
  }  /* Check whether any development error has occurred */
}
/* @Traceability END -- SRS: SRS_Com_02091, SWS_Com_00693 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Com_TpTxConfirmation                                **
**                                                                            **
** Service ID           : 0x26                                                **
**                                                                            **
** Description          : This function is called by the PduR after a large   **
**                        I-PDU has been transmitted via the transport        **
**                        protocol on its network.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same PDU-ID.                  **
**                        Reentrant for different PDU-ID.                     **
**                                                                            **
** Input Parameters     : PduId, Result                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxIpduTPLength      **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxTPIpdu            **
**                                                 Com_GaaTxUpdateBit         **
**                                                 Com_GaaTxPduInfoPtr        **
**                                                 Com_GaaTxMode              **
**                                                 Com_GaaTxTPStatus          **
**                                                 Com_GaaTxIpduTPLength      **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                 SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 Com_TpTxConfMDT()          **
**                                                 Com_TxClearUpdateBit()     **
**                                                 Com_TxSigConfirmation()    **
*******************************************************************************/
#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02095*/
FUNC(void, COM_CODE)
Com_TpTxConfirmation(PduIdType ComTxPduId,
  Std_ReturnType result)
{
  /* @Trace: Com_SUD_API_00921 */ 
  /* Pointer to Tx Ipdu structure */
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST)
  LpTxIpdu;
  /* Pointer to Tx Ipdu */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST)
  LpTxTPIpdu;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to store return value */
  uint8 LucReturnValue;
  #endif
  #if((COM_TX_SIGNAL_UB == STD_ON) || \
      (COM_TX_SIGGROUP_UB == STD_ON) || \
      (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
      (COM_TX_IPDU_REPETITION == STD_ON))
  boolean LblReturnValue;
  #endif
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize DET error flag to false */
  LucReturnValue = (uint8)E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_TPTXCONFIRMATION);
  /* Check whether Tx PDU ID is out of range */
  COM_DET_TXPDUID_RANGE_CHECK_FLAG(ComTxPduId, COMSERVICEID_TPTXCONFIRMATION);
  if(LucReturnValue == (uint8)E_OK)
  #endif /* COM_DEV_ERROR_DETECT */
  {
    /* Check whether Tx I-PDU is started */
    if((Com_GaaTxIpduStatusBit[ComTxPduId] & COM_TX_REQ_STATUS_MASK) !=
      COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00922 */ 
      /* Get the pointer to Tx Ipdu */
      LpTxIpdu = &Com_GaaTxIpdu[ComTxPduId];
      /* Get the pointer to TP structure  */
      LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
      if((uint8)E_OK == result)
      {
        /* @Trace: Com_SUD_API_00923 */ 
        #if((COM_TX_SIGNAL_UB == STD_ON) || \
          (COM_TX_SIGGROUP_UB == STD_ON) || \
          (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
          (COM_TX_IPDU_REPETITION == STD_ON))
        LblReturnValue = Com_TxIpduConfirmation(ComTxPduId);
        if(LblReturnValue == COM_TRUE)
        #endif /*COM_TX_IPDU_UPDATEBIT == STD_ON)*/
        {
          /* @Trace: Com_SUD_API_00924 */ 
          /* Update confirmation status mask */
          SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();

          Com_GaaTxIpduStatusBit[ComTxPduId] |= COM_TX_CONFIRM_STATUS_MASK;
          Com_GaaTxIpduStatusBit[ComTxPduId] &= 
            (uint16)(COM_TX_REQ_STATUS_CLEAR_MASK);        
          SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();

          #if(COM_TX_SIGNAL_IMMEDIATENOTIFY == STD_ON)
          
          if(COM_TX_IPDU_NOTIFY_CONFIG_MASK == 
                    (LpTxIpdu->ucTxConfig & COM_TX_IPDU_DEF_NOTIFY_CONFIG_MASK))
          {
            /* @Trace: Com_SUD_API_00925 */ 
            Com_TxSigConfirmation(LpTxIpdu);
          }
          /* Update the length of the Ipdu in Com internal Ipdu buffers */
          /* @Trace: Com_SUD_API_00926 */
          /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
          Com_GaaTxPduInfoPtr[ComTxPduId].SduLength = 
          Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef];
          #endif /*COM_TP_TX_SIGNAL_IMMEDIATENOTIFY == STD_ON) */
        }
      }  
      /* @Trace: Com_SUD_API_00927 */
      SchM_Enter_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      /* Unlock the buffer no matter what the result */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] &= 
                                       (uint8)~(LpTxTPIpdu->ucTxTPStatusMask);
      SchM_Exit_Com_TX_IPDU_STATUS_PROTECTION_AREA();
      /* Set the length of Ipdu copied to zero */
      Com_GaaTxIpduTPLength[LpTxTPIpdu->ucTxIpduTPLengthRef] = COM_ZERO;
    } /* Check whether Tx I-PDU is started */
  } /* Check whether any development error has occurred */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_DoubleBufferCall                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LpRxTPIpdu, LpPduInfoPtr, LpSduPtr                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_DoubleBufferCall(P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu,
  P2VAR(Com_RxPduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr,
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduPtr)
{
  if((LpRxTPIpdu->pDoubleIpduBuffer != NULL_PTR) &&
    (LpSduPtr != NULL_PTR))
  {      
    /* @Trace: Com_SUD_API_00928 */  
    *(uint16 *) LpPduInfoPtr->SduLength = 
      *(uint16 *) LpRxTPIpdu->pDoubleIpduBuffer->SduLength;
    /* Copy the contents of double buffer to actual buffer */
    /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
    memcpy(
    ((P2VAR(void, AUTOMATIC, COM_VAR))(LpPduInfoPtr->SduDataPtr)), 
    ((P2CONST(void, AUTOMATIC, COM_CONST))(LpSduPtr)), 
    *(PduLengthType *)(LpPduInfoPtr->SduLength));
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif /*if(COM_RX_TP_SUPPORT == STD_ON)||(COM_TX_TP_SUPPORT == STD_ON)*/
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
