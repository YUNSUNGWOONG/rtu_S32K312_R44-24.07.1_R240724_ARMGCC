/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Define all version information of dependent module            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.1.0   20-Mar-2021        TamTV6       Add trace SUD                    **
** 1.0.2     09-Nov-2021        TamTV6       Implement #20952                 **
** 1.0.3.0   12-Aug-2022        DienTC1      #595                             **
** 1.0.4.0   01-Dec-2022        DienTC1      #CP44-996 
** 1.0.5.0   02-Mar-2022        PhuocLH9      #CP44-1745                       **
*******************************************************************************/

#ifndef CRYIF_VERSION_H
#define CRYIF_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* For generated code version */
#include "CryIf.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: CryIf_SUD_MACRO_001 */
/* AUTOSAR Specification Version Information */
#define CRYIF_VERSION_AR_RELEASE_MAJOR_VERSION          (0x04U)
#define CRYIF_VERSION_AR_RELEASE_MINOR_VERSION          (0x04U)
#define CRYIF_VERSION_AR_RELEASE_REVISION_VERSION       (0x00U)

/* Software Version Information */
#define CRYIF_VERSION_SW_MAJOR_VERSION                  (0x01U)
#define CRYIF_VERSION_SW_MINOR_VERSION                  (0x00U)
#define CRYIF_VERSION_SW_PATCH_VERSION                  (0x05U)

/* @Trace: CryIf_SUD_MACRO_003 */
/* If development error detection is enabled */
#if (STD_ON == CRYIF_DEV_ERROR_DETECT)
  #define CRYIF_DET_AR_RELEASE_MAJOR_VERSION            (0x04U)
  #define CRYIF_DET_AR_RELEASE_MINOR_VERSION_L          (0x00U)
  #define CRYIF_DET_AR_RELEASE_MINOR_VERSION_U          (0x04U)
#endif

#define CRYIF_CSM_AR_RELEASE_MAJOR_VERSION              (0x04U)
#define CRYIF_CSM_AR_RELEASE_MINOR_VERSION              (0x04U)

#endif /* CRYIF_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
