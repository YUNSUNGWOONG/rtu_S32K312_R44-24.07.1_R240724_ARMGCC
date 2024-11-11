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
**  INC-MODULE: ComM_PCTypes.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of pre-compile time parameters                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.1.7          31-Jan-2024         MUKim            CP44-3149              **
** 1.1.5          09-Jun-2023         NamNT1           CP44-2206              **
** 1.1.2          31-Oct-2022         NamNT1           CP44-920, CP44-924     **
** 1.1.1          15-Sep-2022         ThuanVT          CP44-782               **
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #27547     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25506,    **
**                                                     #25646                 **
** 1.0.2          20-Dec-2020         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef COMM_PCTYPES_H
#define COMM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: ComM_SUD_DATATYPE_002 */
/* @Trace: SRS_ComM_AR_00254 */
/* @Trace: ComM_SUD_DATATYPE_003 */
#include "ComM_Cfg.h"             /* Module configuration header file*/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
/* @Trace: ComM_SUD_DATATYPE_001 */
/* @Trace: SRS_BSW_00348 SRS_BSW_00357 */
#include "Com.h"                  /* Com Module header file */
#endif
/* @Trace: ComM_SUD_DATATYPE_004 */
/* @Trace: ComM_SUD_DATATYPE_007 */
/* @Trace: SRS_ComM_AR_00204 */
/* @Trace: SRS_ComM_AR_00206 */
#include "ComStack_Types.h"       /* Communication Stack header file */
/* @Trace: ComM_SUD_DATATYPE_012 */
/* @Trace: SRS_ComM_AR_00193 */
/* @Trace: SRS_ComM_AR_00198 */
/* @Trace: ComM_SUD_DATATYPE_013 */
/* @Trace: SRS_ComM_AR_00195 */
/* @Trace: SRS_ComM_AR_00201 */
/* @Trace: ComM_SUD_DATATYPE_014 */
/* @Trace: SRS_ComM_AR_00194 */
/* @Trace: SRS_ComM_AR_00203 */
/* @Trace: SRS_ComM_AR_00209 */
/* @Trace: ComM_SUD_DATATYPE_015 */
/* @Trace: SRS_ComM_AR_00200 */
/* @Trace: SRS_ComM_AR_00203 */
/* @Trace: ComM_SUD_DATATYPE_016 */
/* @Trace: SRS_ComM_AR_00199 */
/* @Trace: SRS_ComM_AR_00200 */
#include "Rte_ComM_Type.h"        /* Rte and ComM types header file */

/*******************************************************************************
**                       Global Data Types                                    **
*******************************************************************************/

/*
 * DET ERRORS
 * This Det error is returned of API service is used without ComM initialized
 */
/* Traceable SWS_ComM_00234, modify value error code */
#ifndef COMM_E_UNINIT
#define COMM_E_UNINIT                         (0x01)
#endif

/* This Det error is returned of API service is used with wrong parameters */
#define COMM_E_WRONG_PARAMETERS               (0x02)

/* Traceable SWS_ComM_00234, add new error code */
/* This Det error is returned of API service is used with a null pointer */
#define COMM_E_PARAM_POINTER                  (0x03)

/* Traceable SWS_ComM_00234, add new error code */
/* This Det error is returned of Initialization failed */
#define COMM_E_INIT_FAILED                    (0x04)

#define COMM_E_WRONG_CHANNEL                  (0x05)

/* Inhibition status Masks */
#define COMM_LIMITCHNTONOCOM_MASK             ((uint8)0x02)
#define COMM_PREVENTWAKEUP_MASK               ((uint8)0x01)

/* Prevent Wakeup Masks*/
#define COMM_PREVENTWAKEUP_MASK_SET           ((uint8)0x01)
#define COMM_PREVENTWAKEUP_MASK_CLR           ((uint8)0xFE)

/* Limit Channel to No Communication Masks*/
#define COMM_LIMITCHANNELTONOCOMM_MASK_SET    ((uint8)0x02)
#define COMM_LIMITCHANNELTONOCOMM_MASK_CLR    ((uint8)0xFD)

