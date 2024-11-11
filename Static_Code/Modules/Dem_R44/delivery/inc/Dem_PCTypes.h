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
**  SRC-MODULE: Dem_PCTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : This file contains the structure definitions and macro        **
**              definitions of DEM module                                     **
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
** 2.1.0.0   31-Mar-2024   EK Kim        Jira #CP44-4039 #CP44-3777           **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.16    28-Nov-2023   DanhTQ1       Jira #CP44-3052                      **
** 1.0.8.0   13-Dec-2021   SY Kim        Jira #CP44-1169                      **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_PCTYPES_H
#define DEM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations>
 * Not a defect */
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */

#include "Dem_Types.h"
#include "Dem_J1939Types.h"
#include "NvM.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, DemCallbackDTCStatusChangedFncType)
(uint32 DTC, uint8 DTCStatusOld, uint8 DTCStatusNew);

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_MonitorStatusChangedFctPtrType)
(Dem_EventIdType EventId);

/*******************************************************************************
 ** Structure for Dem Client Type                                             **
 *******************************************************************************/
typedef struct STag_Dem_ClientType
{
  /* Dem Client Functionality */
  uint8                                  usDemClientFunctionality;
  /* Dem Client Id */
  Dem_ClientIdType                       usDemClientId;
  /* Dem Client Uses Rte */
  boolean                                blDemClientUsesRte;
  /* Dem Event Memory Set Id */
  uint8                                  usDemEventMemorySetId;
  /* number of Dem Callback DTC Status Changed */
  uint8                                  usNumCallbackDTCStatusChangedFnc;
  /* Index Indices array of DemCallbackDTCStatusChanged array */
  uint8                                  usCallbackDTCStatusChangedFncId;
}Dem_ClientType;

/*******************************************************************************
 ** Structure for Dem Config Data Type                                        **
 *******************************************************************************/
#ifndef DEM_SWCGEN
typedef struct STag_Dem_ConfigData
{
  uint8 LucDummy;
} Dem_ConfigType;
#endif
/*******************************************************************************
 ** Structure for Dem Data Element External CS Type                           **
 *******************************************************************************/
typedef struct STag_Dem_DataElementExternalCSType {
  /*defines the prototype of the C function "ReadDataElement"*/
    P2FUNC(Std_ReturnType, DEM_APPL_CODE, pDemDataElementReadFnc)
( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA));

  /*Defines the size of the data element in bytes*/
  uint8 ucDemDataElementDataSize;

  /*Defines whether data is obtained through R-Port or DemDataElementReadFnc*/
  boolean blDemDataElementUsePort;

} Dem_DataElementExternalCSType;

/*******************************************************************************
 ** Structure for Dem Storage Condition Type                                  **
 *******************************************************************************/
typedef struct STag_Dem_StorageConditionType {
  /* Dem Storage Condition Status */
  boolean blDemStrCondStt;

  /* Dem Storage Condition Replacement Event Reference */
  Dem_EventIdType ucDemEventIdx;

} Dem_StorageConditionType;

/*******************************************************************************
 ** Structure for Dem Internal Data Element Class Type                        **
 *******************************************************************************/
typedef struct STag_Dem_DataElementInternalType {
  /*Defines the size of the data element in bytes*/
  uint8 ucDemDataElementDataSize;

  /*defines which parameter is mapped to the data element*/
  uint8 ucDemInternalDataElement;

} Dem_DataElementInternalType;

/*******************************************************************************
 ** Operation cycle IDs and related events structure                          **
 *******************************************************************************/
typedef struct STag_Dem_OperationCycleType 
{
  /* @Trace: Dem_SUD_MACRO_101 */
  #if(DEM_MAX_EVENT_PER_CYCLE > DEM_ZERO)
  /* Stores the number of EventIDs configured for the OperationCycleId */
  Dem_EventIdType NumOfEvents;

  /* Index of the Indices array of EventParameter array */
  CONSTP2CONST(Dem_EventIdType, AUTOMATIC, DEM_CONST) ListOfEventIndex;
  #endif

  /* Operation Cycle Id */
  uint8 ucOperationCycleId;

  /* Dem Leading Cycle Reference */
  uint8 usDemLeadingCycleRef;

  /* index of dependence operation cycle*/
  uint8 usDemDepdntOpCylIdx;

  /* size of dependence operation cycle */
  uint8 usNumberOfDemDepdntOpCyl;

} Dem_OperationCycleType;
/********************************************************************************
 ** Operation cycle IDs and related events structure                          **
 *******************************************************************************/
typedef struct STag_Dem_OperationCycleName {
  /* Operation Cycle Id */
  uint8 ucOperationCycle;

} Dem_OperationCycleName;


/*******************************************************************************
 **                 Structure for DEM Multi Event Triggering                  **
 *******************************************************************************/

typedef struct STag_Dem_MultiEventTrgType
{
  Dem_EventIdType    masterEventIdx;
  uint8              slaveEventIdx;
  uint8              numberOfSlaveEvent;
}Dem_MultiEventTrgType;


/*******************************************************************************
 ** Dem Primary Memory                                                        **
 *******************************************************************************/
typedef struct STag_Dem_PrimaryMemoryType
{
  /* Dem Environment Data Capture */
  uint8 usDemEnvironmentDataCapture;

  /* Dem Event Displacement Strategy */
  uint8 usDemEventDisplacementStrategy;

  /* Dem Event Memory Entry Storage Trigger */
  uint8 usDemEventMemoryEntryStorageTrigger;

  /* Dem Max Number Event Entry Primary */
  uint8 usDemMaxNumberEventEntryPrimary;

  /* Dem Occurrence Counter Processing */
  uint8 usDemOccurrenceCounterProcessing;

  /* Dem Type Of Freeze Frame Record Numeration */
  uint8 usDemTypeOfFreezeFrameRecordNumeration;

  /* start index in Primary memory*/
  uint8 usStartIdx;
  /* stop index in Primary memory*/
  uint8 usStopIdx;

} Dem_PrimaryMemoryType;
/*******************************************************************************
 ** Dem User Defined Memory                                                   **
 *******************************************************************************/
typedef struct STag_Dem_UserDefinedMemoryType
{
  /* Dem Environment Data Capture */
  uint8 usDemEventMemorySet;

  /* Dem Environment Data Capture */
  uint8 usDemEnvironmentDataCapture;

  /* Dem Event Displacement Strategy */
  uint8 usDemEventDisplacementStrategy;

  /* Dem Event Memory Entry Storage Trigger */
  uint8 usDemEventMemoryEntryStorageTrigger;

  /* Dem Max Number Event Entry User Defined */
  uint8 usDemMaxNumberEventEntryUserDefined;

  /* Dem Occurrence Counter Processing */
  uint8 usDemOccurrenceCounterProcessing;

  /* Dem Type Of Freeze Frame Record Numeration*/
  uint8 usDemTypeOfFreezeFrameRecordNumeration;

  /* Dem User Defined Memory Identifier */
  uint8 usDemUserDefinedMemoryIdentifier;

  /* start index in User Defined memory*/
  uint8 usStartIdx;

  /* stop index in User Defined memory*/
  uint8 usStopIdx;

} Dem_UserDefinedMemoryType;



/*******************************************************************************
 ** Clear Dtc Notification                                                    **
 *******************************************************************************/
typedef struct STag_Dem_ClearDtcNotificationType
{
    /* Dem Dtc Clear Dtc Notification callback function */
    P2FUNC(Std_ReturnType, DEM_APPL_CODE, pDemClearDtcNotificationFnc)
    (uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);

    /* Dem clear Dtc notification time */
    uint8 usNotTime;

} Dem_ClearDtcNotificationType;

/*******************************************************************************
 ** Dem Memory Set                                                            **
 *******************************************************************************/
/* @Trace: Dem_SUD_DATATYPE_00008 */
typedef struct STag_Dem_MemorySetType
{
  /* Dem Dtc Status Availability Mask */
  uint8 usDemDtcStatusAvailabilityMask;

  /* Dem Start Permanent Index*/
  uint8 usDemPermanentStartIdx;

  /* Dem Max Number Event Entry Permanent */
  uint8 usDemMaxNumberEventEntryPermanent;

  /* Dem Type Of DTC Supported */
  uint8 eDemTypeOfDTCSupported;

  /* Dem Amber Warning Lamp Indicator Ref*/
  uint8 usDemAmberWarningLampIndicatorRef;

  /* Dem MIL Indicator Ref */
  uint8 usDemMILIndicatorRef;

  /* Dem Protect Lamp Indicator Ref */
  uint8 usDemProtectLampIndicatorRef;

  /* Dem Red Stop Lamp Indicator Ref */
  uint8 usDemRedStopLampIndicatorRef;

  /* Dem Primary Memory */
  uint8 usDemPrimaryMemoryIndex;

  /* start index mirror memory*/
  uint8 usDemMirrorStartIdx;

  /* stop index mirror memory*/
  uint16 usDemMirrorStopIdx;

  /* Dtc Clear Notification Index*/
  uint16 usDtcClearNotIdx;

  /* Dtc Clear Notification Number*/
  uint16 usNumOfDtcClearNot;

} Dem_MemorySetType;

/*******************************************************************************
 **                 Structure for combined DTC                                **
 *******************************************************************************/
