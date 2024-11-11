/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm.c                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : This file provides definitions of following Nm APIs:          **
**              Nm_Init                                                       **
**              Nm_MainFunction                                               **
**              Nm_PassiveStartUp                                             **
**              Nm_NetworkRequest                                             **
**              Nm_NetworkRelease                                             **
**              Nm_DisableCommunication                                       **
**              Nm_EnableCommunication                                        **
**              Nm_SetUserData                                                **
**              Nm_GetUserData                                                **
**              Nm_GetPduData                                                 **
**              Nm_RepeatMessageRequest                                       **
**              Nm_GetNodeIdentifier                                          **
**              Nm_GetLocalNodeIdentifier                                     **
**              Nm_CheckRemoteSleepIndication                                 **
**              Nm_GetState                                                   **
**              Nm_GetVersionInfo                                             **
**              Nm_NetworkStartIndication                                     **
**              Nm_NetworkMode                                                **
**              Nm_BusSleepMode                                               **
**              Nm_PrepareBusSleepMode                                        **
**              NM_SynchronizeMode                                            **
**              Nm_RemoteSleepIndication                                      **
**              Nm_RemoteSleepCancellation                                    **
**              Nm_SynchronizationPoint                                       **
**              Nm_CoordReadyToSleepIndication                                **
**              Nm_CoordReadyToSleepCancellation                              **
**              Nm_PduRxIndication                                            **
**              Nm_StateChangeNotification                                    **
**              Nm_RepeatMessageIndication                                    **
**              Nm_TxTimeoutException                                         **
**              Nm_CarWakeUpIndication                                        **
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
********************************************************************************
** 1.0.5      19-Feb-2024   DHKim         CP44-3592, CP44-3813, CP44-3884     **
** 1.0.4      21-Apr-2023   NamNT1        CP44-1709                           **
** 1.0.1.1    20-Jun-2022   SMKwon        CP44-105                            **
** 1.0.1      16-Mar-2022   LiemNT4       Implement Post-Build and add comment**
**                                        Polyspace message                   **
** 1.0.0      04-Dec-2020   Autoever      Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: Nm_SUD_FILE_001 */
/* Inclusion of Nm Header File */
#include "Nm.h"
/* Inclusion for internal types */
#include "Nm_IntTypes.h"
/* Inclusion for global variables */
#include "Nm_Globals.h"
/* Inclusion for internal functions */
#include "Nm_IntFunc.h"

/* @Trace: SRS_BSW_00171 SRS_BSW_00301 SRS_BSW_00384
 * SRS_Nm_00150 SRS_Nm_02515
 */