/* Network Mode Indications */
#define COMM_NMSTART_IND                      (0x01)
#define COMM_NMMODE_IND                       (0x02)
#define COMM_BUSSLEEPMODE_IND                 (0x03)
#define COMM_PREPBUSSLEEPMODE_IND             (0x04)
#define COMM_NMRST_IND                        (0x05)

/* Nm Variants */
#define COMM_NMVARIANT_NONE                   (0x00)
#define COMM_NMVARIANT_LIGHT                  (0x01)
#define COMM_NMVARIANT_FULL                   (0x02)
#define COMM_NMVARIANT_PASSIVE                (0x03)
#define COMM_NMVARIANT_LINSLAVE               (0x04)

/*Flexray Bus type */
#define COMM_FLEXRAY                          (0x02)

/* Internal Bus Type */
#define COMM_INTERNAL                         (0x03)

/* Lin Bus type */
#define COMM_LIN                              (0x04)

/* Lin Bus type */
#define COMM_ETH                              (0x01)

#define COMM_NUMBER_OF_BUS_TYPES              (0x06)

/* Number of Bus Type */

/* Macros used to set, check masked values of various global variables */
#define COMM_ZERO                             (0x00u)
#define COMM_ONE                              ((uint8)0x01)
#define COMM_TWO                              ((uint8)0x02)
#define COMM_THREE                            ((uint8)0x03)
#define COMM_FOUR                             ((uint8)0x04)
#define COMM_EIGHT                            ((uint8)0x08)

/* Inhibition Status range for Set Ecu Group Classification */
#define COMM_INHIBITION_RANGE                 (0x03)

/* Macro to know if user request for mode change is accepted */
#define COMM_FULLCOMMREQ_ACCPTD               (COMM_ONE)
#define COMM_NOCOMMREQ_ACCPTD                 (COMM_TWO)

/* True / False / Invalid */
#define COMM_TRUE                             (COMM_ONE)
#define COMM_FALSE                            (COMM_ZERO)
#define COMM_INVALID_CHANNEL                  (COMM_TOTAL_CHANNELS)
#define COMM_INVALID_USER                     (COMM_TOTAL_USERS)
#define COMM_INVALID_PNC                      (COMM_TOTAL_PNCS)
#define COMM_INVALID_TX_SIGNAL_ID             (COMM_TOTAL_TX_SIGNALS)

/* Not used User Id */
#define COMM_NOT_USED_USER_ID                 ((uint8) 255)

#define COMM_NOT_USED_CHANNEL_ID              255

/* Maximum Inhibit counter value */
#define COMM_INHIBITCNT_MAX                   ((uint16) 65535)

/* Maximum ComM_ReqedComModeCnt value */
#define COMM_REQEDCOMMODECNT_MAX              ((uint8) 255)

/* Maximum ComM_InhibitionReqst value */
#define COMM_INHIBITIONREQST_MAX              ((uint8) 255)

/* Maximum ComM_ChannelsFullComMode value */
#define COMM_CHANNELSFULLCOMMODE_MAX          ((uint16) 256)

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))

/*PNC Gateway */
#define COMM_ACTIVE_GW                        (0X00)
#define COMM_PASSIVE_GW                       (0X01)

/*Type Of Signal*/
#define COMM_EIRA                             (0x00)
#define COMM_ERA                              (0x01)

/*Types Of PNC User Requests*/
#define PNC_USER_NO_COMM                      (0x00)
#define PNC_USER_FULL_COMM                    (0x01)

/*Type Of Signal Direction*/
#define COMM_RX                               (0x00)
#define COMM_TX                               (0x01)

/* Maximum byte index Com PN info */
#define PNC_COM_MAX_INFO                      (0x3F)

#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/* To avoid unused variable warning */
#define COMM_UNUSED(x)                        ((void)(x)) /* polyspace MISRA2012:D4.9 [Not a defect:Low] "This function macro defined to avoid unused variable warning. Belong to scope coding rule" */

/* @Trace: ComM_SUD_DATATYPE_019 */
typedef struct
{
  #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
  /* Inhibit counter ----> ComMNoCom */
  uint16 ComMFullComInhibitCounter;
  #endif

  /* Ecugroup Type  ComMEcuGroupClassification */
  ComM_InhibitionStatusType ComMEcuInhibition;
} ComM_DataType;

