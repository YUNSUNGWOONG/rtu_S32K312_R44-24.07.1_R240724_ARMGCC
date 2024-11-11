/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : File conatins Defination for Version.c                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date         By               Description                        **
********************************************************************************
** 1.1.6     16-Jun-2023  HieuTM8          #CP44-2100                         **
** 1.1.5     28-Apr-2023  NamNT1           CP44 #1731, 1725, 1920             **
** 1.1.4     31-Jan-2023  NamNT1           CP44 #1151, #1098, #873, #1471,    **
                                           #1560                              **
** 1.1.3     16-Dec-2022  NamNT1           BUGCLASSIC-374, CP44-1326          **
** 1.1.1     07-Oct-2022  NamNT1           CP44 #785, #786, #610, #838, #842  **
**                                         #887                               **
** 1.0.2.1   20-Jun-2022  SM Kwon          CP44-120                           **
** 1.0.2     09-May-2022  ThuanVT          R44-Redmine #25509                 **
** 1.0.1     29-Oct-2021  ThuanVT          R44-Redmine #20143                 **
** 1.0.0     16-Dec-2020  SHKim            Initial Version                    **
*******************************************************************************/

#ifndef CANNM_VERSION_H
#define CANNM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanNm_SUD_MACRO_002 */
/* AUTOSAR Specification Version Information */
#define CANNM_VERSION_AR_RELEASE_MAJOR_VERSION              (0x04u)
#define CANNM_VERSION_AR_RELEASE_MINOR_VERSION              (0x04u)
#define CANNM_VERSION_AR_RELEASE_REVISION_VERSION           (0x00u)

/* Software Version Information */
#define CANNM_VERSION_SW_MAJOR_VERSION                      (0x01u)
#define CANNM_VERSION_SW_MINOR_VERSION                      (0x02u)
#define CANNM_VERSION_SW_PATCH_VERSION                      (0x00u)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Included files AUTOSAR specification version information */
/* Expected Version information of Det module */
#define CANNM_DET_AR_MAJOR_VERSION                          (0x04u)
#define CANNM_DET_AR_MINOR_VERSION                          (0x04u)

/* Expected Version information of SchM module */
#define CANNM_SCHM_AR_MAJOR_VERSION                         (0x04u)
#define CANNM_SCHM_AR_MINOR_VERSION                         (0x04u)

/* Expected Version information of NM module */
#define CANNM_NM_AR_MAJOR_VERSION                           (0x04u)
#define CANNM_NM_AR_MINOR_VERSION                           (0x04u)

/* Expected Version information of CanIf module */
#define CANNM_CANIF_AR_MAJOR_VERSION                        (0x04u)
#define CANNM_CANIF_AR_MINOR_VERSION                        (0x04u)

/* Expected Version information of CanSM module */
#define CANNM_CANSM_AR_MAJOR_VERSION                        (0x04u)
#define CANNM_CANSM_AR_MINOR_VERSION                        (0x04u)

/* Expected Version information of PduR module */
#define CANNM_PDUR_AR_MAJOR_VERSION                         (0x04u)
#define CANNM_PDUR_AR_MINOR_VERSION                         (0x04u)

#endif /*CANNM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
