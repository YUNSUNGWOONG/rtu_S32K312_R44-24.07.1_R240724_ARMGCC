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
**  SRC-MODULE: PduR_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : C header for PduR_Version                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.9     11-Jul-2023   HaoTA4      CP44-1827                              **
** 1.0.8     16-Dec-2022   HaoTA4      CP44-1364                              **
** 1.0.6     06-Dec-2022   HaoTA4      CP44-1252                              **
** 1.0.4     13-Oct-2022   PhucNHM     CP44-803                               **
** 1.0.4     11-Aug-2022   PhucNHM     CP44-635                               **
** 1.0.3     07-Dec-2021   PhucNHM     R44-Redmine #22235                     **
** 1.0.2     05-Oct-2021   PhucNHM     R44-Redmine #20586                     **
** 1.0.1     17-Sep-2021   PhucNHM     R44-Redmine #20304                     **
** 1.0.0     04-Dec-2020   AUTOEVER    Initial Version                        **
*******************************************************************************/
#ifndef PDUR_VERSION_H
#define PDUR_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* @Traceability BEGIN -- SRS: SWS_PduR_00762 */
/* @Trace: SRS_BSW_00318 */
/* @Trace: SRS_BSW_00003 */
/* @Trace: SRS_BSW_00384 */
/* @Trace: PduR_SUD_MACRO_006 */
/* AUTOSAR Specification Version Information */
#define PDUR_VERSION_AR_RELEASE_MAJOR_VERSION       4
#define PDUR_VERSION_AR_RELEASE_MINOR_VERSION       4
#define PDUR_VERSION_AR_RELEASE_REVISION_VERSION    0
/* @Traceability END -- SRS: SWS_PduR_00762 */
/* Software Version Information */
#define PDUR_VERSION_SW_MAJOR_VERSION               1
#define PDUR_VERSION_SW_MINOR_VERSION               0
#define PDUR_VERSION_SW_PATCH_VERSION               9

/* Other (Lower) module version information */
#if (PDUR_CANIF_SUPPORT == STD_ON)
#define PDUR_CANIF_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_CANIF_AR_RELEASE_MINOR_VERSION         4
#endif

#if (PDUR_LINIF_SUPPORT == STD_ON)
#define PDUR_LINIF_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_LINIF_AR_RELEASE_MINOR_VERSION         4
#endif

#if (PDUR_FRIF_SUPPORT == STD_ON)
#define PDUR_FRIF_AR_RELEASE_MAJOR_VERSION          4
#define PDUR_FRIF_AR_RELEASE_MINOR_VERSION          4
#endif

#if (PDUR_SOAD_SUPPORT == STD_ON)
#define PDUR_SOAD_AR_RELEASE_MAJOR_VERSION          4
#define PDUR_SOAD_AR_RELEASE_MINOR_VERSION          4
#endif

#if (PDUR_CANNM_SUPPORT == STD_ON)
#define PDUR_CANNM_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_CANNM_AR_RELEASE_MINOR_VERSION         4
#endif

#if (PDUR_FRNM_SUPPORT == STD_ON)
#define PDUR_FRNM_AR_RELEASE_MAJOR_VERSION          4
#define PDUR_FRNM_AR_RELEASE_MINOR_VERSION          4
#endif

#if (PDUR_UDPNM_SUPPORT == STD_ON)
#define PDUR_UDPNM_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_UDPNM_AR_RELEASE_MINOR_VERSION         4
#endif

/* Other (Both Upper and Lower) module version information */
#if (PDUR_SECOC_SUPPORT == STD_ON)
#define PDUR_SECOC_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_SECOC_AR_RELEASE_MINOR_VERSION         4
#endif

#if (PDUR_SOMEIPTP_SUPPORT == STD_ON)
#define PDUR_SOMEIPTP_AR_RELEASE_MAJOR_VERSION      4
#define PDUR_SOMEIPTP_AR_RELEASE_MINOR_VERSION      4
#endif

#if (PDUR_IPDUM_SUPPORT == STD_ON)
#define PDUR_IPDUM_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_IPDUM_AR_RELEASE_MINOR_VERSION         4
#endif

/* Other (Transport Protocol) module version information */
#if (PDUR_CANTP_SUPPORT == STD_ON)
#define PDUR_CANTP_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_CANTP_AR_RELEASE_MINOR_VERSION         4
#endif

#if (PDUR_FRTP_SUPPORT == STD_ON)
#define PDUR_FRTP_AR_RELEASE_MAJOR_VERSION          4
#define PDUR_FRTP_AR_RELEASE_MINOR_VERSION          4
#endif

#if (PDUR_J1939TP_SUPPORT == STD_ON)
#define PDUR_J1939TP_AR_RELEASE_MAJOR_VERSION       4
#define PDUR_J1939TP_AR_RELEASE_MINOR_VERSION       4
#endif

#if (PDUR_DOIP_SUPPORT == STD_ON)
#define PDUR_DOIP_AR_RELEASE_MAJOR_VERSION          4
#define PDUR_DOIP_AR_RELEASE_MINOR_VERSION          4
#endif

/* Other (Upper Layer) module version information */
#if (PDUR_COM_SUPPORT == STD_ON)
#define PDUR_COM_AR_RELEASE_MAJOR_VERSION           4
#define PDUR_COM_AR_RELEASE_MINOR_VERSION           4
#endif

#if (PDUR_DCM_SUPPORT == STD_ON)
#define PDUR_DCM_AR_RELEASE_MAJOR_VERSION           4
#define PDUR_DCM_AR_RELEASE_MINOR_VERSION           4
#endif

#if (PDUR_LDCOM_SUPPORT == STD_ON)
#define PDUR_LDCOM_AR_RELEASE_MAJOR_VERSION         4
#define PDUR_LDCOM_AR_RELEASE_MINOR_VERSION         4
#endif

#if (PDUR_DLT_SUPPORT == STD_ON)
#define PDUR_DLT_AR_RELEASE_MAJOR_VERSION           4
#define PDUR_DLT_AR_RELEASE_MINOR_VERSION           4
#endif

#if (PDUR_J1939RM_SUPPORT == STD_ON)
#define PDUR_J1939RM_AR_RELEASE_MAJOR_VERSION       4
#define PDUR_J1939RM_AR_RELEASE_MINOR_VERSION       4
#endif

#if (PDUR_J1939DCM_SUPPORT == STD_ON)
#define PDUR_J1939DCM_AR_RELEASE_MAJOR_VERSION      4
#define PDUR_J1939DCM_AR_RELEASE_MINOR_VERSION      4
#endif

#if (PDUR_ETHDIAG_SUPPORT == STD_ON)
#define PDUR_ETHDIAG_AR_RELEASE_MAJOR_VERSION       4
#define PDUR_ETHDIAG_AR_RELEASE_MINOR_VERSION       4
#endif

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_DET_AR_RELEASE_MAJOR_VERSION           4
#define PDUR_DET_AR_RELEASE_MINOR_VERSION           4
#endif

#endif /* PDUR_VERSION_H */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
