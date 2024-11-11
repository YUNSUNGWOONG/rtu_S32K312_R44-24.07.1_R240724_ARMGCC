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
**  SRC-MODULE: Dem_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Header file for Dem_Ram.c                                     **
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


#ifndef DEM_RAM_H
#define DEM_RAM_H
 
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* Dem module header file */
#include "NvM.h"        /* NVRAM manager symbols Header File */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*************************************************************************
 * VAR INIT_UNSPECIFIED
 ************************************************************************/
#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/* Dem_BasedTimeDebounceStatus is updated in the Dem_PreInit */
extern VAR(Dem_EvMemTriggerType, DEM_VAR) Dem_EvMemTrigger;

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
/* Dem_BasedTimeDebounceStatus is updated in the Dem_EvMem_Init */
extern VAR(Dem_ClearDtcStateType, DEM_VAR)
  Dem_ClearDtcState[DEM_NUMBER_OF_DEM_CLIENT];
/* Dem_BasedTimeDebounceStatus is updated in the Dem_SetDTCFilter */
extern VAR(Dem_DTCFilterStateType, DEM_VAR)
  Dem_DTCFilterState[DEM_NUMBER_OF_DEM_CLIENT];
#endif
/* Dem_AllEventStatusByte is updated in the Dem_EvMem_Init */
extern VAR(Dem_UdsStatusByteType, DEM_VAR)
  Dem_AllEventStatusByte[DEM_NUMBER_OF_EVENTS + DEM_ONE];

/* Dem_UDSProcsessState is updated in the Dem_EvMem_Init */
extern VAR(Dem_UdsStatusByteType, DEM_VAR)
  Dem_UDSProcsessState[DEM_NUMBER_OF_EVENTS + DEM_ONE];

extern VAR(Dem_MonitorStatusType, DEM_VAR)
  Dem_AllMonitorStatus[DEM_NUMBER_OF_EVENTS + DEM_ONE];

/* Dem_BasedTimeDebounceStatus is updated in the Dem_PreInit */
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
/* Predebounce time */
extern VAR(Dem_TimeDebounceStatusType, DEM_VAR)
  Dem_BasedTimeDebounceStatus[DEM_NUMBER_OF_PRE_DEBOUNCE_TIME];
#endif
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
/* APIs is updated in the Dem_SelectDTC */
extern VAR(Dem_SelectDtcStateType, DEM_VAR)
  Dem_ClientSelectDtcState[DEM_NUMBER_OF_DEM_CLIENT];
/* APIs is updated in the Dem_SelectFreezeFrameData */
extern VAR(Dem_SelectFreezeFrameDataStateType, DEM_VAR)
  Dem_ClientSelectFreezeFrameData[DEM_NUMBER_OF_DEM_CLIENT];
/* APIs is updated in the Dem_SelectExtendedDataRecord */
extern VAR(Dem_SelectExtendedDataRecordType, DEM_VAR)
  Dem_ClientSelectExtendedDataRecord[DEM_NUMBER_OF_DEM_CLIENT];
#endif
#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * VAR_NO_INIT_UNSPECIFIED
 ************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

extern VAR(Dem_GenericNvRamDataType, DEM_VAR_NOINIT) Dem_NonVolatileData;

extern VAR(Dem_EventStatusNvRamDataType, DEM_VAR_NOINIT)
  Dem_EventStatusNvRamData;

/* Primary Event Memory variable */
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > DEM_ZERO)
extern VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_PrimaryEventMemory[DEM_MAX_NUMBER_EVENT_ENTRY_PRI];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
extern VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_UserDefinedEventMemory[DEM_MAX_NUMBER_EVENT_ENTRY_UD];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
/* Mirror Event Memory variable */
extern VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_MirrorEventMemory[DEM_MAX_NUMBER_EVENT_ENTRY_MIR];
#endif

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * VAR_CLEARED_UNSPECIFIED
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
extern VAR(Dem_RecordUpdateType, DEM_VAR)
  Dem_GstRecordDisableDTC[DEM_NUMBER_OF_DEM_CLIENT];
#endif

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
extern VAR(Dem_FilteredFreezeFrameRecordType, DEM_VAR)
  Dem_FilteredFFRecord[DEM_NUMBER_OF_DEM_CLIENT];
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
extern VAR(Dem_PrestoreBufferType, DEM_VAR)
  Dem_GaaPrestoreBuffer[DEM_MAX_NUMBER_PRESTORED_FF];
