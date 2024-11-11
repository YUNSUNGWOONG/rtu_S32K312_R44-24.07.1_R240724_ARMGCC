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
**  SRC-MODULE: LinIf_SubProcess.c                                            **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LINIF Sub Processing Functions                   **
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
** 1.0.13      21-Aug-2023   KhaLN1          #CP44-2481, #CP44-2254           **
** 1.0.11      07-Mar-2023   KhaLN1          #CP44-1917                       **
** 1.0.10      07-Mar-2023   KhaLN1          #CP44-1811                       **
** 1.0.8       27-Dec-2022   HJ Seong        #CP44-1378                       **
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
#include "LinIf_SubProcess.h"       /* LinIf Sub Processing header */

#if(LINTP_SUPPORT == STD_ON)
#include "LinTp.h"                  /* LinTp header */
#include "LinTp_Rx.h"               /* LinTp internal function header  */
#include "LinTp_Tx.h"               /* LinTp internal function header  */
#include "LinTp_Ram.h"              /* LinTp Ram header  */
#if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
#include "BswM_LinTp.h"             /* BswM callback header for LinTp */
#endif
#include "PduR_LinTp.h"             /* PduR callback header for LinTp */
#endif

#if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_OFF)
#include "Lin.h"                    /* LIN header */
#endif

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "LinIf_Ram.h"              /* LinIf RAM header */
#include "SchM_LinIf.h"             /* Schedule Manager header */
#include "PduR_LinIf.h"
#include "LinSM.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */
CONST(LinIf_FrameInfo, LINIF_DATA) LinIf_GaaFixedFrameInfo [LINIF_TWO] =
{
  /* Frame 0 - MRF frame or Fixed MRF frame */
  {
    /* ddPid */
    LINIF_MRF_PID,

    /* ddCs */
    (Lin_FrameCsModelType)LIN_CLASSIC_CS,

    /* ddDrc */
    (Lin_FrameResponseType)LINIF_FRAMERESPONSE_TX,

    /* ddDl */
    LINIF_EIGHT,

    /* ddLocalHandleId */
    LINIF_ZERO,
    /* ddFrameType */
    LINIF_FIXED_MRF_FRAME,
    /* ucFrameIndex */
    LINIF_ZERO
  },

  /* Frame 1 - SRF frame or Fixed SRF frame */
  {
    /* ddPid */
    LINIF_SRF_PID,

    /* ddCs */
    (Lin_FrameCsModelType)LIN_CLASSIC_CS,

    /* ddDrc */
    (Lin_FrameResponseType)LINIF_FRAMERESPONSE_RX,

    /* ddDl */
    LINIF_EIGHT,

    /* ddLocalHandleId */
    LINIF_ZERO,
    /* ddFrameType */
    LINIF_FIXED_SRF_FRAME,
    /* ucFrameIndex */
    LINIF_ZERO
  }
};
/* polyspace-end VARIABLE:ALL [Not a defect:LoW] "This variable do not interfere with each other" */
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (LINTP_SUPPORT == STD_ON)

static FUNC(uint8, LINIF_CODE) LinTp_HandleP2Timer (
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData);

static FUNC(uint8, LINIF_CODE) LinTp_HandleNCsTimer (
  NetworkHandleType LddChnlIndex,
  P2CONST(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo);

static FUNC(uint8, LINIF_CODE) LinTp_HandleNCrTimer (
  NetworkHandleType LddChnlIndex,
  P2CONST(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo);

static FUNC(uint8, LINIF_CODE) LinTp_HandleNAsTimer (
  NetworkHandleType LddChnlIndex,
  P2CONST(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo);

#endif /* (LINTP_SUPPORT == STD_ON) */

static FUNC(uint8, LINIF_CODE) LinTp_GetNextScheduleId (
  uint8 LucComp,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData);

/*******************************************************************************
** Function Name      : LinIf_SleepReqMainFunction                            **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This functions checks the status of sleep status bit  **
**                      and processes the Goto Sleep command.                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpChannelPtr, LucChannelId                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaDriverApis, Lin_GoToSleep,                   **
**                      Lin_GoToSleepInternal, LinIf_GaaGoToSleepConfFun,     **
**                      LinIf_GaaLtChannelInfo                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Lin_GoToSleep(), LinIf_ChangeToNullSchedule(),        **
**                      Lin_Wakeup(), LinSM_GotoSleep_Confirmation(),         **
**                      LinIf_GaaSchReqConfFun()                              **
**                      SchM_Enter_LinIf_STATUS_PROTECTION                    **
**                      SchM_Exit_LinIf_STATUS_PROTECTION                     **
**                      SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION       **
**                      SchM_Enter_LinIf_WAKEUP_CONFCOUNT_PROTECTION          **
**                      SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION            **
**                      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION      **
**                      SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION           **
**                      SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION             **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"
#if(LINTP_SUPPORT == STD_ON)
FUNC(void, LINIF_CODE) LinIf_SleepReqMainFunction (
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(void, AUTOMATIC, LINIF_CONST) LpTpChannelPtr,
  NetworkHandleType LddChnlIndex)
#else
FUNC(void, LINIF_CODE) LinIf_SleepReqMainFunction(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex)
#endif
{
  /* @Trace: LinIf_SUD_API_258*/
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA), AUTOMATIC,
    LINIF_DATA) LppRxDataPtr;
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpRxDataPtr;
  Lin_StatusType LenLinIfStatus;

  LpChannelRamData = LpChannelPtr->pChannelRamData;
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
  if (LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
  {
    if(LINIF_ZERO == LpChannelRamData->usDelayCounter)
    {
      /* @Trace: LinIf_SUD_API_259*/
      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      if(LINIF_SLEEP_REQ_PENDING == LpChannelRamData->ucSleepRequested)
      {
        /* @Trace: LinIf_SUD_API_260*/
        SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION();
        if(LINIF_CHANNEL_SLEEP != LpChannelRamData->ucChannelSts)
        {
          /* @Trace: LinIf_SUD_API_261*/
          SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
          #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
          /* Invoke respective Driver GotoSleep */
          (void)LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
            ucDriverIndex].pLinGoToSleep(LinIf_GaaLtChannelInfo[LddChnlIndex].
            ucDrvChannelId);
          #else
          /* Invoke GotoSleep function */
          (void)Lin_GoToSleep(LinIf_GaaLtChannelInfo[LddChnlIndex].
          ucDrvChannelId);
          #endif
          /* Load the maximum frame delay count */
          LpChannelRamData->usDelayCounter =
                                    (uint16)LpChannelPtr->ucMaxFrameDelay;
          /* Start of the critical area for sleep request status */
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Update the sleep requested state to sleep sent */
          LpChannelRamData->ucSleepRequested = LINIF_SLEEP_COMMAND_SENT;
          /* Exit the critical area for sleep status */
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Clear the wakeup flag */
          LpChannelRamData->blWakeupStatus = LINIF_FALSE;
        } /* if(LpChannelRamData->ucChannelSts != LINIF_CHANNEL_SLEEP) */
        else
        {
          /* @Trace: LinIf_SUD_API_262*/
          SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
          #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
          /* Invoke respective Driver Go to sleep internal function */
          (void) LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
            ucDriverIndex].pLinGoToSleepInternal(LinIf_GaaLtChannelInfo
            [LddChnlIndex].ucDrvChannelId);
          #else
          (void) Lin_GoToSleepInternal(LinIf_GaaLtChannelInfo[LddChnlIndex].
            ucDrvChannelId);
          #endif
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Clear the sleep requested state */
          LpChannelRamData->ucSleepRequested = LINIF_ZERO;
          SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          /* Clear the wakeup flag */
          LpChannelRamData->blWakeupStatus = LINIF_FALSE;
          #if (LINIF_CDD_SUPPORT == STD_ON)
          (LinIf_GaaGoToSleepConfFun[LddChnlIndex])
           (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
          #else
          LinSM_GotoSleepConfirmation(
            LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
          #endif
        }
      } /* @ if(LpChannelRamData->ucSleepRequested == LINIF_SLEEP_REQ_PENDING) */
      else /* Sleep command transmitted */
      {
        /* @Trace: LinIf_SUD_API_263*/
        SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        LpRxDataPtr = NULL_PTR;
        LppRxDataPtr = &LpRxDataPtr;
        #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Invoke respective Driver GetStatus function */
        LenLinIfStatus =
        LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].ucDriverIndex].
           pLinGetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId,
                                                                 LppRxDataPtr);
        #else
        /* Invoke the GetStatus function */
        LenLinIfStatus = Lin_GetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucDrvChannelId, LppRxDataPtr);
        #endif

        if((LIN_CH_SLEEP == LenLinIfStatus) && \
            (LINIF_FALSE == LpChannelRamData->blWakeupStatus))
        {
          /* @Trace: LinIf_SUD_API_264*/
          SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
          if(LINIF_WAKEUP_REQUESTED == LpChannelRamData->ucSleepRequested)
          {
            /* @Trace: LinIf_SUD_API_265*/
            SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
            #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
            /* Invoke respective Driver Wakeup */
            (void)LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
              ucDriverIndex].pLinWakeup(LinIf_GaaLtChannelInfo[LddChnlIndex].
              ucDrvChannelId);
            #else
            /* Invoke Wakeup function */
            (void)Lin_Wakeup(
                          LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId);
            #endif
          }
          else
          {
            /* @Trace: LinIf_SUD_API_266*/
            SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();

            #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
            /* Invoke respective Driver Go to sleep internal function */
            (void) LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
              ucDriverIndex].pLinGoToSleepInternal(LinIf_GaaLtChannelInfo
              [LddChnlIndex].ucDrvChannelId);
            #else
            (void) Lin_GoToSleepInternal(LinIf_GaaLtChannelInfo[LddChnlIndex].
              ucDrvChannelId);
            #endif

            #if(LINTP_SUPPORT == STD_ON)
            /* Change to NULL Schedule */
            LinIf_ChangeToNullSchedule(LpChannelPtr, LpTpChannelPtr);
            #else
            /* Change to NULL Schedule */
            LinIf_ChangeToNullSchedule(LpChannelPtr);
            #endif /* #if(LINTP_SUPPORT == STD_ON) */
            #if (LINIF_CDD_SUPPORT == STD_ON)

            /* Inform Null schedule change to LinSM by giving schedule
             * request confirmation
             */
            (LinIf_GaaSchReqConfFun[LddChnlIndex])
              (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId,
              LpChannelRamData->ddActivSchId);
            #else
            LinSM_ScheduleRequestConfirmation(
              LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId,
              LpChannelRamData->ddActivSchId);
            #endif

            SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION();
            /* Change the channel status to sleep */
            LpChannelRamData->ucChannelSts = LINIF_CHANNEL_SLEEP;
            SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
            #if (LINIF_CDD_SUPPORT == STD_ON)
            (LinIf_GaaGoToSleepConfFun[LddChnlIndex])
              (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
            #else
            LinSM_GotoSleepConfirmation(
              LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_TRUE);
            #endif
          }
        } /* @ if(LenLinIfStatus == LIN_CH_SLEEP) */
        else
        {
          if(LINIF_WAKEUP_REQUESTED != LpChannelRamData->ucSleepRequested)
          {
            /* @Trace: LinIf_SUD_API_267*/
            #if (LINIF_CDD_SUPPORT == STD_ON)
            (LinIf_GaaGoToSleepConfFun[LddChnlIndex])
             (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_FALSE);
            #else
            LinSM_GotoSleepConfirmation(
              LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, LINIF_FALSE);
            #endif
          }
        }
        /* @Trace: LinIf_SUD_API_268*/
        SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
        /* Clear the sleep requested state */
        LpChannelRamData->ucSleepRequested = LINIF_ZERO;
        SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
      }
    } /* Delay counter = 0 */
    else
    {
      /* @Trace: LinIf_SUD_API_269*/
      (LpChannelRamData->usDelayCounter)--;
    }
  }
  #endif
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  /* Check if Node type is Slave Node */
  if (LINIF_SLAVE_NODE == LpChannelPtr->ddNodeType)
  {
    /* @Trace: LinIf_SUD_API_270*/
    /* Invoke the upper layer confirmation callback */
    #if (LINIF_CDD_SUPPORT == STD_ON)
    (LinIf_GaaGoToSleepIndFun[LddChnlIndex])\
    (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId);
    #else
    LinSM_GotoSleepIndication(\
                  LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId);
    #endif
  } else {
    /* To Avoid QAC Warnings */
  }
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinIf_ProcessPrevStatus                               **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function checks the status of the previous frame **
**                      transmission and reception on the LIN Channel and     **
**                      indicates upper layer in case of success or failure.  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpChannelPtr, LddChnlIndex, LpTpChannelPtr           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Lin_GetStatus(), LinIf_ProcessStatusUncond()          **
**                      LinIf_ProcessStatusSporadic(), LinIf_GaaLtChannelInfo **
**                      LinIf_ProcessStatusEventTrig(),                       **
**                      LinIf_GaaDriverApis(), LinIf_ProcessStatusSRF()       **
**                      LinIf_ProcessStatusMRF()                              **
*******************************************************************************/
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
#if(LINTP_SUPPORT == STD_ON)
FUNC(void, LINIF_CODE) LinIf_ProcessPrevStatus(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelPtr,
  NetworkHandleType LddChnlIndex)
