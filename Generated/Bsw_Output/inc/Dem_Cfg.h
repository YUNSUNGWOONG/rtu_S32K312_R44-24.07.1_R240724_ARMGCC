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
**  FILE-NAME: Dem_Cfg.h                                                      **
**                                                                            **
**  MODULE-NAME: AUTOSAR Dem Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                          **
**  Module version : 2.1.0.0                                         **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
*******************************************************************************/

/*******************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Ecu\Ecud_Dcm.arxml             
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_FiM.arxml             
*                  Configuration\Ecu\Ecud_NvM.arxml             
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml   
*                  Static_Code\Modules\Dcm_R44\generator\Dcm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\FiM_R44\generator\FiM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\NvM_R44\generator\NvM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/ 

#ifndef DEM_CFG_H
#define DEM_CFG_H


/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary in logic */



/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"



/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/

#define    DEM_AR_RELEASE_MAJOR_VERSION                  0x04u
#define    DEM_AR_RELEASE_MINOR_VERSION                  0x04u
#define    DEM_AR_RELEASE_REVISION_VERSION               0x00u
#define    DEM_SW_MAJOR_VERSION                          0x01u
#define    DEM_SW_MINOR_VERSION                          0x00u
#define    DEM_SW_PATCH_VERSION                          0x00u
#define    DEM_VENDOR_ID                                 0x004Cu
#define    DEM_MODULE_ID                                 0x0036u


/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
#ifndef    DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0  
#define    DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0 0x0101
#endif

#define    DEM_DTC_ORIGIN_USERDEFINED_MEMORY_LIST        \
            DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0\

#define    DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin) (\
            (DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0 == (DTCOrigin)) )\

#define    DEM_DTCORGIN_USER_DEFINED_CASE                \
                   case DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0:\

#define    DEM_DTC_GROUP_IS_VALID(DtcValue)              (\
            (DemEventMemorySet0_DEM_DTC_GROUP_POWERTRAIN_DTCS == (DtcValue)) || \
            (DemEventMemorySet0_DEM_DTC_GROUP_CHASSIS_DTCS == (DtcValue)) || \
            (DemEventMemorySet0_DEM_DTC_GROUP_BODY_DTCS == (DtcValue)) || \
            (DemEventMemorySet0_DEM_DTC_GROUP_NETWORK_COM_DTCS == (DtcValue)) || \
            (DemEventMemorySet1_DEM_DTC_GROUP_POWERTRAIN_DTCS == (DtcValue)) || \
            (DemEventMemorySet1_DEM_DTC_GROUP_CHASSIS_DTCS == (DtcValue)) || \
            (DemEventMemorySet1_DEM_DTC_GROUP_BODY_DTCS == (DtcValue)) || \
            (DemEventMemorySet1_DEM_DTC_GROUP_NETWORK_COM_DTCS == (DtcValue)) )\

/* Handles for NvM related Macros /AUTOSAR/NvM/NvMBlock_DemNonVolatileData */
#define    DEM_NVM_BLK_ID_NON_VOLATILE_DATA              (2)
/* Pre-compile option whether J1939 supported or not */
#define    DEM_J1939_SUPPORT                             (STD_OFF)
/* Total DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID entries */
#define    DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID      (3)
/* 
 * Pre-compile option defines the maximum number of elements in buffer for 
 *                    handling of BSW errors
 */

#define    DEM_BSW_ERROR_BUFFER_SIZE                     (25)
/* Pre-compile option defines the clearing process */
#define    DEM_CLEAR_DTC_BEHAVIOUR                       (DEM_CLRRESP_NONVOLATILE_FINISH)
/* Pre-compile option defines support of PTO Functionality */
#define    DEM_PTO_SUPPORT                               (STD_OFF)
/* Precompile option for MIL Indicator ID */
#define    DEM_J1939_PROTECT_LAMP_INDICATORID            (3)
/* Pre-compile option defines support of OBD Functionality */
#define    DEM_OBD_SUPPORT                               (DEM_OBD_NO_OBD_SUPPORT)
/* 
 * Pre-compile option whether internal data max FDC during current cycle is 
 *  enabled or not
 */

#define    DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE (STD_OFF)
/* Precompile option for MIL Indicator ID */
#define    DEM_J1939_REDSTOP_LAMP_INDICATORID            (1)
/* 
 * Pre-compile option whether the aging cycle counter is 
 *  processed every aging cycles or if only tested aging cycle are considered
 */

#define    DEM_AGING_REQUIERES_TESTED_CYCLE              (STD_ON)
/* 
 * Pre-compile option whether the controls the delayed calculation of 
 *  the confirmed status for the OBD driving cycle
 */

#define    DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL         (STD_OFF)
/* Precompile option for MIL Indicator ID */
#define    DEM_MIL_INDICATORID                           (0)
/* 
 * Precompile option for calculating the byte when engine is of type
 *  compression
 */

#define    DEM_PID01_BYTEC_COMPRESSION                   (0)
/* Pre-compile option whether counter based pre debounced supported or not */
#define    DEM_DEBOUNCE_COUNTER_SUPPORT                  (STD_ON)
/* To enable/disable general interface */
#define    DEM_GENERAL_INTERFACE_SUPPORT                 (STD_ON)
/* 
 * Pre-compile option whether Cycles since last failed is 
 *  enabled or not
 */

