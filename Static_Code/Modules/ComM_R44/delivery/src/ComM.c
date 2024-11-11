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
**  SRC-MODULE: ComM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM APIs                                        **
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
** 1.1.7.0        31-Jan-2024         Minuk Kim        CP44-3229              **
** 1.1.4          07-Mar-2022         ThuanVT          CP44-1598              **
** 1.1.3          16-Dec-2022         ThuanVT          BUGCLASSIC-380,        **
                                                       CP44-1324, CP44-1245   **
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #27547,    **
**                                                     #29733                 **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25506,    **
**                                                     #25546                 **
** 1.0.2          20-Dec-2020         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: ComM_SUD_FILE_001 */
#include "ComM.h"                 /* ComM header file */
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
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file */
#endif
#include "SchM_ComM.h"            /* SchM ComM interface API header file */
#if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
#include "NvM.h"                  /* NvM header file */
#endif
#if ((COMM_PNC_SUPPORT == STD_ON) &&\
  (COMM_PNC_ENABLED == STD_ON))
  /* @Trace: ComM_SUD_DATATYPE_001 */
#include "Com.h"                  /*COM header File */
#endif
#include "Rte_ComM.h"             /* RTE generated header file */
#if (COMM_CANCM_SUPPORT == STD_ON)
#include "CanCM_Cbk.h"                   /* CanCM header file */
#endif
#if (COMM_BUSLOAD_DETECTING == STD_ON)
#include "CanIf.h"
#include "CanIf_Types.h" /* CanIf_MsgType */
#endif
#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
#include "Nm.h"                   /* Nm header file */
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_Init                                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes the AUTOSAR Communication  **
**                      : Manager Module                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
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
**                        ComM_InitFlag, ComM_Channels, ComM_Data,            **
**                        ComM_SubPNCMode, ComM_ChannelInhibition             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        NvM_GetErrorStatus()                                **
*******************************************************************************/
/* @Trace: SRS_BSW_00101, SRS_BSW_00414, SRS_BSW_00358, SRS_ComM_AR_00010,
 * SRS_ComM_AR_00016, SRS_ComM_AR_00031, SRS_ComM_AR_00038, SRS_ComM_AR_00066,
 * SRS_ComM_AR_00121, SRS_ComM_AR_00141, SRS_ComM_AR_00142, SRS_ComM_AR_00011
 * SRS_ComM_AR_00156
*/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_Init(
  P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) ConfigPtr)
{
  /* @Trace: ComM_SUD_API_001 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  /* This variable is used to select variant config */
   ComM_ConfigType selectionConfig;
  if (NULL_PTR == ConfigPtr)
  {
  /* @Trace: ComM_SUD_API_002 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
                                           COMM_INIT_SID, COMM_E_PARAM_POINTER);
  #endif
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_003 */
    #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
    /* Initialize the configuration */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "the value of  ConfigPtr are generated by Tcode and has checked manual and it is not having any impact" */
    selectionConfig = *ConfigPtr;
    ComM_PncEnabledFlashPB = selectionConfig.bPncEnabledFlash;
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_004 */
      /* Load config for selection variant */
      ComM_UserPNCRelatedGlobal = selectionConfig.pComM_UserPNCRelated;
      ComM_ChannelsPNCRelatedGlobal =
                                   selectionConfig.pComM_ChannelsPNCRelatedType;
      ComM_PncUserInxArrGlobal = selectionConfig.pComM_PncUserInxArr;
      ComM_PncToUserMappingGlobal = selectionConfig.pComM_PncToUserMapping;
      ComM_ChnPncInxArrGlobal = selectionConfig.pComM_ChnPncInxArr;
      ComM_ChannelToPncMappingGlobal =
                                      selectionConfig.pComM_ChannelToPncMapping;
      ComM_PncsGlobal = selectionConfig.pComM_Pncs;
      ComM_PncMapArrayGlobal = selectionConfig.pComM_PncMapArray;
    }
    else
    {
      /* @Trace: ComM_SUD_API_005 */
      /* Do Nothing */
    }
    #endif
    #if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)

    /* This variable is used to store the return value of NvM status */
    NvM_RequestResultType condition;
    condition = NVM_REQ_NOT_OK;
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    #if (COMM_NVMSTORE_CHANNELS != COMM_ZERO)
    /*Variable to assure the sequential storage of inhibition value*/
    uint8 channelInhibitionProtect;
    #endif
    #endif
    #endif

    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON)) ||\
      (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) &&\
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
    /* Channel, User, PNC Index */
    uint16 arrIndex;
    #endif

    #if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    #if (COMM_NVMSTORE_CHANNELS != COMM_ZERO)
    /*Variable to assure the sequential storage of inhibition value*/
    channelInhibitionProtect = COMM_ZERO;
    #endif
    #endif
    #endif

    /*
     * If the NvM block descriptors configured are same across channel and general
     * containers
     */
    #if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)

    /* Check the Status of ComM Block */
    (void)NvM_GetErrorStatus(COMM_NVRAM_BLOCK_ID, &condition);

    /* If request is not accepted successfully */
    if (NVM_REQ_OK != condition)
    {
      /* @Trace: ComM_SUD_API_006 */
      #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

      /* Load default Data for Inhibit condition */
      ComM_Data.ComMFullComInhibitCounter = COMM_ZERO;
      #endif

      /* Set default value of ECU group classification */
      ComM_Data.ComMEcuInhibition = COMM_ECU_GROUP_CLASSIFICATION;

      #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))

      /* Load value of channel inhibition and Full Com Request Notification */
      for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_CHANNELS; arrIndex++)
      {
        /*Stores all the channel inhibition in global array*/
        ComM_ChannelInhibition[arrIndex] =
          ComM_Channels[arrIndex].ComMInhibition;

        /* Default value of channel specific Notification: No Need to Store */
      }

      #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
              (COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
    } /* End of if (condition != NVM_REQ_OK) */
    else /* If NVM_REQ_OK */
    {
      /* @Trace: ComM_SUD_API_007 */
      #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
      for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_CHANNELS ; arrIndex++)
      {
        #if (COMM_NVMSTORE_CHANNELS != COMM_ZERO)
        /* channel Inhibition: For NVM as well as NVM Channel storage False */
        if (COMM_TRUE == ComM_Channels[arrIndex].NoWakeUpNvmStorage)
        {
          /* @Trace: ComM_SUD_API_008 */
          ComM_ChannelInhibition[arrIndex] =
            ComM_NvmChannelInhibition[channelInhibitionProtect];
          channelInhibitionProtect++;
        }
        else
        #endif
        {
          /* @Trace: ComM_SUD_API_009 */
          ComM_ChannelInhibition[arrIndex] = ComM_Channels[arrIndex].ComMInhibition;
        }
      }
      #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
        (COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
    } /* End of else */
    #else /* End of if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) */
    #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

    /* Load default Data for Inhibit condition */
    ComM_Data.ComMFullComInhibitCounter = COMM_ZERO;
    #endif

    /* Set default value of ECU group classification */
    ComM_Data.ComMEcuInhibition = COMM_ECU_GROUP_CLASSIFICATION;

    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON))

    /* Default value of channel specific inhibition */
    for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_CHANNELS ; arrIndex++)
    {
      ComM_ChannelInhibition[arrIndex] = ComM_Channels[arrIndex].ComMInhibition;
    }

    #endif

    /* Default value of channel Notification : No Need To Store*/
    #endif /* Block descriptors */
    #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
    #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
    for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_PNCS; arrIndex++)
    {
      /* Initialize Sub PNC modes :COMM_PNC_NO_COMMUNICATION = 3*/
      ComM_SubPNCMode[arrIndex] = COMM_PNC_NO_COMMUNICATION;
    }
    #endif
    #else
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_010 */
      for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_PNCS; arrIndex++)
      {
        /* Initialize Sub PNC modes :COMM_PNC_NO_COMMUNICATION = 3*/
        ComM_SubPNCMode[arrIndex] = COMM_PNC_NO_COMMUNICATION;
      }
    }
    else
    {
      /* @Trace: ComM_SUD_API_011 */
      /* Do nothing */
    }
    #endif

    /* Set the ComM Status to Initialized */
    ComM_InitFlag = COMM_INIT;

    /* For prevent the unused argument compiler warning */
    COMM_UNUSED(ConfigPtr);
  }
} /* End of ComM_Init */

/*******************************************************************************
** Function Name        : ComM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This service returns the published information      **
**                        including Major, Minor and Patch version            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(),                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_BSW_00407 SRS_BSW_00004
 */
#if (COMM_VERSION_INFO_API == STD_ON)
FUNC(void, COMM_CODE) ComM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
  COMM_APPL_DATA) Versioninfo)
{
  /* @Trace: ComM_SUD_API_023 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if versioninfo pointer is equal to Null */
  if (NULL_PTR == Versioninfo)
  {
    /* @Trace: ComM_SUD_API_024 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETVERSIONINFO_SID, COMM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_025 */
    /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "The Versioninfo pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* Copy the vendor Id */
    Versioninfo->vendorID = COMM_VENDOR_ID;

    /* Copy the module Id */
    Versioninfo->moduleID = COMM_MODULE_ID;

    /* Copy Software Major Version */
    Versioninfo->sw_major_version = COMM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    Versioninfo->sw_minor_version = COMM_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    Versioninfo->sw_patch_version = COMM_SW_PATCH_VERSION;
    /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "The Versioninfo pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
  }
} /* End of ComM_GetVersionInfo*/
#endif /* End of if (COMM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_GetStatus                                      **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service returns the initialization status of   **
**                      : AUTOSAR Communication Manager Module                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Status                                              **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK                                      **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
/*
 * @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406
 */
FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus(P2VAR(ComM_InitStatusType,
  AUTOMATIC, COMM_APPL_DATA) Status)
{
  /* @Trace: ComM_SUD_API_026 */
  /* This Variable is used to store return value */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if passed status is equal to Null */
  if (NULL_PTR == Status)
  {
    /* @Trace: ComM_SUD_API_027 */
    /* Traceable SWS_ComM_00234, Change error code COMM_E_PARAM_POINTER */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_GETSTATUS_SID,
      COMM_E_PARAM_POINTER);
    returnValue = E_NOT_OK;
  } /* End of if (Status == NULL_PTR) */

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_028 */
    /* Load the variable with the ComM initialization status */
    *Status = (ComM_InitStatusType)ComM_InitFlag; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The Status pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
  } /* End of if (returnValue == E_OK) */
  return (returnValue);
} /* End of ComM_GetStatus */

/*******************************************************************************
** Function Name        : ComM_ResetRequestedChannel                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service reset value of the requested           **
**                      : for channel                                         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel                                             **
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
**                        ComM_InitFlag, ComM_ReqedComModeCnt[]               **
**                        ComM_RequestedComMode[], ComM_CurComMode[],         **
**                        ComM_SubComMode, ComM_ModeRequested,                **
**                        ComM_NmRequested, ComM_TotalUsers                   **
**                        ComM_Users[], ComM_ChnInxArr                        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00406 */
#if (COMM_DIRECT_CHANNEL == STD_ON)
FUNC(void, COMM_CODE) ComM_ResetRequestedChannel(NetworkHandleType Channel)
{
  uint8 noOfChannels;
  uint8 channelIndex;
  uint8 arrIndex;
  NetworkHandleType handleChnlIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
                                 COMM_RESETREQUESTEDCHANNEL_SID, COMM_E_UNINIT);
  }
  else
  #endif
  {
    if (COMM_MAX_CHANNELID >= Channel)
    {
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* Get the channel id from the mapping array */
      handleChnlIndex = ComM_ChannelMapArray[Channel];
      #else
      /* Channel Id is updated into local variable */
      handleChnlIndex = Channel;
      #endif

      /* Clear current communication mode */
      /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      ComM_CurComMode[handleChnlIndex] = COMM_NO_COMMUNICATION;
      /* Clear requests for communication modes */
      ComM_ReqedComModeCnt[handleChnlIndex] = COMM_ZERO;
      /* Clear sub communication mode */
      ComM_SubComMode[handleChnlIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
      /* Clear if any request were done for NM */
      ComM_NmRequested[handleChnlIndex] = COMM_ZERO;
      /* Clear if any request were done for SM */
      ComM_ModeRequested[handleChnlIndex] = COMM_FALSE;
      /* Load default state for user */
      arrIndex = COMM_TOTAL_USERS;
      while (arrIndex != COMM_ZERO)
      {
        arrIndex--;
        noOfChannels = ComM_Users[arrIndex].NoOfDirectChannels;
        /* Clear all user requests */
        channelIndex = ComM_Users[arrIndex].DirectChannelIndex;
        while (noOfChannels != COMM_ZERO)
        {
          /* Get the Channel index from the Channel Index Array */
          if (handleChnlIndex == ComM_ChnInxArr[channelIndex])
          {
            ComM_RequestedComMode[arrIndex] = COMM_NO_COMMUNICATION;
          }
          noOfChannels--;
          channelIndex++;
        }
      }
    } /* end of if (COMM_MAX_CHANNELID >= Channel) */
  }
}
#endif

/*******************************************************************************
** Function Name        : ComM_DeInit                                         **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service returns the De-Initialization the      **
**                      : AUTOSAR Communication Manager Module                **
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
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_ChannelsFullComMode.            **
**                        ComM_RequestedPNCMode, ComM_PncRxEIRASignal,        **
**                        ComM_ReqFlag, ComM_ReqToReadyFlag,                  **
**                        ComM_PncRxERAn, ComM_PncRxEIRA, ComM_PncRxERASignal,**
**                        ComM_SignalTx, ComM_PncEnabledFlashPB               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_ClearGlobalVariables()      **
*******************************************************************************/
/* @Trace: SRS_BSW_00406 SRS_BSW_00336 SRS_ComM_AR_00010 SRS_ComM_AR_00016
 * SRS_ComM_AR_00143 SRS_ComM_AR_00144 SRS_ComM_AR_00011
*/
FUNC(void, COMM_CODE) ComM_DeInit(void)
{
  /* @Trace: ComM_SUD_API_012 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))
  /* Com Signal index Instance Index */
  uint16 tmpIndex;

  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* Number of total ComM Com Tx signal */
  uint16 noOfComMTxSignal;
  #endif

  /* variable for temp index value */
  uint16 arrIndex;

  #endif
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_013 */
    /* Traceable SWS_ComM_00234, Change error code COMM_E_UNINIT */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_DEINIT_SID,
      COMM_E_UNINIT);
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_014 */
    /* check, if no channels are in Full Communication mode */
    if (COMM_ZERO == ComM_ChannelsFullComMode)
    {
    	ComM_ClearGlobalVariables();
      #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
      #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
        (COMM_FRNETWORK_PRESENT == STD_ON))
       /* Init value for number of COmM Com signal */
       noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;
      /* Load default state for PNC */
      for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_PNCS; arrIndex++)
      {
        ComM_RequestedPNCMode[arrIndex] = PNC_USER_NO_COMM;

        /* Flag to check COMM_PNC_REQUESTED state */
        ComM_ReqFlag[arrIndex] = COMM_FALSE;

        /* Flag to check COMM_PNC_REQUESTED to PNC_READY state */
        ComM_ReqToReadyFlag[arrIndex] = COMM_FALSE;

        /*Reset ERA Information*/
        #if (COMM_PNC_GW_ENABLED == STD_ON)
        ComM_PncRxERAn[arrIndex] = COMM_FALSE;
        #endif

        /*Reset EIRA Information*/
        ComM_PncRxEIRA[arrIndex] = COMM_FALSE;

        for (tmpIndex = COMM_ZERO; tmpIndex < COMM_TOTAL_SIGNALS; tmpIndex++)
        {
          /*Reset ERA and EIRA Com Signal Information*/
          #if (COMM_PNC_GW_ENABLED == STD_ON)
          ComM_PncRxERASignal[(arrIndex*noOfComMSignal) + tmpIndex] = COMM_FALSE;
          #endif
          ComM_PncRxEIRASignal[(arrIndex*noOfComMSignal) + tmpIndex] =
                                                                     COMM_FALSE;
        }
      }
      #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
      for (noOfComMTxSignal = COMM_ZERO; noOfComMTxSignal < COMM_TOTAL_TX_SIGNALS ; noOfComMTxSignal++)
      {
        for (arrIndex = COMM_ZERO; arrIndex < PNC_COM_MAX_INFO; arrIndex++)
        {
          ComM_SignalTx[noOfComMTxSignal][arrIndex] = COMM_ZERO;
        }
      }
      #endif
      #endif /* #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
              * (COMM_FRNETWORK_PRESENT == STD_ON))
              */
      #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
              * STD_ON))
              */

      /* Set the Initialization status as COMM_UNINIT */
      ComM_InitFlag = COMM_UNINIT;
    } /* End of if (ComM_ChannelsFullComMode == COMM_ZERO) */
  }
  #else
  /* ========================== Implement for Post-Build ==================== */
  /* Com Signal index Instance Index */
  uint16 tmpIndex;
  /* Number of total ComM Com signal */
  uint16 noOfComMSignal;
  #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
  /* Number of total ComM Com Tx signal */
  uint16 noOfComMTxSignal;
  #endif
  /* variable for temp index value */
  uint16 arrIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_017 */
    /* Traceable SWS_ComM_00234, Change error code COMM_E_UNINIT */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_DEINIT_SID,
      COMM_E_UNINIT);
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_018 */
    /* check, if no channels are in Full Communication mode */
    if (COMM_ZERO == ComM_ChannelsFullComMode)
    {
    	ComM_ClearGlobalVariables();
      /* Check config variant enabled Pnc */
      if (COMM_TRUE == ComM_PncEnabledFlashPB)
      {
        /* @Trace: ComM_SUD_API_021*/
        /* Init value for number of COmM Com signal */
         noOfComMSignal = (uint16)COMM_TOTAL_SIGNALS;
        /* Load default state for PNC */
        for (arrIndex = COMM_ZERO; arrIndex < COMM_TOTAL_PNCS; arrIndex++)
        {
          ComM_RequestedPNCMode[arrIndex] = PNC_USER_NO_COMM;

          /* Flag to check COMM_PNC_REQUESTED state */
          ComM_ReqFlag[arrIndex] = COMM_FALSE;

          /* Flag to check COMM_PNC_REQUESTED to PNC_READY state */
          ComM_ReqToReadyFlag[arrIndex] = COMM_FALSE;

          /*Reset ERA Information*/
          #if (COMM_PNC_GW_ENABLED == STD_ON)
          ComM_PncRxERAn[arrIndex] = COMM_FALSE;
          #endif

          /*Reset EIRA Information*/
          ComM_PncRxEIRA[arrIndex] = COMM_FALSE;

          for (tmpIndex = COMM_ZERO; tmpIndex < COMM_TOTAL_SIGNALS; tmpIndex++)
          {
            /*Reset ERA and EIRA Com Signal Information*/
            #if (COMM_PNC_GW_ENABLED == STD_ON)
            ComM_PncRxERASignal[(arrIndex*noOfComMSignal) + tmpIndex] = COMM_FALSE;
            #endif
            ComM_PncRxEIRASignal[(arrIndex*noOfComMSignal) + tmpIndex] =
                                                                     COMM_FALSE;
          }
        }
        #if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
        for (noOfComMTxSignal = COMM_ZERO; noOfComMTxSignal < COMM_TOTAL_TX_SIGNALS ; noOfComMTxSignal++)
        {
          for (arrIndex = COMM_ZERO; arrIndex < PNC_COM_MAX_INFO; arrIndex++)
          {
            ComM_SignalTx[noOfComMTxSignal][arrIndex] = COMM_ZERO;
          }
        }
        #endif
      } /* End of if (COMM_TRUE == ComM_PncEnabledFlashPB) */
      else
      {
        /* @Trace: ComM_SUD_API_022*/
        /* Do nothing */
      }
      /* Set the Initialization status as COMM_UNINIT */
      ComM_InitFlag = COMM_UNINIT;
    } /* End of if (ComM_ChannelsFullComMode == COMM_ZERO) */
  }
  #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
} /* End of ComM_DeInit */

