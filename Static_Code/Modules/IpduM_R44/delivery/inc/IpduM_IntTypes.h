/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_IntTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM Module                                          **
**                                                                            **
**  PURPOSE   : Provides Type Definitions used within the module              **
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
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef IPDUM_INTTYPES_H
#define IPDUM_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for pre-compile options */
#include "IpduM_Cfg.h"
/* Inclusion for Communication Stack Types definitions */
#include "ComStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define IPDUM_INTTYPES_AR_RELEASE_MAJOR_VERSION        (0x04u)
#define IPDUM_INTTYPES_AR_RELEASE_MINOR_VERSION        (0x04u)


#if(IPDUM_ENABLE_MODULE == STD_ON)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
typedef PduIdType IpduM_SizeType;

typedef signed int IpduM_PtrType;

#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
  typedef IPDUM_TXCONFINTTYPE IpduM_TxConfIntType;
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
  typedef IPDUM_TXREQINTTYPE IpduM_TxReqIntType;

#if (IPDUM_TX_IPDU == STD_ON)
  typedef IPDUM_TXMUXINTTYPE IpduM_TxMuxIntType;
  typedef IPDUM_TXPARTINTTYPE IpduM_TxPartIntType;
  typedef IPDUM_TXSEGMENTINTTYPE IpduM_TxMuxSegmentIntType;
#endif /* (IPDUM_TX_IPDU == STD_ON) */

#if (IPDUM_TX_CONTAINER == STD_ON)
  typedef IPDUM_TXCONTAINERINTTYPE IpduM_TxContainerIntType;
  typedef IPDUM_TXCONTAINEDINTTYPE IpduM_TxContainedIntType;
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */
#endif /* ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON)) */

#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
  typedef IPDUM_RXINDINTTYPE IpduM_RxIndIntType;

#if (IPDUM_RX_IPDU == STD_ON)
  typedef IPDUM_RXMUXINTTYPE IpduM_RxMuxIntType;
  typedef IPDUM_RXPARTINTTYPE IpduM_RxPartIntType;
#endif /* (IPDUM_RX_IPDU == STD_ON) */

#if (IPDUM_RX_CONTAINER == STD_ON)
  typedef IPDUM_RXCONTAINEDINTTYPE IpduM_RxContainedIntType;
  typedef IPDUM_RXCONTAINERINTTYPE IpduM_RxContainerIntType;
#endif /* (IPDUM_RX_CONTAINER == STD_ON) */
#endif /* ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON)) */

/* Structure of configured segments information for copying in bit */
typedef struct
{
  /* Pointer to IpduM buffer */
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) DstBufferPtr;

  /* Number of Byte */
  uint8 NoOfByte;

  #if (IPDUM_SEGMENT_BITFIELD == STD_ON)
  /* Source start mask value */
  uint8 SourceStartMask;

  /* Source end mask value */
  uint8 SourceEndMask;
  #endif

  /* Source byte Offset value */
  uint8 SourceOffset;
} IpduM_SegmentType;

#if (IPDUM_TX_IPDU == STD_ON)
/* Structure of configured TxPathway information */
typedef struct
{
  /* Pointer to PduInfoType structure */
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_CONST) PduInfoPtr;

  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  /* Length of MetaData */
  uint16 MetaDataLength;
  #endif

  /* Source pdu id from PDUR configuration reference (PduRSrcPduRef )*/
  PduIdType TxLoPduId;

  /* Initial Dynamic id for TxOutPDU based on IpduMInitialSelector value */
  IpduM_TxPartIntType InitDynPartIdx;

  #if (IPDUM_TX_STATIC_IPDU == STD_ON)
  /* Static PDU ID for which confirmation is required for upper layer, If any
   *   of the out IPDU is not having static part then value will be
   * IPDUM_TXPART_INVALID_IDX
   */
  IpduM_TxPartIntType StaticPartIdx;
  #endif

  #if (IPDUM_JIT_UPDATE == STD_ON)
  /* Index in array storing the dynamic part in latest by upper layer */
  IpduM_TxPartIntType TxJitDynPartIdx;
  #endif

  #if (IPDUM_TX_CONF_IPDU == STD_ON)
  /* Index in array storing the dynamic part in latest sent by IpduM */
  IpduM_TxPartIntType TxConfDynPartIdx;

  /* Index in array storing Tx Pending Flag by bit */
  IpduM_TxConfIntType TxPendingFlag;

  /* Tx Pending Mask value. It's zero if TxConfirmation Id is not configured */
  uint8 TxPendingMask;
  #endif
  /*
   * Specifies the trigger state of Tx IPDU depends on the configuration of
   * IpduMTxTriggerMode parameter
   */
  uint8 TriggerMode;

  /* Filling not used areas of an I-PDU with this byte-pattern */
  uint8 UnusedBytePattern;
} IpduM_TxOutIpduType;
#endif /* (IPDUM_TX_IPDU == STD_ON) */

