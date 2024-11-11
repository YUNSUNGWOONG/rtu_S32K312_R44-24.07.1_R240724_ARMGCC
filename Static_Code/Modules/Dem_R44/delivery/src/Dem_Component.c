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
**  SRC-MODULE: Dem_Component.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of Dem component functionality                      **
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
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Dtc.h"
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
#include "Dem_Component.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_SetEventAvailable                               **
**                                                                            **
** Service ID           : 0x37                                                **
**                                                                            **
** Description          : Set the available status of a specific Event.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different EventIds.                   **
**                         Non reentrant for the same EventId.                **
**                                                                            **
** Input Parameters     : EventId - Identification of a DemComponent          **
**                        AvailableStatus - This parameter specifies whether  **
**                            the respective Event shall be available (TRUE)  **
**                            or not (FALSE).                                 **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                          E_OK: getting "ComponentFailed" was successful    **
**                          E_NOT_OK: getting "ComponentFailed" was not       **
**                           successful                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04126 SRS_Diag_04142
           SRS_Diag_04220
 */
/* polyspace +4 MISRA-C3:8.5 [Justified:Low] Justify with annotations */
/* polyspace +3 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventAvailable(
  Dem_EventIdType EventId,
  boolean AvailableStatus)
{
  uint8 LucRetVal = E_NOT_OK;
  /* @Trace: SWS_Dem_00687
   * The Dem shall provide the functionality to treat events as if they were not
   * configured as DemEventParameter. The configuration parameter
   * DemAvailabilitySupport is used to enable the functionality
   * (including API Dem_SetEventAvailable).
   */

  /* @Trace: SWS_Dem_01106
   * The Dem shall not provide the function Dem_SetEventAvailable in
   * VARIANT-POST-BUILD. Rational: In VARIANTPOST-BUILD the initial values are
   * not valid before Dem_Init.
   * */
  if (DEM_UNINIT == Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_10681 */
    DEM_REPORT_ERROR(DEM_SETEVENTAVAILABLE_SID, DEM_E_UNINIT);
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (EventId == DEM_NO_EVENT))
  {
   /* @Trace: Dem_SUD_API_10682 */
    DEM_REPORT_ERROR(DEM_SETEVENTAVAILABLE_SID, DEM_E_WRONG_CONDITION);
  }
  else if ((DEM_EVENT_AVAILABLE != AvailableStatus) &&
          (DEM_EVENT_NOT_AVAILABLE != AvailableStatus))
  {
   /* @Trace: Dem_SUD_API_10683 */
    DEM_REPORT_ERROR(DEM_SETEVENTAVAILABLE_SID, DEM_E_PARAM_POINTER);
  }
  /* @Trace: Dem_SUD_API_12352 */
  else if (DEM_EVENT_AVAILABLE == AvailableStatus)
  {
    /* @Trace: SWS_Dem_01232
     * If an event is set to available using Dem_SetEventAvailable and its
     * component is "not available", Dem_SetEventAvailable shall return E_NOT_OK
     * */
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_12363 */
    #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
    Dem_ComponentIdType LddCmpntIdx = LddEvent->usDemComponentIdx;
    /* @Trace: Dem_SUD_API_10684 */
    if(DEM_NO_COMP_IDX != LddCmpntIdx)
    #endif
    {
      #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
      if(DEM_COMPONENT_AVAILABLE != Dem_ComponentAvailable[
           LddCmpntIdx - DEM_ONE])
      {
      /* @Trace: Dem_SUD_API_12366 */
        LucRetVal = E_NOT_OK;
      }
      else
      #endif
      {
        LucRetVal = E_OK;

        /* @Trace: SWS_Dem_01231
         * If the function Dem_SetEventAvailable is called for an event to set
         * the event to "available", the function shall return E_NOT_OK, in case
         * its related node is current "not available"
         * */
        /* @Trace: Dem_SUD_API_12367 */
        #if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
        uint8 LucStartIdx = DEM_ZERO;
        uint8 LucNumOfElement = DEM_ZERO;
        LucStartIdx = Dem_Components[LddCmpntIdx - DEM_ONE].
            usDemDependentCompIdx;
        LucNumOfElement = LucStartIdx + Dem_Components[LddCmpntIdx - DEM_ONE].
            usNumberOfDemDependentComp;
        /* @Trace: Dem_SUD_API_12368 */
        for ( ; LucStartIdx < LucNumOfElement; LucStartIdx++)
        {
          /* @Trace: Dem_SUD_API_12369 */
          uint16 LucDepCompIdx = Dem_ListOfDependentComponent[LucStartIdx];
          /* @Trace: Dem_SUD_API_12370 */
          if( DEM_COMPONENT_AVAILABLE != Dem_ComponentAvailable[
                   LucDepCompIdx - DEM_ONE] )
          {
            LucRetVal = E_NOT_OK;
            break;
          }
        }
        /* @Trace: Dem_SUD_API_12371 */
        if ( E_NOT_OK != LucRetVal )
        #endif
        {
          /* @Trace: SWS_Dem_01111
           * If Dem_SetEventAvailable is called with AvailableStatus == "true",
           * the Dem shall set the UDS status shall be set to 0x50 for this
           * event. */
          DEM_RST_UDSSTATUSBYTE(EventId,
              (uint8)DEM_UDS_STATUS_TNCSLC |(uint8)DEM_UDS_STATUS_TNCTOC);
          /* @Trace: SWS_Dem_01230
           * If the function Dem_SetEventAvailable is called to
           * set an event to "available", the Dem shall trigger the event
           * initialization using DEM_INIT_MONITOR_REENABLED as
           * InitMonitorReason.
           * */
          /* @Trace: SWS_Dem_00256
           */
          /* @Trace: Dem_SUD_API_12372 */
          if (LddEvent->pDemInitMonitorForEvent != NULL_PTR)
          {
            /* @Trace: Dem_SUD_API_12353 */
            /* polyspace<RTE: COR : Not a defect : No Action Planned > function
             * ptr points to a valid function */
            LddEvent->pDemInitMonitorForEvent(
                (Dem_InitMonitorReasonType) DEM_INIT_MONITOR_REENABLED);
          }
        }
      }
    }
  }
  else
  /* Trace: Dem_SUD_API_12363 */
  {
    LucRetVal = E_OK;
    /* @Trace: SWS_Dem_01109
     * When the API Dem_SetEventAvailable is called with AvailableStatus =
     * FALSE, the Dem shall return E_NOT_OK if:
     *  - for the event an event memory entry already exists, or
     *  - any of the event status flags "testFailed", "pending", "confirmed" or
     *   "warningIndicatorRequested" is set
     * */
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId,
            LddEvent->aaEventDestination);

    Dem_NumOfEventMemoryEntryType LddStopIdx =
        Dem_EvMem_GetStopIndexEventMemorySet(EventId,
            LddEvent->aaEventDestination);

    Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[EventId];

    /* The event an event memory entry already exists. */
    if ((LddStartIdx <= LddMemLoc) && (LddMemLoc < LddStopIdx))
    {
    /* @Trace: Dem_SUD_API_12354 */
      LucRetVal = E_NOT_OK;
    }
    else if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)) ||
             (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_PDTC)) ||
             (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC)) ||
             (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR)))
    {
    /* @Trace: Dem_SUD_API_10686 */
      LucRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_10685 */
      /* @Trace: SWS_Dem_01110
       * If Dem_SetEventAvailable is called with AvailableStatus == "false",
       * the Dem shall set the UDS status shall be set to 0x00 for this event.*/
      DEM_RST_UDSSTATUSBYTE(EventId, DEM_ZERO);
    }
  }

  /* @Trace: SWS_Dem_01302
   * Asynchronous behavior of Dem_SetEventAvailable
   * The Dem shall process a call of the Dem_SetEventAvailable asynchronously.
   * This means that the final result is available at a later point in time.
   * */
  /* @Trace: Dem_SUD_API_12355 */
  if (E_NOT_OK != LucRetVal)
  {
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    if (DEM_EVENT_AVAILABLE == AvailableStatus)
    {
      /* @Trace: Dem_SUD_API_12356 */
      Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
    }
    else
    {
      Dem_EvClearProcState(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);

      /* @Trace: SWS_Dem_00915
       * The Dem shall suppress a DTC if all related events of this DTC  are
       * not available.
       * If there is a one to one relationship between DTC and event, the DTC
       *   is suppressed
       * if the related event is not available.
       * If the DTC is a combined DTC, the DTC is suppressed if all combined
       *   events are not available.
       * */
      Dem_CombinedDtcPCType LddCbDTC =
          (Dem_CombinedDtcPCType) Dem_GetCbDTCByEventId(EventId);
      boolean LblIsSupressDtc = DEM_TRUE;
      /* @Trace: Dem_SUD_API_10687 */
      if (LddCbDTC != NULL_PTR)
      {
      /* @Trace: Dem_SUD_API_12357 */
        uint16 LusStartIdx = LddCbDTC->dtc_PointToEventList;
        uint16 LusNumOfElement = LusStartIdx + LddCbDTC->ddNumberOfEvents;
        /* @Trace: Dem_SUD_API_12358 */
        /* @Trace: Dem_SUD_MACRO_066 */
        if (DEM_MAX_LISTOFCOMBINEDEVENTS >= LusNumOfElement)
        {
          /* @Trace: Dem_SUD_API_12359 */
          for (; LusStartIdx < LusNumOfElement; LusStartIdx++)
          {
            uint16 LusEvIdx = Dem_ListOfCombinedEvents[LusStartIdx];
            /* @Trace: Dem_SUD_API_12360 */
            #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
            /* @Trace: Dem_SUD_API_12361 */
            if (DEM_TRUE == Dem_EvIsProcStateTriggered(LusEvIdx,
                DEM_EVPROCSTATE_EVENT_AVAILABLE))
            {
              LblIsSupressDtc = DEM_FALSE;
              break;
            }
            #endif
          }
          /* @Trace: Dem_SUD_API_12362 */
          if (DEM_TRUE == LblIsSupressDtc)
          {
            SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
            LusStartIdx = LddCbDTC->dtc_PointToEventList;
            /* @Trace: Dem_SUD_API_12364 */
            for (; LusStartIdx < LusNumOfElement; LusStartIdx++)
            {
              /* @Trace: Dem_SUD_API_12365 */
              uint16 LusEvntIdx = Dem_ListOfCombinedEvents[LusStartIdx];
              Dem_EvSetProcState(LusEvntIdx, DEM_EVPROCSTATE_DTC_SUPP);
            }
            SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
          }
        }
      }
    }
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
  }
  return LucRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_EventAvailable_Init                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Init Dem event available for all event id.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : None                                                **
