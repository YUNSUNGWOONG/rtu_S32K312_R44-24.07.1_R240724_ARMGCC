/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : Provision of Version Information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                    Description                  **
********************************************************************************
** 1.1.4     31-Jan-2023   NamNT1                CP44 #1151, #1098, #873,     **
                                                 #1471, #1472                 **
** 1.1.1     07-Oct-2022   NamNT1                CP44 #785, #786, #610, #838  **
**                                               #887, #842                   **
** 1.0.2.1   20-Jun-2022   SM Kwon               CP44-120                     **
** 1.0.2     09-May-2022   ThuanVT               R44-Redmine #25509           **
** 1.0.1     15-Mar-2022   TuanNLH               R44-Redmine #17463           **
** 1.0.0     16-Dec-2020   SHKim                 Initial Version              **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanNm.h"                /* CanNm API Header File */
#include "CanNm_Version.h"        /* CanNm Version Information Header */
#include "Nm.h"                   /* Nm header file */
#include "CanIf.h"                /* CanIf header file */
#include "PduR.h"                 /* PduR CallBack Functions Header File */
#include "Det.h"                  /* DET header file */
#include "SchM_CanNm.h"           /* Inclusion of SchM Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define CANNM_VERSION_C_AR_RELEASE_MAJOR_VERSION    (0x04u)
#define CANNM_VERSION_C_AR_RELEASE_MINOR_VERSION    (0x04u)
#define CANNM_VERSION_C_AR_RELEASE_REVISION_VERSION (0x00u)

/* Software Version Information */
#define CANNM_VERSION_C_SW_MAJOR_VERSION            (0x01u)
#define CANNM_VERSION_C_SW_MINOR_VERSION            (0x02u)
#define CANNM_VERSION_C_SW_PATCH_VERSION            (0x00u)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* Interal checking for AR Version */
#if ((CANNM_AR_RELEASE_MAJOR_VERSION != \
                                  CANNM_VERSION_AR_RELEASE_MAJOR_VERSION) || \
     (CANNM_AR_RELEASE_MINOR_VERSION != \
                                  CANNM_VERSION_AR_RELEASE_MINOR_VERSION) || \
     (CANNM_AR_RELEASE_REVISION_VERSION != \
                                  CANNM_VERSION_AR_RELEASE_REVISION_VERSION))
  #error "CanNm : Mismatch AUTOSAR Version in CanNm_Version.c"
#endif

/* Interal checking for SW Version */
#if ((CANNM_SW_MAJOR_VERSION != CANNM_VERSION_SW_MAJOR_VERSION) || \
     (CANNM_SW_MINOR_VERSION != CANNM_VERSION_SW_MINOR_VERSION) || \
     (CANNM_SW_PATCH_VERSION != CANNM_VERSION_SW_PATCH_VERSION))
  #error "CanNm : Mismatch Sofware Version in CanNm_Version.c"
#endif

/* Inter Module check for Det.h */
#if ((defined DET_AR_RELEASE_MAJOR_VERSION) && \
     (defined DET_AR_RELEASE_MINOR_VERSION))
  #if ((DET_AR_RELEASE_MAJOR_VERSION != CANNM_DET_AR_MAJOR_VERSION) || \
       (DET_AR_RELEASE_MINOR_VERSION != CANNM_DET_AR_MINOR_VERSION))
    #error "CanNm : Mismatch AUTOSAR Version with Det.h"
  #endif
#endif

/* Inter Module check for SchM_CANNM.h */
#if ((defined SCHM_CANNM_AR_RELEASE_MAJOR_VERSION) && \
     (defined SCHM_CANNM_AR_RELEASE_MINOR_VERSION))
  #if ((SCHM_CANNM_AR_RELEASE_MAJOR_VERSION != \
                                              CANNM_SCHM_AR_MAJOR_VERSION) || \
       (SCHM_CANNM_AR_RELEASE_MINOR_VERSION != CANNM_SCHM_AR_MINOR_VERSION))
    #error "CanNm : Mismatch AUTOSAR Version with SchM_CanNm.h"
  #endif
#endif

/* Inter Module check for Nm.h */
#if ((defined NM_AR_RELEASE_MAJOR_VERSION) && \
     (defined NM_AR_RELEASE_MINOR_VERSION))
  #if ((NM_AR_RELEASE_MAJOR_VERSION != CANNM_NM_AR_MAJOR_VERSION) || \
       (NM_AR_RELEASE_MINOR_VERSION != CANNM_NM_AR_MINOR_VERSION))
    #error "CanNm : Mismatch AUTOSAR Version with Nm.h"
  #endif
#endif

/* Inter Module check for CanIf.h */
#if ((defined CANIF_AR_RELEASE_MAJOR_VERSION) && \
     (defined CANIF_AR_RELEASE_MINOR_VERSION))
  #if ((CANIF_AR_RELEASE_MAJOR_VERSION != CANNM_CANIF_AR_MAJOR_VERSION) || \
       (CANIF_AR_RELEASE_MINOR_VERSION != CANNM_CANIF_AR_MINOR_VERSION))
    #error "CanNm : Mismatch AUTOSAR Version with CanIf.h"
  #endif
#endif

/* Inter Module check for CanSM_CanIf.h */
#if ((defined CANSM_AR_RELEASE_MAJOR_VERSION) && \
     (defined CANSM_AR_RELEASE_MINOR_VERSION))
  #if ((CANSM_AR_RELEASE_MAJOR_VERSION != \
                                            CANNM_CANSM_AR_MAJOR_VERSION) || \
       (CANSM_AR_RELEASE_MINOR_VERSION != CANNM_CANSM_AR_MINOR_VERSION))
    #error "CanNm : Mismatch AUTOSAR Version with CanSM_CanIf.h"
  #endif
#endif

/* Inter Module check for PduR.h */
#if ((defined CANNM_PDUR_AR_RELEASE_MAJOR_VERSION) && \
     (defined CANNM_PDUR_AR_RELEASE_MINOR_VERSION))
  #if ((CANNM_PDUR_AR_RELEASE_MAJOR_VERSION != \
                                      CANNM_PDUR_AR_RELEASE_MAJOR_VERSION) || \
  (CANNM_PDUR_AR_RELEASE_MINOR_VERSION != CANNM_PDUR_AR_RELEASE_MINOR_VERSION))
    #error "CanNm : Mismatch AUTOSAR Version with PduR.h"
  #endif
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
