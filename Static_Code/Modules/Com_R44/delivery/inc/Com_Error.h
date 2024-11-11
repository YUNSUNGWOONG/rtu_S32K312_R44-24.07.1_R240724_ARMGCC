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
**  SRC-MODULE: Com_Error.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Header file for the declaration of all the DET related errors **
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
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     07-Apr-2022   DuyNHP2     R44-Redmine #25516                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

#ifndef COM_ERROR_H
#define COM_ERROR_H
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations>  */
#if(COM_DEV_ERROR_DETECT ==  STD_OFF)

#else
/* Req 863*/
#define COM_DET_TP_SKIP_TRANSMISSION(COM_API_SERVICEID)                       \
  do{                                                                         \
    /* @Trace: Com_SUD_API_01351 */                                           \
    (void)Det_ReportRuntimeError(COM_MODULE_ID, COM_INSTANCE_ID,              \
                      COM_API_SERVICEID, COM_E_SKIPPED_TRANSMISSION);         \
  }while(0)

/* Check whether module is initialized */
#define COM_DET_INIT_STATUS_CHECK_FLAG(COM_API_SERVICEID)                     \
  do{                                                                         \
    if(Com_GddComStatus == COM_UNINIT)                                        \
    {                                                                         \
      /* @Trace: Com_SUD_API_01352 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                    COM_API_SERVICEID, COM_E_UNINIT);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)
  
/* Check whether Tx PDU ID is out of range */
#define COM_DET_TXPDUID_RANGE_CHECK_FLAG(ComTxPduId,                          \
                                             COM_API_SERVICEID)               \
  do{                                                                         \
    if((ComTxPduId) >= COM_TX_IPDU_COUNT)                                     \
    {                                                                         \
      /* @Trace: Com_SUD_API_01353 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

/* Check whether Rx PDU ID is out of range */
#define COM_DET_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId,                          \
                                             COM_API_SERVICEID)               \
  do{                                                                         \
    if((ComRxPduId) >= COM_RX_IPDU_COUNT)                                     \
    {                                                                         \
      /* @Trace: Com_SUD_API_01354 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

/* Check whether Rx PDU ID is out of range for PB case */
#define COM_DET_RXPDUID_RANGE_CHECK_FLAG_PB(ComRxPduId,                       \
                                             COM_API_SERVICEID)               \
  do{                                                                         \
    if((ComRxPduId) >= Com_GlNoOfRxIpdu)                                      \
    {                                                                         \
      /* @Trace: Com_SUD_API_01355 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)    

/* Check whether TP Rx PDU ID is out of range */
#define COM_DET_TP_RXPDUID_RANGE_CHECK_FLAG(ComRxPduId,                       \
                                             COM_API_SERVICEID)               \
  do{                                                                         \
    if(LucReturnValue != COM_SERVICE_NOT_AVAILABLE)                           \
    {                                                                         \
     if(((&Com_GaaRxIpdu[ComRxPduId])->ucRxTPRef) == COM_INVALID_NONE)        \
     {                                                                        \
        /* @Trace: Com_SUD_API_01356 */                                       \
       (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                 \
                                       COM_API_SERVICEID, COM_E_PARAM);       \
        LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                    \
     }                                                                        \
    }                                                                         \
  }while(0)

/* Check whether SduLength != COM_ZERO and SduDataPtr pointer is NULL */
#define  COM_DET_PDUINFOPTR_LENGTH_CHECK_FLAG(PduInfoPtr,COM_API_SERVICEID)   \
  do{                                                                         \
    if((PduInfoPtr) == NULL_PTR)                                              \
    {                                                                         \
      /* @Trace: Com_SUD_API_01385 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM_POINTER); \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
    else if((((PduInfoPtr)->SduLength) != COM_ZERO) &&                        \
                                (((PduInfoPtr)->SduDataPtr) == NULL_PTR))     \
    {                                                                         \
      /* @Trace: Com_SUD_API_01386 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM_POINTER); \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
  }while(0) 

/* Check whether PduInfoPtr pointer is NULL */
#define  COM_DET_PDUINFOPTR_PTR_CHECK_FLAG(PduInfoPtr,COM_API_SERVICEID)      \
  do{                                                                         \
    if((PduInfoPtr) == NULL_PTR)                                              \
    {                                                                         \
      /* @Trace: Com_SUD_API_01357 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM_POINTER); \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
    else if(((PduInfoPtr)->SduDataPtr) == NULL_PTR)                           \
    {                                                                         \
      /* @Trace: Com_SUD_API_01358 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
        COM_API_SERVICEID, COM_E_PARAM_POINTER);                              \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
  }while(0)                                                                     

/* Check whether Common pointer is NULL */
#define COM_DET_COMMON_PTR_CHECK_FLAG(CommonPtr,COM_API_SERVICEID)            \
  do{                                                                         \
    if((CommonPtr) == NULL_PTR)                                               \
    {                                                                         \
      /* @Trace: Com_SUD_API_01359 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM_POINTER); \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
  }while(0)     

/* Check whether Common pointer is NULL */
#define COM_DET_COMMON_PTR_PARAM_CHECK_FLAG(CommonPtr,COM_API_SERVICEID)      \
  do{                                                                         \
    if((CommonPtr) == NULL_PTR)                                               \
    {                                                                         \
      /* @Trace: Com_SUD_API_01360 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
  }while(0)     

/* Check whether PduInfoPtr pointer is NULL */
#define  COM_DET_IPDUGROUPVECTOR_CHECK_FLAG(COM_API_SERVICEID)                \
  do{                                                                         \
    if(ipduGroupVector == NULL_PTR)                                           \
    {                                                                         \
      /* @Trace: Com_SUD_API_01361 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM_POINTER); \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                   
  
/* Check whether signal ID is out of range */
#define  COM_DET_RX_SIGNALID_RANGE_CHECK_FLAG(COM_API_SERVICEID)              \
  do{                                                                         \
    if(SignalId >= (COM_RX_SIGNAL_COUNT + COM_RX_SIGINGROUP_COUNT))           \
    {                                                                         \
      /* @Trace: Com_SUD_API_01362 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

/* Check whether signal ID is out of for PB case */
#define  COM_DET_RX_SIGNALID_RANGE_CHECK_FLAG_PB(COM_API_SERVICEID)           \
  do{                                                                         \
    if(SignalId >= (Com_GlNoOfRxSignal + Com_GlNoOfRxSigInGrp))               \
    {                                                                         \
      /* @Trace: Com_SUD_API_01363 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)   

/* Check whether signal ID is out of range */
#define  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG(COM_API_SERVICEID)              \
  do{                                                                         \
    if(SignalId >= (COM_TX_SIGNAL_COUNT + COM_TX_SIGINGROUP_COUNT))           \
    {                                                                         \
      /* @Trace: Com_SUD_API_01364 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

/* Check whether signal ID is out of range for PB case */
#define  COM_DET_TX_SIGNALID_RANGE_CHECK_FLAG_PB(COM_API_SERVICEID)           \
  do{                                                                         \
    if(SignalId >= (Com_GlNoOfTxSignal + Com_GlNoOfTxSigInGrp))               \
    {                                                                         \
      /* @Trace: Com_SUD_API_01365 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)   

/* Check whether Rx signal group ID is out of range */
#define  COM_DET_RXSIGNALGROUPID_RANGE_CHECK_FLAG(COM_API_SERVICEID)          \
  do{                                                                         \
    if(SignalGroupId >= COM_RX_SIGGROUP_COUNT)                                \
    {                                                                         \
      /* @Trace: Com_SUD_API_01366 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)      

/* Check whether Rx signal group ID is out of range in case PB */
#define  COM_DET_RXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(COM_API_SERVICEID)       \
  do{                                                                         \
    if(SignalGroupId >= Com_GlNoOfRxSigGrp)                                   \
    {                                                                         \
      /* @Trace: Com_SUD_API_01367 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)   

/* Check whether Tx signal group ID is out of range */
#define  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG(COM_API_SERVICEID)          \
  do{                                                                         \
    if(SignalGroupId >= COM_TX_SIGGROUP_COUNT)                                \
    {                                                                         \
      /* @Trace: Com_SUD_API_01368 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

#define  COM_DET_TXSIGNALGROUPID_RANGE_CHECK_FLAG_PB(COM_API_SERVICEID)       \
  do{                                                                         \
    if(SignalGroupId >= Com_GlNoOfTxSigGrp)                                   \
    {                                                                         \
      /* @Trace: Com_SUD_API_01369 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)     

/* Check whether signal group ID is out of range */
#define  COM_DET_SIGNALID_TX_USS_RANGE_CHECK_FLAG(COM_API_SERVICEID)          \
  do{                                                                         \
    if(SignalId >= (Com_SignalIdType)(COM_TX_SIG_GRPSIG_BOUNDARY +            \
      (Com_SignalIdType)COM_TX_SIGINGROUP_COUNT))                             \
    {                                                                         \
      /* @Trace: Com_SUD_API_01370 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

/* Check whether signal group ID is out of range */
#define  COM_DET_SIGNALID_RX_USS_RANGE_CHECK_FLAG(COM_API_SERVICEID)          \
  do{                                                                         \
    if(SignalId >= (Com_SignalIdType)(COM_RX_SIG_GRPSIG_BOUNDARY +            \
      (Com_SignalIdType)COM_RX_SIGINGROUP_COUNT))                             \
    {                                                                         \
      /* @Trace: Com_SUD_API_01371 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     


/* Check whether signal data pointer is out of range */
#define  COM_DET_SIGNAL_DATA_PTR(COM_API_SERVICEID)                           \
  do{                                                                         \
    if(SignalDataPtr == NULL_PTR)                                             \
    {                                                                         \
      /* @Trace: Com_SUD_API_01372 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM_POINTER); \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     


/* Check whether I-PDU group ID is out of range */
#define  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG(COM_API_SERVICEID)              \
  do{                                                                         \
    if(IpduGroupId >= COM_IPDUGROUP_COUNT)                                    \
    {                                                                         \
      /* @Trace: Com_SUD_API_01373 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

/* Check whether I-PDU group ID is out of range for PB case */
#define  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG_PB(COM_API_SERVICEID)           \
  do{                                                                         \
    if(IpduGroupId >= Com_GlNoOfIpduGrp)                                      \
    {                                                                         \
      /* @Trace: Com_SUD_API_01374 */                                         \
      (void)Det_ReportError (COM_MODULE_ID, COM_INSTANCE_ID,                  \
                                     COM_API_SERVICEID, COM_E_PARAM);         \
      LucReturnValue = (uint8)COM_SERVICE_NOT_AVAILABLE;                      \
    }                                                                         \
  }while(0)                                                                     

#endif /* checking weather DET error check is ON */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations>  */

#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#define  COM_HANDLEID_CHECK_COREID(config, pduid, result)                     \
  {                                                                           \
    /* @Trace: Com_SUD_API_01375 */                                           \
    result = E_NOT_OK;                                                        \
    CoreId = GetCoreID();                                                     \
    if(CoreId == config[pduid])                                               \
    {                                                                         \
      /* @Trace: Com_SUD_API_01376 */                                         \
      result = E_OK;                                                          \
    }                                                                         \
  }

#define  COM_RXPDUID_CHECK_COREID(pduid,result)                               \
  do{                                                                         \
    /* @Trace: Com_SUD_API_01377 */                                           \
    COM_HANDLEID_CHECK_COREID(Com_GaaRxIpduCorePosition,pduid,result);        \
  }while(0)

#define  COM_TXPDUID_CHECK_COREID(pduid,result)                               \
  do{                                                                         \
    /* @Trace: Com_SUD_API_01378 */                                           \
    COM_HANDLEID_CHECK_COREID(Com_GaaTxIpduCorePosition,pduid,result);        \
  }while(0)
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

#endif /* COM_ERROR_H  */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
