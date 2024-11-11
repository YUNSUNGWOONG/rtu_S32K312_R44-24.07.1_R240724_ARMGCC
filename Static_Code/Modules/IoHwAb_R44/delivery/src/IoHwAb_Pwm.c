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
**  SRC-MODULE: IoHwAb_Pwm.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_PwmSetDutyCycle                                        **
**              IoHwAb_PwmSetPeriodAndDuty                                    **
**              IoHwAb_PwmSetOutputToIdle                                     **
**              IoHwAb_PwmGetOutputState                                      **
**              IoHwAb_PwmDisableNotification                                 **
**              IoHwAb_PwmEnableNotification                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.2.0     18-Nov-2021  PhucNHM           R44-Redmine #18098                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Pwm.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Config.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (defined(IOHWAB_MCAL_INFINEON_TC33X)) || (defined(IOHWAB_MCAL_INFINEON_TC36X)) \
 || (defined(IOHWAB_MCAL_INFINEON_TC37X)) || (defined(IOHWAB_MCAL_INFINEON_TC38X)) \
 || (defined(IOHWAB_MCAL_INFINEON_TC39X))

#ifndef PWM_LOW
#define PWM_LOW PWM_17_GTMCCU6_LOW
#endif

#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_PWM == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_PwmSetDutyCycle                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the duty cycle value of        **
**                        corresponding PWM channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Duty                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmSetDutyCycle                          **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12414 SRS_IoHwAb_12445*/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_401_001 */
/* @Trace: IoHwAb_SUD_API_029 */
#if (IOHWAB_PWM_SET_DUTY_CYCLE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmSetDutyCycle(IoHwAb_IndexType ChIdx,
  uint16 Duty)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmSetDutyCycle != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_PWM_NUM_LGC))
  {
    IoHwAb_GpPwmSetDutyCycle(IoHwAb_GaaPwmChIdx[ChIdx], (uint16)Duty);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_SET_DUTY_CYCLE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmSetPeriodAndDuty                          **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes both the period and duty cycle **
**                        value of corresponding PWM channel.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Period, Duty                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmSetPeriodAndDuty                      **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12416 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_401_002 */
/* @Trace: IoHwAb_SUD_API_030 */
#if (IOHWAB_PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmSetPeriodAndDuty(IoHwAb_IndexType ChIdx,
  IoHwAb_PwmPeriodType Period, uint16 Duty)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmSetPeriodAndDuty != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_PWM_NUM_LGC))
  {
    IoHwAb_GpPwmSetPeriodAndDuty(IoHwAb_GaaPwmChIdx[ChIdx], (Pwm_PeriodType)Period,
      (uint16)Duty);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_SET_PERIOD_AND_DUTY_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmSetOutputToIdle                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes output pin of corresponding    **
                           PWM channel to idle state.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmSetOutputToIdle                       **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_402_001 */
/* @Trace: IoHwAb_SUD_API_031 */
#if (IOHWAB_PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmSetOutputToIdle(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmSetOutputToIdle != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_PWM_NUM_LGC))
  {
    IoHwAb_GpPwmSetOutputToIdle(IoHwAb_GaaPwmChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmGetOutputState                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the output state of              **
**                        corresponding PWM channel to idle state.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmGetOutputState                        **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12411 SRS_IoHwAb_12417 */ 
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_402_002 */
/* @Trace: IoHwAb_SUD_API_032 */ 
#if (IOHWAB_PWM_GET_OUTPUT_STATE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmGetOutputState(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmGetOutputState != IOHWAB_NULL_PTR) && 
      (Level != NULL_PTR)&&
      (ChIdx < IOHWAB_PWM_NUM_LGC))
  {
    if (PWM_LOW == IoHwAb_GpPwmGetOutputState(IoHwAb_GaaPwmChIdx[ChIdx]))
    {
      *Level = IOHWAB_LOW;
    }
    else
    {
      *Level = IOHWAB_HIGH;
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_GET_OUTPUT_STATE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding PWM channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmDisableNotification                   **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_403_002 */
/* @Trace: IoHwAb_SUD_API_033 */
#if (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON)
/** IoHwAb_PwmDisableNotification */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmDisableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmDisableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_PWM_NUM_LGC))
  {
    IoHwAb_GpPwmDisableNotification(IoHwAb_GaaPwmChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding PWM channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, NotificationEdge                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmEnableNotification                    **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00122 SWS_IoHwAb_00105 SWR_IOHWAB_403_001 */
/* @Trace: IoHwAb_SUD_API_034 */
#if (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON)
/** IoHwAb_PwmEnableNotification */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmEnableNotification(IoHwAb_IndexType ChIdx,
  IoHwAb_PwmEdgeType NotificationEdge)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmEnableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_PWM_NUM_LGC))
  {
    if (NotificationEdge == IOHWAB_RISING_EDGE)
    {
      IoHwAb_GpPwmEnableNotification(IoHwAb_GaaPwmChIdx[ChIdx],
        (Pwm_EdgeNotificationType)PWM_RISING_EDGE);
    }
    else if (NotificationEdge == IOHWAB_FALLING_EDGE)
    {
      IoHwAb_GpPwmEnableNotification(IoHwAb_GaaPwmChIdx[ChIdx],
        (Pwm_EdgeNotificationType)PWM_FALLING_EDGE);
    }
    else
    {
      IoHwAb_GpPwmEnableNotification(IoHwAb_GaaPwmChIdx[ChIdx],
        (Pwm_EdgeNotificationType)PWM_BOTH_EDGES);
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON) */

#endif /* (IOHWAB_USE_PWM == STD_ON) */

/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
