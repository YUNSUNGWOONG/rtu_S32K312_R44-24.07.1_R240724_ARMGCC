/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't master." */
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
**  SRC-MODULE: CanCM_Ram.c                                                   **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Provision of Global RAM Variables                             **
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
** 1.0.6.0   04-Nov-2022   JW Oh            CP44-752                          **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"
#include "CanCM_Ram.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)
#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Current Voltage Mode*/
/* polyspace +2 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(CanCM_VolModType, CANCM_VAR_NOINIT) CanCM_VolMod[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Current Communication State*/
/* polyspace +2 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(CanCM_CommStatType, CANCM_VAR_NOINIT) 
        CanCM_CommStat[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Internal Status */
/* polyspace +2 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(Tun_CanCMFlagStatus, CANCM_VAR_NOINIT) 
        CanCM_FlagStatus[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#else /* (STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Current Voltage Mode*/
/* polyspace +2 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(CanCM_VolModType, CANCM_VAR_NOINIT)
        CanCM_VolMod[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Current Communication State*/
/* polyspace +2 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(CanCM_CommStatType, CANCM_VAR_NOINIT)
        CanCM_CommStat[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SRS_CanCM_ES95400_30E_00041 */
/* Global Variable for Internal Status */
/* polyspace +2 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(Tun_CanCMFlagStatus, CANCM_VAR_NOINIT)
        CanCM_FlagStatus[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* (STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */


#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global Variable for Battery Voltage */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_BatVol;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global Variable for Battery Voltage Fail Count */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_BatVolFailCnt;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global Variable for ADC sampling period */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_AdcSampleCnt;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Network Activation Timer Counter */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_NTimerCounter[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Delay Voltage Error Timer Counter */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_ETimerCounter[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Reception DM Start Timer Counter */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_RTimerCounter[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#else

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Network Activation Timer Counter */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_NTimerCounter[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Delay Voltage Error Timer Counter */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_ETimerCounter[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Reception DM Start Timer Counter */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_RTimerCounter[CANCM_MAX_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CanCM */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR (boolean, CANCM_VAR_NOINIT) CanCM_CanCMStatus;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint8, CANCM_VAR) CanCM_NumOfAdcGrp;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint8, CANCM_VAR) CanCM_FiltConst;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint8, CANCM_VAR) CanCM_NumOfChannels;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint8, CANCM_VAR) CanCM_LastChannelID;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(boolean, CANCM_VAR) CanCM_HysteresisSupport;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(boolean, CANCM_VAR) CanCM_WakeupSupport;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(boolean, CANCM_VAR) CanCM_DemStatus;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(boolean, CANCM_VAR) CanCM_DisableDMOnAbnormalVoltage;
#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* global variables which point to generated struct when the module support Post-build */
#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16,CANCM_VAR_NOINIT) CanCM_AdcGroupVal[CANCM_MAX_NUMBER_OF_ADC_GROUPS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#endif /* end of (STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)
#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array saving previous battery voltage value */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
VAR(uint16,CANCM_VAR_NOINIT) CanCM_AdcGroupVal[CANCM_NUMBER_OF_ADC_GROUPS];
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif /* end of (STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

