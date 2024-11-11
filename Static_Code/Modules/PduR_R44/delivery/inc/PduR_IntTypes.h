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
**  SRC-MODULE: PduR_IntTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of PduR Structure definitions                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 1.0.9.0_HF1 24-May-2024   Mj Kim      CP44-8274                            **
** 1.0.5       11-Nov-2022   HaoTA4      CP44-383                             **
** 1.0.4       11-Aug-2022   PhucNHM     CP44-635                             **
** 1.0.3       07-Dec-2021   PhucNHM     R44-Redmine #22235                   **
** 1.0.2       05-Oct-2021   PhucNHM     R44-Redmine #20586                   **
** 1.0.1       22-Jun-2021   PhucNHM     R44-Redmine #18951                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/
#ifndef PDUR_INTTYPES_H
#define PDUR_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR_Cfg.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00802*/
#include "Det.h"                  /* DET module header */
/* @Traceability END -- SRS: SWS_PduR_00802 */
#if (PDUR_ZERO_COST_OPERATION == STD_ON)
#include "PduR_Incl.h"            /* Dependent module Header files*/
#endif
#include "PduR_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation */

/* @Trace: PduR_SUD_MACRO_004 */
/* Macro for upper layer indication */
#define PDUR_UPPER_LAYER                      ((uint16)0xFFFF)

/* Macro for buffer unavailable condition */
#define PDUR_GATEWAY_NOBUFFER                 ((uint16)0xFFFE)

/* Macro for invalid condition */
#define PDUR_INVALID_BUFFER                   ((uint16)0xFFFF)

/* Macro for D fifo */
#define PDUR_D_FIFO                           0x40

/* Macro for TT fifo */
#define PDUR_TT_FIFO                          0x80

/* Macro for TT fifo */
#define PDUR_FIFO                             0x40

/* Buffer mask */
#define PDUR_BUFFER_MASK                      0xC0

/* Mask for multicast transmission */
#define PDUR_MULTICAST_MASK                   0x80

/* Mask for gateway condition */
#define PDUR_GATEWAY_MASK                     ((uint8)0x40)

/* Mask for nongateway condition */
#define PDUR_NONGATEWAY_MASK                  ((uint8)0xC0)

/* Mask for upper layer */
#define PDUR_UPPERLAYER_MASK                  ((uint8)0x80)

/* Mask for target index */
#define PDUR_IFCONF_TARGET_INDEX_MASK         ((uint8)0x0F)

/* The following mask is used in case of Uptransmit */
/* For masking the value from structure element - ucFraTIOrNoOfRoute */
#define PDUR_TARGET_INDEX_MASK                ((uint8)0x3F)

/* Mask for target index */
#define PDUR_TPCOPYTX_TARGET_INDEX_MASK       ((uint8)0x07)

/* Mask for target index */
#define PDUR_TPCONF_TARGET_INDEX_MASK         ((uint8)0x07)

/* Mask for number of routes */
#define PDUR_NOOFROUTE_MASK                   ((uint8)0x3F)

/* Macro for zero */
#define PDUR_ZERO                             0x00

/*Macro for one */
#define PDUR_ONE                              0x01

/* Macro for true condition  */
#define PDUR_TRUE                             PDUR_ONE

/* Macro for false condition  */
#define PDUR_FALSE                            PDUR_ZERO

/* Macro for invalid condition */
#define PDUR_INVALID                          ((uint8)0xFF)

/* Macro for undefined condition */
#define PDUR_UNDEFINED                        ((uint16)0xFFFF)

/* Macro for TP Layer */
#define PDUR_TP_LAYER                         ((uint8)0x40)

/* Macro for zero length */
#define PDUR_LENGTH_ZERO                      ((uint8)0x00)

/* Macro for bit mask length */
#define PDUR_BITMASK_UINT8                    ((uint8)0x08)
/*
 * Lower layer communication interface module
 * Macro's for ModuleType present in structure.
 */

/*Lower layer communication interface module for CanIf*/
#define PDUR_CANIF                            ((uint8)0x00)

/*Lower layer communication interface module for CanNm*/
#define PDUR_CANNM                            ((uint8)0x01)

/*Lower layer communication interface module for FrIf*/
#define PDUR_FRIF                             ((uint8)0x03)

/*Lower layer communication interface module for FrNm*/
#define PDUR_FRNM                             ((uint8)0x04)

/*Lower layer communication interface module for LinIf*/
#define PDUR_LINIF                            ((uint8)0x05)

/*Lower layer communication interface module for SoAdIf*/
#define PDUR_SOADIF                           ((uint8)0x06)

/*Lower layer communication interface module for Cdd*/
#define PDUR_CDDIF                            ((uint8)0x07)

/*Lower layer communication interface module for SecOC*/
#define PDUR_SECOCLOIF                        ((uint8)0x08)

/*Lower layer communication interface module for UdpNm*/
#define PDUR_UDPNM                            ((uint8)0x09)

