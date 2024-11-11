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
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           ComXf_Cfg.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file contain internal macros, externs etc.     **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  FrameWork  Version: 1.1.5                                                 **
**                                                                            **
**  Module Version: 1.0.11.1                                                   **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
*******************************************************************************/

#ifndef COMXF_CFG_H
#define COMXF_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/*include for Std_Types.h*/
#include "Std_Types.h"

/*******************************************************************************
**                       General Information                                  **
*******************************************************************************/

/* @Trace: SafeComXf_SUD_MACRO_001 */

#define COMXF_MODULE_ID                                        (175)
#define COMXF_VENDOR_ID                                        (76)
#define COMXF_INSTANCE_ID                                      (0)

#define COMXF_AR_RELEASE_MAJOR_VERSION                         (4)
#define COMXF_AR_RELEASE_MINOR_VERSION                         (4)
#define COMXF_AR_RELEASE_REVISION_VERSION                      (0)
#define COMXF_SW_MAJOR_VERSION                                 (1)
#define COMXF_SW_MINOR_VERSION                                 (0)
#define COMXF_SW_PATCH_VERSION                                 (11)

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/

/* @Trace: SafeComXf_SUD_MACRO_002 */

/******************************************************************************/
/* Description : Development Error Detection Switch                           */
/*                                                                            */
/* Range       : STD_ON, STD_OFF                                              */
/******************************************************************************/
#define COMXF_DEV_ERROR_DETECT                                 (STD_ON)

/******************************************************************************/
/* Description : Version Information Switch                                   */
/*                                                                            */
/* Range       : STD_ON, STD_OFF                                              */
/******************************************************************************/
#define COMXF_VERSION_INFORMATION                              (STD_ON)

/******************************************************************************/
/* Description : ComXf Pre-Compile Switch                                     */
/*                                                                            */
/* Range       : STD_ON, STD_OFF                                              */
/******************************************************************************/
#define COMXF_PRECOMPILE_CONFIG                                (STD_ON)

/******************************************************************************/
/* Description : ComXf Pack Info                                              */
/*                                                                            */
/* Range       :                                                              */
/******************************************************************************/
#define COMXF_PACK_INFO_COUNT                                  (1)

/******************************************************************************/
/* Description : ComXf UnPack Info                                            */
/*                                                                            */
/* Range       :                                                              */
/******************************************************************************/
#define COMXF_UNPACK_INFO_COUNT                                (1)

#endif /* COMXF_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
