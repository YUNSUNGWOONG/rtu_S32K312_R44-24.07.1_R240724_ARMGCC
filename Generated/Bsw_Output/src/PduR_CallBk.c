/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter" */
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
**  FILE-NAME: PduR_CallBk.c                                                  **
**                                                                            **
**  MODULE-NAME: AUTOSAR Pdu Router Module                                    **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                          **
**  Module version : 1.0.9.0                                         **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
 * INPUT FILE(s):
*          CanIf_ECU_Configuration_PDF.arxml              
*          CanNm_ECU_Configuration_PDF.arxml              
*          CanTp_ECU_Configuration_PDF.arxml              
*          Com_ECU_Configuration_PDF.arxml                
*          Dcm_ECU_Configuration_PDF.arxml                
*          LinIf_ECU_Configuration_PDF.arxml              
*          PduR_ECU_Configuration_PDF.arxml               
*          Bswmd_LinIf.arxml                              
*          ECUConfigurationParameters.arxml               
*          Ecud_CanIf.arxml                               
*          Ecud_CanNm.arxml                               
*          Ecud_CanTp.arxml                               
*          Ecud_Com.arxml                                 
*          Ecud_Dcm.arxml                                 
*          Ecud_EcuC.arxml                                
*          Ecud_IpduM.arxml                               
*          Ecud_LinIf.arxml                               
*          Ecud_PduR.arxml                                
*          Bswmd_PduR.arxml                               
*          IpduM_ECU_Configuration_PDF.arxml              
* GENERATED ON: The time-stamp is removed

 */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"
