/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: StbM_Types.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.7           14-Feb-2024         JWMoon          CP44-3634              **
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/
#ifndef STBM_TYPES_H
#define STBM_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* standard AUTOSAR types */
#include "Std_Types.h"
/* StbM module types */
#include "Rte_StbM_Type.h"
/* OS module header file for counter and schedule table */
#include "Os.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Require Type definition                               **
*******************************************************************************/
/* Configuration data structure of the StbM module. */
/* @Trace: SWS_StbM_00249 */
/* @Trace: StbM_SDD_DATATYPE_0014 */
typedef struct STag_StbM_ConfigType
{
  uint8 dummy;
} StbM_ConfigType;

/* Variables of this type store time stamps of the Virtual Local Time. */
/* The unit is nanoseconds. */
/* @Trace: SWS_StbM_91003 */
/* @Trace: StbM_SDD_DATATYPE_0015 */
typedef struct STag_StbM_VirtualLocalTimeType
{
  /* Least significant 32 bits of the 64 bit Virtual Local Time */
  uint32 nanosecondsLo;
  
  /* Most significant 32 bits of the 64 bit Virtual Local Time */
  uint32 nanosecondsHi;
} StbM_VirtualLocalTimeType;

/* Structure which contains additional measurement data. */
/* @Trace: SWS_StbM_00384 */
/* @Trace: StbM_SDD_DATATYPE_0016 */
typedef struct STag_StbM_MeasurementType
{
  /* Propagation delay in nanoseconds */
  uint32 pathDelay;
} StbM_MeasurementType;
      
/* @Trace: SWS_StbM_00322 */
/* @Trace: StbM_SDD_DATATYPE_031 */
/* Name of the customer specific callback function */
typedef P2FUNC(Std_ReturnType, STBM_CODE, StbM_SyncTimeRecordBlockCallback)
                (const StbM_SyncRecordTableBlockType* syncRecordTableBlock);
          
/* @Trace: SWS_StbM_00328 */
/* @Trace: StbM_SDD_DATATYPE_032 */
/* Name of the customer specific callback function */
typedef P2FUNC(Std_ReturnType, STBM_CODE, StbM_OffsetTimeRecordBlockCallback)
                (const StbM_OffsetRecordTableBlockType* offsetRecordTableBlock);

/* Name of the customer specific notification callback function */
/* which shall be called, if the time previously set by the customer is reached. */
/* @Trace: StbM_SDD_DATATYPE_033 */
typedef P2FUNC(Std_ReturnType, STBM_CODE, StbM_NotificationCallback)
                (StbM_TimeDiffType deviationTime);

/* Name of the customer specific notification callback function */
/* which shall be called, if the time previously set by the customer is reached. */
/* @Trace: StbM_SDD_DATATYPE_034, StbM_SDD_DATATYPE_026 */
typedef P2FUNC(Std_ReturnType, STBM_CODE, StbM_StatusNotificationCallback)
                (StbM_TimeBaseNotificationType eventNotification);

/* Name of the customer specific notification callback function */
/* which shall be called, if the time previously set by the customer is reached. */
/* @Trace: StbM_SDD_DATATYPE_034, StbM_SDD_DATATYPE_026 */
typedef P2FUNC(Std_ReturnType, STBM_CODE, StbM_StatusNotificationInterface)
                (const StbM_TimeBaseNotificationType Data);

/*******************************************************************************
**                      Internal Type definition                              **
*******************************************************************************/
/* @Trace: StbM_SDD_DATATYPE_023 */
typedef struct STag_StbM_TimeTupleType
{
  /* Nanoseconds part of the time */
  VAR(StbM_TimeStampType, STBM_VAR) ddLocalTime;
  
  /* 48 bit Seconds part of the time */
  VAR(StbM_VirtualLocalTimeType, STBM_VAR) ddVirtualLocalTime;
} StbM_TimeTupleType;

typedef enum
{
    ETH_FREERUNNING_SOURCE = 0x00,
    GPT_FREERUNNING_SOURCE,
    OS_FREERUNNING_SOURCE,
    NONE_CONFIGURATION
} StbM_LocalTimeHardwareType;

