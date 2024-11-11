/* polyspace +1 MISRA2012:1.1 [Not a Defect:Low] "Macro definitions are needed for performance and file size" */
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted with **
**  Hyundai Autoever, and any other use is prohibited.                        **
**  If you use it for other  purposes or change the source code, you may take **
**  legal responsibility.                                                     **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Version.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
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
** Revision  Date          By           Description                           **
********************************************************************************
** 0.0.1     11-Oct-2019   DongNx       Initial version                       **
** 1.3.1     27-May-2022   TriBD        R44_2021 #27603                       **
**           30-Jun-2022   TriBD        #CP44-324                             **
** 1.3.2     09-Aug-2022   TriBD        #CP44-384 (update UNECE standard)     **
** 1.3.4     17-Jul-2023   JHKim        #CP44-2519                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace +1 MISRA2012:1.1 [Not a Defect:Low] "Macro definitions are needed for performance and file size" */

/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Version.h"



/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Wdg_76_Acw version check */
#if (WDG_76_ACW_AR_RELEASE_MAJOR_VERSION != \
  WDG_76_ACW_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Specification Major Version"
#endif

#if (WDG_76_ACW_AR_RELEASE_MINOR_VERSION != \
  WDG_76_ACW_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Specification Minor Version"
#endif

#if (WDG_76_ACW_AR_RELEASE_REVISION_VERSION != \
  WDG_76_ACW_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Specification Revision Version"
#endif

#if (WDG_76_ACW_SW_MAJOR_VERSION != WDG_76_ACW_VERSION_SW_MAJOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Software Major Version"
#endif

#if (WDG_76_ACW_SW_MINOR_VERSION != WDG_76_ACW_VERSION_SW_MINOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Software Minor Version"
#endif

#if (WDG_76_ACW_SW_PATCH_VERSION != WDG_76_ACW_VERSION_SW_PATCH_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Software Patch Version"
#endif

/* DET Version check */
#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
  && defined(DET_AR_RELEASE_MINOR_VERSION)
#if (DET_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif
#if (DET_AR_RELEASE_MINOR_VERSION != WDG_76_ACW_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif /* #if(WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

/* DEM Version check */
#if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
#if defined(DEM_AR_RELEASE_MAJOR_VERSION) \
  && defined(DEM_AR_RELEASE_MINOR_VERSION)
#if (DEM_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_DEM_AR_RELEASE_MAJOR_VERSION)
  #error "Dem.h : Mismatch in Specification Major Version"
#endif
#if (DEM_AR_RELEASE_MINOR_VERSION != WDG_76_ACW_DEM_AR_RELEASE_MINOR_VERSION)
  #error "Dem.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif /* #if(WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */

/* DIO Version check */
#if defined(DIO_AR_RELEASE_MAJOR_VERSION) \
 && defined(DIO_AR_RELEASE_MINOR_VERSION)
#if (DIO_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_DIO_AR_RELEASE_MAJOR_VERSION)
  #error "Wdg : Mismatch AUTOSAR Version with Dio.h"
#endif
#if (DIO_AR_RELEASE_MINOR_VERSION < WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_L)
  #error "Wdg : Mismatch AUTOSAR Version with Dio.h"
#endif
#if (DIO_AR_RELEASE_MINOR_VERSION > WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_U)
  #error "Wdg : Mismatch AUTOSAR Version with Dio.h"
#endif
#endif /* #if defined(DIO_AR_RELEASE_MAJOR_VERSION) */

/* GPT version check */
#if defined(GPT_AR_RELEASE_MAJOR_VERSION) \
 && defined(GPT_AR_RELEASE_MINOR_VERSION)
#if (GPT_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_GPT_AR_RELEASE_MAJOR_VERSION)
  #error "Wdg : Mismatch AUTOSAR Version with Gpt.h"
#endif
#if (GPT_AR_RELEASE_MINOR_VERSION < WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_L)
  #error "Wdg : Mismatch AUTOSAR Version with Gpt.h"
#endif
#if (GPT_AR_RELEASE_MINOR_VERSION > WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_U)
  #error "Wdg : Mismatch AUTOSAR Version with Gpt.h"
#endif
#endif /* #if defined(GPT_AR_RELEASE_MAJOR_VERSION) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
