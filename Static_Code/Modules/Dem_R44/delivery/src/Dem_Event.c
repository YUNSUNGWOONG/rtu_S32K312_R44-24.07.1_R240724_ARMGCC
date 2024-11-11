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
**  SRC-MODULE: Dem_Event.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of management of diagnostic event                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*
 * @IF_REQ List
 *
 * 1. Dem_GetTestResultThisOperation shall be optimized
 *   (status & mask) == target status
 *
 * 2.  if (event->aaEventDestination == DTCOrigin) =>
 *     if ((MemoryId & DTCOrigin) ==   DTCOrigin)
 *     
 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_EventMemory.h"
#include "Dem_Event.h"
#include "Dem_Indicator.h"
#include "Dem_EventCallback.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventAging.h"
#include "Dem_EventRelatedData.h"
#include "Dem_Component.h"
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* @static uint32 TimeForTest(uint32 cnt); */



#define DEM_START_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
static FUNC(void, DEM_CODE) Dem_GetListOfEventStorageConditionFulfilled(
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus);
#endif   

/******************************************************************************
 * Function Name        : Dem_DTCOriginBelongToEvent
 *
 * Service ID           : None
 *
 * Description          : Checks whether the DTCOrigin of an event correspond 
 *                        to the input DTCOrigin.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : boolean
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *
 *****************************************************************************/
