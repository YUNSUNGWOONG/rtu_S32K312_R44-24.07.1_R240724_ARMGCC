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
**  SRC-MODULE: CanIf_PCTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of variables of which value is set at link time     **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2946, #CP44-2947              **
** 1.0.15   05-Jan-2024    JH Jang        #CP44-2840                          **
** 1.0.14   13-Jun-2023    HieuTM8        #CP44-2304                          **
** 1.0.10   27-Oct-2022    HieuTM8        #CP44-1006                          **
** 1.0.9    03-Oct-2022    HieuTM8        #CP44-832                           **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130, #CP44-444                **
** 1.0.3    14-Apr-2022    HieuTM8        #26257                              **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0.3  23-Aug-2021    HieuTM8        #19470, #19526                      **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_PCTYPES_H
#define CANIF_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"                      /* CAN Interface header file */
#include "CanIf_IntTypes.h"             /* CAN Internal Types header file */
#include "CanIf_Types.h"
#if (STD_ON == CANIF_ECUM_CALLBACK)
#include "EcuM.h"                       /* EcuM header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_PCTYPES_AR_RELEASE_MAJOR_VERSION     (4)
#define CANIF_PCTYPES_AR_RELEASE_MINOR_VERSION     (4)
#define CANIF_PCTYPES_AR_RELEASE_REVISION_VERSION  (0)

/* File version information */
#define CANIF_PCTYPES_SW_MAJOR_VERSION     (1)
#define CANIF_PCTYPES_SW_MINOR_VERSION     (1)
#define CANIF_PCTYPES_SW_REVISION_VERSION  (0)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Macro defined for CAN_CONTROLLER_ID */
#if (CANIF_ONE == CANIF_NO_OF_CONTROLLER)
#define CAN_CONTROLLER_ID (Controller)
#else
#define CAN_CONTROLLER_ID (ptrStaticController->CanControllerId)
#endif

/* Pdu mode mask*/
#define CANIF_PDU_MODE_MASK          ((uint8)0x03)

/* Mask value to set Rx state to enable*/
#define CANIF_RX_STATUS_MASK         ((uint8)0x01)

/* Status value to indicate that Queue is occupied */
#define CANIF_TXQUEUE_OCCUPIED       ((uint8)0x80)

/* Rx Validate wake up mask (The four bit of PduMode) */
#define CANIF_RX_VALIDATE_WAKEUP_MASK ((uint8)0x08)

/* Rx Validate wake up value for controller */
#define CANIF_RX_VALIDATE_WAKEUP     ((uint8)0x08)

/* Status value to indicate that Queue is free */
#define CANIF_INVALID_TXQUEUE        ((CanIf_TxQueueSizeType)0xffff)

/* to fill the controller id field in structure */
#define CANIF_INVALID_CONTROLLER     ((uint8)0xff)

/* to check whether the upper layer is correct or not */
#define CANIF_TX_INVALID_UL_USER     ((uint8)0xff)

/* to check whether the upper layer is correct or not */
#define CANIF_RX_INVALID_UL_USER     ((uint8)0xff)

/* to check whether the Dynamic CanId is configured or not */
#define CANIF_INVALID_DYNCANID       ((CanIf_DynamicIdType)0xffff)

/* to check whether the Dynamic CanId is configured or not */
#define CANIF_INVALID_RXCANIDRANGE   ((uint32)0xffffffffuL)

/* Mask value to get the upper layer Id */
#define CANIF_UL_MASK                ((uint8)0x0f)

/* Mask value to get the HTH type */
#define CANIF_HTHTYPE_MASK           ((uint8)0x0f)

/* Status Mask value to get the Partial Networking status */
#define CANIF_PN_STATUS_MASK         ((uint8)0x10)

/* both Partial network and TX confirmation indication */
#define CANIF_TX_CONFIRM_PN_ENABLED  ((uint8)0x10)

/* Mask for getting the Tx Status with Partial networking feature ON of the
 controller (the third bit of PduMode) */
#define CANIF_TX_PNENABLED_MASK      ((uint8)0x04)

/* Value of the TX PN enabled */
#define CANIF_TX_PNENABLED           ((uint8)0x04)