#if (NM_DEV_ERROR_DETECT == STD_ON)
/* Inclusion of Det header file */
#include "Det.h"
#endif /* (NM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Nm_Init                                             **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service initializes the NM module.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr : Pointer to the selected configuration   **
**                                    set.                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : This service function has to be called after the    **
**                        initialization of the respective bus interface.     **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ClusterStatusFlag, Nm_NetworkStatusFlag,         **
**                        Nm_ModeChangeFlag, Nm_NetworkModeFlag,              **
**                        Nm_ComMRequestFlag, Nm_ShutdownTimer,               **
**                        Nm_SyncPointIndFlag                                 **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00344 SRS_BSW_00414 SRS_BSW_00358 SRS_BSW_00405
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_Init(
  P2CONST(Nm_ConfigType, AUTOMATIC, NM_APPL_CONST) ConfigPtr)
{
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  
  #if (NM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == ConfigPtr)
  {
    /* @Trace: Nm_SUD_API_223 */
    /* Report error NM_E_PARAM_POINTER to DET */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_INIT_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: Nm_SUD_API_224 */
    /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "Pointer support Post-Build shall not be null pointer when the user configuation is post-build " */
    /* Get Nm_PtrChannelConfig from selected variant */
    /* polyspace-begin RTE:IDP [Not a defect:Low] "Pointer support Post-Build shall not be null pointer when the user configuation is post-build " */
    Nm_PtrChannelConfig = ConfigPtr->ptrNm_ChannelConfig;

    /* Get Nm_PtrChannelIndexArray from selected variant */
    Nm_PtrChannelIndexArray = ConfigPtr->ptrNm_ChannelIndexArray;

    #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Get Nm_PtrChannelArray from selected variant */
    Nm_PtrChannelArray = ConfigPtr->ptrNm_ChannelArray;

    /* Get Nm_PtrClusterInfo from selected variant */
    Nm_PtrClusterInfo = ConfigPtr->ptrNm_ClusterInfo;

    /* Get Nm_PtrSchMEnterFunc from selected variant */
    Nm_PtrSchMEnterFunc = ConfigPtr->ptrNm_SchMEnterFunc;

    /* Get Nm_PtrSchMExitFunc from selected variant */
    Nm_PtrSchMExitFunc = ConfigPtr->ptrNm_SchMExitFunc;
    #endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

    #if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
    /* Get Nm_PtrCarWakeUpIndFuncPtr from selected variant */
    Nm_PtrCarWakeUpIndFuncPtr = ConfigPtr->ptrNm_CarWakeUpIndFuncPtr;
    #endif  /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

    /* Get number of channel */
    Nm_NumberOfChannel = ConfigPtr->ddNumberOfChannel;

    #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Get number coordinator cluster */
    Nm_NumberCoordCluster = ConfigPtr->ddNumberCoordCluster;
    #endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

    /* Get max channel Id */
    Nm_MaxChannelId = ConfigPtr->ddMaxChannelId;
    /* polyspace-end RTE:IDP [Not a defect:Low] "Pointer support Post-Build shall not be null pointer when the user configuation is post-build " */
    /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "Pointer support Post-Build shall not be null pointer when the user configuation is post-build" */
  }
  #else
  /* For prevent the unused argument compiler warning */
  NM_UNUSED(ConfigPtr);
  #endif /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* Counter variable */
  uint8 count;

  /* Reset all global variable of all configured networks */
  /* @Trace: Nm_SUD_API_001 */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  for (count = (uint8)NM_ZERO; count < (uint8)Nm_NumberOfChannel; count++)
  #else
  for (count = (uint8)NM_ZERO; count < (uint8)NM_NO_OF_CHANNELS; count++)
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  {
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "This Nm_NumberOfChannel is manually checked and has no impact." */
    Nm_NetworkStatusFlag[count] = NM_NW_SLEEP_INDICATED; 
    Nm_NetworkModeFlag[count] = NM_MODE_BUS_SLEEP;
    Nm_ComMRequestFlag[count] = FALSE;
    Nm_ModeChangeFlag[count] = FALSE;
    Nm_ShutdownTimer[count] = (uint32)NM_ZERO;
    /* polyspace-end RTE:OBAI [Not a defect:Low] "This Nm_NumberOfChannel is manually checked and has no impact." */
  }
  /* Reset all global variable of all configured clusters */
  /* @Trace: Nm_SUD_API_002 */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  for (count = (uint8)NM_ZERO; count < (uint8)Nm_NumberCoordCluster; count++)
  #else
  for (count = (uint8)NM_ZERO; count < (uint8)NM_NO_OF_CLUSTERS; count++)
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  {
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "This Nm_NumberCoordCluster is manually checked and has no impact." */
    Nm_ClusterStatusFlag[count] = NM_CLUSTER_SLEEP;
    Nm_SyncPointIndFlag[count] = TRUE;
    /* polyspace-end RTE:OBAI [Not a defect:Low] "This Nm_NumberCoordCluster is manually checked and has no impact." */
  }
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Set Initialization Status to NM_INIT */
  /* @Trace: Nm_SUD_API_003 */
  Nm_InitStatus = NM_INIT;
  #endif

} /* End of Nm_Init() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_MainFunction                                     **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This function implements the processes of the NM    **
**                        Interface which need a fixed cyclic scheduling.     **
**                        The evaluation of shutdown timers is done in this   **
**                        function.                                           **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Timing               : Fixed Cyclic                                        **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : This service function has to be called after the    **
**                        initialization of the respective bus interface.     **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_ClusterInfo,               **
**                        Nm_ClusterStatusFlag                                **
**                                                                            **
**                        Function(s) invoked : Nm_CheckShutdown,             **
**                        Nm_StartShutdown, Nm_PerformShutdown,               **
**                        Nm_AbortShutdown                                    **
*******************************************************************************/
/* @Trace: SRS_BSW_00424 SRS_BSW_00478 SRS_BSW_00425 SRS_BSW_00373 SRS_BSW_00450
 * SRS_Nm_00045 SRS_Nm_02514 SRS_Nm_00150
 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_MainFunction(void)
{
  /* For storing the starting index to the channel array */
  uint8 chnlStartIdx;
  /* For storing the number of channels belong to same cluster */
  uint8 clusterSize;
  /* Counter variable for all configured clusters */
  uint8 count;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if Nm module has already initiated */
  /* @Trace: Nm_SUD_API_166 */
  if (NM_INIT == Nm_InitStatus)
  #endif
  {
    /* Loop for all configured clusters */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    for (count = (uint8)NM_ZERO; count < (uint8)Nm_NumberCoordCluster; count++)
    #else
    for (count = (uint8)NM_ZERO; count < (uint8)NM_NO_OF_CLUSTERS; count++)
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    {
      /* @Trace: Nm_SUD_API_167 */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* Get a start mapping index to the array Nm_ChannelArray */
      chnlStartIdx = Nm_PtrClusterInfo[count].ChnlStartIndex; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      /* Get the cluster size */
      clusterSize = Nm_PtrClusterInfo[count].Size;
      /* Enter Data Protection */
      Nm_PtrSchMEnterFunc[chnlStartIdx].SchMFuncPtr();
      #else
      /* Get a start mapping index to the array Nm_ChannelArray */
      chnlStartIdx = Nm_ClusterInfo[count].ChnlStartIndex;
      /* Get the cluster size */
      clusterSize = Nm_ClusterInfo[count].Size;
      /* Enter Data Protection */
      Nm_SchMEnterFunc[chnlStartIdx].SchMFuncPtr();
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

      /* Check if Cluster Status indicates the shutdown has not started */
      if (NM_CLUSTER_AWAKE == Nm_ClusterStatusFlag[count]) /* polyspace RTE:OBAI [Not a defect:Low] "This Nm_NumberCoordCluster is manually checked and has no impact." */
      {
        /* Check all conditions for initiating the coordinated shutdown */
        /* @Trace: Nm_SUD_API_168 */
        Nm_CheckShutdown(chnlStartIdx, count, clusterSize);
      }
      /* else if Cluster Status is waiting the Sync Point Indication */
      else if (NM_CLUSTER_SYNC_POINT_DELAY == Nm_ClusterStatusFlag[count])
      {
        /* Delay until for this cluster invoked Nm_SynchronizationPoint */
        /* @Trace: Nm_SUD_API_169*/
        Nm_DelayShutdown(chnlStartIdx, count, clusterSize);
      }
      else
      {
        /* Check if Cluster Status indicates to initiate the shutdown */
        if (NM_CLUSTER_SHUTDOWN_READY == Nm_ClusterStatusFlag[count])
        {
          /* Start the coordinated shutdown */
          /* @Trace: Nm_SUD_API_170 */
          Nm_StartShutdown(chnlStartIdx, count, clusterSize);
        }
        else
        {
          /* No action */
        }

        /* Check if Cluster Status indicates the shutdown has been started */
        if (NM_CLUSTER_SHUTDOWN_STARTED == Nm_ClusterStatusFlag[count])
        {
          /* Processing of coordinated shutdown */
          /* @Trace: Nm_SUD_API_171 */
          Nm_PerformShutdown(chnlStartIdx, count, clusterSize);
        }
        else
        {
          /* No action */
        }

        /* Check if Cluster Status indicates the shutdown has been aborted */
        if (NM_CLUSTER_SHUTDOWN_ABORTED == Nm_ClusterStatusFlag[count])
        {
          /* Abort the coordinated shutdown */
          /* @Trace: Nm_SUD_API_172 */
          Nm_AbortShutdown(chnlStartIdx, count, clusterSize);
        }
        else
        {
          /* No action */
        }
      }
      /* Exit Data Protection */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      Nm_PtrSchMExitFunc[chnlStartIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      Nm_SchMExitFunc[chnlStartIdx].SchMFuncPtr();
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    } /* End of for loop */
  } /* End of if (NM_INIT == Nm_InitStatus) */
  #if (NM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action */
  }
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
} /* End of Nm_MainFunction() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_PassiveStartup()                                 **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This network is responsible for the passive startup **
**                        of the lower BusNm layer. If network is a part of   **
**                        a cluster, Nm_PassiveStartup() is treated as        **
**                        Nm_NetworkRequest(). If the shutdown is aborted,    **
**                        the entire cluster will be kept requested.          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle : Identification of the NM-channel    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If Passive startup of NM has failed      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_PassiveStartUp,       **
**                        Det_ReportError, Nm_GetChannelIndex,                **
**                        Nm_SetRequest                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00330 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00323 SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_00046
 * SRS_Nm_00051 SRS_Nm_00151 SRS_Nm_00154 SRS_Nm_02513 SRS_Nm_00045 SRS_Nm_02514
 * SRS_Nm_02536 SRS_Nm_02537 SRS_Nm_02511 SRS_Nm_AR_00002
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_PassiveStartUp(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  /* @Trace: Nm_SUD_API_004 */
  if (NM_INIT != Nm_InitStatus)
  {
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_PASSIVESTARTUP_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_005 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Request for channel is part of a coordinated cluster */
        /* @Trace: Nm_SUD_API_006 */
        returnVal = Nm_SetRequest(NetworkHandle, networkIdx);
      }
      else
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
      {
        /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType)
        #else
        if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        {
          /* Forward a call of <BusNm>_PassiveStartUp() */
          /* @Trace: Nm_SUD_API_007 */
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          returnVal = \
              Nm_PtrChannelConfig[networkIdx].PassiveStartUpFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #else
          returnVal = \
              Nm_ChannelConfig[networkIdx].PassiveStartUpFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        }
        else
        {
          /* No action */
        }
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_008 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_PASSIVESTARTUP_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_009 */
  return returnVal;
} /* End of Nm_PassiveStartUp() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_NetworkRequest()                                 **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service requests the appropriate lower BusNm   **
**                        Network. If the shutdown is aborted,                **
**                        the entire cluster will be kept requested.          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle : Identification of the NM-channel    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If requesting of network has failed      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_NetworkRequest,       **
**                        Det_ReportError, Nm_GetChannelIndex,                **
**                        Nm_SetRequest                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00330 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00323 SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_AR_00002
 * SRS_Nm_00046 SRS_Nm_00047 SRS_Nm_00051 SRS_Nm_00150 SRS_Nm_02537 SRS_Nm_00154
 * SRS_Nm_02513 SRS_Nm_00045 SRS_Nm_02511 SRS_Nm_02514 SRS_Nm_02516
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequest(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_010 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_NETWORKREQUEST_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_011 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    {
      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex)
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Request for channel is part of a coordinated cluster */
        /* @Trace: Nm_SUD_API_012 */
        returnVal = Nm_SetRequest(NetworkHandle, networkIdx);
      }
      else
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
      {
        /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType)
        #else
        if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        {
          /* Forward a call of <BusNm>_NetworkRequest() */
          /* @Trace: Nm_SUD_API_013 */
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          returnVal = \
              Nm_PtrChannelConfig[networkIdx].NetworkRequestFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #else
          returnVal = \
              Nm_ChannelConfig[networkIdx].NetworkRequestFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        }
        else
        {
          /* No action */
        }
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_014 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_NETWORKREQUEST_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_015 */
  return returnVal;
} /* End of Nm_NetworkRequest() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_NetworkRelease()                                 **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This API releases the appropriate BusNm network.    **
**                        conditions are evaluated i.e., a check is           **
**                        performed to see if all the networks in the cluster **
**                        are ready to go to sleep.                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle : Identification of the NM-channel    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If releasing of network has failed       **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ComMRequestFlag, Nm_ChannelConfig,               **
**                        Nm_NetworkStatusFlag,                               **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc                   **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_NetworkRelease,       **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_Nm_00150 SRS_BSW_00327 SRS_BSW_00337
 * SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323 SRS_BSW_00369 SRS_BSW_00330
 * SRS_Nm_02514 SRS_Nm_00048 SRS_Nm_00051 SRS_Nm_00154 SRS_Nm_02513 SRS_Nm_02516
 * SRS_Nm_00045 SRS_Nm_02511
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRelease(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_016 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_NETWORKRELEASE_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_017 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    {
      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex)
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Set return value to E_OK */
        /* @Trace: Nm_SUD_API_018 */
        returnVal = E_OK;

        /* Reset flag of Request-By-ComM to FALSE */
        Nm_ComMRequestFlag[networkIdx] = FALSE; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */

        /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        /* Enter Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

        /* Check if network is not considered awake */
        if (NM_NW_SLEEP_INDICATED != Nm_NetworkStatusFlag[networkIdx])
        {
          /*
           * Check if channel has NmChannelSleepMaster is set to false and
           * channel has not indicated the bus ready to sleep yet
           */
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          if ((FALSE == Nm_PtrChannelConfig[networkIdx].ChannelSleepMaster) &&
              (NM_NW_NO_RELEASE == Nm_NetworkStatusFlag[networkIdx]))
          #else
          if ((FALSE == Nm_ChannelConfig[networkIdx].ChannelSleepMaster) &&
              (NM_NW_NO_RELEASE == Nm_NetworkStatusFlag[networkIdx]))
          #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
          {
            /* Set flag to indicate that local ECU is ready to sleep */
            /* @Trace: Nm_SUD_API_020 */
            Nm_NetworkStatusFlag[networkIdx] = NM_NW_COMM_RELEASE;
          }
          else
          {
            /* Set flag to indicate that local ECU and bus are ready to sleep */
            /* @Trace: Nm_SUD_API_019 */
            Nm_NetworkStatusFlag[networkIdx] = NM_NW_COMM_BUSNM_RELEASE;
          }
        }
        else
        {
          /* No action */
        }
        /* Exit Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
      }
      else
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
      {
        /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType)
        #else
        if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        {
          /* Forward a call of <BusNm>_NetworkRelease() */
          /* @Trace: Nm_SUD_API_021 */
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          returnVal = \
            Nm_PtrChannelConfig[networkIdx].NetworkReleaseFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #else
          returnVal = \
            Nm_ChannelConfig[networkIdx].NetworkReleaseFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        }
        else
        {
          /* No action */
        }
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_022 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_NETWORKRELEASE_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_023 */
  return returnVal;
} /* End of Nm_NetworkRelease() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_DisableCommunication()                           **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service calls DisableCommunication API of the  **
**                        appropriate BusNm layer to disables the NM PDU      **
**                        transmission ability.                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle : Identification of the NM-channel    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If disabling of NM PDU transmission      **
**                                   ability has failed.                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_DisableCommunication, **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_00150 SRS_Nm_02513
 * SRS_Nm_02512
 */
