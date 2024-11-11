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
**  SRC-MODULE: LinSM_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : C header for LinSM_Version                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.9          24-Aug-2023           KhaLN1           #CP44-2812           **
** 1.0.8          05-Jul-2023           KhaLN1           #CP44-2522           **
** 1.0.7          27-Mar-2023           KhaLN1           #CP44-1882           **
** 1.0.6          25-Nov-2022           TruongND18       #CP44-1089           **
** 1.0.5.1        25-Oct-2022           KhaLN1           #CP44-750            **
** 1.0.5          04-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINSM_VERSION_H
#define LINSM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM_Cfg.h"            /* LinSM configuration header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define LINSM_VERSION_C_AR_RELEASE_MAJOR_VERSION    4
#define LINSM_VERSION_C_AR_RELEASE_MINOR_VERSION    4
#define LINSM_VERSION_C_AR_RELEASE_REVISION_VERSION 0

/* Software Version Information */
#define LINSM_VERSION_C_SW_MAJOR_VERSION            1
#define LINSM_VERSION_C_SW_MINOR_VERSION            0
#define LINSM_VERSION_C_SW_PATCH_VERSION            9

/* AUTOSAR Specification Version Information */
#define LINSM_VERSION_AR_RELEASE_MAJOR_VERSION (LINSM_AR_RELEASE_MAJOR_VERSION)
#define LINSM_VERSION_AR_RELEASE_MINOR_VERSION (LINSM_AR_RELEASE_MINOR_VERSION)
#define LINSM_VERSION_AR_RELEASE_REVISION_VERSION\
  (LINSM_AR_RELEASE_REVISION_VERSION)
/* Software Version Information */
#define LINSM_VERSION_SW_MAJOR_VERSION         (LINSM_SW_MAJOR_VERSION)
#define LINSM_VERSION_SW_MINOR_VERSION         (LINSM_SW_MINOR_VERSION)
#define LINSM_VERSION_SW_PATCH_VERSION         (LINSM_SW_PATCH_VERSION)

/* LinIf Version Information */
#define LINSM_LINIF_AR_RELEASE_MAJOR_VERSION   4
#define LINSM_LINIF_AR_RELEASE_MINOR_VERSION   4

/* ComM Version Information */
#define LINSM_COMM_AR_RELEASE_MAJOR_VERSION    4
#define LINSM_COMM_AR_RELEASE_MINOR_VERSION    4

/* BswM Version Information */
#define LINSM_BSWM_AR_RELEASE_MAJOR_VERSION    4
#define LINSM_BSWM_AR_RELEASE_MINOR_VERSION    4

/* Com Version Information */
#define LINSM_COM_AR_RELEASE_MAJOR_VERSION     4
#define LINSM_COM_AR_RELEASE_MINOR_VERSION     0

/* Det Version Information */
#if (LINSM_DEV_ERROR_DETECT == STD_ON)
#define LINSM_DET_AR_RELEASE_MAJOR_VERSION     4
#define LINSM_DET_AR_RELEASE_MINOR_VERSION     4
#endif

/* Rte Version Information */
#define LINSM_RTE_AR_RELEASE_MAJOR_VERSION     4
#define LINSM_RTE_AR_RELEASE_MINOR_VERSION     4

#endif /* LINSM_VERSION_H */

/*******************************************************************************
**                            Global Data                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