/* @Trace: Dem_SUD_MACRO_013 */
FUNC(boolean, DEM_CODE) Dem_DTCOriginBelongToEvent(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin)
{
  boolean LblBelongToEvent = DEM_FALSE;
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  if (
      (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
      || (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      || (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
      #endif
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
      || (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
      #endif
     )
  {
    /* @Trace: Dem_SUD_API_20651 */
    #if (DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20652 */
    if ((LddEvent->aaEventDestination == DTCOrigin)
       #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
        || ((DEM_TWO == LddEvent->ucNumOfDestSelected ) &&
            (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin))
       #endif
       )
    {
      /* @Trace: Dem_SUD_API_20650 */
      LblBelongToEvent = DEM_TRUE;
    }
    #endif
  }
  /* @Trace: Dem_SUD_API_20658 */
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  /* @Trace: Dem_SUD_API_20656 */
  else if (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY == DTCOrigin)
  {
    /* When Event belong to Event Memory Set of OBD
     * And Event is an OBD Event*/
    Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
    /* @Trace: Dem_SUD_API_20655 */
    if (NULL_PTR != LddCbDTC)
    {
      /* @Trace: Dem_SUD_API_20654 */
      if ((DEM_OBD_EVENT_MEMORY_SET_IDX == LddEvent->ucEventMemDstIdx)
          && ((LddCbDTC->usObdDtc != DEM_NO_DTC) 
          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          || (LddCbDTC->ulObdDtc3Byte != DEM_NO_DTC)
          #endif
          ))  
      {
        /* @Trace: Dem_SUD_API_20653 */
        LblBelongToEvent = DEM_TRUE;
      }
    }
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_20657 */
    /* Nothing to do */
  }

  return LblBelongToEvent;
}


/******************************************************************************
 * Function Name        : Dem_GetEventConditionsAndControlDTCSetting
 *
 * Service ID           : None
 *
 * Description          : Checks whether event condions and control DTC setting
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : 
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 ******************************************************************************/
/* @Trace: SRS_Diag_04115 SRS_Diag_04164
 */
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetEventConditionsAndControlDTCSetting(Dem_EventIdType EventId)
{
  /*
   * pointer to a event should be verified by the caller
   */
  Std_ReturnType LddRetVal = E_OK;
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

  /* @Trace: Dem_SUD_API_20663 */
  #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
  /* @Trace: Dem_SUD_API_20664 */
  if (DEM_ZERO != LddEvent->ucNumOfEnableCondition)
  {
    uint16 LusIdx = DEM_ZERO;
    const uint16 LusNumOfCond = LddEvent->PointToEnableConditionMap +
        LddEvent->ucNumOfEnableCondition;

    /* Check the status of all enable conditions configured for the event */
    /* @Trace: Dem_SUD_API_20665 */
    if (LusNumOfCond <= DEM_MAX_LISTOFENABLECONDITIONID)
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates
     * to true or false according to configuration */
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      /* @Trace: Dem_SUD_API_20667 */
      for (LusIdx = LddEvent->PointToEnableConditionMap;
           LusIdx < LusNumOfCond ;
           LusIdx++)
      {
        /* @Trace: Dem_SUD_API_20666 */
        if ((boolean)DEM_FALSE == Dem_GetEnableConditionStatus(LusIdx))
        {
          /* @Trace: Dem_SUD_API_20659 */
          LddRetVal = E_NOT_OK;
          break;
        }
      }
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }
  /* @Trace: Dem_SUD_API_20668 */
  if (E_OK == LddRetVal)
  #endif
  {
    if (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
    {
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition
       * always evaluates to true. */
      /* @Trace: Dem_SUD_API_20670 */
      #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
      P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
            &Dem_GaaCombinedDtc[LddEvent->e_PointToDTC];
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
      /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
      if (LddCbDTC->ddDtcGroup < Dem_Max_Num_Grp_DTC)
      {
        /*@Dem_DTCKindType kind = LddCbDTC->ddDtcKind;*/

        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* Check DTC Disable DTC Setting of AllDTC or
         * Check DTC Disable DTC Setting of Particular Group */

        /* @Trace: SWS_Dem_00626
         * When DTC setting is disabled, all status reports from the API
         * Dem_SetEventStatus for those events being assigned to this specific
         * DTC group shall be ignored (no change of UDS status byte) by the Dem.
         * */
        /* @Trace: Dem_SUD_API_20015 */
        if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
        {
          /* @Trace: Dem_SUD_API_20662 */
          if (((boolean)DEM_TRUE == Dem_GaaDisableDtcSettingMemSet[
                         LddEvent->ucEventMemDstIdx]))
          {
            /* @Trace: Dem_SUD_API_20661 */
            LddRetVal = E_NOT_OK;
          }
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      else
      /* @Trace: Dem_SUD_API_20660 */
      #endif
      {
        /* Det Error */
        LddRetVal = E_NOT_OK;
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
    }
    else
    {
      /* @Trace: Dem_SUD_API_20669 */
      /* @Trace: Dem_SUD_API_20014 */
      /* If event does not has a DTC, condition will be E_OK */
      /* LddRetVal = E_OK;*/
    }
  }
  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_MainfunctionBswEvents                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Processes Bsw events                                **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_BSW_00339
 */
#if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
FUNC(void, DEM_CODE) Dem_MainfunctionBswEvents(void)
{
  Dem_EventIdType LddEventId;
  Dem_EventStatusType LddEventStatus;

  /* @IF_REQ: 10 events? */
  /* No preempted by Dcm_MainFuntion, so no need
   * 'SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION' */
  /* @Trace: Dem_SUD_API_20672 */
  if ((boolean)DEM_FALSE == Dem_EvMem_Lock())
  {

    /* @Trace: SWS_Dem_00167
     * The Dem module shall provide a buffer mechanism to queue events which
     * are reported before Dem_Init via Dem_SetEventStatus as qualified as
     * Passed or Failed or reaching the qualification (debouncing). Reporting
     * of DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED shall not be queued.
     */
    /* Load the BSW buffer to appropriate event memory */
    /* @Trace: Dem_SUD_API_20673 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_BSW_ERROR_BUFFER_SIZE; LucIdx++)
    {
      /* Check for valid event id */
      SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
      LddEventId = Dem_GaaErrorBuffer[LucIdx];

      if ((boolean)DEM_TRUE == Dem_EventIdIsValid(LddEventId))
      {
        if (DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEventId))
        {
          /* @Trace: Dem_SUD_API_20674 */
          LddEventStatus = Dem_GaaErrorBufferStatus[LucIdx];
          Dem_GaaErrorBuffer[LucIdx] = DEM_NO_EVENT;
          Dem_GaaErrorBufferStatus[LucIdx] = DEM_ZERO;
          SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();

          (void) Dem_ProcessEventStatus(LddEventId, LddEventStatus);
        }
        else
        {
          /* @Trace: Dem_SUD_API_20016 */
          SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_20671 */
        SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
      }
    }
    /*
     Initialize the buffer ReadIdx to zero
     after processing all the events
     */
    SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
    Dem_GucErrorWriteIndex = DEM_ZERO;
    SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
  }
}

/*******************************************************************************
 ** Function Name       : Dem_InitBswEventQueue                               **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Init BSW Event queue                                **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_InitBswEventQueue(void)
{
  /* @Trace: Dem_SUD_API_20675 */
  #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
  /* No need 'critical section' because this function is called by
   * Dem_PreInit() */
  uint8 LucIdx; /* DemBswErrorBufferSize MAX : 255 */
  /* @Trace: Dem_SUD_API_20676 */
  for (LucIdx = DEM_ZERO; LucIdx < DEM_BSW_ERROR_BUFFER_SIZE; LucIdx++)
  {
    /* @Trace: Dem_SUD_API_20677 */
    Dem_GaaErrorBuffer[LucIdx] = DEM_NO_EVENT;
    Dem_GaaErrorBufferStatus[LucIdx] = DEM_ZERO;
  }
  Dem_GucErrorWriteIndex = DEM_ZERO;
  #endif
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_MainfunctionEvents                              **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Processes event and stored event related data       **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_Diag_04141
 */
FUNC(void, DEM_CODE) Dem_MainfunctionEvents(void)
{

  /* @IF_REQ: 10 events? */
  /* No preempted by Dcm_MainFuntion, so no need
   * 'SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION' */
  /* @Trace: Dem_SUD_API_20678 */
  if ((boolean)DEM_FALSE == Dem_EvMem_Lock())
  {
    /* @Trace: Dem_SUD_API_20683 */
    #if ((DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO) && \
         (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO))
    /* @Trace: SWS_Dem_01172
     * The storage/reporting of freeze frame information associated with a
     * Class A malfunction shall take precedence over a Class B1 malfunction
     * which shall take precedence over a Class B2 malfunction and likewise for
     * information associated with a Class C malfunction.
     */
    /* @Trace: SWS_Dem_01173
     * The first malfunction detected shall take precedence over the most
     * recent malfunction unless the most recent malfunction is of a
     * higher class.
     */
    /* @Trace: Dem_SUD_API_20684 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_20685 */
    Dem_SortedEventsByWWHOBDTCClass();
    #endif

    Dem_EventIdType LddEventId;
    /* @Trace: Dem_SUD_API_20686 */
    for ( uint8 LucIdx = DEM_ZERO;
          LucIdx < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER; LucIdx++)
    {
     /* Check for valid event id */
     SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
     LddEventId = Dem_GaaEventEDCBuffer[LucIdx];
     if ((LddEventId <= DEM_NUMBER_OF_EVENTS) && (LddEventId != DEM_NO_EVENT))
     {
       Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
       Dem_GaaEventEDCBuffer[LucIdx] = DEM_NO_EVENT;
       SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();

       Dem_NumOfEventMemoryEntryType LddMemLoc =
                Dem_EvMemToEventMap[LddEventId];
       Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
       Dem_NumOfEventMemoryEntryType LddStartIdx =
              Dem_EvMem_GetStartIndexEventMemorySet(LddEventId,
                 LddEvent->aaEventDestination);
       Dem_NumOfEventMemoryEntryType LddStopIdx =
              Dem_EvMem_GetStopIndexEventMemorySet(LddEventId,
                  LddEvent->aaEventDestination);
       /* Already stored */
       /* @Trace: Dem_SUD_API_20689 */
       if ((LddStartIdx <= LddMemLoc) && (LddMemLoc < LddStopIdx))
       {
         /* Duplicated code for performance and runtime check(polyspace) */
         if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddEvent->aaEventDestination)
         {
           /* @Trace: Dem_SUD_API_20688 */
           LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
         }
         /* @Trace: Dem_SUD_API_20679 */
         #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
         else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(
             LddEvent->aaEventDestination))
         {
           /* @Trace: Dem_SUD_API_20690 */
           LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
         }
         #endif
         else
         {
           /* @Trace: Dem_SUD_API_20680 */
           /* Do nothing */
         }
       }
       /* @Trace: Dem_SUD_API_20682 */
       if (NULL_PTR != LddMemEntry)
       {
         (void)Dem_ProcessCaptureDataRelated(
             LddEventId,
             Dem_GaaEventEDCBufferStatus[LucIdx],
             DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING);
         /* @Trace: Dem_SUD_API_20681 */
         Dem_GaaEventEDCBufferStatus[LucIdx] = DEM_ZERO;
       }
     }
     else
     {
       /* @Trace: Dem_SUD_API_20687 */
       SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
     }
     /*
      Initialize the buffer ReadIdx to zero
      after processing all the events
      */
      SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
      Dem_GucReportIndex = DEM_ZERO;
      SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
    }
    #endif
  }
}

/*******************************************************************************
 ** Function Name       : Dem_InitEventQueue                                  **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Init Event queue                                    **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_InitEventQueue(void)
{
  /* @Trace: Dem_SUD_API_20692 */
  #if (DEM_NUMBER_OF_EVENTS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20693 */
  for (uint16 LusIdx = DEM_ONE; LusIdx <= DEM_NUMBER_OF_EVENTS; LusIdx++)
  {
    /* @Trace: SWS_Dem_01331
     * If the data capturing was triggered from within an API call
     * without monitorData, the Dem shall use a value of 0 as monitorData.
     */
    /* @Trace: Dem_SUD_API_20691 */
    Dem_MonitorData[LusIdx].usMonitorData0 = DEM_ZERO;
    Dem_MonitorData[LusIdx].usMonitorData1 = DEM_ZERO;
  }
  #endif

  /* Init queue store the environment data */
  /* @Trace: Dem_SUD_API_20695 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20696 */
  for ( uint8 LucIdx = DEM_ZERO;
        LucIdx < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER;
        LucIdx++)
  {
    /* @Trace: Dem_SUD_API_20694 */
    Dem_GaaEventEDCBuffer[LucIdx] = DEM_NO_EVENT;
    Dem_GaaEventEDCBufferStatus[LucIdx] = DEM_ZERO;
  }
  Dem_GucReportIndex = DEM_ZERO;
  #endif
}

/******************************************************************************
 * Function Name        : Dem_GetIndexOfMasterEventByEventId
 *
 * Service ID           : None
 *
 * Description          : Check valid of master event and get it's position
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DemMultiEventTrg
 *                        Function(s) invoked :
 ******************************************************************************/
#if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
FUNC(uint8, DEM_CODE) Dem_GetIndexOfMasterEventByEventId
    (Dem_EventIdType EventId)
{
  uint8 LucIdx = DEM_MAX_DEM_MULTI_EVENT_TRIGGERING;
  /* If EventId invalid, no need check master event id */
  /* @Trace: Dem_SUD_API_20697 */
  if (DEM_TRUE == Dem_EventIdIsValid(EventId))
  {
    /* @Trace: Dem_SUD_API_20698 */
    for ( uint8 LucId = DEM_ZERO;
          LucId< DEM_MAX_DEM_MULTI_EVENT_TRIGGERING;
          LucId++)
    {
      /* @Trace: Dem_SUD_API_20699 */
      if (EventId == Dem_DemMultiEventTrg[LucId].masterEventIdx)
      {
        /* @Trace: Dem_SUD_API_20700 */
        LucIdx = LucId;
        break;
      }
    }
  }
  return LucIdx;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_ProcessEventStatus 
 **
 ** Service ID          : None
 **
 ** Description         : It is used to process the event status.
 **
 ** Sync/Async          : Synchronous/Asynchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : EventId
 **                       EventStatus
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : Std_ReturnType
 **                       E_NOT_OK : set of event status failed or could not be
 **                                  accepted
 **                                  [1] the operation cycle configured for this
 **                                  event has not been started
 **                                  [2] enable condition for this event has
 **                                  been disabled
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
 /* @Trace: SRS_Diag_04067 SRS_Diag_04068 SRS_Diag_04073 SRS_Diag_04074
            SRS_Diag_04093 SRS_Diag_04125 SRS_Diag_04127 SRS_Diag_04131
            SRS_Diag_04142 SRS_Diag_04192 SRS_Diag_04219
  */
/* @Trace: Dem_SUD_MACRO_079 */
/* polyspace +1 CODE-METRICS:VG CODE-METRICS:CALLS CODE-METRICS:FXLN CODE-METRICS:PATH[Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_ProcessEventStatus(
    Dem_EventIdType EventId,
    Dem_EventStatusType EvStatus)
{
  Std_ReturnType LddRetVal = E_OK;
  Dem_EventStatusType LddEventStatus = EvStatus;
  /***************************************************************************
   *           General diagnostic event storage processing                   *
   *           [ Refer to Figure 7.25 ]                                      *
   ***************************************************************************/
  
  /* polyspace<RTE:UNR:Not a defect:No action planned> Avoid to runtime error
   * of the polyspace */
  if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {  
    /* @Trace: Dem_SUD_API_20017 */
    LddRetVal = E_NOT_OK;
  }
  /***************************************************************************
   *           Check validity of operation cycle & enable conditions         *
   **************************************************************************/
  /* @Trace: SWS_Dem_00449
   * If one enable condition is not fulfilled, all of Dem_SetEventStatus calls
   * for those events being assigned to this condition shall be ignored (no
   * change of event status byte) by the Dem.
   */

  /* @Trace: SWS_Dem_00450
   * If all event-specific enable conditions are fulfilled, all status reports
   * from SW-Cs and BSW modules via Dem_SetEventStatus for those events being
   * assigned to these conditions shall be accepted by the Dem from this point
   * in time on.
   */
  else if (E_NOT_OK == Dem_GetEventConditionsAndControlDTCSetting(EventId))
  {
    /* @Trace: Dem_SUD_API_20701 */
    /* @Trace: SWS_Dem_00655
     * If the configuration parameter DemDebounceBehavior is set
     * to DEM_DEBOUNCE_STATUS_FREEZE, the Dem module shall freeze the internal
     * debounce timer when at least one enable condition for the related event
     * is set to not fulfilled.
     * */

    /* @Trace: SWS_Dem_00678
     * If the configuration parameter DemDebounceBehavior is set
     * to DEM_DEBOUNCE_STATUS_FREEZE, the Dem module shall freeze the internal
     * debounce timer when ControlDTCSetting is set to disabled for the
     * related event.
     * */

    /* @Trace: SWS_Dem_00654
     * If the configuration parameter DemDebounceBehavior is set to
     * DEM_DEBOUNCE_RESET and the function Dem_SetEnableCondition (refer to
     * chapter 7.7.6) sets one configured enable condition for the event to not
     * fulfilled, it shall reset the related fault detection counter(s).
     * */

    /* @Trace: SWS_Dem_00677
     * If the configuration parameter DemDebounceBehavior is set
     * to DEM_DEBOUNCE_RESET, the function Dem_DisableDTCSetting (refer to
     * chapter 7.11.2.6) shall reset the related fault detection counter(s).
     * */
    /* @Trace: Dem_SUD_API_20756 */
    /* @Trace: Dem_SUD_MACRO_005 */
    #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
    Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) LddCfgTimer =
        NULL_PTR;
    Dem_NumOfDebounceType LddDebounceId = LddEvent->ucIndexOfDebounceAry;
    uint8 LucDebounceType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
        LddEvent->ParamFieldsA);

    LddCfgTimer = Dem_GetCfgDebounceTimer(LddDebounceId);
    /* @Trace: Dem_SUD_API_20723 */
    if (( NULL_PTR != LddCfgTimer) &&
        ( DEM_DEBOUNCE_TIME_BASED == LucDebounceType))
    {
      /* @Trace: Dem_SUD_API_20734 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      if (DEM_DEBOUNCE_RESET == LddCfgTimer->eDemDebounceBehavior)
      {
        /* @Trace: Dem_SUD_API_20745 */
        Dem_ResetFaultDectectionCounter(EventId);
        /* @LddRetVal = E_NOT_OK; */
      }
    }
    #endif
    LddRetVal = E_NOT_OK;
  } 
  else if ((boolean)DEM_FALSE == Dem_GetLocksByEventIdAndEvMem(EventId))
  { 
    /* @Trace: Dem_SUD_API_20712 */
    /* @Trace: Dem_SUD_API_20018 */
    LddRetVal = E_NOT_OK;
  }  
  else 
  {
    /* @Trace: Dem_SUD_API_20767 */
    Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    uint8 LucDebounceType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
        LddEvent->ParamFieldsA);
    Dem_NumOfEventMemoryEntryType LddMemLocOld = Dem_EvMemToEventMap[EventId];
    Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);


    /*************************************************************************
     *                 Process event debouncing                              *
     *************************************************************************/
    /* @Trace: Dem_SUD_API_20778 */
    if ((DEM_DEBOUNCE_NO_DEBOUNCE_BASED != LucDebounceType) &&
        (DEM_DEBOUNCE_COUNTER_BASED != LucDebounceType))
    {
      /* @Trace: Dem_SUD_API_20789 */
      /* @Trace: Dem_SUD_MACRO_086 */
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO)
      if (DEM_DEBOUNCE_MONITOR_BASED == LucDebounceType)
      {
        if (((DEM_EVENT_STATUS_PASSED != LddEventStatus) &&
             (DEM_EVENT_STATUS_FAILED != LddEventStatus)) &&
             (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED != LddEventStatus))
        {
          /* @Trace: SWS_Dem_00437
           * Note: The monitor is not allowed to report the event states
           * DEM_EVENT_STATUS_PREFAILED and DEM_EVENT_STATUS_PREPASSED for
           * monitor internal debouncing. */
          /* LddEventStatus = DEM_EVENT_STATUS_UNDEFINED; */
          /* @Trace: Dem_SUD_API_20707 */
          LddRetVal = E_NOT_OK;
        }
        /* @Trace: Dem_SUD_API_20704 */
        else if (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED == LddEventStatus)
        {
          /* @Trace: Dem_SUD_API_20703 */
          /* @Trace: Dem_SUD_API_20705 */
          #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
          /* @Trace: SWS_Dem_01210
           * If the Dem module is requested to support storage conditions,
           * the Dem module shall check the assigned storage conditions after
           * the event reports DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
           * (e.g. either via interface call or when reaching the configured
           * threshold in debounce algorithm).
           */
          /* @Trace: Dem_SUD_API_20706 */
          if (E_OK != Dem_GetEventStorageConditionState(EventId))
          {
            /* @Trace: Dem_SUD_API_20708 */
            /* LddEventStatus = DEM_EVENT_STATUS_UNDEFINED; */
            LddRetVal = E_NOT_OK;
          }
          #endif
        }
      }
      else
       /* @Trace: Dem_SUD_API_20702 */
      #endif
       /* @Trace: Dem_SUD_API_20709 */
      #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
      if (DEM_DEBOUNCE_TIME_BASED == LucDebounceType)
      {
        /* @Trace: SWS_Dem_00685
         * If the API Dem_ResetEventDebounceStatus is called with
         * DEM_DEBOUNCE_STATUS_FREEZE, it shall freeze the related internal
         * debounce timer.
         * */

        /* @Trace: SWS_Dem_00656
         * If an internal debounce timer is frozen and a new (valid)
         * (debouncing-)result is reported for this event (as per
         * [SWS_Dem_00428] / [SWS_Dem_00432]), the Dem module shall continue
         * running the internal debounce timer (from current value).
         * */
        /* @Trace: Dem_SUD_API_20711 */
        if (DEM_TRUE != Dem_EnableFreeze[EventId - DEM_ONE])
        {
          /* @Trace: Dem_SUD_API_20713 */
          if (DEM_FALSE == Dem_ProcessDebounceTimeBased(
              LddEvent->ucIndexOfDebounceAry, &LddEventStatus))
          {
            /* @Trace: Dem_SUD_API_20714 */
            /* LddEventStatus = DEM_EVENT_STATUS_UNDEFINED; */
            LddRetVal = E_NOT_OK;
          }
        }
      }
      else
      /* @Trace: Dem_SUD_API_20710 */
      #endif
      {
        /* @LddEventStatus = DEM_EVENT_STATUS_UNDEFINED; */
        LddRetVal = E_NOT_OK;
      }
    }

    /* @Trace: SWS_Dem_00791
     * The maximum FDC during current operation cycle shall be update
     * if the current fault detection counter value is greater than the
     * current value of the maximum FDC during current operation cycle.
     * */

    /* @Trace: SWS_Dem_00795
     * The maximum FDC since last clear shall be update if the current
     * fault detection counter value is greater than the current value of
     * the maximum FDC since last clear.
     * */
     /* @Trace: Dem_SUD_API_20715 */
     /* @Trace: Dem_SUD_MACRO_074 */
     #if (DEM_MAX_NUMBER_OF_DTC > DEM_ZERO)
     /* @Trace: Dem_SUD_API_20716 */
     #if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO) || \
          (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON) || \
         (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO))
     sint8 LscHighestFdc = 0;
     /* @Trace: Dem_SUD_API_20717 */
     if ((E_OK == Dem_GetHighestMaximumFDC(EventId, &LscHighestFdc)) &&
         (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC))
     {
       /* @Trace: Dem_SUD_API_20718 */
       #if (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
       /* @Trace: Dem_SUD_API_20719 */
       if ( LscHighestFdc >
            Dem_InternalDataMaxFdc[LddEvent->e_PointToDTC].maxFdcCurrentCycle)
       {
        /* @Trace: Dem_SUD_API_20720 */
         Dem_InternalDataMaxFdc[LddEvent->e_PointToDTC].maxFdcCurrentCycle =
              LscHighestFdc;
       }
       #endif
       /* @Trace: Dem_SUD_API_20721 */
       #if (DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
       /* @Trace: Dem_SUD_API_20722 */
       if ( LscHighestFdc >
            Dem_InternalDataMaxFdc[LddEvent->e_PointToDTC].maxFdcLastClear)
       {
         /* @Trace: Dem_SUD_API_20724 */
         Dem_InternalDataMaxFdc[LddEvent->e_PointToDTC].maxFdcLastClear =
              LscHighestFdc;
       }
       #endif
     }
     #endif
     #endif
    /* @Trace: Dem_SUD_API_20725 */
    /* @Trace: Dem_SUD_MACRO_156 */
    #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20019 */
    Dem_CheckConsecutiveFault(EventId, LddEventStatus);
    #endif

    /* qualified as PASSED */
    if (
        (DEM_EVENT_STATUS_PASSED == LddEventStatus) &&
        /* Not Tested */
        ((DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC)) ||
        /* Failed To Passed */
        (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)))
        /* @IF_REQ : if TF was cleared by API ResetEventStatus? */
       )
    {
      boolean LblStatusDirty = DEM_FALSE;
      const Dem_DTCOriginType LddDTCOrigin =
          LddEvent->aaEventDestination;

      /* (1) Clears TestFailed bit to 0 */

      /* @Trace: SWS_Dem_01064
       * The mirror memory is not relevant for calculation of the UDS status. */
      /* @Trace: Dem_SUD_API_20020 */
      if (DEM_DTC_ORIGIN_MIRROR_MEMORY != LddDTCOrigin)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* @Trace: SWS_Dem_00386, @SWS_Dem_00392, @SWS_Dem_00394
         * The Dem module shall implement the status bit transitions for
         * UDS status bit 0, 4, 6 according to figure 7.17, 7.21, 7.23.
         */
        /* @Trace: Dem_SUD_API_20726 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF))
        {
          /* @Trace: Dem_SUD_API_20728 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_0);
        }
        /* @Trace: Dem_SUD_API_20727 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC))
        {
          /* @Trace: Dem_SUD_API_20729 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_6);
        }
        /* @Trace: Dem_SUD_API_20730 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCSLC))
        {
          /* @Trace: Dem_SUD_API_20731 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_4);
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      /* @Trace: Dem_SUD_API_20732 */
      if ((DEM_NO_DTC_ORIGIN != LddDTCOrigin) &&
          (DEM_DTC_ORIGIN_MIRROR_MEMORY != LddDTCOrigin) &&
          (NULL_PTR != LddCbDTC))
      {
        /* @Trace: Dem_SUD_API_20733 */
        boolean LblEventIsAged = DEM_FALSE;
        /*
         * (2) Clears WarningIndicatorRequest bit 7 to 0 immediately when
         * healing threshold is 0
         *
         * [1] @RfC 63657,Always the operation cycle of indicator is
         * DemOperationCycleRef
         * [2] Indicator is supported
         * [3] A specific event's WarningIndicatorRequest bit = 1 
         * [4] Only indicator is set when event has a DTC

         * WarningIndicatorRequestOffCondition : Counter:N/A
         * Dem_DeActivateIndicatorOnEventPassed shall be called regardless
         * DEM_UDS_STATUS_WIR
         * because Failure Counter shall be initialized */
        LblStatusDirty = Dem_DeActivateIndicatorOnEventPassed(EventId);

        /* if event is stored */
        Dem_NumOfEventMemoryEntryType LddSizeOfMem =
            Dem_EvMem_GetSizeOfElementEventMemory(EventId, LddDTCOrigin);
        Dem_NumOfEventMemoryEntryType LddStartIndex =
            Dem_EvMem_GetStartIndexEventMemorySet(EventId, LddDTCOrigin);
        LddSizeOfMem = LddSizeOfMem + LddStartIndex;
        /* @Trace: Dem_SUD_API_20735 */
        if (LddMemLocOld < LddSizeOfMem)
        {
          /* @Trace: Dem_SUD_API_20736 */
          /* (3) Delete Event immediately when aging threshold is 0 */
          LblEventIsAged = Dem_EventAgingOnEventPassed(EventId, LddDTCOrigin,
              LddMemLocOld);
        }
        /*
         * (4) Clears prestored freeze frame buffer when EventStatus changes
         * from passed to failed
         */

        /* @Trace: SWS_Dem_00465
         * If an event gets qualified as passed(UDS DTC status bit 0 changes
         * from 1 to 0) the Dem module shall release the pre-stored freeze
         * frame for the specific event.
         */
        /* @Trace: Dem_SUD_API_20737 */
        #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
        const Dem_UdsStatusByteType LddEventStatusByteOld =
            Dem_AllEventStatusByte[EventId];
        /* @Trace: Dem_SUD_API_20738 */
        if (DEM_ZERO != (LddEventStatusByteOld & (Dem_UdsStatusByteType)
             DEM_UDS_STATUS_TF))
        {
          /* @Trace: Dem_SUD_API_20739 */
          (void)Dem_ClearSinglePrestoredFFbyEventId(EventId);
        }
        #endif
        /* @Trace: Dem_SUD_API_20740 */
        if ((boolean)DEM_FALSE == LblEventIsAged)
        {
          Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_TRIGGER_NV_DATA_STORAGE);
          /* @Trace: Dem_SUD_API_20741 */
          if (DEM_TRUE == LblStatusDirty)
          {
            /* @Trace: Dem_SUD_API_20742 */
            Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EV_STATUS_IS_DIRTY);
          }
        }
      }
      /* @Trace: SWS_Dem_00710
       * The numerator shall be calculated in the ECU (Master and Primary).*/
      /* @Trace: Dem_SUD_API_20743 */
      #if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
          ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || \
          (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU)))
      /* @Trace: Dem_SUD_API_20744 */
      (void)Dem_ProcessNum(EventId, Dem_AllEventStatusByte[EventId]);
      #endif
      /* Dem Component processing */
      /* @Trace: Dem_SUD_API_20746 */
      #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
      /* @Trace: Dem_SUD_API_20747 */
      Dem_ComponentProcessing(EventId);
      #endif
    }
    /* qualified as FAILED
     * @Dem184: Store an event which is qualified as failed(UDS DTC status bit
     * 0 changes from 0 to 1) @RfC 61309, PassedToFailed problem */
    /* @Trace: SWS_Dem_00455
     * If the Dem module is requested to support storage conditions, the Dem
     * module shall check the assigned storage conditions after the event gets
     * qualified as failed (UDS status bit 0 changes from 0 to 1).
     */
    else if ((DEM_EVENT_STATUS_FAILED == LddEventStatus) &&
            /* Tested at first */
            ((DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC)) ||
            /* Passed to Failed */
            (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)) ||
            /* Not stored */
            ((NULL_PTR != LddCbDTC) && (DEM_NO_EVMEM_ENTRY == LddMemLocOld))))
    {
      /* @Trace: Dem_SUD_API_20732 */
      boolean LblStatusDirty = DEM_FALSE;
      /* @Trace: Dem_SUD_API_20748 */
      #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
      /* @Trace: Dem_SUD_API_20749 */
      const Dem_UdsStatusByteType LddDTCStatusByteOld =
          Dem_GetDTCStatus(EventId);
      #endif
      const Dem_UdsStatusByteType LddEventStatusByteOld =
          Dem_AllEventStatusByte[EventId];
      const Dem_DTCOriginType LddDTCOrigin = LddEvent->aaEventDestination;
    
      /*********************************************************************
       *                     TestFailed bit = 1,                           *
       *                     TestFailedThisOpCycle = 1,                    *
       *                     (TestFailedSinceLastClear = 1)*               *
       *                     TestNotCompleteThisOpCycle = 0;               *
       *                     TestNotCompleteSinceLastClear = 0             *
       *********************************************************************/
      /* @Trace: SWS_Dem_01064
       * The mirror memory is not relevant for calculation of the UDS status. */
      /* @Trace: Dem_SUD_API_20022 */
      if (DEM_DTC_ORIGIN_MIRROR_MEMORY != LddDTCOrigin)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* @Trace: SWS_Dem_00386, SWS_Dem_00389, SWS_Dem_00392, SWS_Dem_00393,
         * SWS_Dem_00394 The Dem module shall implement the status bit
         * transitions for UDS status bit 0, 1, 4, 5, 6
         * according to figure 7.17, 7.18, 7.21, 7.22, 7.23 */
        /* @Trace: Dem_SUD_API_20750 */
        if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF))
        {
          /* @Trace: Dem_SUD_API_20751 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_0);
        }
        /* @Trace: Dem_SUD_API_20752 */
        if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFTOC))
        {
          /* @Trace: Dem_SUD_API_20753 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_1);
        }
        /* @Trace: Dem_SUD_API_20754 */
        if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFSLC))
        {
          /* @Trace: Dem_SUD_API_20755 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
        }
        /* @Trace: Dem_SUD_API_20757 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCSLC))
        {
          /* @Trace: Dem_SUD_API_20758 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_4);
        }
        /* @Trace: Dem_SUD_API_20759 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC))
        {
          /* @Trace: Dem_SUD_API_20760 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_6);
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }

      /* @RfC 60025 : no memory entry for events without having a DTC */
      /* @Trace: Dem_SUD_API_20761 */
      if ((DEM_NO_DTC_ORIGIN != LddDTCOrigin) &&
          (DEM_DTC_ORIGIN_MIRROR_MEMORY != LddDTCOrigin) &&
          (NULL_PTR != LddCbDTC))
      {  
        boolean LblEventDirty = DEM_FALSE;
        /* @Trace: Dem_SUD_API_20762 */
        #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
        /* @Trace: Dem_SUD_API_20763 */
        Dem_DTCType LddDTC = Dem_GetDtcByCombineDTC(LddCbDTC);
        #endif

        /* Dem Component processing */
        /* @Trace: Dem_SUD_API_20764 */
        #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
        /* @Trace: Dem_SUD_API_20765 */
        Dem_ComponentProcessing(EventId);
        #endif
        /* @Trace: Dem_SUD_API_20766 */
        #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
        /* @Trace: Dem_SUD_API_20768 */
        Std_ReturnType EvStorageConditionState =
            Dem_GetEventStorageConditionState(EventId);
        #endif
        /* @Trace: SWS_Dem_01130
         * A failure which is considered as consecutive fault shall not be
         * stored to the failure memory. (The handling shall be analogous to
         * storage condition not fulfilled).
         * */
        /* @Trace: Dem_SUD_API_20769 */
        #if (DEM_NUMBER_OF_EVENTS > DEM_ZERO )
        /* @Trace: Dem_SUD_API_20770 */
        if ((DEM_CONSECUTIVE_FAULT != Dem_EvtDepdntStt[EventId - DEM_ONE])
        /* Check validity of storage conditions */
        /* @Trace: SWS_Dem_00458
         * If one storage condition is not fulfilled and no respective event
         * memory entry exists, the Dem module shall not enter the reported
         * event into the event memory.
         */
        /* @Trace: SWS_Dem_00459
         * If all event-specific storage conditions are fulfilled, the Dem
         * module shall permit the storage of the reported event.
         */
        /* @Trace: SWS_Dem_00591
         * If one storage condition is not fulfilled and a respective
         * event memory entry exists, the Dem module shall not update the
         * event memory of the reported event.
         */
        /* @Trace: Dem_SUD_API_20771 */
        #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
        /* @IF_REQ : disabled condition returns E_OK or E_NOT_OK? */
        /* @Trace: SWS_Dem_01309
         * If at least one storage condition assigned to an event is not
         * fulfilled, the Dem shall skip the calculation of the bits:
         * - bit 2 (PendingDTC) and
         * - bit 3 (ConfirmedDTC).
         * in the corresponding event status byte and UDS status byte.
         */
        && (E_OK == EvStorageConditionState)
        /* @Trace: Dem_SUD_API_20772 */
        #endif
        )
        #endif
        {
          /* @Trace: SWS_Dem_00390
           * The Dem module shall implement the status bit transition for
           * UDS status bit 2 according to figure 7.19. */
          /* @Trace: Dem_SUD_API_20773 */
          if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_PDTC))
          {
            /* @Trace: Dem_SUD_API_20774 */
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_2);
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          /* @Trace: SWS_Dem_00163
           * If the Dem module is requested to support combination on storage,
           * the DTC status bit transitions of the combined DTC (refer
           * [SWS_Dem_00441]) shall be used as trigger source for the
           * allocation of the event memory entry, as well as the collection or
           * update of its related data (freeze frames or extended
           * data records).
           */
          Std_ReturnType LddResult = Dem_EvMem_ProcessEventRetention(
              EventId,
              LddDTCOrigin,
              LddEventStatusByteOld,
              #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
              LddDTCStatusByteOld,
              #endif
              #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
              LddDTC,
              #endif
              &LblEventDirty,
              &LblStatusDirty);
          /* @Trace: Dem_SUD_API_20775 */
          #if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
              ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || \
              (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU)))
          /* @Trace: Dem_SUD_API_20776 */
          (void)Dem_ProcessNum(EventId, Dem_AllEventStatusByte[EventId]);
          #endif
          
          if (DEM_PROCESSEVENTRETENTION_OK == LddResult)
          {
            /* @Trace: Dem_SUD_API_20779 */
            #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
            uint8 LucCliendIdx = Dem_EvMem_GetClientIDFromEventMemorySet(
                LddEvent->ucEventMemDstIdx);
            /* @Trace: Dem_SUD_API_20025 */
            if (DEM_NO_IDX_U8 != LucCliendIdx)
            {
              /* @Trace: Dem_SUD_API_20780 */
              LblStatusDirty |= Dem_EvMem_SetFirstLastFailedDtc(LucCliendIdx,
                  LddDTCOrigin, LddDTC);
            }
            /* @LddRetVal = E_OK; */
            #endif
          }
          else if (DEM_PROCESSEVENTRETENTION_FULL == LddResult)
          {
            /* @Trace: Dem_SUD_API_20777 */
            /* @Trace: SWS_Dem_00397
             * The Dem module shall indicate for each event memory if
             * the event memory is full and there was an attempt to store
             * an additional event in this event  memory.
             */
            /* @Trace: Dem_SUD_API_20786 */
            if ((boolean) DEM_TRUE == Dem_EvMem_SetEvMemOverflowFlag(
                    LddEvent->ucEventMemDstIdx,
                    LddDTCOrigin, DEM_TRUE ))
            {
              /* @Trace: Dem_SUD_API_20787 */
              /* @IF_REQ : Need it? */
              Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
                  DEM_EVMEM_STATUS_DIRTY_NVM);
              Dem_EvMem_TriggerWriteAllBlocks();
            }
            /* @IF_REQ: Returns E_OK as per AUTOSAR Specification,but E_NOT_OK
             * is used as return value by user requirement */
            LddRetVal = E_NOT_OK;
          }
          else /* @(DEM_PROCESSEVENTRETENTION_FAILED == LddResult) */
          {
            /* @Trace: Dem_SUD_API_20024 */
            /* Never be reached */
            LddRetVal = E_NOT_OK;
          }
        }/* @else { LddRetVal = E_OK } */

        Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_TRIGGER_NV_DATA_STORAGE);
        /* @Trace: Dem_SUD_API_20781 */
        if (DEM_TRUE == LblEventDirty)
        {
          /* @Trace: Dem_SUD_API_20782 */
          Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EV_MEM_ENTRY_IS_DIRTY);
        }
        /* @Trace: Dem_SUD_API_20783 */
        if (DEM_TRUE == LblStatusDirty)
        {
          /* @Trace: Dem_SUD_API_20784 */
          Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EV_STATUS_IS_DIRTY);
        }

        /* Need to save if Operation Cycle was not Stored due to optimization*/
        /* @Trace: Dem_SUD_API_20785 */
        if ((boolean)DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(
            DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
            DEM_EVMEM_STATUS_TRIGGER_WAIT_NVM))
        {
          /* @Trace: Dem_SUD_API_20023 */
          Dem_EvMem_ClearNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
              DEM_EVMEM_STATUS_TRIGGER_WAIT_NVM);

          Dem_EvMem_SetNonVolatieDataStatus(
          DEM_NVDATA_GENERIC_NVRAM_DATA_ID, (DEM_EVMEM_STATUS_DIRTY |
              DEM_EVMEM_STATUS_TRIGGER_NVM));

          Dem_EvMem_TriggerWriteAllBlocks();
        }
      }
    }    
    else
    {
      /* @Trace: Dem_SUD_API_20021 */
      /* Do Nothing */
    }
    /* @Trace: Dem_SUD_API_20788 */
    #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
    /* @Trace: SWS_Dem_00461
     * If the configuration parameter DemEnvironmentDataCapture is set to
     * DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING
     * (refer to DemPrimaryMemory or DemUserDefinedMemory), event-specific
     * freeze frame data shall be captured
     * latest in the next cycle of the Dem_MainFunction.
     */
    /* @Trace: SWS_Dem_01081
     * If the configuration parameter DemEnvironmentDataCapture is set to
     * DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING
     * (refer to DemPrimaryMemory or DemUserDefinedMemory), event-specific
     * extended data shall be captured latest in the next cycle
     * of the Dem_MainFunction.
     */
    /* @Trace: Dem_SUD_API_20790 */
    if (DEM_NO_EVMEM_IDX != Dem_Event[EventId - DEM_ONE].ucEventMemDstIdx)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
          Dem_Event[EventId - DEM_ONE].aaEventDestination)
      {
        /* @Trace: Dem_SUD_API_20792 */
        #if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
        /* @Trace: Dem_SUD_API_20793 */
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        if (DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING ==
            Dem_GaaDemPrimaryMemory[Dem_Event[EventId - DEM_ONE].
              ucEventMemDstIdx].usDemEnvironmentDataCapture)
        {
          /* @Trace: Dem_SUD_API_20794 */
          (void)Dem_ProcessCaptureDataRelated(
              EventId,
              LddEventStatus,
              DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING);
        }
        #endif
      }
      else if ( DEM_DTCORGIN_USER_DEFINED_IS_VALID(
                  Dem_Event[EventId - DEM_ONE].aaEventDestination))
      {
        /* @Trace: Dem_SUD_API_20791 */
        /* @Trace: Dem_SUD_API_20796 */
        #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
        /* @Trace: Dem_SUD_API_20797 */
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        if ( DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING ==
               Dem_GaaDemUserDefinedMemory[
                 Dem_Event[EventId - DEM_ONE].ucEventMemDstIdx].
                 usDemEnvironmentDataCapture)
        {
          /* @Trace: Dem_SUD_API_20798 */
          (void)Dem_ProcessCaptureDataRelated(
              EventId,
              LddEventStatus,
              DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING);
        }
        #endif
      }
      else
      {
        /* @Trace: Dem_SUD_API_20795 */
        /* Nothing to do */
      }
    }
    #endif
    Dem_FreeLockByEventId(EventId);
  }
  return LddRetVal;
}
      
