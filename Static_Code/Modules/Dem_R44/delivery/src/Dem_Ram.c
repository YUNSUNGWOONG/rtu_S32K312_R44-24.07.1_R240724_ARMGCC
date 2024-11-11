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
**  SRC-MODULE: Dem_Ram.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Defining Global Variables                                     **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* Dem module header file */
#include "NvM.h"        /* NVRAM manager symbols Header File */
#include "Dem_Ram.h"    /* Dem global Ram variables header file */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#include "Dem_ObdRam.h" /* Dem global Ram variables header file for OBD */
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*************************************************************************
 * VAR INIT_UNSPECIFIED
 ************************************************************************/
#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/* Dem_BasedTimeDebounceStatus is updated in the Dem_PreInit */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_EvMemTriggerType, DEM_VAR) Dem_EvMemTrigger;
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
/* Dem_BasedTimeDebounceStatus is updated in the Dem_EvMem_Init */
VAR(Dem_ClearDtcStateType, DEM_VAR) Dem_ClearDtcState[DEM_NUMBER_OF_DEM_CLIENT];

/* Dem_BasedTimeDebounceStatus is updated in the Dem_SetDTCFilter */
/* polyspace +2 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_DTCFilterStateType, DEM_VAR)
Dem_DTCFilterState[DEM_NUMBER_OF_DEM_CLIENT];
#endif

/* Dem_AllEventStatusByte is updated in the Dem_EvMem_Init */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_UdsStatusByteType, DEM_VAR) Dem_AllEventStatusByte
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];

/* Dem_UDSProcsessState is updated in the Dem_EvMem_Init */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_UdsStatusByteType, DEM_VAR) Dem_UDSProcsessState
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];

/* @Trace: SRS_Diag_04067
 */
/* @Trace: SWS_Dem_01278
 * The Dem shall provide a monitor status per event to store current monitor
 * state information. The monitor status contains the information as defined
 * in Dem_MonitorStatusType. */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_MonitorStatusType, DEM_VAR) Dem_AllMonitorStatus
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];

/* Dem_BasedTimeDebounceStatus is updated in the Dem_PreInit */
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
VAR(Dem_TimeDebounceStatusType, DEM_VAR) Dem_BasedTimeDebounceStatus
  [DEM_NUMBER_OF_PRE_DEBOUNCE_TIME];
#endif
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
/* APIs is updated in the Dem_SelectDTC */
VAR(Dem_SelectDtcStateType, DEM_VAR)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
Dem_ClientSelectDtcState[DEM_NUMBER_OF_DEM_CLIENT];
/* APIs is updated in the Dem_SelectFreezeFrameData */
VAR(Dem_SelectFreezeFrameDataStateType, DEM_VAR)
Dem_ClientSelectFreezeFrameData[DEM_NUMBER_OF_DEM_CLIENT];
/* APIs is updated in the Dem_SelectExtendedDataRecord */
VAR(Dem_SelectExtendedDataRecordType, DEM_VAR)
Dem_ClientSelectExtendedDataRecord[DEM_NUMBER_OF_DEM_CLIENT];
#endif
#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * VAR_NO_INIT_UNSPECIFIED
 ************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

VAR(Dem_GenericNvRamDataType, DEM_VAR_NOINIT) Dem_NonVolatileData;
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_EventStatusNvRamDataType, DEM_VAR_NOINIT) Dem_EventStatusNvRamData;

/* Primary Event Memory variable : */
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > DEM_ZERO)
/* @Trace: Dem_SUD_GLOBALVAR_00001 */
VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT) Dem_PrimaryEventMemory
  [DEM_MAX_NUMBER_EVENT_ENTRY_PRI];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
/* Mirror Event Memory variable */
VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT) Dem_MirrorEventMemory
  [DEM_MAX_NUMBER_EVENT_ENTRY_MIR];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT) Dem_UserDefinedEventMemory
  [DEM_MAX_NUMBER_EVENT_ENTRY_UD];
#endif
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * VAR_CLEARED_UNSPECIFIED
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
 /* polyspace +2 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_RecordUpdateType, DEM_VAR)
Dem_GstRecordDisableDTC[DEM_NUMBER_OF_DEM_CLIENT];
VAR(Dem_FilteredFreezeFrameRecordType, DEM_VAR)
Dem_FilteredFFRecord[DEM_NUMBER_OF_DEM_CLIENT];
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
VAR(Dem_PrestoreBufferType, DEM_VAR) Dem_GaaPrestoreBuffer
  [DEM_MAX_NUMBER_PRESTORED_FF];
#endif

#if (DEM_MAX_NUMBER_OF_DTC > DEM_ZERO)
#if ((DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) || \
     (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON))
VAR(Dem_InternalDataElementType, DEM_VAR) Dem_InternalDataMaxFdc
  [DEM_MAX_NUMBER_OF_DTC];
#endif
#endif
#define DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * VAR CLEARED_32
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

#if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(uint32, DEM_VAR) Dem_MaxTimeStamp
  [DEM_NUM_OF_DTC_ORGINS + DEM_ONE];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/*************************************************************************
 * VAR CLEARED_16
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

#if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
/* BSW error buffer */
VAR(uint16, DEM_VAR) Dem_GaaErrorBuffer
  [DEM_BSW_ERROR_BUFFER_SIZE];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