/* @Trace: Dem_SUD_DATATYPE_00003 */
typedef struct STag_Dem_CombinedDtcType
{
  /* Stores the number of EventIDs configured for the DTC */
  Dem_EventIdType ddNumberOfEvents;

  /* Events Configured for DTC */
  Dem_NumOfEventIdType dtc_PointToEventList;

  /* DTCGroup Index*/
  Dem_DTCGroupType ddDtcGroup;

  /* Kind of DTC */
  Dem_DTCKindType ddDtcKind;

  /* Format of DTC */
  Dem_DTCFormatType ddDtcFormat;

  /* Severity of DTC */
  Dem_DTCSeverityType ddDtcSeverity;

  /* Diagnostic Trouble Code For NON-OBD*/
  uint32 ulUdsDtc;

  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  /* Diagnostic Trouble Code For OBD*/
  uint16 usObdDtc;
  #endif

  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  uint32 ulObdDtc3Byte;
  #endif

  /* Diagnostic Trouble Code FunctionalUnit */
  uint8 ucDtcFunctionalUnit;

  /* Flag to enable Immediate NVRAM Storage */
  uint8 EvMemTriggerFlag;

  #if (DEM_J1939_SUPPORT == STD_ON)
  uint32 J1939DTCValue;

  #endif

  Dem_UdsStatusByteType UdsStatusAvailabilityMask;


  uint16 usDemDTCAttributesRef;

  /* @Trace: SRS_Diag_04141
   */
  /* @Trace: SWS_Dem_01140
   * The Dem shall provide a class value per DTC (to characterize the
   * impact of a malfunction OBD system"s monitoring capability) according to
   * ISO 14229-1 [1], Annex D.3 "DTCSeverityMask and DTC class information bit
   * definitions" (refer to Dem_GetSeverityOfDTC and
   * Dem_GetNextFilteredDTCAndSeverity), only if configured for at least one DTC.*/
  /*Dem WWHOBD DTC Class*/
  Dem_WWHOBDDTCClassType eDemWWHOBDDTCClass;

}Dem_CombinedDtcType;


/*******************************************************************************
 ** Structure type of DTR                                                     **
 *******************************************************************************/

typedef struct STag_Dem_DTRDataType {
  /* @Trace: SRS_Diag_04129
   */
  /* @Trace: SWS_Dem_00752
   * The DemDtrId is assigned by the Dem during the BSW configuration step.*/

  /* Test value */
  uint16 Testvalue;

  /* Low lim value*/
  uint16 Lowlimvalue;

  /* Upp lim value  */
  uint16 Upplimvalue;

  /* Control Type*/
  Dem_DTRControlType Ctrlval;

} Dem_DTRDataType;

/* @Trace: SRS_Diag_04001
 */
/* @Trace: SWS_Dem_00751
 * The Dem shall provide data structures and functionality to receive, store and
 * report Service$06 test results persistently
 * */

typedef struct STag_Dem_DTRType {
  /* @Trace: SRS_Diag_04129
   */
  /* @Trace: SWS_Dem_00752
   * The DemDtrId is assigned by the Dem during the BSW configuration step.*/

  /* Dem Dtr Id */
  uint16 usDemDtrId;

  /* @Trace: SRS_Diag_04001
   */
  /* @Trace: SWS_Dem_00753
   * For ensuring data consistency, an EventId can only be referenced by
   * at maximum one DTR.*/

  /* Event Id Ref*/
  uint16 usEventId;

  /* OBD Monitor Identifier  */
  uint8 usOBDMID;

  /* Tester Identifier */
  uint8 usTID;

  /* Tester Identifier */
  uint8 usTIDIndex;

  /* Unit and Scaling ID */
  uint8 usUaSID;

  /* Dem update kind*/
  uint8 usUpdateKind;

  /* @Trace: SWS_Dem_00758
   * The Dem shall support a conversion of the ECUinternal resolution into
   * the standardized external uint16 size and resolution according to the
   * configured and standardized UaSID. For that reason, the conversion
   * formula is configured per DTR. It is assumed that the conveyed parameter
   * of the API call contain the values in the internal size and resolution.
   * The Dem does offer sint32 as parameter for that reason to cover uint16
   * as well as sint16 (or even sint32) internal data types. */
  /* Dtr Compu Denominator 0*/
  uint16 usDemDtrCompuDenominator0;

  /* Dem Dtr Compu Numerator0*/
  uint16 usDemDtrCompuNumerator0;

  /* Dem Dtr Compu Numerator1*/
  uint16 usDemDtrCompuNumerator1;
} Dem_DTRType;
/*******************************************************************************
 **                 Structure type of Pid Record                              **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
typedef struct STag_Dem_PidRecordType
{
  /* Freeze Frame is configured for Pid */
  uint8 ucPid;

  /* No of data elements */
  uint8 ucNumOfDataElements;

}Dem_PidRecordType;
#endif
/*******************************************************************************
 **                 Structure type of Pid Record                              **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
typedef struct STag_Dem_PidDataElementType
{

  uint8 ucDataElementType;

  uint8 ucDataElementIndex;

}Dem_PidDataElementType;
#endif

/*******************************************************************************
 ** Indicator Attribute list                                                  **
 *******************************************************************************/
typedef struct STag_Dem_IndicatorAttributeType 
{
  /* @Trace: Dem_SUD_MACRO_102 */
  uint8 IndicatorIdRef;             
  Dem_EventIdType EventIdRef;       
  Dem_IndicatorStatusType Behavior; /* blinking , conti ...*/

  /*
  Dem_EventIdType ddNumberOfEvents;
  Dem_EventIdType ListOfEventIndex[DEM_MAX_EVENT_PER_INDICATOR];
  */

  uint8 NumFailureCycles; /* for the WarningIndicatorOnCriteria */
  uint8 NumHealingCycles; /* for the WarningIndicatorOffCriteria */
  
  Dem_NumOfIndicatorAttributeType HealingCycleCounterPos;
  Dem_NumOfIndicatorAttributeType FailureCycleCounterPos;
  Dem_NumOfIndicatorAttributeType IndicatorAttStatusPos;

  /*TODO*/
  #if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && 0
  P2VAR(uint8, AUTOMATIC, DEM_VAR) ObdMilCycleCounter;
  #endif
} Dem_IndicatorAttributeType;

/*******************************************************************************
 ** Structure for DEM Pre Debounce Counter Type                               **
 *******************************************************************************/
#if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON)
/* @Trace: Dem_SUD_DATATYPE_00006 */
typedef struct STag_Dem_PreDebounceCounterType {
  /* Dem Counter Based Fdc Threshold Storage Value*/
  sint16 ssDemCounterBasedFdcThresholdStorageValue;

  /* Dem Debounce Behavior */
  Dem_DebounceBehaviorType eDemDebounceBehavior;

  /* Step size for increment of FDC */
  uint16 usDemCountIncStepSize;

  /* Step size for decrementing the FDC */
  uint16 usDemCountDecStepSize;

  /*Counter Failed Threshold*/
  sint16 ssDemCounterFailedThreshold;

  /*Counter Passed Threshold*/
  sint16 ssDemCounterPassedThreshold;

  /*Jump Up Value */
  sint16 ssDemCounterJumpUpValue;

  /*Jump Down Value*/
  sint16 ssDemCounterJumpDownValue;

  /* Switch for the Dem Jump Down */
  boolean blDemJumpDown;

  /* Switch for the Dem Jump Up */
  boolean blDemJumpUp;

  /*Dem Debounce Counter Storage */
  boolean blDemDebounceCounterStorage;

} Dem_PreDebounceCounterType;
#endif
/*******************************************************************************
 ** Structure for DEM Pre Debounce Monitor Internal Type                      **
 *******************************************************************************/
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO)
typedef struct STag_Dem_PreDebounceMonitorInternalType
{

  /* Pointer to DemCallBackGetFaultDetectionCounter Function */
  P2FUNC(Std_ReturnType, DEM_APPL_CODE, pDemCallBackGetFDCnt)
  (P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA));

  Dem_EventIdType dmi_EventId; /* not used */

}Dem_PreDebounceMonitorInternalType;
#endif
/*******************************************************************************
 ** Structure for DEM Pre Debounce Time Base Type                             **
 *******************************************************************************/
#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
/* @Trace: Dem_SUD_DATATYPE_00007 */
typedef struct STag_Dem_PreDebounceTimeBasedType {

  /* Dem Debounce Behavior */
  uint8 eDemDebounceBehavior;
  /**/
  /* Time out duration in ms for Event Failed qualification in Dem */
  uint32 ulDemTimeFailedThreshold;

  /* Time out duration in ms for Event Passed qualification in Dem */
  uint32 ulDemTimePassedThreshold;

  /*Dem Time Based Fdc Threshold Storage Value */
  uint32 ulDemTimeBasedFdcThresholdStorageValue;

  /* Event Id */
  Dem_EventIdType t_EventId;

} Dem_PreDebounceTimeBasedType;
#endif




/*******************************************************************************
 ** function pointer typedefinition                                           **
 *******************************************************************************/
