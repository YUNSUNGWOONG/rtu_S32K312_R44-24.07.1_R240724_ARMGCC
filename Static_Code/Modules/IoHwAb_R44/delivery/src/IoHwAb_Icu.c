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
**  SRC-MODULE: IoHwAb_Icu.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_IcuSetActivationCondition                              **
**              IoHwAb_IcuDisableNotification                                 **
**              IoHwAb_IcuEnableNotification                                  **
**              IoHwAb_IcuGetInputState                                       **
**              IoHwAb_IcuStartTimestamp                                      **
**              IoHwAb_IcuStopTimestamp                                       **
**              IoHwAb_IcuGetTimestampIndex                                   **
**              IoHwAb_IcuResetEdgeCount                                      **
**              IoHwAb_IcuEnableEdgeCount                                     **
**              IoHwAb_IcuDisableEdgeCount                                    **
**              IoHwAb_IcuGetEdgeNumbers                                      **
**              IoHwAb_IcuEnableEdgeDetection                                 **
**              IoHwAb_IcuDisableEdgeDetection                                **
**              IoHwAb_IcuStartSignalMeasurement                              **
**              IoHwAb_IcuStopSignalMeasurement                               **
**              IoHwAb_IcuGetTimeElapsed                                      **
**              IoHwAb_IcuGetDutyCycleValues                                  **
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
** 1.4.2     10-Nov-2022  KhaLN1            #CP44-797                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24709 #24320         **
** 1.2.0     18-Nov-2021  PhucNHM           R44-Redmine #18098                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Icu.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Config.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (defined(IOHWAB_MCAL_INFINEON_TC33X)) || (defined(IOHWAB_MCAL_INFINEON_TC36X)) \
 || (defined(IOHWAB_MCAL_INFINEON_TC37X)) || (defined(IOHWAB_MCAL_INFINEON_TC38X)) \
 || (defined(IOHWAB_MCAL_INFINEON_TC39X))

#ifndef ICU_RISING_EDGE
#define ICU_RISING_EDGE ICU_17_TIMERIP_RISING_EDGE
#endif

#ifndef ICU_FALLING_EDGE
#define ICU_FALLING_EDGE ICU_17_TIMERIP_FALLING_EDGE
#endif

#ifndef ICU_BOTH_EDGES
#define ICU_BOTH_EDGES ICU_17_TIMERIP_BOTH_EDGES
#endif

#ifndef ICU_IDLE
#define ICU_IDLE ICU_17_TIMERIP_IDLE
#endif

#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_ICU == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_IcuSetActivationCondition                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the activation condition of    **
**                        the corresponding ICU channel.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Activation                                   **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuSetActivationCondition                **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_606_001 */
/* @Trace: IoHwAb_SUD_API_041 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuSetActivationCondition(IoHwAb_IndexType ChIdx,
  IoHwAb_IcuActivationType Activation)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuSetActivationCondition != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    if (Activation == IOHWAB_RISING_EDGE)
    {
      IoHwAb_GpIcuSetActivationCondition(IoHwAb_GaaIcuChIdx[ChIdx],
        (Icu_ActivationType)ICU_RISING_EDGE);
    }
    else if (Activation == IOHWAB_FALLING_EDGE)
    {
      IoHwAb_GpIcuSetActivationCondition(IoHwAb_GaaIcuChIdx[ChIdx],
        (Icu_ActivationType)ICU_FALLING_EDGE);
    }
    else if (Activation == IOHWAB_BOTH_EDGES)
    {
      IoHwAb_GpIcuSetActivationCondition(IoHwAb_GaaIcuChIdx[ChIdx],
        (Icu_ActivationType)ICU_BOTH_EDGES);
    }
    else
    {
      LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_IcuDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuDisableNotification                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_605_002 */
