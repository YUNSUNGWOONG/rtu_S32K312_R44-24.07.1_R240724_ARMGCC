/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
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
**  SRC-MODULE: CanSM_Ram.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of initialization of RAM area.                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.3     25-Jul-2022   HieuTM8        CP44-511                            **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* #include "CanSM_InternalTypes.h" */        /* CanSM PCTypes header file */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_RAM_C_RELEASE_MAJOR_VERSION       0x04u
#define CANSM_RAM_C_RELEASE_MINOR_VERSION       0x04u
#define CANSM_RAM_C_RELEASE_REVISION_VERSION    0x00u

/* CANSM software version information */
#define CANSM_RAM_C_SW_MAJOR_VERSION            0x01u
#define CANSM_RAM_C_SW_MINOR_VERSION            0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_RAM_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_RAM_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_RAM_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_RAM_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_RAM_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */
/* Global variable to store initialization status of CanSM Module */
VAR(CanSM_StateType, CAN_VAR) CanSM_InitStatus;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */



#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */
/* Global variable to store ECU passive status of CanSM Module */
VAR(CanSM_ECUPassiveType,CAN_VAR) CanSM_ECUPassive;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */

#if(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY)
#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* Global variable to store Bus off delay value */
VAR(uint8,CAN_VAR) CanSM_BusOffDelayTime;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
#endif

#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
VAR(CanSM_NetworkType, CAN_VAR) CanSM_Network[CANSM_MAX_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
#else
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
VAR(CanSM_NetworkType, CAN_VAR) CanSM_Network[CANSM_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
#endif

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSm_ModeReqMax;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */


#define CANSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* Memmap header file */
VAR(uint16, CAN_VAR) CanSm_ModeReqRepeatTime;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* Memmap header file */


#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#if(STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSM_LastTrcvHandle;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
#endif

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSM_LastCtrlHandle;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSM_LastNWHandle;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */


#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSM_NWPerCfg;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSM_CtrlPerCfg;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
#endif


#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global pointer to start address of static network for selected configuration */
P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CAN_VAR) CanSM_StaticNw;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_CtrlIDToNW;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_NwIdToIndex;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_CtrlIndexToId;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_TrcvIdToNwIndex;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#endif



/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