/******************************************************************************
 * Function Name        : Dem_GetEventIdByDTC
 *
 * Service ID           : None
 *
 * Description          : Gets the EventId by a DTC
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ApiId, DTC, DTCFormat
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_EventIdType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        None
 ******************************************************************************/
/* @Trace: SRS_Diag_04000
 */
/* @Trace: Dem_SUD_MACRO_081 */
/* polyspace +1 CODE-METRICS:CALLING [Not a defect:Low] "Not a defect" */
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetEventIdByDTC(
  uint8 ApiId,
  const Dem_DTCType DTC,
  const Dem_DTCFormatType DTCFormat)
{
  uint16 LusDtcId;
  Dem_EventIdType LddEventId = DEM_NO_EVENT;
  Dem_DTCType LddTmpDTC = DTC;

  if ( DEM_DTC_FORMAT_OBD == DTCFormat )
  {
    /* @Trace: Dem_SUD_API_20802 */
    LddTmpDTC = DTC >> DEM_EIGHT;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20803 */
    /* Do nothing*/
  }

  if ((DEM_MAX_DTC_VALUE < LddTmpDTC )
      #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
      || (DEM_DTC_GROUP_IS_VALID(LddTmpDTC))
      #endif
     )
  {
    DEM_REPORT_ERROR(ApiId, DEM_E_PARAM_DATA);
    /* @Trace: Dem_SUD_API_20805 */
    #if (DEM_DEV_ERROR_DETECT != STD_ON)
    /* @Trace: Dem_SUD_API_20804 */
    DEM_UNUSED(ApiId);
    #endif
  }
  else
  {
    /* @Trace: Dem_SUD_API_20027 */
    /* @Trace: Dem_SUD_API_20801 */
    for (LusDtcId = DEM_ZERO; LusDtcId < DEM_MAX_NUMBER_OF_DTC; LusDtcId++)
    {
      Dem_DTCType LddDtcValue;
      /* @Trace: Dem_SUD_API_20808 */
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      if (DEM_DTC_FORMAT_UDS != Dem_GaaCombinedDtc[LusDtcId].ddDtcFormat)
      {
        #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
        /* Trace: DEM_19792_42_04 */
        if (DEM_DTC_FORMAT_OBD_3BYTE == Dem_GaaCombinedDtc[LusDtcId].ddDtcFormat)
        {
          /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
          /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
          /* DemSupportedobdUdsDtcSeparation is need to supported */           
          if (Dem_ObdUdsDtc_Separation_Support == STD_ON)
          {
        	  LddDtcValue = Dem_GaaCombinedDtc[LusDtcId].ulObdDtc3Byte;
          }
          else
          {
            LddDtcValue = Dem_GaaCombinedDtc[LusDtcId].ulUdsDtc;
          }
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
        }
        else
        #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */
        {
          /* @Trace: Dem_SUD_API_20806 */
          LddDtcValue = Dem_GaaCombinedDtc[LusDtcId].usObdDtc ;
          /* @IF_REQ: Dem_GaaCombinedDtc[i].usObdDtc << 8 */
        }
      }
      else
      /* @Trace: Dem_SUD_API_20807 */
      #endif /*(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)*/
      {
        LddDtcValue = Dem_GaaCombinedDtc[LusDtcId].ulUdsDtc;
      }
      /* @Trace: Dem_SUD_API_20809 */
      if (LddDtcValue == LddTmpDTC)
      {
        /* @Trace: Dem_SUD_API_20800 */
        LddEventId = Dem_GetFirstEventOfDTC(&Dem_GaaCombinedDtc[LusDtcId]);
        break;
      }
    }
  }
  /* @Trace: Dem_SUD_API_20026 */
  return LddEventId;
}

