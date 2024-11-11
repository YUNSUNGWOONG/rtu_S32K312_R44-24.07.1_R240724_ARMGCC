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
**  SRC-MODULE: Dcm_Timer.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provided API for Dcm timer handling                           **
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
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     10-Jul-2020   SonDT1         Changes made as per #14476          **
** 0.0.3     16-Aug-2020   HueKM          Change periodic timer name          **
** 0.0.4     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     18-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-3035                    **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Timer.h"

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
typedef struct
{
  boolean StartFlag;
  uint32 Time;
  Dcm_TimerCallbackFunType PendingCbk;
  Dcm_TimerCallbackFunType TimeoutCbk;
} Dcm_TimerInfoType;

typedef P2VAR(Dcm_TimerInfoType, AUTOMATIC, DCM_APPL_DATA) Dcm_TimerInfoPtrType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_TimerInfoType, DCM_VAR) Dcm_GaaTimerInfo[TIMER_MAX_NUM];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Static Functions Declaration                          **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

// private getter/setter
static FUNC(Dcm_TimerInfoPtrType, DCM_CODE) Dcm_GetTimerInfoPtr(
  Dcm_TimerType Timer);

static FUNC(void, DCM_CODE) Dcm_SetTimerInfo(
  Dcm_TimerType Timer
  , boolean StartFlag
  , uint32 Time
  , Dcm_TimerCallbackFunType PendingCbk
  , Dcm_TimerCallbackFunType TimeoutCbk);