/* @Trace: IoHwAb_SUD_API_042 */
#if ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON))
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuDisableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuDisableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuDisableNotification(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON)) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuEnableNotification                    **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00123 SWS_IoHwAb_00106 SWR_IOHWAB_605_001 */
/* @Trace: IoHwAb_SUD_API_043 */
#if ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON))
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuEnableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuEnableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuEnableNotification(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON)) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetInputState                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the input pin state of the       **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : State                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetInputState                         **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_607_001 */
/* @Trace: IoHwAb_SUD_API_044 */
#if (IOHWAB_ICU_GET_INPUT_STATE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetInputState(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuStateType, AUTOMATIC, IOHWAB_APPL_DATA) State)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetInputState != IOHWAB_NULL_PTR) && (State != NULL_PTR) &&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    if (ICU_IDLE == IoHwAb_GpIcuGetInputState(IoHwAb_GaaIcuChIdx[ChIdx]))
    {
      *State = IOHWAB_IDLE;
    }
    else
    {
      *State = IOHWAB_ACTIVE;
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif  /* (IOHWAB_ICU_GET_INPUT_STATE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStartTimestamp                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts timestamp feature of the        **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, BufSize, NotiItv                             **
**                                                                            **
** InOut parameter      : BufPtr                                              **
**                                                                            **
** Output Parameters    : State                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStartTimestamp                        **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_601_001 */
/* @Trace: IoHwAb_SUD_API_045 */
#if (IOHWAB_ICU_TIMESTAMP_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStartTimestamp(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuValueType, AUTOMATIC, IOHWAB_APPL_DATA) BufPtr,
  uint16 BufSize, uint16 NotiItv)
{
  Std_ReturnType LddError = E_OK;
  
  IoHwAb_IcuValueType tempBuf; 

  if ((IoHwAb_GpIcuStartTimestamp != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    /* Work-around to avoid Misra Rule 8.13 */
    /* polyspace +3 MISRA-C3:18.1 [Not a defect:Low] "NULL pointer was checked by RTE before accessing" */
    /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "NULL pointer was checked by RTE before accessing" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "NULL pointer was checked by RTE before accessing" */
    tempBuf = *BufPtr; 
    *BufPtr = tempBuf;
    IoHwAb_GpIcuStartTimestamp(IoHwAb_GaaIcuChIdx[ChIdx], (Icu_ValueType *)BufPtr,
      (uint16)BufSize, (uint16)NotiItv);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStopTimestamp                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops timestamp feature of the         **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStopTimestamp                         **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_601_002 */
/* @Trace: IoHwAb_SUD_API_046 */
#if (IOHWAB_ICU_TIMESTAMP_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStopTimestamp(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStopTimestamp != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuStopTimestamp(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetTimestampIndex                         **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service returns the array index number of      **
**                        timestamp buffer of the corresponding ICU channel.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : TimestampIdx                                        **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetTimestampIndex                     **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_601_003 */
/* @Trace: IoHwAb_SUD_API_047 */
#if (IOHWAB_ICU_TIMESTAMP_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetTimestampIndex(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuIndexType, AUTOMATIC, IOHWAB_APPL_DATA) TimestampIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetTimestampIndex != IOHWAB_NULL_PTR) && 
      (TimestampIdx != NULL_PTR) &&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    *TimestampIdx = (IoHwAb_IndexType)IoHwAb_GpIcuGetTimestampIndex
      (IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuResetEdgeCount                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service resets edge counter value of the       **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuResetEdgeCount                        **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_602_003 */
/* @Trace: IoHwAb_SUD_API_048 */
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuResetEdgeCount(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuResetEdgeCount != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuResetEdgeCount(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuEnableEdgeCount                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables edge count feature of the      **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuEnableEdgeCount                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_602_001 */
/* @Trace: IoHwAb_SUD_API_049 */
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuEnableEdgeCount(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuEnableEdgeCount != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuEnableEdgeCount(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuDisableEdgeCount                          **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables edge count feature of the     **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuDisableEdgeCount                      **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_602_002 */
/* @Trace: IoHwAb_SUD_API_050 */
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuDisableEdgeCount(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuDisableEdgeCount != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuDisableEdgeCount(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetEdgeNumbers                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the edge counter value of the    **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Num                                                 **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetEdgeNumbers                        **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_602_004 */
/* @Trace: IoHwAb_SUD_API_051 */
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetEdgeNumbers(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuEdgeNumberType, AUTOMATIC, IOHWAB_APPL_DATA) Num)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetEdgeNumbers != IOHWAB_NULL_PTR) &&
      (Num != NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    *Num = (IoHwAb_ValueType)IoHwAb_GpIcuGetEdgeNumbers(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuEnableEdgeDetection                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables edge detect feature of the     **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuEnableEdgeDetection                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_603_001 */
/* @Trace: IoHwAb_SUD_API_052 */
#if (IOHWAB_ICU_EDGE_DETECT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuEnableEdgeDetection(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuEnableEdgeDetection != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuEnableEdgeDetection(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_DETECT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuDisableEdgeDetection                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables edge detect feature of the    **
**                        corresponding ICU channel.                          **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuDisableEdgeDetection                  **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_603_002 */
/* @Trace: IoHwAb_SUD_API_053 */
#if (IOHWAB_ICU_EDGE_DETECT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuDisableEdgeDetection(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuDisableEdgeDetection != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuDisableEdgeDetection(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_DETECT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStartSignalMeasurement                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts signal measurement feature of   **
**                        the corresponding ICU channel.                      **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStartSignalMeasurement                **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_604_001 */
/* @Trace: IoHwAb_SUD_API_054 */
#if (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStartSignalMeasurement(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStartSignalMeasurement != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuStartSignalMeasurement(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStopSignalMeasurement                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops signal measurement feature of    **
**                        the corresponding ICU channel.                      **
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
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStopSignalMeasurement                 **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_604_002 */
/* @Trace: IoHwAb_SUD_API_055 */
#if (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStopSignalMeasurement(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStopSignalMeasurement != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuStopSignalMeasurement(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetTimeElapsed                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Time                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetTimeElapsed                        **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_604_003 */
/* @Trace: IoHwAb_SUD_API_056 */
#if (IOHWAB_ICU_GET_TIME_ELAPSED_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetTimeElapsed(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuValueType, AUTOMATIC, IOHWAB_APPL_DATA) Time)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetTimeElapsed != IOHWAB_NULL_PTR)&&
      (Time != NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    *Time = (IoHwAb_IcuValueType)IoHwAb_GpIcuGetTimeElapsed(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_GET_TIME_ELAPSED_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetDutyCycleValues                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the duty cycle value of the      **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DutyCycle                                           **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetDutyCycleValues                    **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00002 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_604_004 */
/* @Trace: IoHwAb_SUD_API_057 */
#if (IOHWAB_ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetDutyCycleValues(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuDutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCycle)
{
  Std_ReturnType LddError = E_OK;
  Icu_DutyCycleType DutyCycleResult = {0U,0U};
  if ((IoHwAb_GpIcuGetDutyCycleValues != IOHWAB_NULL_PTR) &&
      (DutyCycle != NULL_PTR)&&
      (ChIdx < IOHWAB_ICU_NUM_LGC))
  {
    IoHwAb_GpIcuGetDutyCycleValues(IoHwAb_GaaIcuChIdx[ChIdx], &DutyCycleResult);
    DutyCycle->ActiveTime = (IoHwAb_IcuValueType)DutyCycleResult.ActiveTime;
    DutyCycle->PeriodTime = (IoHwAb_IcuValueType)DutyCycleResult.PeriodTime;
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) */

#endif /* (IOHWAB_USE_ICU == STD_ON) */

/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
