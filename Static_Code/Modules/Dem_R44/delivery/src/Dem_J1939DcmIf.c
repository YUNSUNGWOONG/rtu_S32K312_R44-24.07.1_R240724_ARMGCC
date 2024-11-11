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
**  SRC-MODULE: Dem_J1939DcmIf.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of Dcm interface functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.6.0   21-Oct-2022   LanhLT        #CP44-853                            **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
  
/* 
   polyspace:begin<MISRA-C:5.1:Not a defect:Justify with annotations>
   Number of character is AUTOSAR standard
   polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
   Not a defect
   polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations>
   Not a defect
   polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations>
   Not a defect
*/
  

#include "Dem.h"                /* DEM module Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Header File */
#endif
#include "SchM_Dem.h"      /* Basic s/w module Scheduler symbols Header File */

#include "Dem_Types.h"
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#include "Dem_EventRelatedData.h"
#include "Dem_Dcm.h"
#if (DEM_J1939_SUPPORT == STD_ON)
#include "Dem_J1939Types.h"
#include "Dem_J1939Ram.h"
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" 

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
static VAR(Dem_J1939DTCFilterStateType, DEM_VAR)
Dem_J1939DTCFilterState[DEM_NUMBER_OF_DEM_CLIENT];
#endif

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static FUNC(void, DEM_CODE) Dem_J1939CountAndStoreFilterDtc(uint8 ClientId);

#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
 ** Function Name       : Dem_J1939CountAndStoreFilterDtc                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Counts and store the filtered dtc as per request by **
 **                       Dcm                                                 **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : ClientId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: Dem_SUD_MACRO_020 */
