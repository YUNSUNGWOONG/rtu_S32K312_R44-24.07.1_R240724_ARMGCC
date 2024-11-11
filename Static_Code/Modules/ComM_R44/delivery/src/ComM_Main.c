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
**  SRC-MODULE: ComM_Main.c                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of Main Functionality                               **
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
** 1.1.7_HF1      04-Mar-2024         MUKim            CP44-4011, CP44-3875   **
** 1.1.7          31-Jan-2024         MUKim            CP44-3149              **
** 1.1.5          09-Jun-2023         NamNT1           CP44-2206              **
** 1.1.4          07-Mar-2022         ThuanVT          CP44-1598, 1152        **
** 1.1.3          16-Dec-2022         ThuanVT          BUGCLASSIC-380,        **
                                                       CP44-1324, CP44-1245   **
** 1.1.0.0        12-Aug-2022         ThuanVT          R44-Redmine #27547,    **
**                                                     #29733                 **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25636,    **
**                                                     #25646, #25674         **
** 1.0.2          05-Apr-2021         HieuTM8          R44-Redmine #14793     **
**                                                     #14801, #18314         **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Internal.h"        /* ComM Internal functions header file */
/* @Trace: ComM_SUD_MACRO_002 */
/* @Trace: SRS_ComM_AR_00217 SRS_ComM_AR_00217 SRS_ComM_AR_00223
 * SRS_ComM_AR_00224 SRS_ComM_AR_00226 SRS_ComM_AR_00227 SRS_ComM_AR_00228
 * SRS_ComM_AR_00229 SRS_ComM_AR_00230 SRS_ComM_AR_00231 SRS_ComM_AR_00233
 * SRS_ComM_AR_00234 SRS_ComM_AR_00237 SRS_ComM_AR_00238 SRS_ComM_AR_00239
 */
/* @Trace: ComM_SUD_MACRO_005   */
#include "ComM_Ram.h"             /* ComM global Ram variables header file */
#include "ComM_Config.h"          /* ComM Config header file */
#include "SchM_ComM.h"            /* SchM data protection API header file */
#include "BswM_ComM.h"
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file */
#endif
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
/* @Trace: ComM_SUD_DATATYPE_001 */
#include "Com.h"
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x60                                                **
**                                                                            **
** Description          : This Service is Main function for the Channels and  **
**                        all associated PNCs of the channels                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : NetworkHandleType Channel                           **
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
**                        ComM_ChannelMapArray, ComM_InitFlag,                **
**                        ComM_CurComMode, ComM_ChannelToPncMapping[],        **
**                        ComM_SubPNCMode, ComM_Pncs, ComM_PncTimeCnt         **
**                        ComM_Channels                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_PNCFullMode(),              **
**                        ComM_PNCNoMode(),ComM_NoComMode(),ComM_FullComMode()**
**                        ComM_SilentComMode()                                **
*******************************************************************************/
/* @Trace: SRS_BSW_00386 SRS_BSW_00406 SRS_ModeMgm_09080 SRS_ComM_AR_00010
 * SRS_ComM_AR_00016 SRS_ComM_AR_00017 SRS_ComM_AR_00018 SRS_ComM_AR_00023
 * SRS_ComM_AR_00028 SRS_ComM_AR_00030 SRS_ComM_AR_00039 SRS_ComM_AR_00061
 * SRS_ComM_AR_00155 SRS_BSW_00373 SRS_ComM_AR_00029 SRS_ComM_AR_00056
 * SRS_ComM_AR_00011 SRS_ComM_AR_00059 SRS_ComM_AR_00063 SRS_ComM_AR_00123
 * SRS_ComM_AR_00210
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_MainFunction(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_455 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* The variable Lucindex is used as array index */
  NetworkHandleType handleChnlIndex;
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))
  /* The variable is used for PNC Index */
  PNCHandleType tmpPncIndex;

  /* The variable is used for PNC Count */
  uint16 tmpPncCount;

  /* The variable is used for Indexing*/
  PNCHandleType pncIndex;
  #endif
  #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
    STD_ON)) */

  /* Check whether the module is initialized or not */
  /* Traceable SWS_BSW_00037 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_456 */
    /* Do nothing */
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_457 */
    /* Get Channel Index */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    handleChnlIndex = ComM_ChannelMapArray[Channel];
    #else
    handleChnlIndex = Channel;
    #endif

    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))

    /* Check if the channel is part of a PNC */
    if (COMM_TRUE == ComM_Channels[handleChnlIndex].ChannelPnc)
    {
      /* @Trace: ComM_SUD_API_458 */
      tmpPncIndex = ComM_Channels[handleChnlIndex].PncIndex;
      tmpPncCount = ComM_Channels[handleChnlIndex].PncCount;
      /*State transitions of the PNC state machines */
      while (tmpPncCount != COMM_ZERO)
      {
        /* Decrement the pnc count */
        tmpPncCount--;

        /* ComM_ChannelToPncMapping[] :The Map provides Index*/
        pncIndex = ComM_ChannelToPncMapping[tmpPncIndex];

        if (COMM_PNC_NO_COMMUNICATION != ComM_SubPNCMode[pncIndex])
        {
          /* @Trace: ComM_SUD_API_459 */
          /* Call PNC State Change: Full */
          ComM_PNCFullMode(pncIndex);
        }
        else
        {
          /* @Trace: ComM_SUD_API_460 */
          /* Call PNC State Change: No */
          ComM_PNCNoMode(pncIndex);
        }
        tmpPncIndex++;
      } /*End of PNC Counts of Channel*/
    } /* End of if (COMM_TRUE == ComM_Channels[handleChnlIndex].ChannelPnc) */

    #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
            *(COMM_FRNETWORK_PRESENT == STD_ON)) */
    #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
            *STD_ON)) */

    if (COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
    {
      /* @Trace: ComM_SUD_API_461 */
      /* Call No Mode switch function*/
      ComM_NoComMode(handleChnlIndex);
    }
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_ETHNETWORK_PRESENT == STD_ON))
    else if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
    {
      /* @Trace: ComM_SUD_API_462 */
      /* Call Silent Mode switch function */
      ComM_SilentComMode(handleChnlIndex);
    }
    #endif
    else
    {
      /* @Trace: ComM_SUD_API_463 */
      /* Call Full Mode switch function */
      ComM_FullComMode(handleChnlIndex);
    }
  } /* End of Else */

  #else
  /* ========================== Implement for Post-Build ==================== */
  /* The variable Lucindex is used as array index */
  NetworkHandleType handleChnlIndex;
  /* Check config variant enabled Pnc */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* The variable is used for PNC Index */
    PNCHandleType tmpPncIndex;

    /* The variable is used for PNC Count */
    uint16 tmpPncCount;

    /* The variable is used for Indexing*/
    PNCHandleType pncIndex;
  // } End of if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // else
  // {
    /* Do nothing */
  // }

  /* Check whether the module is initialized or not */
  /* Traceable SWS_BSW_00037 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_464 */
    /* Do nothing */
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_465 */
    /* Get Channel Index */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    handleChnlIndex = ComM_ChannelMapArray[Channel];
    #else
    handleChnlIndex = Channel;
    #endif
    /* Check config variant enabled Pnc */
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_466 */
      /* Check if the channel is part of a PNC */
      /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      if (COMM_TRUE == \
                      ComM_ChannelsPNCRelatedGlobal[handleChnlIndex].ChannelPnc)
      {
        /* @Trace: ComM_SUD_API_467 */
        tmpPncIndex = ComM_ChannelsPNCRelatedGlobal[handleChnlIndex].PncIndex;
        tmpPncCount = ComM_ChannelsPNCRelatedGlobal[handleChnlIndex].PncCount;
        /*State transitions of the PNC state machines */
        while (tmpPncCount != COMM_ZERO)
        {
          /* Decrement the pnc count */
          tmpPncCount--;
          /* ComM_ChannelToPncMapping[] :The Map provides Index*/
          /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          pncIndex = ComM_ChannelToPncMappingGlobal[tmpPncIndex];
          /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          if (COMM_PNC_NO_COMMUNICATION != ComM_SubPNCMode[pncIndex])
          {
            /* @Trace: ComM_SUD_API_468 */
            /* Call PNC State Change: Full */
            ComM_PNCFullMode(pncIndex);
          }
          else
          {
            /* @Trace: ComM_SUD_API_469 */
            /* Call PNC State Change: No */
            ComM_PNCNoMode(pncIndex);
          }
          tmpPncIndex++;
        } /*End of PNC Counts of Channel*/
      } /* End of if (COMM_TRUE == ComM_Channels[handleChnlIndex].ChannelPnc) */
    } /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
    else
    {
      /* @Trace: ComM_SUD_API_470 */
      /* Do nothing */
    }

    if (COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
    {
      /* @Trace: ComM_SUD_API_471 */
      /* Call No Mode switch function*/
      ComM_NoComMode(handleChnlIndex);
    }
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
                                            (COMM_ETHNETWORK_PRESENT == STD_ON))
    else if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[handleChnlIndex])
    {
      /* @Trace: ComM_SUD_API_472 */
      /* Call Silent Mode switch function */
      ComM_SilentComMode(handleChnlIndex);
    }
    #endif
    else
    {
      /* @Trace: ComM_SUD_API_473 */
      /* Call Full Mode switch function */
      ComM_FullComMode(handleChnlIndex);
    }
  } /* End of Else */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* END OF MAIN */

/*******************************************************************************
** Function Name        : ComM_NoComMode                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_NO_COMMUNICATION mode **
**                        for the corresponding Channel index                 **
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
** Return Parameters    : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_SubComMode, ComM_CommunicationAllowedFlag      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_NoComNoPendingRequest(),                       **
**                        ComM_NoComRequestPending()                          **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00077 SRS_ComM_AR_00065 */
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
FUNC(void, COMM_CODE) ComM_NoComMode(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_535 */
  /* Variable to store passive wake up */
  boolean passiveWakeFlag;

  /* Clear wakeup flag */
  passiveWakeFlag = COMM_FALSE;

  /* If sub state is No request is pending */
  if (COMM_NO_COM_NO_PENDING_REQUEST == ComM_SubComMode[chIndex])
  {
    /* @Trace: ComM_SUD_API_536 */
    /* Process the sub state COMM_NO_COM_NO_PENDING_REQUEST */
    passiveWakeFlag = ComM_NoComNoPendingRequest(chIndex);
  }

  /* If sub state is Pending request */
  if ((COMM_NO_COM_REQUEST_PENDING == ComM_SubComMode[chIndex]) &&
    (COMM_TRUE == ComM_CommunicationAllowedFlag[chIndex]))
  {
    /* @Trace: ComM_SUD_API_537 */
    /* Process the sub state COMM_NO_COM_REQUEST_PENDING */
    ComM_NoComRequestPending(chIndex, passiveWakeFlag);
  }
} /* End of ComM_NoComMode */

/*******************************************************************************
** Function Name        : ComM_SilentComMode                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_SILENT_COMMUNICATION  **
**                        mode for the corresponding Channel index            **
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
**                        ComM_DcmActiveDiagnostic[], ComM_SubComMode[]       **
**                        ComM_ReqedComModeCnt[], ComM_NmRequested[],         **
**                        ComM_ChannelInhibition[], ComM_NmIndication[]       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode()                               **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00005 SRS_ComM_AR_00111 SRS_ComM_AR_00080 SRS_ComM_AR_00081
 * SRS_ComM_AR_00082 SRS_ComM_AR_00083 SRS_ComM_AR_00084
*/
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))

