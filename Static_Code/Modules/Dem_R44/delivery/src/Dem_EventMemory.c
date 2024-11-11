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
**  SRC-MODULE: Dem_EventMemory.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of storage of non-volatile data to NvM              **
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
** 1.0.8.0   13-Dec-2021   SY Kim        Jira #CP44-1167 #CP44-1169           **
** 1.0.3     29-Mar-2022   LanhLT        R44-Redmine #25611                   **
** 1.0.1     07-May-2021   HaoLT6        R44-Redmine #18724                   **
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
#include "NvM.h"            /* NVRAM manager symbols Header File */

#include "BswM.h"

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Rte_Dem.h"

#include "Dem_Event.h"
#include "Dem_EventCallback.h"
#include "Dem_NvData.h"
#include "Dem_EventRelatedData.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"

#if (DEM_J1939_SUPPORT == STD_ON)
#include "Dem_J1939Dcm.h"
#include "Dem_J1939Types.h"
#include "Dem_J1939Ram.h"
#endif

/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DEM_CODE) Dem_EvMem_ClearEvMemEntriesByClearDTC(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  boolean ClearDTCOccurrenceTime);

static FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ClearDTCOfAllGroup(
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin,
  #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
  Dem_J1939DcmSetClearFilterType DTCTypeFilter,
  #endif
  uint8 ClientId
);

static FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ClearSingleDTC(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin); 

static FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ClearDTCOfDTCGroup(
  Dem_DTCGroupType DTCGroup,
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin);
  
static  FUNC(boolean, DEM_CODE) Dem_EvMem_WriteAll(
  const uint8 Filter); 

static  FUNC(boolean, DEM_CODE) Dem_EvMem_ReadAll(
  const uint8 Filter);     

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearEvMemEntriesByClearDTC               **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the dtcs from event memory                    **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : ClientId, DTCOrigin, ClearDTCOccurrenceTime         **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_Diag_04125
 */
/* @Trace: Dem_SUD_MACRO_017 */
static FUNC(void, DEM_CODE) Dem_EvMem_ClearEvMemEntriesByClearDTC(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  boolean ClearDTCOccurrenceTime)
{
  Dem_NumOfEventMemoryEntryType LddMemLoc;
  Dem_EventIdType LddEventId;
  Dem_NumOfEventMemoryEntryType LddStartIdx = DEM_ZERO;
  Dem_NumOfEventMemoryEntryType LddStopIdx = DEM_ZERO;

  /* Dem_EvMem_DTCOriginIsValid is duplcated code (checked by Dem_ClearDTC) , 
   * but this is added to prevent the orange error of the polyspace */
  /* if (DEM_TRUE ==
      Dem_EvMem_DTCOriginIsValid(Dem_ClearDtcState.cds_DTCOrigin)) */
  /* @Trace: Dem_SUD_API_10929 */
  if ((DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
     #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      || (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
     #endif
     #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      || (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
     #endif
     )
  {
    /* @Trace: Dem_SUD_API_10951 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_10940 */
    uint32 LulMaxTimeStamp = DEM_ZERO;
    #endif

    LddStartIdx = Dem_EvMem_GetStartIndexEvMemory(ClientId, DTCOrigin);
    LddStopIdx = Dem_EvMem_GetStopIndexEvMemory(ClientId, DTCOrigin);
    /* @Trace: Dem_SUD_API_10962 */
    for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
    {
      LddEventId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin,LddMemLoc);
      /* if (DEM_TRUE == Dem_EventIdIsValid(EventId)) */
      /* @Trace: Dem_SUD_API_10971 */
      if ((LddEventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != LddEventId))
      {
        Dem_EventMemoryEntryPtrType LddEntry =
            Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, LddMemLoc);
        /* SingleDTC or All DTCs are able to be deleted via flag
         * DEM_EVPROCSTATE_EVENT_DEL */
        if (DEM_TRUE == Dem_EvIsProcStateTriggered(
              LddEventId,
              DEM_EVPROCSTATE_EVENT_DEL))
        {       
          /* ISO-14229,160p:
           * first/most recent failed/comfirmed DTC information shall be cleared 
           * upon a successful ClearDiagnosticInformation request from the
           * client */
          #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
          /* @Trace: Dem_SUD_API_10932 */
          if ((DEM_TRUE == ClearDTCOccurrenceTime)
             #if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > DEM_ZERO)
             && (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
             #endif
          )
          {
            Dem_DTCType LddDtcVal = DEM_ZERO;
            /* Dem_GetEventDTC always is true because 
             * event with DTC is able to store in the memory */
            (void)Dem_GetEventDTC(
                &Dem_Event[LddEventId - 1U], &LddDtcVal, DEM_DTC_FORMAT_UDS);
            /* @Trace: Dem_SUD_API_10934 */
            if (DEM_TRUE == Dem_EvMem_ClearDTCOccurrenceTime(
                  ClientId,
                  LddDtcVal,
                  DEM_FALSE))
            {
              /* @Trace: Dem_SUD_API_10933 */
              Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
                  DEM_EVMEM_STATUS_CLEARDTC);
            }            
          }
          #else
          /* @Trace: Dem_SUD_API_10972 */
          (void)ClearDTCOccurrenceTime;
          #endif
          /* No need critical section */
          Dem_EvClearProcState(LddEventId,DEM_EVPROCSTATE_EVENT_DEL);

          #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
          /* @Trace: Dem_SUD_API_10937 */
          Dem_EvMem_ClearMemLocInEvMemMap(LddEventId, DTCOrigin, LddEntry);
          #else
          /* @Trace: Dem_SUD_API_10935 */
          Dem_EvMem_ClearMemLocInEvMemMap(LddEventId, DTCOrigin);
          #endif
          
          /* Clear Maximum FDC since last clear */
          /* @Trace: SWS_Dem_00794
           * The maximum FDC since last clear shall be reset to zero with
           * each clear DTC command affecting this particular event.
           * */
          /* @Trace: Dem_SUD_API_10936 */
          #if (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
          /* @Trace: Dem_SUD_API_10938 */
          Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
          /* @Trace: Dem_SUD_API_10014 */
          if (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
          {
            /* @Trace: Dem_SUD_API_10939 */
            Dem_InternalDataMaxFdc[LddEvent->e_PointToDTC].maxFdcLastClear =
                DEM_ZERO;
          }
          #endif

           /* Clear the event memory entry in RAM */
          Dem_EvMem_ClearEventMemoryEntry(LddEntry);

          /* NvBlock flag for EventStatus will be set after this job has been
           * finished */
          Dem_EvMem_SetEvMemNvBlockStatus(
              DTCOrigin, LddMemLoc, DEM_EVMEM_STATUS_CLEARDTC);
        }
        else
        {
          /* @Trace: Dem_SUD_API_10973 */
          /* searching max time stamp */
          /* @Trace: Dem_SUD_API_10975 */
          #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
          /* @Trace: Dem_SUD_API_10930 */
          if (NULL_PTR != LddEntry)
          {
            uint32 LulCurrTimeStamp = LddEntry->TimeStamp;
            /* @Trace: Dem_SUD_API_10931 */
            if (LulMaxTimeStamp < LulCurrTimeStamp)
            {
              /* @Trace: Dem_SUD_API_10974 */
              LulMaxTimeStamp =  LulCurrTimeStamp;
            }
          }
          #endif
        }
      }
    }
    /* @Trace: Dem_SUD_API_10945 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_10946 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_10948 */
      Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] = LulMaxTimeStamp;
    }
    else
    #endif
    {
      /* @Trace: Dem_SUD_API_10947 */
      Dem_MaxTimeStamp[DTCOrigin] = LulMaxTimeStamp;
    }
    #endif
  }
  else if (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_10949 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_10950 */
    uint32 LulMaxTimeStamp = DEM_ZERO;
    #endif
    /* @Trace: Dem_SUD_API_10953 */
    for (uint8 LucIdx = DEM_ZERO;
               LucIdx < Dem_NumOfSupportedDTCOrigins;
               LucIdx++)
    { /* @Trace: Dem_SUD_API_10952 */
      Dem_DTCOriginType LddOrigin = Dem_SupportedDTCOrigins[LucIdx];

      LddStartIdx = Dem_EvMem_GetStartIndexEvMemory(ClientId, LddOrigin);
      LddStopIdx = Dem_EvMem_GetStopIndexEvMemory(ClientId, LddOrigin);
      /* @Trace: Dem_SUD_API_10954 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
      {
        LddEventId = Dem_EvMem_GetEventIdByEvMemEntry(LddOrigin, LddMemLoc);
        /* if (DEM_TRUE == Dem_EventIdIsValid(EventId)) */
        /* @Trace: Dem_SUD_API_10016 */
        if ((LddEventId <= DEM_NUMBER_OF_EVENTS) &&
            (DEM_NO_EVENT != LddEventId))
        {
          Dem_EventMemoryEntryPtrType LddEntry =
              Dem_EvMem_GetEmEntryByMemPosition(LddOrigin, LddMemLoc);
          /* SingleDTC or All DTCs are able to be deleted via flag
           * DEM_EVPROCSTATE_EVENT_DEL */
          /* @Trace: Dem_SUD_API_10955 */
          if (DEM_TRUE == Dem_EvIsProcStateTriggered(
             LddEventId, DEM_EVPROCSTATE_EVENT_DEL))
          {
            /* ISO-14229,160p:
             * first/most recent failed/comfirmed DTC information shall be
             * cleared upon a successful ClearDiagnosticInformation request
             * from the client */
            /* @Trace: Dem_SUD_API_10956 */
            #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
            if ((DEM_TRUE == ClearDTCOccurrenceTime)
            #if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > DEM_ZERO)
                && (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddOrigin)
            #endif
            )
            {
              Dem_DTCType LddDtcVal = DEM_ZERO;
              /* Dem_GetEventDTC always is true because
               * event with DTC is able to store in the memory */
              (void)Dem_GetEventDTC(
                  &Dem_Event[LddEventId-1U],
                  &LddDtcVal,
                  DEM_DTC_FORMAT_UDS);
              /* @Trace: Dem_SUD_API_10963 */
              if (DEM_TRUE ==
                    Dem_EvMem_ClearDTCOccurrenceTime(
                        ClientId,
                        LddDtcVal,
                        DEM_FALSE))
              {
                /* @Trace: Dem_SUD_API_10964 */
                Dem_EvMem_SetNonVolatieDataStatus(
                    DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);
              }
            }
            #else
            /* @Trace: Dem_SUD_API_10957 */
            (void)ClearDTCOccurrenceTime;
            #endif
            /* No need critical section */
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_EVENT_DEL);

            #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
            /* @Trace: Dem_SUD_API_10966 */
            Dem_EvMem_ClearMemLocInEvMemMap(LddEventId, LddOrigin, LddEntry);
            #else
            /* @Trace: Dem_SUD_API_10965 */
            Dem_EvMem_ClearMemLocInEvMemMap(LddEventId, LddOrigin);
            #endif

            /* Clear the event memory entry in RAM */
            Dem_EvMem_ClearEventMemoryEntry(LddEntry);

            /* NvBlock flag for EventStatus will be set after this job has been
             * finished */
            Dem_EvMem_SetEvMemNvBlockStatus(LddOrigin, LddMemLoc,
            DEM_EVMEM_STATUS_CLEARDTC);
          }
          else
          {
            /* searching max time stamp */
            /* @Trace: Dem_SUD_API_10960 */
            #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
            /* @Trace: Dem_SUD_API_10958 */
            if (NULL_PTR != LddEntry)
            {
              uint32 LulCurrTimeStamp = LddEntry->TimeStamp;
              /* @Trace: Dem_SUD_API_10959 */
              if (LulMaxTimeStamp < LulCurrTimeStamp)
              {
                /* @Trace: Dem_SUD_API_10961 */
               LulMaxTimeStamp = LulCurrTimeStamp;
              }
            }
            #endif
          }
        }
      }
    }
    /* @Trace: Dem_SUD_API_10968 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_10969 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_10967 */
      Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] = LulMaxTimeStamp;
    }
    else
    #endif
    {
      /* @Trace: Dem_SUD_API_10970 */
      Dem_MaxTimeStamp[DTCOrigin] = LulMaxTimeStamp;
    }
    #endif
  }
  else
  {
    /* @Trace: Dem_SUD_API_10015 */
    /* Nothing to do */
  }
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearDTCOfAllGroup                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the all dtcs from event memory                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCFormat, DTCOrigin, DTCTypeFilter, ClientId       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : DEM_CLEAR_FAILED  : Operation is failed             **
 **                       E_OK :              Clears at least one event       **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_Diag_04141 SRS_Diag_04213 SRS_Diag_04000
 */
static FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ClearDTCOfAllGroup(
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin,
  #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
  Dem_J1939DcmSetClearFilterType DTCTypeFilter,
  #endif
  uint8 ClientId
)
{
  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;
  Dem_NumOfDTCValueType LddDtcLoc;

  /* @Trace: SWS_Dem_00764
   * If no Event is assigned per DTR, the Dem shall reset the DTR
   * data upon a Service$04 clear command by the Dcm, i.e. a Dem_ClearDTC with:
   * DTC = DEM_DTC_GROUP_ALL_DTCS
   * DTCFormat = DEM_DTC_FORMAT_OBD
   * DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY */

  /* @Trace: SWS_Dem_01179
   * Service $14 FFFF33 shall clear all DTCs (WWH-OBD DTCs and UDS DTCs).
   */
  /* @Trace: Dem_SUD_API_10976 */
  #if ((DEM_NUMBER_OF_DTRS > DEM_ZERO) && \
       (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
  /* @Trace: Dem_SUD_API_10987 */
  if ((DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY == DTCOrigin) ||
      (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_10992 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DTRS; LucIdx++)
    {
      if (DEM_NO_IDX_U16 == Dem_GaaDtrInfo[LucIdx].usEventId)
      {
        /* @Trace: Dem_SUD_API_10991 */
        Dem_DtrData[LucIdx].Testvalue   = DEM_ZERO;
        Dem_DtrData[LucIdx].Lowlimvalue = DEM_ZERO;
        Dem_DtrData[LucIdx].Upplimvalue = DEM_ZERO;
      }
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_10993 */
  for (LddDtcLoc = DEM_ZERO; LddDtcLoc < DEM_MAX_NUMBER_OF_DTC;  LddDtcLoc++)
  {
    Dem_CombinedDtcPCType LddCbDTC = &Dem_GaaCombinedDtc[LddDtcLoc];
    /* @Trace: Dem_SUD_API_10994 */
    if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DTCFormat, LddCbDTC))
    {
      Dem_EventIdType LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true  */
      /* @Trace: Dem_SUD_API_10995 */
      if (DEM_NO_EVENT != LddEventId)
      {
        Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
        /* @Trace: Dem_SUD_API_10996 */
        if ((DEM_TRUE == Dem_DTCOriginBelongToEvent(LddEventId, DTCOrigin)) &&
            (LddEvent->ucEventMemDstIdx ==
                Dem_Client[ClientId].usDemEventMemorySetId))
        {      
          /*
          +--------------------------------------+-----------------------------------------+
          | DEM_J1939DTC_CLEAR_ALL               | ConfirmedDTC == 1 AND TestFailed == 1   |
          +--------------------------------------+-----------------------------------------+
          | DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE | ConfirmedDTC == 1 AND TestFailed == 0   |
          +--------------------------------------+-----------------------------------------+*/ 
          /* @Trace: Dem_SUD_API_10997 */
          #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
          boolean LblClearDTC = DEM_FALSE;
          if (DEM_DTC_FORMAT_J1939 == DTCFormat)
          {
            /* DM11  */
            /* @Trace: Dem_SUD_API_10977 */
            if (DEM_J1939DTC_CLEAR_ACTIVE == DTCTypeFilter)
            {
              Dem_UdsStatusByteType LddDtcStatusByte =
                  Dem_GetDTCStatus(LddEventId);
              /* @Trace: Dem_SUD_API_10989 */
              if ((LddDtcStatusByte &
                 ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |
                     (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC)) ==
                         ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |
                     (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC))
              {
                /* @Trace: Dem_SUD_API_10990 */
                LblClearDTC = DEM_TRUE;
              }
            }
            /* DM03 */
            else if (DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE == DTCTypeFilter)
            {
              Dem_UdsStatusByteType LddDtcStatusByte =
                  Dem_GetDTCStatus(LddEventId);
              /* @Trace: Dem_SUD_API_10980 */
              if ((LddDtcStatusByte &
                 ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |
                     (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC)) ==
                         (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC)
              {
                /* @Trace: Dem_SUD_API_10979 */
                LblClearDTC = DEM_TRUE;
              }
            }
            else
            {
              /* @Trace: Dem_SUD_API_10978 */
              LblClearDTC = DEM_TRUE;
            }
          }
          else
          { /* @Trace: Dem_SUD_API_10002 */
            LblClearDTC = DEM_TRUE;
          }
          /* @Trace: Dem_SUD_API_10981 */
          if (DEM_TRUE == LblClearDTC)
          #endif
          {

            /* @Trace: SWS_Dem_01205
               * If the Dem module is requested to clear diagnostic information
               * and the selected DTC is set to DTC group �all DTCs� and the
               * selected DTCOrigin is set to DEM_DTC_ORIGIN_MIRROR_MEMORY, the
               * Dem shall clear only the event entries assigned to the mirror
               * event memory. It does not affect UDS status.
               */
            /* @Trace: Dem_SUD_API_10982 */
            if ((( DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
                || (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin)))
                || ((DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
                    && (LddEvent->ucNumOfDestSelected == DEM_TWO))
                #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
                || (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY == DTCOrigin)
                #endif
                )
            {
              /* @Trace: Dem_SUD_API_10983 */
              if (E_OK == Dem_ClearSingleDTCStatusByte(LddCbDTC,DTCOrigin))
              {
                /* @Trace: Dem_SUD_API_10988 */
                LddRetVal = E_OK;
              }
            }
          }
          /* @Trace: Dem_SUD_API_10984 */
          #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
          else
          {
            /* @Trace: Dem_SUD_API_10985 */
            if (DEM_DTC_FORMAT_J1939 == DTCFormat)
            {
              /* @Trace: Dem_SUD_API_10986 */
              LddRetVal = E_OK;
            }
          }
          #endif
        }
      }
    }
  }

  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearDTCOfDTCGroup                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the all dtc with specific DTCOrigin           **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCGroup, DTCFormat, DTCOrigin                      **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
/* @Trace: SRS_Diag_04150 SRS_Diag_04214 SRS_Diag_04000
 */
static FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ClearDTCOfDTCGroup(
  Dem_DTCGroupType DTCGroup,
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin)
{
  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;
  Dem_NumOfDTCValueType LddDtcLoc;
  Dem_EventIdType LddEventId;
  /* @Trace: Dem_SUD_API_11001 */
  #if (DEM_MAX_NUM_GRP_DTC == DEM_ZERO)
  /* @Trace: Dem_SUD_API_11000 */
  DEM_UNUSED(DTCGroup);
  #endif
  /* @Trace: Dem_SUD_API_11002 */
  for (LddDtcLoc = DEM_ZERO; LddDtcLoc < DEM_MAX_NUMBER_OF_DTC;  LddDtcLoc++)
  {
    Dem_CombinedDtcPCType LddCbDTC = &Dem_GaaCombinedDtc[LddDtcLoc];
    LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
    
    /* polyspace<RTE:UNR:Not a defect:No action planned> for misra */
    /* @Trace: Dem_SUD_API_11006 */
    if (DEM_NO_EVENT != LddEventId)
    {
      /* @Trace: Dem_SUD_API_11005 */
      if ((LddCbDTC->ddDtcFormat == DTCFormat)
          #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
          && (LddCbDTC->ddDtcGroup < Dem_Max_Num_Grp_DTC)
          && (Dem_GaaGroupDTC[LddCbDTC->ddDtcGroup] == DTCGroup)
          #endif
         )
      {
        /* @Trace: Dem_SUD_API_10037 */
        if (DEM_TRUE == Dem_DTCOriginBelongToEvent(LddEventId, DTCOrigin))
        {      
          /* @Trace: Dem_SUD_API_11004 */
          if (E_OK == Dem_ClearSingleDTCStatusByte(LddCbDTC, DTCOrigin))
          {
            /* @Trace: SWS_Dem_01202
             * Defintion of a failed clear DTC operation. If the Dem module is
             * requested to clear diagnostic information, the Dem shall return
             * DEM_CLEAR_FAILED in case of clearing a DTC group or all DTCs,
             * the individual DTCs shall be cleared like described in clearing
             * single DTC. The resulting return value shall be DEM_CLEAR_FAILED
             * if the clearing of all individual DTCs returned DEM_CLEAR_FAILED.
             * */
            /* @Trace: Dem_SUD_API_11003 */
            LddRetVal = E_OK;
          }
        }
      }
    }
  }

  return LddRetVal;
}


/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearSingleDTC                            **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the single dtc data from memory               **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : Event, DTCOrigin                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
static FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ClearSingleDTC(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin)
{
  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;
  DEM_UNUSED(DTCOrigin);
  Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
  /* @Trace: Dem_SUD_API_10011 */
  if (NULL_PTR != LddCbDTC)
  {
    Dem_EvClearProcState(EventId,DEM_EVPROCSTATE_EVENT_DEL);
    /* @Trace: Dem_SUD_API_10998 */
    if (E_OK == Dem_ClearSingleDTCStatusByte(LddCbDTC, DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_10999 */
      LddRetVal = E_OK;
    }
  }
  
  return LddRetVal;
}


/******************************************************************************
* Function Name        : Dem_EvMem_TriggerWriteAllBlocks
*
* Service ID           : None
*
* Description          : Triggers the operation for wirting the nv blocks
*
* Sync/Async           : synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_TriggerWriteAllBlocks(void)
{
  /* @Trace: Dem_SUD_API_11047 */
  Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
}



/******************************************************************************
* Function Name        : Dem_EvMem_RequestWriteAllBlocks
*
* Service ID           : None
*
* Description          : Triggers the operation for wirting the nv blocks
*
* Sync/Async           : synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_RequestWriteAllBlocks(void)
{
  /* @Trace: Dem_SUD_API_10001 */
  Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
  Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_TRUE);
  Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_TRIGGER);

  #ifndef NVM_GPT_CHANNEL_ID
  (void)SchM_Trigger_Dem_ReleasedTrigger_ToNvM();
  #endif
}


/******************************************************************************
* Function Name        : Dem_EvMem_RequestReadAllBlocks
*
* Service ID           : None
*
* Description          : Triggers the operation for reading the nv blocks
*
* Sync/Async           : Asynchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_RequestReadAllBlocks(void)
{
  /* @Trace: Dem_SUD_API_11048 */
  Dem_EvMem_SetReadNvDataTrigger(DEM_TRUE);
}

/******************************************************************************
* Function Name        : Dem_EvMem_PreInit
*
* Service ID           : None
*
* Description          : init the variables for nv data
*
* Sync/Async           : synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : void
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_PreInit(void)
{
  /* Dem_NonVolatileDataState,Dem_EventMemoryState
   * are cleared as 0(zero) by 'VAR CLEARED SECTION' */
   
  Dem_EvMem_SetNvmResult(E_OK);
  Dem_EvMem_SetReadNvDataTrigger(DEM_FALSE);
  Dem_EvMem_SetWriteNvDataTrigger(DEM_FALSE);
  Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_FALSE); 
  Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_DONE);
  /* @Trace: Dem_SUD_API_11049 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11050 */
  for (uint8 LucClientId = DEM_ZERO;
             LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientId++)
  {
    /* @Trace: Dem_SUD_API_11051 */
    Dem_ClearDtcState[LucClientId].cds_State = DEM_CLEARDTC_STATE_READY;
    Dem_ClearDtcState[LucClientId].cds_DTC = DEM_NO_DTC;
    Dem_ClearDtcState[LucClientId].cds_DTCFormat = DEM_ZERO;
    Dem_ClearDtcState[LucClientId].cds_DTCOrigin = DEM_ZERO;
    Dem_ClearDtcState[LucClientId].cds_Result = DEM_CLEAR_FAILED;
    Dem_ClearDtcState[LucClientId].cds_EventIdRef = DEM_NO_EVENT;
    Dem_ClearDtcState[LucClientId].cds_RequestCancel = DEM_FALSE;
    Dem_ClearDtcState[LucClientId].cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
  }
#endif
}

/******************************************************************************
* Function Name        : Dem_EvMem_ReadAll
*
* Service ID           : None
*
* Description          : read nv data from flash memory or eep rom
*
* Sync/Async           : Asynchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : Filter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
/* @Trace: SRS_BSW_00301
 */
/* polyspace +1 CODE-METRICS:CALLS CODE-METRICS:PATH[Not a defect:Low] "Not a defect" */
static FUNC(boolean, DEM_CODE) Dem_EvMem_ReadAll(const uint8 Filter)
{
  boolean LblPending = DEM_FALSE;
  NvM_BlockIdType LddBlockId = DEM_ZERO;
  /* @NvM_RequestResultType nvDataResult; */
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_ZERO;
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) LpNvM_DstPtr;
  uint8 LucIdx;
  Dem_NumOfEventMemoryEntryType LddStartIdx = DEM_ZERO;
  Dem_NumOfEventMemoryEntryType LddStopIdx = DEM_ZERO;

  /* [@IF_REQ x 100, NOTE, @IF_REQ]
   * EventMemory[Num primary entry + num secondary entry...]
   * Regardles of DTCOrigin, only shall use MemLocation 
   */
  /* @Trace: Dem_SUD_API_11027 */
  for (uint8 LucClientIdx = DEM_ZERO;
             LucClientIdx < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientIdx++)
  /* @Trace: Dem_SUD_API_11038 */
  {
    /* @Trace: Dem_SUD_API_11040 */
    for (LucIdx = DEM_ZERO; LucIdx < Dem_NumOfSupportedDTCOrigins; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_11041 */
      Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
      Dem_DTCOriginType LddDTCOrigin = Dem_SupportedDTCOrigins[LucIdx];
      LddStartIdx = Dem_EvMem_GetStartIndexEvMemory(LucClientIdx, LddDTCOrigin);
      LddStopIdx = Dem_EvMem_GetStopIndexEvMemory(LucClientIdx, LddDTCOrigin);
      /* @Trace: Dem_SUD_API_11042 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
      {
        /* @Trace: Dem_SUD_API_11043 */
        if (DEM_TRUE == Dem_EvMem_IsEvMemNvBlockStatusFilter(
            LddDTCOrigin, LddMemLoc, Filter))
        {
          LddMemEntry = Dem_EvMem_GetEmEntryByMemPosition(
              LddDTCOrigin, LddMemLoc);
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * If-condition always evaluates to true. Avoid the runtime error of
           * the polyspace */
          if (NULL_PTR != LddMemEntry)
          {
            if (E_OK == Dem_NvData_GetNvMBlockId(DEM_NVDATA_EVENT_MEMORY_ID,
                   LddDTCOrigin, LddMemLoc, &LddBlockId))
            {
              /* @Trace: Dem_SUD_API_11046 */
              #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                   (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
              if (LddDTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
              {
                /* @Trace: Dem_SUD_API_11029 */
                LpNvM_DstPtr = &Dem_PermanentEventMemory[LddMemLoc];
              }
              else
              #endif
              {
                /* @Trace: Dem_SUD_API_11028 */
                LpNvM_DstPtr = LddMemEntry;
              }

              if (E_OK != NvM_ReadBlock(LddBlockId, LpNvM_DstPtr))
              {
                /* if NvM is busy state, NvM_ReadBlock shall be called on next
                 * mainfunction */
                /* @Trace: Dem_SUD_API_11031 */
                LblPending = DEM_TRUE;
              }
              else
              {
                /* @Trace: Dem_SUD_API_11030 */
                Dem_EvMem_ClearEvMemNvBlockStatus(
                    LddDTCOrigin, LddMemLoc, Filter);
                /* In case of ReadAll, Dem shall wait until nvm is completed */
                Dem_EvMem_SetEvMemNvBlockStatus(LddDTCOrigin, LddMemLoc,
                    DEM_EVMEM_STATUS_QUEUED_NVM);
              }
            }
            /* No NvM Block is congigured */
            else
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * Above If-condition always evaluates to true. Avoid the runtime
             * error of the polyspace */
            {
              /* @Trace: Dem_SUD_API_11045 */
              Dem_EvMem_ClearEvMemNvBlockStatus(
                  LddDTCOrigin, LddMemLoc, Filter);
            }
          }
          else
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * Above If-condition always evaluates to true. Avoid the runtime
           * error of the polyspace */
          {
            /* @Trace: Dem_SUD_API_11044 */
            Dem_EvMem_ClearEvMemNvBlockStatus(LddDTCOrigin, LddMemLoc, Filter);
          }
        }
        /* @Trace: Dem_SUD_API_11033 */
        if (NULL_PTR != LddMemEntry)
        {
          /* @Trace: Dem_SUD_API_11034 */
          if ( DEM_NO_EVMEM_ENTRY != LddMemEntry->EventIdRef)
          {
            /* @Trace: Dem_SUD_API_11032 */
            Dem_EvMem_IncNumOfStoredEvtMemEntriesFromClientId(LucClientIdx,
                LddDTCOrigin, DEM_ONE);
          }
        }
      }
    }
  }
  /* @Trace: Dem_SUD_API_11035 */
  for (LucIdx = DEM_ZERO; LucIdx < Dem_NumOfSupportedSingleNvBlocks; LucIdx++)
  {
    Dem_NvDataIdType LddDataId = Dem_DataIdOfSingleNvBlocks[LucIdx];
    /* @Trace: Dem_SUD_API_10035 */
    if (DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(LddDataId, Filter))
    {
      Std_ReturnType LddResult = Dem_NvData_ReadNonVolatileData(LddDataId);
      switch(LddResult) {
      case E_OK:
        /* @Trace: Dem_SUD_API_11036 */
        Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
        /* In case of ReadAll, Dem shall wait until nvm is completed */
        Dem_EvMem_SetNonVolatieDataStatus(
            LddDataId, DEM_EVMEM_STATUS_QUEUED_NVM);
        break;
      case DEM_E_PENDING:
        /* @Trace: Dem_SUD_API_11037 */
        LblPending = DEM_TRUE;
        break;
      default: /* No NvM Block is congigured */
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        /* @Trace: Dem_SUD_API_11039 */
        Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
        break;
      }
    }  
  }

  /* Read All event status */
  return LblPending;
}


/******************************************************************************
* Function Name        : Dem_EvMem_WriteAll
*
* Service ID           : None
*
* Description          : write nv data to flash memory or eep rom
*
* Sync/Async           : Asynchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : Filter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
/* @Trace: SRS_BSW_00301
 */
/* polyspace +1 CODE-METRICS:CALLS [Not a defect:Low] "Not a defect" */
static FUNC(boolean, DEM_CODE) Dem_EvMem_WriteAll(
  const uint8 Filter)
{
  boolean                                 LblPending = DEM_FALSE;
  Dem_NumOfEventMemoryEntryType           LddMemLoc = DEM_ZERO;
  Dem_EventMemoryEntryPtrType             LddMemEntry;
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) LpNvM_SrcPtr = NULL_PTR;
  Dem_NumOfEventMemoryEntryType           LddStartIdx = DEM_ZERO;
  Dem_NumOfEventMemoryEntryType           LddStopIdx = DEM_ZERO;

  /* [@IF_REQ x 100, NOTE, @IF_REQ]
   * EventMemory[Num primary entry + num secondary entry...]
   * Regardles of DTCOrigin, only shall use MemLocation 
   */
  /* @Trace: Dem_SUD_API_11007 */
  for (uint8 LucClientIdx = DEM_ZERO;
             LucClientIdx < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientIdx++)
  /* @Trace: Dem_SUD_API_11018 */
  {
    /* @Trace: Dem_SUD_API_11020 */
    for (uint8 LucIdx = DEM_ZERO;
               LucIdx < Dem_NumOfSupportedDTCOrigins;
               LucIdx++)
    {
      Dem_DTCOriginType LddDTCOrigin = Dem_SupportedDTCOrigins[LucIdx];
      LddStartIdx = Dem_EvMem_GetStartIndexEvMemory(LucClientIdx, LddDTCOrigin);
      LddStopIdx = Dem_EvMem_GetStopIndexEvMemory(LucClientIdx, LddDTCOrigin);
      /* @Trace: Dem_SUD_API_11021 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
      {
        /* @Trace: Dem_SUD_API_11022 */
        if (DEM_TRUE == Dem_EvMem_IsEvMemNvBlockStatusFilter(
            LddDTCOrigin, LddMemLoc, Filter))
        {
          NvM_BlockIdType LddBlockId = DEM_ZERO;
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * If-condition evaluates to true or false according to
           * configuration */
          if (E_OK == Dem_NvData_GetNvMBlockId(
              DEM_NVDATA_EVENT_MEMORY_ID, LddDTCOrigin, LddMemLoc, &LddBlockId))
          {
            NvM_RequestResultType LddNVResult = NVM_REQ_PENDING;
            if (E_OK == NvM_GetErrorStatus(LddBlockId, &LddNVResult))
            {
              if (NVM_REQ_PENDING != LddNVResult)
              {
                /* @Trace: Dem_SUD_API_11008 */
                #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                     (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
                if (LddDTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
                {
                  /* @Trace: Dem_SUD_API_11026 */
                  LpNvM_SrcPtr = &Dem_PermanentEventMemory[LddMemLoc];
                }
                else
                #endif
                {
                  /* @Trace: Dem_SUD_API_11009 */
                  LddMemEntry = Dem_EvMem_GetEmEntryByMemPosition(
                      LddDTCOrigin, LddMemLoc);
                  LpNvM_SrcPtr = LddMemEntry;
                }

                if (E_OK != NvM_WriteBlock(LddBlockId, LpNvM_SrcPtr))
                {
                  /* @Trace: Dem_SUD_API_11010 */
                  LblPending = DEM_TRUE;
                }
                else
                {
                  Dem_EvMem_ClearEvMemNvBlockStatus(
                      LddDTCOrigin, LddMemLoc, Filter);
                  /* @Trace: Dem_SUD_API_11011 */
                  if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
                  {
                    /* @Trace: Dem_SUD_API_11012 */
                    Dem_EvMem_SetEvMemNvBlockStatus(LddDTCOrigin, LddMemLoc,
                        DEM_EVMEM_STATUS_QUEUED_NVM);
                  }
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_11025 */
                LblPending = DEM_TRUE;
              }
            }
            /* Unknown state */
            else
            {
              /* @Trace: Dem_SUD_API_11024 */
              Dem_EvMem_ClearEvMemNvBlockStatus(
                  LddDTCOrigin, LddMemLoc, Filter);
            }
          }
          /* No NvM Block is congigured */
          else
          {
            /* @Trace: Dem_SUD_API_11023 */
            Dem_EvMem_ClearEvMemNvBlockStatus(LddDTCOrigin, LddMemLoc, Filter);
          }
        }
      }
    }
  }

  /* @Trace: Dem_SUD_API_11013 */
  for (uint8 LucIdx = DEM_ZERO;
             LucIdx < Dem_NumOfSupportedSingleNvBlocks;
             LucIdx++)
  {
    Dem_NvDataIdType LddDataId = Dem_DataIdOfSingleNvBlocks[LucIdx];
    /* @Trace: Dem_SUD_API_11014 */
    if (DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(LddDataId, Filter))
    {
      Std_ReturnType LddResult = Dem_NvData_WriteNonVolatileData(LddDataId);
      switch(LddResult) {
      case E_OK:
        /* @Trace: Dem_SUD_API_10036 */
        Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
        /* @Trace: Dem_SUD_API_11019 */
        if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
        {
          /* @Trace: Dem_SUD_API_11017 */
          Dem_EvMem_SetNonVolatieDataStatus(
              LddDataId, DEM_EVMEM_STATUS_QUEUED_NVM);
        }
        break;
      case DEM_E_PENDING:
        /* @Trace: Dem_SUD_API_11016 */
        LblPending = DEM_TRUE;
        break;
      default: /* No NvM Block is congigured */
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        /* @Trace: Dem_SUD_API_11015 */
        Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
        break;
      }
    }
  }

  return LblPending;
}

