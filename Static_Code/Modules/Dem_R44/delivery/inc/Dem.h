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
**  SRC-MODULE: Dem.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of extern declarations of APIs and Service ID       **
**              macros                                                        **
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

#ifndef DEM_H
#define DEM_H

/* 
   polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect
   polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect
   polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> Not a defect 
*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_Types.h"
#include "Dem_PCTypes.h" 
#include "Dem_Cfg.h"     /* Dem_PBcfg.h [SWS_Dem_00151] */
#include "Dem_Config.h"
#if (DEM_J1939_SUPPORT == STD_ON)
#include "Dem_J1939Dcm.h" /* J1939 */
#endif

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#include "Dem_Obd.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define DEM_UNUSED(x)                 ((void)x)
#define DEM_UNUSED_PTR(x)             ((void)x)

/* Instance ID */
#define DEM_INSTANCE_ID                                       ((uint8)0x00)
/* Service ID for Dem_GetVersionInfo*/
#define DEM_GETVERSIONINFO_SID                                ((uint8)0x00)
/* Service ID for Dem_Init */
#define DEM_INIT_SID                                          ((uint8)0x02)
/* Service ID for Dem_Shutdown */
#define DEM_SHUTDOWN_SID                                      ((uint8)0x03)
/* Service ID for Dem_SetEventStatus  */
#define DEM_SETEVENTSTATUS_SID                                ((uint8)0x04)
/* Service ID for Dem_ResetEventStatus */
#define DEM_RESETEVENTSTATUS_SID                              ((uint8)0x05)
/* Service ID for Dem_PrestoreFreezeFrame */
#define DEM_PRESTOREFREEZEFRAME_SID                           ((uint8)0x06)
/* Service ID for Dem_ClearPrestoredFreezeFrame */
#define DEM_CLEARPRESTOREDFREEZEFRAME_SID                     ((uint8)0x07)
/* Service ID for Dem_RestartOperationCycle */
#define DEM_RESTARTOPERATIONCYCLE_SID                         ((uint8)0x08)

/* Service ID for Dem_ResetEventDebounceStatus */
#define DEM_RESETEVENTDEBOUNCESTATUS_SID                      ((uint8)0x09)

/* Service ID for Dem_SetCycleQualified */
#define DEM_SETCYCLEQUALIFIED_SID                             ((uint8)0x56)
/* Service ID for Dem_GetCycleQualified */
#define DEM_GETCYCLEQUALIFIED_SID                             ((uint8)0xab)
/* Service ID for Dem_GetDTCOfEvent */
#define DEM_GETDTCOFEVENT_SID                                 ((uint8)0x0d)
/* Service ID for Dem_GetSeverityOfDTC */
#define DEM_GETSEVERITYOFDTC_SID                              ((uint8)0x0e)
/* Service ID for Dem_SetDTCFilter */
#define DEM_SETDTCFILTER_SID                                  ((uint8)0x13)

/* Trace: DEM_19792_1A_03 */
/* Service ID for Dem_SetDTCFilterByExtendedDataRecord */
#define DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID              ((uint8)0xc1)
/* Trace: DEM_19792_56_03 */
/* Service ID for Dem_SetDTCFilterByReadinessGroup */
#define DEM_SETDTCFILTERBYREADINESSGROUP_SID                  ((uint8)0xc2)

