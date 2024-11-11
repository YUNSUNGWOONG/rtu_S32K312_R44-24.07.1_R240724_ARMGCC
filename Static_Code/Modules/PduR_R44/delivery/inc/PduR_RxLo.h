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
**  SRC-MODULE: PduR_RxLo.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Header file of PduR_RxLo.c                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 1.0.9.0_HF1 24-May-2024   Mj Kim      CP44-3752                            **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/
#ifndef PDUR_RXLO_H
#define PDUR_RXLO_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(void, PDUR_CODE) PduR_LoRxIndication(PduIdType rxPduId,
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);
#else
extern FUNC(void, PDUR_CODE) PduR_LoRxIndication(PduIdType rxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);

#endif /*#if (PDUR_DEV_ERROR_DETECT == STD_ON)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_LO_RXINDICATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)*/


#endif /* PDUR_RXLO_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