static FUNC(void, DEM_CODE) Dem_J1939CountAndStoreFilterDtc(uint8 ClientId)
{
  /* @Trace: Dem_SUD_API_00276 */
  #if (DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)

  Dem_NumOfDTCValueType LddDtcLoc = DEM_ZERO;
  boolean LblMilOn = DEM_FALSE;

  /* Loop can be cancelled by Dem_DcmCancelOperation (done
   * DEM_JOB_RUNNING->DEM_JOB_CANCEL)*/
  /* @Trace: Dem_SUD_API_00265 */
  for (LddDtcLoc = DEM_ZERO;
      (LddDtcLoc < DEM_MAX_NUMBER_OF_DTC) &&
          (Dem_J1939DTCFilterState[ClientId].j1939_JobAction == DEM_JOB_RUNNING);
       LddDtcLoc++)
  {
    P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) LddCbDTC =
        &Dem_GaaCombinedDtc[LddDtcLoc];
    Dem_EventIdType LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
    Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition always evaluates to true. Avoid to 'Unreachable code' of
     * the polyspace */
    /* @Trace: Dem_SUD_API_00287 */
    if ((DEM_NO_DTC != LddCbDTC->J1939DTCValue) &&
        (DEM_NO_EVENT != LddEventId) &&
        (Dem_J1939DTCFilterState[ClientId].j1939_DTCOrigin ==
            LddEvent->aaEventDestination))
    {
    	/* @Trace: Dem_SUD_API_00290 */
      #if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
      /* Refer to Dem_SetDTCSuppression */
      /* @Trace: Dem_SUD_API_00289 */
      if (DEM_FALSE ==
            Dem_EvIsProcStateTriggered(LddEventId, DEM_EVPROCSTATE_DTC_SUPP))
      #endif
      {
        /* @Trace: Dem_SUD_API_00291 */
        Dem_UdsStatusByteType LddDtcStatusByte = Dem_GetDTCStatus(LddEventId);
        /* @Trace: Dem_SUD_API_00292 */
        if ((LddCbDTC->ddDtcKind ==
               Dem_J1939DTCFilterState[ClientId].j1939_DTCKind) ||
            (DEM_DTC_KIND_ALL_DTCS ==
               Dem_J1939DTCFilterState[ClientId].j1939_DTCKind))
        {
          /* DM01 , DM12(OBD) Active DTC */
          if (DEM_J1939DTC_ACTIVE ==
                Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
          {
            /* @Trace: Dem_SUD_API_00294 */
            if (DEM_NO_INDATT_IDX !=
                  Dem_Event[LddEventId-DEM_ONE].e_PointToIndicator)
            {
              /* @Trace: Dem_SUD_API_00266 */
              /* @Trace: Dem_SUD_MACRO_034 */
              if (DEM_MIL_INDICATORID ==
                    Dem_GaaIndicatorList
                      [Dem_Event[LddEventId - DEM_ONE].e_PointToIndicator].
                        IndicatorIdRef)
              {
                /* @Trace: Dem_SUD_API_00267 */
                LblMilOn =
                    Dem_EvMem_GetIndicatorAttStatus(
                        LddEventId,
                        Dem_GaaIndicatorList[Dem_Event[LddEventId - DEM_ONE].
                                             e_PointToIndicator].
                                               IndicatorAttStatusPos);
              }
            }
            if (((LddDtcStatusByte &
                 ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |
                     (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC)) ==
                         ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |
                    (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC)) ||
                (LblMilOn == DEM_TRUE))
            {
              Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
            }
            else
            {
              /* @Trace: Dem_SUD_API_00268 */
              /* @Trace: Dem_SUD_API_00269 */
              if (DEM_ZERO !=
                    (LddDtcStatusByte &
                     (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF))
              {
                /* @Trace: Dem_SUD_API_00270 */
                Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
                Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
              }
            }
            
          }
          /* DM02 , DM23(OBD) */
          else if (DEM_J1939DTC_PREVIOUSLY_ACTIVE ==
                     Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
          {
            /* @Trace: Dem_SUD_API_00293 */
            /* @Trace: Dem_SUD_API_00275 */
            if (DEM_NUMBER_OF_INDICATORS >
                  Dem_Event[LddEventId - DEM_ONE].e_PointToIndicator)
            {
              /* @Trace: Dem_SUD_API_00277 */
              if (DEM_MIL_INDICATORID ==
                    Dem_GaaIndicatorList
                      [Dem_Event[LddEventId - DEM_ONE].e_PointToIndicator].
                        IndicatorIdRef)
              {
                /* @Trace: Dem_SUD_API_00278 */
                LblMilOn = Dem_EvMem_GetIndicatorAttStatus(
                    LddEventId,
                    Dem_GaaIndicatorList
                      [Dem_Event[LddEventId - DEM_ONE].e_PointToIndicator].
                        IndicatorAttStatusPos);
              }
            }
            /* @Trace: Dem_SUD_API_00271 */
            if (((LddDtcStatusByte & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |
                (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC)) ==
                    (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) &&
                (LblMilOn == DEM_FALSE))
            {
              /* @Trace: Dem_SUD_API_00025 */
              Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
            }
          }
          /* DM27, DM6(OBD) */
          else if (DEM_J1939DTC_PENDING ==
                     Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
          {
            /* @Trace: Dem_SUD_API_00274 */
            /* @Trace: Dem_SUD_API_00279 */
            if ((LddDtcStatusByte &
                (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) ==
                    (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC)
            {
              /* @Trace: Dem_SUD_API_00280 */
              Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
            }
          }
          /* DM28(OBD) */
          else if (DEM_J1939DTC_PERMANENT ==
                     Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
          { 
            /* @Trace: Dem_SUD_API_00281 */
            /* @Trace: Dem_SUD_API_00283 */
            #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                 (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
            /* @Trace: Dem_SUD_API_00282 */
            if (DEM_NO_EVMEM_ENTRY != Dem_EvMem_FindPerMemLoc(LddEventId))
            {
              /* @Trace: Dem_SUD_API_00285 */
              Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
            }
            #endif
          } 
          /* DM35 */
          else if (DEM_J1939DTC_CURRENTLY_ACTIVE ==
                     Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
          {
            /* @Trace: Dem_SUD_API_00284 */
            /* @Trace: Dem_SUD_API_00286 */
            if ((LddDtcStatusByte & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) ==
                (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF)
            {
              /* @Trace: Dem_SUD_API_00035 */
              Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
            }
          }

          else
          {
            /* @Trace: Dem_SUD_API_00288 */
            /* Nothing to do */
          }
        }
      }
    }
  }
  #endif

  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * if-condition will evaluate to false if Dem_DcmCancelOperation is called by
   * Dcm */
  /* @Trace: Dem_SUD_API_00273 */
  if (DEM_JOB_RUNNING == Dem_J1939DTCFilterState[ClientId].j1939_JobAction)
  {
    /* @Trace: Dem_SUD_API_00272 */
    Dem_J1939DTCFilterState[ClientId].j1939_JobAction = DEM_JOB_DONE;
  }
  SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
}

/*******************************************************************************
 ** Function Name       : Dem_J1939StoreFilterFreezeFrame                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Store the filtered Freeze Frame as per request by   **
 **                       Dcm                                                 **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : ClientId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
/* @Trace: SRS_Diag_04112 SRS_Diag_04220
 */
/* @Trace: Dem_SUD_MACRO_053 */
static FUNC(void, DEM_CODE) Dem_J1939StoreFilterFreezeFrame(uint8 ClientId)
{
  if (DEM_JOB_RUNNING == Dem_FilteredFFRecord[ClientId].j1939FF_JobAction)
  {
    /* @Trace: Dem_SUD_API_00317 */
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
        ((DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO) || \
         (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > DEM_ZERO)))
    Dem_EventIdType LddEvId;
    Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_ZERO;
    /* @Trace: Dem_SUD_API_00328 */
    for (LddEvId = DEM_ONE; LddEvId <= DEM_NUMBER_OF_EVENTS; LddEvId++)
    {
      /* @Trace: Dem_SUD_API_00330 */
      Dem_EvClearProcState(LddEvId, DEM_EVPROCSTATE_J1939DTC_FILTER);
      Dem_EvClearProcState(LddEvId, DEM_EVPROCSTATE_J1939EXFF_FILTER);
    }

    Dem_FilteredFFRecord[ClientId].nextEvent = DEM_NO_EVENT;
    /* @Trace: Dem_SUD_API_00331 */
    for (LddMemLoc = DEM_ZERO;
         LddMemLoc < Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PRIMARY_MEMORY];
         LddMemLoc++)
    {
      LddEvId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY,
          LddMemLoc);
      /* if (DEM_TRUE == Dem_EventIdIsValid(LddEvId)) */
      /* @Trace: Dem_SUD_API_00332 */
      if ((LddEvId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != LddEvId))
      {
        P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
            Dem_GetCbDTCByEventId(LddEvId);
        /* @Trace: Dem_SUD_API_00333 */
        if (NULL_PTR != LddCbDTC)
        {
          /* Filtering according to  expected DTCformat */
          /* @Trace: Dem_SUD_API_00334 */
          if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_J1939,
              LddCbDTC))
          {
            Dem_EventParameterPCType LddEvent = &Dem_Event[LddEvId - DEM_ONE];
            /* @Trace: Dem_SUD_API_00335 */
            if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
            {
              if (DEM_J1939DCM_FREEZEFRAME ==
                    Dem_FilteredFFRecord[ClientId].kindOfJ1939FreezeFrame)
              {
                /* @Trace: Dem_SUD_API_00308 */
                if (Dem_EventRelatedData[LddEvent->e_PointToData].
                    J1939FFClassPos < Dem_Num_Of_J1939FreezeFrameClass)
                {
                  Dem_EvSetProcState(LddEvId, DEM_EVPROCSTATE_J1939DTC_FILTER);
                  /* @Trace: Dem_SUD_API_00313 */
                  if (DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent)
                  {
                    /* @Trace: Dem_SUD_API_00312 */
                    Dem_FilteredFFRecord[ClientId].nextEvent = LddEvId;
                  }
                }
              }
              else if (Dem_EventRelatedData[LddEvent->e_PointToData].
                  J1939EXFFClassPos < Dem_Num_Of_J1939FreezeFrameClass)
              {
                /* @Trace: Dem_SUD_API_00307 */
                Dem_EvSetProcState(LddEvId, DEM_EVPROCSTATE_J1939EXFF_FILTER);
                /* @Trace: Dem_SUD_API_00310 */
                if (DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent)
                {
                  /* @Trace: Dem_SUD_API_00311 */
                  Dem_FilteredFFRecord[ClientId].nextEvent = LddEvId;
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_00309 */
                /* Nothing to do */
              }
            }

          }
        }
      }
    }
    #endif
  }
  else if (DEM_JOB_RUNNING == Dem_FilteredFFRecord[ClientId].
      j1939Ratio_JobAction)
  {
    /* @Trace: Dem_SUD_API_00306 */
    /* @Trace: Dem_SUD_API_00323 */
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
    Dem_EventIdType LddEvId;
    uint8 LucRatioIndex;

    for (LddEvId = DEM_ONE; LddEvId <= DEM_NUMBER_OF_EVENTS; LddEvId++)
    {
    	/* @Trace: Dem_SUD_API_00322 */
       Dem_EvClearProcState(LddEvId, DEM_EVPROCSTATE_J1939DTC_FILTER);
    }
    /* @Trace: Dem_SUD_API_00321 */
    Dem_FilteredFFRecord[ClientId].nextEvent = DEM_NO_EVENT;
    Dem_J1939NextRatioIndex = DEM_ZERO;
    /* @Trace: Dem_SUD_API_00320 */
    for (LucRatioIndex = DEM_ZERO;
         LucRatioIndex < DEM_NUMBER_OF_RATIO_INFO;
         LucRatioIndex++)
    {
      LddEvId = Dem_GaaRatioIdInfo[LucRatioIndex].rid_EventId;
      /* @Trace: SWS_Dem_01101
       * A suppressed DTC shall not be visible for the following Dcm query-
       * functions; therefore the following functions shall treat the DTC as if
       * filter is not matching.
       * */
      /* @Trace: Dem_SUD_API_00319 */
      if (DEM_TRUE != Dem_EvIsProcStateTriggered(LddEvId,
          DEM_EVPROCSTATE_DTC_SUPP))
      {
        P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
            Dem_GetCbDTCByEventId(LddEvId);
        /* @Trace: Dem_SUD_API_00318 */
        if (NULL_PTR != LddCbDTC)
        {
          /* Filtering according to  expected DTCformat */
          /* @Trace: SWS_Dem_00912
           * The function Dem_J1939DcmSetRatioFilter shall reset an internal
           * counter to the first valid SPN with DemRatioId defined to be used
           * for the subsequent calls of Dem_J1939DcmGetNextFilteredRatio.
           * Furthermore, it shall return the "Ignition Cycle Counter" according
           * SAEJ193973 chapter 5.7.20.1, as well as "OBD Monitoring Conditions
           * Encountered" according SAEJ193973 chapter 5.7.20.2 (CARB defines
           * this as the general denominator).
           */
          /* @Trace: Dem_SUD_API_00316 */
          if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_J1939,
              LddCbDTC))
          {
            Dem_EvSetProcState(LddEvId, DEM_EVPROCSTATE_J1939DTC_FILTER);
            /* @Trace: Dem_SUD_API_00315 */
            if ((DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent) ||
                (LddEvId < Dem_FilteredFFRecord[ClientId].nextEvent) )
            {
              /* @Trace: Dem_SUD_API_00314 */
              Dem_FilteredFFRecord[ClientId].nextEvent = LddEvId;
            }
          }
        }
      }
    }
    #endif
  }
  else
  {
    /* @Trace: Dem_SUD_API_00324 */
    /* Nothing to do */
  }

  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * if-condition will evaluate to false if Dem_DcmCancelOperation is called by
   * Dcm */
  if (DEM_JOB_RUNNING == Dem_FilteredFFRecord[ClientId].j1939FF_JobAction)
  {
    /* @Trace: Dem_SUD_API_00325 */
    Dem_FilteredFFRecord[ClientId].j1939FF_JobAction = DEM_JOB_DONE;
  }
  else if (DEM_JOB_RUNNING ==
      Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction)
  {
    /* @Trace: Dem_SUD_API_00326 */
    /* @Trace: Dem_SUD_API_00327 */
    Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction = DEM_JOB_DONE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_00329 */
    /* Nothing to do */
  }
  SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
}

/*******************************************************************************
** Function Name        : Dem_J1939MainFunction                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Main function handling for J1939                    **
**                                                                            **
** Timing:              : FIXED_CYCLIC                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GblMilStarted                                   **
**                        Dem_GulTimeSinceMilOn                               **
**                        Dem_GulDemTimeObdmsCount                            **
**                        Dem_GucMilonFlag                                    **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GulDemClearTimeCount                            **
**                        Dem_GulDemTimeObdSecCount                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        Dem_ProcessDebounceTimer                            **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_054 */
FUNC(void, DEM_CODE) Dem_J1939MainFunction(uint8 ClientId)
{
  /* Apply the filter mask and get the number of filtered DTC */
  /* @Trace: Dem_SUD_API_00262 */
  if (Dem_J1939DTCFilterState[ClientId].j1939_JobAction == DEM_JOB_TRIGGER)
  {
    /* @Trace: Dem_SUD_API_00019 */
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    Dem_J1939DTCFilterState[ClientId].j1939_JobAction = DEM_JOB_RUNNING;
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION(); 
    Dem_J1939CountAndStoreFilterDtc(ClientId);
  }
  /* @Trace: Dem_SUD_API_00263 */
  if (Dem_FilteredFFRecord[ClientId].j1939FF_JobAction == DEM_JOB_TRIGGER)
  {
   /* @Trace: Dem_SUD_API_00020 */
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    Dem_FilteredFFRecord[ClientId].j1939FF_JobAction = DEM_JOB_RUNNING;
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
    Dem_J1939StoreFilterFreezeFrame(ClientId);
  }
  /* @Trace: Dem_SUD_API_00264 */
  if (Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction == DEM_JOB_TRIGGER)
  {
    /* @Trace: Dem_SUD_API_00021 */
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction = DEM_JOB_RUNNING;
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
    Dem_J1939StoreFilterFreezeFrame(ClientId);
  }
}

/*******************************************************************************
** Function Name        : Dem_J1939DcmSetDTCFilter                            **
**                                                                            **
** Service ID           : 0x90                                                **
**                                                                            **
** Description          : The function sets the DTC filter for a specific node**
**                        and returns the composite lamp status of the        **
**                        filtered DTCs.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input parameter      : DTCStatusFilter                                     **
**                         The following types are available:                 **
**                         DEM_J1939DTC_ACTIVE                                **
**                         DEM_J1939DTC_PREVIOUSLY_ACTIVE                     **
**                         DEM_J1939DTC_PENDING                               **
**                         DEM_J1939DTC_PERMANENT                             **
**                         DEM_J1939DTC_CURRENTLY_ACTIVE                      **
**                                                                            **
**                        DTCKind                                             **
**                         Defines the functional group of DTCs to be reported**
**                         (e.g. all DTC, OBD-relevant DTC)                   **
**                                                                            **
**                        uint8 ClientId                                      **
**                                                                            **
** Output Parameters    : LampStatus                                          **
**                         E_OK                                               **
**                         DEM_NO_SUCH_ELEMENT                                **
**                         DEM_PENDING                                        **
**                         DEM_BUFFER_TOO_SMALL                               **
** Return parameter     : Std_ReturnType                                      **
**                         E_OK                                               **
**                         E_NOT_OK                                           **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04069 SRS_Diag_04110 SRS_Diag_04112 SRS_Diag_04164
 */
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetDTCFilter(
  Dem_J1939DcmDTCStatusFilterType DTCStatusFilter,
  Dem_DTCKindType DTCKind,
  Dem_DTCOriginType DTCOrigin,
  uint8 ClientId,
  Dem_J1939DcmLampStatusType* LampStatus)  
{
  /* @Trace: SWS_Dem_00970 */
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;
  
  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_00114 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_UNINIT);
    /*LddRetVal =  DEM_NO_SUCH_ELEMENT;*/
  }
  /* LampStatus check */
  else if (NULL_PTR == LampStatus)
  {
    /* @Trace: Dem_SUD_API_00115 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_PARAM_POINTER);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  /* DTCKind check */
  else if (
    (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
    (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS))
  {
    /* @Trace: Dem_SUD_API_00116 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_PARAM_DATA);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  /* FilterwithSeverity input is not defined */
  else if (
    (DEM_J1939DTC_ACTIVE != DTCStatusFilter) &&
    (DEM_J1939DTC_PREVIOUSLY_ACTIVE != DTCStatusFilter) &&
    (DEM_J1939DTC_PENDING != DTCStatusFilter) &&
    (DEM_J1939DTC_PERMANENT != DTCStatusFilter) &&
    (DEM_J1939DTC_CURRENTLY_ACTIVE != DTCStatusFilter))
  {
    /* @Trace: Dem_SUD_API_00117 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_PARAM_DATA);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  /* @Trace: Dem_SUD_MACRO_146 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00118 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #endif
  else  /* node : N/A */
  {
    /*----------------------+-------------------------+-----------------+-------------------------+
     |  SetFilter Parameter |  DTC Status filter      | further filter  | DM representation       |
     |                      |                         | criteria        +---------+---------------+
     |                      |                         |                 |All DTCs | EmissionsDTCs |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_ACTIVE  | (ConfirmedDTC == 1      | n/a             |DM01     |DM12           |
     |                      | AND TestFailed == 1) OR |                 |         |               |
     |                      | MIL_ON                  |                 |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_        | ConfirmedDTC == 1 AND   | n/a             |DM02     |DM23           |
     | PREVIOUSLY_ACTIVE    | TestFailed == 0 AND     |                 |         |               |
     |                      | MIL_OFF                 |                 |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_PENDING | PendingDTC == 1         | n/a             |DM27     |DM06           |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_        | n/a                     | permanent       |n/a      |DM28           |
     | PERMANENT            |                         | memory          |         |               |
     |                      |                         | entry           |         |               |
     |                      |                         | available       |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC         | TestFailed == 1         | n/a             |DM35     |n/a            |   
     |  _CURRENTLY_ACTIVE   |                         |                 |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+*/

    /* lamp Status 
     Unavailable / Do Not Flash (0x03) 
     Slow Flash (0x00)
     Fast Flash (0x01) 
    */

    /* @Trace: SWS_Dem_00856
     * The filter mask attributes set via Dem_J1939DcmSetDTCFilter shall be used
     * until the next call of Dem_J1939DcmSetDTCFilter or Dem initialization.
     */
    VAR(Dem_J1939LampType, DEM_VAR) LddJ1939LampId;
    Dem_EventIdType LddEventId;
    boolean LblMIL = DEM_J1939LAMP_OFF;
    boolean LblRedStopLamp = DEM_J1939LAMP_OFF;
    boolean LblWarningLamp = DEM_J1939LAMP_OFF;
    boolean LblProtectLamp = DEM_J1939LAMP_OFF;

    Dem_IndicatorStatusType LddMILStatus = DEM_INDICATOR_OFF;
    Dem_IndicatorStatusType LddRedStopLampStatus = DEM_INDICATOR_OFF;
    Dem_IndicatorStatusType LddWarningLampStatus = DEM_INDICATOR_OFF;
    Dem_IndicatorStatusType LddProtectLampStatus = DEM_INDICATOR_OFF;

    LddJ1939LampId.MilId =
        Dem_EvMem_GetMILIndicator(Dem_Client[ClientId].usDemEventMemorySetId);
    LddJ1939LampId.RedStopLampId =
        Dem_EvMem_GetDemRedStopLampIndicatorRef(
            Dem_Client[ClientId].usDemEventMemorySetId);
    LddJ1939LampId.WarningLampId =
        Dem_EvMem_GetDemAmberWarningLampIndicatorRef(
            Dem_Client[ClientId].usDemEventMemorySetId);
    LddJ1939LampId.ProtectLampId =
        Dem_EvMem_GetDemProtectLampIndicatorRef(
            Dem_Client[ClientId].usDemEventMemorySetId);
    /* @Trace: Dem_SUD_API_12705 */
    for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
    {
      /* @Trace: Dem_SUD_API_12694 */
      Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
    }
    /* @Trace: Dem_SUD_API_12709 */
    if (DEM_J1939LAMP_NOT_AVAILABLE != LddJ1939LampId.MilId)
    {
      /* @Trace: Dem_SUD_API_12708 */
      (void)Dem_GetIndicatorStatus((uint8)LddJ1939LampId.MilId, &LddMILStatus);
    }
    /* @Trace: Dem_SUD_API_12710 */
    if (DEM_J1939LAMP_NOT_AVAILABLE != LddJ1939LampId.RedStopLampId)
    {
      /* @Trace: Dem_SUD_API_12711 */
      (void)Dem_GetIndicatorStatus(
          (uint8)LddJ1939LampId.RedStopLampId, &LddRedStopLampStatus);
    }
    /* @Trace: Dem_SUD_API_12712 */
    if (DEM_J1939LAMP_NOT_AVAILABLE != LddJ1939LampId.WarningLampId)
    {
      /* @Trace: Dem_SUD_API_12713 */
      (void)Dem_GetIndicatorStatus(
          (uint8)LddJ1939LampId.WarningLampId, &LddWarningLampStatus);
    }
    /* @Trace: Dem_SUD_API_12714 */
    if (DEM_J1939LAMP_NOT_AVAILABLE != LddJ1939LampId.ProtectLampId)
    {
      /* @Trace: Dem_SUD_API_12695 */
      (void)Dem_GetIndicatorStatus(
          (uint8)LddJ1939LampId.ProtectLampId, &LddProtectLampStatus);
    }

    /*  MIL */
    /* @Trace: SWS_Dem_00858
     * The composite "Malfunction Indicator Lamp" shall be set to "Lamp Off" in
     * case the Indicator referenced by DemMILIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_OFF. All other IndicatorStatus states than
     * "DEM_INDICATOR_OFF" shall set the composite Malfunction Indicator Lamp to
     * "Lamp On".
     */
    /* @Trace: SWS_Dem_00859
     * The composite "Flash Malfunction Indicator Lamp" shall be set to
     * "Unavailable / Do Not Flash" (0x03) in case the Indicator referenced by
     * DemMILIndicatorRef has an IndicatorStatus DEM_INDICATOR_OFF or
     * DEM_INDICATOR_CONTINUOUS.
     */

    /* @Trace: SWS_Dem_00860
     * The composite "Flash Malfunction Indicator Lamp" shall be set to
     * "Slow Flash" (0x00) in case the Indicator referenced by
     * DemMILIndicatorRef has an IndicatorStatus DEM_INDICATOR_SLOW_FLASH.
     */
    if (DEM_INDICATOR_SLOW_FLASH == LddMILStatus)
    {
      /* @Trace: Dem_SUD_API_12696 */
      LddMILStatus = DEM_J1939LAMP_SLOW_FLASH;
      LblMIL = DEM_J1939LAMP_ON;
    }
    /* @Trace: SWS_Dem_00861
     * The composite "Flash Malfunction Indicator Lamp" shall be set to "Fast
     * Flash" (0x01) in case the Indicator referenced by DemMILIndicatorRef has
     * an IndicatorStatus DEM_INDICATOR_FAST_FLASH.
     */
    else if (DEM_INDICATOR_FAST_FLASH == LddMILStatus)
    {
      /* @Trace: Dem_SUD_API_00141 */
      LddMILStatus = DEM_J1939LAMP_FAST_FLASH;
      LblMIL = DEM_J1939LAMP_ON;
    }
    else if (DEM_INDICATOR_CONTINUOUS == LddMILStatus)
    {
      /* @Trace: Dem_SUD_API_12697 */
      LddMILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblMIL = DEM_J1939LAMP_ON;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12698 */
      LddMILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblMIL = DEM_J1939LAMP_OFF;
    }

    /*  Red Stop Lamp */
    /* @Trace: SWS_Dem_00862
     * The composite "Red Stop Lamp" shall be set to "Lamp Off" in case the
     * Indicator referenced by  DemRedStopLampIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_OFF. All other IndicatorStatus states than
     * "DEM_INDICATOR_OFF" shall set the composite Red Stop Lamp to "Lamp On".
     */
    /* @Trace: SWS_Dem_00863
     * The composite "Flash Red Stop Lamp" shall be set to "Unavailable / Do Not
     * Flash" (0x03) in case the Indicator referenced by
     * DemRedStopLampIndicatorRef has an IndicatorStatus DEM_INDICATOR_OFF
     * or DEM_INDICATOR_CONTINUOUS.
     */

    /* @Trace: SWS_Dem_00864
     * The composite "Flash Red Stop Lamp" shall be set to "Slow Flash" (0x00)
     * in case the Indicator referenced by DemRedStopLampIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_SLOW_FLASH.
     */
    if (DEM_INDICATOR_SLOW_FLASH == LddRedStopLampStatus)
    {
      /* @Trace: Dem_SUD_API_00142 */
      LddRedStopLampStatus = DEM_J1939LAMP_SLOW_FLASH;
      LblRedStopLamp = DEM_J1939LAMP_ON;
    }
    /* @Trace: SWS_Dem_00865
     * The composite "Flash Red Stop Lamp" shall be set to "Fast Flash" (0x01)
     * in case the Indicator referenced by DemRedStopLampIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_FAST_FLASH.
     */
    else if (DEM_INDICATOR_FAST_FLASH == LddRedStopLampStatus)
    {
      /* @Trace: Dem_SUD_API_12699 */
      LddRedStopLampStatus = DEM_J1939LAMP_FAST_FLASH;
      LblRedStopLamp = DEM_J1939LAMP_ON;
    }
    else if (DEM_INDICATOR_CONTINUOUS == LddRedStopLampStatus)
    {
      /* @Trace: Dem_SUD_API_00143 */
      LddRedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblRedStopLamp = DEM_J1939LAMP_ON;
    }
    else
    {
      LddRedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblRedStopLamp = DEM_J1939LAMP_OFF;
    }
    /*  Amber Warning Lamp */
    /* @Trace: SWS_Dem_00866
     * The composite "Amber Warning Lamp" shall be set to "Lamp Off" in case
     * the Indicator referenced by DemAmberWarningLampIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_OFF. All other IndicatorStatus states than
     * DEM_INDICATOR_OFF shall set the composite Amber Warning Lamp to "Lamp On".
     */
    /* @Trace: SWS_Dem_00867
     * The composite "Amber Warning Lamp" shall be set to "Unavailable / Do Not
     * Flash" (0x03) in case the Indicator referenced by
     * DemAmberWarningLampIndicatorRef has an IndicatorStatus DEM_INDICATOR_OFF
     * or DEM_INDICATOR_CONTINUOUS
     */
    /* @Trace: SWS_Dem_00868
     * The composite "Flash Amber Warning Lamp" shall be set to "Slow Flash"
     * (0x00) in case the Indicator referenced by
     * DemAmberWarningLampIndicatorRef has an IndicatorStatus
     * DEM_INDICATOR_SLOW_FLASH.
     */
    if (DEM_INDICATOR_SLOW_FLASH == LddWarningLampStatus)
    {
      /* @Trace: Dem_SUD_API_12700 */
      LddWarningLampStatus = DEM_J1939LAMP_SLOW_FLASH;
      LblWarningLamp = DEM_J1939LAMP_ON;
    }
    /* @Trace: SWS_Dem_00869
     * The composite "Flash Amber Warning Lamp" shall be set to "Fast Flash"
     * (0x01) in case the Indicator referenced by
     * DemAmberWarningLampIndicatorRef has an IndicatorStatus
     * DEM_INDICATOR_FAST_FLASH.
     */
    else if (DEM_INDICATOR_FAST_FLASH == LddWarningLampStatus)
    {
      /* @Trace: Dem_SUD_API_12701 */
      LddWarningLampStatus = DEM_J1939LAMP_FAST_FLASH;
      LblWarningLamp = DEM_J1939LAMP_ON;
    }
    else if (DEM_INDICATOR_CONTINUOUS == LddWarningLampStatus)
    {
      /* @Trace: Dem_SUD_API_00144 */
      LddWarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblWarningLamp = DEM_J1939LAMP_ON;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12702 */
      LddWarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblWarningLamp = DEM_J1939LAMP_OFF;
    }
    /*   Protect Lamp */
    /* @Trace: SWS_Dem_00870
     * The composite "Protect Lamp" shall be set to "Lamp Off" in case the
     * Indicator referenced by DemProtectLampIndicatorRef has an IndicatorStatus
     * DEM_INDICATOR_OFF. All other IndicatorStatus states than
     * DEM_INDICATOR_OFF shall set the composite Protect Lamp to "Lamp On".
     */
    /* @Trace: SWS_Dem_00871
     * The composite "Flash Protect Lamp" shall be set to "Unavailable / Do Not
     * Flash" (0x03) in case the Indicator referenced by
     * DemProtectLampIndicatorRef has an IndicatorStatus DEM_INDICATOR_OFF
     * or DEM_INDICATOR_CONTINUOUS.
     */
    /* @Trace: SWS_Dem_00872
     * The composite "Flash Protect Lamp" shall be set to "Slow Flash" (0x00)
     * in case the Indicator  referenced by DemProtectLampIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_SLOW_FLASH.
     */
    if (DEM_INDICATOR_SLOW_FLASH == LddProtectLampStatus)
    {
      /* @Trace: Dem_SUD_API_12703 */
      LddProtectLampStatus = DEM_J1939LAMP_SLOW_FLASH;
      LblProtectLamp = DEM_J1939LAMP_ON;
    }
    /* @Trace: SWS_Dem_00873
     * The composite "Flash Protect Lamp" shall be set to "Fast Flash" (0x01)
     * in case the Indicator referenced by DemProtectLampIndicatorRef has an
     * IndicatorStatus DEM_INDICATOR_FAST_FLASH.
     */
    else if (DEM_INDICATOR_FAST_FLASH == LddProtectLampStatus)
    {
      /* @Trace: Dem_SUD_API_12704 */
      LddProtectLampStatus = DEM_J1939LAMP_FAST_FLASH;
      LblProtectLamp = DEM_J1939LAMP_ON;
    }
    else if (DEM_INDICATOR_CONTINUOUS == LddProtectLampStatus)
    {
      /* @Trace: Dem_SUD_API_12706 */
      LddProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblProtectLamp = DEM_J1939LAMP_ON;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12707 */
      LddProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      LblProtectLamp = DEM_J1939LAMP_OFF;
    }

    /* @Trace: SWS_Dem_00857
     * The function Dem_J1939DcmSetDTCFilter shall return the current composite
     * status of the J1939 lamps. The matching filter citreria are defined in
     * Table 7.6.
     */
    LampStatus->LampStatus = (
    /* Flash Malfunction Indicator Lamp */
    (uint8)((uint8)LblMIL <<  (uint8)(BIT_POS_6)) |
    /* Flash Red Stop Lamp */
    (uint8)((uint8)LblRedStopLamp  <<  (uint8)(BIT_POS_4)) |
    /* Flash Amber Warning Lamp */
    (uint8)((uint8)LblWarningLamp  <<  (uint8)(BIT_POS_2)) |
    /* Flash Protect Lamp */
    (uint8)((uint8)LblProtectLamp  <<  (uint8)(BIT_POS_0)));

    LampStatus->FlashLampStatus = (
    /* Flash Malfunction Indicator Lamp Status */
    (uint8)((uint8)LddMILStatus <<  (uint8)(BIT_POS_6)) |
    /* Flash Red Stop Lamp Status */
    (uint8)((uint8)LddRedStopLampStatus   <<  (uint8)(BIT_POS_4)) |
    /* Flash Amber Warning Lamp  Status */
    (uint8)((uint8)LddWarningLampStatus   <<  (uint8)(BIT_POS_2)) |
    /* Flash Protect Lamp Status */
    (uint8)((uint8)LddProtectLampStatus   <<  (uint8)(BIT_POS_0)));

    /* @Trace: SWS_Dem_00855
     * The function Dem_J1939DcmSetDTCFilter shall set the filter mask
     * attributes to be used for the subsequent calls of
     * Dem_J1939DcmGetNumberOfFilteredDTC and Dem_J1939DcmGetNextFilteredDTC,
     * and reset an internal counter to the first event.
     */
    Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter = DTCStatusFilter;
    Dem_J1939DTCFilterState[ClientId].j1939_DTCKind = DTCKind;
    Dem_J1939DTCFilterState[ClientId].j1939_DTCOrigin = DTCOrigin;
    Dem_J1939DTCFilterState[ClientId].j1939_JobAction = DEM_JOB_TRIGGER;
    Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC = DEM_ZERO;

    LddRetVal = E_OK;
  }
  
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNumberOfFilteredDTC                  **
**                                                                            **
** Service ID           : 0x91                                                **
**                                                                            **
** Description          : This API shall be used to get the number of         **
**                        Filtered DTC                                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : uint8 ClientId                                      **
**                                                                            **
** Output Parameters    : uint16* NumberOfFilteredDTC                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                        E_OK                                                **
**                        DEM_NO_SUCH_ELEMENT                                 **
**                        DEM_PENDING                                         **
**                        DEM_BUFFER_TOO_SMALL                                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04112
 */
/* @Trace: Dem_SUD_MACRO_065 */
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNumberOfFilteredDTC(
  uint16* NumberOfFilteredDTC,
  uint8 ClientId)
{
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  /*  Check   module  Initialization  status  */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_00091 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNUMBEROFFILTEREDDTC_SID, DEM_E_UNINIT);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else if (NumberOfFilteredDTC == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_00092 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNUMBEROFFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00093 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNUMBEROFFILTEREDDTC_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #endif
  else
  {
    *NumberOfFilteredDTC = DEM_ZERO;
    /* DEM_JOB_TRIGGER: by Dem_SetFreezeFrameRecordFilter
     * DEM_JOB_RUNNING: by Dem_MainFunction
     * DEM_JOB_DONE:    after job is finished by Dem_MainFunction
     */
    if ((DEM_JOB_TRIGGER ==
           Dem_J1939DTCFilterState[ClientId].j1939_JobAction) ||
        (DEM_JOB_RUNNING == Dem_J1939DTCFilterState[ClientId].j1939_JobAction))
    {    
      /* @Trace: Dem_SUD_API_12715 */
      /* Return appropriate value */
      LddRetVal = DEM_PENDING;
    }
    else if (DEM_JOB_DONE == Dem_J1939DTCFilterState[ClientId].j1939_JobAction)
    {
      /* @Trace: Dem_SUD_API_12716 */
      /* Return the number of filtered DTC's */
      /* @Trace: SWS_Dem_00874
       * The function Dem_J1939DcmGetNumberOfFilteredDTC shall return the number
       * of J1939  DTCs matching the defined filter criteria of Table 7.6 for
       * the corresponding primary event memory of the requested ClientId by the
       * function call of Dem_J1939DcmSetDTCFilter.
       * - In case the function has calculated the total number of matching DTCs
       * , the return value shall be E_OK.
       * - In case the search needs to be interrupted due to internal
       * implementations or limitations, the return value can be set to
       * DEM_PENDING. The out parameter needs not to be valid in this case. The
       * next call of Dem_J1939DcmGetNumberOfFilteredDTC should continue after
       * the interrupted element.
       */
      *NumberOfFilteredDTC =
          Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC;
      LddRetVal = E_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_00146 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
  }   
  return LddRetVal;
}/* End of API */
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmFirstDTCwithLampStatus                  **
**                                                                            **
** Service ID           : 0x93                                                **
**                                                                            **
** Description          : The function set the filter to the first applicable **
**                        DTC for the DM31 response for a specifc node.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input parameter      : ClientId                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04113 SRS_Diag_04220
 */
#if (DEM_J1939_DM31_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_J1939DcmFirstDTCwithLampStatus(uint8 ClientId)
{
  
  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_00094 */
    DEM_REPORT_ERROR(DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_SID, DEM_E_UNINIT);
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00095 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_SID, DEM_E_WRONG_CONFIGURATION);
  }
  #endif
  else  /* node : N/A */
  {
    /* @Trace: Dem_SUD_API_12735 */
    #if (DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
    Dem_NumOfDTCValueType LddDtcLoc = DEM_ZERO;
    Dem_EventIdType LddEventId;
    for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
    {
      /* @Trace: Dem_SUD_API_12736 */
      Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
    }
    /* @Trace: Dem_SUD_API_12737 */
    Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC = DEM_ZERO;
    Dem_J1939FirstDtcLoc[ClientId] = 0xFF;
    /* @Trace: Dem_SUD_API_12738 */
    for (LddDtcLoc = DEM_ZERO; LddDtcLoc < DEM_MAX_NUMBER_OF_DTC ; LddDtcLoc++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) LddCbDTC =
          &Dem_GaaCombinedDtc[LddDtcLoc];
      LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true. Avoid to 'Unreachable code' of
       * the polyspace */
      /* @Trace: Dem_SUD_API_12739 */
      if ((DEM_NO_DTC != LddCbDTC->J1939DTCValue) &&
          (DEM_NO_EVENT != LddEventId))
      {      
        #if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
        /* Refer to Dem_SetDTCSuppression */
        /* @Trace: SWS_Dem_01101
         * A suppressed DTC shall not be visible for the following Dcm query-
         * functions; therefore the following functions shall treat the DTC as
         * if filter is not matching.
         * */
        /* @Trace: Dem_SUD_API_12740 */
        if (DEM_FALSE ==
              Dem_EvIsProcStateTriggered(LddEventId, DEM_EVPROCSTATE_DTC_SUPP))
        #endif
        {
          Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
          Dem_J1939DTCFilterState[ClientId].j1939_NumOfFilteredDTC++;
          /* @Trace: SWS_Dem_00880
           * Each call to Dem_J1939DcmFirstDTCwithLampStatus shall set the
           * internal counter to the first event having a J1939DTC for this
           * particular "ClientId" assiged.
           */
          /* @Trace: Dem_SUD_API_12741 */
          if (0xFFU == Dem_J1939FirstDtcLoc[ClientId])
          {
            /* @Trace: Dem_SUD_API_12742 */
            Dem_J1939FirstDtcLoc[ClientId] = LddDtcLoc;
          }
        }
      }
    }
    #endif
    
    Dem_J1939DTCFilterState[ClientId].j1939_JobAction = DEM_JOB_DONE;
    
  }

}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextFilteredDTC                      **
**                                                                            **
** Service ID           : 0x92                                                **
**                                                                            **
** Description          : This API shall be used to get next Filtered DTC     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* J1939DTC                                    **
**                        uint8*  OccurenceCounter                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                        E_OK                                                **
**                        DEM_NO_SUCH_ELEMENT                                 **
**                        DEM_PENDING                                         **
**                        DEM_BUFFER_TOO_SMALL                                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04111 SRS_Diag_04112 SRS_Diag_04220
 */
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFilteredDTC(
  uint32* J1939DTC,
  uint8* OccurenceCounter,
  uint8 ClientId)
{
  /* @Trace: SWS_Dem_00973 */
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00096 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFILTEREDDTC_SID, DEM_E_UNINIT);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else if ( (NULL_PTR == J1939DTC) || (NULL_PTR == OccurenceCounter))
  {
    /* @Trace: Dem_SUD_API_00097 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00098 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTFILTEREDDTC_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #endif
  else if ((DEM_JOB_TRIGGER ==
              Dem_J1939DTCFilterState[ClientId].j1939_JobAction) ||
           (DEM_JOB_RUNNING ==
               Dem_J1939DTCFilterState[ClientId].j1939_JobAction))
  {    
    /* @Trace: Dem_SUD_API_12717 */
    /* Return appropriate value */
    LddRetVal = DEM_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_J1939DTCFilterState[ClientId].j1939_JobAction)
  {
    /* @Trace: Dem_SUD_API_12727 */
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  } 
  else  
  {
    Dem_NumOfEventMemoryEntryType LddIdxOfEntry = DEM_ZERO;
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(Dem_J1939DTCFilterState[ClientId].
          j1939_DTCOrigin))
    {
      LddIdxOfEntry = Dem_UDEvMemChronoOrderNextLoc;
    }
    else
    #endif
    {
      LddIdxOfEntry = Dem_PriEvMemChronoOrderNextLoc;
    }

    struct {
      Dem_EventIdType LddPrioEventId;
      Dem_EventPriorityType LddPriority;
    } LstHighestEvent = {DEM_ZERO, DEM_ZERO};

    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_12728 */
    if (DEM_J1939DTC_PERMANENT ==
          Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
    {
      /* @Trace: Dem_SUD_API_12729 */
      LddIdxOfEntry = DEM_MAX_NUMBER_EVENT_ENTRY_PER;
    }
    #endif
    
    /* Only DEM_DTC_ORIGIN_PRIMARY_MEMORY */
    /* @Trace: Dem_SUD_API_12730 */
    while (LddIdxOfEntry > DEM_ZERO)
    {
      /* @IF_REQ: SWS_Dem_00411
       * If the Dem module is requested to report in chronological order,
       * the most recent event memory entry shall be reported at first. */
      Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;

      --LddIdxOfEntry;

      #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
           (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
      if (DEM_J1939DTC_PERMANENT ==
            Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
      {
        /* @Trace: Dem_SUD_API_12732 */
        LddMemLoc = LddIdxOfEntry;
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_12731 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
        if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(Dem_J1939DTCFilterState[ClientId].
            j1939_DTCOrigin))
        {
          if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > LddIdxOfEntry)
          {
            LddMemLoc= Dem_UDEvMemChronoOrder[LddIdxOfEntry];
          }
        }
        else
        #endif
        /* @Trace: Dem_SUD_API_12733 */
        /* @Trace: Dem_SUD_MACRO_026 */
        /* polyspace +1 MISRA-C3:15.7 [Justified:Low] Justify with annotations */
        if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddIdxOfEntry)
        {
          LddMemLoc= Dem_PriEvMemChronoOrder[LddIdxOfEntry];
        }
      }
      /* @Trace: Dem_SUD_API_12734 */
      if (DEM_NO_EVMEM_ENTRY != LddMemLoc)
      {
        Dem_EventIdType LddEventId = DEM_NO_EVENT;
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
        if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(Dem_J1939DTCFilterState[ClientId].
            j1939_DTCOrigin))
        {
          LddEventId = Dem_EvMem_GetEventIdByEvMemEntry(
              Dem_J1939DTCFilterState[ClientId].
                j1939_DTCOrigin, LddMemLoc);
        }
        else
        #endif
        {
          LddEventId = Dem_EvMem_GetEventIdByEvMemEntry(
              DEM_DTC_ORIGIN_PRIMARY_MEMORY, LddMemLoc);
        }

        #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
             (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
        /* @Trace: Dem_SUD_API_12718 */
        if (DEM_J1939DTC_PERMANENT ==
              Dem_J1939DTCFilterState[ClientId].j1939_DTCStatusFilter)
        {
          /* @Trace: Dem_SUD_API_12719 */
          LddEventId = Dem_PermanentEventMemory[LddMemLoc].EventIdRef;
        }
        #endif
        /* @Trace: SWS_Dem_00875
         * Each call of the function Dem_J1939DcmGetNextFilteredDTC shall search
         * for the next event having a J1939DTC assigned and matching the filter
         * criteria of Table 7.6 for the node provided by the function call of
         * Dem_J1939DcmSetDTCFilter. In case no more events are matching the
         * filter criteria, the function return value shall be
         * DEM_NO_SUCH_ELEMENT. The out parameters need not to be valid in this
         * case.
         */
        /* @Trace: Dem_SUD_API_12726 */
        if ((DEM_TRUE == Dem_EventIdIsValid(LddEventId)) && (LddEventId != 0))
        {
          P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
              Dem_GetCbDTCByEventId(LddEventId);
          /* @Trace: Dem_SUD_API_12720 */
          if (NULL_PTR != LddCbDTC)
          {
            /* @Trace: Dem_SUD_API_12721 */
            Dem_EventIdType LddFirstEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
            LddEventId = LddFirstEventId;
          }
          /* @Trace: Dem_SUD_API_12722 */
          if ((DEM_TRUE ==
                Dem_EvIsProcStateTriggered(
                    LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER)) && (LddEventId != 0))
          {    
            /* @Trace: Dem_SUD_MACRO_003 */
            #if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
            /* Refer to Dem_SetDTCSuppression */
            /* @Trace: SWS_Dem_01101
             * A suppressed DTC shall not be visible for the following Dcm query
             * -functions; therefore the following functions shall treat the DTC
             * as if filter is not matching.
             * */
            if (DEM_TRUE ==
                  Dem_EvIsProcStateTriggered(
                      LddEventId, DEM_EVPROCSTATE_DTC_SUPP))
            {
              /* @Trace: Dem_SUD_API_00147 */
              Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
            }
            else
            #endif
            {  
              Dem_EventParameterCPCType LddEvent =
                  &Dem_Event[LddEventId - DEM_ONE];
                
              if (DEM_NO_EVENT != LstHighestEvent.LddPrioEventId)
              {
                /* @Trace: Dem_SUD_API_12723 */
                if (LddEvent->ucEventPriority < LstHighestEvent.LddPriority)
                {
                  /* @Trace: Dem_SUD_API_12725 */
                  LstHighestEvent.LddPrioEventId = LddEventId;
                  LstHighestEvent.LddPriority = LddEvent->ucEventPriority;
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_12724 */
                LstHighestEvent.LddPrioEventId = LddEventId;
                LstHighestEvent.LddPriority = LddEvent->ucEventPriority;
              } 
            }
          }
        }
      }  
    }    
    /* @Trace: Dem_SUD_API_13292 */
    if (DEM_NO_EVENT != LstHighestEvent.LddPrioEventId)
    {  
      Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
      /* @Trace: Dem_SUD_API_13294 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(Dem_J1939DTCFilterState[ClientId].
          j1939_DTCOrigin))
      {
        /* @Trace: Dem_SUD_API_13295 */
        LddMemEntry = Dem_EvMem_GetEmEntryByMemPosition(
            Dem_J1939DTCFilterState[ClientId].
              j1939_DTCOrigin,
            Dem_EvMemToEventMap[LstHighestEvent.LddPrioEventId]);
      }
      else
      #endif
      {
       /* @Trace: Dem_SUD_API_13293 */
        LddMemEntry = Dem_EvMem_GetEmEntryByMemPosition(
            DEM_DTC_ORIGIN_PRIMARY_MEMORY,
            Dem_EvMemToEventMap[LstHighestEvent.LddPrioEventId]);
      }
    
      Dem_EvClearProcState(
          LstHighestEvent.LddPrioEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
      /* @Trace: Dem_SUD_API_13296 */
      if (NULL_PTR != LddMemEntry)
      {
        Dem_DTCType LddDtc = DEM_NO_DTC;
        uint16 LddDtcLoc =
            Dem_Event[LstHighestEvent.LddPrioEventId - DEM_ONE].e_PointToDTC;
        /* @Trace: Dem_SUD_API_13297 */
        if (LddDtcLoc < DEM_MAX_NUMBER_OF_DTC)
        {
          LddDtc = Dem_GaaCombinedDtc[LddDtcLoc].J1939DTCValue;
        }
        /* @Trace: Dem_SUD_API_13298 */
        if (DEM_NO_DTC != LddDtc)
        {
          /* @Trace: SWS_Dem_00877
           * In case the function Dem_J1939DcmGetNextFilteredDTC has found an
           * event matching the filter criteria it shall return the
           * corresponding J1939DTC (refer to DemDTCAttributes for details) and
           * the corresponding occurrence counter. The return value shall be
           * E_OK. In case the search needs to be interrupted due to internal
           * implementations or limitations, the return value can be set to
           * DEM_PENDING. The out parameter needs not to be valid in this case.
           * The next call of Dem_J1939DcmGetNextFilteredDTC should continue
           * after the interrupted element. In case the occurrence counter is
           * above +126 (0x7F), the returned values shall be set to +126 (0x7F).
           */
          *J1939DTC = LddDtc;
          *OccurenceCounter = LddMemEntry->EventOccurrenceCounter;
          /* @Trace: Dem_SUD_API_13299 */
          if (*OccurenceCounter > 0x7F)
          {
            /* @Trace: Dem_SUD_API_13300 */
            *OccurenceCounter = 0x7F;
          }                
          LddRetVal = E_OK;
        }
      }
    }
  }
      
  return LddRetVal;
}/* End of API */
#endif

/*******************************************************************************
** Function Name        : Dem_GetJ1939LampStatus                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function shall be used to read the             **
**                        indicator-Status derived from the event status      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                        Dem_J1939DcmLampStatusType  LampStatus              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_IndicatorStatusType* IndicatorStatus            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C:5.6:Not a defect:Justify with annotations>
 * Depends on Dem specfication */

/* @Trace: SRS_Diag_04069 SRS_Diag_04110 SRS_Diag_04164
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetJ1939LampStatus(
  Dem_EventIdType EventId,
  P2VAR (Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA) LampStatus)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  if (LampStatus == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_00295 */
    /* LddRetVal = E_NOT_OK;*/
  }
  else if (EventId < DEM_ONE)
  {
    /* @Trace: Dem_SUD_API_00298 */
    /* LddRetVal = E_NOT_OK;*/
  }
  else
  {
    /* @Trace: Dem_SUD_API_00036 */
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR) LddIndicator;
    Dem_NumOfIndicatorAttributeType LddMax =
        LddEvent->e_PointToIndicator +
        LddEvent->ucNumberofIndicator;
    Dem_NumOfIndicatorAttributeType LddIdx;
    boolean LblIndicatorAttributeStatus;
    /* @Trace: Dem_SUD_API_00299 */
    if (LddMax <= DEM_NUMBER_OF_INDICATORS)
    {
      /* @Trace: Dem_SUD_API_30000 */
      VAR(Dem_J1939LampType, DEM_VAR) LddJ1939LampId;
      boolean LblMIL = DEM_J1939LAMP_OFF;
      boolean LblRedStopLamp = DEM_J1939LAMP_OFF;
      boolean LblWarningLamp = DEM_J1939LAMP_OFF;
      boolean LblProtectLamp = DEM_J1939LAMP_OFF;

      Dem_IndicatorStatusType LddMILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      Dem_IndicatorStatusType LddRedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      Dem_IndicatorStatusType LddWarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      Dem_IndicatorStatusType LddProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;

      LddJ1939LampId.MilId =
          Dem_EvMem_GetMILIndicator(LddEvent->ucEventMemDstIdx);
      LddJ1939LampId.RedStopLampId =
          Dem_EvMem_GetDemRedStopLampIndicatorRef(LddEvent->ucEventMemDstIdx);
      LddJ1939LampId.WarningLampId =
          Dem_EvMem_GetDemAmberWarningLampIndicatorRef(
              LddEvent->ucEventMemDstIdx);
      LddJ1939LampId.ProtectLampId =
          Dem_EvMem_GetDemProtectLampIndicatorRef(LddEvent->ucEventMemDstIdx);
      /* @Trace: Dem_SUD_API_00056 */
      for (LddIdx = LddEvent->e_PointToIndicator; LddIdx < LddMax ; LddIdx++)
      {
        /* @Trace: Dem_SUD_API_00037 */
        LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
        LblIndicatorAttributeStatus =
            Dem_EvMem_GetIndicatorAttStatus(
                LddIndicator->EventIdRef, LddIndicator->IndicatorAttStatusPos);
        /* @Trace: Dem_SUD_API_00300 */
        if (LddJ1939LampId.MilId == LddIndicator->IndicatorIdRef)
        {
          /* @Trace: SWS_Dem_00883
           * The DTCspecific "Malfunction Indicator Lamp" returned in the
           * function Dem_J1939DcmGetNextDTCwithLampStatus shall be set to "Lamp
           * On" in case the corresponding event has assigned the Indicator
           * referenced by DemMILIndicatorRef and the UDS status bit 7
           * (WarningIndicator) is active (set to 1), otherwise it shall be set
           * to "Lamp Off".
           */
        	/* @Trace: Dem_SUD_API_00038 */
          LblMIL = LblIndicatorAttributeStatus;
          /* @Trace: Dem_SUD_API_00301 */
          if (DEM_J1939LAMP_ON == LblMIL)
          {
            /* @Trace: SWS_Dem_00885
             * The DTC-specific "Flash Malfunction Indicator Lamp" shall be set
             * to "Slow Flash" (0x00) in case the corresponding event has set
             * "Lamp On" and the DemIndicatorBehaviour of the Indicator
             * referenced by DemMILIndicatorRef is set to
             * DEM_INDICATOR_SLOW_FLASH.
             */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
             if (DEM_INDICATOR_SLOW_FLASH == LddIndicator->Behavior)
             {
               /* @Trace: Dem_SUD_API_00039 */
               LddMILStatus = DEM_J1939LAMP_SLOW_FLASH;
             }
             /* @Trace: SWS_Dem_00886
              * The DTC-specific "Flash Malfunction Indicator Lamp" shall be set
              * to "Fast Flash" (0x01) in case the corresponding event has set
              * "Lamp On" and the DemIndicatorBehaviour of the Indicator
              * referenced by DemMILIndicatorRef is set to
              * DEM_INDICATOR_FAST_FLASH.
              */
             else if (DEM_INDICATOR_FAST_FLASH == LddIndicator->Behavior)
             {
               /* @Trace: Dem_SUD_API_00040 */
               LddMILStatus = DEM_J1939LAMP_FAST_FLASH;
             }
             /* @Trace: SWS_Dem_00884
              * The DTC-specific "Flash Malfunction Indicator Lamp" shall be set
              * to "Unavailable / Do Not Flash" (0x03) in case the corresponding
              * event has set "Lamp On" and the DemIndicatorBehaviour of the
              * Indicator referenced by DemMILIndicatorRef is set to
              * DEM_INDICATOR_CONTINUOUS.
              */
            else
            {
              /* @Trace: Dem_SUD_API_00041 */
              LddMILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
          }
        }
        /* @Trace: Dem_SUD_API_00302 */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
        if (LddJ1939LampId.RedStopLampId == LddIndicator->IndicatorIdRef)
        {
          /* @Trace: SWS_Dem_00887
           * The DTC-specific "Red Stop Lamp" returned in the function
           * Dem_J1939DcmGetNextDTCwithLampStatus shall be set to "Lamp On" in
           * case the corresponding event has assigned the Indicator referenced
           * by DemRedStopIndicatorRef and the UDS status bit 7
           * (WarningIndicator) is active (set to 1), otherwise it shall be set
           * to "Lamp Off".
           */
          /* @Trace: Dem_SUD_API_00042 */
          LblRedStopLamp = LblIndicatorAttributeStatus;
          /* @Trace: Dem_SUD_API_00303 */
          if (DEM_J1939LAMP_ON == LblRedStopLamp)
          {
            /* @Trace: SWS_Dem_00889
             * The DTC-specific "Flash Red Stop Lamp" shall be set to "Slow
             * Flash" (0x00) in case the corresponding event has set "Lamp On"
             * and the DemIndicatorBehaviour of the Indicator referenced by
             * DemRedStopIndicatorRef is set to DEM_INDICATOR_SLOW_FLASH.
             */
            if (DEM_INDICATOR_SLOW_FLASH == LddIndicator->Behavior)
            {
              /* @Trace: Dem_SUD_API_00043 */
              LddRedStopLampStatus = DEM_J1939LAMP_SLOW_FLASH;
            }
            /* @Trace: SWS_Dem_00890
             * The DTC-specific "Flash Red Stop Lamp" shall be set to "Fast
             * Flash" (0x01) in case the corresponding event  has set "Lamp On"
             * and the DemIndicatorBehaviour of the Indicator referenced by
             * DemRedStopIndicatorRef is set to DEM_INDICATOR_FAST_FLASH.
             */
            else if (DEM_INDICATOR_FAST_FLASH == LddIndicator->Behavior)
            {
              /* @Trace: Dem_SUD_API_00044 */
              LddRedStopLampStatus = DEM_J1939LAMP_FAST_FLASH;
            }
            /* @Trace: SWS_Dem_00888
            * The DTC-specific "Flash Red Stop Lamp" shall be set to
            * "Unavailable / Do Not Flash" (0x03) in case the corresponding
            * event has set "Lamp On" and the DemIndicatorBehaviour of the
            * Indicator referenced by DemRedStopIndicatorRef is set to
            * DEM_INDICATOR_CONTINUOUS.
            */
            else
            {
              /* @Trace: Dem_SUD_API_00045 */
              LddRedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
            }
          }

        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        /* @Trace: Dem_SUD_API_00304 */
        if (LddJ1939LampId.WarningLampId == LddIndicator->IndicatorIdRef)
        {
          /* @Trace: SWS_Dem_00891
           * The DTC-specific "Amber Warning Lamp" returned in the function
           * Dem_J1939DcmGetNextDTCwithLampStatus shall be set to "Lamp On" in
           * case the corresponding event has assigned the Indicator referenced
           * by DemAmberWarningIndicatorRef and the UDS status bit 7
           * (WarningIndicator) is active (set to 1), otherwise it shall be set
           * to "Lamp Off".
           */
           /* @Trace: Dem_SUD_API_00046 */
          LblWarningLamp = LblIndicatorAttributeStatus;
          /* @Trace: Dem_SUD_API_00305 */
          if (DEM_J1939LAMP_ON == LblWarningLamp)
          {
           /* @Trace: SWS_Dem_00893
            * The DTC-specific "Flash Amber Warning Lamp" shall be set to
            * "Slow Flash" (0x00) in case the corresponding event has set "Lamp
            * On" and the DemIndicatorBehaviour of the Indicator referenced by
            * DemAmberWarningIndicatorRef is set to DEM_INDICATOR_SLOW_FLASH.
            */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
            if (DEM_INDICATOR_SLOW_FLASH == LddIndicator->Behavior)
            {
              /* @Trace: Dem_SUD_API_00047 */
              LddWarningLampStatus = DEM_J1939LAMP_SLOW_FLASH;
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
           /* @Trace: SWS_Dem_00894
            * The DTC-specific "Flash Amber Warning Lamp" shall be set to "Fast
            * Flash" (0x01) in case the corresponding event has set "Lamp On"
            * and the DemIndicatorBehaviour of the Indicator referenced by
            * DemAmberWarningIndicatorRef is set to DEM_INDICATOR_FAST_FLASH.
            */
            else if (DEM_INDICATOR_FAST_FLASH == LddIndicator->Behavior)
            {
              /* @Trace: Dem_SUD_API_00048 */
              LddWarningLampStatus = DEM_J1939LAMP_FAST_FLASH;
            }
            /* @Trace: SWS_Dem_00892
            * The DTC-specific "Flash Amber Warning Lamp" shall be set to
            * "Unavailable / Do Not Flash" (0x03) in case the corresponding
            * event has set "Lamp On" and the DemIndicatorBehaviour of the
            * Indicator referenced by DemAmberWarningIndicatorRef is set to
            * DEM_INDICATOR_CONTINUOUS.
            */
            else
            {
              /* @Trace: Dem_SUD_API_00049 */
              LddWarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
            }
          }
        }
        /* @Trace: Dem_SUD_API_00296 */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
        if (LddJ1939LampId.ProtectLampId == LddIndicator->IndicatorIdRef)
        {
          /* @Trace: SWS_Dem_00895
           * The DTC-specific "Protect Lamp" returned in the function
           * Dem_J1939DcmGetNextDTCwithLampStatus shall be set to "Lamp On" in
           * case the corresponding event has assigned the Indicator referenced
           * by DemProtectLampIndicatorRef and the UDS status bit 7
           * (WarningIndicator) is active (set to 1), otherwise it shall be set
           * to "Lamp Off".
           */
          /* @Trace: Dem_SUD_API_00050 */
          LblProtectLamp = LblIndicatorAttributeStatus;
          /* @Trace: Dem_SUD_API_00297 */
          if (DEM_J1939LAMP_ON == LblProtectLamp)
          {
            /* @Trace: SWS_Dem_00897
             * The DTC-specifc "Flash Protect Lamp" shall be set to "Slow Flash"
             * (0x00) in case the corresponding event has set "Lamp On" and the
             * DemIndicatorBehaviour of the Indicator referenced by
             * DemProtectLampIndicatorRef is set to DEM_INDICATOR_SLOW_FLASH.
             */
            if (DEM_INDICATOR_SLOW_FLASH == LddIndicator->Behavior)
            {
              /* @Trace: Dem_SUD_API_00051 */
              LddProtectLampStatus = DEM_J1939LAMP_SLOW_FLASH;
            }
            /* @Trace: SWS_Dem_00898
             * The DTC-specifc "Flash Protect Lamp" shall be set to "Fast Flash"
             * (0x01) in case the corresponding event has set "Lamp On" and the
             * DemIndicatorBehaviour of the Indicator referenced by
             * DemProtectLampIndicatorRef is set to  DEM_INDICATOR_FAST_FLASH.
             */
            else if (DEM_INDICATOR_FAST_FLASH == LddIndicator->Behavior)
            {
              /* @Trace: Dem_SUD_API_00052 */
              LddProtectLampStatus = DEM_J1939LAMP_FAST_FLASH;
            }
            /* @Trace: SWS_Dem_00896
             * The DTC-specifc "Flash Protect Lamp" shall be set to "Unavailable
             * / Do Not Flash" (0x03) in case the corresponding event has set
             * "Lamp On" and the DemIndicatorBehaviour of the Indicator
             * referenced by DemProtectLampIndicatorRef is set to
             * DEM_INDICATOR_CONTINUOUS.
             */
            else
            {
              /* @Trace: Dem_SUD_API_00053 */
              LddProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
            }
          }
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        /* @Trace: Dem_SUD_API_00054 */
        LampStatus->LampStatus = (
        /* Flash Malfunction Indicator Lamp  */
        (uint8)((uint8)LblMIL <<  (uint8)(BIT_POS_6)) |
        /* Flash Red Stop Lamp  */
        (uint8)((uint8)LblRedStopLamp  <<  (uint8)(BIT_POS_4)) |
        /* Flash Amber Warning Lamp   */
        (uint8)((uint8)LblWarningLamp  <<  (uint8)(BIT_POS_2)) |
        /* Flash Protect Lamp */
        (uint8)((uint8)LblProtectLamp  <<  (uint8)(BIT_POS_0)));

        LampStatus->FlashLampStatus = (
        /* Flash Malfunction Indicator Lamp Status */
        (uint8)((uint8)LddMILStatus <<  (uint8)(BIT_POS_6)) |
        /* Flash Red Stop Lamp Status */
        (uint8)((uint8)LddRedStopLampStatus   <<  (uint8)(BIT_POS_4)) |
        /* Flash Amber Warning Lamp  Status */
        (uint8)((uint8)LddWarningLampStatus   <<  (uint8)(BIT_POS_2)) |
        /* Flash Protect Lamp Status */
        (uint8)((uint8)LddProtectLampStatus   <<  (uint8)(BIT_POS_0)));
        LddRetVal = E_OK;
        /* @Trace: Dem_SUD_API_00055 */
      }
    }

  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextDTCwithLampStatus                **
**                                                                            **
** Service ID           : 0x94                                                **
**                                                                            **
** Description          : Gets the next filtered J1939 DTC for DM31 including **
**                        current LampStatus.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input parameter      : uint8 ClientId                                      **
**                                                                            **
** Output Parameters    : LampStatus                                          **
**                         bits 8-7 - Malfunction Indicator Lamp Status       **
**                         bits 6-5 - Red Stop Lamp Status                    **
**                         bits 4-3 - Amber Warning Lamp Status               **
**                         bits 2-1 - Protect Lamp Status                     **
**                                                                            **
**                         bits 8-7 - Flash Malfunction Indicator Lamp        **
**                         bits 6-5 - Flash Red Stop Lamp                     **
**                         bits 4-3 - Flash Amber WarningLamp                 **
**                         bits 2-1 - Flash Protect Lamp                      **
**                                                                            **
**                        uint32* J1939DTC                                    **
**                        uint8* OccurenceCounter                             **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                         E_OK                                               **
**                         DEM_NO_SUCH_ELEMENT                                **
**                         DEM_PENDING                                        **
**                         DEM_BUFFER_TOO_SMALL                               **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04113 SRS_Diag_04220
 */
/* @Trace: Dem_SUD_MACRO_058 */
#if (DEM_J1939_DM31_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextDTCwithLampStatus( 
  Dem_J1939DcmLampStatusType* LampStatus, 
  uint32* J1939DTC, 
  uint8* OccurenceCounter,
  uint8 ClientId)
{
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00099 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_SID, DEM_E_UNINIT);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else if ((NULL_PTR == LampStatus) ||
           (NULL_PTR == J1939DTC) ||
           (NULL_PTR == OccurenceCounter))
  {
    /* @Trace: Dem_SUD_API_00100 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_SID, DEM_E_PARAM_POINTER);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00101 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #endif
  else if ((DEM_JOB_TRIGGER ==
              Dem_J1939DTCFilterState[ClientId].j1939_JobAction) ||
           (DEM_JOB_RUNNING ==
               Dem_J1939DTCFilterState[ClientId].j1939_JobAction))
  {    
    /* @Trace: Dem_SUD_API_00148 */
    /* Return appropriate value */
    LddRetVal = DEM_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_J1939DTCFilterState[ClientId].j1939_JobAction)
  {
    /* @Trace: Dem_SUD_API_12743 */
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  } 
  else  
  {
    /* @Trace: Dem_SUD_API_12745 */
    if (Dem_J1939FirstDtcLoc[ClientId] == 0xFFU)
    {
      /* @Trace: Dem_SUD_API_00149 */
      Dem_J1939FirstDtcLoc[ClientId] = DEM_ZERO;
    }
    /* @Trace: Dem_SUD_API_12746 */
    for (; Dem_J1939FirstDtcLoc[ClientId] < DEM_MAX_NUMBER_OF_DTC;
           Dem_J1939FirstDtcLoc[ClientId]++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) LddCbDTC =
          &Dem_GaaCombinedDtc[Dem_J1939FirstDtcLoc[ClientId]];
      Dem_EventIdType LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
      /* @Trace: SWS_Dem_00881
       * Each call to Dem_J1939DcmGetNextDTCwithLampStatus shall search within
       * the event memory (set by the function
       * Dem_J1939DcmFirstDTCwithLampStatus) for the next event having a
       * J1939DTC assigned. In case no more events are available that have a
       * J1939DTC assigend, the function return value shall be
       * DEM_NO_SUCH_ELEMENT. The out parameter needs not to be valid in this
       * case.
       */
      /* @Trace: Dem_SUD_API_12747 */
      if ((DEM_TRUE == Dem_EventIdIsValid(LddEventId)) && (LddEventId != 0))
      {     
        /* @Trace: Dem_SUD_API_12748 */
        if (DEM_TRUE ==
              Dem_EvIsProcStateTriggered(
                  LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER))
        {    
          #if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
          /* Refer to Dem_SetDTCSuppression */
          /* @Trace: SWS_Dem_01101
           * A suppressed DTC shall not be visible for the following Dcm query-
           * functions; therefore the following functions shall treat the DTC
           * as if filter is not matching.
           * */
          if (DEM_TRUE ==
                Dem_EvIsProcStateTriggered(
                    LddEventId, DEM_EVPROCSTATE_DTC_SUPP))
          {
            /* @Trace: Dem_SUD_API_00150 */
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
          }
          else
          #endif
          {

            Dem_EventMemoryEntryPtrType LddMemEntry =
            Dem_EvMem_FindEntry(LddEventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);

          
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
            /* @Trace: Dem_SUD_API_12749 */
            if (NULL_PTR != LddMemEntry)
            {
              Dem_DTCType LddDtc = DEM_NO_DTC;
              uint16 LusDtcLoc = Dem_Event[LddEventId - DEM_ONE].e_PointToDTC;
              /* @Trace: Dem_SUD_API_12750 */
              if (LusDtcLoc < DEM_MAX_NUMBER_OF_DTC)
              {
                /* @Trace: Dem_SUD_API_12751 */
                LddDtc = Dem_GaaCombinedDtc[LusDtcLoc].J1939DTCValue;
              }
              /* @Trace: Dem_SUD_API_12752 */
              if (DEM_NO_DTC != LddDtc)
              {

                *J1939DTC = LddDtc;
                *OccurenceCounter = LddMemEntry->EventOccurrenceCounter;
                /* @Trace: SWS_Dem_00882
                 * In case Dem_J1939DcmGetNextDTCwithLampStatus has found an
                 * event matching the filter criteria it shall return the
                 * J1939DTC specific status of the lamps (refer to following
                 * sections for details), the corresponding J1939DTC (refer
                 * DemDTCAttributes for details) and the corresponding
                 * occurrence counter. The return value shall be E_OK. In case
                 * the search needs to be interrupted due to internal
                 * implementations or limitations, the return value can be set
                 * to DEM_PENDING. The out parameter needs not to be valid in
                 * this case. The next call of
                 * Dem_J1939DcmGetNextDTCwithLampStatus should continue after
                 * the interrupted element. In case the occurrence counter is
                 * above +126 (0x7F), the returned values shall be set to +126
                 * (0x7F).
                 */
                /* @Trace: Dem_SUD_API_12744 */
                if (*OccurenceCounter > 0x7F)
                {
                  /* @Trace: Dem_SUD_API_00151 */
                  *OccurenceCounter = 0x7F;
                }

                (void)Dem_GetJ1939LampStatus(LddEventId, LampStatus);
                
                  
                LddRetVal = E_OK;
                break;
              }
            }      
          }
        }
      }
    }
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmClearDTC                                **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Clears active DTCs as well as previously avtive DTCs**
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCTypeFilter -                                     **
**                        The following types are available:                  **
**                        DEM_J1939DTC_CLEAR_ACTIVE                           **
**                        DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE                **
**                        uint8 ClientId                                      **
**                                                                            **
**                        NodeAddress - node address of requesting client     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                          E_OK                                              **
**                          DEM_CLEAR_WRONG_DTC                               **
**                          DEM_CLEAR_WRONG_DTCORIGIN                         **
**                          DEM_CLEAR_FAILED                                  **
**                          DEM_PENDING                                       **
**                          DEM_CLEAR_BUSY                                    **
**                          DEM_CLEAR_MEMORY_ERROR                            **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04220
 */
#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
Std_ReturnType Dem_J1939DcmClearDTC(
  Dem_J1939DcmSetClearFilterType DTCTypeFilter,
  Dem_DTCOriginType DTCOrigin,
  uint8 ClientId)
{
  /* @Trace: SWS_Dem_00878
   * The Dem module shall provide the Dem_J1939DcmClearDTC to the J1939Dcm [7]
   * for deleting all active or previously active DTCs from the event memory.
   * This shall trigger also initializing of related SW-Cs / BSW modules
   * according to [SWS_Dem_00003].
   */
  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
	  /* @Trace: Dem_SUD_API_00103 */
    DEM_REPORT_ERROR(DEM_J1939DCMCLEARDTC_SID, DEM_E_WRONG_CONFIGURATION);
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    /*LddRetVal = DEM_CLEAR_FAILED;*/
  }
  else
  #endif
  if ((DEM_CLEARDTC_STATE_USER_CDD == Dem_ClearDtcState[ClientId].cds_User) ||
    (DEM_CLEARDTC_STATE_USER_DCM == Dem_ClearDtcState[ClientId].cds_User))
  {
    /* @Trace: Dem_SUD_API_00102 */
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    LddRetVal = DEM_PENDING; /* It means 'busy' state */
  }
  /* @Trace: SWS_Dem_01101
   * A suppressed DTC shall not be visible for the following Dcm query-functions;
   * therefore the following functions shall treat the DTC as if filter is not
   * matching.
   * */
  else if (DEM_TRUE ==
             Dem_EvIsProcStateTriggered(
                 Dem_ClearDtcState[ClientId].cds_EventIdRef,
                 DEM_EVPROCSTATE_DTC_SUPP))
  {
    /* @Trace: Dem_SUD_API_12753 */
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    LddRetVal = DEM_CLEAR_FAILED;
  }
  else /* DEM_CLEARDTC_STATE_USER_DCM or IDLE */
  {
    if ((DEM_J1939DTC_CLEAR_ACTIVE == DTCTypeFilter) || /* DM11 */
        (DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE == DTCTypeFilter) || /* DM3*/
        (DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE == DTCTypeFilter)
        /* DM53*/
       )
    {
      Dem_ClearDtcState[ClientId].cds_User = DEM_CLEARDTC_STATE_USER_J1939DCM;
      Dem_ClearDtcState[ClientId].cds_DTCTypeFilter = DTCTypeFilter;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      /* Limitations : Supports only DEM_DTC_ORIGIN_PRIMARY_MEMORY according to 
       * J1939-73 
       * DM3 is not used to clear all diagnostic data relative to regulated OBD
       * products.
       * DM3 is not required to satisfy regulated
       * automotive OBD requirements. DM3 can be used for other manufacturer
       * specific purposes */
      LddRetVal =
          Dem_InternalClearDTC(
              ClientId,
              DEM_DTC_GROUP_ALL_DTCS,
              DEM_DTC_FORMAT_J1939,
              DTCOrigin);
      /* @Trace: Dem_SUD_API_12755 */
      if (DEM_PENDING != LddRetVal)
      {
        /* @Trace: Dem_SUD_API_12756 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();    
        Dem_ClearDtcState[ClientId].cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_12754 */
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }  
  return LddRetVal;
}
#endif


/*******************************************************************************
** Function Name        : Dem_J1939DcmSetFreezeFrameFilter                    **
**                                                                            **
** Service ID           : 0x96                                                **
**                                                                            **
** Description          : This API shall set a J1939 freeze frame Record      **
**                        filter                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FreezeFrameKind                                     **
**                        ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04111
 */
/* @Trace: Dem_SUD_MACRO_059 */
#if ((DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON) || \
     (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind,
  uint8 ClientId)
{
  /* @Trace: SWS_Dem_00899
   * The function Dem_J1939DcmSetFreezeFrameFilter shall set the filter mask
   * attributes to be used for the subsequent calls of
   * Dem_J1939DcmGetNextFreezeFrame, and reset an internal counter to the first
   * freeze frame. The filter mask attributes shall be used until the next call
   * of Dem_J1939DcmSetFreezeFrameFilter or Dem initialization. The matching
   * filter citreria are DEM_J1939DCM_FREEZEFRAME (filtering the data in
   * DemJ1939FreezeFrameClassRef) or DEM_J1939DCM_EXPANDED_FREEZEFRAME
   * (filtering the data in DemJ1939ExpandedFreezeFrameClassRef).
   */

  Std_ReturnType LddRetVal = E_OK;

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00104 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETFREEZEFRAMEFILTER_SID, DEM_E_UNINIT);
    /*LddRetVal = E_NOT_OK;*/
  }
  else if ((FreezeFrameKind != DEM_J1939DCM_FREEZEFRAME) &&
           (FreezeFrameKind != DEM_J1939DCM_EXPANDED_FREEZEFRAME) &&
           (FreezeFrameKind != DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME))
  {
    /* @Trace: Dem_SUD_API_00105 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETFREEZEFRAMEFILTER_SID, DEM_E_PARAM_CONFIG);
    /*LddRetVal = E_NOT_OK;*/
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00106 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMSETFREEZEFRAMEFILTER_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = E_NOT_OK;*/
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_12757 */
    Dem_FilteredFFRecord[ClientId].kindOfJ1939FreezeFrame = FreezeFrameKind;
    Dem_FilteredFFRecord[ClientId].j1939FF_JobAction = DEM_JOB_TRIGGER;
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextFreezeFrame                      **
**                                                                            **
** Service ID           : 0x97                                                **
**                                                                            **
** Description          : Gets next freeze frame data. The function stores    **
**                        the data in the provided DestBuffer.                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : DestBuffer                                          **
**                        BufSize                                             **
**                                                                            **
** Output Parameters    : uint32* DTC,                                        **
**                        uint8* DestBuffer                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                         E_OK                                               **
**                         DEM_NO_SUCH_ELEMENT                                **
**                         DEM_PENDING                                        **
**                         DEM_BUFFER_TOO_SMALL                               **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04111 SRS_Diag_04220
 */
/* @Trace: Dem_SUD_MACRO_060 */
#if ((DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON) || \
     (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFreezeFrame(
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) J1939DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) OccurenceCounter,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) BufSize,
  uint8 ClientId)
{
  Std_ReturnType LddRetVal  = DEM_NO_SUCH_ELEMENT;;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
	  /* @Trace: Dem_SUD_API_00107 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_UNINIT);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else if ((NULL_PTR == J1939DTC) || (NULL_PTR == OccurenceCounter) ||
           (NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  {
    /* @Trace: Dem_SUD_API_00108 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_PARAM_POINTER);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00109 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #endif
  /* @Trace: SWS_Dem_00902
   * In case the search of [SWS_Dem_00901] needs to be interrupted due to
   * internal implementations or limitations, the return value can be set to
   * DEM_PENDING. The out parameter needs not to be valid in this case. The
   * next call of Dem_J1939DcmGetNextFreezeFrame should continue after the
   * interrupted element.
   */
  else if ((DEM_JOB_TRIGGER ==
              Dem_FilteredFFRecord[ClientId].j1939FF_JobAction) ||
           (DEM_JOB_RUNNING ==
              Dem_FilteredFFRecord[ClientId].j1939FF_JobAction))
  {
    /* @Trace: Dem_SUD_API_12778 */
    /* Return appropriate value */
    LddRetVal = DEM_PENDING;
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent)
  {
   /* @Trace: Dem_SUD_API_12769 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_PARAM_DATA);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT*/;
  }
  /* @Trace: SWS_Dem_01101
   * A suppressed DTC shall not be visible for the following Dcm query-
   * functions; therefore the following functions shall treat the DTC as if
   * filter is not matching.
   * */
  else if (DEM_TRUE ==
             Dem_EvIsProcStateTriggered(
                 Dem_FilteredFFRecord[ClientId].nextEvent,
                 DEM_EVPROCSTATE_DTC_SUPP))
  {
    /* @Trace: Dem_SUD_API_12758 */
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  /* @Trace: SWS_Dem_00901
   * The function Dem_J1939DcmGetNextFreezeFrame shall trigger the Det error
   * DEM_E_WRONG_CONDITION in case of not supported FreezeFrameKind. Valid
   * values are DEM_J1939DCM_FREEZEFRAME and DEM_J1939DCM_EXPANDED_FREEZEFRAME.
   */
  else if ((DEM_J1939DCM_FREEZEFRAME !=
              Dem_FilteredFFRecord[ClientId].kindOfJ1939FreezeFrame) && \
           (DEM_J1939DCM_EXPANDED_FREEZEFRAME !=
               Dem_FilteredFFRecord[ClientId].kindOfJ1939FreezeFrame))
  {
    /* @Trace: Dem_SUD_API_12777 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_WRONG_CONDITION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT*/;
  }
  else if (DEM_JOB_DONE != Dem_FilteredFFRecord[ClientId].j1939FF_JobAction)
  {
    /* @Trace: Dem_SUD_API_12779 */
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         (DEM_NUM_OF_J1939FREEZEFRAMECLASS > DEM_ZERO))
    Dem_EventMemoryEntryPtrType LddEntry;
    Dem_J1939DcmSetFreezeFrameFilterType LddJ1939FFType = DEM_ZERO;
    Dem_NumOfEventMemoryEntryType LddIdxOfEntry =
        Dem_PriEvMemChronoOrderNextLoc;
    uint16 LusBufSize = DEM_ZERO;
    struct {
      Dem_EventIdType LddPrioEventId;
      Dem_EventPriorityType LddPriority;
      Dem_J1939DcmSetFreezeFrameFilterType LddFilerType;
    } LstHighestEvent = {DEM_ZERO, DEM_ZERO, DEM_ZERO};

    /* Only DEM_DTC_ORIGIN_PRIMARY_MEMORY */
    /* @Trace: SWS_Dem_00900
     * Each function call of Dem_J1939DcmGetNextFreezeFrame shall step to the
     * next (Expanded-)FreezeFrame for a specific event memory defined by the
     * filter criteria (FreezeFrameKind and ClientId) of
     * Dem_J1939DcmSetFreezeFrameFilter. In case no more (Expanded)FreezeFrames
     * are matching the filter criteria, the function shall return
     * DEM_NO_SUCH_ELEMENT. The out parameters need not to be valid in this case.
     */
    /* @Trace: Dem_SUD_API_12780 */
    while (LddIdxOfEntry > DEM_ZERO)
    {
      /* @IF_REQ: SWS_Dem_00411
       * If the Dem module is requested to report in chronological order,
       * the most recent event memory entry shall be reported at first. */
      Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;

      --LddIdxOfEntry;
      /* @Trace: Dem_SUD_API_12781 */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddIdxOfEntry)
      {
        LddMemLoc= Dem_PriEvMemChronoOrder[LddIdxOfEntry];
      }
      /* @Trace: Dem_SUD_API_12782 */
      if (DEM_NO_EVMEM_ENTRY != LddMemLoc)
      {
        Dem_EventIdType LddEventId =
            Dem_EvMem_GetEventIdByEvMemEntry(
                DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                LddMemLoc);

        if (DEM_TRUE ==
              Dem_EvIsProcStateTriggered(
                  LddEventId, DEM_EVPROCSTATE_J1939DTC_FILTER))
        {
          /* @Trace: Dem_SUD_API_12761 */
          LddJ1939FFType = DEM_J1939DCM_FREEZEFRAME;
        }
        else if (DEM_TRUE ==
                   Dem_EvIsProcStateTriggered(
                       LddEventId, DEM_EVPROCSTATE_J1939EXFF_FILTER))
        {
          /* @Trace: Dem_SUD_API_12759 */
          LddJ1939FFType = DEM_J1939DCM_EXPANDED_FREEZEFRAME;
        }
        else
        {
          /* @Trace: Dem_SUD_API_12760 */
          LddJ1939FFType = DEM_THREE;
        }
        /* @Trace: Dem_SUD_API_12783 */
        if (DEM_TRUE == Dem_EventIdIsValid(LddEventId) )
        {
          /* @Trace: Dem_SUD_API_12762 */
          if ((LddJ1939FFType == DEM_J1939DCM_FREEZEFRAME) ||
              (LddJ1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME))
          {
            Dem_EventParameterCPCType LddEvent =
                &Dem_Event[LddEventId - DEM_ONE];

            if (DEM_NO_EVENT != LstHighestEvent.LddPrioEventId)
            {
              /* @Trace: Dem_SUD_API_12764 */
              if (LddEvent->ucEventPriority < LstHighestEvent.LddPriority)
              {
                /* @Trace: Dem_SUD_API_12765 */
                LstHighestEvent.LddPrioEventId = LddEventId;
                LstHighestEvent.LddPriority = LddEvent->ucEventPriority;
                LstHighestEvent.LddFilerType = LddJ1939FFType;
              }
            }
            else
            {
              /* @Trace: Dem_SUD_API_12763 */
              LstHighestEvent.LddPrioEventId = LddEventId;
              LstHighestEvent.LddPriority = LddEvent->ucEventPriority;
              LstHighestEvent.LddFilerType = LddJ1939FFType;
            }
          }
        }
      }
    }    
    /* @Trace: Dem_SUD_API_12766 */
    if (DEM_NO_EVENT != LstHighestEvent.LddPrioEventId)
    {  
    
      Dem_EvClearProcState(
          LstHighestEvent.LddPrioEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
      Dem_EvClearProcState(
          LstHighestEvent.LddPrioEventId, DEM_EVPROCSTATE_J1939EXFF_FILTER);

      LddEntry =
          Dem_EvMem_FindEntry(
              LstHighestEvent.LddPrioEventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      /* @Trace: Dem_SUD_API_12767 */
      if (NULL_PTR != LddEntry)
      {
        Dem_EventParameterPCType LddEvent =
            &Dem_Event[LstHighestEvent.LddPrioEventId - DEM_ONE];
        /* @Trace: Dem_SUD_API_12768 */
        if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
        {
          /* @Trace: SWS_Dem_00903
           * In case the function Dem_J1939DcmGetNextFreezeFrame has found a
           * FreezeFrame, the Dem shall: Check if the buffer in the BufSize
           * parameter is big enough to hold the (Expanded-)FreezeFrame.
           * If not, DEM_FILTERED_BUFFER_TOO_SMALL shall be returned without
           * any further actions. The out parameters need not to be valid in
           * this case.
           * - Copy the (Expanded-)FreezeFrame data into the buffer provided by
           * the parameter DestBuffer (in case of Expanded FreezeFrames without
           * any SPN informations). Unused bits shall be filled with "0".
           * - Set the parameter J1939DTC to the corresponding J1939DTC value
           * (refer DemDTCAttributes for details) and the parameter
           * OccurrenceCounter to the corresponding occurrence counter value.
           * - Return with E_OK. In case the occurrence counter is above +126
           * (0x7F), the returned value shall be set to +126 (0x7F).
           */
          LddRetVal =
              Dem_GetJ1939FreezeFrameData(
                  LddEvent,
                  DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                  DestBuffer,
                  &LusBufSize,
                  LstHighestEvent.LddFilerType);
          /* @Trace: Dem_SUD_API_12770 */
          if (E_OK == LddRetVal)
          {
            *J1939DTC = DEM_NO_DTC;
            uint16 LusDtcLoc =
                Dem_Event[LstHighestEvent.LddPrioEventId - DEM_ONE].e_PointToDTC;
            /* @Trace: Dem_SUD_API_12771 */
            if (LusDtcLoc < DEM_MAX_NUMBER_OF_DTC)
            {
              /* @Trace: Dem_SUD_API_12772 */
              *J1939DTC = Dem_GaaCombinedDtc[LusDtcLoc].J1939DTCValue;
            }
            *OccurenceCounter = LddEntry->EventOccurrenceCounter;
            /* @Trace: Dem_SUD_API_12773 */
            if (*OccurenceCounter > 0x7F)
            {
              /* @Trace: Dem_SUD_API_12774 */
              *OccurenceCounter = 0x7F;
            }
            /* @Trace: Dem_SUD_API_12775 */
            *BufSize = LusBufSize;

            Dem_FilteredFFRecord[ClientId].nextEvent++;
          }
        }
      }
    }
    #endif
  }
  /* @Trace: Dem_SUD_API_12776 */
  return LddRetVal;
}
#endif


/*******************************************************************************
** Function Name        : Dem_J1939DcmSetRatioFilter                          **
**                                                                            **
** Service ID           : 0x99                                                **
**                                                                            **
** Description          : The function set the Ratio filter for a specifc node**
**                        and returns the corresponding                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* IgnitionCycleCounter                        **
**                        uint16* OBDMonitoringConditionsEncountered          **
**                                                                            **
** Return parameter     : Std_ReturnTyp                                       **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* @Trace: Dem_SUD_MACRO_061 */
#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
Std_ReturnType
Dem_J1939DcmSetRatioFilter(
  uint16* IgnitionCycleCounter, 
  uint16* OBDMonitoringConditionsEncountered, 
  uint8 ClientId)
{

  Std_ReturnType LddRetVal = E_OK;
  
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00119 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETRATIOFILTER_SID, DEM_E_UNINIT);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  else if ((IgnitionCycleCounter == NULL_PTR) ||
           (OBDMonitoringConditionsEncountered == NULL_PTR))
  {
    /* @Trace: Dem_SUD_API_00120 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETRATIOFILTER_SID, DEM_E_PARAM_CONFIG);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00121 */
    DEM_REPORT_ERROR(DEM_J1939DCMSETRATIOFILTER_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_12792 */
    *IgnitionCycleCounter = Dem_GusIgnitionCylCnt;
    *OBDMonitoringConditionsEncountered = Dem_GusGeneralDenominator;
    Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction = DEM_JOB_TRIGGER;
  }

  return LddRetVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextFilteredRatio                    **
**                                                                            **
** Service ID           : 0x9a                                                **
**                                                                            **
** Description          : Gets next ratio data. The function reports          **
**                        the Numerator and Denominator.                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : DestBuffer                                          **
**                        BufSize                                             **
**                                                                            **
** Output Parameters    : uin16* SPN,                                         **
**                        uint16* Numerator                                   **
**                        uint16* Denominator                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                         E_OK                                               **
**                         DEM_NO_SUCH_ELEMENT                                **
**                         DEM_PENDING                                        **
**                         DEM_BUFFER_TOO_SMALL                               **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04113 SRS_Diag_04220
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
Std_ReturnType
Dem_J1939DcmGetNextFilteredRatio(
  uint32* SPN,
  uint16* Numerator,
  uint16* Denominator,
  uint8 ClientId)
{
  Std_ReturnType LddRetVal  = DEM_NO_SUCH_ELEMENT;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00122 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_UNINIT);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  else if ((NULL_PTR == SPN) ||
           (NULL_PTR == Numerator) ||
           (NULL_PTR == Denominator))
  {
    /* @Trace: Dem_SUD_API_00123 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_PARAM_POINTER);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00124 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  #endif
  else if ((DEM_JOB_TRIGGER ==
              Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction) ||
           (DEM_JOB_RUNNING ==
              Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction))
  {
    /* @Trace: Dem_SUD_API_12794 */
    /* Return appropriate value */
    LddRetVal = DEM_PENDING;
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent)
  {
    /* @Trace: Dem_SUD_API_00125 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_PARAM_DATA);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  /* @Trace: SWS_Dem_01101
   * A suppressed DTC shall not be visible for the following Dcm query-functions;
   * therefore the following functions shall treat the DTC as if filter is not
   * matching.
   * */
  else if (DEM_TRUE ==
             Dem_EvIsProcStateTriggered(
                 Dem_FilteredFFRecord[ClientId].nextEvent,
                 DEM_EVPROCSTATE_DTC_SUPP))
  {
    /* @Trace: Dem_SUD_API_12793 */
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  else if (DEM_JOB_DONE != Dem_FilteredFFRecord[ClientId].j1939Ratio_JobAction)
  {
    /* @Trace: Dem_SUD_API_12795 */
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
    Dem_EventIdType LddEventId;
    Dem_EventParameterPCType LddEvent;


    /*  if event is deleled or aged, Dem returns the next event.*/
    /* @Trace: SWS_Dem_00913
     * Each call of the function Dem_J1939DcmGetNextFilteredRatio shall skip to
     * the next valid SPN within the event memory with DemRatioId defined.
     * - The events referenced by this SPN via DemRatioId shall be used to
     * calculate the return values SPN (for "SPN of Applicable System Monitor"),
     * Numerator (for "Applicable System Monitor Numerator"), and Denominator
     * (for "Applicable System Monitor Denominator"). The return value shall
     * be E_OK.
     * - In case the calculation needs to be interrupted due to internal
     * implementations or limitations, the return value can be set to
     * DEM_PENDING. The out parameter needs not to be valid in this case. The
     * next call of Dem_J1939DcmGetNextFilteredRatio should continue after the
     * interrupted element.
     * - In case no more SPNs are available, the function return value shall be
     * DEM_NO_SUCH_ELEMENT. The out parameter needs not to be valid in this case.
     */
    /* @Trace: Dem_SUD_API_12796 */
    while (Dem_FilteredFFRecord[ClientId].nextEvent <= DEM_NUMBER_OF_EVENTS)
    {
      /* @Trace: Dem_SUD_API_00154 */
      if (DEM_TRUE ==
            Dem_EvIsProcStateTriggered(
                Dem_FilteredFFRecord[ClientId].nextEvent,
                DEM_EVPROCSTATE_J1939DTC_FILTER))
      {
        Dem_DTCType LddDtc;
        LddEventId = Dem_FilteredFFRecord[ClientId].nextEvent;

        LddEvent = &Dem_Event[LddEventId - DEM_ONE];

        (void)Dem_GetEventDTC(LddEvent, &LddDtc, DEM_DTC_FORMAT_J1939);
  
        /* @Trace: Dem_SUD_API_12797 */
        if (LddEvent->aaRatioIndex[Dem_J1939NextRatioIndex] <
              DEM_NUMBER_OF_RATIO_INFO)
        {
          *SPN = (uint32)(LddDtc >> 8);
          *Numerator =
              Dem_GaaIumprNumerator
                [Dem_GaaRatioIdInfo
                   [LddEvent->aaRatioIndex
                      [Dem_J1939NextRatioIndex]].ucIUMPRGroup];
          *Denominator =
              Dem_GaaIumprDenominator
                [Dem_GaaRatioIdInfo
                   [LddEvent->aaRatioIndex
                      [Dem_J1939NextRatioIndex]].ucIUMPRGroup];
          
          Dem_EvClearProcState(
              Dem_FilteredFFRecord[ClientId].nextEvent,
              DEM_EVPROCSTATE_J1939DTC_FILTER);

          if (Dem_J1939NextRatioIndex <
                (LddEvent->usRatioIdCount-DEM_ONE))
          {
            /* @Trace: Dem_SUD_API_00153 */
            Dem_J1939NextRatioIndex++;
          }
          else
          {
            /* @Trace: Dem_SUD_API_12798 */
            Dem_FilteredFFRecord[ClientId].nextEvent++;
            Dem_J1939NextRatioIndex = DEM_ZERO;
          }
          LddRetVal = E_OK;
          break; 
        }
      }
      /* Increment the record count returned to dcm */
      Dem_FilteredFFRecord[ClientId].nextEvent++;
    }
    #endif
  }
  
  return LddRetVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmReadDiagnosticReadiness1                **
**                                                                            **
** Service ID           : 0x9b                                                **
**                                                                            **
** Description          : Service to report the value of DiagnosticReadiness1 **
**                        (DM5) computed by the Dem.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_J1939DcmDiagnosticReadiness1Type* DataValue,    **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04113 SRS_Diag_04220
 */
/* @Trace: Dem_SUD_MACRO_062 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_J1939_READINESS1_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness1(
  Dem_J1939DcmDiagnosticReadiness1Type* DataValue,
  uint8 ClientId )
{
  Std_ReturnType LddRetVal = E_OK;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00126 */
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS1_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  else if (NULL_PTR == DataValue)
  {
    /* @Trace: Dem_SUD_API_00127 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMREADDIAGNOSTICREADINESS1_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00128 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMREADDIAGNOSTICREADINESS1_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = E_NOT_OK;
  }
  #endif
  else
  {
    VAR(uint16, AUTOMATIC) LusNumberOfFilteredDTC = DEM_ZERO;
    Dem_J1939DcmLampStatusType LddLampStatus;
    uint16 LusEvIndex;
    
    const boolean LaaRdGrp[] =
    {
      DEM_FALSE,   /* DEM_OBD_RDY_NONE        0x00    */
      DEM_TRUE,    /* DEM_OBD_RDY_CAT        0x01    */
      DEM_TRUE,    /* DEM_OBD_RDY_HTCAT      0x02    */
      DEM_TRUE,    /* DEM_OBD_RDY_MISF         0x03    */
      DEM_TRUE,    /* DEM_OBD_RDY_EVAP        0x04    */
      DEM_TRUE,    /* DEM_OBD_RDY_SECAIR      0x05    */
      DEM_TRUE,    /* DEM_OBD_RDY_FLSYS       0x06    */
      DEM_TRUE,    /* DEM_OBD_RDY_EGSENS      0x07    */
      DEM_TRUE,    /* DEM_OBD_RDY_EGR         0x08    */
      DEM_FALSE,
      DEM_TRUE,    /* DEM_OBD_RDY_AC          0x0A    */
      DEM_FALSE,
      DEM_FALSE,
      DEM_TRUE,    /* DEM_OBD_RDY_O2SENS      0x0D    */
      DEM_TRUE,    /* DEM_OBD_RDY_CMPRCMPT    0x0E    */
      DEM_TRUE,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      DEM_TRUE,    /* DEM_OBD_RDY_HTCAT       0x10    */
      DEM_TRUE,    /* DEM_OBD_RDY_NOXCAT      0x11    */
      DEM_TRUE,    /* DEM_OBD_RDY_BOOSTPR     0x12    */
      DEM_FALSE,     
      DEM_TRUE     /* DEM_OBD_RDY_PMFLT       0x14    */
    };
    

    const uint16 LaaShiftMask[] =
    {
      0x00,      /* DEM_OBD_RDY_NONE        0x00    */
      0x0001U,   /* DEM_OBD_RDY_CAT        0x01    */
      0x0002U,   /* DEM_OBD_RDY_HTCAT      0x02    */
      0x01U,     /* DEM_OBD_RDY_MISF         0x03    */
      0x04,      /* DEM_OBD_RDY_EVAP        0x04    */
      0x0008,    /* DEM_OBD_RDY_SECAIR      0x05    */
      0x02,      /* DEM_OBD_RDY_FLSYS       0x06    */
      0x0020U,    /* DEM_OBD_RDY_EGSENS      0x07    */
      0x0080,     /* DEM_OBD_RDY_EGR         0x08    */
      0x0,
      0x0010,     /* DEM_OBD_RDY_AC          0x0A    */
      0,
      0,
      0x100,     /* DEM_OBD_RDY_O2SENS      0x0D    */
      0x04,      /* DEM_OBD_RDY_CMPRCMPT    0x0E    */
      0x0040,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      0x0002,    /* DEM_OBD_RDY_HCCAT       0x10    */
      0x0800,    /* DEM_OBD_RDY_NOXCAT      0x11    */
      0x0200,    /* DEM_OBD_RDY_BOOSTPR     0x12    */
      0,    
      0x4000     /* DEM_OBD_RDY_PMFLT       0x14    */
    };

    
    /*  Byte 1 :   */
    /* @Trace: SWS_Dem_00909
     * A call of Dem_J1939DcmReadDiagnosticReadiness1 shall report a response
     * message based on the J1939-73 [14] DM05 definition:
     * - "Active Trouble Codes" shall report the number of active DTCs identical
     * to the number of filtered DTCs by Dem_J1939DcmSetDTCFilter (Dem_Active,
     * DEM_DTC_KIND_ALL_DTCS).
     * - "Previously Active Diagnostic Trouble Codes" shall report the number of
     * previously active DTCs identical to the number of filtered DTCs by
     * Dem_J1939DcmSetDTCFilter (Dem_PreviouslyActive, DEM_DTC_KIND_ALL_DTCS).
     * - "OBD Compliance" shall be based on the configuration parameter
     * DemOBDCompliancy (in DemGeneralOBD). For nonOBD ECUs the value five (5)
     * shall be reported.
     * - The (Non-)Continuously Monitored Systems support and status shall be
     * reported according to SAE J1939-73 chapter 5.7.5.4 to 5.7.5.6. The
     * calculation shall be based on those events referencing the corresponding
     * configuration parameter
     */
    if (E_OK ==
          Dem_J1939DcmSetDTCFilter(
              DEM_J1939DTC_ACTIVE,
              DEM_DTC_KIND_ALL_DTCS,
              1,
              ClientId,
              &LddLampStatus))
    {
      /* @Trace: Dem_SUD_API_12810 */
      if (Dem_J1939DTCFilterState[ClientId].j1939_JobAction == DEM_JOB_TRIGGER)
      {
        /* @Trace: Dem_SUD_API_12813 */
        SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
        Dem_J1939DTCFilterState[ClientId].j1939_JobAction = DEM_JOB_RUNNING;
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION(); 
        Dem_J1939CountAndStoreFilterDtc(ClientId);
      }
  
      (void)Dem_J1939DcmGetNumberOfFilteredDTC(
          &LusNumberOfFilteredDTC, ClientId);
      /* @Trace: Dem_SUD_API_12814 */
      if (LusNumberOfFilteredDTC > DEM_J1939RDY_MAX_DTC_NUMBER)
      {
        /* @Trace: Dem_SUD_API_12815 */
        LusNumberOfFilteredDTC = DEM_J1939RDY_MAX_DTC_NUMBER;
      }
      DataValue->ActiveTroubleCodes = (uint8)LusNumberOfFilteredDTC;

      /*  Byte 2 :   */
      if (E_OK ==
            Dem_J1939DcmSetDTCFilter(
                DEM_J1939DTC_PREVIOUSLY_ACTIVE,
                DEM_DTC_KIND_ALL_DTCS,
                1, ClientId,
                &LddLampStatus))
      {
        /* @Trace: Dem_SUD_API_12817 */
        if (Dem_J1939DTCFilterState[ClientId].j1939_JobAction ==
              DEM_JOB_TRIGGER)
        {
          /* @Trace: Dem_SUD_API_12818 */
          SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
          Dem_J1939DTCFilterState[ClientId].j1939_JobAction = DEM_JOB_RUNNING;
          SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
          Dem_J1939CountAndStoreFilterDtc(ClientId);
        }

        (void)Dem_J1939DcmGetNumberOfFilteredDTC(
            &LusNumberOfFilteredDTC, ClientId);
        /* @Trace: Dem_SUD_API_12819 */
        if (LusNumberOfFilteredDTC > DEM_J1939RDY_MAX_DTC_NUMBER)
        {
          /* @Trace: Dem_SUD_API_12800 */
          LusNumberOfFilteredDTC = DEM_J1939RDY_MAX_DTC_NUMBER;
        }
        DataValue->PreviouslyActiveDiagnosticTroubleCodes =
            (uint8)LusNumberOfFilteredDTC;

        /*  Byte 3 :   */
        DataValue->OBDCompliance = (uint8)DEM_OBD_COMPLIANCE;

        DataValue->ContinuouslyMonitoredSystemsSupport_Status = DEM_ZERO;
        DataValue->NonContinuouslyMonitoredSystemsSupport5 = DEM_ZERO;
        DataValue->NonContinuouslyMonitoredSystemsSupport6 = DEM_ZERO;
        DataValue->NonContinuouslyMonitoredSystemsStatus7 = DEM_ZERO;
        DataValue->NonContinuouslyMonitoredSystemsStatus8 = DEM_ZERO;

        uint16 LusNonContinuouslyMonitoredSystemsSupport = DEM_ZERO;
        uint16 LusNonContinuouslyMonitoredSystemsStatus = DEM_ZERO;
        /* @Trace: Dem_SUD_API_12801 */
        for (LusEvIndex = DEM_ZERO;
             LusEvIndex < DEM_NUMBER_OF_EVENTS ;
             LusEvIndex++)
        {
          /* @Trace: Dem_SUD_API_12802 */
          P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) LddCbDTC =
              Dem_GetCbDTCByEventId(LusEvIndex+DEM_ONE);
          /* @Trace: Dem_SUD_API_12803 */
          if ((NULL_PTR != LddCbDTC) && (DEM_NO_DTC != LddCbDTC->usObdDtc))
          {
            #if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
            /* Refer to Dem_SetDTCSuppression */
            /* @Trace: SWS_Dem_01101
             * A suppressed DTC shall not be visible for the following Dcm
             * query-functions; therefore the following functions shall treat
             * the DTC as if filter is not matching.
             * */
            /* @Trace: Dem_SUD_API_12804 */
            if (DEM_FALSE ==
                  Dem_EvIsProcStateTriggered(
                      LusEvIndex + DEM_ONE, DEM_EVPROCSTATE_DTC_SUPP))
            #endif
            {
              Dem_UdsStatusByteType LddDtcStatusByte =
                  Dem_GetDTCStatus(LusEvIndex + DEM_ONE);
              boolean LblTested = DEM_ZERO;
              /* @Trace: Dem_SUD_API_12805 */
              if (((uint8)DEM_UDS_STATUS_TNCSLC & LddDtcStatusByte) == DEM_ZERO)
              {
                /* @Trace: Dem_SUD_API_12806 */
                LblTested = DEM_ONE;
              }
              /* @Trace: Dem_SUD_API_12807 */
              if (LaaRdGrp[Dem_Event[LusEvIndex].ulEventOBDReadinessGroup] ==
                    DEM_TRUE)
              {
                if ((DEM_OBD_RDY_MISF ==
                       Dem_Event[LusEvIndex].ulEventOBDReadinessGroup) ||
                    (DEM_OBD_RDY_FLSYS ==
                       Dem_Event[LusEvIndex].ulEventOBDReadinessGroup)
                  || (DEM_OBD_RDY_CMPRCMPT ==
                        Dem_Event[LusEvIndex].ulEventOBDReadinessGroup))
                {
                  DataValue->ContinuouslyMonitoredSystemsSupport_Status =
                      DataValue->ContinuouslyMonitoredSystemsSupport_Status|
                      (uint8)LaaShiftMask
                        [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup];
                  /* @Trace: Dem_SUD_API_12812 */
                  if (DEM_ZERO == LblTested)
                  {
                    /* @Trace: Dem_SUD_API_12811 */
                    DataValue->ContinuouslyMonitoredSystemsSupport_Status =
                        DataValue->ContinuouslyMonitoredSystemsSupport_Status|
                        (uint8)(LaaShiftMask
                          [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup]<<4);
                  }
                }
                else
                {
                  LusNonContinuouslyMonitoredSystemsSupport =
                      LusNonContinuouslyMonitoredSystemsSupport|
                      LaaShiftMask
                        [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup];
                  DataValue->NonContinuouslyMonitoredSystemsSupport5 =
                      (uint8)(LusNonContinuouslyMonitoredSystemsSupport &
                          0x00FFU);
                  DataValue->NonContinuouslyMonitoredSystemsSupport6 =
                      (uint8)((LusNonContinuouslyMonitoredSystemsSupport &
                          0xFF00U) >> DEM_EIGHT);
                  /* @Trace: Dem_SUD_API_12808 */
                  if (DEM_ZERO == LblTested)
                  {
                    /* @Trace: Dem_SUD_API_12809 */
                    LusNonContinuouslyMonitoredSystemsStatus =
                        LusNonContinuouslyMonitoredSystemsStatus|
                        LaaShiftMask
                          [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup];
                    DataValue->NonContinuouslyMonitoredSystemsStatus7 =
                        (uint8)(LusNonContinuouslyMonitoredSystemsStatus &
                          0x00FFU);
                    DataValue->NonContinuouslyMonitoredSystemsStatus8 =
                        (uint8)((LusNonContinuouslyMonitoredSystemsStatus &
                          0xFF00U) >> DEM_EIGHT);
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_12816 */
        LddRetVal = E_NOT_OK;
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_12799 */
      LddRetVal = E_NOT_OK;
    }
  }

  return LddRetVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmReadDiagnosticReadiness2                **
**                                                                            **
** Service ID           : 0x9c                                                **
**                                                                            **
** Description          : Service to report the value of DiagnosticReadiness2 **
**                        (DM5) computed by the Dem.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_J1939DcmDiagnosticReadiness2Type* DataValue,    **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04112
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* @Trace: Dem_SUD_MACRO_063 */
#if (DEM_J1939_READINESS2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness2(
  Dem_J1939DcmDiagnosticReadiness2Type* DataValue,
  uint8 ClientId )
{
  Std_ReturnType LddRetVal = E_OK;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00129 */
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS2_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  else if (NULL_PTR == DataValue)
  {
    /* @Trace: Dem_SUD_API_00130 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMREADDIAGNOSTICREADINESS2_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00131 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMREADDIAGNOSTICREADINESS2_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = E_NOT_OK;
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_00910
     * A call of Dem_J1939DcmReadDiagnosticReadiness2 shall report a response
     * message based on the J1939-73 [14] DM21 definition:
     * - "Distance Traveled While MIL is Activated" shall be identical to PID
     * 0x21, except the maximum value is 64255 (all values above 64255 shall be
     * reported as 64255).
     * - "Distance Since Diagnostic Trouble Codes Cleared" shall be identical
     * to PID 0x31, except the maximum value is 64255 (all values above 64255
     * shall be reported as 64255).
     * - "Minutes Run by Engine While MIL is Activated" shall be identical to
     * PID 0x4D, except the maximum value is 64255 (all values above 64255 shall
     * be reported as 64255).
     * - "Time Since Diagnostic Trouble Codes Cleared" shall be identical to PID
     * 0x4E, except the maximum value is 64255 (all values above 64255 shall be
     * reported as 64255).
     */
    uint8 LaaPIDValue[DEM_TWO] = {DEM_ZERO, DEM_ZERO};

    /*  Byte 1-2 : Distance Traveled While MIL is activated (PID 0x21)  */
    (void)Dem_DcmReadDataOfPID21(LaaPIDValue);

    DataValue->DistanceTraveledWhileMILisActivated =
        (uint16)LaaPIDValue[DEM_ONE] << DEM_EIGHT;
    DataValue->DistanceTraveledWhileMILisActivated |=
        LaaPIDValue[DEM_ZERO];
    

    /* @Trace: Dem_SUD_API_12820 */
    if (DataValue->DistanceTraveledWhileMILisActivated >
          DEM_J1939RDY_MAX_DISTANCE)
    {
      /* @Trace: Dem_SUD_API_00155 */
      DataValue->DistanceTraveledWhileMILisActivated =
          DEM_J1939RDY_MAX_DISTANCE;
    }
    /*  Byte 3-4 : Distance Since DTC Cleared (PID 0x31)  */

    (void)Dem_DcmReadDataOfPID31(LaaPIDValue);

    DataValue->DistanceSinceDTCsCleared=
        (uint16)LaaPIDValue[DEM_ONE] << DEM_EIGHT;
    DataValue->DistanceSinceDTCsCleared |= LaaPIDValue[DEM_ZERO];
    
    /* @Trace: Dem_SUD_API_12821 */
    if (DataValue->DistanceSinceDTCsCleared > DEM_J1939RDY_MAX_DISTANCE)
    {
      /* @Trace: Dem_SUD_API_00156 */
      DataValue->DistanceSinceDTCsCleared = DEM_J1939RDY_MAX_DISTANCE;
    }

    /*  Byte 5-6 : Minutes Run by Engine While MIL is Activated (PID 0x4D)  */

    (void)Dem_DcmReadDataOfPID4D(LaaPIDValue);

    DataValue->MinutesRunbyEngineWhileMILisActivated =
        (uint16)LaaPIDValue[DEM_ONE] << DEM_EIGHT;
    DataValue->MinutesRunbyEngineWhileMILisActivated |= LaaPIDValue[DEM_ZERO];
    
    /* @Trace: Dem_SUD_API_12822 */
    if (DataValue->MinutesRunbyEngineWhileMILisActivated >
          DEM_J1939RDY_MAX_TIME)
    {
      /* @Trace: Dem_SUD_API_00157 */
      DataValue->MinutesRunbyEngineWhileMILisActivated = DEM_J1939RDY_MAX_TIME;
    }

    /*  Byte 7-8 : Distance Since DTC Cleared (PID 0x4E)  */
    (void)Dem_DcmReadDataOfPID4E(LaaPIDValue);
    
    DataValue->TimeSinceDiagnosticTroubleCodesCleared =
        (uint16)LaaPIDValue[DEM_ONE] << DEM_EIGHT;
    DataValue->TimeSinceDiagnosticTroubleCodesCleared |=
        LaaPIDValue[DEM_ZERO];
    
    /* @Trace: Dem_SUD_API_12823 */
    if (DataValue->TimeSinceDiagnosticTroubleCodesCleared >
          DEM_J1939RDY_MAX_TIME)
    {
      /* @Trace: Dem_SUD_API_12824 */
      DataValue->TimeSinceDiagnosticTroubleCodesCleared = DEM_J1939RDY_MAX_TIME;
    }

  }
  
  return LddRetVal;
}
#endif
#endif


/*******************************************************************************
** Function Name        : Dem_J1939DcmReadDiagnosticReadiness3                **
**                                                                            **
** Service ID           : 0x9d                                                **
**                                                                            **
** Description          : Service to report the value of DiagnosticReadiness3 **
**                        (DM5) computed by the Dem.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_J1939DcmDiagnosticReadiness3Type* DataValue,    **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04112 SRS_Diag_04220
 */
/* @Trace: Dem_SUD_MACRO_064 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_J1939_READINESS3_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness3(
  Dem_J1939DcmDiagnosticReadiness3Type* DataValue,
  uint8 ClientId )
{
  Std_ReturnType LddRetVal = E_OK;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_30001 */
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS3_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  else if (NULL_PTR == DataValue)
  {
    /* @Trace: Dem_SUD_API_30002 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMREADDIAGNOSTICREADINESS3_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_30003 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMREADDIAGNOSTICREADINESS3_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = E_NOT_OK;
  }
  #endif
  else
  {
    uint16 LusEvIndex;
    uint8 LaaPIDValue[DEM_FOUR] = {DEM_ZERO, DEM_ZERO, DEM_ZERO, DEM_ZERO};

    const boolean LaaRdGrp[] =
    {
      DEM_FALSE,   /* DEM_OBD_RDY_NONE        0x00    */
      DEM_TRUE,    /* DEM_OBD_RDY_CAT         0x01    */
      DEM_TRUE,    /* DEM_OBD_RDY_HTCAT       0x02    */
      DEM_TRUE,    /* DEM_OBD_RDY_MISF        0x03    */
      DEM_TRUE,    /* DEM_OBD_RDY_EVAP        0x04    */
      DEM_TRUE,    /* DEM_OBD_RDY_SECAIR      0x05    */
      DEM_TRUE,    /* DEM_OBD_RDY_FLSYS       0x06    */
      DEM_TRUE,    /* DEM_OBD_RDY_EGSENS      0x07    */
      DEM_TRUE,    /* DEM_OBD_RDY_EGR         0x08    */
      DEM_FALSE,
      DEM_TRUE,    /* DEM_OBD_RDY_AC          0x0A    */
      DEM_FALSE,
      DEM_FALSE,
      DEM_TRUE,    /* DEM_OBD_RDY_O2SENS      0x0D    */
      DEM_TRUE,    /* DEM_OBD_RDY_CMPRCMPT    0x0E    */
      DEM_TRUE,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      DEM_TRUE,    /* DEM_OBD_RDY_HTCAT       0x10    */
      DEM_TRUE,    /* DEM_OBD_RDY_NOXCAT      0x11    */
      DEM_TRUE,    /* DEM_OBD_RDY_BOOSTPR     0x12    */
      DEM_FALSE,     
      DEM_TRUE     /* DEM_OBD_RDY_PMFLT       0x14    */
    };
    

    const uint16 LaaShiftMask[] =
    {
      0x00,      /* DEM_OBD_RDY_NONE        0x00    */
      0x0001U,   /* DEM_OBD_RDY_CAT        0x01    */
      0x0002U,   /* DEM_OBD_RDY_HTCAT      0x02    */
      0x01U,     /* DEM_OBD_RDY_MISF         0x03    */
      0x04,      /* DEM_OBD_RDY_EVAP        0x04    */
      0x0008,    /* DEM_OBD_RDY_SECAIR      0x05    */
      0x02,      /* DEM_OBD_RDY_FLSYS       0x06    */
      0x0020U,    /* DEM_OBD_RDY_EGSENS      0x07    */
      0x0080,     /* DEM_OBD_RDY_EGR         0x08    */
      0x0,
      0x0010,     /* DEM_OBD_RDY_AC          0x0A    */
      0,
      0,
      0x100,     /* DEM_OBD_RDY_O2SENS      0x0D    */
      0x04,      /* DEM_OBD_RDY_CMPRCMPT    0x0E    */
      0x0040,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      0x0002,    /* DEM_OBD_RDY_HCCAT       0x10    */
      0x0800,    /* DEM_OBD_RDY_NOXCAT      0x11    */
      0x0200,    /* DEM_OBD_RDY_BOOSTPR     0x12    */
      0,    
      0x4000     /* DEM_OBD_RDY_PMFLT       0x14    */
    };


    const uint16 LaaRdGrpDisable[] =
    {
      0x00,                       /* DEM_OBD_RDY_NONE        0x00    */
      DEM_J1939RDY_DISABLE_CAT,   /* DEM_OBD_RDY_CAT        0x01    */
      DEM_J1939RDY_DISABLE_HTCAT,   /* DEM_OBD_RDY_HTCAT      0x02    */
      DEM_J1939RDY_DISABLE_MISF,     /* DEM_OBD_RDY_MISF         0x03    */
      DEM_J1939RDY_DISABLE_EVAP,      /* DEM_OBD_RDY_EVAP        0x04    */
      DEM_J1939RDY_DISABLE_SECAIR,    /* DEM_OBD_RDY_SECAIR      0x05    */
      DEM_J1939RDY_DISABLE_FLSYS,      /* DEM_OBD_RDY_FLSYS       0x06    */
      DEM_J1939RDY_DISABLE_EGSENS,    /* DEM_OBD_RDY_EGSENS      0x07    */
      DEM_J1939RDY_DISABLE_EGR,       /* DEM_OBD_RDY_EGR         0x08    */
      0x0,
      DEM_J1939RDY_DISABLE_AC,        /* DEM_OBD_RDY_AC          0x0A    */
      0,
      0,
      DEM_J1939RDY_DISABLE_O2SENS,        /* DEM_OBD_RDY_O2SENS      0x0D    */
      DEM_J1939RDY_DISABLE_CMPRCMPT,      /* DEM_OBD_RDY_CMPRCMPT    0x0E    */
      DEM_J1939RDY_DISABLE_O2SENSHT,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      DEM_J1939RDY_DISABLE_HCCAT,       /* DEM_OBD_RDY_HCCAT       0x10    */
      DEM_J1939RDY_DISABLE_NOXCAT,      /* DEM_OBD_RDY_NOXCAT      0x11    */
      DEM_J1939RDY_DISABLE_BOOSTPR,      /* DEM_OBD_RDY_BOOSTPR     0x12    */
      0, 
      DEM_J1939RDY_DISABLE_PMFLT       /* DEM_OBD_RDY_PMFLT       0x14    */
    };

    
    /* @Trace: SWS_Dem_00911
     * A call of Dem_J1939DcmReadDiagnosticReadiness3 shall report a response
     * message based on the J1939-73 [14] DM26 definition:
     * - "Time Since Engine Start" shall be retrieved by the
     * DemOBDTimeSinceEngineStart (in DemGeneralOBD)
     * - "Number of Warmups Since DTCs Cleared" shall be identical to PID 0x30,
     * except the maximum value is 250 (all values above 250 shall be reported
     * as 250).
     * - The (Non-)Continuously Monitored Systems Enable/Completed status shall
     * be reported according to SAE J1939-73 [14] chapter 5.7.26.3 to 5.7.26.5.
     * The calculation shall be based on those events referencing the
     * corresponding configuration parameter DemEventOBDReadinessGroup. In case
     * there is no reference by any event parameter it shall shall indicate
     * disabled and complete. Otherwise the disable state shall be based on the
     * readiness group disabled status according to [SWS_Dem_00356], and the
     * complete status shall be set to "monitor complete" (0) if all assigned
     * event parameter have the TestNotCompletedSinceThisOperationCycle status
     * bit set to zero (0); otherwise the status bit shall be set to "monitor
     * not complete" (1).
     */
    /*  Byte 1-2 :   */
    (void)Dem_ReadDataOfTimeEngineStart(LaaPIDValue);
 
    DataValue->TimeSinceEngineStart = (uint16)LaaPIDValue[DEM_ONE] << DEM_EIGHT;
    DataValue->TimeSinceEngineStart |= LaaPIDValue[DEM_ZERO];
    /* @Trace: Dem_SUD_API_12825 */
    if (DataValue->TimeSinceEngineStart > DEM_J1939RDY_MAX_TIME)
    {
      /* @Trace: Dem_SUD_API_12831 */
      DataValue->TimeSinceEngineStart = DEM_J1939RDY_MAX_TIME;
    }


    /*  Byte 3 :   */
    (void)Dem_DcmReadDataOfPID30(LaaPIDValue);
    /* @Trace: Dem_SUD_API_12832 */
    if (LaaPIDValue[DEM_ZERO] > DEM_J1939RDY_MAX_WARMUP_NUMBER)
    {
      /* @Trace: Dem_SUD_API_12833 */
      LaaPIDValue[DEM_ZERO] = DEM_J1939RDY_MAX_WARMUP_NUMBER;
    }
    DataValue->NumberofWarmupsSinceDTCsCleared = LaaPIDValue[DEM_ZERO];

    DataValue->ContinuouslyMonitoredSystemsEnableCompletedStatus = DEM_ZERO;
    DataValue->NonContinuouslyMonitoredSystemsEnableStatus5 = DEM_ZERO;
    DataValue->NonContinuouslyMonitoredSystemsEnableStatus6 = DEM_ZERO;
    DataValue->NonContinuouslyMonitoredSystems7 = DEM_ZERO;
    DataValue->NonContinuouslyMonitoredSystems8 = DEM_ZERO;
    
    uint16 LusNonContinuouslyMonitoredSystemsEnableStatus = DEM_ZERO;
    uint16 LusNonContinuouslyMonitoredSystems = DEM_ZERO;
    /*  Byte 4 :   */    
    /* @Trace: Dem_SUD_API_12834 */
    for (LusEvIndex = DEM_ZERO; LusEvIndex < DEM_NUMBER_OF_EVENTS ; LusEvIndex++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) LddCbDTC =
          Dem_GetCbDTCByEventId(LusEvIndex + DEM_ONE);
      /* @Trace: Dem_SUD_API_12835 */
      if ((NULL_PTR != LddCbDTC) && (DEM_NO_DTC != LddCbDTC->usObdDtc))
      {      
        #if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
        /* Refer to Dem_SetDTCSuppression */
        /* @Trace: SWS_Dem_01101
         * A suppressed DTC shall not be visible for the following Dcm query-
         * functions; therefore the following functions shall treat the DTC as
         * if filter is not matching.
         * */
        /* @Trace: Dem_SUD_API_12836 */
        if (DEM_FALSE ==
              Dem_EvIsProcStateTriggered(
                  LusEvIndex + DEM_ONE, DEM_EVPROCSTATE_DTC_SUPP))
        #endif
        {
        
          Dem_UdsStatusByteType LddDtcStatusByte =
              Dem_GetDTCStatus(LusEvIndex + DEM_ONE);
          boolean LblTested = DEM_ZERO;
          /* @Trace: Dem_SUD_API_12837 */
          if (((uint8)DEM_UDS_STATUS_TNCTOC & LddDtcStatusByte) == DEM_ZERO)
          {
            LblTested = DEM_ONE;
          }
          /* @Trace: Dem_SUD_API_12838 */
          /* @Trace: Dem_SUD_API_12826 */
          if ((LaaRdGrp[Dem_Event[LusEvIndex].ulEventOBDReadinessGroup] ==
                 DEM_TRUE) &&
              ((Dem_GulEventIdDisabled &
                  LaaRdGrpDisable
                    [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup]) !=
                  LaaRdGrpDisable
                    [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup]))
          {
            if ((DEM_OBD_RDY_MISF ==
                   Dem_Event[LusEvIndex].ulEventOBDReadinessGroup) ||
                (DEM_OBD_RDY_FLSYS ==
                   Dem_Event[LusEvIndex].ulEventOBDReadinessGroup)
              || (DEM_OBD_RDY_CMPRCMPT ==
                    Dem_Event[LusEvIndex].ulEventOBDReadinessGroup))
            {
              DataValue->ContinuouslyMonitoredSystemsEnableCompletedStatus =
                  DataValue->ContinuouslyMonitoredSystemsEnableCompletedStatus|
                  (uint8)LaaShiftMask
                    [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup];
              /* @Trace: Dem_SUD_API_12829 */
              if (DEM_ZERO == LblTested)
              {
                /* @Trace: Dem_SUD_API_12830 */
                DataValue->ContinuouslyMonitoredSystemsEnableCompletedStatus =
                    DataValue->ContinuouslyMonitoredSystemsEnableCompletedStatus|
                    (uint8)(LaaShiftMask
                        [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup]<<4);
              }

            }
            else
            {
              LusNonContinuouslyMonitoredSystemsEnableStatus =
                  LusNonContinuouslyMonitoredSystemsEnableStatus|
                  LaaShiftMask[Dem_Event[LusEvIndex].ulEventOBDReadinessGroup];
              DataValue->NonContinuouslyMonitoredSystemsEnableStatus5 =
                  (uint8)(LusNonContinuouslyMonitoredSystemsEnableStatus &
                      0x00FFU);
              DataValue->NonContinuouslyMonitoredSystemsEnableStatus6 =
                  (uint8)((LusNonContinuouslyMonitoredSystemsEnableStatus &
                      0xFF00U) >> DEM_EIGHT);
              /* @Trace: Dem_SUD_API_12827 */
              if (DEM_ZERO == LblTested)
              {
                /* @Trace: Dem_SUD_API_12828 */
                LusNonContinuouslyMonitoredSystems =
                    LusNonContinuouslyMonitoredSystems|
                    LaaShiftMask
                      [Dem_Event[LusEvIndex].ulEventOBDReadinessGroup];
                DataValue->NonContinuouslyMonitoredSystems7 =
                    (uint8)(LusNonContinuouslyMonitoredSystems & 0x00FFU);
                DataValue->NonContinuouslyMonitoredSystems8 =
                    (uint8)((LusNonContinuouslyMonitoredSystems & 0xFF00U) >>
                        DEM_EIGHT);
              }
            }
          }
        }
      }
    }
  }

  return LddRetVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextSPNInFreezeFrame                 **
**                                                                            **
** Service ID           : 0x98                                                **
**                                                                            **
** Description          : Gets next SPN                                       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : DestBuffer                                          **
**                        BufSize                                             **
**                                                                            **
** Output Parameters    : uint32* SPNSupported,                               **
**                        uint8* SPNDataLength                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                         E_OK                                               **
**                         DEM_NO_SUCH_ELEMENT                                **
**                         DEM_PENDING                                        **
**                         DEM_BUFFER_TOO_SMALL                               **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04111
 */
#if (DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(
  uint32* SPNSupported,
  uint8* SPNDataLength,
  uint8 ClientId)
{
  Std_ReturnType LddRetVal  = DEM_NO_SUCH_ELEMENT;

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00110 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_UNINIT);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else if ( (NULL_PTR == SPNSupported) || (NULL_PTR == SPNDataLength))
  {
    /* @Trace: Dem_SUD_API_00111 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_PARAM_POINTER);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_00112 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_WRONG_CONFIGURATION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  #endif
  /* @Trace: SWS_Dem_00905
   * In case the search of [SWS_Dem_00904] needs to be interrupted due to
   * internal implementations or limitations, the return value can be set to
   * DEM_PENDING. The out parameter needs not to be valid in this case. The next
   * call of Dem_J1939DcmGetNextSPNInFreezeFrame should continue after the
   * interrupted element.
   */
  else if ((DEM_JOB_TRIGGER ==
              Dem_FilteredFFRecord[ClientId].j1939FF_JobAction) ||
           (DEM_JOB_RUNNING ==
              Dem_FilteredFFRecord[ClientId].j1939FF_JobAction))
  {
    /* Return appropriate value */
    LddRetVal = DEM_PENDING;
  }
  /* @Trace: SWS_Dem_00906
   * The function Dem_J1939DcmGetNextSPNInFreezeFrame shall trigger the Det
   * error DEM_E_WRONG_CONDITION in case of not supported FreezeFrameKind.
   * Valid value is Dem_SPNsInExpandedFreezeFrame.
   */
  else if (DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME !=
             Dem_FilteredFFRecord[ClientId].kindOfJ1939FreezeFrame)
  {
    /* @Trace: Dem_SUD_API_00138 */
    DEM_REPORT_ERROR(
        DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_WRONG_CONDITION);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent)
  {
    /* @Trace: Dem_SUD_API_00113 */
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_PARAM_DATA);
    /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         (DEM_NUM_OF_J1939FREEZEFRAMECLASS > DEM_ZERO))
    Dem_EventIdType LddEventId;
    Dem_EventMemoryEntryPtrType LddEntry;
    Dem_SizeOfJ1939FreezeFrameDataType LddBufSize;

    Dem_NumOfEventMemoryEntryType LddIdxOfEntry =
        Dem_PriEvMemChronoOrderNextLoc;
    struct {
      Dem_EventIdType LddPrioEventId;
      Dem_EventPriorityType LddPriority;
      Dem_J1939DcmSetFreezeFrameFilterType LddFilerType;
    } LstHighestEvent = {DEM_ZERO, DEM_ZERO, DEM_ZERO};


    /*  if event is deleled or aged, Dem returns the next event.*/
    /* @Trace: SWS_Dem_00904
     * Each call to Dem_J1939DcmGetNextSPNInFreezeFrame shall step to the next
     * SPN of the ExpandedFreezeFrame for this DemEventMemory. In case no more
     * SPN of the ExpandedFreezeFrame definition is available, the function
     * return value shall be DEM_NO_SUCH_ELEMENT. The out parameter needs not
     * to be valid in this case.
     */
    /* @Trace: Dem_SUD_API_12784 */
    while (LddIdxOfEntry > DEM_ZERO)
    {
      Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;

      --LddIdxOfEntry;
      /* @Trace: Dem_SUD_API_12785 */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddIdxOfEntry)
      {
        LddMemLoc= Dem_PriEvMemChronoOrder[LddIdxOfEntry];
      }
      /* @Trace: Dem_SUD_API_12786 */
      if (DEM_NO_EVMEM_ENTRY != LddMemLoc)
      {
        LddEventId =
            Dem_EvMem_GetEventIdByEvMemEntry(
                DEM_DTC_ORIGIN_PRIMARY_MEMORY, LddMemLoc);
        /* @Trace: Dem_SUD_API_12787 */
        if ((LddEventId <= DEM_NUMBER_OF_EVENTS) &&
            (DEM_NO_EVENT != LddEventId))
        {
          /* @Trace: Dem_SUD_API_12788 */
          if (DEM_TRUE ==
                Dem_EvIsProcStateTriggered(
                    LddEventId, DEM_EVPROCSTATE_J1939EXFF_FILTER))
          {
            Dem_EventParameterCPCType LddEvent =
                &Dem_Event[LddEventId - DEM_ONE];

            if (DEM_NO_EVENT != LstHighestEvent.LddPrioEventId)
            {
              /* @Trace: Dem_SUD_API_12789 */
              if (LddEvent->ucEventPriority < LstHighestEvent.LddPriority)
              {
                /* @Trace: Dem_SUD_API_12791 */
                LstHighestEvent.LddPrioEventId = LddEventId;
                LstHighestEvent.LddPriority = LddEvent->ucEventPriority;
              }
            }
            else
            {
              /* @Trace: Dem_SUD_API_12790 */
              LstHighestEvent.LddPrioEventId = LddEventId;
              LstHighestEvent.LddPriority = LddEvent->ucEventPriority;
            }
          }
        }
      } 
    }
    /* @Trace: Dem_SUD_API_13272 */
    if (DEM_NO_EVENT != LstHighestEvent.LddPrioEventId)
    {  
    
      Dem_EvClearProcState(
          LstHighestEvent.LddPrioEventId, DEM_EVPROCSTATE_J1939EXFF_FILTER);

      LddEntry =
          Dem_EvMem_FindEntry(
              LstHighestEvent.LddPrioEventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      /* @Trace: Dem_SUD_API_13273 */
      if (NULL_PTR != LddEntry)
      {
        Dem_EventParameterPCType LddEvent =
            &Dem_Event[LstHighestEvent.LddPrioEventId - DEM_ONE];
        /* @Trace: Dem_SUD_API_13274 */
        if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
        {
          /* @Trace: SWS_Dem_00907
           * In case Dem_J1939DcmGetNextSPNInFreezeFrame has found an SPN of the
           * ExpandedFreezeFrame definition, the Dem shall:
           * - Check if the buffer in the BufSize parameter is big enough to
           * hold the (Expanded)FreezeFrame. If not,
           * DEM_FILTERED_BUFFER_TOO_SMALL shall be returned without any further
           * actions. The out parameters need not to be valid in this case.
           * - Copy the (Expanded)FreezeFrame data into the buffer provided by
           * the parameter DestBuffer (in case of Expanded FreezeFrames without
           * any SPN informations). Unused bits shall be filled with "0".
           * - Set the parameter J1939DTC to the corresponding J1939DTC value
           * (refer DemDTCAttributes for details) and the parameter
           * OccurrenceCounter to the corresponding occurrence counter value.
           * - Return with E_OK. In case the occurrence counter is above +126
           * (0x7F), the returned value shall be set to +126 (0x7F).
           */
          LddRetVal =
              Dem_GetSizeOfJ1939FreezeFrameData(
                  LddEvent, &LddBufSize, DEM_J1939DCM_EXPANDED_FREEZEFRAME);
          /* @Trace: Dem_SUD_API_13275 */
          if (E_OK == LddRetVal)
          {
            *SPNSupported = DEM_NO_DTC;
            uint16 LusDtcLoc =
                Dem_Event[LstHighestEvent.LddPrioEventId - DEM_ONE].e_PointToDTC;
            /* @Trace: Dem_SUD_API_13276 */
            if (LusDtcLoc < DEM_MAX_NUMBER_OF_DTC)
            {
              /* @Trace: Dem_SUD_API_13277 */
              *SPNSupported = Dem_GaaCombinedDtc[LusDtcLoc].J1939DTCValue;
            }
            *SPNDataLength = (uint8)LddBufSize;
          }
        }
      }
    }
    #endif
  }    
  return LddRetVal;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_AddNewChronologicalOrder                  **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Add new chronological oder                          **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : - DTCOrigin                                         **
 **                       - MemLocation                                       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_AddNewChronologicalOrder(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation)
{
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00261 */
    if (Dem_PriEvMemChronoOrderNextLoc < Dem_SizeOfEventMemory[DTCOrigin])
    {
      /* @Trace: Dem_SUD_API_00018 */
      Dem_PriEvMemChronoOrder[Dem_PriEvMemChronoOrderNextLoc] = MemLocation;
      Dem_PriEvMemChronoOrderNextLoc++;
    }
  }
  /* @Trace: Dem_SUD_API_13278 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_13279 */
  /* polyspace +1 MISRA-C3:15.7 [Justified:Low] Justify with annotations */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_00260 */
    /* @Trace: Dem_SUD_API_13280*/
    if (Dem_UDEvMemChronoOrderNextLoc <
          Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_USERDEFINED_MEMORY])
    {
      /* @Trace: Dem_SUD_API_13281*/
      Dem_UDEvMemChronoOrder[Dem_UDEvMemChronoOrderNextLoc] = MemLocation;
      Dem_UDEvMemChronoOrderNextLoc++;
    }
  }
  #endif
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_DelChronologicalOrder                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Delete chronological oder                           **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : - DTCOrigin                                         **
 **                       - MemLocation                                       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_DelChronologicalOrder(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation)
{
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    Dem_NumOfEventMemoryEntryType LddMemLoc;
    /* @Trace: Dem_SUD_API_00257*/
    if (Dem_PriEvMemChronoOrderNextLoc <=  Dem_SizeOfEventMemory[DTCOrigin])
    {
      /* @Trace: Dem_SUD_API_00258*/
      for (LddMemLoc = DEM_ZERO;
           LddMemLoc < Dem_SizeOfEventMemory[DTCOrigin];
           LddMemLoc++)
      {
        /* @Trace: Dem_SUD_API_00012*/
        if (Dem_PriEvMemChronoOrder[LddMemLoc] == MemLocation)
        {
          Dem_NumOfEventMemoryEntryType LddMemLocShift;
          if (Dem_PriEvMemChronoOrderNextLoc >= DEM_TWO)
          {
            /* if Dem_PriEvMemChronoOrderNextLoc is 255, Event Memory is full ,
             * valid range is 0~254 */
            for (LddMemLocShift = LddMemLoc;
                 LddMemLocShift < (Dem_PriEvMemChronoOrderNextLoc - DEM_ONE);
                 LddMemLocShift++)
            {
              /* @Trace: Dem_SUD_API_00014*/
              Dem_PriEvMemChronoOrder[LddMemLocShift] =
                  Dem_PriEvMemChronoOrder[LddMemLocShift + DEM_ONE];
            }
            /* @Trace: Dem_SUD_API_00015*/
            Dem_PriEvMemChronoOrderNextLoc--;
            Dem_PriEvMemChronoOrder[Dem_PriEvMemChronoOrderNextLoc] =
                DEM_NO_EVMEM_ENTRY;
          }        
          else if (Dem_PriEvMemChronoOrderNextLoc == DEM_ONE)
          {
            /* @Trace: Dem_SUD_API_00016*/
            Dem_PriEvMemChronoOrderNextLoc = DEM_ZERO;
            Dem_PriEvMemChronoOrder[DEM_ZERO] = DEM_NO_EVMEM_ENTRY;
          }
          else
          {
            /* @Trace: Dem_SUD_API_00017*/
            /* Never be reached */
            Dem_PriEvMemChronoOrderNextLoc = DEM_ZERO;
            Dem_PriEvMemChronoOrder[DEM_ZERO] = DEM_NO_EVMEM_ENTRY;
          }
          break;
        }
      }
    }
  }
  /* @Trace: Dem_SUD_API_13309*/
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_13308*/
  /* polyspace +1 MISRA-C3:15.7 [Justified:Low] Justify with annotations */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_00256*/
    Dem_NumOfEventMemoryEntryType LddMemLoc;
    /* @Trace: Dem_SUD_API_13301*/
    if (Dem_UDEvMemChronoOrderNextLoc <=
          Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_USERDEFINED_MEMORY])
    {
      /* @Trace: Dem_SUD_API_13302*/
      for (LddMemLoc = DEM_ZERO;
           LddMemLoc < Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
           LddMemLoc++)
      {
        /* @Trace: Dem_SUD_API_13303*/
        if (Dem_UDEvMemChronoOrder[LddMemLoc] == MemLocation)
        {
          Dem_NumOfEventMemoryEntryType LddMemLocShift;

          if (Dem_UDEvMemChronoOrderNextLoc >= DEM_TWO)
          {
            /* if Dem_PriEvMemChronoOrderNextLoc is 255, Event Memory is full ,
             * valid range is 0~254 */
            /* @Trace: Dem_SUD_API_13305*/
            for (LddMemLocShift = LddMemLoc;
                 LddMemLocShift < (Dem_UDEvMemChronoOrderNextLoc - DEM_ONE);
                 LddMemLocShift++)
            {
              /* @Trace: Dem_SUD_API_13307*/
              Dem_UDEvMemChronoOrder[LddMemLocShift] =
                  Dem_UDEvMemChronoOrder[LddMemLocShift + DEM_ONE];
            }
            Dem_UDEvMemChronoOrderNextLoc--;
            Dem_UDEvMemChronoOrder[Dem_UDEvMemChronoOrderNextLoc] =
                DEM_NO_EVMEM_ENTRY;
          }
          else if (Dem_UDEvMemChronoOrderNextLoc == DEM_ONE)
          {
            /* @Trace: Dem_SUD_API_13306*/
            Dem_UDEvMemChronoOrderNextLoc = DEM_ZERO;
            Dem_UDEvMemChronoOrder[DEM_ZERO] = DEM_NO_EVMEM_ENTRY;
          }
          else
          {
            /* @Trace: Dem_SUD_API_13304*/
            /* Never be reached */
            Dem_UDEvMemChronoOrderNextLoc = DEM_ZERO;
            Dem_UDEvMemChronoOrder[DEM_ZERO] = DEM_NO_EVMEM_ENTRY;
          }
          break;
        }
      }
    }
  }
  #endif
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_InitChronologicalOrder                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Init chronological oder                             **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DTCOrigin                                           **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_InitChronologicalOrder(
  Dem_DTCOriginType DTCOrigin)
{
  uint32 LulTimeStampMax = DEM_MAX_TIMESTAMP;
  Dem_NumOfEventMemoryEntryType LddMemLoc;

  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00251*/
    if (Dem_NumOfStoredEvtMemEntryies[DTCOrigin] <=
          Dem_SizeOfEventMemory[DTCOrigin])
    {
      /* @Trace: Dem_SUD_API_00002*/
      /* @Trace: Dem_SUD_API_00252*/
      for (LddMemLoc = DEM_ZERO;
           LddMemLoc < Dem_SizeOfEventMemory[DTCOrigin];
           LddMemLoc++)
      {
        /* @Trace: Dem_SUD_API_00003*/
        Dem_PriEvMemChronoOrder[LddMemLoc] = DEM_NO_EVMEM_ENTRY;
      }

      Dem_NumOfEventMemoryEntryType LddNumStoredEntries =
          Dem_NumOfStoredEvtMemEntryies[DTCOrigin];
      while (LddNumStoredEntries > DEM_ZERO)
      {
        uint32 LulTimeStampOld = DEM_ZERO;
        Dem_NumOfEventMemoryEntryType LddMemLocOld = DEM_NO_EVMEM_ENTRY;
        /* @Trace: Dem_SUD_API_00004*/
        for (LddMemLoc = DEM_ZERO;
             LddMemLoc < Dem_SizeOfEventMemory[DTCOrigin];
             LddMemLoc++)
        {
          Dem_EventIdType LddEventId =
              Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, LddMemLoc);
          /* @Trace: Dem_SUD_API_00253*/
          if (DEM_NO_EVENT != LddEventId)
          {
            Dem_EventMemoryEntryPtrType LddEntry =
                Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, LddMemLoc);
            /* @Trace: Dem_SUD_API_00254*/
            if (NULL_PTR != LddEntry)
            {
              uint32 LulCurrent = LddEntry->TimeStamp;
              /* @Trace: Dem_SUD_API_00255*/
              if ((LulTimeStampMax > LulCurrent) &&
                  (LulCurrent > LulTimeStampOld))
              {
                LulTimeStampOld = LulCurrent;
                LddMemLocOld = LddMemLoc;
              }
            }
          }
          /* @Trace: Dem_SUD_API_00008*/
        }
        /* @Trace: Dem_SUD_API_00009*/
        LulTimeStampMax = LulTimeStampOld;
        --LddNumStoredEntries;
        Dem_PriEvMemChronoOrder[LddNumStoredEntries] = LddMemLocOld;
      }
      /* @Trace: Dem_SUD_API_00010*/
      Dem_PriEvMemChronoOrderNextLoc = Dem_NumOfStoredEvtMemEntryies[DTCOrigin];
    }
  }
  /* @Trace: Dem_SUD_API_13282*/
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_13284*/
  /* polyspace +1 MISRA-C3:15.7 [Justified:Low] Justify with annotations */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  { /* @Trace: Dem_SUD_API_00250*/
    /* @Trace: Dem_SUD_API_13285*/
    if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] <=
          Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_USERDEFINED_MEMORY])
    {
      /* @Trace: Dem_SUD_API_13286*/
      for (LddMemLoc = DEM_ZERO;
           LddMemLoc < Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
           LddMemLoc++)
      {
       /* @Trace: Dem_SUD_API_13287*/
        Dem_UDEvMemChronoOrder[LddMemLoc] = DEM_NO_EVMEM_ENTRY;
      }

      Dem_NumOfEventMemoryEntryType LddNumStoredEntries =
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
      /* @Trace: Dem_SUD_API_13288*/
      while (LddNumStoredEntries > DEM_ZERO)
      {
        uint32 LulTimeStampOld = DEM_ZERO;
        Dem_NumOfEventMemoryEntryType LddMemLocOld = DEM_NO_EVMEM_ENTRY;
        for (LddMemLoc = DEM_ZERO;
             LddMemLoc <
               Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
             LddMemLoc++)
        {
          Dem_EventIdType LddEventId =
              Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, LddMemLoc);
          /* @Trace: Dem_SUD_API_13290*/
          if (DEM_NO_EVENT != LddEventId)
          {
            Dem_EventMemoryEntryPtrType LddEntry =
                Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, LddMemLoc);
            /* @Trace: Dem_SUD_API_13291*/
            if (NULL_PTR != LddEntry)
            {
              uint32 LulCurrent = LddEntry->TimeStamp;
              /* @Trace: Dem_SUD_API_13283*/
              if ((LulTimeStampMax > LulCurrent) &&
                  (LulCurrent > LulTimeStampOld))
              {
                LulTimeStampOld = LulCurrent;
                LddMemLocOld = LddMemLoc;
              }
            }
          }
        }
        /* @Trace: Dem_SUD_API_13289*/
        LulTimeStampMax = LulTimeStampOld;
        --LddNumStoredEntries;
        Dem_UDEvMemChronoOrder[LddNumStoredEntries] = LddMemLocOld;
      }
      Dem_UDEvMemChronoOrderNextLoc =
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
    }
  }
  #endif
}


#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/* 
   polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations>
   Number of character is AUTOSAR standard
   polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations>
   Not a defect
   polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations>
   Not a defect
   polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations>
   Not a defect
*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

