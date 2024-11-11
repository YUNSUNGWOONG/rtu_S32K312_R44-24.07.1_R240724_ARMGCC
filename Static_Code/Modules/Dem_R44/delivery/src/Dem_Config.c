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
**  SRC-MODULE: Dem_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Declares the global variables for configurable values         **
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
** 2.1.0.0   31-Mar-2024   EK Kim        Jira #CP44-4075                      **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dem.h" 
#include "Dem_Ram.h"    /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */
#include "Rte_Dem.h"
#include "Dem_NvData.h"
#include "Dem_Config.h"
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Dem_SUD_MACRO_075 */
#ifdef DEM_MAX_NUMBER_OF_PID_DATAELEMENT
const Dem_NumOfPidDataElementType Dem_Max_Number_Of_Pid_DataElement =
            DEM_MAX_NUMBER_OF_PID_DATAELEMENT;
#endif

/* Configuration Range : 1 ~ 256 , but 255  */
#ifdef DEM_NUMBER_OPERATION_CYCLES
const uint8  Dem_Num_Operation_Cycles = DEM_NUMBER_OPERATION_CYCLES;
#endif


#ifdef DEM_MAX_NUM_GRP_DTC
const uint8  Dem_Max_Num_Grp_DTC = DEM_MAX_NUM_GRP_DTC;
#endif

/* @Trace: Dem_SUD_MACRO_024 */
#ifdef DEM_IMMEDIATE_NV_STORAGE_LIMIT
const uint8  Dem_Immdiate_Nv_Storage_Limit = DEM_IMMEDIATE_NV_STORAGE_LIMIT;
#endif

#ifdef DEM_MAX_NUMBER_EVENT_ENTRY_MIR
const uint8 Dem_Max_Number_Event_Entry_Mir = DEM_MAX_NUMBER_EVENT_ENTRY_MIR;
#endif

#ifdef DEM_MAX_NUMBER_EVENT_ENTRY_PRI
const uint8 Dem_Max_Number_Event_Entry_Pri = DEM_MAX_NUMBER_EVENT_ENTRY_PRI;
#endif

/* @Trace: Dem_SUD_MACRO_028 */
#ifdef DEM_MAX_NUMBER_EVENT_ENTRY_PER
const uint8 Dem_Max_Number_Event_Entry_Per = DEM_MAX_NUMBER_EVENT_ENTRY_PER;
#endif

#ifdef DEM_TASK_TIME
const uint16 Dem_Task_Time = DEM_TASK_TIME;
#endif


#ifdef DEM_MIL_INDICATORID
const uint8 Dem_MIL_IndicatorId = DEM_MIL_INDICATORID;
#endif

#ifdef DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID 
const Dem_NumOfEventMemoryEntryType Dem_Num_Of_Primary_EventMemory_NvBlockId =
    DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID;
#endif

#ifdef DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID
const Dem_NumOfEventMemoryEntryType
       Dem_Num_Of_Userdefined_EventMemory_NvBlockId =
           DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID;
#endif

#ifdef DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID
const Dem_NumOfEventMemoryEntryType Dem_Num_Of_Permanent_EventMemory_NvBlockId
        = DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID;
#endif


#ifdef DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL
const Dem_NumOfDebounceType Dem_Number_Of_Pre_Debounce_Monitor_Internal =
    DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL;
#else
const Dem_NumOfDebounceType Dem_Number_Of_Pre_Debounce_Monitor_Internal =
    DEM_ZERO;
#endif
/* @Trace: Dem_SUD_MACRO_047 */
#ifdef DEM_AGING_REQUIERES_TESTED_CYCLE
const boolean Dem_CfgAgingRequieresTestedCycle =
                (boolean)DEM_AGING_REQUIERES_TESTED_CYCLE;
#endif


#if (DEM_NUMBER_OF_INDICATORS == DEM_ZERO)
P2CONST(Dem_IndicatorAttributeType,AUTOMATIC, DEM_CONST) Dem_GaaIndicatorList
    = NULL_PTR;
