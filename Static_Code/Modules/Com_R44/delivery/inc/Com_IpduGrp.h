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
**  SRC-MODULE: Com_IpduGrp.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of I-PDU group intexternal functions.**
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
** 1.1.11.0  10-Oct-2023   PhucNHM     CP44-2759                              **
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

#ifndef COM_IPDUGRP_H
#define COM_IPDUGRP_H

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
#if((COM_TX_IPDU == STD_ON) || (COM_RX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_IpduGroupStart(Com_IpduGroupIdType IpduGroupId,
                                                          boolean Initialize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
/* #1204 : Dummy Function for integration with BswM Module */
extern FUNC(void, COM_CODE) Com_IpduGroupStart(Com_IpduGroupIdType IpduGroupId,
                                                          boolean Initialize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON) 
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_StartTxIPDUs(
                    PduIdType IpduIndex, boolean Initialize, boolean blIpduGrp);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_IPDU == STD_ON) 
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_StartRxIPDUs(
                    PduIdType IpduIndex, boolean Initialize, boolean blIpduGrp);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


#if((COM_TX_IPDU == STD_ON) || (COM_RX_IPDU == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_IpduGroupStop(Com_IpduGroupIdType IpduGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
/* #1204 : Dummy Function for integration with BswM Module */
extern FUNC(void, COM_CODE) Com_IpduGroupStop(Com_IpduGroupIdType IpduGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


#if((COM_RX_IPDU_DM == STD_ON) || \
  (COM_RX_SIGNAL_UBDM == STD_ON) || \
  (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_EnableReceptionDM
  (Com_IpduGroupIdType IpduGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
/* #1204 : Dummy Function for integration with BswM Module */
extern FUNC(void, COM_CODE) Com_EnableReceptionDM
  (Com_IpduGroupIdType IpduGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_IPDU_DM == STD_ON) || \
  (COM_RX_SIGNAL_UBDM == STD_ON) || \
  (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_DisableReceptionDM
  (Com_IpduGroupIdType IpduGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
/* #1204 : Dummy Function for integration with BswM Module */
extern FUNC(void, COM_CODE) Com_DisableReceptionDM
  (Com_IpduGroupIdType IpduGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON) 
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxCounterUpdate
   (P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) LpTxIpduCounter);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_ReadReceiveIpduList(
                                                   PduIdType* ComRxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_WriteReceiveIpduList(PduIdType ComRxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_ResetReceiveIpduList(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_IpduFilterStatusUpdate(
  P2CONST(Com_TxIpduModeSel, AUTOMATIC, COM_CONST) LpTxModeSelect,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpFilterStatus,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpFilterResult,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LucFilterStatusIndex);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) &&\
  ((COM_TX_IPDU_GROUP_COUNT_MAX>0) || (COM_RX_IPDU_GROUP_COUNT_MAX >0))) || \
  ((COM_TX_IPDU_GROUP_COUNT>0) || (COM_RX_IPDU_GROUP_COUNT >0)))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxBuffersReInit(PduIdType LddIpduHandleId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif /* COM_IPDUGRP_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
