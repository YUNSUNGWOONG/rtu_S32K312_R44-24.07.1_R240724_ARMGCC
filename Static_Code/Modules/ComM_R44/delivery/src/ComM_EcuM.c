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
**  SRC-MODULE: ComM_EcuM.c                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM EcuM Indication APIs                        **
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
** 1.1.7          31-Jan-2024         MUKim            CP44-3149              **
** 1.1.3          16-Dec-2022         ThuanVT          BUGCLASSIC-380,        **
                                                       CP44-1324, CP44-1245   **
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #27547,    **
**                                                     #29733                 **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.2          05-Apr-2021         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
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
#include "ComM_EcuM.h"
#include "BswM_ComM.h"
#include "SchM_ComM.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_EcuM_WakeUpIndication                          **
**                                                                            **
** Service ID           : 0x2a                                                **
**                                                                            **
** Description          : Notification of a WakeUp of the corresponding       **
**                        channel                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_WakeupIndication[],ComM_Channels[],            **
**                        ComM_ChannelMapArray[],ComM_PncTimeCnt[],           **
**                        ComM_PNCWakeupIndication[],ComM_SubPNCMode[],       **
**                        ComM_ChannelToPncMapping[]                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_ECUM_WAKEUP_IND(),                  **
**                        SchM_Exit_ComM_ECUM_WAKEUP_IND(),                   **
**                        SchM_Enter_ComM_PNC_PREPARE_TIMER(),                **
**                        SchM_Exit_ComM_PNC_PREPARE_TIMER(),                 **
**                        SchM_Enter_ComM_PNC_WAKEUP_IND(),                   **
**                        SchM_Exit_ComM_PNC_WAKEUP_IND(),                    **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09087 SRS_ComM_AR_00032 SRS_ComM_AR_00033
 * SRS_ComM_AR_00076 SRS_ComM_AR_00090 SRS_ComM_AR_00184 SRS_ComM_AR_00011
 * SRS_ComM_AR_00235
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_110 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
  /* variables for loop all channel */
  uint8 chnlLoop;

  #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /* Variable for Number of Pncs linked to the Channel */
  uint16 pncCnt;
  /* Variable for Pnc Index */
  PNCHandleType pncInx;
  /* Variable for channel to pnc mapping */
  PNCHandleType pncIndex;
  #endif
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)
  /* Variable to store channel */
  NetworkHandleType channelIndex;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_ECUM_WAKEUPINDICATION_SID);
  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_111 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */
    channelIndex = ComM_ChannelMapArray[Channel];
    #else
    /* Channel Id is updated into local variable */
    channelIndex = Channel;
    #endif
    #endif

    #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) &&\
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    /* Check all channel */
    for(chnlLoop = COMM_ZERO; chnlLoop < COMM_TOTAL_CHANNELS; chnlLoop++)
    {
      if (COMM_TRUE == ComM_Channels[chnlLoop].ChannelPnc)
      {
        /* @Trace: ComM_SUD_API_112 */
        /* Number of Pncs linked to the Channel */
        pncCnt = ComM_Channels[chnlLoop].PncCount;

        /* index in the Pnc index array in the User */
        pncInx = ComM_Channels[chnlLoop].PncIndex;

        /*-----Handling all the PNCs associated  with the channel------*/
        while (pncCnt != COMM_ZERO)
        {
          pncIndex = ComM_ChannelToPncMapping[pncInx];

          pncCnt--;
          SchM_Enter_ComM_PNC_WAKEUP_IND();

          /* Update Status of Global Variable wake up indication*/
          ComM_PNCWakeupIndication[pncIndex] = COMM_TRUE;

          /* Exit Data Protection */
          SchM_Exit_ComM_PNC_WAKEUP_IND();
          pncInx++;
        }
      }
      else
      {
        /* @Trace: ComM_SUD_API_113 */
        /* Do nothing */
      }
    }
    #endif
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_ECUM_WAKEUP_IND();

    /* Update Status of Global Variable wake up indication in bit 0 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(chnlLoop = COMM_ZERO; chnlLoop < COMM_TOTAL_CHANNELS; chnlLoop++)
    {
      ComM_WakeupIndication[chnlLoop] = COMM_TRUE;
    }
    #else
    /* Traceable SWS_ComM_00893, ECUC_ComM_00842, ECUC_ComM_00568 */
    ComM_WakeupIndication[channelIndex] = COMM_TRUE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_ECUM_WAKEUP_IND();

    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    /* For prevent the unused argument compiler warning */
    COMM_UNUSED(Channel);
    #endif
  } /* End of if (returnValue == E_OK) */

  #else
  /* ========================== Implement for Post-Build ==================== */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
  /* variables for loop all channel */
  uint8 chnlLoop;