/*Lower layer communication interface module for DoIP*/
#define PDUR_DOIPIF                           ((uint8)0x0A)

/*Lower layer transport protocol module for EthDiag_Gateway*/
#define PDUR_ETHDIAG_GATEWAY                  ((uint8)0x20)

/*Lower layer transport protocol module for EthDiag_ByPass*/
#define PDUR_ETHDIAG_BYPASS                   ((uint8)0x21)

/*Lower layer transport protocol module for CDD_RouterIF*/
#define PDUR_CDD_ROUTERIF                     ((uint8)0x22)

/*Lower layer transport protocol module for CDD_IPC_IF*/
#define PDUR_CDD_IPC_IF                       ((uint8)0x23)
/*
 * Lower layer transport protocol module
 * Macro's for ModuleType present in structure.
 */

/*Lower layer transport protocol module for CanTp*/
#define PDUR_CANTP                            ((uint8)0x0B)

/*Lower layer transport protocol module for J1939Tp*/
#define PDUR_J1939TP                          ((uint8)0x0C)

/*Lower layer transport protocol module for FrTp*/
#define PDUR_FRTP                             ((uint8)0x0D)

/*Lower layer transport protocol module for LinTp*/
#define PDUR_LINTP                            ((uint8)0x0E)

/*Lower layer transport protocol module for SoAdTp*/
#define PDUR_SOADTP                           ((uint8)0x0F)

/*Lower layer transport protocol module for Cdd*/
#define PDUR_CDDTP                            ((uint8)0x10)

/*Lower layer transport protocol module for DoIP*/
#define PDUR_DOIPTP                           ((uint8)0x11)

/*Lower layer transport protocol module for SecOC*/
#define PDUR_SECOCLOTP                        ((uint8)0x14)

/*Lower layer transport protocol module for SomeIpTpLoTp*/
#define PDUR_SOMEIPTPLOTP                     ((uint8)0x1D)

/*Lower layer transport protocol module for EthDiag_Node*/
#define PDUR_ETHDIAG_NODE                     ((uint8)0x1F)

/*Lower layer transport protocol module for CDD_RouterTP*/
#define PDUR_CDD_ROUTERTP                     ((uint8)0x20)

/*Lower layer transport protocol module for CDD_IPC_TP*/
#define PDUR_CDD_IPC_TP                       ((uint8)0x21)

/*
 * Upper layer module
 * Macro's for ModuleType present in structure.
 */

/*Upper layer module for Com*/
#define PDUR_COM                              ((uint8)0x02)

/*Upper layer module for Dcm*/
#define PDUR_DCM                              ((uint8)0x12)

/*Upper layer module for IpduM*/
#define PDUR_IPDUM                            ((uint8)0x13)

/*Upper layer module for Dlt*/
#define PDUR_DLT                              ((uint8)0x15)

/*Upper layer module for Cdd*/
#define PDUR_CDD                              ((uint8)0x16)

/*Upper layer module for SecOC*/
#define PDUR_SECOCUP                          ((uint8)0x17)

/*Upper layer module for J1939RM*/
#define PDUR_J1939RM                          ((uint8)0x18)

/*Upper layer module for J1939RMIF*/
#define PDUR_J1939RMIF                        ((uint8)0x19)

/*Upper layer module for J1939RMTP*/
#define PDUR_J1939RMTP                        ((uint8)0x1A)

/*Upper layer module for J1939DCM*/
#define PDUR_J1939DCM                         ((uint8)0x1B)

/*Upper layer module for LdComIf*/
#define PDUR_LDCOM                            ((uint8)0x1C)

/*Upper layer module for SomeIpTpUpIf*/
#define PDUR_SOMEIPTPUPIF                     ((uint8)0x1E)

/* The following are the macros used for the Receive states in PduR for TP */
/* Reception yet to be started */
#define PDUR_RX_YETTOSTART                    ((uint8) 0x00)
/* Reception has been completed. */
#define PDUR_RX_COMPLETED                     ((uint8) 0x01)
/* PduR is waiting for an Acknowledgement */
#define PDUR_RX_ACKNOWLEDGE                   ((uint8) 0x02)
/* Reception has been started */
#define PDUR_RX_START                         ((uint8) 0x03)
/* Reception is in progress */
#define PDUR_RX_IN_PROGRESS                   ((uint8) 0x04)
/* PduR in state start transmit when in-proress reception */
#define PDUR_RX_TX_COMPLETED                  ((uint8) 0x05)
/* PduR in state not start transmit when in-proress reception */
#define PDUR_RX_TX_NOT_COMPLETED              ((uint8) 0x06)
/* PduR in state start transmit with result OK when in-proress reception */
#define PDUR_RX_TX_COMPLETED_RESULT_OK        ((uint8) 0x07)
/* Transmission is single-frame */
#define PDUR_TRANSMITSSION_SINGLE_FRAME       ((uint8) 0x00)
/* Transmission is multi-frame */
#define PDUR_TRANSMITSSION_MULTI_FRAME        ((uint8) 0x01)
/*
 * Type definition for function pointer.
 */