VAR(uint16, DEM_VAR) Dem_GaaEventEDCBuffer
  [DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER];
#endif

#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
/* Debounce Counter based */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(sint16, DEM_VAR) Dem_GssTempCounter
  [DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER];
#endif
#define DEM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*************************************************************************
 * VAR CLEARED_8
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

VAR(uint8, DEM_VAR) Dem_GucInit;
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(uint16, DEM_VAR) Dem_EventState
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];

VAR(uint8, DEM_VAR) Dem_GucDisableDtcSettingDTCKind;

VAR(uint8, DEM_VAR) Dem_GaaEventFailureThreshold
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_EvMemToEventMap
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];

VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_NumOfStoredEvtMemEntryies
  [DEM_NUM_OF_DTC_ORGINS + DEM_ONE];

#if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_NumOfStoredEvtMemEntryiesPriMem
  [DEM_MAX_NUMBER_PRIMARY_MEMORY];
#endif

#if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_NumOfStoredEvtMemEntryiesUDMem
  [DEM_MAX_NUMBER_USER_DEFINED_MEMORY];
#endif

/* polyspace +2 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_NumOfStoredEvtMemEntryiesPerMem
  [DEM_MAX_NUMBER_MEMORY_SET];
#endif


#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_NumOfStoredEvtMemEntryiesMirMem
  [DEM_MAX_NUMBER_MEMORY_SET];
#endif

/* DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_NVDATA_GENERIC_NVRAM_DATA_ID */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(uint8, DEM_VAR_NOINIT) Dem_NonVolatileDataState[DEM_TWO];

/* Primary Event Memory variable */
static VAR(uint8, DEM_VAR) Dem_PrimaryEventMemoryState
  [DEM_MAX_NUMBER_EVENT_ENTRY_PRI];

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
/* Mirror Event Memory variable */
static VAR(uint8, DEM_VAR) Dem_MirrorEventMemoryState
  [DEM_MAX_NUMBER_EVENT_ENTRY_MIR];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
/* User Defined Event Memory variable */
static VAR(uint8, DEM_VAR) Dem_UserDefinedEventMemoryState
  [DEM_MAX_NUMBER_EVENT_ENTRY_UD];
#endif

#if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
VAR(uint8, DEM_VAR) Dem_GucErrorWriteIndex;
/* Used to check whether event is stored */
VAR(uint8, DEM_VAR) Dem_GaaErrorBufferStatus
  [DEM_BSW_ERROR_BUFFER_SIZE];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
VAR(uint8, DEM_VAR) Dem_GaaEventEDCBufferStatus
  [DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER];

VAR(uint8, DEM_VAR) Dem_GucReportIndex;
#endif

#if (DEM_NUMBER_OF_EVENTS > DEM_ZERO)
/* Used to check whether event is stored */
VAR(Dem_EventMonitorDataType, DEM_VAR) Dem_MonitorData
  [DEM_NUMBER_OF_EVENTS + DEM_ONE];
#endif

#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_OFF)
VAR(uint8, DEM_VAR) Dem_OperationCycleState
  [DEM_NUMBER_OPERATION_CYCLES];
#endif

/* @IF_REQ: DEM_SIZE_OF_EVENT_DATA -> Max size (FF+ED) */
#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
VAR(uint8, DEM_VAR) Dem_EvEventDataCapture
  [DEM_SIZE_OF_EVENT_DATA];
#endif

#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
/* Debounce Counter based */
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(uint8, DEM_VAR) Dem_CtrDebDirection
  [DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER];
#endif

#if(DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(Dem_NumOfIndicatorAttributeType, DEM_VAR) Dem_IndicatorBehaviorAccumulator
  [DEM_NUM_OF_INDICATORID][DEM_NUM_OF_INDICATOR_BEHAVIOR];
#endif

/* Event dependence status */
#if (DEM_NUMBER_OF_EVENTS > DEM_ZERO )
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(uint8, DEM_VAR) Dem_EvtDepdntStt
  [DEM_NUMBER_OF_EVENTS];
#endif

