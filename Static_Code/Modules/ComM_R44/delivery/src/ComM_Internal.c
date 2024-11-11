/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
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
**  SRC-MODULE: ComM_Internal.c                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of Internal State Change Functionality              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.1.7_HF2      26-Mar-2024         Minuk Kim        CP44-7455              **
** 1.1.7_HF1      04-Mar-2024         Minuk Kim        CP44-5906, CP44-3875   **
** 1.1.7          31-Jan-2024         Minuk Kim        CP44-3148, CP44-3149   **
** 1.1.6          10-Aug-2023         ThuanLD5         CP44-2529              **
** 1.1.4          07-Mar-2022         ThuanVT          CP44-1152, 1762        **
** 1.1.3          16-Dec-2022         ThuanVT          BUGCLASSIC-380,        **
                                                       CP44-1324, CP44-1245   **
** 1.1.1          15-Sep-2022         ThuanVT          CP44-782               **
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #27547,    **
**                                                     #29733                 **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25644,    **
**                                                     #25636, #25646, #25674 **
** 1.0.1          20-Dec-2020         DatNXT           R44-Redmine #14793,    **
**                                                     #14801, #20073         **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Internal.h"
/* @Trace: ComM_SUD_MACRO_002 */
/* @Trace: SRS_ComM_AR_00217 SRS_ComM_AR_00217 SRS_ComM_AR_00223
 * SRS_ComM_AR_00224 SRS_ComM_AR_00226 SRS_ComM_AR_00227 SRS_ComM_AR_00228
 * SRS_ComM_AR_00229 SRS_ComM_AR_00230 SRS_ComM_AR_00231 SRS_ComM_AR_00233
 * SRS_ComM_AR_00234 SRS_ComM_AR_00237 SRS_ComM_AR_00238 SRS_ComM_AR_00239 
 */
/* @Trace: ComM_SUD_MACRO_005   */
#include "ComM_Ram.h"
#include "ComM_Config.h"          /* ComM Config header file */
#include "SchM_ComM.h"
#include "Dcm_ComM.h"
#include "BswM_ComM.h"
#include "Rte_ComM.h"             /* RTE generated header file */
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file */
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_SwitchComMMode                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to switch Communication mode        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex, comMMode                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels, ComM_SMGetCurComModeFun,             **
**                        ComM_SMReqComModeFun, ComM_CurComMode[].            **
**                        ComM_ModeRequested                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanSM_GetCurrentComMode                             **
**                        LinSM_GetCurrentComMode, FrSM_GetCurrentComMode     **
**                        CanSM_RequestComMode, LinSM_RequestComMode,         **
**                        FrSM_RequestComMode, ComM_BusSM_ModeIndication      **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09168 SRS_ComM_AR_00006 SRS_ComM_AR_00072 SRS_ComM_AR_00079
 * SRS_ComM_AR_00085 SRS_ComM_AR_00122 SRS_ComM_AR_00158 SRS_ComM_AR_00159
 * SRS_ComM_AR_00160 SRS_ComM_AR_00161 SRS_ComM_AR_00156
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_SwitchComMMode(uint8 chIndex, ComM_ModeType
  comMMode)
{
  /* @Trace: ComM_SUD_API_670 */
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* This variable is stores the Channel ID */
  NetworkHandleType handleChnlId;

  /* This variable is used to store the Channel Mode */
  ComM_ModeType modePtr;

  /* This variable is used to store the Bus Index */
  uint8 busIndex;
  modePtr = ComM_CurComMode[chIndex];

  /* Loading the address of structure to local pointer */
  handleChnlId = ComM_Channels[chIndex].ChannelId;

  /* Load the bus type from the structure */
  busIndex = ComM_Channels[chIndex].BusType;

  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  if (COMM_INTERNAL != busIndex)
  #endif
  {
    /* @Trace: ComM_SUD_API_671 */
    /* Get the current mode of respective SM */
    (void)ComM_SMGetCurComModeFun[busIndex](handleChnlId, &modePtr);
    /* Check if current mode and requested modes are same */
    if ((modePtr != comMMode))
    {
      /* @Trace: ComM_SUD_API_672 */
      if (COMM_FALSE == ComM_ModeRequested[chIndex])
      {
        /* @Trace: ComM_SUD_API_673 */
        /* Redmine #585 */
        ComM_ModeRequested[chIndex] = COMM_TRUE;
        #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
        (COMM_ETHNETWORK_PRESENT == STD_ON))

        if (!((COMM_SILENT_COMMUNICATION == comMMode) &&
          ((COMM_FLEXRAY == busIndex) || (COMM_LIN == busIndex))))
        #endif
        {
          /* @Trace: ComM_SUD_API_674 */
          /* Request the communication mode from respective SM */
          if (E_OK != ComM_SMReqComModeFun[busIndex](handleChnlId, comMMode))
          {
            /* @Trace: ComM_SUD_API_675 */
            ComM_ModeRequested[chIndex] = COMM_FALSE;
          }
        }
        #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
        (COMM_ETHNETWORK_PRESENT == STD_ON))
        else
        {
          ComM_ModeRequested[chIndex] = COMM_FALSE;
        }
        #endif
      } /* End of if (COMM_FALSE == ComM_ModeRequested[chIndex]) */
    } /* End of if (modePtr != comMMode) */
  } /* End of if (COMM_INTERNAL != busIndex) */
  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  else
  #endif
  #endif /* End of if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  {
    /* @Trace: ComM_SUD_API_676 */
    ComM_BusSM_ModeIndication(handleChnlId, comMMode);
  }
  #endif
} /* End of ComM_SwitchComMMode */

/*******************************************************************************
** Function Name        : ComM_SwitchToFullCom                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to change communication mode        **
**                        to Full communication                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_SubComMode[], ComM_ChannelsFullComMode         **
**                        ComM_Channels[], ComM_WakeupIndication[],           **
**                        ComM_ManagingSetMode[].                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentMode(),                            **
**                        Dcm_ComM_FullComModeEntered                         **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00095 SRS_ComM_AR_00163 
 * SRS_ComM_AR_00167 SRS_ComM_AR_00156
*/
FUNC(void, COMM_CODE) ComM_SwitchToFullCom(uint8 chIndex)
{
 /* @Trace: ComM_SUD_API_245 */
  /* Indication that Channel left the No Communication Mode */
  if (ComM_ChannelsFullComMode < COMM_CHANNELSFULLCOMMODE_MAX)
  {
    ComM_ChannelsFullComMode++;
  }

  /* Report Communication Mode change to DCM */
  (void)Dcm_ComM_FullComModeEntered(ComM_Channels[chIndex].ChannelId);

  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_Channels[chIndex].ChannelId,
    COMM_FULL_COMMUNICATION);

  SchM_Enter_ComM_ECUM_WAKEUP_IND();
  /* Set SubComMode */
  if ((COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
    || (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
    || (COMM_TRUE == ComM_WakeupIndication[chIndex])
    || (COMM_TRUE == ComM_PncReqtedflag[chIndex]))
  {
    /* @Trace: ComM_SUD_API_246 */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
  }
  else
  {
    /* @Trace: ComM_SUD_API_247 */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
  }

  /* Clear the wake up indication for that channel */
  if (COMM_TRUE == ComM_WakeupIndication[chIndex])
  {
    /* @Trace: ComM_SUD_API_248 */
    ComM_WakeupIndication[chIndex] = COMM_FALSE;
  }
  SchM_Exit_ComM_ECUM_WAKEUP_IND();
  #if (COMM_REFERENCE_CHANEL == STD_ON)
  if(COMM_TRUE == ComM_ManagingSetMode[chIndex])
  {
    /* @Trace: ComM_SUD_API_249 */
    ComM_ManagingSetMode[chIndex] = COMM_FALSE;
  }
  #endif

} /* End of ComM_SwitchToFullCom */

/*******************************************************************************
** Function Name        : ComM_SwitchToNoCom                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to change communication mode from   **
**                        Full or Silent to No communication                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_SubComMode[], ComM_ChannelsFullComMode         **
**                        ComM_RequestedComMode[], ComM_ReqedComModeCnt       **
**                        ComM_ChannelInhibition                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Dcm_ComM_NoComModeEntered(),                        **
**                        BswM_ComM_CurrentMode()                             **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00022 SRS_ComM_AR_00070 SRS_ComM_AR_00163
 * SRS_ComM_AR_00167 SRS_ComM_AR_00011 SRS_ComM_AR_00156 SRS_ComM_AR_00168 */
FUNC(void, COMM_CODE) ComM_SwitchToNoCom(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_250 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))
  /* Variable for Number of Pncs linked to the Channel */
  uint16 noOfPncs;
  /* Variable for Pnc Index */
  PNCHandleType tmpPncIndex;
  /* Variable for channel to pnc mapping */
  PNCHandleType indexValue;
  #endif
  #endif

  /* Report the No communication mode to DCM */
  (void)Dcm_ComM_NoComModeEntered(ComM_Channels[chIndex].ChannelId);

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))
  if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc)
  {
    /* @Trace: ComM_SUD_API_251 */
    /* Number of Pncs linked to the Channel */
    noOfPncs = ComM_Channels[chIndex].PncCount;

    /* Index in the Pnc Index array in the User */
    tmpPncIndex = ComM_Channels[chIndex].PncIndex;

    while (noOfPncs != COMM_ZERO)
    {
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      indexValue = ComM_ChannelToPncMapping[tmpPncIndex];

      if (ComM_SubPNCMode[indexValue] == COMM_PNC_PREPARE_SLEEP)
      {

        /* Start the PNC Timer for the channel*/
        SchM_Enter_ComM_PNC_PREPARE_TIMER();
        ComM_PncTimeCnt[indexValue] = COMM_ZERO;
        SchM_Exit_ComM_PNC_PREPARE_TIMER();

        ComM_SubPNCMode[indexValue] = COMM_PNC_NO_COMMUNICATION;

        /* Indication to BswM Module */
        BswM_ComM_CurrentPNCMode(ComM_Pncs[indexValue].PncId,
          COMM_PNC_NO_COMMUNICATION);
      }
      /* Decrement the PNC Count*/
      noOfPncs--;
      tmpPncIndex++;
    } /* End of while (noOfPncs != COMM_ZERO) */
  } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
  #endif
  #endif

  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_Channels[chIndex].ChannelId,
    COMM_NO_COMMUNICATION);

  /* Indication that Channel entered No Communication Mode */
  if (ComM_ChannelsFullComMode > COMM_ZERO)
  {
    ComM_ChannelsFullComMode--;
  }
  /* Change Sub State of No Communication*/
  ComM_SubComMode[chIndex] = COMM_NO_COM_NO_PENDING_REQUEST;

  /* Clear all Requests for the Specific user of the channel */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /*  Check for Limit channel inhibition condition */
  if (COMM_LIMITCHANNELTONOCOMM_MASK_SET == (ComM_ChannelInhibition[chIndex] &
    COMM_LIMITCHANNELTONOCOMM_MASK_SET))
  {
    /* @Trace: ComM_SUD_API_252 */
    ComM_ChannelInhibition[chIndex] = (ComM_ChannelInhibition[chIndex] &
      COMM_LIMITCHANNELTONOCOMM_MASK_CLR);

    /* Traceable SWS_ComM_00355 */
    #if (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON)
      /* Force an ECU reset */
      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The call to this function will have effect depending on configuration" */
      BswM_ComM_InitiateReset();
    #endif
  }
  #endif

  /* ========================== Implement for Post-Build ==================== */
  #else
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* Variable for Number of Pncs linked to the Channel */
    uint16 noOfPncs;
    /* Variable for Pnc Index */
    PNCHandleType tmpPncIndex;
    /* Variable for channel to pnc mapping */
    PNCHandleType indexValue;
  // }
  // else
  // {
    /* Do nothing */
  // }

  /* Report the No communication mode to DCM */
  Dcm_ComM_NoComModeEntered(ComM_Channels[chIndex].ChannelId);

  if (COMM_TRUE == ComM_PncEnabledFlashPB)
  {
    /* @Trace: ComM_SUD_API_253 */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    if (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chIndex].ChannelPnc)
    {
      /* @Trace: ComM_SUD_API_254 */
      /* Number of Pncs linked to the Channel */
      noOfPncs = ComM_ChannelsPNCRelatedGlobal[chIndex].PncCount;
      /* Index in the Pnc Index array in the User */
      tmpPncIndex = ComM_ChannelsPNCRelatedGlobal[chIndex].PncIndex;

      while (noOfPncs != COMM_ZERO)
      {
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        indexValue = ComM_ChannelToPncMappingGlobal[tmpPncIndex];

        /* Start the PNC Timer for the channel*/
        SchM_Enter_ComM_PNC_PREPARE_TIMER();
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        ComM_PncTimeCnt[indexValue] = COMM_ZERO;
        SchM_Exit_ComM_PNC_PREPARE_TIMER();
        /* Decrement the PNC Count*/
        noOfPncs--;
        tmpPncIndex++;

        ComM_SubPNCMode[indexValue] = COMM_PNC_NO_COMMUNICATION;
        /* Indication to BswM Module */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[indexValue].PncId,
          COMM_PNC_NO_COMMUNICATION);
      }
    } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
    else
    {
      /* @Trace: ComM_SUD_API_255 */
      /* Do nothing */
    }
  }
  else
  {
    /* @Trace: ComM_SUD_API_256 */
    /* Do nothing */
  }
  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_Channels[chIndex].ChannelId,
    COMM_NO_COMMUNICATION);
  /* Indication that Channel entered No Communication Mode */
  if (ComM_ChannelsFullComMode > COMM_ZERO)
  {
    ComM_ChannelsFullComMode--;
  }
  /* Change Sub State of No Communication*/
  ComM_SubComMode[chIndex] = COMM_NO_COM_NO_PENDING_REQUEST;

  /* Clear all Requests for the Specific user of the channel */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  /*  Check for Limit channel inhibition condition */
  if (COMM_LIMITCHANNELTONOCOMM_MASK_SET ==
          (ComM_ChannelInhibition[chIndex] & COMM_LIMITCHANNELTONOCOMM_MASK_SET))
  {
    /* @Trace: ComM_SUD_API_257 */
ComM_ChannelInhibition[chIndex] =
           (ComM_ChannelInhibition[chIndex] & COMM_LIMITCHANNELTONOCOMM_MASK_CLR)    ;
    /* Traceable SWS_ComM_00355 */
    #if (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON)
      /* Force an ECU reset */
      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The call to this function will have effect depending on configuration" */
      BswM_ComM_InitiateReset();
    #endif
  }
  else
  {
    /* @Trace: ComM_SUD_API_258 */
    /* Do nothing */
  }
  #endif
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_SwitchToNoCom */

/*******************************************************************************
** Function Name        : ComM_FullComMToSilentComM                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to change communication mode from   **
**                        Full to Silent communication                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels[], ComM_SubComMode[]                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Dcm_ComM_SilentComModeEntered,BswM_ComM_CurrentMode **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00163 SRS_ComM_AR_00167 
 * SRS_ComM_AR_00156
 */
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_FullComMToSilentComM(uint8 chIndex)
{
 /* @Trace: ComM_SUD_API_149 */
  ComM_SubComMode[chIndex] = COMM_SILENT_COM;

  /* Report the Silent communication mode to DCM */
  (void)Dcm_ComM_SilentComModeEntered(ComM_Channels[chIndex].ChannelId);

  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_Channels[chIndex].ChannelId,
    COMM_SILENT_COMMUNICATION);
}
#endif /* #if (COMM_CANNETWORK_PRESENT == STD_ON) ||
  * (COMM_ETHNETWORK_PRESENT == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_RequestComModeInhibitionCheck                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to check for inhibition when there  **
**                        is a request using API ComM_RequestComMode          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex, comMMode                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : comModeErrorFlg                                     **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels[], ComM_LimitEcuToNoCom,              **
**                        ComM_InhibitionReqst, ComM_Data                     **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_ComM_INHIBIT_CNT_PROTECTION(),           **
**                        SchM_Exit_ComM_INHIBIT_CNT_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_BSW_00441 SRS_ModeMgm_09089 SRS_ModeMgm_09089 SRS_ModeMgm_09155
 * SRS_ComM_AR_00110 SRS_ComM_AR_00120 SRS_ComM_AR_00127 SRS_ComM_AR_00128
 * SRS_ComM_AR_00129
 */
#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
FUNC(boolean, COMM_CODE) ComM_RequestComModeInhibitionCheck
  (uint8 chIndex, ComM_ModeType comMMode)
{
  /* @Trace: ComM_SUD_API_723 */
  #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

  /* Variable to check if inhibition is due to wake up inhibition */
  boolean inhibitionFlag;
  #endif
  boolean comModeErrorFlg;
  #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

  /* Initialize the variable */
  inhibitionFlag = COMM_FALSE;
  #endif
  comModeErrorFlg = COMM_FALSE;

  /* Mode cannot be granted because of the Mode Limitation */
  if (COMM_FULL_COMMUNICATION == comMMode)
  {
    #if (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON)
    /* @Trace: ComM_SUD_API_724 */
    /* Check if wake up inhibition is enabled in ECU group
     *   classification and Nm running in passive mode */
     /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if ((COMM_NMVARIANT_PASSIVE == ComM_Channels[chIndex].NmVariant) &&
      (COMM_ONE == ComM_Data.ComMEcuInhibition))
    {
      /* @Trace: ComM_SUD_API_725 */
      /* Error Flag is set*/
      comModeErrorFlg = COMM_TRUE;
    }
    #endif
    #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

    /* Limit to No Communication functionality is enabled and
     *   Limit ECU to No Communication is Enabled */

    /* Prevent Wake Up is enabled */
    #if (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON)
    else if ((COMM_LIMITCHNTONOCOM_MASK == (ComM_ChannelInhibition[chIndex] &
      COMM_LIMITCHNTONOCOM_MASK)) ||
      (COMM_TRUE == ComM_LimitEcuToNoCom))
    #else
    if ((COMM_LIMITCHNTONOCOM_MASK == (ComM_ChannelInhibition[chIndex] &
      COMM_LIMITCHNTONOCOM_MASK)) ||
      (COMM_TRUE == ComM_LimitEcuToNoCom))
    #endif
    {
      /* @Trace: ComM_SUD_API_726 */
      /* Error Flag is set*/
      comModeErrorFlg = COMM_TRUE;
    }
    #endif /* End of if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    #if ((COMM_PASSIVE_NMVARIANT_SUPPORT == STD_OFF) &&\
      (COMM_MODE_LIMITATION_ENABLED == STD_OFF))
    /* Prevent Wake Up is enabled */
    if (COMM_PREVENTWAKEUP_MASK == (ComM_ChannelInhibition[chIndex] &
              COMM_PREVENTWAKEUP_MASK))
    #else
    /* Prevent Wake Up is enabled */
    else if (COMM_PREVENTWAKEUP_MASK == (ComM_ChannelInhibition[chIndex] &
              COMM_PREVENTWAKEUP_MASK))
    #endif
    {
      /* @Trace: ComM_SUD_API_727 */
      /* Error Flag is set*/
      comModeErrorFlg = COMM_TRUE;

      /* Flag to store that inhibition is due to Prevent wake up */
      inhibitionFlag = COMM_TRUE;
    }
    #endif /* End of if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */
    else
    {
      /* @Trace: ComM_SUD_API_728 */
      /* To avoid MISRA warning */
    }
  } /* End of if (COMM_FULL_COMMUNICATION == comMMode) */
  #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

  /*  Check for Limit channel inhibition condition and Limit ECU to No Com */
  /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  else if (COMM_PREVENTWAKEUP_MASK == (ComM_ChannelInhibition[chIndex] &
    COMM_PREVENTWAKEUP_MASK))
  {
    /* @Trace: ComM_SUD_API_729 */
    /* Store the no communication request due to prevent wake up
     *   inhibition */
    if (ComM_InhibitionReqst[chIndex] > COMM_ZERO)
    {
      ComM_InhibitionReqst[chIndex]--;
    }
  }
  else
  {
    /* @Trace: ComM_SUD_API_730 */
    /* To avoid Misra warning */
  }
  #endif /* (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */

  /* Mode cannot be granted because of the Mode Limitation */
  if (COMM_TRUE == comModeErrorFlg)
  {
    /* @Trace: ComM_SUD_API_731 */
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

    /* The Full Communication request during inhibition is checked */
    if (COMM_TRUE == inhibitionFlag)
    {
      /* @Trace: ComM_SUD_API_732 */
      /* Update request when prevent wakeup is enabled */
      if (ComM_InhibitionReqst[chIndex] < COMM_INHIBITIONREQST_MAX)
      {
        ComM_InhibitionReqst[chIndex]++;
      }
    }
    #endif
    #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

    /* if ((COMM_FULL_COMMUNICATION equals comMMode) && */
    if (COMM_INHIBITCNT_MAX > ComM_Data.ComMFullComInhibitCounter)
    {
      /* @Trace: ComM_SUD_API_733 */
      /* Enter in Data Protection */
      SchM_Enter_ComM_INHIBIT_CNT_PROTECTION();

      /* Increment full communication inhibit counter */
      ComM_Data.ComMFullComInhibitCounter++;

      /* Exit Data Protection */
      SchM_Exit_ComM_INHIBIT_CNT_PROTECTION();
    } /* End of if comMMode == COMM_FULL_COMMUNICATION */
    #endif /* End of if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
  } /* End of if (COMM_TRUE == comModeErrorFlg) */

  return (comModeErrorFlg);
} /* End of ComM_RequestComModeInhibitionCheck */

