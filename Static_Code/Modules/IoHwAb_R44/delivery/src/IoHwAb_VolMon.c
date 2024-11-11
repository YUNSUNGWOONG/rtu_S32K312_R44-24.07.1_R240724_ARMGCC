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
**  SRC-MODULE: IoHwAb_VolMon.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for VolMon module                         **
**              IoHwAb_VolMonInit                                             **
**              IoHwAb_VolMon                                                 **
**              IoHwAb_VolMonRead                                             **
**              IoHwAb_VolMonGetStatus                                        **
**              IoHwAb_VolMonIsThresholdOver                                  **
**              IoHwAb_VolMonIsThresholdUnder                                 **
**              IoHwAb_VolMonNotification                                     **
**                                                                            **
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
** 1.3.2     10-Aug-2022  KhaLN1            #CP44-731                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_VolMon.h"
#include "IoHwAb_Config.h"
#include "IoHwAb_Adc.h"
#include "Rte_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace-begin VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
#if (IOHWAB_USE_VOL_MON == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
#ifndef TEST_APPLICATION
static VAR(uint8, IOHWAB_VAR) IoHwAb_GucVolMonIdx;
#else
VAR(uint8, IOHWAB_VAR) IoHwAb_GucVolMonIdx;
#endif
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static VAR(uint8, IOHWAB_VAR) IoHwAb_GucVolMonStatus;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define IOHWAB_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
#ifndef TEST_APPLICATION
static VAR(uint16, IOHWAB_VAR) IoHwAb_GusVolMonFiltValue;
#else
VAR(uint16, IOHWAB_VAR) IoHwAb_GusVolMonFiltValue;
#endif
#define IOHWAB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif /* (IOHWAB_USE_VOL_MON == STD_ON) */
/* polyspace-end VARIABLE:* [Not a defect:Low] "System intended for multitasking" */

/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_VOL_MON == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_VolMonInit                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service initilize VolMon module.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonIdx,                              **
**                          IoHwAb_GusVolMonFiltValue,                        **
**                          IoHwAb_GaaVolMonIncr,                             **
**                          IoHwAb_GaaVolMonMask,                             **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00004 */
/* @Trace: IoHwAb_SUD_API_0103 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonInit(void)
{
  IoHwAb_GucVolMonIdx = 0;

  /* copy the default battery voltage */
  IoHwAb_GusVolMonFiltValue = IOHWAB_VOLMON_DEFAULT_VALUE;

  /* loop until the correct threshold to set the global index */
  while((IoHwAb_GucVolMonIdx < IOHWAB_NUM_VOLMON_LEVEL)
    && (IoHwAb_GusVolMonFiltValue > IoHwAb_GaaVolMonIncr[IoHwAb_GucVolMonIdx]))
  {
    /* increment the index */
    IoHwAb_GucVolMonIdx++;
  }

  /* set the flags corresponding to the index */
  IoHwAb_GucVolMonStatus = IoHwAb_GaaVolMonMask[IoHwAb_GucVolMonIdx];
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMon                                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GusVolMonFiltValue,                        **
**                          IoHwAb_GucVolMonIdx,                              **
**                          IoHwAb_GaaVolMonIncr,                             **
**                          IoHwAb_GucVolMonStatus,                           **
**                          IoHwAb_GaaVolMonMask,                             **
**                          IoHwAb_GaaVolMonDecr                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_AnaInDirReadDirect,                        **
**                          IoHwAb_AnaInFirstOrderFiltering,                  **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00004 */
/* @Trace: SWR_IOHWAB_710_001 SWR_IOHWAB_710_002 SWR_IOHWAB_710_004 */
/* @Trace: SWR_IOHWAB_710_005 */
/* @Trace: IoHwAb_SUD_API_0104 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMon(void)
{
  /* local index */
  uint8 LucIdx;
  /* local variable to hold the current battery level */
  IoHwAb_ValueType LddCurLevel = 0U;
  Std_ReturnType LddError = E_OK;

  /* first read directly the battery voltage */
  /* it could happend that Read direct is made during 10ms acquisition of     */
  /* analog inputs depending on CPU load and design of ConvertAllChannels, if */
  /* so log and error with no reste and skip the sample                       */
  LddError = IoHwAb_AnaInDirReadDirect(IOHWAB_VOLMON_ADC_CH_IDX, &LddCurLevel, 1);
  if (LddError == E_OK)
  {
    /* now filter the battery level */
    LddCurLevel = IoHwAb_AnaInFirstOrderFiltering(IoHwAb_GusVolMonFiltValue,
      LddCurLevel, IOHWAB_VOLMON_FILTER);

    /* if the new battery level is higher, the level is increasing, else decreasing */
    if (LddCurLevel > IoHwAb_GusVolMonFiltValue)
    {
      /*************************** level is increasing ************************/
      /* check if the global index is equal to the nb of thresholds */
      if (IoHwAb_GucVolMonIdx != IOHWAB_NUM_VOLMON_LEVEL)
      {/* the global index is smaller than the nb of thresholds */

        /* set the local index to the global index */
        LucIdx = IoHwAb_GucVolMonIdx;

        /* loop to reach the current threshold in the table */
        while ((LucIdx < IOHWAB_NUM_VOLMON_LEVEL)
          && (LddCurLevel >= IoHwAb_GaaVolMonIncr[LucIdx]))
        {
          /* increment the local index */
          LucIdx++;
        }

        /* test if the local index has changed */
        if (LucIdx != IoHwAb_GucVolMonIdx)
        {/* has changed */

          /* set the flags to mask[loc index] */
          IoHwAb_GucVolMonStatus = IoHwAb_GaaVolMonMask[LucIdx];

          /* set global index to local index */
          IoHwAb_GucVolMonIdx = LucIdx;

          IoHwAb_VolMonNotification();
        }
        else
        {/* not changed */
          /* do nothing, exit function */
        }
      }
      else
      {/* the global index is equal to the number of thresholds and VBAT is increasing */
        /* do nothing, exit function */
      }

    }
    else if (LddCurLevel < IoHwAb_GusVolMonFiltValue)
    {
      /*************************** level is decreasing *************************************/

      /* check if the global index is 0 */
      if ((IoHwAb_GucVolMonIdx != 0) && (IoHwAb_GucVolMonIdx <= IOHWAB_NUM_VOLMON_LEVEL))
      {/* the index is not 0 */

        /* set the local index to the global index */
        LucIdx = IoHwAb_GucVolMonIdx;

        /* loop to reach the current threshold in the table */
        while ((LucIdx > 0) && (LddCurLevel <= IoHwAb_GaaVolMonDecr[LucIdx]))
        {
          /* decrement the local index */
          LucIdx--;
        }

        /* test if the local index has changed */
        if (LucIdx != IoHwAb_GucVolMonIdx)
        {/* has changed */

          /* set the flags to mask[loc index] */
          IoHwAb_GucVolMonStatus = IoHwAb_GaaVolMonMask[LucIdx];

          /* set global index to local index */
          IoHwAb_GucVolMonIdx = LucIdx;

          IoHwAb_VolMonNotification();
        }
        else
        {/* not changed */
          /* do nothing, exit function */
        }
      }
      else
      {/* global index is 0 */
        /* do nothing, exit the function */
      }
    }
    else
    {
      /*************************** level is the same, do nothing  *************/
    }

    /* write the new value of the battery level */
    IoHwAb_GusVolMonFiltValue = LddCurLevel;
  }
  else
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_VOLMON_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMonRead                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GusVolMonFiltValue                         **
**                        Function(s) invoked    : none                       **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_CUS_00004 */
/* @Trace: SWR_IOHWAB_711_001_API */
/* @Trace: IoHwAb_SUD_API_0105 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonRead(
  P2VAR(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  if (Value != NULL_PTR)
  {
    *Value = IoHwAb_GusVolMonFiltValue;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_VolMonGetStatus                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Status                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_CUS_00004 */
