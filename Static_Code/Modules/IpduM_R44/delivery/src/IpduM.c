/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM Module                                          **
**                                                                            **
**  PURPOSE   : This file provides definitions of following IpduM APIs:       **
**              IpduM_Init                                                    **
**              IpduM_GetVersionInfo                                          **
**              IpduM_Transmit                                                **
**              IpduM_RxIndication                                            **
**              IpduM_TxConfirmation                                          **
**              IpduM_TriggerTransmit                                         **
**              IpduM_MainFunctionTx                                          **
**              IpduM_MainFunctionRx                                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.5          16-Dec-2022         NhatTD2          CP44-1256              **
** 1.0.4.1        14-Nov-2022         NhatTD2          CP44-973               **
** 1.0.4          06-Nov-2022         NhatTD2          CP44-612               **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for IpduM header files  */
#include "IpduM.h"
/* Inclusion for Global variables and symbols */
#include "IpduM_Globals.h"
/* Inclusion for internal fucntions */
#include "IpduM_IntFunc.h"

#if(IPDUM_ENABLE_MODULE == STD_ON)

#if ((IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#include "SchM_IpduM.h"
#endif

#endif /* (IPDUM_ENABLE_MODULE == STD_ON) */

#define IPDUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : IpduM_Init                                          **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Initializes the I-PDU Multiplexer.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
** Remarks              : Global Variable(s) : IpduM_InitStatus               **
**                                                                            **
**                        Function(s) invoked: IpduM_InitMux()                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00032 SWS_IpduM_00033 SWS_IpduM_00084
 * SRS_BSW_00101 SRS_BSW_00344 SRS_BSW_00369 SRS_BSW_00405
 * SRS_BSW_00406 SRS_BSW_00438 SRS_IpduM_02807
 */