/* @Trace: PduR_SUD_DATATYPE_008 */
 /* Typedefine for Interface RxIndication function */
typedef P2FUNC(void, PDUR_APPL_CODE, PduRIfReceive)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pPduInfoptr);

/* @Trace: PduR_SUD_DATATYPE_009 */
/*Typedefine for Interface Trigger Transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRIfTriggerTx)
  (PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) pPduInfoptr);

/* @Trace: PduR_SUD_DATATYPE_010 */
/*Typedefine for Interface TxConfirmation function*/
typedef P2FUNC(void, PDUR_APPL_CODE, PduRIfTxConf)
  (const PduIdType id, Std_ReturnType result);

/* @Trace: PduR_SUD_DATATYPE_011 */
/*Typedefine for Interface transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRIfTransmitfun)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pPduInfoptr);

/* @Trace: PduR_SUD_DATATYPE_012 */
/*Typedefine for Interface Cancel transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRIfCancelTransmitfun)
  (PduIdType id);

/* @Trace: PduR_SUD_DATATYPE_013 */
/*Typedefine for Tp CopyTx Data function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpCopyTxData)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) info,
  P2CONST(RetryInfoType, AUTOMATIC, PDUR_VAR) retry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) length);

/* @Trace: PduR_SUD_DATATYPE_014 */
/*Typedefine for TxConfirmation function*/
typedef P2FUNC(void, PDUR_APPL_CODE, PduRTpConfirm)
  (PduIdType id, Std_ReturnType result);

/* @Trace: PduR_SUD_DATATYPE_015 */
/*Typedefine for Tp Cancel Reason function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRTpCancel)
  (PduIdType id);

/* @Trace: PduR_SUD_DATATYPE_016 */
/*Typedefine for RxTp Cancel Reason function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRRxTpCancel)
  (PduIdType id);

/* @Trace: PduR_SUD_DATATYPE_017 */
/*Typedefine for Tp StartOf Reception function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpStReception)
  (PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) info,
  PduLengthType tpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr);

/* @Trace: PduR_SUD_DATATYPE_018 */
/*Typedefine for Tp Copy RxData function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpCopyRxData)
  (PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) info,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) length);

/* @Trace: PduR_SUD_DATATYPE_019 */
/*Typedefine for Tp Transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRTpTransmit)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pPduInfoptr);

/* @Trace: PduR_SUD_DATATYPE_020 */
/*Typedefine for Tp RxIndication function*/
typedef P2FUNC(void, PDUR_APPL_CODE, PduRTpReceive)
  (PduIdType id, Std_ReturnType result);

/* @Trace: PduR_SUD_DATATYPE_021 */
typedef struct PduR_TxQueueType
{
  /* Index to PduInfoPtr Generation Tool should allocate pointer to
   PduInfoType. This parameter is used to store the data and length
   information for gatewayed PDU */
  VAR(PduInfoType, PDUR_VAR) PduInfoPtr;
  /* Next pointer */
  /* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "use type struct PduR_TxQueueType in define struct PduR_TxQueueType to easy implementation for fifo queue buffer" */
  P2VAR(struct PduR_TxQueueType, AUTOMATIC, PDUR_VAR) Next; 
  #if (PDUR_SHARED_GW_IF_BUFFER == STD_ON)
  /* TargetPduId. Store TxPduId handles by TxConfirmation when resolving FIFO */
  PduIdType TargetPduId;
  #endif
  /* Status for free buffer */
  PduR_Buffer_StateType FreeBuffer;
} PduR_TxQueueType;

/* @Trace: PduR_SUD_DATATYPE_022 */
/* Multicast Gateway Tp PDU */
typedef struct
{
  /* Result */
  Std_ReturnType Result;
  /* Confirmation Status */
  uint8 ConfStatus;
}PduR_MulticastTxInfo;

/**
 * @typedef PduR_TxBuffer
 *
 * This structure is require to be generated in case of interface to interface
 *   gateway
 */
/* @Trace: PduR_SUD_DATATYPE_023 */
typedef struct
{
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  /* Index to PduInfoPtr Generation Tool should allocate pointer to
   PduInfoType. This parameter is used to store the data and length
   information for gatewayed PDU */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) SduPtr;

  #if (PDUR_DEFAULTVALUE_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) SduDefaultValuePtr;
  #endif

  /* Actual length is copied */
  PduLengthType SduLengthUpdate;
  /* Pointer to store Meta Data of PduInforPtr */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) MetaPtr;

  #if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) FirstQueuePtr;
  /* Total length of buffer */
  PduLengthType TotalLength;
  /* Pointer to store Index of Sdu buffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) IndexSduPtr;

  #if (PDUR_META_DATA_SUPPORT == STD_ON)
  /* Pointer to store Index of Sdu buffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) IndexMetaPtr;
  #endif
  /* TailLength of tx queue buffer */
  PduLengthType TailLength;
  /* HeadLength of tx queue buffer */
  PduLengthType HeadLength;
  /* CurrentDepth of the Tx Buffer */
  uint8 CurrentDepth;
  #endif
  /* Depth of the Tx Buffer */
  uint8 FIFODepth;
} PduR_TxBuffer;

