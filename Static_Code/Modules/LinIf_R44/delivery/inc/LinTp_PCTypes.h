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
**  SRC-MODULE: LinTp_PCTypes.h                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : It contains all configuration time parameters.                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date           By                 Description                **
********************************************************************************
** 1.0.7         03-Nov-2022    KhaLN1             #CP44-1100                 **
** 1.0.6         17-Oct-2022    KhaLN1             #CP44-563                  **
** 1.0.3         17-Sep-2021    DuyNGB             R44-Redmine #20121         **
** 1.0.1         20-Apr-2021    LongTQB            R44-Redmine #17195         **
** 1.0.0         22-Dec-2020    SJ Kim             Initial version            **
*******************************************************************************/
#ifndef LINTP_PCTYPES_H
#define LINTP_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTp.h" /* LinIf header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* @Trace: LinTp_SUD_MACRO_015 */
/* COMTYPE018 General return codes for NotifResultType */
#define NTFRSLT_OK                     (uint8)0x00
#define NTFRSLT_E_NOT_OK               (uint8)0x01
#define NTFRSLT_E_TIMEOUT_A            (uint8)0x02
#define NTFRSLT_E_TIMEOUT_BS           (uint8)0x03
#define NTFRSLT_E_TIMEOUT_CR           (uint8)0x04
#define NTFRSLT_E_WRONG_SN             (uint8)0x05
#define NTFRSLT_E_INVALID_FS           (uint8)0x06
#define NTFRSLT_E_UNEXP_PDU            (uint8)0x07
#define NTFRSLT_E_WFT_OVRN             (uint8)0x08
#define NTFRSLT_E_ABORT                (uint8)0x09
#define NTFRSLT_E_NO_BUFFER            (uint8)0x0A

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: LinIf_SUD_DATATYPE_023 */
/* Structure for LINTP Channel RAM data */
typedef struct
{
  /* Pointer to store the upper layer buffer address */
  P2VAR(uint8, AUTOMATIC, LINTP_DATA) pTpBuffPtr;
  /* Current ongoing TP message SDUID */
  PduIdType ddActiveTpPduId;
  /* TP message SDUID requested in MRF */
  PduIdType ddMRFSduId;
  /* Current ongoing TP message length */
  PduLengthType ddTpSduLength;
  /* TP bytes to Transmitted or Received */
  uint16 usTpByteCounter;
  /* Timer for P2 timeout supervision */
  uint16 usP2TimerCounter;
  /* counter which counts the current number of Response pending frames */
  uint16 usRespPendingFrameCounter;
  /* Temporary buffer */
  uint8 aaLinTpBuffer[LINTP_EIGHT];
  /* Present TP session NAD */
  uint8 ucActiveNad;
  /* Master request NAD */
  uint8 ucRequestedNad;
  /* Frame counter */
  uint8 ucTpFrameCounter;
  /* 0-UNINIT, 1-IDLE, 2-TX_BUSY_BUFF_RDY,
   * 3-TX_BUSY_BUFF_NOT_RDY, 4-RX_BUSY_BUFF_RDY,
   * 5-RX_BUSY_BUFF_NOT_RDY
   */
  uint8 ucLinTpStatus;
  /* Incase of Rx - '0' local buffer does not have received data
   *                '1' local buffer is having received data
   * Incase of Tx - this parameter indicates the byte number from
   * which onwards the data bytes needs to be copied from upper layer
   */
  uint8 ucLocalTpData;
  /* Present TP session RSID */
  uint8 ucLinTpRsid;
  /* '0' TP header not sent, '1' TP header sent */
  boolean blTpHeaderSent;
  /* '0' P2Timer initially not loaded, '1' P2Timer initially loaded */
  boolean blP2TimerInitialLoad;
  /* '0' if current frame is not first frame, '1' if current frame is first
   * frame
   */
  boolean blFirstFrame;
  /* '0' if the buffer availability is less, '1' if the buffer sufficient
   * availability is less
   */
  boolean blAvblBuff;
}LinTp_ChannelRamData;

