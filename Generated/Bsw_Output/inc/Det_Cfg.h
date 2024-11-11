/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  FILE-NAME: Det_Cfg.h                                                      **
**                                                                            **
**  MODULE-NAME: AUTOSAR DET Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                          **
**  Module version : 1.0.1.2                                         **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/


 /*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_Det.arxml             
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml   
*                  Static_Code\Modules\Det_R44\generator\Det_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef DET_CFG_H
#define DET_CFG_H




/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"



/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    DET_AR_RELEASE_MAJOR_VERSION                  0x04u
#define    DET_AR_RELEASE_MINOR_VERSION                  0x04u
#define    DET_AR_RELEASE_REVISION_VERSION               0x00u
#define    DET_SW_MAJOR_VERSION                          0x01u
#define    DET_SW_MINOR_VERSION                          0x00u
#define    DET_SW_PATCH_VERSION                          0x00u
#define    DET_VENDOR_ID                                 0x004Cu
#define    DET_MODULE_ID                                 0x000Fu
/*******************************************************************************
**                      Pre-compile Macros                                    **
*******************************************************************************/

/* To enable / disable development error detection */
#define    DET_FORWARD_TO_DLT                            STD_OFF


/* To enable / disable the Ea_GetVersionInfo API */
#define    DET_VERSION_INFO_API                          STD_ON


/* To enable / disable the notification functions in the Error Runtime */
#define    DET_ERROR_HOOK                                STD_ON


/* Total number of Error Hooks configured */
#define    DET_TOTAL_ERROR_HOOKS                         (uint8)1


/*To enable / disable the notification functions in the DET Error Runtime */
#define    DET_ERROR_RUNTIME                             STD_OFF


/* Total number of Error Runtime configured */
#define    DET_TOTAL_ERROR_RUNTIME                       (uint8)0


/* To enable / disable the notification functions in the Transient Fault */
#define    DET_ERROR_FAULT_TRANSIENT                     STD_OFF


/* Total number of Transient Fault configured */
#define    DET_TOTAL_ERROR_FAULT_TRANSIENT               (uint8)0


/* To enable / disable the Ram Buffer Storage */
#define    DET_RAM_BUFFER                                STD_ON


/* The Ram Buffer Storage Size */
#define    DET_RAM_BUFFER_SIZE                           (uint8)255


extern Std_ReturnType Det_ErrorHook 
			(uint16 LusModuleId, uint8 LucInstanceId, uint8 LucApiId, uint8 LucErrorId);





#endif /* Det_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