/* Service ID for Dem_GetStatusOfDTC */
#define DEM_GETSTATUSOFDTC_SID                                ((uint8)0x15)
/* Service ID for Dem_GetDTCStatusAvailabilityMask */
#define DEM_GETDTCSTATUSAVAILABILITYMASK_SID                  ((uint8)0x16)
/* Service ID for Dem_GetNumberOfFilteredDTC */
#define DEM_GETNUMBEROFFILTEREDDTC_SID                        ((uint8)0x17)
/* Service ID for Dem_GetNumberOfFreezeFrameRecords */
#define DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID                 ((uint8)0x5a)
/* Service ID for Dem_GetNextFilteredDTC */
#define DEM_GETNEXTFILTEREDDTC_SID                            ((uint8)0x18)
/* Service ID for Dem_GetDTCByOccurrenceTime */
#define DEM_GETDTCBYOCCURRENCETIME_SID                        ((uint8)0x19)
/* Service ID for Dem_DisableDTCRecordUpdate */
#define DEM_DISABLEDTCRECORDUPDATE_SID                        ((uint8)0x1a)
/* Service ID for Dem_EnableDTCRecordUpdate */
#define DEM_ENABLEDTCRECORDUPDATE_SID                         ((uint8)0x1b)
/* Service ID for Dem_GetNextFreezeFrameData */
#define DEM_GETNEXTFREEZEFRAMEDATA_SID                        ((uint8)0x1d)
/* Service ID for Dem_GetExtendedDataRecordByDTC */

/* Service ID for Dem_SelectFreezeFrameData */
#define DEM_SELECTFREEZEFRAMEDATA_SID                         ((uint8)0xb9)
/* Service ID for Dem_SelectExtendedDataRecord */
#define DEM_SELECTEXTENDEDDATARECORD_SID                      ((uint8)0xba)

#define DEM_GETNEXTEXTENDEDDATARECORD_SID                     ((uint8)0x20)
/* Service ID for Dem_GetSizeOfExtendedDataRecordSelection */
#define DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID          ((uint8)0x21)
/* Service ID for Dem_ClearDTC */
#define DEM_CLEARDTC_SID                                      ((uint8)0x22)
/* Service ID for Dem_GetDTCSeverityAvailabilityMask */
#define DEM_GETDTCSEVERITYAVAILABILITYMASK_SID                ((uint8)0xb2)
/* Service ID for Dem_SelectDtc */
#define DEM_SELECTDTC_SID                                     ((uint8)0xb7)
/* Service ID for Dem_GetDTCSelectionResult */
#define DEM_GETDTCSELECTIONRESULT_SID                         ((uint8)0xb8)
/* Service ID for Dem_GetDTCSelectionResultForClearDTC */
#define DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID              ((uint8)0xbb)
/* Service ID for Dem_GetIndicatorStatus */
#define DEM_GETINDICATORSTATUS_SID                            ((uint8)0x29)
/* Service ID for Dem_GetComponentFailed */
#define DEM_GETCOMPONENTFAILED_SID                            ((uint8)0x2a)
/* Service ID for Dem_SetComponentAvailable */
#define DEM_SETCOMPONENTAVAILABLE_SID                         ((uint8)0x2b)
/* Service ID for Dem_MainFunction */
#define DEM_MAINFUNCTION_SID                                  ((uint8)0x55)
/* Service ID for Dem_SetEnableCondition */
#define DEM_SETENABLECONDITION_SID                            ((uint8)0x39)
/* Service ID for Dem_GetNextFilteredRecord */
#define DEM_GETNEXTFILTEREDRECORD_SID                         ((uint8)0x3a)
/* Service ID for Dem_GetNextFilteredDTCAndFDC */
#define DEM_GETNEXTFILTEREDDTCANDFDC_SID                      ((uint8)0x3b)
/* Service ID for Dem_GetNextFilteredDTCAndSeverity */
#define DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID                 ((uint8)0x3d)
/* Service ID for Dem_GetTranslationType */
#define DEM_GETTRANSLATIONTYPE_SID                            ((uint8)0x3c)
/* Service ID for Dem_GetFaultDetectionCounter */
#define DEM_GETFAULTDETECTIONCOUNTER_SID                      ((uint8)0x3e)
/* Service ID for Dem_SetEventAvailable */
#define DEM_SETEVENTAVAILABLE_SID                             ((uint8)0x37)
/* Service ID for Dem_SetEventDisabled */
#define DEM_SETEVENTDISABLED_SID                              ((uint8)0x51)
/* Service ID for Dem_SetEventFailureCycleCounterThreshold*/
#define DEM_SETEVENTFAILURECYCLECOUTERTHRESHOLD_SID           ((uint8)0x57)
/* Service ID for Dem_GetEventMemoryOverflow*/
#define DEM_GETEVENTMEMORYOVERFLOW_SID                        ((uint8)0x32)
/* Service ID for Dem_GetNumberOfEventMemoryEntries*/
#define DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID                 ((uint8)0x32)
/* Service ID for Dem_SetAgingCycleCounterValue*/
#define DEM_SETAGINGCYCLECOUNTERVALUE_SID                     ((uint8)0x12)