/* @Trace: LinIf_SUD_DATATYPE_024 */
typedef struct
{
  /* Max number of Response Pending Frames */
  uint16 usMaxRespPendingFrames;

  /* P2*max timeout when a response pending frame is expected in seconds. */
  uint16 usP2Max;

  /* Definition of the P2max timeout observation parameter in seconds. */
  uint16 usP2Timing;

  /* Pointer to channel RAM data */
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) pLinTpChannelRamData;

  /* First Rx Pduid referring to the channel */
  uint8 ddTpRxMsgIndex;

  /* No. of Rx Pdus referring to the channel*/
  uint8 ddNoOfTpRxMsgs;

  /* Bit0:Configures if TP Frames of not requested LIN-Slaves are dropped or not
   * Dependent on LinTpDropNotRequestedNad
   * 0: Do drop TP Frames of Not requested LIN-Slaves
   * 1: Drop not TP Frames of Not requested LIN-Slaves
   * Bit1:Enables or disables the call of BswM_LinTp_RequestMode() to diagnostic
   * request/response schedule. 0: BswM is not called, 1: BswM is called
   * Dependent on LinTpScheduleChangeDiag
  */
  uint8 ucLinTpChannelStatus;

  /* Corresponding TP channel number */
  uint8 ucTpChannelIndex;

}LinTp_ChannelInfo;

/* @Trace: LinIf_SUD_DATATYPE_025 */
/* Structure for Tp Rx message information */
typedef struct
{
  /* TP Rx messgae SduId */
  PduIdType ddTpRxPduId;
  /* TP Rx message length */
  PduLengthType ddTpRxSduLength;
  /* Timer for N_Cr timeout supervision */
  uint16 usNcrTimerCounter;
  /* Tp Channel index to which this Tx PDU
   * is associated */
  uint8 ucTpRxChannelIndex;
  /* TP Rx message NAd */
  uint8 ucTpNad;
}LinTp_RxMsg;

/* @Trace: LinIf_SUD_DATATYPE_026 */
/* Structure for Tp Tx message information */
typedef struct
{
  /* TP Tx messgae SduId */
  PduIdType ddTpTxPduId;
    /* Timer for N_As timeout supervision */
  uint16 usNasTimerCounter;
  /* Timer for N_Cs timeout supervision */
  uint16 usNcsTimerCounter;
  /* Tp Channel index to which this Tx PDU
   * is associated */
  uint8 ucTpTxChannelIndex;
  /* TP Tx message Nad */
  uint8 ucTpNad;
}LinTp_TxMsg;

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

#ifdef LINIF_TP_CHANNELS
#define LINTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for LIN Channel Information */
extern CONST(LinTp_ChannelInfo, LINTP_CONST) LinTp_GaaChannelInfo[LINIF_TP_CHANNELS];
#define LINTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#ifdef LINIF_MAX_TX_SDU
#define LINTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for LIN TP transmit message */
extern CONST(LinTp_TxMsg, LINTP_CONST) LinTp_GaaTxMsg[LINIF_MAX_TX_SDU];
#define LINTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#ifdef LINIF_MAX_RX_SDU
#define LINTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for LIN TP receive message */
extern CONST(LinTp_RxMsg, LINTP_CONST) LinTp_GaaRxMsg[LINIF_MAX_RX_SDU];
#define LINTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/* #define LINTP_START_SEC_CONST_UNSPECIFIED
 * #include "MemMap.h"
 * extern CONST(LinTp_ConfigType, LINTP_CONST) LinTp_GaaConfig[];
 * #define LINTP_STOP_SEC_CONST_UNSPECIFIED
 * #include "MemMap.h"
 */


/*
 * Library
 */
#define LINTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint16, LINTP_CONST) LinIf_Tp_Channels;
extern CONST(uint16, LINTP_CONST) LinIf_Max_Rx_Sdu;
extern CONST(uint16, LINTP_CONST) LinIf_Max_Tx_Sdu;
#define LINTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"



/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* LINTP_PBTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