#endif


#ifdef DEM_NUM_OF_EXTENDEDDATARECORDCLASS
const uint16 Dem_Num_Of_ExtendedDataRecordClass =
    DEM_NUM_OF_EXTENDEDDATARECORDCLASS;
#endif 

#if (DEM_J1939_SUPPORT == STD_ON)
#ifdef DEM_NUM_OF_J1939FREEZEFRAMECLASS
const Dem_NumOfJ1939FreezeFrameClassType Dem_Num_Of_J1939FreezeFrameClass =
    DEM_NUM_OF_J1939FREEZEFRAMECLASS;
#endif
#endif


#ifdef DEM_SIZE_OF_EXTENDED_DATA
const uint32 Dem_Size_Of_Extended_Data = DEM_SIZE_OF_EXTENDED_DATA;
#endif

#ifdef DEM_MAX_LISTOFEDRECORDCLASSINDEX
const uint16 Dem_Max_ListOfEDRecordClassIndex =
    DEM_MAX_LISTOFEDRECORDCLASSINDEX;
#endif

#ifdef DEM_MAX_LISTOFDIDCLASSINDEX
const uint16 Dem_Max_ListOfDidClassIndex = DEM_MAX_LISTOFDIDCLASSINDEX;
#endif

#ifdef DEM_MAX_LISTOFSPNCLASSINDEX
const uint16 Dem_Max_ListOfSpnClassIndex = DEM_MAX_LISTOFSPNCLASSINDEX;
#endif

/* @Trace: Dem_SUD_MACRO_078 */
#ifdef DEM_MAX_NUM_OF_EVENT_STAT_CHNG_FCTS
const Dem_NumOfEvtStatFctsType Dem_Max_ListOfEvtStatusChangedFctPtr =
    DEM_MAX_NUM_OF_EVENT_STAT_CHNG_FCTS;
#endif


const boolean Dem_Status_Bit_Storage_TestFailed =
    DEM_STATUS_BIT_STORAGE_TESTFAILED;


const boolean Dem_Aging_Requieres_Tested_Cycle =
    DEM_AGING_REQUIERES_TESTED_CYCLE;
/* @Trace: Dem_SUD_MACRO_048 */
const boolean Dem_Healing_Requieres_Tested_Cycle =
    DEM_HEALING_REQUIERES_TESTED_CYCLE;

#ifdef DEM_OBD_UDS_DTC_SEPARATION_SUPPORT
const boolean Dem_ObdUdsDtc_Separation_Support = DEM_OBD_UDS_DTC_SEPARATION_SUPPORT;
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
 **                   Static Function Definitions                             **
 ******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dem_SetEventIdOfPrestoredFF
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Set the Event identifier of a specific entry to 
**                        EventId.
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : BufferIndex, EventId
**                                                                            
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : void
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              :                                                
*******************************************************************************/
#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
FUNC(void, DEM_CODE) 
Dem_SetEventIdOfPrestoredFF(
  Dem_NumOfPrestoredFFType BufferIndex,
  const Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_20960 */
  Dem_GaaPrestoreBuffer[BufferIndex].EventIdRef = EventId;
}

