/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_Globals.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of header file for IpduM_Globals.c                  **
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
** 1.0.8          27-Mar-2024         DH Kim           CP44-3766,3812,5321    **
** 1.0.7          27-Jul-2023         HaoTA4           CP44-2462              **
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.4          06-Nov-2022         NhatTD2          CP44-612               **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.2          18-Apr-2022         DuyNHP2          R44-Redmine #26373     **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef IPDUM_GLOBALS_H
#define IPDUM_GLOBALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for pre-compile options */
#include "IpduM_Cfg.h"
/* Inclusion for internal types */
#include "IpduM_IntTypes.h"
#include "IpduM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define IPDUM_GLOBALS_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define IPDUM_GLOBALS_AR_RELEASE_MINOR_VERSION       (0x04u)


/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* Specifies the unused value */
#define IPDUM_DUMMY                         0u

#if(IPDUM_ENABLE_MODULE == STD_ON)

/* Boolean value for initialized state */
#define IPDUM_INIT                         ((boolean)1)
/* Boolean value for uninitialized state */
#define IPDUM_UNINIT                       ((boolean)0)

/* Not trigger transmission if receiving anything of this I-PDU */
#define IPDUM_TX_IPDU_TRIGGER_NONE          (uint8)0x00
/* Trigger a transmission if receiving a dynamic part */
#define IPDUM_TX_IPDU_TRIGGER_DYNAMIC       (uint8)0x01
/* Trigger a transmission if receiving a static part */
#define IPDUM_TX_IPDU_TRIGGER_STATIC        (uint8)0x02
/* Trigger a transmission if receiving a static or dynamic part */
#define IPDUM_TX_IPDU_TRIGGER_BOTH          (uint8)0x03

#if (IPDUM_TX_IPDU == STD_ON)
/* Specifies that index of Tx Static/Dynamic I-PDU is invalid */
#define IPDUM_TXPART_INVALID_IDX            (IpduM_TxPartIntType) IPDUM_TXPART_INVALID_VALUE
#endif /* (IPDUM_TX_IPDU == STD_ON) */

#if (IPDUM_RX_IPDU == STD_ON)
/* Specifies that index of Rx Static/Dynamic I-PDU is invalid */
#define IPDUM_RXPART_INVALID_IDX            (IpduM_RxPartIntType) IPDUM_RXPART_INVALID_VALUE
#endif
#if (IPDUM_TX_CONTAINER == STD_ON)
#define IPDUM_TXCONTAINED_INVALID_IDX       (IpduM_TxContainedIntType) IPDUM_TXCONTAINED_INVALID_VALUE
#endif
#if (IPDUM_RX_CONTAINER == STD_ON)
#define IPDUM_RXCONTAINED_INVALID_IDX       (IpduM_RxContainedIntType) IPDUM_RXCONTAINED_INVALID_VALUE
#endif

#define IPDUM_MAX_SHORT_PDU_LENGTH          (uint8)0xFF

#define IPDUM_TX_CONTAINER_LOCK             (boolean)1
#define IPDUM_TX_CONTAINER_UNLOCK           (boolean)0

/* Static Container Layout */
#define IPDUM_HEADERTYPE_NONE               (uint8)0x00
/* Dynamic Layout with Header size is 32 bit: Header Id 24 bit and Dlc 8 bit */
#define IPDUM_HEADERTYPE_SHORT              (uint8)0x04
/* Dynamic Layout with Header size is 64 bit: Header Id 32 bit and Dlc 32 bit */
#define IPDUM_HEADERTYPE_LONG               (uint8)0x08

/* Threshold of enabling the corresponding search algorithm dynamic parts */
#define IPDUM_BINARY_SEARCH_THRESHOLD       4u

#define IPDUM_BIG_ENDIAN                    1u
#define IPDUM_LITTLE_ENDIAN                 0u

#define IPDUM_BYTE_MASK_INVALID             (uint8)0xFF

#define IPDUM_ZERO                          0u
#define IPDUM_ONE                           1u
#define IPDUM_TWO                           2u
#define IPDUM_THREE                         3u
#define IPDUM_FOUR                          4u
#define IPDUM_FIVE                          5u
#define IPDUM_SIX                           6u
#define IPDUM_SEVEN                         7u
#define IPDUM_EIGHT                         8u
#define IPDUM_SIXTEEN                       16u
#define IPDUM_TWENTYFOUR                    24u

#if ((IPDUM_TX_IPDU == STD_ON) && (IPDUM_TX_CONTAINER == STD_ON))
  #define IpduM_GetTxReqMuxFlag(id)  (IpduM_TxReqMuxFlgArr[id >> 3] & (uint8)(1 << (id % 8)))
#endif
#if ((IPDUM_TX_CONF_IPDU == STD_ON) && (IPDUM_TX_CONF_CONTAINER == STD_ON))
  #define IpduM_GetTxConfMuxFlag(id) (IpduM_TxConfMuxFlgArr[id >> 3] & (uint8)(1 << (id % 8)))
#endif
#if ((IPDUM_RX_IPDU == STD_ON) && (IPDUM_RX_CONTAINER == STD_ON))
  #define IpduM_GetRxIndMuxFlag(id)  (IpduM_RxIndMuxFlgArr[id >> 3] & (uint8)(1 << (id % 8)))
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
  #define IpduM_GetTxReqPduIdx(id)    IpduM_TxReqPduArr[id]
