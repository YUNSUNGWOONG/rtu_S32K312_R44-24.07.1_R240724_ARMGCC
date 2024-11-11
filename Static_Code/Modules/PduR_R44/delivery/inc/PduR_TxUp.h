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
**  SRC-MODULE: PduR_TxUp.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Header file of PduR_TxUp.c                                    **
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
#ifndef PDUR_TXUP_H
#define PDUR_TXUP_H

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
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);

#else
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType txPduId,
 P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);

#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_IF_TRANSMIT == STD_ON)||
        *(PDUR_TP_TRANSMIT == STD_ON))*/
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */



#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(Std_ReturnType, PDUR_CODE)PduR_UpCancelTransmit(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType);

#else
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_UpCancelTransmit(PduIdType
                                                                    txPduId);

#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif



#endif /* PDUR_TXUP_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
