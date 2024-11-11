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
**  SRC-MODULE: Com.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of initialization and its functionality.            **
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
** 1.1.6.0   07-Dec-2022   PhucNHM     CP44-1267                              **
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #29406 #28007              **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     09-Apr-2022   PhuPV10     R44-Redmine #25517                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"         /* Com header file */
#include "Com_Types.h"         /* Com header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "Com_Error.h"    /* Com Error header file */
#include "Com_Main.h"
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"         /* Det header file */
#endif
#if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#include "Com_Pack.h"
#include "Com_PCTypes.h"
#include "string.h"       /* memcpy() */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_Init                                            **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes internal and external      **
**                        interfaces and variables of the AUTOSAR COM module  **
**                        layer for the further processing. After calling this**
**                        the inter-ECU communication is still disabled.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : config                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                                                 Com_GaaTxIpduCountVal      **
**                                                 Com_GaaRxIpduCountVal      **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_Com_02037, SRS_Com_02113, SRS_Com_02030, SRS_Com_02058,
           SRS_Com_00218, SRS_Com_02042, SRS_Com_02103, SRS_Com_02105,
           SRS_Com_02107, SRS_Com_02102, SRS_Com_02104, SRS_Com_02106,
           SRS_Com_02040, SRS_Com_02067, SRS_Com_02096, SRS_Com_02098,
           SRS_Com_02100, SRS_Com_02101*/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Init
              (P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST) ConfigPtr)
{
  /* @Trace: Com_SUD_API_01258 */
  #if(COM_TX_IPDU == STD_ON)
  #if((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) || \
    (COM_TX_IPDU_UNGRP_COUNT > COM_MACRO_ZERO) || \
    (COM_RX_IPDU_UNGRP_COUNT > COM_MACRO_ZERO))
  PduIdType LddPduIndex;
  PduIdType LddNoOfIpdus;
  #endif
  #endif
  #if(COM_TX_IPDU == STD_ON)
  uint16 LusNoOfTxIpdu;
  uint16 LusNoOfTxIpduSub;
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  uint16 LusNoOfTxIpduUnGrp;
  #endif
  #endif
  #if((COM_RX_IPDU == STD_ON) &&  \
    (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON))
  uint16 LusNoOfRxIpdu;
  uint16 LusNoOfRxIpduUnGrp;
  #endif
  #if ((COM_DEV_ERROR_DETECT == STD_ON) && \
    (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON))
  /* If variant is post build, check Det error null pointer */
  boolean inputValid;
  inputValid = (boolean)COM_TRUE;
  #endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

  /* @Trace: SWS_Com_00010, SWS_Com_00011, SWS_Com_00012,  */
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST) Com_ConfigSet;
  #endif /* (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) */

  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01379 */

  /* Config pointer is not used in Pre-Compile */
  COM_UNUSED_PTR(ConfigPtr);
  
  #if(COM_TX_IPDU == STD_ON)
  /* Get value of Tx Ipdu */
  LusNoOfTxIpdu = (uint16)COM_TX_IPDU_COUNT;
  #endif

  #else /* (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */
  /*------------------------------------------------------*/
  #if (COM_DEV_ERROR_DETECT == STD_ON)
  /* Check det and report error in case ptr config is NULL*/
  if(ConfigPtr == NULL_PTR)
  {
    /* @Trace: Com_SUD_API_01259 */
    (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                    
      COMSERVICEID_INIT, COM_E_PARAM_POINTER);                            
    inputValid = (boolean)COM_FALSE;
  }
  if(inputValid == COM_TRUE)
  #endif
  {
    /* @Trace: Com_SUD_API_01260 */
    /* Load ConfigPtr to Local pointer variable  */
    Com_ConfigSet = ConfigPtr;

    #if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
      (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
    Com_GaaSigReplace = 
      (P2CONST(Com_SigReplace, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pSigReplace;
    #endif

    #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
    /* Pointer to Write Function configuration */
    Com_GaaSigWrFuncPtr = 
      (P2CONST(Com_SigWrFuncPtr, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pSigWrFuncPtr;
    #endif

    #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO)
    /* Pointer to Read Function configuration */
    Com_GaaSigRdFuncPtr = 
      (P2CONST(Com_SigRdFuncPtr, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pSigRdFuncPtr;
    #endif

    #if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Tx Ipdu info configuration */
    Com_GaaTxPduInfoPtr = 
      (P2VAR(PduInfoType, AUTOMATIC,COM_VAR))
      Com_ConfigSet->pTxPduInfoPtr;
    #endif

    #if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Rx Ipdu info configuration */
    Com_GaaRxPduInfoPtr = 
      (P2VAR(Com_RxPduInfoType, AUTOMATIC,COM_VAR))
      Com_ConfigSet->pRxPduInfoPtr;
    #endif

    #if(COM_IPDUGROUP_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Ipdu grp configuration */
    Com_GaaIpduGroup =    
      (P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pIpduGrpConfig;
    #endif

    #if(COM_TX_IPDU == STD_ON)  
    #if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Tx Ipdu configuration */
    Com_GaaTxIpdu = 
      (P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxIpduConfig;
    #endif /* #if(COM_TX_IPDU == STD_ON) */

    #if(COM_TX_SIGNAL_COUNT_MAX > COM_MACRO_ZERO)    
    /* Pointer to Tx Signal congiguration */
    Com_GaaTxSignal = 
        (P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST))          
        Com_ConfigSet->pTxSignalConfig;
    #endif /* #if(COM_TX_SIGNAL_COUNT_MAX > COM_MACRO_ZERO)*/

    #if(COM_TX_IPDU_CONFIRM_MAX > COM_MACRO_ZERO)
    /* Pointer to Tx Ipdu confirmation */
    Com_GaaTxIpduConfirm = 
        (P2CONST(Com_TxIpduConfirm, AUTOMATIC, COM_CONST))   
        Com_ConfigSet->pTxIpduConfirmConfig;
    #endif
    /* Pointer to Tx Ipdu Deadline Mornitoring configuration*/
    #if(COM_TX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
    Com_GaaTxIpduDm =
        (P2CONST(Com_TxIpduDm, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxIpduDmConfig;
    #endif
    #endif /* (COM_TX_IPDU == STD_ON) */

    /* Get number of Tx IPDUs deadline monitoring */
    Com_GlNoOfTxIpduDMCnt = Com_ConfigSet->NoOfTxIpduDMCnt;

    /* Get number of Rx IPDUs deadline monitoring */
    Com_GlNoOfRxIpduDMCnt = Com_ConfigSet->NoOfRxIpduDMCnt;

    /* Pointer to Tx Pack configuration */
    #if(COM_PACK_FUNC_COUNT_MAX > COM_MACRO_ZERO)
    Com_GaaTxPack = 
        (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxPackConfig;
    #endif

    /* Pointer to Rx Unpack configuration */ 
    #if(COM_UNPACK_FUNC_COUNT_MAX > COM_MACRO_ZERO)    
    Com_GaaRxUnpack = 
        (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pRxUnPackConfig;
    #endif

    #if(COM_RX_IPDU == STD_ON)
    /* Pointer to Rx Ipdu configuration */
    Com_GaaRxIpdu = 
        (P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pRxIpduConfig;

    /* Pointer to Rx Signal configuration */
    Com_GaaRxSignal = 
        (P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pRxSignalConfig;

    #if(COM_RX_IPDU_DM == STD_ON)
    /* Pointer to Rx Deadline Mornitoring configuration */
    Com_GaaRxDm = 
        (P2CONST(Com_RxDm, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pRxDmConfig;
    #endif /*#if(COM_RX_IPDU_DM == STD_ON)*/
    #endif /*#if(COM_RX_IPDU == STD_ON)*/

    #if(COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO)
    Com_GaaSigErrorCbk = 
        (P2CONST(Com_SigErrorCbk, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pSigErrorCbk;
    #endif

    #if(COM_RX_INVALIDNOTIFY == STD_ON)
    Com_GaaInvNotifCbk = 
        (P2CONST(pInvSigNotifCbkPtr, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pInvNotifCbk;
    #endif

    #if(COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
    Com_GaaSigNotifCbk = 
        (P2CONST(Com_SigNotifCbk, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pSigNotifCbk;
    #endif

    #if(COM_RX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to  RAM area of Rx Dm Timer configuration */
    Com_GaaRxDMTimer = 
        (P2VAR(uint32, AUTOMATIC, COM_VAR))
        Com_ConfigSet->pRxDMTimer;
    #endif

    /* Pointer to Tx Tp IPDU configuration */
    #if(COM_TX_TP_SUPPORT == STD_ON)
    Com_GaaTxTPIpdu = 
        (P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxTPIpduConfig;
    #endif

    #if(COM_RX_TP_SUPPORT == STD_ON)
    Com_GaaRxTPIpdu = 
        (P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pRxTPIpduConfig;
    #endif

    /* Pointer to Tx Update Bit configuration */
    #if((COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON))
    Com_GaaTxUpdateBit = 
        (P2CONST(Com_TxUpdateBit, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxUbitConfig;
    #endif

    /* Get number of IPDU grp in this configuration */
    Com_GlNoOfIpduGrp = Com_ConfigSet->NoOfIpduGrp;
    
    #if(COM_TX_IPDU == STD_ON)
    /* Get number of Tx IPDU in this configuration */
    Com_GlNoOfTxIpdu = Com_ConfigSet->NoOfTxIpdus;
    Com_GlNoOfTxSignal = Com_ConfigSet->NoOfTxSig;
    Com_GlNoOfTxSigGrp = Com_ConfigSet->NoOfTxSigGrp;
    Com_GlNoOfTxSigInGrp = Com_ConfigSet->NoOfTxSigInGrp;
    
    /* Pointer to Tx periodic timer  configuration */
    #if(COM_TX_PERIOD_TIMER_COUNT > COM_MACRO_ZERO)
    Com_GaaTxPeriodicTimer = 
        (P2VAR(uint16, AUTOMATIC, COM_VAR))
            Com_ConfigSet->pTxPeriodicTimer;
    #endif

    /* Pointer to filter status configuration */
    #if(COM_FILTER_STATUS_COUNT > COM_MACRO_ZERO)
    Com_GaaFilterStatus = 
        (P2VAR(uint8, AUTOMATIC, COM_VAR))
          Com_ConfigSet->pFilterSts;
    #endif

    #if( COM_TX_MODE_COUNT_MAX > 0)
      /* Pointer to Tx Mode configuration */
    Com_GaaTxMode = 
        (P2CONST(Com_TxMode, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxModeConfig;
    #endif
    /* Get number of Tx IPDU Ungrp in this configuration */
    Com_GlNoOfTxIpduUngrp = Com_ConfigSet->NoOfTxIpduUngrp;

    LusNoOfTxIpdu = Com_GlNoOfTxIpdu;
    LusNoOfTxIpduUnGrp = Com_GlNoOfTxIpduUngrp;
    #endif

    #if(COM_RX_IPDU == STD_ON)
    /* Get number of Rx IPDU in this configuration */
    Com_GlNoOfRxIpdu = Com_ConfigSet->NoOfRxIpdus;
    Com_GlNoOfRxSignal = Com_ConfigSet->NoOfRxSig;
    Com_GlNoOfRxSigGrp = Com_ConfigSet->NoOfRxSigGrp;
    Com_GlNoOfRxSigInGrp = Com_ConfigSet->NoOfRxSigInGrp;

    /* Get number of Rx IPDU Ungrp in this configuration */
    Com_GlNoOfRxIpduUngrp = Com_ConfigSet->NoOfRxIpduUngrp;

    LusNoOfRxIpdu = Com_GlNoOfRxIpdu;
    LusNoOfRxIpduUnGrp = Com_GlNoOfRxIpduUngrp;
    #endif
    
    #if(COM_RX_IPDU_GROUP_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Rx Ipdu Grp configuration */
    Com_GaaRxIpduGroup =
        (P2CONST(PduIdType, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pRxIpduGroup;
    #endif

    #if(COM_TX_IPDU_GROUP_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Tx Ipdu Grp configuration */
    Com_GaaTxIpduGroup = 
      (P2CONST(PduIdType, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pTxIpduGroup;
    #endif

    #if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
      /* Pointer to Rx I-PDU Belong Group Configuration */
    Com_GaaRxIpduBelongGroup = 
            (P2CONST(PduIdType, AUTOMATIC, COM_CONST))
              Com_ConfigSet->pRxIpduBelongGroup;
    #endif

    #if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
     /* Pointer to Tx I-PDU Belong Group Configuration */
    Com_GaaTxIpduBelongGroup = 
            (P2CONST(PduIdType, AUTOMATIC, COM_CONST))
              Com_ConfigSet->pTxIpduBelongGroup;
    #endif

    #if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
     /* Pointer to Rx I-PDU DM Belong Group Configuration */
    Com_GaaRxIpduDmBelongGroup = 
            (P2CONST(PduIdType, AUTOMATIC, COM_CONST))
              Com_ConfigSet->pRxIpduDmBelongGroup;
    #endif

    #if(COM_RX_INVALIDNOTIFY == STD_ON)
    /* Pointer to Invalid notification Cbk configuration */
    Com_GaaInvNotifCbk = 
      (P2CONST(pInvSigNotifCbkPtr, AUTOMATIC, COM_CONST))
        Com_ConfigSet->pInvNotifCbk;
    #endif
        
    #if(COM_TX_IPDU_MDT_COUNT > COM_MACRO_ZERO)
    /* Pointer to MDT time out configuration */
    Com_GaaTxMDTimeout = 
      (P2CONST(uint16,AUTOMATIC, COM_CONST))
      Com_ConfigSet->pTxMDTimeout;
    #endif
    
    #if(COM_RX_SIGINGROUP_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Rx signal In Grp index configuration */
    Com_GaaRxSigInGrp = 
      (P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxSigInGrp;
    #endif
    
    #if((COM_RX_SIGGROUP_INVALID == STD_ON) || \
      (COM_RX_SIGGROUP_FILTER == STD_ON))
    /* Pointer to Rx signal grp Invalid or filter index configuration */
    Com_GaaRxInvOrFltSigGroup = 
      (P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxInvOrFltSigGroup;
    /* Pointer to Rx signal in grp Invalid or filter index configuration */
    Com_GaaRxSigInGrpInvOrFlt =
      (P2CONST(Com_RxSigInGrpInvOrFlt, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxSigInGrpInvOrFlt;
    #endif

    Com_GaaInvalidFuncPtr =
      (P2CONST(Com_InvalidFuncPtr, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pInvalidFuncPtr;

    #if((COM_RX_SIGGROUP_REPLACE == STD_ON) || \
      (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON))
    #if(COM_SIGGRP_REPLACE_COUNT > COM_MACRO_ZERO)     
    Com_GaaSigGrpReplace =
      (P2CONST(Com_SigGrpReplace, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pSigGrpReplace;
    #endif
    #endif 

    #if(COM_RX_SIGNAL_INVALID == STD_ON)
    Com_GaaRxInvalid =
      (P2CONST(Com_RxInvalid, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxInvalid;
    #endif

    #if(COM_WR_FUNC_COUNT > COM_MACRO_ZERO)
    Com_GaaWrFuncPtr =
      (P2CONST(Com_WrFuncPtr, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pWrFuncPtr;
    #endif

    #if(COM_NO_OF_FILTER_ONEVERYN > COM_MACRO_ZERO)
    Com_GaaFilterOneEveryN =
      (P2CONST(Com_FilterOneEveryN, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pFilterOneEveryN;
    #endif

    #if(COM_TX_IPDU_CALLOUT_COUNT > COM_MACRO_ZERO)
    Com_GaaTxIpduCallOut =
      (P2CONST(Com_TxIpduCallOut, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pTxIpduCallOut;
    #endif

    #if(COM_TX_SIGGRP_MODE_SEL_COUNT > COM_MACRO_ZERO)
      Com_GaaTxSigGrpModeSel = 
      (P2CONST(Com_TxSigGrpModeSel, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pTxSigGrpModeSel;
    #endif
    
    #if(COM_TX_SIGGROUP == STD_ON)
    Com_GaaTxSigInGrp = 
      (P2CONST(Com_TxSigInGrp,AUTOMATIC,  COM_CONST))
      Com_ConfigSet->pTxSigInGrp;
    #endif
    
    #if(COM_RX_GW_COUNT > COM_MACRO_ZERO)
    Com_GaaRxGWIpdu = 
      (P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxGWIpdu;
    #endif
    
    #if(COM_RX_SIG_GATEWAY == STD_ON)
    Com_GaaTxGWSignal = 
      (P2CONST(Com_TxGWSignal, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pTxGWSignal;
    #endif
    
    #if((COM_RX_SIGNAL_GW == STD_ON) || (COM_RX_SIGINGROUP_GW == STD_ON))
    Com_GaaRxGWSignal = 
      (P2CONST(Com_RxGWSignal, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxGWSignal;
    #endif
    
    #if(COM_RX_SIG_INGRP_GW_COUNT > COM_MACRO_ZERO)
    Com_GaaRxGWSigInGrp = 
      (P2CONST(Com_RxGWSigInGrp,AUTOMATIC, COM_CONST)) 
      Com_ConfigSet->pRxSigInGrpInvOrFlt;
    #endif
    
    #if(COM_RX_SIGGROUP_COUNT_MAX > COM_MACRO_ZERO)
    Com_GaaRxSigGroup = 
      (P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pRxSigGroup;
    #endif
    
    #if(COM_TX_SIGGROUP_COUNT_MAX > COM_MACRO_ZERO)
    Com_GaaTxSigGroup =
      (P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST))
      Com_ConfigSet->pTxSigGroup;
    #endif

    #if(COM_RX_IPDU_CALLOUT_COUNT > COM_MACRO_ZERO)
    Com_GaaRxIpduCallOut = (P2CONST(Com_RxIpduCallOut, AUTOMATIC, COM_CONST)) 
    Com_ConfigSet->pRxIpduCallOut;
    #endif

    #if(((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) && \
      (COM_RX_SIG_GATEWAY == STD_ON)) || (COM_RX_SIGNAL_GW_DES == STD_ON))
    Com_GaaRxGWIpduStatus = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    Com_ConfigSet->pRxGWIpduStatus;
    #endif

    #if(COM_TX_REPT_COUNT > COM_MACRO_ZERO)
    /* Global array for allocating RAM area of Tx Rept Timer */
    Com_GaaTxReptCount = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    Com_ConfigSet->pTxReptCount ;
    /* Global array for allocating RAM area of Tx Rept Sub Timer */
    Com_GaaTxReptSubCount = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    Com_ConfigSet->pTxReptSubCount;
    #endif

    #if(COM_TX_REPT_TIMER_COUNT > COM_MACRO_ZERO)
    Com_GaaTxReptTimer = (P2VAR(uint16, AUTOMATIC, COM_VAR))
    Com_ConfigSet->pTxReptTimer;
    #endif

    #if(COM_TX_IPDU_MDT_COUNT > COM_MACRO_ZERO)
    /* Global array for allocating RAM area of Tx Minimum Delay Timer */
    Com_GaaTxMDTimer = (P2VAR(uint16, AUTOMATIC, COM_VAR))
    Com_ConfigSet->pTxMDTimer;
    #endif
    
    #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
    Com_GaaTxIpduCounter = (P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST))
    Com_ConfigSet->pTxIpduCounter;
    #endif

    #if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
    Com_GaaRxIpduCounter = (P2CONST(Com_RxIpduCounter, AUTOMATIC, COM_CONST))
    Com_ConfigSet->pRxIpduCounter;
    #endif

    /* Reset buffers when re-init by PostBuild */
    /* 8-bit buffer */
    #if(COM_UINT8_BUFFER_SIZE > COM_MACRO_ZERO)
    memcpy(
      (P2VAR(void, AUTOMATIC, COM_VAR))(&Com_GaaRamInit8Bit[COM_ZERO]),
      (P2CONST(void, AUTOMATIC, COM_CONST))(&Com_GaaRomReInit8Bit[COM_ZERO]),
      (uint8)COM_UINT8_BUFFER_SIZE);
    #endif
    /* 16-bit buffer */
    #if(COM_UINT16_BUFFER_SIZE > COM_MACRO_ZERO)
    memcpy(
      (P2VAR(void, AUTOMATIC, COM_VAR))(&Com_GaaRamInit16Bit[COM_ZERO]),
      (P2CONST(void, AUTOMATIC, COM_CONST))(&Com_GaaRomReInit16Bit[COM_ZERO]),
      (uint8)COM_UINT16_BUFFER_SIZE);
    #endif
    /* 32-bit buffer */
    #if(COM_UINT32_BUFFER_SIZE > COM_MACRO_ZERO)
    memcpy(
      (P2VAR(void, AUTOMATIC, COM_VAR))(&Com_GaaRamInit32Bit[COM_ZERO]),
      (P2CONST(void, AUTOMATIC, COM_CONST))(&Com_GaaRomReInit32Bit[COM_ZERO]),
      (uint8)COM_UINT32_BUFFER_SIZE);
    #endif
    /* 64-bit buffer */
    #if(COM_UINT64_BUFFER_SIZE > COM_MACRO_ZERO)
    memcpy(
      (P2VAR(void, AUTOMATIC, COM_VAR))(&Com_GaaRamInit64Bit[COM_ZERO]),
      (P2CONST(void, AUTOMATIC, COM_CONST))(&Com_GaaRomReInit64Bit[COM_ZERO]),
      (uint8)COM_UINT64_BUFFER_SIZE);
    #endif
  }
  #endif /* #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)*/

  #if ((COM_DEV_ERROR_DETECT == STD_ON) && \
    (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON))
  if(inputValid == COM_TRUE)
  #endif
  {
    /* @Trace: Com_SUD_API_01261 */
    #if(COM_TX_IPDU == STD_ON)
    LusNoOfTxIpduSub = LusNoOfTxIpdu;
    while(LusNoOfTxIpduSub > COM_MACRO_ZERO)
    {
      /* @Trace: Com_SUD_API_01262 */
      Com_GaaTxIpduStatusBit[LusNoOfTxIpduSub-1] |= COM_TX_TMS_STATUS_MASK;
      LusNoOfTxIpduSub --;
    }

    #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
    if (LusNoOfTxIpduUnGrp != COM_ZERO)
    {
      LddPduIndex = (PduIdType)(LusNoOfTxIpdu - LusNoOfTxIpduUnGrp);
      LddNoOfIpdus = (PduIdType)LusNoOfTxIpduUnGrp;
      while(LddNoOfIpdus != (PduIdType)COM_ZERO)
      {
        --LddNoOfIpdus;
      /* @Trace: Com_SUD_API_01263 */
      /* Invoke Com_StartTxIPDUsto enable Tx Ipdu not belong to IPDU grp */
        Com_StartTxIPDUs(LddPduIndex, COM_TRUE, COM_FALSE);

        ++LddPduIndex;
      }
    }
    #else
    #if (COM_TX_IPDU_UNGRP_COUNT > COM_MACRO_ZERO)
    LddPduIndex = (PduIdType)(COM_TX_IPDU_COUNT - COM_TX_IPDU_UNGRP_COUNT);
    LddNoOfIpdus = (PduIdType)COM_TX_IPDU_UNGRP_COUNT;
    while(LddNoOfIpdus != (PduIdType)COM_ZERO)
    {
      --LddNoOfIpdus;
    /* @Trace: Com_SUD_API_01380 */
    /* Invoke Com_StartTxIPDUsto enable Tx Ipdu not belong to IPDU grp */
      Com_StartTxIPDUs(LddPduIndex, COM_TRUE, COM_FALSE);

      ++LddPduIndex;
    }
    #endif
    #endif
    #endif /*End of (COM_TX_IPDU == STD_ON)*/

    #if(COM_RX_IPDU == STD_ON)
    #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
    if (LusNoOfRxIpduUnGrp != COM_ZERO )
    {
      LddPduIndex = (PduIdType)(LusNoOfRxIpdu - LusNoOfRxIpduUnGrp);
      LddNoOfIpdus = (PduIdType)LusNoOfRxIpduUnGrp;
      while(LddNoOfIpdus != (PduIdType)COM_ZERO)
      {
        --LddNoOfIpdus;
      /* @Trace: Com_SUD_API_01264 */
      /* Invoke Com_StartRxIPDUsto enable Tx Ipdu not belong to IPDU grp */
        Com_StartRxIPDUs(LddPduIndex, COM_TRUE, COM_FALSE);

        ++LddPduIndex;
      }
    }
    #else
    #if (COM_RX_IPDU_UNGRP_COUNT > COM_MACRO_ZERO)
    LddPduIndex = (PduIdType)(COM_RX_IPDU_COUNT - COM_RX_IPDU_UNGRP_COUNT);
    LddNoOfIpdus = (PduIdType)COM_RX_IPDU_UNGRP_COUNT;
    while(LddNoOfIpdus != (PduIdType)COM_ZERO)
    {
      --LddNoOfIpdus;
    /* @Trace: Com_SUD_API_01381 */
    /* Invoke Com_StartRxIPDUsto enable Tx Ipdu not belong to IPDU grp */
      Com_StartRxIPDUs(LddPduIndex, COM_TRUE, COM_FALSE);

      ++LddPduIndex;
    }
    #endif
    #endif
    #endif /*End of (COM_TX_IPDU == STD_ON)*/
    
    #if (STD_ON == COM_MULTI_CORE_SUPPORT)
    /* @Trace: Com_SUD_API_01265 */
    Com_NotifyList_Init();
    #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
    /* Set the Com module status variable to initialized */
    Com_GddComStatus = COM_INIT;  
  } /* @End if(inputValid == COM_TRUE) */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* @Traceability END -- SRS: SRS_Com_02037, SRS_BSW_00101, SRS_Com_02030, SRS_Com_02058,
 SRS_Com_00218, SRS_Com_02042 */
/*******************************************************************************
** Function Name        : Com_DeInit                                          **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service stops the inter-ECU communication. All **
**                        started I-PDU groups are stopped and have to be     **
**                        started again, if needed, after Com_Init is called. **
**                        By a call to Com_DeInit the AUTOSAR COM module is   **
**                        put into an not initialized state.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaIpduGrpEnStatus     **
**                                                 Com_GaaIpduGrpDmStatus     **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaRxDmStatus          **
**                                                 Com_GddComStatus           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02037, SRS_BSW_00101, SRS_Com_02030, SRS_Com_02058,
           SRS_Com_00218, SRS_Com_02042  */
FUNC(void, COM_CODE) Com_DeInit(void)
{
  /* @Trace: Com_SUD_API_01266 */
  uint8 LucIpduGroupStsCount;
  PduIdType LddIpduCount;
  LucIpduGroupStsCount = COM_IPDU_GRP_VECTOR_SIZE;
  /* Loop for all Ipdu Group */
  do
  {
    /* @Trace: Com_SUD_API_01267 */
    LucIpduGroupStsCount--;
    Com_GaaIpduGrpEnStatus[LucIpduGroupStsCount] = COM_ZERO;
    Com_GaaIpduGrpDmStatus[LucIpduGroupStsCount] = COM_ZERO;

  }while(LucIpduGroupStsCount != COM_ZERO);

  #if(COM_TX_IPDU == STD_ON)
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01268 */
  LddIpduCount = (PduIdType) COM_TX_IPDU_COUNT;
  #else
  /* @Trace: Com_SUD_API_01382 */
  LddIpduCount = Com_GlNoOfTxIpdu;
  #endif
  do
  {
    /* @Trace: Com_SUD_API_01269 */
    --LddIpduCount;
    Com_GaaTxIpduStatusBit[LddIpduCount] = (uint16) COM_ZERO;
   
    Com_GaaTxIpduStatus[LddIpduCount] = (PduIdType) COM_ZERO;

  }while(LddIpduCount != (PduIdType)COM_ZERO);
  #endif

  #if(COM_RX_IPDU == STD_ON)
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01270 */
  LddIpduCount = (PduIdType) COM_RX_IPDU_COUNT;
  #else
  /* @Trace: Com_SUD_API_01383 */
  LddIpduCount = Com_GlNoOfTxIpdu;
  #endif
  do
  {
    /* @Trace: Com_SUD_API_01271 */
    --LddIpduCount;
    Com_GaaRxIpduStatus[LddIpduCount] = (PduIdType)COM_ZERO;
  }while(LddIpduCount != (PduIdType)COM_ZERO);
  #endif
  
  #if((COM_RX_IPDU_DM == STD_ON) || \
   (COM_RX_SIGNAL_UBDM == STD_ON) || \
   (COM_RX_SIGGROUP_UBDM == STD_ON))
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01272 */
  LddIpduCount = (PduIdType)COM_RX_IPDU_DM_COUNT;
  #else
  /* @Trace: Com_SUD_API_01384 */
  LddIpduCount = (PduIdType)COM_RX_IPDU_DM_COUNT_MAX;
  #endif
  do
  {
    /* @Trace: Com_SUD_API_01273 */
    --LddIpduCount;
    
    Com_GaaRxDmStatus[LddIpduCount] = (PduIdType)COM_ZERO;

  }while(LddIpduCount != (PduIdType)COM_ZERO);
  #endif

  /* @Trace: Com_SUD_API_01274 */
  /* Support PostBuild variant*/
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)

  #if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
    (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
  Com_GaaSigReplace = NULL_PTR;
  #endif

  #if(COM_RX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
  Com_GaaRxDMTimer = NULL_PTR;
  #endif

  #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
  /* DeInit Pointer to Write Function configuration */
  Com_GaaSigWrFuncPtr = NULL_PTR;
  #endif

  #if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO)
  /* DeInit Pointer to Read Function configuration */
  Com_GaaSigRdFuncPtr = NULL_PTR;
  #endif

  #if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Tx Ipdu info configuration */
  Com_GaaTxPduInfoPtr = NULL_PTR;
  #endif

  #if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Rx Ipdu info configuration */
  Com_GaaRxPduInfoPtr = NULL_PTR;
  #endif

  #if(COM_IPDUGROUP_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Ipdu grp configuration */
  Com_GaaIpduGroup =  NULL_PTR;
  #endif

  #if(COM_TX_IPDU == STD_ON)  
  #if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Tx Ipdu configuration */
  Com_GaaTxIpdu = NULL_PTR;
  #endif /* #if(COM_TX_IPDU == STD_ON) */

  #if(COM_TX_SIGNAL_COUNT_MAX > COM_MACRO_ZERO)    
  /* DeInit Pointer to Tx Signal congiguration */
  Com_GaaTxSignal = NULL_PTR;
  #endif /* #if(COM_TX_SIGNAL_COUNT_MAX > COM_MACRO_ZERO)*/

  #if(COM_TX_IPDU_CONFIRM_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Tx Ipdu confirmation */
  Com_GaaTxIpduConfirm = NULL_PTR;
  #endif
  /* DeInit Pointer to Tx Ipdu Deadline Mornitoring configuration*/
  #if(COM_TX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
  Com_GaaTxIpduDm = NULL_PTR;
  #endif
  #endif /* (COM_TX_IPDU == STD_ON) */

  /* DeInit Pointer to Tx Pack configuration */
  #if(COM_PACK_FUNC_COUNT_MAX > COM_MACRO_ZERO)
  Com_GaaTxPack = NULL_PTR;
  #endif

  /* DeInit Pointer to Rx Unpack configuration */ 
  #if(COM_UNPACK_FUNC_COUNT_MAX > COM_MACRO_ZERO)    
  Com_GaaRxUnpack = NULL_PTR;
  #endif

  #if(COM_RX_IPDU == STD_ON)
  /* DeInit Pointer to Rx Ipdu configuration */
  Com_GaaRxIpdu = NULL_PTR;

  /* DeInit Pointer to Rx Signal configuration */
  Com_GaaRxSignal = NULL_PTR;

  #if(COM_RX_IPDU_DM == STD_ON)
  /* DeInit Pointer to Rx Deadline Mornitoring configuration */
  Com_GaaRxDm = NULL_PTR;
  #endif /*#if(COM_RX_IPDU_DM == STD_ON)*/
  #endif /*#if(COM_RX_IPDU == STD_ON)*/

  /* DeInit Pointer to Tx Tp IPDU configuration */
  #if(COM_TX_TP_SUPPORT == STD_ON)
  Com_GaaTxTPIpdu = NULL_PTR;
  #endif

  #if(COM_RX_TP_SUPPORT == STD_ON)
  Com_GaaRxTPIpdu = NULL_PTR;
  #endif

  /* DeInit Pointer to Tx Update Bit configuration */
   #if((COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON))
  Com_GaaTxUpdateBit = NULL_PTR;
   #endif

  /* Get number of IPDU grp in this configuration */
  Com_GlNoOfIpduGrp = COM_ZERO;
  
  #if(COM_TX_IPDU == STD_ON)
  /* Get number of Tx IPDU in this configuration */
  Com_GlNoOfTxIpdu = COM_ZERO;
  Com_GlNoOfTxSignal = COM_ZERO;
  Com_GlNoOfTxSigGrp = COM_ZERO;
  Com_GlNoOfTxSigInGrp = COM_ZERO;

  /* DeInit Pointer to Tx periodic timer  configuration */
  #if(COM_TX_PERIOD_TIMER_COUNT > COM_MACRO_ZERO)
  Com_GaaTxPeriodicTimer = NULL_PTR;
  #endif

  /* DeInit Pointer to filter status configuration */
  #if(COM_FILTER_STATUS_COUNT > COM_MACRO_ZERO) 
  Com_GaaFilterStatus = NULL_PTR;
  #endif

  #if( COM_TX_MODE_COUNT_MAX > 0)
    /* DeInit Pointer to Tx Mode configuration */
  Com_GaaTxMode = NULL_PTR;
  #endif
  /* Get number of Tx IPDU Ungrp in this configuration */
  Com_GlNoOfTxIpduUngrp = COM_ZERO;

  #endif

  #if(COM_RX_IPDU == STD_ON)
  /* Get number of Rx IPDU in this configuration */
  Com_GlNoOfRxIpdu = COM_ZERO;
  Com_GlNoOfRxSignal = COM_ZERO;
  Com_GlNoOfRxSigGrp = COM_ZERO;
  Com_GlNoOfRxSigInGrp = COM_ZERO;

  /* Get number of Rx IPDU Ungrp in this configuration */
  Com_GlNoOfRxIpduUngrp = COM_ZERO;
  #endif
  
  #if(COM_RX_IPDU_GROUP_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Rx Ipdu Grp configuration */
  Com_GaaRxIpduGroup = NULL_PTR;
  #endif

  #if(COM_TX_IPDU_GROUP_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Tx Ipdu Grp configuration */
  Com_GaaTxIpduGroup = NULL_PTR;
  #endif

  #if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Rx I-PDU Belong Group Configuration */
  Com_GaaRxIpduBelongGroup = NULL_PTR;
  #endif

  #if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Tx I-PDU Belong Group Configuration */
  Com_GaaTxIpduBelongGroup = NULL_PTR;
  #endif

  #if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
    /* Pointer to Rx I-PDU DM Belong Group Configuration */
  Com_GaaRxIpduDmBelongGroup = NULL_PTR;
  #endif  

  #if(COM_RX_INVALIDNOTIFY == STD_ON)
  /* DeInit Pointer to Invalid notification Cbk configuration */
  Com_GaaInvNotifCbk = NULL_PTR;
  #endif
      
  #if(COM_TX_IPDU_MDT_COUNT > COM_MACRO_ZERO)
  /* DeInit Pointer to MDT time out configuration */
  Com_GaaTxMDTimeout = NULL_PTR;
  #endif
  
  #if(COM_RX_SIGINGROUP_COUNT_MAX > COM_MACRO_ZERO)
  /* DeInit Pointer to Rx signal In Grp index configuration */
  Com_GaaRxSigInGrp = NULL_PTR;
  #endif
  
  #if((COM_RX_SIGGROUP_INVALID == STD_ON) || \
    (COM_RX_SIGGROUP_FILTER == STD_ON))
  /* DeInit Pointer to Rx signal grp Invalid or filter index configuration */
  Com_GaaRxInvOrFltSigGroup = NULL_PTR;
  #endif
  
  #if(COM_TX_SIGGRP_MODE_SEL_COUNT > COM_MACRO_ZERO)
    Com_GaaTxSigGrpModeSel = NULL_PTR;
  #endif
  
  #if(COM_TX_SIGGROUP == STD_ON)
  Com_GaaTxSigInGrp = NULL_PTR;
  #endif
  
  #if(COM_RX_GW_COUNT > COM_MACRO_ZERO)
  Com_GaaRxGWIpdu = NULL_PTR;
  #endif
  
  #if(COM_RX_SIG_GATEWAY == STD_ON)
  Com_GaaTxGWSignal = NULL_PTR;
  #endif
  
  #if((COM_RX_SIGNAL_GW == STD_ON) || (COM_RX_SIGINGROUP_GW == STD_ON))
  Com_GaaRxGWSignal = NULL_PTR;
  #endif
  
  #if(COM_RX_SIGGROUP_COUNT_MAX > COM_MACRO_ZERO)
  Com_GaaRxSigGroup = NULL_PTR;
  #endif
  
  #if(COM_TX_SIGGROUP_COUNT_MAX > COM_MACRO_ZERO)
  Com_GaaTxSigGroup = NULL_PTR;
  #endif

  #if(COM_RX_IPDU_CALLOUT_COUNT > COM_MACRO_ZERO)
  Com_GaaRxIpduCallOut = NULL_PTR;
  #endif

  #if(((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) &&\
    (COM_RX_SIG_GATEWAY == STD_ON)) || (COM_RX_SIGNAL_GW_DES == STD_ON))
  Com_GaaRxGWIpduStatus = NULL_PTR;
  #endif

  #if(COM_TX_REPT_COUNT > COM_MACRO_ZERO)
  /* Global array for allocating RAM area of Tx Rept Timer */
  Com_GaaTxReptCount = NULL_PTR;
  /* Global array for allocating RAM area of Tx Rept Sub Timer */
  Com_GaaTxReptSubCount = NULL_PTR;
  #endif

  #if(COM_TX_REPT_TIMER_COUNT > COM_MACRO_ZERO)
  Com_GaaTxReptTimer = NULL_PTR;
  #endif

   #if(COM_TX_IPDU_MDT_COUNT > COM_MACRO_ZERO)
   /* Global array for allocating RAM area of Tx Minimum Delay Timer */
    Com_GaaTxMDTimer = NULL_PTR;
   #endif
   
  #endif /*(COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)*/
  /* Set the Com module status variable to uninitialized */
  Com_GddComStatus = COM_UNINIT;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This function returns the version information of the**
**                        Com Module.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/
#if(COM_VERSIONINFO_API == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_GetVersionInfo
              (P2VAR(Std_VersionInfoType, AUTOMATIC, COM_VAR) versioninfo)
{
  /* #7707 */
  /* @Trace: Com_SUD_API_01275 */
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  /* Initialize DET error flag to E_OK */
  LucReturnValue = (uint8)E_OK; 
  /* Check whether version information is equal to NULL */
  COM_DET_COMMON_PTR_CHECK_FLAG(versioninfo, COMSERVICEID_GETVERSIONINFO);
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_01276 */
    /* Copy the vendor ID */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    versioninfo->vendorID = COM_VENDOR_ID; 
    /* Copy the module ID */
    versioninfo->moduleID = COM_MODULE_ID;
    /* Copy software major version */
    versioninfo->sw_major_version = (uint8)COM_SW_MAJOR_VERSION;
    /* Copy software minor version */
    versioninfo->sw_minor_version = (uint8)COM_SW_MINOR_VERSION;
    /* Copy software patch version */
    versioninfo->sw_patch_version = (uint8)COM_SW_PATCH_VERSION;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : Com_GetStatus                                       **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This function returns the Returns the status of the **
**                        COM module.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Com_StatusType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void)
{
  /* @Trace: Com_SUD_API_01277 */
  return Com_GddComStatus;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