#endif  /* ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
  * || (COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_ChannelDETCheck                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to check DET for the ChannelID      **
**                        passed                                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, ApiId                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK                                      **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_ChannelMapArray                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406
 */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ChannelDETCheck
  (NetworkHandleType Channel, uint8 ApiId)
{
  /* @Trace: ComM_SUD_API_698 */
  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_699 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_UNINIT);

    /* Set return value to indicate ComM is uninitialized */
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_700 */
    /* Do nothing */
  }

  /*Check if Channel ID is more than the Id configured */
  if (COMM_MAX_CHANNELID < Channel)
  {
    /* @Trace: ComM_SUD_API_701 */
    /* Report error to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the channel is not within configured
     *   channels */
    returnValue = E_NOT_OK;
  }
  #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
  else if (COMM_INVALID_CHANNEL == ComM_ChannelMapArray[Channel])
  {
    /* @Trace: ComM_SUD_API_702 */
    /* Report error to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the channel is not a configured channel */
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_703 */
    /* To avoid MISRA warning */
  }
  #endif /* End of if (COMM_CHANNEL_SEQUENTIAL == STD_OFF) */
  return (returnValue);
} /* End of ComM_ChannelDETCheck */
#endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_UserDETCheck                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to check DET for the UserID passed  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : User, ApiId                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK                                      **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_UserMapArray                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406
 */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_UserDETCheck
  (ComM_UserHandleType User, uint8 ApiId)
{
  /* @Trace: ComM_SUD_API_259 */
  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_260 */
    /* Report to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_UNINIT);

    /* Set return value to indicate ComM is uninitialized */
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_261 */
    /* Do nothing */
  }

  /* Check if User ID is  more than total users and
   *   is more than the Id configured */
  if ((COMM_NOT_USED_USER_ID == User) || (COMM_MAX_USERID < User))
  {
    /* @Trace: ComM_SUD_API_262 */
    /* Report error to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the user is not valid Id */
    returnValue = E_NOT_OK;
  }
  #if (COMM_USER_SEQUENTIAL == STD_OFF)
  else if (COMM_INVALID_USER == ComM_UserMapArray[User])
  {
    /* @Trace: ComM_SUD_API_263 */
    /* Report error to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the user is not a configured user */
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_264 */
    /* To avoid MISRA warning */
  }
  #endif /* End of if (COMM_USER_SEQUENTIAL == STD_OFF) */
  return (returnValue);
} /* End of ComM_UserDETCheck */
#endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_RequestComModeRteUpdate                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Rte the user requesting   **
**                        Fullcommunication for a channel using API           **
**                        ComM_RequestComMode                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex, userInx, comMMode                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Data,ComM_Channels[],ComM_Users[]              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Write_fullComRequestors()                           **
**                        SchM_Enter_ComM_REQ_MODECNT_PROTECTION()            **
**                        SchM_Exit_ComM_REQ_MODECNT_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00069 SRS_ComM_AR_00134 SRS_ComM_AR_00166
 * SRS_ComM_AR_00156 
 */
#if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
  (COMM_DIRECT_USER_MAPPING == STD_OFF))
