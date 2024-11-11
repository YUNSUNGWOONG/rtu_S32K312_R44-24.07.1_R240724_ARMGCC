/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_Globals.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provision of header file for Nm_Globals.c                     **
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
** 1.0.2      31-Oct-2022   NamNT1         CP44-925                           **
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.1      16-Mar-2022   LiemNT4        Implement support Post-Build       **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

#ifndef NM_GLOBALS_H
#define NM_GLOBALS_H

/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/
/* Inclusion for internal types */
#include "Nm_IntTypes.h"
/* Inclusion of Nm Header File */
#include "Nm.h"
#if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
#include "Nm_PBcfg.h"
#endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define NM_GLOBALS_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define NM_GLOBALS_AR_RELEASE_MINOR_VERSION       (0x04u)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#if (NM_DEV_ERROR_DETECT == STD_ON)
  /* For Initialization Status */
  #define NM_INIT                               ((boolean)1)
#endif

/* @Trace: Nm_SUD_MACRO_002 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* Macros for assigning values to cluster shutdown flags */
  #define NM_CLUSTER_SLEEP                      ((uint8)0x00)
  #define NM_CLUSTER_AWAKE                      ((uint8)0x01)
  #define NM_CLUSTER_SYNC_POINT_DELAY           ((uint8)0x02)
  #define NM_CLUSTER_SHUTDOWN_READY             ((uint8)0x03)
  #define NM_CLUSTER_SHUTDOWN_ABORTED           ((uint8)0x04)
  #define NM_CLUSTER_SHUTDOWN_STARTED           ((uint8)0x05)

  /* Macros for assigning values to network release flags */
  #define NM_NW_NO_RELEASE                      ((uint8)0x00)
  #define NM_NW_COMM_RELEASE                    ((uint8)0x01)
  #define NM_NW_BUSNM_RELEASE                   ((uint8)0x02)
  #define NM_NW_COMM_BUSNM_RELEASE              ((uint8)0x03)
  #define NM_NW_SLEEP_INDICATED                 ((uint8)0x04)
  #define NM_NW_RELEASED                        ((uint8)0x05)
  #define NM_NW_ABORTION_TRIGGER                ((uint8)0x06)

#if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
  #define NM_SLEEP_BIT_SET                      ((boolean)1)
  #define NM_SLEEP_BIT_RESET                    ((boolean)0)
#endif  /* (NM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

  #define NM_INVALID_IDX                        (uint8)0xFF
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
  /* Macros for assigning values to the NMS */
  #define NM_RM_BSM                             ((uint8)0x01)
  #define NM_RM_PBSM                            ((uint8)0x02)
  #define NM_NO_RM                              ((uint8)0x04)
  #define NM_NO_RS                              ((uint8)0x08)
  #define NM_RM_RS                              ((uint8)0x10)
  #define NM_RM_NO                              ((uint8)0x20)
#endif  /* (NM_STATE_CHANGE_IND_ENABLED == STD_ON) */

/* Nm zero value definitions */
#define NM_ZERO                                 (0x00u)

/* To avoid unused variable warning */
#define NM_UNUSED(x)                            ((void)(x)) /* polyspace MISRA2012:D4.9 [No action planned:Low] "Use macro function to reduce length of code." */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Extern definitions */
#if (NM_DEV_ERROR_DETECT == STD_ON)
#define NM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of Nm Module */
/* @Trace: Nm_SUD_GLOBALVAR_015 */
extern VAR (boolean, NM_VAR_POWER_ON_INIT) Nm_InitStatus;
#define NM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* (NM_DEV_ERROR_DETECT == STD_ON) */

#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
#define NM_START_SEC_CONFIG_DATA_PREBUILD_PTR
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_001 */
extern CONSTP2FUNC(void, NM_CONFIG_DATA, Nm_CarWakeUpIndFuncPtr) (
  NetworkHandleType nmNetworkHandle);
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
#include "MemMap.h"
#endif /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