#endif

#if (DEM_MAX_NUMBER_OF_DTC > DEM_ZERO)
#if ((DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) || \
     (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON))
extern VAR(Dem_InternalDataElementType, DEM_VAR)
  Dem_InternalDataMaxFdc[DEM_MAX_NUMBER_OF_DTC];
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
extern VAR(uint32, DEM_VAR) Dem_MaxTimeStamp[DEM_NUM_OF_DTC_ORGINS + DEM_ONE];
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
extern VAR(uint16, DEM_VAR) Dem_GaaErrorBuffer[DEM_BSW_ERROR_BUFFER_SIZE];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
extern VAR(uint16, DEM_VAR)
  Dem_GaaEventEDCBuffer[DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER];
#endif

#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
/* Debounce Counter based */
extern VAR(sint16, DEM_VAR)
  Dem_GssTempCounter[DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER];
#endif
#define DEM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*************************************************************************
 * VAR CLEARED_8
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

extern VAR(uint8, DEM_VAR) Dem_GucInit;

extern VAR(uint16, DEM_VAR) Dem_EventState[DEM_NUMBER_OF_EVENTS + DEM_ONE];

extern VAR(uint8, DEM_VAR) Dem_GucDisableDtcSettingDTCKind;

extern VAR(uint8, DEM_VAR)
  Dem_GaaEventFailureThreshold[DEM_NUMBER_OF_EVENTS + DEM_ONE];

extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
  Dem_EvMemToEventMap[DEM_NUMBER_OF_EVENTS + DEM_ONE];

extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
  Dem_NumOfStoredEvtMemEntryies[DEM_NUM_OF_DTC_ORGINS + DEM_ONE];

#if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
  Dem_NumOfStoredEvtMemEntryiesPriMem[DEM_MAX_NUMBER_PRIMARY_MEMORY];
#endif

#if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
  Dem_NumOfStoredEvtMemEntryiesUDMem[DEM_MAX_NUMBER_USER_DEFINED_MEMORY];
#endif

#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
  Dem_NumOfStoredEvtMemEntryiesPerMem[DEM_MAX_NUMBER_MEMORY_SET];
#endif

#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
extern VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR)
  Dem_NumOfStoredEvtMemEntryiesMirMem[DEM_MAX_NUMBER_MEMORY_SET];
#endif

/* DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_NVDATA_GENERIC_NVRAM_DATA_ID */
extern VAR(uint8, DEM_VAR_NOINIT) Dem_NonVolatileDataState[DEM_TWO];

#if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
extern VAR(uint8, DEM_VAR) Dem_GucErrorWriteIndex;

/* Used to check whether event is stored */
extern VAR(uint8, DEM_VAR) Dem_GaaErrorBufferStatus[DEM_BSW_ERROR_BUFFER_SIZE];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
extern VAR(uint8, DEM_VAR)
  Dem_GaaEventEDCBufferStatus[DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER];

extern VAR(uint8, DEM_VAR) Dem_GucReportIndex;
#endif

#if (DEM_NUMBER_OF_EVENTS > DEM_ZERO)
/* Used to check whether event is stored */
extern VAR(Dem_EventMonitorDataType, DEM_VAR)
  Dem_MonitorData[DEM_NUMBER_OF_EVENTS + DEM_ONE];
#endif

#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_OFF)
extern VAR(uint8, DEM_VAR) Dem_OperationCycleState[DEM_NUMBER_OPERATION_CYCLES];
#endif

#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern VAR(uint8, DEM_VAR) Dem_EvEventDataCapture[DEM_SIZE_OF_EVENT_DATA];
#endif

#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
/* Debounce Counter based */
extern VAR(uint8, DEM_VAR)
  Dem_CtrDebDirection[DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER];
#endif

#if(DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
extern VAR(Dem_NumOfIndicatorAttributeType, DEM_VAR)
  Dem_IndicatorBehaviorAccumulator
    [DEM_NUM_OF_INDICATORID][DEM_NUM_OF_INDICATOR_BEHAVIOR];
#endif

