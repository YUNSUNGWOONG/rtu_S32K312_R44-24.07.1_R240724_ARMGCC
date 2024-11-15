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
**  FILE-NAME: PduR_Com.h                                            **
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
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
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

#ifndef PDUR_COM_H
#define PDUR_COM_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Extern Declaration for PduR_ComTransmit() API */
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit(PduIdType txPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);

/* Extern Declaration for PduR_ComCancelTransmit() API */
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_ComCancelTransmit(PduIdType txPduId);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* PDUR_CANIF_H*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
