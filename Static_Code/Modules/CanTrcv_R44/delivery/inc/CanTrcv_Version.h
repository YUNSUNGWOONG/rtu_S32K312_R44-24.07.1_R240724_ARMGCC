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
**  SRC-MODULE: CanTrcv_Version.h                                             **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Header file of CanTrcv_Version.c                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.11         08-Feb-2024         Yubin Song       #CP44-3726             **
** 1.0.10         02-Jun-2023         HieuTM8          #CP44-2209             **
** 1.0.9          03-Mar-2023         HieuTM8          Update release version **
** 1.0.8          09-Dec-2022         HieuTM8          #CP44-1194             **
** 1.0.7          31-Oct-2022         HieuTM8          #CP44-1036             **
** 1.0.6          14-Oct-2022         HieuTM8          #CP44-648              **
** 1.0.5          06-Jul-2022         HjSeong          #CP44-505              **
** 1.0.4          12-May-2022         HieuTM8          Redmine #27274         **
** 1.0.3          29-Apr-2022         HieuTM8          Redmine #20079         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/
/* @Trace: SRS_BSW_00300 */
#ifndef CANTRCV_VERSION_H
#define CANTRCV_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
#include "CanTrcv.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: CanTrcv_SUD_MACRO_001 */

/* AUTOSAR Specification Version Information */
#define CANTRCV_VERSION_AR_RELEASE_MAJOR_VERSION           (4)
#define CANTRCV_VERSION_AR_RELEASE_MINOR_VERSION           (4)
#define CANTRCV_VERSION_AR_RELEASE_REVISION_VERSION        (0)
#define CANTRCV_VERSION_AR_RELEASE_MINOR_VERSION_ZERO      (0)
#define CANTRCV_VERSION_AR_RELEASE_REVISION_VERSION_THREE  (3)

/* Software Version Information */
#define CANTRCV_VERSION_SW_MAJOR_VERSION            (1)
#define CANTRCV_VERSION_SW_MINOR_VERSION            (0)
#define CANTRCV_VERSION_SW_PATCH_VERSION            (11)

/* Autosar CanIf Specification Version */
#define CANTRCV_CANIF_AR_MAJOR_VERSION              (4)
#define CANTRCV_CANIF_AR_MINOR_VERSION              (4)
#define CANTRCV_CANIF_AR_MINOR_VERSION_ZERO         (0)

/* Autosar Det Specification Version */
#define CANTRCV_DET_AR_MAJOR_VERSION                (4)
#define CANTRCV_DET_AR_MINOR_VERSION                (4)
#define CANTRCV_DET_AR_MINOR_VERSION_ZERO           (0)

/* Autosar Dem Specification Version */
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#define CANTRCV_DEM_AR_MAJOR_VERSION                (4)
#define CANTRCV_DEM_AR_MINOR_VERSION                (4)
#endif /*STD_OFF == CANTRCV_SUPPORT_AR403*/

/* Autosar Time Service Specification Version */
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_TIMER_1US16BIT)
#define CANTRCV_TM_AR_MAJOR_VERSION                 (4)
#define CANTRCV_TM_AR_MINOR_VERSION                 (4)
#endif /* (STD_ON == CANTRCV_TIMER_1US16BIT) */
#endif /*STD_OFF == CANTRCV_SUPPORT_AR403*/

/* Autosar Dio Specification Version */
#define CANTRCV_DIO_AR_MAJOR_VERSION                (4)
#define CANTRCV_DIO_AR_MINOR_VERSION_ZERO           (0) 
#define CANTRCV_DIO_AR_MINOR_VERSION_TWO            (2)
#define CANTRCV_DIO_AR_MINOR_VERSION_THREE          (3)
#define CANTRCV_DIO_AR_MINOR_VERSION_FOUR           (4)

/* Autosar Spi Specification Version */
#if (STD_ON == CANTRCV_SPI_SUPPORTED)
#define CANTRCV_SPI_AR_MAJOR_VERSION                (4)
#define CANTRCV_SPI_AR_MINOR_VERSION_ZERO           (0)
#define CANTRCV_SPI_AR_MINOR_VERSION_TWO            (2)
#define CANTRCV_SPI_AR_MINOR_VERSION_FOUR           (4)
#endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */

/* Autosar Icu Specification Version */
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_ICU_CHANNEL_USED)
#define CANTRCV_ICU_AR_MAJOR_VERSION                (4)
#define CANTRCV_ICU_AR_MINOR_VERSION                (2)
#endif /* (STD_ON == CANTRCV_ICU_CHANNEL_USED) */
#endif /* (STD_OFF == CANTRCV_SUPPORT_AR403) */

/* Autosar EcuM Specification Version */
#if ((STD_ON == CANTRCV_HW_PN_SUPPORTED) || \
  (STD_ON == CANTRCV_WAKEUP_SUPPORTED))
#define CANTRCV_ECUM_AR_MAJOR_VERSION               (4)
#define CANTRCV_ECUM_AR_MINOR_VERSION_ZERO          (0)
#define CANTRCV_ECUM_AR_MINOR_VERSION               (4)
#endif /* ((STD_ON == CANTRCV_HW_PN_SUPPORTED) || \
  (STD_ON == CANTRCV_WAKEUP_SUPPORTED)) */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANTRCV_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
