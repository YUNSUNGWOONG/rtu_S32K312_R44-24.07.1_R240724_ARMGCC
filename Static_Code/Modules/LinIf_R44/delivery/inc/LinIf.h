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
**  SRC-MODULE: LinIf.h                                                       **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of extern declaration of APIs, Service-ID's,        **
**              DET error codes of the APIs, type definitions, structure data **
**              types of Lin Interface.                                       **
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
** 1.0.8       04-Dec-2022   KhaLN1          #CP44-1191                       **
** 1.0.7       03-Nov-2022   KhaLN1          #CP44-1100                       **
** 1.0.6       17-Oct-2022   KhaLN1          #CP44-563                        **
** 1.0.5       03-Aug-2022   KhaLN1          #CP44-513                        **
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/

#ifndef LINIF_H
#define LINIF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "LinIf_Cfg.h"             /* Configuration header file */

#if ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && \
  (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_OFF))
#include "LinTrcv.h"               /* Lin Transceiver Header */
#endif

#if (LINTP_SUPPORT == STD_ON)
#include "LinTp.h"                 /* LinTp header file */
#endif

#include "EcuM.h"                  /* EcuM  header */
#include "Lin_GeneralTypes.h"      /* Lin General Types header */
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* @Trace: LinIf_SUD_MACRO_014 */
#define LINIF_ZERO                              ((uint8)0x00U)
#define LINIF_ONE                               ((uint8)0x01U)
#define LINIF_TWO                               ((uint8)0x02U)
#define LINIF_THREE                             ((uint8)0x03U)
#define LINIF_FOUR                              ((uint8)0x04U)
/* #define LINIF_FIVE                              (uint8)0x05 */
#define LINIF_SIX                               ((uint8)0x06U)
#define LINIF_SEVEN                             ((uint8)0x07U)
#define LINIF_EIGHT                             ((uint8)0x08U)
#define LINIF_FALSE                             ((boolean)0x00U)
#define LINIF_TRUE                              ((boolean)0x01U)
#define LINIF_UNINIT                            ((boolean)0x00U)
#define LINIF_INIT                              ((boolean)0x01U)
#define LINIF_INITIAL_VALUE                     ((uint8)0x55U)
/* #define LINIF_CHANNEL_UNINIT                    (uint8)0x00 */
/* Channel Status */
#define LINIF_CHANNEL_OPERATIONAL               ((uint8)0x01U)
#define LINIF_CHANNEL_SLEEP                     ((uint8)0x02U)

#define LINIF_NULL_SCHEDULE                     ((uint8)0x00U)

/*Channel Run Mode*/
#define LINIF_RUN_ONCE                          ((uint8)0x01U)
#define LINIF_RUN_CONTINUOUS                    ((uint8)0x02U)
#define LINIF_CONTINUE_AT_IT_POINT              ((uint8)0x00U)
#define LINIF_START_FROM_BEGINNING              ((uint8)0x01U)

#define LINIF_MAX_BYTE                          ((uint8)0xFFU)
#define LINIF_UNCONDITIONAL                     ((uint8)0x00U)
#define LINIF_SPORADIC                          ((uint8)0x01U)
#define LINIF_EVENT_TRIGGER                     ((uint8)0x02U)
#define LINIF_FIXED_MRF                         ((uint8)0x05U)
#define LINIF_FIXED_SRF                         ((uint8)0x06U)

/* LinIf Collision Status*/
#define LINIF_COLLISION_NOT_OCCURRED            ((uint8)0x00U)
#define LINIF_COLLISION_OCCURRED                ((uint8)0x01U)
#define LINIF_COLLISION_RESOLVED                ((uint8)0x02U)

/*LinIf Request State*/
#define LINIF_CHNL_STARTUP_NORMAL               ((uint8)0x00U)
#define LINIF_SLEEP_REQUESTED                   ((uint8)0x01U)
#define LINIF_SLEEP_REQ_PENDING                 ((uint8)0x02U)
#define LINIF_SLEEP_COMMAND_SENT                ((uint8)0x03U)
#define LINIF_SLEEP_COMMAND_RECEIVED            ((uint8)0x04U)
#define LINIF_WAKEUP_REQUESTED                  ((uint8)0x05U)

