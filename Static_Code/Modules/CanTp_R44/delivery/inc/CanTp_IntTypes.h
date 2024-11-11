/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_IntTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanTp                                                 **
**                                                                            **
**  PURPOSE   : To provide CanTp structure type definitions                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.7     31-Oct-2022   HieuTM8        #CP44-1038                          **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803                  **
** 1.0.2     18-Apr-2022   HieuTM8        R44-Redmine  #25515                 **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344 #24831   **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

#ifndef CANTP_INTTYPES_H
#define CANTP_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp header file */
#include "SchM_CanTp.h"           /* SchM header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* Version number macros for checking */
/* AUTOSAR specification version information */
/* @Trace: CanTp_SUD_MACRO_003 */
#define CANTP_INTTYPES_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_INTTYPES_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_INTTYPES_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_INTTYPES_SW_MAJOR_VERSION            0x01u
#define CANTP_INTTYPES_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/

/*******************************************************************************
**                       Global Symbols                                      **
*******************************************************************************/
#define CANTP_ZERO                     0x00
#define CANTP_ONE                      0x01
#define CANTP_TWO                      0x02
#define CANTP_THREE                    0x03
#define CANTP_FOUR                     0x04
#define CANTP_FIVE                     0x05
#define CANTP_SIX                      0x06
#define CANTP_SEVEN                    0x07
#define CANTP_EIGHT                    0x08
#define CANTP_NINE                     0x09
#define CANTP_TEN                      0x0A
#define CANTP_SIXTEEN                  0x10
#define CANTP_TWENTYFOUR               0x18
#define CANTP_THIRTY                   0x1E  /* 30 bytes */
#define CANTP_THIRTYONE                0x1F  /* 31 bytes */
#define CANTP_THIRTYTWO                0x20  /* 32 bytes */
#define CANTP_SIXTYTWO                 0x3E  /* 62 bytes */
#define CANTP_SIXTYTHREE               0x3F  /* 63 bytes */
#define CANTP_SIXTYFOUR                0x40  /* 64 bytes */
#define CANTP_FOURZERONINEFIVE         0xFFF /* 4095 bytes */

#define CANTP_MAX_SDU_LENGTH           ((uint32) 0xFFFFFFFFu) /* Allowed Max SDU
                                                        * length */
/* Physical and Functional address for CAN2.0 and CANFD*/
#define CANTP_PHYSICAL_ADDRESS         0x00 /* Physical Communication*/
#define CANTP_FUNCTIONAL_ADDRESS       0x01 /* Functional Communication*/

/* CanTp Addressing Mode */
#define CANTP_STANDARD_ADDRESS         0x00 /* Standard Addressing Mode */
#define CANTP_EXTENDED_ADDRESS         0x01 /* Extended Addressing Mode */
#define CANTP_MIXED_ADDRESS            0x02 /* Mixed Addressing Mode */
#define CANTP_MIXED29BIT_ADDRESS       0x03 /* Mixed29bit Addressing Mode */
#define CANTP_NORMALFIXED_ADDRESS      0x04 /* Normal fixed addressing mode */

/* CanTp Addressing Information */
#define CANTP_NAI_MASK               ((uint16) 0x00FF) /* Clear the high byte for upper layer
                                                        * request , response for CanTp
                                                        */
#define CANTP_ERASE_3BYTES_HIGH      ((uint32)0x000000FF)

/* Define addressing follow Chapter 10.3.3 Normal fixed addressing
 * in ISO 15765-2-2016*/
#define CANTP_HIGHESTBYTE_CANID32             0x18
#define CANTP_PHYSICAL_CANID_NORMALFIXED      0xDA
#define CANTP_FUNCTIONAL_CANID_NORMALFIXED    0xDB
#define CANTP_PHYSICAL_CANID_MIXED29          0xCE
#define CANTP_FUNCTIONAL_CANID_MIXED29        0xCD

/* CanTp Frame PCI Byte */
#define CANTP_PCI_MASK                 0xF0 /* Mask to Extract PCI */
#define CANTP_SF_PCI                   0x00 /* Single Frame PCI InfoByte */
#define CANTP_FD_SF_PCI                0x00FF/*Single Frame PCI InfoByte for FD*/
#define CANTP_FF_PCI                   0x10 /* First Frame PCI InfoByte */
#define CANTP_CF_PCI                   0x20 /* Consecutive Frame PCI InfoByte
                                            **/