/*--------------------Structure for PNC states------------------------------- */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
/* @Trace: ComM_SUD_DATATYPE_018 */
/* @Trace: SRS_ComM_AR_00244 SRS_ComM_AR_00245 SRS_ComM_AR_00246
 * SRS_ComM_AR_00247 SRS_ComM_AR_00248
 */

/* Struct containing data information PNC */
typedef struct
{
  /*
   *--------------------ComMPncComSignal--------------------------------------
   * This structure element gives the number of Com Signals linked to the Pnc
   */
  uint16 NoOfComSignal;

  /* Com Signals index for the current PNC*/
  uint16 ComSignalIndex;

  /* PNC id */
  PNCHandleType PncId;
  /*
   *--------------For Reference to [ ComMusers ]----------------------------
   * This structure element gives the number of users linked to the Pnc
   */
  uint8 UserCount;

  /* User start index for the current channel */
  uint8 UserIndex;

  /*
   *--------------For Reference to [ ComMChannel ]----------------------------
   * This structure element contains the number of channels for the user.
   */
  uint8 NoOfChannelPnc;

  /* This structure element conatains index of ChannelIndexArray array, contains channel index */
  uint8 ChannelPncIndex;
} ComM_PncsType;

/*--------------------Structure for ComMPncComSignal------------------------- */
/* @Trace: ComM_SUD_DATATYPE_020 */
/* @Trace: SRS_ComM_AR_00012 SRS_ComM_AR_00249 SRS_ComM_AR_00250
 * SRS_ComM_AR_00251 SRS_ComM_AR_00252 SRS_ComM_AR_00253
 */
typedef struct
{
  /* Reference to [ ComSignal ] */
  Com_SignalIdType ComMComSigId;

  /* Reference to [ ComMChannel ] */
  #if (COMM_PNC_GW_ENABLED == STD_ON)
  NetworkHandleType ComMChannelId;
  #endif

  /* ComMPncComSignalDirection */
  uint8 ComMPncComSigDir;

  /*ComMPncComSignalKind*/
  uint8 ComMPncComSignalKind;

  /* vector offset reference to BusSM module */
  uint8 ComMPncVectorOffset;
} ComM_ComSignalType;
#endif

/*--------------------------------------------------------------------------- */
#if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
/* typedef for handling function pointer for requesting communication mode from
 *   corresponding SM */
typedef P2FUNC(Std_ReturnType, COMM_APPL_CODE, ComM_SMReqComModeFuncPtr)
  (NetworkHandleType ChannelId, ComM_ModeType ComMode);

/* typedef for handling function pointer to get current communication mode from
 *   corresponding SM*/
typedef P2FUNC(Std_ReturnType, COMM_APPL_CODE, ComM_SMGetCurComModeFuncPtr)
  (NetworkHandleType ChannelId, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA)
  ComModePtr);

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing pointer to function for SM Get current mode API */
/* @Trace: ComM_SUD_GLOBALVAR_005 */
extern CONST(ComM_SMGetCurComModeFuncPtr, COMM_CONST)
                              ComM_SMGetCurComModeFun[COMM_SM_GET_CUR_COM_MODE];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing pointer to function for SM request mode API */
/* @Trace: ComM_SUD_GLOBALVAR_006 */
extern CONST(ComM_SMReqComModeFuncPtr, COMM_CONST)
                                     ComM_SMReqComModeFun[COMM_SM_REQ_COM_MODE];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */

#if (COMM_USER_SEQUENTIAL == STD_OFF)
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array used for mapping User Id to be sequential */
/* @Trace: ComM_SUD_GLOBALVAR_008 */
extern CONST(ComM_UserHandleType, COMM_CONST)
                                  ComM_UserMapArray[COMM_MAX_USERID + COMM_ONE];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array used for mapping Channel Id to be sequential */
/* @Trace: ComM_SUD_GLOBALVAR_009 */
extern CONST(NetworkHandleType, COMM_CONST)
                            ComM_ChannelMapArray[COMM_MAX_CHANNELID + COMM_ONE];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (COMM_DIRECT_CHANNEL == STD_ON)
