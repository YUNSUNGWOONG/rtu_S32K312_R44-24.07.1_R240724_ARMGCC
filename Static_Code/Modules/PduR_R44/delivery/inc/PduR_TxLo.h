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
**  SRC-MODULE: PduR_TxLo.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Header file of PduR_TxLo.c                                    **
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
** 1.0.4       11-Aug-2022   PhucNHM     CP44-635                             **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

#ifndef PDUR_TXLO_H
#define PDUR_TXLO_H

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
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(void, PDUR_CODE) PduR_LoTxConfirmation(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType, Std_ReturnType result);
#else
extern FUNC(void, PDUR_CODE) PduR_LoTxConfirmation(PduIdType txPduId,
  Std_ReturnType result);
#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* End of if (PDUR_LO_TXCONFIRMATION == STD_ON) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_LoTriggerTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr);

#else
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_LoTriggerTransmit
  (PduIdType txPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr);

#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&
        *(PDUR_LO_TXCONFIRMATION == STD_ON)) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */




#endif /* PDUR_TXLO_H */

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