/* TX confirm bit is MSB of Higher nibble, PN enabled bit is MSB of lower
 nibble (The fifth bit of PduMode )*/
#define CANIF_TX_CONFIRM_STATUS_MASK ((uint8)0x10)

/* mask for getting the Tx confirmation Status of the controller */
#define CANIF_TX_CONFIRMED           ((uint8)0x10)

/* Status mask for getting the Notification value */
#define CANIF_NOTIFY_STATUS_MASK     ((uint8)0x80)

/* Status mask for getting the Notification value */
#define CANIF_CLEAR_NOTIFY_STATUS    ((uint8)0x7F)

/* Status mask for getting the Rx Notification value */
#define CANIF_RX_NOTIFY_STATUS_MASK  ((uint8)0x10)

/* Status mask for getting the Rx Data value */
#define CANIF_RX_DATA_STATUS_MASK    ((uint8)0x20)

/* Status mask for IDSM report target PDU */
#define CANIF_RX_IDSM_REPORT_MASK    ((uint8)0x40)

/* Status mask for getting the Dlc value */
#define CANIF_RX_DLC_STATUS_MASK     ((uint8)0x0f)

/* Status mask for getting the queue status */
#define CANIF_QUEUE_STATUS_MASK      ((uint8)0xF0)

/*mask for getting battery voltage status for blocking transmit request */
#define CANIF_TX_BAT_STATUS_MASK     ((uint8)0x20)

/* Mask for Standard CAN ID */
#define CANIF_STANDARD_ID_MASK       ((uint16)0x07FF)

/* Mask for Extended CAN ID */
#define CANIF_EXTENDED_ID_MASK       ((uint32)0x1FFFFFFF)

/* Mask for CAN Frame Type */
#define CANIF_FRAME_TYPE_MASK        ((uint32)0xC0000000)

/* Shift for CAN Frame Type*/
#define CANIF_FRAME_TYPE_SHIFT       ((uint8)0x1E)

/* IP Table of each Controller */
#define CANIF_IPTABLE_COUNT          ((uint8)0x8)

/* Mask for First CAN ID bit*/
#define CANIF_STANDARD_ID_FIRSTBIT_MASK ((uint16)0x0700)