#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Channel to user map array : In channels, Channel Index --> User ID */
/* @Trace: ComM_SUD_GLOBALVAR_010 */
extern CONST(ComM_UserHandleType, COMM_CONST)
                        ComM_ChannelToUserMapping[COMM_NUMBER_OF_USERTOCHANNEL];
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if (COMM_DIRECT_CHANNEL == STD_ON)
#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Channel indices array : In Users, Direct Channel Index --> Channel Index*/
/* @Trace: ComM_SUD_GLOBALVAR_007 */
/* @Trace: SRS_ComM_AR_00057 */
extern CONST(uint8, COMM_CONST) ComM_ChnInxArr[COMM_NUMBER_OF_USERTOCHANNEL];
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

/*--------------------PNC is implemented-------------------------------------*/
#if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))

/*------------PNC ComSignal related information to be stored------------------*/
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing ComSignal data structure information */
/* @Trace: ComM_SUD_GLOBALVAR_004 */
extern CONST(ComM_ComSignalType, COMM_CONST)
ComM_ComSignal[COMM_TOTAL_SIGNALS];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((COMM_FULL_NMVARIANT_SUPPORT  == STD_ON) && \
                                      (COMM_LIGHT_NMVARIANT_SUPPORT  == STD_ON))
#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Array used to mapping managing channel  sequence */
/* @Trace: ComM_SUD_GLOBALVAR_015 */
extern CONST(uint8, COMM_CONST)
ComM_ManagingMapArray[COMM_MANAGING_MAP_ARRAY + COMM_ONE];
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif /* End of #if ((COMM_PNC_SUPPORT, == STD_ON) &&\
  * (COMM_PNC_ENABLE == STD_ON)) */
  
#if(COMM_BUSLOAD_DETECTING == STD_ON)
#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Array containing contrller of channel information */
extern CONST(uint8, COMM_CONST) ComM_ChannelCtrlMapping[COMM_MAX_CHANNELID + COMM_ONE];
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
/* ====================== Implement for Pre-Compile ==========================*/

/* Struct containing data information Channel */
/* @Trace: ComM_SUD_DATATYPE_021 */
/* @Trace: SRS_ComM_AR_00211 SRS_ComM_AR_00212 SRS_ComM_AR_00170
 * SRS_ComM_AR_00213 SRS_ComM_AR_00214 SRS_ComM_AR_00215 SRS_ComM_AR_00216
 * SRS_ComM_AR_00218 SRS_ComM_AR_00219 SRS_ComM_AR_00220 SRS_ComM_AR_00221
 * SRS_ComM_AR_00222 SRS_ComM_AR_00225 SRS_ComM_AR_00232 SRS_ComM_AR_00236
 * SRS_ComM_AR_00240 SRS_ComM_AR_00241 SRS_ComM_AR_00242 SRS_ComM_AR_00243
 * SRS_ComM_AR_00257 SRS_ComM_AR_00258
 */

