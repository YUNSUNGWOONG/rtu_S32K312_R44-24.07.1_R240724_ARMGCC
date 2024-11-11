/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           CanCM_Cfg.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Communication Manager Module            **
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
**  Framework version:   ${framework_version}                      	          **
**  Module version:      ${module_version}                                    **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanCM.arxml           
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_IoHwAb.arxml          
*                  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml 
*                  Static_Code\Modules\CanCM_R44\generator\CanCM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\IoHwAb_R44\generator\IoHwAb_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:59:03                       
*/

#ifndef CANCM_CFG_H
#define CANCM_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
/*******************************************************************************
**                     Version Information                                    **
*******************************************************************************/
/* @Trace: CanCM_SUD_MACRO_002 */
#define    CANCM_CFG_AR_RELEASE_MAJOR_VERSION            0x04u
#define    CANCM_CFG_AR_RELEASE_MINOR_VERSION            0x04u
#define    CANCM_CFG_AR_RELEASE_REVISION_VERSION         0x00u
#define    CANCM_CFG_SW_MAJOR_VERSION                    0x01u
#define    CANCM_CFG_SW_MINOR_VERSION                    0x00u
#define    CANCM_CFG_SW_PATCH_VERSION                    0x08u


/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/

#define    CANCM_AR_RELEASE_MAJOR_VERSION                0x04u
#define    CANCM_AR_RELEASE_MINOR_VERSION                0x04u
#define    CANCM_AR_RELEASE_REVISION_VERSION             0x00u
#define    CANCM_SW_MAJOR_VERSION                        0x01u
#define    CANCM_SW_MINOR_VERSION                        0x00u
#define    CANCM_SW_PATCH_VERSION                        0x08u
#define    CANCM_MODULE_ID                               0x1F6u
#define    CANCM_VENDOR_ID                               0x4Cu


/*******************************************************************************
**                      Pre-compile Options                                   **
*******************************************************************************/

/* @Trace: CanCM_SUD_MACRO_004 */

/* pre-compile option for compare criticalupper and criticallower voltage */
#define CANCM_COMPARE_CRITICAL_UPPER_AND_CRITICAL_LOWER         STD_OFF

/* pre-compile option for compare abnormalupper and abnormallower voltage */
#define CANCM_COMPARE_ABNOMAL_UPPER_AND_ABNORMAL_LOWER          STD_OFF

/* pre-compile option for checking whether CanCMBatMonConfig exist or not */
#define CANCM_BATMON_CONFIG_EXIST                               STD_ON

/* pre-compile option for the support of post-build selectable mode */
#define CANCM_VARIANT_POSTBUILD_SUPPORT                         STD_OFF

/* pre-compile option for the availability of DET module */
#define CANCM_DEV_ERROR_DETECT                                  STD_ON

/* pre-compile option for the availability of get version info API */
#define CANCM_VERSION_INFO_API                                  STD_ON

/* The pre-compile option for DEM support */
#define CANCM_DEM_STATUS                                        STD_ON

/* The pre-compile option for CanCMDisableDMOnAbnormalVoltage parameter */
#define CANCM_DISABLE_DM_ON_ABNOMAL_VOLTAGE                     STD_ON

/* The pre-compile option for CanCMWakeupSupport parameter */
#define CANCM_WAKEUP_SUPPORT                                    STD_ON

/* The pre-compile option for CanCMHysteresisSupport parameter */
#define CANCM_HYSTERESIS_SUPPORT                                STD_ON




/*******************************************************************************
**                      Channel Handles                                       **
*******************************************************************************/
/* @Trace: CanCM_SUD_MACRO_006 */
/* Channel handle for each channel */

/* The configured value of filtering constant */
#define CANCM_FILTERING_CONSTANT                                (uint8)0

/* The number of CanCM channels */
#define CANCM_NUMBER_OF_CHANNELS                                (uint8)1

/* The number of ComM channels */
#define CANCM_NUMBER_OF_COMM_CHANNELS                           (uint8)3

/* The number of ADC channels */
#define CANCM_NUMBER_OF_ADC_GROUPS                              (uint8)1

/* The largest Id of ComMChannelId mapped to CanCMChannelConfig */
#define CANCM_LAST_CHANNEL_HANDLE                               (uint8)0

/* The pre-compile option for Channel index mapping with ComM Channel Id */
#define CANCM_COM_M_CHANNEL_MAP                                 (uint8)1



/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/


#endif /* #ifndef CANCM_CFG_H */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/

