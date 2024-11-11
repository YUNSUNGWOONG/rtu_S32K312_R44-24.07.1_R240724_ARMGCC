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
**  SRC-MODULE: CanTrcv_Globals.h                                             **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Header file of CanTrcv_Globals.c                              **
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
** 1.0.11         08-Feb-2024         Yubin Song       #CP44-3726             **
** 1.0.9          03-Mar-2023         HieuTM8          #CP44-1782             **
** 1.0.6          13-Oct-2022         HieuTM8          #CP44-943              **
** 1.0.4          12-May-2022         HieuTM8          Redmine #26586         **
** 1.0.3          08-May-2022         HieuTM8          Redmine #25643         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/
/* @Trace: SRS_BSW_00300 */
#ifndef CANTRCV_GLOBALS_H
#define CANTRCV_GLOBALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
#include "CanTrcv_IntTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define CANTRCV_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CAN Transceiver Driver */
/* @Trace: CanTrcv_SUD_GLOBALVAR_001 */
extern VAR(boolean, CANTRCV_VAR_INIT) CanTrcv_InitStatus;
#define CANTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store current operation mode of CanTrcv networks */
/* @Trace: CanTrcv_SUD_GLOBALVAR_003 */
extern VAR(CanTrcv_TrcvModeType, CANTRCV_VAR)
  CanTrcv_ByteArray[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Wuf flag */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_ClearWufFlag definition." */
extern VAR(uint8, CANTRCV_VAR_INIT)
  CanTrcv_ClearWufFlag[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global variable to store wake up reason */
/* @Trace: CanTrcv_SUD_GLOBALVAR_004 */
extern VAR(CanTrcv_TrcvWakeupReasonType, CANTRCV_VAR)
  CanTrcv_WakeUpReason[CANTRCV_NUM_OF_NETWORKS];

/* Global variable to store wake up status of Can Transceiver */
/* @Trace: CanTrcv_SUD_GLOBALVAR_005 */
extern VAR(CanTrcv_TrcvWakeupModeType, CANTRCV_VAR)
  CanTrcv_WakeupMode[CANTRCV_NUM_OF_NETWORKS];

/* Global variable to store wake up event is pending */
/* @Trace: CanTrcv_SUD_GLOBALVAR_006 */
extern VAR(CanTrcv_WakeUpPendingType, CANTRCV_VAR)
  CanTrcv_WakeupPending[CANTRCV_NUM_OF_NETWORKS];

/* Flag indicates wake up event status on Can Transceiver */
/* @Trace: CanTrcv_SUD_GLOBALVAR_007 */
extern VAR(CanTrcv_WakeupEventType, CANTRCV_VAR)
  CanTrcv_WakeupFlagIndication[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanTrcv_SUD_GLOBALVAR_008 */
extern VAR(ArisuCan_CanConfigType, CANTRCV_VAR) CanTrcv_ArisuCanSts;
/* @Trace: CanTrcv_SUD_GLOBALVAR_009 */
extern VAR(ArisuCan_ChannelConfigType, CANTRCV_VAR) CanTrcv_ArisuChannelUsed;
/* @Trace: CanTrcv_SUD_GLOBALVAR_010 */
extern VAR(ArisuCan_SBCModeType, CANTRCV_VAR) ArisuCan_SBCModeSts;
#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* @Trace: CanTrcv_SUD_GLOBALVAR_012 */
#define CANTRCV_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(uint16, CANTRCV_VAR) ArisuCan_SpiDestData;
#define CANTRCV_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: CanTrcv_SUD_GLOBALVAR_013 */
#define CANTRCV_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, CANTRCV_VAR) ArisuCan_ReadFlag;
#define CANTRCV_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#endif /* STD_ON == CANTRCV_ARISUCAN_SUPPORTED */

#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
#if (STD_ON == CANTRCV_SPI_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(uint16, CANTRCV_VAR) CanTrcv_SPICommRetries;
#define CANTRCV_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif /* STD_ON == CANTRCV_SPI_SUPPORTED */

#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, CANTRCV_VAR) CanTrcv_SPICommTimeout;
#define CANTRCV_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif /* STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED */
#endif /* (STD_OFF == CANTRCV_SUPPORT_AR403)*/
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
/* @Trace: CanTrcv_SUD_CONSTVAR_001 */
#define CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTrcv_NetworkType, CANTRCV_CONST)
  CanTrcv_CanTrcvNetwork[CANTRCV_NUM_OF_NETWORKS];

/* @Trace: CanTrcv_SUD_CONSTVAR_002 */
#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
extern CONST(ArisuCan_CanConfigType, CANTRCV_CONST)
  CanTrcv_ArisuCan[ARISUCAN_TYPE_NUM_OF_MODE];
#endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */

#define CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to indicate check wake flag */
/* @Trace: CanTrcv_SUD_GLOBALVAR_002 */
extern VAR(boolean, CANTRCV_VAR)
  CanTrcv_CheckWakeFlagIndication[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#if (STD_ON == CANTRCV_PN_SUPPORTED)
#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
#define CANTRCV_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
  CanTrcv_PartialNetwork;

#define CANTRCV_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#else
#define CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTrcv_PartialNetworkType, CANTRCV_CONST)
  CanTrcv_PartialNetwork[CANTRCV_NUM_OF_PARTIALNETWORKS];

#define CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_PN_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANTRCV_GLOBALS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
