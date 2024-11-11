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
**  SRC-MODULE: Dem_EventRelatedData.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of event related data functionality                 **
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
** 2.1.0.0   29-Mar-2024   EK Kim        Jira #CP44-3819 #CP44-3777           **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
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

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Rte_Dem.h"

#include "Dem_Event.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventMemory.h"
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#include "Dem_Obd.h"
#endif
#include "Dem_Dtc.h"

#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
#include "Dcm.h"
#endif

/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned> Not defect  */ 

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Dem_FFRecordNumBelongToFFClass                      **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                        and normal operation.                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EvData, RecordNumber, NumOfFFRecords                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RelRecordIndex                                      **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)

FUNC(Std_ReturnType, DEM_CODE)
Dem_FFRecordNumBelongToFFClass(
  Dem_EventRelatedDataPCType EvData,
  const Dem_RecordNumberType RecordNumber,
  const Dem_NumOfRecordNumberType NumOfFFRecords,
  P2VAR(Dem_NumOfRecordNumberType, AUTOMATIC, DEM_APPL_DATA) RelRecordIndex)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint16 LusMaxFFRecordClass =
      EvData->FFRecordClassIndex + (uint16)NumOfFFRecords;
  /* @Trace: Dem_SUD_API_12981 */
  if (LusMaxFFRecordClass <= DEM_NUM_OF_FRREZEFRAMERECORDCLASS) /* Note : <= */
  {
    uint16 LusIRecord;
    /* @Trace: Dem_SUD_API_12980 */
    for (LusIRecord = EvData->FFRecordClassIndex;
         LusIRecord < LusMaxFFRecordClass;
         LusIRecord++)
    {
      /* @Trace: Dem_SUD_API_12979 */
      if (RecordNumber ==
            Dem_FreezeFrameRecordClass[LusIRecord].FreezeFrameRecordNumber)
      {
        /* Range : 0~ 255 */
        /* @Trace: Dem_SUD_API_12978 */
        uint16 LusIdxFromZero = LusIRecord - EvData->FFRecordClassIndex;
        *RelRecordIndex = (Dem_NumOfRecordNumberType)LusIdxFromZero;

        LddRetVal = E_OK;
        break;
      }
    }
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetSizeOfFreezeFrameByRecord                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : The API shall be used to get the size of            **
**                        freeze frame                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId, RecordNumber, DTCOrigin                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SizeOfFreezeFrame                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetSizeOfFreezeFrameByRecord(
  Dem_EventIdType EventId,
  Dem_RecordNumberType RecordNumber,
  Dem_DTCOriginType DTCOrigin,   /* DTCOrigin is verified by caller */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfFreezeFrame)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  uint8 protocolId = 0x00u;
  /* OBD */
  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  (void)Dcm_GetObdProtocolId(&protocolId);
  #endif
  
  if ((protocolId != DEM_PROTOCOLID_J1979_2_OBD_ON_UDS) &&
     (DEM_OBD_RECORD_NUMBER == RecordNumber))
  {
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO))
    /* @Trace: Dem_SUD_API_12988 */
    if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
    {
      Dem_EventRelatedDataCPCType LddEvData =
          &Dem_EventRelatedData[LddEvent->e_PointToData];
      if (LddEvData->WWHOBDFFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS)
      {
        /* @Trace: Dem_SUD_API_12982 */
        LddRetVal = E_OK; /* No Error */
        *SizeOfFreezeFrame =
            Dem_FreezeFrameClass[LddEvData->WWHOBDFFClassPos].size;
      }
      else
      {
        /* @Trace: Dem_SUD_API_12987 */
        if (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
        {
          /* @Trace: Dem_SUD_API_12986 */
          if (DEM_DTC_FORMAT_OBD ==
                Dem_GaaCombinedDtc[LddEvent->e_PointToDTC].ddDtcFormat)
          {
            /* @Trace: Dem_SUD_API_00173 */
            *SizeOfFreezeFrame = DEM_ZERO;
            /* Report size of all PIDs */
            (void)Dem_GetSizeOfOBDFreezeFrameData(
                LddEvent, DEM_TRUE, DEM_ZERO, SizeOfFreezeFrame);
            LddRetVal = E_OK;
          }
        }
      }
    }
    #endif
  }
  /* UDS */
  else 
  {
    /* @Trace: Dem_SUD_API_12989 */
    if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
    { 
      Dem_EventRelatedDataCPCType LddEvData =
          &Dem_EventRelatedData[LddEvent->e_PointToData];
      /* @Trace: Dem_SUD_API_12990 */
      if (LddEvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS)
      {
        Dem_NumOfRecordNumberType LddRecordIndex = DEM_ZERO;
        Dem_EventMemoryEntryPtrType LddEntry;
        
        if (DEM_MAX_RECORD == RecordNumber) 
        {
          LddRetVal = E_OK; /* No Error */
          *SizeOfFreezeFrame = DEM_ZERO;
          
          /* @Trace: SWS_Dem_00076
           * Note: If the record number value 0xFF is requested, the Dem
           * considers the size of all stored extended data records (in the
           * range of 0x01 to 0xEF) */
          LddEntry = Dem_EvMem_FindEntry(EventId, DTCOrigin);
          /* @Trace: Dem_SUD_API_12992 */
          if (NULL_PTR != LddEntry)
          {
            /* @Trace: Dem_SUD_API_12991 */
            *SizeOfFreezeFrame =
                Dem_GetSizeOfFreezeFrameData(
                    &Dem_FreezeFrameClass[LddEvData->FFClassPos],
                    DEM_FFFORMAT_TYPE_HDR_REC);
            /* number of record that stored FF. */
            *SizeOfFreezeFrame =
                *SizeOfFreezeFrame * Dem_EvMem_GetRecNumOfFF(LddEntry);
          }
        }
        else if (E_OK == Dem_FFRecordNumBelongToFFClass(
            LddEvData,
            RecordNumber,
            LddEvData->MaxNumOfFreezeFrameRecords,
            &LddRecordIndex))
        {
          LddRetVal = E_OK;
          *SizeOfFreezeFrame = DEM_ZERO;
          
          LddEntry= Dem_EvMem_FindEntry(EventId, DTCOrigin);
          /* @Trace: Dem_SUD_API_12985 */
          if (NULL_PTR != LddEntry)
          {
            Dem_NumOfRecordNumberType LddMaxCount =
                Dem_EvMem_GetRecNumOfFF(LddEntry);

            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* When $F0 Record is not exist yet, ($F0 Configuration is Mandatory) 
               $00 Record have to Response instead of $F0 */
            /* 1979-2 Needed To Recnum $F0 Response */
            if ((RecordNumber == 0xF0u) &&
                (LddRecordIndex >= LddMaxCount))
            {
              (void) Dem_FFRecordNumBelongToFFClass(
                  LddEvData,
                  DEM_ZERO,
                  LddEvData->MaxNumOfFreezeFrameRecords,
                  &LddRecordIndex);
            }
            #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/

            /* @Trace: Dem_SUD_API_12983 */
            if (LddRecordIndex < LddMaxCount)
            {
              /* @Trace: Dem_SUD_API_12984 */
              *SizeOfFreezeFrame =
                  Dem_GetSizeOfFreezeFrameData(
                      &Dem_FreezeFrameClass[LddEvData->FFClassPos],
                      DEM_FFFORMAT_TYPE_HDR_REC);
            }
          }      
        }
        else
        {
          /* @Trace: Dem_SUD_API_12993 */
          /* LddRetVal = E_NOT_OK;*/
        }
      }
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_CaptureFFClass                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Loads the Dids in the DestBuffer                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId, FFDataClass, BufSize                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OutBuffer                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_CaptureFFClass(
  Dem_EventIdType EventId,
  Dem_FreezeFrameClassCPCType FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize) 
{
  boolean LblDirty = DEM_FALSE;
  uint16 LusIdx;

  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  /* @Trace: Dem_SUD_API_12994 */
  if ((NULL_PTR != FFDataClass) && (NULL_PTR != OutBuffer)) 
  {
    uint16 LusMax = FFDataClass->PointToDidMap +  FFDataClass->NumOfDidClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition always evaluates to true. Avoid the runtime error of the
     * polyspace */
    /* @Trace: Dem_SUD_API_12995 */
    if ((BufSize >= FFDataClass->size) &&
        (LusMax <= Dem_Max_ListOfDidClassIndex))
    {
      uint32 LulIdxForDst = DEM_ZERO;
      /* @Trace: Dem_SUD_API_12996 */
      for (LusIdx = FFDataClass->PointToDidMap; LusIdx < LusMax; LusIdx++)
      {
        CONSTP2CONST(Dem_DidClassType, AUTOMATIC, DEM_CONST)
        LddDidClass =  &Dem_DidClass[Dem_ListOfDidClassIndex[LusIdx]];

        if ((LulIdxForDst + (uint32)LddDidClass->size) <= BufSize)
        {
          /* @Trace: Dem_SUD_API_12998 */
          /* Read Data Element from SW-C through RTE */
          LblDirty |= Dem_CaptureDataElementClass(
              EventId,
              LddDidClass->PointToDataElementMap,
              LddDidClass->NumOfDataElementClass,
              &OutBuffer[LulIdxForDst],
              LddDidClass->size);
              
          LulIdxForDst += LddDidClass->size;
        }
        else
        /* @Trace: Dem_SUD_API_12997 */
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        {

        }
      }
    }
  }

  return LblDirty;
}
#endif

/*******************************************************************************
** Function Name        : Dem_CaptureOBDFFClass                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is used to load the OBD freeze frame             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : OBDClass                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OBDFreezeFrameData                                  **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE) Dem_CaptureOBDFFClass(
  CONSTP2CONST(Dem_OBDClassType, AUTOMATIC, DEM_CONST) OBDClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OBDFreezeFrameData )
{
  boolean LblDirty = DEM_FALSE;
  const Dem_NumOfPidClassType LddNumOfPid = OBDClass->NumOfPidClass;
  CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) LddPID =
      OBDClass->PidClass;
  uint32 LulIdxForDst = DEM_ZERO;
  /* @Trace: Dem_SUD_API_12999 */
  if (NULL_PTR != LddPID)
  {
    /* @Trace: Dem_SUD_API_13000 */
    if (LddNumOfPid <= DEM_MAX_NUMBER_OF_PID_RECDS)
    {
      /* @Trace: Dem_SUD_API_13001 */
      for (Dem_NumOfPidClassType LddIdx = DEM_ZERO;
                                 LddIdx < LddNumOfPid;
                                 LddIdx++)
      {
        /* @Trace: Dem_SUD_API_13002 */
        /* Read Data Element from SW-C through RTE */
        LblDirty |= Dem_OBDCaptureDataElementClass(
            LddPID[LddIdx].PointToDataElementMap,
            LddPID[LddIdx].NumOfPidDataElements,
            &OBDFreezeFrameData[LulIdxForDst],
            LddPID[LddIdx].size);
        LulIdxForDst += LddPID[LddIdx].size;
      }
    }
  }
  return LblDirty;
}
#endif

/*******************************************************************************
** Function Name        : Dem_CaptureEDClass                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is used to load the extended data.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventStatus, EventId, EDDataClass, BufSize          **
**                        EventOccurrence                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OutBuffer                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04073 SRS_Diag_04127
 */
/* @Trace: Dem_SUD_MACRO_118 */
#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
FUNC(boolean, DEM_CODE)
Dem_CaptureEDClass(
  Dem_EventStatusType EventStatus,
  Dem_EventIdType EventId,
  Dem_ExtendedDataClassCPCType EDDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize,
  Dem_EventOccurrenceType EventOccurrence
  )
{
  boolean LblDirty = DEM_FALSE;
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  /* @Trace: Dem_SUD_API_13003 */
  if ((NULL_PTR != EDDataClass) && (NULL_PTR != OutBuffer))
  {
    uint32 LulIdxForDst = DEM_ZERO;
    uint16 LusMaxEDR =
        EDDataClass->PointToEDRecordMap +
        EDDataClass->NumOfEDRecordClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition evaluates to true or false according to configuration */
    /* @Trace: Dem_SUD_API_13007 */
    if (LusMaxEDR <= Dem_Max_ListOfEDRecordClassIndex)
    { 
      uint16 LusIEDR;
      /* Loop through the no. of data elements for the Did */
      /* @Trace: Dem_SUD_API_13008 */
      for (LusIEDR = EDDataClass->PointToEDRecordMap;
           LusIEDR < LusMaxEDR;
           LusIEDR++)
      { 
        CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST) 
            LddEDRecord =
                &Dem_ExtendedDataRecordClass
                  [Dem_ListOfEDRecordClassIndex[LusIEDR]];
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
        /* @Trace: Dem_SUD_API_13010 */
        const Dem_UdsStatusByteType LddEventStatusByteOld  =
            Dem_GetDTCStatus(EventId);
        #else
        /* @Trace: Dem_SUD_API_13009 */
        const Dem_UdsStatusByteType LddEventStatusByteOld  =
            Dem_AllEventStatusByte[EventId];
        #endif
        if ((LulIdxForDst + (uint32)LddEDRecord->size) <= BufSize)
        {
          /* Check if the record should be updated once or every time a event
           * fails */
          /* Check if the record should be updated once or every time a event
           * fails */
          /* @Trace: SWS_Dem_00815
           * If the configuration parameter DemExtendedDataRecordUpdate is set
           * to DEM_UPDATE_RECORD_NO, the ExtendedDataRecord shall be stored
           * only if the ExtendedDataRecord is currently not stored in this
           * event memory entry.
           */

          /* @Trace: SWS_Dem_00816
           * If the configuration parameter DemExtendedDataRecordUpdate is set
           * to DEM_UPDATE_RECORD_YES, the ExtendedDataRecord shall be updated
           * with each trigger (refer to DemExtendedDataRecordTrigger).
           */

          /* @Trace: SWS_Dem_00270
           * The function Dem_DisableDTCRecordUpdate shall protect the event
           * related data of the selected DTC within the selected DTCOrigin
           * from updating or deleting, to allow a consistent read for the
           * following subsequent APIcalls:
           * - Dem_SelectFreezeFrameData
           *   Dem_GetSizeOfFreezeFrameSelection and
           *   Dem_GetNextFreezeFrameData
           * - Dem_SelectExtendedDataRecord
           *   Dem_GetSizeOfExtendedDataRecordSelection and
           *   Dem_GetNextExtendedDataRecord.
           */
          Std_ReturnType LddStatusOfDTCRecordUpdate =
              Dem_GetStatusOfDTCRecordUpdate(EventId);
          /* @Trace: Dem_SUD_API_13012 */
          if (((DEM_UPDATE_RECORD_YES == LddEDRecord->RecordUpdate) ||
              (DEM_ONE == EventOccurrence)
              /* @&& (DEM_UPDATE_RECORD_NO == LddEDRecord->RecordUpdate)) */)
              #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
              && (E_OK == LddStatusOfDTCRecordUpdate)
              #endif
             )
          {
              /* @Trace: Dem_SUD_MACRO_085 */
              #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
              P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR)
                  LddTimerStatus = NULL_PTR;
              /* @Trace: Dem_SUD_API_13013 */
              if ((EventId <= DEM_NUMBER_OF_EVENTS) &&
                  (DEM_NO_EVENT != EventId))
              {
                /* @Trace: Dem_SUD_API_13014 */
                if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME >
                      Dem_Event[EventId - DEM_ONE].ucIndexOfDebounceAry)
                {
                  LddTimerStatus =
                      Dem_GetDebounceTimerStatus(Dem_Event[EventId - DEM_ONE].
                          ucIndexOfDebounceAry);
                }
              }
              #endif
            /* @Trace: SWS_Dem_00811
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_FDC_THRESHOLD, the ExtendedDataRecord shall be
             * captured (as allowed by [SWS_Dem_00810]) each time the
             * configured FDC threshold (refer to
             * DemCounterBasedFdcThresholdStorageValue or
             * DemTimeBasedFdcThresholdStorageValue) is reached (by a positive
             * increment), but at most once per operation cycle.
             */

            /* @Trace: SWS_Dem_00812
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_TEST_FAILED, the ExtendedDataRecord shall be
             * captured (as allowed by [SWS_Dem_00810]) each time the UDS
             * status bit 0 is set (changing from 0 to 1).
             */

            /* @Trace: SWS_Dem_00813
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_PENDING, the ExtendedDataRecord shall be captured
             * (as allowed by [SWS_Dem_00810]) each time the UDS status bit 2
             * is set (changing from 0 to 1).
             */

            /* @Trace: SWS_Dem_00814
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_CONFIRMED, the ExtendedDataRecord shall be
             * captured (as allowed by [SWS_Dem_00810]) each time the UDS
             * status bit 3 is set (changing from 0 to 1).
             */

            /* @Trace: SWS_Dem_01070
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_PASSED, the ExtendedDataRecord shall be captured
             * with the change of Testfailed UDS status bit 0 is reset
             * (changing from 1 to 0). If no entry exists, on passed report no
             * new entry shall be created.
             */

            /* @Trace: SWS_Dem_01071
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_MIRROR, the ExtendedDataRecord shall be captured
             * with the transfer of the memory entry to the mirror memory.
             */

            /* @Trace: SWS_Dem_01069
             * If the DemExtendedDataRecordTrigger is set to
             * DEM_TRIGGER_ON_FDC_THRESHOLD and the event reports
             * DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (monitor-internal
             * debounced event), the ExtendedDataRecord shall be captured
             * (refer [SWS_Dem_00810]), but at most once per operation cycle.
             */

            boolean LblIsBit0GetTransit =
                Dem_EvIsUdsProcStateTriggered(
                    EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_0);
            boolean LblIsBit2GetTransit =
                Dem_EvIsUdsProcStateTriggered(
                    EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_2);
            boolean LblIsBit3GetTransit =
                Dem_EvIsUdsProcStateTriggered(
                    EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
            /* @Trace: Dem_SUD_API_13004 */
            if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
            {
              #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
              Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
              sint16 LssDemCounterBasedFdcThresholdStorageValue =
                  Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry].
                    ssDemCounterBasedFdcThresholdStorageValue;
              #endif

              #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
              uint32 LulTimeBasedFdcThresholdStorageValue =
                  Dem_GaaPreDebounceTimeBased[LddEvent->ucIndexOfDebounceAry].
                    ulDemTimeBasedFdcThresholdStorageValue;
              #endif
              /* @Trace: Dem_SUD_API_13005 */
              if ((
                    ((DEM_TRIGGER_ON_TEST_FAILED ==
                        LddEDRecord->RecordTriger) &&
                    ((DEM_TRUE == LblIsBit0GetTransit) &&
                     ((uint8)(LddEventStatusByteOld &
                      (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) ==
                          DEM_ZERO))) ||

                    ((DEM_TRIGGER_ON_PENDING == LddEDRecord->RecordTriger) &&
                     ((DEM_TRUE == LblIsBit2GetTransit) &&
                     ((uint8)(LddEventStatusByteOld &
                      (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) ==
                         DEM_ZERO))) ||

                    ((DEM_TRIGGER_ON_CONFIRMED == LddEDRecord->RecordTriger) &&
                     ((DEM_TRUE == LblIsBit3GetTransit) &&
                     ((uint8)(LddEventStatusByteOld &
                      (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) ==
                         DEM_ZERO))) ||

                     ((DEM_TRIGGER_ON_PASSED == LddEDRecord->RecordTriger) &&
                      ((DEM_TRUE == LblIsBit0GetTransit) &&
                      ((uint8)(LddEventStatusByteOld &
                       (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) ==
                         DEM_UDS_STATUS_TF)))

                    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
                    || ((((DEM_DEBOUNCE_COUNTER_BASED ==
                            DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
                                Dem_Event[EventId - DEM_ONE].ParamFieldsA)) &&
                         (Dem_GssTempCounter[Dem_Event[EventId - DEM_ONE].
                                               ucIndexOfDebounceAry]
                            >= LssDemCounterBasedFdcThresholdStorageValue)) &&
                         (DEM_TRIGGER_ON_FDC_THRESHOLD ==
                             LddEDRecord->RecordTriger)) &&
                         (DEM_ONE == EventOccurrence))
                    #endif

                    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
                    || (((NULL_PTR != LddTimerStatus) &&
                       (((DEM_DEBOUNCE_TIME_BASED ==
                           DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
                               Dem_Event[EventId - DEM_ONE].ParamFieldsA)) &&
                       (LddTimerStatus->tds_Counter
                           <= (LulTimeBasedFdcThresholdStorageValue /
                               Dem_Task_Time))) &&
                       (DEM_TRIGGER_ON_FDC_THRESHOLD ==
                           LddEDRecord->RecordTriger))) &&
                       (DEM_ONE == EventOccurrence))
                    #endif

                    || ((DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED ==
                           EventStatus) &&
                       (DEM_TRIGGER_ON_FDC_THRESHOLD ==
                           LddEDRecord->RecordTriger) &&
                       (DEM_ONE == EventOccurrence))

                    #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
                    || (DEM_TRIGGER_ON_MIRROR == LddEDRecord->RecordTriger)
                    #endif
                  ))
              {
                /* @Trace: Dem_SUD_API_13006 */
                /* Read Data Element from SW-C through RTE */
                LblDirty |= Dem_CaptureDataElementClass(
                    EventId,
                    LddEDRecord->PointToDataElementMap,
                    LddEDRecord->NumOfDataElementClass,
                    &OutBuffer[LulIdxForDst],
                    LddEDRecord->size);
              }
            }
          }
          LulIdxForDst += LddEDRecord->size;
        }
        else
        {
         /* @Trace: Dem_SUD_API_13011 */

        }
      }
    }
  }

  return LblDirty;
}
#endif