FUNC(void, COMM_CODE) ComM_SilentComMode(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_622 */
  boolean flag_FullCom;
  flag_FullCom = COMM_FALSE;
  /* If sub state is COMM_SILENT_COM */
  if (COMM_SILENT_COM == ComM_SubComMode[chIndex])
  {
    /* @Trace: ComM_SUD_API_623 */
     /* If Bus Sleep Mode indication mode is No Communication */
    /* Traceable SWS_ComM_00295 */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();
    if (COMM_BUSSLEEPMODE_IND == ComM_NmIndication[chIndex])
    {
      /* @Trace: ComM_SUD_API_624 */
      /* Switch to No Communication from Silent Communication */
      ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
      ComM_NmRequested[chIndex] = COMM_ZERO;
      ComM_NmIndication[chIndex] = COMM_ZERO;

      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
    else if(COMM_NMSTART_IND == ComM_NmIndication[chIndex])
    {
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
      ComM_NoComRequestPending(chIndex, COMM_TRUE);
    }
    else
    {
      /* @Trace: ComM_SUD_API_625 */
      /* DCM indication active diagnostic */
      /* Traceable SWS_ComM_00878 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "This condition will evaluate to false if internal bustype is configured" */
      if (COMM_INTERNAL != ComM_Channels[chIndex].BusType)
      {
        /* @Trace: ComM_SUD_API_626 */
        #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
          (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
          (COMM_NONE_NMVARIANT_SUPPORT ==STD_ON))
          if ((COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex]) &&
            ((COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant) ||
            (COMM_NMVARIANT_LIGHT == ComM_Channels[chIndex].NmVariant) ||
            (COMM_NMVARIANT_NONE == ComM_Channels[chIndex].NmVariant)))
          {
            /* @Trace: ComM_SUD_API_627 */
            /* Switch to Full Communication Mode from Silent Comm */
            flag_FullCom = COMM_TRUE;
            ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
          }
        #endif
      } /* if (ComM_Channels[chIndex].BusType != COMM_INTERNAL) */
      else
      {
        /* @Trace: ComM_SUD_API_628 */
        /* Do nothing */
      }
      /* If Network Mode indication indication by NM */
      /* Traceable SWS_ComM_00296 */
      if (COMM_NMMODE_IND == ComM_NmIndication[chIndex])
      {
        /* @Trace: ComM_SUD_API_629 */
        /* Switch to Full Communication Mode from Silent Comm */
        flag_FullCom = COMM_TRUE;

        /* Change sub state to Ready Sleep */
        ComM_SubComMode[chIndex] = COMM_FULL_COM_READY_SLEEP;
        ComM_NmIndication[chIndex] = COMM_ZERO;
      }
      else
      {
        /* @Trace: ComM_SUD_API_630 */
        /* Do nothing */
      }
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
      /* Check for User requested Mode */
      /* Traceable SWS_ComM_00877 */
      if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
      {
        /* @Trace: ComM_SUD_API_631 */
        #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
          (COMM_MODE_LIMITATION_ENABLED == STD_ON))
        if (COMM_PREVENTWAKEUP_MASK_SET !=
        (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET))
        #endif
        {
          /* @Trace: ComM_SUD_API_632 */
          /* Switch to Full Communication Mode from Silent Comm */
          flag_FullCom = COMM_TRUE;
          ComM_SubComMode[chIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
        }
      }
      else /* if (ComM_ReqedComModeCnt[chIndex] != COMM_ZERO) */
      {
        /* @Trace: ComM_SUD_API_633 */
        /* Do nothing */
      }
      /* Switch to Full Communication Mode */
      if (COMM_TRUE == flag_FullCom)
      {
        /* @Trace: ComM_SUD_API_634 */
        ComM_SwitchComMMode(chIndex, COMM_FULL_COMMUNICATION);
      }
      else
      {
        /* @Trace: ComM_SUD_API_635 */
        /* Do nothing */
      }
    } /* End of else */
  } /* End of if (COMM_SILENT_COM == ComM_SubComMode[chIndex]) */
} /* End of ComM_SilentComMode */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_ETHNETWORK_PRESENT == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_FullComMode                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_FULL_COMMUNICATION    **
**                        mode for the corresponding Channel index            **
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
**                        ComM_SubComMode                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PNCComSigFullCom(), ComM_FullComNetwReq(),     **
**                        ComM_FullComReadySleep()                            **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00011
 */
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
FUNC(void, COMM_CODE) ComM_FullComMode(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_318 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* PNC related function to be done before channel function */
  #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
      ((COMM_CANNETWORK_PRESENT == STD_ON) || \
                                            (COMM_FRNETWORK_PRESENT == STD_ON)))
  ComM_PNCComSigFullCom(chIndex);
  #endif
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* Check config variant enabled Pnc */
  if (COMM_TRUE == ComM_PncEnabledFlashPB)
  {
    /* @Trace: ComM_SUD_API_319 */
    /* PNC related function to be done before channel function */
    ComM_PNCComSigFullCom(chIndex);
  } /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
  else
  {
    /* @Trace: ComM_SUD_API_320 */
    /* Do nothing */
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */

  /* If Sub State is Network Requested */
  if (COMM_FULL_COM_NETWORK_REQUESTED == ComM_SubComMode[chIndex])
  {
    /* @Trace: ComM_SUD_API_321 */
    ComM_FullComNetwReq(chIndex);
  }

  /* If sub state is Ready Sleep */
  if (COMM_FULL_COM_READY_SLEEP == ComM_SubComMode[chIndex])
  {
    /* @Trace: ComM_SUD_API_322 */
    ComM_FullComReadySleep(chIndex);
  }
} /* END OF FULL COMM*/
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/*******************************************************************************
** Function Name        : ComM_NoComNoPendingRequest                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to Process the channel request came **
**                        in ComM sub state COMM_NO_COM_NO_PENDING_REQUEST    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : chIndex                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : passiveWakeFlag                                     **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_DcmActiveDiagnostic, ComM_ChannelInhibition,   **
**                        ComM_LimitEcuToNoCom, ComM_ReqedComModeCnt,         **
**                        ComM_ManagingSetMode                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_NoComNoPendingReleaseNmBus,                    **
**                        ComM_CheckPassiveAndSyncWakeUp,                     **
**                        ComM_NoComNoPendingRequestSetSubMode                **
**                        BswM_ComM_InitiateReset                             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09080 SRS_ModeMgm_09087 SRS_ComM_AR_00005 SRS_ComM_AR_00039
 * SRS_ComM_AR_00071 SRS_ComM_AR_00073 SRS_ComM_AR_00074 SRS_ComM_AR_00075
 * SRS_ComM_AR_00076 SRS_ComM_AR_00091 SRS_ComM_AR_00092 SRS_ComM_AR_00093
 * SRS_ComM_AR_00111 SRS_ComM_AR_00114 SRS_ComM_AR_00117 SRS_ComM_AR_00126
 * SRS_ComM_AR_00162 SRS_ComM_AR_00262 SRS_ComM_AR_00264
 */
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
FUNC(boolean, COMM_CODE) ComM_NoComNoPendingRequest(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_474 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* Variable to Store Full Comm set or not */
  boolean fullFlag;

  /* Variable to store passive wake up */
  boolean passiveWakeFlag;

  #if (COMM_REFERENCE_CHANEL == STD_ON)
  /* Managing channel index */
  uint8 managingId;

  /* Managing channel id temp */
  uint8 managingChnlId;
  #endif

  #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /* The variable is used for PNC Index */
  PNCHandleType tmpPncIndex;
  /* The variable is used for PNC Count */
  uint16 tmpPncCount;
  /* The variable is used for Indexing*/
  PNCHandleType pncIndexMapping;
  #endif

  /* Clear Full Comm Flag */
  fullFlag = COMM_FALSE;

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  ComM_NoComNoPendingReleaseNmBus(chIndex);
  #endif

  /* Check for Active Diagnostics */
  /* Traceable SWS_ComM_00876 */
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
       (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
  if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
  {
    if ((COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant) ||\
      (COMM_NMVARIANT_LIGHT == ComM_Channels[chIndex].NmVariant) ||\
      (COMM_NMVARIANT_NONE == ComM_Channels[chIndex].NmVariant))
    {
      /* @Trace: ComM_SUD_API_477 */
      /* Set Full Comm Flag */
      fullFlag = COMM_TRUE;
    }
  }
  else
  {
    /* @Trace: ComM_SUD_API_478 */
    /* Do nothing */
  }
  SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
  #endif
  /* Check communication limitation */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /*  Check for Limit channel inhibition condition and Limit ECU to No Com */
  /* Traceable SWS_ComM_00355 */
  if ((COMM_TRUE == ComM_LimitEcuToNoCom) ||
    (COMM_LIMITCHANNELTONOCOMM_MASK_SET ==
    (ComM_ChannelInhibition[chIndex] & COMM_LIMITCHANNELTONOCOMM_MASK_SET)))
  {
    /* @Trace: ComM_SUD_API_479 */
    /* Clear wakeup flag */
    passiveWakeFlag = COMM_FALSE;
    #if (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON)
      /* Force an ECU reset */
	  /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The call to this function will have effect depending on configuration" */
      BswM_ComM_InitiateReset();
    #endif
  }
  else
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
          *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
  {
    passiveWakeFlag = ComM_CheckPassiveAndSyncWakeUp(chIndex);

    /* Traceable SWS_ComM_00875 */
    /* use case Communication limitation enable but channel isn't inhibited */
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
         (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    /* Check if communication limitation is not set */
    if (COMM_PREVENTWAKEUP_MASK_SET !=
      (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET))
    #endif
    {
      /* @Trace: ComM_SUD_API_491 */
      /* Check PNC state on entry sub state COMM_PNC_REQUESTED */
      /* Traceability SWS_ComM_00993 */
      #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
        ((COMM_CANNETWORK_PRESENT == STD_ON) || \
                                            (COMM_FRNETWORK_PRESENT == STD_ON)))
      if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc)
      {
        /* @Trace: ComM_SUD_API_492 */
        tmpPncIndex = ComM_Channels[chIndex].PncIndex;
        tmpPncCount = ComM_Channels[chIndex].PncCount;
        /*State transitions of the PNC state machines */
        while (tmpPncCount != COMM_ZERO)
        {
          /* Decrement the pnc count */
          tmpPncCount--;
          /* ComM_ChannelToPncMapping[] :The Map provides Index*/
          pncIndexMapping = ComM_ChannelToPncMapping[tmpPncIndex];
          /* Flag PNC requested when received PNC signal info */
          if (COMM_TRUE == ComM_ReqFlag[pncIndexMapping])
          {
            /* @Trace: ComM_SUD_API_493 */
            fullFlag = COMM_TRUE;
            tmpPncCount = COMM_ZERO;
            ComM_PncReqtedflag[chIndex] = COMM_TRUE;
          }
          else
          {
            /* @Trace: ComM_SUD_API_494 */
            /* Do nothing */
          }
          tmpPncIndex++;
        } /*End of PNC Counts of Channel*/
      } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
      else
      #endif /* End PNC support */
      {
        /* @Trace: ComM_SUD_API_495 */
        /* Check For Full Communication Request */
        if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
        {
          /* @Trace: ComM_SUD_API_496 */
          /* Set Full Comm Flag */
          fullFlag = COMM_TRUE;

          /* Clear wakeup flag */
          passiveWakeFlag = COMM_FALSE;
          #if (COMM_REFERENCE_CHANEL == STD_ON)
          /* Check channel is managed channel */
          if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl)
          {
            /* @Trace: ComM_SUD_API_497 */
            /* managed channel is not passive and active gateway */
            /* Traceable ECUC_ComM_00842 */
            managingChnlId = ComM_Channels[chIndex].IdOfManagingChnl;
            #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
            managingId = ComM_ChannelMapArray[managingChnlId];
            #else
            managingId = managingChnlId;
            #endif
            /* Request the managing channel to full communication */
            /* if ((COMM_TRUE == ComM_Channels[managingId].ManagingChnl) &&\ */
            if (COMM_ZERO == ComM_ReqedComModeCnt[managingId])
            {
              /* @Trace: ComM_SUD_API_498 */
              /* Set request full com to managing channel */
              ComM_ManagingSetMode[managingId] = COMM_TRUE;
            }

          } /* if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl) */
          else
          {
            /* @Trace: ComM_SUD_API_499 */
            /* Do nothing */
          }
          #endif /* End of #if (COMM_REFERENCE_CHANEL == STD_ON) */
        }
        else  /* if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex]) */
        {
          /* @Trace: ComM_SUD_API_500 */
          /* Do nothing */
        }
      }
      /* end of if (ComM_ReqedComModeCnt[chIndex] != COMM_ZERO) */
    }
    /* End of traceable SWS_ComM_00875 */
  }
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* Variable to Store Full Comm set or not */
  boolean fullFlag;
  /* Variable to store passive wake up */
  boolean passiveWakeFlag;
  #if (COMM_REFERENCE_CHANEL == STD_ON)
  /* Managing channel chIndex */
  uint8 managingId;
  /* Managing channel id temp */
  uint8 managingChnlId;
  #endif
  /* Check config variant enabled Pnc */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* The variable is used for PNC Index */
    PNCHandleType tmpPncIndex;
    /* The variable is used for PNC Count */
    uint16 tmpPncCount;
    /* The variable is used for Indexing*/
    PNCHandleType pncIndexMapping;
  // } End of if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // else
  // {
    /* Do nothing */
  // }

  /* Clear Full Comm Flag */
  fullFlag = COMM_FALSE;

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  ComM_NoComNoPendingReleaseNmBus(chIndex);
  #endif

  /* Check for Active Diagnostics */
  /* Traceable SWS_ComM_00876 */
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) || \
       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) || \
       (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  if (COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex])
  {
    if ((COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant) || \
      (COMM_NMVARIANT_LIGHT == ComM_Channels[chIndex].NmVariant) || \
      (COMM_NMVARIANT_NONE == ComM_Channels[chIndex].NmVariant))
    {
      /* @Trace: ComM_SUD_API_507 */
      /* Set Full Comm Flag */
      fullFlag = COMM_TRUE;
    }
  }
  else
  {
    /* @Trace: ComM_SUD_API_508 */
    /* Do nothing */
  }
  #endif

  /* Check communication limitation */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
                                       (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  /*  Check for Limit channel inhibition condition and Limit ECU to No Com */
  /* Traceable SWS_ComM_00355 */
  if ((COMM_TRUE == ComM_LimitEcuToNoCom) || \
    (COMM_LIMITCHANNELTONOCOMM_MASK_SET ==
          (ComM_ChannelInhibition[chIndex] & COMM_LIMITCHANNELTONOCOMM_MASK_SET)))
  {
    /* @Trace: ComM_SUD_API_509 */
    /* Clear wakeup flag */
    passiveWakeFlag = COMM_FALSE;
    #if (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON)
    /* Force an ECU reset */
	/* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The call to this function will have effect depending on configuration" */
    BswM_ComM_InitiateReset();
    #endif
  }
  else
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
          *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
  {
    passiveWakeFlag = ComM_CheckPassiveAndSyncWakeUp(chIndex);

    /* Traceable SWS_ComM_00875 */
    /* use case Communication limitation enable but channel isn't inhibited */
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
                                       (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    /* Check if communication limitation is not set */
    if (COMM_PREVENTWAKEUP_MASK_SET !=
                  (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET))
    #endif
    {
      /* @Trace: ComM_SUD_API_521 */
      /* Check PNC state on entry sub state COMM_PNC_REQUESTED */
      /* Traceability SWS_ComM_00993 */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      if (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chIndex].ChannelPnc)
      {
        /* @Trace: ComM_SUD_API_522 */
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
          pncIndexMapping = ComM_ChannelToPncMappingGlobal[tmpPncIndex];
          /* Flag PNC requested when received PNC signal info */
          /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          if (COMM_TRUE == ComM_ReqFlag[pncIndexMapping])
          {
            /* @Trace: ComM_SUD_API_523 */
            fullFlag = COMM_TRUE;
            tmpPncCount = COMM_ZERO;
            ComM_PncReqtedflag[chIndex] = COMM_TRUE;
          }
          else
          {
            /* @Trace: ComM_SUD_API_524 */
            /* Do nothing */
          }
          tmpPncIndex++;
        } /*End of PNC Counts of Channel*/
      } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
      else
      {
        /* @Trace: ComM_SUD_API_525 */
        /* Check For Full Communication Request */
        if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex])
        {
          /* @Trace: ComM_SUD_API_526 */
          /* Set Full Comm Flag */
          fullFlag = COMM_TRUE;

          /* Clear wakeup flag */
          passiveWakeFlag = COMM_FALSE;
          #if (COMM_REFERENCE_CHANEL == STD_ON)
          /* Check channel is managed channel */
          if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl)
          {
            /* @Trace: ComM_SUD_API_527 */
            /* managed channel is not passive and active gateway */
            /* Traceable ECUC_ComM_00842 */
            managingChnlId = ComM_Channels[chIndex].IdOfManagingChnl;
            #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
            managingId = ComM_ChannelMapArray[managingChnlId];
            #else
            managingId = managingChnlId;
            #endif
            /* Request the managing channel to full communication */
            /* if ((COMM_TRUE == ComM_Channels[managingId].ManagingChnl) &&\ */
            if (COMM_ZERO == ComM_ReqedComModeCnt[managingId])
            {
              /* @Trace: ComM_SUD_API_528 */
              /* Set request full com to managing channel */
              ComM_ManagingSetMode[managingId] = COMM_TRUE;
            }
          } /* if (COMM_TRUE == ComM_Channels[chIndex].ManagedChnl) */
          else
          {
            /* @Trace: ComM_SUD_API_529 */
            /* Do nothing */
          }
          #endif /* End of #if (COMM_REFERENCE_CHANEL == STD_ON) */
        }
        else  /* if (COMM_ZERO != ComM_ReqedComModeCnt[chIndex]) */
        {
          /* @Trace: ComM_SUD_API_530 */
          /* Do nothing */
        }
      }
    }
  /* End of traceable SWS_ComM_00875 */
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  /* Check for Full Communication Request during mode limitation */
  if ((COMM_PREVENTWAKEUP_MASK_SET !=
    (ComM_ChannelInhibition[chIndex] & COMM_PREVENTWAKEUP_MASK_SET)) &&
    (COMM_ZERO != ComM_InhibitionReqst[chIndex]))
  {
    /* @Trace: ComM_SUD_API_531 */
    /* Set Full Comm Flag */
    fullFlag = COMM_TRUE;
  }
  else
  {
    /* @Trace: ComM_SUD_API_532 */
    /* Do nothing */
  }
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
    *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

  /* If there is request for full communication */
  ComM_NoComNoPendingRequestSetSubMode(chIndex, fullFlag, passiveWakeFlag);
  /* Return checked in Next sub state: COMM_NO_COM_NO_PENDING_REQUEST*/
  return (passiveWakeFlag);
} /* End of ComM_NoComNoPendingRequest */
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/*******************************************************************************
** Function Name        : ComM_NoComRequestPending                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to Process the channel request came **
**                        in ComM sub state COMM_NO_COM_NO_REQUEST_PENDING    **
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
**                        ComM_Channels, ComM_SubComMode,                     **
**                        ComM_ReqedComModeCnt,ComM_DcmActiveDiagnostic       **
**                        ComM_DcmInactiveDiagnostic                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_FullComModePassiveWakeUp                       **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00039 SRS_ComM_AR_00077 SRS_ComM_AR_00078 SRS_ComM_AR_00089
 * SRS_ComM_AR_00090 SRS_ComM_AR_00091 SRS_ComM_AR_00092 SRS_ComM_AR_00093
 * SRS_ComM_AR_00084 SRS_ComM_AR_00111 SRS_ComM_AR_00114 SRS_ComM_AR_00124
 * SRS_ComM_AR_00126 SRS_ComM_AR_00162 SRS_ComM_AR_00156
*/
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
FUNC(void, COMM_CODE) ComM_NoComRequestPending(uint8 chIndex, boolean
  passiveWakeFlag)
{
  /* @Trace: ComM_SUD_API_704*/
  #if (COMM_REFERENCE_CHANEL == STD_ON)
  /* number of managed channel */
  uint8 managedChnlCnt;
  /* Index of managed channel */
  uint8 managedInx;
  /* id of managed channel in mapping array */
  uint8 tmpManagedId;

  /* index for this managing channel in mapping array */
  uint8 managingInx;
  #endif

  boolean flagNoCom;
  #if((COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) || (COMM_INTERNALBUS_PRESENT == STD_ON))
  ComM_FullComModePassiveWakeUp(chIndex, passiveWakeFlag);
  #endif
  /* If there is no user request for Full communication */
  /* Traceable SWS_ComM_00897 SWS_ComM_00993 */
  if ((COMM_ZERO == ComM_ReqedComModeCnt[chIndex]) &&
     (COMM_FALSE == ComM_PncReqtedflag[chIndex]))
  {
    /* @Trace: ComM_SUD_API_709*/
    /* Clear flag change to COMM_NO_COM_NO_PENDING_REQUEST */
    flagNoCom = COMM_FALSE;
    if (COMM_FALSE == passiveWakeFlag)
    {
      /* @Trace: ComM_SUD_API_710*/
      /* If Dcm had indicated inactive diagnostic */
      SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
      if ((COMM_TRUE == ComM_DcmActiveDiagnostic[chIndex]) &&\
          (COMM_TRUE == ComM_DcmInactiveDiagnostic[chIndex]))
      {
        /* @Trace: ComM_SUD_API_711*/
        /* Set flag change to COMM_NO_COM_NO_PENDING_REQUEST */
        flagNoCom = COMM_TRUE;
      }
      else if (COMM_FALSE == ComM_DcmActiveDiagnostic[chIndex])
      {
        /* @Trace: ComM_SUD_API_712*/
        /* Set flag change to COMM_NO_COM_NO_PENDING_REQUEST */
        flagNoCom = COMM_TRUE;
      }
      else
      {
        /* @Trace: ComM_SUD_API_713*/
        /* Do nothing */
      }
      SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
    } /* End of if (COMM_FALSE == passiveWakeFlag) */
    else
    {
      /* @Trace: ComM_SUD_API_714*/
      /* Do nothing */
    }

    if (COMM_TRUE == flagNoCom)
    {
      /* @Trace: ComM_SUD_API_715*/
      /* Check channel is managing */
      #if (COMM_REFERENCE_CHANEL == STD_ON)
      if (COMM_TRUE == ComM_Channels[chIndex].ManagingChnl)
      {
        /* @Trace: ComM_SUD_API_716*/
        /* get number of managed channel */
        managedChnlCnt = ComM_Channels[chIndex].NoOfManagedChnl;
        /* get the index of list managed */
        managingInx = ComM_Channels[chIndex].ManagingIndex;
        while(managedChnlCnt != COMM_ZERO)
        {
          /* get managed channel id */
          tmpManagedId = ComM_ManagingMapArray[managingInx];
          #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
          managedInx = ComM_ChannelMapArray[tmpManagedId];
          #else
          managedInx = tmpManagedId;
          #endif
          /* Check channel reference to any pnc */
          #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
          /* ================== Implement for Pre-Compile =================== */
          if ((COMM_ZERO != ComM_ReqedComModeCnt[managedInx])
          #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
          || (COMM_TRUE == ComM_Channels[managedInx].ChannelPnc)
          #endif
          )
          #else
          /* ================== Implement for Post-Build ==================== */
          /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          if ((COMM_ZERO != ComM_ReqedComModeCnt[managedInx]) || \
            (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[managedInx].ChannelPnc))
          #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
          {
            /* @Trace: ComM_SUD_API_717*/
            managedChnlCnt = COMM_ZERO;
            flagNoCom = COMM_FALSE;
          }
          else
          {
            /* @Trace: ComM_SUD_API_718*/
            managedChnlCnt--;
            managingInx++;
          }
        } /* End of  while(managedChnlCnt != COMM_ZERO) */
        if (COMM_TRUE == flagNoCom)
        {
          /* @Trace: ComM_SUD_API_719*/
          /* Change to sub state to COMM_NO_COM_NO_PENDING_REQUEST */
          ComM_SubComMode[chIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
        }
        else
        {
          /* @Trace: ComM_SUD_API_720*/
          /* Do nothing */
        }
      }/* if (COMM_TRUE == ComM_Channels[chIndex].ManagingChnl) */
      /* Channel is not a managing channel */
      else
      {
        /* @Trace: ComM_SUD_API_721*/
        /* Change to sub state to COMM_NO_COM_NO_PENDING_REQUEST */
        ComM_SubComMode[chIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
      }
      #else /*  #if (COMM_REFERENCE_CHANEL == STD_ON) */

      /* Change to sub state to COMM_NO_COM_NO_PENDING_REQUEST */
      ComM_SubComMode[chIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
      #endif /* End of #if (COMM_REFERENCE_CHANEL == STD_ON) */
    } /* End of if (COMM_TRUE == flagNoCom) */
    else
    {
      /* @Trace: ComM_SUD_API_722*/
      /* Do nothing */
    }
  } /* End of if (ComM_ReqedComModeCnt[chIndex] == COMM_ZERO) */
  /* End of Traceable SWS_ComM_00897 */
} /* End of ComM_NoComRequestPending */
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/*******************************************************************************
** Function Name        : ComM_PNCFullMode                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve for PNC_FULL_COMMUNICATION **
**                        state.                                              **
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
**                        ComM_SubPNCMode                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PNCFullModeRequested()                         **
**                        ComM_PNCFullModeReadySleep()                        **
**                        ComM_PNCFullModePrepareSleep()                      **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00168  */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PNCFullMode(PNCHandleType tmpPncIndex)
{
  /* PNC Sub State (1): COMM_PNC_REQUESTED */
  if (COMM_PNC_REQUESTED == ComM_SubPNCMode[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_538 */
    ComM_PNCFullModeRequested(tmpPncIndex);
  }
  /* PNC Sub State (2): COMM_PNC_READY_SLEEP */
  else if (COMM_PNC_READY_SLEEP == ComM_SubPNCMode[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_539 */
    ComM_PNCFullModeReadySleep(tmpPncIndex);
  }
  /* PNC Sub State (3): COMM_PNC_PREPARE_SLEEP */
  else
  {
    /* @Trace: ComM_SUD_API_540 */
    ComM_PNCFullModePrepareSleep(tmpPncIndex);
  }
} /* End of ComM_PNCFullMode */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PNCNoMode                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve for                        **
**                        COMM_PNC_NO_COMMUNICATION                           **
**                        state.                                              **
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
** Remarks              : Global Variable(s):                                 **
**                        ComM_RequestedPNCMode, ComM_PncRxERAn,              **
**                        ComM_SubPNCMode, ComM_Pncs, ComM_ReqFlag,           **
**                        ComM_PncRxEIRA, ComM_PNCWakeupIndication            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00001 SRS_ComM_AR_00010 SRS_ComM_AR_00049 SRS_ComM_AR_00016
 * SRS_ComM_AR_00022 SRS_ComM_AR_00034 SRS_ComM_AR_00035 SRS_ComM_AR_00036
 * SRS_ComM_AR_00037
*/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PNCNoMode(PNCHandleType tmpPncIndex)
{
  /* @Trace: ComM_SUD_API_611 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* variables for loop all channel mapping to PNC */
  uint8 loopChannel;
  /* Index of channel mapping to this PNC in mapping array*/
  uint8 chnlPncIndex;
  /* Number of channel mapping to this PNC */
  uint8 numOfChnl;
  /* Channel ID*/
  NetworkHandleType channel;
  /* Variable to store channel */
  NetworkHandleType channelIndex;
  /* User Request or  ERAn Changes*/
  /* Traceable SWS_ComM_00932, SWS_ComM_00934 */
  SchM_Enter_ComM_PNC_WAKEUP_IND();
  if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex])
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    || (COMM_TRUE == ComM_PncRxERAn[tmpPncIndex])
    #endif
    )
  {
    SchM_Exit_ComM_PNC_WAKEUP_IND();
    /* @Trace: ComM_SUD_API_612 */
    /*PNC Sub State changed to : COMM_PNC_REQUESTED*/
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_REQUESTED;
    /*Indication to BswM Module*/
    /* Traceable SWS_ComM_00908 */
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId, COMM_PNC_REQUESTED);
    /* Set the Request flag*/
    ComM_ReqFlag[tmpPncIndex] = COMM_TRUE;
  } /* End of if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex]) */
  /* Synchronouse wake up is coverd in API ComM_EcuM_WakeUpIndication */
  /* Traceable SWS_ComM_00931, SWS_ComM_00964, SWS_ComM_01014, SWS_ComM_01015 */
  else if (COMM_TRUE == ComM_PNCWakeupIndication[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_613 */
    /* Clear request PNC wakeup */
    ComM_PNCWakeupIndication[tmpPncIndex] = COMM_FALSE;
    SchM_Exit_ComM_PNC_WAKEUP_IND();
    /* get number of channel mapping to PNC */
    numOfChnl = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;
    /* Get the index of channel mapping to PNC */
    chnlPncIndex = ComM_Pncs[tmpPncIndex].ChannelPncIndex;

    for(loopChannel = 0; loopChannel < numOfChnl; loopChannel++)
    {
      /* get channel id mapping to this PNC */
      channel = ComM_ChnPncInxArr[chnlPncIndex];

      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* Get the channel id from the mapping array */
      channelIndex = ComM_ChannelMapArray[channel];
      #else
      /* Channel Id is updated into local variable */
      channelIndex = channel;
      #endif
      /* Traceable SWS_ComM_00952 */
      /* Start the PNC Timer for the channel*/
      SchM_Enter_ComM_PNC_PREPARE_TIMER();
      ComM_PncTimeCnt[tmpPncIndex] =
      ComM_Channels[channelIndex].PncPrepareSleepTimer;
      SchM_Exit_ComM_PNC_PREPARE_TIMER();
      chnlPncIndex++;
    }

    /* PNC Sub State changed to : COMM_PNC_PREPARE_SLEEP */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_PREPARE_SLEEP;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
      COMM_PNC_PREPARE_SLEEP);
  } /* End of if (COMM_TRUE == ComM_PNCWakeupIndication[tmpPncIndex]) */
  /*  #endif End of if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */

  /* Conditions: No Local Request */
  /* Traceable SWS_ComM_00933 */
  else if (COMM_TRUE == ComM_PncRxEIRA[tmpPncIndex])
  {
    SchM_Exit_ComM_PNC_WAKEUP_IND();
    /* @Trace: ComM_SUD_API_614 */
    /*PNC Sub State changed to : COMM_PNC_READY_SLEEP*/
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_READY_SLEEP;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_Pncs[tmpPncIndex].PncId,
      COMM_PNC_READY_SLEEP);
  }
  else
  {
    SchM_Exit_ComM_PNC_WAKEUP_IND();
    /* @Trace: ComM_SUD_API_615 */
    /* No State Change */
  }
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* variables for loop all channel mapping to PNC */
  uint8 loopChannel;
  /* Index of channel mapping to this PNC in mapping array*/
  uint8 chnlPncIndex;
  /* Number of channel mapping to this PNC */
  uint8 numOfChnl;
  /* Channel ID*/
  NetworkHandleType channel;
  /* Variable to store channel */
  NetworkHandleType channelIndex;
  /* User Request or  ERAn Changes*/
  /* Traceable SWS_ComM_00932, SWS_ComM_00934 */
  if ((PNC_USER_FULL_COMM == ComM_RequestedPNCMode[tmpPncIndex])
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    || (COMM_TRUE == ComM_PncRxERAn[tmpPncIndex])
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_617 */
    /*PNC Sub State changed to : COMM_PNC_REQUESTED*/
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_REQUESTED;
    /*Indication to BswM Module*/
    /* Traceable SWS_ComM_00908 */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                          COMM_PNC_REQUESTED);
    /* Set the Request flag*/
    ComM_ReqFlag[tmpPncIndex] = COMM_TRUE;
  }
  /* Synchronouse wake up is coverd in API ComM_EcuM_WakeUpIndication */
  /* Traceable SWS_ComM_00931, SWS_ComM_00964,
                                              SWS_ComM_01014, SWS_ComM_01015 */
  else if (COMM_TRUE == ComM_PNCWakeupIndication[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_618 */
    /* Clear request PNC wakeup */
    ComM_PNCWakeupIndication[tmpPncIndex] = COMM_FALSE;
    /* get number of channel mapping to PNC */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    numOfChnl = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
    /* Get the index of channel mapping to PNC */
    chnlPncIndex = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;

    for(loopChannel = 0; loopChannel < numOfChnl; loopChannel++)
    {
      /* get channel id mapping to this PNC */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      channel = ComM_ChnPncInxArrGlobal[chnlPncIndex];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* Get the channel id from the mapping array */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      channelIndex = ComM_ChannelMapArray[channel];
      #else
      /* Channel Id is updated into local variable */
      channelIndex = channel;
      #endif
      /* Traceable SWS_ComM_00952 */
      /* Start the PNC Timer for the channel*/
      SchM_Enter_ComM_PNC_PREPARE_TIMER();
      /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      ComM_PncTimeCnt[tmpPncIndex] =
      ComM_Channels[channelIndex].PncPrepareSleepTimer;
      SchM_Exit_ComM_PNC_PREPARE_TIMER();
      chnlPncIndex++;
    }
    /* PNC Sub State changed to : COMM_PNC_PREPARE_SLEEP */
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_PREPARE_SLEEP;
    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                      COMM_PNC_PREPARE_SLEEP);
  } /* End of if (COMM_TRUE == ComM_PNCWakeupIndication[tmpPncIndex]) */
  /*  #endif End of if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */

  /* Conditions: No Local Request */
  /* Traceable SWS_ComM_00933 */
  else if (COMM_TRUE == ComM_PncRxEIRA[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_619 */
    /*PNC Sub State changed to : COMM_PNC_READY_SLEEP*/
    ComM_SubPNCMode[tmpPncIndex] = COMM_PNC_READY_SLEEP;
    /*Indication to BswM Module*/
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    BswM_ComM_CurrentPNCMode(ComM_PncsGlobal[tmpPncIndex].PncId,
                                                        COMM_PNC_READY_SLEEP);
  }
  else
  {
    /* @Trace: ComM_SUD_API_620 */
    /* No State Change */
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCNoMode */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PNCComSigFullCom                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve PNC entry activities in    **
**                        COMM_FULL_COMMUNICATION for the corresponding       **
**                        Channel index                                       **
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
**                        ComM_ChannelToPncMapping, ComM_Channels,            **
**                        ComM_SubPNCMode, ComM_ReqToReadyFlag,               **
**                        ComM_SignalTx, ComM_ComSignal, ComM_Pncs            **
**                        ComM_PncTimeCnt, ComM_SignalTxMapArray              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PNCNetwReq(), Com_SendSignal()                 **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00002 SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00040
 * SRS_ComM_AR_00041 SRS_ComM_AR_00043 SRS_ComM_AR_00046
*/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PNCComSigFullCom(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_644 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  /* The variable is used for PNC Index */
  PNCHandleType handlePncIndex;

  /* The variable is used for PNC Count */
  uint16 tmpPncCount;

  /* The variable is used for PNC Indexing */
  PNCHandleType pncInx;

  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* The variable is used for PNC ID */
  PNCHandleType tmpPncId;

  /* The variable is used for storing Byte Index */
  uint8 byteIndex;

  /* The variable is used for storing Bit Index */
  uint8 bitIndex;

  /* The variable is used to store Mask Value */
  uint8 mask;

  /* The variable is used to store Mask Value to clear bit */
  uint8 maskClear;

  /* The variable is used for Signal Indexing */
  uint16 signalIndex;

  /* The variable is used for Signal counting */
  uint16 signalCount;

  /* The variable is used to store signal ID */
  uint16 signalHandleId;

  /* Signal Tx index */
  uint16 signalTxIndex;
  #endif

  if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc)
  {
    /* @Trace: ComM_SUD_API_645 */
    handlePncIndex = ComM_Channels[chIndex].PncIndex;
    tmpPncCount = ComM_Channels[chIndex].PncCount;
    /*State transitions of the PNC state machines */
    while (tmpPncCount != COMM_ZERO)
    {
      /* Decrement the pnc count */
      tmpPncCount--;

      /* ComM_ChannelToPncMapping[] :The Map provides Index*/
      pncInx = ComM_ChannelToPncMapping[handlePncIndex];

      if (COMM_PNC_NO_COMMUNICATION != ComM_SubPNCMode[pncInx])
      {
        /* @Trace: ComM_SUD_API_646 */
        /* On entry of PNC sub state COMM_PNC_REQUESTED */
        if (COMM_PNC_REQUESTED == ComM_SubPNCMode[pncInx])
        {
          /* @Trace: ComM_SUD_API_647 */
          ComM_PNCNetwReq(pncInx, chIndex);
        }
        /* On entry PNC sub state COMM_PNC_READY_SLEEP */
        else if (COMM_PNC_READY_SLEEP == ComM_SubPNCMode[pncInx])
        {
          /* @Trace: ComM_SUD_API_648 */
          if (COMM_TRUE == ComM_ReqToReadyFlag[pncInx])
          {
            /* @Trace: ComM_SUD_API_649 */
            /* Reset the flag */
            ComM_ReqToReadyFlag[pncInx] = COMM_FALSE;
            #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) 
            /*Calculating the PNC ID for the Pnc Index*/
            tmpPncId = ComM_Pncs[pncInx].PncId;
            /* Signal Instance Index associated with the PNC */
            signalIndex = ComM_Pncs[pncInx].ComSignalIndex;

            /* Signal Count of the PNC */
            signalCount = ComM_Pncs[pncInx].NoOfComSignal;
            while (signalCount != COMM_ZERO)
            {
              if (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir)
              {
                /* @Trace: ComM_SUD_API_650 */
                /*Calculation Of Byte Index*/
                /* Traceable SWS_ComM_00825 */
                byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
                  ComM_ComSignal[signalIndex].ComMPncVectorOffset;

                /*Calculation Of Bit Index within the Byte */
                bitIndex = (uint8)(tmpPncId % COMM_EIGHT);

                /*Calculating the Mask Value for the bit Index*/
                mask = (uint8)(COMM_ONE << bitIndex);

                maskClear = (~mask);

                /*Get Signal Tx Index from Signal Index*/
                signalTxIndex = ComM_SignalTxMapArray[signalIndex];

                /* Clear signal Tx */
                ComM_SignalTx[signalTxIndex][byteIndex] =
                  (ComM_SignalTx[signalTxIndex][byteIndex] & maskClear);
                /* Get signal Id */
                signalHandleId =
                  ComM_ComSignal[signalIndex].ComMComSigId;
                /* Send signal to Com module */
                (void)Com_SendSignal(signalHandleId,
                  (const void*)ComM_SignalTx[signalTxIndex]);
              }
              else
              {
                /* @Trace: ComM_SUD_API_651 */
                /* Do nothing */
              }
              signalIndex++;
              signalCount--;
            } /* End of while */
            #endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
          } /* End of if (ComM_ReqToReadyFlag[pncInx] == COMM_TRUE) */
        } /* End of if (ComM_SubPNCMode[pncInx] == COMM_PNC_READY_SLEEP) */
          /* On entry of PNC sub state COMM_PNC_PREPARE_SLEEP */
        else
        {
          /* @Trace: ComM_SUD_API_652 */
          if (COMM_ZERO != ComM_PncTimeCnt[pncInx])
          {
            /* @Trace: ComM_SUD_API_653 */
            /* Decrement the PNC timer for the Channel */
            ComM_PncTimeCnt[pncInx]--;
          }
        }
      } /* if (ComM_SubPNCMode[pncInx] != COMM_PNC_NO_COMMUNICATION) */
      /* increase Pnc index */
      handlePncIndex++;
    } /*End of PNC Counts of Channel*/
  } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* The variable is used for PNC Index */
  PNCHandleType handlePncIndex;
  /* The variable is used for PNC Count */
  uint16 tmpPncCount;
  /* The variable is used for PNC Indexing */
  PNCHandleType pncInx;
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* The variable is used for PNC ID */
  PNCHandleType tmpPncId;
  /* The variable is used for storing Byte Index */
  uint8 byteIndex;
  /* The variable is used for storing Bit Index */
  uint8 bitIndex;
  /* The variable is used to store Mask Value */
  uint8 mask;
  /* The variable is used to store Mask Value to clear bit */
  uint8 maskClear;
  /* The variable is used for Signal Indexing */
  uint16 signalIndex;
  /* The variable is used for Signal counting */
  uint16 signalCount;
  /* The variable is used to store signal ID */
  uint16 signalHandleId;
  /* Signal Tx index */
  uint16 signalTxIndex;
  #endif

  /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  if (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chIndex].ChannelPnc)
  {
    /* @Trace: ComM_SUD_API_655 */
    handlePncIndex = ComM_ChannelsPNCRelatedGlobal[chIndex].PncIndex;
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
      pncInx = ComM_ChannelToPncMappingGlobal[handlePncIndex];

      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      if (COMM_PNC_NO_COMMUNICATION != ComM_SubPNCMode[pncInx])
      {
        /* @Trace: ComM_SUD_API_656 */
        /* On entry of PNC sub state COMM_PNC_REQUESTED */
        if (COMM_PNC_REQUESTED == ComM_SubPNCMode[pncInx])
        {
          /* @Trace: ComM_SUD_API_657 */
          ComM_PNCNetwReq(pncInx, chIndex);
        }
        /* On entry PNC sub state COMM_PNC_READY_SLEEP */
        else if (COMM_PNC_READY_SLEEP == ComM_SubPNCMode[pncInx])
        {
          /* @Trace: ComM_SUD_API_658 */
          if (COMM_TRUE == ComM_ReqToReadyFlag[pncInx])
          {
            /* @Trace: ComM_SUD_API_659 */
            /* Reset the flag */
            ComM_ReqToReadyFlag[pncInx] = COMM_FALSE;
            #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
            /*Calculating the PNC ID for the Pnc Index*/
            /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
            tmpPncId = ComM_PncsGlobal[pncInx].PncId;
            /* Signal Instance Index associated with the PNC */
            signalIndex = ComM_PncsGlobal[pncInx].ComSignalIndex;
            /* Signal Count of the PNC */
            signalCount = ComM_PncsGlobal[pncInx].NoOfComSignal;
            while (signalCount != COMM_ZERO)
            {
              /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
              /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
              /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
              if (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir)
              {
                /* @Trace: ComM_SUD_API_660 */
                /*Calculation Of Byte Index*/
                /* Traceable SWS_ComM_00825 */
                byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
                              ComM_ComSignal[signalIndex].ComMPncVectorOffset;
                /*Calculation Of Bit Index within the Byte */
                bitIndex = (uint8)(tmpPncId % COMM_EIGHT);
                /*Calculating the Mask Value for the bit Index*/
                mask = (uint8)(COMM_ONE << bitIndex);
                maskClear = (~mask);              
                /*Get Signal Tx Index from Signal Index*/
                signalTxIndex = ComM_SignalTxMapArray[signalIndex];
                /* Clear signal Tx */
                /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
                /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
                /* polyspace +2 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
                ComM_SignalTx[signalTxIndex][byteIndex] =
                                        (ComM_SignalTx[signalTxIndex][byteIndex] & maskClear);
                /* Get signal Id */
                signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;
                /* Send signal to Com module */
                (void)Com_SendSignal(signalHandleId,
                                                  (const void*)ComM_SignalTx[signalTxIndex]);
              }
              else
              {
                /* @Trace: ComM_SUD_API_661 */
                /* Do nothing */
              }
              signalIndex++;
              signalCount--;
            } /* End of while */
            #endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
          } /* End of if (ComM_ReqToReadyFlag[pncInx] == COMM_TRUE) */
        } /* End of if (ComM_SubPNCMode[pncInx] == COMM_PNC_READY_SLEEP) */
          /* On entry of PNC sub state COMM_PNC_PREPARE_SLEEP */
        else
        {
          /* @Trace: ComM_SUD_API_662 */
          if (COMM_ZERO != ComM_PncTimeCnt[pncInx])
          {
            /* @Trace: ComM_SUD_API_663 */
            /* Decrement the PNC timer for the Channel */
            ComM_PncTimeCnt[pncInx]--;
          }
        }
      } /* if (ComM_SubPNCMode[pncInx] != COMM_PNC_NO_COMMUNICATION) */
      /* increase Pnc index */
      handlePncIndex++;
    } /*End of PNC Counts of Channel*/
  } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCComSigFullCom */
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PNCNetwReq                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve PNC entry activities in    **
**                        PNC_FULL_COMMUNICATION sub state COMM_PNC_REQUESTED **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : tmpPncIndex, byteIndex, mask, chIndex               **
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
**                        ComM_ReqFlag, ComM_Channels, ComM_SignalTx,         **
**                        ComM_Pncs, ComM_ComSignal,                          **
**                        ComM_RequestedPNCMode, ComM_ChannelMapArray         **
**                        ComM_PncRxERASignal, ComM_SignalTxMapArray          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Com_SendSignal(), Nm_NetworkRequest()               **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09243 SRS_ModeMgm_00049 SRS_ComM_AR_00002 SRS_ComM_AR_00010
 * SRS_ComM_AR_00016 SRS_ComM_AR_00040 SRS_ComM_AR_00041 SRS_ComM_AR_00042
 * SRS_ComM_AR_00062 SRS_ComM_AR_00124 SRS_ComM_AR_00125 SRS_ComM_AR_00162
 * SRS_ComM_AR_00156