/*******************************************************************************
** Function Name        : Dem_GetBufferOfPrestoredFF                          
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : It is used to get the buffer address and BufferIndex 
**                        index of buffer corresponding to EventId in the 
**                        prestored buffer in which freeze frames are stored. 
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : EventId                                             
**                                                                            
** InOut parameter      : None                                         
**                                                                            
** Output Parameters    : BufferIndex                                              
**                                                                            
** Return parameter     : uint8                                                
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              :                                      
*******************************************************************************/
FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE)
Dem_GetBufferOfPrestoredFF(
  const Dem_EventIdType EventId,
  P2VAR(Dem_NumOfPrestoredFFType, AUTOMATIC, DEM_VAR) BufferIndex)
{
  Dem_NumOfPrestoredFFType LddIndex;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpBuffer = NULL_PTR;
  /* @Trace: Dem_SUD_API_20964 */
  for (LddIndex = DEM_ZERO; LddIndex < DEM_MAX_NUMBER_PRESTORED_FF; LddIndex++)
  {
    /* @Trace: Dem_SUD_API_20961 */
    if (Dem_GaaPrestoreBuffer[LddIndex].EventIdRef == EventId)
    {
      #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
      LpBuffer = Dem_GaaPrestoreBuffer[LddIndex].data;
      /* @Trace: Dem_SUD_API_20965 */
      if (NULL_PTR != BufferIndex)
      {
        /* @Trace: Dem_SUD_API_20963 */
        *BufferIndex = LddIndex;
      }
      #else
      /* @Trace: Dem_SUD_API_20962 */
      DEM_UNUSED(BufferIndex);
      #endif
      
      break;
    }
  }

  return LpBuffer;
}

/*******************************************************************************
** Function Name        : Dem_ClearSinglePrestoredFFbyEventId                           
**                                                                            
** Service ID           : None                                                
**                                                                            
** Description          : Clears a prestored freeze frame of a specific event. 
**                                                                            
** Sync/Async           : Synchronous                                         
**                                                                            
** Re-entrancy          : Reentrant                                           
**                                                                            
** Input Parameters     : EventId
**                                                                            
** InOut parameter      : None
**                                                                            
** Output Parameters    : None
**                                                                            
** Return parameter     : Std_ReturnType
**                                                                            
** Preconditions        : None                                                
**                                                                            
** Remarks              :                   
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_071 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearSinglePrestoredFFbyEventId(Dem_EventIdType EventId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint32 LulIndex;

  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates
   * to true or false according to configuration */
  /* @Trace: Dem_SUD_API_20003 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    Dem_EventParameterCPCType event = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_20004 */
    if (event->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
    {
      Dem_EventRelatedDataCPCType EvData = &Dem_EventRelatedData[
                     event->e_PointToData];
      /* @Trace: Dem_SUD_API_20972 */
      if ((EvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS))
      {
        /* @Trace: Dem_SUD_API_20971 */
        if (DEM_TRUE == EvData->FFPreStorageSupported)
        {              
          /* @Trace: Dem_SUD_API_20970 */
          for (LulIndex = DEM_ZERO; LulIndex < DEM_MAX_NUMBER_PRESTORED_FF;
               LulIndex++)
          {
            /* @Trace: Dem_SUD_API_20967 */
            if (Dem_GaaPrestoreBuffer[LulIndex].EventIdRef == EventId)
            {
              /* @Trace: Dem_SUD_API_20968 */
              #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
              uint32 LulIdx;
              /* @Trace: Dem_SUD_API_20969 */
              /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Not a defect:Justify with annotations */
              for ( LulIdx = DEM_ZERO; LulIdx < DEM_SIZE_OF_PRESTORED_FF;
                    LulIdx++)
              {
                /* @Trace: Dem_SUD_API_20966 */
                Dem_GaaPrestoreBuffer[LulIndex].data[LulIdx] = DEM_SET_BYTE;
              }              
              #endif
              Dem_GaaPrestoreBuffer[LulIndex].EventIdRef = DEM_NO_EVENT;

              LddRetVal = E_OK;
              break;
            }
          }
        }
      }
    }
  }
  return LddRetVal;
}
#endif

/******************************************************************************
 * Function Name        : Dem_SetStorageConditionStatus
 *
 * Service ID           : None
 *
 * Description          : Sets the state of the storage condition
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : storIndex, state
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
 *                        Dem_GaaStorageConditionStatus
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
FUNC(void, DEM_CODE)
Dem_SetStorageConditionStatus(uint8 storIndex, boolean state)
{
  /* @Trace: Dem_SUD_API_20974 */
  #if (DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20973 */
  Dem_GaaStorageConditionStatus[storIndex] = state;
  #endif
}

