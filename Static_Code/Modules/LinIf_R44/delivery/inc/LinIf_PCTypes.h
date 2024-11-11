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
**  SRC-MODULE: LinIf_PCTypes.h                                               **
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
** Revision    Date          By              Description                      **
********************************************************************************
** 1.0.15      01-Mar-2024   JH Jang         #CP44-5060, #CP44-5062           **
** 1.0.8       04-Dec-2022   KhaLN1          #CP44-1191                       **
** 1.0.6       17-Oct-2022   KhaLN1          #CP44-563, #CP44-884             **
** 1.0.5       03-Aug-2022   KhaLN1          #CP44-513                        **
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/

#ifndef LINIF_PCTYPES_H
#define LINIF_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Lin_GeneralTypes.h"      /* Lin General Types header */
#include "EcuM.h"                /* EcuM  header */
#if (LINTP_SUPPORT == STD_ON)
#include "LinTp_PCTypes.h"      /* LinTp Post Build Time Types header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: LinIf_SUD_MACRO_001 */
/*
 * AUTOSAR specification version information
 */
#define LINIF_PCTYPES_AR_RELEASE_MAJOR_VERSION  (LINIF_AR_RELEASE_MAJOR_VERSION)
#define LINIF_PCTYPES_AR_RELEASE_MINOR_VERSION  (LINIF_AR_RELEASE_MINOR_VERSION)
#define LINIF_PCTYPES_AR_RELEASE_REVISION_VERSION \
  (LINIF_AR_RELEASE_REVISION_VERSION)

/*
 * File version information
 */
#define LINIF_PCTYPES_SW_MAJOR_VERSION    (LINIF_SW_MAJOR_VERSION)
#define LINIF_PCTYPES_SW_MINOR_VERSION    (LINIF_SW_MINOR_VERSION)
#define LINIF_PCTYPES_SW_PATCH_VERSION    (LINIF_SW_PATCH_VERSION)

#define LINIF_LIN_AR44_RELEASE_MAJOR_VERSION   4
#define LINIF_LIN_AR44_RELEASE_MINOR_VERSION   4
#define LINIF_LIN_AR47_RELEASE_MINOR_VERSION   7

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* To solve the gap between AR44 and the others */
#if ((LINIF_LIN_H_AR_RELEASE_MAJOR_VERSION == LINIF_LIN_AR44_RELEASE_MAJOR_VERSION )\
  && ((LINIF_LIN_H_AR_RELEASE_MINOR_VERSION == LINIF_LIN_AR44_RELEASE_MINOR_VERSION)\
  || (LINIF_LIN_H_AR_RELEASE_MINOR_VERSION == LINIF_LIN_AR47_RELEASE_MINOR_VERSION)))
#define LINIF_FRAMERESPONSE_TX      LIN_FRAMERESPONSE_TX 
#define LINIF_FRAMERESPONSE_RX      LIN_FRAMERESPONSE_RX
#define LINIF_FRAMERESPONSE_IGNORE  LIN_FRAMERESPONSE_IGNORE
#else
#define LINIF_FRAMERESPONSE_TX      LIN_MASTER_RESPONSE
#define LINIF_FRAMERESPONSE_RX      LIN_SLAVE_RESPONSE
#define LINIF_FRAMERESPONSE_IGNORE  LIN_SLAVE_TO_SLAVE
#endif /* ((LINIF_LIN_H_AR_RELEASE_MAJOR_VERSION == LINIF_LIN_AR44_RELEASE_MAJOR_VERSION )\
        && (LINIF_LIN_H_AR_RELEASE_MINOR_VERSION == LINIF_LIN_AR44_RELEASE_MINOR_VERSION )) */

/* @Trace: LinIf_SUD_DATATYPE_006 */
/* Type for Lin If Upper Layer */
typedef enum
{
  /* Upper layer module is CDD */
  LINIF_UL_MODULE_CDD,
  /* Upper layer module is LinSm */
  LINIF_UL_MODULE_LIN_SM,
  /* Upper layer module is PDUR */
  LINIF_UL_MODULE_PDUR,
  /* Upper layer module is not defined */
  LINIF_UL_MODULE_NOT_DEFINED
} LinIf_ULModule;

