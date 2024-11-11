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
**  SRC-MODULE: Dem_EventMemoryCfg.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provides the interface of varialble data that are configurable**
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
** 2.0.1.0   04-Jan-2024   GuillaumeMPD  Jira #CP44-3617 #CP44-3618           **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */
#include "Dem_Config.h"
#include "Dem_Dtc.h"
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
#include "Dem_EventRelatedData.h"
#include "Dem_Indicator.h"
#include "Dem_Version.h"
#if (DEM_J1939_SUPPORT == STD_ON)
#include "Dem_J1939Dcm.h"
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#include "Dem_Obd.h"
#endif


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
 **                    Function Definitions                                   **
 ******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
static FUNC(boolean, DEM_CODE) Dem_EvMem_SetFirstLastConfirmedDTC(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin, 
  Dem_DTCType DTC);
#endif

#if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)  
static FUNC(void, DEM_CODE) Dem_EvMem_SetUdsStatusByteToEvMemEntry(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_NumOfEventMemoryEntryType memLoc);
#endif  
  

/******************************************************************************
* Function Name        : Dem_EvMem_SetEventId
*
* Service ID           : None
*
* Description          : Store event id
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EvEntry, EventId
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
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_SetEventId(
  Dem_EventMemoryEntryPtrType EvEntry,
  Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_00410 */
  EvEntry->EventIdRef = EventId;
}

/******************************************************************************
* Function Name        : Dem_EvMem_ClearEventMemoryEntry
*
* Service ID           : None
*
* Description          : Clear event memory entries
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EmEntry
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
*
*****************************************************************************/
/* @Trace: SRS_Diag_04195
 */
FUNC(void, DEM_CODE) Dem_EvMem_ClearEventMemoryEntry(
  Dem_EventMemoryEntryPtrType EmEntry )
{
   /* polyspace<RTE:UNR:Not a defect:No action planned>
    * entry always is not null, but this is added to prevent the misra rule
    * violation 21.1 */
  if (NULL_PTR == EmEntry)
  {
    /* @Trace: Dem_SUD_API_00411 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_00418 */
    uint32 LulIndex;
    /* @Trace: Dem_SUD_API_00417 */
    #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00420 */
    for (LulIndex = 0; LulIndex < DEM_SIZE_OF_EVENT_DATA; LulIndex++)
    {
      /* @Trace: Dem_SUD_API_00419 */
      EmEntry->data[LulIndex] = DEM_SET_BYTE;
    }
    /* @Trace: Dem_SUD_API_00421 */
    #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
    /* Clear the number of FF captured */
    /* @Trace: Dem_SUD_API_00422 */
    EmEntry->IndexOfFFRecords = DEM_ZERO;
    #endif
    #endif
    

    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    /* Clear the event from memory */
    EmEntry->EventIdRef = DEM_NO_EVENT;  
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    /* @Trace: Dem_SUD_API_00423 */
    #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
    /* @Trace: Dem_SUD_API_00424 */
    for (LulIndex = 0; LulIndex < DEM_MAX_NUM_EVENTS_PER_DTC; LulIndex++)
    {
      /* @Trace: Dem_SUD_API_00412 */
      EmEntry->EventStatuByte[LulIndex] = 0x0;
    }   
    #endif
    /* @Trace: Dem_SUD_API_00413 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_00414 */
    EmEntry->TimeStamp = 0;
    #endif
    
    /* Clear the Occurrence counter */
    /*entry->EventStatusMask = DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC; */

    /* @Trace: SWS_Dem_00161
     * The Dem module shall handle the reoccurrence of unlearned events like new
     * events, since they were previously deleted from the event memory by aging.
     */
    EmEntry->EventOccurrenceCounter = DEM_ZERO;
    /* @Trace: Dem_SUD_API_00415 */
    #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
    /* @Trace: Dem_SUD_API_00416 */
    EmEntry->FailureCycleCounter = DEM_ZERO;
    #endif
    
    EmEntry->AgingCycleCounter = DEM_ZERO;
  }  
}

/******************************************************************************
* Function Name        : Dem_EvMem_GetEmEntryByMemPosition
*
* Service ID           : None
*
* Description          : Get event memory entry by memory position
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : DTCOrigin, MemLocation
*
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : Dem_EventMemoryEntryPtrType
*
* Preconditions        : None
*
* Remarks              :
*
*****************************************************************************/
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Dem_EventMemoryEntryPtrType, DEM_CODE)
Dem_EvMem_GetEmEntryByMemPosition(
  const Dem_DTCOriginType DTCOrigin, 
  const Dem_NumOfEventMemoryEntryType MemLocation)
{  
  Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;

  switch (DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00433 */
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
       /* @Trace: Dem_SUD_API_00432 */
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_PRI)
      {
        /* @Trace: Dem_SUD_API_00425 */
        LddMemEntry = &Dem_PrimaryEventMemory[MemLocation];
      }
      break;
     /* @Trace: Dem_SUD_API_00434 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    DEM_DTCORGIN_USER_DEFINED_CASE
       /* @Trace: Dem_SUD_API_00436 */
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_UD)
      {
        /* @Trace: Dem_SUD_API_00435 */
        LddMemEntry = &Dem_UserDefinedEventMemory[MemLocation];
      }
      break;
    #endif
    /* @Trace: Dem_SUD_API_00437 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_00438 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00439 */
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
       /* @Trace: Dem_SUD_API_00426 */
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_PER)
      {
        /* @Trace: Dem_SUD_API_00427 */
        LddMemEntry = &Dem_PermanentEventMemory[MemLocation];
      }
      break;
    #endif
    #endif

    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00429 */
    case DEM_DTC_ORIGIN_MIRROR_MEMORY:
      /* @Trace: Dem_SUD_API_00430 */
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_MIR)
      {
        /* @Trace: Dem_SUD_API_00431 */
        LddMemEntry = &Dem_MirrorEventMemory[MemLocation];
      }
      break;
    #endif

    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * Default switch clause is unreachable. switch-expression. */
    default:
      /* @Trace: Dem_SUD_API_00428 */
      /*  Do Nothing  */
      break;
  }  

  return LddMemEntry;
}
/******************************************************************************
* Function Name        : Dem_EvMem_GetEventIdByEvMemEntry
*
* Service ID           : None
*
* Description          : Get event id by event memory entry location
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : DTCOrigin, MemLocation
*
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : Dem_EventIdType
*
* Preconditions        : None
*
* Remarks              :
*
*****************************************************************************/
FUNC(Dem_EventIdType, DEM_CODE) 
Dem_EvMem_GetEventIdByEvMemEntry(  
  const Dem_DTCOriginType DTCOrigin, 
  const Dem_NumOfEventMemoryEntryType MemLocation)
{
  Dem_EventIdType LddEventId;

  switch (DTCOrigin) {
    /* @Trace: Dem_SUD_API_00444 */
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_PRI)
      {
        /* @Trace: Dem_SUD_API_00440 */
        LddEventId = Dem_PrimaryEventMemory[MemLocation].EventIdRef;
      }
      else
      {
        /* @Trace: Dem_SUD_API_00174 */
        LddEventId = DEM_NO_EVENT;
      }
      break;
    /* @Trace: Dem_SUD_API_00445 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00446 */
    DEM_DTCORGIN_USER_DEFINED_CASE
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_UD)
      {
        /* @Trace: Dem_SUD_API_00447 */
        LddEventId = Dem_UserDefinedEventMemory[MemLocation].EventIdRef;
      }
      else
      {
        /* @Trace: Dem_SUD_API_00175 */
        LddEventId = DEM_NO_EVENT;
      }
      break;
    #endif
    /* @Trace: Dem_SUD_API_00443 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_00450 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00449 */
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_PER)
      {
        /* @Trace: Dem_SUD_API_00448 */
        LddEventId = Dem_PermanentEventMemory[MemLocation].EventIdRef;
      }
      else
      {
        /* @Trace: Dem_SUD_API_00176 */
        LddEventId = DEM_NO_EVENT;
      }
      break;
    #endif
    #endif
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00441 */
    case DEM_DTC_ORIGIN_MIRROR_MEMORY:
      if (MemLocation < DEM_MAX_NUMBER_EVENT_ENTRY_MIR)
      {
        /* @Trace: Dem_SUD_API_00451 */
        LddEventId = Dem_MirrorEventMemory[MemLocation].EventIdRef;
      }
      else
      {
        /* @Trace: Dem_SUD_API_00177 */
        LddEventId = DEM_NO_EVENT;
      }
      break;
    #endif
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * Default switch clause is unreachable. switch-expression. */
    default:
    /* @Trace: Dem_SUD_API_00442 */
    LddEventId = DEM_NO_EVENT;
      break;
  }  

  return LddEventId;
}

#if (DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)

#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
/*******************************************************************************
** Function Name        : Dem_EvMem_GetEDBuffer                           
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Get the buffer for extended data. 
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : EvData, MemEntry, BufSize
**                                                                            
** InOut parameter      : entry
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : uint8*
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              : Global Variable(s)  :                               
**                        None
**                                                                            
**                        Function(s) invoked :                               
**                        None                                                
*******************************************************************************/
FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetEDBuffer(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize)
{
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
  /* @Trace: Dem_SUD_API_00452 */
  if (NULL_PTR != MemEntry)
  {
    uint32 LucOffset = DEM_ZERO;
    /* if Event has a FFClass , src shall be shifted */
    #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00455 */
    if (EvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS)
    {
      /* @Trace: Dem_SUD_API_00453 */
      /* when FF exists, max freeze frame record is 2
       * Data format = [-FF0-|-FF1-| ED ] */
      LucOffset =
          (uint32)EvData->MaxNumOfFreezeFrameRecords *
          (uint32)Dem_FreezeFrameClass[EvData->FFClassPos].size;
    }
    #else
    /* @Trace: Dem_SUD_API_00454 */
    (void) EvData;
    #endif
    /* RecordIndex starts from zero */
    LpDst = &MemEntry->data[LucOffset];
    *BufSize = DEM_SIZE_OF_EVENT_DATA - LucOffset;
  }
  return LpDst;
}
#endif


#if (DEM_J1939_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : Dem_EvMem_GetJ1939FFBuffer                           
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Get the buffer for J1939 FF data. 
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : EvData, MemEntry, BufSize, J1939FFType
**                                                                            
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : uint8*
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              : Global Variable(s)  :                               
**                        None
**                                                                            
**                        Function(s) invoked :                               
**                        None                                                
*******************************************************************************/
FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetJ1939FFBuffer (
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize, 
  Dem_J1939DcmSetFreezeFrameFilterType J1939FFType)
{
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
  /* @Trace: Dem_SUD_API_00456 */
  if (NULL_PTR != MemEntry)
  {
    uint32 LulOffset = DEM_ZERO;
    DEM_UNUSED(J1939FFType);
    /* if Event has a FFClass , src shall be shifted */
    /* @Trace: Dem_SUD_API_00462 */
    #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00463 */
    if (EvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS)
    {
      /* @Trace: Dem_SUD_API_00459 */
      /* when FF exists, max freeze frame record is 2
       * Data format = [-FF0-|-FF1-| ED | J1939FF | J1939EXFF ] */
      LulOffset =
          (uint32)EvData->MaxNumOfFreezeFrameRecords *
          (uint32)Dem_FreezeFrameClass[EvData->FFClassPos].size;
    }
    #endif
    /* @Trace: Dem_SUD_API_00464 */
    #if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00465 */
    if (EvData->EDClassPos < DEM_NUM_OF_EXTENDEDDATACLASS)
    {
      /* @Trace: Dem_SUD_API_00460 */
      /* when FF exists, max freeze frame record is 2
       * Data format = [-FF0-|-FF1-| ED | J1939FF | J1939EXFF ] */
      LulOffset += (uint16)Dem_ExtendedDataClass[EvData->EDClassPos].size;
    }
    #endif
     /* @Trace: Dem_SUD_API_00466 */
    #if (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00467 */
    if ((J1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME) &&
        (EvData->J1939FFClassPos < Dem_Num_Of_J1939FreezeFrameClass))
    {
      /* @Trace: Dem_SUD_API_00461 */
      LulOffset +=
          (uint32)Dem_J1939FreezeFrameClass[EvData->J1939FFClassPos].size;
    }
    #endif

    /* RecordIndex starts from zero */
    /* @Trace: Dem_SUD_API_00458 */
    if (DEM_SIZE_OF_EVENT_DATA > LulOffset)
    {
      /* @Trace: Dem_SUD_API_00457 */
      LpDst = &MemEntry->data[LulOffset];
      *BufSize = DEM_SIZE_OF_EVENT_DATA - LulOffset;
    }
  }
  return LpDst;
}
#endif

/*******************************************************************************
** Function Name        : Dem_EvMem_GetFFBufferForWriting                           
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Get the next index of the freeze frame records. 
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : EvData, MemEntry, BufSize, EventStatus
**                                                                            
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : uint8*
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              : Global Variable(s)  :                               
**                        None
**                                                                            
**                        Function(s) invoked :                               
**                        None                                                
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04127
 */
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetFFBufferForWriting(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize,
  Dem_EventStatusType EventStatus)
{
  const Dem_RecordNumberType  LddMaxLimit = EvData->MaxNumOfFreezeFrameRecords;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
  uint8 LucResult = E_NOT_OK;
  /* Tip, the range of Record Number is 1~254(0xFE). Record Number 0 is value
   * for OBD Freeze Frame */
  /* @Trace: SWS_Dem_00582
   * If DemTypeOfFreezeFrameRecordNumeration is set to DEM_FF_RECNUM_CONFIGURED
   * (refer to DemPrimaryMemory or DemUserDefinedMemory), the Dem shall store
   * per event memory entry all configured freeze frame records for this DTC.
   */
  /* @Trace: SWS_Dem_00797
   * If the FreezeFrame uses dedicated, configured record numbers (refer to
   * DemFreezeFrameRecNumClassRef) and an event memory entry exists, the Dem
   * module shall capture the FreezeFrame on the configured trigger (refer to
   * DemFreezeFrameRecordTrigger) and store it to the event memory entry.
   */
  /* @Trace: Dem_SUD_API_00468 */
  if (NULL_PTR != MemEntry)
  {
    /* @Trace: Dem_SUD_API_00477 */
    if (DEM_NO_EVMEM_IDX !=
          Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
            Dem_Event[EvData->EventIdRef - DEM_ONE].aaEventDestination)
      {
        /* @Trace: Dem_SUD_API_00482 */
        #if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        if (DEM_FF_RECNUM_CALCULATED ==
              Dem_GaaDemPrimaryMemory[Dem_Event[EvData->EventIdRef - DEM_ONE].
                                      ucEventMemDstIdx].
                                        usDemTypeOfFreezeFrameRecordNumeration)
        {
          /* @Trace: Dem_SUD_API_00481 */
          LucResult = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_00478 */
          /* @Trace: Dem_SUD_API_00479 */
          if (E_OK == Dem_GetFFRecNumConfiguredConditionState(
              EvData, MemEntry, EventStatus))
          {
            /* @Trace: Dem_SUD_API_00480 */
            LucResult = E_OK;
          }
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        #endif
      }
      else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(
          Dem_Event[EvData->EventIdRef - DEM_ONE].aaEventDestination))
      {
        /* @Trace: Dem_SUD_API_00483 */
        /* @Trace: Dem_SUD_API_00471 */
        #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
        if (DEM_FF_RECNUM_CALCULATED ==
              Dem_GaaDemUserDefinedMemory
                [Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx].
                  usDemTypeOfFreezeFrameRecordNumeration)
        {
          /* @Trace: Dem_SUD_API_00473 */
          LucResult = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_00472 */
          /* @Trace: Dem_SUD_API_00469 */
          if (E_OK == Dem_GetFFRecNumConfiguredConditionState(
                EvData, MemEntry, EventStatus))
          {
            /* @Trace: Dem_SUD_API_00484 */
            LucResult = E_OK;
          }
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        #endif
      }
      else
      {
        /* @Trace: Dem_SUD_API_00470 */
        /* Nothing to do */
      }
    }
    /* @Trace: Dem_SUD_API_00474 */
    if (E_OK == LucResult)
    {
      Dem_NumOfRecordNumberType LddIFFRecord = MemEntry->IndexOfFFRecords;
      if ((DEM_ZERO != LddMaxLimit) && (LddIFFRecord <= LddMaxLimit))
      {
        if (LddIFFRecord < LddMaxLimit)
        {
          /* @Trace: Dem_SUD_API_00476 */
          /* Increment the index of ListOfRecordNumbers for Next Step */
          MemEntry->IndexOfFFRecords++;
        }
        else
        {
          /* @Trace: Dem_SUD_API_00475 */
          /* Record Number  is never DEM_ZERO, it is always more than one.
           */
          /* @Trace: SWS_Dem_00585
           * If more than one freeze frame record isconfigured for a specific
           * event, and this event is updated in the event memory, and all
           * available freeze frame record slots for this event are occupied,
           * the Dem module shall update the most recent record. */
          LddIFFRecord = LddMaxLimit - DEM_ONE;
        }
        /* RecordIndex starts from zero */
        LpDst = &MemEntry->data[LddIFFRecord * (*BufSize)];
        *BufSize  = DEM_SIZE_OF_EVENT_DATA - (LddIFFRecord * (*BufSize));
      }
      else
      {
        /* @Trace: Dem_SUD_API_00178 */
        /* MaxLimit never be 0, if MaxLimit is 0, FFClass of EvData will be
         * generated as NULL_PTR . */
        DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
      }
    }
  }

  return LpDst;
}

/*******************************************************************************
** Function Name        : Dem_EvMem_GetWWHFFBufferForWriting
**
** Service ID           : None
**
** Description          : Get the WWH free frame buffer size for writing
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : EvData, MemEntry
**
** InOut parameter      : None
**
** Output Parameters    : BufSize
**
** Return parameter     : uint8
**
** Preconditions        : None
**
** Remarks              : Global Variable(s)  :
**                        None
**
**                        Function(s) invoked :
**                        None
*******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetWWHFFBufferForWriting(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize)
{
  const Dem_RecordNumberType  LddMaxLimit = EvData->MaxNumOfFreezeFrameRecords;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
  uint8 LucResult = E_NOT_OK;
  /* Tip, the range of Record Number is 1~254(0xFE). Record Number 0 is value
   * for OBD Freeze Frame */
  /* @Trace: Dem_SUD_API_01248 */
  if (NULL_PTR != MemEntry)
  {
    /* @Trace: Dem_SUD_API_01258 */
    
    if (DEM_NO_EVMEM_IDX !=
          Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
            Dem_Event[EvData->EventIdRef - DEM_ONE].aaEventDestination)
      {
        /* @Trace: Dem_SUD_API_01260 */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        #if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
        if (DEM_FF_RECNUM_CALCULATED ==
              Dem_GaaDemPrimaryMemory
                [Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx].
                  usDemTypeOfFreezeFrameRecordNumeration)
        {
          /* @Trace: Dem_SUD_API_01262 */
          LucResult = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_01261 */
          /* @Trace: Dem_SUD_API_01264 */
          if (E_OK == Dem_GetWWHFFRecNumConfiguredConditionState(
              EvData, MemEntry))
          {
            /* @Trace: Dem_SUD_API_01263 */
            LucResult = E_OK;
          }
        }
        #endif
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
      }
      else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(
            Dem_Event[EvData->EventIdRef - DEM_ONE].aaEventDestination))
      {
        /* @Trace: Dem_SUD_API_01259 */
        /* @Trace: Dem_SUD_API_01250 */
        
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
        #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
        if (DEM_FF_RECNUM_CALCULATED ==
                Dem_GaaDemUserDefinedMemory
                  [Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx].
                    usDemTypeOfFreezeFrameRecordNumeration)
        {
          /* @Trace: Dem_SUD_API_01253 */
          LucResult = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_01251 */
          /* @Trace: Dem_SUD_API_01249 */
          if (E_OK == Dem_GetWWHFFRecNumConfiguredConditionState(
                EvData, MemEntry))
          {
            /* @Trace: Dem_SUD_API_01252 */
            LucResult = E_OK;
          }
        }
        #endif
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
      }
      else
      {
        /* @Trace: Dem_SUD_API_01265 */
        /* Nothing to do */
      }
    }
    /* @Trace: Dem_SUD_API_01254 */
    if (E_OK == LucResult)
    {
      Dem_NumOfRecordNumberType LddIFFRecord = MemEntry->IndexOfFFRecords;
      if ((DEM_ZERO != LddMaxLimit) && (LddIFFRecord <= LddMaxLimit))
      {
        if (LddIFFRecord < LddMaxLimit)
        {
          /* @Trace: Dem_SUD_API_01257 */
          /* Increment the index of ListOfRecordNumbers for Next Step */
          MemEntry->IndexOfFFRecords++;
        }
        else
        {
          /* @Trace: Dem_SUD_API_01256 */
          /* Record Number  is never DEM_ZERO, it is always more than one.
           */
          /* @Trace: SWS_Dem_00585
           * If more than one freeze frame record isconfigured for a specific
           * event, and this event is updated in the event memory, and all
           * available freeze frame record slots for this event are occupied,
           * the Dem module shall update the most recent record. */
          LddIFFRecord = LddMaxLimit - DEM_ONE;
        }
        /* RecordIndex starts from zero */
        /* @Trace: SWS_Dem_00582
         * If DemTypeOfFreezeFrameRecordNumeration is set to
         * DEM_FF_RECNUM_CONFIGURED (refer to DemPrimaryMemory or
         * DemUserDefinedMemory), the Dem shall store per event memory entry
         * all configured freeze frame records for this DTC.
         */
        LpDst = &MemEntry->data[LddIFFRecord * (*BufSize)];
        *BufSize  = DEM_SIZE_OF_EVENT_DATA - (LddIFFRecord * (*BufSize));
      }
      else
      {
        /* @Trace: Dem_SUD_API_01255 */
        /* MaxLimit never be 0, if MaxLimit is 0, FFClass of EvData will be
         * generated as NULL_PTR . */
        DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
      }
    }
  }

  return LpDst;
}