/******************************************************************************
 * Function Name        : Dem_InitStorageConditionStatus
 *
 * Service ID           : None
 *
 * Description          : Resets the state of the storage conditions
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : index, state
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
 *                        DEM_NUMBER_STORAGE_CONDITION
 *                        Dem_GaaStorageConditionStatus
 *                        Dem_GaaStorageCondition
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_InitStorageConditionStatus(void)
{
  /* @Trace: Dem_SUD_API_20977 */
  #if (DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO)
  uint8 LucStorIndex = DEM_ZERO;
  /* @Trace: Dem_SUD_API_20976 */
  for ( LucStorIndex = DEM_ZERO;
        LucStorIndex < DEM_NUMBER_STORAGE_CONDITION;
        LucStorIndex++)
  {
    /* @Trace: Dem_SUD_API_20975 */
    Dem_GaaStorageConditionStatus[LucStorIndex] =
         Dem_GaaStorageCondition[LucStorIndex].blDemStrCondStt;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_GetStorageConditionStatus
 *
 * Service ID           : None
 *
 * Description          : Gets the state of the storage condition
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : storIndex
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
 *                        Dem_GaaStorageConditionStatus
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
FUNC(boolean, DEM_CODE)
Dem_GetStorageConditionStatus(uint16 storIndex)
{
  boolean LblStatus = DEM_TRUE;

  #if ((DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO) && \
       (DEM_MAX_LISTOFSTORAGECONDITIONID > DEM_ZERO))
  /* @Trace: Dem_SUD_API_20978 */
  LblStatus = Dem_GaaStorageConditionStatus[
               Dem_ListOfStorageConditionId[storIndex]];
  #else
  /* @Trace: Dem_SUD_API_20979 */
  DEM_UNUSED(storIndex);
  #endif
  
  return LblStatus;
}
#endif

/******************************************************************************
 * Function Name        : Dem_SetEnableConditionStatus
 *
 * Service ID           : None
 *
 * Description          : Set the state of the enable conditions
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : condIndex, state
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
 *                        Dem_EnableConditionStatus
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
#if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_SetEnableConditionStatus(
    uint8 condIndex ,
    boolean state)
{
  /* @Trace: Dem_SUD_API_20981 */
  #if (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20980 */
  Dem_EnableConditionStatus[condIndex] = state;
  #endif
}

/******************************************************************************
 * Function Name        : Dem_InitEnableConditionStatus
 *
 * Service ID           : None
 *
 * Description          : Resets the state of the enable conditions
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
 *                        Dem_Num_Enable_Condition
 *                        Dem_GaaEnableCondition
 *                        Dem_EnableConditionStatus
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_InitEnableConditionStatus(void)
{
  /* @Trace: Dem_SUD_API_20982 */
  #if (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20983 */
  for ( uint8 LucCondIndex = DEM_ZERO;
        LucCondIndex < DEM_NUMBER_ENABLE_CONDITION;
        LucCondIndex++)
  {
    /* @Trace: Dem_SUD_API_20984 */
    Dem_EnableConditionStatus[LucCondIndex] =
         Dem_GaaEnableCondition[LucCondIndex];
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_GetEnableConditionStatus
 *
 * Service ID           : None
 *
 * Description          : Gets the state of the enable condition
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : condIndex
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
 *                        Dem_EnableConditionStatus
 *
 *                        Function(s) invoked :
 *                        None
 *
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_GetEnableConditionStatus(uint16 condIndex)
{
  boolean LblStatus = DEM_TRUE;

  #if ((DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO) && \
       (DEM_MAX_LISTOFENABLECONDITIONID > DEM_ZERO))
  /* @Trace: Dem_SUD_API_20986 */
  LblStatus = Dem_EnableConditionStatus[
               Dem_ListOfEnableConditionId[condIndex]];
  #else
  /* @Trace: Dem_SUD_API_20985 */
  DEM_UNUSED(condIndex);
  #endif
  
  return LblStatus;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetCfgDebounceTimer                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Returns the structure variables of                  **
**                        time based debounce                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DebounceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_PreDebounceTimeBasedType*                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GaaPreDebounceTimeBased                         **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)  
FUNC_P2CONST(Dem_PreDebounceTimeBasedType, DEM_CONST, DEM_CODE)
Dem_GetCfgDebounceTimer(Dem_NumOfDebounceType DebounceId)
{
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) LddTimerConf =
      NULL_PTR;
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20127 */
  if (DebounceId < DEM_NUMBER_OF_PRE_DEBOUNCE_TIME)
  {
    /* @Trace: Dem_SUD_API_20988 */
    LddTimerConf = &Dem_GaaPreDebounceTimeBased[DebounceId];
  }
  #else
  /* @Trace: Dem_SUD_API_20987 */
  DEM_UNUSED(DebounceId);
  #endif
  
  return LddTimerConf;
}

