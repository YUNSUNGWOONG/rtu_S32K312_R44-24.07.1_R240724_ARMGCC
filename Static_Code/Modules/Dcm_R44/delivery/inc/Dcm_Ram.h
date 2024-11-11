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
**  SRC-MODULE: Dcm_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Ram                                          **
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
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-2768, #CP44-2676        **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-2730                    **
** 1.1.2     13-Nov-2023   DH Kwak        Refer #CP44-3122                    **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
** 1.4.1     01-Apr-2024   DanhTQ1        Refer #CP44-3362                    **
*******************************************************************************/
#ifndef DCM_RAM_H
#define DCM_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_PCTypes.h"
#include "Dcm_Timer.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
** Variables of boolean                                                       **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

extern VAR(boolean, DCM_VAR) Dcm_GblReset;

extern VAR(boolean, DCM_VAR) Dcm_GblSendResOnReset;

extern VAR(boolean, DCM_VAR) Dcm_GblJumpToBootloader;

extern VAR(boolean, DCM_VAR) Dcm_IsBlockSeqCounterRollOver;

/* Store initialization status of Dcm */
extern VAR(boolean, DCM_VAR_POWER_ON_INIT) Dcm_GblInitStatus;

/* Store the status of the normal transmission */
extern VAR(boolean, DCM_VAR) Dcm_GblNormalReq;

/* sg.baek 022305 - Task #2163 in redmine */
extern VAR(boolean, DCM_VAR) Dcm_GblProcessNewRequest;

#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
/* Store the status of the second request*/
extern VAR(boolean, DCM_VAR) Dcm_GblSecDeclRequest;
#endif

#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
extern VAR(boolean, DCM_VAR) Dcm_GblProcessPendingRequest;

extern VAR(boolean, DCM_VAR) Dcm_GblAddPendingRequestToQueue;
#endif

extern VAR(boolean, DCM_VAR) Dcm_GblSendResponse;

extern VAR(boolean, DCM_VAR) Dcm_GblRespPendConfirmation;

extern VAR(boolean, DCM_VAR) Dcm_GblPduRTransmitResponse;

extern VAR(boolean, DCM_VAR) Dcm_TriggerCancelPendingOperation;

/* Store the status of current did */
extern VAR(boolean, DCM_VAR) Dcm_GblDIDRangePresent;

extern VAR(boolean, DCM_VAR) Dcm_GblDTCFDCPending;

extern VAR(boolean, DCM_VAR) Dcm_GblFaultDetectionCounter;

/* Store the number of Filter Dtc By Severity mask */
extern VAR(boolean, DCM_VAR) Dcm_GblNumFilterDTCStatusBySevirtMask;

#if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
extern VAR(boolean, DCM_VAR) Dcm_GblDTCSettingDisabled;
#endif

#if ((DCM_READ_ITC_SERVICE_SUPPRT == STD_ON) ||\
     (DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON))
extern VAR(boolean, DCM_VAR) Dcm_InternalTroubleCodeService;
#endif

#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* Store the requested serviceToRespondTo */
extern VAR(boolean, DCM_VAR) Dcm_GblRoeClearAll;
#endif

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
extern VAR(boolean, DCM_VAR) Dcm_GblAvailabilityPIDFlag;
#endif

#if ((DCM_ECURESET_SERVICE == STD_ON) || \
     (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON))
extern VAR(boolean, DCM_VAR) Dcm_GblExecuteECUReset;
#endif
#if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        (DCM_RESPONSE_ONEVENT_BLOCKID > 0))
extern VAR(boolean, DCM_VAR) Dcm_GblNvMReadBlock;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
** Variables of 8-bit size                                                    **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Store the status of first time calling main function */
extern VAR(uint8, DCM_VAR) Dcm_GblFirstCallToMain;

/* Store the Subfunction respective to the request*/
extern VAR(uint8, DCM_VAR) Dcm_GucSubFunction;

/* Store current protocol priority */
extern VAR(uint8, DCM_VAR) Dcm_GucPrtclPriority;

/* Store the communication mode */
extern VAR(uint8, DCM_VAR) Dcm_GaaCommMode[DCM_NO_OF_COMM_CHANNELS];

/* Store pointer to the request or response data */
extern P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_GpReqResData;

/* To store PID Count */
extern VAR(uint8, DCM_VAR) Dcm_GucPIDCount;

/* To indicate ID belongs to Availability list */
extern VAR(uint8, DCM_VAR) Dcm_GucAvlState;

extern VAR(uint8, DCM_VAR) Dcm_GaaPidSignalData[DCM_THIRTY_TWO];


extern VAR(uint8, DCM_VAR) Dcm_GucReadGlobal;

