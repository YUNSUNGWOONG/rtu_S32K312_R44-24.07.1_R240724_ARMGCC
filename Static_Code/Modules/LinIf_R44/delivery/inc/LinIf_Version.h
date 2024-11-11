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
**  SRC-MODULE: LinIf_Version.h                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : C header for LinIf_Version                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By              Description                      **
********************************************************************************
** 1.0.15      01-Mar-2024   JH Jang         #CP44-5060, #CP44-5062           **
** 1.0.14      20-Sep-2023   DH Choi         #BUGCLASSIC-711                  **
** 1.0.13      15-Aug-2023   KhaLN1          #CP44-2673                       **
** 1.0.12      30-Jun-2023   JH Jang         #CP44-2409, 2410                 **
** 1.0.11      07-Apr-2023   KhaLN1          #CP44-1917                       **
** 1.0.10      07-Mar-2023   KhaLN1          #CP44-1811                       **
** 1.0.9       06-Feb-2023   KhaLN1          #CP44-1626                       **
** 1.0.8       04-Dec-2022   KhaLN1          #CP44-1191                       **
** 1.0.7       03-Nov-2022   KhaLN1          #CP44-1100                       **
** 1.0.6       26-Oct-2022   KhaLN1          #CP44-884 #CP44-563 #CP44-861    **
** 1.0.5       03-Aug-2022   KhaLN1          #CP44-513                        **
** 1.0.4       03-Jun-2022   HJ Seong        R44-Redmine #27098               **
** 1.0.3       25-Apr-2021   DuyNHP2         R44-Redmine #26480               **
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.2       28-Feb-2022   HJ Seong        R44-Redmine #24836               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/
#ifndef LINIF_VERSION_H
#define LINIF_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinIf.h"        /* LIN Interface Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: LinIf_SUD_MACRO_003 */
/* AUTOSAR Specification Version Information */
#define LINIF_VERSION_AR_RELEASE_MAJOR_VERSION     4
#define LINIF_VERSION_AR_RELEASE_MINOR_VERSION     4
#define LINIF_VERSION_AR_RELEASE_REVISION_VERSION  0

/* Software Version Information */
#define LINIF_VERSION_SW_MAJOR_VERSION      1
#define LINIF_VERSION_SW_MINOR_VERSION      0
#define LINIF_VERSION_SW_PATCH_VERSION      15

#define LINIF_LINSM_AR_RELEASE_MAJOR_VERSION    4
#define LINIF_LINSM_AR_RELEASE_MINOR_VERSION    4

#define LINIF_PDUR_AR_RELEASE_MAJOR_VERSION     4
#define LINIF_PDUR_AR_RELEASE_MINOR_VERSION     4

#if(LINIF_DEV_ERROR_DETECT == STD_ON)
#define LINIF_DET_AR_RELEASE_MAJOR_VERSION      4
#define LINIF_DET_AR_RELEASE_MINOR_VERSION      4
#endif

#if(LINIF_MULTIPLE_DRIVER_SUPPORT == STD_OFF)
#define LINIF_LIN_AR_RELEASE_MAJOR_VERSION_4      4
#define LINIF_LIN_AR_RELEASE_MINOR_VERSION_4      4
#define LINIF_LIN_AR_RELEASE_MINOR_VERSION_7      7
#define LINIF_LIN_AR_RELEASE_MINOR_VERSION_3      3
#define LINIF_LIN_AR_RELEASE_MINOR_VERSION_2      2
#endif

#define LINIF_RTE_AR_RELEASE_MAJOR_VERSION      4
#define LINIF_RTE_AR_RELEASE_MINOR_VERSION      4
#if(LINTP_SUPPORT == STD_ON)
#define LINIF_BSWM_AR_RELEASE_MAJOR_VERSION     4
#define LINIF_BSWM_AR_RELEASE_MINOR_VERSION     4
#endif

#if ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && \
  (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_OFF))
#define LINIF_LINTRCV_AR_RELEASE_MAJOR_VERSION  4
#define LINIF_LINTRCV_AR_RELEASE_MINOR_VERSION  4
#endif

#if (LINIF_CDD_SUPPORT == STD_ON)
#define LINIF_CDD_AR_RELEASE_MAJOR_VERSION     4
#define LINIF_CDD_AR_RELEASE_MINOR_VERSION     4
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* LINIF_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
