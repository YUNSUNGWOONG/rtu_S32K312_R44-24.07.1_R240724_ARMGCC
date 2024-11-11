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
**  SRC-MODULE: PduR_Globals.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of Globals variable.                 **
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
** 1.0.1     22-Jun-2021   PhucNHM     R44-Redmine #18951                     **
** 1.0.0     04-Dec-2020   AUTOEVER    Initial Version                        **
*******************************************************************************/

#ifndef PDUR_GLOBALS_H
#define PDUR_GLOBALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "ComStack_Types.h"       /* Com Stack Types header file */
#include "PduR_Cfg.h"
#include "PduR_IntTypes.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
/* Global variable to store initialization status of PduR Module */
extern VAR(PduR_StateType, PDUR_VAR) PduR_InitStatus;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_8
#include "MemMap.h"
/* Routing Path Group Init Value */
extern VAR(uint8, PDUR_VAR)
  PduR_GroupPathId[PDUR_PATH_GROUP_MULTI_8_COUNT_MAX];
#define PDUR_STOP_SEC_VAR_INIT_8
#include "MemMap.h"
#endif

#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
/* PduR_UpTransmitConfig global pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
extern P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) PduR_UpTransmitConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_UpTransmitMaxPduId global variable */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduIdType, PDUR_VAR) PduR_UpTransmitMaxPduId;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((PDUR_LO_RXINDICATION == STD_ON)||(PDUR_TP_RXINDICATION == STD_ON))
/* PduR_LoRxConfig global pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
extern P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) PduR_LoRxConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_IfTpRxIndicationMaxPduId global variable */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduIdType, PDUR_VAR) PduR_IfTpRxIndicationMaxPduId;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((PDUR_LO_TXCONFIRMATION == STD_ON)||(PDUR_TP_TXCONFIRMATION == STD_ON))
/* PduR_LoTxConfig global pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
extern P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) PduR_LoTxConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_IfTpConfirmationMaxPduId global variable */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduIdType, PDUR_VAR) PduR_IfTpConfirmationMaxPduId;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
/* PduR_TxBufferConfig global pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
extern P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) PduR_TxBufferConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_TxBufRoutingCount global variable */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
extern VAR(uint16, PDUR_VAR) PduR_TxBufRoutingCount;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

#if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
/* PduR_TpBufferConfig global pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
extern P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) PduR_TpBufferConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_TpBufRoutingCount global variable */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
extern VAR(uint16, PDUR_VAR) PduR_TpBufRoutingCount;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

/* PduR_ConfigurationId global variable */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
extern VAR(uint16, PDUR_VAR) PduR_ConfigurationId;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"

#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
/* PduR_RoutingPathGroupMaxId global variable */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
extern VAR(uint16, PDUR_VAR) PduR_RoutingPathGroupMaxId;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

#if ((PDUR_TP_TXCONFIRMATION == STD_ON) &&\
  (PDUR_TP_GATEWAY_OPERATION == STD_ON))
/* PduR_TpGWLowDestCount global variable */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
extern VAR(uint16, PDUR_VAR) PduR_TpGWLowDestCount;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif
#endif /* #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON) */

#endif /* PDUR_GLOBALS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