/* There is not return type in the AR 4.2.1 */
/* Fixed : Argument EventId is removed */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_EvtStatusChangedFctPtrType)
(Dem_UdsStatusByteType EventStatusOld, Dem_UdsStatusByteType EventStatusNew);

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_DtcStatusChangedFctPtrType)
(uint32 DTC, uint8 DTCStatusOld, uint8 DTCStatusNew);

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_DtcInitMonitorOfFctPtrType)
(Dem_InitMonitorReasonType InitMonitorReason);

/*******************************************************************************
 ** Record Update Structure                                                   **
 *******************************************************************************/

typedef struct STag_Dem_RecordUpdateType {
  /* Diagnostic Trouble Code For NON-OBD*/
  uint32 ulUdsDtc;

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  /* Diagnostic Trouble Code For OBD*/
  uint16 usObdDtc;
#endif
} Dem_RecordUpdateType;

typedef struct STag_Dem_TimeDebounceStatusType 
{
  /* Event Status of Time based debouncing*/
  Dem_EventStatusType tds_EventStatus;
  uint32 tds_Counter;
} Dem_TimeDebounceStatusType;

typedef struct STag_Dem_FilteredFreezeFrameRecordType
{
  Dem_EventIdType nextEvent;
  Dem_NumOfRecordNumberType nextRecord;
  /*  Dem_NumOfEventIdType numOfEvents; */
  uint16 numberOfFilteredRecords;
  /* service retention lock*/
  boolean isLockService[DEM_MAXIMUM_SETFREEZEFRAMERECORDFILTER_SID_LOCKID];
  /* result of Dem_SetFreezeFrameRecordFilter */
  boolean resultSetFFRecFilter;
#if ((DEM_J1939_SUPPORT == STD_ON) && \
    ((DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON) || \
     (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)))
  /* kind of J1939 Freeze Frame */
  uint8 j1939FF_JobAction;
  uint8 j1939Ratio_JobAction;
  Dem_J1939DcmSetFreezeFrameFilterType kindOfJ1939FreezeFrame;
#endif
} Dem_FilteredFreezeFrameRecordType;


/*******************************************************************************
 ** Structure for DEM External Data Element Class Type                        **
 *******************************************************************************/
typedef  P2FUNC(uint8, DEM_APPL_CODE, Dem_DataElementReadFuncType)
  (P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA), Dem_MonitorDataType monitorData0);

typedef  P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_SRDataElementReadFuncType)
  (P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA));

typedef struct STag_Dem_DataElementClassType {
  /*defines the prototype of the C function "ReadDataElement" */
  Dem_DataElementReadFuncType ReadFunc;

  /*defines the prototype of the C function "ReadDataElement" with SR port*/
  Dem_SRDataElementReadFuncType SRReadFunc;

  /*Defines the size of the data element in bytes*/
  Dem_SizeOfDataElementClassType size;

  /*
   bit 0 : Defines whether DataElement is Internal Type or External type
   bit 1-31 : defines which parameter is mapped to the data element
   */
  uint32 type;
} Dem_DataElementClassType;

/******************************************************************************
 *                 Did class
 ******************************************************************************/
typedef struct STag_Dem_DidClassType {
  /* Freeze Frame is configured for Did */
  Dem_DataIdentifierType DataId;

  Dem_SizeOfDidClassType size;

  /* No of data elements */
  Dem_NumOfDataElementClassType NumOfDataElementClass;
  
  /* Size of all DataElements in bytes */
  uint16 PointToDataElementMap;
} Dem_DidClassType;


/*******************************************************************************
 ** Freeze frame class                                                        **
 *******************************************************************************/
/* @Trace: Dem_SUD_DATATYPE_00004 */
typedef struct STag_Dem_FreezeFrameClassType {
  Dem_SizeOfFreezeFrameClassType size;
  const Dem_NumOfDidClassType NumOfDidClass;
  /* An array of the DID */
  uint16 PointToDidMap;
} Dem_FreezeFrameClassType;

/*******************************************************************************
 ** Free frame record class                                                   **
 *******************************************************************************/
typedef struct STag_Dem_FreezeFrameRecordClassType {
  /* Freeze Frame record number */
  Dem_FreezeFrameNumberType FreezeFrameRecordNumber;

  /* Freeze Frame data should be updated or no */
  uint8 RecordUpdate;

  /* Defines the trigger to store the FreezeFrameRecord */
  uint8 RecordTriger;
} Dem_FreezeFrameRecordClassType;

/*******************************************************************************
 ** Extended data record class                                                **
 *******************************************************************************/
typedef struct STag_Dem_ExtendedDataRecordClassType {
  /* Extended Data record number */
  Dem_ExtendedDataNumberType ExtendedDataRecordNumber;

  Dem_SizeOfExtendedDataRecordClassType size;

  /* Defines the trigger to store the ExtendedDataRecord */
  uint8 RecordTriger;

  /* Extended data should be updated or no */
  uint8 RecordUpdate;

  /* No of data elements */
  Dem_NumOfDataElementClassType NumOfDataElementClass;

  /* An array of the Data Element */
  uint16 PointToDataElementMap;
} Dem_ExtendedDataRecordClassType;

/*******************************************************************************
 ** Extended data class                                                       **
 *******************************************************************************/
/* No of data elements */
typedef struct STag_Dem_ExtendedDataClassType {
  Dem_SizeOfExtendedDataClassType size;
  Dem_NumOfExtendedDataRecordClassType NumOfEDRecordClass;
  uint16 PointToEDRecordMap;
} Dem_ExtendedDataClassType;


/*******************************************************************************
 ** Dem General OBD                                                           **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT !=  DEM_OBD_NO_OBD_SUPPORT)
typedef struct STag_Dem_GeneralOBDInfo
{


  /* Pointer to DemOBDDrivingCycleRef in data element array */
  P2CONST(Dem_OperationCycleType, AUTOMATIC, DEM_CONST)
  pOBDDrivingCycleRef;

  /* Pointer to DemOBDInputAcceleratorPaddleInformation in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputAcceleratorPaddleInformation;

  /* Pointer to DemOBDInputAmbientPressure in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputAmbientPressure;

  /* Pointer to DemOBDInputAmbientTemperature in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputAmbientTemperature;

  /* Pointer to DemOBDInputDistanceInformation in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputDistanceInformation;

  /* Pointer to DemOBDInputEngineSpeed in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputEngineSpeed;

  /* Pointer to DemOBDInputEngineTemperature in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputEngineTemperature;

  /* Pointer to DemOBDInputProgrammingEvent in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputProgrammingEvent;

  /* Pointer to DemOBDInputVehicleSpeed in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDInputVehicleSpeed;

  /* Pointer to DemOBDPFCCycleRef in data element array */
  P2CONST(Dem_OperationCycleType, AUTOMATIC, DEM_CONST)
  pOBDPFCCycleRef;

  /* Pointer to DemOBDTimeSinceEngineStart in data element array */
  P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  pOBDTimeSinceEngineStart;

  /* Pointer to DemOBDWarmUpCycleRef in data element array */
  P2CONST(Dem_OperationCycleType, AUTOMATIC, DEM_CONST)
  pOBDWarmUpCycleRef;

  /* Pointer to DemOBDIgnitionCycleRef in data element array */
  P2CONST(Dem_OperationCycleType, AUTOMATIC, DEM_CONST)
  pOBDIgnitionCycleRef;
}Dem_GeneralOBDInfo;
#endif

/*******************************************************************************
 **   Dem RatioId                                                             **
 *******************************************************************************/

#if (DEM_OBD_SUPPORT !=  DEM_OBD_NO_OBD_SUPPORT)
typedef struct STag_Dem_RatioIdInfo
{
  /* DemDiagnosticEventRef */
  Dem_EventIdType rid_EventId;

  /* @Trace: SWS_Dem_00715
   * The Dem module shall provide configuration parameter DemIUMPRDenGroup to
   * offer several conditions to be applied to the denominator per RatioId.*/

  /* IUMPR Group assigned to the Ratio id */
  uint8 ucIUMPRGroup;

  /* @Trace: SWS_Dem_00361
   * The Dem module shall provide the configuration parameter DemRatioKind,
   * to indicate per RatioId if the numerator is calculated based on the TESTED-
   * status or the API call.*/
  /* DemRatioIdType */
  uint8 ucRatioIdType;

  /* Primary DemFunctionIdRef */
  #if ((DEM_FIM_INTEGRATED == STD_ON) && (DEM_MAX_NUMBER_OF_FID_REF > DEM_ZERO))
  uint8 aaPrimaryFid[DEM_MAX_NUMBER_OF_FID_REF];

  /* Number configured FID in DemFunctionIdRef */
  uint16 NumOfPrimaryFid; 
  #endif

  /* Ratio Id */
  uint16 ucRatioId;

  /* Dem IUMPR Den Group*/
  uint8 ucIUMPRDenGroup;

}Dem_RatioIdInfo;
#endif

/*******************************************************************************
 ** OBD freeze frame class                                                    **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
typedef struct STag_Dem_PidClassType
{
  /* Freeze Frame is configured for Did */
  Dem_PidIdentifierType PidIdentifier;

  /* Size of all DataElements in bytes */
  Dem_SizeOfPidClassType size;

  /* No of data elements */
  Dem_NumOfPidDataElementType NumOfPidDataElements;

  /* An array of the Data Element */
  uint16 PointToDataElementMap;
}Dem_PidClassType;

