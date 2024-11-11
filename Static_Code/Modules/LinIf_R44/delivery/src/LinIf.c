/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually  and has no impact" */
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
**  SRC-MODULE: LinIf.c                                                       **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinIf APIs                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By              Description                      **
********************************************************************************
** 1.0.13      21-Aug-2023   KhaLN1          #CP44-2481                       **
** 1.0.10      07-Mar-2023   KhaLN1          #CP44-1811                       **
** 1.0.8       04-Dec-2022   KhaLN1          #CP44-1191                       **
** 1.0.7.1     22-Nov-2022   KhaLN1          #CP44-1162                       **
** 1.0.7       03-Nov-2022   KhaLN1          #CP44-1100                       **
** 1.0.6       17-Oct-2022   KhaLN1          #CP44-563 #CP44-861              **
** 1.0.5       03-Aug-2022   KhaLN1          #CP44-513                        **
** 1.0.3       25-Apr-2022   DuyNHP2         R44-Redmine #26480               **
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: LinIf_SUD_FILE_001 */
#include "LinIf_SubProcess.h"    	/* LinIf internal function header */

#if(LINTP_SUPPORT == STD_ON)
#include "LinTp_Ram.h"           	/* LinTp RAM header */
#include "LinTp_Rx.h"            	/* LinTp Rx internal header */
#include "LinTp_Tx.h"            	/* LinTp Tx internal header */
#if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
#include "BswM_LinTp.h"						/* BswM callback header for LinTp */
#endif
#endif

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                	/* DET header */
#endif

#if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_OFF)
#include "Lin.h"                	/* Lin Header */
#endif

#if (LINIF_SLAVE_SUPPORT == STD_ON)
#include "Com.h"
#endif

#include "LinSM.h"
#include "LinIf_Ram.h"
#include "PduR_LinIf.h"         /* PduR callback header for LinIf */
#include "SchM_LinIf.h"         	/* Schedule Manager header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/



/*******************************************************************************
** Function Name      : LinIf_Init                                            **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : This service initializes the LIN Interface. The LINIF **
**                      state will be set to LINIF_INIT and LINIF channel     **
**                      state will be set to LINIF_CHANNEL_OPERATIONAL after  **
**                      successful completion of this API.                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *ConfigPtr                                            **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpDbTocPtr,                   **
**                      LinIf_GpFirstChannel, LinIf_GpFirstAssociatedFrame,   **
**                      LinIf_GddMaxAssociatedFrames, LinTp_GpFirstChannel,   **
**                      LinIf_GaaChannelInfo, LinTp_GaaChannelInfo            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(), LinIf_ChangeToNullSchedule(),      **
**                      EcuM_GetResetReason(), Lin_GetStatus()                **
*******************************************************************************/
/* @Trace: SWS_LinIf_00198 SWS_LinIf_00373 SWS_LinIf_00233
 * SRS_BSW_00101 SRS_BSW_00358 SRS_BSW_00405 SRS_BSW_00414
 * SRS_BSW_00416 SRS_Lin_01569 SRS_BSW_00327 SRS_BSW_00328
 * SRS_BSW_00335 SRS_BSW_00167 SRS_BSW_00170 SRS_BSW_00337
 * SRS_BSW_00344 SRS_BSW_00404 SRS_BSW_00406 SRS_BSW_00413
 * SRS_BSW_00480 SRS_BSW_00481 SRS_Lin_01551 SRS_Lin_01577
 */
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_Init
  (P2CONST(LinIf_ConfigType, AUTOMATIC, LINIF_APPL_CONST) ConfigPtr)
{
  #if(LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Initialize the error status flag to false */
  boolean LblErrFlag;
  #endif /* #if(LINIF_DEV_ERROR_DETECT == STD_ON) */

  #if(LINIF_DEV_ERROR_DETECT == STD_ON)
  LblErrFlag = LINIF_FALSE;
  #endif /* #if(LINIF_DEV_ERROR_DETECT == STD_ON) */

  #if(LINIF_DEV_ERROR_DETECT == STD_ON)
  /* check if the ConfigPtr is not NULL Pointer */
  if (NULL_PTR != ConfigPtr)
  {
    /* @Trace: LinIf_SUD_API_002*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, LINIF_INIT_SID,
      LINIF_E_PARAM_POINTER);
     /* Set the error status flag to true */
    LblErrFlag = LINIF_TRUE;
  }
  /* Check if no development error occurred */
  if(LINIF_FALSE == LblErrFlag)
  #endif /* #if(LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_003*/
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_Init" */
    LINIF_UNUSED_PTR(ConfigPtr);
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_Init" */
    #if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
    /* Initialize all channels with DET error checking */
    LblErrFlag = LinIf_InitAllChannels();
    #else
    LinIf_InitAllChannels();
    #endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */

    #if (LINIF_DEV_ERROR_DETECT == STD_ON)
    /* Set the LinIf state to initialized */
    /* If there is no problem with DET or
                                   getting wakeup event, init is successful. */
    if(LINIF_FALSE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_014*/
      /* SWS_LinIf_00381, SWS_LinIf_00438 */
      LinIf_GblInitSts = LINIF_INIT;
    }
    else
    {
      /* Do nothing */
    }
    #endif /* #if (LINIF_DEV_ERROR_DETECT == STD_ON) */
    #if(LINTP_SUPPORT == STD_ON)
    /* @Trace: LinIf_SUD_API_015*/
    LinTp_Init(NULL_PTR);
    #endif
  }/* No development errors occurred */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinIf_GetVersionInfo                                  **
**                                                                            **
** Service ID         : 0x03                                                  **
**                                                                            **
** Description        : This service returns the version information of this  **
**                      module.                                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : *versioninfo                                          **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00340 SWS_LinIf_00640
 * SRS_BSW_00407 SRS_BSW_00327 SRS_BSW_00337
 */
#if (LINIF_VERSION_INFO_API == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, LINIF_APPL_DATA) versioninfo)
{
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* check if versioninfo pointer is equal to Null */
  if(NULL_PTR == versioninfo)
  {
    /* @Trace: LinIf_SUD_API_016*/
    /* Report to DET  */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_GETVERSIONINFO_SID, LINIF_E_PARAM_POINTER);
  }
  else
  #endif /*#if(LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_017*/
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
    /* Copy the vendor Id */
    versioninfo->vendorID = LINIF_VENDOR_ID;
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
    /* Copy the module Id */
    versioninfo->moduleID = LINIF_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = LINIF_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = LINIF_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = LINIF_SW_PATCH_VERSION;
  }
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinIf_CheckWakeup                                     **
**                                                                            **
** Service ID         : 0x60                                                  **
**                                                                            **
** Description        : This function is called when the EcuM detects a       **
**                      wake up for the specific LIN channel.                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : WakeupSource                                          **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GaaDriverApis, LinIf_GaaChannelInfo,            **
**                      LinIf_GaaTrcvDriverApis                               **
**                                                                            **
**                      Function(s) invoked:  Det_ReportError(),              **
**                                                                            **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
*******************************************************************************/
/* @Trace: SWS_LinIf_00378 SWS_LinIf_00503 SWS_LinIf_00566 SWS_LinIf_00689
 * SRS_BSW_00375 SRS_Lin_01514 SRS_BSW_00327 SRS_BSW_00337
 */
#if (LINIF_WAKEUP_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, LINIF_CODE) LinIf_CheckWakeup
                                          (EcuM_WakeupSourceType WakeupSource)
{
  /* @Trace: LinIf_SUD_API_018*/
  Std_ReturnType LddReturnValue;

  /* Change Number to Macro*/
  #if (LINIF_NO_OF_WAKEUP_SOURCES >= LINIF_ONE_CHECK)
  P2CONST(LinIf_WakeupSource, AUTOMATIC, LINIF_APPL_CONST) LpWkpSource;
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  P2CONST(LinIf_DrvApis, AUTOMATIC, LINIF_APPL_CONST) LpDriver;
  #endif/* #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)*/

  #if (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
  uint8 LucLinTrcvDriverIndex;
  uint8 LucLinTrcvDriverChannel;
  #else/* #if (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)*/
  #if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
  uint8 LucLinTrcvDriverChannel;
  #endif
  #endif

  EcuM_WakeupSourceType LddWakeupEvent;

  /* Change Number to Macro*/
  #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
  uint8_least LucNoOfWakeupSources;
  #endif

  Std_ReturnType LddReturnValueFlag;
  /* Initialize LddReturnValue with E_OK */
  LddReturnValue = E_OK;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_019*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_CHECKWAKEUP_SID, LINIF_E_UNINIT);
    /* Set the DET error flag */
    LddReturnValue = E_NOT_OK;
  }

  /* Check for any development error */
  if (E_OK == LddReturnValue)
  #endif /*  (STD_ON == LINIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: LinIf_SUD_API_020*/
    /* Set LddReturnValue to E_NOT_OK */
    LddReturnValueFlag = E_NOT_OK;
    /* Get the pointer to the wakeup structure */
    LpWkpSource = &LinIf_GaaWakeupSource[LINIF_ZERO];

    /* Change Number to Macro*/
    #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
    /* Get the number of wakeup sources into the local variable */
    LucNoOfWakeupSources = (uint8_least)LINIF_NO_OF_WAKEUP_SOURCES;
    do
    {
    #endif
    /* @Trace: LinIf_SUD_API_021*/
      /* Get the wakeup event and store it in a local variable */
      LddWakeupEvent = LpWkpSource->ddWakeupEvent;
      /* Check whether the wakeup event is matched or not */
      if (LddWakeupEvent != WakeupSource)
      {
        /* @Trace: LinIf_SUD_API_022*/
        #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
        /* Decrement the number of wakeup sources */
        LucNoOfWakeupSources--;

        /* Increment wakeup source pointer by one */

        LpWkpSource++;

        #endif
      }
      else
      {
        /* @Trace: LinIf_SUD_API_023*/
        /* Get the channel pointer */
        LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor
          [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]];

        /* Change Number to Macro*/
        #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
        /* Set the wakeup flag to true */
        LucNoOfWakeupSources = (uint8_least)LINIF_ZERO;
        #endif
        /* Setting the return val to E_OK */
        LddReturnValueFlag = E_OK;
        /* Change the channel state to OPERATIONAL --LINIF186*/
        if (LpChannelPtr->pChannelRamData->ucSleepRequested >=
           LINIF_SLEEP_REQUESTED)
        {
          /* @Trace: LinIf_SUD_API_024*/
          /* Change the sleep request to not requested */
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          LpChannelPtr->pChannelRamData->ucSleepRequested = LINIF_ZERO;
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        }
      }

   /* Change Number to Macro*/
   #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
    }while(LINIF_ZERO != LucNoOfWakeupSources);
   #endif

    /* Check whether wakeup flag is true */
    if (E_OK == LddReturnValueFlag)
    {
      /* polyspace +1 DEFECT:DEAD_CODE MISRA2012:14.3,2.1 [Not a defect:Low] "The condition evaluates to different values depend on the diversity of configuration" */
      if (LINIF_LINDRV_WAKEUPSOURCE == (LpWkpSource->ucWakeupSource))
      {
        /* @Trace: LinIf_SUD_API_025*/
        #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Get the pointer to corresponding Lin Driver structure */
        LpDriver = &LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo
		  [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]].ucDriverIndex];
        /* Invoke corresponding Driver Checkwakeup function */
        LddReturnValue = LpDriver->pLinCheckWakeup(LinIf_GaaLtChannelInfo
          [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]].ucDrvChannelId);
        #else
        /* Invoke Lin_Checkwakeup function */
        LddReturnValue = Lin_CheckWakeup(LinIf_GaaLtChannelInfo
          [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]].ucDrvChannelId);
        #endif
      }
      else
      {
        /* @Trace: LinIf_SUD_API_026*/
        #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
        /* Get the pointer to corresponding Lin Trcv Driver structure */
        LucLinTrcvDriverIndex = LinIf_GaaLtChannelInfo
          [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]].ucTrcvDriverIndex;

        if(LINIF_TRCV_NOTCONFIGURED != LucLinTrcvDriverIndex)
        {
          /* @Trace: LinIf_SUD_API_027*/
          /* Invoke corresponding Lin Trcv Driver Checkwakeup function */
          LddReturnValue =
        	LinIf_GaaTrcvDriverApis[LucLinTrcvDriverIndex].pLinTrcvCheckWakeup(
        	LinIf_GaaLtChannelInfo[LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]].
			ucTrcvDrvChannelId);
        }
        #else/*#if (STD_ON == LINIF_MULTIPLE_TRCVDRV_SUPPORT)*/
        #if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
        LucLinTrcvDriverChannel = LinIf_GaaLtChannelInfo
          [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]].ucTrcvDrvChannelId;
        if(LINIF_TRCV_NOTCONFIGURED != LucLinTrcvDriverChannel)
        {
          /* Invoke Lin_Checkwakeup function */
          LddReturnValue = LinTrcv_CheckWakeup(LucLinTrcvDriverChannel);
        }
        #else
        UNUSED(LpWkpSource);
        #endif/* #if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON)*/
        #endif/* #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)*/
      }
    }/*(E_OK == LddReturnValue) */
    #if (LINIF_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* @Trace: LinIf_SUD_API_028*/
      /* Report to DET, if Wakeup sourceId is invalid --LINIF566 */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                       LINIF_CHECKWAKEUP_SID, LINIF_E_PARAM_WAKEUPSOURCE);
      LddReturnValue = E_NOT_OK;
    }
    #endif
  }/*after passing DET Checks */

  #else
  LINIF_UNUSED(WakeupSource);
  LddReturnValue = E_NOT_OK;
  #endif
  /* @Trace: LinIf_SUD_API_029*/
  return(LddReturnValue);
}