#else
FUNC(void, LINIF_CODE) LinIf_ProcessPrevStatus(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex)
#endif
{
  /* @Trace: LinIf_SUD_API_271*/
  uint16 LusSchEntry;
  LinIf_SchHandleType LddScheduler;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;

  #if (LINIF_FIXEDSRF_FRAMES == STD_ON)
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA),
    AUTOMATIC, LINIF_DATA) LppRxDataPtr;
  /* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpDummyPtr;
  Lin_StatusType LenLinIfStatus;
  #endif /* (LINIF_FIXEDSRF_FRAMES == STD_ON) */
  LinIf_FrameType LddFrameType;
  /* Get the pointer to the Channel RAM Data */
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  #if (LINIF_FIXEDSRF_FRAMES == STD_ON)
  LpDummyPtr = NULL_PTR;
  LppRxDataPtr = &LpDummyPtr;
  #endif /* (LINIF_FIXEDSRF_FRAMES == STD_ON) */
  LddScheduler = \
              LpChannelPtr->ddFirstScheduler + LpChannelRamData->ddActivSchId;
  /* Get the previous scheduler entry pointer */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LusSchEntry = \
    (LinIf_GaaConfiguration[0].pSchTable[LddScheduler].usSchFirstEntry) + \
                ((uint16)LpChannelRamData->ucSchEntryNum - (uint16)LINIF_ONE);
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* Get the frame type of the previous schedule entry */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LddFrameType = \
    LinIf_GaaConfiguration[0].pSchTblEntry[LusSchEntry].pFramePtr->ddFrameType;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  switch(LddFrameType)
  {
    case LINIF_UNCONDITIONAL_FRAME:
    {
      /* @Trace: LinIf_SUD_API_272*/
      LinIf_ProcessStatusUncond(LddChnlIndex, LpChannelPtr);
    }
    break;
    #if(LINIF_SPORADIC_FRAMES == STD_ON)
    case LINIF_SPORADIC_FRAME:
    {
      /* @Trace: LinIf_SUD_API_273*/
      LinIf_ProcessStatusSporadic(LddChnlIndex, LpChannelPtr);
    }
    break;
    #endif
    #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
    case LINIF_EVENT_TRIGGERED_FRAME:
    {
      /* @Trace: LinIf_SUD_API_274*/
      LinIf_ProcessStatusEventTrig(LddChnlIndex, LpChannelPtr);
    }
    break;
    #endif
    #if(LINTP_SUPPORT == STD_ON)
    case LINIF_MRF_FRAME:
    {
      /* @Trace: LinIf_SUD_API_275*/
      LinIf_ProcessStatusMRF(LddChnlIndex, LpChannelPtr, LpTpChannelPtr);
    }
    break;
    case LINIF_SRF_FRAME:
    {
      /* @Trace: LinIf_SUD_API_276*/
      LinIf_ProcessStatusSRF(LddChnlIndex, LpChannelPtr, LpTpChannelPtr);
    }
    break;
    #endif
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
    #if (LINIF_FIXEDSRF_FRAMES == STD_ON)
    case LINIF_FIXED_SRF_FRAME:
      #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
      /* Invoke respective Driver GetStatus function */
      LenLinIfStatus = LinIf_GaaDriverApis [LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucDriverIndex].pLinGetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucDrvChannelId, LppRxDataPtr);
      #else
      /* @Trace: LinIf_SUD_API_277*/
      /* Invoke the GetStatus function */
      LenLinIfStatus = Lin_GetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucDrvChannelId, LppRxDataPtr);
      #endif

      /* Check if there is no response from slave */
      if(LIN_RX_NO_RESPONSE == LenLinIfStatus)
      {
        /* @Trace: LinIf_SUD_API_278*/
      #if (LINIF_DEV_ERROR_DETECT == STD_ON)
        /* Report Development error LINIF_E_NC_NO_RESPONSE
         * to DET.
        */
        (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
          LINIF_MAINFUNCTION_SID, LINIF_E_NC_NO_RESPONSE);
      #endif
      }
      /* @Trace: LinIf_SUD_API_279*/
    break;
    #endif /* (LINIF_FIXEDSRF_FRAMES == STD_ON) */
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
    default:
    /** Redmine #13950: fixed MISRA violation **/
    {
      /* @Trace: LinIf_SUD_API_280*/
      break;
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
  }
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_ChangeSchedule                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used for switching the schedule table**
**                      to the requested schedule table.                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpChannelPtr                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                     LinIf_GaaSchReqConfFun, LinIf_GaaLtChannelInfo         **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      LinSM_ScheduleRequest_Confirmation()                  **
**                                                                            **
*******************************************************************************/
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_ChangeSchedule
(P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex)
{
  /* @Trace: LinIf_SUD_API_281*/
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  /* Initialize delay counter */
  LpChannelRamData->usDelayCounter = LINIF_ZERO;
  /* Initialize schedule entry number */
  LpChannelRamData->ucSchEntryNum = LpChannelRamData->ucTempEntryNum;
  /* Redmine #11084: Reset the Schedule Request when the schedule is changed */
  *(LpChannelPtr->pSchId) = LpChannelPtr->ddMaxSchs;

  #if (LINIF_CDD_SUPPORT == STD_ON)
  (LinIf_GaaSchReqConfFun[LddChnlIndex])
    (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId,
    LpChannelRamData->ddActivSchId);
  #else
  LinSM_ScheduleRequestConfirmation(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ddComMNwHndlId, LpChannelRamData->ddActivSchId);
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_CheckForIdToServe                               **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used for checking the latest Schedule**
**                      table need to be executed.                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpChannelPtr                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : LucScheduleTableToRet                                 **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaSchReqConfFun, LinIf_GaaLtChannelInfo        **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      None                                                  **
**                                                                            **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, LINIF_CODE) LinIf_CheckForIdToServe(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  NetworkHandleType LddChnlIndex)
{
  /* @Trace: LinIf_SUD_API_282*/
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  uint8 LucIdToReturn;
  uint8 LucComp;

  LucIdToReturn = LINIF_ZERO;
  LucComp = LINIF_ZERO;

  /* Get the Channel RAM data */
  LpChannelRamData = LpChannelPtr->pChannelRamData;

  /* Check whether pending schedule table id is valid */
  if((LpChannelRamData->ddPendingId) < (LpChannelPtr->ddMaxSchs))
  {
    /* @Trace: LinIf_SUD_API_283*/
    LucComp = LINIF_ONE;
  }
  /* Check whether requested schedule table id is valid */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  if(*(LpChannelPtr->pSchId) < (LpChannelPtr->ddMaxSchs))
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  {
    /* @Trace: LinIf_SUD_API_284*/
    LucComp = LucComp + LINIF_TWO;
  /* Check whether requested schedule table id
                             is valid and equal to pending schedule table id */
    if(*(LpChannelPtr->pSchId) == LpChannelRamData->ddPendingId)
    {
      /* Check whether active schedule table is completed */
      if(LpChannelRamData->ddActivSchId != LpChannelRamData->ddCompltdSchId)
      {
        /* @Trace: LinIf_SUD_API_285*/
        /* Making the particular Memory pointing to Schedule Id
         * to Invalid value.
         */
        LucIdToReturn = *(LpChannelPtr->pSchId);
        *(LpChannelPtr->pSchId) = LpChannelPtr->ddMaxSchs;
        /* polyspace-begin DEFECT:SIGN_CHANGE [Justified:Low] "The condition to enter this branch makes the LucComp value always greater than 2, so the calculation result will always be greater than 0" */
        /* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "The condition to enter this branch makes the LucComp value always greater than 2, so the calculation result will always be greater than 0" */
        /* @Trace: LinIf_SUD_API_286*/
        LucComp = (LucComp - LINIF_TWO);
        /* polyspace-end CERT-C:INT02-C [Justified:Low] "The condition to enter this branch makes the LucComp value always greater than 2, so the calculation result will always be greater than 0" */
        /* polyspace-end MISRA-C3:D4.1 [Justified:Low] "The condition to enter this branch makes the LucComp value always greater than 2, so the calculation result will always be greater than 0" */
        /* polyspace-end DEFECT:SIGN_CHANGE [Justified:Low] "The condition to enter this branch makes the LucComp value always greater than 2, so the calculation result will always be greater than 0" */
      }
      /* Invoke <User>_ScheduleRequestConfirmation */
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaSchReqConfFun[LddChnlIndex])
        (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId,
        *(LpChannelPtr->pSchId));
      #else
      /* @Trace: LinIf_SUD_API_287*/
      LinSM_ScheduleRequestConfirmation(LinIf_GaaLtChannelInfo[LddChnlIndex].
        ddComMNwHndlId, *(LpChannelPtr->pSchId));
      #endif
    }
  }
  /* Check if the requested schedule is a 'NULL_SCHEDULE' */
  if(LINIF_NULL_SCHEDULE == *(LpChannelPtr->pSchId))
  {
    /* @Trace: LinIf_SUD_API_288*/
    LucIdToReturn = LINIF_NULL_SCHEDULE;
  }
  /* 1. If the requested schedule is not a 'NULL_SCHEDULE'  */
  /* 2. or there is no schedule that is requested       */
  else
  {
    /* If the active schedule is not a 'NULL_SCHEDULE'  */
    if(LINIF_ZERO < LpChannelRamData->ddActivSchId)
    {
      /* Check whether active chedule is RUN_ONCE and not completed. */
    /* Then the active schedule has to be served again.        */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      if((LINIF_RUN_ONCE == \
        (LinIf_GaaConfiguration[0].pSchTable[LpChannelPtr->ddFirstScheduler \
           + LpChannelRamData->ddActivSchId]).ucScheduleType) &&
           (LpChannelRamData->ddActivSchId !=LpChannelRamData->ddCompltdSchId))
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      {
        /* @Trace: LinIf_SUD_API_289*/
        LucIdToReturn = LpChannelRamData->ddActivSchId;
      }
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      else
      {
        /* Return the ID of the next schedule to be executed */
        LucIdToReturn = LinTp_GetNextScheduleId(
          LucComp, LpChannelPtr, LpChannelRamData);
      } /* else */
    }
  /* The Active Schedule is a 'NULL_SCHEDULE' */
    else /* if(LpChannelRamData->ddActivSchId > LINIF_ZERO) */
    {
  /* There is a schedule request with a valid schedule ID */
      if(LINIF_TWO == LucComp)
      {
        /* @Trace: LinIf_SUD_API_302*/
        LucIdToReturn = *(LpChannelPtr->pSchId);
        LpChannelRamData->ucTempEntryNum = LINIF_ZERO;
      }
    }
  } /* Not a NULL_SCHEDULE */
  /* @Trace: LinIf_SUD_API_303*/
  return(LucIdToReturn);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinIf_ChangeToNullSchedule                            **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to change current schedule to   **
**                      NULL schedule when a NULL schedule is requested from  **
**                      upper layer or when a channel is put to sleep.        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpChannelPtr                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_LinIf_STATUS_PROTECTION                    **
**                      SchM_Exit_LinIf_STATUS_PROTECTION                     **
*******************************************************************************/
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
#if(LINTP_SUPPORT == STD_ON)
FUNC(void, LINIF_CODE) LinIf_ChangeToNullSchedule(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST) LpTpChannelPtr)
#else
FUNC(void, LINIF_CODE) LinIf_ChangeToNullSchedule(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr)
#endif
{
  /* @Trace: SWS_LinIf_00231*/
  /* @Trace: LinIf_SUD_API_304*/
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  #if(LINTP_SUPPORT == STD_ON)
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA)
    LpTpChannelRamData;
  #endif
  /* Get the Channel RAM data */
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  /* Reset the Schedule Request */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  *(LpChannelPtr->pSchId) = LpChannelPtr->ddMaxSchs;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */

  #if(LINTP_SUPPORT == STD_ON)
  if(LinTp_GblInitSts == LINTP_INIT)
  {
    /* @Trace: LinIf_SUD_API_305*/
    LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    /* Check if TP Tx or Rx is ongoing */
    /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    if(LpTpChannelRamData->ucLinTpStatus > LINTP_CHANNEL_IDLE)
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
    {
      /* @Trace: LinIf_SUD_API_306*/
      /* Change the TP channel state to IDLE */
      LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
    }
    /* @Trace: LinIf_SUD_API_307*/
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
  }
  #endif
  /* @Trace: SWS_LinIf_00263*/
  /* @Trace: LinIf_SUD_API_308*/
  /* Set active schedule id equal to zero */
  LpChannelRamData->ddActivSchId = LINIF_NULL_SCHEDULE;
  /* Set Pending, Completed Schedule Ids to Invalid */
  LpChannelRamData->ddPendingId = LpChannelPtr->ddMaxSchs;
  LpChannelRamData->ddCompltdSchId = LpChannelPtr->ddMaxSchs;
  /* Reset the delay counter */
  LpChannelRamData->usDelayCounter = LINIF_ZERO;
  /* Reset the Schedule Entries Left counter */
  LpChannelRamData->ucNoOfEntriesLeft = LINIF_ZERO;
  /* Reset the Schedule entry number */
  LpChannelRamData->ucSchEntryNum = LINIF_ZERO;
  #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
  /* Set Pending Schedule Id of Event Triggered Frames to Invalid */
  LpChannelRamData->ddPendingSchIdEvt = LpChannelPtr->ddMaxSchs;
  /* Reset the Schedule Entries Left counter of Event Triggered Frames */
  LpChannelRamData->ucNoOfEntriesLeftAsEvt = LINIF_ZERO;
  /* Reset the temporary Schedule entry number */
  LpChannelRamData->ucTempEntryNum = LINIF_ZERO;
  /* Reset the Collision Flag status */
  LpChannelRamData->ucCollisionStatusFlag = LINIF_COLLISION_NOT_OCCURRED;
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_AssociatedBinarySearch                          **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to search for a PDUID in list of**
**                      sorted PDUIDs.                                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId                                              **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : LpRetAssociatedFramePtr                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable: LinIf_GpFirstAssociatedFrame,        **
**                                       LinIf_GaaAssociatedFrame             **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      None                                                  **
*******************************************************************************/
#if((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON))
#define LINIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
FUNC(P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST), LINIF_CODE)
                              LinIf_AssociatedBinarySearch(PduIdType LddPduId)
/* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */                              
{
  /* @Trace: SWS_LinIf_00471*/
  /* @Trace: LinIf_SUD_API_309*/
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST)LpAssociatedFramePtr;
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST)LpRetAssociatedFramePtr;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  PduIdType LddCurrPduId;


  /* Redmine 8274: Change Number to Macro */
  uint8 LucSporIdx = LINIF_ZERO;
  /* Initialize return value with null pointer */
  LpRetAssociatedFramePtr = NULL_PTR;
  /* Initialize the sporadic frame pointer with first sporadic frame pointer */
  LpAssociatedFramePtr = &LinIf_GaaAssociatedFrame[LINIF_ZERO];

  /* Get the lower limit of PduId */
  do
  {
    /* @Trace: LinIf_SUD_API_310*/
    /* Get the pointer of Frame */
    LpFramePtr = LpAssociatedFramePtr[LucSporIdx].pAssociatedFrame;

    LddCurrPduId = LpFramePtr->ddLocalHandleId;

    if(LddCurrPduId == LddPduId)
    {
      /* @Trace: LinIf_SUD_API_311*/
      LpRetAssociatedFramePtr = &LpAssociatedFramePtr[LucSporIdx];
      break;
    }
    
    /* @Trace: LinIf_SUD_API_312*/
    LucSporIdx++;
  }while(LucSporIdx < LinIf_GaaConfiguration[0].usNoAssociatedFrm);
  /* @Trace: LinIf_SUD_API_313*/
  /* Return sporadic list frame pointer */
  return (LpRetAssociatedFramePtr);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_AssociatedPendingMask                           **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to search for a PDUID and set   **
**                        the pending mask in list of sorted PDUIDs.          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId, LbCheckPend                                 **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable: LinIf_GaaAssociatedFrame,            **
**                      LinIf_GaaConfiguration[0].usNoAssociatedFrm           **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_LinIf_SPORADIC_STATUS_PROTECTION,          **
**                      SchM_Exit_LinIf_SPORADIC_STATUS_PROTECTION            **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_AssociatedPendingMask(PduIdType LddPduId, \
                                                          boolean LbCheckPend)
{
  /* @Trace: SWS_LinIf_00341*/
  /* @Trace: LinIf_SUD_API_314*/
  #if((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON))
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST)LpAssociatedFramePtr;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  PduIdType LddCurrPduId;

  uint8 LucSporIdx = LINIF_ZERO;

  LpAssociatedFramePtr = &LinIf_GaaAssociatedFrame[LINIF_ZERO];

  do
  {
    /* @Trace: LinIf_SUD_API_315*/
    /* Get the pointer of Frame */
    LpFramePtr = LpAssociatedFramePtr->pAssociatedFrame;
    /* Get Local Handle Id of Associated Frame */
    LddCurrPduId = LpFramePtr->ddLocalHandleId;
    /* Check whether if it is requested PduId for Transmit or not */
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
    if(LddCurrPduId == LddPduId)
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
    {
      /* Check Pendings Request */
      if(LINIF_TRUE == LbCheckPend)
      {
        /* @Trace: LinIf_SUD_API_316*/
        /* Set pending Flag for Requested PduId */
        SchM_Enter_LinIf_SPORADIC_STATUS_PROTECTION();
        *(LpAssociatedFramePtr[(LinIf_UnderlyingType)LucSporIdx].pPendingSts) |=
          LpAssociatedFramePtr[(LinIf_UnderlyingType)LucSporIdx].ucPendStsMask;
        SchM_Exit_LinIf_SPORADIC_STATUS_PROTECTION();
      }
      else
      {
        /* @Trace: LinIf_SUD_API_317*/
        /* Clear pending Flag for Requested PduId */
        SchM_Enter_LinIf_SPORADIC_STATUS_PROTECTION();
        *(LpAssociatedFramePtr[(LinIf_UnderlyingType)LucSporIdx].pPendingSts) &=
            (uint8)(~(LpAssociatedFramePtr[(LinIf_UnderlyingType)LucSporIdx].\
                                                                ucPendStsMask));
        SchM_Exit_LinIf_SPORADIC_STATUS_PROTECTION();
      }
    }

    /* @Trace: LinIf_SUD_API_318*/
    LucSporIdx++;
  }while(LucSporIdx < LinIf_GaaConfiguration[0].usNoAssociatedFrm);
  #else
  LINIF_UNUSED(LddPduId);
  LINIF_UNUSED(LbCheckPend);
  #endif
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinIf_SendFrame                                       **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to the periodic transmission of **
**                      frames                                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LpChannelPtr, LpSchEntry, LddChnlIndex                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : LblStatus                                             **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GpDbTocPtr, LinIf_GaaDriverApis[],              **
**                      LinIf_GaaFixedFrameInfo[],LinIf_GaaDriverApis,        **
**                      LinIf_GaaLtChannelInfo, LinIf_GaaTriggerTransmitFun   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Lin_SendHeader(), PduR_LinIfTriggerTransmit(),        **
**                      Lin_SendResponse(), LinTp_UpdateFrameStatus(),        **
*******************************************************************************/
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
#if(LINTP_SUPPORT == STD_ON)
FUNC(void, LINIF_CODE) LinIf_SendFrame(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  VAR(uint16, LINIF_CONST) LusSchEntry,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelPtr,
  NetworkHandleType LddChnlIndex)
