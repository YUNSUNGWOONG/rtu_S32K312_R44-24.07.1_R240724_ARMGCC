/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm_IntTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : File conatins structure defination                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date         By                Description                       **
********************************************************************************
** 1.1.6     16-Jun-2023  HieuTM8           #CP44-2100                        **
** 1.1.4     31-Jan-2023  NamNT1            CP44 #1098                        **
** 1.1.3     16-Dec-2022  NamNT1            BUGCLASSIC-374, CP44-1326         **
** 1.1.1     07-Oct-2022  NamNT1            CP44 #785, #786, #610, #838, #842 **
**                                          #887                              **
** 1.1.0     09-Jun-2022  SMKwon            R44-Redmine #28017, #29362        **
** 1.0.2.1   20-Jun-2022  SM Kwon           CP44-120                          **
** 1.0.2     29-Apr-2022  ThuanVT           R44-Redmine #25510                **
** 1.0.0     16-Dec-2020  SHKim             Initial Version                   **
*******************************************************************************/

#ifndef CANNM_INTTYPES_H
#define CANNM_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanNm_Cfg.h"            /* CanNm Configuration header file */
#include "SchM_CanNm.h"           /* CanNm Schm functions header file */
#include "Nm.h"                   /* Nm Header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanNm_SUD_MACRO_001 */
/* AUTOSAR specification version information */
#define CANNM_INTTYPES_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define CANNM_INTTYPES_AR_RELEASE_MINOR_VERSION       (0x04u)
#define CANNM_INTTYPES_AR_RELEASE_REVISION_VERSION    (0x00u)

/* File version information */
#define CANNM_INTTYPES_SW_MAJOR_VERSION         (0x01u)
#define CANNM_INTTYPES_SW_MINOR_VERSION         (0x02u)
#define CANNM_INTTYPES_SW_PATCH_VERSION         (0x00u)

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/

/* Time for which the NM shall stay in the Prepare-bus Sleep mode before
 *   transiting into the Bus-Sleep mode */
/* @Trace: CanNm_SUD_MACRO_005 */
/* Macros for numerical Values */
#define CANNM_ZERO                             (uint8) 0x00
#define CANNM_ONE                              (uint8) 0x01
#define CANNM_SEVEN                            (uint8) 0x07
#define CANNM_EIGHT                            (uint8) 0x08
#define CANNM_MAX_PDU_SIZE                     (uint8) 0x40
#define CANNM_MAX_PDU_INFO_SIZE                (uint8) 0x1f

/* Macros for Bit order */
#define CANNM_BYTE0                            (0U)

/* Macros for user data Values */
#define CANNM_MAX_DATA                         (uint8) 0xFF

/* Macros for boolean Values */
#define CANNM_FALSE                            0
#define CANNM_TRUE                             1

typedef uint16 CanNm_TimeType;

/* CanNm Modes and states */
/* @Trace: CanNm_SUD_DATATYPE_016 */
typedef enum {
  CANNM_STATE_UNINIT = 0x00,
  CANNM_BUS_SLEEP_MODE,
  CANNM_PREPAREBUS_SLEEP_MODE,
  CANNM_READY_SLEEP_STATE,
  CANNM_NORMAL_OPERATION_STATE,
  CANNM_REPEAT_MESSAGE_STATE
} CanNm_ModeState;

/* CanNm Modes and states */
/* @Trace: CanNm_SUD_DATATYPE_018 */
typedef enum {
  CANNM_RX_HANDLING_METHOD_IGNORE = 0x00,
  CANNM_RX_HANDLING_METHOD_PROCESS_WITH_PARTIAL_NETWORK,
  CANNM_RX_HANDLING_METHOD_PROCESS_WITHOUT_PARTIAL_NETWORK
} CANNM_RX_HANDLING_METHOD;


typedef enum {
  NM_STATE_UNDEFINED = 0x00,
  NM_STATE_NS_RMS = 0x04,
  NM_STATE_NS_RSS = 0x08,
  NM_STATE_RMS_BSM = 0x01,
  NM_STATE_RMS_PBSM = 0x02,
  NM_STATE_RMS_NS = 0x20,
  NM_STATE_RMS_RSS = 0x10,
  NM_STATE_RSS_RMS = 0x00,
  NM_STATE_RSS_NS = 0x00,
  NM_STATE_PBSM_RSS = 0x00,
  NM_STATE_BSM_PBSM = 0x00,
} NM_STATE;

