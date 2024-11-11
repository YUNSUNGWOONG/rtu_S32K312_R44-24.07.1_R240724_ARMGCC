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
**  SRC-MODULE: FiM_Config.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Configurable const variable definition                        **
**              of Function Inhibition Manager                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.1    16-Mar-2021    LanhLT          Fix polyspace                      **
** 0.0.4    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.3     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.2    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM.h"         /* FiM Header File */
#include "FiM_Ram.h"     /* Ram header file */
#include "FiM_Config.h"  /* Ram header file */

#if (FIM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"         /* Det header file */
#endif

/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
#if(FIM_FIDS_SEQUENTIAL == STD_ON)
#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* The largest value of all the configured FIDs */
static const FiM_FunctionIdType Fim_Largest_FID =
  (FiM_FunctionIdType)FIM_LARGEST_FID;

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* FIM_FIDS_SEQUENTIAL == STD_ON */


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if(FIM_EN_EVENTID_BINARYSEARCH == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"
  static FUNC(boolean, FIM_CODE) FiM_EventIdBinarySearch(
  Dem_EventIdType LddEventId,
  P2VAR(FiM_EventsSizeType, AUTOMATIC, FIM_VAR)LpEventIndex);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_EventIdLinearSearch(
  Dem_EventIdType LddEventId,
  P2VAR(FiM_EventsSizeType, AUTOMATIC, FIM_VAR)LpEventIndex);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_EN_EVENTID_BINARYSEARCH == STD_ON */

#if(FIM_FIDS_SEQUENTIAL == STD_OFF)
#if(FIM_EN_FID_BINARYSEARCH == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_FidBinarySearch(
  FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR)LddFidArrayIndex);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_FidLinearSearch(
  FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR)LddFidArrayIndex);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_EN_FID_BINARYSEARCH == STD_ON */
#endif /* FIM_FIDS_SEQUENTIAL == STD_OFF */

#if(FIM_TOTAL_NUM_OF_DEM_COMPONENT >0)
#if(FIM_EN_COMPONENTID_BINARYSEARCH == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_ComponentIdBinarySearch(
  Dem_ComponentIdType LddComponentId,
  P2VAR(uint16, AUTOMATIC, FIM_VAR)LpComponentIndex);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_ComponentIdLinearSearch(
  Dem_ComponentIdType LddComponentId,
  P2VAR(uint16, AUTOMATIC, FIM_VAR)LpComponentIndex);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_EN_COMPONENTID_BINARYSEARCH == STD_ON */
#endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT >0 */

