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
**  SRC-MODULE: EcuM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.2.5     24-Nov-2023   Eugean Kim    	   CP44-3054,3055                 **
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 1.0.0     03-Mar-2020   LocLT5        R44-Redmine #655, #8668              **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Version.h"        /* EcuM Version Header File */
#include "BswM.h"             /* BswM version header file */
#include "Rte.h"              /* Rte version header file */
#include "Gpt.h"              /* Gpt version header file */
#include "ComM.h"             /* ComM version header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* EcuM AUTOSAR Version check */
#if ((ECUM_AR_RELEASE_MAJOR_VERSION != ECUM_VERSION_AR_RELEASE_MAJOR_VERSION)||\
    (ECUM_AR_RELEASE_MINOR_VERSION != ECUM_VERSION_AR_RELEASE_MINOR_VERSION))
  #error "EcuM : Mismatch AUTOSAR Version in EcuM_Version.c"
#endif

/* EcuM Software Version check */
#if ((ECUM_SW_MAJOR_VERSION != ECUM_VERSION_SW_MAJOR_VERSION) || \
     (ECUM_SW_MINOR_VERSION != ECUM_VERSION_SW_MINOR_VERSION) || \
     (ECUM_SW_PATCH_VERSION != ECUM_VERSION_SW_PATCH_VERSION))
  #error "EcuM : Mismatch Software Version in EcuM_Version.c"
#endif

/* BswM version check */
#if defined(BSWM_AR_RELEASE_MAJOR_VERSION) && \
    defined(BSWM_AR_RELEASE_MINOR_VERSION)
#if ((BSWM_AR_RELEASE_MAJOR_VERSION != ECUM_BSWM_AR_RELEASE_MAJOR_VERSION) || \
     (BSWM_AR_RELEASE_MINOR_VERSION != ECUM_BSWM_AR_RELEASE_MINOR_VERSION))
  #error " EcuM : Mismatch AUTOSAR Version with BswM.h"
#endif
#endif

/* Rte version check */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) && \
    defined(RTE_AR_RELEASE_MINOR_VERSION)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != ECUM_RTE_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != ECUM_RTE_AR_RELEASE_MINOR_VERSION))
  #error " EcuM : Mismatch AUTOSAR Version with Rte.h"
#endif
#endif

/* Gpt version check */
#if defined(GPT_AR_RELEASE_MAJOR_VERSION) && \
    defined(GPT_AR_RELEASE_MINOR_VERSION)
#if ((GPT_AR_RELEASE_MAJOR_VERSION != ECUM_GPT_AR_RELEASE_MAJOR_VERSION) || \
    ((GPT_AR_RELEASE_MINOR_VERSION < ECUM_GPT_AR_R42_RELEASE_MINOR_VERSION) || \
     (GPT_AR_RELEASE_MINOR_VERSION > ECUM_GPT_AR_R48_RELEASE_MINOR_VERSION)))
  #error " EcuM : Mismatch AUTOSAR Version with Gpt.h"
#endif
#endif

/* ComM version check */
#if defined(COMM_AR_RELEASE_MAJOR_VERSION) && \
    defined(COMM_AR_RELEASE_MINOR_VERSION)
#if ((COMM_AR_RELEASE_MAJOR_VERSION != ECUM_COMM_AR_RELEASE_MAJOR_VERSION) || \
     (COMM_AR_RELEASE_MINOR_VERSION != ECUM_COMM_AR_RELEASE_MINOR_VERSION))
  #error " EcuM : Mismatch AUTOSAR Version with ComM.h"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