/******************************************************************************
 * Function Name        : Dem_GetFFRecNumConfiguredConditionState
 *
 * Service ID           : None
 *
 * Description          : Checks whether capture the FreezeFrame
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData, MemEntry, EventStatus
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
/* @Trace: SRS_Diag_04067 SRS_Diag_04073 SRS_Diag_04127
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetFFRecNumConfiguredConditionState(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPCType MemEntry,
    Dem_EventStatusType EventStatus)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* @Trace: SWS_Dem_00803
   * If the FreezeFrame uses dedicated, configured record numbers (refer to
   * DemFreezeFrameRecNumClass) and DemFreezeFrameRecordUpdate is set to
   * DEM_UPDATE_RECORD_NO, the FreezeFrame shall be stored only if the
   * FreezeFrame is currently not stored in this event memory entry.
   */

  /* @Trace: SWS_Dem_00804
   * If the FreezeFrame uses dedicated, configured record numbers (refer to
   * DemFreezeFrameRecNumClass) and DemFreezeFrameRecordUpdate is set to
   * DEM_UPDATE_RECORD_YES, the FreezeFrame shall be updated with each
   * trigger (refer to DemFreezeFrameRecordTrigger).
   */
  /* @Trace: Dem_SUD_API_00487 */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO) || \
      (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00492 */
  Dem_EventParameterPCType LddEvent = &Dem_Event[EvData->EventIdRef - DEM_ONE];
  #endif

  /* @Trace: SWS_Dem_00539
   * If the Dem module is requested to support combination on retrieval ,
   * the status bit transition of each event shall trigger the collection,
   * update and storage of the related data (freeze frame / extended data).
   */
  /* @Trace: SWS_Dem_00540
   * If the Dem module is requested to report data of a combined DTC
   * (combination on retrieval ), the Dem module shall return the event
   * related data of all assigned events.
   */
  #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
  /* @Trace: Dem_SUD_API_00493 */
  const Dem_UdsStatusByteType LddEventStatusByteOld  =
      Dem_GetDTCStatus(EvData->EventIdRef);
  #else
  /* @Trace: Dem_SUD_API_00494 */
  const Dem_UdsStatusByteType LddEventStatusByteOld  =
      Dem_AllEventStatusByte[EvData->EventIdRef];
  #endif
  uint8 LucStatusOfDTCRecordUpdate =
      Dem_GetStatusOfDTCRecordUpdate(EvData->EventIdRef);
  /* Check whether configure FFRecordClass */
  uint16 LusMaxFFR =
      EvData->FFRecordClassIndex + (uint16)EvData->MaxNumOfFreezeFrameRecords;
  /* @Trace: Dem_SUD_API_00495 */
  if (LusMaxFFR > DEM_ZERO)
  {
    uint16 LusFFRecClassIdx =
        EvData->FFRecordClassIndex + MemEntry->IndexOfFFRecords;
    /* @Trace: Dem_SUD_API_00497 */
    if (MemEntry->IndexOfFFRecords >= EvData->MaxNumOfFreezeFrameRecords)
    {
      /* @Trace: Dem_SUD_API_00496 */
      LusFFRecClassIdx -= DEM_ONE;
    }
    /* @Trace: Dem_SUD_API_00498 */
    if (((DEM_UPDATE_RECORD_YES ==
          Dem_FreezeFrameRecordClass[LusFFRecClassIdx].RecordUpdate) ||
        (DEM_ONE == MemEntry->EventOccurrenceCounter))
        #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
        && (E_OK == LucStatusOfDTCRecordUpdate)
        #endif
       )
      /* polyspace+1 MISRA2012:D4.4 [Justified:Low] "Comment for explain aspects of the code." */
      /* && ((DEM_UPDATE_RECORD_NO ==
       *    Dem_FreezeFrameRecordClass[EvData->FFRecordClassIndex +
       *                               MemEntry->IndexOfFFRecords].
       *                                RecordUpdate) */
    {
      /* @Trace: Dem_SUD_API_00499*/
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
      P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
          NULL_PTR;
      /* @Trace: Dem_SUD_API_00488 */
      if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > LddEvent->ucIndexOfDebounceAry)
      {
        /* @Trace: Dem_SUD_API_00489 */
        LddTimerStatus =
            Dem_GetDebounceTimerStatus(LddEvent->ucIndexOfDebounceAry);
      }
      #endif
      /* @Trace: SWS_Dem_00799
       * If the DemFreezeFrameRecordTrigger is set to
       * DEM_TRIGGER_ON_FDC_THRESHOLD, the FreezeFrame shall be captured (as
       * allowed by [SWS_Dem_00797]) each time the configured FDC threshold
       * (refer to DemCounterBasedFdcThresholdStorageValue or
       * DemTimeBasedFdcThresholdStorageValue) is reached (by a positive
       * increment), but at most once per operation cycle.
       */

      /* @Trace: SWS_Dem_00800
       * If the DemFreezeFrameRecordTrigger is set to
       * DEM_TRIGGER_ON_TEST_FAILED, the FreezeFrame shall be captured (as
       * allowed by [SWS_Dem_00797]) each time the UDS status bit 0 is set
       * (changing from 0 to 1).
       */

      /* @Trace: SWS_Dem_00801
       * If the DemFreezeFrameRecordTrigger is set to DEM_TRIGGER_ON_PENDING,
       * the FreezeFrame shall be captured (as allowed by [SWS_Dem_00797]) each
       * time the UDS status bit 2 is set (changing from  0 to 1).
       */

      /* @Trace: SWS_Dem_00802
       * If the DemFreezeFrameRecordTrigger is set to DEM_TRIGGER_ON_CONFIRMED,
       * the FreezeFrame shall be captured (as allowed by [SWS_Dem_00797]) each
       * time the Confirmed UDS status bit 3 is set (changing from 0 to 1).
       */

      /* @Trace: SWS_Dem_01308
       * If the DemFreezeFrameRecordTrigger is set to
       * DEM_TRIGGER_ON_EVERY_TEST_FAILED, each time an event was reported as
       * FAILED or after optional debouncing a qualified FAILED is detected the
       * Dem shall capture the Freeze frame.
       */

      /* @Trace: SWS_Dem_01068
       * If the DemFreezeFrameRecordTrigger is set to
       * DEM_TRIGGER_ON_FDC_THRESHOLD and the event reports
       * DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (monitor-internal debounced
       * event), the FreezeFrame shall be captured (refer [SWS_Dem_00797]),
       * but at most once per operation cycle.
       */
      uint8 LucFFRecordTriger =
          Dem_FreezeFrameRecordClass[LusFFRecClassIdx].RecordTriger;
      boolean LblIsBit0GetTransit =
          Dem_EvIsUdsProcStateTriggered(
              EvData->EventIdRef, DEM_UDSPROCSTATE_TRANSITION_BIT_0);
      boolean LblIsBit2GetTransit =
          Dem_EvIsUdsProcStateTriggered(
              EvData->EventIdRef, DEM_UDSPROCSTATE_TRANSITION_BIT_2);
      boolean LblIsBit3GetTransit =
          Dem_EvIsUdsProcStateTriggered(
              EvData->EventIdRef, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
      /* @Trace: Dem_SUD_API_00491 */
      if ((
            ((DEM_TRIGGER_ON_TEST_FAILED == LucFFRecordTriger) &&
            ((DEM_TRUE == LblIsBit0GetTransit) &&
              ((uint8)(LddEventStatusByteOld &
               (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) == DEM_ZERO))) ||

            ((DEM_TRIGGER_ON_PENDING == LucFFRecordTriger) &&
            ((DEM_TRUE == LblIsBit2GetTransit) &&
            ((uint8)(LddEventStatusByteOld &
             (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) == DEM_ZERO))) ||

            ((DEM_TRIGGER_ON_CONFIRMED == LucFFRecordTriger) &&
            ((DEM_TRUE == LblIsBit3GetTransit) &&
            ((uint8)(LddEventStatusByteOld &
             (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) == DEM_ZERO))) ||

            ((DEM_TRIGGER_ON_EVERY_TEST_FAILED == LucFFRecordTriger) &&
             (DEM_EVENT_STATUS_FAILED == EventStatus))

            #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
            || ((((DEM_DEBOUNCE_COUNTER_BASED ==
                    DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA)) &&
                 (Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry] >=
                     Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry].
                        ssDemCounterBasedFdcThresholdStorageValue)) &&
                 (DEM_TRIGGER_ON_FDC_THRESHOLD == LucFFRecordTriger)) &&
                 (DEM_ONE == MemEntry->EventOccurrenceCounter))
            #endif
            /* @Trace: Dem_SUD_MACRO_031 */
            #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
            || (((NULL_PTR != LddTimerStatus) &&
               (((DEM_DEBOUNCE_TIME_BASED ==
                     DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA))
                  &&
                  (LddTimerStatus->tds_Counter <=
                      (Dem_GaaPreDebounceTimeBased
                          [LddEvent->ucIndexOfDebounceAry].
                            ulDemTimeBasedFdcThresholdStorageValue/
                           Dem_Task_Time))) &&
               (DEM_TRIGGER_ON_FDC_THRESHOLD == LucFFRecordTriger))) &&
               (DEM_ONE == MemEntry->EventOccurrenceCounter))
            #endif

            || ((DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED == EventStatus) &&
                (DEM_TRIGGER_ON_FDC_THRESHOLD == LucFFRecordTriger) &&
                (DEM_ONE == MemEntry->EventOccurrenceCounter))
         ))
      {
        /* @Trace: Dem_SUD_API_00490 */
        LddRetVal = E_OK;
      }
    }
  }
  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_GetWWHFFRecNumConfiguredConditionState
 *
 * Service ID           : None
 *
 * Description          : Checks whether capture the FreezeFrame
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData, MemEntry
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
/* @Trace: SRS_Diag_04067 SRS_Diag_04073 SRS_Diag_04141
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetWWHFFRecNumConfiguredConditionState(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPCType MemEntry)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* @Trace: SWS_Dem_00539
   * If the Dem module is requested to support combination on retrieval ,
   * the status bit transition of each event shall trigger the collection,
   * update and storage of the related data (freeze frame / extended data).
   */
  /* @Trace: SWS_Dem_00540
   * If the Dem module is requested to report data of a combined DTC
   * (combination on retrieval ), the Dem module shall return the event
   * related data of all assigned events.
   */

  #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
  /* @Trace: Dem_SUD_API_00500 */
  const Dem_UdsStatusByteType LddEventStatusByteOld  =
      Dem_GetDTCStatus(EvData->EventIdRef);
  #else
  /* @Trace: Dem_SUD_API_00501 */
  const Dem_UdsStatusByteType LddEventStatusByteOld  =
      Dem_AllEventStatusByte[EvData->EventIdRef];
  #endif
  /* Check whether configure FFRecordClass */
  uint16 LusMaxFFR =
      EvData->FFRecordClassIndex + (uint16)EvData->MaxNumOfFreezeFrameRecords;
  /* @Trace: Dem_SUD_API_00502 */
  if (LusMaxFFR > DEM_ZERO)
  {
    uint16 LusFFRecClassIdx =
        EvData->FFRecordClassIndex + MemEntry->IndexOfFFRecords;
    /* @Trace: Dem_SUD_API_00503 */
    if (MemEntry->IndexOfFFRecords >= EvData->MaxNumOfFreezeFrameRecords)
    {
      /* @Trace: Dem_SUD_API_00504 */
      LusFFRecClassIdx -= DEM_ONE;
    }

    CONSTP2CONST(Dem_FreezeFrameRecordClassType,AUTOMATIC,DEM_CONST)
    LddFFRecord = &Dem_FreezeFrameRecordClass[LusFFRecClassIdx];
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
    if (DEM_ZERO == LddFFRecord->FreezeFrameRecordNumber)
    {
      /* @Trace: SWS_Dem_01171
       * The update behavior if the Freeze Frame 0x00 is updated on transition
       * of UDS status bit 3 from 0 to 1, can be configured using
       * DemFreezeFrameRecordUpdate.
       */
      boolean LblIsBit3GetTransit =
          Dem_EvIsUdsProcStateTriggered(
              EvData->EventIdRef, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
      boolean LblIsBit2GetTransit =
          Dem_EvIsUdsProcStateTriggered(
              EvData->EventIdRef, DEM_UDSPROCSTATE_TRANSITION_BIT_2);
      /* @Trace: Dem_SUD_API_00507 */
      if ((((DEM_UPDATE_RECORD_YES == LddFFRecord->RecordUpdate) ||
           (DEM_ONE == MemEntry->EventOccurrenceCounter)) &&
           ((DEM_TRUE == LblIsBit3GetTransit) &&
           ((uint8)(LddEventStatusByteOld &
            (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) == DEM_ZERO))) ||
          /* @Trace: SWS_Dem_01170
           * The legislative Freeze Frame 0x00 shall be stored on transition of
           * UDS status bit 2 from 0 to 1 (via DemFreezeFrameRecordTrigger set
           * to DEM_TRIGGER_ON_PENDING).
           */
          ((DEM_TRIGGER_ON_PENDING == LddFFRecord->RecordTriger) &&
          ((DEM_TRUE == LblIsBit2GetTransit) &&
          ((uint8)(LddEventStatusByteOld &
           (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) == DEM_ZERO)))
         )
      {
        /* @Trace: Dem_SUD_API_00506 */
        LddRetVal = E_OK;
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_00505 */
      LddRetVal = E_OK;
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_EvMem_GetRecNumOfFF
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Gets the record number of a freeze frame
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : entry
**
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : Dem_RecordNumberType
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              : Global Variable(s)  :                               
**                        None
**                                                                            
**                        Function(s) invoked :                               
**                        None                                                
*******************************************************************************/
FUNC(Dem_RecordNumberType, DEM_CODE)
Dem_EvMem_GetRecNumOfFF(Dem_EventMemoryEntryCPCType entry)
{
  Dem_RecordNumberType LddRecNum;
  if (NULL_PTR != entry)
  {
    /* @Trace: Dem_SUD_API_00485 */
    LddRecNum = entry->IndexOfFFRecords;
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * Above If-condition always evaluates to true. Avoid the runtime error of
   * the polyspace */
  {
    /* @Trace: Dem_SUD_API_00486 */
    LddRecNum = (uint8)DEM_ZERO;
  }

  return LddRecNum;
}

#endif
#endif

/******************************************************************************
 * Function Name        : Dem_EvMem_SetFirstLastFailedDtc
 *
 * Service ID           : None
 *
 * Description          : Sets the order of an failed DTC. 
 *                        It used to UDS $17-[0B or 0D]
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId, DTCOrigin, DTC
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_EventStatusNvRamData
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
FUNC(boolean, DEM_CODE)
Dem_EvMem_SetFirstLastFailedDtc(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  Dem_DTCType DTC)
{
  boolean LblDirty = DEM_FALSE;

  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition evaluates to true or false according to configuration */
  /* @Trace: Dem_SUD_API_00508 */
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    const uint32 LulFirstIndex = DEM_FIRST_FAILED_DTC - DEM_ONE;
    const uint32 LulRecentIndex = DEM_MOST_RECENT_FAILED_DTC - DEM_ONE;
    
    SchM_Enter_Dem_REQUEST_OCCTIME_PROTECTION();
    /* Occurrence time DTC manipulation (First Failed DTC)*/
    /* @Trace: Dem_SUD_API_00510 */
    if (DEM_NO_DTC == Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
                                             .DTCOccurenceTime[LulFirstIndex])
    {
      /* @Trace: Dem_SUD_API_00509 */
      Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
                .DTCOccurenceTime[LulFirstIndex] = DTC;
      LblDirty = DEM_TRUE;
    }
    /* Most recent failed DTC */
    /* @Trace: Dem_SUD_API_00512 */
    if (DTC != Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
                 .DTCOccurenceTime[LulRecentIndex])
    {
      /* @Trace: Dem_SUD_API_00511 */
      Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
                 .DTCOccurenceTime[LulRecentIndex] = DTC;
      LblDirty = DEM_TRUE;
    }
    SchM_Exit_Dem_REQUEST_OCCTIME_PROTECTION();
  }
  return LblDirty;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_SetFirstLastConfirmedDTC
 *
 * Service ID           : None
 *
 * Description          : Sets the order of an comfirmed DTC. 
 *                        It used to UDS $17-[0C or 0E]
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId, DTC
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_EventStatusNvRamData
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
static FUNC(boolean, DEM_CODE) Dem_EvMem_SetFirstLastConfirmedDTC(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin, Dem_DTCType DTC)
{
  boolean LblDirty = DEM_FALSE;

  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition evaluates to true or false according to configuration */
  /* @Trace: Dem_SUD_API_00513 */
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00515 */
    const uint32 LulFirstIndex = DEM_FIRST_DET_CONFIRMED_DTC - DEM_ONE;
    const uint32 LulMostIndex  = DEM_MOST_REC_DET_CONFIRMED_DTC - DEM_ONE;

    SchM_Enter_Dem_REQUEST_OCCTIME_PROTECTION();
    /* Occurrence time DTC manipulation (first detected confirmed DTC ) */
    /* @Trace: Dem_SUD_API_00516 */
    if (DEM_NO_DTC == Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
        .DTCOccurenceTime[LulFirstIndex])
    {
      /* @Trace: Dem_SUD_API_00514 */
      Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
      .DTCOccurenceTime[LulFirstIndex] = DTC;
      LblDirty = DEM_TRUE;
    }
    /* Most recently detected confirmed DTC */
    /* @Trace: Dem_SUD_API_00517 */
    if (DTC != Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
        .DTCOccurenceTime[LulMostIndex])
    {
      /* @Trace: Dem_SUD_API_00518 */
      Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
      .DTCOccurenceTime[LulMostIndex] = DTC;
      LblDirty = DEM_TRUE;
    }
    SchM_Exit_Dem_REQUEST_OCCTIME_PROTECTION();
  }
  return LblDirty;
}
#endif
/******************************************************************************
 * Function Name        : Dem_EvMem_ClearDTCOccurrenceTime
 *
 * Service ID           : None
 *
 * Description          : Clears the order of the specific DTC. 
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId, DTC, AllDTCs
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
 *****************************************************************************/
FUNC(boolean, DEM_CODE)
Dem_EvMem_ClearDTCOccurrenceTime(
  uint8 ClientId,
  const Dem_DTCType DTC,
  boolean AllDTCs)
{
  uint32 LulIndex;
  boolean LblDirty = DEM_FALSE;
  
  SchM_Enter_Dem_REQUEST_OCCTIME_PROTECTION();

  if (DEM_TRUE == AllDTCs)
  {
    /* @Trace: Dem_SUD_API_00520 */
    /* @Trace: Dem_SUD_API_00521 */
    for (LulIndex = DEM_ZERO; LulIndex < DEM_MAX_DTC_REQEST_TYPE; LulIndex++)
    {  
      /* @Trace: Dem_SUD_API_00523 */
      if (DEM_NO_DTC != Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId]
            .DTCOccurenceTime[LulIndex])
      {
        /* @Trace: Dem_SUD_API_00522 */
        Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId]
            .DTCOccurenceTime[LulIndex] = DEM_NO_DTC;
        LblDirty = DEM_TRUE;
      }
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_00519 */
    /* @Trace: Dem_SUD_API_00524 */
    for (LulIndex = DEM_ZERO; LulIndex < DEM_MAX_DTC_REQEST_TYPE; LulIndex++)
    {
      /* @Trace: Dem_SUD_API_00526 */
      if (DTC == Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
          .DTCOccurenceTime[LulIndex])
      {
        /* @Trace: Dem_SUD_API_00525 */
        Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId] \
        .DTCOccurenceTime[LulIndex] = DEM_NO_DTC;
        LblDirty = DEM_TRUE;
      }
    }
  }
  SchM_Exit_Dem_REQUEST_OCCTIME_PROTECTION();

  return LblDirty;
}
#endif

/*******************************************************************************
** Function Name        : Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Get user defined index from DTCOrigin
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : DTCOrigin
**                                                                            
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : uint8
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              :    
*******************************************************************************/
/* polyspace +1 CODE-METRICS:CALLING [Not a defect:Low] "Not a defect" */
FUNC(uint8, DEM_CODE) Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(
  Dem_DTCOriginType DTCOrigin)
{
  uint8 LucRetVal = DEM_NO_IDX_U8;
  #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00531 */
  uint16 LusTmpOrigin = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00528 */
  for (uint8 LucIndex = DEM_ZERO;
             LucIndex < DEM_MAX_NUMBER_USER_DEFINED_MEMORY;
             LucIndex++)
  {
    LusTmpOrigin =
        ((uint16)Dem_GaaDemUserDefinedMemory[LucIndex].
            usDemUserDefinedMemoryIdentifier) | 0xFF00U;
    LusTmpOrigin = (uint16)(LusTmpOrigin & (uint16)0x01FFU);
    /* @Trace: Dem_SUD_API_00529 */
    if (DTCOrigin == LusTmpOrigin)
    {
      /* @Trace: Dem_SUD_API_00530 */
      LucRetVal = LucIndex;
      break;
    }
  }
  #else
  /* @Trace: Dem_SUD_API_00527 */
  DEM_UNUSED(DTCOrigin);
  #endif
  return LucRetVal;
}

/*******************************************************************************
** Function Name        : Dem_EvMem_SetEvMemOverflowFlag
**
** Service ID           : None
**
** Description          : Sets the overflow indication flag of event memory
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : EvtMemSetId, DTCOrigin,
**                        state (DEM_TRUE: memory is full, DEM_FALSE: not full)
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : boolean
**
** Preconditions        : None
**
** Remarks              :
*******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_SetEvMemOverflowFlag(
  uint8 EvtMemSetId,
  Dem_DTCOriginType DTCOrigin, 
  boolean state)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00534 */
  if (((boolean)DEM_TRUE == Dem_EvMem_DTCOriginIsValid(DTCOrigin)) &&
       (DEM_MAX_NUMBER_MEMORY_SET > EvtMemSetId))
  {
    /*It is not User Defined Memory*/
    if (!DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      boolean LblOldState = Dem_IsBit8Set(
          Dem_EventStatusNvRamData.EventMemoryOverflow[EvtMemSetId],
          (uint8)DTCOrigin);
      /* @Trace: Dem_SUD_API_00536 */
      if (LblOldState != state)
      {
        /* @Trace: Dem_SUD_API_00535 */
        Dem_EventStatusNvRamData.EventMemoryOverflow[EvtMemSetId] =
            (state == (boolean)DEM_TRUE) ?
          Dem_SetBit8(
              Dem_EventStatusNvRamData.EventMemoryOverflow[EvtMemSetId],
              (uint8)DTCOrigin) :
          Dem_ClearBit8(
              Dem_EventStatusNvRamData.EventMemoryOverflow[EvtMemSetId],
              (uint8)DTCOrigin);
        LblDirty = DEM_TRUE;
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_00532 */
      /* @Trace: Dem_SUD_API_00533 */
      #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
      /*It is User Defined Memory*/
      uint8 LucUserDefinedIdx =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
          /* @Trace: Dem_SUD_API_00537 */
      if (DEM_NO_IDX_U8 != LucUserDefinedIdx)
      {
        /* @Trace: Dem_SUD_API_00538 */
        Dem_EventStatusNvRamData.
          EventMemoRyOverflowUserDefined[LucUserDefinedIdx] = state;
        LblDirty = DEM_TRUE;
      }
      #endif
    }
  }
  
  return LblDirty;
}

/*******************************************************************************
** Function Name        : Dem_EvMem_GetEvMemOverflowFlag
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Gets the overflow indication flag of event memory 
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : EvtMemSetId, DTCOrigin
**                                                                            
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : boolean(DEM_TRUE: memory is full, DEM_FALSE: not full)
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              : 
*******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_GetEvMemOverflowFlag(
  uint8 EvtMemSetId,
  Dem_DTCOriginType DTCOrigin)
{
  boolean LblReVal = DEM_TRUE;
  /* @Trace: Dem_SUD_API_00539 */
  if ((boolean)DEM_TRUE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
  {
    /*It is not User Defined Memory*/
    if (!DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_00541 */
      LblReVal = Dem_IsBit8Set(
          Dem_EventStatusNvRamData.EventMemoryOverflow[EvtMemSetId],
          (uint8)DTCOrigin);
    }
    else
    {
      /* @Trace: Dem_SUD_API_00540 */
      /* @Trace: Dem_SUD_API_00542 */
      #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
      /*It is User Defined Memory*/
      /* @Trace: Dem_SUD_API_00543 */
      uint8 LucUserDefinedIdx =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
      /* @Trace: Dem_SUD_API_00544 */
      if (DEM_NO_IDX_U8 != LucUserDefinedIdx)
      {
        /* @Trace: Dem_SUD_API_00545 */
        LblReVal = Dem_EventStatusNvRamData.
            EventMemoRyOverflowUserDefined[LucUserDefinedIdx];
      }
      #endif
    }
  }
  /* @Trace: Dem_SUD_API_00179 */
  return LblReVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_CheckFirstEcuRun
 *
 * Service ID           : None
 *
 * Description          : Checks whether non-volatile datas are written
 *                        at least one  or not in the NvRam
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
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_CheckFirstEcuRun(void)
{
  boolean LblRetVal;

  if (
      (DEM_NVM_FOOTPRINT            == Dem_NonVolatileData.FootPrint) &&
      (DEM_EVMEM_VERSION_SIGNATURES == Dem_NonVolatileData.EvMemVer[DEM_ZERO]) &&
      (DEM_EVMEM_VERSION_MAJOR      == Dem_NonVolatileData.EvMemVer[DEM_ONE]) &&
      (DEM_EVMEM_VERSION_MINOR      == Dem_NonVolatileData.EvMemVer[DEM_TWO]) &&
      (DEM_EVMEM_VERSION_REVISION   == Dem_NonVolatileData.EvMemVer[DEM_THREE]))
  {
    /* @Trace: Dem_SUD_API_00546 */
    LblRetVal = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_00180 */
    LblRetVal = DEM_FALSE;  
  }
  return LblRetVal;
}


/******************************************************************************
 * Function Name        : Dem_EvMem_ResetEventStatusNvRamBlock
 *
 * Service ID           : None
 *
 * Description          : Clears the non-volatile data(event memory, etc)
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
 * Remarks              : Global Variable(s)  :
 *                        Dem_EventStatusNvRamData
 *
 *                        Function(s) invoked :
 *                        DEM_RST_UDSSTATUSBYTE()
 *****************************************************************************/
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_EvMem_ResetEventStatusNvRamBlock(void)
{
  Dem_EventIdType LddNVDataIndex;
  /* @Trace: Dem_SUD_API_00547 */
  for (LddNVDataIndex = DEM_ZERO;
       LddNVDataIndex < DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS);
       LddNVDataIndex++)
  {    
    #if (DEM_UDS_STATUS_TF_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00558 */
    Dem_EventStatusNvRamData.TF_BitArray[LddNVDataIndex] = DEM_ZERO;
    #endif   
   
    #if (DEM_UDS_STATUS_TFTOC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00569 */
    Dem_EventStatusNvRamData.TFTOC_BitArray[LddNVDataIndex] = DEM_ZERO;
    #endif
    
    #if (DEM_UDS_STATUS_PDTC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00576 */
    Dem_EventStatusNvRamData.PDTC_BitArray[LddNVDataIndex] = DEM_ZERO;
    #endif
    
    #if (DEM_UDS_STATUS_CDTC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00577 */
    Dem_EventStatusNvRamData.CDTC_BitArray[LddNVDataIndex] = 0xFFU;
    #endif
    
    #if (DEM_UDS_STATUS_TNCSLC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00578 */
    Dem_EventStatusNvRamData.TNCSLC_BitArray[LddNVDataIndex] = 0xFFU;
    #endif
    
    #if (DEM_UDS_STATUS_TFSLC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00579 */
    Dem_EventStatusNvRamData.TFSLC_BitArray[LddNVDataIndex] = DEM_ZERO;
    #endif  
    
    #if (DEM_UDS_STATUS_TNCTOC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00580 */
    Dem_EventStatusNvRamData.TNCTOC_BitArray[LddNVDataIndex] = 0xFFU;
    #endif
    
    #if (DEM_UDS_STATUS_WIR_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00581 */
    Dem_EventStatusNvRamData.WIR_BitArray[LddNVDataIndex] = DEM_ZERO;
    #endif
    /* @Trace: Dem_SUD_API_00548 */
  }
  /* @Trace: Dem_SUD_API_00549 */
  #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00551 */
  for (LddNVDataIndex = DEM_ZERO;
       LddNVDataIndex < DEM_BITARRAY_BITNSLOTS(
           DEM_ONE + DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS);
       LddNVDataIndex++)
  {    
    /* @Trace: Dem_SUD_API_00550 */
    Dem_EventStatusNvRamData.AttributeStatus[LddNVDataIndex] = DEM_ZERO;
  }
  #endif
  /* @Trace: Dem_SUD_API_00565 */
  #if (DEM_NUM_OF_FAILURE_COUNTER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00564 */
  for (LddNVDataIndex = DEM_ZERO;
       LddNVDataIndex < DEM_NUM_OF_FAILURE_COUNTER;
       LddNVDataIndex++)
  {  
    /* @Trace: Dem_SUD_API_00563 */
    Dem_EventStatusNvRamData.IndicatorFailureCycleCounter[LddNVDataIndex] =
        DEM_ZERO;
  }
  #endif
  /* @Trace: Dem_SUD_API_00575 */
  #if (DEM_NUM_OF_HEALING_COUNTER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00574 */
  for (LddNVDataIndex = DEM_ZERO;
       LddNVDataIndex < DEM_NUM_OF_HEALING_COUNTER;
       LddNVDataIndex++)
  { 
    /* @Trace: Dem_SUD_API_00573 */
    Dem_EventStatusNvRamData.IndicatorHealingCycleCounter[LddNVDataIndex] =
        DEM_ZERO;
  }
  #endif

  /* Clears the order of the DTCs */
  /* @Trace: Dem_SUD_API_00552 */
  #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
  /* @Trace: Dem_SUD_API_00553 */
  /* @Trace: Dem_SUD_API_00554 */
  for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DEM_CLIENT; LucIdx++)
  {
    /* @Trace: Dem_SUD_API_00555 */
    /* @Trace: Dem_SUD_API_00556 */
    for (LddNVDataIndex = DEM_ZERO;
         LddNVDataIndex < DEM_MAX_DTC_REQEST_TYPE;
         LddNVDataIndex++)
    {
      /* @Trace: Dem_SUD_API_00557 */
      Dem_EventStatusNvRamData.DTCOccurenceTimeData[LucIdx].
        DTCOccurenceTime[LddNVDataIndex] = DEM_NO_DTC;
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00559 */
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  Dem_EventStatusNvRamData.DtcClear        = DEM_ZERO;
  Dem_EventStatusNvRamData.NumOfWUCSinceLC = DEM_ZERO;
  Dem_EventStatusNvRamData.WWHOBDConMICont = DEM_ZERO;
  Dem_EventStatusNvRamData.WWHOBDB1Counter = DEM_ZERO;
  Dem_EventStatusNvRamData.ObdMemoryId     = DEM_NO_EVMEM_ENTRY;
  /* @Trace: Dem_SUD_API_00560 */
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  for (LddNVDataIndex = DEM_ZERO;
       LddNVDataIndex < DEM_NUMBER_OF_RATIO_INFO;
       LddNVDataIndex++)
  {
    /* @Trace: Dem_SUD_API_00562 */
    Dem_EventStatusNvRamData.IumprDenominator[LddNVDataIndex] = DEM_ZERO;
    Dem_EventStatusNvRamData.IumprNumerator[LddNVDataIndex] = DEM_ZERO;
  }
  /* @Trace: Dem_SUD_API_00561 */
  Dem_EventStatusNvRamData.IgnitionCylCnt = DEM_ZERO;
  Dem_EventStatusNvRamData.GeneralDenCnt = DEM_ZERO;
  #endif
  #endif
  /* @Trace: Dem_SUD_API_00566 */
  /* @Trace: Dem_SUD_API_00568 */
  #if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
  for (uint8 LucIdx = DEM_ZERO; LucIdx <DEM_MAX_NUMBER_MEMORY_SET; LucIdx++)
  {
    /* @Trace: Dem_SUD_API_00567 */
    Dem_EventStatusNvRamData.EventMemoryOverflow[LucIdx] = DEM_ZERO;
  }
  #endif
   /* @Trace: Dem_SUD_API_00570 */
  #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00572 */
  for (uint8 LucIdx = DEM_ZERO;
             LucIdx <DEM_MAX_NUMBER_USER_DEFINED_MEMORY;
             LucIdx++)
  {
    /* @Trace: Dem_SUD_API_00571 */
    Dem_EventStatusNvRamData.EventMemoRyOverflowUserDefined[LucIdx] = DEM_FALSE;
  }
  #endif
}


/******************************************************************************
 * Function Name        : Dem_EvMem_ResetManagementBlock
 *
 * Service ID           : None
 *
 * Description          : Clears the non-volatile data(event memory, etc)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : SetfootPrintAsDefault
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
FUNC(void, DEM_CODE) Dem_EvMem_ResetManagementBlock(
  boolean SetfootPrintAsDefault)
{
  uint8 LucOcIndex;
 
  /* Initialize the operation cycle state */
  /* @Trace: Dem_SUD_API_00584 */
  for (LucOcIndex = DEM_ZERO;
       LucOcIndex < Dem_Num_Operation_Cycles;
       LucOcIndex++)
  {
    /* @Trace: Dem_SUD_API_00582 */
    (void)Dem_EvMem_SetOpCycleState(
        (uint8)LucOcIndex, DEM_CYCLE_STATE_NOTSTART);

    (void)Dem_EvMem_SetOpCycleQualifiedState(
        (uint8)LucOcIndex, DEM_CYCLE_STATE_NOTSTART);

  } 

  if ((boolean)DEM_TRUE == SetfootPrintAsDefault)
  {
    /* @Trace: Dem_SUD_API_00586 */
    Dem_NonVolatileData.FootPrint = DEM_NVM_FOOTPRINT;
    Dem_NonVolatileData.EvMemVer[DEM_ZERO] = DEM_EVMEM_VERSION_SIGNATURES;
    Dem_NonVolatileData.EvMemVer[DEM_ONE] = DEM_EVMEM_VERSION_MAJOR;
    Dem_NonVolatileData.EvMemVer[DEM_TWO] = DEM_EVMEM_VERSION_MINOR;
    Dem_NonVolatileData.EvMemVer[DEM_THREE] = DEM_EVMEM_VERSION_REVISION;
  }
  else
  {
    /* @Trace: Dem_SUD_API_00585 */
    Dem_NonVolatileData.FootPrint = 0;  
    Dem_NonVolatileData.EvMemVer[DEM_ZERO] = DEM_ZERO;
    Dem_NonVolatileData.EvMemVer[DEM_ONE] = DEM_ZERO;
    Dem_NonVolatileData.EvMemVer[DEM_TWO] = DEM_ZERO;
    Dem_NonVolatileData.EvMemVer[DEM_THREE] = DEM_ZERO;
  }
  /* @Trace: Dem_SUD_API_00589 */
  #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
  Dem_NumOfPrestoredFFType LddIndex;
  /* @Trace: Dem_SUD_API_00590 */
  for (LddIndex = DEM_ZERO; LddIndex < DEM_MAX_NUMBER_PRESTORED_FF; LddIndex++)
  {
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    /* @Trace: Dem_SUD_API_00587 */
    #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
    uint32 LulIndexFF;
    /* @Trace: Dem_SUD_API_00583 */
    /* @Trace: Dem_SUD_API_00588 */
    /* polyspace +2 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
    for (LulIndexFF = DEM_ZERO;
         LulIndexFF < DEM_SIZE_OF_PRESTORED_FF;
         LulIndexFF++)
    {
      /* @Trace: Dem_SUD_API_00591 */
      Dem_NonVolatileData.DataPrestored[LddIndex].data[LulIndexFF] =
          DEM_SET_BYTE;
    }
    #endif
    Dem_NonVolatileData.EvIdPrestored[LddIndex] = DEM_NO_EVENT;
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
  }
  #endif
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetOpCycleState
*
* Service ID           : None
*
* Description          : Sets the state of an operation(start or end)
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : OperationCycleId, state
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
*****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_SetOpCycleState(
    uint8 OperationCycleId,
  Dem_OperationCycleStateType state)
{
  boolean LblDirty;
  #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)  
  if (Dem_NonVolatileData.OperationCycleState[OperationCycleId] != state)
  {
    /* @Trace: Dem_SUD_API_00594 */
    Dem_NonVolatileData.OperationCycleState[OperationCycleId] = state;  
    LblDirty = DEM_TRUE;
  }  
  else
  {
    /* @Trace: Dem_SUD_API_00593 */
    LblDirty = DEM_FALSE;
  }
  #else
  /* @Trace: Dem_SUD_API_00592 */
  Dem_OperationCycleState[OperationCycleId] = state;
  LblDirty = DEM_FALSE;
  #endif
  
  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetOpCycleQualifiedState
*
* Service ID           : None
*
* Description          : Sets the Qualified state of an operation
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : OperationIndex, state
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
*****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_SetOpCycleQualifiedState(
    uint8 OperationCycleId,
  Dem_OperationCycleStateType state)
{
  boolean LblDirty;
  #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)  
  if (Dem_NonVolatileData.OperationCycleQualifiedStt[OperationCycleId] != state)
  {
    /* @Trace: Dem_SUD_API_00594 */
    Dem_NonVolatileData.OperationCycleQualifiedStt[OperationCycleId] = state;  
    LblDirty = DEM_TRUE;
  }  
  else
  {
    /* @Trace: Dem_SUD_API_00593 */
    LblDirty = DEM_FALSE;
  }
  #else
  /* @Trace: Dem_SUD_API_00592 */
  Dem_OperationCycleQualifiedStt[OperationCycleId] = state;
  LblDirty = DEM_FALSE;
  #endif
  
  return LblDirty;
}


/******************************************************************************
* Function Name        : Dem_EvMem_GetOpCycleState
*
* Service ID           : None
*
* Description          : Gets the state of an operation(start or end)
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : OperationCycleId
*                        
* InOut parameter      : None
*
* Output Parameters    : CycleState
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_GetOpCycleState(
  uint8 OperationCycleId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState)
{
  #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)  
  /* @Trace: Dem_SUD_API_00595 */
  *CycleState = Dem_NonVolatileData.OperationCycleState[OperationCycleId];
  #else
  /* @Trace: Dem_SUD_API_00596 */
  *CycleState = Dem_OperationCycleState[OperationCycleId];
  #endif
}

/******************************************************************************
* Function Name        : Dem_EvMem_GetOpCycleQualifiedState
*
* Service ID           : None
*
* Description          : Sets the qualified state of an operation
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : OperationIndex 
*                        
* InOut parameter      : None
*
* Output Parameters    : state
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_GetOpCycleQualifiedState(
  uint8 OperationCycleId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState)
{
  #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)  
  /* @Trace: Dem_SUD_API_00595 */
  *CycleState = Dem_NonVolatileData.OperationCycleQualifiedStt[OperationCycleId];
  #else
  /* @Trace: Dem_SUD_API_00596 */
  *CycleState = Dem_OperationCycleQualifiedStt[OperationCycleId];
  #endif
}

/******************************************************************************
* Function Name        : Dem_EvMem_IncAgingCounter
*
* Service ID           : None
*
* Description          : Increase the aging counter of the event that stored
*                        in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : entry
*                        
* InOut parameter      : None
*
* Output Parameters    : AgingCounter
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_IncAgingCounter(
  Dem_EventMemoryEntryPtrType entry,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) AgingCounter)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00597 */
  if (entry->AgingCycleCounter < (uint8)0xFF)
  {
    /* @Trace: Dem_SUD_API_00598 */
    ++(entry->AgingCycleCounter);
    *AgingCounter = entry->AgingCycleCounter;
    LblDirty = DEM_TRUE;
   }

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_GetAgingCounter
*
* Service ID           : None
*
* Description          : Gets the aging counter of the event that stored
*                        in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EventId, MemEntry, ElementType
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : uint8
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
/* @Trace: SRS_Diag_04068 SRS_Diag_04133 SRS_Diag_04178 SRS_Diag_04190
 */
/* @Trace: Dem_SUD_MACRO_099 */
FUNC(uint8, DEM_CODE) 
Dem_EvMem_GetAgingCounter(  
  Dem_EventIdType EventId,
  Dem_EventMemoryEntryPCType MemEntry,
  uint32 ElementType)
{
  uint8 LucAgingCounter = DEM_ZERO;
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  /* @Trace: SWS_Dem_00643
   * If the data element DEM_AGINGCTR_UPCNT is configured, the aging counter
   * mapping shall be based on a count-up mechanism from 0 to
   * DemAgingCycleCounterThreshold (refer to ISO-14229-1[2], Annex D).
   */
  /* @Trace: SWS_Dem_00492
   * The Dem module shall be able to cover the current value of the aging
   * counter of each individual event memory entry, to support an output.
   */
  /* @Trace: Dem_SUD_API_00599 */
  if (NULL_PTR != MemEntry)
  {
    if (DEM_DATA_ELEMENT_AGINGCTR_UPCNT == ElementType)
    {
      if (DEM_TRUE == DEM_GET_EVENTPARAM_AGING_ALLOWED(LddEvent->ParamFieldsA))
      {
        /* @Trace: Dem_SUD_API_00604 */
        LucAgingCounter =  MemEntry->AgingCycleCounter;
      }
      /* @Trace: SWS_Dem_01044
       * If Dem DemAgingAllowed is set to false the internal data element
       * DEM_AGINGCTR_UPCNT shall be 0.
       */
      else
      {
        /* @Trace: Dem_SUD_API_00605 */
        LucAgingCounter =  DEM_ZERO;
      }
    }
    /* @Trace: SWS_Dem_00673
     * If the data element DEM_AGINGCTR_DOWNCNT is configured, the aging counter
     * mapping shall be based on a count-down mechanism from
     * DemAgingCycleCounterThreshold to 0 (refer to ISO-14229-1[2], Annex D).
     */
    /* @Trace: Dem_SUD_API_00603 */
    else if (DEM_DATA_ELEMENT_AGINGCTR_DOWNCNT == ElementType)
    {
      if (DEM_TRUE == DEM_GET_EVENTPARAM_AGING_ALLOWED(LddEvent->ParamFieldsA))
      {
        /* @Trace: Dem_SUD_API_00607 */
        LucAgingCounter =
            LddEvent->ucAgingCycleCounterThreshold -
            MemEntry->AgingCycleCounter;
      }
      else
      {
        /* @Trace: Dem_SUD_API_00610 */
        /* @Trace: SWS_Dem_01043
         * If DemAgingAllowed is set to false the internal data element
         * DEM_AGINGCTR_DOWNCNT shall be DemAgingCycleCounterThreshold if
         * configured or 255.
         */
        if (DEM_ZERO != LddEvent->ucAgingCycleCounterThreshold)
        {
          /* @Trace: Dem_SUD_API_00608 */
          LucAgingCounter = LddEvent->ucAgingCycleCounterThreshold;
        }
        else
        {
          /* @Trace: Dem_SUD_API_00609 */
          LucAgingCounter = DEM_AGING_COUNTER_MAX;
        }
      }
    }
    /* @Trace: SWS_Dem_01219
     * If the configuration parameter DemInternalDataElement is set to
     * DEM_AGINGCTR_UPCNT_FIRST_ACTIVE, the value shall be calculated analogous
     * to DEM_AGINGCTR_UPCNT. The difference is, that in case the current aging
     * counter has a value of 0 and the event status bits
     * TestFailedThisOperationCycle and TestNotCompletedThisOperationCycle are
     * set to False, a value of 1 is reported upon reading the Dem internal
     * aging counter.
     */
    /* @Trace: Dem_SUD_API_00606 */
    else if (DEM_DATA_ELEMENT_AGINGCTR_UPCNT_FIRST_ACTIVE == ElementType)
    {
      if ((DEM_ZERO == MemEntry->AgingCycleCounter) &&
          (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFTOC)) &&
          (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC)))
      {
        /* @Trace: Dem_SUD_API_00601 */
        LucAgingCounter =  DEM_ONE;
      }
      else
      {
        /* @Trace: Dem_SUD_API_00602 */
        LucAgingCounter =  MemEntry->AgingCycleCounter;
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_00600 */
      /* Nothing to do */
    }
  }
  return LucAgingCounter;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetAgingCounter
*
* Service ID           : None
*
* Description          : Sets the aging counter of the event that stored
*                        to API parameter AgingCycleCounter in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : entry, AgingCounter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetAgingCounter(
  Dem_EventMemoryEntryPtrType entry,
  uint8 AgingCounter)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00611 */
  if (AgingCounter != entry->AgingCycleCounter)
  {
    /* @Trace: Dem_SUD_API_00612 */
    LblDirty = DEM_TRUE;
    entry->AgingCycleCounter = AgingCounter;
  }

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetFailureCounter
*
* Service ID           : None
*
* Description          : Sets the aging counter of the event that stored to
*                        API parameter FailureCounter in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : entry, FailureCounter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetFailureCounter(
  Dem_EventMemoryEntryPtrType entry,
  uint8 FailureCounter)
{
  boolean LblDirty = DEM_FALSE;

  #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
  /* @Trace: Dem_SUD_API_00615 */
  if (entry->FailureCycleCounter != FailureCounter)
  {
    /* @Trace: Dem_SUD_API_00614 */
    entry->FailureCycleCounter = FailureCounter;
    LblDirty = DEM_TRUE;
  }
  #else
  /* @Trace: Dem_SUD_API_00613 */
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition evaluates to true or false according to configuration */
  DEM_UNUSED(FailureCounter);
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition evaluates to true or false according to configuration */
  DEM_UNUSED_PTR(entry);
  #endif

  return LblDirty;
}

/******************************************************************************
 * Function Name        : Dem_GetHighestMaximumFDC
 *
 * Service ID           : None
 *
 * Description          : Gets the maximum FDC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : MaxFDC
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  :
 *                        None
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04073 SRS_Diag_04125
 */
#if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)||\
    (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)|| \
    (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO))
FUNC(Std_ReturnType, DEM_CODE) Dem_GetHighestMaximumFDC(
  Dem_EventIdType EventId,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) MaxFDC)
{

  /* @Trace: SWS_Dem_00789
   * If the UDS DTC of [ [SWS_Dem_00788]] is referenced by multiple
   * events or an combined DTC, the event with the highest maximum FDC value
   * shall be used to report.
   * */

  /* @Trace: SWS_Dem_00793
   * If the UDS DTC of [SWS_Dem_00792] is referenced by multiple
   * events or an combined DTC, the event with the highest maximum FDC value
   * shall be used to report.
   * */
  /* @Trace: SWS_Dem_00672
   * The fault detection counter of the combined DTC shall be the maximum fault
   * detection counter value of the sub-events.
   */
  Std_ReturnType LddRetVal = E_OK;
  sint8 LscMax = 0;
  Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
  if ((NULL_PTR != LddCbDTC) && (DEM_DTC_FORMAT_UDS == LddCbDTC->ddDtcFormat))
  {
    uint16 LusStartPos = Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
    const uint16 LusEndPos = Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
    Dem_EventIdType LddEvId;
    for (; LusStartPos < LusEndPos; LusStartPos++)
    {
      LddEvId = Dem_ListOfCombinedEvents[LusStartPos];
      /* @Trace: Dem_SUD_API_00618 */
      if (E_OK == Dem_GetFaultDetectionCounter(LddEvId, MaxFDC))
      {
        /* @Trace: Dem_SUD_API_00620 */
        if (*MaxFDC > LscMax)
        {
          /* @Trace: Dem_SUD_API_00619 */
          LscMax = *MaxFDC;
        }
      }
    }
    /* @Trace: Dem_SUD_API_00617 */
    *MaxFDC = LscMax;
  }
  else
  {
    /* @Trace: Dem_SUD_API_00616 */
    LddRetVal = E_NOT_OK;
  }
  return LddRetVal;
}
#endif