#endif
#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
  #define IpduM_GetTxConfPduIdx(id)   IpduM_TxConfPduArr[id]
#endif
#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#define IpduM_GetRxIndPduIdx(id)      IpduM_RxIndPduArr[id]
#endif

#if (IPDUM_TX_IPDU == STD_ON)
  #define IpduM_IsTxReqForDynamicPart(id)     (IpduM_TxInIpdu[id].TxDynamicPart)
  #define IpduM_GetTxMuxIpduFromPartIpdu(id)   IpduM_TxInIpdu[id].TxOutIpduIdx
  #define IpduM_GetTxPartConfRefPduId(id)     (IpduM_TxInIpdu[id].TxUpIpduId)

  #define IpduM_GetTxMuxDefaultVal(id)        (IpduM_TxOutIpdu[id].UnusedBytePattern)
  #define IpduM_GetTxMuxInitDynPart(id)        IpduM_TxOutIpdu[id].InitDynPartIdx
  #define IpduM_GetTxMuxTriggerMode(id)       (IpduM_TxOutIpdu[id].TriggerMode)
  #define IpduM_GetTxMuxOutgoingRefPduId(id)  (IpduM_TxOutIpdu[id].TxLoPduId)

  #define IpduM_IsTxMuxSentByReceivingDynamicPart(id) (boolean)(IpduM_TxOutIpdu[id].TriggerMode) & IPDUM_TX_IPDU_TRIGGER_DYNAMIC
  #define IpduM_IsTxMuxSentByReceivingStaticPart(id)  (boolean)(IpduM_TxOutIpdu[id].TriggerMode) & IPDUM_TX_IPDU_TRIGGER_STATIC

  #define IpduM_GetTxMuxPduInfoPtr(id)         (IpduM_TxOutIpdu[id].PduInfoPtr)
  #define IpduM_GetAddrBufOfTxMux(id)          (IpduM_TxOutIpdu[id].PduInfoPtr->SduDataPtr)
  #define IpduM_GetLengthBufOfTxMux(id)        (IpduM_TxOutIpdu[id].PduInfoPtr->SduLength)
  #define IpduM_GetAddrMetaDataBufOfTxMux(id)  (IpduM_TxOutIpdu[id].PduInfoPtr->MetaDataPtr)
  #define IpduM_GetLengthMetaDataOfTxMux(id)   (IpduM_TxOutIpdu[id].MetaDataLength)

  #define IpduM_GetTxSegmentIdx(id)         (IpduM_TxInIpdu[id].SegmentFieldIdx)
  #define IpduM_GetTxNoOfSegment(id)        (IpduM_TxInIpdu[id].NoOfSegments)

  #define IpduM_GetAddrTxSegmentDestBuf(id)  IpduM_SegmentField[id].DstBufferPtr
  #define IpduM_GetTxSegmentSize(id)         IpduM_SegmentField[id].NoOfByte
  #define IpduM_GetTxSegmentByteOffset(id)  (IpduM_SegmentField[id].SourceOffset)
#endif /* (IPDUM_TX_IPDU == STD_ON) */

#if (IPDUM_SEGMENT_BITFIELD == STD_ON)
  #define IpduM_GetTxSegmentFirstByteSetMask(id)           (IpduM_SegmentField[id].SourceStartMask)
  #define IpduM_GetTxSegmentFirstByteClrMask(id)  (uint8)(~(IpduM_SegmentField[id].SourceStartMask))
  #define IpduM_GetTxSegmentLastByteSetMask(id)            (IpduM_SegmentField[id].SourceEndMask)
  #define IpduM_GetTxSegmentLastByteClrMask(id)   (uint8)(~(IpduM_SegmentField[id].SourceEndMask))
#endif

#if (IPDUM_TX_STATIC_IPDU == STD_ON)
  #define IpduM_GetTxMuxStaticPartIdx(id)    (IpduM_TxOutIpdu[id].StaticPartIdx)
#endif

#if (IPDUM_JIT_UPDATE == STD_ON)
  #define IpduM_IsTxPartJITRequired(id)           (IpduM_TxInIpdu[id].JitUpdate)

  #define IpduM_GetIdxOfJITDynTxPartBuf(id)  (IpduM_TxOutIpdu[id].TxJitDynPartIdx)
  #define IpduM_GetTxMuxJITDynPartIdx(i)      IpduM_JitDynPartMapArray[i]
  #define IpduM_SetTxMuxJITDynPart(i, val)    IpduM_JitDynPartMapArray[i] = val
#endif /* (IPDUM_JIT_UPDATE == STD_ON) */

