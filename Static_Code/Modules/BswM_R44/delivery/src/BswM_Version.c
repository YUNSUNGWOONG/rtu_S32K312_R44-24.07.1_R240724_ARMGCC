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
**  SRC-MODULE: BswM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
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
** 1.0.0     03-Mar-2020   ThiNT8        R44-Redmine #4579, #8683              **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "BswM_Version.h"        /* EcuM Version Header File */
#include "Rte.h"              /* Rte version header file */
#include "BswM.h"             /* BswM version header file */
#include "Os.h"               /* Os version header file */
#include "CanSM.h"               /* CanSM version header file */
#include "ComM.h"               /* ComM version header file */
#include "EcuM.h"               /* EcuM version header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* BswM AUTOSAR Version check */
#if ((BSWM_AR_RELEASE_MAJOR_VERSION != BSWM_VERSION_AR_RELEASE_MAJOR_VERSION) || \
       (BSWM_AR_RELEASE_MINOR_VERSION != BSWM_VERSION_AR_RELEASE_MINOR_VERSION))
  #error "BswM : Mismatch AUTOSAR Version in BswM_Version.c "
#endif

/* BswM Software Version check */
#if ((BSWM_SW_MAJOR_VERSION != BSWM_VERSION_SW_MAJOR_VERSION) || \
       (BSWM_SW_MINOR_VERSION != BSWM_VERSION_SW_MINOR_VERSION) || \
       (BSWM_SW_PATCH_VERSION != BSWM_VERSION_SW_PATCH_VERSION))
  #error "BswM : Mismatch Software Version in BswM_Version.c "
#endif

/* RTE Version check */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) \
  && defined(RTE_AR_RELEASE_MINOR_VERSION)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != BSWM_RTE_AR_RELEASE_MAJOR_VERSION) || \
    (RTE_AR_RELEASE_MINOR_VERSION != BSWM_RTE_AR_RELEASE_MINOR_VERSION))
#error "BswM : Mismatch AUTOSAR Version with Rte.h"
#endif
#endif

/* CAMSM Version check */
#if defined(CAMSM_AR_RELEASE_MAJOR_VERSION) \
  && defined(CAMSM_AR_RELEASE_MINOR_VERSION)
#if ((CAMSM_AR_RELEASE_MAJOR_VERSION != BSWM_CAMSM_AR_RELEASE_MAJOR_VERSION) || \
    (CAMSM_AR_RELEASE_MINOR_VERSION != BSWM_CAMSM_AR_RELEASE_MINOR_VERSION))
#error "BswM : Mismatch AUTOSAR Version with CanSM.h"
#endif
#endif

/* ECUM Version check */
#if defined(ECUM_AR_RELEASE_MAJOR_VERSION) \
  && defined(ECUM_AR_RELEASE_MINOR_VERSION)
#if ((ECUM_AR_RELEASE_MAJOR_VERSION != BSWM_ECUM_AR_RELEASE_MAJOR_VERSION) || \
    (ECUM_AR_RELEASE_MINOR_VERSION != BSWM_ECUM_AR_RELEASE_MINOR_VERSION))
#error "BswM : Mismatch AUTOSAR Version with EcuM.h"
#endif
#endif

/* COMM Version check */
#if defined(COMM_AR_RELEASE_MAJOR_VERSION) \
  && defined(COMM_AR_RELEASE_MINOR_VERSION)
#if ((COMM_AR_RELEASE_MAJOR_VERSION != BSWM_COMM_AR_RELEASE_MAJOR_VERSION) || \
    (COMM_AR_RELEASE_MINOR_VERSION != BSWM_COMM_AR_RELEASE_MINOR_VERSION))
#error "BswM : Mismatch AUTOSAR Version with ComM.h"
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

