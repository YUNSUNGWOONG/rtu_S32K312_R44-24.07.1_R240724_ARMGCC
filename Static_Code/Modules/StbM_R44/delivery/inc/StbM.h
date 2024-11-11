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
**  SRC-MODULE: StbM.h                                                        **
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
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/
#ifndef STBM_H
#define STBM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* StbM types provided by the RTE */
#include "Rte_StbM_Type.h"
/* standard AUTOSAR types */
#include "Std_Types.h"
/* @Trace: StbM_SDD_DATATYPE_011 */
/* @Trace: StbM_SDD_DATATYPE_012 */
/* StbM module types */
#include "StbM_Types.h"

/* StbM configuration header */
/* @Trace: StbM_SDD_MACRO_009 */
/* @Trace: StbM_SDD_GLOBALVAR_005 */
#include "StbM_Cfg.h"

#include "StbM_Macro.h"

#include "StbM_Cbk.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* StbM instance ID */
#define STBM_INSTANCE_ID                        ((uint8) 0x00)

/* StbM Service ID */
/* @Trace: StbM_SDD_MACRO_010 */
#define STBM_GETVERSIONINFO_SID                 ((uint8) 0x05)

#define STBM_INIT_SID                           ((uint8) 0x00)

#define STBM_GETCURRENTTIME_SID                 ((uint8) 0x07)

#define STBM_GETCURRENTTIMEEXTENDED_SID         ((uint8) 0x08)

#define STBM_GETCURRENTVIRTUALLOCALTIME_SID     ((uint8) 0x1e)

#define STBM_SETGLOBALTIME_SID                  ((uint8) 0x0b)

#define STBM_UPDATEGLOBALTIME_SID               ((uint8) 0x10)

#define STBM_SETUSERDATA_SID                    ((uint8) 0x0c)

#define STBM_SETOFFSET_SID                      ((uint8) 0x0d)

#define STBM_GETOFFSET_SID                      ((uint8) 0x0e)

#define STBM_BUSGETCURRENTTIME_SID              ((uint8) 0x07)

#define STBM_BUSSETGLOBALTIME_SID               ((uint8) 0x0f)

#define STBM_GETRATEDEVIATION_SID               ((uint8) 0x11)

#define STBM_SETRATECORRECTION_SID              ((uint8) 0x12)

#define STBM_GETTIMELEAP_SID                    ((uint8) 0x13)

#define STBM_GETTIMEBASESTATUS_SID              ((uint8) 0x14)

#define STBM_STARTTIMER_SID                     ((uint8) 0x15)

#define STBM_GETSYNCTIMERECORDHEAD_SID          ((uint8) 0x16)

#define STBM_GETOFFSETTIMERECORDHEAD_SID        ((uint8) 0x17)

#define STBM_TRIGGERTIMETRANSMISSION_SID        ((uint8) 0x1c)

#define STBM_GETTIMEBASEUPDATECOUNTER_SID       ((uint8) 0x1b)

#define STBM_GETMASTERCONFIG_SID                ((uint8) 0x1d)

#define STBM_MAINFUNCTION_SID                   ((uint8) 0x04)

/*******************************************************************************
**                      StbM Error Codes                                      **
*******************************************************************************/
/* StbM_Init called with an invalid configuration pointer */
/* @Trace: StbM_SDD_MACRO_013 */
#define STBM_E_INIT_FAILED                   ((uint8)0x11)

/* API called while StbM is not initialized */
#define STBM_E_UNINIT                        ((uint8)0x0B)

/* API called with wrong parameter */
#define STBM_E_PARAM                         ((uint8)0x0A)

/* API called with invalid pointer in parameter list */
#define STBM_E_PARAM_POINTER                 ((uint8)0x10)

/* API disabled by configuration */
#define STBM_E_SERVICE_DISABLED              ((uint8)0x12)

