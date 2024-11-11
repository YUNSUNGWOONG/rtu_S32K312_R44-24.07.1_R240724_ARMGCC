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
**  SRC-MODULE: CanIf_IntTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR CanIf Structure type definitions         **
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
** 1.1.0    29-Feb-2024    Jh Yang        #CP44-2946, #CP44-2947, #CP44-3811  **
** 1.0.14   13-Jun-2023    HieuTM8        #CP44-2236, #CP44-2304              **
** 1.0.9    03-Oct-2022    HieuTM8        #CP44-832                           **
** 1.0.6    25-Jul-2022    HieuTM8        #CP44-444                           **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.4    09-May-2022    Jiwon Oh       #26814,#27128                       **
** 1.0.1    09-Feb-2022    HieuTM8        #20891,#23968,19167                 **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_INTTYPES_H
#define CANIF_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanIf.h"                      /* CAN Interface header file */
#include "CanIf_Types.h" 
#include "CanDrv_422_Compat.h"
#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR_CanIf.h"                 /* Call-back PduR header file */
#endif

#if (STD_ON == CANIF_CANTP_CALLBACK)
#include "CanTp.h"                  /* Call-back CanTp header file */
#endif
#if (STD_ON == CANIF_CANNM_CALLBACK)
#include "CanNm.h"                  /* Call-back CannM header file */
#endif
#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#include "CanIf_CanTrcv.h"              /* Call-back CanTrcv header file */
#endif

#include "Det.h"                        /* DET header file */

#include "CanIf_UserInc.h"              /* CanIf User included header file */

#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#include "EcuM.h"
#endif


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_INT_AR_RELEASE_MAJOR_VERSION       (4)
#define CANIF_INT_AR_RELEASE_MINOR_VERSION       (4)
#define CANIF_INT_AR_RELEASE_REVISION_VERSION    (0)

/* Software Version Information */
#define CANIF_INT_SW_MAJOR_VERSION    (1)
#define CANIF_INT_SW_MINOR_VERSION    (1)

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code"*/
/* Macro for getting Pdu mode */
#define CANIF_PDU_MODE(PduMode) \
    ((PduMode) & CANIF_PDU_MODE_MASK)

/* Macro for setting PDU mode and keep status of Tx & Rx flags*/
#define CANIF_SET_PDU_MODE(PduMode, PduModeReq) \
    (PduMode) = ((PduMode) & (~CANIF_PDU_MODE_MASK)) | (uint8)PduModeReq

/* Macro for getting Tx status */
#define CANIF_TX_STATUS(PduMode) \
    (((uint8)CANIF_ONLINE == CANIF_PDU_MODE(PduMode)) ? \
            CANIF_TX_ENABLED : \
            ((uint8)CANIF_TX_OFFLINE_ACTIVE == CANIF_PDU_MODE(PduMode)) ? \
                    (uint8)CANIF_TX_OFFLINE_ACTIVE : CANIF_TX_DISABLED)

/* Macro for getting Rx status */
#define CANIF_RX_STATUS(PduMode) \
    ((PduMode) & CANIF_RX_STATUS_MASK)

/* Macro for setting Tx confirmed */
#define CANIF_SET_TX_CONFIRMED(PduMode) \
    (PduMode) |= CANIF_TX_CONFIRM_STATUS_MASK

/* Macro for clear Tx confirmed */
#define CANIF_CLEAR_TX_CONFIRMED(PduMode) \
    (PduMode) &= ~CANIF_TX_CONFIRM_STATUS_MASK

/* Macro for checking for Tx confirmed */
#define CANIF_IS_TX_CONFIRMED(PduMode) \
    (((uint8)CANIF_ONLINE == CANIF_PDU_MODE(PduMode)) && \
     (((PduMode) & CANIF_TX_CONFIRM_STATUS_MASK) == CANIF_TX_CONFIRMED))

/* Macro for setting Rx wake up validation flag */
#define CANIF_SET_RX_VALIDATE_WAKEUP(PduMode) \
    (PduMode) |= CANIF_RX_VALIDATE_WAKEUP_MASK

