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
**  SRC-MODULE: LinTrcv_Wakeup.c                                              **
**                                                                            **
**  TARGET    : MC33661                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Implementation of functional Wakeup                           **
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
** 1.0.4          23-Dec-2022           TruongND18       #CP44-1198           **
** 1.0.3.1        01-Nov-2022           KhaLN1           #CP44-801            **
** 1.0.3.1        14-Oct-2022           KhaLN1           #CP44-565            **
** 1.0.3          03-Aug-2022           KhaLN1           #CP44-705            **
** 1.0.2          17-May-2022           DuyNHP2          R44-Redmine #20124   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_WakeUp.h"                  /* LinTrcv_Wakeup header file */
#include "LinTrcv_ModeCtrl.h"
#if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
#include "Det.h"                             /* Det header file */
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : LinTrcv_DetGetBusWuReason                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DET check for API LinTrcv_GetBusWuReason            **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucLinNetwork, LddReason                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus         **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#if(STD_ON == LINTRCV_DEV_ERROR_DETECT)
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_DetGetBusWuReason
    (VAR (uint8, LINTRCV_VAR) LucLinNetwork,
     P2CONST(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINTRCV_APPL_CONST) \
                                                                      LddReason)
{
	/* @Trace: LinTrcv_SUD_API_047*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValueDet;
  /* Initialize return value to E_OK */
  LddReturnValueDet = (Std_ReturnType)E_OK;
  /* Check whether the module is uninitialized */
  if (LINTRCV_UNINIT == LinTrcv_GblInitStatus)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_048*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                              LINTRCV_GETBUSWAKEUPREASON_SID, LINTRCV_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether network is out of range */
  if (LINTRCV_NUM_OF_NETWORKS <= LucLinNetwork)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_049*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                 LINTRCV_GETBUSWAKEUPREASON_SID, LINTRCV_E_INVALID_LIN_NETWORK);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether the VersionInfo is equal to null pointer */
  if (NULL_PTR == LddReason)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_050*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                       LINTRCV_GETBUSWAKEUPREASON_SID, LINTRCV_E_PARAM_POINTER);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* @Trace: LinTrcv_SUD_API_051*/
  /* Return Status */
  return (LddReturnValueDet);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : LinTrcv_GetBusWuReason                              **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This API provides the reason for the wakeup that    **
