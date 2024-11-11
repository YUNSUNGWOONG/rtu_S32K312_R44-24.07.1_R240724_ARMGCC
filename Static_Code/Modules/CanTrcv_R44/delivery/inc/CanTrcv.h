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
**  SRC-MODULE: CanTrcv.h                                                     **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Header file of CanTrcv.c                                      **
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
** 1.0.11         08-Feb-2024         Yubin Song       #CP44-3726             **
** 1.0.7          31-Oct-2022         HieuTM8          #CP44-1036             **
** 1.0.6          17-Oct-2022         HieuTM8          #CP44-877              **
** 1.0.4          12-May-2022         HieuTM8          Redmine #26586         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/
/* @Trace: SRS_BSW_00300 */
#ifndef CANTRCV_H
#define CANTRCV_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
#include "CanTrcv_IntTypes.h"

#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
#include "CanTrcv_PBCfg.h"
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */

#if (STD_ON == CANTRCV_SPI_SUPPORTED)
/* @Trace: CanTrcv_SUD_DATATYPE_008 CanTrcv_SUD_DATATYPE_009 CanTrcv_SUD_DATATYPE_010 CanTrcv_SUD_DATATYPE_011
 * CanTrcv_SUD_DATATYPE_016 */
#include "Spi.h"
#endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */
/* Development Error Tracer header file */
#include "Det.h"
/* @Trace: CanTrcv_SUD_DATATYPE_018 */
#include "Std_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
/* The state of a flag in the transceiver hardware. */
/* @Trace: CanTrcv_SUD_DATATYPE_037 */
typedef enum
{
  CANTRCV_FLAG_CLEARED = 0,
  CANTRCV_FLAG_SET
} CanTrcv_TrcvFlagStateType;

/* Partial Network activation state */
/* @Trace: CanTrcv_SUD_DATATYPE_036 */
typedef enum
{
  PN_DISABLED = 0,
  PN_ENABLED
} CanTrcv_PNActivationType;
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
/*******************************************************************************
**                        Service IDs                                         **
*******************************************************************************/

/* @Trace: CanTrcv_SUD_MACRO_004 */

/* Service ID for CanTrcv_Init */
#define CANTRCV_INIT_SID                            ((uint8)0x00)
/* Service ID for CanTrcv_SetOpMode */
#define CANTRCV_SETOPMODE_SID                       ((uint8)0x01)
/* Service ID for CanTrcv_GetOpMode */
#define CANTRCV_GETOPMODE_SID                       ((uint8)0x02)
/* Service ID for CanTrcv_GetBusWuReason */
#define CANTRCV_GETBUSWUREASON_SID                  ((uint8)0x03)
/* Service ID for CanTrcv_GetVersionInfo */
#define CANTRCV_GETVERSIONINFO_SID                  ((uint8)0x04)
/* Service ID for CanTrcv_SetWakeupMode */
#define CANTRCV_SETWAKEUPMODE_SID                   ((uint8)0x05)
/* Service ID for CanTrcv_MainFunction */
#define CANTRCV_MAINFUNCTION_SID                    ((uint8)0x06)
/* Service ID for CanTrcv_CheckWakeup */
#define CANTRCV_CHECKWAKEUP_SID                     ((uint8)0x07)
/* Service ID for CanTrcv_MainFunctionDiagnostics */
#define CANTRCV_MAINFUNCTIONDIAGNOSTICS_SID         ((uint8)0x08)
/* Service ID for CanTrcv_GetTrcvSystemData */
#define CANTRCV_GETTRCVSYSTEMDATA_SID               ((uint8)0x09)
/* Service ID for CanTrcv_ClearTrcvWufFlag */
#define CANTRCV_CLEARTRCVWUFLAG_SID                 ((uint8)0x0A)
/* Service ID for CanTrcv_ReadTrcvTimeoutFlag */
#define CANTRCV_READTRCVTIMEOUTFLAG_SID             ((uint8)0x0B)
/* Service ID for CanTrcv_ClearTrcvTimeoutFlag */
#define CANTRCV_CLEARTRCVTIMEOUTFLAG_SID            ((uint8)0x0C)
/* Service ID for CanTrcv_ReadTrcvSilenceFlag */
#define CANTRCV_READTRCVSILENCEFLAG_SID             ((uint8)0x0D)
/* Service ID for CanTrcv_CheckWakeFlag */
#define CANTRCV_CHECKWAKEFLAG_SID                   ((uint8)0x0E)
/* Service ID for CanTrcv_SetPNActivationState */
#define CANTRCV_SETPNACTIVATIONSTATE_SID            ((uint8)0x0F)
/* Service ID for CanTrcv_DeInit */
#define CANTRCV_DEINIT_SID                          ((uint8)0x10)

