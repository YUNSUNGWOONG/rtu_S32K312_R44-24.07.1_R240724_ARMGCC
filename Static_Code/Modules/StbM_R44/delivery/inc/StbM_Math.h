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
**  SRC-MODULE: StbM_Math.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of mathematical functions and their functionality.  **
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
#ifndef STBM_MATH_H
#define STBM_MATH_H

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

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
/* localElapsedTimeStamp = localTimeStamp + localVirtualLocalTime */
extern FUNC(void, STBM_CODE) StbM_Math_SumOfTimeStampWithVlt(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStamp,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVirtualLocalTime,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localElapsedTimeStamp);

/* localElapsedTime = localTimeCurrent - localTimePre */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Math_DiffOfTwoVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimePre,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimeCurrent,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime);

extern FUNC(Std_ReturnType, STBM_CODE) StbM_Math_CompareVlt(
          VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimeStamp,
          VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimeThreshold);

/* localElapsedTime = localTimeCurrent - localTimePre */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Math_DiffOfTwoTimeStamp(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimePre,
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeCurrent,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime);

extern FUNC(void, STBM_CODE) StbM_Math_SumOfTwoTimeStamp(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimePre,
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeCurrent,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime);

extern FUNC(void, STBM_CODE) StbM_Math_ConvertTimeStampToRaw(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStamp,
  P2VAR(uint64, AUTOMATIC, STBM_APPL_DATA)localTimeRaw);
  
/* localElapsedTime = localRate * localTimePre */
extern FUNC(void, STBM_CODE) StbM_Math_MultRateWithVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimePre,
  VAR(StbM_RateCorrectionType, AUTOMATIC)localRate,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime);
  
/* localElapsedTime = localNumber + localTimePre */ 
extern FUNC(void, STBM_CODE) StbM_Math_SumOfNumberWithVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimePre,
  VAR(uint32, AUTOMATIC)localNumber,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime);
 
/* rate = delta of TimeStamp / delta of Vlt */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Math_CalRateCorrection(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStampStart,
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStampStop,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVltStart,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVltStop,
  P2VAR(StbM_RateCorrectionType, AUTOMATIC, STBM_APPL_DATA)localRate);

/* localTimeStamp = localTimeTuple + localRate * delta of Vlt */
extern FUNC(Std_ReturnType, STBM_CODE) StbM_Math_TimeStampInterpolate(
  VAR(StbM_RateCorrectionType, AUTOMATIC)localRate,
  VAR(StbM_TimeTupleType, AUTOMATIC)localTimeTuple,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVlt,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localTimeStamp);

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* STBM_MATH_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