**                        the LIN transceiver has detected in the parameter   **
**                        "Reason". The ability to detect and differentiate   **
**                        the possible wakeup reasons depends strongly on the **
**                        LIN transceiver hardware.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LinNetwork                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Reason                                              **
**                                                                            **
** Return parameter     : E_OK: will be returned if the wake up reason is     **
**                        detected.                                           **
**                        E_NOT_OK: will be returned, if service request is   **
**                        failed due to development errors or the wakeup      **
**                        reason is not detected.                             **
**                                                                            **
** Preconditions        : The LIN Transceiver Driver must be initialized      **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : LinTrcv_DetGetBusWuReason()   **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00007 SWS_LinTrcv_00126 SWS_LinTrcv_00127 SWS_LinTrcv_00128
 * SWS_LinTrcv_00129 SWS_LinTrcv_00130 SRS_BSW_00369 SRS_BSW_00406 SRS_BSW_00377
 * SRS_Can_01097 SRS_Can_01103 SRS_Lin_01588
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_GetBusWuReason
                                    (VAR (uint8, LINTRCV_VAR) LinNetwork,
     P2VAR(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINTRCV_APPL_DATA) Reason)
{
	/* @Trace: LinTrcv_SUD_API_040*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValue;
  VAR (LinTrcv_TrcvModeType,LINTRCV_VAR) lddMode;

  #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  LddReturnValue = LinTrcv_DetGetBusWuReason(LinNetwork, Reason);

  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif
  {
	  /* @Trace: LinTrcv_SUD_API_041*/
    /* Initialize return value to E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
    /* Get current OpMode into local variable */
    lddMode = LinTrcv_GaaNetworkRamData[LinNetwork].ddOpMode;
    /* Check whether channel is being used or not */
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
    if (LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].blChannelUsed)
    {
      /* Set the return value to E_OK */
	  /* @Trace: LinTrcv_SUD_API_042*/
      LddReturnValue = (Std_ReturnType)E_OK;
      /* Check whether current operation mode is normal */
      if (LINTRCV_TRCV_MODE_NORMAL == lddMode)
      {
		  /* @Trace: LinTrcv_SUD_API_043*/
	      /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low]. Jufify: Null pointer is checked in the DET-ON case by function LinTrcv_DetGetBusWuReason.*/
        /* Set the Wakeup Reason to LINTRCV_WU_INTERNALLY */
        *Reason = (LinTrcv_TrcvWakeupReasonType)LINTRCV_WU_INTERNALLY;
      }
      #if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
      else if ((LINTRCV_TRCV_MODE_STANDBY == lddMode) &&
         (LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].
             blLinTrcvWakeupByBusUsed))
      {
		  /* @Trace: LinTrcv_SUD_API_044*/
        /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low]. Jufify: Null pointer is checked in the DET-ON case by function LinTrcv_DetGetBusWuReason.*/
        /* Set the Wakeup Reason to LINTRCV_WU_BY_BUS */
        *Reason = (LinTrcv_TrcvWakeupReasonType)LINTRCV_WU_BY_BUS;
      }
      #endif
      else
      {
		  /* @Trace: LinTrcv_SUD_API_045*/
        /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low]. Jufify: Null pointer is checked in the DET-ON case by function LinTrcv_DetGetBusWuReason.*/
        /* Set the Wakeup Reason to LINTRCV_WU_NOT_SUPPORTED */
        *Reason = (LinTrcv_TrcvWakeupReasonType)LINTRCV_WU_NOT_SUPPORTED;
        /* Set the return value to E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
	
      }
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinTrcv_WakeUp" */
  }
  /* @Trace: LinTrcv_SUD_API_046*/
  /* Return Status */
  return(LddReturnValue);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_DetCheckWakeup                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DET check for API LinTrcv_CheckWakeup               **
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
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus         **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#if(STD_ON == LINTRCV_DEV_ERROR_DETECT)
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_DetCheckWakeup
                                 (VAR (uint8, LINTRCV_VAR) LucLinNetwork)
{
	/* @Trace: LinTrcv_SUD_API_061*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValueDet;

  /* Initialize return value to E_OK */
  LddReturnValueDet = (Std_ReturnType)E_OK;

  /* Check whether the module is uninitialized */
  if (LINTRCV_UNINIT == LinTrcv_GblInitStatus)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_062*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                                     LINTRCV_CHECKWAKEUP_SID, LINTRCV_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether network is out of range */
  if (LINTRCV_NUM_OF_NETWORKS <= LucLinNetwork)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_063*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                      LINTRCV_CHECKWAKEUP_SID, LINTRCV_E_INVALID_LIN_NETWORK);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether current operation mode is not in sleep mode */
  else if (LINTRCV_TRCV_MODE_SLEEP !=
      LinTrcv_GaaNetworkRamData[LucLinNetwork].ddOpMode)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_064*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                         LINTRCV_CHECKWAKEUP_SID, LINTRCV_E_TRCV_NOT_SLEEP);
            /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* Do nothing */
  }
	/* @Trace: LinTrcv_SUD_API_065*/
  /* Return Status */
  return (LddReturnValueDet);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : LinTrcv_CheckWakeup                                 **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Notifies the calling function if a wakeup is        **