/* @Trace: PduR_SUD_DATATYPE_024 */
 /* PduR_LoGWRxIndication */
typedef struct
{
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  /* Updated Length of PDU */
  PduLengthType PduLength;

  /* Updated Length of Meta Data PDU */
  #if (PDUR_META_DATA_SUPPORT == STD_ON)
  uint8 MetaDataLength;
  #endif
  /* PDUR_GATEWAY_NOBUFFER and PDUR_UPPER_LAYER */
  uint16 TxBufferIndex;

  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  uint16 TxQueueIndex;
  #endif
  /* TargetPduId. Generation tool should provide the handle id of the target
   *   module if configured. In case, handle id of the target module is not
   *   configured then the handle name should be considered */
  PduIdType TargetPduId;

  /* First two bits are set for type of Buffer*/
  /* 0x40 - Direct FIFO Buffer
   * 0x80 - TT -FIFO Buffer
   Rest six bits gives TargetIndex */

  uint8 TargetIndexBufType;
} PduR_LoGWRxIndication;

/*Typedefine for Rx Indication Callout function*/
typedef P2FUNC(boolean, PDUR_APPL_CODE, PduRRxIndCallOut)
  (PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) PduInfoPtr);

/**
 * typedef PduR_LoRxIndication
 *
 * This structure is require to be generated in case of receive indication
 *   from interface
 */
/* @Trace: PduR_SUD_DATATYPE_025 */
typedef struct
{
  #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) GWIfPdu;
  #endif
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* PduR group Mask Value for Pdu*/
  uint16 GroupMaskValue;
  #endif
  /* Incase of non gateway ucTargetIndex shall contain target id*/
  #if (PDUR_IF_RECEIVE_SUPPORT == STD_ON)
  PduIdType UpTargetPduId;
  #endif
  /* Incase of non gateway ucTargetIndex shall point to function pointer index
   *   In case of gateway without multicast=> 0x40
   *   In case of gateway with multicast => 0x80 | no or route
   *   Index for Receive or Gateway  Or Multicast Gateway */
  uint8 TargetIndexOrRoutePDU;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ModuleType;
  #endif

  PduRRxIndCallOut pFuncPduRCallOut;
}PduR_LoRxInd;

/**
 * typedef PduR_MulticastTxPdu
 *
 * This structure is require to be generated in case of Multicast Tx Pdu
 */
/* @Trace: PduR_SUD_DATATYPE_026 */
typedef struct
{
  P2VAR(PduR_MulticastTxInfo, AUTOMATIC, PDUR_VAR) MulticastTxInfo;
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  /* TargetPduId. Generation tool should provide the handle id of the target
   * module if configured. In case, handle id of the target module is not
   * configured then the handle name should be considered */
  PduIdType TargetPduId;
  /* Target Index for If Transmit, If Rx Indication */
  uint8 TargetIndex;

} PduR_MulticastTxPdu;

/**
 * typedef PduR_UpTx
 *
 * This structure is require to be generated in case of Up Transmit (Com /IpduM)
 */
/* @Trace: PduR_SUD_DATATYPE_027 */
typedef struct
{
  /* Pointer to MulticastTpPdu or MultiCastTxPdu structure */
  P2CONST(void, AUTOMATIC, PDUR_CONST) MulticastTpOrTxPdu;
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  /* In case of single cast will provide the handle id of the target
     module configured */
  PduIdType LoTargetPduId;
  /* This element indicates the frame type(Fra) - Tp or Interface
   * 6th bit will be set if the frame is Tp and 7th bit will be set
   * in case of multicast transmission. */
  uint8 FraTIOrNoOfRoute;
  /*
   * No of Tx confimations configured
   * Count of PduRTransmissionConfirmation
   */
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  uint8 TxConfirmMask;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ModuleType;
  #endif

} PduR_UpTx;