/*******************************************************************************
** Function Name        : Dem_CaptureJ1939FFClass                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is used to load the J1939 free frame data        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : J1939FFDataClass, EventId, BufSize                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OutBuffer                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_NUM_OF_J1939FREEZEFRAMECLASS > DEM_ZERO))
FUNC(boolean, DEM_CODE) Dem_CaptureJ1939FFClass(
  Dem_EventIdType EventId,
  CONSTP2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST) J1939FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize) 
{
  boolean LblDirty = DEM_FALSE;
  uint16 LusIdx;

  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  /* @Trace: Dem_SUD_API_13015 */
  if ((NULL_PTR != J1939FFDataClass) && (NULL_PTR != OutBuffer)) 
  {
    uint16 LusMax =
        J1939FFDataClass->PointToSpnMap +  J1939FFDataClass->NumOfSpnClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition always evaluates to true. Avoid the runtime error of the
     * polyspace */
    /* @Trace: Dem_SUD_API_13016 */
    /* @Trace: Dem_SUD_MACRO_072 */
    if ((BufSize >= J1939FFDataClass->size) &&
        (LusMax <= Dem_Max_ListOfSpnClassIndex))
    {
      uint32 LulIdxForDst = DEM_ZERO;
      /* @Trace: Dem_SUD_API_13017 */
      for (LusIdx = J1939FFDataClass->PointToSpnMap; LusIdx < LusMax; LusIdx++)
      {
        CONSTP2CONST(Dem_SPNClassType, AUTOMATIC, DEM_CONST)
        LddSpnClass =  &Dem_SPNClass[Dem_ListOfSPNClassIndex[LusIdx]];
        if ((LulIdxForDst + (uint32)LddSpnClass->size) <= BufSize)
        {
          /* @Trace: Dem_SUD_API_13019 */
          /* Read Data Element from SW-C through RTE */
          LblDirty |= Dem_CaptureDataElementClass(
              EventId,
              LddSpnClass->PointToDataElementMap,
              LddSpnClass->NumOfSpnDataElements,
              &OutBuffer[LulIdxForDst],
              LddSpnClass->size);
              
          LulIdxForDst += LddSpnClass->size;
        }
        else
        /* @Trace: Dem_SUD_API_13018 */
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        {
          /* Nothing to do */
        }
      }
    }
  }

  return LblDirty;
}
#endif

#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
/*******************************************************************************
** Function Name        : Dem_CaptureDataElementClass                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function is used to get the extended data or   **
 *                        freeze frame data from SW-C                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DataClassMap, EventId, BufSize, NumOfDataClass      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OutBuffer                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04085 SRS_Diag_04127
 */
FUNC(boolean, DEM_CODE)
Dem_CaptureDataElementClass(
  Dem_EventIdType EventId,
  uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize)
{
  boolean LblDirty = DEM_FALSE;
  uint16 LusIData = DEM_ZERO;
  const uint16 LusMaxData = DataClassMap + NumOfDataClass;
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  if ((NULL_PTR != OutBuffer) &&
      (LusMaxData <= DEM_MAX_LISTOFDATAELEMENTCLASSINDEX))
  {
    uint32 LulIdxForDst = DEM_ZERO;
  
    /* Loop through the no. of data elements for the Did */
    /* @Trace: Dem_SUD_API_13020 */
    for (LusIData = DataClassMap; LusIData < LusMaxData; LusIData++)
    {
      uint8 LucResult = E_NOT_OK;
      CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
      LddElementClass =
          &Dem_DataElementClass[Dem_ListOfDataElementClassIndex[LusIData]];
      /* @Trace: Dem_SUD_API_13021 */
      if ((LulIdxForDst + (uint32)LddElementClass->size) <= BufSize)
      {
        if (DEM_DATA_ELEMENT_EXTERNAL == LddElementClass->type)
        {
          /* @Trace: SWS_Dem_00282
           * The Dem module shall use the C-callback ReadDataElement
           * respectively the operation ReadData of the interface
           * DataServices_{Data} to collect all configured data elements which
           * are not typed as internal data elements (refer to
           * DemInternalDataElementClass) of the respective extended data
           * record.
           */
          /* @Trace: SWS_Dem_00261
           * The Dem module shall use the C-callback DemRead respectively the
           * operation ReadData of the interface DataServices_{Data} to collect
           * all configured data elements of the respective freeze frame.
           */
          if (NULL_PTR != LddElementClass->ReadFunc)
          {      
            /* @Trace: Dem_SUD_API_13024 */
            /* @IF_REQ : GeneralInterfaceSupported is false and callback event
             * data changed is none , use destBuffer */
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            /* @Trace: SWS_Dem_00463
             * If the SW-C or BSW module cannot not provide the requested data
             * (ReadDataElement returns other than E_OK), the Dem shall fill
             * the missing data with the padding value 0xFF, report the runtime
             * error DEM_E_NODATAAVAILABLE to the Det and continue its normal
             * operation.
             */
            LucResult =
                LddElementClass->ReadFunc(
                    Dem_EvEventDataCapture,
                    Dem_MonitorData[EventId].usMonitorData0);
            /* @Trace: Dem_SUD_API_13025 */
            if (E_NOT_OK == LucResult)
            {
              /* @Trace: Dem_SUD_API_13026 */
              DEM_REPORT_ERROR(
                  DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_NODATAAVAILABLE);
            }
          }
          /*Sender-Receiver port configured*/
          else if (NULL_PTR != LddElementClass->SRReadFunc)
          {
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            LucResult =
                LddElementClass->SRReadFunc(
                    Dem_EvEventDataCapture);

            if (E_NOT_OK == LucResult)
            {
              DEM_REPORT_ERROR(
                  DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_NODATAAVAILABLE);
            }
          }
          else
          {
            /* @Trace: Dem_SUD_API_13023 */
            DEM_REPORT_ERROR(
                DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_PARAM_POINTER);
          }
        }
        /* @Trace: SWS_Dem_00918
         * The Dem shall treat the non-integer data type uint8[n] either like
         * an integer data type of the matching size or leave the contents
         * uninterpreted in case the DemDataElementEndianness is configured to
         * OPAQUE.
         */
        /* @Trace: SWS_Dem_00919
         * The Dem shall interpret opaque data as uint8[n] and shall always map
         * it to an n-bytes sized signal.
         */
        else if (DEM_DATA_ELEMENT_OPAQUE == LddElementClass->type)
        {
          LucResult = E_OK;
        }
        else
        {
          /* Nothing to do */
        }
        /* internal data or returned value of ReadFunc is  E_NOT_OK */
        if (E_OK == LucResult)
        {
          uint32 LulK;
          /* @Trace: Dem_SUD_API_13329 */
          for (LulK = DEM_ZERO; LulK < LddElementClass->size; LulK++)
          {
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a defect>
             * Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned>
             * Polyspace bug */
            /* @Trace: Dem_SUD_API_13330 */
            if ((DEM_FALSE == LblDirty) &&
                (OutBuffer[LulIdxForDst + LulK] !=
                    Dem_EvEventDataCapture[LulK]))
            {
              /* @Trace: Dem_SUD_API_13331 */
              LblDirty = DEM_TRUE;
            }
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a defect>
             * Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned>
             * Polyspace bug */
            OutBuffer[LulIdxForDst + LulK] = Dem_EvEventDataCapture[LulK];
          }
        }
        else
        {
          uint32 LulK;
          /* @Trace: Dem_SUD_API_13027 */
          for (LulK = DEM_ZERO; LulK < LddElementClass->size; LulK++)
          {
           /* @Trace: Dem_SUD_API_13022 */
           /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a defect>
            * Rule violation by runtime error(orange) of PolySpace */
           /* polyspace<RTE:IDP:Not a defect:No action planned> Polyspace bug */
            OutBuffer[LulIdxForDst + LulK] = DEM_DATA_PADDING;
          }
        }
        
        LulIdxForDst += LddElementClass->size;
      }
    }
  }

  return LblDirty;
}

/*******************************************************************************
** Function Name        : Dem_OBDCaptureDataElementClass                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function is used to get the extended data or   **
**                        freeze frame data from SW-C for Obd                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DataClassMap, BufSize, NumOfDataClass               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OutBuffer                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE)
Dem_OBDCaptureDataElementClass(
  uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize)
{
  boolean LblDirty = DEM_FALSE;
  uint16 LusIData = DEM_ZERO;
  const uint16 LusMaxData = DataClassMap + NumOfDataClass;
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  /* @Trace: Dem_SUD_API_13028 */
  if ((NULL_PTR != OutBuffer) &&
      (LusMaxData <= DEM_MAX_LISTOFDATAELEMENTCLASSINDEX))
  {
    uint32 LulIdxForDst = DEM_ZERO;

    /* Loop through the no. of data elements for the Did */
    /* @Trace: Dem_SUD_API_13033 */
    for (LusIData = DataClassMap; LusIData < LusMaxData; LusIData++)
    {
      uint8 LucResult = E_NOT_OK;
      CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
      LddElementClass =
          &Dem_DataElementClass[Dem_ListOfDataElementClassIndex[LusIData]];
      /* @Trace: Dem_SUD_API_13034 */
      if ((LulIdxForDst + (uint32)LddElementClass->size) <= BufSize)
      {
        /* @Trace: Dem_SUD_API_13035 */
        if (DEM_DATA_ELEMENT_EXTERNAL == LddElementClass->type)
        {
          if (NULL_PTR != LddElementClass->ReadFunc)
          {
            /* @IF_REQ : GeneralInterfaceSupported is false and callback event
             * data changed is none , use destBuffer */
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            LucResult =
                LddElementClass->ReadFunc(Dem_EvEventDataCapture, DEM_ZERO);
            /* @Trace: Dem_SUD_API_13037 */
            if (E_NOT_OK == LucResult)
            {
              /* @Trace: Dem_SUD_API_13038 */
              DEM_REPORT_ERROR(
                  DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_NODATAAVAILABLE);
            }
          }
          /* Sender-Receiver port configured*/
          else if (NULL_PTR != LddElementClass->SRReadFunc)
          {
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            LucResult = LddElementClass->SRReadFunc(Dem_EvEventDataCapture);

            if (E_NOT_OK == LucResult)
            {
              DEM_REPORT_ERROR(
                  DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_NODATAAVAILABLE);
            }
          }
          else
          {
          /* @Trace: Dem_SUD_API_13036 */
            DEM_REPORT_ERROR(
                DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_PARAM_POINTER);
          }
        }

        /* internal data or returned value of ReadFunc is  E_NOT_OK */
        if (E_OK == LucResult)
        {
          uint32 LulK;
          /* @Trace: Dem_SUD_API_13040 */
          for (LulK = DEM_ZERO; LulK < LddElementClass->size; LulK++)
          {
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a
             * defect>
             * Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned>
             * Polyspace bug */
            /* @Trace: Dem_SUD_API_13030 */
            if ((DEM_FALSE == LblDirty) &&
                (OutBuffer[LulIdxForDst + LulK] !=
                    Dem_EvEventDataCapture[LulK]))
            {
              /* @Trace: Dem_SUD_API_13029 */
              LblDirty = DEM_TRUE;
            }
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a
             * defect>
             * Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned>
             * Polyspace bug */
            OutBuffer[LulIdxForDst + LulK] = Dem_EvEventDataCapture[LulK];
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_13039 */
          uint32 LulK;
          /* @Trace: Dem_SUD_API_13032 */
          for (LulK = DEM_ZERO; LulK < LddElementClass->size; LulK++)
          {
            /* @Trace: Dem_SUD_API_13031 */
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a
             * defect>
             * Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned>
             * Polyspace bug */
            OutBuffer[LulIdxForDst + LulK] = DEM_DATA_PADDING;
          }
        }

        LulIdxForDst += LddElementClass->size;
      }
    }
  }

  return LblDirty;
}
#endif