extern VAR(uint8, DCM_VAR) Dcm_GucTranslationType;

extern VAR(uint8, DCM_VAR) Dcm_GucMemorySelection;

extern VAR(uint8, DCM_VAR) Dcm_GucAvailableDTCStatusMask;

extern VAR(uint8, DCM_VAR) Dcm_GucFunctionalGroupIdentifier;

#if (DCM_J1979_2_SUPPORT == STD_ON)
/* Trace: DCM_19792_56_11 */
extern VAR(uint8, DCM_VAR) Dcm_GucReadinessGroupIdentifier;
/* Trace: DCM_19792_1A_07 */
extern VAR(uint8, DCM_VAR) Dcm_GucExtendedDataRecordNumber;
#endif /* J19792 */

#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Store record number */
extern VAR(uint8, DCM_VAR) Dcm_GucNumofDTC;

extern VAR(uint8, DCM_VAR) Dcm_GucRecordNumber;
#endif


#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
extern VAR(uint8, DCM_VAR) Dcm_GucSecurSequChk;

extern VAR(uint8, DCM_VAR) Dcm_GaaSeed[DCM_MAX_SECURITY_SEED_SIZE];
#endif


#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
     (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
/* Store SubNetValue for service 0x28 */
extern VAR(uint8, DCM_VAR) Dcm_GucSubNetValue;

/* Store CommunicationModeType for service 0x28 */
extern VAR(uint8, DCM_VAR) Dcm_GucCommunicationModeType;

/* Store CommunicationModeType for service 0x28 */
extern VAR(Dcm_CommunicationModeType, DCM_VAR) Dcm_GucComCtrlMode;
#endif


#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
extern VAR(uint8, DCM_VAR) Dcm_GucMemAddrSizeBytes;

extern VAR(uint8, DCM_VAR) Dcm_GucMemoryIdentifier;

extern P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_GpWriteData;
#endif


#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* Store the status of the ROE transmission */
extern VAR(uint8, DCM_VAR) Dcm_GucResOnEventStatus;
#endif

extern P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_GpDIDSignalDataPtr;

#if (DCM_DSP_MAX_DID_SIZE != DCM_ZERO)
extern VAR(uint8, DCM_VAR) Dcm_GaaDidReadSignalData[DCM_DSP_MAX_DID_SIZE];
#endif

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
/* Store Memory Identifier for 0x23 service */
extern VAR(uint8, DCM_VAR) Dcm_GucRMBAMemoryIdentifier;
#endif

#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
extern VAR(uint8, DCM_VAR) Dcm_GucInOutParameter;

#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
extern VAR(uint8, DCM_VAR) Dcm_GaaUnderControl[DCM_MAX_CONTROL_MASK_SIZE];
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
extern VAR(uint16, DCM_VAR) Dcm_GusMaxNoOfRespPend;

extern VAR(uint16, DCM_VAR) Dcm_GusMaxNoOfForceRespPend;


#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
extern VAR(uint32, DCM_VAR) Dcm_GusRMBAMemorySize;
#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
extern VAR(uint32, DCM_VAR) Dcm_GusWriteMemorySize;
#endif

#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
     (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
#if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
extern VAR(uint16, DCM_VAR) Dcm_GucSubNodeId;
#endif
#endif


extern VAR(uint16, DCM_VAR) Dcm_GusDIDIndexVal;

extern VAR(uint16, DCM_VAR) Dcm_GusDataIdentifier;

#define DCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*******************************************************************************
** Variables of 32-bit size                                                   **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

extern VAR(uint32, DCM_VAR) Dcm_GaaCRLLength;

/* Array for Present Date WriteMemory Data values */
extern VAR(uint8, DCM_VAR) Dcm_GaaPresentDate[DCM_THREE];

/* Store Channel Identifier associated to the received Pdu */
extern VAR(uint32, DCM_VAR) Dcm_GulChannelIdentifier;


/* Store DTC value for 0x14 service */
extern VAR(uint32, DCM_VAR) Dcm_GulDTCValue;

extern VAR(uint32, DCM_VAR) Dcm_GulFDCRespSize;

/* Global Variable to store DTC */
extern VAR(Tun_DcmDword32, DCM_VAR) Dcm_GunDTC;

#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Store buffer size in case of paged processing */
extern VAR(uint32, DCM_VAR) Dcm_GulBufferSize;
#endif


#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/* Store Memory Address for 0x23 service */
extern VAR(uint32, DCM_VAR) Dcm_GulRMBAMemoryAddress;
#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/* Store Memory Address for 0x3D service */
extern VAR(uint32, DCM_VAR) Dcm_GulWriteMemoryAddress;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/*******************************************************************************
** Variables of unspecified size that are initialized                         **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Store the type of start up mode */
extern VAR(Dcm_EcuStartModeType, DCM_VAR) Dcm_EcuStartMode;

/* Store relevant information prior jump to bootloader */
extern VAR(Dcm_ProgConditionsType, DCM_VAR) Dcm_GddProgConditions;


/* Store the current operation status */
extern VAR(Dcm_OpStatusType, DCM_VAR) Dcm_GddOpStatus;

/* Store the previous session level */
extern VAR(Dcm_SesCtrlType, DCM_VAR) Dcm_GddOldSession;

/* Store the current session level */
extern VAR(Dcm_SesCtrlType, DCM_VAR) Dcm_GddCurrentSession;

/* Store the pointer to the current timing values */
extern VAR(Dcm_TimerServerType, DCM_VAR) Dcm_GstCurrentTimingValue;


/* Store all information for request and response processing */
extern VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GstMsgContext;

/* Store the RxPduId */
extern VAR(PduIdType, DCM_VAR) Dcm_GddRxPduId;

/* Store the current protocol type */
extern VAR(Dcm_ProtocolType, DCM_VAR) Dcm_GddProtocolType;

/* Store length of the request which is in progress */
extern VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GaaReqLength[DCM_NUM_OF_PROTOCOLCONFIG];

/* Store the request data for tester present request */
extern VAR(uint8, DCM_VAR) Dcm_GaaTesterPresentReqBuff[DCM_BUFSZ_TESTERPRESENT];

extern VAR(Dcm_RequestContextType, DCM_VAR) Dcm_RequestContext[DCM_NUM_OF_PROTOCOLCONFIG];


extern VAR(PduIdType, DCM_VAR) Dcm_GddDcmTxPduId;

extern VAR(PduIdType, DCM_VAR) Dcm_GddDcmTxConfPduId;

/* Store the response length for the first page */
extern VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GddTxResponseLen;

/* Store negative response code */
extern VAR(Dcm_NegativeResponseCodeType, DCM_VAR) Dcm_GddNegRespError;

#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
extern VAR(PduIdType, DCM_VAR) Dcm_GddSecDeclTxPduId;

extern VAR(PduIdType, DCM_VAR) Dcm_GddSecDeclConfTxPduId;

extern VAR(uint8, DCM_VAR) Dcm_GucSidOfDeclinedRequest;

extern VAR(PduIdType, DCM_VAR) Dcm_GddRxPduId_DeclinedRequest;
#endif

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Store the response length pending in paged transmission */
extern VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GddCurrentLength;
#endif


/* Store the status of the transmission */
extern VAR(Dcm_TxRespStatusType, DCM_VAR) Dcm_TxRespStatus;

/* Store the status of paged buffer transmission */
extern VAR(Dcm_DspSerPgStatusType, DCM_VAR) Dcm_DspSerPgStatus;

/* Store the status of the protocol and provide buffer for transmission */
extern VAR(Dcm_PrtclTxBufStatusType, DCM_VAR) Dcm_PrtclTxBufStatus;

extern VAR(Dcm_ServicePendingStatusType, DCM_VAR) Dcm_ServicePendingStatus;

extern VAR(Dcm_ServiceForcePendingStatusType, DCM_VAR) Dcm_ServiceForcePendingStatus;

extern VAR(Dcm_MemServicePendingStatusType, DCM_VAR) Dcm_MemServicePendingStatus;

extern VAR(Dcm_DspServiceProcessingStsType, DCM_VAR) Dcm_DspServiceProcessingSts;


#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* Store the pointer to the MsgContext */
extern P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) Dcm_GpRoeMsgContext;

/* Store the response length pending in paged transmission*/
extern VAR(Dcm_MsgLenType, DCM_VAR) Dcm_GddRoeReqLength;

extern VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GstRoeMsgContext;

extern VAR(Dcm_RoeEventStoreType, DCM_VAR) Dcm_GaaRoeNonVolatileData;

extern VAR(Dcm_RoeRequestInfo, DCM_VAR) Dcm_GddRoeRequestInfo[DCM_NUM_OF_ROE_EVENT_CONFIG];
#endif


#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern VAR(Dcm_MsgContextType, DCM_VAR) Dcm_GstPerMsgContext;

extern VAR(Dcm_PeriodicStatusType, DCM_VAR) Dcm_GddPerStatus;

extern VAR(Dcm_PeriodicSchedulerInfoType, DCM_VAR) Dcm_GddPerSchInfo;
#endif


#if(DCM_AUTRON_FBL_USED == STD_OFF)
#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_SERVICE == STD_ON)
extern CONST(uint8, DCM_CONST) Dcm_SecSerPublicKey[DCM_SEC_PUBLIC_KEY_LENGTH];
#endif
#endif

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* DCM_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