/**
 * typedef PduR_LoTxConfirmation
 *
 * This structure is require to be generated in case of transmit confirmation
  and trigger transmit from interface
*/
/* @Trace: PduR_SUD_DATATYPE_028 */
typedef struct
{
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  P2VAR(PduR_MulticastTxInfo, AUTOMATIC, PDUR_VAR) MulticastTxInfo;
  #endif
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  /* Pointer to Tx buffer */
  uint16 TxBufferIndex;
  /* TargetPduId. Generation tool should provide the handle id of the target
  *  module if configured */
  /* Id need to be generated from PduRSrcPduRef of upper layer*/
  PduIdType TargetPduId;
  /*
  * Index for Transmit and Transmit Confirmation
  * In case of Gateway, ucTargetIndex shall be 0x40 | Index
  */
  uint8 TargetIndex;
  #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
        (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
  /* Type Of Buffer
     0xFF: No Buffer
     0x00: Single Buffer
     0x40: D-FIFO
     0x80: T-FIFO */
  uint8 BufferType;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ModuleType;
  #endif
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  uint8 TxConfirmMask;
  #endif
  /* 0 - Indicates confirmation is not configured for the specific destination
   1 - Indicates confirmation is configured for the specific destination */
  boolean LoTxConfirmation;
  #if (PDUR_SHARED_GW_IF_BUFFER == STD_ON)
  /* 0 - Route is not sharing a single cast FIFO buffer
   * 1 - Route is sharing a single cast FIFO buffer */
  boolean BufferShared;
  #endif
} PduR_LoTxConf;

/* @Trace: PduR_SUD_DATATYPE_029 */
typedef struct PduR_TpQueueType
{
  /* PduInfoPtr of fifo buffer */
  VAR(PduInfoType, PDUR_VAR) PduInfoPtr;
  /* Available length of fifo buffer */
  PduLengthType AvailLength;
  /* Copied length of fifo buffer */
  PduLengthType CopiedLength;
  /* Requested length of fifo buffer */
  PduLengthType ReqLength;
  /* Rx PduId of fifo buffer */
  PduIdType RxPduId;
  /* Rx State of fifo buffer */
  uint8 RxState;
  /* Status free of fifo buffer */
  boolean FreeBuffer;
  /* Index of fifo buffer */
  uint16 IndexFifo;
  /* Index list of fifo buffer */
  uint16 IndexList;
  #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
  /* Status use pool of fifo buffer */
  boolean PoolStatus;
  /* index pool of fifo buffer */
  uint8 IndexPool;
  #endif
  /* TxConfirm of fifo buffer */
  uint8 TxConfirm;
  /* Next pointer of fifo buffer */
  /* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "use type struct PduR_TxQueueType in define struct PduR_TxQueueType to apply link list for implement fifo queue buffer" */
  P2VAR(struct PduR_TpQueueType, AUTOMATIC, PDUR_VAR) Next; 
} PduR_TpQueueType;

/* @Trace: PduR_SUD_DATATYPE_030 */
typedef struct
{
  /* Length of copied length */
  uint8 IndexPool;
  /* Length of available length */
  boolean PoolStatus;
} PduR_TpPool;

/* @Trace: PduR_SUD_DATATYPE_031 */
typedef struct
{
  /* Available length of single buffer */
  PduLengthType AvailLength;
  /* Requested length of single buffer */
  PduLengthType ReqLength;
  /* Copied length of single buffer */
  PduLengthType CopiedLength;
  /* Rx state of single buffer */
  uint8 RxState;
  /* Status free of fifo buffer */
  boolean FreeBuffer;
  #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
  /* Status use pool of single buffer */
  boolean PoolStatus;
  /* IndexPool of single buffer */
  uint8 IndexPool;
  #endif
  /* TxConfirm of single buffer */
  uint8 TxConfirm;
} PduR_TpSingleBuffer;

/* @Trace: PduR_SUD_DATATYPE_032 */
typedef struct
{
  /* SduPtr of Pool buffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) SduPtr;
  /* PduMaxLength of Pool buffer */
  PduLengthType PduMaxLength;
  /* State of Pool buffer */
  boolean State;
}PduR_PoolBuffer;

/**
 * @typedef PduR_TpBuffer
 *
 * This structure is require to be generated in case of interface to interface
 *   gateway
 */
/* @Trace: PduR_SUD_DATATYPE_033 */
typedef struct
{
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  /* SduPtr of PduR buffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) SduPtr;
  /* Pointer to store Meta Data of PduInforPtr */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) MetaPtr;
  /* TotalLength of routing path's buffer */
  PduLengthType TotalLength;
  /* struct variable for single buffer */
  P2VAR(PduR_TpSingleBuffer, AUTOMATIC, PDUR_VAR) SinBufPtr;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) FirstQueuePtr;
  /* Pointer to store Index of Sdu buffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) IndexSduPtr;

  #if (PDUR_META_DATA_SUPPORT == STD_ON)
  /* Pointer to store Index of Sdu buffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) IndexMetaPtr;
  #endif
  /* TailLength of tx queue buffer */
  PduLengthType TailLength;
  /* HeadLength of tx queue buffer */
  PduLengthType HeadLength;
  /* CurrentDepth of the Tx Buffer */
  uint8 CurrentDepth;
  /* Depth of the Tx Buffer */
  uint8 FIFODepth;
  #endif
} PduR_TpBuffer;

/* Multicast Gateway Tp PDU */
/* @Trace: PduR_SUD_DATATYPE_053 */
typedef struct
{
  /* Result */
  Std_ReturnType Result;
  /* Confirmation Status */
  uint8 ConfStatus;
  /* First destination lower */
  boolean FirstLower;
}PduR_MulticastTpInfo;