typedef struct STag_Dem_OBDClassType
{
  /* No of data elements */
  Dem_NumOfPidClassType NumOfPidClass;

  /* Size of all PidClass in bytes */
  Dem_SizeOfOBDFreezeFrameDataType size;

  /* An array of the Data Element */
  CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) PidClass;
}Dem_OBDClassType;
#endif


/*******************************************************************************
 ** J1939 freeze frame class                                                  **
 *******************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)
typedef struct STag_Dem_SPNClassType
{
  /* J1939 Freeze Frame is configured for Spn */
  Dem_SpnIdentifierType SpnIdentifier;

  /* Size of all DataElements in bytes */
  Dem_SizeOfSpnClassType size;

  /* No of data elements */
  Dem_NumOfSpnDataElementType NumOfSpnDataElements;
  
  /* Size of all DataElements in bytes */
  uint16 PointToDataElementMap;

}Dem_SPNClassType;

typedef struct STag_Dem_J1939FreezeFrameClassType
{

  /* Size of all SPNClass in bytes */
  Dem_SizeOfJ1939FreezeFrameDataType size;
  /* No of data elements */
  Dem_NumOfSpnClassType NumOfSpnClass;

  /* An array of the SPN */
  uint16 PointToSpnMap;
}Dem_J1939FreezeFrameClassType;
#endif

/*******************************************************************************
 ** Event related data                                                        **
 *******************************************************************************/
/* @Trace: Dem_SUD_DATATYPE_00001 */
typedef struct STag_Dem_EventRelatedData {
  Dem_EventIdType EventIdRef;

  /* Pointer to Event Data changed function*/
  /* Fixed : EventId is removed*/
  P2FUNC(Std_ReturnType, DEM_APPL_CODE, CallbackEventDataChanged)(void);

  /* Freeze Frame Pre storage is supported or not */
  boolean FFPreStorageSupported;

  Dem_NumOfRecordNumberType MaxNumOfFreezeFrameRecords;

  /* Index of Freeze Frame Record Class that is configured. */
  uint16 FFRecordClassIndex;

  /* An array of the DID */
  Dem_NumOfFreezeFrameClassType FFClassPos;

  Dem_NumOfExtendedDataClassType EDClassPos;

  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  Dem_NumOfFreezeFrameClassType WWHOBDFFClassPos;

  CONSTP2CONST(Dem_OBDClassType, AUTOMATIC, DEM_CONST) OBDClassPos;
  #endif

  #if (DEM_J1939_SUPPORT == STD_ON)
  Dem_NumOfJ1939FreezeFrameClassType  J1939FFClassPos;
  Dem_NumOfJ1939FreezeFrameClassType  J1939EXFFClassPos;
  
  #endif
} Dem_EventRelatedDataType;


/*******************************************************************************
 ** Component parameter                                                       **
 *******************************************************************************/
typedef struct STag_Dem_ComponentType
{
    /* Dem Component Failed Callback Fnc */
  P2FUNC(Std_ReturnType, DEM_APPL_CODE, pFailedCallbackFnc)
  (Dem_ComponentIdType ComponentId);

    /* Dem Component Failed Callback Use Port*/
    boolean blDemCompFailedCBUsePort;
    /* Dem Component Id */
    Dem_ComponentIdType usDemComponentId;
    /* Dem Component Ignores Priority */
    boolean blDemCompIgrPrio;
    /*Dem Immediate Child Component */
    uint8 usDemChildIdx;
    /* Number of dem child*/
    uint8 usNumberOfDemChild;

  /*Dem Parent Component Idx*/
  uint8 usDemParentCompIdx;
  /* Number of dem parent Component*/
  uint8 usNumberOfDemParentComp;

  /*Dem Dependent Component Idx */
  uint8 usDemDependentCompIdx;
  /* Number of dem dependent Component*/
  uint8 usNumberOfDemDependentComp;

  /*Dem EventId Idx*/
  uint8 usDemEventIdIndex;

  /* Number of dem event Id Index*/
  uint8 usNumberOfDemEventId;
}Dem_ComponentType;


/*******************************************************************************
 ** Event parameter                                                           **
 *******************************************************************************/
/* @Trace: Dem_SUD_DATATYPE_00002 */
typedef struct STag_Dem_EventParameterType 
{
  /* Dem Causality Delay Time */
  uint32 usDemCausalityDelayTime; 

  /* Dem Component Priority*/
  uint8 usDemComponentPriority; 

  /* Dem Component Index*/
  Dem_ComponentIdType usDemComponentIdx;

  /* Dem Event Available*/
  boolean blDemEventAvailable;

  /* Dem Event Confirmation Threshold*/
  uint8 usDemEventConfirmationThreshold; 
  /* Dem Event Failure Cycle Counter Threshold Adaptable */
  boolean blDemEventFailureCycleCounterThresholdAdaptable;

  /* Dem Event Recoverable In Same Operation Cycle */
  boolean blEventRecoverableInSameOperationCycle;

  Dem_NumOfEventRelatedDataType e_PointToData;
  /*CallBacks*/
  /* Function pointer to ClearEventAllowed */
  P2FUNC(Std_ReturnType, DEM_APPL_CODE, pDemClearEventAllowed)
  (P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) pAllowed);

  /* Dem Clear Event Allowed Behavior */
  uint8 usDemClearEventAllowedBehavior;

  /* Function Pointer to Init Monitor For Event*/
  P2FUNC(Std_ReturnType, DEM_APPL_CODE, pDemInitMonitorForEvent)
  (Dem_InitMonitorReasonType InitMonitorReason);

  /* Operation Cycle Reference */
  uint8 e_OperationCycleId;

  /* Aging Cycle Reference*/
  uint8 e_AgingCycleId;

  /* Pointer to Combined DTC array */
  uint16 e_PointToDTC;

  /* Number of Event Status functions for the event */
  uint8 ddNumOfEventStatusFct;
  /* Index of array of indexes of event status functions */
  Dem_NumOfEvtStatFctsType PointToEventStatusFncMap;

  /* Bit 0  : DEM_EVENT_KIND_BSW                      (0)
   *          DEM_EVENT_KIND_SWC                      (1)
   *
   * Bit 1-2: DEM_DEBOUNCE_COUNTER_BASED              (0x01U)
   *          DEM_DEBOUNCE_TIME_BASED                 (0x02U)
   *          DEM_DEBOUNCE_MONITOR_BASED              (0x03U)
   *          DEM_DEBOUNCE_NO_DEBOUNCE_BASED          (0x00U)
   *
   * Bit 3  : DEM_EVENT_SIGNIFICANCE_FAULT            (0x01U)
   *          DEM_EVENT_SIGNIFICANCE_OCCURRENCE       (0x00U)
   *
   * Bit 4  : AgingAllowed                            TRUE/FALSE
   *
   * Bit 5  : StorageTestFailed                       TRUE/FALSE
   *
   * Bit 6  : Reset WIR                               TRUE/FALSE
   */   
  uint8 ParamFieldsA;

  /* Index to debounce array */
  Dem_NumOfDebounceType ucIndexOfDebounceAry;

  /*Aging counter Threshold*/
  uint8 ucAgingCycleCounterThreshold;

  /*Aging counter Threshold for TFSLC*/
  uint8 ucAgingCycleCounterThresholdForTFSLC;

  /* Event destinations */
  #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
  uint16 aaEventDestination;

  /* Index Event Destination*/
  uint8 ucEventMemDstIdx;

  /* Number Of Destination select*/
  uint8 ucNumOfDestSelected;
  #endif

  /* Event failure Cycle Counter Threshold */
  uint8 ucEventFailureThreshold;

  /* @IF_REQ :   #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO) */
  /* Total number of Indicators of the Event */
  uint8 ucNumberofIndicator;
  /* Array of indices of the Indicator ID array*/
  Dem_NumOfIndicatorAttributeType e_PointToIndicator;
  /* #endif */

  /* Event priority */
  Dem_EventPriorityType ucEventPriority;

  /* Number of Monitor Status*/
  uint8 ucNumberofMonitorStatus;

  /* Point To Monitor Status*/
  uint16 e_PointToMonitorStatus;


  #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
  /* Number of EnableConditions */
  uint8 ucNumOfEnableCondition;
  /* Index to array of EnableCondition */
  uint16 PointToEnableConditionMap;
  #endif

  #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
  /* Number of StorageConditions */
  uint8 ucNumOfStorageCondition;
  /* Index to array of StorageCondition */
  uint16 PointToStorageConditionMap;
  #endif


  
  #if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  uint16 usRatioIdCount;
  uint8 aaRatioIndex[DEM_NUMBER_OF_RATIO_INFO];
  #endif
  /* @Trace: Dem_SUD_MACRO_010 */
  #if (DEM_PTO_SUPPORT == STD_ON)
  /* PTO is Enabled or not */
  boolean blPTOStatus;
  #endif  

  /* Event OBD Readiness Group*/
  uint32 ulEventOBDReadinessGroup;  
  uint16 usObdDtc;

  #endif
}Dem_EventParameterType;

typedef struct STag_Dem_EventMonitorDataType {
  /* Monitor Data 0 */
  uint32 usMonitorData0;
  /* Monitor Data 1 */
  uint32 usMonitorData1;
} Dem_EventMonitorDataType;
/*******************************************************************************
 ** non-volatile data                                                         **
 *******************************************************************************/
  
  
