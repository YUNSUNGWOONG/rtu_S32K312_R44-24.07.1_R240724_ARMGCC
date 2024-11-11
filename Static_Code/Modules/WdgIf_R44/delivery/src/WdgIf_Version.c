/* polyspace +1 MISRA2012:1.1 [Justified: Low] "Macro definitions are needed for performance and file size" */
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
**  SRC-MODULE: WdgIf_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDGIF                                 **
**                                                                            **
**  PURPOSE   : AutoEver Custom Watchdog Interface Check Version              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 0.0.1     23-Sep-2019 <Tungdt39>         R44-Redmine <#1440>               **
** 1.3.1     09-Aug-2022 <TriBD>            CP44-729, CP44-323                **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgIf_Version.h"
#include "Det.h"
/*******************************************************************************
**                      Check Version                                         **
*******************************************************************************/
/* check ARS version of file WdgIf_Version.h */
#if (WDGIF_AR_RELEASE_MAJOR_VERSION != WDGIF_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "WdgIf_Version.h : Mismatch in Specification Major Version"
#endif /* End of #if (WDGIF_AR_RELEASE_MAJOR_VERSION != WDGIF_VERSION_AR_RELEASE_MAJOR_VERSION) */
#if (WDGIF_AR_RELEASE_MINOR_VERSION != WDGIF_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "WdgIf_Version.h : Mismatch in Specification Minor Version"
#endif /* End of #if (WDGIF_AR_RELEASE_MINOR_VERSION != WDGIF_VERSION_AR_RELEASE_MINOR_VERSION) */
#if (WDGIF_AR_RELEASE_REVISION_VERSION != WDGIF_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "WdgIf_Version.h : Mismatch in Specification revision Version"
#endif /* End of #if (WDGIF_AR_RELEASE_REVISION_VERSION != WDGIF_VERSION_AR_RELEASE_REVISION_VERSION) */

/* check SW version of file WdgIf_Version.h */
#if (WDGIF_SW_MAJOR_VERSION != WDGIF_VERSION_SW_MAJOR_VERSION)
  #error "WdgIf_Version.h : Mismatch in Specification SW Major Version"
#endif /* End of #if (WDGIF_SW_MAJOR_VERSION != WDGIF_VERSION_SW_MAJOR_VERSION) */
#if (WDGIF_SW_MINOR_VERSION != WDGIF_VERSION_SW_MINOR_VERSION)
  #error "WdgIf_Version.h : Mismatch in Specification SW Minor Version"
#endif /* End of #if (WDGIF_SW_MINOR_VERSION != WDGIF_VERSION_SW_MINOR_VERSION) */
#if (WDGIF_SW_PATCH_VERSION != WDGIF_VERSION_SW_PATCH_VERSION)
  #error "WdgIf_Version.h : Mismatch in Specification SW patch Version"
#endif /* End of #if (WDGIF_SW_PATCH_VERSION != WDGIF_VERSION_SW_PATCH_VERSION) */


/* check version of file Wdg_17_Scu.h */
#if defined(WDG_17_SCU_AR_RELEASE_MAJOR_VERSION) && defined(WDG_17_SCU_AR_RELEASE_MINOR_VERSION)
#if ((WDGIF_WDG_17_SCU_AR_RELEASE_MAJOR_VERSION != WDG_17_SCU_AR_RELEASE_MAJOR_VERSION) || \
     ((WDGIF_WDG_17_SCU_AR_R42_RELEASE_MINOR_VERSION != WDG_17_SCU_AR_RELEASE_MINOR_VERSION) && \
		(WDGIF_WDG_17_SCU_AR_R44_RELEASE_MINOR_VERSION != WDG_17_SCU_AR_RELEASE_MINOR_VERSION)))
  #error " Wdg_17_Scu.h : Mismatch AUTOSAR Version with WdgIf.h"
#endif
#endif /* End of #if defined(WDG_17_SCU_AR_RELEASE_MAJOR_VERSION) && defined(WDG_17_SCU_AR_RELEASE_MINOR_VERSION) */

/* check version of file Wdg_39_Acw.h */
#if defined(WDG_39_ACW_AR_RELEASE_MAJOR_VERSION) && defined(WDG_39_ACW_AR_RELEASE_MINOR_VERSION)
#if ((WDGIF_WDG_39_ACW_AR_RELEASE_MAJOR_VERSION != WDG_39_ACW_AR_RELEASE_MAJOR_VERSION) || \
     (WDGIF_WDG_39_ACW_AR_RELEASE_MINOR_VERSION != WDG_39_ACW_AR_RELEASE_MINOR_VERSION))
  #error " Wdg_39_Acw.h : Mismatch AUTOSAR Version with WdgIf.h"
#endif
#endif /* End of #if defined(WDG_39_ACW_AR_RELEASE_MAJOR_VERSION) && defined(WDG_39_ACW_AR_RELEASE_MINOR_VERSION) */

/* check version of file Wdg_76_Acw.h */
#if defined(WDG_76_ACW_AR_RELEASE_MAJOR_VERSION) && defined(WDG_76_ACW_AR_RELEASE_MINOR_VERSION)
#if ((WDGIF_WDG_76_ACW_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_AR_RELEASE_MAJOR_VERSION) || \
     (WDGIF_WDG_76_ACW_AR_RELEASE_MINOR_VERSION != WDG_76_ACW_AR_RELEASE_MINOR_VERSION))
  #error " Wdg_76_Acw.h : Mismatch AUTOSAR Version with WdgIf.h"
#endif
#endif /* End of #if defined(WDG_76_ACW_AR_RELEASE_MAJOR_VERSION) && defined(WDG_76_ACW_AR_RELEASE_MINOR_VERSION) */

/* check version of file Det.h */
#if defined(DET_AR_RELEASE_MAJOR_VERSION) && defined(DET_AR_RELEASE_MINOR_VERSION)
#if ((WDGIF_DET_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION) || \
     (WDGIF_DET_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION))
  #error " Det.h : Mismatch AUTOSAR Version with WdgIf.h"
#endif
#endif /* End of #if defined(DET_AR_RELEASE_MAJOR_VERSION) && defined(DET_AR_RELEASE_MINOR_VERSION) */

/* check version of file Std_Types.h */
#if defined(STDTYPES_AR_RELEASE_MAJOR_VERSION) && defined(STDTYPES_AR_RELEASE_MINOR_VERSION)
#if ((WDGIF_STDTYPES_AR_RELEASE_MAJOR_VERSION != STDTYPES_AR_RELEASE_MAJOR_VERSION) || \
     (WDGIF_STDTYPES_AR_RELEASE_MINOR_VERSION != STDTYPES_AR_RELEASE_MINOR_VERSION))
  #error " Std_Types.h : Mismatch AUTOSAR Version with WdgIf.h"
#endif
#endif /* End of #if defined(STDTYPES_AR_RELEASE_MAJOR_VERSION) && defined(STDTYPES_AR_RELEASE_MINOR_VERSION) */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