/*   if (COMM_TRUE == ComM_PncEnabledFlashPB)
  { */
    /* Variable for Number of Pncs linked to the Channel */
    uint16 pncCnt;
    /* Variable for Pnc Index */
    PNCHandleType pncInx;
    /* Variable for channel to pnc mapping */
    PNCHandleType pncIndex;
  // }
  // else
  // {
    /* Do nothing */
  // }
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)
  /* Variable to store channel */
  NetworkHandleType channelIndex;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_ECUM_WAKEUPINDICATION_SID);
  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_114 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */
    channelIndex = ComM_ChannelMapArray[Channel];
    #else
    /* Channel Id is updated into local variable */
    channelIndex = Channel;
    #endif
    #endif

    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_115 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    /* Check all channel */
    for(chnlLoop = COMM_ZERO; chnlLoop < COMM_TOTAL_CHANNELS; chnlLoop++)
    {
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      if (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chnlLoop].ChannelPnc)
      {
        /* @Trace: ComM_SUD_API_116 */
        /* Number of Pncs linked to the Channel */
        pncCnt = ComM_ChannelsPNCRelatedGlobal[chnlLoop].PncCount;

        /* index in the Pnc index array in the User */
        pncInx = ComM_ChannelsPNCRelatedGlobal[chnlLoop].PncIndex;

        /*-----Handling all the PNCs associated  with the channel------*/
        while (pncCnt != COMM_ZERO)
        {
          /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          pncIndex = ComM_ChannelToPncMappingGlobal[pncInx];

          pncCnt--;
          SchM_Enter_ComM_PNC_WAKEUP_IND();

          /* Update Status of Global Variable wake up indication*/
          /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          ComM_PNCWakeupIndication[pncIndex] = COMM_TRUE;

          /* Exit Data Protection */
          SchM_Exit_ComM_PNC_WAKEUP_IND();
          pncInx++;
        }
      }
      else
      {
        /* @Trace: ComM_SUD_API_117 */
        /* Do nothing */
      }
    }
    #endif
    }
    else /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
    {
      /* @Trace: ComM_SUD_API_118 */
      /* Do nothing */
    }
    /* Enter Data Protection */
    SchM_Enter_ComM_ECUM_WAKEUP_IND();
    /* Update Status of Global Variable wake up indication in bit 0 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(chnlLoop = COMM_ZERO; chnlLoop < COMM_TOTAL_CHANNELS; chnlLoop++)
    {
      ComM_WakeupIndication[chnlLoop] = COMM_TRUE;
    }
    #else
    /* Traceable SWS_ComM_00893, ECUC_ComM_00842, ECUC_ComM_00568 */
    ComM_WakeupIndication[channelIndex] = COMM_TRUE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_ECUM_WAKEUP_IND();

    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    /* For prevent the unused argument compiler warning */
    COMM_UNUSED(Channel);
    #endif
  } /* End of if (returnValue == E_OK) */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_EcuM_WakeUpIndication */
