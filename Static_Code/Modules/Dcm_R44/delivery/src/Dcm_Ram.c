/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_Ram.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Global variable definitions                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     14-Aug-2020   HueKM          Change data of SID2A as per #14836  **
** 0.0.3     30-Sep-2020   HueKM          Remove unused variables             **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1799                    **
** 1.0.13    10-Jul-2023   DanhTQ1        Refer #CP44-2474                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-2768,                   **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-2730                    **
** 1.1.2     13-Nov-2023   DH Kwak        Refer #CP44-3122                    **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
** 1.4.1     01-Apr-2024   DanhTQ1        Refer #CP44-3362                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Ram.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
** Variables of boolean                                                       **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

VAR(boolean, DCM_VAR) Dcm_GblReset;

VAR(boolean, DCM_VAR) Dcm_GblSendResOnReset;

VAR(boolean, DCM_VAR) Dcm_GblJumpToBootloader;

VAR(boolean, DCM_VAR) Dcm_IsBlockSeqCounterRollOver;

/* Store initialization status of Dcm */
VAR(boolean, DCM_VAR_POWER_ON_INIT) Dcm_GblInitStatus;

/* Store the status of the normal transmission */
VAR(boolean, DCM_VAR) Dcm_GblNormalReq;

/* sg.baek 022305 - Task #2163 in redmine */
VAR(boolean, DCM_VAR) Dcm_GblProcessNewRequest;

#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
/* Store the status of the second request*/
VAR(boolean, DCM_VAR) Dcm_GblSecDeclRequest;
#endif

#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
VAR(boolean, DCM_VAR) Dcm_GblProcessPendingRequest;

VAR(boolean, DCM_VAR) Dcm_GblAddPendingRequestToQueue;
#endif

VAR(boolean, DCM_VAR) Dcm_GblSendResponse;

VAR(boolean, DCM_VAR) Dcm_GblRespPendConfirmation;

VAR(boolean, DCM_VAR) Dcm_GblPduRTransmitResponse;

VAR(boolean, DCM_VAR) Dcm_TriggerCancelPendingOperation;

/* Store the status of current did */
VAR(boolean, DCM_VAR) Dcm_GblDIDRangePresent;

VAR(boolean, DCM_VAR) Dcm_GblDTCFDCPending;

VAR(boolean, DCM_VAR) Dcm_GblFaultDetectionCounter;

/* Store the number of Filter Dtc By Severity mask */
VAR(boolean, DCM_VAR) Dcm_GblNumFilterDTCStatusBySevirtMask;

#if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
VAR(boolean, DCM_VAR) Dcm_GblDTCSettingDisabled;
#endif

#if ((DCM_READ_ITC_SERVICE_SUPPRT == STD_ON) ||\
     (DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON))
VAR(boolean, DCM_VAR) Dcm_InternalTroubleCodeService;
#endif

#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* Store the requested serviceToRespondTo */
VAR(boolean, DCM_VAR) Dcm_GblRoeClearAll;
#endif

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
VAR(boolean, DCM_VAR) Dcm_GblAvailabilityPIDFlag;
#endif

#if ((DCM_ECURESET_SERVICE == STD_ON) || \
     (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON))
VAR(boolean, DCM_VAR) Dcm_GblExecuteECUReset;
#endif

#if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        (DCM_RESPONSE_ONEVENT_BLOCKID > 0))
VAR(boolean, DCM_VAR) Dcm_GblNvMReadBlock;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
** Variables of 8-bit size                                                    **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Store the status of first time calling main function */
VAR(uint8, DCM_VAR) Dcm_GblFirstCallToMain;

/* Array for Present Date WriteMemory Data values */
VAR(uint8, DCM_VAR) Dcm_GaaPresentDate[DCM_THREE];

/* Store the Subfunction respective to the request*/
VAR(uint8, DCM_VAR) Dcm_GucSubFunction;

/* Store current protocol priority */
VAR(uint8, DCM_VAR) Dcm_GucPrtclPriority;

/* Store the communication mode */
VAR(uint8, DCM_VAR) Dcm_GaaCommMode[DCM_NO_OF_COMM_CHANNELS];

/* Store pointer to the request or response data */
P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_GpReqResData;


/* To store PID Count */
VAR(uint8, DCM_VAR) Dcm_GucPIDCount;

/* To indicate ID belongs to Availability list */
VAR(uint8, DCM_VAR) Dcm_GucAvlState;

VAR(uint8, DCM_VAR) Dcm_GaaPidSignalData[DCM_THIRTY_TWO];


