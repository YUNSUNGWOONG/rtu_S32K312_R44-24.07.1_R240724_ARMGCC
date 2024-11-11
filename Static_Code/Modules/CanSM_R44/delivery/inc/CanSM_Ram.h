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
**  SRC-MODULE: CanSM_Ram.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of declaration of RAM area.                         **
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
** 1.0.4     30-Sep-2022   HieuTM8        #CP44-876                           **
** 1.0.2     27-Apr-2022   HieuTM8        R44-Redmine #23926                  **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_RAM_H
#define CANSM_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_InternalTypes.h"        /* Inclusion of CanSM Pctypes header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_007  */
/* AUTOSAR Specification Version Information */
#define CANSM_RAM_H_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_RAM_H_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_RAM_H_AR_RELEASE_REVISION_VERSION      0x00u

/* Software Version Information */
#define CANSM_RAM_H_SW_MAJOR_VERSION                 0x01u
#define CANSM_RAM_H_SW_MINOR_VERSION                 0x00u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */

/* Global variable to store initialization status of CANSM Module */
/* @Trace: CanSM_SUD_GLOBALVAR_001 */
extern VAR(CanSM_StateType, CAN_VAR) CanSM_InitStatus;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */
/* Global variable to store ECU passive status of CanSM Module */
/* @Trace: CanSM_SUD_GLOBALVAR_002 */
extern VAR(CanSM_ECUPassiveType,CAN_VAR) CanSM_ECUPassive;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */

#if(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY)
#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* Global variable to store Bus off delay value */
/* @Trace: CanSM_SUD_GLOBALVAR_003 */
extern VAR(uint8,CAN_VAR) CanSM_BusOffDelayTime;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
#endif

#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_011 */
extern VAR(CanSM_NetworkType, CAN_VAR) CanSM_Network[CANSM_MAX_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
#else
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_011 */
extern VAR(CanSM_NetworkType, CAN_VAR) CanSM_Network[CANSM_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
#endif


#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_004 */
extern VAR(uint8, CAN_VAR) CanSm_ModeReqMax;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_010 */
extern VAR(uint16, CAN_VAR) CanSm_ModeReqRepeatTime;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* Memmap header file */

#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)

#if(STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_005 */
extern VAR(uint8, CAN_VAR) CanSM_LastTrcvHandle;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
#endif

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_006 */
extern VAR(uint8, CAN_VAR) CanSM_LastCtrlHandle;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_007 */
extern VAR(uint8, CAN_VAR) CanSM_LastNWHandle;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */



#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_008 */
extern VAR(uint8, CAN_VAR) CanSM_NWPerCfg;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */


#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALVAR_009 */
extern VAR(uint8, CAN_VAR) CanSM_CtrlPerCfg;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#endif


#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global pointer to start address of static network for selected configuration */
/* @Trace: CanSM_SUD_GLOBALCONST_001 */
extern P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_VAR) CanSM_StaticNw;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALCONST_002 */
extern P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_CtrlIDToNW;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALCONST_003 */
extern P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_NwIdToIndex;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALCONST_004 */
extern P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_CtrlIndexToId;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/* @Trace: CanSM_SUD_GLOBALCONST_005 */
extern P2CONST(uint8, AUTOMATIC, CAN_VAR) CanSM_TrcvIdToNwIndex;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
#endif

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANSM_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

