
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE:           CanTrcv_Cfg.h                                       **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Tranceiver Module                       **
**                                                                            **
**  PURPOSE   :           This file contain internal macros, externs etc.     **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**                                                                            **
**  Module version :    1.0.11.0                                              **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Dio_s32k312_mqfp172.epd
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Mcal\Ecud_Dio.arxml        
*                  Configuration\System\Bswmd\Bswmd_Dio.arxml   
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/


#ifndef CANTRCV_CFG_H
#define CANTRCV_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for CanTrcv Config Header */
#include "ComStack_Types.h"


/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_MACRO_002 */
#define    CANTRCV_AR_RELEASE_MAJOR_VERSION              0x04u
#define    CANTRCV_AR_RELEASE_MINOR_VERSION              0x04u
#define    CANTRCV_AR_RELEASE_REVISION_VERSION           0x00u
#define    CANTRCV_SW_MAJOR_VERSION                      0x01u
#define    CANTRCV_SW_MINOR_VERSION                      0x00u
#define    CANTRCV_SW_PATCH_VERSION                      0x0Bu
#define    CANTRCV_VENDOR_ID                             0x004Cu
#define    CANTRCV_MODULE_ID                             0x0047u

/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
/* Pre-compile option for using R40 */
#define CANTRCV_SUPPORT_AR403                           (STD_OFF)

/* Pre-compile option for Post-Build Support */
#define CANTRCV_POSTBUILD_SUPPORTED                     (STD_OFF)

/* Pre-compile option for Dev Error Detect */
#define CANTRCV_DEV_ERROR_DETECT                        (STD_ON)

/* Pre-compile option for Get Version Info */
#define CANTRCV_GET_VERSION_INFO                        (STD_ON)

/* Pre-compile option for Wakeup Support */
#define CANTRCV_WAKEUP_SUPPORTED                        (STD_ON)

/* Pre-compile option for ARISU-CAN support */
#define CANTRCV_ARISUCAN_SUPPORTED                      (STD_OFF)

/* Pre-compile option for ARISU PWM AUTO support */
#define CANTRCV_ARISU_PWM_AUTO                          (STD_OFF)

/* Pre-compile option for HW PN Support */
#define CANTRCV_HW_PN_SUPPORTED                         (STD_ON)

/* Pre-compile option for PN Enable */
#define CANTRCV_PN_SUPPORTED                            (STD_OFF)

/* Pre-compile option for ICU channel used */
#define CANTRCV_ICU_CHANNEL_USED                        (STD_OFF)

/* Pre-complie option for timer type */
#define CANTRCV_TIMER_1US16BIT                          (STD_OFF)

/* Pre-compile option for device XJA11XX support */
#define CANTRCV_XJA11XX_SUPPORTED                       (STD_OFF)

/* Pre-compile option for TLE9255W support */
#define CANTRCV_TLE9255W_SUPPORTED                      (STD_OFF)

/* Pre-compile option for device TCAN1145 support */
#define CANTRCV_TCAN1145_SUPPORTED                      (STD_OFF)

/* Pre-compile option for device TCAN1043A support */
#define CANTRCV_TCAN1043A_SUPPORTED                     (STD_OFF)

/* Pre-compile option for Power On Flag */
#define CANTRCV_HW_POR_SUPPORTED                        (STD_OFF)

/* Pre-compile option for SPI Support */
#define CANTRCV_SPI_SUPPORTED                           (STD_OFF)

/* Pre-compile option for using SPI Less than AR42 */
#define CANTRCV_SPI_LESS_AR42                           (STD_OFF) 

/* Pre-compile option for DEM event support */
#define CANTRCV_E_BUS_ERROR_SUPPORTED                   (STD_OFF)

/* Pre-compile option for check channel used */
#define CANTRCV_CHANNEL_USED                            (STD_ON)

/* Pre-compile option for check all channel used */
#define CANTRCV_CHANNEL_USED_ALL                        (STD_ON)

/* Pre-compile option for check channel init mode is NORMAL */
#define CANTRCV_CHANNELS_INIT_MODE_NORMAL               (STD_OFF)

/* Pre-compile option for check all channel init mode is NORMAL */
#define CANTRCV_CHANNELS_INIT_MODE_ALL_NORMAL           (STD_OFF)

/* Pre-compile option for check channel init mode is STANDBY */
#define CANTRCV_CHANNELS_INIT_MODE_STANDBY              (STD_ON)

/* Pre-compile option for check all channel init mode is STANDBY */
#define CANTRCV_CHANNELS_INIT_MODE_ALL_STANDBY          (STD_ON)

/* Pre-compile option for check channel init mode is SLEEP */
#define CANTRCV_CHANNELS_INIT_MODE_SLEEP                (STD_OFF)

/* Pre-compile option for check all channel init mode is SLEEP */
#define CANTRCV_CHANNELS_INIT_MODE_ALL_SLEEP            (STD_OFF)

/* Pre-compile option for check devices have support sleep mode */
#define CANTRCV_HW_SUPPORT_SLEEP_MODE                   (STD_ON)