*/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
FUNC(void, COMM_CODE) ComM_PNCNetwReq(PNCHandleType tmpPncIndex, uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_586 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  COMM_UNUSED(chIndex);
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* Variable to store Byte Index of PNC */
  uint8 byteIndex;

  /* Variable to store Bit Index of PNC */
  uint8 bitIndex;

  /*Variable to store Mask Value for the bit Index*/
  uint8 mask;

  /* The variable is used for Signal Indexing */
  uint16 signalIndex;

  /* The variable is used for Signal counting */
  uint16 signalCount;

  /* The variable is used to store signal ID */
  uint16 signalHandleId;

  /* The variable is used for PNC ID */
  PNCHandleType tmpPncId;

  /* Signal Tx chIndex */
  uint16 signalTxIndex;
  #endif

  #if (COMM_PNC_GW_ENABLED == STD_ON)
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* variable to store the handle channel id index */
  NetworkHandleType handleChnlIndex;

  /* The variable to store the channel ID*/
  NetworkHandleType handleCHId;
  #endif

  /* variable to store the count of channels */
  uint8 noOfChannelsInPNC;

  /* variable to store the start index of channel from pnc */
  NetworkHandleType handleChnlIndexInPNC;
  #if (((COMM_TOTAL_TX_SIGNALS != COMM_ZERO) &&\
    ((COMM_ACTIVE_GATEWAY_PRESENT == STD_ON) ||\
    (COMM_PASSIVE_GATEWAY_PRESENT == STD_ON))) ||\
    ((COMM_PNC_NM_REQUEST_SUPPORT == STD_ON) &&\
    (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)))
  /* variable to store the handle channel id */
  NetworkHandleType handleChnlId;

  /* variable to store the handle channel id temple*/
  NetworkHandleType handleChnlIdTmp;
  #endif

  #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

  /* Reset flag full com received PNC signal info */
  ComM_PncReqtedflag[chIndex] = COMM_FALSE;

  /* On entry of PNC sub state  Com_SendSignal()
   * and ComM_PncNetworkRequest()*/
  if (COMM_TRUE == ComM_ReqFlag[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_587 */
    /* Reset the flag */
    ComM_ReqFlag[tmpPncIndex] = COMM_FALSE;
    #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
    /* Get Pnc id */
    tmpPncId = ComM_Pncs[tmpPncIndex].PncId;
    #endif
    #if (COMM_PNC_GW_ENABLED == STD_ON)

    /* Get the Channels associated with the PNC*/
    noOfChannelsInPNC = ComM_Pncs[tmpPncIndex].NoOfChannelPnc;

    /*Channel Index */
    handleChnlIndexInPNC = ComM_Pncs[tmpPncIndex].ChannelPncIndex;
    while (noOfChannelsInPNC != COMM_ZERO)
    {
      #if (((COMM_TOTAL_TX_SIGNALS != COMM_ZERO) &&\
        ((COMM_ACTIVE_GATEWAY_PRESENT == STD_ON) ||\
        (COMM_PASSIVE_GATEWAY_PRESENT == STD_ON))) ||\
        ((COMM_PNC_NM_REQUEST_SUPPORT == STD_ON) &&\
        (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)))
      /* Get the Channel ID from PNC Index Array */
      handleChnlIdTmp = ComM_ChnPncInxArr[handleChnlIndexInPNC];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      handleChnlId = ComM_ChannelMapArray[handleChnlIdTmp];
      #else
      handleChnlId = handleChnlIdTmp;
      #endif
      #endif
      #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
      /* Traceable SWS_ComM_00992 */
      /* The channel is ACTIVE */
      #if (COMM_PASSIVE_GATEWAY_PRESENT == STD_ON)
      if (COMM_ACTIVE_GW == ComM_Channels[handleChnlId].PncGatewayType)
      #endif
      {
        /* @Trace: ComM_SUD_API_588 */
        /* Signal Instance Index associated with the PNC */
        signalIndex = ComM_Pncs[tmpPncIndex].ComSignalIndex;

        /* Signal Count of the PNC */
        signalCount = ComM_Pncs[tmpPncIndex].NoOfComSignal;
        while (signalCount != COMM_ZERO)
        {
          /* Get the Channel Id from Com Signal*/
          handleCHId = ComM_ComSignal[signalIndex].ComMChannelId;
          #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
          handleChnlIndex = ComM_ChannelMapArray[handleCHId];
          #else
          handleChnlIndex = handleCHId;
          #endif

          if ((handleChnlId == handleChnlIndex) &&
            (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir))
          {
            /* @Trace: ComM_SUD_API_589 */
            /*Calculation Of Byte Index*/
            /* Traceable SWS_ComM_00825 */
            byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
              ComM_ComSignal[signalIndex].ComMPncVectorOffset;

            /*Calculation Of Bit Index within the Byte */
            bitIndex = (uint8)(tmpPncId % COMM_EIGHT);

            /*Calculating the Mask Value for the bit Index*/
            mask = (uint8)(COMM_ONE << bitIndex);

            /*Get Signal Tx Index from Signal Index*/
            signalTxIndex = ComM_SignalTxMapArray[signalIndex];

            /* Set Tx signal to 1 */
            ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] | mask);
            /* Get the signal ID */
            signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;
            /* Invoke ComSendSignal of Com */
            (void)Com_SendSignal(signalHandleId, (const void*)ComM_SignalTx[signalTxIndex]);
          } /* End of if ((handleChnlId == handleChnlIndex) && */
          signalIndex++;
          signalCount--;
        } /* End of while */
      } /* End of if (COMM_ACTIVE_GW ==
                                 ComM_Channels[handleChnlId].PncGatewayType) */
      /* Traceable SWS_ComM_00164, SWS_ComM_00959 */
      /* The channel is PASSIVE */
      #if (COMM_PASSIVE_GATEWAY_PRESENT == STD_ON)
      else if (COMM_PASSIVE_GW == ComM_Channels[handleChnlId].PncGatewayType)
      {
        /* @Trace: ComM_SUD_API_590 */
        ComM_PNCNetwReq_PassiveGW(tmpPncIndex, handleChnlId);
      }
      else
      {
        /* @Trace: ComM_SUD_API_591 */
        /* To Avoid MISRA-C */
      }
      #endif /* #if (COMM_PASSIVE_GATEWAY_PRESENT == STD_ON) */
      #endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
      /* Decrement the Number of channels */
      noOfChannelsInPNC--;

      /* Increment the channel Index */
      handleChnlIndexInPNC++;

      #if ((COMM_PNC_NM_REQUEST_SUPPORT == STD_ON) &&\
        (COMM_FULL_NMVARIANT_SUPPORT == STD_ON))
      /* Network request for the channel under PNC, Provided FULL NM variant*/
      if ((COMM_TRUE == ComM_Channels[handleChnlId].PncNmRequest) &&
        (COMM_NMVARIANT_FULL == ComM_Channels[handleChnlId].NmVariant))
      {
        /* @Trace: ComM_SUD_API_592 */
        ComM_SwitchComMMode(handleChnlId, COMM_FULL_COMMUNICATION);

        /* Change sub state to Network Requested */
        ComM_SubComMode[handleChnlId] = COMM_FULL_COM_NETWORK_REQUESTED;

        /* Start the Min amount of duration in full Communication counter */
        ComM_TimeCnt[handleChnlId] = ComM_Channels[handleChnlId].MinFullComMode;

        (void)Nm_NetworkRequest(ComM_Channels[handleChnlId].ChannelId);
      }
      else
      {
        /* @Trace: ComM_SUD_API_593 */
        /* Do nothing */
      }
      #endif
    } /* End of while (noOfChannelsInPNC != COMM_ZERO) */
    #else /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */
    #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
    /* Signal Instance Index associated with the PNC */
    signalIndex = ComM_Pncs[tmpPncIndex].ComSignalIndex;

    /* Signal Count of the PNC */
    signalCount = ComM_Pncs[tmpPncIndex].NoOfComSignal;
    while (signalCount != COMM_ZERO)
    {
      if (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir)
      {
        /* @Trace: ComM_SUD_API_594 */
        /*Calculation Of Byte Index*/
        /* Traceable SWS_ComM_00825 */
        byteIndex = (tmpPncId/COMM_EIGHT) -
          ComM_ComSignal[signalIndex].ComMPncVectorOffset;

        /*Calculation Of Bit Index within the Byte */
        bitIndex = (tmpPncId % COMM_EIGHT);

        /*Calculating the Mask Value for the bit Index*/
        mask = (uint8)(COMM_ONE << bitIndex);

        /*Get Signal Tx Index from Signal Index*/
        signalTxIndex = ComM_SignalTxMapArray[signalIndex];

        /* Set signal Tx to 1 */
        ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] | mask);

        /* Get the signal ID */
        signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;

        /* Invoke ComSendSignal of Com */
        (void)Com_SendSignal(signalHandleId, (const void*)ComM_SignalTx[signalTxIndex]);
      } /* End of if(COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir) */
      else
      {
        /* @Trace: ComM_SUD_API_595 */
        /* Do nothing */
      }
      signalIndex++;
      signalCount--;
    } /* End of while (signalCount != COMM_ZERO) */
    #endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
    /* Network request for the channel under PNC, Provided FULL NM variant*/
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    if ((COMM_TRUE == ComM_Channels[chIndex].PncNmRequest) &&
      (COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant))
    {
      /* @Trace: ComM_SUD_API_596 */
      /* Invoke Network Request from PNC Entry*/
      (void)Nm_NetworkRequest(ComM_Channels[chIndex].ChannelId);
    }
    else
    {
      /* @Trace: ComM_SUD_API_597 */
      /* Do nothing */
    }
    #endif /* End of if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */
    #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */
  } /* End of if (COMM_TRUE == ComM_ReqFlag[tmpPncIndex]) */
  #else
  /* ========================== Implement for Post-Build ==================== */
  COMM_UNUSED(chIndex);
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* Variable to store Byte Index of PNC */
  uint8 byteIndex;
  /* Variable to store Bit Index of PNC */
  uint8 bitIndex;
  /*Variable to store Mask Value for the bit Index*/
  uint8 mask;
  /* The variable is used for Signal Indexing */
  uint16 signalIndex;
  /* The variable is used for Signal counting */
  uint16 signalCount;
  /* The variable is used to store signal ID */
  uint16 signalHandleId;
  /* The variable is used for PNC ID */
  PNCHandleType tmpPncId;
  /* Signal Tx index */
  uint16 signalTxIndex;
  #endif

  #if (COMM_PNC_GW_ENABLED == STD_ON)
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* variable to store the handle channel id chIndex */
  NetworkHandleType handleChnlIndex;
  /* The variable to store the channel ID*/
  NetworkHandleType handleCHId;
  #endif
  /* variable to store the count of channels */
  uint8 noOfChannelsInPNC;
  /* variable to store the start index of channel from pnc */
  NetworkHandleType handleChnlIndexInPNC;
  /* variable to store the handle channel id */
  NetworkHandleType handleChnlId;
  /* variable to store the handle channel id temple*/
  NetworkHandleType handleChnlIdTmp;
  #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* Get Pnc id */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  tmpPncId = ComM_PncsGlobal[tmpPncIndex].PncId;
  #endif
  /* Reset flag full com received PNC signal info */
  ComM_PncReqtedflag[chIndex] = COMM_FALSE;
  /* On entry of PNC sub state  Com_SendSignal()
  * and ComM_PncNetworkRequest()*/
  if (COMM_TRUE == ComM_ReqFlag[tmpPncIndex])
  {
    /* @Trace: ComM_SUD_API_599 */
    /* Reset the flag */
    ComM_ReqFlag[tmpPncIndex] = COMM_FALSE;
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    /* Get the Channels associated with the PNC*/
    noOfChannelsInPNC = ComM_PncsGlobal[tmpPncIndex].NoOfChannelPnc;
    /*Channel Index */
    handleChnlIndexInPNC = ComM_PncsGlobal[tmpPncIndex].ChannelPncIndex;
    while (noOfChannelsInPNC != COMM_ZERO)
    {
      /* Get the Channel ID from PNC Index Array */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      handleChnlIdTmp = ComM_ChnPncInxArrGlobal[handleChnlIndexInPNC];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This chIndex verified by GenTool. It is not having any impact" */
      handleChnlId = ComM_ChannelMapArray[handleChnlIdTmp];
      #else
      handleChnlId = handleChnlIdTmp;
      #endif
      #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
      /* Traceable SWS_ComM_00992 */
      /* The channel is ACTIVE */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This chIndex verified by GenTool. It is not having any impact" */
      if (COMM_ACTIVE_GW == ComM_Channels[handleChnlId].PncGatewayType)
      {
        /* @Trace: ComM_SUD_API_600 */
        /* Signal Instance Index associated with the PNC */
        signalIndex = ComM_PncsGlobal[tmpPncIndex].ComSignalIndex;
        /* Signal Count of the PNC */
        signalCount = ComM_PncsGlobal[tmpPncIndex].NoOfComSignal;
        while (signalCount != COMM_ZERO)
        {
          /* Get the Channel Id from Com Signal*/
          /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "This chIndex verified by GenTool. It is not having any impact" */
          handleCHId = ComM_ComSignal[signalIndex].ComMChannelId;
          #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
          handleChnlIndex = ComM_ChannelMapArray[handleCHId];
          #else
          handleChnlIndex = handleCHId;
          #endif
          if ((handleChnlId == handleChnlIndex) &&
            (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir))
          {
            /* @Trace: ComM_SUD_API_601 */
            /*Calculation Of Byte Index*/
            /* Traceable SWS_ComM_00825 */
            byteIndex = (uint8)(tmpPncId/COMM_EIGHT) -
                              ComM_ComSignal[signalIndex].ComMPncVectorOffset;
            /*Calculation Of Bit Index within the Byte */
            bitIndex = (uint8)(tmpPncId % COMM_EIGHT);
            /*Calculating the Mask Value for the bit Index*/
            mask = (uint8)(COMM_ONE << bitIndex);
            /*Get Signal Tx Index from Signal Index*/
            signalTxIndex = ComM_SignalTxMapArray[signalIndex];
            /* Set Tx signal to 1 */
            /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
            /* polyspace +1 RTE:OBAI [Not a defect:Low] "This chIndex verified by GenTool. It is not having any impact" */
            ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] | mask);
            /* Get the signal ID */
            signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;
            /* Invoke ComSendSignal of Com */
            (void)Com_SendSignal(signalHandleId, (const void*)ComM_SignalTx[signalTxIndex]);
          } /* End of if ((handleChnlId == handleChnlIndex) && */
          signalIndex++;
          signalCount--;
        } /* End of while */
      } /* End of if (COMM_ACTIVE_GW ==
                                ComM_Channels[handleChnlId].PncGatewayType) */
      /* Traceable SWS_ComM_00164, SWS_ComM_00959 */
      /* The channel is PASSIVE */
      else if (COMM_PASSIVE_GW == ComM_Channels[handleChnlId].PncGatewayType)
      {
        /* @Trace: ComM_SUD_API_602 */
        ComM_PNCNetwReq_PassiveGW(tmpPncIndex, handleChnlId);
      }
      else
      {
        /* @Trace: ComM_SUD_API_603 */
        /* To Avoid MISRA-C */
      }
      #endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
      /* Decrement the Number of channels */
      noOfChannelsInPNC--;
      /* Increment the channel Index */
      handleChnlIndexInPNC++;
      /* Network request for the channel under PNC, Provided FULL NM variant*/
      if ((COMM_TRUE == ComM_Channels[handleChnlId].PncNmRequest) &&
        (COMM_NMVARIANT_FULL == ComM_Channels[handleChnlId].NmVariant))
      {
        /* @Trace: ComM_SUD_API_604 */
        ComM_SwitchComMMode(handleChnlId, COMM_FULL_COMMUNICATION);
        /* Change sub state to Network Requested */
        ComM_SubComMode[handleChnlId] = COMM_FULL_COM_NETWORK_REQUESTED;
        /* Start the Min amount of duration in full Communication counter */
        ComM_TimeCnt[handleChnlId] =
                                    ComM_Channels[handleChnlId].MinFullComMode;
        (void)Nm_NetworkRequest(ComM_Channels[handleChnlId].ChannelId);
      }
      else
      {
        /* @Trace: ComM_SUD_API_605 */
        /* Do nothing */
      }
    } /* End of while (noOfChannelsInPNC != COMM_ZERO) */
    #else /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */
    #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
    /* Signal Instance Index associated with the PNC */
    signalIndex = ComM_PncsGlobal[tmpPncIndex].ComSignalIndex;
    /* Signal Count of the PNC */
    signalCount = ComM_PncsGlobal[tmpPncIndex].NoOfComSignal;
    while (signalCount != COMM_ZERO)
    {
      if (COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir)
      {
        /* @Trace: ComM_SUD_API_606 */
        /*Calculation Of Byte Index*/
        /* Traceable SWS_ComM_00825 */
        byteIndex = (tmpPncId/COMM_EIGHT) -
                              ComM_ComSignal[signalIndex].ComMPncVectorOffset;
        /*Calculation Of Bit Index within the Byte */
        bitIndex = (tmpPncId % COMM_EIGHT);
        /*Calculating the Mask Value for the bit Index*/
        mask = (uint8)(COMM_ONE << bitIndex);
        /*Get Signal Tx Index from Signal Index*/
        signalTxIndex = ComM_SignalTxMapArray[signalIndex];
        /* Set signal Tx to 1 */
        ComM_SignalTx[signalTxIndex][byteIndex] = (ComM_SignalTx[signalTxIndex][byteIndex] | mask);
        /* Get the signal ID */
        signalHandleId = ComM_ComSignal[signalIndex].ComMComSigId;
        /* Invoke ComSendSignal of Com */
        (void)Com_SendSignal(signalHandleId, (const void*)ComM_SignalTx[signalTxIndex]);
      } /* End if(COMM_TX == ComM_ComSignal[signalIndex].ComMPncComSigDir) */
      else
      {
        /* @Trace: ComM_SUD_API_607 */
        /* Do nothing */
      }
      signalIndex++;
      signalCount--;
    } /* End of while (signalCount != COMM_ZERO) */
    #endif /* #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO) */
    /* Network request for the channel under PNC, Provided FULL NM variant*/
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    if ((COMM_TRUE == ComM_Channels[chIndex].PncNmRequest) &&
      (COMM_NMVARIANT_FULL == ComM_Channels[chIndex].NmVariant))
    {
      /* @Trace: ComM_SUD_API_608 */
      /* Invoke Network Request from PNC Entry*/
      (void)Nm_NetworkRequest(ComM_Channels[chIndex].ChannelId);
    }
    else
    {
      /* @Trace: ComM_SUD_API_609 */
      /* Do nothing */
    }
    #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */
    #endif /* End of if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */
  } /* End of if (COMM_TRUE == ComM_ReqFlag[tmpPncIndex]) */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_PNCNetwReq */
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_FullComNetwReq                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_FULL_COMMUNICATION sub**
**                        state COMM_FULL_COM_NETWORK_REQUESTED.              **
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
**                        ComM_Channels, ComM_NmRequested,                    **
**                        ComM_ChannelInhibition, ComM_LimitEcuToNoCom,       **
**                        ComM_SubComMode, ComM_TimeCnt,                      **
**                        ComM_ReqedComModeCnt, ComM_InhibitionReqst,         **
**                        ComM_DcmActiveDiagnostic, ComM_NmIndication         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Nm_NetworkRequest(), ComM_FullComNetwReqSubTwo()    **
**                        ComM_FullComNetwReqSubOne(),ComM_SwitchComMMode(),  **
**                        ComM_FullComNetwReqSubThree(),                      **
                          ComM_FullComNetwReqSetFlagMode                      **