/* Variables of this type are used to express a rate deviation in ppm. */
typedef uint32 StbM_RateCorrectionType;

/*******************************************************************************
**                      Configuration's Type definition                       **
*******************************************************************************/
/* Configuration of Time Base. */
/* @Trace: StbM_SDD_DATATYPE_035, StbM_SDD_DATATYPE_017 */
typedef struct STag_StbM_TimeBaseConfigType
{
  /* Identification of a Synchronized TimeBase via a unique identifier. */
  CONST(StbM_SynchronizedTimeBaseType, STBM_CONST) ddTimeBaseId;

  /* This reference makes the containing StbMSynchronizedTimeBase */
  /* an Offset Time-Base. */
  /* @Trace: SWS_StbM_00193 */
  CONST(StbM_SynchronizedTimeBaseType, STBM_CONST) ddSyncTimeBaseId;

  /* This parameter shall be set to true for a Global Time Master that acts */
  /* as a system-wide source of time information with respect to Global Time. */
  CONST(boolean, STBM_CONST) enSystemWideTimeMasterSlave;    

  CONST(boolean, STBM_CONST) enStoreNvRam;    

  /* This attribute describes the timeout for the situation that the time */
  /* synchronization gets lost in the scope of the time domain. */
  /* [unit: seconds]. */
  CONST(uint64, STBM_CONST) ulSyncLossTimeout;
      
  /* To identify a global time master for a particular time base */
  CONST(uint16, STBM_CONST) usClearTimeleapCount;
  
  /* This represents the maximum allowed positive difference between a newly */
  /* received Global Time Base value and the current Local Time Base value */
  /* [unit: seconds] -> nanoseconds  */
  CONST(uint64, STBM_CONST) ulStbMTimeLeapFutureThreshold;    
  
  /* This represents the maximum allowed negative difference between the */
  /* current Local Time Base value and a newly received Global Time Base value*/
  /* [unit: seconds] -> nanoseconds */
  CONST(uint64, STBM_CONST) ulStbMTimeLeapPastThreshold;

  /* Reference to the local time hardware. */
  CONST(StbM_LocalTimeHardwareType, STBM_CONST) ucLocalTimeHardware;
  
  /* References the hardware reference clock of this Synchronized Time Base. */
  CONST(uint8, STBM_CONST) usLocalTimeClockID;
  
  /* StbMNotificationCustomer */
  /* Base address of StbMNotificationCustomer config */
  CONST(uint16, STBM_CONST) usStatusMask;
  
  /* Notification about a Time Base related status change */
  CONST(StbM_StatusNotificationCallback, STBM_CONST) pStatusCallback;
  
  /* Notification about a Time Base related status change */
  CONST(StbM_StatusNotificationInterface, STBM_CONST) pStatusInterface;

  /* StbMNotificationCustomer */
  /* Base address of StbMNotificationCustomer config */
  CONST(uint8, STBM_CONST) usBaseOfNotification;
  
  /* Size of StbMNotificationCustomer config */
  CONST(uint8, STBM_CONST) usSizeOfNotification;

  /* StbMTimeCorrection */
  CONST(uint8, STBM_CONST) ucBaseOfCorrection;
  
  /* StbMTimeRecording */
  CONST(uint8, STBM_CONST) ucBaseOfRecording;

  /* StbMTriggered */
  CONST(uint8, STBM_CONST) ucBaseOfTriggered;

  CONST(uint8, STBM_CONST) ucSizeOfTriggered;
}StbM_TimeBaseConfigType;

/* Configuration the hardware reference clock of Synchronized Time Base. */
typedef struct STag_StbM_OSTimeClockConfigType
{
  /* The Counter which tick value should be read */
  CONST(CounterType, STBM_CONST) ddCounterID;

  /* Seconds Per Tick*/
  CONST(uint32, STBM_CONST) ulNanoSecondsPerTick;
} StbM_OSTimeClockConfigType;