FUNC(void, IPDUM_CODE) IpduM_Init(
  P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_CONST) config)
{
#if (IPDUM_ENABLE_MODULE == STD_ON)
  #if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_CONST) IpduM_ConfigSet;
  IpduM_ConfigSet = config;

  #if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_SEGMENT_BITFIELD == STD_ON))
  IpduM_SegmentField =
     (P2CONST(IpduM_SegmentType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pSegmentField;
  #endif

  #if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_TX_STATIC_IPDU ==STD_ON)|| \
       (IPDUM_JIT_UPDATE == STD_ON)||(IPDUM_TX_CONF_IPDU == STD_ON))
  IpduM_TxOutIpdu =
    (P2CONST(IpduM_TxOutIpduType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pTxOutIpdu;
  #endif

  #if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_JIT_UPDATE == STD_ON)|| \
       (IPDUM_TX_CONF_IPDU == STD_ON))
  IpduM_TxInIpdu = 
    (P2CONST(IpduM_TxInIpduType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pTxInIpdu;
  #endif

  #if ((IPDUM_RX_IPDU == STD_ON)&&(IPDUM_RX_DYNAMIC_IPDU == STD_ON))
  IpduM_RxMuxDynPartArr = 
    (P2CONST(IpduM_RxMuxDynPartType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pRxMuxDynPartArr;
  IpduM_SelBitField =
    (P2CONST(IpduM_SelBitFieldType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pSelBitField;
  #endif

  #if ((IPDUM_RX_IPDU == STD_ON) && \
       ((IPDUM_RX_STATIC_IPDU == STD_ON)||(IPDUM_RX_DYNAMIC_IPDU == STD_ON)))
  IpduM_RxInIpdu =
     (P2CONST(IpduM_RxIpduType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pRxInIpdu;
  #endif

  #if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
  IpduM_TxReqPduArr =
     (P2CONST(IpduM_TxReqIntType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pTxReqPduArr;
  #endif
  
  #if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
  IpduM_RxIndPduArr =
     (P2CONST(IpduM_RxIndIntType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pRxIndPduArr;
  #endif

  #if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
  IpduM_TxConfPduArr =
     (P2CONST(IpduM_TxConfIntType, AUTOMATIC, IPDUM_CONST)) IpduM_ConfigSet->pTxConfIntType;
  #endif

  #endif

  /* To prevent multiple calls */
  if (IPDUM_INIT != IpduM_InitStatus)
  {
    /* @Trace: IpduM_SUD_API_295 */
    #if (IPDUM_TX_IPDU == STD_ON)
    /* Initiate all configured TxPathway */
    IpduM_InitMux();
    #endif /* (IPDUM_TX_IPDU == STD_ON) */
    #if (IPDUM_TX_CONTAINER == STD_ON)
    /* Initiate all configured TxContainer */
    /* @Trace: IpduM_SUD_API_296 */
    IpduM_InitContainer();
    #endif /* (IPDUM_TX_CONTAINER == STD_ON) */

    /* Set the Ipdum init status TRUE*/
    /* @Trace: IpduM_SUD_API_297 */
    IpduM_InitStatus = IPDUM_INIT;
  }
  else
  {
    /* No action */
  }
  
#endif

  #if ((IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_ON) && (IPDUM_ENABLE_MODULE == STD_ON))
  /* Unused as not support post-build yet */
  #else
  /* @Trace: IpduM_SUD_API_298 */
  IPDUM_UNUSED(config);
  #endif

} /* End of IpduM_Init() */

/*******************************************************************************
** Function Name        : IpduM_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Service returns the version information of this     **
**                        module.                                             **
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
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: Det_ReportError()              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00037
 * SRS_BSW_00003 SRS_BSW_00369 SRS_BSW_00407 SRS_BSW_00357
 */


#if(IPDUM_ENABLE_MODULE == STD_ON)
#if (IPDUM_VERSION_INFO_API == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_APPL_DATA) versioninfo)
{
  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether version information is equal to NULL */
  if (NULL_PTR == versioninfo)
  {
    /* @Trace: IpduM_SUD_API_299 */
    /* Report to DET */
    (void)Det_ReportError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID,
                          IPDUM_GETVERSIONINFO_SID, IPDUM_E_PARAM_POINTER);
  }
  else
  #endif /* End of if (IPDUM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: IpduM_SUD_API_300 */
    /* Copy the vendor ID */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "This ptr can not enter in state of NULL" */
    versioninfo->vendorID = (uint16)IPDUM_VENDOR_ID;
    /* Copy the module ID */
    versioninfo->moduleID = (uint16)IPDUM_MODULE_ID;
    /* Copy software major version */
    versioninfo->sw_major_version = (uint8)IPDUM_SW_MAJOR_VERSION;
    /* Copy software minor version */
    versioninfo->sw_minor_version = (uint8)IPDUM_SW_MINOR_VERSION;
    /* Copy software patch version */
    versioninfo->sw_patch_version = (uint8)IPDUM_SW_PATCH_VERSION;
  }
} /* End of IpduM_GetVersionInfo() */
#endif /* (IPDUM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_Transmit                                      **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Requests transmission of a PDU.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant for   **
**                        the same PduId.                                     **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                        PduInfoPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : IpduM_DetCheckFuncs()      **
**                                                 IpduM_TxIpduMux()          **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00043
 * SRS_BSW_00369
 */

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  IpduM_TxReqIntType txReqPduIdx;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: IpduM_SUD_API_301 */
  uint8 errorId;
  #endif
  /* Local variable for return value */
  Std_ReturnType retVal;

  /* Initiate return value as "not ok" */
  retVal = E_NOT_OK;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  /* Validate the input API parameters */
  /* @Trace: IpduM_SUD_API_302 */
  errorId = IpduM_DetCheckFuncs(IPDUM_TRANSMIT_SID, TxPduId,
                                IPDUM_MAX_TX_PDU_ID, PduInfoPtr);
  /* Check if no error occurred */
  if (IPDUM_E_NO_ERROR == errorId)
  #endif /* #if (IPDUM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: IpduM_SUD_API_303 */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Array index have generation rule alway bigger than zero" */
    txReqPduIdx = IpduM_GetTxReqPduIdx(TxPduId);
    #if ((IPDUM_TX_IPDU == STD_ON) && (IPDUM_TX_CONTAINER == STD_ON))
    if ((uint8)IPDUM_ZERO != IpduM_GetTxReqMuxFlag(TxPduId))
    #endif
    {
      /* @Trace: IpduM_SUD_API_304 */
      #if (IPDUM_TX_IPDU == STD_ON)
      /* Process transmission request for Multiplexed I-PDU */
      /* @Trace: IpduM_SUD_API_305 */
      retVal = IpduM_TxIpduMux((IpduM_TxPartIntType)txReqPduIdx, PduInfoPtr);
      #endif
    }
    #if ((IPDUM_TX_IPDU == STD_ON) && (IPDUM_TX_CONTAINER == STD_ON))
    else
    #endif
    {
      /* @Trace: IpduM_SUD_API_306 */
      #if (IPDUM_TX_CONTAINER == STD_ON)
      /* @Trace: IpduM_SUD_API_307 */
      retVal = IpduM_ContainerTransmit((IpduM_TxContainedIntType)txReqPduIdx, PduInfoPtr);
      #endif
    }
  } /*@ (E_OK == retVal) */
  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action */
  }
  #endif
  return (retVal);
} /* End of IpduM_Transmit() */
#endif /* ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON)) */

/*******************************************************************************
** Function Name        : IpduM_TxConfirmation                                **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : The lower layer communication interface module      **
**                        confirms the transmission of a PDU, or the failure  **
**                        to transmit a PDU.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant for   **
**                        the same PduId.                                     **
**                                                                            **
** Input Parameters     : PduIdType                                           **
**                        result                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: IpduM_DetCheckFuncs()          **
**                                             IpduM_TxConfirmIpduMux()       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00044
 * SRS_BSW_00369
 */

#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
FUNC(void, IPDUM_CODE) IpduM_TxConfirmation(
  PduIdType TxPduId, Std_ReturnType result)
{
  IpduM_TxConfIntType txConfPduIdx;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId;

  /* Validate the input API parameters */
  /* @Trace: IpduM_SUD_API_308 */
  errorId = IpduM_DetCheckFuncs(IPDUM_TXCONFIRMATION_SID, TxPduId,
                                IPDUM_MAX_TX_CONF_PDU_ID, NULL_PTR);
  /* Check if no error occurred */
  if (IPDUM_E_NO_ERROR == errorId)
  #endif /* #if (IPDUM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: IpduM_SUD_API_309 */
    /* Get index of IPDU */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Array index have generation rule alway bigger than zero" */
    txConfPduIdx = IpduM_GetTxConfPduIdx(TxPduId);

    #if ((IPDUM_TX_CONF_IPDU == STD_ON) && (IPDUM_TX_CONF_CONTAINER == STD_ON))
    /* Check if receiving request for multiplexed IPDU */
    if ((uint8)IPDUM_ZERO != IpduM_GetTxConfMuxFlag(TxPduId))
    #endif
    {
      /* @Trace: IpduM_SUD_API_310 */
      #if (IPDUM_TX_CONF_IPDU == STD_ON)
      /* Generate TxConfirmation for dynamic and static parts */
      IpduM_TxConfirmIpduMux(txConfPduIdx, result);
      #endif
    }
    #if ((IPDUM_TX_CONF_IPDU == STD_ON) && (IPDUM_TX_CONF_CONTAINER == STD_ON))
    else
    #endif
    {
      /* @Trace: IpduM_SUD_API_311 */
      #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
      IpduM_ContainerTxConfirmation((IpduM_TxContainerIntType)txConfPduIdx, result);
      #endif
    }
  }/* End of IpduM_TxConfirmation(PduIdType, TxPduId) */
  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action */
  }
  #endif
} /* End of IpduM_TxConfirmation() */
#endif /* ((IPDUM_TX_CONF_IPDU == STD_ON)) ||
           (IPDUM_TX_CONF_CONTAINER == STD_ON)) */

/*******************************************************************************
** Function Name        : IpduM_TriggerTransmit                               **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : Within this API, the upper layer module (called     **
**                        module) shall check whether the available data fits **
**                        into the buffer size reported by                    **
**                        PduInfoPtr->SduLength.                              **
**                        If it fits, it shall copy its data into the buffer  **
**                        provided by PduInfoPtr->SduDataPtr and update the   **
**                        length of the actual copied data in                 **
**                        PduInfoPtr->SduLength.                              **
                          If not, it returns E_NOT_OK without changing        **
                          PduInfoPtr.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant for   **
**                        the same PduId.                                     **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                        PduInfoPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: IpduM_DetCheckFuncs()          **
**                                             IpduM_TriggerTxIpduMux()       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00060
 * SRS_BSW_00369
 */

#if ((IPDUM_TX_TRIGGERTRANS_IPDU == STD_ON) || \
     (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON))
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTransmit(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  IpduM_TxConfIntType txTriggerPduIdx;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId;
  #endif

  /* Local variable for return value */
  Std_ReturnType retVal;

  /* Initiate return value as "not ok" */
  /* @Trace: IpduM_SUD_API_312 */
  retVal = E_NOT_OK;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  /* Validate the input API parameters */
  /* @Trace: IpduM_SUD_API_313 */
  errorId = IpduM_DetCheckFuncs(IPDUM_TRIGGERTRANSMIT_SID, TxPduId,
                  IPDUM_MAX_TX_CONF_PDU_ID,
                  (P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA))PduInfoPtr);
  /* Check if no error occurred */
  if (IPDUM_E_NO_ERROR == errorId)
  #endif /* #if (IPDUM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: IpduM_SUD_API_314 */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Array index have generation rule alway bigger than zero" */
    txTriggerPduIdx = IpduM_GetTxConfPduIdx(TxPduId);

    #if ((IPDUM_TX_TRIGGERTRANS_IPDU == STD_ON) && \
         (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON))
    /* Check if receiving request for multiplexed IPDU */
    if ((uint8)IPDUM_ZERO != IpduM_GetTxConfMuxFlag(TxPduId))
    #endif
    {
      /* @Trace: IpduM_SUD_API_315 */
      #if (IPDUM_TX_TRIGGERTRANS_IPDU == STD_ON)
      /* Request contents of multiplexed I-PDU */
      retVal = IpduM_TriggerTxIpduMux(txTriggerPduIdx, PduInfoPtr);
      #endif
    }
    #if ((IPDUM_TX_TRIGGERTRANS_IPDU == STD_ON) && \
         (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON))
    else
    #endif
    {
      /* @Trace: IpduM_SUD_API_316 */
      #if (IPDUM_TX_TRIGGERTRANS_CONTAINER == STD_ON)
      retVal = IpduM_ContainerTriggerTransmit((IpduM_TxContainedIntType)txTriggerPduIdx, PduInfoPtr);
      #endif /* (IPDUM_TX_TRIGGERTRANS_CONTAINER == STD_ON) */
    }
  }
  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action */
  }
  #endif
  /* @Trace: IpduM_SUD_API_317 */
  return (retVal);
} /* End of IpduM_TriggerTransmit() */
#endif /* ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON)) */