#if (IPDUM_TX_CONF_IPDU == STD_ON)
  #define IpduM_IsTxPartConfRequired(id)  (IpduM_TxInIpdu[id].TxConfirmRequired)

  #define IpduM_GetIdxOfConfDynTxPartBuf(id)  (IpduM_TxOutIpdu[id].TxConfDynPartIdx)
  #define IpduM_GetTxMuxConfDynPart(i)     (IpduM_TxConfDynPartMapArray[i])
  #define IpduM_SetTxMuxConfDynPart(i, val) \
    do { \
      SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA(); \
      IpduM_TxConfDynPartMapArray[i] = val; \
      SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA(); \
    } while(0)
  #define IpduM_IsTxMuxConfEnabled(id)          (boolean)(IpduM_TxOutIpdu[id].TxPendingMask)
  #define IpduM_GetTxMuxByteIdxOfConfPendingFlagBuf(id)  (IpduM_TxOutIpdu[id].TxPendingFlag)
  #define IpduM_GetTxMuxByteMaskOfConfPendingFlagBuf(id) (IpduM_TxOutIpdu[id].TxPendingMask)
#endif /* (IPDUM_TX_CONF_IPDU == STD_ON) */

#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
  #define IpduM_GetTxConfPendingFlag(i, msk) (IpduM_TxPendingFlag[i] & msk)
  #define IpduM_SetTxConfPendingFlag(i, msk) \
    do { \
      SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA(); \
      IpduM_TxPendingFlag[i] |= msk; \
      SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA(); \
    } while(0)
  #define IpduM_ClearTxConfPendingFlag(i, msk) \
    do { \
      SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA(); \
      IpduM_TxPendingFlag[i] &= (uint8)(~msk); \
      SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA();\
    } while(0)
#endif /* ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON)) */

#if (IPDUM_RX_IPDU == STD_ON)
#if (IPDUM_RX_STATIC_IPDU == STD_ON)
  #define IpduM_IsRxMuxStaticPartExist(id)  (IpduM_RxInIpdu[id].StaticPartExist)
  #define IpduM_GetRxMuxStaticRefPduId(id)  (IpduM_RxInIpdu[id].StaticUpPduId)
#endif

#if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
  #define IpduM_GetRxMuxSelField(id)       (IpduM_RxInIpdu[id].SelBitFieldIdx)
  #define IpduM_GetRxMuxNoOfDynPart(id)    (IpduM_RxInIpdu[id].NoOfDynRxIndIpdu)
  #define IpduM_GetRxMuxDynPartIdx(id)     (IpduM_RxInIpdu[id].DynPartIdx)
  #define IpduM_GetRxMuxByteOrder(id)      (IpduM_RxInIpdu[id].BigEndian)

  #define IpduM_GetRxMuxDynSelVal(id)    (IpduM_RxMuxDynPartArr[id].SelectorValue)
  #define IpduM_GetRxMuxDynRefPduId(id)  (IpduM_RxMuxDynPartArr[id].DynUpPduId)

  #define IpduM_GetRxMuxSelFieldBytePos(id)        (IpduM_SelBitField[id].OffSetValue)
  #define IpduM_GetRxMuxSelFieldStartByteMask(id)  (IpduM_SelBitField[id].StartMask)
  #define IpduM_GetRxMuxSelFieldEndByteMask(id)    (IpduM_SelBitField[id].EndMask)
  #define IpduM_GetRxMuxSelFieldNoOfByte(id)       (IpduM_SelBitField[id].NoOfByteAndShiftBits >> 4u)
  #define IpduM_GetRxMuxSelFieldBitShift(id)       (IpduM_SelBitField[id].NoOfByteAndShiftBits & 0x0Fu)
#endif /* (IPDUM_RX_DYNAMIC_IPDU == STD_ON) */
#endif /* (IPDUM_RX_IPDU == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of IpduM */
extern VAR(boolean, IPDUM_VAR) IpduM_InitStatus;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if ((IPDUM_TX_CONF_IPDU == STD_ON) && (IPDUM_TX_CONF_CONTAINER == STD_ON))
#define IPDUM_START_SEC_CONST_8
#include "MemMap.h"
/* Array of indication the Pdu is a Multiplexed I-PDU */
extern CONST(uint8, IPDUM_CONST) IpduM_TxConfMuxFlgArr[];
#define IPDUM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array of configured Tx Pdu info for TriggerTransmit and TxConfirmation */
#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_TxConfIntType, IPDUM_CONST) IpduM_TxConfPduArr[];
#else
extern P2CONST(IpduM_TxConfIntType, AUTOMATIC, IPDUM_CONST) IpduM_TxConfPduArr;
#endif
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define IPDUM_START_SEC_VAR_INIT_8
#include "MemMap.h"
extern VAR(uint8, IPDUM_VAR) IpduM_TxPendingFlag[];
#define IPDUM_STOP_SEC_VAR_INIT_8
#include "MemMap.h"
#endif /*((IPDUM_TX_CONF_IPDU == STD_ON)||(IPDUM_TX_CONF_CONTAINER == STD_ON))*/

#if ((IPDUM_TX_IPDU == STD_ON) && (IPDUM_TX_CONTAINER == STD_ON))
#define IPDUM_START_SEC_CONST_8
#include "MemMap.h"
/* Array of indication the Pdu is a part of Multiplexed I-PDU */
extern CONST(uint8, IPDUM_CONST) IpduM_TxReqMuxFlgArr[];
#define IPDUM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array of configured Tx Pdu information for Transmission request */
#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_TxReqIntType, IPDUM_CONST) IpduM_TxReqPduArr[];
#else
extern P2CONST(IpduM_TxReqIntType, AUTOMATIC, IPDUM_CONST) IpduM_TxReqPduArr;
#endif