/*******************************************************************************
** Function Name        : Dem_CaptureInternalDataElementClass                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function is used to get the extended data or   **
**                        freeze frame data from Dem internally               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId, DTCOrigin, MemEntry, DataClassMap          **
**                        NumOfDataClass                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04068 SRS_Diag_04127 SRS_Diag_04134 SRS_Diag_04189
           SRS_Diag_04190
 */
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DEM_CODE) Dem_CaptureInternalDataElementClass(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  Dem_EventMemoryEntryPtrType MemEntry,
  const uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer)
{
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  /* @Trace: Dem_SUD_API_13041 */
  if ((NULL_PTR != MemEntry) && (NULL_PTR != DestBuffer))
  {
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpOutBuffer = DestBuffer;
    uint16 LusIdx = DEM_ZERO;
    uint16 LusMax = DataClassMap + NumOfDataClass;
    sint8 LscFDC = (sint8)0x00;
    /* @Trace: Dem_SUD_API_13052 */
    #if (DEM_J1939_SUPPORT == STD_ON)
    /* @Trace: Dem_SUD_API_13063 */
    Dem_J1939DcmLampStatusType LddLampStatus = {DEM_ZERO, DEM_ZERO};
    #endif
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition always evaluates to true. Avoid the runtime error of the
     * polyspace */
    /* @Trace: Dem_SUD_API_13072 */
    /* @Trace: Dem_SUD_MACRO_067 */
    if (LusMax <= DEM_MAX_LISTOFDATAELEMENTCLASSINDEX)
    {
      /* Loop through the no. of data elements for the Did */
      /* @Trace: Dem_SUD_API_13073 */
      for (LusIdx = DataClassMap; LusIdx < LusMax; LusIdx++)
      {
        /* @Trace: Dem_SUD_API_13074 */
        Std_ReturnType LddResult = E_NOT_OK;

        #if ((DEM_J1979_2_OBD_ON_UDS == STD_ON) && (DEM_NUMBER_OF_DTRS > DEM_ZERO))
        /* Trace: DEM_19792_06_01 */
        uint8 LucNumberOfDTR = DEM_ZERO;
        #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */
    
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
        LddElement =
            &Dem_DataElementClass[Dem_ListOfDataElementClassIndex[LusIdx]];
        /* @Trace: Dem_SUD_API_13075 */
        if ((DEM_DATA_ELEMENT_EXTERNAL != LddElement->type) &&
            (DEM_DATA_ELEMENT_BIG_ENDIAN != LddElement->type) &&
            (DEM_DATA_ELEMENT_LITTLE_ENDIAN != LddElement->type) &&
            (DEM_DATA_ELEMENT_OPAQUE != LddElement->type))
        {
          switch(LddElement->type)
          {            
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * If-condition evaluates to true or false according to
             * configuration */
            /* @Trace: SWS_Dem_00473
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_OVFLIND, then the Dem-internal value of the overflow
             * indication (refer to chapter 7.7.2.3) shall be mapped to the
             * respective data element as boolean (0 = False, 1 = True).
             */
            case DEM_DATA_ELEMENT_OVFLIND:
              /* @Trace: Dem_SUD_API_13076 */
              *LpOutBuffer =
                  (uint8)Dem_EvMem_GetEvMemOverflowFlag(
                      Dem_Event[EventId - DEM_ONE].ucEventMemDstIdx, DTCOrigin);
              LddResult = E_OK;
            break;

            case DEM_DATA_ELEMENT_AGINGCTR_UPCNT:
            case DEM_DATA_ELEMENT_AGINGCTR_DOWNCNT:
            case DEM_DATA_ELEMENT_AGINGCTR_UPCNT_FIRST_ACTIVE:
            /* @Trace: Dem_SUD_API_13077 */
              *LpOutBuffer = Dem_EvMem_GetAgingCounter(
                  EventId, MemEntry, LddElement->type);
              LddResult = E_OK;
            break;
            /* @Trace: SWS_Dem_00471
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_OCCCTR, then the Dem-internal value of the occurrence counter
             * (refer to chapter 7.3.2) shall be mapped to the respective data
             * element.
             */
            case DEM_DATA_ELEMENT_OCCCTR:
              /* @Trace: Dem_SUD_API_13042 */
              *LpOutBuffer = MemEntry->EventOccurrenceCounter;
              LddResult = E_OK;
            break;
            /* No impement */
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * Switch-expression never evaluates
             * to DEM_DATA_ELEMENT_SIGNIFICANCE */
            /* @Trace: SWS_Dem_00592
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_SIGNIFICANCE, then the (static) Dem-internal value of the
             * DTC significance (refer to chapter 7.4.6) shall be mapped to the
             * respective data element with 0 = OCCURRENCE and 1 = FAULT.
             */
            case DEM_DATA_ELEMENT_SIGNIFICANCE:
              /* @Trace: Dem_SUD_API_13043 */
              *LpOutBuffer =
                  DEM_GET_EVENTPARAM_SIGNIFICANCE(
                      Dem_Event[EventId - DEM_ONE].ParamFieldsA);
              LddResult = E_OK;
            break;
            /* @Trace: SWS_Dem_00820
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_CYCLES_SINCE_LAST_FAILED, then the Dem-internal value of the
             * operation cycle counter since last failed (refer to chapter
             * 7.6.2.1) shall be mapped to the respective data element.
             */
            /* @Trace: Dem_SUD_API_13044 */
            #if (DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
            /* @Trace: Dem_SUD_API_13055 */
            case DEM_DATA_ELEMENT_CYCLES_SINCE_LAST_FAILED:
              /* @Trace: Dem_SUD_API_13045 */
              *LpOutBuffer = MemEntry->cyclesSinLastFailedCounter;
              LddResult = E_OK;
            break;
            #endif
            /* @Trace: SWS_Dem_00821
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_CYCLES_SINCE_FIRST_FAILED, then the Dem-internal value of
             * the operation cycle counter since first failed (refer to chapter
             * 7.6.2.2) shall be mapped to the respective data element.
             */
            /* @Trace: Dem_SUD_API_13046 */
            #if (DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
            case DEM_DATA_ELEMENT_CYCLES_SINCE_FIRST_FAILED:
              /* @Trace: Dem_SUD_API_13047 */
              *LpOutBuffer = MemEntry->cyclesSinFirstFailedCounter;
              LddResult = E_OK;
            break;
            #endif
            /* @Trace: SWS_Dem_00818
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_MAX_FDC_SINCE_LAST_CLEAR, then the Dem-internal value of the
             * maximum Fault Detection Counter sincle last clear (refer to
             * chapter 7.7.3.6) shall be mapped to the respective data element.
             */
            /* @Trace: Dem_SUD_API_13049 */
            #if (DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
            /* @Trace: Dem_SUD_API_13056 */
            case DEM_DATA_ELEMENT_MAX_FDC_SINCE_LAST_CLEAR:
              /* @Trace: Dem_SUD_API_13048 */
              *LpOutBuffer =
                  (uint8)Dem_InternalDataMaxFdc
                    [Dem_Event[EventId - DEM_ONE].e_PointToDTC].maxFdcLastClear;
              LddResult = E_OK;
            break;
            #endif
            /* @Trace: SWS_Dem_00819
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_MAX_FDC_DURING_CURRENT_CYCLE, then the Dem-internal value of
             * the maximum Fault Detection Counter during current operation
             * cycle (refer to chapter 7.7.3.6) shall be mapped to the
             * respective data element.
             */
            /* @Trace: Dem_SUD_API_13051 */
            #if (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
            /* @Trace: Dem_SUD_API_13057 */
            case DEM_DATA_ELEMENT_MAX_FDC_DURING_CURRENT_CYCLE:
              /* @Trace: Dem_SUD_API_13050 */
              *LpOutBuffer =
                  (uint8)Dem_InternalDataMaxFdc
                    [Dem_Event[EventId - DEM_ONE].e_PointToDTC].
                      maxFdcCurrentCycle;
              LddResult = E_OK;
            break;
            #endif
            /* @Trace: SWS_Dem_00822
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_FAILED_CYCLES, then the Dem-internal value of the failed
             * operation cycle counter (refer to chapter 7.6.2.3) shall be
             * mapped to the respective data element.
             */
            /* @Trace: Dem_SUD_API_13054 */
            #if (DEM_INTERNAL_DATA_FAILED_CYCLES == STD_ON)
            /* @Trace: Dem_SUD_API_13058 */
            case DEM_DATA_ELEMENT_FAILED_CYCLES:
              /* @Trace: Dem_SUD_API_13053 */
              *LpOutBuffer = MemEntry->failedCyclesCounter;
              LddResult = E_OK;
            break;
            #endif
            /* @Trace: SWS_Dem_01045
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_CURRENT_FDC, then the fault detection counter (refer to
             * chapter 7.7.3) shall be mapped to the respective data element.
             */
            /* @Trace: SWS_Dem_01084
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_CURRENT_FDC, then the Dem-internal value of the current
             * fault detection counter (refer to subsubsection 7.7.3.3 and
             * subsubsection 7.7.3.4) shall be mapped to the respective data
             * element with the following value-translation:
             * [0..127]->[0x00..0x7F] and [-1..-128]->[0xFF..0x80].
             */
            case DEM_DATA_ELEMENT_CURRENT_FDC:
              if (E_OK == Dem_GetFaultDetectionCounter(EventId, &LscFDC))
              {
               /* @Trace: Dem_SUD_API_13060 */
                *LpOutBuffer =  *((uint8 *) &LscFDC);
                LddResult = E_OK;
              }
              else
              {
               /* @Trace: Dem_SUD_API_13059 */
                LddResult = E_NOT_OK;
              }
            break;

            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* Trace: DEM_19792_06_01 */
            /* @Trace: SWS_Dem_01367 in R21-11
             * Mapping of Monitor Activity Data on internal data element If
             * the DemInternalDataElement is set to DEM_MONITOR_ACTIVITY_DATA, the Dem
             * shall support per DTC the Monitor Activity Data according to SAE J1979-2 and map it
             * as value for this internal data element.
             */
            case DEM_DATA_ELEMENT_MONITOR_ACTIVITY_DATA:
              /* This Data is 
               * Monitor Activity Numerator (1 bytes) + 
               * Stored Monitor Activity Ratio (1 bytes) in SAE J1979-2_202104 */      
                LpOutBuffer[0U] = DEM_ZERO;
                LpOutBuffer[1U] = DEM_ZERO;

                /* Trace: DEM_COMB_04 */
                #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
                uint8 LucValueOfMinMAN = DEM_ZERO;
                uint8 LucValueOfMinMAR = DEM_ZERO;
                #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
                boolean LblMANExistFlag = DEM_FALSE;
                Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
                
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

                    for ( VAR(uint8, DEM_VAR) LucRatioIdIndex = DEM_ZERO;
                          LucRatioIdIndex < DEM_NUMBER_OF_RATIO_INFO;
                          LucRatioIdIndex++)
                    {
                      if (LddTmpEvId == Dem_GaaRatioIdInfo[LucRatioIdIndex].rid_EventId)
                      {
                        if (LblMANExistFlag == DEM_FALSE)
                        {
                          LblMANExistFlag = DEM_TRUE;
                          LucValueOfMinMAN = Dem_GaaMonitorActivityNumerator[LucRatioIdIndex];
                          LucValueOfMinMAR = Dem_GaaMonitorActivityRatio[LucRatioIdIndex];
                        }
                        else
                        {
                          /* Check Minimum Value */
                          if (LucValueOfMinMAN > Dem_GaaMonitorActivityNumerator[LucRatioIdIndex])
                          {
                            LucValueOfMinMAN = Dem_GaaMonitorActivityNumerator[LucRatioIdIndex];
                            LucValueOfMinMAR = Dem_GaaMonitorActivityRatio[LucRatioIdIndex];
                          }
                        }
                        break;
                      }
                    }
                    ++LddStartPos;
                  }
                }
                #endif /*(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)*/
                LpOutBuffer[0U] = LucValueOfMinMAN;
                LpOutBuffer[1U] = LucValueOfMinMAR;
                #else
                #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
                for ( VAR(uint8, DEM_VAR) LucRatioIdIndex = DEM_ZERO; 
                      LucRatioIdIndex < DEM_NUMBER_OF_RATIO_INFO; 
                      LucRatioIdIndex++)
                {
                  if (EventId == Dem_GaaRatioIdInfo[LucRatioIdIndex].rid_EventId)
                  {
                    LpOutBuffer[0U] = Dem_GaaMonitorActivityNumerator[LucRatioIdIndex];
                    LpOutBuffer[1U] = Dem_GaaMonitorActivityRatio[LucRatioIdIndex];
                    break;
                  }   
                }
                #endif /* (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) */
                #endif
                LddResult = E_OK;
              break;
            /* Trace: DEM_OBD_09_01 */
            /* @Trace: SWS_Dem_01365 in R21-11
             * Mapping of IUMPR ratio on internal data element If the Dem-
             * InternalDataElement is set to DEM_IUMPR, the Dem shall use the DTC assigned
             * IUMPR value in SAE J1979-2 format as value for this internal data element.
             */            
            /* @Trace: SWS_Dem_CONSTR_06175 in R21-11
             * Prerequisites for use of DEM_IUMPR If an internal
             * data element uses DEM_IUMPR the corresponding event shall be referenced by Dem-
             * DiagnosticEventRef.
             */
            case DEM_DATA_ELEMENT_IUMPR:  
                LpOutBuffer[0U] = DEM_ZERO;
                LpOutBuffer[1U] = DEM_ZERO;
                LpOutBuffer[2U] = DEM_ZERO;
                LpOutBuffer[3U] = DEM_ZERO;
                
                /* Trace: DEM_COMB_05 */
                #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
                uint16 LusValueOfMinNum = DEM_ZERO;
                uint16 LusValueOfMinDen = DEM_ZERO;
                #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
                boolean LblNumExistFlag = DEM_FALSE;                 
                VAR(float32, DEM_VAR) LusPrevMinRatioValue;
				        VAR(float32, DEM_VAR) LusRatioValue;
                Dem_CombinedDtcPCType LddCbDTCIUMPR = Dem_GetCbDTCByEventId(EventId);
                
                if (NULL_PTR != LddCbDTCIUMPR)
                {
                  Dem_NumOfEventIdType LddStartPos =
                      Dem_GetStartEventIdMapOfCbDTC(LddCbDTCIUMPR);
                  const Dem_NumOfEventIdType LddEndPos =
                      Dem_GetEndEventIdMapOfCbDTC(LddCbDTCIUMPR);

                  while (LddStartPos < LddEndPos)
                  {
                    Dem_EventIdType LddTmpEvId =
                        Dem_ListOfCombinedEvents[LddStartPos];

                    for ( VAR(uint8, DEM_VAR) LucRatioIdIndex = DEM_ZERO;
                          LucRatioIdIndex < DEM_NUMBER_OF_RATIO_INFO;
                          LucRatioIdIndex++)
                    {
                      if (LddTmpEvId == Dem_GaaRatioIdInfo[LucRatioIdIndex].rid_EventId)
                      {
					  
				                if(Dem_GaaIumprDenominator[LucRatioIdIndex] != 0)
                        {
                          LusRatioValue = ((float32)Dem_GaaIumprNumerator[LucRatioIdIndex] / 
                          (float32)Dem_GaaIumprDenominator[LucRatioIdIndex]);
                        }
                        else
                        {
                          LusRatioValue = (float32)Dem_GaaIumprNumerator[LucRatioIdIndex];
                        }
						
                        if (LblNumExistFlag == DEM_FALSE)
                        {
                          LblNumExistFlag = DEM_TRUE;
                          LusPrevMinRatioValue = LusRatioValue;          
                          LusValueOfMinNum = Dem_GaaIumprNumerator[LucRatioIdIndex];
                          LusValueOfMinDen = Dem_GaaIumprDenominator[LucRatioIdIndex];
                        }
                        else
                        {
                          /* Check Minimum Ratio */
                          if (LusPrevMinRatioValue > LusRatioValue)
                          {
                            LusPrevMinRatioValue = LusRatioValue;          
                            LusValueOfMinNum = Dem_GaaIumprNumerator[LucRatioIdIndex];
                            LusValueOfMinDen = Dem_GaaIumprDenominator[LucRatioIdIndex];
                          }
                          else if (LusPrevMinRatioValue < LusRatioValue)
                          {
                            /* Do Nothing */
                          }
                          else
                          {
                            /* If Same Ratio, Change only when Numerator or Denominator is bigger than prev ratio */
                            if ( (Dem_GaaIumprNumerator[LucRatioIdIndex] > LusValueOfMinNum ) || 
                                (Dem_GaaIumprDenominator[LucRatioIdIndex] > LusValueOfMinDen )  )
                            {
                              LusPrevMinRatioValue = LusRatioValue;          
                              LusValueOfMinNum = Dem_GaaIumprNumerator[LucRatioIdIndex];
                              LusValueOfMinDen = Dem_GaaIumprDenominator[LucRatioIdIndex];
                            }
                          }
                        }
                        break;
                      }
                    }
                    ++LddStartPos;
                  }
                }
                #endif /*#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)*/
                /* SAE J1979-2 ExtendedDataRecord 0x91 DTC Based IUMPR */
                /* Monitor Completion Counts 2 Bytes */
                LpOutBuffer[0U] = (uint8)(LusValueOfMinNum >> DEM_EIGHT);
                LpOutBuffer[1U] = (uint8)(LusValueOfMinNum);
                /* Monitor Condition Encountered Counts 2 Bytes */
                LpOutBuffer[2U] = (uint8)(LusValueOfMinDen >> DEM_EIGHT);
                LpOutBuffer[3U] = (uint8)(LusValueOfMinDen);
                #else
                #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
                for ( VAR(uint8, DEM_VAR) LucRatioIdIndex = DEM_ZERO; 
                      LucRatioIdIndex < DEM_NUMBER_OF_RATIO_INFO; 
                      LucRatioIdIndex++)
                {
                  if (EventId == Dem_GaaRatioIdInfo[LucRatioIdIndex].rid_EventId)
                  {
                    /* SAE J1979-2 ExtendedDataRecord 0x91 DTC Based IUMPR */
                    /* Monitor Completion Counts 2 Bytes */
                    LpOutBuffer[0U] = (uint8)(Dem_GaaIumprNumerator[LucRatioIdIndex] >> DEM_EIGHT);
                    LpOutBuffer[1U] = (uint8)(Dem_GaaIumprNumerator[LucRatioIdIndex]);
                    /* Monitor Condition Encountered Counts 2 Bytes */
                    LpOutBuffer[2U] = (uint8)(Dem_GaaIumprDenominator[LucRatioIdIndex] >> DEM_EIGHT);
                    LpOutBuffer[3U] = (uint8)(Dem_GaaIumprDenominator[LucRatioIdIndex]);
                    break;
                  }   
                }
                #endif /*(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)*/
                #endif
                LddResult = E_OK;
              break;
            /* Trace: DEM_OBD_06_03 */
            /* @Trace: SWS_Dem_01366 in R21-11
             * Mapping of DTR value on internal data element If the Dem-
             * InternalDataElement is set to DEM_DTR, the Dem shall use the DTC assigned
             * DTR value in SAE J1979-2 format as value for this internal data element.
             */            
            /* @Trace: SWS_Dem_CONSTR_06176 in R21-11
             * Prerequisites for use of DEM_DTR If an inter-
             * nal data element uses DEM_DTR the corresponding event shall be referenced by
             * DemDtrEventRef.
             */
            case DEM_DATA_ELEMENT_DTR:            
                /* Trace: DEM_GEN_14 */
                #if(DEM_NUMBER_OF_DTRS > DEM_ZERO)
                /* This Data is Diagnostic Test Result in 1979-2 */
                for ( VAR(uint8, DEM_VAR) LucDTRIdIndex = DEM_ZERO; 
                      LucDTRIdIndex < DEM_NUMBER_OF_DTRS; 
                      LucDTRIdIndex++)
                {
                  if (EventId == Dem_GaaDtrInfo[LucDTRIdIndex].usEventId)
                  {                 
                    /* SAE J1979-2 ExtendedDataRecord 0x92 DTC Based Test Result */

                    /* Unit and scaling ID 2 Bytes */
                    /* Because of usUaSID is only 1 byte, so 1st byte usUaSID stored always 0 */
                    LpOutBuffer[DEM_ONE+(DEM_EIGHT*LucNumberOfDTR)] = DEM_ZERO;
                    LpOutBuffer[DEM_TWO+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_GaaDtrInfo[LucDTRIdIndex].usUaSID);

                    /* Test Value 2 Byte */
                    LpOutBuffer[DEM_THREE+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_DtrData[LucDTRIdIndex].Testvalue >> DEM_EIGHT);
                    LpOutBuffer[DEM_FOUR+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_DtrData[LucDTRIdIndex].Testvalue);

                    /* Minimum Test Limit 2 Byte */
                    LpOutBuffer[DEM_FIVE+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_DtrData[LucDTRIdIndex].Lowlimvalue >> DEM_EIGHT);
                    LpOutBuffer[DEM_SIX+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_DtrData[LucDTRIdIndex].Lowlimvalue);

                    /* Maximum Test Limit 2 Byte */
                    LpOutBuffer[DEM_SEVEN+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_DtrData[LucDTRIdIndex].Upplimvalue >> DEM_EIGHT);
                    LpOutBuffer[DEM_EIGHT+(DEM_EIGHT*LucNumberOfDTR)] = 
                      (uint8)(Dem_DtrData[LucDTRIdIndex].Upplimvalue);
                  
                    LucNumberOfDTR++;   
                  }   
                }                
                /* Number of Test Results 1 Byte */
                *LpOutBuffer = LucNumberOfDTR;
                #endif
                LddResult = E_OK;
              break;

            #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */
            
            /* @Trace: SWS_Dem_01334
             * If DemInternalDataElement is set to DEM_MONITOR_DATA_0, the Dem
             * shall use the 32 bit value of the provided monitorData0
             * parameter value of the call Dem_SetEventStatusWithMonitorData as
             * internal data value.
             */
            /* @Trace: SWS_Dem_01330
             * If the ReadData operation is configured to provide the
             * monitorData0, the Dem shall add the monitorData0 from the
             * Dem_SetEventStatusWithMonitorData to the Read-Data operation
             * parameter monitorData0.
             */
            case DEM_DATA_ELEMENT_MONITOR_DATA_0:
              /* @Trace: Dem_SUD_API_13061 */
              *LpOutBuffer = (uint8)Dem_MonitorData[EventId].usMonitorData0;
              LddResult = E_OK;
            break;
            /* @Trace: SWS_Dem_01314
             * If DemInternalDataElement is set to DEM_MONITOR_DATA_1, the Dem
             * shall use the 32 bit value of the provided monitorData1
             * parameter value of the call Dem_SetEventStatusWithMonitorData
             * as internal data value.
             */
            case DEM_DATA_ELEMENT_MONITOR_DATA_1:
              /* @Trace: Dem_SUD_API_13062 */
              *LpOutBuffer = (uint8)Dem_MonitorData[EventId].usMonitorData1;
              LddResult = E_OK;
            break;

            /* @Trace: SWS_Dem_01391
             * If DemInternalDataElement is set to DEM_DTC_PRIORITY, the Dem
             * shall set the value of this internal data element to the DTC
             * priority assigned by DemDTCPriority for this DTC. The length of
             * this internal data element is one byte.
             */
            case DEM_DATA_ELEMENT_DTC_PRIORITY:
              /* @Trace: Dem_SUD_API_13064 */
              *LpOutBuffer = Dem_Event[EventId - DEM_ONE].ucEventPriority;
              LddResult = E_OK;
            break;
            /* @Trace: SWS_Dem_01310
             * If the configuration parameter DemInternalDataElement is set to
             * DEM_J1939LAMP_STATUS, then the lamp status (refer chapter 7.10.3)
             * in the format of type Dem_J1939DcmLampStatusType shall be mapped
             * to the respective data element.
             */
            /* @Trace: Dem_SUD_API_13065 */
            #if (DEM_J1939_SUPPORT == STD_ON)
            /* @Trace: Dem_SUD_API_13068 */
            case DEM_DATA_ELEMENT_J1939LAMP_STATUS:
            if (E_OK == Dem_GetJ1939LampStatus(EventId, &LddLampStatus))
            {
              /* @Trace: Dem_SUD_API_13067 */
              *LpOutBuffer = LddLampStatus.LampStatus;
              LddResult = E_OK;
            }
            else
            {
              /* @Trace: Dem_SUD_API_13066 */
              LddResult = E_NOT_OK;
            }
            break;
            #endif
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * Default switch clause is unreachable. switch-expression */
            default :
              DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_NODATAAVAILABLE);
              LddResult = E_NOT_OK;
            break;
          }
          /* @IF_REQ : Det Error */
          /* @Trace: Dem_SUD_API_13069 */
          if (E_OK != LddResult)
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * If-condition evaluates to true or false according to
           * configuration */
          {
            Dem_SizeOfDataElementClassType LddK;
            /* @Trace: Dem_SUD_API_13070 */
            for (LddK = DEM_ZERO; LddK < LddElement->size; LddK++)
            {
             /* @Trace: Dem_SUD_API_13071 */
              LpOutBuffer[LddK] = DEM_DATA_PADDING;
            }
          }
        }
        LpOutBuffer = &LpOutBuffer[LddElement->size];
      }
    }
  }
}