#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_Transmit                                        **
**                                                                            **
** Service ID         : 0x04                                                  **
**                                                                            **
** Description        : This function call indicates a request from an upper  **
**                      layer to transmit the frame specified by LinTxPduId   **
**                      This call only marks the sporadic/event triggerred    **
**                      frame as pending for transmission.                    **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LinTxPduId, *PduInfoPtr                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GaaChannelInfo                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(), LinIf_AssociatedBinarySearch()     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00201 SWS_LinIf_00105 SWS_LinIf_00341 SWS_LinIf_00700
 * SWS_LinIf_00106 SWS_LinIf_00570 SWS_LinIf_00575 SWS_LinIf_00719
 * SRS_Lin_01571 SRS_BSW_00327 SRS_Lin_01576
 */
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_Transmit(PduIdType LinTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, LINIF_APPL_CONST) PduInfoPtr)
{
  /* @Trace: LinIf_SUD_API_030*/
  #if((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON))
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST) LpAssociatedFramePtr;
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  Std_ReturnType LddReturnValue;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrorFlag;
  #endif /*(LINIF_DEV_ERROR_DETECT == STD_ON)*/

  LddReturnValue = E_NOT_OK;
  LpAssociatedFramePtr = NULL_PTR;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LblDetErrorFlag = LINIF_FALSE;
  #endif /*(LINIF_DEV_ERROR_DETECT == STD_ON)*/


  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_031*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_TRANSMIT_SID, LINIF_E_UNINIT);
    /* Set the DET error flag */
    LblDetErrorFlag = LINIF_TRUE;
  }
  /* Check If PduInfoPtr is NULL_PTR */
  else if(NULL_PTR == PduInfoPtr)
  {
    /* @Trace: LinIf_SUD_API_032*/
    /* Report to DET */
    (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_TRANSMIT_SID, LINIF_E_PARAM_POINTER);
    /* Set the error flag to TRUE */
    LblDetErrorFlag = LINIF_TRUE;
  }
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
  /* Check If PduInfoPtr->SduDataPtr is NULL_PTR */
  else if(NULL_PTR == PduInfoPtr->SduDataPtr)
  {
    /* @Trace: LinIf_SUD_API_033*/
    /* Report to DET */
    (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_TRANSMIT_SID, LINIF_E_PARAM_POINTER);
    /* Set the error flag to TRUE */
    LblDetErrorFlag = LINIF_TRUE;
  }
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
  else
  {
    /* @Trace: LinIf_SUD_API_034*/
    /* Get the frame pointer of the requested frame */
    LpAssociatedFramePtr = LinIf_AssociatedBinarySearch(LinTxPduId);
    /* Check if the requested is not a sporadic frame and PduId is in range */
    if(LpAssociatedFramePtr == NULL_PTR)
    {
      /* @Trace: LinIf_SUD_API_035*/
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_TRANSMIT_SID, LINIF_E_PARAMETER);
      /* Set the DET error flag */
      LblDetErrorFlag = LINIF_TRUE;
    }
  }
  #endif /*(LINIF_DEV_ERROR_DETECT == STD_ON)*/

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if no development errors occurred */
  if(LINIF_FALSE == LblDetErrorFlag)
  #else /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  /* No development errors occurred */
  LINIF_UNUSED_PTR(PduInfoPtr);
  /* Get the frame pointer of the requested frame */
  LpAssociatedFramePtr = LinIf_AssociatedBinarySearch(LinTxPduId);
  if(LpAssociatedFramePtr != NULL_PTR)
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_036*/
    LpChannelPtr = &LinIf_GaaConfiguration[0].
	pChannelInfor[LpAssociatedFramePtr->ucChannelId];

    #if (STD_ON == LINIF_MASTER_SUPPORT)
    /* implement for SWS_LinIf_00719 - AUTOSAR 4.4.0*/
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    if((LINIF_MASTER_NODE == LpChannelPtr->ddNodeType) &&
	(LINIF_NULL_SCHEDULE == *(LpChannelPtr->pSchId)))
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
	/*TODO: (LINIF_NULL_SCHEDULE == (LpChannelPtr->pChannelRamData)->ddActivSchId)) */
    {
      /* @Trace: LinIf_SUD_API_037*/
      LddReturnValue = E_NOT_OK;
    }
    else
    #endif /*(STD_ON == LINIF_MASTER_SUPPORT)*/
    /* Check if the channel is not in sleep status */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    if(LINIF_CHANNEL_SLEEP != (LpChannelPtr->pChannelRamData)->ucChannelSts)
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    {
      /* @Trace: LinIf_SUD_API_038*/
      LinIf_AssociatedPendingMask(LinTxPduId, LINIF_TRUE);
      /* Set the return value */
      LddReturnValue = E_OK;
    }
    else
    {
      /* Avoid QAC */
    }
  }
  /* @Trace: LinIf_SUD_API_039*/
  return(LddReturnValue);

  #else /* ((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON)) */
  LINIF_UNUSED_PTR(PduInfoPtr);
  LINIF_UNUSED(LinTxPduId);
  return(E_OK);
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinIf_ScheduleRequest                                 **
**                                                                            **
** Service ID         : 0x05                                                  **
**                                                                            **
** Description        : This function can be used simultaneously by different **
**                      upper layers to request schedule table to be executed **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : Channel, Schedule                                     **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GpDbTocPtr, LinIf_GaaComMChannelMap,            **
**                      LinIf_GddMaxComMChannelId, LinIf_GddNoOfChanls,       **
**                      LinIf_GaaChannelInfo                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00202 SWS_LinIf_00389 SWS_LinIf_00563 SWS_LinIf_00567
 * SWS_LinIf_00858
 * SRS_Lin_01564 SRS_BSW_00327 SRS_BSW_00335 SRS_BSW_00413 SRS_BSW_00425
 * SRS_BSW_00452 SRS_Lin_01590
 */
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_ScheduleRequest
  (NetworkHandleType Channel, LinIf_SchHandleType ScheduleIndex)
{
  /* @Trace: LinIf_SUD_API_040*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  NetworkHandleType LddChnlIndex;
  Std_ReturnType LddReturnValue;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucStatus;
  uint8 LucIdx;
  boolean LblErrFlag;
  #endif

  LddReturnValue = E_OK;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LblErrFlag = LINIF_TRUE;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_041*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_SCHEDULEREQUEST_SID, LINIF_E_UNINIT);
    /* Set the return value */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel is out of range */
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_042*/
      /* Report  the error to DET  with LINIF_E_NONEXISTENT_CHANNEL */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_SCHEDULEREQUEST_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_043*/
      /* Get the Channel index */
      LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    }
    if(E_OK == LddReturnValue)
    {
      
      /* @Trace: LinIf_SUD_API_045*/
      LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
      /* Get the Channel Status */
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      LucStatus = (LpChannelPtr->pChannelRamData)->ucChannelSts;
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      if(LucStatus == LINIF_CHANNEL_SLEEP)
      {
        /* @Trace: LinIf_SUD_API_046*/
        /* Report to DET */
        (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
          LINIF_SCHEDULEREQUEST_SID, LINIF_E_SCHEDULE_REQUEST_ERROR);
        /* Set the return value */
        LddReturnValue = E_NOT_OK;
      }
      /* Check if the requested schedule id is out of range */
      if(ScheduleIndex >= LpChannelPtr->ddMaxSchs)
      {
        /* @Trace: LinIf_SUD_API_047*/
        /* Report to DET */
        (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
          LINIF_SCHEDULEREQUEST_SID, LINIF_E_SCHEDULE_REQUEST_ERROR);
        /* Set the return value */
        LddReturnValue = E_NOT_OK;
      }
    } /* No DET */
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif /* #if (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_048*/
    /* Get the Channel index */

    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    /* Get the channel pointer */
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    {
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      *(LpChannelPtr->pSchId) = ScheduleIndex;
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    } /* No development errors occurred */
  }
  /* @Trace: LinIf_SUD_API_049*/
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinIf_GotoSleep                                       **
**                                                                            **
** Service ID         : 0x06                                                  **
**                                                                            **
** Description        : This function initiates transition into sleep mode on **
**                      the selected channel.                                 **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GpDbTocPtr, LinIf_GaaComMChannelMap,            **
**                      LinIf_GddMaxComMChannelId, LinIf_GddNoOfChanls,       **
**                      LinIf_GaaChannelInfo                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError,                                      **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
*******************************************************************************/
/* @Trace: SWS_LinIf_00204 SWS_LinIf_00488 SWS_LinIf_00564 SWS_LinIf_00113
 * SRS_Lin_01523 SRS_BSW_00327 SRS_BSW_00335 SRS_BSW_00452 SRS_Lin_01504
 * SRS_Lin_01596
*/
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_GotoSleep
  (NetworkHandleType Channel)
{
  /* @Trace: LinIf_SUD_API_050*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  /* Redmine #8713 */
  NetworkHandleType LddChnlIndex = (NetworkHandleType)LINIF_ZERO;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddReturnValue;
  uint8 LucIdx;
  boolean LblErrFlag;
  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  #endif

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_051*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_GOTOSLEEP_SID, LINIF_E_UNINIT);
    /* Set the return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_052*/
      /* Report  the error to DET  with LINIF_E_NONEXISTENT_CHANNEL */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_GOTOSLEEP_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {

    /* @Trace: LinIf_SUD_API_055*/
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* Check if already sleep request is not initiated on the bus */

    #if (LINIF_MASTER_SUPPORT == STD_ON)
    if (LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
    {
      if(LINIF_SLEEP_COMMAND_SENT != LpChannelRamData->ucSleepRequested)
      {
        if(LINIF_NULL_SCHEDULE != LpChannelRamData->ddActivSchId)
        {
          /* @Trace: LinIf_SUD_API_056*/
          /* Set the sleep pending bit to sleep requested */
          LpChannelRamData->ucSleepRequested = LINIF_SLEEP_REQUESTED;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_057*/
          /* Set the sleep pending bit to Sleep req pending */
          LpChannelRamData->ucSleepRequested = LINIF_SLEEP_REQ_PENDING;
        }
      }
    }
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_GoToSleep" */
    else
    {
      /* To avoid QAC error */
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_GoToSleep" */

    #endif
    #if (LINIF_SLAVE_SUPPORT == STD_ON)
    if (LINIF_SLAVE_NODE == LpChannelPtr->ddNodeType)
    {
      /* @Trace: LinIf_SUD_API_058*/
      /* Invoke respective Driver Go to sleep internal function */
      #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
      /* Invoke respective Driver Go to sleep internal function */
      (void) LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucDriverIndex].pLinGoToSleepInternal(LinIf_GaaLtChannelInfo
        [LddChnlIndex].ucDrvChannelId);
      #else
      (void) Lin_GoToSleepInternal(LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucDrvChannelId);
      #endif
      /* Change the channel status to sleep */
      LpChannelRamData->ucChannelSts = LINIF_CHANNEL_SLEEP;
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaGoToSleepConfFun[LddChnlIndex])\
        (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
      #else
      LinSM_GotoSleepConfirmation(\
        LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
      #endif
      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      /* Set Sleep Request Pending Flag as false */
      LpChannelRamData->ucSleepRequested = LINIF_ZERO;
      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      /* Clear the wakeup flag */
      LpChannelRamData->blWakeupStatus = LINIF_FALSE;
    }
    else
    {
      /* To avoid QAC error */
    }
    #endif
    /* @Trace: LinIf_SUD_API_059*/
    SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
  }/* No development error is occurred */
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: LinIf_SUD_API_060*/
  return(LddReturnValue);
  #else
  return(E_OK);
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinIf_Wakeup                                          **
**                                                                            **
** Service ID         : 0x07                                                  **
**                                                                            **
** Description        : This call initiates the wake up process on selected   **
**                      controller/ Channel.                                  **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GpDbTocPtr, LinIf_GaaDriverApis                 **
**                      LinIf_GaaComMChannelMap, LinIf_GddMaxComMChannelId,   **
**                      LinIf_GaaChannelInfo, LinIf_GaaLtChannelInfo          **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(), Lin_Wakeup(),                      **
**                      SchM_Enter_LinIf_WAKEUP_CONFCOUNT_PROTECTION          **
**                      SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION            **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
**                      SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION           **
**                      SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION             **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
*******************************************************************************/
/* @Trace: SWS_LinIf_00205 SWS_LinIf_00432 SWS_LinIf_00296 SWS_LinIf_00713
 * SWS_LinIf_00714 SWS_LinIf_00720 SWS_LinIf_00721 SWS_LinIf_00565
 * SRS_Lin_01515 SRS_BSW_00327 SRS_BSW_00335 SRS_Lin_01560 SRS_ES90600_00E_SWP_00216
 */
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_Wakeup
  (NetworkHandleType Channel)
{
  /* @Trace: LinIf_SUD_API_061*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  /*Redmine #8713*/
  NetworkHandleType LddChnlIndex = (NetworkHandleType)LINIF_ZERO;
  Std_ReturnType LddReturnValue;
  uint8 LucSleepReqSts;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIdx;
  boolean LblErrFlag;
  LblErrFlag = LINIF_TRUE;
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */

  /* Redmine #8713 Remove dead assignment
  LddChnlIndex = (NetworkHandleType)LINIF_ZERO;
  */
  LddReturnValue = E_OK;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_062*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, LINIF_WAKEUP_SID,
      LINIF_E_UNINIT);
    /* Set the return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_063*/
      /* Report  the error to DET  with LINIF_E_NONEXISTENT_CHANNEL */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_WAKEUP_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_066*/
    /* Get the channel pointer */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    /* Get the pointer of the Channel Ram Data */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */

    SchM_Enter_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
    /* Set Wakeup counter as 1 */
    LpChannelRamData->ucWakeupConfirmCount = LINIF_ONE;
    SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION();

    if(LINIF_CHANNEL_SLEEP == LpChannelRamData->ucChannelSts)
    {
      if (LINIF_FALSE == LpChannelRamData->blWakeupStatus)
      {
        #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Invoke respective Driver Wakeup function and check its return value*/
        /* @Trace: LinIf_SUD_API_067*/
        LpChannelRamData->ucWakeupSignalSent
            = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
              ucDriverIndex].
                pLinWakeup(LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId);
        #else
        LpChannelRamData->ucWakeupSignalSent
            = Lin_Wakeup(LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId);
        #endif
      }
      else
      {
        #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Invoke respective Driver Wakeup function and check its return value*/
        /* @Trace: LinIf_SUD_API_068*/
        LpChannelRamData->ucWakeupSignalSent
          = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
            ucDriverIndex].pLinWakeupInternal(\
                          LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId);
        #else
        LpChannelRamData->ucWakeupSignalSent = Lin_WakeupInternal(\
                     LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId);
        #endif
      }

      /* @Trace: LinIf_SUD_API_069*/
      LddReturnValue = LpChannelRamData->ucWakeupSignalSent;
      SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION();
      /* Change the channel state to OPERATIONAL only if the transmission of
      wakeup signal was successful. */
      if (E_OK == LpChannelRamData->ucWakeupSignalSent)
      {
        /* @Trace: LinIf_SUD_API_070*/
        /* Clear the wakeup flag */
        LpChannelRamData->blWakeupStatus = LINIF_FALSE;
        LpChannelRamData->ucChannelSts = LINIF_CHANNEL_OPERATIONAL;
        #if (LINIF_SLAVE_SUPPORT == STD_ON)
        if (LINIF_SLAVE_NODE == LpChannelPtr->ddNodeType)
        {
          /* @Trace: LinIf_SUD_API_520 */
          /* Increase number wake-up signal sent */
          LpChannelRamData->ucNumberWakeupSignalSent++;
          /* Initialization delay timer */
          LpChannelRamData->ulCounterDelayWakeupSignalSent = LpChannelPtr->ulCounterDelayWakeupSignalSent;
        }
        #endif /* (LINIF_SLAVE_NODE == LpChannelPtr->ddNodeType) */
      }
      else
      {
        /* Invoke Wakeup confirmation for Upper Layer */
        #if (LINIF_CDD_SUPPORT == STD_ON)
        (LinIf_GaaWakeupConfFun [LddChnlIndex])
          (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_FALSE);
        #else
        /* @Trace: LinIf_SUD_API_072*/
        LinSM_WakeupConfirmation(
          LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_FALSE);
        #endif
      }
      /* @Trace: LinIf_SUD_API_073*/
      SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
    }
    else /* Channel is not in sleep state */
    {
      /* @Trace: LinIf_SUD_API_074*/
      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      LucSleepReqSts = LpChannelRamData->ucSleepRequested;
      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      #if (LINIF_MASTER_SUPPORT == STD_ON)
      if (LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
      {
        /* If sleep request is pending, i.e. not initiated on the bus */
        if((LINIF_SLEEP_REQ_PENDING == LucSleepReqSts) ||
          (LINIF_SLEEP_REQUESTED == LucSleepReqSts))
        {
          /* @Trace: LinIf_SUD_API_075*/
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Clear the sleep requested status */
          LpChannelRamData->ucSleepRequested = LINIF_ZERO;
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        }
        /* Check if already the sleep command is initiated on the bus */
        else if(LINIF_SLEEP_COMMAND_SENT == LucSleepReqSts)
        {
          /* @Trace: LinIf_SUD_API_076*/
          SchM_Enter_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
          LpChannelRamData->ucWakeupConfirmCount +=
                                    (uint8)LpChannelRamData->usDelayCounter;
          SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Set the sleep pending bit */
          LpChannelRamData->ucSleepRequested = LINIF_WAKEUP_REQUESTED;
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        }
        else
        {
          /* Avoid QAC */
        }
      }
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
      else
      #endif
      {
        #if (LINIF_SLAVE_SUPPORT == STD_ON)
        if (LINIF_SLEEP_COMMAND_RECEIVED == LucSleepReqSts)
        {
          /* @Trace: LinIf_SUD_API_077*/
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Set the sleep pending bit */
          LpChannelRamData->ucSleepRequested = LINIF_WAKEUP_REQUESTED;
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        }
        else
        {
          /* Avoid QAC */
        }
        #endif
      }
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
    } /* Channel is not in sleep state */
  }/* No development error is occurred */
  /* @Trace: LinIf_SUD_API_078*/
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinIf_SetTrcvMode                                     **
**                                                                            **
** Service ID         : 0x08                                                  **
**                                                                            **
** Description        : Set the given LIN transceiver to the given mode.      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : Channel, TransceiverMode                              **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpDbTocPtr,                   **
**                      LinIf_GpFirstChannel, LinIf_GaaComMChannelMap,        **
**                      LinIf_GaaTrcvDriverApis, LinIf_GddMaxComMChannelId,   **
**                      LinIf_GddNoOfChanls, LinIf_GaaLtChannelInfo           **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(), LinSM_Wakeup_Confirmation(),       **
**                      LinTrcv_SetOpMode()                                   **
*******************************************************************************/
/* @Trace: SWS_LinIf_00544 SWS_LinIf_00536 SWS_LinIf_00537 SWS_LinIf_00538
 * SWS_LinIf_00539 SWS_LinIf_00540 SWS_LinIf_00634
 * SRS_Lin_01584 SRS_Lin_01585 SRS_Lin_01586 SRS_BSW_00327
 */