#if (IPDUM_TX_IPDU == STD_ON)
extern CONST(PduInfoType, IPDUM_CONST) IpduM_TxIpduPduInfoArray[];
extern VAR(uint8, IPDUM_VAR)IpduM_TxIpduSduBuffer[];
extern VAR(IpduM_TxPartIntType, IPDUM_VAR) IpduM_TxConfDynPartMapArray[];
extern VAR(IpduM_TxPartIntType, IPDUM_VAR) IpduM_JitDynPartMapArray[];
extern VAR(uint8, IPDUM_VAR)IpduM_TxIpduMetaDataBuffer[];

#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_SegmentType, IPDUM_CONST) IpduM_SegmentField[];
#else
extern P2CONST(IpduM_SegmentType, AUTOMATIC, IPDUM_CONST) IpduM_SegmentField;
#endif

/* Global array for IpduM Tx In Ipdu  structure  */
#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_TxInIpduType, IPDUM_CONST) IpduM_TxInIpdu[];
#else
extern P2CONST(IpduM_TxInIpduType, AUTOMATIC, IPDUM_CONST) IpduM_TxInIpdu;
#endif

/* Global array for IpduM Tx Out Ipdu structure  */
#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_TxOutIpduType, IPDUM_CONST) IpduM_TxOutIpdu[];
#else
extern P2CONST(IpduM_TxOutIpduType, AUTOMATIC, IPDUM_CONST) IpduM_TxOutIpdu;
#endif

#endif /* (IPDUM_TX_IPDU == STD_ON) */
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON)) */

#if ((IPDUM_RX_IPDU == STD_ON) && (IPDUM_RX_CONTAINER == STD_ON))
#define IPDUM_START_SEC_CONST_8
#include "MemMap.h"
/* Array of indication the Pdu is a Multiplexed I-PDU */
extern CONST(uint8, IPDUM_CONST) IpduM_RxIndMuxFlgArr[];
#define IPDUM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array of configured Rx Pdu info for RxIndication */
#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_RxIndIntType, IPDUM_CONST) IpduM_RxIndPduArr[];
#else
extern P2CONST(IpduM_RxIndIntType, AUTOMATIC, IPDUM_CONST) IpduM_RxIndPduArr;
#endif

#if (IPDUM_RX_IPDU == STD_ON)
#if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)

#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_RxMuxDynPartType, IPDUM_CONST) IpduM_RxMuxDynPartArr[];
extern CONST(IpduM_SelBitFieldType, IPDUM_CONST) IpduM_SelBitField[];
#else
extern P2CONST(IpduM_RxMuxDynPartType, AUTOMATIC, IPDUM_CONST) IpduM_RxMuxDynPartArr;
extern P2CONST(IpduM_SelBitFieldType, AUTOMATIC, IPDUM_CONST) IpduM_SelBitField;
#endif
#endif

#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
extern CONST(IpduM_RxIpduType, IPDUM_CONST) IpduM_RxInIpdu[];
#else
extern P2CONST(IpduM_RxIpduType, AUTOMATIC, IPDUM_CONST) IpduM_RxInIpdu;
#endif

#endif /* (IPDUM_RX_IPDU == STD_ON) */

#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON)) */


#if (IPDUM_TX_CONTAINER == STD_ON)
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(IpduM_TxContainedPduType, IPDUM_CONST) IpduM_TxContainedArr[];
extern CONST(IpduM_TxContainerPduType, IPDUM_CONST) IpduM_TxContainerArr[];
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define IPDUM_START_SEC_VAR_INIT_BOOLEAN
#include "MemMap.h"
extern VAR(boolean, IPDUM_VAR) IpduM_TxContainerProtectFlagBuf[];
#define IPDUM_STOP_SEC_VAR_INIT_BOOLEAN
#include "MemMap.h"

#define IPDUM_START_SEC_VAR_INIT_8
#include "MemMap.h"
extern VAR(uint8, IPDUM_VAR) IpduM_TxContainerBuffer[];

#if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
extern VAR(uint8, IPDUM_VAR) IpduM_TxLIBAddedFlagArr[];
#endif
#define IPDUM_STOP_SEC_VAR_INIT_8
#include "MemMap.h"

#if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON))
#define IPDUM_START_SEC_VAR_INIT_16
#include "MemMap.h"
extern VAR(uint16, IPDUM_VAR) IpduM_SendTimeoutContainerTxArr[];
#define IPDUM_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

#define IPDUM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(IpduM_QueueTxContainerType, IPDUM_VAR) IpduM_TxContainerHandlingBuffer[];

#if ((IPDUM_TX_STATIC_CONTAINER == STD_ON) && (IPDUM_TX_DIRECT_STATIC_CONTAINER == STD_ON))
extern VAR(IpduM_TxContainedIntType, IPDUM_VAR) IpduM_TxLIBStaticContainerCntBuffer[];
#endif

#if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && \
      (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && \
      ((IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF) || \
      (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON)))
extern VAR(IpduM_TxContainedIntType, IPDUM_VAR) IpduM_TxLIBReadPosBuffer[];
extern VAR(IpduM_TxContainedIntType, IPDUM_VAR) IpduM_TxLIBWritePosBuffer[];
extern VAR(IpduM_TxContainedIntType, IPDUM_VAR) IpduM_TxLIBContainedPduIdxArr[];
#endif