/* Macro for clearing Rx wake up validation flag */
#define CANIF_CLEAR_RX_VALIDATE_WAKEUP(PduMode) \
    (PduMode) &= ~CANIF_RX_VALIDATE_WAKEUP_MASK

/* Macro for checking for Rx validate wake up */
#define CANIF_IS_RX_VALIDATE_WAKEUP(PduMode) \
    ((CANIF_RX_ENABLED == CANIF_RX_STATUS(PduMode)) && \
    (((PduMode) & CANIF_RX_VALIDATE_WAKEUP_MASK) == CANIF_RX_VALIDATE_WAKEUP))

/* Macro for setting TX PN enabled flag */
#define CANIF_SET_TX_PNENABLED(PduMode) \
    (PduMode) |= CANIF_TX_PNENABLED_MASK

/* Macro for clear TX PN flag */
#define CANIF_CLEAR_TX_PNENABLED(PduMode) \
    (PduMode) &= ~CANIF_TX_PNENABLED_MASK

/* Macro for checking for TX PN enabled flag */
#define CANIF_IS_TX_PNENABLED(PduMode) \
    (((PduMode) & CANIF_TX_PNENABLED_MASK) == CANIF_TX_PNENABLED)
    
/* polyspace-end MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code"*/
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define CANIF_BLOCK                               ((uint8)0x10)

#define CANIF_TX_PN_MASK                          ((uint8)0x10)

#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
#define CANIF_OK                                  ((Std_ReturnType)0x00)

#define CANIF_NOT_OK                              ((Std_ReturnType)0x01)
#else
#define CANIF_OK                                  ((Can_ReturnType)0x00)

#define CANIF_NOT_OK                              ((Can_ReturnType)0x01)
#endif
#define CANIF_ZERO                                (0x00)

#define CANIF_ONE                                 (0x01)

#define CANIF_TWO                                 (0x02)

#define CANIF_THREE                               (0x03)

#define CANIF_FIVE                                (0x05)

#define CANIF_SIX                                 (0x06)

#define CANIF_SEVEN                               (0x07)

#define CANIF_EIGHT                               (0x08)

#define CANIF_NINE                                (0x09)

#define CANIF_THIRTYTWO                           (0x20)

#define CANIF_16                                  (0x10)

#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
#define CANIF_UNINIT                        ((Can_ControllerStateType)0x00)

#define CANIF_STARTED                       ((Can_ControllerStateType)0x01)

#define CANIF_STOPPED                       ((Can_ControllerStateType)0x02)

#define CANIF_SLEEP                         ((Can_ControllerStateType)0x03)
#else
#define CANIF_UNINIT                        ((CanIf_ControllerModeType)0x00)

#define CANIF_SLEEP                         ((CanIf_ControllerModeType)0x01)

#define CANIF_STARTED                       ((CanIf_ControllerModeType)0x02)

#define CANIF_STOPPED                       ((CanIf_ControllerModeType)0x03)
#endif
#define CANIF_INITIALISED                   ((uint8)0x01)

#define CANIF_UNINITIALISED                 ((uint8)0x00)

#define CANIF_TRUE                          ((uint8)0x01)

#define CANIF_FALSE                         ((uint8)0x00)

#define CANIF_RANGE_SUCCESS                 ((uint8)0x80)

#define CANIF_FAILURE                       ((uint8)0x00)

#define CANIF_MAX_DLC                       ((uint8)0x08)

#define CANIF_FULL_CAN                      ((uint8)0x01)

#define CANIF_BASIC_CAN                     ((uint8)0x00)

#define CANIF_RX_BASIC_CAN_STD              ((uint8)0x00)

#define CANIF_RX_BASIC_CAN_EXT              ((uint8)0x01)

#define CANIF_RX_BASIC_CAN_MIXED            ((uint8)0x02)

#define CANIF_RX_FULL_CAN_STD               ((uint8)0x03)

#define CANIF_RX_FULL_CAN_EXT               ((uint8)0x04)

#define CANIF_RX_FULL_CAN_MIXED             ((uint8)0x05)

#define CANIF_MAX_UL                        ((uint8)0x08)