/******************************************************************************
* Function Name        : Dem_EvMem_MainFunctionClearDtc
*
* Service ID           : None
*
* Description          : periodic task to clear DTC
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04065 SRS_Diag_04093
           SRS_Diag_04117 SRS_Diag_04150 SRS_Diag_04185 SRS_Diag_04194
           SRS_Diag_04213 SRS_Diag_04214 SRS_Diag_04164
 */
/* polyspace +1 CODE-METRICS:VG CODE-METRICS:CALLS CODE-METRICS:FXLN CODE-METRICS:PATH[Not a defect:LOW] "Not a defect" */ 
FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionClearDtc(void)
{
  /* @Trace: Dem_SUD_API_11052 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  Std_ReturnType LddResult = DEM_CLEAR_FAILED;
  /* @Trace: Dem_SUD_API_11063 */
  for (uint8 LucClientId = DEM_ZERO;
             LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientId++)
  {
    /* @Trace: Dem_SUD_API_11074 */
    if (DEM_TRUE == Dem_ClearDtcState[LucClientId].cds_RequestCancel)
    {
      /* @Trace: Dem_SUD_API_11085 */
      if ((DEM_CLEARDTC_STATE_PREPARE_CLEARDTC ==
            Dem_ClearDtcState[LucClientId].cds_State) ||
          (DEM_CLEARDTC_STATE_RUNNING ==
              Dem_ClearDtcState[LucClientId].cds_State)
         /*@||
         @(DEM_CLEARDTC_STATE_WAIT == Dem_ClearDtcState.cds_State) ||
         @(DEM_CLEARDTC_STATE_RESULT == Dem_ClearDtcState.cds_State)
         */
     )
      {
        Dem_EventIdType LddTmpEvId;
        /* @Trace: Dem_SUD_API_10003 */
        for (LddTmpEvId = DEM_ONE;
             LddTmpEvId <= DEM_NUMBER_OF_EVENTS;
             LddTmpEvId++)
        {
          /* @Trace: Dem_SUD_API_11107 */
          Dem_EvClearProcState(LddTmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);
        }

        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        Dem_ClearDtcState[LucClientId].cds_State = DEM_CLEARDTC_STATE_READY;
        Dem_ClearDtcState[LucClientId].cds_Result = DEM_CLEAR_FAILED;
        Dem_ClearDtcState[LucClientId].cds_RequestCancel = DEM_FALSE;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      /* If cds_RequestCancel is set to true , Dem_ClearDTC will be called by
       * Dcm anymore. So Dem-self shall stop the clearing processs */
      else if (DEM_CLEARDTC_STATE_RESULT ==
          Dem_ClearDtcState[LucClientId].cds_State)
      {
        /* @Trace: Dem_SUD_API_10004 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        Dem_ClearDtcState[LucClientId].cds_State =
            DEM_CLEARDTC_STATE_AFTER_CLEAROK;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      else /* DEM_CLEARDTC_STATE_WAIT or DEM_CLEARDTC_STATE_CLEAR_EVMEM */
      {
        /* @Trace: Dem_SUD_API_11096 */
        /* Nothing to do */
      }
    }
    /* [Relationship of state and RequestCancel]
     *+-+---------------+---------------+---------------+---------------+
     *| |    State      | ReqeustCancel |   behavior    |   next state  |
     *+-+---------------+---------------+---------------+---------------+
     *|1|   ready       |      1        |    N/A        |    N/A        |
     *+-+---------------+---------------+---------------+---------------+
     *|2|   running     |      1        |    cancel     |    ready      |
     *+-+---------------+---------------+---------------+---------------+
     *|3|   wait        |      1        |    wait NvM   |    result     |
     *+-+---------------+---------------+---------------+---------------+
     *|4|   result      |      1        |    normal     |  after ok     |
     *+-+---------------+---------------+---------------+---------------+
     *|5|   after ok    |      1        |    normal     |    ready      |
     *+-+---------------+---------------+---------------+---------------+
     *|                   Normal process                                |
     *+-+---------------+---------------+---------------+---------------+
     *|1|   ready       |      0        |    N/A        |    N/A        |
     *+-+---------------+---------------+---------------+---------------+
     *|2|   running     |      0        |    clearDTC   |    wait       |
     *+-+---------------+---------------+---------------+---------------+
     *|3|   wait        |      0        |    wait NvM   |    result     |
     *+-+---------------+---------------+---------------+---------------+
     *|4|   result      |      0        |    N/A        |    N/A        |
     *+-+---------------+---------------+---------------+---------------+
     *|5|   after ok    |      0        | call init mon |    ready      |
     *+-+---------------+---------------+---------------+---------------+ */
    /* @Trace: Dem_SUD_API_11118 */
    if (DEM_CLEARDTC_STATE_READY != Dem_ClearDtcState[LucClientId].cds_State)
    {
      switch (Dem_ClearDtcState[LucClientId].cds_State)
      {
        case DEM_CLEARDTC_STATE_PREPARE_CLEARDTC:
          /* @Trace: Dem_SUD_API_11122 */
          if (DEM_FALSE == Dem_OperationCycleTrigger)
          {
            boolean LblLocked = DEM_FALSE;
            Dem_EventIdType LddEventId;
            /* @Trace: Dem_SUD_API_11053 */
            for (LddEventId = DEM_ONE;
                 LddEventId <= DEM_NUMBER_OF_EVENTS;
                 LddEventId++)
            {
              /* @Trace: Dem_SUD_API_11054 */
              if (DEM_TRUE == Dem_EvIsProcStateTriggered(
                  LddEventId, DEM_EVPROCSTATE_EVENT_LOCK))
              {
                /* @Trace: Dem_SUD_API_10006 */
                LblLocked = DEM_TRUE;
                break;
              }
            }
            /* @Trace: Dem_SUD_API_11055 */
            if (DEM_FALSE == LblLocked)
            {
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              Dem_ClearDtcState[LucClientId].cds_State =
                  DEM_CLEARDTC_STATE_RUNNING;
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

              /* @Trace: SWS_Dem_01240
               * If DemClearDtcNotificationTime is configured to START, the Dem
               * shall inform the application about the start of a clear DTC
               * operation. If the DemClearDtcNotificationFnc is configured,
               * the Dem shall shall call this configured function otherwise
               * the Dem shall call the R-Port ClearDtcNotification.
               * */
              /* @Trace: Dem_SUD_API_11056 */
              #if ((DEM_NUM_OF_CLEARDTC_NOTIFICATIONID > DEM_ZERO) && \
                   (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO))
              /* @Trace: Dem_SUD_API_11058 */
              uint8 LucEvMemSetId = DEM_NO_EVMEM_IDX;
              /* @Trace: Dem_SUD_API_11057 */
              if (Dem_ClearDtcState[LucClientId].cds_ClientIdRef <
                    DEM_NUMBER_OF_DEM_CLIENT)
              {
                /* @Trace: Dem_SUD_API_11059 */
               LucEvMemSetId =
                   Dem_Client[Dem_ClearDtcState[LucClientId].cds_ClientIdRef].
                     usDemEventMemorySetId;
              }
              /* @Trace: Dem_SUD_API_11060 */
              if (DEM_MAX_NUMBER_MEMORY_SET > LucEvMemSetId)
              {
                /* @Trace: Dem_SUD_API_11061 */
                if ((Dem_GaaDemMemorySet[LucEvMemSetId].usNumOfDtcClearNot !=
                      DEM_ZERO) &&
                    (DEM_NUM_OF_CLEARDTC_NOTIFICATIONID >=
                        Dem_GaaDemMemorySet[LucEvMemSetId].usNumOfDtcClearNot))
                {
                  /* @Trace: Dem_SUD_API_11062 */
                  uint16 LusStartIdx =
                      Dem_GaaDemMemorySet[LucEvMemSetId].usDtcClearNotIdx;
                  uint16 LusStopIdx =
                      LusStartIdx +
                      Dem_GaaDemMemorySet[LucEvMemSetId].usNumOfDtcClearNot;
                  /* @Trace: Dem_SUD_API_11067 */
                  for (; (LusStartIdx < LusStopIdx) &&
                      (LusStartIdx < DEM_NUMBER_OF_CLEAR_DTC_NOTIFICATION_FNC); LusStartIdx++)
                  {
                    /* @Trace: Dem_SUD_API_11065 */
                    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
                    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
                    if (DEM_CLEAR_DTC_NOTIFICATION_START ==
                          Dem_GaaClearDtcNotificationFnc[LusStartIdx].usNotTime)
                    {
                      /* @Trace: Dem_SUD_API_11066 */
                      if (NULL_PTR !=
                            Dem_GaaClearDtcNotificationFnc[LusStartIdx].
                              pDemClearDtcNotificationFnc )
                      {
                        /* @Trace: Dem_SUD_API_11064 */
                        Dem_GaaClearDtcNotificationFnc[LusStartIdx].
                          pDemClearDtcNotificationFnc(
                              Dem_ClearDtcState[LucClientId].cds_DTC,
                              Dem_ClearDtcState[LucClientId].cds_DTCFormat,
                              Dem_ClearDtcState[LucClientId].cds_DTCOrigin);
                      }
                    }
                    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
                  }
                  
                }
              }
              #endif
            }
          }
          break;

        case DEM_CLEARDTC_STATE_RUNNING:
          /* @Trace: SWS_Dem_01206
           * The Dem shall call the callback DemClearEventAllowed only if the
           * selected DTCOrigin for the clear operation is the primary or user
           * defined event memory.
           * */
          /* @Trace: Dem_SUD_API_11069 */
          if ((DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
                Dem_ClearDtcState[LucClientId].cds_DTCOrigin) ||
               #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
               (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY ==
                   Dem_ClearDtcState[LucClientId].cds_DTCOrigin) ||
               #endif
               #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
               (DEM_DTC_ORIGIN_MIRROR_MEMORY ==
                   Dem_ClearDtcState[LucClientId].cds_DTCOrigin) ||
               #endif
              (DEM_DTCORGIN_USER_DEFINED_IS_VALID (
                  Dem_ClearDtcState[LucClientId].cds_DTCOrigin)))
          {
            /* Clear Group DTC : if cds_EventIdRef is null , then Dcm will clear
             * All dtcs or group of dtc  */
            if (DEM_NO_EVENT == Dem_ClearDtcState[LucClientId].cds_EventIdRef)
            {

              /* @Trace: SWS_Dem_01203
               * If the Dem module is requested to clear diagnostic information
               * and the selected DTC is set to DTC group �all DTCs� and the
               * selected DTCOrigin is set to DEM_DTC_ORIGIN_PRIMARY_MEMORY or
               * DEM_DTC_ORIGIN_USERDEFINED_MEMORY_<NAME>, the Dem shall reset
               * all event and DTC status bytes and clear event related data
               * assigned to the requested DTCOrigin.
               * */
              if (DEM_DTC_GROUP_ALL_DTCS ==
                    Dem_ClearDtcState[LucClientId].cds_DTC)
              {
                /* @Trace: SWS_Dem_00879
                 * The function Dem_J1939DcmClearDTC shall clear the status of
                 * all event(s) related to the specified DTC(s), as well as all
                 * associated event memory entries for these event(s).
                 */
                /* @Trace: Dem_SUD_API_11071 */
                LddResult =
                    Dem_EvMem_ClearDTCOfAllGroup(
                        Dem_ClearDtcState[LucClientId].cds_DTCFormat,
                        Dem_ClearDtcState[LucClientId].cds_DTCOrigin,
                        #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
                        Dem_ClearDtcState[LucClientId].cds_DTCTypeFilter,
                        #endif
                        LucClientId
                        );
              }
              else if (DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD ==
                  Dem_ClearDtcState[LucClientId].cds_DTC)
              {
                #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
                /* @IF_REQ OBD is not implemented yet!!!!
                 * clear all dtc (evnet kind :DEM_DTC_KIND_EMISSION_REL_DTCS)
                 */
                /* @Trace: SWS_Dem_00879
                 * The function Dem_J1939DcmClearDTC shall clear the status of
                 * all event(s) related to the specified DTC(s), as well as all
                 * associated event memory entries for these event(s).
                 */
                /* @Trace: Dem_SUD_API_11073 */
                LddResult =
                    Dem_EvMem_ClearDTCOfAllGroup(
                        Dem_ClearDtcState[LucClientId].cds_DTCFormat,
                        Dem_ClearDtcState[LucClientId].cds_DTCOrigin,
                        #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
                        Dem_ClearDtcState[LucClientId].cds_DTCTypeFilter,
                        #endif
                        LucClientId
                        );
                #else
                /* @Trace: Dem_SUD_API_11075 */
                LddResult = DEM_WRONG_DTC;
                #endif
              }
              else
              {
                /* @Trace: Dem_SUD_API_11072 */
                LddResult = Dem_EvMem_ClearDTCOfDTCGroup(
                    (Dem_DTCGroupType)Dem_ClearDtcState[LucClientId].cds_DTC,
                    Dem_ClearDtcState[LucClientId].cds_DTCFormat,
                    Dem_ClearDtcState[LucClientId].cds_DTCOrigin);
              }
            }
            /* Clear a single DTC */
            else
            {
              /* @Trace: Dem_SUD_API_11070 */
              LddResult = Dem_EvMem_ClearSingleDTC(
                  Dem_ClearDtcState[LucClientId].cds_EventIdRef,
                  Dem_ClearDtcState[LucClientId].cds_DTCOrigin);
            }
            /* checks whether at least one event is dirty or not */
            if (E_OK == LddResult)
            {
              /* @Trace: Dem_SUD_API_11076 */
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              Dem_ClearDtcState[LucClientId].cds_State =
                  DEM_CLEARDTC_STATE_CLEAR_EVMEM;
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }
            else
            {
              /* @Trace: Dem_SUD_API_11077 */
              Dem_ClearDtcState[LucClientId].cds_Result = LddResult;
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              Dem_ClearDtcState[LucClientId].cds_State =
                  DEM_CLEARDTC_STATE_RESULT;
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }
          }
          break;

        case DEM_CLEARDTC_STATE_CLEAR_EVMEM:

          if (DEM_DTC_GROUP_ALL_DTCS == Dem_ClearDtcState[LucClientId].cds_DTC)
          {
            Dem_EvMem_ClearEvMemEntriesByClearDTC(
                LucClientId,
                Dem_ClearDtcState[LucClientId].cds_DTCOrigin,
                DEM_FALSE);
            /* @Trace: Dem_SUD_API_11080 */
            #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
            /* @Trace: Dem_SUD_API_11081 */
            if (DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
                  Dem_ClearDtcState[LucClientId].cds_DTCOrigin)
            {
              /* ISO-14229,160p:
               * first/most recent failed/comfirmed DTC information shall be
               * cleared upon a successful ClearDiagnosticInformation request
               * from the client */
              /* @Trace: Dem_SUD_API_11082 */
              if (DEM_TRUE ==
                    Dem_EvMem_ClearDTCOccurrenceTime(
                        LucClientId, DEM_ZERO, DEM_TRUE))
              {
                /* @Trace: Dem_SUD_API_11083 */
                Dem_EvMem_SetNonVolatieDataStatus(
                    DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);
              }
            }
            #endif

            /* @Trace: SWS_Dem_00399
             * The event memory overflow indication of the respective event
             * memory shall be reset, if all DTCs of this memory are deleted by
             * Dem_ClearDTC
             */
            /* @Trace: Dem_SUD_API_11084 */
            #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
            /* @Trace: Dem_SUD_API_11086 */
            if (DEM_NUMBER_OF_DEM_CLIENT >
                      Dem_ClearDtcState[LucClientId].cds_ClientIdRef)
            {
              /* @Trace: Dem_SUD_API_11087 */
              /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
              if (DEM_NO_EVMEM_IDX !=
                    Dem_Client[Dem_ClearDtcState[LucClientId].cds_ClientIdRef].
                      usDemEventMemorySetId)
              {
                /* @Trace: Dem_SUD_API_11088 */
                if (DEM_TRUE == Dem_EvMem_SetEvMemOverflowFlag(
                    Dem_Client[Dem_ClearDtcState[LucClientId].cds_ClientIdRef].
                      usDemEventMemorySetId,
                    Dem_ClearDtcState[LucClientId].cds_DTCOrigin, DEM_FALSE))
                {
                  /* @Trace: Dem_SUD_API_11089 */
                  Dem_EvMem_SetNonVolatieDataStatus(
                      DEM_NVDATA_ALL_EVENT_STATUS_ID,
                      DEM_EVMEM_STATUS_CLEARDTC);
                }
              }
              }
            #endif
          }
          else
          {
            /* @Trace: Dem_SUD_API_11079 */
            Dem_EvMem_ClearEvMemEntriesByClearDTC(
                LucClientId,
                Dem_ClearDtcState[LucClientId].cds_DTCOrigin,
                DEM_TRUE);
          }

          #if (DEM_CLEAR_DTC_BEHAVIOUR == DEM_CLRRESP_NONVOLATILE_FINISH)
          /* @Trace: Dem_SUD_API_11090 */
          Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
          Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_TRUE);
          #elif (DEM_CLEAR_DTC_BEHAVIOUR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
          /* @Trace: Dem_SUD_API_11091 */
          Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
          #else
          /* @Trace: Dem_SUD_API_11092 */
          /* Do nothing */
          #endif

          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_ClearDtcState[LucClientId].cds_State = DEM_CLEARDTC_STATE_WAIT;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          break;
        case DEM_CLEARDTC_STATE_WAIT:
          /* @Trace: Dem_SUD_API_11094 */
          if (DEM_FALSE == Dem_EvMem_WaitClearAllBlocks(&LddResult))
          {
            /* @Trace: Dem_SUD_API_10010 */
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_ClearDtcState[LucClientId].cds_State =
                DEM_CLEARDTC_STATE_RESULT;
            Dem_ClearDtcState[LucClientId].cds_Result = LddResult;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          break;

        /* After Dem_ClearDTC returns any value to Dcm */
        case DEM_CLEARDTC_STATE_AFTER_CLEAROK: /* last state! */
        /* @Trace: SWS_Dem_00573
         * If DemTriggerMonitorInitBeforeClearOk is set to TRUE,
         * the Dem_ClearDTC shall not return E_OK until the events intialization
         * is triggered (callback function InitMonitorForEvent is called).
         * If DemTriggerMonitorInitBeforeClearOk is set to FALSE, DEM_CLEAR_OK
         * is not considering Event initialization (InitMonitorForEvent).
         * */
          /* @Trace: Dem_SUD_API_11097 */
          #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_OFF)
          if (E_OK == Dem_ClearDtcState[LucClientId].cds_Result)
          {
            Dem_EventIdType LddTmpEvId;
            /* @Trace: Dem_SUD_API_11101 */
            for (LddTmpEvId = DEM_ONE;
                 LddTmpEvId <= DEM_NUMBER_OF_EVENTS;
                 LddTmpEvId++)
            {
              /* @Trace: Dem_SUD_API_11098 */
              if (DEM_TRUE == Dem_EvIsProcStateTriggered(
                    LddTmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC))
              {
                Dem_EvClearProcState(
                    LddTmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);

                /* @Trace: SWS_Dem_00680
                 * The Dem_ClearDTC API shall trigger the callback function
                 * InitMonitorForEvent of the related event(s) in case of
                 * clearing the event(s). The InitMonitorReason parameter shall
                 * be set to DEM_INIT_MONITOR_CLEAR.
                 * */
                /* @Trace: SWS_Dem_00256 */
                /* @Trace: Dem_SUD_API_11099 */
                if (Dem_Event[LddTmpEvId - DEM_ONE].pDemInitMonitorForEvent !=
                      NULL_PTR)
                {
                  /* polyspace<RTE:COR:Not a defect:No action planned>
                   * Polyspace bug */
                  /* @Trace: Dem_SUD_API_11100 */
                  Dem_Event[LddTmpEvId - DEM_ONE].pDemInitMonitorForEvent(
                      (Dem_InitMonitorReasonType)DEM_INIT_MONITOR_CLEAR);
                }
              }
            }
          }
          else
          {
            /* @Trace: Dem_SUD_API_11104 */
            Dem_EventIdType LddTmpEvId;
            for (LddTmpEvId = DEM_ONE;
                 LddTmpEvId <= DEM_NUMBER_OF_EVENTS;
                 LddTmpEvId++)
            {
              /* @Trace: Dem_SUD_API_11102 */
              Dem_EvClearProcState(
                  LddTmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);
            }
          }
          #endif

          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_ClearDtcState[LucClientId].cds_State = DEM_CLEARDTC_STATE_READY;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          Dem_ClearDtcState[LucClientId].cds_RequestCancel = DEM_FALSE;

          /* @IF_REQ: Add one more phase => case XXX: */
          /* @Trace: Dem_SUD_API_11105 */
          /* @Trace: Dem_SUD_MACRO_051 */
          #if (DEM_J1939_SUPPORT == STD_ON)
          /* @Trace: Dem_SUD_API_11106 */
          Dem_EvMem_InitChronologicalOrder(
              Dem_ClearDtcState[LucClientId].cds_DTCOrigin);
          #endif
          /* @Trace: Dem_SUD_API_11108 */
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)

          #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
          Dem_SetMalfuntionOnOff();
          #endif
          /* @Trace: Dem_SUD_API_11109 */
          
          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          /* Trace: DEM_19792_14_02 */
          if ( (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY == Dem_ClearDtcState[LucClientId].cds_DTCOrigin) ||
                /* Condition 1: UDS 0x14 FFFFFF */
               (DEM_DTC_GROUP_ALL_DTCS == Dem_ClearDtcState[LucClientId].cds_DTC) ||
                /* Condition 2: UDS 0x14 FFFF33 */
               (DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD == Dem_ClearDtcState[LucClientId].cds_DTC) ||
                /* Condition 3: Single DTC Clear && That DTC is OBDMemoryId DTC */
               ( (Dem_ClearDtcState[LucClientId].cds_EventIdRef != DEM_NO_EVENT) &&
                  (Dem_ClearDtcState[LucClientId].cds_EventIdRef == Dem_PrimaryEventMemory[Dem_ObdMemoryId].EventIdRef) )
             )
          {
            /* @Trace: Dem_SUD_API_11111 */
            Dem_ClearObdInfomation();
          }
          #else 
          /* @Trace: Dem_SUD_API_11110 */
          if (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY ==
                Dem_ClearDtcState[LucClientId].cds_DTCOrigin)
          {
            /* @Trace: Dem_SUD_API_11111 */
            Dem_ClearObdInfomation();
          }
          #endif

          #endif

          /* @Trace: SWS_Dem_01241
           * If DemClearDtcNotificationTime is configured to FINISH, the Dem
           * shall inform the application about the end of a clear DTC operation
           * . The Dem shall consider the configuration parameter
           * DemClearDTCBehavior which defines the clearing process of
           * diagnostic information including clearing completion. If the
           * DemClearDtcNotificationFnc is configured, the Dem shall call this
           * configured function otherwise the Dem shall call the R-Port
           * ClearDtcNotification.
           * */
          /* @Trace: Dem_SUD_API_11112 */
          #if ((DEM_NUM_OF_CLEARDTC_NOTIFICATIONID > DEM_ZERO) && \
               (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO))
          uint16 LusMemSetId = DEM_NO_EVMEM_IDX;
          /* @Trace: Dem_SUD_API_11114 */
          if (DEM_NUMBER_OF_DEM_CLIENT >
               Dem_ClearDtcState[LucClientId].cds_ClientIdRef)
          {
            /* @Trace: Dem_SUD_API_11113 */
           LusMemSetId =
               Dem_Client[Dem_ClearDtcState[LucClientId].cds_ClientIdRef].
                 usDemEventMemorySetId;
          }
          if (DEM_NO_EVMEM_IDX != LusMemSetId)
          {
            /* @Trace: Dem_SUD_API_11115 */
            if ((Dem_GaaDemMemorySet[LusMemSetId].usNumOfDtcClearNot !=
                  DEM_ZERO) &&
                (DEM_NUM_OF_CLEARDTC_NOTIFICATIONID >=
                  Dem_GaaDemMemorySet[LusMemSetId].usNumOfDtcClearNot))
            {
              uint16 LusStartIdx =
                  Dem_GaaDemMemorySet[LusMemSetId].usDtcClearNotIdx;
              uint16 LusStopIdx =
                  LusStartIdx +
                  Dem_GaaDemMemorySet[LusMemSetId].usNumOfDtcClearNot;
              /* @Trace: Dem_SUD_API_11119 */
              for (; (LusStartIdx < LusStopIdx) && 
                    (LusStartIdx < DEM_NUMBER_OF_CLEAR_DTC_NOTIFICATION_FNC); LusStartIdx++)
              {
                /* @Trace: Dem_SUD_API_11116 */
                /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
                if (DEM_CLEAR_DTC_NOTIFICATION_FINISH ==
                      Dem_GaaClearDtcNotificationFnc[LusStartIdx].usNotTime)
                {
                  /* @Trace: Dem_SUD_API_11117 */
                  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
                  /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
                  if (NULL_PTR !=
                        Dem_GaaClearDtcNotificationFnc[LusStartIdx].
                          pDemClearDtcNotificationFnc )
                  {
                    /* @Trace: Dem_SUD_API_11120 */
                    Dem_GaaClearDtcNotificationFnc[LusStartIdx].
                      pDemClearDtcNotificationFnc(
                          Dem_ClearDtcState[LucClientId].cds_DTC,
                          Dem_ClearDtcState[LucClientId].cds_DTCFormat,
                          Dem_ClearDtcState[LucClientId].cds_DTCOrigin);
                  }
                  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
                }
              }
              
            }
          }
          #endif
          break;

        /* case DEM_CLEARDTC_STATE_RESULT:
         *  Nothing to do while Dem_ClearDTC returns LddResult */
        default:
          /* Do Nothing */
          break;
      }
    }
  }
  #endif
}

