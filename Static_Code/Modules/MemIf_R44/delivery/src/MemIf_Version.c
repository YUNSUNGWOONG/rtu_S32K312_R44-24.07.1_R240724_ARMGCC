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
**  SRC-MODULE: MemIf_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemIf Module                                          **
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
** Revision   Date            By                 Description                  **
********************************************************************************
** 0.0.1     25-Nov-2019     Ngocvm2;HuyP4      Initial Version               **
** 0.0.2     06-Jan-2020     VietPT4            Fix misra rule                **
** 0.0.3     27-Apr-2020     NgocVM2            Follow New V Cycle            **
** 0.0.4     07-Jul-2020     Thaodx        Updated SUD R44-Remine <#11836>    **
** 0.0.5     13-Jul-2020     NamTV9        Fix Defect R44-Redmine <#14587>    **
** 1.0.1     28-Aug-2021     JH Lim        Fix Defect R44-Redmine <#19737>    **
** 1.0.2     29-Jun-2022     SH Park       Improvement mobilegence            **
**                                           Classic <CP44-224, CP44-82>      **
** 1.0.3     30-Sep-2022     SH Park       Improvement mobilegence            **
**                                           Classic <CP44-77>      		      **
** 1.0.4     16-Nov-2022     ThuanLD5      Improvement mobilegence            **
**                                           Classic <CP44-1163> <CP44-1171>  **
*******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "MemIf_Version.h"
#if(MEMIF_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif
#ifdef MEMIF_FEE_DRIVER_INDEX
  #include "Fee.h"
#endif
#ifdef MEMIF_EA_DRIVER_INDEX
  #include "Ea.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define MEMIF_VERSION_AR_RELEASE_MAJOR_VERSION     4U
#define MEMIF_VERSION_AR_RELEASE_MINOR_VERSION     4U
#define MEMIF_VERSION_AR_RELEASE_REVISION_VERSION  0U

/* Software Version Information */
#define MEMIF_VERSION_SW_MAJOR_VERSION             1U
#define MEMIF_VERSION_SW_MINOR_VERSION             0U
#define MEMIF_VERSION_SW_PATCH_VERSION             4U

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* MemIf AUTOSAR Version check */
#if (MEMIF_AR_RELEASE_MAJOR_VERSION != MEMIF_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "MemIf.c : Mismatch in Specification Major Version"
#endif

#if (MEMIF_AR_RELEASE_MINOR_VERSION != MEMIF_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "MemIf.c : Mismatch in Specification Minor Version"
#endif

#if (MEMIF_AR_RELEASE_REVISION_VERSION != MEMIF_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "MemIf.c : Mismatch in Specification Revision Version"
#endif

/* MemIf Software Version check */
#if (MEMIF_SW_MAJOR_VERSION != MEMIF_VERSION_SW_MAJOR_VERSION)
  #error "MemIf.c : Mismatch in Software Major Version"
#endif

#if (MEMIF_SW_MINOR_VERSION != MEMIF_VERSION_SW_MINOR_VERSION)
  #error "MemIf.c : Mismatch in Software Minor Version"
#endif

#if (MEMIF_SW_PATCH_VERSION != MEMIF_VERSION_SW_PATCH_VERSION)
  #error "MemIf.c : Mismatch in Software Patch Version"
#endif

/* Det Version check */
#if(STD_ON == MEMIF_DEV_ERROR_DETECT)
  #if(DET_AR_RELEASE_MAJOR_VERSION != MEMIF_DET_AR_RELEASE_MAJOR_VERSION)
    #error "Det.h : Mismatch in Specification Major Version"
  #endif
  #if(DET_AR_RELEASE_MINOR_VERSION != MEMIF_DET_AR_RELEASE_MINOR_VERSION)
    #error "Det.h : Mismatch in Specification Minor Version"
  #endif
#endif

/* Ea Version check */
#ifdef MEMIF_EA_DRIVER_INDEX
  #if(EA_AR_RELEASE_MAJOR_VERSION != MEMIF_EA_AR_RELEASE_MAJOR_VERSION)
    #error "Ea.h : Mismatch in Specification Major Version"
  #endif
  #if(EA_AR_RELEASE_MINOR_VERSION != MEMIF_EA_AR_RELEASE_MINOR_VERSION)
    #error "Ea.h : Mismatch in Specification Minor Version"
  #endif
#endif

/* Fee Version check */
#ifdef MEMIF_FEE_DRIVER_INDEX
  #if(FEE_AR_RELEASE_MAJOR_VERSION != MEMIF_FEE_AR_RELEASE_MAJOR_VERSION)
    #error "Fee.h : Mismatch in Specification Major Version"
  #endif
  #if(FEE_AR_RELEASE_MINOR_VERSION != MEMIF_FEE_AR_RELEASE_MINOR_VERSION_1)
    #if(FEE_AR_RELEASE_MINOR_VERSION != MEMIF_FEE_AR_RELEASE_MINOR_VERSION_2)
      #error "Fee.h : Mismatch in Specification Minor Version"
    #endif
  #endif
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