**                        detected.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LinNetwork                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Will be returned, if a wakeup has been        **
**                        detected.                                           **
**                        E_NOT_OK: Will be returned, if no wakeup has been   **
**                        detected                                            **
**                                                                            **
** Preconditions        : The LIN Transceiver Driver must be initialized      **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus,        **
**                                              LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : EcuM_SetWakeupEvent(),        **
**                                              LinIf_WakeupConfirmation      **
**                                              LinTrcv_ReadDioConfigType()   **
**                                              LinTrcv_DetCheckWakeup()      **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00012 SWS_LinTrcv_00066 SWS_LinTrcv_00144 SWS_LinTrcv_00145
 * SWS_LinTrcv_00166 SWS_LinTrcv_00167 SWS_LinTrcv_91002 SRS_BSW_00369
 * SRS_BSW_00375 SRS_BSW_00406 SRS_Can_01097 SRS_Lin_01514 SRS_Lin_01563
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_CheckWakeup
                                    (VAR (uint8, LINTRCV_VAR) LinNetwork)
{
	/* @Trace: LinTrcv_SUD_API_054*/
  #if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
  VAR (Dio_LevelType, LINTRCV_VAR) LddDioReturnvalueRxD;
  #endif
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValue;

  #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  LddReturnValue = LinTrcv_DetCheckWakeup(LinNetwork);
  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif
  {
	  /* @Trace: LinTrcv_SUD_API_055*/
    /* Initialize return value to E_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
    #if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
    /* Check whether channel is being used and wake up by bus is used */
    if ((LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].blChannelUsed) &&
        (LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].
            blLinTrcvWakeupByBusUsed))
    {
		/* @Trace: LinTrcv_SUD_API_056*/
      /* Invoke function to read the value of the ddRxDPin for wake up */
      LddDioReturnvalueRxD = LinTrcv_ReadDioConfigType(
          LinTrcv_GaaNetworkInfo[LinNetwork].ddRxDPin);
      /* check if the Dio return value is LOW */
      if ((Dio_LevelType)STD_LOW == LddDioReturnvalueRxD)
      {
		  /* @Trace: LinTrcv_SUD_API_057*/
        LddReturnValue = (Std_ReturnType)E_OK;
        if ((LINTRCV_WAKEUP_NOTIFICATION_ENABLED ==
            LinTrcv_GaaNetworkRamData[LinNetwork].ddWakeupEventNotification))
        {
			/* @Trace: LinTrcv_SUD_API_058*/
          /* Report Wake-up detection to the EcuM */
          EcuM_SetWakeupEvent(LinTrcv_GaaNetworkInfo[LinNetwork].
                              ddWakeupSourceId);
          /* Report Wake-up detection to the LinIf */
          LinIf_WakeupConfirmation(LinTrcv_GaaNetworkInfo[LinNetwork].
                                   ddWakeupSourceId);
          /* Set the current Operation mode as Standby */
          LinTrcv_GaaNetworkRamData[LinNetwork].ddOpMode =
              (LinTrcv_TrcvModeType)LINTRCV_TRCV_MODE_STANDBY;
        }
        else
        {
			/* @Trace: LinTrcv_SUD_API_059*/
          /* Store the detected wake up event */
          LinTrcv_GaaNetworkRamData[LinNetwork].blWakeupPending = LINTRCV_TRUE;
        }
      }
    }
    #endif
  }
  /* @Trace: LinTrcv_SUD_API_060*/
  /* Return Status */
  return(LddReturnValue);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_DetSetWakeupMode                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DET check for API LinTrcv_SetWakeupMode             **
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
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus         **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#if(STD_ON == LINTRCV_DEV_ERROR_DETECT)
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_DetSetWakeupMode
                                 (VAR (uint8, LINTRCV_VAR) LucLinNetwork)
{
	/* @Trace: LinTrcv_SUD_API_075*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValueDet;

  /* Initialize return value to E_OK */
  LddReturnValueDet = (Std_ReturnType)E_OK;

  /* Check whether the module is uninitialized */
  if (LINTRCV_UNINIT == LinTrcv_GblInitStatus)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_076*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                                   LINTRCV_SETWAKEUPMODE_SID, LINTRCV_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* Check whether network is out of range */
  if (LINTRCV_NUM_OF_NETWORKS <= LucLinNetwork)
  {
	/* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
	/* @Trace: LinTrcv_SUD_API_077*/
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                      LINTRCV_SETWAKEUPMODE_SID, LINTRCV_E_INVALID_LIN_NETWORK);
    /* Set the return value to E_NOT_OK */
    LddReturnValueDet = (Std_ReturnType)E_NOT_OK;
  }
  /* @Trace: LinTrcv_SUD_API_078*/
  /* Return Status */
  return (LddReturnValueDet);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : LinTrcv_SetWakeupMode                               **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Enables, disables and clears the notification for   **