typedef struct STag_Dem_DTCFilterStateType {
  Dem_DTCOriginType dfs_DTCOrigin;               
  boolean dfs_FilterForFDC;
  Dem_DTCSeverityType dfs_DTCKind;               
  Dem_DTCSeverityType dfs_DTCSeverityMask;     
  boolean dfs_FilterWithSeverity;
  Dem_UdsStatusByteType dfs_DTCStatusMask;
  Dem_DTCFormatType dfs_DTCFormat;
  
  uint8 dfs_JobAction;
  uint16  dfs_NumOfFilteredDTC;
  Dem_EventIdType  dfs_NextEvent;
  boolean dfs_resultGetDtcFilter;
  boolean dfs_isLockService[DEM_MAXIMUM_SETDTCFILTER_SID_LOCKID];

  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  /* Trace: DEM_19792_1A_06 */
  uint8 dfs_ExtendedDataRecord;
  /* Trace: DEM_19792_56_07 */
  Dem_EventOBDReadinessGroupType dfs_ReadinessGroupNumber;
  #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

} Dem_DTCFilterStateType;


typedef uint8 word_t;
enum
{
  NUM_OF_WORD_BITS = sizeof(word_t) * 8
};

/***********************************************************************************
 *                             CAUTION!!!!!                                        *
 *                                                                                 *
 * If the structures for event memory, the structure alignment shall be considered *
 *                                                                                 *
 ***********************************************************************************/

typedef struct STag_Dem_OccurenceTimeDataType
{
  Dem_DTCType DTCOccurenceTime[DEM_MAX_DTC_REQEST_TYPE];
}Dem_OccurenceTimeDataType;

/*******************************************************************************
 ** PreStore Buffer of RAM                                                     **
 *******************************************************************************/

typedef struct STag_Dem_PrestoreBufferType {
  /* Event Id which failure */
  Dem_EventIdType EventIdRef;

  #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
  uint8 data[DEM_SIZE_OF_PRESTORED_FF];
  #endif
  
} Dem_PrestoreBufferType;

#if ((DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO) && \
     (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO))
typedef struct STag_Dem_DataPrestoredType
{
  uint8 data[DEM_SIZE_OF_PRESTORED_FF];
}Dem_DataPrestoredType;
#endif

typedef struct STag_Dem_EventStatusNvRamDataType 
{ 
  /* ISO14229 - 189 page
   * Record of the first/most recent failed DTC shall be independent of the
   * aging process of confirmed DTCs. As  mentioned  above,  first/most  recent
   * failed  DTC  information  shall  be  cleared  upon  a  successful
   * ClearDiagnosticInformation  request  from  the  client */
  #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
  /* the variable for DTC Request by occurrence time */
  Dem_OccurenceTimeDataType DTCOccurenceTimeData[DEM_NUMBER_OF_DEM_CLIENT];
  #endif

  #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
       (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
  /* Trace: DEM_OBD_09_20 */
  uint16 IumprDenominator[DEM_NUMBER_OF_RATIO_INFO];
  uint16 IumprNumerator[DEM_NUMBER_OF_RATIO_INFO];
  uint16 IumprMinimumRatioIDPerGroup[DEM_IUMPR_MAX];

  uint16 IgnitionCylCnt;
  uint16 GeneralDenCnt;

  #endif

  #if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  /* Trace: DEM_OBD_01_08 */  
  uint16 DataOfPID21;
  uint16 DataOfPID4D;
  uint16 DataOfPID4E;
  uint16 DataOfPID31;
  uint16 WWHOBDConMICont;
  uint16 WWHOBDB1Counter;
  #endif

  /* @Trace: SRS_Diag_04124
   */
  /* @Trace: SWS_Dem_00674
   * If the configuration parameter DemDebounceCounterStorage
   * is set to True, the Dem module shall store the current value of the
   * internal debounce counter non-volatile (refer to [SWS_Dem_00341]).
   * */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
  sint16 InternalDebouneCnt[DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER];
  #endif

  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  uint8 ObdMemoryId;
  #endif
  /* @IF_REQ : if DTCAvailiableMask is 0xFF , Bit array is not good */
  /* @Trace: SRS_Diag_04067
   */
  /* @Trace: SWS_Dem_00525
   * If the configuration parameter DemStatusBitStorageTestFailed is set to
   * True, the Dem module shall retain the information for UDS DTC status bit 0
   * (TestFailed) over power cycles (non-volatile).*/
  #if (DEM_UDS_STATUS_TF_ALLEVENTSTATUS > DEM_ZERO)
  uint8 TF_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  /* @Trace: SRS_Diag_04067
   */
  /* @Trace: SWS_Dem_00389
   * Note: The information for UDS DTC status bit 1
   * (TestFailedThisOperationCycle) is non-volatile, if the PendingDTC bit is
   * used (refer to [SWS_Dem_00006]) or if the Dem module supports operation
   * cycles over power cycles (refer to DemOperationCycleStatusStorage). */
  #if (DEM_UDS_STATUS_TFTOC_ALLEVENTSTATUS > DEM_ZERO)
  uint8 TFTOC_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  /* @Trace: SRS_Diag_04141
   */
  /* @Trace: SWS_Dem_01183
   * The information for UDS DTC status bit 2 (PendingDTC) needs
   * to be stored non-volatile*/
  #if (DEM_UDS_STATUS_PDTC_ALLEVENTSTATUS > DEM_ZERO)
  uint8 PDTC_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  #if (DEM_UDS_STATUS_CDTC_ALLEVENTSTATUS > DEM_ZERO)
  uint8 CDTC_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  /* @Trace: SRS_Diag_04067
   */
  /* @Trace: SWS_Dem_00392
   * Note: The information for UDS DTC status bit 4
   * (TestNotCompletedSinceLastClear) is non-volatile. */
  #if (DEM_UDS_STATUS_TNCSLC_ALLEVENTSTATUS > DEM_ZERO)
  uint8 TNCSLC_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  /* @Trace: SRS_Diag_04067
   */
  /* @Trace: SWS_Dem_00393
   * 1. Note: The information for UDS DTC status bit 4
   * (TestNotCompletedSinceLastClear) is non-volatile.
   * 2. PDTC is stored only in the event memory entry and
   * DemStatusBitHandlingTestFailedSinceLastClear is normal */
  #if (DEM_UDS_STATUS_TFSLC_ALLEVENTSTATUS > DEM_ZERO)
  uint8 TFSLC_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif  

  /* @Trace: SRS_Diag_04067
   */
  /* @Trace: SWS_Dem_00394
   * Note: The information for UDS DTC status bit 1
   * (TestNotCompleteThisOperationCycle) is non-volatile, if the PendingDTC bit
   * is used (refer to [SWS_Dem_00006]) or if the Dem module supports operation
   * cycles over power cycles (refer to DemOperationCycleStatusStorage). */
  #if (DEM_UDS_STATUS_TNCTOC_ALLEVENTSTATUS > DEM_ZERO)
  uint8 TNCTOC_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  /* 2. if dispacement is not supported, WIR is stored only in the event
   * memory */
  #if (DEM_UDS_STATUS_WIR_ALLEVENTSTATUS > DEM_ZERO)
  uint8 WIR_BitArray[DEM_BITARRAY_BITNSLOTS(DEM_ONE + DEM_NUMBER_OF_EVENTS)];
  #endif

  /* @IF_REQ : healing and failure counter can be merged one variable */
  /* @Trace: Dem_SUD_MACRO_113 */
  #if (DEM_NUM_OF_HEALING_COUNTER > DEM_ZERO)
  uint8 IndicatorHealingCycleCounter[DEM_NUM_OF_HEALING_COUNTER];
  #endif
  /* @Trace: Dem_SUD_MACRO_111 */
  #if (DEM_NUM_OF_FAILURE_COUNTER > DEM_ZERO)
  uint8 IndicatorFailureCycleCounter[DEM_NUM_OF_FAILURE_COUNTER];
  #endif
  /* @Trace: Dem_SUD_MACRO_115 */
  #if (DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS > DEM_ZERO)
  uint8 AttributeStatus[DEM_BITARRAY_BITNSLOTS(
      DEM_ONE + DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS)];
  #endif

  #if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
  uint8  EventMemoryOverflow[DEM_MAX_NUMBER_MEMORY_SET]; /* 4 bits are used */
  #endif
  
  #if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  uint8 DtcClear;
  uint8 NumOfWUCSinceLC;  

    /* Trace: DEM_GEN_08*/  
  uint8 MilonFlag;
  uint8 PreMilonFlag;

    
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
   /* Trace: DEM_19792_06_13 */
  /* Store the value of Monitor Activity Denominator (MAD - General Denominator) */
  uint8 MonitorActivityDenominator[DEM_NUMBER_OF_RATIO_INFO];
  /* Store the value of Monitor Activity Numerator (MAN) */
  uint8 MonitorActivityNumerator[DEM_NUMBER_OF_RATIO_INFO];
  /* Store the value of Monitor Activity RATIO (MAR) */
  uint8 MonitorActivityRatio[DEM_NUMBER_OF_RATIO_INFO];  
  /* Store the indicator of Monitor Activity Denominator whether it is updated in one Operation Cycle*/
  uint8 MonitorActivityDenominatorNeedCountedCycleEnd[DEM_NUMBER_OF_RATIO_INFO];
  /* Store the indicator of Monitor Activity Numerator whether it is updated in one Operation Cycle*/
  uint8 MonitorActivityNumeratorNeedCountedCycleEnd[DEM_NUMBER_OF_RATIO_INFO];  
  #endif /* J19792 */
  boolean IumprUpdateFlagPerGroup[DEM_IUMPR_MAX];
  #endif
  #endif

  #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
  boolean EventMemoRyOverflowUserDefined[DEM_MAX_NUMBER_USER_DEFINED_MEMORY];
  #endif


  uint8 endOfStructure;
} Dem_EventStatusNvRamDataType;


typedef struct STag_Dem_GenericNvRamDataType 
{
  uint32 FootPrint;

  #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
  Dem_EventIdType EvIdPrestored[DEM_MAX_NUMBER_PRESTORED_FF];
  #endif

  uint8  EvMemVer[DEM_FOUR];
  #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)
  uint8 OperationCycleState[DEM_NUMBER_OPERATION_CYCLES];
  /* Trace: DEM_CYCLE_02 */
  uint8 OperationCycleQualifiedStt[DEM_NUMBER_OPERATION_CYCLES];  
  #endif

  #if ((DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO) && \
       (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO))
  Dem_DataPrestoredType DataPrestored[DEM_MAX_NUMBER_PRESTORED_FF];
  #endif

  uint8 endOfStructure;
} Dem_GenericNvRamDataType;