/*******************************************************************************
**                              DET IDs                                       **
*******************************************************************************/

/* @Trace: CanTrcv_SUD_MACRO_007 */
/* @Trace: SRS_BSW_00385 */
/* API called with wrong parameter for the CAN transceiver */
#define CANTRCV_E_INVALID_TRANSCEIVER               ((uint8)0x01)
/* API called with null pointer parameter */
#define CANTRCV_E_PARAM_POINTER                     ((uint8)0x02)
/* API service used without initialization */
#define CANTRCV_E_UNINIT                            ((uint8)0x11)
/* API service called in wrong transceiver operation mode */
#define CANTRCV_E_TRCV_NOT_STANDBY                  ((uint8)0x21)
#define CANTRCV_E_TRCV_NOT_NORMAL                   ((uint8)0x22)
/* API service called with invalid parameter for TrcvWakeup Mode */
#define CANTRCV_E_PARAM_TRCV_WAKEUP_MODE            ((uint8)0x23)
/* API service called with invalid parameter for OpMode */
#define CANTRCV_E_PARAM_TRCV_OPMODE                 ((uint8)0x24)
/* Configured baud rate is not supported by the transceiver */
#define CANTRCV_E_BAUDRATE_NOT_SUPPORTED            ((uint8)0x25)
/* No/incorrect communication to transceiver */
#define CANTRCV_E_NO_TRCV_CONTROL                   ((uint8)0x26)
/* Module initialization has failed */
#define CANTRCV_E_INIT_FAILED                       ((uint8)0x27)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANTRCV_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, CANTRCV_CODE) CANTRCV_INIT_MACRO(
  P2CONST(CanTrcv_ConfigType, AUTOMATIC, CANTRCV_CONST) ConfigPtr);

extern FUNC(void, CANTRCV_CODE) CanTrcv_Init_Channel(
  VAR(uint8, AUTOMATIC) CanTrcvChannel);

extern FUNC(void, CANTRCV_CODE) CanTrcv_InitOpMode_Channel(
  VAR(uint8, AUTOMATIC) CanTrcvChannel,
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) initOpMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_SETOPMODE_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) OpMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetOpMode_Processing(
  VAR(uint8, AUTOMATIC) Transceiver,
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) OpMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_GETOPMODE_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode);

extern FUNC(void, CANTRCV_CODE) CANTRCV_GETVERSIONINFO_MACRO(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_APPL_DATA) versioninfo);

extern FUNC(void, CANTRCV_CODE) CANTRCV_DEINIT_MACRO(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CHECKWAKEUP_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver);

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_SETWAKEUPMODE_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  VAR(CanTrcv_TrcvWakeupModeType,AUTOMATIC) TrcvWakeupMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_GETBUSWUREASON_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_CONST) reason);

#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CHECKWAKEFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver);
  
extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_GETTRCVSYSTEMDATA_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_VAR) TrcvSysData);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_READTRCVTIMEOUTFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CLEARTRCVTIMEOUTFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_READTRCVSILENCEFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_SETPNACTIVATIONSTATE_MACRO(
  VAR(CanTrcv_PNActivationType, AUTOMATIC) ActivationState);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CLEARTRCVWUFFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver);

#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED))

extern FUNC(ArisuCan_SBCModeType, CANTRCV_CODE)
  CanTrcv_ArisuCan_GetInternalSBCMode(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_ReadStatus(
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) address,
  P2VAR(CanTrcv_ArisuCanType, AUTOMATIC, CANTRCV_VAR) data);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_PowerDownMode(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_ChangeStopMode(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_VbsenseEnable(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_VbsenseDisable(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_SetMode(
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode);

extern FUNC(void, CANTRCV_CODE) CanTrcv_ArisuCan_RequestCanMode(
  VAR(CanTrcv_HwType, AUTOMATIC) canTrcv,
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode);

#endif /* ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED)) */

#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h"

/* @Trace: CanTrcv_SUD_CONSTVAR_003 */
#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
#define CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTrcv_ConfigType, CANTRCV_CONST)
  CanTrcv_Config[CANTRCV_NUM_OF_VARIANTS];
#define CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
#endif /* CANTRCV_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