#if (IPDUM_TX_CONF_CONTAINER == STD_ON)
extern VAR(IpduM_TxContainedIntType, IPDUM_CONST)  IpduM_TxContainedConfirmArr[];
#endif
#define IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

#if (IPDUM_TX_CONTAINER == STD_ON)
#define IpduM_GetBasedAddrTxContainerBuffer(id)  (IpduM_TxContainerArr[id].TxSduDataPtr)
#define IpduM_GetTxContainerProtection(id)       (IpduM_TxContainerProtectFlagBuf[id])
#define IpduM_SetTxContainerProtection(id, val)   IpduM_TxContainerProtectFlagBuf[id] = val

#if (IPDUM_META_DATA_SUPPORT == STD_ON)
#define IpduM_IsTxContainerMetaDataSupport(id)  (boolean)(IpduM_TxContainerArr[id].TxMetaDataLength)
#define IpduM_GetBasedAddrTxContainerMetaDataBuffer(id)   IpduM_TxContainerArr[id].TxMetaDataPtr
#define IpduM_GetTxContainerMetaDataLength(id)           (IpduM_TxContainerArr[id].TxMetaDataLength)
#endif

#define IpduM_IsLastIsBestTxContainerTx(id)         (IpduM_TxContainerArr[id].LastIsBest)
#define IpduM_IsTriggerTransmitContainerTx(id)      (IpduM_TxContainerArr[id].TriggerTransmitMode)
#define IpduM_IsDynamicContainerTx(id)     (boolean)(IpduM_TxContainerArr[id].HeaderSize)
#define IpduM_IsTxTriggerAlwaysContainedPdu(id)     (IpduM_TxContainedArr[id].AlwaysTrigger)
#define IpduM_GetMaxNoOfInstanceTxContainer(id)     (IpduM_TxContainerArr[id].QueueSize)
#define IpduM_GetTxContainerHeaderSize(idx)         (IpduM_TxContainerArr[idx].HeaderSize)
#define IpduM_GetNoOfContainedPduInContainerTx(id)  (IpduM_TxContainerArr[id].NoOfContainedPdu)
#define IpduM_GetFirstTxContainedOfContainer(id)     IpduM_TxContainerArr[id].ContainedMappingIndex
#define IpduM_GetTxContainerRefPduId(id)            (IpduM_TxContainerArr[id].TxLoPduId)
#define IpduM_GetMaxInstanceLenOfTxContainer(id)    (IpduM_TxContainerArr[id].MaxPduLength)

#define IpduM_IsContainerTxFirstContainedPduTrigger(id)  (IpduM_TxContainerArr[id].FirstTrigger)

#define IpduM_GetContainerTxIdx(id)         IpduM_TxContainedArr[id].TxContainerMappingIndex
#define IpduM_GetTxContainedRefPduId(id)   (IpduM_TxContainedArr[id].TxUpPduId)
#define IpduM_GetTxContainedMaxPduLen(id)  (IpduM_TxContainedArr[id].MaxPduLength)

#if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
  #define IpduM_GetLIBAddedFlagIdxOfTxContainedPdu(id)                 (IpduM_TxContainedArr[id].LIBAddedFlagBitPos >> 3u)
  #define IpduM_GetLIBAddedFlagMaskOfTxContainedPdu(id)  (uint8)(1u << (IpduM_TxContainedArr[id].LIBAddedFlagBitPos % 8))
  #define IpduM_GetLIBAddedFlagBuffer(i)                  (IpduM_TxLIBAddedFlagArr[i])
  #define IpduM_SetLIBAddedFlagOfTxContainedPdu(i, msk)    IpduM_TxLIBAddedFlagArr[i] |= msk
  #define IpduM_ClearLIBAddedFlagOfTxContainedPdu(i, msk)  IpduM_TxLIBAddedFlagArr[i] &= (uint8)(~msk)
#endif

#if (IPDUM_TX_STATIC_CONTAINER == STD_ON)
#if (IPDUM_TX_DIRECT_STATIC_CONTAINER == STD_ON)
  #define IpduM_IncCntOfStaticTxContainedPduUpdatedByUL(id)    IpduM_TxLIBStaticContainerCntBuffer[id]++
  #define IpduM_GetNoOfStaticTxContainedPduUpdatedByUL(id)    (IpduM_TxLIBStaticContainerCntBuffer[id])
  #define IpduM_ClearCntOfStaticTxContainedPduUpdatedByUL(id)  IpduM_TxLIBStaticContainerCntBuffer[id] = (IpduM_TxContainedIntType)0u
#endif
  #define IpduM_GetLIBTxContainerUnusedBytePattern(id)    (IpduM_TxContainerArr[id].UnusedBytePattern)
  #define IpduM_GetLIBStaticTxContainerOffset(id)          IpduM_TxContainedArr[id].PduOffset
  #define IpduM_GetStaticTxContainedUpdateBitBytePos(id)   IpduM_TxContainedArr[id].UpdateBytePosition
  #define IpduM_GetStaticTxContainedUpdateBitByteMask(id)  IpduM_TxContainedArr[id].UpdateByteMask
#endif /* (IPDUM_TX_STATIC_CONTAINER == STD_ON) */

