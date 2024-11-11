/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_IntTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provides Type Definitions used within the module              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.0.3      16-Dec-2022   NamNT1         BUGCLASSIC-385, CP44-1325          **
** 1.0.2      31-Oct-2022   NamNT1         CP44-925                           **
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.1      16-Mar-2022   LiemNT4        Implement support Post-Build       **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

#ifndef NM_INTTYPES_H
#define NM_INTTYPES_H

/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/
#include "Std_Types.h"
#include "Nm_Cfg.h"
#include "SchM_Nm.h"
#include "ComStack_Types.h"

#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
/* Inclusion for using Com_SignalIdType and Com_SendSignal() */
/* @Trace: Nm_SUD_DATATYPE_003 */
#include "Com.h"
#endif
#include "NmStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define NM_INTTYPES_AR_RELEASE_MAJOR_VERSION        (0x04u)
#define NM_INTTYPES_AR_RELEASE_MINOR_VERSION        (0x04u)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Structure definition for each Nm Channel */
/* @Trace: Nm_SUD_DATATYPE_008 */
typedef struct
{
  /* Function pointer to <BusNm>_PassiveStartUp() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, PassiveStartUpFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

  /* Function pointer to <BusNm>_NetworkRequest() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, NetworkRequestFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

  /* Function pointer to <BusNm>_NetworkRelease() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, NetworkReleaseFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

  #if (NM_COM_CONTROL_ENABLED == STD_ON)
  /* Function pointer to <BusNm>_DisableCommunication() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, DisableCommunicationFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

  /* Function pointer to <BusNm>_EnableCommunication() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, EnableCommunicationFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);
  #endif  /* (NM_COM_CONTROL_ENABLED == STD_ON) */

  #if (NM_USER_DATA_ENABLED == STD_ON)
  /* Function pointer to <BusNm>_SetUserData() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, SetUserDataFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
    P2CONST(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr);

   /* Function pointer to <BusNm>_GetUserData() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, GetUserDataFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
    P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr);
  #endif  /* (NM_USER_DATA_ENABLED == STD_ON) */

  /* Function pointer to <BusNm>_GetPduData() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, GetPduDataFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
    P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

  /* Function pointer to <BusNm>_RepeatMessageRequest() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, RepeatMessageRequestFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

  /* Function pointer to <BusNm>_GetNodeIdentifier() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, GetNodeIdentifierFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
    P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

  /* Function pointer to <BusNm>_GetLocalNodeIdentifier() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, GetLocalNodeIdentifierFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
    P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

  #if (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
  /* Function pointer to <BusNm>_CheckRemoteSleepIndication() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, CheckRemoteSleepIndFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
    P2VAR(boolean, AUTOMATIC, NM_APPL_DATA) nmRemoteSleepIndPtr);
  #endif  /* (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON) */

  /* Function pointer to <BusNm>_GetState() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, GetStateFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
    P2VAR(Nm_StateType, AUTOMATIC, NM_APPL_DATA) nmStatePtr,
    P2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_DATA) nmModePtr);

  #if (NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)
  /* Function pointer to <BusNm>_RequestBusSynchronization() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, RequestBusSyncFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);
  #endif  /* (NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON) */

  #if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
  /* Function pointer to <BusNm>_SetSleepReadyBit() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, SetSleepReadyBitFuncPtr)(
    VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
    VAR(boolean, NM_APPL_DATA) nmSleepReadyBit);
  #endif  /* (NM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

  #if ((NM_STATE_CHANGE_IND_ENABLED == STD_ON) && \
       (NM_STATE_CHANGE_IND_USER_CALLOUT == STD_ON))
  /* Function pointer to State Change Notification User Callout */
  P2FUNC(void, NM_APPL_CODE, StateChangeIndCalloutFuncPtr)(
    VAR(Nm_StateType, NM_APPL_DATA) nmPreviousState,
    VAR(Nm_StateType, NM_APPL_DATA) nmCurrentState);
  #endif  /* ((NM_STATE_CHANGE_IND_ENABLED == STD_ON) && \
              (NM_STATE_CHANGE_IND_USER_CALLOUT == STD_ON)) */

  #if ((NM_PDU_RX_INDICATION_ENABLED == STD_ON) && \
       (NM_PDU_RX_IND_USER_CALLOUT == STD_ON))
  /* Function pointer to PDU Rx Indication User Callout */
  P2FUNC(void, NM_APPL_CODE, PduRxIndCalloutFuncPtr)(void);
  #endif  /* ((NM_PDU_RX_INDICATION_ENABLED == STD_ON) && \
              (NM_PDU_RX_IND_USER_CALLOUT == STD_ON)) */

  #if (NM_REPEAT_MSG_IND_USER_CALLOUT == STD_ON)
  /* Function pointer to Repeat Message Indication User Callout */
  P2FUNC(void, NM_APPL_CODE, RepeatMsgIndCalloutFuncPtr)(void);
  #endif  /* (NM_REPEAT_MSG_IND_USER_CALLOUT == STD_ON) */

  #if (NM_TX_TIMEOUT_EXCEPTION_USER_CALLOUT == STD_ON)
  /* Function pointer to Tx Timeout Exception User Callout */
  P2FUNC(void, NM_APPL_CODE, TxTimeoutExceptionCalloutFuncPtr)(void);
  #endif  /* (NM_TX_TIMEOUT_EXCEPTION_USER_CALLOUT == STD_ON) */

  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /*
   * Specifies Shutdown Delay Timer of NM channel in calling period
   * the Main Function
   */
  uint32 DelayTimerTick;
  #endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

  #if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
  /* Specifies ComSignal Id for State Report configuration */
  Com_SignalIdType StateReportSignalId;

  /* Indicates if the NMS shall be set for the corresponding network */
  boolean StateReportEnabled;
  #endif  /* (NM_STATE_CHANGE_IND_ENABLED == STD_ON) */

  #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  #if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
  /* Indicates whether a NM channel will be coordinated actively or passively */
  boolean ActiveCoordinator;
  #endif  /* (NM_COORDINATOR_SYNC_SUPPORT == STD_ON) */
  /*
   * Indicates if the sleep of this network can be absolutely decided
   * by the local node only
   */
  boolean ChannelSleepMaster;

  /* Indicates whether this network is a synchronizing network */
  boolean SynchronizingNetwork;

  /* Specifies index of cluster a NM channel belongs in the array of clusters */
  uint8 ClusterListIndex;

  /* Specifies the NM channel Identifier */
  NetworkHandleType ChannelId;
  #endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */
  /*
   * Indicates whether on a NM channel user data is accessed via Com signals
   * or by SetUserData API
   */
  boolean ComUserDataSupport;

  /* Indicates whether a NM channel is active or passive */
  boolean PassiveModeEnabled;

  /* Specifies the Bus NM Type */
  Nm_BusNmType BusType;
} Nm_ChannelConfigType;

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* Structure definition for Exclusive Area Protection */
/* @Trace: Nm_SUD_DATATYPE_010 */
typedef struct
{
  /* Pointer to SchM Enter/Exit function */
  P2FUNC(void, NM_APPL_CODE, SchMFuncPtr)(void);
} Nm_SchMFuncType;
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* Structure definition for specific information of each cluster */
/* @Trace: Nm_SUD_DATATYPE_009 */
typedef struct
{
  /* Index of first channel belongs to cluster in channel array */
  uint8 ChnlStartIndex;
  /* Number of channels are configured which belong to cluster */
  uint8 Size;
} Nm_ClusterInfoType;
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/* @Trace: SRS_BSW_00414 Nm_SUD_DATATYPE_011 */
/* Configuration data structure of the Nm module */
typedef struct
{
  #if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* Pointer to array Nm_ChannelConfig in Post-Build */
    P2CONST(Nm_ChannelConfigType, AUTOMATIC, NM_CONFIG_DATA) ptrNm_ChannelConfig;

    /* Pointer to array Nm_ChannelIndexArray in Post-Build */
    P2CONST(uint8, AUTOMATIC, NM_CONFIG_DATA) ptrNm_ChannelIndexArray;

    #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Pointer to array Nm_ChannelArray in Post-Build */
    P2CONST(uint8, AUTOMATIC, NM_CONFIG_DATA) ptrNm_ChannelArray;
    
    /* Pointer to array Nm_ClusterInfo in Post-Build */
    P2CONST(Nm_ClusterInfoType, AUTOMATIC, NM_CONFIG_DATA) ptrNm_ClusterInfo;

    /* Pointer to array Nm_SchMEnterFunc in Post-Build */
    P2CONST(Nm_SchMFuncType, AUTOMATIC, NM_CONFIG_DATA) ptrNm_SchMEnterFunc;

    /* Pointer to array Nm_SchMExitFunc in Post-Build */
    P2CONST(Nm_SchMFuncType, AUTOMATIC, NM_CONFIG_DATA) ptrNm_SchMExitFunc;
    #endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

    #if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
    /* Pointer to function pointer Nm_CarWakeUpIndFunctionPtr in Post-Build */
    CONSTP2FUNC(void, NM_CONFIG_DATA, ptrNm_CarWakeUpIndFuncPtr)(NetworkHandleType nmNetworkHandle);
    #endif  /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

    /* NumberOfChannel */
    uint8 ddNumberOfChannel;

    #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Number Coordination Cluster */
    uint8 ddNumberCoordCluster;
    #endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

    /* Max channeld Id */
    uint8 ddMaxChannelId;
  #else
    uint8 Dummy;
  #endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
} Nm_ConfigType;

#endif /* NM_INTTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