/*******************************************************************************
 * Function Name        : Dem_EvMem_MainFunctionReadAll
 *
 * Service ID           : None
 *
 * Description          : Read all NvData
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionReadAll(void)
{  
  /* Sequence : 
   * [1] NvM_ReadBlock
   * [2] Wait until NvM's Job is finished*/  
  /* @Trace: SWS_Dem_00578
   * If the NVM module was not able to read some nonvolatile data of the Dem
   * module, the Dem module shall initialize all non-volatile data with their
   * initial values.
   */
  if (DEM_TRUE == Dem_EvMem_ReadNvDataIsTriggered())
  { 
    /* Is pending(TRUE: pending)*/
    /* @Trace: Dem_SUD_API_11125 */
    if (DEM_FALSE == Dem_EvMem_ReadAll(DEM_EVMEM_STATUS_INVALID))
    {  
      /* @Trace: Dem_SUD_API_10007 */
      Dem_EvMem_SetReadNvDataTrigger(DEM_FALSE); 
      
      /* Trigger FinishJob after NvM_ReadBlock */
      Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_TRUE);
      #ifndef NVM_GPT_CHANNEL_ID
      (void)SchM_Trigger_Dem_ReleasedTrigger_ToNvM();
      #endif
    }
  }
  else
  {
    /* Wait the result of NvM after NvM_ReadBlock call */
    /* @Trace: Dem_SUD_API_10008 */
    if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
    {
      /* Is pending(TRUE: pending)*/
      /* @Trace: Dem_SUD_API_11123 */
      if (DEM_FALSE == Dem_NvData_WaitNvmFinishJob(
            DEM_EVMEM_STATUS_QUEUED_NVM, DEM_NVM_READ))
      {
        /* @Trace: Dem_SUD_API_10009 */
        Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_FALSE);
        
        /* After BswM accept the DEM_BSWM_MODE_DEM_INIT_FINISH,
         * Dem_Init is called by BswM */      
        BswM_RequestMode(DEM_MODULE_ID, DEM_BSWM_MODE_READBLOCK_END);
      }
    }
  }
}

/*******************************************************************************
 * Function Name        : Dem_EvMem_MainFunctionWriteAll
 *
 * Service ID           : None
 *
 * Description          : Write all NvData
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionWriteAll(void)
{  
  /* Sequence : 
   * [1] NvM_WriteBlock
   * [2] Wait until NvM's Job is finished*/
  if (DEM_TRUE == Dem_EvMem_WriteNvDataIsTriggered())
  {
    /* Is pending(TRUE: pending)*/
    /* @Trace: Dem_SUD_API_11131 */
    if (DEM_FALSE == Dem_EvMem_WriteAll(
          DEM_EVMEM_STATUS_DIRTY | DEM_EVMEM_STATUS_TRIGGER_NVM))
    {
      /* @Trace: Dem_SUD_API_11130 */
      Dem_EvMem_SetWriteNvDataTrigger(DEM_FALSE); 
    }
  }
  else
  {
    if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
    {
      /* Is pending(TRUE: pending)*/
      /* @Trace: Dem_SUD_API_11129 */
      if (DEM_FALSE == Dem_NvData_WaitNvmFinishJob(
            DEM_EVMEM_STATUS_QUEUED_NVM | DEM_EVMEM_STATUS_FINISH_NVM,
            DEM_NVM_WRITE))
      {      
        Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_FALSE);
        if (DEM_JOB_TRIGGER == Dem_EvMem_WriteNvDataEndModeTriggered())
        {
          /* @Trace: Dem_SUD_API_10034 */
          Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_RUNNING);
        }
      }
    }
    else if (DEM_JOB_RUNNING == Dem_EvMem_WriteNvDataEndModeTriggered())
    {
      /* @Trace: Dem_SUD_API_10005 */
      Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_DONE);
      BswM_RequestMode(DEM_MODULE_ID, DEM_BSWM_MODE_WRITEBLOCK_END);
    }
    else
    {
      /* @Trace: Dem_SUD_API_11128 */
      /* Do nothing */
    }
  }
}


/*******************************************************************************
 * Function Name        : Dem_EvMem_AgingEvMemEntry
 *
 * Service ID           : None
 *
 * Description          : Process aging for stored event to remove it from
 *                        event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin, EvMemEntry
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *                        DEM_TRUE : WIR bit is on
 *                        DEM_FALSE: WIR bit is off
 *
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
/* @Trace: SRS_Diag_04065 SRS_Diag_04067 SRS_Diag_04073 SRS_Diag_04133
           SRS_Diag_04141
 */