#if(LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_SetTrcvMode(\
              NetworkHandleType Channel, LinTrcv_TrcvModeType TransceiverMode)
{
  /* @Trace: LinIf_SUD_API_079*/
  NetworkHandleType LddChnlIndex = (NetworkHandleType)LINIF_ZERO;
  Std_ReturnType LddReturnValue;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIdx;
  boolean LblErrFlag;
  LblErrFlag = LINIF_TRUE;
  LddReturnValue = E_OK;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_080*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                      LINIF_SETTRCVMODE_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_081*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                            LINIF_SETTRCVMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      #if((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
          (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON))
      /* @Trace: LinIf_SUD_API_082*/
      LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
      #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
                (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON) */
    }
    /* check if transceiver driver is not referenced to
                                                   the corresponding channel*/
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    if((LINIF_TRCV_NOTCONFIGURED == \
            LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDriverIndex)
      || (LINIF_TRCV_NOTCONFIGURED == \
        LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId ))
    {
      /* @Trace: LinIf_SUD_API_084*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                              LINIF_SETTRCVMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    #else
    #if(LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)
    /* check if transceiver driver is not referenced to the corresponding channel*/
    /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* 
    polyspace-begin MISRA2012:2.1 [Justified:Low] "It's changed in GEN code"
    polyspace-begin MISRA2012:14.3 [Justified:Low] "It's changed in GEN code" 
    */
    if(LINIF_TRCV_NOTCONFIGURED == \
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId)
    {
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                              LINIF_SETTRCVMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    /* 
    polyspace-end MISRA2012:2.1 [Justified:Low] "It's changed in GEN code"
    polyspace-end MISRA2012:14.3 [Justified:Low] "It's changed in GEN code" 
    */
    /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    #endif /* (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON) */
    #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) */

    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_SetTrcvMode" */
    if((uint8)TransceiverMode > LINIF_TRCV_INVALID_MODE)

    {
      /* @Trace: LinIf_SUD_API_085*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                              LINIF_SETTRCVMODE_SID, LINIF_E_TRCV_INV_MODE);
      LddReturnValue = E_NOT_OK;
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_SetTrcvMode" */
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_086*/
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    LddReturnValue = \
        LinIf_GaaTrcvDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].\
          ucTrcvDriverIndex].pSetOpMode(LinIf_GaaLtChannelInfo[LddChnlIndex].\
                                          ucTrcvDrvChannelId, TransceiverMode);
    #else

    LddReturnValue = LinTrcv_SetOpMode(LinIf_GaaLtChannelInfo[LddChnlIndex].\
                                          ucTrcvDrvChannelId, TransceiverMode);
    #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) */
  }
  /* @Trace: LinIf_SUD_API_087*/
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if(LINIF_TRCV_DRIVER_SUPPORT == STD_ON)*/