#define CANTP_FC_PCI                   0x30 /* Flow control PCI InfoByte*/
#define CANTP_FS_MASK                  0x0F /* Flow Status mask*/

#define CANTP_FD_SF_FIRST              0x00 /* Single Frame PCI InfoByte#1*/
#define CANTP_FD_FF_FIRST              0x10 /* First Frame PCI InfoByte#1*/
#define CANTP_FD_FF_SECOND             0x00 /* First Frame PCI InfoByte#2*/

/* Confirm States */
#define CANTP_TX_CONF_IDLE             0x00 /* Ideal Tx Confirmation State */
#define CANTP_SF_LF_TX_CONF            0x01 /* Indicates SF or last Frame
                                             *    Tx Confirmation*/
#define CANTP_CF_TX_CONF               0x02 /* Indicates CF Tx Confirmation*/
#define CANTP_FC_TX_CONF               0x03 /* Indicates FC Tx Confirmation*/
#define CANTP_LAST_CF_TX_CONF          0x04 /* Tx Confirmation for FF or last
                                             * CF in a block received */

/* Buffer States */
#define CANTP_TX_NOTRDY                0x00 /* Ideal Tx Buffer State */
#define CANTP_TX_RDY                   0x01 /* Ideal Tx Buffer available */
#define CANTP_TX_NOTRDY_INITREQ        0x02 /* Indicates Tx Buffer Busy */
#define CANTP_RX_NOTRDY_INITREQ        0x04 /* Indicates Rx Buffer unavailable
                                            **/
#define CANTP_RX_RDY                   0x05 /* Indicates Rx Buffer available */
#define CANTP_RX_NOTRDY                0x07 /* Indicates Rx Buffer to be
                                             *   requested */

/* Channel States */
#define CANTP_WAIT                     0x00 /* Ideal Channel State */
#define CANTP_TX_NORMAL                0x01 /* Frame is in Transmit process */
#define CANTP_RX_FC                    0x02 /* Waiting for Rx indication for
                                             *   FC */
#define CANTP_RX_NORMAL                0x03 /* Frame is in receive process */
#define CANTP_FC_TXCONF                0x04 /* Frame is in Transmit FC process
                                            **/
#define CANTP_RX_CF                    0x05 /* Frame is in RX CF process */
#define CANTP_RXBUF_WAIT               0x06 /* Waiting for receive buffer */
#define CANTP_MAX_TX_STATE             0x02 /* If channel state is greater
                                             *   than*/

/*
 * this state then Communication is
 * for reception
 */

#define CANTP_FS_CTS                   0x00 /* Flow Status is Continue To
                                             * Send*/
#define CANTP_FS_WT                    0x01 /* Flow Status is WAIT*/
#define CANTP_FS_OVFLW                 0x02 /* Flow Status is OverFlow*/
/* @Trace: SWS_CanTp_00027 */
/* Note: The CanTp module shall have two internal states, CANTP_OFF and CANTP_ON */
#define CANTP_ON                       0x01 /* Indicate CanTP is initialized */
#define CANTP_OFF                      0x00 /* Indicate CanTP is not initialized */

#define CANTP_TRUE                     ((boolean) 0x01)
#define CANTP_FALSE                    ((boolean) 0x00)

#define CANTP_NAS_TIMER                0x00 /* To access timer array for NAS*/
#define CANTP_NBS_TIMER                0x01 /* To access timer array for NBS*/
#define CANTP_NCS_TIMER                0x02 /* To access timer array for NCS*/
#define CANTP_MAX_FRAME_COUNTER        0x0F /* Max allowed frames */
#define CANTP_NAR_TIMER                0x03 /* To access timer array for NAR*/
#define CANTP_NBR_TIMER                0x04 /* To access timer array for NBR*/
#define CANTP_NCR_TIMER                0x05 /* To access timer array for NCR*/

#define CANTP_STMIN                    ((uint8)0x00) /* To identify STMIN in
                                             * ChangeParameter request */
#define CANTP_BS                       ((uint8)0x01) /* To identify BS in
                                             * ChangeParameter request */