#if (IPDUM_TX_IPDU == STD_ON)
/* Structure of configured Dynamic and Static part information in TxPathway */
typedef struct
{
  /* Destination PDU ID fetched from PDU Router or Com module */
  PduIdType TxUpIpduId;

  /* Specifies the index in Segment Bit field array */
  IpduM_TxMuxSegmentIntType SegmentFieldIdx;

  /* Number of Copy Bit Field */
  IpduM_TxMuxSegmentIntType NoOfSegments;

  /* Specifies the index in arr */
  IpduM_TxMuxIntType TxOutIpduIdx;

  /* Indicates whether the requested transmission for Dynamic Part */
  boolean TxDynamicPart;

  #if (IPDUM_JIT_UPDATE == STD_ON)
  /* Boolean variable for JIT Update */
  boolean JitUpdate;
  #endif

  #if (IPDUM_TX_CONF_IPDU == STD_ON)
  /* Boolean variable for whether TxConfirmation is required or not */
  boolean TxConfirmRequired;
  #endif
} IpduM_TxInIpduType;
#endif /* (IPDUM_TX_IPDU == STD_ON) */

#if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
typedef struct
{
  /* Start Mask for selector bit field */
  uint8 StartMask;

  /* End Mask for selector bit field */
  uint8 EndMask;

  /* Number of shift bits and byte to extract the data
   * Low Nibble: Number of shift bits value
   * High Nibble: Number of byte value
   */
  uint8 NoOfByteAndShiftBits;

  /* Offset to Select Bit Position in IpduM buffer */
  uint8 OffSetValue;
} IpduM_SelBitFieldType;
#endif /* (IPDUM_RX_DYNAMIC_IPDU == STD_ON) */

#if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
typedef struct
{
  /* Source Pdu id from PDUR configuration reference for dynamic part */
  PduIdType DynUpPduId;

  /* Selector value for comparison, for static part this value will be 0xff */
  uint16 SelectorValue;
} IpduM_RxMuxDynPartType;
#endif

#if (IPDUM_RX_IPDU == STD_ON)
typedef struct
{
  #if (IPDUM_RX_STATIC_IPDU == STD_ON)
  /* Source Pdu id from PDUR configuration reference for static part */
  PduIdType StaticUpPduId;

  /* Indicates if Static Ipdu configured */
  boolean StaticPartExist;
  #endif

  #if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
  /* Indicates ByteOrder is Big Endian configured in RxPathway */
  boolean BigEndian;

  /* Index in array of Rx Dynamic Part if configuration */
  IpduM_RxPartIntType DynPartIdx;

  /* Number of Dynamic Rx Indication Ipdu */
  IpduM_RxPartIntType NoOfDynRxIndIpdu;

  /* Index in array of Rx Selector Bit Field if configuration  */
  IpduM_RxMuxIntType SelBitFieldIdx;
  #endif
} IpduM_RxIpduType;
#endif /* (IPDUM_RX_IPDU == STD_ON) */

#if (IPDUM_RX_CONTAINER == STD_ON)
/* Type definition for Rx ContainedPdu information */
typedef struct
{
  /* Header ID of the ContainedPdu */
  uint32 HeaderId;

  /* Length of Static ContainedPdu. If highest offset, it is maximum length */
  PduLengthType SduLength;

  /* Static offset in bytes of the ContainedPdu */
  PduLengthType PduOffset;

 /* Byte location in the ContainerPdu which PDU's Update-Bit belong to */
  PduLengthType UpdateBytePos;

  /* Mask of Update-Bit in the ContainerPdu */
  uint8 UpdateBitMask;

  /* PDU Handle ID assigned by PDU Router */
  PduIdType PduHandleId;

  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  /* Indicates the ContainedPdu that support MetaData */
  boolean MetaDataFlag;
  #endif
} IpduM_RxContainedPduInfoType;