FUNC(void, DEM_CODE) Dem_EvMem_AgingEvMemEntry(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,  
  Dem_EventMemoryEntryPtrType EvMemEntry)
{ 
  /* @Trace: Dem_SUD_API_11132 */
  #if (DEM_STATUS_BIT_HANDLING_TFSLC == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
  /* @Trace: Dem_SUD_API_10032 */
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - 1U];
  #endif
  /* @Trace: Dem_SUD_API_11143 */
  #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
  Dem_CombinedDtcPCType LddCbDTC;
  /* @Trace: SWS_Dem_00442
   * If a combined DTC (combination on storage) is aged,
   * the Dem module shall remove this event memory entry and reset the status
   * bytes of all sub-events according to [SWS_Dem_00823], [SWS_Dem_00824] and
   * [SWS_Dem_00498]. */
  LddCbDTC = Dem_GetCbDTCByEventId(EventId);
  /* @Trace: Dem_SUD_API_11161 */
  if (NULL_PTR != LddCbDTC)
  #endif  
  {
    #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    if (LddCbDTC->ddNumberOfEvents > 1U)
    {
      Dem_NumOfEventIdType LddstartPos =
          Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
      const Dem_NumOfEventIdType LddEndPos =
          Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
      /* @Trace: Dem_SUD_API_11164 */
      for (; LddstartPos < LddEndPos; LddstartPos++)
      {
        Dem_EventIdType LddEvId = Dem_ListOfCombinedEvents[LddstartPos];

        /* Aging */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        #if (DEM_STATUS_BIT_HANDLING_TFSLC == \
              DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
        /* TestFailedSinceLastClear bit5 = 0 , ConfirmedDTC bit = 0*/
        /* @Trace: SWS_Dem_01054
         * Upon event aging counter reach threshold
         * DemAgingCycleCounterThresholdForTFSLC, the UDS status bit 5
         * (TestFailedSinceLastClear) shall be set to 0 if
         * DemStatusBitHandlingTestFailedSinceLastClear is set to
         * DEM_STATUS_BIT_AGING_AND_DISPLACEMENT.
         */
        if (DEM_ZERO != LddEvent->ucAgingCycleCounterThresholdForTFSLC)
        {
          /* @Trace: Dem_SUD_API_11133 */
          if (LddEvent->ucAgingCycleCounterThresholdForTFSLC <=
                EvMemEntry->AgingCycleCounter)
          {
            /* @Trace: Dem_SUD_API_11166 */
            if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_TFSLC))
            {
              /* @Trace: Dem_SUD_API_11165 */
              Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
            }
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_11136 */
          if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_TFSLC))
          {
            /* @Trace: Dem_SUD_API_11135 */
            Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
          }
        }
        /* @Trace: SWS_Dem_00498
         * Upon event aging counter reach threshold
         * DemAgingCycleCounterThreshold, the UDS status bit 3 shall be set
         * to 0.
         */
        /* @Trace: Dem_SUD_API_11138 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_CDTC))
        {
          /* @Trace: Dem_SUD_API_11137 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
        }
        #else
        /* @Trace: Dem_SUD_API_11141 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_CDTC))
        {
          /* @Trace: Dem_SUD_API_11139 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
        }
        #endif
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        Dem_EvMem_SetUdsStatusByteToNvData(LddEvId);
      }
    }
    else
    #endif
    { /* @Trace: Dem_SUD_API_11163 */
      /* Aging */

      /* @Trace: SWS_Dem_00393
       * The Dem module shall implement the status bit transition for UDS status
       * bit 5 according to figure 7.22 .
       * AgingCriteriaFulfilled */
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      /* @Trace: SWS_Dem_01054
       * Upon event aging counter reach threshold
       * DemAgingCycleCounterThresholdForTFSLC, the UDS status bit 5
       * (TestFailedSinceLastClear) shall be set to 0 if
       * DemStatusBitHandlingTestFailedSinceLastClear is set to
       * DEM_STATUS_BIT_AGING_AND_DISPLACEMENT.
       */
      #if (DEM_STATUS_BIT_HANDLING_TFSLC == \
            DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
      /* TestFailedSinceLastClear bit5 = 0 , ConfirmedDTC bit = 0*/
      if (DEM_ZERO != LddEvent->ucAgingCycleCounterThresholdForTFSLC)
      {
        /* @Trace: Dem_SUD_API_11145 */
        if (NULL_PTR != EvMemEntry)
        {
          /* @Trace: Dem_SUD_API_11146 */
          if (LddEvent->ucAgingCycleCounterThresholdForTFSLC <=
                EvMemEntry->AgingCycleCounter)
          {
            /* @Trace: Dem_SUD_API_11147 */
            if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFSLC))
            {
              /* @Trace: Dem_SUD_API_11150 */
              Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
            }
          }
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_11149 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFSLC))
        {
          /* @Trace: Dem_SUD_API_11148 */
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
        }
      }
      /* @Trace: Dem_SUD_API_11152 */
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC))
      {
        /* @Trace: Dem_SUD_API_11151 */
        Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
      }
      #else
      /* @Trace: Dem_SUD_API_11153 */
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC))
      {
        /* @Trace: Dem_SUD_API_11155 */
        Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
      }
      #endif
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EvMem_SetUdsStatusByteToNvData(EventId);
    }
  }

  /* @Trace: Dem_SUD_API_11156 */
  #if (DEM_STATUS_BIT_HANDLING_TFSLC == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
  boolean LblIsBit5GetTransit =
      Dem_EvIsUdsProcStateTriggered(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
  /* @Trace: Dem_SUD_API_11157 */
  if ((DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFSLC)) ||
     ((DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFSLC)) &&
      (DEM_TRUE == LblIsBit5GetTransit)))
  #endif
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();

    /* @Trace: Dem_SUD_API_11158 */
    #if (DEM_J1939_SUPPORT == STD_ON)
    /* @Trace: Dem_SUD_API_10033 */
    Dem_EvMem_DelChronologicalOrder(DTCOrigin, Dem_EvMemToEventMap[EventId]);
    #endif


    /* @IF_REQ : Checking whether critical section is needed or not when event
     * is removed from memory */
    /* Delete event memory entry  */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_11159 */
    Dem_EvMem_ClearMemLocInEvMemMap(EventId, DTCOrigin, EvMemEntry);
    #else
    /* @Trace: Dem_SUD_API_11160 */
    Dem_EvMem_ClearMemLocInEvMemMap(EventId, DTCOrigin);
    #endif

    Dem_EvMem_SetEventId(EvMemEntry, DEM_NO_EVENT);

    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

    /* @Trace: SWS_Dem_01075
     * Upon event aging, the Dem shall remove the event related Snapshot data
     * (Freeze frame) and extended data records from the event memory.
     */
    /* @Trace: SWS_Dem_00493
     * DemAgingCycleCounterThreshold or DemAgingCycleCounterThresholdForTFSLC
     * (depending on which value is higher) defines the number of completed
     * aging cycles, after which the event memory entry shall be deleted(aged)
     * from the event memory.
     */

    /* @Trace: SWS_Dem_01174
     * The Freeze Frame 0x00 shall be erased if the event was removed from fault
     * memory due to aging.
     */
    Dem_EvMem_ClearEventMemoryEntry(EvMemEntry);

    #if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* Trace: DEM_GEN_02 */
    /* If OBD Memory Exist */
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    if ((DEM_NO_EVMEM_ENTRY != Dem_ObdMemoryId) &&
        (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > Dem_ObdMemoryId))
    {
      if (Dem_PrimaryEventMemory[Dem_ObdMemoryId].EventIdRef == EventId)
      {
        Dem_EvMem_ClearEventMemoryEntry(&Dem_PrimaryEventMemory[Dem_ObdMemoryId]);
        Dem_ObdMemoryId = DEM_NO_EVMEM_ENTRY;
        Dem_EventStatusNvRamData.ObdMemoryId = Dem_ObdMemoryId;
        Dem_EvMem_SetNonVolatieDataStatus(
            DEM_NVDATA_ALL_EVENT_STATUS_ID,
            DEM_EVMEM_STATUS_DIRTY_NVM);
        Dem_EvMem_TriggerWriteAllBlocks();
      }
    }
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    #endif /* (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) */
  }
}

/******************************************************************************
* Function Name        : Dem_EvMem_FindNewTimeStamp
*
* Service ID           : None
*
* Description          : Find the new time stamp to store it in new entry
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant(Not DTCOrigin)
*
* Input Parameters     : EventId, DTCOrigin
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : uint32
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
#if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
FUNC(uint32, DEM_CODE) Dem_EvMem_FindNewTimeStamp(
    Dem_EventIdType EventId,
    Dem_DTCOriginType DTCOrigin)
{
  uint32 LulNewTimeStamp = DEM_ZERO;


  /* @Trace: Dem_SUD_API_11175 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_11167 */
    LulNewTimeStamp = Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
  }
  else
  #endif
  {
    /* @Trace: Dem_SUD_API_11176 */
    LulNewTimeStamp = Dem_MaxTimeStamp[DTCOrigin];
  }

  if (LulNewTimeStamp < (DEM_MAX_TIMESTAMP - (uint32)DEM_ONE))
  /* Valild maximum valie is 0xFFFFFFFE */
  {
    /* @Trace: Dem_SUD_API_11177 */
    LulNewTimeStamp++;
  }
  else
  { /* @Trace: Dem_SUD_API_10028 */
    Dem_NumOfEventMemoryEntryType LddStartIdx = DEM_ZERO;
    Dem_NumOfEventMemoryEntryType LddStopIdx = DEM_ZERO;
    Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_ZERO;

        
    #if (DEM_J1939_SUPPORT == STD_ON)
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_10029 */ 
      Dem_NumOfEventMemoryEntryType LddSizeOfEventMemory = DEM_ZERO;
      Dem_NumOfEventMemoryEntryType LddNumStoredEntry = DEM_ZERO;

      LddSizeOfEventMemory =
          Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);

      if (Dem_NumOfStoredEvtMemEntryies[DTCOrigin] < LddSizeOfEventMemory)
      {
        LulNewTimeStamp = DEM_ONE;
        /* @Trace: Dem_SUD_API_11180 */
        for (LddNumStoredEntry = DEM_ZERO;
             LddNumStoredEntry < Dem_NumOfStoredEvtMemEntryies[DTCOrigin];
             LddNumStoredEntry++)
        {
          LddMemLoc = Dem_PriEvMemChronoOrder[LddNumStoredEntry];
          /* @Trace: Dem_SUD_API_10030 */
          if (LddMemLoc < LddSizeOfEventMemory)
          {
            Dem_EventIdType LddEvId =
                Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, LddMemLoc);
            /* @Trace: Dem_SUD_API_11168 */
            if (DEM_TRUE == Dem_EventIdIsValid(LddEvId))
            {
              Dem_EventMemoryEntryPtrType LddMemEntry =
                  Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, LddMemLoc);
              Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEvId);
              /* polyspace<RTE:UNR:Not a defect:No action planned>
               * If-condition evaluates to true or false according to
               * configuration */
              /* @Trace: Dem_SUD_API_11182 */
              if ((NULL_PTR != LddCbDTC) && (NULL_PTR != LddMemEntry))
              {
                /* @Trace: Dem_SUD_API_11181 */
                LddMemEntry->TimeStamp = LulNewTimeStamp;
                LulNewTimeStamp++;
                Dem_EvMem_SetEvMemNvBlockStatus(
                    DTCOrigin, LddMemLoc, LddCbDTC->EvMemTriggerFlag);
              }
            }
          }
        }
      }
    }
    else
    #endif
    { /* @Trace: Dem_SUD_API_10031 */
      /* @IF_REQ */
      /* Perhaps, almost timeStamp of events will be larage value (0xFFFFXXXX),
       * so these should be initialized*/
      LulNewTimeStamp = DEM_ONE;

      LddStartIdx = Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
      LddStopIdx = Dem_EvMem_GetStopIndexEventMemorySet(EventId, DTCOrigin);
      /* @Trace: Dem_SUD_API_11169 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
      {
        Dem_EventIdType LddEvId = Dem_EvMem_GetEventIdByEvMemEntry(
            DTCOrigin, LddMemLoc);
        /* @Trace: Dem_SUD_API_11170 */
        if (DEM_TRUE == Dem_EventIdIsValid(LddEvId))
        {    
          Dem_EventMemoryEntryPtrType LddMemEntry =
              Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, LddMemLoc);
          Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(LddEvId);
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * If-condition evaluates to true or false according to
           * configuration */
          /* @Trace: Dem_SUD_API_11171 */
          if ((NULL_PTR != cbDTC) && (NULL_PTR != LddMemEntry))
          {
            /* @Trace: Dem_SUD_API_11172 */
            LddMemEntry->TimeStamp = LulNewTimeStamp;
            LulNewTimeStamp++;
            Dem_EvMem_SetEvMemNvBlockStatus(
                DTCOrigin, LddMemLoc, cbDTC->EvMemTriggerFlag);
          }
        }
      }
    }
  } 
  
  if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_11173 */
    Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] = LulNewTimeStamp;
  }
  else
  {
    /* @Trace: Dem_SUD_API_11174 */
    Dem_MaxTimeStamp[DTCOrigin] = LulNewTimeStamp;
  }
  return LulNewTimeStamp;
}
#endif

