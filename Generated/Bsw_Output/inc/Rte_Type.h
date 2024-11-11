/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : Rte_Type.h                                                    **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/
/******************************************************************************/
/*                 Multiple Header Inclusion Protection Start                 */
/******************************************************************************/
#ifndef RTE_TYPE_H
#define RTE_TYPE_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                  Type Definitions for AUTOSAR data types                   */
/******************************************************************************/
typedef signed long StbM_TimeDiffType;
typedef unsigned char StbM_TimeBaseStatusType;
typedef unsigned long StbM_TimeBaseNotificationType;
typedef unsigned short StbM_SynchronizedTimeBaseType;
typedef signed short StbM_RateDeviationType;
typedef unsigned char StbM_MasterConfigType;
typedef unsigned short StbM_CustomerIdType;
typedef unsigned char KeyM_ResultType;
typedef unsigned short IoHwAb_ValueType;
typedef unsigned char IoHwAb_ThresholdType;
typedef unsigned long IoHwAb_PwmPeriodType;
typedef unsigned char IoHwAb_PwmEdgeType;
typedef unsigned short IoHwAb_OcuValueType;
typedef unsigned char IoHwAb_OcuReturnType;
typedef unsigned char IoHwAb_OcuPinStateType;
typedef unsigned char IoHwAb_OcuPinActionType;
typedef unsigned char IoHwAb_LevelType;
typedef unsigned char IoHwAb_LengthType;
typedef unsigned short IoHwAb_IndexType;
typedef unsigned short IoHwAb_IcuValueType;
typedef unsigned char IoHwAb_IcuStateType;
typedef unsigned short IoHwAb_IcuIndexType;
typedef unsigned long IoHwAb_IcuEdgeNumberType;
typedef unsigned char IoHwAb_IcuActivationType;
typedef unsigned long IoHwAb_GptValueType;
typedef unsigned char IoHwAb_BoolType;
typedef unsigned char FiM_FunctionIdType;
typedef unsigned char Dem_UdsStatusByteType;
typedef unsigned char Dem_RatioIdType;
typedef unsigned char Dem_MonitorStatusType;
typedef unsigned long Dem_MonitorDataType;
typedef unsigned char Dem_J1939DcmSetFreezeFrameFilterType;
typedef unsigned char Dem_J1939DcmSetClearFilterType;
typedef unsigned char Dem_J1939DcmDTCStatusFilterType;
typedef unsigned char Dem_IumprDenomCondStatusType;
typedef unsigned char Dem_IumprDenomCondIdType;
typedef unsigned char Dem_InitMonitorReasonType;
typedef unsigned char Dem_IndicatorStatusType;
typedef unsigned char Dem_EventStatusType;
typedef unsigned char Dem_EventStatusExtendedType;
typedef unsigned char Dem_EventOBDReadinessGroupType;
typedef unsigned short Dem_EventIdType;
typedef unsigned char Dem_DebouncingStateType;
typedef unsigned char Dem_DebounceResetStatusType;
typedef unsigned char Dem_DTRControlType;
typedef unsigned char Dem_DTCTranslationFormatType;
typedef unsigned char Dem_DTCSeverityType;
typedef unsigned char Dem_DTCRequestType;
typedef unsigned short Dem_DTCOriginType;
typedef unsigned char Dem_DTCKindType;
typedef unsigned char Dem_DTCFormatType;
typedef unsigned char Dem_ConfigType;
typedef unsigned short Dem_ComponentIdType;
typedef unsigned char Dcm_OpStatusType;
typedef unsigned char Csm_ResultType;
typedef unsigned char Crypto_VerifyResultType;
typedef unsigned char Crypto_OperationModeType;
typedef unsigned char ComM_UserHandleType;
typedef unsigned char BswM_StateManagerType;
typedef unsigned char BswM_ShutdownTargetType;
typedef unsigned char BswM_EcuModeTransition;
typedef unsigned long AUTOSAR_uint8_least;
typedef unsigned char AUTOSAR_uint8;
typedef unsigned long AUTOSAR_uint32_least;
typedef unsigned long AUTOSAR_uint32;
typedef unsigned long AUTOSAR_uint16_least;
typedef unsigned short AUTOSAR_uint16;
typedef signed long AUTOSAR_sint8_least;
typedef signed char AUTOSAR_sint8;
typedef signed long AUTOSAR_sint64;
typedef signed long AUTOSAR_sint32_least;
typedef signed long AUTOSAR_sint32;
typedef signed long AUTOSAR_sint16_least;
typedef signed short AUTOSAR_sint16;
typedef double AUTOSAR_float64;
typedef float AUTOSAR_float32;
typedef unsigned char AUTOSAR_boolean;
typedef uint8 array8uint8[8];
typedef uint8 array64uint8[64];
typedef uint16 WdgM_SupervisedEntityIdType;
typedef uint8 WdgM_ModeType;
typedef uint8 WdgM_LocalStatusType;
typedef uint8 WdgM_GlobalStatusType;
typedef uint16 WdgM_CheckpointIdType;
typedef void * VoidPtr;
struct _StbM_UserDataType_ {
  unsigned short userDataLength;
  unsigned char userByte0;
  unsigned char userByte1;
  unsigned char userByte2;
};
typedef struct _StbM_UserDataType_ StbM_UserDataType;