#define CANIF_WAKEUP_VALIDATION_VALUE       ((uint8)0x81)

#define CANIF_PDUR                          ((uint8)0x00)

#define CANIF_CANTP                         ((uint8)0x01)

#define CANIF_CANNM                         ((uint8)0x02)

#define CANIF_CDD                           ((uint8)0x03)

#define CANIF_J1939TP                       ((uint8)0x04)

#define CANIF_XCP                           ((uint8)0x05)

#define CANIF_OSEKNM                        ((uint8)0x06)

#define CANIF_J1939NM                       ((uint8)0x07)

#define CANIF_STANDARD_CANID_VALUE          ((uint32)0x7FF)

#define CANIF_EXTENDED_CANID_VALUE          ((uint32)0x9FFFFFFFU)

#define CANIF_CANDRV_WAKEUPSOURCE           ((uint8)0x00)

#define CANIF_CANTRCV_WAKEUPSOURCE          ((uint8)0x01)

#define CANIF_CANFD_NO_STANDARD_CANID_TYPE  ((uint8) 0x00)

#define CANIF_CANFD_STANDARD_CANID_TYPE     ((uint8) 0x01)

#define CANIF_CANFD_NO_EXTENDED_CANID_TYPE  ((uint8) 0x02)

#define CANIF_CANFD_EXTENDED_CANID_TYPE     ((uint8) 0x03)

#define CANIF_STANDARD_CANID_TYPE           ((uint8) 0x04)

#define CANIF_EXTENDED_CANID_TYPE           ((uint8) 0x05)

#define CANIF_CONTROLLER_WAKEUP_ON                     (1)

#define CANIF_CONTROLLER_WAKEUP_OFF                    (0)

#define CANIF_RX_DISABLED                   ((uint8) 0x00)

#define CANIF_RX_ENABLED                    ((uint8) 0x01)

#define CANIF_TX_DISABLED                   ((uint8) 0x00)

#define CANIF_TX_ENABLED                    ((uint8) 0x01)

#define CANIF_TX_BAT_ERROR                  ((uint8) 0x01)
#define CANIF_TX_BAT_NORMAL                 ((uint8) 0x00)

#define CANIF_TRCV_INIT_MODE                ((uint8) 0xff)

#define CANIF_TWELVE                        ((uint8)12)

#define CANIF_FOUR                          ((uint8)4)

#define CANIF_SIXTEEN                       ((uint8)16)

#define CANIF_TWENTY_FOUR                   ((uint8)24)

#define CANIF_CANID_MASK_ONE                ((uint8)0xFF)

#define CANIF_CANID_MASK_TWO                ((uint16)0xFFFF)

#define CANIF_MASK_BYTE_ONE                 ((uint16)0XFF00)

#define CANIF_CANID_MASK_FOUR               ((uint32)0x1FFFFFFF)

#define CANIF_MASK_BYTE_FOUR                ((uint32)0XFF000000U)

#define CANIF_MASK_BYTE_THREE               ((uint32)0X00FF0000)

#define CANIF_EXTENDED_BIT_SET              ((uint32)0x80000000U)

#define CANIF_CANFD_MAX_LENGTH             ((uint8) 0x40)

#define CANIF_MAX_META_PDU_DATA_LENGTH     ((uint8) 0x46)

#define CANIF_CANID_BYTE_MASK              ((uint32)0x000000FFU)

#if (STD_OFF == CANIF_CANFD_ID_16BIT_SUPPORT)
#define CANIF_STANDARD_FD_VALUE            ((uint32)0x40000000U)
#else
#define CANIF_STANDARD_FD_VALUE            ((uint32)0x00004000U)
#endif
#define CANIF_EXTENDED_FD_VALUE            ((uint32)0x40000000U)

#define CANIF_PDUR_TRIGGER                 ((uint8)0U)

#define CANIF_CDD_TRIGGER                  ((uint8)1U)
/* type definitions for objects depends on CAN DB import */
/* They shall be fixed to uint16 regardless of CAN DB import result */
typedef PduIdType CanIf_TxPduIdType;
typedef PduIdType CanIf_RxPduIdType;
/* @Trace: CanIf_SUD_DATATYPE_017 */
typedef uint16 CanIf_HthType;
typedef uint16 CanIf_TxQueueSizeType;
typedef uint16 CanIf_DynamicIdType;
typedef uint16 CanIf_IdType;

