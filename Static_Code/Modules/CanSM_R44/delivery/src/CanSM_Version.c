/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
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
**  SRC-MODULE: CanSM_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.9     07-Jun-2023   HieuTM8        #CP44-2208                          **
** 1.0.3     25-Jul-2022   HieuTM8        CP44-511                            **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of CanSM header */
#include "CanSM.h"

#include "CanSM_Error.h"

/* Version Information File */
#include "CanSM_Version.h"

/* Inclusion of ComM header file */
#include "ComM.h"

/* Inclusion of CanIf header file */
#include "CanIf.h"

/* Inclusion of Det header file */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"
#endif

/* #4975 */
#if(STD_ON == CANSM_DEM_STATUS)
#include "Dem.h"                  /* Dem header file */
#endif

/* Inclusion of SchM header file */
#include "SchM_CanSM.h"

/* Inclusion of BswM header file */
#include "BswM.h"

#if (STD_ON == CANSM_PNC_AVAILABILITY)
/* Inclusion of CanNm header file */
#include "CanNm.h"
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_VERSION_C_AR_RELEASE_MAJOR_VERSION       0x04u
#define CANSM_VERSION_C_AR_RELEASE_MINOR_VERSION       0x04u
#define CANSM_VERSION_C_AR_RELEASE_REV_VERSION         0x00u

/* CANSM software version information */
#define CANSM_VERSION_C_SW_MAJOR_VERSION               0x01u
#define CANSM_VERSION_C_SW_MINOR_VERSION               0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_VERSION_C_AR_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_VERSION_C_AR_RELEASE_REV_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_VERSION_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_VERSION_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/* CanIf version check */
#if (CANIF_AR_RELEASE_MAJOR_VERSION != CANSM_CANIF_AR_RELEASE_MAJOR_VERSION)
#error "CanIf.h : Mismatch in Specification Major Version"
#endif

#if (CANIF_AR_RELEASE_MINOR_VERSION != CANSM_CANIF_AR_RELEASE_MINOR_VERSION)
#error "CanIf.h : Mismatch in Specification Minor Version"
#endif

/* ComM version check */
#if (COMM_AR_RELEASE_MAJOR_VERSION != CANSM_COMM_AR_RELEASE_MAJOR_VERSION)
#error "ComM.h : Mismatch in Specification Major Version"
#endif
#if (COMM_AR_RELEASE_MINOR_VERSION != CANSM_COMM_AR_RELEASE_MINOR_VERSION)
#error "ComM.h : Mismatch in Specification Minor Version"
#endif

/* DET Version check */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#if (DET_AR_RELEASE_MAJOR_VERSION != CANSM_DET_AR_RELEASE_MAJOR_VERSION)
#error "Det.h : Mismatch in Specification Major Version"
#endif
#if (DET_AR_RELEASE_MINOR_VERSION != CANSM_DET_AR_RELEASE_MINOR_VERSION)
#error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

/* DEM Version check */
#if(STD_ON == CANSM_DEM_STATUS)
#if (DEM_AR_RELEASE_MAJOR_VERSION != CANSM_DEM_AR_RELEASE_MAJOR_VERSION)
#error "Dem.h : Mismatch in Specification Major Version"
#endif
#if (DEM_AR_RELEASE_MINOR_VERSION != CANSM_DEM_AR_RELEASE_MINOR_VERSION)
#error "Dem.h : Mismatch in Specification Minor Version"
#endif
#endif

/* BswM Version check */
#if (BSWM_AR_RELEASE_MAJOR_VERSION != CANSM_BSWM_AR_RELEASE_MAJOR_VERSION)
#error "BswM.h : Mismatch in Specification Major Version"
#endif
#if (BSWM_AR_RELEASE_MINOR_VERSION != CANSM_BSWM_AR_RELEASE_MINOR_VERSION)
#error "BswM.h : Mismatch in Specification Minor Version"
#endif

#if (STD_ON == CANSM_PNC_AVAILABILITY)
/* CanNM Version check */
#if (CANNM_AR_RELEASE_MAJOR_VERSION != CANSM_CANNM_AR_RELEASE_MAJOR_VERSION)
#error "CanNm.h : Mismatch in Specification Major Version"
#endif
#if (CANNM_AR_RELEASE_MINOR_VERSION != CANSM_CANNM_AR_RELEASE_MINOR_VERSION)
#error "CanNm.h : Mismatch in Specification Minor Version"
#endif
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