*******************************************************************************/
/* @Trace: SRS_Diag_04126
 */
#if ((DEM_NUMBER_OF_EVENTS > DEM_ZERO) && \
    (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY))
FUNC(void, DEM_CODE) Dem_EventAvailable_Init(void)
{
  /* @Trace: SWS_Dem_01107
   * The value of the configuration parameter DemEventAvailable shall be used
   * as initial value for availability of an event and may be changed
   * dynamically via API Dem_SetEventAvailable.
   * */
  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
  /* @Trace: Dem_SUD_API_21000 */
  for ( Dem_EventIdType LddEventId = DEM_ONE;
        LddEventId <= DEM_NUMBER_OF_EVENTS;
        LddEventId++ )
  {
    /* @Trace: Dem_SUD_API_21001 */
    #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
    Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    if (DEM_TRUE == LddEvent->blDemEventAvailable)
    {
      /* @Trace: Dem_SUD_API_21003 */
      Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
    }
    else
    {
      /* @Trace: Dem_SUD_API_21002 */
      Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
    }
    #endif
    /*Init for Event Dependence status*/
    Dem_EvtDepdntStt[LddEventId - DEM_ONE] = DEM_NORMAL;
  }
  SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
}
#endif

/*******************************************************************************
** Function Name        : Dem_Component_Init                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Init component available for all event id.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : None                                                **
*******************************************************************************/
/* @Trace: SRS_Diag_04142
 */
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
FUNC(void, DEM_CODE) Dem_Component_Init(void)
{
  /* @Trace: SWS_Dem_01239
   * After startup all DemComponents shall be available.
   * */
  /* @Trace: Dem_SUD_API_21005 */
  for ( uint8 LucCompIdx = DEM_ONE;
        LucCompIdx <= DEM_NUMBER_OF_DEM_COMPONENT;
        LucCompIdx++ )
  {
    /* @Trace: Dem_SUD_API_21004 */
    Dem_ComponentAvailable[LucCompIdx - DEM_ONE] = DEM_COMPONENT_AVAILABLE;
    Dem_ComponentState[LucCompIdx - DEM_ONE] = DEM_COMPONENT_NOT_FAILED;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetComponentFailed                              **
**                                                                            **
** Service ID           : 0x2a                                                **
**                                                                            **
** Description          : Gets the failed status of a DemComponent            **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ComponentId - Identification of a DemComponent      **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ComponentFailed                                     **
**                                                                            **
** Return parameter     : E_OK: getting "ComponentFailed" was successful      **
**                        E_NOT_OK: getting "ComponentFailed" was not         **
**                          successful                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
/* @Trace: SRS_Diag_04142
 */
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
FUNC(Std_ReturnType, DEM_CODE) Dem_GetComponentFailed(
  Dem_ComponentIdType ComponentId,
  boolean * ComponentFailed)
{
  /* @Trace: SWS_Dem_01131
   * The Dem shall provide the interface Dem_GetComponentFailed, which allows
   * querying a DemComponents FAILED status.
   * */

  uint8 LucRetVal = E_NOT_OK;
  /* @Trace: Dem_SUD_API_11979 */
  #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
  if (ComponentId > DEM_NUMBER_OF_DEM_COMPONENT)
  {
    /* @Trace: Dem_SUD_API_11980 */
    DEM_REPORT_ERROR(DEM_GETCOMPONENTFAILED_SID, DEM_E_WRONG_CONDITION);
  }
  else if(NULL_PTR == ComponentFailed )
  {
     /* @Trace: Dem_SUD_API_11981 */
     DEM_REPORT_ERROR(DEM_GETCOMPONENTFAILED_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    if(DEM_COMPONENT_AVAILABLE != Dem_ComponentAvailable[ComponentId - DEM_ONE])
    {
      /* @Trace: Dem_SUD_API_11982 */
      /* @Trace: SWS_Dem_01134
       * The Dem shall support the availability of DemComponent. Components
       * which are not available shall be treated as if they are not included
       * in the system (e.g. Dem_GetComponentFailed will return E_NOT_OK).
       * */
      /* LucRetVal = E_NOT_OK; */
    }
    else
    {
      /* @Trace: Dem_SUD_API_10689 */
      LucRetVal = E_OK;
      *ComponentFailed = Dem_ComponentState[ComponentId - DEM_ONE];
    }
  }
  #endif
  return LucRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_SetComponentAvailable                           **
**                                                                            **
** Service ID           : 0x2b                                                **
**                                                                            **
** Description          : Set the availability of a specific DemComponent     **
**                                                                            **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ComponentId - Identification of a DemComponent      **
**                        AvailableStatus - This parameter specifies whether  **
**                         the respective Component shall be available        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Operation was successful                      **
**                        E_NOT_OK: Operation failed                          **
**                                                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
/* @Trace: SRS_Diag_04142
 */
/* polyspace +3 MISRA-C3:8.5 [Justified:Low] Justify with annotations */
/* polyspace +2 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
FUNC(Std_ReturnType, DEM_CODE) Dem_SetComponentAvailable(
  Dem_ComponentIdType ComponentId,
  boolean AvailableStatus
  )
{
  /* @Trace: SWS_Dem_01135
   * The interface Dem_SetComponentAvailable shall be available to set the
   * availability state of a component.
   */
  uint8 LucRetVal = E_NOT_OK;
  #if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
  uint8 LucStartIdx = DEM_ZERO;
  uint8 LucNumOfElement = DEM_ZERO;
  #endif

  #if ((DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO) && \
       (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY))
  uint8 LucStartEvtIdx = DEM_ZERO;
  uint8 LucNumOfEvtElement = DEM_ZERO;
  #endif
  if(ComponentId > DEM_NUMBER_OF_DEM_COMPONENT)
  {
    /* @Trace: Dem_SUD_API_12310 */
    DEM_REPORT_ERROR(DEM_SETCOMPONENTAVAILABLE_SID, DEM_E_WRONG_CONDITION);
    /*@retVal = E_NOT_OK;*/
  }
  else if((DEM_COMPONENT_AVAILABLE != AvailableStatus ) &&
          (DEM_COMPONENT_NOT_AVAILABLE != AvailableStatus ))
  {
    /* @Trace: Dem_SUD_API_12318 */
    DEM_REPORT_ERROR(DEM_SETCOMPONENTAVAILABLE_SID, DEM_E_PARAM_DATA);
    /*@retVal = E_NOT_OK;*/
  }
  else
  {
    LucRetVal = E_OK;
    boolean LblOldCompntStt = Dem_ComponentAvailable[ComponentId - DEM_ONE];
    /* @Trace: Dem_SUD_API_12319 */
    if(AvailableStatus != LblOldCompntStt)
    {
      /* Set dem component available */
      Dem_ComponentAvailable[ComponentId - DEM_ONE] = AvailableStatus;
    }

    /* @Trace: SWS_Dem_01120
     * The Dem shall allow defining relations between DemComponent. The
     * relations are directed, which means one component is depending on
     * another component (DemImmediateChildComponentRef).
     * Any component which has a directed relation (also over multiple
     * components) is considered as parent component.
     */

    /* @Trace: SWS_Dem_01226
     * If a DemComponent is set to "not available" via
     * Dem_SetComponentAvailable, the Dem shall treat all the dependent
     * components (children) as if they are set as "not available".
     * */
    /* @Trace: Dem_SUD_API_12320 */
    #if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
    /* get index and size for dependence components */
    LucStartIdx = Dem_Components[ComponentId - DEM_ONE].usDemDependentCompIdx;
    LucNumOfElement = LucStartIdx + Dem_Components[ComponentId - DEM_ONE].
        usNumberOfDemDependentComp;

    /* loop all dependence component of this component */
    /* @Trace: Dem_SUD_API_12321 */
    for( ; LucStartIdx < LucNumOfElement; LucStartIdx++)
    {
      /* Set dependence component to AvailableStatus */
      uint16 LusDepCompIdx = Dem_ListOfDependentComponent[LucStartIdx];
      /* @Trace: Dem_SUD_API_12322 */
      if ( AvailableStatus != Dem_ComponentAvailable[LusDepCompIdx - DEM_ONE] )
      {
        /* @Trace: Dem_SUD_API_12323 */
        /* Update new state */
        Dem_ComponentAvailable[LusDepCompIdx -DEM_ONE] = AvailableStatus;
      }
    }


    /* @Trace: SWS_Dem_01227
     * If a DemComponent is set to "not available" via
     * Dem_SetComponentAvailable, the Dem shall set all assigned events to
     * "not available", including the events of all child nodes.
     * The behavior for the events will be analogous to setting
     * each event individually to "not available" (e.g. setting the event
     * status).
     * */
    /* @Trace: SWS_Dem_01229
     * If a DemComponent is set to available via Dem_SetComponentAvailable, all
     * assigned events are also set to "available", including the events of all
     * child nodes (if those nodes are not still set to "not available"). The
     * behavior for the individual events will be analogous to setting them
     * individually to "available" (e.g. triggering InitMonitorForEvent).
     * */
    /* @Trace: Dem_SUD_API_12324 */
    #if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
    LucStartIdx = Dem_Components[ComponentId - DEM_ONE].usDemDependentCompIdx;
    LucNumOfElement = LucStartIdx + Dem_Components[ComponentId - DEM_ONE].
        usNumberOfDemDependentComp;

    /* loop all dependence component of this component */
    /* @Trace: Dem_SUD_API_12325 */
    for( ; LucStartIdx < LucNumOfElement; LucStartIdx++)
    {
      /* Set dependence component to AvailableStatus */
      /* @Trace: Dem_SUD_API_12311 */
      #if ((DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO) && \
           (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY))
      uint16 LusDepCompIdx = Dem_ListOfDependentComponent[LucStartIdx];
      LucStartEvtIdx = Dem_Components[LusDepCompIdx - DEM_ONE].
          usDemEventIdIndex;
      LucNumOfEvtElement = LucStartEvtIdx +
          Dem_Components[LusDepCompIdx - DEM_ONE].usNumberOfDemEventId;
      /* @Trace: Dem_SUD_API_12313 */
      for(; LucStartEvtIdx<LucNumOfEvtElement; LucStartEvtIdx++)
      {
        /* @Trace: Dem_SUD_API_12312 */
        uint16 LusEvtIdx = Dem_ListOfEventIdComponent[LucStartEvtIdx];
        (void)Dem_SetEventAvailable( LusEvtIdx,
           (DEM_COMPONENT_AVAILABLE == AvailableStatus) ? DEM_EVENT_AVAILABLE
               : DEM_EVENT_NOT_AVAILABLE);
      }
      #endif
    }
    #endif
    #endif
    /* @Trace: Dem_SUD_API_12314 */
    #if ((DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO) && \
         (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY))
    /* get index and size for dependence events */
    LucStartEvtIdx = Dem_Components[ComponentId - DEM_ONE].usDemEventIdIndex;
    LucNumOfEvtElement = LucStartEvtIdx +
        Dem_Components[ComponentId - DEM_ONE].usNumberOfDemEventId;

    /* @Trace: SWS_Dem_01121
     * The Dem shall allow to assign events to DemComponents.
     */
    /* loop all events of this component */
    /* @Trace: Dem_SUD_API_12317 */
    for (; LucStartEvtIdx < LucNumOfEvtElement; LucStartEvtIdx++)
    {
      uint16 LusEvtIdx = Dem_ListOfEventIdComponent[LucStartEvtIdx];
      if(DEM_COMPONENT_AVAILABLE == AvailableStatus)
      {
        /* @Trace: Dem_SUD_API_12315 */
        (void)Dem_SetEventAvailable(LusEvtIdx, DEM_EVENT_AVAILABLE);
      }
      else
      {
        /* @Trace: SWS_Dem_01136
         * With setting a DemComponent to not available, all assigned events
         * shall also be set as not available.
         * */
        /* @Trace: SWS_Dem_01228
         * If a DemComponent is set to "not available" via
         * Dem_SetComponentAvailable and any individual event assigned to it is
         * already failed, the individual event will be kept as "available".
         * Dem_SetComponentAvailable still shall return E_OK
         * */
        /* @Trace: Dem_SUD_API_12316 */
        if(DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LusEvtIdx, DEM_UDS_STATUS_TF))
        {
          /* @Trace: Dem_SUD_API_10688 */
          (void)Dem_SetEventAvailable(LusEvtIdx, DEM_EVENT_NOT_AVAILABLE);
        }
      }
    }
    #endif
  }
  return LucRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_CheckConsecutiveFault                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Chech the consecutive fault of event id             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId, EventStatus                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04142
 */
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
FUNC(void, DEM_CODE) Dem_CheckConsecutiveFault(
  Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{

  /* get ComponentId */
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  Dem_ComponentIdType LddCompntIdx = LddEvent->usDemComponentIdx;
  #if ((DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO) || \
      (DEM_NUM_OF_PARENT_COMPONENT_LIST > DEM_ZERO))
  uint8 LucStartIdx = DEM_ZERO;
  uint8 LucNumOfElement = DEM_ZERO;
  #endif
  /************************************************************
   * Check consecutive fault for event
   ************************************************************/
  if ((EventId > DEM_NUMBER_OF_EVENTS) || (EventId == DEM_NO_EVENT))
  {
    /* @Trace: Dem_SUD_API_21025 */
    /* Do nothing */
  }
  else if ((DEM_EVENT_STATUS_FAILED != EventStatus) &&
           (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED != EventStatus))
  {
    /* @Trace: Dem_SUD_API_21007 */
    /* Do nothing */
  }
  /*Check whether event have the Dem component*/
  else if (DEM_NO_COMP_IDX != LddCompntIdx)
  {
    /* @Trace: Dem_SUD_API_21009 */
    #if (DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO)
    /* @Trace: Dem_SUD_API_21008 */
    LucStartIdx = Dem_Components[LddCompntIdx - DEM_ONE].usDemEventIdIndex;
    LucNumOfElement = LucStartIdx + Dem_Components[LddCompntIdx - DEM_ONE].
        usNumberOfDemEventId;
    #endif
    /* @Trace: SWS_Dem_01126
     * Whenever an event reports FAILED, it shall be considered as
     * CONSECUTIVE FAULT, if any other event with higher priority at the same
     * DemComponent already is FAILED
     * */
    /* @Trace: Dem_SUD_API_21021 */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
    if (DEM_TRUE != Dem_Components[LddCompntIdx-DEM_ONE].blDemCompIgrPrio)
    {
      /* @Trace: Dem_SUD_API_21020 */
      #if (DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO)
      /* @Trace: Dem_SUD_API_21019 */
      for (; LucStartIdx < LucNumOfElement; LucStartIdx++)
      {
        /* @Trace: SWS_Dem_01128
         * The Dem shall allow to ignore the priority of events ignore the
         * priority of events. In this case, the event shall only be considered
         * as CONSECUTIVE FAULT if any parent component is FAILED.
         *  */

        /* @Trace: SWS_Dem_01122
         * The Dem shall allow sorting the events assigned to a DemComponent by
         * priority. The priority is defined per event as DemComponentPriority.
         */
        uint16 LusDstEvtIdx = Dem_ListOfEventIdComponent[LucStartIdx];
        uint8 LucPriEvtSrc = LddEvent->usDemComponentPriority;
        uint8 LucPriEvtDst = Dem_Event[LusDstEvtIdx - DEM_ONE].
            usDemComponentPriority;
        /* @Trace: Dem_SUD_API_21017 */
        if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(LusDstEvtIdx, DEM_UDS_STATUS_TF)) &&
            (LucPriEvtSrc > LucPriEvtDst))
        {
          /* @Trace: Dem_SUD_API_21006 */
          Dem_EvtDepdntStt[EventId - DEM_ONE] = DEM_CONSECUTIVE_FAULT;
        }
      }
      #endif
    }

    /* @Trace: SWS_Dem_01127
     * Whenever an event reports FAILED, it shall be considered as CONSECUTIVE
     * FAULT, if any parent DemComponent is FAILED.
     */
    /* @Trace: Dem_SUD_API_21011 */
    #if (DEM_NUM_OF_PARENT_COMPONENT_LIST > DEM_ZERO)
    /* @Trace: Dem_SUD_API_21010 */
    LucStartIdx = Dem_Components[LddCompntIdx - DEM_ONE].usDemParentCompIdx;
    LucNumOfElement = Dem_Components[LddCompntIdx - DEM_ONE].
        usNumberOfDemParentComp;
    /* @Trace: Dem_SUD_API_21024 */
    for (; LucStartIdx < LucNumOfElement; LucStartIdx++)
    {
      uint16 LusCmpntPrtIdx = Dem_ListOfParrentComponent[LucStartIdx];
      /* @Trace: Dem_SUD_API_21023 */
      if (DEM_COMPONENT_FAILED == Dem_ComponentState[LusCmpntPrtIdx - DEM_ONE])
      {
        /* @Trace: Dem_SUD_API_21022 */
        Dem_EvtDepdntStt[EventId - DEM_ONE] = DEM_CONSECUTIVE_FAULT;
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_21012 */
    if (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED == EventStatus)
    {
      /* @Trace: Dem_SUD_API_21013 */
      /* @Trace: SWS_Dem_01211
       * A report of DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (e.g. either via
       * interface call or when reaching the configured threshold in debounce
       * algorithm) which is considered as consecutive report of a Failed event
       * shall not be stored to the failure memory. The handling shall be
       * analogous to storage condition not fulfilled.*/
      Dem_EvtDepdntStt[EventId - DEM_ONE] = DEM_CONSECUTIVE_FAULT;
    }

    /* @Trace: SWS_Dem_01129
     * If a reported failure is not considered as consecutive fault, it shall be
     * considered as CAUSAL FAULT
     */

    /* @Trace: SWS_Dem_01218
     * If a reported failure is not considered as consecutive fault and it has
     * configured a DemCausalityDelayTime, it shall be considered as
     * PRELIMINARY-CAUSAL FAULT
     */
    /* @Trace: Dem_SUD_API_21016 */
    if (DEM_CONSECUTIVE_FAULT != Dem_EvtDepdntStt[EventId - DEM_ONE])
    {
      if (LddEvent->usDemCausalityDelayTime > DEM_ZERO)
      {
        /* @Trace: Dem_SUD_API_21014 */
        Dem_EvtDepdntStt[EventId - DEM_ONE] = DEM_PRELIMINARY_CAUSAL_FAULT;
      }
      else
      {
        /* @Trace: Dem_SUD_API_21015 */
        Dem_EvtDepdntStt[EventId - DEM_ONE] = DEM_CAUSAL_FAULT;
      }
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_21018 */
    /* Nothing to do */
  }
}
#endif

/*******************************************************************************
** Function Name        : Dem_ComponentProcessing                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Process for dem component                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04142
 */
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
FUNC(void, DEM_CODE) Dem_ComponentProcessing(Dem_EventIdType EventId)
{
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  /* @Trace: SWS_Dem_01118
   * The Dem shall represent monitored components as DemComponent with a unique
   * identifier, which is used in interfaces to identify the component.
   */
  Dem_ComponentIdType LddCmpntIdx = LddEvent->usDemComponentIdx;
  /* @Trace: Dem_SUD_API_21038 */
  #if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
  /* @Trace: Dem_SUD_API_21036 */
  boolean LblOldCmpntStt = DEM_FALSE;
  uint8 LucStartIdx = DEM_ZERO;
  uint8 LucNumOfElement = DEM_ZERO;
  #endif
  /* @Trace: Dem_SUD_API_21027 */
  if (DEM_NO_COMP_IDX != LddCmpntIdx)
  {
    /* @Trace: SWS_Dem_01123
     * On reporting an error (DEM_MONITOR_STATUS_TF) for an event, the
     * assigned DemComponent shall be set as FAILED in the context of the
     * event report.
     * */

    /* bit No.0 is set of Monitor */
    if (DEM_IS_BIT_SET_MONITORSTATUSBYTE(EventId, DEM_MONITOR_STATUS_TF))
    {
      /* @Trace: Dem_SUD_API_21035 */
      /* @Trace: Dem_SUD_MACRO_015 */
      #if ((DEM_TRIGGER_FIM_REPORTS == STD_ON) && \
          (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO))
      LblOldCmpntStt = Dem_ComponentState[LddCmpntIdx - DEM_ONE];
      #endif

      Dem_ComponentState[LddCmpntIdx - DEM_ONE] = DEM_COMPONENT_FAILED;
      /* @Trace: Dem_SUD_API_21039 */
      #if ((DEM_TRIGGER_FIM_REPORTS == STD_ON) && \
          (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO))
      /* @Trace: SWS_Dem_01132
       * If DemTriggerFiMReports is enabled, the Dem shall notify the
       * FiM module on each change of DemComponent failed status by
       * calling the function DemTriggerOnComponentStatus
       */
      /* @Trace: SWS_Dem_01133
       * If the component status is changing and DemComponentFailedCallbackFnc
       * is configured or DemComponentFailedCallbackUsePort is set to TRUE,
       * the Dem shall trigger the callback DemTriggerOnComponentStatus
       * */
      /* @Trace: SWS_Dem_01119
       * Each DemComponent shall have a boolean status FAILED, which represents
       * the information whether the component has errors or not.
       */
      /* @Trace: Dem_SUD_API_21040 */
      if(LblOldCmpntStt != Dem_ComponentState[LddCmpntIdx - DEM_ONE])
      {
        /* @Trace: Dem_SUD_API_21041 */
        if(NULL_PTR != Dem_Components[LddCmpntIdx - DEM_ONE].pFailedCallbackFnc)
        {
          /* @Trace: Dem_SUD_API_21026 */
          /*calling DemTriggerOnComponentStatus*/
          Dem_Components[LddCmpntIdx - DEM_ONE].pFailedCallbackFnc(LddCmpntIdx);
        }
        /*else if(DEM_TRUE == Dem_Components[LddCmpntIdx - DEM_ONE].
         * blDemCompFailedCBUsePort)
         {
         Rte_Call_DemTriggerOnComponentStatus(LddCmpntIdx);
         }*/
      }
      #endif
      /* @Trace: Dem_SUD_API_21042 */
      #if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
      /* @Trace: SWS_Dem_01124
       * On setting a DemComponent to FAILED, all dependent components
       * shall be set as FAILED
       * */
      LucStartIdx = Dem_Components[LddCmpntIdx - DEM_ONE].usDemDependentCompIdx;
      LucNumOfElement = LucStartIdx + Dem_Components[LddCmpntIdx - DEM_ONE].
          usNumberOfDemDependentComp;
      /* @Trace: Dem_SUD_API_21043 */
      for (; LucStartIdx < LucNumOfElement; LucStartIdx++)
      {
        uint16 LusDepCompIdx = Dem_ListOfDependentComponent[LucStartIdx];
        LblOldCmpntStt = Dem_ComponentState[LusDepCompIdx - DEM_ONE];
        /* @Trace: Dem_SUD_API_21044 */
        if (LblOldCmpntStt != Dem_ComponentState[LddCmpntIdx - DEM_ONE])
        {
          /* @Trace: Dem_SUD_API_21037 */
          Dem_ComponentState[LusDepCompIdx - DEM_ONE] = DEM_COMPONENT_FAILED;
        }
      }
      #endif
    }
    else
    {
      /* @Trace: Dem_SUD_API_21028 */
      /* @Trace: SWS_Dem_01125
       * A DemComponent shall be set to NOT FAILED, when all assigned events
       * are NOT FAILED (DEM_MONITOR_STATUS_TF) and all parent components are
       * NOT FAILED.
       * */
      /* @Trace: Dem_SUD_API_21029 */
      #if (DEM_NUM_OF_PARENT_COMPONENT_LIST > DEM_ZERO)
      /* @Trace: Dem_SUD_API_21045 */
      boolean LblIsSetFail = DEM_TRUE;
      LucStartIdx = Dem_Components[LddCmpntIdx - DEM_ONE].usDemParentCompIdx;
      LucNumOfElement = LucStartIdx + Dem_Components[LddCmpntIdx - DEM_ONE].
          usNumberOfDemParentComp;

      /* check all parent are not failed */
      /* @Trace: Dem_SUD_API_21048 */
      for (; LucStartIdx < LucNumOfElement; LucStartIdx++)
      {
        uint16 LucPrtCompIdx = Dem_ListOfParrentComponent[LucStartIdx];
        /* @Trace: Dem_SUD_API_21046 */
        if (DEM_COMPONENT_FAILED == Dem_ComponentState[LucPrtCompIdx - DEM_ONE])
        {
          /* @Trace: Dem_SUD_API_21047 */
          LblIsSetFail = DEM_FALSE;
          break;
        }
      }
      #endif
      /* check all event of this component are not failed*/
      /* @Trace: Dem_SUD_API_21030 */
      #if (DEM_NUM_OF_PARENT_COMPONENT_LIST > DEM_ZERO)
      /* @Trace: Dem_SUD_API_21031 */
      if (DEM_FALSE != LblIsSetFail)
      #endif
      {
        /* @Trace: Dem_SUD_API_21032 */
        #if ((DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO) && \
            (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO))
        LucStartIdx = Dem_Components[LddCmpntIdx-DEM_ONE].usDemEventIdIndex;
        LucNumOfElement = LucStartIdx + Dem_Components[LddCmpntIdx - DEM_ONE].
            usNumberOfDemEventId;
        /* @Trace: Dem_SUD_API_21050 */
        for (; LucStartIdx < LucNumOfElement; LucStartIdx++)
        {
          uint16 LusEvtIdx = Dem_ListOfEventIdComponent[LucStartIdx];
          /* @Trace: Dem_SUD_API_21049 */
          if (DEM_IS_BIT_SET_MONITORSTATUSBYTE(LusEvtIdx,
               DEM_MONITOR_STATUS_TF))
          {
            /* @Trace: Dem_SUD_API_30005 */
            LblIsSetFail = DEM_FALSE;
            break;
          }
        }
        #endif
      }
      /* all assigned events are NOT FAILED (DEM_MONITOR_STATUS_TF) and all
       * parent components are NOT FAILED. ==> set to componet to Not Failed*/
      /* @Trace: Dem_SUD_API_21033 */
      #if (DEM_NUM_OF_PARENT_COMPONENT_LIST > DEM_ZERO)
      /* @Trace: Dem_SUD_API_21034 */
      if(DEM_FALSE != LblIsSetFail)
      #endif
      {
        /* @Trace: Dem_SUD_API_21058 */
        Dem_ComponentState[LddCmpntIdx - DEM_ONE] = DEM_COMPONENT_NOT_FAILED;
      }
    }
  }
}
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