/* @Trace: LinIf_SUD_DATATYPE_007 */
/* Type for Lin If node */
typedef enum
{
  /* Master node */
  LINIF_MASTER_NODE,
  /* Slave node */
  LINIF_SLAVE_NODE
} LinIf_NodeType;

/* @Trace: LinIf_SUD_DATATYPE_008 */
/* Type for Lin Protocol Version */
typedef enum
{
  /* ISO 17987 */
  LINIF_ISO17987,
  /* LIN 1.3 */
  LINIF_LIN13,
  /* LIN 2.0 */
  LINIF_LIN20,
  /* LIN 2.1 */
  LINIF_LIN21,
  /* LIN 2.2 */
  LINIF_LIN22
} LinIf_LinProtocolVersion;

/* @Trace: LinIf_SUD_DATATYPE_005 */
/* Type for pLinNodeConfiguration in case master node */
typedef uint32 LinIf_JitterType;

/* @Trace: LinIf_SUD_DATATYPE_010 */
/* Type for pLinSlaveNodeCfg in case slave node */
typedef struct {
  /* Node Supplier Id */
  uint16 usSupplierId;
  /* Node Function Id */
  uint16 usFunctionId;
  /* Node Variant Id */
  uint8 ucVariantId;
  /* Node NAD Initial Value */
  uint8 ucInitNAD;
  /* Node Configured NAD */
  uint8 ucConfiguredNAD;
  /* Number of main function period */
  uint32 ulNasTimeout;
} LinIf_NodeConfig;

/* @Trace: LinIf_SUD_DATATYPE_011 */
/* Type for pLinNodeConfiguration in case slave node */
typedef struct {
    const void * pLinSlaveNodeCfg;
} LinIf_SlaveNodeInfo;


typedef signed int LinIf_UnderlyingType;

/* @Trace: LinIf_SUD_DATATYPE_009 */
typedef enum {
    LINIF_UNCONDITIONAL_FRAME = 0,
    LINIF_MRF_FRAME,
    LINIF_SRF_FRAME,
    LINIF_EVENT_TRIGGERED_FRAME,
    LINIF_SPORADIC_FRAME,
    LINIF_ASSIGN_FRAME,
    LINIF_UNASSIGN_FRAME,
    LINIF_ASSIGN_NAD_FRAME,
    LINIF_FREE_FRAME,
    LINIF_CONDITIONAL_FRAME,
    LINIF_SAVE_CONFIGURATION_FRAME,
    LINIF_ASSIGN_FRAME_ID_RANGE_FRAME,
    LINIF_FIXED_MRF_FRAME,
    LINIF_FIXED_SRF_FRAME
} LinIf_FrameType;

/* @Trace: LinIf_SUD_DATATYPE_012 */
/* Structure for frame information */
typedef struct
{
  /* Frame PID, from parameter LinIfPid?present in LinIfFrame?container.*/
  Lin_FramePidType ddPid;
  /* Frame CheckSum model,
   * parameter LinIfChecksumType?present in LinIfFrame?container.
  */
  Lin_FrameCsModelType ddCs;
  /* Frame direction,
   * choice container LinIfPduDirection?present in LinIfFrame?container
   * LinIfTxPdu the value will be 0
   * LinIfRxPdu the value will be 1
   * LinIfSlaveToSlavePdu the value will be 2
  */
  Lin_FrameResponseType ddDrc;
  /* Frame data length,
   * configuration parameter LinIfLength?present in LinIfFrame?container.
  */
  Lin_FrameDlType ddDl;
  /* Local handle Id of Pdu which is defined by LinIf
   * In case of LinIfTxPdu?it is generated from
   * the LinIfTxPduRef?present in LinIfPduDirection?and
   * in case of LinIfRxPdu?it is generated from
   * the LinIfRxPduRef?present in LinIfPduDirection?
  */
  PduIdType ddLocalHandleId;
  /* 0-UCF, 1-Sporadic, 2-EvtTrig, 3-MRF, 4-SRF,
   * 5-FixedMRF, 6-FixedSRF */
  LinIf_FrameType ddFrameType;
  /*Frame Index */
  uint8 ucFrameIndex;
}LinIf_FrameInfo;