/*******************************************************************************
**                          Macro Definitions                                 **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

#if (STD_ON == STBM_VERSION_INFO_API)
/* Returns the version information of StbM module */
extern FUNC(void, STBM_CODE) StbM_GetVersionInfo(
    P2VAR(Std_VersionInfoType, AUTOMATIC, STBM_APPL_DATA) versionInfo);
#endif /* STD_ON == STBM_VERSION_INFO_API */

/* Initializes the StbM module */
extern FUNC(void, STBM_CODE) StbM_Init(P2CONST(StbM_ConfigType,
  AUTOMATIC, STBM_APPL_DATA)ConfigPtr);

/* Returns a time value in standard format. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* @Trace: StbM_SDD_DATATYPE_024 */
#if (STD_ON == STBM_GET_CURRENT_TIME_EXTENDED)
/* Returns a time value in extended format. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeExtended(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampExtendedType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);
#endif /* STD_ON == STBM_GET_CURRENT_TIME_EXTENDED */

/* Returns the Virtual Local Time of the referenced Time Base. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr);

/* Allows the Customers to set the new global time that has to be valid */
/* for the system, which will be sent to the busses. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* Allows the Customers to set the Global Time */
/* that will be sent to the buses. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateGlobalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* Allows the Customers to set the new User Data. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_SetUserData(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* Allows the Customers and the Timesync Modules to */
/* set the Offset Time and the User Data. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_SetOffset(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* Allows the Timesync Modules to get the current */
/* Offset Time and User Data. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffset(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* Returns the current Time Tuple, status and User Data of the Time Base. */
extern  FUNC(Std_ReturnType, STBM_CODE) StbM_BusGetCurrentTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)globalTimePtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

/* Allows the Time Base Provider Modules to forward a new Global Time tuple */
/* (i.e., the Received Time Tuple) to the StbM. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)globalTimePtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA)measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr);

/* Returns value of the current rate deviation of a Time Base. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetRateDeviation(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_DATA)rateDeviation);

/* Allows to set the rate of a Synchronized Time Base */
/* (being either a Pure Local Time Base or not). */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_SetRateCorrection(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  VAR(StbM_RateDeviationType, AUTOMATIC)rateDeviation);

/* Returns value of Time Leap. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeLeap(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_APPL_DATA)timeJump);

/* Returns detailed status information for a Synchronized (or Pure Local) */
/* Time Base and, if called for an Offset Time Base, for the Offset Time */
/* Base and the underlying Synchronized Time Base. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeBaseStatus(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_DATA)syncTimeBaseStatus,
  P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_DATA)offsetTimeBaseStatus);

/* Sets a time value, which the Time Base value is compared against. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_StartTimer(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  VAR(StbM_CustomerIdType, AUTOMATIC)customerId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)expireTime);    

/* Accesses to the recorded snapshot data Header of the table belonging */ 
/* to the Synchronized Time Base. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetSyncTimeRecordHead(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_SyncRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA)syncRecordTableHead);

/* Accesses to the recorded snapshot data Header of the table belonging */
/* to the Offset Time Base. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeRecordHead(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_OffsetRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA)offsetRecordTableHead);

/* Called by the <Upper Layer> to force the Timesync Modules to transmit */
/* the current Time Base again due to an incremented */
/* timeBaseUpdateCounter[timeBaseId] */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_TriggerTimeTransmission(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId);

/* Allows the Timesync Modules to detect, whether a Time Base should be */
/* transmitted immediately in the subsequent <Bus>TSyn_MainFunction() cycle. */
extern FUNC(uint8, STBM_CODE) StbM_GetTimeBaseUpdateCounter(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId);

/* Indicates if the functionality for a system wide master */ 
/*(e.g. StbM_SetGlobalTime) for a given Time Base is available or not. */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_GetMasterConfig(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_MasterConfigType, AUTOMATIC, STBM_APPL_DATA)masterConfig);

/* Function called by BSW scheduler for StbM */
extern FUNC(void, STBM_CODE) StbM_MainFunction(void);

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* STBM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

