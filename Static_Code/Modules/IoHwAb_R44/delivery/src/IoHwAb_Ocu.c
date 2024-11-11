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
**  SRC-MODULE: IoHwAb_Ocu.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_Ocu_StartChannel                                       **
**              IoHwAb_Ocu_StopChannel                                        **
**              IoHwAb_Ocu_SetPinState                                        **
**              IoHwAb_Ocu_SetPinAction                                       **
**              IoHwAb_Ocu_GetCounter                                         **
**              IoHwAb_Ocu_SetAbsoluteThreshold                               **
**              IoHwAb_Ocu_SetRelativeThreshold                               **
**              IoHwAb_Ocu_EnableNotification                                 **
**              IoHwAb_Ocu_DisableNotification                                **
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
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_IoHwAb.h"
#include "IoHwAb_Ocu.h"
#include "IoHwAb_Config.h"

#if (IOHWAB_USE_OCU == STD_ON)
#include "Ocu.h"
#include "Ocu_Cfg.h"
#endif /* (IOHWAB_USE_OCU == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_OCU == STD_ON)

#if (IOHWAB_OCU_START_CHANNEL_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuStartChannel                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts the timer of the corresponding  **
**                        OCU channel.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Value                                        **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuStartTimer                            **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_001 */
/* @Trace: IoHwAb_SUD_API_058 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuStartChannel(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuStartChannel != IOHWAB_NULL_PTR)&&
     (ChIdx < IOHWAB_OCU_NUM_LGC))
  {
    IoHwAb_GpOcuStartChannel(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_START_CHANNEL_API == STD_ON) */


#if (IOHWAB_OCU_STOP_CHANNEL_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuStopTimer                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops the timer of the corresponding   **
**                        OCU channel.                                        **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuStopTimer                             **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_002 */
/* @Trace: IoHwAb_SUD_API_059 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuStopChannel(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuStopChannel != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_OCU_NUM_LGC))
  {
    IoHwAb_GpOcuStopChannel(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_STOP_CHANNEL_API == STD_ON) */


#if (IOHWAB_OCU_GET_COUNTER_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuGetCounter                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service get the counter values from            **
                          the corresponding OCU channel                       **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuGetCounter                            **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_005 */
/* @Trace: IoHwAb_SUD_API_060 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuGetCounter(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_OcuValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuGetCounter != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_OCU_NUM_LGC)&&
      (Value != IOHWAB_NULL_PTR))
  {
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    *Value = (IoHwAb_OcuValueType)IoHwAb_GpOcuGetCounter(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_GET_COUNTER_API == STD_ON) */


#if (IOHWAB_OCU_SET_PIN_STATE_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetPinState                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service Set the Output Pin State of            **
                          the corresponding OCU channel                       **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetState                              **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_003 */
/* @Trace: IoHwAb_SUD_API_061 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetPinState(IoHwAb_IndexType ChIdx, IoHwAb_OcuPinStateType PinState)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuSetPinState != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_OCU_NUM_LGC))
  {
    IoHwAb_GpOcuSetPinState(IoHwAb_GaaOcuChIdx[ChIdx], (Ocu_PinStateType)PinState);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_PIN_STATE_API == STD_ON) */


#if (IOHWAB_OCU_SET_PIN_ACTION_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetPinAction                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service Set the Output Pin Action of           **
                          the corresponding OCU channel                       **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetPinAction                          **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_004 */
/* @Trace: IoHwAb_SUD_API_062 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetPinAction(IoHwAb_IndexType ChIdx, IoHwAb_OcuPinActionType PinAction)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuSetPinAction != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_OCU_NUM_LGC))
  {
    IoHwAb_GpOcuSetPinAction(IoHwAb_GaaOcuChIdx[ChIdx], (Ocu_PinActionType)PinAction);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_PIN_ACTION_API == STD_ON) */

#if (IOHWAB_OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetAbsoluteThreshold                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding OCU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetAbsoluteThreshold                  **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_006 */
/* @Trace: IoHwAb_SUD_API_063 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetAbsoluteThreshold(IoHwAb_IndexType ChIdx,
    IoHwAb_OcuValueType ReferenceValue,
    IoHwAb_OcuValueType AbsoluteValue, 
    P2VAR(IoHwAb_OcuReturnType, AUTOMATIC, IOHWAB_APPL_DATA) ThresholdResult)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuSetAbsoluteThreshold != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_OCU_NUM_LGC) &&
      (ThresholdResult != IOHWAB_NULL_PTR))
  {
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    *ThresholdResult = (IoHwAb_OcuReturnType)IoHwAb_GpOcuSetAbsoluteThreshold(
    IoHwAb_GaaOcuChIdx[ChIdx], ReferenceValue, AbsoluteValue );
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) */

#if (IOHWAB_OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetRelativeThreshold                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding OCU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetRelativeThreshold                  **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_007 */
/* @Trace: IoHwAb_SUD_API_064 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetRelativeThreshold(IoHwAb_IndexType ChIdx,
    IoHwAb_OcuValueType RelativeValue,
    P2VAR(IoHwAb_OcuReturnType, AUTOMATIC, IOHWAB_APPL_DATA) ThresholdResult)    
{
  Std_ReturnType LddError = E_OK;
  
  if ((IoHwAb_GpOcuSetRelativeThreshold != IOHWAB_NULL_PTR)&&
      (ThresholdResult != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_OCU_NUM_LGC ))
  {
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    *ThresholdResult = (IoHwAb_OcuReturnType)IoHwAb_GpOcuSetRelativeThreshold(
    IoHwAb_GaaOcuChIdx[ChIdx], RelativeValue);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_RELATIVE_THRESHOLD_API == STD_ON) */

#if (IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding OCU channel.                          **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuDisableNotification                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWR_IOHWAB_801_009 */
/* @Trace: IoHwAb_SUD_API_065 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuDisableNotification(IoHwAb_IndexType ChIdx)                                 
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuDisableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_OCU_NUM_LGC))
  {
    IoHwAb_GpOcuDisableNotification(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON)*/

#if (IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding OCU channel.                          **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuEnableNotification                    **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00006 */
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00155 SWS_IoHwAb_00156 */
/* @Trace: SWR_IOHWAB_801_008 */
/* @Trace: IoHwAb_SUD_API_066 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuEnableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuEnableNotification != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_OCU_NUM_LGC))
  {
    IoHwAb_GpOcuEnableNotification(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON) */

#endif /* (IOHWAB_USE_OCU == STD_ON) */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
