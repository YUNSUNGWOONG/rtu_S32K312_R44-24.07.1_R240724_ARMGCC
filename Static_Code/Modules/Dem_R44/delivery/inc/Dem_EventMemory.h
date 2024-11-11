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
**  SRC-MODULE: Dem_EventMemory.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_EventMemory.c                                **
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
** 1.0.14.0  25-Aug-2023   DanhTQ1       #CP44-2672                           **
** 1.0.6.0   21-Oct-2022   LanhLT        #CP44-907                            **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/


#ifndef DEM_EVENTMEMORY_H
#define DEM_EVENTMEMORY_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"
#include "Dem_Ram.h"
#include "Dem_NvData.h"

/*******************************************************************************
**                      Extern function definition                            **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, DEM_CODE) Dem_ClearEventsWithOutAssignedDTCs(void);

extern FUNC(Dem_UdsStatusByteType, DEM_CODE) Dem_EvMem_GetUdsStatusByteToNvData(
 const Dem_EventIdType EventId,
 const Dem_DTCOriginType DTCOrigin);

extern FUNC(void, DEM_CODE) Dem_EvMem_SetUdsStatusByteToNvData(
  const Dem_EventIdType EventId);
    
extern FUNC(void, DEM_CODE) Dem_EvMem_VerifyAllEventMemories(void);

extern FUNC(uint8, DEM_CODE) 
Dem_EvMem_TriggerNvDataStorage(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_UdsStatusByteType EventStatusByteOld,
  uint8 NvDataBlkStatus,
  boolean EvMemEntryIsDirty,
  boolean EvStatusIsDirty);

extern FUNC(void, DEM_CODE) Dem_EvMem_Init(void);

extern FUNC(uint8, DEM_CODE) Dem_EvMem_EventIsImmediateStorage(
  Dem_DTCOriginType DTCOrigin,  
  Dem_EventIdType EventId);

#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
extern FUNC(boolean, DEM_CODE) Dem_EvMem_SetFirstLastFailedDtc(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin, 
  Dem_DTCType DTC);
#endif

extern FUNC(uint8, DEM_CODE) Dem_GetDemEventMemoryEntryStorageTrigger(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);


extern FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_ProcessEventRetention(
  Dem_EventIdType EventId, 
  Dem_DTCOriginType DTCOrigin,  
  const Dem_UdsStatusByteType EventStatusByteOld,
  #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
  const Dem_UdsStatusByteType DTCStatusOld,
  #endif
  #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
  Dem_DTCType DTC,
  #endif  
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventDirty,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  StatusDirty);

#if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
extern FUNC(uint32, DEM_CODE) Dem_EvMem_FindNewTimeStamp(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin);
#endif

extern FUNC(void, DEM_CODE) Dem_EvMem_AddMemLocInEvMemMap(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  Dem_NumOfEventMemoryEntryType MemLocation);

extern FUNC(void, DEM_CODE) Dem_EvMem_ClearMemLocInEvMemMap(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin  
  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)  
  ,Dem_EventMemoryEntryPtrType EvMemEt
  #endif
);

extern FUNC(void, DEM_CODE) Dem_EvMem_IncNumOfStoredEvtMemEntriesFromClientId(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  uint8 memSize
);

extern FUNC(Dem_EventMemoryEntryPtrType, DEM_CODE) Dem_EvMem_FindEntry(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_IsUserDefinedBelongToEventMemorySet(
  uint8 MemSetId,
  uint8 userDefinedIdx
);

extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_FindEntryWithLowestPriority(
  Dem_EventIdType EventId,
  Dem_EventPriorityType PriorityOfNewEvent,
  Dem_DTCOriginType DTCOrigin,
  uint8 DisplacementStrategy);

extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetClientIDFromEventMemorySet(
  uint8 MemSetIdx
);

extern FUNC(boolean, DEM_CODE)
Dem_EvMem_ClearDTCOccurrenceTime(
  uint8 ClientId,
  const Dem_DTCType DTC,
  boolean AllDTCs);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_TriggerImmediateStorage(
  const Dem_EventMemoryEntryPtrType EvMemEntry);

extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetEvUserDefinedIdxFromDTCOrigin(
  Dem_DTCOriginType DTCOrigin);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_SetEvMemOverflowFlag(
    uint8 EvtMemSetId,
  Dem_DTCOriginType DTCOrigin, 
  boolean state);

extern FUNC(void, DEM_CODE) Dem_EvMem_AgingEvMemEntry(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,  
  Dem_EventMemoryEntryPtrType EvMemEntry);

extern FUNC(void, DEM_CODE) Dem_EvMem_PreInit(void);


extern FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionClearDtc(void);

extern FUNC(void, DEM_CODE) Dem_EvMem_RequestWriteAllBlocks(void);

extern FUNC(void, DEM_CODE) Dem_EvMem_RequestReadAllBlocks(void);

extern FUNC(void, DEM_CODE) Dem_EvMem_TriggerWriteAllBlocks(void);

extern FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionReadAll(void);

extern FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionWriteAll(void);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_Lock(void);

#if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
FUNC(Dem_EventMemoryEntryPtrType, DEM_CODE) Dem_EvMem_GetEmEntryByMemPosition(
  const Dem_DTCOriginType DTCOrigin, 
  const Dem_NumOfEventMemoryEntryType MemLocation);

extern FUNC(Dem_EventIdType, DEM_CODE) Dem_EvMem_GetEventIdByEvMemEntry(
  const Dem_DTCOriginType DTCOrigin, 
  const Dem_NumOfEventMemoryEntryType MemLocation);

extern FUNC(void, DEM_CODE) Dem_EvMem_SetEventId(
  Dem_EventMemoryEntryPtrType EvEntry,
  Dem_EventIdType EventId);

extern FUNC(void, DEM_CODE) Dem_EvMem_ClearEventMemoryEntry(
  Dem_EventMemoryEntryPtrType EmEntry);

extern FUNC(void, DEM_CODE) Dem_EvMem_ResetManagementBlock(
  boolean SetfootPrintAsDefault);

extern FUNC(void, DEM_CODE) Dem_EvMem_ResetEventStatusNvRamBlock(void);

#if(DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_FindMirMemLoc(
  Dem_EventIdType EventId);
#endif

#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
extern FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetEDBuffer(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize);
#endif

#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetFFBufferForWriting(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize,
  Dem_EventStatusType EventStatus);

extern FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetWWHFFBufferForWriting(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetFFRecNumConfiguredConditionState(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPCType MemEntry,
  Dem_EventStatusType EventStatus);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetWWHFFRecNumConfiguredConditionState(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPCType MemEntry);

extern FUNC(Dem_RecordNumberType, DEM_CODE) Dem_EvMem_GetRecNumOfFF(
  Dem_EventMemoryEntryCPCType entry);

#endif

extern FUNC(boolean, DEM_CODE) Dem_EvMem_CheckFirstEcuRun(void);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_DTCOriginIsValid(
  const Dem_DTCOriginType DTCOrigin);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetOpCycleState(
  uint8 OperationCycleId,
  Dem_OperationCycleStateType state);

extern FUNC(void, DEM_CODE) 
Dem_EvMem_GetOpCycleState(
  uint8 OperationCycleId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState);


extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_IncAgingCounter(
  Dem_EventMemoryEntryPtrType entry,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) AgingCounter);

extern FUNC(uint8, DEM_CODE) 
Dem_EvMem_GetAgingCounter(
  Dem_EventIdType EventId,
  Dem_EventMemoryEntryPCType MemEntry,
  uint32 ElementType);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetAgingCounter(
  Dem_EventMemoryEntryPtrType entry,
  uint8 AgingCounter);

extern FUNC(Dem_EventIdType, DEM_CODE) 
Dem_EvMem_FaultConfirmation(
  Dem_EventIdType EventId, 
  Dem_DTCOriginType DTCOrigin,
  #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > 1U)
  uint8 EventFailureThreshold,
  #endif
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) EventDirty);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetFailureCounter(
  Dem_EventMemoryEntryPtrType entry,
  uint8 FailureCounter);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_IncEventOccCounter(
  Dem_EventMemoryEntryPtrType entry);

extern FUNC(Dem_EventOccurrenceType, DEM_CODE) 
Dem_EvMem_GetEventOccCounter(
  Dem_EventMemoryEntryPCType MemEntry);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_GetEvMemOverflowFlag(
  uint8 EvtMemSetId,
  Dem_DTCOriginType DTCOrigin);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_EvMem_GetDTCByOccurrenceTime(
  uint8 ClientId,
  Dem_DTCRequestType ReqType, 
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_ResetIndicatorAttribute(
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  IndicatorAttr);

extern FUNC(void, DEM_CODE) 
  Dem_EvMem_InitIndicatorBehaviorAccumulator(void);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_GetIndicatorAttStatus(
  const Dem_EventIdType EventId,
  const Dem_NumOfIndicatorAttributeType IndicatorAttrId);
  
extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetIndicatorAttStatus(
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  IndicatorAtt,
  const boolean AttStatus);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetIndicatorFailureCounter(
  const Dem_NumOfIndicatorAttributeType FailureCounterId,
  const uint8 FailureCounter);

extern FUNC(boolean, DEM_CODE) 
Dem_EvMem_SetIndicatorHealingCounter(
  const Dem_NumOfIndicatorAttributeType HealingCounterId,
  const uint8 HealingCounter);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_IncreaseIndicatorFailureCounter(
  const Dem_NumOfIndicatorAttributeType FailureCounterId,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) CounterValue);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_IncreaseIndicatorHealingCounter(
  const Dem_NumOfIndicatorAttributeType HealingCounterId,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) CounterValue);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_DTCFormatIsValid(
    const Dem_DTCFormatType DTCFormat, Dem_CombinedDtcPCType CombinedDTC);

extern FUNC(Dem_EventMemoryEntryPtrType, DEM_CODE) Dem_AllocateEventMemoryEntry(
  Dem_EventIdType EventId,
  #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
  Dem_DTCType DTC,
  #endif
  Dem_DTCOriginType DTCOrigin
  );

extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetOccurrenceCounterProcessing(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(boolean, DEM_CODE) Dem_EvMem_GetDemTypeOfDTCSupported(
  uint8 ClientId, Dem_DTCTranslationFormatType *dtcFormatType
);

extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetEventDisplacementStrategy(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(uint16, DEM_CODE) Dem_EvMem_GetSizeOfElementEventMemory(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetStartIndexEventMemorySet(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetStopIndexEventMemorySet(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetNumOfStoredEvtMemEntries(
  Dem_EventIdType EventId, Dem_DTCOriginType DTCOrigin);

extern FUNC(uint16, DEM_CODE) Dem_EvMem_GetSizeOfEventMemory(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin);

extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetNumOfEvtMemFromDTCOrigin(
  uint8 EventMemSetIdx, Dem_DTCOriginType DTCOrigin);

extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetAvailableMaskFromMemSetIdx(
  uint8 MemSetId);

extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemEventMemoryEntryStorageTrigger(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(void, DEM_CODE) Dem_EvMem_ResetNumOfStoredEvtMemEntries(
  Dem_DTCOriginType DTCOrigin
);

extern FUNC(void, DEM_CODE) Dem_EvMem_IncreaseNumOfStoredEvtMemEntries(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  uint8 memSize
);

extern FUNC(void, DEM_CODE) Dem_EvMem_DecreaseNumOfStoredEvtMemEntries(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  uint8 memSize
);

extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetStartIndexEvMemory(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin
);
extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE)
Dem_EvMem_GetStopIndexEvMemory(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin);


#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO))
extern FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetJ1939FFBuffer (
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize,
  Dem_J1939DcmSetFreezeFrameFilterType J1939FFType);
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetJ1939LampStatus(
  Dem_EventIdType EventId,
  P2VAR (Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA) LampStatus);
#endif

#if((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
    (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
extern FUNC(boolean, DEM_CODE) Dem_EvMem_RegisterPermanentDTC(
  Dem_EventIdType EventId);
extern FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_FindPerMemLoc(
  Dem_EventIdType EventId);

extern FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentDTC(
  Dem_EventIdType EventId,
  boolean pfc);

extern FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentDTCAllCbEvents(
  Dem_EventIdType EventId, 
  boolean pfc);
  
extern FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentMemEntry(
  Dem_NumOfEventMemoryEntryType memLoc,
  Dem_EventIdType EventId);
#endif

#endif /* DEM_MAX_EVENT_DESTINATION_SELECTED */