#if (NM_COM_CONTROL_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_DisableCommunication(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_079 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_DISABLECOMMUNICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_080 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Call <BusNm>_DisableCommunication() */
        /* @Trace: Nm_SUD_API_081 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = \
        Nm_PtrChannelConfig[networkIdx].DisableCommunicationFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
        #else
        returnVal = \
        Nm_ChannelConfig[networkIdx].DisableCommunicationFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_082 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_DISABLECOMMUNICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_083 */
  return returnVal;
} /* End of Nm_DisableCommunication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COM_CONTROL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_EnableCommunication()                            **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service calls EnableCommunication API of the   **
**                        appropriate BusNm layer to enables the NM PDU       **
**                        transmission ability.                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle : Identification of the NM-channel    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If enabling of NM PDU transmission       **
**                                   ability has failed.                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_EnableCommunication,  **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_00150 SRS_Nm_00047
 * SRS_Nm_02512
 */
#if (NM_COM_CONTROL_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_EnableCommunication(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_084 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_ENABLECOMMUNICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_085 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Call <BusNm>_EnableCommunication() */
        /* @Trace: Nm_SUD_API_086 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = \
        Nm_PtrChannelConfig[networkIdx].EnableCommunicationFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
        #else
        returnVal = \
        Nm_ChannelConfig[networkIdx].EnableCommunicationFuncPtr(NetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_087 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_ENABLECOMMUNICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_088 */
  return returnVal;
} /* End of Nm_EnableCommunication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COM_CONTROL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_SetUserData()                                    **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This service call the SetUserData API for the       **
**                        appropriate BusNm layer to set user data for        **
**                        NM messages transmitted next on the bus.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle: Identification of the NM-channel     **
**                        nmUserDataPtr : User data for the next transmitted  **
**                                        NM message                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If setting of user data has failed       **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_SetUserData,          **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_00150
 */
#if (NM_USER_DATA_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_SetUserData(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2CONST(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_089 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_SETUSERDATA_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if (NULL_PTR == nmUserDataPtr)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_090 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_SETUSERDATA_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_091 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    {
      /*
       * Check if NmComUserDataSupport is set false and the NmBusType is not
       * configured to NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((FALSE == Nm_PtrChannelConfig[networkIdx].ComUserDataSupport) &&
          (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((FALSE == Nm_ChannelConfig[networkIdx].ComUserDataSupport) &&
          (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Call <BusNm>_SetUserData() */
        /* @Trace: Nm_SUD_API_092 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].SetUserDataFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                NetworkHandle, nmUserDataPtr);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].SetUserDataFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                NetworkHandle, nmUserDataPtr);
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_093 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_SETUSERDATA_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_094 */
  return returnVal;
} /* End of Nm_SetUserData() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_USER_DATA_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_GetUserData()                                    **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service call the GetUserData API for the       **
**                        appropriate BusNm layer to get user data out of     **
**                        the last successfully received NM message.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkHandle: Identification of the NM-channel     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmUserDataPtr : Pointer where user data out of the  **
**                                        last successfully received NM       **
**                                        message shall be copied to.         **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If getting of user data has failed       **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetUserData,          **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_02504 SRS_Nm_00150
 */