/* @Trace: LinIf_SUD_DATATYPE_013 */
/* Structure for Sporadic/Event Triggered Frame's Associated UCF information */
typedef struct
{
  /* @Trace: LinIf_SUD_CONSTVAR_001 */
  /* Pointer to frame info structure */
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST)pAssociatedFrame;
  /* @Trace: LinIf_SUD_GLOBALVAR_001 */
  /* Pointer to RAM bit contains pending status information */
  P2VAR(uint8, AUTOMATIC, LINIF_DATA)pPendingSts;
  /* Sporadic frame PduId, from the parameter
   * LinIfTxPduId?of LinIfTxPdu?container present in LinIfPduDirection?
  */
  /* PduIdType ddSporPduId; To be changed to GaaSpoPduId[]
   * Channel Id, channel index value of LinIfChannel?container
   * It is an index not the configuration parameter
  */
  uint8 ucChannelId;
  /* Pending status mask,
   * This value is based on the bit position allocated in the pPendingSts.
   * For that position the bit value will be set as ??and
   * for other positions it will be set as ??
  */
  uint8 ucPendStsMask;
  /* Priority, priority value of unconditional frame in Sporadic frame slot
  */
  uint8 ddPriority;
}LinIf_AssociatedFrame;

/* @Trace: LinIf_SUD_DATATYPE_014 */
/* Structure for schedule table entry information */
typedef struct
{
  /* @Trace: LinIf_SUD_CONSTVAR_002 */
  /* Pointer to frame info structure */
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST)pFramePtr;
  /* For sporadic or fixed MRF this is an index
   * This parameter gives the index value of sporadic (or) fixed MRF frames
   * For sporadic - gives the index of LinIf_AssociatedFramePtrArry?structured array
   * For fixed MRF - it gives the index of FixedMrfArray?
  */
  uint8 ddFrameIndex;

  /* Incase of Sporadic this shows the number of associated frames in an
   * LinIfEntry?container, It can be generated by referring to LinIfFrameRef?
   * in LinIfEntry?container
  */
  uint8 ddNoOfFrames;
  /* Time delay for next header transmission (in terms of LinIfTimeBase's) */
  uint16 usDelayCount;
}LinIf_SchEntry;

/* @Trace: LinIf_SUD_DATATYPE_015 */
/* Structure for schedule table information */
typedef struct
{
  /* Pointer to first schedule entry structure */
  uint16 usSchFirstEntry;
  /* 1-RUN_ONCE, 2-RUN_CONTINUOUS */
  uint8 ucScheduleType;
  /* Number of schedule entries in the schedule table */
  uint8 ucNoOfSchEntries;
  /* mode of the schedule table :
  0-LINTP_APPLICATIVE_SCHEDULE, 1-LINTP_DIAG_REQUEST, 2-LINTP_DIAG_RESPONSE */
  #if(LINTP_SUPPORT == STD_ON)
  LinTp_Mode ucSchMode;
  #endif
  /* Resume Position: 0-CONTINUE_AT_IT_POINT, 1-START_FROM_BEGINNING*/
  boolean blResumePosition;
}LinIf_Scheduler;

/* @Trace: LinIf_SUD_DATATYPE_016 */
/* Structure for LINIF Channel RAM data */
typedef struct
{
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  /* The present Scheduler ID */
	uint8 ddActivSchId;
  /* The pending Scheduler ID */
	uint8 ddPendingId;
  /* The Completed Scheduler ID */
	uint8 ddCompltdSchId;
  #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
  /* To store the Active Schedule Table Id if the Collision is occured for
   * Event triggered frame.
  */
	uint8 ddPendingSchIdEvt;
  #endif
  #endif
  /* Frame delay counter, it should reach '0' to send next LIN frame */
  uint16 usDelayCounter;
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
  /* Schedule entry number, to restore the execution incase if the
   * Collision is occured for Event triggered frame.
  */
  uint8 ucNoOfEntriesLeftAsEvt;
  #endif
  /* Schedule entry number, to restore the execution incase if the
   * resume position is configured as CONTINUE_AT_IT_POINT
  */
  uint8 ucNoOfEntriesLeft;
  /* Current schedule entry number in the current schedule */
  uint8 ucSchEntryNum;
  /* Temporary storage of Current schedule entry number */
  uint8 ucTempEntryNum;
  /* Frame index of the transmitted frame */
  uint8 ucPrevFrameIndex;
  /* Frame index of the transmitted frame */
  uint8 ucPrevAssociatedFrameIndex;

  /* For Wakeup Confirmation count */
  uint8 ucWakeupConfirmCount;
  #if(LINIF_EVTTRIGGER_FRAMES == STD_ON)
  /* For knowing whether Collision occured */
  uint8 ucCollisionStatusFlag;
  #endif
  #endif
  /* '0' sleep not requested, '1' sleep requested but not yet sent
  * '2' sleep command sent, '3' wakeup requested before checking the
  * sleep command status */
  uint8 ucSleepRequested;
  /* Wake up flag */
  boolean blWakeupStatus;
  /* Channel status */
  uint8 ucChannelSts;
  /* '0': succeed to send wakeup signal, '1': failed to send wakeup signal */
  uint8 ucWakeupSignalSent;
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  /* Pid of active Frame */
  uint8 ucActivePid;
  /* Tx Requyest Pending flag */
  boolean blTxRequestPending;
  /* Rx Requyest Pending flag */
  boolean blRxRequestPending;
  /* Counter to count the number of wake-up sent */
  uint8 ucNumberWakeupSignalSent;
  /* Counter to count the number of block wake-up */
  uint8 ucNumberBlockWakeup;
  /* Counter to delay between each block wake-up */
  uint32 ulCounterDelayBlockWakeup;
  /* Counter to delay between each wake-up signal*/
  uint32 ulCounterDelayWakeupSignalSent;
  #endif
}LinIf_ChannelRamData;