#define CANTP_STMIN_DIRECT_VALUE_RANGE 0x7F /* Indicates STMIN in 0-127ms */

#define CANTP_STMIN_US_LOW             0xF1 /* Indicates STMIN in 100microsec
                                            **/
#define CANTP_STMIN_US_HIGH            0xF9 /* Indicates STMIN in 900microsec
                                            **/
#define CANTP_STMIN_MAP_MASK           0x0F /*Mask to access STMin Maping
                                             * Array*/
#define CANTP_MAX_STMIN_DELAY          0x7F /* Max STMIN 127ms */

#define CANTP_FF_LEN_MASK              0x0F /* First Frame Length Mask */

#define CANTP_MAX_BS_VAL               0xFF /* Max Block size*/

#define CANTP_INFINITE_BS              (uint16)0x1000 /* Infinite block size*/

#define CANTP_INVALID                  ((uint8) 0xFF)

/*First frame or successive frame */
#define CANTP_TX_SFORFF                0xFF /* Indicates FF or Single frame */
#define CANTP_CONSCFRAME               0x00 /* Indicates Consecutive frame */
#define CANTP_MAX_STMINBS_VAL          0xFF /* Upper limit for Blocksize or
                                             * STMIN */


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: SWS_CanTp_00002 SWS_CanTp_00296 */
/* SWS_CanTp_00002: CanTp_<TypeName>Type */
/* SWS_CanTp_00296: implementation-specific types are not "visible" outside of CanTp */
/* @Trace: CanTp_SUD_DATATYPE_009 */
typedef uint8 CanTp_NotifResultType;
/* polyspace +2 MISRA-C3:19.2 [Not a defect:Low] "Union used for handling endian conversion" */
/* @Trace: CanTp_SUD_DATATYPE_010 */
typedef union
{
  uint16 WholeWord;
  /* @Trace: CanTp_SUD_DATATYPE_012 */
  struct
  {
    /* If the processor is Big endian */
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    uint8 MSByte;               /* MS Byte */
    uint8 LSByte;               /* LS Byte */
    /* If the processor is Little endian */
    #else
    uint8 LSByte;               /* LS Byte */
    uint8 MSByte;               /* MS Byte */
    #endif /* End of if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
  } byte_val;
} CanTp_WordAccessType;

/* polyspace +2 MISRA-C3:19.2 [Not a defect:Low] "Union used for handling endian conversion" */
/* @Trace: CanTp_SUD_DATATYPE_011 */
typedef union
{
  uint32 WholeLong;
  /* @Trace: CanTp_SUD_DATATYPE_013 */
  struct
  {
    /* If the processor is Big endian */
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    uint8 MSByte;               /* MS Byte */
    uint8 Byte_2;
    uint8 Byte_1;
    uint8 LSByte;               /* LS Byte */
    /* If the processor is Little endian */
    #else
    uint8 LSByte;               /* LS Byte */
    uint8 Byte_1;               /* Next byte */
    uint8 Byte_2;               /* Two next byte */
    uint8 MSByte;               /* MS Byte */
    #endif /* End of if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
  } byte_val;
} CanTp_LongAccessType;

