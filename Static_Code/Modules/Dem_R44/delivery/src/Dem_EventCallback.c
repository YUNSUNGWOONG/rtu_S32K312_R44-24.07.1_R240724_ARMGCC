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
**  SRC-MODULE: Dem_EventCallback.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of call of event related callbacks                  **
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
#include "Dem_Ram.h"        /* DEM Ram Header File */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif
#if ((DEM_FIM_INTEGRATED == STD_ON) && (DEM_TRIGGER_FIM_REPORTS == STD_ON))
#include "FiM_Dem.h"              /* FiM module header file */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "Dcm_Dem.h"
#include "Rte_Dem.h"
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */

#include "Dem_Dtc.h"
#include "Dem_Event.h"
#include "Dem_EventCallback.h"
#include "Dem_EventMemory.h"

#if (DEM_J1939_SUPPORT == STD_ON)
#include "J1939Dcm_Dem.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************
 * Function Name        : Dem_TriggerCallbackOnUdsStatus
 *
 * Service ID           : None
 *
 * Description          : Trigger the callback functions on event status change
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, EventStatusByteOld, DTCStatusOld
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *
 *                        Dcm_DemTriggerOnDTCStatus
 *****************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_BSW_00457 SRS_Diag_04010 SRS_Diag_04031
           SRS_Diag_04112 SRS_Diag_04155 SRS_Diag_04148 SRS_Diag_04164
 */