/******************************************************************************
 * Function Name        : Dem_EvMem_GetDTCByOccurrenceTime
 *
 * Service ID           : None
 *
 * Description          : Gets DTC by Occurence time
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId, ReqType
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : DTC
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_EvMem_GetDTCByOccurrenceTime(
  uint8 ClientId,
  Dem_DTCRequestType ReqType, 
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  Dem_DTCRequestType LddReqType = ReqType - DEM_ONE;
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  if (LddReqType < DEM_MAX_DTC_REQEST_TYPE)
  {
    SchM_Enter_Dem_REQUEST_OCCTIME_PROTECTION();
    *DTC = Dem_EventStatusNvRamData.DTCOccurenceTimeData[ClientId].
             DTCOccurenceTime[LddReqType];
    SchM_Exit_Dem_REQUEST_OCCTIME_PROTECTION();
    /* @Trace: Dem_SUD_API_00623 */
    if (DEM_NO_DTC != *DTC)
    {
      /* @Trace: Dem_SUD_API_00622 */
      LddRetVal = E_OK;
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_00621 */
    *DTC = DEM_NO_DTC;
  }

  return LddRetVal;
}
#endif


/******************************************************************************
* Function Name        : Dem_EvMem_IncreaseIndicatorHealingCounter
*
* Service ID           : None
*
* Description          : Increase the Healing counter of the event that stored
*                        in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : HealingCounterId
*                        
* InOut parameter      : None
*
* Output Parameters    : CounterValue
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_IncreaseIndicatorHealingCounter(
  const Dem_NumOfIndicatorAttributeType HealingCounterId,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) CounterValue)
{
  DEM_UNUSED(HealingCounterId);
  DEM_UNUSED(CounterValue);
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00625 */
  #if (DEM_NUM_OF_HEALING_COUNTER > DEM_ZERO)
  if (HealingCounterId < DEM_NUM_OF_HEALING_COUNTER)
  {
    /* @Trace: Dem_SUD_API_00626 */
    if (Dem_EventStatusNvRamData.
          IndicatorHealingCycleCounter[HealingCounterId] < (uint8)0xFF)
    {
      /* @Trace: Dem_SUD_API_00627 */
      Dem_EventStatusNvRamData.IndicatorHealingCycleCounter[HealingCounterId]++;
      LblDirty = DEM_TRUE;
    }
    *CounterValue =
        Dem_EventStatusNvRamData.IndicatorHealingCycleCounter[HealingCounterId];
  }
  else
  {
    /* @Trace: Dem_SUD_API_00624 */
    *CounterValue = DEM_ZERO;
  }
  #endif

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_IncreaseIndicatorFailureCounter
*
* Service ID           : None
*
* Description          : Increase the failure counter of the event that stored
*                        in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : FailureCounterId
*                        
* InOut parameter      : None
*
* Output Parameters    : CounterValue
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_IncreaseIndicatorFailureCounter(
  const Dem_NumOfIndicatorAttributeType FailureCounterId,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) CounterValue)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00629 */
  #if (DEM_NUM_OF_FAILURE_COUNTER > DEM_ZERO)
  if (FailureCounterId < DEM_NUM_OF_FAILURE_COUNTER)
  {
    /* @Trace: Dem_SUD_API_00631 */
    if (Dem_EventStatusNvRamData.
          IndicatorFailureCycleCounter[FailureCounterId] < (uint8)0xFF)
    {
      /* @Trace: Dem_SUD_API_00630 */
      LblDirty = DEM_TRUE;
      Dem_EventStatusNvRamData.IndicatorFailureCycleCounter[FailureCounterId]++;
    }
    *CounterValue =
        Dem_EventStatusNvRamData.IndicatorFailureCycleCounter[FailureCounterId];
  }
  else
  {
    /* @Trace: Dem_SUD_API_00628 */
    *CounterValue = DEM_ZERO;
  }
  #else
  DEM_UNUSED(FailureCounterId);
  DEM_UNUSED(CounterValue);
  #endif

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetIndicatorHealingCounter
*
* Service ID           : None
*
* Description          : Set indicator healing counter
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : HealingCounterId, HealingCounter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetIndicatorHealingCounter(
  const Dem_NumOfIndicatorAttributeType HealingCounterId,
  const uint8 HealingCounter)
{
  DEM_UNUSED(HealingCounterId);
  DEM_UNUSED(HealingCounter);
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00632 */
  #if (DEM_NUM_OF_HEALING_COUNTER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00633 */
  if (HealingCounterId < DEM_NUM_OF_HEALING_COUNTER)
  {
    /* @Trace: Dem_SUD_API_00634 */
    if (Dem_EventStatusNvRamData.
          IndicatorHealingCycleCounter[HealingCounterId] != HealingCounter)
    {
      /* @Trace: Dem_SUD_API_00635 */
      Dem_EventStatusNvRamData.IndicatorHealingCycleCounter[HealingCounterId] =
          HealingCounter;
      LblDirty = DEM_TRUE;
    }
  }
  #endif

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetIndicatorFailureCounter
*
* Service ID           : None
*
* Description          : Set indicator failure counter
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : FailureCounterId, FailureCounter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetIndicatorFailureCounter(
  const Dem_NumOfIndicatorAttributeType FailureCounterId,
  const uint8 FailureCounter)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00645 */
  #if (DEM_NUM_OF_FAILURE_COUNTER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00646 */
  if (FailureCounterId < DEM_NUM_OF_FAILURE_COUNTER)
  {
    /* @Trace: Dem_SUD_API_00647 */
    if (Dem_EventStatusNvRamData.
          IndicatorFailureCycleCounter[FailureCounterId] != FailureCounter)
    {
      /* @Trace: Dem_SUD_API_00648 */
      Dem_EventStatusNvRamData.IndicatorFailureCycleCounter[FailureCounterId] =
          FailureCounter;
      LblDirty = DEM_TRUE;
    }
  }
  #else
  DEM_UNUSED(FailureCounterId);
  DEM_UNUSED(FailureCounter);
  #endif

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetIndicatorAttStatus
*
* Service ID           : None
*
* Description          : Set indicator att Status
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : IndicatorAtt, AttStatus
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetIndicatorAttStatus(
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  IndicatorAtt,
  const boolean AttStatus)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00636 */
  #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
  if (DEM_TRUE == AttStatus)
  {
    /* @Trace: Dem_SUD_API_00637 */
    #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00638 */
    if (DEM_NO_INDATT_IDX != IndicatorAtt->IndicatorAttStatusPos)
    {        
      /* @Trace: Dem_SUD_API_13311 */    
      DEM_BITARRAY_BITSET(
          Dem_EventStatusNvRamData.AttributeStatus,
          IndicatorAtt->IndicatorAttStatusPos);
      LblDirty = DEM_TRUE;
    }
    #endif
    /* @Trace: Dem_SUD_API_00639 */
    if ((IndicatorAtt->Behavior < DEM_NUM_OF_INDICATOR_BEHAVIOR) &&
        (IndicatorAtt->IndicatorIdRef < DEM_NUM_OF_INDICATORID))
    {
      /* @Trace: Dem_SUD_API_13312 */
      Dem_IndicatorBehaviorAccumulator
          [IndicatorAtt->IndicatorIdRef][IndicatorAtt->Behavior]++;
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_00641 */
    /* @Trace: Dem_SUD_API_00642 */
    #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00643 */
    if (DEM_NO_INDATT_IDX != IndicatorAtt->IndicatorAttStatusPos)
    {
      DEM_BITARRAY_BITCLEAR(
          Dem_EventStatusNvRamData.AttributeStatus,
          IndicatorAtt->IndicatorAttStatusPos);
      LblDirty = DEM_TRUE;
    }
    #endif
    /* @Trace: Dem_SUD_API_00640 */
    if ((IndicatorAtt->Behavior < DEM_NUM_OF_INDICATOR_BEHAVIOR) &&
        (IndicatorAtt->IndicatorIdRef < DEM_NUM_OF_INDICATORID))
    {
      /* @Trace: Dem_SUD_API_00644 */
      Dem_IndicatorBehaviorAccumulator
        [IndicatorAtt->IndicatorIdRef][IndicatorAtt->Behavior]--;
    }
  }
  #else
  DEM_UNUSED(IndicatorAtt);
  DEM_UNUSED(AttStatus); 
  #endif
  
  return LblDirty;
}



/******************************************************************************
* Function Name        : Dem_EvMem_ResetIndicatorAttribute
*
* Service ID           : None
*
* Description          : Reset indicator attribute
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : IndicatorAttr
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_ResetIndicatorAttribute(
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  IndicatorAttr)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00649 */
  #if (DEM_NUM_OF_FAILURE_COUNTER > DEM_ZERO)
  {
    Dem_NumOfIndicatorAttributeType LddPos =
        IndicatorAttr->FailureCycleCounterPos;
    /* @Trace: Dem_SUD_API_00655 */
    if (LddPos < DEM_NUM_OF_FAILURE_COUNTER)
    {
      /* @Trace: Dem_SUD_API_00656 */
      if (DEM_ZERO !=
            Dem_EventStatusNvRamData.IndicatorFailureCycleCounter[LddPos])
      {
        /* @Trace: Dem_SUD_API_00181 */
        Dem_EventStatusNvRamData.IndicatorFailureCycleCounter[LddPos] =
            DEM_ZERO;
        LblDirty = DEM_TRUE;
      }
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00657 */
  #if (DEM_NUM_OF_HEALING_COUNTER > DEM_ZERO)
  {
    Dem_NumOfIndicatorAttributeType LddPos =
        IndicatorAttr->HealingCycleCounterPos;
    /* @Trace: Dem_SUD_API_00658 */
    if (LddPos < DEM_NUM_OF_HEALING_COUNTER)
    {
      /* @Trace: Dem_SUD_API_00659 */
      if (DEM_ZERO !=
            Dem_EventStatusNvRamData.IndicatorHealingCycleCounter[LddPos])
      {
        /* @Trace: Dem_SUD_API_00660 */
        Dem_EventStatusNvRamData.IndicatorHealingCycleCounter[LddPos] = DEM_ZERO;
        LblDirty = DEM_TRUE;
      }
    }
  }
  #endif
  
  /* @Trace: Dem_SUD_API_00661 */
  #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
  { 
    Dem_NumOfIndicatorAttributeType LddPos =
        IndicatorAttr->IndicatorAttStatusPos;
    /* @Trace: Dem_SUD_API_00662 */
    if (LddPos < DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS)
    {
      /* @Trace: Dem_SUD_API_00650 */
      if (DEM_FALSE != DEM_BITARRAY_BITTEST_ISBITSET(
            Dem_EventStatusNvRamData.AttributeStatus , LddPos))
      {
        /* @Trace: Dem_SUD_API_00651 */
        DEM_BITARRAY_BITCLEAR(
            Dem_EventStatusNvRamData.AttributeStatus, LddPos);
        LblDirty = DEM_TRUE;
      }
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00652 */
  #if ((DEM_NUMBER_OF_INDICATORS > DEM_ZERO ) && \
       (DEM_NUM_OF_INDICATOR_BEHAVIOR > DEM_ZERO))
  /* @Trace: Dem_SUD_API_00653 */
  if ((IndicatorAttr->Behavior < DEM_NUM_OF_INDICATOR_BEHAVIOR) &&
      (IndicatorAttr->IndicatorIdRef < DEM_NUM_OF_INDICATORID))
  {
    /* @Trace: Dem_SUD_API_00654 */
    Dem_IndicatorBehaviorAccumulator
        [IndicatorAttr->IndicatorIdRef][IndicatorAttr->Behavior] = 0;
  }
  #endif
  
  #if ((DEM_NUM_OF_FAILURE_COUNTER == DEM_ZERO ) \
        && (DEM_NUM_OF_HEALING_COUNTER == DEM_ZERO) \
        && (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS == DEM_ZERO) \
        && ((DEM_NUMBER_OF_INDICATORS == DEM_ZERO) \
        || (DEM_NUM_OF_INDICATOR_BEHAVIOR == DEM_ZERO)) \
      )
  DEM_UNUSED(IndicatorAttr);
  #endif

  return LblDirty;
}

/******************************************************************************
* Function Name        : Dem_EvMem_InitIndicatorBehaviorAccumulator
*
* Service ID           : None
*
* Description          : Init indicator behavior accumulator
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
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
/* @Trace: Dem_SUD_MACRO_103 */
FUNC(void, DEM_CODE) 
Dem_EvMem_InitIndicatorBehaviorAccumulator(void)
{
  /* @Trace: Dem_SUD_API_00663 */
  #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)

  uint8 LucStatus;
  /* @Trace: Dem_SUD_API_00665 */
  #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00666 */
  Dem_NumOfIndicatorAttributeType LddPos;
  #endif
  
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  LddIndicator;
  Dem_NumOfIndicatorAttributeType LddIdx;
  /* @Trace: Dem_SUD_API_00667 */
  for (LddIdx = DEM_ZERO; LddIdx < DEM_NUMBER_OF_INDICATORS ; LddIdx++)
  {  
    LddIndicator = &Dem_GaaIndicatorList[LddIdx];
    /* @Trace: Dem_SUD_API_00668 */
    #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
    LddPos = LddIndicator->IndicatorAttStatusPos;
    if (LddPos < DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS)
    {
      /* @Trace: Dem_SUD_API_00670 */
      LucStatus = (boolean)DEM_BITARRAY_BITGET(
          Dem_EventStatusNvRamData.AttributeStatus , LddPos);
    }
    else
    #endif
    {
      /* @Trace: Dem_SUD_API_00669 */
      LucStatus = (boolean)(((uint8)(Dem_AllEventStatusByte
          [LddIndicator->EventIdRef] >> 7U)) & (uint8)0x01);
    } 
    /* @Trace: Dem_SUD_API_00671 */
    if (DEM_FALSE != LucStatus)
    {
      /* @Trace: Dem_SUD_API_00672 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      if ((DEM_NUM_OF_INDICATORID > LddIndicator->IndicatorIdRef) &&
          (DEM_NUM_OF_INDICATOR_BEHAVIOR > LddIndicator->Behavior))
      {
        /* @Trace: Dem_SUD_API_00664 */
        Dem_IndicatorBehaviorAccumulator
          [LddIndicator->IndicatorIdRef][LddIndicator->Behavior]++;
      }
    }

  }
  #endif
}

/******************************************************************************
* Function Name        : Dem_EvMem_GetIndicatorAttStatus
*
* Service ID           : None
*
* Description          : Get indicator attStatus of the event
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EventId, IndicatorAttrId
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
FUNC(boolean, DEM_CODE) 
Dem_EvMem_GetIndicatorAttStatus(
  const Dem_EventIdType EventId,
  const Dem_NumOfIndicatorAttributeType IndicatorAttrId)
{
  DEM_UNUSED(IndicatorAttrId);
  boolean LblStatus = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00676 */
  #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
  if (Dem_Event[EventId - DEM_ONE].ucNumberofIndicator > DEM_ONE)
  {
    /* @Trace: Dem_SUD_API_00674 */
    if (DEM_BITARRAY_BITNSLOTS(
        DEM_ONE + DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS) >=
          DEM_BITARRAY_BITSLOT(IndicatorAttrId))
    {
      /* @Trace: Dem_SUD_API_00675 */
      LblStatus = DEM_BITARRAY_BITGET(
          Dem_EventStatusNvRamData.AttributeStatus , IndicatorAttrId);
    }
  }
  else
  #endif
  {
    /* @Trace: Dem_SUD_API_00673 */
    LblStatus =
        (boolean)(((uint8)(Dem_AllEventStatusByte[EventId] >> DEM_SEVEN)) &
                   (uint8)DEM_ONE);
  }
  
  return LblStatus;
}