FUNC(void, COMM_CODE) ComM_RequestComModeRteUpdate(uint8 chIndex, uint8
  userInx, ComM_ModeType comMMode)
{
  /* @Trace: ComM_SUD_API_240 */
  /* Variable to store the maximum requestors of a channel */
  uint8 maxChannelReq;

  /* Variable to store the last user id who requested the channel */
  uint8 lastUserId;

  /* Variable to store the index of requestors of a channel */
  uint8 reqIndex;

  /* Variable to write the maximum requestors of a channel to Rte */
  Rte_PortHandle_ComM_CurrentChannelRequest_P comMRteFullComWrite;

  /*   Rule            : 11.5
   *   Message         : A cast shall not be performed that removes any const or
   *                     volatile qualification from type addressed by a
   *                     pointer.
   *   Reason          : Since compiler was giving error typecasting has been
   *                     done
   *   Verification    : However, part of the code is verified manually and it
   *                     is not having any impact.
   */

  /* Initialization to pointer to function of Rte */
  #if (COMM_RTE_NOTIF == STD_ON)
  comMRteFullComWrite = (Rte_PortHandle_ComM_CurrentChannelRequest_P)
                           Rte_Ports_ComM_CurrentChannelRequest_P();
  #endif
  /* Initializing the index with recent user requestor of the
   *   channel*/
  maxChannelReq = ComM_FullComReq[chIndex].NumberOfRequesters;

  /*If the mode is Full communication */
  if (COMM_FULL_COMMUNICATION == comMMode)
  {
    /* @Trace: ComM_SUD_API_241 */
    /* Enter in Data Protection */
    SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

    /* Store the user id of the user of the channel */
    ComM_FullComReq[chIndex].HandleArray[maxChannelReq] =
      ComM_Users[userInx].UserId;

    /* Store the number of requestors of the channel */
    ComM_FullComReq[chIndex].NumberOfRequesters++;

    /* Exit data protection */
    SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
  } /* End of if (comMMode == COMM_FULL_COMMUNICATION) */
  else
  {
    /* @Trace: ComM_SUD_API_242 */
    /* Get the last user id */
    lastUserId = ComM_FullComReq[chIndex].HandleArray
                    [maxChannelReq - COMM_ONE];

    /* If the current user had requested for Full Communication
     *   before */
    if (lastUserId != ComM_Users[userInx].UserId)
    {
      /* @Trace: ComM_SUD_API_243 */
      /* Check if user is present in the array of Full Communication
       *   requestors of that channel */
      for (reqIndex = COMM_ZERO; reqIndex < maxChannelReq;
           reqIndex++)
      {
        /* Find the user */
        if (ComM_FullComReq[chIndex].HandleArray
            [reqIndex] == ComM_Users[userInx].UserId)
        {
          /* @Trace: ComM_SUD_API_244 */
          /* Enter in Data Protection */
          SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

          /* Overwrite the ID with last user id */
          ComM_FullComReq[chIndex].HandleArray
          [reqIndex] = lastUserId;

          /* Exit data protection */
          SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
        } /* End of if (ComM_FullComReq[chIndex].HandleArray */
      }
    } /* End of if (lastUserId != ComM_Users[userInx].UserId) */
    /* Enter in Data Protection */
    SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

    /* Decrement total number of requestors requested count */
    ComM_FullComReq[chIndex].NumberOfRequesters--;

    /* Exit data protection */
    SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
  } /* End of else */

  /* Update Rte with the required information */
  #if (COMM_RTE_NOTIF == STD_ON)
  comMRteFullComWrite[chIndex].Write_fullComRequestors(&ComM_FullComReq[chIndex]);
  #endif
} /* End of ComM_RequestComModeRteUpdate */
#endif /* End of if (COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_PncUserHandle                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall save user mode request for PNC   **
**                        State changes                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : tmpPncIndex,   comMode                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_Pncs,ComM_PncToUserMapping,                    **
**                        ComM_UserMapArray,ComM_RequestedComMode,            **
**                        ComM_RequestedPNCMod,                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00010 SRS_ComM_AR_00016  */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PncUserHandle(PNCHandleType tmpPncIndex, ComM_ModeType
  comMode)
{
  /* @Trace: ComM_SUD_API_182 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* The Variable to store User Index */
  uint8 tmpPncUserIndex;

  /* The Variable to store User Count */
  uint8 pncUserCount;

  /* The Variable to store User ID */
  uint8 tmpUserId;

  /* The Variable to store User Index from user map array */
  uint8 userIndex;

  /* The Variable to get comMode for avoid MISRA 17.8 */
  ComM_ModeType comModeTemp;

  /* Get comMode */
  comModeTemp = comMode;
  /* Get User Index */
  tmpPncUserIndex = ComM_Pncs[tmpPncIndex].UserIndex;

  /* Get User Count */
  pncUserCount = ComM_Pncs[tmpPncIndex].UserCount;
  while (pncUserCount != COMM_ZERO)
  {
    pncUserCount--;

    /* Note: Mapping provides ID of the User */
    tmpUserId = ComM_PncToUserMapping[tmpPncUserIndex];
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    userIndex = ComM_UserMapArray[tmpUserId];
    #else
    userIndex = tmpUserId;
    #endif

    /* Checking mode of all the users of the PNC*/
    if (comModeTemp < ComM_RequestedComMode[userIndex])
    {
      /* @Trace: ComM_SUD_API_183 */
      comModeTemp = ComM_RequestedComMode[userIndex];
    }
    tmpPncUserIndex++;
  }

  /* full communication mode :At least one User in Full Com */
  if (COMM_FULL_COMMUNICATION == comModeTemp)
  {
    /* @Trace: ComM_SUD_API_184 */
    /* full communication mode */
    ComM_RequestedPNCMode[tmpPncIndex] = PNC_USER_FULL_COMM;
  }
  else
  /* No communication mode :All user request No Com */
  {
    /* @Trace: ComM_SUD_API_185 */
    /* ready sleep mode */
    ComM_RequestedPNCMode[tmpPncIndex] = PNC_USER_NO_COMM;
  }

  #else
  /* ========================== Implement for Post-Build ==================== */
  /* The Variable to store User Index */
  uint8 tmpPncUserIndex;
  /* The Variable to store User Count */
  uint8 pncUserCount;
  /* The Variable to store User ID */
  uint8 tmpUserId;
  /* The Variable to store User Index from user map array */
  uint8 userIndex;
  /* The Variable to get comMode for avoid MISRA 17.8 */
  ComM_ModeType comModeTemp;

  /* Get comMode */
  comModeTemp = comMode;
  /* Get User Index */
  tmpPncUserIndex = ComM_PncsGlobal[tmpPncIndex].UserIndex;
  /* Get User Count */
  pncUserCount = ComM_PncsGlobal[tmpPncIndex].UserCount;
  while (pncUserCount != COMM_ZERO)
  {
    pncUserCount--;
    /* Note: Mapping provides ID of the User */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    tmpUserId = ComM_PncToUserMappingGlobal[tmpPncUserIndex];
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    userIndex = ComM_UserMapArray[tmpUserId];
    #else
    userIndex = tmpUserId;
    #endif

    /* Checking mode of all the users of the PNC*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if (comModeTemp < ComM_RequestedComMode[userIndex])
    {
      /* @Trace: ComM_SUD_API_186 */
      comModeTemp = ComM_RequestedComMode[userIndex];
    }
    tmpPncUserIndex++;
  }

  /* full communication mode :At least one User in Full Com */
  if (COMM_FULL_COMMUNICATION == comModeTemp)
  {
    /* @Trace: ComM_SUD_API_187 */
    /* full communication mode */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_RequestedPNCMode[tmpPncIndex] = PNC_USER_FULL_COMM;
  }
  else
  /* No communication mode :All user request No Com */
  {
    /* @Trace: ComM_SUD_API_188 */
    /* ready sleep mode */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_RequestedPNCMode[tmpPncIndex] = PNC_USER_NO_COMM;
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PncUserHandle */

#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  * (COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  * STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PncUserLowestMode                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall indicate RTE about the PNC Users **
**                        Lowest communication Mode of the associated channels**
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userIndx                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_Users, ComM_PncUserInxArr, ComM_Pncs           **
**                        ComM_ChnPncInxArr, ComM_ChannelMapArray             **
**                        ComM_CurComMode, ComM_ChnInxArr                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Rte_Switch_ComM_UMxxx_currentMode()                 **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00011   */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PncUserLowestMode(uint8 userIndx)
{
   /* @Trace: ComM_SUD_API_189 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* variable to store the Channel ID from ComM_ChnPncInxArr */
  NetworkHandleType handleChnlId;
  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Variable to store the Total No. of Channels of the User */
  uint8 noOfChannels;

  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 userChannelIndex;

  /* The Variable to store Channel Index */
  uint8 chnInd;
  #endif

  /* variable to store the total No of PNCS associated with User */
  uint16 pncCnt;

  /* variable to store the start index of ComM_PncUserInxArr for a User*/
  PNCHandleType pncIx;

  /* variable to store pnc index from the respective users */
  PNCHandleType pncIndex;

  /* variable to store the Channel Count from pnc */
  uint8 chnlCnt;

  /* variable to store the start channel index from pnc */
  uint8 chnlInx;

  /* variable to store the index */
  NetworkHandleType handleChnlIndex;

  #if (COMM_RTE_NOTIF == STD_ON)
   Rte_PortHandle_ComM_CurrentMode_P comMRteMode;

  /* Lowest mode requested by user (No-Slient-Full)*/
  ComM_ModeType lowestMode;

  /* Initialize to Full communication */
  lowestMode = COMM_FULL_COMMUNICATION;

  /* Initialization to pointer to function */
  comMRteMode =
    (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();
  #endif

  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Get the No of User Direct channels */
  /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "userIndx value and ComM_Users are generated by Tcode and has checked manual and it is not having any impact" */
  /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "userIndx value and ComM_Users are generated by Tcode and has checked manual and it is not having any impact" */
  /* polyspace-begin RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  noOfChannels = ComM_Users[userIndx].NoOfDirectChannels; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "userIndx value and ComM_Users are generated by Tcode and has checked manual and it is not having any impact" */
  /* polyspace-end RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */

  /* Get the Direct channels Index */
  userChannelIndex = ComM_Users[userIndx].DirectChannelIndex;
  #endif

  /* Get the total No of PNCS associated with User when all related features are supported*/
  pncCnt = ComM_Users[userIndx].NoOfPncs;

  /* Get the start PNC Index */
  pncIx = ComM_Users[userIndx].PncUserIndex;
  /*PNC loop to channel Loop */
  while (pncCnt != COMM_ZERO)
  {
    /* Decrement the pnc count */
    pncCnt--;

    /* Get the index from the user */
    pncIndex = ComM_PncUserInxArr[pncIx];

    /* Get the Channel Count from pnc */
    chnlCnt = ComM_Pncs[pncIndex].NoOfChannelPnc;

    /* Get the start channel index from pnc */
    chnlInx = ComM_Pncs[pncIndex].ChannelPncIndex;
    while (chnlCnt != COMM_ZERO)
    {
      chnlCnt--;

      /*
       * Note: pnc Index array provides ID of the channel
       * variable to store the channel ID
       */
      handleChnlId = ComM_ChnPncInxArr[chnlInx];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

      /* variable to store the channel index  */
      handleChnlIndex = ComM_ChannelMapArray[handleChnlId];
      #else
      handleChnlIndex = handleChnlId;
      #endif

      if (COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
      {
         /* @Trace: ComM_SUD_API_190 */
        /* Get the lowest mode */
        #if (COMM_RTE_NOTIF == STD_ON)
        lowestMode = COMM_NO_COMMUNICATION;
        #endif
        /* Break from while: channel */
        chnlCnt = COMM_ZERO;
        /* Break from while: PNC */
        pncCnt = COMM_ZERO;
        #if (COMM_DIRECT_CHANNEL == STD_ON)
        /* Break from while: direct channel */
        noOfChannels = COMM_ZERO;
        #endif
      } /* End of if (COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
        */
      else
      {
         /* @Trace: ComM_SUD_API_191 */
        /* Check for Silent communication */
        if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
        {
          /* @Trace: ComM_SUD_API_192 */
          /* Get the lowest mode */
          #if (COMM_RTE_NOTIF == STD_ON)
          lowestMode = COMM_SILENT_COMMUNICATION;
          #endif
        }
        /* Check next channel associated with the same PNC */
        chnlInx++;
      } /* End of else */
    }
    pncIx++;
  }

  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /* Direct channel Loop */
  while (noOfChannels != COMM_ZERO)
  {
    /* Decrement the direct channel count */
    noOfChannels--;

    /* Get the channel index  */
    chnInd = ComM_ChnInxArr[userChannelIndex];

    if (COMM_NO_COMMUNICATION == ComM_CurComMode[chnInd])
    {
      /* @Trace: ComM_SUD_API_193 */
      /* Get the lowest mode */
      #if (COMM_RTE_NOTIF == STD_ON)
      lowestMode = COMM_NO_COMMUNICATION;
      #endif

      /* Break from while */
      noOfChannels = COMM_ZERO;
    }
    else
    {
      /* @Trace: ComM_SUD_API_194 */
      /* Check for Silent communication */
      if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[chnInd])
      {
        /* @Trace: ComM_SUD_API_195 */
        /* Get the lowest mode */
        #if (COMM_RTE_NOTIF == STD_ON)
        lowestMode = COMM_SILENT_COMMUNICATION;
        #endif
      }
      /* Check next channel associated with the same user */
      userChannelIndex++;
    } /* End of else */
  }

  #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

  /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
  #if (COMM_RTE_NOTIF == STD_ON)
  if (NULL_PTR != comMRteMode[userIndx].Switch_currentMode)
  {
    /* @Trace: ComM_SUD_API_196 */
    comMRteMode[userIndx].Switch_currentMode(lowestMode);
  }
  #endif

  #else
  /* ========================== Implement for Post-Build ==================== */
  if (COMM_TRUE == ComM_PncEnabledFlashPB)
  {
    /* @Trace: ComM_SUD_API_197 */
    /* variable to store the Channel ID from ComM_ChnPncInxArr */
    NetworkHandleType handleChnlId;
    #if (COMM_DIRECT_CHANNEL == STD_ON)
    /* Variable to store the Total No. of Channels of the User */
    uint8 noOfChannels;
    /* Index to the channel Id's in the ChannelIndex Array */
    uint8 userChannelIndex;
    /* The Variable to store Channel Index */
    uint8 chnInd;
    #endif

    /* variable to store the total No of PNCS associated with User */
    uint16 pncCnt;
    /* variable to store the start PNC Index */
    PNCHandleType pncIx;
    /* variable to store index from the respective users */
    PNCHandleType pncIndex;
    /* variable to store the Channel Count from pnc */
    uint8 chnlCnt;
    /* variable to store the start channel pncIndex from pnc */
    uint8 chnlInx;
    /* variable to store the index */
    NetworkHandleType handleChnlIndex;

    #if (COMM_RTE_NOTIF == STD_ON)
    Rte_PortHandle_ComM_CurrentMode_P comMRteMode;
    /* Lowest mode requested by user (No-Slient-Full)*/
    ComM_ModeType lowestMode;
    /* Initialize to Full communication */
    lowestMode = COMM_FULL_COMMUNICATION;
    /* Initialization to pointer to function */
    comMRteMode =
      (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();
    #endif

    #if (COMM_DIRECT_CHANNEL == STD_ON)
    /* Get the No of User Direct channels */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
    noOfChannels = ComM_Users[userIndx].NoOfDirectChannels; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "userIndx value and ComM_Users are generated by Tcode and has checked manual and it is not having any impact" */
    /* polyspace-end RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
    /* Get the Direct channels Index */
    userChannelIndex = ComM_Users[userIndx].DirectChannelIndex;
    #endif

    /* Get the total No of PNCS associated with User*/
    /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "the value of  ComM_UserPNCRelatedGlobal are generated by Tcode and has checked manual and it is not having any impact" */
    pncCnt = ComM_UserPNCRelatedGlobal[userIndx].NoOfPncs;
    /* Get the start PNC Index */
    pncIx = ComM_UserPNCRelatedGlobal[userIndx].PncUserIndex;
    /*PNC loop to channel Loop */
    while (pncCnt != COMM_ZERO)
    {
      /* Decrement the pnc count */
      pncCnt--;
      /* Get the index from the user */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      pncIndex = ComM_PncUserInxArrGlobal[pncIx];
      /* Get the Channel Count from pnc */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      chnlCnt = ComM_PncsGlobal[pncIndex].NoOfChannelPnc;
      /* Get the start channel index from pnc */
      chnlInx = ComM_PncsGlobal[pncIndex].ChannelPncIndex;
      while (chnlCnt != COMM_ZERO)
      {
        chnlCnt--;
        /*
        * Note: pnc Index array provides ID of the channel
        * variable to store the channel ID
        */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        handleChnlId = ComM_ChnPncInxArrGlobal[chnlInx];
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        /* variable to store the channel index  */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        handleChnlIndex = ComM_ChannelMapArray[handleChnlId];
        #else
        handleChnlIndex = handleChnlId;
        #endif

        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        if (COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
        {
          /* @Trace: ComM_SUD_API_198 */
          /* Get the lowest mode */
          #if (COMM_RTE_NOTIF == STD_ON)
          lowestMode = COMM_NO_COMMUNICATION;
          #endif
          /* Break from while: channel */
          chnlCnt = COMM_ZERO;
          /* Break from while: PNC */
          pncCnt = COMM_ZERO;
          #if (COMM_DIRECT_CHANNEL == STD_ON)
          /* Break from while: direct channel */
          noOfChannels = COMM_ZERO;
          #endif
        } /* End of if (COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
          */
        else
        {
          /* @Trace: ComM_SUD_API_199 */
          /* Check for Silent communication */
          if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
          {
            /* @Trace: ComM_SUD_API_200 */
            /* Get the lowest mode */
            #if (COMM_RTE_NOTIF == STD_ON)
            lowestMode = COMM_SILENT_COMMUNICATION;
            #endif
          }
          /* Check next channel associated with the same PNC */
          chnlInx++;
        } /* End of else */
      }
      pncIx++;
    }

    #if (COMM_DIRECT_CHANNEL == STD_ON)
    /* Direct channel Loop */
    while (noOfChannels != COMM_ZERO)
    {
      /* Decrement the direct channel count */
      noOfChannels--;
      /* Get the channel index  */
      chnInd = ComM_ChnInxArr[userChannelIndex];

      if (COMM_NO_COMMUNICATION == ComM_CurComMode[chnInd])
      {
        /* @Trace: ComM_SUD_API_201 */
        /* Get the lowest mode */
        #if (COMM_RTE_NOTIF == STD_ON)
        lowestMode = COMM_NO_COMMUNICATION;
        #endif
        /* Break from while */
        noOfChannels = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_202 */
        /* Check for Silent communication */
        if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[chnInd])
        {
          /* @Trace: ComM_SUD_API_203 */
          /* Get the lowest mode */
          #if (COMM_RTE_NOTIF == STD_ON)
          lowestMode = COMM_SILENT_COMMUNICATION;
          #endif
        }
        /* Check next channel associated with the same user */
        userChannelIndex++;
      } /* End of else */
    }

    #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

    /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
    #if (COMM_RTE_NOTIF == STD_ON)
    if (NULL_PTR != comMRteMode[userIndx].Switch_currentMode)
    {
      /* @Trace: ComM_SUD_API_204 */
      comMRteMode[userIndx].Switch_currentMode(lowestMode);
    }
    #endif
  }
  else /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
  {
    /* @Trace: ComM_SUD_API_205 */
    /* Do nothing */
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PncUserLowestMode */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  (COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  * STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_ComSignalReception                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall save EIRA and ERAn Signals of PNC**
**                        as indicated by Com Module                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : signalId, comSignalRxPtr                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_Pncs,ComM_ComSignal,ComM_PncRxEIRA             **
**                        ComM_PncRxEIRASignal,ComM_PncRxERASignal,           **
**                        ComM_PncRxERAn                                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00013 SRS_ComM_AR_00014 SRS_ComM_AR_00016
 * SRS_ComM_AR_00024 SRS_ComM_AR_00025 SRS_ComM_AR_00010
*/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#if (((COMM_PNC_EIRA_SIGNAL_PRESENT == STD_ON) ||\
  (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)) &&\
  (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_ComSignalReception(Com_SignalIdType signalId,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) comSignalRxPtr )
{
  /* @Trace: ComM_SUD_API_139 */
  /* Variable to Store the Count of Total Signals */
  uint16 comSignalCnt;

  /* Variable to Store the Signal start Instance*/
  uint16 signalInst;

  /* Variable to store Bit Index of PNC */
  uint8 bitIndex;

  /* Variable to store Byte Index of PNC */
  uint8 byteIndex;

  /* Variable to store PNC Index*/
  PNCHandleType handlePncIndex;

  /* Variable to store the PNC Identifier*/
  PNCHandleType tmpPncId;

  #if (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)
  /* Variable to store Signal Kind {EIRA/ERA} */
  uint8 signalKind;
  #endif

  /* Variable to store Signal Direction {EIRA/ERA} */
  uint8 signalDxn;

  /*Variable to store Mask Value for the bit Index*/
  uint8 mask;

  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;

  /* Init value for number of COmM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;

  for (handlePncIndex = COMM_ZERO; handlePncIndex < COMM_TOTAL_PNCS;
    handlePncIndex++)
  {
    #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
    /* ======================== Implement for Pre-Compile =================== */
        /*Calculating the PNC ID for the Pnc Index*/
    tmpPncId = ComM_Pncs[handlePncIndex].PncId;
    /* Count of Total Signal with this PNC */
    comSignalCnt = ComM_Pncs[handlePncIndex].NoOfComSignal;
    /* Start Index of the Signal Instance within this PNC */
    signalInst = ComM_Pncs[handlePncIndex].ComSignalIndex;
    #else
    /* ======================== Implement for Post-Build ==================== */
    /*Calculating the PNC ID for the Pnc Index*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    tmpPncId = ComM_PncsGlobal[handlePncIndex].PncId;
    /* Count of Total Signal with this PNC */
    comSignalCnt = ComM_PncsGlobal[handlePncIndex].NoOfComSignal;
    /* Start Index of the Signal Instance within this PNC */
    signalInst = ComM_PncsGlobal[handlePncIndex].ComSignalIndex;
    #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */

    /*Traversing whole signals of the PNC*/
    while (comSignalCnt != COMM_ZERO)
    {
      comSignalCnt--;

      if (signalId == ComM_ComSignal[signalInst].ComMComSigId)
      {
        /* @Trace: ComM_SUD_API_140 */

        #if (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)
        /* Com Signal Kind */
        signalKind = ComM_ComSignal[signalInst].ComMPncComSignalKind;
        #endif

        /* Com Signal Direction */
        signalDxn = ComM_ComSignal[signalInst].ComMPncComSigDir;

        if (COMM_RX == signalDxn)
        {
          /*
           * Same SignalHandleId is not present in PNC more than once
           * Signal search is over : Break From Loop
           */
          comSignalCnt = COMM_ZERO;
          /*Calculation Of Byte Index*/
          /* Traceable SWS_ComM_00825 */
          /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
                                     ComM_ComSignal[signalInst].ComMPncVectorOffset;
      
          /*Calculation Of Bit Index within the Byte */
          bitIndex = (uint8)(tmpPncId % COMM_EIGHT);
      
          /*Calculating the Mask Value for the bit Index*/
          mask = (uint8)(COMM_ONE << bitIndex);

          #if (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)
          /* EIRA is Received : Rx EIRA in a PNC */
          if (COMM_EIRA == signalKind)
          #endif
          {
            /* @Trace: ComM_SUD_API_141 */
            /* polyspace +4 RTE:NIV [Not a defect:Low] "This variable is initialized by caller function since checked manually. It has no impact." */
            /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
            if (COMM_ZERO == (comSignalRxPtr[byteIndex] & mask))
            {
              /* @Trace: ComM_SUD_API_142 */
              /* Clear PNC EIRA Signal Instance*/
              ComM_PncRxEIRASignal[(handlePncIndex*noOfComMSignal) + signalInst]
                = COMM_FALSE;
            }
            else
            {
              /* @Trace: ComM_SUD_API_143 */
              ComM_PncRxEIRA[handlePncIndex] = COMM_TRUE;

              /* Set PNC EIRA Signal Instance*/
              ComM_PncRxEIRASignal[(handlePncIndex*noOfComMSignal) + signalInst]
                = COMM_TRUE;
            }
          }
          #if (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)
          #if (COMM_PNC_GW_ENABLED == STD_ON)
          else /* ERA is Received: n ERA in a PNC */
          {
            /* @Trace: ComM_SUD_API_144 */
            /* polyspace +4 RTE:NIV [Not a defect:Low] "This variable is initialized by caller function since checked manually. It has no impact." */
            /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
            if (COMM_ZERO == (comSignalRxPtr[byteIndex] & mask))
            {
              /* @Trace: ComM_SUD_API_145 */
              /* The ERA Received for Signal Instance : COMM_FALSE */
              ComM_PncRxERASignal[(handlePncIndex*noOfComMSignal) + signalInst]
                = COMM_FALSE;
            }
            else
            {
              /* @Trace: ComM_SUD_API_146 */
              ComM_PncRxERAn[handlePncIndex] = COMM_TRUE;

              /* The ERA Received for Signal Instance : COMM_TRUE */
              ComM_PncRxERASignal[(handlePncIndex*noOfComMSignal) + signalInst]
                = COMM_TRUE;
            }
          } /* End of if (COMM_EIRA == signalKind) */
          #endif /* End of #if (COMM_PNC_GW_ENABLED == STD_ON) */
          #endif /* End of #if (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON) */
        }
        else
        {
          /* @Trace: ComM_SUD_API_147 */
          /* Do Nothing : To Avoid MISRA C */
        }
      } /* End of if (signalId == ComM_ComSignal[signalInst].ComMComSigId) */
      else
      {
        /* @Trace: ComM_SUD_API_148 */
        signalInst++;
      }
    }
  }
} /* End of ComM_ComSignalReception */

#endif /* End of #if (((COMM_PNC_EIRA_SIGNAL_PRESENT == STD_ON) ||\
  (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)) &&\
  (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON)) */
#endif /* End of #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  (COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  * STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_RequestComModeDirectChnl                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update RTE about the user request**
**                        for Full communication of direct channels using API **
**                        ComM_RequestComMode                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userInx, comMode                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Users, ComM_RequestedComMode,                  **
**                        ComM_ChnInxArr, ComM_ReqedComModeCnt                **
**                        ComM_Channels, ComM_TimeCnt                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_RequestComModeRteUpdate()                      **
**                        ComM_RequestComModeInhibitionCheck()                **
**                        SchM_Enter_ComM_REQ_MODECNT_PROTECTION()            **
**                        SchM_Exit_ComM_REQ_MODECNT_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09078 SRS_BSW_00331 SRS_BSW_00369 SRS_BSW_00441
 * SRS_ComM_AR_00004 SRS_ComM_AR_00109 SRS_ComM_AR_00121   */
#if (COMM_DIRECT_CHANNEL == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModeDirectChnl(uint8
  userInx, ComM_ModeType comMode)
{
   /* @Trace: ComM_SUD_API_206 */
  /* Function Return Variable */
  Std_ReturnType returnValue;

  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 noOfChannels;

  /* Index to the ComM_ChnInxArr/ComM_ChnPncInxArr Array */
  uint8 channelIndex;

  /* Variable to store the channel Index */
  uint8 chIndex;

  /* Flag to check FULL/NO communication request is stored in global variable */
  uint8 comModeReqFlag;

  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  boolean inhibitionRetVal;
  #endif

  /* Initialize the request variable to predefined value */
  comModeReqFlag = COMM_ZERO;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;
  /*
   * Note: Direct channel may be Present in case of PNC ENABLED
   * Number of Direct Channel linked to the User
   */
  /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  noOfChannels = ComM_Users[userInx].NoOfDirectChannels;

  /* Index in the Direct Channel Index array in the User */
  channelIndex = ComM_Users[userInx].DirectChannelIndex;
  while (noOfChannels != COMM_ZERO)
  {
    /* Get the Channel index from the Channel Index Array */
    chIndex = ComM_ChnInxArr[channelIndex];

    /* Decrement the Channel */
    noOfChannels--;
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    inhibitionRetVal =
      ComM_RequestComModeInhibitionCheck(chIndex, comMode);

    /* If no inhibition is set */
    if (COMM_FALSE == inhibitionRetVal)
    #endif
    {
       /* @Trace: ComM_SUD_API_207 */
      /* Enter in Data Protection */
      SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

      if (COMM_FULL_COMMUNICATION == comMode)
      {
         /* @Trace: ComM_SUD_API_208 */
        /* If the previous request of that user is not
         *   Full communication */
        if (COMM_FULL_COMMUNICATION != ComM_RequestedComMode[userInx])
        {
           /* @Trace: ComM_SUD_API_209 */
          /* Load the Requested Full Com Mode into the User
           *   Requested Com mode array */
          ComM_RequestedComMode[userInx] =
            COMM_FULL_COMMUNICATION;

          /* Flag to know that the user has requested only once */
          comModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
        }
        /* Back to no com by limit to no com and then request full com */
        else if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
        {
          /* Flag to know that the user has requested only once */
          comModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
        }
        else
        {
          /* Do nothing */
        }
      } /* End of if (comMode == COMM_FULL_COMMUNICATION) */
      else if (COMM_NO_COMMUNICATION != ComM_RequestedComMode[userInx])
      {
         /* @Trace: ComM_SUD_API_210 */
        /* Load the Requested No Com Mode into the User
         *   Requested Com mode array
         */
        ComM_RequestedComMode[userInx] = COMM_NO_COMMUNICATION;

        /* Flag to know that the user has requested only once */
        comModeReqFlag = COMM_NOCOMMREQ_ACCPTD;
      }
      else
      {
         /* @Trace: ComM_SUD_API_211 */
        /* To avoid MISRA warning */
      }
      /* If the user request was accepted */
      if (COMM_FULLCOMMREQ_ACCPTD == comModeReqFlag)
      {
         /* @Trace: ComM_SUD_API_212 */
        /* Load the Requested ComMode in the Array */
        if (ComM_ReqedComModeCnt[chIndex] < COMM_REQEDCOMMODECNT_MAX)
        {
          ComM_ReqedComModeCnt[chIndex]++;
        }
        #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
        (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

        /* Stop the timer if there is user request when there is no NM
         *   available
         */
        ComM_TimeCnt[chIndex] = (ComM_TimeType)COMM_ZERO;
        #endif
      }
      else if (COMM_NOCOMMREQ_ACCPTD == comModeReqFlag)
      {
         /* @Trace: ComM_SUD_API_213 */
        /* Load the Requested ComMode in the Array */
        if (ComM_ReqedComModeCnt[chIndex] > COMM_ZERO)
        {
          ComM_ReqedComModeCnt[chIndex]--;
        }
      }
      else
      {
         /* @Trace: ComM_SUD_API_214 */
        /* To avoid MISRA warning */
      }
      /* Exit data protection */
      SchM_Exit_ComM_REQ_MODECNT_PROTECTION();

      /* Next Channel Index */
      channelIndex++;
      #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
        (COMM_DIRECT_USER_MAPPING == STD_OFF))

      /* Update Rte with the user who has requested the channel */
      if (COMM_TRUE == ComM_Channels[chIndex].FullCommReqNotifEn)
      {
         /* @Trace: ComM_SUD_API_215 */
        ComM_RequestComModeRteUpdate(chIndex, userInx, comMode);
      }
      #endif
    }
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    else
    {
       /* @Trace: ComM_SUD_API_216 */
      returnValue = COMM_E_MODE_LIMITATION;
    }
    #endif
  } /* End of while (noOfChannels != COMM_ZERO) */

  return (returnValue);
} /* End of ComM_RequestComModeDirectChnl */
#endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_GetCurComModeDirectChnl                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Lowest mode of direct     **
**                        channels for the API ComM_GetCurComMode             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userChannelIndex, noOfChannels, lowestMode          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : returnValue                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChnInxArr, ComM_Channels,                      **
**                        ComM_CurComMode, ComM_SMGetCurComModeFun            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanSM_GetCurrentComMode(), LinSM_GetCurrentComMode()**
**                        FrSM_GetCurrentComMode(), EthSM _GetCurrentComMode()**
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09172 SRS_ComM_AR_00122 SRS_ComM_AR_00158 SRS_ComM_AR_00159
 * SRS_ComM_AR_00160 SRS_ComM_AR_00164  */
#if (COMM_DIRECT_CHANNEL == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurComModeDirectChnl(uint8
  userChannelIndex, uint8 noOfChannels, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA) lowestMode)
{
  /* @Trace: ComM_SUD_API_150 */
  /* The variable to get the direct channel Index */
  uint8 channelIndex;

  Std_ReturnType returnValue;
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* Pointer to load the current mode of respective SM */
  ComM_ModeType modePtr;

  modePtr = COMM_NO_COMMUNICATION;
  #endif

  /* The variable to get userChannelIndex for avoid MISRA 17.8 */
  uint8 userChannelIndexTemp;
  /* The variable to get noOfChannels for avoid MISRA 17.8 */
  uint8 noOfChannelsTemp;

  /* Initialize userChannelIndexTemp value */
  userChannelIndexTemp = userChannelIndex;
  /* Initialize noOfChannelsTemp value */
  noOfChannelsTemp = noOfChannels;

  /*Initialize the Return value*/
  returnValue = E_OK;
  /* Check the Current Communication Mode of the Each Direct channel */
  while (noOfChannelsTemp != COMM_ZERO)
  {
    /* Get the Channel from Index Array */
    channelIndex = ComM_ChnInxArr[userChannelIndexTemp];

    /* Decrement the Number of channels */
    noOfChannelsTemp--;
    {
      #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
      #if (COMM_INTERNALBUS_PRESENT == STD_ON)
      if (COMM_INTERNAL != ComM_Channels[channelIndex].BusType)
      #endif
      {
        /* @Trace: ComM_SUD_API_151 */
        /* Check the SM channel mode*/
        (void) ComM_SMGetCurComModeFun[ComM_Channels[channelIndex].
            BusType](ComM_Channels[channelIndex].ChannelId, &modePtr);
        /* Check the current Communication Mode */
        if (COMM_NO_COMMUNICATION == modePtr)
        {
          /* @Trace: ComM_SUD_API_152 */
          /* Get the lowest mode */
          *lowestMode = COMM_NO_COMMUNICATION;

          /* Break from while */
          noOfChannelsTemp = COMM_ZERO;
        }
        else
        {
          /* @Trace: ComM_SUD_API_153 */
          /* Check for Silent comm */
          if (COMM_SILENT_COMMUNICATION == modePtr)
          {
            /* @Trace: ComM_SUD_API_154 */
            /* Get the lowest mode */
            *lowestMode = COMM_SILENT_COMMUNICATION;
            userChannelIndexTemp++;
          }
          else
          {
            /* @Trace: ComM_SUD_API_155 */
            /* Check the next channel associated with the user */
            userChannelIndexTemp++;
          }
        } /* End of else */
      } /* End of if (ComM_Channels[channelIndex].BusType !=
         * COMM_INTERNAL) */
      #if (COMM_INTERNALBUS_PRESENT == STD_ON)
      else
      #endif
      #endif /* End of if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
      #if (COMM_INTERNALBUS_PRESENT == STD_ON)
      {
        /* @Trace: ComM_SUD_API_156 */
        /* Check the current CommunicationMode */
        if (COMM_NO_COMMUNICATION == ComM_CurComMode[channelIndex])
        {
          /* @Trace: ComM_SUD_API_157 */
          /* Get the lowest mode */
          *lowestMode = COMM_NO_COMMUNICATION;

          /* Break from while */
          noOfChannelsTemp = COMM_ZERO;
        }
        else
        {
          /* @Trace: ComM_SUD_API_158 */
          /* Check for Silent comm */
          if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[channelIndex])
          {
            /* @Trace: ComM_SUD_API_159 */
            /* Get the lowest mode */
            *lowestMode = COMM_SILENT_COMMUNICATION;
            userChannelIndexTemp++;
          }
          else
          {
            /* @Trace: ComM_SUD_API_160 */
            userChannelIndexTemp++;
          }
        } /* End of else */
      }
      #endif
    }
  }

  return (returnValue);
} /* End of ComM_GetCurComModeDirectChnl*/
#endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_PNCFullModeRequested                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the PNC_FULL_COMMUNICATION **
**                        sub state COMM_PNC_REQUESTED                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : tmpPncIndex                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Pncs, ComM_PncRxERASignal,                     **
**                        ComM_PncRxERAn, ComM_SubPNCMode,                    **
**                        ComM_ReqToReadyFlag                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00010 SRS_ComM_AR_00043 SRS_ComM_AR_00016
 * SRS_ComM_AR_00022 SRS_ComM_AR_00044 SRS_ComM_AR_00045 SRS_ComM_AR_00046
 * SRS_ComM_AR_00047 SRS_ComM_AR_00168   */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PNCFullModeRequested(PNCHandleType tmpPncIndex)
{
  /* @Trace: ComM_SUD_API_569 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if (COMM_PNC_GW_ENABLED == STD_ON)
  /* variable to store the count of signals */
  uint16 noOfSignals;

  /* variable to store the start instance of signal container */
  uint16 signalInsIndex;
  /* flag for ERA vector */
  boolean eranFlag;

  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;

  /* Init value for number of COmM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;

  /* Initialize the condition of ERAn*/
  eranFlag = COMM_FALSE;

  /* Get the Com Signals associated with the PNC*/
  noOfSignals = ComM_Pncs[tmpPncIndex].NoOfComSignal;

  /*Com Signal Instance Index */
  signalInsIndex = ComM_Pncs[tmpPncIndex].ComSignalIndex;
  while (noOfSignals != COMM_ZERO)
  {
    if (COMM_TRUE ==
      ComM_PncRxERASignal[(tmpPncIndex*noOfComMSignal) + signalInsIndex])
    {
      /* @Trace: ComM_SUD_API_570 */
      /* set ERA flag */
      eranFlag = COMM_TRUE;
      /* Condition to break From Loop: ERAn is !COMM_ZERO */
      noOfSignals = COMM_ZERO;
    }
    else
    {
      /* @Trace: ComM_SUD_API_571 */
      /* Decrement the Number of channels */
      noOfSignals--;
    }
    /* Increment the channel Index*/
    signalInsIndex++;
  } /* End of while (noOfSignals != COMM_ZERO) */

  /* Check for PNC state Change to : COMM_PNC_READY_SLEEP */
  if (COMM_TRUE != eranFlag)
  {
    /* @Trace: ComM_SUD_API_572 */
    /* Change status for RxERA */
    ComM_PncRxERAn[tmpPncIndex] = COMM_FALSE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_573 */
    /* do nothing */
  }

  /* Traceable SWS_ComM_00966 */
  #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
  /* Check if all user request no com and all RxERA set to zero */
  if ((PNC_USER_NO_COMM == ComM_RequestedPNCMode[tmpPncIndex]) &&
    (COMM_FALSE == ComM_PncRxERAn[tmpPncIndex]))
  {
    /* @Trace: ComM_SUD_API_574 */
    /* set flag release channel assigned to this pnc */
    ComM_ReleaseFlag[tmpPncIndex] = COMM_TRUE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_575 */
    /* do nothing */
  }
  #endif /*End of #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON) */
  #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

  /* Condition to Enter : COMM_PNC_READY_SLEEP */
  /* Traceable SWS_ComM_00991 */
  if ((PNC_USER_NO_COMM == ComM_RequestedPNCMode[tmpPncIndex])
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    && (!(COMM_TRUE == ComM_PncRxERAn[tmpPncIndex]))
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_576 */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_READY_SLEEP;

    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
      COMM_PNC_READY_SLEEP);

    /* Set the Flag */
    ComM_ReqToReadyFlag[tmpPncIndex] = COMM_TRUE;
  }

  #else
  /* ========================== Implement for Post-Build ==================== */
  #if (COMM_PNC_GW_ENABLED == STD_ON)
  /* variable to store the count of signals */
  uint16 noOfSignals;
  /* variable to store the start instance of signal container */
  uint16 signalInsIndex;
  /* flag for ERA vector */
  boolean eranFlag;
  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;
  /* Init value for number of COmM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;
  /* Initialize the condition of ERAn*/
  eranFlag = COMM_FALSE;
  /* Get the Com Signals associated with the PNC*/
  /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  noOfSignals = ComM_PncsGlobal[tmpPncIndex].NoOfComSignal;

  /* Com Signal Instance Index */
  signalInsIndex = ComM_PncsGlobal[tmpPncIndex].ComSignalIndex;
  while (noOfSignals != COMM_ZERO)
  {
    /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if (COMM_TRUE ==
      ComM_PncRxERASignal[(tmpPncIndex*noOfComMSignal) + signalInsIndex])
    {
      /* @Trace: ComM_SUD_API_578 */
      /* set ERA flag */
      eranFlag = COMM_TRUE;
      /* Condition to break From Loop: ERAn is !COMM_ZERO */
      noOfSignals = COMM_ZERO;
    }
    else
    {
      /* @Trace: ComM_SUD_API_579 */
      /* Decrement the Number of channels */
      noOfSignals--;
    }
    /* Increment the channel Index*/
    signalInsIndex++;
  } /* End of while (noOfSignals != COMM_ZERO) */

  /* Check for PNC state Change to : COMM_PNC_READY_SLEEP */
  if (COMM_TRUE != eranFlag)
  {
    /* @Trace: ComM_SUD_API_580 */
    /* Change status for RxERA */
    ComM_PncRxERAn[tmpPncIndex] = COMM_FALSE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_581 */
    /* do nothing */
  }

  /* Traceable SWS_ComM_00966 */
  #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
  /* Check if all user request no com and all RxERA set to zero */
  if ((PNC_USER_NO_COMM == ComM_RequestedPNCMode[tmpPncIndex]) &&
    (COMM_FALSE == ComM_PncRxERAn[tmpPncIndex]))
  {
    /* @Trace: ComM_SUD_API_582 */
    /* set flag release channel assigned to this pnc */
    ComM_ReleaseFlag[tmpPncIndex] = COMM_TRUE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_583 */
    /* do nothing */
  }
  #endif /*End of #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON) */
  #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

  /* Condition to Enter : COMM_PNC_READY_SLEEP */
  /* Traceable SWS_ComM_00991 */
  if ((PNC_USER_NO_COMM == ComM_RequestedPNCMode[tmpPncIndex])
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    && (!(COMM_TRUE == ComM_PncRxERAn[tmpPncIndex]))
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_584 */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_READY_SLEEP;
    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                        COMM_PNC_READY_SLEEP);
    /* Set the Flag */
    ComM_ReqToReadyFlag[tmpPncIndex] = COMM_TRUE;
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCFullModeRequested */
/*******************************************************************************
** Function Name        : ComM_PNCFullModeReadySleep                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the PNC_FULL_COMMUNICATION **
**                        sub state COMM_PNC_READY_SLEEP                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : tmpPncIndex                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_RequestedPNCMode, ComM_PncRxERAn,              **
**                        ComM_SubPNCMode, ComM_ReqFlag, ComM_Pncs            **
**                        ComM_PncRxEIRASignal, ComM_PncRxEIRA                **
**                        ComM_ChnPncInxArr, ComM_ChannelMapArray,            **
**                        ComM_Channels, ComM_PncTimeCnt                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00022
 * SRS_ComM_AR_00047 SRS_ComM_AR_00048 SRS_ComM_AR_00049 SRS_ModeMgm_09246
 * SRS_ModeMgm_09247 SRS_ModeMgm_09248 SRS_ComM_AR_00168 SRS_ComM_AR_00168 */