/* Structure for Channel RAM variables */
/* @Trace: SWS_CanTp_00120 */
/* SWS_CanTp_00120: configure concurrent connections in the CanTp module */
/* @Trace: CanTp_SUD_DATATYPE_014 CanTP_SUD_DATATYPE_004 */
typedef struct
{
  /* Pointer given to Upper layer buffer while Tx*/
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrUpLayerBuff;

  /* Rx_Dl is derived from CAN_DL,
   * get from CanTp RxIndication */
  uint8 RxDl;

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  /* Consumes a meta data item of Up layer */
  VAR(uint8, AUTOMATIC) UpMetaData[CANTP_METADATA_LEN_MAX];
  #endif /* (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */

  #if ((STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
  (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
  (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
  /* Produces/Consumes a meta data item for/from Lo layer CAN_ID_32 */
  VAR(CanTp_LongAccessType, AUTOMATIC) LoMetaData;
  /* Use for Fc transfer */
  VAR(CanTp_LongAccessType, AUTOMATIC) LoFcMetaData;
  #endif /* if ( (STD_ON == CANTP_TX_EXTENDED_ADDRESS) */
  #endif /* End of CANTP_DYNID_SUPPORT */
  /* @Trace: CanTp_SUD_DATATYPE_002 */
  /* SduId in Process */
  PduIdType ActivePduId;

  /* SduLength in process */
  PduLengthType SduLength;
  #if (CANTP_RX_NSDU == STD_ON)

  /* Available Buffer length provided for Rx */
  uint32 AvlBuffLength;
  #endif

  /* Number of bytes remaining for Tx or Rx */
  uint32 ByteCounter;
  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

  /* To hold the max configured wait flow control frame to be transmitted */
  uint16 RxWftMax;
  #endif

  /* Decrete Index */
  uint8 DecreteIndex;

  /* Local Buffer to hold can 2.0 and CanFd*/
  #if (CANTP_FD_SUPPORT == STD_ON)
  /* MaxFDDlc bytes buffer to handle for both CanFD and Can 2.0 */
  uint8 DataBuffer[CANTP_FD_MAX_DLC];
  #else /*(CANTP_FD_SUPPORT == STD_ON)*/
  /* 8 bytes buffer to optimize CanTp Ram allocate */
  uint8 DataBuffer[CANTP_EIGHT];
  #endif /*(CANTP_FD_SUPPORT == STD_ON)*/

  /* To hold CanTp individual channel state */
  uint8 ChannelState;

  /* To hold the position from where data bytes to be processed */
  uint8 LocalDataByteIndex;

  /* To hold the position of PCI Byte */
  uint8 CurrentBytePosition;
  #if ((CANTP_TX_PHYSICAL_ADDRESSING == STD_ON) ||\
  (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON))

  /* To hold the CF sequence number
   * Note: Functional Address only for SF.
   * So, It doesn't need CF counter.
   */
  uint8 FrameCounter;
  #endif

  /* To hold the Tx Confirmation State */
  uint8 TxConfirmState;

  /*To hold the provided buffer status */
  uint8 BufferState;
  #if ((CANTP_TX_PHYSICAL_ADDRESSING == STD_ON) ||\
  (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON))

  /*To hold the Block size of Flow control frame*/
  uint16 BSVar;
  #endif

  /* To hold the Flowstatus of Flow control frame*/
  uint8 FlowStatus;
  #if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON)

  /* To hold the STMin of Flow control frame*/
  uint8 StMinValue;
  #endif

  /* To hold the SF or FF or CF length */
  uint8 CurrentFrameLen;

  /* To indicate the SF or FF */
  uint8 NewFrameFlag;

  /* To indicate the SF or CF or FF*/
  uint8 FrameType;

#ifdef CANTP_DYNID_SUPPORT
  /* Indicate status of MetaData buffer of channel */
  VAR(boolean, AUTOMATIC) AvlMetaDt;
#endif
} CanTp_ChannelRamType;

/* @Trace: SWS_CanTp_00340 */
/* post-build configuration parameters */
/* The following structure is used for all the received PDUs which includes (FC)
 * PDUs. This structure will be used only if there is at least one receive PDU is
 * configured for extended addressing */
/* @Trace: CanTp_SUD_DATATYPE_019 */
typedef struct
{
  /* If the PDU is configured for extended addressing this parameter should
   * give the number of SDUs the PDU is associated
   * If the PDU is configured for normal addressing this parameter gives either
   * RxSduId (if it is a normal receive frame) or gives the TxSduId (if it is
   * a Flow Control frame) */
  PduIdType NoOfPdusOrSduId;

  /* Index to the structure of Nsa and Sdu Mapping
   * If the PDU is not configured for extended addressing this should be
   *   "CANTP_INVALID" */
  PduIdType RxNSaOrNAeSduMapIndex;

  /* Addressing mode of the PDU */
  uint8 AddressingMode;

#ifdef CANTP_DYNID_SUPPORT
  /* Indicate Pdu (CanIf2CanTp) which is configured with metaData */
  boolean InPduwithMetaDataSts;
#endif
} CanTp_RxExtPdusType;

#if (CANTP_RX_NSDU == STD_ON)