/*******************************************************************************
** Function Name        : ComM_ReadInhibitCounter                             **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service returns the amount of rejected "FULL   **
**                        COMMUNICATION" user requests                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : CounterValue                                        **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_Data                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09156 SRS_ModeMgm_09155 SRS_ComM_AR_00130
 * SRS_ComM_AR_00152
 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
  (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON))
FUNC(Std_ReturnType, COMM_CODE)
  ComM_ReadInhibitCounter(P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue)
{
  /* @Trace: ComM_SUD_API_306 */
  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;
  /* Check, if the module is initialized or not */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_307 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_READINHIBITCOUNTER_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }

  /* Check, if CounterValue pointer is equal to Null */
  if (NULL_PTR == CounterValue)
  {
    /* @Trace: ComM_SUD_API_308 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_READINHIBITCOUNTER_SID, COMM_E_PARAM_POINTER);
    returnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_309 */
    /* Load Counter Pointer with the Inhibit Counter Value */
    *CounterValue = ComM_Data.ComMFullComInhibitCounter; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The CounterValue pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_ReadInhibitCounter */
#endif /* if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\*/

/*******************************************************************************
** Function Name        : ComM_ResetInhibitCounter                            **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This service resets the "Inhibited Full             **
**                        Communication Request Counter"                      **
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
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_Data                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09156 SRS_ComM_AR_00130 SRS_ComM_AR_00153
 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
  (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter(void)
{
  /* @Trace: ComM_SUD_API_310 */
  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Report to DET, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_311 */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_RESETINHIBITCOUNTER_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }
  else
  #endif /*#if(COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_312 */
    ComM_Data.ComMFullComInhibitCounter = COMM_ZERO;
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_ResetInhibitCounter */
#endif /* end of if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\ */

/*******************************************************************************
** Function Name        : ComM_SetECUGroupClassification                      **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This service changes the ECU Group Classification   **
**                        status                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Status                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_Data                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00030 SRS_ComM_AR_00106 SRS_ComM_AR_00192
 * SRS_ComM_AR_00157
 */