FUNC(void, COMM_CODE) ComM_PNCFullModeReadySleep(PNCHandleType tmpPncIndex)
{
  /* @Trace: ComM_SUD_API_556 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* variable to store the count of signals */
  uint16 noOfSignals;

  /* variable to store the start instance of signal container */
  uint16 signalInsIndex;

  /* variable to store the Channel index from channel map array */
  uint8 chIndex;

  /* variable to store the count of channels */
  uint8 noOfChannels;

  /* variable to store the start index of channel from pnc */
  NetworkHandleType handleChnlIndex;

  /* variable to store the channel ID */
  NetworkHandleType handleId;

  /* variable to check EIRA conditions */
  boolean eiraFlag;

  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;

  /* Init value for number of COmM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;

  /* Initialize the EIRA Flag */
  eiraFlag = COMM_FALSE;

  /* Check for PNC state Change to : COMM_PNC_REQUESTED */
  /* Traceable SWS_ComM_00165 */
  if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex])
      #if (COMM_PNC_GW_ENABLED == STD_ON)
      || (COMM_TRUE == ComM_PncRxERAn[tmpPncIndex])
      #endif
      )
  {
    /* @Trace: ComM_SUD_API_557 */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_REQUESTED;

    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId, COMM_PNC_REQUESTED);

    /* Set the Flag */
    ComM_ReqFlag[tmpPncIndex] = COMM_TRUE;
  }
  /* If still state is COMM_PNC_READY_SLEEP : Check for EIRA == COMM_FALSE*/
  else
  {
    /* @Trace: ComM_SUD_API_558 */
    /* Get the Com Signals associated with the PNC*/
    noOfSignals = ComM_Pncs[tmpPncIndex].NoOfComSignal;

    /*Com Signal Instance Index */
    signalInsIndex = ComM_Pncs[tmpPncIndex].ComSignalIndex;
    while (noOfSignals != COMM_ZERO)
    {
      if (COMM_TRUE ==
        ComM_PncRxEIRASignal[(tmpPncIndex*noOfComMSignal) + signalInsIndex])
      {
        /* @Trace: ComM_SUD_API_559 */
        eiraFlag = COMM_TRUE;

        /* Condition to break From Loop: ERAn is !COMM_ZERO */
        noOfSignals = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_560 */
        /* Decrement the Number of channels */
        noOfSignals--;
      }
      /* Increment the channel Index*/
      signalInsIndex++;
    } /* End of while (noOfSignals != COMM_ZERO) */

    /* Check for PNC state Change to : COMM_PNC_PREPARE_SLEEP */
    if (COMM_TRUE != eiraFlag)
    {
      /* @Trace: ComM_SUD_API_561 */
      /* Reset the EIRA flag as the Channels of PNC has EIRA == COMM_FALSE */
      ComM_PncRxEIRA[tmpPncIndex] = COMM_FALSE;

      /* Indication to BswM Module about the Sub State */
      ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_PREPARE_SLEEP;

      /*Indication to BswM Module*/
      BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
        COMM_PNC_PREPARE_SLEEP);

      /* Get the Channels associated with the PNC*/
      noOfChannels = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;

      /*Channel Index */
      handleChnlIndex = ComM_Pncs[tmpPncIndex].ChannelPncIndex;
      while (noOfChannels != COMM_ZERO)
      {
        /* Get the Channel ID from PNC Index Array */
        handleId = ComM_ChnPncInxArr[handleChnlIndex];
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        chIndex = ComM_ChannelMapArray[handleId];
        #else
        chIndex = handleId;
        #endif

        /* Start the PNC Timer for the channel*/
        /* #13018 */
        ComM_PncTimeCnt[tmpPncIndex] =
          ComM_Channels[chIndex].PncPrepareSleepTimer;

        /* Decrement the Number of channels */
        noOfChannels--;

        /* Increment the channel Index */
        handleChnlIndex++;
      } /* End of while (noOfChannels != COMM_ZERO) */
    } /* End of if (COMM_TRUE != eiraFlag) */
  } /* End of else */
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* variable to store the count of signals */
  uint16 noOfSignals;
  /* variable to store the start instance of signal container */
  uint16 signalInsIndex;
  /* variable to store the Channel index from channel map array */
  uint8 chIndex;
  /* variable to store the count of channels */
  uint8 noOfChannels;
  /* variable to store the start index of channel from pnc */
  NetworkHandleType handleChnlIndex;
  /* variable to store the channel ID */
  NetworkHandleType handleId;
  /* variable to check EIRA conditions */
  boolean eiraFlag;
  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;
  /* Init value for number of COmM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;
  /* Initialize the EIRA Flag */
  eiraFlag = COMM_FALSE;
  /* Check for PNC state Change to : COMM_PNC_REQUESTED */
  /* Traceable SWS_ComM_00165 */
  if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex])
      #if (COMM_PNC_GW_ENABLED == STD_ON)
      || (COMM_TRUE == ComM_PncRxERAn[tmpPncIndex])
      #endif
      )
  {
    /* @Trace: ComM_SUD_API_563 */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_REQUESTED;
    /* Indication to BswM Module about the Sub State */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                          COMM_PNC_REQUESTED);
    /* Set the Flag */
    ComM_ReqFlag[tmpPncIndex] = COMM_TRUE;
  }
  /* If still state is COMM_PNC_READY_SLEEP : Check for EIRA == COMM_FALSE*/
  else
  {
    /* @Trace: ComM_SUD_API_564 */
    /* Get the Com Signals associated with the PNC*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    noOfSignals = ComM_PncsGlobal[tmpPncIndex].NoOfComSignal;
    /*Com Signal Instance Index */
    signalInsIndex = ComM_PncsGlobal[tmpPncIndex].ComSignalIndex;
    while (noOfSignals != COMM_ZERO)
    {
      /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      if (COMM_TRUE ==
        ComM_PncRxEIRASignal[(tmpPncIndex*noOfComMSignal) + signalInsIndex])
      {
        /* @Trace: ComM_SUD_API_565 */
        eiraFlag = COMM_TRUE;
        /* Condition to break From Loop: ERAn is !COMM_ZERO */
        noOfSignals = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_566 */
        /* Decrement the Number of channels */
        noOfSignals--;
      }
      /* Increment the channel Index*/
      signalInsIndex++;
    } /* End of while (noOfSignals != COMM_ZERO) */

    /* Check for PNC state Change to : COMM_PNC_PREPARE_SLEEP */
    if (COMM_TRUE != eiraFlag)
    {
      /* @Trace: ComM_SUD_API_567 */
      /* Reset the EIRA flag as the Channels of PNC has EIRA == COMM_FALSE */
      ComM_PncRxEIRA[tmpPncIndex] = COMM_FALSE;
      /* Indication to BswM Module about the Sub State */
      ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_PREPARE_SLEEP;
      /*Indication to BswM Module*/
      BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                      COMM_PNC_PREPARE_SLEEP);
      /* Get the Channels associated with the PNC*/
      noOfChannels = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
      /*Channel Index */
      handleChnlIndex = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;
      while (noOfChannels != COMM_ZERO)
      {
        /* Get the Channel ID from PNC Index Array */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        handleId = ComM_ChnPncInxArrGlobal[handleChnlIndex];
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        chIndex = ComM_ChannelMapArray[handleId];
        #else
        chIndex = handleId;
        #endif
        /* Start the PNC Timer for the channel*/
        /* #13018 */
  /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        ComM_PncTimeCnt[tmpPncIndex] =
                                    ComM_Channels[chIndex].PncPrepareSleepTimer;
        /* Decrement the Number of channels */
        noOfChannels--;
        /* Increment the channel Index */
        handleChnlIndex++;
      } /* End of while (noOfChannels != COMM_ZERO) */
    } /* End of if (COMM_TRUE != eiraFlag) */
  } /* End of else */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCFullModeReadySleep */

/*******************************************************************************
** Function Name        : ComM_PNCFullModePrepareSleep                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the PNC_FULL_COMMUNICATION **
**                        sub state COMM_PNC_PREPARE_SLEEP                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : tmpPncIndex                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_RequestedPNCMode, ComM_ChnPncInxArr,           **
**                        ComM_Pncs, ComM_PncRxERAn, ComM_SubPNCMode          **
**                        ComM_ReqFlag, ComM_ChannelMapArray,                 **
**                        ComM_PncTimeCnt, ComM_PncRxEIRA                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00022
 * SRS_ComM_AR_00050 SRS_ComM_AR_00051 SRS_ComM_AR_00052 SRS_ComM_AR_00053
*/
FUNC(void, COMM_CODE) ComM_PNCFullModePrepareSleep(PNCHandleType tmpPncIndex)
{
  /* @Trace: ComM_SUD_API_541 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* variable to store the count of channels */
  uint8 noOfChannels;

  /* variable to store the start index of channel from pnc */
  //NetworkHandleType handleChnlIndex;

  /* variable to store the track of COMM_PNC_NO_COMMUNICATION*/
  boolean pncNoComFlag;

  if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex])
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    || (COMM_TRUE == ComM_PncRxERAn[tmpPncIndex])
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_542 */
    /* Mode Changed: COMM_PNC_PREPARE_SLEEP to COMM_PNC_REQUESTED*/
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_REQUESTED;

    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
      COMM_PNC_REQUESTED);

    /* Set the Flag */
    ComM_ReqFlag[tmpPncIndex] = COMM_TRUE;

  } /* End if (ComM_RequestedPNCMode[tmpPncIndex] equals PNC_USER_FULL_COMM) */
  else if (COMM_TRUE == ComM_PncRxEIRA[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_543 */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_READY_SLEEP;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
      COMM_PNC_READY_SLEEP);
  } /* End of if (ComM_PncRxEIRA[tmpPncIndex] == COMM_TRUE) */
  /* If still the sub state is COMM_PNC_PREPARE_SLEEP */
  else
  {
    /* @Trace: ComM_SUD_API_544 */
    /* Get the Channels associated with the PNC */
    noOfChannels = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;

    /*Channel Index */
    //handleChnlIndex = ComM_Pncs[tmpPncIndex].ChannelPncIndex;

    /*Variable to check for condition : COMM_PNC_NO_COMMUNICATION */
    pncNoComFlag = COMM_FALSE;
    while (noOfChannels != COMM_ZERO)
    {
      /* Decrement the Number of channels */
      noOfChannels--;

      /* Check the timer status of each channel */
      /* #13018 */
      if (COMM_ZERO != ComM_PncTimeCnt[tmpPncIndex])
      {
        /* @Trace: ComM_SUD_API_545 */
        /* Set the Flag HIGH*/
        pncNoComFlag = COMM_TRUE;

        /* Break From Loop */
        noOfChannels = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_546 */
        /* Increment the channel Index */
        //handleChnlIndex++;
      }
    } /* End of while (noOfChannels != COMM_ZERO) */

    if (COMM_TRUE != pncNoComFlag)
    {
      /* @Trace: ComM_SUD_API_547 */
      /* switch PNC mode to no communication */
      ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_NO_COMMUNICATION;

      /* Indication to BswM Module */
      BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
        COMM_PNC_NO_COMMUNICATION);
    }
  } /* End of else */
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* variable to store the count of channels */
  uint8 noOfChannels;
  /* variable to store the start index of channel from pnc */
  //NetworkHandleType handleChnlIndex;
  /* variable to store the track of COMM_PNC_NO_COMMUNICATION*/
  boolean pncNoComFlag;

  if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex])
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    || (COMM_TRUE == ComM_PncRxERAn[tmpPncIndex])
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_549 */
    /* Mode Changed: COMM_PNC_PREPARE_SLEEP to COMM_PNC_REQUESTED*/
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_REQUESTED;
    /* Indication to BswM Module about the Sub State */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
          COMM_PNC_REQUESTED);
    /* Set the Flag */
    ComM_ReqFlag[tmpPncIndex] = COMM_TRUE;
  } /* End if (ComM_RequestedPNCMode[tmpPncIndex] == PNC_USER_FULL_COMM) */
  else if (COMM_TRUE == ComM_PncRxEIRA[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_550 */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_READY_SLEEP;
    /*Indication to BswM Module*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                        COMM_PNC_READY_SLEEP);
  } /* End of if (ComM_PncRxEIRA[tmpPncIndex] == COMM_TRUE) */
  /* If still the sub state is COMM_PNC_PREPARE_SLEEP */
  else
  {
    /* @Trace: ComM_SUD_API_551 */
    /* Get the Channels associated with the PNC */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    noOfChannels = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
    /*Channel Index */
    //handleChnlIndex = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;
    /*Variable to check for condition : COMM_PNC_NO_COMMUNICATION */
    pncNoComFlag = COMM_FALSE;
    while (noOfChannels != COMM_ZERO)
    {
      /* Decrement the Number of channels */
      noOfChannels--;
      /* Check the timer status of each channel */
      /* #13018 */
      if (COMM_ZERO != ComM_PncTimeCnt[tmpPncIndex])
      {
        /* @Trace: ComM_SUD_API_552 */
        /* Set the Flag HIGH*/
        pncNoComFlag = COMM_TRUE;
        /* Break From Loop */
        noOfChannels = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_553 */
        /* Increment the channel Index */
        //handleChnlIndex++;
      }
    } /* End of while (noOfChannels != COMM_ZERO) */

    if (COMM_TRUE != pncNoComFlag)
    {
      /* @Trace: ComM_SUD_API_554 */
      /* switch PNC mode to no communication */
      ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_NO_COMMUNICATION;
      /* Indication to BswM Module */
      BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
        COMM_PNC_NO_COMMUNICATION);
    }
  } /* End of else */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCFullModePrepareSleep */

/*******************************************************************************
** Function Name        : ComM_RequestComModePNC                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the requested communication**
**                        mode for the PNCs associated  with users            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userInx, comMode                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : returnValue                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_Users, ComM_PncUserInxArr, ComM_Pncs           **
**                        ComM_ChnPncInxArr, ComM_ChannelMapArray,            **
**                        ComM_RequestedComMode, ComM_ReqedComModeCnt,        **
**                        ComM_TimeCnt, ComM_Channels                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_RequestComModeInhibitionCheck()                **
**                        SchM_Enter_ComM_REQ_MODECNT_PROTECTION()            **
**                        SchM_Exit_ComM_REQ_MODECNT_PROTECTION()             **
**                        ComM_RequestComModeRteUpdate()                      **
**                        ComM_PncUserHandle()                                **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09089 SRS_ModeMgm_09078 SRS_ModeMgm_09085 SRS_BSW_00331
 * SRS_BSW_00369 SRS_BSW_00377 SRS_BSW_00441 SRS_ModeMgm_09081 SRS_ComM_AR_00004
 * SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00035 SRS_ComM_AR_00039
 * SRS_ComM_AR_00109 SRS_ComM_AR_00121
 */
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModePNC(uint8 userInx,
  ComM_ModeType comMode)
{
  /* @Trace: ComM_SUD_API_217 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* variable to store the Total No. of PNCs */
  uint16 noOfPncs;

  /* Variable to store the user pnc index */
  PNCHandleType tmpUserPNCIndex;

  /* Variable to store the pnc index */
  PNCHandleType tmpPncIndex;

  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 noOfChannels;

  /* Index to the ComM_ChnInxArr/ComM_ChnPncInxArr Array */
  NetworkHandleType handleChnlIndex;

  /* Variable to store the channel Index */
  uint8 chIndex;
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  boolean inhibitionRetVal;
  #endif

  /* Flag to check if full/no communication request is stored in global
   *   variable */
  #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
            (COMM_DIRECT_USER_MAPPING == STD_OFF))
  /* Variable to store the channel RTE Indication */
  boolean channelRteInd[COMM_TOTAL_CHANNELS];
  /* Variable to store the channel count for RTE Indication */
  uint8 tmpChannelCount;
  #endif

  /* Flag to check if full/no communication request is stored in global
   *   variable */
  uint8 comModeReqFlag;

  /* Function Return Variable */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;

  /* Initialize the request variable */
  comModeReqFlag = COMM_ZERO;

  #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
            (COMM_DIRECT_USER_MAPPING == STD_OFF))
  /* Initialize the Channel count */
  tmpChannelCount = COMM_TOTAL_CHANNELS;
  while (tmpChannelCount != COMM_ZERO)
  {
    tmpChannelCount--;
    channelRteInd[tmpChannelCount] = COMM_FALSE;
  }
  #endif

  /* Number of Pncs linked to the User */
  /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  noOfPncs = ComM_Users[userInx].NoOfPncs; /* polyspace RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */

  /* Pnc Index in the User */
  tmpUserPNCIndex = ComM_Users[userInx].PncUserIndex;
  while (noOfPncs != COMM_ZERO)
  {
    noOfPncs--;
    tmpPncIndex = ComM_PncUserInxArr[tmpUserPNCIndex];

    /* Number of Channel linked to the PNC */
    noOfChannels = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;

    /* Index in the Channel Index array in the PNC*/
    handleChnlIndex = ComM_Pncs[tmpPncIndex].ChannelPncIndex;
    while (noOfChannels != COMM_ZERO)
    {
      /* Decrement the Channel */
      noOfChannels--;

      /* Get the Channel ID from Index Array */
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      chIndex = ComM_ChannelMapArray[ComM_ChnPncInxArr[handleChnlIndex]];
      #else
      chIndex = ComM_ChnPncInxArr[handleChnlIndex];
      #endif

      #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
            (COMM_DIRECT_USER_MAPPING == STD_OFF))
      /* channelRteInd : To avoid multiple indication to RTE */
      if (COMM_TRUE != channelRteInd[chIndex])
      #endif
      {
        /* @Trace: ComM_SUD_API_218 */
        #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
        inhibitionRetVal =
          ComM_RequestComModeInhibitionCheck(chIndex, comMode);

        /* If no inhibition is set */
        if (COMM_FALSE == inhibitionRetVal)
        #endif
        {
          /* @Trace: ComM_SUD_API_219 */
          /* Enter in Data Protection */
          SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

          if (COMM_FULL_COMMUNICATION == comMode)
          {
            /* @Trace: ComM_SUD_API_220 */
            /* If the previous request of that user is not
             *   Full communication */
            if (COMM_FULL_COMMUNICATION != ComM_RequestedComMode[userInx])
            {
              /* @Trace: ComM_SUD_API_221 */
              /* Load the Requested Full Com Mode into the User
               *   Requested Com mode array */
              ComM_RequestedComMode[userInx] = COMM_FULL_COMMUNICATION;

              /* Flag to know that the user has requested only once */
              comModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
            }
            /* Back to no com by limit to no com and then request full com */
            else if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
            {
              /* Flag to know that the user has requested only once */
              comModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
            }
            else
            {
              /* Do nothing */
            }
          } /* End of if (comMode == COMM_FULL_COMMUNICATION) */
          else if (COMM_NO_COMMUNICATION != ComM_RequestedComMode[userInx])
          {
            /* @Trace: ComM_SUD_API_222 */
            /* Load the Requested No Com Mode into the User
             *   Requested Com mode array */
            ComM_RequestedComMode[userInx] = COMM_NO_COMMUNICATION;

            /* Flag to know that the user has requested only once */
            comModeReqFlag = COMM_NOCOMMREQ_ACCPTD;
          }
          else
          {
            /* @Trace: ComM_SUD_API_223 */
            /* To avoid MISRA warning */
          }

          /* If the user request was accepted */
          if (COMM_FULLCOMMREQ_ACCPTD == comModeReqFlag)
          {
            /* @Trace: ComM_SUD_API_224 */
            /* Load the Requested ComMode in the Array */
            if (ComM_ReqedComModeCnt[chIndex] < COMM_REQEDCOMMODECNT_MAX)
            {
              ComM_ReqedComModeCnt[chIndex]++;
            }
            #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
            (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

            /* Stop the timer if there is user request when there is no NM
             *   available */
            ComM_TimeCnt[chIndex] = (ComM_TimeType)COMM_ZERO;
            #endif
          }
          else if (COMM_NOCOMMREQ_ACCPTD == comModeReqFlag)
          {
            /* @Trace: ComM_SUD_API_225 */
            /* Load the Requested ComMode in the Array */
            if (ComM_ReqedComModeCnt[chIndex] > COMM_ZERO)
            {
              ComM_ReqedComModeCnt[chIndex]--;
            }
          }
          else
          {
            /* @Trace: ComM_SUD_API_226 */
            /* To avoid MISRA warning */
          }
          /* Exit data protection */
          SchM_Exit_ComM_REQ_MODECNT_PROTECTION();

          #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
            (COMM_DIRECT_USER_MAPPING == STD_OFF))
          /* Update Rte with the user who has requested the channel */
          if (COMM_TRUE == ComM_Channels[chIndex].FullCommReqNotifEn)
          {
            /* @Trace: ComM_SUD_API_227 */
            ComM_RequestComModeRteUpdate(chIndex, userInx, comMode);

            /* The RTE is indicated with Channel mode*/
            channelRteInd[chIndex] = COMM_TRUE;
          }
          /* The RTE is indicated with Channel mode*/
          #endif
        }
        #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
        else
        {
          /* @Trace: ComM_SUD_API_228 */
          /* Load Return Value with COMM_E_MODE_LIMITATION */
          returnValue = COMM_E_MODE_LIMITATION;
        }
        #endif
      } /* End of if (channelRteInd[chIndex] != COMM_TRUE) */
      handleChnlIndex++;
    } /* End of while (noOfChannels != COMM_ZERO) */

    /* PNC State changes associated  with the user */
    ComM_PncUserHandle(tmpPncIndex, comMode);
    tmpUserPNCIndex++;
  } /* End of while (noOfPncs != COMM_ZERO) */
  return (returnValue);

  #else
  /* ========================== Implement for Post-Build ==================== */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* variable to store the Total No. of PNCs */
    uint16 noOfPncs;
    /* Variable to store the user pnc index */
    PNCHandleType tmpUserPNCIndex;
    /* Variable to store the pnc index */
    PNCHandleType tmpPncIndex;
    /* variable to store the Total No. of Channels of the User/PNC */
    uint8 noOfChannels;
    /* Index to the ComM_ChnInxArr/ComM_ChnPncInxArr Array */
    NetworkHandleType handleChnlIndex;
    /* Variable to store the channel Index */
    uint8 chIndex;
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    boolean inhibitionRetVal;
    #endif

    /* Flag to check if full/no communication request is stored in global
    *   variable */
    #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
              (COMM_DIRECT_USER_MAPPING == STD_OFF))
    /* Variable to store the channel RTE Indication */
    boolean channelRteInd[COMM_TOTAL_CHANNELS];
    /* Variable to store the channel count for RTE Indication */
    uint8 tmpChannelCount;
    #endif

    /* Flag to check if full/no communication request is stored in global
    *   variable */
    uint8 comModeReqFlag;
    /* Function Return Variable */
    Std_ReturnType returnValue;
    /* Initialize the return variable to E_OK */
    returnValue = E_OK;
    /* Initialize the request variable */
    comModeReqFlag = COMM_ZERO;

    #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
              (COMM_DIRECT_USER_MAPPING == STD_OFF))
    /* Initialize the Channel count */
    tmpChannelCount = COMM_TOTAL_CHANNELS;
    while (tmpChannelCount != COMM_ZERO)
    {
      tmpChannelCount--;
      channelRteInd[tmpChannelCount] = COMM_FALSE;
    }
    #endif

    /* Number of Pncs linked to the User */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    noOfPncs = ComM_UserPNCRelatedGlobal[userInx].NoOfPncs; /* polyspace RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
    /* Pnc Index in the User */
    tmpUserPNCIndex = ComM_UserPNCRelatedGlobal[userInx].PncUserIndex;
    while (noOfPncs != COMM_ZERO)
    {
      noOfPncs--;
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      tmpPncIndex = ComM_PncUserInxArrGlobal[tmpUserPNCIndex];
      /* Number of Channel linked to the PNC */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      noOfChannels = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
      /* Index in the Channel Index array in the PNC*/
      handleChnlIndex = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;
      while (noOfChannels != COMM_ZERO)
      {
        /* Decrement the Channel */
        noOfChannels--;
        /* Get the Channel ID from Index Array */
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        chIndex = ComM_ChannelMapArray[ComM_ChnPncInxArrGlobal[handleChnlIndex]];
        #else
        chIndex = ComM_ChnPncInxArrGlobal[handleChnlIndex];
        #endif

        #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
              (COMM_DIRECT_USER_MAPPING == STD_OFF))
        /* channelRteInd : To avoid multiple indication to RTE */
        if (COMM_TRUE != channelRteInd[chIndex])
        #endif
        {
          /* @Trace: ComM_SUD_API_229 */
          #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
          (COMM_MODE_LIMITATION_ENABLED == STD_ON))
          inhibitionRetVal =
                             ComM_RequestComModeInhibitionCheck(chIndex, comMode);
          /* If no inhibition is set */
          if (COMM_FALSE == inhibitionRetVal)
          #endif
          {
            /* @Trace: ComM_SUD_API_230 */
            /* Enter in Data Protection */
            SchM_Enter_ComM_REQ_MODECNT_PROTECTION();
            if (COMM_FULL_COMMUNICATION == comMode)
            {
              /* @Trace: ComM_SUD_API_231 */
              /* If the previous request of that user is not
              *   Full communication */
              /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
              /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
              /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
              if (COMM_FULL_COMMUNICATION != ComM_RequestedComMode[userInx])
              {
                /* @Trace: ComM_SUD_API_232 */
                /* Load the Requested Full Com Mode into the User
                *   Requested Com mode array */
                ComM_RequestedComMode[userInx] = COMM_FULL_COMMUNICATION;
                /* Flag to know that the user has requested only once */
                comModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
              }
              /* Back to no com by limit to no com and then request full com */
              else if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
              {
                /* Flag to know that the user has requested only once */
                comModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
              }
              else
              {
                /* Do nothing */
              }
            } /* End of if (comMode == COMM_FULL_COMMUNICATION) */
            /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            else if (COMM_NO_COMMUNICATION != ComM_RequestedComMode[userInx])
            {
              /* @Trace: ComM_SUD_API_233 */
              /* Load the Requested No Com Mode into the User
              *   Requested Com mode array */
              ComM_RequestedComMode[userInx] = COMM_NO_COMMUNICATION;
              /* Flag to know that the user has requested only once */
              comModeReqFlag = COMM_NOCOMMREQ_ACCPTD;
            }
            else
            {
              /* @Trace: ComM_SUD_API_234 */
              /* To avoid MISRA warning */
            }
            /* If the user request was accepted */
            if (COMM_FULLCOMMREQ_ACCPTD == comModeReqFlag)
            {
              /* @Trace: ComM_SUD_API_235 */
              /* Load the Requested ComMode in the Array */
              if (ComM_ReqedComModeCnt[chIndex] < COMM_REQEDCOMMODECNT_MAX)
              {
                ComM_ReqedComModeCnt[chIndex]++;
              }
              #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
              (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
              /* Stop the timer if there is user request when there is no NM
              *   available */
              ComM_TimeCnt[chIndex] = (ComM_TimeType)COMM_ZERO;
              #endif
            }
            else if (COMM_NOCOMMREQ_ACCPTD == comModeReqFlag)
            {
              /* @Trace: ComM_SUD_API_236 */
              /* Load the Requested ComMode in the Array */
              if (ComM_ReqedComModeCnt[chIndex] > COMM_ZERO)
              {  
                ComM_ReqedComModeCnt[chIndex]--;
              }
            }
            else
            {
              /* @Trace: ComM_SUD_API_237 */
              /* To avoid MISRA warning */
            }
            /* Exit data protection */
            SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
            #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
              (COMM_DIRECT_USER_MAPPING == STD_OFF))
            /* Update Rte with the user who has requested the channel */
            if (COMM_TRUE == ComM_Channels[chIndex].FullCommReqNotifEn)
            {
              /* @Trace: ComM_SUD_API_238 */
              ComM_RequestComModeRteUpdate(chIndex, userInx, comMode);
              /* The RTE is indicated with Channel mode*/
              channelRteInd[chIndex] = COMM_TRUE;
            }
            /* The RTE is indicated with Channel mode*/
            #endif
          }
          #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
          (COMM_MODE_LIMITATION_ENABLED == STD_ON))
          else
          {
            /* @Trace: ComM_SUD_API_239 */
            /* Load Return Value with COMM_E_MODE_LIMITATION */
            returnValue = COMM_E_MODE_LIMITATION;
          }
          #endif
        } /* End of if (channelRteInd[chIndex] != COMM_TRUE) */
        handleChnlIndex++;
      } /* End of while (noOfChannels != COMM_ZERO) */
      /* PNC State changes associated  with the user */
      ComM_PncUserHandle(tmpPncIndex, comMode);
      tmpUserPNCIndex++;
    } /* End of while (noOfPncs != COMM_ZERO) */
  // }
  // else  End of if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* Do nothing */
  // }
  return (returnValue);
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_RequestComModePNC */