/* Service ID for Dem_SetAgingCycleState*/
/* #define DEM_SETAGINGCYCLESTATE_SID                         ((uint8)0x11)*/

/* Service ID for Dem_SetStorageCondition*/
#define DEM_SETSTORAGECONDITION_SID                           ((uint8)0x38)
/* Service ID for Dem_GetEventExtendedDataRecordEx*/
#define DEM_GETEVENTEXTENDEDDATARECORDEX_SID                  ((uint8)0x6d)
/* Service ID for Dem_GetEventFreezeFrameDataEx*/
#define DEM_GETEVENTFREEZEFRAMEDATAEX_SID                     ((uint8)0x6e)
/* Service ID for Dem_SetDTCSuppression*/
#define DEM_SETDTCSUPPRESSION_SID                             ((uint8)0x33)
/* Service ID for Dem_SetFreezeFrameRecordFilter*/
#define DEM_SETFREEZEFRAMERECORDFILTER_SID                    ((uint8)0x3f)
/* Service ID for Dem_GetFunctionalUnitOfDTC*/
#define DEM_GETFUNCTIONALUNITOFDTC_SID                        ((uint8)0x34)
/* Service ID for Dem_GetFreezeFrameDataByRecord*/
#define DEM_GETOBDFREEZEFRAMEDATABYRECORD_SID                 ((uint8)0x1c)
#define DEM_GETFREEZEFRAMEDATABYRECORD_SID                    ((uint8)0x1c)


/*  Dem_GetFreezeFrameDataByRecord is renamed  
    to Dem_DcmGetOBDFreezeFrameData()  in the AUTOSAR R4.1.2*/ 
    
/* Service ID for Dem_DcmGetOBDFreezeFrameData*/
#define DEM_GETOBDFREEZEFRAMEDATA_SID                         ((uint8)0x1c)


/* Service ID for Dem_GetSizeOfFreezeFrameSelection*/
#define DEM_GETSIZEOFFREEZEFRAMESELECTION_SID                 ((uint8)0x1f)
/* Service ID for Dem_DisableDTCSetting*/
#define DEM_DISABLEDTCSETTING_SID                             ((uint8)0x24)
/* Service ID for Dem_EnableDTCSetting*/
#define DEM_ENABLEDTCSETTING_SID                              ((uint8)0x25)
/* Service ID for Dem_DcmCancelOperation*/
#define DEM_DCMCANCELOPERATION_SID                            ((uint8)0x2a)
/* Service ID for Dem_DcmReadDataOfPID01*/
#define DEM_DCMREADDATAOFPID01_SID                            ((uint8)0x61)
/* Service ID for Dem_DcmReadDataOfPID1C*/
#define DEM_DCMREADDATAOFPID1C_SID                            ((uint8)0x63)
/* Service ID for Dem_SetDataOfPID21*/
#define DEM_SETDATAOFPID21_SID                                ((uint8)0xa6)
/* Service ID for Dem_GetDataOfPID21*/
#define DEM_GETDATAOFPID21_SID                                ((uint8)0xb1)
/* Service ID for Dem_DcmReadDataOfPID21*/
#define DEM_DCMREADDATAOFPID21_SID                            ((uint8)0x64)
/* Service ID for Dem_ReadDataOfPID01*/
#define DEM_READDATAOFPID01_SID                               ((uint8)0xb3)
/* Service ID for Dem_GetB1Counter*/
#define DEM_GETB1COUNTER_SID                                  ((uint8)0xb4)
/* Service ID for Dem_DcmReadDataOfPID30*/
#define DEM_DCMREADDATAOFPID30_SID                            ((uint8)0x65)
/* Service ID for Dem_DcmReadDataOfPID31*/
#define DEM_DCMREADDATAOFPID31_SID                            ((uint8)0x66)
/* Service ID for Dem_DcmReadDataOfPID41*/
#define DEM_DCMREADDATAOFPID41_SID                            ((uint8)0x67)
/* Service ID for Dem_DcmReadDataOfPID4D*/
#define DEM_DCMREADDATAOFPID4D_SID                            ((uint8)0x68)
/* Service ID for Dem_DcmReadDataOfPID4E*/
#define DEM_DCMREADDATAOFPID4E_SID                            ((uint8)0x69)
/* Service ID for Dem_DcmReadDataOfPID91*/
#define DEM_DCMREADDATAOFPID91_SID                            ((uint8)0x6a)
/* Service ID for Dem_DcmReadDataOfOBDFreezeFrame*/
#define DEM_DCMREADDATAOFOBDFREEZEFRAME_SID                   ((uint8)0x52)
/* Service ID for Dem_DcmGetDTCOfOBDFreezeFrame*/
#define DEM_DCMGETDTCOFOBDFREEZEFRAME_SID                     ((uint8)0x53)
/* Service ID for Dem_SetPtoStatus*/
#define DEM_SETPTOSTATUS_SID                                  ((uint8)0x79)
/* Service ID for Dem_RepIUMPRFaultDetect*/
#define DEM_REPIUMPRFAULTDETECT_SID                           ((uint8)0x73)