/* Event dependence status */
#if (DEM_NUMBER_OF_EVENTS > DEM_ZERO )
extern VAR(uint8, DEM_VAR) Dem_EvtDepdntStt
  [DEM_NUMBER_OF_EVENTS];
#endif

#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
/* Trace: DEM_COMB_06 */
/* Keep the Status of Each Event Composed of Cominbed Event, When Restart */
extern VAR(Dem_UdsStatusByteType, DEM_VAR) Dem_CombinedEventStatusByteAtCycleEnd[DEM_MAX_LISTOFCOMBINEDEVENTS];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*****************************************************************************/
/* VAR CLEARED BOOLEAN                                                       */
/*****************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
extern VAR(boolean, DEM_VAR) Dem_EnableFreeze[DEM_NUMBER_OF_EVENTS];
#endif

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
extern VAR(boolean, DEM_VAR)
  Dem_ComponentAvailable[DEM_NUMBER_OF_DEM_COMPONENT];
#endif

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
extern VAR(boolean, DEM_VAR) Dem_ComponentState[DEM_NUMBER_OF_DEM_COMPONENT];
#endif

extern VAR(boolean, DEM_VAR) Dem_OperationCycleTrigger;

#if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
extern VAR(boolean, DEM_VAR)
  Dem_GaaDisableDtcSettingGroupDTC[DEM_MAX_NUM_GRP_DTC];
#endif

extern VAR(boolean, DEM_VAR) Dem_GblDisableDtcSettingAllDTC;

#if (DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO)
extern VAR(boolean, DEM_VAR)
  Dem_GaaStorageConditionStatus[DEM_NUMBER_STORAGE_CONDITION];
#endif

#if (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO)
extern VAR(boolean, DEM_VAR)
  Dem_EnableConditionStatus[DEM_NUMBER_ENABLE_CONDITION];
#endif

#if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
extern VAR(boolean, DEM_VAR) Dem_DoReadFromNv;
#endif
#if (DEM_NUMBER_OPERATION_CYCLES > DEM_ZERO)
/* BSW error buffer */
extern VAR(boolean, DEM_VAR)
  Dem_OperationCycleBuffer[DEM_NUMBER_OPERATION_CYCLES];
#endif

#if (DEM_NUMBER_OPERATION_CYCLES > DEM_ZERO)
/* Operation cycle qualitifed status */
extern VAR(boolean, DEM_VAR)
  Dem_OperationCycleQualifiedStt[DEM_NUMBER_OPERATION_CYCLES];
#endif

#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
extern VAR(boolean, DEM_VAR) Dem_GaaDisableDtcSettingMemSet
  [DEM_MAX_NUMBER_MEMORY_SET];
#endif
#define DEM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*************************************************************************
 * CONST
 ************************************************************************/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* This pointer array points to the event memories */
/*extern CONSTP2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_CONST)
 * Dem_EventMemory[];*/

extern CONSTP2VAR(uint8, AUTOMATIC, DEM_CONST)
  Dem_EventMemoryState[DEM_NUM_OF_DTC_ORGINS + DEM_ONE];

extern CONST(Dem_NumOfEventMemoryEntryType, DEM_CONST)
  Dem_SizeOfEventMemory[DEM_NUM_OF_DTC_ORGINS + DEM_ONE];

extern CONST(Dem_DTCOriginType, DEM_CONST)
  Dem_SupportedDTCOrigins[DEM_MAX_NUMBER_SUPPORTED_DTC_ORIGINS];

extern CONST(uint8, DEM_CONST)  Dem_NumOfSupportedDTCOrigins;

extern CONST(Dem_NvDataIdType, DEM_CONST) Dem_DataIdOfSingleNvBlocks[DEM_TWO];
    
extern CONST(Dem_NvDataIdType, DEM_CONST)  Dem_NumOfSupportedSingleNvBlocks;

/* BlockId is allocated in the Dem_Config.c */
extern CONST(NvM_BlockIdType, DEM_CONST)  Dem_EventStatusNvRamBlkId;

/* BlockId is allocated in the Dem_Config.c */
extern CONST(NvM_BlockIdType, DEM_CONST)  Dem_NonVolatileDataBlkId;

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/*****************************************************************************/

/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */

#endif /* DEM_RAM_H */
/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/