/* type definition of Rx call-back function */
typedef void (*CanIf_Rx_Callback)(PduIdType CanTxPduId, P2CONST(void, AUTOMATIC, CANIF_CONST)SduPtr);


typedef void (*CanIf_Rx_CddCbk)(PduIdType CanTxPduId, P2CONST(void, AUTOMATIC, CANIF_CONST)SduPtr,
                                                            Can_IdType CanId);

#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
/* Structure for Transciever */
typedef struct
{
  uint8 CanTrcvId;         /* CanTrcvId */
  uint8 CanTrcvDriverId;   /* driver id in case of multiple driver support */
} CanIf_TransceiverConfigType;
#endif

#if((STD_ON == CANIF_WAKEUP_SUPPORT) || (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT) ||\
 (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)|| (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT))
/* Structure for wakeup source information */
typedef struct 
{
  EcuM_WakeupSourceType WakeupEvent;  /* Wakeup event */
  uint8 WakeupSource;    /* CANIF_<CANDRV/CANTRCV_WAKEUPSOURCE */
  uint8 CanCntrlOrTrcvId; /* CanControllerId/CanTrcvId */
  #if ((STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT) || \
                                      (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT))
  uint8 DriverId; /*Driver Id*/
  #endif
  uint8 ControllerConfigId;  /* Index of the CAN Controller structure */

  uint8 NoOfCanCntrlOrTrcvId;
} CanIf_WakeupSourceInfoType;
#endif

/* Structure for Rx L-PDU(Range Or List)  */
typedef struct 
{
  /* @Trace: CanIf_SUD_DATATYPE_008 */
  Can_IdType RxPduCanId;     /* actual ID(List) */
  Can_IdType RxLowerCanId;  /* CAN-ID lower limit (Range) */
  Can_IdType RxUpperCanId;  /* CAN-ID upper limit */

  CanIf_RxPduIdType RxPduId;
  CanIf_RxPduIdType TargetId;  /* TargetPduId */
  
  #if (STD_ON == CANIF_META_DATA_SUPPORT)
  uint32 CanIfRxPduCanIdMask;
  uint8 MetaDataLength;
  MetaDataItemType MetaDataType;
  #endif  
  
  #if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
      (STD_ON == CANIF_READRXPDU_DATA_API))
  CanIf_RxPduIdType RxNotifyId;  /*  Notify Id */
  #endif
  
  /* @Trace: CanIf_SUD_DATATYPE_031 */
  #if (STD_ON == CANIF_PRIVATE_DATA_LENGTH_CHECK)
  boolean DataLengthCheck; /* data length check */
  uint8 Dlc;  /* Statically configured DLC */
  #endif
  
  uint8 CallbackIndex;     /* CanRxPduId */  
  uint8 RxUserOrNotifSts;  /* RxUserOrNotifSts
                              Upper Layer - Lower nibble
                              0xX0- PDUR
                              0xX1- CANTP
                              0xX2- CAN NM
                              0xX3- CDD
                              0xX4- J1939TP
                              0xX5- XCP
                           */
                            /* Notif Status  - Upper Nibble
                              0x1X - Notify
                              0x2X - Data
                              0x4X - IdsM
                           */

  uint8 ControllerId;      /* Controller to which the RxLpdu is mapped to */
  uint8 RxPduCanIdType;    /* CanIfRxPduCanIdType 
                              0x00 - STANDARD_NO_FD_CAN
                              0x01 - STANDARD_FD_CAN
                              0x02 - EXTENDED_NO_FD_CAN
                              0x03 - EXTENDED_FD_CAN
                              0x04 - STANDARD_CAN
                              0x05 - EXTENDED_CAN
                           */

} CanIf_RxLpduType;

/* @Trace: CanIf_SUD_DATATYPE_032 */
#if ((STD_ON == CANIF_DEV_ERROR_DETECT) ||                                     \
                                    (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT))
