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
**  SRC-MODULE: PduR_Globals.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of Initialization of Globals variable.              **
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
** 1.0.2     05-Oct-2021   PhucNHM     R44-Redmine #20586                     **
** 1.0.1     22-Jun-2021   PhucNHM     R44-Redmine #18951                     **
** 1.0.0     04-Dec-2020   AUTOEVER    Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"                         /* PDU Router RAM header */
#include "PduR_Globals.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace:begin <VARIABLE:*:Not a defect:Low> "this variable do not interfere with each other" */
/* @Trace: SRS_BSW_00415 */ 
/* @Trace: PduR_SUD_GLOBALVAR_001 */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store initialization status of PduR Module */
VAR(PduR_StateType, PDUR_VAR) PduR_InitStatus;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
/* PduR_UpTransmitConfig pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) PduR_UpTransmitConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_UpTransmitMaxPduId */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
VAR(PduIdType, PDUR_VAR) PduR_UpTransmitMaxPduId;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((PDUR_LO_RXINDICATION == STD_ON)||(PDUR_TP_RXINDICATION == STD_ON))
/* PduR_LoRxConfig pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) PduR_LoRxConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_IfTpRxIndicationMaxPduId */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
VAR(PduIdType, PDUR_VAR) PduR_IfTpRxIndicationMaxPduId;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((PDUR_LO_TXCONFIRMATION == STD_ON)||(PDUR_TP_TXCONFIRMATION == STD_ON))
/* PduR_LoTxConfig pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) PduR_LoTxConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_IfTpConfirmationMaxPduId */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
VAR(PduIdType, PDUR_VAR) PduR_IfTpConfirmationMaxPduId;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
/* PduR_TxBufferConfig pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) PduR_TxBufferConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_TxBufRoutingCount */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
VAR(uint16, PDUR_VAR) PduR_TxBufRoutingCount;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

#if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
/* PduR_TpBufferConfig pointer */
#define PDUR_START_SEC_VAR_INIT_PTR
#include "MemMap.h"
P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) PduR_TpBufferConfig;
#define PDUR_STOP_SEC_VAR_INIT_PTR
#include "MemMap.h"

/* PduR_TpBufRoutingCount */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
VAR(uint16, PDUR_VAR) PduR_TpBufRoutingCount;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

/* PduR_ConfigurationId */
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
VAR(uint16, PDUR_VAR) PduR_ConfigurationId;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"

/* PduR_RoutingPathGroupMaxId */
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
VAR(uint16, PDUR_VAR) PduR_RoutingPathGroupMaxId;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif

/* PduR_TpGWLowDestCount */
#if ((PDUR_TP_TXCONFIRMATION == STD_ON) &&\
  (PDUR_TP_GATEWAY_OPERATION == STD_ON))
#define PDUR_START_SEC_VAR_INIT_16
#include "MemMap.h"
VAR(uint16, PDUR_VAR) PduR_TpGWLowDestCount;
#define PDUR_STOP_SEC_VAR_INIT_16
#include "MemMap.h"
#endif
#endif /* #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON) */

/* polyspace:end <VARIABLE:*:Not a defect:Low> "this variable do not interfere with each other" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