#define    DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED    (STD_OFF)
/* To check the configuration of NvMSetRamBlockStatusApi in NvM module is TRUE/FALSE */
#define    DEM_NVM_SET_RAM_BLOCK_STATUS_API              (STD_ON)
/* 
 * Pre-compile option for check all parameter DemEnvironmentDataCapture
 *  configured with DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING
 */

#define    DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING (STD_OFF)
/* Macro to Activate/Deactivate the notification to the FIM */
#define    DEM_TRIGGER_FIM_REPORTS                       (STD_ON)
/* 
 * Pre-compile option whether the aging cycle counter is processed in 
 *  operation cycles with test failed report or not
 */

#define    DEM_AGING_REQUIRES_NOT_FAILED_CYCLE           (STD_ON)
/* Activate/Deactivate the permanent storage of the TestFailed status bits */
#define    DEM_STATUS_BIT_STORAGE_TESTFAILED             (STD_ON)
/* 
 * Pre-compile option whether Failed cycles is 
 *  enabled or not
 */

#define    DEM_INTERNAL_DATA_FAILED_CYCLES               (STD_OFF)
/* Pre-compile option defines the size of Prestore buffer */
#define    DEM_MAX_NUMBER_PRESTORED_FF                   (0)
/* Defines the supported Dem_<...>ClearDTC API scope. */
#define    DEM_CLEAR_DTC_LIMITATION                      (DEM_ALL_SUPPORTED_DTCS)
/* 
* Pre-compile option defines whether the enable conditions is supported or
* not
*/

#define    DEM_ENABLE_CONDITION_SUPPORT                  (STD_ON)
/* 
 * Pre-compile option whether operation cycle status storage is 
 *  enabled or not
 */

#define    DEM_OPERATION_CYCLE_STATUS_STORAGE            (STD_OFF)
/* 
 * Pre-compile option whether internal data max FDC since last clear is 
 *  enabled or not
 */

#define    DEM_INTERNAL_DATA_MAX_FDC_SINCE_LAST_CLEAR    (STD_OFF)
/* 
 * Pre-compile the size of the buffer for storing environmental data 
 *  until they are processed and stored
 */

#define    DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER       (0)
/* 
 * Pre-compile option whether the confirmed bit is reset
 *  or not while an event memory entry will be displaced
 */

#define    DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW           (STD_ON)
/* 
 * Pre-compile option whether Cycles since first failed is 
 *  enabled or not
 */

#define    DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED   (STD_OFF)
/* Total DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID entries */
#define    DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID  (3)
/* Macro for the Combination Support */
#define    DEM_EVENT_COMBINATION_SUPPORT                 (DEM_EVCOMB_ONRETRIEVAL)
/* To enable/disable the Dem_GetVersionInfo API */
#define    DEM_VERSION_INFO_API                          (STD_ON)
/* Pre-compile option the Initialization for FiM */
#define    DEM_FIM_INTEGRATED                            (STD_ON)
/* Precompile option for status bit handling for Test Failed Since Last Clear */
#define    DEM_STATUS_BIT_HANDLING_TFSLC                 (DEM_STATUS_BIT_NORMAL)
/* 
 * Macro to define whether init should be triggered before or after        
 *              DEM_CLEAR_OK
 */

#define    DEM_TRIGGER_INIT_BEFORE_CLEAR_OK              (STD_OFF)
/* Total DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID entries */
#define    DEM_NUM_OF_MIRROR_EVENTMEMORY_NVBLOCKID       (3)
/* Total DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID entries */
#define    DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID    (3)
/* Precompile option for calculating the obd event memory set index */
#define    DEM_OBD_EVENT_MEMORY_SET_IDX                  (0)
/* Pre-compile option whether time based pre debounce supported or not */
#define    DEM_DEBOUNCE_TIME_SUPPORT                     (STD_ON)
/* Macro for task time */
#define    DEM_TASK_TIME                                 (10.0)
/* Handles for NvM related Macros /AUTOSAR/NvM/NvMBlock_DemEventStatusNvRamBlock */
#define    DEM_NVM_BLK_ID_EVENT_STATUS                   (3)
/* 
 * Precompile option for calculating the lower nibble value based on the 
 *  configuration
 */

#define    DEM_PID01_BYTEB_LOWER_NIBBLE                  (0)
/* Macro for the storsage condition support */
#define    DEM_STORAGE_CONDITION_SUPPORT                 (STD_ON)
/* Precompile option for MIL Indicator ID */
#define    DEM_J1939_AMBERWARNING_LAMP_INDICATORID       (2)
/* Precompile option for calculating the byte when engine is of type spark */
#define    DEM_PID01_BYTEC_SPARK                         (0)
/* 
 * Pre-compile default endianness of the data belonging 
 *  to a data element
 */