/******************************************************************************
 * Function Name        : Dem_EvMem_FindEntryWithLowestPriority 
 *
 * Service ID           : None
 *
 * Description          : Function is used to find the event entry that      
 *                        with lowest priority                                           
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, PriorityOfNewEvent, DTCOrigin, DisplacementStrategy
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_NumOfEventMemoryEntryType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04071 SRS_Diag_04073 SRS_Diag_04118
           SRS_Diag_04178 SRS_Diag_04195
 */
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_FindEntryWithLowestPriority(
  Dem_EventIdType EventId,
  Dem_EventPriorityType PriorityOfNewEvent,
  Dem_DTCOriginType DTCOrigin,
  uint8 DisplacementStrategy)
{
  Dem_NumOfEventMemoryEntryType LddMemLoc;
  boolean LblPassivefound = DEM_FALSE;
  boolean LblFound = DEM_FALSE;
  Dem_NumOfEventMemoryEntryType LddStartIdx =
      Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
  Dem_NumOfEventMemoryEntryType LddStopIdx =
      Dem_EvMem_GetStopIndexEventMemorySet(EventId, DTCOrigin);

  struct {
    /* 0 ~255  max number of event memory entries is 255 */  
    Dem_NumOfEventMemoryEntryType LddLoc;
    uint32 LulTimeStamp;
    Dem_EventPriorityType LddPrio;
    Dem_EventIdType LddEventId;
  } LstLowestEvent;

  LstLowestEvent.LddLoc = DEM_NO_EVMEM_IDX;
  LstLowestEvent.LulTimeStamp = DEM_MAX_TIMESTAMP; /* newest time */
  LstLowestEvent.LddPrio = 0xFFU; /* lowest priority */
  LstLowestEvent.LddEventId = DEM_NO_EVENT;

  /***************************************************************
   * [Dem383] A priority value of 1 shall be the highest priority.
   *  Larger priority value shall define lower importance.
   ***************************************************************/
  for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
  {
    /* @Trace: Dem_SUD_API_11194 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_11205 */
    if (LddMemLoc != Dem_ObdMemoryId)
    #endif
    {
      Dem_EventIdType LddEvId;

      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      LddEvId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, LddMemLoc);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      /* evId never be DEM_NO_EVENT, because Event memory is full */
      /* @Trace: Dem_SUD_API_10022 */
      if ((LddEvId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != LddEvId))
      {
        /* evId never be DEM_NO_EVENT, because Event memory is full */
        Dem_EventPriorityType LddPrioOfEvent =
            Dem_Event[LddEvId - DEM_ONE].ucEventPriority;

        /* @Trace: SWS_Dem_00696
         * If the configuration parameter DemOBDEventDisplacement is set to
         * FALSE the Dem module shall process the displacement without the
         * OBDbehavior (refer to figure 7.29).
         */
        /* @Trace: Dem_SUD_API_11216 */
        /* @Trace: Dem_SUD_MACRO_151 */
        #if (DEM_OBD_EVENT_DISPLACEMENT == STD_ON)
        boolean LaaQualifiedDisplacement[DEM_FIVE];
        boolean LblResult = DEM_FALSE;

        if (PriorityOfNewEvent < LddPrioOfEvent)
        {
          /* @Trace: Dem_SUD_API_10023 */
          LblFound = DEM_TRUE;
        }
        /* Eventold is emission related */
        else
        {
          /* @Trace: Dem_SUD_API_11217 */
          Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEvId - 1U];
          uint8 LucMemSetId = LddEvent->ucEventMemDstIdx;
          /* @Trace: Dem_SUD_API_11218 */
          for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_FIVE; LucIdx++)
          {
            /* @Trace: Dem_SUD_API_10021 */
            LaaQualifiedDisplacement[LucIdx] = DEM_FALSE;
          }
          /* @Trace: Dem_SUD_API_11219 */
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEvId);
          /* @Trace: Dem_SUD_API_11220 */
          if (NULL_PTR != LddCbDTC)
          {
            if (DEM_NO_DTC != LddCbDTC->usObdDtc)
            {
              /* @Trace: Dem_SUD_API_11221 */
              LaaQualifiedDisplacement[DEM_ZERO] = DEM_TRUE;
            }
          }
          #endif

          /* @Trace: Dem_SUD_API_11185 */
          /* @Trace: Dem_SUD_MACRO_154 */
          #if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
          /* @Trace: Dem_SUD_API_11186 */
          if (DEM_NO_EVMEM_IDX != LucMemSetId)
          {
            /* @Trace: Dem_SUD_API_11187 */
            if (DEM_NO_IDX_U8 !=
                  Dem_GaaDemMemorySet[LucMemSetId].usDemMILIndicatorRef)
            {
              /* @Trace: Dem_SUD_API_11184 */
              LaaQualifiedDisplacement[DEM_ONE] = DEM_TRUE;
            }
          }
          #endif

          /* @Trace: Dem_SUD_API_11188 */
          #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
          /* @Trace: Dem_SUD_API_11189 */
          if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
          {
            Dem_EventRelatedDataPCType LddEvData =
                &Dem_EventRelatedData[LddEvent->e_PointToData];
            uint16 LusMaxFFRecord =
                LddEvData->FFRecordClassIndex +
                LddEvData->MaxNumOfFreezeFrameRecords;
            /* @Trace: Dem_SUD_API_11190 */
            if (LusMaxFFRecord <= DEM_NUM_OF_FRREZEFRAMERECORDCLASS)
            {
              uint16 LusIRecord;
              /* @Trace: Dem_SUD_API_11191 */
              for (LusIRecord = LddEvData->FFRecordClassIndex;
                   LusIRecord < LusMaxFFRecord;
                   LusIRecord++)
              {
                /* @Trace: Dem_SUD_API_11192 */
                if (DEM_OBD_RECORD_NUMBER ==
                      Dem_FreezeFrameRecordClass[LusIRecord].
                        FreezeFrameRecordNumber)
                {
                  /* @Trace: Dem_SUD_API_10026 */
                  LaaQualifiedDisplacement[DEM_TWO] = DEM_TRUE;
                  break;
                }
              }
            }
          }
          #endif

          /* @Trace: Dem_SUD_API_11193 */
          if (PriorityOfNewEvent >= LddPrioOfEvent)
          {
            /* @Trace: Dem_SUD_API_10025 */
            LaaQualifiedDisplacement[DEM_THREE] = DEM_TRUE;
          }


          /* @Trace: Dem_SUD_API_11195 */
          if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_PDTC))
          {
            /* @Trace: Dem_SUD_API_10027 */
            LaaQualifiedDisplacement[DEM_FOUR] = DEM_TRUE;
          }

          /* @Trace: SWS_Dem_00695
           * If the configuration parameter DemOBDEventDisplacement is set to
           * TRUE all emission related events with the following conditions
           * shall not be considered during the displacement mechanism and
           * shall not displaced from error memory:
           *  + Eventold is emission related
           *    AND
           *  + (Eventold triggers MIL indicator
           *  + OR (Eventold holds legislative Freeze Frame AND has equal or
           *    higher priority)
           *  + OR Pending-DTC==1)
           */
          /* @Trace: Dem_SUD_API_10024 */
          LblResult = LaaQualifiedDisplacement[DEM_ZERO] &
                     (LaaQualifiedDisplacement[DEM_ONE] |
                      LaaQualifiedDisplacement[DEM_TWO] |
                      LaaQualifiedDisplacement[DEM_FOUR]);
        }

        /* @Trace: Dem_SUD_API_11196 */
        if ((DEM_TRUE == LblFound) ||
            ((DEM_FALSE == LblResult) &&
                (DEM_TRUE == LaaQualifiedDisplacement[DEM_THREE])))
        #endif
        {
          /* Priority of reported event <= priority of found entries? */
          /* @Trace: SWS_Dem_00406
           * If event displacement is enabled (DemEventDisplacementStrategy
           * selects DEM_DISPLACEMENT_FULL in DemPrimaryMemory or
           * DemUserDefinedMemory or  DEM_DISPLACEMENT_PRIO_OCC), the Dem
           * module shall perform the following sequence by combination of the
           * different displacement criteria (refer to figure 7.29):
           * 1. Priority (refer [SWS_Dem_00403])
           * 2. Active/Passive status (configurable, only for
           * DEM_DISPLACEMENT_FULL in DemPrimaryMemory or DemUserDefinedMemory)
           * (refer [SWS_Dem_00404])
           * 3. Occurrence (refer [SWS_Dem_00405])
           */
          /* @Trace: SWS_Dem_00403
           * If displacement strategy is DEM_DISPLACEMENT_FULL or
           * DEM_DISPLACEMENT_PRIO_OCC (refer to DemPrimaryMemory or
           * DemUserDefinedMemory), the Dem module shall displace lower
           * prioritized events by higher prioritized events.
           */
          /* @Trace: Dem_SUD_API_11197 */
          if (PriorityOfNewEvent <= LddPrioOfEvent)
          {
            LblFound = DEM_FALSE;

            /*Passive memory entries found?  Passive status = TestFailed bit is
             * 0 */
            /* Group I : passsive event memory entries */
            /* @Trace: SWS_Dem_00404
             * If displacement strategy is DEM_DISPLACEMENT_FULL(refer to
             * DemPrimaryMemory or DemUserDefinedMemory), the Dem module shall
             * displace passive events preferably (refer to chapter 7.7.1.4).
             */
            /* @Trace: Dem_SUD_API_11198 */
            if (DEM_DISPLACEMENT_FULL == DisplacementStrategy)
            {
              /* @Trace: Dem_SUD_API_11199 */
              if (DEM_ZERO == (Dem_AllEventStatusByte[LddEvId] &
                  (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF))
              {
                /* @Trace: Dem_SUD_API_11201 */
                if (DEM_FALSE == LblPassivefound)
                {
                  /* @Trace: Dem_SUD_API_11200 */
                  LblPassivefound = DEM_TRUE;
                  LstLowestEvent.LddLoc = DEM_NO_EVMEM_IDX;
                }
                LblFound = DEM_TRUE;
              }
            }
            /* Group II : No passive event ,
             * Priority of reported event < priority of found entries? */
            /* @Trace: Dem_SUD_API_11202 */
            if (DEM_FALSE == LblPassivefound)
            {
              /* @Trace: SWS_Dem_00692
               * If an event is reported and an event memory entry with the
               * same priority exists and the existing event is not tested in
               * this operation cycle (TestNotCompletedThisOperationCycle bit
               * == 1), the Dem shall displace the existing event with the
               * reported event.
               */

              /* @Trace: SWS_Dem_00693
               * If an event is reported and an event memory entry with the
               * same priority exists and the existing event is tested in this
               * operation cycle (TestNotCompletedThisOperationCycle bit == 0),
               * the Dem shall discard the reported event.
               */
              if (PriorityOfNewEvent < LddPrioOfEvent)
              {
                /* @Trace: Dem_SUD_API_11203 */
                LblFound = DEM_TRUE;
              }
              else if (PriorityOfNewEvent == LddPrioOfEvent)
              {
                /* @Trace: Dem_SUD_API_11207 */
                if (DEM_IS_BIT_SET_UDSSTATUSBYTE(
                      LddEvId, DEM_UDS_STATUS_TNCTOC))
                {
                  /* @Trace: Dem_SUD_API_11204 */
                  LblFound = DEM_TRUE;
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_11206 */
                /* Nothing to do */
              }
            }
            /* @Trace: Dem_SUD_API_11208 */
            if (DEM_TRUE == LblFound)
            {
              Dem_EventMemoryEntryPtrType LddEvMemEntry =
                  Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, LddMemLoc);
              /* polyspace<RTE:UNR:Not a defect:No action planned>
               * If-condition evaluates to true or false according to
               * configuration */
              /* @Trace: SWS_Dem_00407
               * If no event memory entry for displacement was identified, the
               * Dem module shall discard the storage request.
               */
              /* @Trace: Dem_SUD_API_11209 */
              if (NULL_PTR != LddEvMemEntry)
              {
                /* @Trace: Dem_SUD_API_11210 */
                #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
                uint32 LulTStamp = LddEvMemEntry->TimeStamp;
                /* Displace oldest found entry with reported event */
                if (DEM_NO_EVMEM_IDX == LstLowestEvent.LddLoc)
                {
                  /* @Trace: Dem_SUD_API_11211 */
                  LstLowestEvent.LddLoc = LddMemLoc;
                  LstLowestEvent.LulTimeStamp = LulTStamp;
                  LstLowestEvent.LddPrio = LddPrioOfEvent;
                  LstLowestEvent.LddEventId = LddEvId;
                }
                else
                {
                  /* if a current event is oldest and lower priority than a
                   * previous event  */
                  if (LddPrioOfEvent == LstLowestEvent.LddPrio)
                  {
                    /* lower time stamp is oldest event */
                /* @Trace: SWS_Dem_00405
                 * If displacement strategy is DEM_DISPLACEMENT_FULL or
                 * DEM_DISPLACEMENT_PRIO_OCC (refer to DemPrimaryMemory or
                 * DemUserDefinedMemory), the Dem module shall displace older
                 * stored events in the chronological order prior to newer
                 * stored events (refer [SWS_Dem_00412] and [SWS_Dem_00787]).
                 */
                    /* @Trace: Dem_SUD_API_11213 */
                    if (LulTStamp < LstLowestEvent.LulTimeStamp)
                    {
                      /* @Trace: Dem_SUD_API_11212 */
                      LstLowestEvent.LddLoc = LddMemLoc;
                      LstLowestEvent.LulTimeStamp =  LulTStamp;
                      LstLowestEvent.LddPrio = LddPrioOfEvent;
                      LstLowestEvent.LddEventId = LddEvId;
                    }
                  }
                  else if (LddPrioOfEvent > LstLowestEvent.LddPrio)
                  {
                    /* @Trace: Dem_SUD_API_11214 */
                    LstLowestEvent.LddLoc = LddMemLoc;
                    LstLowestEvent.LulTimeStamp =  LulTStamp;
                    LstLowestEvent.LddPrio = LddPrioOfEvent;
                    LstLowestEvent.LddEventId = LddEvId;
                  }
                  else
                  {
                    /* @Trace: Dem_SUD_API_11215 */
                    /* Do nothing */
                  }
                }
                #endif
              }
            }
          }
        }
      }
    }
  }
  /* Found a event to be displaced */
  /* @Trace: Dem_SUD_API_13313 */
  if (DEM_NO_EVMEM_IDX != LstLowestEvent.LddLoc)
  {
    Dem_EventIdType LddEventIdOldest  = LstLowestEvent.LddEventId;
    
    Dem_EventMemoryEntryPtrType LddEvMemEntry =
        Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin,LstLowestEvent.LddLoc);
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates
     * to true or false according to configuration */
    /* @Trace: Dem_SUD_API_13321 */
    if (NULL_PTR != LddEvMemEntry)
    {
      Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEventIdOldest);
      /* @Trace: Dem_SUD_API_13322 */
      if (NULL_PTR != LddCbDTC) /* useless if-condition */
      {
        Dem_UdsStatusByteType LddMaskToClear =
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC |
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC;

        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* EventId shall be rechecked because of the preemption problem */
        if (Dem_EvMem_GetEventIdByEvMemEntry(
            DTCOrigin, LstLowestEvent.LddLoc) == LddEventIdOldest)
        {
          Dem_EvInitProcState(LddEventIdOldest);  

          /*Set to new event id for locking an event memory entry. */
          Dem_EvMem_SetEventId(LddEvMemEntry, EventId);
          
          #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
          /* @Trace: Dem_SUD_API_13325 */
          Dem_EvMem_ClearMemLocInEvMemMap(
              LddEventIdOldest, DTCOrigin, LddEvMemEntry);
          #else
          /* @Trace: Dem_SUD_API_13324 */
          /* @Trace: SWS_Dem_00408
           * If the event memory entry for displacement was identified, the Dem
           * module shall remove this event memory entry from the event memory.
           */
          Dem_EvMem_ClearMemLocInEvMemMap(LddEventIdOldest, DTCOrigin);
          #endif
          
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          /* @Trace: Dem_SUD_API_13326 */
          #if (DEM_J1939_SUPPORT == STD_ON)
          /* @Trace: Dem_SUD_API_13327 */
          Dem_EvMem_DelChronologicalOrder(DTCOrigin, LstLowestEvent.LddLoc);
          #endif

          /* Dem784_Conf : the "TestFailedSinceLastClear" status bits are reset
           * to 0 */
          /* @Trace: SWS_Dem_01186
           * If an event memory entry was removed during displacement, the UDS
           * status bit 5 shall be reset to 0 in case of
           * DemStatusBitHandlingTestFailedSinceLastClear is set to
           * DEM_STATUS_BIT_AGING_AND_DISPLACEMENT and
           * DemResetConfirmedBitOnOverflow is set to true.
           */
          #if ((DEM_STATUS_BIT_HANDLING_TFSLC == \
                DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) && \
               ((DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE) || \
                (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_ON)))
          /* @Trace: Dem_SUD_API_13314 */
          LddMaskToClear |= (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC;
          #else
          /* @Trace: Dem_SUD_API_13328 */
          DEM_UNUSED(LddMaskToClear);
          #endif  

          /* @Trace: SWS_Dem_00443
           * If a combined DTC (combination on storage) is displaced,
           * the Dem module shall remove this event memory entry and reset the
           * status bytes of all sub-events according to [SWS_Dem_00409] and
           * [SWS_Dem_01186] */

          /* @Trace: SWS_Dem_00542
           * For combination on retrieval, the displacement algorithm for each
           * event of a combined DTC shall be treated individually (refer to
           * [SWS_Dem_00408]).
           */
          #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
          /* @Trace: Dem_SUD_API_13320 */
          /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Same as Dead Code" */
          if (NULL_PTR != LddCbDTC)
          {
            Dem_NumOfEventIdType LddStartPos =
                Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
            const Dem_NumOfEventIdType LddEndPos =
                Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
            /* @Trace: Dem_SUD_API_13318 */
            while (LddStartPos < LddEndPos)
            {
              /* @Trace: Dem_SUD_API_13319 */
              Dem_EventIdType LddTmpEvId =
                  Dem_ListOfCombinedEvents[LddStartPos];
              /* @Trace: SWS_Dem_00409
               * If an event memory entry was removed during displacement, the
               * Dem module shall reset the UDS status bit 2 and UDS status bit
               * 3 to 0 if the configuration parameter
               * DemResetConfirmedBitOnOverflow (refer to DemGeneral) is set to
               * true.
               */  
              DEM_CLR_UDSSTATUSBYTE(LddTmpEvId, LddMaskToClear);
              
              /* All EventStatus NvRam data shall be initialized */
              Dem_EvMem_SetUdsStatusByteToNvData(LddTmpEvId);
              ++LddStartPos;
            }
          }
          /* polyspace-end MISRA-C3:14.3 [Justified:Low] "Same as Dead Code" */
          #else
          /* @Trace: Dem_SUD_API_13317 */
          /* @Trace: SWS_Dem_00409
           * If an event memory entry was removed during displacement, the Dem
           * module shall reset the UDS status bit 2 and UDS status bit 3 to 0
           * if the configuration parameter DemResetConfirmedBitOnOverflow
           * (refer to DemGeneral) is set to true.
           */
          /* @Trace: Dem_SUD_API_13316 */
          /* @Trace: Dem_SUD_MACRO_144 */
          #if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_ON)
          /* @Trace: Dem_SUD_API_13315 */
          DEM_CLR_UDSSTATUSBYTE(LddEventIdOldest, LddMaskToClear);
          #endif
          /* All EventStatus NvRam data shall be initialized */        
          Dem_EvMem_SetUdsStatusByteToNvData(LddEventIdOldest);
          #endif  

          /* EventStatus of removed events shall be updated to NvData */
          Dem_EvMem_SetNonVolatieDataStatus(
              DEM_NVDATA_ALL_EVENT_STATUS_ID, LddCbDTC->EvMemTriggerFlag);
        }
        else
        {
          /* @Trace: Dem_SUD_API_13323 */
          LstLowestEvent.LddLoc = (Dem_NumOfEventMemoryEntryType)DEM_NO_EVENT;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    }
  }


  return LstLowestEvent.LddLoc;
}


/*
@bool check(uint32_t theArray[], uint32_t compareVal)
{
    uint32_t i;
    uint32_t x = theArray[SIZE-1];
    if (x == compareVal)
        return true;
    theArray[SIZE-1] = compareVal;
    for (i = 0; theArray[i] != compareVal; i++);
    theArray[SIZE-1] = x;
    return i != SIZE-1;
}
*/


/******************************************************************************
 * Function Name        : Dem_EvMem_VerifyAllEventMemories
 *
 * Service ID           : None
 *
 * Description          : Puts the default initial values into
 *                        non-volatile data
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
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
/* @Trace: SRS_Diag_04107 SRS_BSW_00301
 */