#if (NM_USER_DATA_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetUserData(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_095 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETUSERDATA_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if (NULL_PTR == nmUserDataPtr)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_096 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETUSERDATA_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_097 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) && /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call <BusNm>_GetUserData() */
        /* @Trace: Nm_SUD_API_098 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].GetUserDataFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                  NetworkHandle, nmUserDataPtr);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].GetUserDataFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                  NetworkHandle, nmUserDataPtr);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_099 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_GETUSERDATA_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_100 */
  return returnVal;
} /* End of Nm_GetUserData() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_USER_DATA_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_GetPduData()                                     **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service call the GetPduData API for the        **
**                        appropriate BusNm layer to get the whole PDU        **
**                        data out of the most recently received NM message.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkHandle: Identification of the NM-channel     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmPduData : Pointer where NM PDU shall be copied to.**
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If getting of NM PDU data has failed     **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetPduData,           **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_02506
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetPduData(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmPduData)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_101 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETPDUDATA_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if (NULL_PTR == nmPduData)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_102 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETPDUDATA_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_103 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) && /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call <BusNm>_GetPduData() */
        /* @Trace: Nm_SUD_API_104 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].GetPduDataFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                      NetworkHandle, nmPduData);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].GetPduDataFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                      NetworkHandle, nmPduData);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_105 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_GETPDUDATA_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_106 */
  return returnVal;
} /* End of Nm_GetPduData() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_RepeatMessageRequest()                           **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : Set Repeat Message Request Bit for NM messages      **
**                        transmitted next on the bus.                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle: Identification of the NM-channel     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If setting of Repeat Message Request     **
**                                   Bit has failed                           **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_RepeatMessageRequest, **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_00153 SRS_Nm_00150
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_RepeatMessageRequest(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_107 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_REPEATMESSAGEREQUEST_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_108 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call <BusNm>_RepeatMessageRequest() */
        /* @Trace: Nm_SUD_API_109 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].RepeatMessageRequestFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                              NetworkHandle);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].RepeatMessageRequestFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                               NetworkHandle);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_110 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_REPEATMESSAGEREQUEST_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_111 */
  return returnVal;
} /* End of Nm_RepeatMessageRequest() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_GetNodeIdentifier()                              **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : This service call the GetNodeIdentifier API for the **
**                        appropriate BusNm layer to get node identifier out  **
**                        of the last successfully received NM-message.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle: Identification of the NM-channel     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmNodeIdPtr : Pointer where node identifier out of  **
**                                      the last successfully received        **
**                                      NM-message shall be copied to         **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If getting of the node identifier out of **
**                                   the last received NM-message has failed  **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetNodeIdentifier,    **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_02505
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetNodeIdentifier(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_112 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETNODEIDENTIFIER_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if (NULL_PTR == nmNodeIdPtr)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_113 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETNODEIDENTIFIER_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_114 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) && /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call <BusNm>_GetNodeIdentifier() */
        /* @Trace: Nm_SUD_API_115 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].GetNodeIdentifierFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                    NetworkHandle, nmNodeIdPtr);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].GetNodeIdentifierFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                    NetworkHandle, nmNodeIdPtr);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_116 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_GETNODEIDENTIFIER_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_117 */
  return returnVal;
} /* End of Nm_GetNodeIdentifier() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_GetLocalNodeIdentifier()                         **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service call the GetLocalNodeIdentifier API    **
**                        for the appropriate BusNm layer to get node         **
**                        identifier configured for the local node.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle: Identification of the NM-channel     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmNodeIdPtr : Pointer where node identifier of the  **
**                                      local node shall be copied to         **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If getting of the node identifier of the **
**                                   local node has failed                    **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked :                               **
**                        <BusNm>_GetLocalNodeIdentifier,                     **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_02508
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetLocalNodeIdentifier(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace:  Nm_SUD_API_118 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETLOCALNODEIDENTIFIER_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if (NULL_PTR == nmNodeIdPtr)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_119 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETLOCALNODEIDENTIFIER_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_120 */
    getIndex = Nm_GetChannelIndex(NetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) && /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call <BusNm>_GetLocalNodeIdentifier() */
        /* @Trace: Nm_SUD_API_121 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].GetLocalNodeIdentifierFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                    NetworkHandle, nmNodeIdPtr);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].GetLocalNodeIdentifierFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                    NetworkHandle, nmNodeIdPtr);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_122 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                           NM_GETLOCALNODEIDENTIFIER_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_123 */
  return returnVal;
} /* End of Nm_GetLocalNodeIdentifier() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_CheckRemoteSleepIndication()                     **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : Check if remote sleep indication takes place or not.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmRemoteSleepIndPtr : Pointer where check result of **
**                                              sleep indication shall be     **
**                                              copied to                     **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If checking of remote sleep indication   **
**                                   bits has failed                          **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex,                                 **
**                        <BusNm>_CheckRemoteSleepInication                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_02513 SRS_Nm_00150
 */
#if (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_CheckRemoteSleepIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
  P2VAR(boolean, AUTOMATIC, NM_APPL_DATA) nmRemoteSleepIndPtr)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;
  /* Initiate the network index at zero */
  networkIdx = (uint8)NM_ZERO;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_124 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if (NULL_PTR == nmRemoteSleepIndPtr)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_125 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                         NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_126 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid and Passive Mode is not enabled */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if ((TRUE == getIndex) &&
        (FALSE == Nm_PtrChannelConfig[networkIdx].PassiveModeEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    if ((TRUE == getIndex) &&
        (FALSE == Nm_ChannelConfig[networkIdx].PassiveModeEnabled))
    #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
    {
      /*
       * Check if the NmBusType is not configured to
       * NM_BUSNM_LOCALNM and NM_BUSNM_J1939NM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType) &&
          (NM_BUSNM_J1939NM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */ 
      {
        /* Call <BusNm>_CheckRemoteSleepIndication() */
        /* @Trace: Nm_SUD_API_127 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].CheckRemoteSleepIndFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                        nmNetworkHandle, nmRemoteSleepIndPtr);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].CheckRemoteSleepIndFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                        nmNetworkHandle, nmRemoteSleepIndPtr);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_128 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                       NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_129 */
  return returnVal;
} /* End of Nm_CheckRemoteSleepIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_GetState()                                       **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : Returns the state of the network management.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmStatePtr : Pointer where state of the network     **
**                                     management shall be copied to          **
**                        nmModePtr  : Pointer to the location where the mode **
**                                     of the network management shall be     **
**                                     copied to                              **
**                                                                            **
** Return parameter     : E_OK     : If no error occurred.                    **
**                        E_NOT_OK : If getting of NM state has failed        **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_InitStatus,                **
**                        Nm_ChannelConfig                                    **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetState,             **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00101 SRS_Nm_00050
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetState(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
  P2VAR(Nm_StateType, AUTOMATIC, NM_APPL_DATA) nmStatePtr,
  P2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_DATA) nmModePtr)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing return value */
  Std_ReturnType returnVal;
  /* For storing result of getting channel index */
  boolean getIndex;

  /* Set return value to E_NOT_OK */
  returnVal = E_NOT_OK;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_130 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETSTATE_SID, NM_E_UNINIT);
  }
  /* Check if API called with NULL pointer */
  else if ((NULL_PTR == nmStatePtr) || (NULL_PTR == nmModePtr))
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_131 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETSTATE_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_132 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call <BusNm>_GetState() */
        /* @Trace: Nm_SUD_API_133 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        returnVal = Nm_PtrChannelConfig[networkIdx].GetStateFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                        nmNetworkHandle, nmStatePtr, nmModePtr);
        #else
        returnVal = Nm_ChannelConfig[networkIdx].GetStateFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                        nmNetworkHandle, nmStatePtr, nmModePtr);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_134 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_GETSTATE_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  /* @Trace: Nm_SUD_API_135 */
  return returnVal;
} /* End of Nm_GetState() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_GetVersionInfo                                   **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This function returns the version information of    **
**                        the Nm Module.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NmVerInfoPtr : Pointer to where to store the        **
**                                       version information of this module.  **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00003
 * SRS_BSW_00407 SRS_BSW_00482
 */
