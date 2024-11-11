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
**  SRC-MODULE: ComM.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
********************************************************************************
** 1.1.7          31-Jan-2024         NamNT1           CP44-3037              **
** 1.1.5          09-Jun-2022         NamNT1           CP44-2062              **
** 1.1.2          31-Oct-2022         NamNT1           CP44-920, CP44-924     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25506     **
** 1.0.2          20-Dec-2020         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef COMM_H
#define COMM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
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

/* @Trace: ComM_SUD_DATATYPE_002 */
/* @Trace: SRS_ComM_AR_00254 */
/* @Trace: ComM_SUD_DATATYPE_003 */
#include "ComM_Cfg.h"             /* Module configuration header file*/

/* @Trace: ComM_SUD_DATATYPE_005 */
/* @Trace: ComM_SUD_DATATYPE_006 */

#if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) &&\
    (COMM_NVMSTORE_CHANNELS != 0x00))
#include "Rte_NvM_Type.h"            /* NvM types header file */
#endif

/* @Trace: ComM_SUD_MACRO_004  */
/* @Trace: ComM_SUD_MACRO_006  */
#include "ComM_PCTypes.h"

#if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#include "ComM_PBcfg.h"             /* Module configuration header file for PB*/
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Instance ID for DET report error */
#define COMM_INSTANCE_ID                   0x00

/* Service ID for ComM_COMCbk */
#define COMM_COMCBK_SID                    0x36

/* Service ID for Main Function */
#define COMM_MAINFUNCTION_SID              0x60

/* Service ID for ComM_Init */
#define COMM_INIT_SID                      0x01

/* Service ID for ComM_DeInit */
#define COMM_DEINIT_SID                    0x02

/* Service ID for ComM_GetStatus */
#define COMM_GETSTATUS_SID                 0x03

/* Service ID for ComM_GetInhibitionStatus */
#define COMM_GETINHIBITIONSTATUS_SID       0x04

/* Service ID for ComM_RequestComMode */
#define COMM_REQUESTCOMMODE_SID            0x05

/* Service ID for ComM_GetMaxComMode */
#define COMM_GETMAXCOMMODE_SID             0x06

/* Service ID for ComM_GetRequestedComMode */
#define COMM_GETREQUESTEDCOMMODE_SID       0x07

/* Service ID for ComM_GetCurrentComMode */
#define COMM_GETCURRENTCOMMODE_SID         0x08

/* Service ID for ComM_PreventWakeUp */
#define COMM_PREVENTWAKEUP_SID             0x09

/* Service ID for ComM_LimitChannelToNoComMode */
#define COMM_LIMITCHANNELTONOCOMMODE_SID   0x0b

/* Service ID for ComM_LimitECUToNoComMode */
#define COMM_LIMITECUTONOCOMMODE_SID       0x0c

/* Service ID for ComM_ReadInhibitCounter */
#define COMM_READINHIBITCOUNTER_SID        0x0d

/* Service ID for ComM_ResetInhibitCounter */
#define COMM_RESETINHIBITCOUNTER_SID       0x0e

/* Service ID for ComM_SetECUGroupClassification */
#define COMM_SETECUGROUPCLASSIFICATION_SID 0x0f

/* Service ID for ComM_GetVersionInfo */
#define COMM_GETVERSIONINFO_SID            0x10

/* Service ID for ComM_Nm_NetworkStartIndication */
#define COMM_NM_NETWORKSTARTINDICATION_SID 0x15

/* Service ID for ComM_Nm_NetworkMode */
#define COMM_NM_NETWORKMODE_SID            0x18

/* Service ID for ComM_Nm_PrepareBusSleepMode */
#define COMM_NM_PREPAREBUSSLEEPMODE_SID    0x19

/* Service ID for ComM_Nm_BusSleepMode */
#define COMM_NM_BUSSLEEPMODE_SID           0x1a

/* Service ID for ComM_Nm_RestartIndication */
#define COMM_NM_RESTARTINDICATION_SID      0x1b

/* Service ID for ComM_DCM_ActiveDiagnostic */
#define COMM_DCM_ACTIVEDIAGNOSTIC_SID      0x1f

/* Service ID for ComM_DCM_InactiveDiagnostic */
#define COMM_DCM_INACTIVEDIAGNOSTIC_SID    0x20

/* Service ID for ComM_CommunicationAllowed */
#define COMM_COMMUNICATIONALLOWED_SID      0x35

/* Service ID for ComM_Ecum_WakeUpIndication */
#define COMM_ECUM_WAKEUPINDICATION_SID     0x2a

/* Service ID for ComM_BusSM_ModeIndication */
#define COMM_BUSSM_MODEINDICATION_SID      0x33

/* Service ID for ComM_BusSM_BusSleepMode */
#define COMM_BUSSM_BUSSLEEPMODE_SID        0x34

/* Service ID for ComM_ResetRequestedChannel */
#define COMM_RESETREQUESTEDCHANNEL_SID     0x38

/* Service ID for ComM_EcuM_PNCWakeUpIndication */
#define COMM_ECUM_PNCWAKEUPINDICATION_SID  0x37

/* Service ID for ComM_GetChannelBusLoad */
#define COMM_GETCHANNELBUSLOAD_SID         0x39

