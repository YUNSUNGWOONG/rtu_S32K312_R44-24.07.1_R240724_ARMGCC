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
**  SRC-MODULE: E2EXf_Cfg.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Transformer Module                                **
**                                                                            **
**  PURPOSE   : This file is auto generated, do not edit this file manually   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  FrameWork Version: 1.1.5                                           **
**                                                                            **
**  Module Version: 1.1.1.0                                          **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_E2EXf.arxml           
*                  Configuration\System\Bswmd\Bswmd_E2EXf.arxml 
*                  Configuration\System\DBImport\FD_CAN1.arxml  
*                  Configuration\System\Transformer\Transformer.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\E2EXf_R44\generator\E2EXf_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef E2EXF_CFG_H
#define E2EXF_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00159 */
/* @Trace: SafeE2EXf_SUD_FILE_001 */
/* @Trace: SafeE2EXf_SUD_DATATYPE_003 SafeE2EXf_SUD_DATATYPE_004 SafeE2EXf_SUD_DATATYPE_005 SafeE2EXf_SUD_DATATYPE_006 SafeE2EXf_SUD_DATATYPE_007 SafeE2EXf_SUD_DATATYPE_008 SafeE2EXf_SUD_DATATYPE_009 SafeE2EXf_SUD_DATATYPE_010 SafeE2EXf_SUD_DATATYPE_011 */

#include "E2E.h"                         /* E2E Library Header File */
/*******************************************************************************
**                      Published Information                                 **
*******************************************************************************/
/* @Trace: SafeE2EXf_SUD_MACRO_007 */
/* Module ID */
#define E2EXF_MODULE_ID                          (176)

/* Vendor ID */
#define E2EXF_VENDOR_ID                          (76)

/* AUTOSAR Specification Version Information */
#define E2EXF_AR_RELEASE_MAJOR_VERSION           (4)
#define E2EXF_AR_RELEASE_MINOR_VERSION           (4)
#define E2EXF_AR_RELEASE_REVISION_VERSION        (0)


/* Software Version Information */
#define E2EXF_SW_MAJOR_VERSION                   (1)
#define E2EXF_SW_MINOR_VERSION                   (1)
#define E2EXF_SW_PATCH_VERSION                   (0)

/*******************************************************************************
**                      Pre-compile Configuration Macros                      **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Macro is defined according to user configuration" */
/* @Trace: SafeE2EXf_SUD_MACRO_008 */

#define E2EXF_DEV_ERROR_DETECT                   (STD_ON)

#define E2EXF_INSTANCE_ID                        (0)

#define E2EXF_VERSION_INFO_API                   (STD_ON)

#define E2EXF_PRECOMPILE_CONFIG                  (STD_ON)

/* polyspace-end MISRA-C3:2.5 */

/* Window size from configuration */
#define E2EXF_WS_COM_COMISIGNALGROUP_MSGGR_E2E_FD_CAN1_BSD_01_50MS_P11    (1)
#define E2EXF_WS_COM_COMISIGNALGROUP_MSGGR_E2E_FD_CAN1_TCU_01_10MS_P11    (1)


/*******************************************************************************
**                      Provided Types                                        **
*******************************************************************************/
#define E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SafeE2EXf_SUD_DATATYPE_012 */
/* @Trace: SafeE2EXf_SUD_DATATYPE_013 */
/* @Trace: SafeE2EXf_SUD_DATATYPE_014 */
/* polyspace +1 MISRA-C3:D4.8 [Justified:Low] "Data type is defined following specification document" */
struct E2EXf_ConfigType_Tag {
  E2E_P11ConfigType PCfg_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11;
  E2E_SMConfigType SMCfg_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11;
  E2E_P11ConfigType PCfg_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11;
  E2E_SMConfigType SMCfg_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11;
};

#define E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_UNSPECIFIED
#include "MemMap.h"

#endif /* E2EXF_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
