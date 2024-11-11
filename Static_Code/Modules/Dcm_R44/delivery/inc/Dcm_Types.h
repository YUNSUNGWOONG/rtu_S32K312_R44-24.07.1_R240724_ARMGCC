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
**  SRC-MODULE: Dcm_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provision of Dcm type definitions                             **
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
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     17-Jun-2020   HueKM          Changes made as per #12214          **
** 0.0.3     16-Aug-2020   HueKM          Correct UDS 0x2A macros             **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.6     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE and #CP44-1200            **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1558                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-2768, #CP44-2676        **
** 1.1.2     13-Nov-2023   DH Kwak        Refer #CP44-3122 #CP44-3194         **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.3.0_HF1 13-Jan-2024   SY Kim         Refer #45119                        **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
*******************************************************************************/
#ifndef DCM_TYPES_H
#define DCM_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"
#include "Rte_Dcm_Type.h"
#include "Dcm_Cfg.h"

#if (DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
** Std_ReturnType                                                             **
*******************************************************************************/
#ifndef DCM_E_PENDING
#define DCM_E_PENDING                                                    (0x0Au)
#endif

#ifndef DCM_E_FORCE_RCRRP
#define DCM_E_FORCE_RCRRP                                                (0x0Cu)
#endif

#ifndef DCM_E_COMPARE_KEY_FAILED
#define DCM_E_COMPARE_KEY_FAILED                                         (0x0Bu)
#endif

/* Hyundai AutoEver Specific */
#ifndef DCM_E_NO_DID
#define DCM_E_NO_DID                                                     (0x46u)
#endif

/* Task #12214 in Redmine */
#ifndef E_PROTOCOL_NOT_ALLOWED
#define E_PROTOCOL_NOT_ALLOWED                                           (0x05u)
#endif

/* Task #5246, #5367, #6609: if macro is not defined in Std_Types.h */
#ifndef E_REQUEST_NOT_ACCEPTED
#define E_REQUEST_NOT_ACCEPTED                                           (0x08u)
#endif

/*******************************************************************************
** Standard Support Parameter                                                 **
*******************************************************************************/
#ifndef DCM_ISO14229_SUPPORT
#define DCM_ISO14229_SUPPORT                                             (0x00u)
#endif

#ifndef DCM_ES95486_SUPPORT
#define DCM_ES95486_SUPPORT                                              (0x01u)
#endif

#ifndef DCM_ES96590_SUPPORT
#define DCM_ES96590_SUPPORT                                              (0x02u)
#endif

#ifndef DCM_ES95486_02_SUPPORT
#define DCM_ES95486_02_SUPPORT                                           (0x03u)
#endif

#ifndef DCM_ES95486_50_SUPPORT
#define DCM_ES95486_50_SUPPORT                                           (0x04u)
#endif

#ifndef DCM_QZN04_SUPPORT
#define DCM_QZN04_SUPPORT                                                (0x05u)
#endif

/*******************************************************************************
** SWCGEN and RCRRP Macros                                                   **
*******************************************************************************/
#ifdef DCM_ENABLE_RX_TX_NORM
#define DCM_SWCGEN
#endif

#ifndef DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING
#define DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING                    (0x78u)
#endif

/*******************************************************************************
** OBD Type                                                                   **
*******************************************************************************/
/* Trace: DCM_19792_GEN_01 */
#ifndef DCM_PROTOCOLID_OBD_NONE
#define DCM_PROTOCOLID_OBD_NONE                                          (0x00u)
#endif

/*  DCM_J1979_2_OBD_ON_UDS  */
#ifndef DCM_PROTOCOLID_J1979_2_OBD_ON_UDS
#define DCM_PROTOCOLID_J1979_2_OBD_ON_UDS                                (0x01u)
#endif

#ifndef DCM_PROTOCOLID_J1979_OBD2
#define DCM_PROTOCOLID_J1979_OBD2                                        (0x02u)
#endif

/*******************************************************************************
** Dcm_StatusType                                                             **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00976 */
typedef uint8 Dcm_StatusType;

/* This value is representing a successful operation */
#define DCM_E_OK                                          ((Dcm_StatusType)0x00)

/* ResponseOnOneEvent request is not accepted by DCM */
#define DCM_E_ROE_NOT_ACCEPTED                            ((Dcm_StatusType)0x06)

/* Periodic transmission request is not accepted by DCM */
#define DCM_E_PERIODICID_NOT_ACCEPTED                     ((Dcm_StatusType)0x07)
#endif

/*******************************************************************************
** Dcm_CommunicationModeType                                                  **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00981 */
typedef uint8 Dcm_CommunicationModeType;

/* Enable the Rx and Tx for normal communication */
#define DCM_ENABLE_RX_TX_NORM                 ((Dcm_CommunicationModeType) 0x00)

/* Enable the Rx and disable the Tx for normal communication */
#define DCM_ENABLE_RX_DISABLE_TX_NORM         ((Dcm_CommunicationModeType) 0x01)

/* Disable the Rx and enable the Tx for normal communication */
#define DCM_DISABLE_RX_ENABLE_TX_NORM         ((Dcm_CommunicationModeType) 0x02)

/* Disable Rx and Tx for normal communication */
#define DCM_DISABLE_RX_TX_NORMAL              ((Dcm_CommunicationModeType) 0x03)

#define DCM_DISABLE_RX_TX_NORM                ((Dcm_CommunicationModeType) 0x03)

/* Enable the Rx and Tx for network management communication */
#define DCM_ENABLE_RX_TX_NM                   ((Dcm_CommunicationModeType) 0x04)

/* Enable Rx and disable the Tx for network management communication */
#define DCM_ENABLE_RX_DISABLE_TX_NM           ((Dcm_CommunicationModeType) 0x05)

/* Disable the Rx and enable the Tx for network management communication */
#define DCM_DISABLE_RX_ENABLE_TX_NM           ((Dcm_CommunicationModeType) 0x06)

/* Disable Rx and Tx for network management communication */
#define DCM_DISABLE_RX_TX_NM                  ((Dcm_CommunicationModeType) 0x07)

/* Enable Rx and Tx for normal and network management communication */
#define DCM_ENABLE_RX_TX_NORM_NM              ((Dcm_CommunicationModeType) 0x08)

/* Enable the Rx and disable the Tx for normal and network management communication */
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM      ((Dcm_CommunicationModeType) 0x09)

/* Disable the Rx and enable the Tx for normal and network management communication */
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM      ((Dcm_CommunicationModeType) 0x0A)

/* Disable Rx and Tx for normal and network management communication */
#define DCM_DISABLE_RX_TX_NORM_NM             ((Dcm_CommunicationModeType) 0x0B)
#endif

/* Undefined communication mode type */
#define DCM_COMMUNICATIONMODETYPE_UNDEFINED                              (0xFFu)

/*******************************************************************************
** Dcm_ConfigType                                                             **
*******************************************************************************/
/* @Trace: SWS_Dcm_00982 */
typedef struct STagDcm_ConfigType
{
  uint8 ucDummy;

} Dcm_ConfigType;

/*******************************************************************************
** Dcm_ReturnReadMemoryType                                                   **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00985 */
typedef uint8 Dcm_ReturnReadMemoryType;

/* Reading has been done */
#define DCM_READ_OK                            ((Dcm_ReturnReadMemoryType) 0x00)

/* Reading is pending, another call is request to finalize the reading */
#define DCM_READ_PENDING                       ((Dcm_ReturnReadMemoryType) 0x01)