/*******************************************************************************
** Function Name        : ComM_GetCurComModePNC                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Lowest mode of PNC for the**
**                        API ComM_GetCurComMode                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userIndex, lowestMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Users, ComM_PncUserInxArr, ComM_Pncs,          **
**                        ComM_ChnPncInxArr, ComM_ChannelMapArray,            **
**                        ComM_Channels, ComM_CurComMode                      **
**                        ComM_SMGetCurComModeFun                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), CanSM_GetCurrentComMode(),       **
**                        LinSM_GetCurrentComMode(), FrSM_GetCurrentComMode(),**
**                        EthSM_GetCurrentComMode()                           **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09172 SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00122
 * SRS_ComM_AR_00158 SRS_ComM_AR_00159 SRS_ComM_AR_00160 SRS_ComM_AR_00164
 */
FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurComModePNC(uint8 userIndex, P2VAR(
    ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) lowestMode)
{
  /* @Trace: ComM_SUD_API_161 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  Std_ReturnType returnValue;
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* Pointer to load the current mode of respective SM */
  ComM_ModeType modePtr;
  modePtr = COMM_NO_COMMUNICATION;
  #endif

  /* Variable to store No of PNCs of the User */
  uint16 noOfPncs;

  /* Variable for PNC Index associated with users */
  PNCHandleType tmpUserPNCIndex;

  /* Variable for Pnc Index */
  PNCHandleType tmpPncIndex;

  /* Variable for Pnc Channel Index */
  NetworkHandleType handleChannelPncInx;

  /* Variable for Channel ID associated with a PNC */
  uint8 tmpChannelId;

  /* Variable for Pnc Channel Index */
  uint8 pncChannelInx;

  /* Variable to get number of channels */
  uint8 noOfChannels;

  /* Initialize the variable */
  returnValue = E_OK;

  /* Get the No of PNCs of the User */
  /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  noOfPncs = ComM_Users[userIndex].NoOfPncs; /* polyspace RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */

  /* PNC Index */
  tmpUserPNCIndex = ComM_Users[userIndex].PncUserIndex;
  /* Check the Current Communication Mode of the Each channel of each PNC */
  while (noOfPncs != COMM_ZERO)
  {
    /* Get the PNC Index from Index Array */
    tmpPncIndex = ComM_PncUserInxArr[tmpUserPNCIndex];

    /* Decrement the Number of PNCs */
    noOfPncs--;

    /* Get the Channels associated with the PNC*/
    noOfChannels = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;

    /*Channel Index of Pnc */
    handleChannelPncInx = ComM_Pncs[tmpPncIndex].ChannelPncIndex;
    /* Check the Current Communication Mode Each channel */
    while (noOfChannels != COMM_ZERO)
    {
      /* Get the Channel ID from PNC Index Array */
      tmpChannelId = ComM_ChnPncInxArr[handleChannelPncInx];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

      /* The index variable is updated with Channel */
      pncChannelInx = ComM_ChannelMapArray[tmpChannelId];
      #else
      pncChannelInx = tmpChannelId;
      #endif

      /* Decrement the Number of channels */
      noOfChannels--;

      #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
      #if (COMM_INTERNALBUS_PRESENT == STD_ON)
      if (COMM_INTERNAL != ComM_Channels[pncChannelInx].BusType)
      #endif
      {
        /* @Trace: ComM_SUD_API_162 */
        /* Check the SM channel mode*/
        (void) ComM_SMGetCurComModeFun[ComM_Channels[pncChannelInx].
            BusType](ComM_Channels[pncChannelInx].ChannelId, &modePtr);
        /* Check the current Communication Mode */
        if (COMM_NO_COMMUNICATION == modePtr)
        {
          /* @Trace: ComM_SUD_API_163 */
          /* Get the lowest mode */
          *lowestMode = COMM_NO_COMMUNICATION;

          /* Break from while : Channels */
          noOfChannels = COMM_ZERO;

          /* Break from while : PNCs */
          noOfPncs = COMM_ZERO;
        } /* End of if (modePtr == COMM_NO_COMMUNICATION) */
        else
        {
          /* @Trace: ComM_SUD_API_164 */
          /* Check for Silent comm */
          if (COMM_SILENT_COMMUNICATION == modePtr)
          {
            /* @Trace: ComM_SUD_API_165 */
            /* Get the lowest mode */
            *lowestMode = COMM_SILENT_COMMUNICATION;
            handleChannelPncInx++;
          }
          else
          {
            /* @Trace: ComM_SUD_API_166 */
            /* Check the next channel associated with the user */
            handleChannelPncInx++;
          }
        } /* End of else */
      } /* End of if (COMM_INTERNAL != ComM_Channels[pncChannelInx].BusType) */
      #if (COMM_INTERNALBUS_PRESENT == STD_ON)
      else
      #endif
      #endif /* (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
      #if (COMM_INTERNALBUS_PRESENT == STD_ON)
      {
        /* @Trace: ComM_SUD_API_167 */
        /* Check the current CommunicationMode */
        if (COMM_NO_COMMUNICATION == ComM_CurComMode[pncChannelInx])
        {
          /* @Trace: ComM_SUD_API_168 */
          /* Get the lowest mode */
          *lowestMode = COMM_NO_COMMUNICATION;

          /* Break from while : Channels */
          noOfChannels = COMM_ZERO;

          /* Break from while : PNCs */
          noOfPncs = COMM_ZERO;
        } /* End of if (COMM_NO_COMMUNICATION ==
           * ComM_CurComMode[pncChannelInx]) */
        else
        {
          /* @Trace: ComM_SUD_API_169 */
          /* Check for Silent comm */
          if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[pncChannelInx])
          {
            /* @Trace: ComM_SUD_API_170 */
            /* Get the lowest mode */
            *lowestMode = COMM_SILENT_COMMUNICATION;
            handleChannelPncInx++;
          }
          else
          {
            /* @Trace: ComM_SUD_API_171 */
            handleChannelPncInx++;
          }
        } /* End of else */
      }
      #endif
    }
    tmpUserPNCIndex++;
  } /* End While */
  return (returnValue);
  #else
  /* ========================== Implement for Post-Build ==================== */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    Std_ReturnType returnValue;

    #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
    /* Pointer to load the current mode of respective SM */
    ComM_ModeType modePtr;
    modePtr = COMM_NO_COMMUNICATION;
    #endif

    /* Variable to store No of PNCs of the User */
    uint16 noOfPncs;
    /* Variable for PNC Index associated with users */
    PNCHandleType tmpUserPNCIndex;
    /* Variable for Pnc Index */
    PNCHandleType tmpPncIndex;
    /* Variable for Pnc Channel Index */
    NetworkHandleType handleChannelPncInx;
    /* Variable for Channel ID associated with a PNC */
    uint8 tmpChannelId;
    /* Variable for Pnc Channel Index */
    uint8 pncChannelInx;
    /* Variable to get number of channels */
    uint8 noOfChannels;
    /* Initialize the variable */
    returnValue = E_OK;
    /* Get the No of PNCs of the User */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    noOfPncs = ComM_UserPNCRelatedGlobal[userIndex].NoOfPncs; /* polyspace RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
    /* PNC Index */
    tmpUserPNCIndex = ComM_UserPNCRelatedGlobal[userIndex].PncUserIndex;
    /* Check the Current Communication Mode of the Each channel of each PNC */
    while (noOfPncs != COMM_ZERO)
    {
      /* Get the PNC Index from Index Array */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      tmpPncIndex = ComM_PncUserInxArrGlobal[tmpUserPNCIndex];
      /* Decrement the Number of PNCs */
      noOfPncs--;
      /* Get the Channels associated with the PNC*/
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      noOfChannels = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
      /*Channel Index of Pnc */
      handleChannelPncInx = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;
      /* Check the Current Communication Mode Each channel */
      while (noOfChannels != COMM_ZERO)
      {
        /* Get the Channel ID from PNC Index Array */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        tmpChannelId = ComM_ChnPncInxArrGlobal[handleChannelPncInx];
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        /* The index variable is updated with Channel */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        pncChannelInx = ComM_ChannelMapArray[tmpChannelId];
        #else
        pncChannelInx = tmpChannelId;
        #endif
        /* Decrement the Number of channels */
        noOfChannels--;

        #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        if (COMM_INTERNAL != ComM_Channels[pncChannelInx].BusType)
        {
          /* @Trace: ComM_SUD_API_172 */
          /* Check the SM channel mode*/
          (void) ComM_SMGetCurComModeFun[ComM_Channels[pncChannelInx].
              BusType](ComM_Channels[pncChannelInx].ChannelId, &modePtr);
          /* Check the current Communication Mode */
          if (COMM_NO_COMMUNICATION == modePtr)
          {
            /* @Trace: ComM_SUD_API_173 */
            /* Get the lowest mode */
            *lowestMode = COMM_NO_COMMUNICATION;
            /* Break from while : Channels */
            noOfChannels = COMM_ZERO;
            /* Break from while : PNCs */
            noOfPncs = COMM_ZERO;
          } /* End of if (modePtr == COMM_NO_COMMUNICATION) */
          else
          {
            /* @Trace: ComM_SUD_API_174 */
            /* Check for Silent comm */
            if (COMM_SILENT_COMMUNICATION == modePtr)
            {
              /* @Trace: ComM_SUD_API_175 */
              /* Get the lowest mode */
              *lowestMode = COMM_SILENT_COMMUNICATION;
              handleChannelPncInx++;
            }
            else
            {
              /* @Trace: ComM_SUD_API_176 */
              /* Check the next channel associated with the user */
              handleChannelPncInx++;
            }
          } /* End of else */
        } /* End of if (COMM_INTERNAL != ComM_Channels[pncChannelInx].BusType) */
        else
        #endif /* (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
        {
          /* @Trace: ComM_SUD_API_177 */
          /* Check the current CommunicationMode */
          if (COMM_NO_COMMUNICATION == ComM_CurComMode[pncChannelInx])
          {
            /* @Trace: ComM_SUD_API_178 */
            /* Get the lowest mode */
            *lowestMode = COMM_NO_COMMUNICATION;
            /* Break from while : Channels */
            noOfChannels = COMM_ZERO;
            /* Break from while : PNCs */
            noOfPncs = COMM_ZERO;
          } /* End of if (COMM_NO_COMMUNICATION ==
            * ComM_CurComMode[pncChannelInx]) */
          else
          {
            /* @Trace: ComM_SUD_API_179 */
            /* Check for Silent comm */
            if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[pncChannelInx])
            {
              /* @Trace: ComM_SUD_API_180 */
              /* Get the lowest mode */
              *lowestMode = COMM_SILENT_COMMUNICATION;
              handleChannelPncInx++;
            }
            else
            {
              /* @Trace: ComM_SUD_API_181 */
              handleChannelPncInx++;
            }
          } /* End of else */
        }
      }
      tmpUserPNCIndex++;
    } /* End While */
  // }
  // else  End of if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* Do nothing */
  // }
  return (returnValue);
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_GetCurComModePNC */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  * (COMM_FRNETWORK_PRESENT == STD_ON))
  */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  * STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_FullComNetwReqSubThree                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check other conditions than timer**
**                        expiry for full communication sub state READY SLEEP **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels, ComM_ChannelToPncMapping,            **
**                        ComM_SubPNCMode,ComM_ChannelInhibition,             **
**                        ComM_InhibitionReqst, ComM_ReqedComModeCnt,         **
**                        ComM_DcmActiveDiagnostic,ComM_DcmInactiveDiagnostic **
**                        ComM_SubComMode                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00094 SRS_ComM_AR_00095 SRS_ComM_AR_00111 
 * SRS_ComM_AR_00011 */
