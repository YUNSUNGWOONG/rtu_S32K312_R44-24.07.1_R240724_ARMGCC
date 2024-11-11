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
**  SRC-MODULE: LinIf_Ram.c                                                   **
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
** Revision    Date          By              Description                      **
********************************************************************************
** 1.0.3       17-Sep-2021   DuyNGB          R44-Redmine #20121               **
** 1.0.1       20-Apr-2021   LongTQB         R44-Redmine #17195               **
** 1.0.0       22-Dec-2020   SJ Kim          Initial version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinIf_Ram.h"            /* LinIf RAM header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
#define LINIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of LIN Interface */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */
VAR (boolean, LINIF_ZERO_INIT_DATA) LinIf_GblInitSts;
/* polyspace-end VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */
#define LINIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
