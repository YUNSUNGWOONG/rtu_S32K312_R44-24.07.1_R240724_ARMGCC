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
**  SRC-MODULE: Com_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of COM types.                        **
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
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-770                               **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     09-Apr-2022   PhuPV10     R44-Redmine #25517                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

#ifndef COM_TYPES_H
#define COM_TYPES_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h" /* Standard types header file  */
#include "Com_Cfg.h"
#include "Com_PCTypes.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:11.5:Not a defect:Low> This type is used to declare service ID */
/* @Trace: Com_SUD_DATATYPE_018 */
/* Typedefenition for Com Service Id */
typedef uint8 Com_ServiceIdType;
/* polyspace:end<MISRA-C3:11.5:Not a defect:Low> This type is used to declare service ID */

/* @Trace: Com_SUD_MACRO_009 */
/* Service ID of Com Initialization */
#define COMSERVICEID_INIT                         ((Com_ServiceIdType)0x01)
/* Service ID of Com De-Initialization */
#define COMSERVICEID_DEINIT                       ((Com_ServiceIdType)0x02)
/* Service ID of Com I-PDU Group start */
#define COMSERVICEID_IPDUGROUPSTART               ((Com_ServiceIdType)0x03)
/* Service ID of Com I-PDU Group stop */
#define COMSERVICEID_IPDUGROUPSTOP                ((Com_ServiceIdType)0x04)
/* Service ID of Com Reception DM disable */
#define COMSERVICEID_RECEPTIONDMDISABLE           ((Com_ServiceIdType)0x05)
/* Service ID of Com Reception DM enable */
#define COMSERVICEID_RECEPTIONDMENABLE            ((Com_ServiceIdType)0x06)
/* Service ID of Com Get Status */
#define COMSERVICEID_GETSTATUS                    ((Com_ServiceIdType)0x07)
/* Service ID of Com Configuration ID */
#define COMSERVICEID_GETCONFIGURATIONID           ((Com_ServiceIdType)0x08)
/* Service ID of Com Get Version Info */
#define COMSERVICEID_GETVERSIONINFO               ((Com_ServiceIdType)0x09)
/* Service ID of Com Send Signal */
#define COMSERVICEID_SENDSIGNAL                   ((Com_ServiceIdType)0x0A)
/* Service ID of Com Receive Signal */
#define COMSERVICEID_RECEIVESIGNAL                ((Com_ServiceIdType)0x0B)
/* Service ID of Com Send Signal Group */
#define COMSERVICEID_SENDSIGNALGROUP              ((Com_ServiceIdType)0x0D)
/* Service ID of Com Receive Signal Group */
#define COMSERVICEID_RECEIVESIGNALGROUP           ((Com_ServiceIdType)0x0E)
/* Service ID of Com Invalidate Signal */
#define COMSERVICEID_INVALIDATESIGNAL             ((Com_ServiceIdType)0x10)
/* Service ID of Com Trigger Ipdu Send */
#define COMSERVICEID_TRIGGERIPDUSEND              ((Com_ServiceIdType)0x17)
/* Service ID of Com Trigger Ipdu Send Meta Data */
#define COMSERVICEID_TRIGGERIPDUSENDWITHMETADATA  ((Com_ServiceIdType)0x28)
/* Service ID of Com Main Function Rx */
#define COMSERVICEID_MAINFUNCTIONRX               ((Com_ServiceIdType)0x18)
/* Service ID of Com Main Function Tx */
#define COMSERVICEID_MAINFUNCTIONTX               ((Com_ServiceIdType)0x19)
/* Service ID of Com Main Function Gateway */
#define COMSERVICEID_MAINFUNCTIONROUTESIGNALS     ((Com_ServiceIdType)0x1A)
/* Service ID of Com Invalidate Signal Group */
#define COMSERVICEID_INVALIDATESIGNALGROUP        ((Com_ServiceIdType)0x1B)
/* Service ID of Com Tp Rx Indication */
#define COMSERVICEID_TPRXINDICATION               ((Com_ServiceIdType)0x1E)
/* Service ID of Com Send Dynamic Signal */
#define COMSERVICEID_SENDDYNSIGNAL                ((Com_ServiceIdType)0x21)
/* Service ID of Com Tp Rx Indication */
#define COMSERVICEID_RECEIVEDYNSIGNAL             ((Com_ServiceIdType)0x22)
/* Service ID of Com Tp Rx Copy */
#define COMSERVICEID_COPYRXDATA                   ((Com_ServiceIdType)0x44)
/* Service ID of Com Tp Tx Copy */
#define COMSERVICEID_COPYTXDATA                   ((Com_ServiceIdType)0x43)
/* Service ID of Com Send Signal Group Array */
#define COMSERVICEID_SENDSIGNALGROUPARRAY         ((Com_ServiceIdType)0x23)
/* Service ID of Com Receive Signal Group Array */
#define COMSERVICEID_RECEIVESIGNALGROUPARRAY      ((Com_ServiceIdType)0x24)
/* Service ID of Com Tp Rx Indication */
#define COMSERVICEID_STARTOFRECEPTION             ((Com_ServiceIdType)0x25)
/* Service ID of Com Tp Rx Indication */
#define COMSERVICEID_TPTXCONFIRMATION             ((Com_ServiceIdType)0x26)
/* Service ID of Com Tp Rx Indication */
#define COMSERVICEID_SWITCHIPDUTXMODE             ((Com_ServiceIdType)0x27)
/* Service ID of Com Tx Confirmation */
#define COMSERVICEID_TXCONFIRMATION               ((Com_ServiceIdType)0x40)
/* Service ID of Com Trigger Transmit */
#define COMSERVICEID_TRIGGERTRANSMIT              ((Com_ServiceIdType)0x41)
/* Service ID of Com Rx Indication */
#define COMSERVICEID_RXINDICATION                 ((Com_ServiceIdType)0x42)

