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
**  SRC-MODULE: Tm_1us32bit.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Time Service Module                                   **
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
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.1     24-Jun-2022   PhatCT         R44-Redmine #25858, #28232, #25857  **
** 1.0.0     19-Jun-2020   DanhLT2        Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Tm.h"                    /* Header file of Tm */
#include "Tm_Cfg.h"                /* Tm Cfg header file */
#include "Tm_Types.h"              /* Tm PCTypes file */
#include "Tm_Ram.h"                /* Tm Ram header file */
#include "Tm_Version.h"  
#if(TM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Det module Header file */
#endif
#include "Gpt.h"

/*******************************************************************************
**                      Global Types                                          **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name      : Tm_ResetTimer1us32bit                                 **
**                                                                            **
** Service ID         : 0x0c                                                  **
**                                                                            **
** Description        : Resets a timer instance (user point of view).         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant but not for the same timer instance         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : TimerPtr                                              **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : TM_ENABLE_PREDEFTIMER_1US_32BIT = STD_ON              **
**                                                                            **
** Remarks            : Global Variable(s) :None                              **
**                      Function(s) invoked:Det_ReportError,                  **
**                                          Det_ReportRuntimeError,           **
**                                          Gpt_GetPredefTimerValue.          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00369 SRS_BSW_00312 SRS_Tm_00001 SRS_Tm_00002 SRS_Tm_00003 SRS_Tm_00004 Tm_SUD_FILE_001 Tm_SUD_MACRO_006 */
#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)
#define TM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, TM_CODE) Tm_ResetTimer1us32bit(
        P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr)
{
  /* @Trace: Tm_SUD_API_013 */
  /* Declare local variables */
  /* @Trace: Tm_SUD_DATATYPE_001 */
  Std_ReturnType lddReturnVal;
  /* @Trace: Tm_SUD_DATATYPE_003 */
  Gpt_PredefTimerType lddPredefTimer;
  uint32 lulTimeValue;
  uint32 lulTimeSpanValue;
  /*Initialize return value */
  /* @Trace: Tm_SUD_MACRO_009 */
  lddReturnVal = E_NOT_OK;
  lulTimeValue = TM_32BIT_ZERO ;   
  if(NULL_PTR == TimerPtr)
  {
    #if (TM_DEV_ERROR_DETECT  == STD_ON)
    /* @Trace: Tm_SUD_API_015 */
    /* Report development error */
    (void)Det_ReportError(TM_MODULE_ID, TM_INSTANCE_ID,
        TM_RESETTIMER1US32BIT_SID, TM_E_PARAM_POINTER);
    #endif /* TM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: Tm_SUD_API_014 */
    /* Delivers the current value of the desired GPT Predef Timer */
    lddPredefTimer = GPT_PREDEF_TIMER_1US_32BIT;
    lddReturnVal = Gpt_GetPredefTimerValue(lddPredefTimer, &lulTimeValue);
    if(E_NOT_OK == lddReturnVal)
    {
      #if (TM_DEV_ERROR_DETECT  == STD_ON)
      /* @Trace: Tm_SUD_API_016 */
      /* Report runtime error */
      (void)Det_ReportRuntimeError(TM_MODULE_ID, TM_INSTANCE_ID,
        TM_RESETTIMER1US32BIT_SID, TM_E_HARDWARE_TIMER);
      #endif /* TM_DEV_ERROR_DETECT == STD_ON */
    }
    else
    {
      /* @Trace: Tm_SUD_API_017 */
      /* Set reference time of time instance = current time of the related 
      GPT Prefer Timer*/
      lulTimeSpanValue = lulTimeValue;
      TimerPtr->ui32RefTime = lulTimeSpanValue; /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimerPtr have data type is structure and it is checked not NULL so it is not having any impact" */
    }
  }
  /* @Trace: Tm_SUD_API_018 */
  /* Return of function */
  return lddReturnVal;
}
#define TM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

