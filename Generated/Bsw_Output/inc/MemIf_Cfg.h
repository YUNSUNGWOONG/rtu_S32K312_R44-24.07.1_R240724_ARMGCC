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
**  SRC-MODULE: MemIf_Cfg.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MEMIF                                                 **
**                                                                            **
**  PURPOSE   : Macro configuration datas                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                **
**                                                                            **
**  Module version : 1.0.4.1                                                  **
**                                                                            **
**  Tool Version: 4.4.7                                                       **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Fls_s32k312_mqfp172.epd
*                  Configuration\Ecu\Ecud_MemIf.arxml           
*                  Configuration\Ecu\Mcal\Ecud_Fee.arxml        
*                  Configuration\Ecu\Mcal\Ecud_Fls.arxml        
*                  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml 
*                  Static_Code\Modules\b_mcal_nxp_S32K3xx\b_mcal_Fee_nxp_S32K3xx\autosar\Fee.epd
*                  Static_Code\Modules\MemIf_R44\generator\MemIf_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef MEMIF_CFG_H
#define MEMIF_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "MemIf_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    MEMIF_AR_RELEASE_MAJOR_VERSION                0x04U
#define    MEMIF_AR_RELEASE_MINOR_VERSION                0x04U
#define    MEMIF_AR_RELEASE_REVISION_VERSION             0x00U
#define    MEMIF_SW_MAJOR_VERSION                        0x01U
#define    MEMIF_SW_MINOR_VERSION                        0x00U
#define    MEMIF_SW_PATCH_VERSION                        0x04U
#define    MEMIF_VENDOR_ID                               0x004CU
#define    MEMIF_MODULE_ID                               0x0016U

/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
/* Enables/Disables Development error detection */
#define MEMIF_DEV_ERROR_DETECT                              STD_ON

/* Enables/Disables GetVersionInfo API */
#define MEMIF_VERSION_INFO_API                              STD_ON

/* MemIfNumberOfDevices */
#define MEMIF_NO_OF_DEVICES                                 0x01U
/* FeeDriverIndex */
#define MEMIF_FEE_DRIVER_INDEX                              0x00U

/*******************************************************************************
**                      Initialization Structure                              **
*******************************************************************************/
#endif /* MEMIF_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