typedef struct
{
  /*
   * This structure element defines the timeout after state ready sleep is
   * left.
   * --> ComMNmLightTimeout*/
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  ComM_TimeType NmLightTimeout;
  #endif

  /*
   * This structure element contains the minimum time duration in
   * full communication mode.
   * Derivation: ComMTMinFullComModeDuration/ComMMainFunctionPeriod
   */
  ComM_TimeType MinFullComMode;

  /*
   * Time in seconds the pnc state machine shall wait in sub-state
   * COMM_PNC_PREPARE_SLEEP
   * Derivation: ComMPncPrepareSleepTimer/ComMMainFunctionPeriod
   */
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
  ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  uint16 PncPrepareSleepTimer;
  #endif

  /*
   * This structure element contains the channel identification number of the
   * channel.
   * --> ComMChannelId
   */
  NetworkHandleType ChannelId;

  /*
   * This variable contains the bus type of the channel.
   * 0 - CAN, 1 - Ethernet, 2 - FlexRay, 4 - LIN
   * --> ComMBusType
   */
  uint8 BusType;

  /*
   * This variable contains the Gateway behaviour of a ComMChannel..
   * 0 - Active, 1 - Passive, 2 - Invalid
   * --> ComMPncGatewayType
   */
  #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
                                                (COMM_PNC_GW_ENABLED == STD_ON))
  uint8 PncGatewayType;
  #endif

  /*
   * This structure element defines the functionality of the network
   * management.
   * --> ComMNmVariant
   */
  uint8 NmVariant;

  /*
   *This structure element defines bit 0 defines ComMNoWakeup inhibition, not
   * allowing ECU to wake up the channel, bit 1 defines
   * ComMNoCom, not allowing channel to switch to Silent or Full communication
   * --> ComMGlobalNvmBlockDescriptor
   */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
                                       (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  uint8 ComMInhibition;
  #endif

  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /*
   *-----------------------ComMUserPerChannel --------------------------------
   * This should only be present if it is not a part of any PNC Cluster
   */

  /*
   *This stucture element contains the starting index to ChannelToUserMapping
   * array pointing to the user of this channel
   */
  uint8 ChannelUserIndex;

  /*
   * This structure element contains the number of users associated with a
   * particular channel
   */
  uint8 ChannelUserCount;

  /*-------------------------------------------------------------------------*/
  #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /*
   *This stucture element contains the starting index to ChannelToPncMapping
   * array pointing to the user of this channel
   */
  PNCHandleType PncIndex;

  /* This structure element contains the number of Pnc associated with a
   * particular channel */
  uint16 PncCount;
  #endif

  /****************************** ComM channel manager ************************/
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) && \
                                       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON))
  /* Channel Id of managing channel if this channel is managed channel */
  uint8 IdOfManagingChnl;

    /* number of managed */
  uint8 NoOfManagedChnl;

  /* The index of every ComM managing channel in the mapping array */
  uint8 ManagingIndex;
  #endif

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /*
   * Every time Nm shall be called using the API Nm_NetworkRequest when, FULL
   * Communication is requested due to a change in the PNC state machine to
   * COMM_PNC_REQUESTED.
   * -->  ComMPncNmRequest
   */
  boolean PncNmRequest;

  /*
   * boolean parameter that defines whether Channel is part of PNC cluster
   * ComMChannelPerPnc: If the Channel is refered by any PNC : TRUE
   */
  boolean ChannelPnc;
  #endif

  /*
   * This structure element defines if the optional SenderReceiver Port of
   * Interface ComM_CurrentChannelRequest will be provided for this channel.
   * --> ComMFullCommRequestNotificationEnabled
   */
  #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
                                          (COMM_DIRECT_USER_MAPPING == STD_OFF))
  boolean FullCommReqNotifEn;
  #endif

  /*
   * This structure element defines if the NoWakeUp inhibition state of the
   * channel shall be stored in the block: ComMGlobalNvmBlockDescriptor.
   * --> ComMGlobalNvmBlockDescriptor
   */
  #if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) && \
      ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) || \
                                      (COMM_MODE_LIMITATION_ENABLED == STD_ON)))
  boolean NoWakeUpNvmStorage;
  #endif

  /****************************** ComM channel manager ************************/
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) && \
                                       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON))
  /* Channel is managed channel */
  boolean ManagedChnl;

  /* Channel is managing channel */
  boolean ManagingChnl;
  #endif

} ComM_ChannelsType;

/* Struct containing data information User */
/* @Trace: ComM_SUD_DATATYPE_022 */
/* @Trace: SRS_ComM_AR_00254 SRS_ComM_AR_00255 SRS_ComM_AR_00256 */
typedef struct
{
  /*
   * This structure element contains the user identification number of the
   * corresponding user.
   */
  ComM_UserHandleType UserId;

  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /*
   * The channel is implicit already referenced by the PNC ---
   * Avoid redundant configuration
   */

  /*
   * This structure element contains the number of channels for the users not
   * using PNC
   */
  uint8 NoOfDirectChannels;

  /* This structure element contains index of DirectChannelIndexArray array. */
  uint8 DirectChannelIndex;

  /*------------------------------------------------------------------------*/
  #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /*
   *This structure element gives the number of users linked to the PNC when 
   *all related features are supported.
   */
  uint16 NoOfPncs;

  /* User start index for the current channel */
  PNCHandleType PncUserIndex;
  #endif

} ComM_UsersType;