/*******************************************************************************
** Function Name      : Tm_GetTimeSpan1us32bit                                **
**                                                                            **
** Service ID         : 0x0d                                                  **
**                                                                            **
** Description        : Delivers the time difference (current time -          **
**                        reference time).                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : TimerPtr                                              **
**                                                                            **
** InOut Parameters   : TimeSpanPtr                                           **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : TM_ENABLE_PREDEFTIMER_1US_32BIT = STD_ON              **
**                                                                            **
** Remarks            : Global Variable(s) :None                              **
**                      Function(s) invoked:Det_ReportError,                  **
**                                          Det_ReportRuntimeError.           **
**                                          Gpt_GetPredefTimerValue.          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00369 SRS_BSW_00312 SRS:SRS_Tm_00001 SRS_Tm_00002 SRS_Tm_00003 SRS_Tm_00005 */
#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)
#define TM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, TM_CODE) Tm_GetTimeSpan1us32bit(
        P2CONST(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr, 
        P2VAR(uint32, AUTOMATIC, TM_APPL_CONST) TimeSpanPtr)
{
  /* @Trace: Tm_SUD_API_043 */
  /* Declare local variables */
  /* @Trace: Tm_SUD_DATATYPE_001 */
  Std_ReturnType lddReturnVal;
  /* @Trace: Tm_SUD_DATATYPE_003 */
  Gpt_PredefTimerType lddPredefTimer;
  uint32 lulTimeValue;
  uint32 lulCurTimeValue;
  uint32 lulRefTimeValue;
  uint32 lulTimeSpanValue;
  /*Initialize return value */
  /* @Trace: Tm_SUD_MACRO_009 */
  lddReturnVal = E_NOT_OK;
  lulTimeValue = TM_32BIT_ZERO ;   
  if((NULL_PTR == TimerPtr)||(NULL_PTR == TimeSpanPtr))
  {
    #if (TM_DEV_ERROR_DETECT  == STD_ON)
    /* @Trace: Tm_SUD_API_045 */
    /* Report development error */
    (void)Det_ReportError(TM_MODULE_ID, TM_INSTANCE_ID,
        TM_GETTIMESPAN1US32BIT_SID, TM_E_PARAM_POINTER);
    #endif /* TM_DEV_ERROR_DETECT == STD_ON */
    if (NULL_PTR != TimeSpanPtr)
    {
        /* @Trace: Tm_SUD_API_046 */
        /* Delivers the time span = 0  */
        *TimeSpanPtr = TM_32BIT_ZERO;  /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimeSpanPtr is checked not NULL so it is not having any impact" */
    }
	  else 
	  {
		/* do nothing*/
	  }
  }
  else
  {
    /* @Trace: Tm_SUD_API_044 */
    /* Delivers the current value of the desired GPT Predef Timer */
    lddPredefTimer = GPT_PREDEF_TIMER_1US_32BIT;
    lddReturnVal = Gpt_GetPredefTimerValue(lddPredefTimer, &lulTimeValue);
    if(E_NOT_OK == lddReturnVal)
    {
      #if (TM_DEV_ERROR_DETECT  == STD_ON)
      /* @Trace: Tm_SUD_API_047 */
      /* Report Runtime error */
      (void)Det_ReportRuntimeError(TM_MODULE_ID, TM_INSTANCE_ID,
        TM_GETTIMESPAN1US32BIT_SID, TM_E_HARDWARE_TIMER);
      #endif /* TM_DEV_ERROR_DETECT == STD_ON */
       /* @Trace: Tm_SUD_API_046 */
       /* Delivers time span = 0*/
      *TimeSpanPtr = TM_32BIT_ZERO; /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimeSpanPtr is checked not NULL so it is not having any impact" */
    }
    else
    {
      lulCurTimeValue = lulTimeValue & TM_32BIT_MASK;
      lulRefTimeValue = TimerPtr->ui32RefTime; /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimerPtr have data type is structure and it is checked not NULL so it is not having any impact" */
      if(lulCurTimeValue >= lulRefTimeValue)
      {
        /* @Trace: Tm_SUD_API_048 */
        /* Calculates time span */
        lulTimeSpanValue = lulCurTimeValue - lulRefTimeValue;
      }
      else
      {
        /* @Trace: Tm_SUD_API_049 */
        /* Calculates time span and Wrap around handling*/
        lulTimeSpanValue = TM_32BIT_MAX - (lulRefTimeValue - lulCurTimeValue
                                            - TM_32BIT_ONE);
      }
      /* @Trace: Tm_SUD_API_050 */
      /* Delivers the time span */
      *TimeSpanPtr = lulTimeSpanValue;/* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimeSpanPtr is checked not NULL so it is not having any impact" */
    }
  }
  /* @Trace: Tm_SUD_API_051 */
  /* return of function */
  return lddReturnVal;
}
#define TM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