/* Service ID for Dem_SetDTR*/
#define DEM_SETDTR_SID                                        ((uint8)0xa2)

/* Service ID for Dem_SetIUMPRDenCondition*/
#define DEM_SETIUMPRDENCONDITION_SID                          ((uint8)0xae)
/* Service ID for Dem_GetIUMPRDenCondition*/
#define DEM_GETIUMPRDENCONDITION_SID                          ((uint8)0xaf)

/* Service ID for Dem_RepIUMPRDenRelease*/
#define DEM_REPIUMPRDENRELEASE_SID                            ((uint8)0x72)
/* Service ID for Dem_SetWIRStatus*/
#define DEM_SETWIRSTATUS_SID                                  ((uint8)0x7a)
/* Service ID for Dem_DcmGetInfoTypeValue08*/
#define DEM_DCMGETINFOTYPEVALUE08_SID                         ((uint8)0x6b)
/* Service ID for Dem_GetInfoTypeValue0B*/
#define DEM_DCMGETINFOTYPEVALUE0B_SID                         ((uint8)0x6c)

/* Trace: DEM_19792_06_16 */
/* Service ID for Dem_GetInfoTypeValue79*/
#define DEM_DCMGETINFOTYPEVALUE79_SID                         ((uint8)0xc3)

/* Service ID for Dem_SetDataOfPID31*/
#define DEM_SETDATAOFPID31_SID                            ((uint8)0xa7)
/* Service ID for Dem_SetDataOfPID4D*/
#define DEM_SETDATAOFPID4D_SID                            ((uint8)0xa8)
/* Service ID for Dem_SetDataOfPID4E*/
#define DEM_SETDATAOFPID4E_SID                            ((uint8)0xa9)

/* Service ID for Dem_DcmGetDTRData */
#define DEM_DCMGETDTRDATA_SID                            ((uint8)0xa5)
/* Service ID for Dem_DcmGetNumTIDsOfOBDMID */
#define DEM_DCMGETNUMTIDSOFOBDMID_SID                    ((uint8)0xa4)
/* Service ID for Dem_DcmGetAvailableOBDMIDs */
#define DEM_DCMGETAVAILABLEOBDMIDS_SID                   ((uint8)0xa3)


