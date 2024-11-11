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
**  SRC-MODULE: StbM_Math.c                                                   **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* StbM module header */
#include "StbM_Math.h"

#include "StbM_MacroFunction.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : StbM_Math_SumOfTimeStampWithVlt                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localElapsedTimeStamp = localTimeStamp +            **
**                                 localVirtualLocalTime                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimeStamp: StbM_TimeStampType                  **
**                        localVirtualLocalTime: StbM_VirtualLocalTimeType    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTimeStamp: result                       **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Math_SumOfTimeStampWithVlt(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStamp,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVirtualLocalTime,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localElapsedTimeStamp)
{
  VAR(uint64, AUTOMATIC)lulNanosecondsValue;
  VAR(uint64, AUTOMATIC)lulSecondsValue;
  VAR(uint64, AUTOMATIC)lulTimeValue;
  /* @Trace: StbM_SUD_API_311 */
  /* Convert VirtualLocalTime to nano seconds */
  lulNanosecondsValue = ((uint64)(localVirtualLocalTime.nanosecondsLo)) | 
            (((uint64)(localVirtualLocalTime.nanosecondsHi))<<STBM_THIRTY_TWO);
  /* Add nanoseconds of localTimeStamp into nano seconds */
  lulNanosecondsValue = lulNanosecondsValue + 
                            (uint64)localTimeStamp.nanoseconds;
  /* Convert localTimeStamp to seconds */
  lulSecondsValue = (uint64)(localTimeStamp.seconds) | 
                    (((uint64)(localTimeStamp.secondsHi))<<STBM_THIRTY_TWO);
  /* Calculate seconds over*/
  lulTimeValue = lulNanosecondsValue / STBM_NANOSEC_SEC_IN_ONE_SEC;
  lulSecondsValue = lulSecondsValue + lulTimeValue;
  /* Set return value */
  localElapsedTimeStamp->nanoseconds = (uint32)
                        (lulNanosecondsValue % STBM_NANOSEC_SEC_IN_ONE_SEC);
  localElapsedTimeStamp->seconds = (uint32)
                        (lulSecondsValue & STBM_64BIT_LSB_MASK);
  localElapsedTimeStamp->secondsHi = (uint16)
                ((lulSecondsValue & STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO);
} /* End of StbM_Math_SumOfTimeStampWithVlt(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_DiffOfTwoVlt                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localElapsedTime = localTimeCurrent - localTimePre  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimePre: StbM_VirtualLocalTimeType             **
**                        localTimeCurrent: StbM_VirtualLocalTimeType         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTime: result                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Math_DiffOfTwoVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimePre,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimeCurrent,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;

  VAR(uint64, AUTOMATIC)lulTimePre;
  VAR(uint64, AUTOMATIC)lulTimeCurrent;
  VAR(uint64, AUTOMATIC)lulElapsedTime;
  
  lddReturnVal = E_OK;
  /* Convert VirtualLocalTime to nano seconds */
  lulTimePre = ((uint64)(localTimePre.nanosecondsLo)) | 
            (((uint64)(localTimePre.nanosecondsHi))<<STBM_THIRTY_TWO);
  
  lulTimeCurrent = ((uint64)(localTimeCurrent.nanosecondsLo)) | 
            (((uint64)(localTimeCurrent.nanosecondsHi))<<STBM_THIRTY_TWO);
  /* Convert into output format */
  /* @Trace: StbM_SUD_API_321 */
  if(lulTimeCurrent >= lulTimePre)
  {
    lulElapsedTime = lulTimeCurrent - lulTimePre;
    localElapsedTime->nanosecondsLo = (uint32)
                          (lulElapsedTime & STBM_64BIT_LSB_MASK);
    localElapsedTime->nanosecondsHi = (uint32)
                ((lulElapsedTime & STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO);
  }
  else
  /* @Trace: StbM_SUD_API_322 */
  {
    localElapsedTime->nanosecondsLo = (uint32)STBM_ZERO;
    localElapsedTime->nanosecondsHi = (uint32)STBM_ZERO;
    lddReturnVal = E_NOT_OK;
  }
  
  return (lddReturnVal);
} /* End of StbM_Math_DiffOfTwoVlt(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_CompareVlt                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : return (localTimeStamp <= localTimeThreshold)       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimeStamp: StbM_VirtualLocalTimeType           **
**                        localTimeThreshold: StbM_VirtualLocalTimeType       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Math_CompareVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimeStamp,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimeThreshold)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;

  VAR(uint64, AUTOMATIC)lulTimeThreshold;
  VAR(uint64, AUTOMATIC)lulTimeStamp;
  
  lddReturnVal = E_OK;
  /* Convert VirtualLocalTime to nano seconds */
  lulTimeThreshold = ((uint64)(localTimeThreshold.nanosecondsLo)) |
            (((uint64)(localTimeThreshold.nanosecondsHi))<<STBM_THIRTY_TWO);
  lulTimeStamp = ((uint64)(localTimeStamp.nanosecondsLo)) |
            (((uint64)(localTimeStamp.nanosecondsHi))<<STBM_THIRTY_TWO);
  /* Convert into output format */
  /* @Trace: StbM_SUD_API_331 */
  if(lulTimeStamp > lulTimeThreshold)
  {
    lddReturnVal = E_NOT_OK;
  }
  /* @Trace: StbM_SUD_API_332 */
  else
  {
    /* Do nothing */
  }
  
  return (lddReturnVal);
} /* End of StbM_Math_CompareVlt(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_SumOfTwoTimeStamp                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localElapsedTimeStamp = localTimeStamp +            **
**                                 localVirtualLocalTime                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimePre: StbM_TimeStampType                    **
**                        localTimeCurrent: StbM_TimeStampType                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTime: StbM_TimeStampType                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Math_SumOfTwoTimeStamp(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimePre,
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeCurrent,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime)
{
  
  VAR(uint32, AUTOMATIC)lulNanoSecondsElapsedTime;
  VAR(uint64, AUTOMATIC)lulSecondsTimePre;
  VAR(uint64, AUTOMATIC)lulSecondsTimeCurrent;
  VAR(uint64, AUTOMATIC)lulSecondsElapsedTime;

  /* Convert localTimeStamp to seconds */
  lulSecondsTimePre = (uint64)(localTimePre.seconds) | (((uint64)
                        (localTimePre.secondsHi))<<STBM_THIRTY_TWO);
  
  lulSecondsTimeCurrent = (uint64)(localTimeCurrent.seconds) | (((uint64)
                        (localTimeCurrent.secondsHi))<<STBM_THIRTY_TWO);

  lulSecondsElapsedTime = lulSecondsTimeCurrent + lulSecondsTimePre; 
  /* polyspace +3 DEFECT:UINT_OVFL [Not a defect:Low] "lulNanoSecondsElapsedTime is not able to reach max value of uint32" */
  /* polyspace +2 CERT-C:INT30-C [Not a defect:Low] "lulNanoSecondsElapsedTime is not able to reach max value of uint32" */
  lulNanoSecondsElapsedTime = localTimeCurrent.nanoseconds +
            localTimePre.nanoseconds;
  /* @Trace: StbM_SUD_API_341 */
  if((uint32)STBM_NANOSEC_SEC_IN_ONE_SEC <= lulNanoSecondsElapsedTime)
  {
    lulSecondsElapsedTime = lulSecondsElapsedTime + (uint64)STBM_ONE;
    lulNanoSecondsElapsedTime = lulNanoSecondsElapsedTime - 
                            STBM_NANOSEC_SEC_IN_ONE_SEC;
  }
  /* @Trace: StbM_SUD_API_342 */
  else
  {    
    /* Do nothing */
  }
  
  /* Set return value */
  localElapsedTime->nanoseconds = (uint32)lulNanoSecondsElapsedTime;
  localElapsedTime->seconds = (uint32)(lulSecondsElapsedTime & 
                                                  STBM_64BIT_LSB_MASK);
  localElapsedTime->secondsHi = (uint16)((lulSecondsElapsedTime & 
                                  STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO); 
} /* End of StbM_Math_SumOfTwoTimeStamp(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_DiffOfTwoTimeStamp                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localElapsedTime = localTimeCurrent - localTimePre  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimePre: StbM_TimeStampType                    **
**                        localTimeCurrent: StbM_TimeStampType                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTime: StbM_TimeStampType                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Math_DiffOfTwoTimeStamp(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimePre,
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeCurrent,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
  
  VAR(uint32, AUTOMATIC)lulNanoSecondsElapsedTime;
  VAR(uint64, AUTOMATIC)lulSecondsTimePre;
  VAR(uint64, AUTOMATIC)lulSecondsTimeCurrent;
  VAR(uint64, AUTOMATIC)lulSecondsElapsedTime;

  lddReturnVal = E_OK;
  /* Convert localTimeStamp to seconds */
  lulSecondsTimePre = (uint64)(localTimePre.seconds) | (((uint64)
                        (localTimePre.secondsHi))<<STBM_THIRTY_TWO);
  
  lulSecondsTimeCurrent = (uint64)(localTimeCurrent.seconds) | (((uint64)
                        (localTimeCurrent.secondsHi))<<STBM_THIRTY_TWO);
  /* @Trace: StbM_SUD_API_351 */
  if(lulSecondsTimeCurrent > lulSecondsTimePre)
  {
    lulSecondsElapsedTime = lulSecondsTimeCurrent - lulSecondsTimePre; 
    if(localTimeCurrent.nanoseconds >= localTimePre.nanoseconds)
    {
      lulNanoSecondsElapsedTime = localTimeCurrent.nanoseconds - 
              localTimePre.nanoseconds;
    }
    /* @Trace: StbM_SUD_API_352 */
    else
    {  
      lulSecondsElapsedTime = lulSecondsElapsedTime - (uint64)STBM_ONE;
      lulNanoSecondsElapsedTime = ( STBM_NANOSEC_SEC_IN_ONE_SEC - 
              localTimePre.nanoseconds ) + localTimeCurrent.nanoseconds;
    }
  }
  /* @Trace: StbM_SUD_API_353 */
  else if(lulSecondsTimeCurrent == lulSecondsTimePre )
  {
    lulSecondsElapsedTime = (uint64)STBM_ZERO;
    if(localTimeCurrent.nanoseconds >= localTimePre.nanoseconds)
    {
      lulNanoSecondsElapsedTime = localTimeCurrent.nanoseconds - 
              localTimePre.nanoseconds;
    }
    /* @Trace: StbM_SUD_API_354 */
    else
    {
      lulNanoSecondsElapsedTime = localTimePre.nanoseconds - 
              localTimeCurrent.nanoseconds;        
      /* Invaild input */
      lddReturnVal = E_NOT_OK;
    }
  }
  /* @Trace: StbM_SUD_API_355 */
  else
  {
    lulSecondsElapsedTime = lulSecondsTimePre - lulSecondsTimeCurrent; 
    if(localTimePre.nanoseconds >= localTimeCurrent.nanoseconds)
    {
      lulNanoSecondsElapsedTime = localTimePre.nanoseconds - 
              localTimeCurrent.nanoseconds;
    }
    /* @Trace: StbM_SUD_API_356 */
    else
    {  
      lulSecondsElapsedTime = lulSecondsElapsedTime - (uint64)STBM_ONE;
      lulNanoSecondsElapsedTime = ( STBM_NANOSEC_SEC_IN_ONE_SEC - 
              localTimeCurrent.nanoseconds ) + localTimePre.nanoseconds;
    }
    /* Invaild input */
    lddReturnVal = E_NOT_OK;
  }
  
  /* Set return value */
  localElapsedTime->nanoseconds = (uint32)lulNanoSecondsElapsedTime;
  localElapsedTime->seconds = (uint32)(lulSecondsElapsedTime & 
                                                  STBM_64BIT_LSB_MASK);
  localElapsedTime->secondsHi = (uint16)((lulSecondsElapsedTime & 
                                  STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO); 
  return (lddReturnVal);
} /* End of StbM_Math_DiffOfTwoTimeStamp(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_ConvertTimeStamp                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Convert StbM_TimeStampType to  uint64               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimeStamp: StbM_TimeStampType                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTime: uint64                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Math_ConvertTimeStampToRaw(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStamp,
  P2VAR(uint64, AUTOMATIC, STBM_APPL_DATA)localTimeRaw)
{ 
  VAR(uint64, AUTOMATIC)lulTimeStamp;
  /* @Trace: StbM_SUD_API_361 */
  /* Convert localTimeStamp to seconds */
  lulTimeStamp = (uint64)(localTimeStamp.seconds) | (((uint64)
                        (localTimeStamp.secondsHi))<<STBM_THIRTY_TWO);
  /* Convert localTimeStamp to nano seconds */
  lulTimeStamp = lulTimeStamp * STBM_NANOSEC_SEC_IN_ONE_SEC;
  lulTimeStamp = lulTimeStamp + localTimeStamp.nanoseconds;

  *localTimeRaw = lulTimeStamp;
} /* End of StbM_Math_ConvertTimeStamp(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_MultRateWithVlt                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localElapsedTime = localRate * localTimePre         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimePre: StbM_VirtualLocalTimeType             **
**                        localRate: StbM_RateCorrectionType                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTime: StbM_VirtualLocalTimeType         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Math_MultRateWithVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimePre,
  VAR(StbM_RateCorrectionType, AUTOMATIC)localRate,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime)
{
  VAR(uint64, AUTOMATIC)lulNanosecondsValue;
  VAR(uint64, AUTOMATIC)lulElapsedTime;
  /* @Trace: StbM_SUD_API_371 */
  /* Convert VirtualLocalTime to nano seconds */
  lulNanosecondsValue = ((uint64)(localTimePre.nanosecondsLo)) | 
            (((uint64)(localTimePre.nanosecondsHi))<<STBM_THIRTY_TWO);
  /* Multi with rate ppm */
  lulElapsedTime = lulNanosecondsValue * localRate;
  
  lulElapsedTime = lulElapsedTime / STBM_RATE_CORRECTION_ONE;
  /* Convert into output format */  
  localElapsedTime->nanosecondsLo = (uint32)
                        (lulElapsedTime & STBM_64BIT_LSB_MASK);
  localElapsedTime->nanosecondsHi = (uint32)
              ((lulElapsedTime & STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO);
} /* End of StbM_Math_MultRateWithVlt(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_SumOfNumberWithVlt                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localElapsedTime = localNumber + localTimePre       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimePre: StbM_VirtualLocalTimeType             **
**                        localNumber: uint32                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localElapsedTime: StbM_VirtualLocalTimeType         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Math_SumOfNumberWithVlt(
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localTimePre,
  VAR(uint32, AUTOMATIC)localNumber,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localElapsedTime)
{
  VAR(uint64, AUTOMATIC)lulNanosecondsValue;
  VAR(uint64, AUTOMATIC)lulElapsedTime;
  /* @Trace: StbM_SUD_API_381 */
  /* Convert VirtualLocalTime to nano seconds */
  lulNanosecondsValue = ((uint64)(localTimePre.nanosecondsLo)) | 
            (((uint64)(localTimePre.nanosecondsHi))<<STBM_THIRTY_TWO);
  /* Sum of with rate ppm */
  lulElapsedTime = lulNanosecondsValue + localNumber;
  /* Convert into output format */  
  localElapsedTime->nanosecondsLo = (uint32)
                        (lulElapsedTime & STBM_64BIT_LSB_MASK);
  localElapsedTime->nanosecondsHi = (uint32)
              ((lulElapsedTime & STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO);
} /* End of StbM_Math_SumOfNumberWithVlt(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_CalRateCorrection                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : rate = delta of TimeStamp / delta of Vlt            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localTimeStampStart: StbM_TimeStampType             **
**                        localTimeStampStop: StbM_TimeStampType              **
**                        localVltStart: StbM_VirtualLocalTimeType            **
**                        localVltStop: StbM_VirtualLocalTimeType             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localRate: StbM_RateCorrectionType                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Math_CalRateCorrection(
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStampStart,
  VAR(StbM_TimeStampType, AUTOMATIC)localTimeStampStop,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVltStart,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVltStop,
  P2VAR(StbM_RateCorrectionType, AUTOMATIC, STBM_APPL_DATA)localRate)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
  
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStampElapsed;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVltElapsed;
  VAR(uint64, AUTOMATIC)lddRate;
  VAR(uint64, AUTOMATIC)lulTimeStamp;
  VAR(uint64, AUTOMATIC)lulVltTime;
  
  lulVltTime = (uint64)STBM_ZERO;
  lddReturnVal = StbM_Math_DiffOfTwoVlt(localVltStart, localVltStop, 
                                        &lddVltElapsed);
  if(E_OK == lddReturnVal)
  {
    /* Convert VirtualLocalTime to nano seconds */
    lulVltTime = ((uint64)(lddVltElapsed.nanosecondsLo)) | 
            (((uint64)(lddVltElapsed.nanosecondsHi))<<STBM_THIRTY_TWO);
    /* @Trace: StbM_SUD_API_393 */
    if((uint64)STBM_ZERO == lulVltTime)
    {
      lddReturnVal = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    /* Do nothing */
  }
  /* @Trace: StbM_SUD_API_391 */
  if(E_OK == lddReturnVal)
  {
    lddReturnVal = StbM_Math_DiffOfTwoTimeStamp(localTimeStampStart, 
                    localTimeStampStop, &lddTimeStampElapsed);
    if(E_OK == lddReturnVal)
    {
      /* Convert TimeStamp to nano seconds */
      lulTimeStamp = (uint64)(lddTimeStampElapsed.seconds) | (((uint64)
                        (lddTimeStampElapsed.secondsHi))<<STBM_THIRTY_TWO);
      lulTimeStamp = lulTimeStamp * STBM_NANOSEC_SEC_IN_ONE_SEC;
      lulTimeStamp = lulTimeStamp + lddTimeStampElapsed.nanoseconds;
      /* Calculate */
      lddRate = lulTimeStamp * STBM_RATE_CORRECTION_ONE;
      lddRate = lddRate / lulVltTime;
      *localRate = (StbM_RateCorrectionType)lddRate;
    }
    else
    {
      /* @Trace: StbM_SUD_API_392 */
      *localRate = STBM_RATE_CORRECTION_ZERO;
    }
  }
  else
  {
    /* @Trace: StbM_SUD_API_394 */
    *localRate = STBM_RATE_CORRECTION_ZERO;
  }
  
  return (lddReturnVal);
} /* End of StbM_Math_CalRateCorrection(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Math_TimeStampInterpolate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : localTimeStamp = localTimeTuple +                   **
**                            localRate*delta of Vlt                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : localRate: StbM_TimeStampType                       **
**                        localTimeTuple: StbM_TimeTupleType                  **
**                        localVlt: StbM_VirtualLocalTimeType                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localTimeStamp: StbM_TimeStampType                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : StbM_Math_DiffOfTwoVlt,       **
**                             StbM_Math_MultRateWithVlt,                     **
**                             StbM_Math_SumOfTimeStampWithVlt                **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Math_TimeStampInterpolate(
  VAR(StbM_RateCorrectionType, AUTOMATIC)localRate,
  VAR(StbM_TimeTupleType, AUTOMATIC)localTimeTuple,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)localVlt,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)localTimeStamp)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
 
  VAR(StbM_TimeStampType, AUTOMATIC) lddLocalTupe;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC) lddVltTuple;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC) lddVltElapsed;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC) lddVltRatio;

  lddReturnVal = E_OK;
  /* Get local time tupe and Vlt time tupe */
  lddLocalTupe = localTimeTuple.ddLocalTime;
  lddVltTuple = localTimeTuple.ddVirtualLocalTime;
  /* Check rate in special cases */
  /* @Trace: StbM_SUD_API_401 */
  if(STBM_RATE_CORRECTION_ZERO == localRate)
  {
    localTimeStamp->nanoseconds = lddLocalTupe.nanoseconds;
    localTimeStamp->seconds = lddLocalTupe.seconds;
    localTimeStamp->secondsHi = lddLocalTupe.secondsHi;
  }
  /* @Trace: StbM_SUD_API_402 */
  else if(STBM_RATE_CORRECTION_ONE == localRate)
  {
    lddReturnVal = StbM_Math_DiffOfTwoVlt(lddVltTuple, localVlt, 
                                        &lddVltElapsed);

    StbM_Math_SumOfTimeStampWithVlt(lddLocalTupe, lddVltElapsed, 
                                        localTimeStamp);
  }
  /* In other case */
  /* @Trace: StbM_SUD_API_403 */
  else
  {
    lddReturnVal = StbM_Math_DiffOfTwoVlt(lddVltTuple, localVlt, 
                                        &lddVltElapsed);

    StbM_Math_MultRateWithVlt(lddVltElapsed, localRate, 
                                        &lddVltRatio);

    StbM_Math_SumOfTimeStampWithVlt(lddLocalTupe, lddVltRatio,  
                                        localTimeStamp);
  }
  
  return (lddReturnVal);
} /* End of StbM_Math_TimeStampInterpolate(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