/* Configuration the hardware reference clock of Synchronized Time Base. */
typedef struct STag_StbM_EthernetTimeClockConfigType
{
  /* Index of the addresses ETH controller */
  CONST(uint8, STBM_CONST) ucCtrlIdx;
} StbM_EthernetTimeClockConfigType;

/* Configuration of notification customer */
typedef struct STag_StbM_NotificationConfigType
{
  /* Identification of a Synchronized TimeBase that containe it*/
  CONST(StbM_SynchronizedTimeBaseType, STBM_CONST) ddTimeBaseId;
  
  /* Identification of a event notification customer */
  CONST(uint16, STBM_CONST) usId;
  
  /* Name of the customer specific notification callback function */
  /* which shall be called, if the time previously set by the customer is reached. */
  CONST(StbM_NotificationCallback, STBM_CONST) pCallback;
} StbM_NotificationConfigType;

/* Configuration of the rate- and offset correction of a Time Base. */
typedef struct STag_StbM_TimeCorrectionConfigType
{
  /* Identification of a Synchronized TimeBase that containe it*/
  CONST(StbM_SynchronizedTimeBaseType, STBM_CONST) ddTimeBaseId;
  
  /* StbMAllowMasterRateCorrection */
  CONST(boolean, STBM_CONST) blMaster;
  
  /* StbMMasterRateDeviationMax: */
  CONST(uint16, STBM_CONST) ulRateDeviationMax;
  
  /* StbMOffsetCorrectionAdaptionInterval */
  CONST(uint32, STBM_CONST) ulInterval;
  
  /* StbMOffsetCorrectionJumpThreshold */
  CONST(uint32, STBM_CONST) ulJumpThreshold;

  /* StbMRateCorrectionMeasurementDuration */
  CONST(uint32, STBM_CONST) ulDuration;
  
  /* StbMRateCorrectionsPerMeasurementDuration */
  CONST(uint16, STBM_CONST) ucPerMeasurement;
  
  /* &StbM_GaaTimeCorrectionTuple_<n>  */
  CONSTP2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_CONST) pTimeTuple;
} StbM_TimeCorrectionConfigType;

typedef struct STag_StbM_SyncTimeRecordingConfigType
{
  /* Identification of a Synchronized TimeBase that containe it*/
  CONST(StbM_SynchronizedTimeBaseType, STBM_CONST) ddTimeBaseId;
  
  CONST(uint16, STBM_CONST) usCount;
  
  CONSTP2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_CONST) pAddress;
  
  CONST(StbM_SyncTimeRecordBlockCallback, STBM_CONST) pCallback;
} StbM_SyncTimeRecordingConfigType;

typedef struct STag_StbM_OffsetTimeRecordingConfigType
{
  /* Identification of a Synchronized TimeBase that containe it*/
  CONST(StbM_SynchronizedTimeBaseType, STBM_CONST) ddTimeBaseId;
  
  CONST(uint16, STBM_CONST) usCount;
  
  CONSTP2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_CONST) pAddress;
  
  CONST(StbM_OffsetTimeRecordBlockCallback, STBM_CONST) pCallback;
} StbM_OffsetTimeRecordingConfigType;

typedef struct STag_StbM_TriggeredConfigType
{
    /* Period to trigger the OS SyncScheduleTable */
    /* This parameter shall be in multiples of main function period */
    CONST(uint64, AUTOMATIC) ulPeriod;
    
    /* Schedule table reference */
    CONST(ScheduleTableType, AUTOMATIC) ulScheduleTableId;
    
    /* OsScheduleTableDuration of Schedule table reference */
    CONST(uint64, AUTOMATIC) ulScheduleTableDuration;

    /* Reference to the OsSecondsPerTick of the counter, which drives the schedule table. */
    CONST(uint64, AUTOMATIC) ulOsSecondsPerTick;
} StbM_TriggeredConfigType;
/*******************************************************************************
**                      Value definition                                      **
*******************************************************************************/