/*******************************************************************************
** Function Name        : IpduM_RxIndication                                  **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : Indication of a received PDU from a lower layer     **
**                        communication interface module.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant for   **
**                        the same PduId.                                     **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                        PduInfoPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: IpduM_DetCheckFuncs()          **
**                                              IpduM_RxIpduMux()             **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00040 SWS_IpduM_00041 SWS_IpduM_00042 SWS_IpduM_00217
 * SWS_IpduM_00086
 * SRS_IpduM_02817 SRS_BSW_00369 SRS_IpduM_02812 SRS_IpduM_02820
 */


#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
FUNC(void, IPDUM_CODE) IpduM_RxIndication(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  IpduM_RxIndIntType rxIndId;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId;

  /* Validate the input API parameters */
  /* @Trace: IpduM_SUD_API_318 */
  errorId = IpduM_DetCheckFuncs(IPDUM_RXINDICATION_SID, RxPduId,
		                        IPDUM_MAX_RX_PDU_ID, PduInfoPtr);

  /* Check if no error occurred */
  if (IPDUM_E_NO_ERROR == errorId)
  #endif /* #if (IPDUM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: IpduM_SUD_API_319 */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Array index have generation rule alway bigger than zero" */
    rxIndId = IpduM_GetRxIndPduIdx(RxPduId);

    #if ((IPDUM_RX_IPDU == STD_ON) && (IPDUM_RX_CONTAINER == STD_ON))
    if ((uint8)IPDUM_ZERO != IpduM_GetRxIndMuxFlag(RxPduId))
    #endif
    #if (IPDUM_RX_IPDU == STD_ON)
    {
      /* Check if length of incoming I-PDU is not zero */
      /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "This ptr can not enter in state of NULL" */
      if ((PduLengthType)IPDUM_ZERO < PduInfoPtr->SduLength)
      {
        /* @Trace: IpduM_SUD_API_320 */
        /* Process the receiving multiplexed I-PDU */
        IpduM_RxIpduMux((IpduM_RxMuxIntType)rxIndId, PduInfoPtr);
      }
      else
      {
        /* No action */
      }
    }
    #endif
    #if ((IPDUM_RX_IPDU == STD_ON) && (IPDUM_RX_CONTAINER == STD_ON))
    else
    #endif
    {
      /* @Trace: IpduM_SUD_API_321 */
      #if (IPDUM_RX_CONTAINER == STD_ON)
      IpduM_ContainerRxIndication((IpduM_RxContainerIntType)rxIndId, PduInfoPtr);
      #endif /* (IPDUM_RX_CONTAINER == STD_ON) */
    }
  } /* End of if (FALSE == errorFlag) */
  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action */
  }
  #endif
} /* End of IpduM_RxIndication() */
#endif /* ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON)) */

