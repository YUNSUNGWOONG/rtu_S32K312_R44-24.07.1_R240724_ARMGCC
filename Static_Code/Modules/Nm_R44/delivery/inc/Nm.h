/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
** SRC-MODULE: Nm.h                                                           **
**                                                                            **
** TARGET    : All                                                            **
**                                                                            **
** PRODUCT   : AUTOSAR Nm Module                                              **
**                                                                            **
** PURPOSE   : Provision of Nm Module header                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.0.3      16-Dec-2022   NamNT1         BUGCLASSIC-385, CP44-1325          **
** 1.0.2      31-Oct-2022   NamNT1         CP44-925                           **
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.1      16-Mar-2022   LiemNT4        Implement support Post-Build       **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

#ifndef NM_H
#define NM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00348 SRS_BSW_00353 SRS_BSW_00357 SRS_BSW_00384 */
/* Inclusion for AUTOSAR standard types */
/* @Trace: Nm_SUD_DATATYPE_001 Nm_SUD_DATATYPE_002 */
#include "Std_Types.h"

/* @Trace: SRS_BSW_00301 */
/* Inclustion for NetworkHandleType */
/* @Trace: Nm_SUD_DATATYPE_004 */
#include "ComStack_Types.h"

/* Inclusion for Nm_StateType, Nm_ModeType, NmBusType */
#include "NmStack_Types.h"

#include "Nm_IntTypes.h"
/* @Trace: SRS_BSW_00348 SRS_BSW_00353 SRS_BSW_00357 SRS_BSW_00384
 * SRS_Nm_02515 SRS_Nm_02536
 */
/* Inclusion for Communication Manager callback functions */
#include "ComM_Nm.h"

/* @Trace: SRS_BSW_00159 SRS_BSW_00345 SRS_BSW_00419 */
/* Inclusion for pre-processor switches */
#include "Nm_Cfg.h"

/* @Trace: SRS_BSW_00301 SRS_Nm_00150 SRS_Nm_02515 */
#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
/* Inclusion for using Com_SignalIdType and Com_SendSignal() */
/* @Trace: Nm_SUD_DATATYPE_003 */
#include "Com.h"
#endif

/* @Trace: SRS_BSW_00424 SRS_BSW_00425 */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* Inclusion of MainFunction and Data Protection APIs */
#include "SchM_Nm.h"
#endif

#if (NM_VARIANT_POSTBUID_SUPPORT == STD_ON)
#include "Nm_PBcfg.h"
#endif  /* (NM_VARIANT_POSTBUID_SUPPORT == STD_ON) */
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#if (NM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: Nm_SUD_MACRO_012 */
  /* Error codes for API used without Nm interface initialization */
  #define NM_E_UNINIT                           ((uint8)0x00)
  /* Error codes for API called with wrong parameter but not NULL pointer */
  #define NM_E_INVALID_CHANNEL                  ((uint8)0x01)
  /* Error codes for API called with a NULL pointer */
  #define NM_E_PARAM_POINTER                    ((uint8)0x02)

  /* Macro for Instance Id to be used for reporting DET error */
  #define NM_INSTANCE_ID                        ((uint8)0x00)

  /* API Service Ids */
  /* @Trace: Nm_SUD_MACRO_009 */
  #define NM_INIT_SID                           ((uint8)0x00)
  #define NM_PASSIVESTARTUP_SID                 ((uint8)0x01)
  #define NM_NETWORKREQUEST_SID                 ((uint8)0x02)
  #define NM_NETWORKRELEASE_SID                 ((uint8)0x03)
  #define NM_DISABLECOMMUNICATION_SID           ((uint8)0x04)
  #define NM_ENABLECOMMUNICATION_SID            ((uint8)0x05)
  #define NM_SETUSERDATA_SID                    ((uint8)0x06)
  #define NM_GETUSERDATA_SID                    ((uint8)0x07)
  #define NM_GETPDUDATA_SID                     ((uint8)0x08)
  #define NM_REPEATMESSAGEREQUEST_SID           ((uint8)0x09)
  #define NM_GETNODEIDENTIFIER_SID              ((uint8)0x0a)
  #define NM_GETLOCALNODEIDENTIFIER_SID         ((uint8)0x0b)
  #define NM_CHECKREMOTESLEEPINDICATION_SID     ((uint8)0x0d)
  #define NM_GETSTATE_SID                       ((uint8)0x0e)
  #define NM_GETVERSIONINFO_SID                 ((uint8)0x0f)
  #define NM_NETWORKSTARTINDICATION_SID         ((uint8)0x11)
  #define NM_NETWORKMODE_SID                    ((uint8)0x12)
  #define NM_BUSSLEEPMODE_SID                   ((uint8)0x14)
  #define NM_PREPAREBUSSLEEPMODE_SID            ((uint8)0x13)
  #define NM_SYNCHRONIZEMODE_SID                ((uint8)0x21)
  #define NM_REMOTESLEEPINDICATION_SID          ((uint8)0x17)
  #define NM_REMOTESLEEPCANCELLATION_SID        ((uint8)0x18)
  #define NM_SYNCHRONIZATIONPOINT_SID           ((uint8)0x19)
  #define NM_COORDREADYTOSLEEPINDICATION_SID    ((uint8)0x1e)
  #define NM_COORDREADYTOSLEEPCANCELLATION_SID  ((uint8)0x1f)
  #define NM_PDURXINDICATION_SID                ((uint8)0x15)
  #define NM_STATECHANGENOTIFICATION_SID        ((uint8)0x16)
  #define NM_REPEATMESSAGEINDICATION_SID        ((uint8)0x1a)
  #define NM_TXTIMEOUTEXCEPTION_SID             ((uint8)0x1b)
  #define NM_CARWAKEUPINDICATION_SID            ((uint8)0x1d)
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00344
 * SRS_BSW_00358 SRS_BSW_00405 SRS_BSW_00414
 * SRS_Nm_00046 SRS_Nm_00051 SRS_Nm_00151
 * SRS_Nm_02513 SRS_Nm_02536 SRS_Nm_00047
 * SRS_Nm_00048 SRS_Nm_02512 SRS_Nm_02503
 * SRS_Nm_02504 SRS_Nm_02506 SRS_Nm_00153
 * SRS_Nm_02505 SRS_Nm_02508 SRS_Nm_00050
 * SRS_BSW_00003 SRS_BSW_00407 SRS_BSW_00482
 * SRS_BSW_00359 SRS_Nm_AR_00003 SRS_Nm_00052
 * SRS_Nm_02509 SRS_Nm_02516 SRS_Nm_02535
 */
