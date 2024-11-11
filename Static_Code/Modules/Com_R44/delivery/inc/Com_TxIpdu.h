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
**  SRC-MODULE: Com_TxIpdu.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of initialization functions.         **
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
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

#ifndef COM_TXIPDU_H
#define COM_TXIPDU_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#if ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
  (COM_TX_IPDU_REPETITION == STD_ON) || (COM_TX_IPDU_GW == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_TxRequest(PduIdType LddTxPduId,
                                                              uint8 LucConfig);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_TxRequest
                               (PduIdType LddTxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_TxIpduTMSCalc
                              (PduIdType LddTxPduId, uint8 LucConfig);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif /* COM_MAIN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
