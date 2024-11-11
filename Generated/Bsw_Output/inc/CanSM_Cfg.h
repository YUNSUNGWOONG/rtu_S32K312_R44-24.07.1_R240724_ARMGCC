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
**  SRC-MODULE: CanSM_Cfg.h                                                   **
**                                                                            **                                        
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : This file contain generated macros                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
**                                                                            **
********************************************************************************
********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version: 1.1.5                                                  **
**  Module version:    1.0.9.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_Com.arxml             
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml 
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef CANSM_CFG_H
#define CANSM_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"
#include "Std_Types.h"


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    CANSM_CFG_AR_RELEASE_MAJOR_VERSION            0x04u
#define    CANSM_CFG_AR_RELEASE_MINOR_VERSION            0x04u
#define    CANSM_CFG_AR_RELEASE_REVISION_VERSION         0x00u
#define    CANSM_CFG_SW_MAJOR_VERSION                    0x01u
#define    CANSM_CFG_SW_MINOR_VERSION                    0x00u
#define    CANSM_CFG_SW_PATCH_VERSION                    0x09u
/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    CANSM_AR_RELEASE_MAJOR_VERSION                0x04u
#define    CANSM_AR_RELEASE_MINOR_VERSION                0x04u
#define    CANSM_AR_RELEASE_REVISION_VERSION             0x00u
#define    CANSM_SW_MAJOR_VERSION                        0x01u
#define    CANSM_SW_MINOR_VERSION                        0x00u
#define    CANSM_SW_PATCH_VERSION                        0x09u
#define    CANSM_VENDOR_ID                               0x004Cu
#define    CANSM_MODULE_ID                               0x008Cu
/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_010 */
/* Pre-compile option for Development error detection */
#define CANSM_DEV_ERROR_DETECT                          (STD_ON)

/* Pre-compile option for CanSM Version Info API */
#define CANSM_VERSION_INFO_API                          (STD_ON)

/* Pre-compile option for baudrating setting  */
#define CANSM_SET_BAUDRATE_API                          (STD_OFF)

/* Pre-compile option for Bus off recovery support */
#define CANSM_BUSOFF_RECOVERY_MACRO_SUPPORT             (STD_OFF)

/* Pre-compile option for bor counter support */
#define CANSM_BOR_COUNTER_MACRO_SUPPORT                 (STD_OFF)

/*  Pre-Compile option shall be used to Enable/Disable PN mode */
#define CANSM_PNC_AVAILABILITY                          (STD_ON)

/* Pre-compile option for the support of ECU passive */
#define CANSM_TX_OFFLINE_ACTIVE_SUPPORT                 (STD_OFF)

/* Pre-compile option for the support of pretended Network */
#define CANSM_ICOM_SUPPORT                              (STD_OFF)

/* Pre-compile option if given configuration is for Post-Build */
#define CANSM_VARIANT_POSTBUILD_SUPPORT                 (STD_OFF)

/*  Pre-Compile option for DemStatus */
#define CANSM_DEM_STATUS                                (STD_ON)

/* Pre-compile option for CanSM Transreceiver support */
#define CANSM_CANTRCV_SUPPORT                           (STD_ON)

/* Pre-compile option for CanSM User Timeout support */
#define CANSM_USER_TIMEOUT_SUPPORT                      (STD_OFF)

/*  Pre-Compile option for Enable Bus Off delay */
#define CANSM_ENABLE_BUS_OFF_DELAY                      (STD_OFF)

/* Pre-compile option for Enabling/Disabling Polling mode */
#define CANSM_BOR_TX_CONFIRMATION_POLLING               (STD_OFF)

/* Pre-compile option for the number of CanSM Configurations */
#define CANSM_NUMBER_OF_CONFIGURATION                   (1)

/* Pre-compile option for the number of static networks */
#define CANSM_NUMBER_OF_STATIC_NWS                      (1)

/* Pre-compile option for CanSM Highest Transceiver Channel Id */
#define CANSM_LAST_TRCV_HANDLE                          (0)

/* Pre-compile option for CanSM last network handle */
#define CANSM_LAST_NW_HANDLE                            (0)

/* Pre-compile option for the biggest CanIfControllerId configured in CanSM Configurations */
#define CANSM_LAST_CTRL_HANDLE                          (0)

/* Pre-compile option for the number of CanSMControllers in all configurations */
#define CANSM_NUMBER_OF_STATIC_CTRL                     (1)


/*******************************************************************************
**                      Type Definition                                       **
*******************************************************************************/
        
/* Type definition for CanSM_TimerType */
typedef uint16 CanSM_TimerType;

/* Type definition for CanSM_BusOffCntType */
typedef uint8 CanSM_BusOffCntType;


/*******************************************************************************
**                      Internal Macros                                       **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_011 */
#endif /* #ifndef CANSM_CFG_H */
/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/