/*******************************************************************************
** Function Name        : FiM_EventIdSearch                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaEventInfo for a requested event.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddEventId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpEventIndex                                        **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, FIM_CODE) FiM_EventIdSearch(
  Dem_EventIdType LddEventId,
  P2VAR(FiM_EventsSizeType, AUTOMATIC, FIM_VAR)LpEventIndex)
{

  /* @Trace: FiM_SUD_API_039 */
  boolean LblEventExists;

  #if (FIM_EN_EVENTID_BINARYSEARCH == STD_ON)
  /* @Trace: FiM_SUD_API_040 */
  /* Check whether EventId is in the configured range - use binary search */
  LblEventExists = FiM_EventIdBinarySearch(LddEventId, LpEventIndex);
  #else
  /* @Trace: FiM_SUD_API_041 */
  LblEventExists = FiM_EventIdLinearSearch(LddEventId, LpEventIndex);
  #endif
  /* @Trace: FiM_SUD_API_042 */
  return LblEventExists;
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_ComponentIdSearch                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaComponentInfo for a requested event.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddComponentId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpComponentIndex                                    **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#if(FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, FIM_CODE) FiM_ComponentIdSearch(
  Dem_ComponentIdType LddComponentId,
  P2VAR(uint16, AUTOMATIC, FIM_VAR)LpComponentIndex)
{
  /* @Trace: FiM_SUD_API_043 */
  boolean LblEventExists;
  #if (FIM_EN_COMPONENTID_BINARYSEARCH == STD_ON)
  /* Check whether EventId is in the configured range - use binary search */
  /* @Trace: FiM_SUD_API_044 */
  LblEventExists = FiM_ComponentIdBinarySearch(LddComponentId,
      LpComponentIndex);
  #else
  /* @Trace: FiM_SUD_API_045 */
  LblEventExists = FiM_ComponentIdLinearSearch(LddComponentId,
      LpComponentIndex);
  #endif /* FIM_EN_COMPONENTID_BINARYSEARCH == STD_ON */
  /* @Trace: FiM_SUD_API_046 */
  return LblEventExists;
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : FiM_FidSearch                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaFunctionId for a requested Fid.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddFid                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LddFidArrayIndex                                    **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, FIM_CODE) FiM_FidSearch(FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR)LddFidArrayIndex)
{
  /* @Trace: FiM_SUD_API_047 */
  boolean foundFid = FIM_FALSE;

  /* Check if FID is within the configured range */
  #if (FIM_FIDS_SEQUENTIAL == STD_ON)
  /* @Trace: FiM_SUD_API_048 */
  *LddFidArrayIndex = (FiM_FidsSizeType)LddFid;
  if (LddFid > Fim_Largest_FID)
  {
    /* No require action */
  }
  else
  {
  /* @Trace: FiM_SUD_API_049 */
    foundFid = FIM_TRUE;
  }
  #else

  #if (FIM_EN_FID_BINARYSEARCH == STD_ON)
  /* @Trace: FiM_SUD_API_050 */
  foundFid = FiM_FidBinarySearch(LddFid, LddFidArrayIndex);
  #else
  /* @Trace: FiM_SUD_API_051 */
  foundFid = FiM_FidLinearSearch(LddFid, LddFidArrayIndex);
  #endif /* FIM_EN_FID_BINARYSEARCH == STD_ON */
  #endif /* FIM_FIDS_SEQUENTIAL == STD_ON */
  /* @Trace: FiM_SUD_API_052    */
  return foundFid;
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_EventIdBinarySearch                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaEventInfo for a requested event.             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddEventId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpEventIndex                                        **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaEventInfo                                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if ((FIM_EN_EVENTID_BINARYSEARCH == STD_ON) && \
    (FIM_TOTAL_NUM_OF_DEM_EVENTS > FIM_ZERO))
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_EventIdBinarySearch(
  Dem_EventIdType LddEventId, P2VAR(FiM_EventsSizeType, AUTOMATIC,
  FIM_VAR)LpEventIndex)
{
  /* @Trace: FiM_SUD_API_053 */
  Dem_EventIdType LddCurrEventId;
  FiM_EventsSizeType LddHigh;
  FiM_EventsSizeType LddLow;
  FiM_EventsSizeType LddMiddle;
  boolean LblReturn;

  /* Initialize return value with false */
  LblReturn = FIM_FALSE;

  /* Initialize LddHigh variable with number of Events */
  LddHigh = FIM_TOTAL_NUM_OF_DEM_EVENTS - FIM_ONE;
  /* Initialize LddLow variable with one */
  LddLow = FIM_ZERO;

  /* Check whether search EventId is in range */
  if ((LddEventId >= FiM_GaaEventInfo[LddLow].ddEventId) &&
  (LddEventId <= FiM_GaaEventInfo[LddHigh].ddEventId))
  {
    /* @Trace: FiM_SUD_API_054 */
    do
    {
      /* Get the middle index number */
      LddMiddle = (LddHigh + LddLow) >> FIM_ONE;

      /* Get the EventId of the middle */
      LddCurrEventId = FiM_GaaEventInfo[LddMiddle].ddEventId;

      /* Compare the current EventId with the requested one */
      if (LddCurrEventId == LddEventId)
      {
        /* @Trace: FiM_SUD_API_055 */
        /* Update the identified Event Index number in out variable */
        *LpEventIndex = LddMiddle;
        /* Update the return variable to true */
        LblReturn = FIM_TRUE;
        /* Set LddHigh to zero & LddLow = one to break the loop */
        LddHigh = FIM_ZERO;
        LddLow = FIM_ONE;
      }
      else
      {
        /* Check if the requested EventId smaller than the current EventId */
        if (LddEventId < LddCurrEventId)
        {
          /*The requested EventId is smaller than current, update LddHigh*/
          /* @Trace: FiM_SUD_API_056 */
          LddHigh = LddMiddle - FIM_ONE;
        }
        else
        {
          /* The requested EventId is greater than current, update LddLow */
          /* @Trace: FiM_SUD_API_057 */
          LddLow = LddMiddle + FIM_ONE;
        }
      } /* end if(LddCurrEventId == LddEventId) */
    }
    while (LddLow <= LddHigh);
  }
  else
  {
    /* No require action */
  }
  /* @Trace: FiM_SUD_API_058 */
  return (LblReturn);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : FiM_EventIdLinearSearch                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaEventInfo for a requested event.             **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Input Parameters     : LddEventId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpEventIndex                                        **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaEventInfo                                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if ((FIM_EN_EVENTID_BINARYSEARCH == STD_OFF) && \
    (FIM_TOTAL_NUM_OF_DEM_EVENTS > FIM_ZERO))
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_EventIdLinearSearch(
  Dem_EventIdType LddEventId,
  P2VAR(FiM_EventsSizeType, AUTOMATIC, FIM_VAR)LpEventIndex)
{
  /* @Trace: FiM_SUD_API_059 */
  boolean LblSearchResult;
  /* variable to break the FOR loop */
  FiM_EventsSizeType LddIndex;

  /* Set the search result flag to FIM_FALSE */
  LblSearchResult = FIM_FALSE;
  /* Check for LddEventId by linear search */
  for (LddIndex = FIM_ZERO; LddIndex < FIM_TOTAL_NUM_OF_DEM_EVENTS; LddIndex++)
  {
    /* @Trace: FiM_SUD_API_060 */
    /* Is EventId matches with requested EventId */
    if (FiM_GaaEventInfo[LddIndex].ddEventId == LddEventId)
    {
      /* @Trace: FiM_SUD_API_061 */
      /* Update index for Request Array Index */
      *LpEventIndex = LddIndex;
      /* Set search result flag to TRUE */
      LblSearchResult = FIM_TRUE;
      break;
    }
    else
    {
      /* No require action */
    }
  }
  /* Return FIM_TRUE if found else FIM_FALSE */
  /* @Trace: FiM_SUD_API_062 */
  return(LblSearchResult);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : FiM_FidBinarySearch                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaFunctionId for a requested Fid.              **
**                        This service is used only in case if the FIDs are   **
**                        not sequential.                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddFid                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LddFidArrayIndex                                    **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaFunctionId                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if (FIM_FIDS_SEQUENTIAL == STD_OFF)
#if ((FIM_EN_FID_BINARYSEARCH == STD_ON) && (FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO))
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_FidBinarySearch(FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR) LddFidArrayIndex)
{
  /* @Trace: FiM_SUD_API_068 */
  FiM_FunctionIdType LddCurrFid;
  FiM_FidsSizeType LddHigh;
  FiM_FidsSizeType LddLow;
  FiM_FidsSizeType LddMiddle;
  boolean LblReturn;

  LblReturn = FIM_FALSE;

  /* Initialize LddHigh variable with number of FIDs */
  LddHigh = FIM_TOTAL_NUM_OF_FIDS - FIM_ONE;
  /* Initialize LddLow variable with one */
  LddLow = FIM_ZERO;

  /* Check whether search Fid is in range */
  if ((LddFid >= FiM_GaaFunctionId[FIM_ZERO]) &&
          (LddFid <= FiM_GaaFunctionId[LddHigh]))
  {
    /* @Trace: FiM_SUD_API_063 */
    do
    {
      /* Get the middle index number */
      LddMiddle = (LddHigh + LddLow) >> FIM_ONE;

      /* Get the Fid of the middle */
      LddCurrFid = FiM_GaaFunctionId[LddMiddle];

      /* Compare the current Fid with the requested one */
      if (LddCurrFid == LddFid)
      {
        /* Update the identified Fid Index number in out variable */
        /* @Trace: FiM_SUD_API_064 */
        *LddFidArrayIndex = LddMiddle;
        /* Update the return variable to true */
        LblReturn = FIM_TRUE;
        /* Set LddHigh to zero & LddLow = one to break the loop */
        LddHigh = FIM_ZERO;
        LddLow = FIM_ONE;
      }
      else
      {
        /* @Trace: FiM_SUD_API_069 */
        /* Check if the requested Fid smaller than the current Fid */
        if (LddFid < LddCurrFid)
        {
          /* @Trace: FiM_SUD_API_065 */
          /* The requested Fid is smaller than current, update LddHigh */
          LddHigh = LddMiddle - FIM_ONE;
        }
        else
        {
          /* @Trace: FiM_SUD_API_066 */
          /* The requested Fid is greater than current, update LddLow */
          LddLow = LddMiddle + FIM_ONE;
        }
      } /* end if(LddCurrFid == LddFid) */
    }
    while (LddLow <= LddHigh);
  }
  else
  {
    /* No require action */
  }
  /* @Trace: FiM_SUD_API_067 */
  return(LblReturn);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : FiM_FidLinearSearch                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaFunctionId for a requested Fid.              **
**                        This service is used only in case if the FIDs are   **
**                        not sequential.                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddFid                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LddFidArrayIndex                                    **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaFunctionId                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if (FIM_FIDS_SEQUENTIAL == STD_OFF)
#if (FIM_EN_FID_BINARYSEARCH == STD_OFF)
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_FidLinearSearch(FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR)LddFidArrayIndex)
{
  boolean LblSearchResult;
  FiM_FidsSizeType LddIndex;
  /* @Trace: FiM_SUD_API_070 */
  /* Set the search result flag to FIM_FALSE */
  LblSearchResult = FIM_FALSE;

  #if (FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO)
  /* Check for LddFid by linear search */
  for (LddIndex = FIM_ZERO; LddIndex < FIM_TOTAL_NUM_OF_FIDS; LddIndex++)
  {
    /* @Trace: FiM_SUD_API_071 */
    /* Is FiD matches with requested FiD */
    if (FiM_GaaFunctionId[LddIndex] == LddFid)
    {
      /* @Trace: FiM_SUD_API_072 */
      /* Update index for Request Array Index */
      *LddFidArrayIndex = LddIndex;
      /* Set search result flag to TRUE */
      LblSearchResult = FIM_TRUE;
      break;
    }
    else
    {
      /* No require action */
    }
  }
  #else
  UNUSED(LddFid);
  UNUSED(LddFidArrayIndex);
  #endif
  /* Return FIM_TRUE if found else FIM_FALSE */
  /* @Trace: FiM_SUD_API_073 */
  return (LblSearchResult);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_EN_FID_BINARYSEARCH == STD_OFF */
#endif /* FIM_FIDS_SEQUENTIAL == STD_OFF */

/*******************************************************************************
** Function Name        : FiM_ComponentIdLinearSearch                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaFunctionId for a requested Fid.              **
**                        This service is used only in case if the FIDs are   **
**                        not sequential.                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddComponentId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpComponentIndex                                    **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaFunctionId, FiM_GaaComponentInfo             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
#if (FIM_EN_COMPONENTID_BINARYSEARCH == STD_OFF)
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_ComponentIdLinearSearch(
  Dem_ComponentIdType LddComponentId,
  P2VAR(uint16, AUTOMATIC, FIM_VAR)LpComponentIndex)
{
  boolean LblSearchResult;
  /* variable to break the FOR loop */
  FiM_ComponentSizeType LddIndex;
  /* @Trace: FiM_SUD_API_074 */
  /* Set the search result flag to FIM_FALSE */
  LblSearchResult = FIM_FALSE;
  /* Check for LddIndex by linear search */
  for (LddIndex = FIM_ZERO; LddIndex < FIM_TOTAL_NUM_OF_DEM_COMPONENT;
      LddIndex++)
  {
    /* Is ComponentId matches with requested ComponentId */
    /* @Trace: FiM_SUD_API_075 */
    if (FiM_GaaComponentInfo[LddIndex].ddComponentId == LddComponentId)
    {
      /* @Trace: FiM_SUD_API_076 */
      /* Update index for Request Array Index */
      *LpComponentIndex = LddIndex;
      /* Set search result flag to TRUE */
      LblSearchResult = FIM_TRUE;
      break;
    }
    else
    {
      /* No require action */
    }
  }
  /* Return FIM_TRUE if found else FIM_FALSE */
  /* @Trace: FiM_SUD_API_077 */
  return (LblSearchResult);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* FIM_EN_COMPONENTID_BINARYSEARCH == STD_OFF */
#endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO */

/*******************************************************************************
** Function Name        : FiM_ComponentIdBinarySearch                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service identifies array index of              **
**                        FiM_GaaComponentInfo for a requested Fid.           **
**                                                                            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddComponentId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LddFidArrayIndex                                    **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaFunctionId, FiM_GaaComponentInfo             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if ((FIM_EN_COMPONENTID_BINARYSEARCH == STD_ON) && \
    (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO))
#define FIM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, FIM_CODE) FiM_ComponentIdBinarySearch(
  Dem_ComponentIdType LddComponentId,
  P2VAR(uint16, AUTOMATIC, FIM_VAR)LpComponentIndex)
{
  /* @Trace: FiM_SUD_API_078 */
  FiM_FunctionIdType LddCurrComponentId;
  FiM_ComponentSizeType LddHigh;
  FiM_ComponentSizeType LddLow;
  FiM_ComponentSizeType LddMiddle;
  boolean LblReturn;
  LblReturn = FIM_FALSE;
  /* Initialize LddHigh variable with number of FIDs */
  LddHigh = FIM_TOTAL_NUM_OF_DEM_COMPONENT - FIM_ONE;
  /* Initialize LddLow variable with one */
  LddLow = (FiM_ComponentSizeType)FIM_ZERO;
  /* Check whether search DemComponent id is in range */
  if ((LddComponentId >= FiM_GaaComponentInfo[FIM_ZERO].ddComponentId) &&
      (LddComponentId <= FiM_GaaComponentInfo[LddHigh].ddComponentId))
  {
    /* @Trace: FiM_SUD_API_079 */
    do
    {
      /* Get the middle index number */
      /* @Trace: FiM_SUD_API_080 */
      LddMiddle = (LddHigh + LddLow) >> FIM_ONE;

      /* Get DemComponent id of the middle */
      LddCurrComponentId = FiM_GaaComponentInfo[LddMiddle].ddComponentId;
      /* Compare the current DemComponent id with the requested one */
      if (LddCurrComponentId == LddComponentId)
      {
        /* @Trace: FiM_SUD_API_081 */
        /* Update the DemComponent id in out variable */
        *LpComponentIndex = LddMiddle;
        /* Update the return variable to true */
        LblReturn = FIM_TRUE;
        /* Set LddHigh to zero & LddLow = one to break the loop */
        LddHigh = FIM_ZERO;
        LddLow = FIM_ONE;
      }
      else
      {
        /* Check if the requested  smaller than the current Fid */
        if (LddComponentId < LddCurrComponentId)
        {
          /* The requested DemComponent id is smaller than current,
           * update LddHigh */
          /* @Trace: FiM_SUD_API_082 */
          LddHigh = LddMiddle - FIM_ONE;
        }
        else
        {
          /* The requested DemComponent id is greater than current,
           * update LddLow */
          /* @Trace: FiM_SUD_API_108 */
          LddLow = LddMiddle + FIM_ONE;
        }
      } /* end if (LddCurrComponentId == LddComponentId) */
    }
    while (LddLow <= LddHigh);
  }
  else
  {
    LblReturn = FIM_FALSE;
  }
  /* @Trace: FiM_SUD_API_083 */
  return (LblReturn);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* (FIM_EN_COMPONENTID_BINARYSEARCH == STD_ON) && \
   (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
*/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