#if (NM_VERSION_INFO_API == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, NM_APPL_DATA) NmVerInfoPtr)
{
  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if API called with a NULL pointer */
  if (NULL_PTR == NmVerInfoPtr)
  {
    /* Report error NM_E_PARAM_POINTER to DET */
    /* @Trace: Nm_SUD_API_136 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_GETVERSIONINFO_SID, NM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NmVerInfoPtr shall not be null pointer when the development error detection switches off but cannot ensure that it shall point to Std_VersionInfoType structure as limitation in C" */
    /* @Trace: Nm_SUD_API_137 */
    /* Copy the vendor Id */
    NmVerInfoPtr->vendorID = (uint16)NM_VENDOR_ID;
    /* Copy the module Id */
    NmVerInfoPtr->moduleID = (uint16)NM_MODULE_ID;
    /* Copy Software Major Version */
    NmVerInfoPtr->sw_major_version = (uint8)NM_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    NmVerInfoPtr->sw_minor_version = (uint8)NM_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    NmVerInfoPtr->sw_patch_version = (uint8)NM_SW_PATCH_VERSION;
    /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NmVerInfoPtr shall not be null pointer when the development error detection switches off but cannot ensure that it shall point to Std_VersionInfoType structure as limitation in C" */
  }
} /* End of Nm_GetVersionInfo() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_NetworkStartIndication                           **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service shall notify ComM that a NM-message    **
**                        has been received in the Bus-Sleep Mode, what       **
**                        indicates that some nodes in the  network have      **
**                        entered the Network Mode.                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus                  **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex, ComM_Nm_NetworkStartIndication  **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_BSW_00330 SRS_Nm_00154
 * SRS_Nm_02513
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_NetworkStartIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_024 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_NETWORKSTARTINDICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_025 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Forward to ComM by calling ComM_Nm_NetworkStartIndication() */
      /* @Trace: Nm_SUD_API_026 */
      ComM_Nm_NetworkStartIndication(nmNetworkHandle);

      NM_UNUSED(networkIdx);
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_027 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                           NM_NETWORKSTARTINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }

} /* End of Nm_NetworkStartIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_NetworkMode                                      **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service shall notify the upper layer(ComM) that**
**                        the network management has entered Network Mode.    **
**                        In case coordinated shutdown is underway, this      **
**                        callback will result in aborted shutdown.           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig, Nm_NetworkModeFlag                **
**                        Nm_ClusterStatusFlag, Nm_ComMRequestFlag,           **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc                   **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex, ComM_Nm_NetworkMode             **
*******************************************************************************/
/* @Trace: SRS_BSW_00330 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00323 SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_00051
 * SRS_Nm_02537 SRS_Nm_00154 SRS_Nm_02513 SRS_Nm_00045 SRS_Nm_02511 SRS_Nm_02514
 * SRS_Nm_02516
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_NetworkMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  #endif

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_028 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_NETWORKMODE_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_029 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if the network belongs to a coordinated cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* @Trace: Nm_SUD_API_030 */
        /* Set the Network Mode Flag to NM_MODE_NETWORK */
        Nm_NetworkModeFlag[networkIdx] = NM_MODE_NETWORK; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */

        /* Reset flag to false as finishing the request process */
        Nm_ComMRequestFlag[networkIdx] = FALSE;

        /* Get the index to the array Nm_ClusterInfo */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        /* Enter Data Protection */
        Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr();
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        /* Enter Data Protection */
        Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        /*
         * Check if Cluster Status is set to appropriated flag of indicating
         * the shutdown has been initiated
         */
        if ((NM_CLUSTER_SYNC_POINT_DELAY == Nm_ClusterStatusFlag[clusterIdx]) || /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
            (NM_CLUSTER_SHUTDOWN_READY == Nm_ClusterStatusFlag[clusterIdx]) ||
            (NM_CLUSTER_SHUTDOWN_STARTED == Nm_ClusterStatusFlag[clusterIdx]))
        {
          /* @Trace: Nm_SUD_API_031 */
          /* Change the status of the network to trigger shutdown abortion */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_ABORTION_TRIGGER;
        }
        else
        {
          /* No action */
        }
        /* Exit Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr();
        #else
        Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
        #endif
      }
      else
      {
        /* No action */
      }
      #else
      NM_UNUSED(networkIdx);
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

      /* Forward to ComM by calling ComM_Nm_NetworkMode() */
      /* @Trace: Nm_SUD_API_032 */
      ComM_Nm_NetworkMode(nmNetworkHandle);
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_033 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_NETWORKMODE_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
} /* End of Nm_NetworkMode() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_BusSleepMode                                     **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : Notification that the network management has        **
**                        entered Bus-Sleep Mode.                             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig, Nm_NetworkModeFlag                **
**                        Nm_ClusterStatusFlag, Nm_NetworkStatusFlag,         **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc,                  **
**                        Nm_ComMRequestFlag                                  **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex, ComM_Nm_BusSleepMode            **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_BSW_00330 SRS_Nm_00051
 * SRS_Nm_02514 SRS_Nm_00154 SRS_Nm_02513 SRS_Nm_00045 SRS_Nm_02516 SRS_Nm_02511
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_BusSleepMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  #endif

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_034 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_BUSSLEEPMODE_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_035 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Forward to ComM by calling ComM_Nm_BusSleepMode() */
      /* @Trace: Nm_SUD_API_036 */
      ComM_Nm_BusSleepMode(nmNetworkHandle);

      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if the network belongs to a coordinated cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        /* Get the index to the array Nm_ClusterInfo */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        /* Enter Data Protection */
        /* polyspace-begin RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
        Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        /* Set the Network Status to indicate sleep */
        Nm_NetworkStatusFlag[networkIdx] = NM_NW_SLEEP_INDICATED;
        /* Exit Data Protection */
        Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        /* polyspace-end RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
        #else
        /* @Trace: Nm_SUD_API_037 */
        /* Enter Data Protection */
        Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
        /* Set the Network Status to indicate sleep */
        Nm_NetworkStatusFlag[networkIdx] = NM_NW_SLEEP_INDICATED;
        /* Exit Data Protection */
        Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        /*
         * Check if the coordinated cluster this network belongs to has not
         * started the shutdown process and mode changed unexpectedly and
         * there is no request by ComM
         */
        if ((NM_CLUSTER_AWAKE == Nm_ClusterStatusFlag[clusterIdx]) && /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
            (NM_MODE_NETWORK == Nm_NetworkModeFlag[networkIdx]) &&
            (FALSE == Nm_ComMRequestFlag[networkIdx]))
        {
          /* Set flag as true to indicate mode is changed unexpectedly */
          /* @Trace: Nm_SUD_API_038 */
          Nm_ModeChangeFlag[networkIdx] = TRUE;
        }
        else
        {
          /* No action */
        }

        /* Set the Network Mode Flag to NM_MODE_BUS_SLEEP */
        /* @Trace: Nm_SUD_API_039 */
        Nm_NetworkModeFlag[networkIdx] = NM_MODE_BUS_SLEEP;
      }
      else
      {
        /* No action */
      }
      #else
      NM_UNUSED(networkIdx);
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_040 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_BUSSLEEPMODE_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
} /* End of Nm_BusSleepMode() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_PrepareBusSleepMode                              **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : Notification that the network management has        **
**                        entered Prepare BusSleep Mode.                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_NetworkModeFlag, Nm_ModeChangeFlag,              **
**                        Nm_ClusterStatusFlag, Nm_ComMRequestFlag            **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex, ComM_Nm_PrepareBusSleepMode     **
*******************************************************************************/
/* @Trace: SRS_BSW_00330 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00323 SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_00051
 * SRS_Nm_02516 SRS_Nm_00154 SRS_Nm_02513 SRS_Nm_00045 SRS_Nm_02511 SRS_Nm_02514
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_PrepareBusSleepMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  #endif

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_041 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_PREPAREBUSSLEEPMODE_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_042 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Forward to ComM by calling ComM_Nm_PrepareBusSleepMode() */
      /* @Trace: Nm_SUD_API_043 */
      ComM_Nm_PrepareBusSleepMode(nmNetworkHandle);

      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if the network belongs to a coordinated cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* @Trace: Nm_SUD_API_044 */
        /* Set the Network Mode Flag to NM_MODE_PREPARE_BUS_SLEEP */
        Nm_NetworkModeFlag[networkIdx] = NM_MODE_PREPARE_BUS_SLEEP; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */

        /* Get the index to the array Nm_ClusterInfo */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        /*
         * Check if the coordinated cluster this network belongs to has not
         * started the shutdown process and there is no request by ComM
         */
        if ((NM_CLUSTER_AWAKE == Nm_ClusterStatusFlag[clusterIdx]) && /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
            (FALSE == Nm_ComMRequestFlag[networkIdx]))
        {
          /* Set flag as true to indicate mode is changed unexpectedly */
          /* @Trace: Nm_SUD_API_045 */
          Nm_ModeChangeFlag[networkIdx] = TRUE;
        }
        else
        {
          /* No action */
        }
      }
      else
      {
        /* No action */
      }
      #else
      NM_UNUSED(networkIdx);
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_046 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_PREPAREBUSSLEEPMODE_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
} /* End of Nm_PrepareBusSleepMode() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_SynchronizeMode                                  **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : This service provides notification to the upper     **
**                        layer that the network has entered Synchronize Mode **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant but not for same channel                  **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_NetworkModeFlag, Nm_ModeChangeFlag,              **
**                        Nm_ClusterStatusFlag, Nm_ComMRequestFlag            **
**                        Nm_SyncPointIndFlag                                 **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_Nm_00045 SRS_Nm_02511 SRS_Nm_02514
 * SRS_Nm_02516 SRS_Nm_AR_00003
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_SynchronizeMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  #endif

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_047 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_SYNCHRONIZEMODE_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_048 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
      /* Check if the network belongs to a coordinated cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* @Trace: Nm_SUD_API_049 */
        /* Set the Network Mode Flag to NM_MODE_SYNCHRONIZE */
        Nm_NetworkModeFlag[networkIdx] = NM_MODE_SYNCHRONIZE; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */

        /* Get the index to the array Nm_ClusterInfo */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        /*
         * Check if the coordinated cluster this network belongs to has not
         * started the shutdown process and there is no request by ComM
         */
        if ((NM_CLUSTER_AWAKE == Nm_ClusterStatusFlag[clusterIdx]) && /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
            (FALSE == Nm_ComMRequestFlag[networkIdx]))
        {
          /* Set flag as true to indicate mode is changed unexpectedly */
          /* @Trace: Nm_SUD_API_050 */
          Nm_ModeChangeFlag[networkIdx] = TRUE;
        }
        /* else if Cluster Status is waiting the Sync Point Indication */
        else if (NM_CLUSTER_SYNC_POINT_DELAY == \
                                               Nm_ClusterStatusFlag[clusterIdx])
        {
          /*
           * Clear the flag of waiting the Sync Point Indication,
           * then the coordinator can initiate the coordinated shutdown
           */
           /* @Trace: Nm_SUD_API_051 */
          Nm_SyncPointIndFlag[clusterIdx] = FALSE;
        }
        else
        {
          /* No action */
        }
      }
      else
      {
        /* No action */
      }
      #else
      NM_UNUSED(networkIdx);
      #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_052 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_SYNCHRONIZEMODE_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
} /* End of Nm_SynchronizeMode() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_RemoteSleepIndication                            **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Notification that the network management has        **
**                        detected that all other nodes on the network are    **
**                        ready to enter Bus-Sleep Mode.                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig, Nm_NetworkStatusFlag,             **
**                        Nm_ClusterInfo, Nm_SchMEnterFunc,                   **
**                        Nm_SchMExitFunc                                     **
**                                                                            **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex, Nm_CheckShutdown                **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00333
 * SRS_BSW_00359 SRS_Nm_00052 SRS_Nm_00045 SRS_Nm_02511 SRS_Nm_02514
 * SRS_Nm_02516 SRS_Nm_00150
 */