/******************************************************************************
 * Function Name        : Dem_GetEventDTC
 *
 * Service ID           : None
 *
 * Description          : Gets the DTC value of an event
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, DTCFormat
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DTC
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        None
 ******************************************************************************/
/* @Trace: SRS_Diag_04010
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventDTC(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC, Dem_DTCFormatType DTCFormat)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  *DTC  = DEM_NO_DTC;  
  /* no need to check 'if (DEM_NO_DTC_IDX != event->e_PointToDTC)' */
  /* @Trace: Dem_SUD_API_20813 */
  if (event->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
  {

    switch(DTCFormat)
    {
      /* @Trace: Dem_SUD_API_20814 */
      case DEM_DTC_FORMAT_UDS:
        /* @Trace: Dem_SUD_API_20810 */
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].ulUdsDtc;
      break;
      /* @Trace: SWS_Dem_00277
       * The Dem shall report DTC values as a uint32 with byte 0 = LowByte,
       * byte 1 = MiddleByte, byte 2 = HighByte and byte 3 is unused. For
       * OBD DTC format there are only two bytes (HighByte, LowByte) used. The
       * Dem services shall report these DTCs as a uint32 with byte 1 = LowByte,
       * byte 2 = HighByte, byte 3 is unused and byte 0 = 0x00.
       */
      /* @Trace: Dem_SUD_API_20815 */
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      /* @Trace: Dem_SUD_API_20816 */
      case DEM_DTC_FORMAT_OBD:
        /* @Trace: Dem_SUD_API_20817 */
        *DTC = (uint32)(Dem_GaaCombinedDtc[event->e_PointToDTC].usObdDtc) << 8U;
      break;

      #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
      /* Trace: DEM_19792_42_04 */
      case DEM_DTC_FORMAT_OBD_3BYTE:
        /* DemSupportedobdUdsDtcSeparation is need to supported */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
        if (Dem_ObdUdsDtc_Separation_Support == STD_ON)
        {
          *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].ulObdDtc3Byte;
        }
        else
        {
          *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].ulUdsDtc;
        }
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
      break;
      #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

      #endif
      /* @Trace: Dem_SUD_API_20818 */
      #if (DEM_J1939_SUPPORT == STD_ON) 
      /* @Trace: Dem_SUD_API_20819 */
      case DEM_DTC_FORMAT_J1939:
        /* @Trace: Dem_SUD_API_20820 */
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].J1939DTCValue << 8U;
      break;
      #endif
      default:
        /* @Trace: Dem_SUD_API_20028 */
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].ulUdsDtc;
      break;
      
    }
  }
  /* @Trace: Dem_SUD_API_20812 */
  if (DEM_NO_DTC != *DTC)
  {
    /* @Trace: Dem_SUD_API_20811 */
    LddRetVal = E_OK;
  }
  
  return  LddRetVal;
}