#include "PduR_IntTypes.h"
#include "PduR_Incl.h"
#include "PduR_TxUp.h"
#include "PduR_RxLo.h"
#include "PduR_TxLo.h"
#include "PduR_RxTp.h"
#include "PduR_TxTp.h"



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_ComTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit(PduIdType txPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  Std_ReturnType returnVal;
  returnVal = PduR_UpTransmit(txPduId, PDUR_COM, ptrPduInfoPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_ComCancelTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_ComCancelTransmit(PduIdType txPduId)
{
Std_ReturnType returnVal;
returnVal = PduR_UpCancelTransmit(txPduId, PDUR_COM);
return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_LinIfTxConfirmation() API */
FUNC(void, PDUR_CODE) PduR_LinIfTxConfirmation(PduIdType txPduId,
Std_ReturnType result)
{
  PduR_LoTxConfirmation(txPduId, PDUR_LINIF, result);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"           
/* Function Definition for PduR_LinIfRxIndication() API */
FUNC(void, PDUR_CODE) PduR_LinIfRxIndication(PduIdType rxPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) ptrPduInfoPtr)
{
  PduR_LoRxIndication(rxPduId, PDUR_LINIF, ptrPduInfoPtr);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_LinIfTriggerTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_LinIfTriggerTransmit(PduIdType txPduId,
P2VAR(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  Std_ReturnType returnVal;
  returnVal = PduR_LoTriggerTransmit(txPduId, PDUR_LINIF, ptrPduInfoPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_DcmTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(PduIdType txPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  Std_ReturnType returnVal;
  returnVal = PduR_UpTransmit(txPduId, PDUR_DCM, ptrPduInfoPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function Definition for PduR_DcmCancelReceive() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmCancelReceive(PduIdType rxPduId)
{
Std_ReturnType returnVal;
returnVal = PduR_CancelReceive(rxPduId);
return returnVal;
}
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_DcmCancelTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmCancelTransmit(PduIdType txPduId)
{
Std_ReturnType returnVal;
returnVal = PduR_UpCancelTransmit(txPduId, PDUR_DCM);
return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function def inition for PduR_LinTpCopyTxData() API */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LinTpCopyTxData(PduIdType txPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) ptrPduInfoPtr,
P2CONST(RetryInfoType, AUTOMATIC, PDUR_DATA) ptrRetry,
P2VAR(PduLengthType, AUTOMATIC, PDUR_DATA) ptrAvailableDataPtr)
{
  BufReq_ReturnType returnVal;
  returnVal = PduR_LoTpCopyTxData(txPduId, PDUR_LINTP, ptrPduInfoPtr, ptrRetry, ptrAvailableDataPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"    

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_LinTpCopyRxData() API */
FUNC(BufReq_ReturnType, PDUR_CODE) 
PduR_LinTpCopyRxData(PduIdType rxPduId, 
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) pduInfoPtr, 
P2VAR(PduLengthType, AUTOMATIC, PDUR_DATA) bufferSizePtr)
{
  BufReq_ReturnType returnVal;
  returnVal = PduR_LoTpCopyRxData(rxPduId, PDUR_LINTP, pduInfoPtr, bufferSizePtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function Definition for PduR_LinTpRxIndication() API */
FUNC(void, PDUR_CODE) PduR_LinTpRxIndication(PduIdType rxPduId,
Std_ReturnType result)
{
  PduR_LoTpRxIndication(rxPduId, PDUR_LINTP, result);
}
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function Definition for PduR_LinTpStartOfReception() API */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LinTpStartOfReception
(PduIdType rxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) pduInfoPtr,
PduLengthType tpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_DATA)bufferSizePtr)
{
  BufReq_ReturnType returnVal;
  returnVal = PduR_LoTpStartOfReception(rxPduId, PDUR_LINTP, pduInfoPtr, tpSduLength, bufferSizePtr);
  return returnVal;
}
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_LinTpTxConfirmation() API */
FUNC(void, PDUR_CODE) PduR_LinTpTxConfirmation(PduIdType txPduId,
Std_ReturnType result)
{
  PduR_LoTpTxConfirmation(txPduId, PDUR_LINTP, result);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_CanIfTxConfirmation() API */
FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation(PduIdType txPduId,
Std_ReturnType result)
{
  PduR_LoTxConfirmation(txPduId, PDUR_CANIF, result);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"           
/* Function Definition for PduR_CanIfRxIndication() API */
FUNC(void, PDUR_CODE) PduR_CanIfRxIndication(PduIdType rxPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) ptrPduInfoPtr)
{
  PduR_LoRxIndication(rxPduId, PDUR_CANIF, ptrPduInfoPtr);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_CanIfTriggerTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_CanIfTriggerTransmit(PduIdType txPduId,
P2VAR(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  Std_ReturnType returnVal;
  returnVal = PduR_LoTriggerTransmit(txPduId, PDUR_CANIF, ptrPduInfoPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function def inition for PduR_CanTpCopyTxData() API */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData(PduIdType txPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) ptrPduInfoPtr,
P2CONST(RetryInfoType, AUTOMATIC, PDUR_DATA) ptrRetry,
P2VAR(PduLengthType, AUTOMATIC, PDUR_DATA) ptrAvailableDataPtr)
{
  BufReq_ReturnType returnVal;
  returnVal = PduR_LoTpCopyTxData(txPduId, PDUR_CANTP, ptrPduInfoPtr, ptrRetry, ptrAvailableDataPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"    

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_CanTpCopyRxData() API */
FUNC(BufReq_ReturnType, PDUR_CODE) 
PduR_CanTpCopyRxData(PduIdType rxPduId, 
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) pduInfoPtr, 
P2VAR(PduLengthType, AUTOMATIC, PDUR_DATA) bufferSizePtr)
{
  BufReq_ReturnType returnVal;
  returnVal = PduR_LoTpCopyRxData(rxPduId, PDUR_CANTP, pduInfoPtr, bufferSizePtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function Definition for PduR_CanTpRxIndication() API */
FUNC(void, PDUR_CODE) PduR_CanTpRxIndication(PduIdType rxPduId,
Std_ReturnType result)
{
  PduR_LoTpRxIndication(rxPduId, PDUR_CANTP, result);
}
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Function Definition for PduR_CanTpStartOfReception() API */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception
(PduIdType rxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) pduInfoPtr,
PduLengthType tpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_DATA)bufferSizePtr)
{
  BufReq_ReturnType returnVal;
  returnVal = PduR_LoTpStartOfReception(rxPduId, PDUR_CANTP, pduInfoPtr, tpSduLength, bufferSizePtr);
  return returnVal;
}
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_CanTpTxConfirmation() API */
FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation(PduIdType txPduId,
Std_ReturnType result)
{
  PduR_LoTpTxConfirmation(txPduId, PDUR_CANTP, result);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_CanNmTxConfirmation() API */
FUNC(void, PDUR_CODE) PduR_CanNmTxConfirmation(PduIdType txPduId,
Std_ReturnType result)
{
  PduR_LoTxConfirmation(txPduId, PDUR_CANNM, result);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"           
/* Function Definition for PduR_CanNmRxIndication() API */
FUNC(void, PDUR_CODE) PduR_CanNmRxIndication(PduIdType rxPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_DATA) ptrPduInfoPtr)
{
  PduR_LoRxIndication(rxPduId, PDUR_CANNM, ptrPduInfoPtr);
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"            
/* Function def inition for PduR_CanNmTriggerTransmit() API */
FUNC(Std_ReturnType, PDUR_CODE) PduR_CanNmTriggerTransmit(PduIdType txPduId,
P2VAR(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  Std_ReturnType returnVal;
  returnVal = PduR_LoTriggerTransmit(txPduId, PDUR_CANNM, ptrPduInfoPtr);
  return returnVal;
}           
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"





/*******************************************************************************
**                      ZERO COST OPERATION                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

