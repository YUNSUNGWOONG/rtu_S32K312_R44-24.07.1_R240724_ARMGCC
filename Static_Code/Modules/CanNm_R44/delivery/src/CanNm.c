/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Module                         **
**                                                                            **
**  PURPOSE   : This file provides definitions of following Nm APIs:          **
**              CanNm_Init                                                    **
**              CanNm_DeInit                                                  **
**              CanNm_PassiveStartUp                                          **
**              CanNm_NetworkRequest                                          **
**              CanNm_NetworkRelease                                          **
**              CanNm_DisableCommunication                                    **
**              CanNm_EnableCommunication                                     **
**              CanNm_SetUserData                                             **
**              CanNm_GetUserData                                             **
**              CanNm_Transmit                                                **
**              CanNm_GetNodeIdentifier                                       **
**              CanNm_GetLocalNodeIdentifier                                  **
**              CanNm_RepeatMessageRequest                                    **
**              CanNm_GetPduData                                              **
**              CanNm_GetState                                                **
**              CanNm_GetVersionInfo                                          **
**              CanNm_RequestBusSynchronization                               **
**              CanNm_CheckRemoteSleepIndication                              **
**              CanNm_SetSleepReadyBit                                        **
**              CanNm_MainFunction                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By            Description                         **
** 1.2.0_HF1  08-Mar-2024   JH Yang       CP44 #3008                          **
** 1.2.0      22-Feb-2024   JH Kim        CP44 #3894                          **
** 1.1.6      16-Jun-2023   HieuTM8       #CP44-2100                          **
** 1.1.5      28-Apr-2023   NamNT1        CP44 #1731                          **
** 1.1.4      31-Jan-2023   NamNT1        CP44 #1151, #1098, #873, #1471      **
** 1.1.2      28-Oct-2022   ThuanVT       CP44 #940                           **
** 1.1.1      07-Oct-2022   NamNT1        CP44 #785, #786, #610, #838         **
**                                        #887, #842                          **
** 1.1.0      20-Jul-2022   SMKwon        R44-Redmine #28017, #29362, #29697  **
** 1.0.2.1    20-Jun-2022   SM Kwon       CP44-120                            **
** 1.0.2      29-Apr-2022   ThuanVT       R44-Redmine #25510, #25678          **
** 1.0.1      15-Mar-2022   TuanNLH       R44-Redmine #17009, #17463          **
** 1.0.0      04-Dec-2020   SHKim         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CANM_SUD_FILE_001 */
#include "CanNm.h"                /* CanNm API Header File */
#include "CanNm_IntFunc.h"        /* CanNm Internal Functions header file */

#include "Det.h"                  /* Det Header File */

#include "Nm.h"                   /* NM Header File */

#include "SchM_CanNm.h"           /* Schedule Manager header file */

#include "PduR_CanNm.h"           /* PduR Header File */

#include "CanIf.h"                /* CanIf Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANNM_C_AR_RELEASE_MAJOR_VERSION    (0x04u)
#define CANNM_C_AR_RELEASE_MINOR_VERSION    (0x04u)
#define CANNM_C_AR_RELEASE_REVISION_VERSION (0x00u)

/* CanNm software version information */
#define CANNM_C_SW_MAJOR_VERSION            (0x01u)
#define CANNM_C_SW_MINOR_VERSION            (0x02u)
#define CANNM_C_SW_PATCH_VERSION            (0x00u)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (CANNM_AR_RELEASE_MAJOR_VERSION != CANNM_C_AR_RELEASE_MAJOR_VERSION)
#error "CanNm.c : Mismatch in Specification Major Version"
#endif

#if (CANNM_AR_RELEASE_MINOR_VERSION != CANNM_C_AR_RELEASE_MINOR_VERSION)
#error "CanNm.c : Mismatch in Specification Minor Version"
#endif

#if (CANNM_AR_RELEASE_REVISION_VERSION != CANNM_C_AR_RELEASE_REVISION_VERSION)
#error "CanNm.c : Mismatch in Specification Revision Version"
#endif

#if (CANNM_SW_MAJOR_VERSION != CANNM_C_SW_MAJOR_VERSION)
#error "CanNm.c : Mismatch in Software Major Version"
#endif

#if (CANNM_SW_MINOR_VERSION != CANNM_C_SW_MINOR_VERSION)
#error "CanNm.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if (CANNM_NMS_POSITION_ENABLED == STD_ON)
static FUNC(void, CANNM_CODE) CanNm_IntProcessNmState(uint32 CanNmChannelIndex, CanNm_ModeState previousMode, CanNm_ModeState currentMode);
#endif

#define CANNM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanNm_Init                                          **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Performs complete initialization of the CANNM       **
**                        Module.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : cannmConfigPtr                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        CanNm_ArrayStaticChannel                            **
**                        CanNm_ArrayChannel                                  **
**                        CanNm_ArrayPnEIRAPdu                                **
**                        CanNm_ArrayPnEIRATimer                              **
**                        CanNm_InitStatus                                    **
**                        CanNm_ChannelsDataPtr                               **
**                        CanNm_PnFilterMaskBytesPtr                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_Memset                                        **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_Nm_02517 SRS_Nm_02527 SRS_BSW_00358 SRS_BSW_00101 SRS_BSW_00414 SRS_ES95480_03E_SWP_00128 */
FUNC(void, CANNM_CODE) CanNm_Init(
  P2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_APPL_CONST) cannmConfigPtr)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;

  uint32 canNmChannelIndex;
  
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  /* Check whether the configset is null */
  if (NULL_PTR == cannmConfigPtr)
  {
    /* @Trace: CanNm_SUD_API_001 */
    (void)Det_ReportRuntimeError(CANNM_MODULE_ID, CANNM_INSTANCE_ID,
      CANNM_INIT_SID, CANNM_E_INIT_FAILED);
  }
  else
  #endif /* (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
  {
    /* @Trace: CanNm_SUD_API_002 */
    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    CanNm_ChannelsDataPtr = &cannmConfigPtr->channelsConfigPtr[CANNM_ZERO];
    CanNm_PnFilterMaskBytesPtr = &cannmConfigPtr->pnFilterMaskBytePtr[CANNM_ZERO];
    CanNm_RxPduId = &cannmConfigPtr->rxPduIdPtr[CANNM_ZERO];
    CanNm_NumberOfRxPdu = cannmConfigPtr->numberOfRxPdu;
    #else
	/* polyspace +1 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
    CANNM_UNUSED_PTR(cannmConfigPtr);
    #endif /* (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  
    for (canNmChannelIndex = CANNM_ZERO; canNmChannelIndex < CANNM_NUMBER_OF_CHANNEL; canNmChannelIndex++)
    {
      /* @Trace: CanNm_SUD_API_003 */
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

      #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
      ptrChannel->remoteSleepIndTime = CANNM_ZERO;
      #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
      ptrChannel->waitBusSleepTime = CANNM_ZERO;
      ptrChannel->repeatMessageTime = CANNM_ZERO;
      ptrChannel->ntwkTimeOutTime = CANNM_ZERO;
      ptrChannel->msgCycleTime = CANNM_ZERO;

      /* CanNm shall not perform transmission error handling */
      #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
      #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
      ptrChannel->msgTimeOutTime = CANNM_ZERO;
      #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
      #endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */
      
      CanNm_Memset(&ptrChannel->rxUserData[CANNM_BYTE0], CANNM_ZERO, CANNM_MAX_PDU_SIZE);
      CanNm_Memset(&ptrChannel->txUserData[CANNM_BYTE0], CANNM_ZERO, ptrStaticChannel->userDataPosition);
      CanNm_Memset(&ptrChannel->txUserData[ptrStaticChannel->userDataPosition], ptrStaticChannel->userDataInitValue, ptrStaticChannel->userDataLength);
      #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
      CanNm_InitERA(canNmChannelIndex);
      #endif
      /* @Trace: CanNm_SUD_API_007 */
      /* Change the mode status to Bus sleep mode */
      ptrChannel->modeStatus = CANNM_BUS_SLEEP_MODE;
      ptrChannel->nextModeState = CANNM_BUS_SLEEP_MODE;
      ptrChannel->noOfImmediateNmTx = CANNM_ZERO;
      #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
      ptrChannel->remoteSlpDetect = CANNM_FALSE;
      #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if (ptrStaticChannel->nodeDetectionEnabled == CANNM_TRUE)
      {
      /* @Trace: CanNm_SUD_API_008 */
        /* Update the NodeId for the Channel */
        #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
        ptrChannel->txUserData[ptrStaticChannel->pduNidPosition] 
                                                  = ptrPostBuildChannel->nodeId;
        #else
        ptrChannel->txUserData[ptrStaticChannel->pduNidPosition] 
                                                     = ptrStaticChannel->nodeId;
        #endif /*#if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      }
      else
      {
        /* Do nothing */
      }

      /* Check and set internal value if PNC feature have been turn on */
      #if(CANNM_GLOBAL_PN_SUPPORT == STD_ON)
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if(ptrPostBuildChannel->pnEnabled == CANNM_TRUE)
      #else
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */      
      if(ptrStaticChannel->pnEnabled == CANNM_TRUE)
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      {
        /* @Trace: CanNm_SUD_API_009 */
        #if (CANNM_FORCEPNAVAILABILITYCONFENABLED_PRESENT == STD_ON)
        ptrChannel->pnStatusBit = ptrStaticChannel->forcePnAvailabilityConfEnabled;
        /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
        if (ptrChannel->pnStatusBit == CANNM_TRUE)
        {
          #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
          #if (CANNM_CBV_POS_OFF_PRESENT == STD_ON)
          /* Check and set PNI bit in CBV if PNC feature have been turn on */
          if(CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition)
          #endif
          {
            #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
            if (ptrPostBuildChannel->pnEnabled == CANNM_TRUE)
            {
              /* Update the CBV for the Channel to enable PN */
              /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
              ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
              = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                        | CANNM_PNI_BIT;
            }
            else
            {
              /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
              ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                        & ~(CANNM_PNI_BIT);
            }
            #else
            #if (CANNM_PN_DISABLED_PRESENT == STD_ON)
            if(ptrStaticChannel->pnEnabled == CANNM_TRUE)
            #endif
            {
              /* Update the CBV for the Channel to enable PN */
              /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
              ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
              = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                        | CANNM_PNI_BIT;
            }
            #if (CANNM_PN_DISABLED_PRESENT == STD_ON)
            else
            {
              /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
              ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                        & ~(CANNM_PNI_BIT);
            }
            #endif
            #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
          }
          #if (CANNM_CBV_POS_OFF_PRESENT == STD_ON)
          else
          {
            /* Do nothing */
          }
          #endif
          #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
        }
        #else
        /* @Trace: CanNm_SUD_API_009 */
        ptrChannel->pnStatusBit = CANNM_FALSE;
        #endif /* #if (CANNM_FORCEPNAVAILABILITYCONFENABLED_PRESENT == STD_ON) */
      }
      #endif /* #if(CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

      /* @Trace: CanNm_SUD_API_010 */
      ptrChannel->networkRequested = CANNM_FALSE;
      ptrChannel->communicationEnabled = CANNM_TRUE;
      ptrChannel->txNmCoordinatorSleepReadyBit = CANNM_FALSE;
      ptrChannel->busLoadReductionEnabled = CANNM_FALSE;
      ptrChannel->nmCoordReadyToSleepIndicationCalled = CANNM_FALSE;
      ptrChannel->transmissionRequestFailed = CANNM_FALSE;
      ptrChannel->txActiveWakeUpBit = CANNM_FALSE;

      #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
      ptrChannel->carWakeUpBit = CANNM_FALSE;
      #endif  /* #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */
      #if(CANNM_NMS_POSITION_ENABLED == STD_ON)
      ptrChannel->nmState = NM_STATE_UNDEFINED;
      #endif
      #if (CANNM_REASON_POSITION_ENABLED == STD_ON)
      ptrChannel->nwRequestReason = 0x00u;
      #endif
    }
    #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
    CanNm_InitEIRA();
    #endif

    /*Set the global init status to true*/
    CanNm_InitStatus = CANNM_TRUE;
  }  
}

