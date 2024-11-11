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
**  PURPOSE   : C header for Dem_Config.c                                     **
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

#ifndef DEM_CONFIG_H
#define DEM_CONFIG_H
/* @IF_REQ : Check range */
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary
 * in logic */

#include "Dem_PCTypes.h"
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#ifdef DEM_MAX_NUMBER_OF_PID_DATAELEMENT
extern const Dem_NumOfPidDataElementType Dem_Max_Number_Of_Pid_DataElement;
#endif

/* Configuration Range : 1 ~ 256 , but 255  */
#ifdef DEM_NUMBER_OPERATION_CYCLES
extern const uint8  Dem_Num_Operation_Cycles;
#endif

#ifdef DEM_MAX_NUM_GRP_DTC
extern const uint8  Dem_Max_Num_Grp_DTC;
#endif

#ifdef DEM_IMMEDIATE_NV_STORAGE_LIMIT
extern const uint8  Dem_Immdiate_Nv_Storage_Limit;
#endif

#ifdef DEM_MAX_NUMBER_EVENT_ENTRY_MIR
extern const uint8 Dem_Max_Number_Event_Entry_Mir;
#endif

#ifdef DEM_MAX_NUMBER_EVENT_ENTRY_PRI
extern const uint8 Dem_Max_Number_Event_Entry_Pri;
#endif

#ifdef DEM_MAX_NUMBER_EVENT_ENTRY_PER
extern const uint8 Dem_Max_Number_Event_Entry_Per;
#endif

#ifdef DEM_TASK_TIME
extern const uint16 Dem_Task_Time;
#endif

#ifdef DEM_MIL_INDICATORID
extern const uint8 Dem_MIL_IndicatorId;
#endif

#ifdef DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL
extern const Dem_NumOfDebounceType Dem_Number_Of_Pre_Debounce_Monitor_Internal;
#endif

#ifdef DEM_AGING_REQUIERES_TESTED_CYCLE
extern const boolean Dem_CfgAgingRequieresTestedCycle;
#endif

#if(DEM_NUMBER_OF_INDICATORS == DEM_ZERO)
extern P2CONST(Dem_IndicatorAttributeType, AUTOMATIC, DEM_CONST)
    Dem_GaaIndicatorList;
#endif

#ifdef DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID 
extern const Dem_NumOfEventMemoryEntryType
             Dem_Num_Of_Primary_EventMemory_NvBlockId;
#endif

#ifdef DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID
extern const Dem_NumOfEventMemoryEntryType
                  Dem_Num_Of_Userdefined_EventMemory_NvBlockId;
#endif

#ifdef DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID
extern const Dem_NumOfEventMemoryEntryType
                      Dem_Num_Of_Permanent_EventMemory_NvBlockId;
#endif
/* @Trace: Dem_SUD_MACRO_145 */
#ifdef DEM_NUM_OF_EXTENDEDDATARECORDCLASS
extern const uint16 Dem_Num_Of_ExtendedDataRecordClass;
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
#ifdef DEM_NUM_OF_J1939FREEZEFRAMECLASS
extern const Dem_NumOfJ1939FreezeFrameClassType
                   Dem_Num_Of_J1939FreezeFrameClass;
#endif
#endif


#ifdef DEM_SIZE_OF_EXTENDED_DATA
extern const uint32 Dem_Size_Of_Extended_Data;
#endif

#ifdef DEM_MAX_LISTOFEDRECORDCLASSINDEX
extern const uint16 Dem_Max_ListOfEDRecordClassIndex;
#endif

#ifdef DEM_MAX_LISTOFDIDCLASSINDEX
extern const uint16 Dem_Max_ListOfDidClassIndex;
#endif

#ifdef DEM_MAX_LISTOFSPNCLASSINDEX
extern const uint16 Dem_Max_ListOfSpnClassIndex;
#endif

#ifdef DEM_MAX_NUM_OF_EVENT_STAT_CHNG_FCTS
extern const Dem_NumOfEvtStatFctsType Dem_Max_ListOfEvtStatusChangedFctPtr;
#endif

extern const boolean Dem_Status_Bit_Storage_TestFailed;
extern const boolean Dem_Aging_Requieres_Tested_Cycle;
extern const boolean Dem_Healing_Requieres_Tested_Cycle;

#ifdef DEM_OBD_UDS_DTC_SEPARATION_SUPPORT
extern const boolean Dem_ObdUdsDtc_Separation_Support;
#endif


#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"




/*******************************************************************************
**                      Function Prototype                                    **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
extern FUNC(void, DEM_CODE) 
Dem_SetEventIdOfPrestoredFF(
  Dem_NumOfPrestoredFFType BufferIndex,
  const Dem_EventIdType EventId);

extern FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE)
Dem_GetBufferOfPrestoredFF(
  const Dem_EventIdType EventId,
  P2VAR(Dem_NumOfPrestoredFFType, AUTOMATIC, DEM_VAR) BufferIndex);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearSinglePrestoredFFbyEventId(Dem_EventIdType EventId);
#endif

#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
extern FUNC(void, DEM_CODE)
Dem_SetStorageConditionStatus(uint8 storIndex, boolean state);

extern FUNC(void, DEM_CODE)
Dem_InitStorageConditionStatus(void);
#endif

#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)  
extern FUNC_P2CONST(Dem_PreDebounceTimeBasedType, DEM_CONST, DEM_CODE)
Dem_GetCfgDebounceTimer(Dem_NumOfDebounceType DebounceId);

extern FUNC_P2VAR(Dem_TimeDebounceStatusType, DEM_VAR, DEM_CODE)
Dem_GetDebounceTimerStatus(Dem_NumOfDebounceType DebounceId);
#endif

extern FUNC(void, DEM_CODE)
Dem_SetEnableConditionStatus(uint8 condIndex, boolean state);

extern FUNC(void, DEM_CODE)
Dem_InitEnableConditionStatus(void);


extern FUNC(boolean, DEM_CODE)
Dem_GetStorageConditionStatus(uint16 storIndex);

extern FUNC(boolean, DEM_CODE)
Dem_GetEnableConditionStatus(uint16 condIndex);

extern FUNC_P2CONST(Dem_IndicatorAttributeType, DEM_CONST, DEM_CODE)
Dem_GetCfgIndicatorAtt(Dem_NumOfIndicatorAttributeType IndicatorAttrId);

extern FUNC(void, DEM_CODE) Dem_InitEventFailureThreshold (void);
/**************************************************/
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary
 * in logic */

#endif
