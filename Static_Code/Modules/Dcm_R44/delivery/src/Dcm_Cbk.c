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
**  SRC-MODULE: Dcm_Cbk.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Implement the callback function for PduR                      **
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
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     19-Mar-2020   LanhLT         Update Preempt protocol             **
** 0.0.3     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.4     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.5     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.6     17-Nov-2020   HueKM          Changes Dcm_CopyTxData prototype    **
** 0.0.7     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.8     24-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE and #CP44-1200            **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1637, #CP44-1799        **
**                                        #CP44-1804                          **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.0.13    10-Jul-2023   DanhTQ1        Refer #CP44-2474                    **
** 1.0.13    04-Aug-2023   KT Kim         Refer #CP44-2644                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106, #CP44-2676        **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.1     01-Apr-2024   QuanTDM        Refer #CP44-4313                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Cbk.h"
#include "Rte_Dcm.h"
#include "PduR_Dcm.h"
#if(DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif

#include "SchM_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Dsl.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DspServices.h"
#include "Dcm_DslManageSecurity.h"

#include "ComM_Dcm.h"
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#include "Dcm_DspResponseOnEvent.h"
#endif

#include "Dcm_Config.h"
#include "Dcm_Validate.h"
#include "Dcm_ActiveDiag.h"
#include "Dcm_Timer.h"
#include "Dcm_GenericConnection.h"

#include "Dcm_Utils.h"
#include "Dcm_ReqRespHandling.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* For PagedBuffer */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

/* CAN : max 7 bytes, CAN FD: max 64 */
#define DCM_MAX_PAGED_SDU_LEN 63

/* polyspace +3 MISRA2012:8.9 [Justified:Low] Justify with annotations */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static Dcm_MsgLenType Dcm_GulFilledSduLength;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static uint8 Dcm_GaaFilledPagedSdu[DCM_MAX_PAGED_SDU_LEN];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

typedef enum {
  DCM_RX_REQ_PHY
  , DCM_RX_REQ_FUNC
  , DCM_RX_REQ_PHY_WHILE_BUSY
  , DCM_RX_REQ_FUNC_WHILE_BUSY
  , DCM_RX_REQ_PHY_HIGHER_PRIORITY_WHILE_BUSY
  , DCM_RX_REQ_FUNC_HIGHER_PRIORITY_WHILE_BUSY
  #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
  , DCM_RX_REQ_OBD_WHILE_BUSY_REQ_UDS
  , DCM_RX_REQ_UDS_WHILE_BUSY_REQ_OBD
  #endif
} Dcm_RxRequestStateType;

typedef enum {
  DCM_COPY_RX_REQ_EMPTY
  , DCM_COPY_RX_REQ_NORMAL
  , DCM_COPY_RX_REQ_CONCURRENT_TESTERPRESENT
  , DCM_COPY_RX_REQ_DECLINED
  , DCM_COPY_RX_MAX_NUM
} Dcm_CopyRxStateType;