FUNC(void, DEM_CODE)
Dem_TriggerCallbackOnUdsStatus(
  const Dem_EventIdType EventId,
  const Dem_UdsStatusByteType EventStatusByteOld,
  const Dem_UdsStatusByteType DTCStatusOld)
{
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  uint8 LucMask =
      Dem_EvMem_GetAvailableMaskFromMemSetIdx(LddEvent->ucEventMemDstIdx);
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false. Avoid the runtime error of the
   * polyspace */
  /* @Trace: Dem_SUD_API_11398 */
  if ((DEM_NO_EVENT != EventId) && (EventId <= DEM_NUMBER_OF_EVENTS) )
  {  
    const Dem_UdsStatusByteType LddEventStatusByteNew =
        Dem_AllEventStatusByte[EventId];

    /* if eventStatus is not changed, DTCStatus will be not changed */  
    /* @Trace: Dem_SUD_API_11409 */
    if (EventStatusByteOld != LddEventStatusByteNew)
    {
      /* if callbacks EventStatusChanged are configured , Dcm shall invoke all
       * configured callbacks */
      /* @Trace: Dem_SUD_API_11420 */
      if ((DEM_ZERO != LddEvent->ddNumOfEventStatusFct) &&
          (DEM_ZERO !=
              ((EventStatusByteOld ^ LddEventStatusByteNew) & LucMask)))
      {
        Dem_NumOfEvtStatFctsType LddMax =
            LddEvent->PointToEventStatusFncMap +
            LddEvent->ddNumOfEventStatusFct;
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition always evaluates to true. Avoid the runtime error of the
         * polyspace */
        /* @Trace: Dem_SUD_API_10811 */
        if (LddMax <= Dem_Max_ListOfEvtStatusChangedFctPtr)
        {
          Dem_NumOfEvtStatFctsType LddIdx;
          /* @Trace: Dem_SUD_API_11423 */
          for (LddIdx = LddEvent->PointToEventStatusFncMap;
               LddIdx < LddMax;
               LddIdx++)
          {           
            /* notify Application/Bsw that Event Status has changed */
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * If-condition always evaluates to true. Avoid the runtime error of
             * the polyspace */
            /* @Trace: Dem_SUD_API_10810 */
            if (NULL_PTR != Dem_ListOfEvtStatusChangedFctPtr[LddIdx])
            {
              /* @Trace: Dem_SUD_API_11422 */
              (void)Dem_ListOfEvtStatusChangedFctPtr[LddIdx](EventStatusByteOld,
                  LddEventStatusByteNew);
            }
          }
        }
      }

      /* @Trace: SWS_Dem_00475
       * If "event related data" (extended data or freeze frame data) of an
       * event memory entry is added or updated AND notifications on data
       * changes are configured via DemCallbackEventDataChanged, the Dem shall
       * trigger these configured event-specific notifications as well as the
       * general notification GeneralCallbackEventDataChanged
       * */
      /* @Trace: Dem_SUD_API_11424 */
      /* @Trace: Dem_SUD_MACRO_046 */
      #if (DEM_GENERAL_INTERFACE_SUPPORT == STD_ON)
      /* @Trace: Dem_SUD_API_11425 */
      /* polyspace +1 MISRA-C3:17.7 [Justified:Low] Justify with annotations */
      Rte_Call_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged(
          EventId, EventStatusByteOld, LddEventStatusByteNew);
      #endif

      /* Trigger FIM on event status changes */
      /* @Trace: SWS_Dem_00029
       * If DemTriggerFiMReports is set to True, the Dem module shall notify the
       * FiM module (refer to [8]) on each change of the monitoring status
       * (refer also to [SWS_Dem_00016]), by calling the function
       * FiM_DemTriggerOnEventStatus (with same syntax as
       * <Module>_DemTriggerOnMonitorStatus) in the context of
       * Dem_SetEventStatus.
       */
      /* @Trace: Dem_SUD_API_11427 */
      #if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
      #if (DEM_FIM_INTEGRATED == STD_ON)
      /* @Trace: Dem_SUD_API_11399 */
      #if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)
      /* @Trace: Dem_SUD_API_11426 */
      FiM_DemTriggerOnMonitorStatus(EventId);
      #endif
      #else
      /* @Trace: Dem_SUD_API_11400 */
      #error "In case DemTriggerFiMReports is true, DemFimIntegrated shall be true"
      #endif
      #endif

      /* Has DTC ? */
      /* @Trace: Dem_SUD_API_10812 */
      if (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
      {
        const Dem_UdsStatusByteType LddDTCStatusNew = Dem_GetDTCStatus(EventId);
        Dem_CombinedDtcPCType LddCbDTC =
            &Dem_GaaCombinedDtc[LddEvent->e_PointToDTC];

        /* @IF_REQ : Apply LddCbDTC->UdsStatusAvailabilityMask : Generator shall
         * be modified  */
        /* @Trace: Dem_SUD_API_11401 */
        if (((DTCStatusOld ^ LddDTCStatusNew) & LucMask) != DEM_ZERO)
        {
          /* @Trace: Dem_SUD_API_11402 */
          /* polyspace+1 MISRA-C3:14.3 [Justified:Low] "It depends on the configuration." */
          if (DEM_NO_DTC != LddCbDTC->ulUdsDtc)
          {
            /* @Trace: SWS_Dem_00284
             * The Dem module shall trigger the callback function configured
             * in DemCallbackDTCStatusChanged on every DemDTC status change.
             * */
            /* @Trace: SWS_Dem_00828
             * If the status of a DTC changes, the Dem shall call the configured
             * DemCallbackDTCStatusChanged function */
            /* @Trace: Dem_SUD_API_11403 */
            if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddEvent->aaEventDestination)
            {
              /* @Trace: Dem_SUD_API_11405 */
              for (uint8 LucCbkIdx = DEM_ZERO;
                         LucCbkIdx < DEM_NUMBER_OF_DEM_CLIENT;
                         LucCbkIdx++)
              {
                /* One DemEventMemorySet corresponding one DemPrimaryMemory
                 * (ref Dem_GaaDemPrimaryMemory) */
                /* @Trace: Dem_SUD_API_11404 */
                if (LddEvent->ucEventMemDstIdx ==
                    Dem_Client[LucCbkIdx].usDemEventMemorySetId)
                {
                  /* @Trace: Dem_SUD_API_11408 */
                  uint8 LucStartPos =
                      Dem_Client[LucCbkIdx].usCallbackDTCStatusChangedFncId;
                  uint8 LucEndPos = LucStartPos +
                      Dem_Client[LucCbkIdx].usNumCallbackDTCStatusChangedFnc;
                  /* @Trace: Dem_SUD_API_11407 */
                  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
                  /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
                  for (; LucStartPos < LucEndPos; LucStartPos++)
                  {
                    /* @Trace: Dem_SUD_API_10813 */
                    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
                    if (NULL_PTR != Dem_GaaDtcStatusChangedFctPtr[LucStartPos])
                    /* polyspace<MISRA-C:1.1:Not a defect:Justify with
                     * annotations a defect> Enter comment here */
                    {
                      /* @Trace: Dem_SUD_API_11406 */
                      Dem_GaaDtcStatusChangedFctPtr[LucStartPos](
                          LddCbDTC->ulUdsDtc, DTCStatusOld, LddDTCStatusNew);
                    }
                  }
                  break;
                  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
                }
              }
            }

            /* @Trace: SWS_Dem_00255
             * Triggers on changes of the UDS DTC status byte. Allows
             * to trigger on ROE Event for subservice OnDTCStatusChanged. */
            (void)Dcm_DemTriggerOnDTCStatus(
                LddCbDTC->ulUdsDtc, DTCStatusOld, LddDTCStatusNew);

          } /* End of if (DEM_NO_DTC != LddCbDTC->ulUdsDtc) */

          /* @Trace: SWS_Dem_00986
           * The Dem module shall trigger the callback function configured in
           * DemCallbackOBDDTCStatusChanged on every DemObdDTC status change.*/
          /* @Trace: Dem_SUD_API_11410 */
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
              (DEM_NUM_OF_OBDCBDTCSTATUSCHANGED > DEM_ZERO)
          /* @Trace: Dem_SUD_API_11411 */
          if ((DEM_NO_DTC != LddCbDTC->usObdDtc) &&
              (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddEvent->aaEventDestination) &&
              (DEM_ZERO != ((DTCStatusOld ^ LddDTCStatusNew) & LucMask)))
          {
            uint8 LucStartPos = DEM_START_OBDCBDTCSTATUSCHANGED;
            uint8 LucEndPos = LucStartPos + DEM_NUM_OF_OBDCBDTCSTATUSCHANGED;
            for (; LucStartPos < LucEndPos; LucStartPos++)
            {
              /* polyspace<RTE:UNR:Not a defect:No action planned>
               * If-condition always evaluates to false. Avoid the runtime error
               * of the polyspace */
              /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations a
               * defect> Enter comment here */
              /* @Trace: Dem_SUD_API_11413 */
              if (NULL_PTR != Dem_GaaDtcStatusChangedFctPtr[LucStartPos])
              /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations a
               * defect> Enter comment here */
              {
                /* @Trace: Dem_SUD_API_11412 */
                Dem_GaaDtcStatusChangedFctPtr[LucStartPos](
                    LddCbDTC->usObdDtc, DTCStatusOld, LddDTCStatusNew);
              }
            }
            /* @Trace: Dem_SUD_API_11414 */
            (void)Dcm_DemTriggerOnDTCStatus(
                LddCbDTC->usObdDtc, DTCStatusOld, LddDTCStatusNew);
          }
          #endif
        }

        /* @Trace: Dem_SUD_API_11415 */
        #if (DEM_J1939_SUPPORT == STD_ON)
        /* @Trace: Dem_SUD_API_11416 */
        if (DEM_NO_DTC != LddCbDTC->J1939DTCValue)
        {
          /* @Trace: SWS_Dem_00987
           * The Dem module shall trigger the callback function configured in
           * DemCallbackJ1939DTCStatusChanged on every J1939 DTC status change.
           */

          /* @Trace: SWS_Dem_00971
           * In case the TestFailed bit in the event status changes and a
           * J1939 DTC number is assigned to that event parameter, the function
           * J1939Dcm_DemTriggerOnDTCStatus shall be called. */
          /* @Trace: Dem_SUD_API_11417 */
          if (((DTCStatusOld ^ LddDTCStatusNew) & DEM_UDS_STATUS_TF) != DEM_ZERO)
          {
            /* polyspace<MISRA-C:8.1:Not a defect:Justify with annotations a
             * defect> This function is defined by Dcm */
            /* polyspace<MISRA-C:16.10:Not a defect:Justify with annotations a
             * defect> This don't return error information */
            #if (DEM_NUM_OF_J1939CBDTCSTATUSCHANGED > DEM_ZERO)
            uint8 LucStartPos = DEM_START_J1939CBDTCSTATUSCHANGED;
            uint8 LucEndPos = LucStartPos + DEM_NUM_OF_J1939CBDTCSTATUSCHANGED;
            /* @Trace: Dem_SUD_API_11421 */
            for (; LucStartPos < LucEndPos; LucStartPos++)
            {
              /* @Trace: Dem_SUD_API_11419 */
              if (NULL_PTR != Dem_GaaDtcStatusChangedFctPtr[LucStartPos])
              {
                /* @Trace: Dem_SUD_API_11418 */
                Dem_GaaDtcStatusChangedFctPtr[LucStartPos](
                    LddCbDTC->J1939DTCValue, DTCStatusOld, LddDTCStatusNew);
              }
            }
            #endif
            uint8 LucClientId = Dem_EvMem_GetClientIDFromEventMemorySet(
                LddEvent->ucEventMemDstIdx);
            (void)J1939Dcm_DemTriggerOnDTCStatus(
                LddCbDTC->J1939DTCValue, LucClientId);
          }
        }
        #endif
      }
    }
  }
}