#if (LINIF_SLAVE_SUPPORT == STD_ON)
/* @Trace: LinIf_SUD_DATATYPE_017 */
/* Structure for LINIF Channel RAM data */
typedef struct STag_LinIf_FrameRamData
{
  /* @Trace: LinIf_SUD_GLOBALVAR_002 */
  /* Pid List ascending corresponding to the parameter LinIfFrameIndex */
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) pPidTable;
  /* @Trace: LinIf_SUD_CONSTVAR_003 */
  /* FrameInfo List ascending corresponding to the parameter LinIfFrameIndex */
  P2CONST(uint8, AUTOMATIC, LINIF_DATA) pFrameIndexTable;
}LinIf_FrameRamData;
#endif
/* @Trace: LinIf_SUD_DATATYPE_018 */
/* Structure for LIN Interface Channel information */
typedef struct
{
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  /* Pointer to first scheduler structure */
  uint8 ddFirstScheduler;
  #if (LINIF_FIXEDMRF_FRAMES == STD_ON)
  /* @Trace: LinIf_SUD_CONSTVAR_005 */
  /* Pointer to first fixed MRF structure */
  P2CONST(uint8, AUTOMATIC, LINIF_CONST)pFirstFixedMrf;
  #endif
  #endif
  #if ((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON))
  /* @Trace: LinIf_SUD_CONSTVAR_006 */
  /* Pointer to first associated frame pointer */
  P2CONST(LinIf_AssociatedFrame, AUTOMATIC, LINIF_CONST) pFistAssociatedFrmPtr;
  /* No of Associated Frame in the channel */
  uint16 usNoAssociatedFrm;
  #endif
  /* @Trace: LinIf_SUD_GLOBALVAR_003 */
  /* Pointer to channel RAM data */
  P2VAR(LinIf_ChannelRamData, AUTOMATIC, LINIF_DATA)pChannelRamData;
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  /* @Trace: LinIf_SUD_CONSTVAR_004 LinIf_SUD_GLOBALVAR_004 */
  /* Pointer to channel RAM data */
  P2VAR(LinIf_FrameRamData, AUTOMATIC, LINIF_DATA)pFrameRamData;
  #endif
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  /* @Trace: LinIf_SUD_GLOBALVAR_005 */
  /* Pointer to RAM byte contains scheduler Id */
  P2VAR(uint8, AUTOMATIC, LINIF_DATA)pSchId;
  /* Maximum number of schedules for the channel */
  uint8 ddMaxSchs;
  #endif
  /* Time required for 174 bits */
  uint8 ucMaxFrameDelay;
  /* Node Type */
  LinIf_NodeType ddNodeType;
  #if (LINIF_MASTER_SUPPORT == STD_ON)
  /* Index of Master Jitter Value Array */
  LinIf_JitterType ddJitterIdx;
  #endif

  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  /* @Trace: LinIf_SUD_CONSTVAR_007 */
  /* Point to Slave Config Pointer */
  P2CONST(LinIf_NodeConfig, AUTOMATIC, LINIF_CONST) pSlaveCfg;
  /* Bus Idle Timeout */
  uint16 usBusIdleTimeout;
  /* Index of Pid Table */
  uint8 ucPidTableIdx;
  /* Length of Pid Table */
  uint8 ucLenOfPidTable;
  /* Lin Protocol Version */
  LinIf_LinProtocolVersion ddLinProtocol;
  /* Counter to delay between each block wake-up */
  uint32 ulCounterDelayBlockWakeup;
  /* Counter to delay between each wake-up signal*/
  uint32 ulCounterDelayWakeupSignalSent;
  #endif
  #if (LINIF_ERR_NOTIFICATION_SUPPORT == STD_ON)
  /* Pointer to Error notification function defined in RTE */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinErrNotiFunc)\
        (uint8 channelid, uint8 errcode, uint8 schEntryNum, uint8 frameId);
  #endif
  #if (LINIF_AS_NOTIFICATION_SUPPORT == STD_ON)
  /* Pointer to scheduling notification function defined in RTE */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinASNotiFunc)\
        (uint8 channelId, uint8 schId, uint8 schEntryNum, uint8 frameId);
  #endif
}LinIf_ChannelInfo;