#define NM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_013 */
extern CONST(Nm_ChannelConfigType, NM_CONFIG_DATA) Nm_ChannelConfig[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_014 */
extern CONST(uint8, NM_CONFIG_DATA) Nm_ChannelIndexArray[NM_MAX_CHANNEL_ID + 1];
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)

#define NM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_002 */
extern CONST(uint8, NM_CONFIG_DATA) Nm_ChannelArray[NM_CHANNEL_BELONG_TO_CLUSTER];
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"

#define NM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_006 */
extern CONST(Nm_ClusterInfoType, NM_CONFIG_DATA) Nm_ClusterInfo[NM_NO_OF_CLUSTERS];
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_CONFIG_DATA_PREBUILD_PTR
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_012 */
extern CONST(Nm_SchMFuncType, NM_CONFIG_DATA) Nm_SchMEnterFunc[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
#include "MemMap.h"

#define NM_START_SEC_CONFIG_DATA_PREBUILD_PTR
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_011 */
extern CONST(Nm_SchMFuncType, NM_CONFIG_DATA) Nm_SchMExitFunc[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_003 */
extern VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_ClusterStatusFlag[NM_NO_OF_CLUSTERS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_004 */
extern VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_NetworkStatusFlag[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_005 */
extern VAR(Nm_ModeType, NM_VAR_POWER_ON_INIT) Nm_NetworkModeFlag[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_007 */
extern VAR(boolean, NM_VAR_POWER_ON_INIT) Nm_ModeChangeFlag[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_008 */
extern VAR(boolean, NM_VAR_POWER_ON_INIT) Nm_ComMRequestFlag[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_010 */
extern VAR(boolean, NM_VAR_POWER_ON_INIT) Nm_SyncPointIndFlag[NM_NO_OF_CLUSTERS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_32
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_009 */
extern VAR(uint32, NM_VAR_POWER_ON_INIT) Nm_ShutdownTimer[NM_NO_OF_CHANNELS];
#define NM_STOP_SEC_VAR_POWER_ON_INIT_32
#include "MemMap.h"

#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/* Define for Post-Build */
#if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for ChannelConfig */
/* @Trace: Nm_SUD_GLOBALVAR_016 */
extern P2CONST(Nm_ChannelConfigType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrChannelConfig;

/* Struct for ChannelIndexArray */
/* @Trace: Nm_SUD_GLOBALVAR_017 */
extern P2CONST(uint8, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrChannelIndexArray;

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* Struct for ChannelArray */
/* @Trace: Nm_SUD_GLOBALVAR_018 */
extern P2CONST(uint8, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrChannelArray;

/* Struct for ClusterInfo */
/* @Trace: Nm_SUD_GLOBALVAR_019 */
extern P2CONST(Nm_ClusterInfoType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrClusterInfo;

/* Struct for SchMEnterFunc */
/* @Trace: Nm_SUD_GLOBALVAR_020 */
extern P2CONST(Nm_SchMFuncType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrSchMEnterFunc;

/* Struct for SchMExitFunc */
/* @Trace: Nm_SUD_GLOBALVAR_021 */
extern P2CONST(Nm_SchMFuncType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrSchMExitFunc;
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
/* Struct for function pointer Nm_CarWakeUpIndFuncPtr */
/* @Trace: Nm_SUD_GLOBALVAR_022 */
extern P2FUNC(void, NM_CONFIG_DATA, Nm_PtrCarWakeUpIndFuncPtr)(NetworkHandleType nmNetworkHandle);
#endif  /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* @Trace: Nm_SUD_GLOBALVAR_023 */
extern VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_NumberOfChannel;

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* @Trace: Nm_SUD_GLOBALVAR_024 */
extern VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_NumberCoordCluster;
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/* @Trace: Nm_SUD_GLOBALVAR_025 */
extern VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_MaxChannelId;
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */

#endif /* NM_GLOBALS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
