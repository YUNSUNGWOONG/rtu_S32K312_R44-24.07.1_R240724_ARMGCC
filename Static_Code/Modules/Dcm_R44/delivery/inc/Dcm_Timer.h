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
**  SRC-MODULE: Dcm_Timer.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Timer                                        **
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
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-3035                    **
** 1.1.2     13-Nov-2023   DH Kwak        Refer #CP44-3122                    **
*******************************************************************************/

#ifndef DCM_TIMER_H
#define DCM_TIMER_H

#define DCM_TIMSTR_P2_SERVER_MIN      ((uint16)0x0000)
#define DCM_TIMSTR_P2_SERVER_MAX      ((uint16)50U)

#define DCM_TIMSTR_P2_STAR_SERVER_MIN ((uint16)0x0000)
#define DCM_TIMSTR_P2_STAR_SERVER_MAX ((uint16)5000U)

#define DCM_TIMSTR_S3_SERVER          ((uint16)0x1388)


// Macros to get/set Timing Params
#define P2_SERVER_MAX                     Dcm_GstCurrentTimingValue.Timer_P2ServerMax
#define P2_SERVER_ADJUST                  Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust
#define P2STAR_SERVER_MAX                 Dcm_GstCurrentTimingValue.Timer_P2StarServerMax
#define P2STAR_SERVER_ADJUST              Dcm_GstCurrentTimingValue.Timer_P2StarServerAdjust
#define S3_SERVER                         Dcm_GstCurrentTimingValue.Timer_S3Server

#define GET_TIMER_P2_SERVER_MAX           (P2_SERVER_MAX)
#define SET_TIMER_P2_SERVER_MAX(T)        (P2_SERVER_MAX = (T))

#define GET_TIMER_P2_SERVER_ADJUST        (P2_SERVER_ADJUST)
#define SET_TIMER_P2_SERVER_ADJUST(T)     (P2_SERVER_ADJUST = (T))

#define GET_TIMER_P2STAR_SERVER_MAX       (P2STAR_SERVER_MAX)
#define SET_TIMER_P2STAR_SERVER_MAX(T)    (P2STAR_SERVER_MAX = (T))

#define GET_TIMER_P2STAR_SERVER_ADJUST    (P2STAR_SERVER_ADJUST)
#define SET_TIMER_P2STAR_SERVER_ADJUST(T) (P2STAR_SERVER_ADJUST = (T))

#define GET_TIMER_S3_SERVER               (S3_SERVER)
#define SET_TIMER_S3_SERVER(T)            (S3_SERVER = (T))


/*******************************************************************************
**                            DCM Timing parameters                           **
*******************************************************************************/
typedef struct STagDcm_TimerServerType
{
  uint32 Timer_P2ServerMax;
  uint32 Timer_P2ServerAdjust;

  uint32 Timer_P2StarServerMax;
  uint32 Timer_P2StarServerAdjust;

  uint32 Timer_S3Server;
} Dcm_TimerServerType;

/*******************************************************************************
**                            DCM Timer Type                                  **
*******************************************************************************/
typedef enum 
{
  DCM_P2SERVERMAX_TIMER
  // , DCM_P2SERVERMIN_TIMER
  , DCM_WAIT_FULL_COM_TIMER
  , DCM_S3SERVER_TIMER

  #if (DCM_DSP_SECURITY_SERVICE == STD_ON)
  , DCM_SECURITY_TIMER
  #if (0 < DCM_NUM_OF_ATTEMPT_COUNTER_ENABLE)
  , DCM_READ_ATTEMPT_COUNTER_TIMER
  , DCM_WRITE_ATTEMPT_COUNTER_TIMER
  #endif
  #endif

  #if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
  , DCM_ROE_INTERMESSAGE_TIMER
  #endif

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  , DCM_PDID_SLOW_TIMER
  , DCM_PDID_MEDIUM_TIMER
  , DCM_PDID_FAST_TIMER
  #endif

  #if (0 < DCM_AUTHENTICATION_DEFAULT_SESSION_TIMEOUT)
  , DCM_AUTHENTICATION_DEFAULT_SESSION_TIMER
  #endif

  #if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
  , DCM_PERSIST_AUTHENTICATION_STATE_TIMER
  #endif

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  , DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER
  #endif

  #if(DCM_RESPONSE_ONEVENT_BLOCKID > 0)
  , DCM_ROE_ACCESS_NVRAM_TIMER
  #endif

  , TIMER_MAX_NUM
} Dcm_TimerType;

typedef P2FUNC(void, DCM_CODE, Dcm_TimerCallbackFunType)(void);

#define DCM_START_SEC_CODE
#include "MemMap.h"

// Abstract public functions provided for outside
extern FUNC(void, DCM_CODE) Dcm_InitTimers(Dcm_ConfigConstPtrType pConfig);

extern FUNC(void, DCM_CODE) Dcm_UpdateTimers(void);

extern FUNC(void, DCM_CODE) Dcm_StartTimerExt(
  Dcm_TimerType Timer
  , uint32 Time
  , Dcm_TimerCallbackFunType PendingCbk
  , Dcm_TimerCallbackFunType TimeoutCbk);

extern FUNC(void, DCM_CODE) Dcm_StartTimer(Dcm_TimerType Timer, uint32 Time);

extern FUNC(void, DCM_CODE) Dcm_StopTimer(Dcm_TimerType Timer);

extern FUNC(boolean, DCM_CODE) Dcm_IsTimerRunning(Dcm_TimerType Timer);

extern FUNC(boolean, DCM_CODE) Dcm_IsTimerExpired(Dcm_TimerType Timer);

extern FUNC(boolean, DCM_CODE) Dcm_IsTimerStarted(Dcm_TimerType Timer);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
