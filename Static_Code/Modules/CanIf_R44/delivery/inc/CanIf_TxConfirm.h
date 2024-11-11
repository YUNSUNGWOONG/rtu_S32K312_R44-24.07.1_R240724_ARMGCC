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
**  SRC-MODULE: CanIf_TxConfirm.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Prototype definition of CanIf_TxConfirm.c                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0    29-Feb-2024    Jh Yang        #CP44-2947                          **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_TXCONFIRM_H
#define CANIF_TXCONFIRM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Tx.h"              /* Transmit Header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_TXCONFIRM_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_TXCONFIRM_AR_RELEASE_MINOR_VERSION       4
#define CANIF_TXCONFIRM_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_TXCONFIRM_SW_MAJOR_VERSION       1
#define CANIF_TXCONFIRM_SW_MINOR_VERSION       1
#define CANIF_TXCONFIRM_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Inline Function                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_DummyTxConfirmation (PduIdType CanTxPduId,
    Std_ReturnType result);
extern FUNC(void, CANIF_CODE) CanIf_TxConfirmation (
                                           VAR(PduIdType, CANIF_VAR) CanIfTxSduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"


#endif /* CANIF_TX_CONFIRM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
