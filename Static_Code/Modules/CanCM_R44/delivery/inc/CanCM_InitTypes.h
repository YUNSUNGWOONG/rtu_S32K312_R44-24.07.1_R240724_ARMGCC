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
**  SRC-MODULE: CanCM_InitTypes.h                                             **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Declaration of data types                                     **
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
** 1.0.9     20-Dec-2023   HieuTM8          CP44-3561                         **
** 1.0.7.0   29-Jun-2023   YB Song          CP44-2402                         **
** 1.0.5.0   14-Oct-2022   NhatTD2          CP44-1009                         **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_INIT_TYPES_H
#define CANCM_INIT_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM_Cfg.h"
/* @Trace: SRS_BSW_00301 */
#if (STD_ON == CANCM_DEM_STATUS)
#include "Dem.h"
#else
#include "Rte_Type.h"
#endif
#include "Det.h"
#include "ComStack_Types.h"


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANCM_INITTYPES_H_AR_RELEASE_MAJOR_VERSION   (0x04u)
#define CANCM_INITTYPES_H_AR_RELEASE_MINOR_VERSION   (0x04u)
#define CANCM_INITTYPES_H_AR_RELEASE_PATCH_VERSION   (0x00u)

/* File version information */
#define CANCM_INITTYPES_H_SW_MAJOR_VERSION   (0x01u)
#define CANCM_INITTYPES_H_SW_MINOR_VERSION   (0x00u)

/*******************************************************************************
**                      Typedef Section                                       **
*******************************************************************************/
/* @Trace: CanCM_SUD_DATATYPE_009 */
typedef struct 
{
  EcuM_WakeupSourceType WakSrc;
  IoHwAb_IndexType WakPin;
  #if (STD_ON == CANCM_DEM_STATUS)
  Dem_EventIdType EventId;
  #endif


  /* voltage range */
  uint16 AbnormalUpper;
  uint16 AbnormalLower;
  uint16 CriticalUpper;
  uint16 CriticalLower;
  uint16 Hysteresis;
  
  /* timing parameters */
  uint16 ActivationTime;
  uint16 DelayTimeCritical;
  uint16 TimeoutStartTime;
  
  uint8 ComMChannelId;
  uint8 ChannelId;
  uint8 CanIfCtrlId;
} Tdd_CanCM_ChannelConfig;

/* @Trace: CanCM_SUD_DATATYPE_008 Nhat*/
#if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)
/* global struct which store configuration data of CanCM */
typedef struct
{

  /* the status of CanCMDemStatusSupport parameter */
  boolean DemSupport;
  /* the status of DisableDMOnAbnormalVoltage parameter */
  boolean DMAbnormal;
  /* the status of CanCMWakeUpSupport parameter */
  boolean WKSupport;
  /* the status of CanCMHysteresisSupport parameter */
  boolean HysSupport;
  /* the value of CanCMFilteringConstant parameter */
  uint8 FilteringConst;
  /* the number of CanCM channels */
  uint8 NumOfChannels;
  /* the number of ComM CanCM channels */
  uint8 NumOfComMChannels;
  /* the number of ADC groups */
  uint8 NumOfAdcGroups;
  /* the largest channelId of ComM mapped to CanCMChannelConfig */
  uint8 LastChannelID;
  /* To point to CanCM_AdcDefaultVal */
  P2CONST(uint16, AUTOMATIC, CANCM_CONST) PtrAdcDefaultVal;
  /* To point to CanCM_AdcGroup */
  P2VAR(IoHwAb_IndexType, AUTOMATIC, CANCM_VAR_NOINIT) PtrAdcGroup;
  /* To point to CanCM_ComMChannelMap */
  P2CONST(NetworkHandleType, AUTOMATIC, CANCM_CONST) PtrComMChannelMap;
  /* To point to CanCM_ChannelConfig */
  P2CONST(Tdd_CanCM_ChannelConfig, AUTOMATIC, CANCM_CONST) PtrChannelConfig;
}CanCM_ConfigType;
#endif

/* @Trace: CanCM_SUD_DATATYPE_010 */
/* polyspace-begin MISRA-C3:19.2 [Not a defect:Low] "Using UNION instead of struct to optimize memory and reduce the complexity of code" */
typedef union
{
  struct
  {
    /*
     * Check if the bit access is little ENDIAN and define the bit fields
     * accordingly
     */
  #if (CPU_BIT_ORDER == LSB_FIRST)
    uint8 Unused:2;
    uint8 NmDisabled :1;
    uint8 WakEvt:1;
    uint8 WakChkEnabled :1;
    uint8 TxDisabled :1;
    uint8 DtcDisabled:1;
    uint8 VolFailed:1;
  #else
    uint8 VolFailed:1;
    uint8 DtcDisabled:1;
    uint8 TxDisabled :1;
    uint8 WakChkEnabled :1;
    uint8 WakEvt :1;
    uint8 NmDisabled :1;
    uint8 Unused:2;
  #endif
  }BitByteRecord;

  uint8 MaskByte;
  
}Tun_CanCMFlagStatus;
/* polyspace-end MISRA-C3:19.2 [Not a defect:Low] "Using UNION instead of struct to optimize memory and reduce the complexity of code" */
/*******************************************************************************
**                      Enum Section                                          **
*******************************************************************************/
/* @Trace: CanCM_SUD_DATATYPE_006 */
typedef enum
{
  CANCM_COMM_STAT_INACTIVE        = 0,
  CANCM_COMM_STAT_START           = 1,
  CANCM_COMM_STAT_ACTIVE          = 2,
  CANCM_COMM_STAT_SHUTDOWN        = 3,
  CANCM_COMM_STAT_UNDEFINED       = 4
} CanCM_CommStatType;
/* @Trace: CanCM_SUD_DATATYPE_007 */
typedef enum
{
  CANCM_VOL_MODE_NORMAL           = 0,
  CANCM_VOL_MODE_ABNORMAL         = 1,
  CANCM_VOL_MODE_CRITICAL         = 2,
  CANCM_VOL_MODE_UNDEFINED        = 3
} CanCM_VolModType;


enum
{
  CANCM_COMM_STAT_TX_DISABLED                   = 0,
  CANCM_COMM_STAT_TX_ENABLED                    = 1,
};

enum
{
  CANCM_COMM_STAT_RX_DISABLED                  = 0,
  CANCM_COMM_STAT_RX_ENABLED_DM_ENABLED        = 1,
  CANCM_COMM_STAT_RX_ENABLED_DM_DISABLED       = 2,
};
/* @Trace: SRS_CanCM_ES95400_30E_00040 */
/* @Trace: CanCM_SUD_DATATYPE_004 */
typedef uint8 CanCM_ChannelType;

#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