/*******************************************************************************
** Function Name      : LinIf_GetTrcvMode                                     **
**                                                                            **
** Service ID         : 0x09                                                  **
**                                                                            **
** Description        : Returns the actual state of a LIN Transceiver Driver. **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : TransceiverModePtr                                    **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GpDbTocPtr, LinIf_GaaComMChannelMap,            **
**                      LinIf_GaaTrcvDriverApis[], LinIf_GddMaxComMChannelId, **
**                      LinIf_GddNoOfChanls                                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(), LinTrcv_GetOpMode()                **
*******************************************************************************/
/* @Trace: SWS_LinIf_00545 SWS_LinIf_00541 SWS_LinIf_00546 SWS_LinIf_00571
 * SWS_LinIf_00635
 * SRS_Lin_01587 SRS_BSW_00327
 */
#if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_GetTrcvMode(NetworkHandleType Channel,
  P2VAR(LinTrcv_TrcvModeType, AUTOMATIC, LINIF_APPL_DATA) TransceiverModePtr)
{
  /* @Trace: LinIf_SUD_API_088*/
  NetworkHandleType LddChnlIndex;
  Std_ReturnType LddReturnValue;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIdx;
  boolean LblErrFlag;

  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_089*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                      LINIF_GETTRCVMODE_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_090*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                            LINIF_GETTRCVMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      #if((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
          (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON))
      /* Get the Channel index */
      LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
      #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
                (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)) */
      /* check if transceiver driver is not referenced to
                                              the corresponding channel*/
      #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
      if((LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDriverIndex == \
                                                    LINIF_TRCV_NOTCONFIGURED)
        || (LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId == \
                                              LINIF_TRCV_NOTCONFIGURED))
      {
        /* @Trace: LinIf_SUD_API_093*/
        (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                            LINIF_GETTRCVMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
        LddReturnValue = E_NOT_OK;
      }
      /* check if transceiver driver is not referenced to
                                                the corresponding channel*/
      #else
      #if(LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)
      /* 
      polyspace-begin MISRA2012:2.1 [Justified:Low] "It's changed in GEN code" 
      polyspace-begin MISRA2012:14.3 [Justified:Low] "It's changed in GEN code" 
      */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_SetTrcvMode" */
	  /* The value of LddChnlIndex is generated by gentool and is always less
        than LINIF_IF_CHANNELS, so the below conditon is redundant */
      //if(LddChnlIndex < LINIF_IF_CHANNELS)
      {
        if(LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId == \
                                                      LINIF_TRCV_NOTCONFIGURED)
        {
          (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                              LINIF_GETTRCVMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
          LddReturnValue = E_NOT_OK;
        }
      }
	  /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_SetTrcvMode" */
      /* 
      polyspace-end MISRA2012:2.1 [Justified:Low] "It's changed in GEN code" 
      polyspace-end MISRA2012:14.3 [Justified:Low] "It's changed in GEN code"
      */
      #endif /* (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON) */
      #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) */
      /* Check if the TransceiverModePtr is NULL */
      if(TransceiverModePtr == NULL_PTR)
      {
        /* @Trace: LinIf_SUD_API_094*/
        (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                          LINIF_GETTRCVMODE_SID, LINIF_E_PARAM_POINTER);
        LddReturnValue = E_NOT_OK;
      }
    }
  }
  /* Check if no development errors occurred */
  if(E_OK == LddReturnValue)
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the Channel index */
    /* @Trace: LinIf_SUD_API_095*/
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    LddReturnValue = LinIf_GaaTrcvDriverApis[\
          LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDriverIndex].pGetOpMode(\
              LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId, \
                                                          TransceiverModePtr);
    #else

    LddReturnValue = \
     LinTrcv_GetOpMode(LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId \
                                                           ,TransceiverModePtr);
    #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) */
  }
  /* @Trace: LinIf_SUD_API_096*/
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON) */
/*******************************************************************************
** Function Name      : LinIf_GetTrcvWakeupReason                             **
**                                                                            **
** Service ID         : 0x0A                                                  **
**                                                                            **
** Description        : Returns the reason for the wake up that has been      **
**                      detecteted by the LIN Transceiver Driver.             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : TrcvWuReasonPtr                                       **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GpDbTocPtr, LinIf_GaaComMChannelMap,            **
**                      LinIf_GaaTrcvDriverApis[], LinIf_GddMaxComMChannelId, **
**                      LinIf_GddNoOfChanls                                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(), LinTrcv_GetOpMode(),               **
**                      LinTrcv_GetBusWuReason()                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_LinIf_00547 SWS_LinIf_00548 SWS_LinIf_00549 SWS_LinIf_00573
 * SWS_LinIf_00572 SWS_LinIf_00636
 * SRS_Lin_01588 SRS_BSW_00327
 */
#if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_GetTrcvWakeupReason
  (NetworkHandleType Channel, P2VAR(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, \
                                              LINIF_APPL_DATA) TrcvWuReasonPtr)
{
  /* @Trace: LinIf_SUD_API_097*/
  NetworkHandleType LddChnlIndex;
  Std_ReturnType LddReturnValue;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if no development errors occurred */
  LddReturnValue = LinIf_DetGetTrcvWakeupReason(Channel, TrcvWuReasonPtr);
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_106*/
    /* Get the Channel index */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    LddReturnValue = LinIf_GaaTrcvDriverApis[LinIf_GaaLtChannelInfo[\
      LddChnlIndex].ucTrcvDriverIndex].pGetBusWuReason(LinIf_GaaLtChannelInfo[\
                            LddChnlIndex].ucTrcvDrvChannelId, TrcvWuReasonPtr);
    #else

    LddReturnValue = LinTrcv_GetBusWuReason(\
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId,TrcvWuReasonPtr);
    #endif
  }
  /* @Trace: LinIf_SUD_API_107*/
  LINIF_UNUSED(Channel);
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON) */
/*******************************************************************************
** Function Name      : LinIf_SetTrcvWakeupMode                               **
**                                                                            **
** Service ID         : 0x0b                                                  **
**                                                                            **
** Description        : This enables, disables and clears the notification    **
**                          for wakeup events on the addressed network        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : Channel, LinTrcvWakeupMode                            **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts,                                     **
**                      LinIf_GaaComMChannelMap, LinIf_GaaLtChannelInfo       **
**                      LinIf_GaaTrcvDriverApis, LinIf_GddMaxComMChannelId,   **
**                      LinIf_GddNoOfChanls                                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(),                                    **
**                      LinTrcv_SetWakeupMode()                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_LinIf_00550 SWS_LinIf_00551 SWS_LinIf_00595 SWS_LinIf_00596
 * SWS_LinIf_00637
 * SRS_Lin_01589 SRS_BSW_00327
 */