/* @Trace: LinIf_SUD_DATATYPE_019 */
/* Structure for LIN Interface Channel information Link time Parameters */
typedef struct
{
  /* Driver reference channel Id */
  uint8 ucDrvChannelId;
  #if (LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
  /* Transceiver Driver reference channel Id */
  uint8 ucTrcvDrvChannelId;
  #endif

  #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
  /* Driver structure index for the channel */
  uint8 ucDriverIndex;
  #endif
  #if (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
  /* Driver structure index for the channel */
  uint8 ucTrcvDriverIndex;
  #endif
  #if (LINIF_CDD_SUPPORT == STD_ON)
    /* Target Index for SchReqConf */
  uint8 ucSchReqConfIndex;
  /* Target Index for GoToSleepConf */
  uint8 ucGoToSleepConfIndex;
  /* Target Index for WakeupConf */
  uint8 ucWakeupConfIndex;
  #endif
  /*ComM Network Handle Id */
  NetworkHandleType ddComMNwHndlId;
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  /*Com Signal Handle Id */
  NetworkHandleType ddComSigHndId;
  #endif
}LinIf_LtChannelInfo;

 #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
/* @Trace: LinIf_SUD_DATATYPE_020 */
/* Structure for Lin Driver APIs */
typedef struct
{
  /* Function pointer for Lin_SendHeader */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinSendFrame)(const uint8 Channel,
	CONSTP2CONST(Lin_PduType, AUTOMATIC, LINIF_APPL_DATA) PduInfoPtr);

  /* Function pointer for Lin_GoToSleep */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinGoToSleep)(const uint8 Channel);

  /* Function pointer for Lin_Wakeup */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinWakeup)(const uint8 Channel);

  /* Function pointer for Lin_WakeupInternal */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinWakeupInternal)(const uint8 Channel);

  /* Function pointer for Lin_GetStatus */
  /* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
  P2FUNC(Lin_StatusType, LINIF_APPL_CODE, pLinGetStatus)(const uint8 Channel,
    CONSTP2VAR(P2VAR(uint8, AUTOMATIC, LINIF_DATA), AUTOMATIC,
    LINIF_APPL_DATA) LinSduPtr);
  /* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */    

  /* Function pointer for Lin_CheckWakeup */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinCheckWakeup)(const uint8 Channel);

  /* Function pointer for Lin_GoToSleepInternal */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinGoToSleepInternal)(const uint8 Channel);

}LinIf_DrvApis;
  #endif

 #if (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