#if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Channel to PNC map array for PNC associated with the channel */
/* @Trace: ComM_SUD_GLOBALVAR_021 */
/* @Trace: SRS_ComM_AR_00055 */
extern CONST(ComM_UserHandleType, COMM_CONST)
                                ComM_PncToUserMapping[COMM_PNC_TO_USER_MAPPING];
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"

#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Channel indices array : In Pnc, Channel Index --> Channel ID */
/* @Trace: ComM_SUD_GLOBALVAR_011 */
/* @Trace: SRS_ComM_AR_00244 */
extern CONST(NetworkHandleType, COMM_CONST)
                                ComM_ChnPncInxArr[COMM_CHANNEL_PNC_INDEX_ARRAY];
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"

#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* Pnc indices array : In Users, Index --> PNC Index*/
/* @Trace: ComM_SUD_GLOBALVAR_013 */
/* @Trace: SRS_ComM_AR_00055 */
extern CONST(PNCHandleType, COMM_CONST) ComM_PncUserInxArr[COMM_PNC_USER_INDEX_ARRRAY];
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"

#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* Channel to PNC map array : In Channels, Channel Index --> PNC Index, contains PNC ID */
/* @Trace: ComM_SUD_GLOBALVAR_012 */
/* @Trace: SRS_ComM_AR_00057 */
extern CONST(PNCHandleType, COMM_CONST)
                          ComM_ChannelToPncMapping[COMM_CHANNEL_TO_PNC_MAPPING];
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"

#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* Array to get Pnc sequence, contains PNC ID*/
/* @Trace: ComM_SUD_GLOBALVAR_014 */
/* @Trace: SRS_ComM_AR_00019 */
extern CONST(PNCHandleType, COMM_CONST) ComM_PncMapArray[COMM_PNC_MAP_ARRAY];
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"
#endif /* End #if PNC support */

#else /* end if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
/* ====================== Implement for Post-Build ===========================*/

/* Struct containing data information Channel */
/* @Trace: ComM_SUD_DATATYPE_021 */
/* @Trace: SRS_ComM_AR_00211 SRS_ComM_AR_00212 SRS_ComM_AR_00170
 * SRS_ComM_AR_00213 SRS_ComM_AR_00214 SRS_ComM_AR_00215 SRS_ComM_AR_00216
 * SRS_ComM_AR_00218 SRS_ComM_AR_00219 SRS_ComM_AR_00220 SRS_ComM_AR_00221
 * SRS_ComM_AR_00222 SRS_ComM_AR_00225 SRS_ComM_AR_00232 SRS_ComM_AR_00236
 * SRS_ComM_AR_00240 SRS_ComM_AR_00241 SRS_ComM_AR_00242 SRS_ComM_AR_00243
 * SRS_ComM_AR_00257 SRS_ComM_AR_00258
 */