/* polyspace +1 CODE-METRICS:LEVEL CODE-METRICS:CALLS CODE-METRICS:PATH[Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_EvMem_VerifyAllEventMemories(void)
{
  uint8 LucIdx;
  uint8 LucClearType;
  Dem_EventIdType LddEventId;
  boolean LblNvmBlocksVirgin = DEM_TRUE;

  /* Checks magic key */
  /* @Trace: SWS_Dem_00339
   * The Dem module shall verify the validity (which relates to block states),
   * integrity (which relates to CRC results), and for general NvM-reading
   * errors of its nonvolatile blocks (before using the respective data).
   */
  /* @Trace: Dem_SUD_API_11222 */
  if (NVM_REQ_OK == Dem_NvData_GetNvMErrorStatus(Dem_NonVolatileDataBlkId))
  {
    /* @Trace: Dem_SUD_API_10019 */
    if (DEM_TRUE == Dem_EvMem_CheckFirstEcuRun()) 
    {
      /* @Trace: Dem_SUD_API_11233 */
      LblNvmBlocksVirgin = DEM_FALSE;
    }
  }

  /* @Trace: Dem_SUD_API_11244 */
  if (DEM_TRUE == LblNvmBlocksVirgin)
  {
    Dem_EvMem_ResetManagementBlock(DEM_TRUE);
    /* @Trace: Dem_SUD_API_11255 */
    #if defined(DEM_NVM_BLK_ID_NON_VOLATILE_DATA)
    /* @Trace: Dem_SUD_API_11264 */
    #if (DEM_NVM_BLK_ID_NON_VOLATILE_DATA > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11265 */
    Dem_EvMem_SetNonVolatieDataStatus(
        DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
    #endif
    #endif
  }
  
  /* @Trace: Dem_SUD_API_11266 */
  #if defined(DEM_NVM_BLK_ID_EVENT_STATUS)
  /* @Trace: Dem_SUD_API_11267 */
  #if (DEM_NVM_BLK_ID_EVENT_STATUS> DEM_ZERO)
  /* Checks  the Event Status Block */
  LucClearType = DEM_NVBLOCK_INVALID;
  NvM_RequestResultType LddResult =
      Dem_NvData_GetNvMErrorStatus(Dem_EventStatusNvRamBlkId);
  /* @Trace: Dem_SUD_API_11268 */
  if (NVM_REQ_NV_INVALIDATED != LddResult) /* It does not matter to #3260 */
  {
    if ((DEM_FALSE == LblNvmBlocksVirgin) && ((NVM_REQ_OK == LddResult)
       #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
       || (NVM_REQ_BLOCK_SKIPPED == LddResult)
       #endif
       ))
    {
      /* @Trace: Dem_SUD_API_11223 */
      LucClearType = DEM_NVBLOCK_SUCCESS;
    }
    else
    {
      /* @Trace: Dem_SUD_API_11224 */
      /* If AllNvBlocksReset is TRUE and result of the block is not
       * NVM_REQ_NV_INVALIDATED it is not possible to determine whether a value
       * of NvRam Block is valid */
      LucClearType = DEM_NVBLOCK_FAILED;
    }
  }

  if (DEM_NVBLOCK_SUCCESS == LucClearType)
  {
    /* @Trace: Dem_SUD_API_11229 */
    #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
    Dem_NumOfPrestoredFFType LddIndex;
    /* @Trace: Dem_SUD_API_11228 */
    /* polyspace +2 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
    for (LddIndex = DEM_ZERO;
         LddIndex < DEM_MAX_NUMBER_PRESTORED_FF;
         LddIndex++)
    {
      /* @Trace: Dem_SUD_API_11230 */
      #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
      uint32 LulIndexPr;
      /* @Trace: Dem_SUD_API_11231 */
      /* polyspace +2 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      for (LulIndexPr = DEM_ZERO;
           LulIndexPr < DEM_SIZE_OF_PRESTORED_FF;
           LulIndexPr++)
      {
        /* @Trace: Dem_SUD_API_11232 */
        Dem_GaaPrestoreBuffer[LddIndex].data[LulIndexPr] =
            Dem_NonVolatileData.DataPrestored[LddIndex].data[LulIndexPr];
      }
      #endif
      Dem_GaaPrestoreBuffer[LddIndex].EventIdRef =
          Dem_NonVolatileData.EvIdPrestored[LddIndex];
    }
    #endif
  }
  else
  #endif
  #endif
  {
    #if defined(DEM_NVM_BLK_ID_EVENT_STATUS)
    #if (DEM_NVM_BLK_ID_EVENT_STATUS> DEM_ZERO)
    if (DEM_NVBLOCK_FAILED == LucClearType)
    {
      /* @Trace: Dem_SUD_API_11226 */
      Dem_EvMem_ResetEventStatusNvRamBlock();
      Dem_EvMem_SetNonVolatieDataStatus(
          DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
      Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
    }
    else /* DEM_NVBLOCK_INVALID */
    #endif
    #endif
    {
      /* @Trace: Dem_SUD_API_11227 */
      Dem_EvMem_ResetEventStatusNvRamBlock();
    }
  }

  /* @Trace: Dem_SUD_API_11235 */
  for (LddEventId = DEM_ZERO; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
  {
    /* @Trace: Dem_SUD_API_11234 */
    Dem_EvMemToEventMap[LddEventId] = DEM_NO_EVMEM_ENTRY; /* 0xFF */
  }

  /* @Trace: Dem_SUD_API_11237 */
  for (LucIdx = DEM_ZERO; LucIdx < Dem_NumOfSupportedDTCOrigins; LucIdx++)
  {
    /* @Trace: Dem_SUD_API_11236 */
    Dem_EvMem_ResetNumOfStoredEvtMemEntries(Dem_SupportedDTCOrigins[LucIdx]);
  }

  /* @Trace: Dem_SUD_API_11239 */
  for (uint8 LucClientId = DEM_ZERO;
             LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientId++)
  {
    /* Checks the Event Memory Entry Block */
    /* @Trace: Dem_SUD_API_11238 */
    for (LucIdx = DEM_ZERO; LucIdx < Dem_NumOfSupportedDTCOrigins; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_11241 */
      NvM_BlockIdType LddBlockId;
      Dem_NumOfEventMemoryEntryType LddMemLoc;
      Dem_DTCOriginType LddDTCOrigin = Dem_SupportedDTCOrigins[LucIdx];

      Dem_NumOfEventMemoryEntryType LddStartIdx =
          Dem_EvMem_GetStartIndexEvMemory(LucClientId, LddDTCOrigin);
      Dem_NumOfEventMemoryEntryType LddStopIdx =
          Dem_EvMem_GetStopIndexEvMemory(LucClientId, LddDTCOrigin);

      /* @Trace: Dem_SUD_API_11242 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
      {
        Dem_EventMemoryEntryPtrType LddMemEntry =
            Dem_EvMem_GetEmEntryByMemPosition(LddDTCOrigin, LddMemLoc);
        LddEventId = Dem_EvMem_GetEventIdByEvMemEntry(LddDTCOrigin, LddMemLoc);
        LucClearType = DEM_NVBLOCK_INVALID; /* Clear and Call NvM_WriteBlock */
        /* polyspace<RTE:UNR:Not a defect:No action planned> Not a defect */
        /* @Trace: Dem_SUD_API_11243 */
        if (E_OK == Dem_NvData_GetNvMBlockId(
            DEM_NVDATA_EVENT_MEMORY_ID, LddDTCOrigin, LddMemLoc, &LddBlockId))
        {
          NvM_RequestResultType LddReqResult =
              Dem_NvData_GetNvMErrorStatus(LddBlockId);
          /* @Trace: Dem_SUD_API_11245 */
          if (NVM_REQ_NV_INVALIDATED != LddReqResult)
          /* It does not matter to #3260 */
          {
            LucClearType = DEM_NVBLOCK_FAILED;
            /* @Trace: Dem_SUD_API_11246 */
            if ((DEM_FALSE == LblNvmBlocksVirgin) &&
                ((NVM_REQ_OK == LddReqResult)
                #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
                || (NVM_REQ_BLOCK_SKIPPED == LddReqResult)
                #endif
               ))
            {
              /* Is empty? */
              if (DEM_ZERO != LddEventId) /* starts from 1 */
              {
                /* @Trace: Dem_SUD_API_11247 */
                if (LddEventId <= DEM_NUMBER_OF_EVENTS)
                {
                  /* @Trace: Dem_SUD_API_11248 */
                  if (DEM_TRUE == Dem_EventHasDtc(LddEventId))
                  {
                    LucClearType = DEM_NVBLOCK_SUCCESS;
                    /* @Trace: Dem_SUD_API_11249 */
                    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
                    /* @Trace: Dem_SUD_API_11250 */
                    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
                    if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(LddDTCOrigin))
                    {
                      /* @Trace: Dem_SUD_API_11252 */
                      DEM_EVMEM_SET_MAX_TIMESTAMP(
                          LddMemEntry->TimeStamp,
                          DEM_DTC_ORIGIN_USERDEFINED_MEMORY);
                    }
                    else
                    #endif
                    {
                      /* @Trace: Dem_SUD_API_11251 */
                      DEM_EVMEM_SET_MAX_TIMESTAMP(
                          LddMemEntry->TimeStamp, LddDTCOrigin);
                    }
                    #endif
                    Dem_EvMem_AddMemLocInEvMemMap(
                        LddEventId, LddDTCOrigin, LddMemLoc);
                  }
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_10020 */
                LucClearType = DEM_NVBLOCK_INVALID;
              }
            }
          }
        }
        /* @Trace: Dem_SUD_API_11253 */
        if (DEM_NVBLOCK_SUCCESS != LucClearType)
        {
          if (DEM_NVBLOCK_FAILED == LucClearType)
          {
            Dem_EvMem_ClearEventMemoryEntry(LddMemEntry);
            /* @Trace: Dem_SUD_API_11256 */
            #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                 (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
            /* @Trace: Dem_SUD_API_11257 */
            if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == LddDTCOrigin)
            {
              /* @Trace: Dem_SUD_API_11258 */
              Dem_EvMem_ClearPermanentMemEntry(LddMemLoc, LddEventId);
            }
            #endif
            Dem_EvMem_SetEvMemNvBlockStatus(
                LddDTCOrigin, LddMemLoc, DEM_EVMEM_STATUS_DIRTY_NVM);
            Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
          }
          else /* DEM_NVBLOCK_INVALID */
          {
            /* If AllNvBlocksReset is TRUE and result of the block is not
             * NVM_REQ_NV_INVALIDATED it is not possible to determine whether
             * a value of NvRam Block is valid */
            /* @Trace: Dem_SUD_API_11259 */
            Dem_EvMem_ClearEventMemoryEntry(LddMemEntry);
            #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                 (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
            /* @Trace: Dem_SUD_API_11260 */
            if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == LddDTCOrigin)
            {
              /* @Trace: Dem_SUD_API_11261 */
              Dem_EvMem_ClearPermanentMemEntry(LddMemLoc,LddEventId);
            }
            #endif
          }
        }
      }

      /* @Trace: Dem_SUD_API_11262 */
      #if (DEM_J1939_SUPPORT == STD_ON)
      /* @Trace: Dem_SUD_API_11263 */
      Dem_EvMem_InitChronologicalOrder(LddDTCOrigin);
      #endif
    }
  }
}     

/******************************************************************************
 * Function Name        : Dem_EvMem_Init
 *
 * Service ID           : None
 *
 * Description          : Initialize the even memory
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
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        
 *
 *                        Function(s) invoked :
 *                        DEM_RST_UDSSTATUSBYTE()
 *****************************************************************************/
/* @Trace: SRS_Diag_04066 SRS_Diag_04067
 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_EvMem_Init(void)
{
  Dem_EventIdType LddEventId;

  /* If WIR or TFTOC or TF or CDTC or PDTC or TFSLC bit is true 
   +--------------------------------------+-------+
   |Bit                                   |NotUsed|
   +------------------------------------+-+-------+
   | TestFailed                         |0|   0   |
   +------------------------------------+-+-------+
   | TestFailedThisOperationCycle       |1|   0   |
   +------------------------------------+-+-------+
   | PendingDTC                         |2|   0   | if TFTOC is 1, set to 1 on
   +------------------------------------+-+-------+ EvMemInit(?)
   | ConfirmedDTC                       |3|   0   |
   +------------------------------------+-+-------+
   | TestNotCompletedSinceLastClear     |4|   1   | set to 1 on EvMemInit
   +------------------------------------+-+-------+
   | TestFailedSinceLastClear           |5|   0   |
   +------------------------------------+-+-------+
   | TestNotCompletedThisOperationCycle |6|   1   | set to 1 on operation cycle
   +------------------------------------+-+-------+ changed
   | WarningIndicatorRequested          |7|   0   |
   +------------------------------------+-+-------+*/

  /* Loop through the number of events */
  DEM_RST_UDSSTATUSBYTE(DEM_NO_EVENT, DEM_ZERO);
  for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEventId);
    /* @Trace: SWS_Dem_01199, SWS_Dem_01207
     * The Dem module shall support the configuration parameter
     * DemMemoryDestinationRef to define the destination memory/
     * memories for individual DTCs. When using the Dem interfaces,
     * Dem_DTCOriginType selects the destination memories.
     */
    Dem_DTCOriginType LddDTCOrigin = LddEvent->aaEventDestination;
    if ((DEM_NO_DTC_ORIGIN != LddDTCOrigin) && (NULL_PTR != LddCbDTC))
    {
      boolean LblDirty = DEM_FALSE;    
      /* Get current EventStatusByte */      
      Dem_UdsStatusByteType LddEventStatusByteOld;
      Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[LddEventId];

      /* Read EventStatusByte from NvData */
      DEM_RST_UDSSTATUSBYTE(LddEventId, Dem_EvMem_GetUdsStatusByteToNvData(
          LddEventId, LddDTCOrigin));
      
      /* Get old event status after Dem_EvMem_GetUdsStatusByteToNvData */
      LddEventStatusByteOld = Dem_AllEventStatusByte[LddEventId];
      
      /* If event is stored in the event memory */
      Dem_NumOfEventMemoryEntryType LddSizeOfMem =
          Dem_EvMem_GetSizeOfElementEventMemory(LddEventId, LddDTCOrigin);
      Dem_NumOfEventMemoryEntryType LddStartIndex =
          Dem_EvMem_GetStartIndexEventMemorySet(LddEventId, LddDTCOrigin);
      LddSizeOfMem = LddSizeOfMem + LddStartIndex;
      /* @Trace: Dem_SUD_API_11279 */
      if (LddMemLoc < LddSizeOfMem)
      {    
        uint8 LucCycleStateOld = DEM_CYCLE_STATE_START;

        /* if OpCycleStorage is off, OperationCycleState was initialized as 0
         * (START) by 'START CODE' So , if OpCycleState is END(1), it means
         * OpCycleStorage is on and state is stored.*/
        Dem_EvMem_GetOpCycleState(
            LddEvent->e_OperationCycleId, &LucCycleStateOld);

        if ((DEM_CYCLE_STATE_START != LucCycleStateOld) &&
            ((LddEventStatusByteOld & DEM_BITMASK_RESET_PDTC) ==
                (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC))
        {
          /* @Trace: Dem_SUD_API_11282 */
          DEM_CLR_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_PDTC);
        }
        else
        {
          /* PedingDTC = 0->1 
           * [1] An event is stored
           * [2] TestFailedThisOperationCycle is true(Event was failed
           *     previously)
           * [3] storage  condition is not supported
           *     if it is used, the status of PDTC can not be determined.
           */
          /* @Trace: Dem_SUD_API_11283 */
          #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
          /* @Trace: Dem_SUD_API_11284 */
          if (DEM_ZERO == LddEvent->ucNumOfStorageCondition)
          #endif
          {
            /* @Trace: Dem_SUD_API_11285 */
            if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(
                  LddEventId, DEM_UDS_STATUS_PDTC))
            {
              /* @Trace: Dem_SUD_API_10018 */
              if (DEM_IS_BIT_SET_UDSSTATUSBYTE(
                    LddEventId, DEM_UDS_STATUS_TFTOC))
              {
                /* @Trace: Dem_SUD_API_11286 */
                DEM_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_PDTC);
              }    
            }
          }
        }
        
        DEM_CLR_UDSSTATUSBYTE(
            LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC); /* Bit 6 */
        DEM_SET_UDSSTATUSBYTE(
            LddEventId,
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);  /* Bit 5 */
      }
      else
      {
        /* @Trace: Dem_SUD_API_11287 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_CDTC))
        {
          /* @Trace: Dem_SUD_API_11278 */
          DEM_RST_UDSSTATUSBYTE(
              LddEventId,
              ((uint8)DEM_UDS_STATUS_TNCTOC | (uint8)DEM_UDS_STATUS_TNCSLC));
        }
      }

      /*[Checked]*/
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEventId,
         (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF    | /* Bit 0 */
         (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC | /* Bit 1 */
         (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC  | /* Bit 2 */
         (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC  | /* Bit 3 */
         (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC | /* Bit 5 */
         (Dem_UdsStatusByteType)DEM_UDS_STATUS_WIR))   /* Bit 7 */
      {
        /* @Trace: Dem_SUD_API_11270 */
        DEM_SET_UDSSTATUSBYTE(
            LddEventId,(Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC); /* Bit 5 */
        DEM_CLR_UDSSTATUSBYTE(
            LddEventId,(Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC); /* Bit 6 */
      }
      /* @IF_REQ : Apply cbDTC->UdsStatusAvailabilityMask ?  */
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition evaluates to true or false according to configuration */
      else 
      {
        uint8 LucMask =
            Dem_EvMem_GetAvailableMaskFromMemSetIdx(LddEvent->ucEventMemDstIdx);
        /* @Trace: Dem_SUD_API_11271 */
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        if (DEM_ZERO ==
              ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC & LucMask))
        {
          /* @Trace: Dem_SUD_API_11272 */
          DEM_SET_UDSSTATUSBYTE(
              LddEventId,
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC);  /* Bit 5 */
          /* TFSLC is cleared already */
        }
      }     

      /* [Checked] */
      /* @Trace: Dem_SUD_API_11273 */
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TF))
      {
        /* @IF_REQ : [SWS_Dem_00525] 
         * If the configuration parameter DemStatusBitStorageTestFailed is set
         * to True, the Dem module shall retain the information for UDS DTC
         * status bit 0 (TestFailed) over power cycles Question) power cycle is
         * ECU reset or Operation Cycle(DEM_OPCYC_POWER)? */

        /* @Trace: SWS_Dem_00388
         * If the configuration parameter DemStatusBitStorageTest-Failed is set
         * to False, the Dem module shall not retain the information for UDS
         * status bit 0 over power cycles (volatile). */

        /* @Trace: SWS_Dem_00525
         * If the configuration parameter DemStatusBitStorageTest-Failed is set
         * to True, the Dem module shall retain the information for UDS status
         * bit 0 over power cycles (non-volatile). */
        if (DEM_FALSE == DEM_GET_EVENTPARAM_STORAGE_TF(LddEvent->ParamFieldsA))
        {/* @Trace: Dem_SUD_API_11274 */
          DEM_CLR_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TF);
        }
      }
      
      /*[Checked]*/
      /* @Trace: Dem_SUD_API_11276 */
      if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_WIR)) &&
          (DEM_WIR_RESET_ON_OPERATIONCYCLE_START ==
              DEM_GET_EVENTPARAM_RESET_WIR(LddEvent->ParamFieldsA)))
      {
        /* @Trace: Dem_SUD_API_11275 */
        DEM_CLR_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_WIR);
        LblDirty |= Dem_InitIndicator(LddEventId);
      }

      /* @Trace: SWS_Dem_00389
       * Should not be applied in the AUTOEVER platform to support
       * the vendor specific requirements(aging/healing) and
       * therefore DEM_UDS_STATUS_TFTOC always is non-volatile data
       *
       * NOTE : DEM_UDS_STATUS_TNCTOC,DEM_UDS_STATUS_TFTOC SHALL BE INITIALIZED
       * ON OPERATION CYCLE START
       *
       * The information for UDS DTC status bit 1 (TestFailedThisOperationCycle)
       * is non-volatile, if the PendingDTC bit is used (refer to
       * [SWS_Dem_00006]) or if the Dem module supports operation cycles over
       * power cycles
       * 1. PendingDTC is not used
       * 2. OperationCycleState Storage is off */
      (void)Dem_EvMem_TriggerNvDataStorage(
        LddEventId, LddDTCOrigin, LddEventStatusByteOld,
        LddCbDTC->EvMemTriggerFlag, DEM_FALSE, LblDirty);
    }
    else
    {
      /* @Trace: Dem_SUD_API_10017 */
      DEM_RST_UDSSTATUSBYTE(
          LddEventId,
          ((uint8)DEM_UDS_STATUS_TNCTOC | (uint8)DEM_UDS_STATUS_TNCSLC));
    }

    /* @Trace: SWS_Dem_00391
     * Note: The information for UDS DTC status bit 3(ConfirmedDTC) is
     * non-volatile (but it is also calculable based on the respective event
     * memory entry).
     */
    /* @Trace: SWS_Dem_00392
     * Note: The information for UDS DTC status bit 4
     * (TestNotCompletedSinceLastClear) is non-volatile.
     */
    /* @Trace: SWS_Dem_00393
     * Note: The information for UDS DTC status bit 5
     * (TestFailedSinceLastClear) is nonvolatile.
     */
    /* @Trace: SWS_Dem_00395
     * Note: The information for UDS  DTC  status bit 7
     * (WarningIndicatorRequested) maybe volatile
     * (because it is calculated based on the assigned warning indicator
     * states).
     */
    /* But we don't use the warning indicator states, so bit 7 is non-volatile
     * except MIL_ON */
  }

  Dem_EvMem_InitIndicatorBehaviorAccumulator();

      /* Trace: DEM_CYCLE_03 */

  /* Init for result for all client as E_NOT_OK (not selected) */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11281 */
  for (uint8 LucClientId = DEM_ZERO;
             LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientId++)
  {
    /* @Trace: Dem_SUD_API_11280 */
    Dem_ClientSelectDtcState[LucClientId].resultSelectDTC = E_NOT_OK;
    Dem_DTCFilterState[LucClientId].dfs_resultGetDtcFilter = E_NOT_OK;
    Dem_FilteredFFRecord[LucClientId].resultSetFFRecFilter = E_NOT_OK;
    Dem_ClientSelectFreezeFrameData[LucClientId].resultSelectFreezeFrameData =
        E_NOT_OK;
    Dem_ClientSelectExtendedDataRecord[LucClientId].
      resultSelectExtendedDataRecord = E_NOT_OK;
  }
  #endif

}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_DTCOriginIsValid
 **
 ** Service ID          : None
 **
 ** Description         : Checks whether DTC Origin is supported or not
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : DTCOrigin
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : boolean
 **
 ** Preconditions       : None
 **
 ** Remarks             : Global Variable(s)  :
 **
 **                       Function(s) invoked :
 *******************************************************************************/