/* Service ID for Dem_GetDTCSuppression*/
#define DEM_GETDTCSUPPRESSION_SID                             ((uint8)0xbc)
/* Service ID for Dem_GetMonitorStatus*/
#define DEM_GETMONITORSTATUS_SID                              ((uint8)0xB5)
/* Service ID for Dem_GetEventUdsStatus*/
#define DEM_GETEVENTUDSSTATUS_SID                             ((uint8)0xB6)
/* Service ID for Dem_SetEventStatusWithMonitorData*/
#define DEM_SETEVENTSTATUSWITHMONITORDATA_SID                 ((uint8)0xBD)
/* Service ID for Dem_GetDebouncingOfEvent*/
#define DEM_GETDEBOUNCINGOFEVENT_SID                          ((uint8)0x9F)

/* AUTOEVER specific sid */
#define DEM_EVMEM_FINDNEWOREXISTEDENTRY_SID                   ((uint8)0x60)
#define DEM_UNSPECIFIED_SID                                   ((uint8)0xFE)
#define DEM_CAPTUREDATAELEMENTCLASS_SID                       ((uint8)0xFD)


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

/* Called by BswM */
extern FUNC(void, DEM_CODE) Dem_ReadNvData(void);

/* Called by BswM */
extern FUNC(void, DEM_CODE) Dem_WriteNvData(void);

/* 
  polyspace:begin<MISRA-C:16.4:Not a defect:Justify with annotations> Not a defect 
*/

/* Dem_GetVersionInfo */
/* @Trace: DEM_SUD_DATATYPE_005 */
extern FUNC(void, DEM_CODE) Dem_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA) versioninfo);

/* Dem_PreInit */
extern FUNC(void, DEM_CODE) Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_APPL_CONST)Dem_ConfigPtr);

/* Dem_Init */
extern FUNC(void, DEM_CODE) Dem_Init(void);

/* Dem_Shutdown */
extern FUNC(void, DEM_CODE) Dem_Shutdown(void);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventUdsStatus
  (Dem_EventIdType EventId,
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) UDSStatusByte);
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetMonitorStatus
  (Dem_EventIdType EventId,
  P2VAR(Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA) MonitorStatus);
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus
  (Dem_EventIdType EventId, Dem_EventStatusType EventStatus);


#ifndef DEM_SWCGEN
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatusWithMonitorData(
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus,
  Dem_MonitorDataType monitorData0,
  Dem_MonitorDataType monitorData1);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventFailureCycleCounterThreshold(
  Dem_EventIdType EventId,
  uint8 FailureCycleCounterThreshold);
#endif

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventStatus(
  Dem_EventIdType EventId);
extern FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventDebounceStatus(
  Dem_EventIdType EventId,
  Dem_DebounceResetStatusType DebounceResetStatus);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDebouncingOfEvent(
  Dem_EventIdType EventId,
  Dem_DebouncingStateType* DebouncingState);

/* Dem_GetDTCOfEvent */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfEvent(
  Dem_EventIdType EventId,
  Dem_DTCFormatType DTCFormat,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTCOfEvent);

/* Dem_SetEnableCondition */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEnableCondition
  (uint8 EnableConditionID, boolean ConditionFulfilled);

/* Dem_SetStorageCondition */
extern  FUNC(Std_ReturnType, DEM_CODE) Dem_SetStorageCondition(
  uint8 StorageConditionID, 
  boolean ConditionFulfilled);

/* Dem_RestartOperationCycle */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_RestartOperationCycle(
  uint8 OperationCycleId);


#ifndef DEM_SWCGEN
#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventAvailable(
  Dem_EventIdType EventId, boolean AvailableStatus);
#endif
#endif
/* Dem_GetCycleQualified */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetCycleQualified(
  uint8 OperationCycleId,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) isQualified);

/* Dem_SetCycleQualified */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetCycleQualified(
        uint8 OperationCycleId );

/* Dem_GetIndicatorStatus */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(
  uint8 IndicatorId,
  P2VAR (Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus);

/* Dem_GetEventFreezeFrameDataEx */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType EventId, 
  uint8 RecordNumber, 
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);

/* Dem_GetEventExtendedDataRecordEx */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType EventId,
  uint8 RecordNumber,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);

#ifndef DEM_SWCGEN
/* Dem_GetEventMemoryOverflow */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventMemoryOverflow(uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) OverflowIndication);
#endif