struct _StbM_TimeStampType_ {
  unsigned char timeBaseStatus;
  unsigned long nanoseconds;
  unsigned long seconds;
  unsigned short secondsHi;
};
typedef struct _StbM_TimeStampType_ StbM_TimeStampType;

struct _StbM_TimeStampExtendedType_ {
  unsigned char timeBaseStatus;
  unsigned long nanoseconds;
  unsigned long long seconds;
};
typedef struct _StbM_TimeStampExtendedType_ StbM_TimeStampExtendedType;

struct _StbM_SyncRecordTableHeadType_ {
  unsigned char SynchronizedTimeDomain;
  unsigned long HWfrequency;
  unsigned long HWprescaler;
};
typedef struct _StbM_SyncRecordTableHeadType_ StbM_SyncRecordTableHeadType;

struct _StbM_SyncRecordTableBlockType_ {
  unsigned long GlbSeconds;
  unsigned long GlbNanoSeconds;
  unsigned char TimeBaseStatus;
  unsigned long VirtualLocalTimeLow;
  signed short RateDeviation;
  unsigned long LocSeconds;
  unsigned long LocNanoSeconds;
  unsigned long PathDelay;
};
typedef struct _StbM_SyncRecordTableBlockType_ StbM_SyncRecordTableBlockType;

struct _StbM_OffsetRecordTableHeadType_ {
  unsigned char OffsetTimeDomain;
};
typedef struct _StbM_OffsetRecordTableHeadType_ StbM_OffsetRecordTableHeadType;

struct _StbM_OffsetRecordTableBlockType_ {
  unsigned long GlbSeconds;
  unsigned long GlbNanoSeconds;
  unsigned char TimeBaseStatus;
};
typedef struct _StbM_OffsetRecordTableBlockType_ StbM_OffsetRecordTableBlockType;

typedef uint8 NvM_RequestResultType;
typedef uint8 NvM_InitBlockRequestType;
typedef uint8 NvM_BlockRequestType;
typedef uint16 NvM_BlockIdType;
struct _MsgGr_LIN2_SlaveResp_ {
  uint8 SlaveRespB0;
  uint8 SlaveRespB1;
  uint8 SlaveRespB2;
  uint8 SlaveRespB3;
  uint8 SlaveRespB4;
  uint8 SlaveRespB5;
  uint8 SlaveRespB6;
  uint8 SlaveRespB7;
};
typedef struct _MsgGr_LIN2_SlaveResp_ MsgGr_LIN2_SlaveResp;

struct _MsgGr_LIN2_RR_Sensor_Status_ {
  uint16 RR_TOF;
  boolean RR_Sensor_Status_0;
  boolean RR_Sensor_Status_1;
  boolean RR_Sensor_Status_2;
  boolean RR_Sensor_Status_3;
  boolean RR_Sensor_Status_4;
  boolean RR_Sensor_Status_5;
  boolean RR_Sensor_Status_6;
  boolean RR_Sensor_Status_7;
  uint8 RR_CRC;
  uint8 RR_Ringtime;
};
typedef struct _MsgGr_LIN2_RR_Sensor_Status_ MsgGr_LIN2_RR_Sensor_Status;