/* Multicast Gateway Tp PDU */
/* @Trace: PduR_SUD_DATATYPE_034 */
typedef struct
{
  /* This pointer gives index to the TpBuffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) RamArea;
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 GroupMaskValue;
  #endif
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  /* Tp Threshold value */
  uint16 TpThreshold;
  #endif

  #if(PDUR_META_DATA_SUPPORT == STD_ON)
  /* Updated Length of Meta Data */
  PduLengthType MetaDataLength;
  #endif
  /* PDUR_GATEWAY_NOBUFFER and PDUR_UPPER_LAYER */
  uint16 TxBufferIndex;

  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  uint16 TxQueueIndex;
  #endif
  /* TargetPduId. Generation tool should provide the handle id of the target
    module if configured. */
  PduIdType TargetPduId;
  /* First two bits are set for type of Buffer*/
  /* 0x00 - Single Buffer
   * 0x40 - FIFO Buffer
   * 0x80 - Upper Buffer
   Rest six bits gives TargetIndex */
  uint8 TargetIndexBufType;
} PduR_GWRxTpPdu;

/* Structure for Tp Rx Indication */
/* @Trace: PduR_SUD_DATATYPE_035 */
typedef struct
{
  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) GWRxTpPdu;
  #endif
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* PduR group Mask Value for Pdu*/
  uint16 GroupMaskValue;
  #endif
  /* Target Layer ID */
  PduIdType UpTargetPduId;
  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) &&\
  (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON)
  /* Cancel receive Low target Id */
  PduIdType LoRxHandleId;
  #endif
  /* Target Index for Tp Transmit
    0x40 in case of Singlecast Gateway
    0x80 | no of route in case of multicast gateway */
  uint8 TargetIndexOrNoOfRoute;

  /* Source Index for cancel receive */
  #if (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON)
  uint8 SourceIndex;
  #endif

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /* Module type i.e. PDUR_<Msn> */
  uint8 ModuleType;
  #endif
}PduR_TpRxIndication;

/**
 * typedef PduR_MulticastTpPdu
 *
 * This structure is require to be generated in case of Tp Multicast
 */
/* @Trace: PduR_SUD_DATATYPE_036 */
typedef struct
{
  /* Multicast Tp Info Index */
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) MulticastTpInfo;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
 /* PduR group Mask Value for Pdu*/
  uint16 GroupMaskValue;
  #endif

  /* ddTargetPduId. Generation tool should provide the handle id of the target
    module configured. */
  PduIdType TargetPduId;

  /* Target Index for Tp Transmit, Tp Cancellation */
  uint8 TargetIndex;

  /* Count of PduRTransmissionConfirmation */
  uint8 TpConfirmMask;
} PduR_MulticastTpPdu;


/* Structure for Tp Copy Tx Buffer */
/* @Trace: PduR_SUD_DATATYPE_037 */
typedef struct
{
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) MulticastTpInfo;
  #endif

  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  /* Number of bytes is copied by lower module  */
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) RamArea;

  /* Multi-frame Status  */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) RamAreaFrame;
  #endif
  /* PDUR_GATEWAY_NOBUFFER and PDUR_UPPER_LAYER */
  uint16 TxBufferIndex;

  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* PduR group Mask Value for Pdu*/
  uint16 GroupMaskValue;
  #endif
  #if (PDUR_MULTICAST_GATEWAY_TP_FIFO_SUPPORT == STD_ON)
  /* Index for struct LoRxIndication */
  uint8 RxPduIndex;
  #endif
  /* TargetPduId handle id of the target module configured,
   Id need to be generated from PduRSrcPduRef of upper layer */
  PduIdType UpTargetPduId;
  /* 1. Target Index in case Non_Gateway case
     2. 0x40 | Target index in case of singlecast gateway
     3. 0x80 | Target index in case of multicast gateway */
  uint8 TargetIndex;
  /* Mask for Tx Confirmation */
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  uint8 TxCnfrmStsMask;
  #endif

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ModuleType;
  #endif
} PduR_TpCopyTxDataBuf;

/* typedef PduR_LoTxDestination */
/* @Trace: PduR_SUD_DATATYPE_051 */
typedef struct
{
  /* Pointer to PduR_LowIfTxConfirmation or PduR_LowTpCopyTxDataBuf structure */
  P2CONST(void, AUTOMATIC, PDUR_CONST) LoIfTpDestiantion;
  /* Check routing is interfaces */
  boolean IsInterfaceRouting;
} PduR_LoTxDestination;

/* typedef PduR_LoRxSource */
/* @Trace: PduR_SUD_DATATYPE_052 */
typedef struct
{
  /* Pointer to PduR_LowIfTxConfirmation or PduR_LowTpCopyTxDataBuf structure */
  P2CONST(void, AUTOMATIC, PDUR_CONST) LoIfTpSource;
  /* Check routing is interfaces */
  boolean IsInterfaceRouting;
} PduR_LoRxSource;