#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanIf_ConfigType, CANIF_CONST) CanIf_Config[CANIF_NO_OF_VARIANT];
#define CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#if (STD_ON == CANIF_SETDYNAMICTXID_API)
#define CANIF_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Can_IdType, CANIF_VAR) CanIf_CanId[CANIF_NO_OF_DYNAMIC_TXLPDU];
#define CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif 
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"
extern CONST(uint16, CANIF_CONST) CanIf_HrhMapArray[CANIF_NO_OF_HRH_MAP];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanIf_ControllerConfigType, CANIF_CONST)
 CanIf_ControllerConfig[CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h" 
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global array for HRH structure */
extern CONST(CanIf_HrhType, CANIF_CONST) CanIf_Hrh[CANIF_NO_OF_HRH];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if(STD_ON == CANIF_IDTABLE_SEARCH)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for HRH structure */
extern CONST(CanIf_RxLpduIdTableType, CANIF_CONST) CanIf_RxLpduIdTable[];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx L-PDU structure */
/* @Trace: CanIf_SUD_GLOBALVAR_006 */
extern CONST(CanIf_TxLpduType, CANIF_CONST) CanIf_TxLpdu[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx L-PDU structure */
extern VAR(PduInfoType, CANIF_VAR) CanIf_TxPduInfoPtr[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#if (STD_ON == CANIF_TX_BUFFERING)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx L-PDU structure */
extern CONST(CanIf_TxBufferType, CANIF_CONST) CanIf_TxBuffer[CANIF_NO_OF_TXBUFFER];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"
/* Global array for mapping index between queue and tx basic pdu */
extern CONST(uint16, CANIF_CONST) CanIf_TxBasicPduIndexMapping[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"

#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx L-PDU structure */
extern CONST(CanIf_RxLpduType, CANIF_CONST) CanIf_RxLpdu[CANIF_NO_OF_RXLPDU];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for CAN Driver structure  */
/* @Trace: CanIf_SUD_GLOBALVAR_010 */
extern CONST(CanIf_CanDriverType, CANIF_CONST) CanIf_CanDriver[];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for CAN Transceiver Driver structure  */
extern CONST(CanIf_CanTrcvDriverType, CANIF_CONST) CanIf_CanTrcvDriver[];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for CAN Transceiver Channel structure */
/* @Trace: CanIf_SUD_GLOBALVAR_012 */
extern CONST(CanIf_TransceiverConfigType, CANIF_CONST) CanIf_CanTrcv[];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_OFF == CANIF_VARIANT_POSTBUILD_SUPPORT)
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanIf_HrhInitType, CANIF_CONST) CanIf_HrhInit[CANIF_NO_OF_HRH_INIT];
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if ((STD_ON == CANIF_WAKEUP_SUPPORT) || (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT))
/* Global array for wakeup sources */
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanIf_WakeupSourceInfoType, CANIF_CONST) CanIf_WakeupSource[CANIF_NO_OF_WAKEUP_SOURCES];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TX_BUFFERING)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Queue allocation */
extern P2VAR(CanIf_TxQueueType, CANIF_VAR, CANIF_VAR) CanIf_QueueList[CANIF_NO_OF_TXBUFFER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Global array for Single Rx Indication Callback Arrays */
extern CONST(CanIf_RxCbkUserType, CANIF_CONST) CanIf_RxSingleCbkUser[CANIF_NINE];

/* Global array for Tx Confirmation Callbacks */
extern CONST(CanIf_TxCbkUserType, CANIF_CONST) CanIf_TxSingleCbkUser[CANIF_NINE];

/* @Trace: SWS_CANIF_00883 */
/* Global array for Tx Trigger Callbacks */
#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)
extern CONST(CanIf_TxCbkTriggerUserType, CANIF_CONST) CanIf_TxSingleCbkTriggerUser[CANIF_TWO];
#endif
/*Global pointer for Multiple Rx Indication Callback Arrays */
extern CONSTP2CONST(CanIf_RxCbkUserType,AUTOMATIC, CANIF_CONST) CanIf_RxMulCbkUser;

/*Global pointer for Multiple Tx Confirmation Callback Arrays */
extern CONSTP2CONST(CanIf_TxCbkUserType,AUTOMATIC, CANIF_CONST) CanIf_TxMulCbkUser;

/* Global variable for Tx Bufferring Functionality */
extern CONST(CanIf_TxBufferPtrsType, CANIF_CONST) CanIf_TxBuffCon;

  #if (STD_ON == CANIF_TX_MULTIPLE_CALLBACK)
extern CONST(CanIf_TxCbkUserType, CANIF_CONST)CanIf_TxCbkUser[CANIF_NO_OF_TXCONFIRMATION];
  #endif
  #if (STD_ON == CANIF_RX_MULTIPLE_CALLBACK)
extern CONST(CanIf_RxCbkUserType, CANIF_CONST)CanIf_RxCbkUser[CANIF_NO_OF_RXINDICATION];
  #endif
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/* define for Post-Build */
#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Structure for Controller */
extern P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) CanIfControllerConfig;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if ((CANIF_DEV_ERROR_DETECT == STD_ON) || CANIF_MULTIPLE_CANDRV_SUPPORT )
#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanIf_HrhInitType, AUTOMATIC, CANIF_CONST) CanIfHrhInit;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanIf_HrhType,AUTOMATIC, CANIF_CONST) CanIfHrh;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanIf_RxLpduType, AUTOMATIC,CANIF_VAR) CanIfRxLpdu;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanIf_TxLpduType,AUTOMATIC, CANIF_CONST) CanIfTxLpdu;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (CANIF_TX_QUEUE == STD_ON)
#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanIf_TxBufferType,AUTOMATIC, CANIF_CONST) CanIfTxBuffer;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(uint16, AUTOMATIC, CANIF_CONST) CanIfHrhMapArray;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(uint16, AUTOMATIC, CANIF_CONST) CanIfTxBasicPduIndexMapping;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#endif /* #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT) */

#endif /* CANIF_PCTYPES_H */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