#endif

/*******************************************************************************
** Function Name        : Dem_ReadDataOfExtendedData                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Reads the extended data from an event memory entry  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EvData, DTCOrigin, ExtendedDataNumber, BufSize      **
**                        NumOfDataClass                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
/* @Trace: Dem_SUD_MACRO_109 */
#if (DEM_SIZE_OF_EXTENDED_DATA >  DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE)
Dem_ReadDataOfExtendedData(
  Dem_EventRelatedDataPCType EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_ExtendedDataNumberType  ExtendedDataNumber,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Dem_ReturnReadEventDataType LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
  /* Note: range of EvData->EventIdRef */
  if ( 
      (NULL_PTR != DestBuffer)
      && 
      (EvData->EDClassPos < DEM_NUM_OF_EXTENDEDDATACLASS)
      &&
      (EvData->EventIdRef <= DEM_NUMBER_OF_EVENTS)
      &&
      (DEM_NO_EVENT != EvData->EventIdRef)
  )
  {    
    Dem_ExtendedDataClassPCType LddExtendedData =
        &Dem_ExtendedDataClass[EvData->EDClassPos];
      /* In case of BufSize is DEM_ZERO, Read FF regardless of a size of
       * DestBuffer */
    uint16 LusExtendedDataSize = Dem_GetSizeOfExtendedData(
        LddExtendedData, ExtendedDataNumber, NULL_PTR
        #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
        , EvData->EventIdRef
        #endif
        );
    uint16 LusBufSizeForDst =
        (NULL_PTR != BufSize) ? *BufSize : LusExtendedDataSize;
    
    /* If extended data record number is invalid , 
     * returned LusExtendedDataSize value of Dem_GetSizeOfExtendedData is
     * zero */
    if (DEM_ZERO == LusExtendedDataSize)
    {
      /* @Trace: Dem_SUD_API_13085 */
      LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    }
    else if ((DEM_ZERO == LusBufSizeForDst) ||
             (LusExtendedDataSize > LusBufSizeForDst) )
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition evaluates to true or false according to configuration */
    {
      /* @Trace: Dem_SUD_API_13086 */
      LddRetVal = DEM_GET_READEVDATA_WRONG_BUFFERSIZE;
    }
    else
    {
      Dem_EventMemoryEntryPtrType LddMemEntry =
          Dem_EvMem_FindEntry(EvData->EventIdRef, DTCOrigin);
      if (NULL_PTR == LddMemEntry)
      {
        /* @Trace: Dem_SUD_API_13087 */
        LddRetVal = DEM_GET_READEVDATA_NOT_STORED;
      }
      else
      {
        uint32 LulBufSizeForSrc = DEM_ZERO;
        P2VAR(uint8, AUTOMATIC, DEM_VAR) LpSrc =
            Dem_EvMem_GetEDBuffer(EvData, LddMemEntry, &LulBufSizeForSrc);
        
        Dem_NumOfExtendedDataRecordClassType LddIEDR;
        Dem_NumOfExtendedDataRecordClassType LddMaxEDR;

        LddMaxEDR =
            LddExtendedData->PointToEDRecordMap +
            LddExtendedData->NumOfEDRecordClass;
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        /* @Trace: Dem_SUD_API_13088 */
        if ((NULL_PTR != LpSrc) &&
            (LulBufSizeForSrc >= LddExtendedData->size) &&
            (LddMaxEDR <= Dem_Max_ListOfEDRecordClassIndex))
        {        
          uint32 LulIdxForSrc = DEM_ZERO;
          uint32 LulIdxForDst = DEM_ZERO;
          /* Loop through the no. of data elements for the Did */
          /* @Trace: Dem_SUD_API_13089 */
          for (LddIEDR = LddExtendedData->PointToEDRecordMap;
               LddIEDR < LddMaxEDR;
               LddIEDR++)
          {
            P2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST) 
            LddEDRecord =
                &Dem_ExtendedDataRecordClass
                  [Dem_ListOfEDRecordClassIndex[LddIEDR]];

            if (((LulIdxForDst + (uint32)LddEDRecord->size) >
                    LusBufSizeForDst) ||
                ((LulIdxForSrc + (uint32)LddEDRecord->size) >
                    LulBufSizeForSrc))
            {
              /* @Trace: Dem_SUD_API_13090 */
              DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_OUT_OF_BOUNDS);
            }
            else
            {
              /* if ExtendedDataNumber is equal to DEM_MAX_RECORD, report all
               * records. */
              /* @Trace: Dem_SUD_API_13091 */
              if ((ExtendedDataNumber ==
                     LddEDRecord->ExtendedDataRecordNumber) ||
                  (DEM_MAX_RECORD == ExtendedDataNumber) )
              {               
                Dem_SizeOfExtendedDataClassType LddIdx;
                /* Copy external data element from event memory entry */
                /* @Trace: SWS_Dem_00989
                 * The format of the data in the destination buffer (DestBuffer)
                 * of the function Dem_GetEventExtendedDataRecordEx is raw
                 * hexadecimal values and contains no header-information like
                 * RecordNumber.
                 */
                for (LddIdx = DEM_ZERO; LddIdx < LddEDRecord->size; LddIdx++)
                {
                  /* @Trace: Dem_SUD_API_13079 */
                  /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations
                   * a defect> Rule violation by runtime error(orange) of
                   * PolySpace */
                  DestBuffer[LulIdxForDst + LddIdx] =
                      LpSrc[LulIdxForSrc + LddIdx];
                }
                /* @Trace: Dem_SUD_API_13092 */
                /* Read Data Internal Element such as aging counter, healing
                 * counter */
                Dem_CaptureInternalDataElementClass(
                    EvData->EventIdRef,
                    DTCOrigin,
                    LddMemEntry,
                    LddEDRecord->PointToDataElementMap,
                    LddEDRecord->NumOfDataElementClass,
                    &DestBuffer[LulIdxForDst]);
                LulIdxForDst += LddEDRecord->size;
                /* @Trace: Dem_SUD_API_13080 */
                if (DEM_MAX_RECORD != ExtendedDataNumber)
                {
                 /* @Trace: Dem_SUD_API_13081 */
                  break; /* exit loop */
                }
              }
              LulIdxForSrc += LddEDRecord->size;
            }
          }
          /* @Trace: Dem_SUD_API_13084 */
          if (DEM_ZERO != LulIdxForDst)
          {
            /* @Trace: Dem_SUD_API_13083 */
            if (NULL_PTR != BufSize)
            {
              /* @Trace: Dem_SUD_API_13082 */
              *BufSize = LusExtendedDataSize;
            }
            LddRetVal = DEM_GET_READEVDATA_OK;
          } 
        }
      }
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_13078 */
    LddRetVal = DEM_GET_READEVDATA_WRONG_DTC;
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetJ1939FreezeFrameData                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Reads the J1939 Freeze Frame data from an event     **
**                        memory entry                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : event, DTCOrigin, J1939FFType, BufSize              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_122 */
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO))
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetJ1939FreezeFrameData(
    Dem_EventParameterCPCType event,
    Dem_DTCOriginType DTCOrigin,
    P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize,
    Dem_J1939DcmSetFreezeFrameFilterType J1939FFType)
{

  Dem_ReturnReadEventDataType LddRetVal = E_OK;

  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDest = DestBuffer;
  Dem_NumOfJ1939FreezeFrameClassType LddFFClassPos;

  P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST)
  LddJ1939ffDataClass = NULL_PTR;
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC = NULL_PTR;
  P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) LddEvData;
  /* @Trace: Dem_SUD_API_13104 */
  if (DEM_MAX_NUMBER_OF_DTC > event->e_PointToDTC)
  {
    /* @Trace: Dem_SUD_API_13093 */
    LddCbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];
  }
  LddEvData = &Dem_EventRelatedData[event->e_PointToData];
  /* @Trace: Dem_SUD_API_13107 */
  if ((NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  {
    /* @Trace: Dem_SUD_API_13108 */
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  /* @Trace: Dem_SUD_API_13109 */
  if (NULL_PTR != LddCbDTC)
  {
    /* @Trace: Dem_SUD_API_13110 */
    if (Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_J1939, LddCbDTC) == DEM_FALSE)
    {
      /* No J1939 event */
      /* @Trace: Dem_SUD_API_13111 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
  }

  if (J1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME)
  {
    /* @Trace: Dem_SUD_API_13113 */
    LddFFClassPos = LddEvData->J1939EXFFClassPos;
  }
  else 
  {
    /* @Trace: Dem_SUD_API_13112 */
    LddFFClassPos = LddEvData->J1939FFClassPos;
  }
  /* @Trace: Dem_SUD_API_13094 */
  if (DEM_NO_IDX_U16 == LddFFClassPos)
  {
    /* No J1939 freeze frame configured of event. */
    /* @Trace: Dem_SUD_API_13095 */
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  if (DEM_NUM_OF_J1939FREEZEFRAMECLASS > LddFFClassPos)
  {
    LddJ1939ffDataClass = &Dem_J1939FreezeFrameClass[LddFFClassPos];
    /* @Trace: Dem_SUD_API_13096 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Error Configuration. */
    if (DEM_ZERO == LddJ1939ffDataClass->size)
    {
      /* @Trace: Dem_SUD_API_13098 */
      /* No obd freeze frame configured */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */

  }
  else
  {
    /* @Trace: Dem_SUD_API_13097 */
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  /* @Trace: Dem_SUD_API_13099 */
  if (E_OK == LddRetVal)
  {

    uint32 LulBufSizeForSrc = DEM_ZERO;
    Dem_EventMemoryEntryPtrType LddMemEntry =
        Dem_EvMem_FindEntry(LddEvData->EventIdRef, DTCOrigin);
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpSrc =
        Dem_EvMem_GetJ1939FFBuffer(
            LddEvData,
            LddMemEntry,
            &LulBufSizeForSrc,
            J1939FFType);
    uint16 LusISpn;
    uint16 LusMaxSpn;
    Dem_SizeOfSpnClassType LddIdx;

    LusMaxSpn =
        LddJ1939ffDataClass->PointToSpnMap + LddJ1939ffDataClass->NumOfSpnClass;

    if ((NULL_PTR != LpSrc) &&
        (LulBufSizeForSrc >= LddJ1939ffDataClass->size) &&
        (LusMaxSpn <= Dem_Max_ListOfSpnClassIndex))
    {

      for (LusISpn = LddJ1939ffDataClass->PointToSpnMap;
           LusISpn < LusMaxSpn;
           LusISpn++)
      {
        CONSTP2CONST(Dem_SPNClassType, AUTOMATIC, DEM_CONST) SPN =
            &Dem_SPNClass[Dem_ListOfSPNClassIndex[LusISpn]];
        /* @Trace: Dem_SUD_API_13105 */
        for (LddIdx = DEM_ZERO; LddIdx < SPN->size; LddIdx++)
        {
          /* @Trace: Dem_SUD_API_13103 */
          LpDest[LddIdx] = LpSrc[LddIdx];
        }
        LpDest = &LpDest[SPN->size]; /* For Read all */
        LpSrc = &LpSrc[SPN->size];
      }
      /* @Trace: Dem_SUD_API_13101 */
      if (LpDest != DestBuffer)
      {
        /* @Trace: Dem_SUD_API_13102 */
        if (NULL_PTR != BufSize)
        {
          /* @Trace: Dem_SUD_API_13106 */
          *BufSize = (uint16)LddJ1939ffDataClass->size;
        }
        LddRetVal = E_OK;
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_13100 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    
  }  
  return LddRetVal;

}
#endif

/*******************************************************************************
** Function Name        : Dem_GetWWHFreezeFrameData                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Reads the WWH Freeze Frame data from an event       **
**                        memory entry                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EvData, DTCOrigin, DataIdentifier, BufSize          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04024
 */
/* @Trace: Dem_SUD_MACRO_112 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetWWHFreezeFrameData(
    Dem_EventRelatedDataPCType  EvData,
    Dem_DTCOriginType DTCOrigin,
    Dem_DataIdentifierType DataIdentifier,
    P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Dem_ReturnReadEventDataType LddRetVal = DEM_GET_READEVDATA_OK;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDest = DestBuffer;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpSrc = NULL_PTR;

  if ((NULL_PTR == DestBuffer) || (NULL_PTR == BufSize) || (NULL_PTR == EvData))
  {
    /* @Trace: Dem_SUD_API_13114 */
    LddRetVal = DEM_GET_READEVDATA_WRONG_DTC;
  }
  else if (DEM_NO_IDX_U8 == EvData->WWHOBDFFClassPos)
  {
    /* @Trace: Dem_SUD_API_13120 */
    LddRetVal = DEM_GET_READEVDATA_WRONG_DTC;
  }
  else
  {
    /* @Trace: Dem_SUD_API_13121 */
    /* Nothing to do */
  }
  /* @Trace: Dem_SUD_API_13122 */
  if (DEM_GET_READEVDATA_OK == LddRetVal)
  {
    P2CONST(Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONST) LddWWHFFDataClass =
        &Dem_FreezeFrameClass[EvData->WWHOBDFFClassPos];
    Dem_EventMemoryEntryCPType LddMemEntry =
        Dem_EvMem_FindEntry(EvData->EventIdRef, DTCOrigin);

    LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    if (NULL_PTR != LddMemEntry)
    {
      uint16 LusMaxDID =
          LddWWHFFDataClass->PointToDidMap +
          LddWWHFFDataClass->NumOfDidClass;
      /* @NumOfStoredRecords shall be greater than 0 */

      /* read recent freeze frame record number, but not specific record
       * number */
      /* @Trace: SWS_Dem_00479
       * The function Dem_GetEventFreezeFrameDataEx shall report the data of
       * the DID (defined by parameter DataId) in the requested freeze frame
       * record (defined by parameter RecordNumber, except RecordNumber equal
       * 0xFF) of the requested diagnostic event (EventId). If the RecordNumber
       * is equal to 0xFF and parameter DemTypeOfFreezeFrameRecordNumeration is
       * set to  DEM_FF_RECNUM_CALCULATED (refer to DemPrimaryMemory or
       * DemUserDefinedMemory) the most recent record shall be used, otherwise
       * E_NOT_OK shall be returned.
       */

      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true. Avoid the runtime error of the
       * polyspace */
      /* @Trace: Dem_SUD_MACRO_068 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      if ((DEM_ZERO != LusMaxDID) &&
          (LusMaxDID <= Dem_Max_ListOfDidClassIndex)) /* Note : <= */
      {
        uint16 LusIDID = DEM_ZERO;
        /*  |Record Number(or N/A)| Num of DIDs | 1st DID | Data #1|...
         *  | Nth DID | Data #n |
         *
         *  Record Number : Record Number of Freeze Frame
         *  Num of DIDs : Number of all the DID.
         *  Nth DID : Size of the Nth DID */
        LpSrc = LddMemEntry->data;
        /* @Trace: Dem_SUD_API_13115 */
        for (LusIDID = LddWWHFFDataClass->PointToDidMap;
             LusIDID < LusMaxDID ;
             LusIDID++)
        {
          /* @Trace: Dem_SUD_API_13116 */
          /* @Trace: Dem_SUD_MACRO_091 */
          #if (DEM_NUM_OF_DIDCLASS > DEM_ZERO)
          Dem_DidClassCPCType LddDID =
              &Dem_DidClass[Dem_ListOfDidClassIndex[LusIDID]];
          /* @Trace: Dem_SUD_API_13117 */
          if ((LddDID->DataId == DataIdentifier))
          {
            /* Copy external data element from event memory entry */
            /* @Trace: Dem_SUD_API_13118 */
            for (Dem_SizeOfDidClassType LddIdx = DEM_ZERO;
                                        LddIdx < LddDID->size;
                                        LddIdx++)
            {
              /* @Trace: Dem_SUD_API_13119 */
              LpDest[LddIdx] = LpSrc[LddIdx];
            }
            LpDest = &LpDest[LddDID->size]; /* For Read all */
          }
          LpSrc = &LpSrc[LddDID->size];
          #endif
        }
        /* @Trace: Dem_SUD_API_13125 */
        if (LpDest != DestBuffer)
        {
          /* @Trace: Dem_SUD_API_13127 */
          if (NULL_PTR != BufSize)
          {
            /* @Trace: Dem_SUD_API_13126 */
            *BufSize = LddWWHFFDataClass->size;
          }
          LddRetVal = DEM_GET_READEVDATA_OK;
        }
      }
      else
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition evaluates to true or false according to configuration */
      {
       /* @Trace: Dem_SUD_API_13124 */
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_13123 */
      LddRetVal = DEM_GET_READEVDATA_NOT_STORED;
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetReadDataOfPID                                **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Provision to give the pid data                      **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : entry, ReportTotalPid, PidIdentifier                **
 **                       ReportTotalDataElement, DataElementIndexOfPID       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : DestBuffer                                          **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: Dem_SUD_MACRO_119 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetReadDataOfPID(
  Dem_EventMemoryEntryCPType entry,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  const boolean ReportTotalPid,
  const Dem_PidIdentifierType PidIdentifier,
  const boolean ReportTotalDataElement,
  const Dem_NumOfDataElementClassType DataElementIndexOfPID)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  #if (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
  /* @Dem_EventIdType EventId = DEM_NO_EVENT;*/
  Dem_NumOfPidClassType LddIndexOfPid = DEM_ZERO;
  Dem_NumOfPidClassType LddNumOfPid = DEM_ZERO;

  /* @P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) EvData = NULL_PTR;*/

  /* @Dem_EventParameterPCType event = NULL_PTR;*/

  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpSrc = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = DestBuffer;


  if ((DEM_TRUE == ReportTotalPid) && (DEM_FALSE == ReportTotalDataElement))
  {
    /* wrong usage */
    /* @Trace: Dem_SUD_API_13128 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_WRONG_CONDITION);
  }
  else
  {
    CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) LddPID =
        Dem_GaaObd[DEM_ZERO].PidClass;
    LddNumOfPid = Dem_GaaObd[DEM_ZERO].NumOfPidClass;
    /* @Trace: Dem_SUD_API_13137 */
    if (NULL_PTR != entry)
    {
      /* Get buffer of event memory entry */
      LpSrc = entry->data;
      uint32 LulBufSize = DEM_SIZE_OF_EVENT_DATA;
      /* @Trace: Dem_SUD_API_13138 */
      for (LddIndexOfPid = DEM_ZERO;
           LddIndexOfPid < LddNumOfPid;
           LddIndexOfPid++)
      {
        const Dem_NumOfPidDataElementType
        LddNumOfDataElement = LddPID[LddIndexOfPid].NumOfPidDataElements;

        if ((DEM_TRUE == ReportTotalPid) ||
            (PidIdentifier == LddPID[LddIndexOfPid].PidIdentifier))
        {
          Dem_NumOfPidDataElementType LddPids;
          /* @Trace: Dem_SUD_API_13141 */
          for (LddPids = DEM_ZERO;
               LddPids < LddNumOfDataElement;
               LddPids++)
          {
            CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
            LddListOfDataElementPtr =
                &Dem_DataElementClass
                  [Dem_ListOfDataElementClassIndex
                     [Dem_GaaPid[LddIndexOfPid].PointToDataElementMap]];
            /* @Trace: Dem_SUD_API_13142 */
            if (LddListOfDataElementPtr[LddPids].size <= LulBufSize)
            {
              /* @Trace: Dem_SUD_API_13143 */
              if (((DEM_TRUE == ReportTotalDataElement) ||
                   (DataElementIndexOfPID == LddPids)))
              {
                Dem_SizeOfDataElementClassType LddIdx;
                Dem_SizeOfDataElementClassType LddSize =
                    LddListOfDataElementPtr[LddPids].size;
                /* @Trace: Dem_SUD_API_13144 */
                for (LddIdx = DEM_ZERO; LddIdx < LddSize; LddIdx++)
                {
                  /* @Trace: Dem_SUD_API_13133 */
                  LpDst[LddIdx] = LpSrc[LddIdx];
                }
                LulBufSize -= LddListOfDataElementPtr[LddPids].size;
                /* @Trace: Dem_SUD_API_13129 */
                if (LulBufSize > DEM_ZERO)
                {
                  /* @Trace: Dem_SUD_API_13130 */
                  LpSrc = &LpSrc[LddListOfDataElementPtr[LddPids].size];
                  LpDst = &LpDst[LddListOfDataElementPtr[LddPids].size];
                }
                /* @Trace: Dem_SUD_API_13132 */
                if (DEM_FALSE == ReportTotalDataElement)
                {
                  /* @Trace: Dem_SUD_API_13131 */
                  break; /* Exit loop */
                }
              }
            }
          }
          /* @Trace: Dem_SUD_API_13140 */
          if (DEM_FALSE == ReportTotalPid)
          {
           /* @Trace: Dem_SUD_API_13134 */
            break; /* Exit loop */
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_13139 */
          LpSrc = &LpSrc[LddPID[LddIndexOfPid].size];
        }
      }
    }
    /* @Trace: Dem_SUD_API_13135 */
    if (LpDst != DestBuffer)
    {
      /* @Trace: Dem_SUD_API_13136 */
      LddRetVal = E_OK;
    }
  }
  #endif
  return LddRetVal;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetOBDFreezeFrameData                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Reads the OBD Freeze Frame data from an event       **
 **                       memory entry                                        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event, DTCOrigin, BufSize                           **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : DestBuffer                                          **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: Dem_SUD_MACRO_131 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOBDFreezeFrameData(
    Dem_EventParameterPCType event,
    Dem_DTCOriginType DTCOrigin,
    P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Std_ReturnType LddReVal = (uint8)DEM_DATA_OK;
  P2VAR(Dem_EventMemoryEntryType,AUTOMATIC,DEM_CONST) LddEntry = NULL_PTR;
  Dem_SizeOfOBDFreezeFrameDataType LddSize = DEM_ZERO;
  Std_ReturnType LddResult = E_NOT_OK;

  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC = NULL_PTR;
  if (event->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
  {
    /* @Trace: Dem_SUD_API_13145 */
    LddCbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];
  }

  boolean LblIsFormatOBD = DEM_FALSE;
  /* @Trace: Dem_SUD_API_13151 */
  if (NULL_PTR != LddCbDTC)
  {
    /* @Trace: Dem_SUD_API_13152 */
    if (DEM_DTC_FORMAT_OBD == LddCbDTC->ddDtcFormat)
    {
      /* @Trace: Dem_SUD_API_13153 */
      LblIsFormatOBD = DEM_TRUE;
    }
  }
  #if (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO)
  LddResult =
      Dem_GetSizeOfOBDFreezeFrameData(event, DEM_TRUE, DEM_ZERO, &LddSize);
  #endif

  if (DEM_FALSE == LblIsFormatOBD)
  {
    /* @Trace: Dem_SUD_API_13154 */
    /* No OBD event */
    LddReVal = (uint8)DEM_DATA_WRONG_DTC;
  }
  else if (E_NOT_OK == LddResult)
  {
    /* @Trace: Dem_SUD_API_13155 */
    /* No obd freeze frame configured */
    LddReVal = (uint8)DEM_DATA_WRONG_DTC;
  }
  else if (DEM_ZERO == LddSize)
  {
    /* @Trace: Dem_SUD_API_13156 */
    /* No obd freeze frame configured */
    LddReVal = (uint8)DEM_DATA_WRONG_DTC;
  }
  else if (*BufSize < LddSize)
  {
    /* @Trace: Dem_SUD_API_13157 */
    /* Target buffer size is too small */
    LddReVal = (uint8)DEM_DATA_WRONG_BUFFERSIZE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_13158 */
    if (NULL_PTR != LddCbDTC)
    {
      #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
      /* Trace: DEM_19792_04_02 */
      if (Dem_ObdMemoryId != DEM_NO_EVMEM_ENTRY)
      {
        LddEntry = &Dem_PrimaryEventMemory[Dem_ObdMemoryId];
      }
      #else
      LddEntry =
          Dem_EvMem_FindEntry(Dem_GetFirstEventOfDTC(LddCbDTC), DTCOrigin);
      #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/

      /* @Trace: Dem_SUD_API_13148 */
      if (NULL_PTR != LddEntry)
      {
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /* @Trace: Dem_SUD_API_13146 */
        LddResult = Dem_GetReadDataOfPID(LddEntry, DestBuffer,
            DEM_TRUE, DEM_ZERO, /* ignore pid number */
            DEM_TRUE, DEM_ZERO);/* ignore data index */
        #else
        /* @Trace: Dem_SUD_API_13147 */
        DEM_UNUSED_PTR(DestBuffer);
        #endif
      }
    }
    if (E_NOT_OK == LddResult)
    {
      /* @Trace: Dem_SUD_API_13150 */
      *BufSize = DEM_ZERO;
    }
    else
    {
      /* @Trace: Dem_SUD_API_13149 */
      *BufSize = LddSize;
    }
  }

  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  DEM_UNUSED(DTCOrigin);
  #endif

  return LddReVal;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_ReadDataOfFreezeFrame                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Reads the freeze frame data from an event           **
 **                       memory entry                                        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EvData, DTCOrigin, RecordNumber, DataIdentifier     **
 **                       HeaderType, BufSize                                 **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : DestBuffer                                          **
 **                                                                           **
 ** Return parameter    : Dem_ReturnReadEventDataType                         **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: SRS_Diag_04024 SRS_Diag_04127
 */
/* @Trace: Dem_SUD_MACRO_132 */
/* polyspace +3 CODE-METRICS:FXLN CODE-METRICS:PATH[Not a defect:Low] "Not a defect" */
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
FUNC(Dem_ReturnReadEventDataType, DEM_CODE)
Dem_ReadDataOfFreezeFrame(
  Dem_EventRelatedDataPCType  EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_RecordNumberType RecordNumber,
  Dem_DataIdentifierType DataIdentifier,
  Dem_FFBufferFormatType HeaderType,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Dem_ReturnReadEventDataType LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;

  Dem_NumOfRecordNumberType LddIRecord = DEM_ZERO;
  Dem_NumOfRecordNumberType LddNumOfStoredRecords = DEM_ZERO;

  P2VAR(uint8, AUTOMATIC, DEM_VAR)   LpDest = DestBuffer;
  P2CONST(uint8, AUTOMATIC, DEM_VAR) LpSrc  = NULL_PTR;
  P2CONST(uint8, AUTOMATIC, DEM_VAR) LpBase = NULL_PTR;

  if ((DEM_NO_EVENT != EvData->EventIdRef) &&
      (EvData->EventIdRef <= DEM_NUMBER_OF_EVENTS) &&
      (EvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS) )
  {    
    /* index shall be checked by caller */
    Dem_FreezeFrameClassPCType LddFFDataClass =
        &Dem_FreezeFrameClass[EvData->FFClassPos];
    Dem_SizeOfFreezeFrameClassType LddFFClassSize =
        Dem_GetSizeOfFreezeFrameData(LddFFDataClass, HeaderType);
    Dem_SizeOfFreezeFrameClassType LddBufSizeForDst =
        (NULL_PTR != BufSize) ? *BufSize : LddFFClassSize;

    if (DEM_ZERO == LddFFClassSize)
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition evaluates to true or false according to configuration */
    {
      /* @Trace: Dem_SUD_API_13170 */
      DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
      LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    }    
    else if (LddBufSizeForDst < LddFFClassSize)
    {
      /* @Trace: Dem_SUD_API_13177 */
      LddRetVal = DEM_GET_READEVDATA_WRONG_BUFFERSIZE;
    }
    else if (DEM_RDFF_RECENT_FFRECNUM == RecordNumber)
    {
      /* @Trace: Dem_SUD_API_13178 */
      LddRetVal = DEM_GET_READEVDATA_OK;
    }
    else if (E_OK == Dem_FFRecordNumBelongToFFClass(
                       EvData,
                       RecordNumber,
                       EvData->MaxNumOfFreezeFrameRecords,
                       &LddIRecord))
    {
      /* @Trace: Dem_SUD_API_13179 */
      LddRetVal = DEM_GET_READEVDATA_OK;
    }
    else
    {
      /* @LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
    }
    /* @Trace: Dem_SUD_API_13180 */
    if (DEM_GET_READEVDATA_OK == LddRetVal)
    {
      Dem_EventMemoryEntryCPType LddMemEntry =
          Dem_EvMem_FindEntry(EvData->EventIdRef, DTCOrigin);
      
      LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
      if (NULL_PTR != LddMemEntry)
      {
        uint16 LusMaxDID =
            LddFFDataClass->PointToDidMap +
            LddFFDataClass->NumOfDidClass;
        /* @LddNumOfStoredRecords shall be greater than 0 */
        LddNumOfStoredRecords = LddMemEntry->IndexOfFFRecords;
        Dem_EventParameterPCType LddEvent =
            &Dem_Event[EvData->EventIdRef - DEM_ONE];
        /* read recent freeze frame record number , but not specific record
         * number */
        /* @Trace: SWS_Dem_00479
         * The function Dem_GetEventFreezeFrameDataEx shall report the data of
         * the DID (defined by parameter DataId) in the requested freeze frame
         * record (defined by parameter RecordNumber, except RecordNumber equal
         * 0xFF) of the requested diagnostic event (EventId). If the
         * RecordNumber is equal to 0xFF and parameter
         * DemTypeOfFreezeFrameRecordNumeration is set to
         * DEM_FF_RECNUM_CALCULATED (refer to DemPrimaryMemory or
         * DemUserDefinedMemory) the most recent record shall be used,
         * otherwise E_NOT_OK shall be returned.
         */
        /* @Trace: Dem_SUD_API_13182 */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
        if (DEM_RDFF_RECENT_FFRECNUM == RecordNumber)
        {
          /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
          if (((DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
                  LddEvent->aaEventDestination) &&
               (DEM_FF_RECNUM_CALCULATED ==
                  Dem_GaaDemPrimaryMemory[LddEvent->ucEventMemDstIdx].
                    usDemTypeOfFreezeFrameRecordNumeration))
              #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
              || ((DEM_DTCORGIN_USER_DEFINED_IS_VALID(
                     LddEvent->aaEventDestination)) &&
               (DEM_FF_RECNUM_CALCULATED ==
                   Dem_GaaDemUserDefinedMemory
                     [LddEvent->ucEventMemDstIdx].
                       usDemTypeOfFreezeFrameRecordNumeration))
              #endif
             )
          {
            /* @Trace: Dem_SUD_API_13160 */
            /* get a buffer index that record number is stored */
            LddIRecord = LddNumOfStoredRecords - DEM_ONE;
          }
          else
          {
            /* @Trace: Dem_SUD_API_13183 */
            LddIRecord = LddNumOfStoredRecords;
          }
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */

        #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
        /* When $F0 Record is not exist yet, ($F0 Configuration is Mandatory) 
          $00 Record have to Response instead of $F0 */
        /* 1979-2 Needed To Recnum $F0 Response */
        if ((RecordNumber == 0xF0u) &&
            (LddIRecord >= LddNumOfStoredRecords))
        {
          (void) Dem_FFRecordNumBelongToFFClass(
              EvData,
              DEM_ZERO,
              EvData->MaxNumOfFreezeFrameRecords,
              &LddIRecord);
        }
        #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

        if (LddNumOfStoredRecords > EvData->MaxNumOfFreezeFrameRecords)
        {
          /* @Trace: Dem_SUD_API_13161 */
          DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
          /* @LddRetVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
        }
        /* LddIRecord : index from zero */
        else if (LddIRecord >= LddNumOfStoredRecords)
        {
          /* @Trace: Dem_SUD_API_13162 */
          LddRetVal = DEM_GET_READEVDATA_NOT_STORED;
        }
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition always evaluates to true. Avoid the runtime error of
         * the polyspace */
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        else if ((DEM_ZERO != LusMaxDID) &&
                 (LusMaxDID <= Dem_Max_ListOfDidClassIndex)) /* Note : <= */
        {        
          uint16 LusIDID = DEM_ZERO;
          /* @Trace: SWS_Dem_00991
           * The format of the data in the destination buffer (DestBuffer) of
           * the function Dem_GetEventFreezeFrameDataEx is raw hexadecimal
           * values and contains no header-information like RecordNumber or
           * DataId. The size of the buffer equals to the configuration settings
           * of all respective data elements.
           */
          /*  |Record Number(or N/A)| Num of DIDs | 1st DID | Data #1|...
           *  | Nth DID | Data #n |
           *
           *  Record Number : Record Number of Freeze Frame
           *  Num of DIDs : Number of all the DID.
           *  Nth DID : Size of the Nth DID */        
          LpBase = LddMemEntry->data;
          Dem_SizeOfFreezeFrameClassType LddSize =
              (LddIRecord) * (LddFFDataClass->size);
          if (DEM_SIZE_OF_EVENT_DATA > LddSize)
          {
            LpSrc = &LpBase[LddIRecord * LddFFDataClass->size];
            if (HeaderType == DEM_FFFORMAT_TYPE_HDR_REC)
            {
              /* @Trace: Dem_SUD_API_13165 */
              /* | Record Number | Number Of DID | ... */
              LpDest[DEM_ZERO] = RecordNumber;
              LpDest[DEM_ONE] = LddFFDataClass->NumOfDidClass;
              LpDest = &LpDest[DEM_TWO];
            }
            else if (HeaderType == DEM_FFFORMAT_TYPE_HDR_DID)
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * If-condition evaluates to true or false according to
             * configuration */
            {
              /* | Number Of DID | ... */
              /* @Trace: Dem_SUD_API_13166 */
              LpDest[DEM_ZERO] = LddFFDataClass->NumOfDidClass;
              LpDest = &LpDest[DEM_ONE];
            }
            else /* @if (HeaderType == DEM_FFFORMAT_TYPE_RAW) */
            {
              /* @Trace: Dem_SUD_API_13167 */
              /* | ... */        
              /* nothing to do */        
            }
        
            for (LusIDID = LddFFDataClass->PointToDidMap;
                 LusIDID < LusMaxDID ;
                 LusIDID++)
            {
              Dem_DidClassCPCType LddDID =
                  &Dem_DidClass[Dem_ListOfDidClassIndex[LusIDID]];
              /* @Trace: Dem_SUD_API_13176 */
              if ((LddDID->DataId == DataIdentifier) ||
                  (DEM_DATAID_IGNORED == DataIdentifier))
              {
                Dem_SizeOfDidClassType LddIdx;
                /* @Trace: Dem_SUD_API_13172 */
                if ((HeaderType == DEM_FFFORMAT_TYPE_HDR_REC) ||
                    (HeaderType == DEM_FFFORMAT_TYPE_HDR_DID))
                {
                  /* @Trace: Dem_SUD_API_13173 */
                  LpDest[DEM_ZERO] =
                      (uint8)((LddDID->DataId & DEM_MASK_UPPER_BYTE) >>
                          DEM_EIGHT);
                  LpDest[DEM_ONE] =
                      (uint8) (LddDID->DataId & DEM_MASK_LOWER_BYTE);
                  LpDest = &LpDest[DEM_TWO];
                }        
                /* Copy external data element from event memory entry */
                /* @Trace: Dem_SUD_API_13174 */
                for (LddIdx = DEM_ZERO; LddIdx < LddDID->size; LddIdx++)
                {
                  /* @Trace: Dem_SUD_API_13175 */
                  /* polyspace<MISRA-C:21.1:Not a defect:Justify with
                   * annotations a defect> Rule violation by runtime
                   * error(orange) of PolySpace */
                  LpDest[LddIdx] = LpSrc[LddIdx];
                }              
                LpDest = &LpDest[LddDID->size]; /* For Read all */
              }
              LpSrc = &LpSrc[LddDID->size];
            }  
            /* @Trace: Dem_SUD_API_13168 */
            if (LpDest != DestBuffer)
            {
              /* @Trace: Dem_SUD_API_13169 */
              if (NULL_PTR != BufSize)
              {
               /* @Trace: Dem_SUD_API_13171 */
                *BufSize = LddFFClassSize;
              }
              LddRetVal = DEM_GET_READEVDATA_OK;
            }          
          }
          else
          {
            /* @Trace: Dem_SUD_API_13164 */
            DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
          }
        } 
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        {
          /* @Trace: Dem_SUD_API_13163 */
          /* Nothing to do */
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_13181 */
        LddRetVal = DEM_GET_READEVDATA_NOT_STORED;
      } 
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_13159 */
    LddRetVal = DEM_GET_READEVDATA_WRONG_DTC;
  }
  return LddRetVal;
}

#endif

/*******************************************************************************
 ** Function Name       : Dem_StoreUdsEDClass                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Loads the extended data in the event memory         **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventStatus, EvData, MemEntry                       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: SRS_Diag_04127
 */
#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
/* polyspace:begin<MISRA-C:16.7:Not a defect:Justify with annotations>
 * A pointer parameter in a function prototype should be declared as pointer to
 * const if the pointer is not used to modify the addressed object. */
FUNC(boolean, DEM_CODE)
Dem_StoreUdsEDClass(
  Dem_EventStatusType EventStatus,
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: SWS_Dem_00468
   * If an event is stored or updated in the event memory, the Dem module shall
   * store the collected extended data into the event memory entry.
   */
  /* @Trace: Dem_SUD_API_13185 */
  /* @Trace: Dem_SUD_MACRO_093 */
  if ((NULL_PTR != MemEntry) &&
      (EvData->EDClassPos < DEM_NUM_OF_EXTENDEDDATACLASS))
  {
	  /* @Trace: Dem_SUD_API_13184 */
    uint32 LulBufSize = DEM_ZERO;
    Dem_ExtendedDataClassPCType LddEdDataClass =
        &Dem_ExtendedDataClass[EvData->EDClassPos];
    /* Gets ptr of buffer to save the event data(FF+EXT) of an event */
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst =
        Dem_EvMem_GetEDBuffer(EvData, MemEntry, &LulBufSize);

    LblDirty = Dem_CaptureEDClass(
        EventStatus,
        EvData->EventIdRef,
        LddEdDataClass, LpDst,
        LulBufSize,
        MemEntry->EventOccurrenceCounter);
  }
  return LblDirty;
}
/* polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations>
 * A pointer parameter in a function prototype should be declared as pointer to
 * const if the pointer is not used to modify the addressed object. */
#endif

/*******************************************************************************
 ** Function Name       : Dem_StoreUdsFFClass                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Loads the freeze frame data in the event memory     **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventStatus, EvData, MemEntry, EnvDataCapture       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04127
 */
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
FUNC(boolean, DEM_CODE)
Dem_StoreUdsFFClass(
    Dem_EventStatusType EventStatus,
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry,
    uint8 EnvDataCapture)
{
  boolean LblDirty = DEM_FALSE;

  if (
   (NULL_PTR != MemEntry) && 
   (NULL_PTR != EvData)  && 
   (EvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS) &&
   (EvData->FFRecordClassIndex < DEM_NUM_OF_FRREZEFRAMERECORDCLASS) &&
   ((EvData->EventIdRef <= DEM_NUMBER_OF_EVENTS) &&
    (EvData->EventIdRef != DEM_NO_EVENT)))
  {
    /* @Trace: Dem_SUD_API_13186 */
    P2CONST(Dem_FreezeFrameClassType, AUTOMATIC, DEM_VAR) LddFFDataClass =
        &Dem_FreezeFrameClass[EvData->FFClassPos];
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
    uint32 LulBufSize = LddFFDataClass->size;
    /* @Trace: SWS_Dem_00337
     * If DemTypeOfFreezeFrameRecordNumeration is set to
     * DEM_FF_RECNUM_CALCULATED (refer to DemPrimaryMemory or
     * DemUserDefinedMemory), the Dem shall store DemMaxNumberFreezeFrameRecords
     * number of freeze frames for this DTC.
     */
    /* @Trace: SWS_Dem_00581
     * If the Dem module uses calculated record numbers, the Dem module shall
     * numerate the event-specific freeze frame records consecutively starting
     * by 1, based on their chronological order.
     */
    LpDst = Dem_EvMem_GetFFBufferForWriting(
        EvData, MemEntry, &LulBufSize, EventStatus);
    if (NULL_PTR != LpDst)
    {
      /* @Trace: SWS_Dem_00191
       * If no pre-stored freeze frame is available, the Dem module shall
       * behave according to chapter 7.7.7.1 Storage of freeze frame data.
       */
      /* @Trace: Dem_SUD_MACRO_029 */
      #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
      P2VAR(uint8, AUTOMATIC, DEM_VAR) LpSrc = NULL_PTR;
      /* Prestored freeze frame data */
      /* @Trace: Dem_SUD_API_13188 */
      if (DEM_TRUE == EvData->FFPreStorageSupported)
      {
        /* @Trace: SWS_Dem_00464
         * If a pre-stored freeze frame is available, the Dem module shall
         * use the data of the pre-stored freeze frame instead of the current
         * data at the point in time when the event related date is captured
         * (refer to [SWS_Dem_00461].
         */
        /* @Trace: Dem_SUD_API_13189 */
        LpSrc = Dem_GetBufferOfPrestoredFF(EvData->EventIdRef, NULL_PTR);
      }
      /* found prestored freeze frame in the buffer. */
      if (NULL_PTR != LpSrc)
      {
        Dem_SizeOfFreezeFrameClassType LddIdx;
        /* @Trace: Dem_SUD_API_13192 */
        for (LddIdx = DEM_ZERO; LddIdx < LddFFDataClass->size; LddIdx++)
        {      
          /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a
           * defect> Rule violation */
          /* @Trace: Dem_SUD_API_13193 */
          if ( (DEM_FALSE == LblDirty) && (LpDst[LddIdx] != LpSrc[LddIdx]) )
          {
           /* @Trace: Dem_SUD_API_13194 */
            LblDirty = DEM_TRUE;
          } 
          /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations a
           * defect> Rule violation */
          LpDst[LddIdx] = LpSrc[LddIdx];
        }
      }
      else
      #endif
      if ((DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING == EnvDataCapture)
          #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_OFF)
          || (DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING == EnvDataCapture)
          #endif
         )
      {
        /* @Trace: Dem_SUD_API_13190 */
        LblDirty |= Dem_CaptureFFClass(
            EvData->EventIdRef, LddFFDataClass, LpDst, LulBufSize);
      }
      else
      {
        /* @Trace: Dem_SUD_API_13191 */
        /* Nothing to do */
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_13187 */
      /* Det Error */
    }
  }
  
  return LblDirty;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_StoreWWHFFClass                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Loads the WWH freeze frame data in the event memory **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EvData, MemEntry                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE) Dem_StoreWWHFFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_13196 */
  if ((NULL_PTR != MemEntry) && (NULL_PTR != EvData)
      && (EvData->WWHOBDFFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS))
  {
   /* @Trace: Dem_SUD_API_13195 */
    P2CONST(Dem_FreezeFrameClassType, AUTOMATIC, DEM_VAR) LddFFDataClass =
        &Dem_FreezeFrameClass[EvData->WWHOBDFFClassPos];
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
    uint32 LulBufSize = LddFFDataClass->size;
    LpDst = Dem_EvMem_GetWWHFFBufferForWriting(EvData, MemEntry, &LulBufSize);
    /* @Trace: Dem_SUD_API_13197 */
    if (NULL_PTR != LpDst)
    {
      /* @Trace: Dem_SUD_API_13198 */
      LblDirty |= Dem_CaptureFFClass(
          EvData->EventIdRef, LddFFDataClass, LpDst, LulBufSize);
    }
  }
  return LblDirty;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_StoreJ1939FFClass                               **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Loads the j1939 freeze frame data in the event      **
 **                       memory                                              **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EvData, MemEntry                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO))
FUNC(boolean, DEM_CODE)
Dem_StoreJ1939FFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_13199 */
  if ((NULL_PTR != MemEntry) &&
      (EvData->J1939FFClassPos < Dem_Num_Of_J1939FreezeFrameClass))
  {
	/* @Trace: Dem_SUD_API_13200 */
    uint32 LulBufSize = DEM_ZERO;
    P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST)
    LddJ1939ffDataClass = &Dem_J1939FreezeFrameClass[EvData->J1939FFClassPos];
    /* Gets ptr of buffer to save the event data(FF+EXT) of an event */
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst =
        Dem_EvMem_GetJ1939FFBuffer(EvData, MemEntry, &LulBufSize, 0);
    
    LblDirty = Dem_CaptureJ1939FFClass(
        EvData->EventIdRef, LddJ1939ffDataClass, LpDst, LulBufSize);
  }  

  return LblDirty;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_StoreJ1939EXFFClass                             **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Loads the j1939 expanded freeze frame data in the   **
 **                       event memory                                        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EvData, MemEntry                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: Dem_SUD_MACRO_121 */
#if ((DEM_J1939_SUPPORT == STD_ON) && \
     (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > DEM_ZERO))
FUNC(boolean, DEM_CODE)
Dem_StoreJ1939EXFFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean LblDirty = DEM_FALSE;
  /* @Trace: Dem_SUD_API_13201 */
  if ((NULL_PTR != MemEntry) &&
      (EvData->J1939EXFFClassPos < Dem_Num_Of_J1939FreezeFrameClass))
  {
    /* @Trace: Dem_SUD_API_13202 */
    uint32 LulBufSize = DEM_ZERO;
    P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST)
    LddJ1939ExFFDataClass =
        &Dem_J1939FreezeFrameClass[EvData->J1939EXFFClassPos];
    /* Gets ptr of buffer to save the event data(FF+EXT) of an event */
    P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst =
        Dem_EvMem_GetJ1939FFBuffer(EvData, MemEntry, &LulBufSize, 1);
    
    LblDirty =
        Dem_CaptureJ1939FFClass(
            EvData->EventIdRef, LddJ1939ExFFDataClass, LpDst, LulBufSize);
  }  

  return LblDirty;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_GetOBDFFBufferForWriting                  **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : This function is used to get the extended data      **
 **                       or freeze frame data internally from Dem or from    **
 **                       some external function                              **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EvData, MemEntry                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : BufSize                                             **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO))
FUNC_P2VAR(uint8, DEM_VAR, DEM_CODE) Dem_EvMem_GetOBDFFBufferForWriting(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry,
  P2VAR(uint32, AUTOMATIC, DEM_VAR) BufSize)
{
  const Dem_RecordNumberType  LddMaxLimit = EvData->MaxNumOfFreezeFrameRecords;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
  uint8 LucResult = E_NOT_OK;
  /* Tip, the range of Record Number is 1~254(0xFE). Record Number 0 is value
   * for OBD Freeze Frame */
  /* @Trace: Dem_SUD_API_13203 */
  if (NULL_PTR != MemEntry)
  {
    if (DEM_NO_EVMEM_IDX !=
          Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx)
    {
      if (DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
            Dem_Event[EvData->EventIdRef - DEM_ONE].aaEventDestination)
      {
        #if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        if (DEM_FF_RECNUM_CALCULATED ==
                Dem_GaaDemPrimaryMemory
                  [Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx].
                    usDemTypeOfFreezeFrameRecordNumeration)
        {
          /* @Trace: Dem_SUD_API_13218 */
          LucResult = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_13219 */
          /* Check whether configure FFRecordClass */
          uint16 LusMaxFFR =
              EvData->FFRecordClassIndex +
              (uint16)EvData->MaxNumOfFreezeFrameRecords;
          if (LusMaxFFR > DEM_ZERO)
          {
            uint16 LusFFRecClassIdx =
                EvData->FFRecordClassIndex + MemEntry->IndexOfFFRecords;
            /* @Trace: Dem_SUD_API_13220 */
            if (MemEntry->IndexOfFFRecords >=
                  EvData->MaxNumOfFreezeFrameRecords)
            {
            /* @Trace: Dem_SUD_API_13204 */
              LusFFRecClassIdx -= DEM_ONE;
            }
            /* @Trace: Dem_SUD_API_13206 */
            /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
            if ((DEM_UPDATE_RECORD_YES ==
                   Dem_FreezeFrameRecordClass[LusFFRecClassIdx].RecordUpdate) ||
                (DEM_ONE == MemEntry->EventOccurrenceCounter))
            {
              /* @Trace: Dem_SUD_API_13205 */
              LucResult = E_OK;
            }
          }
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        #endif
      }
      else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(
                 Dem_Event[EvData->EventIdRef - DEM_ONE].aaEventDestination))
      {
        #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
        if (DEM_FF_RECNUM_CALCULATED ==
                Dem_GaaDemUserDefinedMemory
                  [Dem_Event[EvData->EventIdRef - DEM_ONE].ucEventMemDstIdx].
                    usDemTypeOfFreezeFrameRecordNumeration)
        {
          /* @Trace: Dem_SUD_API_13217 */
          LucResult = E_OK;
        }
        else
        {
          uint16 LusMaxFFR =
              EvData->FFRecordClassIndex +
              (uint16)EvData->MaxNumOfFreezeFrameRecords;
          /* @Trace: Dem_SUD_API_13214 */
          if ((LusMaxFFR > DEM_ZERO) &&
              ((EvData->FFRecordClassIndex + MemEntry->IndexOfFFRecords)
                  < DEM_NUM_OF_FRREZEFRAMERECORDCLASS))
          {
            /* @Trace: Dem_SUD_API_13215 */
            /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
            if ((DEM_UPDATE_RECORD_YES ==
                   Dem_FreezeFrameRecordClass
                     [EvData->FFRecordClassIndex + MemEntry->IndexOfFFRecords].
                        RecordUpdate) ||
                (DEM_ONE == MemEntry->EventOccurrenceCounter))
            {
              /* @Trace: Dem_SUD_API_13216 */
              LucResult = E_OK;
            }
          }
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        #endif
      }
      else
      {
        /* @Trace: Dem_SUD_API_13213 */
        /* Nothing to do */
      }
    }
    /* @Trace: Dem_SUD_API_13207 */
    if (E_OK == LucResult)
    {
      /* Trace: DEM_OBD_02_01 */
      /* @Trace: Dem_SUD_API_13210 */
      Dem_NumOfRecordNumberType LddIFFRecord = MemEntry->IndexOfFFRecords;
      if ((DEM_ZERO != LddMaxLimit) && (LddIFFRecord <= LddMaxLimit))
      {
        /* Only Use Record 0 */
        if (LddIFFRecord == 0u)
        {
          /* @Trace: Dem_SUD_API_13210 */
          /* Increment the index of ListOfRecordNumbers for Next Step */
          MemEntry->IndexOfFFRecords++;
          
          /* LddRecordIndex starts from zero */
          /* @Trace: Dem_SUD_API_13211 */
		  /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "LddIFFRecord is changed when API is used" */
          if (DEM_SIZE_OF_EVENT_DATA > (LddIFFRecord * (*BufSize)))
          {
            /* @Trace: Dem_SUD_API_13212 */
            LpDst = &MemEntry->data[LddIFFRecord * (*BufSize)];
          }
		  /* polyspace-end MISRA-C3:14.3 [Justified:Low] "LddIFFRecord is changed when API is used" */
          *BufSize  = DEM_SIZE_OF_EVENT_DATA - (LddIFFRecord * (*BufSize));          
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_13208 */
        /* LddMaxLimit never be 0, if LddMaxLimit is 0, FFClass of EvData will
         * be generated as NULL_PTR . */
        DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
      }
    }
  }

  return LpDst;
}

/*******************************************************************************
 ** Function Name       : Dem_StoreObdFFClass                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Loads the OBD freeze frame data in the event memory **
 **                                                                           **
 ** Sync/Async          : Synchronous/Asynchronous                            **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EvData, MemEntry                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
FUNC(boolean, DEM_CODE)
Dem_StoreObdFFClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry)
{
  /* @Std_ReturnType LddResult = E_NOT_OK;*/
  /* @boolean found = DEM_FALSE;*/
  boolean LblDirty = DEM_FALSE;
  /* @Dem_NumOfRecordNumberType LddRecordIndex = DEM_ZERO;*/

  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpSrc = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) LpDst = NULL_PTR;
  /* @P2VAR(uint8, AUTOMATIC, DEM_VAR) LpBase = NULL_PTR;*/

  /* Get buffer of event memory for a specific event */
  /* @LpBase = entry->data;*/

  /* Get buffer of event memory entry */
  /* @Trace: Dem_SUD_API_13221 */
  if (EvData->OBDClassPos != NULL_PTR)
  {
    uint32 LulBufSize = EvData->OBDClassPos->size;
    LpDst = Dem_EvMem_GetOBDFFBufferForWriting(EvData,
        MemEntry, &LulBufSize);
    /* @Trace: Dem_SUD_API_13226 */
    if (NULL_PTR != LpDst)
    {
      if (NULL_PTR != EvData->CallbackEventDataChanged)
      {
        /* Use temporary buffer to check the difference between Old and New
         * data. */
        /* @Trace: Dem_SUD_API_13228 */
        if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > Dem_ObdMemoryId)
        {
          /* @Trace: Dem_SUD_API_13229 */
          Dem_EventMemoryEntryPtrType LddMemEntry =
              &Dem_PrimaryEventMemory[Dem_ObdMemoryId];
          LpSrc = LddMemEntry->data;
        }
      }
      else
      {
       /* @Trace: Dem_SUD_API_13227 */
        LpSrc = LpDst;
      }

      (void)Dem_CaptureOBDFFClass(EvData->OBDClassPos, LpSrc);
      /* @Trace: Dem_SUD_API_13230 */
      if (NULL_PTR != LpSrc)
      {
        if (LpSrc != LpDst)
        {
          /* @Dem_NumOfPidDataElementType DataIndex = DEM_ZERO;*/
          Dem_NumOfPidClassType LddIdx = DEM_ZERO;
          const Dem_NumOfPidClassType LddNumOfPid =
              EvData->OBDClassPos->NumOfPidClass;
          /* @Trace: Dem_SUD_API_13232 */
          if (NULL_PTR != EvData->OBDClassPos->PidClass)
          {
            CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) LddPID =
                EvData->OBDClassPos->PidClass;
            /* @Trace: Dem_SUD_API_13233 */
            for (LddIdx = DEM_ZERO; LddIdx < LddNumOfPid; LddIdx++)
            {
              Dem_NumOfPidDataElementType LddJ = DEM_ZERO;
              const Dem_NumOfPidDataElementType LddNumOfPidData =
                  LddPID[LddIdx].NumOfPidDataElements;
              /* @Trace: Dem_SUD_API_13222 */
              for (LddJ = DEM_ZERO; LddJ < LddNumOfPidData; LddJ++)
              {
                CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
                LddListOfDataElementPtr =
                    &Dem_DataElementClass[Dem_ListOfDataElementClassIndex[LddJ]];

                uint8 LucSize = LddListOfDataElementPtr->size;

                Dem_SizeOfFreezeFrameClassType LddIndex;
                /* @Trace: Dem_SUD_API_13223 */
                for (LddIndex = DEM_ZERO; LddIndex < LucSize; LddIndex++)
                {
                  /* @Trace: Dem_SUD_API_13224 */
                  if (DEM_FALSE == LblDirty)
                  {
                    {
                      /* @Trace: Dem_SUD_API_13225 */
                      LblDirty = DEM_TRUE;
                    }
                  }
                  LpDst[LddIndex] = LpSrc[LddIndex];
                }
                LpDst = &LpDst[LucSize];
                LpSrc = &LpSrc[LucSize];
              }
            }
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_13231 */
          /* FF is already stored in the FFBuffer */
        }
      }
    }
  }
  return LblDirty;
}


#endif

/*******************************************************************************
 ** Function Name       : Dem_GetSizeOfFreezeFrameData                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : The API shall be used to get the size of freeze     **
 **                       frame                                               **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : FFClass, FFBufferType                               **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Dem_SizeOfFreezeFrameClassType                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
FUNC(Dem_SizeOfFreezeFrameClassType, DEM_CODE)
Dem_GetSizeOfFreezeFrameData(
  Dem_FreezeFrameClassPCType FFClass,
  const Dem_FFBufferFormatType FFBufferType)
{
  Dem_SizeOfFreezeFrameClassType LddBufSize = DEM_ZERO;

  /* variable range for calculation
   * LddFFDataClass->size : 0 ~ 65535
   * LddFFDataClass->NumOfDidClass : 0 ~ 255
   * sizeof(Dem_DataIdentifierType) : 2
   * LddFFDataClass->NumOfDidClass * sizeof(Dem_DataIdentifierType) : 0~500 <-
   * need casting
   * sizeof(Dem_NumOfDidClassType) : 1
   */
  /* |NumofDIDs|1st DID|Data#1|*/
  if (DEM_FFFORMAT_TYPE_HDR_DID == FFBufferType)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition evaluates to true or false according to configuration */
  {
    /* @Trace: Dem_SUD_API_13234 */
    LddBufSize =
      FFClass->size + 
      ((Dem_SizeOfFreezeFrameClassType)FFClass->NumOfDidClass *
          (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_DataIdentifierType)) +
      (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_NumOfDidClassType);
  }
  /* |RecNum|NumofDIDs|1st DID|Data#1|*/
  else if (DEM_FFFORMAT_TYPE_HDR_REC == FFBufferType)
  {
    /* @Trace: Dem_SUD_API_13235 */
    LddBufSize =
      FFClass->size + 
      ((Dem_SizeOfFreezeFrameClassType)FFClass->NumOfDidClass *
          (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_DataIdentifierType)) +
      (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_NumOfDidClassType) + 
      (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_RecordNumberType);
  }
  /* @else if (DEM_FFFORMAT_TYPE_RAW == type) */
  else
  {
    /* @Trace: Dem_SUD_API_13236 */
    LddBufSize = FFClass->size;
  }

  return LddBufSize;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetSizeOfExtendedData                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Gets the size of extended data                      **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EDClass, ExtendedDataNumber                         **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : NumOfMatchedEDR                                     **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
FUNC(Dem_SizeOfExtendedDataClassType, DEM_CODE)
Dem_GetSizeOfExtendedData(
  Dem_ExtendedDataClassPCType EDClass,
  const Dem_ExtendedDataNumberType ExtendedDataNumber,
  P2VAR(Dem_NumOfExtendedDataRecordClassType, AUTOMATIC, DEM_VAR) NumOfMatchedEDR
  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  , Dem_EventIdType EventId
  #endif
  )
{
  Dem_SizeOfExtendedDataClassType LddBufSize = DEM_ZERO;

  /* [1] All Extended Data Record Number */
  if (DEM_MAX_EXTENDED_RECORD_NUMBER == ExtendedDataNumber)
  {
    LddBufSize = EDClass->size;
    /* @Trace: Dem_SUD_API_13240 */
    if (NULL_PTR != NumOfMatchedEDR)
    {
      *NumOfMatchedEDR = EDClass->NumOfEDRecordClass;
    }
  } 
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  else if (DEM_EXTENDED_DATA_NUMBER_OBD == ExtendedDataNumber)
  {
    /* @Trace: Dem_SUD_API_13237 */
    /* @Trace: SWS_Dem_00076
     * Note: If the record number value 0xFE is requested, the Dem considers
     * the size of all OBD stored extended data records in the range of 0x90 to
     * 0xEF */
    Dem_ExtendedDataNumberType from =
        (Dem_ExtendedDataNumberType)DEM_MIN_VALID_OBD_EXTENDED_RECORD_NUMBER;
    Dem_ExtendedDataNumberType to =
        (Dem_ExtendedDataNumberType)DEM_MAX_VALID_OBD_EXTENDED_RECORD_NUMBER;

    Dem_NumOfExtendedDataRecordClassType LddIEDR;
    Dem_NumOfExtendedDataRecordClassType LddMaxEDR;
    
    LddMaxEDR = EDClass->PointToEDRecordMap + EDClass->NumOfEDRecordClass;
    /* @Trace: Dem_SUD_API_13245 */
    /* @Trace: Dem_SUD_MACRO_069 */
    if (LddMaxEDR <= Dem_Max_ListOfEDRecordClassIndex)
    {       
      /* @Trace: Dem_SUD_API_13246 */
      for (LddIEDR = EDClass->PointToEDRecordMap;
           LddIEDR < LddMaxEDR;
           LddIEDR++)
      {
        CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST)
          LddEDRecord =
              &Dem_ExtendedDataRecordClass
                [Dem_ListOfEDRecordClassIndex[LddIEDR]];
        /* @Trace: Dem_SUD_API_13247 */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
        if  ((LddEDRecord->ExtendedDataRecordNumber >= from ) &&
            (LddEDRecord->ExtendedDataRecordNumber <= to ))
        {
          LddBufSize += LddEDRecord->size;
          /* @Trace: Dem_SUD_API_13238 */
          if (NULL_PTR != NumOfMatchedEDR)
          {
            /* @Trace: Dem_SUD_API_13239 */
            *NumOfMatchedEDR += DEM_ONE;
          }           
        }  
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
      }
    }
  }
  #endif
  /* [2] A specific Extended Data Record Number */
  else
  {     
    Dem_NumOfExtendedDataRecordClassType LddIEDR;
    Dem_NumOfExtendedDataRecordClassType LddMaxEDR;
    
    LddMaxEDR = EDClass->PointToEDRecordMap + EDClass->NumOfEDRecordClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition evaluates to true or false according to configuration */
    /* @Trace: Dem_SUD_API_13241 */
    if (LddMaxEDR <= Dem_Max_ListOfEDRecordClassIndex)
    {       
      /* @Trace: Dem_SUD_API_13242 */
      for (LddIEDR = EDClass->PointToEDRecordMap;
           LddIEDR < LddMaxEDR;
           LddIEDR++)
      {
        CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST)
        LddEDRecord =
            &Dem_ExtendedDataRecordClass[Dem_ListOfEDRecordClassIndex[LddIEDR]];
        /* @Trace: Dem_SUD_API_13244 */
        if (LddEDRecord->ExtendedDataRecordNumber == ExtendedDataNumber)
        {

          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          if (DEM_EXTENDED_DATA_NUMBER_DTR == ExtendedDataNumber)
          {
              uint16 LucNumberOfDTR = 0;
              uint8 LucDTRIdIndex = 0;
              #if(DEM_NUMBER_OF_DTRS > DEM_ZERO)
              /* This Data is Diagnostic Test Result in 1979-2 */
              for ( LucDTRIdIndex = DEM_ZERO; 
                    LucDTRIdIndex < DEM_NUMBER_OF_DTRS; 
                    LucDTRIdIndex++)
              {
                if (EventId == Dem_GaaDtrInfo[LucDTRIdIndex].usEventId)
                {                 
                  /* SAE J1979-2 ExtendedDataRecord 0x92 DTC Based Test Result */
                  LucNumberOfDTR++;   
                }   
              }
              #endif
              /* type cast to em_SizeOfExtendedDataClassType */
              LddBufSize = ((LucNumberOfDTR * (uint16) DEM_EIGHT) + (uint16)(DEM_ONE));
          }
          else
          #endif
          {        
            LddBufSize = LddEDRecord->size;
          }
          /* @Trace: Dem_SUD_API_13243 */
          if (NULL_PTR != NumOfMatchedEDR)
          {
            *NumOfMatchedEDR = DEM_ONE;
          }          
          break;
        }
      }
    }
  }
  
  return LddBufSize;
}
#endif

/*******************************************************************************
** Function Name        : Dem_StoreEventRelatedData                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used store event related data to memory entries  **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
**                                                                            **
** Input Parameters     : EvData, EvMemEntry, EventStatus, EnvDataCapture     **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04155 SRS_Diag_04160
 */
#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
FUNC(boolean, DEM_CODE) Dem_StoreEventRelatedData(
  P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) EvData,
  Dem_EventMemoryEntryPtrType EvMemEntry,
  Dem_EventStatusType EventStatus,
  uint8 EnvDataCapture)
{
  boolean LblDirty = DEM_FALSE;
  /* Freeze Frame Data */
  #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
  LblDirty |=
      Dem_StoreUdsFFClass(EventStatus, EvData, EvMemEntry, EnvDataCapture);
  #else
  DEM_UNUSED(EnvDataCapture);
  #endif

  /* Extended Data  */
  #if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
  LblDirty |= Dem_StoreUdsEDClass(EventStatus, EvData, EvMemEntry);
  #endif

  /* OBD Freeze Frame Data */
  #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
       (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO))
  /* @Trace: Dem_SUD_API_13248 */
  if ((DEM_NO_EVMEM_ENTRY != Dem_ObdMemoryId) &&
      (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > Dem_ObdMemoryId))
  {
    /* @Trace: Dem_SUD_API_13249 */
    LblDirty |=
        Dem_StoreObdFFClass(EvData, &Dem_PrimaryEventMemory[Dem_ObdMemoryId]);
  }
  #endif

  /* WWH OBD Freeze Frame Data*/
  #if (((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
        (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)))
  /* @Trace: Dem_SUD_API_13250 */
  if (EvData->WWHOBDFFClassPos !=DEM_NO_IDX_U8)
  {
    /* @Trace: Dem_SUD_API_13251 */
    LblDirty |=
        Dem_StoreWWHFFClass(EvData, EvMemEntry);
  }
  #else
  DEM_UNUSED(EnvDataCapture);
  #endif

  /* J1939 Freeze Frame Data */
  #if ((DEM_J1939_SUPPORT == STD_ON) && \
       (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO))
  LblDirty |= Dem_StoreJ1939FFClass(EvData, EvMemEntry);
  #endif

  #if ((DEM_J1939_SUPPORT == STD_ON) && \
       (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > DEM_ZERO))
  LblDirty |= Dem_StoreJ1939EXFFClass(EvData, EvMemEntry);
  #endif

  /* This callback should be called only when the event has the event related
   * data. */
  /* @Trace: Dem_SUD_API_13252 */
  if (DEM_TRUE == LblDirty)
  {    
    /* @Trace: SWS_Dem_00475
     * If "event related data" (extended data or freeze frame data) of an event
     * memory entry is added or updated AND notifications on data changes are
     * configured via DemCallbackEventDataChanged, the Dem shall trigger these
     * configured event-specific notifications as well as the general
     * notification GeneralCallbackEventDataChanged. The datachanged-callbacks
     * shall be triggered in case an event is reported as:
     * + DEM_EVENT_STATUS_PASSED
     * + DEM_EVENT_STATUS_PREPASSED
     * + DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
     */
    /* @Trace: Dem_SUD_API_13253 */
    if ((DEM_EVENT_STATUS_PASSED == EventStatus) ||
        (DEM_EVENT_STATUS_PREPASSED == EventStatus) ||
        (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED == EventStatus))
    {
      /* @Trace: Dem_SUD_API_13254 */
      if (NULL_PTR != EvData->CallbackEventDataChanged)
      {
        /* @Trace: Dem_SUD_API_13255 */
        /* polyspace<RTE:COR:Not a defect:No action planned> Polyspace bug */
        (void)EvData->CallbackEventDataChanged();
      }
      #if (DEM_GENERAL_INTERFACE_SUPPORT == STD_ON)
      (void)Rte_Call_GeneralCBDataEvt_EventDataChanged(EvData->EventIdRef);
      #endif
    }
  }
  /* @Trace: SWS_Dem_00969
   * A pre-stored freeze frame shall be released after it has been stored in
   * the event memory or discarded.
   */
  /* Clear prestored freeze frame buffer */
  #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
  (void)Dem_ClearSinglePrestoredFFbyEventId(EvData->EventIdRef);
  #endif 

  return LblDirty;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetSizeOfOBDFreezeFrameData                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used get the size of OBD FreezeFrame data        **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
**                                                                            **
** Input Parameters     : event, ReportTotalRecord, PidIdentifier             **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : BufSize                                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO))
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfOBDFreezeFrameData(
    Dem_EventParameterCPCType event,
    const boolean ReportTotalRecord,
    const Dem_PidIdentifierType PidIdentifier,
    P2VAR(Dem_SizeOfOBDFreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) LddEvData = NULL_PTR;
  if (event->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
  {
    /* @Trace: Dem_SUD_API_13256 */
    LddEvData = &Dem_EventRelatedData[event->e_PointToData];
  }

  if (NULL_PTR == LddEvData)
  {
    /* @Trace: Dem_SUD_API_13257 */
    LddRetVal = E_NOT_OK;
  }
  else if (NULL_PTR == LddEvData->OBDClassPos)
  {
    /* @Trace: Dem_SUD_API_13258 */
    /* No OBD freeze frame configured of event. */
     LddRetVal = E_NOT_OK;
  }
  else if (DEM_TRUE == ReportTotalRecord)
  {
    /* @Trace: Dem_SUD_API_13259 */
    *BufSize =  LddEvData->OBDClassPos->size;
    LddRetVal = E_OK;
  }
  else
  {
    Dem_NumOfPidClassType LddIdx = DEM_ZERO;
    const Dem_NumOfPidClassType LddNum = LddEvData->OBDClassPos->NumOfPidClass;
    CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) LddPID =
        LddEvData->OBDClassPos->PidClass;
    /* @Trace: Dem_SUD_API_13260 */
    for (LddIdx = DEM_ZERO; LddIdx < LddNum; LddIdx++)
    {
    /* @Trace: Dem_SUD_API_13261 */
      if (PidIdentifier == LddPID[LddIdx].PidIdentifier)
      {
        /* @Trace: Dem_SUD_API_13262 */
        *BufSize = LddPID[LddIdx].size;
        LddRetVal = E_OK;
      }
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetSizeOfJ1939FreezeFrameData                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used get the size of J1939 FreezeFrame data      **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : event,J1939FFType                                   **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : BufSize                                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)  
/* @Trace: Dem_SUD_MACRO_055 */
#if (DEM_NUM_OF_J1939FREEZEFRAMECLASS > DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfJ1939FreezeFrameData(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_SizeOfJ1939FreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize,
  Dem_J1939DcmSetFreezeFrameFilterType J1939FFType)
{
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) LddEvData;
  P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_VAR) LddJ1939FFClass =
      NULL_PTR;
  Dem_NumOfJ1939FreezeFrameClassType LddFFClassPos;
  *BufSize = DEM_ZERO;
  LddEvData = &Dem_EventRelatedData[event->e_PointToData];
   
  if (J1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME)
  {
  /* @Trace: Dem_SUD_API_13263 */
    LddFFClassPos = LddEvData->J1939EXFFClassPos;
  }
  else 
  {
   /* @Trace: Dem_SUD_API_13264 */
    LddFFClassPos = LddEvData->J1939FFClassPos;
  }
  /* @Trace: Dem_SUD_API_13265 */
  if ((DEM_NO_IDX_U16 == LddFFClassPos) ||
      (DEM_NUM_OF_J1939FREEZEFRAMECLASS <= LddFFClassPos))
  {
    /* No J1939 freeze frame configured of event. */
     /*LddRetVal = DEM_NO_SUCH_ELEMENT;*/
  }
  else
  {
    /* @Trace: Dem_SUD_API_13266 */
    LddJ1939FFClass = &Dem_J1939FreezeFrameClass[LddFFClassPos];
    *BufSize =  LddJ1939FFClass->size;
    LddRetVal = E_OK;
  }

  return LddRetVal;
}
#endif
#endif

/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned> Not defect  */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