VAR(uint8, DCM_VAR) Dcm_GucReadGlobal;

VAR(uint8, DCM_VAR) Dcm_GucTranslationType;

VAR(uint8, DCM_VAR) Dcm_GucMemorySelection;

VAR(uint8, DCM_VAR) Dcm_GucAvailableDTCStatusMask;

VAR(uint8, DCM_VAR) Dcm_GucFunctionalGroupIdentifier;

#if (DCM_J1979_2_SUPPORT == STD_ON)
/* Trace: DCM_19792_56_11 */
VAR(uint8, DCM_VAR) Dcm_GucReadinessGroupIdentifier;
/* Trace: DCM_19792_1A_07 */
VAR(uint8, DCM_VAR) Dcm_GucExtendedDataRecordNumber;
#endif /* J19792 */

#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Store record number */
VAR(uint8, DCM_VAR) Dcm_GucNumofDTC;

VAR(uint8, DCM_VAR) Dcm_GucRecordNumber;
#endif


#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
VAR(uint8, DCM_VAR) Dcm_GucSecurSequChk;

VAR(uint8, DCM_VAR) Dcm_GaaSeed[DCM_MAX_SECURITY_SEED_SIZE];
#endif


#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
     (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
/* Store SubNetValue for service 0x28 */
VAR(uint8, DCM_VAR) Dcm_GucSubNetValue;

/* Store CommunicationModeType for service 0x28 */
VAR(uint8, DCM_VAR) Dcm_GucCommunicationModeType;

/* Store CommunicationModeType for service 0x28 */
VAR(Dcm_CommunicationModeType, DCM_VAR) Dcm_GucComCtrlMode;
#endif


#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
VAR(uint8, DCM_VAR) Dcm_GucMemAddrSizeBytes;

VAR(uint8, DCM_VAR) Dcm_GucMemoryIdentifier;

P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_GpWriteData;
#endif

#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* Store the status of the ROE transmission */
VAR(uint8, DCM_VAR) Dcm_GucResOnEventStatus;
#endif

P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_GpDIDSignalDataPtr;

#if (DCM_DSP_MAX_DID_SIZE != DCM_ZERO)
VAR(uint8, DCM_VAR) Dcm_GaaDidReadSignalData[DCM_DSP_MAX_DID_SIZE];
#endif

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
/* Store Memory Identifier for 0x23 service */
VAR(uint8, DCM_VAR) Dcm_GucRMBAMemoryIdentifier;
#endif

#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
VAR(uint8, DCM_VAR) Dcm_GucInOutParameter;

#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
VAR(uint8, DCM_VAR) Dcm_GaaUnderControl[DCM_MAX_CONTROL_MASK_SIZE];
#endif
#endif

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*******************************************************************************
** Variables of 16-bit size                                                   **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Store maximum number of response Pending */
VAR(uint16, DCM_VAR) Dcm_GusMaxNoOfRespPend;

VAR(uint16, DCM_VAR) Dcm_GusMaxNoOfForceRespPend;


#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
VAR(uint32, DCM_VAR) Dcm_GusRMBAMemorySize;
#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
VAR(uint32, DCM_VAR) Dcm_GusWriteMemorySize;
#endif

#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
     (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
#if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
VAR(uint16, DCM_VAR) Dcm_GucSubNodeId;
#endif
#endif


VAR(uint16, DCM_VAR) Dcm_GusDIDIndexVal;

VAR(uint16, DCM_VAR) Dcm_GusDataIdentifier;

#define DCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*******************************************************************************
** Variables of 32-bit size                                                   **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Store CRL Length value for security service */
VAR(uint32, DCM_VAR) Dcm_GaaCRLLength;

/* Store Channel Identifier associated to the received Pdu */
VAR(uint32, DCM_VAR) Dcm_GulChannelIdentifier;

/* Store DTC value for 0x14 service */
VAR(uint32, DCM_VAR) Dcm_GulDTCValue;

VAR(uint32, DCM_VAR) Dcm_GulFDCRespSize;

/* Global Variable to store DTC */
VAR(Tun_DcmDword32, DCM_VAR) Dcm_GunDTC;

#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Store buffer size in case of paged processing */
VAR(uint32, DCM_VAR) Dcm_GulBufferSize;
#endif


#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/* Store Memory Address for 0x23 service */
VAR(uint32, DCM_VAR) Dcm_GulRMBAMemoryAddress;
#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/* Store Memory Address for 0x3D service */
VAR(uint32, DCM_VAR) Dcm_GulWriteMemoryAddress;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/*******************************************************************************
** Variables of unspecified size that are initialized                         **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Store the type of start up mode */
VAR(Dcm_EcuStartModeType, DCM_VAR) Dcm_EcuStartMode;

/* Store relevant information prior jump to bootloader */
VAR(Dcm_ProgConditionsType, DCM_VAR) Dcm_GddProgConditions;


/* Store the current operation status */
VAR(Dcm_OpStatusType, DCM_VAR) Dcm_GddOpStatus;

/* Store the previous session level */
VAR(Dcm_SesCtrlType, DCM_VAR) Dcm_GddOldSession;

/* Store the current session level */
VAR(Dcm_SesCtrlType, DCM_VAR) Dcm_GddCurrentSession;

/* Store the pointer to the current timing values */
VAR(Dcm_TimerServerType, DCM_VAR) Dcm_GstCurrentTimingValue;


/* Store all information for request and response processing */
VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GstMsgContext;

/* Store the RxPduId */
VAR(PduIdType, DCM_VAR) Dcm_GddRxPduId;

/* Store the current protocol type */
VAR(Dcm_ProtocolType, DCM_VAR) Dcm_GddProtocolType;

/* Store length of the request which is in progress */
VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GaaReqLength[DCM_NUM_OF_PROTOCOLCONFIG];

/* Store the request data for tester present request */
VAR(uint8, DCM_VAR) Dcm_GaaTesterPresentReqBuff[DCM_BUFSZ_TESTERPRESENT];

VAR(Dcm_RequestContextType, DCM_VAR) Dcm_RequestContext[DCM_NUM_OF_PROTOCOLCONFIG];


VAR(PduIdType, DCM_VAR) Dcm_GddDcmTxPduId;

VAR(PduIdType, DCM_VAR) Dcm_GddDcmTxConfPduId;

/* Store the response length for the first page */
VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GddTxResponseLen;

/* Store negative response code */
VAR(Dcm_NegativeResponseCodeType, DCM_VAR) Dcm_GddNegRespError;

#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
VAR(PduIdType, DCM_VAR) Dcm_GddSecDeclTxPduId;

VAR(PduIdType, DCM_VAR) Dcm_GddSecDeclConfTxPduId;

VAR(uint8, DCM_VAR) Dcm_GucSidOfDeclinedRequest;

VAR(PduIdType, DCM_VAR) Dcm_GddRxPduId_DeclinedRequest;
#endif

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Store the response length pending in paged transmission */
VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GddCurrentLength;
#endif


/* Store the status of the transmission */
VAR(Dcm_TxRespStatusType, DCM_VAR) Dcm_TxRespStatus;

/* Store the status of paged buffer transmission */
VAR(Dcm_DspSerPgStatusType, DCM_VAR) Dcm_DspSerPgStatus;

/* Store the status of the protocol and provide buffer for transmission */
VAR(Dcm_PrtclTxBufStatusType, DCM_VAR) Dcm_PrtclTxBufStatus;

VAR(Dcm_ServicePendingStatusType, DCM_VAR) Dcm_ServicePendingStatus;

VAR(Dcm_ServiceForcePendingStatusType, DCM_VAR) Dcm_ServiceForcePendingStatus;

VAR(Dcm_MemServicePendingStatusType, DCM_VAR) Dcm_MemServicePendingStatus;

VAR(Dcm_DspServiceProcessingStsType, DCM_VAR) Dcm_DspServiceProcessingSts;


#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* Store the pointer to the MsgContext */
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) Dcm_GpRoeMsgContext;

/* Store the response length pending in paged transmission*/
VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GddRoeReqLength;

VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GstRoeMsgContext;

VAR(Dcm_RoeEventStoreType, DCM_VAR) Dcm_GaaRoeNonVolatileData;

VAR(Dcm_RoeRequestInfo, DCM_VAR) Dcm_GddRoeRequestInfo[DCM_NUM_OF_ROE_EVENT_CONFIG];
#endif


#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GstPerMsgContext;

VAR(Dcm_PeriodicStatusType, DCM_VAR) Dcm_GddPerStatus;

VAR(Dcm_PeriodicSchedulerInfoType, DCM_VAR) Dcm_GddPerSchInfo;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_8
#include "MemMap.h"
#if(DCM_AUTRON_FBL_USED == STD_OFF)
#if(DCM_CSAC_CONFIGURED == STD_ON)
/* number of the entries of each data type */
CONST(uint8, DCM_CONST) Dcm_SecSerPublicKey[DCM_SEC_PUBLIC_KEY_LENGTH] = {
  0xB3U, 0x48U, 0xDFU, 0xD7U, 0xA1U, 0x77U, 0xF5U, 0xF1U, 0x9DU, 0x83U, 0xB2U, 0x9BU, 0x5CU, 0x70U, 0xC0U, 0xD5U, 
  0xCCU, 0x0CU, 0xFEU, 0x64U, 0x59U, 0x26U, 0xD5U, 0x5EU, 0x03U, 0x1AU, 0x9BU, 0x97U, 0xB3U, 0x00U, 0xEEU, 0x21U, 
  0xD1U, 0x1EU, 0x4EU, 0x2CU, 0x73U, 0x0FU, 0x41U, 0xACU, 0x03U, 0x7DU, 0x85U, 0xD9U, 0x9EU, 0xF4U, 0x7AU, 0x62U, 
  0x41U, 0x6CU, 0x9BU, 0x81U, 0x30U, 0x18U, 0xA6U, 0xCFU, 0x72U, 0x67U, 0xE8U, 0x85U, 0x57U, 0xC4U, 0xAEU, 0xF8U, 
  0x2AU, 0xFBU, 0xBAU, 0x6DU, 0x45U, 0x18U, 0x1AU, 0x0FU, 0x33U, 0x3BU, 0x14U, 0xF6U, 0x8AU, 0x3FU, 0x87U, 0x17U, 
  0x6DU, 0xFEU, 0x4AU, 0x56U, 0xF1U, 0x8DU, 0x0BU, 0xE7U, 0xADU, 0xCDU, 0xEEU, 0x87U, 0xB3U, 0x29U, 0xBEU, 0x4FU, 
  0x4AU, 0xEDU, 0x58U, 0x4EU, 0x40U, 0x60U, 0x3EU, 0xE9U, 0xA8U, 0x9DU, 0x57U, 0xF6U, 0x12U, 0x69U, 0x1DU, 0x21U, 
  0xCAU, 0x34U, 0xA8U, 0xA4U, 0xC1U, 0xB3U, 0x8FU, 0xCEU, 0x66U, 0x2FU, 0xCFU, 0x8FU, 0x72U, 0x46U, 0xD8U, 0xFCU, 
  0xEBU, 0xD5U, 0x63U, 0xC2U, 0xBCU, 0x0EU, 0x42U, 0x8BU, 0x4CU, 0x7FU, 0x78U, 0xE7U, 0x4FU, 0xCBU, 0x24U, 0xDCU, 
  0x1DU, 0xE3U, 0x4CU, 0x52U, 0xCEU, 0x0DU, 0x85U, 0x2EU, 0x6AU, 0xDEU, 0x4AU, 0x9DU, 0x3DU, 0xD7U, 0xCAU, 0x10U, 
  0x0FU, 0xC9U, 0x98U, 0x5AU, 0x80U, 0x9BU, 0x5EU, 0x9FU, 0x7CU, 0x17U, 0x59U, 0x02U, 0x19U, 0xAFU, 0xD9U, 0xB8U, 
  0x16U, 0xA0U, 0x85U, 0x89U, 0x90U, 0x4AU, 0x51U, 0x39U, 0xFDU, 0x0DU, 0xFDU, 0xF1U, 0x36U, 0x99U, 0x8CU, 0x64U, 
  0x21U, 0xF3U, 0x61U, 0x07U, 0x7AU, 0x9FU, 0xD9U, 0x33U, 0x9CU, 0x6AU, 0x4AU, 0x46U, 0xE3U, 0xCDU, 0xAEU, 0x00U, 
  0x4EU, 0x51U, 0xEAU, 0xE7U, 0x00U, 0x14U, 0xC0U, 0xEBU, 0xC0U, 0x10U, 0xBAU, 0xACU, 0xE8U, 0x6FU, 0xFFU, 0x29U, 
  0xD4U, 0x9FU, 0x61U, 0x43U, 0x2FU, 0x1EU, 0x07U, 0xFAU, 0x1FU, 0x5AU, 0x05U, 0xC7U, 0xF0U, 0x36U, 0x3EU, 0x94U, 
  0xB5U, 0xA6U, 0x1BU, 0x3FU, 0xBAU, 0x5DU, 0xAEU, 0xC7U, 0x33U, 0xB2U, 0x87U, 0x5CU, 0xE9U, 0xE5U, 0xF6U, 0xE1U
};
#endif
#endif
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
