/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually  and has no impact" */
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
**  SRC-MODULE: LinIf_Version.c                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
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
** Revision    Date          By              Description                      **
********************************************************************************
** 1.0.15      01-Mar-2024   JH Jang         #CP44-5060, #CP44-5062           **
** 1.0.13      15-Aug-2023   KhaLN1          #CP44-2673                       **
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinIf_Version.h"          /* Version Information File */
#include "Rte.h"                   /* Schedule Manager header */
#if(LINTP_SUPPORT == STD_ON)
#include "BswM.h"                   /* BSW Mode Manager header */
#endif
#include "PduR.h"                   /* PDU Router Header */
#include "LinSM.h"                  /* LIN state manager header */
#if (LINIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                    /* DET header */
#endif
#if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_OFF)
#include "Lin.h"              /* Lin driver header */
#endif
#if ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && \
  (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_OFF))
#include "LinTrcv.h"          /* LinTrcv driver header */
#endif
#if (LINIF_CDD_SUPPORT == STD_ON)
#include "Cdd.h"                /* Cdd Header */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* LinIf AUTOSAR Version check */
#if ((LINIF_VERSION_AR_RELEASE_MAJOR_VERSION != LINIF_AR_RELEASE_MAJOR_VERSION) || \
     (LINIF_VERSION_AR_RELEASE_MINOR_VERSION != LINIF_AR_RELEASE_MINOR_VERSION) || \
     (LINIF_VERSION_AR_RELEASE_REVISION_VERSION != LINIF_AR_RELEASE_REVISION_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in LinIf_Version.c"
#endif

/* LinIf Software Version check */
#if ((LINIF_SW_MAJOR_VERSION != LINIF_VERSION_SW_MAJOR_VERSION) || \
     (LINIF_SW_MINOR_VERSION != LINIF_VERSION_SW_MINOR_VERSION) || \
     (LINIF_SW_PATCH_VERSION != LINIF_VERSION_SW_PATCH_VERSION))
  #error "LinIf : Mismatch Sofware Version in LinIf_Version.c"
#endif

/* Det AUTOSAR Version check */
#if (LINIF_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != \
                                      LINIF_DET_AR_RELEASE_MAJOR_VERSION) \
 || (DET_AR_RELEASE_MINOR_VERSION != \
                                        LINIF_DET_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in Det.h"
#endif
#endif

/* Lin AUTOSAR Version check */
#if (LINIF_MULTIPLE_DRIVER_SUPPORT == STD_OFF)
#if ((LINIF_LIN_H_AR_RELEASE_MAJOR_VERSION != LINIF_LIN_AR_RELEASE_MAJOR_VERSION_4) || \
           ((LINIF_LIN_H_AR_RELEASE_MINOR_VERSION != LINIF_LIN_AR_RELEASE_MINOR_VERSION_4) && \
           (LINIF_LIN_H_AR_RELEASE_MINOR_VERSION != LINIF_LIN_AR_RELEASE_MINOR_VERSION_2) && \
           (LINIF_LIN_H_AR_RELEASE_MINOR_VERSION != LINIF_LIN_AR_RELEASE_MINOR_VERSION_7) && \
           (LINIF_LIN_H_AR_RELEASE_MINOR_VERSION != LINIF_LIN_AR_RELEASE_MINOR_VERSION_3)))
  #error "LinIf: Mismatch AUTOSAR Version in Lin.h"
#endif
#endif

/* RTE AUTOSAR Version check */
#if ((RTE_AR_RELEASE_MAJOR_VERSION != LINIF_RTE_AR_RELEASE_MAJOR_VERSION) || \
           (RTE_AR_RELEASE_MINOR_VERSION != LINIF_RTE_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in Rte.h"
#endif

/* BswM AUTOSAR Version check */
#if(LINTP_SUPPORT == STD_ON)
#if ((BSWM_AR_RELEASE_MAJOR_VERSION != LINIF_BSWM_AR_RELEASE_MAJOR_VERSION) || \
         (BSWM_AR_RELEASE_MINOR_VERSION != LINIF_BSWM_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in BswM.h"
#endif
#endif

/* LinSM AUTOSAR Version check */
#if ((LINSM_AR_RELEASE_MAJOR_VERSION != LINIF_LINSM_AR_RELEASE_MAJOR_VERSION) \
    || (LINSM_AR_RELEASE_MINOR_VERSION != LINIF_LINSM_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in LinSM.h"
#endif

/* PduR AUTOSAR Version check */
#if ((PDUR_AR_RELEASE_MAJOR_VERSION != LINIF_PDUR_AR_RELEASE_MAJOR_VERSION) || \
      (PDUR_AR_RELEASE_MINOR_VERSION != LINIF_PDUR_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in PduR.h"
#endif

/* LinTrcv AUTOSAR Version check */
#if ((LINIF_TRCV_DRIVER_SUPPORT == STD_ON) && \
  (LINIF_MULTIPLE_TRCV_DRIVER_SUPPORT == STD_OFF))
#if ((LINTRCV_AR_RELEASE_MAJOR_VERSION != \
                                LINIF_LINTRCV_AR_RELEASE_MAJOR_VERSION) \
 || (LINTRCV_AR_RELEASE_MINOR_VERSION != \
                                        LINIF_LINTRCV_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in LinTrcv.h"
#endif
#endif

/* CDD AUTOSAR Version check */
#if (LINIF_CDD_SUPPORT == STD_ON)
#if ((CDD_AR_RELEASE_MAJOR_VERSION != LINIF_CDD_AR_RELEASE_MAJOR_VERSION) || \
        (CDD_AR_RELEASE_MINOR_VERSION != LINIF_CDD_AR_RELEASE_MINOR_VERSION))
  #error "LinIf: Mismatch AUTOSAR Version in Cdd.h"
#endif
#endif
/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