/* Reading has failed */
#define DCM_READ_FAILED                        ((Dcm_ReturnReadMemoryType) 0x02)

/*Reading is pending, the Response pending transmission starts immediately*/
#define DCM_READ_FORCE_RCRRP                   ((Dcm_ReturnReadMemoryType) 0x03)
#endif

/*******************************************************************************
**                Dcm_ReturnWriteMemoryType                                   **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00986 */
typedef uint8 Dcm_ReturnWriteMemoryType;

/* Writing has been done */
#define DCM_WRITE_OK                          ((Dcm_ReturnWriteMemoryType) 0x00)

/* Writing is pending, another called is requested */
#define DCM_WRITE_PENDING                     ((Dcm_ReturnWriteMemoryType) 0x01)

/* The writing has failed */
#define DCM_WRITE_FAILED                      ((Dcm_ReturnWriteMemoryType) 0x02)

/* Writing is pending, the Response pending transmission starts immediately */
#define DCM_WRITE_FORCE_RCRRP                 ((Dcm_ReturnWriteMemoryType) 0x03)
#endif

/*******************************************************************************
** Dcm_EcuStartModeType                                                       **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00987 */
typedef uint8 Dcm_EcuStartModeType;

/* The ECU starts normally */
#define DCM_COLD_START                             ((Dcm_EcuStartModeType) 0x00)

/* The ECU starts from a bootloader jump */
#define DCM_WARM_START                             ((Dcm_EcuStartModeType) 0x01)
#endif

/*******************************************************************************
**                Dcm_ProgConditionsType                                      **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00988 */
typedef struct STagDcm_ProgConditionsType
{
  /* Unique id of the connection on which the request has been received */
  uint16 ConnectionId;

  /* Source address of the received request if meta data is enabled */
  uint16 TesterAddress;

  /* Service identifier of the received request */
  uint8 Sid;

  /* Identifier of the received subfunction */
  uint8 SubFncId;

  /* Set to true in order to request reprogramming of the ECU */
  boolean ReprogramingRequest;

  /* Indicate whether the application has been updated or not */
  boolean ApplUpdated;

  /* Set to true in case the flashloader or application shall send a response */
  boolean ResponseRequired;

  /* Indication current security level */
  uint8 SecurityLevel;

} Dcm_ProgConditionsType;
#endif

/*******************************************************************************
** Related Message Type                                                       **
*******************************************************************************/
#ifndef DCM_SWCGEN
/* @Trace: SWS_Dcm_00989 */
/* Base type for diagnostic message item */
typedef uint8 Dcm_MsgItemType;

/* @Trace: SWS_Dcm_00991 */
/* Length of diagnostic message (request, positive or negative response) */
typedef uint32 Dcm_MsgLenType;

/* @Trace: SWS_Dcm_00993 */
/* Determine the relation between request and response confirmation */
typedef uint8 Dcm_IdContextType;
#endif

/* @Trace: SWS_Dcm_00990 */
/* Base type for diagnostic message (request, positive or negative response) */
typedef Dcm_MsgItemType* Dcm_MsgType;

/* @Trace: SWS_Dcm_00992 */
/* Additional information on message request */
typedef struct STagDcm_MsgAddInfoType
{
  /* To know if the request type is physical or functional */
  uint8 reqType;

  /* To know if the positive response is to be suppressed */
  uint8 suppressPosResponse;

} Dcm_MsgAddInfoType;

/* @Trace: SWS_Dcm_00994 */
/* All information which is necessary to process a diagnostic message */
typedef struct STagDcm_MsgContextType
{
  /* Request data, starting directly after service identifier */
  Dcm_MsgType reqData;

  /* Request data length (excluding service identifier) */
  Dcm_MsgLenType reqDataLen;

  /* Positive response data, starting directly after service identifier */
  Dcm_MsgType resData;

  /* Positive response data length (excluding service identifier) */
  Dcm_MsgLenType resDataLen;

  /* Additional information about service request and response */
  Dcm_MsgAddInfoType msgAddInfo;

  /* The maximal length of a response */
  Dcm_MsgLenType resMaxDataLen;

  /* Determine the relation between request and response confirmation */
  Dcm_IdContextType idContext;

  /* Pdu Identifier on which the request was received */
  PduIdType dcmRxPduId;

} Dcm_MsgContextType;

/*******************************************************************************
** Dcm_ExtendedOpStatusType                                                   **
*******************************************************************************/
/* @Trace: SWS_Dcm_91015 */
typedef uint8 Dcm_ExtendedOpStatusType;

/* Indicates that a positive response has been sent successfully */
#define DCM_POS_RESPONSE_SENT                  ((Dcm_ExtendedOpStatusType) 0x04)

/* Indicates that a positive response has not been sent successfully */
#define DCM_POS_RESPONSE_FAILED                ((Dcm_ExtendedOpStatusType) 0x05)

/* Indicates that a negative response has been sent successfully */
#define DCM_NEG_RESPONSE_SENT                  ((Dcm_ExtendedOpStatusType) 0x06)

/* Indicates that a negative response has not been sent successfully */
#define DCM_NEG_RESPONSE_FAILED                ((Dcm_ExtendedOpStatusType) 0x07)

/*******************************************************************************
** Dcm_EcuResetType                                                           **
*******************************************************************************/
typedef uint8 Dcm_EcuResetType;

#define DCM_NONE                                       ((Dcm_EcuResetType) 0x00)
#define DCM_HARD                                       ((Dcm_EcuResetType) 0x01)
#define DCM_KEYONOFF                                   ((Dcm_EcuResetType) 0x02)
#define DCM_SOFT                                       ((Dcm_EcuResetType) 0x03)
#define DCM_JUMPTOBOOTLOADER                           ((Dcm_EcuResetType) 0x04)
#define DCM_JUMPTOSYSSUPPLIERBOOTLOADER                ((Dcm_EcuResetType) 0x05)
#define DCM_EXECUTE                                    ((Dcm_EcuResetType) 0x06)

/*******************************************************************************
** Dcm_ModeRapidPowerShutDownType                                             **
*******************************************************************************/
typedef uint8 Dcm_ModeRapidPowerShutDownType;

#define DCM_ENABLE_RAPIDPOWERSHUTDOWN    ((Dcm_ModeRapidPowerShutDownType) 0x00)
#define DCM_DISABLE_RAPIDPOWERSHUTDOWN   ((Dcm_ModeRapidPowerShutDownType) 0x01)

/*******************************************************************************
** Dcm_ControlDTCSettingType                                                  **
*******************************************************************************/
typedef uint8 Dcm_ControlDTCSettingType;

#define DCM_ENABLEDTCSETTING                  ((Dcm_ControlDTCSettingType) 0x00)
#define DCM_DISABLEDTCSETTING                 ((Dcm_ControlDTCSettingType) 0x01)

/*******************************************************************************
** Common data types abstraction                                              **
*******************************************************************************/
typedef P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) Dcm_BooleanPtrType;

typedef P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_Uint8PtrType;

typedef P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) Dcm_Uint8ConstPtrType;

typedef P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) Dcm_Uint16PtrType;

typedef P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST) Dcm_Uint16ConstPtrType;

typedef P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) Dcm_Uint32PtrType;

typedef P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) Dcm_ProtocolTypePtrType;

typedef P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) Dcm_NrcPtrType;

typedef P2CONST(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_CONST) Dcm_NrcConstPtrType;

typedef P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) Dcm_MsgContextPtrType;

typedef P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_CONST) Dcm_MsgContextConstPtrType;

typedef P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST) Dcm_ConfigConstPtrType;