/******************************************************************************
 * Function Name        : Dem_GetEventDTCOrigin
 *
 * Service ID           : None
 *
 * Description          : This function is used to get the main origin
 *                        of an event.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DTCOrigin
 *
 * Return parameter     : StdReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *
 ******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventDTCOrigin(
    Dem_EventParameterCPCType event,
    P2VAR(Dem_DTCOriginType, AUTOMATIC, DEM_VAR) DTCOrigin)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ( (NULL_PTR == DTCOrigin) || (NULL_PTR == event) )
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition
   * always evaluates to false. Avoid to runtime error of the polyspace */
  {
    /* @Trace: Dem_SUD_API_20029 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);  
  }
  else
  {
    /* @Trace: Dem_SUD_API_20821 */
     /* @Trace: Dem_SUD_API_20823 */
    if ((event->aaEventDestination == DEM_DTC_ORIGIN_PRIMARY_MEMORY) ||
      (DEM_DTCORGIN_USER_DEFINED_IS_VALID(event->aaEventDestination)))
    {
      /* @Trace: Dem_SUD_API_20822 */
      *DTCOrigin = event->aaEventDestination;
      LddRetVal = E_OK;
    }
  }

  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_GetEventEnableConditionState
 *
 * Service ID           : None
 *
 * Description          : Checks whether enable condions are true or not
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 ******************************************************************************/
#if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventEnableConditionState(
    Dem_EventIdType EventId)
{
  Std_ReturnType LddRetVal = E_OK;
  /* @Trace: Dem_SUD_API_20824 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    uint16 LusIdx = DEM_ZERO;
    Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    const uint16 LusNumOfCond = LddEvent->PointToEnableConditionMap +
        LddEvent->ucNumOfEnableCondition;
    /* @Trace: Dem_SUD_API_20825 */
    if (LusNumOfCond <= DEM_MAX_LISTOFENABLECONDITIONID)
    {
      /* Check the status of all enable conditions configured for the event by
       * SW-C*/
      /* @Trace: Dem_SUD_API_20826 */
      for ( LusIdx = LddEvent->PointToEnableConditionMap;
            LusIdx < LusNumOfCond ;
            LusIdx++)
      {
        /* enable storage == all condition is true */
        /* @Trace: SWS_Dem_00447 */
        /* @Trace: Dem_SUD_API_20827 */
        if ((boolean)DEM_FALSE == Dem_GetEnableConditionStatus(LusIdx))
        {
          /* @Trace: Dem_SUD_API_20828 */
          LddRetVal = E_NOT_OK;
          break;
        }
      }
    }
  }

  return LddRetVal;
}
#endif