#if(LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_SetTrcvWakeupMode
  (NetworkHandleType Channel, LinTrcv_TrcvWakeupModeType LinTrcvWakeupMode)
{
  /* @Trace: LinIf_SUD_API_108*/
  NetworkHandleType LddChnlIndex = (NetworkHandleType)LINIF_ZERO;
  Std_ReturnType LddReturnValue;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = LinIf_DetSetTrcvWakeupMode(Channel, LinTrcvWakeupMode);

  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_115*/
    /* Get the Channel index */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    LddReturnValue = LinIf_GaaTrcvDriverApis[LinIf_GaaLtChannelInfo[\
    LddChnlIndex].ucTrcvDriverIndex].pSetWakeupMode
    (LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId,LinTrcvWakeupMode);
    #else
    LddReturnValue = LinTrcv_SetWakeupMode(\
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId, \
                                                             LinTrcvWakeupMode);
    #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) */
  }
  /* @Trace: LinIf_SUD_API_116*/
  LINIF_UNUSED(Channel);
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_HeaderIndication                                **
**                                                                            **
** Service ID         : 0x78                                                  **
**                                                                            **
** Description        : The LIN Driver will call this function to report a    **
**                      received LIN header. This function is only applicable **
**                      for LIN slave nodes (available only if the ECU has    **
**                      any LIN slave channel).                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant for different Channels. Non reentrant for   **
**                                                        the same Channel.   **
**                                                                            **
** Input Parameters   : Channel, PduInfoPtr                                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Function(s) invoked:                                  **
**                      LinIf_GetSchEntryIdx, Det_ReportError,                **
**                      PduR_LinIfTriggerTransmit,                            **
*******************************************************************************/
/* @Trace: SWS_LinIf_91004 SWS_LinIf_00843 SWS_LinIf_00844 SWS_LinIf_00845
 * SWS_LinIf_00846 SWS_LinIf_00863
 * SRS_BSW_00327 SRS_Lin_01558
 */
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_HeaderIndication
                             (NetworkHandleType Channel, Lin_PduType* PduPtr)
{
  /* @Trace: LinIf_SUD_API_117*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  uint8 LucFrameIdx;
  Lin_FramePidType LddPid;
  uint8 LucFrameId;
  uint8 LucP0;
  uint8 LucP1;
  uint8 LucByte;
  uint8 LucValidPid;
  uint8 LddFrameType;
  NetworkHandleType LddChnlIndex;
  PduInfoType LddUpPduInfo;
  #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
  uint8 LucAssocFrms;
  uint8 LucAssocCount;

  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST) LpAssociatedFrame;
  #endif
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  Std_ReturnType LddReturnValue;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIdx;
  boolean LblErrFlag;
  LblErrFlag = LINIF_TRUE;
  LddReturnValue = E_OK;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_118*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                  LINIF_HEADERINDICATION_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_119*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                      LINIF_HEADERINDICATION_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
    /* Check If PduPtr is NULL_PTR */
    if(NULL_PTR == PduPtr)
    {
      /* @Trace: LinIf_SUD_API_122*/
      /* Report to DET */
      (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                        LINIF_HEADERINDICATION_SID, LINIF_E_PARAM_POINTER);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* To Avoid QAC Warnings */
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_123*/
    /* Get Channel Index */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    /* Get Channel Pointer Variable */
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    /* Get Channel Ram Data Variable of current Channel */
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* Initialize Reception pending flag of all Frame Types*/
    LpChannelRamData->blTxRequestPending = LINIF_FALSE;
    /* Get the pointer to Frame RAM data */
    LpFrameRamData = LpChannelPtr->pFrameRamData;
    /* Set Delay Counter as Bus Idle Timeout value */
    LpChannelRamData->usDelayCounter = LpChannelPtr->usBusIdleTimeout;
    /* Get Pid */
    LddPid = PduPtr->Pid;
    /* Get Frame Id */
    LucFrameId = LddPid & LINIF_FRAME_ID_FILTER_MASK;
    /* Caculate the value of Parity bit 0 */
    LINIF_PARITY_BIT_P0_CALCULATE(LucP0, LucFrameId);
    /* Caculate the value of Parity bit 1 */
    LINIF_PARITY_BIT_P1_CALCULATE(LucP1, LucFrameId);
    /* Get the index of LinIf_GaaChannelIdMapping */
    LucByte = (uint8) LucFrameId / 8;
    /* Check either request Pid is valid or not */
    LucValidPid = LinIf_GaaFrameIdMapping[LddChnlIndex][LucByte] & \
                                              (1 << (LddPid - (8 * LucByte)));
    if (((LINIF_ZERO != LucValidPid) && 
        (LucP0 == (LddPid & LINIF_PARITY_BIT_P0_MASK)) && \
               (LucP1 == (LddPid & LINIF_PARITY_BIT_P1_MASK)))
                  || (LINIF_MRF_PID == LddPid) || (LINIF_SRF_PID == LddPid))
    {
      /* @Trace: LinIf_SUD_API_124*/
      /* Set active Pid */
      LpChannelRamData->ucActivePid = LddPid;
      /* Get the Frame index in the channel */
      LucFrameIdx = LinIf_GetFrameIndex(Channel, LddPid);
      /* Get the pointer of Frame */
      LpFramePtr = &LinIf_GaaConfiguration[0].pFrameInfo[\
                            LpFrameRamData->pFrameIndexTable[LucFrameIdx]];
      /* Check if Wake Up request is sent */
      if (E_OK == LpChannelRamData->ucWakeupSignalSent)
      {
        /* @Trace: LinIf_SUD_API_125*/
        /* Invoke Wakeup confirmation for Upper Layer */
        #if (LINIF_CDD_SUPPORT == STD_ON)
        (LinIf_GaaWakeupConfFun [LddChnlIndex])
          (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
        #else
        LinSM_WakeupConfirmation(
          LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
        #endif
        /* Clear the WakeupSignalSent*/
        LpChannelRamData->ucWakeupSignalSent = E_NOT_OK;
        /* Update the channel status */
        LpChannelRamData->ucChannelSts = LINIF_CHANNEL_OPERATIONAL;

        /* Reset counter number of wake-up signal sent */
        LpChannelRamData->ucNumberWakeupSignalSent = LINIF_ZERO;
        /* Reset counter number of block wake-up */
        LpChannelRamData->ucNumberBlockWakeup = LINIF_ZERO;
        /* Reset counter delay between each block wake-up */
        LpChannelRamData->ulCounterDelayBlockWakeup = LpChannelPtr->ulCounterDelayBlockWakeup;
      }
      /* @Trace: LinIf_SUD_API_126*/
      /* Get Frame Type */
      LddFrameType = LpFramePtr->ddFrameType;
      switch(LddFrameType)
      {
        case LINIF_UNCONDITIONAL_FRAME:
        {

          if (LINIF_FRAMERESPONSE_TX == LpFramePtr->ddDrc)
          {
            /* @Trace: LinIf_SUD_API_127*/
            /* Set Tx Request Pending Flag as true */
            LpChannelRamData->blTxRequestPending = LINIF_TRUE;
            /* Set Length of Sdu as 8 */
            LddUpPduInfo.SduLength = LpFramePtr->ddDl;
            /* Set Sdu Data buffer */
            LddUpPduInfo.SduDataPtr = PduPtr->SduPtr;
            /* Get the response data from PDU Router */
            #if (LINIF_CDD_SUPPORT == STD_ON)
            LddReturnValue = \
                (LinIf_GaaTriggerTransmitFun[\
                    LpFrameRamData->pFrameIndexTable[LucFrameIdx]]
                      (LinIf_GaaGlobalHandleId[LucFrameIdx], &LddUpPduInfo));
            #else
            LddReturnValue = \
                PduR_LinIfTriggerTransmit(\
                      LinIf_GaaGlobalHandleId[LucFrameIdx], &LddUpPduInfo);
            #endif
            if (E_OK == LddReturnValue)
            {
              /* @Trace: LinIf_SUD_API_128*/
              /* Update PduPtr Infor */
              PduPtr->Cs = LpFramePtr->ddCs;
              PduPtr->Dl = LpFramePtr->ddDl;
              PduPtr->Drc = LpFramePtr->ddDrc;
            }
            else
            {
              /* @Trace: LinIf_SUD_API_129*/
              /* Ignore this Frame */
              PduPtr->Drc = LINIF_FRAMERESPONSE_IGNORE;
            }
          }
          else if (LINIF_FRAMERESPONSE_RX == LpFramePtr->ddDrc)
          {
            /* @Trace: LinIf_SUD_API_130*/
            /* Set Rx Request Pending Flag as true */
            LpChannelRamData->blRxRequestPending = LINIF_TRUE;
            /* Update PduPtr Infor */
            PduPtr->Cs = LpFramePtr->ddCs;
            PduPtr->Dl = LpFramePtr->ddDl;
            PduPtr->Drc = LpFramePtr->ddDrc;
          }
          else
          {
            /* @Trace: LinIf_SUD_API_131*/
            /* Ignore this Frame */
            PduPtr->Drc = LINIF_FRAMERESPONSE_IGNORE;
          }
          /* @Trace: LinIf_SUD_API_132*/
          break;
        }
        #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
        case LINIF_EVENT_TRIGGERED_FRAME:
        {
          /* @Trace: LinIf_SUD_API_133*/
          /* Set Tx Request Pending Flag as true */
          LpChannelRamData->blTxRequestPending = LINIF_TRUE;
          /* Set Associated Frame Counter as 0 */
          LucAssocCount = LINIF_ZERO;
          /* Get the number of Associated Frame in this Configuration */
          LucAssocFrms = LpChannelPtr->usNoAssociatedFrm;
          /* Set Length of Sdu as 8 */
          LddUpPduInfo.SduLength = LpFramePtr->ddDl;
          /* Set Sdu Data buffer */
          LddUpPduInfo.SduDataPtr = PduPtr->SduPtr;
          do
          {
            /* @Trace: LinIf_SUD_API_134*/
            /* Get the First Associated Frame */
            LpAssociatedFrame = \
                      &(LpChannelPtr->pFistAssociatedFrmPtr[LucAssocCount]);
            /* Check if the associated frame is pending for transmission */
            if((*(LpAssociatedFrame->pPendingSts) & \
              (LpAssociatedFrame->ucPendStsMask)) == \
                (LpAssociatedFrame->ucPendStsMask))
            {
              /* @Trace: LinIf_SUD_API_135*/
              LpFramePtr = LpAssociatedFrame->pAssociatedFrame;
              /* Set the counter to max value to break the while loop */
              LucAssocCount = (uint8)LucAssocFrms;
              /* Get the response data from PDU Router */

              #if (LINIF_CDD_SUPPORT == STD_ON)
              LddReturnValue = \
                  (LinIf_GaaTriggerTransmitFun[\
                      LpFrameRamData->pFrameIndexTable[LucFrameIdx]]
                        (LinIf_GaaGlobalHandleId[LucFrameIdx], &LddUpPduInfo));
              #else
              LddReturnValue = 
                  PduR_LinIfTriggerTransmit(
                        LinIf_GaaGlobalHandleId[LucFrameIdx], &LddUpPduInfo);
              #endif
              if (E_OK == LddReturnValue)
              {
                #if (LINIF_DEV_ERROR_DETECT == STD_ON)
                if(NULL_PTR == PduPtr->SduPtr)
                {
                  /* @Trace: LinIf_SUD_API_136*/
                  /* Report to DET */
                  (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                            LINIF_HEADERINDICATION_SID, LINIF_E_PARAM_POINTER);
                  /* Set the error flag to TRUE */
                  LddReturnValue = E_NOT_OK;
                }
                else
                #endif
                {
                  /* @Trace: LinIf_SUD_API_137*/
                  /* Update PduPtr Infor */
                  PduPtr->Cs = LpFramePtr->ddCs;
                  PduPtr->Dl = LpFramePtr->ddDl;
                  PduPtr->Drc = LpFramePtr->ddDrc;
                }
              }
              else
              {
                /* @Trace: LinIf_SUD_API_138*/
                /* Ignore this Frame */
                PduPtr->Drc = LINIF_FRAMERESPONSE_IGNORE;
              }
            }
            else
            {
              /* @Trace: LinIf_SUD_API_139*/
              LucAssocCount++;
            }
          }while(LucAssocCount < LucAssocFrms);
          /* @Trace: LinIf_SUD_API_140*/
          break;
        }
        #endif
        #if(LINTP_SUPPORT == STD_ON)
        case LINIF_MRF_FRAME:
        {
          /* @Trace: LinIf_SUD_API_141*/
          break;
        }
        case LINIF_SRF_FRAME:
        {
          /* @Trace: LinIf_SUD_API_142*/
          break;
        }
        #endif
        default:
        /* @Trace: LinIf_SUD_API_143*/
          break;
      }
    }
    else
    {
      /* @Trace: LinIf_SUD_API_144*/
      /* Ignore this Frame */
      PduPtr->Drc = LINIF_FRAMERESPONSE_IGNORE;
    }
  }
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  else
  {
  }
  #endif
  /* @Trace: LinIf_SUD_API_145*/
  return (LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_RxIndication                                    **
**                                                                            **
** Service ID         : 0x79                                                  **
**                                                                            **
** Description        : The LIN Driver will call this function to report a    **
**                      successfully received response and provides the       **
**                      reception data to the LIN Interface. This function is **
**                      only applicable for LIN slave nodes (available only   **
**                      if the ECU has any LIN slave channel).                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant for different Channels. Non reentrant for   **
**                                                        the same Channel.   **
**                                                                            **
** Input Parameters   : Channel, Lin_SduPtr                                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_LinIf_STATUS_PROTECTION                    **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
**                      SchM_Exit_LinIf_STATUS_PROTECTION                     **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
*******************************************************************************/
/* @Trace: SWS_LinIf_91005 SWS_LinIf_00848 SWS_LinIf_00849 SWS_LinIf_00850
 * SWS_LinIf_00864
 * SRS_BSW_00327 SRS_Lin_01502
 */
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_RxIndication
                                (NetworkHandleType Channel, uint8* Lin_SduPtr)
{ 
  /* @Trace: LinIf_SUD_API_146*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  PduInfoType LddRxData;
  uint8 LddFrameType;
  uint16 LucFrameIdx;
  NetworkHandleType LddChnlIndex;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddReturnValue;
  uint8 LucIdx;
  boolean LblErrFlag;
  #endif
  uint8 lucNad;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_147*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                  LINIF_RXINDICATION_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_148*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                        LINIF_RXINDICATION_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
    /* Check If Lin_SduPtr is NULL_PTR */
    if(NULL_PTR == Lin_SduPtr)
    {
      /* @Trace: LinIf_SUD_API_151*/
      /* Report to DET */
      (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                        LINIF_RXINDICATION_SID, LINIF_E_PARAM_POINTER);
      LddReturnValue = E_NOT_OK;
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_152*/
    /* Get Channel Index */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    /* Get Channel Pointer Variable */
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    /* Get Channel Ram Data Variable of current Channel */
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* Set Delay Counter as Bus Idle Timeout value */
    LpChannelRamData->usDelayCounter = LpChannelPtr->usBusIdleTimeout;
    /* Get the pointer to Frame RAM data */
    LpFrameRamData = LpChannelPtr->pFrameRamData;
    if (LINIF_MRF_PID == LpChannelRamData->ucActivePid)
    {
      /* @Trace: LinIf_SUD_API_153*/
    	LddFrameType = LINIF_MRF_FRAME;
    	LddRxData.SduLength = LINIF_MRF_FRAME_LEN;
    }
    else if (LINIF_SRF_PID == LpChannelRamData->ucActivePid)
    {
      /* @Trace: LinIf_SUD_API_154*/
    	LddFrameType = LINIF_SRF_FRAME;
    	LddRxData.SduLength = LINIF_SRF_FRAME_LEN;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_155*/
    /* Get the scheduler entry index */
    LucFrameIdx = LinIf_GetFrameIndex(Channel, LpChannelRamData->ucActivePid);
    /* Get the pointer of Frame */
    LpFramePtr = &LinIf_GaaConfiguration[0].pFrameInfo[\
                            LpFrameRamData->pFrameIndexTable[LucFrameIdx]];
    /* Get Frame Type */
    LddFrameType = LpFramePtr->ddFrameType;
    /* Get Sdu Length */
    LddRxData.SduLength = LpFramePtr->ddDl;
    }
    /* @Trace: LinIf_SUD_API_156*/
    /* Get Sdu Data Pointer */
    LddRxData.SduDataPtr = Lin_SduPtr;
    /*Get NAD value*/
    lucNad = Lin_SduPtr[0];
    switch(LddFrameType)
    {
      case LINIF_UNCONDITIONAL_FRAME:
      {
        /* @Trace: LinIf_SUD_API_157*/
        /* Enter protection area */
        SchM_Enter_LinIf_STATUS_PROTECTION();
        if (LINIF_TRUE == LpChannelRamData->blRxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_158*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* Invoke the upper layer confirmation callback */
          #if (LINIF_CDD_SUPPORT == STD_ON)
          (LinIf_GaaRxIndFun[LpFrameRamData->pFrameIndexTable[LucFrameIdx]](\
                            LinIf_GaaGlobalHandleId[LucFrameIdx], &LddRxData));
          #elif(LINIF_RX_LPDU == STD_ON)
          PduR_LinIfRxIndication(\
                            LinIf_GaaGlobalHandleId[LucFrameIdx], &LddRxData);
          #endif

          LpChannelRamData->blRxRequestPending = LINIF_FALSE;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_159*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
        }
        /* @Trace: LinIf_SUD_API_160*/
        break;
      }
      case LINIF_MRF_FRAME:
      {
        /* @Trace: LinIf_SUD_API_161*/
        /* Enter protection area */
        SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        if (LINIF_ZERO == lucNad) 
        {
          /* @Trace: LinIf_SUD_API_162*/
          /* Exit protection area */
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Invoke the upper layer confirmation callback */
          #if (LINIF_CDD_SUPPORT == STD_ON)
          (LinIf_GaaGoToSleepIndFun[LddChnlIndex])(Channel);
          #else
          LinSM_GotoSleepIndication(Channel);
          #endif
          LINIF_UNUSED(LucFrameIdx);
        }
        else
        {
          /* @Trace: LinIf_SUD_API_163*/
          /* Exit protection area */
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        }

        /* @Trace: LinIf_SUD_API_164*/
        break;
      }
      default:
        /* @Trace: LinIf_SUD_API_165*/
        break;
    }
  }/* No development error is occurred */
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* To Avoid QAC Warnings */
  }
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_TxConfirmation                                  **
**                                                                            **
** Service ID         : 0x7a                                                  **
**                                                                            **
** Description        : The LIN Driver will call this function to report a    **
**                      successfully transmitted response.                    **
**                      This function is only applicable for LIN slave nodes  **
**                      (available only if the ECU has any LIN slave channel).**
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant for different Channels. Non reentrant for   **
**                                                        the same Channel.   **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : None                                                  **
*******************************************************************************/
/* @Trace: SWS_LinIf_91006 SWS_LinIf_00852 SWS_LinIf_00853 SWS_LinIf_00865
 * SRS_BSW_00327
 */
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_TxConfirmation(NetworkHandleType Channel)
{
  /* @Trace: LinIf_SUD_API_166*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  uint16 LucFrameIdx;
  NetworkHandleType LddChnlIndex;
  uint8 LucRespErrSignal;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddReturnValue;
  uint8 LucIdx;
  boolean LblErrFlag;
  #endif

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_167*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                  LINIF_TXCONFIRMATION_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_168*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                        LINIF_TXCONFIRMATION_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_171*/
    /* Get Channel Index */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    /* Get Channel Pointer Variable */
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    /* Get Channel Ram Data Variable of current Channel */
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* Get the pointer to Frame RAM data */
    LpFrameRamData = LpChannelPtr->pFrameRamData;
    /* Set Delay Counter as Bus Idle Timeout value */
    LpChannelRamData->usDelayCounter = LpChannelPtr->usBusIdleTimeout;
    /* Get the scheduler entry index */
    LucFrameIdx = LinIf_GetFrameIndex(Channel, LpChannelRamData->ucActivePid);
    /* Get the pointer of Frame */
    LpFramePtr = &LinIf_GaaConfiguration[0].pFrameInfo[\
                            LpFrameRamData->pFrameIndexTable[LucFrameIdx]];
    if (LINIF_TRUE == LpChannelRamData->blTxRequestPending)
    {
      /* @Trace: LinIf_SUD_API_172*/
      /* Set Pending flag of Tx as */
      LpChannelRamData->blTxRequestPending = LINIF_FALSE;
      /* Invoke the upper layer confirmation callback */
      #if (LINIF_CDD_SUPPORT == STD_ON)
              (LinIf_GaaTxConfirmationFun[\
                      LpFrameRamData->pFrameIndexTable[LucFrameIdx]])(\
                              LinIf_GaaGlobalHandleId[LucFrameIdx], LINIF_TRUE);
      #elif(LINIF_TX_LPDU == STD_ON)
      PduR_LinIfTxConfirmation(LinIf_GaaGlobalHandleId[LucFrameIdx], \
                                                                  LINIF_TRUE);
      #endif
      if (LINIF_LIN13 != LpChannelPtr->ddLinProtocol)
      {
        /* @Trace: LinIf_SUD_API_173*/
        /* Clear the response_error signal */
        LucRespErrSignal = 0x00;
        /* Update response_error signal */
        Com_SendSignal(LinIf_GaaLtChannelInfo[LddChnlIndex].ddComSigHndId, \
                                                            &LucRespErrSignal);
      }
      else
      {
        /* To Avoid QAC Warnings */
      }
      /* @Trace: LinIf_SUD_API_174*/
      /* Clear pending flag of Event Trigger Frame */
      LinIf_AssociatedPendingMask(LpFramePtr->ddLocalHandleId, LINIF_FALSE);
    }
    else
    {
      /* @Trace: LinIf_SUD_API_175*/
      LINIF_UNUSED(LucFrameIdx);
      LINIF_UNUSED(LucRespErrSignal);
      /* To Avoid QAC Warnings */
    }
  }/* No development error is occurred */
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* To Avoid QAC Warnings */
  }
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_LinErrorIndication                              **
**                                                                            **
** Service ID         : 0x7a                                                  **
**                                                                            **
** Description        : The LIN Driver will call this function to report a    **
**                      successfully transmitted response.                    **
**                      This function is only applicable for LIN slave nodes  **
**                      (available only if the ECU has any LIN slave channel).**
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant for different Channels. Non reentrant for   **
**                                                        the same Channel.   **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_LinIf_STATUS_PROTECTION                    **
**                      SchM_Exit_LinIf_STATUS_PROTECTION                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_91007 SWS_LinIf_00855 SWS_LinIf_00866
 * SRS_BSW_00327 SRS_BSW_00385 SRS_Lin_01595
 */
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_LinErrorIndication(
                    NetworkHandleType Channel, Lin_SlaveErrorType ErrorStatus)
{
  /* @Trace: LinIf_SUD_API_176*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  uint16 LucFrameIdx;
  NetworkHandleType LddChnlIndex;
  uint8 LucRespErrSignal;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddReturnValue;
  uint8 LucIdx;
  boolean LblErrFlag;
  #endif
  Lin_StatusType LenLinStatus;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_177*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                LINIF_LINERRORINDICATION_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_178*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                    LINIF_LINERRORINDICATION_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_181*/
    /* Set Channel Status as LIN_OPERATIONAL */
    LenLinStatus = LIN_OPERATIONAL;
    /* Get Channel Index */
    LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    /* Get Channel Pointer Variable */
    LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
    /* Get Channel Ram Data Variable of current Channel */
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* Set Delay Counter as Bus Idle Timeout value */
    LpChannelRamData->usDelayCounter = LpChannelPtr->usBusIdleTimeout;
    /* Get the scheduler entry index */
    LucFrameIdx = LinIf_GetFrameIndex(Channel, LpChannelRamData->ucActivePid);
    switch (ErrorStatus)
    {
      case LIN_ERR_RESP_STOPBIT:
      {
        /* @Trace: LinIf_SUD_API_182*/
        /* Enter protection area */
        SchM_Enter_LinIf_STATUS_PROTECTION();
        if (LINIF_TRUE == LpChannelRamData->blTxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_183*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_TX_ERROR */
          LenLinStatus = LIN_TX_ERROR;
        }
        else
        if (LINIF_TRUE == LpChannelRamData->blRxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_184*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_RX_ERROR */
          LenLinStatus = LIN_RX_ERROR;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_185*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
        }
        /* @Trace: LinIf_SUD_API_186*/
        break;
      }
      case LIN_ERR_RESP_CHKSUM:
        /* Enter protection area */
        /* @Trace: LinIf_SUD_API_187*/
        SchM_Enter_LinIf_STATUS_PROTECTION();
        if (LINIF_TRUE == LpChannelRamData->blTxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_188*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_TX_ERROR */
          LenLinStatus = LIN_TX_ERROR;
        }
        else
        if (LINIF_TRUE == LpChannelRamData->blRxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_189*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_RX_ERROR */
          LenLinStatus = LIN_RX_ERROR;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_190*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
        }
        /* @Trace: LinIf_SUD_API_191*/
        break;
      case LIN_ERR_INC_RESP:
      {
        /* @Trace: LinIf_SUD_API_192*/
        /* Enter protection area */
        SchM_Enter_LinIf_STATUS_PROTECTION();
        if (LINIF_TRUE == LpChannelRamData->blTxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_193*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_RX_ERROR */
          LenLinStatus = LIN_RX_ERROR;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_194*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
        }
        /* @Trace: LinIf_SUD_API_195*/
        break;
      }
      case LIN_ERR_NO_RESP:
      {
        /* @Trace: LinIf_SUD_API_196*/
        /* Enter protection area */
        SchM_Enter_LinIf_STATUS_PROTECTION();
        if (LINIF_TRUE == LpChannelRamData->blRxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_197*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_RX_NO_RESPONSE */
          LenLinStatus = LIN_RX_NO_RESPONSE;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_198*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
        }
        /* @Trace: LinIf_SUD_API_199*/
        break;
      }
      case LIN_ERR_RESP_DATABIT:
      {
        /* @Trace: LinIf_SUD_API_200*/
        /* Enter protection area */
        SchM_Enter_LinIf_STATUS_PROTECTION();
        if (LINIF_TRUE == LpChannelRamData->blTxRequestPending)
        {
          /* @Trace: LinIf_SUD_API_201*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* LIN_TX_ERROR */
          LenLinStatus = LIN_TX_ERROR;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_202*/
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
        }
        /* @Trace: LinIf_SUD_API_203*/
        break;
      }
      case LIN_ERR_HEADER:
      default:
      {
        /* @Trace: LinIf_SUD_API_204*/
        break;
      }
    }
    if(LenLinStatus == LIN_TX_ERROR)
    {
      /* @Trace: LinIf_SUD_API_205*/
      /* Invoke the upper layer confirmation callback */
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaTxConfirmationFun[LucFrameIdx])\
                            (LinIf_GaaGlobalHandleId[LucFrameIdx], E_NOT_OK);
      #elif(LINIF_TX_LPDU == STD_ON)
      PduR_LinIfTxConfirmation(LinIf_GaaGlobalHandleId[LucFrameIdx], E_NOT_OK);
      #endif
      #if (LINIF_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                              LINIF_LINERRORINDICATION_SID, LINIF_E_RESPONSE);
      #endif
    }
    else if((LIN_RX_ERROR == LenLinStatus) || (LIN_RX_NO_RESPONSE == LenLinStatus))
    {
      /* @Trace: LinIf_SUD_API_206*/
      #if (LINIF_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                              LINIF_LINERRORINDICATION_SID, LINIF_E_RESPONSE);
      #endif
    }
    else
    {
      /* To avoid QAC error */
    }
    if((LIN_RX_ERROR == LenLinStatus) || (LIN_TX_ERROR == LenLinStatus))
    {
      if (LINIF_LIN13 != LpChannelPtr->ddLinProtocol)
      {
        /* @Trace: LinIf_SUD_API_207*/
        /* Clear the response_error signal */
        LucRespErrSignal = 0x01;
        /* Update response_error signal */
        Com_SendSignal(LinIf_GaaLtChannelInfo[LddChnlIndex].ddComSigHndId, \
                                                            &LucRespErrSignal);
      }
      else
      {
        /* To avoid QAC error */
      }
    }
    else
    {
      /* To avoid QAC error */
    }
  }/* No development error is occurred */
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* To Avoid QAC Warnings */
  }
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if(LINIF_SLAVE_SUPPORT == STD_ON)*/
/*******************************************************************************
** Function Name      : LinIf_WakeupConfirmation                              **
**                                                                            **
** Service ID         : 0x61                                                  **
**                                                                            **
** Description        : The LIN Driver or LIN Transceiver Driver will call    **
**                      this function to report the wake up source after      **
**                      the successful wakeup detection during CheckWakeup    **
**                      or after power on by bus.                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : WakeupSource                                          **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_LinIf_STATUS_PROTECTION                    **
**                      SchM_Exit_LinIf_STATUS_PROTECTION                     **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
*******************************************************************************/
/* @Trace: SWS_LinIf_00715 SWS_LinIf_00716 SWS_LinIf_00717 SWS_LinIf_00718
 * SRS_BSW_00327
 */
#if (LINIF_WAKEUP_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_WakeupConfirmation(
                                          EcuM_WakeupSourceType WakeupSource)
{
  /* @Trace: LinIf_SUD_API_208*/
  #if (LINIF_NO_OF_WAKEUP_SOURCES >= LINIF_ONE_CHECK)
  P2CONST(LinIf_WakeupSource, AUTOMATIC, LINIF_APPL_CONST) LpWkpSource;
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  EcuM_WakeupSourceType LddWakeupEvent;
  #else
  LINIF_UNUSED(WakeupSource);
  #endif

  /* Change Number to Macro*/
  #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
  uint8_least LucNoOfWakeupSources;
  #endif
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddReturnValue;
  /* Initialize LddReturnValue with E_OK */
  LddReturnValue = E_OK;
  #endif

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_209*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINIF_CHECKWAKEUP_SID, LINIF_E_UNINIT);
    /* Set the DET error flag */
    LddReturnValue = E_NOT_OK;
  }

  /* Check for any development error */
  if (E_OK == LddReturnValue)
  #endif /*  (STD_ON == LINIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: LinIf_SUD_API_210*/
    #if (LINIF_NO_OF_WAKEUP_SOURCES >= LINIF_ONE_CHECK)
    /* Get the pointer to the wakeup structure */
    LpWkpSource = &LinIf_GaaWakeupSource[LINIF_ZERO];

    /* Change Number to Macro*/
    #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
    /* Get the number of wakeup sources into the local variable */
    LucNoOfWakeupSources = (uint8_least)LINIF_NO_OF_WAKEUP_SOURCES;
    do
    {
    #endif
    /* @Trace: LinIf_SUD_API_211*/
      /* Get the wakeup event and store it in a local variable */
      LddWakeupEvent = LpWkpSource->ddWakeupEvent;
      /* Check whether the wakeup event is matched or not */
      if (LddWakeupEvent != WakeupSource)
      {
        /* @Trace: LinIf_SUD_API_212*/
        #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
        /* Decrement the number of wakeup sources */
        LucNoOfWakeupSources--;
        /* Increment wakeup source pointer by one */
        LpWkpSource++;
        #endif
      }
      else
      {
        /* @Trace: LinIf_SUD_API_213*/
        /* Get the channel pointer */
        LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor
          [LinIf_GaaComMChannelMap[LpWkpSource->ucChannelId]];

        /* Change Number to Macro*/
        #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
        /* Set the wakeup flag to true */
        LucNoOfWakeupSources = (uint8_least)LINIF_ZERO;
        #endif
        /* Change the sleep request to not requested */
        SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        LpChannelPtr->pChannelRamData->ucSleepRequested = LINIF_ZERO;
        SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        /* Set wakeup flag */
        LpChannelPtr->pChannelRamData->blWakeupStatus = LINIF_TRUE;
      }

    /* Change Number to Macro*/
    #if (LINIF_NO_OF_WAKEUP_SOURCES > LINIF_ONE_CHECK)
    }while(LINIF_ZERO != LucNoOfWakeupSources);
    #endif
    #endif
  }/*after passing DET Checks */
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* @Trace: LinIf_SUD_API_214*/
    /* Report to DET, if Wakeup sourceId is invalid */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
    	LINIF_WAKEUPCONFIRMATION_SID, LINIF_E_PARAM_WAKEUPSOURCE);
  }
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinIf_SetPIDTable                                     **
**                                                                            **
** Service ID         : 0x61                                                  **
**                                                                            **
** Description        : Set all assigned PID values.                          **
**                      The order is congruent to the LIN frame index.        **
**                      Only applicable for LIN slave nodes.                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : Channel, PidBuffer, PidBufferLength                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : None                                                  **
*******************************************************************************/
/* @Trace: SWS_LinIf_91003 SWS_LinIf_00823 SWS_LinIf_00824 SWS_LinIf_00825
 * SWS_LinIf_00826 SWS_LinIf_00827 SWS_LinIf_00860
 * SRS_BSW_00327
 */
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_SetPIDTable(
NetworkHandleType Channel, Lin_FramePidType* PidBuffer, uint8 PidBufferLength)
{
  /* @Trace: LinIf_SUD_API_215*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  uint8 LucLenOfPidTable;
  uint8 LucCountIdx;
  uint8 LddChnlIndex;
  Std_ReturnType LddReturnValue;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIdx;
  boolean LblErrFlag;
  LblErrFlag = LINIF_TRUE;
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */

  /* Get Channel Index */
  LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
  /* Get Channel Pointer Variable */
  LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
  /* Get the pointer to Frame RAM data */
  LpFrameRamData = LpChannelPtr->pFrameRamData;
  /* get Length of Pid Table */
  LucLenOfPidTable = LpChannelPtr->ucLenOfPidTable;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = E_OK;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_216*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                LINIF_SETPIDTABLE_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE ==  LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_217*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                    LINIF_SETPIDTABLE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Check If PidBuffer is NULL_PTR */
      if(NULL_PTR == PidBuffer)
      {
        /* @Trace: LinIf_SUD_API_219*/
        /* Report to DET */
        (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                          LINIF_SETPIDTABLE_SID, LINIF_E_PARAM_POINTER);
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* To Avoid QAC Warnings */
      }
      /* Check If PidBufferLength is smaller than the number
                                                     of the configured PIDs */
      if(PidBufferLength < LucLenOfPidTable)
      {
        /* @Trace: LinIf_SUD_API_220*/
        /* Report to DET */
        (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                          LINIF_SETPIDTABLE_SID, LINIF_E_PARAMETER);
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* To Avoid QAC Warnings */
      }
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_221*/
    /* @Trace: LinIf_SUD_API_222*/
    for (LucCountIdx = 0; LucCountIdx < LucLenOfPidTable; LucCountIdx++)
    {
      /* @Trace: LinIf_SUD_API_223*/
      LpFrameRamData->pPidTable[LucCountIdx] = PidBuffer[LucCountIdx];
    }
  }
  /* @Trace: LinIf_SUD_API_224*/
  return LddReturnValue;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name      : LinIf_GetPIDTable                                     **