#if (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_RemoteSleepIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_053 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_REMOTESLEEPINDICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_054 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        /* Enter Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        /* Check if the channel has indicated local ECU ready to sleep */
        if (NM_NW_COMM_RELEASE == Nm_NetworkStatusFlag[networkIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
        {
          /* Set flag to indicate that local ECU and bus are ready to sleep */
          /* @Trace: Nm_SUD_API_055 */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_COMM_BUSNM_RELEASE;
        }
        /* else if channel has not indicated local ECU ready to sleep yet */
        else if (NM_NW_NO_RELEASE == Nm_NetworkStatusFlag[networkIdx])
        {
          /* Set flag to indicate that the bus ready to sleep */
          /* @Trace: Nm_SUD_API_056 */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_BUSNM_RELEASE;
        }
        else
        {
          /* No action */
        }
        /* Exit Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_057 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_REMOTESLEEPINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmNetworkHandle);
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
} /* End of Nm_RemoteSleepIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_RemoteSleepCancellation                          **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : Notification that the network management has        **
**                        detected that not all other nodes on the network    **
**                        are ready to enter Bus-Sleep Mode.                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig, Nm_NetworkStatusFlag,             **
**                        Nm_ClusterStatusFlag, Nm_SchMEnterFunc,             **
**                        Nm_SchMExitFunc                                     **
**                                                                            **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_02509 SRS_Nm_00150
 * SRS_Nm_02537 SRS_Nm_00045 SRS_Nm_02511 SRS_Nm_02514 SRS_Nm_02516
 */
#if (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_RemoteSleepCancellation(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_058 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_REMOTESLEEPCANCELLATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_059 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /*
         * If BusNm shall indicate the Remote Sleep Cancellation when
         * detect a node on a network that has not yet been released and
         * is still in 'network mode' starts requesting the network again,
         * then the coordinated shutdown shall be aborted
         */

        /* Get the index to the array Nm_ClusterInfo */
        /* @Trace: Nm_SUD_API_060*/
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */

        /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        /* Enter Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        /*
         * Check if Cluster Status is set to appropriated flag of indicating
         * the shutdown has been initiated
         */
        if ((NM_CLUSTER_SYNC_POINT_DELAY == Nm_ClusterStatusFlag[clusterIdx]) || /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
            (NM_CLUSTER_SHUTDOWN_READY == Nm_ClusterStatusFlag[clusterIdx]) ||
            (NM_CLUSTER_SHUTDOWN_STARTED == Nm_ClusterStatusFlag[clusterIdx]))
        {
          /* Change the status of the network to trigger shutdown abortion */
          /* @Trace: Nm_SUD_API_061 */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_ABORTION_TRIGGER; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
        }
        /* else if channel has indicated the bus ready to sleep */
        else if (NM_NW_BUSNM_RELEASE == Nm_NetworkStatusFlag[networkIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
        {
          /* Reset the status to initial value */
          /* @Trace: Nm_SUD_API_062 */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_NO_RELEASE;
        }
        /* if channel has indicated local ECU and bus ready to sleep yet */
        else if (NM_NW_COMM_BUSNM_RELEASE == Nm_NetworkStatusFlag[networkIdx])
        {
          /* Reset flag to indicate that local ECU is ready to sleep only */
          /* @Trace: Nm_SUD_API_063 */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_COMM_RELEASE;
        }
        else
        {
          /* No action */
        }
        /* Exit Data Protection */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_064 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_REMOTESLEEPCANCELLATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmNetworkHandle);
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
} /* End of Nm_RemoteSleepCancellation() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_SynchronizationPoint                             **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Notification to the NM Coordinator functionality    **
**                        that this is a suitable point in time to initiate   **
**                        the coordinated shutdown on.                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig, Nm_SyncPointIndFlag               **
**                                                                            **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_02511 SRS_Nm_02514
 * SRS_Nm_02516 SRS_Nm_00045
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_SynchronizationPoint(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_065 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_SYNCHRONIZATIONPOINT_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_066 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /*
       * Check if this network belongs to NM Coordination cluster and
       * is set to synchronizing network
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) && /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          (TRUE == Nm_PtrChannelConfig[networkIdx].SynchronizingNetwork))
      #else
      if ((NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex) &&
          (TRUE == Nm_ChannelConfig[networkIdx].SynchronizingNetwork))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Get the index to the array Nm_ClusterInfo */
        /* @Trace: Nm_SUD_API_067 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        /* Check if Cluster Status is waiting the Sync Point Indication */
        if (NM_CLUSTER_SYNC_POINT_DELAY == Nm_ClusterStatusFlag[clusterIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
        {
          /*
           * Clear the flag of waiting the Sync Point Indication,
           * then the coordinator can initiate the coordinated shutdown
           */
           /* @Trace: Nm_SUD_API_068 */
          Nm_SyncPointIndFlag[clusterIdx] = FALSE;
        }
        else
        {
          /* No action */
        }
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_069 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                             NM_SYNCHRONIZATIONPOINT_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmNetworkHandle);
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
} /* End of Nm_SynchronizationPoint() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_CoordReadyToSleepIndication                      **
**                                                                            **
** Service ID           : 0x1e                                                **
**                                                                            **
** Description          : Sets an indication, when the NM Coordinator         **
**                        Sleep Ready bit in the Control  Bit Vector is set   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle : Identification of the NM-channel  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_ChannelConfig,             **
**                        Nm_ClusterStatusFlag, Nm_SchMEnterFunc,             **
**                        Nm_SchMExitFunc                                     **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_02535 SRS_Nm_00150
 */
#if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_CoordReadyToSleepIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmChannelHandle)
{
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  /* For storing the starting index to the channel array */
  uint8 startIdx;
  /* For storing the index of first channel in the cluster */
  uint8 startChannelIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_070 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                               NM_COORDREADYTOSLEEPINDICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_071 */
    getIndex = Nm_GetChannelIndex(nmChannelHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* @Trace: Nm_SUD_API_072 */
        /* Get the index to the array Nm_ClusterInfo */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        /* polyspace-begin RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        /* Get a start mapping index to the array Nm_ChannelArray */
        startIdx = Nm_PtrClusterInfo[clusterIdx].ChnlStartIndex;
        /* Get the index of the first channel in the cluster */
        startChannelIdx = Nm_PtrChannelArray[startIdx];
        /* polyspace-end RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        /* Enter Data Protection */
        /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        /* Set the Cluster Status to initiate the shutdown */
        Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_READY; /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
        /* Exit Data Protection */
        Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        /* Get a start mapping index to the array Nm_ChannelArray */
        startIdx = Nm_ClusterInfo[clusterIdx].ChnlStartIndex;
        /* Get the index of the first channel in the cluster */
        startChannelIdx = Nm_ChannelArray[startIdx];
        /* Enter Data Protection */
        Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
        /* Set the Cluster Status to initiate the shutdown */
        Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_READY;
        /* Exit Data Protection */
        Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_073 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                      NM_COORDREADYTOSLEEPINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmChannelHandle);
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
} /* End of Nm_CoordReadyToSleepIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_CoordReadyToSleepCancellation                    **
**                                                                            **
** Service ID           : 0x1f                                                **
**                                                                            **
** Description          : Cancels an indication, when the NM Coordinator      **
**                        Sleep Ready bit in the Control  Bit Vector is set   **
**                        back to 0                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle : Identification of the NM-channel  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_ChannelConfig,             **
**                        Nm_ClusterStatusFlag, Nm_SchMEnterFunc,             **
**                        Nm_SchMExitFunc                                     **
**                        Function(s) invoked : Det_ReportError,              **
**                        Nm_GetChannelIndex                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00333
 * SRS_BSW_00359 SRS_Nm_00150 SRS_Nm_02535 SRS_Nm_02537
 */
#if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_CoordReadyToSleepCancellation(
  VAR(NetworkHandleType, NM_APPL_DATA) nmChannelHandle)
{
  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_074 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_COORDREADYTOSLEEPCANCELLATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_075 */
    getIndex = Nm_GetChannelIndex(nmChannelHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if this network belongs to NM Coordination cluster */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NM_INVALID_IDX != Nm_PtrChannelConfig[networkIdx].ClusterListIndex) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NM_INVALID_IDX != Nm_ChannelConfig[networkIdx].ClusterListIndex)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Get the index to the array Nm_ClusterInfo */
        /* @Trace: Nm_SUD_API_076 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
        #else
        clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        /* Check if Cluster Status is set to appropriated flag of indicating
            the shutdown has been initiated */
        if ((NM_CLUSTER_SYNC_POINT_DELAY == Nm_ClusterStatusFlag[clusterIdx]) || /* polyspace RTE:OBAI [Not a defect:Low] "This clusterIdx is manually checked and has no impact." */
            (NM_CLUSTER_SHUTDOWN_READY == Nm_ClusterStatusFlag[clusterIdx]) ||
            (NM_CLUSTER_SHUTDOWN_STARTED == Nm_ClusterStatusFlag[clusterIdx]))
        {
          /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
          /* @Trace: Nm_SUD_API_077 */
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          /* Enter Data Protection */
          /* polyspace-begin RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr();
          /* Change the status of the network to trigger shutdown abortion */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_ABORTION_TRIGGER; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
          /* Exit Data Protection */
          Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr();
          /* polyspace-end RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          #else
          /* Enter Data Protection */
          Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
          /* Change the status of the network to trigger shutdown abortion */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_ABORTION_TRIGGER;
          /* Exit Data Protection */
          Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
          #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
          /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
        }
        else
        {
          /* No action */
        }
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_078 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                    NM_COORDREADYTOSLEEPCANCELLATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmChannelHandle);
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
} /* End of Nm_CoordReadyToSleepCancellation() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_PduRxIndication                                  **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : Notification form BusNm that a NM message has been  **
**                        received                                            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : This service function has to be called after the    **
**                        initialization of the respective bus interface.     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig                                    **
**                        Function(s) invoked : PduRxIndUserCallout,          **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_00150 SRS_Nm_AR_00004
 */