FUNC(void, COMM_CODE) ComM_FullComNetwReqSubThree(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_378 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))
  /* The variable is used for PNC Index */
  PNCHandleType tmpPncIndex;

  /* The variable is used for PNC Count */
  uint16 tmpPncCount;

  /* The variable is used for Indexing*/
  PNCHandleType subPNCIndex;

  uint8 isAllNoCom = 0;
  #endif
  #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
    * STD_ON)) */

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) &&\
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /* Check if the channel is part of a PNC */
  if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc)
  {
    /* @Trace: ComM_SUD_API_379 */
    tmpPncIndex = ComM_Channels[chIndex].PncIndex;
    tmpPncCount = ComM_Channels[chIndex].PncCount;
    /*State transitions of the PNC state machines */
    while (tmpPncCount != COMM_ZERO)
    {
      /* Decrement the pnc count */
      tmpPncCount--;

      /* ComM_ChannelToPncMapping[] :The Map provides Index*/
      subPNCIndex = ComM_ChannelToPncMapping[tmpPncIndex];

      if (COMM_PNC_REQUESTED == ComM_SubPNCMode[subPNCIndex])
      {
        /* @Trace: ComM_SUD_API_380 */
        isAllNoCom++;
      }
      tmpPncIndex++;
    } /*End of while (tmpPncCount != COMM_ZERO)*/
  } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
  #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
    * STD_ON)) */

  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  if (COMM_PREVENTWAKEUP_MASK_SET !=
  (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET))
  #endif
  {
    /* @Trace: ComM_SUD_API_381 */
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    /* Check for Full Communication request during inhibition */
    if (COMM_ZERO != ComM_InhibitionReqst[chIndex])
    {
      /* @Trace: ComM_SUD_API_382 */
      /* Full communication request during inhibition is loaded into
       *   request variable */
      ComM_ReqedComModeCnt[chIndex] = ComM_InhibitionReqst[chIndex];
      ComM_InhibitionReqst[chIndex]--;
    }
    #endif

    /* If there is no user request */
    if ((COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) &&\
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
        && (COMM_ZERO == isAllNoCom)
    #endif
    )
    {
      /* Enter Data Protection */
      SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
      /* @Trace: ComM_SUD_API_383 */
      /* If there is active diagnostic and If Inactive diagnostic is called */
      if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
      {
        if (COMM_TRUE == ComM_DcmInactiveDiagnostic[chIndex])
        {
          /* @Trace: ComM_SUD_API_384 */
          /* Change sub state to Ready Sleep */
          ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;

          /* Clear diagnostic flag */
          ComM_DcmActiveDiagnostic[chIndex] = COMM_FALSE;

          /* Clear diagnostic flag */
          ComM_DcmInactiveDiagnostic[chIndex] = COMM_FALSE;
        }
      } /* End of if (ComM_DcmActiveDiagnostic[chIndex] == COMM_TRUE) */
      /* If there is no diagnostic set */
      else
      {
        /* @Trace: ComM_SUD_API_385 */
         /* Change sub state to Ready Sleep */
         ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
      }
      /* Exit Data Protection */
      SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
    } /* End of if (ComM_ReqedComModeCnt[chIndex] == COMM_ZERO) */
    else
    {
      /* @Trace: ComM_SUD_API_386 */
      /* Do nothing */
    }
  }
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  /* If inhibition is set */
  else
  {
    /* @Trace: ComM_SUD_API_387 */
      /* Change sub state to Ready Sleep */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
  }
  #endif

  #else
  /* ========================== Implement for Post-Build ==================== */
  /* the variable is used for check no com */
  uint8 isAllNoCom = 0;
  if (COMM_TRUE == ComM_PncEnabledFlashPB)
  {
    /* @Trace: ComM_SUD_API_388 */
    /* The variable is used for PNC Index */
    PNCHandleType tmpPncIndex;
    /* The variable is used for PNC Count */
    uint16 tmpPncCount;
    /* The variable is used for Indexing*/
    PNCHandleType subPNCIndex;

    /* Check if the channel is part of a PNC */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    if (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chIndex].ChannelPnc)
    {
      /* @Trace: ComM_SUD_API_389 */
      tmpPncIndex = ComM_ChannelsPNCRelatedGlobal[chIndex].PncIndex;
      tmpPncCount = ComM_ChannelsPNCRelatedGlobal[chIndex].PncCount;
      /*State transitions of the PNC state machines */
      while (tmpPncCount != COMM_ZERO)
      {
        /* Decrement the pnc count */
        tmpPncCount--;

        /* ComM_ChannelToPncMapping[] :The Map provides Index*/
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        subPNCIndex = ComM_ChannelToPncMappingGlobal[tmpPncIndex];

        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        if (COMM_PNC_NO_COMMUNICATION != ComM_SubPNCMode[subPNCIndex])
        {
          /* @Trace: ComM_SUD_API_390 */
          isAllNoCom++;
        }
        tmpPncIndex++;
      } /*End of while (tmpPncCount != COMM_ZERO)*/
    } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
    else
    {
      /* @Trace: ComM_SUD_API_391 */
      /* Do nothing */
    }
  } /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
  else
  {
    /* @Trace: ComM_SUD_API_392 */
    /* Do nothing */
  }

  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  if (COMM_PREVENTWAKEUP_MASK_SET !=
  (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET))
  #endif
  {
    /* @Trace: ComM_SUD_API_393 */
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    /* Check for Full Communication request during inhibition */
    if (COMM_ZERO != ComM_InhibitionReqst[chIndex])
    {
      /* @Trace: ComM_SUD_API_394 */
      /* Full communication request during inhibition is loaded into
      *   request variable */
      ComM_ReqedComModeCnt[chIndex] = ComM_InhibitionReqst[chIndex];
      ComM_InhibitionReqst[chIndex]--;
    }
    #endif

    /* If there is no user request */
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_395 */
      if ((COMM_ZERO == ComM_ReqedComModeCnt[chIndex]) && \
                                                      (COMM_ZERO == isAllNoCom))
      {
        /* @Trace: ComM_SUD_API_396 */
        /* If there is active diagnostic and If Inactive diagnostic is called */
        if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
        {
          if (COMM_TRUE == ComM_DcmInactiveDiagnostic[chIndex])
          {
            /* Enter Data Protection */
            SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();

            /* @Trace: ComM_SUD_API_397 */
            /* Change sub state to Ready Sleep */
            ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;

            /* Clear diagnostic flag */
            ComM_DcmActiveDiagnostic[chIndex] = COMM_FALSE;

            /* Clear diagnostic flag */
            ComM_DcmInactiveDiagnostic[chIndex] = COMM_FALSE;

            /* Exit Data Protection */
            SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
          }
        } /* End of if (ComM_DcmActiveDiagnostic[chIndex] == COMM_TRUE) */
        /* If there is no diagnostic set */
        else
        {
          /* @Trace: ComM_SUD_API_398 */
          /* Change sub state to Ready Sleep */
          ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
        }
      } /* End of if (ComM_ReqedComModeCnt[chIndex] == COMM_ZERO) */
      else
      {
        /* @Trace: ComM_SUD_API_399 */
        /* Do nothing */
      }
    } /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
    else
    {
      /* @Trace: ComM_SUD_API_400 */
      if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
      {
        /* @Trace: ComM_SUD_API_401 */
        /* If there is active diagnostic and If Inactive diagnostic is called */
        if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
        {
          if (COMM_TRUE == ComM_DcmInactiveDiagnostic[chIndex])
          {
            /* Enter Data Protection */
            SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();

            /* @Trace: ComM_SUD_API_402 */
            /* Change sub state to Ready Sleep */
            ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;

            /* Clear diagnostic flag */
            ComM_DcmActiveDiagnostic[chIndex] = COMM_FALSE;

            /* Clear diagnostic flag */
            ComM_DcmInactiveDiagnostic[chIndex] = COMM_FALSE;

            /* Exit Data Protection */
            SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
          }
        } /* End of if (ComM_DcmActiveDiagnostic[chIndex] == COMM_TRUE) */
        /* If there is no diagnostic set */
        else
        {
          /* @Trace: ComM_SUD_API_403 */
          /* Change sub state to Ready Sleep */
          ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
        }
      }
      else
      {
        /* @Trace: ComM_SUD_API_404 */
        /* Do nothing */
      }
    }
  }
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  /* If inhibition is set */
  else
  {
    /* @Trace: ComM_SUD_API_405 */
      /* Change sub state to Ready Sleep */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
  }
  #endif
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_FullComNetwReqSubThree */
/*******************************************************************************
** Function Name        : ComM_FullComNetwReqSubTwo                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check the condition for network  **
**                        request, User request and Dcm indicate diagnostic   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_SubComMode, ComM_NmRequestProcessing,          **
**                        ComM_NmRequested,ComM_ChannelInhibition,            **
**                        ComM_ReqedComModeCnt, ComM_DcmActiveDiagnostic,     **
**                        ComM_InhibitionReqst                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode, Nm_NetworkRequest,             **
**                        ComM_SwitchReadySleepWithManagedChannel             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_00049 SRS_ComM_AR_00095  */
#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
FUNC(void, COMM_CODE) ComM_FullComNetwReqSubTwo(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_366 */
  /* Variable to store Nm request in inhibition mode */
  boolean flaglNmReq;

  /* set init value */
  flaglNmReq = COMM_FALSE;

  Std_ReturnType returnVal = E_NOT_OK;

  if (COMM_TWO != ComM_NmRequested[chIndex])
  {
    SchM_Enter_ComM_REQ_MODECNT_PROTECTION();
    /* @Trace: ComM_SUD_API_367 */
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    /* Check For Prevent WakeUp Inhibition */
    if (COMM_PREVENTWAKEUP_MASK_SET !=
      (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET))
    {
      /* @Trace: ComM_SUD_API_368 */
    #endif
      if ((COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
        || (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
        #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
        || (COMM_ZERO != ComM_InhibitionReqst[chIndex])
        #endif
        )
      {
        /* @Trace: ComM_SUD_API_369 */
        /* Set a flag */
        flaglNmReq = COMM_TRUE;
      } /* End of if ((ComM_ChannelInhibition[chIndex] & */
      else
      {
        /* @Trace: ComM_SUD_API_370 */
        /* Do nothing */
      }
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    } /* End of if (COMM_TWO != ComM_NmRequested[chIndex]) */
      /* Active diagnostic shall not be inhibited */
    else if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
    {
      /* @Trace: ComM_SUD_API_371 */
      /* Set a flag */
      flaglNmReq = COMM_TRUE;
    }
    else
    {
      /* @Trace: ComM_SUD_API_372 */
      /* To avoid MISRA warning */
    }
    #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
            *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
    /* Traceable SWS_ComM_00869, SWS_ComM_00870 */
    SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
    if (COMM_TRUE == flaglNmReq)
    {
      /* Request Nm Bus Communication */
      returnVal = Nm_NetworkRequest(ComM_Channels[chIndex].ChannelId);
      if (E_OK == returnVal)
      {
        /* @Trace: ComM_SUD_API_373 */
        /* Enter Data Protection */
        SchM_Enter_ComM_NM_INDICATION_PROTECTION();
        /* Set Flag for Nm is requested for network */
        ComM_NmRequested[chIndex] = COMM_TWO;
        ComM_NmRequestProcessing[chIndex] = COMM_TRUE;
        /* Exit Data Protection */
        SchM_Exit_ComM_NM_INDICATION_PROTECTION();
      }
      else
      {
        /* @Trace: ComM_SUD_API_744 */
        /* Do nothing */
      }
    }
    else
    {
      /* @Trace: ComM_SUD_API_374 */
      /* Do nothing */
    }
  } /* End of if (COMM_TWO != ComM_NmRequested[chIndex]) */
  else
  {
    /* @Trace: ComM_SUD_API_375 */
    /* Do nothing */
  }
  SchM_Enter_ComM_CURRENT_MODE_PROTECTION();
  /* Traceable SWS_ComM_00888 */
  if ((COMM_ZERO == ComM_ReqedComModeCnt[chIndex]) &&\
    (COMM_FALSE == ComM_DcmActiveDiagnostic[chIndex]))
  {
    SchM_Exit_ComM_CURRENT_MODE_PROTECTION();
    /* @Trace: ComM_SUD_API_376 */
    #if (COMM_REFERENCE_CHANEL == STD_ON)
    /* Switch sub mode ready sleep when managed channel */
    ComM_SwitchReadySleepWithManagedChannel(chIndex);
    #else
      /* Change sub state to Ready Sleep */
      ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
    #endif /* end of #if (COMM_REFERENCE_CHANEL == STD_ON) */
  }
  else
  {
    SchM_Exit_ComM_CURRENT_MODE_PROTECTION();
    /* @Trace: ComM_SUD_API_377 */
    /* Do nothing */
  }
}
#endif /* End of #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_FullComNetwReqSubOne                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check the timer expiry for full  **
**                        communication sub state READY SLEEP when Nm variant **
**                        LIGHT and NONE                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels,ComM_TimeCnt,ComM_SubComMode          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00100 SRS_ComM_AR_00105   */
#if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
FUNC(uint8, COMM_CODE) ComM_FullComNetwReqSubOne(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_354 */
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* The Variable is used to load the Nm Light Time out of channel */
  ComM_TimeType timeOut;

  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;
  #endif
  /* Variable to store the flag if NM is in different mode */
  uint8 flagStore;

  /* Clear Timer State */
  flagStore = COMM_ZERO;

  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* Get the Nm Variant of the channel */
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;

  /* Load the address of structure into local variable */
  timeOut = ComM_Channels[chIndex].NmLightTimeout;
  #endif
  SchM_Enter_ComM_REQ_MODECNT_PROTECTION();
  /* If the timer has not expired */
  if ((ComM_TimeType)COMM_ZERO != ComM_TimeCnt[chIndex])
  {
    /* @Trace: ComM_SUD_API_355 */
    /* Decrement the Timeout */
    ComM_TimeCnt[chIndex]--;
    flagStore = COMM_ONE;

    if ((ComM_TimeType)COMM_ZERO == ComM_TimeCnt[chIndex])
    {
      /* @Trace: ComM_SUD_API_356 */
      flagStore = COMM_ZERO;
      /* Check if there is any user request            *
       * 18/Feb/2014 Kt.Kim according to redmine #572  *
       */
      #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
      if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
      {
        /* @Trace: ComM_SUD_API_357 */
        /* Change sub state to Ready Sleep */
        if (COMM_NMVARIANT_LIGHT == tmpNmVariant)
        {
          /* @Trace: ComM_SUD_API_358 */
          /* Start the Nm light time out duration in full Communication */
          ComM_TimeCnt[chIndex] = timeOut;
        }
        else
        {
          /* @Trace: ComM_SUD_API_359 */
          /* Do nothing */
        }
      } /* End of if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex]) */
      else
      {
        /* @Trace: ComM_SUD_API_360 */
        /* Do nothing */
      }
      #endif
    } /* End of if ((ComM_TimeType)COMM_ZERO equals ComM_TimeCnt[chIndex]) */
    else
    {
      /* @Trace: ComM_SUD_API_361 */
      /* Do nothing */
    }
  } /* End of if ((ComM_TimeType)COMM_ZERO != ComM_TimeCnt[chIndex]) */
  /* 2014.07.10 Bug Fix #1080 by KtKim */
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  else if (COMM_NMVARIANT_LIGHT == tmpNmVariant)
  {
    /* @Trace: ComM_SUD_API_362 */
    /* If timer is expired reset timer if NO COMMUNICATION is
    requested.                                               */
    if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
    {
      /* @Trace: ComM_SUD_API_363 */
      /* Start the Nm light time out duration in full Communication */
      ComM_TimeCnt[chIndex] = timeOut;
    }
    else
    {
      /* @Trace: ComM_SUD_API_364 */
      /* Do nothing */
    }
  }
  else
  {
    /* @Trace: ComM_SUD_API_365 */
    /* Do nothing */
  }
  #endif
  SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
  return (flagStore);
} /* End of ComM_FullComNetwReqSubOne */
#endif /* End of if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||
  * (COMM_NONE_NMVARIANT_SUPPORT == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_COMCbk                                         **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : This service shall Receive PNC ERAn and EIRA signal **
**                      : as indicated by Com                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : signalId                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ComSignal                                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), Com_ReceiveSignal(),             **
**                        ComM_ComSignalReception()                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00026
 * SRS_ComM_AR_00015 SRS_ComM_AR_00179
 */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_COMCbk(Com_SignalIdType SignalId)
{
  /* @Trace: ComM_SUD_API_265 */
  /*
   * Variable to Store Signal Information in ComM
   * Note: Fetched the signal length
   */
  uint8 comSignalRx[PNC_COM_MAX_LENGTH];

  /* Variable used to init the com Signals */
  uint8 comSignalInit;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  #endif

  /* Init the com Signals */
  comSignalInit = PNC_COM_MAX_LENGTH;
  while (comSignalInit != COMM_ZERO)
  {
    /* decrement the variable */
    comSignalInit--;

    /* Initialize Signal Rx */
    comSignalRx[comSignalInit] = COMM_ZERO;
  }

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;

  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_266 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_COMCBK_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }
  /* Check, if there is no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_267 */
    if (E_OK == Com_ReceiveSignal(SignalId, (void*)comSignalRx))
    {
      #if (((COMM_PNC_EIRA_SIGNAL_PRESENT == STD_ON) ||\
        (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)) &&\
        (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON))
      /* @Trace: ComM_SUD_API_268 */
      /* Rational: A signal can have 48 PNC Information  */
      ComM_ComSignalReception(SignalId, comSignalRx);
      #endif
    }
    else
    {
      /* @Trace: ComM_SUD_API_269 */
      /* Do nothing */
    }
  }
} /* End of ComM_COMCbk */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  * (COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  * TD_ON)) */