/* Macro for repeat msg and network request */
#define CANNM_REPTMSG_BIT                      (uint8) 0x01
#define CANNM_ACTWKP_BIT                       (uint8) 0x10
#define CANNM_SETSLEEP_BIT                     (uint8) 0x08
#define CANNM_PNI_BIT                          (uint8) 0x40

/* Macro for length of Meta data */
#define CANNM_METADATA_LENGTH                  (uint8) 0x04
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*The following structure contains Pre-Compile time configuration required for
 *   CANNM module */
/* @Trace: SRS_BSW_00405 */
/* BYTE MASK TYPE */
/* @Trace: CanNm_SUD_DATATYPE_012 */
typedef struct
{
  uint8 byteIndex;
  uint8 byteValue;
} CanNm_PnByteMskType;

/* @Trace: CanNm_SUD_DATATYPE_014 */
typedef struct
{
  /* CanNmPnInfoLength */
  uint8 pnInfoLength;

  /* CanNmPnInfoOffset */
  uint8 pnInfoOffset;
} CanNm_PnInfoType;

/* @Trace: CanNm_SUD_DATATYPE_013 */
typedef struct
{
   PduIdType canNmRxPduId;
   uint32 canNmChannelIndex;
} CanNm_RxPdu;

/* @Trace: CanNm_SUD_DATATYPE_015 */
typedef struct
{
   PduIdType canNmTxPduId;
   uint32 canNmChannelIndex;
} CanNm_TxPdu;

/* Structure for CanNm_PduPosition Type*/
/* @Trace: CanNm_SUD_DATATYPE_017 */
typedef enum
{
  CANNM_PDU_BYTE_0 = 0x00,
  CANNM_PDU_BYTE_1 = 0x01,
  CANNM_PDU_BYTE_2 = 0x02,
  CANNM_PDU_BYTE_3 = 0x03,
  CANNM_PDU_OFF = 0xFF
} CanNm_PduPositionType;

/* @Trace: CanNm_SUD_DATATYPE_011 */
typedef struct
{
  /* Time for which the NM shall stay in the Prepare-bus Sleep mode before
   *   transiting into the Bus-Sleep mode */
  CanNm_TimeType waitBusSleepTime;

  /* NM Timeout time for NM PDU�s */
  CanNm_TimeType ntwkTimeOutTime;

  /* Timeout time for Repeat message state */
  CanNm_TimeType repeatMsgTime;

  /* Timeout time for Remote Sleep Indication */
  CanNm_TimeType remoteSleepIndTime;
  
  /* Node specific bus cycle time in the periodic transmission mode with bus
   *   load reduction */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  #if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
  CanNm_TimeType msgReducedTime;
  #endif /* #if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON) */
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

  /* Period of NM Message */
  CanNm_TimeType msgCycleTime;

  /* Time offset in the periodic transmission mode */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  CanNm_TimeType msgCycleOffset;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

  /* CanNm shall not perform transmission error handling */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  /* Transmission Timeout time of NM-message */
  CanNm_TimeType msgTimeOutTime;
  #endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

  /* Period of Immediate NM Message */
  CanNm_TimeType immMsgCycleTime;
  
  /* L-PDU handle of the NM PDU to be transmitted by CanIf_Transmit */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  PduIdType txPduId;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

  /* PDUR ERA PDU ID */
  #if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
  PduIdType pnEraRxNSduHandleId;
  #endif /* #if (CANNM_PN_ERA_CALC_ENABLED == STD_ON) */

  /* CanNm Tx user data PDU ID */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  PduIdType canNmTransmitHandleId;
  #endif /* CANNM_POSTBUILD_SUPPORTED */
  
  /* PDUR user data PDU ID */
  PduIdType txTriggerUserPduId;

  /* Represent CarWakeup Byte position and Bit position
   *                                       (CanNmCarWakeUpBytePosition)  */
  uint8 carWakeupByte;
  
  /* CanNm Car WakeUp Node ID (CanNmCarWakeUpFilterNodeId) */
  uint8 carWkpNodeId;

  /* CanNm Car WakeUp Mask based on CarWakeup bit(CanNmCarWakeUpBitPosition) */
  uint8 carWakeupMask;

  /* Number of Nm messages to be transmitted by immMsgCycleTime*/
  uint8 noOfImmediateNmTx;

  /* Length of the data contained in the NM PDU */
  uint8 userDataLength;

  /* Length of the Nm PDU */
  uint8 pduLength;

  /* Position of the source node identifier within the NM PDU */
  CanNm_PduPositionType pduNidPosition;

  /* Index of the user data array */
  uint8 userDataPosition;

  /* Position of the control bit vector within the NM PDU */
  CanNm_PduPositionType pduCbvPosition;
  
  /* CanNm Channel Node ID */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  uint8 nodeId;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

  /* Channel handle to be passed to the upper layer (NM Interface) */
  NetworkHandleType comMChannelId;

  /* Bus load reduction active for a particular NM channel */
  boolean busLoadRedActive;
  
  /* CanNmActiveWakeupBitEnabled */
  boolean activeWakeupBitEnabled;
  
  /* CanNmAllNmMessagesKeepAwake */
  boolean allNmMessagesKeepAwake;
  
  /* CanNmPnEnabled */
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  boolean pnEnabled;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */
  
  /* CanNmPnEraCalcEnabled */
  boolean pnEraCalcEnabled;
  
  /* CanNmCarWakeUpRxEnabled */
  boolean carWakeUpRxEnabled;
  
  /* CanNmCarWakeUpFilterEnabled */
  boolean carWakeUpFilterEnabled;
  
  /* CanNmPnHandleMultipleNetworkRequests */
  boolean pnHandleMultipleNetworkRequests;

  /* Value of CanIfTxPduTriggerTransmit*/
  boolean canIfTriggerTransmit;

  /* Node detection enables/disables */
  boolean nodeDetectionEnabled;

  /* CanNmForcePnAvailabilityConfEnabled */
  boolean forcePnAvailabilityConfEnabled;

  /* Position of the control bit vector within the NM PDU */
  CanNm_PduPositionType nmStatePosition;

  /* Position of the control bit vector within the NM PDU */
  CanNm_PduPositionType nwRequestReasonPosition;

  /* Initial value of each byte of user data within the NM PDU */
  uint8 userDataInitValue;
} CanNm_StaticChannel;