/* Rx Nsdu structure for dynamic parameters*/
/* @Trace: CanTp_SUD_DATATYPE_021 */
typedef struct
{
  /* PduId used for upper layer communications */
  PduIdType UpTargetPduId;

  /* PduId used for lower layer Flow control frame CanTp->CanIf communication */
  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)
  PduIdType LoTxFcTargetPduId;
  #endif

  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

  /* Nar timeout value (count) */
  uint16 NarTimeoutValue;
  #endif

  /* Nbr timeout value (count) */
  uint16 NbrTimeoutValue;

  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

  /* Ncr timeout value (count) */
  uint16 NcrTimeoutValue;

  /* RxWftMax */
  uint16 RxWftMax;
  #endif /* End of if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON) */
} CanTp_RxNSduDynamicType;
#endif /* End of if (CANTP_RX_NSDU == STD_ON) */

#if (CANTP_RX_NSDU == STD_ON)

/* Rx Nsdu structure for static parameters */
/* @Trace: CanTp_SUD_DATATYPE_017 */
typedef struct
{
  /* @Trace: SWS_CanTp_00121 SWS_CanTp_00190 */
  /* SWS_CanTp_00121, SWS_CanTp_00190: Each N-SDU is statically linked to one connection channel */
  /* Channel Id */
  CanTp_ChannelType ChannelId;

  /* Target Address Type */
  uint8 TaType;

  /* Addressing mode, '0' - Normal addressing, '1' - extended addressing,
   * '2' - Mixed 11bit addressing, '3' - Mixed 29 bit addressing,
   * '4' - Normal fixed addressing */
  uint8 AddressingMode;
  #if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED29BIT_ADDRESS == STD_ON))
  /* NTa (Extended) or NAe (Mixed/Mixed29Bit) value for Flow Control frame */
  uint8 FcNTaOrNAeValue;

  #endif /* End of #if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
    (CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
    (CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ) */

  #if (CANTP_RX_SDU_PADDING_ACTIVATION == STD_ON)
  /* Padding action, 'TRUE' - Padding activation is STD_ON
   * 'FALSE' - Padding activation is off */
  boolean RxPaddingActivation;
  #endif
#ifdef CANTP_DYNID_SUPPORT
  /* Indicate Pdu (CanIf2CanTp) which is configured with metaData */
  boolean InPduwithMetaDataSts;
#if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  /* Indicate Pdu (CanTp2PduR) which is configured with metaData */
  boolean OutPduwithMetaDataSts;
#endif
#endif
} CanTp_RxNsduStaticType;
#endif /* End of if (CANTP_RX_NSDU == STD_ON) */

#if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

/* Rx Nsdu RAM structure */
/* @Trace: CanTp_SUD_DATATYPE_015*/ 
typedef struct
{
  /* Maximum number of N-PDUs the CanTp receiver allows the sender to send */
  uint8 BlockSize;

  /* Separation  time between the transmissions of two CF N-PDU */
  uint8 STMin;
} CanTp_STminBsType;
#endif /* (CANTP_RX_PHYSICAL_ADDRESSING) */

/* polyspace:end<MISRA-C:18.4:Not a defect:Justify with annotations> Union used for handling endian conversion */
#if (CANTP_TX_NSDU == STD_ON)

/* Tx Nsdu structure for dynamic parameters */
/* @Trace: CanTp_SUD_DATATYPE_020 */
typedef struct
{
  /* Confirmation SduId used for upper layer */
  PduIdType UpConfirmationSduId;

  /* PduId used for lower layer data transfer communication */
  PduIdType LoTargetPduId;

  /* Nas timeout value (count) */
  uint16 NasTimeoutValue;

  #if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON)

  /* Nbs timeout value (count) */
  uint16 NbsTimeoutValue;

  /* Ncs timeout value (count) */
  uint16 NcsTimeoutValue;
  #endif /* End of if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON) */
} CanTp_TxNSduDynamicType;
#endif /* End of if (CANTP_TX_NSDU == STD_ON) */

#if (CANTP_TX_NSDU == STD_ON)

/* Tx Nsdu structure for static parameters */
/* @Trace: CanTp_SUD_DATATYPE_016 */
typedef struct
{
   /* @Trace: SWS_CanTp_00121 SWS_CanTp_00190 */
   /* SWS_CanTp_00121, SWS_CanTp_00190: Each N-SDU is statically linked to one connection channel */
  /* Channel Id */
  CanTp_ChannelType ChannelId;

  /* Target address Type, '0'-Physical addressing, '1'- Functional addressing */
  uint8 TaType;

  /* Addressing mode, '0' - Normal addressing, '1' - extended addressing,
   * '2' - Mixed 11bit addressing, '3' - Mixed 29 bit addressing
   * '4' - Normal fixed addressing */
  uint8 AddressingMode;
  #if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
   (CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
   (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON))
  /* NTa or NAe value */
  uint8 NTaOrNAeValue;
  #endif /* End of #if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
                      (CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
                      (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON)) */
  #ifdef CANTP_DYNID_SUPPORT
  /* Indicate Pdu (CanTp2CanIf) which is configured with metaData */
  boolean OutTxPduwithMetaDataSts;
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  /* Indicate Pdu (PduR2CanTp) which is configured with metaData */
  boolean InTxPduwithMetaDataSts;
  #endif /* #if (STD_OFF == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #if ((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
   (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
  /* When DynIdSupport is enabled, CanTpNSa is also required
   * for each TxNSdu with AddressingFormat CANTP_NORMALFIXED or
   * CANTP_MIXED29BIT.
   */
  uint8 TxNSa;

  /* When DynIdSupport is enabled and GenericConnectionSupport
   * is not enabled, CanTpNTa is also required for each TxNSdu
   * with AddressingFormat CANTP_NORMALFIXED or CANTP_MIXED29BIT.
   */
  uint8 TxNTa;
  #endif /* #if ((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) */
  #endif /* #ifdef CANTP_DYNID_SUPPORT */
  #if (CANTP_TX_SDU_PADDING_ACTIVATION == STD_ON)
  /* Padding action, 'TRUE' - Padding activation is STD_ON
   * 'FALSE' - Padding activation is off  */
  boolean TxPaddingActivation;
  #endif /* #if (CANTP_TX_SDU_PADDING_ACTIVATION == STD_ON) */
  #if (CANTP_TC == STD_ON)
  /* 'TRUE'- Cancel transmit activation is STD_ON
   * 'FALSE'- Cancel transmit activation is STD_OFF  */
  boolean TxCancelTransmitAct;
  #endif /* #if (CANTP_TC == STD_ON) */

  /* The maximum Tx length of the N-PDU shall be derived
   * from the PduLength configuration parameter of EcuC
   * */
  uint8 TxSduMaxLength;
} CanTp_TxNsduStaticType;
#endif /* End of if (CANTP_TX_NSDU == STD_ON) */

/* The following structure is generated for each receive PDU if it is
 * configured for mixed/extended addressing. In case of Rx FC frames, if the
 * associated Tx PDU is configured for mixed/extended addressing this will be
 * generated.
 */
#if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
(CANTP_TX_NORMALFIXED_ADDRESS == STD_ON) ||\
(CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
(CANTP_RX_NORMALFIXED_ADDRESS == STD_ON))
/* @Trace: CanTp_SUD_DATATYPE_018 */
typedef struct
{
  /* If the PDU belongs to the Rx FC then this should be CanTpTxNSduId
   * else this should be index of RxNSduId */
  PduIdType SduIndex;

  /* RxN_TA (CanTpNSa): Extended addressing only
   * RxN_Ae (CanTpNAe): Mixed Addressing and Mixed29bit
   */
  uint8 RxNTaOrNAe;

#ifdef CANTP_DYNID_SUPPORT
#if((CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
  (CANTP_RX_NORMALFIXED_ADDRESS == STD_ON) ||\
  (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
  (CANTP_TX_NORMALFIXED_ADDRESS == STD_ON))
  /* CanTpNSa */
  uint8 RxNTa;

  /* CanTpNTa */
  uint8 RxNSa;
#endif
#endif
} CanTp_RxNSaOrNAeSduMappingType;
#endif /* End of #if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
(CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED29BIT_ADDRESS == STD_ON))
 */

typedef struct
{
	#if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)

    #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
	P2CONST(CanTp_ChannelType, AUTOMATIC, CANTP_CONST) PtrRxSduMap;
    #endif

	#if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
	(CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
	(CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
	(CANTP_TX_NORMALFIXED_ADDRESS == STD_ON) ||\
	(CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
	(CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
	(CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
	(CANTP_RX_NORMALFIXED_ADDRESS == STD_ON))
	/* Nsa and Sdu Mapping */
	P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CONST) PtrNSaOrNAeSduMapping;
	#endif /* End of #if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
	(CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
	(CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
	(CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
	(CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
	(CANTP_RX_MIXED29BIT_ADDRESS == STD_ON)) */

    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    #if ((STD_ON == CANTP_TX_NSDU) ||\
    (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
    (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
    (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
	P2CONST(CanTp_RxExtPdusType, AUTOMATIC, CANTP_CONST) PtrRxExtFcPdus;
    #endif /* ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)) */
    #endif

    #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
    || (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
    (STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (STD_ON == CANTP_RX_MIXED_ADDRESS)\
    || (STD_ON == CANTP_DEV_ERROR_DETECT) \
    || (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) \
    || (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) \
    || (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) \
    || (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
	P2CONST(CanTp_RxExtPdusType, AUTOMATIC, CANTP_CONST) PtrRxExtPdus;
    #endif

    #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
	P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) PtrRxNSduDynamic;
    #endif /* ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)) */

    #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING))
	P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) PtrRxNSduStatic;
    #endif /* ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)) */

    #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)
	P2VAR(CanTp_STminBsType, AUTOMATIC, CANTP_VAR) PtrSTminBs;
    #endif

    /*#if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
	P2CONST(CanTp_TxNSduDynamicType, AUTOMATIC, CANTP_VAR) PtrTxNSduDynamic;
    #endif*/

	#if (CANTP_TX_NSDU == STD_ON)
	P2CONST(CanTp_TxNSduDynamicType, AUTOMATIC, CANTP_VAR) PtrTxNSduDynamic;
	P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_VAR) PtrTxNSduStatic;
    #endif

    #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_NSDU))
    uint16 TotalRxTxChannels;
    #endif
    #else
    /* MainfunctionPeriod value */
    uint8 MainfunctionPeriod;
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
} CanTp_ConfigType;


// #if (CANTP_VARIANT_POSTBUILD_SUPPORT == STD_ON)
// #define CANTP_START_SEC_CONST_UNSPECIFIED
// #include "MemMap.h"
// extern CONST(CanTp_ConfigType, CANTP_CONST) CanTp_Config[CANTP_NO_OF_VARIANT];
// #define CANTP_STOP_SEC_CONST_UNSPECIFIED
// #include "MemMap.h"
// #endif

/*******************************************************************************
**                      MACROs                                                **
*******************************************************************************/
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Low] "No Impact of this rule violation" */
#define CANTP_TIMER_UPDATE_MACRO(Channel, Timer, TimerValue)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_Timers[(uint8)(Channel)][(uint8)(Timer)] = (uint16)(TimerValue);\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)

/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Low] "No Impact of this rule violation" */
#define CANTP_STOP_ALL_TX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_Timers\
    [CanTp_ChannelMapping[(uint8)(Channel)]][(uint8)CANTP_NAS_TIMER]\
      = (uint16)CANTP_ZERO;\
    CanTp_Timers\
    [CanTp_ChannelMapping[(uint8)(Channel)]][(uint8)CANTP_NBS_TIMER]\
      = (uint16)CANTP_ZERO;\
    CanTp_Timers[CanTp_ChannelMapping[(uint8)(Channel)]][CANTP_NCS_TIMER]\
      = (uint16)CANTP_ZERO;\
    CanTp_StMinTimers[(Channel)] = (uint8)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)

/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Low] "No Impact of this rule violation" */
#define CANTP_STOP_ALL_RX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_Timers[(uint8)(Channel)][(uint8)CANTP_NAR_TIMER] = (uint16)CANTP_ZERO;\
    CanTp_Timers[(uint8)(Channel)][(uint8)CANTP_NBR_TIMER] = (uint16)CANTP_ZERO;\
    CanTp_Timers[(uint8)(Channel)][(uint8)CANTP_NCR_TIMER] = (uint16)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANTP_INTTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

