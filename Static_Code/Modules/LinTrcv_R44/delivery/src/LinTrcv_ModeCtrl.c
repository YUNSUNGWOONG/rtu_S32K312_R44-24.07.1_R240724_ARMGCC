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
**  SRC-MODULE: LinTrcv_ModeCtrl.c                                            **
**                                                                            **
**  TARGET    :   MC33661                                                     **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Implementation of LinTrcv_SetOpMode and LinTrcv_GetOpMode     **
**              APIs                                                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.7          29-Mar-2024           YB Song          #CP44-5981           **
** 1.0.4          05-Jan-2023           TruongND18       #CP44-1198           **
** 1.0.3.1        01-Nov-2022           KhaLN1           #CP44-801            **
** 1.0.3.1        14-Oct-2022           KhaLN1           #CP44-565            **
** 1.0.2          17-May-2022           DuyNHP2          R44-Redmine #20124   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_ModeCtrl.h"              /* LinTrcv_ModeCtrl header file */
#include "SchM_LinTrcv.h"                  /* Schedule Manager header */
#include "Dio.h"                           /* Dio header file */
#include "Os.h"                            /* Os header file */
#if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
#include "Det.h"                           /* DET module header */
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#ifdef OS_STM0_TIM0
#define OS_GET_TIMESTAMP()   (OS_STM0_TIM0.U)
#define MAX_TICK             (uint32)0xFFFFFFFF
#endif