#if (NM_PDU_RX_INDICATION_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_PduRxIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  #if (NM_PDU_RX_IND_USER_CALLOUT == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_138 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_PDURXINDICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_139 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if the NmPduRxIndUserCallout is defined */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NULL_PTR != Nm_PtrChannelConfig[networkIdx].PduRxIndCalloutFuncPtr) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NULL_PTR != Nm_ChannelConfig[networkIdx].PduRxIndCalloutFuncPtr)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call the callout for OEM specific extensions */
        /* @Trace: Nm_SUD_API_140 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrChannelConfig[networkIdx].PduRxIndCalloutFuncPtr();
        #else
        Nm_ChannelConfig[networkIdx].PduRxIndCalloutFuncPtr();
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_141 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_PDURXINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmNetworkHandle);
  #endif /* (NM_PDU_RX_IND_USER_CALLOUT == STD_ON) */
} /* End of Nm_PduRxIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_PDU_RX_INDICATION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_StateChangeNotification                          **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : Notification that the state of the lower layer      **
**                        <BusNm> has changed.                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle : Identification of the NM-channel  **
**                        nmCurrentState  : Previous state of the NM-channel  **
**                        nmPreviousState : Previous state of the NM-channel  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig                                    **
**                        Function(s) invoked : Com_SendSignal,               **
**                        BswM_StateChangeNotification, Det_ReportError,      **
**                        Nm_GetChannelIndex, StateChangeIndUserCallout       **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_00051 SRS_Nm_00050
 * SRS_Nm_00150 SRS_Nm_AR_00004
 */