#define    DEM_DATA_ELEMENT_DEFAULT_ENDIANNESS           (BIG_ENDIAN)
/* Pre-compile option whether clear event without Dtc Event Memory */
#define    DEM_CLEAR_EVENTS_WITHOUT_DTC_EVENT_MEMORY     (DEM_NO_EVMEM_IDX)
/* Pre-compile option whether support for availability is enabled or not. */
#define    DEM_AVAILABILITY_SUPPORT                      (DEM_EVENT_AVAILABILITY)
/* 
 * Pre-compile option for check at least one
 *  DemDebounceCounterStorage is configured true
 */

#define    DEM_DEBOUNCE_COUNTER_STORAGE_CONFIGURED       (STD_OFF)
/* To enable/disable development error detection */
#define    DEM_DEV_ERROR_DETECT                          (STD_ON)
/* Pre-compile option to enable or disable DTC suppression support */
#define    DEM_SUPPRESSION_SUPPORT                       (DEM_DTC_SUPPRESSION)
/* Dem OBD Centralized PID 21 handling */
#define    DEM_OBD_CENTRALIZED_PID_21_HANDLING           (STD_OFF)


/* Dem OBD Centralized PID 31 handling */
#define    DEM_OBD_CENTRALIZED_PID_31_HANDLING           (STD_OFF)


/* Dem OBD Delayed DCY Confirmed and MIL  */
#define    DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL         (STD_OFF)


/* Dem Obd event Displacement */
#define    DEM_OBD_EVENT_DISPLACEMENT                    (STD_OFF)


/* Dem Obd Uds Dtc Separation */
#define    DEM_OBD_UDS_DTC_SEPARATION_SUPPORT            (STD_OFF)


/* Precompile option for Dem OBD Compliancy */
#define    DEM_OBD_COMPLIANCE                            (0)
/* Precompile option for the type of Engine */
#define    DEM_ENGINE_CHECK                              (DEM_ENGINE_SPARK)

/* Pre-compile option to support protocol J1979-2 (OBD_ON_UDS) or not */
#define    DEM_J1979_2_OBD_ON_UDS                        (STD_OFF)


/* Precompile option for DemJ1939ClearDtcSupport */
#define    DEM_J1939_CLEAR_DTC_SUPPORT                   (STD_OFF)


/* Precompile option for DemJ1939Dm31SupportSupport */
#define    DEM_J1939_DM31_SUPPORT                        (STD_OFF)


/* Precompile option for DemJ1939ExpandedFreezeFrameSupport */
#define    DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT        (STD_OFF)


/* Precompile option for DemJ1939FreezeFrameSupport */
#define    DEM_J1939_FREEZEFRAME_SUPPORT                 (STD_OFF)


/* Precompile option for DemJ1939RatioSupport */
#define    DEM_J1939_RATIO_SUPPORT                       (STD_OFF)


/* Precompile option for DemJ1939Readiness1Support */
#define    DEM_J1939_READINESS1_SUPPORT                  (STD_OFF)


/* Precompile option for DemJ1939Readiness2Support */
#define    DEM_J1939_READINESS2_SUPPORT                  (STD_OFF)


/* Precompile option for DemJ1939Readiness3Support */
#define    DEM_J1939_READINESS3_SUPPORT                  (STD_OFF)


/* Precompile option for DemJ1939ReadingDtcSupport */
#define    DEM_J1939_READING_DTC_SUPPORT                 (STD_OFF)


/* Precompile option for reportFirstConfirmedDTC, reportFirstTestFailedDTC, reportMostRecentTestFailedDTC, reportMostRecentConfirmedDTC are used in Dcm */
#define    DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED       (STD_ON)


/* Total DEM_MAX_EVENT_DESTINATION_SELECTED entries */
#define    DEM_MAX_EVENT_DESTINATION_SELECTED            (2)
/* Precompile option for the total data element data size of the PIDs */
#define    DEM_MAX_SIZE_OF_PID_DATAELEMENT               (0)
/* Total DEM_NUMBER_OF_DATA_ELEMENT_INTERNAL entries */
#define    DEM_NUMBER_OF_DATA_ELEMENT_INTERNAL           (3)
/* Total DEM_NUM_OF_J1939FREEZEFRAMECLASS entries */
#define    DEM_NUM_OF_J1939FREEZEFRAMECLASS              (0)
/* Total DEM_MAX_LISTOFDATAELEMENTCLASSINDEX entries */
#define    DEM_MAX_LISTOFDATAELEMENTCLASSINDEX           (7)
/* Total DEM_MAX_LISTOFSPNCLASSINDEX entries */
#define    DEM_MAX_LISTOFSPNCLASSINDEX                   (0)
/* Macro to define the number of element in dependent component list*/
#define    DEM_NUM_OF_DEPENDENT_COMPONENT_LIST           (0)
/* 
 * Precompile option for the total number healing counter to be stored for
 * indicator
 */