/* Structure for Transmit functions */
/* @Trace: PduR_SUD_DATATYPE_038 */
typedef struct
{
  PduRIfTransmitfun TargetLayer;
} PduR_IfTransmitFun;

/* Structure for Transmit cancel functions */
/* @Trace: PduR_SUD_DATATYPE_039 */
typedef struct
{
  PduRIfCancelTransmitfun TargetLayer;
} PduR_IfCancelTransmitFun;

/* Structure for If Receive functions */
/* @Trace: PduR_SUD_DATATYPE_040 */
typedef struct
{
  PduRIfReceive TargetLayer;
} PduR_IfReceive;

/* Structure for If Trigger Transmit functions */
/* @Trace: PduR_SUD_DATATYPE_041 */
typedef struct
{
  PduRIfTriggerTx TargetLayer;
} PduR_IfTriggerTx;

/* Structure for If Confirmation functions */
/* @Trace: PduR_SUD_DATATYPE_042 */
typedef struct
{
  PduRIfTxConf TargetLayer;
} PduR_IfConfirmation;

/* Structure for Transmit functions */
/* @Trace: PduR_SUD_DATATYPE_043 */
typedef struct
{
  PduRTpTransmit TargetLayer;
} PduR_TpTransmitFun;

/* Structure for Tp Receive functions */
/* @Trace: PduR_SUD_DATATYPE_044 */
typedef struct
{
  PduRTpReceive TargetLayer;
} PduR_TpReceive;

/* Structure for Tp Confirmation functions */
/* @Trace: PduR_SUD_DATATYPE_045 */
typedef struct
{
  PduRTpConfirm TargetLayer;
} PduR_TpConfirmation;

/* Structure for Tp Cancellation functions */
/* @Trace: PduR_SUD_DATATYPE_046 */
typedef struct
{
  PduRTpCancel TargetLayer;
} PduR_TpCancellation;

/* Structure for Rx Tp Cancellation functions */
/* @Trace: PduR_SUD_DATATYPE_047 */
typedef struct
{
  PduRRxTpCancel TargetLayer;
} PduR_RxTpCancellation;

/* Structure for Tp StartOfReception functions */
/* @Trace: PduR_SUD_DATATYPE_048 */
typedef struct
{
  PduRTpStReception TargetLayer;
} PduR_TpStartOfReception;

/* Structure for Tp CopyRxData functions */
/* @Trace: PduR_SUD_DATATYPE_049 */
typedef struct
{
  PduRTpCopyRxData TargetLayer;
} PduR_TpCopyRxData;

/* Structure for Tp CopyTxData functions */
/* @Trace: PduR_SUD_DATATYPE_050 */
typedef struct
{
  PduRTpCopyTxData TargetLayer;
} PduR_TpCopyTxData;

/* @Trace: PduR_SUD_CONSTVAR_001 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
/*This is an array of function pointers of <Lo>_Transmit*/
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfTransmitFun, PDUR_CONST)
  PduR_IfTransmitService[PDUR_TOTAL_COUNT_IF_TRANSMIT];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Lo>_CancelTransmit*/
#if (PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfCancelTransmitFun, PDUR_CONST)
  PduR_UpIfCancelTransmitService[PDUR_TOTAL_COUNT_IF_CANCEL_TRANSMIT];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_TriggerTransmit*/
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_IF_NORMAL_OPERATION == STD_ON))
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfTriggerTx, PDUR_CONST)
  PduR_LowIfTriggerTransmit[PDUR_TOTAL_COUNT_IF_TRIGGER];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_RxIndication*/
#if (PDUR_IF_RECEIVE_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfReceive, PDUR_CONST)
  PduR_LowIfReceive[PDUR_TOTAL_COUNT_IF_RECEIVE];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_TxConfirmation.*/
#if (PDUR_IF_NORMAL_OPERATION == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfConfirmation, PDUR_CONST)
  PduR_LowIfConfirmation[PDUR_TOTAL_COUNT_IF_CONFIRMATION];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_Transmit.*/
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpTransmitFun, PDUR_CONST)
  PduR_TpTransmitService[PDUR_TOTAL_COUNT_TP_TRANSMIT];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_StartOfReception*/
