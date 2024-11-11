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
**  SRC-MODULE: Dcm_ReqRespHandling.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Implementation for Response Transmission                      **
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
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.3     20-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1799                    **
** 1.0.13    10-Jul-2023   DanhTQ1        Refer #CP44-2474                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Utils.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_ReqRespHandling.h"

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
typedef enum
{
  NEG_BYTE // Negative Response SID = 0x7F
  , SID_BYTE
  , NRC_BYTE
  , NEG_RESP_LEN
} Dcm_NegRespByteType;

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static VAR(uint8, DCM_VAR) Dcm_GaaNegResp[NEG_RESP_LEN];
#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
static VAR(uint8, DCM_VAR) Dcm_GaaNegResp_DeclinedRequest[NEG_RESP_LEN];
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
#define REQ_QUEUE_SIZE (2)

typedef struct
{
  PduIdType RxPduId;
  Dcm_OpStatusType OpStatus;
} Dcm_ReqItemType;

typedef P2VAR(Dcm_ReqItemType, AUTOMATIC, DCM_APPL_DATA) Dcm_ReqItemPtrType;

typedef struct
{
  Dcm_ReqItemType Items[REQ_QUEUE_SIZE];
  uint8 Front;
  uint8 Rear;
  uint8 Size;
} Dcm_ReqQueueType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_ReqQueueType, DCM_VAR) Dcm_ReqQueue;

/* For context switching */
static VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GaaStoreMsgContext[
  DCM_NUM_OF_PDUIDTABLECONFIG];

static VAR(PduIdType, DCM_VAR) Dcm_GaaStoreTxPduId[
  DCM_NUM_OF_PDUIDTABLECONFIG];

static VAR(PduIdType, DCM_VAR) Dcm_GaaStoreTxConfPduId[
  DCM_NUM_OF_PDUIDTABLECONFIG];

/* For serialize all asynchronous C/S interface calls */
static P2VAR(void, AUTOMATIC, DCM_APPL_DATA) Dcm_PendingAsyncCsif;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Static Functions Declaration                          **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) Dcm_InitReqHandling(
  Dcm_ConfigConstPtrType pConfig);

static FUNC(void, DCM_CODE) Dcm_InitRespHandling(
  Dcm_ConfigConstPtrType pConfig);

static FUNC(void, DCM_CODE) Dcm_SetNegRespByte(
  Dcm_NegRespByteType Index, uint8 Value);

#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_IsSendingResponseOnCurrentRequest(void);

static FUNC(void, DCM_CODE) Dcm_InitReqQueue(void);

static FUNC(boolean, DCM_CODE) Dcm_IsReqQueueFull(void);

static FUNC(boolean, DCM_CODE) Dcm_IsReqQueueEmpty(void);

static FUNC(boolean, DCM_CODE) Dcm_EnReqQueue(
  Dcm_ReqItemType ReqItem);

static FUNC(boolean, DCM_CODE) Dcm_DeReqQueue(
  Dcm_ReqItemPtrType pReqItem);

static FUNC(void, DCM_CODE) Dcm_StoreRequestContext(
  PduIdType RxPduId);

static FUNC(void, DCM_CODE) Dcm_SwitchRequestContext(
  PduIdType NextRxPduId);

static FUNC(void, DCM_CODE) Dcm_DelayChangeNonDefSessionRequest(
  Dcm_ReqItemPtrType pReqItem);

static FUNC(boolean, DCM_CODE) Dcm_IsChangeNonDefSessionRequest(
  PduIdType RxPduId);
#endif