typedef P2FUNC(BufReq_ReturnType, DCM_CODE, Dcm_ProcessCopyRxDataFunType)(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

typedef enum {
  DCM_RX_INDICATION_FAIL
  , DCM_RX_INDICATION_REQ_NORMAL
  , DCM_RX_INDICATION_REQ_CONCURRENT_TESTERPRESENT
  , DCM_RX_INDICATION_REQ_DECLINED
  , DCM_RX_INDICATION_REQ_HIGHER_PRIORITY
  #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
  , DCM_RX_INDICATION_REQ_OBD_WHILE_BUSY_REQ_UDS
  , DCM_RX_INDICATION_REQ_UDS_WHILE_BUSY_REQ_OBD
  #endif
  , DCM_RX_INDICATION_MAX_NUM
} Dcm_RxIndicationStateType;

typedef P2FUNC(void, DCM_CODE, Dcm_ProcessTpRxIndicationFunType)(
  PduIdType Id);

typedef enum {
  DCM_COPY_TX_REQ_NORMAL
  , DCM_COPY_TX_REQ_DECLINED
  , DCM_COPY_TX_REQ_PERI
  , DCM_COPY_TX_REQ_ROE
  , DCM_COPY_TX_REQ_REJECTED
  , DCM_COPY_TX_MAX_NUM
} Dcm_CopyTxStateType;

typedef P2FUNC(BufReq_ReturnType, DCM_CODE, Dcm_ProcessCopyTxDataFunType)(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

typedef P2FUNC(Dcm_CopyTxStateType, DCM_CODE, Dcm_JudgeCopyTxDataStateFunType)(
  PduIdType Id);

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static uint8 Dcm_GusFuncTesterPresentRequested;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

// StartOfReception
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ValidateStartOfReception(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthType TpSduLength
  , PduLengthPtrType BufferSizePtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessStartOfReception(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthType TpSduLength
  , PduLengthPtrType BufferSizePtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_JudgeStartOfReceptionState(
  PduIdType Id
  , Dcm_BooleanPtrType pIsProcessRequest
  , Dcm_BooleanPtrType pIsStopS3Timer
  ,PduInfoConstPtrType Info);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_JudgeStartOfReceptionState_DiffConnection(
  PduIdType Id
  , Dcm_BooleanPtrType pIsProcessRequest
  , Dcm_BooleanPtrType pIsStopS3Timer
  , PduInfoConstPtrType Info);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_JudgeStartOfReceptionState_SameConnection(
  PduIdType Id
  , Dcm_BooleanPtrType pIsProcessRequest
  , Dcm_BooleanPtrType pIsStopS3Timer
  , PduInfoConstPtrType Info);

static FUNC(Dcm_RxRequestStateType, DCM_CODE) Dcm_JudgeRxRequestStateType(
  PduIdType Id);


// CopyRxData
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ValidateCopyRxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

static FUNC(Dcm_CopyRxStateType, DCM_CODE) Dcm_JudgeCopyRxDataState(
  PduIdType Id
  , PduInfoConstPtrType Info);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_NoRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_NormalRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_ConcurrentTesterPresentRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_DeclinedRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr);

static FUNC(boolean, DCM_CODE) Dcm_IsCopyConcurrentTesterPresentRequest(
  PduIdType Id);


// TpRxIndication
static FUNC(boolean, DCM_CODE) Dcm_ValidateTpRxIndication(
  PduIdType Id
  , Std_ReturnType Result);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication(
  PduIdType Id
  , Std_ReturnType Result);

static FUNC(Dcm_RxIndicationStateType, DCM_CODE) Dcm_JudgeRxIndicationState(
  PduIdType Id
  , Std_ReturnType Result);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_Fail(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_NormalRequest(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_ConcurrentTesterPresentRequest(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_DeclinedRequest(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_HigherPriorityRequest(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_HigherPriorityRequest_NoBusy(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_HigherPriorityRequest_WhileBusy(
  PduIdType Id);

#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_ObdRequestWhileBusyUdsRequest(
  PduIdType Id);

static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_UdsRequestWhileBusyObdRequest(
  PduIdType Id);
#endif

static FUNC(boolean, DCM_CODE) Dcm_IsConcurrentTesterPresentRequest(
  Dcm_PduIdTablePtrType pPduIdTable);

// CopyTxData
static FUNC(boolean, DCM_CODE) Dcm_ValidateCopyTxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState(
  PduIdType Id);

static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_RoeRequest(
  PduIdType Id);

static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_PeriodicRequest(
  PduIdType Id);

static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_DeclinedRequest(
  PduIdType Id);

static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_NormalRequest(
  PduIdType Id);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_NormalRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_DeclinedRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_PeriodicRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_RoeRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_RejectedRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr);

static FUNC(void, DCM_CODE) Dcm_CbkInternal_CopyTxData(
  BufReq_ReturnType *pReturnValue
  , PduInfoConstPtrType pPduInfo
  , PduLengthPtrType AvailableDataPtr);

static FUNC(boolean, DCM_CODE) Dcm_IsFuncTesterPresentWithSuppressionRequested (
  PduIdType Id
 , PduInfoConstPtrType Info );

/*******************************************************************************
** Function Name        : Dcm_StartOfReception                                **
**                                                                            **
** Service ID           : 0x46                                                **
**                                                                            **
** Description          : By this service the DCM is requested to provide a   **
**                        buffer for a transport layer on first frame or      **
**                        single frame reception.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Info, TpSduLength                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04003 SRS_Diag_04167 */
/* @Trace: SWS_Dcm_00094 */
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_StartOfReception(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthType TpSduLength
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70300 */
  BufReq_ReturnType RetVal;
  RetVal = Dcm_ValidateStartOfReception(Id, Info, TpSduLength, BufferSizePtr);

  if (BUFREQ_OK == RetVal)
  {
    /* @Trace: SWS_Dcm_00833 */
    /* @Trace: Dcm_SUD_API_70301 */
    /* Ensure reentrant by using protection */
    SchM_Enter_Dcm_RxPduIdProtection();
    RetVal = Dcm_ProcessStartOfReception(Id, Info, TpSduLength, BufferSizePtr);
    SchM_Exit_Dcm_RxPduIdProtection();
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateStartOfReception                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate the state and input arguments of           **
**                        start of reception function                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, TpSduLength, BufferSizePtr                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ValidateStartOfReception(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthType TpSduLength
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70302 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;
  uint8 ApiId = DCM_START_OF_RECEPTION_SID;

  /* Check init & inputs arguments */
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkPduId(ApiId, Id));
  CHK_NEXT(ChkVal, Dcm_ChkRxMetaDataPtr(ApiId, Id, Info));
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, BufferSizePtr));

  /* @Trace: SRS_Diag_04147 */
  /* @Trace: SWS_Dcm_00642 */
  CHK_NEXT(ChkVal, Dcm_ChkZeroLength(ApiId, TpSduLength));

  /* @Trace: SRS_Diag_04153 */
  CHK_NEXT(ChkVal, Dcm_ChkRxTargetAddress(Id, Info));

  Dcm_BufferConfigConstPtrType pBufferCfg = NULL_PTR;

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_70303 */
    pBufferCfg = Dcm_GetBufferConfigPtr(Id);
    ChkVal = Dcm_ChkP2Const(ApiId, pBufferCfg);
  }

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_70304 */
    /* Check available buffer size < requested size */
    /* polyspace +1 CERT-C:EXP34-C [Justified:Low] "The NULL_PTR was checked in the function Dcm_ChkP2Const " */
    ChkVal = Dcm_ChkLength(ApiId, TpSduLength, pBufferCfg->ulBufferSize);

    /* @Trace: SWS_Dcm_00444 */
    if (DCM_FALSE == ChkVal)
    {
      /* @Trace: Dcm_SUD_API_70305 */
      RetVal = BUFREQ_E_OVFL;
    }
  }

  /* Check module state */
  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_70306 */
    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
    uint8 ComMChannel = pPduIdTable->ComMChannelId;

    ChkVal = Dcm_ChkComMChannel(ApiId, ComMChannel);
    CHK_NEXT(ChkVal, Dcm_IsNotInNoComMode(ComMChannel));

    /* @Trace: SWS_Dcm_00834 */
    CHK_NEXT(ChkVal, Dcm_IsNotInReset());
  }

  /* @Trace: Dcm_SUD_API_70307 Dcm_SUD_API_70308 */
  return (DCM_TRUE == ChkVal) ? BUFREQ_OK : RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessStartOfReception                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for start of reception        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, TpSduLength                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessStartOfReception(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthType TpSduLength
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70309 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;
  boolean IsProcessRequest = DCM_FALSE;
  boolean IsStopS3Timer = DCM_FALSE;
  boolean IsfuncTesterPresent = DCM_FALSE;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  if (DCM_IS_CLR_PDU_STATUS(pPduIdTable))
  {
    /* @Trace: Dcm_SUD_API_70310 */
    RetVal = Dcm_JudgeStartOfReceptionState(
      Id, &IsProcessRequest, &IsStopS3Timer, Info);
  }

  Dcm_BufferConfigConstPtrType pBufferCfg = NULL_PTR;
  uint8 ProtocolIdx;
  if (BUFREQ_OK == RetVal)
  {
    /* @Trace: Dcm_SUD_API_70311 */
    pBufferCfg = Dcm_GetBufferConfigPtr(Id);
    ProtocolIdx = Dcm_GetProtocolTypeIndex(pPduIdTable->ProtocolType);

    CHK_RET_VAL(NULL_PTR == pBufferCfg, RetVal, BUFREQ_E_NOT_OK);
    CHK_RET_VAL(DCM_NUM_OF_PROTOCOLCONFIG <= ProtocolIdx, RetVal, BUFREQ_E_NOT_OK);
    CHK_RET_VAL(NULL_PTR == BufferSizePtr, RetVal, BUFREQ_E_NOT_OK);
  }

  if (BUFREQ_OK == RetVal)
  {
    /* @Trace: Dcm_SUD_API_70312 */
    /* Accept request */
    SchM_Enter_Dcm_RxPduIdProtection();
    DCM_SET_PDU_STATUS(pPduIdTable);
    SchM_Exit_Dcm_RxPduIdProtection();
    pPduIdTable->ulRxCopiedLength = 0U;

    /* if functional tester present (3E 80) requested, Dcm will accept and keep continute remain work*/
    Dcm_GusFuncTesterPresentRequested = DCM_NO_TESTER_PRESENT_REQUESTED;
    IsfuncTesterPresent = Dcm_IsFuncTesterPresentWithSuppressionRequested(Id, Info);
 

    *BufferSizePtr = (PduLengthType)pBufferCfg->ulBufferSize;

    Dcm_StoreSourceTesterAddress(Id, Info);    

    /* Trigger to process request after succeeded to receive request */
    
    if (IsfuncTesterPresent==DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_70313 */
      if(IsProcessRequest==DCM_TRUE)
      {
        SchM_Enter_Dcm_RxLengthProtection();
        if (DCM_FALSE == DCM_IS_SET_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]))
        {
          DCM_SET_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]);
          pPduIdTable->ucReceiveStatus = DCM_RECEPTION_ONGOING;  
          Dcm_GaaReqLength[ProtocolIdx] = 0U;
        }
        SchM_Exit_Dcm_RxLengthProtection();
      }
    }
    
    if ((DCM_TRUE == IsStopS3Timer) && 
        (DCM_TRANSPARENT_TESTER_PRESENT != Dcm_GusFuncTesterPresentRequested))
    {
      /* @Trace: Dcm_SUD_API_70314 */
      Dcm_StopTimer(DCM_S3SERVER_TIMER);
    }

    /* Suspend periodic transmission */
    #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    Dcm_GddPerStatus.blOnResTrans = DCM_FALSE;
    #endif
  }

  DCM_UNUSED(TpSduLength);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeStartOfReceptionState                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge start of reception state                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pIsProcessRequest, pIsStopS3Timer, Info             **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_JudgeStartOfReceptionState(
  PduIdType Id
  , Dcm_BooleanPtrType pIsProcessRequest
  , Dcm_BooleanPtrType pIsStopS3Timer
  , PduInfoConstPtrType Info)
{
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  if (DCM_TRUE == Dcm_IsDiffConnection(Dcm_GddRxPduId, Id))
  {
    /* @Trace: Dcm_SUD_API_70315 */
    RetVal = Dcm_JudgeStartOfReceptionState_DiffConnection(
      Id, pIsProcessRequest, pIsStopS3Timer, Info);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70316 */
    RetVal = Dcm_JudgeStartOfReceptionState_SameConnection(
      Id, pIsProcessRequest, pIsStopS3Timer, Info);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeStartOfReceptionState_DiffConnection       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge start of reception state in case              **
**                        different connection                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pIsProcessRequest, pIsStopS3Timer, Info             **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04166 */
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_JudgeStartOfReceptionState_DiffConnection(
  PduIdType Id
  , Dcm_BooleanPtrType pIsProcessRequest
  , Dcm_BooleanPtrType pIsStopS3Timer
  , PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_70317 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  // New request on different connection
  // A - Not processing request
  //   1. Accept phy request
  //   2. Accept func request
  // => reset S3Server Timer (if in non-default session)

  // B - Processing request
  //   1. Accept phy request (if RespOnSecDeclReq On) => respond NRC 0x21
  //   2. Reject phy request (if RespOnSecDeclReq Off)
  //   3. Accept func request => but no further process
  //   4*. Accept phy/func request with higher priority => protocol preemption

  // (*) func request can be TESTER_PRESENT or not => check if received

  Dcm_RxRequestStateType RxRequestState = Dcm_JudgeRxRequestStateType(Id);

  /* @Trace: SWS_Dcm_00655 SWS_Dcm_00656 SWS_Dcm_00924 */
  switch (RxRequestState)
  {
    case DCM_RX_REQ_PHY:
    case DCM_RX_REQ_FUNC:
    case DCM_RX_REQ_PHY_HIGHER_PRIORITY_WHILE_BUSY:
    case DCM_RX_REQ_FUNC_HIGHER_PRIORITY_WHILE_BUSY:

    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    case DCM_RX_REQ_OBD_WHILE_BUSY_REQ_UDS:
    case DCM_RX_REQ_UDS_WHILE_BUSY_REQ_OBD:
    #endif
      /* @Trace: Dcm_SUD_API_70318 */
      *pIsProcessRequest = DCM_TRUE;

      if (DCM_TRUE == Dcm_IsNonDefaultSession())
      {
        /* @Trace: Dcm_SUD_API_70319 */
        *pIsStopS3Timer = DCM_TRUE;
      }

      RetVal = BUFREQ_OK;
      break;

    case DCM_RX_REQ_FUNC_WHILE_BUSY:
      /* @Trace: SWS_Dcm_01145 */
      if (DCM_TRUE == Dcm_IsFuncTesterPresentWithSuppressionRequested(Id,Info))
      {
        /* @Trace: Dcm_SUD_API_70320 */
        RetVal = BUFREQ_OK;
      }
      else
      {
          #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          // store SID for return NRC 0x21
          /* @Trace: Dcm_SUD_API_70476 */
          Dcm_GucSidOfDeclinedRequest = Info->SduDataPtr[0];
          RetVal = BUFREQ_OK;
          #endif
      }
      break;

    /* case DCM_RX_REQ_PHY_WHILE_BUSY */
    default:
      /* @Trace: SWS_Dcm_00790 SWS_Dcm_00728 */
      #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
      /* @Trace: SWS_Dcm_00788 SWS_Dcm_00727 SWS_Dcm_00729*/
      // store SID for return NRC 0x21
      /* @Trace: Dcm_SUD_API_70321 */
      Dcm_GucSidOfDeclinedRequest = Info->SduDataPtr[0];
      RetVal = BUFREQ_OK;
      #endif
      break;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeStartOfReceptionState_SameConnection       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge start of reception state in case              **
**                        same connection                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pIsProcessRequest, pIsStopS3Timer                   **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_JudgeStartOfReceptionState_SameConnection(
  PduIdType Id
  , Dcm_BooleanPtrType pIsProcessRequest
  , Dcm_BooleanPtrType pIsStopS3Timer
  , PduInfoConstPtrType Info )
{
  /* @Trace: Dcm_SUD_API_70322 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  // New request on same connection
  // A- Not processing request
  //   1. Accept phy request
  //   2. Accept func request
  // => reset S3Server Timer (if in non-default session)

  // B - Processing request
  //   1. Reject phy request
  //   2. Accept func request => but no further process

  // (*) func request can be TESTER_PRESENT or not => check if received

  Dcm_RxRequestStateType RxRequestState = Dcm_JudgeRxRequestStateType(Id);

  switch (RxRequestState)
  {
    case DCM_RX_REQ_PHY:
    case DCM_RX_REQ_FUNC:
      /* @Trace: Dcm_SUD_API_70323 */
      RetVal = BUFREQ_OK;
      *pIsProcessRequest = DCM_TRUE;

      if (DCM_TRUE == Dcm_IsNonDefaultSession())
      {
        /* @Trace: Dcm_SUD_API_70324 */
        *pIsStopS3Timer = DCM_TRUE;
      }
      break;

    /* @Trace: SWS_Dcm_00557 */
    case DCM_RX_REQ_FUNC_WHILE_BUSY:
      /* @Trace: Dcm_SUD_API_70325 */
      if (DCM_TRUE == Dcm_IsFuncTesterPresentWithSuppressionRequested(Id, Info))
      {
        RetVal = BUFREQ_OK;
      }
      else
      {
          #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          // store SID for return NRC 0x21
          Dcm_GucSidOfDeclinedRequest = Info->SduDataPtr[0];
          #endif
      }
      break;

    default:
      /* @Trace: Dcm_SUD_API_70326 */
      /* Reject request */
      #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
      // store SID for return NRC 0x21
      Dcm_GucSidOfDeclinedRequest = Info->SduDataPtr[0];
      #endif
      break;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeRxRequestStateType                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Rx Request State Type                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_RxRequestStateType                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_RxRequestStateType, DCM_CODE) Dcm_JudgeRxRequestStateType(
  PduIdType Id)
{
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];

  boolean IsProcessingRequest = Dcm_IsProcessingRequest();
  boolean IsFunctionalRequest = Dcm_IsFunctionalRequest(pPduIdTable);
  boolean IsHigherPriorityRequest = Dcm_IsHigherPriorityProtocol(pPduIdTable);

  /* @Trace: SWS_Dcm_00625 */
  Dcm_RxRequestStateType RxRequestState;
  if (DCM_FALSE == IsProcessingRequest)
  {
    /* @Trace: Dcm_SUD_API_70327 Dcm_SUD_API_70332 */
    RxRequestState = (DCM_FALSE == IsFunctionalRequest) ?
      DCM_RX_REQ_PHY : DCM_RX_REQ_FUNC;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70328 Dcm_SUD_API_70329 */
    RxRequestState = (DCM_FALSE == IsFunctionalRequest) ?
      DCM_RX_REQ_PHY_WHILE_BUSY : DCM_RX_REQ_FUNC_WHILE_BUSY;

    if ((DCM_TRUE == IsHigherPriorityRequest) || (DCM_TRUE == Dcm_IsOBDRequestById(Id)) )
    {
      /* @Trace: Dcm_SUD_API_70330 Dcm_SUD_API_70331 */
      // can lead to protocol preemption
      RxRequestState = (DCM_FALSE == IsFunctionalRequest) ?
        DCM_RX_REQ_PHY_HIGHER_PRIORITY_WHILE_BUSY
        : DCM_RX_REQ_FUNC_HIGHER_PRIORITY_WHILE_BUSY;
    }

    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    if ((DCM_TRUE == Dcm_IsOBDRequestById(Id)) // new request
        && (DCM_TRUE == Dcm_IsUDSRequestById(Dcm_GddRxPduId))) // current request
    {
      /* @Trace: Dcm_SUD_API_70333 */
      RxRequestState = DCM_RX_REQ_OBD_WHILE_BUSY_REQ_UDS;
    }

    if ((DCM_TRUE == Dcm_IsUDSRequestById(Id)) // new request
        && (DCM_TRUE == Dcm_IsOBDRequestById(Dcm_GddRxPduId))) // current request
    {
      /* @Trace: Dcm_SUD_API_70334 */
      RxRequestState = DCM_RX_REQ_UDS_WHILE_BUSY_REQ_OBD;
    }
    #endif
  }

  return RxRequestState;
}

/*******************************************************************************
** Function Name        : Dcm_CopyRxData                                      **
**                                                                            **
** Service ID           : 0x44                                                **
**                                                                            **
** Description          : By this service the DCM is requested to provide a   **
**                        buffer for a transport layer on first frame or      **
**                        single frame reception.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00556 */
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyRxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70335 */
  BufReq_ReturnType RetVal;
  RetVal = Dcm_ValidateCopyRxData(Id, Info, BufferSizePtr);

  if (RetVal == BUFREQ_OK)
  {
    /* @Trace: SWS_Dcm_00831 */
    /* @Trace: Dcm_SUD_API_70336 */
    RetVal = Dcm_ProcessCopyRxData(Id, Info, BufferSizePtr);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateCopyRxData                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate the state and input arguments of           **
**                        copy rx data function                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, BufferSizePtr                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ValidateCopyRxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70337 */
  uint8 ApiId = DCM_COPY_RXDATA_SID;

  /* Check init & inputs arguments */
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkPduId(ApiId, Id));
  CHK_NEXT(ChkVal, Dcm_ChkP2Const(ApiId, Info));
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, BufferSizePtr));

  if ((DCM_TRUE == ChkVal) && (0U < Info->SduLength))
  {
    /* @Trace: Dcm_SUD_API_70338 */
    ChkVal = Dcm_ChkP2Var(ApiId, Info->SduDataPtr);
  }

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_70339 */
    Dcm_BufferConfigConstPtrType pBufferCfg = Dcm_GetBufferConfigPtr(Id);
    ChkVal = Dcm_ChkP2Const(ApiId, pBufferCfg);
  }

  /* Check module state */
  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_70340 */
    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
    uint8 ComMChannel = pPduIdTable->ComMChannelId;

    ChkVal = DCM_IS_SET_PDU_STATUS(pPduIdTable) ? DCM_TRUE : DCM_FALSE;
    CHK_NEXT(ChkVal, Dcm_ChkComMChannel(ApiId, ComMChannel));
    CHK_NEXT(ChkVal, Dcm_IsNotInNoComMode(ComMChannel));
    CHK_NEXT(ChkVal, Dcm_IsNotInReset());
  }

  /* @Trace: Dcm_SUD_API_70341 Dcm_SUD_API_70342 */
  return (DCM_TRUE == ChkVal) ? BUFREQ_OK : BUFREQ_E_NOT_OK;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyRxData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for copy rx data              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70343 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  Dcm_ProcessCopyRxDataFunType DispatchTable[DCM_COPY_RX_MAX_NUM] = {
    Dcm_ProcessCopyRxData_NoRequest
    , Dcm_ProcessCopyRxData_NormalRequest
    , Dcm_ProcessCopyRxData_ConcurrentTesterPresentRequest
    , Dcm_ProcessCopyRxData_DeclinedRequest
  };

  Dcm_CopyRxStateType CopyRxState = Dcm_JudgeCopyRxDataState(Id, Info);
  RetVal = DispatchTable[CopyRxState](Id, Info, BufferSizePtr);

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeCopyRxDataState                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Copy Rx Data State                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_CopyRxStateType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_CopyRxStateType, DCM_CODE) Dcm_JudgeCopyRxDataState(
  PduIdType Id
  , PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_70344 */
  Dcm_CopyRxStateType CopyRxState = DCM_COPY_RX_REQ_EMPTY;
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];

  if (0U < Info->SduLength)
  {
    if (DCM_TRUE == Dcm_IsCopyConcurrentTesterPresentRequest(Id))
    {
      /* @Trace: Dcm_SUD_API_70346 */
      CopyRxState = DCM_COPY_RX_REQ_CONCURRENT_TESTERPRESENT;
    }
    else
    {
      if((DCM_TRUE == Dcm_IsProcessingRequest()) && 
          (DCM_FALSE == Dcm_IsHigherPriorityProtocol(pPduIdTable)))
      {
        if((Dcm_IsOBDRequestById(Id) ^ Dcm_IsOBDRequestById(Dcm_GddRxPduId)) == 0U)
        {
            /* @Trace: Dcm_SUD_API_70474 */
            CopyRxState = DCM_COPY_RX_REQ_DECLINED;
        }
        else
        {
            /* @Trace: Dcm_SUD_API_70475 */
            CopyRxState = DCM_COPY_RX_REQ_NORMAL;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70345 */
        CopyRxState = DCM_COPY_RX_REQ_NORMAL;
      }
    }
  }

  return CopyRxState;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyRxData_NoRequest                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Rx Data in case no request             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_NoRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: SWS_Dcm_00996 */
  /* @Trace: Dcm_SUD_API_70347 */
  Dcm_BufferConfigConstPtrType pBufferCfg = Dcm_GetBufferConfigPtr(Id);

  if ((NULL_PTR != pBufferCfg)
      && (NULL_PTR != BufferSizePtr))
  {
    /* @Trace: Dcm_SUD_API_70348 */
    *BufferSizePtr = (PduLengthType)pBufferCfg->ulBufferSize;
  }

  DCM_UNUSED(Info);
  return BUFREQ_OK;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyRxData_NormalRequest                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Rx Data in case normal request         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_NormalRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70349 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  Dcm_BufferConfigConstPtrType pBufferCfg = Dcm_GetBufferConfigPtr(Id);
  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(pPduIdTable->ProtocolType);
  Dcm_Uint8PtrType pSduData = Info->SduDataPtr;

  uint32 BufferSize = 0U;
  Dcm_Uint8PtrType pBufferArea = NULL_PTR;

  if ((pPduIdTable->ucRxBufferId < DCM_NUM_OF_BUFFER_CONFIG)
      && (NULL_PTR != pBufferCfg)
      && (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG))
  {
    /* @Trace: Dcm_SUD_API_70350 */
    BufferSize = pBufferCfg->ulBufferSize - pPduIdTable->ulRxCopiedLength;
    pBufferArea = &pBufferCfg->pBufferArea[pPduIdTable->ulRxCopiedLength];
  }

  if ((0U < BufferSize) && (pBufferArea != NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_70351 */
    SchM_Enter_Dcm_RxLengthProtection();
    uint32 NoOfBytes = Info->SduLength;
    Dcm_GaaReqLength[ProtocolIdx] += NoOfBytes;
    pPduIdTable->ulRxCopiedLength += NoOfBytes;
    SchM_Exit_Dcm_RxLengthProtection();

    /* @Trace: SWS_Dcm_00443 */
    /* @Trace: Dcm_SUD_API_70352 */
    Dcm_MemCopy(pBufferArea, pSduData, NoOfBytes);

    if (BufferSize < NoOfBytes)
    {
      RetVal = BUFREQ_E_NOT_OK;
    }
    else
    {
      *BufferSizePtr = (PduLengthType)(BufferSize - NoOfBytes);
      RetVal = BUFREQ_OK;
    }
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyRxData_                              **
**                        ConcurrentTesterPresentRequest                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Rx Data in case                        **
**                        Concurrent Tester Present Request                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01144 */
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_ConcurrentTesterPresentRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{
  /* @Trace: Dcm_SUD_API_70353 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  Dcm_Uint8PtrType pSduData = Info->SduDataPtr;

  if (Info->SduLength == 0x02)
  {
    /* @Trace: Dcm_SUD_API_70354 */
    //pPduIdTable->ucReceiveStatus = DCM_RECEPTION_IDLE;

    Dcm_GaaTesterPresentReqBuff[0U] = pSduData[0U];
    Dcm_GaaTesterPresentReqBuff[1U] = pSduData[1U];

    *BufferSizePtr = 0U;
    RetVal = BUFREQ_OK;

  }
  else
  {
    /* @Trace: Dcm_SUD_API_70355 */
    SchM_Enter_Dcm_RxPduIdProtection();
    DCM_CLR_PDU_STATUS(pPduIdTable);
    SchM_Exit_Dcm_RxPduIdProtection();
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyRxData_DeclinedRequest               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Rx Data in case                        **
**                        decline second request                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BufferSizePtr                                       **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +4 MISRA-C3:8.13 [Justified:Low] "Do nothing when second request is declined. Not impact" */
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyRxData_DeclinedRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , PduLengthPtrType BufferSizePtr)
{

  DCM_UNUSED(Id);
  DCM_UNUSED(Info);
  DCM_UNUSED(BufferSizePtr);

  return BUFREQ_OK;
}

/*******************************************************************************
** Function Name        : Dcm_IsCopyConcurrentTesterPresentRequest            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether copy data in case concurrent tester   **
**                        present request or not                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                               **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsCopyConcurrentTesterPresentRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70356 */
  boolean ChkVal = DCM_FALSE;

  Dcm_RxRequestStateType RxRequestState = Dcm_JudgeRxRequestStateType(Id);
  boolean IsReceivingToProcessOtherRequest = Dcm_IsReceivingToProcessOtherRequest(Id);

  if ((RxRequestState == DCM_RX_REQ_FUNC_WHILE_BUSY)
      || (RxRequestState == DCM_RX_REQ_FUNC_HIGHER_PRIORITY_WHILE_BUSY)
      || ((RxRequestState == DCM_RX_REQ_FUNC)
          && (DCM_TRUE == IsReceivingToProcessOtherRequest)))
  {
     /* @Trace: Dcm_SUD_API_70357 */
    if ( DCM_NO_TESTER_PRESENT_REQUESTED != Dcm_GusFuncTesterPresentRequested)
    {
      ChkVal = DCM_TRUE;
    }
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_TpRxIndication                                  **
**                                                                            **
** Service ID           : 0x45                                                **
**                                                                            **
** Description          : This service indicates the DCM module whether the   **
**                        reception of diagnostic request is finished with    **
**                        or without errors.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Result                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : This function is called by PduR                     **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00093 */
FUNC(void, DCM_APPL_CODE) Dcm_TpRxIndication(
  PduIdType Id
  , Std_ReturnType Result)
{
  /* @Trace: Dcm_SUD_API_70358 */
  boolean ChkVal = Dcm_ValidateTpRxIndication(Id, Result);

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: SWS_Dcm_00345 */
    /* @Trace: Dcm_SUD_API_70359 */
    /* Ensure reentrant by using protection */
    Dcm_ProcessTpRxIndication(Id, Result);
  }
}

/*******************************************************************************
** Function Name        : Dcm_ValidateTpRxIndication                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate the input arguments of TpTxIndication      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Result                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ValidateTpRxIndication(
  PduIdType Id
  , Std_ReturnType Result)
{
  /* @Trace: Dcm_SUD_API_70360 */
  uint8 ApiId = DCM_RX_INDICATION_SID;

  /* Check init & inputs arguments */
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkPduId(ApiId, Id));

  DCM_UNUSED(Result);
  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for TpRx Indication           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Result                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication(
  PduIdType Id
  , Std_ReturnType Result)
{
  Dcm_ProcessTpRxIndicationFunType DispatchTable[DCM_RX_INDICATION_MAX_NUM] = {
    Dcm_ProcessTpRxIndication_Fail
    , Dcm_ProcessTpRxIndication_NormalRequest
    , Dcm_ProcessTpRxIndication_ConcurrentTesterPresentRequest
    , Dcm_ProcessTpRxIndication_DeclinedRequest
    , Dcm_ProcessTpRxIndication_HigherPriorityRequest
    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    , Dcm_ProcessTpRxIndication_ObdRequestWhileBusyUdsRequest
    , Dcm_ProcessTpRxIndication_UdsRequestWhileBusyObdRequest
    #endif
  };

  /* @Trace: Dcm_SUD_API_70361 */
  Dcm_RxIndicationStateType RxIndicationState;
  RxIndicationState = Dcm_JudgeRxIndicationState(Id, Result);
  DispatchTable[RxIndicationState](Id);
}

/*******************************************************************************
** Function Name        : Dcm_JudgeRxIndicationState                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Rx Indication State                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Result                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_RxIndicationStateType                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_RxIndicationStateType, DCM_CODE) Dcm_JudgeRxIndicationState(
  PduIdType Id
  , Std_ReturnType Result)
{
  /* @Trace: Dcm_SUD_API_70362 */
  Dcm_RxIndicationStateType RxIndicationState = DCM_RX_INDICATION_FAIL;
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];

  if ((Result == E_OK) && DCM_IS_SET_PDU_STATUS(pPduIdTable))
  {
    if ((DCM_CONCURENT_TESTER_PRESENT == Dcm_GusFuncTesterPresentRequested)
        || (DCM_TRANSPARENT_TESTER_PRESENT == Dcm_GusFuncTesterPresentRequested))
    {
      RxIndicationState = DCM_RX_INDICATION_REQ_CONCURRENT_TESTERPRESENT;
    }
    else if (pPduIdTable->ucReceiveStatus == DCM_RECEPTION_ONGOING)
    {
      /* @Trace: Dcm_SUD_API_70363 Dcm_SUD_API_70364 */
      RxIndicationState = (DCM_FALSE == Dcm_IsHigherPriorityProtocol(pPduIdTable)) ?
        DCM_RX_INDICATION_REQ_NORMAL : DCM_RX_INDICATION_REQ_HIGHER_PRIORITY;

      if(DCM_TRUE == Dcm_IsOBDRequestById(Id))
      {
        RxIndicationState = DCM_RX_INDICATION_REQ_HIGHER_PRIORITY;
      }

      #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
      if (DCM_TRUE == Dcm_IsProcessingRequest())
      {
        if ((DCM_TRUE == Dcm_IsOBDRequestById(Id)) // new request
            && (DCM_TRUE == Dcm_IsUDSRequestById(Dcm_GddRxPduId))) // current request
        {
          /* @Trace: Dcm_SUD_API_70365 */
          RxIndicationState = DCM_RX_INDICATION_REQ_OBD_WHILE_BUSY_REQ_UDS;
        }

        if ((DCM_TRUE == Dcm_IsUDSRequestById(Id)) // new request
            && (DCM_TRUE == Dcm_IsOBDRequestById(Dcm_GddRxPduId))) // current request
        {
          /* @Trace: Dcm_SUD_API_70366 */
          RxIndicationState = DCM_RX_INDICATION_REQ_UDS_WHILE_BUSY_REQ_OBD;
        }
      }
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_70367 Dcm_SUD_API_70368 */
      RxIndicationState = (DCM_TRUE == Dcm_IsConcurrentTesterPresentRequest(pPduIdTable)) 
        ? DCM_RX_INDICATION_REQ_CONCURRENT_TESTERPRESENT : DCM_RX_INDICATION_REQ_DECLINED;
    }
  }

  return RxIndicationState;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_Fail                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case Failed             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01050 */
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_Fail(
  PduIdType Id)
{
  /* @Trace: SWS_Dcm_00344 */
  /* @Trace: Dcm_SUD_API_70369 */

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  
  if ((DCM_RECEPTION_COMPLETED != pPduIdTable->ucReceiveStatus) 
      && (DCM_IS_SET_PDU_STATUS(pPduIdTable)))
  {
	/* @Trace: Dcm_SUD_API_79088 */
    SchM_Enter_Dcm_RxPduIdProtection();
    DCM_CLR_PDU_STATUS(pPduIdTable);
    SchM_Exit_Dcm_RxPduIdProtection();
    pPduIdTable->ucReceiveStatus = DCM_RECEPTION_COMPLETED;
	
	/* Test for Restart s3 timer */
	if (CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
    {
      /* Restart S3 timer if Dcm is on non-default session */
	  /* @Trace: Dcm_SUD_API_79087 */
      Dcm_StartTimer(DCM_S3SERVER_TIMER, GET_TIMER_S3_SERVER);
    }	

    uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(pPduIdTable->ProtocolType);
    if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      /* @Trace: Dcm_SUD_API_70370 */
      SchM_Enter_Dcm_ProtclProtection();
      DCM_CLR_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]);
      SchM_Exit_Dcm_ProtclProtection();
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_NormalRequest             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case Normal Request     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_NormalRequest(
  PduIdType Id)
{
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  pPduIdTable->ucReceiveStatus = DCM_RECEPTION_COMPLETED;

  Std_ReturnType RetVal = E_OK;

  // Check request is coming for the first time
  /* @Trace: SWS_Dcm_00036 */
  if ((DCM_FALSE == DCM_IS_ACTIVE_PROTOCOL_STATUS())
      || (pPduIdTable->ProtocolType != Dcm_GddProtocolType))
  {
    /* @Trace: SRS_Diag_04196 */
    /* @Trace: Dcm_SUD_API_70371 */
    RetVal = Dcm_SwitchProtocol(Id);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70372 */
    Dcm_TriggerEventActivationDiagnostic(AD_TE_RECEIVED_REQUEST);
  }

  Dcm_GddRxPduId = Id;

  /* @Trace: SWS_Dcm_00674 */
  if ((RetVal == E_PROTOCOL_NOT_ALLOWED) || (RetVal == E_NOT_OK))
  {
    /* @Trace: Dcm_SUD_API_70373 */
    Dcm_GddDcmTxConfPduId = (uint8)pPduIdTable->usTxConfirmationPduId;
    Dcm_DslTxIncorrectCondition(DCM_RX_INDICATION_SID);
  }
  else
  {
    /* @Trace: SWS_Dcm_00111 */
    /* @Trace: Dcm_SUD_API_70374 */
    Dcm_GblNormalReq = DCM_TRUE;
    Dcm_GblProcessNewRequest = DCM_TRUE;

    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    if (DCM_FALSE == Dcm_AddNewRequestToQueue(Id))
    {
      /* @Trace: Dcm_SUD_API_70375 */
      Dcm_ProcessTpRxIndication_Fail(Id);
    }
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_                          **
**                        ConcurrentTesterPresentRequest                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case                    **
**                        Concurrent Tester Present Request                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_ConcurrentTesterPresentRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70376 */
  //@DCM_CLR_PDU_STATUS(pPduIdTable);
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];

  Dcm_GaaTesterPresentReqBuff[0U] = 0U;
  Dcm_GaaTesterPresentReqBuff[1U] = 0U;

  if (DCM_TRUE == Dcm_IsNonDefaultSession())
  {
    /* @Trace: SWS_Dcm_01145 */
    /*if tester present received on a different DcmDslConnection
    * Dcm will not reset the session timeout timer
    */
    if (DCM_CONCURENT_TESTER_PRESENT == Dcm_GusFuncTesterPresentRequested)
    {
      /* @Trace: SWS_Dcm_00112 */
      /* @Trace: Dcm_SUD_API_70377 */
      Dcm_StartTimer(DCM_S3SERVER_TIMER, GET_TIMER_S3_SERVER);
    }

  }
  /*reset state of tester present*/
  Dcm_GusFuncTesterPresentRequested = DCM_NO_TESTER_PRESENT_REQUESTED;
  SchM_Enter_Dcm_RxPduIdProtection();
  DCM_CLR_PDU_STATUS(pPduIdTable);
  SchM_Exit_Dcm_RxPduIdProtection();
  DCM_UNUSED(Id);
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_DeclinedRequest           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case Declined Request   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_DeclinedRequest(
  PduIdType Id)
{
  #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  PduInfoType PduInfo;
  Std_ReturnType RetVal;

#if 0
  uint8 rxBufferId = pPduIdTable->ucRxBufferId;
  Dcm_BufferConfigConstPtrType pBufferCfg = &Dcm_GaaBufferConfig[rxBufferId];

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pBufferArea = pBufferCfg->pBufferArea;
#endif
  SchM_Enter_Dcm_RxPduIdProtection();
  DCM_CLR_PDU_STATUS(pPduIdTable);
  SchM_Exit_Dcm_RxPduIdProtection();
  pPduIdTable->ucReceiveStatus = DCM_RECEPTION_COMPLETED;

  Dcm_GddRxPduId_DeclinedRequest = Id;
  Dcm_GddSecDeclTxPduId = pPduIdTable->ddTxPduId;
  Dcm_GddSecDeclConfTxPduId = pPduIdTable->usTxConfirmationPduId;

  /* @Trace: SWS_Dcm_00789 */
  Dcm_SetNegResp_DeclinedRequest(Dcm_GucSidOfDeclinedRequest, DCM_E_BUSYREPEATREQUEST);

  //Reset SID for Decline request
  Dcm_GucSidOfDeclinedRequest = DCM_ZERO;


  Dcm_GetNegResp_DeclinedRequest(&PduInfo);
  RetVal = Dcm_DslWPduR_DcmTransmit(Id, Dcm_GddSecDeclTxPduId, &PduInfo);

  /* @Trace: SWS_Dcm_00118 */
  /* @Trace: Dcm_SUD_API_70378 Dcm_SUD_API_70379 */
  Dcm_GblSecDeclRequest = (RetVal == E_OK) ? DCM_TRUE : DCM_FALSE;
  #else
  DCM_UNUSED(Id);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_HigherPriorityRequest     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case                    **
**                        higher priority request                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_HigherPriorityRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70380 */
  /* current active protocol */ 
  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);

  if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
  {
    SchM_Enter_Dcm_ProtclProtection();
    DCM_CLR_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]);
    SchM_Exit_Dcm_ProtclProtection();

    /* Cancel receiving old request */
    /* @Trace: SWS_Dcm_00575 SWS_Dcm_00576 */
  	Dcm_CancelAllReceivingOtherRequests(Id);

    if (DCM_FALSE == Dcm_IsProcessingRequest())
    {
      /* @Trace: Dcm_SUD_API_70381 */
      Dcm_ProcessTpRxIndication_HigherPriorityRequest_NoBusy(Id);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_70382 */
      Dcm_ProcessTpRxIndication_HigherPriorityRequest_WhileBusy(Id);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_                          **
**                        HigherPriorityRequest_NoBusy                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case                    **
**                        higher priority request while no busy               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_HigherPriorityRequest_NoBusy(
  PduIdType Id)
{
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  pPduIdTable->ucReceiveStatus = DCM_RECEPTION_COMPLETED;

  /* @Trace: SWS_Dcm_00459 SWS_Dcm_00460 SWS_Dcm_01190 SRS_Diag_04196 */
  Std_ReturnType RetVal = Dcm_SwitchProtocol(Id);

  Dcm_GddRxPduId = Id;

  /* sg.baek 150223 - Task #2163 in redmine */
  if ((RetVal == E_PROTOCOL_NOT_ALLOWED) || (RetVal == E_NOT_OK))
  {
    /* @Trace: Dcm_SUD_API_70383 */
    Dcm_GddDcmTxConfPduId = (uint8)pPduIdTable->usTxConfirmationPduId;
    Dcm_DslTxIncorrectCondition(DCM_RX_INDICATION_SID);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70384 */
    Dcm_GblNormalReq = DCM_TRUE;
    Dcm_GblProcessNewRequest = DCM_TRUE;

    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    if (DCM_FALSE == Dcm_AddNewRequestToQueue(Id))
    {
      /* @Trace: Dcm_SUD_API_70385 */
      Dcm_ProcessTpRxIndication_Fail(Id);
    }
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_                          **
**                        HigherPriorityRequest_WhileBusy                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case                    **
**                        higher priority request while busy                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_HigherPriorityRequest_WhileBusy(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70386 */
  /* (Cancel processing) Forward the stop protocol request to the DSD layer */
  (void)Dcm_DsdIndication(Dcm_GddRxPduId, DCM_TRUE, DCM_FALSE, DCM_FALSE);

  Dcm_TxRespStatus.ucRespPending = DCM_FALSE;
  Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;

  Dcm_GblNormalReq = DCM_FALSE;

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_GddPerStatus.blOnResTrans = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
  #endif

  Dcm_ProcessTpRxIndication_HigherPriorityRequest_NoBusy(Id);
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_                          **
**                        ObdRequestWhileBusyUdsRequest                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case                    **
**                        Obd Request While Busy Uds Request                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04163 */
#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
/* @Trace: SWS_Dcm_01367 SWS_Dcm_01371 */
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_ObdRequestWhileBusyUdsRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70387 */
  if (DCM_TRUE == Dcm_IsNonDefaultSession())
  {
    /* @Trace: Dcm_SUD_API_70388 */
    /* Cancel running UDS request and remove it from queue if have */
    (void)Dcm_DsdCancelTransmission(Dcm_GddRxPduId);
    Dcm_DsdCancelOperation();
    Dcm_DsdResetPendingFlag();
    Dcm_DelRequestFromQueue(Dcm_GddRxPduId);

    /* Transit into default session */
    DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION);

    /* @Trace: SRS_Diag_04208 */
    (void) SchM_Switch_Dcm_DcmDiagnosticSessionControl(DCM_DEFAULT_SESSION);
  }

  if (DCM_FALSE == Dcm_AddNewRequestToQueue(Id))
  {
    /* @Trace: Dcm_SUD_API_70389 */
    Dcm_ProcessTpRxIndication_Fail(Id);
  }
}

/*******************************************************************************
** Function Name        : Dcm_ProcessTpRxIndication_                          **
**                        UdsRequestWhileBusyObdRequest                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Tp Rx Indication in case                    **
**                        Uds Request While Busy Obd Request                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04163 */
static FUNC(void, DCM_CODE) Dcm_ProcessTpRxIndication_UdsRequestWhileBusyObdRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70390 */
  if (DCM_FALSE == Dcm_AddNewRequestToQueue(Id))
  {
    /* @Trace: Dcm_SUD_API_70391 */
    Dcm_ProcessTpRxIndication_Fail(Id);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsConcurrentTesterPresentRequest                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether the request is concurrent tester      **
**                        present request                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pPduIdTable                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00113 SWS_Dcm_01168 */
static FUNC(boolean, DCM_CODE) Dcm_IsConcurrentTesterPresentRequest(
  Dcm_PduIdTablePtrType pPduIdTable)
{
  /* @Trace: Dcm_SUD_API_70392 */
  boolean ChkVal = DCM_FALSE;

  if ((DCM_TRUE == Dcm_IsFunctionalRequest(pPduIdTable))
      && (0x3EU == Dcm_GaaTesterPresentReqBuff[0U])
      && (0x80U == Dcm_GaaTesterPresentReqBuff[1U]))
  {
    /* @Trace: Dcm_SUD_API_70393 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_CbkInternal_CopyTxData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service checks the DCM module to provide the   **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : None                                                **
**                                                                            **
** InOut Parameters     : pReturnValue, pPduInfo                              **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_CbkInternal_CopyTxData(
  BufReq_ReturnType *pReturnValue
  , PduInfoConstPtrType pPduInfo
  , PduLengthPtrType AvailableDataPtr)
{
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) LpPduInfo;

  LpPduInfo = pPduInfo;

  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  Dcm_MsgLenType LulSduLengthToFill;
  uint8 LucPagedSduIsFull;

  if (Dcm_TxRespStatus.ucFirstPageTrans == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_70394 */
    Dcm_TxRespStatus.ucFirstPageTrans = DCM_FALSE;

    Dcm_MsgLenType LulBufferSize = Dcm_GddTxResponseLen;
    Dcm_GddTxResponseLen = Dcm_GstMsgContext.resDataLen;
    Dcm_GstMsgContext.resDataLen = LulBufferSize;
    Dcm_GulFilledSduLength = DCM_ZERO;
  }
  else if (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE)
  {
    /* @Trace: Dcm_SUD_API_70395 */
    Dcm_GddTxResponseLen = Dcm_GstMsgContext.resDataLen;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70396 */
    /* No action in this case */
  }
  #else
  Dcm_GddTxResponseLen = Dcm_GstMsgContext.resDataLen;
  #endif

  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 IsPagedRespNotReady = Dcm_IsPagedResponseNotReady();
  #endif

  if ((DCM_TRUE == Dcm_IsNormalResponseNotReady())
      #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      || (DCM_TRUE == IsPagedRespNotReady)
      #endif
     )
  {
    /* @Trace: Dcm_SUD_API_70397 */
    *pReturnValue = BUFREQ_E_BUSY;
  }
  else if (DCM_TRUE == Dcm_IsNegRespReady())
  {
    /* @Trace: Dcm_SUD_API_70398 */
    Dcm_CopyNegResp(LpPduInfo->SduDataPtr, LpPduInfo->SduLength);

    *pReturnValue = BUFREQ_OK;
    *AvailableDataPtr = 0U;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70399 */
    /* No action in this case */
  }

  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /*
  * Check if paged response in true and the previous page is
  * transmitted and total response length is not DCM_ZERO
  */
  if ((Dcm_GstMsgContext.resDataLen == DCM_ZERO)
      && (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
      && (Dcm_TxRespStatus.ucNormResponse == DCM_FALSE)
      && (Dcm_TxRespStatus.ucDslPagedTrans == DCM_FALSE)
      && (Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
      && (Dcm_GddTxResponseLen != DCM_ZERO))
  {
    /* @Trace: Dcm_SUD_API_70400 */
    Dcm_DsdConfirmation(E_OK);

    Dcm_StartTimer(DCM_P2SERVERMAX_TIMER
      , (GET_TIMER_P2_SERVER_MAX - GET_TIMER_P2_SERVER_ADJUST));

    Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;
  }
  /* Check whether response transmission is failed  */
  else if (Dcm_TxRespStatus.ucRespFailed == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_70401 */
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
    Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
    Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
    Dcm_TxRespStatus.ucRespFailed = DCM_FALSE;
    Dcm_TxRespStatus.ucRespPending = DCM_FALSE;
    Dcm_TxRespStatus.ucFirstPageTrans = DCM_FALSE;
    Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
    Dcm_TxRespStatus.ucFailedInd = DCM_FALSE;
    Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;

    Dcm_GblNormalReq = DCM_FALSE;

    /* Add this code #6174 by Jin 170104 */
    Dcm_DslStatusReset();
  }
  else
  #endif
  {
    if (DCM_TRUE == Dcm_IsNormalResponseReady())
    {
      if ((LpPduInfo->SduLength == 0U) && (Dcm_GddTxResponseLen != 0U))
      {
        /* @Trace: Dcm_SUD_API_70402 */
        //LpPduInfo->SduLength = (uint8)Dcm_GddTxResponseLen;
        *AvailableDataPtr = (PduLengthType)Dcm_GddTxResponseLen;
        *pReturnValue = BUFREQ_E_BUSY;
      }

      /*
       * Check if the requested length is less than or equal to
       * remaining response bytes to be transmitted
       */
      if ((LpPduInfo->SduLength != 0U) && (LpPduInfo->SduLength <= Dcm_GddTxResponseLen))
      {
        /* @Trace: SRS_Diag_04147 */
        /* @Trace: SWS_Dcm_01186 */
        #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        LucPagedSduIsFull = DCM_FALSE;
        *pReturnValue = BUFREQ_E_BUSY;

        if (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
        {
          if (LpPduInfo->SduLength > Dcm_GulFilledSduLength)
          {
            LulSduLengthToFill = LpPduInfo->SduLength - Dcm_GulFilledSduLength;

            /* Fill the PagedResData */
            if (LulSduLengthToFill > Dcm_GstMsgContext.resDataLen)
            {
              /* @Trace: Dcm_SUD_API_70403 */
              /* Copy from resData to PagedResData */
              Dcm_MemCopy(&Dcm_GaaFilledPagedSdu[Dcm_GulFilledSduLength], Dcm_GstMsgContext.resData, Dcm_GstMsgContext.resDataLen);

              /* Update PagedDataLen */
              Dcm_GulFilledSduLength += Dcm_GstMsgContext.resDataLen;

              /* Update resData */
              Dcm_GstMsgContext.resData = &Dcm_GstMsgContext.resData[Dcm_GstMsgContext.resDataLen];

              /* Update resDataLen */
              Dcm_GstMsgContext.resDataLen = DCM_ZERO;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_70404 */
              /* Copy from resData to PagedResData */
              Dcm_MemCopy(&Dcm_GaaFilledPagedSdu[Dcm_GulFilledSduLength], Dcm_GstMsgContext.resData, LulSduLengthToFill);

              /* Update PagedDataLen */
              Dcm_GulFilledSduLength += LulSduLengthToFill;

              /* Update resData */
              Dcm_GstMsgContext.resData = &Dcm_GstMsgContext.resData[LulSduLengthToFill];

              /* Update resDataLen */
              Dcm_GstMsgContext.resDataLen -= LulSduLengthToFill;

              /* Update Paged Transmit Flag */
              LucPagedSduIsFull = DCM_TRUE;
            }
          }
          else
          {
            /* @Trace: Dcm_SUD_API_70405 */
            LucPagedSduIsFull = DCM_TRUE;
          }

          /* Copy paged data */
          if (LucPagedSduIsFull == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_70406 */
            Dcm_MemCopy(LpPduInfo->SduDataPtr, Dcm_GaaFilledPagedSdu, LpPduInfo->SduLength);

            Dcm_GulFilledSduLength -= LpPduInfo->SduLength;

            /* Decrement the total response length by the size of the buffer provided  */
            Dcm_GddTxResponseLen = (Dcm_GddTxResponseLen - (LpPduInfo->SduLength));

            *pReturnValue = BUFREQ_OK;
            *AvailableDataPtr = (PduLengthType)Dcm_GddTxResponseLen;
          }

          /* Check if the response length is ZERO */
          /* IG issue protection code : BSG */
          if ((Dcm_GstMsgContext.resDataLen == 0U)
              && (Dcm_GddTxResponseLen != 0U))
          {
            /* @Trace: Dcm_SUD_API_70407 */
            /* Update the bit flag for the page transmitted from DSL layer to FALSE */
            Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;
            Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_70408 */
            Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
          }
        }
        else
        #endif
        {
          /* Copy no paged data */
          Dcm_MemCopy(LpPduInfo->SduDataPtr, Dcm_GstMsgContext.resData, LpPduInfo->SduLength);

          /* Check if the requested length is greater than the filled page length */
          if (Dcm_GstMsgContext.resDataLen < LpPduInfo->SduLength)
          {
            /* @Trace: Dcm_SUD_API_70409 */
            *AvailableDataPtr = 0U;
            Dcm_GstMsgContext.resDataLen = 0U;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_70410 */
            Dcm_GstMsgContext.resData = &Dcm_GstMsgContext.resData[LpPduInfo->SduLength];
            Dcm_GstMsgContext.resDataLen -= LpPduInfo->SduLength;
          }

          Dcm_GddTxResponseLen -= LpPduInfo->SduLength;

          *pReturnValue = BUFREQ_OK;
          *AvailableDataPtr = (PduLengthType)Dcm_GddTxResponseLen;
          
          /* Update the flag for buffer provided to TRUE */
          Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
        }
      }
      else
      {
        /* Update the flag for buffer provided to TRUE */
        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
      }

      if (Dcm_GddTxResponseLen == 0U)
      {
        /* @Trace: Dcm_SUD_API_70411 */
        Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;
        Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;

        /* Trigger to handle in TxConfirmation */
        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_CopyTxData                                      **
**                                                                            **
** Service ID           : 0x43                                                **
**                                                                            **
** Description          : This service request the DCM module to provide the  **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async          :  Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Retry                                           **
**                                                                            **
** InOut Parameters     : Info                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00092 */
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyTxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  /* @Trace: Dcm_SUD_API_70412 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  boolean ChkVal = Dcm_ValidateCopyTxData(Id, Info, Retry, AvailableDataPtr);
  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: SWS_Dcm_00832 */
    /* @Trace: Dcm_SUD_API_70413 */
    RetVal = Dcm_ProcessCopyTxData(Id, Info, Retry, AvailableDataPtr);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateCopyTxData                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate the input arguments of copy tx data        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry, AvailableDataPtr                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ValidateCopyTxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  /* @Trace: Dcm_SUD_API_70414 */
  uint8 ApiId = DCM_COPY_TXDATA_SID;

  /* Check init & inputs arguments */
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkP2Const(ApiId, Info));
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, AvailableDataPtr));

  DCM_UNUSED(Id);
  DCM_UNUSED(Retry);
  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyTxData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for copy tx data              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  Dcm_ProcessCopyTxDataFunType DispatchTable[DCM_COPY_TX_MAX_NUM] = {
    Dcm_ProcessCopyTxData_NormalRequest
    , Dcm_ProcessCopyTxData_DeclinedRequest
    , Dcm_ProcessCopyTxData_PeriodicRequest
    , Dcm_ProcessCopyTxData_RoeRequest
    , Dcm_ProcessCopyTxData_RejectedRequest
  };

  /* @Trace: Dcm_SUD_API_70415 */
  Dcm_CopyTxStateType CopyTxState = Dcm_JudgeCopyTxDataState(Id);
  RetVal = DispatchTable[CopyTxState](Id, Info, Retry, AvailableDataPtr);

  DCM_UNUSED(Retry);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeCopyTxDataState                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Copy Tx Data State                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_CopyTxStateType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70416 */
  Dcm_CopyTxStateType CopyTxState = DCM_COPY_TX_REQ_REJECTED;

  Dcm_JudgeCopyTxDataStateFunType DispatchTable[] = {
    Dcm_JudgeCopyTxDataState_RoeRequest
    , Dcm_JudgeCopyTxDataState_PeriodicRequest
    , Dcm_JudgeCopyTxDataState_DeclinedRequest
    , Dcm_JudgeCopyTxDataState_NormalRequest
    , NULL_PTR // last item to stop the loop
  };

  uint8 idx = 0U;
  while ((DispatchTable[idx] != NULL_PTR)
         && (CopyTxState == DCM_COPY_TX_REQ_REJECTED))
  {
    /* @Trace: Dcm_SUD_API_70417 */
    CopyTxState = DispatchTable[idx](Id);
    idx++;
  }

  return CopyTxState;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeCopyTxDataState_RoeRequest                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Copy Tx Data State in case Roe Request        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_CopyTxStateType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_RoeRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70418 */
  Dcm_CopyTxStateType CopyTxState = DCM_COPY_TX_REQ_REJECTED;

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) \
       && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  uint8 IsPrtclType2 = Dcm_IsProtocolType2(Dcm_GddRxPduId);

  if ((DCM_TRUE == IsPrtclType2) &&
      (Dcm_GucResOnEventStatus == DCM_ROEONGOING))
  {
    if (Dcm_GddDcmTxConfPduId == Id)
    {
      /* @Trace: Dcm_SUD_API_70419 */
      CopyTxState = DCM_COPY_TX_REQ_ROE;
    }
  }
  #else
  DCM_UNUSED(Id);
  #endif

  return CopyTxState;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeCopyTxDataState_PeriodicRequest            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Copy Tx Data State in case Periodic Request   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_CopyTxStateType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_PeriodicRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70420 */
  Dcm_CopyTxStateType CopyTxState = DCM_COPY_TX_REQ_REJECTED;

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_PduIdTablePtrType LpPduIdTable;
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddPerStatus.ddRxPduId];

  Dcm_PeriodicTxPduPtrType LpPerTxPdu;
  LpPerTxPdu = &LpPduIdTable->pPerTxPdu[Dcm_GddPerStatus.ucTxPduIdx];

  if ((Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
      && (LpPerTxPdu->usPerTxConfirmPduId == Id))
  {
    /* @Trace: Dcm_SUD_API_70421 */
    CopyTxState = DCM_COPY_TX_REQ_PERI;
  }
  #else
  DCM_UNUSED(Id);
  #endif

  return CopyTxState;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeCopyTxDataState_DeclinedRequest            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Copy Tx Data State in case Declined Request   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_CopyTxStateType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_DeclinedRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70422 */
  Dcm_CopyTxStateType CopyTxState = DCM_COPY_TX_REQ_REJECTED;

  #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
  if ((Dcm_GddSecDeclConfTxPduId == Id)
      && (Dcm_GblSecDeclRequest == DCM_TRUE))
  {
    /* @Trace: Dcm_SUD_API_70423 */
    CopyTxState = DCM_COPY_TX_REQ_DECLINED;
  }
  #else
  DCM_UNUSED(Id);
  #endif

  return CopyTxState;
}

/*******************************************************************************
** Function Name        : Dcm_JudgeCopyTxDataState_NormalRequest              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Copy Tx Data State in case Normal Request     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id                                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_CopyTxStateType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_CopyTxStateType, DCM_CODE) Dcm_JudgeCopyTxDataState_NormalRequest(
  PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_70424 */
  Dcm_CopyTxStateType CopyTxState = DCM_COPY_TX_REQ_REJECTED;

  Dcm_PduIdTablePtrType pPduIdTable;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint8 NetworkId = pPduIdTable->ComMChannelId;
  boolean IsFullComMode = Dcm_IsInFullComMode(NetworkId);
  boolean ChkComMChannel = Dcm_ChkComMChannel(DCM_COPY_TXDATA_SID, NetworkId);
  
  if ((DCM_IS_SET_PDU_STATUS(pPduIdTable))
      && (DCM_TRUE == ChkComMChannel)
      && (DCM_TRUE == IsFullComMode)
      && (Dcm_GddDcmTxConfPduId == Id))
  {
    /* @Trace: Dcm_SUD_API_70425 */
    CopyTxState = DCM_COPY_TX_REQ_NORMAL;
  }

  return CopyTxState;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyTxData_NormalRequest                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Tx Data in case Normal Request         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_NormalRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  /* @Trace: Dcm_SUD_API_70426 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  /* @Trace: SWS_Dcm_00346 */
  Dcm_CbkInternal_CopyTxData(&RetVal, Info, AvailableDataPtr);

  /* @Trace: SWS_Dcm_00350 */
  if (RetVal == BUFREQ_E_NOT_OK)
  {
    /* @Trace: Dcm_SUD_API_70427 */
    Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_TRUE;
  }

  DCM_UNUSED(Id);
  DCM_UNUSED(Retry);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyTxData_DeclinedRequest               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Tx Data in case Declined Request       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_DeclinedRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;
  #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
  /* @Trace: Dcm_SUD_API_70428 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId_DeclinedRequest];

  uint8 NetworkId = pPduIdTable->ComMChannelId;
  boolean IsInFullComMode = Dcm_IsInFullComMode(NetworkId);

  if ((DCM_TRUE == Dcm_ChkComMChannel(DCM_COPY_TXDATA_SID, NetworkId))
      && (DCM_TRUE == IsInFullComMode))
  {
    /* @Trace: SWS_Dcm_00346 */
    /* @Trace: Dcm_SUD_API_70429 */
    Dcm_CopyNegResp_DeclinedRequest(Info->SduDataPtr, Info->SduLength);

    *AvailableDataPtr = 0U;
    RetVal = BUFREQ_OK;
  }
  #else
  DCM_UNUSED(Info);
  DCM_UNUSED(AvailableDataPtr);
  #endif

  DCM_UNUSED(Id);
  DCM_UNUSED(Retry);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyTxData_PeriodicRequest               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Tx Data in case Periodic Request       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Justified:Low] Justify with annotations */
/* polyspace +1 DEFECT:DEAD_CODE [Justified:Low] "Dcm_GpEncodeByte depend on configuration. No Impact" */
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_PeriodicRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  /* @Trace: Dcm_SUD_API_70430 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  /* @Trace: Dcm_SUD_API_70431 */
  RetVal = Dcm_DslCopyPeriodicTxData(Id, Info, AvailableDataPtr);
  #else
  DCM_UNUSED(Id);
  DCM_UNUSED(Info);
  DCM_UNUSED(AvailableDataPtr);
  #endif

  DCM_UNUSED(Retry);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyTxData_RoeRequest                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Tx Data in case Roe Request            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_RoeRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  /* @Trace: Dcm_SUD_API_70432 */
  BufReq_ReturnType RetVal = BUFREQ_E_NOT_OK;

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) \
       && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  /* @Trace: Dcm_SUD_API_70433 */
  RetVal = Dcm_DslCopyROETxData(Info, AvailableDataPtr);
  #else
  DCM_UNUSED(Info);
  DCM_UNUSED(AvailableDataPtr);
  #endif

  DCM_UNUSED(Id);
  DCM_UNUSED(Retry);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessCopyTxData_RejectedRequest               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Copy Tx Data in case Rejected Request       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Id, Info, Retry                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : AvailableDataPtr                                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProcessCopyTxData_RejectedRequest(
  PduIdType Id
  , PduInfoConstPtrType Info
  , RetryInfoConstPtrType Retry
  , PduLengthPtrType AvailableDataPtr)
{
  /* @Trace: SWS_Dcm_00350 */
  /* @Trace: Dcm_SUD_API_70434 */
  Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_TRUE;

  DCM_UNUSED(Id);
  DCM_UNUSED(Info);
  DCM_UNUSED(Retry);
  DCM_UNUSED(AvailableDataPtr);
  return BUFREQ_E_NOT_OK;
}

/*******************************************************************************
** Function Name        : Dcm_DslCopyPeriodicTxData                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service request the DCM module to provide the  **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmTxPduId                                          **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : TxDataCntPtr                                        **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_DslCopyPeriodicTxData(
  PduIdType DcmTxPduId,
  PduInfoConstPtrType PduInfoPtr,
  PduLengthPtrType TxDataCntPtr)
{
  /* @Trace: Dcm_SUD_API_70435 */
  BufReq_ReturnType LddReturnValue = BUFREQ_E_NOT_OK;

  Dcm_PduIdTablePtrType LpPduIdTable;
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddPerStatus.ddRxPduId];

  Dcm_PeriodicTxPduPtrType LpPerTxPdu;
  LpPerTxPdu = &LpPduIdTable->pPerTxPdu[Dcm_GddPerStatus.ucTxPduIdx];

  uint8 LucIdx;
  uint8 LucDataBufferIdx = DCM_ZERO;
  boolean LblPeriodicStatus = DCM_FALSE;

  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) LddPduInfoPtr;
  
  LddPduInfoPtr = PduInfoPtr;

  if (Dcm_GaaCommMode[LpPduIdTable->ComMChannelId] == DCM_FULL_COMMUNICATION)
  {
    /* @Trace: Dcm_SUD_API_70436 */
    for (LucIdx = DCM_ZERO; LucIdx < LpPduIdTable->ucNumPerTxPdu; LucIdx++)
    {
      SchM_Enter_Dcm_ProtclProtection();
      if ((DCM_PDID_IS_SET_PDU_STATUS(LpPerTxPdu)) && 
          (DcmTxPduId == LpPerTxPdu->usPerTxConfirmPduId))
      {
        /* @Trace: Dcm_SUD_API_70437 */
        LucDataBufferIdx = LpPerTxPdu->ucDataBufferId;
        SchM_Exit_Dcm_ProtclProtection();

        LblPeriodicStatus = DCM_TRUE;
        break;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70438 */
        SchM_Exit_Dcm_ProtclProtection();
        LpPerTxPdu++;
      }
    }

    if (LblPeriodicStatus == DCM_TRUE)
    {
      uint32 LulDataLen = Dcm_GaaPerDataInfo[LucDataBufferIdx].ulDataLen;

      if (LddPduInfoPtr->SduLength == DCM_ZERO)
      {
        /* @Trace: Dcm_SUD_API_70439 */
        *TxDataCntPtr = (PduLengthType) LulDataLen;
        LddReturnValue = BUFREQ_E_BUSY;
      }
      /* polyspace +1 MISRA-C:12.1 [Justified:Low] Justify with annotations */
      if (((LddPduInfoPtr->SduLength != DCM_ZERO) && (PduInfoPtr->SduLength) <= LulDataLen) && (LulDataLen != DCM_ZERO))
      {
        /* @Trace: Dcm_SUD_API_70440 */
        uint32 LulNoOfBytes = PduInfoPtr->SduLength;
        LucIdx = (uint8)DCM_ZERO;
        do
        {
          /* Update 32 bit information */
          SchM_Enter_Dcm_ProtclProtection();

          LddPduInfoPtr->SduDataPtr[LucIdx] = Dcm_GaaPerDataInfo[LucDataBufferIdx].pDataBuffer[LucIdx];

          SchM_Exit_Dcm_ProtclProtection();
          LucIdx++;
          LulNoOfBytes--;
        } while(LulNoOfBytes != DCM_ZERO);


        SchM_Enter_Dcm_ProtclProtection();

        Dcm_GaaPerDataInfo[LucDataBufferIdx].ulDataLen -= PduInfoPtr->SduLength;

        LulDataLen = Dcm_GaaPerDataInfo[LucDataBufferIdx].ulDataLen;
        SchM_Exit_Dcm_ProtclProtection();

        if (PduInfoPtr->SduLength > LulDataLen)
        {
          /* @Trace: Dcm_SUD_API_70441 */
          *TxDataCntPtr = DCM_ZERO;

          /* Update the available response length to ZERO */
          SchM_Enter_Dcm_ProtclProtection();
          Dcm_GaaPerDataInfo[LucDataBufferIdx].ulDataLen = DCM_ZERO;
          SchM_Exit_Dcm_ProtclProtection();
        }
        else
        {
          /* @Trace: Dcm_SUD_API_70442 */
          /* Update the variable for providing buffer as TRUE */
          SchM_Enter_Dcm_ProtclProtection();
          Dcm_GaaPerDataInfo[LucDataBufferIdx].pDataBuffer = 
             &Dcm_GaaPerDataInfo[LucDataBufferIdx].pDataBuffer[PduInfoPtr->SduLength];
          Dcm_GaaPerDataInfo[LucDataBufferIdx].ulDataLen -= PduInfoPtr->SduLength;
          SchM_Exit_Dcm_ProtclProtection();
        }

        LddReturnValue = BUFREQ_OK;

        if (LulDataLen != DCM_ZERO)
        {
          /* @Trace: Dcm_SUD_API_70443 */
          Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70444 */
        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
      }
    }
  }

  return (LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_TpTxConfirmation                                **
**                                                                            **
** Service ID           : 0x48                                                **
**                                                                            **
** Description          : This service confirms the transmission of the       **
**                        complete request, the buffer will be unlocked       **
**                        after this confirmation function                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Result                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00351 SWS_Dcm_00624 */
FUNC(void, DCM_APPL_CODE) Dcm_TpTxConfirmation(
  PduIdType Id
  , Std_ReturnType Result)
{
  /* @Trace: Dcm_SUD_API_70445 */
  uint8 ApiId = DCM_TP_TX_CONFIRMATION_SID;

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  uint8 LucIsS3TimerStart = DCM_TRUE;
  #endif

  boolean ChkVal = Dcm_ChkInit(ApiId);

  if (DCM_TRUE == ChkVal)
  {
    #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)    
    if((Dcm_GddSecDeclConfTxPduId == Id)  && (Dcm_GblSecDeclRequest == DCM_TRUE))
    {
      /* @Trace: Dcm_SUD_API_70455 */
      Dcm_GblSecDeclRequest = DCM_FALSE;
      Dcm_GddSecDeclTxPduId = 0U;
      Dcm_GddSecDeclConfTxPduId = 0U;
      Dcm_GddRxPduId_DeclinedRequest = 0U;
      Dcm_ClearNegResp_DeclinedRequest();
    }
    else
    #endif
    {
      if (
        (
          ((Dcm_PrtclTxBufStatus.ucBufferProvided == DCM_TRUE) || (Dcm_PrtclTxBufStatus.ucCopyTxRejected == DCM_TRUE))
          &&
          (Dcm_GddDcmTxConfPduId == Id) // tx confirmation if for normal response 
          &&
          (Dcm_GblNormalReq == DCM_TRUE)
        )

        #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        || (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
        #endif

        #if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
        || (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
        #endif
      )
      {
        if (Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
        {
          if (Dcm_TxRespStatus.ucNormResponse == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_70446 */
            Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;

            /* @Trace: SWS_Dcm_00352 */
            Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
            Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;

            /* @Trace: SWS_Dcm_00241 */
            SchM_Enter_Dcm_RxPduIdProtection();
            DCM_CLR_PDU_STATUS(&Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId]);
            Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucReceiveStatus = DCM_RECEPTION_IDLE;
            SchM_Exit_Dcm_RxPduIdProtection();

            uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);
            if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
            {
              if (NULL_PTR != Dcm_GaaProtocolConfig[ProtocolIdx].pProtocolStatus)
              {
                /* @Trace: Dcm_SUD_API_70447 */
                SchM_Enter_Dcm_ProtclProtection();
                DCM_CLR_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]);
                SchM_Exit_Dcm_ProtclProtection();
              }
            }

            /* A request is completed and new request can be accepted */
            Dcm_GblNormalReq = DCM_FALSE;
          }

          /* @Trace: SWS_Dcm_01073 */
          #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
          if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_70448 */
            Dcm_PduIdTablePtrType LpPduIdTable;
            LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddPerStatus.ddRxPduId];

            Dcm_PeriodicTxPduPtrType LpPerTxPdu;
            LpPerTxPdu = &LpPduIdTable->pPerTxPdu[Dcm_GddPerStatus.ucTxPduIdx];
            uint8 TxBufferId = LpPerTxPdu->ucDataBufferId;

            /* Reset status for next transmission */
            LpPerTxPdu->blBusyStatus = DCM_FALSE;

            SchM_Enter_Dcm_ProtclProtection();
            DCM_PDID_CLR_PDU_STATUS(LpPerTxPdu);
            Dcm_GaaPerDataInfo[TxBufferId].ucDataStatus = DCM_PDID_DATA_IDLE;
            SchM_Exit_Dcm_ProtclProtection();

            /* Send PDID in next channel */
            if ((Dcm_GddPerStatus.ucTxPduIdx + DCM_ONE) < LpPduIdTable->ucNumPerTxPdu)
            {
              /* @Trace: Dcm_SUD_API_70449 */
              Dcm_GddPerStatus.ucTxPduIdx++;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_70450 */
              Dcm_GddPerStatus.ucTxPduIdx = DCM_ZERO;
            }

            /* when Pdid transmission, S3timer should not be restart*/
            LucIsS3TimerStart = DCM_FALSE;
          }

          /* In case initial request, check if enable periodic transmission */
          if (Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_70451 */
            Dcm_GddPerStatus.blOnResTrans = DCM_TRUE;
            Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
          }
          #endif

          /* @Trace: SRS_Diag_04019 */
          /* @Trace: SWS_Dcm_00235 */
          Dcm_DsdConfirmation(Result);

          /* Restart the S3 server Timer */
          if (DCM_TRUE == Dcm_IsNonDefaultSession())
          {
            #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
            if (DCM_TRUE == LucIsS3TimerStart)
            #endif
            {
              /* @Trace: Dcm_SUD_API_70452 Dcm_SUD_API_70466 */
              Dcm_StartTimer(DCM_S3SERVER_TIMER, GET_TIMER_S3_SERVER);
            }
          }
          else
          {
            /* @Trace: Dcm_SUD_API_70453 */
            /* @Trace: SWS_Dcm_01374 SWS_Dcm_01378 */
            Dcm_TriggerEventActivationDiagnostic(AD_TE_FINISHED_REQUEST);
          }

          /* @Trace: SWS_Dcm_01482 */
          #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
          (void)Dcm_TriggerTimerFallbackToDeauthenticatedState();
          #endif

          Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_70454 */
          Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_FALSE;

          /* Update the local variable to DCM_TRUE for clearing the status and
            to start the S3 server Timer */
          Dcm_DslStatusReset();
        }
      }
      else
      {
        /* Do nothing */
      }

    
      /* Check if the normal request is ongoing */
      if (
        (Dcm_TxRespStatus.ucNegResp == DCM_TRUE)
        &&
        (Dcm_GddDcmTxConfPduId == Id)  // tx confirmation id for normal request
      )
      {
        if (Dcm_MemServicePendingStatus.ucStartProtocolFailed == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_70456 */
          Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_FALSE;

          /* Update the local variable to DCM_TRUE for clearing the status and
            to start the S3 server Timer */
          Dcm_DslStatusReset();
        }

        if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
        {
          if (E_OK != Result)
          {
            /* @Trace: Dcm_SUD_API_70457 */
            Dcm_TriggerCancelPendingOperation = DCM_TRUE;
          }

          /* @Trace: SWS_Dcm_00117 */
          /* @Trace: Dcm_SUD_API_70458 */
          Dcm_DsdConfirmation(Result);
        }

        /* @Trace: Dcm_SUD_API_70459 */
        Dcm_TxRespStatus.ucNegResp = DCM_FALSE;

        /* #6972 Clear ucNeedFailedConfiramtion for DCM_RES_POS_OK */
        Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
        Dcm_GblRespPendConfirmation = DCM_TRUE;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslCopyROETxData                                **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service request the DCM module to provide the  **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduInfoPtr                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : TxDataCntPtr                                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpRoeMsgContext            **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) \
     && (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DslCopyROETxData(
  PduInfoConstPtrType PduInfoPtr,
  PduLengthPtrType TxDataCntPtr)
{
  /* @Trace: Dcm_SUD_API_70460 */
  Std_ReturnType LddReturnValue = BUFREQ_E_NOT_OK;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) PduIdTablePtr;
  uint32 LulDataLen;

  PduIdTablePtr = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
  uint8 LucNetworkId = PduIdTablePtr->ComMChannelId;

  if (Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
  {
    if(PduInfoPtr->SduLength == DCM_ZERO)
    {
      /* @Trace: Dcm_SUD_API_70461 */
      *TxDataCntPtr = (PduLengthType) Dcm_GpRoeMsgContext->resDataLen;
      LddReturnValue = BUFREQ_E_BUSY;
    }

    /* @Trace: Dcm_SUD_API_70462 */
    SchM_Enter_Dcm_ProtclProtection();
    LulDataLen = Dcm_GpRoeMsgContext->resDataLen;
    SchM_Exit_Dcm_ProtclProtection();

    if ((PduInfoPtr->SduLength != DCM_ZERO) && (PduInfoPtr->SduLength <= LulDataLen))
    {
      Dcm_MemCopy(PduInfoPtr->SduDataPtr 
        , Dcm_GpRoeMsgContext->resData
        , PduInfoPtr->SduLength);

      SchM_Enter_Dcm_ProtclProtection();
      LulDataLen = Dcm_GpRoeMsgContext->resDataLen;
      SchM_Exit_Dcm_ProtclProtection();

      /* Check if the requested length is greater than the filled page length */
      if (LulDataLen < PduInfoPtr->SduLength)
      {
        /* @Trace: Dcm_SUD_API_70463 */
        *TxDataCntPtr = DCM_ZERO;
        LulDataLen = DCM_ZERO;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70464 */
        SchM_Enter_Dcm_ProtclProtection();
        Dcm_GpRoeMsgContext->resData = &Dcm_GpRoeMsgContext->resData[
          PduInfoPtr->SduLength];

        Dcm_GpRoeMsgContext->resDataLen -= PduInfoPtr->SduLength;
        SchM_Exit_Dcm_ProtclProtection();
      }

      LulDataLen -= PduInfoPtr->SduLength;
      LddReturnValue = E_OK;
      *TxDataCntPtr = LulDataLen;
    }

    SchM_Enter_Dcm_ProtclProtection();
    LulDataLen = Dcm_GpRoeMsgContext->resDataLen;
    SchM_Exit_Dcm_ProtclProtection();

    if (LulDataLen == DCM_ZERO)
    {
      /* @Trace: Dcm_SUD_API_70465 */
      Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
    }
  }
  
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsFuncTesterPresentWithSuppressionRequested     **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function to check incoming request is tester        **
**                        present with suppression or not                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsFuncTesterPresentWithSuppressionRequested (
  PduIdType Id
 , PduInfoConstPtrType Info )
{
  boolean retVal;
  Dcm_PduIdTablePtrType pPduIdTable;
  boolean IsFunctionalRequest;

  retVal = DCM_FALSE;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  IsFunctionalRequest = Dcm_IsFunctionalRequest(pPduIdTable);

  if ((2U == Info->SduLength )
      && ((uint8) 0x3E == Info->SduDataPtr[0])
      && ((uint8) 0x80 == Info->SduDataPtr[1])
      && (DCM_TRUE == IsFunctionalRequest)
      )
  {
    retVal = DCM_TRUE;
    if (DCM_TRUE == Dcm_IsDiffConnection(Dcm_GddRxPduId, Id))
    {
      Dcm_GusFuncTesterPresentRequested = DCM_TRANSPARENT_TESTER_PRESENT;
    }
    else 
    {
      Dcm_GusFuncTesterPresentRequested = DCM_CONCURENT_TESTER_PRESENT;
    }
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_TxConfirmation                                  **
**                                                                            **
** Service ID           : 0x48                                                **
**                                                                            **
** Description          : This service confirms the transmission of a PDU,    **
**                        or the failure to transmit a PDU                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Result                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00351 SWS_Dcm_00624 SWS_Dcm_01073 */
/* this function is only called in case PeriodicTransmission */
FUNC(void, DCM_APPL_CODE) Dcm_TxConfirmation(
  PduIdType Id
  , Std_ReturnType Result)
{
  uint8 ApiId = DCM_TX_CONFIRMATION_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);

  if (DCM_TRUE == ChkVal)
  {
    if ((((Dcm_PrtclTxBufStatus.ucBufferProvided == DCM_TRUE)
         || (Dcm_PrtclTxBufStatus.ucCopyTxRejected == DCM_TRUE))
           && (Dcm_GddDcmTxConfPduId == Id)
           && (Dcm_GblNormalReq == DCM_TRUE))

        #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        || (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
        #endif
       )
    {
      if (Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
      {
        if (Dcm_TxRespStatus.ucNormResponse == DCM_TRUE)
        {
          Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;

          /* @Trace: SWS_Dcm_00241 */
          SchM_Enter_Dcm_RxPduIdProtection();
          DCM_CLR_PDU_STATUS(&Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId]);
          Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucReceiveStatus = DCM_RECEPTION_IDLE;
          SchM_Exit_Dcm_RxPduIdProtection();

          uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);
          if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
          {
            if (NULL_PTR != Dcm_GaaProtocolConfig[ProtocolIdx].pProtocolStatus)
            {
              SchM_Enter_Dcm_ProtclProtection();
              DCM_CLR_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]);
              SchM_Exit_Dcm_ProtclProtection();
            }
          }

          /* A request is completed and new request can be accepted */
          Dcm_GblNormalReq = DCM_FALSE;
        }

        /* @Trace: SWS_Dcm_01073 */
        #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_70448 */
          Dcm_PduIdTablePtrType LpPduIdTable;
          LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddPerStatus.ddRxPduId];

          Dcm_PeriodicTxPduPtrType LpPerTxPdu;
          LpPerTxPdu = &LpPduIdTable->pPerTxPdu[Dcm_GddPerStatus.ucTxPduIdx];
          uint8 TxBufferId = LpPerTxPdu->ucDataBufferId;

          /* Reset status for next transmission */
          LpPerTxPdu->blBusyStatus = DCM_FALSE;

          SchM_Enter_Dcm_ProtclProtection();
          DCM_PDID_CLR_PDU_STATUS(LpPerTxPdu);
          Dcm_GaaPerDataInfo[TxBufferId].ucDataStatus = DCM_PDID_DATA_IDLE;
          SchM_Exit_Dcm_ProtclProtection();

          /* Send PDID in next channel */
          if ((Dcm_GddPerStatus.ucTxPduIdx + DCM_ONE) < LpPduIdTable->ucNumPerTxPdu)
          {
            /* @Trace: Dcm_SUD_API_70449 */
            Dcm_GddPerStatus.ucTxPduIdx++;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_70450 */
            Dcm_GddPerStatus.ucTxPduIdx = DCM_ZERO;
          }
        }

        /* In case initial request, check if enable periodic transmission */
        if (Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_70451 */
          Dcm_GddPerStatus.blOnResTrans = DCM_TRUE;
          Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
        }
        #endif

        /* @Trace: SRS_Diag_04019 */
        /* @Trace: SWS_Dcm_00235 */
        Dcm_DsdConfirmation(Result);

        /* Restart the S3 server Timer */
        if (DCM_FALSE == Dcm_IsNonDefaultSession())
        {
          /* @Trace: SWS_Dcm_01374 SWS_Dcm_01378 */
          Dcm_TriggerEventActivationDiagnostic(AD_TE_FINISHED_REQUEST);
        }

        /* @Trace: SWS_Dcm_01482 */
        #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
        (void)Dcm_TriggerTimerFallbackToDeauthenticatedState();
        #endif

        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
        Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;
      }
      else
      {
        Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_FALSE;

        /* Update the local variable to DCM_TRUE for clearing the status and
           to start the S3 server Timer */
        Dcm_DslStatusReset();
      }
    }
    else
    {
      #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
      if (Dcm_GblSecDeclRequest == DCM_TRUE)
      {
        Dcm_GblSecDeclRequest = DCM_FALSE;
        Dcm_GddSecDeclTxPduId = 0U;
      }
      #endif
    }

    /* Check if the normal request is ongoing */
    if ((Dcm_TxRespStatus.ucNegResp == DCM_TRUE)
        && ((Dcm_GddDcmTxConfPduId == Id)
            #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
            || (Dcm_GddSecDeclConfTxPduId == Id)
            #endif
            )
       )
    {
      if (Dcm_MemServicePendingStatus.ucStartProtocolFailed == DCM_TRUE)
      {
        Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_FALSE;

        /* Update the local variable to DCM_TRUE for clearing the status and
           to start the S3 server Timer */
        Dcm_DslStatusReset();
      }

      if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
      {
        if (E_OK != Result)
        {
          Dcm_TriggerCancelPendingOperation = DCM_TRUE;
        }

        /* @Trace: SWS_Dcm_00117 */
        Dcm_DsdConfirmation(Result);
      }

      Dcm_TxRespStatus.ucNegResp = DCM_FALSE;

      /* #6972 Clear ucNeedFailedConfiramtion for DCM_RES_POS_OK */
      Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
      Dcm_GblRespPendConfirmation = DCM_TRUE;
    }
  }
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