/******************************************************************************
 * Function Name        : Dem_GetEventStorageConditionState
 *
 * Service ID           : None
 *
 * Description          : Get the storage condions state
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : 
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 ******************************************************************************/
/* @Trace: SRS_Diag_04137 SRS_Diag_04219
 */
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStorageConditionState(
    Dem_EventIdType EventId)
{
  Std_ReturnType LddRetVal = E_OK;
  uint16 LusIdx = DEM_ZERO;
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  const uint16 LusNumOfCond =
      LddEvent->PointToStorageConditionMap + LddEvent->ucNumOfStorageCondition;
  /* @Trace: Dem_SUD_API_20829 */
  if (LusNumOfCond <= DEM_MAX_LISTOFSTORAGECONDITIONID)
  {
    /* Check the status of all enable conditions configured for the
     * event by SW-C*/
    /* @Trace: Dem_SUD_API_20830 */
    for ( LusIdx = LddEvent->PointToStorageConditionMap;
          LusIdx < LusNumOfCond ;
          LusIdx++)
    {
      /* enable storage == all condition is true */
      /* @Trace: Dem_SUD_API_20832 */
      if ((boolean)DEM_FALSE == Dem_GetStorageConditionStatus(LusIdx))
      {
        /* @Trace: Dem_SUD_API_20831 */
        LddRetVal = E_NOT_OK;
        break;
      }
    }
  }
  /* @Trace: SWS_Dem_01086
   * When a storage condition is deactivated, the replacement event shall be
   * set (status FAILED) as soon as a failure is reported and filtered by the
   * storage condition (storage condition not fulfilled). Note: As long as the
   * storage condition is not fulfilled and no event assigned to the storage
   * condition reports FAILED, the replacement event shall not be set.
   */
  /* @Trace: SWS_Dem_01088
   * The status/behavior of the filtered event (filtered by the
   * storagecondition) is not affected by the replacement event (meaning:
   * the failure which is filtered by the storage condition
   * behaves identical in case of having a replacement event or in case of NOT
   * having a replacement event configured for the storage condition).
   */
  if (E_OK == LddRetVal)
  {
    /* @Trace: Dem_SUD_API_20834 */
    if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(EventId,
         DEM_EVPROCSTATE_STORAGE_CONDITION))
    {
     /* @Trace: SWS_Dem_01089
      * The replacement event is reset (status PASSED), when the storage
      * condition is fulfilled (on enabling the storage condition).
      */
      /* @Trace: Dem_SUD_API_20835 */
      Dem_GetListOfEventStorageConditionFulfilled(EventId,
          DEM_EVENT_STATUS_PASSED);
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_20833 */
    Dem_GetListOfEventStorageConditionFulfilled(EventId,
        DEM_EVENT_STATUS_FAILED);
  }
  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_GetListOfEventStorageConditionFulfilled
 *
 * Service ID           : None
 *
 * Description          : Get event storage condition fulfilled list
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, EventStatus
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  : Dem_Event
 *                        Function(s) invoked :
 ******************************************************************************/
/* @Trace: SRS_Diag_04137 SRS_Diag_04219
 */
static FUNC(void, DEM_CODE) Dem_GetListOfEventStorageConditionFulfilled(
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus)
{
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  uint16 LusIdx = DEM_ZERO;
  const uint16 LusNumOfCond = LddEvent->PointToStorageConditionMap +
      LddEvent->ucNumOfStorageCondition;
  /* @Trace: Dem_SUD_API_20836 */
  if (LusNumOfCond <= DEM_MAX_LISTOFSTORAGECONDITIONID)
  {
    /* @Trace: Dem_SUD_API_20840 */
    for ( LusIdx = LddEvent->PointToStorageConditionMap;
          LusIdx < LusNumOfCond ;
          LusIdx++)
    {
      /* Check all storage condition status */
      /* @Trace: Dem_SUD_API_20841 */
      if ((boolean)DEM_FALSE ==
           Dem_GaaStorageCondition[LusIdx].blDemStrCondStt)
      {
        /* @Trace: SWS_Dem_01090
         * constraints for the replacement event:
         * + must not be mapped to an storage condition
         * + must not be configured to use debouncing
         * + must not have an InitMForE callback/ clearEventAllowed
         * + must not be configured for enableConditions
         * + must be configured as DEM_EVENT_KIND_BSW
         */

        /* @Trace: SWS_Dem_01085
         * For each storage condition a replacement event may be defined (see
         * DemStorageConditionReplacementEventRef).
         * This replacement event will be used as a replacement failure info.
         */

        /* @Trace: SWS_Dem_01087
         * The replacement error has an EventStatus (Dem_UdsStatusByteType) as
         * every other event.
         */
        /* @Trace: Dem_SUD_API_20842 */
        /* @Trace: Dem_SUD_MACRO_089 */
        #if ((DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO) && \
             (DEM_MAX_LISTOFSTORAGECONDITIONID > DEM_ZERO))
        /* @Trace: Dem_SUD_API_20843 */
        if ( DEM_NO_EVENT_INDEX !=
             Dem_GaaStorageCondition[
               Dem_ListOfStorageConditionId[LusIdx]].ucDemEventIdx)
        {
          /* @Trace: Dem_SUD_API_20844 */
          #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
          SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * If-condition always evaluates to true */
          /* @Trace: Dem_SUD_API_20845 */
          if (Dem_GucErrorWriteIndex < DEM_BSW_ERROR_BUFFER_SIZE)
          {
            /* Check if the error buffer is empty */
            /* @Trace: Dem_SUD_API_20846 */
            if (DEM_NO_EVENT == Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex])
            {
              /* Load the event into the buffer */
              Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex] =
                  Dem_GaaStorageCondition[
                  Dem_ListOfStorageConditionId[LusIdx]].ucDemEventIdx;
              Dem_GaaErrorBufferStatus[Dem_GucErrorWriteIndex] = EventStatus;

              /* Check if the buffer is full */
              Dem_GucErrorWriteIndex++;
              /* @Trace: Dem_SUD_API_20837 */
              if (Dem_GucErrorWriteIndex >= DEM_BSW_ERROR_BUFFER_SIZE)
              {
                /* @Trace: Dem_SUD_API_20847 */
                /* Initialize the buffer to zero */
                Dem_GucErrorWriteIndex = DEM_ZERO;
              }
            }
          }
          SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
          #endif
        }
        #endif
      }
    }
  }
  if (DEM_EVENT_STATUS_FAILED == EventStatus)
  {
    /* @Trace: Dem_SUD_API_20838 */
    Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_STORAGE_CONDITION);
  }
  else
  {
    /* @Trace: Dem_SUD_API_20839 */
    Dem_EvClearProcState(EventId, DEM_EVPROCSTATE_STORAGE_CONDITION);
  }
}
#endif