#define NM_START_SEC_CODE
#include "MemMap.h"

/* Standard services */
extern FUNC(void, NM_CODE) Nm_Init(
  P2CONST(Nm_ConfigType, AUTOMATIC, NM_APPL_DATA) ConfigPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_PassiveStartUp(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequest(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRelease(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

/* Communication Control services */
#if (NM_COM_CONTROL_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, NM_CODE) Nm_DisableCommunication(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_EnableCommunication(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);
#endif

/* Extra services */
#if (NM_USER_DATA_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, NM_CODE) Nm_SetUserData(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2CONST(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetUserData(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr);
#endif

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetPduData(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmPduData);

extern FUNC(Std_ReturnType, NM_CODE) Nm_RepeatMessageRequest(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetNodeIdentifier(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetLocalNodeIdentifier(
  VAR(NetworkHandleType, NM_APPL_DATA) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

#if (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, NM_CODE) Nm_CheckRemoteSleepIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
  P2VAR(boolean, AUTOMATIC, NM_APPL_DATA) nmRemoteSleepIndPtr);
#endif

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetState(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
  P2VAR(Nm_StateType, AUTOMATIC, NM_APPL_DATA) nmStatePtr,
  P2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_DATA) nmModePtr);

#if (NM_VERSION_INFO_API == STD_ON)
extern FUNC(void, NM_CODE) Nm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, NM_APPL_DATA) NmVerInfoPtr);
#endif

/* Standard Callback notifications */
extern FUNC(void, NM_CODE) Nm_NetworkStartIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_NetworkMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_BusSleepMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_PrepareBusSleepMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_SynchronizeMode(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

#if (NM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_RemoteSleepIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_RemoteSleepCancellation(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);
#endif

extern FUNC(void, NM_CODE) Nm_SynchronizationPoint(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

#if (NM_COORDINATOR_SYNC_SUPPORT == STD_ON)
extern FUNC(void, NM_CODE) Nm_CoordReadyToSleepIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmChannelHandle);

extern FUNC(void, NM_CODE) Nm_CoordReadyToSleepCancellation(
  VAR(NetworkHandleType, NM_APPL_DATA) nmChannelHandle);
#endif

/* Extra Callback notifications */
#if (NM_PDU_RX_INDICATION_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_PduRxIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);
#endif

#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_StateChangeNotification(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle,
  VAR(Nm_StateType, NM_APPL_DATA) nmPreviousState,
  VAR(Nm_StateType, NM_APPL_DATA) nmCurrentState);
#endif

extern FUNC(void, NM_CODE) Nm_RepeatMessageIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_TxTimeoutException(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);

#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_CarWakeUpIndication(
  VAR(NetworkHandleType, NM_APPL_DATA) nmNetworkHandle);
#endif

#define NM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* NM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
