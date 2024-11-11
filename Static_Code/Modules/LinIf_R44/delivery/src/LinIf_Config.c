/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually  and has no impact" */
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
**  SRC-MODULE: LinIf_Config.c                                                **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Mapping configuration parameters to constants                 **
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
#include "LinIf.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#if (LINTP_SUPPORT == STD_ON)
#define LINTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */
CONST(uint16, LINTP_CONST) LinIf_Tp_Channels = LINIF_TP_CHANNELS;
CONST(uint16, LINTP_CONST) LinIf_Max_Rx_Sdu = LINIF_MAX_RX_SDU;
CONST(uint16, LINTP_CONST) LinIf_Max_Tx_Sdu = LINIF_MAX_TX_SDU;
/* polyspace-end VARIABLE:ALL [Not a defect:Low] "This variable do not interfere with each other" */

#define LINTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