struct _MsgGr_LIN2_RL_Sensor_Status_ {
  uint16 RL_TOF;
  boolean RL_Sensor_Status_0;
  boolean RL_Sensor_Status_1;
  boolean RL_Sensor_Status_2;
  boolean RL_Sensor_Status_3;
  boolean RL_Sensor_Status_4;
  boolean RL_Sensor_Status_5;
  boolean RL_Sensor_Status_6;
  boolean RL_Sensor_Status_7;
  uint8 RL_CRC;
  uint8 RL_Ringtime;
};
typedef struct _MsgGr_LIN2_RL_Sensor_Status_ MsgGr_LIN2_RL_Sensor_Status;

struct _MsgGr_LIN2_RCR_Sensor_Status_ {
  uint16 RCR_TOF;
  boolean RCR_Sensor_Status_0;
  boolean RCR_Sensor_Status_1;
  boolean RCR_Sensor_Status_2;
  boolean RCR_Sensor_Status_3;
  boolean RCR_Sensor_Status_4;
  boolean RCR_Sensor_Status_5;
  boolean RCR_Sensor_Status_6;
  boolean RCR_Sensor_Status_7;
  uint8 RCR_CRC;
  uint8 RCR_Ringtime;
};
typedef struct _MsgGr_LIN2_RCR_Sensor_Status_ MsgGr_LIN2_RCR_Sensor_Status;

struct _MsgGr_LIN2_RCL_Sensor_Status_ {
  uint16 RCL_TOF;
  boolean RCL_Sensor_Status_0;
  boolean RCL_Sensor_Status_1;
  boolean RCL_Sensor_Status_2;
  boolean RCL_Sensor_Status_3;
  boolean RCL_Sensor_Status_4;
  boolean RCL_Sensor_Status_5;
  boolean RCL_Sensor_Status_6;
  boolean RCL_Sensor_Status_7;
  uint8 RCL_CRC;
  uint8 RCL_Ringtime;
};
typedef struct _MsgGr_LIN2_RCL_Sensor_Status_ MsgGr_LIN2_RCL_Sensor_Status;

struct _MsgGr_LIN2_Master_Cmd_ {
  uint8 NAD;
  uint8 PCI_Type;
  uint8 SID;
  boolean RL_Sensor_Tx;
  boolean RCL_Sensor_Tx;
  boolean RCR_Sensor_Tx;
  boolean RR_Sensor_Tx;
  boolean FL_Sensor_Tx;
  boolean FCL_Sensor_Tx;
  boolean FCR_Sensor_Tx;
  boolean FR_Sensor_Tx;
  boolean RL_Sensor_Rx;
  boolean RCL_Sensor_Rx;
  boolean RCR_Sensor_Rx;
  boolean RR_Sensor_Rx;
  boolean FL_Sensor_Rx;
  boolean FCL_Sensor_Rx;
  boolean FCR_Sensor_Rx;
  boolean FR_Sensor_Rx;
};
typedef struct _MsgGr_LIN2_Master_Cmd_ MsgGr_LIN2_Master_Cmd;

struct _MsgGr_LIN2_MasterReq_ {
  uint8 MasterReqB0;
  uint8 MasterReqB1;
  uint8 MasterReqB2;
  uint8 MasterReqB3;
  uint8 MasterReqB4;
  uint8 MasterReqB5;
  uint8 MasterReqB6;
  uint8 MasterReqB7;
};
typedef struct _MsgGr_LIN2_MasterReq_ MsgGr_LIN2_MasterReq;

struct _MsgGr_LIN2_FR_Sensor_Status_ {
  uint16 FR_TOF;
  boolean FR_Sensor_Status_0;
  boolean FR_Sensor_Status_1;
  boolean FR_Sensor_Status_2;
  boolean FR_Sensor_Status_3;
  boolean FR_Sensor_Status_4;
  boolean FR_Sensor_Status_5;
  boolean FR_Sensor_Status_6;
  boolean FR_Sensor_Status_7;
  uint8 FR_CRC;
  uint8 FR_Ringtime;
};
typedef struct _MsgGr_LIN2_FR_Sensor_Status_ MsgGr_LIN2_FR_Sensor_Status;

