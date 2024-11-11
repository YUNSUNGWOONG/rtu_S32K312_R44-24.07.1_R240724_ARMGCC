/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
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
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Version file */
#include "KeyM_Version.h"
/* Csm version header file */
#include "Csm.h"
/* Det module Header file */
#if (KEYM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/* NvM version Header file */
#if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
#include "NvM.h"
#endif
/* Rte version header file */
#include "Rte.h"
#if (KEYM_USE_STBM == STD_ON)
/* StbM version header file */
#include "StbM.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/
#if ((KEYM_AR_RELEASE_MAJOR_VERSION != KEYM_VERSION_AR_RELEASE_MAJOR_VERSION) \
  || (KEYM_AR_RELEASE_MINOR_VERSION != KEYM_VERSION_AR_RELEASE_MINOR_VERSION))

#error "KeyM : Mismatch AUTOSAR Version in KeyM_Version.c"
#endif

#if ((KEYM_SW_MAJOR_VERSION != KEYM_VERSION_SW_MAJOR_VERSION) || \
  (KEYM_SW_MINOR_VERSION != KEYM_VERSION_SW_MINOR_VERSION) || \
  (KEYM_SW_PATCH_VERSION != KEYM_VERSION_SW_PATCH_VERSION))

#error "KeyM : Mismatch Software Version in KeyM_Version.c"
#endif

/* Csm version check */
#if defined(CSM_AR_RELEASE_MAJOR_VERSION) \
  && defined(CSM_AR_RELEASE_MINOR_VERSION)

#if ((CSM_AR_RELEASE_MAJOR_VERSION != KEYM_CSM_AR_RELEASE_MAJOR_VERSION) || \
  (CSM_AR_RELEASE_MINOR_VERSION != KEYM_CSM_AR_RELEASE_MINOR_VERSION))

#error "KeyM : Mismatch AUTOSAR Version with Csm.h"
#endif

#endif

/* DET Version check */
#if (KEYM_DEV_ERROR_DETECT == STD_ON)

#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
     && defined(DET_AR_RELEASE_MINOR_VERSION)

#if (DET_AR_RELEASE_MAJOR_VERSION != KEYM_DET_AR_RELEASE_MAJOR_VERSION)
#error "KeyM : Mismatch AUTOSAR Major Version with Det.h"
#endif

#if   (DET_AR_RELEASE_MINOR_VERSION < KEYM_DET_AR_RELEASE_MINOR_VERSION_L)
#error "KeyM : Mismatch AUTOSAR Minor Version with Det.h"
#endif

#if   (DET_AR_RELEASE_MINOR_VERSION > KEYM_DET_AR_RELEASE_MINOR_VERSION_U)
#error "KeyM : Mismatch AUTOSAR Minor Version with Det.h"
#endif
#endif

#endif /* (KEYM_DEV_ERROR_DETECT == STD_ON) */

/* NVM Version check */
#if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)

#if defined(NVM_AR_RELEASE_MAJOR_VERSION) \
  && defined(NVM_AR_RELEASE_MINOR_VERSION)

#if ((NVM_AR_RELEASE_MAJOR_VERSION != KEYM_NVM_AR_RELEASE_MAJOR_VERSION) || \
  (NVM_AR_RELEASE_MINOR_VERSION != KEYM_NVM_AR_RELEASE_MINOR_VERSION))

#error "KeyM : Mismatch AUTOSAR Version with NvM.h"

#endif

#endif

#endif /* (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON) */

/* RTE Version check */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) \
  && defined(RTE_AR_RELEASE_MINOR_VERSION)

#if (RTE_AR_RELEASE_MAJOR_VERSION != KEYM_RTE_AR_RELEASE_MAJOR_VERSION)

#error "KeyM : Mismatch AUTOSAR Major Version with Rte.h"

#endif

#if   (RTE_AR_RELEASE_MINOR_VERSION < KEYM_RTE_AR_RELEASE_MINOR_VERSION_L)
#error "KeyM : Mismatch AUTOSAR Minor Version with Rte.h"
#endif

#if   (RTE_AR_RELEASE_MINOR_VERSION > KEYM_RTE_AR_RELEASE_MINOR_VERSION_U)
#error "KeyM : Mismatch AUTOSAR Minor Version with Rte.h"
#endif

#endif

#if (KEYM_USE_STBM == STD_ON)
/* StbM version check */
#if defined(STBM_AR_RELEASE_MAJOR_VERSION) \
  && defined(STBM_AR_RELEASE_MINOR_VERSION)

#if ((STBM_AR_RELEASE_MAJOR_VERSION != KEYM_STBM_AR_RELEASE_MAJOR_VERSION) || \
  (STBM_AR_RELEASE_MINOR_VERSION != KEYM_STBM_AR_RELEASE_MINOR_VERSION))

#error "KeyM : Mismatch AUTOSAR Version with StbM.h"

#endif
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