typedef P2FUNC(void, DCM_APPL_CODE, Dcm_InitFunType)(Dcm_ConfigConstPtrType pConfig);

/*******************************************************************************
** Dcm_DidType                                                                **
*******************************************************************************/
typedef enum 
{
  DCM_DID_TYPE_DYN
  , DCM_DID_TYPE_OBD
  , DCM_DID_TYPE_NONOBD
  , DCM_DID_TYPE_RANGE
  , DCM_DID_TYPE_SESSION
  , DCM_DID_TYPE_OBD_PROTOCOLID
  , DCM_DID_TYPE_NUM
  , DCM_DID_TYPE_UNDEFINED
} Dcm_DidType;

/*******************************************************************************
** Dcm_ProtocolTransType                                                      **
*******************************************************************************/
typedef enum
{
  TYPE1
  , TYPE2
} Dcm_ProtocolTransType;

/*******************************************************************************
** Dcm_ProtocolRxAddrType                                                     **
*******************************************************************************/
typedef enum
{
  DCM_PHYSICAL_TYPE
  , DCM_FUNCTIONAL_TYPE
} Dcm_ProtocolRxAddrType;

/*******************************************************************************
** Dcm_DidUsePortType                                                         **
*******************************************************************************/
typedef enum
{
  USE_ATOMIC_NV_DATA_INTERFACE
  , USE_ATOMIC_SENDER_RECEIVER_INTERFACE
  , USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE
  , USE_DATA_ELEMENT_SPECIFIC_INTERFACES
} Dcm_DidUsePortType;

/*******************************************************************************
** Dcm_DataUsePortType                                                        **
*******************************************************************************/
typedef enum
{
  USE_BLOCK_ID
  , USE_DATA_ASYNCH_CLIENT_SERVER
  , USE_DATA_ASYNCH_CLIENT_SERVER_ERROR
  , USE_DATA_ASYNCH_FNC
  , USE_DATA_ASYNCH_FNC_ERROR
  , USE_DATA_SENDER_RECEIVER
  , USE_DATA_SENDER_RECEIVER_AS_SERVICE
  , USE_DATA_SYNCH_CLIENT_SERVER
  , USE_DATA_SYNCH_FNC
  , USE_ECU_SIGNAL
} Dcm_DataUsePortType;

/*******************************************************************************
** Dcm_EndianType                                                             **
*******************************************************************************/
typedef enum
{
  DCM_BIG_ENDIAN, 
  DCM_LITTLE_ENDIAN, 
  DCM_OPAQUE
} Dcm_EndianType;

/*******************************************************************************
** Dcm_DataType                                                               **
*******************************************************************************/
typedef enum
{
  DCM_DATA_TYPE_BOOLEAN
  , DCM_DATA_TYPE_SINT16
  , DCM_DATA_TYPE_SINT16_N
  , DCM_DATA_TYPE_SINT32
  , DCM_DATA_TYPE_SINT32_N
  , DCM_DATA_TYPE_SINT8
  , DCM_DATA_TYPE_SINT8_N
  , DCM_DATA_TYPE_UINT16
  , DCM_DATA_TYPE_UINT16_N
  , DCM_DATA_TYPE_UINT32
  , DCM_DATA_TYPE_UINT32_N
  , DCM_DATA_TYPE_UINT8
  , DCM_DATA_TYPE_UINT8_DYN
  , DCM_DATA_TYPE_UINT8_N
  , DCM_DATA_TYPE_VARIABLE_LENGTH
} Dcm_DataType;

/*******************************************************************************
** Dcm_SecurityUsePortType                                                    **
*******************************************************************************/
typedef enum
{
  USE_ASYNCH_CLIENT_SERVER,
  USE_ASYNCH_FNC
} Dcm_SecurityUsePortType;

/*******************************************************************************
** Dcm_DidControlMaskType                                                     **
*******************************************************************************/
typedef enum
{
  DCM_CONTROLMASK_EXTERNAL
  , DCM_CONTROLMASK_INTERNAL
  , DCM_CONTROLMASK_NO
} Dcm_DidControlMaskType;

/*******************************************************************************
** Dcm_EcuResetResponseType                                                   **
*******************************************************************************/
typedef enum
{
  AFTER_RESET
  , BEFORE_RESET
} Dcm_EcuResetResponseType;

/*******************************************************************************
** Dcm_PidServiceType                                                         **
*******************************************************************************/
typedef enum
{
  DCM_SERVICE_01
  , DCM_SERVICE_01_02
  , DCM_SERVICE_02
} Dcm_PidServiceType;

/*******************************************************************************
** Dcm_RoeStatusType                                                          **
*******************************************************************************/
typedef enum
{
  DCM_ROE_CLEARED
  , DCM_ROE_STOPPED
  , DCM_ROE_STARTED
} Dcm_RoeStatusType;

/*******************************************************************************
** Dcm_RoeEventWindowTimeType                                                 **
*******************************************************************************/
typedef enum
{
  DCM_ROE_EVENT_WINDOW_INFINITE = 0x02
  , DCM_ROE_EVENT_WINDOW_CURRENT_CYCLE
  , DCM_ROE_EVENT_WINDOW_CURRENT_AND_FOLLOWING_CYCLE
} Dcm_RoeEventWindowTimeType;

/*******************************************************************************
** Dcm_SesForBootType                                                         **
*******************************************************************************/
typedef enum
{
  DCM_NO_BOOT
  , DCM_OEM_BOOT
  , DCM_OEM_BOOT_RESPAPP
  , DCM_SYS_BOOT
  , DCM_SYS_BOOT_RESPAPP
} Dcm_SesForBootType;

/*******************************************************************************
** Dcm_CompareModeType                                                        **
*******************************************************************************/
typedef enum
{
  DCM_COMPARE_BSW_OR_SWC_MODE
  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  , DCM_COMPARE_CERT_ELE
  #endif
  , DCM_COMPARE_SWC_SR_DATA_ELE
} Dcm_CompareModeType;

#if (DCM_CRYPTO_R44_USED == STD_ON)
typedef uint8 Csm_AlignType;
typedef uint8 Csm_VerifyResultType;
typedef struct {
	uint32 length;
	Csm_AlignType data[294];
} Csm_AsymPublicKeyType;

#if (DCM_CNR_USED_SHA1 == STD_ON)
typedef uint8 Dcm_AlignType;
typedef uint8 Dcm_VerifyResultType;
typedef struct {
	uint32 length;
	Dcm_AlignType data[294];
} Dcm_AsymPublicKeyType;
#endif
#endif
/*******************************************************************************
** Dcm_ConditionType                                                          **
*******************************************************************************/
typedef enum
{
  DCM_EQUALS
  , DCM_EQUALS_NOT
  , DCM_GREATER_OR_EQUAL
  , DCM_GREATER_THAN
  , DCM_LESS_OR_EQUAL
  , DCM_LESS_THAN
} Dcm_ConditionType;

/*******************************************************************************
** Dcm_LogicalOperatorType                                                    **
*******************************************************************************/
typedef enum
{
  DCM_AND
  , DCM_OR
} Dcm_LogicalOperatorType;

/*******************************************************************************
** Dcm_PduRefType                                                             **
*******************************************************************************/
typedef enum 
{
  PDUREF_NO_METADATA
  , PDUREF_METADATA_SA_TA
  , PDUREF_METADATA_SA
  , PDUREF_METADATA_TA
} Dcm_PduRefType;