typedef struct 
{
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  uint16 MaxHrhId;    /* Maximum Hrh Id */
  #endif
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  uint8 HrhOffSetId;  /* Hrh Offeset Id */
  #endif
} CanIf_HrhInitType;
#endif
/* Structure for HRH */
/* @Trace: CanIf_SUD_DATATYPE_034 */
typedef struct 
{
  PduIdType RxLpduIndex;    /* Pointer to first range or list kind of Rx L-PDU(s)
                            structure */
  uint8 Softwarefilter;
  PduIdType  NoOfHrhRange;  /* Number of range */
  Can_IdType Hrhcanidlower;
  Can_IdType Hrhcanidupper;
  Can_IdType HrhRangeMask;   /* Range Mask */
  Can_IdType HrhRangeBaseId; /* Base ID range */ 

  PduIdType NoOfRxLpdusList;     /* Number of list kind of Rx L-PDU(s) */
  uint8 FilterMethod;   /* Filter Method :  0x00: -> BasicCAN WITH STANDARD
                          0x01: -> BASICCAN WITH EXTENDED
                          0x02: -> BASICCAN WITH MIXED
                          0x03: -> FULLCAN WITH STANDARD
                          0x04: -> FULLCAN WITH EXTENDED
                          0x05: -> FULLCAN WITH MIXED */
  #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
  uint8 ControllerId;   /* Index to the controller */
  #endif
} CanIf_HrhType;

/* @Trace: CanIf_SUD_DATATYPE_033 */
#if(STD_ON == CANIF_IDTABLE_SEARCH)
/* Structure for IdTable */
typedef struct 
{
  PduIdType RxLpduIdTableIndex; /* Pointer to first range or list kind of Rx L-PDU(s)
                          structure */
  PduIdType NoOfRxLpdusRange;    /* Number of range kind of Rx L-PDU(s) */
} CanIf_RxLpduIdTableType;
#endif

 #if ((STD_ON == CANIF_READRXPDU_DATA_API) || \
                                  (STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API))
/* Structure for Rx L-PDU Notification */

typedef struct 
{
  #if (STD_ON == CANIF_READRXPDU_DATA_API)
  uint8 RxBufferData[CANIF_EIGHT];    /* Pointer to Rx L-PDU data buffer */
  #endif
  uint8 DlcOrNotify;    /* Pointer to Rx L-PDU status */

} CanIf_RxLpduNotifyType;
#endif

/* Structure for Transmit L-PDU */
typedef struct 
{
  Can_IdType CanId;    /* Statically configured CAN-ID */
  Can_HwHandleType HthIdorBufferId;    /* Statically configured Hth Id */

  PduIdType TxConfirmPduId;  /* Handle Id - for confirmation */

  PduIdType TxPduId;  /* Handle Id - CanTxPduId */

  uint8 CallbackIndex;   /* Callback function index */

  uint8 TxCbkUser;    /* Callback Id for confirmation */	
  uint8 HTHTypeOrTXPN;   /* Lower nibble | Higher nibble
                              0x0X              0xX0
                           CANIF_FULL_CAN  | CANIF_TXPN_ENABLED
                           CANIF_BASIC_CAN | CANIF_TXPN_ENABLED
                           CANIF_FULL_CAN  | CANIF_TXPN_DISABLED
                           CANIF_BASIC_CAN | CANIF_TXPN_DISABLED
                           Type of HTH */
  uint8 CanIdType;    /* Type of CAN-ID */  
  boolean TriggerTransmit;
  boolean Truncate;
  
  #if (STD_ON == CANIF_META_DATA_SUPPORT)
  Can_IdType CanIdMask;
  uint8      MetaDataLength;
  #endif
  
  #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
  uint8 TxNotifyStatusIndex;   /* Pointer to Tx L-PDU notify status */
  #endif
  #if (STD_ON == CANIF_SETDYNAMICTXID_API)
  CanIf_DynamicIdType DynCanIdIndex;   /* Dynamic CAN-ID */
  #endif

  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  uint8 DriverId;    /* CAN Driver Id */
  #endif
  #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
  uint8 TxNotifyStsMask;    /* Mask for the bit corresponding to L-PDU
                              notify status */
  #endif
  
  #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
  uint8 ControllerId;   /* Type of CAN-ID */
  #endif
  
} CanIf_TxLpduType;