/*******************************************************************************
** Function Name        : CanNm_DeInit                                        **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : Performs complete de-initialization of the CANNM    **
**                        Module.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        CanNm_InitStatus                                    **
**                        CanNm_ArrayChannel                                  **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00336 SRS_BSW_00369 */
FUNC(void, CANNM_CODE) CanNm_DeInit(void)
{
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  uint32 canNmChannelIndex;
  boolean notInBusSleep = CANNM_FALSE;

  if (CanNm_InitStatus != CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_014 */
    (void)Det_ReportError(CANNM_MODULE_ID,
                          CANNM_INSTANCE_ID,
                          CANNM_DEINIT_SID,
                          CANNM_E_UNINIT); 
  }
  else
  {
    SchM_Enter_CanNm_INTERNAL_STATUS();

    for (canNmChannelIndex = CANNM_ZERO; (CANNM_TRUE != notInBusSleep) && (canNmChannelIndex < CANNM_NUMBER_OF_CHANNEL); canNmChannelIndex++)
    {
      /* @Trace: CanNm_SUD_API_015 */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      
      if (ptrChannel->modeStatus != CANNM_BUS_SLEEP_MODE)
      {
        /* @Trace: CanNm_SUD_API_016 */
        notInBusSleep = CANNM_TRUE;
      }
      else
      {
        /* Do nothing */
      }
    }
    SchM_Exit_CanNm_INTERNAL_STATUS();

    if (notInBusSleep == CANNM_TRUE)
    {
      /* @Trace: CanNm_SUD_API_017 */
      (void)Det_ReportError(CANNM_MODULE_ID,
                            CANNM_INSTANCE_ID,
                            CANNM_DEINIT_SID,
                            CANNM_E_NOT_IN_BUS_SLEEP);
    }
    else
  #else
  {
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* @Trace: CanNm_SUD_API_018 */
      SchM_Enter_CanNm_INTERNAL_STATUS();
      CanNm_InitStatus = CANNM_FALSE;
      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }
}

/*******************************************************************************
** Function Name        : CanNm_PassiveStartUp                                **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Triggers the transition from Bus-Sleep Mode to the  **
**                        Network Mode in Repeat Message State.               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
/* @Trace: SRS_Nm_02536 SRS_Nm_02511 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_PassiveStartUp(
  VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_021 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_PASSIVE_STARTUP_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_022 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_PASSIVE_STARTUP_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_023 */
      /* Get channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();
      if ((ptrChannel->modeStatus != CANNM_BUS_SLEEP_MODE) &&
             (ptrChannel->modeStatus != CANNM_PREPAREBUS_SLEEP_MODE))
      {
        /* return E_NOT_OK */
      }
      else
      {
        /* @Trace: CanNm_SUD_API_024 */
        ptrChannel->nextModeState = CANNM_REPEAT_MESSAGE_STATE;

        returnValue = E_OK;
      }
      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }
  
  return returnValue;
}


/*******************************************************************************
** Function Name        : CanNm_NetworkRequest                                **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Request the network, since ECU needs to communicate **
**                        on the bus. Network state shall be changed to       **
**                       'requested'.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same channel)             **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* @Trace: SRS_Nm_00045 SRS_Nm_00047 SRS_Nm_02513 SRS_Nm_02528 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRequest(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if ((CANNM_HANDLE_MULTI_REQUEST_PRESENT == STD_ON) || (CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON))
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_025 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_NETWORK_REQUEST_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_026 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_NETWORK_REQUEST_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_027 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      #if ((CANNM_HANDLE_MULTI_REQUEST_PRESENT == STD_ON) || (CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON))
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #endif

      SchM_Enter_CanNm_INTERNAL_STATUS();
      #if (CANNM_HANDLE_MULTI_REQUEST_PRESENT == STD_ON)
      if (ptrStaticChannel->pnHandleMultipleNetworkRequests == CANNM_TRUE)
      {
        if ((ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE) ||
            (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE) ||
            (ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE))
        {
          /* @Trace: CanNm_SUD_API_028 */
          ptrChannel->nextModeState = CANNM_REPEAT_MESSAGE_STATE;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      #endif
      {
        if ((ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE) ||
        ((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) && (ptrChannel->repeatMessageTime == CANNM_ZERO)) ||
        ((ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE) && (ptrChannel->nextModeState == CANNM_READY_SLEEP_STATE)))
        {
          /* @Trace: CanNm_SUD_API_029 */
          ptrChannel->nextModeState = CANNM_NORMAL_OPERATION_STATE;
        }
        else
        {
          /* Do nothing */
        }
      }

      if ((ptrChannel->modeStatus == CANNM_BUS_SLEEP_MODE) ||
          (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE))
      {
        /* @Trace: CanNm_SUD_API_030 */
        ptrChannel->nextModeState = CANNM_REPEAT_MESSAGE_STATE;

        #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
        #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON)
        if (ptrStaticChannel->activeWakeupBitEnabled == CANNM_TRUE)
        {
        #endif
          /* @Trace: CanNm_SUD_API_031 */
          ptrChannel->txActiveWakeUpBit = CANNM_TRUE;
        #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON)
        }
        else
        {
          /* Do nothing */
        }
        #endif
        #endif
      }
      
      /* @Trace: CanNm_SUD_API_032 */
      /* Set the network request bit */
      ptrChannel->networkRequested = CANNM_TRUE;

      SchM_Exit_CanNm_INTERNAL_STATUS();

      returnValue = E_OK;
    }
  }
  
  return returnValue;
}
#endif /* #if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */


