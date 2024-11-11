/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't master." */
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
**  SRC-MODULE: CanCM_Version.c                                               **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.9     20-Dec-2023   HieuTM8          CP44-3561                         **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM_Version.h"

/* @Trace: SRS_BSW_00447 */
/* Inter Module check for Det.h */
#if ((defined DET_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined DET_AR_RELEASE_MINOR_VERSION))
  #if ((DET_AR_RELEASE_MAJOR_VERSION != CANCM_DET_AR_RELEASE_MAJOR_VERSION) || \
      ((DET_AR_RELEASE_MINOR_VERSION != CANCM_DET_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (DET_AR_RELEASE_MINOR_VERSION != CANCM_DET_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version with Det.h"
  #endif
#endif

/* Inter Module check for Dem.h */
#if ((defined DEM_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined DEM_AR_RELEASE_MINOR_VERSION))
  #if ((DEM_AR_RELEASE_MAJOR_VERSION != CANCM_DEM_AR_RELEASE_MAJOR_VERSION) || \
      ((DEM_AR_RELEASE_MINOR_VERSION != CANCM_DEM_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (DEM_AR_RELEASE_MINOR_VERSION != CANCM_DEM_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version with Dem.h"
  #endif
#endif

/* Inter Module check for EcuM.h */
#if ((defined ECUM_AR_RELEASE_MAJOR_VERSION) && \
                                        (defined ECUM_AR_RELEASE_MINOR_VERSION))
  #if ((ECUM_AR_RELEASE_MAJOR_VERSION != CANCM_ECUM_AR_RELEASE_MAJOR_VERSION) || \
      ((ECUM_AR_RELEASE_MINOR_VERSION != CANCM_ECUM_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (ECUM_AR_RELEASE_MINOR_VERSION != CANCM_ECUM_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version with EcuM.h"
  #endif
#endif

/* Inter Module check for CanIf.h */
#if ((defined CANIF_AR_RELEASE_MAJOR_VERSION) && \
                                       (defined CANIF_AR_RELEASE_MINOR_VERSION))
  #if ((CANIF_AR_RELEASE_MAJOR_VERSION != CANCM_CANIF_AR_RELEASE_MAJOR_VERSION) || \
      ((CANIF_AR_RELEASE_MINOR_VERSION != CANCM_CANIF_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (CANIF_AR_RELEASE_MINOR_VERSION != CANCM_CANIF_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version with CanIf.h"
  #endif
#endif


/* Inter Module check for IoHwAb.h */
#if ((defined IOHWAB_AR_RELEASE_MAJOR_VERSION) && \
                                       (defined IOHWAB_AR_RELEASE_MINOR_VERSION))
  #if ((IOHWAB_AR_RELEASE_MAJOR_VERSION != CANCM_IOHWAB_AR_RELEASE_MAJOR_VERSION) || \
      ((IOHWAB_AR_RELEASE_MINOR_VERSION != CANCM_IOHWAB_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (IOHWAB_AR_RELEASE_MINOR_VERSION != CANCM_IOHWAB_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version IoHwAb.h"
  #endif
#endif

/* Inter Module check for ComM.h */
#if ((defined COMM_AR_RELEASE_MAJOR_VERSION) && \
                                       (defined COMM_AR_RELEASE_MINOR_VERSION))
  #if ((COMM_AR_RELEASE_MAJOR_VERSION != CANCM_COMM_AR_RELEASE_MAJOR_VERSION) || \
      ((COMM_AR_RELEASE_MINOR_VERSION != CANCM_COMM_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (COMM_AR_RELEASE_MINOR_VERSION != CANCM_COMM_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version ComM.h"
  #endif
#endif

/* Inter Module check for BswM.h */
#if ((defined BSWM_AR_RELEASE_MAJOR_VERSION) && \
                                       (defined BSWM_AR_RELEASE_MINOR_VERSION))
  #if ((BSWM_AR_RELEASE_MAJOR_VERSION != CANCM_BSWM_AR_RELEASE_MAJOR_VERSION) || \
      ((BSWM_AR_RELEASE_MINOR_VERSION != CANCM_BSWM_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (BSWM_AR_RELEASE_MINOR_VERSION != CANCM_BSWM_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version BswM.h"
  #endif
#endif

/* Inter Module check for BswM.h */
#if ((defined RTE_AR_RELEASE_MAJOR_VERSION) && \
                                       (defined RTE_AR_RELEASE_MINOR_VERSION))
  #if ((RTE_AR_RELEASE_MAJOR_VERSION != CANCM_RTE_AR_RELEASE_MAJOR_VERSION) || \
      ((RTE_AR_RELEASE_MINOR_VERSION != CANCM_RTE_AR_RELEASE_MINOR_VERSION_FOUR) && \
       (RTE_AR_RELEASE_MINOR_VERSION != CANCM_RTE_AR_RELEASE_MINOR_VERSION_ZERO)))
    #error "CanCM : Mismatch AUTOSAR Version Rte.h"
  #endif
#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