**                        wakeup events on the addressed network              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LinNetwork, TrcvWakupMode                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: will be returned if the transceiver state has **
**                        been changed to the requested mode.                 **
**                        E_NOT_OK will be returned, if service request is    **
**                        failed due to development errors or the wakeup mode **
**                        is not set.                                         **
**                                                                            **
** Preconditions        : The LIN Transceiver Driver must be initialized      **
**                                                                            **
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus,        **
**                                              LinTrcv_GaaNetworkInfo[],     **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked : EcuM_SetWakeupEvent()         **
**                                              LinTrcv_DetSetWakeupMode()    **
**                                              LinIf_WakeupConfirmation()    **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00009 SWS_LinTrcv_00135 SWS_LinTrcv_00136 SWS_LinTrcv_00137
 * SWS_LinTrcv_00138 SWS_LinTrcv_00139 SWS_LinTrcv_00140 SRS_BSW_00310
 * SRS_Lin_01589
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_SetWakeupMode
                                    (VAR (uint8, LINTRCV_VAR) LinNetwork,
             VAR (LinTrcv_TrcvWakeupModeType, LINTRCV_VAR) TrcvWakupMode)
{
	/* @Trace: LinTrcv_SUD_API_066*/
  VAR (Std_ReturnType, LINTRCV_VAR) LddReturnValue;

  #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  LddReturnValue = LinTrcv_DetSetWakeupMode(LinNetwork);
  if ((Std_ReturnType)E_OK != LddReturnValue)
  {
	  /* @Trace: LinTrcv_SUD_API_067*/
    UNUSED(TrcvWakupMode);
  }
  else
  #endif
  {
	  /* @Trace: LinTrcv_SUD_API_068*/
    /* Initialize return value to E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
    #if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
    /* Check whether channel is being used and wake up by bus is used */
    if ((LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].blChannelUsed) &&
        (LINTRCV_TRUE == LinTrcv_GaaNetworkInfo[LinNetwork].
            blLinTrcvWakeupByBusUsed))
    {
		/* @Trace: LinTrcv_SUD_API_069*/
      /* Set return value to E_OK */
      LddReturnValue = (Std_ReturnType)E_OK;
      /* Check whether TrcvWakupMode is LINTRCV_WUMODE_ENABLE */
      if (LINTRCV_WUMODE_ENABLE == TrcvWakupMode)
      {
        if (LINTRCV_TRUE == LinTrcv_GaaNetworkRamData[LinNetwork].
                              blWakeupPending)
        {
			/* @Trace: LinTrcv_SUD_API_070*/
          /* Report Wake-up detection to the EcuM */
          EcuM_SetWakeupEvent(LinTrcv_GaaNetworkInfo[LinNetwork].
                              ddWakeupSourceId);
          /* Report Wake-up detection to the LinIf */
          LinIf_WakeupConfirmation(LinTrcv_GaaNetworkInfo[LinNetwork].
                                   ddWakeupSourceId);
          /* Clear the pending wake up event */
          LinTrcv_GaaNetworkRamData[LinNetwork].blWakeupPending =
             LINTRCV_FALSE;
        }
		/* @Trace: LinTrcv_SUD_API_071*/
        /* Enable the wake up notification */
        LinTrcv_GaaNetworkRamData[LinNetwork].ddWakeupEventNotification =
            LINTRCV_WAKEUP_NOTIFICATION_ENABLED;
      }
      /* Check whether TrcvWakupMode is LINTRCV_WUMODE_DISABLE */
      else if (LINTRCV_WUMODE_DISABLE == TrcvWakupMode)
      {
		  /* @Trace: LinTrcv_SUD_API_072*/
        LinTrcv_GaaNetworkRamData[LinNetwork].ddWakeupEventNotification =
            LINTRCV_WAKEUP_NOTIFICATION_DISABLED;
      }
      /* Check whether TrcvWakupMode is LINTRCV_WUMODE_CLEAR and notification
      Disabled */
      else
      {
        if ((LINTRCV_WUMODE_CLEAR == TrcvWakupMode) &&
         (LINTRCV_WAKEUP_NOTIFICATION_DISABLED ==
             LinTrcv_GaaNetworkRamData[LinNetwork].ddWakeupEventNotification))
        {
			/* @Trace: LinTrcv_SUD_API_073*/
          /* Clear the pending wake up event */
          LinTrcv_GaaNetworkRamData[LinNetwork].blWakeupPending = LINTRCV_FALSE;
        }
      }
    }
    #endif
  }
  /* @Trace: LinTrcv_SUD_API_074*/
  /* Return Status */
  return (LddReturnValue);
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