/******************************************************************************
* Function Name        : Dem_EvMem_GetUdsStatusByteToNvData
*
* Service ID           : None
*
* Description          : Gets UDS status byte to NvData
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EventId, DTCOrigin
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : Dem_UdsStatusByteType
*
* Preconditions        : None
*
* Remarks              : This function is called by Dem_EvMem_Init once
*
*****************************************************************************/
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Dem_UdsStatusByteType, DEM_CODE) Dem_EvMem_GetUdsStatusByteToNvData(
    const Dem_EventIdType EventId, const Dem_DTCOriginType DTCOrigin)
{
  DEM_UNUSED(DTCOrigin);
  Dem_UdsStatusByteType LddUdsStatusByte = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00677 */
  #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
  Dem_NumOfEventMemoryEntryType LddSizeOfMem =
        Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
  Dem_NumOfEventMemoryEntryType LddStartIndex =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
  LddSizeOfMem = LddSizeOfMem + LddStartIndex;

  if (Dem_EvMemToEventMap[EventId] <  LddSizeOfMem)
  {
    Dem_EventMemoryEntryPtrType MemEntry = NULL_PTR;

    /* Duplicated code for performance and runtime check(polyspace) */
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)  
    {
      MemEntry = &Dem_PrimaryEventMemory[Dem_EvMemToEventMap[EventId]];
    }
    /* @Trace: Dem_SUD_API_00685 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00684 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_00687 */
      MemEntry = &Dem_UserDefinedEventMemory[Dem_EvMemToEventMap[EventId]];
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_00686 */
      /* Do nothing */
    }   
    /* @Trace: Dem_SUD_API_00688 */     
    if (NULL_PTR != MemEntry)
    {
      #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
      Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
      /* @Trace: Dem_SUD_API_00690 */
      if (NULL_PTR != LddCbDTC)
      {
        if (DEM_ONE == LddCbDTC->ddNumberOfEvents)
        {
          /* @Trace: Dem_SUD_API_00679 */
          LddUdsStatusByte = MemEntry->EventStatuByte[DEM_ZERO];
        }
        else
        {
          /* @Trace: Dem_SUD_API_00678 */
          Dem_NumOfEventIdType LddIndex = DEM_ZERO;
          Dem_NumOfEventIdType LddStartPos =
              Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
          const Dem_NumOfEventIdType LddEndPos =
              Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
          /* @Trace: Dem_SUD_API_00680 */
          while (LddStartPos < LddEndPos)
          {    
            /* @Trace: Dem_SUD_API_00681 */
            /* @Trace: Dem_SUD_MACRO_107 */
            if ((LddIndex < DEM_MAX_NUM_EVENTS_PER_DTC) &&
                (Dem_ListOfCombinedEvents[LddStartPos] == EventId))
            {
              /* @Trace: Dem_SUD_API_00682 */
              LddUdsStatusByte = MemEntry->EventStatuByte[LddIndex];
              break;
            }
            ++LddIndex;
            ++LddStartPos;
          }
        }
      }
      #else
      /* @Trace: Dem_SUD_API_00689 */
      LddUdsStatusByte = MemEntry->EventStatuByte[0];
      #endif
    }
  }
  else
  #endif  
  {    
    /* @Trace: Dem_SUD_API_00683 */
    /*+------------------------------------+-----+
      | TestFailed                         | 0   |
      +------------------------------------+-----+
      | TestFailedThisOperationCycle       | 1   |
      +------------------------------------+-----+
      | PendingDTC                         | 2   |
      +------------------------------------+-----+
      | ConfirmedDTC                       | 3   |
      +------------------------------------+-----+
      | TestNotCompletedSinceLastClear     | 4   |
      +------------------------------------+-----+
      | TestFailedSinceLastClear           | 5   |
      +------------------------------------+-----+
      | TestNotCompletedThisOperationCycle | 6   |
      +------------------------------------+-----+
      | WarningIndicatorRequested          | 7   |
      +------------------------------------+-----+*/
    
    #if (DEM_UDS_STATUS_TF_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01268 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId, DEM_ZERO,
        Dem_EventStatusNvRamData.TF_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01280 */
    /* Default Value is 'Clear' */    
    #endif   
   
    #if (DEM_UDS_STATUS_TFTOC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01269 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId,
        DEM_ONE,
        Dem_EventStatusNvRamData.TFTOC_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01281 */
    /* Default Value is 'Clear' */    
    #endif
    
    #if (DEM_UDS_STATUS_PDTC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01270 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId, DEM_TWO,
        Dem_EventStatusNvRamData.PDTC_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01282 */
    /* Default Value is 'Clear' */    
    #endif

    #if (DEM_UDS_STATUS_CDTC_ALLEVENTSTATUS > DEM_ZERO) /* always not used */
    /* @Trace: Dem_SUD_API_01271 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId,
        DEM_THREE,
        Dem_EventStatusNvRamData.CDTC_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01272 */
    /* Default Value is 'Clear' */    
    #endif
    
    #if (DEM_UDS_STATUS_TNCSLC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01273 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId,
        DEM_FOUR,
        Dem_EventStatusNvRamData.TNCSLC_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01274 */
    LddUdsStatusByte |= DEM_UDS_STATUS_TNCSLC;
    #endif
    
    #if (DEM_UDS_STATUS_TFSLC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01275 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId,
        DEM_FIVE,
        Dem_EventStatusNvRamData.TFSLC_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01283 */
    /* Default Value is 'Clear' */    
    #endif  
    
    #if (DEM_UDS_STATUS_TNCTOC_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01276 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId,
        DEM_SIX,
        Dem_EventStatusNvRamData.TNCTOC_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01277 */
    LddUdsStatusByte |= DEM_UDS_STATUS_TNCTOC;
    #endif
    
    #if (DEM_UDS_STATUS_WIR_ALLEVENTSTATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01278 */
    DEM_UDSSTATUS_GET_NV(
        LddUdsStatusByte,
        EventId, DEM_SEVEN,
        Dem_EventStatusNvRamData.WIR_BitArray);
    #else
    /* @Trace: Dem_SUD_API_01279 */
    /* Default Value is 'Clear' */
    #endif 
  }

  return LddUdsStatusByte;
}

/******************************************************************************
* Function Name        : Dem_EvMem_SetUdsStatusByteToEvMemEntry
*
* Service ID           : None
*
* Description          : Stores the event status in the event memory entry
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EventId, DTCOrigin, memLoc
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
*****************************************************************************/
#if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
static FUNC(void, DEM_CODE) 
Dem_EvMem_SetUdsStatusByteToEvMemEntry(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_NumOfEventMemoryEntryType memLoc)
{
  Dem_UdsStatusByteType LddEventStatusByteNew = Dem_AllEventStatusByte[EventId];
  Dem_EventMemoryEntryPtrType LddEvMemEntry = NULL_PTR;

  /* Duplicated code for performance and runtime check(polyspace) */        
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)  
  {
    /* @Trace: Dem_SUD_API_00691 */
    LddEvMemEntry = &Dem_PrimaryEventMemory[memLoc];
  }
  /* @Trace: Dem_SUD_API_00697 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00696 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_00699 */
    LddEvMemEntry = &Dem_UserDefinedEventMemory[Dem_EvMemToEventMap[EventId]];
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00698 */
    /* Do nothing */
  } 

  /* Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId); */
  /* polyspace<RTE:UNR:Not a defect:No action planned>  Avoid the runtime error
   * of the polyspace */
  /* @Trace: Dem_SUD_API_00700 */
  if (NULL_PTR != LddEvMemEntry)
  {
    #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
    /* @Trace: Dem_SUD_API_00702 */
    if (NULL_PTR != LddCbDTC)
    {    
      if (DEM_ONE == LddCbDTC->ddNumberOfEvents)
      {
        /* @Trace: Dem_SUD_API_00703 */
        LddEvMemEntry->EventStatuByte[DEM_ZERO] = LddEventStatusByteNew;
      }
      /* > DEM_ONE */
      else
      {
        /* @Trace: Dem_SUD_API_00692 */
        Dem_NumOfEventIdType LddIndex = DEM_ZERO;
        Dem_NumOfEventIdType LddStartPos =
            Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
        const Dem_NumOfEventIdType LddEndPos =
            Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
            /* @Trace: Dem_SUD_API_00693 */
        while (LddStartPos < LddEndPos)
        {    
          if ((LddIndex < DEM_MAX_NUM_EVENTS_PER_DTC) &&
            (Dem_ListOfCombinedEvents[LddStartPos] == EventId))
          {
            /* @Trace: Dem_SUD_API_00694 */
            LddEvMemEntry->EventStatuByte[LddIndex] = LddEventStatusByteNew;
            break;
          }
          /* @Trace: Dem_SUD_API_00695 */
          ++LddIndex;
          ++LddStartPos;
        }
      }
    }
    #else
    /* @Trace: Dem_SUD_API_00701 */
    LddEvMemEntry->EventStatuByte[DEM_ZERO] = LddEventStatusByteNew;
    #endif
  }

}
#endif

/******************************************************************************
* Function Name        : Dem_EvMem_SetUdsStatusByteToNvData
*
* Service ID           : None
*
* Description          : Stores the event status in the Event Status Nv Data
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
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : Global Variable(s)  :
*
*                        Function(s) invoked :
*
*****************************************************************************/
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) 
Dem_EvMem_SetUdsStatusByteToNvData(
  const Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_00704 */
  #if ((DEM_UDS_STATUS_TF_ALLEVENTSTATUS > DEM_ZERO)     ||\
       (DEM_UDS_STATUS_TFTOC_ALLEVENTSTATUS > DEM_ZERO)  ||\
       (DEM_UDS_STATUS_PDTC_ALLEVENTSTATUS > DEM_ZERO)   ||\
       (DEM_UDS_STATUS_CDTC_ALLEVENTSTATUS > DEM_ZERO)   ||\
       (DEM_UDS_STATUS_TNCSLC_ALLEVENTSTATUS > DEM_ZERO) ||\
       (DEM_UDS_STATUS_TFSLC_ALLEVENTSTATUS > DEM_ZERO)  ||\
       (DEM_UDS_STATUS_TNCTOC_ALLEVENTSTATUS > DEM_ZERO) ||\
       (DEM_UDS_STATUS_WIR_ALLEVENTSTATUS > DEM_ZERO))
  /* @Trace: Dem_SUD_API_00712 */
  Dem_UdsStatusByteType LddEventStatusByteNew = Dem_AllEventStatusByte[EventId];
  #endif

  /*+------------------------------------+-+----------------------+
    | TestFailed                         |0| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+
    | TestFailedThisOperationCycle       |1| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+
    | PendingDTC                         |2| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+
    | ConfirmedDTC                       |3| N/A                  |
    +------------------------------------+-+----------------------+
    | TestNotCompletedSinceLastClear     |4| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+
    | TestFailedSinceLastClear           |5| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+
    | TestNotCompletedThisOperationCycle |6| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+
    | WarningIndicatorRequested          |7| Ram->GeneralNvData   |
    +------------------------------------+-+----------------------+*/ 
  /* @Trace: Dem_SUD_API_00713 */
  #if (DEM_UDS_STATUS_TF_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00711 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.TF_BitArray,
      EventId, LddEventStatusByteNew,
      DEM_UDS_STATUS_TF);
  #endif   
  /* @Trace: Dem_SUD_API_00714 */
  #if (DEM_UDS_STATUS_TFTOC_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00710 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.TFTOC_BitArray,
      EventId,
      LddEventStatusByteNew,
      DEM_UDS_STATUS_TFTOC);
  #endif
  /* @Trace: Dem_SUD_API_00715 */
  #if (DEM_UDS_STATUS_PDTC_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00709 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.PDTC_BitArray,
      EventId, LddEventStatusByteNew,
      DEM_UDS_STATUS_PDTC);
  #endif
  /* @Trace: Dem_SUD_API_00716 */
  #if (DEM_UDS_STATUS_CDTC_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00708 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.CDTC_BitArray,
      EventId,
      LddEventStatusByteNew,
      DEM_UDS_STATUS_CDTC);
  #endif
  /* @Trace: Dem_SUD_API_00717 */
  #if (DEM_UDS_STATUS_TNCSLC_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00707 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.TNCSLC_BitArray,
      EventId,
      LddEventStatusByteNew,
      DEM_UDS_STATUS_TNCSLC);
  #endif
  /* @Trace: Dem_SUD_API_00718 */
  #if (DEM_UDS_STATUS_TFSLC_ALLEVENTSTATUS > DEM_ZERO)
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.TFSLC_BitArray,
      EventId,
      LddEventStatusByteNew,
      DEM_UDS_STATUS_TFSLC);
  #endif  
  /* @Trace: Dem_SUD_API_00719 */
  #if (DEM_UDS_STATUS_TNCTOC_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00706 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.TNCTOC_BitArray,
      EventId, LddEventStatusByteNew,
      DEM_UDS_STATUS_TNCTOC);
  #endif
  /* @Trace: Dem_SUD_API_00720 */
  #if (DEM_UDS_STATUS_WIR_ALLEVENTSTATUS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00705 */
  DEM_UDSSTATUS_SYNC_NV(
      Dem_EventStatusNvRamData.WIR_BitArray,
      EventId,
      LddEventStatusByteNew,
      DEM_UDS_STATUS_WIR);
  #endif  
}


/******************************************************************************
* Function Name        : Dem_EvMem_TriggerNvDataStorage
*
* Service ID           : None
*
* Description          : Trigger the Nv data storage of event status on event
*                        status is changed
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : EventId, DTCOrigin, EventStatusByteOld, NvDataBlkStatus
*                        EvMemEntryIsDirty, EvStatusIsDirty
*
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : uint8
*
* Preconditions        : None
*
* Remarks              : 
*****************************************************************************/
FUNC(uint8, DEM_CODE) 
Dem_EvMem_TriggerNvDataStorage(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_UdsStatusByteType EventStatusByteOld,
  uint8 NvDataBlkStatus,
  boolean EvMemEntryIsDirty,
  boolean EvStatusIsDirty)
{
  boolean LblEvStatusIsDirty = EvStatusIsDirty;
  /* polyspace<RTE:UNR:Not a defect:No action planned>  Avoid the runtime error
   * of the polyspace */
  /* @Trace: Dem_SUD_API_00721 */
  if ((DEM_NO_EVENT != EventId) && (EventId <= DEM_NUMBER_OF_EVENTS) )
  {
    Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[EventId];            
    Dem_NumOfEventMemoryEntryType LddSizeOfMem =
              Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
    Dem_NumOfEventMemoryEntryType LddStartIndex =
                  Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
    LddSizeOfMem = LddSizeOfMem + LddStartIndex;
    /* @Trace: Dem_SUD_API_00732 */
    #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
    if ( LddMemLoc < LddSizeOfMem)
    {
      Dem_UdsStatusByteType LddMask;
      boolean LblStorageTestFailed = DEM_GET_EVENTPARAM_STORAGE_TF(
          Dem_Event[EventId - DEM_ONE].ParamFieldsA);
      
      if (DEM_TRUE == LblStorageTestFailed)
      {
        /* @Trace: Dem_SUD_API_00738 */
        LddMask = DEM_UDS_STATUS_MASK_EVMEM |
            ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF);
      }
      else /* FALSE */
      {
        /* @Trace: Dem_SUD_API_00739 */
        LddMask = DEM_UDS_STATUS_MASK_EVMEM &
                  ((Dem_UdsStatusByteType)
                   (~(Dem_UdsStatusByteType)DEM_UDS_STATUS_TF));
      }     
      /* @Trace: Dem_SUD_API_00740 */ 
      if (((EventStatusByteOld ^ Dem_AllEventStatusByte[EventId]) & LddMask) !=
              DEM_ZERO)
      { 
        /* @Trace: Dem_SUD_API_00741 */
        Dem_EvMem_SetUdsStatusByteToEvMemEntry(EventId, DTCOrigin, LddMemLoc);
        EvMemEntryIsDirty = DEM_TRUE;
      }
    }
    else
    #endif
    {    
      /* @Trace: Dem_SUD_API_00737 */
      /* if NvRamBlockAccessOptimizationSupport supports and displacement
       * support is off,EventStatus is missing in the EventStatusNvBlock */
      /* @Trace: Dem_SUD_API_00742 */
      #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)      
      const Dem_UdsStatusByteType LddEventStatusByteNew =
          Dem_AllEventStatusByte[EventId];

      Dem_UdsStatusByteType LddMask;
      boolean LblStorageTestFailed =
          DEM_GET_EVENTPARAM_STORAGE_TF(Dem_Event[EventId-DEM_ONE].ParamFieldsA);
      
      if ((boolean)DEM_TRUE == LblStorageTestFailed)
      {
        /* @Trace: Dem_SUD_API_00722 */
        LddMask = DEM_UDS_STATUS_MASK_ALLEVENTSTATUS |
                  ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF);
      }
      else /* FALSE */
      {
        /* @Trace: Dem_SUD_API_00743 */
        LddMask = DEM_UDS_STATUS_MASK_ALLEVENTSTATUS &
                  ((Dem_UdsStatusByteType)
                   (~(Dem_UdsStatusByteType)DEM_UDS_STATUS_TF));
      }  
      /* @Trace: Dem_SUD_API_00723 */
      #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
      /* if displacement is on and optimization is on*/
      /* if opimization is on  (status & mask) != DEM_ZERO or (status & mask)
       * is changed */
      /* @Trace: Dem_SUD_API_00724 */
      if (((LddEventStatusByteNew & DEM_UDS_STATUS_TRIGGER_ALLEVENTSTATUS ) !=
              DEM_ZERO) ||
         (((EventStatusByteOld ^ LddEventStatusByteNew) &
              DEM_UDS_STATUS_TRIGGER_ALLEVENTSTATUS) != DEM_ZERO))
       /* @Trace: Dem_SUD_API_00725 */
      #endif
      {
        /* @Trace: Dem_SUD_API_00726 */
        if (((EventStatusByteOld ^ LddEventStatusByteNew) & LddMask) !=
                DEM_ZERO)
        {  
          /* @Trace: Dem_SUD_API_00727 */
          Dem_EvMem_SetUdsStatusByteToNvData(EventId);
          LblEvStatusIsDirty = DEM_TRUE;
        }
      }
      #endif
    }
    /* @Trace: Dem_SUD_API_00728 */
    if (((boolean)DEM_TRUE == EvMemEntryIsDirty) &&
        ( LddMemLoc < LddSizeOfMem))
    {
      /* @Trace: Dem_SUD_API_00729 */
      Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, LddMemLoc, NvDataBlkStatus);

      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      if ( (EventId == Dem_PrimaryEventMemory[Dem_ObdMemoryId].EventIdRef) && 
           (EventId != DEM_NO_EVENT) )
      {
        Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, Dem_ObdMemoryId, NvDataBlkStatus);
      }
      #endif /* (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) */

    }
    
    /* Handle for Mirror Memory*/
    /* @Trace: Dem_SUD_API_00730 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00731 */
    if (DEM_TWO == (&Dem_Event[EventId - DEM_ONE])->ucNumOfDestSelected)
    {
      Dem_NumOfEventMemoryEntryType LddMemLocMirId =
          Dem_EvMem_FindMirMemLoc(EventId);
      /* @Trace: Dem_SUD_API_00733 */
      if ((DEM_NO_EVMEM_ENTRY !=
            LddMemLocMirId) && ((boolean)DEM_TRUE == EvMemEntryIsDirty))
      {
        /* @Trace: Dem_SUD_API_00734 */
        Dem_EvMem_SetEvMemNvBlockStatus(
            DEM_DTC_ORIGIN_MIRROR_MEMORY, LddMemLocMirId, NvDataBlkStatus);
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00736 */
    if ((boolean)DEM_TRUE == LblEvStatusIsDirty)
    {
      /* @Trace: Dem_SUD_API_00735 */
      Dem_EvMem_SetNonVolatieDataStatus(
          DEM_NVDATA_ALL_EVENT_STATUS_ID, NvDataBlkStatus);
    }
  }

  return NvDataBlkStatus;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_DecreaseNumOfStoredEvtMemEntries
 *
 * Service ID           : None
 *
 * Description          : This function is to decrease number of 
 *                        stored event memory entries
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin, memSize
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_DecreaseNumOfStoredEvtMemEntries(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  uint8 memSize
)
{
  /* @Trace: Dem_SUD_API_00744 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00756 */
      if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
      {
        /* @Trace: Dem_SUD_API_00757 */
        if (Dem_NumOfStoredEvtMemEntryiesPriMem[LddEvent->ucEventMemDstIdx] >=
              memSize)
        {
          Dem_NumOfStoredEvtMemEntryiesPriMem[LddEvent->ucEventMemDstIdx] -=
              memSize;
        }
        /* @Trace: Dem_SUD_API_00759 */
        if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] >=
              memSize)
        {
          /* @Trace: Dem_SUD_API_00758 */
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] -=
              memSize;
        }
      }
    }
    /* @Trace: Dem_SUD_API_00760 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00755 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      uint8 LucIdxUserDefined =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
          /* @Trace: Dem_SUD_API_00762 */
      if (DEM_NO_IDX_U8 != LucIdxUserDefined)
      {
        /* @Trace: Dem_SUD_API_00745 */
        if (Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdxUserDefined] >=
              memSize)
        {
          Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdxUserDefined] -=
              memSize;
        }
        /* @Trace: Dem_SUD_API_00747 */
        if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] >=
              memSize)
        {
          /* @Trace: Dem_SUD_API_00746 */
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] -=
              memSize;
        }
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00748 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00761 */
    else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
    {
      if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
      {
        /* @Trace: Dem_SUD_API_00750 */
        if (Dem_NumOfStoredEvtMemEntryiesPerMem[LddEvent->ucEventMemDstIdx] >=
              memSize)
        {
          /* @Trace: Dem_SUD_API_00232 */
          Dem_NumOfStoredEvtMemEntryiesPerMem[LddEvent->ucEventMemDstIdx] -=
              memSize;
        }
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00751 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00749 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
      {
        /* @Trace: Dem_SUD_API_00753 */
        if (Dem_NumOfStoredEvtMemEntryiesMirMem[LddEvent->ucEventMemDstIdx] >=
              memSize)
        {
          /* @Trace: Dem_SUD_API_00754 */
          Dem_NumOfStoredEvtMemEntryiesMirMem[LddEvent->ucEventMemDstIdx] -=
             memSize;
        }
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_00752 */
      /* Nothing to do */
    }
    #endif
  }
}
/******************************************************************************
 * Function Name        : Dem_EvMem_IncreaseNumOfStoredEvtMemEntries
 *
 * Service ID           : None
 *
 * Description          : This function is to increase number of
 *                        stored event memory entries
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin, memSize
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
 *                        Dem_Event
 *                        Dem_NumOfStoredEvtMemEntryiesPriMem
 *                        Dem_NumOfStoredEvtMemEntryiesUDMem
 *
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  uint8 memSize
)
{
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00770 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00771 */
      Dem_NumOfStoredEvtMemEntryiesPriMem[LddEvent->ucEventMemDstIdx] =
          Dem_NumOfStoredEvtMemEntryiesPriMem[LddEvent->ucEventMemDstIdx] +
          memSize;
      Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] =
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] +
          memSize;
    }
  }
  /* @Trace: Dem_SUD_API_00772 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00763 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    uint8 LucIdxUserDefined =
        Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
        /* @Trace: Dem_SUD_API_00774 */
    if (DEM_NO_IDX_U8 != LucIdxUserDefined)
    {
      /* @Trace: Dem_SUD_API_00775 */
      Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdxUserDefined] =
          Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdxUserDefined] +
          memSize;

      Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] =
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] +
          memSize;
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00776 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00773 */
  else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00764 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00765 */
      Dem_NumOfStoredEvtMemEntryiesPerMem[LddEvent->ucEventMemDstIdx] =
          Dem_NumOfStoredEvtMemEntryiesPerMem[LddEvent->ucEventMemDstIdx] +
          memSize;
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00766 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00777 */
  else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00768 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00769 */
      Dem_NumOfStoredEvtMemEntryiesMirMem[LddEvent->ucEventMemDstIdx] =
          Dem_NumOfStoredEvtMemEntryiesMirMem[LddEvent->ucEventMemDstIdx] +
          memSize;
    }
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00767 */
    /* Nothing to do */
  }
}
/******************************************************************************
 * Function Name        : Dem_EvMem_IncNumOfStoredEvtMemEntriesFromClientId
 *
 * Service ID           : None
 *
 * Description          : This function is to increase number of
 *                        stored event memory entries from client id
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin, memSize
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
 *                        Dem_Event
 *                        Dem_NumOfStoredEvtMemEntryiesPriMem
 *                        Dem_NumOfStoredEvtMemEntryiesUDMem
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04164
 */