/******************************************************************************
 * Function Name        : Dem_GetOpCycleStateByEvent
 *
 * Service ID           : None
 *
 * Description          : Gets operation cycle state by event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : CycleState
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        Dem_EvMem_GetOpCycleState()
 *****************************************************************************/
/* @Trace: Dem_SUD_MACRO_097 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetOpCycleStateByEvent(
  Dem_EventIdType EventId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition
   * always evaluates to false. Avoid to runtime error of the polyspace */
  if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_20030 */
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }  
  else if (NULL_PTR == CycleState)
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition
   * always evaluates to false. Avoid to runtime error of the polyspace */
  /* @Trace: Dem_SUD_API_20848 */
  {
  /* @Trace: Dem_SUD_API_20849 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
  }
  else 
  {
    /* @Trace: Dem_SUD_API_20850 */
    /* @IF_REQ : e_OperationCycleId ==
     * Dem_GaaOperationCycleIdsList[0].ucOperationCycleId */
    /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition
     * always evaluates to true. Avoid to runtime error of the polyspace */
    /* @Trace: Dem_SUD_API_20031 */
    if (Dem_Event[EventId - DEM_ONE].e_OperationCycleId <
        Dem_Num_Operation_Cycles)
    {
      /* @Trace: Dem_SUD_API_20851 */
      *CycleState = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_NOTSTART;
      Dem_EvMem_GetOpCycleState(Dem_Event[EventId - DEM_ONE].e_OperationCycleId,
          CycleState);
      LddRetVal = E_OK;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
 * Function Name        : Dem_GetTestResultThisOperation
 *
 * Service ID           : None
 *
 * Description          : Get a test result after event is processed
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventStatusByte, RequireTestedCycle
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_TestResultType
 *                        DEM_TEST_RESULT_PASSED_THIS_OPERATION
 *                        DEM_TEST_RESULT_FAILED_THIS_OPERATION
 *                        DEM_TEST_RESULT_PASSED_FIRST
 *                        DEM_TEST_RESULT_FAILED_FIRST
 *                        DEM_TEST_RESULT_NO_RESULT : Test not completed
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
/* @Trace: SRS_Diag_04133 SRS_Diag_04178
 */
FUNC(Dem_TestResultType, DEM_CODE) Dem_GetTestResultThisOperation( 
  Dem_UdsStatusByteType EventStatusByte, 
  boolean RequireTestedCycle)
{
  Dem_TestResultType LddOpTestResult = DEM_TEST_RESULT_NO_RESULT;

  if ((boolean)DEM_TRUE == RequireTestedCycle)
  {
    /* @Trace: SWS_Dem_00826
     * If the configuration parameter DemAgingRequieresTestedCycle
     * (refer DemGeneral) set to True, the Dem module shall process
     * (count further) the aging cycle counter value, if the respective
     * aging cycle ends/restarts and the UDS status bit
     * 6 (TestNotCompleteThisOperationCycle) is set to zero. */
    if ((EventStatusByte & (Dem_UdsStatusByteType) DEM_UDS_STATUS_TNCTOC) ==
          DEM_ZERO)
    {      
      if ((EventStatusByte & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC) !=
          DEM_ZERO)
      {
        /* @Trace: Dem_SUD_API_20852 */
        LddOpTestResult = DEM_TEST_RESULT_FAILED_THIS_OPERATION;
      }      
      else
      {
        /* @Trace: Dem_SUD_API_20853 */
        LddOpTestResult = DEM_TEST_RESULT_PASSED_THIS_OPERATION;
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_20854 */
      LddOpTestResult = DEM_TEST_RESULT_NO_RESULT;
    }
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates
   * to true or false according to configuration */
  /* @Trace: Dem_SUD_API_20855 */
  {

    /* @testFailedThisOperationCycle==1 */  
    if ((EventStatusByte & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC) !=
          DEM_ZERO)
    {
      /* @Trace: Dem_SUD_API_20856 */
      LddOpTestResult = DEM_TEST_RESULT_FAILED_THIS_OPERATION;
    } 
    /* @Trace: SWS_Dem_00490
     * If the configuration parameter DemAgingRequieresTestedCycle
     * (refer to DemGeneral) set to False, the Dem module shall process
     * (count further) the aging counter value, if the respective aging cycle
     * ends/restarts.
     * Note: The aging counter in [SWS_Dem_00490] is processed also if no
     * new test result is available in the respective aging cycle. */
    else
    {
      /* @Trace: Dem_SUD_API_20857 */
      LddOpTestResult = DEM_TEST_RESULT_PASSED_THIS_OPERATION;
    }
  }

  return LddOpTestResult;
}

/*******************************************************************************
 ** Function Name       : Dem_ProcessUDSStatus
 **
 ** Service ID          : None
 **
 ** Description         : It is used to process the UDS status.
 **
 ** Sync/Async          : Asynchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : None
 **
 ** Preconditions       : None
 **
 ** Remarks             :
 *******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04066 SRS_Diag_04067 SRS_Diag_04073
           SRS_Diag_04077
 */
/* polyspace +1 CODE-METRICS:FXLN CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_ProcessUDSStatus(void)
{
  /* @Trace: Dem_SUD_API_20871 */
  for (Dem_EventIdType LddEventId = DEM_ONE;
                       LddEventId <= DEM_NUMBER_OF_EVENTS;
                       LddEventId++)
  {
    const Dem_UdsStatusByteType LddDTCStatusByteOld =
        Dem_GetDTCStatus(LddEventId);
    const Dem_UdsStatusByteType LddEventStatusByteOld =
        Dem_AllEventStatusByte[LddEventId];
    /* @Trace: Dem_SUD_API_20882 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered( LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_0))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TF))
      {
       /* @Trace: Dem_SUD_API_20893 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF);
      }
      else
      {
       /* @Trace: Dem_SUD_API_20899 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_0);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20900 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_1))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TFTOC))
      {
        /* @Trace: Dem_SUD_API_20902 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20901 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_1);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20903 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_2))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_PDTC))
      {
        /* @Trace: Dem_SUD_API_20904 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20872 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_2);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20873 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_3))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_CDTC))
      {
        /* @Trace: Dem_SUD_API_20875 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20874 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC);
      }

      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20876 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_4))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TNCSLC))
      {
        /* @Trace: Dem_SUD_API_20878 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC);
      }
      else
      {
       /* @Trace: Dem_SUD_API_20877 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_4);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20879 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_5))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TFSLC))
      {
        /* @Trace: Dem_SUD_API_20881 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20880 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20883 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_6))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TNCTOC))
      {
        /* @Trace: Dem_SUD_API_20885 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCTOC);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20884 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCTOC);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_6);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: Dem_SUD_API_20886 */
    if (DEM_TRUE == Dem_EvIsUdsProcStateTriggered(LddEventId,
          DEM_UDSPROCSTATE_TRANSITION_BIT_7))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_WIR))
      {
        /* @Trace: Dem_SUD_API_20888 */
        DEM_SET_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_WIR);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20887 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_WIR);
      }
      Dem_EvClearUdsProcState(LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_7);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
    /* @Trace: SWS_Dem_01050
     * Each time the status of an event is updated, the combined DTC status
     * shall be calculated. If the combined DTC status has changed the relevant
     * callbacks shall be invoked; refer to [SWS_Dem_00284], [SWS_Dem_00986],
     * [SWS_Dem_00987] and [SWS_Dem_00828].
     */

    /* @Trace: SWS_Dem_00016
     * The Dem module shall trigger the event-specific callbackfunction
     * EventUdsStatusChanged on each UDS status change.
     */

    /* @Trace: SWS_Dem_00828
     * If the status of a DTC changes, the Dem shall call the configured
     * DemCallbackDTCStatusChanged function
     */
    /* @Trace: Dem_SUD_API_20889 */
    if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEventId])
    {
      Dem_TriggerCallbackOnUdsStatus(
          LddEventId, LddEventStatusByteOld, LddDTCStatusByteOld);
    }

    /* @Trace: SWS_Dem_00551
     * If immediate nonvolatile storage is enabled for a specific DTC,
     * the Dem module shall trigger the storage for new event memory
     * entries and after every change of the event related data (event
     * memory entry was updated).
     */
    /* @Trace: Dem_SUD_API_20890 */
    if (DEM_TRUE == Dem_EvIsProcStateTriggered(LddEventId,
          DEM_EVPROCSTATE_TRIGGER_NV_DATA_STORAGE))
    {
      Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];

      Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEventId);

      const Dem_DTCOriginType LddDTCOrigin =
                LddEvent->aaEventDestination;
      /* @Trace: Dem_SUD_API_20891 */
      if (NULL_PTR != LddCbDTC)
      {
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        uint8 LucTriggerNvStorage =
          (DEM_EVMEM_STATUS_DIRTY_NVM == LddCbDTC->EvMemTriggerFlag) ?
          /* @Trace: Dem_SUD_API_20894 */
          Dem_EvMem_EventIsImmediateStorage(LddDTCOrigin, LddEventId) :
          /* @Trace: Dem_SUD_API_20892 */
          DEM_EVMEM_STATUS_DIRTY;
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        boolean LblEventDirty = Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_EV_MEM_ENTRY_IS_DIRTY);

        boolean LblStatusDirty = Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_EV_STATUS_IS_DIRTY);
        /* @Trace: Dem_SUD_API_20895 */
        if (DEM_EVMEM_STATUS_DIRTY_NVM == Dem_EvMem_TriggerNvDataStorage(
            LddEventId, LddDTCOrigin, LddEventStatusByteOld,
             LucTriggerNvStorage, LblEventDirty, LblStatusDirty))
        {
          Dem_EvMem_TriggerWriteAllBlocks();
        }
        Dem_EvClearProcState(
            LddEventId, DEM_EVPROCSTATE_TRIGGER_NV_DATA_STORAGE);
        /* @Trace: Dem_SUD_API_20896 */
        if (DEM_TRUE == LblEventDirty)
        {
          Dem_EvClearProcState(
              LddEventId, DEM_EVPROCSTATE_EV_MEM_ENTRY_IS_DIRTY);
        }
        /* @Trace: Dem_SUD_API_20897 */
        if (DEM_TRUE == LblStatusDirty)
        {
          /* @Trace: Dem_SUD_API_20898 */
          Dem_EvClearProcState(
              LddEventId, DEM_EVPROCSTATE_EV_STATUS_IS_DIRTY);
        }
      }
    }
  }
}