/*******************************************************************************
** Function Name        : CanNm_NetworkRelease                                **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Release the network, since ECU does not have to     **
**                        communicate on the bus.Network state shall be       **
**                        changed to 'released'.                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same channel)             **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* @Trace: SRS_Nm_00045 SRS_Nm_00047 SRS_Nm_02513 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRelease(
  VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle)
{
  uint32 canNmChannelIndex;
  Std_ReturnType returnValue = E_NOT_OK;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;

  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_033*/
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_NETWORK_RELEASE_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_034 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_NETWORK_RELEASE_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_035 */
      /* Get channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Set the network request bit */
      ptrChannel->networkRequested = CANNM_FALSE;

      if ((ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE)||
         ((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE)  &&
         (ptrChannel->repeatMessageTime == CANNM_ZERO)) ||
         ((ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE) &&
         (ptrChannel->nextModeState == CANNM_NORMAL_OPERATION_STATE)))
      {

        /* @Trace: CanNm_SUD_API_036 */
        ptrChannel->nextModeState = CANNM_READY_SLEEP_STATE;
      }
      else
      {
      /* Do nothing */
      }
      /* @Trace: CanNm_SUD_API_037 */
      SchM_Exit_CanNm_INTERNAL_STATUS();

      returnValue = E_OK;
    }
  }
  
  return returnValue;
}
#endif /* #if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */


/*******************************************************************************
** Function Name        : CanNm_DisableCommunication                          **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : Disables the NM PDU transmission ability.           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        Nm_RemoteSleepCancellation                          **
**                        SchM_Enter_CanNm_INTERNAL_STATU                     **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
/* @Trace: SRS_Nm_02512 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication(
                      VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle)
{
  uint32 canNmChannelIndex;
  Std_ReturnType returnValue = E_NOT_OK;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_038 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_DISABLE_COMMUNICATION_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_039 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_DISABLE_COMMUNICATION_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_040 */
      #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Get channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      
      if ((ptrChannel->modeStatus != CANNM_REPEAT_MESSAGE_STATE) &&
            (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE) &&
            (ptrChannel->modeStatus != CANNM_READY_SLEEP_STATE))
      {
      /* Return E_NOT_OK */
      }
      else
      {
        /* @Trace: CanNm_SUD_API_041 */
        ptrChannel->communicationEnabled = CANNM_FALSE;

        /* Stop the Message Cycle Timer */
        ptrChannel->msgCycleTime = CANNM_ZERO;

        /* Stop the Network Timer */
        ptrChannel->ntwkTimeOutTime = CANNM_ZERO;
        
        ptrChannel->transmissionRequestFailed = CANNM_FALSE;

        #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
        /* Stop the Remote Sleep Timer */
        ptrChannel->remoteSleepIndTime = CANNM_ZERO;
        if (ptrChannel->remoteSlpDetect == CANNM_TRUE)
        {
          /* @Trace: CanNm_SUD_API_042 */
          /* Get channel configuration data */
          ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

          ptrChannel->remoteSlpDetect = CANNM_FALSE;
          Nm_RemoteSleepCancellation(ptrStaticChannel->comMChannelId);
        }
        else
        {
          /* Do nothing */
        }
        #endif /* #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
        /* @Trace: CanNm_SUD_API_043 */
        returnValue = E_OK;
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
      #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
    }
  }
  
  return returnValue;
}
#endif /* #if (CANNM_COM_CONTROL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_EnableCommunication                           **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Enables the NM PDU transmission ability.            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
/* @Trace: SRS_Nm_02512 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication(
                      VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle)
{
  volatile Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_044 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_ENABLE_COMMUNICATION_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_045 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_ENABLE_COMMUNICATION_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    { 
      /* @Trace: CanNm_SUD_API_046 */
      #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)

      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();

      if ((ptrChannel->modeStatus != CANNM_REPEAT_MESSAGE_STATE) &&
             (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE) &&
             (ptrChannel->modeStatus != CANNM_READY_SLEEP_STATE))
      {
        /* Return E_NOT_OK */
      }
      else if(ptrChannel->communicationEnabled == CANNM_TRUE)
      {
        /* Return E_NOT_OK */
      }
      else
      {
      /* @Trace: CanNm_SUD_API_047 */
        /* Start the Message Cycle Timer */
        ptrChannel->msgCycleTime = ptrStaticChannel->msgCycleTime;

        /* Start the Network Timeout */
        ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;

        #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
        /* Start the Remote Sleep Timeout */
        ptrChannel->remoteSleepIndTime = ptrStaticChannel->remoteSleepIndTime;
        #endif /* #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

        /* Enable the transmission of NM PDUS */
        ptrChannel->communicationEnabled = CANNM_TRUE;

        returnValue = E_OK;
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
      #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
    }
  }

  return returnValue;
}
#endif /* #if (CANNM_COM_CONTROL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_SetUserData                                   **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Sets user data for NM messages transmitted next on  **
**                        the bus.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle, nmUserDataPtr                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm and the CanIf itself are initialized correctly**
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        CanNm_Memcpy                                        **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if ((CANNM_USER_DATA_ENABLED == STD_ON) && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF))
#if(CANNM_COM_USERDATA_SUPPORT == STD_OFF)
/* @Trace: SRS_Nm_02503 SRS_Nm_02504 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetUserData(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
  P2CONST(uint8, AUTOMATIC, CANNM_APPL_CONST) nmUserDataPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_048 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_USERDATA_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (nmUserDataPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_049 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_USERDATA_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_050 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_USERDATA_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_051 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Copy the data in Tx Buffer */
      CanNm_Memcpy(&(ptrChannel->txUserData[ptrStaticChannel->userDataPosition]),
                   nmUserDataPtr,
                   ptrStaticChannel->userDataLength);

      SchM_Exit_CanNm_INTERNAL_STATUS();

      returnValue = E_OK;
    }
  }

  return returnValue;
}
#endif /* #if(CANNM_COM_USERDATA_SUPPORT == STD_OFF) */
#endif /* #if ((CANNM_USER_DATA_ENABLED == STD_ON) && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)) */

/*******************************************************************************
** Function Name        : CanNm_GetUserData                                   **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Gets the user data out of the most recently received**
**                        NM message.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmUserDataPtr                                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm and the CanIf itself are initialized correctly**
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        CanNm_Memcpy                                        **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if (CANNM_USER_DATA_ENABLED == STD_ON)
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetUserData(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_CONST) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
    
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_052 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_USERDATA_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (nmUserDataPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_053 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_USERDATA_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_054 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_USERDATA_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_055 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Copy the User data from Rx User Data array into nmUser data Pointer */
      CanNm_Memcpy(nmUserDataPtr,
                   &(ptrChannel->rxUserData[ptrStaticChannel->userDataPosition]),
                   ptrStaticChannel->userDataLength);

      SchM_Exit_CanNm_INTERNAL_STATUS();
      
      returnValue = E_OK;
    }
  }

  return returnValue;
}
#endif /* #if (CANNM_USER_DATA_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_Transmit                                      **
**                                                                            **
** Service ID           : 0x49                                                **
**                                                                            **
** Description          : Request Transmit Nm PDU                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant(but not for the same NM-channel)         **
**                                                                            **
** Input Parameters     : CanTxPduId, PduInfoPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromTransmitHandleId        **
**                        Det_ReportError                                     **
**                        CanNm_IntCollectTxData                              **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
**                        CanNm_IntUpdateEIRA                                 **
*******************************************************************************/
#if ((CANNM_COM_USERDATA_SUPPORT == STD_ON) || (CANNM_GLOBAL_PN_SUPPORT == STD_ON))
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_Transmit(
  PduIdType CanTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_CONST) PduInfoPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  #if ((CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT == STD_ON) ||\
    (CANNM_COM_USERDATA_SUPPORT == STD_ON))
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif

  #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_COM_USERDATA_SUPPORT == STD_ON))
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_COM_USERDATA_SUPPORT == STD_ON)) */

  #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
  PduInfoType structPduInfoType;
  #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */
  
  #if ((CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT == STD_OFF) &&\
    (CANNM_COM_USERDATA_SUPPORT == STD_OFF))
  CANNM_UNUSED_PTR(PduInfoPtr);
  #endif

  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus != CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_056 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TRANSMIT_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (PduInfoPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_057 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TRANSMIT_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (CanNm_IntGetChannelIndexFromTransmitHandleId(CanTxPduId, &canNmChannelIndex) != E_OK)
    {
      /* @Trace: CanNm_SUD_API_058 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TRANSMIT_SID, CANNM_E_INVALID_PDUID);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_059 */
      /* Get channel configuration data and channel internal data */
      #if ((CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT == STD_ON) ||\
        (CANNM_COM_USERDATA_SUPPORT == STD_ON))
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #endif
      #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_COM_USERDATA_SUPPORT == STD_ON))
      ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
      #endif /* #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_COM_USERDATA_SUPPORT == STD_ON)) */

      SchM_Enter_CanNm_INTERNAL_STATUS();
      #if (CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT == STD_ON)
      if (ptrStaticChannel->canIfTriggerTransmit == CANNM_FALSE)
      #endif
      {
        /* @Trace: CanNm_SUD_API_060 */
        #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
        /* Collecting data from upper layer */
        CanNm_IntCollectTxData(canNmChannelIndex);
        #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */
      }
      #if (CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT == STD_ON)
      else
      /* polyspace +1 RTE:UNR [Justified:Low] "canIfTriggerTransmit is CANNM_TRUE at some cases." */
      {
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "PduInfoPtr already checked before used" */
        if(PduInfoPtr->SduDataPtr != NULL_PTR)
        {
          /* @Trace: CanNm_SUD_API_061 */
          /* Copy current requested user data to NM PDU */
          CanNm_Memcpy(&(ptrChannel->txUserData[ptrStaticChannel->userDataPosition]),
                    &(PduInfoPtr->SduDataPtr[ptrStaticChannel->userDataPosition]),
                    ptrStaticChannel->userDataLength);
        }
        else
        {
          /* Do nothing */
        }
      }
      #endif

      /* Request additional transmission with current data */
      #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
      if((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) ||
          (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE))
      {
        /* @Trace: CanNm_SUD_API_062 */
        /* Init data */
        structPduInfoType.SduDataPtr = ptrChannel->txUserData;
        structPduInfoType.SduLength = ptrStaticChannel->pduLength;
        structPduInfoType.MetaDataPtr = PduInfoPtr->MetaDataPtr;

        #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
        CanNm_IntUpdateEIRA(&structPduInfoType.SduDataPtr[CANNM_BYTE0]);
        #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

        /* Request an additional transmission of the NM PDU with the current user data */
        #if(CANNM_COM_CONTROL_ENABLED == STD_ON)
        if(ptrChannel->communicationEnabled == CANNM_TRUE)
        #endif /* #if(CANNM_COM_CONTROL_ENABLED == STD_ON) */
        {
          #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
          returnValue = CanIf_Transmit(ptrPostBuildChannel->txPduId,
                                                            &structPduInfoType);
          #else
          returnValue = CanIf_Transmit(ptrStaticChannel->txPduId,
                                                            &structPduInfoType);
          #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
        }
        #if(CANNM_COM_CONTROL_ENABLED == STD_ON)
        else
        {
          /* Do nothing */
        }
        #endif /* #if(CANNM_COM_CONTROL_ENABLED == STD_ON) */
      }
      #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }

  return returnValue;
}
#endif /* #if ((CANNM_COM_USERDATA_SUPPORT == STD_ON) || (CANNM_GLOBAL_PN_SUPPORT == STD_ON)) */