struct _MsgGr_LIN2_FL_Sensor_Status_ {
  uint16 FL_TOF;
  boolean FL_Sensor_Status_0;
  boolean FL_Sensor_Status_1;
  boolean FL_Sensor_Status_2;
  boolean FL_Sensor_Status_3;
  boolean FL_Sensor_Status_4;
  boolean FL_Sensor_Status_5;
  boolean FL_Sensor_Status_6;
  boolean FL_Sensor_Status_7;
  uint8 FL_CRC;
  uint8 FL_Ringtime;
};
typedef struct _MsgGr_LIN2_FL_Sensor_Status_ MsgGr_LIN2_FL_Sensor_Status;

struct _MsgGr_LIN2_FCR_Sensor_Status_ {
  uint16 FCR_TOF;
  boolean FCR_Sensor_Status_0;
  boolean FCR_Sensor_Status_1;
  boolean FCR_Sensor_Status_2;
  boolean FCR_Sensor_Status_3;
  boolean FCR_Sensor_Status_4;
  boolean FCR_Sensor_Status_5;
  boolean FCR_Sensor_Status_6;
  boolean FCR_Sensor_Status_7;
  uint8 FCR_CRC;
  uint8 FCR_Ringtime;
};
typedef struct _MsgGr_LIN2_FCR_Sensor_Status_ MsgGr_LIN2_FCR_Sensor_Status;

struct _MsgGr_LIN2_FCL_Sensor_Status_ {
  uint16 FCL_TOF;
  boolean FCL_Sensor_Status_0;
  boolean FCL_Sensor_Status_1;
  boolean FCL_Sensor_Status_2;
  boolean FCL_Sensor_Status_3;
  boolean FCL_Sensor_Status_4;
  boolean FCL_Sensor_Status_5;
  boolean FCL_Sensor_Status_6;
  boolean FCL_Sensor_Status_7;
  uint8 FCL_CRC;
  uint8 FCL_Ringtime;
};
typedef struct _MsgGr_LIN2_FCL_Sensor_Status_ MsgGr_LIN2_FCL_Sensor_Status;

struct _MsgGr_LIN1_SlaveResp_ {
  uint8 SlaveRespB0;
  uint8 SlaveRespB1;
  uint8 SlaveRespB2;
  uint8 SlaveRespB3;
  uint8 SlaveRespB4;
  uint8 SlaveRespB5;
  uint8 SlaveRespB6;
  uint8 SlaveRespB7;
};
typedef struct _MsgGr_LIN1_SlaveResp_ MsgGr_LIN1_SlaveResp;

struct _MsgGr_LIN1_RR_Sensor_Status_ {
  uint16 RR_TOF;
  boolean RR_Sensor_Status_0;
  boolean RR_Sensor_Status_1;
  boolean RR_Sensor_Status_2;
  boolean RR_Sensor_Status_3;
  boolean RR_Sensor_Status_4;
  boolean RR_Sensor_Status_5;
  boolean RR_Sensor_Status_6;
  boolean RR_Sensor_Status_7;
  uint8 RR_CRC;
  uint8 RR_Ringtime;
};
typedef struct _MsgGr_LIN1_RR_Sensor_Status_ MsgGr_LIN1_RR_Sensor_Status;

struct _MsgGr_LIN1_RL_Sensor_Status_ {
  uint16 RL_TOF;
  boolean RL_Sensor_Status_0;
  boolean RL_Sensor_Status_1;
  boolean RL_Sensor_Status_2;
  boolean RL_Sensor_Status_3;
  boolean RL_Sensor_Status_4;
  boolean RL_Sensor_Status_5;
  boolean RL_Sensor_Status_6;
  boolean RL_Sensor_Status_7;
  uint8 RL_CRC;
  uint8 RL_Ringtime;
};
typedef struct _MsgGr_LIN1_RL_Sensor_Status_ MsgGr_LIN1_RL_Sensor_Status;

