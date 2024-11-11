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
**  SRC-MODULE: CanTrcv_Globals.c                                             **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Provision of Global RAM Variables                             **
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
** 1.0.4          12-May-2022         HieuTM8          Redmine #26586         **
** 1.0.3          08-May-2022         HieuTM8          Redmine #25643         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
#include "CanTrcv_Globals.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define CANTRCV_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CAN Transceiver Driver */
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable CanTrcv_InitStatus definition." */
VAR(boolean, CANTRCV_VAR_INIT) CanTrcv_InitStatus = CANTRCV_UNINITIALIZED;
#define CANTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Byte allocation */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_ByteArray definition." */
VAR(CanTrcv_TrcvModeType, CANTRCV_VAR_NOINIT)
  CanTrcv_ByteArray[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Byte allocation */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_ByteArray definition." */
VAR(uint8, CANTRCV_VAR_INIT)
  CanTrcv_ClearWufFlag[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store wake up reason */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_WakeUpReason definition." */
VAR(CanTrcv_TrcvWakeupReasonType, CANTRCV_VAR)
  CanTrcv_WakeUpReason[CANTRCV_NUM_OF_NETWORKS];

/* Global variable to store wake up status of Can Transceiver */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_WakeupMode definition." */
VAR(CanTrcv_TrcvWakeupModeType, CANTRCV_VAR)
  CanTrcv_WakeupMode[CANTRCV_NUM_OF_NETWORKS];

/* Global variable to store wake up event is pending */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_WakeupPending definition." */
VAR(CanTrcv_WakeUpPendingType, CANTRCV_VAR)
  CanTrcv_WakeupPending[CANTRCV_NUM_OF_NETWORKS];

/* Flag indicates wake up event status on Can Transceiver */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_WakeupFlagIndication definition." */
VAR(CanTrcv_WakeupEventType, CANTRCV_VAR)
  CanTrcv_WakeupFlagIndication[CANTRCV_NUM_OF_NETWORKS];

#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store ArisuCan status */
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable CanTrcv_ArisuCanSts definition." */
VAR(ArisuCan_CanConfigType, CANTRCV_VAR) CanTrcv_ArisuCanSts;
/* Global variable to store ArisuCan which will use */
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable CanTrcv_ArisuChannelUsed definition." */
VAR(ArisuCan_ChannelConfigType, CANTRCV_VAR) CanTrcv_ArisuChannelUsed;
/* Global variable to store SBC mode of ArisuCan */
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable ArisuCan_SBCModeSts definition." */
VAR(ArisuCan_SBCModeType, CANTRCV_VAR) ArisuCan_SBCModeSts;
#define CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTRCV_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable ArisuCan_SpiDestData definition." */
VAR(uint16, CANTRCV_VAR) ArisuCan_SpiDestData;
#define CANTRCV_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CANTRCV_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable ArisuCan_SpiDestData definition." */
VAR(uint8, CANTRCV_VAR) ArisuCan_ReadFlag;
#define CANTRCV_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#endif/* STD_ON == CANTRCV_ARISUCAN_SUPPORTED */

#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
#if (STD_ON == CANTRCV_SPI_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable CanTrcv_SPICommRetries definition." */
VAR(uint16, CANTRCV_VAR) CanTrcv_SPICommRetries;
#define CANTRCV_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif /* STD_ON == CANTRCV_SPI_SUPPORTED */

#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable CanTrcv_SPICommTimeout definition." */
VAR(uint32, CANTRCV_VAR) CanTrcv_SPICommTimeout;
#define CANTRCV_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif /* STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED */
#endif /* (STD_OFF == CANTRCV_SUPPORT_AR403)*/
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
#define CANTRCV_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to indicate check wake flag */
/* polyspace +2 VARIABLE:* [Justified:Low] "Global variable CanTrcv_CheckWakeFlagIndication definition." */
VAR(boolean, CANTRCV_VAR)
  CanTrcv_CheckWakeFlagIndication[CANTRCV_NUM_OF_NETWORKS];
#define CANTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#if (STD_ON == CANTRCV_PN_SUPPORTED)
#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
#define CANTRCV_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* polyspace +2 VARIABLE:* [Justified:Low] "Global pointer CanTrcv_PartialNetwork definition." */
P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
  CanTrcv_PartialNetwork;

#define CANTRCV_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_PN_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