#define MASK_LEN_BIT 16
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : LinTrcv_SetMode                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sets the LIN transceiver hardware to OpMode mode    **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucLinNetwork, LddOpMode, LddCurrentOpMode          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : LinTrcv_SetNormalMode(),      **
**                                               LinTrcv_SetSleepMode(),      **
**                                               LinTrcv_SetStandByMode()     **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE)
LinTrcv_SetMode (VAR (uint8, LINTRCV_VAR) LucLinNetwork,
                 VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) LddOpMode,
                 VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) LddCurrentOpMode)
{
  /*Sleep or Standby -> Normal mode */
  if (LINTRCV_TRCV_MODE_NORMAL == LddOpMode)
  {
	  /* @Trace: LinTrcv_SUD_API_013*/
    LinTrcv_SetNormalMode (LucLinNetwork);
  }
  else if (LINTRCV_TRCV_MODE_STANDBY == LddOpMode)
  {
	/* Sleep or Standby -> Standby mode */
    if (LINTRCV_TRCV_MODE_NORMAL != LddCurrentOpMode)
    {
		/* @Trace: LinTrcv_SUD_API_014*/
      LinTrcv_SetStandByMode (LucLinNetwork);
    }
    /* Normal -> Standby mode */
    else
    {
		/* @Trace: LinTrcv_SUD_API_015*/
      LinTrcv_SetSleepMode (LucLinNetwork);
      LinTrcv_SetStandByMode (LucLinNetwork);
    }
  }
  else
  {
    /* Normal or Sleep -> Sleep mode */
    if (LINTRCV_TRCV_MODE_STANDBY != LddCurrentOpMode)
    {
		/* @Trace: LinTrcv_SUD_API_016*/
      LinTrcv_SetSleepMode (LucLinNetwork);
    }
    /* Standby -> Sleep mode */
    else
    {
		/* @Trace: LinTrcv_SUD_API_017*/
      LinTrcv_SetNormalMode (LucLinNetwork);
      LinTrcv_SetSleepMode (LucLinNetwork);
    }
  }
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_SetOpMode                                   **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : The internal state of the LIN transceiver driver    **
**                        is switched to mode given in the parameter OpMode.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LinNetwork, OpMode                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: will be returned if the transceiver state has **
**                        been changed to the requested mode.                 **
**                        E_NOT_OK: will be returned if the transceiver state **
**                        change is not accepted or has failed or the         **
**                        parameter is out of the allowed range.              **
**                                                                            **
** Preconditions        : The LIN Transceiver Driver must be initialized      **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus,        **
**                                              LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : Det_ReportError(),            **
**                                              LinTrcv_SetMode()             **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00002 SWS_LinTrcv_00108 SWS_LinTrcv_00109
 * SWS_LinTrcv_00110 SWS_LinTrcv_00147 SWS_LinTrcv_00112 SWS_LinTrcv_00113
 * SWS_LinTrcv_00114 SWS_LinTrcv_00148 SWS_LinTrcv_00115 SWS_LinTrcv_00149
 * SWS_LinTrcv_00116 SWS_LinTrcv_00117 SWS_LinTrcv_00157 SRS_BSW_00369 
 * SRS_BSW_00406 SRS_BSW_00357 SRS_Can_01097 SRS_Can_01098 SRS_Can_01099 
 * SRS_Can_01100 SRS_Lin_01524 SRS_Lin_01566 SRS_Lin_01584 SRS_Lin_01585 SRS_Lin_01586
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
/* polyspace +4 CODE-METRICS:LEVEL [Reviewed:Low] "CONDITIONAL PASS" */
FUNC(Std_ReturnType, LINTRCV_CODE)
LinTrcv_SetOpMode (VAR (uint8, LINTRCV_VAR) LinNetwork,
VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) OpMode)
{
	/* @Trace: LinTrcv_SUD_API_018*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValue;
  VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) LddCurrentOpMode;

  /* Initialize return value to E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;
  #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (LINTRCV_UNINIT == LinTrcv_GblInitStatus)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_019*/
    /* Report to DET */
    (void)Det_ReportError (LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
        LINTRCV_SETOPMODE_SID, LINTRCV_E_UNINIT);
    /* Set the return value to E_NOT_OK  */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether Network is out of range */
  else if (LINTRCV_NUM_OF_NETWORKS <= LinNetwork)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_020*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
        LINTRCV_SETOPMODE_SID, LINTRCV_E_INVALID_LIN_NETWORK);
    /* Set the return value to E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* Do nothing */
  }
  /* Check any DET error has occurred */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif/* #if(LINTRCV_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check whether channel is being used */
    if (LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].blChannelUsed)
    {
		/* @Trace: LinTrcv_SUD_API_021*/
      /* Get the current Operation mode */
      LddCurrentOpMode = LinTrcv_GaaNetworkRamData[LinNetwork].ddOpMode;

      #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
      #if (LINTRCV_STANDBYMODE_USED == STD_ON)
      if (LINTRCV_FALSE == LinTrcv_GaaNetworkInfo[LinNetwork].blStandbyModeUsed)
      #endif
      {
        /* Check whether OpMode standby and current mode is equal to sleep
        * but Wk not configured
        */
        if (((LINTRCV_TRCV_MODE_STANDBY == OpMode) &&
          (LINTRCV_TRCV_MODE_STANDBY != LddCurrentOpMode))||
          ((Dio_ChannelType)LINTRCV_INVALID ==
          LinTrcv_GaaNetworkInfo[LinNetwork].ddWkPin.DioConfigType.ChannelID))
        {
          /* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
          /* @Trace: LinTrcv_SUD_API_022*/
          /* Report to DET */
          (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                    LINTRCV_SETOPMODE_SID, LINTRCV_E_INVALID_TRCV_OPMODE);
          /* Set the return value to E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        }
        else if ((LINTRCV_TRCV_MODE_SLEEP == OpMode) &&
          (LINTRCV_TRCV_MODE_NORMAL != LddCurrentOpMode))
        {
          /* @Trace: LinTrcv_SUD_API_096*/
          /* Report to DET */
          (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                    LINTRCV_SETOPMODE_SID, LINTRCV_E_TRCV_NOT_NORMAL);
          /* Set the return value to E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        }
        else if ((LINTRCV_TRCV_MODE_NORMAL == OpMode) &&
          (LINTRCV_TRCV_MODE_SLEEP != LddCurrentOpMode))
        {
          /* @Trace: LinTrcv_SUD_API_097*/
          /* Report to DET */
          (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                    LINTRCV_SETOPMODE_SID, LINTRCV_E_TRCV_NOT_SLEEP);
          /* Set the return value to E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /*Do nothing*/
        }
      }
      /* Check any DET error has occurred */
      if ((Std_ReturnType)E_OK == LddReturnValue)
      #endif
      {
		  /* @Trace: LinTrcv_SUD_API_023*/
        /* Invoke the function to set LIN Transceiver Driver to mode */
        LinTrcv_SetMode(LinNetwork, OpMode, LddCurrentOpMode);
      }
    }
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
    else
    {
		/* @Trace: LinTrcv_SUD_API_024*/
      /* Set the return value to E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
  }
  /* Return Status */
  /* @Trace: LinTrcv_SUD_API_025*/
  return (LddReturnValue);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_GetOpMode                                   **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : API detects the actual software state of LIN        **
**                        transceiver driver.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LinNetwork                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : OpMode                                              **
**                                                                            **
** Return parameter     : E_OK: will be returned if the operation mode is     **
**                        detected.                                           **
**                        E_NOT_OK: will be returned, if service request is   **
**                        failed due to development errors or the operation   **
**                        mode is not detected.                               **
**                                                                            **
** Preconditions        : The LIN Transceiver Driver must be initialized      **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus,        **
**                                              LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00005 SWS_LinTrcv_00121 SWS_LinTrcv_00122
 * SWS_LinTrcv_00123 SWS_LinTrcv_00124 SWS_LinTrcv_00125 SRS_BSW_00369 SRS_BSW_00377
 * SRS_Can_01097 SRS_Can_01101 SRS_Lin_01587
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE)
LinTrcv_GetOpMode (VAR (uint8, LINTRCV_VAR) LinNetwork,
P2VAR(LinTrcv_TrcvModeType, AUTOMATIC, LINTRCV_APPL_DATA) OpMode)
{
	/* @Trace: LinTrcv_SUD_API_033*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValue;

  /* Initialize return value to E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;
  #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is uninitialized */
  if (LINTRCV_UNINIT == LinTrcv_GblInitStatus)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_034*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
    LINTRCV_GETOPMODE_SID, LINTRCV_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether network is out of range */
  if (LINTRCV_NUM_OF_NETWORKS <= LinNetwork)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_035*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
    LINTRCV_GETOPMODE_SID, LINTRCV_E_INVALID_LIN_NETWORK);
    /* Set the return value to E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  }

  #endif
  /* Check whether the OpMode is equal to null pointer */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  {
    if (NULL_PTR != OpMode )
    {
      /* Check whether channel is being used or not */
      if (LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].blChannelUsed)
      {
		  /* @Trace: LinTrcv_SUD_API_036*/
          
        /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low]. Jufify: Null pointer is checked in the DET-ON case by "if (NULL_PTR == OpMode)" */
        *OpMode = LinTrcv_GaaNetworkRamData[LinNetwork].ddOpMode;
      }
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
      else
      {
		  /* @Trace: LinTrcv_SUD_API_037*/
        /* Set the return value to E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
      }
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
    }
    else
    {
      #if (LINTRCV_DEV_ERROR_DETECT == STD_ON)
	  /* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	  /* @Trace: LinTrcv_SUD_API_038*/
      /* Report to DET */
      (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
      LINTRCV_GETOPMODE_SID, LINTRCV_E_PARAM_POINTER);
      /* Set the return value to E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
      #endif
    }
  }
	/* @Trace: LinTrcv_SUD_API_039*/
  /* Return Status */
  return(LddReturnValue);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_SetNormalMode                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sets the LIN transceiver hardware to Normal mode    **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucLinNetwork                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : Dio_WriteChannel()            **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE)