/*******************************************************************************
** Other Types                                                                **
*******************************************************************************/
typedef enum
{
  INIT_FUN_ACTIVE_DIAGNOSTIC
  , INIT_FUN_TIMERS
  , INIT_FUN_MANAGE_SECURITY
  , INIT_FUN_SESSION_CONTROL
  , INIT_FUN_RESPONSE_HANDLING
  , INIT_FUN_GENERIC_CONNECTION
  , INIT_FUN_AUTHENTICATION
  , INIT_FUN_MAX_NUM
} Dcm_InitFunIndexType;

/*******************************************************************************
** Numerical macros                                                           **
*******************************************************************************/
#define DCM_ZERO                                                          (0x00)
#define DCM_ONE                                                           (0x01)
#define DCM_TWO                                                   ((uint8) 0x02)
#define DCM_THREE                                                 ((uint8) 0x03)
#define DCM_FOUR                                                  ((uint8) 0x04)
#define DCM_FIVE                                                  ((uint8) 0x05)
#define DCM_SIX                                                   ((uint8) 0x06)
#define DCM_SEVEN                                                 ((uint8) 0x07)
#define DCM_EIGHT                                                 ((uint8) 0x08)
#define DCM_NINE                                                  ((uint8) 0x09)
#define DCM_TEN                                                   ((uint8) 0x0A)
#define DCM_ELEVEN                                                ((uint8) 0x0B)
#define DCM_TEWELVE                                               ((uint8) 0x0C)
#define DCM_THIRTEEN                                              ((uint8) 0x0D)
#define DCM_FOURTEEN                                              ((uint8) 0x0E)
#define DCM_FIFTEEN                                               ((uint8) 0x0F)
#define DCM_THIRTY_TWO                                            ((uint8) 0x20)
#define DCM_SIXTY_FOUR                                            ((uint8) 0x40)
#define DCM_NINTY_SIX                                             ((uint8) 0x60)
#define DCM_ONE_TWO_EIGHT                                         ((uint8) 0x80)
#define DCM_ONE_SIXTY                                             ((uint8) 0xA0)
#define DCM_ONE_NINE_TWO                                          ((uint8) 0xC0)
#define DCM_TWO_TWO_FOUR                                          ((uint8) 0xE0)
#define DCM_SIXTEEN                                               ((uint8) 0x10)
#define DCM_TWENTY                                                ((uint8) 0x14)
#define DCM_NINETEEN                                              ((uint8) 0x13)
#define DCM_TWENTYONE                                             ((uint8) 0x15)
#define DCM_SEVENTEEN                                             ((uint8) 0x11)
#define DCM_EIGHTTEEN                                             ((uint8) 0x12)
#define DCM_MAXVALUE                                              ((uint8) 0xFF)
#define DCM_TWENTYFOUR                                            ((uint8) 0x18)

/*******************************************************************************
** Diagnostic Service Ids                                                     **
*******************************************************************************/
#define DCM_DIAGNOSTICSESSIONCONTROL                              ((uint8) 0x10)
#define DCM_ECURESET                                              ((uint8) 0x11)
#define DCM_CLEARDIAGNOSTICINFORMATION                            ((uint8) 0x14)
#define DCM_READDTCINFORMATION                                    ((uint8) 0x19)
#define DCM_READDATABYIDENTIFIER                                  ((uint8) 0x22)
#define DCM_STOPDIAGNOSTICSESSION                                 ((uint8) 0x20)
#define DCM_READMEMORYBYADDRESS                                   ((uint8) 0x23)
#define DCM_READSCALINGDATABYIDENTIFIER                           ((uint8) 0x24)
#define DCM_SECURITYACCESS                                        ((uint8) 0x27)
#define DCM_COMMUNICATIONCONTROL                                  ((uint8) 0x28)
#define DCM_ENABLENORMALMESSAGETRANSMISSION                       ((uint8) 0x29)
#define DCM_READDATABYPERIODICIDENTIFIER                          ((uint8) 0x2A)
#define DCM_DYNAMICALLYDEFINEDATAIDENTIFIER                       ((uint8) 0x2C)
#define DCM_WRITEDATABYIDENTIFIER                                 ((uint8) 0x2E)
#define DCM_INPUTOUTPUTCONTROLBYIDENTIFIER                        ((uint8) 0x2F)
#define DCM_ROUTINECONTROL                                        ((uint8) 0x31)
#define DCM_REQUESTDOWNLOAD                                       ((uint8) 0x34)
#define DCM_REQUESTUPLOAD                                         ((uint8) 0x35)
#define DCM_TRANSFERDATA                                          ((uint8) 0x36)
#define DCM_REQUESTTRANSFEREXIT                                   ((uint8) 0x37)
#define DCM_WRITEMEMORYBYADDRESS                                  ((uint8) 0x3D)
#define DCM_TESTERPRESENT                                         ((uint8) 0x3E)
#define DCM_ACCESSTIMINGPARAMETER                                 ((uint8) 0x83)
#define DCM_SECUREDDATATRANSMISSION                               ((uint8) 0x84)
#define DCM_CONTROLDTCSETTING                                     ((uint8) 0x85)
#define DCM_RESPONSEONEVENT                                       ((uint8) 0x86)
#define DCM_LINKCONTROL                                           ((uint8) 0x87)

/*******************************************************************************
** OBD Service Ids                                                            **
*******************************************************************************/
#define DCM_OBD_REQ_CURRENTPOWERTRAINDIAGDATA                     ((uint8) 0x01)
#define DCM_OBD_REQ_POWERTRAIN_FREEZEFRAME_DATA                   ((uint8) 0x02)
#define DCM_OBD_GETDTC_03                                         ((uint8) 0x03)
#define DCM_OBD_CLRRST_EMISSION_DIAGINFO                          ((uint8) 0x04)
#define DCM_OBD_REQ_ONBOAD_MONITOR_RESULT                         ((uint8) 0x06)
#define DCM_OBD_GETDTC_07                                         ((uint8) 0x07)
#define DCM_OBD_REQ_CTLR_ONBOAD_SYSTEM                            ((uint8) 0x08)
#define DCM_OBD_REQ_VEHICLEINFO                                   ((uint8) 0x09)
#define DCM_OBD_GETDTC_0A                                         ((uint8) 0x0A)

/*******************************************************************************
** ID Contexts                                                                **
*******************************************************************************/
/* OBD Services */
#define DCM_OBD_CLEAR_DIAG_INFO                                   ((uint8) 0x44)

/* ES Services */
#define DCM_STOP_DIAGNOSTIC_SESSION                                ((uint8)0x60)

/* UDS Services */
#define DCM_UDS_DIAG_SESSION_CONTROL                              ((uint8) 0x50)
#define DCM_UDS_ECU_RESET                                         ((uint8) 0x51)
#define DCM_UDS_CLEAR_DIAG_INFO                                   ((uint8) 0x54)
#define DCM_UDS_READ_DTC                                          ((uint8) 0x59)
#define DCM_UDS_READ_MEMORY_BY_ADDRESS                            ((uint8) 0x63)
#define DCM_UDS_COMMUNICATION_CONTROL                             ((uint8) 0x68)
#define DCM_UDS_ENABLE_NORMAL_MSG_TRANSMISSION                    ((uint8) 0x69)
#define DCM_UDS_WRITE_MEMORY_BY_ADDRESS                           ((uint8) 0x7D)

