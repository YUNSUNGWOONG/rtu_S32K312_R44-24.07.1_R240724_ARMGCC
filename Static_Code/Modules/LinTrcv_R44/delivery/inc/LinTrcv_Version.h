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
**  SRC-MODULE: LinTrcv_Version.h                                             **
**                                                                            **
**  TARGET    : MC33661                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Header file of LinTrcv_Version.c                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date              By             Description                **
********************************************************************************
** 1.0.7          08-Apr-2024       YB Song        #CP44-5981                 **
** 1.0.6          14-Mar-2024       YB Song        #CP44-3713                 **
** 1.0.5          17-May-2023       KhaLN1         #CP44-2131                 **
** 1.0.4          05-Jan-2023       TruongND18     #CP44-1198                 **
** 1.0.3          03-Aug-2022       KhaLN1         #CP44-705                  **
** 1.0.2          17-May-2022       DuyNHP2        R44-Redmine #20124 #27289  **
** 1.0.1          24-Feb-2022       SM Kwon        R44-Redmine #24795         **
** 1.0.0          22-Dec-2020       SJ Kim         Initial Version            **
*******************************************************************************/

#ifndef LINTRCV_VERSION_H
#define LINTRCV_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_PCTypes.h" /* LinTrcv configuration header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: LinTrcv_SUD_MACRO_001 */
/* LinTrcv AUTOSAR version information */
#define LINTRCV_VERSION_AR_RELEASE_MAJOR_VERSION      (4)
#define LINTRCV_VERSION_AR_RELEASE_MINOR_VERSION      (4)
#define LINTRCV_VERSION_AR_RELEASE_REVISION_VERSION   (0)

/* LINTRCV software version information */
#define LINTRCV_VERSION_SW_MAJOR_VERSION              (1)
#define LINTRCV_VERSION_SW_MINOR_VERSION              (0)
#define LINTRCV_VERSION_SW_PATCH_VERSION              (7)

/* Tm Version Check */
#if (STD_ON == LINTRCV_TIMER_TYPE)
#define LINTRCV_TM_AR_RELEASE_MAJOR_VERSION           (4)
#define LINTRCV_TM_AR_RELEASE_MINOR_VERSION           (4)
#endif

/* Det Version Check */
#if(STD_ON == LINTRCV_DEV_ERROR_DETECT)
#define LINTRCV_DET_AR_RELEASE_MAJOR_VERSION          (4)
#define LINTRCV_DET_AR_RELEASE_MINOR_VERSION          (4)
#endif

/* DIO Version Check */
#define LINTRCV_DIO_AR_RELEASE_MAJOR_VERSION          (4)
#define LINTRCV_DIO_AR_RELEASE_MINOR_VERSION_1        (2)
#define LINTRCV_DIO_AR_RELEASE_MINOR_VERSION_2        (3)
#define LINTRCV_DIO_AR_RELEASE_MINOR_VERSION_3        (4)

/* EcuM, LinIf Version Check */
#if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
#define LINTRCV_ECUM_AR_RELEASE_MAJOR_VERSION         (4)
#define LINTRCV_ECUM_AR_RELEASE_MINOR_VERSION         (4)
#define LINTRCV_LINIF_AR_RELEASE_MAJOR_VERSION        (4)
#define LINTRCV_LINIF_AR_RELEASE_MINOR_VERSION        (4)
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* LINTRCV_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
