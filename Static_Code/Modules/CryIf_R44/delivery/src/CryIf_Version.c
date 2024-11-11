/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Check version information of this module and dependent module **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.2     09-Nov-2021        TamTV6       Implement #20952                 **
*******************************************************************************/

/* For dependent module macros */
#include "CryIf_Version.h"
/* If development error detection is enabled */
#if (STD_ON == CRYIF_DEV_ERROR_DETECT)
/* For version check with Det */
#include "Det.h"
#endif

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* Check with module ASR/SW version */
#if (CRYIF_AR_RELEASE_MAJOR_VERSION != CRYIF_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "CryIf : Mismatch AUTOSAR Version in CryIf_Version.c "
#endif

#if (CRYIF_AR_RELEASE_MINOR_VERSION != CRYIF_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "CryIf : Mismatch AUTOSAR Version in CryIf_Version.c "
#endif

#if (CRYIF_AR_RELEASE_REVISION_VERSION != \
  CRYIF_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "CryIf : Mismatch AUTOSAR Version in CryIf_Version.c "
#endif

#if (CRYIF_SW_MAJOR_VERSION != CRYIF_VERSION_SW_MAJOR_VERSION)
  #error "CryIf : Mismatch Software Version in CryIf_Version.c "
#endif

#if (CRYIF_SW_MINOR_VERSION != CRYIF_VERSION_SW_MINOR_VERSION)
  #error "CryIf : Mismatch Software Version in CryIf_Version.c "
#endif

#if (CRYIF_SW_PATCH_VERSION != CRYIF_VERSION_SW_PATCH_VERSION)
  #error "CryIf : Mismatch Software Version in CryIf_Version.c "
#endif

/* Check with ASR version of dependent module */
/* Csm module */
#if (CSM_AR_RELEASE_MAJOR_VERSION != CRYIF_CSM_AR_RELEASE_MAJOR_VERSION)
  #error "CryIf : Mismatch AUTOSAR Version with Csm.h"
#endif

#if (CSM_AR_RELEASE_MINOR_VERSION != CRYIF_CSM_AR_RELEASE_MINOR_VERSION)
  #error "CryIf : Mismatch AUTOSAR Version with Csm.h"
#endif

/* Det module */
#if (STD_ON == CRYIF_DEV_ERROR_DETECT)
  #if defined(DET_AR_RELEASE_MAJOR_VERSION) \
     && defined(DET_AR_RELEASE_MINOR_VERSION)
  #if (DET_AR_RELEASE_MAJOR_VERSION != CRYIF_DET_AR_RELEASE_MAJOR_VERSION)
  #error "CryIf : Mismatch AUTOSAR Major Version with Det.h"
  #endif

  #if   (DET_AR_RELEASE_MINOR_VERSION < CRYIF_DET_AR_RELEASE_MINOR_VERSION_L)
  #error "CryIf : Mismatch AUTOSAR Minor Version with Det.h"
  #endif

  #if   (DET_AR_RELEASE_MINOR_VERSION > CRYIF_DET_AR_RELEASE_MINOR_VERSION_U)
  #error "CryIf : Mismatch AUTOSAR Minor Version with Det.h"
  #endif
  #endif
#endif /* STD_ON == CRYIF_DEV_ERROR_DETECT */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