extern FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_CopyMemoryEntries(
  Dem_EventMemoryEntryPtrType memEntryDest,
  Dem_EventMemoryEntryPtrType memEntrySrc);


extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetMILIndicator(uint8 memorySetID);

#if (DEM_J1939_SUPPORT == STD_ON)
extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemRedStopLampIndicatorRef(
  uint8 memorySetID);
extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemAmberWarningLampIndicatorRef(
  uint8 memorySetID);
extern FUNC(uint8, DEM_CODE) Dem_EvMem_GetDemProtectLampIndicatorRef(
  uint8 memorySetID);
#endif


#if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)||\
    (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)|| \
    (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO))
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetHighestMaximumFDC(
  Dem_EventIdType EventId,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) MaxFDC);
#endif

extern FUNC(boolean, DEM_CODE) Dem_EvMem_SetOpCycleQualifiedState(
  uint8 OperationCycleId,
  Dem_OperationCycleStateType state);

extern FUNC(void, DEM_CODE) Dem_EvMem_GetOpCycleQualifiedState(
  uint8 OperationCycleId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState);

/**************************************************
 *   Static Function Prototype Declaration
 **************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.5:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvMem_SetNvmResult(
  Std_ReturnType NvmResult)
{
  Dem_EvMemTrigger.nvmResult = NvmResult;
  /* @Trace: Dem_SUD_API_10900 */
}