/*******************************************************************************
 * Function Name        : DemTriggerCallbackOnMonitorStatus
 *
 * Service ID           : None
 *
 * Description          : Trigger the callback functions on monitor status
 *                        change
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaMonitorStatusChangedFctPtr
 *                        Function(s) invoked :
 ******************************************************************************/
/* @Trace: SRS_Diag_04067
 */
FUNC(void, DEM_CODE) DemTriggerCallbackOnMonitorStatus(Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_11428 */
  if (DEM_TRUE == Dem_EventIdIsValid(EventId))
  {
    Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: SWS_Dem_01283
     * Upon processing the monitor status for reported event with
     * DemEventKind = DEM_EVENT_KIND_SWC,the Dem shall call the monitor status
     * changed callback C/S Interface CallbackMonitorStatusChange whenever the
     * monitor status has changed and a C/S interface is configured for this
     * event. */
    /* @Trace: Dem_SUD_API_11429 */
    if (DEM_EVENT_KIND_SWC == Dem_GetEventKind(EventId))
    {
       /* @Trace: Dem_SUD_API_11430 */
      if (DEM_ZERO != LddEvent->ucNumberofMonitorStatus)
      {
        uint16 LusStartIdx = LddEvent->e_PointToMonitorStatus;
        uint16 LusStopIdx = LusStartIdx + LddEvent->ucNumberofMonitorStatus;
        /* @Trace: Dem_SUD_API_11433 */
        for (; LusStartIdx < LusStopIdx; LusStartIdx++)
        {
           /* @Trace: Dem_SUD_API_10814 */
          /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Call function.*/
          /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
          if (NULL_PTR != Dem_GaaMonitorStatusChangedFctPtr[LusStartIdx])
          {
            /* @Trace: Dem_SUD_API_11431 */
            /* In case there is no DemCallbackMonitorStatusChangedFnc, the Dem
             * will have an R-Port requiring the interface
             * CallbackMonitorStatusChanged, whose name is generated by using
             * the unique callback-prefix followed by the event name. */
            Dem_GaaMonitorStatusChangedFctPtr[LusStartIdx](EventId);
          }
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        }
      }
    }
  }

  /* @Trace: SWS_Dem_01281
   * If the parameter DemGeneralCallbackMonitorStatusChangedFnc is
   * configured, the Dem shall call this configured C function with the
   * signature of <Module>_DemTriggerOnMonitorStatus. */
  /* @Trace: Dem_SUD_API_11432 */
  #if (DEM_GENERAL_INTERFACE_SUPPORT == STD_ON)
  /* @Trace: Dem_SUD_API_11434 */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
  if (NULL_PTR != Dem_GeneralCBMonitorStatusChangedFctPtr)
  {
    /* @Trace: Dem_SUD_API_10815 */
    (void)(*Dem_GeneralCBMonitorStatusChangedFctPtr)(EventId);
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  #endif
}
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/