/*******************************************************************************
 ** Event memory                                                              **
 *******************************************************************************/

/* Note: Configuration dependancy
 * [1] data : DemFreeFrameClass or DemExtendedDataClass is configured 
 * [2] IndexOfFFRecords:  DemMaxNumberFreezeFrameRecords is greater than 0
 * 
 */
/* @Trace: Dem_SUD_DATATYPE_00005 */
typedef struct STag_Dem_EventMemory 
{
  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
  uint32 TimeStamp;
  #endif
  
  /* Event Id which failure */
  Dem_EventIdType EventIdRef;

  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  boolean PfcQualified;
  #endif

  #if (DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT == STD_ON)
  /* Event Status Byte */
  Dem_UdsStatusByteType EventStatuByte[DEM_MAX_NUM_EVENTS_PER_DTC];
  #endif

  /*
   1. The Dem module shall initialize the occurrence counter with
   the value  one if the related event is entered in the respective event
   memory

   DEM_PROCESS_OCCCTR_TF : If the configuration parameter
   DemOccurrenceCounterProcessing (refer to DemGeneral) is
   DEM_PROCESS_OCCCTR_TF, the Dem  module shall  increment the occurrence
   counter by one, triggered by each UDS DTC status bit 0 (TestFailed)
   transition from 0 to 1, if the related event is already stored in the event
   memory.

   DEM_PROCESS_OCCCTR_CDTC: If  the configuration  parameter
   DemOccurrenceCounterProcessing (refer to DemGeneral) is
   DEM_PROCESS_OCCCTR_CDTC, the Dem module shall increment the occurrence
   counter  by one, triggered by each UDS DTC status bit 0 (TestFailed)
   transition from 0 to 1, if the related event is already stored in the event
   memory and the UDS DTC Status bit 3 (ConfirmedDTC) is equal to 1 */
  Dem_EventOccurrenceType EventOccurrenceCounter;

  /* To clear the event in the event memory 
  @IF_REQ : if internal data element is mapped to the aging counter, 
   this variable is deplicated entry.data[n]*/

  /* @Trace: SRS_Diag_04068 SRS_Diag_04133 SRS_Diag_04178
   */
  /* @Trace: SWS_Dem_00019
   * The Dem module shall support at least an aging counter for each event
   * memory entry
   * */
  uint8 AgingCycleCounter;

  /* To set the confirmed bit
   * @IF_REQ : if internal data element is mapped to the healing counter, 
   * this variable is deplicated entry.data[n]*/
  #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
  uint8 FailureCycleCounter;
  #endif

  #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
  /* IndexOfFFRecords point to empty slot of ListOfRecordNumbers. 
   * @IF_REQ: It can be calculated based on the padding data of freeze frame
   * records */
  Dem_NumOfRecordNumberType IndexOfFFRecords;
  #endif

  /* 3. EXTENDED DATA */
  #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
  uint8 data[DEM_SIZE_OF_EVENT_DATA];
  #endif

  /* @Trace: SRS_Diag_04190
   */
  /* @Trace: SWS_Dem_00984
   * If the counter "Cycles since last failed" is mapped to an extended
   * data record (DemInternalDataElement set to DEM_CYCLES_SINCE_LAST_FAILED,
   * it shall be available per "event related data" record..
   * */
  /* 4.Cycles since last failed */
    #if (DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  uint8 cyclesSinLastFailedCounter;
  #endif

  /* @Trace: SRS_Diag_04074 SRS_Diag_04190
   */
  /* @Trace: SWS_Dem_00775
   * If the counter "Cycles since first failed" is
   * mapped to an extended data record (DemInternalDataElement set to
   * DEM_CYCLES_SINCE_FIRST_FAILED), it shall be available per "event related
   * data" record.
   * */
  /* 5. Cyles since first failed */
    #if (DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  uint8 cyclesSinFirstFailedCounter;
  #endif

  /* @Trace: SRS_Diag_04068 SRS_Diag_04189 SRS_Diag_04190
   */
  /* @Trace: SWS_Dem_00779
   * If the counter "Failed cycles" is mapped to an extended data record
   * (DemInternalDataElement set to DEM_FAILED_CYCLES), it shall be
   * available per "event related data" record.
   * */
  /* 6. Failed cycles*/
    #if (DEM_INTERNAL_DATA_FAILED_CYCLES == STD_ON)
  uint8 failedCyclesCounter;
  #endif

  uint8 endOfStructure;
} Dem_EventMemoryEntryType;

/* @IF_REQ */
/*
typedef struct STag_Dem_ChronoEventMemoryType
{
  Dem_EventIdType EventId;
  Dem_NumOfEventMemoryEntryType ref;
} Dem_ChronoEventMemoryType;
*/

/*******************************************************************************
 ** Dem Internal Data Element                                                 **
 *******************************************************************************/
#if ((DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) || \
     (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON))
typedef struct Stag_Dem_InternalDataElementType {
  /* Maximum FDC during current operation cycle */
  /* @Trace: SRS_Diag_04125
   */
  /* @Trace: SWS_Dem_00788
   * If the maximum FDC during current operation cycle
   * is mapped to an extended data record (DemInternalDataElement set to
   * DEM_MAX_FDC_DURING_CURRENT_CYCLE), it shall be available for all events
   * referencing a UDS DTC. */
  #if (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
  sint8 maxFdcCurrentCycle;
  #endif

  /* Maximum FDC since last clear */
  /* @Trace: SRS_Diag_04125
   */
  /* @Trace: SWS_Dem_00792
   * If the maximum FDC since last clear is mapped
   * to an extended data record (DemInternalDataElement set to
   * DEM_MAX_FDC_SINCE_LAST_CLEAR), it shall be available for all events
   * referencing a UDS DTC. */
  #if (DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  sint8 maxFdcLastClear;
  #endif

} Dem_InternalDataElementType;
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/*Trace: Dem_SUD_MACRO_075 */
#if (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO)
typedef struct STag_Dem_OBDFreezeFrameDataType
{
  /* Although structure of PIDData has logical ploblem, it is optimized about
   * capicity of storage for PID.*/
  /* PID data element: Size and data */
/* @Trace: Dem_SUD_MACRO_044 */
  uint8 PIDData[DEM_MAX_NUMBER_OF_PID_DATAELEMENT]
                [DEM_MAX_SIZE_OF_PID_DATAELEMENT];
}Dem_OBDFreezeFrameDataType;
#endif

#endif


typedef struct STag_Dem_ClearDtcStateType 
{
  uint8 cds_State; 
  Std_ReturnType cds_Result;
  boolean cds_RequestCancel;

  Dem_EventIdType cds_EventIdRef;
  Dem_EventIdType cds_StartEventIdRef;  
  Dem_ClientIdType cds_ClientIdRef;


  uint32 cds_DTC;
  Dem_DTCFormatType cds_DTCFormat;
  Dem_DTCOriginType cds_DTCOrigin;
  Dem_NumOfEventMemoryEntryType cds_MemLocation;

  uint8 cds_User;
  #if (DEM_J1939_SUPPORT == STD_ON)
  #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
  Dem_J1939DcmSetClearFilterType cds_DTCTypeFilter;  
  #endif  
  #endif
} Dem_ClearDtcStateType;

typedef struct STag_Dem_SelectDtcStateType
{
  /* DTC which is selected */
  uint32 selectedDTC;
  /* DTCFormat which is selected */
  Dem_DTCFormatType selectedDTCFormat;
  /* DTCOrigin which is selected */
  Dem_DTCOriginType selectedDTCOrigin;
  /* service retention lock*/
  boolean isLockService[DEM_MAXIMUM_CLEARDTC_SID_LOCKID];
  /* Information of DTC */
  uint8 resultSelectDTC;

} Dem_SelectDtcStateType;