/* Type definition for Rx ContainerPdu information */
typedef struct
{
  /* The layout of the header information */
  uint8 HeaderType;

  /*
   * Indicates the handling of ContainerPdu
   * shall be done in the context of the caller
   */
  boolean ImmediateProcessing;

  #if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
  /* Defines a local queue for handling of each ContainerPdu */
  uint8 QueueSize;

  /* Index in the Queue Info structure */
  uint32 QueueBufIdx;

  /* Pointer to the buffer stored Rx PDU in case Deferred Processing */
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) SduRamAreaPtr;

  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  /* Pointer to the buffer stored Meta Data in case Deferred Processing */
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) MetaDataRamAreaPtr;
  #endif
  #endif /* (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON) */

  /* Maximum length in bytes of Rx ContainerPdu configured in EcuC */
  PduLengthType MaxRxPduLength;
  /*
   * Minimum expected length in bytes of Rx ContainerPdu
   *  Static Container: MinLen = Highest Offset + 1
   *  Dynamic Container: MinLen = Header Size
   */
  PduLengthType MinRxPduLength;

  /* Index in the first ContainedPdu refer to this ContainerPdu */
  IpduM_RxContainedIntType RxContainedPduMappingIndex;

  /* Number of ContainedPdu refer to this ContainerPdu */
  IpduM_RxContainedIntType NoOfRxContainedPdu;

  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  /* Length in bytes of Meta Data in Rx ContainerPdu configured in EcuC */
  uint16 MetaDataLength;
  #endif
} IpduM_RxContainerPduInfoType; /* order of array IpduM_RxContainerPduArray[]: Defferred Container 1..N, Immediate Container 1..N */

typedef struct
{
  uint8 WriteCnt;
  uint8 ReadCnt;
  uint8 InstanceCnt;
} IpduM_QueueRxContainerType;

#endif /* (IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
**              Tx ContainerPdu                                               **
*******************************************************************************/
#if ((IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
typedef struct
{
  uint32 HeaderId;
  uint32 Dlc;
} IpduM_HeaderFieldType;
#endif

#if (IPDUM_TX_CONTAINER == STD_ON)
typedef struct
{
  uint8 WriteCnt;
  uint8 ReadCnt;
  uint8 InstanceCnt;
  PduLengthType InstanceLen;
} IpduM_QueueTxContainerType;

/* Type definition for Tx ContainerPdu information */
typedef struct
{
  #if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON))
  boolean TimeoutBaseEnabled;
  IpduM_TxContainerIntType TimerBufIndex;
  #endif

  #if (IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON)
  uint16 SendTimeout;
  #endif

  /* The layout of the header information */
  uint8 HeaderSize;

  /* Defines a local queue for handling of each ContainerPdu */
  uint8 QueueSize;

  boolean FirstTrigger;

  #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  PduLengthType ThresholdSize;
  #endif

  #if ((IPDUM_TX_STATIC_CONTAINER == STD_ON) || (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON))
  /* Filling not used areas of an I-PDU with this byte-pattern */
  uint8 UnusedBytePattern; /* generate 0x00 if has no configured IpduMUnusedAreasDefault */
  #endif

  boolean TriggerTransmitMode;

  /* Source PduId from PDUR configuration reference */
  PduIdType TxLoPduId;

  /*
   * Defines whether this Pdu shall be collected using a last-is-best or
   * queued semantics.
   */
  boolean LastIsBest;

  IpduM_TxContainedIntType NoOfContainedPdu;
  IpduM_TxContainedIntType ContainedMappingIndex;

  PduLengthType MaxPduLength;

  #if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF))
  IpduM_TxContainedIntType LIBReadWritePosBufIdx;
  IpduM_TxContainedIntType LIBBufIdxOffset;
  #endif
  #endif /* (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) */

  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) TxSduDataPtr;

  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  IpduM_TxContainedIntType TxConfBufIndex;

  /* Index in array storing Tx Pending Flag by bit */
  IpduM_TxConfIntType TxPendingBitPos;
  #endif

  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) TxMetaDataPtr;
  uint16 TxMetaDataLength;
  #endif
} IpduM_TxContainerPduType;

/* Type definition for Tx ContainedPdu information */
typedef struct
{
  /* Pointer to PduInfoType structure */
  IpduM_TxContainerIntType TxContainerMappingIndex;

  #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  /* Specifies part of the ContainerPdu when this ContainedPdu is inside */
  uint32 HeaderId;
  #endif

  #if (IPDUM_TX_STATIC_CONTAINER == STD_ON)
  /* Static offset (in bytes) of the ContainedPdu */
  PduLengthType PduOffset;

  /* Specifies where the PDU's Update-Bit is stored in the ContainerPdu */
  PduLengthType UpdateBytePosition;
  boolean UpdateByteMask;
  #endif

  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  /* Indicates whether TxConfirmation is required or not */
  boolean TxConfirmRequired;
  #endif

  /* Destination PduId fetched from PduR or Com module */
  PduIdType TxUpPduId;

  PduLengthType MaxPduLength;

  #if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
  IpduM_TxContainedIntType LIBAddedFlagBitPos;
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON))
  IpduM_TxContainedIntType LIBBufIdxOffset;
  IpduM_TxContainedIntType NoOfSamePriorityPdu;
  IpduM_TxContainedIntType LIBReadWritePosBufIdx;
  #endif
  #endif /* (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) */

  /* Defines whether this Pdu triggers the sending of the ContainerPdu */
  boolean AlwaysTrigger;
  #if (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON)
  uint16 SendTimeout;
  #endif
} IpduM_TxContainedPduType;
#endif