#define    DEM_NUM_OF_HEALING_COUNTER                    (26)
/* Macro to define the max size of freeze frame */
#define    DEM_SIZE_OF_FF_ONE_RECORD                     (3)
/* Total DEM_NUMBER_OF_DEM_COMPONENT entries */
#define    DEM_NUMBER_OF_DEM_COMPONENT                   (1)
/* Macro to define the max size of j1939 freeze frame */
#define    DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME          (0)
/* Total DEM_NUM_OF_CLEARDTC_NOTIFICATIONID entries */
#define    DEM_NUM_OF_CLEARDTC_NOTIFICATIONID            (1)
/* Macro to define the max number of events for DTC */
#define    DEM_MAX_NUM_EVENTS_PER_DTC                    (5)
/* Total DEM_NUM_OF_DATAELEMENTCLASS entries */
#define    DEM_NUM_OF_DATAELEMENTCLASS                   (12)
/* Total DEM_NUM_OF_DIDCLASS entries */
#define    DEM_NUM_OF_DIDCLASS                           (2)
/* Total DEM_NUM_OF_FREEZEFRAMECLASS entries */
#define    DEM_NUM_OF_FREEZEFRAMECLASS                   (2)
/* Precompile option for the total DTRs */
#define    DEM_NUMBER_OF_DTRS                            (0)
/* Total DEM_MAX_LISTOFCHILDCOMPONENT entries */
#define    DEM_MAX_LISTOFCHILDCOMPONENT                  (0)
/* Total DEM_MAX_NUMBER_OF_PID_RECDS entries */
#define    DEM_MAX_NUMBER_OF_PID_RECDS                   (0)
/* Macro to define the max size of extended data */
#define    DEM_SIZE_OF_EXTENDED_DATA                     (3)
/* Total DEM_MAX_LISTOFCBMONITORSTATUSCHANGED entries */
#define    DEM_MAX_LISTOFCBMONITORSTATUSCHANGED          (0)
/* 
 * Precompile option for the total number failure counter to be stored for
 * indicator
 */
#define    DEM_NUM_OF_FAILURE_COUNTER                    (28)
/* Total number of Dem GeneralOBD*/
#define    DEM_NUM_OF_GST_GENERAL_OBD_INFO               (0)
/* Total number of Dtc status change FCTPTR */
#define    DEM_NUMBER_OF_DTC_STATUS_CHANGED_FCT_PTR      (1)
/* Total DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER entries */
#define    DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER            (4)
/* Total DEM_MAX_LISTOFENABLECONDITIONID entries */
#define    DEM_MAX_LISTOFENABLECONDITIONID               (1)
/* Total DEM_NUM_OF_SPNCLASS entries */
#define    DEM_NUM_OF_SPNCLASS                           (0)
/* Total DEM_NUM_OF_EXTENDEDDATARECORDCLASS entries */
#define    DEM_NUM_OF_EXTENDEDDATARECORDCLASS            (5)
/* 
 * Pre-compile option indicates the maximum number of events that can be
 * stored  in the user defined memory
 */

#define    DEM_MAX_NUMBER_EVENT_ENTRY_UD                 (3)
/* Total DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST entries */
#define    DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST     (0)
/* Total DEM_MAX_NUMBER_MEMORY_SET entries */
#define    DEM_MAX_NUMBER_MEMORY_SET                     (2)
/* Total DEM_MAX_LISTOFEDRECORDCLASSINDEX entries */
#define    DEM_MAX_LISTOFEDRECORDCLASSINDEX              (6)
/* Total DEM_NUM_OF_EVENTRELATEDDATA entries */
#define    DEM_NUM_OF_EVENTRELATEDDATA                   (22)
/* Total DEM_MAX_NUM_GRP_DTC entries */
#define    DEM_MAX_NUM_GRP_DTC                           (8)
/* Total DEM_MAX_LISTOFSLAVEEVENT entries */
#define    DEM_MAX_LISTOFSLAVEEVENT                      (2)
/* 
 * Precompile option for the total indicator attribite status to be stored/
 * for indicator/
*/

#define    DEM_NUM_OF_INDICATOR_ATTRIBUTE_STATUS         (18)
/* 
 * Pre-compile option indicates the maximum number of events that can be
 * stored  in the mirror memory
 */

#define    DEM_MAX_NUMBER_EVENT_ENTRY_MIR                (7)
/* Total DEM_NUMBER_OPERATION_CYCLES entries */
#define    DEM_NUMBER_OPERATION_CYCLES                   (2)
/* Total DEM_NUMBER_OF_DEM_CLIENT entries */
#define    DEM_NUMBER_OF_DEM_CLIENT                      (2)
/* Precompile option for the total number of the PID data elements */
#define    DEM_TOTAL_PID_DATAELEMENT_COUNT               (0)
/* Total DEM_NUMBER_OF_INDICATORS entries */
#define    DEM_NUMBER_OF_INDICATORS                      (28)
/* Total DEM_MAX_LISTOFSTORAGECONDITIONID entries */
#define    DEM_MAX_LISTOFSTORAGECONDITIONID              (2)
/* Total DEM_NUMBER_OF_EVENTS entries */
#define    DEM_NUMBER_OF_EVENTS                          (107)
/* Total DEM_NUM_OF_EXTENDEDDATACLASS entries */
#define    DEM_NUM_OF_EXTENDEDDATACLASS                  (5)
/* Total number of Obd Callback DtcStatusChanged */
#define    DEM_START_OBDCBDTCSTATUSCHANGED               (0)
/* Macro to define the number of element in parent component list*/
#define    DEM_NUM_OF_PARENT_COMPONENT_LIST              (0)
/* 
 * Pre-compile option indicates the maximum number of events that can be
 * stored  in the permanent memory
 */

