
/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE:  IpduM_Cfg.h                                                  **
**                                                                            **
**  PRODUCT:     AUTOSAR Ipdu Multiplexer Module                              **
**                                                                            **
**  PURPOSE:     This file contain internal macros, externs etc.              **
**               API's.														  **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**  Module version :    1.0.8.0                                               **
**                                                                            ** 
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_Com.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_IpduM.arxml           
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml 
*                  Static_Code\Modules\Com_R44\generator\Com_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\IpduM_R44\generator\IpduM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef IPDUM_CFG_H
#define IPDUM_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    IPDUM_AR_RELEASE_MAJOR_VERSION                0x04u
#define    IPDUM_AR_RELEASE_MINOR_VERSION                0x04u
#define    IPDUM_AR_RELEASE_REVISION_VERSION             0x00u
#define    IPDUM_SW_MAJOR_VERSION                        0x01u
#define    IPDUM_SW_MINOR_VERSION                        0x00u
#define    IPDUM_SW_PATCH_VERSION                        0x08u
#define    IPDUM_VENDOR_ID                               0x004Cu
#define    IPDUM_MODULE_ID                               0x0034u

/*******************************************************************************
**                      Pre-compile options                                   **
*******************************************************************************/

/* Pre-compile option for Enable Module */
#define IPDUM_ENABLE_MODULE                 		STD_OFF

/* Precompile option for variant Post-Build support */
#define IPDUM_VARIANT_POSTBUILD_SUPPORT                 STD_OFF
   
/*******************************************************************************
**                     	Global Symbols                                        **
*******************************************************************************/


#endif /* IPDUM_CFG_H */

/*******************************************************************************
**                     	Symbolic Name Definition                              **
*******************************************************************************/



/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