struct _MsgGr_LIN1_RCR_Sensor_Status_ {
  uint16 RCR_TOF;
  boolean RCR_Sensor_Status_0;
  boolean RCR_Sensor_Status_1;
  boolean RCR_Sensor_Status_2;
  boolean RCR_Sensor_Status_3;
  boolean RCR_Sensor_Status_4;
  boolean RCR_Sensor_Status_5;
  boolean RCR_Sensor_Status_6;
  boolean RCR_Sensor_Status_7;
  uint8 RCR_CRC;
  uint8 RCR_Ringtime;
};
typedef struct _MsgGr_LIN1_RCR_Sensor_Status_ MsgGr_LIN1_RCR_Sensor_Status;

struct _MsgGr_LIN1_RCL_Sensor_Status_ {
  uint16 RCL_TOF;
  boolean RCL_Sensor_Status_0;
  boolean RCL_Sensor_Status_1;
  boolean RCL_Sensor_Status_2;
  boolean RCL_Sensor_Status_3;
  boolean RCL_Sensor_Status_4;
  boolean RCL_Sensor_Status_5;
  boolean RCL_Sensor_Status_6;
  boolean RCL_Sensor_Status_7;
  uint8 RCL_CRC;
  uint8 RCL_Ringtime;
};
typedef struct _MsgGr_LIN1_RCL_Sensor_Status_ MsgGr_LIN1_RCL_Sensor_Status;

struct _MsgGr_LIN1_Master_Cmd_ {
  uint8 NAD;
  uint8 PCI_Type;
  uint8 SID;
  boolean RL_Sensor_Tx;
  boolean RCL_Sensor_Tx;
  boolean RCR_Sensor_Tx;
  boolean RR_Sensor_Tx;
  boolean FL_Sensor_Tx;
  boolean FCL_Sensor_Tx;
  boolean FCR_Sensor_Tx;
  boolean FR_Sensor_Tx;
  boolean RL_Sensor_Rx;
  boolean RCL_Sensor_Rx;
  boolean RCR_Sensor_Rx;
  boolean RR_Sensor_Rx;
  boolean FL_Sensor_Rx;
  boolean FCL_Sensor_Rx;
  boolean FCR_Sensor_Rx;
  boolean FR_Sensor_Rx;
};
typedef struct _MsgGr_LIN1_Master_Cmd_ MsgGr_LIN1_Master_Cmd;

struct _MsgGr_LIN1_MasterReq_ {
  uint8 MasterReqB0;
  uint8 MasterReqB1;
  uint8 MasterReqB2;
  uint8 MasterReqB3;
  uint8 MasterReqB4;
  uint8 MasterReqB5;
  uint8 MasterReqB6;
  uint8 MasterReqB7;
};
typedef struct _MsgGr_LIN1_MasterReq_ MsgGr_LIN1_MasterReq;

struct _MsgGr_LIN1_FR_Sensor_Status_ {
  uint16 FR_TOF;
  boolean FR_Sensor_Status_0;
  boolean FR_Sensor_Status_1;
  boolean FR_Sensor_Status_2;
  boolean FR_Sensor_Status_3;
  boolean FR_Sensor_Status_4;
  boolean FR_Sensor_Status_5;
  boolean FR_Sensor_Status_6;
  boolean FR_Sensor_Status_7;
  uint8 FR_CRC;
  uint8 FR_Ringtime;
};
typedef struct _MsgGr_LIN1_FR_Sensor_Status_ MsgGr_LIN1_FR_Sensor_Status;

struct _MsgGr_LIN1_FL_Sensor_Status_ {
  uint16 FL_TOF;
  boolean FL_Sensor_Status_0;
  boolean FL_Sensor_Status_1;
  boolean FL_Sensor_Status_2;
  boolean FL_Sensor_Status_3;
  boolean FL_Sensor_Status_4;
  boolean FL_Sensor_Status_5;
  boolean FL_Sensor_Status_6;
  boolean FL_Sensor_Status_7;
  uint8 FL_CRC;
  uint8 FL_Ringtime;
};
typedef struct _MsgGr_LIN1_FL_Sensor_Status_ MsgGr_LIN1_FL_Sensor_Status;

