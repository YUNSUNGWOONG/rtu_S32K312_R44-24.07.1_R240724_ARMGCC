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
**  SRC-MODULE: CanCM_Ram.h                                                   **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Header file of CanCM_Ram.c                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.6.0   04-Nov-2022   JW Oh            CP44-752, CP44-1009               **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_RAM_H
#define CANCM_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"             /* CanCM main header file */
#include "CanCM_InitTypes.h"   /* CanCM type definition header file */
#include "CanCM_Cfg.h"
#if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)
#include "CanCM_PBcfg.h"
#endif



/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_025 */
/* Global Variable for Current Voltage Mode*/
extern VAR(CanCM_VolModType, CANCM_VAR_NOINIT) CanCM_VolMod[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_015 */
/* Global Variable for Current Communication State*/
extern VAR(CanCM_CommStatType, CANCM_VAR_NOINIT) CanCM_CommStat[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_029 */
/* Global Variable for Internal Status */
extern VAR(Tun_CanCMFlagStatus, CANCM_VAR_NOINIT) CanCM_FlagStatus[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#else /* (STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_025 */
/* Global Variable for Current Voltage Mode*/
extern VAR(CanCM_VolModType, CANCM_VAR_NOINIT) CanCM_VolMod[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_015 */
/* Global Variable for Current Communication State*/
extern VAR(CanCM_CommStatType, CANCM_VAR_NOINIT) CanCM_CommStat[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_029 */
/* Global Variable for Internal Status */
extern VAR(Tun_CanCMFlagStatus, CANCM_VAR_NOINIT) CanCM_FlagStatus[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* (STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_031 */
/* Global Variable for Battery Voltage */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_BatVol;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_032 */
/* Global Variable for Battery Voltage Fail Count */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_BatVolFailCnt;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_033 */
/* Global Variable for ADC Sample Count */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_AdcSampleCnt;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_019 */
/* Global Variable for Network Activation Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_NTimerCounter[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_021 */
/* Global Variable for Voltage Error Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_ETimerCounter[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_023 */
/* Global Variable for Reception DM Start Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_RTimerCounter[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#else

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Network Activation Timer Counter */
/* @Trace: CanCM_SUD_GLOBALVAR_019 */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_NTimerCounter[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_021 */
/* Global Variable for Voltage Error Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_ETimerCounter[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_023 */
/* Global Variable for Reception DM Start Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_RTimerCounter[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif

#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)
#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_017 */
/* Global Variable for values of ADC for non-postbuild Mode */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_AdcGroupVal[CANCM_NUMBER_OF_ADC_GROUPS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_034 */
/* Global variable to store Initialization status of CanCM */
extern VAR (boolean, CANCM_VAR_NOINIT) CanCM_CanCMStatus;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*set of global variables which store configuration for post-build*/
#if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_027 */
/* Global variable for number of ADC groups */
extern VAR(uint8, CANCM_VAR) CanCM_NumOfAdcGrp;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_030 */
/* Global variable for filtering constant */
extern VAR(uint8, CANCM_VAR) CanCM_FiltConst;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_016 */
/* Global variable for number of channels */
extern VAR(uint8, CANCM_VAR) CanCM_NumOfChannels;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_018 */
/* Global variable for the largest channelId mapped to CanCMChannelConfig */
extern VAR(uint8, CANCM_VAR) CanCM_LastChannelID;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_020 */
/* Global variable for checking DEM reported */
extern VAR(boolean, CANCM_VAR) CanCM_DemStatus;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_022 */
/* Global variable for supporting Hysteresis */
extern VAR(boolean, CANCM_VAR) CanCM_HysteresisSupport;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_024 */
/* Global variable for supporting Wake-up */
extern VAR(boolean, CANCM_VAR) CanCM_WakeupSupport;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_026 */
/* Global variable for supporting disable Abnormal Voltage mode */
extern VAR(boolean, CANCM_VAR) CanCM_DisableDMOnAbnormalVoltage;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_028 */
extern VAR(uint16,CANCM_VAR_NOINIT) CanCM_AdcGroupVal[CANCM_MAX_NUMBER_OF_ADC_GROUPS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#endif /* end of (STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT) */


#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