**                                                                            **
** Service ID         : 0x61                                                  **
**                                                                            **
** Description        : Retrieves all assigned PID values.                    **
**                      The order is congruent to the LIN frame index.        **
**                      Only applicable for LIN slave nodes.                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : Channel, PidBuffer, PidBufferLength                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : None                                                  **
*******************************************************************************/
/* @Trace: SWS_LinIf_91002 SWS_LinIf_00816 SWS_LinIf_00817 SWS_LinIf_00828
 * SWS_LinIf_00818 SWS_LinIf_00819 SWS_LinIf_00820 SWS_LinIf_00821
 * SWS_LinIf_00859
 * SRS_BSW_00327
 */
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinIf_GetPIDTable(
NetworkHandleType Channel, Lin_FramePidType* PidBuffer, uint8* PidBufferLength)
{
  /* @Trace: LinIf_SUD_API_225*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  uint8 LucLenOfPidTable;
  uint8 LucCountIdx;
  uint8 LddChnlIndex;
  Std_ReturnType LddReturnValue;
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIdx;
  boolean LblErrFlag;
  #endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */

  /* Get Channel Index */
  LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
  /* Get Channel Pointer Variable */
  LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
  /* Get the pointer to Frame RAM data */
  LpFrameRamData = LpChannelPtr->pFrameRamData;
  /* get Length of Pid Table */
  LucLenOfPidTable = LpChannelPtr->ucLenOfPidTable;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_226*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                LINIF_SETPIDTABLE_SID, LINIF_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*check if Network handle is valid*/
    for(LucIdx = LINIF_ZERO; LucIdx < LINIF_IF_CHANNELS; LucIdx++)
    {
      if(Channel == LinIf_GaaComMChannel[LucIdx])
      {
        LblErrFlag = LINIF_FALSE;
        break;
      }
      else
      {
        /* Do nothing */
      }
    }
    if(LINIF_TRUE == LblErrFlag)
    {
      /* @Trace: LinIf_SUD_API_227*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                    LINIF_SETPIDTABLE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Check If PidBuffer is NULL_PTR */
      if(NULL_PTR == PidBuffer)
      {
        /* @Trace: LinIf_SUD_API_229*/
        /* Report to DET */
        (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                          LINIF_SETPIDTABLE_SID, LINIF_E_PARAM_POINTER);
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* To Avoid QAC Warnings */
      }
      /* Check If PidBufferLength is NULL_PTR */
      if(NULL_PTR == PidBufferLength)
      {
        /* @Trace: LinIf_SUD_API_230*/
        /* Report to DET */
        (void)Det_ReportError (LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                          LINIF_SETPIDTABLE_SID, LINIF_E_PARAM_POINTER);
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* To Avoid QAC Warnings */
      }
    }
  }
  /* Check if no development error is occurred */
  if(E_OK == LddReturnValue)
  #endif
  {
    /* @Trace: LinIf_SUD_API_231*/
    *PidBufferLength = LucLenOfPidTable;
    /* @Trace: LinIf_SUD_API_232*/
    /* @Trace: LinIf_SUD_API_233*/
    for (LucCountIdx = 0; LucCountIdx < LucLenOfPidTable; LucCountIdx++)
    {
      /* @Trace: LinIf_SUD_API_234*/
      PidBuffer[LucCountIdx] = LpFrameRamData->pPidTable[LucCountIdx];
    }
  }
  /* @Trace: LinIf_SUD_API_235*/
  return LddReturnValue;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_MainFunction                                    **
