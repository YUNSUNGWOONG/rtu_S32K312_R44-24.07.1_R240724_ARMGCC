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
**  INC-MODULE:           ComXf_Version.c                                     **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file provides definitions of packing functions **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                         Revision History                                   **
********************************************************************************
** Revision  Date             By          Description                         **
********************************************************************************
** 1.0.0     22-Feb-2020      HIEPVT1         Initial Version                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/* Include for ComXf_Version.h */
#include "ComXf_Version.h"
/* Include for ComXf_Cfg.h */
#include "ComXf_Cfg.h"
/* Include for Det.h */
#if(COMXF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* End of (COMXF_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
**                      File Version Check                                    **
*******************************************************************************/

/* COMXF AUTOSAR Version check */
#if ((COMXF_AR_RELEASE_MAJOR_VERSION != COMXF_VERSION_AR_RELEASE_MAJOR_VERSION) || \
      (COMXF_AR_RELEASE_MINOR_VERSION != COMXF_VERSION_AR_RELEASE_MINOR_VERSION) || \
      (COMXF_AR_RELEASE_REVISION_VERSION != COMXF_VERSION_AR_RELEASE_REVISION_VERSION))
#error "COMXF : Mismatch AUTOSAR Version in COMXF_Version.c "
#endif
/* COMXF Software Version check */
#if ((COMXF_SW_MAJOR_VERSION != COMXF_VERSION_SW_MAJOR_VERSION) || \
     (COMXF_SW_MINOR_VERSION != COMXF_VERSION_SW_MINOR_VERSION) || \
     (COMXF_SW_PATCH_VERSION != COMXF_VERSION_SW_PATCH_VERSION))
  #error "COMXF : Mismatch Software Version in COMXF_Version.c "
#endif

#if(COMXF_DEV_ERROR_DETECT == STD_ON)
/* DET Version check */
#if defined(DET_AR_RELEASE_MAJOR_VERSION)\
  && defined(DET_AR_RELEASE_MINOR_VERSION)
#if ((DET_AR_RELEASE_MAJOR_VERSION != COMXF_DET_AR_RELEASE_MAJOR_VERSION) || \
    (DET_AR_RELEASE_MINOR_VERSION != COMXF_DET_AR_RELEASE_MINOR_VERSION))
#error "COMXF : Mismatch AUTOSAR Version with DET.h"
#endif
#endif
#endif /* End of (COMXF_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/