#else
FUNC(void, LINIF_CODE) LinIf_SendFrame(
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  VAR(uint16, LINIF_CONST) LusSchEntry,
  NetworkHandleType LddChnlIndex)
#endif
{
  /* @Trace: LinIf_SUD_API_319*/
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  #if(LINTP_SUPPORT == STD_ON)
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA)
    LpTpChannelRamData;
  P2CONST(LinTp_TxMsg, AUTOMATIC, LINTP_CONST) LpTpTxMsgPtr;
  #endif
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  P2CONST(LinIf_DrvApis, AUTOMATIC, LINIF_CONST) LpDriverApisPtr;
  #endif
  #if(LINIF_SPORADIC_FRAMES == STD_ON)
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST) LpAssociatedFrame;
  uint8 LucAssocFrms;
  uint8 LucAssocCount;
  #endif
  Lin_PduType LddLoPduInfo;
  PduInfoType LddUpPduInfo;
  LinIf_FrameType LddFrameType;
  uint8 LucDrvChannelId;
  uint8 LaaResponseData[LINIF_EIGHT];
  Std_ReturnType LddReturnValue;

  LddUpPduInfo.SduLength = LINIF_EIGHT;
  LddUpPduInfo.SduDataPtr = LaaResponseData;
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  #if(LINTP_SUPPORT == STD_ON)
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  /* Get pointer to Rx Msg structure */
  //LpTpRxMsgPtr = &(LinTp_GaaRxMsg[LpTpChannelPtr->ddTpRxMsgIndex]);
  #endif
  /* Get the frame type */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LddFrameType = \
    LinIf_GaaConfiguration[0].pSchTblEntry[LusSchEntry].pFramePtr->ddFrameType;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* Get frame pointer of the current schedule entry frame */
  LpFramePtr = LinIf_GaaConfiguration[0].pSchTblEntry[LusSchEntry].pFramePtr;
  /* Reset the frame index */
  LpChannelRamData->ucPrevAssociatedFrameIndex = LINIF_MAX_BYTE;
  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  LpDriverApisPtr = \
      &LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].ucDriverIndex];
  #endif
  /* Get the Driver Channel Id */
  LucDrvChannelId = LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId;
  switch(LddFrameType)
  {
    case LINIF_UNCONDITIONAL_FRAME:
    {
      /* @Trace: LinIf_SUD_API_320*/
      /* Copy the header parameters into a local structure */

      LINIF_COPY_HDR_PARAM(LddLoPduInfo, LpFramePtr);
      /* Check if frame is of Transmit type */
      /* polyspace-begin MISRA-C3:10.4 [To investigate:Low] "Value of left and right are appropriate to compare" */
      if(LINIF_FRAMERESPONSE_TX == LddLoPduInfo.Drc)
      /* polyspace-end MISRA-C3:10.4 [To investigate:Low] "Value of left and right are appropriate to compare" */        
      {
        /* @Trace: LinIf_SUD_API_321*/
        /* Get the response data from PDU Router */
        #if (LINIF_CDD_SUPPORT == STD_ON)
        LddReturnValue = \
          (LinIf_GaaTriggerTransmitFun[LpFramePtr->ucFrameIndex])\
            (LinIf_GaaGlobalHandleId[LpFramePtr->ucFrameIndex], &LddUpPduInfo);
        #else
        /* polyspace +3 CERT-C:DCL39-C [Justified:Low] "The other module will access the data in the struct by specific element, so data padding will not affect" */
        LddReturnValue = \
              PduR_LinIfTriggerTransmit(\
                  LinIf_GaaGlobalHandleId[LpFramePtr->ucFrameIndex], \
                                                                &LddUpPduInfo);
        #endif
        if (E_OK == LddReturnValue)
        {
          /* @Trace: LinIf_SUD_API_322*/
          LddLoPduInfo.SduPtr = LddUpPduInfo.SduDataPtr;
          #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
          /* Invoke respective Driver SendHeader */
          (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
          #else
          (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
          #endif
        }
        else
        {
          /* To avoid QAC error */
        }
      }
      else
      {
        /* @Trace: LinIf_SUD_API_323*/
        LddLoPduInfo.SduPtr = LddUpPduInfo.SduDataPtr;
        #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Invoke respective Driver SendHeader */
        (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
        #else
        (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
        #endif
      }
    }
    /* @Trace: LinIf_SUD_API_324*/
    break;
    #if(LINIF_SPORADIC_FRAMES == STD_ON)
    case LINIF_SPORADIC_FRAME:
    {
      /* @Trace: LinIf_SUD_API_325*/
      /* Get No. of Associated Frame in the channel */
      /* polyspace-begin MISRA-C3:10.3 [To investigate:Low] "Value is within acceptable range" */
      LucAssocFrms = (uint8)LpChannelPtr->usNoAssociatedFrm;
      /* polyspace-end MISRA-C3:10.3 [To investigate:Low] "Value is within acceptable range" */
      /* Initialize count variable as LINIF_ZERO */
      LucAssocCount = LINIF_ZERO;
      do
      {
        /* @Trace: LinIf_SUD_API_326*/
        /* Get first Associated Frame Pointer */
        LpAssociatedFrame = &LpChannelPtr->pFistAssociatedFrmPtr[LucAssocCount];
        /* Check if the sporadic frame is pending for transmission */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        /* polyspace-begin MISRA-C3:14.4 [To investigate:Low] "The logic of this condition is Boolean" */
        /* polyspace-begin MISRA-C3:10.1 [To investigate:Low] "Right operand of && return boolean" */
        /* polyspace-begin MISRA-C3:10.4 [To investigate:Low] "Value of left and right operand are Boolean" */
        if((*(LpAssociatedFrame->pPendingSts) & \
          (LpAssociatedFrame->ucPendStsMask)) == \
            (LpAssociatedFrame->ucPendStsMask))
        /* polyspace-end MISRA-C3:10.4 [To investigate:Low] "Value of left and right operand are Boolean" */
        /* polyspace-end MISRA-C3:10.1 [To investigate:Low] "Right operand of && return boolean" */
        /* polyspace-end MISRA-C3:14.4 [To investigate:Low] "The logic of this condition is Boolean" */
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
        {
          /* @Trace: LinIf_SUD_API_327*/
          LpFramePtr = &LpAssociatedFrame->pAssociatedFrame[LucAssocCount];
          /* Update the sporadic frame index */
          LpChannelRamData->ucPrevAssociatedFrameIndex = LucAssocCount;
          /* Set the counter to max value to break the while loop */
          LucAssocCount = (uint8)LucAssocFrms;
          /* Copy the header parameters into a local structure */
          /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
          LINIF_COPY_HDR_PARAM(LddLoPduInfo, LpFramePtr);
          /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
          /* Get the response data from PDU Router */

          #if (LINIF_CDD_SUPPORT == STD_ON)
          LddReturnValue = \
            (LinIf_GaaTriggerTransmitFun[LpFramePtr->ucFrameIndex])
             (LinIf_GaaGlobalHandleId[LpFramePtr->ucFrameIndex], &LddUpPduInfo);
          #else
          LddReturnValue = \
                PduR_LinIfTriggerTransmit(\
                    LinIf_GaaGlobalHandleId[LpFramePtr->ucFrameIndex], \
                                                              &LddUpPduInfo);
          #endif
          if (E_OK == LddReturnValue)
          {
            /* @Trace: LinIf_SUD_API_328*/
            LddLoPduInfo.SduPtr = LddUpPduInfo.SduDataPtr;
            #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
            /* Invoke respective Driver SendHeader */
            (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
            #else
            (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
            #endif
          }
          else
          {
            /* To avoid QAC Error */
          }
        }
        else
        {
          /* @Trace: LinIf_SUD_API_329*/
          LucAssocCount++;
        }
      }while(LucAssocCount < LucAssocFrms);
    }
    /* @Trace: LinIf_SUD_API_330*/
    break;
    #endif
    #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
    case LINIF_EVENT_TRIGGERED_FRAME:
    {
      /* Copy the header parameters into a local structure */
      /* @Trace: LinIf_SUD_API_331*/
      LINIF_COPY_HDR_PARAM(LddLoPduInfo, LpFramePtr);
      LddLoPduInfo.SduPtr = LddUpPduInfo.SduDataPtr;
      #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
      /* Invoke respective Driver SendHeader */
      (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
      #else
      (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
      #endif
    }
    break;
    #endif
    #if(LINTP_SUPPORT == STD_ON)
    case LINIF_MRF_FRAME:
    {
      /* Check if TP transmission is ongoing and buffer is ready */
      if(LpTpChannelRamData->ucLinTpStatus == LINTP_TX_BUSY_BUFF_RDY)
      {
        /* @Trace: LinIf_SUD_API_332*/
        LpFramePtr = &LinIf_GaaFixedFrameInfo[LINIF_ZERO];
        LddLoPduInfo.SduPtr = LpTpChannelRamData->aaLinTpBuffer;
        LpTpChannelRamData->blTpHeaderSent = LINIF_TRUE;
        /* Copy the header parameters into a local structure */
        LINIF_COPY_HDR_PARAM(LddLoPduInfo, LpFramePtr);
        #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Invoke respective Driver SendHeader */
        (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
        #else
        (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
        #endif
        /* get pointer to LinTp Tx structure */
        LpTpTxMsgPtr = &(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId]);
        /* Check if the timer configured is nonzero */
        /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        if(LINIF_ZERO < LpTpTxMsgPtr->usNasTimerCounter)
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
        {
          /* @Trace: LinIf_SUD_API_333*/
          /* Start N_As timer */
          LINTP_TIMER_UPDATE_MACRO(LpTpTxMsgPtr->ucTpTxChannelIndex,
            LINTP_NAS_TIMER, LpTpTxMsgPtr->usNasTimerCounter);
        }
        /* polyspace-end MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        /* Check that if it is CF */
        if(LINIF_ONE < LpTpChannelRamData->ucTpFrameCounter)
        {
          /* @Trace: LinIf_SUD_API_334*/
          /* Stop N_Cs timer */
          LINTP_TIMER_UPDATE_MACRO(LpTpTxMsgPtr->ucTpTxChannelIndex,
            LINTP_NCS_TIMER, LINIF_ZERO);
        }
        /* @Trace: LinIf_SUD_API_335*/
        /* Save the requested SduId*/
        LpTpChannelRamData->ddMRFSduId = LpTpChannelRamData->ddActiveTpPduId;
        /* Save the requested NAD */
        LpTpChannelRamData->ucRequestedNad = LpTpTxMsgPtr->ucTpNad;
      }
      else
      {
        /* @Trace: LinIf_SUD_API_336*/
        LpTpChannelRamData->blTpHeaderSent = LINIF_FALSE;
      }
    }
    /* @Trace: LinIf_SUD_API_337*/
    break;
    case LINIF_SRF_FRAME:
    {
      if(LINIF_TRUE == LpTpChannelRamData->blFirstFrame)
      {
        /* @Trace: LinIf_SUD_API_338*/
        LpTpChannelRamData->blTpHeaderSent = LINIF_TRUE;
        /* Copy the header parameters into a local structure */
        LINIF_COPY_HDR_PARAM(LddLoPduInfo, &LinIf_GaaFixedFrameInfo[LINIF_ONE]);
        LddLoPduInfo.SduPtr = LddUpPduInfo.SduDataPtr;
        #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
        /* Invoke respective Driver SendHeader */
        (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
        #else
        (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
        #endif
      }
    }
    break;
    #endif
    #if (LINIF_FIXEDMRF_FRAMES == STD_ON)
    case LINIF_FIXED_MRF_FRAME:
    {
      /* @Trace: LinIf_SUD_API_339*/
      LpFramePtr = &LinIf_GaaFixedFrameInfo[LINIF_ZERO];

      LddLoPduInfo.SduPtr = (P2VAR(uint8, AUTOMATIC, LINIF_DATA))
         (LpChannelPtr->pFirstFixedMrf + \
            (LinIf_UnderlyingType)(LinIf_GaaConfiguration[0].\
                                      pSchTblEntry[LusSchEntry].ddFrameIndex));

      /* Copy the header parameters into a local structure */
      LINIF_COPY_HDR_PARAM(LddLoPduInfo, LpFramePtr);
      #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
      /* Invoke respective Driver SendHeader */
      (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
      #else
      (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
      #endif
    }
    break;
    #endif
    #if (LINIF_FIXEDSRF_FRAMES == STD_ON)
    case LINIF_FIXED_SRF_FRAME:
    {
      /* @Trace: LinIf_SUD_API_340*/
      LpFramePtr = &LinIf_GaaFixedFrameInfo[LINIF_ONE];
      /* Copy the header parameters into a local structure */
      LINIF_COPY_HDR_PARAM(LddLoPduInfo, LpFramePtr);
      LddLoPduInfo.SduPtr = LddUpPduInfo.SduDataPtr;
      #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
      /* Invoke respective Driver SendHeader */
      (void)LpDriverApisPtr->pLinSendFrame(LucDrvChannelId, &LddLoPduInfo);
      #else
      (void)Lin_SendFrame(LucDrvChannelId, &LddLoPduInfo);
      #endif
    }
    break;
    #endif
    /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
    default:
    {
      /* @Trace: LinIf_SUD_API_341*/
      break;
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
  }
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_ProcessStatusUncond                             **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is process previous status if frametype **
**                      unconditional                                         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId, LpChannelPtr                                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError, Lin_GetStatus,                       **
**                      PduR_LinIfRxIndication,                               **
**                      PduR_LinIfTxConfirmation                              **
*******************************************************************************/
#if (LINIF_MASTER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(void, LINIF_CODE) LinIf_ProcessStatusUncond
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_342*/
  LinIf_SchHandleType LddScheduler;
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA),
    AUTOMATIC, LINIF_DATA) LppRxDataPtr;
  /* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    
  uint16 LusSchEntry;
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpDummyPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  uint8 LucFrameIdx;
  Lin_StatusType LenLinIfStatus;
  PduInfoType LddRxData;
  #if ((LINIF_AS_NOTIFICATION_SUPPORT == STD_ON) || \
                          (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON))
  uint8 LucFrameID;
  #endif
  LpDummyPtr = NULL_PTR;
  LppRxDataPtr = &LpDummyPtr;
  /* Get the pointer to the Channel RAM Data */
  LpChannelRamData = LpChannelPtr->pChannelRamData;

  /* Get the pointer to channel current scheduler */
  LddScheduler = LpChannelPtr->ddFirstScheduler + \
                                                LpChannelRamData->ddActivSchId;

  /* Get the previous scheduler entry pointer */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LusSchEntry = \
    (LinIf_GaaConfiguration[0].pSchTable[LddScheduler].usSchFirstEntry) +
              ((uint16)LpChannelRamData->ucSchEntryNum - (uint16)LINIF_ONE);
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* Get the pointer of Frame */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LpFramePtr = LinIf_GaaConfiguration[0].pSchTblEntry[LusSchEntry].pFramePtr;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* Get Frame Index */
  LucFrameIdx = LpFramePtr->ucFrameIndex;
  #if ((LINIF_AS_NOTIFICATION_SUPPORT == STD_ON) || \
                                    (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON))
  /* Redmine #8274: Change Number to Macro */
  LucFrameID = (uint8)(LpFramePtr->ddPid & LINIF_FRAME_ID_FILTER_MASK);
  #endif

  #if (LINIF_AS_NOTIFICATION_SUPPORT == STD_ON)
   if(LpChannelPtr->pLinASNotiFunc != NULL_PTR)
   {
     /* @Trace: LinIf_SUD_API_343*/
    (LpChannelPtr->pLinASNotiFunc)\
        (LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, \
                (uint8)(LpChannelRamData->ddActivSchId), \
                    (uint8)(LpChannelRamData->ucSchEntryNum),LucFrameID);
   }
  #endif

  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  /* Invoke respective Driver GetStatus function */
  LenLinIfStatus = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDriverIndex].pLinGetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #else
  /* @Trace: LinIf_SUD_API_344*/
  /* Invoke the GetStatus function */
  LenLinIfStatus = \
    Lin_GetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId, \
                                                                LppRxDataPtr);
  #endif

  LddRxData.SduLength = LpFramePtr->ddDl;
  LddRxData.SduDataPtr = *LppRxDataPtr;
  LddRxData.MetaDataPtr = NULL_PTR;
  /* Check if the previous transport frame is of type Tx */
  /* polyspace-begin MISRA-C3:10.4 [To investigate:Low] "Value of left and right are appropriate to compare" */
  if(LINIF_FRAMERESPONSE_TX == LpFramePtr->ddDrc)
  /* polyspace-end MISRA-C3:10.4 [To investigate:Low] "Value of left and right are appropriate to compare" */
  {
    /* Check if the frame is successfully transmitted */
    if(LIN_TX_OK == LenLinIfStatus)
    {
      /* @Trace: LinIf_SUD_API_345*/
      /* Invoke the upper layer confirmation callback */
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaTxConfirmationFun[LucFrameIdx])(\
                                LinIf_GaaGlobalHandleId[LucFrameIdx], E_OK);
      #elif(LINIF_TX_LPDU == STD_ON)
      PduR_LinIfTxConfirmation(LinIf_GaaGlobalHandleId[LucFrameIdx], E_OK);
      #endif
    }
    else if((LIN_TX_BUSY == LenLinIfStatus) || (LIN_TX_ERROR == LenLinIfStatus))
    {
      /* @Trace: LinIf_SUD_API_346*/
      #if (LINIF_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_MAINFUNCTION_SID, LINIF_E_RESPONSE);
      #endif

      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaTxConfirmationFun[LucFrameIdx])\
                              (LinIf_GaaGlobalHandleId[LucFrameIdx], E_NOT_OK);
      #elif(LINIF_TX_LPDU == STD_ON)
      PduR_LinIfTxConfirmation(LinIf_GaaGlobalHandleId[LucFrameIdx], 
                                                                      E_NOT_OK);
      #endif
    }
    else
    {
      
    }
    
    #if (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON)
    /* Error detection is only availabble for unconditional frame
                                       in continually running schedule table */
    if(LINIF_RUN_CONTINUOUS == \
      (LinIf_GaaConfiguration[0].pSchTable[LpChannelPtr->ddFirstScheduler + \
                       LpChannelRamData->ddActivSchId]).ucScheduleType)
    {
      if((LIN_TX_BUSY == LenLinIfStatus) || (LIN_TX_HEADER_ERROR == LenLinIfStatus) || \
                                                   (LIN_TX_ERROR == LenLinIfStatus))
      {
        #if (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON)
        /* call error notification function */
        if(LpChannelPtr->pLinErrNotiFunc != NULL_PTR)
        {
          /* @Trace: LinIf_SUD_API_347*/
          (LpChannelPtr->pLinErrNotiFunc)(\
              LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, \
                  (uint8)LenLinIfStatus, (uint8)(LpChannelRamData->ucSchEntryNum),\
                                                                   LucFrameID);
        }
        #endif
      }
    }
    #endif
    /* @Trace: LinIf_SUD_API_348*/
    LINIF_UNUSED(LddRxData.SduLength);
  }
  /* Check if the previous transport frame is of type Rx */
  /* polyspace-begin MISRA-C3:10.4 [To investigate:Low] "Value of left and right are appropriate to compare" */
  else if(LINIF_FRAMERESPONSE_RX == LpFramePtr->ddDrc)
  /* polyspace-end MISRA-C3:10.4 [To investigate:Low] "Value of left and right are appropriate to compare" */    
  {
    /* Check if the frame is successfully received */
    if(LIN_RX_OK == LenLinIfStatus)
    {
      /* @Trace: LinIf_SUD_API_349*/
      /* Invoke the upper layer confirmation callback */
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaRxIndFun[LucFrameIdx])
                      (LinIf_GaaGlobalHandleId[LucFrameIdx], &LddRxData);
      #elif(LINIF_RX_LPDU == STD_ON)
      /* polyspace +1 CERT-C:DCL39-C [Justified:Low] "The other module will access the data in the struct by specific element, so data padding will not affect" */
      PduR_LinIfRxIndication(LinIf_GaaGlobalHandleId[LucFrameIdx], &LddRxData);
      #endif
    }
    else{
      /* @Trace: LinIf_SUD_API_350*/
      LINIF_UNUSED(LddRxData.SduLength);
    }
    #if (LINIF_DEV_ERROR_DETECT == STD_ON)
    if((LIN_RX_ERROR == LenLinIfStatus) || (LIN_RX_BUSY == LenLinIfStatus) ||
      (LIN_RX_NO_RESPONSE == LenLinIfStatus))
    {
      /* @Trace: LinIf_SUD_API_351*/
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_MAINFUNCTION_SID, LINIF_E_RESPONSE);
    }
    #endif
    #if (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON)
    /* Error detection is only availabble for unconditional frame
                                     in continually running schedule table */
    if(LINIF_RUN_CONTINUOUS == \
      (LinIf_GaaConfiguration[0].pSchTable[LpChannelPtr->ddFirstScheduler + \
                         LpChannelRamData->ddActivSchId]).ucScheduleType)
    {
      if((LIN_RX_BUSY == LenLinIfStatus) || (LIN_RX_NO_RESPONSE == LenLinIfStatus) ||
         (LIN_RX_ERROR == LenLinIfStatus) ||
         #ifdef LIN_17_TIMEOUT_SUPPORT
         (LIN_RX_RESPONSE_TIMEOUT_ERROR = LenLinIfStatus)||
         #endif
         (LIN_TX_HEADER_ERROR == LenLinIfStatus))
      {
        #if (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON)
        /* call error notification function */
        if(LpChannelPtr->pLinErrNotiFunc != NULL_PTR)
        {
          /* @Trace: LinIf_SUD_API_352*/
          (LpChannelPtr->pLinErrNotiFunc)(\
              LinIf_GaaLtChannelInfo[LddChnlIndex].ddComMNwHndlId, \
                (uint8)LenLinIfStatus, (uint8)(LpChannelRamData->ucSchEntryNum), \
                                                                  LucFrameID);
        }
        #endif
      }
    }
    #endif
  }
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
  else /* the previous transport frame is of type Slave to Slave */
  {
    /* Avoid QAC */
  }
  /* @Trace: LinIf_SUD_API_353*/
  /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF_V2" */
  LINIF_UNUSED(LucFrameIdx);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_ProcessStatusSporadic                           **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is process previous status if frametype **
**                      Sporadic                                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId, LpChannelPtr                                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaDriverApis, LinIf_GaaLtChannelInfo,          **
**                      LinIf_GaaTxConfirmationFun,                           **
**                      SchM_Enter_LinIf_SPORADIC_STATUS_PROTECTION           **
**                      SchM_Exit_LinIf_SPORADIC_STATUS_PROTECTION            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError, Lin_GetStatus,                       **
**                      PduR_LinIfTxConfirmation                              **
*******************************************************************************/
#if(LINIF_SPORADIC_FRAMES == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_ProcessStatusSporadic
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_354*/
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA),
    AUTOMATIC, LINIF_DATA) LppRxDataPtr;
  /* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    
  #if (LINIF_CDD_SUPPORT == STD_ON)
  LinIf_SchHandleType LddScheduler;
  uint16 LusSchEntry;
  #endif
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpDummyPtr;
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST) LpAssociatedFramePtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  uint8 LucFrameIdx;
  Lin_StatusType LenLinIfStatus;
  LpDummyPtr = NULL_PTR;
  LppRxDataPtr = &LpDummyPtr;
  /* Get the pointer to the Channel RAM Data */
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  #if (LINIF_CDD_SUPPORT == STD_ON)
  /* Get the pointer to channel current scheduler */
  LddScheduler = \
              LpChannelPtr->ddFirstScheduler + LpChannelRamData->ddActivSchId;
  #endif
  /* Get the previous scheduler entry pointer */
  #if (LINIF_CDD_SUPPORT == STD_ON)
  LusSchEntry = \
      (LinIf_GaaConfiguration[0].pSchTable[LddScheduler].usSchFirstEntry) +
              ((uint16)LpChannelRamData->ucSchEntryNum - (uint16)LINIF_ONE);
  #endif
  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  /* Invoke respective Driver GetStatus function */
  LenLinIfStatus = LinIf_GaaDriverApis [LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDriverIndex].pLinGetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #else
  /* Invoke the GetStatus function */
  LenLinIfStatus = Lin_GetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #endif
  /* Check if any sporadic frame was transmitted */
  if(LINIF_MAX_BYTE != LpChannelRamData->ucPrevAssociatedFrameIndex)
  {
    /* @Trace: LinIf_SUD_API_355*/
    /* Get Pending Associated Frame Pointer */
    /* polyspace-begin MISRA-C3:18.4 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
    LpAssociatedFramePtr = &LpChannelPtr->pFistAssociatedFrmPtr[LpChannelRamData->ucPrevAssociatedFrameIndex];
    /* polyspace-end MISRA-C3:18.4 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
    /* Get the pointer of Frame */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LpFramePtr = LpAssociatedFramePtr->pAssociatedFrame;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    /* Get Frame index */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LucFrameIdx = LpFramePtr->ucFrameIndex;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    /* Check if the frame is successfully transmitted */
    if(LIN_TX_OK == LenLinIfStatus)
    {
      /* @Trace: LinIf_SUD_API_356*/
      /* Invoke the upper layer confirmation callback */
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaTxConfirmationFun[LucFrameIdx])\
                            (LinIf_GaaGlobalHandleId[LucFrameIdx], E_OK);
      #elif(LINIF_TX_LPDU == STD_ON)
      PduR_LinIfTxConfirmation(LinIf_GaaGlobalHandleId[LucFrameIdx], E_OK);
      #endif

      LinIf_AssociatedPendingMask(\
                                LpFramePtr->ddLocalHandleId, LINIF_FALSE);
    } /* end if(LenLinIfStatus == LIN_TX_OK) */
    else if((LIN_TX_BUSY == LenLinIfStatus) || (LIN_TX_ERROR == LenLinIfStatus))
    {
      /* @Trace: LinIf_SUD_API_357*/
      #if (LINIF_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINIF_MAINFUNCTION_SID, LINIF_E_RESPONSE);
      #endif
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaTxConfirmationFun[LucFrameIdx])\
                            (LinIf_GaaGlobalHandleId[LucFrameIdx], E_NOT_OK);
      #elif(LINIF_TX_LPDU == STD_ON)
      PduR_LinIfTxConfirmation(LinIf_GaaGlobalHandleId[LucFrameIdx], 
                                                                    E_NOT_OK);
      #endif
    }
    else
    {
      /*Avoid QAC*/
    }
  }
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_ProcessStatusEventTrig                          **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is process previous status if frametype **
**                      is Event triggered                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId, LpChannelPtr                                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaDriverApis, LinIf_GaaLtChannelInfo,          **
**                      LinIf_GaaRxIndFun                                     **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Lin_GetStatus, PduR_LinIfRxIndication                 **
**                                                                            **
*******************************************************************************/
#if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_ProcessStatusEventTrig
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_358*/
  LinIf_SchHandleType LddScheduler;
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA),
    AUTOMATIC, LINIF_DATA) LppRxDataPtr;
  uint16 LusSchEntry;
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpDummyPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) LpFramePtr;
  uint8 LucFrameIdx;
  Lin_StatusType LenLinIfStatus;
  PduInfoType LddRxData;
  LpDummyPtr = NULL_PTR;
  LppRxDataPtr = &LpDummyPtr;
  /* Get the pointer to the Channel RAM Data */
  LpChannelRamData = LpChannelPtr->pChannelRamData;
  /* Get the pointer to channel current scheduler */
  LddScheduler = \
            LpChannelPtr->ddFirstScheduler + LpChannelRamData->ddActivSchId;
  /* Get the previous scheduler entry pointer */
  LusSchEntry = \
    (LinIf_GaaConfiguration[0].pSchTable[LddScheduler].usSchFirstEntry) +
              ((uint16)LpChannelRamData->ucSchEntryNum - (uint16)LINIF_ONE);
  /* Get the pointer of Frame */
  LpFramePtr = LinIf_GaaConfiguration[0].pSchTblEntry[LusSchEntry].pFramePtr;
  /* Get Frame Index */
  LucFrameIdx = LpFramePtr->ucFrameIndex;
  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  /* Invoke respective Driver GetStatus function */
  LenLinIfStatus = LinIf_GaaDriverApis [LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDriverIndex].pLinGetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #else
  /* Invoke the GetStatus function */
  LenLinIfStatus = Lin_GetStatus(\
          LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId, LppRxDataPtr);
  #endif

  LddRxData.SduLength = \
          LinIf_GaaConfiguration[0].pSchTblEntry[LusSchEntry].pFramePtr->ddDl;
  LddRxData.SduDataPtr = *LppRxDataPtr;
  /* Check if the frame is successfully received */
  if(LIN_RX_OK == LenLinIfStatus)
  {
    /* @Trace: LinIf_SUD_API_359*/
    /* Invoke the upper layer confirmation callback */
    #if (LINIF_CDD_SUPPORT == STD_ON)
    (LinIf_GaaRxIndFun[LucFrameIdx])
                    (LinIf_GaaGlobalHandleId[LucFrameIdx], &LddRxData);
    #elif(LINIF_RX_LPDU == STD_ON)
    PduR_LinIfRxIndication(LinIf_GaaGlobalHandleId[LucFrameIdx], &LddRxData);
    #endif
  } /* end if(LenLinIfStatus == LIN_RX_OK) */
  else{
    /* @Trace: LinIf_SUD_API_360*/
    LINIF_UNUSED(LddRxData.SduLength);
  }
  if((LIN_RX_ERROR == LenLinIfStatus) || (LIN_RX_BUSY == LenLinIfStatus))
  {
    /* @Trace: LinIf_SUD_API_361*/
    /* Update the Collision status flag in ChannelRam data */
    LpChannelRamData->ucCollisionStatusFlag = LINIF_COLLISION_OCCURRED;
    LpChannelRamData->ddPendingSchIdEvt = LpChannelRamData->ddActivSchId;
  }
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_ProcessStatusMRF                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is process previous status if frametype **
**                      is MRF                                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId, LpChannelPtr                                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaDriverApis, LinIf_GaaLtChannelInfo,          **
**                      LinTp_GaaTxMsg                                        **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Lin_GetStatus, BswM_LinTp_RequestMode                 **
**                      PduR_LinTpTxConfirmation, LinTp_UpdateFrameStatus     **
**                      SchM_Enter_LinIf_STATUS_PROTECTION,                   **
**                      SchM_Exit_LinIf_STATUS_PROTECTION                     **
*******************************************************************************/
#if(LINTP_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_ProcessStatusMRF
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr, P2CONST(LinTp_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpTpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_362*/
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA),
    AUTOMATIC, LINIF_DATA) LppRxDataPtr;
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpDummyPtr;
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData;
  P2CONST(LinTp_TxMsg, AUTOMATIC, LINTP_CONST) LpTpTxMsgPtr;
  Lin_StatusType LenLinIfStatus;
  LpDummyPtr = NULL_PTR;
  LppRxDataPtr = &LpDummyPtr;
  /* Get the pointer to the Tp Channel RAM Data */
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  LINIF_UNUSED_PTR(LpChannelPtr);
  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  /* Invoke respective Driver GetStatus function */
  LenLinIfStatus = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo
    [LddChnlIndex].ucDriverIndex].pLinGetStatus
    (LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId, LppRxDataPtr);
  #else
  /* Invoke the GetStatus function */
  LenLinIfStatus = Lin_GetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #endif

  if((LIN_TX_OK == LenLinIfStatus) && (LINTP_TX_BUSY_BUFF_ERROR == LpTpChannelRamData->ucLinTpStatus))
  {
    /* @Trace: LinIf_SUD_API_370*/
	LpTpChannelRamData->blTpHeaderSent = LINIF_TRUE;
  }

  /* Check if any ongoing Tp Tx activity is there for the channel */
  if(LINIF_TRUE == LpTpChannelRamData->blTpHeaderSent)
  {
    /* @Trace: LinIf_SUD_API_363*/
    LinTp_UpdateFrameStatus(LpTpChannelRamData);
    /* Check if any Tx errors occurred for previous transmission */
    if((LIN_TX_ERROR == LenLinIfStatus) || (LIN_TX_HEADER_ERROR == LenLinIfStatus))
    {
      /* @Trace: LinIf_SUD_API_364*/
      /* Invoke the upper layer confirmation callback */
      PduR_LinTpTxConfirmation(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
                                                            E_NOT_OK);
      #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
      /* Invoke BswM with requested schedule mode */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
      if(((LpTpChannelPtr->ucLinTpChannelStatus) & LINTP_DIAG_SELECT) ==
        LINTP_DIAG_SELECT)
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
      {
        /* @Trace: LinIf_SUD_API_365*/
        /* Invoke BswM with LINTP_APPLICATIVE_SCHEDULE */
        BswM_LinTp_RequestMode(LinIf_GaaLtChannelInfo[LddChnlIndex].
          ddComMNwHndlId, LINTP_APPLICATIVE_SCHEDULE);
      }
      #endif
      /* @Trace: LinIf_SUD_API_366*/
      /* Enter protection area */
      SchM_Enter_LinIf_STATUS_PROTECTION();
      /* Clear the ongoing transmission */
      LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
      /* Exit protection area */
      SchM_Exit_LinIf_STATUS_PROTECTION();
    }
    else if(LIN_TX_OK == LenLinIfStatus)
    {
      /* Check if complete Tp message is transmitted */
      if(LINIF_MAX_BYTE == LpTpChannelRamData->ucTpFrameCounter)
      {
        /* @Trace: LinIf_SUD_API_368*/
        /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
        /* Invoke the upper layer confirmation callback */
        PduR_LinTpTxConfirmation(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
                                                                  NTFRSLT_OK);
        /* Clear the ongoing transmission as Tx is completed */
        LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
        /* Call the function to switch the mode and stop the
         * ongoing transmission
         */
        #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
        /* Invoke BswM with requested schedule mode */
        /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
        if(((LpTpChannelPtr->ucLinTpChannelStatus) & LINTP_DIAG_SELECT) ==
            LINTP_DIAG_SELECT)
        /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
         {
           /* @Trace: LinIf_SUD_API_369*/
           BswM_LinTp_RequestMode(LinIf_GaaLtChannelInfo
             [LddChnlIndex].ddComMNwHndlId, LINTP_DIAG_RESPONSE);
         }
        #endif
      } /* if(LpTpChannelRamData->ucTpFrameCounter == LINIF_MAX_BYTE) */
      /* Check it is not the last frame*/
      else
      {
        /* @Trace: LinIf_SUD_API_371*/
        /* get pointer to LInTp Tx structure */
        LpTpTxMsgPtr = &(LinTp_GaaTxMsg
          [LpTpChannelRamData->ddActiveTpPduId]);
        /* Check if the timer configured is nonzero */
        /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        if(LINIF_ZERO < LpTpTxMsgPtr->usNcsTimerCounter)
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
        {
          /* @Trace: LinIf_SUD_API_372*/
          /* Start N_Cs timer */
          LINTP_TIMER_UPDATE_MACRO(LpTpTxMsgPtr->ucTpTxChannelIndex,
            LINTP_NCS_TIMER, LpTpTxMsgPtr->usNcsTimerCounter);
        }
        /* polyspace-end MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        /* @Trace: LinIf_SUD_API_373*/
        /* Stop N_As timer */
        LINTP_TIMER_UPDATE_MACRO(LpTpTxMsgPtr->ucTpTxChannelIndex,
          LINTP_NAS_TIMER, LINTP_ZERO);
      }
    } /* If no error occurs*/
    else
    {
      /* @Trace: LinIf_SUD_API_374*/
      LpTpChannelRamData->ucLinTpStatus = LINTP_TX_BUSY_BUFF_ERROR;
    }
  } /* Header was sent in the previous MainFunction call */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinIf_ProcessStatusSRF                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is process previous status if frametype **