typedef struct
{
  /*
   * This structure element defines the timeout after state ready sleep is
   * left.
   * --> ComMNmLightTimeout*/
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  ComM_TimeType NmLightTimeout;
  #endif

  /*
   * This structure element contains the minimum time duration in
   * full communication mode.
   * Derivation: ComMTMinFullComModeDuration/ComMMainFunctionPeriod
   */
  ComM_TimeType MinFullComMode;

  /*
   * Time in seconds the pnc state machine shall wait in sub-state
   * COMM_PNC_PREPARE_SLEEP
   * Derivation: ComMPncPrepareSleepTimer/ComMMainFunctionPeriod
   */
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
  ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  uint16 PncPrepareSleepTimer;
  #endif

  /*
   * This structure element contains the channel identification number of the
   * channel.
   * --> ComMChannelId
   */
  NetworkHandleType ChannelId;

  /*
   * This variable contains the bus type of the channel.
   * 0 - CAN, 1 - Ethernet, 2 - FlexRay, 4 - LIN
   * --> ComMBusType
   */
  uint8 BusType;

  /*
   * This variable contains the Gateway behaviour of a ComMChannel..
   * 0 - Active, 1 - Passive, 2 - Invalid
   * --> ComMPncGatewayType
   */
  #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
                                                (COMM_PNC_GW_ENABLED == STD_ON))
  uint8 PncGatewayType;
  #endif

  /*
   * This structure element defines the functionality of the network
   * management.
   * --> ComMNmVariant
   */
  uint8 NmVariant;

  /*
   *This structure element defines bit 0 defines ComMNoWakeup inhibition, not
   * allowing ECU to wake up the channel, bit 1 defines
   * ComMNoCom, not allowing channel to switch to Silent or Full communication
   * --> ComMGlobalNvmBlockDescriptor
   */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
                                       (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  uint8 ComMInhibition;
  #endif

  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /*
   *-----------------------ComMUserPerChannel --------------------------------
   * This should only be present if it is not a part of any PNC Cluster
   */

  /*
   *This stucture element contains the starting index to ChannelToUserMapping
   * array pointing to the user of this channel
   */
  uint8 ChannelUserIndex;

  /*
   * This structure element contains the number of users associated with a
   * particular channel
   */
  uint8 ChannelUserCount;

  /*-------------------------------------------------------------------------*/
  #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

  /****************************** ComM channel manager ************************/
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) && \
                                       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON))
  /* Channel Id of managing channel if this channel is managed channel */
  uint8 IdOfManagingChnl;

    /* number of managed */
  uint8 NoOfManagedChnl;

  /* The index of every ComM managing channel in the mapping array */
  uint8 ManagingIndex;
  #endif

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
  /*
   * Every time Nm shall be called using the API Nm_NetworkRequest when, FULL
   * Communication is requested due to a change in the PNC state machine to
   * COMM_PNC_REQUESTED.
   * -->  ComMPncNmRequest
   */
  boolean PncNmRequest;

  /*
   * boolean parameter that defines whether Channel is part of PNC cluster
   * ComMChannelPerPnc: If the Channel is refered by any PNC : TRUE
   */
  /* boolean ChannelPnc; */
  #endif

  /*
   * This structure element defines if the optional SenderReceiver Port of
   * Interface ComM_CurrentChannelRequest will be provided for this channel.
   * --> ComMFullCommRequestNotificationEnabled
   */
  #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
                                          (COMM_DIRECT_USER_MAPPING == STD_OFF))
  boolean FullCommReqNotifEn;
  #endif

  /*
   * This structure element defines if the NoWakeUp inhibition state of the
   * channel shall be stored in the block: ComMGlobalNvmBlockDescriptor.
   * --> ComMGlobalNvmBlockDescriptor
   */
  #if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) && \
      ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) || \
                                      (COMM_MODE_LIMITATION_ENABLED == STD_ON)))
  boolean NoWakeUpNvmStorage;
  #endif

  /****************************** ComM channel manager ************************/
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) && \
                                       (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON))
  /* Channel is managed channel */
  boolean ManagedChnl;

  /* Channel is managing channel */
  boolean ManagingChnl;
  #endif

} ComM_ChannelsType;

/* Struct containing data information User */
/* @Trace: ComM_SUD_DATATYPE_022 */
/* @Trace: SRS_ComM_AR_00254 SRS_ComM_AR_00255 SRS_ComM_AR_00256 */
typedef struct
{
  /*
   * This structure element contains the user identification number of the
   * corresponding user.
   */
  ComM_UserHandleType UserId;

  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /*
   * The channel is implicit already referenced by the PNC ---
   * Avoid redundant configuration
   */

  /*
   * This structure element contains the number of channels for the users not
   * using PNC
   */
  uint8 NoOfDirectChannels;

  /* This structure element contains index of DirectChannelIndexArray array. */
  uint8 DirectChannelIndex;

  /*------------------------------------------------------------------------*/
  #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

} ComM_UsersType;

/* Struct data for User dependcy to PNC */
/* @Trace: ComM_SUD_DATATYPE_023 */
/* @Trace: SRS_ComM_AR_00244 */
typedef struct
{
  /* This structure element gives the number of users linked to the PNC */
  uint16 NoOfPncs;

  /* User start index for the current channel */
  PNCHandleType PncUserIndex;
} ComM_UserPNCRelatedType;