/* #define LINIF_CHNL_STARTUP_SLEEP                (uint8)0x01 */
#define LINIF_LINDRV_WAKEUPSOURCE               ((uint8)0x00U)
#define LINIF_LINTRCV_WAKEUPSOURCE              ((uint8)0x01U)
/* Instance identification */
#define LINIF_INSTANCE_ID                       ((uint8)0x00U)
/* Redmien #8274: Change Number to Macro*/
#define LINIF_FRAME_ID_FILTER_MASK              ((uint8)0x3FU)
#define LINIF_PARITY_BIT_P0_MASK                ((uint8)0x40U)
#define LINIF_PARITY_BIT_P1_MASK                ((uint8)0x80U)
#define LINIF_ONE_CHECK                         (0x01)

/* @Trace: LinIf_SUD_MACRO_012 */
/* API service ids */
#define LINIF_INIT_SID                          ((uint8)0x01U)
#define LINIF_GETVERSIONINFO_SID                ((uint8)0x03U)
#define LINIF_TRANSMIT_SID                      ((uint8)0x49U)
#define LINIF_SCHEDULEREQUEST_SID               ((uint8)0x05U)
#define LINIF_GOTOSLEEP_SID                     ((uint8)0x06U)
#define LINIF_WAKEUP_SID                        ((uint8)0x07U)
#define LINIF_SETTRCVMODE_SID                   ((uint8)0x08U)
#define LINIF_GETTRCVMODE_SID                   ((uint8)0x09U)
#define LINIF_GETTRCVWAKEUPREASON_SID           ((uint8)0x0AU)
#define LINIF_SETTRCVWAKEUPMODE_SID             ((uint8)0x0BU)
#define LINIF_CHECKWAKEUP_SID                   ((uint8)0x60U)
#define LINIF_WAKEUPCONFIRMATION_SID            ((uint8)0x61U)
#define LINIF_GETPIDTABLE_SID                   ((uint8)0x72U)
#define LINIF_SETPIDTABLE_SID                   ((uint8)0x73U)
#define LINIF_HEADERINDICATION_SID              ((uint8)0x78U)
#define LINIF_RXINDICATION_SID                  ((uint8)0x79U)
#define LINIF_TXCONFIRMATION_SID                ((uint8)0x7AU)
#define LINIF_LINERRORINDICATION_SID            ((uint8)0x7BU)
#define LINIF_MAINFUNCTION_SID                  ((uint8)0x80U)

/* @Trace: LinIf_SUD_MACRO_016 */
/* DET error codes */
#define LINIF_E_UNINIT                          ((uint8)0x00U)
#define LINIF_E_ALREADY_INITIALIZED             ((uint8)0x10U)
#define LINIF_E_NONEXISTENT_CHANNEL             ((uint8)0x20U)
#define LINIF_E_PARAMETER                       ((uint8)0x30U)
#define LINIF_E_PARAM_POINTER                   ((uint8)0x40U)
#define LINIF_E_SCHEDULE_REQUEST_ERROR          ((uint8)0x51U)
#define LINIF_E_TRCV_INV_CHANNEL                ((uint8)0x52U)
#define LINIF_E_TRCV_INV_MODE                   ((uint8)0x53U)
#define LINIF_E_TRCV_NOT_NORMAL                 ((uint8)0x54U)
#define LINIF_E_PARAM_WAKEUPSOURCE              ((uint8)0x55U)
#define LINIF_E_RESPONSE                        ((uint8)0x60U)
#define LINIF_E_NC_NO_RESPONSE                  ((uint8)0x61U)
/* Redmine 14279: Add DET Code for reporting a failure of Lin Driver regarding
Sleep Register control.*/
#define LINIF_E_DRV_SLEEP_FAILED                ((uint8)0x62U)