#endif /*IPDUM_ENABLE_MODULE == STD_ON */

/*******************************************************************************
** Function Name        : IpduM_MainFunctionTx                                **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This function performs the processing of the        **
**                        transmission activities that are not directly       **
**                        handled within the calls from PduR.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: PduR_IpduMTransmit()           **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_91002
 * SWS_IpduM_91002
 */
#if(IPDUM_ENABLE_MODULE == STD_OFF)
FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx(void)
{
	/* dummy call */
}
#elif (IPDUM_TX_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx(void)
{
  IpduM_TxContainerIntType containerId;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (IPDUM_INIT == IpduM_InitStatus)
  #endif
  {
    /* @Trace: IpduM_SUD_API_322 */
    containerId = (IpduM_TxContainerIntType)IPDUM_ZERO;
    while ((IpduM_TxContainerIntType)IPDUM_NO_OF_TX_CONTAINERS > containerId)
    {
      /* @Trace: IpduM_SUD_API_323 */
      IpduM_TxQueuedContainerPdu(containerId);

      #if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON))
      if (FALSE != IpduM_IsTimeoutBaseTriggeringForContainerTx(containerId))
      {
        /* @Trace: IpduM_SUD_API_324 */
        SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
        if (IPDUM_TX_CONTAINER_UNLOCK == IpduM_GetTxContainerProtection(containerId))
        {
          /* @Trace: IpduM_SUD_API_325 */
          IpduM_SetTxContainerProtection(containerId, IPDUM_TX_CONTAINER_LOCK);
          SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

          if ((uint16)IPDUM_ONE == IpduM_GetContainerTxPduSendTimer(containerId))
          {
            /* @Trace: IpduM_SUD_API_326 */
            IpduM_TriggerContainerPdu(containerId, TRUE);
          }
          else
          {
            /* No action */
          }
          if ((uint16)IPDUM_ZERO < IpduM_GetContainerTxPduSendTimer(containerId))
          {
            /* @Trace: IpduM_SUD_API_327 */
            IpduM_DecContainerTxPduSendTimer(containerId);
          }
            /* @Trace: IpduM_SUD_API_328 */
          SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
          IpduM_SetTxContainerProtection(containerId, IPDUM_TX_CONTAINER_UNLOCK);
        }
        else
        {
          /* No action */
        }
        /* @Trace: IpduM_SUD_API_329 */
        SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
      } /* End of checking containerPdu support time-base triggering */
      #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
      else
      {
        /* No action */
      }
      #endif
      #endif /* ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON)) */
      /* Increase counter for next containerPdu */
      /* @Trace: IpduM_SUD_API_330 */
      containerId++;
    } /* End while loop all Tx ContainerPdu */
  } /* End if (IPDUM_INIT == IpduM_InitStatus) */
  else
  {
    /* No action */
  }
} /* End of IpduM_MainFunctionTx() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_MainFunctionRx                                **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This function performs the processing of the        **
**                        reception activities that are not directly handled  **
**                        within the calls from PduR.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: IpduM_DequeueRxContainerPdu()  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_91001
 * SWS_IpduM_91002
 * SRS_BSW_00432
 */

#if (IPDUM_ENABLE_MODULE == STD_OFF)
FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx(void){
	/* dummy call */
}
#elif (IPDUM_RX_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx(void)
{
  #if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
  IpduM_RxContainerIntType containerId;

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (IPDUM_INIT == IpduM_InitStatus)
  #endif
  {
    /* @Trace: IpduM_SUD_API_331 */
    containerId = (IpduM_RxContainerIntType)IPDUM_ZERO;
    while (IPDUM_NO_OF_RX_CONTAINERS > containerId)
    {
      /* Deferred ContainerRxPdu shall be extracted */
      if (FALSE == IpduM_IsRxContainerPduImmediateProcessing(containerId))
      {
      /* @Trace: IpduM_SUD_API_332 */
        IpduM_ExtractQueuedRxContainer(containerId);
      }
      else
      {
        /* No action */
      }
      /* @Trace: IpduM_SUD_API_333 */
      containerId++;
    }
  }
  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action */
  }
  #endif
  #endif /* (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON) */

} /* End of IpduM_MainFunctionRx() */
#endif /* (IPDUM_RX_CONTAINER == STD_ON) */

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