#ifndef DEM_SWCGEN
/* Dem_GetNumberOfEventMemoryEntries */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetNumberOfEventMemoryEntries(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) NumberOfEventMemoryEntries);
#endif

#ifndef DEM_SWCGEN
#if(DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
extern FUNC(Std_ReturnType, DEM_CODE)Dem_SetDTCSuppression(
  uint8 ClientId,
  boolean SuppressionStatus);
#endif

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSuppression(
  uint8 ClientId,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) SuppressionStatus);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetWIRStatus(
  Dem_EventIdType EventId,
  boolean WIRStatus);
#endif

/* Dem_GetDTCStatusAvailabilityMask */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetDTCStatusAvailabilityMask(
  uint8 ClientId,
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) DTCStatusMask);

/* Dem_SetDTCFilter */
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCFilter(
  uint8 ClientId,
  uint8 DTCStatusMask,
  Dem_DTCFormatType DTCFormat,
  Dem_DTCOriginType DTCOrigin,
  boolean FilterWithSeverity,
  Dem_DTCSeverityType DTCSeverityMask,
  boolean FilterForFaultDetectionCounter);

#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_56_03 */
/* Dem_SetDTCFilterByReadinessGroup */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCFilterByReadinessGroup(
  uint8 ClientId,
  Dem_DTCFormatType DTCFormat, 
  Dem_EventOBDReadinessGroupType ReadinessGroupNumber);

/* Trace: DEM_19792_1A_03 */
/* Dem_SetDTCFilterByExtendedDataRecordNumber */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCFilterByExtendedDataRecordNumber(
        uint8 ClientId,
        Dem_DTCFormatType DTCFormat, 
        uint8 ExtendedDataRecordnumber);
#endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

/* Dem_GetTranslationType */
extern FUNC(Dem_DTCTranslationFormatType, DEM_CODE)Dem_GetTranslationType(uint8 ClientId);

/* Dem_GetNumberOfFilteredDTC */
extern FUNC(Std_ReturnType, DEM_CODE)
  Dem_GetNumberOfFilteredDTC(
  uint8 ClientId,
  P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredDTC);

/* Dem_GetNextFilteredDTC */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFilteredDTC(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus);

/* Dem_GetNextFilteredDTCAndSeverity */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFilteredDTCAndSeverity(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus,
  P2VAR (Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit);

/* Dem_GetStatusOfDTC */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetStatusOfDTC(
  uint8 ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus);

/* Dem_GetSeverityOfDTC */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetSeverityOfDTC(
  uint8 ClientId,
  P2VAR (Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity);

/* Dem_GetFunctionalUnitOfDTC */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetFunctionalUnitOfDTC(
  uint8 ClientId,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit);

/* Dem_DisableDTCRecordUpdate */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DisableDTCRecordUpdate(
  uint8 ClientId);

/* Dem_EnableDTCRecordUpdate */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_EnableDTCRecordUpdate(
  uint8 ClientId);

/* Dem_SetFreezeFrameRecordFilter */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_SetFreezeFrameRecordFilter(
  uint8 ClientId,
  Dem_DTCFormatType DTCFormat);

/* Dem_GetNumberOfFilteredDTC */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetNumberOfFreezeFrameRecords(
  uint8 ClientId,
  P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredRecords);

/* Dem_GetDTCByOccurrenceTime */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCByOccurrenceTime(
  uint8 ClientId,
  Dem_DTCRequestType DTCRequest,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC);

/* Dem_GetNextFilteredRecord */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFilteredRecord(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) RecordNumber);

/* Dem_GetNextFilteredDTCAndFDC */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFilteredDTCAndFDC(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) DTCFaultDetectionCounter);

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
/* Dem_GetComponentFailed */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetComponentFailed(
  Dem_ComponentIdType ComponentId,
  boolean* ComponentFailed);
#endif

#ifndef DEM_SWCGEN
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
/* Dem_SetComponentAvailable */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetComponentAvailable(
  Dem_ComponentIdType ComponentId,
  boolean AvailableStatus);