/* Structure for Controller */
typedef struct 
{
  /* Pointer to tx Lpdu */
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) TxLpdu;

  CanIf_TxPduIdType NoOfTxPdu;    /* Index number to Tx L-PDU link to queue */

  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  uint8 CanDriverId;        /* CAN Driver Id */
  #endif
  #if (CANIF_NO_OF_CONTROLLER >  CANIF_ONE)
  uint8 CanControllerId;   /* Statically configured ControllerId */
  #endif
  #if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
  boolean WakeupEnabled;   /* Indication of wakeup */
  #endif
  #if (STD_ON == CANIF_PN_SUPPORT)
  boolean PartialNWEnabled;   /* Indication of Partial networking feature */
  #endif
} CanIf_ControllerConfigType;

typedef struct 
{
  /* Mode of the Controller */
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
    (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  Can_ControllerStateType ControllerMode;
  #else
  Can_ControllerStateType ControllerMode;
  #endif
  #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
  boolean MirroringActive; /* Indication of Bus Mirrorring*/
  #endif
  uint8 PduMode; /*       Pdu Mode
                    0x00  Transmit and receive path of
                          the corresponding channel are
                          disabled => no communication mode
                    0x01  Transmit path of the corresponding
                          channel is disabled. The receive
                          path is enabled.
                    0x02  Transmit path of the corresponding
                          channel is in offline active mode
                          (see SWS_CANIF_00072). The receive
                          path is disabled.
                          This mode requires CanIfTxOfflineActiveSupport = TRUE.
                    0x03  Transmit and receive path of the
                          corresponding channel are
                          enabled => full operation mode
                 */
  #if (STD_ON == CANIF_CANCM_SUPPORT)
  uint8 BatVolStatus; /*  Battery Voltage Status
                            0x00  Normal
                            0x01  Error
                        */
#endif
} CanIf_ControllerType;

/* Structure for CAN Driver */
typedef struct 
{
  /* Function to set ControllerMode ->Can_SetControllerMode */
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanSetControllerMode)(uint8 Controller, Can_ControllerStateType ModeType);
  #else
  P2FUNC(Can_ReturnType, CANIF_APPL_CODE, CanSetControllerMode)(uint8 Controller, Can_StateTransitionType ModeType);
  #endif

  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
       (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanGetControllerMode)
        (uint8 Controller,
         P2VAR(Can_ControllerStateType, AUTOMATIC, CANIF_APPL_DATA)
                                                             ControllerModePtr);
  #endif

  /* Function to Write CAN Data to Driver->Can_Write */
  /* @Trace: CanIf_SUD_DATATYPE_049 */
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanWrite) (Can_HwHandleType Hth,
                    P2CONST(Can_PduType, AUTOMATIC, CANIF_APPL_CONST) PduInfo);
  #else
  P2FUNC(Can_ReturnType, CANIF_APPL_CODE, CanWrite) (Can_HwHandleType Hth,
                    P2CONST(Can_PduType, AUTOMATIC, CANIF_APPL_CONST) PduInfo);
  #endif
  
  /* Function to check wakeup occured->Can_CheckWakeup */
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanCheckwakeup) (uint8 controller);
  #else
  P2FUNC(Can_ReturnType, CANIF_APPL_CODE, CanCheckwakeup) (uint8 controller);
  #endif


  #if (STD_ON == CANIF_SET_BAUDRATE_API)
  /* Function to check wakeup occured->Can_ChangeBaudrate */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanSetBaudrate) (uint8 controller,
      CONST(uint16, CANIF_CONST) Baudrate);
  #endif

  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
       (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  /* Function to get controller error state */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanGetControllerErrorState)
        (uint8 controller,
         P2VAR(Can_ErrorStateType, AUTOMATIC, CANIF_APPL_DATA) ErrorStatePtr);
  #endif

  #if (STD_ON == CANIF_PUBLIC_ICOM_SUPPORT)
  /* Function to change the Icom Configuration of a CAN controller */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanSetIcomConfiguration)
        (uint8 ControllerId, VAR(IcomConfigIdType, CANIF_VAR) ConfigurationId);
  #endif

  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
       (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_FOUR))
  /* Function to get the Rx error counter of a CAN controller */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanGetControllerRxErrorCounter)
        (uint8 ControllerId,
         P2VAR(uint8, AUTOMATIC, CANIF_VAR) RxErrorCounterPtr);

  /* Function to get the Tx error counter of a CAN controller */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanGetControllerTxErrorCounter)
        (uint8 controller,
         P2VAR(uint8, AUTOMATIC, CANIF_VAR) TxErrorCounterPtr);
  #endif
} CanIf_CanDriverType;