typedef struct STag_Dem_SelectFreezeFrameDataType
{
  /* Record number which is selected */
  uint8 selectRecordNumber;
  /* Information of Freeze Frame data */
  uint8 resultSelectFreezeFrameData;

} Dem_SelectFreezeFrameDataStateType;

typedef struct STag_Dem_SelectExtendedDataRecordType
{
  /* Extended Data Number which is selected */
  uint8 selectExtendedDataNumber;
  /* Information of Extended data record */
  uint8 resultSelectExtendedDataRecord;

  /* Point to the next extendedDataRecordNumber to read
   * if the selectExtendedDataNumber is 0xFF */
  Dem_NumOfExtendedDataRecordClassType nextPointToEDRecordMap;

  /* Number of all extended data records selected 
   * if the selectExtendedDataNumber is 0xFF */ 
  Dem_NumOfExtendedDataRecordClassType maxNumOfEDRecordClass;
} Dem_SelectExtendedDataRecordType;

typedef struct STag_Dem_EvMemTriggerType
{
  boolean readNvBlocksTrigger;
  boolean writeNvBlocksTrigger;
  boolean waitNvBlocksJobFinishTrigger; 
  uint8   writeNvBlocksEndModeTrigger;
  Std_ReturnType nvmResult;
} Dem_EvMemTriggerType;

/*******************************************************************************
 ** Dem DTC Attributes Type                                                   **
 *******************************************************************************/
typedef struct STag_Dem_DTCAttributesType
{
  /* Is Primary Memory configured in DemDTCAttributes */
  uint8 ucPrimaryMemory;

  /* Is Mirror Memory configured in DemDTCAttributes */
  uint8 ucMirrorMemory;

} DemDTCAttributesType;


/* @IF_REQ
typedef struct STag_Dem_OperationCycleAsyncStateType
{
  Dem_OperationCycleStateType ocs_State;
  boolean ocs_Trigger;
} Dem_OperationCycleAyncStateType;
*/

/*******************************************************************************
 **                      extern declarations                                  **
 *******************************************************************************/

/*******************************************************************************
 ** Definition and configuration of Event Parameter Structure                 **
 *******************************************************************************/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Dem_SUD_MACRO_096 */
#if (DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
/* Array Dem_PrimaryNvmBlockId */
/* @Trace: DEM_SUD_DATATYPE_002 */
extern CONST(NvM_BlockIdType, DEM_CONST)
  Dem_PrimaryEventMemoryNvmBlockId[DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID];
#endif
/* @Trace: Dem_SUD_MACRO_095 */
/* @Trace: DEM_SUD_DATATYPE_002 */
#if (DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
/* Array Dem_PrimaryNvmBlockId */
extern CONST(NvM_BlockIdType, DEM_CONST)
  Dem_PermanentEventMemoryNvmBlockId
    [DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID];
#endif

#if (DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
/* Array Dem_UserDefinedNvmBlockId */
/* @Trace: DEM_SUD_DATATYPE_002 */
extern CONST(NvM_BlockIdType, DEM_CONST)
  Dem_UserDefinedEventMemoryNvmBlockId
    [DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID];
#endif

#if (DEM_NUM_OF_MIRROR_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
/* Array Dem_MirrorNvmBlockId */
/* @Trace: DEM_SUD_DATATYPE_002 */
extern CONST(NvM_BlockIdType, DEM_CONST)
  Dem_MirrorEventMemoryNvmBlockId[DEM_NUM_OF_MIRROR_EVENTMEMORY_NVBLOCKID];
#endif

#if (DEM_NUMBER_OPERATION_CYCLES > DEM_ZERO)
extern CONST(Dem_OperationCycleName, DEM_CONST)
  Dem_GstOperationCycleName[DEM_NUMBER_OPERATION_CYCLES];
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
 ** Definition and configuration of Combined Dtc Structure                    **
 *******************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_CombinedDtcType, DEM_CONST)
  Dem_GaaCombinedDtc[DEM_MAX_NUMBER_OF_DTC];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_EventIdType, DEM_CONST)
  Dem_ListOfCombinedEvents[DEM_MAX_LISTOFCOMBINEDEVENTS];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_PrimaryMemoryType, DEM_CONST)
  Dem_GaaDemPrimaryMemory[DEM_MAX_NUMBER_PRIMARY_MEMORY];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_UserDefinedMemoryType, DEM_CONST)
  Dem_GaaDemUserDefinedMemory[DEM_MAX_NUMBER_USER_DEFINED_MEMORY];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
/*******************************************************************************
 ** Array of PIDs                                                             **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT !=  DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dem_PidClassType, DEM_CONST)
  Dem_GaaPid[DEM_MAX_NUMBER_OF_PID_RECDS];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif
#endif
/*******************************************************************************
 ** Array of PIDs                                                             **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT !=  DEM_OBD_NO_OBD_SUPPORT)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#if(DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO)
extern CONST(Dem_PidDataElementType, DEM_CONST)
  Dem_GaaDataElementRefAry[DEM_MAX_NUMBER_OF_PID_DATAELEMENT];
#endif
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
 ** Dem Component information                                                 **
 *******************************************************************************/
#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_ComponentType, DEM_CONST)
  Dem_Components[DEM_NUMBER_OF_DEM_COMPONENT];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
 ** List of Dem child component                                               **
 *******************************************************************************/
/* @Trace: Dem_SUD_MACRO_157 */
#if (DEM_MAX_LISTOFCHILDCOMPONENT > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_ComponentIdType, DEM_CONST)
  Dem_ListOfChildComponent[DEM_MAX_LISTOFCHILDCOMPONENT];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
 ** Operation cycle information                                               **
 *******************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(Dem_OperationCycleType, DEM_CONST)
    Dem_GaaOperationCycleIdsList[DEM_NUMBER_OPERATION_CYCLES];

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
 ** Enable Condition information                                              **
 *******************************************************************************/
/* @Trace: Dem_SUD_MACRO_080 */
#if (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO)
#define DEM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
extern CONST(boolean, DEM_CONST)
    Dem_GaaEnableCondition[DEM_NUMBER_ENABLE_CONDITION];

#define DEM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"
#endif

/*******************************************************************************
 ** Storage Condition information                                             **
 *******************************************************************************/
#if (DEM_NUMBER_STORAGE_CONDITION > DEM_ZERO)
#define DEM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"

extern CONST(Dem_StorageConditionType, DEM_CONST)
    Dem_GaaStorageCondition[DEM_NUMBER_STORAGE_CONDITION];

#define DEM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"
#endif
/*******************************************************************************
 ** Pre Debounce Counter information                                          **
 *******************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
extern CONST(Dem_PreDebounceCounterType, DEM_CONST) 
  Dem_GaaPreDebounceCounter[DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER];
#endif

/*******************************************************************************
 ** Pre Debounce Monitor Internal information                                 **
 *******************************************************************************/
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO)
extern CONST(Dem_PreDebounceMonitorInternalType, DEM_CONST)
Dem_GaaPreDebounceMonitorInternal[DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL];
#endif

/*******************************************************************************
 ** Pre Debounce Time information                                             **
 *******************************************************************************/
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
extern CONST(Dem_PreDebounceTimeBasedType, DEM_CONST)
    Dem_GaaPreDebounceTimeBased [DEM_NUMBER_OF_PRE_DEBOUNCE_TIME];
#endif

/*******************************************************************************
 ** List of supported IndicatorIds                                             **
 *******************************************************************************/
#if(DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
extern CONST(Dem_IndicatorAttributeType, DEM_CONST)
  Dem_GaaIndicatorList[DEM_NUMBER_OF_INDICATORS];
#endif

/*******************************************************************************
 ** General OBD Information                                                   **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT !=  DEM_OBD_NO_OBD_SUPPORT)
extern CONST(Dem_GeneralOBDInfo, DEM_CONST)
  Dem_GstGeneralOBDInfo[DEM_NUM_OF_GST_GENERAL_OBD_INFO];
#endif

/*******************************************************************************
 ** Array of ratio Id Info                                                    **
 *******************************************************************************/
#if(DEM_NUMBER_OF_DTRS > DEM_ZERO)
extern CONST(Dem_DTRType, DEM_CONST)
  Dem_GaaDtrInfo[DEM_NUMBER_OF_DTRS];
#endif

/*******************************************************************************
 ** Array of ratio Id Info                                                    **
 *******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
    (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
extern CONST(Dem_RatioIdInfo, DEM_CONST)
  Dem_GaaRatioIdInfo[DEM_NUMBER_OF_RATIO_INFO];
#endif

/*******************************************************************************
 ** Array of Function Pointers to Event Status Changed Function               **
 *******************************************************************************/
extern CONST(Dem_EvtStatusChangedFctPtrType, DEM_CONST) 
  Dem_ListOfEvtStatusChangedFctPtr[DEM_NUM_OF_EVT_STATUS_CHANGED_FCTPTR];

/*******************************************************************************
 ** Array Of Operation Cycle Events                                           **
 *******************************************************************************/
extern CONST(Dem_EventIdType, DEM_CONST)
    Dem_ListOfOperationCycleEvents[DEM_NUM_OF_OPERATION_CYCLE_EVENTS];