#if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  #define IpduM_GetContainerTxSizeThreshold(id)  (IpduM_TxContainerArr[id].ThresholdSize)
  #define IpduM_GetTxContainedHeaderId(id)       (IpduM_TxContainedArr[id].HeaderId)
#if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
#if (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF)
  #define IpduM_GetSizeOfLIBContainerTxIdxBuf(id)    (IpduM_TxContainerArr[id].NoOfContainedPdu)
  #define IpduM_GetOffsetOfLIBContainerTxIdxBuf(id)   IpduM_TxContainerArr[id].LIBBufIdxOffset

  #define IpduM_GetWritePosOfLIBContainerTxIdxBuf(id)   (IpduM_TxLIBWritePosBuffer[IpduM_TxContainerArr[id].LIBReadWritePosBufIdx])
  #define IpduM_IncWritePosOfLIBContainerTxIdxBuf(id)  ++IpduM_TxLIBWritePosBuffer[IpduM_TxContainerArr[id].LIBReadWritePosBufIdx]
  #define IpduM_ClearWritePosOfLIBContainerTxIdxBuf(id)  IpduM_TxLIBWritePosBuffer[IpduM_TxContainerArr[id].LIBReadWritePosBufIdx] = (uint8)0x00

  #define IpduM_GetReadPosOfLIBContainerTxIdxBuf(id)   (IpduM_TxLIBReadPosBuffer[IpduM_TxContainerArr[id].LIBReadWritePosBufIdx])
  #define IpduM_IncReadPosOfLIBContainerTxIdxBuf(id)  ++IpduM_TxLIBReadPosBuffer[IpduM_TxContainerArr[id].LIBReadWritePosBufIdx]
  #define IpduM_ClearReadPosOfLIBContainerTxIdxBuf(id)  IpduM_TxLIBReadPosBuffer[IpduM_TxContainerArr[id].LIBReadWritePosBufIdx] = (uint8)0x00

  #define IpduM_SetContainedPduIdxToLIBContainerTxIdxBuf(i, id)  IpduM_TxLIBContainedPduIdxArr[i] = id
  #define IpduM_GetContainedPduIdxFromLIBContainerTxIdxBuf(i)    IpduM_TxLIBContainedPduIdxArr[i]
#elif (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON)
  #define IpduM_GetNoOfContainedPduTxHaveSamePriorityValue(id)  (IpduM_TxContainedArr[id].NoOfSamePriorityPdu)
  #define IpduM_GetOffsetOfLIBContainerTxIdxBuf(id)             (IpduM_TxContainedArr[id].LIBBufIdxOffset)

  #define IpduM_GetWritePosOfLIBContainerTxIdxBuf(id)   (IpduM_TxLIBWritePosBuffer[IpduM_TxContainedArr[id].LIBReadWritePosBufIdx])
  #define IpduM_IncWritePosOfLIBContainerTxIdxBuf(id)  ++IpduM_TxLIBWritePosBuffer[IpduM_TxContainedArr[id].LIBReadWritePosBufIdx]
  #define IpduM_ClearWritePosOfLIBContainerTxIdxBuf(id)  IpduM_TxLIBWritePosBuffer[IpduM_TxContainedArr[id].LIBReadWritePosBufIdx] = (uint8)0x00

  #define IpduM_GetReadPosOfLIBContainerTxIdxBuf(id)   (IpduM_TxLIBReadPosBuffer[IpduM_TxContainedArr[id].LIBReadWritePosBufIdx])
  #define IpduM_IncReadPosOfLIBContainerTxIdxBuf(id)  ++IpduM_TxLIBReadPosBuffer[IpduM_TxContainedArr[id].LIBReadWritePosBufIdx]
  #define IpduM_ClearReadPosOfLIBContainerTxIdxBuf(id)  IpduM_TxLIBReadPosBuffer[IpduM_TxContainedArr[id].LIBReadWritePosBufIdx] = (uint8)0x00

  #define IpduM_SetContainedPduIdxToLIBContainerTxIdxBuf(i, id)  IpduM_TxLIBContainedPduIdxArr[i] = id
  #define IpduM_GetContainedPduIdxFromLIBContainerTxIdxBuf(i)    IpduM_TxLIBContainedPduIdxArr[i]
#endif
#endif /* (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) */
#endif /* (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) */

#if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON))
  #define IpduM_IsTimeoutBaseTriggeringForContainerTx(id)  (IpduM_TxContainerArr[id].TimeoutBaseEnabled)
  #define IpduM_SetContainerTxPduSendTimer(id, val)  IpduM_SendTimeoutContainerTxArr[IpduM_TxContainerArr[id].TimerBufIndex] = val
  #define IpduM_DecContainerTxPduSendTimer(id)     --IpduM_SendTimeoutContainerTxArr[IpduM_TxContainerArr[id].TimerBufIndex]
  #define IpduM_GetContainerTxPduSendTimer(id)      (IpduM_SendTimeoutContainerTxArr[IpduM_TxContainerArr[id].TimerBufIndex])
#if (IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON)
  #define IpduM_GetContainerTxSendTimeout(id)     (IpduM_TxContainerArr[id].SendTimeout)
#endif
#if (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON)
  #define IpduM_GetContainedTxPduSendTimeout(id)  (IpduM_TxContainedArr[id].SendTimeout)