/* Function pointer to CanTrcv Driver */
typedef struct 
{
  /* Function to set CanTrcv Mode ->CanTrcv_SetOpMode */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanTrcvSetOpMode)
                       (uint8 Transceiver, CanTrcv_TrcvModeType TrcvWakeupMode);
  /* Function to get CanTrcv Mode ->CanTrcv_GetOpMode */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanTrcvGetOpMode)
                      (uint8 Transceiver, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC,
                                                        CANIF_APPL_DATA)OpMode);
  #if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
  /* Function to get CanTrcv Mode ->CanTrcv_GetBusWuReason */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanTrcvGetBusWuReason)
  (uint8 Transceiver, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC,
                                               CANIF_APPL_DATA)TrcvWuReasonPtr);
  /* Function to set CanTrcv Wakeup Mode ->CanTrcv_SetWakeupMode */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanTrcvSetWakeupMode)
                 (uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);
  /* Function to check wakeup occured->CanTrcv_CheckWakeup  */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CanTrcvCheckWakeup)
                                                            (uint8 Transceiver);
  #endif
  #if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_PN_SUPPORT))
  /* Function to Clear TrcvWufFlag */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, ClearTrcvWufFlag)(uint8 Transceiver);

  /* Function to Clear TrcvWufFlag */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, CheckWakeFlag)(uint8 Transceiver);
  #endif
} CanIf_CanTrcvDriverType;

/* Structure for Rx callback user */
typedef struct 
{
  /* Callback function for Rx Indication */
  P2FUNC(void, CANIF_APPL_CODE, RxIndication)(PduIdType TargetRxPduId,
                    P2CONST(PduInfoType, AUTOMAITC, CANIF_CONST) PduInfoPtr);
} CanIf_RxCbkUserType;

/* Structure for Tx callback user */
typedef struct 
{
  /* Transmit Function for different callback user */
  P2FUNC(void, CANIF_APPL_CODE, TxCbkUser)(CanIf_TxPduIdType TargetPduId,
          Std_ReturnType result);
} CanIf_TxCbkUserType;

/* @Trace: SWS_CANIF_00883 */
#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)
/* Structure for Tx Trigger callback user */
typedef struct 
{
  /* Transmit Function for different trigger callback user */
  P2FUNC(Std_ReturnType, CANIF_APPL_CODE, pTxCbkTriggerUser)(PduIdType TxPduId,
                           P2CONST(PduInfoType, AUTOMAITC, CANIF_CONST) PduInfoPtr);
} CanIf_TxCbkTriggerUserType;
#endif /*#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)*/

/* Structure for Transmit Queue for Tx buffer
   This structure need not be generated by the tool */
struct Stag_CanIf_TxQueue
{
  struct Stag_CanIf_TxQueue *TxNextQueue;
  Can_IdType CanId;    /* Statically configured CanId */
  PduIdType TxLPduId;    /* Transmit Pdu Id */
  uint8* TxBufferPtr;      /* Pointer to Tx data*/
  #if (CANIF_CANFD_SUPPORT == STD_ON)
  uint8 TxBuffer[CANIF_CANFD_MAX_LENGTH];   /* RAM Pointer to the Buffer Area */
  #else
  uint8 TxBuffer[CANIF_EIGHT];       /* RAM Pointer to the Buffer Area */
  #endif
  uint8 Dlc;    /* Data length Code*/
};