#define LINIF_MRF_PID                           ((uint8)0x3CU)
#define LINIF_SRF_PID                           ((uint8)0x3DU)
#define LINIF_MRF_FRAME_LEN											((uint8)0x08U)
#define LINIF_SRF_FRAME_LEN											((uint8)0x08U)

#define LINIF_DROP_REQUEST                      ((uint8)0x01U)

#define LINIF_CF_SIZE                           ((uint8)0x06U)

#define LINIF_BLOCK_WAKEUP_REPETITION_INFINITY	((uint8)0xFFU)

/* Invalid Values */
#define LINIF_TRCV_NOTCONFIGURED                ((uint8)0xFFU)
#define LINIF_TRCV_INVALID_MODE                 ((uint8)0x02U)
#define LINIF_TRCV_INVALID_WAKEUP_MODE          ((uint8)0x02U)
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
#define LINIF_UNUSED(x)           do { \
                                    if((uint32)(x) != (uint32)LINIF_ZERO) {} \
                                  } while(0)

#define LINIF_UNUSED_PTR(x)       do { \
                                    if((x) != NULL_PTR) {} \
                                  } while(0)

/* Macro to copy the frame header parameters into Lin Pdu type structure */
#define LINIF_COPY_HDR_PARAM(LddPduInfo, LpFramePtr) \
  do \
  {                                                  \
    (LddPduInfo).Pid = (LpFramePtr)->ddPid;              \
    (LddPduInfo).Cs =  (LpFramePtr)->ddCs;               \
    (LddPduInfo).Drc = (LpFramePtr)->ddDrc;              \
    (LddPduInfo).Dl =  (LpFramePtr)->ddDl;               \
  } while(0)

#define LINIF_PARITY_BIT_P0_CALCULATE(LucP0, LucFrameId) \
  do \
  {                                                              \
    LucP0 = (((LucFrameId & 0x01) ^ ((LucFrameId & 0x02 ) >> 1) ^ \
         ((LucFrameId & 0x04) >> 2) ^ ((LucFrameId & 0x10) >> 4)) << 6); \
  } while(0)

#define LINIF_PARITY_BIT_P1_CALCULATE(LucP1, LucFrameId) \
  do \
  {                                                                         \
    LucP1 = ((!((( LucFrameId & 0x02 ) >> 1) ^ ((LucFrameId & 0x08) >> 3) ^ \
            ((LucFrameId & 0x10) >> 4) ^ ((LucFrameId & 0x20) >> 5))) << 7); \
  } while(0)
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */    
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: LinIf_SUD_DATATYPE_004 */
/* Enum for LinTp mode */
typedef enum
{
  /* Applicative schedule is selected */
  LINTP_APPLICATIVE_SCHEDULE,
  /* Master request schedule table is selected */
  LINTP_DIAG_REQUEST,
  /* Slave response schedule table is selected */
  LINTP_DIAG_RESPONSE

}LinTp_Mode;

/* @Trace: LinIf_SUD_DATATYPE_001 */
/* LinIf Schedule Handle type */
typedef uint8 LinIf_SchHandleType;

#include "LinIf_PCTypes.h"
/* @Trace: LinIf_SUD_DATATYPE_002 */
typedef struct {
  /* @Trace: LinIf_SUD_CONSTVAR_008 */
  /* Pointer to LinIf Channel Infor*/
  P2CONST(LinIf_ChannelInfo, AUTOMATIC, LINIF_CONST) pChannelInfor;
  /* @Trace: LinIf_SUD_CONSTVAR_009 */
  /* Pointer to LinIf schedule table */
  P2CONST(LinIf_Scheduler, AUTOMATIC, LINIF_CONST) pSchTable;
  /* @Trace: LinIf_SUD_CONSTVAR_010 */
  /* Pointer to LinIf Schuedule Table Entry */
  P2CONST(LinIf_SchEntry, AUTOMATIC, LINIF_CONST) pSchTblEntry;
  /* @Trace: LinIf_SUD_CONSTVAR_011 */
  /* Pointer to LinIf Frame Info*/
  P2CONST(LinIf_FrameInfo, AUTOMATIC, LINIF_CONST) pFrameInfo;
  #if (LINIF_SLAVE_SUPPORT == STD_ON)
  /* @Trace: LinIf_SUD_GLOBALVAR_006 */
  /* Pointer to LinIf Pid Table*/
  P2VAR(uint8, AUTOMATIC, LINIF_DATA) pPidTable;
  /* @Trace: LinIf_SUD_CONSTVAR_012 */
  /* Pointer to LinIf Frame Index Table*/
  P2CONST(uint8, AUTOMATIC, LINIF_CONST) pFrameIdxTable;
  #endif
  /* No of channels configured in this connfiguration */
  uint8 ucNoOfChannels;
  /* Number of Associated Frames */
  uint8 usNoAssociatedFrm;

}LinIf_ConfigType;

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#define LINIF_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, LINIF_CODE) LinIf_Init
  (P2CONST(LinIf_ConfigType, AUTOMATIC, LINIF_APPL_CONST) ConfigPtr);