FUNC(void, DEM_CODE) Dem_EvMem_IncNumOfStoredEvtMemEntriesFromClientId(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  uint8 memSize
)
{
  /* @Trace: Dem_SUD_API_00778 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  uint8 LucMemSetIdx = Dem_Client[ClientId].usDemEventMemorySetId;
  /* @Trace: Dem_SUD_API_00784 */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
  if (DEM_NO_EVMEM_IDX != LucMemSetIdx)
  {
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00785 */
      Dem_NumOfStoredEvtMemEntryiesPriMem[LucMemSetIdx] =
         Dem_NumOfStoredEvtMemEntryiesPriMem[LucMemSetIdx] +
         memSize;
      Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] =
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] +
          memSize;
    }
    /* @Trace: Dem_SUD_API_00787 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00786 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      uint8 LucIdxUserDefined =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
          /* @Trace: Dem_SUD_API_00789 */
      if (DEM_NO_IDX_U8 != LucIdxUserDefined)
      {
        /* @Trace: Dem_SUD_API_00790 */
        Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdxUserDefined] =
            Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdxUserDefined] +
            memSize;

        Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] =
            Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] +
            memSize;
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00791 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00788 */
    else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00780 */
      Dem_NumOfStoredEvtMemEntryiesPerMem[LucMemSetIdx] =
          Dem_NumOfStoredEvtMemEntryiesPerMem[LucMemSetIdx] + memSize;
    }
    #endif
    /* @Trace: Dem_SUD_API_00781 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00779 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00783 */
      Dem_NumOfStoredEvtMemEntryiesMirMem[LucMemSetIdx] =
          Dem_NumOfStoredEvtMemEntryiesMirMem[LucMemSetIdx] + memSize;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_00782 */
      /* Nothing to do */
    }
  }
  #endif
}
/******************************************************************************
 * Function Name        : Dem_EvMem_ResetNumOfStoredEvtMemEntries
 *
 * Service ID           : None
 *
 * Description          : This function is to reset number of
 *                        stored event memory entries
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_ResetNumOfStoredEvtMemEntries(
  Dem_DTCOriginType DTCOrigin
)
{
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    for (uint8 LucIdx = DEM_ZERO;
               LucIdx < DEM_MAX_NUMBER_PRIMARY_MEMORY;
               LucIdx++)
    {
      /* @Trace: Dem_SUD_API_00799 */
      Dem_NumOfStoredEvtMemEntryiesPriMem[LucIdx] = DEM_ZERO;
    }
    /* @Trace: Dem_SUD_API_00800 */
    Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] = DEM_ZERO;
  }
  /* @Trace: Dem_SUD_API_00801 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00792 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    for (uint8 LucIdx = DEM_ZERO;
               LucIdx < DEM_MAX_NUMBER_USER_DEFINED_MEMORY;
               LucIdx++)
    {
      /* @Trace: Dem_SUD_API_00802 */
      Dem_NumOfStoredEvtMemEntryiesUDMem[LucIdx] = DEM_ZERO;
    }
    /* @Trace: Dem_SUD_API_00803 */
    Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] = DEM_ZERO;
  }
  #endif
  /* @Trace: Dem_SUD_API_00805 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00804 */
  else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
  {
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_MAX_NUMBER_MEMORY_SET; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_00793 */
      Dem_NumOfStoredEvtMemEntryiesMirMem[LucIdx] = DEM_ZERO;
    }
    /* @Trace: Dem_SUD_API_00794 */
    Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_MIRROR_MEMORY] = DEM_ZERO;
  }
  #endif
  /* @Trace: Dem_SUD_API_00795 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00806 */
  else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
  {
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_MAX_NUMBER_MEMORY_SET; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_00798 */
      Dem_NumOfStoredEvtMemEntryiesPerMem[LucIdx] = DEM_ZERO;
    }
    /* @Trace: Dem_SUD_API_00797 */
    Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY] = DEM_ZERO;
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00796 */
    /* Nothing to do */
  }
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetOccurrenceCounterProcessing
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Dem processing 
 *                        Occurrence Counter
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(uint8, DEM_CODE) Dem_EvMem_GetOccurrenceCounterProcessing(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
)
{
  uint8 LucReVal = DEM_PROCESS_OCCCTR_CDTC;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00808 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00809 */
      LucReVal = Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx]. \
          usDemOccurrenceCounterProcessing;
    }
  }
  /* @Trace: Dem_SUD_API_00810 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00807 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_00812 */
    uint8 LucIdxUserDefined =
        Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
    /* @Trace: Dem_SUD_API_00813 */
    if (DEM_NO_IDX_U8 != LucIdxUserDefined)
    {
      /* @Trace: Dem_SUD_API_00814 */
      LucReVal =
          Dem_GaaDemUserDefinedMemory[LucIdxUserDefined].
            usDemOccurrenceCounterProcessing;
    }
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00811 */
    /* Nothing to do */
  }
  return LucReVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_GetDemTypeOfDTCSupported
 *
 * Service ID           : None
 *
 * Description          : This function is to get Dem type of supported Dtc
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : dtcFormatType
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Client
 *                        Dem_GaaDemMemorySet
 *
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04164
 */
FUNC(boolean, DEM_CODE) Dem_EvMem_GetDemTypeOfDTCSupported(
    uint8 ClientId, Dem_DTCTranslationFormatType *dtcFormatType
)
{
  boolean LblReVal = DEM_FALSE;
  /* @Trace: Dem_SUD_API_00815 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* ClientId not found */
  /* @Trace: Dem_SUD_API_00816 */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
  if (DEM_NO_EVMEM_IDX != Dem_Client[ClientId].usDemEventMemorySetId )
  {
    /* @Trace: Dem_SUD_API_00817 */
    *dtcFormatType =
        Dem_GaaDemMemorySet[Dem_Client[ClientId].usDemEventMemorySetId].
          eDemTypeOfDTCSupported;
    LblReVal = DEM_TRUE;
  }
  #endif
  /* @Trace: Dem_SUD_API_00182 */
  return LblReVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetEventDisplacementStrategy
 *
 * Service ID           : None
 *
 * Description          : This function is to get the displacement Strategy
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
/* @Trace: Dem_SUD_MACRO_104 */
FUNC(uint8, DEM_CODE) Dem_EvMem_GetEventDisplacementStrategy(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
)
{
  uint8 LucRetVal = DEM_DISPLACEMENT_NONE;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00819 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00820 */
      LucRetVal =
          Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx].
            usDemEventDisplacementStrategy;
    }
  }
  /* @Trace: Dem_SUD_API_00821 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00818 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    uint8 LucIdxUserDefined =
        Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
    /* @Trace: Dem_SUD_API_00823 */
    if (DEM_NO_IDX_U8 != LucIdxUserDefined)
    {
      /* @Trace: Dem_SUD_API_00824 */
      LucRetVal =
          Dem_GaaDemUserDefinedMemory[LucIdxUserDefined].
            usDemEventDisplacementStrategy;
    }
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00822 */
    /* Nothing to do */
  }
  return LucRetVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetSizeOfElementEventMemory
 *
 * Service ID           : None
 *
 * Description          : This function is to get the element size of event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint16
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(uint16, DEM_CODE) Dem_EvMem_GetSizeOfElementEventMemory(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
)
{
  uint16 LusRetVal = DEM_ZERO;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00830 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00831 */
      LusRetVal =
          Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx].
            usDemMaxNumberEventEntryPrimary;
    }
  }
  /* @Trace: Dem_SUD_API_00832 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00825 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    uint8 LucIdxUserDefined = Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(
        DTCOrigin);
    /* @Trace: Dem_SUD_API_00834 */
    if (DEM_NO_IDX_U8 != LucIdxUserDefined)
    {
      /* @Trace: Dem_SUD_API_00835 */
      LusRetVal =
          Dem_GaaDemUserDefinedMemory[LucIdxUserDefined].
            usDemMaxNumberEventEntryUserDefined;
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00836 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00833 */
  else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00826 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00183 */
      LusRetVal =
          Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].usDemMirrorStopIdx -
          (uint16)Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
            usDemMirrorStartIdx;
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00827 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00837 */
  else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00829 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00184 */
      LusRetVal =
          Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
            usDemMaxNumberEventEntryPermanent;
    }
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00828 */
    /* Nothing to do */
  }
  return LusRetVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetSizeOfEventMemory
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Dem size of event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint16
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04164
 */
FUNC(uint16, DEM_CODE) Dem_EvMem_GetSizeOfEventMemory(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin
)
{
  uint16 LusRetVal = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00838 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  uint8 LucMemSetIdx = Dem_Client[ClientId].usDemEventMemorySetId;
  /* @Trace: Dem_SUD_API_00841 */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
  if (DEM_NO_EVMEM_IDX != LucMemSetIdx)
  {
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00843 */
      LusRetVal =
          Dem_GaaDemPrimaryMemory[LucMemSetIdx].usDemMaxNumberEventEntryPrimary;
    }
    /* @Trace: Dem_SUD_API_00844 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00842 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      uint8 LucIdxUserDefined = Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(
          DTCOrigin);
      /* @Trace: Dem_SUD_API_00846 */
      if (DEM_NO_IDX_U8 != LucIdxUserDefined)
      {
        /* @Trace: Dem_SUD_API_00185 */
        LusRetVal =
            Dem_GaaDemUserDefinedMemory[LucIdxUserDefined].
              usDemMaxNumberEventEntryUserDefined;
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00847 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00845 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00186 */
      LusRetVal = Dem_GaaDemMemorySet[LucMemSetIdx].usDemMirrorStopIdx
          - (uint16)Dem_GaaDemMemorySet[LucMemSetIdx].usDemMirrorStartIdx;
    }
    #endif
    /* @Trace: Dem_SUD_API_00839 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00848 */
    else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00187 */
      LusRetVal =
          Dem_GaaDemMemorySet[LucMemSetIdx].usDemMaxNumberEventEntryPermanent;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_00840 */
      /* Nothing to do */
    }
  }
  #endif
  return LusRetVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_GetStartIndexEventMemorySet
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Start Index for Event
 *                        Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
/* polyspace +2 CODE-METRICS:CALLING [Not a defect:Low] "Not a defect" */
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetStartIndexEventMemorySet(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
)
{
  Dem_NumOfEventMemoryEntryType LddReVal = DEM_NO_IDX_U8;
  /* @Trace: Dem_SUD_API_00849 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_00855 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_00857 */
        LddReVal =
            Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx].usStartIdx;
      }
      /* @Trace: Dem_SUD_API_00858 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00856 */
      else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      {
        uint8 LucUserDefinedIdx =
            Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
        /* @Trace: Dem_SUD_API_00860 */
        if (DEM_TRUE == Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
                LddEvent->ucEventMemDstIdx, LucUserDefinedIdx))
        {
          /* @Trace: Dem_SUD_API_00861 */
          LddReVal = Dem_GaaDemUserDefinedMemory[LucUserDefinedIdx].usStartIdx;
        }

      }
      #endif
      /* @Trace: Dem_SUD_API_00862 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00859 */
      else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_00851 */
        LddReVal =
            Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
              usDemPermanentStartIdx;
      }
      #endif
      /* @Trace: Dem_SUD_API_00852 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00850 */
      else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_00854 */
        LddReVal =
            Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
              usDemMirrorStartIdx;
      }
      #endif
      else
      {
        /* @Trace: Dem_SUD_API_00853 */
        /* Nothing to do */
      }
    }
  }
  return LddReVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_GetStopIndexEventMemorySet
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Stop Index for Event
 *                        Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetStopIndexEventMemorySet(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
)
{
  Dem_NumOfEventMemoryEntryType LddReVal = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00863 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_00869 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_00871 */
        LddReVal =
            Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx].usStopIdx;
      }
      /* @Trace: Dem_SUD_API_00872 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00870 */
      else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      {
        uint8 LucUserDefinedIdx =
            Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin( DTCOrigin);
        /* @Trace: Dem_SUD_API_00874 */
        if (DEM_TRUE == Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
                LddEvent->ucEventMemDstIdx, LucUserDefinedIdx))
        {
          /* @Trace: Dem_SUD_API_00875 */
          LddReVal = Dem_GaaDemUserDefinedMemory[LucUserDefinedIdx].usStopIdx;
        }

      }
      #endif
      /* @Trace: Dem_SUD_API_00876 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00873 */
      else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_00865 */
        LddReVal =
            Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].usDemMirrorStopIdx;
      }
      #endif
      /* @Trace: Dem_SUD_API_00866 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00864 */
      else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_00868 */
        LddReVal =
            ((uint16)Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
                usDemPermanentStartIdx +
            (uint16)Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].
                usDemMaxNumberEventEntryPermanent);
      }
      #endif
      else
      {
        /* @Trace: Dem_SUD_API_00867 */
        /* Nothing to do */
      }
    }
  }
  return LddReVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_IsUserDefinedBelongToEventMemorySet
 *
 * Service ID           : None
 *
 * Description          : This function is to check whether user defined belong to
 *                        an event memory set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : MemSetId, userDefinedIdx
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
  uint8 MemSetId,
  uint8 userDefinedIdx
)
{
  boolean LblReVal = DEM_FALSE;
  #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00878 */
  if (DEM_NO_IDX_U8 != userDefinedIdx)
  {
    /* @Trace: Dem_SUD_API_00879 */
    if (MemSetId ==
          Dem_GaaDemUserDefinedMemory[userDefinedIdx].usDemEventMemorySet)
    {
      /* @Trace: Dem_SUD_API_00880 */
      LblReVal = DEM_TRUE;
    }
  }
  #else
  /* @Trace: Dem_SUD_API_00877 */
  DEM_UNUSED(MemSetId);
  DEM_UNUSED(userDefinedIdx);
  #endif
  return LblReVal;
}


/******************************************************************************
 * Function Name        : Dem_EvMem_GetMILIndicator
 *
 * Service ID           : None
 *
 * Description          : This function is to get the MIL Indicator for Event
 *                        Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : memorySetID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaDemMemorySet
 *
 *****************************************************************************/
/* @Trace: Dem_SUD_MACRO_105 */
FUNC(uint8, DEM_CODE) Dem_EvMem_GetMILIndicator(uint8 memorySetID)
{
  uint8 LucRetVal = DEM_NO_IDX_U8;
  /* @Trace: Dem_SUD_API_00881 */
  if ((DEM_NO_IDX_U8 != memorySetID)
      && (memorySetID < DEM_MAX_NUMBER_MEMORY_SET))
  {
    /* @Trace: Dem_SUD_API_00882 */
    LucRetVal = Dem_GaaDemMemorySet[memorySetID].usDemMILIndicatorRef;
  }

  return LucRetVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_GetDemProtectLampIndicatorRef
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Protect Lamp Indicator
 *                        for Event Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : memorySetID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaDemMemorySet
 *
 *****************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)
FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemProtectLampIndicatorRef(uint8 memorySetID)
{
  uint8 LucRetVal = DEM_NO_IDX_U8;
  /* @Trace: Dem_SUD_API_00884 */
  if ((DEM_NO_IDX_U8 != memorySetID) &&
      (memorySetID < DEM_MAX_NUMBER_MEMORY_SET))
  {
    /* @Trace: Dem_SUD_API_00883 */
    LucRetVal = Dem_GaaDemMemorySet[memorySetID].usDemProtectLampIndicatorRef;
  }

  return LucRetVal;
}
#endif


/******************************************************************************
 * Function Name        : Dem_EvMem_GetDemAmberWarningLampIndicatorRef
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Amber Warning Lamp
 *                        Indicator for Event Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : memorySetID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaDemMemorySet
 *
 *****************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)
FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemAmberWarningLampIndicatorRef(
  uint8 memorySetID)
{
  uint8 LucRetVal = DEM_NO_IDX_U8;
  /* @Trace: Dem_SUD_API_00885 */
  if (( DEM_NO_IDX_U8 != memorySetID ) &&
      ( memorySetID < DEM_MAX_NUMBER_MEMORY_SET ))
  {
    /* @Trace: Dem_SUD_API_00886 */
    LucRetVal =
        Dem_GaaDemMemorySet[memorySetID].usDemAmberWarningLampIndicatorRef;
  }

  return LucRetVal;
}
#endif


/******************************************************************************
 * Function Name        : Dem_EvMem_GetDemRedStopLampIndicatorRef
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Red Stop Lamp
 *                        Indicator for Event Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : memorySetID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaDemMemorySet
 *
 *****************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)
FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemRedStopLampIndicatorRef(uint8 memorySetID)
{
  uint8 LucRetVal = DEM_NO_IDX_U8;
  /* @Trace: Dem_SUD_API_00887 */
  if ((DEM_NO_IDX_U8 != memorySetID ) &&
      (memorySetID < DEM_MAX_NUMBER_MEMORY_SET))
  {
    /* @Trace: Dem_SUD_API_00888 */
    LucRetVal = Dem_GaaDemMemorySet[memorySetID].usDemRedStopLampIndicatorRef;
  }

  return LucRetVal;
}
#endif
/******************************************************************************
 * Function Name        : Dem_EvMem_GetStartIndexEvMemory
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Start Index for Event
 *                        Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04164
 */
/* @Trace: Dem_SUD_MACRO_106 */
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_GetStartIndexEvMemory(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin
)
{
  Dem_NumOfEventMemoryEntryType LddReVal = DEM_NO_IDX_U8;
  /* @Trace: Dem_SUD_API_00889 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  uint8 LucMemSetIdx = Dem_Client[ClientId].usDemEventMemorySetId;
  /* @Trace: Dem_SUD_API_00894 */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
  if (DEM_NO_EVMEM_IDX != LucMemSetIdx)
  {
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00896 */
      LddReVal = Dem_GaaDemPrimaryMemory[LucMemSetIdx].usStartIdx;
    }
    /* @Trace: Dem_SUD_API_00897 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00895 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      uint8 LucUserDefinedIdx =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
          /* @Trace: Dem_SUD_API_00899 */
      if (DEM_TRUE ==
            Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
                LucMemSetIdx, LucUserDefinedIdx))
      {
        /* @Trace: Dem_SUD_API_00900 */
        LddReVal = Dem_GaaDemUserDefinedMemory[LucUserDefinedIdx].usStartIdx;
      }
    }
    #endif
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00898 */
    else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00890 */
      LddReVal = Dem_GaaDemMemorySet[LucMemSetIdx].usDemPermanentStartIdx;
    }
    #endif
    /* @Trace: Dem_SUD_API_00891 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00901 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00893 */
      LddReVal = Dem_GaaDemMemorySet[LucMemSetIdx].usDemMirrorStartIdx;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_00892 */
      /* Nothing to do */
    }
  }
  #endif

  return LddReVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetStopIndexEvMemory
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Stop Index for Event
 *                        Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04164
 */
/* @Trace: Dem_SUD_MACRO_108 */
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_GetStopIndexEvMemory(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin)
{
  Dem_NumOfEventMemoryEntryType LddReVal = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00902 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  uint8 LucMemSetIdx = Dem_Client[ClientId].usDemEventMemorySetId;
  /* @Trace: Dem_SUD_API_00909 */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
  if (DEM_NO_EVMEM_IDX != LucMemSetIdx)
  {
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00910 */
      LddReVal = (uint16)Dem_GaaDemPrimaryMemory[LucMemSetIdx].usStopIdx;
    }
    /* @Trace: Dem_SUD_API_00911 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00908 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      uint8 LucUserDefinedIdx =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin( DTCOrigin);
      /* @Trace: Dem_SUD_API_00913 */
      if (DEM_TRUE ==
            Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
                LucMemSetIdx,
                LucUserDefinedIdx))
      {
        /* @Trace: Dem_SUD_API_00914 */
        LddReVal =
            (uint16)Dem_GaaDemUserDefinedMemory[LucUserDefinedIdx].usStopIdx;
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00915 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00912 */
    else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00904 */
      LddReVal =
          (uint16)Dem_GaaDemMemorySet[LucMemSetIdx].usDemPermanentStartIdx +
          (uint16)Dem_GaaDemMemorySet[LucMemSetIdx].
                    usDemMaxNumberEventEntryPermanent;
    }
    #endif
    /* @Trace: Dem_SUD_API_00905 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00903 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00907 */
      LddReVal = Dem_GaaDemMemorySet[LucMemSetIdx].usDemMirrorStopIdx;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_00906 */
      /* Nothing to do */
    }
  }
  #endif
  return LddReVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetClientIDFromEventMemorySet
 *
 * Service ID           : None
 *
 * Description          : This function is to get the Client ID from Memory Set
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : MemSetIdx
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
/* @Trace: SRS_Diag_04164
 */
FUNC(uint8, DEM_CODE) Dem_EvMem_GetClientIDFromEventMemorySet(
  uint8 MemSetIdx
)
{
  uint8 LucReVal = DEM_NO_IDX_U8;
  for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DEM_CLIENT; LucIdx++)
  {
    /* @Trace: Dem_SUD_API_00917 */
    if (Dem_Client[LucIdx].usDemEventMemorySetId == MemSetIdx)
    {
      /* @Trace: Dem_SUD_API_00918 */
      LucReVal = Dem_Client[LucIdx].usDemClientId;
    }
  }
  /* @Trace: Dem_SUD_API_00916 */
  return LucReVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetNumOfStoredEvtMemEntries
 *
 * Service ID           : None
 *
 * Description          : This function is to get the number of stored event
 *                        memory entries
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetNumOfStoredEvtMemEntries(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
)
{
  Dem_NumOfEventMemoryEntryType LddReVal = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00919 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (EventId != DEM_NO_EVENT))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00928 */
      if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
      {
        /* @Trace: Dem_SUD_API_00929 */
        LddReVal =
            Dem_NumOfStoredEvtMemEntryiesPriMem[LddEvent->ucEventMemDstIdx];
      }
    }
    /* @Trace: Dem_SUD_API_00930 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00927 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      uint8 LucUserDefinedIdx =
          Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
      /* @Trace: Dem_SUD_API_00932 */
      if (DEM_TRUE == Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
              LddEvent->ucEventMemDstIdx, LucUserDefinedIdx))
      {
        /* @Trace: Dem_SUD_API_00933 */
        LddReVal = Dem_NumOfStoredEvtMemEntryiesUDMem[LucUserDefinedIdx];
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00934 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00931 */
    else if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00921 */
      if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
      {
        /* @Trace: Dem_SUD_API_00922 */
        LddReVal =
            Dem_NumOfStoredEvtMemEntryiesPerMem[LddEvent->ucEventMemDstIdx];
      }
    }
    #endif
    /* @Trace: Dem_SUD_API_00923 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00920 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_00925 */
      if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
      {
        /* @Trace: Dem_SUD_API_00926 */
        LddReVal =
            Dem_NumOfStoredEvtMemEntryiesMirMem[LddEvent->ucEventMemDstIdx];
      }
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_00924 */
      /* Nothing to do */
    }
  }
  return LddReVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_GetNumOfEvtMemFromDTCOrigin
 *
 * Service ID           : None
 *
 * Description          : This function is to get the number of event memory
 *                        entries from DTCOrigin
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventMemSetIdx, DTCOrigin
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
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetNumOfEvtMemFromDTCOrigin(
    uint8 EventMemSetIdx, Dem_DTCOriginType DTCOrigin)
{
  Dem_NumOfEventMemoryEntryType LddRetVal = DEM_ZERO;
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00939 */
    LddRetVal = Dem_NumOfStoredEvtMemEntryiesPriMem[EventMemSetIdx];
  }
  /* @Trace: Dem_SUD_API_00940 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00935 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    uint8 LucUserDefinedIdx =
        Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
    /* @Trace: Dem_SUD_API_00942 */
    if (DEM_NO_IDX_U8 != LucUserDefinedIdx)
    {
      /* @Trace: Dem_SUD_API_00943 */
      LddRetVal= Dem_NumOfStoredEvtMemEntryiesUDMem[LucUserDefinedIdx];
    }
  }
  #endif
  /* @Trace: Dem_SUD_API_00944 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00941 */
  else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00946 */
    LddRetVal = Dem_NumOfStoredEvtMemEntryiesMirMem[EventMemSetIdx];
  }
  #endif
  /* @Trace: Dem_SUD_API_00936 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00945 */
  else if ((DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin) ||
      (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY == DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_00938 */
    LddRetVal = Dem_NumOfStoredEvtMemEntryiesPerMem[EventMemSetIdx];
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00937 */
    /* Nothing to do */
  }
  return LddRetVal;
}


/******************************************************************************
 * Function Name        : Dem_EvMem_GetAvailableMaskFromMemSetIdx
 *
 * Service ID           : None
 *
 * Description          : This function is to get available mask from
 *                        memset index.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : MemSetId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaDemMemorySet
 *
 *****************************************************************************/
FUNC(uint8, DEM_CODE) Dem_EvMem_GetAvailableMaskFromMemSetIdx(
    uint8 MemSetId)
{
  uint8 LucRetVal = DEM_ZERO;
  /* @Trace: Dem_SUD_API_00947 */
  if (DEM_NO_EVMEM_IDX != MemSetId)
  {
    /* @Trace: Dem_SUD_API_00948 */
    LucRetVal = Dem_GaaDemMemorySet[MemSetId].usDemDtcStatusAvailabilityMask;
  }
  return LucRetVal;
}
/******************************************************************************
 * Function Name        : Dem_EvMem_GetDemEventMemoryEntryStorageTrigger
 *
 * Service ID           : None
 *
 * Description          : This function is to get the storage trigger of event
 *                        memory entries
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : uint8
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_Event
 *                        Dem_GaaDemUserDefinedMemory
 *                        Dem_GaaDemPrimaryMemory
 *
 *****************************************************************************/
FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemEventMemoryEntryStorageTrigger(
    Dem_EventIdType EventId, Dem_DTCOriginType DTCOrigin)
{
  uint8 LucRetVal = DEM_ZERO;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    /* @Trace: Dem_SUD_API_00950 */
    if (DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx)
    {
      /* @Trace: Dem_SUD_API_00951 */
      LucRetVal =
          Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx].
            usDemEventMemoryEntryStorageTrigger;
    }
  }
  /* @Trace: Dem_SUD_API_00952 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  /* @Trace: Dem_SUD_API_00949 */
  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
  {
    uint8 LucIdxUserDefined =
        Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(DTCOrigin);
    /* @Trace: Dem_SUD_API_00954 */
    if (DEM_NO_IDX_U8 != LucIdxUserDefined)
    {
      /* @Trace: Dem_SUD_API_00955 */
      LucRetVal =
          Dem_GaaDemUserDefinedMemory[LucIdxUserDefined].
            usDemEventMemoryEntryStorageTrigger;
    }
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_00953 */
    /* Nothing to do */
  }
  return LucRetVal;
}