#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
/* This function is provided for OEM extensions */
FUNC(void, NM_CODE) Nm_StateChangeNotification(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
  VAR(Nm_StateType, NM_APPL_DATA) nmPreviousState,
  VAR(Nm_StateType, NM_APPL_DATA) nmCurrentState)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;
  /* For storing signalData of Network Management State */
  uint8 signalData;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_142 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_STATECHANGENOTIFICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_143 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if ((TRUE == getIndex))
    {
      /* Check if State Report is enable and StateReportSignal is defined */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if((TRUE == Nm_PtrChannelConfig[networkIdx].StateReportEnabled)) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if((TRUE == Nm_ChannelConfig[networkIdx].StateReportEnabled))
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Check if NM State transition from BusSleepMode to RepeatMessage */
        if ((NM_STATE_BUS_SLEEP == nmPreviousState) &&
            (NM_STATE_REPEAT_MESSAGE == nmCurrentState))
        {
          /* @Trace: Nm_SUD_API_144 */
          signalData = NM_RM_BSM;
        }
        /* Check if NM State transition
          from PrepareBusSleepMode to RepeatMessage */
        else if ((NM_STATE_PREPARE_BUS_SLEEP == nmPreviousState) &&
                (NM_STATE_REPEAT_MESSAGE == nmCurrentState))
        {
          /* @Trace: Nm_SUD_API_145 */
          signalData = NM_RM_PBSM;
        }
        /* Check if NM State transition from RepeatMessage to MormalOperation */
        else if ((NM_STATE_REPEAT_MESSAGE == nmPreviousState) &&
                (NM_STATE_NORMAL_OPERATION == nmCurrentState))
        {
          /* @Trace: Nm_SUD_API_146 */
          signalData = NM_NO_RM;
        }
        /* Check if NM State transition from ReadySleep to MormalOperation */
        else if ((NM_STATE_READY_SLEEP == nmPreviousState) &&
                (NM_STATE_NORMAL_OPERATION == nmCurrentState))
        {
          /* @Trace: Nm_SUD_API_147 */
          signalData = NM_NO_RS;
        }
        /* Check if NM State transition from ReadySleep to RepeatMessage */
        else if ((NM_STATE_READY_SLEEP == nmPreviousState) &&
                (NM_STATE_REPEAT_MESSAGE == nmCurrentState))
        {
          /* @Trace: Nm_SUD_API_148 */
          signalData = NM_RM_RS;
        }
        /* Check if NM State transition from MormalOperation to RepeatMessage */
        else if ((NM_STATE_NORMAL_OPERATION == nmPreviousState) &&
                (NM_STATE_REPEAT_MESSAGE == nmCurrentState))
        {
          /* @Trace: Nm_SUD_API_149 */
          signalData = NM_RM_NO;
        }
        /* NM State transition is not supported */
        else
        {
          /* @Trace: Nm_SUD_API_150 */
          signalData = (uint8)NM_ZERO;
        }
        /* Call Com_SendSignal() if the State transition is supported */
        /* @Trace: Nm_SUD_API_151 */
        if ((uint8)NM_ZERO != signalData)
        {
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          (void)Com_SendSignal(Nm_PtrChannelConfig[networkIdx].StateReportSignalId,
                              (P2CONST(void, AUTOMATIC, NM_VAR))&signalData);
          #else
          (void)Com_SendSignal(Nm_ChannelConfig[networkIdx].StateReportSignalId,
                              (P2CONST(void, AUTOMATIC, NM_VAR))&signalData);
          #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
        }
        else
        {

          /* No action */
        }

      }
      else
      {
        /* No action */
      }
      #if (NM_STATE_CHANGE_IND_USER_CALLOUT == STD_ON)
      /* Check if the State Change Notification Callout is defined */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NULL_PTR != Nm_PtrChannelConfig[networkIdx].StateChangeIndCalloutFuncPtr)
      #else
      if (NULL_PTR != Nm_ChannelConfig[networkIdx].StateChangeIndCalloutFuncPtr)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call the callout for OEM specific extensions */
        /* @Trace: Nm_SUD_API_152 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrChannelConfig[networkIdx].StateChangeIndCalloutFuncPtr(
                                               nmPreviousState, nmCurrentState);
        #else
        Nm_ChannelConfig[networkIdx].StateChangeIndCalloutFuncPtr(
                                               nmPreviousState, nmCurrentState);
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
      #endif /* (NM_STATE_CHANGE_IND_USER_CALLOUT == STD_ON) */
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_153 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_STATECHANGENOTIFICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
} /* End of Nm_StateChangeNotification() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_STATE_CHANGE_IND_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_RepeatMessageIndication                          **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : Service to indicate that an NM message with set     **
**                        Repeat Message Request Bit has been received.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig                                    **
**                        Function(s) invoked : RepeatMsgIndUserCallout,      **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_00153 SRS_Nm_AR_00004
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_RepeatMessageIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  #if (NM_REPEAT_MSG_IND_USER_CALLOUT == STD_ON)
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_154 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_REPEATMESSAGEINDICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_155 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if NmRepeatMsgIndUserCallout is defined */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NULL_PTR != Nm_PtrChannelConfig[networkIdx].RepeatMsgIndCalloutFuncPtr) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NULL_PTR != Nm_ChannelConfig[networkIdx].RepeatMsgIndCalloutFuncPtr)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call the callout for OEM specific extensions */
        /* @Trace: Nm_SUD_API_156 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrChannelConfig[networkIdx].RepeatMsgIndCalloutFuncPtr();
        #else
        Nm_ChannelConfig[networkIdx].RepeatMsgIndCalloutFuncPtr();
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_157 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_REPEATMESSAGEINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmNetworkHandle);
  #endif /* #if (NM_REPEAT_MSG_IND_USER_CALLOUT == STD_ON) */
} /* End of Nm_RepeatMessageIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_TxTimeoutException                               **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : Service to indicate that an attempt to send an NM   **
**                        message failed.                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus,                 **
**                        Nm_ChannelConfig                                    **
**                        Function(s) invoked : TxTimeoutExceptionUserCallout,**
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_AR_00004
 */
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_TxTimeoutException(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  #if (NM_TX_TIMEOUT_EXCEPTION_USER_CALLOUT == STD_ON)
 /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_158 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_TXTIMEOUTEXCEPTION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_159 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /* Check if the input channel is valid */
    if (TRUE == getIndex)
    {
      /* Check if NmTxTimeoutExceptionUserCallout is defined */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (NULL_PTR != \
                  Nm_PtrChannelConfig[networkIdx].TxTimeoutExceptionCalloutFuncPtr) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (NULL_PTR != \
                  Nm_ChannelConfig[networkIdx].TxTimeoutExceptionCalloutFuncPtr)
      #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      {
        /* Call the callout for OEM specific extensions */
        /* @Trace: Nm_SUD_API_160 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        Nm_PtrChannelConfig[networkIdx].TxTimeoutExceptionCalloutFuncPtr();
        #else
        Nm_ChannelConfig[networkIdx].TxTimeoutExceptionCalloutFuncPtr();
        #endif  /* NM_VARIANT_POSTBUID_SUPPORT == STD_ON */
      }
      else
      {
        /* No action */
      }
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_161 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_TXTIMEOUTEXCEPTION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  #else
  NM_UNUSED(nmNetworkHandle);
  #endif /* #if (NM_TX_TIMEOUT_EXCEPTION_USER_CALLOUT == STD_ON) */
} /* End of Nm_TxTimeoutException() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_CarWakeUpIndication                              **
**                                                                            **
** Service ID           : 0x1d                                                **
**                                                                            **
** Description          : This function is called by a <Bus>Nm to indicate    **
**                        reception of a CWU request.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle: Identification of the NM-channel   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_InitStatus                  **
**                        Function(s) invoked : CarWakeUpCallout,             **
**                        BswM_Nm_CarWakeUpIndication,                        **
**                        Det_ReportError, Nm_GetChannelIndex                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 SRS_BSW_00323
 * SRS_BSW_00369 SRS_BSW_00333 SRS_BSW_00359 SRS_Nm_02503 SRS_Nm_00150
 */
#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_CarWakeUpIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing result of getting channel index */
  boolean getIndex;

  #if (NM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the NM module has not initialized yet */
  if (NM_INIT != Nm_InitStatus)
  {
    /* Report error NM_E_UNINIT to DET */
    /* @Trace: Nm_SUD_API_162 */
    (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                          NM_CARWAKEUPINDICATION_SID, NM_E_UNINIT);
  }
  else
  #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel index from channel id */
    /* @Trace: Nm_SUD_API_163 */
    getIndex = Nm_GetChannelIndex(nmNetworkHandle, &networkIdx);
    /*
     * Check if the input channel is valid and
     * Nm_CarWakeUpIndFuncPtr is not null
     */
    if (TRUE == getIndex)
    {
      /*
       * Call Car Wake Up Indication function:
       * If NmCarWakeUpCallout is defined, Nm will call CarWakeUp User callout.
       * Otherwise, Nm will call BswM_Nm_CarWakeUpIndication.
       */
      /* @Trace: Nm_SUD_API_164 */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      Nm_PtrCarWakeUpIndFuncPtr(nmNetworkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
      #else
      Nm_CarWakeUpIndFuncPtr(nmNetworkHandle);
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    }
    else
    {
      #if (NM_DEV_ERROR_DETECT == STD_ON)
      /* Report error NM_E_INVALID_CHANNEL to DET */
      /* @Trace: Nm_SUD_API_165 */
      (void)Det_ReportError(NM_MODULE_ID, NM_INSTANCE_ID,
                            NM_CARWAKEUPINDICATION_SID, NM_E_INVALID_CHANNEL);
      #endif /* (NM_DEV_ERROR_DETECT == STD_ON) */
    }
    NM_UNUSED(networkIdx);
  }
} /* End of Nm_CarWakeUpIndication() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
