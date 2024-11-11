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
**  SRC-MODULE: LinTp_Tx.h                                                    **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR LINIF TP Tx Internal Functions.          **
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

#ifndef LINTP_TX_H
#define LINTP_TX_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinTp.h"                    /* LinIf TP header */
#include "LinTp_PCTypes.h"            /* LinTp pre compile header file */
#include "LinIf_PCTypes.h"            /* LinIf pre compile header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: LinTp_SUD_MACRO_009 */
/*
 * AUTOSAR specification version information
 */
#define LINTP_TX_AR_RELEASE_MAJOR_VERSION  (LINIF_AR_RELEASE_MAJOR_VERSION)
#define LINTP_TX_AR_RELEASE_MINOR_VERSION  (LINIF_AR_RELEASE_MINOR_VERSION)
#define LINTP_TX_AR_RELEASE_REVISION_VERSION  (LINIF_AR_RELEASE_REVISION_VERSION)

/*
 * File version information
 */
#define LINTP_TX_SW_MAJOR_VERSION  (LINIF_SW_MAJOR_VERSION)
#define LINTP_TX_SW_MINOR_VERSION  (LINIF_SW_MINOR_VERSION)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define LINTP_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, LINTP_CODE) LinTp_CopyDataTxBuff (P2CONST
  (LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelInfo);

extern FUNC(void, LINIF_CODE) LinTp_PrepareNextTxFrame (P2VAR
  (LinTp_ChannelRamData, AUTOMATIC, LINIF_APPL_DATA) LpTpChannelRamData);

extern FUNC(void, LINIF_CODE) LinTp_UpdateFrameStatus (P2VAR
  (LinTp_ChannelRamData, AUTOMATIC, LINIF_APPL_DATA) LpTpChannelRamData);

#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* LINTP_RX_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