#endif
#endif

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
/* Dem_SelectFreezeFrameData */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SelectFreezeFrameData(
  uint8 ClientId,
  uint8 RecordNumber);
/* Dem_GetNextFreezeFrameData */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFreezeFrameData(
  uint8 ClientId,
  P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize);
/* Dem_GetSizeOfExtendedDataRecordSelection */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetSizeOfFreezeFrameSelection(
  uint8 ClientId,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) SizeOfFreezeFrame);
/*Dem_SelectExtendedDataRecord*/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SelectExtendedDataRecord(
  uint8 ClientId,
  uint8 ExtendedDataNumber);
/*Dem_GetNextExtendedDataRecord*/
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextExtendedDataRecord(
  uint8 ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize);
/*Dem_GetSizeOfExtendedDataRecordSelection*/
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfExtendedDataRecordSelection(
  uint8 ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfExtendedDataRecord);
#endif

/* Dem_DisableDTCSetting */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DisableDTCSetting
  (uint8 ClientId);

/* Dem_EnableDTCSetting */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_EnableDTCSetting
  (uint8 ClientId);

/* Dem_GetDTCSelectionResultForClearDTC */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCSelectionResultForClearDTC(
  uint8 ClientId);

#ifndef DEM_SWCGEN
/* Dem_SelectDTC */
FUNC(Std_ReturnType, DEM_CODE) Dem_SelectDTC(uint8 ClientId, uint32 DTC,
  Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);

/* Dem_GetDTCSelectionResult */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCSelectionResult(uint8 ClientId);
#endif

/* Dem_DcmCancelOperation */
extern FUNC(void, DEM_CODE) Dem_DcmCancelOperation(void);

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTR(
  uint16 DTRId,
  sint32 TestResult,
  sint32 LowerLimit,
  sint32 UpperLimit,
  Dem_DTRControlType Ctrlval);
#endif


#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE)Dem_SetEventDisabled(
  Dem_EventIdType EventId);

#if(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
/* Dem_RepIUMPRFaultDetect */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_RepIUMPRFaultDetect(
Dem_RatioIdType RatioID);
#endif

/* Dem_GetDTCOfOBDFreezeFrame */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_GetDTCOfOBDFreezeFrame(
  uint8 FrameNumber, 
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC);

/* Dem_SetPtoStatus */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_SetPtoStatus(
  boolean PtoStatus);
#endif

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC(uint8 ClientId);

/* Dem_MainFunction */
extern FUNC(void, DEM_CODE) Dem_MainFunction(void);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType EventId);

#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_PrestoreFreezeFrame(
  Dem_EventIdType EventId);
#endif

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetFaultDetectionCounter(
  Dem_EventIdType EventId,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter);
#ifndef DEM_SWCGEN
extern FUNC(Std_ReturnType, DEM_CODE) Dem_CddClearDTC(uint8 ClientId);
#endif
/* polyspace:end<MISRA-C:16.4:Not a defect:Justify with annotations> Not a defect */


#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetIUMPRDenCondition(
  VAR(Dem_IumprDenomCondIdType, DEM_VAR) ConditionId,
  VAR(Dem_IumprDenomCondStatusType, DEM_VAR) CondidtionStatus);
#endif

#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
extern FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenRelease(
  VAR(Dem_RatioIdType, DEM_VAR) RatioID);
#endif

  #if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetIUMPRDenCondition(
  VAR(Dem_IumprDenomCondIdType, DEM_VAR) ConditionId,
  P2VAR(Dem_IumprDenomCondStatusType, AUTOMATIC, DEM_VAR) CondidtionStatus);
#endif

#if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU))
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDataOfPID21 (
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID21value );
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetB1Counter(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) B1Counter);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID01Value);
#endif

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCSeverityAvailabilityMask(
  uint8 ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverityMask);

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                  NVRAM Block Id Permanent RAM addresses                     *
*******************************************************************************/
/* 
   polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect
   polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect
   polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations> Not a defect 
*/

#endif /* DEM_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
