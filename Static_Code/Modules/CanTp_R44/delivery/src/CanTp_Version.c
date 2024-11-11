/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.1     27-Feb-2022   HieuTM8        R44-Redmine #20400                  **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_Version.h"        /* CanTp Version Header File */
#include "PduR_CanTp.h"           /* PduR header for CAN TP */
#include "CanIf.h"                /* CanIf header file */
#include "SchM_CanTp.h"           /* Scheduler Header File */
#include "Rte.h"                  /* Rte Header File */
#include "PduR.h"                 /* PduR Header File */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#include "Det.h"                  /* DET header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR Specification Version Information */
#define CANTP_VERSION_C_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_VERSION_C_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_VERSION_C_AR_RELEASE_REVISION_VERSION 0x00u

/* Software Version Information */
#define CANTP_VERSION_C_SW_MAJOR_VERSION            0x01u
#define CANTP_VERSION_C_SW_MINOR_VERSION            0x01u
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* CAN TP Version Check */
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_VERSION_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_VERSION_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_VERSION_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_Version.c : Mismatch in Specification Revision Version"
#endif

#if (CANTP_SW_MAJOR_VERSION != CANTP_VERSION_C_SW_MAJOR_VERSION)
#error "CanTp_Version.c : Mismatch in Software Major Version"
#endif

#if (CANTP_SW_MINOR_VERSION != CANTP_VERSION_C_SW_MINOR_VERSION)
#error "CanTp_Version.c : Mismatch in Software Minor Version"
#endif

/* PDUR Version Check */
#if (PDUR_AR_RELEASE_MAJOR_VERSION != CANTP_PDUR_AR_RELEASE_MAJOR_VERSION)
#error "PduR.h : Mismatch in Specification Major Version"
#endif

#if (PDUR_AR_RELEASE_MINOR_VERSION != CANTP_PDUR_AR_RELEASE_MINOR_VERSION)
#error "PduR.h : Mismatch in Specification Minor Version"
#endif

/* CAN Interface Version Check */
#if (CANIF_AR_RELEASE_MAJOR_VERSION != CANTP_CANIF_AR_RELEASE_MAJOR_VERSION)
#error "CanIf.h : Mismatch in Specification Major Version"
#endif

#if (CANIF_AR_RELEASE_MINOR_VERSION != CANTP_CANIF_AR_RELEASE_MINOR_VERSION)
#error "CanIf.h : Mismatch in Specification Minor Version"
#endif

/* DET Version Check */
#if (CANTP_DEV_ERROR_DETECT == STD_ON)
#if (DET_AR_RELEASE_MAJOR_VERSION != CANTP_DET_AR_RELEASE_MAJOR_VERSION)
#error "Det.h : Mismatch in Specification Major Version"
#endif

#if (DET_AR_RELEASE_MINOR_VERSION != CANTP_DET_AR_RELEASE_MINOR_VERSION)
#error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */

/* SCHM Version Check */
#if (RTE_AR_RELEASE_MAJOR_VERSION != CANTP_RTE_AR_RELEASE_MAJOR_VERSION)
#error "Rte.h : Mismatch in Rte Specification Major Version"
#endif
#if (RTE_AR_RELEASE_MINOR_VERSION != CANTP_RTE_AR_RELEASE_MINOR_VERSION)
#error "Rte.h : Mismatch in Rte Specification Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