typedef struct Stag_CanIf_TxQueue CanIf_TxQueueType; 

typedef P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) (CanIf_TxQueueTypePtr);

/* @Trace: CanIf_SUD_DATATYPE_044 */
typedef struct 
{
  /* Pointer to First Queue to be transmitted */
  P2VAR(CanIf_TxQueueTypePtr, AUTOMAITC, CANIF_VAR) TxFirstQueue;
  Can_HwHandleType HthId;         /* HTH start Index */
  CanIf_TxQueueSizeType QueueIndex;   /* Queue Start index */
  CanIf_TxQueueSizeType NoOfTxQueue;    /* number of TxQueue */
} CanIf_TxBufferType;


/* Structure for pointers for arrays relevant to Tx Buferring Functionality */
typedef struct 
{
  /* Pointer to tx buffer arrays */
  P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) TxBuffer;
  /* Pointer to tx queue arrays */
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_CONST) TxQueue;
  /* Pointer to PduToQueueMappting arrays */
  P2VAR(CanIf_TxPduIdType,AUTOMATIC, CANIF_CONST) TxPduToQueueMapping;
  /* Pointer to basic tx pdu mapping arrays */
  P2CONST(uint16, AUTOMATIC, CANIF_CONST) BasicTxPduIndex;

} CanIf_TxBufferPtrsType;

/* @Trace: SWS_CANIF_00144 */ /* CanIf_ConfigType*/
typedef struct 
{
  /* pointe to array CanIf_ControllerConfig in PostBuild */
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) pCanIf_ControllerConfig;

  #if ((CANIF_DEV_ERROR_DETECT == STD_ON) || CANIF_MULTIPLE_CANDRV_SUPPORT )
  /* pointe to array CanIf_HrhInit in PostBuild */
  P2CONST(CanIf_HrhInitType, AUTOMATIC, CANIF_CONST) pCanIf_HrhInit;
  #endif

  /* pointe to array CanIf_RxLpdu in PostBuild */
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) pCanIf_RxLpdu;

  PduIdType NoofRxLpdu; /* Number of Rx Lpdu */

  /* pointe to array CanIf_Hrh in PostBuild */
  P2CONST(CanIf_HrhType, AUTOMATIC, CANIF_CONST) pCanIf_Hrh;

  #if (CANIF_TX_QUEUE == STD_ON)
  /* pointe to array CanIf_TxBuffer in PostBuild */  
  P2CONST(CanIf_TxBufferType,AUTOMATIC, CANIF_CONST) pCanIf_TxBuffer;

  uint16 Noofbuffer; /* Number of Tx buffer */
  uint16 Noofqueue;  /* Number of Tx Queue */
  uint16 NoofBasictxlpdu; /* Number of Tx Basic */
  #endif

  /* pointe to array CanIf_TxLpdu in PostBuild */ 
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) pCanIf_TxLpdu;

  uint16 NoofTxLpdu; /* Number of Tx Lpdu */
 
  /* pointe to array CanIf_HrhMapArray in PostBuild */ 
  P2CONST(uint16,AUTOMATIC, CANIF_CONST) pCanIf_HrhMapArray;

  uint16 NoofHrh; /* Number of Hrh */

  /* pointe to array CanIf_TxBasicPduIndexMapping in PostBuild */ 
  P2CONST(uint16,AUTOMATIC, CANIF_CONST) pCanIf_TxBasicPduIndexMapping;

  #if (STD_ON == CANIF_SETDYNAMICTXID_API)
  /* pointe to array CanIf_CanId in PostBuild */ 
  P2VAR(Can_IdType,AUTOMATIC, CANIF_VAR) pCanIf_CanId;

  PduIdType NoofdynamicCanId; /* Number of Dynamic CanId */
  #endif

  uint16 NoofRxnotify; /* Number of Rx notify Id */
} CanIf_ConfigType;

typedef signed int CanIf_PtrSize;
typedef P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) (CanIf_RxLpduTypePtr);
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANIF_INTTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