#define    DEM_MAX_NUMBER_EVENT_ENTRY_PER                (8)
/* Total DEM_NUM_OF_FRREZEFRAMERECORDCLASS entries */
#define    DEM_NUM_OF_FRREZEFRAMERECORDCLASS             (11)
/* The maximum number of supported DTC origins */
#define    DEM_MAX_NUMBER_SUPPORTED_DTC_ORIGINS          (3)
/* Total DEM_MAX_NUMBER_OF_DTC entries */
#define    DEM_MAX_NUMBER_OF_DTC                         (18)
/* Start Index J1939 Callback DtcStatusChanged*/
#define    DEM_START_J1939CBDTCSTATUSCHANGED             (0)
/* 
 * Pre-compile option indicates the maximum number of events that can be
 * stored  in the primary memory
 */
#define    DEM_MAX_NUMBER_EVENT_ENTRY_PRI                (9)
/* Total DEM_MAX_NUMBER_PRIMARY_MEMORY entries */
#define    DEM_MAX_NUMBER_PRIMARY_MEMORY                 (2)
/* Total number of J1939 Callback DtcStatusChanged */
#define    DEM_NUM_OF_J1939CBDTCSTATUSCHANGED            (0)
/* Total DEM_NUMBER_OF_RATIO_INFO entries */
#define    DEM_NUMBER_OF_RATIO_INFO                      (0)
/* Total number of event status changed fctptr */
#define    DEM_NUM_OF_EVT_STATUS_CHANGED_FCTPTR          (6)
/* Total DEM_MAX_NUMBER_OF_PID_DATAELEMENT entries */
#define    DEM_MAX_NUMBER_OF_PID_DATAELEMENT             (0)
/* Total DEM_MAX_LISTOFDIDCLASSINDEX entries */
#define    DEM_MAX_LISTOFDIDCLASSINDEX                   (2)
/* Precompile option for the total number callback DTC Status changed */
#define    DEM_MAX_NUM_OF_DTC_STAT_CHNG_FCTS             (0)
/* Total number of Dem operation cycle events*/
#define    DEM_NUM_OF_OPERATION_CYCLE_EVENTS             (107)
/* Total DEM_MAX_DEM_MULTI_EVENT_TRIGGERING entries */
#define    DEM_MAX_DEM_MULTI_EVENT_TRIGGERING            (1)
/* 
 * Precompile option for the enable/disable of fault confirmation
 * counter(trip counter)
 */
#define    DEM_NUM_OF_ENABLE_TRIP_COUNTER                (2)
/* Total DEM_MAX_NUMBER_USER_DEFINED_MEMORY entries */
#define    DEM_MAX_NUMBER_USER_DEFINED_MEMORY            (1)
/* Total number of monitor status changed fctptrtype */
#define    DEM_NUMBER_OF_MONITOR_STATUS_CHANGED_FCT_PTR_TYPE (1)
/* Total number of Dtc notification function */
#define    DEM_NUMBER_OF_CLEAR_DTC_NOTIFICATION_FNC      (1)
/* Precompile option for the total OBD Freeze frame class */
#define    DEM_NUM_OF_OBDFREEZEFRAMECLASS                (0)
/* Total DEM_MAX_NUM_OF_EVENT_STAT_CHNG_FCTS entries */
#define    DEM_MAX_NUM_OF_EVENT_STAT_CHNG_FCTS           (6)
/* Total DEM_MAX_LISTOFCOMBINEDEVENTS entries */
#define    DEM_MAX_LISTOFCOMBINEDEVENTS                  (22)
/* Macro to define the max size of event related data */
#define    DEM_SIZE_OF_EVENT_DATA                        (6)
/* Precompile option for the total number IndicatorId */
#define    DEM_NUM_OF_INDICATORID                        (6)
/* Total DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL entries */
#define    DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL   (0)
/* Macro to define the max size of j1939 freeze frame */
#define    DEM_SIZE_OF_J1939FREEZEFRAME                  (0)
/* Total DEM_NUMBER_OF_PRE_DEBOUNCE_TIME entries */
#define    DEM_NUMBER_OF_PRE_DEBOUNCE_TIME               (3)
/* Total number of Obd Callback DtcStatusChanged */
#define    DEM_NUM_OF_OBDCBDTCSTATUSCHANGED              (0)
/* Total DEM_NUMBER_STORAGE_CONDITION entries */
#define    DEM_NUMBER_STORAGE_CONDITION                  (2)
/* Total DEM_NUMBER_ENABLE_CONDITION entries */
#define    DEM_NUMBER_ENABLE_CONDITION                   (1)
/* Macro to define the max size of freeze frame */
#define    DEM_SIZE_OF_FREEZEFRAME                       (3)
/* Macro to define the max number of events for operation cycle */
#define    DEM_MAX_EVENT_PER_CYCLE                       (11449)
/* Maximum FID that the parameter DemFunctionIdRef configured */
#define    DEM_MAX_NUMBER_OF_FID_REF                     (0)
/* Macro to define the number of element in event id component list*/
#define    DEM_NUM_OF_EVENT_ID_COMPONENT_LIST            (2)
/* Total DEM_MAX_NUMBER_OF_DTC_ATTRIBUTE entries */
#define    DEM_MAX_NUMBER_OF_DTC_ATTRIBUTE               (14)
/* Total number of SWC Event*/
#define    DEM_NUMBER_OF_SWC_EVENTS                      (0)



