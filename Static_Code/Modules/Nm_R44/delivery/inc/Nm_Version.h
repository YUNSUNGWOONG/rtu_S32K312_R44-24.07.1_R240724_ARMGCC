/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_Version.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provides the information used for Version Check               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.0.5      19-Feb-2024   DHKim          CP44-3592, CP44-3813, CP44-3884    **
** 1.0.4      21-Apr-2023   NamNT1         CP44-1709                          **
** 1.0.3      16-Dec-2022   NamNT1         BUGCLASSIC-385, CP44-1325          **
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.1      29-Oct-2021   ThuanVT        R44-Redmine #20144                 **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

#ifndef NM_VERSION_H
#define NM_VERSION_H

/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/
/* Inclusion for AUTOSAR standard types */
#include "Std_Types.h"
/* Inclusion for pre-processor switches */
#include "Nm_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: Nm_SUD_MACRO_003 */
#define NM_VERSION_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define NM_VERSION_AR_RELEASE_MINOR_VERSION       (0x04u)
#define NM_VERSION_AR_RELEASE_REVISION_VERSION    (0x00u)

#define NM_VERSION_SW_MAJOR_VERSION               (0x01u)
#define NM_VERSION_SW_MINOR_VERSION               (0x00u)
#define NM_VERSION_SW_PATCH_VERSION               (0x05u)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Expected Version information of Com Stack Types definition */
#define NM_COMSTACK_TYPES_AR_MAJOR_VERSION  (0x04u)
#define NM_COMSTACK_TYPES_AR_MINOR_VERSION  (0x04u)

/* Expected Version information of ComM module */
#define NM_COMM_AR_MAJOR_VERSION          (0x04u)
#define NM_COMM_AR_MINOR_VERSION          (0x04u)

/* Expected Version information of Det module */
#if (NM_DEV_ERROR_DETECT == STD_ON)
#define NM_DET_AR_MAJOR_VERSION           (0x04u)
#define NM_DET_AR_MINOR_VERSION           (0x04u)
#endif

/* Expected Version information of Com module */
#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
#define NM_COM_AR_MAJOR_VERSION           (0x04u)
#define NM_COM_AR_MINOR_VERSION           (0x04u)
#endif

/* Expected Version information of BswM module */
#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
#define NM_BSWM_AR_MAJOR_VERSION          (0x04u)
#define NM_BSWM_AR_MINOR_VERSION          (0x04u)
#endif

/* Expected Version information of SchM module */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#define NM_SCHM_AR_MAJOR_VERSION          (0x04u)
#define NM_SCHM_AR_MINOR_VERSION          (0x04u)
#endif

/* Expected Version information of CanNm module */
#if (NM_CANNM_ENABLED == STD_ON)
#define NM_CANNM_AR_MAJOR_VERSION         (0x04u)
#define NM_CANNM_AR_MINOR_VERSION         (0x04u)
#endif

/* Expected Version information of FrNm module */
#if (NM_FRNM_ENABLED == STD_ON)
#define NM_FRNM_AR_MAJOR_VERSION          (0x04u)
#define NM_FRNM_AR_MINOR_VERSION          (0x04u)
#endif

/* Expected Version information of UdpNm module */
#if (NM_UDPNM_ENABLED == STD_ON)
#define NM_UDPNM_AR_MAJOR_VERSION         (0x04u)
#define NM_UDPNM_AR_MINOR_VERSION         (0x04u)
#endif

/* Expected Version information of J1939Nm module */
#if (NM_J1939NM_ENABLED == STD_ON)
#define NM_J1939NM_AR_MAJOR_VERSION       (0x04u)
#define NM_J1939NM_AR_MINOR_VERSION       (0x04u)
#endif

/* Expected Version information of OsekNm module */
#if (NM_OSEKNM_ENABLED == STD_ON)
#define NM_OSEKNM_AR_MAJOR_VERSION        (0x04u)
#define NM_OSEKNM_AR_MINOR_VERSION        (0x04u)
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#endif /* NM_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