#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
typedef struct
{
  /* Indicates whether the confirmation for TxPathway or Tx ContainerPdu */
  boolean TxPathway;
  /*
   * Pointer to corresponding element of:
   * - TxPathway in Tx Out Ipdu array or
   * - ContainerTxPdu in Tx Container Pdu Array
   */
  P2CONST(void, AUTOMATIC, IPDUM_CONST) MappingInfoPtr;
} IpduM_TxConfMapInfoType;
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
/* Array of configured Tx Pdu information for Transmission request */
typedef struct
{
  /* Indicates whether the confirmation for TxPathway or Tx ContainerPdu */
  boolean TxPathway;
  /*
   * Pointer to corresponding element of:
   * - TxDynamicPart or TxStaticPart in Tx In Ipdu array or
   * - ContainedTxPdu in Tx Contained Pdu Array
   */
  P2CONST(void, AUTOMATIC, IPDUM_CONST) MappingInfoPtr;
} IpduM_TxPduInfoType;
#endif

#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
/* Type definition for Rx Pdu information */
typedef struct
{
  /* Indicates the Rx Pdu is configured in RxPathway container */
  boolean RxPathwayFlag;
  /* Pointer to the mapping Rx Info structure respectively
   * - RxPathway in Rx Ipdu array or
   * - ContainerRxPdu in Rx Container Pdu Array
   * */
  P2CONST(void, AUTOMATIC, IPDUM_CONST) MappingInfoPtr;
} IpduM_RxPduInfoType;
#endif

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

/*******************************************************************************
**                      Type Definitions                                      **
*******************************************************************************/
/* The data structure contains the initialization data for the IpduM module */
typedef struct
{

  #if ((IPDUM_ENABLE_MODULE == STD_ON) && (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_ON))
  
  #if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_SEGMENT_BITFIELD == STD_ON))
  P2CONST(IpduM_SegmentType, AUTOMATIC, IPDUM_CONST) pSegmentField;
  #endif

  #if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_TX_STATIC_IPDU ==STD_ON)|| \
       (IPDUM_JIT_UPDATE == STD_ON)||(IPDUM_TX_CONF_IPDU == STD_ON))
  P2CONST(IpduM_TxOutIpduType, AUTOMATIC, IPDUM_CONST) pTxOutIpdu;
  #endif

  #if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_JIT_UPDATE == STD_ON)|| \
      (IPDUM_TX_CONF_IPDU == STD_ON))
  P2CONST(IpduM_TxInIpduType, AUTOMATIC, IPDUM_CONST) pTxInIpdu;
  #endif

  #if ((IPDUM_RX_IPDU == STD_ON)&&(IPDUM_RX_DYNAMIC_IPDU == STD_ON))
  P2CONST(IpduM_RxMuxDynPartType, AUTOMATIC, IPDUM_CONST) pRxMuxDynPartArr;
  P2CONST(IpduM_SelBitFieldType, AUTOMATIC, IPDUM_CONST) pSelBitField;
  #endif

  #if ((IPDUM_RX_IPDU == STD_ON) && \
       ((IPDUM_RX_STATIC_IPDU == STD_ON)||(IPDUM_RX_DYNAMIC_IPDU == STD_ON)))
  P2CONST(IpduM_RxIpduType, AUTOMATIC, IPDUM_CONST) pRxInIpdu;
  #endif

  #if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
  P2CONST(IpduM_TxReqIntType, AUTOMATIC, IPDUM_CONST) pTxReqPduArr;
  #endif
  
  #if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
  P2CONST(IpduM_RxIndIntType, AUTOMATIC, IPDUM_CONST) pRxIndPduArr;
  #endif

  #if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
  P2CONST(IpduM_TxConfIntType, AUTOMATIC, IPDUM_CONST) pTxConfIntType;
  #endif

  #else
  uint8 Dummy;
  #endif

} IpduM_ConfigType;

/*******************************************************************************
**                      MACROs                                                **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#endif /* IPDUM_INTTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