/*******************************************************************************
** Function Name      : Tm_ShiftTimer1us32bit                                 **
**                                                                            **
** Service ID         : 0x0e                                                  **
**                                                                            **
** Description        : Shifts the reference time of the timer instance.      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : TimeValue                                             **
**                                                                            **
** InOut Parameters   : TimerPtr                                              **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : TM_ENABLE_PREDEFTIMER_1US_32BIT = STD_ON              **
**                                                                            **
** Remarks            : Global Variable(s) :None                              **
**                      Function(s) invoked:Det_ReportError.                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00369 SRS_BSW_00312 SRS_Tm_00001 SRS_Tm_00003 SRS_Tm_00006 */
#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)
#define TM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, TM_CODE) Tm_ShiftTimer1us32bit(
          P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr,
          uint32 TimeValue)
{
  /* @Trace: Tm_SUD_API_070 */
  /* Declare local variables */
  uint32 lulRefTimeValue;
  uint32 lulShiftTimeValue;
  uint32 lulTimeSpanValue;
  
  if(NULL_PTR == TimerPtr)
  {
    #if (TM_DEV_ERROR_DETECT  == STD_ON)
    /* @Trace: Tm_SUD_API_072 */
    /* Report development error */
    (void)Det_ReportError(TM_MODULE_ID, TM_INSTANCE_ID,
        TM_SHIFTTIMESPAN1US32BIT_SID, TM_E_PARAM_POINTER);
    #endif /* TM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: Tm_SUD_API_071 */
    /* Get new reference time of the timer instance */
    lulRefTimeValue = TimerPtr->ui32RefTime;  /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimerPtr have data type is structure and it is checked not NULL so it is not having any impact" */
    lulShiftTimeValue = TimeValue;
    lulTimeSpanValue = lulRefTimeValue + lulShiftTimeValue;
    TimerPtr->ui32RefTime = lulTimeSpanValue;
  }
}
#define TM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

/*******************************************************************************
** Function Name      : Tm_SyncTimer1us32bit                                  **
**                                                                            **
** Service ID         : 0x0f                                                  **
**                                                                            **
** Description        : Synchronizes two timer instances.                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant but not for the same destination            **
**                       timer instance                                       **
**                                                                            **
** Input Parameters   : TimerSrcPtr                                           **
**                                                                            **
** InOut Parameters   : TimerDstPtr                                           **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : TM_ENABLE_PREDEFTIMER_1US_32BIT = STD_ON              **
**                                                                            **
** Remarks            : Global Variable(s) :None                              **
**                      Function(s) invoked:Det_ReportError.                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00369 SRS_BSW_00312 SRS:SRS_Tm_00001 SRS_Tm_00003 SRS_Tm_00007 */
#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)
#define TM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, TM_CODE) Tm_SyncTimer1us32bit(
        P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerDstPtr,
        P2CONST(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerSrcPtr
            )
{
  if((NULL_PTR == TimerDstPtr)||(NULL_PTR == TimerSrcPtr))
  {
    #if (TM_DEV_ERROR_DETECT  == STD_ON)
    /* @Trace: Tm_SUD_API_081 */
    /* Report development error */
    (void)Det_ReportError(TM_MODULE_ID, TM_INSTANCE_ID,
        TM_SYNCTIMESPAN1US32BIT_SID, TM_E_PARAM_POINTER);
    #endif /* TM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: Tm_SUD_API_080 */
    /* set reference time of destination = reference time of source*/
    TimerDstPtr->ui32RefTime = TimerSrcPtr->ui32RefTime; /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer TimerDstPtr and TimerSrcPtr have data type is structure and it is checked not NULL so it is not having any impact" */
  }
}
#define TM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