/*******************************************************************************
** Function Name        : CanNm_GetNodeIdentifier                             **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Get node identifier out of the most recently        **
**                        received NM message.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmNodeIdPtr                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm and the CanIf itself are initialized correctly**
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Nm_02505 SRS_Nm_02506 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNodeIdentifier(
  VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_063 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NODEIDENTIFIER_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (nmNodeIdPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_064 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NODEIDENTIFIER_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_065 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NODEIDENTIFIER_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_066 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      /* polyspace +2 DEFECT:USELESS_IF [Justified:Low] "This defect does not impact module operation" */
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if (CANNM_PDU_OFF != ptrStaticChannel->pduNidPosition)
      {
        /* @Trace: CanNm_SUD_API_067 */
        /* Update the nmNodeIdPtr */
        /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "nmNodeIdPtr is already checked null before" */
        *nmNodeIdPtr = ptrChannel->rxUserData[ptrStaticChannel->pduNidPosition];
        returnValue = E_OK;
      }
      else
      /* polyspace +1 RTE:UNR [Justified:Low] "Else branch to follow coding rule" */
      {
        /* Do nothing */
      }
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_GetLocalNodeIdentifier                        **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Get node identifier configured for the local node.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmNodeIdPtr                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm is  initialized correctly                     **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetLocalNodeIdentifier(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #else
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_068 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_LOCALNODEIDENTIFIER_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (nmNodeIdPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_069 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_LOCALNODEIDENTIFIER_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_070 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_LOCALNODEIDENTIFIER_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */ 
    }
    else
    {
      /* @Trace: CanNm_SUD_API_071 */
      /* Get channel configuration data */
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
      #else
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

      /* Update the nmNodeIdPtr */
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "nmNodeIdPtr is already checked null before" */
      *nmNodeIdPtr = ptrPostBuildChannel->nodeId;
      #else
      /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "nmNodeIdPtr is already checked null before" */
      *nmNodeIdPtr = ptrStaticChannel->nodeId;
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      
      returnValue = E_OK;
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_RepeatMessageRequest                          **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Sets Repeat Message Request bit for NM Message      **
**                        transmitted next on the bus.                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant (But not within the same channel)         **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
/* @Trace: SRS_Nm_00153 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RepeatMessageRequest(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_072 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_REPEAT_MESSAGEREQUEST_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_073 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_REPEAT_MESSAGEREQUEST_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_074 */
      /* Get channel internal data and channel configuration data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */

      SchM_Enter_CanNm_INTERNAL_STATUS();
      if ((ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE) ||
          (ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE))
      {
        /* @Trace: CanNm_SUD_API_075 */
        ptrChannel->nextModeState = CANNM_REPEAT_MESSAGE_STATE;
        
        #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
        /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
        if ((CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition))
        {
          /* @Trace: CanNm_SUD_API_076 */
          /* Set the repeat message request bit of status bits */
          /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
            = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                    | CANNM_REPTMSG_BIT;
        }
        else
        {
          /* Do nothing */
        }
        #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
        /* @Trace: CanNm_SUD_API_077 */
        returnValue = E_OK;
      }
      else
      {
        /* Do nothing */
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }
 
  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_GetPduData                                    **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : Get the whole PDU data out of the most recently     **
**                        received NM message.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmPduDataPtr                                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm and the CanIf itself are initialized correctly**
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                        CanNm_NodeDetectionEnabled                          **
**                        CanNm_UserDataEnabled                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
**                        CanNm_Memcpy                                        **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if ((CANNM_NODE_DETECTION_ENABLED == STD_ON) || (CANNM_USER_DATA_ENABLED == STD_ON))
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetPduData(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmPduDataPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST_VAR) ptrStaticChannel;
  
  SchM_Enter_CanNm_INTERNAL_STATUS();
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_078 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_PDUDATA_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (nmPduDataPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_079 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_PDUDATA_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_080 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_PDUDATA_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_081 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
      #if ((CANNM_USER_DATA_ENABLED == STD_ON) || \
                                                (CANNM_NODE_ID_ENABLED == STD_ON))
      if(ptrChannel->carWakeUpBit == CANNM_TRUE)
      {
        /* @Trace: CanNm_SUD_API_082 */
        CanNm_Memcpy(nmPduDataPtr, ptrChannel->carWakeUpPdu, ptrStaticChannel->pduLength);

        ptrChannel->carWakeUpBit = CANNM_FALSE;
      }
      else
      #endif /* #if (CANNM_USER_DATA_ENABLED == STD_ON) */
      #endif /* #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */
      {
        /* @Trace: CanNm_SUD_API_083 */
        CanNm_Memcpy(nmPduDataPtr, ptrChannel->rxUserData, ptrStaticChannel->pduLength);
      }
      /* @Trace: CanNm_SUD_API_084 */
      returnValue = E_OK;
    }
  }
  
  SchM_Exit_CanNm_INTERNAL_STATUS();
  
  return returnValue;
} 
#endif /* #if ((CANNM_NODE_DETECTION_ENABLED == STD_ON) || (CANNM_USER_DATA_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : CanNm_GetState                                      **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Returns the current state and mode of the network   **
**                        management.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmStatePtr, nmModePtr                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
/* @Trace: SRS_Nm_00050 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetState(
  VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle,
  P2VAR(Nm_StateType, AUTOMATIC, CANNM_APPL_DATA) nmStatePtr,
  P2VAR(Nm_ModeType, AUTOMATIC, CANNM_APPL_DATA) nmModePtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_085 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_STATE_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if ((nmStatePtr == NULL_PTR) || (nmModePtr == NULL_PTR))
  {
    /* @Trace: CanNm_SUD_API_086 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_STATE_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_087 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_STATE_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_088 */
      /* Get channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Set the equivalent NM mode */
      switch (ptrChannel->modeStatus)
      {
        case CANNM_BUS_SLEEP_MODE:
          /* @Trace: CanNm_SUD_API_089 */
          /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "nmModePtr and nmStatePtr are already checked null before" */
          *nmModePtr = NM_MODE_BUS_SLEEP;
          *nmStatePtr = NM_STATE_BUS_SLEEP;
          returnValue = E_OK;
          break;
          
        case CANNM_PREPAREBUS_SLEEP_MODE:
          /* @Trace: CanNm_SUD_API_090 */
          /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "nmModePtr and nmStatePtr are already checked null before" */
          *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP;
          *nmStatePtr = NM_STATE_PREPARE_BUS_SLEEP;
          returnValue = E_OK;
          break;
          
        case CANNM_READY_SLEEP_STATE:
          /* @Trace: CanNm_SUD_API_091 */
          /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "nmModePtr and nmStatePtr are already checked null before" */
          *nmModePtr = NM_MODE_NETWORK;
          *nmStatePtr = NM_STATE_READY_SLEEP;
          returnValue = E_OK;
          break;
          
        case CANNM_NORMAL_OPERATION_STATE:
          /* @Trace: CanNm_SUD_API_092 */
          /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "nmModePtr and nmStatePtr are already checked null before" */
          *nmModePtr = NM_MODE_NETWORK;
          *nmStatePtr = NM_STATE_NORMAL_OPERATION;
          returnValue = E_OK;
          break;
          
        case CANNM_REPEAT_MESSAGE_STATE:
          /* @Trace: CanNm_SUD_API_093 */
          /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "nmModePtr and nmStatePtr are already checked null before" */
          *nmModePtr = NM_MODE_NETWORK;
          *nmStatePtr = NM_STATE_REPEAT_MESSAGE;
          returnValue = E_OK;
          break;
          
        default:
          /* Do nothing */
          break;
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0xF1                                                **
**                                                                            **
** Description          : Returns the version information of the module.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 */
FUNC(void, CANNM_CODE) CanNm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CANNM_APPL_DATA) versioninfo)
{
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  if (versioninfo == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_019 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_VERSIONINFO_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: CanNm_SUD_API_020 */
    /* Copy the vendor Id */
    /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "versioninfo is already checked null before" */
    versioninfo->vendorID = CANNM_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = CANNM_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)CANNM_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)CANNM_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)CANNM_SW_PATCH_VERSION;
  }
}