/*******************************************************************************
** Function Name        : Dcm_InitTimers                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function Dcm timer initialize                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init must be called before call this fucntion   **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_SetTimerInfo                      **
**                                                                            **
*******************************************************************************/
// Abstract public functions provided for outside
FUNC(void, DCM_CODE) Dcm_InitTimers(Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_10200 */
  for (uint16 Timer = 0; Timer < (uint16) TIMER_MAX_NUM; Timer++)
  {
    /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
    Dcm_SetTimerInfo((Dcm_TimerType) Timer, DCM_FALSE, 0, NULL_PTR, NULL_PTR);
  }

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_UpdateTimers                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function update Dcm available timer                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetTimerInfoPtr                   **
**                                      Dcm_StopTimer                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UpdateTimers(void)
{
  /* @Trace: Dcm_SUD_API_10201 */
  Dcm_TimerInfoPtrType pTimer = NULL_PTR;
  Dcm_TimerCallbackFunType pCbkFun = NULL_PTR;

  for (uint16 Timer = 0; Timer < (uint16) TIMER_MAX_NUM; Timer++)
  {
    /* @Trace: Dcm_SUD_API_10202 */
    /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
    pTimer = Dcm_GetTimerInfoPtr((Dcm_TimerType) Timer);

    if (DCM_FALSE == pTimer->StartFlag)
    {
      continue;
    }

    if (0 < pTimer->Time)
    {
      /* @Trace: Dcm_SUD_API_10203 */
      pTimer->Time--;
    }

    /* @Trace: Dcm_SUD_API_10216 Dcm_SUD_API_10217 */
    pCbkFun = (0 < pTimer->Time) ? pTimer->PendingCbk : pTimer->TimeoutCbk;

    if (NULL_PTR != pCbkFun)
    {
      /* @Trace: Dcm_SUD_API_10204 */
      pCbkFun();

      if (pCbkFun == pTimer->TimeoutCbk)
      {
        /* @Trace: Dcm_SUD_API_10205 */
        /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
        Dcm_StopTimer((Dcm_TimerType) Timer);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_StartTimerExt                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function start Dcm available timer                  **
**                        and invoked setup function                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer, Time, PendingCbk, TimeoutCbk                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_SetTimerInfo                      **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StartTimerExt(
  Dcm_TimerType Timer
  , uint32 Time
  , Dcm_TimerCallbackFunType PendingCbk
  , Dcm_TimerCallbackFunType TimeoutCbk)
{
  /* @Trace: Dcm_SUD_API_10206 */
  Dcm_SetTimerInfo(Timer, DCM_TRUE, Time, PendingCbk, TimeoutCbk);
}

/*******************************************************************************
** Function Name        : Dcm_StartTimer                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function start Dcm available timer                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer, Time                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_SetTimerInfo                      **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StartTimer(Dcm_TimerType Timer, uint32 Time)
{
  /* @Trace: Dcm_SUD_API_10207 */
  Dcm_SetTimerInfo(Timer, DCM_TRUE, Time, NULL_PTR, NULL_PTR);
}

/*******************************************************************************
** Function Name        : Dcm_StopTimer                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function stop Dcm available timer                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_SetTimerInfo                      **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StopTimer(Dcm_TimerType Timer)
{
  /* @Trace: Dcm_SUD_API_10208 */
  Dcm_SetTimerInfo(Timer, DCM_FALSE, 0, NULL_PTR, NULL_PTR);
}

/*******************************************************************************
** Function Name        : Dcm_IsTimerRunning                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check a timer is runing or not             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetTimerInfoPtr                   **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsTimerRunning(Dcm_TimerType Timer)
{
  /* @Trace: Dcm_SUD_API_10209 */
  boolean LblRetVal = DCM_FALSE;
  Dcm_TimerInfoPtrType pTimer = Dcm_GetTimerInfoPtr(Timer);

  if ((DCM_TRUE == pTimer->StartFlag) && ((uint16) DCM_ZERO < pTimer->Time))
  {
    /* @Trace: Dcm_SUD_API_10210 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsTimerExpired                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check a timer expired or not               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetTimerInfoPtr                   **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsTimerExpired(Dcm_TimerType Timer)
{
  /* @Trace: Dcm_SUD_API_10211 */
  boolean LblRetVal = DCM_FALSE;
  Dcm_TimerInfoPtrType pTimer = Dcm_GetTimerInfoPtr(Timer);

  if ((DCM_TRUE == pTimer->StartFlag) && ((uint16) DCM_ZERO == pTimer->Time))
  {
    /* @Trace: Dcm_SUD_API_10212 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsTimerStarted                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check a timer is started or not            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetTimerInfoPtr                   **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsTimerStarted(Dcm_TimerType Timer)
{
  /* @Trace: Dcm_SUD_API_10213 */
  Dcm_TimerInfoPtrType pTimer = Dcm_GetTimerInfoPtr(Timer);
  return (pTimer->StartFlag);
}

/*******************************************************************************
** Function Name        : Dcm_GetTimerInfoPtr                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function get status of a timer                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_TimerInfoPtrType                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaTimerInfo              **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_TimerInfoPtrType, DCM_CODE) Dcm_GetTimerInfoPtr(
  Dcm_TimerType Timer)
{
  /* @Trace: Dcm_SUD_API_10214 */
  return &Dcm_GaaTimerInfo[Timer];
}

/*******************************************************************************
** Function Name        : Dcm_SetTimerInfo                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to set status of a timer                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Timer, StartFlag, Time, PendingCbk, TimeoutCbk      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaTimerInfo              **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetTimerInfo(
  Dcm_TimerType Timer
  , boolean StartFlag
  , uint32 Time
  , Dcm_TimerCallbackFunType PendingCbk
  , Dcm_TimerCallbackFunType TimeoutCbk)
{
  /* @Trace: Dcm_SUD_API_10215 */
  SchM_Enter_Dcm_TimerProtection();
  Dcm_TimerInfoPtrType pTimer = &Dcm_GaaTimerInfo[Timer];
  pTimer->StartFlag = StartFlag;
  pTimer->Time = (Time / DCM_TASK_TIME);
  pTimer->PendingCbk = PendingCbk;
  pTimer->TimeoutCbk = TimeoutCbk;
  SchM_Exit_Dcm_TimerProtection();  
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