#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
/* Trace: DEM_COMB_06 */
/* Keep the Status of Each Event Composed of Cominbed Event, When Restart */
VAR(Dem_UdsStatusByteType, DEM_VAR) Dem_CombinedEventStatusByteAtCycleEnd[DEM_MAX_LISTOFCOMBINEDEVENTS];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*****************************************************************************/
/* VAR CLEARED BOOLEAN                                                       */
/*****************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
VAR(boolean, DEM_VAR) Dem_EnableFreeze
  [DEM_NUMBER_OF_EVENTS];
#endif

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
VAR(boolean, DEM_VAR) Dem_ComponentAvailable
  [DEM_NUMBER_OF_DEM_COMPONENT];
#endif

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(boolean, DEM_VAR) Dem_ComponentState
  [DEM_NUMBER_OF_DEM_COMPONENT];
#endif

VAR(boolean, DEM_VAR) Dem_OperationCycleTrigger;

#if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
VAR(boolean, DEM_VAR) Dem_GaaDisableDtcSettingGroupDTC
  [DEM_MAX_NUM_GRP_DTC];
#endif

VAR(boolean, DEM_VAR) Dem_GblDisableDtcSettingAllDTC;

#if (DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO)
VAR(boolean, DEM_VAR) Dem_GaaStorageConditionStatus
  [DEM_NUMBER_STORAGE_CONDITION];
#endif

#if (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO)
VAR(boolean, DEM_VAR) Dem_EnableConditionStatus
  [DEM_NUMBER_ENABLE_CONDITION];
#endif

#if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
VAR(boolean, DEM_VAR) Dem_DoReadFromNv;
#endif

#if (DEM_NUMBER_OPERATION_CYCLES > DEM_ZERO)
/* BSW error buffer */
VAR(boolean, DEM_VAR) Dem_OperationCycleBuffer
  [DEM_NUMBER_OPERATION_CYCLES];
#endif

#if (DEM_NUMBER_OPERATION_CYCLES > DEM_ZERO)
/* BSW error buffer */
VAR(boolean, DEM_VAR) Dem_OperationCycleQualifiedStt
  [DEM_NUMBER_OPERATION_CYCLES];
#endif


#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
 /* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */ 
VAR(boolean, DEM_VAR) Dem_GaaDisableDtcSettingMemSet
  [DEM_MAX_NUMBER_MEMORY_SET];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*************************************************************************
 * CONST
 ************************************************************************/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

CONSTP2VAR(uint8, AUTOMATIC, DEM_CONST) Dem_EventMemoryState
  [DEM_NUM_OF_DTC_ORGINS + DEM_ONE] =
{
  NULL_PTR,

  &Dem_PrimaryEventMemoryState[DEM_ZERO],

  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  &Dem_MirrorEventMemoryState[DEM_ZERO],
  #else
  NULL_PTR,
  #endif

  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
      (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  &Dem_PermanentEventMemoryState[DEM_ZERO],
  #else
  NULL_PTR,
  #endif

  /* OBD Origin*/
  NULL_PTR,

  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  &Dem_UserDefinedEventMemoryState[DEM_ZERO],
  #else
  NULL_PTR,
  #endif
};  

/* number of the entries of each event memory */
CONST(Dem_NumOfEventMemoryEntryType, DEM_CONST) Dem_SizeOfEventMemory
  [DEM_NUM_OF_DTC_ORGINS + DEM_ONE] =
{
  0,
  DEM_MAX_NUMBER_EVENT_ENTRY_PRI,
  DEM_MAX_NUMBER_EVENT_ENTRY_MIR,
  DEM_MAX_NUMBER_EVENT_ENTRY_PER,
  DEM_ZERO, /*OBD Relavant*/
  DEM_MAX_NUMBER_EVENT_ENTRY_UD
};

CONST(Dem_DTCOriginType, DEM_CONST) Dem_SupportedDTCOrigins[DEM_MAX_NUMBER_SUPPORTED_DTC_ORIGINS] = {
  DEM_DTC_ORIGIN_PRIMARY_MEMORY,

  #if(DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  DEM_DTC_ORIGIN_MIRROR_MEMORY,
  #endif

  #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
       (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
  DEM_DTC_ORIGIN_PERMANENT_MEMORY,
  #endif

  #if(DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
  DEM_DTC_ORIGIN_USERDEFINED_MEMORY_LIST
  #endif
};

CONST(uint8, DEM_CONST)  Dem_NumOfSupportedDTCOrigins 
  = COUNTOF(Dem_SupportedDTCOrigins);

CONST(Dem_NvDataIdType, DEM_CONST) Dem_DataIdOfSingleNvBlocks[DEM_TWO] = {
  DEM_NVDATA_ALL_EVENT_STATUS_ID,
  DEM_NVDATA_GENERIC_NVRAM_DATA_ID
};

CONST(Dem_NvDataIdType, DEM_CONST)  Dem_NumOfSupportedSingleNvBlocks =
    COUNTOF(Dem_DataIdOfSingleNvBlocks);

#if defined(DEM_NVM_BLK_ID_EVENT_STATUS)
CONST(NvM_BlockIdType, DEM_CONST) Dem_EventStatusNvRamBlkId =
    DEM_NVM_BLK_ID_EVENT_STATUS;
#else
CONST(NvM_BlockIdType, DEM_CONST) Dem_EventStatusNvRamBlkId = DEM_ZERO;
#endif

#if defined(DEM_NVM_BLK_ID_NON_VOLATILE_DATA)
CONST(NvM_BlockIdType, DEM_CONST) Dem_NonVolatileDataBlkId =
    DEM_NVM_BLK_ID_NON_VOLATILE_DATA;
#else
CONST(NvM_BlockIdType, DEM_CONST) Dem_NonVolatileDataBlkId = DEM_ZERO;
#endif


#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  
/*****************************************************************************/

/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/
