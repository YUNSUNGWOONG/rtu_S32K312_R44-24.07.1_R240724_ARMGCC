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
**  SRC-MODULE: CanCM_PCTypes.h                                               **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Declare global variables support build library                **
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
** 1.0.5.0   14-Oct-2022   NhatTD2          CP44-812                          **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_PCTYPES_H
#define CANCM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANCM_PCTYPES_AR_RELEASE_MAJOR_VERSION   (0x04u)
#define CANCM_PCTYPES_AR_RELEASE_MINOR_VERSION   (0x04u)
#define CANCM_PCTYPES_AR_RELEASE_PATCH_VERSION   (0x00u)

/* File version information */
#define CANCM_PCTYPES_SW_MAJOR_VERSION   (0x01u)
#define CANCM_PCTYPES_SW_MINOR_VERSION   (0x00u)

/*******************************************************************************
**                      Defines Section                                       **
*******************************************************************************/
#define CANCM_FALSE                                         0x00U
#define CANCM_TRUE                                          0x01U

#define CANCM_ADC_SAMPLE_MOD        ((uint8)0x02)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*declaration for Channel and ADC groups */
#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_008 */
extern CONST(Tdd_CanCM_ChannelConfig, CANCM_CONST) CanCM_ChannelConfig[CANCM_NUMBER_OF_CHANNELS];
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_006 */
/* Global Array for Channel index mapping with ComM Channel Id */
extern CONST(NetworkHandleType, CANCM_CONST) CanCM_ComMChannelMap[CANCM_COM_M_CHANNEL_MAP];
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_004 */
/* Global Array for Adc group Ids */
extern VAR(IoHwAb_IndexType, CANCM_VAR_NOINIT) CanCM_AdcGroup[CANCM_NUMBER_OF_ADC_GROUPS];
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_002 */
/* Global array saving configured default ADC value  */
extern CONST(uint16, CANCM_CONST) CanCM_AdcDefaultVal[CANCM_NUMBER_OF_ADC_GROUPS];
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif
#endif /*end of (STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_001 */
/* Global variable for checking DET reported */
extern CONST(boolean, CANCM_CONST) CanCM_DevErrorDetect;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_003 */
/* Global variable for supporting Version Info */
extern CONST(boolean, CANCM_CONST) CanCM_VersionInfoApi;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_005 */
/* Global variable for number of ADC groups */
extern CONST(uint8, CANCM_CONST) CanCM_NumOfAdcGrp;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_007 */
/* Global variable for filtering constant */
extern CONST(uint8, CANCM_CONST) CanCM_FiltConst;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_010 */
/* Global variable for number of channels */
extern CONST(uint8, CANCM_CONST) CanCM_NumOfChannels;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_014 */
/* Global variable for the largest channelId mapped to CanCMChannelConfig */
extern CONST(uint8, CANCM_CONST) CanCM_LastChannelID;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_009 */
/* Global variable for checking DEM reported */
extern CONST(boolean, CANCM_CONST) CanCM_DemStatus;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_011 */
/* Global variable for supporting Hysteresis */
extern CONST(boolean, CANCM_CONST) CanCM_HysteresisSupport;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_012 */
/* Global variable for supporting Wake-up */
extern CONST(boolean, CANCM_CONST) CanCM_WakeupSupport;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#define CANCM_START_SEC_CONST_BOOLEAN
#include "MemMap.h"
/* @Trace: CanCM_SUD_GLOBALVAR_013 */
/* Global variable for supporting disable Abnormal Voltage mode */
extern CONST(boolean, CANCM_CONST) CanCM_DisableDMOnAbnormalVoltage;
#define CANCM_STOP_SEC_CONST_BOOLEAN
#include "MemMap.h"

#endif /*end of (STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT) */

#if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)

#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
#define CANCM_START_SEC_CONST_16
#include "MemMap.h"
extern P2CONST(IoHwAb_IndexType, AUTOMATIC,CANCM_VAR) CanCM_AdcGroup;
#define CANCM_STOP_SEC_CONST_16
#include "MemMap.h"
#endif

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
extern P2CONST(NetworkHandleType, AUTOMATIC,CANCM_VAR) CanCM_ComMChannelMap;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(Tdd_CanCM_ChannelConfig, AUTOMATIC,CANCM_VAR) CanCM_ChannelConfig;
#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* #if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT) */ 

#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