#endif
#endif /* #if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON)) */

#if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  #define IpduM_GetContainerTxPduConfBufIdx(id)        (IpduM_TxContainerArr[id].TxConfBufIndex)
  #define IpduM_SetContainedTxPduIdxToConfBuf(i, id)    IpduM_TxContainedConfirmArr[i] = id
  #define IpduM_GetContainedTxPduIdxFromConfBuf(i)     (IpduM_TxContainedConfirmArr[i])
  #define IpduM_IsContainerTxConfirmationEnabled(id)  ((IpduM_TxContainedIntType)0xFFFF != IpduM_TxContainerArr[id].TxPendingBitPos)
  #define IpduM_GetContainerByteIdxOfTxConfPendingFlagBuf(id)                              IpduM_TxContainerArr[id].TxPendingBitPos >> 3u
  #define IpduM_GetContainerByteMaskOfTxConfPendingFlagBuf(id)                   0x01u << (IpduM_TxContainerArr[id].TxPendingBitPos % 8u)
#endif

#define IpduM_GetWriteCntInstanceTxContainer(id)          (IpduM_TxContainerHandlingBuffer[id].WriteCnt)
#define IpduM_SetWriteCntInstanceTxContainer(id, val)      IpduM_TxContainerHandlingBuffer[id].WriteCnt = val
#define IpduM_IncWriteCntInstanceTxContainer(id)         ++IpduM_TxContainerHandlingBuffer[id].WriteCnt
#define IpduM_GetReadCntInstanceTxContainer(id)           (IpduM_TxContainerHandlingBuffer[id].ReadCnt)
#define IpduM_SetReadCntInstanceTxContainer(id, val)       IpduM_TxContainerHandlingBuffer[id].ReadCnt = val
#define IpduM_IncReadCntInstanceTxContainer(id)          ++IpduM_TxContainerHandlingBuffer[id].ReadCnt
#define IpduM_GetCntOfQueuedInstanceTxContainer(id)       (IpduM_TxContainerHandlingBuffer[id].InstanceCnt)
#define IpduM_SetCntOfQueuedInstanceTxContainer(id, val)   IpduM_TxContainerHandlingBuffer[id].InstanceCnt = val
#define IpduM_IncCntOfQueuedInstanceTxContainer(id)      ++IpduM_TxContainerHandlingBuffer[id].InstanceCnt
#define IpduM_DecCntOfQueuedInstanceTxContainer(id)      --IpduM_TxContainerHandlingBuffer[id].InstanceCnt
#define IpduM_GetSizeOfCurrInstanceTxContainer(id)        (IpduM_TxContainerHandlingBuffer[id].InstanceLen)
#define IpduM_SetCurrInstanceLengthOfTxContainer(id, val)  IpduM_TxContainerHandlingBuffer[id].InstanceLen = val
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

#if (IPDUM_RX_CONTAINER == STD_ON)
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(IpduM_RxContainedPduInfoType, IPDUM_CONST) IpduM_RxContainedPduArray[];
extern CONST(IpduM_RxContainerPduInfoType, IPDUM_CONST) IpduM_RxContainerPduArray[];
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
#define IPDUM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(IpduM_QueueRxContainerType, IPDUM_VAR) IpduM_RxContainerHandlingArr[]; /* size is Number of Defferred processing ContainerRxPdu */
#define IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define IPDUM_START_SEC_VAR_INIT_8
#include "MemMap.h"
extern VAR(uint8, IPDUM_VAR) IpduM_RxContainerDeferredSduBuffer[]; /* size is maximum PduLength of Defferred ContainerRxPdu */
#define IPDUM_STOP_SEC_VAR_INIT_8
#include "MemMap.h"

#define IPDUM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduLengthType, IPDUM_VAR) IpduM_QueuedInstanceRxContainerSizeArr[]; /* size is Number of Defferred processing ContainerRxPdu * QueueSize */
#define IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (IPDUM_META_DATA_SUPPORT == STD_ON)
#define IPDUM_START_SEC_VAR_INIT_8
#include "MemMap.h"
extern VAR(uint8, IPDUM_VAR) IpduM_RxContainerDeferredMetaDataBuffer[]; /* size is maximum MetaData of Defferred ContainerRxPdu */
#define IPDUM_STOP_SEC_VAR_INIT_8
#include "MemMap.h"

#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
extern VAR(boolean, IPDUM_VAR) IpduM_QueuedInstanceRxContainerMetaDataArr[]; /* size is Number of Defferred processing ContainerRxPdu * QueueSize */
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* (IPDUM_META_DATA_SUPPORT == STD_ON) */
#endif /* (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON) */
#endif /* (IPDUM_RX_CONTAINER == STD_ON) */

#if (IPDUM_RX_CONTAINER == STD_ON)
#define IpduM_IsRxContainerPduImmediateProcessing(id)  (IpduM_RxContainerPduArray[id].ImmediateProcessing)

#define IpduM_IsRxDynamicContainerPdu(id)     (boolean)(IpduM_RxContainerPduArray[id].HeaderType)
#define IpduM_GetRxContainerHeaderSize(id)              IpduM_RxContainerPduArray[id].HeaderType