/* Macro to Activate/Deactivate the notification to the DCM */
#define DEM_TRIGGER_DCM_REPORTS (STD_OFF)


/* Macro for the Immediate storage limit configured */
#define DEM_IMMEDIATE_NV_STORAGE_LIMIT ((uint8)6)

/* 
 * Pre-compile option indicates the maximum number of events that can be
 * stored  in the secondary memory
 */
#define DEM_MAX_NUMBER_EVENT_ENTRY_SEC (0)

/* Precompile option for operation cycle proccessing */
#define DEM_OPER_CYCLE_PROCESSING (DEM_PROCESS_OPCYC_STATE)


/* 
 * Defines if the healing cycle counter is processed every event operation
 * cycles or if only tested event operation cycle are considered.
 */
#define DEM_HEALING_REQUIERES_TESTED_CYCLE (STD_ON)

/* 
 * This configuration switch defines, whether support for nvm access
 * optimization is enabled or not.
 */
#define DEM_NVRAMBLOCK_ACCESS_OPTIMIZATION_SUPPORT (STD_OFF)

/* Activate/Deactivate the permanent storage of the "TestFailed" status bit */
#define DEM_NUM_OF_TESTFAILED_BIT_STORAGE 0





/* DEM_DTC_GROUP_POWERTRAIN_DTCS*/
#define    DemEventMemorySet0_DEM_DTC_GROUP_POWERTRAIN_DTCS 0x100
/* DEM_DTC_GROUP_CHASSIS_DTCS*/
#define    DemEventMemorySet0_DEM_DTC_GROUP_CHASSIS_DTCS 0x4000ff
/* DEM_DTC_GROUP_BODY_DTCS*/
#define    DemEventMemorySet0_DEM_DTC_GROUP_BODY_DTCS    0x8000ff
/* DEM_DTC_GROUP_NETWORK_COM_DTCS*/
#define    DemEventMemorySet0_DEM_DTC_GROUP_NETWORK_COM_DTCS 0xc000ff
/* DEM_DTC_GROUP_POWERTRAIN_DTCS*/
#define    DemEventMemorySet1_DEM_DTC_GROUP_POWERTRAIN_DTCS 0x100
/* DEM_DTC_GROUP_CHASSIS_DTCS*/
#define    DemEventMemorySet1_DEM_DTC_GROUP_CHASSIS_DTCS 0x4000ff
/* DEM_DTC_GROUP_BODY_DTCS*/
#define    DemEventMemorySet1_DEM_DTC_GROUP_BODY_DTCS    0x8000ff
/* DEM_DTC_GROUP_NETWORK_COM_DTCS*/
#define    DemEventMemorySet1_DEM_DTC_GROUP_NETWORK_COM_DTCS 0xc000ff


/*******************************************************************************
**                      HandleId's Information                                **
*******************************************************************************/

