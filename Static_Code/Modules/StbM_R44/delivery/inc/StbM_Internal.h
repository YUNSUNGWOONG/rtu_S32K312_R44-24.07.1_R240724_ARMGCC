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
**  SRC-MODULE: StbM_Internal.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of internal functions and their functionality.      **
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
** 1.0.5           30-Nov-2022         NamNT1          ASPICE-76              **
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/
#ifndef STBM_INTERNAL_H
#define STBM_INTERNAL_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "StbM.h"

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/

/*******************************************************************************
**                          Global Data                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_GetVirtualLocalTime(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_GetCurrentTime(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)timeVlt,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)timeVltRx);

#if(STD_ON == STBM_TIME_RECORDING_SUPPORT)  
extern 
FUNC(void, STBM_CODE) StbM_Internal_WriteTimeRecordTable(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)globalTime,
  VAR(StbM_TimeBaseStatusType, AUTOMATIC)timeBaseStatus,
  #if(STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
  VAR(StbM_TimeStampType, AUTOMATIC)localTime, 
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)virtualTime, 
  VAR(StbM_MeasurementType, AUTOMATIC)measureDataPtr
  #endif /* STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED */
  );

extern FUNC(void, STBM_CODE) StbM_Internal_RecordSyncTimeBase(
  VAR(uint8, AUTOMATIC)ucBaseOfRecording,
  VAR(uint32, AUTOMATIC)GlbSeconds,
  VAR(uint32, AUTOMATIC)GlbNanoSeconds,
  VAR(uint8, AUTOMATIC)TimeBaseStatus, 
  VAR(uint32, AUTOMATIC)VirtualLocalTimeLow, 
  VAR(sint16, AUTOMATIC)RateDeviation, 
  VAR(uint32, AUTOMATIC)LocSeconds, 
  VAR(uint32, AUTOMATIC)LocNanoSeconds, 
  VAR(uint32, AUTOMATIC)PathDelay);

#if(STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED)
extern FUNC(void, STBM_CODE) StbM_Internal_RecordOffsetTimeBase(
  VAR(uint8, AUTOMATIC)ucBaseOfRecording,
  VAR(uint32, AUTOMATIC)GlbSeconds,
  VAR(uint32, AUTOMATIC)GlbNanoSeconds,
  VAR(uint8, AUTOMATIC)TimeBaseStatus);
#endif

extern FUNC(void, STBM_CODE) StbM_Internal_ReadTimeRecordTable(
  VAR(uint16, AUTOMATIC)lusConfigPtr);
#endif  /* STD_ON == STBM_TIME_RECORDING_SUPPORT */ 

extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_CheckTimeLeap(
  VAR(uint16,AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)localTime,
  VAR(StbM_TimeStampType, AUTOMATIC)globalTime);
  
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_CheckTimeOut(
  VAR(uint16,AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)globalTime);

extern FUNC(void, STBM_CODE) StbM_TimeNotificationCallback(void);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_UpdateStatusWithoutNotification(
  VAR(uint16, AUTOMATIC)localConfigPtr,
  VAR(uint8, AUTOMATIC) localStatusMask,
  VAR(boolean, AUTOMATIC) localStatusValue);
  
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_UpdateStatusOfTimeBase(
  VAR(uint16, AUTOMATIC)localConfigPtr,
  VAR(uint8, AUTOMATIC) localStatusMask,
  VAR(boolean, AUTOMATIC) localStatusValue);
  
extern FUNC(void, STBM_CODE) StbM_Internal_IncreaseCounterOfTimeBase(
  VAR(uint16, AUTOMATIC)localConfigPtr);
  
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_SlaveTimeCorrection(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)timeVlt); 
 
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_SlaveRateCorrection(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)timeStamp,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)timeVlt);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_CalRateDeviation(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_DATA)rateDeviation); 

extern FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_SetRateDeviation(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_RateDeviationType, AUTOMATIC)rateDeviation);

#if (STD_ON == STBM_TIME_NOTIFICATION_SUPPORT)
extern FUNC(void, STBM_CODE) StbM_Internal_TimerNotification(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp);
#endif

#if (STD_ON == STBM_TRIGGERED_CUSTOMER_SUPPORT)
extern FUNC(void, STBM_CODE) StbM_Internal_Trigger(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp);
#endif

#if (STD_ON == STBM_DEV_ERROR_DETECT)
extern FUNC(Std_ReturnType, STBM_CODE) StbM_CheckSyncOffsetTimeBaseID(
	Std_ReturnType	InputErr,
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint8 ServiceID);

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInvalid3Pointer(
	Std_ReturnType InputErr,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr1,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr2,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr3,
	uint8 ApiID);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInvalid2Pointer(
	Std_ReturnType InputErr,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr1,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr2,
	uint8 ApiID);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInvalid1Pointer(
	Std_ReturnType InputErr,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr,
	uint8 ApiID);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInitStatus(
	Std_ReturnType InputErr,
	uint8 ApiID);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimeBaseID(
	Std_ReturnType InputErr,
  StbM_SynchronizedTimeBaseType timeBaseId,
	uint8 ApiID);

#endif /* (STD_ON == STBM_DEV_ERROR_DETECT) */

#if(STD_ON == STBM_TIME_RECORDING_SUPPORT)
extern FUNC(void, STBM_CODE) StbM_InitTimeRecording(void);
#endif

extern FUNC(void, STBM_CODE) StbM_IntprocessOfBusSetGlobalTime(
		P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)globalTimePtr,
		VAR(uint16, AUTOMATIC)lusConfigPtr,
		P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData);

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
#endif /* STBM_INTERNAL_H */