/*******************************************************************************
** Function Name        : CanNm_RequestBusSynchronization                     **
**                                                                            **
** Service ID           : 0xC0                                                **
**                                                                            **
** Description          : Request the Bus Synchronization                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant (But not within the same channel)         **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        CanNm_IntCollectTxData                              **
**                        CanNm_IntUpdateEIRA                                 **
**                        CanIf_Transmit                                      **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON))
/* @Trace: SRS_BSW_00323 SRS_Nm_02516 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynchronization(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  PduInfoType structPduInfoType;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus != CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_094 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_REQUEST_BUSSYNCHRONIZATION_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_095 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_REQUEST_BUSSYNCHRONIZATION_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_096 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();

      if ((ptrChannel->modeStatus == CANNM_BUS_SLEEP_MODE) || (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE))
      {
        /* Return E_NOT_OK */
      }
      else
      {
        #if(CANNM_COM_CONTROL_ENABLED == STD_ON)
        if(ptrChannel->communicationEnabled == CANNM_TRUE)
        #endif
        {
          /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
          if (ptrStaticChannel->canIfTriggerTransmit == CANNM_FALSE)
          {
            #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
            /* @Trace: CanNm_SUD_API_097 */
            /* Collecting data from upper layer */
            CanNm_IntCollectTxData(canNmChannelIndex);
            #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */
          }
          else
          {
            /* Do nothing */
          }

          /* Trigger transmission of a single Network Management PDU */
          if((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) ||
              (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE))
          {
            /* Init data */
            /* @Trace: CanNm_SUD_API_098 */
            structPduInfoType.SduDataPtr = ptrChannel->txUserData;
            structPduInfoType.SduLength = ptrStaticChannel->pduLength;
            structPduInfoType.MetaDataPtr = NULL_PTR;

            #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
            CanNm_IntUpdateEIRA(&structPduInfoType.SduDataPtr[CANNM_BYTE0]);
            #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */
            returnValue = CanNm_RequestBusSynTransmit(canNmChannelIndex, &structPduInfoType);
          }
        }
        #if(CANNM_COM_CONTROL_ENABLED == STD_ON)
        else
        {
          /* Return E_NOT_OK if Communication is disable */
        }
        #endif /* #if(CANNM_COM_CONTROL_ENABLED == STD_ON) */
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }

  return returnValue;
}
#endif /* #if ((CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON) && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)) */

/*******************************************************************************
** Function Name        : CanNm_CheckRemoteSleepIndication                    **
**                                                                            **
** Service ID           : 0xD0                                                **
**                                                                            **
** Description          : Checks if remote sleep indication has taken place or**
**                        not.                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmRemoteSleepIndPtr                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
/* @Trace: SRS_Nm_00052 SRS_Nm_02509 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_CheckRemoteSleepIndication(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
  P2VAR(boolean, AUTOMATIC, CANNM_APPL_DATA) nmRemoteSleepIndPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_100 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_CHECK_REMOTESLEEPINDICATION_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (nmRemoteSleepIndPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_101 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_CHECK_REMOTESLEEPINDICATION_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_102 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_CHECK_REMOTESLEEPINDICATION_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_103 */
      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Get channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

      if ((ptrChannel->modeStatus == CANNM_BUS_SLEEP_MODE) ||
             (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE) ||
             (ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE))
      {
        /* Return E_NOT_OK */
      }
      else
      {
        /* @Trace: CanNm_SUD_API_104 */
        *nmRemoteSleepIndPtr = ptrChannel->remoteSlpDetect;
        returnValue = E_OK;
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }

  return returnValue;
}
#endif /*#if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_SetSleepReadyBit                              **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Set the NM Coordinator Sleep Ready bit              **
**                                              in the Control Bit Vector     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle, nmSleepReadyBit                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked   :                             **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        CanNm_IntCanIfTransmit                              **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if (CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON)
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetSleepReadyBit(
  VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
  VAR(boolean,CANNM_VAR) nmSleepReadyBit)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_CONST) ptrChannel;
  #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_105 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_SLEEP_READYBIT_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_106 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_SLEEP_READYBIT_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_107 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */

      SchM_Enter_CanNm_INTERNAL_STATUS();

      if (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE)
      {
        /* Return E_NOT_OK */
      }
      else
      {
        #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
        if ((CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition) && (CANNM_FALSE == nmSleepReadyBit))
        {
          /* @Trace: CanNm_SUD_API_108 */
          /* Clear NM Coordinator Sleep Ready Bit */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
            = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                              & ~(CANNM_SETSLEEP_BIT);
        }
        /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
        else if ((CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition))
        {
          /* @Trace: CanNm_SUD_API_109 */
          /* Set NM Coordinator Sleep Ready Bit */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
            = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                                | CANNM_SETSLEEP_BIT;
        }
        else
        {
          /* Do nothing */
        }
        #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
        /* @Trace: CanNm_SUD_API_110 */
        #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
        /* Trigger transmit a Nm PDU */
        (void)CanNm_IntCanIfTransmit(canNmChannelIndex);
        #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

        returnValue = E_OK;
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }

  return returnValue;
}
#endif /* #if (CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_TxConfirmation                                **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : Notify CAN NM that NM message has been successfully **
**                       transmitted.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant(but not for the same NM-channel)         **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : The CanNm and the CanIf itself are initialized      **
**                        correctly                                           **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus,                                   **
**                                                                            **
**                        Function Invoked:                                   **
**                        CanNm_IntGetChannelIdFromCanNmTxConfirmationHandleId**
**                        (void)Det_ReportError                               **
**                        PduR_CanNmTxConfirmation                            **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
/* @Trace: SRS_Nm_00151 SRS_BSW_00323 */
FUNC(void, CANNM_CODE) CanNm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_111 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TX_CONFIRMATION_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIdFromCanNmTxConfirmationHandleId(TxPduId, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_112 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TX_CONFIRMATION_SID, CANNM_E_INVALID_PDUID);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_113 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

      SchM_Enter_CanNm_INTERNAL_STATUS();
      
      if (ptrChannel->noOfImmediateNmTx > CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_114 */
        ptrChannel->noOfImmediateNmTx--;
      }
      else
      {
        /* Do nothing */
      }

      #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if(ptrPostBuildChannel->pnEnabled == CANNM_TRUE)
      #else
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if(ptrStaticChannel->pnEnabled == CANNM_TRUE)
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      {
        /* @Trace: CanNm_SUD_API_115 */
        ptrChannel->msgTimeOutTime = CANNM_ZERO;
      }
      else
      {
        /* Do nothing */
      }
      #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

      if(E_OK == result)
      {
        /* Checking if result is OK and in network mode*/
        if((ptrChannel->modeStatus != CANNM_BUS_SLEEP_MODE) &&
          (ptrChannel->modeStatus != CANNM_PREPAREBUS_SLEEP_MODE))
        {
          /* @Trace: CanNm_SUD_API_116 */
          /* Restart NM-Timeout Timer */
          ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {
        /* @Trace: CanNm_SUD_API_117 */
        /* If CanNm_TxConfirmation is called with result E_NOT_OK */
        Nm_TxTimeoutException(ptrStaticChannel->comMChannelId);
      }

      /* @Trace: CanNm_SUD_API_118 */
      SchM_Exit_CanNm_INTERNAL_STATUS();

      #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
      /*Invoke Pdur function to forward the transmission confirmation result*/
      PduR_CanNmTxConfirmation(ptrStaticChannel->txTriggerUserPduId, result);
      #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */
    }
  }
}
#endif /* #if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */

/*******************************************************************************
** Function Name        : CanNm_RxIndication                                  **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : Notify CAN NM that a NM message has been received.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant(but not for the same NM-channel)         **
**                                                                            **
** Input Parameters     : RxPduId, PduInfoPtr                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : The CanNm and the CanIf itself are initialized      **
**                        correctly                                           **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function Invoked:                                   **
**                        CanNm_IntGetChannelIdFromCanNmRxIndicationHandleId  **
**                        (void)Det_ReportError                               **
**                        CanNm_IntGetRxHandlingMethod                        **
**                        CanNm_Memcpy                                        **
**                        CanNm_IntUpdateEIRA                                 **
**                        CanNm_IntUpdateERA                                  **
**                        Nm_PduRxIndication                                  **
**                        Nm_NetworkStartIndication                           **
**                        Nm_RepeatMessageIndication                          **
**                        Nm_CoordReadyToSleepIndication                      **
**                        Nm_CoordReadyToSleepCancellation                    **
**                        Nm_RemoteSleepCancellation                          **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
**                        CanNm_RxIndicationSetInternalStatus                 **
*******************************************************************************/
/* @Trace: SRS_Nm_02509 SRS_BSW_00323 */
FUNC(void, CANNM_CODE) CanNm_RxIndication(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduInfoPtr)
{
  uint32 canNmChannelIndex;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;

  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  CANNM_RX_HANDLING_METHOD rxHandlingMethod;
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

  #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON))
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus != CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_119 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_RX_INDICATION_SID, CANNM_E_UNINIT);
  }
  /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "PduInfoPtr and PduInfoPtr->SduDataPtr are already checked null before" */
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if ((PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    /* @Trace: CanNm_SUD_API_120 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_RX_INDICATION_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIdFromCanNmRxIndicationHandleId(RxPduId, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_121 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_RX_INDICATION_SID, CANNM_E_INVALID_PDUID);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_122 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON))
      ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
      #endif /* #if ((CANNM_POSTBUILD_SUPPORTED == STD_ON) && (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)) */
      CanNm_Memset(ptrChannel->rxUserData, 0x00, CANNM_MAX_PDU_INFO_SIZE);
      CanNm_Memcpy(ptrChannel->rxUserData, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
      #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
      rxHandlingMethod = CanNm_IntGetRxHandlingMethod(canNmChannelIndex, ptrChannel->rxUserData);
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false following received message" */
      if ((CANNM_RX_HANDLING_METHOD_PROCESS_WITH_PARTIAL_NETWORK == rxHandlingMethod) ||
          (CANNM_RX_HANDLING_METHOD_PROCESS_WITHOUT_PARTIAL_NETWORK == rxHandlingMethod))
      #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
      {
        SchM_Enter_CanNm_INTERNAL_STATUS();
        /* Check meta data received */
        if(PduInfoPtr->MetaDataPtr != NULL_PTR)
        {
          /* @Trace: CanNm_SUD_API_124 */
          #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
          /* Set meta data flag as TRUE */
          ptrChannel->rxMetaDataCheck = CANNM_TRUE;
          /* Copy Rx meta data into internal buffer */
          CanNm_Memcpy(ptrChannel->rxMetaData, PduInfoPtr->MetaDataPtr, CANNM_METADATA_LENGTH);
          #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

          #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
          /* Set meta data flag as TRUE */
          CanNm_RxMetaDataCheck = CANNM_TRUE;
          /* Copy Rx meta data into internal buffer */
          CanNm_Memcpy(CanNm_RxMetaData, PduInfoPtr->MetaDataPtr, CANNM_METADATA_LENGTH);
          #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */
        }
		/* polyspace +12 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
        else
        {
          /* @Trace: CanNm_SUD_API_125 */
          #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
          /* Set meta data flag as FALSE */
          ptrChannel->rxMetaDataCheck = CANNM_FALSE;
          #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */
    
          #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
          CanNm_RxMetaDataCheck = CANNM_FALSE;
          #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

        }
        SchM_Exit_CanNm_INTERNAL_STATUS();
        
        #if (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
        if(ptrChannel->communicationEnabled != CANNM_FALSE)
        {
          /* @Trace: CanNm_SUD_API_126 */
          #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
          ptrChannel->msgCycleTime = ptrPostBuildChannel->msgReducedTime;
          #else
          ptrChannel->msgCycleTime = ptrStaticChannel->msgReducedTime;
          #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
        }
        else
        {
          /* Do nothing */
        }
        #endif /* #if (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON) */

        #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
        if(ptrStaticChannel->carWakeUpRxEnabled == CANNM_TRUE)
        {
          /* @Trace: CanNm_SUD_API_127 */
          /* Car wakeup processing */
          CanNm_CarWakeupProcess(PduInfoPtr, ptrChannel, ptrStaticChannel);
        }
        else
        {
          /* Do nothing */
        }
        #endif /* #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

        #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
        if (CANNM_RX_HANDLING_METHOD_PROCESS_WITH_PARTIAL_NETWORK == rxHandlingMethod)
        {
          /* @Trace: CanNm_SUD_API_128 */
          #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
          CanNm_IntUpdateEIRA(&PduInfoPtr->SduDataPtr[CANNM_BYTE0]);
          #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

          #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
          CanNm_IntUpdateERA(canNmChannelIndex, &PduInfoPtr->SduDataPtr[CANNM_BYTE0]);
          #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */
        }
        else
        {
          /* Do nothing */
        }
        #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
        /* @Trace: CanNm_SUD_API_129 */
        #if (CANNM_PDU_RXINDICATION_ENABLED == STD_ON)
        Nm_PduRxIndication(ptrStaticChannel->comMChannelId);
        #endif /* #if (CANNM_PDU_RXINDICATION_ENABLED == STD_ON) */
        CanNm_RxIndicationSetInternalStatus(canNmChannelIndex);
      }
      #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
      else
      {
        /* Do nothing */
      }
      #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
    }
  }
}