#if (LINIF_VERSION_INFO_API == STD_ON)
extern FUNC(void, LINIF_CODE) LinIf_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, LINIF_APPL_DATA) versioninfo);
#endif

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_Transmit
  (PduIdType LinTxPduId, P2CONST(PduInfoType, AUTOMATIC,
  LINIF_APPL_CONST) PduInfoPtr);

extern FUNC(void, LINIF_CODE) LinIf_AssociatedPendingMask(PduIdType LddPduId, \
                                                          boolean LbCheckPend);

#if (LINIF_MASTER_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_ScheduleRequest
  (NetworkHandleType Channel, LinIf_SchHandleType ScheduleIndex);
#endif

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_GotoSleep
  (NetworkHandleType Channel);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_Wakeup
  (NetworkHandleType Channel);

#if (LINIF_WAKEUP_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_CheckWakeup
  (EcuM_WakeupSourceType WakeupSource);
#endif

#if(LINIF_TRCV_DRIVER_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_SetTrcvMode
  (NetworkHandleType Channel, LinTrcv_TrcvModeType TransceiverMode);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_GetTrcvMode
  (NetworkHandleType Channel,
  P2VAR(LinTrcv_TrcvModeType, AUTOMATIC, LINIF_APPL_DATA) TransceiverModePtr);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_GetTrcvWakeupReason
  (NetworkHandleType Channel,
  P2VAR(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINIF_APPL_DATA)
  TrcvWuReasonPtr);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_SetTrcvWakeupMode(
  NetworkHandleType Channel, LinTrcv_TrcvWakeupModeType LinTrcvWakeupMode);
#endif
extern FUNC(void, LINIF_CODE) LinIf_WakeupConfirmation(
                                          EcuM_WakeupSourceType WakeupSource);
#if (LINIF_SLAVE_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LINIF_CODE)
      LinIf_HeaderIndication(NetworkHandleType Channel, Lin_PduType* PduPtr);
extern FUNC(void, LINIF_CODE) LinIf_RxIndication
                              (NetworkHandleType Channel, uint8* Lin_SduPtr);
extern FUNC(void, LINIF_CODE) LinIf_TxConfirmation (NetworkHandleType Channel);
extern FUNC(void, LINIF_CODE) LinIf_LinErrorIndication(
                    NetworkHandleType Channel, Lin_SlaveErrorType ErrorStatus);
extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_SetPIDTable(
NetworkHandleType Channel, Lin_FramePidType* PidBuffer, uint8 PidBufferLength);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_GetPIDTable(
NetworkHandleType Channel, Lin_FramePidType* PidBuffer, uint8* PidBufferLength);
#endif
extern FUNC(void, LINIF_CODE) LinIf_MainFunction(NetworkHandleType Channel);
#define LINIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Extern declarations for Global Data                   **
*******************************************************************************/
#define LINIF_START_SEC_DBTOC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(LinIf_ConfigType, LINIF_CONST) LinIf_GaaConfiguration[LINIF_ONE];
#define LINIF_STOP_SEC_DBTOC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif  /* LINIF_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