FUNC(Std_ReturnType, COMM_CODE)
  ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status)
{
  /* @Trace: ComM_SUD_API_313 */
  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_314 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_SETECUGROUPCLASSIFICATION_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }

  /* Check whether Status passed is valid or not */
  if (COMM_INHIBITION_RANGE < Status)
  {
    /* @Trace: ComM_SUD_API_315 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_SETECUGROUPCLASSIFICATION_SID, COMM_E_WRONG_PARAMETERS);
    returnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_316 */
    ComM_Data.ComMEcuInhibition = Status;
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_SetECUGroupClassification*/

/*******************************************************************************
** Function Name        : ComM_GetRequestedComMode                            **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This function returns the currently requested       **
**                        Communication mode of the corresponding user        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ComMode                                             **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_UserMapArray, ComM_RequestedComMode            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_UserDETCheck(),             **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09149
 */
FUNC(Std_ReturnType, COMM_CODE)
  ComM_GetRequestedComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType,
  AUTOMATIC, COMM_APPL_DATA) ComMode)
{
  /* @Trace: ComM_SUD_API_037 */
  /* This variable is to store the return values */
  Std_ReturnType returnValue;

  /* Variable to store User Index */
  uint8 tmpUserIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  returnValue = ComM_UserDETCheck(User, COMM_GETREQUESTEDCOMMODE_SID);

  /* Check, if ComMode pointer is equal to Null */
  if (NULL_PTR == ComMode)
  {
    /* @Trace: ComM_SUD_API_038 */
  /* Traceable SWS_ComM_00234,
        check null pointer with error code COMM_E_PARAM_POINTER */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETREQUESTEDCOMMODE_SID, COMM_E_PARAM_POINTER);
    returnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_039 */
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    tmpUserIndex = ComM_UserMapArray[User]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "User value and ComM_UserMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    tmpUserIndex = User;
    #endif

    /* Load the requested commode into the pointer variable */
    /* polyspace +6 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    *ComMode = ComM_RequestedComMode[tmpUserIndex]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* polyspace-end RTE:OBAI [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* Set the return variable to E_OK */
    returnValue = E_OK;
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_GetRequestedComMode */

/*******************************************************************************
** Function Name        : ComM_GetInhibitionStatus                            **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Returns the Inhibition Status of ComM channel       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Status                                              **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray, ComM_ChannelInhibition        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_ChannelDETCheck()           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00030 SRS_ComM_AR_00185 SRS_ComM_AR_00138
 */
#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE)
  ComM_GetInhibitionStatus(NetworkHandleType Channel, P2VAR(
  ComM_InhibitionStatusType, AUTOMATIC, COMM_APPL_DATA) Status)
{
  /* @Trace: ComM_SUD_API_285 */
  /* Variable to store the Return values of functions */
  Std_ReturnType returnValue;

  /* Variable to store the channel Index */
  NetworkHandleType handleChnlIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  returnValue = ComM_ChannelDETCheck(Channel, COMM_GETINHIBITIONSTATUS_SID);

  /* Report to DET, if passed status is equal to Null */
  if (NULL_PTR == Status)
  {
    /* @Trace: ComM_SUD_API_286 */
    /* Traceable SWS_ComM_00234,
      check null pointer with error code COMM_E_PARAM_POINTER */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETINHIBITIONSTATUS_SID, COMM_E_PARAM_POINTER);
    returnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_287 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Load Channel index variable with channel */
    handleChnlIndex = Channel;
    #endif

    /* Load the pointer with Inhibition status of the channel */
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "The Status pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "The Status pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "The Status pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    *Status = ComM_ChannelInhibition[handleChnlIndex]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The Status pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* polyspace-end RTE:OBAI [Not a defect:Low] "The Status pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
  /* Set the return variable to E_OK */
    returnValue = E_OK;
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_GetInhibitionStatus*/
#endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
        *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_GetCurrentComMode                              **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Requests the Current communication mode of the user **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ComMode                                             **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_UserMapArray[], ComM_Users[]                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_GetCurComModeDirectChnl(),  **
**                        ComM_GetCurComModePNC, ComM_UserDETCheck()          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_ModeMgm_09084 SRS_ModeMgm_09172 SRS_ComM_AR_00007 SRS_ComM_AR_00010
 * SRS_ComM_AR_00016 SRS_ComM_AR_00030 SRS_ComM_AR_00069 SRS_ComM_AR_00148
 * SRS_ComM_AR_00164 SRS_ComM_AR_00011
 */
FUNC(Std_ReturnType, COMM_CODE)
  ComM_GetCurrentComMode(ComM_UserHandleType User,
  P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode)
{
  /* @Trace: ComM_SUD_API_040 */
  /* Function Return Variable */
  Std_ReturnType returnValue;

  /* Lowest mode requested by user (No-Slient-Full)*/
  ComM_ModeType lowestMode;
  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 noOfChannels;
  #endif
  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 userChannelIndex;
  #endif

  /* Variable to store the user Index */
  uint8 userIndex;

  /* Init with highest mode (No-Slient-Full)*/
  lowestMode = COMM_FULL_COMMUNICATION;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the user id is valid and if ComM is initialized */
  returnValue = ComM_UserDETCheck(User, COMM_GETCURRENTCOMMODE_SID);

  /* Check, if passed Communication mode is equal to Null */
  if (NULL_PTR == ComMode)
  {
    /* @Trace: ComM_SUD_API_041 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETCURRENTCOMMODE_SID, COMM_E_PARAM_POINTER);
    returnValue = E_NOT_OK;
  }
  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_042 */
    /* User Index */
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    userIndex = ComM_UserMapArray[User]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "User value and ComM_UserMappArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    userIndex = User;
    #endif

    #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
    #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
    returnValue = ComM_GetCurComModePNC(userIndex, &lowestMode);

    /* The lowest mode may have been updated in ComM_GetCurComModePNC() */
    if (COMM_NO_COMMUNICATION != lowestMode)
    /* @Trace: ComM_SUD_API_043 */
    #endif
    #else
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_044 */
      returnValue = ComM_GetCurComModePNC(userIndex, &lowestMode);
    }
    else
    {
      /* @Trace: ComM_SUD_API_045 */
      lowestMode = COMM_FULL_COMMUNICATION;
    }
    if (COMM_NO_COMMUNICATION != lowestMode)
    #endif
    {
      /* @Trace: ComM_SUD_API_046 */
      #if (COMM_DIRECT_CHANNEL == STD_ON)
      /* Get the No of channels of the User */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      noOfChannels = ComM_Users[userIndex].NoOfDirectChannels;

      /* Channel Index */
      userChannelIndex = ComM_Users[userIndex].DirectChannelIndex;

      returnValue = ComM_GetCurComModeDirectChnl(userChannelIndex,
        noOfChannels, &lowestMode);
      #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */
    }/* End of if (lowestMode != COMM_NO_COMMUNICATION) */

    /* Update the Comm Mode   */
    *ComMode = lowestMode; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
  }
  return (returnValue);
} /* End of ComM_GetCurrentComMode */

/*******************************************************************************
** Function Name        : ComM_PreventWakeUp                                  **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service Changes the inhibition status          **
**                      : COMM_NO_WAKEUP for the corresponding channel.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, Status                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray, ComM_ChannelInhibition,       **
**                        ComM_CurComMode                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09157 SRS_ComM_AR_00030 SRS_ComM_AR_00106
 * SRS_ComM_AR_00113 SRS_ComM_AR_00149 SRS_ComM_AR_00115 SRS_ComM_AR_00137
 * SRS_ComM_AR_00139 SRS_ComM_AR_00197
 */
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE)
  ComM_PreventWakeUp(NetworkHandleType Channel, boolean Status)
{
  /* @Trace: ComM_SUD_API_288 */
  /* The variable returnValue is used for return values */
  Std_ReturnType returnValue;

  /* The variable index is used as array index */
  NetworkHandleType handleChnlIndex;

  boolean LblFlag;

  LblFlag = COMM_FALSE;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  returnValue = ComM_ChannelDETCheck(Channel, COMM_PREVENTWAKEUP_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_289 */
    /* Set the returnValue to E_OK */
    returnValue = E_OK;

    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* The index variable is updated with Channel */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    handleChnlIndex = Channel;
    #endif

    /* If the current mode is not No or Silent then set wake up inhibition */
    /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +4 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if ((COMM_NO_COMMUNICATION == ComM_CurComMode[handleChnlIndex]) ||
    /* polyspace-end RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      (COMM_SILENT_COMMUNICATION == ComM_CurComMode[handleChnlIndex]))
    {
      /* @Trace: ComM_SUD_API_290 */
      if (COMM_ONE == (ComM_Data.ComMEcuInhibition & COMM_ONE))
      {
        /* @Trace: ComM_SUD_API_291 */
        /* Updating status array bit 0 for WAKEUP Status */
        if (COMM_TRUE == Status)
        {
          /* @Trace: ComM_SUD_API_292 */
          ComM_ChannelInhibition[handleChnlIndex] =
            (ComM_ChannelInhibition[handleChnlIndex] |
            COMM_PREVENTWAKEUP_MASK_SET);
        }
        else
        {
          /* @Trace: ComM_SUD_API_293 */
          /* Updating status array bit 0 for WAKEUP Status */
          ComM_ChannelInhibition[handleChnlIndex] =
            (ComM_ChannelInhibition[handleChnlIndex] &
            COMM_PREVENTWAKEUP_MASK_CLR);
        }
      }
      else
      {
        /* @Trace: ComM_SUD_API_294 */
        LblFlag = COMM_TRUE;
      }
    }
    else
    {
      /* @Trace: ComM_SUD_API_295 */
      LblFlag = COMM_TRUE;
    }
    if (COMM_TRUE == LblFlag)
    {
      /* @Trace: ComM_SUD_API_296 */
      returnValue = E_NOT_OK;
    }
  }
  /* Return E_OK or E_NOT_OK*/
  return (returnValue);
} /* End of ComM_PreventWakeUp */
#endif /* (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_LimitChannelToNoComMode                        **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service Changes the inhibition status          **
**                      : COMM_NO_WAKEUP for the corresponding channel.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, Status                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray, ComM_ChannelInhibition        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09157 SRS_ComM_AR_00030 SRS_ComM_AR_00106
 * SRS_ComM_AR_00108 SRS_ComM_AR_00150 SRS_ComM_AR_00138 SRS_ComM_AR_00171
 * SRS_ComM_AR_00172
 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
  (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode(NetworkHandleType
  Channel, boolean Status)
{
  /* @Trace: ComM_SUD_API_297 */
  /* The variable returnValue is used for return values */
  Std_ReturnType returnValue;

  /* The variable handleChnlIndex is used as array index */
  NetworkHandleType handleChnlIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  returnValue = ComM_ChannelDETCheck(Channel, COMM_LIMITCHANNELTONOCOMMODE_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_298 */
    /* Set the returnValue to E_OK */
    returnValue = E_OK;

    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* The index variable is updated with Channel*/
    handleChnlIndex = Channel;
    #endif /* (COMM_CHANNEL_SEQUENTIAL == STD_OFF) */
    if (COMM_TWO == (ComM_Data.ComMEcuInhibition & COMM_TWO))
    {
      /* @Trace: ComM_SUD_API_299 */
      if (COMM_TRUE == Status)
      {
        /* @Trace: ComM_SUD_API_300 */
        /* Updating status array bit 1 for Limit channel to No comm inhibition*/
        /* polyspace +6 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +5 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace-begin RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        ComM_ChannelInhibition[handleChnlIndex] =
          (ComM_ChannelInhibition[handleChnlIndex] |
          COMM_LIMITCHANNELTONOCOMM_MASK_SET);
        /* polyspace-end RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      }
      else
      {
        /* @Trace: ComM_SUD_API_301 */
        /* Updating status array bit 1 for Limit channel to No comm inhibition*/
        /* polyspace +6 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +5 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace-begin RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
        ComM_ChannelInhibition[handleChnlIndex] =
          (ComM_ChannelInhibition[handleChnlIndex] &
          COMM_LIMITCHANNELTONOCOMM_MASK_CLR);
        /* polyspace-end RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      }
    } /* End if ((ComM_Data.ComMEcuInhibition & COMM_TWO) equals COMM_TWO) */
    else
    {
      /* @Trace: ComM_SUD_API_302 */
      returnValue = E_NOT_OK;
    }
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_LimitChannelToNoComMode */
#endif /* End of #if (COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
                   (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_LimitECUToNoComMode                            **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : This service Changes the inhibition status to       **
**                      : COMM_NO_COM                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Status                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_InitFlag, ComM_LimitEcuToNoCom                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09157 SRS_ComM_AR_00030 SRS_ComM_AR_00106
 * SRS_ComM_AR_00151 SRS_ComM_AR_00136 SRS_ComM_AR_00139 SRS_ComM_AR_00196
 * SRS_ComM_AR_00207
 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
  (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode(boolean Status)
{
  /* @Trace: ComM_SUD_API_303 */
  /* The variable returnValue is used for return values */
  Std_ReturnType returnValue;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Report to DET, Check whether the module is initialized or not */
  if (COMM_UNINIT == ComM_InitFlag)
  {
    /* @Trace: ComM_SUD_API_304 */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_LIMITECUTONOCOMMODE_SID, COMM_E_UNINIT);
    returnValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* @Trace: ComM_SUD_API_305 */
    /* Set the returnValue to E_OK */
    returnValue = E_OK;

    /* Update status value into global variable */
    ComM_LimitEcuToNoCom = Status;
  }
  /* Return E_OK or E_NOT_OK */
  return (returnValue);
} /* End of ComM_LimitECUToNoComMode */
#endif /* (COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\ */

/*******************************************************************************
** Function Name        : ComM_RequestComMode                                 **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Requesting of Communication mode by a user          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User, ComMode                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_MODE_LIMITATION          **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_UserMapArray                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_RequestComModeDirectChnl(), **
**                        ComM_RequestComModePNC(), ComM_UserDETCheck()       **
*******************************************************************************/
/* @Trace: SRS_BSW_00406 SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385
 * SRS_BSW_00386 SRS_ModeMgm_09083 SRS_ModeMgm_09081 SRS_ComM_AR_00003
 * SRS_ComM_AR_00116 SRS_ComM_AR_00004 SRS_ComM_AR_00010 SRS_ComM_AR_00016
 * SRS_ComM_AR_00023 SRS_ComM_AR_00027 SRS_ComM_AR_00035 SRS_ComM_AR_00039
 * SRS_ComM_AR_00069 SRS_ComM_AR_00109 SRS_ComM_AR_00110 SRS_ComM_AR_00120
 * SRS_ComM_AR_00121 SRS_ComM_AR_00128 SRS_ComM_AR_00129 SRS_ComM_AR_00135
 * SRS_ComM_AR_00145 SRS_ComM_AR_00011 SRS_ComM_AR_00131
 */
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComMode(ComM_UserHandleType User,
  ComM_ModeType ComMode)
{
  /* @Trace: ComM_SUD_API_029 */
  /* Index to the user Index */
  uint8 tmpUserIndex;

  /* Function Return Variable */
  Std_ReturnType returnValue;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  returnValue = ComM_UserDETCheck(User, COMM_REQUESTCOMMODE_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_030 */
    #if (COMM_DEV_ERROR_DETECT == STD_ON)

    /* If the requested mode is Silent then report to Det */
    if (COMM_SILENT_COMMUNICATION == ComMode)
    {
      /* @Trace: ComM_SUD_API_031 */
      (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
        COMM_REQUESTCOMMODE_SID, COMM_E_WRONG_PARAMETERS);
      returnValue = E_NOT_OK;
    }
    else
    #endif
    {
      /* @Trace: ComM_SUD_API_032 */
      #if (COMM_USER_SEQUENTIAL == STD_OFF)
      tmpUserIndex = ComM_UserMapArray[User]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "User value and ComM_UserMappArray are generated by Tcode and has checked manual and it is not having any impact" */
      #else
      /* Load the user in user index */
      tmpUserIndex = User;
      #endif

      #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
      /* Implement for Pre-Compile */
      #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
          ((COMM_CANNETWORK_PRESENT == STD_ON) || \
                                            (COMM_FRNETWORK_PRESENT == STD_ON)))
      returnValue = ComM_RequestComModePNC(tmpUserIndex, ComMode);
      #endif

      #if (COMM_DIRECT_CHANNEL == STD_ON)
      #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
          ((COMM_CANNETWORK_PRESENT == STD_ON) || \
                                            (COMM_FRNETWORK_PRESENT == STD_ON)))
      if (E_OK == returnValue)
      #endif
      {
        /* @Trace: ComM_SUD_API_033 */
        returnValue = ComM_RequestComModeDirectChnl(tmpUserIndex, ComMode);
      }
      #endif /* (COMM_DIRECT_CHANNELS == STD_ON) */

      #else
      /* Impelemt for Port-Build */
      if (COMM_TRUE == ComM_PncEnabledFlashPB)
      {
        /* @Trace: ComM_SUD_API_034 */
        returnValue = ComM_RequestComModePNC(tmpUserIndex, ComMode);
      }
      else
      {
        /* @Trace: ComM_SUD_API_035 */
        returnValue = E_OK;
      }
      #if (COMM_DIRECT_CHANNEL == STD_ON)
      if (E_OK == returnValue)
      {
        /* @Trace: ComM_SUD_API_036 */
        returnValue = ComM_RequestComModeDirectChnl(tmpUserIndex, ComMode);
      }
      #endif /* (COMM_DIRECT_CHANNELS == STD_ON) */
      #endif /* End of if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
    }
  }
  return (returnValue);
}  /* End of ComM_RequestComMode */

/*******************************************************************************
** Function Name        : ComM_GetMaxComMode                                  **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Function to query the maximum allowed               **
**                        Communication Mode of the corresponding user        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ComMode                                             **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK                                    **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_UserMapArray                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_RequestComModeDirectChnl(), **
**                        ComM_RequestComModePNC(), ComM_UserDETCheck()       **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09083 SRS_ComM_AR_00010 SRS_ComM_AR_00016
 * SRS_ComM_AR_00186 SRS_ComM_AR_00146 SRS_ComM_AR_00147 SRS_ComM_AR_00011
 */
Std_ReturnType ComM_GetMaxComMode(ComM_UserHandleType User,
  P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode)
{
  /* @Trace: ComM_SUD_API_131 */
  /* Function Return Variable */
  Std_ReturnType returnValue;
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 noOfChannels;
  #endif
  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 userChannelIndex;
  #endif
  /* Variable to store the user Index */
  uint8 userIndex;
  #endif

  /* Initiate return value as E_OK */
  /* returnValue = E_OK; */

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the user id is valid and if ComM is initialized */
  returnValue = ComM_UserDETCheck(User, COMM_GETMAXCOMMODE_SID);

  /* Check, if passed Communication mode is equal to Null */
  if (NULL_PTR == ComMode)
  {
    /* @Trace: ComM_SUD_API_132 */
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETMAXCOMMODE_SID, COMM_E_PARAM_POINTER);
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: ComM_SUD_API_133 */
    /* Do nothing */
  }

  /* Traceable SWS_ComM_00374, SWS_ComM_00796, SWS_ComM_00867 */
  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_134 */
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    /* Load the user in user index */
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    userIndex = ComM_UserMapArray[User]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "User value and ComM_UserMappArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    userIndex = User;
    #endif

    #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    ComM_GetMaxComModePNC(userIndex, ComMode);
    /* The lowest mode may have been updated in ComM_GetMaxComModePNC() */
    if (COMM_NO_COMMUNICATION != *ComMode) /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    /* @Trace: ComM_SUD_API_135 */
    #endif

    #else
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_136 */
      ComM_GetMaxComModePNC(userIndex, ComMode);
    }
    else
    {
      /* @Trace: ComM_SUD_API_137 */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "the value of  ComMode has checked in static code and it is not having any impact" */
      *ComMode = COMM_FULL_COMMUNICATION;
    }
    if (COMM_NO_COMMUNICATION != *ComMode) /* polyspace MISRA2012:D4.14 [Not a defect:Low] "The ComMode pointer shall be assigned with valid address. However, part of code is verified manually and it is not having any impact" */
    #endif
    {
      /* @Trace: ComM_SUD_API_138 */
      #if (COMM_DIRECT_CHANNEL == STD_ON)
      /* Get the No of channels of the User */
      /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      noOfChannels = ComM_Users[userIndex].NoOfDirectChannels;
      /* Channel Index */
      userChannelIndex = ComM_Users[userIndex].DirectChannelIndex;
      ComM_GetMaxComModeDirectChnl(userChannelIndex, noOfChannels, ComMode);
      #endif
    }/* End of if ((lowestMode != COMM_NO_COMMUNICATION) */
    #else
    /* Set max com mode as full com */
    *ComMode = COMM_FULL_COMMUNICATION;
    #endif
    returnValue = E_OK;
  }
  return (returnValue);
}  /* End of ComM_GetMaxComMode */

/*******************************************************************************
** Function Name        : ComM_BusSM_ModeIndication                           **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : Indication of actual bus mode by the corresponding  **
**                        Bus State Manager                                   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel, ComMode                                    **
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
**                        ComM_ChannelMapArray[], ComM_ChnInxArr[],           **
**                        ComM_CurComMode[], ComM_Users[],                    **
**                        ComM_ModeRequested[], ComM_Channels                 **
**                        ComM_ChannelToPncMapping, ComM_Pncs,                **
**                        ComM_PncToUserMapping, ComM_UserMapArray            **
**                        ComM_ChannelToUserMapping, ComM_UserRteInd[]        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Rte_Ports_ComM_CurrentMode_P(), Det_ReportError()   **
**                        ComM_ChannelDETCheck(), ComM_SwitchToNoCom()        **
**                        ComM_SwitchToFullCom(),                             **
**                        SchM_Enter_ComM_CURRENT_MODE_PROTECTION(),          **
**                        SchM_Exit_ComM_CURRENT_MODE_PROTECTION(),           **
**                        ComM_FullComMToSilentComM(),                        **
**                        ComM_IndicatePncUserLowestMode()                    **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00010 SRS_ComM_AR_00016 SRS_ComM_AR_00178
 * SRS_ComM_AR_00132 SRS_ComM_AR_00133 SRS_ComM_AR_00156 SRS_ComM_AR_00165
 * SRS_ComM_AR_00205 SRS_ComM_AR_00208
 */
FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication(NetworkHandleType Channel,
  ComM_ModeType ComMode)
{
  /* @Trace: ComM_SUD_API_055 */
  #if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* ========================== Implement for Pre-Compile =================== */

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
  /* Variable to store the Nm variant value */
  uint8 nmVarient;
  /* Variable to store Nm request in inhibition mode */
  boolean blnmReq = COMM_FALSE;
  Std_ReturnType returnVal = E_NOT_OK;
  #endif

  #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to store the User Id from the mapping array */
  ComM_UserHandleType handleUserId;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Variable to store return value E_OK or E_NOT_OK */
  Std_ReturnType returnValue;
  #endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */

  /* Channel Index */
  uint8 channelIndex;

  #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to store the User index from the mapping array */
  uint8 userIndx;
  #if ((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_OFF))

  /* Variable to access Rte function */
  #if (COMM_RTE_NOTIF == STD_ON)
  Rte_PortHandle_ComM_CurrentMode_P comMRteMode;

  /* Lowest mode requested by user (No-Slient-Full)*/
  ComM_ModeType lowestMode;
  #endif

  /* Variable to store the channel index from the mapping array */
  NetworkHandleType chnInd;

  /* Variable to store the Total No. of Channels of the User */
  uint8 noOfChannels;

  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 userChannelIndex;
  #endif

  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Variable to store the Total No. of Users of the Channel */
  uint8 noOfUsers;

  /* Index to the User Id's in the ChannelToUserMapping Array */
  uint8 tmpUserIndex;
  #endif

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_FRNETWORK_PRESENT == STD_ON))
  /* Variable to get the No of PNCs of the Channel */
  uint16 noOfPncs;

  /* variable to get the PNC Index of the channel */
  PNCHandleType tmpPncIndex;

  /* variable to get PNC Index from channel to pnc mapping */
  PNCHandleType pncInx;

  /* variable to store user associated with pnc */
  uint8 pncUserCount;

  /* variable to store user index of users associated with the pnc */
  uint8 tmpPncUserIndex;

  /* variable to store user count */
  uint8 tmpUserCount;

  tmpUserCount = COMM_TOTAL_USERS;
  while (tmpUserCount != COMM_ZERO)
  {
    tmpUserCount--;
    ComM_UserRteInd[tmpUserCount] = COMM_FALSE;
  }
  #endif
  #endif

  #if ((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_OFF))
  /* Initialization to pointer to function */
  #if (COMM_RTE_NOTIF == STD_ON)
  comMRteMode =
    (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();

  /* Initialize to Full communication */
  lowestMode = COMM_FULL_COMMUNICATION;
  #endif
  #endif
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_BUSSM_MODEINDICATION_SID);

  /* Check, if no development error occurred */
  /* polyspace +1 RTE:UNR [Not a defect:Low] "This condition can be reachable since checked manually. It has no impact." */
  if (E_OK == returnValue)
  /* @Trace: ComM_SUD_API_056 */
  #endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get Channel Index */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    channelIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    channelIndex = Channel;
    #endif /* #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF) */

    /* Check if the current mode and the indicated mode is not same */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if (ComM_CurComMode[channelIndex] != ComMode) /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    {
      /* @Trace: ComM_SUD_API_057 */
      /* Enter Data Protection */
      SchM_Enter_ComM_CURRENT_MODE_PROTECTION();

      /* Set the Current Communication Mode to indicated mode */
      ComM_CurComMode[channelIndex] = ComMode;

      /* After SM indicates the mode change for the channel which had requested
       *   the change in mode, clear the flag */
      ComM_ModeRequested[channelIndex] = COMM_FALSE;

      /* Exit Data Protection */
      SchM_Exit_ComM_CURRENT_MODE_PROTECTION();

      /* If indicated mode is No communication */
      if (COMM_NO_COMMUNICATION == ComMode)
      {
        /* @Trace: ComM_SUD_API_058 */
        /* Invoke switching to No communication */
        ComM_SwitchToNoCom(channelIndex);
      }
      #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
        (COMM_ETHNETWORK_PRESENT == STD_ON))

      /* If indicated mode is Silent communication */
      /* polyspace +2 RTE:UNR [Not a defect:Low] "This condition can be reachable since checked manually. It has no impact." */
      else if (COMM_SILENT_COMMUNICATION == ComMode)
      {
        /* @Trace: ComM_SUD_API_059 */
        ComM_FullComMToSilentComM(channelIndex);
      }
      #endif
      else
      {
        /* @Trace: ComM_SUD_API_060 */
        /* Invoke switching to Full communication */
        ComM_SwitchToFullCom(channelIndex);
      }
      #if (COMM_CANCM_SUPPORT == STD_ON)
      /* Only if bus type is CAN */
      if (COMM_ZERO == ComM_Channels[channelIndex].BusType)
      {
        /* @Trace: ComM_SUD_API_061 */
        /* Report Communication Mode change to CanCM */
        (void)CanCM_ComModeIndication(ComM_Channels[channelIndex].ChannelId,
          ComMode);
      }
      #endif

    } /* End of if (ComM_CurComMode[channelIndex] != ComMode) */

    #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
    #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) &&\
      ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
      (COMM_FRNETWORK_PRESENT == STD_ON)))

    /* If the Channel is associated  with a PNC: PNC Channel */
    if (COMM_TRUE == ComM_Channels[channelIndex].ChannelPnc)
    {
      /* @Trace: ComM_SUD_API_062 */
      /* Get the No of PNCs of the Channel */
      noOfPncs = ComM_Channels[channelIndex].PncCount;

      /* PNC Index of the channel */
      tmpPncIndex = ComM_Channels[channelIndex].PncIndex;
      while (noOfPncs != COMM_ZERO)
      {
        /* PNC Index from channel to pnc mapping */
        pncInx = ComM_ChannelToPncMapping[tmpPncIndex];

        /* Decrement the count*/
        noOfPncs--;

        /* user associated with the pnc */
        pncUserCount = ComM_Pncs[pncInx].UserCount;

        /* user index of users associated with the pnc */
        tmpPncUserIndex = ComM_Pncs[pncInx].UserIndex;
        while (pncUserCount != COMM_ZERO)
        {
          pncUserCount--;

          /* Get the User Index: Map array provides ID of the User */
          handleUserId = ComM_PncToUserMapping[tmpPncUserIndex];

          #if (COMM_USER_SEQUENTIAL == STD_OFF)
          userIndx = ComM_UserMapArray[handleUserId];
          #else
          userIndx = handleUserId;
          #endif

          /* ComM_UserRteInd[]: variable to avoid same user indication more
           * than once to RTE, Eg: Two PNC may refer to same user */
          if (COMM_TRUE != ComM_UserRteInd[userIndx])
          {
            /* @Trace: ComM_SUD_API_063 */
            /* Indicate lowest mode of user :PNC channels and Direct channels */
            ComM_PncUserLowestMode(userIndx);

            /* User : Executed in one of the PNC */
            ComM_UserRteInd[userIndx] = COMM_TRUE;
          }
          /* Increment the user index of the pnc  */
          tmpPncUserIndex++;
        }
        /* Increment the pnc index */
        tmpPncIndex++;
      }
    } /* End of #if (ComM_Channels[channelIndex].ChannelPnc == COMM_TRUE) */
    #if (COMM_DIRECT_CHANNEL == STD_ON)
    /* Note: PNC is Enabled but, Channel is not part of PNC: Direct Channel */
    else
    {
      /* @Trace: ComM_SUD_API_064 */
      /* Get the No of Users of the Channel */
      noOfUsers = ComM_Channels[channelIndex].ChannelUserCount;

      /* User Index */
      tmpUserIndex = ComM_Channels[channelIndex].ChannelUserIndex;
      /* Check the Current Communication Mode of the Each channel */
      while (noOfUsers != COMM_ZERO)
      {
        /* Decrement the Number of channels */
        noOfUsers--;

        /* Get the User Id from the channel to user mapping  */
        handleUserId = ComM_ChannelToUserMapping[tmpUserIndex];

        #if (COMM_USER_SEQUENTIAL == STD_OFF)
        userIndx = ComM_UserMapArray[handleUserId];
        #else /* if COMM_USER_SEQUENTIAL == OFF */
        /* Load the user in user index */
        userIndx = handleUserId;
        #endif

        /* Indicate lowest mode of user : PNC channels and Direct channels */
        ComM_PncUserLowestMode(userIndx);
        tmpUserIndex++;
      }
    } /* End of else */
    #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */
    #endif

    /* Note: PNC is not Enabled : Get the No of Users of the Channel */
    #if ((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_OFF))

    /* User Count */
    noOfUsers = ComM_Channels[channelIndex].ChannelUserCount;
    /* User Index */
    tmpUserIndex = ComM_Channels[channelIndex].ChannelUserIndex;

    /* Check the Current Communication Mode of the Each channel */
    while (noOfUsers != COMM_ZERO)
    {
      /* Get the Channel from Index Array */
      handleUserId = ComM_ChannelToUserMapping[tmpUserIndex];

      /* Decrement the Number of channels */
      noOfUsers--;

      #if (COMM_USER_SEQUENTIAL == STD_OFF)
      userIndx = ComM_UserMapArray[handleUserId];
      #else /* if COMM_USER_SEQUENTIAL == OFF */
      /* Load the user in user index */
      userIndx = handleUserId;
      #endif

      /* Get the No of channels of the User */
      noOfChannels = ComM_Users[userIndx].NoOfDirectChannels;

      /* Channel Index */
      userChannelIndex = ComM_Users[userIndx].DirectChannelIndex;

      /* If there are more than one user for the channel */
      if (COMM_ONE < noOfChannels)
      {
        /* @Trace: ComM_SUD_API_065 */
        /* Check the Current Communication Mode of the Each channel */
        while (noOfChannels != COMM_ZERO)
        {
          /* Get the Channel from Index Array */
          chnInd = ComM_ChnInxArr[userChannelIndex];

          /* Decrement the Number of channels */
          noOfChannels--;

          /* Check the current Communication Mode */
          if (COMM_NO_COMMUNICATION == ComM_CurComMode[chnInd])
          {
            /* @Trace: ComM_SUD_API_066 */
            #if (COMM_RTE_NOTIF == STD_ON)
            /* Get the lowest mode */
            lowestMode = COMM_NO_COMMUNICATION;
            #endif

            /* Break from while */
            noOfChannels = COMM_ZERO;
          }
          else
          {
            /* @Trace: ComM_SUD_API_067 */
            #if (COMM_RTE_NOTIF == STD_ON)
            /* Check for Silent communication */
            if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[chnInd])
            {
              /* @Trace: ComM_SUD_API_068 */
              /* Get the lowest mode */
              lowestMode = COMM_SILENT_COMMUNICATION;
            }
            #endif
            /* Check next channel associated with the same user */
            userChannelIndex++;
          } /* End of else */
        } /* End While */
      } /* End of if (noOfChannels > COMM_ONE) */
      else
      {
        /* @Trace: ComM_SUD_API_069 */
        /* If the channel has single user, directly get the current mode of
         * the channel
         */
        #if (COMM_RTE_NOTIF == STD_ON)
        lowestMode = ComM_CurComMode[channelIndex];
        #endif
      }
      /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
      #if (COMM_RTE_NOTIF == STD_ON)
      if (NULL_PTR != comMRteMode[userIndx].Switch_currentMode)
      {
        /* @Trace: ComM_SUD_API_070 */
        comMRteMode[userIndx].Switch_currentMode(lowestMode);
      }
      #endif
      tmpUserIndex++;
    }
    #endif /* End of #if ((COMM_PNC_SUPPORT == STD_OFF) &&
            * (COMM_PNC_ENABLED == STD_OFF))
            */
    #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_OFF)) ||\
         ((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_ON)))
    COMM_UNUSED(userIndx);
    #endif
    #if (COMM_DIRECT_CHANNEL == STD_ON)
    COMM_UNUSED(noOfUsers);
    COMM_UNUSED(tmpUserIndex);
    #endif
    COMM_UNUSED(handleUserId);
    #endif /* end of #if (COMM_DIRECT_USER_MAPPING == STD_OFF) */

    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    if((ComM_SubComMode[channelIndex] == COMM_FULL_COM_NETWORK_REQUESTED) &&
      (ComMode == COMM_FULL_COMMUNICATION))
    {
      /* @Trace: ComM_SUD_API_753 */
      /* Check if NM Variant is FULL */
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
      /* Get Nm Variant*/
      nmVarient = ComM_Channels[channelIndex].NmVariant;
      if (nmVarient == COMM_NMVARIANT_FULL)
      {
        /* @Trace: ComM_SUD_API_754 */
        /* Enter Data Protection */
        SchM_Enter_ComM_NM_INDICATION_PROTECTION();

        /* Check if NM is already requested */
        if (ComM_NmRequested[channelIndex] != COMM_TWO)
        {
          /* @Trace: ComM_SUD_API_755 */
          #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
            (COMM_MODE_LIMITATION_ENABLED == STD_ON))

          /* Check For Prevent WakeUp Inhibition */
          if ((ComM_ChannelInhibition[channelIndex] &
              COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET)
          {
          #endif
          /* @Trace: ComM_SUD_API_756 */
            if ((ComM_ReqedComModeCnt[channelIndex] != COMM_ZERO)
              || (ComM_DcmActiveDiagnostic[channelIndex] == COMM_TRUE)
              #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
              || (ComM_InhibitionReqst[channelIndex] != COMM_ZERO)
              #endif
              )
            {
              /* @Trace: ComM_SUD_API_757 */
              /* Set a flag */
              blnmReq = COMM_TRUE;
            } /* End of if ((ComM_ChannelInhibition[channelIndex] & */

          #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
            (COMM_MODE_LIMITATION_ENABLED == STD_ON))
          } /* End of if (ComM_NmRequested[channelIndex] != COMM_TWO) */
            /* Active diagnostic shall not be inhibited */
          else if (ComM_DcmActiveDiagnostic[channelIndex] == COMM_TRUE)
          {
            /* @Trace: ComM_SUD_API_758 */
            /* Set a flag */
            blnmReq = COMM_TRUE;
          }
          else
          {
          /* To avoid MISRA warning */
          }
          #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
                  *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
          /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
          /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
          if (blnmReq == COMM_TRUE)
          {
            /* @Trace: ComM_SUD_API_759 */
            /* 25120 */
            /* Request Nm Bus Communication */
            returnVal = Nm_NetworkRequest(ComM_Channels[channelIndex].ChannelId);

            if(E_OK == returnVal)
            {
              /* @Trace: ComM_SUD_API_760 */
              /* Set Flag for Nm is requested for network */
              ComM_NmRequested[channelIndex] = COMM_TWO;
              ComM_NmRequestProcessing[channelIndex] = COMM_TRUE;
            }else{
              /* To do Nothing */
            }
          }
          /* Exit Data Protection */
          SchM_Exit_ComM_NM_INDICATION_PROTECTION();
        }
        else
        {
          /* Exit Data Protection */
          SchM_Exit_ComM_NM_INDICATION_PROTECTION();
        }

      } /* End of if (nmVarient == COMM_NMVARIANT_FULL) */
    }
    #endif /* (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */
  }

  #else
  /* ========================== Implement for Post-Build ==================== */
  #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to store the User Id from the mapping array */
  ComM_UserHandleType handleUserId;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Variable to store return value E_OK or E_NOT_OK */
  Std_ReturnType returnValue;
  #endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */

  /* Channel Index */
  uint8 channelIndex;

  #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to store the User index from the mapping array */
  uint8 userIndx;
  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /* Check config enabled Pnc */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* Variable to access Rte function */
    #if (COMM_RTE_NOTIF == STD_ON)
    Rte_PortHandle_ComM_CurrentMode_P comMRteMode;

    /* Lowest mode requested by user (No-Slient-Full)*/
    ComM_ModeType lowestMode;
    #endif

    /* Variable to store the channel index from the mapping array */
    NetworkHandleType chnInd;

    /* Variable to store the Total No. of Channels of the User */
    uint8 noOfChannels;

    /* Index to the channel Id's in the ChannelIndex Array */
    uint8 userChannelIndex;
  // }
  // else
  // {
    /* Do nothing */
  // }


  /* Variable to store the Total No. of Users of the Channel */
  uint8 noOfUsers;

  /* Index to the User Id's in the ChannelToUserMapping Array */
  uint8 tmpUserIndex;
  #endif

  /* Check config enabled Pnc */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* Variable to get the No of PNCs of the Channel */
    uint16 noOfPncs;

    /* variable to get the PNC Index of the channel */
    PNCHandleType tmpPncIndex;

    /* variable to get PNC Index from channel to pnc mapping */
    PNCHandleType pncInx;

    /* variable to store user associated with pnc */
    uint8 pncUserCount;

    /* variable to store user index of users associated with the pnc */
    uint8 tmpPncUserIndex;

    /* variable to store user count */
    uint8 tmpUserCount;

    tmpUserCount = COMM_TOTAL_USERS;
    while (tmpUserCount != COMM_ZERO)
    {
      tmpUserCount--;
      ComM_UserRteInd[tmpUserCount] = COMM_FALSE;
    }
  // }
  // else
  // {
    /* Do nothing */
  // }

  /* Check config enabled Pnc */
  // if (COMM_TRUE == ComM_PncEnabledFlashPB)
  // {
    /* Initialization to pointer to function */
    #if (COMM_DIRECT_CHANNEL == STD_ON)
    #if (COMM_RTE_NOTIF == STD_ON)
    comMRteMode =
      (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();

    /* Initialize to Full communication */
    lowestMode = COMM_FULL_COMMUNICATION;
    #endif
    #endif
  // }
  // else
  // {
    /* Do nothing */
  // }
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_BUSSM_MODEINDICATION_SID);

  /* Check, if no development error occurred */
  /* polyspace +1 RTE:UNR [Not a defect:Low] "This condition can be reachable since checked manually. It has no impact." */
  if (E_OK == returnValue)
  /* @Trace: ComM_SUD_API_071 */
  #endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get Channel Index */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */
    channelIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    /* Channel Id is updated into local variable */
    channelIndex = Channel;
    #endif /* #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF) */

    /* Check if the current mode and the indicated mode is not same */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if (ComM_CurComMode[channelIndex] != ComMode) /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    {
      /* @Trace: ComM_SUD_API_072 */
      /* Enter Data Protection */
      SchM_Enter_ComM_CURRENT_MODE_PROTECTION();

      /* Set the Current Communication Mode to indicated mode */
      ComM_CurComMode[channelIndex] = ComMode;

      /* After SM indicates the mode change for the channel which had requested
       *   the change in mode, clear the flag */
      ComM_ModeRequested[channelIndex] = COMM_FALSE;

      /* Exit Data Protection */
      SchM_Exit_ComM_CURRENT_MODE_PROTECTION();

      /* If indicated mode is No communication */
      if (COMM_NO_COMMUNICATION == ComMode)
      {
        /* @Trace: ComM_SUD_API_073 */
        /* Invoke switching to No communication */
        ComM_SwitchToNoCom(channelIndex);
      }
      #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
        (COMM_ETHNETWORK_PRESENT == STD_ON))

      /* If indicated mode is Silent communication */
      /* polyspace +2 RTE:UNR [Not a defect:Low] "This condition can be reachable since checked manually. It has no impact." */
      else if (COMM_SILENT_COMMUNICATION == ComMode)
      {
        /* @Trace: ComM_SUD_API_074 */
        ComM_FullComMToSilentComM(channelIndex);
      }
      #endif
      else
      {
        /* @Trace: ComM_SUD_API_075 */
        /* Invoke switching to Full communication */
        ComM_SwitchToFullCom(channelIndex);
      }
      #if (COMM_CANCM_SUPPORT == STD_ON)
      /* Only if bus type is CAN */
      if (COMM_ZERO == ComM_Channels[channelIndex].BusType)
      {
        /* @Trace: ComM_SUD_API_076 */
        /* Report Communication Mode change to CanCM */
        (void)CanCM_ComModeIndication(ComM_Channels[channelIndex].ChannelId,
          ComMode);
      }
      else
      {
        /* @Trace: ComM_SUD_API_077 */
        /* Do nothing */
      }
      #endif
    } /* End of if (ComM_CurComMode[channelIndex] != ComMode) */

    #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
    /* Check config enabled Pnc */
    if (COMM_TRUE == ComM_PncEnabledFlashPB)
    {
      /* @Trace: ComM_SUD_API_078 */
      /* If the Channel is associated  with a PNC: PNC Channel */
      if (COMM_TRUE == ComM_ChannelsPNCRelatedGlobal[channelIndex].ChannelPnc)
      {
        /* @Trace: ComM_SUD_API_079 */
        /* Get the No of PNCs of the Channel */
        noOfPncs = ComM_ChannelsPNCRelatedGlobal[channelIndex].PncCount;

        /* PNC Index of the channel */
        tmpPncIndex = ComM_ChannelsPNCRelatedGlobal[channelIndex].PncIndex;
        while (noOfPncs != COMM_ZERO)
        {
          /* PNC Index from channel to pnc mapping */
          pncInx = ComM_ChannelToPncMappingGlobal[tmpPncIndex];

          /* Decrement the count*/
          noOfPncs--;

          /* user associated with the pnc */
          pncUserCount = ComM_PncsGlobal[pncInx].UserCount;

          /* user index of users associated with the pnc */
          tmpPncUserIndex = ComM_PncsGlobal[pncInx].UserIndex;
          while (pncUserCount != COMM_ZERO)
          {
            pncUserCount--;

            /* Get the User Index: Map array provides ID of the User */
            handleUserId = ComM_PncToUserMappingGlobal[tmpPncUserIndex];

            #if (COMM_USER_SEQUENTIAL == STD_OFF)
            userIndx = ComM_UserMapArray[handleUserId];
            #else
            userIndx = handleUserId;
            #endif

            ComM_IndicatePncUserLowestMode(userIndx);
            /* Increment the user index of the pnc  */
            tmpPncUserIndex++;
          }
          /* Increment the pnc index */
          tmpPncIndex++;
        }
      }
      #if (COMM_DIRECT_CHANNEL == STD_ON)
      /* Note: PNC is Enabled but, Channel is not part of PNC: Direct Channel */
      else
      {
        /* @Trace: ComM_SUD_API_082 */
        /* Get the No of Users of the Channel */
        noOfUsers = ComM_Channels[channelIndex].ChannelUserCount;

        /* User Index */
        tmpUserIndex = ComM_Channels[channelIndex].ChannelUserIndex;
        /* Check the Current Communication Mode of the Each channel */
        while (noOfUsers != COMM_ZERO)
        {
          /* Decrement the Number of channels */
          noOfUsers--;

          /* Get the User Id from the channel to user mapping  */
          handleUserId = ComM_ChannelToUserMapping[tmpUserIndex];

          #if (COMM_USER_SEQUENTIAL == STD_OFF)
          userIndx = ComM_UserMapArray[handleUserId];
          #else /* if COMM_USER_SEQUENTIAL == OFF */
          /* Load the user in user index */
          userIndx = handleUserId;
          #endif

          /* Indicate lowest mode of user : PNC channels and Direct channels */
          ComM_PncUserLowestMode(userIndx);
          tmpUserIndex++;
        }
      } /* End of else */
      #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */
    }
    #if (COMM_DIRECT_CHANNEL == STD_ON)
    else
    {
      /* @Trace: ComM_SUD_API_083 */
      /* PNC is not Enabled for config: Get the No of Users of the Channel */
      /* User Count */
      noOfUsers = ComM_Channels[channelIndex].ChannelUserCount;

      /* User Index */
      tmpUserIndex = ComM_Channels[channelIndex].ChannelUserIndex;

      /* Check the Current Communication Mode of the Each channel */
      while (noOfUsers != COMM_ZERO)
      {
        /* Get the Channel from Index Array */
        handleUserId = ComM_ChannelToUserMapping[tmpUserIndex];

        /* Decrement the Number of channels */
        noOfUsers--;

        #if (COMM_USER_SEQUENTIAL == STD_OFF)
        userIndx = ComM_UserMapArray[handleUserId];
        #else /* if COMM_USER_SEQUENTIAL == OFF */
        /* Load the user in user index */
        userIndx = handleUserId;
        #endif

        /* Get the No of channels of the User */
        noOfChannels = ComM_Users[userIndx].NoOfDirectChannels;

        /* Channel Index */
        userChannelIndex = ComM_Users[userIndx].DirectChannelIndex;

        /* If there are more than one user for the channel */
        if (COMM_ONE < noOfChannels)
        {
          /* @Trace: ComM_SUD_API_084 */
          /* Check the Current Communication Mode of the Each channel */
          while (noOfChannels != COMM_ZERO)
          {
            /* Get the Channel from Index Array */
            chnInd = ComM_ChnInxArr[userChannelIndex];

            /* Decrement the Number of channels */
            noOfChannels--;

            /* Check the current Communication Mode */
            if (COMM_NO_COMMUNICATION == ComM_CurComMode[chnInd])
            {
              /* @Trace: ComM_SUD_API_085 */
              #if (COMM_RTE_NOTIF == STD_ON)
              /* Get the lowest mode */
              lowestMode = COMM_NO_COMMUNICATION;
              #endif

              /* Break from while */
              noOfChannels = COMM_ZERO;
            }
            else
            {
              /* @Trace: ComM_SUD_API_086 */
              #if (COMM_RTE_NOTIF == STD_ON)
              /* Check for Silent communication */
              if (COMM_SILENT_COMMUNICATION == ComM_CurComMode[chnInd])
              {
                /* @Trace: ComM_SUD_API_087 */
                /* Get the lowest mode */
                lowestMode = COMM_SILENT_COMMUNICATION;
              }
              else
              {
                /* @Trace: ComM_SUD_API_088 */
                /* Do nothing */
              }
              #endif
              /* Check next channel associated with the same user */
              userChannelIndex++;
            } /* End of else */
          } /* End While */
        } /* End of if (noOfChannels > COMM_ONE) */
        else
        {
          /* @Trace: ComM_SUD_API_089 */
          /* If the channel has single user, directly get the current mode of
          * the channel
          */
          #if (COMM_RTE_NOTIF == STD_ON)
          lowestMode = ComM_CurComMode[channelIndex];
          #endif
        }
        /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
        #if (COMM_RTE_NOTIF == STD_ON)
        if (NULL_PTR != comMRteMode[userIndx].Switch_currentMode)
        {
          /* @Trace: ComM_SUD_API_090 */
          comMRteMode[userIndx].Switch_currentMode(lowestMode);
        }
        else
        {
          /* @Trace: ComM_SUD_API_091 */
          /* Do nothing */
        }
        #endif
        tmpUserIndex++;
      }
    }
    #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */
    #endif /* end of #if (COMM_DIRECT_USER_MAPPING == STD_OFF) */
  }
  #endif
} /* End of ComM_BusSM_ModeIndication */