static DEM_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_EvMem_GetNvmResult(void)
{
  return Dem_EvMemTrigger.nvmResult;
  /* @Trace: Dem_SUD_API_10901 */
}

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvMem_SetReadNvDataTrigger(
  boolean TriggerState)
{
  Dem_EvMemTrigger.readNvBlocksTrigger = TriggerState;
  /* @Trace: Dem_SUD_API_10902 */
}

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvMem_SetWriteNvDataTrigger(
  boolean TriggerState)
{
  Dem_EvMemTrigger.writeNvBlocksTrigger = TriggerState;
  /* @Trace: Dem_SUD_API_10903 */
}


static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvMem_SetWriteNvDataEndModeTrigger(
  uint8 TriggerState)
{
  Dem_EvMemTrigger.writeNvBlocksEndModeTrigger = TriggerState;
  /* @Trace: Dem_SUD_API_10904 */
}


static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvMem_SetWaitNvmFinishJobTrigger(
  boolean TriggerState)
{
  Dem_EvMemTrigger.waitNvBlocksJobFinishTrigger = TriggerState;
  /* @Trace: Dem_SUD_API_10905 */
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EvMem_ReadNvDataIsTriggered(void)
{
  return Dem_EvMemTrigger.readNvBlocksTrigger;
  /* @Trace: Dem_SUD_API_10906 */
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EvMem_WriteNvDataIsTriggered(void)
{
  return Dem_EvMemTrigger.writeNvBlocksTrigger;
  /* @Trace: Dem_SUD_API_10907 */
}

static DEM_INLINE FUNC(uint8, DEM_CODE)
Dem_EvMem_WriteNvDataEndModeTriggered(void)
{
  return Dem_EvMemTrigger.writeNvBlocksEndModeTrigger;
  /* @Trace: Dem_SUD_API_10908 */
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_NvmWaitFinishJobIsTrigger(void)
{
  return Dem_EvMemTrigger.waitNvBlocksJobFinishTrigger;
  /* @Trace: Dem_SUD_API_10909 */
}

/*
 * Event memory entries's status
 */
static DEM_INLINE FUNC(boolean , DEM_CODE) Dem_EvMem_IsEvMemNvBlockStatusFilter(
  const Dem_DTCOriginType DTCOrigin, 
  const Dem_NumOfEventMemoryEntryType MemLocation,
  const uint8 Filter)
{
  boolean LblMatchFilter = DEM_FALSE;
  CONSTP2VAR(uint8, AUTOMATIC, DEM_CONST) LpEvMemStatus =
     (DEM_TRUE != DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin)) ?
      Dem_EventMemoryState[DTCOrigin]:
      Dem_EventMemoryState[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
  /* @Trace: Dem_SUD_API_10910 */
  if (NULL_PTR != LpEvMemStatus)
  {
    /* @Trace: Dem_SUD_API_10911 */
    if ((LpEvMemStatus[MemLocation] & Filter) == Filter)
    {
      /* @Trace: Dem_SUD_API_10912 */
      LblMatchFilter = DEM_TRUE;
    }
  }
  return LblMatchFilter;
}

/* NOTE: DTCOrigin , DTCOrigin shall be verified by caller */
static DEM_INLINE FUNC(void , DEM_CODE) Dem_EvMem_SetEvMemNvBlockStatus(
  Dem_DTCOriginType DTCOrigin,
  Dem_NumOfEventMemoryEntryType MemLocation,
  uint8 EvMemStatus)
{
  CONSTP2VAR(uint8, AUTOMATIC, DEM_CONST) LpEvMemStatusList =
        (DEM_TRUE != DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin)) ?
          Dem_EventMemoryState[DTCOrigin] :
          Dem_EventMemoryState[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
  /* @Trace: Dem_SUD_API_10914 */
  if (NULL_PTR != LpEvMemStatusList)
  {
    #if(DEM_NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_BlockIdType BlockId = 0U;
    if(E_OK == Dem_NvData_GetNvMBlockId(DEM_NVDATA_EVENT_MEMORY_ID, DTCOrigin, MemLocation, &BlockId))
    {
      /* @Trace: Dem_SUD_API_13333 */
      NvM_SetRamBlockStatus(BlockId, DEM_TRUE);
    }
    #endif
    /* @Trace: Dem_SUD_API_10913 */
    LpEvMemStatusList[MemLocation] |= EvMemStatus;
  }
}

/* NOTE: DTCOrigin , DTCOrigin shall be verified by caller */
static DEM_INLINE FUNC(void , DEM_CODE) Dem_EvMem_InitEvMemNvBlockStatus(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation,
  const uint8 EvMemStatus)
{
  CONSTP2VAR(uint8, AUTOMATIC, DEM_CONST) LpEvMemStatusList =
      (DEM_TRUE != DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin)) ?
          Dem_EventMemoryState[DTCOrigin] :
          Dem_EventMemoryState[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
  /* @Trace: Dem_SUD_API_10916 */
  if (NULL_PTR != LpEvMemStatusList)
  {
    /* @Trace: Dem_SUD_API_10915 */
    LpEvMemStatusList[MemLocation] = EvMemStatus;
  }
}

/* NOTE: DTCOrigin , DTCOrigin shall be verified by caller */
static DEM_INLINE FUNC(void , DEM_CODE) Dem_EvMem_ClearEvMemNvBlockStatus(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation,
  const uint8 EvMemStatus)
{
  CONSTP2VAR(uint8, AUTOMATIC, DEM_CONST) LpEvMemStatusList =
       (DEM_TRUE != DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin)) ?
           Dem_EventMemoryState[DTCOrigin] :
           Dem_EventMemoryState[DEM_DTC_ORIGIN_USERDEFINED_MEMORY];
  /* @Trace: Dem_SUD_API_10012 */
  if (NULL_PTR != LpEvMemStatusList)
  {
    /* @Trace: Dem_SUD_API_10917 */
    LpEvMemStatusList[MemLocation] =
        LpEvMemStatusList[MemLocation] & ((uint8)(~EvMemStatus));
  }
}

/*
 * Non-volatile data's status
 */

static DEM_INLINE FUNC(boolean , DEM_CODE) 
Dem_EvMem_NonVolatieDataStatusFilter(
  const Dem_NvDataIdType NvDataId,  
  const uint8 Filter)
{
  boolean LblMatchFilter;
  if ((Dem_NonVolatileDataState[NvDataId] & Filter) == Filter)
  {
    /* @Trace: Dem_SUD_API_10918 */
    LblMatchFilter = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_10919 */
    LblMatchFilter = DEM_FALSE;
  }
  return LblMatchFilter;
}

/* NOTE: DTCOrigin , DTCOrigin shall be verified by caller */
static DEM_INLINE FUNC(void , DEM_CODE) Dem_EvMem_SetNonVolatieDataStatus(
  const Dem_NvDataIdType NvDataId,  
  const uint8 EvMemStatus)
{
  #if(DEM_NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
  NvM_BlockIdType BlockId = 0U;
  /* Second and third parameters have no meaning in case NvDataId is different than DEM_NVDATA_EVENT_MEMORY_ID */
  if(E_OK == Dem_NvData_GetNvMBlockId(NvDataId, 1U, 1U, &BlockId))
  {
    /* @Trace: Dem_SUD_API_13332 */
    NvM_SetRamBlockStatus(BlockId, DEM_TRUE);
  }
  #endif
  /* @Trace: Dem_SUD_API_10920 */
  Dem_NonVolatileDataState[NvDataId] |= EvMemStatus;
}

/* NOTE: DTCOrigin , DTCOrigin shall be verified by caller */
static DEM_INLINE FUNC(void , DEM_CODE) Dem_EvMem_InitNonVolatieDataStatus(
  const Dem_NvDataIdType NvDataId,  
  const uint8 EvMemStatus)
{
  Dem_NonVolatileDataState[NvDataId] = EvMemStatus;
  /* @Trace: Dem_SUD_API_10921 */
}

/* NOTE: DTCOrigin , DTCOrigin shall be verified by caller */
static DEM_INLINE FUNC(void , DEM_CODE) Dem_EvMem_ClearNonVolatieDataStatus(
  const Dem_NvDataIdType NvDataId,  
  const uint8 EvMemStatus)
{
  Dem_NonVolatileDataState[NvDataId] &= (uint8)(~EvMemStatus);
  /* @Trace: Dem_SUD_API_10922 */
}

/* @Trace: SRS_Diag_04065 SRS_Diag_04194
 */
static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EvMem_WaitClearAllBlocks(
  P2VAR(Std_ReturnType, AUTOMATIC,DEM_VAR) ClearDtcReturnValue)
{  
  boolean LblRetVal;
  #if (DEM_CLEAR_DTC_BEHAVIOUR == DEM_CLRRESP_NONVOLATILE_FINISH)
  LblRetVal = Dem_NvmWaitFinishJobIsTrigger();
  /* @Trace: Dem_SUD_API_10926 */
  if (DEM_FALSE == LblRetVal)
  {
    if (E_NOT_OK == Dem_EvMem_GetNvmResult())
    {
      /* @Trace: SWS_Dem_01057
       * If the Dem module is requested to clear diagnostic information and the
       * configuration parameter DemClearDTCBehavior is set
       * to DEM_CLRRESP_NONVOLATILE_FINISH, the Dem module shall return
       * DEM_CLEAR_MEMORY_ERROR if the clearing of the non-volatile memory
       * fails. */
      /* @Trace: Dem_SUD_API_10013 */
      *ClearDtcReturnValue = DEM_CLEAR_MEMORY_ERROR;
    }
    else
    {
      /* @Trace: SWS_Dem_00572
       * If the Dem module is requested to clear diagnostic information and the
       * configuration parameter DemClearDTCBehavior is set to
       * DEM_CLRRESP_NONVOLATILE_FINISH, the Dem module shall return E_OK
       * after the volatile memory and the non-volatile memory is cleared.
       * */
      /* @Trace: Dem_SUD_API_10924 */
      *ClearDtcReturnValue = E_OK;
    }
  }
  #elif  (DEM_CLEAR_DTC_BEHAVIOUR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
  /* @Trace: SWS_Dem_00571
   * If the Dem module is requested to clear diagnostic information and the
   * configuration parameter DemClearDTCBehavior is set to
   * DEM_CLRRESP_NONVOLATILE_TRIGGER, the Dem module shall return E_OK after
   * the volatile memory is cleared and clearing of the non-volatile memory is
   * triggered
   * */
  /* @Trace: Dem_SUD_API_10923 */
  LblRetVal = Dem_EvMem_WriteNvDataIsTriggered();
  /* @Trace: Dem_SUD_API_10927 */
  if ((boolean)DEM_FALSE == LblRetVal)
  {
    /* Don't care return value of NvM */
    /* @Trace: Dem_SUD_API_10928 */
    *ClearDtcReturnValue = E_OK;
  }
  #else
  {
    /* @Trace: SWS_Dem_00570
     * If the Dem module is requested to clear diagnostic information and the
     * configuration parameter DemClearDTCBehavior is set to
     * DEM_CLRRESP_VOLATILE, the Dem module shall return E_OK after the
     * volatile memory is cleared.
     * */
    /* Don't care return value of NvM */
    /* @Trace: Dem_SUD_API_10925 */
    *ClearDtcReturnValue = E_OK;
    LblRetVal = DEM_FALSE;
  }
  #endif    

  return LblRetVal;
}

/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:8.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:8.5:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */

/**************************************************/
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*************************************************/

#endif