/******************************************************************************
 * Function Name        : Dem_EvMem_ProcessEventRetention
 *
 * Service ID           : None
 *
 * Description          : This function is used to update data and
 *                        to add new event in the event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin, EventStatusByteOld
 *                        DTCStatusOld, DTC
 *
 * InOut parameter      : None
 *
 * Output Parameters    : EventDirty, StatusDirty
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_EventRelatedData
 *
 *                        Function(s) invoked :
 *                        Dem_GetConditionOfDTCRecordUpdate
 *                        DEM_CLR_UDSSTATUSBYTE
 *                        Dem_StoreObdFFClass
 *                        CallbackEventDataChanged
 *****************************************************************************/
/* @Trace: SRS_Diag_04066 SRS_Diag_04067 SRS_Diag_04068 SRS_Diag_04073
           SRS_Diag_04105 SRS_Diag_04118 SRS_Diag_04125 SRS_Diag_04127
           SRS_Diag_04131 SRS_Diag_04161 SRS_Diag_04195
 */
/* polyspace +1 CODE-METRICS:VG CODE-METRICS:CALLS CODE-METRICS:FXLN CODE-METRICS:PATH[Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ProcessEventRetention(
  Dem_EventIdType EventId, 
  Dem_DTCOriginType DTCOrigin,  
  const Dem_UdsStatusByteType EventStatusByteOld,
  #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
  const Dem_UdsStatusByteType DTCStatusOld,
  #endif
  #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
  Dem_DTCType DTC,
  #endif  
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventDirty,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  StatusDirty 
)
{        
  Std_ReturnType LddRetVal = DEM_PROCESSEVENTRETENTION_FAILED;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId-DEM_ONE];
  Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[EventId];
  Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
  /* @Trace: Dem_SUD_API_00956 */
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  /* @Trace: Dem_SUD_API_01030 */
  Dem_EventMemoryEntryPtrType LddMemEntryObd = NULL_PTR;
  #endif
  /* @Trace: Dem_SUD_API_01019 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  /* @Trace: Dem_SUD_API_01041 */
  Dem_EventMemoryEntryPtrType LddMemEntryMir = NULL_PTR;
  #endif
  
 /* @Trace: SWS_Dem_01220
  * If DemOBDDelayedDCYConfirmedAndMIL is set to TRUE, the behavior of
  * events linked to the OBD driving cycle (DemOBDDrivingCycleRef) shall
  * be changed: If the operation cycle is not qualified, status reports
  * shall be processed, except update of the confirmed status. At the
  * moment the OBD driving cycle is set to qualified, the Dem shall execute
  * computations required to reach the confirmed states of events collected
  * during the "not qualified" phase of the cycle.
  */
  /* Trace: DEM_GEN_17 */
  #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
  boolean LblObdDcyQualified = DEM_TRUE;
  if (Dem_GstOperationCycleName[LddEvent->e_OperationCycleId].ucOperationCycle ==
      DEM_OPCYC_OBD_DCY)
  {
    LblObdDcyQualified = DEM_FALSE;
    /* Trace: DEM_CYCLE_02 */
    Dem_OperationCycleStateType LddCycleQualified;
    Dem_EvMem_GetOpCycleQualifiedState(LddEvent->e_OperationCycleId, &LddCycleQualified);

    if (LddCycleQualified)
    {
      LblObdDcyQualified = DEM_TRUE;
    }
  }
  #endif

  uint8 LucDtcConfirmed;
  Dem_NumOfEventMemoryEntryType LddStartIdx =
      Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
  Dem_NumOfEventMemoryEntryType LddStopIdx =
      Dem_EvMem_GetStopIndexEventMemorySet(EventId, DTCOrigin);
  uint8 LucDispStrategy =
      Dem_EvMem_GetEventDisplacementStrategy(EventId, DTCOrigin);
  /* Already stored */
  if ((LddStartIdx <= LddMemLoc) && (LddMemLoc < LddStopIdx))
  { 
    /* @Trace: SWS_Dem_00163
     * If the Dem module is requested to support combination on storage, the
     * DTC status bit transitions of the combined DTC (refer [SWS_Dem_00441])
     * shall be used as trigger source for the allocation of the event memory
     * entry, as well as the collection or update of its related data (freeze
     * frames or extended data records).
     */
    #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    /* @Trace: Dem_SUD_API_01074 */
    LucDtcConfirmed  =
        (uint8)(DTCStatusOld & (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC);
    #else /* combination is disabled or type 2 */
    /* @Trace: Dem_SUD_API_01063 */
    LucDtcConfirmed  =
        (uint8)(EventStatusByteOld & (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC);
    #endif        

    /* Duplicated code for performance and runtime check(polyspace) */
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_01096 */
      LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
    }
    /* @Trace: SWS_Dem_01063
     * The user defined memory shall have the same behavior as the
     * primary memory(event retention, event prioritization, aging,
     * displacement).
     */
    /* @Trace: Dem_SUD_API_01012 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01085 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_01016 */
      LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_01015 */
      /* Do nothing */
    }

    /* Handling for MIRROR Memory*/
    /* @Trace: Dem_SUD_API_00957 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01001 */
    if ( DEM_TWO == LddEvent->ucNumOfDestSelected )
    {
      uint16 LusStartMirIdx =
          Dem_EvMem_GetStartIndexEventMemorySet(
              EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY);
      uint16 LusStopMirIdx =
          Dem_EvMem_GetStopIndexEventMemorySet(
              EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY);
      uint16 LusMirMemFreeId = DEM_MAX_NUMBER_EVENT_ENTRY_MIR;

      /* @Trace: Dem_SUD_API_00990 */
      for (Dem_NumOfEventMemoryEntryType LddMemLocMirId = LusStartMirIdx;
                                         LddMemLocMirId < LusStopMirIdx;
                                         LddMemLocMirId++)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* @Trace: Dem_SUD_API_00979 */
        if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMemLocMirId)
        {
          /* @Trace: Dem_SUD_API_00968 */
          if (EventId == Dem_MirrorEventMemory[LddMemLocMirId].EventIdRef)
          {
            /* @Trace: Dem_SUD_API_00188 */
            LddMemEntryMir = &Dem_MirrorEventMemory[LddMemLocMirId];
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            break;
          }
          else
          {
             /* @Trace: Dem_SUD_API_01284 */
            if (LusMirMemFreeId == DEM_MAX_NUMBER_EVENT_ENTRY_MIR)
            {
              /* @Trace: Dem_SUD_API_01285 */
              if (DEM_NO_EVENT ==
              Dem_MirrorEventMemory[LddMemLocMirId].EventIdRef)
              {
                /* @Trace: Dem_SUD_API_01286 */
                LusMirMemFreeId = LddMemLocMirId;
              }
            }
          }
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }

      /* @Trace: Dem_SUD_API_01289 */
      /* not stored in mirror memory yet, look for free space*/
      if(LddMemEntryMir == NULL_PTR)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* @Trace: Dem_SUD_API_01287 */
        if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LusMirMemFreeId)
        {
          /* @Trace: Dem_SUD_API_01288 */
          LddMemEntryMir = &Dem_MirrorEventMemory[LusMirMemFreeId];
          LddMemEntryMir->EventIdRef = EventId; /* Set EventId */
          Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
            EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY, DEM_ONE);
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
    }
    #endif

    /* @Trace: Dem_SUD_API_01017 */
    if (NULL_PTR != LddMemEntry) /* Always true */
    {
      /* @Trace: Dem_SUD_API_01018 */
      if (DEM_ZERO != LddMemEntry->AgingCycleCounter)
      {
        /* @Trace: Dem_SUD_API_01020 */
        LddMemEntry->AgingCycleCounter = DEM_ZERO;/* Init aging cycle counter */
        *EventDirty = DEM_TRUE;
      }
      /* @Trace: SWS_Dem_01244
       * If Dem_SetEventFailureCycleCounterThreshold is called and the
       * corresponding event is already stored in event memory and the new
       * failure threshold is less or equal to the current failure counter,
       * then the event will get confirmed. This implies, that the event
       * related data will also be updated according their defined triggers.
       */

      /* @Trace: SWS_Dem_01245
       * If Dem_SetEventFailureCycleCounterThreshold is called and the
       * corresponding event is already stored in event memory and already
       * confirmed, the event memory entry and confirmation status will remain,
       * even if the new threshold is greater than the failure counter. Also
       * after new error status reports, the confirmation status will remain.
       */
      /* @Trace: Dem_SUD_API_01021 */
      #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
      /* @Trace: Dem_SUD_API_01022 */
      if ((Dem_GaaEventFailureThreshold[EventId] > DEM_ONE) &&
          (DEM_ZERO == LucDtcConfirmed))
      {               
        #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
        /* @Trace: Dem_SUD_API_01024 */
        uint8 LucTestFailedThisOpCycle =
            (uint8)(DTCStatusOld &
            (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC);
        #else /* combination is disabled or type 2 */
        /* @Trace: Dem_SUD_API_01023 */
        uint8 LucTestFailedThisOpCycle =
            (uint8)(EventStatusByteOld &
            (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC);
        #endif        
        /* @Trace: SWS_Dem_00391
         * The Dem module shall implement the status bit transition for UDS
         * status bit 3 according to figure 7.20.
         *
         * Dem_SetEventStatus[(EventStatus = DEM_EVENT_STATUS_FAILED) &&
         * (testFailedThisOperationCycle == 0) &&
         * ((failure counter+1) >= DemEventFailureCycleCounterThreshold)] */
        /* @Trace: Dem_SUD_API_01025 */
        if (DEM_ZERO == LucTestFailedThisOpCycle)
        {
          /* @Trace: Dem_SUD_API_01026 */
          if (LddMemEntry->FailureCycleCounter < (uint8)0xFF)
          {
            /* Trace: DEM_GEN_17 */
            #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
            if(LblObdDcyQualified)
            #endif
            {
              #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
              /* Trace: DEM_COMB_03 */
              #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
              Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
              boolean LblCbDtcFailureCntIncFlag = DEM_FALSE;
              if (NULL_PTR != LddCbDTC)
              {
                Dem_NumOfEventIdType LddStartPos =
                    Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
                const Dem_NumOfEventIdType LddEndPos =
                    Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
                while (LddStartPos < LddEndPos)
                {
                  Dem_EventIdType LddTmpEvId =
                      Dem_ListOfCombinedEvents[LddStartPos];

                  if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(LddTmpEvId, DEM_UDS_STATUS_TFTOC))
                        || (DEM_TRUE == Dem_EvIsUdsProcStateTriggered( LddTmpEvId,
                                              DEM_UDSPROCSTATE_TRANSITION_BIT_1)))
                  {
                    /* Exclude Itself */
                    if (LddTmpEvId != EventId)
                    {
                      LblCbDtcFailureCntIncFlag = DEM_TRUE;
                      break;
                    }
                  }                  
                  ++LddStartPos;
                }
              }

              if (LblCbDtcFailureCntIncFlag == DEM_FALSE)
              #endif
              #endif
              {

                /* @Trace: Dem_SUD_API_01027 */
                ++LddMemEntry->FailureCycleCounter;
                *EventDirty = DEM_TRUE;
              }
            }

          }
          /* EventFailureThreshold is more than 2 or equal to 2 */
          /* @Trace: Dem_SUD_API_01028 */
          if (LddMemEntry->FailureCycleCounter >=
                Dem_GaaEventFailureThreshold[EventId])
          {
            /* @Trace: SWS_Dem_01051
             * For combination on storage, the event which allocated (or
             * reallocate) the event memory entry shall be the only event,
             * which has the confirmed bit set. */
            /* @Trace: Dem_SUD_API_01029 */
            if ((DEM_NO_EVENT != LddMemEntry->EventIdRef) &&
                (LddMemEntry->EventIdRef <= DEM_NUMBER_OF_EVENTS))
            {
              /* @Trace: Dem_SUD_API_01031 */
              if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(
                    LddMemEntry->EventIdRef, DEM_UDS_STATUS_CDTC))
              {
                SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                Dem_EvSetUdsProcState(
                    LddMemEntry->EventIdRef, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
                SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              }
            }
            
            LddMemEntry->FailureCycleCounter = DEM_ZERO;
            /* @Trace: Dem_SUD_API_01032 */
            #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
            uint8 LucCliendIdx =
                Dem_EvMem_GetClientIDFromEventMemorySet(
                    LddEvent->ucEventMemDstIdx);
            /* @Trace: Dem_SUD_API_01033 */
            if (DEM_NO_IDX_U8 != LucCliendIdx)
            {
              /* @Trace: Dem_SUD_API_01034 */
              *StatusDirty |=
                  Dem_EvMem_SetFirstLastConfirmedDTC(
                      LucCliendIdx, DTCOrigin, DTC);
            }
            #endif

            *EventDirty = DEM_TRUE;
            
            LucDtcConfirmed = (uint8)DEM_TRUE;
          }  
        }
      } 
      #endif


      /* @Trace: SWS_Dem_00772
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this counter is
       * stored in event memory the counter shall initialized to zero.*/
      /* @Trace: Dem_SUD_API_01035 */
      #if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO) && \
           (DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON))
      /* @Trace: Dem_SUD_API_01036 */
      if ((DEM_DEBOUNCE_COUNTER_BASED ==
            DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA) &&
          (Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry] >=
              Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry].
                ssDemCounterFailedThreshold)))
      {
        /* @Trace: Dem_SUD_API_01037 */
        LddMemEntry->cyclesSinLastFailedCounter = DEM_ZERO;
      }
      #endif
      /* @Trace: SWS_Dem_00011
       * The Dem module shall provide an occurrence counter per event memory
       * entry.
       */

      /* @Trace: SWS_Dem_00625
       * The Dem module shall not increment the event-specific occurrence
       * counter anymore, if it has reached its maximum value (255, refer to
       * [SWS_Dem_00471]).
       */
      /* @Trace: Dem_SUD_API_01038 */
      if (LddMemEntry->EventOccurrenceCounter  < (uint8)DEM_OCC_MAX)
      {
        /* @Trace: SWS_Dem_00524
         * If the configuration parameter DemOccurrenceCounterProcessing (refer
         * to DemGeneral) is DEM_PROCESS_OCCCTR_TF , the Dem module shall
         * increment the occurrence counter by one, triggered by each event
         * status bit 0 (TestFailed) transition from 0 to 1, if the related
         * event is already stored in the event memory.
         */
        /* @Trace: SWS_Dem_00580
         * If the configuration parameter DemOccurrenceCounterProcessing (refer
         * to DemGeneral) is DEM_PROCESS_OCCCTR_CDTC, the Dem module shall
         * increment the occurrence counter by one, triggered by each UDS DTC
         * status bit 0 (TestFailed) transition from 0 to 1, if the related
         * event is already stored in the event memory and the event Status bit
         * 3 (ConfirmedDTC) is equal to 1 (refer to chapter 0).
         */
        uint8 LucDemOccCntProcess =
            Dem_EvMem_GetOccurrenceCounterProcessing( EventId, DTCOrigin);

        if (((DEM_PROCESS_OCCCTR_CDTC == LucDemOccCntProcess) ||
            (DEM_PROCESS_OCCCTR_TF == LucDemOccCntProcess)) &&
            (DEM_ZERO != LucDtcConfirmed))
        {
          /* @Trace: Dem_SUD_API_01039 */
          ++LddMemEntry->EventOccurrenceCounter;
          *EventDirty = DEM_TRUE;
        }
        else
        {
          /* @Trace: Dem_SUD_API_01040 */
          /* Do nothing */
        }
      }      
      /*************************************************************************
       *             Check WarningIndicatorOnCondition                         *
       * [1] @RfC 63657, use  DemOperationCycleRef                             *
       * [2] @SWS_Dem_01052, @SWS_Dem_01051 : Combined DTC's ComfirmedDTC = 1  *
       * [3] New Event or TFTOC changed from 0 to 1 (threshold != 0)           *
       * [4] Indicator Failure Counter should be increased by 1 on each        *
       *     operation cycle                                                   *
       ************************************************************************/
      /* @Trace: SWS_Dem_01052
       * For combination on storage, an event that cannot set the confirmed bit
       * due to [SWS_Dem_01051] shall still generate warningIndicatorOnCriteria
       * according to [SWS_Dem_00501]. */
      /* @Trace: Dem_SUD_API_01042 */
      if (LddEvent->ucNumberofIndicator > DEM_ZERO)
      {
        /* Trace: DEM_GEN_17 */
        #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
        if(LblObdDcyQualified)
        #endif
        {
          Dem_EventIdType LddCbDtcEventId = EventId;
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          /* Trace: DEM_COMB_03 */
          #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
          Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
          boolean LblCbDtcIndicatorIncFlag = DEM_FALSE;
          if (NULL_PTR != LddCbDTC)
          {
            Dem_NumOfEventIdType LddStartPos =
                Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
            const Dem_NumOfEventIdType LddEndPos =
                Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);


            while (LddStartPos < LddEndPos)
            {
              Dem_EventIdType LddTmpEvId =
                  Dem_ListOfCombinedEvents[LddStartPos];
              if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(LddTmpEvId, DEM_UDS_STATUS_TFTOC))
                    || (DEM_TRUE == Dem_EvIsUdsProcStateTriggered( LddTmpEvId,
                                          DEM_UDSPROCSTATE_TRANSITION_BIT_1)))
              {
                /* Exclude Itself */
                if (LddTmpEvId != EventId)
                {
                  LblCbDtcIndicatorIncFlag = DEM_TRUE;
                  break;
                }
              }                  
              ++LddStartPos;
            }
          }

          if (LddMemEntry->EventIdRef != EventId)
          {
            LddCbDtcEventId = LddMemEntry->EventIdRef;
          }

          if (LblCbDtcIndicatorIncFlag == DEM_FALSE)
          #endif
          #endif
          {
            /* @Trace: Dem_SUD_API_01043 */
            *StatusDirty |= Dem_ActivateIndicatorOnEventFailed(
                LddCbDtcEventId,
                (uint8)(EventStatusByteOld &
                    (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC));
           }
        }

      }
      /* @Trace: Dem_SUD_API_01044 */
      #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
      /* @Trace: Dem_SUD_API_01045 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      {
        /* @Trace: Dem_SUD_API_01047 */
        if (Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] !=
              LddMemEntry->TimeStamp)
        {
          /* @Trace: Dem_SUD_API_00219 */
          LddMemEntry->TimeStamp = Dem_EvMem_FindNewTimeStamp(
              EventId, DTCOrigin);
        }
      }
      else
      /* @Trace: Dem_SUD_API_01046 */
      #endif
      if (Dem_MaxTimeStamp[DTCOrigin] != LddMemEntry->TimeStamp)
      {
        /* @Trace: Dem_SUD_API_01049 */
        LddMemEntry->TimeStamp = Dem_EvMem_FindNewTimeStamp(EventId, DTCOrigin);
      }
      else
      {
        /* @Trace: Dem_SUD_API_01048 */
        /* Nothing to do */
      }
      #endif
      /* @Trace: Dem_SUD_API_01050 */
      #if (DEM_J1939_SUPPORT == STD_ON)
      /* @Trace: SWS_Dem_00787
       * If an 'stored event' gets re-qualified as failed (UDS DTC status bit 0
       * changes from 0 to 1) and a respective event memory entry exists, the
       * Dem module shall update the chronological order of the event storage
       * by setting the particular event as most recent event memory entry. */
      /* @Trace: Dem_SUD_API_01051 */
      Dem_EvMem_DelChronologicalOrder(DTCOrigin, LddMemLoc);
      Dem_EvMem_AddNewChronologicalOrder(DTCOrigin, LddMemLoc);
      #endif

      /* Handling for MIRROR Memory*/
      /* @Trace: Dem_SUD_API_01053 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_01054 */
      if ((LddEvent->ucNumOfDestSelected == DEM_TWO ) &&
          (LddMemEntryMir != NULL_PTR))
      {
        /* @Trace: Dem_SUD_API_00220 */
        (void)Dem_EvMem_CopyMemoryEntries(LddMemEntryMir, LddMemEntry);
      }
      #endif

      LddRetVal = DEM_PROCESSEVENTRETENTION_OK;
    }
  } 
  else /** New Event */
  {
    /* @Trace: Dem_SUD_API_01052 */
     /*******************************************************************
     *                      ConfirmedDTC bit = 1                       *
     * [1] @ISO 14229:2013, 373p, Figure D.9                           *
     * [2] @RfC 59420, Remove the DemEventFailureCycleRef              *
     * [3] new event or TestFailedThisOperationCycle from 0 to 1       *
     *******************************************************************/
    /* @Trace: Dem_SUD_API_01055 */
    #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
    /*
     * Confirmation threshold [ "Blank" == one ]
     *
     * The ConfirmedDTC bit is set (change from 0 to 1) at the same time as the
     * pendingDTC bit because this example is for a non emissions-related server
     * /ECU with a confirmation threshold of 1.
     */
    /* @Trace: Dem_SUD_API_01056 */
    if (Dem_GaaEventFailureThreshold[EventId] <= DEM_ONE)
    #endif
    {
      /* @Trace: Dem_SUD_API_01057 */
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC))
      {
        /* @Trace: Dem_SUD_API_01058 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* Trace: DEM_GEN_17 */
        #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
        if(LblObdDcyQualified)
        #endif
        {
          Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      /* polyspace+1 MISRA2012:D4.4 [Justified:Low] "Comment for explain aspects of the code." */
      /* dtcConfirmed = DEM_TRUE; */
    }

    boolean LblIsRetention = DEM_FALSE;
    Dem_NumOfEventMemoryEntryType LddNumOfMemEntries =
        Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
    /* get the number of stored event memory entries */
    Dem_NumOfEventMemoryEntryType LddNumOfStoredEvtMemEntries =
        Dem_EvMem_GetNumOfStoredEvtMemEntries(EventId ,DTCOrigin);
    /* Duplicated code for performance and runtime check(polyspace) */
    /* No need the memory protection */

    uint8 LucDemMemStrTrg =
        Dem_EvMem_GetDemEventMemoryEntryStorageTrigger(EventId, DTCOrigin);
    boolean LblIsBit0GetTransit =
        Dem_EvIsUdsProcStateTriggered(
            EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_0);
    boolean LblIsBit2GetTransit =
        Dem_EvIsUdsProcStateTriggered(
            EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_2);
    boolean LblIsBit3GetTransit =
        Dem_EvIsUdsProcStateTriggered(
            EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
    /* @Trace: SWS_Dem_00783, SWS_Dem_00784, SWS_Dem_00922
     */
    /* @Trace: Dem_SUD_API_01059 */
    if ((( /* UDS status bit 0 from 0 --> 1 */
          (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)) &&
          (DEM_TRUE == LblIsBit0GetTransit)) ||
         ( /* UDS status bit 2 from 0 --> 1*/
          (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_PDTC)) &&
          (DEM_TRUE == LblIsBit2GetTransit)) ||
         /* (UDS status bit 2 is 1) and  (UDS status bit 0 from 0 --> 1) */
         ((DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_PDTC)) &&
         ((DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)) &&
          (DEM_TRUE == LblIsBit0GetTransit)))) &&
         ((DEM_TRIGGER_ON_TEST_FAILED == LucDemMemStrTrg) ||
          (DEM_TRIGGER_ON_FDC_THRESHOLD == LucDemMemStrTrg)))
    {
      /* @Trace: Dem_SUD_API_01060 */
      LblIsRetention = DEM_TRUE;
    }

    /* @Trace: SWS_Dem_00785, SWS_Dem_00923
     */
    /* @Trace: Dem_SUD_API_01061 */
    if ((
         (/* UDS status bit 3 from 0 --> 1 */
          (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC)) &&
          (DEM_TRUE == LblIsBit3GetTransit)
         ) ||
         (  /* (UDS status bit 3 is 1) and (UDS status bit 0 from 0 --> 1)
             * and (DemResetConfirmedBitOnOverflow is set to false)*/
         (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC)) &&
         ((DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)) &&
         (DEM_TRUE == LblIsBit0GetTransit)) &&
         (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == DEM_FALSE))
        ) &&
        ((DEM_TRIGGER_ON_CONFIRMED == LucDemMemStrTrg ) ||
         (DEM_TRIGGER_ON_TEST_FAILED == LucDemMemStrTrg ) ||
         (DEM_TRIGGER_ON_FDC_THRESHOLD == LucDemMemStrTrg )))
    {
      /* @Trace: Dem_SUD_API_01062 */
      LblIsRetention = DEM_TRUE;
    }

    /* @Trace: SWS_Dem_00786 */
    /* @Trace: Dem_SUD_API_01064 */
    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01065 */
    sint16 LssDemCounterBasedFdcThresholdStorageValue =
        Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry].
          ssDemCounterBasedFdcThresholdStorageValue;
    /* @Trace: Dem_SUD_API_01067 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
    if (((DEM_DEBOUNCE_COUNTER_BASED ==
            DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA)) &&
         (Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry] >=
             LssDemCounterBasedFdcThresholdStorageValue))&&
    (DEM_TRIGGER_ON_FDC_THRESHOLD == LucDemMemStrTrg))
    {
       /* @Trace: Dem_SUD_API_01068 */
      LblIsRetention = DEM_TRUE;
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
    #endif
    /* @Trace: Dem_SUD_API_01069 */
    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01066 */
    P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
        NULL_PTR;
    /* @Trace: Dem_SUD_API_01070 */
    if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > LddEvent->ucIndexOfDebounceAry)
    {
      /* @Trace: Dem_SUD_API_01071 */
      LddTimerStatus =
          Dem_GetDebounceTimerStatus(LddEvent->ucIndexOfDebounceAry);
    }
    /* @Trace: Dem_SUD_API_01072 */
    if (NULL_PTR != LddTimerStatus)
    {
      /* @Trace: Dem_SUD_API_01073 */
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
      /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
      if (((DEM_DEBOUNCE_TIME_BASED ==
              DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA)) &&
           (LddTimerStatus->tds_Counter <=
                  ((Dem_GaaPreDebounceTimeBased[LddEvent->ucIndexOfDebounceAry].
                      ulDemTimeBasedFdcThresholdStorageValue)/(Dem_Task_Time))))
          && (DEM_TRIGGER_ON_FDC_THRESHOLD == LucDemMemStrTrg))
      {
        /* @Trace: Dem_SUD_API_01075 */
        LblIsRetention = DEM_TRUE;
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
    }
    #endif

    /* @Trace: SWS_Dem_00798
     * If the FreezeFrame uses dedicated, configured record numbers (refer to
     * DemFreezeFrameRecNumClassRef) and no event memory entry exists, the Dem
     * module shall first try to allocate an event memory entry as described in
     * [SWS_Dem_00783], [SWS_Dem_00784], [SWS_Dem_00785] and [SWS_Dem_00786].
     * Afterwards requirement [SWS_Dem_00797] applies.
     */

    /* @Trace: SWS_Dem_00810
     * If no event memory entry exists, the Dem module shall first try to
     * allocate an event memory entry as described in [SWS_Dem_00783],
     * [SWS_Dem_00784], [SWS_Dem_00785] and [SWS_Dem_00786]. Afterwards
     * requirement [SWS_Dem_00809] applies.
     */
    /* @Trace: Dem_SUD_API_01076 */
    if (DEM_TRUE == LblIsRetention)
    {
      if (LddNumOfStoredEvtMemEntries < LddNumOfMemEntries)
      {
        if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
        {
          /* @Trace: Dem_SUD_API_01079 */
          for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            if (DEM_NO_EVENT == Dem_PrimaryEventMemory[LddMemLoc].EventIdRef)
            {
              /* @Trace: Dem_SUD_API_00998 */
              /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
              if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLoc)
              {
                /* @Trace: Dem_SUD_API_00999 */
                LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
                LddMemEntry->EventIdRef = EventId; /* Set EventId */
              }
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              break;
            }
            else
            {
              /* @Trace: Dem_SUD_API_00997 */
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }
          }

          /* @Trace: Dem_SUD_API_01080 */
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) LddEvData =
              NULL_PTR;
          /* @Trace: Dem_SUD_API_01081 */
          /* @Trace: Dem_SUD_MACRO_092 */
          if (DEM_NUM_OF_EVENTRELATEDDATA > LddEvent->e_PointToData)
          {
            LddEvData = &Dem_EventRelatedData[LddEvent->e_PointToData];
          }

          /* Allocation for OBD*/
          /* @Trace: Dem_SUD_API_01082 */
          if (NULL_PTR != LddEvData)
          {
            /* @Trace: Dem_SUD_API_01083 */
            if ((LddEvData->OBDClassPos != NULL_PTR) &&
               (DEM_NO_EVMEM_ENTRY == Dem_ObdMemoryId ))
            {
              /* @Trace: Dem_SUD_API_01084 */
              for (Dem_NumOfEventMemoryEntryType LddMemLocObd = LddStartIdx;
                                                 LddMemLocObd < LddStopIdx;
                                                 LddMemLocObd++)
              {
                 /* @Trace: Dem_SUD_API_01088 */
                /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
                if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLocObd)
                {
                  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                  if (DEM_NO_EVENT ==
                        Dem_PrimaryEventMemory[LddMemLocObd].EventIdRef)
                  {
                    /* @Trace: Dem_SUD_API_01090 */
                    LddMemEntryObd = &Dem_PrimaryEventMemory[LddMemLocObd];
                    LddMemEntryObd->EventIdRef = EventId; /* Set EventId */
                    Dem_ObdMemoryId = (uint8)LddMemLocObd;
                    Dem_EventStatusNvRamData.ObdMemoryId = Dem_ObdMemoryId;
                    Dem_EvMem_SetNonVolatieDataStatus(
                        DEM_NVDATA_ALL_EVENT_STATUS_ID,
                        DEM_EVMEM_STATUS_DIRTY_NVM);
                    Dem_EvMem_TriggerWriteAllBlocks();
                    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

                    break;
                  }
                  else
                  {
                    /* @Trace: Dem_SUD_API_01089 */
                    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                  }
                }
              }
              /* @Trace: Dem_SUD_API_01086 */
              if (NULL_PTR != LddMemEntryObd)
              {
                /* @Trace: Dem_SUD_API_01087 */
                Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
                    EventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_ONE);
              }
            }
          }
          #endif
        }
        /* @Trace: Dem_SUD_API_01091 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
        /* @Trace: Dem_SUD_API_01078 */
        else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
        {
          /* @Trace: Dem_SUD_API_01093 */
          for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            if (DEM_NO_EVENT ==
                  Dem_UserDefinedEventMemory[LddMemLoc].EventIdRef)
            {
              /* @Trace: Dem_SUD_API_01094 */
              if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > LddMemLoc)
              {
                /* @Trace: Dem_SUD_API_01095 */
                LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
                LddMemEntry->EventIdRef = EventId; /* Set EventId */
              }
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              break;
            }
            else
            {
              /* @Trace: Dem_SUD_API_00221 */
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }
          }
        }
        #endif
        else
        {
          /* @Trace: Dem_SUD_API_01092 */
          /* retVal = DEM_PROCESSEVENTRETENTION_FAILED; */
        }

        /* Handling for MIRROR Memory*/
        /* @Trace: Dem_SUD_API_01097 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
        /* @Trace: Dem_SUD_API_01098 */
        if (DEM_TWO == LddEvent->ucNumOfDestSelected )
        {
          Dem_NumOfEventMemoryEntryType LddStartMirIdx =
              Dem_EvMem_GetStartIndexEventMemorySet(
                  EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY);
          Dem_NumOfEventMemoryEntryType LddStopMirIdx =
              Dem_EvMem_GetStopIndexEventMemorySet(
                  EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY);
          Dem_NumOfEventMemoryEntryType LddMemLocMirId =
              Dem_EvMem_FindMirMemLoc(EventId);
          if ( DEM_NO_EVMEM_ENTRY == LddMemLocMirId)
          {
            /* @Trace: Dem_SUD_API_01101 */
            for (LddMemLocMirId = LddStartMirIdx;
                 LddMemLocMirId < LddStopMirIdx;
                 LddMemLocMirId++)
            {
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              if (DEM_NO_EVENT ==
                    Dem_MirrorEventMemory[LddMemLocMirId].EventIdRef)
              {
                /* @Trace: Dem_SUD_API_01103 */
                if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMemLocMirId)
                {
                  /* @Trace: Dem_SUD_API_01104 */
                  LddMemEntryMir = &Dem_MirrorEventMemory[LddMemLocMirId];
                  LddMemEntryMir->EventIdRef = EventId; /* Set EventId */
                  Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
                      EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY, DEM_ONE);
                }
                SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                break;
              }
              else
              {
                /* @Trace: Dem_SUD_API_01102 */
                SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              }
            }
          }
          else
          {
            /* @Trace: Dem_SUD_API_01099 */
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            /* @Trace: Dem_SUD_API_01100 */
            if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMemLocMirId)
            {
              /* @Trace: Dem_SUD_API_00222 */
              LddMemEntryMir = &Dem_MirrorEventMemory[LddMemLocMirId];
            }
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
        }
        #endif
      }
      /* event memory is full */

      /* @Trace: SWS_Dem_00400
       * If the event retention want to allocate a new event memory entry and
       * there is no free event memory entry available, the Dem module shall
       * check according [SWS_Dem_00406] for allocated event memory entries to
       * be displaced by the new event memory entry.
       */
      /* @Trace: SWS_Dem_00401
       * The Dem module provides the configuration parameter
       * DemEventDisplacementStrategy (refer to DemPrimaryMemory or
       * DemUserDefinedMemory) defining whether the existing event memory entry
       * can be displaced or not.
       */
      /* @Trace: SWS_Dem_00402
       * If event displacement is disabled (DemEventDisplacementStrategy in
       * DemPrimaryMemory or DemUserDefinedMemory selects DEM_DISPLACEMENT_NONE)
       * , the Dem module shall not displace existing event memory entries if
       * the event memory is full.
       */
      /* @Trace: SWS_Dem_00542
       * For combination on retrieval, the displacement algorithm for each event
       * of a combined DTC shall be treated individually (refer to
       * [SWS_Dem_00408]).
       */
      /* @Trace: Dem_SUD_API_01077 */
      else if (DEM_DISPLACEMENT_NONE != LucDispStrategy)
      {
        LddMemLoc = Dem_EvMem_FindEntryWithLowestPriority(
            EventId, LddEvent->ucEventPriority, DTCOrigin, LucDispStrategy);
        Dem_NumOfEventMemoryEntryType LddSizeOfMem =
                      Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
        Dem_NumOfEventMemoryEntryType LddStartIndexDisp =
                      Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
        LddSizeOfMem = LddSizeOfMem + LddStartIndexDisp;
         /* @Trace: Dem_SUD_API_01002 */
        if (LddMemLoc < LddSizeOfMem)
        {
          /* Duplicated code for performance and runtime check(polyspace) */
          if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
          {
            /* @Trace: Dem_SUD_API_01004 */
            if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLoc)
            {
              /* @Trace: Dem_SUD_API_01005 */
              LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
            }
          }
          /* @Trace: SWS_Dem_01063
           * The user defined memory shall have the same behavior as the
           * primary memory(event retention, event prioritization, aging,
           * displacement).
           */
          /* @Trace: Dem_SUD_API_01006 */
          #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
          /* @Trace: Dem_SUD_API_01003 */
          else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID (DTCOrigin))
          {
            /* @Trace: Dem_SUD_API_01008 */
            if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > LddMemLoc)
            {
              /* @Trace: Dem_SUD_API_00223 */
              LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
            }
          }
          #endif
          else
          {
            /* @Trace: Dem_SUD_API_01007 */
            /* Do nothing */
          }
        }

        /* Handling for MIRROR Memory*/
        /* @Trace: Dem_SUD_API_01009 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
        /* @Trace: Dem_SUD_API_01010 */
        if ( DEM_TWO == LddEvent->ucNumOfDestSelected  )
        {
          Dem_NumOfEventMemoryEntryType LddMirMemLoc =
               Dem_EvMem_FindEntryWithLowestPriority(
                   EventId, LddEvent->ucEventPriority,
                 DEM_DTC_ORIGIN_MIRROR_MEMORY, LucDispStrategy);
          LddSizeOfMem =
              Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
          Dem_NumOfEventMemoryEntryType LddStartIndexMir =
               Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
          LddSizeOfMem = LddSizeOfMem + LddStartIndexMir;
          /* @Trace: Dem_SUD_API_01011 */
          if (LddMirMemLoc < LddSizeOfMem)
          {
            /* @Trace: Dem_SUD_API_01013 */
            if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMirMemLoc)
            {
              /* @Trace: Dem_SUD_API_01014 */
              LddMemEntryMir = &Dem_MirrorEventMemory[LddMirMemLoc];
            }
          }
        }
        #endif
      }
      else
      {
        /* @Trace: Dem_SUD_API_01000 */
        /* Nothing to do */
      }
    }

    /* New Entry */
    if (NULL_PTR != LddMemEntry)
    {
      /* @Trace: SWS_Dem_00780
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this counter is not
       * stored in event memory and there are available event memory entry, new
       * entry shall be allocated and the counter shall be started and
       * initialized to zero.
       * */
      /* @Trace: SWS_Dem_00776
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this
       * counter is not stored in event memory and there are available event
       * memory entry, new entry shall be allocated and the counter shall be
       * started and initialized to zero.*/
      /* @Trace: SWS_Dem_00771
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this counter is not
       *  stored in event memory and there are available event memory entry,
       *  new entry shall be allocated and the counter shall be started and
       *  initialized to zero.*/
      /* @Trace: Dem_SUD_API_01106 */
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00958 */
      if (((DEM_DEBOUNCE_COUNTER_BASED ==
              DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA)) &&
           (Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry] >=
               Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry].
                 ssDemCounterFailedThreshold)))
      {
        /* @Trace: Dem_SUD_API_00959 */
        #if ((DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON))
        /* @Trace: Dem_SUD_API_00960 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        LddMemEntry->cyclesSinLastFailedCounter = DEM_ZERO;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        #endif
        /* @Trace: Dem_SUD_API_00961 */
        #if (DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
        /* @Trace: Dem_SUD_API_00962 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        LddMemEntry->cyclesSinFirstFailedCounter = DEM_ZERO;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        #endif
        /* @Trace: Dem_SUD_API_00963 */
        #if (DEM_INTERNAL_DATA_FAILED_CYCLES == STD_ON)
        /* @Trace: Dem_SUD_API_00964 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        LddMemEntry->failedCyclesCounter = DEM_ZERO;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        #endif
      }
      #endif

      /* @Trace: Dem_SUD_API_00965 */
      #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
      LddMemEntry->TimeStamp = Dem_EvMem_FindNewTimeStamp(EventId, DTCOrigin);
      /* @Trace: Dem_SUD_API_00966 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      {
        /* @Trace: Dem_SUD_API_00969 */
        if (Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] <
              LddMemEntry->TimeStamp)
        {
          /* @Trace: Dem_SUD_API_00970 */
          Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] =
              LddMemEntry->TimeStamp;
        }
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_00967 */
        /* @Trace: Dem_SUD_API_00971 */
        if (Dem_MaxTimeStamp[DTCOrigin] < LddMemEntry->TimeStamp)
        {
          /* @Trace: Dem_SUD_API_00224 */
          Dem_MaxTimeStamp[DTCOrigin] = LddMemEntry->TimeStamp;
        }
      }
      #endif
      /* @Trace: Dem_SUD_API_00972 */
      #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
      {
        /* @Trace: Dem_SUD_API_00974 */
        for (uint16 LusIdx = DEM_ZERO;
                    LusIdx < DEM_MAX_NUM_EVENTS_PER_DTC;
                    LusIdx++)
        {
          /* @Trace: Dem_SUD_API_00973 */
          LddMemEntry->EventStatuByte[LusIdx] = DEM_ZERO;
        }   
      }
      #endif      
      
      /* @Trace: SWS_Dem_00523
       * The Dem module shall initialize the occurrence counter with the value
       * one if the related event is entered in the respective event memory. */
      LddMemEntry->EventOccurrenceCounter = DEM_ONE;
      /* Initialize the failure counter related ConfirmedDTC */
      /* @Trace: Dem_SUD_API_00975 */
      #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
      /* @Trace: Dem_SUD_API_00976 */
      LddMemEntry->FailureCycleCounter = DEM_ZERO;
      #endif
      LddMemEntry->AgingCycleCounter = DEM_ZERO;
      /* @Trace: Dem_SUD_API_00977 */
      #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
      {
        uint32 LulIdx;
        /* @Trace: Dem_SUD_API_00980 */
        for (LulIdx = DEM_ZERO; LulIdx < DEM_SIZE_OF_EVENT_DATA; LulIdx++)
        {
          /* @Trace: Dem_SUD_API_00978 */
          LddMemEntry->data[LulIdx] = DEM_SET_BYTE;
        }
        /* @Trace: Dem_SUD_API_00981 */
        #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
        /* @Trace: Dem_SUD_API_00982 */
        LddMemEntry->IndexOfFFRecords = DEM_ZERO;
        #endif
      }
      #endif  

      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EvMem_AddMemLocInEvMemMap(EventId, DTCOrigin, LddMemLoc);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      /* @Trace: Dem_SUD_API_00983 */
      #if (DEM_J1939_SUPPORT == STD_ON)
      /* @Trace: Dem_SUD_API_00984 */
      Dem_EvMem_AddNewChronologicalOrder(DTCOrigin, LddMemLoc);
      #endif

      /*******************************************************************
       *                      ConfirmedDTC bit = 1                       *
       * [1] @ISO 14229:2013, 373p, Figure D.9                           *
       * [2] @RfC 59420, Remove the DemEventFailureCycleRef              *
       * [3] new event or TestFailedThisOperationCycle from 0 to 1       *
       *******************************************************************/
      /* @Trace: Dem_SUD_API_00985 */
      #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
      /* 
       * Confirmation threshold [ "Blank" == one ]
       *
       * The ConfirmedDTC bit is set (change from 0 to 1) at the same time as
       * the pendingDTC bit because this example is for a non emissions-related
       * server/ECU with a confirmation threshold of 1.
       */
      if (Dem_GaaEventFailureThreshold[EventId] > DEM_ONE)
      {
        /* Trace: DEM_GEN_17 */
        #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
        if(LblObdDcyQualified)
        #endif
        {
          /* @Trace: Dem_SUD_API_00987 */      
          LddMemEntry->FailureCycleCounter = DEM_ONE; /* Because new event */
        }
      }          
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_00986 */
        /* @Trace: Dem_SUD_API_00988 */
        #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
        uint8 LucCliendIdx =
            Dem_EvMem_GetClientIDFromEventMemorySet(LddEvent->ucEventMemDstIdx);
        /* @Trace: Dem_SUD_API_00989 */
        if (DEM_NO_IDX_U8 != LucCliendIdx)
        {
          /* @Trace: Dem_SUD_API_00991 */
          *StatusDirty |=
              Dem_EvMem_SetFirstLastConfirmedDTC(LucCliendIdx, DTCOrigin, DTC);
        }
        #endif
      }
      /* @Trace: SWS_Dem_01052
       * For combination on storage, an event that cannot set the confirmed bit
       * due to [SWS_Dem_01051] shall still generate warningIndicatorOnCriteria
       * according to [SWS_Dem_00501]. */
      /* @Trace: Dem_SUD_API_00992 */
      if (LddEvent->ucNumberofIndicator > DEM_ZERO)
      {
        /* @Trace: Dem_SUD_API_00993 */
        /* DEM_ZERO == new event */
                /* Trace: DEM_GEN_17 */
        #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
        if(LblObdDcyQualified)
        #endif
        /* @Trace: Dem_SUD_API_00993 */
        /* DEM_ZERO == new event */
        {
          Dem_EventIdType LddCbDtcEventId = EventId;
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          /* Trace: DEM_COMB_03 */
          #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
          Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
          boolean LblCbDtcIndicatorIncFlag = DEM_FALSE;

          if (NULL_PTR != LddCbDTC)
          {
            Dem_NumOfEventIdType LddStartPos =
                Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
            const Dem_NumOfEventIdType LddEndPos =
                Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);

            while (LddStartPos < LddEndPos)
            {
              Dem_EventIdType LddTmpEvId =
                  Dem_ListOfCombinedEvents[LddStartPos];
              if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(LddTmpEvId, DEM_UDS_STATUS_TFTOC))
                    || (DEM_TRUE == Dem_EvIsUdsProcStateTriggered( LddTmpEvId,
                                          DEM_UDSPROCSTATE_TRANSITION_BIT_1)))
              {
                /* Exclude Itself */
                if (LddTmpEvId != EventId)
                {
                  LblCbDtcIndicatorIncFlag = DEM_TRUE;
                  break;
                }
              }                  
              ++LddStartPos;
            }
          }

          if (LddMemEntry->EventIdRef != EventId)
          {
            LddCbDtcEventId = LddMemEntry->EventIdRef;
          }

          if (LblCbDtcIndicatorIncFlag == DEM_FALSE)
          #endif
          #endif
          {

            *StatusDirty |=
                Dem_ActivateIndicatorOnEventFailed(LddCbDtcEventId, (uint8)DEM_ZERO);
          }
        }
      }
      *EventDirty = DEM_TRUE;

      /* Handling for MIRROR Memory*/
      /* @Trace: Dem_SUD_API_00994 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00995 */
      if ((LddEvent->ucNumOfDestSelected == DEM_TWO ) &&
          (LddMemEntryMir != NULL_PTR))
      {
        /* @Trace: Dem_SUD_API_00996 */
        (void)Dem_EvMem_CopyMemoryEntries(LddMemEntryMir,LddMemEntry);
      }
      #endif

      LddRetVal = DEM_PROCESSEVENTRETENTION_OK; 
    }
    else
    {
      /* @Trace: Dem_SUD_API_01105 */
      LddRetVal = DEM_PROCESSEVENTRETENTION_FULL;
    }
  }      
  
  return LddRetVal;
}