/*******************************************************************************
** Read DTC Sub Functions                                                     **
*******************************************************************************/
#define DCM_UDS_READ_DTC_INFO_01                                  ((uint8) 0x01)
#define DCM_UDS_READ_DTC_INFO_02                                  ((uint8) 0x02)
#define DCM_UDS_READ_DTC_INFO_03                                  ((uint8) 0x03)
#define DCM_UDS_READ_DTC_INFO_04                                  ((uint8) 0x04)
#define DCM_UDS_READ_DTC_INFO_05                                  ((uint8) 0x05)
#define DCM_UDS_READ_DTC_INFO_06                                  ((uint8) 0x06)
#define DCM_UDS_READ_DTC_INFO_07                                  ((uint8) 0x07)
#define DCM_UDS_READ_DTC_INFO_08                                  ((uint8) 0x08)
#define DCM_UDS_READ_DTC_INFO_09                                  ((uint8) 0x09)
#define DCM_UDS_READ_DTC_INFO_0A                                  ((uint8) 0x0A)
#define DCM_UDS_READ_DTC_INFO_0B                                  ((uint8) 0x0B)
#define DCM_UDS_READ_DTC_INFO_0C                                  ((uint8) 0x0C)
#define DCM_UDS_READ_DTC_INFO_0D                                  ((uint8) 0x0D)
#define DCM_UDS_READ_DTC_INFO_0E                                  ((uint8) 0x0E)
#define DCM_UDS_READ_DTC_INFO_0F                                  ((uint8) 0x0F)
#define DCM_UDS_READ_DTC_INFO_10                                  ((uint8) 0x10)
#define DCM_UDS_READ_DTC_INFO_11                                  ((uint8) 0x11)
#define DCM_UDS_READ_DTC_INFO_12                                  ((uint8) 0x12)
#define DCM_UDS_READ_DTC_INFO_13                                  ((uint8) 0x13)
#define DCM_UDS_READ_DTC_INFO_14                                  ((uint8) 0x14)
#define DCM_UDS_READ_DTC_INFO_15                                  ((uint8) 0x15)
#define DCM_UDS_READ_DTC_INFO_17                                  ((uint8) 0x17)
#define DCM_UDS_READ_DTC_INFO_18                                  ((uint8) 0x18)
#define DCM_UDS_READ_DTC_INFO_19                                  ((uint8) 0x19)
#define DCM_UDS_READ_DTC_INFO_42                                  ((uint8) 0x42)
#define DCM_UDS_READ_DTC_INFO_55                                  ((uint8) 0x55)

#if (DCM_J1979_2_SUPPORT == STD_ON)
/* Trace: DCM_19792_56_12 */
#define DCM_UDS_READ_DTC_INFO_56                                  ((uint8) 0x56)
#define DCM_UDS_READ_DTC_INFO_1A                                  ((uint8) 0x1A)
#endif /* J19792 */

/*******************************************************************************
** Related DTC Services Macros                                                **
*******************************************************************************/
/* Control DTC Setting Type */
#define DCM_DTC_SETTING_TYPE_ON                                   ((uint8) 0x01)
#define DCM_DTC_SETTING_TYPE_OFF                                  ((uint8) 0x02)

/* DTC Translation type */
#define DCM_FORMAT_IDENTIFIER_15031_6                             ((uint8) 0x00)
#define DCM_FORMAT_IDENTIFIER_14229_1                             ((uint8) 0x01)

#define DCM_DTC_SEV_MASK                                          ((uint8) 0xE0)
#define DCM_STATUS_MASK_ALL                                       ((uint8) 0x00)

#define DCM_MAX_RECDDATA_SIZE                                     ((uint8) 0xFF)
#define DCM_MAX_EXTND_RECORDS                                     ((uint8) 0xFF)
#define DCM_DTRSTATUS_VISIBLE                                     ((uint8) 0x00)
#define DCM_UDS_DTC_FGID_LIMITATION                               ((uint8) 0x33)

#define DCM_USER_DEFINED_FAULT_MEMORY                          ((uint16) 0x0100)

#define DCM_DTC_ALL                                       ((uint32) 0x00000000u)
#define DCM_DTCGROUP_ALL_GROUPS                           ((uint32) 0x00FFFFFFu)
#define DCM_DTCGROUP_CHASSIS_GROUP                        ((uint32) 0x004000FFu)

