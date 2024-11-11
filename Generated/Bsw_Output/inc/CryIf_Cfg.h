/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_Cfg.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Macro configuration data                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                          **
**                                                                            **
**  Module version : 1.0.5.0                                         **
**                                                                            **
**  Tool Version: 4.4.7                                              **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Crypto_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CryIf.arxml           
*                  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml
*                  Configuration\Ecu\Mcal\Ecud_Crypto.arxml     
*                  Configuration\System\Bswmd\Bswmd_Crypto.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml
*                  Static_Code\Modules\CryIf_R44\generator\CryIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Crypto_76_HaeModule_R44\generator\AUTOSAR_Crypto_76_HaeModule_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef CRYIF_CFG_H
#define CRYIF_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For standard types */
#include "Std_Types.h"
/* For crypto general types */
#include "Csm.h"
#include "Rte_Csm_Type.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    CRYIF_AR_RELEASE_MAJOR_VERSION                0x04U
#define    CRYIF_AR_RELEASE_MINOR_VERSION                0x04U
#define    CRYIF_AR_RELEASE_REVISION_VERSION             0x00U
#define    CRYIF_SW_MAJOR_VERSION                        0x01U
#define    CRYIF_SW_MINOR_VERSION                        0x00U
#define    CRYIF_SW_PATCH_VERSION                        0x05U
#define    CRYIF_VENDOR_ID                               0x004CU
#define    CRYIF_MODULE_ID                               0x0070U
/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
/* Enable or disable development error detection */
#define CRYIF_DEV_ERROR_DETECT                (STD_ON)

/* Enable or disable version information support */
#define CRYIF_VERSION_INFO_API                (STD_ON)

/* Total number element of key element array */
#define CRYIF_TOTAL_KEY_ELEMENT_NUMBER        ((uint32)72)

/* Total number element of channel id array */
#define CRYIF_TOTAL_CHANNEL_ID_NUMBER         ((uint32)2)

/* Total number element of key id array */
#define CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER       ((uint32)25)

/* Maximum number key element of each key id */
#define CRYIF_MAX_KEY_ELEMENT_NUMBER          ((uint8)5)

/* Maximum value of key element size */
#define CRYIF_MAX_KEY_ELEMENT_SIZE            ((uint32)260)

/* Total Crypto Driver */
#define CRYIF_TOTAL_CRYPTO_DRIVER             ((uint8)2)

#endif /* CRYIF_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