struct _MsgGr_LIN1_FCR_Sensor_Status_ {
  uint16 FCR_TOF;
  boolean FCR_Sensor_Status_0;
  boolean FCR_Sensor_Status_1;
  boolean FCR_Sensor_Status_2;
  boolean FCR_Sensor_Status_3;
  boolean FCR_Sensor_Status_4;
  boolean FCR_Sensor_Status_5;
  boolean FCR_Sensor_Status_6;
  boolean FCR_Sensor_Status_7;
  uint8 FCR_CRC;
  uint8 FCR_Ringtime;
};
typedef struct _MsgGr_LIN1_FCR_Sensor_Status_ MsgGr_LIN1_FCR_Sensor_Status;

struct _MsgGr_LIN1_FCL_Sensor_Status_ {
  uint16 FCL_TOF;
  boolean FCL_Sensor_Status_0;
  boolean FCL_Sensor_Status_1;
  boolean FCL_Sensor_Status_2;
  boolean FCL_Sensor_Status_3;
  boolean FCL_Sensor_Status_4;
  boolean FCL_Sensor_Status_5;
  boolean FCL_Sensor_Status_6;
  boolean FCL_Sensor_Status_7;
  uint8 FCL_CRC;
  uint8 FCL_Ringtime;
};
typedef struct _MsgGr_LIN1_FCL_Sensor_Status_ MsgGr_LIN1_FCL_Sensor_Status;

struct _MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11_ {
  uint8 TCU_EngRpmDisSta_Tx_P11;
  uint8 TCU_01_10ms_P11_E2EReserved;
};
typedef struct _MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11_ MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11;

struct _MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11_ {
  uint8 TCU_EngRpmDisSta_Rx_P11;
  uint8 BSD_01_50ms_P11_E2EReserved;
};
typedef struct _MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11_ MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11;

typedef uint8 KeyM_KeyCertNameDataType[14];
typedef const uint8 * KeyM_DataPtr;
typedef uint8 * KeyM_CryptoKeyDataType;
typedef const uint8 * KeyM_ConstCryptoKeyDataType;
struct _IoHwAb_IcuDutyCycleType_ {
  IoHwAb_IcuValueType ActiveTime;
  IoHwAb_IcuValueType PeriodTime;
};
typedef struct _IoHwAb_IcuDutyCycleType_ IoHwAb_IcuDutyCycleType;

typedef uint32 EcuM_WakeupSourceType;
typedef uint8 EcuM_UserType;
typedef uint32 EcuM_TimeType;
typedef uint8 EcuM_StateType;
typedef uint8 EcuM_ShutdownTargetType;
typedef uint16 EcuM_ShutdownModeType;
typedef uint8 EcuM_ShutdownCauseType;
typedef uint8 EcuM_ResetType;
typedef uint8 EcuM_RequestType;
typedef uint16 EcuM_CallerType;
typedef uint8 EcuM_BootTargetType;
typedef unsigned char Dem_PID31valueType[2];
typedef unsigned char Dem_PID21valueType[2];
typedef unsigned char Dem_MaxDataValueType[8];
struct _Dem_J1939DcmLampStatusType_ {
  uint8 LampStatus;
  uint8 FlashLampStatus;
};
typedef struct _Dem_J1939DcmLampStatusType_ Dem_J1939DcmLampStatusType;