/* @Trace: LinIf_SUD_DATATYPE_021 */
/* Structure for Lin Transceiver Driver APIs */
typedef struct STag_LinIf_TrcvDrvApis
{
  /* Function pointer for LinTrcv_GetBusWuReason */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pGetBusWuReason)
    (uint8 LinNetwork,
    P2VAR(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINIF_APPL_DATA) Reason);

  /* Function pointer for LinTrcv_SetWakeupMode */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pSetWakeupMode)
    (uint8 LinNetwork, LinTrcv_TrcvWakeupModeType LinTrcvWakeupMode);

  /* Function pointer for LinTrcv_GetOpMode */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pGetOpMode)(uint8 LinNetwork,
    P2VAR(LinTrcv_TrcvModeType, AUTOMATIC, LINIF_APPL_DATA) OpMode);

  /* Function pointer for LinTrcv_SetOpMode */
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pSetOpMode)(uint8 LinNetwork,
    LinTrcv_TrcvModeType OpMode);

  /* Function pointer for LinTrcv_CheckWakeup*/
  P2FUNC(Std_ReturnType, LINIF_APPL_CODE, pLinTrcvCheckWakeup)
  (uint8 LinNetwork);

}LinIf_TrcvDrvApis;
 #endif

#if (LINIF_WAKEUP_SUPPORT == STD_ON)
/* @Trace: LinIf_SUD_DATATYPE_022 */
/* Structure for wakeup source information */
typedef struct
{
  /* LinIf channel where wakeup detected */
  uint8 ucChannelId;
  /* Wakeup event */
  EcuM_WakeupSourceType ddWakeupEvent;
  /* LINIF_LINDRV_WAKEUPSOURCE, LINIF_LINTRCV_WAKEUPSOURCE */
  uint8 ucWakeupSource;
}LinIf_WakeupSource;
#endif

#if (LINIF_CDD_SUPPORT == STD_ON)
/* Function pointer for ScheduleRequest Confirmation functions */
typedef P2FUNC(void, LINIF_APPL_CODE, LinIf_SchReqConfFun)
  (NetworkHandleType network, LinIf_SchHandleType schedule);
/* Function pointer for GoToSleep Confirmation functions */
typedef P2FUNC(void, LINIF_APPL_CODE, LinIf_GoToSleepConfFun)
  (NetworkHandleType channel, boolean success);
/* Function pointer for Wakeup Confirmation functions */
typedef P2FUNC(void, LINIF_APPL_CODE, LinIf_WakeupConfFun)
  (NetworkHandleType channel, boolean success);
/* Function pointer for LinIf TriggerTransmit functions */
typedef P2FUNC(Std_ReturnType, LINIF_APPL_CODE, LinIf_TriggerTransmitFun)
  (PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, LINIF_APPL_DATA) PduInfoPtr);
/* Function pointer for LinIf TxConfirmation functions */
typedef P2FUNC(void, LINIF_APPL_CODE, LinIf_TxConfirmationFun)
  (PduIdType TxPduId);
/* Function pointer for LinIf RxIndication functions */
typedef P2FUNC(Std_ReturnType, LINIF_APPL_CODE, LinIf_RxIndicationFun)
  (PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, LINIF_APPL_DATA) PduInfoPtr);
/* Function pointer for LinIf Rx Indication functions */
typedef P2FUNC(void, LINIF_APPL_CODE, LinIf_RxIndFun)
  (PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, LINIF_APPL_DATA) PduInfoPtr);
#endif

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
  /* Array contains all Channels information */

extern CONST(LinIf_ChannelInfo, LINIF_CONST) LinIf_GaaChannelInfo[LINIF_IF_CHANNELS];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains all schedule tables information */

extern CONST(LinIf_Scheduler, LINIF_CONST) LinIf_GaaScheduler[LINIF_MAX_SCHEDULE_IDX];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains all schedule table entries information */

extern CONST(LinIf_SchEntry, LINIF_CONST) LinIf_GaaSchEntry[LINIF_SCH_ENTRY_ARR_SIZE];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains all Frames Information */

extern CONST(LinIf_FrameInfo, LINIF_CONST) LinIf_GaaFrameInfo[LINIF_NUMBER_LIN_FRAME];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Global array for LIN Driver APIs  */

extern CONST(LinIf_DrvApis, LINIF_CONST) LinIf_GaaDriverApis[LINIF_NUMBER_LIN_DRIVER];

#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif  /* #if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_ON) */

#if (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_ON)
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for LIN Trcv Driver APIs  */

extern CONST(LinIf_TrcvDrvApis, LINIF_CONST) LinIf_GaaTrcvDriverApis[LINIF_NO_OF_LINTRCVDRV];

#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif  /* #if (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORTED == STD_ON) */

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains mapping information to ComMChannel */

