/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Fota                                                  **
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
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.0     23-Dec-2022  VuPH6       Initial Version                         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Fota.h"           /* Generated Header File */
#include "Fota_Cfg.h"           /* Generated Header File */
#include "Fota_Version.h"       /* Fota Version Header File */
#include "Csm.h"          /* Csm Inclusion Header File */
#include "Mem_76_Pfls_Version.h"          /* Mem Inclusion Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#if ((FOTA_AR_RELEASE_MAJOR_VERSION != FOTA_VERSION_AR_RELEASE_MAJOR_VERSION)||\
     (FOTA_AR_RELEASE_MINOR_VERSION != FOTA_VERSION_AR_RELEASE_MINOR_VERSION))
#error "Fota: Mismatch AUTOSAR Version in Fota_Version.c"
#endif

/* Software Version Information */
#if ((FOTA_SW_MAJOR_VERSION != FOTA_VERSION_SW_MAJOR_VERSION)||\
     (FOTA_SW_MINOR_VERSION != FOTA_VERSION_SW_MINOR_VERSION)||\
     (FOTA_SW_PATCH_VERSION != FOTA_VERSION_SW_PATCH_VERSION))
#error "Fota: Mismatch Software Version in Fota_Version.c"
#endif

/* CSM Version check*/
#if (FOTA_CSM_SUPPORT == STD_ON)
#if ((CSM_AR_RELEASE_MAJOR_VERSION != FOTA_CSM_AR_RELEASE_MAJOR_VERSION)||\
     (CSM_AR_RELEASE_MINOR_VERSION != FOTA_CSM_AR_RELEASE_MINOR_VERSION))
#error "Csm : Mismatch AUTOSAR Version with Csm.h"
#endif
#endif /* End of if (FOTA_CSM_SUPPORT == STD_ON) */

/* MEM Version Check */
#if ((MEM_76_PFLS_VERSION_AR_RELEASE_MAJOR_VERSION != FOTA_MEM_76_PFLS_AR_RELEASE_MAJOR_VERSION)||\
     (MEM_76_PFLS_VERSION_AR_RELEASE_MINOR_VERSION != FOTA_MEM_76_PFLS_AR_RELEASE_MINOR_VERSION))
#error "Mem_76_Pfls : Mismatch AUTOSAR Version with Mem_76_Pfls.h"
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