/* @Trace: Com_SUD_MACRO_035 */
/* Error code for API service called with wrong parameter */
#define COM_E_PARAM                               ((uint8)0x01)
/* Error code for API service called without COM being initialized */
#define COM_E_UNINIT                              ((uint8)0x02)
/* Error code for API service called with NULL Pointer */
#define COM_E_PARAM_POINTER                       ((uint8)0x03)
/* Error code for API service called when Tp is busy */
#define COM_E_SKIPPED_TRANSMISSION                ((uint8)0x05)

/* @Trace: Com_SUD_DATATYPE_080 */
/* Structure for the COM configuration type */
typedef struct
{
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  /* Number of Tx signal */
  uint16 NoOfTxSig;
  /* Number of Tx signal grp */
  uint16 NoOfTxSigGrp;
  /* Number of Tx signal In grp */
  uint16 NoOfTxSigInGrp;
  /* Number of Rx signal */
  uint16 NoOfRxSig;
  /* Number of Rx signal grp */
  uint16 NoOfRxSigGrp;
  /* Number of Rx signal In grp */
  uint16 NoOfRxSigInGrp;
  /* Number of IPDU grp */
  uint8  NoOfIpduGrp;
  /* Number of Tx IPDU */
  uint16 NoOfTxIpdus;
  /* Number of Rx IPDU */
  uint16 NoOfRxIpdus;
  /* Number of Tx IPDU do not belong to any IPDU Grp */
  uint16 NoOfTxIpduUngrp;
  /* Number of Rx IPDU do not belong to any IPDU Grp */
  uint16 NoOfRxIpduUngrp;
  /* Number of number of Rx sig and sig in grp in configuration */
  uint16 NoOfTxSigIngrp;
  /* Number of Tx IPDU Deadline Monitoring count */
  uint16 NoOfTxIpduDMCnt;
  /* Number of Rx IPDU Deadline Monitoring count */
  uint16 NoOfRxIpduDMCnt;
  /* Pointer to Ipdu Grp configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pIpduGrpConfig;
  /* Pointer to Tx Ipdu Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxIpduConfig;
  /* Pointer to Rx Ipdu Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxIpduConfig;
  /* Pointer to Tx Signal Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxSignalConfig;
  /* Pointer to Rx Signal Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxSignalConfig;
  /* Pointer to Tx confirmation notification Configuration*/
  P2CONST(void, AUTOMATIC, COM_CONST) pTxIpduConfirmConfig;
  /* Pointer to Tx Ipdu Deadline Mornitoring Configuration*/
  P2CONST(void, AUTOMATIC, COM_CONST) pTxIpduDmConfig;
  /* Pointer to Tx Pack Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxPackConfig;
  /* Pointer to Rx Unpack Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxUnPackConfig;
  /* Pointer to Tx Ipdu Mode Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxModeConfig;
  /* Pointer to Rx Deadline Mornitoring Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxDmConfig;
   /* Pointer to Notification Callback Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigNotifCbk;
  /* Pointer to Error Callback Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigErrorCbk;
  /* Pointer to Tx Tp IPDU Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxTPIpduConfig;
  /* Pointer to Tx Tp IPDU Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxTPIpduConfig;
  /* Pointer to pTxIpduGroup Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxIpduGroup;
  /* Pointer to pRxIpduGroup Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxIpduGroup;
  /* Pointer to pRxIpduBelongGroup Configuration */
  P2CONST(void,AUTOMATIC, COM_CONST) pRxIpduBelongGroup;
  /* Pointer to pTxIpduBelongGroup Configuration */
  P2CONST(void,AUTOMATIC, COM_CONST) pTxIpduBelongGroup;
  /* Pointer to pRxIpduDmBelongGroup Configuration */
  P2CONST(void,AUTOMATIC, COM_CONST) pRxIpduDmBelongGroup;
  /* Pointer to pInvNotifCbk Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pInvNotifCbk;
  /* Pointer to pTxPeriodicTimer Configuration */
  P2VAR(void,AUTOMATIC, COM_VAR)  pTxPeriodicTimer;
  /* Pointer to Com_TxUbitConfig Configuration */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxUbitConfig;    
  /* Com_GaaTxPduInfoPtr */
  P2VAR(void, AUTOMATIC, COM_VAR) pTxPduInfoPtr;
  /* Com_GaaRxPduInfoPtr */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxPduInfoPtr;
  /* Com_GaaRxCntNotify */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxCntNotify;
  /* Com_GaaFilterStatus */
  P2VAR(void, AUTOMATIC, COM_VAR) pFilterSts;
  /* Com_GaaFilterOneEveryN */
  P2CONST(void, AUTOMATIC, COM_CONST) pFilterOneEveryN;
  /* Com_GaaTxMDTimeout */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxMDTimeout;
  /* Com_GaaTxSigInGrp */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxSigInGrp;  
  /* Com_GaaRxSigInGrp */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxSigInGrp;
  /* Com_GaaRxInvOrFltSigGroup */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxInvOrFltSigGroup;
  /* Com_GaaTxSigGrpModeSel */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxSigGrpModeSel;
  /* Com_GaaRxGWIpdu */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxGWIpdu;
  /* Com_GaaTxGWSignal */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxGWSignal;
  /* Com_GaaRxGWSignal */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxGWSignal;
  /* Com_GaaRxGWSigInGrp */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxGWSigInGrp;
  /* Com_GaaRxSigInGrpInvOrFlt */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxSigInGrpInvOrFlt;
  /* Com_GaaTxSigGroup */
  P2CONST(void, AUTOMATIC, COM_CONST) pTxSigGroup;
  /* Com_GaaRxSigGroup */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxSigGroup;
  /* Com_GaaSigWrFuncPtr */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigWrFuncPtr;
  /* Com_GaaSigRdFuncPtr */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigRdFuncPtr;
  /*Com_GaaSigReplace*/
  P2CONST(void, AUTOMATIC, COM_CONST) pSigReplace ;
  /* Com_GaaRxInvalid */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxInvalid;
  /* Com_GaaInvalidFuncPtr */
  P2CONST(void, AUTOMATIC, COM_CONST) pInvalidFuncPtr;
  /* Com_GaaTxIpduCounter */
  P2CONST(void, AUTOMATIC, COM_CONST)  pTxIpduCounter;
  /* Com_GaaRxIpduCounter */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxIpduCounter;
  /* Com_GaaSigGroupMaskInfo */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigGroupMaskInfo;
  /* Com_GaaSigGroupChangedStatus */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigGroupChangedStatus;
  /* Com_GaaSigGrpReplace */
  P2CONST(void, AUTOMATIC, COM_CONST) pSigGrpReplace;
  /* Com_GaaWrFuncPtr */
  P2CONST(void, AUTOMATIC, COM_CONST) pWrFuncPtr;
  /* Com_GaaRxIpduCallOut */
  P2CONST(void, AUTOMATIC, COM_CONST) pRxIpduCallOut;
  /*Com_GaaTxIpduCallOut*/
  P2CONST(void, AUTOMATIC, COM_CONST) pTxIpduCallOut;
  /* Com_GaaRxGWIpduStatus */
  P2VAR(void, AUTOMATIC, COM_VAR) pRxGWIpduStatus;
  /* Com_GaaTxReptCount */
  P2VAR(void, AUTOMATIC, COM_VAR) pTxReptCount;
  /* Com_GaaTxReptSubCount */
  P2VAR(void, AUTOMATIC, COM_VAR) pTxReptSubCount;
  /* Com_GaaTxReptTimer */
  P2VAR(uint16, AUTOMATIC, COM_VAR) pTxReptTimer;
  /* Com_GaaTxMDTimer */
  P2VAR(uint16, AUTOMATIC, COM_VAR) pTxMDTimer;
  /* Com_GaaRxDMTimer */
  P2VAR(uint32, AUTOMATIC, COM_VAR) pRxDMTimer;
  #else /* #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)*/
  uint8 ucDummy;
  #endif
}Com_ConfigType;

/* @Trace: Com_SUD_DATATYPE_029 */
/* Status value returned by the API service Com_GetStatus() */
typedef enum
{
  COM_UNINIT = 0x00,
  COM_INIT
}Com_StatusType;

/* @Trace: Com_SUD_DATATYPE_019 */
typedef uint8 Com_IpduGroupIdType;
/* I-PDU group vector */
/* ring buffer support for RxIpdu */

/* @Trace: Com_SUD_DATATYPE_083 */
/* ring buffer support for notifyCbk */
typedef struct
{
  VAR(uint16, COM_VAR) usWriteIndex;
  
  VAR(uint16, COM_VAR) usReadIndex;
  
  VAR(uint16, COM_VAR) usCount;
  
  CONST(uint16, COM_CONST) usSize;
  
  CONSTP2VAR(Com_NotifCountType, AUTOMATIC, COM_CONST) pList;
}Com_NotifyCbkListType;

/* @Trace: Com_SUD_DATATYPE_084 */
typedef struct
{
  CONSTP2VAR(Com_NotifyCbkListType, AUTOMATIC, COM_CONST) ptr;
}Com_NotifyCbkPtrType;

#endif /* COM_TYPES_H  */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