**                      is MRF                                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Re-entrant                                            **
**                                                                            **
** Input Parameters   : LddPduId, LpChannelPtr                                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaDriverApis, LinIf_GaaLtChannelInfo,          **
**                      LinTp_GaaRxMsg                                        **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      LinTp_CheckForCfRxMsg, Lin_GetStatus,                 **
**                      PduR_LinTpRxIndication, LinTp_CheckForNewRxMsg        **
**                      SchM_Enter_LinIf_STATUS_PROTECTION,                   **
**                      SchM_Exit_LinIf_STATUS_PROTECTION,                    **
**                      BswM_LinTp_RequestMode                                **
*******************************************************************************/
#if(LINTP_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_ProcessStatusSRF
  (NetworkHandleType LddChnlIndex, P2CONST(LinIf_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpChannelPtr, P2CONST(LinTp_ChannelInfo, AUTOMATIC,
  LINIF_CONST) LpTpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_375*/
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA),
    AUTOMATIC, LINIF_DATA) LppRxDataPtr;
  /* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpDummyPtr;
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData;
  P2CONST(LinTp_RxMsg, AUTOMATIC, LINTP_CONST) LpTpRxMsgPtr;
  Lin_StatusType LenLinIfStatus;
  LpDummyPtr = NULL_PTR;
  LppRxDataPtr = &LpDummyPtr;
  /* Get the pointer to the Tp Channel RAM Data */
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  /* Invoke respective Driver GetStatus function */
  LenLinIfStatus = LinIf_GaaDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDriverIndex].pLinGetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #else
  /* Invoke the GetStatus function */
  LenLinIfStatus = Lin_GetStatus(LinIf_GaaLtChannelInfo[LddChnlIndex].
    ucDrvChannelId, LppRxDataPtr);
  #endif
  /* Check if the SRF header was transmitted */
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
  if(LINIF_TRUE == LpTpChannelRamData->blTpHeaderSent)
  /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
  {
    /* Check if a Tp message is received */
    if(LIN_RX_OK == LenLinIfStatus)
    {
      /* Check that it is CF */
      if(LINIF_ONE < LpTpChannelRamData->ucTpFrameCounter)
      {
        /* @Trace: LinIf_SUD_API_376*/
        /* get pointer to LInTp Tx structure */
        LpTpRxMsgPtr = &(LinTp_GaaRxMsg[LpTpChannelRamData->ddActiveTpPduId]);
        /* Stop N_Cr timer */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        LINTP_TIMER_UPDATE_MACRO(LpTpRxMsgPtr->ucTpRxChannelIndex,
          LINTP_NCR_TIMER, LINTP_ZERO);
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      }
      /* Check that it is not the last CF */
      if(LINIF_MAX_BYTE != LpTpChannelRamData->ucTpFrameCounter)
      {
        /* @Trace: LinIf_SUD_API_377*/
        /* get pointer to LInTp Tx structure */
        LpTpRxMsgPtr = &(LinTp_GaaRxMsg[LpTpChannelRamData->ddActiveTpPduId]);
        /* Check if the timer configured is nonzero */
        /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        if(LINIF_ONE < LpTpRxMsgPtr->usNcrTimerCounter)
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
        {
          /* @Trace: LinIf_SUD_API_378*/
          /* Start N_Cr timer */
          LINTP_TIMER_UPDATE_MACRO(LpTpRxMsgPtr->ucTpRxChannelIndex,
            LINTP_NCR_TIMER, LpTpRxMsgPtr->usNcrTimerCounter);
        }
        /* polyspace-end MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
      }
      /* Check if the Tp Rx is starting now */
      if(LpTpChannelRamData->ucLinTpStatus == LINTP_CHANNEL_IDLE)
      {
        /* @Trace: LinIf_SUD_API_379*/
        /* Invoke internal function that if New Tp message is
         * received */
        LinTp_CheckForNewRxMsg((*LppRxDataPtr), LpTpChannelPtr);
      }
      /* Check if the Tp Rx is starting now */
      else /* Receive the continuous frame */
      {
        if(LINIF_ZERO == LpTpChannelRamData->usTpByteCounter)
        {
          /* @Trace: LinIf_SUD_API_380*/
          /* Enter protection area */
          SchM_Enter_LinIf_STATUS_PROTECTION();
          LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
          /* Exit protection area */
          SchM_Exit_LinIf_STATUS_PROTECTION();
          /* Invoke Upper Layer Rx Indication with NTFRSLT_E_OK */
          PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
            NTFRSLT_OK);
           /* Reset first frame to TRUE */
          LpTpChannelRamData->blFirstFrame = LINIF_TRUE;
          #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
          /* Invoke BswM with requested schedule mode */
          /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
          if(((LpTpChannelPtr->ucLinTpChannelStatus) & LINTP_DIAG_SELECT) ==
            LINTP_DIAG_SELECT)
          /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
          {
            /* @Trace: LinIf_SUD_API_381*/
            /* Invoke BswM_LinTp_RequestMode with LINTP_APPLICATIVE_SCHEDULE */
            BswM_LinTp_RequestMode(LinIf_GaaLtChannelInfo
              [LddChnlIndex].ddComMNwHndlId, LINTP_APPLICATIVE_SCHEDULE);
          }
          #endif
        }
        else
        {
          /* @Trace: LinIf_SUD_API_382*/
          LinTp_CheckForCfRxMsg((*LppRxDataPtr), LpTpChannelPtr);
        }
      }
    }/* Check if a Tp message is received */
    else if(LIN_RX_ERROR == LenLinIfStatus)
    {
      /* @Trace: LinIf_SUD_API_383*/
      /* Invoke Upper Layer Rx Indication with NTFRSLT_E_NOT_OK */
      PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_NOT_OK);
    }else if(LIN_RX_NO_RESPONSE == LenLinIfStatus)
    {
      /* @Trace: LinIf_SUD_API_384*/
      /* Enter protection area */
      SchM_Enter_LinIf_STATUS_PROTECTION();
      LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
      /* Exit protection area */
      SchM_Exit_LinIf_STATUS_PROTECTION();
    }
    else
    {
      /* To avoid QAC warning */
    }
  } /* if(LpTpChannelRamData->blTpHeaderSent == LINIF_TRUE) */
  /* @Trace: LinIf_SUD_API_385*/
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
  LINIF_UNUSED_PTR(LpChannelPtr);
  /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinTp_MainFunc                                        **