/*******************************************************************************
** Function Name        : Dem_GetDebounceTimerStatus                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Get debounce timer status                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DebounceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_TimeDebounceStatusType                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
FUNC_P2VAR(Dem_TimeDebounceStatusType, DEM_VAR, DEM_CODE)
Dem_GetDebounceTimerStatus(
  Dem_NumOfDebounceType DebounceId)
{
  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
      NULL_PTR;

  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20128 */
  if (DebounceId < DEM_NUMBER_OF_PRE_DEBOUNCE_TIME)
  {
    /* @Trace: Dem_SUD_API_20990 */
    LddTimerStatus = &Dem_BasedTimeDebounceStatus[DebounceId];
  }
  #else
  /* @Trace: Dem_SUD_API_20989 */
  DEM_UNUSED(DebounceId);
  #endif

  return LddTimerStatus;
}

#endif

/******************************************************************************
 * Function Name        : Dem_GetCfgIndicatorAtt
 *
 * Service ID           : None
 *
 * Description          : Gets the indicator attribute type of indicator 
 *                        attribute id
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : IndicatorAttrId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_IndicatorAttributeType
 *
 * Preconditions        : None
 *
 * Remarks              :
 *                        Global Variable(s)  :
 *                        Dem_EventRelatedData
 *
 *                        Function(s) invoked :
 *****************************************************************************/
FUNC_P2CONST(Dem_IndicatorAttributeType, DEM_CONST, DEM_CODE)
Dem_GetCfgIndicatorAtt(Dem_NumOfIndicatorAttributeType IndicatorAttrId)
{
  DEM_UNUSED(IndicatorAttrId);
  #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20991 */
  return &Dem_GaaIndicatorList[IndicatorAttrId];
  #else
  /* @Trace: Dem_SUD_API_20992 */
  return NULL_PTR;
  #endif
}

/*******************************************************************************
** Function Name        : Dem_InitEventFailureThreshold                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Initialize the event failure threshold of all Event **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GaaEventAvailableBuffer                         **
**                        Dem_Number_Of_Event                                 **
**                        Function(s) invoked : None                          **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_InitEventFailureThreshold(void)
{
  /* @Trace: Dem_SUD_API_20993 */
  #if (DEM_NUMBER_OF_EVENTS > DEM_ZERO)
  Dem_EventParameterPCType LddEvent = NULL_PTR;
  /* @Trace: Dem_SUD_API_20994 */
  for ( Dem_EventIdType LddEventIndex = DEM_ONE;
        LddEventIndex <= DEM_NUMBER_OF_EVENTS;
        LddEventIndex++)
  {
    /* @Trace: Dem_SUD_API_20995 */
    LddEvent = &Dem_Event[LddEventIndex - DEM_ONE];
    Dem_GaaEventFailureThreshold[LddEventIndex] =
        LddEvent->usDemEventConfirmationThreshold;
  }
  #endif
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"