/* @Trace: SRS_Diag_04002
 */
FUNC(boolean, DEM_CODE) Dem_EvMem_DTCOriginIsValid(
    const Dem_DTCOriginType DTCOrigin)
{
  boolean LblValid;

  switch(DTCOrigin)
  {
  /* Primary memory is  mandatory */
  /* @Trace: Dem_SUD_API_11288 */
  case DEM_DTC_ORIGIN_PRIMARY_MEMORY:

    /* @Trace: Dem_SUD_API_11292 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11293 */
  case DEM_DTC_ORIGIN_MIRROR_MEMORY:
  /* @Trace: Dem_SUD_API_11291 */
  #endif

    /* @Trace: Dem_SUD_API_11294 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11298 */
  case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
    /* @Trace: Dem_SUD_API_11290 */
  #endif

    /* @Trace: Dem_SUD_API_11295 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    DEM_DTCORGIN_USER_DEFINED_CASE
    /* @Trace: Dem_SUD_API_11289 */
  #endif

    /* @Trace: Dem_SUD_API_11296 */
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_11297 */
  case DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY:
    /* @Trace: Dem_SUD_API_11299 */
  #endif

    LblValid = DEM_TRUE;
    break;

  default:
    LblValid = DEM_FALSE;
    break;
  }

  return LblValid;
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_Lock
 **
 ** Service ID          : None
 **
 ** Description         : Get lock status of the event memory
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : boolean
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_Lock(void)
{
  boolean LblLock = DEM_FALSE;
  /* @Trace: Dem_SUD_API_11300 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11303 */
  for (uint8 LucClientId = DEM_ZERO;
             LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientId++)
  {
    if (DEM_CLEARDTC_STATE_READY != Dem_ClearDtcState[LucClientId].cds_State)
    {
      /* @Trace: Dem_SUD_API_11302 */
      LblLock = DEM_TRUE;
      break;
    }
    else
    {
      /* @Trace: Dem_SUD_API_11301 */
      LblLock = DEM_FALSE;
    }
  }
  #endif
  
  return LblLock;
}

/******************************************************************************
* Function Name        : Dem_EvMem_RegisterPermanentDTC
*
* Service ID           : None
*
* Description          : Register Permanent DTC of event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant(Not same event Id)
*
* Input Parameters     : EventId
*
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              :
*
*****************************************************************************/
/* @Trace: SRS_Diag_04001
 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
FUNC(boolean, DEM_CODE) Dem_EvMem_RegisterPermanentDTC(
  Dem_EventIdType EventId)
{
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
  P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_VAR) LddCbDTC;
  boolean LblDirty = DEM_FALSE;
  boolean LblAddEvent = DEM_TRUE;

  /* @Trace: SWS_Dem_00300
   * The Dem shall be able to handle Permanent DTCs according to
   * regulations (refer to [20]) within the specific event memory
   * type "permanent" (refer to chapter 7.3.4).*/

  /* @Trace: Dem_SUD_API_11304 */
  if ((EventId < DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_11310 */
    if (DEM_MAX_NUMBER_OF_DTC > LddEvent->e_PointToDTC)
    {
      LddCbDTC = &Dem_GaaCombinedDtc[LddEvent->e_PointToDTC];
      /* @Trace: Dem_SUD_API_11311 */
      if (DEM_DTC_KIND_EMISSION_REL_DTCS == LddCbDTC->ddDtcKind)
      {
        Dem_NumOfEventMemoryEntryType LddStartIdx =
            Dem_EvMem_GetStartIndexEventMemorySet(
                EventId, DEM_DTC_ORIGIN_PERMANENT_MEMORY);
        uint16 LusStopIdx =
            Dem_EvMem_GetStopIndexEventMemorySet(
                EventId, DEM_DTC_ORIGIN_PERMANENT_MEMORY);
        Dem_NumOfEventMemoryEntryType LddNumOfMemEntries =
            Dem_EvMem_GetNumOfStoredEvtMemEntries(
                EventId, DEM_DTC_ORIGIN_PERMANENT_MEMORY);

        Dem_NumOfEventMemoryEntryType LddMaxNumEnvEntry = DEM_ZERO;
        /* @Trace: Dem_SUD_API_11312 */
        if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
        {
          /* @Trace: Dem_SUD_API_11313 */
          LddMaxNumEnvEntry =
              Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
                usDemMaxNumberEventEntryPermanent;
        }

        if (LddMaxNumEnvEntry <= LddNumOfMemEntries)
        {
          /* Displacement */
          /* @Trace: Dem_SUD_API_10819 */
          LblAddEvent = DEM_FALSE;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11314 */
          for (LddMemLoc = LddStartIdx; LddMemLoc < LusStopIdx; LddMemLoc++)
          {
            /* already stored */
            /* @Trace: Dem_SUD_API_11315 */
            if (EventId == Dem_PermanentEventMemory[LddMemLoc].EventIdRef)
            {
              /* @Trace: Dem_SUD_API_11316 */
              LblAddEvent = DEM_FALSE;
              break;
            }
          }
        }

        /* @Trace: Dem_SUD_API_11317 */
        if (LblAddEvent == DEM_TRUE)
        {
          /* @Trace: Dem_SUD_API_11305 */
          for (LddMemLoc = LddStartIdx; LddMemLoc < LusStopIdx; LddMemLoc++)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            if (DEM_NO_EVENT == Dem_PermanentEventMemory[LddMemLoc].EventIdRef)
            {
              /* @Trace: SWS_Dem_00590
               * Events that have been confirmed and activate the MIL (refer
               * to OBDrelevant DTCs, chapter 7.4.1), shall be stored robustly
               * against ClearDTC or powerfail (for details confer [20]).*/
              /* @Trace: Dem_SUD_API_11307 */
              Dem_PermanentEventMemory[LddMemLoc].EventIdRef = EventId;
              /* Set EventId */
              Dem_PermanentEventMemory[LddMemLoc].PfcQualified = DEM_FALSE;

              Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
                  EventId, DEM_DTC_ORIGIN_PERMANENT_MEMORY, DEM_ONE);
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              /* @Trace: SWS_Dem_01076
               * New permanent faults of the current driving cycle shall be
               * reported to the Dcm service $0A request latest after the next
               * OBD driving cycle starts.*/

              /* @Trace: SWS_Dem_01077
               * New permanent faults shall be stored in non-volatile memory
               * (Next Driving Cycle after WriteAll or after positive Callback
               * from NvM) latest at ECU shutdown.*/
              /*Trigger write to NvM*/
              LblDirty = DEM_TRUE;
              break;
            }
            else
            {
              /* @Trace: Dem_SUD_API_11306 */
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }
          }
        }
      }
    }

    /* @Trace: Dem_SUD_API_11309 */
    if (LblDirty == DEM_TRUE)
    {
      /* @Trace: Dem_SUD_API_11308 */
      Dem_EvMem_SetEvMemNvBlockStatus(
          DEM_DTC_ORIGIN_PERMANENT_MEMORY,
          LddMemLoc,
          DEM_EVMEM_STATUS_DIRTY_NVM);
    }
  }

  return LblDirty;
}

#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearPermanentDTC
 **
 ** Service ID          : None
 **
 ** Description         : Clear Permanent DTCs
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : void
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentDTC(
  Dem_EventIdType EventId,
  boolean pfc)
{
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;

  /* @Trace: Dem_SUD_API_11318 */
  if (( EventId < DEM_NUMBER_OF_EVENTS) &&(EventId != DEM_NO_EVENT))
  {
    Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(
            EventId,
            DEM_DTC_ORIGIN_PERMANENT_MEMORY);
    uint16 LusStopIdx = DEM_ZERO;
    Dem_NumOfEventMemoryEntryType LddNumOfMemEntries =
        Dem_EvMem_GetNumOfStoredEvtMemEntries(
            EventId,
            DEM_DTC_ORIGIN_PERMANENT_MEMORY);

    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];


    /* @Trace: Dem_SUD_API_11319 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_11320 */
     LusStopIdx = LddStartIdx
          + Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
              usDemMaxNumberEventEntryPermanent;
    }
    /* @Trace: Dem_SUD_API_11321 */
    if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > LusStopIdx)
    {
      /* @Trace: Dem_SUD_API_11322 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LusStopIdx; LddMemLoc++)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        if ((EventId == Dem_PermanentEventMemory[LddMemLoc].EventIdRef)
            && ((Dem_PermanentEventMemory[LddMemLoc].PfcQualified == DEM_TRUE)
            || (pfc == DEM_TRUE)))
        {
          Dem_PermanentEventMemory[LddMemLoc].EventIdRef = DEM_NO_EVENT;
          Dem_PermanentEventMemory[LddMemLoc].PfcQualified = DEM_FALSE;
          /* @Trace: Dem_SUD_API_11324 */
          if (LddNumOfMemEntries > DEM_ZERO)
          {
            /* @Trace: Dem_SUD_API_11325 */
            Dem_EvMem_DecreaseNumOfStoredEvtMemEntries(EventId,
            DEM_DTC_ORIGIN_PERMANENT_MEMORY, DEM_ONE);
          }
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          Dem_EvMem_SetEvMemNvBlockStatus(
              DEM_DTC_ORIGIN_PERMANENT_MEMORY, LddMemLoc,
          DEM_EVMEM_STATUS_DIRTY_NVM);
          break;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11323 */
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    }
  }
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearPermanentDTCAllCbEvents
 **
 ** Service ID          : None
 **
 ** Description         : Clear All Permanent DTCs related with Combined DTC
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : void
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentDTCAllCbEvents(
    Dem_EventIdType EventId, boolean pfc)
{
  if (EventId != DEM_NO_EVENT)
  {
    Dem_EventIdType LddEventId;
    Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);        
    Dem_NumOfEventIdType LddStartPos = Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
    const Dem_NumOfEventIdType LddEndPos =Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
    
    for (; LddStartPos < LddEndPos; LddStartPos++)
    {
      LddEventId = Dem_ListOfCombinedEvents[LddStartPos];
      Dem_EvMem_ClearPermanentDTC(LddEventId, pfc);          
    }
  }
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_FindPerMemLoc
 **
 ** Service ID          : None
 **
 ** Description         : Find Permanent memory location 
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : EventId
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : Dem_NumOfEventMemoryEntryType
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_FindPerMemLoc(
  Dem_EventIdType EventId)
{
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
  boolean LblFindEvent = DEM_FALSE;

  /* @Trace: Dem_SUD_API_11326 */
  if ((EventId < DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId,
        DEM_DTC_ORIGIN_PERMANENT_MEMORY);

    uint16 LusStopIdx = DEM_ZERO;
    /* @Trace: Dem_SUD_API_11327 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_11328 */
      LusStopIdx = LddStartIdx
          + Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
              usDemMaxNumberEventEntryPermanent;
    }
    /* @Trace: Dem_SUD_API_11329 */
    if (DEM_MAX_NUMBER_EVENT_ENTRY_PER >= LusStopIdx)
    {
      /* @Trace: Dem_SUD_API_11330 */
      for (LddMemLoc = LddStartIdx; LddMemLoc < LusStopIdx; LddMemLoc++)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        if (EventId == Dem_PermanentEventMemory[LddMemLoc].EventIdRef)
        {
          /* @Trace: Dem_SUD_API_11332 */
          LblFindEvent = DEM_TRUE;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          break;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11331 */
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    }

    /* @Trace: Dem_SUD_API_11334 */
    if (LblFindEvent == DEM_FALSE)
    {
      /* @Trace: Dem_SUD_API_11333 */
     LddMemLoc = DEM_NO_EVMEM_ENTRY;
    }
  }

  return LddMemLoc;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_FindMirMemLoc
 **
 ** Service ID          : None
 **
 ** Description         : Find mirror memory location
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : EventId
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : Dem_NumOfEventMemoryEntryType
 **
 ** Preconditions       : None
 **
 ** Remarks             :
 *******************************************************************************/
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_FindMirMemLoc(
  Dem_EventIdType EventId)
{
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
  boolean LblFindEvent = DEM_FALSE;

  /* @Trace: Dem_SUD_API_11335 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId,
            DEM_DTC_ORIGIN_MIRROR_MEMORY);

    Dem_NumOfEventMemoryEntryType LddStopIdx =
        Dem_EvMem_GetStopIndexEventMemorySet(
            EventId,
            DEM_DTC_ORIGIN_MIRROR_MEMORY);

    /* @Trace: Dem_SUD_API_11337 */
    for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      if (EventId == Dem_MirrorEventMemory[LddMemLoc].EventIdRef)
      {
        /* @Trace: Dem_SUD_API_11340 */
        LblFindEvent = DEM_TRUE;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        break;
      }
      else
      {
        /* @Trace: Dem_SUD_API_11336 */
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
    }

    /* @Trace: Dem_SUD_API_11338 */
    if (LblFindEvent == DEM_FALSE)
    {
      /* @Trace: Dem_SUD_API_11339 */
     LddMemLoc = DEM_NO_EVMEM_ENTRY;
    }
  }

  return LddMemLoc;

}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearPermanentMemEntry
 **
 ** Service ID          : None
 **
 ** Description         : Clear Permanent Memory Entry
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : memLoc, EventId
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : void
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentMemEntry(
    Dem_NumOfEventMemoryEntryType memLoc, Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_11341 */
  if ((EventId < DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    /* @Trace: Dem_SUD_API_10820 */
    Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId,
        DEM_DTC_ORIGIN_PERMANENT_MEMORY);

    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

    Dem_NumOfEventMemoryEntryType LddNumOfMemEntries =
        Dem_EvMem_GetNumOfStoredEvtMemEntries(EventId,
        DEM_DTC_ORIGIN_PERMANENT_MEMORY);

    uint16 LusStopIdx = DEM_ZERO;
    /* @Trace: Dem_SUD_API_11342 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_10821 */
      LusStopIdx = LddStartIdx +
          Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
            usDemMaxNumberEventEntryPermanent;
    }
    /* @Trace: Dem_SUD_API_11343 */
    if ((memLoc < LusStopIdx) && (memLoc >= LddStartIdx))
    {
      /* @Trace: Dem_SUD_API_10822 */
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();

      Dem_PermanentEventMemory[memLoc].EventIdRef = DEM_NO_EVENT;
      Dem_PermanentEventMemory[memLoc].PfcQualified = DEM_FALSE;
      /* @Trace: Dem_SUD_API_10823 */
      if (LddNumOfMemEntries > DEM_ZERO)
      {
        /* @Trace: Dem_SUD_API_11344 */
        Dem_EvMem_DecreaseNumOfStoredEvtMemEntries(EventId,
        DEM_DTC_ORIGIN_PERMANENT_MEMORY, DEM_ONE);
      }
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      Dem_EvMem_SetEvMemNvBlockStatus(DEM_DTC_ORIGIN_PERMANENT_MEMORY, memLoc,
      DEM_EVMEM_STATUS_DIRTY_NVM);
    }
  }
}
#endif


#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

