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
**  SRC-MODULE: CanCM_Config.c                                                **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Initialize global variables support build library             **
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
#include "CanCM_PCTypes.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)
#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(uint8, CANCM_CONST) CanCM_NumOfAdcGrp = CANCM_NUMBER_OF_ADC_GROUPS;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(uint8, CANCM_CONST) CanCM_FiltConst = CANCM_FILTERING_CONSTANT;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(uint8, CANCM_CONST) CanCM_NumOfChannels = CANCM_NUMBER_OF_CHANNELS;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(uint8, CANCM_CONST) CanCM_LastChannelID = CANCM_LAST_CHANNEL_HANDLE;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(boolean, CANCM_CONST) CanCM_HysteresisSupport = CANCM_HYSTERESIS_SUPPORT;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(boolean, CANCM_CONST) CanCM_WakeupSupport = CANCM_WAKEUP_SUPPORT;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(boolean, CANCM_CONST) CanCM_DemStatus = CANCM_DEM_STATUS;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(boolean, CANCM_CONST) CanCM_DisableDMOnAbnormalVoltage = 
                                           CANCM_DISABLE_DM_ON_ABNOMAL_VOLTAGE;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#else /* #if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
P2CONST(IoHwAb_IndexType, AUTOMATIC,CANCM_VAR) CanCM_AdcGroup;
#define CANCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif

#define CANCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
P2CONST(NetworkHandleType, AUTOMATIC,CANCM_VAR) CanCM_ComMChannelMap;
#define CANCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
P2CONST(Tdd_CanCM_ChannelConfig, AUTOMATIC,CANCM_VAR) CanCM_ChannelConfig;
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* #if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This variable is checked manually and no impact" */
CONST(boolean, CANCM_CONST) CanCM_DevErrorDetect = CANCM_DEV_ERROR_DETECT;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is checked manually and no impact" */
CONST(boolean, CANCM_CONST) CanCM_VersionInfoApi = CANCM_VERSION_INFO_API;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/