/* Struct data for Channel dependcy to PNC */
/* @Trace: ComM_SUD_DATATYPE_024 */
/* @Trace: SRS_ComM_AR_00244 */
typedef struct
{
  /*
   *This stucture element contains the starting index to ChannelToPncMapping
   * array pointing to the user of this channel
   */
  PNCHandleType PncIndex;

  /* This structure element contains the number of Pnc associated with a
   * particular channel */
  uint16 PncCount;

  /*
   * boolean parameter that defines whether Channel is part of PNC cluster
   * ComMChannelPerPnc: If the Channel is refered by any PNC : TRUE
   */
  boolean ChannelPnc;
} ComM_ChannelsPNCRelatedType;

/* @Trace: SWS_ComM_00162 */
/* This type contains the implementation-specific post build
    configuration structure */
typedef struct
{
  /* Struct containing data PNC information */
  P2CONST(ComM_PncsType, AUTOMATIC, COMM_CONST) pComM_Pncs;
  /* Struct containing data User dependcy to PNC */
  P2CONST(ComM_UserPNCRelatedType, AUTOMATIC, COMM_CONST) pComM_UserPNCRelated;
  /* Struct containing data Channel dependcy to PNC */
  P2CONST(ComM_ChannelsPNCRelatedType, AUTOMATIC, COMM_CONST)
                                                   pComM_ChannelsPNCRelatedType;
  /* Array containing data Pnc mapping to User */
  P2CONST(ComM_UserHandleType, AUTOMATIC, COMM_CONST) pComM_PncToUserMapping;
  /* Array containing data Pnc mapping to Channel index */
  P2CONST(NetworkHandleType, AUTOMATIC, COMM_CONST) pComM_ChnPncInxArr;
  /* Array containing data Pnc mapping to User index */
  P2CONST(PNCHandleType, AUTOMATIC, COMM_CONST) pComM_PncUserInxArr;
    /* Array containing data Pnc mapping to Channel */
  P2CONST(PNCHandleType, AUTOMATIC, COMM_CONST) pComM_ChannelToPncMapping;
  /* Array containing data Pnc map index */
  P2CONST(PNCHandleType, AUTOMATIC, COMM_CONST) pComM_PncMapArray;
  /* Flash containing information Pnc enabled */
  boolean bPncEnabledFlash;
} ComM_ConfigType;
/* ========================================================================== */
#endif /* End of if COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON */

/* ============================== Common struct ============================= */
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing channel data structure information */
/* @Trace: ComM_SUD_GLOBALVAR_001 */
/* @Trace: SRS_ComM_AR_00054 SRS_ComM_AR_00171 */
extern CONST(ComM_ChannelsType, COMM_CONST) ComM_Channels[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing user data structure information */
/* @Trace: ComM_SUD_GLOBALVAR_002 */
/* @Trace: SRS_ModeMgm_09133 */
extern CONST(ComM_UsersType, COMM_CONST) ComM_Users[COMM_TOTAL_USERS];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) && \
    ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON)))
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing PNC data structure information */
/* @Trace: ComM_SUD_GLOBALVAR_003 */
/* @Trace: SRS_ComM_AR_00244 */
extern CONST(ComM_PncsType, COMM_CONST) ComM_Pncs[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* This array maps Tx Signal to ComM_SignalTx array index */
/* @Trace: ComM_SUD_GLOBALVAR_068 */
/* @Trace: SRS_ComM_AR_00244 */
extern CONST(uint16, COMM_CONST) ComM_SignalTxMapArray[COMM_TOTAL_SIGNALS];
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"
#endif
/* ========================================================================== */

/* This variable contains the default values is to be stored from NvM */
/*
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(ComM_DataType, COMM_CONST) ComM_ConstData;
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) &&\
  (COMM_DIRECT_USER_MAPPING == STD_OFF))
extern CONST(ComM_UserHandleArrayType, COMM_CONST)
ComM_ConstFullComReq[COMM_TOTAL_CHANNELS];
#endif

#if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
extern CONST(uint8, COMM_CONST)
ComM_ConstChannelInhibitStatus[COMM_TOTAL_CHANNELS];
#endif
*/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COMM_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

