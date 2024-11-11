/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_Globals.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm module                                             **
**                                                                            **
**  PURPOSE   : This file provides definitions of Global Variables used in    **
**              the module                                                    **
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
** 1.0.1.1    20-Jun-2022   SMKwon        CP44-105                            **
** 1.0.1      16-Mar-2022   LiemNT4       Implement support Post-Build        **
** 1.0.0      04-Dec-2020   Autoever      Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of Global Variable header file */
#include "Nm_Globals.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (NM_DEV_ERROR_DETECT == STD_ON)
#define NM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of Nm Module */
VAR (boolean, NM_VAR_POWER_ON_INIT) Nm_InitStatus; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* (NM_DEV_ERROR_DETECT == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* For storing the flag of Cluster Status handling */
VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_ClusterStatusFlag[NM_NO_OF_CLUSTERS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* For storing the flag of Network Status handling */
VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_NetworkStatusFlag[NM_NO_OF_CHANNELS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
/* For storing a value of current Network Mode */
VAR(Nm_ModeType, NM_VAR_POWER_ON_INIT) Nm_NetworkModeFlag[NM_NO_OF_CHANNELS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
/* For storing status when network mode changed unexpectedly */
VAR(boolean, NM_VAR_POWER_ON_INIT) Nm_ModeChangeFlag[NM_NO_OF_CHANNELS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
/* For storing the flag whether having interal network mode request by ComM */
VAR(boolean, NM_VAR_POWER_ON_INIT) Nm_ComMRequestFlag[NM_NO_OF_CHANNELS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
/* For storing the flag whether waiting for the synchronization point */
VAR(boolean, NM_VAR_POWER_ON_INIT) Nm_SyncPointIndFlag[NM_NO_OF_CLUSTERS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"

#define NM_START_SEC_VAR_POWER_ON_INIT_32
#include "MemMap.h"
/* The channel shutdown delay timer in calling period of main function */
VAR(uint32, NM_VAR_POWER_ON_INIT) Nm_ShutdownTimer[NM_NO_OF_CHANNELS]; /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
#define NM_STOP_SEC_VAR_POWER_ON_INIT_32
#include "MemMap.h"

#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)

#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for ChannelConfig */
P2CONST(Nm_ChannelConfigType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrChannelConfig;
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for ChannelIndexArray */
P2CONST(uint8, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrChannelIndexArray;
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for ChannelArray */
P2CONST(uint8, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrChannelArray;
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for ClusterInfo */
P2CONST(Nm_ClusterInfoType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrClusterInfo;
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for SchMEnterFunc */
P2CONST(Nm_SchMFuncType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrSchMEnterFunc;
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for SchMExitFunc */
P2CONST(Nm_SchMFuncType, AUTOMATIC, NM_CONFIG_DATA) Nm_PtrSchMExitFunc;
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
#define NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Struct for function pointer Nm_CarWakeUpIndFuncPtr */
P2FUNC(void, NM_CONFIG_DATA, Nm_PtrCarWakeUpIndFuncPtr)(NetworkHandleType nmNetworkHandle);
#define NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif  /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_NumberOfChannel;
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_NumberCoordCluster;
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#define NM_START_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"
VAR(uint8, NM_VAR_POWER_ON_INIT) Nm_MaxChannelId;
#define NM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "MemMap.h"

#endif /* (NM_VARIANT_POSTBUID_SUPPORT) == STD_ON */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