extern CONST(uint8, LINIF_CONST) LinIf_GaaComMChannelMap[LINIF_MAX_COMM_IDX];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_8
#include "MemMap.h"
/* Array contains channel of LinIf */
extern CONST(uint8, LINIF_CONST) LinIf_GaaComMChannel[LINIF_IF_CHANNELS];
#define LINIF_STOP_SEC_CONST_8
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Link-Time Array contains the information of Channel */

extern CONST(LinIf_LtChannelInfo, LINIF_CONST) LinIf_GaaLtChannelInfo[LINIF_IF_CHANNELS];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CONST_8
#include "MemMap.h"
/* Global Variable contains the Frame ID mapping infor */
extern CONST(uint8, LINIF_CONST) LinIf_GaaFrameIdMapping[LINIF_IF_CHANNELS][8];
#define LINIF_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if (LINIF_CDD_SUPPORT == STD_ON)
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains the function pointer of Schedule Request Confirmation */
extern CONST(LinIf_SchReqConfFun, LINIF_CONST) LinIf_GaaSchReqConfFun[LINIF_NUMBER_SCHEDULE_REQUEST_CONFIRMATION_FUNCTION];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains the function pointer of Go To Sleep Confirmation */
extern CONST(LinIf_WakeupConfFun, LINIF_CONST) LinIf_GaaGoToSleepConfFun[LINIF_NUMBER_GO_TO_SLEEP_CONFIRMATION_FUNCTION];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains the function pointer of Wakeup Confirmation */
extern CONST(LinIf_WakeupConfFun, LINIF_CONST) LinIf_GaaWakeupConfFun[LINIF_NUMBER_WAKE_UP_CONFIRMATION_FUNCTION];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains the function pointer of Trigger Transmit */
extern CONST(LinIf_TriggerTransmitFun, LINIF_CONST)
                                            LinIf_GaaTriggerTransmitFun[LINIF_NUMBER_TRIGGER_TRANSMIT_FUNCTION];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains the function pointer of Tx Confirmation */
extern CONST(LinIf_TxConfirmationFun, LINIF_CONST) LinIf_GaaTxConfirmationFun[LINIF_NUMBER_TX_CONFIRMATION_FUNCTION];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array contains the function pointer of Rx Indication */
extern CONST(LinIf_RxIndFun, LINIF_CONST) LinIf_GaaRxIndFun[LINIF_NUMBER_RX_INDICATION_FUNCTION];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((LINIF_WAKEUP_SUPPORT == STD_ON) && (LINIF_NO_OF_WAKEUP_SOURCES > 0))
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for wakeup sources */

extern CONST(LinIf_WakeupSource, LINIF_CONST) LinIf_GaaWakeupSource[LINIF_NO_OF_WAKEUP_SOURCES];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if((LINIF_SPORADIC_FRAMES == STD_ON) || (LINIF_EVTTRIGGER_FRAMES == STD_ON))
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for Sporadic Frame */

extern CONST(LinIf_AssociatedFrame, LINIF_CONST) LinIf_GaaAssociatedFrame[LINIF_NUMBER_ASSOCIATED_FRAME];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for the PduId of the Transmit Frames */
extern CONST(uint16, LINIF_CONST) LinIf_GaaGlobalHandleId[LINIF_NUMBER_LIN_FRAME];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (LINIF_EVTTRIGGER_FRAMES == STD_ON)
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for the index of Resolved Schedule Table */
extern CONST(uint8, LINIF_CONST) LinIf_GaaResSchTableIdx[LINIF_SCH_ENTRY_ARR_SIZE];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (LINIF_SLAVE_SUPPORT == STD_ON)
#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for the Slave Node Configuration */
extern CONST(LinIf_NodeConfig, LINIF_CONST) LinIf_GaaSlaveCfg[LINIF_NUMBER_SLAVE_CFG];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define LINIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint8, LINIF_DATA) LinIf_GaaBitData[LINIF_SIZE_BIT_DATA_ARRAY];
#define LINIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINIF_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
extern VAR (LinIf_ChannelRamData, LINIF_DATA) LinIf_GaaChannelRamData[LINIF_IF_CHANNELS];
#define LINIF_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"

#define LINIF_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
extern VAR (LinIf_SchHandleType, LINIF_DATA) LinIf_GaaSchData[LINIF_IF_CHANNELS];
#define LINIF_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* LINIF_PCTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
