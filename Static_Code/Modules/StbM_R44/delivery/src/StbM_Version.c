/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
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
**  SRC-MODULE: StbM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.6           31-Jul-2023         NamNT1          CP44-2035              **
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* StbM module version header */
#include "StbM_Version.h"

#include "Os.h"

#include "Gpt.h"

#if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
#include "EthIf.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* StbM AUTOSAR Specification Version Information */
#if ((STBM_AR_RELEASE_MAJOR_VERSION != STBM_VERSION_AR_RELEASE_MAJOR_VERSION) || \
    (STBM_AR_RELEASE_MINOR_VERSION != STBM_VERSION_AR_RELEASE_MINOR_VERSION))

#error "StbM : Mismatch AUTOSAR Version in StbM_Version.c"

#endif

/* StbM Software Version Information */
#if ((STBM_SW_MAJOR_VERSION != STBM_VERSION_SW_MAJOR_VERSION) || \
    (STBM_SW_MINOR_VERSION != STBM_VERSION_SW_MINOR_VERSION) || \
    (STBM_SW_PATCH_VERSION != STBM_VERSION_SW_PATCH_VERSION))

#error "StbM : Mismatch Software Version in StbM_Version.c"

#endif

/* RTE AUTOSAR Specification Version Information */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) \
  && defined(RTE_AR_RELEASE_MINOR_VERSION)

#if ((RTE_AR_RELEASE_MAJOR_VERSION != STBM_RTE_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != STBM_RTE_AR_RELEASE_MINOR_VERSION))

#error "StbM : Mismatch AUTOSAR Version with Rte.h"

#endif
#endif

/* Det AUTOSAR Specification Version Information */
#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
  && defined(DET_AR_RELEASE_MINOR_VERSION)

#if ((DET_AR_RELEASE_MAJOR_VERSION != STBM_DET_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != STBM_DET_AR_RELEASE_MINOR_VERSION))

#error "StbM : Mismatch AUTOSAR Version with Det.h"

#endif
#endif

/* Os AUTOSAR Specification Version Information */
#if defined(OS_AR_RELEASE_MAJOR_VERSION) \
  && defined(OS_AR_RELEASE_MINOR_VERSION)

#if ((OS_AR_RELEASE_MAJOR_VERSION != STBM_OS_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != STBM_OS_AR_RELEASE_MINOR_VERSION))

#error "StbM : Mismatch AUTOSAR Version with Os.h"

#endif
#endif

/* Gpt AUTOSAR Specification Version Information */
#if defined(GPT_AR_RELEASE_MAJOR_VERSION) \
  && defined(GPT_AR_RELEASE_MINOR_VERSION)

#if (GPT_AR_RELEASE_MAJOR_VERSION != STBM_GPT_AR_RELEASE_MAJOR_VERSION)
#if  ((GPT_AR_RELEASE_MINOR_VERSION != STBM_GPT_AR_RELEASE_MINOR_VERSION_AR44) || \
     (GPT_AR_RELEASE_MINOR_VERSION != STBM_GPT_AR_RELEASE_MINOR_VERSION_AR43))

#error "StbM : Mismatch AUTOSAR Version with Gpt.h"

#endif
#endif
#endif

/* EthIf AUTOSAR Specification Version Information */
#if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
#if defined(ETHIF_AR_RELEASE_MAJOR_VERSION) \
  && defined(ETHIF_AR_RELEASE_MINOR_VERSION)

#if ((ETHIF_AR_RELEASE_MAJOR_VERSION != STBM_ETHIF_AR_RELEASE_MAJOR_VERSION) || \
     (ETHIF_AR_RELEASE_MINOR_VERSION != STBM_ETHIF_AR_RELEASE_MINOR_VERSION))

#error "StbM : Mismatch AUTOSAR Version with EthIf.h"

#endif
#endif
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