/*******************************************************************************
 ** Array of Function Pointers to Monitor Status Changed Function             **
 *******************************************************************************/
extern CONST(Dem_MonitorStatusChangedFctPtrType, DEM_CONST)
  Dem_GaaMonitorStatusChangedFctPtr
    [DEM_NUMBER_OF_MONITOR_STATUS_CHANGED_FCT_PTR_TYPE];
/*******************************************************************************
 ** Array of Function Pointers to Event Status Changed Function               **
 *******************************************************************************/
extern CONST(Dem_DtcStatusChangedFctPtrType, DEM_CONST)
  Dem_GaaDtcStatusChangedFctPtr[DEM_NUMBER_OF_DTC_STATUS_CHANGED_FCT_PTR];

/*******************************************************************************
 ** Array of group of DTC's
 *******************************************************************************/
#if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
extern CONST(Dem_DTCGroupType, DEM_CONST) Dem_GaaGroupDTC[DEM_MAX_NUM_GRP_DTC];
#endif

/********************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
extern CONST(Dem_ExtendedDataRecordClassType, DEM_CONST)
  Dem_ExtendedDataRecordClass[DEM_NUM_OF_EXTENDEDDATARECORDCLASS];

extern CONST(Dem_ExtendedDataClassType, DEM_CONST)
  Dem_ExtendedDataClass[DEM_NUM_OF_EXTENDEDDATACLASS];
#endif

/********************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
extern CONST(Dem_NumOfExtendedDataRecordClassType, DEM_CONST)
  Dem_ListOfEDRecordClassIndex[DEM_MAX_LISTOFEDRECORDCLASSINDEX];
#endif

#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern CONST(Dem_FreezeFrameRecordClassType, DEM_CONST)
  Dem_FreezeFrameRecordClass[DEM_NUM_OF_FRREZEFRAMERECORDCLASS];
extern CONST(Dem_FreezeFrameClassType, DEM_CONST)
  Dem_FreezeFrameClass[DEM_NUM_OF_FREEZEFRAMECLASS];
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
#if (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO)
extern CONST(Dem_J1939FreezeFrameClassType, DEM_CONST)
  Dem_J1939FreezeFrameClass[DEM_NUM_OF_J1939FREEZEFRAMECLASS];
#endif
#endif

/********************************************************************/
#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern CONST(Dem_EventRelatedDataType, DEM_CONST)
  Dem_EventRelatedData[DEM_NUM_OF_EVENTRELATEDDATA];
#endif

/*extern CONST(uint8, DEM_CONST) Dem_ListOfEnableConditionGroupId[];*/
/* @Trace: SRS_Diag_04061 SRS_Diag_04063
 */
extern CONST(Dem_EventParameterType, DEM_CONST) Dem_Event[DEM_NUMBER_OF_EVENTS];


/********************************************************************/
/* @Trace: Dem_SUD_MACRO_090 */
#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern CONST(Dem_DataElementClassType, DEM_CONST)
  Dem_DataElementClass[DEM_NUM_OF_DATAELEMENTCLASS];
#endif

/********************************************************************/
#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern CONST(Dem_NumOfDataElementClassType, DEM_CONST) 
  Dem_ListOfDataElementClassIndex[DEM_MAX_LISTOFDATAELEMENTCLASSINDEX];
#endif

/********************************************************************/
#if (DEM_MAX_NUMBER_MEMORY_SET > DEM_ZERO)
extern CONST(Dem_MemorySetType, DEM_CONST)
  Dem_GaaDemMemorySet[DEM_MAX_NUMBER_MEMORY_SET];
#endif

/********************************************************************/
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
extern CONST(Dem_ClientType, DEM_CONST) Dem_Client[DEM_NUMBER_OF_DEM_CLIENT];
#endif

/********************************************************************/
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern CONST(Dem_DidClassType, DEM_CONST) Dem_DidClass[DEM_NUM_OF_DIDCLASS];
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
/* @Trace: Dem_SUD_MACRO_098 */
#if (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO)
extern CONST(Dem_SPNClassType, DEM_CONST) Dem_SPNClass[DEM_NUM_OF_SPNCLASS];
#endif
#endif
/********************************************************************/
#if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
extern CONST(Dem_NumOfDidClassType, DEM_CONST)
  Dem_ListOfDidClassIndex[DEM_MAX_LISTOFDIDCLASSINDEX];
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
#if (DEM_SIZE_OF_J1939FREEZEFRAME > DEM_ZERO)
extern CONST(Dem_NumOfSpnClassType, DEM_CONST)
  Dem_ListOfSPNClassIndex[DEM_MAX_LISTOFSPNCLASSINDEX];
#endif
#endif

#if (DEM_MAX_LISTOFENABLECONDITIONID > DEM_ZERO)
extern CONST(uint8, DEM_CONST)
  Dem_ListOfEnableConditionId[DEM_MAX_LISTOFENABLECONDITIONID];
#endif

#if (DEM_MAX_LISTOFSTORAGECONDITIONID > DEM_ZERO)
extern CONST(uint8, DEM_CONST)
  Dem_ListOfStorageConditionId[DEM_MAX_LISTOFSTORAGECONDITIONID];
#endif

#if (DEM_NUM_OF_CLEARDTC_NOTIFICATIONID > DEM_ZERO)
extern CONST(Dem_ClearDtcNotificationType, DEM_CONST)
  Dem_GaaClearDtcNotificationFnc[DEM_NUMBER_OF_CLEAR_DTC_NOTIFICATION_FNC];
#endif
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#if (DEM_NUM_OF_PARENT_COMPONENT_LIST > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dem_ComponentIdType, DEM_CONST)
  Dem_ListOfParrentComponent[DEM_NUM_OF_PARENT_COMPONENT_LIST];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DEM_NUM_OF_DEPENDENT_COMPONENT_LIST > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dem_ComponentIdType, DEM_CONST)
  Dem_ListOfDependentComponent[DEM_NUM_OF_DEPENDENT_COMPONENT_LIST];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DEM_NUM_OF_EVENT_ID_COMPONENT_LIST > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dem_EventIdType, DEM_CONST)
  Dem_ListOfEventIdComponent[DEM_NUM_OF_EVENT_ID_COMPONENT_LIST];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if (DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, DEM_CONST)
  Dem_ListOfDependentOperationCycle[DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dem_MultiEventTrgType, DEM_CONST)
  Dem_DemMultiEventTrg[DEM_MAX_DEM_MULTI_EVENT_TRIGGERING];
extern CONST(Dem_EventIdType, DEM_CONST)
  Dem_ListOfSlaveEventTrg[DEM_MAX_LISTOFSLAVEEVENT];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DEM_GENERAL_INTERFACE_SUPPORT == STD_ON)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array Dem_GeneralCBMonitorStatusChangedFctPtr */
extern CONST(Dem_MonitorStatusChangedFctPtrType, DEM_CONST)
  Dem_GeneralCBMonitorStatusChangedFctPtr;
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(DemDTCAttributesType, DEM_CONST)
  Dem_GaaDTCAttributes[DEM_MAX_NUMBER_OF_DTC_ATTRIBUTE];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
 ** Definition of type                                                        **
 *******************************************************************************/
/* types of the event parameter */
typedef P2VAR(Dem_EventParameterType,AUTOMATIC,DEM_VAR)
  Dem_EventParameterPtrType;
typedef P2CONST(Dem_EventParameterType,AUTOMATIC,DEM_VAR)
  Dem_EventParameterPCType;
typedef CONSTP2CONST(Dem_EventParameterType,AUTOMATIC,DEM_CONST)
  Dem_EventParameterCPCType;

/* types of the event memory */
typedef P2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_VAR)
  Dem_EventMemoryEntryPtrType;
typedef P2CONST(Dem_EventMemoryEntryType, AUTOMATIC, DEM_VAR)
  Dem_EventMemoryEntryPCType;
typedef CONSTP2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_CONST)
  Dem_EventMemoryEntryCPType;
typedef CONSTP2CONST(Dem_EventMemoryEntryType, AUTOMATIC, DEM_CONST)
  Dem_EventMemoryEntryCPCType;
typedef CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
  Dem_DataElementClassCPCType;
typedef CONSTP2CONST(Dem_DidClassType, AUTOMATIC, DEM_CONST)
  Dem_DidClassCPCType;
typedef P2CONST(Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONST)
  Dem_FreezeFrameClassPCType;
typedef CONSTP2CONST(Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONST)
  Dem_FreezeFrameClassCPCType;
typedef P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_CONST)
  Dem_CombinedDtcPCType;
typedef CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST)
  Dem_ExtendedDataRecordClassCPCType;
typedef P2CONST(Dem_ExtendedDataClassType, AUTOMATIC, DEM_CONST)
  Dem_ExtendedDataClassPCType;
typedef CONSTP2CONST(Dem_ExtendedDataClassType, AUTOMATIC, DEM_CONST)
  Dem_ExtendedDataClassCPCType;
typedef CONSTP2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST)
  Dem_EventRelatedDataCPCType;
typedef P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR)
  Dem_EventRelatedDataPCType;
typedef P2VAR(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR)
  Dem_EventRelatedDataPtrType;

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations>
 * Not a defect */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */


#endif /* DEM_PCTYPES_H */
/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/
