/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/**
*   @file Dio_Cfg.h
*   @implements Dio_Cfg.h_Artifact
*
*   @defgroup DIO_CFG Dio Cfg
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Std_Types.h"
#include "Siul2_Dio_Ip_Cfg.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define DIO_VENDOR_ID_CFG_H                   43
#define DIO_AR_RELEASE_MAJOR_VERSION_CFG_H    4
#define DIO_AR_RELEASE_MINOR_VERSION_CFG_H    7
#define DIO_AR_RELEASE_REVISION_VERSION_CFG_H 0
#define DIO_SW_MAJOR_VERSION_CFG_H            3
#define DIO_SW_MINOR_VERSION_CFG_H            0
#define DIO_SW_PATCH_VERSION_CFG_H            0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Dio_Cfg.h and StandardTypes.h file are of the same Autosar version */
    #if ((DIO_AR_RELEASE_MAJOR_VERSION_CFG_H != STD_AR_RELEASE_MAJOR_VERSION) ||   \
        (DIO_AR_RELEASE_MINOR_VERSION_CFG_H != STD_AR_RELEASE_MINOR_VERSION)       \
        )
        #error "AUTOSAR Version Numbers of Dio_Cfg.h and StandardTypes.h are different"
    #endif
#endif

/* Check if Dio_Cfg.h and Siul2_Dio_Ip_Cfg.h files are of the same vendor.*/
#if (DIO_VENDOR_ID_CFG_H != SIUL2_DIO_IP_VENDOR_ID_CFG_H)
    #error "Dio_Cfg.h and Siul2_Dio_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Dio_Cfg.h and Siul2_Dio_Ip_Cfg.h files are of the same Autosar version.*/