typedef struct STag_StbM_TimeBaseValueType
{
  /* Sync Timeout time */
  VAR(StbM_RateCorrectionType, STBM_VAR) ddRate;
  
  /* Flag for time correction is avaiable */
  VAR(boolean, STBM_VAR) ucRateValid;

  /* Sync Timeout time */
  VAR(StbM_UserDataType, STBM_VAR) ddUserData;

  /* Sync Timeout time */
  VAR(StbM_TimeStampType, STBM_VAR) ddLocalTime;

  /* Counter value belonging to the Time Base, */
  /* that indicates a Time Base update to the Timesync Modules */
  VAR(uint8, STBM_VAR) timeBaseUpdateCounter;

  /* Flag for synch is avaiable */
  VAR(uint8, STBM_VAR) ucFirstSynch;

  /* Sign Global Time difference between the Received Time */
  VAR(boolean, STBM_VAR) blSignOfTimeLeap;

  /* Global Time difference between the Received Time */
  VAR(uint64, STBM_VAR) ulTimeLeap;

  /* Global Time difference between the Received Time */
  VAR(uint16, STBM_VAR) ulTimeLeapClear;

  /* Time Notifications */
  VAR(uint16, STBM_VAR) blStartTimerCount;

  /* Status Notifications */
  VAR(uint16, STBM_VAR) ulNotificationEvents;
}StbM_TimeBaseValueType;

typedef struct STag_StbM_OSTimeClockValueType
{
  /* PreviousTickCount */
  VAR(uint32, STBM_VAR) ddPreviousTickCount;

  /* PreviousTimeValue */
  VAR(uint64, STBM_VAR) ddPreviousTimeValue;
} StbM_OSTimeClockValueType;

typedef struct STag_StbM_EthernetTimeClockValueType
{
  /* FirstSync */
  VAR(boolean, STBM_VAR) blFirst;

  /* second part for first value */
  VAR(StbM_TimeStampType, STBM_VAR) ddFirstValue;
} StbM_EthernetTimeClockValueType;

typedef struct STag_StbM_NotificationValueType
{
  /* Time Notifications */
  VAR(boolean, STBM_VAR) blStartTimer;

  /* Customer Timer will expire based on the corresponding Time Base */
  VAR(StbM_TimeStampType, STBM_VAR) CustomerTimerExpireTime;
} StbM_NotificationValueType;

typedef struct STag_StbM_CallBackParameterValueType
{
  /* Time Notifications */
  VAR(boolean, STBM_VAR) enCbk;

  /* Time Notifications */
  VAR(uint16, STBM_VAR) usId;

  /* Customer Timer will expire based on the corresponding Time Base */
  VAR(StbM_TimeDiffType, STBM_VAR) ddTimeDiff;
} StbM_CallBackParameterValueType;

typedef struct STag_StbM_TimeRecordingValueType
{
  /* Identification of a Synchronized TimeBase that containe it*/
  VAR(uint16, STBM_VAR) ulPtr;
  
  /* Flag for time correction is avaiable */
  VAR(boolean, STBM_VAR) blOver;
  
} StbM_TimeRecordingValueType;

/* Configuration of the rate- and offset correction of a Time Base. */
typedef struct STag_StbM_TimeCorrectionValueType
{
  /* Flag for time correction is avaiable */
  VAR(boolean, STBM_VAR) ucFirst;
  
  /* buffer ptr of rate Correction  */
  VAR(uint8, STBM_VAR) ucCount;
  
  /* time mark of start rate Correction */
  VAR(StbM_VirtualLocalTimeType, STBM_VAR) ddMark;
} StbM_TimeCorrectionValueType;

/* Configuration of the rate- and offset correction of a Time Base. */
typedef struct STag_StbM_TriggeredValueType
{
  /* latest trigger time  */
  VAR(StbM_TimeStampType, STBM_VAR) time;
} StbM_TriggeredValueType;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* Check for unused parameter warnings*/
#ifndef STBM_UNUSED
#define STBM_UNUSED(variable) (void) variable
#endif

#endif /* STBM_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

