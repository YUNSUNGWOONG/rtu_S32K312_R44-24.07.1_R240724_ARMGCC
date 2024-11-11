/* polyspace +1 MISRA2012:1.1 [Not a Defect:Low] "Macro definitions are needed for performance and file size" */
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
**  SRC-MODULE: WdgM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Checking version information                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     11-Mar-2020   TienVD       Update traceability                   **
** 1.0.2     30-Mar-2021   HiepVT1      Update check version method between   **
**                                      WdgM and DET                          **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
** 1.3.1.0   08-Aug-2022   TriBD        #CP44-385                             **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_Version.h"     /* WdgM Version file */
#include "WdgIf.h"            /* WdgIf version header file */
#if(WDGM_IMMEDIATE_RESET == STD_ON)
#include "Mcu.h"              /* Mcu module Header file */
#endif
#if(WDGM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"              /* Det module Header file */
#endif
#if(WDGM_DEM_ERROR_REPORT == STD_ON)
#include "Dem.h"              /* Dem version Header file */
#endif
#include "Rte.h"              /* Rte version header file */
#include "BswM.h"             /* BswM version header file */
#include "Os.h"               /* Os version header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/
/* @Trace: SafeWdgM_SRS_BSW_00036 */
#if ((WDGM_AR_RELEASE_MAJOR_VERSION != WDGM_VERSION_AR_RELEASE_MAJOR_VERSION) || \
    (WDGM_AR_RELEASE_MINOR_VERSION != WDGM_VERSION_AR_RELEASE_MINOR_VERSION))

#error "WdgM : Mismatch AUTOSAR Version in WdgM_Version.c"
#endif

#if ((WDGM_SW_MAJOR_VERSION != WDGM_VERSION_SW_MAJOR_VERSION) || \
    (WDGM_SW_MINOR_VERSION != WDGM_VERSION_SW_MINOR_VERSION) || \
    (WDGM_SW_PATCH_VERSION != WDGM_VERSION_SW_PATCH_VERSION))

#error "WdgM : Mismatch Software Version in WdgM_Version.c"
#endif


/* WdgIf version check */
#if defined(WDGIF_AR_RELEASE_MAJOR_VERSION) \
  && defined(WDGIF_AR_RELEASE_MINOR_VERSION)
#if ((WDGIF_AR_RELEASE_MAJOR_VERSION != WDGM_WDGIF_AR_RELEASE_MAJOR_VERSION) || \
    (WDGIF_AR_RELEASE_MINOR_VERSION != WDGM_WDGIF_AR_RELEASE_MINOR_VERSION))

#error "WdgM : Mismatch AUTOSAR Version with WdgIf.h"
#endif

#endif

#if(WDGM_IMMEDIATE_RESET == STD_ON)
/* Mcu version check */

#if defined(MCU_AR_RELEASE_MAJOR_VERSION) \
  && defined(MCU_AR_RELEASE_MINOR_VERSION)

#if ((MCU_AR_RELEASE_MAJOR_VERSION != WDGM_MCU_AR_RELEASE_MAJOR_VERSION) \
  || (MCU_AR_RELEASE_MINOR_VERSION < WDGM_MCU_AR_RELEASE_MINOR_VERSION_L) \
  || (MCU_AR_RELEASE_MINOR_VERSION > WDGM_MCU_AR_RELEASE_MINOR_VERSION_U))

#error "WdgM : Mismatch AUTOSAR Version with Mcu.h"
#endif

#endif

#endif


/* DET Version check */
#if (WDGM_DEV_ERROR_DETECT == STD_ON)

#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
  && defined(DET_AR_RELEASE_MINOR_VERSION)

#if (DET_AR_RELEASE_MAJOR_VERSION != WDGM_DET_AR_RELEASE_MAJOR_VERSION)
#error "WdgM : Mismatch AUTOSAR Major Version with Det.h"
#endif

#if   (DET_AR_RELEASE_MINOR_VERSION < WDGM_DET_AR_RELEASE_MINOR_VERSION_L)
#error "WdgM : Mismatch AUTOSAR Minor Version with Det.h"
#endif

#if   (DET_AR_RELEASE_MINOR_VERSION > WDGM_DET_AR_RELEASE_MINOR_VERSION_U)
#error "WdgM : Mismatch AUTOSAR Minor Version with Det.h"
#endif

#endif

#endif /* #if(WDGM_DEV_ERROR_DETECT == STD_ON) */


/* DEM Version check */
#if(WDGM_DEM_ERROR_REPORT == STD_ON)

#if defined(DEM_AR_RELEASE_MAJOR_VERSION) \
  && defined(DEM_AR_RELEASE_MINOR_VERSION)

#if ((DEM_AR_RELEASE_MAJOR_VERSION != WDGM_DEM_AR_RELEASE_MAJOR_VERSION) || \
    (DEM_AR_RELEASE_MINOR_VERSION != WDGM_DEM_AR_RELEASE_MINOR_VERSION))

#error "WdgM : Mismatch AUTOSAR Version with Dem.h"
#endif
#endif

#endif /* #if(WDGM_DEM_ERROR_REPORT == STD_ON) */

/* RTE Version check */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) \
  && defined(RTE_AR_RELEASE_MINOR_VERSION)

#if ((RTE_AR_RELEASE_MAJOR_VERSION != WDGM_RTE_AR_RELEASE_MAJOR_VERSION) || \
    (RTE_AR_RELEASE_MINOR_VERSION != WDGM_RTE_AR_RELEASE_MINOR_VERSION))

#error "WdgM : Mismatch AUTOSAR Version with Rte.h"
#endif

#endif

/* BswM version check */
#if defined(BSWM_AR_RELEASE_MAJOR_VERSION) \
  && defined(BSWM_AR_RELEASE_MINOR_VERSION)

#if ((BSWM_AR_RELEASE_MAJOR_VERSION != WDGM_BSWM_AR_RELEASE_MAJOR_VERSION) || \
    (BSWM_AR_RELEASE_MINOR_VERSION != WDGM_BSWM_AR_RELEASE_MINOR_VERSION))

#error "WdgM : Mismatch AUTOSAR Version with BswM.h"
#endif

#endif

/* OS version check */
#if defined(OS_AR_RELEASE_MAJOR_VERSION) \
  && defined(OS_AR_RELEASE_MINOR_VERSION)
#if ((OS_AR_RELEASE_MAJOR_VERSION != WDGM_OS_AR_RELEASE_MAJOR_VERSION) || \
    (OS_AR_RELEASE_MINOR_VERSION != WDGM_OS_AR_RELEASE_MINOR_VERSION))

#error "WdgM : Mismatch AUTOSAR Version with Os.h"
#endif
#endif


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