/*******************************************************************************
** Function Name        : CanNm_ConfirmPnAvailability                         **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : Enables the PN filter functionality on the          **
**                                            indicated NM channel            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked   :                             **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
/* @Trace: SRS_BSW_00323 */
FUNC(void, CANNM_CODE) CanNm_ConfirmPnAvailability(
  CONST(NetworkHandleType, CANNM_APPL_CONST)nmChannelHandle)
{
  uint32 canNmChannelIndex;
  
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_138 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_CONFIRM_PNAVAILABILITY_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_139 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_CONFIRM_PNAVAILABILITY_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_140 */
      /* Get channel configuration data and channel internal data */
      #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      
      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Enable the PN algorithm for the channel */
      ptrChannel->pnStatusBit = CANNM_TRUE;

      #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
      #if (CANNM_CBV_POS_OFF_PRESENT == STD_ON)
      /* Check and set PNI bit in CBV if PNC feature have been turn on */
      if(CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition)
      #endif
      {
        #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
        if (ptrPostBuildChannel->pnEnabled == CANNM_TRUE)
        {
          /* @Trace: CanNm_SUD_API_141 */
          /* Update the CBV for the Channel to enable PN */
          /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
          = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                    | CANNM_PNI_BIT;
        }
        else
        {
          /* @Trace: CanNm_SUD_API_142 */
          /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
            = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                    & ~(CANNM_PNI_BIT);
        }
        #else
        #if (CANNM_PN_DISABLED_PRESENT == STD_ON)
        if(ptrStaticChannel->pnEnabled == CANNM_TRUE)
        #endif
        {
          /* @Trace: CanNm_SUD_API_141 */
          /* Update the CBV for the Channel to enable PN */
          /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
          = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                    | CANNM_PNI_BIT;
        }
        #if (CANNM_PN_DISABLED_PRESENT == STD_ON)
        else
        {
          /* @Trace: CanNm_SUD_API_142 */
          /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
          ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
            = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] 
                                                    & ~(CANNM_PNI_BIT);
        }
        #endif
        #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      }
      #if (CANNM_CBV_POS_OFF_PRESENT == STD_ON)
      else
      {
        /* Do nothing */
      }
      #endif
      #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */

      SchM_Exit_CanNm_INTERNAL_STATUS();
    }
  }
}
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_TriggerTransmit                               **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : A function used to check whether the available data **
**                        fits into the buffer size or not.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds.                     **
**                        Non reentrant for the same PduId.                   **
**                                                                            **
** Input Parameters     : TxPduId, PduInfoPtr                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIdFromTriggerTransmitHandleId    **
**                        (void)Det_ReportError                               **
**                        CanNm_IntCollectTxData                              **
**                        CanNm_IntUpdateEIRA                                 **
**                        CanNm_Memcpy                                        **
*******************************************************************************/
#if (CANNM_TRIGGER_TRANSMIT_ENABLED == STD_ON)
/* @Trace: SRS_Nm_02503 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_TriggerTransmit(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANNM_VAR) PduInfoPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus != CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_143 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TRIGGER_TRANSMIT_SID, CANNM_E_UNINIT);
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else if (PduInfoPtr == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_144 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TRIGGER_TRANSMIT_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /*# if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIdFromTriggerTransmitHandleId(TxPduId, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_145 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_TRIGGER_TRANSMIT_SID, CANNM_E_INVALID_PDUID);
      #endif /*# if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_146 */
      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "PduInfoPtr->SduDataPtr is already checked null before" */
      if (ptrStaticChannel->pduLength <= PduInfoPtr->SduLength)
      {
        /* @Trace: CanNm_SUD_API_147 */
        #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
        CanNm_IntCollectTxData(canNmChannelIndex);
        #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */

        PduInfoPtr->SduLength = ptrStaticChannel->pduLength;

        (void)CanNm_Memcpy(PduInfoPtr->SduDataPtr,
                           ptrChannel->txUserData,
                           PduInfoPtr->SduLength);

        #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
        CanNm_IntUpdateEIRA(&PduInfoPtr->SduDataPtr[CANNM_BYTE0]);
        #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

        returnValue = E_OK;
      }
      else
      {
        /* If not fit, E_NOT_OK will be inform */
      }
    }
  }

  return returnValue;
}
#endif /* #if (CANNM_TRIGGER_TRANSMIT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_MainFunction                                  **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : Handles the CanNm states and the internal Timers    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
**                        (void)Det_ReportError                               **
**                        CanNm_IntExitPrepareBusSleepMode                    **
**                        CanNm_IntExitReadySleepState                        **
**                        CanNm_IntExitNetworkMode                            **
**                        CanNm_IntExitNormalOperationState                   **
**                        CanNm_IntExitRepeatMessageState                     **
**                        CanNm_IntEntryBusSleepMode                          **
**                        CanNm_IntEntryPrepareBusSleepMode                   **
**                        CanNm_IntEntryReadySleepState                       **
**                        CanNm_IntEntryNormalOperationState                  **
**                        CanNm_IntNetworkModeEntry                           **
**                        CanNm_IntEntryRepeatMessageState                    **
**                        CanNm_IntPrepareBusSleepMode                        **
**                        CanNm_IntReadySleepState                            **
**                        CanNm_IntNormalOperationState                       **
**                        CanNm_IntRepeatMessageState                         **
**                        CanNm_IntProcessMsgTimeOutTime                      **
**                        CanNm_IntProcessNmMessage                           **
**                        CanNm_IntProcessERATimer                            **
**                        CanNm_IntProcessEIRATimer                           **
**                        CanNm_IntProcessNmState                             **
*******************************************************************************/
/* @Trace: SRS_Nm_00053 SRS_Nm_00046 SRS_BSW_00323 */
FUNC(void, CANNM_CODE) CanNm_MainFunction(void)
{
  uint32 canNmChannelIndex;

  for (canNmChannelIndex = CANNM_ZERO; canNmChannelIndex < CANNM_NUMBER_OF_CHANNEL; canNmChannelIndex++)
  {
    /* @Trace: CanNm_SUD_API_148 */
    P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;

    SchM_Enter_CanNm_INTERNAL_STATUS();

    /* Get channel internal data */
    ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

    if (ptrChannel->modeStatus != ptrChannel->nextModeState)
    {
      #if (CANNM_NMS_POSITION_ENABLED == STD_ON)
      /* @Trace: CanNm_SUD_API_283 */
      CanNm_IntProcessNmState(canNmChannelIndex, ptrChannel->modeStatus, ptrChannel->nextModeState);
      #endif

      CanNm_ExitCurrentState(canNmChannelIndex);

      /* Check next mode state */
      CanNm_EntryNextState(canNmChannelIndex);
    }
    else
    {
      /* Do nothing */
    }

    /* Check current mode state */
    CanNm_ImplementCurrentState(canNmChannelIndex);

    SchM_Exit_CanNm_INTERNAL_STATUS();
  }
  /* @Trace: CanNm_SUD_API_164 */  
  SchM_Enter_CanNm_INTERNAL_STATUS();

  #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
  CanNm_IntProcessEIRATimer();
  #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

  #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
  CanNm_IntProcessERATimer();
  #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

  /* CanNm shall not perform transmission error handling */
  #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  CanNm_IntProcessMsgTimeOutTime();
  #endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

  CanNm_IntProcessNmMessage();
    
  SchM_Exit_CanNm_INTERNAL_STATUS();
}

/*******************************************************************************
** Function Name        : CanNm_IntProcessNmState                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Process NM State                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : LulCanNmChannelIndex                                **
**                      : previousMode                                        **
**                      : currentMode                                         **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayChannel, CanNm_ArrayStaticChannel        **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_ES95480_03E_SWP_00088 */
#if(STD_ON == CANNM_NMS_POSITION_ENABLED)
static FUNC(void, CANNM_CODE) CanNm_IntProcessNmState(uint32 CanNmChannelIndex, CanNm_ModeState previousMode, CanNm_ModeState currentMode)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  CanNm_PduPositionType nmStatePos;
  
  ptrChannel = &CanNm_ArrayChannel[CanNmChannelIndex];
  nmStatePos = CanNm_ArrayStaticChannel[CanNmChannelIndex].nmStatePosition;

  SchM_Enter_CanNm_INTERNAL_STATUS();
  if ((previousMode == CANNM_REPEAT_MESSAGE_STATE) && (currentMode == CANNM_NORMAL_OPERATION_STATE))
  {
    /* @Trace: CanNm_SUD_API_271 */
    ptrChannel->nmState = NM_STATE_NS_RMS;
  }
  else if ((previousMode == CANNM_READY_SLEEP_STATE) && (currentMode == CANNM_NORMAL_OPERATION_STATE))
  {
    /* @Trace: CanNm_SUD_API_272 */
    ptrChannel->nmState = NM_STATE_NS_RSS;
  }
  else if ((previousMode == CANNM_BUS_SLEEP_MODE) && (currentMode == CANNM_REPEAT_MESSAGE_STATE))
  {
    /* @Trace: CanNm_SUD_API_273 */
    ptrChannel->nmState = NM_STATE_RMS_BSM;
  }
  else if ((previousMode == CANNM_PREPAREBUS_SLEEP_MODE) && (currentMode == CANNM_REPEAT_MESSAGE_STATE))
  {
    /* @Trace: CanNm_SUD_API_274 */
    ptrChannel->nmState = NM_STATE_RMS_PBSM;
  }
  else if ((previousMode == CANNM_NORMAL_OPERATION_STATE) && (currentMode == CANNM_REPEAT_MESSAGE_STATE))
  {
    /* @Trace: CanNm_SUD_API_275 */
    ptrChannel->nmState = NM_STATE_RMS_NS;
  }
  else if ((previousMode == CANNM_READY_SLEEP_STATE) && (currentMode == CANNM_REPEAT_MESSAGE_STATE))
  {
    /* @Trace: CanNm_SUD_API_276 */
    ptrChannel->nmState = NM_STATE_RMS_RSS;
  }
  else if ((previousMode == CANNM_REPEAT_MESSAGE_STATE) && (currentMode == CANNM_READY_SLEEP_STATE))
  {
    /* @Trace: CanNm_SUD_API_277 */
    ptrChannel->nmState = NM_STATE_RSS_RMS;
  }
  else if ((previousMode == CANNM_NORMAL_OPERATION_STATE) && (currentMode == CANNM_READY_SLEEP_STATE))
  {
    /* @Trace: CanNm_SUD_API_278 */
    ptrChannel->nmState = NM_STATE_RSS_NS;
  }
  else if ((previousMode == CANNM_READY_SLEEP_STATE) && (currentMode == CANNM_PREPAREBUS_SLEEP_MODE))
  {
    /* @Trace: CanNm_SUD_API_279 */
    ptrChannel->nmState = NM_STATE_PBSM_RSS;
  }
  else if ((previousMode == CANNM_PREPAREBUS_SLEEP_MODE) && (currentMode == CANNM_BUS_SLEEP_MODE))
  {
    /* @Trace: CanNm_SUD_API_280 */
    ptrChannel->nmState = NM_STATE_BSM_PBSM;
  }
  else
  {
    /* @Trace: CanNm_SUD_API_281 */
    #if (CANNM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_MAINFUNCTION_SID, CANNM_E_INVALID_REQUEST);
    #endif /* if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  }
  #if(STD_ON == CANNM_NMS_POSITION_ENABLED)
  #if(STD_ON == CANNM_NMS_POSITION_ENABLE_DISABLE_MIXED)
  if(nmStatePos != CANNM_PDU_OFF)
  #endif
  {
    /* @Trace: CanNm_SUD_API_282 */
    ptrChannel->txUserData[nmStatePos] = (uint8)ptrChannel->nmState;
  }
  #endif
  SchM_Exit_CanNm_INTERNAL_STATUS();
}
#endif
/*******************************************************************************
** Function Name        : CanNm_SetNetworkRequestReason                       **
**                                                                            **
** Service ID           : 0xF2                                                **
**                                                                            **
** Description          : Sets Network Request Reason Data for NM messages    **
**                        transmitted next on the bus.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle, nmNetworkRequestReason             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm is initialized correctly                      **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                        CanNm_ArrayStaticChannel                            **
**                        CanNm_ArrayChannel                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
/* @Trace: SRS_ES95480_03E_SWP_00087 */
#if (CANNM_REASON_POSITION_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetNetworkRequestReason(
  CONST(NetworkHandleType, CANNM_CONST) nmChannelHandle,
  CONST(uint8, CANNM_APPL_CONST) nmNetworkRequestReason)
{
  Std_ReturnType returnValue = E_NOT_OK;
  #if (CANNM_REASON_POSITION_ENABLED == STD_ON)
  uint32 canNmChannelIndex = 0;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  CanNm_PduPositionType nwRequestReasonPos;
  
  SchM_Enter_CanNm_INTERNAL_STATUS();
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_284 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_NETWORK_REQUEST_REASON_SID, CANNM_E_UNINIT);
  }
  else if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
  {
    /* @Trace: CanNm_SUD_API_285 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_NETWORK_REQUEST_REASON_SID, CANNM_E_INVALID_CHANNEL);
  }
  else
  #endif
  {
    #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)

    P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) LpStaticChannel;
    LpStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
    nwRequestReasonPos = LpStaticChannel->nwRequestReasonPosition;

    #if (CANNM_REASON_POSITION_ENABLE_DISABLE_MIXED == STD_ON)

    if ((uint8)CANNM_PDU_OFF == nwRequestReasonPos)
    {
      /* @Trace: CanNm_SUD_API_287 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SET_NETWORK_REQUEST_REASON_SID, CANNM_E_INVALID_REQUEST);
      #endif /* if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    #endif
    {
      /* @Trace: CanNm_SUD_API_288 */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrChannel->nwRequestReason = nmNetworkRequestReason;

      ptrChannel->txUserData[nwRequestReasonPos] = ptrChannel->nwRequestReason;
      returnValue = E_OK;
    }
    #endif
  }

  SchM_Exit_CanNm_INTERNAL_STATUS();
  #endif
  return returnValue;
}
#endif