/* Structure for Channel postbuild data */
/* @Trace: CanNm_SUD_DATATYPE_009 */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
typedef struct
{
  /* Node specific bus cycle time in the periodic transmission mode with bus
   *   load reduction */
  #if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
  CanNm_TimeType msgReducedTime;
  #endif /* #if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON) */

  /* Time offset in the periodic transmission mode */
  CanNm_TimeType msgCycleOffset;

  /* CanNm shall not perform transmission error handling */
  #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  /* Transmission Timeout time of NM-message */
  CanNm_TimeType msgTimeOutTime;
  #endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

  /* L-PDU handle of the NM PDU to be transmitted by CanIf_Transmit */
  PduIdType txPduId;

  /* CanNm Tx user data PDU ID */
  PduIdType canNmTransmitHandleId;

  /* CanNm Channel Node ID */
  uint8 nodeId;

  /* CanNmPnEnabled */
  boolean pnEnabled;
} CanNm_ChannelConfigType;
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

/* @Trace: CanNm_SUD_DATATYPE_010 */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
typedef struct
{
  /* Pointer point to PN filter mask byte */
  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  const uint8* pnFilterMaskBytePtr;
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
  
  /* Pointer point to channel data */
  const CanNm_ChannelConfigType* channelsConfigPtr;

  /* Pointer point to Rx Pdu ID array */
  const CanNm_RxPdu* rxPduIdPtr;

  /* Number of Rx Pdu */
  uint32 numberOfRxPdu;
} CanNm_ConfigType;
#else
typedef struct
{
  uint8 dummy;
} CanNm_ConfigType;
#endif /* (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanNm_SUD_GLOBALVAR_013 */
/* extern definition for Channel configuration information array
 *   (for all active channels) */
extern CONST(CanNm_StaticChannel, CANNM_CONST) CanNm_ArrayStaticChannel[CANNM_NUMBER_OF_CHANNEL];
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanNm_SUD_GLOBALVAR_011 */
extern CONST(CanNm_TxPdu, CANNM_CONST) CanNm_ArrayTxPdu[CANNM_NUMBER_OF_TXPDU];
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanNm_SUD_GLOBALVAR_012 */
extern CONST(CanNm_RxPdu, CANNM_CONST) CanNm_ArrayRxPdu[CANNM_NUMBER_OF_RXPDU];
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/* @Trace: CanNm_SUD_GLOBALVAR_014 */
extern VAR(uint8, CANNM_VAR) CanNm_ArrayPnEIRAPdu[CANNM_MAX_PDU_SIZE];
#define CANNM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanNm_SUD_GLOBALVAR_015 */
extern VAR(CanNm_TimeType, CANNM_VAR) CanNm_ArrayPnEIRATimer[(CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE * CANNM_EIGHT)];
#define CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#endif /* CANNM_INTTYPES_H */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
