/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_IntFunc.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provides definition of Internal Functions:                    **
**              Nm_GetChannelIndex                                            **
**              Nm_CheckShutdown                                              **
**              Nm_DelayShutdown                                              **
**              Nm_StartShutdown                                              **
**              Nm_AbortShutdown                                              **
**              Nm_PerformShutdown                                            **
**              Nm_SetRequest                                                 **
**              Nm_CheckFlagIndicate                                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By           Description                          **
********************************************************************************
** 1.0.5      19-Feb-2024   DHKim        CP44-3592, CP44-3813, CP44-3884      **
** 1.0.4.0    21-Apr-2023   NamNT1       CP44-1709                            **
** 1.0.1.1    20-Jun-2022   SMKwon       CP44-105                             **
** 1.0.1      16-Mar-2022   LiemNT4      Implement support Post-Build and add **
**                                       comment polyspace                    **
** 1.0.0      04-Dec-2020   Autoever     Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of Internal functions header file */
#include "Nm_IntFunc.h"
/* Inclusion for Global Variables */
#include "Nm_Globals.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
static FUNC(void, NM_CODE) Nm_CheckFlagIndicate(
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) networkIdx);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_GetChannelIndex                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to get channel index from        **
**                        channel id.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : chnlId : Identification of the NM-channel           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ptrChnlIdx : Index in configuration channels array  **
**                                                                            **
** Return parameter     : TRUE  : If NM-channel is valid                      **
**                        FALSE : If NM-channel is invalid                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_ChannelIndexArray           **
**                                                                            **
**                        Function(s) Invoked : None                          **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, NM_CODE) Nm_GetChannelIndex(
  VAR(NetworkHandleType, NM_APPL_DATA) chnlId,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) ptrChnlIdx)
{
  /* For storing return value */
  boolean returnVal;

  /* Initiate return value to false */
  /* @Trace: Nm_SUD_API_174 */
  returnVal = FALSE;

  /* Check if channel Id is not larger than maximum of configured channel id */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  if ((NetworkHandleType)Nm_MaxChannelId >= chnlId)
  #else
  if ((NetworkHandleType)NM_MAX_CHANNEL_ID >= chnlId)
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  {
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Check if channel index is valid */
    if ((uint8)Nm_NumberOfChannel > Nm_PtrChannelIndexArray[chnlId]) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    {
      /* Get index of channel in Nm_ChannelConfig */
      *ptrChnlIdx = Nm_PtrChannelIndexArray[chnlId];
      /* Set return value to true */
      returnVal = TRUE;
    }
    else
    {
      /* No action */
    }
    #else
    /* Check if channel index is valid */
    if ((uint8)NM_NO_OF_CHANNELS > Nm_ChannelIndexArray[chnlId])
    {
      /* Get index of channel in Nm_ChannelConfig */
      /* @Trace: Nm_SUD_API_173 */
      *ptrChnlIdx = Nm_ChannelIndexArray[chnlId];
      /* Set return value to true */
      returnVal = TRUE;
    }
    else
    {
      /* No action */
    }
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  }
  else
  {
    /* No action */
  }
  return returnVal;
} /* End of Nm_GetChannelIndex() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_CheckShutdown                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to check if the network mode     **
**                        changed unexpectedly.                               **
**                        Then determine when all conditions for initiating   **
**                        the coordinated shutdown are met.                   **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : startIdx   : The starting index to the channel array**
**                        clusterIdx : Cluster Index in Cluster Array         **
**                        clusterSize: Number of channels belong to cluster   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_ChannelArray,              **
**                        Nm_ChannelConfig, Nm_SyncPointIndFlag,              **
**                        Nm_NetworkStatusFlag, Nm_ClusterStatusFlag,         **
**                        Nm_ModeChangeFlag,                                  **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc                   **
**                        Function(s) Invoked : <BusNm>_NetworkRelease        **
*******************************************************************************/
/* @Trace: SRS_Nm_02514 SRS_Nm_00047 SRS_Nm_02516
 * SRS_Nm_00044 SRS_Nm_AR_00001
 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_CheckShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* Counter variable */
  uint8 count;
  /* Flag of existing the whether synchronizing network in a cluster */
  boolean syncFlag;
  /* Flag of all network in a cluster are ready to sleep */
  boolean sleepFlag;
  /* Flag of all network in a cluster are coordinated actively */
  boolean activeFlag;
  /* For storing the index of first channel in the cluster */
  uint8 startChannelIdx;

  /* Reset to initial value */
  syncFlag = FALSE;
  sleepFlag = TRUE;
  activeFlag = TRUE;

  /* Get the index of the first channel in the cluster */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  startChannelIdx = Nm_PtrChannelArray[startIdx]; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  startChannelIdx = Nm_ChannelArray[startIdx];
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

  /* Loop for all networks belongs to cluster */
  for (count = (uint8)NM_ZERO; count < clusterSize; count++)
  {
    /* Get the next channel in the cluster */
    /* @Trace: Nm_SUD_API_183 */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    networkIdx = Nm_PtrChannelArray[startIdx + count];
    #else
    networkIdx = Nm_ChannelArray[startIdx + count];
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    
    /* Check if flag to indicate mode is changed unexpectedly is set to true */
    if (TRUE == Nm_ModeChangeFlag[networkIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
    {
      /* Reset flag to FALSE */
      /* @Trace: Nm_SUD_API_184 */
      Nm_ModeChangeFlag[networkIdx] = FALSE;
      Nm_CheckFlagIndicate(clusterIdx, networkIdx);
    }
    else
    {
      /* No action */
    }

    /* Check if cluster has only actively coordinated channels */
    if (TRUE == sleepFlag)
    {
      #if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
      /* Checking if existing Passively coordinated channel */
      /* @Trace: Nm_SUD_API_189 */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if (FALSE == Nm_PtrChannelConfig[networkIdx].ActiveCoordinator) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      if (FALSE == Nm_ChannelConfig[networkIdx].ActiveCoordinator)
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Set flag to true */
        activeFlag = FALSE;
      }
      else
      {
        /* No action */
      }
      #endif

      /*
       * Checking if existing Synchronizing Network and this network is still
       * considered as awake
       */
      /* @Trace: Nm_SUD_API_190 */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* Enter Data Protection */
      Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr();
      if ((TRUE == Nm_PtrChannelConfig[networkIdx].SynchronizingNetwork) &&
          (NM_NW_COMM_BUSNM_RELEASE == Nm_NetworkStatusFlag[networkIdx]))
      #else
      /* Enter Data Protection */
      Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
      if ((TRUE == Nm_ChannelConfig[networkIdx].SynchronizingNetwork) &&
          (NM_NW_COMM_BUSNM_RELEASE == Nm_NetworkStatusFlag[networkIdx]))
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* Set flag to true */
        syncFlag = TRUE;
      }
      else
      {
        /* No action */
      }

      /*
       * Checking if at least one network is neither ready to sleep nor
       * indicated "bus sleep"
       */
      /* @Trace: Nm_SUD_API_191 */
      if ((NM_NW_COMM_BUSNM_RELEASE != Nm_NetworkStatusFlag[networkIdx]) &&
          (NM_NW_SLEEP_INDICATED != Nm_NetworkStatusFlag[networkIdx]))
      {
        /* Set flag to true */
        sleepFlag = FALSE;
      }
      else
      {
        /* No action */
      }
      /* Exit Data Protection */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr();
      #else
      Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
      #endif 
    }
    else
    {
      /* No action */
    }
  }

  /*
   * Check if all network belongs to cluster are ready to sleep and
   * cluster contains all actively coordinated channels
   */
  if ((TRUE == sleepFlag) && (TRUE == activeFlag))
  {
    /* Enter Data Protection */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    /* Check if need to delay for the Synchronization Point Indication */
    if ((TRUE == syncFlag) && (TRUE == Nm_SyncPointIndFlag[clusterIdx]))
    {
      /* Set the Cluster Status to waiting the Sync Point Indication */
      /* @Trace: Nm_SUD_API_193 */
      Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SYNC_POINT_DELAY;
    }
    else
    {
      /* Set the Cluster Status to initiate the shutdown */
      /* @Trace: Nm_SUD_API_192*/
      Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_READY;
    }
    /* Exit Data Protection */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    #else
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  }
  else
  {
    /* No action */
  }
} /* End of Nm_CheckShutdown() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_DelayShutdown                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to check if a network that is    **
**                        configured as synchronizing network for this        **
**                        coordination cluster invoked                        **
**                        Nm_SynchronizationPoint().                          **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : startIdx   : The starting index to the channel array**
**                        clusterIdx : Cluster Index in Cluster Array         **
**                        clusterSize: Number of channels belong to cluster   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_ChannelArray,              **
**                        Nm_ChannelConfig, Nm_SyncPointIndFlag,              **
**                        Nm_NetworkStatusFlag, Nm_ClusterStatusFlag,         **
**                        Function(s) Invoked : None                          **
*******************************************************************************/
/* @Trace: SRS_Nm_00044 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_DelayShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* Counter variable */
  uint8 count;
  /* Flag of trigger shutdown abortion */
  boolean abortionFlag;
  /* For storing the index of first channel in the cluster */
  uint8 startChannelIdx;

  /* Set to initial value */
  abortionFlag = FALSE;
  count = (uint8)NM_ZERO;

  /* Get the index of the first channel in the cluster */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  startChannelIdx = Nm_PtrChannelArray[startIdx]; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  startChannelIdx = Nm_ChannelArray[startIdx];
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

  /* Loop for all networks belongs to cluster */
  while (count < clusterSize)
  {
    /* Get the next channel in the cluster */
    /* @Trace: Nm_SUD_API_194 */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Enter Data Protection */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr();
    networkIdx = Nm_PtrChannelArray[startIdx + count];
    #else
    /* Enter Data Protection */
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    networkIdx = Nm_ChannelArray[startIdx + count];
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    /* Check if Network Status is triggered shutdown abortion */
    if (NM_NW_ABORTION_TRIGGER == Nm_NetworkStatusFlag[networkIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
    {
      /* @Trace: Nm_SUD_API_195 */
      /* Set the Cluster Status to indicate the shutdown abortion */
      Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_ABORTED;
      /* Set flag of trigger shutdown abortion to true */
      abortionFlag = TRUE;
      /* Set counter to break the while-loop*/
      count = clusterSize;
    }
    else
    {
      /* Increase counter for next channel */
      count++;
    }
    /* Exit Data Protection */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr();
    #else
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  }
  /*
   * Check if there is no shutdown abortion triggered and
   * the Sync Point Indication has been occurred
   */
  if ((FALSE == abortionFlag) &&
      (FALSE == Nm_SyncPointIndFlag[clusterIdx]))
  {
    /* @Trace: Nm_SUD_API_196 */
    /*
     * Reset flag of waiting synchronizing point to true for when the
     * coordinated shutdown is evaluated again
     */
    Nm_SyncPointIndFlag[clusterIdx] = TRUE;

    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Enter Data Protection */
    /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* Set the Cluster Status to initiate the shutdown */
    Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_READY;
    /* Exit Data Protection */
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    #else
    /* Enter Data Protection */
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    /* Set the Cluster Status to initiate the shutdown */
    Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_READY;
    /* Exit Data Protection */
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  }
  else
  {
    /* No action */
  }
} /* End of Nm_DelayShutdown() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_StartShutdown                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to initiate the coordination     **
**                        shutdown such as initiate the shutdown delay timer  **
**                        and set the NMCoordinatorSleepReady bit to SET (1). **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : startIdx   : The starting index to the channel array**
**                        clusterIdx : Cluster Index in Cluster Array         **
**                        clusterSize: Number of channels belong to cluster   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_ChannelArray,              **
**                        Nm_ChannelConfig, Nm_ShutdownTimer,                 **
**                        Nm_ClusterStatusFlag, Nm_SchMEnterFunc,             **
**                        Nm_SchMExitFunc                                     **
**                        Function(s) Invoked : <BusNm>_SetSleepReadyBit      **
*******************************************************************************/
/* @Trace: SRS_Nm_00149 SRS_Nm_02516 SRS_Nm_02535 SWS_Nm_00261 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_StartShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* Counter variable */
  uint8 count;
  #if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
  /* For storing the channel Id in the channel config structure */
  NetworkHandleType chnlId;
  #endif
  /* Flag of trigger shutdown abortion */
  boolean abortionFlag;
  /* For storing the index of first channel in the cluster */
  uint8 startChannelIdx;

  /* Set to initial value */
  abortionFlag = FALSE;
  count = (uint8)NM_ZERO;

  /* Get the index of the first channel in the cluster */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  startChannelIdx = Nm_PtrChannelArray[startIdx]; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  startChannelIdx = Nm_ChannelArray[startIdx];
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

  /* Loop for all networks belongs to cluster */
  while (count < clusterSize)
  {
    /* Get the next channel in the cluster */
    /* @Trace: Nm_SUD_API_197 */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    networkIdx = Nm_PtrChannelArray[startIdx + count];
    /* Enter Data Protection */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr();
    #else
    networkIdx = Nm_ChannelArray[startIdx + count];
    /* Enter Data Protection */
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    /* Check if Network Status is triggered shutdown abortion */
    if (NM_NW_ABORTION_TRIGGER == Nm_NetworkStatusFlag[networkIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
    {
      /* @Trace: Nm_SUD_API_198 */
      /* Set the Cluster Status to indicate the shutdown abortion */
      Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_ABORTED;
      /* Set flag of trigger shutdown abortion to true */
      abortionFlag = TRUE;
      /* Set counter to break the while-loop */
      count = clusterSize;
    }
    else
    {
      #if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
      /*
       * Check if the channel is actively coordinated channel and
       * NmBusType is not set to NM_BUSNM_LOCALNM
       */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      if ((TRUE == Nm_PtrChannelConfig[networkIdx].ActiveCoordinator) && /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
          (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType))
      #else
      if ((TRUE == Nm_ChannelConfig[networkIdx].ActiveCoordinator) &&
          (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType))
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      {
        /* @Trace: Nm_SUD_API_199 */
        /* Get the Channel Id */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        chnlId = Nm_PtrChannelConfig[networkIdx].ChannelId;
        /* Set the NM Coordinator Sleep Ready bit to SET (1) */
        (void)Nm_PtrChannelConfig[networkIdx].SetSleepReadyBitFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                    chnlId, NM_SLEEP_BIT_SET);
        #else
        chnlId = Nm_ChannelConfig[networkIdx].ChannelId;
        /* Set the NM Coordinator Sleep Ready bit to SET (1) */
        (void)Nm_ChannelConfig[networkIdx].SetSleepReadyBitFuncPtr(
                                                    chnlId, NM_SLEEP_BIT_SET);
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      }
      else
      {
        /* No action */
      }
      #endif
      /* Set the shutdown delay timers */
      /* @Trace: Nm_SUD_API_200 */
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      Nm_ShutdownTimer[networkIdx] = \
                                    Nm_PtrChannelConfig[networkIdx].DelayTimerTick;
      #else
      Nm_ShutdownTimer[networkIdx] = \
                                    Nm_ChannelConfig[networkIdx].DelayTimerTick;
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      /* Increase counter for next channel */
      count++;
    }
    /* Exit Data Protection */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr();
    #else
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif 

  }
  /* Check if there is shutdown abortion occurred */
  if (FALSE == abortionFlag)
  {
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Enter Data Protection */
    /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* Set the Cluster Status to start the coordinated shutdown */
    Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_STARTED;
    /* Exit Data Protection */
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    #else
    /* @Trace: Nm_SUD_API_201 */
    /* Enter Data Protection */
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    /* Set the Cluster Status to start the coordinated shutdown */
    Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_STARTED;
    /* Exit Data Protection */
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  }
  else
  {
    /* No action */
  }
} /* End of Nm_StartShutdown() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_PerformShutdown                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to perform the coordinated       **
**                        shutdown. In case, Nm receives E_NOT_OK on a        **
**                        <BusNm>_NetworkRelease, the shutdown shall be       **
**                        immediately aborted.                                **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : startIdx   : The starting index to the channel array**
**                        clusterIdx : Cluster Index in Cluster Array         **
**                        clusterSize: Number of channels belong to cluster   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_ChannelArray,              **
**                        Nm_ChannelConfig, Nm_ShutdownTimer,                 **
**                        Nm_ClusterStatusFlag, Nm_NetworkStatusFlag,         **
**                        Nm_NetworkModeFlag,                                 **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc                   **
**                        Function(s) Invoked : <BusNm>_NetworkRelease,       **
**                        <BusNm>_RequestBusSynchronization,                  **
**                        ComM_Nm_BusSleepMode                                **
*******************************************************************************/
/* @Trace: SRS_Nm_02516 SRS_Nm_02537 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_PerformShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing the channel Id in the channel config structure */
  NetworkHandleType chnlId;
  /* Counter variable for all networks in a cluster */
  uint8 count;
  /* For counting the networks in cluster have indicated sleep */
  uint8 sleepCnt;
  /* For storing return value of <BusNm>_NetworkRelease() */
  Std_ReturnType returnVal;
  /* For storing the index of first channel in the cluster */
  uint8 startChannelIdx;

  /* Get the index of the first channel in the cluster */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  startChannelIdx = Nm_PtrChannelArray[startIdx]; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  startChannelIdx = Nm_ChannelArray[startIdx];
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

  sleepCnt = (uint8)NM_ZERO;
  count = (uint8)NM_ZERO;
  /* Loop for all networks belongs to cluster */
  while (count < clusterSize)
  {
    /* Get the next channel in the cluster */
    /* @Trace: Nm_SUD_API_202 */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    networkIdx = Nm_PtrChannelArray[startIdx + count];
    /* Enter Data Protection */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr();
    #else
    networkIdx = Nm_ChannelArray[startIdx + count];
    /* Enter Data Protection */
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

    /* Checking if this Network has been ready to sleep */
    if (NM_NW_COMM_BUSNM_RELEASE == Nm_NetworkStatusFlag[networkIdx]) /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */
    {
      /* Check if the Shutdown Delay Time is expired */
      if ((uint32)NM_ZERO == Nm_ShutdownTimer[networkIdx])
      {
        /* Get channel Id */
        /* @Trace: Nm_SUD_API_204 */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        chnlId = Nm_PtrChannelConfig[networkIdx].ChannelId; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
        #else
        chnlId = Nm_ChannelConfig[networkIdx].ChannelId;
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

        /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
        #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
        if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType)
        #else
        if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
        #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
        {
          #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
          #if (NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)
          /* Call <BusNm>_RequestBusSynchronization() */
          (void)Nm_PtrChannelConfig[networkIdx].RequestBusSyncFuncPtr(chnlId); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #endif  /* (NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON) */

          /* Call <BusNm>_NetworkRelease() */
          returnVal = \
                Nm_PtrChannelConfig[networkIdx].NetworkReleaseFuncPtr(chnlId); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
          #else
          #if (NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)
          /* Call <BusNm>_RequestBusSynchronization() */
          /* @Trace: Nm_SUD_API_205 */
          (void)Nm_ChannelConfig[networkIdx].RequestBusSyncFuncPtr(chnlId);
          #endif  /* (NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON) */

          /* Call <BusNm>_NetworkRelease() */
          /* @Trace: Nm_SUD_API_206 */
          returnVal = \
                Nm_ChannelConfig[networkIdx].NetworkReleaseFuncPtr(chnlId);
          #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

          /* Check if releasing bus is failed */
          if (E_NOT_OK == returnVal)
          {
            /* @Trace: Nm_SUD_API_208 */
            /* Set the Cluster Status to indicate the shutdown abortion */
            Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_ABORTED;
            /* Set counter for breaking while-loop */
            count = clusterSize - 1;
          }
          else
          {
            /* @Trace: Nm_SUD_API_207 */
            /* Change the Network Status as BusNm has been released by Nm */
            Nm_NetworkStatusFlag[networkIdx] = NM_NW_RELEASED;
           }
        }
        else
        {
          /* @Trace: Nm_SUD_API_209 */
          /* Inform to ComM by calling ComM_Nm_BusSleepMode() */
          ComM_Nm_BusSleepMode(chnlId);
          /*
           * Set the Network Status to indicate the LocalNm has been entered
           * "bus-sleep mode"
           */
          Nm_NetworkStatusFlag[networkIdx] = NM_NW_SLEEP_INDICATED;
          /* Set Network Mode flag to NM_MODE_BUS_SLEEP */
          Nm_NetworkModeFlag[networkIdx] = NM_MODE_BUS_SLEEP;
        }
      }
      else
      {
        /* Descrease Shutdown Delay Timer */
        /* @Trace: Nm_SUD_API_203 */
        Nm_ShutdownTimer[networkIdx]--;
      }
    }
    /* else if network has indicated sleep */
    /* @Trace: Nm_SUD_API_210 */
    else if (NM_NW_SLEEP_INDICATED == Nm_NetworkStatusFlag[networkIdx])
    {
      /* Increase the counter when network has indicated sleep */
      sleepCnt++;
    }
    /* else if Network Status is triggered shutdown abortion */
    else if (NM_NW_ABORTION_TRIGGER == Nm_NetworkStatusFlag[networkIdx])
    {
      /* Set the Cluster Status to indicate the shutdown abortion */
      Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SHUTDOWN_ABORTED;

      /* Set counter for breaking while-loop */
      count = clusterSize - 1;
    }
    else
    {
      /* No action */
    }
    /* Exit Data Protection */
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr();
    #else
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

    /* Increase counter to the next channel */
    count++;
  }

  /* Check if all the networks belong to same cluster have indicated sleep */
  if (sleepCnt == clusterSize)
  {
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Enter Data Protection */
    /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* Set the Cluster Status to indicate the shutdown has been finished */
    Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SLEEP;
    /* Exit Data Protection */
    Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
    #else
    /* @Trace: Nm_SUD_API_212 */
    /* Enter Data Protection */
    Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
    /* Set the Cluster Status to indicate the shutdown has been finished */
    Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_SLEEP;
    /* Exit Data Protection */
    Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  }
  else
  {
    /* No action */
  }
} /* End of Nm_PerformShutdown() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_AbortShutdown                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to keep all the networks in a    **
**                        particular cluster requested.                       **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : startIdx   : The starting index to the channel array**
**                        clusterIdx : Cluster Index in Cluster Array         **
**                        clusterSize: Number of channels belong to cluster   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_ChannelArray,              **
**                        Nm_ChannelConfig, Nm_ShutdownTimer,                 **
**                        Nm_NetworkStatusFlag, Nm_ClusterStatusFlag,         **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc                   **
**                        Function(s) Invoked : <BusNm>_SetSleepReadyBit,     **
**                        ComM_Nm_NetworkMode, ComM_Nm_RestartIndication,     **
**                        <BusNm>_NetworkRequest                              **
*******************************************************************************/
/* @Trace: SRS_Nm_02516 SRS_Nm_02535 SRS_Nm_02537 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_AbortShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize)
{
  /* For storing the index to the channel config structure */
  uint8 networkIdx;
  /* For storing the channel Id in the channel config structure */
  NetworkHandleType chnlId;
  /* Counter variable */
  uint8 count;
  /* For storing temporal return value */
  Std_ReturnType returnVal;
  /* For storing the index of first channel in the cluster */
  uint8 startChannelIdx;

  /* Get the index of the first channel in the cluster */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  startChannelIdx = Nm_PtrChannelArray[startIdx]; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  startChannelIdx = Nm_ChannelArray[startIdx];
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

  /* Loop for all networks belong to same cluster */
  for (count = (uint8)NM_ZERO; count < clusterSize; count++)
  {
    /* @Trace: Nm_SUD_API_213 */    
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Get the next channel in the cluster */
    networkIdx = Nm_PtrChannelArray[startIdx + count];
    /* Get the Channel Id */
    chnlId = Nm_PtrChannelConfig[networkIdx].ChannelId; /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
    #else
    /* Get the next channel in the cluster */
    networkIdx = Nm_ChannelArray[startIdx + count];
    /* Get the Channel Id */
    chnlId = Nm_ChannelConfig[networkIdx].ChannelId;
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    
    #if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
    
    #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /*
     * Check if the channel is actively coordinated channel and
     * NmBusType is not set to NM_BUSNM_LOCALNM
     */
    /* @Trace: Nm_SUD_API_214 */
    if ((TRUE == Nm_PtrChannelConfig[networkIdx].ActiveCoordinator) &&
        (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType))
    {
      /* Set the NM Coordinator Sleep Ready bit to RESET (0) */
      (void)Nm_PtrChannelConfig[networkIdx].SetSleepReadyBitFuncPtr( /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
                                                chnlId, NM_SLEEP_BIT_RESET);
    }
    else
    {
      /* No action */
    }
    #else
    /*
     * Check if the channel is actively coordinated channel and
     * NmBusType is not set to NM_BUSNM_LOCALNM
     */
    if ((TRUE == Nm_ChannelConfig[networkIdx].ActiveCoordinator) &&
        (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType))
    {
      /* Set the NM Coordinator Sleep Ready bit to RESET (0) */
      (void)Nm_ChannelConfig[networkIdx].SetSleepReadyBitFuncPtr(
                                                chnlId, NM_SLEEP_BIT_RESET);
    }
    else
    {
      /* No action */
    }
    #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    #endif /* (NM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

    /* Reset the shutdown delay timers to zero */
    /* @Trace: Nm_SUD_API_215 */
    Nm_ShutdownTimer[networkIdx] = (uint32)NM_ZERO; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */

    /* Check if this network has not indicated "bus sleep" */
    /* @Trace: Nm_SUD_API_216 */
    if (NM_MODE_BUS_SLEEP != Nm_NetworkModeFlag[networkIdx]) 
    {
      /* Initiate the return value to E_OK */
      returnVal = E_OK;
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* Check if BusNmType is not set to NM_BUSNM_LOCALNM */
      if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType)
      {
        /* Re-request the network from <BusNm> */
        returnVal = \
                  Nm_PtrChannelConfig[networkIdx].NetworkRequestFuncPtr(chnlId); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
      }
      #else
      /* Check if BusNmType is not set to NM_BUSNM_LOCALNM */
      if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
      {
        /* Re-request the network from <BusNm> */
        /* @Trace: Nm_SUD_API_218 */
        returnVal = \
                  Nm_ChannelConfig[networkIdx].NetworkRequestFuncPtr(chnlId);
      }
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      else
      {
        /* Call ComM_Nm_NetworkMode() */
        /* @Trace: Nm_SUD_API_217 */
        ComM_Nm_NetworkMode(chnlId);
      }

      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
      Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      #else
      /* Enter Data Protection */
      Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
      /* Check if requesting network is failed */
      if (E_NOT_OK == returnVal)
      {
        /* Change the status of the network to be not considered awake */
        /* @Trace: Nm_SUD_API_220 */
        Nm_NetworkStatusFlag[networkIdx] = NM_NW_SLEEP_INDICATED;
      }
      else
      {
        /* Change the status of the network to be considered awake */
        /* @Trace: Nm_SUD_API_219 */
        Nm_NetworkStatusFlag[networkIdx] = NM_NW_NO_RELEASE;
      }
      #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* Exit Data Protection */
      Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
      /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
      #else
      /* Exit Data Protection */
      Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
      #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
    }
    /* This network has already indicated "bus sleep" */
    else
    {
      /* Call ComM_Nm_RestartIndication() */
      /* @Trace: Nm_SUD_API_221 */
      ComM_Nm_RestartIndication(chnlId);
    }
  }

  /* @Trace: Nm_SUD_API_222 */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Enter Data Protection */
  /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
  Nm_PtrSchMEnterFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  /* Change the cluster state to indicate that the cluster is now awake */
  Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_AWAKE;
  /* Exit Data Protection */
  Nm_PtrSchMExitFunc[startChannelIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
  #else
  /* Enter Data Protection */
  Nm_SchMEnterFunc[startChannelIdx].SchMFuncPtr();
  /* Change the cluster state to indicate that the cluster is now awake */
  Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_AWAKE;
  /* Exit Data Protection */
  Nm_SchMExitFunc[startChannelIdx].SchMFuncPtr();
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
} /* End of Nm_AbortShutdown() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_SetRequest                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : In case a network is part of a coordinated cluster, **
**                        this API is called to forward a call of             **
**                        <BusNm>_NetworkRequest to the lower layer if        **
**                        BusNmType is not set to NM_BUSNM_LOCALNM to keep    **
**                        netowrk as requested. If the shutdown is aborted,   **
**                        the entire cluster will be kept requested.          **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : networkHandle : Identification of the NM-channel    **
**                        networkIdx : Index in configuration channels array  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_ComMRequestFlag,           **
**                        Nm_ChannelConfig, Nm_NetworkStatusFlag,             **
**                        Nm_ClusterStatusFlag, Nm_NetworkModeFlag,           **
**                        Nm_SchMEnterFunc, Nm_SchMExitFunc                   **
**                                                                            **
**                        Function(s) Invoked : <BusNm>_NetworkRequest,       **
**                        ComM_Nm_NetworkMode                                 **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Nm_02536 SRS_Nm_02537 SRS_Nm_AR_00002 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_SetRequest(
  VAR(NetworkHandleType, NM_APPL_DATA) networkHandle,
  VAR(uint8, NM_APPL_DATA) networkIdx)
{
  /* For storing the index to the Cluster List structure */
  uint8 clusterIdx;
  /* For storing return value */
  Std_ReturnType returnVal;

  /* Set return value to E_OK */
  returnVal = E_OK;

  /* Set the flag of Request-By-ComM to TRUE */
  /* @Trace: Nm_SUD_API_180 */
  Nm_ComMRequestFlag[networkIdx] = TRUE; /* polyspace RTE:OBAI [Not a defect:Low] "This networkIdx is manually checked and has no impact." */

  /* @Trace: Nm_SUD_API_176 */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
  if (NM_BUSNM_LOCALNM != Nm_PtrChannelConfig[networkIdx].BusType)
  {
    /* Forward a call of <BusNm>_NetworkRequest() */
    returnVal = \
              Nm_PtrChannelConfig[networkIdx].NetworkRequestFuncPtr(networkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
  }
  #else
  /* Check if the NmBusType is not configured to NM_BUSNM_LOCALNM */
  if (NM_BUSNM_LOCALNM != Nm_ChannelConfig[networkIdx].BusType)
  {
    /* Forward a call of <BusNm>_NetworkRequest() */
    returnVal = \
              Nm_ChannelConfig[networkIdx].NetworkRequestFuncPtr(networkHandle); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by Tool Generator and checked manually and has  no impact." */
  }
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  else
  {
    /* @Trace: Nm_SUD_API_175 */
    /* Set Network Mode flag to NM_MODE_NETWORK */
    Nm_NetworkModeFlag[networkIdx] = NM_MODE_NETWORK;
    /* Call ComM_Nm_NetworkMode() */
    ComM_Nm_NetworkMode(networkHandle);
  }

  /* Get the index to the array Nm_ClusterInfo */
  /* @Trace: Nm_SUD_API_177 */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  clusterIdx = Nm_PtrChannelConfig[networkIdx].ClusterListIndex;
  /* Enter Data Protection */
  Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr();
  #else
  clusterIdx = Nm_ChannelConfig[networkIdx].ClusterListIndex;
  /* Enter Data Protection */
  Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  /*
   * Check if Cluster Status is set to
   * appropriated flag of indicating shutdown
   */
  /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "This clusterIdx is manually checked and has no impact." */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "This clusterIdx is manually checked and has no impact." */
  if ((NM_CLUSTER_SYNC_POINT_DELAY == Nm_ClusterStatusFlag[clusterIdx]) ||
      (NM_CLUSTER_SHUTDOWN_READY == Nm_ClusterStatusFlag[clusterIdx]) ||
      (NM_CLUSTER_SHUTDOWN_STARTED == Nm_ClusterStatusFlag[clusterIdx]))
  {
    /* @Trace: Nm_SUD_API_178 */
    /* Change the status of the network to trigger shutdown abortion */
    Nm_NetworkStatusFlag[networkIdx] = NM_NW_ABORTION_TRIGGER;
  }
  /* else if requesting network is successful */
  else if (E_OK == returnVal)
  {
    /* @Trace: Nm_SUD_API_179 */
    /* Change the status of the network to be considered awake */
    Nm_NetworkStatusFlag[networkIdx] = NM_NW_NO_RELEASE;

    /* Check if Cluster Status is sleep */
    if (NM_CLUSTER_SLEEP == Nm_ClusterStatusFlag[clusterIdx])
    {
      /* @Trace: Nm_SUD_API_181 */
      /* Set cluster status to not considered sleep */
      Nm_ClusterStatusFlag[clusterIdx] = NM_CLUSTER_AWAKE;
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
  /* Exit Data Protection */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr();
  #else
  Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
  
  /* @Trace: Nm_SUD_API_182 */
  return returnVal;
} /* End of Nm_SetRequest() */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Nm_CheckFlagIndicate                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Nm_CheckShutdown() that Check if    **
**                        flag to indicate mode is changed                    **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : None                                                **
**                                                                            **
** Input Parameters     : startIdx   : The starting index to the channel array**
**                        networkIdx : Cluster Index in network Array         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NM_COORDINATOR_SUPPORT_ENABLED == STD_ON            **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_PtrChannelConfig,          **
**                        Nm_ChannelConfig, Nm_PtrSchMEnterFunc               **
**                        Nm_SyncPointIndFlag, Nm_NetworkStatusFlag           **
**                                                                            **
**                        Function(s) Invoked : NetworkReleaseFuncPtr,        **
*******************************************************************************/
/* @Trace: SRS_Nm_02516 SRS_Nm_02537 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, NM_CODE) Nm_CheckFlagIndicate(
	VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) networkIdx)
{
  /* For storing the channel Id in the channel config structure */
  NetworkHandleType chnlId;

  /* Check if this network is synchronizing */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  if (TRUE == Nm_PtrChannelConfig[networkIdx].SynchronizingNetwork) /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  if (TRUE == Nm_ChannelConfig[networkIdx].SynchronizingNetwork)
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  {
    /* Set Flag of waiting Synchronization Point to false */
    /* @Trace: Nm_SUD_API_185 */
    Nm_SyncPointIndFlag[clusterIdx] = FALSE;
  }
  else
  {
    /* No action */
  }

  /* Enter Data Protection */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* polyspace-begin RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
  Nm_PtrSchMEnterFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  #else
  Nm_SchMEnterFunc[networkIdx].SchMFuncPtr();
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
  /* Check if the channel has indicated local ECU ready to sleep */
  if (NM_NW_COMM_RELEASE == Nm_NetworkStatusFlag[networkIdx])
  {
    /* Set flag to indicate that local ECU and bus are ready to sleep */
    /* @Trace: Nm_SUD_API_186 */
    Nm_NetworkStatusFlag[networkIdx] = NM_NW_COMM_BUSNM_RELEASE;
  }
  /* else if channel has not indicated local ECU ready to sleep yet */
  else if (NM_NW_NO_RELEASE == Nm_NetworkStatusFlag[networkIdx])
  {
    /* Set flag to indicate that the bus ready to sleep */
    /* @Trace: Nm_SUD_API_187 */
    Nm_NetworkStatusFlag[networkIdx] = NM_NW_BUSNM_RELEASE;
  }
  else
  {
    /* No action */
  }
  /* Get Channel ID belongs to cluster */
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Exit Data Protection */
  Nm_PtrSchMExitFunc[networkIdx].SchMFuncPtr(); /* polyspace RTE:IDP [Not a defect:Low] "This pointer will not outside since checked manually. It has no impact." */
  /* polyspace-end RTE:COR [Not a defect:Low] "This function pointer SchMFuncPtr will be generated by the Generator and checked manually. It has no impact." */
  chnlId = Nm_PtrChannelConfig[networkIdx].ChannelId;
  /* Call <BusNm>_NetworkRelease for this network */
  (void)Nm_PtrChannelConfig[networkIdx].NetworkReleaseFuncPtr(chnlId); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
  #else
  /* @Trace: Nm_SUD_API_188 */
  /* Exit Data Protection */
  Nm_SchMExitFunc[networkIdx].SchMFuncPtr();
  chnlId = Nm_ChannelConfig[networkIdx].ChannelId;
  /* Call <BusNm>_NetworkRelease for this network */
  (void)Nm_ChannelConfig[networkIdx].NetworkReleaseFuncPtr(chnlId); /* polyspace RTE:COR [Not a defect:Low] "This function pointer will be generated by the Generator and checked manually. It has no impact." */
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
}
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