*******************************************************************************/
/* @Trace: SRS_BSW_00441 SRS_ModeMgm_00049 SRS_ComM_AR_00039 SRS_ComM_AR_00086
 * SRS_ComM_AR_00043 SRS_ComM_AR_00088 SRS_ComM_AR_00094 SRS_ComM_AR_00095
 * SRS_ComM_AR_00096 SRS_ComM_AR_00097 SRS_ComM_AR_00098 SRS_ComM_AR_00100
 * SRS_ComM_AR_00105 SRS_ComM_AR_00111 SRS_ComM_AR_00112 SRS_ComM_AR_00118
 * SRS_ComM_AR_00119 SRS_ComM_AR_00124 SRS_ComM_AR_00125 SRS_ComM_AR_00162
 * SRS_ModeMgm_09071
*/
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
FUNC(void, COMM_CODE) ComM_FullComNetwReq(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_323 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  /* Variable to store the flag if NM is in different mode */
  uint8 flagMode;
  #endif
  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;
  #endif

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) &&\
       (COMM_0PNCVECTOR_AVOIDANCE == STD_ON))
  /* Number of pnc mapping to channel */
  uint16 tmpPncCount;
  /* index of PNC */
  PNCHandleType tmpPncIndex;
  /* index of PNC in channel mapping table */
  PNCHandleType subPNCIndex;
  #endif

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;
  #endif

  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  flagMode = ComM_FullComNetwReqSetFlagMode(chIndex);
  #else
  ComM_FullComNetwReqSetFlagMode(chIndex);
  #endif

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)

  /* Check if NM Variant is FULL */
  if (COMM_NMVARIANT_FULL == tmpNmVariant)
  {
    /* @Trace: ComM_SUD_API_333 */
    /* Process switch com mode with full variant*/
    ComM_FullComNetwReqSubTwo(chIndex);
  }
  #endif

  /* If the Nm is present or if the timer has not expired when Nm is
   *   Light or None */
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  if (COMM_ONE != flagMode)
  #endif
  {
    /* @Trace: ComM_SUD_API_334 */
    ComM_FullComNetwReqSubThree(chIndex);
  }

  /* If Nm indicates Bus Sleep */
  SchM_Enter_ComM_NM_INDICATION_PROTECTION();
  if ((COMM_BUSSLEEPMODE_IND == ComM_NmIndication[chIndex])
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    && (COMM_FALSE == ComM_NmRequestProcessing[chIndex])
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_335 */
    ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
    ComM_NmIndication[chIndex] = COMM_ZERO;
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) &&\
       (COMM_0PNCVECTOR_AVOIDANCE == STD_ON))
    /* Traceable SWS_ComM_00966 */
  else if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc)
  {
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    /* @Trace: ComM_SUD_API_336 */
    tmpPncIndex = ComM_Channels[chIndex].PncIndex;
    tmpPncCount = ComM_Channels[chIndex].PncCount;
    /* loop all pnc mapping to channel */
    while (COMM_ZERO != tmpPncCount)
    {
      tmpPncCount--;
      /* ComM_ChannelToPncMapping[] :The Map provides Index*/
      subPNCIndex = ComM_ChannelToPncMapping[tmpPncIndex];

      if (COMM_TRUE == ComM_ReleaseFlag[subPNCIndex])
      {
        /* @Trace: ComM_SUD_API_337 */
        tmpPncCount = COMM_ZERO;
        /* clear relese flag */
        ComM_ReleaseFlag[subPNCIndex] = COMM_FALSE;
        /* Switch to No Communication from Silent Communication */
        ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
      }
      tmpPncIndex++;
    } /* End of while (COMM_ZERO != tmpPncCount) */
  } /* end of else if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
  #endif/*end of #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
                STD_ON) && (COMM_0PNCVECTOR_AVOIDANCE == STD_ON))*/
  else
  {
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    /* @Trace: ComM_SUD_API_338 */
    /* do nothing */
  }

  #else
  /* ========================== Implement for Post-Build ==================== */
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
                                        (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  /* Variable to store the flag if NM is in different mode */
  uint8 flagMode;
  #endif
  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;
  #endif

  #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
  /* Number of pnc mapping to channel */
  uint16 tmpPncCount;
  /* index of PNC */
  PNCHandleType tmpPncIndex;
  /* index of PNC in channel mapping table */
  PNCHandleType subPNCIndex;
  #endif

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;
  #endif

  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  flagMode = ComM_FullComNetwReqSetFlagMode(chIndex);
  #else
  ComM_FullComNetwReqSetFlagMode(chIndex);
  #endif

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Check if NM Variant is FULL */
  if (COMM_NMVARIANT_FULL == tmpNmVariant)
  {
    /* @Trace: ComM_SUD_API_348 */
    /* Process switch com mode with full variant*/
    ComM_FullComNetwReqSubTwo(chIndex);
  }
  #endif
  /* If the Nm is present or if the timer has not expired when Nm is
   *   Light or None */
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
                                        (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
  if (COMM_ONE != flagMode)
  #endif
  {
    /* @Trace: ComM_SUD_API_349 */
    ComM_FullComNetwReqSubThree(chIndex);
  }
  /* If Nm indicates Bus Sleep */
  if ((COMM_BUSSLEEPMODE_IND == ComM_NmIndication[chIndex])
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    && (COMM_FALSE == ComM_NmRequestProcessing[chIndex])
    #endif
    )
  {
    /* @Trace: ComM_SUD_API_350 */
    ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
    ComM_NmIndication[chIndex] = COMM_ZERO;
  }
  #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
  /* Traceable SWS_ComM_00966 */
  /* Check config variant enabled Pnc */
  /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  else if ((COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chIndex].ChannelPnc) && \
          (COMM_TRUE == ComM_PncEnabledFlashPB))
  {
    /* @Trace: ComM_SUD_API_351 */
    tmpPncIndex = ComM_ChannelsPNCRelatedGlobal[chIndex].PncIndex;
    tmpPncCount = ComM_ChannelsPNCRelatedGlobal[chIndex].PncCount;
    /* loop all pnc mapping to channel */
    while (COMM_ZERO != tmpPncCount)
    {
      tmpPncCount--;
      /* ComM_ChannelToPncMapping[] :The Map provides Index*/
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      subPNCIndex = ComM_ChannelToPncMappingGlobal[tmpPncIndex];
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      if (COMM_TRUE == ComM_ReleaseFlag[subPNCIndex])
      {
        /* @Trace: ComM_SUD_API_352 */
        tmpPncCount = COMM_ZERO;
        /* clear relese flag */
        ComM_ReleaseFlag[subPNCIndex] = COMM_FALSE;
        /* Switch to No Communication from Silent Communication */
        ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
      }
      tmpPncIndex++;
    } /* End of while (COMM_ZERO != tmpPncCount) */
  } /* end of else if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
  else
  {
    /* @Trace: ComM_SUD_API_353 */
    /* do nothing */
  }
  #endif/*end of #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON) */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_FullComNetwReq */
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/*******************************************************************************
** Function Name        : ComM_FullComReadySleep                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_FULL_COMMUNICATION sub**
**                        state COMM_FULL_COM_READY_SLEEP.                    **
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
**                        ComM_TimeCnt, ComM_Channels, ComM_ReqedComModeCnt   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode,                                **
**                        ComM_FullComReadySleepReleaseNmBus                  **
**                        ComM_FullComReadySleepSwitchMode                    **
*******************************************************************************/
/* @Trace: SRS_BSW_00441 SRS_ComM_AR_00039 SRS_ComM_AR_00086 SRS_ComM_AR_00043
 * SRS_ComM_AR_00099 SRS_ComM_AR_00101 SRS_ComM_AR_00102 SRS_ComM_AR_00103
 * SRS_ComM_AR_00104 SRS_ComM_AR_00111 SRS_ComM_AR_00112 SRS_ComM_AR_00124
 * SRS_ComM_AR_00162
*/
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
FUNC(void, COMM_CODE) ComM_FullComReadySleep(uint8 chIndex)
{
  /* @Trace: ComM_SUD_API_406 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;
  ComM_TimeType tmpTimeCnt;

  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;
  #endif
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) &&\
       (COMM_0PNCVECTOR_AVOIDANCE == STD_ON))
  /* Number of pnc mapping to channel */
  uint16 tmpPncCount;
  /* index of PNC */
  PNCHandleType tmpPncIndex;
  /* index of PNC in channel mapping table */
  PNCHandleType subPNCIndex;
  #endif

  /* If the bus type is other than Internal */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "This condition will evaluate to false if internal bustype is configured" */
  if (COMM_INTERNAL != ComM_Channels[chIndex].BusType)
  {
    /* @Trace: ComM_SUD_API_407 */
    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) &&\
       (COMM_0PNCVECTOR_AVOIDANCE == STD_ON))
    /* Traceable SWS_ComM_00966 */
    if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc)
    {
      /* @Trace: ComM_SUD_API_408 */
      tmpPncIndex = ComM_Channels[chIndex].PncIndex;
      tmpPncCount = ComM_Channels[chIndex].PncCount;
      /* loop all pnc mapping to channel */
      while (COMM_ZERO != tmpPncCount)
      {
        tmpPncCount--;
        /* ComM_ChannelToPncMapping[] :The Map provides Index*/
        subPNCIndex = ComM_ChannelToPncMapping[tmpPncIndex];

        if (COMM_TRUE == ComM_ReleaseFlag[subPNCIndex])
        {
          /* @Trace: ComM_SUD_API_409 */
          tmpPncCount = COMM_ZERO;
          /* clear relese flag */
          ComM_ReleaseFlag[subPNCIndex] = COMM_FALSE;
          /* Switch to No Communication from Silent Communication */
          ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
        }
        else
        {
          /* @Trace: ComM_SUD_API_410 */
          /* Do nothing */
        }
        tmpPncIndex++;
      } /* End of while (COMM_ZERO != tmpPncCount) */
    } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
    else
    #endif/*end of #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
                   STD_ON) && (COMM_0PNCVECTOR_AVOIDANCE == STD_ON))*/
    {
    	ComM_FullComReadySleepReleaseNmBus(chIndex);

      #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
      /* Traceable SWS_ComM_00891 */
      if (COMM_NMVARIANT_LIGHT == tmpNmVariant)
      {
        /* @Trace: ComM_SUD_API_418 */
        SchM_Enter_ComM_INHIBIT_CNT_PROTECTION();
        tmpTimeCnt = ComM_TimeCnt[chIndex];
        SchM_Exit_ComM_INHIBIT_CNT_PROTECTION();
        
        if ((ComM_TimeType)COMM_ZERO != tmpTimeCnt)
        {
          /* @Trace: ComM_SUD_API_419 */
          /* Decrement the Timeout */
          tmpTimeCnt--;

          /* If Timer expires */
          if ((ComM_TimeType)COMM_ZERO == tmpTimeCnt)
          {
            /* @Trace: ComM_SUD_API_420 */
            /* Switch to No Communication from Full Communication */
            ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
          }
          SchM_Enter_ComM_INHIBIT_CNT_PROTECTION();
          ComM_TimeCnt[chIndex] = tmpTimeCnt;
          SchM_Exit_ComM_INHIBIT_CNT_PROTECTION();
        } /* End of if ((ComM_TimeType)COMM_ZERO != ComM_TimeCnt[chIndex]) */
        /* 2014.07.10 - Fixed Bug #1081 by KtKim */
        /* If configured LightTimeout is 0 then switch to NO COMM immediately */
        #if (COMM_NONE_ZERO_LIGHT_TIMEOUT_PRESENT == STD_ON)
        else if((ComM_TimeType)COMM_ZERO == ComM_Channels[chIndex].NmLightTimeout)
        #endif
        {
          /* @Trace: ComM_SUD_API_421 */
          /* Switch to No Communication from Full Communication */
          ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
        }
        #if (COMM_NONE_ZERO_LIGHT_TIMEOUT_PRESENT == STD_ON)
        else
        {
          /* @Trace: ComM_SUD_API_422 */
          /* Switch to No Communication if NO COMM is requested and timer is 0 */
          if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
          {
            /* @Trace: ComM_SUD_API_423 */
            ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
          }
        }
        #endif
      } /* End of if (COMM_NMVARIANT_LIGHT == tmpNmVariant) */
      else
      {
        /* @Trace: ComM_SUD_API_424 */
        /* To avoid MISRA warning */
      }
      #endif /* #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) */
      
      ComM_FullComReadySleepSwitchMode(chIndex);
    }
  } /* End of if (COMM_INTERNAL != ComM_Channels[chIndex].BusType) */

  /* If bus type is Internal */
  /* Traceable SWS_ComM_00671 */
  #if (COMM_NONE_NMVARIANT_SUPPORT == STD_ON)
  if ((COMM_INTERNAL == ComM_Channels[chIndex].BusType) &&\
    (COMM_ZERO == ComM_ReqedComModeCnt[chIndex]))
  {
    /* @Trace: ComM_SUD_API_429 */
    /* Switch to No Communication from Full Communication */
    ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
  }
  else
  {
    /* @Trace: ComM_SUD_API_430 */
    /* do nothing */
  }
  #endif /* (COMM_NONE_NMVARIANT_SUPPORT == STD_ON) */
  #else
  /* ========================== Implement for Post-Build ==================== */
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* Variable to store the Nm variant value */
  uint8 tmpNmVariant;
  /* Get Nm Variant*/
  tmpNmVariant = ComM_Channels[chIndex].NmVariant;
  #endif
  #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
  /* Number of pnc mapping to channel */
  uint16 tmpPncCount;
  /* index of PNC */
  PNCHandleType tmpPncIndex;
  /* index of PNC in channel mapping table */
  PNCHandleType subPNCIndex;
  #endif

  /* If the bus type is other than Internal */
  if (COMM_INTERNAL != ComM_Channels[chIndex].BusType)
  {
    /* @Trace: ComM_SUD_API_431 */
    #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
    /* Traceable SWS_ComM_00966 */
    /* Check config variant enabled Pnc */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    if ((COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[chIndex].ChannelPnc) && \
       (COMM_TRUE == ComM_PncEnabledFlashPB))
    {
      /* @Trace: ComM_SUD_API_432 */
      tmpPncIndex = ComM_ChannelsPNCRelatedGlobal[chIndex].PncIndex;
      tmpPncCount = ComM_ChannelsPNCRelatedGlobal[chIndex].PncCount;
      /* loop all pnc mapping to channel */
      while (COMM_ZERO != tmpPncCount)
      {
        tmpPncCount--;
        /* ComM_ChannelToPncMapping[] :The Map provides Index*/
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        subPNCIndex = ComM_ChannelToPncMappingGlobal[tmpPncIndex];
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        if (COMM_TRUE == ComM_ReleaseFlag[subPNCIndex])
        {
          /* @Trace: ComM_SUD_API_433 */
          tmpPncCount = COMM_ZERO;
          /* clear relese flag */
          ComM_ReleaseFlag[subPNCIndex] = COMM_FALSE;
          /* Switch to No Communication from Silent Communication */
          ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
        }
        else
        {
          /* @Trace: ComM_SUD_API_434 */
          /* Do nothing */
        }
        tmpPncIndex++;
      } /* End of while (COMM_ZERO != tmpPncCount) */
    } /* End of if (COMM_TRUE == ComM_Channels[chIndex].ChannelPnc) */
    else
    #endif/*end of #if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON) */
    {
    	ComM_FullComReadySleepReleaseNmBus(chIndex);

      #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
      /* Traceable SWS_ComM_00891 */
      if (COMM_NMVARIANT_LIGHT == tmpNmVariant)
      {
        /* @Trace: ComM_SUD_API_442 */
        if ((ComM_TimeType)COMM_ZERO != ComM_TimeCnt[chIndex])
        {
          /* @Trace: ComM_SUD_API_443 */
          /* Decrement the Timeout */
          ComM_TimeCnt[chIndex]--;
          /* If Timer expires */
          if ((ComM_TimeType)COMM_ZERO == ComM_TimeCnt[chIndex])
          {
            /* @Trace: ComM_SUD_API_444 */
            /* Switch to No Communication from Full Communication */
            ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
          }
        } /* End of if ((ComM_TimeType)COMM_ZERO != ComM_TimeCnt[chIndex]) */
        /* 2014.07.10 - Fixed Bug #1081 by KtKim */
        /* If configured LightTimeout is 0 then switch to NO COMM immediately */
        else if((ComM_TimeType)COMM_ZERO == ComM_Channels[chIndex].NmLightTimeout)
        {
          /* @Trace: ComM_SUD_API_445 */
          /* Switch to No Communication from Full Communication */
          ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
        }
        else
        {
          /* @Trace: ComM_SUD_API_446 */
          /* Switch to No Communication if NO COMM is
                                                     requested and timer is 0 */
          if (COMM_ZERO == ComM_ReqedComModeCnt[chIndex])
          {
            /* @Trace: ComM_SUD_API_447 */
            ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
          }
        }
      } /* End of if (COMM_NMVARIANT_LIGHT == tmpNmVariant) */
      else
      {
        /* @Trace: ComM_SUD_API_448 */
        /* To avoid MISRA warning */
      }
      #endif /* #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) */

      ComM_FullComReadySleepSwitchMode(chIndex);
    }
  } /* End of if (COMM_INTERNAL != ComM_Channels[chIndex].BusType) */

  /* If bus type is Internal */
  /* Traceable SWS_ComM_00671 */
  #if (COMM_NONE_NMVARIANT_SUPPORT == STD_ON)
  if ((COMM_INTERNAL == ComM_Channels[chIndex].BusType) && \
    (COMM_ZERO == ComM_ReqedComModeCnt[chIndex]))
  {
    /* @Trace: ComM_SUD_API_453 */
    /* Switch to No Communication from Full Communication */
    ComM_SwitchComMMode(chIndex, COMM_NO_COMMUNICATION);
  }
  else
  {
    /* @Trace: ComM_SUD_API_454 */
    /* do nothing */
  }
  #endif /* (COMM_NONE_NMVARIANT_SUPPORT == STD_ON) */
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_FullComReadySleep */
#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
