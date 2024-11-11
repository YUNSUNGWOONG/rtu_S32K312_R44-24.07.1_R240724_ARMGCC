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
**  SRC-MODULE: CanIf_Types.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Type definition of AUTOSAR CanIf                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0    29-Feb-2024    Jh Yang        #CP44-2947                          **
** 1.0.9    03-Oct-2022    HieuTM8        #CP44-832                           **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.2   	25-Mar-2022    HieuTM8        #25534                              **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SWS_CANIF_00040 Mandatory interfaces */
/* @Trace: SWS_CANIF_00294 Optional interfaces*/
#include "Can.h"                  /* CAN Driver Module Header File */
#include "CanIf_Cfg.h"
#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
#include "CanIf_PBcfg.h"         /* Configuration PB header file */
#endif

#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#include "CanIf_CanTrcv.h"              /* CAN Transceiver Module Header File */
#endif
/* @Trace: SRS_Can_01001 */
/* @Trace: SWS_CANIF_00142 Imported types*/
#include "Can_GeneralTypes.h"           /* Can Generaltypes header file */

#include "CanDrv_422_Compat.h"			/* Support type for MCAL 4.2.2*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define CANIF_TYPES_AR_RELEASE_MINOR_VERSION     4
#define CANIF_TYPES_AR_RELEASE_REVISION_VERSION  0

/* Software Version Information */
#define CANIF_TYPES_SW_MAJOR_VERSION     1
#define CANIF_TYPES_SW_MINOR_VERSION     1
#define CANIF_TYPES_SW_REVISION_VERSION  0
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* Return value of the WakeupSourceType. */
#define CANIF_CONTROLLER_WAKEUP (0)
#define CANIF_TRANSCEIVER_WAKEUP (1)

/* polyspace-begin MISRA-C3:D4.8 [Not a defect: Justified] "Structure will be derefernenced based on Configuration" */
typedef struct
{
  uint32 TxMsgCnt;
  uint32 RxMsgCnt;
} CanIf_MsgType;
/* polyspace-end MISRA-C3:D4.8 [Not a defect: Justified] "Structure will be derefernenced based on Configuration" */

/* @Trace: SWS_CANIF_00137 */ /* CanIf_PduModeType */
typedef enum
{
  CANIF_OFFLINE = 0,
  CANIF_TX_OFFLINE,
  CANIF_TX_OFFLINE_ACTIVE,
  CANIF_ONLINE
} CanIf_PduModeType;

/* @Trace: SWS_CANIF_00201 */ /* CanIf_NotifStatusType*/
/* Return value of the Notification Status API */
typedef enum
{
  CANIF_NO_NOTIFICATION = 0,
  CANIF_TX_RX_NOTIFICATION
} CanIf_NotifStatusType;

/* Return value of the CanIf_TrcvWakeupModeType. */
typedef enum
{
  CANIF_TRCV_WU_ENABLE = 0,
  CANIF_TRCV_WU_DISABLE,
  CANIF_TRCV_WU_CLEAR
} CanIf_TrcvWakeupModeType;

/* Battery voltage state transitions that are used by
 * the function CanIf_SetBatteryVoltageMode */
typedef enum
{
  CANIF_SET_BATVOL_NORMAL = 0,
  CANIF_SET_BATVOL_CRITICAL
} CanIf_BatVolSetModeType;

/* L-PDU meta data item type */
typedef enum {
  ADDRESS_EXTENSION_8 = 0x00,
  CAN_ID_32,
  ETHERNET_MAC_64,
  LIN_NAD_8,
  PRIORITY_8,
  SOCKET_CONNECTION_ID_16,
  SOURCE_ADDRESS_16,
  TARGET_ADDRESS_16,
  CANIF_INVALID_METADATA_TYPE = 0xff
} MetaDataItemType;
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANIF_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
