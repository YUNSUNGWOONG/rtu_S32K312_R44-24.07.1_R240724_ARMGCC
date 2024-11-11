/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
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
**  SRC-MODULE: LinTp_Ram.c                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Global RAM variables of LIN Interface                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date           By                 Description                **
********************************************************************************
** 1.0.6         17-Oct-2022    KhaLN1             #CP44-563                  **
** 1.0.3         17-Sep-2021    DuyNGB             R44-Redmine #20121         **
** 1.0.1         20-Apr-2021    LongTQB            R44-Redmine #17195         **
** 1.0.0         22-Dec-2020    SJ Kim             Initial version            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "LinIf_Cfg.h"
#if(LINTP_SUPPORT == STD_ON)
#include "LinTp_Ram.h"  /* Module RAM header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: LinTp_SUD_MACRO_004 */
/* AUTOSAR Specification version information */
#define LINTP_RAM_C_AR_RELEASE_MAJOR_VERSION    4
#define LINTP_RAM_C_AR_RELEASE_MINOR_VERSION    4
#define LINTP_RAM_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define LINTP_RAM_C_SW_MAJOR_VERSION    1
#define LINTP_RAM_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (LINTP_RAM_AR_RELEASE_MAJOR_VERSION != LINTP_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "LinTp_Ram.c : Mismatch in Specification Major Version"
#endif
#if (LINTP_RAM_AR_RELEASE_MINOR_VERSION != LINTP_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "LinTp_Ram.c : Mismatch in Specification Major Version"
#endif
#if (LINTP_RAM_AR_RELEASE_REVISION_VERSION != \
  LINTP_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "LinTp_Ram.c : Mismatch in Specification Major Version"
#endif
#if (LINTP_RAM_SW_MAJOR_VERSION != LINTP_RAM_C_SW_MAJOR_VERSION)
  #error "LinTp_Ram.c : Mismatch in Major Version"
#endif
#if (LINTP_RAM_SW_MINOR_VERSION != LINTP_RAM_C_SW_MINOR_VERSION)
  #error "LinTp_Ram.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

#define LINTP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of LIN Interface */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */
VAR (boolean, LINTP_VAR) LinTp_GblInitSts;
#define LINTP_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define LINTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: LinTp_SUD_CONSTVAR_013 */
/* Global pointer to hold first channel data structure address */
P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST)
  LinTp_GpFirstChannel;
#define LINTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#ifdef LINIF_TP_CHANNELS
#define LINTP_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Array for N_As, N_Cs/N_Cr Timers for all the channels */
VAR(uint16, LINTP_VAR) LinTp_GaaTimers[LINIF_TP_CHANNELS][LINTP_THREE];
/* polyspace-end VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */
#define LINTP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif

#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