/*******************************************************************************
 ** Function Name       : Dem_ProcessWIRStatus
 **
 ** Service ID          : None
 **
 ** Description         : It is used to process the WIR status.
 **
 ** Sync/Async          : Asynchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : None
 **
 ** Preconditions       : None
 **
 ** Remarks             :
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_ProcessWIRStatus(void)
{
  /* @Trace: Dem_SUD_API_20858 */
  for ( Dem_EventIdType LddEventId = DEM_ONE;
        LddEventId <= DEM_NUMBER_OF_EVENTS;
        LddEventId++)
  {
    const Dem_UdsStatusByteType LddDTCStatusByteOld =
        Dem_GetDTCStatus(LddEventId);
    const Dem_UdsStatusByteType LddEventStatusByteOld =
        Dem_AllEventStatusByte[LddEventId];
    /* @Trace: Dem_SUD_API_20859 */
    if (DEM_TRUE == Dem_EvIsProcStateTriggered(
           LddEventId, DEM_EVPROCSTATE_IS_SET_WIR_STATUS))
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (DEM_TRUE == Dem_EvIsProcStateTriggered( LddEventId,
          DEM_EVPROCSTATE_WIR_STATUS))
      {
       /* @Trace: Dem_SUD_API_20861 */
        DEM_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_WIR);
      }
      else
      {
        /* @Trace: Dem_SUD_API_20860 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_WIR);
        (void)Dem_InitIndicator(LddEventId);
      }
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_IS_SET_WIR_STATUS);
    }
    /* @Trace: Dem_SUD_API_20862 */
    if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEventId])
    {
      /* @Trace: Dem_SUD_API_20863 */
      Dem_TriggerCallbackOnUdsStatus(LddEventId, LddEventStatusByteOld,
          LddDTCStatusByteOld);
    }
  }
}

#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
/******************************************************************************
 * Function Name        : Dem_ProcessCaptureDataRelated
 *
 * Service ID           : None
 *
 * Description          : Process capture data on the configured trigger
 *                        and store it to the event memory entry
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : - EventId
 *                        - EventStatus
 *                        - EnvDataCapture
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  :
 *                        Function(s) invoked :
 ******************************************************************************/
/* @Trace: SRS_Diag_04127
 */
FUNC(void, DEM_CODE) Dem_ProcessCaptureDataRelated(
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus,
  uint8 EnvDataCapture)
{
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  Dem_DTCOriginType LddDTCOrigin = LddEvent->aaEventDestination;
  Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[EventId];
  Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
  Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId, LddDTCOrigin);
  Dem_NumOfEventMemoryEntryType LddStopIdx =
        Dem_EvMem_GetStopIndexEventMemorySet(EventId, LddDTCOrigin);
  /* Already stored */
  /* @Trace: Dem_SUD_API_20032 */
  if ((LddStartIdx <= LddMemLoc) && (LddMemLoc < LddStopIdx))
  {
    /* Duplicated code for performance and runtime check(polyspace) */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddDTCOrigin)
    {
      /* @Trace: Dem_SUD_API_20033 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      if (LddMemLoc < DEM_MAX_NUMBER_EVENT_ENTRY_PRI)
      {
        /* @Trace: Dem_SUD_API_20867 */
        LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
      }
    }
    /* @Trace: Dem_SUD_API_20869 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(LddDTCOrigin))
    {
      /* @Trace: Dem_SUD_API_20870 */
      if (LddMemLoc < DEM_MAX_NUMBER_EVENT_ENTRY_UD)
      {
        /* @Trace: Dem_SUD_API_20866 */
        LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
      }
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_20868 */
      /* Do nothing */
    }
  }
  /* @Trace: SWS_Dem_00809
   * If an event memory entry exists, the Dem module shall capture the
   * ExtendedDataRecord on the configured trigger (refer to
   * DemExtendedDataRecordTrigger) and store it to the event memory entry.
   */
  /* @Trace: Dem_SUD_API_20865 */
  if (NULL_PTR != LddMemEntry)
  {
    /* @Trace: Dem_SUD_API_20126 */
    if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
    {
      /* @Trace: Dem_SUD_API_20864 */
      (void)Dem_StoreEventRelatedData(
          &Dem_EventRelatedData[LddEvent->e_PointToData],
          LddMemEntry, EventStatus, EnvDataCapture);
    }
  }
}
#endif

/******************************************************************************
 * Function Name        : Dem_SortedEventsByWWHOBDTCClass
 *
 * Service ID           : None
 *
 * Description          : Sorted events by precedence of WWHOBDDTCClass
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : NumOfEvents
 *
 * InOut parameter      : None
 *
 * Output Parameters    : EventBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  :
 *                        Function(s) invoked :
 ******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
FUNC(void, DEM_CODE) Dem_SortedEventsByWWHOBDTCClass(void)
{
  Dem_EventIdType LddEventId;
  VAR(uint16, DEM_VAR) LaaBufferWWHOBDDTCClassEvIdSorted
      [DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER];
  VAR(uint8, DEM_VAR) LaaBufferWWHOBDDTCClassEvStatusSorted
      [DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER];
  uint16 LusOffset = DEM_ZERO;
  /* @Trace: Dem_SUD_API_20905 */
  for (uint16 LusEvIdx = LusOffset;
       LusEvIdx < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER;
       LusEvIdx++)
  {
    /* @Trace: Dem_SUD_API_20913 */
    LaaBufferWWHOBDDTCClassEvIdSorted[LusEvIdx] = DEM_NO_EVENT;
    LaaBufferWWHOBDDTCClassEvStatusSorted[LusEvIdx] =
        DEM_EVENT_STATUS_UNDEFINED;
  }
  /* @Trace: Dem_SUD_API_20915 */
  for (uint8 LucClassEvIdx = DEM_DTC_WWHOBD_CLASS_NOCLASS;
       LucClassEvIdx <= DEM_DTC_WWHOBD_CLASS_C;
       (LucClassEvIdx = LucClassEvIdx << 1))
  {
    /* @Trace: Dem_SUD_API_20914 */
    for (uint16 LusEvIdx = DEM_ZERO;
         LusEvIdx < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER;
         LusEvIdx++)
    {
      LddEventId = Dem_GaaEventEDCBuffer[LusEvIdx];
      /* @Trace: Dem_SUD_API_20916 */
      if ((LddEventId <= DEM_NUMBER_OF_EVENTS) && (LddEventId != DEM_NO_EVENT))
      {
        Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
        /* @Trace: Dem_SUD_API_20917 */
        if (DEM_MAX_NUMBER_OF_DTC > LddEvent->e_PointToDTC)
        {
          uint8 LucDemWWHOBDDTCClass =
              Dem_GaaCombinedDtc[LddEvent->e_PointToDTC].eDemWWHOBDDTCClass;
          /* @Trace: Dem_SUD_API_20918 */
          if ((DEM_DTC_WWHOBD_CLASS_A == LucDemWWHOBDDTCClass)  ||
              (DEM_DTC_WWHOBD_CLASS_B1 == LucDemWWHOBDDTCClass) ||
              (DEM_DTC_WWHOBD_CLASS_B2 == LucDemWWHOBDDTCClass) ||
              (DEM_DTC_WWHOBD_CLASS_C == LucDemWWHOBDDTCClass))
          {
            /* @Trace: Dem_SUD_API_20919 */
            if (LucDemWWHOBDDTCClass == LucClassEvIdx)
            {
              /* @Trace: Dem_SUD_API_20920 */
              if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > LusOffset)
              {
                /* @Trace: Dem_SUD_API_20906 */
                LaaBufferWWHOBDDTCClassEvIdSorted[LusOffset] = LddEventId;
                LaaBufferWWHOBDDTCClassEvStatusSorted[LusOffset] =
                    Dem_GaaEventEDCBufferStatus[LusEvIdx];
                LusOffset++;
              }
            }
          }
        }
      }
    }
  }

  LusOffset = DEM_ZERO;
  /* @Trace: Dem_SUD_API_20907 */
  for (uint16 LusEvIdx = DEM_ZERO;
       LusEvIdx < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER;
       LusEvIdx++)
  {
    LddEventId = Dem_GaaEventEDCBuffer[LusEvIdx];
    /* @Trace: Dem_SUD_API_20908 */
    if ((LddEventId <= DEM_NUMBER_OF_EVENTS) && (LddEventId != DEM_NO_EVENT))
    {
      Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
      /* @Trace: Dem_SUD_API_20909 */
      if (DEM_MAX_NUMBER_OF_DTC > LddEvent->e_PointToDTC)
      {
        uint8 LucDemWWHOBDDTCClass =
            Dem_GaaCombinedDtc[LddEvent->e_PointToDTC].eDemWWHOBDDTCClass;
        /* @Trace: Dem_SUD_API_20910 */
        if ((DEM_DTC_WWHOBD_CLASS_A == LucDemWWHOBDDTCClass)  ||
            (DEM_DTC_WWHOBD_CLASS_B1 == LucDemWWHOBDDTCClass) ||
            (DEM_DTC_WWHOBD_CLASS_B2 == LucDemWWHOBDDTCClass) ||
            (DEM_DTC_WWHOBD_CLASS_C == LucDemWWHOBDDTCClass))
        {
          /* @Trace: Dem_SUD_API_20911 */
          if (LaaBufferWWHOBDDTCClassEvIdSorted[LusEvIdx] != DEM_NO_EVENT)
          {
            /* @Trace: Dem_SUD_API_20912 */
            Dem_GaaEventEDCBuffer[LusEvIdx] =
                LaaBufferWWHOBDDTCClassEvIdSorted[LusOffset];
            Dem_GaaEventEDCBufferStatus[LusEvIdx] =
                LaaBufferWWHOBDDTCClassEvStatusSorted[LusOffset];
            LusOffset++;
          }
        }
      }
    }
  }
}
#endif
#endif
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

