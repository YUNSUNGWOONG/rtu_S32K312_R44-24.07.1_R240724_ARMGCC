/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM Module                                          **
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
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.8          27-Mar-2024         DH Kim           CP44-3766,3812,5321    **
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.3          15-Jul-2022         DuyNHP2          CP44-567               **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.2          18-Apr-2022         DuyNHP2          R44-Redmine #26373     **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef IPDUM_VERSION_H
#define IPDUM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "IpduM_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define IPDUM_VERSION_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define IPDUM_VERSION_AR_RELEASE_MINOR_VERSION       (0x04u)
#define IPDUM_VERSION_AR_RELEASE_REVISION_VERSION    (0x00u)

#define IPDUM_VERSION_SW_MAJOR_VERSION               (0x01u)
#define IPDUM_VERSION_SW_MINOR_VERSION               (0x00u)
#define IPDUM_VERSION_SW_PATCH_VERSION               (0x08u)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if(IPDUM_ENABLE_MODULE == STD_ON)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
/* Expected Version information of ComStack_Types.h */
#define IPDUM_COMSTACK_TYPES_AR_MAJOR_VERSION        (0x04u)
#define IPDUM_COMSTACK_TYPES_AR_MINOR_VERSION        (0x04u)

/* Expected Version information of Com.h */
#if (IPDUM_COM_SUPPORT_DIRECT == STD_ON)
#define IPDUM_COM_AR_MAJOR_VERSION                   (0x04u)
#define IPDUM_COM_AR_MINOR_VERSION                   (0x04u)
#endif

/* Expected Version information of Det.h */
#if ((IPDUM_DEV_ERROR_DETECT == STD_ON) || \
     (IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#define IPDUM_DET_AR_MAJOR_VERSION                   (0x04u)
#define IPDUM_DET_AR_MINOR_VERSION                   (0x04u)
#endif

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

/* Expected Version information of PduR_IpduM.h */
#define IPDUM_PDUR_IPDUM_AR_MAJOR_VERSION            (0x04u)
#define IPDUM_PDUR_IPDUM_AR_MINOR_VERSION            (0x04u)

/* Expected Version information of SchM_IpduM.h */
#define IPDUM_SCHM_IPDUM_AR_MAJOR_VERSION            (0x04u)
#define IPDUM_SCHM_IPDUM_AR_MINOR_VERSION            (0x04u)

#endif /* IPDUM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
