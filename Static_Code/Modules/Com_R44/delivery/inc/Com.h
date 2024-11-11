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
**  SRC-MODULE: Com.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of APIs                              **
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
** 1.1.6.0   07-Dec-2022   PhucNHM     CP44-1269                              **
** 1.1.5.0   04-Oct-2022   PhucNHM     CP44-769                               **
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #29406                     **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.3     10-May-2022   SM Kwon     R44-Redmine #27173                     **
** 1.1.2     14-Apr-2022   PhucNHM     R44-Redmine #25992                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139 #19314              **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

/* @Trace: Com_SUD_FILE_001 */

#ifndef COM_H
#define COM_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h" /* Com Stack Types header file */
#include "Com_Types.h"      /* Com Types header file */
#include "Com_Cfg.h"        /* Com Configuration header file */
#include "Com_PCTypes.h"    /* Com PCTypes header file */
#include "Com_Ram.h"
#include "Com_IpduGrp.h"
#if(COM_PARTIAL_NETWORK_SUPPORT == STD_ON)
#include "ComM_Com.h"       /* ComM COM Callback hearder file */
#endif
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
#if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#include "Com_PBcfg.h"
#endif

/* @Trace: Com_SUD_DATATYPE_001 */
/* @Trace: Com_SUD_DATATYPE_002 */
/* @Trace: Com_SUD_DATATYPE_003 */
/* @Trace: Com_SUD_DATATYPE_004 */
/* @Trace: Com_SUD_DATATYPE_005 */
/* @Trace: Com_SUD_DATATYPE_006 */
/* @Trace: Com_SUD_DATATYPE_007 */

/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary in logic */

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-begin MISRA-C3:19.7 [Not a defect:Justify with annotations] "use function like-macro for removing unused argument compiler warning" */
#define COM_UNUSED(x)                            do { \
                                                    if((uint32)(x) != \
                                                    (uint32)COM_ZERO) {} \
                                                  } while(0)
  
/* polyspace +1 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
#define COM_UNUSED_PTR(x)                        do { \
                                                    if((x) != NULL_PTR) {} \
                                                  } while(0)
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-end MISRA-C3:19.7 [Not a defect:Justify with annotations] "use function like-macro for removing unused argument compiler warning" */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* @Trace: Com_SUD_MACRO_010 */
/* Instance ID */
#define COM_INSTANCE_ID ((uint8)0x0)

/* @Trace: Com_SUD_MACRO_034 */
/* Service ID for Com Service Not Available */
#define COM_SERVICE_NOT_AVAILABLE  ((uint8)0x80)
/* Service ID for Com Busy */
#define COM_BUSY  ((uint8)0x81)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Init
   (P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST) ConfigPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_DeInit(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if(COM_VERSIONINFO_API == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, COM_VAR) versioninfo);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint32, COM_CODE) Com_GetConfigurationId(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if(COM_TX_SIGNAL_INVALID == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_InvalidateSignal (Com_SignalIdType SignalId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_SwitchIpduTxMode
  (PduIdType PduId, boolean txMode);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGINGROUP_INVALID == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup
  (Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_SIGNAL == STD_ON) ||(COM_TX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignal
  (Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL == STD_ON)||(COM_RX_SIGGROUP == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignal
  (Com_SignalIdType SignalId,
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignalGroup
  (Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* #7525 */
#if(COM_TX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignalGroupArray 
  (Com_SignalGroupIdType SignalGroupId, 
  P2CONST (uint8, AUTOMATIC, COM_CONST) SignalGroupArrayPtr );
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup
  (Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* #7525 */
#if(COM_RX_SIGGROUP == STD_ON)
#if((COM_ENABLE_SIGNALGROUP_ARRAY_API == STD_ON) &&\
  (COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray
  (Com_SignalGroupIdType SignalGroupId, 
  P2VAR (uint8, AUTOMATIC, COM_VAR) SignalGroupArrayPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType ComTxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
/* #1204 : Dummy Function for integration with BswM Module */
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType ComTxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if((COM_TX_IPDU == STD_ON) && (COM_META_DATA_SUPPORT == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSendWithMetaData
  (PduIdType PduId, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) MetaData);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendDynSignal(Com_SignalIdType SignalId,
  P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr, uint16 Length);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_DYN_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(Com_SignalIdType SignalId,
  P2VAR(void, AUTOMATIC, COM_VAR) SignalDataPtr,
  P2VAR(uint16, AUTOMATIC, COM_VAR) length);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_SIGNAL_RANGE_VALIDATION_CHECK == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_TxSigValidationCheck
						 (uint16 signalSize, uint8 signalType, 
             P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"  
#endif

#if(COM_RX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU has been received */
extern FUNC(void, COM_CODE) Com_RxIndication(PduIdType ComRxPduId,
                        P2CONST(PduInfoType, AUTOMATIC, COM_CONST)PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU
   has been transmitted on the bus */
extern FUNC(void, COM_CODE) Com_TxConfirmation
  (PduIdType ComTxPduId, Std_ReturnType result);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer when an AUTOSAR COM I-PDU is to
   be transmitted */
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(PduIdType ComTxPduId,
                              P2VAR(PduInfoType, AUTOMATIC, COM_VAR)PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU
   has been received on the bus */
extern FUNC(BufReq_ReturnType, COM_CODE) Com_StartOfReception(PduIdType
  ComRxPduId, P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPointer,
  PduLengthType TpSduLength, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) RxBufferSizePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU
   has been received on the bus */
extern FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData(PduIdType ComRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST)PduInfoPointer,
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR)RxBufferSizePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU
   has been received on the bus */
extern FUNC(void, COM_CODE)Com_TpRxIndication(
  PduIdType ComRxPduId, Std_ReturnType result);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU
   has been transmitted on the bus */
extern FUNC(BufReq_ReturnType, COM_CODE) Com_CopyTxData(PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) info,
  P2CONST(RetryInfoType, AUTOMATIC, COM_CONST) retry, 
  P2VAR(PduLengthType, AUTOMATIC, COM_VAR) availableDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
/* This function is called by the lower layer after an I-PDU
   has been transmitted on the bus */
extern FUNC(void, COM_CODE)Com_TpTxConfirmation(
  PduIdType ComTxPduId, Std_ReturnType result);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP_ARRAY_TMS == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_SigGrpArrayTMS
(P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST)LpTxSigGrp);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Com_ConfigType, COM_CONST) Com_PBConfig[];
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define COM_TX_IPDU_COUNT Com_GlNoOfTxIpdu
#endif
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary in logic */
#endif /* COM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