/*******************************************************************************
** Function Name      : Tm_BusyWait1us32bit                                   **
**                                                                            **
** Service ID         : 0x10                                                  **
**                                                                            **
** Description        : Performs busy waiting by polling with a guaranteed    **
**                      minimum waiting time.                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : WaitingTimeMin                                        **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : TM_ENABLE_PREDEFTIMER_1US_32BIT = STD_ON              **
**                                                                            **
** Remarks            : Global Variable(s) :None                              **
**                      Function(s) invoked:Gpt_GetPredefTimerValue,          **
**                                          Det_ReportRuntimeError.           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00369 SRS_BSW_00312 SRS_Tm_00001 SRS_Tm_00003 SRS_Tm_00008 */
#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)
#define TM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, TM_CODE) Tm_BusyWait1us32bit(uint8 WaitingTimeMin)
{

  /* @Trace: Tm_SUD_API_108 */
  /* Declare local variables */
  /* @Trace: Tm_SUD_DATATYPE_001 */
  Std_ReturnType lddReturnVal;
  /* @Trace: Tm_SUD_DATATYPE_003 */
  Gpt_PredefTimerType lddPredefTimer;
  uint32 lulTimeValue;
  uint32 lulCurTimeValue;
  uint32 lulRefTimeValue;
  uint32 lulTimeSpanValue;
  lulTimeValue = TM_32BIT_ZERO ;   
  /* @Trace: Tm_SUD_API_109 */
  /* Declare lulLoopCountValue local variables */
  #if (TM_BUSY_WAIT_LOOP_ENABLE  == STD_ON)
  uint32 lulLoopCountValue;
  #endif /* TM_LOOP_WAIT_ENABLE == STD_ON */
  
  /* @Trace: Tm_SUD_API_110 */
  /* Delivers the current value of the desired GPT Predef Timer */
  lddPredefTimer = GPT_PREDEF_TIMER_1US_32BIT;
  lddReturnVal = Gpt_GetPredefTimerValue(lddPredefTimer, &lulTimeValue);
  if(E_NOT_OK == lddReturnVal)
  {
    #if (TM_DEV_ERROR_DETECT  == STD_ON) 
    /* @Trace: Tm_SUD_API_111 */
    /* Report Run time error */
    (void)Det_ReportRuntimeError(TM_MODULE_ID, TM_INSTANCE_ID,
      TM_BUSYWAIT1US32BIT_SID, TM_E_HARDWARE_TIMER);
    #endif /* TM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: Tm_SUD_API_112 */
    /* Initialize Time Span value and Refer Time value */
    lulRefTimeValue = lulTimeValue & TM_32BIT_MASK;
    lulTimeSpanValue = TM_32BIT_ZERO;
    while((lulTimeSpanValue<WaitingTimeMin)&&(E_OK == lddReturnVal)) /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "WaitingTimeMin and lddReturnVal have determined value so it is not having any impact" */
    {
      /* @Trace: Tm_SUD_API_113 */
      /* initialize lulLoopCountValue local variables */
	  /* @Trace: Tm_SUD_MACRO_006 */
      #if (TM_BUSY_WAIT_LOOP_ENABLE  == STD_ON)
      lulLoopCountValue = TM_BUSY_WAIT_LOOP_NUMBER;
      while(lulLoopCountValue > TM_32BIT_ZERO)
      {
        /* @Trace: Tm_SUD_API_115 */
        /* decrease lulLoopCountValue local variable*/ 
        lulLoopCountValue--;
      }
      #endif /* TM_LOOP_WAIT_ENABLE == STD_ON */
      /* @Trace: Tm_SUD_API_116 */
      /* Get Current Time value */
      lddReturnVal = Gpt_GetPredefTimerValue(lddPredefTimer, &lulTimeValue);
      if(E_NOT_OK == lddReturnVal)
      {
        #if (TM_DEV_ERROR_DETECT  == STD_ON) 
        /* @Trace: Tm_SUD_API_117 */
        /*Report Run time error */
        (void)Det_ReportRuntimeError(TM_MODULE_ID, TM_INSTANCE_ID,
          TM_BUSYWAIT1US32BIT_SID, TM_E_HARDWARE_TIMER);
        #endif /* TM_DEV_ERROR_DETECT == STD_ON */
      }
      else
      {
        lulCurTimeValue = lulTimeValue & TM_32BIT_MASK;
        if(lulCurTimeValue >= lulRefTimeValue)
        { 
        /* @Trace: Tm_SUD_API_118 */
        /* Measure time span */
          lulTimeSpanValue = lulCurTimeValue - lulRefTimeValue;
        }
        else
        {
        /* @Trace: Tm_SUD_API_119 */
        /* Measure time span and Wrap-around handling*/
          lulTimeSpanValue = TM_32BIT_MAX - (lulRefTimeValue - lulCurTimeValue 
                                            - TM_32BIT_ONE);
        }	
      }
    }
  }
  /* @Trace: Tm_SUD_API_114 */
  /* Return of function*/
  return lddReturnVal;
}
#define TM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/