/*******************************************************************************
** Function Name        : ComM_BusSM_BusSleepMode                             **
**                                                                            **
** Service ID           : 0x34                                                **
**                                                                            **
** Description          : Notification of the corresponding Bus State Manager **
**                        that the actual bus mode is Bus-Sleep               **
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
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray, ComM_NmIndication             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                         ComM_ChannelDETCheck(), Det_ReportError()          **
**                         SchM_Enter_ComM_NM_INDICATION_PROTECTION()         **
**                         SchM_Exit_ComM_NM_INDICATION_PROTECTION()          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ModeMgm_09085 SRS_ComM_AR_00087 SRS_ComM_AR_00177
 * SRS_ComM_AR_00202
 */
#if (COMM_LINSLAVE_NMVARIANT_SUPPORT == STD_ON)
FUNC(void, COMM_CODE) ComM_BusSM_BusSleepMode(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_047 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Variable to store E_OK or E_NOT_OK */
  Std_ReturnType returnValue;
  #endif

  #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to access Rte function */
  #if (COMM_RTE_NOTIF == STD_ON)
  Rte_PortHandle_ComM_CurrentMode_P comMRteMode;

  /* Lowest mode */
  ComM_ModeType lowestMode;
  #endif
  /* Variable to store the User Id from the mapping array */
  ComM_UserHandleType handleUserId;

  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Variable to store the Total No. of Users of the Channel */
  uint8 noOfUsers;

  /* Index to the User Id's in the ChannelToUserMapping Array */
  uint8 tmpUserIndex;
  #endif /* end #if (COMM_DIRECT_CHANNEL == STD_ON) */

  /* Variable to store the User index from the mapping array */
  uint8 userIndx;

  /* Initialization to pointer to function */
  #if (COMM_RTE_NOTIF == STD_ON)
  comMRteMode =
    (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();

  /* Initialize to No communication */
  lowestMode = COMM_NO_COMMUNICATION;
  #endif
  #endif /* end #if (COMM_DIRECT_USER_MAPPING == STD_OFF) */

  /* Variable to store channel */
  NetworkHandleType channelIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_BUSSM_BUSSLEEPMODE_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_048 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    channelIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    channelIndex = Channel;
    #endif

    /* Check LINSLAVE variant and Full Com mode */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if (COMM_NMVARIANT_LINSLAVE == ComM_Channels[channelIndex].NmVariant) /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    {
      /* @Trace: ComM_SUD_API_049 */
      if (COMM_FULL_COMMUNICATION == ComM_CurComMode[channelIndex])
      {
        /* @Trace: ComM_SUD_API_050 */
        /* Enter Data Protection */
        SchM_Enter_ComM_CURRENT_MODE_PROTECTION();

        /* Set the Current Communication Mode to indicated mode */
        ComM_CurComMode[channelIndex] = COMM_NO_COMMUNICATION;

        /* After SM indicates the mode change for the channel which had
         * requested the change in mode, clear the flag */
        ComM_ModeRequested[channelIndex] = COMM_FALSE;

        /* Exit Data Protection */
        SchM_Exit_ComM_CURRENT_MODE_PROTECTION();

        /* Invoke switching to No communication */
        ComM_SwitchToNoCom(channelIndex);
      } /* if (ComM_CurComMode[channelIndex] == COMM_FULL_COMMUNICATION) */
      else
      {
        /* @Trace: ComM_SUD_API_051 */
        /* Do nothing */
      }

      /* Indication mode to RTE when BusSM change mode */
      #if (COMM_DIRECT_USER_MAPPING == STD_OFF) && (COMM_RTE_NOTIF == STD_ON)
      /* User Count */
      noOfUsers = ComM_Channels[channelIndex].ChannelUserCount;
      /* User Index */
      tmpUserIndex = ComM_Channels[channelIndex].ChannelUserIndex;

      /* Check the Current Communication Mode of the Each channel */
      while (noOfUsers != COMM_ZERO)
      {
        /* Get the Channel from Index Array */
        handleUserId = ComM_ChannelToUserMapping[tmpUserIndex];

        /* Decrement the Number of channels */
        noOfUsers--;

        #if (COMM_USER_SEQUENTIAL == STD_OFF)
        userIndx = ComM_UserMapArray[handleUserId];
        #else /* if COMM_USER_SEQUENTIAL == OFF */
        /* Load the user in user index */
        userIndx = handleUserId;
        #endif

        /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
        if (NULL_PTR != comMRteMode[userIndx].Switch_currentMode)
        {
          /* @Trace: ComM_SUD_API_052 */
          comMRteMode[userIndx].Switch_currentMode(lowestMode);
        }
        else
        {
          /* @Trace: ComM_SUD_API_053 */
          /* Do nothing */
        }
        tmpUserIndex++;
      }
      #endif /* end #if(COMM_DIRECT_USER_MAPPING == STD_OFF) */
    } /* if (ComM_Channels[channelIndex].NmVariant ==
       * COMM_NMVARIANT_LINSLAVE)
       */
    else
    {
      /* @Trace: ComM_SUD_API_054 */
      /* Do nothing */
    }
  }
} /* End of ComM_BusSM_BusSleepMode(NetworkHandleType Channel) */
#endif /* End of #if (COMM_LINSLAVE_NMVARIANT_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_GetChannelBusLoad                              **
**                                                                            **
** Service ID           : 0x39                                                **
**                                                                            **
** Description          : This service provide Tx/Rx Message Counts of Channel**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BusLoad                                             **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK                                      **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelCtrlMapping                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                        CanIf_ReadBusMsgCount()                             **
*******************************************************************************/
/* @Trace: SRS_ComM_AR_00259 SRS_ComM_AR_00260 SRS_ComM_AR_00261 SRS_ComM_AR_00263 */
#if (COMM_BUSLOAD_DETECTING == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_GetChannelBusLoad(NetworkHandleType Channel,
  P2VAR(ComM_BusMsgType, AUTOMATIC, COMM_APPL_DATA) BusLoad)
{
  /* This Variable is used to store return value */
  Std_ReturnType returnValue;

  CanIf_MsgType comMBusMsg;

  /* Initialize the return variable to E_OK */
  returnValue = E_OK;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_GETCHANNELBUSLOAD_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    #if (COMM_DEV_ERROR_DETECT == STD_ON)
    /* Check, if passed status is equal to Null */
    if (ComM_ChannelCtrlMapping[Channel] == COMM_NOT_USED_CHANNEL_ID)
    {
      /* @Trace: ComM_SUD_API_747 */
      /* Report to DET  */
      (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_GETCHANNELBUSLOAD_SID,
        COMM_E_WRONG_CHANNEL);
      returnValue = E_NOT_OK;
    }
    else
    #endif
    {
      /* @Trace: ComM_SUD_API_749 */
      CanIf_ReadBusMsgCount(ComM_ChannelCtrlMapping[Channel], &comMBusMsg);
      BusLoad->usTxMsgCnt = comMBusMsg.usTxMsgCnt;
      BusLoad->usRxMsgCnt = comMBusMsg.usRxMsgCnt;
    }
  }
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* @Trace: ComM_SUD_API_748 */
    /* Do nothing */
  }
  #endif

  return (returnValue);
} /* End of ComM_GetChannelBusLoad */
#endif

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

