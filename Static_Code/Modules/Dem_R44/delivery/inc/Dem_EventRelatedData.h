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
**  SRC-MODULE: Dem_EventRelatedData.h                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_EventRelatedData.c                            **
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
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/


#ifndef DEM_EVENTRELATEDDATA_H
#define DEM_EVENTRELATEDDATA_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"
#include "Dem_Config.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
**                Extern function definition                                  **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(boolean, DEM_CODE)
Dem_CaptureOBDFFClass(
  CONSTP2CONST(Dem_OBDClassType, AUTOMATIC, DEM_CONST) OBDClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OBDFreezeFrameData
);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetWWHFreezeFrameData(
  Dem_EventRelatedDataPCType  EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_DataIdentifierType DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE)
Dem_OBDCaptureDataElementClass(
  uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);
#endif

#if (DEM_SIZE_OF_EXTENDED_DATA> DEM_ZERO)
extern FUNC(boolean, DEM_CODE)
Dem_CaptureEDClass(
  Dem_EventStatusType EventStatus,
  Dem_EventIdType EventId,
  Dem_ExtendedDataClassCPCType EDDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize,
  Dem_EventOccurrenceType EventOccurrence);
#endif

#if ((DEM_J1939_SUPPORT == STD_ON) && \
     (DEM_NUM_OF_J1939FREEZEFRAMECLASS > DEM_ZERO))
extern FUNC(boolean, DEM_CODE) Dem_CaptureJ1939FFClass(
  Dem_EventIdType EventId,
  CONSTP2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST)
  J1939FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);
#endif

#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern FUNC(boolean, DEM_CODE)
Dem_CaptureDataElementClass(
  Dem_EventIdType EventId,
  uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);


extern FUNC(void, DEM_CODE)
Dem_CaptureInternalDataElementClass(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  Dem_EventMemoryEntryPtrType MemEntry,
  const uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer);
#endif

#if((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
    (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO))
extern FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetOBDFFBufferForWriting(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize);

extern FUNC(boolean, DEM_CODE)
Dem_StoreObdFFClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern FUNC(Dem_SizeOfFreezeFrameClassType, DEM_CODE)
Dem_GetSizeOfFreezeFrameData(
  Dem_FreezeFrameClassPCType FFClass,
  const Dem_FFBufferFormatType FFBufferType);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_FFRecordNumBelongToFFClass(
  Dem_EventRelatedDataPCType EvData,
  const Dem_RecordNumberType RecordNumber,
  const Dem_NumOfRecordNumberType NumOfFFRecords,
  P2VAR(Dem_NumOfRecordNumberType, AUTOMATIC, DEM_APPL_DATA) RelRecordIndex);

extern FUNC(boolean, DEM_CODE) Dem_CaptureFFClass(
  Dem_EventIdType EventId,
  Dem_FreezeFrameClassCPCType FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);
#endif


#if (DEM_SIZE_OF_EXTENDED_DATA> DEM_ZERO)

extern FUNC(boolean, DEM_CODE)
Dem_StoreUdsEDClass(
  Dem_EventStatusType EventStatus,
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern FUNC(boolean, DEM_CODE)
Dem_StoreUdsFFClass(
    Dem_EventStatusType EventStatus,
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry,
    uint8 EnvDataCapture);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(boolean, DEM_CODE) Dem_StoreWWHFFClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if ((DEM_J1939_SUPPORT == STD_ON) && \
     (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO))
extern FUNC(boolean, DEM_CODE)
  Dem_StoreJ1939FFClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if ((DEM_J1939_SUPPORT == STD_ON) && \
     (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > DEM_ZERO))
extern FUNC(boolean, DEM_CODE)
Dem_StoreJ1939EXFFClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
#if (DEM_NUM_OF_J1939FREEZEFRAMECLASS > DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfJ1939FreezeFrameData(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_SizeOfJ1939FreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize,
  Dem_J1939DcmSetFreezeFrameFilterType J1939FFType);
#endif
#endif

#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetSizeOfFreezeFrameByRecord(
  Dem_EventIdType EventId,
  Dem_RecordNumberType RecordNumber,
  Dem_DTCOriginType DTCOrigin,   /* DTCOrigin is verified by caller */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfFreezeFrame);
#endif

#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern FUNC(boolean, DEM_CODE)
Dem_StoreEventRelatedData(
 P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) EvData,
 Dem_EventMemoryEntryPtrType EvMemEntry,
 Dem_EventStatusType EventStatus,
 uint8 EnvDataCapture);
#endif

extern FUNC(Std_ReturnType, DEM_CODE) 
Dem_ReadDataOfExtendedData(
  Dem_EventRelatedDataPCType EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_ExtendedDataNumberType  ExtendedDataNumber,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOBDFreezeFrameData(
  Dem_EventParameterPCType event,
  Dem_DTCOriginType DTCOrigin,
  P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize);
#endif

extern FUNC(Dem_ReturnReadEventDataType, DEM_CODE)
Dem_ReadDataOfFreezeFrame(
  Dem_EventRelatedDataPCType EvData,   
  Dem_DTCOriginType DTCOrigin,
  Dem_RecordNumberType RecordNumber,
  Dem_DataIdentifierType DataIdentifier,
  Dem_FFBufferFormatType HeaderType,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);


extern FUNC(Dem_SizeOfExtendedDataClassType, DEM_CODE)
Dem_GetSizeOfExtendedData(
  Dem_ExtendedDataClassPCType EDClass,
  const Dem_ExtendedDataNumberType ExtendedDataNumber,
  P2VAR(Dem_NumOfExtendedDataRecordClassType, AUTOMATIC, DEM_VAR) NumOfMatchedEDR
  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  , Dem_EventIdType EventId
  #endif
  );


#if (DEM_J1939_SUPPORT == STD_ON)  
#if (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO)

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetJ1939FreezeFrameData(
  Dem_EventParameterCPCType event,
  Dem_DTCOriginType DTCOrigin,
  P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize,
  Dem_J1939DcmSetFreezeFrameFilterType J1939FFType);
#endif
#endif
  
/**************************************************/
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*************************************************/


#endif