/*******************************************************************************
** Function Name        : CanNm_GetNetworkRequestReason                       **
**                                                                            **
** Service ID           : 0xF3                                                **
**                                                                            **
** Description          : Gets Network Request Reason from the latest received**
**                        NM message.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pNmNetworkRequestReason                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm is initialized correctly                      **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                        CanNm_ArrayChannel                                  **
**                        CanNm_StaticArrayChannel                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        Det_ReportError                                     **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
/* @Trace: SRS_ES95480_03E_SWP_00087 */
#if (CANNM_REASON_POSITION_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNetworkRequestReason(
  CONST(NetworkHandleType, CANNM_CONST) nmChannelHandle,
  CONSTP2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNetworkRequestReason)
{
  Std_ReturnType returnValue = E_NOT_OK;

  #if (CANNM_REASON_POSITION_ENABLED == STD_ON)
  uint32 canNmChannelIndex = 0;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_CONST) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  CanNm_PduPositionType nwRequestReasonPos;

  SchM_Enter_CanNm_INTERNAL_STATUS();
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_290 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NETWORK_REQUEST_REASON_SID, CANNM_E_UNINIT);
  }
  else if (nmNetworkRequestReason == NULL_PTR)
  {
    /* @Trace: CanNm_SUD_API_291 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NETWORK_REQUEST_REASON_SID, CANNM_E_PARAM_POINTER);
  }
  else if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
  {
    /* @Trace: CanNm_SUD_API_292 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NETWORK_REQUEST_REASON_SID, CANNM_E_INVALID_CHANNEL);

  }
  else
#endif /* if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: CanNm_SUD_API_293 */
    ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
    ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
    nwRequestReasonPos = ptrStaticChannel->nwRequestReasonPosition;
    #if ((CANNM_REASON_POSITION_ENABLE_DISABLE_MIXED == STD_ON) && (CANNM_DEV_ERROR_DETECT == STD_ON))
    if ((uint8)CANNM_PDU_OFF == nwRequestReasonPos)
    {
      /* @Trace: CanNm_SUD_API_294 */
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NETWORK_REQUEST_REASON_SID, CANNM_E_INVALID_REQUEST);
    }
    else
    #endif
    {
      /* @Trace: CanNm_SUD_API_295 */
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
      *nmNetworkRequestReason = ptrChannel->rxUserData[nwRequestReasonPos];

      returnValue = E_OK;
    }
  }

  SchM_Exit_CanNm_INTERNAL_STATUS();
  #endif
  return returnValue;
}
#endif

#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_EnableCommunication_TimerisNotStarted         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Enables the NM PDU transmission ability.            **
**                        (Don't start network timeout timer)                 **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication_TimerisNotStarted(
                      VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle)
{
  volatile Std_ReturnType returnValue = E_NOT_OK;
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;

  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_306 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_ENABLE_COMMUNICATION_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_307 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_ENABLE_COMMUNICATION_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_308 */
      #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)

      /* Get channel configuration data and channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
      ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

      SchM_Enter_CanNm_INTERNAL_STATUS();
      if(ptrChannel->communicationEnabled == CANNM_TRUE)
      {
        /* Return E_NOT_OK */
      }
      else
      {
      /* @Trace: CanNm_SUD_API_309 */
        /* Start the Message Cycle Timer */
        ptrChannel->msgCycleTime = ptrStaticChannel->msgCycleTime;

        #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
        /* Start the Remote Sleep Timeout */
        ptrChannel->remoteSleepIndTime = ptrStaticChannel->remoteSleepIndTime;
        #endif /* #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

        /* Enable the transmission of NM PDUS */
        ptrChannel->communicationEnabled = CANNM_TRUE;

        returnValue = E_OK;
      }

      SchM_Exit_CanNm_INTERNAL_STATUS();
      #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
    }
  }

  return returnValue;
}
#endif /* #if (CANNM_COM_CONTROL_ENABLED == STD_ON) */

#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_DisableCommunication_TimerisNotStopped        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Disables the NM PDU transmission ability.           **
**                        (Don't stop network timeout timer)                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_InitStatus                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetChannelIndexFromNmHandleId              **
**                        (void)Det_ReportError                               **
**                        Nm_RemoteSleepCancellation                          **
**                        SchM_Enter_CanNm_INTERNAL_STATU                     **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication_TimerisNotStopped(
                      VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle)
{
  uint32 canNmChannelIndex;
  Std_ReturnType returnValue = E_NOT_OK;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (CanNm_InitStatus == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_300 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_DISABLE_COMMUNICATION_SID, CANNM_E_UNINIT);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK != CanNm_IntGetChannelIndexFromNmHandleId(nmChannelHandle, &canNmChannelIndex))
    {
      /* @Trace: CanNm_SUD_API_301 */
      #if (CANNM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_DISABLE_COMMUNICATION_SID, CANNM_E_INVALID_CHANNEL);
      #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* @Trace: CanNm_SUD_API_302 */
      #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      SchM_Enter_CanNm_INTERNAL_STATUS();

      /* Get channel internal data */
      ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

      /* @Trace: CanNm_SUD_API_303 */
      ptrChannel->communicationEnabled = CANNM_FALSE;

      /* Stop the Message Cycle Timer */
      ptrChannel->msgCycleTime = CANNM_ZERO;

      ptrChannel->transmissionRequestFailed = CANNM_FALSE;

      #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
      /* Stop the Remote Sleep Timer */
      ptrChannel->remoteSleepIndTime = CANNM_ZERO;
      if (ptrChannel->remoteSlpDetect == CANNM_TRUE)
      {
        /* @Trace: CanNm_SUD_API_304 */
        /* Get channel configuration data */
        ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

        ptrChannel->remoteSlpDetect = CANNM_FALSE;
        Nm_RemoteSleepCancellation(ptrStaticChannel->comMChannelId);
      }
      else
      {
        /* Do nothing */
      }
      #endif /* #if(CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
      /* @Trace: CanNm_SUD_API_305 */
      returnValue = E_OK;

      SchM_Exit_CanNm_INTERNAL_STATUS();
      #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
    }
  }

  return returnValue;
}
#endif /* #if (CANNM_COM_CONTROL_ENABLED == STD_ON) */
#define CANNM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