#if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpStartOfReception, PDUR_CONST)
  PduR_LowTpStartOfReception[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_RxIndication*/
#if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpReceive, PDUR_CONST)
  PduR_LowTpReceive[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_TxConfirmation.*/
#if (PDUR_TP_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpConfirmation, PDUR_CONST)
  PduR_LowTpConfirmation[PDUR_TOTAL_COUNT_TP_UP_TX];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_CancelTransmit.*/
#if ((PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON))
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCancellation, PDUR_CONST)
  PduR_UpTpCancellation[PDUR_TOTAL_COUNT_TP_CANCEL_TRANSMIT];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_CancelReceive.*/
#if (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_RxTpCancellation, PDUR_CONST)
  PduR_UpTpCancelReceive[PDUR_TOTAL_COUNT_TP_CANCEL_RECEIVE];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_CopyRxData.*/
#if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCopyRxData, PDUR_CONST)
  PduR_LowTpCopyRxData[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_CopyTxData.*/
#if (PDUR_TP_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCopyTxData, PDUR_CONST)
  PduR_LowTpCopyTxData[PDUR_TOTAL_COUNT_TP_UP_TX];
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
/* global variable is used as an array of FIFO buffer for TP.*/
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_PoolBuffer, PDUR_VAR)
  PduR_PoolPtr[PDUR_TP_POOLS_INDEX_COUNT];
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* global variable is used as an array of Pool buffer for TP.*/
#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TpPool, PDUR_VAR)
                              PduR_PoolVar;
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

/* global variable is used as an array of FIFO buffer for IF.*/
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TxQueueType, PDUR_VAR)
  PduR_IfTxQueue[PDUR_TX_BUFFER_INDEX_COUNT]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

/* global variable is used as an array of FIFO buffer for TP.*/
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TpQueueType, PDUR_VAR)
  PduR_TpTxQueue[PDUR_TP_BUFFER_INDEX_COUNT]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
/* global variable is used as an array of FIFO buffer for TP.*/
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduLengthType, PDUR_VAR)
  PduR_RamAreaTx[PDUR_TP_GATEWAY_LOW_DESTINATION_COUNT];
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if defined(PDUR_TP_SINGLE_BUFFER_ROUTING_COUNT)
#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TpSingleBuffer, PDUR_VAR) 
  PduR_TpSinBuf[PDUR_TP_SINGLE_BUFFER_ROUTING_COUNT]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if defined(PDUR_TP_GATEWAY_LOW_DESTINATION_COUNT)
#define PDUR_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/* Array for multicast tx confirmation count */
extern VAR(uint8, PDUR_VAR) 
  PduR_RamAreaFrame[PDUR_TP_GATEWAY_LOW_DESTINATION_COUNT]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
#endif

#if defined(PDUR_NUMBER_OF_BYTE_TP_BUFFER)
#define PDUR_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
extern VAR(uint8, PDUR_VAR) PduR_SduDataPtr [PDUR_NUMBER_OF_BYTE_TP_BUFFER]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
#endif

#if defined(PDUR_NUMBER_OF_BYTE_POOL_BUFFER)
#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint8, PDUR_VAR) PduR_SduPoolPtr[PDUR_NUMBER_OF_BYTE_POOL_BUFFER]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)

#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONST_INIT_8
#include "MemMap.h"
extern CONST(uint8, PDUR_VAR)
  PduR_GroupPathIdAtInit[PDUR_PATH_GROUP_MULTI_8_COUNT_MAX];
#define PDUR_STOP_SEC_CONST_INIT_8
#include "MemMap.h"
#endif

/*global variable is used as an array of buffer configured for Tp.*/
#if ((PDUR_SB_TP_BUFFER_SUPPORT == STD_ON) || \
  (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON))
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TpBuffer, PDUR_VAR)
  PduR_TpTxBuffer[PDUR_TP_BUFFER_ROUTING_COUNT]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of TxBuffer*/
#if ((PDUR_SB_TX_BUFFER_SUPPORT == STD_ON) || \
  (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TxBuffer, PDUR_VAR)
  PduR_IfTxBuffer[PDUR_TX_BUFFER_ROUTING_COUNT]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array which consists of the information regarding the data to be
copied to the lower layer in case of TP.*/
#if (PDUR_TP_TXCONFIRMATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCopyTxDataBuf, PDUR_CONST)
  PduR_LowTpCopyTxDataBuf[PDUR_TP_TXCONFIRMATION_MAXPDUID]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the CanIf, FrIf, LinIf and IpduM Tx
Confirmation.*/
#if(PDUR_LO_TXCONFIRMATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_LoTxConf, PDUR_CONST)
  PduR_LowIfTxConfirmation[PDUR_LO_TXCONFIRMATION_MAXPDUID]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the Tp Rx Indication.*/
#if(PDUR_TP_RXINDICATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpRxIndication, PDUR_CONST)
  PduR_LowTpRxIndication[PDUR_TP_RXINDICATION_MAXPDUID]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the Com and IpduM Transmit.*/
#if(PDUR_UP_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_UpTx, PDUR_CONST) PduR_UpIfTpTransmit[PDUR_UP_MAXPDUID]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if(PDUR_LO_RXINDICATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_LoRxInd, PDUR_CONST)
  PduR_LowRxIndication[PDUR_LO_RXINDICATION_MAXPDUID]; /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external variable is unique" */
#define PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#endif /* #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON) */

#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation */


#endif /* #ifndef PDUR_INTTYPES_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