/*******************************************************************************
** Related to Communication Control macros                                    **
*******************************************************************************/
#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
  (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
#define DCM_LOCAL_NUM_OF_SUBREQ                                             (4U)
#define DCM_LOCAL_NUM_OF_COMTYPE                                       (3U + 1U)

#elif (DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT)
#define DCM_LOCAL_NUM_OF_SUBREQ                                             (4U)
#define DCM_LOCAL_NUM_OF_COMTYPE                                       (3U + 1U)

#elif (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
#define DCM_LOCAL_NUM_OF_SUBREQ                                             (4U)
#define DCM_LOCAL_NUM_OF_COMTYPE                                       (3U + 1U)

#elif (DCM_STANDARD_SUPPORT == DCM_ES95486_50_SUPPORT)
#define DCM_LOCAL_NUM_OF_SUBREQ                                             (4U)
#define DCM_LOCAL_NUM_OF_COMTYPE                                       (3U + 1U)

#elif (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT)
#define DCM_LOCAL_NUM_OF_SUBREQ                                             (4U)
#define DCM_LOCAL_NUM_OF_COMTYPE                                       (3U + 1U)

#else /* (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)*/
#define DCM_LOCAL_NUM_OF_SUBREQ                                             (6U)
#define DCM_LOCAL_NUM_OF_COMTYPE                                       (3U + 1U)
#endif 
#endif

#define DCM_CC_ENABLE_RX_AND_TX                                  ((uint8) 0x00u)
#define DCM_CC_DIABLE_NM_TRANS                                   ((uint8) 0x01u)
#define DCM_CC_DIABLE_NM_TRANS_NORESP                            ((uint8) 0x02u)
#define DCM_CC_DISABLE_RX_AND_TX                                 ((uint8) 0x03u)
#define DCM_CC_MAX_NUM                                                      (4u)

/* Commnuication Type */
#define DCM_COMM_TYPE_NORMAL                                     ((uint8) 0x01u)
#define DCM_COMM_TYPE_NM                                         ((uint8) 0x02u)
#define DCM_COMM_TYPE_NM_AND_NORMAL                              ((uint8) 0x03u)
#define DCM_COMM_TYPE_MAX_NUM                                               (4u)

/* Communication Mode */
#define DCM_FULL_COMMUNICATION                                    ((uint8) 0x00)
#define DCM_SILENT_COMMUNICATION                                  ((uint8) 0x01)
#define DCM_NO_COMMUNICATION                                      ((uint8) 0x02)

/*******************************************************************************
** Response On Event Macros                                                   **
*******************************************************************************/
#define DCM_ROE_IDLE                                                     (0x00u)
#define DCM_ROEONGOING                                                   (0x01u)
#define DCM_ROEPENDING                                                   (0x02u)

#define DCM_ROE_SUBFUNCTION_MASK                                         (0x3Fu)
#define DCM_ROE_STORE_BIT_MASK                                           (0x40u)

/* sub-function (eventType) bit5-0 definition */
#define DCM_STOP_ROE                                                     (0x00u)
#define DCM_STOP_ROE_STOREBIT                                            (0x40u)

#define DCM_ON_DTC_STATUS_CHANGE                                         (0x01u)
#define DCM_ON_DTC_STATUS_CHANGE_STOREBIT                                (0x41u)

#define DCM_ON_CHANGE_OF_DID                                             (0x03u)
#define DCM_ON_CHANGE_OF_DID_STOREBIT                                    (0x43u)

#define DCM_REPORT_ACTIVATED_EVENTS                                      (0x04u)

#define DCM_START_ROE                                                    (0x05u)
#define DCM_START_ROE_STOREBIT                                           (0x45u)

#define DCM_CLEAR_ROE                                                    (0x06u)
#define DCM_CLEAR_ROE_STOREBIT                                           (0x46u)

/* the max buffer size to store servieToRespondTo */
#define DCM_ROE_STRT_SIZE                                                (0x10u)

#define DCM_ROE_MAX_REQ_DATA_LEN                                         (0x03u)

/* Length of Request Message Parameters */
#define DCM_ROE_MIN_ROE_REQ_MSG_LEN                                      (0x01u)

/* length of ROE request with setup subfuntion
  onDTCStatusChange and onChangeOfDataIdentifier*/
#define DCM_ROE_SETUP_REQ_LEN                                            (0x05u)

/* length of ROE request with control subfuntion
  stop/start/clearResponseOnEvent and reportActivatedEvents*/
#define DCM_ROE_CONTROL_REQ_LEN                                          (0x02u)

/* minimum length of STRTR(serviceToRespondToRecord) request message
   ReadDataByIdentifier = 3-byte
   ReadDTCInformation : 2-byte
   RoutineControl : 4-byte
   InputOutputControlByIdentifier : 3-byte   */
#define DCM_ROE_MIN_STRTR_REQ_MSG_LEN                                    (0x02u)

/* Length of eventTypeRecord when the sub-function is
  stopResponseOnEvent (0x00) */
#define DCM_ROE_ETR_LEN_STPROE                                           (0x00u)

/* Length of eventTypeRecord when the sub-function is
  onDTCStatusChange (0x01) */
#define DCM_ROE_ETR_LEN_ONDTCS                                           (0x01u)

/* Length of eventTypeRecord when the sub-function is
  onChangeOfDataIdentifier (0x03) */
#define DCM_ROE_ETR_LEN_OCODID                                           (0x02u)

/* Length of eventTypeRecord when the sub-function is
  reportActivatedEvents (0x04) */
#define DCM_ROE_ETR_LEN_RAE                                              (0x00u)

/* Length of eventTypeRecord when the sub-function is
  startResponseOnEvent (0x05) */
#define DCM_ROE_ETR_LEN_STRTROE                                          (0x00u)

/* Length of eventTypeRecord when the sub-function is
  clearResponseOnEvent (0x06) */
#define DCM_ROE_ETR_LEN_CLRROE                                           (0x00u)

/* Value of vehicle manufacturer specific eventWindowTime */
#define DCM_ROE_SPECIFIC_WINDOW_TIME                                     (0x02u)

/*******************************************************************************
** Read Data By Periodic Identifier Macros                                    **
*******************************************************************************/
/* Data Buffer Status */
#define DCM_PDID_DATA_IDLE                                        ((uint8) 0x00)
#define DCM_PDID_DATA_READY                                       ((uint8) 0x01)
#define DCM_PDID_DATA_BUSY                                        ((uint8) 0x02)

/* Periodic transmission mode */
#define DCM_PDID_MODE_UNDEFINE                                    ((uint8) 0x00)
#define DCM_PDID_MODE_SLOW_RATE                                   ((uint8) 0x01)
#define DCM_PDID_MODE_MEDIUM_RATE                                 ((uint8) 0x02)
#define DCM_PDID_MODE_FAST_RATE                                   ((uint8) 0x03)
#define DCM_PDID_MODE_STOP_SENDING                                ((uint8) 0x04)

/* Periodic response status state */
#define DCM_PDID_INACTIVE                                         ((uint8) 0x00)
#define DCM_PDID_FIRST_RESPONSE                                   ((uint8) 0x01)
#define DCM_PDID_SCHEDULER_RESPONSE                               ((uint8) 0x02)

/* Periodic state */
#define DCM_PDID_STATE_UNDEFINE                                   ((uint8) 0x00)
#define DCM_PDID_STATE_VALIDATION                                 ((uint8) 0x01)
#define DCM_PDID_STATE_CHECK_READ                                 ((uint8) 0x02)
#define DCM_PDID_STATE_READ_LENGTH                                ((uint8) 0x03)
#define DCM_PDID_STATE_READY_STOP                                 ((uint8) 0x04)
#define DCM_PDID_STATE_READY_START                                ((uint8) 0x05)

/* Number of Periodic Timer */
#define DCM_PDID_NUM_OF_TIMER                                     ((uint8) 0x03)

/* High byte of Periodic Identifier */
#define DCM_PDID_HIGH_BYTE                                        ((uint8) 0xF2)

/* Upper range of Periodic Identifier */
#define DCM_PDID_UPPER_RANGE                                   ((uint16) 0xF2FF)

/* Get PDID from request message */
#define DCM_PDID_ASSEMBLE_DID(pDid)      (((uint16) 0xF200) | ((uint16) (pDid)))

/*******************************************************************************
** Related Did Services Macros                                                **
*******************************************************************************/
#define DCM_SIZEOF_DATAID                                                (0x02u)

#define DCM_OBDDID_LOWER_RANGE                                 ((uint16) 0xF400)
#define DCM_OBDDID_RANGE_F4FF                                  ((uint16) 0xF4FF)
#define DCM_OBDDID_RANGE_F600                                  ((uint16) 0xF600)
#define DCM_OBDDID_RANGE_F6FF                                  ((uint16) 0xF6FF)
#define DCM_OBDDID_RANGE_F800                                  ((uint16) 0xF800)
#define DCM_OBDDID_UPPER_RANGE                                 ((uint16) 0xF8FF)

#define DCM_READDATABYID_F186                                  ((uint16) 0xF186)
#define DCM_READDATABYID_F810                                  ((uint16) 0xF810)

#define DCM_IOCTRL_MINIMUM_LENGTH                              ((uint32) 0x0003)

#define DCM_DDDID_LOWER_RANGE                                  ((uint16) 0xF200)
#define DCM_DDDID_UPPER_RANGE                                  ((uint16) 0xF3FF)

#define DCM_CLEAR_DEFINED_DDDID                                   ((uint8) 0x03)
#define DCM_DEFINE_DDDID_BY_MEMORY                                ((uint8) 0x02)
#define DCM_DEFINE_DDDID_BY_DATAID                                ((uint8) 0x01)

/* Status of did signals  */
#define DCM_OPSTATUS_INITIAL                                      ((uint8) 0x00)
#define DCM_OPSTATUS_COMPLETE                                     ((uint8) 0x01)
#define DCM_OPSTATUS_PENDING                                      ((uint8) 0x02)

/*******************************************************************************
** Routine Control Services Macros                                            **
*******************************************************************************/
#define DCM_RID_CTRL_START                                        ((uint8) 0x01)
#define DCM_RID_CTRL_STOP                                         ((uint8) 0x02)
#define DCM_RID_CTRL_REQUEST                                      ((uint8) 0x03)

#define DCM_RID_OBD_LOW_RANGE                                  ((uint16) 0xE000)
#define DCM_RID_OBD_HIGH_RANGE                                 ((uint16) 0xE0FF)

/*******************************************************************************
** Link Control Services Macros                                               **
*******************************************************************************/
#define DCM_LINK_CTRL_MODE_TRANSITION_WITH_FIXED_PARAMETER        ((uint8) 0x01)
#define DCM_LINK_CTRL_MODE_TRANSITION_WITH_SPECIFIC_PARAMETER     ((uint8) 0x02)
#define DCM_LINK_CTRL_TRANSITION_BAUDRATE                         ((uint8) 0x03)

/*******************************************************************************
** Related OBD Services Macros                                                **
*******************************************************************************/
/* Macro to get PID */
#define DCM_GET_PID                                               ((uint8) 0x00)

/* Macro to get TID */
#define DCM_GET_TID                                               ((uint8) 0x02)

/* Macro to get OBDMID */
#define DCM_GET_OBDMID                                            ((uint8) 0x01)

/* Macro to get InfoType */
#define DCM_GET_VID                                               ((uint8) 0x03)

/* Macro to other PID */
#define DCM_OTHER_PID                                             ((uint8) 0x04)

/* Macro to get DID (0xF400 - 0xF4FF) */
#define DCM_OTHER_DID_OBD_RANGE                                   ((uint8) 0x04)

/* Macro to get DID (0xF800 - 0xF8FF) */
#define DCM_OTHER_DID_INFOTYPE_RANGE                              ((uint8) 0x05)

/* Macro to TWO PID */
#define DCM_TWO_PID                                               ((uint8) 0x08)

  /* Value of service id of OBD */
#define DCM_OBD_NO_SID                                            ((uint8) 0xFF)

/* ID related to Availability list */
#define DCM_AVAIL_ID                                                  (DCM_ZERO)

/* ID related to Dem */
#define DCM_DEM_PID                                                    (DCM_ONE)

/* ID related to R-Port */
#define DCM_R_PORT_PID                                                 (DCM_TWO)

/* Search macros */
#define DCM_NOT_CONFIG_ID                                             (DCM_FIVE)

/* Dem PIDs */
#define DCM_DEMPID01                                              ((uint8) 0x01)
#define DCM_DEMPID1C                                              ((uint8) 0x1C)
#define DCM_DEMPID21                                              ((uint8) 0x21)
#define DCM_DEMPID30                                              ((uint8) 0x30)
#define DCM_DEMPID31                                              ((uint8) 0x31)
#define DCM_DEMPID41                                              ((uint8) 0x41)
#define DCM_DEMPID4D                                              ((uint8) 0x4D)
#define DCM_DEMPID4E                                              ((uint8) 0x4E)

/*******************************************************************************
** Det Report Errors                                                          **
*******************************************************************************/
/* Development errors */
/* @Trace: SRS_BSW_00337 */
/* @Trace: SWS_Dcm_00044 SWS_Dcm_00040 */
#define DCM_E_INTERFACE_RETURN_VALUE                              ((uint8) 0x02)
#define DCM_E_INTERFACE_BUFFER_OVERFLOW                           ((uint8) 0x03)
#define DCM_E_UNINIT                                              ((uint8) 0x05)
#define DCM_E_PARAM                                               ((uint8) 0x06)
#define DCM_E_PARAM_POINTER                                       ((uint8) 0x07)
#define DCM_E_INIT_FAILED                                         ((uint8) 0x08)
#define DCM_E_SET_PROG_CONDITIONS_FAIL                            ((uint8) 0x09)

/* Run time errors */
/* @Trace: SRS_BSW_00369 SRS_BSW_00452 */
/* @Trace: SWS_Dcm_00044 SWS_Dcm_01416 */
#define DCM_E_INTERFACE_TIMEOUT                                   ((uint8) 0x01)
#define DCM_E_INVALID_VALUE                                       ((uint8) 0x0A)
#define DCM_E_FORCE_RCRRP_IN_SILENT_COMM                          ((uint8) 0x0B)

/*******************************************************************************
** Common macros                                                              **
*******************************************************************************/
/* Boolean macros */
#define DCM_TRUE                                                ((boolean) 0x01)
#define DCM_FALSE                                               ((boolean) 0x00)

/* Processing types */
#define DCM_SYNC_DONE                                                 (DCM_TRUE)
#define DCM_ASYNC_DONE                                               (DCM_FALSE)

/* Initialize macros */
#define DCM_INITIALIZED                                               (DCM_TRUE)
#define DCM_UNINITIALIZED                                            (DCM_FALSE)

/*  Macro ID For response */
#define DCM_SID_MASK                                              ((uint8) 0xBF)
#define DCM_RESPONSE_ID                                           ((uint8) 0x40)

#define DCM_SUPRESSBIT_MASK                                       ((uint8) 0x80)
#define DCM_SUBFUNCTION_MASK                                      ((uint8) 0x7F)

#define DCM_NEGATIVE_RESPONSE_SID                                 ((uint8) 0x7F)
#define DCM_SERVICE_NOT_CONFIGURED                                ((uint8) 0xFF)

/* DSP Macros*/
#define DCM_BIT6_AND_MASK                                         ((uint8) 0xBF)
#define DCM_BIT0_AND_MASK                                         ((uint8) 0x01)
#define DCM_SIG_SIZE_MASK_VALUE                                   ((uint8) 0xF0)
#define DCM_SIG_BYTE_MASK_VALUE                                   ((uint8) 0x0F)

#define DCM_U8_HLSB_MASK                                       ((uint16) 0x00FF)
#define DCM_U8_MSB_MASK                                        ((uint16) 0xFF00)

#define DCM_U16_LSB_MASK                                       ((uint16) 0x00FF)
#define DCM_U16_MSB_MASK                                       ((uint16) 0xFF00)

#define DCM_8B_ALIGN(b)                                            (((b) + 7)/8)

#define DCM_U16_LO_BYTE(b)                               ((uint8) ((b) & 0xFFU))
#define DCM_U16_HI_BYTE(b)                       ((uint8) (((b) >> 8U) & 0xFFU))

#define DCM_LO_NIBBLE(b, type)            ((type) (((type) (b)) & (type) 0x0FU))
#define DCM_HI_NIBBLE(b, type)    ((type) ((((type) (b)) >> 4U) & (type) 0x0FU))

#ifndef DCM_INLINE
#ifndef INLINE
#define DCM_INLINE inline
#else
#define DCM_INLINE INLINE
#endif
#endif

#define DCM_UNUSED(variable)                                   ((void) variable)

/* polyspace +1 MISRA2012:D4.9 [Justified:Low] "DCM_UNUSED_PTR is used in integration_Dcm." */
#define DCM_UNUSED_PTR(x)   do{if((x) != NULL_PTR) {}} while(0)

/*******************************************************************************
** Other features macros and types                                            **
*******************************************************************************/
#define DCM_BUFSZ_TESTERPRESENT                                          (0x08u)

/* Internal DTC Diagnostic Service support */
#define DEM_SESCTRL_ITC_TYPE                                      ((uint8) 0x01)
#define DCM_READ_ITC_SERVICE                                      ((uint8) 0xBA)
#define DCM_CLEAR_ITC_SERVICE                                     ((uint8) 0xBB)

#define DCM_ITC_STATUS_MASK                                              (0x08u)

#define DCM_RECEPTION_ONGOING                                     ((uint8) 0x01)
#define DCM_RECEPTION_COMPLETED                                   ((uint8) 0x02)
#define DCM_RECEPTION_IDLE                                        ((uint8) 0x03)
#define DCM_RECEPTION_CANCELLED                                   ((uint8) 0x04)

#define TXPDUID_UNSET                                                     (0xFF)
#define ADDRESS_UNSET                                                   (0xFFFF)
#define DEM_CLIENTID_UNSET                                        ((uint8) 0xFF)

typedef uint8 Dcm_ModeType;

typedef uint8 Dcm_BufferKindType;
#define DCM_BUFFER_KIND_TX                          ((Dcm_BufferKindType) 0x01u)
#define DCM_BUFFER_KIND_RX                          ((Dcm_BufferKindType) 0x02u)
#define DCM_BUFFER_KIND_TX_ROE                      ((Dcm_BufferKindType) 0x03u)
#define DCM_BUFFER_KIND_TX_PERIODIC                 ((Dcm_BufferKindType) 0x04u)

/*******************************************************************************
** Tester Present Type                                                        **
*******************************************************************************/
#define DCM_NO_TESTER_PRESENT_REQUESTED                          ((uint8) 0x00u)
#define DCM_CONCURENT_TESTER_PRESENT                             ((uint8) 0x01u)
#define DCM_TRANSPARENT_TESTER_PRESENT                           ((uint8) 0x02u)

/*******************************************************************************
** First call to main type                                                    **
*******************************************************************************/
#define DCM_FIRST_CALL_TO_MAIN_INIT                              ((uint8) 0x00u)
#define DCM_FIRST_CALL_TO_MAIN_WAIT                              ((uint8) 0x01u)
#define DCM_FIRST_CALL_TO_MAIN_EXECUTE                           ((uint8) 0x02u)
#define DCM_FIRST_CALL_TO_MAIN_DONE                              ((uint8) 0x03u)

/*******************************************************************************
** Function like-macros                                                       **
*******************************************************************************/
#define DCM_GET_RID_FROM_REQUEST(routineId, pReqData) \
  do { \
    (routineId) = (uint16) (pReqData)[DCM_ONE]; \
    (routineId) = (uint16) (routineId) << DCM_EIGHT; \
    (routineId) = (uint16) (routineId) | (pReqData)[DCM_TWO]; \
  } while (0);

/* Clear the periodic pdu status */
#define DCM_PDID_CLR_PDU_STATUS(pPerPdu) \
  (*((pPerPdu)->pPerPduIdStatus) &= ~((pPerPdu)->usPerPduIdStatusMask))

/* Set the periodic pdu status */
#define DCM_PDID_SET_PDU_STATUS(pPerPdu) \
  (*((pPerPdu)->pPerPduIdStatus) |= (pPerPdu)->usPerPduIdStatusMask)

/* Check the the periodic pdu status is set or not */
#define DCM_PDID_IS_SET_PDU_STATUS(pPerPdu) \
  ((*((pPerPdu)->pPerPduIdStatus) & (pPerPdu)->usPerPduIdStatusMask) != DCM_ZERO)

/* Check the the periodic pdu status is clear or not */
#define DCM_PDID_IS_CLR_PDU_STATUS(pPerPdu) \
  ((*((pPerPdu)->pPerPduIdStatus) & (pPerPdu)->usPerPduIdStatusMask) == DCM_ZERO)

#define DCM_SET_RDATA_PENDING_STATUS(s)\
  do { \
    Dcm_ServicePendingStatus.ucReadDataPendingStatus = (s); \
  } while(0)

#define DCM_GET_DATAID_FROM_REQUEST(lvalue, rvalue, pos) \
  do { \
    (lvalue) = (uint16)(rvalue)[(pos)]; \
    (lvalue) = (uint16)((lvalue) << 8U); \
    (lvalue) = (lvalue) | (uint16)(rvalue)[(pos) + 1U]; \
  } while(0)

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
#define DCM_SET_DATAID_IN_RESPONSE(buf,pos,did) \
  do { \
    if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE) \
    { \
      (buf)[(pos)] = DCM_U16_LO_BYTE((did)); \
      (pos) += 1; \
    } \
    else \
    { \
      (buf)[(pos)] = DCM_U16_HI_BYTE((did)); \
      (buf)[(pos) + 1U] = DCM_U16_LO_BYTE((did)); \
      (pos) += DCM_SIZEOF_DATAID; \
    } \
  } while(0)