/* @Trace: SWR_IOHWAB_711_002_API */
/* @Trace: IoHwAb_SUD_API_0106 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonGetStatus(
  P2VAR(IoHwAb_StatusType, AUTOMATIC, IOHWAB_APPL_DATA) VolMonStatus)
{
  if (VolMonStatus != NULL_PTR)
  {
    *VolMonStatus = IoHwAb_GucVolMonStatus;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_VolMonIsThresholdOver                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Threshold                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_CUS_00004 */
/* @Trace: SWR_IOHWAB_711_003_API */
/* @Trace: IoHwAb_SUD_API_0107 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonIsThresholdOver(
  IoHwAb_ThresholdType Threshold,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) VolMonResult)
{
  if ((VolMonResult != NULL_PTR) && ( Threshold < 8U))
  {
    if ( (IoHwAb_GucVolMonStatus & (uint8)(((IoHwAb_ThresholdType)1 << (IoHwAb_ThresholdType)Threshold) )) != 0U )
    {
      *VolMonResult = IOHWAB_TRUE;
    }
    else
    {
      *VolMonResult = IOHWAB_FALSE;
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_VolMonIsThresholdUnder                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Threshold                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_CUS_00004 */
/* @Trace: SWR_IOHWAB_711_004_API */
/* @Trace: IoHwAb_SUD_API_0108 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonIsThresholdUnder(
  IoHwAb_ThresholdType Threshold,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) VolMonResult)
{
  if ((VolMonResult != NULL_PTR) && ( Threshold < 8U))
  {
    if ( (IoHwAb_GucVolMonStatus & (uint8)(((IoHwAb_ThresholdType)1 << (IoHwAb_ThresholdType)Threshold))) != 0U )
    {
      *VolMonResult = IOHWAB_FALSE;
    }
    else
    {
      *VolMonResult = IOHWAB_TRUE;
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_VolMonNotification                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function notifies the transition of battery    **
**                        level to application                                **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          Rte_Call_R_VolMon_Cbk_Notification                **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00004 SRS_BSW_00333 SRS_BSW_00440 SRS_SPAL_12056 */
/* @Trace: IoHwAb_SUD_API_0109 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonNotification(void)
{
  (void)Rte_Call_IoHwAb_R_VolMon_Cbk_Notification();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_VOL_MON == STD_ON) */

/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
