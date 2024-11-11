/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Checking inter-module version information                     **
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
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.2     09-Nov-2021   TamTV6       Implement #20990                      **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Version.h"
#include "Det.h"
#include "Rte.h"
#include "CryIf.h"

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/
#if ((CSM_AR_RELEASE_MAJOR_VERSION != CSM_VERSION_AR_RELEASE_MAJOR_VERSION) || \
    (CSM_AR_RELEASE_MINOR_VERSION != CSM_VERSION_AR_RELEASE_MINOR_VERSION))
#error "Csm : Mismatch AUTOSAR Version in Csm_Version.c"
#endif

#if ((CSM_SW_MAJOR_VERSION != CSM_VERSION_SW_MAJOR_VERSION) || \
    (CSM_SW_MINOR_VERSION != CSM_VERSION_SW_MINOR_VERSION) || \
    (CSM_SW_PATCH_VERSION != CSM_VERSION_SW_PATCH_VERSION))
#error "Csm : Mismatch Software Version in Csm_Version.c"
#endif

/* DET Version check */
#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
  && defined(DET_AR_RELEASE_MINOR_VERSION)
#if (DET_AR_RELEASE_MAJOR_VERSION != CSM_DET_AR_RELEASE_MAJOR_VERSION)
#error "Csm : Mismatch AUTOSAR Major Version with Det.h"
#endif

#if   (DET_AR_RELEASE_MINOR_VERSION < CSM_DET_AR_RELEASE_MINOR_VERSION_L)
#error "Csm : Mismatch AUTOSAR Minor Version with Det.h"
#endif

#if   (DET_AR_RELEASE_MINOR_VERSION > CSM_DET_AR_RELEASE_MINOR_VERSION_U)
#error "Csm : Mismatch AUTOSAR Minor Version with Det.h"
#endif
#endif

/* RTE Version check */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) \
  && defined(RTE_AR_RELEASE_MINOR_VERSION)

#if (RTE_AR_RELEASE_MAJOR_VERSION != CSM_RTE_AR_RELEASE_MAJOR_VERSION)

#error "Csm : Mismatch AUTOSAR Major Version with Rte.h"

#endif

#if   (RTE_AR_RELEASE_MINOR_VERSION < CSM_RTE_AR_RELEASE_MINOR_VERSION_L)
#error "Csm : Mismatch AUTOSAR Minor Version with Rte.h"
#endif

#if   (RTE_AR_RELEASE_MINOR_VERSION > CSM_RTE_AR_RELEASE_MINOR_VERSION_U)
#error "Csm : Mismatch AUTOSAR Minor Version with Rte.h"
#endif

#endif

/* CRYIF Version check */
#if defined(CRYIF_AR_RELEASE_MAJOR_VERSION) \
  && defined(CRYIF_AR_RELEASE_MINOR_VERSION)
#if ((CRYIF_AR_RELEASE_MAJOR_VERSION != CSM_CRYIF_AR_RELEASE_MAJOR_VERSION) || \
    (CRYIF_AR_RELEASE_MINOR_VERSION != CSM_CRYIF_AR_RELEASE_MINOR_VERSION))
#error "Csm : Mismatch AUTOSAR Version with CryIf.h"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