/*******************************************************************************
** Function Name        : ComM_GetMaxComModePNC                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Lowest mode of PNC for the**
**                        API ComM_GetMaxComMode                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userIndex, lowestMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Users, ComM_PncUserInxArr, ComM_Pncs,          **
**                        ComM_ChnPncInxArr, ComM_ChannelMapArray,            **
**                        ComM_TotalChannels                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(),                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00186   */
#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
          (COMM_MODE_LIMITATION_ENABLED == STD_ON))
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_GetMaxComModePNC(uint8 userIndex, P2VAR(
    ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) lowestMode)
{
  /* @Trace: ComM_SUD_API_273 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* Variable to store No of PNCs of the User */
  uint16 noOfPncs;
  /* Variable for PNC Index associated with users */
  PNCHandleType tmpUserPNCIndex;
  /* Variable for Pnc Index */
  PNCHandleType tmpPncIndex;
  /* Variable for Pnc Channel Index */
  NetworkHandleType handleChannelPncInx;
  /* Variable for Channel ID associated with a PNC */
  uint8 tmpChannelId;
  /* Variable for Pnc Channel Index */
  uint8 pncChannelInx;
  /* Variable to get number of channels */
  uint8 noOfChannels;

  /* Get the No of PNCs of the User */
  /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  noOfPncs = ComM_Users[userIndex].NoOfPncs; /* polyspace RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* PNC Index */
  tmpUserPNCIndex = ComM_Users[userIndex].PncUserIndex;
  /* Check the Current Communication Mode of the Each channel of each PNC */
  while (noOfPncs != COMM_ZERO)
  {
    /* Get the PNC Index from Index Array */
    tmpPncIndex = ComM_PncUserInxArr[tmpUserPNCIndex];
    /* Decrement the Number of PNCs */
    noOfPncs--;
    /* Get the Channels associated with the PNC*/
    noOfChannels = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;
    /*Channel Index of Pnc */
    handleChannelPncInx = ComM_Pncs[tmpPncIndex].ChannelPncIndex;
    /* Check the Current Communication Mode Each channel */
    while (noOfChannels != COMM_ZERO)
    {
      /* Get the Channel ID from PNC Index Array */
      tmpChannelId = ComM_ChnPncInxArr[handleChannelPncInx];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* The index variable is updated with Channel */
      pncChannelInx = ComM_ChannelMapArray[tmpChannelId];
      #else
      pncChannelInx = tmpChannelId;
      #endif
      /* Decrement the Number of channels */
      noOfChannels--;
      /*
       * Check if wake up inhibition is enabled in ECU group classification or
       * Inhibition/Limitation is enable or
       * Limit ECU to No Communication is Enabled
       */
      if ((COMM_ZERO != ComM_Data.ComMEcuInhibition) && \
        ((COMM_ZERO != ComM_ChannelInhibition[pncChannelInx]) || \
        (COMM_TRUE == ComM_LimitEcuToNoCom)))
      {
        /* @Trace: ComM_SUD_API_274 */
        /* Get the lowest mode */
        *lowestMode = COMM_NO_COMMUNICATION; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The lowestMode pointer is declared in local ComM, it shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
        /* Break from while : Channels */
        noOfChannels = COMM_ZERO;
        /* Break from while : PNCs */
        noOfPncs = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_275 */
        /* Get the max com mode */
        *lowestMode = COMM_FULL_COMMUNICATION; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The lowestMode pointer is declared in local ComM, it shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
        /* Check the next channel associated with the user */
        handleChannelPncInx++;
      }
    }/* End While */
    tmpUserPNCIndex++;
  } /* End While */
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* Variable to store No of PNCs of the User */
  uint16 noOfPncs;
  /* Variable for PNC Index associated with users */
  PNCHandleType tmpUserPNCIndex;
  /* Variable for Pnc Index */
  PNCHandleType tmpPncIndex;
  /* Variable for Pnc Channel Index */
  NetworkHandleType handleChannelPncInx;
  /* Variable for Channel ID associated with a PNC */
  uint8 tmpChannelId;
  /* Variable for Pnc Channel Index */
  uint8 pncChannelInx;
  /* Variable to get number of channels */
  uint8 noOfChannels;

  /* Get the No of PNCs of the User */
  /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  noOfPncs = ComM_UserPNCRelatedGlobal[userIndex].NoOfPncs; /* polyspace RTE:OBAI [Not a defect:Low] "Value of array ComM_User is generated by Tcode and checked manual. It is not having any impact" */
  /* PNC Index */
  tmpUserPNCIndex = ComM_UserPNCRelatedGlobal[userIndex].PncUserIndex;
  /* Check the Current Communication Mode of the Each channel of each PNC */
  while (noOfPncs != COMM_ZERO)
  {
    /* Get the PNC Index from Index Array */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    tmpPncIndex = ComM_PncUserInxArrGlobal[tmpUserPNCIndex];
    /* Decrement the Number of PNCs */
    noOfPncs--;
    /* Get the Channels associated with the PNC*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    noOfChannels = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
    /*Channel Index of Pnc */
    handleChannelPncInx = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;
    /* Check the Current Communication Mode Each channel */
    while (noOfChannels != COMM_ZERO)
    {
      /* Get the Channel ID from PNC Index Array */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      tmpChannelId = ComM_ChnPncInxArrGlobal[handleChannelPncInx];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* The index variable is updated with Channel */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      pncChannelInx = ComM_ChannelMapArray[tmpChannelId];
      #else
      pncChannelInx = tmpChannelId;
      #endif
      /* Decrement the Number of channels */
      noOfChannels--;
      /*
      * Check if wake up inhibition is enabled in ECU group classification or
      * Inhibition/Limitation is enable or
      * Limit ECU to No Communication is Enabled
      */
      /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      if ((COMM_ZERO != ComM_Data.ComMEcuInhibition) && \
        ((COMM_ZERO != ComM_ChannelInhibition[pncChannelInx]) || \
        (COMM_TRUE == ComM_LimitEcuToNoCom)))
      {
        /* @Trace: ComM_SUD_API_277 */
        /* Get the lowest mode */
        *lowestMode = COMM_NO_COMMUNICATION; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The lowestMode pointer is declared in local ComM, it shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
        /* Break from while : Channels */
        noOfChannels = COMM_ZERO;
        /* Break from while : PNCs */
        noOfPncs = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_278 */
        /* Get the max com mode */
        *lowestMode = COMM_FULL_COMMUNICATION; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The lowestMode pointer is declared in local ComM, it shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
        /* Check the next channel associated with the user */
        handleChannelPncInx++;
      }
    }/* End While */
    tmpUserPNCIndex++;
  } /* End While */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_GetMaxComModePNC */
#endif
#endif
#endif

/*******************************************************************************
** Function Name        : ComM_GetMaxComModeDirectChnl                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Lowest mode of direct     **
**                        channels for the API ComM_GetMaxComMode             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userChannelIndex, noOfChannels, lowestMode          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : returnValue                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChnInxArr, ComM_TotalChannels                  **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanSM_GetCurrentComMode(), LinSM_GetCurrentComMode()**
**                        FrSM_GetCurrentComMode(), EthSM _GetCurrentComMode()**
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00186  */
#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
#if (COMM_DIRECT_CHANNEL == STD_ON)
FUNC(void, COMM_CODE) ComM_GetMaxComModeDirectChnl(uint8
  userChannelIndex, uint8 noOfChannels, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA) lowestMode)
{
  /* @Trace: ComM_SUD_API_270 */
  /* The variable to get the direct channel Index */
  uint8 channelIndex;
  /* The variable to get userChannelIndex avoid MISRA 17.8 */
  uint8 userChannelIndexTemp;
  /* The variable to get noOfChannels avoid MISRA 17.8 */
  uint8 noOfChannelsTemp;

  userChannelIndexTemp = userChannelIndex;
  noOfChannelsTemp = noOfChannels;

  /* Check the Current Communication Mode of the Each Direct channel */
  while (noOfChannelsTemp != COMM_ZERO)
  {
    /* Get the Channel from Index Array */
    channelIndex = ComM_ChnInxArr[userChannelIndexTemp];
    /* Decrement the Number of channels */
    noOfChannelsTemp--;
    /*
     * Check if wake up inhibition is enabled in ECU group classification or
     * Inhibition/Limitation is enable or
     * Limit ECU to No Communication is Enabled
     */
    if ((COMM_ZERO != ComM_Data.ComMEcuInhibition) &&
        ((COMM_ZERO != ComM_ChannelInhibition[channelIndex]) ||
        (COMM_TRUE == ComM_LimitEcuToNoCom)))
    {
      /* @Trace: ComM_SUD_API_271 */
      /* Get the lowest mode */
      *lowestMode = COMM_NO_COMMUNICATION;
      /* Break from while : Channels */
      noOfChannelsTemp = COMM_ZERO;
    }
    else
    {
      /* @Trace: ComM_SUD_API_272 */
      /* Get the max com mode */
      *lowestMode = COMM_FULL_COMMUNICATION;
      /* Check the next channel associated with the user */
      userChannelIndexTemp++;
    }
  }/* End While */
} /* End of ComM_GetMaxComModeDirectChnl*/
#endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */
#endif /* End if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
            (COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_SwitchReadySleepWithManagedChannel             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to switch mode when channel         **
**                        is managed channel, related ComM_FullComNetwReq     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ManagingMapArray, ComM_ReqedComModeCnt         **
**                        ComM_SubComMode, ComM_Channels                      **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    : Nope                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00095 */
#if (COMM_REFERENCE_CHANEL == STD_ON)
#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
FUNC(void, COMM_CODE) ComM_SwitchReadySleepWithManagedChannel(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_636 */
  uint8 managedId;
  /* current id of managed channel in mapping array*/
  uint8 tmpManagedId;

  /* the managed channel index */
  uint8 managedInx;

  /* count number of managed channel */
  uint8 managedChnlCnt;

  /* flag set to full com */
  boolean flagFullCom;

  flagFullCom = COMM_TRUE;
  if (COMM_TRUE != ComM_Channels[chIndex].ManagingChnl)
  {
    /* @Trace: ComM_SUD_API_637 */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
  }
  else
  {
    /* @Trace: ComM_SUD_API_638 */
    /* Get managed channel index */
    managedInx = ComM_Channels[chIndex].ManagingIndex;
    /* get number of managed channel */
    managedChnlCnt = ComM_Channels[chIndex].NoOfManagedChnl;
    while(managedChnlCnt != COMM_ZERO)
    {
      /* get managed channel id in mapping array*/
      tmpManagedId = ComM_ManagingMapArray[managedInx];

      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      managedId = ComM_ChannelMapArray[tmpManagedId];
      #else
      managedId = tmpManagedId;
      #endif
      /* Check if managed channel is not reference to ComMPnc
        * and have not user requested full communication
        * Managed channel is Light variant
        */
      #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
      /* ====================== Implement for Pre-Compile =================== */
      if ((COMM_ZERO != ComM_ReqedComModeCnt[managedId])
      #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
      || (COMM_TRUE == ComM_Channels[managedId].ChannelPnc)
      #endif
      )
      #else
      /* ====================== Implement for Post-Build ==================== */
      /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      if ((COMM_ZERO != ComM_ReqedComModeCnt[managedId]) || \
             (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[managedId].ChannelPnc))
      #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
      {
        /* @Trace: ComM_SUD_API_639 */
        managedChnlCnt = COMM_ZERO;
        flagFullCom = COMM_FALSE;
      }
      else
      {
        /* @Trace: ComM_SUD_API_640 */
        managedInx++;
        managedChnlCnt--;
      }
    } /* End of while(managedChnlCnt != COMM_ZERO) */

    if (COMM_TRUE == flagFullCom)
    {
      /* @Trace: ComM_SUD_API_641 */
      /* Change sub state to Ready Sleep */
      ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
    }
    else
    {
      /* @Trace: ComM_SUD_API_642 */
      /* Do nothing */
    }

  } /* End of else */
} /* End of ComM_SwitchReadySleepWithManagedChannel */
#endif
#endif

/*******************************************************************************
** Function Name        : ComM_SwithFullModeReference                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall change sub mode infunction mode  **
**                        mitation and the current channel are reference to   **
**                        another channel                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ReqedComModeCnt, ComM_ChannelMapArray,         **
**                        ComM_Channels, ComM_SubComMode                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00103 */
FUNC(void, COMM_CODE) ComM_SwithFullModeReference(uint8 chIndex)
{
  #if (COMM_REFERENCE_CHANEL == STD_ON)
  NetworkHandleType managingChnlId;
  NetworkHandleType managingId;
  #endif

  /* Check user request full com */
  if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
  {
    /* @Trace: ComM_SUD_API_665 */
    /* Check channel is managed channel */
    #if (COMM_REFERENCE_CHANEL == STD_ON)
    if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl)
    {
      /* @Trace: ComM_SUD_API_666 */
      managingChnlId = ComM_Channels[chIndex].IdOfManagingChnl;
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      managingId = ComM_ChannelMapArray[managingChnlId];
      #else
      managingId = managingChnlId;
      #endif
      /* if ((COMM_TRUE == ComM_Channels[managingId].ManagingChnl) && */
      if (COMM_FULL_COM_READY_SLEEP == ComM_SubComMode[managingId])
      {
        /* @Trace: ComM_SUD_API_667 */
        /* switch managing channel to FULL_COM_NETWORK_REQUESTED */
        ComM_SubComMode[managingId] = COMM_FULL_COM_NETWORK_REQUESTED;
      }
      else
      {
        /* @Trace: ComM_SUD_API_668 */
        /* Do nothing */
      }
    }/*End of if ((ComM_Channels[chIndex].ManagedChnl == COMM_TRUE)*/
    #endif /* End of #if (COMM_REFERENCE_CHANEL == STD_ON) */
    /* Change sub state to Network Requested */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
  } /* End of if (ComM_ReqedComModeCnt[chIndex] != COMM_ZERO) */
  else
  {
    /* @Trace: ComM_SUD_API_669 */
    /* do nothing */
  }
} /* End of ComM_SwithFullModeReference */