#else
#define DCM_SET_DATAID_IN_RESPONSE(buf,pos,did) \
  do { \
    (buf)[(pos)] = DCM_U16_HI_BYTE((did)); \
    (buf)[(pos) + 1U] = DCM_U16_LO_BYTE((did)); \
    (pos) += DCM_SIZEOF_DATAID; \
  } while(0)
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
#define DCM_REPORT_ERROR(ApiId, ErrorId) \
  { (void) Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID, ApiId, ErrorId); }

#define DCM_REPORT_RUNTIME_ERROR(ApiId, ErrorId) \
  { (void) Det_ReportRuntimeError(DCM_MODULE_ID, DCM_INSTANCE_ID, ApiId, ErrorId); }

#else
#define DCM_REPORT_ERROR(ApiId, ErrorId) \
  { \
    DCM_UNUSED(ApiId); \
    DCM_UNUSED(ErrorId); \
  }

#define DCM_REPORT_RUNTIME_ERROR(ApiId, ErrorId) \
  { \
    DCM_UNUSED(ApiId); \
    DCM_UNUSED(ErrorId); \
  }
#endif

#define DCM_CLEAR_ALL_DSP_FLAGS() \
do {\
  Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;\
  Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;\
  Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;\
  Dcm_DspSerPgStatus.ucPagingStarted = DCM_FALSE;\
  Dcm_DspSerPgStatus.ucFirstPage = DCM_FALSE;\
  Dcm_DspSerPgStatus.ucPagingInMid = DCM_FALSE;\
  Dcm_DspSerPgStatus.ucMultipleRecd = DCM_FALSE;\
} while(0)