#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_EcuM_PNCWakeUpIndication                       **
**                                                                            **
** Service ID           : 0x37                                                **
**                                                                            **
** Description          : Notification of a WakeUp on the corresponding       **
**                        partial network cluster                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : PNCid                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_WakeupIndication[],ComM_Channels[],            **
**                        ComM_ChannelMapArray[],ComM_PncTimeCnt[],           **
**                        ComM_PNCWakeupIndication[],ComM_SubPNCMode[],       **
**                        ComM_ChannelToPncMapping[]                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_ECUM_WAKEUP_IND(),                  **
**                        SchM_Exit_ComM_ECUM_WAKEUP_IND(),                   **
**                        SchM_Enter_ComM_PNC_PREPARE_TIMER(),                **
**                        SchM_Exit_ComM_PNC_PREPARE_TIMER(),                 **
**                        SchM_Enter_ComM_PNC_WAKEUP_IND(),                   **
**                        SchM_Exit_ComM_PNC_WAKEUP_IND(),                    **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00406 SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385
 * SRS_BSW_00386 SRS_ModeMgm_09248 SRS_ComM_AR_00034 SRS_ComM_AR_00183
 */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_EcuM_PNCWakeUpIndication(PNCHandleType PNCid)
{
  /* @Trace: ComM_SUD_API_119 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
  uint16 loopIndex;
  #else
  /* Number of channels mapping to this Pnc */
  uint8 noOfChannels;
  /* Pnc index address */
  PNCHandleType pncInx;
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)
  /* Index of this Pnc */
  PNCHandleType channelIndex;

  /* channel index */
  NetworkHandleType channelId;

  /* channel id temp */
  NetworkHandleType channelIdTmp;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  returnValue = E_OK;
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_120 */
    /* Report to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_ECUM_PNCWAKEUPINDICATION_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_121 */
    /* do nothing */
  }
  if (COMM_MAX_PNCID < PNCid)
  {
    /* @Trace: ComM_SUD_API_122 */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_ECUM_PNCWAKEUPINDICATION_SID, COMM_E_WRONG_PARAMETERS);
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_123 */
    /* Do nothing */
  }
  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_124 */
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
      (COMM_FRNETWORK_PRESENT == STD_ON))
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(loopIndex = COMM_ZERO; loopIndex < COMM_TOTAL_PNCS; loopIndex++)
    {
      /* Enter Data Protection */
      SchM_Enter_ComM_PNC_WAKEUP_IND();

      /* Update Status of Global Variable wake up indication*/
      ComM_PNCWakeupIndication[loopIndex] = COMM_TRUE;

      /* Exit Data Protection */
      SchM_Exit_ComM_PNC_WAKEUP_IND();
    }
    #else /* #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    /* Get Pnc index*/
    pncInx = ComM_PncMapArray[PNCid];

    /* Traceable SWS_ComM_00964 */
    /* Enter Data Protection */
    SchM_Enter_ComM_PNC_WAKEUP_IND();

    /* Update Status of Global Variable wake up indication*/
    ComM_PNCWakeupIndication[pncInx] = COMM_TRUE;

    /* Exit Data Protection */
    SchM_Exit_ComM_PNC_WAKEUP_IND();
    #endif /* End of #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
                        (COMM_FRNETWORK_PRESENT == STD_ON)) */
    /* Enter Data Protection */
    SchM_Enter_ComM_ECUM_WAKEUP_IND();

    /* Traceable SWS_ComM_01015 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(loopIndex = COMM_ZERO; loopIndex < COMM_TOTAL_CHANNELS; loopIndex++)
    {
      /* Set flag wakeup indication for all channel*/
      ComM_WakeupIndication[loopIndex] = COMM_TRUE;
    }

    #else /* #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    /* get Pnc id index */
    pncInx = ComM_PncMapArray[PNCid];
    channelIndex = ComM_Pncs[pncInx].ChannelPncIndex;
    /* Get the number of channels mapping to this Pnc */
    noOfChannels = ComM_Pncs[pncInx].NoOfChannelPnc;
    while (noOfChannels != COMM_ZERO)
    {
      /* Get the Channel from PNC Index Array */
      channelIdTmp = ComM_ChnPncInxArr[channelIndex];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        channelId = ComM_ChannelMapArray[channelIdTmp];
      #else
        channelId = channelIdTmp;
      #endif
      /* Set flag wakeup indication for channel */
      ComM_WakeupIndication[channelId] = COMM_TRUE;


      channelIndex++;
      noOfChannels--;
    } /* end of while (noOfChannels != COMM_ZERO) */
      /* End of traceable SWS_ComM_01014, ECUC_ComM_00842, ECUC_ComM_00568 */
    #endif /* End of #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */

    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    COMM_UNUSED(PNCid);
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_ECUM_WAKEUP_IND();
  } /* End of if (returnValue == E_OK) */

  #else
  /* ========================== Implement for Post-Build ==================== */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
  PNCHandleType loopIndex;
  #else
  /* Number of channels mapping to this Pnc */
  uint8 noOfChannels;
    /* Pnc index address */
  PNCHandleType pncInx;
  #endif

  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)
  /* Index of this Pnc */
  PNCHandleType channelIndex;
  /* channel index */
  NetworkHandleType channelId;
  /* channel id temp */
  NetworkHandleType channelIdTmp;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  returnValue = E_OK;
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_125 */
    /* Report to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_ECUM_PNCWAKEUPINDICATION_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_126 */
    /* do nothing */
  }
  if (COMM_MAX_PNCID < PNCid)
  {
    /* @Trace: ComM_SUD_API_127 */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_ECUM_PNCWAKEUPINDICATION_SID, COMM_E_WRONG_PARAMETERS);
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_128 */
    /* Do nothing */
  }
  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_129 */
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) || \
                                             (COMM_FRNETWORK_PRESENT == STD_ON))
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(loopIndex = COMM_ZERO; loopIndex < COMM_TOTAL_PNCS; loopIndex++)
    {
      /* Enter Data Protection */
      SchM_Enter_ComM_PNC_WAKEUP_IND();
      /* Update Status of Global Variable wake up indication*/
      ComM_PNCWakeupIndication[loopIndex] = COMM_TRUE;
      /* Exit Data Protection */
      SchM_Exit_ComM_PNC_WAKEUP_IND();
    }
    #else /* #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */

    /* Get Pnc index*/
    pncInx = ComM_PncMapArrayGlobal[PNCid];
    /* Traceable SWS_ComM_00964 */
    /* Enter Data Protection */
    SchM_Enter_ComM_PNC_WAKEUP_IND();
    /* Update Status of Global Variable wake up indication*/
    ComM_PNCWakeupIndication[pncInx] = COMM_TRUE;
    /* Exit Data Protection */
    SchM_Exit_ComM_PNC_WAKEUP_IND();
    #endif /* End of #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
                        (COMM_FRNETWORK_PRESENT == STD_ON)) */
    /* Enter Data Protection */
    SchM_Enter_ComM_ECUM_WAKEUP_IND();

    /* Traceable SWS_ComM_01015 */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(loopIndex = COMM_ZERO; loopIndex < COMM_TOTAL_CHANNELS; loopIndex++)
    {
      /* Set flag wakeup indication for all channel*/
      ComM_WakeupIndication[loopIndex] = COMM_TRUE;
    }
    #else /* #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    /* get Pnc id index */
    pncInx = ComM_PncMapArrayGlobal[PNCid];

    channelIndex = ComM_PncsGlobal[pncInx].ChannelPncIndex;
    /* Get the number of channels mapping to this Pnc */
    noOfChannels = ComM_PncsGlobal[pncInx].NoOfChannelPnc;
    while (noOfChannels != COMM_ZERO)
    {
      /* Get the Channel from PNC Index Array */
      channelIdTmp = ComM_ChnPncInxArrGlobal[channelIndex];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      channelId = ComM_ChannelMapArray[channelIdTmp];
      #else
      channelId = channelIdTmp;
      #endif
      /* Set flag wakeup indication for channel */
      ComM_WakeupIndication[channelId] = COMM_TRUE;
      channelIndex++;
      noOfChannels--;
    }
    /* End of traceable SWS_ComM_01014, ECUC_ComM_00842, ECUC_ComM_00568 */
    #endif /* End of #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    COMM_UNUSED(PNCid);
    #endif
    /* Exit Data Protection */
    SchM_Exit_ComM_ECUM_WAKEUP_IND();
  } /* End of if (returnValue == E_OK) */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_EcuM_PNCWakeUpIndication */
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
