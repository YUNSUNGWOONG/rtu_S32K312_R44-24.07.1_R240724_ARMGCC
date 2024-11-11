/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM                                                   **
**                                                                            **
**  PURPOSE   : Header for Com_Version.c                                      **
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
** 1.1.11.0  10-Oct-2023   PhucNHM     CP44-2759                              **
** 1.1.10.0  05-May-2023   PhucNHM     CP44-2094                              **
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.8.0   15-Feb-2023   PhucNHM     CP44-1599 CP44-1600                    **
** 1.1.7.0   07-Dec-2022   PhucNHM     CP44-1362                              **
** 1.1.6.0   07-Dec-2022   PhucNHM     Com_R44-1.1.6.0 update version         **
** 1.1.5.0   04-Oct-2022   PhucNHM     CP44-769                               **
** 1.1.4     02-Jun-2022   DuyNHP2     R44-Redmine #27636                     **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.3     17-May-2022   SMKwon      R44-Redmine #27173                     **
** 1.1.2     13-Apr-2022   PhucNHM     R44-Redmine #25516 #24777 #25517       **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
#ifndef COM_VERSION_H
#define COM_VERSION_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: Com_SUD_MACRO_001 */
/* AUTOSAR Specification Version Information */
#define COM_VERSION_AR_RELEASE_MAJOR_VERSION  4
#define COM_VERSION_AR_RELEASE_MINOR_VERSION  4
#define COM_VERSION_AR_RELEASE_REVISION_VERSION  0

/* Software Version Information */
#define COM_VERSION_SW_MAJOR_VERSION  1
#define COM_VERSION_SW_MINOR_VERSION  1
#define COM_VERSION_SW_PATCH_VERSION  11


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: Com_SUD_MACRO_005 */
/* Autosar Det Specification Version */
#define COM_DET_AR_RELEASE_MAJOR_VERSION        4
#define COM_DET_AR_RELEASE_MINOR_VERSION        4

/* @Trace: Com_SUD_MACRO_006 */
/* Autosar PduR Specification Version */
#define COM_PDUR_AR_RELEASE_MAJOR_VERSION       4
#define COM_PDUR_AR_RELEASE_MINOR_VERSION       4

/* @Trace: Com_SUD_MACRO_007 */
/* Autosar Rte Specification Version */
#define COM_RTE_AR_RELEASE_MAJOR_VERSION        4
#define COM_RTE_AR_RELEASE_MINOR_VERSION        4

/* Autosar PduR Specification Version */
#define COM_PDUR_AR_RELEASE_MAJOR_VERSION       4
#define COM_PDUR_AR_RELEASE_MINOR_VERSION       4

/* Autosar ComM Specification Version */
#define COM_COMM_AR_RELEASE_MAJOR_VERSION       4
#define COM_COMM_AR_RELEASE_MINOR_VERSION       4

#if (STD_ON == COM_MULTI_CORE_SUPPORT)
/* Autosar OS Specification Version */
#define COM_OS_AR_RELEASE_MAJOR_VERSION       4
#define COM_OS_AR_RELEASE_MINOR_VERSION       4
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* COM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