#define IpduM_GetMinSizeOfInstanceRxContainer(id)      (IpduM_RxContainerPduArray[id].MinRxPduLength)
#define IpduM_GetMaxSizeOfInstanceRxContainer(id)      (IpduM_RxContainerPduArray[id].MaxRxPduLength)

#define IpduM_GetNoOfContainedPduInRxContainer(id)     (IpduM_RxContainerPduArray[id].NoOfRxContainedPdu)
#define IpduM_GetFirstContainedPduOfRxContainer(id)     IpduM_RxContainerPduArray[id].RxContainedPduMappingIndex

#define IpduM_GetRxContainedRefPduId(id)   IpduM_RxContainedPduArray[id].PduHandleId

#if (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)
#define IpduM_GetRxContainedHeaderId(id)  (IpduM_RxContainedPduArray[id].HeaderId)
#endif

#if (IPDUM_RX_STATIC_CONTAINER== STD_ON)
#define IpduM_GetStaticRxContainedUpdateBitBytePos(id)        IpduM_RxContainedPduArray[id].UpdateBytePos
#define IpduM_GetStaticRxContainedUpdateBitByteMask(id)       IpduM_RxContainedPduArray[id].UpdateBitMask
#define IpduM_IsRxContainedUpdateBitConfigured(id)  (boolean)(IpduM_RxContainedPduArray[id].UpdateBitMask)

#define IpduM_GetStaticRxContainedPduOffset(id)               IpduM_RxContainedPduArray[id].PduOffset
#define IpduM_GetMaxLengthOfStaticRxContainedPdu(id)          IpduM_RxContainedPduArray[id].SduLength
#endif

#if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
#define IpduM_GetAddrOfDeferredRxContainerSduBuf()  &IpduM_RxContainerDeferredSduBuffer[0]

#if (IPDUM_META_DATA_SUPPORT == STD_ON)
#define IpduM_GetAddrOfDeferredRxContainerMetaDataBuf()  &IpduM_RxContainerDeferredMetaDataBuffer[0]
#define IpduM_GetBasedAddrRxContainerMetaDataBuffer(id)   IpduM_RxContainerPduArray[id].MetaDataRamAreaPtr
#define IpduM_GetQueuedInstanceRxContainerSupportMetaData(i)      (IpduM_QueuedInstanceRxContainerMetaDataArr[i])
#define IpduM_SetQueuedInstanceRxContainerSupportMetaData(i, val)  IpduM_QueuedInstanceRxContainerMetaDataArr[i] = val
#endif

#define IpduM_GetCntOfQueuedInstanceRxContainer(id)   (IpduM_RxContainerHandlingArr[id].InstanceCnt)
#define IpduM_IncCntOfQueuedInstanceRxContainer(id)  ++IpduM_RxContainerHandlingArr[id].InstanceCnt
#define IpduM_DecCntOfQueuedInstanceRxContainer(id)  --IpduM_RxContainerHandlingArr[id].InstanceCnt
#define IpduM_GetWriteCntInstanceRxContainer(id)       IpduM_RxContainerHandlingArr[id].WriteCnt
#define IpduM_GetReadCntInstanceRxContainer(id)        IpduM_RxContainerHandlingArr[id].ReadCnt
#define IpduM_IncWriteCntInstanceRxContainer(id)     ++IpduM_RxContainerHandlingArr[id].WriteCnt
#define IpduM_IncReadCntInstanceRxContainer(id)      ++IpduM_RxContainerHandlingArr[id].ReadCnt
#define IpduM_SetWriteCntInstanceRxContainer(id, val)  IpduM_RxContainerHandlingArr[id].WriteCnt = val
#define IpduM_SetReadCntInstanceRxContainer(id, val)   IpduM_RxContainerHandlingArr[id].ReadCnt = val

#define IpduM_GetQueuedInstanceRxContainerBufIdx(id)      IpduM_RxContainerPduArray[id].QueueBufIdx
#define IpduM_GetSizeOfQueuedInstanceRxContainer(i)      (IpduM_QueuedInstanceRxContainerSizeArr[i])
#define IpduM_SetSizeOfQueuedInstanceRxContainer(i, val)  IpduM_QueuedInstanceRxContainerSizeArr[i] = val

#define IpduM_GetBasedAddrRxContainerBuf(id)      IpduM_RxContainerPduArray[id].SduRamAreaPtr
#define IpduM_GetMaxNoOfInstanceRxContainer(id)  (IpduM_RxContainerPduArray[id].QueueSize)
#endif /* (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON) */

#if (IPDUM_META_DATA_SUPPORT == STD_ON)
#define IpduM_IsRxContainerMetaDataSupport(id)  (boolean)(IpduM_RxContainerPduArray[id].MetaDataLength)
#define IpduM_GetRxContainerMetaDataLength(id)           (IpduM_RxContainerPduArray[id].MetaDataLength)
#define IpduM_IsRxContainedPduSupportMetaData(id)        (IpduM_RxContainedPduArray[id].MetaDataFlag)
#endif /* (IPDUM_META_DATA_SUPPORT == STD_ON) */

#endif /* (IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
**                      Variable for Library                                  **
*******************************************************************************/

#endif /* (IPDUM_ENABLE_MODULE == STD_ON) */


#endif /* IPDUM_GLOBALS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