#define    DemConf_DemEventParameter_ETH_E_ACCESS        ((Dem_EventIdType)1)
#define    DemConf_DemEventParameter_ETH_E_ALIGNMENT     ((Dem_EventIdType)2)
#define    DemConf_DemEventParameter_ETH_E_CRC           ((Dem_EventIdType)3)
#define    DemConf_DemEventParameter_ETH_E_LATECOLLISON  ((Dem_EventIdType)4)
#define    DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION ((Dem_EventIdType)5)
#define    DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME ((Dem_EventIdType)6)
#define    DemConf_DemEventParameter_ETH_E_RX_FRAMES_LOST ((Dem_EventIdType)7)
#define    DemConf_DemEventParameter_ETH_E_SINGLECOLLISION ((Dem_EventIdType)8)
#define    DemConf_DemEventParameter_ETH_E_UNDERSIZRFRAME ((Dem_EventIdType)9)
#define    DemConf_DemEventParameter_FEE_E_GC_ERASE      ((Dem_EventIdType)10)
#define    DemConf_DemEventParameter_FEE_E_GC_INIT       ((Dem_EventIdType)11)
#define    DemConf_DemEventParameter_FEE_E_GC_READ       ((Dem_EventIdType)12)
#define    DemConf_DemEventParameter_FEE_E_GC_TRIG       ((Dem_EventIdType)13)
#define    DemConf_DemEventParameter_FEE_E_GC_WRITE      ((Dem_EventIdType)14)
#define    DemConf_DemEventParameter_FEE_E_INVALIDATE    ((Dem_EventIdType)15)
#define    DemConf_DemEventParameter_FEE_E_READ          ((Dem_EventIdType)16)
#define    DemConf_DemEventParameter_FEE_E_UNCONFIG_BLK_EXCEEDED ((Dem_EventIdType)17)
#define    DemConf_DemEventParameter_FEE_E_WRITE         ((Dem_EventIdType)18)
#define    DemConf_DemEventParameter_FEE_E_WRITE_CYCLES_EXHAUSTED ((Dem_EventIdType)19)
#define    DemConf_DemEventParameter_FLS_E_COMPARE_FAILED ((Dem_EventIdType)20)
#define    DemConf_DemEventParameter_FLS_E_ERASE_FAILED  ((Dem_EventIdType)21)
#define    DemConf_DemEventParameter_FLS_E_READ_FAILED   ((Dem_EventIdType)22)
#define    DemConf_DemEventParameter_FLS_E_UNEXPECTED_FLASH_ID ((Dem_EventIdType)23)
#define    DemConf_DemEventParameter_FLS_E_WRITE_FAILED  ((Dem_EventIdType)24)
#define    DemConf_DemEventParameter_MCU_E_CCU6_CLC_ENABLE_ERR ((Dem_EventIdType)25)
#define    DemConf_DemEventParameter_MCU_E_CCU6_CLC_DISABLE_ERR ((Dem_EventIdType)26)
#define    DemConf_DemEventParameter_MCU_E_CCUCON_UPDATE_ERR ((Dem_EventIdType)27)
#define    DemConf_DemEventParameter_MCU_E_CLOCK_FAILURE ((Dem_EventIdType)28)
#define    DemConf_DemEventParameter_MCU_E_CONVCTRL_CLC_ENABLE_ERR ((Dem_EventIdType)29)
#define    DemConf_DemEventParameter_MCU_E_CONVCTRL_CLC_DISABLE_ERR ((Dem_EventIdType)30)
#define    DemConf_DemEventParameter_MCU_E_GPT12_CLC_ENABLE_ERR ((Dem_EventIdType)31)
#define    DemConf_DemEventParameter_MCU_E_GPT12_CLC_DISABLE_ERR ((Dem_EventIdType)32)
#define    DemConf_DemEventParameter_MCU_E_GTM_CLC_ENABLE_ERR ((Dem_EventIdType)33)
#define    DemConf_DemEventParameter_MCU_E_GTM_CLC_DISABLE_ERR ((Dem_EventIdType)34)
#define    DemConf_DemEventParameter_MCU_E_OSC_FAILURE   ((Dem_EventIdType)35)
#define    DemConf_DemEventParameter_MCU_E_PERIPHERAL_PLL_LOCK_LOSS ((Dem_EventIdType)36)
#define    DemConf_DemEventParameter_MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR ((Dem_EventIdType)37)
#define    DemConf_DemEventParameter_MCU_E_PMSWCR_UPDATE_ERR ((Dem_EventIdType)38)
#define    DemConf_DemEventParameter_MCU_E_SYSTEM_PLL_LOCK_LOSS ((Dem_EventIdType)39)
#define    DemConf_DemEventParameter_MCU_E_SYSTEM_PLL_TIMEOUT_ERR ((Dem_EventIdType)40)
#define    DemConf_DemEventParameter_SPI_E_HARDWARE_ERROR ((Dem_EventIdType)41)
#define    DemConf_DemEventParameter_WDG_E_DISABLE_REJECTED ((Dem_EventIdType)42)
#define    DemConf_DemEventParameter_WDG_E_MODE_FAILED   ((Dem_EventIdType)43)
#define    DemConf_DemEventParameter_CANCM_E_BAT_FAIL    ((Dem_EventIdType)44)
#define    DemConf_DemEventParameter_CANSM_E_BUS_OFF_FD_CAN1 ((Dem_EventIdType)45)
#define    DemConf_DemEventParameter_CANSM_E_BUS_OFF_FD_CAN2 ((Dem_EventIdType)46)
#define    DemConf_DemEventParameter_CANSM_E_BUS_OFF_HS_CAN1 ((Dem_EventIdType)47)
#define    DemConf_DemEventParameter_CANSM_E_BUS_OFF_Project ((Dem_EventIdType)48)
#define    DemConf_DemEventParameter_CANSM_E_BUS_OFF_LS_CAN1 ((Dem_EventIdType)49)
#define    DemConf_DemEventParameter_CANSM_E_MODE_CHANGE_FD_CAN1 ((Dem_EventIdType)50)
#define    DemConf_DemEventParameter_CANSM_E_MODE_CHANGE_FD_CAN2 ((Dem_EventIdType)51)
#define    DemConf_DemEventParameter_CANSM_E_MODE_CHANGE_HS_CAN1 ((Dem_EventIdType)52)
#define    DemConf_DemEventParameter_CANSM_E_MODE_CHANGE_Project ((Dem_EventIdType)53)
#define    DemConf_DemEventParameter_CANSM_E_MODE_CHANGE_LS_CAN1 ((Dem_EventIdType)54)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT1   ((Dem_EventIdType)55)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT2   ((Dem_EventIdType)56)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT3   ((Dem_EventIdType)57)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT4   ((Dem_EventIdType)58)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT5   ((Dem_EventIdType)59)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT6   ((Dem_EventIdType)60)
#define    DemConf_DemEventParameter_ECUM_E_CONFIGURATION_DATA_INCONSISTENT ((Dem_EventIdType)61)
#define    DemConf_DemEventParameter_WDGM_E_IMPROPER_CALLER ((Dem_EventIdType)62)
#define    DemConf_DemEventParameter_ECUM_E_RAM_CHECK_FAILED ((Dem_EventIdType)63)
#define    DemConf_DemEventParameter_ETHSM_E_LINK_DOWN   ((Dem_EventIdType)64)
#define    DemConf_DemEventParameter_ETHTRCV_E_ACCESS    ((Dem_EventIdType)65)
#define    DemConf_DemEventParameter_IOHWAB_E_BUSY       ((Dem_EventIdType)66)
#define    DemConf_DemEventParameter_IOHWAB_E_PROC_FAIL  ((Dem_EventIdType)67)
#define    DemConf_DemEventParameter_IOHWAB_E_SETUP_FAIL ((Dem_EventIdType)68)
#define    DemConf_DemEventParameter_IOHWAB_E_WRONG_STATE ((Dem_EventIdType)69)
#define    DemConf_DemEventParameter_IOHWAB_E_WRONG_SETTING ((Dem_EventIdType)70)
#define    DemConf_DemEventParameter_IOHWAB_E_WRONG_PARAM ((Dem_EventIdType)71)
#define    DemConf_DemEventParameter_NVM_E_INTEGRITY_FAILED ((Dem_EventIdType)72)
#define    DemConf_DemEventParameter_NVM_E_LOSS_OF_REDUNDANCY ((Dem_EventIdType)73)
#define    DemConf_DemEventParameter_NVM_E_QUEUE_OVERFLOW ((Dem_EventIdType)74)
#define    DemConf_DemEventParameter_NVM_E_REQ_FAILED    ((Dem_EventIdType)75)
#define    DemConf_DemEventParameter_NVM_E_VERIFY_FAILED ((Dem_EventIdType)76)
#define    DemConf_DemEventParameter_NVM_E_WRITE_PROTECTED ((Dem_EventIdType)77)
#define    DemConf_DemEventParameter_NVM_E_WRONG_BLOCK_ID ((Dem_EventIdType)78)
#define    DemConf_DemEventParameter_WDG_76_ACW_E_DISABLE_REJECTED ((Dem_EventIdType)79)
#define    DemConf_DemEventParameter_WDG_76_ACW_E_MODE_FAILED ((Dem_EventIdType)80)
#define    DemConf_DemEventParameter_ECUM_E_IMPROPER_CALLER ((Dem_EventIdType)81)
#define    DemConf_DemEventParameter_WDGM_E_MONITORING   ((Dem_EventIdType)82)
#define    DemConf_DemEventParameter_WDGM_E_SET_MODE     ((Dem_EventIdType)83)
#define    DemConf_DemEventParameter_EEP_E_COMPARE_FAILED ((Dem_EventIdType)84)
#define    DemConf_DemEventParameter_EEP_E_ERASE_FAILED  ((Dem_EventIdType)85)
#define    DemConf_DemEventParameter_EEP_E_READ_FAILED   ((Dem_EventIdType)86)
#define    DemConf_DemEventParameter_EEP_E_WRITE_FAILED  ((Dem_EventIdType)87)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT7   ((Dem_EventIdType)88)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT8   ((Dem_EventIdType)89)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT9   ((Dem_EventIdType)90)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT10  ((Dem_EventIdType)91)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT11  ((Dem_EventIdType)92)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT12  ((Dem_EventIdType)93)
#define    DemConf_DemEventParameter_CANSM_E_MODE_REQUEST_TIMEOUT_HS_CAN1 ((Dem_EventIdType)94)
#define    DemConf_DemEventParameter_CANSM_E_MODE_REQUEST_TIMEOUT_FD_CAN1 ((Dem_EventIdType)95)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT13  ((Dem_EventIdType)96)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT_SOMEIPXF_MALFORMED_MESSAGE ((Dem_EventIdType)97)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT_E2EXF_MALFORMED_MESSAGE ((Dem_EventIdType)98)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT14  ((Dem_EventIdType)99)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT15  ((Dem_EventIdType)100)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT16  ((Dem_EventIdType)101)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT17  ((Dem_EventIdType)102)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT18  ((Dem_EventIdType)103)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT19  ((Dem_EventIdType)104)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT20  ((Dem_EventIdType)105)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT21  ((Dem_EventIdType)106)
#define    DemConf_DemEventParameter_DEM_E_TEST_EVENT22  ((Dem_EventIdType)107)
/* The handles for each EnableCondition configured */
#define    DemConf_DemEnableCondition_DemEnableCondition0 (Dem_EnableConditionIdType)(0)
/* The handles for each StorageCondition configured */
#define    DemConf_DemStorageCondition_DemStorageCondition0 (Dem_StorageConditionIdType)(0)
#define    DemConf_DemStorageCondition_DemStorageCondition1 (Dem_StorageConditionIdType)(1)

/*******************************************************************************
**                      Type Definitions                                      **
*******************************************************************************/

/* The type definition is generated as uint8 or uint16 based on the number of
 * Event Status functions for the event configured */

typedef uint16 Dem_NumOfEvtStatFctsType;

/* The type definition is generated as uint8 or uint16 based on the number of
 * DTC status functions configured for the DTC */

typedef uint8 Dem_NumOfDtcInitMOFType;

/* The type definition is generated as uint8 or uint16 based on the
   multiplicity of the configuration container DemRatioId */



/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary in logic */



#endif /* DEM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