/******************************************************************************
* Function Name        : Dem_EvMem_CopyMemoryEntries
*
* Service ID           : None
*
* Description          : copy memory entries from src to dest
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : memEntrySrc
*
* InOut parameter      : None
*
* Output Parameters    : memEntryDest
*
* Return parameter     : Std_ReturnType
*
* Preconditions        : This function shall be called when DTC supports
*                        immediate-storage
*
* Remarks              :
*
*****************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_CopyMemoryEntries(
    Dem_EventMemoryEntryPtrType memEntryDest,
    Dem_EventMemoryEntryPtrType memEntrySrc)
{
  Std_ReturnType LddReVal = E_NOT_OK;
  /* @Trace: Dem_SUD_API_01107 */
  if ((NULL_PTR != memEntrySrc) && (NULL_PTR != memEntryDest))
  {
    /* @Trace: Dem_SUD_API_01115 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_01116 */
    memEntryDest->TimeStamp = memEntrySrc->TimeStamp;
    #endif

    /* Event Id which failure */
    memEntryDest->EventIdRef = memEntrySrc->EventIdRef;
    /* @Trace: Dem_SUD_API_01117*/
    #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
    /* Event Status Byte */
    /* @Trace: Dem_SUD_API_01118 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx< DEM_MAX_NUM_EVENTS_PER_DTC;LucIdx++)
    {
      /* @Trace: Dem_SUD_API_01119 */
      memEntryDest->EventStatuByte[LucIdx] = memEntrySrc->EventStatuByte[LucIdx];
    }
    #endif

    memEntryDest->EventOccurrenceCounter = memEntrySrc->EventOccurrenceCounter;
    memEntryDest->AgingCycleCounter = memEntrySrc->AgingCycleCounter;
    /* @Trace: Dem_SUD_API_01120 */
    #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
    /* @Trace: Dem_SUD_API_01121 */
    memEntryDest->FailureCycleCounter = memEntrySrc->FailureCycleCounter;
    #endif
    /* @Trace: Dem_SUD_API_01122 */
    #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01108 */
    memEntryDest->IndexOfFFRecords = memEntrySrc->IndexOfFFRecords;
    #endif

    /* 3. EXTENDED DATA */
    /* @Trace: Dem_SUD_API_01109 */
    #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01111 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_SIZE_OF_EVENT_DATA; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_01110 */
      memEntryDest->data[LucIdx] = memEntrySrc->data[LucIdx];
    }
    #endif

    /* @Trace: Dem_SUD_API_01112 */
    #if ((DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON))
    /* @Trace: Dem_SUD_API_00225 */
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    memEntryDest->cyclesSinLastFailedCounter =
        memEntrySrc->cyclesSinLastFailedCounter;
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    #endif
    /* @Trace: Dem_SUD_API_01113 */
    #if (DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
    /* @Trace: Dem_SUD_API_00226 */
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    memEntryDest->cyclesSinFirstFailedCounter =
        memEntrySrc->cyclesSinFirstFailedCounter;
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    #endif
    /* @Trace: Dem_SUD_API_01114 */
    #if (DEM_INTERNAL_DATA_FAILED_CYCLES == STD_ON)
    /* @Trace: Dem_SUD_API_00227 */
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    memEntryDest->failedCyclesCounter =
        memEntryDest->failedCyclesCounter;
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    #endif

    LddReVal = E_OK;
  }

  return LddReVal;
}

/******************************************************************************
* Function Name        : Dem_EvMem_EventIsImmediateStorage
*
* Service ID           : None
*
* Description          : Checks whether Event supports immediate storage or not
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : DTCOrigin, EventId
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : uint8
*
* Preconditions        : This function shall be called when DTC supports
*                        immediate-storage
*
* Remarks              : 
*
*****************************************************************************/
FUNC(uint8, DEM_CODE) Dem_EvMem_EventIsImmediateStorage(
  Dem_DTCOriginType DTCOrigin,  
  Dem_EventIdType EventId)
{
  uint8 LucSupport = DEM_EVMEM_STATUS_DIRTY | DEM_EVMEM_STATUS_TRIGGER_NVM;

  Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[EventId];
  Dem_NumOfEventMemoryEntryType LddSizeOfMem =
           Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
  Dem_NumOfEventMemoryEntryType LddStartIndex =
           Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
  LddSizeOfMem = LddSizeOfMem + LddStartIndex;
  /* @Trace: Dem_SUD_API_01123 */
  if (LddMemLoc < LddSizeOfMem)
  {  
    Dem_EventMemoryEntryPtrType LddMemEntry;
    /* @IF_REQ : if occ is 255 and limit is 255 ? */
    switch(DTCOrigin) {
    /* @Trace: Dem_SUD_API_01124 */
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
      /* @Trace: Dem_SUD_API_01125 */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLoc)
      {
        LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
        /* @Trace: Dem_SUD_API_01126 */
        if (LddMemEntry->EventOccurrenceCounter >=
              Dem_Immdiate_Nv_Storage_Limit)
        {
          /* @Trace: Dem_SUD_API_00228 */
          LucSupport = DEM_EVMEM_STATUS_DIRTY;
        }
      }
      break;
      /* @Trace: Dem_SUD_API_01127 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    DEM_DTCORGIN_USER_DEFINED_CASE
    /* @Trace: Dem_SUD_API_01129 */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > LddMemLoc)
      {
        LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
        /* @Trace: Dem_SUD_API_01130 */
        if (LddMemEntry->EventOccurrenceCounter >=
              Dem_Immdiate_Nv_Storage_Limit)
        {
          /* @Trace: Dem_SUD_API_00229 */
          LucSupport = DEM_EVMEM_STATUS_DIRTY;
        }
      }
      break;
    #endif

    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * Default switch clause is unreachable. switch-expression. */
    default:
    /* @Trace: Dem_SUD_API_01128 */
    /*  Do Nothing  */
      break;
    }  
  }
  /* @Trace: Dem_SUD_API_00230 */
  return LucSupport;
}


/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearMemLocInEvMemMap
 **
 ** Service ID          : None
 **
 ** Description         : clear event memory index into the event memory map
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : EventId, DTCOrigin, EvMemEt
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
/* @Trace: SRS_Diag_04073 */
/* polyspace +6 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DEM_CODE) Dem_EvMem_ClearMemLocInEvMemMap(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
  /* @Trace: Dem_SUD_API_01131 */
  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)  
  ,Dem_EventMemoryEntryPtrType EvMemEt
  #endif
)
{
  if (((DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
     #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      || (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
     #endif
     ) && ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId)))
  {
    /* @Trace: SWS_Dem_00440
     * If the Dem module is requested to clear a combined DTC (refer to
     * Dem_ClearDTC), the Dem module shall clear all related events (refer to
     * [SWS_Dem_01049] and [SWS_Dem_01050])
     */
    #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
        Dem_GetCbDTCByEventId(EventId);
    /* @Trace: Dem_SUD_API_01145 */
    if (NULL_PTR != LddCbDTC)
    {
      if (DEM_ONE == LddCbDTC->ddNumberOfEvents)
      {
        /* @Trace: Dem_SUD_API_01143 */
        Dem_EvMemToEventMap[EventId] = DEM_NO_EVMEM_ENTRY;
      }
      else
      {
        /* @Trace: Dem_SUD_API_01144 */
        Dem_NumOfEventIdType LddStartPos =
            Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
        const Dem_NumOfEventIdType LddEndPos =
            Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
        /* @Trace: Dem_SUD_API_01147 */
        for (; LddStartPos < LddEndPos; LddStartPos++)
        {
          /* @Trace: Dem_SUD_API_01146 */
          Dem_EvMemToEventMap[Dem_ListOfCombinedEvents[LddStartPos]] =
              DEM_NO_EVMEM_ENTRY;
        }
      }
    }
    #else
    /* @Trace: Dem_SUD_API_01142 */
    Dem_EvMemToEventMap[EventId] = DEM_NO_EVMEM_ENTRY;
    #endif

    Dem_EvClearProcState(EventId, DEM_EVPROCSTATE_EVENT_STORED);
  }


  Dem_NumOfEventMemoryEntryType LddNumOfEvtMemEntries =
      Dem_EvMem_GetNumOfStoredEvtMemEntries(EventId, DTCOrigin);
      /* @Trace: Dem_SUD_API_01148 */
  if (LddNumOfEvtMemEntries > DEM_ZERO)
  {
    /* @Trace: Dem_SUD_API_01149 */
    Dem_EvMem_DecreaseNumOfStoredEvtMemEntries(EventId, DTCOrigin, DEM_ONE);
  }
  /* @Trace: Dem_SUD_API_01132 */
  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
  /* @Trace: Dem_SUD_API_01133 */
  if (NULL_PTR != EvMemEt)
  {
    /* @Trace: Dem_SUD_API_01134 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_01136 */
      if (Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] ==
            EvMemEt->TimeStamp)
      {
        /* @Trace: Dem_SUD_API_01137 */
        if (Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] > DEM_ZERO)
        {
          /* @Trace: Dem_SUD_API_01138 */
          Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY]--;
        }
      }
    }
    else
    #endif
    {
      /* @Trace: Dem_SUD_API_01135 */
      /* @Trace: Dem_SUD_API_01139 */
      if (Dem_MaxTimeStamp[DTCOrigin] == EvMemEt->TimeStamp)
      {
        /* @Trace: Dem_SUD_API_01140 */
        if (Dem_MaxTimeStamp[DTCOrigin] > DEM_ZERO)
        {
          /* @Trace: Dem_SUD_API_01141 */
          Dem_MaxTimeStamp[DTCOrigin]--;
        }
      }
    }
  }
  #endif  
}