#define DCM_GET_MEMORY_ADDR_BYTES(addLenFormat) \
  (((uint8) (addLenFormat)) & ((uint8) 0x0F))

#define DCM_GET_MEMORY_SIZE_BYTES(addLenFormat) \
  (((uint8) (addLenFormat)) >> (uint8) 0x04) & ((uint8) 0x0F)

// Protocol status
#define DCM_CLR_PROTOCOL_STATUS(PRT)    (*((PRT)->pProtocolStatus) &= (~((PRT)->ucPrtclStatusMask)))
#define DCM_SET_PROTOCOL_STATUS(PRT)    (*((PRT)->pProtocolStatus) |=  ((PRT)->ucPrtclStatusMask))
#define DCM_IS_SET_PROTOCOL_STATUS(PRT) \
  (boolean) (((*((PRT)->pProtocolStatus)) & ((PRT)->ucPrtclStatusMask)) == ((PRT)->ucPrtclStatusMask))

// PduId status
#define DCM_CLR_PDU_STATUS(PDU)    (*((PDU)->pPduIdStatus) &= (~((PDU)->usPduIdStatusMask)))
#define DCM_SET_PDU_STATUS(PDU)    (*((PDU)->pPduIdStatus) |=  ((PDU)->usPduIdStatusMask))
#define DCM_IS_SET_PDU_STATUS(PDU) \
  (((*((PDU)->pPduIdStatus)) & ((PDU)->usPduIdStatusMask)) == ((PDU)->usPduIdStatusMask))
#define DCM_IS_CLR_PDU_STATUS(PDU) \
  (((*((PDU)->pPduIdStatus)) & ((PDU)->usPduIdStatusMask)) != ((PDU)->usPduIdStatusMask))

#define CHECK_DEFAULT_SESSION(LucSession) ((DCM_DEFAULT_SESSION) == (LucSession))
#define CHECK_NONDEFAULT_SESSION(LucSession) ((DCM_DEFAULT_SESSION) != (LucSession))

#if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
#define DCM_UNUSED_AUTHENTICATION_NRC                                 ((uint8)0)
#endif

/*public Key length*/
#define DCM_SEC_PUBLIC_KEY_LENGTH    256
#endif /* DCM_TYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
