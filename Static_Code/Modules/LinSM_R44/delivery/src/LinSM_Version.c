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
**  SRC-MODULE: LinSM_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinSM Module Version information                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.5.1        25-Oct-2022           KhaLN1           #CP44-750            **
** 1.0.5          03-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinSM_Version.h"        /* LinSM version header */
#include "LinIf.h"                /* LinIf header file */
#include "ComM.h"                 /* ComM header file */
#include "BswM.h"                 /* BswM header file */
#include "Rte.h"                  /* Rte header file */

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Det header file */
#endif

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/*  Version Check for LinSM */
#if ((LINSM_VERSION_AR_RELEASE_MAJOR_VERSION !=\
                        LINSM_VERSION_C_AR_RELEASE_MAJOR_VERSION) || \
     (LINSM_VERSION_AR_RELEASE_MINOR_VERSION !=\
                        LINSM_VERSION_C_AR_RELEASE_MINOR_VERSION) || \
	 (LINSM_VERSION_AR_RELEASE_REVISION_VERSION !=\
                        LINSM_VERSION_C_AR_RELEASE_REVISION_VERSION) || \
	 (LINSM_SW_MAJOR_VERSION != LINSM_VERSION_C_SW_MAJOR_VERSION) || \
	 (LINSM_SW_MINOR_VERSION != LINSM_VERSION_C_SW_MINOR_VERSION) || \
   (LINSM_SW_PATCH_VERSION != LINSM_VERSION_C_SW_PATCH_VERSION))
#error "LinSM: Mismatch AUTOSAR Version in LinSM_Version.c"
#endif

/*  Version Check With LinIf */
#if ((LINIF_AR_RELEASE_MAJOR_VERSION != LINSM_LINIF_AR_RELEASE_MAJOR_VERSION) || \
     (LINIF_AR_RELEASE_MINOR_VERSION != LINSM_LINIF_AR_RELEASE_MINOR_VERSION))
#error "LinSM: Mismatch AUTOSAR Version in LinIf.h"
#endif

/*  Version Check With ComM */
#if ((COMM_AR_RELEASE_MAJOR_VERSION != LINSM_COMM_AR_RELEASE_MAJOR_VERSION) || \
     (COMM_AR_RELEASE_MINOR_VERSION != LINSM_COMM_AR_RELEASE_MINOR_VERSION))
#error "LinSM: Mismatch AUTOSAR Version in ComM.h"
#endif

/*  Version Check With BswM */
#if ((BSWM_AR_RELEASE_MAJOR_VERSION != LINSM_BSWM_AR_RELEASE_MAJOR_VERSION) || \
     (BSWM_AR_RELEASE_MINOR_VERSION != LINSM_BSWM_AR_RELEASE_MINOR_VERSION))
#error "LinSM: Mismatch AUTOSAR Version in BswM.h"
#endif

/*  Version Check With Det */
#if (LINSM_DEV_ERROR_DETECT == STD_ON)

#if ((DET_AR_RELEASE_MAJOR_VERSION != LINSM_DET_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != LINSM_DET_AR_RELEASE_MINOR_VERSION))
#error "LinSM: Mismatch AUTOSAR Version in Det.h"
#endif

#endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */

/*  Version Check With Rte*/
#if ((RTE_AR_RELEASE_MAJOR_VERSION != LINSM_RTE_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != LINSM_RTE_AR_RELEASE_MINOR_VERSION))
#error "LinSM: Mismatch AUTOSAR Version in Rte.h"
#endif

/*******************************************************************************
**                            Global Data                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