/*******************************************************************************
 ** Function Name       : Dem_EvMem_AddMemLocInEvMemMap
 **
 ** Service ID          : None
 **
 ** Description         : Insert new event memory index into the event 
 **                       memory Map
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : EventId, DTCOrigin, MemLocation
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
 ******************************************************************************/
/* @Trace: SRS_Diag_04073
 */
FUNC(void, DEM_CODE) Dem_EvMem_AddMemLocInEvMemMap(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  Dem_NumOfEventMemoryEntryType MemLocation)
{
  Dem_NumOfEventMemoryEntryType LddNumOfEvtMemEntries = DEM_ZERO;

  LddNumOfEvtMemEntries =
      Dem_EvMem_GetNumOfStoredEvtMemEntries(EventId, DTCOrigin);
  /* @Trace: Dem_SUD_API_01150 */
  if (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
  {
    /* @Trace: SWS_Dem_00024
     * In case DemEventCombinationSupport is set to DEM_EVCOMB_ONRETRIEVAL or
     * DEM_EVCOMB_ONSTORAGE, the combination of multiple events to a DTC is
     * defined by referencing from each event to the same DTC.
     */
    /* @Trace: Dem_SUD_API_01151 */
    #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
        Dem_GetCbDTCByEventId(EventId);
    if (NULL_PTR != LddCbDTC)
    {  
      if (DEM_ZERO == LddCbDTC->ddNumberOfEvents)
      {
        /* @Trace: Dem_SUD_API_00189 */
        Dem_EvMemToEventMap[EventId] = MemLocation;
      }
      else
      {
        /* @Trace: Dem_SUD_API_01153 */
        Dem_NumOfEventIdType LddStartPos =
            Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
        const Dem_NumOfEventIdType LddEndPos =
            Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
        /* @Trace: Dem_SUD_API_01155 */
        for (;LddStartPos < LddEndPos; LddStartPos++)
        {
          /* @Trace: Dem_SUD_API_01154 */
          Dem_EvMemToEventMap[Dem_ListOfCombinedEvents[LddStartPos]] =
              MemLocation;
        }
      }
    }
    #else  
    Dem_EvMemToEventMap[EventId] = MemLocation;
    #endif
    /* @Trace: Dem_SUD_API_01152 */
    Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EVENT_STORED);
  }
  /* @Trace: Dem_SUD_API_01156 */
  if ((LddNumOfEvtMemEntries < DEM_NO_EVMEM_ENTRY))
  {
    /* @Trace: Dem_SUD_API_01157 */
    Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(EventId, DTCOrigin, DEM_ONE);
  }
}



/******************************************************************************
* Function Name        : Dem_EvMem_FindEntry
*
* Service ID           : None
*
* Description          : Find the stored event in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant(Not same event Id)
*
* Input Parameters     : EventId, DTCOrigin
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : Dem_EventMemoryEntryPtrType
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(Dem_EventMemoryEntryPtrType, DEM_CODE) Dem_EvMem_FindEntry(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin)
{  
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
  Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
  Dem_NumOfEventMemoryEntryType LddStartIdx =
      Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
  Dem_NumOfEventMemoryEntryType LddStopIdx =
      Dem_EvMem_GetStopIndexEventMemorySet(EventId, DTCOrigin);

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  LddMemLoc = Dem_EvMemToEventMap[EventId];
  /* @Trace: Dem_SUD_API_01158 */
  if ((LddStartIdx <= LddMemLoc) && (LddMemLoc < LddStopIdx))
  {
    /* @Trace: Dem_SUD_API_01170 */
    /* Duplicated code for performance and runtime check(polyspace) */
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_01168 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLoc)
      {
        /* @Trace: Dem_SUD_API_01169 */
        LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
      }
    }
    /* @Trace: Dem_SUD_API_01174 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01167 */
    else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_01160 */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > LddMemLoc)
      {
        /* @Trace: Dem_SUD_API_00190*/
        LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
      }
    }
    /* @Trace: Dem_SUD_API_01171 */
    #endif
    /* @Trace: Dem_SUD_API_01161 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_01159 */
    else if (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
    {
      /* @Trace: Dem_SUD_API_01163 */
      if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMemLoc)
      {
        /* @Trace: Dem_SUD_API_01164 */
        LddMemEntry = &Dem_MirrorEventMemory[LddMemLoc];
      }
    }
    /* @Trace: Dem_SUD_API_01172 */
    #endif
    /* @Trace: Dem_SUD_API_01165 */
    #if ((DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO) && \
         (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
         /* @Trace: Dem_SUD_API_01162 */
    else if ((DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin) &&
             (DEM_MAX_NUMBER_EVENT_ENTRY_PER > LddMemLoc))
    {
      /* @Trace: Dem_SUD_API_00191 */
      LddMemEntry = &Dem_PermanentEventMemory[LddMemLoc];
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_01166 */
      /* Do nothing */
    }
  }
  /* @Trace: Dem_SUD_API_01173 */
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

  return LddMemEntry;
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_DTCFormatIsValid
 **
 ** Service ID          : None
 **
 ** Description         : Checks whether DTC Origin is supported or not
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : DTCFormat, CombinedDTC
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
/* @Trace: SRS_Diag_04000
 */
FUNC(boolean, DEM_CODE) Dem_EvMem_DTCFormatIsValid(
    const Dem_DTCFormatType DTCFormat, Dem_CombinedDtcPCType CombinedDTC)
{
  boolean LblValid = FALSE;

  switch(DTCFormat)
  {
    /* @Trace: Dem_SUD_API_01175 */
    case DEM_DTC_FORMAT_UDS:
    /* @Trace: Dem_SUD_API_01179 */
    if (NULL_PTR != CombinedDTC)
    {
      /* @Trace: Dem_SUD_API_01180 */
      if (CombinedDTC->ulUdsDtc != DEM_NO_DTC)
      {
        /* @Trace: Dem_SUD_API_01181 */
        LblValid = TRUE;
      }
    }
    break;
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_01183 */
    case DEM_DTC_FORMAT_OBD:
    /* @Trace: Dem_SUD_API_01184 */
    if (NULL_PTR != CombinedDTC)
    {
      /* @Trace: Dem_SUD_API_01185 */
      if (CombinedDTC->usObdDtc != DEM_NO_DTC)
      {
        /* @Trace: Dem_SUD_API_01182 */
        LblValid = TRUE;
      }
    }
    break;
    
    #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
    /* Trace: DEM_19792_42_04 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
    case DEM_DTC_FORMAT_OBD_3BYTE:
    if (NULL_PTR != CombinedDTC)
    {          
      /* DemSupportedobdUdsDtcSeparation is need to supported */           
      if (Dem_ObdUdsDtc_Separation_Support == STD_ON)
      {
        if (CombinedDTC->ulObdDtc3Byte != DEM_NO_DTC)
        {
          LblValid = TRUE;
        }
      }
      else                   
      {
        /* @Trace: Dem_SUD_API_01185 */
        if (CombinedDTC->ulUdsDtc != DEM_NO_DTC)
        {
          /* @Trace: Dem_SUD_API_01182 */
          LblValid = TRUE;
        }
      }
    }
    break;
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
    #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/

    #endif
    /* @Trace: Dem_SUD_API_01186 */
    #if (DEM_J1939_SUPPORT == STD_ON)
    case DEM_DTC_FORMAT_J1939:
    /* @Trace: Dem_SUD_API_01177 */
    if (CombinedDTC->J1939DTCValue != DEM_NO_DTC)
    {
      /* @Trace: Dem_SUD_API_01178 */
      LblValid = TRUE;
    }
    break;
    #endif

    default:
    /* @Trace: Dem_SUD_API_01176 */
    LblValid = DEM_FALSE;
    break;
  }

  return LblValid;
}

/******************************************************************************
 * Function Name        : Dem_AllocateEventMemoryEntry
 *
 * Service ID           : None
 *
 * Description          : Allocate memory entry for Event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTC, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_EventMemoryEntryPtrType
 *
 * Preconditions        :
 *
 * Remarks              : Global Variable(s)  :
 *                        Function(s) invoked :
 ******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04073 SRS_Diag_04105 SRS_Diag_04118
           SRS_Diag_04125 SRS_Diag_04131
 */
/* polyspace +1 CODE-METRICS:VG CODE-METRICS:CALLS  CODE-METRICS:FXLN CODE-METRICS:PATH[Not a defect:LOW] "Not a defect" */ 
FUNC(Dem_EventMemoryEntryPtrType, DEM_CODE) Dem_AllocateEventMemoryEntry
    (Dem_EventIdType EventId,
     #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
     Dem_DTCType DTC,
     #endif
     Dem_DTCOriginType DTCOrigin
     )
{
  Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_ZERO;
    Dem_NumOfEventMemoryEntryType LddStartIdx =
        Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
    Dem_NumOfEventMemoryEntryType LddStopIdx =
        Dem_EvMem_GetStopIndexEventMemorySet(EventId, DTCOrigin);
    Dem_NumOfEventMemoryEntryType LddNumOfMemEntries =
        Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
    Dem_NumOfEventMemoryEntryType LddNumOfStoredEvtMemEntries =
        Dem_EvMem_GetNumOfStoredEvtMemEntries(EventId ,DTCOrigin);
    uint8 LucDispStrategy =
        Dem_EvMem_GetEventDisplacementStrategy(EventId, DTCOrigin);
    /* @Trace: Dem_SUD_API_01187 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_01198 */
    Dem_EventMemoryEntryPtrType LddMemEntryObd = NULL_PTR;
    #endif
    /* @Trace: Dem_SUD_API_01209 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
    /* @Trace: Dem_SUD_API_00192 */
    Dem_EventMemoryEntryPtrType LddMemEntryMir = NULL_PTR;
    #endif
    if (LddNumOfStoredEvtMemEntries < LddNumOfMemEntries)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_01246 */
        for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
        {
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          if (DEM_NO_EVENT == Dem_PrimaryEventMemory[LddMemLoc].EventIdRef)
          {
            /* @Trace: Dem_SUD_API_01242 */
            /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
            if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLoc)
            {
              /* @Trace: Dem_SUD_API_01245 */
              LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
              LddMemEntry->EventIdRef = EventId; /* Set EventId */
            }
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            break;
          }
          else
          {
            /* @Trace: Dem_SUD_API_00193 */
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
        }
        /* @Trace: Dem_SUD_API_01247 */
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /* @Trace: Dem_SUD_API_01188 */
        if (DEM_NUM_OF_EVENTRELATEDDATA > LddEvent->e_PointToData)
        {
          /* @Trace: Dem_SUD_API_00194 */
          P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) LddEvData
              = &Dem_EventRelatedData[LddEvent->e_PointToData];
          /* Allocation for OBD*/
          /* @Trace: Dem_SUD_API_01189 */
          if ((LddEvData->OBDClassPos != NULL_PTR) &&
              (DEM_NO_EVMEM_ENTRY == Dem_ObdMemoryId))
          {
            /* @Trace: Dem_SUD_API_01190 */
            for (Dem_NumOfEventMemoryEntryType LddMemLocObd = LddStartIdx;
                                               LddMemLocObd < LddStopIdx;
                                               LddMemLocObd++)
            {
              /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
              if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > LddMemLocObd)
              {
                /* @Trace: Dem_SUD_API_00195 */
                SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                if (DEM_NO_EVENT ==
                      Dem_PrimaryEventMemory[LddMemLocObd].EventIdRef)
                {
                  /* @Trace: Dem_SUD_API_00196 */
                  LddMemEntryObd = &Dem_PrimaryEventMemory[LddMemLocObd];
                  LddMemEntryObd->EventIdRef = EventId; /* Set EventId */
                  Dem_ObdMemoryId = (uint8)LddMemLocObd;
                  Dem_EventStatusNvRamData.ObdMemoryId = Dem_ObdMemoryId;
                  Dem_EvMem_SetNonVolatieDataStatus(
                      DEM_NVDATA_ALL_EVENT_STATUS_ID,
                      DEM_EVMEM_STATUS_DIRTY_NVM);
                  Dem_EvMem_TriggerWriteAllBlocks();
                  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                  break;
                }
                else
                {
                  /* @Trace: Dem_SUD_API_00197 */
                  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                }
              }
            }
            /* @Trace: Dem_SUD_API_01191 */
            if (NULL_PTR != LddMemEntryObd)
            {
              /* @Trace: Dem_SUD_API_00198 */
              Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
                  EventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_ONE);
            }
          }
        }
        #endif
      }
      /* @Trace: Dem_SUD_API_01192 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      /* @Trace: Dem_SUD_API_01231 */
      else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      {
        /* @Trace: Dem_SUD_API_01194 */
        for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
        {
          /* @Trace: Dem_SUD_API_00199 */
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          if (DEM_NO_EVENT == Dem_UserDefinedEventMemory[LddMemLoc].EventIdRef)
          {
            /* @Trace: Dem_SUD_API_01195 */
            if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > LddMemLoc)
            {
              /* @Trace: Dem_SUD_API_00200 */
              LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
              LddMemEntry->EventIdRef = EventId; /* Set EventId */
            }
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            break;
          }
          else
          {
            /* @Trace: Dem_SUD_API_00201 */
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
        }
      }
      #endif
      else
      {
        /* @Trace: Dem_SUD_API_01193 */
        /* retVal = DEM_PROCESSEVENTRETENTION_FAILED; */
      }

      /* Handling for MIRROR Memory*/
      /* @Trace: Dem_SUD_API_01197 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_00202 */
      /* @Trace: Dem_SUD_API_01199 */
      if (DEM_TWO == LddEvent->ucNumOfDestSelected )
      {
        Dem_NumOfEventMemoryEntryType LddStartMirIdx =
            Dem_EvMem_GetStartIndexEventMemorySet( EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY);
        Dem_NumOfEventMemoryEntryType LddStopMirIdx =
            Dem_EvMem_GetStopIndexEventMemorySet( EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY);
        Dem_NumOfEventMemoryEntryType LddMemLocMirId =
            Dem_EvMem_FindMirMemLoc(EventId);
        if (DEM_NO_EVMEM_ENTRY == LddMemLocMirId)
        {
          for (LddMemLocMirId = LddStartMirIdx;
               LddMemLocMirId < LddStopMirIdx;
               LddMemLocMirId++)
          {
            /* @Trace: Dem_SUD_API_00203 */
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            if (DEM_NO_EVENT ==
                  Dem_MirrorEventMemory[LddMemLocMirId].EventIdRef)
            {
              /* @Trace: Dem_SUD_API_01196 */
              if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMemLocMirId)
              {
                /* @Trace: Dem_SUD_API_00204 */
                LddMemEntryMir = &Dem_MirrorEventMemory[LddMemLocMirId];
                LddMemEntryMir->EventIdRef = EventId; /* Set EventId */
                Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
                    EventId, DEM_DTC_ORIGIN_MIRROR_MEMORY, DEM_ONE);
              }
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              break;
            }
            else
            {
              /* @Trace: Dem_SUD_API_00205 */
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_01200 */
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          /* @Trace: Dem_SUD_API_01201 */
          if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMemLocMirId)
          {
            /* @Trace: Dem_SUD_API_00206 */
            LddMemEntryMir = &Dem_MirrorEventMemory[LddMemLocMirId];
          }
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
      #endif
    }
    /* event memory is full */

    /* @Trace: SWS_Dem_00400
     * If the event retention want to allocate a new event memory entry and
     * there is no free event memory entry available, the Dem module shall
     * check according [SWS_Dem_00406] for allocated event memory entries to be
     * displaced by the new event memory entry.
     */
    /* @Trace: SWS_Dem_00401
     * The Dem module provides the configuration parameter
     * DemEventDisplacementStrategy (refer to DemPrimaryMemory or
     * DemUserDefinedMemory) defining whether the existing event memory entry
     * can be displaced or not.
     */
    /* @Trace: SWS_Dem_00402
     * If event displacement is disabled (DemEventDisplacementStrategy in
     * DemPrimaryMemory or DemUserDefinedMemory selects DEM_DISPLACEMENT_NONE),
     * the Dem module shall not displace existing event memory entries if the
     * event memory is full.
     */
    /* @Trace: Dem_SUD_API_01220 */
    else if (DEM_DISPLACEMENT_NONE != LucDispStrategy)
    {
      /* @Trace: Dem_SUD_API_00207 */
      LddMemLoc =
          Dem_EvMem_FindEntryWithLowestPriority(
              EventId, LddEvent->ucEventPriority, DTCOrigin, LucDispStrategy);
      Dem_NumOfEventMemoryEntryType LddsizeOfMem =
                Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);
      Dem_NumOfEventMemoryEntryType LddStartIndex =
                Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
      LddsizeOfMem = LddsizeOfMem + LddStartIndex;
      /* @Trace: Dem_SUD_API_01203 */
      if (LddMemLoc < LddsizeOfMem)
      {
        /* Duplicated code for performance and runtime check(polyspace) */
        if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
        {
          /* @Trace: Dem_SUD_API_01205 */
          if (LddMemLoc < DEM_MAX_NUMBER_EVENT_ENTRY_PRI)
          {
            /* @Trace: Dem_SUD_API_00208 */
            LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
          }
        }
        /* @Trace: SWS_Dem_01063
         * The user defined memory shall have the same behavior as the
         * primary memory(event retention, event prioritization, aging,
         * displacement).
         */
        /* @Trace: Dem_SUD_API_01206 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
        /* @Trace: Dem_SUD_API_01204 */
        else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID (DTCOrigin))
        {
          if (LddMemLoc < DEM_MAX_NUMBER_EVENT_ENTRY_UD)
          {
            /* @Trace: Dem_SUD_API_00209 */
            LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
          }
        }
        #endif
        else
        {
          /* @Trace: Dem_SUD_API_01207 */
          /* Do nothing */
        }
      }

      /* Handling for MIRROR Memory*/
      /* @Trace: Dem_SUD_API_01208 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_01210 */
      if ( DEM_TWO == LddEvent->ucNumOfDestSelected  )
      {
        Dem_NumOfEventMemoryEntryType LddMirMemLoc =
             Dem_EvMem_FindEntryWithLowestPriority(
                 EventId, LddEvent->ucEventPriority,
                 DEM_DTC_ORIGIN_MIRROR_MEMORY,
                 LucDispStrategy);

        LddsizeOfMem =
            Dem_EvMem_GetSizeOfElementEventMemory(EventId, DTCOrigin);

        Dem_NumOfEventMemoryEntryType LddStartIndexMir =
            Dem_EvMem_GetStartIndexEventMemorySet(EventId, DTCOrigin);
        LddsizeOfMem = LddsizeOfMem + LddStartIndexMir;
        /* @Trace: Dem_SUD_API_01211 */
        if (LddMirMemLoc < LddsizeOfMem)
        {
          if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > LddMirMemLoc)
          {
            /* @Trace: Dem_SUD_API_00210 */
            LddMemEntryMir = &Dem_MirrorEventMemory[LddMirMemLoc];
          }
        }
      }
      #endif
    }
    else
    {
      /* @Trace: Dem_SUD_API_01202 */
      /* Nothing to do */
    }

    /* New Entry */
    /* @Trace: Dem_SUD_API_01212 */
    if (NULL_PTR != LddMemEntry)
    {
      /* @Trace: SWS_Dem_00780
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this counter is not
       * stored in event memory and there are available event memory entry, new
       * entry shall be allocated and the counter shall be started and
       * initialized to zero.
       * */
      /* @Trace: SWS_Dem_00776
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this counter is not
       * stored in event memory and there are available event memory entry, new
       * entry shall be allocated and the counter shall be started and
       * initialized to zero.*/
      /* @Trace: SWS_Dem_00771
       * If internal debounce counter reach DemDebounceCounterFailedThreshold
       * (latest UDS status bit 0 changes from 0 to 1) and this counter is not
       * stored in event memory and there are available event memory entry,
       * new entry shall be allocated and the counter shall be started and
       * initialized to zero.*/
      /* @Trace: Dem_SUD_API_01213 */
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
      /* @Trace: Dem_SUD_API_01214 */
      if (((DEM_DEBOUNCE_COUNTER_BASED ==
              DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA)) &&
           (Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry] >=
               Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry].
                 ssDemCounterFailedThreshold)))
      {
        /* @Trace: Dem_SUD_API_01215 */
        #if ((DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON))
        /* @Trace: Dem_SUD_API_01216 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        LddMemEntry->cyclesSinLastFailedCounter = DEM_ZERO;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        #endif
        /* @Trace: Dem_SUD_API_01244 */
        #if (DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
        /* @Trace: Dem_SUD_API_01217 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        LddMemEntry->cyclesSinFirstFailedCounter = DEM_ZERO;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        #endif
        /* @Trace: Dem_SUD_API_01243 */
        #if (DEM_INTERNAL_DATA_FAILED_CYCLES == STD_ON)
        /* @Trace: Dem_SUD_API_00211 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        LddMemEntry->failedCyclesCounter = DEM_ZERO;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        #endif
      }
      #endif
      /* @Trace: Dem_SUD_API_01241 */
      #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
      LddMemEntry->TimeStamp = Dem_EvMem_FindNewTimeStamp(EventId, DTCOrigin);
      /* @Trace: Dem_SUD_API_01238 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
      if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
      {
        /* @Trace: Dem_SUD_API_01240 */
        if (Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] <
              LddMemEntry->TimeStamp)
        {
          /* @Trace: Dem_SUD_API_00212 */
          Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] =
              LddMemEntry->TimeStamp;
        }
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_01239 */
        /* @Trace: Dem_SUD_API_01218 */
        if (Dem_MaxTimeStamp[DTCOrigin] < LddMemEntry->TimeStamp)
        {
          /* @Trace: Dem_SUD_API_00213 */
          Dem_MaxTimeStamp[DTCOrigin] = LddMemEntry->TimeStamp;
        }
      }
      #endif
      /* @Trace: Dem_SUD_API_01219 */
      /* @Trace: Dem_SUD_MACRO_050 */
      #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
      {
        /* @Trace: Dem_SUD_API_01237 */
        for (uint16 LusIdx = DEM_ZERO;
                    LusIdx < DEM_MAX_NUM_EVENTS_PER_DTC;
                    LusIdx++)
        {
          /* @Trace: Dem_SUD_API_01221 */
          LddMemEntry->EventStatuByte[LusIdx] = DEM_ZERO;
        }
      }
      #endif

      /* @Trace: SWS_Dem_00523
       * The Dem module shall initialize the occurrence counter with the value
       * one if the related event is entered in the respective event memory. */
      LddMemEntry->EventOccurrenceCounter = DEM_ONE;
      /* Initialize the failure counter related ConfirmedDTC */
      /* @Trace: Dem_SUD_API_01222 */
      #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
      /* @Trace: Dem_SUD_API_00214 */
      LddMemEntry->FailureCycleCounter = DEM_ZERO;
      #endif
      LddMemEntry->AgingCycleCounter = DEM_ZERO;
      /* @Trace: Dem_SUD_API_01223 */
      #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
      {
        uint32 LulIndex;
        /* @Trace: Dem_SUD_API_01224 */
        for (LulIndex = DEM_ZERO; LulIndex < DEM_SIZE_OF_EVENT_DATA; LulIndex++)
        {
          /* @Trace: Dem_SUD_API_01225 */
          LddMemEntry->data[LulIndex] = DEM_SET_BYTE;
        }
        /* @Trace: Dem_SUD_API_01226 */
        #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
        LddMemEntry->IndexOfFFRecords = DEM_ZERO;
        #endif
      }
      #endif

      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EvMem_AddMemLocInEvMemMap(EventId, DTCOrigin, LddMemLoc);
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      /* @Trace: Dem_SUD_API_01227 */
      #if (DEM_J1939_SUPPORT == STD_ON)
      /* @Trace: Dem_SUD_API_00215 */
      Dem_EvMem_AddNewChronologicalOrder(DTCOrigin, LddMemLoc);
      #endif

      /*******************************************************************
       *                      ConfirmedDTC bit = 1                       *
       * [1] @ISO 14229:2013, 373p, Figure D.9                           *
       * [2] @RfC 59420, Remove the DemEventFailureCycleRef              *
       * [3] new event or TestFailedThisOperationCycle from 0 to 1       *
       *******************************************************************/
      /* @Trace: Dem_SUD_API_01228 */
      #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
      /*
       * Confirmation threshold [ "Blank" == one ]
       *
       * The ConfirmedDTC bit is set (change from 0 to 1) at the same time as
       * the pendingDTC bit because this example is for a non emissions-related
       * server/ECU with a confirmation threshold of 1.
       */
      if (Dem_GaaEventFailureThreshold[EventId] > DEM_ONE)
      {
        /* @Trace: Dem_SUD_API_00216 */
        LddMemEntry->FailureCycleCounter = DEM_ONE; /* Because new event */
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_01229 */
        /* @Trace: Dem_SUD_API_01230 */
        #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
        uint8 LucCliendIdx =
            Dem_EvMem_GetClientIDFromEventMemorySet(LddEvent->ucEventMemDstIdx);
        /* @Trace: Dem_SUD_API_01232 */
        if (DEM_NO_IDX_U8 != LucCliendIdx)
        {
          /* @Trace: Dem_SUD_API_01233 */
          (void)Dem_EvMem_SetFirstLastConfirmedDTC(
              LucCliendIdx, DTCOrigin, DTC);
        }
        #endif
      }
      /* @Trace: SWS_Dem_01052
       * For combination on storage, an event that cannot set the confirmed bit
       * due to [SWS_Dem_01051] shall still generate warningIndicatorOnCriteria
       * according to [SWS_Dem_00501]. */
      /* @Trace: Dem_SUD_API_01234 */
      if (LddEvent->ucNumberofIndicator > DEM_ZERO)
      {
        /* @Trace: Dem_SUD_API_00217 */
        /* DEM_ZERO == new event */
        (void)Dem_ActivateIndicatorOnEventFailed(EventId, (uint8)DEM_ZERO);

      }

      /* Handling for MIRROR Memory*/
      /* @Trace: Dem_SUD_API_01235 */
      #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
      /* @Trace: Dem_SUD_API_01236 */
      if ((LddEvent->ucNumOfDestSelected == DEM_TWO ) &&
          (LddMemEntryMir != NULL_PTR))
      {
        /* @Trace: Dem_SUD_API_00218 */
        (void)Dem_EvMem_CopyMemoryEntries(LddMemEntryMir, LddMemEntry);
      }
      #endif
    }
  }
  return LddMemEntry;
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

