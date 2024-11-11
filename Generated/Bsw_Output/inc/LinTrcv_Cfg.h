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
**  FILE-NAME: LinTrcv_Cfg.h                                                  **
**                                                                            **
**  MODULE-NAME: AUTOSAR LIN Transceiver Driver Module                        **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**  Module version    : 1.0.7.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Definition\Dio_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_LinTrcv.arxml         
*                  Configuration\Ecu\Mcal\Ecud_Dio.arxml        
*                  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\LinTrcv_R44\generator\LinTrcv_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/ 

#ifndef LINTRCV_CFG_H
#define LINTRCV_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"            /* ComStack_Types Header File*/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
/* @Trace: LinTrcv_SUD_MACRO_002 */
#define    LINTRCV_AR_RELEASE_MAJOR_VERSION              0x04u
#define    LINTRCV_AR_RELEASE_MINOR_VERSION              0x04u
#define    LINTRCV_AR_RELEASE_REVISION_VERSION           0x00u
#define    LINTRCV_SW_MAJOR_VERSION                      0x01u
#define    LINTRCV_SW_MINOR_VERSION                      0x00u
#define    LINTRCV_SW_PATCH_VERSION                      0x07u
#define    LINTRCV_VENDOR_ID                             0x004Cu
#define    LINTRCV_MODULE_ID                             0x0040u
/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/
/* @Trace: LinTrcv_SUD_MACRO_003 */


/* Pre-compile option for Development Error detection */
#define   LINTRCV_DEV_ERROR_DETECT                                      (STD_ON)

/* Pre-compile option for Version Info API */
#define   LINTRCV_GET_VERSION_INFO                                      (STD_ON)

/* Pre-compile option for Wake up supported by hardware */
#define   LINTRCV_WAKEUP_SUPPORT                                        (STD_ON)

/* Wait time for transceiver state changes in micro seconds*/
#define   LINTRCV_WAIT_TIME                                           ((uint32)50)

/* Macro for total number of LIN transceiver networks */
#define   LINTRCV_NUM_OF_NETWORKS                                           (2U)

/* Type of the Time Service Predefined Timer */
#define   LINTRCV_TIMER_TYPE                                           (STD_OFF)

/* Pre-compile option for LIN Transceiver Hardware support StandbyMode */
#define   LINTRCV_STANDBYMODE_USED                                     (STD_OFF)

/*******************************************************************************
**                      Network Handles                                       **
*******************************************************************************/
#define   LinTrcvConf_LinTrcvChannel_LIN1                             ((uint8)0)
#define   LinTrcvConf_LinTrcvChannel_LIN2                             ((uint8)1)



#endif /* LINTRCV_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/