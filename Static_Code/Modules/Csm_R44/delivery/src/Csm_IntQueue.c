/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_IntQueue.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Internal function of CSM                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17725, Add trace SUD             **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_IntFunc.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#if (CSM_QUEUE_OPERATION_ENABLE == STD_ON)
/* Swap queue elements by their indices */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CSM_CODE) Csm_PrvQueueSwapElement
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  VAR(uint32, AUTOMATIC) index0, 
  VAR(uint32, AUTOMATIC) index1
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Compare less than queue elements' priorities by their indices */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CSM_CODE) Csm_PrvQueueCompLtElement
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue,
  VAR(uint32, AUTOMATIC) index0, 
  VAR(uint32, AUTOMATIC) index1
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Queue sift up */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CSM_CODE) Csm_PrvQueueSiftUp
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  VAR(uint32, AUTOMATIC) startIdx
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Queue sift down */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CSM_CODE) Csm_PrvQueueSiftDown
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  VAR(uint32, AUTOMATIC) startIdx
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Return the left child index of current index */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint32, CSM_CODE) Csm_PrvQueueLeftChildIndex
(
  VAR(uint32, AUTOMATIC) indexCnt
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Return the right child index of current index */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint32, CSM_CODE) Csm_PrvQueueRightChildIndex
(
  VAR(uint32, AUTOMATIC) indexCnt
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Return the parent index of current index */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint32, CSM_CODE) Csm_PrvQueueParentIndex
(
  VAR(uint32, AUTOMATIC) indexCnt
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To check whether queue is full */
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CSM_CODE) Csm_PrvIsQueueFull
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueSwapElement                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Swap queue elements by their indices                **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : index0 : index of the first element                 **
**                        index1 : index of the second element                **
**                                                                            **
** InOut parameter      : ptrQueue : Hold the pointer to queue                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CSM_CODE) Csm_PrvQueueSwapElement
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  VAR(uint32, AUTOMATIC) index0,
  VAR(uint32, AUTOMATIC) index1
)
{
  /* @Trace: Csm_SUD_FUNC_230 */
  Csm_QueueSlotType queueSlotLocal;
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  /* Swap two elements of queue */
  queueSlotLocal.SerialNo = ptrQueue->QueueBuf[index0].SerialNo;
  queueSlotLocal.CsmJob = ptrQueue->QueueBuf[index0].CsmJob;
  ptrQueue->QueueBuf[index0].SerialNo = ptrQueue->QueueBuf[index1].SerialNo;
  ptrQueue->QueueBuf[index0].CsmJob = ptrQueue->QueueBuf[index1].CsmJob;
  ptrQueue->QueueBuf[index1].SerialNo = queueSlotLocal.SerialNo;
  ptrQueue->QueueBuf[index1].CsmJob = queueSlotLocal.CsmJob;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueCompLtElement                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Compare less than queue elements' priorities by     **
**                        their indices                                       **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrQueue : Hold the pointer to queue                **
**                        index0 : index of the first element                 **
**                        index1 : index of the second element                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE : first element's priority is lower than       **
                                 second element's priority                    **
**                        FALSE : first element's priority is higher than     **
**                                second element's priority                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CSM_CODE) Csm_PrvQueueCompLtElement
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue,
  VAR(uint32, AUTOMATIC) index0, 
  VAR(uint32, AUTOMATIC) index1
)
{
  boolean result;
  Csm_JobType *localJobIndex0;
  Csm_JobType *localJobIndex1;
  uint32 localJobPriorityIndex0;
  uint32 localJobPriorityIndex1;
  uint32 localSerialNoIndex0;
  uint32 localSerialNoIndex1;

  /* @Trace: Csm_SUD_FUNC_260 */
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  localJobIndex0 = ptrQueue->QueueBuf[index0].CsmJob;
  localJobIndex1 = ptrQueue->QueueBuf[index1].CsmJob;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  localJobPriorityIndex0 = localJobIndex0->CryptoJob->jobInfo->jobPriority;
  localJobPriorityIndex1 = localJobIndex1->CryptoJob->jobInfo->jobPriority;
  /* Check order by priorities */
  if (localJobPriorityIndex0 < localJobPriorityIndex1)
  {
    /* @Trace: Csm_SUD_FUNC_261 */
    result = TRUE;
  }
  /* If order cannot be determined by priorities, check serial numbers */
  else if (localJobPriorityIndex0 == localJobPriorityIndex1)
  {
    /* @Trace: Csm_SUD_FUNC_262 */
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    localSerialNoIndex0 = ptrQueue->QueueBuf[index0].SerialNo;
    localSerialNoIndex1 = ptrQueue->QueueBuf[index1].SerialNo;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    if (localSerialNoIndex1 < localSerialNoIndex0)
    {
      result = TRUE;
    }
    else
    {
      result = FALSE;
    }
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_263 */
    result = FALSE;
  }

  return result;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueSiftUp                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Queue sift up, maintain invariant after enqueue.    **
**                        Also use to elevate job to root to delete job from  **
**                        queue                                               **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : startIdx : start index                              **
**                                                                            **
** InOut parameter      : ptrQueue : Hold the pointer to queue                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvQueueParentIndex                             **
**                        Csm_PrvQueueCompLtElement                           **
**                        Csm_PrvQueueSwapElement                             **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CSM_CODE) Csm_PrvQueueSiftUp
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue,
  VAR(uint32, AUTOMATIC) startIdx
)
{
  /* @Trace: Csm_SUD_FUNC_240 */
  uint32 cursor;
  uint32 parent;
  boolean compResult;

  cursor = startIdx;
  while (0U < cursor)
  {
    parent = Csm_PrvQueueParentIndex(cursor);
    compResult = Csm_PrvQueueCompLtElement(ptrQueue, parent, cursor);
    if (FALSE != compResult)
    {
      Csm_PrvQueueSwapElement(ptrQueue, cursor, parent);
      cursor = parent;
    }
    else
    {
      /* Break loop */
      cursor = 0U;
    }
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueSiftDown                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Queue sift down, maintain invariant after dequeue   **
**                        or delete job from queue                            **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : startIdx : start index                              **
**                                                                            **
** InOut parameter      : ptrQueue : Hold the pointer to queue                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                        Csm_PrvQueueLeftChildIndex                          **
**                        Csm_PrvQueueCompLtElement                           **
**                        Csm_PrvQueueRightChildIndex                         **
**                        Csm_PrvQueueSwapElement                             **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CSM_CODE) Csm_PrvQueueSiftDown
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue,
  VAR(uint32, AUTOMATIC) startIdx
)
{
  /* @Trace: Csm_SUD_FUNC_250 */
  uint32 cursor;
  uint32 queueSize;
  uint32 left;
  uint32 right;
  uint32 largest;

  cursor = startIdx;
  left = Csm_PrvQueueLeftChildIndex(cursor);
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  queueSize = ptrQueue->CurrentQueueSize;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  while (left < queueSize)
  {
    largest = cursor;
    if (FALSE != Csm_PrvQueueCompLtElement(ptrQueue, largest, left))
    {
      largest = left;
    }
    right = Csm_PrvQueueRightChildIndex(cursor);
    if (right < queueSize)
    {
      if (FALSE != Csm_PrvQueueCompLtElement(ptrQueue, largest, right))
      {
        largest = right;
      }
    }
    if (cursor != largest)
    {
      Csm_PrvQueueSwapElement(ptrQueue, cursor, largest);
      cursor = largest;
      left = Csm_PrvQueueLeftChildIndex(cursor);
    }
    else
    {
      /* Break loop */
      left = queueSize;
    }
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueLeftChildIndex                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Return the left child index of current index        **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : indexCnt : index of current node in queue           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32 : index of left child node in queue          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint32, CSM_CODE) Csm_PrvQueueLeftChildIndex
(
  VAR(uint32, AUTOMATIC) indexCnt
)
{
  /* @Trace: Csm_SUD_FUNC_310 */
  return ((2U * indexCnt) + 1U);
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueRightChildIndex                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Return the right child index of current index       **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : indexCnt : index of current node in queue           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32 : index of right child node in queue         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint32, CSM_CODE) Csm_PrvQueueRightChildIndex
(
  VAR(uint32, AUTOMATIC) indexCnt
)
{
  /* @Trace: Csm_SUD_FUNC_290 */
  return ((2U * indexCnt) + 2U);
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvQueueParentIndex                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Return the parent index of current index            **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : indexCnt : index of current node in queue           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32 : index of parent node in queue              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint32, CSM_CODE) Csm_PrvQueueParentIndex
(
  VAR(uint32, AUTOMATIC) indexCnt
)
{
  /* @Trace: Csm_SUD_FUNC_300 */
  return ((indexCnt - 1U)/2U);
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvIsQueueFull                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : To check whether queue is full                      **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrQueue : Hold the pointer to queue                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE : queue is full                                **
**                        FALSE : queue is not full                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CSM_CODE) Csm_PrvIsQueueFull
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA)  ptrQueue
)
{
  /* @Trace: Csm_SUD_FUNC_320 */
  boolean result = FALSE;
  uint32 queueSize;

  result = FALSE;
  /* Since CurrentQueueSize can be changed by Csm_MainFunction, therefore we
     need to have a protection here to prevent modifying CurrentQueueSize
     while checking for its value */
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  queueSize = ptrQueue->CurrentQueueSize;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  if (queueSize >= ptrQueue->MaxQueueSize)
  {
    /* @Trace: Csm_SUD_FUNC_321 */
    result = TRUE;
  }
  return result;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvGetQueueByChannelId                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get queue by channel ID                             **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : channelId : Hold the channel ID                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Csm_QueueType* : Pointer to queue                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Marco P2VAR is defined in Generic source. It is out of scope." */
FUNC(P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA), CSM_CODE) Csm_PrvGetQueueByChannelId
(
  VAR(uint32, AUTOMATIC) channelId
)
/* polyspace-end MISRA-C3:20.7 */
{
  /* @Trace: Csm_SUD_FUNC_330 */
  Csm_QueueType *ptrQueueLocal;
  uint32 i;

  ptrQueueLocal = &(Csm_QueueList[0U]);
  i = 0x0U;
  while (CSM_TOTAL_CONFIGURED_QUEUE > i)
  {
    if (channelId == Csm_QueueList[i].CryIfChannelId)
    {
      ptrQueueLocal = &(Csm_QueueList[i]);
      /* To exit the while loop */
      i = CSM_TOTAL_CONFIGURED_QUEUE;
    }
    else
    {
      i++;
    }
  }
  return ptrQueueLocal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvIsQueueEmpty                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : To check whether queue is empty                     **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrQueue : Hold the pointer to queue                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE: queue is empty                                **
**                        FALSE: queue is not empty                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CSM_CODE) Csm_PrvIsQueueEmpty
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue
)
{
  boolean result;
  uint32 queueSize;

  /* @Trace: Csm_SUD_FUNC_340 */
  result = FALSE;
  /* Since CurrentQueueSize can be changed by Csm_MainFunction,
     therefore we need to have a protection here to prevent modifying
     CurrentQueueSize while checking for its value */
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  queueSize = ptrQueue->CurrentQueueSize;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  if (0U == queueSize)
  {
    /* @Trace: Csm_SUD_FUNC_341 */
    result = TRUE;
  }
  return result;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvEnqueue                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Put job to queue, return CRYPTO_E_QUEUE_FULL if     **
**                        queue is full                                       **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : ptrQueue : Hold the pointer to queue                **
**                        ptrJob : Hold the pointer to job                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK : enqueue successfully                         **
**                        E_NOT_OK : enqueue failed                           **
**                        CRYPTO_E_QUEUE_FULL : queue is full                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                        Csm_PrvIsQueueFull                                  **
**                        Csm_PrvJobQueueExist                                **
**                        Csm_PrvIsQueueEmpty                                 **
**                        Csm_PrvQueueSiftUp                                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvEnqueue
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  P2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) ptrJob
)
{
  Std_ReturnType result;
  uint32 minSerialNo;
  uint32 idx;
  uint32 localCounter;
  uint32 queueSize;
  uint32 localSerialNo;
  boolean isQueueFull;
  boolean isQueueEmpty;

  isQueueFull = Csm_PrvIsQueueFull(ptrQueue);
  /* If queue is full, job shall not be put in queue */
  if (FALSE == isQueueFull)
  {
    /* @Trace: Csm_SUD_FUNC_271 */
    /* Put job in queue and increment current queue size */
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    localCounter = ptrQueue->Counter;
    queueSize = ptrQueue->CurrentQueueSize;
    isQueueEmpty = Csm_PrvIsQueueEmpty(ptrQueue);
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    if (FALSE == isQueueEmpty)
    {
      if (CSM_QUEUE_COUNTER_MAX > localCounter)
      {
        result = E_OK;
      }
      else
      {
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* Find minimum serial number */
        minSerialNo = ptrQueue->QueueBuf[0U].SerialNo;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        for (idx = 1U; idx < queueSize; idx++)
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          localSerialNo = ptrQueue->QueueBuf[idx].SerialNo;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
          if (localSerialNo < minSerialNo)
          {
            minSerialNo = localSerialNo;
          }
        }
        if (0U < minSerialNo)
        {
          /* Reset serial numbers */
          for (idx = 0U; idx < queueSize; idx++)
          {
            SchM_Enter_Csm_GLOBALVAR_PROTECTION();
            ptrQueue->QueueBuf[idx].SerialNo -= minSerialNo;
            SchM_Exit_Csm_GLOBALVAR_PROTECTION();
          }
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          /* Reset counter */
          ptrQueue->Counter -= minSerialNo;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
          result = E_OK;
        }
        else
        {
          /* Counter is saturated, return E_NOT_OK */
          result = E_NOT_OK;
        }
      }
    }
    else
    {
      /* @Trace: Csm_SUD_FUNC_273 */
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      /* Since queue is empty, counter could be reset */
      ptrQueue->Counter = 0U;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      result = E_OK;
    }
    
    if (E_OK == result)
    {
      /* @Trace: Csm_SUD_FUNC_272 */
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      ptrQueue->QueueBuf[queueSize].CsmJob = ptrJob;
      ptrQueue->QueueBuf[queueSize].SerialNo = localCounter;
      ptrQueue->Counter += 1U;
      ptrQueue->CurrentQueueSize += 1U;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      Csm_PrvQueueSiftUp(ptrQueue, queueSize);
    }
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_270 */
    /* SWS_Csm_01041 requires to return QUEUE_FULL error code.
    However SWS_Csm_00982 return value doesn't include CRYPTO_E_QUEUE_FULL.
    In this case, I think returning CRYPTO_E_QUEUE_FULL is acceptable.
    */
    result = CRYPTO_E_QUEUE_FULL;
  }
  return result;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvDequeue                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the highest priority job and remove it from     **