typedef unsigned char Dem_DataArrayType_DE_0010[4];
typedef Dem_DataArrayType_DE_0010 Dem_DataType_DE_0010;
typedef unsigned char Dem_DataArrayType_DE_0009[4];
typedef Dem_DataArrayType_DE_0009 Dem_DataType_DE_0009;
typedef unsigned char Dem_DataArrayType_DE_0008[8];
typedef Dem_DataArrayType_DE_0008 Dem_DataType_DE_0008;
typedef unsigned char Dem_DataArrayType_DE_0006[1];
typedef Dem_DataArrayType_DE_0006 Dem_DataType_DE_0006;
typedef unsigned char Dem_DataArrayType_DE_0005[3];
typedef Dem_DataArrayType_DE_0005 Dem_DataType_DE_0005;
typedef unsigned char Dem_DataArrayType_DE_0004[1];
typedef Dem_DataArrayType_DE_0004 Dem_DataType_DE_0004;
typedef unsigned char Dem_DataArrayType_DE_0003[3];
typedef Dem_DataArrayType_DE_0003 Dem_DataType_DE_0003;
typedef unsigned char Dem_DataArrayType_DE_0002[3];
typedef Dem_DataArrayType_DE_0002 Dem_DataType_DE_0002;
typedef unsigned char Dem_DataArrayType_DE_0001[3];
typedef Dem_DataArrayType_DE_0001 Dem_DataType_DE_0001;
typedef uint8 Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignal_PrimitiveType;
typedef Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignal_PrimitiveType Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignalType;
typedef uint8 Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignal_PrimitiveType;
typedef Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignal_PrimitiveType Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignalType;
typedef uint8 Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignal_PrimitiveType;
typedef Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignal_PrimitiveType Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignalType;
typedef uint8 Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignal_PrimitiveType;
typedef Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignal_PrimitiveType Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignalType;
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_SeedArray_L9Type[8];
typedef uint8 Dcm_SecLevelType;
typedef uint8 Dcm_ScalingInfoArray_VehicleSpeedType[9];
typedef uint8 Dcm_ScalingInfoArray_VINDataIdentifierType[2];
typedef uint8 Dcm_ResponseDataArrayType[254];
typedef uint8 Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignal_PrimitiveType;
typedef Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignal_PrimitiveType Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignalType;
typedef uint8 Dcm_RequestDataArrayType[254];
typedef uint8 Dcm_RequestControlServicesOutArray_Tid1Type[1];
typedef uint8 Dcm_RequestControlServicesInArray_Tid1Type[1];
typedef uint8 Dcm_RangeArray_DIDs_0100h_0110hType[30];
typedef uint8 Dcm_ProtocolType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef uint8 Dcm_KeyArray_L9Type[8];
typedef uint8 Dcm_InputOutputControlParameterType;
typedef uint8 Dcm_InfoTypeServicesArray_VINInfoDataType[17];
typedef uint8 Dcm_IOOperationResponseType;
typedef uint8 Dcm_FileAndDirNameType[4];
typedef uint8 Dcm_DidSupportedType;
typedef uint8 Dcm_DataElement_VehicleSpeed_ArrayType[1];
typedef Dcm_DataElement_VehicleSpeed_ArrayType Dcm_DataElement_VehicleSpeedType;
typedef uint8 Dcm_DataElement_VehicleManufacturerECUSoftwareVersionNumber_ArrayType[17];
typedef Dcm_DataElement_VehicleManufacturerECUSoftwareVersionNumber_ArrayType Dcm_DataElement_VehicleManufacturerECUSoftwareVersionNumberType;
typedef uint8 Dcm_DataElement_VINDataIdentifier_ArrayType[17];
typedef Dcm_DataElement_VINDataIdentifier_ArrayType Dcm_DataElement_VINDataIdentifierType;
typedef uint8 Dcm_DataElement_SystemSupplierECUSoftwareNumber_ArrayType[4];
typedef Dcm_DataElement_SystemSupplierECUSoftwareNumber_ArrayType Dcm_DataElement_SystemSupplierECUSoftwareNumberType;
typedef uint8 Dcm_DataElement_SystemSupplierECUHardwareVersionNumber_ArrayType[4];
typedef Dcm_DataElement_SystemSupplierECUHardwareVersionNumber_ArrayType Dcm_DataElement_SystemSupplierECUHardwareVersionNumberType;
typedef uint8 Dcm_DataElement_RPM_ArrayType[2];
typedef Dcm_DataElement_RPM_ArrayType Dcm_DataElement_RPMType;
typedef uint8 Dcm_DataElement_ECT_ArrayType[1];
typedef Dcm_DataElement_ECT_ArrayType Dcm_DataElement_ECTType;
typedef uint8 Dcm_DataElement_BatVolt_ArrayType[1];
typedef Dcm_DataElement_BatVolt_ArrayType Dcm_DataElement_BatVoltType;
typedef uint8 Dcm_DataElement_ActuatorControl_ArrayType[1];
typedef Dcm_DataElement_ActuatorControl_ArrayType Dcm_DataElement_ActuatorControlType;
typedef uint8 Dcm_DataArrayTypeUint8_RPMType[2];
typedef uint8 Dcm_DataArrayTypeUint8_ActuatorControlType[1];
typedef uint8 Dcm_ConfirmationStatusType;
typedef uint8 Dcm_CertExpirationDateInfoType[3];
typedef uint8 Dcm_CertAuthorizationInfoType[4];
struct _Dcm_CertInfoType_ {
  Dcm_CertAuthorizationInfoType authorization;
  Dcm_CertExpirationDateInfoType expirationDate;
};
typedef struct _Dcm_CertInfoType_ Dcm_CertInfoType;