/* Pre-compile option for check channel's hardware used STB, EN */
#define CANTRCV_HW_SUPPORT_WAKEUP_USED_STB_EN_PIN       (STD_ON)

/* Pre-compile option for check channel's hardware used STB */
#define CANTRCV_ALL_HW_SUPPORT_WAKEUP_USED_STB_PIN      (STD_OFF)

/* Pre-compile option for check devices which have support wake up */
#define CANTRCV_ALL_HW_SUPPORT_WAKEUP                   (STD_ON)

/* Pre-compile option for check and perform wake up events */
#define CANTRCV_ALL_HW_SUPPORT_WAKEUP_EVENT             (STD_ON)

/* Pre-compile option for check channel's hardware is configued TJA1041/TJA1043/TJA1463/TJA1041A */
#define CANTRCV_HW_DIO_SUPPORT_SLEEP_MODE               (STD_ON)

/* Pre-compile option for check Transceiver has EN/STB control pin */
#define CANTRCV_HW_USED_EN_STB_CONTROL_PIN              (STD_ON)

/* Pre-compile option for check sleep Mode Used for channel */
#define CANTRCV_SLEEP_MODE_USED                         (STD_OFF)

/* Pre-compile option for check channel used pn network */
#define CANTRCV_CHANNEL_USED_PN_NETWORK                 (STD_OFF)

/* Pre-compile option for SPI asynctransmit support */
#define CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED             (STD_OFF)

/*******************************************************************************
**                           MACROS                                           **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_MACRO_005 */
        

/* Pre-compile option for Number Of Networks */
#define CANTRCV_NUM_OF_NETWORKS                         ((uint8)1)

/* Pre-compile option for Number Of CanTrcv Networks */
#define CANTRCV_NUM_OF_PARTIALNETWORKS                  ((uint8)0)

/* Pre-compile option for Waitime Count */
#define CANTRCV_WAIT_TIME                               ((uint32)200)

/* Pre-compile option for TCAN1043A Waitime Count */
#if(CANTRCV_TCAN1043A_SUPPORTED == STD_ON)
#if(CANTRCV_SUPPORT_AR403 == STD_ON)
#define CANTRCV_TCAN1043A_WAIT_COUNT ((uint32)0)
#else
#define CANTRCV_TCAN1043A_WAIT_TIME               ((uint32)20)
#endif
#endif

#define CANTRCV_MAIN_FUNCTION_DIAG_PERIOD               ((uint32)0)

#define CANTRCV_MAIN_FUNCTION_PERIOD                    ((uint32)5)



/* Instance ID */
#define CANTRCV_INSTANCE_ID                             ((uint8)0)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00413 SRS_BSW_00347 */
/* API Name for global initialization */
#define CANTRCV_INIT_MACRO                     (CanTrcv_Init)

/* API Name for version info */
#define CANTRCV_GETVERSIONINFO_MACRO           (CanTrcv_GetVersionInfo)

/* API Name for set operation mode */
#define CANTRCV_SETOPMODE_MACRO                (CanTrcv_SetOpMode)

/* API Name for get operation mode */
#define CANTRCV_GETOPMODE_MACRO                (CanTrcv_GetOpMode)

/* API Name for de-initialization */
#define CANTRCV_DEINIT_MACRO                   (CanTrcv_DeInit)

/* API Name for check wake up  */
#define CANTRCV_CHECKWAKEUP_MACRO              (CanTrcv_CheckWakeup)

/* API Name for  get bus wake up reason */
#define CANTRCV_GETBUSWUREASON_MACRO           (CanTrcv_GetBusWuReason)

/* API Name for set wake up mode */
#define CANTRCV_SETWAKEUPMODE_MACRO            (CanTrcv_SetWakeupMode)

/* API name for schedule processing of main function */
#define CANTRCV_MAINFUNCTION_MACRO             (CanTrcv_MainFunction)

/* API Name for get system data  */
#define CANTRCV_GETTRCVSYSTEMDATA_MACRO        (CanTrcv_GetTrcvSystemData)

/* API Name for check wake up flag */
#define CANTRCV_CHECKWAKEFLAG_MACRO            (CanTrcv_CheckWakeFlag)

/* API Name for read transceiver timeout flag  */
#define CANTRCV_READTRCVTIMEOUTFLAG_MACRO      (CanTrcv_ReadTrcvTimeoutFlag)

/* API Name for clear transceiver timeout flag  */
#define CANTRCV_CLEARTRCVTIMEOUTFLAG_MACRO     (CanTrcv_ClearTrcvTimeoutFlag)

/* API Name for read transceiver silence flag  */
#define CANTRCV_READTRCVSILENCEFLAG_MACRO      (CanTrcv_ReadTrcvSilenceFlag)

/* API Name for clear wake up frame flag  */
#define CANTRCV_CLEARTRCVWUFFLAG_MACRO         (CanTrcv_ClearTrcvWufFlag)

#define CANTRCV_SETPNACTIVATIONSTATE_MACRO     (CanTrcv_SetPNActivationState)



#endif  /* CANTRCV_CFG_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