/*******************************************************************************
** Function Name        : Dcm_InitReqRespHandling                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for request and response handling   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_InitReqRespHandling(Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_20400 */
  Dcm_InitReqHandling(pConfig);
  Dcm_InitRespHandling(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_CopyNegResp                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Copy the negative response data to provided buffer  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DataLen                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pData                                               **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CopyNegResp(Dcm_Uint8PtrType pData, PduLengthType DataLen)
{
  /* @Trace: Dcm_SUD_API_20401 */
  if (DataLen <= (PduLengthType) NEG_RESP_LEN)
  {
    /* @Trace: Dcm_SUD_API_20402 */
    Dcm_MemCopy(pData, Dcm_GaaNegResp, DataLen);
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetNegResp                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the negative response data and store to PduInfo **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pPduInfo                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_GetNegResp(PduInfoPtrType pPduInfo)
{
  /* @Trace: Dcm_SUD_API_20403 */
  pPduInfo->SduDataPtr = Dcm_GaaNegResp;
  pPduInfo->SduLength = (PduLengthType) NEG_RESP_LEN;
}

/*******************************************************************************
** Function Name        : Dcm_SetNegResp                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the negative response data by Sid and Nrc code  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Sid, Nrc                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SetNegResp(uint8 Sid, uint8 Nrc)
{
  /* @Trace: Dcm_SUD_API_20404 */
  Dcm_SetNegRespByte(SID_BYTE, Sid);
  Dcm_SetNegRespByte(NRC_BYTE, Nrc);
}

/*******************************************************************************
** Function Name        : Dcm_ClearNegResp                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear SID_BYTE, NRC_BYTE of negative response data  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ClearNegResp(void)
{
  /* @Trace: Dcm_SUD_API_20405 */
  Dcm_SetNegRespByte(NEG_BYTE, DCM_NEGATIVE_RESPONSE_SID);
  Dcm_SetNegRespByte(SID_BYTE, 0);
  Dcm_SetNegRespByte(NRC_BYTE, 0);
}

/*******************************************************************************
** Function Name        : Dcm_CopyNegResp_DeclinedRequest                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Copy the negative response data to provided buffer  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DataLen                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pData                                               **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
FUNC(void, DCM_CODE) Dcm_CopyNegResp_DeclinedRequest(Dcm_Uint8PtrType pData, PduLengthType DataLen)
{
  /* @Trace: Dcm_SUD_API_70477 */
  if (DataLen <= (PduLengthType) NEG_RESP_LEN)
  {
    /* @Trace: Dcm_SUD_API_70478 */
    Dcm_MemCopy(pData, Dcm_GaaNegResp_DeclinedRequest, DataLen);
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetNegResp_DeclinedRequest                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the negative response data and store to PduInfo **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pPduInfo                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_GetNegResp_DeclinedRequest(PduInfoPtrType pPduInfo)
{
  /* @Trace: Dcm_SUD_API_70479 */
  pPduInfo->SduDataPtr = Dcm_GaaNegResp_DeclinedRequest;
  pPduInfo->SduLength = (PduLengthType) NEG_RESP_LEN;
}

/*******************************************************************************
** Function Name        : Dcm_SetNegResp_DeclinedRequest                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the negative response data by Sid and Nrc code  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Sid, Nrc                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SetNegResp_DeclinedRequest(uint8 Sid, uint8 Nrc)
{
  /* @Trace: Dcm_SUD_API_70480 */
  Dcm_GaaNegResp_DeclinedRequest[0] = 0x7F;
  Dcm_GaaNegResp_DeclinedRequest[1] = Sid;
  Dcm_GaaNegResp_DeclinedRequest[2] = Nrc;
}

/*******************************************************************************
** Function Name        : Dcm_ClearNegResp_DeclinedRequest                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear SID_BYTE, NRC_BYTE of negative response data  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ClearNegResp_DeclinedRequest(void)
{
  /* @Trace: Dcm_SUD_API_70481 */
  Dcm_GaaNegResp_DeclinedRequest[0] = 0x7F;
  Dcm_GaaNegResp_DeclinedRequest[1] = 0U;
  Dcm_GaaNegResp_DeclinedRequest[2] = 0U;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_InitReqHandling                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for request handling                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InitReqHandling(Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_20406 */
  #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
  Dcm_InitReqQueue();
  Dcm_GblProcessPendingRequest = DCM_FALSE;
  Dcm_GblAddPendingRequestToQueue = DCM_FALSE;
  Dcm_SetPendingAsyncCsif(NULL_PTR);
  #endif

  #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
  Dcm_GucSidOfDeclinedRequest = DCM_ZERO;
  #endif 

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_InitRespHandling                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for response handling               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InitRespHandling(Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_20407 */
  Dcm_ClearNegResp();
  #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
  /* @Trace: Dcm_SUD_API_70482 */
  Dcm_ClearNegResp_DeclinedRequest();
  #endif
  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_SetNegRespByte                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set negative response data by index                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Index, Value                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetNegRespByte(Dcm_NegRespByteType Index, uint8 Value)
{
  /* @Trace: Dcm_SUD_API_20408 */
  if (Index < NEG_RESP_LEN)
  {
    /* @Trace: Dcm_SUD_API_20409 */
    Dcm_GaaNegResp[Index] = Value;
  }
}

/*******************************************************************************
** Function Name        : Dcm_AddNewRequestToQueue                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Add new request data to request queue               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
FUNC(boolean, DCM_CODE) Dcm_AddNewRequestToQueue(PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_20410 */
  Dcm_ReqItemType ReqItem = { RxPduId, DCM_INITIAL };
  return Dcm_EnReqQueue(ReqItem);
}

/*******************************************************************************
** Function Name        : Dcm_AddPendingRequestToQueue                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Add pending request to request queue                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_AddPendingRequestToQueue(PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_20411 */
  boolean RetVal = DCM_FALSE;

  /* Store request/message context to switch later */
  Dcm_ReqItemType ReqItem = { RxPduId, DCM_PENDING };

  if (Dcm_EnReqQueue(ReqItem))
  {
    /* @Trace: Dcm_SUD_API_20412 */
    Dcm_StoreRequestContext(RxPduId);
    RetVal = DCM_TRUE;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetNextRequestFromQueue                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get next request from request queue                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_GetNextRequestFromQueue(void)
{
  /* @Trace: Dcm_SUD_API_20413 */
  Dcm_ReqItemType ReqItem;

  if ((DCM_FALSE == Dcm_IsSendingResponseOnCurrentRequest())
      && (DCM_TRUE == Dcm_DeReqQueue(&ReqItem)))
  {
    Dcm_DelayChangeNonDefSessionRequest(&ReqItem);

    Dcm_OpStatusType ReqStatus = ReqItem.OpStatus;

    /* @Trace: Dcm_SUD_API_20414 Dcm_SUD_API_20415 */
    Dcm_GblProcessNewRequest = (DCM_INITIAL == ReqStatus) ? \
      DCM_TRUE : DCM_FALSE;

    /* @Trace: Dcm_SUD_API_20416 Dcm_SUD_API_20417 */
    Dcm_GblProcessPendingRequest = (DCM_PENDING == ReqStatus) ? \
      DCM_TRUE : DCM_FALSE;

    Dcm_GblNormalReq = DCM_TRUE;

    /* @Trace: SWS_Dcm_01369 */
    /* Request/message context switching by PduId */
    PduIdType NextRxPduId = ReqItem.RxPduId;

    if (Dcm_GddRxPduId != NextRxPduId
        && DCM_TRUE == Dcm_GblProcessPendingRequest)
    {
      /* @Trace: Dcm_SUD_API_20418 */
      Dcm_SwitchRequestContext(NextRxPduId);
    }

    Dcm_GddRxPduId = NextRxPduId;
  }
}

/*******************************************************************************
** Function Name        : Dcm_AddCurrentPendingRequestToQueue                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Add current pending request to request queue        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_AddCurrentPendingRequestToQueue(void)
{
  /* @Trace: Dcm_SUD_API_20419 */
  if (DCM_TRUE == Dcm_GblAddPendingRequestToQueue)
  {
    /* @Trace: Dcm_SUD_API_20420 */
    Dcm_GblAddPendingRequestToQueue = DCM_FALSE;
    (void)Dcm_AddPendingRequestToQueue(Dcm_GddRxPduId);
  }
}

/*******************************************************************************
** Function Name        : Dcm_DelRequestFromQueue                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Delete request from request queue                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DelRequestFromQueue(PduIdType RxPduId)
{
  uint8 Cnt = 0;
  Dcm_ReqItemType ReqItem;

  /* @Trace: Dcm_SUD_API_20421 */
  while ((Cnt++ < REQ_QUEUE_SIZE) && (DCM_TRUE == Dcm_DeReqQueue(&ReqItem)))
  {
    if (RxPduId != ReqItem.RxPduId)
    {
      /* @Trace: Dcm_SUD_API_20422 */
      (void)Dcm_EnReqQueue(ReqItem);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_TriggerAddPendingRequestToQueue                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Trigger add pending request to queue                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_TriggerAddPendingRequestToQueue(void)
{
  /* @Trace: Dcm_SUD_API_20423 */
  if (DCM_TRUE == Dcm_GblNormalReq
      && DCM_FALSE == Dcm_GblSendResponse
      && DCM_FALSE == Dcm_TxRespStatus.ucNormResponse)
  {
    /* @Trace: Dcm_SUD_API_20424 */
    Dcm_GblAddPendingRequestToQueue = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_SetPendingAsyncCsif                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set pending asynchronous client server interface    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PendingAsyncCsif                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SetPendingAsyncCsif(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) PendingAsyncCsif)
{
  /* @Trace: Dcm_SUD_API_20425 */
  Dcm_PendingAsyncCsif = PendingAsyncCsif;
}

/*******************************************************************************
** Function Name        : Dcm_IsAsyncCsifPending                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the asynchoronous client server interface  **
**                        is in pending process                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PendingAsyncCsif                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01370 */
FUNC(boolean, DCM_CODE) Dcm_IsAsyncCsifPending(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) PendingAsyncCsif)
{
  /* @Trace: Dcm_SUD_API_20426 Dcm_SUD_API_20427 */
  boolean ChkVal = (Dcm_PendingAsyncCsif == PendingAsyncCsif) ? \
    DCM_TRUE : DCM_FALSE;

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsSendingResponseOnCurrentRequest               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if in sending response on current request     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsSendingResponseOnCurrentRequest(void)
{
  /* @Trace: Dcm_SUD_API_20428 */
  boolean RetVal = DCM_FALSE;

  if ((DCM_TRUE == Dcm_GblSendResponse)
      || (DCM_TRUE == Dcm_GblPduRTransmitResponse)
      || (DCM_TRUE == Dcm_TxRespStatus.ucNormResponse)
      || (DCM_TRUE == Dcm_TxRespStatus.ucNegResp))
  {
    /* @Trace: Dcm_SUD_API_20429 */
    RetVal = DCM_TRUE;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_InitReqQueue                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize request queue data                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InitReqQueue(void)
{
  /* @Trace: Dcm_SUD_API_20430 */
  Dcm_ReqQueue.Front = 0;
  Dcm_ReqQueue.Rear = 0;
  Dcm_ReqQueue.Size = 0;

  for (uint8 idx = 0; idx < DCM_NUM_OF_PDUIDTABLECONFIG; idx++)
  {
    Dcm_MemClear((Dcm_Uint8PtrType)&Dcm_GaaStoreMsgContext[idx], 
      sizeof(Dcm_MsgContextType));
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsReqQueueFull                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the request queue is full or not           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsReqQueueFull(void)
{
  /* @Trace: Dcm_SUD_API_20431 Dcm_SUD_API_20432 */
  return (REQ_QUEUE_SIZE == Dcm_ReqQueue.Size) ? DCM_TRUE : DCM_FALSE;
}

/*******************************************************************************
** Function Name        : Dcm_IsReqQueueEmpty                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the request queue is empty or not          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsReqQueueEmpty(void)
{
  /* @Trace: Dcm_SUD_API_20433 Dcm_SUD_API_20434 */
  return (0 == Dcm_ReqQueue.Size) ? DCM_TRUE : DCM_FALSE;
}

/*******************************************************************************
** Function Name        : Dcm_EnReqQueue                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Push data to request queue                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ReqItem                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_EnReqQueue(Dcm_ReqItemType ReqItem)
{
  /* @Trace: Dcm_SUD_API_20435 */
  boolean RetVal = DCM_FALSE;

  if (DCM_FALSE == Dcm_IsReqQueueFull())
  {
    /* @Trace: Dcm_SUD_API_20436 */
    Dcm_Uint8PtrType pRear = &Dcm_ReqQueue.Rear;

    if (DCM_FALSE == Dcm_IsReqQueueEmpty())
    {
      /* @Trace: Dcm_SUD_API_20437 */
      (*pRear)++;
      *pRear %= REQ_QUEUE_SIZE;
    }

    Dcm_ReqQueue.Items[*pRear] = ReqItem;
    Dcm_ReqQueue.Size++;

    RetVal = DCM_TRUE;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DeReqQueue                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pop data from request queue                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pReqItem                                            **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DeReqQueue(Dcm_ReqItemPtrType pReqItem)
{
  /* @Trace: Dcm_SUD_API_20438 */
  boolean RetVal = DCM_FALSE;

  if ((DCM_FALSE == Dcm_IsReqQueueEmpty())
      && (NULL_PTR != pReqItem))
  {
    /* @Trace: Dcm_SUD_API_20439 */
    Dcm_Uint8PtrType pFront = &Dcm_ReqQueue.Front;
    *pReqItem = Dcm_ReqQueue.Items[*pFront];
    Dcm_ReqQueue.Size--;

    if (DCM_FALSE == Dcm_IsReqQueueEmpty())
    {
      /* @Trace: Dcm_SUD_API_20440 */
      (*pFront)++;
      *pFront %= REQ_QUEUE_SIZE;
    }

    RetVal = DCM_TRUE;
  }

  DCM_UNUSED(pReqItem);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_StoreRequestContext                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Store the current request context                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_StoreRequestContext(PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_20441 */
  Dcm_MemCopy(
    (Dcm_Uint8PtrType)&Dcm_GaaStoreMsgContext[RxPduId]
    , (Dcm_Uint8ConstPtrType)&Dcm_GstMsgContext
    , sizeof(Dcm_MsgContextType));

  Dcm_GaaStoreTxPduId[RxPduId] = Dcm_GddDcmTxPduId;
  Dcm_GaaStoreTxConfPduId[RxPduId] = Dcm_GddDcmTxConfPduId;
}

/*******************************************************************************
** Function Name        : Dcm_SwitchRequestContext                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Switch the request context                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NextRxPduId                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SwitchRequestContext(PduIdType NextRxPduId)
{
  /* @Trace: Dcm_SUD_API_20442 */
  Dcm_MemCopy(
    (Dcm_Uint8PtrType)&Dcm_GstMsgContext
    , (Dcm_Uint8ConstPtrType)&Dcm_GaaStoreMsgContext[NextRxPduId]
    , sizeof(Dcm_MsgContextType));

  Dcm_GddDcmTxPduId = Dcm_GaaStoreTxPduId[NextRxPduId];
  Dcm_GddDcmTxConfPduId = Dcm_GaaStoreTxConfPduId[NextRxPduId];
}

/*******************************************************************************
** Function Name        : Dcm_DelayChangeNonDefSessionRequest                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Delay change non default session request            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pReqItem                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01372 */
static FUNC(void, DCM_CODE) Dcm_DelayChangeNonDefSessionRequest(
  Dcm_ReqItemPtrType pReqItem)
{
  /* @Trace: Dcm_SUD_API_20443 */
  if (NULL_PTR != pReqItem)
  {
    /* @Trace: Dcm_SUD_API_20444 */
    PduIdType NowRxPduId = Dcm_GddRxPduId;
    PduIdType NextRxPduId = pReqItem->RxPduId;

    if ((DCM_TRUE == Dcm_IsOBDRequestById(NowRxPduId))
        && (DCM_TRUE == Dcm_IsChangeNonDefSessionRequest(NextRxPduId))
        && (DCM_FALSE == Dcm_IsReqQueueEmpty()))
    {
      /* @Trace: Dcm_SUD_API_20445 */
      (void)Dcm_EnReqQueue(*pReqItem);
      (void)Dcm_DeReqQueue(pReqItem);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsChangeNonDefSessionRequest                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if is in change to non default session or not **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsChangeNonDefSessionRequest(PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_20446 */
  boolean ChkVal = DCM_FALSE;

  Dcm_BufferConfigConstPtrType pBufferCfg = Dcm_GetBufferConfigPtr(RxPduId);

  if ((NULL_PTR != pBufferCfg)
      && (NULL_PTR != pBufferCfg->pBufferArea)
      && (0x10U == pBufferCfg->pBufferArea[0U])
      && (0x01U != pBufferCfg->pBufferArea[1U]))
  {
    /* @Trace: Dcm_SUD_API_20447 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsNormalResponseNotReady                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check of normal response is not ready               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsNormalResponseNotReady(void)
{
  /* @Trace: Dcm_SUD_API_20448 */
  boolean ChkVal = DCM_FALSE;

  if ((DCM_FALSE == Dcm_TxRespStatus.ucNormResponse)
      && (DCM_FALSE == Dcm_TxRespStatus.ucNegResp)
      && (DCM_TRUE == Dcm_TxRespStatus.ucRespPending))
  {
    /* @Trace: Dcm_SUD_API_20449 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsNormalResponseReady                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if normal response is ready or not            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsNormalResponseReady(void)
{
  /* @Trace: Dcm_SUD_API_20450 */
  boolean ChkVal = DCM_FALSE;

  if ((DCM_TRUE == Dcm_TxRespStatus.ucNormResponse)
      && (DCM_FALSE == Dcm_TxRespStatus.ucNegResp))
  {
    /* @Trace: Dcm_SUD_API_20451 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsPagedResponseNotReady                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if paged response not ready                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsPagedResponseNotReady(void)
{
  /* @Trace: Dcm_SUD_API_20452 */
  boolean ChkVal = DCM_FALSE;

  if ((DCM_TRUE == Dcm_TxRespStatus.ucPagedTrans)
      && (DCM_FALSE == Dcm_TxRespStatus.ucDslPagedTrans)
      && (DCM_FALSE == Dcm_TxRespStatus.ucNormResponse)
      && (DCM_FALSE == Dcm_TxRespStatus.ucNegResp))
  {
    /* @Trace: Dcm_SUD_API_20453 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsNegRespReady                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if negative response is ready or not          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsNegRespReady(void)
{
  /* @Trace: Dcm_SUD_API_20454 Dcm_SUD_API_20455 */
  boolean ChkVal = (DCM_TRUE == Dcm_TxRespStatus.ucNegResp) ? \
    DCM_TRUE : DCM_FALSE;

  return ChkVal;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