typedef Crypto_VerifyResultType * Csm_VerifyResultPtr;
typedef uint8 Csm_SignatureVerifyDataType_Crypto_SW[256];
typedef uint8 Csm_SignatureVerifyCompareType_Crypto_SW[256];
typedef uint8 Csm_RandomGenerateResultType_Crypto_SW[8];
typedef uint8 Csm_RandomGenerateResultType_Crypto_HSE[16];
typedef uint8 Csm_MacVerifyDataType_Crypto_HSE[326656];
typedef uint8 Csm_MacVerifyCompareType_Crypto_SW[128];
typedef uint8 Csm_MacVerifyCompareType_Crypto_HSE[32];
typedef uint8 Csm_MacGenerateResultType_Crypto_HSE[32];
typedef uint8 Csm_MacGenerateDataType_Crypto_HSE[326656];
typedef uint32 * Csm_LengthPtr;
typedef uint8 Csm_KeyDataType_RandomSeed_L9[4];
typedef uint8 Csm_KeyDataType_Pkcs1_Asims_Public_key[260];
typedef uint8 Csm_KeyDataType_MacVer_AES_CMAC_key[16];
typedef uint8 Csm_KeyDataType_Hash_Dummy_Fota[32];
typedef uint8 Csm_KeyDataType_Decr_AES_CTR_Key1_swlib_Fota[16];
typedef uint8 Csm_KeyDataType_Decr_AES_CTR_Key0_swlib_Fota[16];
typedef uint8 Csm_HashResultType_Crypto_SW[32];
typedef uint8 Csm_HashResultType_Crypto_HSE[32];
typedef uint8 Csm_HashDataType_Crypto_SW[65536];
typedef uint8 Csm_HashDataType_Crypto_HSE[64];
typedef uint8 Csm_EncryptResultType_Crypto_HSE[500];
typedef uint8 Csm_EncryptDataType_Crypto_HSE[500];
typedef uint8 Csm_DecryptResultType_Crypto_HSE[500];
typedef uint8 Csm_DecryptDataType_Crypto_HSE[500];
typedef unsigned char * Csm_DataPtr;
typedef const unsigned char * Csm_ConstDataPtr;
typedef const void * ConstVoidPtr;
typedef ComM_UserHandleType ComM_UserHandleSubArrayType_ComMChannel_LIN2[1];
typedef ComM_UserHandleType ComM_UserHandleSubArrayType_ComMChannel_LIN1[1];
struct _ComM_UserHandleArrayType_ComMChannel_LIN2_ {
  unsigned char numberOfRequesters;
  ComM_UserHandleSubArrayType_ComMChannel_LIN2 handleArray;
};
typedef struct _ComM_UserHandleArrayType_ComMChannel_LIN2_ ComM_UserHandleArrayType_ComMChannel_LIN2;

struct _ComM_UserHandleArrayType_ComMChannel_LIN1_ {
  unsigned char numberOfRequesters;
  ComM_UserHandleSubArrayType_ComMChannel_LIN1 handleArray;
};
typedef struct _ComM_UserHandleArrayType_ComMChannel_LIN1_ ComM_UserHandleArrayType_ComMChannel_LIN1;

typedef uint8 ComM_ModeType;
typedef uint8 ComM_InhibitionStatusType;

/******************************************************************************/
/*                         TransformerError structure                         */
/******************************************************************************/
typedef uint8 Rte_TransformerClass;
typedef uint8 Rte_TransformerErrorCode;

typedef struct STag_Rte_TransformerError
{
  Rte_TransformerErrorCode errorCode;      
  Rte_TransformerClass transformerClass;      
} Rte_TransformerError;

typedef struct
{
  uint16 clientId;      
  uint16 sequenceCounter;      
} Rte_Cs_TransactionHandleType;

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/

