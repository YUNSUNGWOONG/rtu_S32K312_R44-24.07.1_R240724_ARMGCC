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
**  SRC-MODULE: ComM_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : C header for ComM_Version                                     **
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
** 1.1.7          31-Jan-2024         NamNT1           CP44-3037              **
** 1.1.6          10-Aug-2023         ThuanLD5         CP44-2529              **
** 1.1.5          09-Jun-2023         NamNT1           CP44-2062, 2206, 2115  **
** 1.1.4          07-Mar-2023         ThuanVT          CP44-1598, 1152, 1762  **
** 1.1.3          16-Dec-2022         ThuanVT          BUGCLASSIC-380,        **
**                                                     CP44-1324, CP44-1245   **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.3          22-Feb-2022         ThuanVT          R44-Redmine #23340     **
** 1.0.2          29-Oct-2021         ThuanVT          R44-Redmine #20142     **
** 1.0.1          27-Dec-2020         DatNXT           R44-Redmine #14801     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef COMM_VERSION_H
#define COMM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: ComM_SUD_MACRO_003 */
#include "ComM.h"                 /* ComM header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_VERSION_AR_RELEASE_MAJOR_VERSION    (0x04U)
#define COMM_VERSION_AR_RELEASE_MINOR_VERSION    (0x04U)
#define COMM_VERSION_AR_RELEASE_REVISION_VERSION (0x00U)

/* ComM Software Version Information */
#define COMM_VERSION_SW_MAJOR_VERSION             (0x01U)
#define COMM_VERSION_SW_MINOR_VERSION             (0x01U)
#define COMM_VERSION_SW_PATCH_VERSION             (0x07U)

/* CanSM Software Version Information */
#if (COMM_CANNETWORK_PRESENT == STD_ON)
#define COMM_CANSM_AR_RELEASE_MAJOR_VERSION       (0x04U)
#define COMM_CANSM_AR_RELEASE_MINOR_VERSION       (0x04U)
#endif

/* Dcm Software Version Information */
#define COMM_DCM_AR_RELEASE_MAJOR_VERSION         (0x04U)
#define COMM_DCM_AR_RELEASE_MINOR_VERSION         (0x04U)

/* Det Software Version Information */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#define COMM_DET_AR_RELEASE_MAJOR_VERSION         (0x04U)
#define COMM_DET_AR_RELEASE_MINOR_VERSION         (0x04U)
#endif

/* FrSM Software Version Information */
#if (COMM_FRNETWORK_PRESENT == STD_ON)
#define COMM_FRSM_AR_RELEASE_MAJOR_VERSION        (0x04U)
#define COMM_FRSM_AR_RELEASE_MINOR_VERSION        (0x04U)
#endif

/* LinSM Software Version Information */
#if (COMM_LINNETWORK_PRESENT == STD_ON)
#define COMM_LINSM_AR_RELEASE_MAJOR_VERSION       (0x04U)
#define COMM_LINSM_AR_RELEASE_MINOR_VERSION       (0x04U)
#endif

/* EthSM Software Version Information */
#if (COMM_ETHNETWORK_PRESENT == STD_ON)
#define COMM_ETHSM_AR_RELEASE_MAJOR_VERSION       (0x04U)
#define COMM_ETHSM_AR_RELEASE_MINOR_VERSION       (0x04U)
#endif

/* Nm Software Version Information */
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
                                     (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#define COMM_NM_AR_RELEASE_MAJOR_VERSION          (0x04U)
#define COMM_NM_AR_RELEASE_MINOR_VERSION          (0x04U)
#endif

/* NvM Software Version Information */
#if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
#define COMM_NVM_AR_RELEASE_MAJOR_VERSION         (0x04U)
#define COMM_NVM_AR_RELEASE_MINOR_VERSION         (0x04U)
#endif

/* Rte Software Version Information */
#define COMM_RTE_AR_RELEASE_MAJOR_VERSION         (0x04U)
#define COMM_RTE_AR_RELEASE_MINOR_VERSION         (0x04U)

/* BswM Software Version Information */
#define COMM_BSWM_AR_RELEASE_MAJOR_VERSION        (0x04U)
#define COMM_BSWM_AR_RELEASE_MINOR_VERSION        (0x04U)

/* EcuM Software Version Information */
#define COMM_ECUM_AR_RELEASE_MAJOR_VERSION        (0x04U)
#define COMM_ECUM_AR_RELEASE_MINOR_VERSION        (0x04U)

/* CanCM Software Version Information */
#define COMM_CANCM_AR_RELEASE_MAJOR_VERSION       (0x04U)
#define COMM_CANCM_AR_RELEASE_MINOR_VERSION       (0x04U)

#endif /* COMM_VERSION_H */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