**                        queue, return NULL_PTR if queue is empty            **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : ptrQueue : Hold the pointer to queue                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Csm_JobType* : Hold the pointer to job              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                        Csm_PrvIsQueueEmpty                                 **
**                        Csm_PrvJobQueueRemove                               **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Marco P2VAR is defined in Generic source. It is out of scope." */
FUNC(P2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA), CSM_CODE) Csm_PrvDequeue
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue
)
/* polyspace-end MISRA-C3:20.7 */
{
  /* @Trace: Csm_SUD_FUNC_280 */
  Csm_JobType *ptrJobLocal;
  boolean isQueueEmpty;
  ptrJobLocal = NULL_PTR;
  isQueueEmpty = Csm_PrvIsQueueEmpty(ptrQueue);
  /* Return NULL_PTR if queue is empty */
  if (FALSE == isQueueEmpty)
  {
    /* @Trace: Csm_SUD_FUNC_281 */
    /* Get the highest priority job and remove it from queue, decrement
       current queue size */
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Get job from root position, index 0 */
    ptrJobLocal = ptrQueue->QueueBuf[0U].CsmJob;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    /* Remove job from queue */
    Csm_PrvJobQueueRemove(ptrQueue, ptrJobLocal);
  }
  return ptrJobLocal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvJobQueueExist                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if job is already in queue                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrQueue : Hold the pointer to queue                **
**                        ptrJob : Hold the pointer to job                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : indexPtr : Hold the pointer to store index of job   **
**                                   in queue                                 **
**                                                                            **
** Return parameter     : TRUE : job is already in queue                      **
**                        FALSE : job is not in queue                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CSM_CODE) Csm_PrvJobQueueExist
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  P2CONST(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) ptrJob, 
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) indexPtr
)
{
  /* @Trace: Csm_SUD_FUNC_200 */
  boolean result;
  uint32 i;
  uint32 localJobId;
  uint32 queueSize;
  Csm_JobType *ptrJobLocal;

  result = FALSE;
  localJobId = ptrJob->CryptoJob->jobId;
  i = 0x0U;
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  queueSize = ptrQueue->CurrentQueueSize;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  while (i < queueSize)
  {
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    ptrJobLocal = ptrQueue->QueueBuf[i].CsmJob;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    if (localJobId == ptrJobLocal->CryptoJob->jobId)
    {
      result = TRUE;
      if (NULL_PTR != indexPtr)
      {
        *indexPtr = i;
      }
      /* To exit the while loop */
      i = queueSize;
    }
    else
    {
      i++;
    }
  }
  return result;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvJobQueueRemove                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Remove job from queue if job is in queue            **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : ptrQueue : Hold the pointer to queue                **
**                        ptrJob : Hold the pointer to job                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvJobQueueExist                                **
**                        Csm_PrvQueueParentIndex                             **
**                        Csm_PrvQueueSiftUp                                  **
**                        Csm_PrvQueueSiftDown                                **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CSM_CODE) Csm_PrvJobQueueRemove
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  P2CONST(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) ptrJob
)
{
  /* @Trace: Csm_SUD_FUNC_210 */
  uint32 cursor;
  uint32 parent;
  boolean compResult;
  uint32 lastIndex;
  boolean isJobExistInQueue;
  cursor = 0U;
  isJobExistInQueue = Csm_PrvJobQueueExist(ptrQueue, ptrJob, &cursor);
  /* @Trace: Csm_SUD_FUNC_211 */
  /* Check if job is in queue */
  if (TRUE == isJobExistInQueue)
  {
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    lastIndex = ptrQueue->CurrentQueueSize - 1U;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    if (cursor != lastIndex)
    {
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      /* Overwrite cursor node by the rightmost node of queue */
      ptrQueue->QueueBuf[cursor].SerialNo = \
      ptrQueue->QueueBuf[lastIndex].SerialNo;
      ptrQueue->QueueBuf[cursor].CsmJob = \
      ptrQueue->QueueBuf[lastIndex].CsmJob;
      ptrQueue->QueueBuf[lastIndex].CsmJob = NULL_PTR;
      ptrQueue->CurrentQueueSize -= 1U;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      /* Maintain invariance of queue */
      if (0U < cursor)
      {
        /* If cursor's priority is higher than its parent, siftup, otherwise siftdown */
        parent = Csm_PrvQueueParentIndex(cursor);
        compResult = Csm_PrvQueueCompLtElement(ptrQueue, parent, cursor);
        if (FALSE != compResult)
        {
          Csm_PrvQueueSiftUp(ptrQueue, cursor);
        }
        else
        {
          Csm_PrvQueueSiftDown(ptrQueue, cursor);
        }
      }
      /* Cursor is at root position, e.g. dequeuing, simply siftdown */
      else
      {
        Csm_PrvQueueSiftDown(ptrQueue, cursor);
      }
    }
    else
    {
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      /* Simply remove job from queue */
      ptrQueue->QueueBuf[lastIndex].CsmJob = NULL_PTR;
      ptrQueue->CurrentQueueSize -= 1U;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    }
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_PrvIsHighestPrio                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if job has the highest priority in queue      **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrQueue : Hold the pointer to queue                **
**                        ptrJob : Hold the pointer to job                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE : job has the highest priority in queue        **
**                        FALSE : job does not have the highest priority      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                        Csm_PrvIsQueueEmpty                                 **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CSM_CODE) Csm_PrvIsHighestPrio
(
  P2CONST(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) ptrQueue, 
  P2CONST(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) ptrJob
)
{
  /* @Trace: Csm_SUD_FUNC_220 */
  Csm_JobType *ptrFirstQueueElem;
  boolean result;
  boolean isQueueEmpty;
  result = FALSE;
  isQueueEmpty = Csm_PrvIsQueueEmpty(ptrQueue);
  if (FALSE == isQueueEmpty)
  {
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    ptrFirstQueueElem = ptrQueue->QueueBuf[0U].CsmJob;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    /* Since this is a priority queue therefore we can assume that the
       first entry in a queue will always has highest priority */
    if (ptrJob->CryptoJob->jobInfo->jobPriority > \
        ptrFirstQueueElem->CryptoJob->jobInfo->jobPriority)
    {
      result = TRUE;
    }
  }
  else
  {
    /* In case queue is empty, we can assume that ptrJob has highest
       priority */
    result = TRUE;
  }
  return result;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