LinTrcv_SetNormalMode (VAR (uint8, LINTRCV_VAR) LucLinNetwork)
{
	/* @Trace: LinTrcv_SUD_API_032*/
  /* Invoke the function to write the High value to ddTxDPin */
  LinTrcv_WriteDioConfigType(LinTrcv_GaaNetworkInfo[LucLinNetwork].ddTxDPin,
           (Dio_LevelType)STD_HIGH);
  /* Invoke the function to write the High value to ddENPin */
  LinTrcv_WriteDioConfigType(LinTrcv_GaaNetworkInfo[LucLinNetwork].ddENPin,
           (Dio_LevelType)STD_HIGH);
  /* Wait for changing the transceiver state */
  LinTrcv_WaitForChangeMode(LINTRCV_WAIT_TIME);
  /* Update the current Operation mode with Normal */
  LinTrcv_GaaNetworkRamData[LucLinNetwork].ddOpMode =
      (LinTrcv_TrcvModeType)LINTRCV_TRCV_MODE_NORMAL;
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_SetSleepMode                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sets the LIN transceiver hardware to Sleep mode     **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucLinNetwork                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : Dio_WriteChannel()            **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE)
LinTrcv_SetSleepMode (VAR (uint8, LINTRCV_VAR) LucLinNetwork)
{
	/* @Trace: LinTrcv_SUD_API_026*/
  /* Invoke the function to write the High value to ddTxDPin */
  LinTrcv_WriteDioConfigType(LinTrcv_GaaNetworkInfo[LucLinNetwork].ddTxDPin,
           (Dio_LevelType)STD_HIGH);
  /* Invoke the function to write the Low value to ddENPin */
  LinTrcv_WriteDioConfigType(LinTrcv_GaaNetworkInfo[LucLinNetwork].ddENPin,
           (Dio_LevelType)STD_LOW);
  /* Wait for changing the transceiver state */
  LinTrcv_WaitForChangeMode(LINTRCV_WAIT_TIME);
  /* Update the Operation mode with Sleep */
  LinTrcv_GaaNetworkRamData[LucLinNetwork].ddOpMode =
              (LinTrcv_TrcvModeType)LINTRCV_TRCV_MODE_SLEEP;
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_SetStandByMode                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sets the LIN transceiver hardware to Stand By mode  **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucLinNetwork                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : Dio_WriteChannel()            **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE)
LinTrcv_SetStandByMode (VAR (uint8, LINTRCV_VAR) LucLinNetwork)
{
	/* @Trace: LinTrcv_SUD_API_027*/
  Dio_LevelType LddDioReturnvalueWk;
  Dio_LevelType LddvalueWk;

  if ((Dio_ChannelType)LINTRCV_INVALID !=
      LinTrcv_GaaNetworkInfo[LucLinNetwork].ddWkPin.DioConfigType.ChannelID)
  {
	  /* @Trace: LinTrcv_SUD_API_028*/
    /* Invoke function to read the value of the ddWkDPin for wake up */
    LddDioReturnvalueWk = LinTrcv_ReadDioConfigType(
        LinTrcv_GaaNetworkInfo[LucLinNetwork].ddWkPin);
    /* Toggle Wk pin */
    if (LddDioReturnvalueWk == STD_LOW)
    {
		/* @Trace: LinTrcv_SUD_API_029*/
      LddvalueWk = STD_HIGH;
    }
    else
    {
		/* @Trace: LinTrcv_SUD_API_030*/
      LddvalueWk = STD_LOW;
    }
	/* @Trace: LinTrcv_SUD_API_031*/
    /* Invoke the function to write ddWkPin to toggle */
    LinTrcv_WriteDioConfigType(LinTrcv_GaaNetworkInfo[LucLinNetwork].ddWkPin,
           (Dio_LevelType)LddvalueWk);
    /* Wait for changing the transceiver state */
    LinTrcv_WaitForChangeMode(LINTRCV_WAIT_TIME);
    /* Update the Operation mode with standby */
    LinTrcv_GaaNetworkRamData[LucLinNetwork].ddOpMode =
          (LinTrcv_TrcvModeType)LINTRCV_TRCV_MODE_STANDBY;
  }
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WaitForChangeMode                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : use Tm_BusyWait1us16bit for wait time               **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LulWaitCount                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : MAX_TICK                      **
**                        Function(s) invoked : Tm_BusyWait1us16bit()         **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00171
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_WaitForChangeMode(VAR(uint8, LINTRCV_VAR)
                           LulWaitCount)
{
  #if (STD_ON == LINTRCV_TIMER_TYPE)
    (void)Tm_BusyWait1us16bit(LulWaitCount);
  #else
    #ifdef OS_STM0_TIM0
    uint32 LulPreTick;
    uint32 LulPostTick;
    uint32 LulPeriod;
    LulPreTick = 0;
    LulPostTick = 0;
    LulPeriod = 0;

    LulPreTick = OS_GET_TIMESTAMP();
    /* Timer tick is 10 nano second, WaitCount is micro second */
    while (LulPeriod < LulWaitCount * 100)
    {
      /* Get tick from Os */
      LulPostTick = OS_GET_TIMESTAMP();
      /* calculate period */
      if (LulPostTick > LulPreTick)
      {
        LulPeriod = LulPostTick - LulPreTick;
      }
      else
      {
        LulPeriod = (MAX_TICK - LulPreTick) + LulPostTick;
      }
    }
    #else
    UNUSED(LulWaitCount);
    #endif
  #endif
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_ReadDioConfigType                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : use Read Channel | Port | GroupChannel              **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DioConfigType                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Function(s) invoked :  Dio_ReadChannel              **
**                                               Dio_ReadPort                 **
**                                               Dio_ReadChannelGroup         **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Dio_LevelType, LINTRCV_CODE) LinTrcv_ReadDioConfigType(VAR (
    LinTrcv_DioConfigType, LINTRCV_VAR) DioConfigType)
{
  /* @Trace: LinTrcv_SUD_API_079*/
  Dio_LevelType LddDioReturnvalue;
  LddDioReturnvalue = 0x00;
  //Mask to filter dominant pin
  uint16 MaskPort = 0x0001;
  Dio_PortLevelType PortValue;
  switch (DioConfigType.DioType)
  {
    case LINTRCV_DIO_CHANNEL:
    /* @Trace: LinTrcv_SUD_API_080*/
      LddDioReturnvalue = Dio_ReadChannel(DioConfigType.DioConfigType.ChannelID);
      break;
    case LINTRCV_DIO_PORT:
      /* PinNumber was configed to [0-15] & validated by gentool */
      /* Polyspace requiring */
      if (MASK_LEN_BIT > DioConfigType.DioConfigType.PortPin.PinNumber)
      {
		/* @Trace: LinTrcv_SUD_API_081*/
        PortValue = Dio_ReadPort(DioConfigType.DioConfigType.PortPin.PortID);
        //Check pin that need read in port
        MaskPort = MaskPort << DioConfigType.DioConfigType.PortPin.PinNumber;
        LddDioReturnvalue = (((PortValue & MaskPort) == 0) ? STD_LOW : STD_HIGH);
      }
      break;
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
    case LINTRCV_DIO_GROUP_CHANNEL:
      if (MASK_LEN_BIT > DioConfigType.DioConfigType.GroupPin.PinNumber)
      {
		/* @Trace: LinTrcv_SUD_API_082*/
        PortValue = Dio_ReadChannelGroup(DioConfigType.DioConfigType.GroupPin.
                                         GroupChannel);
        //Check pin that need read in GroupChannel
        MaskPort = MaskPort << DioConfigType.DioConfigType.GroupPin.PinNumber;
        LddDioReturnvalue = (((PortValue & MaskPort) == 0) ? STD_LOW : STD_HIGH);
      }
      break;
    default:
      /* do nothing, checked all case */
      break;
  }
  /* @Trace: LinTrcv_SUD_API_083  */
  return LddDioReturnvalue;
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_WriteDioConfigType                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : use Write Channel | Port | GroupChannel             **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DioConfigType, level                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Function(s) invoked :  Dio_WriteChannel             **
**                                               Dio_ReadPort                 **
**                                               Dio_WritePort                **
**                                               Dio_ReadChannelGroup         **
**                                               Dio_WriteChannelGroup        **
**                       SchM_Enter_LinTrcv_DIO_READ_WRITE_PROTECTION         **
**                       SchM_Exit_LinTrcv_DIO_READ_WRITE_PROTECTION          **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_WriteDioConfigType
                 (VAR(LinTrcv_DioConfigType, LINTRCV_VAR) DioConfigType,
                  Dio_LevelType level)
{
    /* @Trace: LinTrcv_SUD_API_084 */
  uint16 MaskPort = 0x0001;
  Dio_PortLevelType PortValue;
  switch (DioConfigType.DioType)
  {
    case LINTRCV_DIO_CHANNEL:
      /* @Trace: LinTrcv_SUD_API_085 */
      Dio_WriteChannel(DioConfigType.DioConfigType.ChannelID, level);
      break;
    case LINTRCV_DIO_PORT:
      /* PinNumber was configed to [0-15] & validated by gentool */
      /* Polyspace requiring */
      if (MASK_LEN_BIT > DioConfigType.DioConfigType.PortPin.PinNumber)
      {
		/* @Trace: LinTrcv_SUD_API_086*/
        SchM_Enter_LinTrcv_DIO_READ_WRITE_PROTECTION();
        PortValue = Dio_ReadPort(DioConfigType.DioConfigType.PortPin.PortID);
        //Creat Mask to set dominant pin in Port
        MaskPort = MaskPort << DioConfigType.DioConfigType.PortPin.PinNumber;

        if (STD_HIGH == level)
        {
          /* @Trace: LinTrcv_SUD_API_087 */
          //set bit at pinNumber
          PortValue |= MaskPort;
        }
        else
        {
          /* @Trace: LinTrcv_SUD_API_088 */
          //clear bit at pinNumber
          MaskPort = ~MaskPort;
          PortValue &= MaskPort;
        }
        /* @Trace: LinTrcv_SUD_API_089 */
        Dio_WritePort(DioConfigType.DioConfigType.PortPin.PortID, PortValue);
        SchM_Exit_LinTrcv_DIO_READ_WRITE_PROTECTION();
      }
      break;
    case LINTRCV_DIO_GROUP_CHANNEL:
      if (MASK_LEN_BIT > DioConfigType.DioConfigType.GroupPin.PinNumber)
      {
        /* @Trace: LinTrcv_SUD_API_090 */
        SchM_Enter_LinTrcv_DIO_READ_WRITE_PROTECTION();
        PortValue = Dio_ReadChannelGroup(DioConfigType.DioConfigType.GroupPin.
                                         GroupChannel);
        //Creat Mask to set dominant pin in GroupChannel
        MaskPort = MaskPort << DioConfigType.DioConfigType.GroupPin.PinNumber;

        if (STD_HIGH == level)
        {
          /* @Trace: LinTrcv_SUD_API_091 */
          //set bit at pinNumber
          PortValue |= MaskPort;
        }
        else
	 /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
        {
          /* @Trace: LinTrcv_SUD_API_092 */
          //clear bit at pinNumber
          MaskPort = ~MaskPort;
          PortValue &= MaskPort;
        }
        /* @Trace: LinTrcv_SUD_API_093 */
        Dio_WriteChannelGroup(DioConfigType.DioConfigType.GroupPin.GroupChannel,
                              PortValue);
        SchM_Exit_LinTrcv_DIO_READ_WRITE_PROTECTION();
      }
      break;
    default:
      /* do nothing, checked all case */
      break;
  }
	 /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