**                                                                            **
** Service ID         : 0x80                                                  **
**                                                                            **
** Description        : This function is the main processing function in the  **
**                      LIN Interface. It will be invoked periodically.       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : Channel                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinIf_GpFirstChannel,               **
**                      LinIf_GpFirstTpChannelRam,                            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(),                                    **
**                      SchM_Enter_LinIf_WAKEUP_CONFCOUNT_PROTECTION          **
**                      SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION            **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
**                      SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION           **
**                      SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION             **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
**                      LinTp_RequestNewRxBuff(),                             **
**                      LinTp_CopyDataTxBuff(), LinIf_SleepReqMainFunction(), **
**                      LinIf_ChangeSchedule(), LinIf_ProcessPrevStatus(),    **
**                      LinIf_ChangeToNullSchedule(),                         **
**                      Lin_SendHeader(), Lin_SendResponse(),                 **
**                      LinSM_WakeupConfirmation(),                           **
**                      Cdd_WakeupConfirmation()                              **
*******************************************************************************/
/* @Trace: SWS_LinIf_00384 SWS_LinIf_00725 SWS_LinIf_00726 SWS_LinIf_00473
 * SWS_LinIf_00286 SWS_LinIf_00287
 * SRS_BSW_00373 SRS_Lin_01546 SRS_Lin_01555 SRS_Lin_01561 SRS_BSW_00327
 */
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_MainFunction(NetworkHandleType Channel)
{
  /* @Trace: LinIf_SUD_API_236*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;

  /* Get the channel pointer */
  LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[Channel];
  /* Get the channel Ram Data pointer */
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  if (LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
  {
    /* Process main function for Master node*/
    LinIf_MainFunctionMaster(Channel, LpChannelRamData, LpChannelPtr);
  }
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
  else
  #endif /* #if (LINIF_MASTER_SUPPORT == STD_ON) */
  {
    #if (LINIF_SLAVE_SUPPORT == STD_ON)
    if(LINIF_CHANNEL_OPERATIONAL == LpChannelRamData->ucChannelSts)
    {
      if (LINIF_ZERO == LpChannelRamData->usDelayCounter)
      {
        /* @Trace: LinIf_SUD_API_255*/
        LinIf_SleepReqMainFunction(LpChannelPtr, Channel);
      }
      else
      {
        /* @Trace: LinIf_SUD_API_256*/
        LpChannelRamData->usDelayCounter--;
      }
      
      /* Reset */
    }
    else
    {
      /* @Trace: LinIf_SUD_API_257*/
      LpChannelRamData->usDelayCounter = LpChannelPtr->usBusIdleTimeout;
    }

    /* Check wake-up signal sent */
    if(E_OK == LpChannelRamData->ucWakeupSignalSent)
    {
      /* Check block wake-up completed or not (wake-up signal counter = 3) */
      if(LINIF_THREE <= LpChannelRamData->ucNumberWakeupSignalSent)
      {
        /* Check timeout between each block wake-up signal */
        if(LINIF_ZERO == LpChannelRamData->ulCounterDelayBlockWakeup)
        {
          /* @Trace: LinIf_SUD_API_523 */
          /* Increase number of block wake-up signal */
          LpChannelRamData->ucNumberBlockWakeup++;
          /* Reset counter of number wake-up signal sent */
          LpChannelRamData->ucNumberWakeupSignalSent = LINIF_ZERO;

          /* If the number of block wakes is less than the configured number or the configuration is infinity, send a wake-up signal */
          if((LINIF_BLOCK_WAKEUP_REPETITION_INFINITY == LINIF_BLOCK_WAKEUP_REPETITION_MAX) || (LINIF_BLOCK_WAKEUP_REPETITION_MAX > LpChannelRamData->ucNumberBlockWakeup))
          {
            /* @Trace: LinIf_SUD_API_524 */
            /* Increase counter */
            LpChannelRamData->ucNumberWakeupSignalSent++;
            /* Reset timeout timer */
            LpChannelRamData->ulCounterDelayWakeupSignalSent = LpChannelPtr->ulCounterDelayWakeupSignalSent;
            LpChannelRamData->ulCounterDelayBlockWakeup = LpChannelPtr->ulCounterDelayBlockWakeup;

            /* Put internal go to sleep and send wake-up signal */
            #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
            LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[Channel].ucDriverIndex].pLinGoToSleepInternal(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
            LpChannelRamData->ucWakeupSignalSent = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[Channel].ucDriverIndex].pLinWakeup(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
            #else
            (void) Lin_GoToSleepInternal(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
            LpChannelRamData->ucWakeupSignalSent = Lin_Wakeup(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
              #endif
          }
          else
          {
            /* @Trace: LinIf_SUD_API_525 */
            /* If the number of block wake-ups is greater than the configured number, clear the flag to stop sending the wake-up signal */
            LpChannelRamData->ucWakeupSignalSent = E_NOT_OK;
            /* Reset flag number block wake-up flag */
            LpChannelRamData->ucNumberBlockWakeup = LINIF_ZERO;
            LpChannelRamData->ucNumberWakeupSignalSent = LINIF_ZERO;
            LpChannelRamData->ulCounterDelayBlockWakeup = LpChannelPtr->ulCounterDelayBlockWakeup;
            /* Invoke Wakeup confirmation for Upper Layer */
            #if (LINIF_CDD_SUPPORT == STD_ON)
            (LinIf_GaaWakeupConfFun [Channel])
              (LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId, LINIF_FALSE);
            #else
            LinSM_WakeupConfirmation(
              LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId, LINIF_FALSE);
            #endif
          }
        }
        else
        {
          /* Decrease timer */
          LpChannelRamData->ulCounterDelayBlockWakeup--;
        }
      }
      else
      {
        /* Check the timeout between each wake-up signal */
        if(LINIF_ZERO == LpChannelRamData->ulCounterDelayWakeupSignalSent)
        {
          /* @Trace: LinIf_SUD_API_522 */
          /* Increase counter */
          LpChannelRamData->ucNumberWakeupSignalSent++;
          /* Set delay counter for next wake-up signal */
          LpChannelRamData->ulCounterDelayWakeupSignalSent = LpChannelPtr->ulCounterDelayWakeupSignalSent;

          /* Put internal go to sleep and send wake-up signal */
          #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
          LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[Channel].ucDriverIndex].pLinGoToSleepInternal(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
          LpChannelRamData->ucWakeupSignalSent = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[Channel].ucDriverIndex].pLinWakeup(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
          #else
          (void) Lin_GoToSleepInternal(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
          LpChannelRamData->ucWakeupSignalSent = Lin_Wakeup(LinIf_GaaLtChannelInfo[Channel].ucDrvChannelId);
          #endif
        }
        else
        {
          /* Decrease timer */
          LpChannelRamData->ulCounterDelayWakeupSignalSent--;
        }

      }
    }
    else
    {
      /* @Trace: LinIf_SUD_API_521 */
      /* Reset number block wake-up flag */
      LpChannelRamData->ucNumberBlockWakeup = LINIF_ZERO;
      LpChannelRamData->ucNumberWakeupSignalSent = LINIF_ZERO;
    }
    #endif /*#if (LINIF_SLAVE_SUPPORT == STD_ON)*/
  }
  /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