#if ((DIO_AR_RELEASE_MAJOR_VERSION_CFG_H    != SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (DIO_AR_RELEASE_MINOR_VERSION_CFG_H    != SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (DIO_AR_RELEASE_REVISION_VERSION_CFG_H != SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Dio_Cfg.h and Siul2_Dio_Ip_Cfg.h are different"
#endif
/* Check if Dio_Cfg.h and Siul2_Dio_Ip_Cfg.h files are of the same Software version.*/
#if ((DIO_SW_MAJOR_VERSION_CFG_H != SIUL2_DIO_IP_SW_MAJOR_VERSION_CFG_H) || \
     (DIO_SW_MINOR_VERSION_CFG_H != SIUL2_DIO_IP_SW_MINOR_VERSION_CFG_H) || \
     (DIO_SW_PATCH_VERSION_CFG_H != SIUL2_DIO_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Dio_Cfg.h and Siul2_Dio_Ip_Cfg.h are different"
#endif
       
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/
/**
* @brief          Enable or Disable Development Error Detection.
*
* @implements     DIO_DEV_ERROR_DETECT_define
*/
#define DIO_DEV_ERROR_DETECT    (STD_ON)

/**
* @brief          Function @p Dio_GetVersionInfo() enable switch.
*
* @implements     DIO_VERSION_INFO_API_define
*/
#define DIO_VERSION_INFO_API    (STD_OFF)

/**
* @brief          Function @p Dio_FlipChannel() enable switch.
*/
#define DIO_FLIP_CHANNEL_API    (STD_OFF)

/**
* @brief          Function @p Dio_MaskedWritePort() enable switch.
*/
#define DIO_MASKEDWRITEPORT_API (STD_OFF)

/**
* @brief          Platform specific define stating if mapping of port bits over port pins is reversed.
*/
#define DIO_REVERSED_MAPPING_OF_PORT_BITS_OVER_PORT_PINS    (STD_ON)

/**
* @brief          Reversed port functionality enable switch.
*
* @implements DIO_REVERSEPORTBITS_define
*/
#define DIO_REVERSEPORTBITS     (STD_ON)


/**
* @brief          Undefined pins masking enable switch.
*/
#define DIO_READZERO_UNDEFINEDPORTS (STD_OFF)



/**
* @brief Enable/Disable multiocre function from the driver
*/
#define DIO_MULTICORE_ENABLED          (STD_OFF)

/**
* @brief          Number of implemented ports.
*
* @note           Used for channel, port and channel group validation.
*/
#define DIO_NUM_PORTS_U16               ((uint16)0xa)

/**
* @brief          The number of partition on the port
*
* @note           Used for port validation.
*/
#define DIO_PORT_PARTITION_U16          ((uint16)10U)

/**
* @brief          Number of channels in a port.
*
* @note           Used for channel, port and channel group validation.
*/
#define DIO_NUM_CHANNELS_PER_PORT_U16   ((uint16)((uint16)sizeof(Dio_PortLevelType) * 0x8U))

/**
* @brief          Number of channels available on the implemented ports.
*
* @note           Used for channel validation.
*/
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    #define DIO_NUM_CHANNELS_U16            ((uint16)154U)
#endif


/**
* @brief The number of partition on the channel.
*
* @note           Used for channel validation.
*/
#define DIO_CHANNEL_PARTITION_U16           ((uint16)160U)

/**
* @brief          Mask representing no available channels on a port.
*
* @note           Used for channel validation.
*/
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    #define DIO_NO_AVAILABLE_CHANNELS_U16   ((Dio_PortLevelType)0x0U)
#endif

/**
* @brief          Mask representing the maximum valid offset for a channel group.
*
* @note           Used for channel group validation.
*/
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    #define DIO_MAX_VALID_OFFSET_U8         ((uint8)0xFU)
#endif

/**
*   @brief   Enables or disables the access to a hardware register from user mode
*            USER_MODE_SOFT_LOCKING:        All reads to hw registers will be done via REG_PROT, user mode access
*            SUPERVISOR_MODE_SOFT_LOCKING:  Locks the access to the registers only for supervisor mode
*
*   @note    Currently, no register protection mechanism is used for Dio driver.
*/
#define DIO_USER_MODE_SOFT_LOCKING      (STD_OFF)

/**
* @brief          Dio driver Pre-Compile configuration switch.
*/
#define DIO_PRECOMPILE_SUPPORT


/**
* @brief Support for User mode.
*        If this parameter has been configured to 'STD_ON', the Dio driver code can be executed from both supervisor and user mode.
*
*/

#define DIO_ENABLE_USER_MODE_SUPPORT   (STD_OFF)


#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
 #ifdef DIO_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == DIO_ENABLE_USER_MODE_SUPPORT)
    #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Dio in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined
  #endif /* (STD_ON == DIO_ENABLE_USER_MODE_SUPPORT) */
 #endif /* ifdef DIO_ENABLE_USER_MODE_SUPPORT*/
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

/**
* @brief Number of SIUL2 instances on the platform.
*/
#define DIO_NUM_SIUL2_INSTANCES_U8      ((uint8)1)

/**
* @brief List of identifiers for each of the SIUL2 instances on the platform
*/
#define DIO_SIUL2_0_U8        ((uint8)0)

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief          Symbolic name for the configuration Dio_ConfigPC.
*
*/
#define Dio_ConfigPC    (Dio_Config)

/* ========== DioConfig ========== */

/* ---------- DioPort_AL ---------- */

/**
* @brief          Symbolic name for the port DioPort_AL.
*
*/
#define DioConf_DioPort_DioPort_AL  ((uint8)0x00U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA0.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA0 ((uint16)0x0000U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA1.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA1 ((uint16)0x0001U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA2.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA2 ((uint16)0x0002U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA3.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA3 ((uint16)0x0003U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA4.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA4 ((uint16)0x0004U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA5.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA5 ((uint16)0x0005U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA6.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA6 ((uint16)0x0006U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA7.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA7 ((uint16)0x0007U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA8.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA8 ((uint16)0x0008U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA9.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA9 ((uint16)0x0009U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA10.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA10 ((uint16)0x000aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA11.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA11 ((uint16)0x000bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA12.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA12 ((uint16)0x000cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA13.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA13 ((uint16)0x000dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA14.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA14 ((uint16)0x000eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA15.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA15 ((uint16)0x000fU)

/* ---------- DioPort_AH ---------- */

/**
* @brief          Symbolic name for the port DioPort_AH.
*
*/
#define DioConf_DioPort_DioPort_AH  ((uint8)0x01U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA16.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA16 ((uint16)0x0010U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA17.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA17 ((uint16)0x0011U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA18.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA18 ((uint16)0x0012U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA19.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA19 ((uint16)0x0013U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA20.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA20 ((uint16)0x0014U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA21.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA21 ((uint16)0x0015U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA24.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA24 ((uint16)0x0018U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA25.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA25 ((uint16)0x0019U)



/**
* @brief          Symbolic name for the channel DioChannel_PTA27.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA27 ((uint16)0x001bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA28.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA28 ((uint16)0x001cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA29.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA29 ((uint16)0x001dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA30.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA30 ((uint16)0x001eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTA31.
*
*/
#define  DioConf_DioChannel_DioChannel_PTA31 ((uint16)0x001fU)

/* ---------- DioPort_BL ---------- */

/**
* @brief          Symbolic name for the port DioPort_BL.
*
*/
#define DioConf_DioPort_DioPort_BL  ((uint8)0x02U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB0.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB0 ((uint16)0x0020U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB1.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB1 ((uint16)0x0021U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB2.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB2 ((uint16)0x0022U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB3.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB3 ((uint16)0x0023U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB4.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB4 ((uint16)0x0024U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB5.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB5 ((uint16)0x0025U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB8.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB8 ((uint16)0x0028U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB9.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB9 ((uint16)0x0029U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB10.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB10 ((uint16)0x002aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB11.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB11 ((uint16)0x002bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB12.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB12 ((uint16)0x002cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB13.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB13 ((uint16)0x002dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB14.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB14 ((uint16)0x002eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB15.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB15 ((uint16)0x002fU)

/* ---------- DioPort_BH ---------- */

/**
* @brief          Symbolic name for the port DioPort_BH.
*
*/
#define DioConf_DioPort_DioPort_BH  ((uint8)0x03U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB16.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB16 ((uint16)0x0030U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB17.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB17 ((uint16)0x0031U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB18.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB18 ((uint16)0x0032U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB19.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB19 ((uint16)0x0033U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB20.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB20 ((uint16)0x0034U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB21.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB21 ((uint16)0x0035U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB22.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB22 ((uint16)0x0036U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB23.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB23 ((uint16)0x0037U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB24.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB24 ((uint16)0x0038U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB25.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB25 ((uint16)0x0039U)



/**
* @brief          Symbolic name for the channel DioChannel_PTB26.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB26 ((uint16)0x003aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB27.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB27 ((uint16)0x003bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB28.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB28 ((uint16)0x003cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB29.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB29 ((uint16)0x003dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTB30.
*
*/
#define  DioConf_DioChannel_DioChannel_PTB30 ((uint16)0x003eU)

/* ---------- DioPort_CL ---------- */

/**
* @brief          Symbolic name for the port DioPort_CL.
*
*/
#define DioConf_DioPort_DioPort_CL  ((uint8)0x04U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC0.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC0 ((uint16)0x0040U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC1.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC1 ((uint16)0x0041U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC2.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC2 ((uint16)0x0042U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC3.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC3 ((uint16)0x0043U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC4.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC4 ((uint16)0x0044U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC5.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC5 ((uint16)0x0045U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC6.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC6 ((uint16)0x0046U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC7.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC7 ((uint16)0x0047U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC8.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC8 ((uint16)0x0048U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC9.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC9 ((uint16)0x0049U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC10.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC10 ((uint16)0x004aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC11.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC11 ((uint16)0x004bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC12.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC12 ((uint16)0x004cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC13.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC13 ((uint16)0x004dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC14.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC14 ((uint16)0x004eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC15.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC15 ((uint16)0x004fU)

/* ---------- DioPort_CH ---------- */

/**
* @brief          Symbolic name for the port DioPort_CH.
*
*/
#define DioConf_DioPort_DioPort_CH  ((uint8)0x05U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC16.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC16 ((uint16)0x0050U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC17.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC17 ((uint16)0x0051U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC18.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC18 ((uint16)0x0052U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC19.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC19 ((uint16)0x0053U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC20.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC20 ((uint16)0x0054U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC21.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC21 ((uint16)0x0055U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC23.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC23 ((uint16)0x0057U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC24.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC24 ((uint16)0x0058U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC25.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC25 ((uint16)0x0059U)



/**
* @brief          Symbolic name for the channel DioChannel_PTC26.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC26 ((uint16)0x005aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC27.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC27 ((uint16)0x005bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC28.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC28 ((uint16)0x005cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC29.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC29 ((uint16)0x005dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC30.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC30 ((uint16)0x005eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTC31.
*
*/
#define  DioConf_DioChannel_DioChannel_PTC31 ((uint16)0x005fU)

/* ---------- DioPort_DL ---------- */

/**
* @brief          Symbolic name for the port DioPort_DL.
*
*/
#define DioConf_DioPort_DioPort_DL  ((uint8)0x06U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD0.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD0 ((uint16)0x0060U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD1.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD1 ((uint16)0x0061U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD2.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD2 ((uint16)0x0062U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD3.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD3 ((uint16)0x0063U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD4.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD4 ((uint16)0x0064U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD5.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD5 ((uint16)0x0065U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD6.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD6 ((uint16)0x0066U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD7.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD7 ((uint16)0x0067U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD8.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD8 ((uint16)0x0068U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD9.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD9 ((uint16)0x0069U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD10.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD10 ((uint16)0x006aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD11.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD11 ((uint16)0x006bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD12.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD12 ((uint16)0x006cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD13.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD13 ((uint16)0x006dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD14.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD14 ((uint16)0x006eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD15.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD15 ((uint16)0x006fU)

/* ---------- DioPort_DH ---------- */

/**
* @brief          Symbolic name for the port DioPort_DH.
*
*/
#define DioConf_DioPort_DioPort_DH  ((uint8)0x07U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD16.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD16 ((uint16)0x0070U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD17.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD17 ((uint16)0x0071U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD18.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD18 ((uint16)0x0072U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD20.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD20 ((uint16)0x0074U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD21.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD21 ((uint16)0x0075U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD22.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD22 ((uint16)0x0076U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD23.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD23 ((uint16)0x0077U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD24.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD24 ((uint16)0x0078U)



/**
* @brief          Symbolic name for the channel DioChannel_PTD26.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD26 ((uint16)0x007aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD27.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD27 ((uint16)0x007bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD28.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD28 ((uint16)0x007cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD29.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD29 ((uint16)0x007dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD30.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD30 ((uint16)0x007eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTD31.
*
*/
#define  DioConf_DioChannel_DioChannel_PTD31 ((uint16)0x007fU)

/* ---------- DioPort_EL ---------- */

/**
* @brief          Symbolic name for the port DioPort_EL.
*
*/
#define DioConf_DioPort_DioPort_EL  ((uint8)0x08U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE0.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE0 ((uint16)0x0080U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE1.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE1 ((uint16)0x0081U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE2.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE2 ((uint16)0x0082U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE3.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE3 ((uint16)0x0083U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE4.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE4 ((uint16)0x0084U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE5.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE5 ((uint16)0x0085U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE6.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE6 ((uint16)0x0086U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE7.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE7 ((uint16)0x0087U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE8.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE8 ((uint16)0x0088U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE9.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE9 ((uint16)0x0089U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE10.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE10 ((uint16)0x008aU)



/**
* @brief          Symbolic name for the channel DioChannel_PTE11.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE11 ((uint16)0x008bU)



/**
* @brief          Symbolic name for the channel DioChannel_PTE12.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE12 ((uint16)0x008cU)



/**
* @brief          Symbolic name for the channel DioChannel_PTE13.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE13 ((uint16)0x008dU)



/**
* @brief          Symbolic name for the channel DioChannel_PTE14.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE14 ((uint16)0x008eU)



/**
* @brief          Symbolic name for the channel DioChannel_PTE15.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE15 ((uint16)0x008fU)

/* ---------- DioPort_EH ---------- */

/**
* @brief          Symbolic name for the port DioPort_EH.
*
*/
#define DioConf_DioPort_DioPort_EH  ((uint8)0x09U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE16.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE16 ((uint16)0x0090U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE17.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE17 ((uint16)0x0091U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE18.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE18 ((uint16)0x0092U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE19.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE19 ((uint16)0x0093U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE21.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE21 ((uint16)0x0095U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE22.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE22 ((uint16)0x0096U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE23.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE23 ((uint16)0x0097U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE24.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE24 ((uint16)0x0098U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE25.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE25 ((uint16)0x0099U)



/**
* @brief          Symbolic name for the channel DioChannel_PTE26.
*
*/
#define  DioConf_DioChannel_DioChannel_PTE26 ((uint16)0x009aU)


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief          Type of a DIO port representation.
*
* @implements     Dio_PortType_typedef
*/
typedef uint8 Dio_PortType;

/**
* @brief          Type of a DIO channel representation.
*
* @implements     Dio_ChannelType_typedef
*/
typedef uint16 Dio_ChannelType;

/**
* @brief          Type of a DIO port levels representation.
*
* @implements     Dio_PortLevelType_typedef
*/
typedef uint16 Dio_PortLevelType;

/**
* @brief          Type of a DIO channel levels representation.
*
* @implements     Dio_LevelType_typedef
*/
typedef uint8 Dio_LevelType;

/**
* @brief          Type of a DIO channel group representation.
*
* @implements     Dio_ChannelGroupType_struct
*/
typedef struct
{
    Dio_PortType      port;      /**< @brief Port identifier.  */
    uint8             u8offset;    /**< @brief Bit offset within the port. */
    Dio_PortLevelType mask;      /**< @brief Group mask. */
} Dio_ChannelGroupType;

/**
* @brief          Type of a DIO configuration structure.
*
* @note           In this implementation there is no need for a configuration
*                 structure there is only a dummy field, it is recommended
*                 to initialize this field to zero.
*
* @implements     Dio_ConfigType_struct
*/
typedef struct
{
    uint8 u8NumChannelGroups; /**< @brief Number of channel groups in configuration */
    const Dio_ChannelGroupType * pChannelGroupList;     /**< @brief
                                               Pointer to list of channel groups in configuration */
    const uint32 * pau32Dio_ChannelToPartitionMap;      /**< @brief Pointer to channel to partition mapping */
    const uint32 * pau32Dio_PortToPartitionMap;         /**< @brief Pointer to port to partition mapping */
} Dio_ConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/
#define DIO_START_SEC_CONST_8
#include "Dio_MemMap.h"

/**
* @brief Array of values storing the SIUL2 instance each port on the platform belongs to
*/
extern const uint8 Dio_au8PortSiul2Instance[DIO_NUM_PORTS_U16];

/**
* @brief Array of values storing the offset PORT0 has inside the SIUL2 instance it
*        belongs to
*/
extern const uint8 Dio_au8Port0OffsetInSiul2Instance[DIO_NUM_SIUL2_INSTANCES_U8];


#define DIO_STOP_SEC_CONST_8
#include "Dio_MemMap.h"

#define DIO_START_SEC_CONST_32
#include "Dio_MemMap.h"

/**
* @brief Array containing list of mapping channel for partition
*/
extern const uint32 Dio_au32ChannelToPartitionMap[DIO_CHANNEL_PARTITION_U16];

/**
* @brief Array containing list of mapping port for partition
*/
extern const uint32 Dio_au32PortToPartitionMap[DIO_PORT_PARTITION_U16];

#define DIO_STOP_SEC_CONST_32
#include "Dio_MemMap.h"

#define DIO_START_SEC_CONST_16
#include "Dio_MemMap.h"
/**
* @brief Array of bitmaps of output pins available per port
*/
extern const Dio_PortLevelType Dio_aAvailablePinsForWrite[DIO_NUM_PORTS_U16];

/**
* @brief Array of bitmaps of input pins available per port
*/
extern const Dio_PortLevelType Dio_aAvailablePinsForRead[DIO_NUM_PORTS_U16];

#define DIO_STOP_SEC_CONST_16
#include "Dio_MemMap.h"

/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif  /* DIO_CFG_H */

/** @} */