**                                                                            **
** Service ID         : 0x80                                                  **
**                                                                            **
** Description        : This function is the main processing function for     **
**                      LinTp. It will be invoked by LinIf_MainFunction.      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
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
**                      Det_ReportError(), SchM_Enter_LinIf(),                **
**                      SchM_Exit_LinIf(), LinTp_RequestNewRxBuff(),          **
**                      LinTp_CopyDataTxBuff(), LinIf_SleepReqMainFunction(), **
**                      LinIf_ChangeSchedule(), LinIf_ProcessPrevStatus(),    **
**                      LinIf_ChangeToNullSchedule(),                         **
**                      Lin_SendHeader(), Lin_SendResponse(),                 **
**                      LinSM_WakeupConfirmation(),                           **
**                      Cdd_WakeupConfirmation()                              **
*******************************************************************************/
#if(LINTP_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinTp_MainFunc (NetworkHandleType LddChnlIndex)
{
  /* @Trace: LinIf_SUD_API_386*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA)LpTpChannelRamData;
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST)LpTpChannelInfo;
  uint8 LucNewBuffReqFlag;
  /* Set the default value */
  LucNewBuffReqFlag = LINIF_ZERO;

  LpTpChannelInfo = &(LinTp_GpFirstChannel[LddChnlIndex]);

  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LpTpChannelRamData = LpTpChannelInfo->pLinTpChannelRamData;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */

  /* P2 timer handling */
  LucNewBuffReqFlag |= LinTp_HandleP2Timer(LpTpChannelRamData);

  /* N_Cs timer handling */
  LucNewBuffReqFlag |= LinTp_HandleNCsTimer(
    LddChnlIndex, LpTpChannelRamData, LpTpChannelInfo);

  /* N_Cr timer handling  */
  LucNewBuffReqFlag |= LinTp_HandleNCrTimer(
    LddChnlIndex, LpTpChannelRamData, LpTpChannelInfo);

  /* N_As timer handling */
  LucNewBuffReqFlag |= LinTp_HandleNAsTimer(
    LddChnlIndex, LpTpChannelRamData, LpTpChannelInfo);

  /* If the buffer request flag is True */
  if(LINIF_ONE == LucNewBuffReqFlag)
  {
    if(LpTpChannelRamData->ucLinTpStatus == LINTP_RX_BUSY_BUFF_NOT_RDY)
    {
      /* @Trace: LinIf_SUD_API_399*/
      LinTp_RequestNewRxBuff(LpTpChannelInfo);
    }
    else if(LpTpChannelRamData->ucLinTpStatus == LINTP_TX_BUSY_BUFF_NOT_RDY)
    {
      /* @Trace: LinIf_SUD_API_400*/
      LinTp_CopyDataTxBuff(LpTpChannelInfo);
    }
    else
    {
      /* Avoid QAC */
    }
  } /* @ end if(LucNewBuffReqFlag == LINIF_ONE) */
  else
  {
    /* @Trace: LinIf_SUD_API_401*/
    /* Notify the upper layer by calling the function
     * PduR_LinTpRxIndication with the result NTFRSLT_E_NOT_OK */
    PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
    NTFRSLT_E_NOT_OK);

    /* Call the function to switch the mode and stop the ongoing
     *  transmission */
    LinIf_SwitchScheduleMode(LpTpChannelInfo, LINTP_APPLICATIVE_SCHEDULE);
  }

}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name      : LinTp_TransmitDetCheck                                **
**                                                                            **
** Service ID         : 0x80                                                  **
**                                                                            **
** Description        : This function is to check for Det errors in           **
**                      LinTp_Transmit                                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
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
**                      LinIf_GblInitSts, LinTp_GblInitSts                    **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
#if ((LINTP_SUPPORT == STD_ON) && (LINIF_DEV_ERROR_DETECT == STD_ON))
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinTp_TransmitDetCheck(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, LINTP_APPL_CONST) PduInfoPtr)
{
  /* @Trace: LinIf_SUD_API_402*/
  Std_ReturnType LddReturnValue;
  /* Set the return value to default */
  LddReturnValue = E_NOT_OK;

  /* Check if the LinIf or LinTp is not initialized */
  if((LINIF_UNINIT == LinIf_GblInitSts) || (LINTP_UNINIT == LinTp_GblInitSts))
  {
    /* @Trace: LinIf_SUD_API_403*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_TRANSMIT_SID, LINIF_E_UNINIT);
  }
  /* Check if the PduId is out of range */
  else if(TxPduId >= LinIf_Max_Tx_Sdu)
  {
    /* @Trace: LinIf_SUD_API_404*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_TRANSMIT_SID, LINIF_E_PARAMETER);
  }
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
  /* Check if the input PduInfoPtr has an invalid value */
  else if( (PduInfoPtr == NULL_PTR)
      || (PduInfoPtr->SduDataPtr == NULL_PTR)
      || (LINIF_MAX_TX_LIMIT < PduInfoPtr->SduLength))
  {
    /* @Trace: LinIf_SUD_API_405*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_TRANSMIT_SID, LINIF_E_PARAM_POINTER);
  }
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
  else
  {
    /* @Trace: LinIf_SUD_API_406*/
    LddReturnValue = E_OK;
  }

  /* @Trace: LinIf_SUD_API_407*/
  return(LddReturnValue);
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinIf_GetFranmeIndex                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function is to get Frame index for               **
**                      the request Frame with a specifiec ddPduId            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
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
**                      LinIf_GaaConfiguration                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      None                                                  **
*******************************************************************************/
#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, LINIF_CODE) LinIf_GetFrameIndex
                          (NetworkHandleType Channel, Lin_FramePidType ddPId)
{
  /* @Trace: LinIf_SUD_API_408*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  NetworkHandleType LddChnlIndex;
  uint8 LucLenOfPidTable;
  uint8 LucFrameCount;
  uint8 LucFrameIdx;

  LucFrameIdx = LINIF_ZERO;
  /* Get Channel Index */
  LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
  /* Get Channel Pointer Variable */
  LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex];
  /* Get No of schedule entry in the current Channel */
  LucLenOfPidTable = LpChannelPtr->ucLenOfPidTable;
  /* Get the pointer to Frame RAM data */
  LpFrameRamData = LpChannelPtr->pFrameRamData;
  /* Find which schedule entry have the Pid value equal as ddPId */
  /* @Trace: LinIf_SUD_API_409*/
  /* @Trace: LinIf_SUD_API_410*/
  for (LucFrameCount = LINIF_ZERO; LucFrameCount < LucLenOfPidTable; \
                                                            LucFrameCount++)
  {
    /* Check if Pid value of checking Frame equal as ddPId*/
    if (LpFrameRamData->pPidTable[LucFrameCount] == ddPId)
    {
      /* @Trace: LinIf_SUD_API_411*/
      LucFrameIdx = LucFrameCount;
      LucFrameCount = LucLenOfPidTable;
    }
  }
  /* @Trace: LinIf_SUD_API_412*/
  return LucFrameIdx;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif


/* TODO: VinhHTQ re-structure */
#if (STD_ON == LINIF_MASTER_SUPPORT)
/*******************************************************************************
** Function Name      : LinIf_ProcessWakeUpConfirm                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function process wakeup confirm in               **
**                      LinIf_MainFunction                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
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
**                      LinIf_GaaConfiguration                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      None                                                  **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"

FUNC(void, LINIF_CODE) LinIf_ProcessWakeUpConfirm(NetworkHandleType Channel)
{
  /* @Trace: LinIf_SUD_API_413*/
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;

  LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[Channel];
  LpChannelRamData = LpChannelPtr->pChannelRamData;

  SchM_Enter_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
  if (LINIF_ZERO < LpChannelRamData->ucWakeupConfirmCount)
  {
    /* @Trace: LinIf_SUD_API_414*/
    LpChannelRamData->ucWakeupConfirmCount--;
    if (LINIF_ZERO == LpChannelRamData->ucWakeupConfirmCount)
    {
      /* @Trace: LinIf_SUD_API_415*/
      SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
      /* Invoke Wake-up confirmation for Upper Layer */
      #if (STD_ON == LINIF_CDD_SUPPORT)
      (LinIf_GaaWakeupConfFun [Channel])(
          LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
          (E_OK == LpChannelRamData->ucWakeupSignalSent));
      #else
      LinSM_WakeupConfirmation(
          LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
          (E_OK == LpChannelRamData->ucWakeupSignalSent));
      #endif
    }
    else
    {
      /* @Trace: LinIf_SUD_API_416*/
      SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
    }
  }
  else
  {
    /* @Trace: LinIf_SUD_API_417*/
    SchM_Exit_LinIf_WAKEUP_CONFCOUNT_PROTECTION();
  }
}

#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinIf_ProcessScheduleChanging                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function process schedule changging in           **
**                      LinIf_MainFunction                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
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
**                      LinIf_GaaConfiguration                                **
**                      LinIf_GaaLtChannelInfo                                **
**                      LinIf_GaaSchReqConfFun                                **
**                      LinIf_GaaResSchTableIdx                               **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      LinIf_CheckForIdToServe                               **
**                      LinSM_ScheduleRequestConfirmation                     **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"

FUNC(void, LINIF_CODE) LinIf_ProcessScheduleChanging(NetworkHandleType Channel, LinIf_SchHandleType* LddScheduler)
{
  /* @Trace: LinIf_SUD_API_418*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  P2CONST(LinIf_Scheduler, AUTOMATIC, LINIF_DATA) LpScheduler;
#if (STD_ON == LINTP_SUPPORT)
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo;
#endif
  uint8 LucReqSchId_SporFrms;

  /* Get the channel pointer */
  LpChannelPtr = &LinIf_GaaConfiguration[0].pChannelInfor[Channel];
  /* Get the channel Ram Data pointer */
  LpChannelRamData = LpChannelPtr->pChannelRamData;
#if (STD_ON == LINTP_SUPPORT)
  LpTpChannelInfo = &(LinTp_GaaChannelInfo[Channel]);
#endif

  /* Get current scheduler index */
  /*LddScheduler = LpChannelPtr->ddFirstScheduler + \
                                      LpChannelRamData->ddActivSchId;*/

  /* Get current scheduler table */
  LpScheduler = &LinIf_GaaConfiguration[0].pSchTable[(*LddScheduler)];

#if (STD_ON == LINIF_EVTTRIGGER_FRAMES)
  if (LpChannelRamData->ucCollisionStatusFlag >=
  LINIF_COLLISION_OCCURRED)
  {

    if (((*(LpChannelPtr->pSchId) == LpChannelRamData->ddActivSchId)
        || (*(LpChannelPtr->pSchId) == LpChannelRamData->ddPendingId)
        || (*(LpChannelPtr->pSchId) == LpChannelRamData->ddPendingSchIdEvt))
        && (*(LpChannelPtr->pSchId) < LpChannelPtr->ddMaxSchs))
    {
      /* @Trace: LinIf_SUD_API_419*/
      #if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaSchReqConfFun[Channel])
      (LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
          *(LpChannelPtr->pSchId));
      #else
      LinSM_ScheduleRequestConfirmation(
          LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
          *(LpChannelPtr->pSchId));
      #endif
      /* Making the particular Memory pointing to Schedule Id
        * to Invalid value.
        */
      *(LpChannelPtr->pSchId) = LpChannelPtr->ddMaxSchs;
    } /* end if(((*(LpChannelPtr->pSchId)... */
    if (LINIF_COLLISION_OCCURRED == LpChannelRamData->ucCollisionStatusFlag)
    {
      /* @Trace: LinIf_SUD_API_420*/
      uint16 LusEntryIdx;
      /* Get the pointer to scheduler entry */
      LusEntryIdx = (LpScheduler->usSchFirstEntry)
          + ((uint16) LpChannelRamData->ucSchEntryNum - (uint16) LINIF_ONE);
      /* Get resolve schedule table index */
      LucReqSchId_SporFrms = LinIf_GaaResSchTableIdx[LusEntryIdx];
      /* Set Collision status as Resolved */
      LpChannelRamData->ucCollisionStatusFlag =
      LINIF_COLLISION_RESOLVED;
      /* Store previous Schedule Index before Collision occurs */
      LpChannelRamData->ucNoOfEntriesLeftAsEvt =
          LpChannelRamData->ucSchEntryNum;
    } /* if(LpChannelRamData->ucCollisionStatusFlag == LINIF_ONE) */
    else
    {
      /* @Trace: LinIf_SUD_API_421*/
      LucReqSchId_SporFrms = LpChannelRamData->ddActivSchId;
    }
  } /* if(LpChannelRamData->ucCollisionStatusFlag >= LINIF_ONE) */
  else
#endif /* (STD_ON == LINIF_EVTTRIGGER_FRAMES) */
  {
    /* @Trace: LinIf_SUD_API_422*/
    LucReqSchId_SporFrms = LinIf_CheckForIdToServe(LpChannelPtr, Channel);
  }
  /* Check if end of the schedule is reached */

  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  if (LpChannelRamData->ucSchEntryNum == LpScheduler->ucNoOfSchEntries)
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  {
    /* @Trace: LinIf_SUD_API_423*/
    /* Reset the schedule entry index */
    LpChannelRamData->ucSchEntryNum = LINIF_ZERO;
    LpChannelRamData->ddCompltdSchId = LpChannelPtr->ddMaxSchs;
  }

  /* For serving the schedule request that has a same
    ID with the Active Schedule,  */
  /* Add a condition'(LucReqSchId_SporFrms == *(LpChannelPtr->pSchId)'*/
  if ((LpChannelRamData->ddActivSchId != LucReqSchId_SporFrms)
      || (LucReqSchId_SporFrms == *(LpChannelPtr->pSchId)))
  {
    /* Check if requested is schedule is not a NULL schedule */
    /* Requested schedule entry is not NULL */

    /* polyspace-begin MISRA-C3:10.1 [To investigate:Low] "Right operand of && return boolean" */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    if ((LINIF_NULL_SCHEDULE != LucReqSchId_SporFrms)
        && ((LinIf_GaaConfiguration[0].pSchTable[(LpChannelPtr->ddFirstScheduler + LucReqSchId_SporFrms)]).ucNoOfSchEntries != LINIF_ZERO))
   
    /* polyspace-end MISRA-C3:10.1 [To investigate:Low] "Right operand of && return boolean" */
    {

      /* @Trace: LinIf_SUD_API_424*/
      LpChannelRamData->ddActivSchId = LucReqSchId_SporFrms;
      /* Change the schedule table */
      LinIf_ChangeSchedule(LpChannelPtr, Channel);

      /* Update the scheduler pointer in the local variable */
     (*LddScheduler) = LpChannelPtr->ddFirstScheduler + LucReqSchId_SporFrms;
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    }
    else
    {

#if(LINTP_SUPPORT == STD_ON)
      /* @Trace: LinIf_SUD_API_425*/
      /* Change to NULL Schedule */
      LinIf_ChangeToNullSchedule(LpChannelPtr, LpTpChannelInfo);
#else
      /* Change to NULL Schedule */
      LinIf_ChangeToNullSchedule(LpChannelPtr);
#endif /* #if(LINTP_SUPPORT == STD_ON) */

#if (LINIF_CDD_SUPPORT == STD_ON)
      (LinIf_GaaSchReqConfFun[Channel])
      (LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
          LpChannelRamData->ddActivSchId);
#else
      LinSM_ScheduleRequestConfirmation(
          LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
          LpChannelRamData->ddActivSchId);
#endif

    }
  } /* if(LpChannelRamData->ddActivSchId != LucReqSchId_SporFrms) */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == LINIF_MASTER_SUPPORT) */






#if (LINTP_SUPPORT == STD_ON)
#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinTp_HandleP2Timer                                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function handle P2 timer.                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : *LpTpChannelRamData                                   **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint8                                                 **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                        None                                                **
**                      Function(s) invoked:                                  **
**                        None                                                **
*******************************************************************************/
static FUNC(uint8, LINIF_CODE) LinTp_HandleP2Timer (
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData)
{
  uint8 LucNewBuffReqFlag;

  /* Initialize local variable */
  LucNewBuffReqFlag = LINIF_ZERO;

  /* If the P2 timeout counter started */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  if(LINIF_ONE <= LpTpChannelRamData->usP2TimerCounter)
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  {
    /* @Trace: LinIf_SUD_API_387*/
    /* Reset the P2 Timer counter */
    LpTpChannelRamData->usP2TimerCounter--;
    /* Check the P2 timeout counter expires or not */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    if(LINIF_ZERO != LpTpChannelRamData->usP2TimerCounter)
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    {
      /* @Trace: LinIf_SUD_API_388*/
      /* Set the buffer request flag as True */
      LucNewBuffReqFlag = LINIF_ONE;
    }
  }
  else
  {
    /* @Trace: LinIf_SUD_API_389*/
    /* Set the buffer request flag as True */
    LucNewBuffReqFlag = LINIF_ONE;
  }

  return LucNewBuffReqFlag;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinTp_HandleNCsTimer                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function handle N_Cs timer.                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LddChnlIndex                                          **
**                      *LpTpChannelRamData                                   **
**                      *LpTpChannelInfo                                      **  
**                                                                            ** 
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint8                                                 **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                        LinTp_GaaTimers                                     **
**                                                                            **
**                      Function(s) invoked:                                  **
**                        PduR_LinTpRxIndication(),                           **
**                        LinIf_SwitchScheduleMode()                          **
*******************************************************************************/
static FUNC(uint8, LINIF_CODE) LinTp_HandleNCsTimer (
  NetworkHandleType LddChnlIndex,
  P2CONST(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo)
{
  uint8 LucNewBuffReqFlag;

  /* Initialize local variable */
  LucNewBuffReqFlag = LINIF_ZERO;

  /* If the N_Cs timeout counter started */
  if(LINIF_ONE <= (LinTp_GaaTimers[LddChnlIndex][LINTP_NCS_TIMER]))
  {
    /* @Trace: LinIf_SUD_API_390*/
    /* Decrement the timer */
    LinTp_GaaTimers[LddChnlIndex][LINTP_NCS_TIMER]--;
    /* Check the N_Cs timeout counter expires or not */
    if(LINIF_ZERO != LinTp_GaaTimers[LddChnlIndex][LINTP_NCS_TIMER])
    {
      /* @Trace: LinIf_SUD_API_391*/
      /* Set the buffer request flag as True */
      LucNewBuffReqFlag = LINIF_ONE;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_392*/
      /* Invoke the upper layer confirmation callback with failure */
      PduR_LinTpTxConfirmation(
        LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_NOT_OK);
      /* Switch the mode to LINTP_APPLICATIVE_SCHEDULE */
      LinIf_SwitchScheduleMode(LpTpChannelInfo, LINTP_APPLICATIVE_SCHEDULE);
    }
  }

  return LucNewBuffReqFlag;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinTp_HandleNCrTimer                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function handle N_Cr timer.                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LddChnlIndex                                          **
**                      *LpTpChannelRamData                                   **
**                      *LpTpChannelInfo                                      **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint8                                                 **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                        LinTp_GaaTimers                                     **
**                                                                            **
**                      Function(s) invoked:                                  **
**                        PduR_LinTpRxIndication(),                           **
**                        LinIf_SwitchScheduleMode()                          **
*******************************************************************************/
static FUNC(uint8, LINIF_CODE) LinTp_HandleNCrTimer (
  NetworkHandleType LddChnlIndex,
  P2CONST(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo)
{
  uint8 LucNewBuffReqFlag;

  /* Initialize local variable */
  LucNewBuffReqFlag = LINIF_ZERO;

  /* If the N_Cr timeout counter started */
  if(LINIF_ONE <= (LinTp_GaaTimers[LddChnlIndex][LINTP_NCR_TIMER]))
  {
    /* @Trace: LinIf_SUD_API_393*/
    /* Decrement the timer */
    LinTp_GaaTimers[LddChnlIndex][LINTP_NCR_TIMER]--;
    /* Check the N_Cr timeout counter expires or not */
    if(LINIF_ZERO != LinTp_GaaTimers[LddChnlIndex][LINTP_NCR_TIMER])
    {
      /* @Trace: LinIf_SUD_API_394*/
      /* Set the buffer request flag as True */
      LucNewBuffReqFlag = LINIF_ONE;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_395*/
      /* Invoke the upper layer confirmation callback with failure */
      PduR_LinTpRxIndication(
        LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_TIMEOUT_CR);
      /* Switch the mode to LINTP_APPLICATIVE_SCHEDULE */
      LinIf_SwitchScheduleMode(LpTpChannelInfo, LINTP_APPLICATIVE_SCHEDULE);
    }
  }

  return LucNewBuffReqFlag;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinTp_HandleNAsTimer                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function handle N_As timer.                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LddChnlIndex                                          **
**                      *LpTpChannelRamData                                   **
**                      *LpTpChannelInfo                                      **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint8                                                 **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                        LinTp_GaaTimers                                     **
**                                                                            **
**                      Function(s) invoked:                                  **
**                        PduR_LinTpRxIndication(),                           **
**                        LinIf_SwitchScheduleMode()                          **
*******************************************************************************/
static FUNC(uint8, LINIF_CODE) LinTp_HandleNAsTimer (
  NetworkHandleType LddChnlIndex,
  P2CONST(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo)
{
  uint8 LucNewBuffReqFlag;

  /* Initialize local variable */
  LucNewBuffReqFlag = LINIF_ZERO;

  /* If the N_As timeout counter started */
  if(LINIF_ONE <= (LinTp_GaaTimers[LddChnlIndex][LINTP_NAS_TIMER]))
  {
    /* @Trace: LinIf_SUD_API_396*/
    /* Decrement the timer */
    LinTp_GaaTimers[LddChnlIndex][LINTP_NAS_TIMER]--;
    /* Check the N_Cr timeout counter expires or not */
    if(LINIF_ZERO != LinTp_GaaTimers[LddChnlIndex][LINTP_NAS_TIMER])
    {
      /* @Trace: LinIf_SUD_API_397*/
      /* Set the buffer request flag as True */
      LucNewBuffReqFlag = LINIF_ONE;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_398*/
      /* Invoke the upper layer confirmation callback with failure */
      PduR_LinTpTxConfirmation(
        LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_TIMEOUT_A);
      /* Switch the mode to LINTP_APPLICATIVE_SCHEDULE */
      LinIf_SwitchScheduleMode(LpTpChannelInfo, LINTP_APPLICATIVE_SCHEDULE);
    }
  }

  return LucNewBuffReqFlag;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (LINTP_SUPPORT == STD_ON) */

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinTp_GetNextScheduleId                               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function returns the ID of the next schedule     **
**                      to be executed.                                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LucComp                                               **
**                      *LpChannelPtr                                         **
**                      *LpChannelRamData                                     **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint8                                                 **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                        LinIf_GaaConfiguration                              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                        None                                                **
*******************************************************************************/
static FUNC(uint8, LINIF_CODE) LinTp_GetNextScheduleId (
  uint8 LucComp,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData)
{
  uint8 LucIdToReturn;

  /* Initialize local variable */
  LucIdToReturn = LINIF_ZERO;

  /* polyspace-begin MISRA-C3:16.1 [Justified:Low] "Default label never been reach" */
  /* polyspace-begin MISRA-C3:16.4 [Justified:Low] "Default label never been reach" */
  /* The schedule can be changed in below cases */
  switch (LucComp)
  {
    /* There is no schedule request or pending schedule table */
    case LINIF_ZERO:
    {
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      if((LinIf_GaaConfiguration[0].pSchTable[\
                LpChannelPtr->ddFirstScheduler + \
                    LpChannelRamData->ddActivSchId]).ucScheduleType == \
                                                    LINIF_RUN_CONTINUOUS)
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      {
        /* @Trace: LinIf_SUD_API_290*/
        LucIdToReturn = LpChannelRamData->ddActivSchId;
      }
      /* @Trace: LinIf_SUD_API_291*/
      break;
    }
    /* There is the pending schedule table, and the schedule which is
                                        'RUN_ONCE' type is completed. */
    /* And additionally, it is possible that there is a schedule request
                              that the ID is equal to the pending one. */
    /* So, serve the pending schedule table. */
    case LINIF_ONE:
    {
      /* @Trace: LinIf_SUD_API_292*/
      LucIdToReturn = LpChannelRamData->ddPendingId;
      LpChannelRamData->ucTempEntryNum =
        LpChannelRamData->ucNoOfEntriesLeft;
      /* Making the particular Memory pointing to Schedule Id
        * to Invalid value.
      */
      LpChannelRamData->ddPendingId = LpChannelPtr->ddMaxSchs;
      break;
    }
    /* There is a schedule request with a valid schedule ID
                                      (also including the same ID) */
    case LINIF_TWO:
    {
      /* @Trace: LinIf_SUD_API_293*/
      LucIdToReturn = *(LpChannelPtr->pSchId);
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      if((LINIF_RUN_ONCE == \
        (LinIf_GaaConfiguration[0].\
          pSchTable[LpChannelPtr->ddFirstScheduler + \
                (*(LpChannelPtr->pSchId))]).ucScheduleType) &&\
          (LINIF_RUN_CONTINUOUS == \
                (LinIf_GaaConfiguration[0].\
                    pSchTable[LpChannelPtr->ddFirstScheduler + \
                        LpChannelRamData->ddActivSchId]).ucScheduleType))
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      {
        if((LINIF_CONTINUE_AT_IT_POINT == \
            (LinIf_GaaConfiguration[0].\
                pSchTable[LpChannelPtr->ddFirstScheduler + \
                  LpChannelRamData->ddActivSchId]).blResumePosition) &&
          (LpChannelRamData->ddActivSchId != LpChannelRamData->
          ddCompltdSchId))
        {
          /* @Trace: LinIf_SUD_API_294*/
            LpChannelRamData->ucNoOfEntriesLeft =
              LpChannelRamData->ucSchEntryNum;
        }
        else
        {
          /* @Trace: LinIf_SUD_API_295*/
          LpChannelRamData->ucNoOfEntriesLeft = LINIF_ZERO;
        }
        /* @Trace: LinIf_SUD_API_296*/
        LpChannelRamData->ddPendingId = LpChannelRamData->ddActivSchId;
      }
      /* @Trace: LinIf_SUD_API_297*/
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      LpChannelRamData->ucTempEntryNum = LINIF_ZERO;

      break;
    }
  /* polyspace-end MISRA-C3:16.1 [Justified:Low] "Default label never been reach" */
  /* polyspace-end MISRA-C3:16.4 [Justified:Low] "Default label never been reach" */
    /* Existence of PendingID will be there if ActiveScheduleId is
      * RUN_ONCE, as we are considering RUN_ONCE is completed we can make
      * comparison between PendingID and Requested ID. As PendingID is RC
      * we can consider Requested ID as IDToServe.
    */
    /* pending Schedule is present and the Active schedule is completed
      * But a new schedule request is present
    */
    default:
    {
      /* @Trace: LinIf_SUD_API_298*/
      LucIdToReturn = *(LpChannelPtr->pSchId);
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      if(LINIF_RUN_CONTINUOUS == \
          (LinIf_GaaConfiguration[0].\
              pSchTable[LpChannelPtr->ddFirstScheduler + \
                        (*(LpChannelPtr->pSchId))]).ucScheduleType)
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_TransmitUCF" */
      {
        /* @Trace: LinIf_SUD_API_299*/
        /* Making the particular Memory pointing to Schedule Id to Invalid value.
        */
        LpChannelRamData->ddPendingId = LpChannelPtr->ddMaxSchs;
        LpChannelRamData->ucNoOfEntriesLeft = LINIF_ZERO;
      }
      /* @Trace: LinIf_SUD_API_300*/
      LpChannelRamData->ucTempEntryNum = LINIF_ZERO;

      break;
    }
  } /* switch (LucComp) */

  return LucIdToReturn;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#if ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && (LINIF_DEV_ERROR_DETECT == STD_ON))
#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinIf_DetGetTrcvWakeupReason                          **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used for DET checking of             **
**                      LinIf_GetTrcvWakeupReason API.                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : Channe                                                **
**                      TrcvWuReasonPtr                                       **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaComMChannel,                                 **
**                      LinIf_GaaComMChannelMap,                              **
**                      LinIf_GaaLtChannelInfo,                               **
**                      LinIf_GaaTrcvDriverApis                               **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError                                       **
**                      LinTrcv_GetOpMode                                     **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, LINIF_CODE) LinIf_DetGetTrcvWakeupReason (
  NetworkHandleType Channel,
  P2CONST(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINIF_APPL_DATA)
    TrcvWuReasonPtr)
{
  uint8 LucIdx;
  NetworkHandleType LddChnlIndex;
  Std_ReturnType LddReturnValue;
  LinTrcv_TrcvModeType LddTrcvMode;
  boolean LblErrFlag;

  /* Initialize local variables */
  LddChnlIndex = LINIF_ZERO;
  LddReturnValue = E_OK;
  LddTrcvMode = LINTRCV_TRCV_MODE_NORMAL;
  LblErrFlag = LINIF_TRUE;

  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_098*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                LINIF_GETTRCVWAKEUPREASON_SID, LINIF_E_UNINIT);
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
      /* @Trace: LinIf_SUD_API_099*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                      LINIF_GETTRCVWAKEUPREASON_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* Access LinIf_GaaComMChannelMap with the 'Channel' as an
         index after checking the validity of the 'Channel'.*/
      /* Get the Channel index */
      /* @Trace: LinIf_SUD_API_100*/
      LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
    }
    /* check if transceiver driver is not referenced to
                                                   the corresponding channel*/
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    if((LINIF_TRCV_NOTCONFIGURED == \
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDriverIndex)
      || (LINIF_TRCV_NOTCONFIGURED == \
        LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId))
    {
      /* @Trace: LinIf_SUD_API_102*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                    LINIF_GETTRCVWAKEUPREASON_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    /* check if transceiver driver is not referenced to
                                                   the corresponding channel*/
    #else
    #if(LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)
    /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* 
    polyspace-begin MISRA2012:2.1 [Justified:Low] "It's changed in GEN code" 
    polyspace-begin MISRA2012:14.3 [Justified:Low] "It's changed in GEN code" 
    */
    if(LINIF_TRCV_NOTCONFIGURED == \
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId)
    {
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                      LINIF_GETTRCVWAKEUPREASON_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    /* 
    polyspace-end MISRA2012:2.1 [Justified:Low] "It's changed in GEN code" 
    polyspace-end MISRA2012:14.3 [Justified:Low] "It's changed in GEN code" 
    */
    /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    #endif
    #endif
    if(E_OK == LddReturnValue)
    {
      #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
      /* @Trace: LinIf_SUD_API_103*/
      (void) LinIf_GaaTrcvDriverApis[LinIf_GaaLtChannelInfo[LddChnlIndex].
        ucTrcvDriverIndex].pGetOpMode(LinIf_GaaLtChannelInfo[LddChnlIndex].\
                                            ucTrcvDrvChannelId, &LddTrcvMode);
      #else
      (void) LinTrcv_GetOpMode(LinIf_GaaLtChannelInfo[LddChnlIndex].\
                                              ucTrcvDrvChannelId, &LddTrcvMode);
      #endif
      /* polyspace-begin RTE:NIVL [Justified:Low] "The value was set before" */
      if(LddTrcvMode != LINTRCV_TRCV_MODE_NORMAL)
      /* polyspace-begin RTE:NIVL [Justified:Low] "The value was set before" */
      {
        /* @Trace: LinIf_SUD_API_104*/
        (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                      LINIF_GETTRCVWAKEUPREASON_SID, LINIF_E_TRCV_NOT_NORMAL);
        LddReturnValue = E_NOT_OK;
      }
    } /* if(E_OK == LddReturnValue) */
    /* Check if the TransceiverModePtr iis NULL */
    if(NULL_PTR == TrcvWuReasonPtr)
    {
      /* @Trace: LinIf_SUD_API_105*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                    LINIF_GETTRCVWAKEUPREASON_SID, LINIF_E_PARAM_POINTER);
      LddReturnValue = E_NOT_OK;
    }
  }
  return LddReturnValue;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinIf_DetSetTrcvWakeupMode                            **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used for DET checking of             **
**                      LinIf_SetTrcvWakeupMode API.                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : Channe                                                **
**                      TrcvWuReasonPtr                                       **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaComMChannel,                                 **
**                      LinIf_GaaComMChannelMap,                              **
**                      LinIf_GaaLtChannelInfo,                               **
**                      LinIf_GaaTrcvDriverApis                               **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError                                       **
**                      LinTrcv_GetOpMode                                     **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, LINIF_CODE) LinIf_DetSetTrcvWakeupMode (
  NetworkHandleType Channel,
  LinTrcv_TrcvWakeupModeType LinTrcvWakeupMode)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIdx;
  boolean LblErrFlag;
  #if((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
    (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON))
  NetworkHandleType LddChnlIndex;
  #endif /* ((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
    (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)) */

  /* Initialize local variable */
  LddReturnValue = E_OK;
  LblErrFlag = LINIF_TRUE;
  #if((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
    (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON))
  LddChnlIndex = (NetworkHandleType)LINIF_ZERO;
  #endif /* ((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
    (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)) */

  /* Check if the LINIF module is not initialized */
  if(LINIF_UNINIT == LinIf_GblInitSts)
  {
    /* @Trace: LinIf_SUD_API_109*/
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                              LINIF_SETTRCVWAKEUPMODE_SID, LINIF_E_UNINIT);
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
      /* @Trace: LinIf_SUD_API_110*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                      LINIF_SETTRCVWAKEUPMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      #if((LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
          (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON))
      /* @Trace: LinIf_SUD_API_111*/
      /* Get the Channel index */
      LddChnlIndex = LinIf_GaaComMChannelMap[Channel];
      #endif /* (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON) || \
                (LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)) */
    }
    /* check if transceiver driver is not referenced to
                                                   the corresponding channel*/
    #if(LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
    if((LINIF_TRCV_NOTCONFIGURED == \
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDriverIndex)
      || (LINIF_TRCV_NOTCONFIGURED == \
        LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId))
    {
      /* @Trace: LinIf_SUD_API_113*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                    LINIF_SETTRCVWAKEUPMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
      LddReturnValue = E_NOT_OK;
    }
    /* check if transceiver driver is not referenced to
                                                   the corresponding channel*/
    #else
    #if(LINIF_TRCV_CHANNEL_ID_NOT_CONFIGURED == STD_ON)
    /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* 
    polyspace-begin MISRA2012:2.1 [Justified:Low] "It's changed in GEN code" 
    polyspace-begin MISRA2012:14.3 [Justified:Low] "It's changed in GEN code" 
    */
    if(LINIF_TRCV_NOTCONFIGURED == \
      LinIf_GaaLtChannelInfo[LddChnlIndex].ucTrcvDrvChannelId)
    {
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                      LINIF_SETTRCVWAKEUPMODE_SID, LINIF_E_NONEXISTENT_CHANNEL);
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
    if((uint8)LinTrcvWakeupMode > LINIF_TRCV_INVALID_WAKEUP_MODE)

    {
      /* @Trace: LinIf_SUD_API_114*/
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID, \
                                LINIF_SETTRCVWAKEUPMODE_SID, LINIF_E_PARAMETER);
      LddReturnValue = E_NOT_OK;
    }
    /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_SetTrcvMode" */
  }

  return LddReturnValue;
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && (LINIF_DEV_ERROR_DETECT == STD_ON)) */

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinIf_InitAllChannels                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes all the channels in          **
**                      LIN Interface.                                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GaaConfiguration,                               **
**                      LinTp_GaaChannelInfo,                                 **
**                      LinIf_GaaLtChannelInfo,                               **
**                      LinIf_GaaDriverApis                                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError(),                                    **
**                      LinIf_ChangeToNullSchedule(),                         **
**                      EcuM_GetResetReason(),                                **
**                      Lin_GetStatus(),                                      **
**                      Lin_GoToSleepInternal()                               **
*******************************************************************************/
#if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
FUNC(boolean, LINIF_CODE) LinIf_InitAllChannels (void)
#else
FUNC(void, LINIF_CODE) LinIf_InitAllChannels (void)
#endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */
{
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr;
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData;
  #if (LINTP_SUPPORT == STD_ON)
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST) LpTpChannelPtr;
  #endif /* (LINTP_SUPPORT == STD_ON) */
  #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  uint8 lucLinDriveIndex;
  #endif /* (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON) */
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA) LpFrameRamData;
  uint8 LucPidTableIdx;
  #endif /* (LINIF_SLAVE_SUPPORT == STD_ON) */
  uint8 LucLinDriveId;
  NetworkHandleType LddChnlIndex;
  #if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
  boolean LblDetError;
  #endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */
  /* Variables for checking Lin_GoToSleepInternal s*/
  Lin_StatusType LenLinStatus;
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) LpRxDataPtr;
  /* @Trace: LinIf_SUD_API_001*/
  #if(LINIF_SPORADIC_FRAMES == STD_ON)
  uint8 LucByteCount;
  uint8 LucAssociatedFrames;
  #endif

  /* Initialize channel index */
  LddChnlIndex = LINIF_ZERO;
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  LucPidTableIdx = LINIF_ZERO;
  #endif /* (LINIF_SLAVE_SUPPORT == STD_ON) */
  #if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
  LblDetError = LINIF_FALSE;
  #endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */

  do
  {
    /* @Trace: LinIf_SUD_API_004*/
    /* Get the pointer to first channel structure */
    LpChannelPtr = &(LinIf_GaaConfiguration[0].pChannelInfor[LddChnlIndex]);
    /* Get the pointer to channel RAM data */
    LpChannelRamData = LpChannelPtr->pChannelRamData;
    /* SWS_LinIf_00444 */
    #if(LINTP_SUPPORT == STD_ON)
    LpTpChannelPtr = &(LinTp_GaaChannelInfo[LddChnlIndex]);
    /* Invoke internal function to clear all pending status parameters
    * of the channel and setting active schedule to NULL */
    LinIf_ChangeToNullSchedule(LpChannelPtr, LpTpChannelPtr);
    #else
      #if(LINIF_MASTER_SUPPORT == STD_ON)
      if(LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
      {
          /* Change to NULL Schedule */
          LinIf_ChangeToNullSchedule(LpChannelPtr);
      }
      #endif /* #if(LINIF_MASTER_SUPPORT == STD_ON) */
    #endif /* #if(LINTP_SUPPORT == STD_ON) */
    /* Clear the sleep requested status */
    LpChannelRamData->ucSleepRequested = LINIF_ZERO;
    /* Clear the sleep WakeupConfirmCount */
    LpChannelRamData->ucWakeupConfirmCount = LINIF_ZERO;
    /* Clear the WakeupSignalSent */
    LpChannelRamData->ucWakeupSignalSent = E_NOT_OK;
    #if (LINIF_SLAVE_SUPPORT == STD_ON)
    /* Get the pointer to Frame RAM data */
    LpFrameRamData = LpChannelPtr->pFrameRamData;
    if (LINIF_SLAVE_NODE == LpChannelPtr->ddNodeType)
    {
      /* @Trace: LinIf_SUD_API_005*/
      /* Get Pid Table index */
      LucPidTableIdx = LpChannelPtr->ucPidTableIdx;
      /* Get Pid Table */
      LpFrameRamData->pPidTable = \
        &LinIf_GaaConfiguration[0].pPidTable[LucPidTableIdx];
      /* Get Frame Index Table */
      LpFrameRamData->pFrameIndexTable = \
              &LinIf_GaaConfiguration[0].pFrameIdxTable[LucPidTableIdx];
      /* Initialization number of wake-up signal sent */
      LpChannelRamData->ucNumberWakeupSignalSent = LINIF_ZERO;
      /* Initialization number of block wake-up */
      LpChannelRamData->ucNumberBlockWakeup = LINIF_ZERO;
      /* Initialization timer delay */
      LpChannelRamData->ulCounterDelayBlockWakeup = LpChannelPtr->ulCounterDelayBlockWakeup;
      LpChannelRamData->ulCounterDelayWakeupSignalSent = LINIF_ZERO;
    }
    #endif
    /* @Trace: LinIf_SUD_API_006*/
    /* SWS_LinIf_00507 */
    /* Set LinIf Channel state to sleep */
    LpChannelRamData->ucChannelSts = LINIF_CHANNEL_SLEEP;
    LucLinDriveId = LinIf_GaaLtChannelInfo[LddChnlIndex].ucDrvChannelId;
    #if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
    /* Set Lin Channel state to sleep without sending Sleep Cmd */
    lucLinDriveIndex = LinIf_GaaLtChannelInfo[LddChnlIndex].ucDriverIndex;
    (void) LinIf_GaaDriverApis[lucLinDriveIndex].
        pLinGoToSleepInternal(LucLinDriveId);

      #if(LINIF_MASTER_SUPPORT == STD_ON)
      /* Lin_GetStatus() only applicable for LIN master node */
      if(LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
      {
      /* Check Lin Driver channel state after a call of
        Lin_GoToSleepInternal */
      LenLinStatus = LinIf_GaaDriverApis[lucLinDriveIndex].
        pLinGetStatus(LucLinDriveId, &LpRxDataPtr);
      }
      #endif /* (LINIF_MASTER_SUPPORT == STD_ON) */
    #else
    /* Set Lin Channel state to sleep without sending Sleep Cmd */
    (void)Lin_GoToSleepInternal(LucLinDriveId);
      #if(LINIF_MASTER_SUPPORT == STD_ON)
      /* Lin_GetStatus() only applicable for LIN master node */
      if(LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
      {
      /* Invoke the GetStatus function */
      LenLinStatus = Lin_GetStatus(LucLinDriveId, &LpRxDataPtr);
      }
      #endif /* (LINIF_MASTER_SUPPORT == STD_ON) */
    #endif

      #if(LINIF_MASTER_SUPPORT == STD_ON)
      /* Lin_GetStatus() only applicable for LIN master node */
      if(LINIF_MASTER_NODE == LpChannelPtr->ddNodeType)
      {
        /* Check Lin Driver channel state after a call of Lin_GoToSleepInternal */
        if(LIN_CH_SLEEP != LenLinStatus)
        {
          /* @Trace: LinIf_SUD_API_007*/
          #if(LINIF_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
                                  LINIF_INIT_SID, LINIF_E_DRV_SLEEP_FAILED);
          LblDetError = LINIF_TRUE;
          #endif
        }
        else
        {
          /* @Trace: LinIf_SUD_API_008*/
          /* Clear the wakeup flag */
          LpChannelRamData->blWakeupStatus = LINIF_FALSE;
        }
      }
      #endif /* (LINIF_MASTER_SUPPORT == STD_ON) */
    /* @Trace: LinIf_SUD_API_009*/
    /* Increment the Channel Count */
    LddChnlIndex++;
  }while((LddChnlIndex < LinIf_GaaConfiguration[0].ucNoOfChannels) && (LINIF_FALSE == LblDetError));

  /* The following statement will be incorrect if there is a slave configuration but no sporadic frames are configured */
  /* @Trace: LinIf_SUD_API_010*/
  //#if((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_SLAVE_SUPPORT == STD_ON))
  #if (LINIF_SPORADIC_FRAMES == STD_ON)
  #if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
  if(LINIF_FALSE == LblDetError)
  #endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */  
  {
    LucAssociatedFrames = \
        (uint8)(((uint8)(LinIf_GaaConfiguration[0].usNoAssociatedFrm - \
                                    LINIF_ONE) >> LINIF_THREE) + LINIF_ONE);
    /* @Trace: LinIf_SUD_API_011*/
    /* @Trace: LinIf_SUD_API_012*/                                
    for(LucByteCount = LINIF_ZERO; LucByteCount < LucAssociatedFrames; \
                                                              LucByteCount++)
    {
      /* @Trace: LinIf_SUD_API_013*/
      /* initialize sporadic frame pending status : LinIf_GaaBitData */
      LinIf_GaaBitData[LucByteCount] = LINIF_ZERO;
    }
  }
  #endif /* (LINIF_SPORADIC_FRAMES == STD_ON) */

  #if ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON))
  return LblDetError;
  #endif /* ((LINIF_DEV_ERROR_DETECT == STD_ON) && (LINIF_MASTER_SUPPORT == STD_ON)) */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#if (LINIF_MASTER_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name      : LinIf_MainFunctionMaster                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function is the main processing function for     **
**                      Master in the LIN Interface.                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : Channel                                               **
**                      *LpChannelRamData                                     **
**                      *LpChannelPtr                                         **
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
**                      LinTp_GaaChannelInfo,                                 **
**                      LinIf_GaaConfiguration,                               **
**                      LinIf_GaaSchReqConfFun,                               **
**                      LinIf_GaaLtChannelInfo                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      LinIf_ProcessWakeUpConfirm(),                         **
**                      LinIf_ProcessPrevStatus(),                            **
**                      LinTp_MainFunc(),                                     **
**                      LinIf_SleepReqMainFunction(),                         **
**                      LinIf_ProcessScheduleChanging(),                      **
**                      LinIf_SendFrame()                                     **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_MainFunctionMaster (
  NetworkHandleType Channel,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr)
{
  #if(LINTP_SUPPORT == STD_ON)
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST)LpTpChannelInfo;
  #endif /* (LINTP_SUPPORT == STD_ON) */
  #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
	P2CONST(LinIf_Scheduler, AUTOMATIC, LINIF_DATA) LpScheduler;
  #endif

  LinIf_SchHandleType LddScheduler;

  /* @Trace: LinIf_SUD_API_237*/
  #if(LINTP_SUPPORT == STD_ON)
  LpTpChannelInfo = &(LinTp_GaaChannelInfo[Channel]);
  #endif /* #if(LINTP_SUPPORT == STD_ON) */

  LinIf_ProcessWakeUpConfirm(Channel);

  SchM_Enter_LinIf_CHANNEL_STATUS_PROTECTION();
  SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
  /* Check if the channel is in operational state */
  if((LINIF_CHANNEL_OPERATIONAL == LpChannelRamData->ucChannelSts) ||
    (LINIF_SLEEP_REQ_PENDING <= LpChannelRamData->ucSleepRequested))
  {
    /* @Trace: LinIf_SUD_API_238*/
    SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
    SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
    /*Get current scheduler index*/
    LddScheduler = LpChannelPtr->ddFirstScheduler \
                                        + LpChannelRamData->ddActivSchId;

    if(LINIF_ZERO == LpChannelRamData->usDelayCounter)
    {
      /* @Trace: LinIf_SUD_API_239*/
      SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      if(LINIF_SLEEP_REQUESTED == LpChannelRamData->ucSleepRequested)
      {
        /* @Trace: LinIf_SUD_API_240*/
        LpChannelRamData->ucSleepRequested = LINIF_SLEEP_REQ_PENDING;
      }

      if((LINIF_SLEEP_REQ_PENDING >= LpChannelRamData->ucSleepRequested) \
                          && (LINIF_ZERO != LpChannelRamData->ucSchEntryNum))
      {
        /* @Trace: LinIf_SUD_API_241*/
        SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();

        #if(LINTP_SUPPORT == STD_ON)
        /* Process the previous transport status */
        LinIf_ProcessPrevStatus(LpChannelPtr, LpTpChannelInfo, Channel);
        #else
        /* Process the previous transport status */
        LinIf_ProcessPrevStatus(LpChannelPtr, Channel);
        #endif /* #if(LINTP_SUPPORT == STD_ON) */

        /* Check if end of the schedule is reached */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        if(((LpChannelRamData->ucSchEntryNum) ==
          LinIf_GaaConfiguration[0].pSchTable[LddScheduler].ucNoOfSchEntries))
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
        {
          /* @Trace: LinIf_SUD_API_242*/
          /* For finding which schedule table is completed */
          LpChannelRamData->ddCompltdSchId = LpChannelRamData->ddActivSchId;
          #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
          if(LINIF_COLLISION_RESOLVED == \
                                  LpChannelRamData->ucCollisionStatusFlag)
          {
            /* @Trace: LinIf_SUD_API_243*/
            LpChannelRamData->ucCollisionStatusFlag = \
                                                LINIF_COLLISION_NOT_OCCURRED;
            /* Load the stored schedule Id for event triggered frame */
            LpChannelRamData->ddActivSchId =
                                      LpChannelRamData->ddPendingSchIdEvt;
            /* Load the stored schedule entry number for event
              * triggered frame.
              */
            LpChannelRamData->ucSchEntryNum =
                                  LpChannelRamData->ucNoOfEntriesLeftAsEvt;
            /* Get current scheduler index */
            LddScheduler = LpChannelPtr->ddFirstScheduler \
                                        + LpChannelRamData->ddActivSchId;
            /* Get current scheduler table */
            LpScheduler = &LinIf_GaaConfiguration[0].pSchTable[LddScheduler];
            /* Check the type of schedule table; (if the current schedule
              * is LINIF_RUN_CONTINUOUS and is the last schedule) OR (the
              * Schedule table is of LINIF_RUN_ONCE)
              */

            if(((LINIF_RUN_CONTINUOUS == LpScheduler->ucScheduleType) \
                && (*(LpChannelPtr->pSchId) == LpChannelPtr->ddMaxSchs))
                      || (LINIF_RUN_ONCE == LpScheduler->ucScheduleType))
            {
              /* @Trace: LinIf_SUD_API_244*/
              #if (LINIF_CDD_SUPPORT == STD_ON)
              (LinIf_GaaSchReqConfFun[Channel])
                    (LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId, \
                                            LpChannelRamData->ddActivSchId);
              #else
              LinSM_ScheduleRequestConfirmation(
                    LinIf_GaaLtChannelInfo[Channel].ddComMNwHndlId,
                                          LpChannelRamData->ddActivSchId);
              #endif
            } /* end if((((LpChannelPtr->pFirstScheduler...*/
              /* Making the particular Memory pointing to Schedule Id
                * to Invalid value.
                */
              /* @Trace: LinIf_SUD_API_245*/
              LpChannelRamData->ddPendingSchIdEvt = LpChannelPtr->ddMaxSchs;
          } /* end if(LpChannelRamData->ucCollisionStatusFlag... */
          #endif
        }/* end if(((LpChannelRamData->... */
      }
      else
      {
        /* @Trace: LinIf_SUD_API_246*/
        SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
      }
    }

    /* Check if TP is supported */
    #if(LINTP_SUPPORT == STD_ON)
    if(LinTp_GblInitSts == LINTP_INIT)
    {
      /* @Trace: LinIf_SUD_API_247*/
      LinTp_MainFunc(Channel);
    }
    #endif

    /* @Trace: LinIf_SUD_API_248*/
    SchM_Enter_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
  #if (LINTP_SUPPORT == STD_ON)
  LinIf_SleepRequestedHandle(
    LddScheduler, Channel, LpChannelRamData, LpChannelPtr, LpTpChannelInfo);
  #else
  LinIf_SleepRequestedHandle(
    LddScheduler, Channel, LpChannelRamData, LpChannelPtr);
  #endif


  }/* Channel is in operational state */
  else
  {
    /* @Trace: LinIf_SUD_API_254*/
    SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
    SchM_Exit_LinIf_CHANNEL_STATUS_PROTECTION();
  }
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#define LINIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinIf_SleepRequestedHandle                            **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function handles sleep request.                  **
**                      This function will be called by Main function.        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : Scheduler                                             **
**                      Channel                                               **
**                      *LpChannelPtr                                         **
**                      *LpTpChannelInfo                                      **
**                                                                            **
** InOut Parameters   : LpChannelRamData                                      **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinIf_GaaConfiguration                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      LinIf_SleepReqMainFunction(),                         **
**                      LinIf_ProcessScheduleChanging(),                      **
**                      LinIf_SendFrame()                                     **
**                                                                            **
*******************************************************************************/
#if (LINTP_SUPPORT == STD_ON)
FUNC(void, LINIF_CODE) LinIf_SleepRequestedHandle (
  LinIf_SchHandleType Scheduler,
  NetworkHandleType Channel,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_CONST) LpTpChannelInfo)
#else
FUNC(void, LINIF_CODE) LinIf_SleepRequestedHandle (
  LinIf_SchHandleType Scheduler,
  NetworkHandleType Channel,
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA) LpChannelRamData,
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) LpChannelPtr)
#endif /* (LINTP_SUPPORT == STD_ON) */
{
  uint16 LusEntryIdx;
  LinIf_SchHandleType LddScheduler;

  LddScheduler = Scheduler;

  if(LINIF_SLEEP_REQ_PENDING <= LpChannelRamData->ucSleepRequested)
  {
    /* @Trace: LinIf_SUD_API_249*/
    SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
    #if (LINTP_SUPPORT == STD_ON)
    LinIf_SleepReqMainFunction(LpChannelPtr, LpTpChannelInfo, Channel);
    #else
    LinIf_SleepReqMainFunction(LpChannelPtr, Channel);
    #endif /* (LINTP_SUPPORT == STD_ON) */
  }
  else /* Sleep request is not pending */
  {
    /* @Trace: LinIf_SUD_API_250*/
    SchM_Exit_LinIf_SLEEP_REQUEST_STATUS_PROTECTION();
    /* Check if active schedule is not a NULL schedule */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    if((LINIF_NULL_SCHEDULE != LpChannelRamData->ddActivSchId) ||
                      (*(LpChannelPtr->pSchId) < LpChannelPtr->ddMaxSchs))
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    {
      /* Check if delay count equal to zero */
      if(LINIF_ZERO == LpChannelRamData->usDelayCounter)
      {
        /* @Trace: LinIf_SUD_API_251*/
        /**** PROCESS CHANGING SCHEDULE OR CHANGING ENTRY ****/
        LinIf_ProcessScheduleChanging(Channel, &LddScheduler);

        /**** PROCESS SCHEDULE ENTRY ****/
        if(LINIF_NULL_SCHEDULE != LpChannelRamData->ddActivSchId)
        {
          /* @Trace: LinIf_SUD_API_252*/
          /* Get the pointer to scheduler entry */
          /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
          LusEntryIdx = LinIf_GaaConfiguration[0].pSchTable[\
            LddScheduler].usSchFirstEntry + \
                            (uint16)LpChannelRamData->ucSchEntryNum;
          /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */

          #if(LINTP_SUPPORT == STD_ON)
          /* Invoke the corresponding header and response transmission */
          LinIf_SendFrame(LpChannelPtr, LusEntryIdx, LpTpChannelInfo,
            Channel);
          #else
          /* Invoke the corresponding header and response transmission */
          LinIf_SendFrame(LpChannelPtr, LusEntryIdx, Channel);
          #endif
          
          /* Load the delay count */
          LpChannelRamData->usDelayCounter = \
              LinIf_GaaConfiguration[0].pSchTblEntry[\
                                          LusEntryIdx].usDelayCount;

          /* Increment entry number in the schedule */
          (LpChannelRamData->ucSchEntryNum)++;
        }
      } /* Delay counter is zero */

      /* Check if delay count equal to zero */
      if(LINIF_ZERO != LpChannelRamData->usDelayCounter)
      {
        /* Decrement the delay counter */
        /* @Trace: LinIf_SUD_API_253*/
        (LpChannelRamData->usDelayCounter)--;
      }

    }/* Active schedule is not a null schedule */
  }/* Sleep request is not pending */
}
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (LINIF_MASTER_SUPPORT == STD_ON) */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
