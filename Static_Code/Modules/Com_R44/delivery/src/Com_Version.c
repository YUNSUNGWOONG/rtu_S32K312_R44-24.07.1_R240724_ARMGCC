/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Version Information.                             **
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
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.5.0   04-Oct-2022   PhucNHM     CP44-769                               **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Com.h"                 /* Com module header file */
#include "Com_Version.h"         /* Com version header file */

#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                 /* Det module header file */
#endif

#include "PduR.h"                /* PduR module header file */
#include "Rte.h"                 /* Rte module header file */
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#if ((COM_CFG_AR_RELEASE_MAJOR_VERSION != COM_VERSION_AR_RELEASE_MAJOR_VERSION)\
  || (COM_CFG_AR_RELEASE_MINOR_VERSION != COM_VERSION_AR_RELEASE_MINOR_VERSION))
#error "Com: Mismatch AUTOSAR Version in Com_Version.c"
#endif

/* Software Version Information */
#if ((COM_SW_MAJOR_VERSION != COM_VERSION_SW_MAJOR_VERSION)||\
     (COM_SW_MINOR_VERSION != COM_VERSION_SW_MINOR_VERSION)||\
     (COM_SW_PATCH_VERSION != COM_VERSION_SW_PATCH_VERSION))
#error "Com: Mismatch Software Version in Com_Version.c"
#endif

/* PduR Version Check */
#if ((PDUR_AR_RELEASE_MAJOR_VERSION != COM_PDUR_AR_RELEASE_MAJOR_VERSION)||\
     (PDUR_AR_RELEASE_MINOR_VERSION != COM_PDUR_AR_RELEASE_MINOR_VERSION))
#error "PduR : Mismatch AUTOSAR Version with PduR.h"
#endif

/* Rte Version Check */
#if ((RTE_AR_RELEASE_MAJOR_VERSION != COM_RTE_AR_RELEASE_MAJOR_VERSION)||\
     (RTE_AR_RELEASE_MINOR_VERSION != COM_RTE_AR_RELEASE_MINOR_VERSION))
#error "Rte : Mismatch AUTOSAR Version with Rte.h"
#endif

#if(COM_PARTIAL_NETWORK_SUPPORT == STD_ON)
/* ComM Version Check */
#if ((COMM_COM_AR_RELEASE_MAJOR_VERSION != COM_COMM_AR_RELEASE_MAJOR_VERSION)||\
     (COMM_COM_AR_RELEASE_MAJOR_VERSION != COM_COMM_AR_RELEASE_MINOR_VERSION))
#error "ComM : Mismatch AUTOSAR Version with ComM_Com.h"
#endif
#endif

#if (STD_ON == COM_MULTI_CORE_SUPPORT)
/* Os Version Check */
#if ((OS_AR_RELEASE_MAJOR_VERSION != COM_OS_AR_RELEASE_MAJOR_VERSION)||\
     (OS_AR_RELEASE_MAJOR_VERSION != COM_OS_AR_RELEASE_MINOR_VERSION))
#error "Os : Mismatch AUTOSAR Version with Os.h"
#endif
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