/* Initialization status of ComM */
/* @Trace: SRS_ComM_AR_00174 */
/* @Trace: ComM_SUD_DATATYPE_009 */
typedef enum
{
  COMM_UNINIT = 0x00,
  COMM_INIT   = 0x01
} ComM_InitStatusType;

/* @Trace: SRS_ComM_AR_00020 SRS_ComM_AR_00021 SRS_ComM_AR_00175 */
/* @Trace: ComM_SUD_DATATYPE_010 */
/* Current mode of a PNC */
typedef enum
{
  COMM_PNC_REQUESTED        = 0x00,
  COMM_PNC_READY_SLEEP      = 0x01,
  COMM_PNC_PREPARE_SLEEP    = 0x02,
  COMM_PNC_NO_COMMUNICATION = 0x03
} ComM_PncModeType;

/* @Trace: SRS_ComM_AR_00176 */
/* @Trace: ComM_SUD_DATATYPE_008  */
/* @Trace: SRS_ComM_AR_00254 */
/* State and sub-state of ComM state machine */
typedef enum
{
  COMM_NO_COM_NO_PENDING_REQUEST  = 0,
  COMM_NO_COM_REQUEST_PENDING     = 1,
  COMM_FULL_COM_NETWORK_REQUESTED = 2,
  COMM_FULL_COM_READY_SLEEP       = 3,
  COMM_SILENT_COM                 = 4
} ComM_StateType;

#if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
/* @Trace: SRS_ComM_AR_00173 */
/* @Trace: ComM_SUD_DATATYPE_011 */
/* This type contains the implementation-specific post build
    configuration structure */
typedef struct
{
  uint8 Dummy;
}ComM_ConfigType;
#endif


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_Init */
extern FUNC(void, COMM_CODE) ComM_Init(
  P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) ConfigPtr);

/* Extern for ComM_DeInit */
extern FUNC(void, COMM_CODE) ComM_DeInit(void);

/* Extern for ComM_ResetRequestedChannel */
extern FUNC(void, COMM_CODE) ComM_ResetRequestedChannel
  (NetworkHandleType Channel);

/* Extern for ComM_GetStatus */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus(P2VAR(ComM_InitStatusType,
  AUTOMATIC, COMM_APPL_DATA) Status);

#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
/* Extern for ComM_GetInhibitionStatus */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetInhibitionStatus(
  NetworkHandleType Channel, P2VAR(ComM_InhibitionStatusType, AUTOMATIC,
  COMM_APPL_DATA) Status);
#endif

/* Extern for ComM_RequestComMode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComMode(ComM_UserHandleType
  User, ComM_ModeType ComMode);

/* Extern for ComM_GetMaxComMode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetMaxComMode(
  ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC,
  COMM_APPL_DATA) ComMode);

/* Extern for ComM_GetRequestedComMode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetRequestedComMode(
  ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC,
  COMM_APPL_DATA) ComMode);

/* Extern for ComM_GetCurrentComMode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurrentComMode(
  ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC,
  COMM_APPL_DATA) ComMode);

/* Extern for ComM_SetECUGroupClassification */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_SetECUGroupClassification(
  ComM_InhibitionStatusType Status);

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/* Extern for ComM_PreventWakeUp */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_PreventWakeUp(NetworkHandleType
  Channel, boolean Status);
#endif

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
  (COMM_RESET_AFTER_FORCING_NO_COMM == STD_ON))
/* Extern for ComM_LimitChannelToNoComMode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode(
  NetworkHandleType Channel, boolean Status);

/* Extern for ComM_LimitECUToNoComMode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode(boolean Status);
#endif

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\
  (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON))
/* Extern for ComM_ReadInhibitCounter */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter(P2VAR(uint16,
  AUTOMATIC, COMM_APPL_DATA) CounterValue);

/* Extern for ComM_ResetInhibitCounter */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter(void);
#endif /* End of if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) &&\*/

#if (COMM_VERSION_INFO_API == STD_ON)
/* Extern for ComM_GetVersionInfo */
extern FUNC(void, COMM_CODE) ComM_GetVersionInfo(P2VAR(Std_VersionInfoType,
  AUTOMATIC, COMM_APPL_DATA) Versioninfo);
#endif

/* Extern for ComM_BusSM_ModeIndication */
extern FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication(NetworkHandleType
  Channel, ComM_ModeType ComMode);

#if (COMM_LINSLAVE_NMVARIANT_SUPPORT == STD_ON)
/* Extern for ComM_BusSM_BusSleepMode */
extern FUNC(void, COMM_CODE) ComM_BusSM_BusSleepMode(NetworkHandleType Channel);
#endif /* End if (COMM_LINSLAVE_NMVARIANT_SUPPORT == STD_ON) */

#if (COMM_BUSLOAD_DETECTING == STD_ON)
/* Extern for ComM_GetChannelBusLoad */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetChannelBusLoad(NetworkHandleType Channel,
  P2VAR(ComM_BusMsgType, AUTOMATIC, COMM_APPL_DATA) BusLoad);
#endif

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/* @Trace: SWS_ComM_00649 */
/* ComM return types */
#ifndef COMM_E_MODE_LIMITATION
#define COMM_E_MODE_LIMITATION                (0x02)
#endif

#endif /* COMM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