/*******************************************************************************
** Function Name        : ComM_PNCNetwReq_PassiveGW                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check the condition for implement**
**                        function ComM PNC network requested in passive      **
**                        gateway                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : pncIndex, handleChnlId                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Pncs, ComM_RequestedPNCMode, ComM_Channels     **
**                        ComM_ComSignal,ComM_ChannelMapArray,                **
**                        ComM_PncRxERASignal, ComM_SignalTxMapArray          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ProcessTxSignal                                **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09243 SRS_ComM_AR_00013  */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if (COMM_PNC_GW_ENABLED == STD_ON)
#if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
FUNC(void, COMM_CODE)
  ComM_PNCNetwReq_PassiveGW(PNCHandleType pncIndex, uint8 handleChnlId)
{
  /* @Trace: ComM_SUD_API_677 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* Com signal index */
  uint16 signalIndex;
  /* Value for count Com signal */
  uint16 signalCount;
  /* Variable for store COm signal Id */
  uint16 signalHandleId;
  /* Signal byte index */
  uint8 byteIndex;
  /* Signal bit index */
  uint8 bitIndex;
  /* Mask set value */
  uint8 mask;
  /* store ComM channel ID */
  uint8 channelId;
  /* Channel index value */
  uint8 handleChnlIndex;
  /* Variables for store Pnc Id */
  PNCHandleType tmpPncId;
  #if ((COMM_ACTIVE_GATEWAY_PRESENT == STD_ON) &&\
    (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON) &&\
    (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON))
  /* The variable is used for passive gateway User No COMM Request */
  boolean pncUserFlag;
  /* Flag for Rx sig nal of ERA */
  boolean activeRxERA;
  #endif
  /* Number of ComM Com signal */
  uint16 noOfComMSignal;
  /* Signal Tx index */
  uint16 signalTxIndex;
  /* Set or clear PNC */
  boolean isPncCleared;

  /* Initial of number total ComM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;
  /* Get PNC id */
  /* polyspace +1 RTE:UNR [Not a defect:Low] "This is used to fix UNECE violation and has no impact" */
  if (pncIndex < COMM_TOTAL_PNCS)
  {
    tmpPncId = ComM_Pncs[pncIndex].PncId;
    #if ((COMM_ACTIVE_GATEWAY_PRESENT == STD_ON) &&\
        (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON) &&\
        (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON))
    /* Initialization of ACTIVE Rx ERA */
    activeRxERA = COMM_FALSE;
    /* Initial of userPnc flag */
    pncUserFlag = COMM_FALSE;

    if (PNC_USER_NO_COMM == ComM_RequestedPNCMode[pncIndex])
    {
      /* @Trace: ComM_SUD_API_678 */
      /* set flag for user request com mode no com */
      pncUserFlag = COMM_TRUE;
    }
    else
    {
      /* @Trace: ComM_SUD_API_679 */
      /* Do nothing */
    }

    /* Signal Instance Index associated with the PNC */
    signalIndex = ComM_Pncs[pncIndex].ComSignalIndex;
    /* Signal Count of the PNC */
    signalCount = ComM_Pncs[pncIndex].NoOfComSignal;
    while (signalCount != COMM_ZERO)
    {
      /* Get the Channel Id from Com Signal*/
      channelId = ComM_ComSignal[signalIndex].ComMChannelId;
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      handleChnlIndex = ComM_ChannelMapArray[channelId];
      #else
      handleChnlIndex = channelId;
      #endif
      if ((COMM_ACTIVE_GW == ComM_Channels[handleChnlIndex].PncGatewayType) &&
          (COMM_RX == ComM_ComSignal[signalIndex].ComMPncComSigDir) &&
          (COMM_ERA == ComM_ComSignal[signalIndex].ComMPncComSignalKind))
      {
        /* @Trace: ComM_SUD_API_680 */
        if (COMM_TRUE ==
          ComM_PncRxERASignal[(pncIndex*noOfComMSignal) + signalIndex])
        {
          /* @Trace: ComM_SUD_API_681 */
          activeRxERA = COMM_TRUE;
          /* Condition to break from Loop*/
          signalCount = COMM_ZERO;
        }
        else
        {
          /* @Trace: ComM_SUD_API_682 */
          /* Decrement the Number of Signals */
          signalCount--;
        }
      } /* End of if ((COMM_ACTIVE_GW == ComM_Channels[handleChnlIndex]... */
      else
      {
        /* @Trace: ComM_SUD_API_683 */
        /* Decrement the Number of Signals */
        signalCount--;
      }
      /* Increment the Signal Index */
      signalIndex++;
    }
    #endif /* End of #if ((COMM_ACTIVE_GATEWAY_PRESENT == STD_ON) &&\
        (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON) &&\
        (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)) */

    /* Signal Instance Index associated with the PNC */
    signalIndex = ComM_Pncs[pncIndex].ComSignalIndex;
    /* Signal Count of the PNC */
    signalCount = ComM_Pncs[pncIndex].NoOfComSignal;
    while (signalCount != COMM_ZERO)
    {
      /* Get the Channel Id from Com Signal*/
      channelId = ComM_ComSignal[signalIndex].ComMChannelId;
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      handleChnlIndex = ComM_ChannelMapArray[channelId];
      #else
      handleChnlIndex = channelId;
      #endif

      if ((handleChnlId == handleChnlIndex) && \
        (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir))
      {
        /* @Trace: ComM_SUD_API_684 */
        /*Calculation Of Byte Index*/
        byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
          ComM_ComSignal[signalIndex].ComMPncVectorOffset;

        /*Calculation Of Bit Index within the Byte */
        bitIndex = (uint8)(tmpPncId % COMM_EIGHT);

        /*Calculating the Mask Value for the bit Index*/
        mask = (uint8)(COMM_ONE << bitIndex);

        /*Get Signal Tx Index from Signal Index*/
        signalTxIndex = ComM_SignalTxMapArray[signalIndex];
        /* Get the signal ID */
        signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;
        #if ((COMM_ACTIVE_GATEWAY_PRESENT == STD_ON) &&\
          (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON) &&\
          (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON))
        if ((COMM_FALSE != activeRxERA) && (COMM_TRUE == pncUserFlag))
        {
          /* @Trace: ComM_SUD_API_685 */
          /* Set Rx signal to 0 */
          ComM_PncRxERASignal[(pncIndex*noOfComMSignal) + signalIndex] = COMM_FALSE;
          isPncCleared = COMM_TRUE;
        } /* End of if (((!activeRxERA) && pncUserFlag) == COMM_TRUE) */
        else
        #endif
        {
          /* @Trace: ComM_SUD_API_686 */
          /* Set Rx signal to 1 */
          ComM_PncRxERASignal[(pncIndex*noOfComMSignal) + signalIndex] = COMM_TRUE;
          isPncCleared = COMM_FALSE;
        }
        ComM_ProcessTxSignal(signalTxIndex, signalHandleId, byteIndex, mask, isPncCleared);
      } /* End of if ((handleChnlId == handleChnlIndex) &&
          (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir)) */
      /* increase signal index */
      signalIndex++;
      /* decrement  signal count value */
      signalCount--;
    }
  }

  #else
  /* ========================== Implement for Post-Build ==================== */
  /* Com signal index */
  uint16 signalIndex;
  /* Value for count Com signal */
  uint16 signalCount;
  /* Variable for store COm signal Id */
  uint16 signalHandleId;
  /* Signal byte index */
  uint8 byteIndex;
  /* Signal bit index */
  uint8 bitIndex;
  /* Mask set value */
  uint8 mask;
  /* Mask clear value */
  uint8 maskClear;
  /* store ComM channel ID */
  uint8 channelId;
  /* Channel index value */
  uint8 handleChnlIndex;
  /* Variables for store Pnc Id */
  PNCHandleType tmpPncId;
  /* The variable is used for passive gateway User No COMM Request */
  boolean pncUserFlag;
  /* Flag for Rx sig nal of ERA */
  boolean activeRxERA;
  /* Number of ComM Com signal */
  uint16 noOfComMSignal;
  /* Signal Tx index */
  uint16 signalTxIndex;

  /* Initial of number total ComM Com signal */
  noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;
  /* Get PNC id */
  tmpPncId = ComM_PncsGlobal[pncIndex].PncId;
  /* Initialization of ACTIVE Rx ERA */
  activeRxERA = COMM_FALSE;
  /* Initial of userPnc flag */
  pncUserFlag = COMM_FALSE;

  if (PNC_USER_NO_COMM == ComM_RequestedPNCMode[pncIndex])
  {
    /* @Trace: ComM_SUD_API_688 */
    /* set flag for user request com mode no com */
    pncUserFlag = COMM_TRUE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_689 */
    /* Do nothing */
  }

  /* Signal Instance Index associated with the PNC */
  signalIndex = ComM_PncsGlobal[pncIndex].ComSignalIndex;
  /* Signal Count of the PNC */
  signalCount = ComM_PncsGlobal[pncIndex].NoOfComSignal;
  while (signalCount != COMM_ZERO)
  {
    /* Get the Channel Id from Com Signal*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    channelId = ComM_ComSignal[signalIndex].ComMChannelId;
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    handleChnlIndex = ComM_ChannelMapArray[channelId];
    #else
    handleChnlIndex = channelId;
    #endif

    if ((COMM_ACTIVE_GW == ComM_Channels[handleChnlIndex].PncGatewayType) && \
        (COMM_RX == ComM_ComSignal[signalIndex].ComMPncComSigDir) && \
        (COMM_ERA == ComM_ComSignal[signalIndex].ComMPncComSignalKind))
    {
      /* @Trace: ComM_SUD_API_690 */
      if (COMM_TRUE ==
        ComM_PncRxERASignal[(pncIndex*noOfComMSignal) + signalIndex])
      {
        /* @Trace: ComM_SUD_API_691 */
        activeRxERA = COMM_TRUE;
        /* Condition to break from Loop*/
        signalCount = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_692 */
        /* Decrement the Number of Signals */
        signalCount--;
      }
    } /* End of if ((COMM_ACTIVE_GW == ComM_Channels[handleChnlIndex]... */
    else
    {
      /* @Trace: ComM_SUD_API_693 */
      /* Decrement the Number of Signals */
      signalCount--;
    }
    /* Increment the Signal Index */
    signalIndex++;
  }

  /* Signal Instance Index associated with the PNC */
  signalIndex = ComM_PncsGlobal[pncIndex].ComSignalIndex;
  /* Signal Count of the PNC */
  signalCount = ComM_PncsGlobal[pncIndex].NoOfComSignal;
  while (signalCount != COMM_ZERO)
  {
    /* Get the Channel Id from Com Signal*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    channelId = ComM_ComSignal[signalIndex].ComMChannelId;
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    handleChnlIndex = ComM_ChannelMapArray[channelId];
    #else
    handleChnlIndex = channelId;
    #endif

    if ((handleChnlId == handleChnlIndex) && \
      (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir))
    {
      /* @Trace: ComM_SUD_API_694 */
      /*Calculation Of Byte Index*/
      byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
                              ComM_ComSignal[signalIndex].ComMPncVectorOffset;
      /*Calculation Of Bit Index within the Byte */
      bitIndex = (uint8)(tmpPncId % COMM_EIGHT);
      /*Calculating the Mask Value for the bit Index*/
      mask = (uint8)(COMM_ONE << bitIndex);
      /*Get Signal Tx Index from Signal Index*/
      signalTxIndex = ComM_SignalTxMapArray[signalIndex];

      if ((COMM_FALSE != activeRxERA) && (COMM_TRUE == pncUserFlag))
      {
        /* @Trace: ComM_SUD_API_695 */
        maskClear = (~mask);
        /* PNC Bit for all Com signals assigned as TX: 0*/
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] & maskClear);
        /* Set Rx signal to 0 */
        ComM_PncRxERASignal[(pncIndex*noOfComMSignal) + signalIndex] =
                                                                    COMM_FALSE;
      } /* End of if (((!activeRxERA) && pncUserFlag) == COMM_TRUE) */
      else
      {
        /* @Trace: ComM_SUD_API_696 */
        /* set signal to send */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] | mask);
        /* Set Rx signal to 1 */
        ComM_PncRxERASignal[(pncIndex*noOfComMSignal) + signalIndex] =
                                                                    COMM_TRUE;
      }
      /* Get the signal ID */
      signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;
      /* Invoke ComSendSignal of Com */
      (void)Com_SendSignal(signalHandleId, (const void*)ComM_SignalTx[signalTxIndex]);
    } /* End of if ((handleChnlId == handleChnlIndex) &&
        (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir)) */
    /* increase signal index */
    signalIndex++;
    /* decrement  signal count value */
    signalCount--;
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCNetwReq_PassiveGW */
#endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
#endif /* #if (COMM_PNC_GW_ENABLED == STD_ON) */
#endif
/*******************************************************************************
** Function Name        : ComM_ClearGlobalVariables                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is part of ComM_DeInit service         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels, ComM_NvmChannelInhibition,           **
**                        ComM_CurComMode, ComM_ReqedComModeCnt,              **
**                        ComM_SubComMode, ComM_NmIndication,                 **
**                        ComM_ModeRequested, ComM_PncReqtedflag              **
**                        ComM_RequestedComMode                               **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_ClearGlobalVariables(void)
{
  #if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) &&\
   ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
   (COMM_MODE_LIMITATION_ENABLED == STD_ON)))
  #if (COMM_NVMSTORE_CHANNELS != COMM_ZERO)
  uint8 channelInhibitionProtect = COMM_ZERO;
  #endif
  #endif
  /* variable for temp index value */
  uint16 arrIndex;

  /* @Trace: ComM_SUD_API_015 */
  #if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)\
    && ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON)))
  #if (COMM_NVMSTORE_CHANNELS != COMM_ZERO)
  for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_CHANNELS ; arrIndex++)
  {
    /*Stores only the channel inhibition whose NVM Storage is TRUE*/
    if (COMM_TRUE == ComM_Channels[arrIndex].NoWakeUpNvmStorage)
    {
      /* @Trace: ComM_SUD_API_016 */
      ComM_NvmChannelInhibition[channelInhibitionProtect] =
        ComM_ChannelInhibition[arrIndex];
      channelInhibitionProtect++;
    }
  }
  #endif
  #endif /* End of if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) &&
          * ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
          * (COMM_MODE_LIMITATION_ENABLED == STD_ON))) */
  /*************************************************************************
  ** Design Taken: In Module COMM_UNINIT Reset the global variables to ZERO
  *************************************************************************/

  /* Load default states into global variables*/
  for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_CHANNELS ; arrIndex++)
  {
    /* Clear all current communication modes */
    ComM_CurComMode[arrIndex] = COMM_NO_COMMUNICATION;

    /* Clear all requests for communication modes */
    ComM_ReqedComModeCnt[arrIndex] = COMM_ZERO;

    /* Clear all sub communication modes */
    ComM_SubComMode[arrIndex] = COMM_NO_COM_NO_PENDING_REQUEST;

    /* Clear all Nm indications */
    ComM_NmIndication[arrIndex] = COMM_ZERO;

    /* Clear if any requests were done for SM */
    ComM_ModeRequested[arrIndex] = COMM_FALSE;

    /* Clear if Pnc com requested received PNC signal info */
    ComM_PncReqtedflag[arrIndex] = COMM_FALSE;
  }

  /* Load default state for user */
  for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_USERS; arrIndex++)
  {
    /* Clear all user requests */
    ComM_RequestedComMode[arrIndex] = COMM_NO_COMMUNICATION;
  }
}
/*******************************************************************************
** Function Name        : ComM_FullComNetwReqSetFlagMode                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is part of ComM_FullComNetwReq service **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : flagMode                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels, ComM_ChannelInhibition,              **
**                        ComM_LimitEcuToNoCom, ComM_SubComMode,              **
**                        ComM_TimeCnt, ComM_ReqedComModeCnt,                 **
**                        ComM_DcmActiveDiagnostic, ComM_NmIndication         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_FullComNetwReqSubOne(),ComM_SwitchComMMode()   **
*******************************************************************************/
#if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
FUNC(uint8, COMM_CODE) ComM_FullComNetwReqSetFlagMode(uint8 chIndex)
#else
FUNC(void, COMM_CODE) ComM_FullComNetwReqSetFlagMode(uint8 chIndex)
#endif
{
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  /* Variable to store the flag if NM is in different mode */
  uint8 flagMode;
  #endif
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  /* Clear Timer State */
  flagMode = COMM_ZERO;
  #endif

  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;

  /* Traceable SWS_ComM_00915, SWS_ComM_01017 */
  #if ((COMM_LINSLAVE_NMVARIANT_SUPPORT == STD_ON) ||\
      (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
  if ((COMM_NMVARIANT_PASSIVE == tmpNmVariant) ||\
      ((COMM_NMVARIANT_LINSLAVE == tmpNmVariant) &&\
      (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])))
  {
    /* @Trace: ComM_SUD_API_324 */
    /* Change sub state to Ready Sleep */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
  }
  else
  {
    /* @Trace: ComM_SUD_API_325 */
    /* Do nothing */
  }
  #endif

  /* Traceable SWS_ComM_00826 */
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
       (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
  if ((COMM_NMVARIANT_FULL == tmpNmVariant) ||
    (COMM_NMVARIANT_PASSIVE == tmpNmVariant))
  {
    /* @Trace: ComM_SUD_API_326 */
    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();
    if ((COMM_PREPBUSSLEEPMODE_IND == ComM_NmIndication[chIndex])
      #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
      && (COMM_FALSE == ComM_NmRequestProcessing[chIndex])
      #endif
      )
    {
      /* @Trace: ComM_SUD_API_327 */
      /* Switch to Silent Comm Mode from Full Communication */
      ComM_SwitchComMMode(chIndex, COMM_SILENT_COMMUNICATION);
      ComM_NmIndication[chIndex] = COMM_ZERO;
      /* Exit Data Protection */
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
    else
    {
      /* @Trace: ComM_SUD_API_328 */
      /* Exit Data Protection */
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
  }
  #endif

  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  /* Check if Nm Variant is light or None and Check for
   *     No Full Comm Mode or Active Diagnostic Disabled  */
  if ((COMM_NMVARIANT_LIGHT == tmpNmVariant) ||
    (COMM_NMVARIANT_NONE == tmpNmVariant))
  {
    /* @Trace: ComM_SUD_API_329 */
    flagMode = ComM_FullComNetwReqSubOne(chIndex);
  }
  #endif /* if Nm Variant is light or none */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  SchM_Enter_ComM_CURRENT_MODE_PROTECTION();
  /* Check for channel inhibition condition and
       Limit ECU to No Com by masking with 0xF0 & check if bit 4 is set*/
  if (((COMM_LIMITCHANNELTONOCOMM_MASK_SET ==
    (ComM_ChannelInhibition[chIndex] & COMM_LIMITCHANNELTONOCOMM_MASK_SET)) ||
    (COMM_TRUE == ComM_LimitEcuToNoCom)) &&
    (COMM_TRUE != ComM_DcmActiveDiagnostic[chIndex]))
  {
    /* @Trace: ComM_SUD_API_330 */
    /* Change sub state to Ready Sleep */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
    /* Clear User Request, if any */
    if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
    {
      /* @Trace: ComM_SUD_API_331 */
      ComM_ReqedComModeCnt[chIndex] = COMM_ZERO;
    }

    #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)

    /* Check if Nm Variant is light or None and Check for
     *   No Full Comm Mode or Active Diagnostic Disabled  */
    if (COMM_NMVARIANT_LIGHT == tmpNmVariant)
    {
      /* @Trace: ComM_SUD_API_332 */
      /* Start the Nm light time out duration in full
       *   Communication */
      ComM_TimeCnt[chIndex] = ComM_Channels[chIndex].NmLightTimeout;
    }
    #endif
  } /* End of if (((COMM_LIMITCHANNELTONOCOMM_MASK_SET == */
  SchM_Exit_ComM_CURRENT_MODE_PROTECTION();
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
          *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  return flagMode;
  #endif
}
/*******************************************************************************
** Function Name        : ComM_FullComReadySleepReleaseNmBus                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is part of ComM_FullComReadySleep      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelInhibition, ComM_Channels,              **
**                        ComM_NmRequested, ComM_ReqedComModeCnt,             **
**                        ComM_NmIndication                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Nm_NetworkRelease(), ComM_SwitchComMMode()          **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_FullComReadySleepReleaseNmBus(uint8 chIndex)
{
  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;

  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;

  Std_ReturnType returnValue = E_NOT_OK;
  #endif

  /* @Trace: ComM_SUD_API_411 */
  /* Traceable SWS_ComM_00133 */
  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Check NM Variant is FULL */
  if ((COMM_NMVARIANT_FULL == tmpNmVariant) &&\
      (COMM_ZERO != ComM_NmRequested[chIndex]))
  {
    /* Release Nm Bus Communication */
    returnValue = Nm_NetworkRelease(ComM_Channels[chIndex].ChannelId);
    if (E_OK == returnValue)
    {
      /* @Trace: ComM_SUD_API_412 */
      /* Resetting the Nm Request global variable */
      ComM_NmRequested[chIndex] = COMM_ZERO;
    }
    else
    {
      /* @Trace: ComM_SUD_API_745 */
      /* do nothing */
    }
  }
  #endif /* #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */

  /* Traceable SWS_ComM_00637 */
  SchM_Enter_ComM_NM_INDICATION_PROTECTION();
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  if (COMM_PREVENTWAKEUP_MASK_SET != (ComM_ChannelInhibition[chIndex] &
    COMM_PREVENTWAKEUP_MASK_SET))
  #endif
  {
    /* @Trace: ComM_SUD_API_413 */
    /*
     * Check if requested mode is NO Communication
     * or if Bus Sleep Mode indication
     */
    if ((COMM_ZERO == ComM_ReqedComModeCnt[chIndex]) &&
        (COMM_BUSSLEEPMODE_IND == ComM_NmIndication[chIndex]))
    {
      /* @Trace: ComM_SUD_API_414 */
      /* Switch to No communication */
      ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
      ComM_NmIndication[chIndex] = COMM_ZERO;
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
    else
    {
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
      /* @Trace: ComM_SUD_API_415 */
      /* do nothing */
    }
  }
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  else if (COMM_BUSSLEEPMODE_IND == ComM_NmIndication[chIndex])
  {
    /* @Trace: ComM_SUD_API_416 */
    /* Switch to No communication */
    ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
    ComM_NmIndication[chIndex] = COMM_ZERO;
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
  else
  {
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    /* @Trace: ComM_SUD_API_417 */
    /* To avoid MISRA warning */
  }
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */
}
/*******************************************************************************
** Function Name        : ComM_FullComReadySleepSwitchMode                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is part of ComM_FullComReadySleep      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelInhibition, ComM_LimitEcuToNoCom,       **
**                        ComM_SubComMode, ComM_Channels,                     **
**                        ComM_DcmActiveDiagnostic, ComM_NmIndication         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode(), ComM_SwithFullModeReference  **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_FullComReadySleepSwitchMode(uint8 chIndex)
{
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;

  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;
  #endif

  /* Check requested full communication
   * Check mode communication limitation */
  /* Traceable SWS_ComM_00882 */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
     (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  /* Check For Inhibition */
  if ((COMM_PREVENTWAKEUP_MASK_SET !=
    (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET)) &&
    (COMM_TRUE != ComM_LimitEcuToNoCom))
  #endif
  {
    /* @Trace: ComM_SUD_API_425 */
    ComM_SwithFullModeReference(chIndex);
  }

  /* Check DCM indicate active diagnostic
   * Limitation communication shall temporarily be inactive */
  /* Traceable SWS_ComM_00883 */
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
       (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
  if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
  {
  	/* polyspace +3 MISRA-C3:14.3 [Justified:Low] "This condition be false with different configruation" */
    if ((COMM_NMVARIANT_FULL == tmpNmVariant) ||\
      (COMM_NMVARIANT_LIGHT == tmpNmVariant) ||\
      (COMM_NMVARIANT_NONE == tmpNmVariant))
    {
      /* @Trace: ComM_SUD_API_426 */
      /* Change sub state to Network Requested */
      ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
    }
  }
  SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
  #endif
  /* Traceable SWS_ComM_00826 */
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
       (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
  if ((COMM_NMVARIANT_FULL == tmpNmVariant) ||
    (COMM_NMVARIANT_PASSIVE == tmpNmVariant))
  {
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();
    /* @Trace: ComM_SUD_API_427 */
    if ((COMM_PREPBUSSLEEPMODE_IND == ComM_NmIndication[chIndex])
      #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
      && (COMM_FALSE == ComM_NmRequestProcessing[chIndex])
      #endif
      )
    {
      /* @Trace: ComM_SUD_API_428 */
      /* Switch to Silent Comm Mode from Full Communication */
      ComM_SwitchComMMode(chIndex, COMM_SILENT_COMMUNICATION);
      ComM_NmIndication[chIndex] = COMM_ZERO;
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
    else
    {
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
  }
  #endif
}
#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : ComM_NoComNoPendingReleaseNmBus                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is a sub-function of                   **
**                        ComM_NoComNoPendingRequest service                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels, ComM_NmRequested                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Nm_NetworkRelease                                   **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_NoComNoPendingReleaseNmBus(uint8 chIndex)
{
  Std_ReturnType returnValue = E_NOT_OK;

  /* Traceable SWS_ComM_00288 */
  /*
   * Invoke Nm_NetworkRelease if ComM has requested the Nm
   * Nm_NetworkRequest or Nm_PassiveStartup for that channel
   * before and has not yet released it.
   */
  if ((COMM_INTERNAL != ComM_Channels[chIndex].BusType) &&\
      (COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant) &&\
      (COMM_ZERO != ComM_NmRequested[chIndex]))
  {
    /* Release Nm Bus Communication */
    returnValue = Nm_NetworkRelease(ComM_Channels[chIndex].ChannelId);
    if (E_OK == returnValue)
    {
      /* @Trace: ComM_SUD_API_475 */
      /* Resetting the Nm Request global variable */
      ComM_NmRequested[chIndex] = COMM_ZERO;
    }
    else
    {
      /* @Trace: ComM_SUD_API_736 */
      /* do nothing */
    }
  }
  else
  {
    /* @Trace: ComM_SUD_API_476 */
    /* Do nothing */
  }
}
#endif /* #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */
/*******************************************************************************
** Function Name        : ComM_CheckPassiveAndSyncWakeUp                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is a sub-function of                   **
**                        ComM_NoComNoPendingRequest service                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : passiveWakeFlag                                     **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_NmIndication, ComM_WakeupIndication,           **
**                        ComM_SubComMode, ComM_ManagingSetMode               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
FUNC(boolean, COMM_CODE) ComM_CheckPassiveAndSyncWakeUp(uint8 chIndex)
{
  /* Variable to store passive wake up */
  boolean passiveWakeFlag;

  #if (COMM_REFERENCE_CHANEL == STD_ON)
  /* Managing channel index */
  uint8 managingId;

  /* Managing channel id temp */
  uint8 managingChnlId;
  #endif

  /* Clear wakeup flag */
  passiveWakeFlag = COMM_FALSE;

  /* @Trace: ComM_SUD_API_480 */
  /* Check for Passive wakeup and Synchronous Wakeup enabled */
  /*
   * Traceable SWS_ComM_00694, SWS_ComM_00893, SWS_ComM_01014,
   * SWS_BSW_01015
   */
  SchM_Enter_ComM_NM_INDICATION_PROTECTION();
  if (COMM_TRUE == ComM_WakeupIndication[chIndex])
  {
    /* @Trace: ComM_SUD_API_481 */
    /* Set Passive Comm Flag */
    passiveWakeFlag = COMM_TRUE;

    /* Check the channel is managed channel */
    #if (COMM_REFERENCE_CHANEL == STD_ON)
    if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl)
    {
      /* @Trace: ComM_SUD_API_482 */
      /* get managing channel id */
      managingChnlId = ComM_Channels[chIndex].IdOfManagingChnl;
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      managingId = ComM_ChannelMapArray[managingChnlId];
      #else
      managingId = managingChnlId;
      #endif
      if (COMM_NO_COM_NO_PENDING_REQUEST == ComM_SubComMode[managingId])
      {
        /* @Trace: ComM_SUD_API_483 */
        /* Set flag for the managing channel */
        ComM_ManagingSetMode[managingId] = COMM_TRUE;
      }
      else
      {
        /* @Trace: ComM_SUD_API_484 */
        /* do nothing */
      }
    } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl) */
    else
    {
      /* @Trace: ComM_SUD_API_485 */
      /* do nothing */
    }
    #endif /* end of #if (COMM_REFERENCE_CHANEL == STD_ON) */
  } /* End of if (COMM_TRUE == ComM_WakeupIndication[chIndex]) */
  else
  {
    /* @Trace: ComM_SUD_API_486 */
    /* Do nothing */
  }
  /* Check For Nm Start Indication */
  /* Traceable SWS_ComM_00051, SWS_ComM_00583 */
  if (COMM_NMSTART_IND == ComM_NmIndication[chIndex])
  {
    /* @Trace: ComM_SUD_API_487 */
    ComM_NmIndication[chIndex] = COMM_ZERO;

    /* Set Passive Comm Flag */
    passiveWakeFlag = COMM_TRUE;
  }
  /* Check For Nm Restart Indication */
  /* Traceable SWS_ComM_00894 */
  else if (COMM_NMRST_IND == ComM_NmIndication[chIndex])
  {
    /* @Trace: ComM_SUD_API_488 */
    /* Nm Restart Indication implemented so clear Nm indication */
    ComM_NmIndication[chIndex] = COMM_ZERO;

    /* Set Passive Comm Flag */
    passiveWakeFlag = COMM_TRUE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_489 */
    /* Do nothing */
  }
  SchM_Exit_ComM_NM_INDICATION_PROTECTION();

  /* Check channel is referenced by another channel requested full mode */
  #if (COMM_REFERENCE_CHANEL == STD_ON)
  if ((COMM_TRUE == ComM_ManagingSetMode[chIndex]) &&
    (COMM_TRUE == ComM_Channels[chIndex].ManagingChnl))
  {
    /* @Trace: ComM_SUD_API_490 */
    passiveWakeFlag = COMM_TRUE;
  }
  #endif
  
  return (passiveWakeFlag);
}

/*******************************************************************************
** Function Name        : ComM_NoComNoPendingRequestSetSubMode                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is a sub-function of                   **
**                        ComM_NoComNoPendingRequest service                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_SubComMode                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_NoComNoPendingRequestSetSubMode(uint8 chIndex,
  boolean fullFlag, boolean passiveWakeFlag)
{
  if ((COMM_TRUE == fullFlag) || (COMM_TRUE == passiveWakeFlag))
  {
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    if ((COMM_INTERNAL != ComM_Channels[chIndex].BusType) &&\
        (COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant))
    {
      if (COMM_ZERO == ComM_NmRequested[chIndex])
      {
        /* @Trace: ComM_SUD_API_743 */
        ComM_SubComMode[chIndex] = COMM_NO_COM_REQUEST_PENDING;
      }
      else
      {
        /* @Trace: ComM_SUD_API_742 */
        /* Do nothing */
      }
    }
    else
    {
      /* @Trace: ComM_SUD_API_741 */
      ComM_SubComMode[chIndex] = COMM_NO_COM_REQUEST_PENDING;
    }
    #else
    {
      /* @Trace: ComM_SUD_API_533 */
      ComM_SubComMode[chIndex] = COMM_NO_COM_REQUEST_PENDING;
    }
    #endif
  }
  else
  {
  /* @Trace: ComM_SUD_API_534 */
  /* Do nothing */
  }
}

#if((COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) || (COMM_INTERNALBUS_PRESENT == STD_ON))
/*******************************************************************************
** Function Name        : ComM_FullComModePassiveWakeUp                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is a sub-function of                   **
**                        ComM_NoComRequestPending service                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex, passiveWakeFlag                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_Channels,ComM_SubComMode,ComM_TimeCnt,         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode(), Nm_PassiveStartUp()          **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_FullComModePassiveWakeUp(uint8 chIndex, boolean
  passiveWakeFlag)
{
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  /* Variable to Store the BusType when bus is not internal */
  uint8 busIndex;

  /* Get the BusType */
  busIndex = ComM_Channels[chIndex].BusType;
  #endif
  #endif
  
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_OFF) &&\
    (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_OFF))
  COMM_UNUSED(passiveWakeFlag);
  #endif

  /* If the bus type is other than Internal */
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  if (COMM_INTERNAL != busIndex)
  #endif
  {
    /* @Trace: ComM_SUD_API_705*/
    /* Switch to Full Communication Mode from No Communication */
    ComM_SwitchComMMode(chIndex, COMM_FULL_COMMUNICATION);

    /* Change sub state to Network Requested */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
    /* Traceable SWS_ComM_00886 */
    #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
      (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
    SchM_Enter_ComM_INHIBIT_CNT_PROTECTION();
    /* Start the Min amount of duration in full Communication counter */
      ComM_TimeCnt[chIndex] = ComM_Channels[chIndex].MinFullComMode;
    SchM_Exit_ComM_INHIBIT_CNT_PROTECTION();
    #endif
    /* Traceable SWS_ComM_00665 */
    #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
      (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))

    if ((COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant) ||
      (COMM_NMVARIANT_PASSIVE == ComM_Channels[chIndex].NmVariant))
    {
      /* @Trace: ComM_SUD_API_706*/
      /* If the Passive wake up is set */
      if (COMM_TRUE == passiveWakeFlag)
      {
        /* @Trace: ComM_SUD_API_707*/
        /* Request Nm Bus Communication */
        (void)Nm_PassiveStartUp(ComM_Channels[chIndex].ChannelId);

        /* Set Flag for Nm is requested for Passive start up */
        ComM_NmRequested[chIndex] = COMM_ONE;
      }
    }
    #endif /* Nm Variant Full or Passive */
  } /* End of if (COMM_INTERNAL != busIndex) */
  /* If the bus type is Internal */
  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  else
  #endif
  #endif /* (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
  #if (COMM_INTERNALBUS_PRESENT == STD_ON)
  {
    /* @Trace: ComM_SUD_API_708*/
    /* Switch to Full Communication Mode from No Communication */
    ComM_SwitchComMMode(chIndex, COMM_FULL_COMMUNICATION);

    /* Change sub state to Network Requested */
    ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;

    /* Start the Min amount of duration in full Communication counter */
    ComM_TimeCnt[chIndex] = ComM_Channels[chIndex].MinFullComMode;
  }
  #endif
}
#endif /* ((COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) || (COMM_INTERNALBUS_PRESENT == STD_ON)) */

#if (COMM_DIRECT_USER_MAPPING == STD_OFF)
/*******************************************************************************
** Function Name        : ComM_IndicatePncUserLowestMode                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Indication of actual bus mode by the corresponding  **
**                        Bus State Manager                                   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : userIndx                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_UserRteInd[]                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PncUserLowestMode()                            **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_IndicatePncUserLowestMode(uint8 userIndx)
{
  /* ComM_UserRteInd[]: variable to avoid same user indication more
    * than once to RTE, Eg: Two PNC may refer to same user */
  if (COMM_TRUE != ComM_UserRteInd[userIndx])
  {
    /* @Trace: ComM_SUD_API_063 */
    /* Indicate lowest mode of user :PNC channels and Direct channels */
    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
    ComM_PncUserLowestMode(userIndx);
    #endif
    #endif
    /* User : Executed in one of the PNC */
    ComM_UserRteInd[userIndx] = COMM_TRUE;
  }
}
#endif

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if (COMM_PNC_GW_ENABLED == STD_ON)
#if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
/*******************************************************************************
** Function Name        : ComM_ProcessTxSignal                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check the condition for implement**
**                        function ComM PNC network requested in passive      **
**                        gateway                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : signalTxIndex, signalHandleId, byteIndex            **
**                        mask, isPncCleared                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_SignalTx                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Com_SendSignal                                      **
*******************************************************************************/
FUNC(void, COMM_CODE) ComM_ProcessTxSignal(uint16 signalTxIndex,
  uint16 signalHandleId, uint8 byteIndex, uint8 mask, boolean isPncCleared)
{
  if (signalTxIndex < COMM_TOTAL_TX_SIGNALS)
  {
    if (COMM_TRUE == isPncCleared)
    {
      /* @Trace: ComM_SUD_API_750 */
      /* PNC Bit for all Com signals assigned as TX: 0*/
      ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] & (~mask));
    }
    else
    {
      /* @Trace: ComM_SUD_API_751 */
      /* set signal to send */
      ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] | mask);
    }
	/* @Trace: ComM_SUD_API_752 */
    /* Invoke ComSendSignal of Com */
    (void)Com_SendSignal(signalHandleId, (const void*)ComM_SignalTx[signalTxIndex]);
  }
}
#endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
#endif /* #if (COMM_PNC_GW_ENABLED == STD_ON) */
#endif
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
