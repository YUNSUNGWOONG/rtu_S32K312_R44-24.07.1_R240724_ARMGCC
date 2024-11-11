/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm_Globals.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : Provision for CanNm extern Variable                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date         By                  Description                     **
********************************************************************************
** 1.1.4     31-Jan-2023  NamNT1              CP44 #1098                      **
** 1.1.1     07-Oct-2022  NamNT1              CP44 #785, #786, #610, #838,    **
**                                            #887, #842                      **
** 1.1.0.0   28-Jul-2022  SM Kwon             R44 Redmine #29362              **
** 1.0.2.1   20-Jun-2022  SM Kwon             CP44-120                        **
** 1.0.0     16-Dec-2020  SHKim               Initial Version                 **
*******************************************************************************/

#ifndef CANNM_GLOBALS_H
#define CANNM_GLOBALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanNm_IntTypes.h"        /* CanNm configuration header */
/* @Trace: CanNm_SUD_DATATYPE_006 CanNm_SUD_DATATYPE_007 */
#include "NmStack_Types.h"        /* Nm Interface type definitions header */
#include "CanNm.h"
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#include "CanNm_PBCfg.h"            /* Postbuild Configuration header file */
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANNM_GLOBALS_AR_RELEASE_MAJOR_VERSION      (0x04u)
#define CANNM_GLOBALS_RELEASE_MINOR_VERSION         (0x04u)
#define CANNM_GLOBALS_AR_RELEASE_REVISION_VERSION   (0x00u)

/* File version information */
#define CANNM_GLOBALS_SW_MAJOR_VERSION              (0x01u)
#define CANNM_GLOBALS_SW_MINOR_VERSION              (0x02u)
#define CANNM_GLOBALS_SW_PATCH_VERSION              (0x00u)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: CanNm_SUD_DATATYPE_008 */
typedef struct
{
  /* For all the States and the Modes*/
  CanNm_ModeState modeStatus;
  CanNm_ModeState nextModeState;

  #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
  /* ERA timer */
  CanNm_TimeType eRATimer[CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE * CANNM_EIGHT];
  #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

  /* Remote sleep indication timer */
  #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
  CanNm_TimeType remoteSleepIndTime;
  #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
  
  /* Wait bus sleep timer */
  CanNm_TimeType waitBusSleepTime;
  
  /* Repeat message state timer */
  CanNm_TimeType repeatMessageTime;

  /* NM Timeout time for NM PDU�s */
  CanNm_TimeType ntwkTimeOutTime;

  /* Period of NM Message */
  CanNm_TimeType msgCycleTime;

  /* CanNm shall not perform transmission error handling */
  #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  /* Tx Msg timeout timer */
  CanNm_TimeType msgTimeOutTime;
  #endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

  /* Buffer to store Rx data */
  uint8 rxUserData[CANNM_MAX_PDU_SIZE];

  #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
  /* Buffer to store meta data */
  uint8 rxMetaData[CANNM_METADATA_LENGTH];
  #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

  /* Buffer to store Tx data */
  uint8 txUserData[CANNM_MAX_PDU_SIZE];

  /* No. of immediate NM Pdus */
  uint8 noOfImmediateNmTx;

  #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
  /* ERA array containing PN bits */
  uint8 eRA[CANNM_MAX_PDU_SIZE];
  #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

  /* Buffer to store wake up data */
  uint8 carWakeUpPdu[CANNM_MAX_PDU_SIZE];

  /* Remote sleep detection */
  #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
  boolean remoteSlpDetect;
  #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

  /* PN algorithm status for the channel */
  boolean pnStatusBit;
  
  /* Network request status */
  boolean networkRequested;
  
  /* Communication status */
  volatile boolean communicationEnabled;

  /* Active wake up bit status */
  boolean txActiveWakeUpBit;

  /* Coordinator sleep ready bit status */
  boolean txNmCoordinatorSleepReadyBit;

  /* Bus load reduction status */
  boolean busLoadReductionEnabled;

  /* Nm sleep indication call status */
  boolean nmCoordReadyToSleepIndicationCalled;

  /* Tx result status */
  boolean transmissionRequestFailed;

  #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
  /* Car wake up status */
  boolean carWakeUpBit;
  #endif /* #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

  #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
  /* Meta Data flag check */
  boolean rxMetaDataCheck;
  #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

  #if(STD_ON == CANNM_NMS_POSITION_ENABLED)
  NM_STATE nmState;
  #endif

  #if (CANNM_REASON_POSITION_ENABLED == STD_ON)
  uint8 nwRequestReason;
  #endif
} CanNm_Channel;

/* @Trace: CanNm_SUD_GLOBALVAR_001 */
/* extern definitions */
#define CANNM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* extern definitions for variable to hold CANNM Initialization Status */
extern VAR(boolean, CANNM_VAR) CanNm_InitStatus;
#define CANNM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* @Trace: CanNm_SUD_GLOBALVAR_002 */
#define CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* extern definition for Channel configuration information array
 *   (for all active channels)  
 */
extern VAR(CanNm_Channel, CANNM_VAR_NOINIT)
                                    CanNm_ArrayChannel[CANNM_NUMBER_OF_CHANNEL];
#define CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* @Trace: CanNm_SUD_GLOBALVAR_003 */
#if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Consists of the PN mask bytes of all the channels. Index of this array to be
 * provided in CanNm_ArrayStaticChannel for the respective channel
 */
extern CONST(uint8, CANNM_CONST) CanNm_ArrayPnMaskByte[CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE];
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
#endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

/* @Trace: CanNm_SUD_GLOBALVAR_004 */
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanNm_PnInfoType, CANNM_CONST) CanNm_structPnInfo;
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

/* @Trace: CanNm_SUD_GLOBALVAR_005 */
#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* extern definitions for variable to hold CANNM Meta Data Status */
extern VAR(boolean, CANNM_VAR) CanNm_RxMetaDataCheck;
#define CANNM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /*#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

/* @Trace: CanNm_SUD_GLOBALVAR_006 */
#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
extern VAR(uint8, CANNM_VAR) CanNm_RxMetaData[CANNM_METADATA_LENGTH];
#define CANNM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

/* @Trace: CanNm_SUD_GLOBALVAR_007 */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
#define CANNM_START_SEC_CONFIG_CONST_POSTBUILD_8
#include "MemMap.h"
extern P2CONST(uint8, AUTOMATIC, CANNM_APPL_CONST) CanNm_PnFilterMaskBytesPtr;
#define CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_8
#include "MemMap.h"
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

/* @Trace: CanNm_SUD_GLOBALVAR_008 */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#define CANNM_START_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_APPL_CONST) CanNm_ChannelsDataPtr;
#define CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

/* @Trace: CanNm_SUD_GLOBALVAR_009 */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#define CANNM_START_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanNm_RxPdu, AUTOMATIC, CANNM_APPL_CONST) CanNm_RxPduId;
#define CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

/* @Trace: CanNm_SUD_GLOBALVAR_010 */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#define CANNM_START_SEC_VAR_NO_INIT_POSTBUILD_32
#include "MemMap.h"
extern VAR(uint32, CANNM_VAR) CanNm_NumberOfRxPdu;
#define CANNM_STOP_SEC_VAR_NO_INIT_POSTBUILD_32
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANNM_GLOBALS_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
