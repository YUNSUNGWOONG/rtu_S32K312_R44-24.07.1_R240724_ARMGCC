/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : APIs implementation for CanTp module                          **
**              CanTp_Init                                                    **
**              CanTp_Shutdown                                                **
**              CanTp_Transmit                                                **
**              CanTp_MainFunction                                            **
**              CanTp_GetVersionInfo                                          **
**              CanTp_CancelTransmit                                          **
**              CanTp_CancelReceive                                           **
**              CanTp_ChangeParameter                                         **
**              CanTp_ReadParameter                                           **
**              CanTp_TimeoutProcessing                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     31-Oct-2023   HieuTM8        #CP44-2819                          **
** 1.0.9     12-Dec-2022   HieuTM8        #CP44-1244                          **
** 1.0.8     25-Nov-2022   HieuTM8        #CP44-1120, #CP44-1199              **
** 1.0.7     31-Oct-2022   HieuTM8        #CP44-1038, #CP44-892               **
** 1.0.5     12-Aug-2022   HieuTM8        CP44-743                            **
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26810, #26528          **
** 1.0.2     13-Apr-2022   HieuTM8        R44-Redmine #25679                  **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344          **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp.h"                /* CanTp Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_Cbk.h"            /* CanTp Callback APIs Header File */
#include "CanTp_TxInternal.h"     /* CanTp TxInternal Header File */
#include "CanTp_RxInternal.h"     /* CanTp RxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Ram Header File */
#include "PduR_CanTp.h"           /* PduR header for CAN TP */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* @Trace: SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_C_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_C_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_C_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_C_SW_MAJOR_VERSION            0x01u
#define CANTP_C_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_C_SW_MAJOR_VERSION)
#error "CanTp.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_C_SW_MINOR_VERSION)
#error "CanTp.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

static FUNC(void, CANTP_CODE) CanTp_TimeoutProcessing(
                    VAR(uint8, CANTP_VAR) rxTxInstances);

/*******************************************************************************
** Function Name        : CanTp_Init                                          **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes all global variables of    **
**                        the CAN Transport Layer and set the CanTp module to **
**                        idle state.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : CfgPtr                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_InitStatus,          **
**                                                 CanTp_ChannelRam           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01075 SRS_BSW_00101 SRS_BSW_00358 SRS_BSW_00414 */
FUNC(void, CANTP_CODE) CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC,
    CANTP_APPL_CONST) CfgPtr)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelTxRam;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRxRam;
  uint8 rxTxInstances;
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  uint8 metaDataIdx;
  #endif
  #endif

  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  if (CfgPtr == NULL_PTR)
  {
    #if (STD_ON == CANTP_DEV_ERROR_DETECT)
    /* Report Error to DET */
    /* @Trace: CanTp_SUD_API_001 */
    /* @Trace: SWS_CanTp_00293 */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID, CANTP_INIT_SID, CANTP_E_PARAM_POINTER);
    #endif
    CanTp_InitStatus = CANTP_FALSE;
  }
  else
  #endif
  {
    /* @Trace: CanTp_SUD_API_003 */
    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Select variant */
    Variant_Select = CfgPtr;

    /* Get the number of total Rx and Tx of all channels */
    CanTp_NumOfChannel = Variant_Select->TotalRxTxChannels;

    #else /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    CANTP_UNUSED(CfgPtr);
    #endif /* End of if (STD_OFF == CANTP_VARIANT_POSTBUILD_SUPPORT) */

    /* @Trace: SWS_CanTp_00169 */
    /* In the state CANTP_OFF, the CanTp shall allow
    * an update of the postbuild (use CfgPtr) configuration.*/

    /* Initialize  Instance counter to zero  */
    rxTxInstances = (uint8)CANTP_ZERO;
    /* @Trace: SWS_CanTp_00030 */
    /* The function CanTp_Init shall initialize all global
    * variables of the module and sets all transport protocol connections
    * in a sub-state of CANTP_ON*/
    do
    {
      /* Get the address of first channel Ram */
      ptrChannelTxRam = &CanTp_ChannelTxRam[rxTxInstances];
      ptrChannelRxRam = &CanTp_ChannelRxRam[rxTxInstances];
      /* @Trace: SWS_CanTp_00273 */
      /* Note: The CanTp module shall loose all current connections
      * if CanTp_Init is called when CanTp module is in the global
      * state CANTP_ON */
      /* @Trace: SWS_CanTp_00111 */
      /* Note: If called when the CanTp module is in the global state CANTP_ON,
      * the function CanTp_Init shall return the module to state Idle
      * (state = CANTP_ON, but neither transmission nor reception are
      * in progress). */
      ptrChannelTxRam->ChannelState = (uint8)CANTP_WAIT;
      ptrChannelRxRam->ChannelState = (uint8)CANTP_WAIT;
      /* Change the Tx confirm state to IDLE */
      ptrChannelTxRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
      ptrChannelRxRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
      #if (CANTP_RX_NSDU == STD_ON)
      /* Change the AvlBuffLength value to ZERO */
      ptrChannelTxRam->AvlBuffLength = (uint16)CANTP_ZERO;
      ptrChannelRxRam->AvlBuffLength = (uint16)CANTP_ZERO;
      #endif

      /* Set RxDl to default 8 bytes */
      ptrChannelTxRam->RxDl = (uint8)CANTP_EIGHT;
      ptrChannelRxRam->RxDl = (uint8)CANTP_EIGHT;
      #ifdef CANTP_DYNID_SUPPORT
      /* Indicate status of MetaData buffer of channel */
      ptrChannelTxRam->AvlMetaDt = CANTP_FALSE;
      ptrChannelRxRam->AvlMetaDt = CANTP_FALSE;
      #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
      for (metaDataIdx = (uint8)CANTP_ZERO; \
        metaDataIdx < (uint8)CANTP_METADATA_LEN_MAX; \
        metaDataIdx++)
      {
        /* Set the metaData to default value*/
        ptrChannelTxRam->UpMetaData[metaDataIdx] = CANTP_INVALID;
        ptrChannelRxRam->UpMetaData[metaDataIdx] = CANTP_INVALID;
      }
      #endif

      #if ( (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
      (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
      (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) )
      ptrChannelTxRam->LoMetaData.WholeLong = CANTP_MAX_SDU_LENGTH;
      ptrChannelRxRam->LoMetaData.WholeLong = CANTP_MAX_SDU_LENGTH;
      #endif /*if ( (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
      (STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED_ADDRESS) ) */
      #endif /* CANTP_DYNID_SUPPORT */

      /* Increment Instance counter */
      rxTxInstances++;

    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    } while (rxTxInstances < (uint8)CanTp_NumOfChannel);
    #else
    } while (rxTxInstances < ((uint8)CANTP_TOTAL_RX_TX_CHANNELS));
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

    /* SWS_CanTp_00170 */
    /* The CanTp module shall change to the internal state CANTP_ON
    * when the CanTp has been successfully initialized */
    /* @Trace: SWS_CanTp_00238 */
    /* Note: The CanTp module shall perform segmentation and re-assembly tasks only when
    * the CanTp is in the CANTP_ON state */
    CanTp_InitStatus = CANTP_TRUE;
  }
} /* End of CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_Shutdown                                      **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service closes all pending transport protocol  **
**                        connections, frees all resources and sets the       **
**                        corresponding CanTp module into the CANTP_TRUE state**
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
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_InitStatus,          **
**                                                 CanTp_ChannelRam           **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00336 */
FUNC(void, CANTP_CODE) CanTp_Shutdown(void)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelTxRam;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRxRam;
  uint8 rxTxInstances;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* @Trace: SWS_CanTp_00199 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  /* CanTp not Initilized */
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* @Trace: CanTp_SUD_API_004 */
    /* Report Det Error */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_SHUTDOWN_SID, CANTP_E_UNINIT);
  }
  else
  #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: CanTp_SUD_API_006 */
    rxTxInstances = (uint8)CANTP_ZERO;
    /* Get the address of first channel Ram */
    ptrChannelTxRam = &CanTp_ChannelTxRam[rxTxInstances];
    ptrChannelRxRam = &CanTp_ChannelRxRam[rxTxInstances];
    /* @Trace: SWS_CanTp_00202 */
    /* Lose all pending transport protocol connections */
    /* Reset all channels to the default value */
    do
    {
      /* Change the channel state to WAIT/IDLE */
      ptrChannelTxRam->ChannelState = (uint8)CANTP_WAIT;
      ptrChannelRxRam->ChannelState = (uint8)CANTP_WAIT;
      /* Change the Tx confirm state to IDLE */
      ptrChannelTxRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
      ptrChannelRxRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
      /* Increment Instance counter */
      rxTxInstances++;

      /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    } while (rxTxInstances < (uint8)CanTp_NumOfChannel);
    #else
    } while (rxTxInstances < ((uint8)CANTP_TOTAL_RX_TX_CHANNELS));
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    /* @Trace: SWS_CanTp_00010 */
    /* The function CanTp_Shutdown shall stop the CanTp module properly */
    /* Set the Global Initialization status */
    CanTp_InitStatus = CANTP_FALSE;
  } /* If no development error has occurred */
} /* End of CanTp_Shutdown(void) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_Transmit                                      **
**                                                                            **
** Service ID           : 0x49                                                **
**                                                                            **
** Description          : This service is used to request the transfer of     **
**                        segmented data.                                     **
**                                                                            **
** Sync/Async           : Asnchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpTxSduId                                        **
**                        CanTpTxInfoPtr                                      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_BytePos,             **
**                                                 CanTp_TxSduStatic,         **
**                                                 CanTp_ChannelRam           **
**                                                 CANTP_CHANNEL_ID            **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_TxDetCheck           **
**                                                 CanTp_TxDlcCheck           **
**                                         CanTp_TransmissionComplete         **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01071 SRS_Can_01074  SRS_Can_01066 SRS_Can_01116 SRS_Can_01163 
 * SRS_BSW_00159, SRS_BSW_00167, SRS_BSW_00353, SRS_Can_01086, SRS_ES95486_02E_SWP_00019, SRS_ES95486_02E_SWP_00020 
 * , SWP_CP_SRS_UDS_0001, SRS_ES95486_02E_SWP_00026, SRS_ES95486_02E_SWP_00028, SRS_ES95486_02E_SWP_00029
 * SRS_ES95486_02E_SWP_00048, SRS_ES95486_02E_SWP_00049, , SRS_ES95486_02E_SWP_00030, SWP_CP_SRS_UDS_0002
 * SWP_CP_SRS_UDS_0003, SRS_ES95486_02E_SWP_00037, SRS_ES95486_02E_SWP_00038, SRS_ES95486_02E_SWP_00039, SRS_ES95486_02E_SWP_00040
 * SWP_CP_SRS_UDS_0007, SRS_ES95486_02E_SWP_00053, SRS_ES95486_02E_SWP_00045, , SRS_ES95486_02E_SWP_00046
 * SRS_ES95486_02E_SWP_00047, SRS_ES95486_02E_SWP_00051, , SRS_ES95486_02E_SWP_00050, 
 * SRS_ES95486_02E_SWP_00052, SRS_ES95486_02E_SWP_00067, SRS_ES95486_02E_SWP_00069, SRS_ES95486_02E_SWP_00070, SRS_ES95486_50E_SWP00020
 * SRS_ES95486_50E_SWP00023, SRS_ES95486_50E_SWP00035, SRS_ISO_15765_00001, SRS_ISO_15765_00002, SRS_ISO_15765_00003
 * SRS_ISO_15765_00004, SRS_ISO_15765_00005, SRS_ISO_15765_00006, SRS_ISO_15765_00007, SRS_ISO_15765_00008
 * SRS_ISO_15765_00009, SRS_ISO_15765_00010, SRS_ISO_15765_00011, SRS_ISO_15765_00012, SRS_ISO_15765_00013
 * SRS_ISO_15765_00014, SRS_ISO_15765_00015, SRS_ISO_15765_00016, SRS_ISO_15765_00018, SRS_ISO_15765_00019
 * SRS_ISO_15765_00020, SRS_ISO_15765_00021, SRS_ISO_15765_00022 
*/
/* Note: The CanTp module shall perform segmentation and re-assembly tasks only when
 * the CanTp is in the CANTP_ON state */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrStaticTxNSdu;
  Std_ReturnType returnValue;
  CanTp_ChannelType channel;
  CanTp_LongAccessType dataLen;
  uint8 bytePosition;
  boolean dlcErrorFlag;
  uint8 txDataMaxLength;
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if (((STD_ON == CANTP_TX_EXTENDED_ADDRESS)||(STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)\
      ||(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS)) \
    && (STD_ON == CANTP_TX_NSDU_METADATA))
  VAR(CanTp_WordAccessType, AUTOMATIC) wordAccess;
  #endif
  #if (STD_ON == CANTP_TX_NSDU_METADATA)
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrMetaData;
  #endif
  #endif /* (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #endif /* def CANTP_DYNID_SUPPORT */

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  returnValue = CanTp_TxDetCheck(CanTpTxSduId, CanTpTxInfoPtr);

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if (((STD_ON == CANTP_TX_EXTENDED_ADDRESS)||(STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)\
      ||(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS)) \
      && (STD_ON == CANTP_TX_NSDU_METADATA))
  /* set to default value*/
  wordAccess.WholeWord = (uint16)CANTP_ZERO;
  #endif
  #endif
  #endif
  
  if (E_OK == returnValue)
  #endif /* if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanTp_SUD_API_007 */
    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Get the pointer to current TxNsdu */
    ptrStaticTxNSdu = &(Variant_Select->PtrTxNSduStatic)[CanTpTxSduId];
    #else
    /* Get the pointer to current TxNsdu */
    ptrStaticTxNSdu = &CanTp_TxSduStatic[CanTpTxSduId];
    #endif
    
    /* Set return value (uint8) E_NOT_OK */
    returnValue = E_NOT_OK;

    /* @Trace: SWS_CanTp_00354 */
    /* Set the Tx max length from the PduLength configuration parameter of EcuC */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This warnning is checked by the CanTp_TxDetCheck() function with the condition ptrTxNSduStatic-> TxSduMaxLength. Therefore, thhis warnning not imapct" */
    txDataMaxLength = ptrStaticTxNSdu->TxSduMaxLength;

    /* Get the connection channel Id */
    channel = ptrStaticTxNSdu->ChannelId;

    /* Get the Sdu Channel Ram base on mapping table and channel value */
    ptrChannelRam = &CanTp_ChannelTxRam[CanTp_ChannelMapping[channel]];

    /* @Trace: SWS_CanTp_00287 */
    /* The CanTp module shall not accept the receiving or
     * the transmission of N-SDU with the same identifier in parallel,
     * because otherwise the received frames cannot be assigned to the correct connection.
     * When only specific connections (without MetaData) are used,
     * this requirement is enforced by the configuration, because each N-SDU is linked to only one connection channel
     */
    /* @Trace: SWS_CanTp_00288 */
    /* The CAN Transport Layer will reject transmission, if no free connection channels are available */
    /* @Trace: SWS_CanTp_00206 */
    /* The function CanTp_Transmit shall reject a request if the CanTp_Transmit
     * service is called for a N-SDU identifier which is being used in a currently running
     * CAN Transport Layer session.*/
    if ((uint8)CANTP_WAIT == ptrChannelRam->ChannelState)
    {
      /* @Trace: CanTp_SUD_API_181 */
      /* Set the channel state to CANTP_TX_NORMAL */
      ptrChannelRam->ChannelState = (uint8)CANTP_TX_NORMAL;
      /* Set all Tx timer to default value */
      CANTP_STOP_ALL_TX_TIMERS(CanTp_ChannelMapping[channel]);
      /* Set the active PduId */
      ptrChannelRam->ActivePduId = CanTpTxSduId;
      /* @Trace: SWS_CanTp_00299 */
      /* Only the data length information of the structure indicated by PduInfoPtr has to be used */
      /* Copy the requested NSDU length into union variable */
      /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "Value is checked by CanTp_TxDetCheck" */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "This warning is checked by the CanTp_TxDetCheck() function with case of CanTpTxInfoPtr->SduLength,. It's compared with the value of maximum of sduLength. Therefore, this warnning not impact." */
      dataLen.WholeLong = (uint32)CanTpTxInfoPtr->SduLength;

      /* Validate DLC. Error flag is set to TRUE in following condition.
       *   1. If Nsdu is configured for physical addressing and DLC is less
       *      than configured sdu length.
       *   2. If Nsdu is configured for functional addressing and DLC is
       *      greater than 6 byte.
       */
      dlcErrorFlag = CanTp_TxDlcCheck(ptrStaticTxNSdu,
        (PduLengthType)dataLen.WholeLong);

      if (CANTP_TRUE == dlcErrorFlag)
      {
        /* @Trace: CanTp_SUD_API_008 */
        /* Terminate the new transmission */
        /* @Trace: SWS_CanTp_00255 */
        CanTp_TransmissionComplete
          (ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
      }
      else /* No DLC error */
      {
        /* @Trace: CanTp_SUD_API_009 */
        /* Copy the NSDU length to global variable */
        ptrChannelRam->ByteCounter = dataLen.WholeLong;

        /* Get the N_PCI position if transmit NSDU is configured as Extended */
        bytePosition = CanTp_BytePos[ptrStaticTxNSdu->AddressingMode];

        /* Based on bytePos, update the current addressing global variable
         * bytePos = 0 -> CANTP_STANDARD/NORMALFIXED_ADDRESS
         * bytePos = 1 -> CANTP_MIXED/MIXED29BIT/EXTENDED_ADDRESS */
        ptrChannelRam->CurrentBytePosition = bytePosition;

        #ifndef CANTP_DYNID_SUPPORT
        #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED_ADDRESS)||(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
        if (bytePosition > (uint8)CANTP_ZERO)
        {
          /* @Trace: CanTp_SUD_API_010 */
          /* @Trace: SWS_CanTp_00281 */
          /* Fill the first byte of each transmitted segmented
          * (SF, FF and CF) with the N_TA or N_AE */
            ptrChannelRam->DataBuffer[CANTP_ZERO] = \
                    ptrStaticTxNSdu->NTaOrNAeValue;
        }
        #endif
        #else /* #ifdef CANTP_DYNID_SUPPORT */
        /* @Trace: SWS_CanTp_00334 */
        /* When CanTp_Transmit is called for an N-SDU with MetaData,
         * the CanTp module shall store the addressing information contained in the MetaData of
         * the N-SDU and use this information for transmission of SF, FF, and CF N-PDUs and
         * for identification of FC N-PDUs.
         * The addressing information in the MedataData depends on the addressing format
         * Normal: none
         * Extended: N_TA
         * Mixed 11 bit: N_AE
         * Normal fixed: N_SA, N_TA
         * Mixed 29 bit: N_SA, N_TA, N_AE.
         *
         * @brief: Description about metaData shall be used for configures one Pdu.
         * 1. Enum parameter MetaDataItemType to MetaDataItem, with values:
         * + SOURCE_ADDRESS_16 (MetaDataItemLength = 16, DoIP, CanTp, FrTp, J1939Tp)
         * + TARGET_ADDRESS_16 (MetaDataItemLength = 16, DoIP, CanTp, FrTp, J1939Tp)
         * + ADDRESS_EXTENSION_8 (MetaDataItemLength = 8, CanTp only)
         * + CAN_ID_32  (CanIf)
         * 2. The MetaDataType defines the content of the meta data in EcuC module.
         * 2.1. One MetaDataType shall content at least one MetaDataItem.
         * 2.2. Length of metaData depend one number of MetaDataItem.
         * 3. The Generate tool have to check the consistance of metadata length with
         * Addressing type of CanTp.
         * 4. CanTp consumes and produce the metaData from Up to Lo layer in Transmit
         * and from Lo to Up layer in Reception.
         */
        #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
        /* @Trace: SWS_CanTp_00299 */
        /* For an N-SDU with MetaData, the MetaData also provided via the PduInfoPtr is relevant */
        #if (STD_ON == CANTP_TX_NSDU_METADATA)
        if(NULL_PTR != CanTpTxInfoPtr->MetaDataPtr)
        {
          /* @Trace: CanTp_SUD_API_011 */
          ptrMetaData = &CanTpTxInfoPtr->MetaDataPtr[(uint8)CANTP_ZERO];
        }
        else
        {
          /* @Trace: CanTp_SUD_API_012 */
          ptrMetaData = NULL_PTR;
        }
        #endif /* (STD_ON == CANTP_TX_NSDU_METADATA) */
        #endif /* (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
        #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) || \
            (STD_ON == CANTP_TX_MIXED_ADDRESS) || \
            (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) || \
            (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS))
        switch (ptrStaticTxNSdu->AddressingMode)
        {      
          #if (STD_ON == CANTP_TX_EXTENDED_ADDRESS)
          /* Extended address shall consume TARGET_ADDRESS_16 from Upper layer.
          * Pack to first byte of pay-load of transmit messages if Generic connection
          * is enable. Otherwise, default value shall be use by internal configured.
          */
          case (uint8)CANTP_EXTENDED_ADDRESS:
            /* @Trace: CanTp_SUD_API_013 */
            /* Store the addressing information contained
            * in the MetaData of the N-SDU
            */
            #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
            /* MetaData is available. */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;
            /* Copy N_TA from Upper metaData to local var,
              * Incase: Pdu has configured with metaData and
              * metaDataPtr is not Null.
              * */
            #if (STD_ON == CANTP_TX_NSDU_METADATA)
            if((CANTP_TRUE == ptrStaticTxNSdu->InTxPduwithMetaDataSts) &&\
            (NULL_PTR != ptrMetaData))
            {
              /* @Trace: CanTp_SUD_API_014 */
              #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
              wordAccess.byte_val.MSByte = ptrMetaData[(uint8)CANTP_ZERO];
              wordAccess.byte_val.LSByte = ptrMetaData[(uint8)CANTP_ONE];
              #else
              wordAccess.byte_val.LSByte = ptrMetaData[(uint8)CANTP_ZERO];
              wordAccess.byte_val.MSByte = ptrMetaData[(uint8)CANTP_ONE];
              #endif
              ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = wordAccess.byte_val.LSByte;
            }
            else
            #endif /* (STD_ON == CANTP_TX_NSDU_METADATA) */
            {
              /* @Trace: CanTp_SUD_API_015 */
              /* Use local configuration set */
              ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrStaticTxNSdu->NTaOrNAeValue;
            }
            #else /* End of #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
            /* If generic connection is disable, handle same as
              * one specific connection */
            ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrStaticTxNSdu->NTaOrNAeValue;
            #endif /* End of #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
            break;
          #endif /* End of #if (STD_ON == CANTP_TX_EXTENDED_ADDRESS) */
          #if (STD_ON == CANTP_TX_MIXED_ADDRESS)
          /* Mixed address shall consume ADDRESS_EXTENSION_8 from Upper layer.
          * Pack to first byte of pay-load of transmit messages if Generic connection
          * is enable. Otherwise, default value shall be use by internal configured.
          */
          case (uint8)CANTP_MIXED_ADDRESS:
          
            /* @Trace: CanTp_SUD_API_016 */
            #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
          /* MetaData shall be not use to forward to Lo layer
            * with mixed addressing. */
            ptrChannelRam->AvlMetaDt = CANTP_FALSE;
            /* Copy NAe
            * Copy from metaData if pdu is configured and available metaData
            * Otherwise, use default value from module.
            * */
            #if (STD_ON == CANTP_TX_NSDU_METADATA)
            if ((NULL_PTR != ptrMetaData) &&\
            (CANTP_TRUE == ptrStaticTxNSdu->InTxPduwithMetaDataSts))
            {
              /* @Trace: CanTp_SUD_API_017 */
              ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] =  ptrMetaData[(uint8)CANTP_ZERO];
            }
            else
            #endif
            {
              /* @Trace: CanTp_SUD_API_018 */
              ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrStaticTxNSdu->NTaOrNAeValue;
            }
            #else
            ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrStaticTxNSdu->NTaOrNAeValue;
            #endif /* (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
            break;
          #endif /* End of #if (STD_ON == CANTP_TX_MIXED_ADDRESS) */
          #if (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)
          /* Normal fixed (29bit) address shall consume SOURCE_ADDRESS_16 and
          * TARGET_ADDRESS_16 from Upper layer.
          * Produces the CAN_ID_32 of Lo layer from MetaData which got from
          * Upper layer. If Generic connection is disable CanTp shall use
          * local configured N_Ta for transmit.
          */
          case (uint8)CANTP_NORMALFIXED_ADDRESS:
          
            /* @Trace: CanTp_SUD_API_019 */
            #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
            /* MetaData shall be used to forward to Lo layer
              * with normal fixed addressing. */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;

            #if (STD_ON == CANTP_TX_NSDU_METADATA)
            if((NULL_PTR != ptrMetaData) &&\
            (CANTP_TRUE == ptrStaticTxNSdu->InTxPduwithMetaDataSts))
            {
              /* @Trace: CanTp_SUD_API_020 */
              /* Copy N_SA from Upper metaData to local */
              wordAccess.WholeWord = (uint16)*((uint16*)&ptrMetaData[(uint8)CANTP_ZERO]);

              /* Assign N_SA to the LoMetaData
                * to produce CAN_ID_32 for transmit */
              ptrChannelRam->LoMetaData.byte_val.LSByte = wordAccess.byte_val.LSByte;

              ptrMetaData += (uint8)CANTP_TWO;

              /* Copy N_TA from Upper metaData to local */
              wordAccess.WholeWord = (uint16)*((uint16*)&ptrMetaData[(uint8)CANTP_ZERO]);

              /* Assign N_TA to the LoMetaData
                * to produce CAN_ID_32 for transmit
                * */
              ptrChannelRam->LoMetaData.byte_val.Byte_1 = wordAccess.byte_val.LSByte;
            }
            else
            #endif /* (STD_ON == CANTP_TX_NSDU_METADATA) */
            {
              /* @Trace: CanTp_SUD_API_021 */
              /* Use default configuration value */
              ptrChannelRam->LoMetaData.byte_val.LSByte = ptrStaticTxNSdu->TxNSa;
              /*ECUC_CanTp_00139: CanTpNTa is not mandatory for TxNSdu
                * When DynIdSupport is enabled and GenericConnectionSupport is not enabled */
              ptrChannelRam->LoMetaData.byte_val.Byte_1 = ptrStaticTxNSdu->TxNTa;
            }
            #else /* #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
            /* Generic connection disable, CanTp shall provide N_SA, N_Ta
              * This case for one specific connection */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;
            ptrChannelRam->LoMetaData.byte_val.LSByte = ptrStaticTxNSdu->TxNSa;
            ptrChannelRam->LoMetaData.byte_val.Byte_1 = ptrStaticTxNSdu->TxNTa;
            #endif /* #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
            /* PDU Format:Normal Fixed Addressing */
            /* Produces the two high byte in CAN_ID_32 */
            if ((uint8)CANTP_PHYSICAL_ADDRESS == ptrStaticTxNSdu->TaType)
            {
              /* @Trace: CanTp_SUD_API_022 */
              ptrChannelRam->LoMetaData.byte_val.MSByte =\
                        (uint8)CANTP_HIGHESTBYTE_CANID32;
              ptrChannelRam->LoMetaData.byte_val.Byte_2 =\
                        (uint8)CANTP_PHYSICAL_CANID_NORMALFIXED;
            }
            else
            {
              /* @Trace: CanTp_SUD_API_023 */
              ptrChannelRam->LoMetaData.byte_val.MSByte =\
                        (uint8)CANTP_HIGHESTBYTE_CANID32;
              ptrChannelRam->LoMetaData.byte_val.Byte_2 =\
                        (uint8)CANTP_FUNCTIONAL_CANID_NORMALFIXED;
            }
            break;
          #endif /* #if (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) */
          #if (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS)
          /* Mixed (29bit) address shall consume SOURCE_ADDRESS_16 ,
          * TARGET_ADDRESS_16 and ADDRESS_EXTENSION from Upper layer.
          * Produces the CAN_ID_32 of Lo layer from MetaData which got from
          * Upper layer. If Generic connection is disable CanTp shall use
          * local configured N_Ta for transmit.
          */
        case (uint8)CANTP_MIXED29BIT_ADDRESS:
          
            /* @Trace: CanTp_SUD_API_024 */
            #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
            /* MetaData shall be used to forward to Lo layer
              * with normal fixed addressing. */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;

            #if (STD_ON == CANTP_TX_NSDU_METADATA)
            if((NULL_PTR != ptrMetaData) &&\
            (CANTP_TRUE == ptrStaticTxNSdu->InTxPduwithMetaDataSts))
            {
              /* @Trace: CanTp_SUD_API_025 */
              /* Copy N_SA from Upper metaData to local */
              wordAccess.WholeWord = (uint16)*((uint16*)&ptrMetaData[(uint8)CANTP_ZERO]);

              /* Assign N_SA to the LoMetaData
                * to produce CAN_ID_32 for transmit */
              ptrChannelRam->LoMetaData.byte_val.LSByte = wordAccess.byte_val.LSByte;

              ptrMetaData += CANTP_TWO;

              /* Copy N_TA from Upper metaData to local */
              wordAccess.WholeWord = (uint16)*((uint16*)&ptrMetaData[(uint8)CANTP_ZERO]);

              /* Assign N_TA to the LoMetaData
                * to produce CAN_ID_32 for transmit
                * */
              ptrChannelRam->LoMetaData.byte_val.Byte_1 = wordAccess.byte_val.LSByte;

              /* Copy N_Ae to the first byte of buffer */
              ptrMetaData += CANTP_TWO;
              ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrMetaData[(uint8)CANTP_ZERO];
            }
            else
            #endif /* (STD_ON == CANTP_TX_NSDU_METADATA) */
            {
              /* @Trace: CanTp_SUD_API_026 */
              /* Use default configuration set */
              ptrChannelRam->LoMetaData.byte_val.LSByte = ptrStaticTxNSdu->TxNSa;
              ptrChannelRam->LoMetaData.byte_val.Byte_1 = ptrStaticTxNSdu->TxNTa;
              ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrStaticTxNSdu->NTaOrNAeValue;
            }
            #else /* #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
            /* Generic connection disable, CanTp shall provide N_SA, N_Ta
              * This case for one specific connection */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;
            ptrChannelRam->LoMetaData.byte_val.LSByte = ptrStaticTxNSdu->TxNSa;
            ptrChannelRam->LoMetaData.byte_val.Byte_1 = ptrStaticTxNSdu->TxNTa;
            ptrChannelRam->DataBuffer[(uint8)CANTP_ZERO] = ptrStaticTxNSdu->NTaOrNAeValue;
            #endif /* #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */

            /* Produces the two high byte in CAN_ID_32 */
            if ((uint8)CANTP_PHYSICAL_ADDRESS == ptrStaticTxNSdu->TaType)
            {
              /* @Trace: CanTp_SUD_API_027 */
              ptrChannelRam->LoMetaData.byte_val.MSByte =\
                        (uint8)CANTP_HIGHESTBYTE_CANID32;
              ptrChannelRam->LoMetaData.byte_val.Byte_2 =\
                        (uint8)CANTP_PHYSICAL_CANID_MIXED29;
            }
            else
            {
              /* @Trace: CanTp_SUD_API_028 */
              ptrChannelRam->LoMetaData.byte_val.MSByte =\
                        (uint8)CANTP_HIGHESTBYTE_CANID32;
              ptrChannelRam->LoMetaData.byte_val.Byte_2 =\
                        (uint8)CANTP_FUNCTIONAL_CANID_MIXED29;
            }
            break;
          #endif /* #if (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) */
          default: /* (uint8)CANTP_STANDARD_ADDRESS */
            #if ((STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) && (STD_ON == CANTP_TX_NSDU_METADATA))
            CANTP_UNUSED(ptrMetaData);
            #endif
            break;
        }
        #else
          #if ((STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) && (STD_ON == CANTP_TX_NSDU_METADATA))
          CANTP_UNUSED(ptrMetaData);
          #endif
        #endif    
        #endif /* End of #ifndef CANTP_DYNID_SUPPORT */

         /* @Trace: SWS_CanTp_00231 */
         /* If data does fit into the associated N-PDU,
         * the function CanTp_Transmit() shall send a SF N-PDU.
         * In case of Single Frame and CAN_DL <= 8 */
        /* @Trace: SWS_CanTp_00225 */
        /* For specific connections that do not use MetaData,
         * the function CanTp_Transmit shall only use the full SduLength information and
         * shall not use the available N-SDU data buffer in order to prepare Single Frame or First Frame PCI */
        if ((dataLen.WholeLong <= ((uint32)txDataMaxLength - (uint32)CANTP_ONE - (uint32)bytePosition)) &&\
        ((uint32)txDataMaxLength <= (uint32)CANTP_EIGHT))
        {
          /* @Trace: CanTp_SUD_API_029 */
          /* Set the PCI byte for single frame (SF) */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.LSByte;
          
          /* Set the frame type as SF */
          ptrChannelRam->FrameType = (uint8)CANTP_SF_PCI;
        }
        #if ((STD_ON == CANTP_FD_SUPPORT) && (STD_ON == CANTP_TX_DL_GREATER_THAN_8))
        /* In case of Single Frame and CAN_DL > 8 only for CAN-FD */
        else if (dataLen.WholeLong <=
          ((uint32)txDataMaxLength - (uint32)CANTP_TWO - (uint32)bytePosition))
        {
          /* @Trace: CanTp_SUD_API_030 */
          /* Set the PCI byte#1 for single frame (SF) */
          ptrChannelRam->DataBuffer[bytePosition] = (uint8)CANTP_FD_SF_FIRST;
          bytePosition++;
            /* Set the PCI byte#2 for single frame (SF) */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.LSByte;

            /* Set the frame type as SF */
          ptrChannelRam->FrameType = (uint8)CANTP_SF_PCI;
        }
        #endif /* End of #if (STD_ON == CANTP_FD_SUPPORT) */

        /* @Trace: SWS_CanTp_00232 */
        /* If data does not fit into the associated N-PDU
         * In case of First Frame and FF_DL > 4095*/
        
        else if ( dataLen.WholeLong > (uint32)CANTP_FOURZERONINEFIVE )
        {
          /* @Trace: CanTp_SUD_API_031 */
          /* Set the PCI byte#1 for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] = (uint8)CANTP_FD_FF_FIRST;
          bytePosition++;
          /* Set the PCI byte#2 for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] = (uint8)CANTP_FD_FF_SECOND;
          bytePosition++;
          /* Set the PCI byte#3 for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.MSByte;
          bytePosition++;
          /* Set the PCI byte#4 for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.Byte_2;
          bytePosition++;
          /* Set the PCI byte#5 for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.Byte_1;
          bytePosition++;
          /* Set the PCI byte#6 for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.LSByte;

          #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
          /* Initialize frame counter */
          ptrChannelRam->FrameCounter = (uint8)CANTP_ZERO;
          #endif

          /* Set the frame type as FF */
          ptrChannelRam->FrameType = (uint8)CANTP_FF_PCI;
        }
        /* In case of First Frame and FF_DL <= 4095*/
        else
        {
          /* @Trace: CanTp_SUD_API_032 */
          /* Set the PCI byte for first frame (FF) */
          ptrChannelRam->DataBuffer[bytePosition] =
          (((uint8)CANTP_FF_PCI) | (dataLen.byte_val.Byte_1));
          bytePosition++;
          /* Set the byte2 in the first frame */
          ptrChannelRam->DataBuffer[bytePosition] = dataLen.byte_val.LSByte;

          #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
          /* Initialize frame counter */
          ptrChannelRam->FrameCounter = (uint8)CANTP_ZERO;
          #endif

          /* Set the frame type as FF */
          ptrChannelRam->FrameType = (uint8)CANTP_FF_PCI;
        }
        /* Set the Data Byte index after proceeded N-PCI */
        ptrChannelRam->LocalDataByteIndex = bytePosition + (uint8)CANTP_ONE;

        /* Set the channel buffer state to request the buffer */
        ptrChannelRam->BufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;

        /* Set the new frame flag status as start of Transmission of FF or SF */
        ptrChannelRam->NewFrameFlag = (uint8)CANTP_TX_SFORFF;

        /* Set return value (uint8) E_OK */
        returnValue = E_OK;
      } /* No DLC error */
    } /* Tx channel is in WAIT state */
  } /* No development errors occurred */
  /* @Trace: SWS_CanTp_00177 */
  /* @Trace: CanTp_SUD_API_361 */
  /* After the transmit request was accepted, the CanTp module
   *shall notify its upper layer if the N-SDU transfer is fully processed */
  /* @Trace: SWS_CanTp_00123 */
  /* @Trace: CanTp_SUD_API_362 */
  /* CanTp_Transmit() function returns E_NOT_OK when channel state is in use */
  return (returnValue);
} /* End of CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType,
   * AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (CANTP_TX_NSDU == STD_ON) */

/*******************************************************************************
** Function Name        : CanTp_TxDetCheck                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service will check the for any error in the    **
**                        input parameters passed to CanTp_Transmit API       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : txSduId                                             **
**                        ptrTxInfo                                           **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :    CanTp_TxSduStatic       **
**                                                    Cantp_Max_Tx_Sduid      **
**                        Function(s) invoked    : Det_ReportError            **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* CanTp return the value E_NOT_OK and report to DET */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxDetCheck(PduIdType txSduId,
  P2CONST( PduInfoType, AUTOMATIC, CANTP_CONST) ptrTxInfo)
{
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSduStatic;
  uint8 bytePos;
  PduLengthType sduLength;
  #endif
  PduLengthType pduLength;
  Std_ReturnType returnValue;
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  pduLength = (PduLengthType)CANTP_ZERO;
  #endif
  /* @Trace: SWS_CanTp_00008 */
  /* Initialize return status with (uint8) E_OK */
  returnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  /* If support Postbuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the pointer to current TxNsdu */
  ptrTxNSduStatic = &(Variant_Select->PtrTxNSduStatic)[txSduId];
  #else
  /* Get the pointer to current TxNsdu */
  ptrTxNSduStatic = &CanTp_TxSduStatic[txSduId];
  #endif
  #endif
  /* @Trace: SWS_CanTp_00199 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  /* Check if CanTp is not Initialized */
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* @Trace: CanTp_SUD_API_033 */
    /* Report to DET */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMIT_SID, CANTP_E_UNINIT);

    /* Set return value (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_InitStatus) */

  /* Check if Tx SduId is greater than maximum value */
  if ((uint16)txSduId > CANTP_MAX_TX_SDUID)
  {
    /* @Trace: CanTp_SUD_API_034 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMIT_SID, CANTP_E_PARAM_ID);

    /* Set return value (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if ((uint16)txSduId > CANTP_MAX_TX_SDUID) */

  /* @Trace: SWS_CanTp_00321 */
  /* Check if the input parameter pointer is a NULL pointer */
  if (NULL_PTR == ptrTxInfo)
  {
    /* @Trace: CanTp_SUD_API_035 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMIT_SID, CANTP_E_PARAM_POINTER);
    /* Set return value (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (NULL_PTR == ptrTxInfo) */
  else
  {
	  /* @Trace: CanTp_SUD_API_036 */
    if ((Std_ReturnType)E_OK == returnValue)
    {
      /* @Trace: CanTp_SUD_API_037 */
      /* Get the complete PDU length */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "The value had been checked by lower modules before being passed through the API" */
      pduLength = ptrTxInfo->SduLength;

      /* Check if the data length is invalid */
      if ((PduLengthType)CANTP_ZERO == pduLength)
      {
        /* Report to DET */
        /* @Trace: SWS_CanTp_00352 */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TRANSMIT_SID, CANTP_E_PADDING);

        /* Set return value (uint8) E_NOT_OK */
        returnValue = (Std_ReturnType)E_NOT_OK;
      } /* End of if (CANTP_ZERO == pduLength) */
    } /* End of if ((uint8)E_OK == returnValue) */
  } /* End of else */
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)

  /* Check if no DET error occurred */
  if ((Std_ReturnType)E_OK == returnValue)
  {
    /* @Trace: CanTp_SUD_API_038 */
    /* Check if the TxNsdu is configured for functional addressing */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == ptrTxNSduStatic->TaType)
    {
      /* @Trace: CanTp_SUD_API_039 */
      #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS)||(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))

      /* Get the N_PCI position if transmit NSDU is configured as Extended */
      bytePos = CanTp_BytePos[ptrTxNSduStatic->AddressingMode];
      #else

      /* Initialise the Addressing format value as Standard */
      bytePos = (uint8)CANTP_ZERO;
      #endif
      /* SRS_ES95486_02E_SWP_00047 Functional addressing (1-n communication)shall only be supported for Single Frame */
      /* SWS_CanTp_00092 */
      /* The CanTp module shall provide 1 to n communication (i.e. functional addressing), /
       in the form of functionality to SF N-PDUs (and only SF N-SDU) */
      /* Check if the requested SduLength is not fit into a single frame */
      #if (STD_ON == CANTP_TX_DL_GREATER_THAN_8)
      if (ptrTxNSduStatic->TxSduMaxLength > (uint8)CANTP_EIGHT)
      {
        /* @Trace: CanTp_SUD_API_040 */
        sduLength = ((PduLengthType)ptrTxNSduStatic->TxSduMaxLength - CANTP_TWO - bytePos);
      }
      else
      #endif
      {
        /* @Trace: CanTp_SUD_API_041 */
        sduLength = ((PduLengthType)ptrTxNSduStatic->TxSduMaxLength - CANTP_ONE - bytePos);
      } /* End of if (ptrTxNSduStatic->TxSduMaxLength > (uint8)CANTP_EIGHT) */

      /* @Trace: SWS_CanTp_00093 */
      /* If a multiple segmented session occurs
       * (on both receiver and sender side) with a handle whose communication
       * type is functional, the CanTp module shall reject the request and
       * report the runtime error code CANTP_E_INVALID_TATYPE
       * to the Default Error Tracer. */
      if ((PduLengthType)pduLength > sduLength)
      {
        /* @Trace: CanTp_SUD_API_042 */
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TRANSMIT_SID, CANTP_E_INVALID_TATYPE);
        /* Set return value (uint8) E_NOT_OK */
        returnValue = (Std_ReturnType)E_NOT_OK;
      }
    } /* if(LpTpTxNsdu->TaType == CANTP_FUNCTIONAL_ADDRESS) */
  } /* if(returnValue == (uint8) E_OK) */
  #endif /* #if(CANTP_TX_FUNCTIONAL_ADDRESSING == STD_ON) */

  return (returnValue);
} /* End of CanTp_TxDetCheck(PduIdType txSduId, P2CONST( PduInfoType,
   * AUTOMATIC, CANTP_CONST) ptrTxInfo) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (CANTP_TX_NSDU == STD_ON) && (CANTP_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : CanTp_CancelTransmit                                **
**                                                                            **
** Service ID           : 0x4a                                                **
**                                                                            **
** Description          : This service allows the upper layer to cancel a     **
**                        transmission in progress                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpTxSduId                                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_InitStatus,          **
**                                                 CanTp_TxSduStatic,         **
**                                                 CanTp_ChannelRam,          **
**                                                 CANTP_CHANNEL_ID           **
**                                                 Cantp_Max_Tx_Sduid         **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_TransmissionComplete **
*******************************************************************************/
#if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TC))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace:  SRS_Can_01076 */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmit(PduIdType CanTpTxSduId)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu;
  CanTp_ChannelType channel;
  Std_ReturnType returnValue;

  /* Initialize return status with (uint8) E_OK */
  returnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* @Trace: SWS_CanTp_00254 */
  /* Check the CanTpTxSduId is valid */
  if (CanTpTxSduId > (PduIdType)CANTP_MAX_TX_SDUID)
  {
    /* @Trace: CanTp_SUD_API_043 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELTRANSMIT_SID, CANTP_E_PARAM_ID);

    /* Set return value (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CanTpTxSduId > (PduIdType)CANTP_MAX_TX_SDUID) */
  #endif

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Initialization local pointer */
  ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[CanTpTxSduId];
  #else
  /* Initialization local pointer */
  ptrTxNSdu = &CanTp_TxSduStatic[CanTpTxSduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  if (E_OK == returnValue)
  {
    /* @Trace: CanTp_SUD_API_045 */
    /* @Trace: SWS_CanTp_00242 */
    /* Only perform cancel transmit if TxSdu activated the TC */
    #if (STD_OFF == CANTP_TC_ALL)
    if (CANTP_FALSE != ptrTxNSdu->TxCancelTransmitAct)
    #endif
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      /* @Trace: CanTp_SUD_API_046 */
      /* @Trace: SWS_CanTp_00199 */
      /* Call CanTp_Init before using the CanTp module for further processing */
      /* Check if CanTp is not Initialized */
      if (CANTP_FALSE == CanTp_InitStatus)
      {
        /* Report to DET */
        /* @Trace: CanTp_SUD_API_186 */
        /* @Trace: SWS_CanTp_00031 */
        /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_CANCELTRANSMIT_SID, CANTP_E_UNINIT);

        /* Set return value (uint8) E_NOT_OK */
        returnValue = (Std_ReturnType)E_NOT_OK;
      } /* End of if (CANTP_FALSE == CanTp_InitStatus) */
      #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */

      /* Check if any DET error is occurred */
      if ((Std_ReturnType)E_OK == returnValue)
      {
        /* @Trace: CanTp_SUD_API_047 */
        /* Get the connection channel structure address */
        channel = ptrTxNSdu->ChannelId;

        /* Load the address of the channel RAM */
        ptrChannelRam = &CanTp_ChannelTxRam[CanTp_ChannelMapping[channel]];

        /* Check requested PduId is Active PduId */
        if (ptrChannelRam->ActivePduId == CanTpTxSduId)
        {
          /* @Trace: CanTp_SUD_API_048 */
          /* @Trace: SWS_CanTp_00254 */
          /* Check current state is not transmit state */
          if ((uint8)CANTP_WAIT == ptrChannelRam->ChannelState)
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            /* @Trace: CanTp_SUD_API_049 */
            /* Report to DET */
            (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
              CANTP_CANCELTRANSMIT_SID, CANTP_E_OPER_NOT_SUPPORTED);
            #endif
            /* Set return value (uint8) E_NOT_OK */
            returnValue = (Std_ReturnType)E_NOT_OK;
          }
          /* Check currently SF transmission is in progress */
          else if ((uint8)CANTP_SF_PCI == ptrChannelRam->FrameType)
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            /* @Trace: CanTp_SUD_API_050 */
            /* Report to DET */
            (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
              CANTP_CANCELTRANSMIT_SID, CANTP_E_OPER_NOT_SUPPORTED);
            #endif
            /* Set return value (uint8) E_NOT_OK */
            returnValue = (Std_ReturnType)E_NOT_OK;
          }
          else
          { 
            /* @Trace: CanTp_SUD_API_051 */  
            /* returnValue = E_OK */
            /* @Trace: SWS_CanTp_00255 */
            /* Call the PduR_CanTpTxConfirmation with notification result E_NOT_OK */
            /* @Trace: SWS_CanTp_00243 */
            /* After the call of the service CanTp_CancelTransmit(), the transfer on this connection shall be aborted */
            CanTp_TransmissionComplete(ptrChannelRam, E_NOT_OK);
          }
        } /* @ if(CanTpTxSduId == ptrChannelRam->ActivePduId) */
        else
        {
          #if (STD_ON == CANTP_DEV_ERROR_DETECT)
          /* @Trace: CanTp_SUD_API_052 */
          /* @Trace: SWS_CanTp_00254 */
          /* Report to DET */
          (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_CANCELTRANSMIT_SID, CANTP_E_OPER_NOT_SUPPORTED);
          #endif
          /* Set return value (uint8) E_NOT_OK */
          returnValue = (Std_ReturnType)E_NOT_OK;
        } /* End of else */
      } /* Check if any DET error is occurred */
    }
    #if (STD_OFF == CANTP_TC_ALL)
    else    
    {
      /* @Trace: CanTp_SUD_API_235 */
      returnValue = E_NOT_OK;
    } /*End of (CANTP_FALSE != ptrTxNSdu->TxCancelTransmitAct) */
    #endif /* #if (STD_OFF == CANTP_TC_ALL) */
  } /* End of (E_OK == returnValue) */
  /* @Trace: SWS_CanTp_00256 */
  /* @Trace: CanTp_SUD_API_044 */
  /* The CanTp shall abort the transmission of the current N-SDU
   * if the service returns E_OK */
  return (returnValue);
} /* End of CanTp_CancelTransmit(PduIdType CanTpTxSduId) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((CANTP_TX_NSDU == STD_ON) && (CANTP_TC == STD_ON)) */

/*******************************************************************************
** Function Name        : CanTp_CancelReceive                                 **
**                                                                            **
** Service ID           : 0x4c                                                **
**                                                                            **
** Description          : This service allows the upper layer to cancel a     **
**                        reception in progress                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpRxSduId                                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_InitStatus,          **
**                                                 CanTp_RxSduStatic,         **
**                                                 CanTp_GaaChannelMode,      **
**                                                 CanTp_ChannelRam           **
**                                                 CANTP_CHANNEL_ID           **
**                                                 CanTp_MaxCanTpRxSduId      **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_ReceptionComplete    **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01081 */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceive(PduIdType CanTpRxSduId)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu;
  CanTp_ChannelType channel;
  Std_ReturnType returnValue;
  uint8 bytePos;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the pointer to current RxNsdu */
  ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[CanTpRxSduId];
  #else
  /* Get the pointer to current RxNsdu */
  ptrRxNSdu = &CanTp_RxSduStatic[CanTpRxSduId];
  #endif

  /* Initialize return status with (uint8) E_OK */
  returnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* @Trace: SWS_CanTp_00199 */
  /* @Trace: CanTp_SUD_API_239 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  /* Check if CanTp is not Initialized */
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* @Trace: CanTp_SUD_API_053 */
    /* Report to DET */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELRECEIVE_SID, CANTP_E_UNINIT);

    /* Set return value (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_InitStatus) */

  /* @Trace: SWS_CanTp_00260 */
  /* Check the validity of CanTpRxSduId */
  if (CanTpRxSduId > (PduIdType)CANTP_MAX_RX_SDUID)
  {
    /* @Trace: CanTp_SUD_API_054 */
    /* @Trace: SWS_CanTp_00260 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELRECEIVE_SID, CANTP_E_PARAM_ID);

    /* Set return value (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CanTpRxSduId > (PduIdType)CANTP_MAX_RX_SDUID) */
  else
  {
    /* @Trace: CanTp_SUD_API_055 */
    /* If the RxNsdu supports Functional addressing */
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType)
    {
      /* Report to DET */
      /* @Trace: SWS_CanTp_00260 */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CANCELRECEIVE_SID, CANTP_E_PARAM_ID);
      /* Set return value (uint8) E_NOT_OK */
      returnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType) */
    #endif /* #if(STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)  */
  } /* End of else */

  /* Check if any DET error is occurred */
  if ((Std_ReturnType)E_OK == returnValue)
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanTp_SUD_API_056 */
    /* Get the connection channel structure address */
    channel = ptrRxNSdu->ChannelId;
    
    /* Assign the channel ram to local pointer by channel value */
    ptrChannelRam = &CanTp_ChannelRxRam[CanTp_ChannelMapping[channel]];

    /* @Trace: SWS_CanTp_00260 */
    /* Check requested PduId is Active PduId */
    if (CanTpRxSduId == ptrChannelRam->ActivePduId)
    {
      /* @Trace: CanTp_SUD_API_002 */
      if ((uint8)CANTP_WAIT == ptrChannelRam->ChannelState)
      {
        #if (STD_ON == CANTP_DEV_ERROR_DETECT)
        /* @Trace: CanTp_SUD_API_058 */
        /* @Trace: SWS_CanTp_00260 */
        /* Report to DET */
        (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_CANCELRECEIVE_SID, CANTP_E_OPER_NOT_SUPPORTED);

        /* Set return value (uint8) E_NOT_OK */
        returnValue = (Std_ReturnType)E_NOT_OK;
        #endif
      } /* End of if (CANTP_WAIT == ptrChannelRam->ChannelState) */
      else
      {
        #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED_ADDRESS))
        /* @Trace: CanTp_SUD_API_059 */
        /* Get the N_PCI position if transmit NSDU is configured as Extended */
        bytePos = CanTp_BytePos[ptrRxNSdu->AddressingMode];
        #else

        /* Initialise the Addressing format value as Standard */
        bytePos = (uint8)CANTP_ZERO;
        #endif

        /* @Trace: SWS_CanTp_00262 */
        /* Check currently SF reception is in progress */
        if ((uint8)CANTP_SF_PCI == ptrChannelRam->FrameType)
        {
          /* @Trace: CanTp_SUD_API_060 */
          /* Set return value (uint8) E_NOT_OK */
          returnValue = (Std_ReturnType)E_NOT_OK;
        }
        /* Check whether last consecutive frame of the N-SDU reception in
         * progress */
        else if (ptrChannelRam->ByteCounter <=
                 ((uint32)CANTP_SEVEN - (uint32)bytePos))
        {
          /* @Trace: CanTp_SUD_API_061 */
          /* Set return value (uint8) E_NOT_OK */
          returnValue = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: CanTp_SUD_API_062 */
          /* @Trace: SWS_CanTp_00263 */ 
          /* Call the PduR_CanTpRxIndication with notification result E_NOT_OK */
          /* Process the reception complete function */
          CanTp_ReceptionComplete(ptrChannelRam,
            (CanTp_NotifResultType)E_NOT_OK);
        }
      } /* End of else */
    } /* Check requested PduId is Active PduId */
    else
    {
      /* @Trace: CanTp_SUD_API_063 */
      /* @Trace: SWS_CanTp_00352 */
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CANCELRECEIVE_SID, CANTP_E_OPER_NOT_SUPPORTED);

      /* Set return value (uint8) E_NOT_OK */
      returnValue = (Std_ReturnType)E_NOT_OK;
      #endif
    } /* End of else */
  } /* Check if any DET error is occurred */

  /* @Trace: SWS_CanTp_00261 */ 
  /* @Trace: CanTp_SUD_API_363 */
  /* The CanTp shall abort the reception of the
   * current N-SDU if the service returns E_OK. */
  return (returnValue);
} /* End of CanTp_CancelReceive(PduIdType CanTpRxSduId) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (CANTP_RX_NSDU == STD_ON) */

/*******************************************************************************
** Function Name        : CanTp_MainFunction                                  **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : The main function for scheduling the CanTp          **
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
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_InitStatus           **
**                                                 CanTp_ChannelRam,          **
**                                                 CanTp_StMinTimers,         **
**                                                 CanTp_Timers,              **
**                                                 CanTp_TxSduStatic          **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_RequestCopyTxData    **
**                                                 CanTp_RequestRxBuffer      **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01066 SRS_Can_01116 SRS_Can_01081 SRS_BSW_00424 SRS_BSW_00373 SRS_BSW_00406 */
FUNC(void, CANTP_CODE) CanTp_MainFunction(void)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelTxRam;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRxRam;
  #if (STD_ON == CANTP_TX_NSDU)
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrStMinTimer;
  uint16 timerValue;
  #endif
  uint8 rxTxInstances;
  
  /* @Trace: CanTp_SUD_API_064 */
  /* @Trace: SWS_CanTp_00199 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  /* Check if CanTp is not Initialized */
  if (CANTP_TRUE == CanTp_InitStatus)
  {
    /* @Trace: CanTp_SUD_API_259 */ 
    /* Get the address of first channel Ram */
    ptrChannelTxRam = &CanTp_ChannelTxRam[CANTP_ZERO];
    ptrChannelRxRam = &CanTp_ChannelRxRam[CANTP_ZERO];
    #if (STD_ON == CANTP_TX_NSDU)
    /* @Trace: SWS_CanTp_00164 */
    /* The main function for scheduling the CANTP */
    /* Get the Stmin timer start address */
    ptrStMinTimer = &CanTp_StMinTimers[CANTP_ZERO];
    #endif

    /* Initialize channel count equal to zero */
    rxTxInstances = (uint8)CANTP_ZERO;
    /* @Trace: SWS_CanTp_00096 */
    /* The CanTp module shall support several connections simultaneously */
    /* @Trace: SWS_CanTp_00122 */
    /* Each connection channel is independent of the other connection channels.
     * This means that a connection channel uses its own resources, such as internal buffer, timer, or state machine.
     * Loop for all channels */
    
    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    while (rxTxInstances < (uint8)CanTp_NumOfChannel)
    #else
    while (rxTxInstances < (uint8)CANTP_TOTAL_RX_TX_CHANNELS)
    #endif /* End of If (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    {
      /* Check if the channel is not in IDLE state */
      if (ptrChannelTxRam->ChannelState != (uint8)CANTP_WAIT)     
      {
        #if (STD_ON == CANTP_TX_NSDU)
        /* @Trace: SWS_CanTp_00184 */
        /* If the PduR_CanTpCopyTxData() function returns BUFREQ_E_BUSY, the CanTp module shall later
         * (implementation specific) retry to copy the data */
    	  /* @Trace: CanTp_SUD_API_066 */
        if ((uint8)CANTP_TX_NOTRDY_INITREQ == ptrChannelTxRam->BufferState)
        {
          /* @Trace: CanTp_SUD_API_253 */
          /* Request upper layer Copy Tx Data */
          CanTp_RequestCopyTxData(ptrChannelTxRam);
        }
        /* Check if TxNsdu is configured */
        /* @Trace: CanTp_SUD_API_065 */
		    CanTp_TimeoutProcessing(rxTxInstances);
          timerValue = (uint16)(*ptrStMinTimer);
          /* Check if the STmin timer is running */
          /* @Trace: CanTp_SUD_API_069 */
          if (timerValue != (uint16)CANTP_ZERO)
          {
            /* @Trace: CanTp_SUD_API_264 */
            /* Decrement the STmin timer */
            timerValue--;

            /* Update the timer variable */
            SchM_Enter_CanTp_TIMER_PROTECTION();
            *ptrStMinTimer = (uint8)timerValue;
            SchM_Exit_CanTp_TIMER_PROTECTION();
          } /* End of if (timerValue != CANTP_ZERO) */

          /* Check if the STmin timer is expired and buffer is available */
          if ((timerValue == (uint16)CANTP_ZERO) &&
              (ptrChannelTxRam->BufferState == (uint8)CANTP_TX_RDY))
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            /* @Trace: CanTp_SUD_API_070 */
            if(ptrChannelTxRam->ActivePduId > CANTP_MAX_TX_SDUID)
            {
              /* @Trace: CanTp_SUD_API_071 */
              /* @Trace: SWS_CanTp_00293 */
              /* Report to DET */
              (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
                  CANTP_MAINFUNCTION_SID, CANTP_E_INVALID_TX_ID);
            }
            else
            #endif
            {
              /* @Trace: CanTp_SUD_API_072 */
              /* If support PostBuild */
              #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
              /* Get the TxNSdu structure address */
              ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[ptrChannelTxRam->ActivePduId];
              #else
              /* Get the TxNSdu structure address */
              ptrTxNSdu = &CanTp_TxSduStatic[ptrChannelTxRam->ActivePduId];
              #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

              /* Transmit the data to lower layer */
              CanTp_CanIfTransmit(ptrTxNSdu);
            }
          } /* End of if ((CANTP_ZERO == timerValue) && */
        #endif /* End of if (STD_ON == CANTP_TX_NSDU) */
      } /* Channel is not in IDLE state */
      
      if (ptrChannelRxRam->ChannelState != (uint8)CANTP_WAIT)
      {
         #if (STD_ON == CANTP_RX_NSDU)
        /*
         * Check if receive buffer needs to be requested
         * Check if the FC confirmation is not awaited
         */
        if ((ptrChannelRxRam->BufferState == (uint8)CANTP_RX_NOTRDY_INITREQ) &&
            (ptrChannelRxRam->TxConfirmState != (uint8)CANTP_FC_TX_CONF))
        {
          /* @Trace: CanTp_SUD_API_067 */
          /* Request buffer from upper layer and Copy Rx Data */
          CanTp_RequestRxBuffer(ptrChannelRxRam);
        }
        #endif /* End of if (CANTP_RX_NSDU == STD_ON) */ 
		    CanTp_TimeoutProcessing(rxTxInstances);
      }
      /* Go to the next RX or TX NSDU */
      /*  polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation */
      ptrChannelTxRam++;
      ptrChannelRxRam++;
      /* by JSLim 2013.01.03 -- [Bug#413]Fixed : Multiple Channel bug */

      #if(CANTP_TX_NSDU == STD_ON)
      ptrStMinTimer++;
      #endif
      /*  polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation */
      /* Go to the next RX or TX NSDU */
      rxTxInstances++;
     }
  }
  else
  {
	  /* Not do nothing */
  }
} /* End of CanTp_MainFunction(void) */


#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_Getversioninfo                                **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        CanTp module. The version information includes:     **
**                        - Module Id                                         **
**                        - Vendor Id                                         **
**                        - Vendor specific version numbers.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_VERSION_INFO_API)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType,
    AUTOMATIC, CANTP_APPL_DATA) versioninfo)
{
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* @Trace: SWS_CanTp_00319 */
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* @Trace: CanTp_SUD_API_073 */
    /* Report to DET  */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_GETVERSIONINFO_SID, CANTP_E_PARAM_POINTER);
  }
  else
  #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanTp_SUD_API_074 */
    /* Copy the vendor Id */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The pointer versioninfo is checked with the condition if (NULL_PTR == versioninfo) then report Det Error. Thus, The pointer can not NULL or poin to unknown memory because of checked" */
    versioninfo->vendorID = CANTP_VENDOR_ID;

    /* Copy the module Id */
    versioninfo->moduleID = CANTP_MODULE_ID;

    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)CANTP_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)CANTP_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)CANTP_SW_PATCH_VERSION;
  }
} /* End of CanTp_Getversioninfo(P2VAR(Std_versioninfoType, AUTOMATIC,
   * CANTP_APPL_DATA) versioninfo) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_VERSION_INFO_API) */

/*******************************************************************************
** Function Name       : CanTp_ChangeParameter                                **
**                                                                            **
** Service ID          : 0x4b                                                 **
**                                                                            **
** Description         : This service primitive is used to request the change **
**                       of the value of the TP_STMIN or TP_BS                **
**                       parameter. The value is given by value.              **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : id,                                                  **
**                       parameter,                                           **
**                       value                                                **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : (uint8) E_OK                                         **
**                       (uint8) E_NOT_OK                                     **
**                                                                            **
** Preconditions       : The CanTp module must be initialized before this call**
**                                                                            **
** Remarks             : Global Variable(s)     : CanTp_InitStatus,           **
**                                                CanTp_RxSduStatic,          **
**                                                CanTp_GaaChannelMode,       **
**                                                CanTp_ChannelRam,           **
**                                                CanTp_GaaSTminBs            **
**                                                CANTP_CHANNEL_ID            **
**                                                CANTP_MAX_RX_SDUID          **
**                       Function(s) invoked   :  Det_ReportError             **
*******************************************************************************/
#if ((STD_ON == CANTP_CHANGE_PARAMETER_API)\
  && (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id,
  TPParameterType parameter, VAR(uint16, AUTOMATIC) Value)
{
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  CanTp_ChannelType channel;
  Std_ReturnType returnValue;
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  uint8 index;
  #endif
  #endif

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the pointer to current RxNsdu */
  ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[id];
  #else
  /* Get the pointer to current RxNsdu */
  ptrRxNSdu = &CanTp_RxSduStatic[id];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* Initialize return status with (uint8) E_OK */
  returnValue = (Std_ReturnType)E_OK;

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  index = (uint8)CANTP_ZERO;
  #endif
  #endif

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* @Trace: CanTp_SUD_API_075 */
  /* @Trace: SWS_CanTp_00199 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  /* Check whether CanTp module initialization has not been done*/
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* Report to DET  */
    /* @Trace: CanTp_SUD_API_078 */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CHANGEPARAM_SID, CANTP_E_UNINIT);

    /* Set return returnValue (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_InitStatus) */

  /* Check if the parameter is invalid */
  if (((uint8)parameter != CANTP_BS) && ((uint8)parameter != CANTP_STMIN))
  {
    /* Report to DET  */
    /* @Trace: CanTp_SUD_API_076 */
    /* @Trace: SWS_CanTp_00305 */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

    /* Set return returnValue E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (parameter > TP_BS) */

  /* check the validity of rxSduId  */
  if (id > (PduIdType)CANTP_MAX_RX_SDUID)
  {
    /* Report to DET */
    /* @Trace: CanTp_SUD_API_077 */
    /* @Trace: SWS_CanTp_00305 */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

    /* Set return returnValue (uint8) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (id > (PduIdType)CANTP_MAX_RX_SDUID) */
  else
  {
    /* If the RxNsdu supports Functional addressing */
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)

    /* If the RxNsdu supports Functional addressing */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType)
    {
      /* Report to DET */
      /* @Trace: CanTp_SUD_API_079 */
      /* @Trace: SWS_CanTp_00305 */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

      /* Set return returnValue (Std_ReturnType) E_NOT_OK */
      returnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType) */
    #endif /* #if(STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)  */
  } /* End of else */

  /* Check if no Det error detected */
  if ((Std_ReturnType)E_OK == returnValue)
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanTp_SUD_API_080 */
    /* Get the channel ram data structure in to local pointer */
    channel = ptrRxNSdu->ChannelId;
    
    /* Assign the sdu channel ram to local pointer by channel value */
    ptrChannelRam = &CanTp_ChannelRxRam[CanTp_ChannelMapping[channel]];

    /* @Trace: SWS_CanTp_00303 */
    /* Check if the communication is not for reception */
    if ((ptrChannelRam->ChannelState == CANTP_WAIT) ||
         (ptrChannelRam->ActivePduId != id))
    {
      /* @Trace: CanTp_SUD_API_081 */
      /* Check request is for 'TP_STMIN' parameter */
      if (CANTP_STMIN == (uint8)parameter)
      {
        #if (STD_ON == CANTP_DEV_ERROR_DETECT)
        /* @Trace: CanTp_SUD_API_082 */
        /* @Trace: SWS_CanTp_00305 */
        /* Check new Value of the parameter 'CANTP_STMIN' is within a range */
        if (((Value > (uint16)CANTP_STMIN_DIRECT_VALUE_RANGE) &&
             (Value < (uint16)CANTP_STMIN_US_LOW)) || (Value >
                                                       (uint16)
                                                       CANTP_STMIN_US_HIGH))
        {
          /* Report to DET */
          /* @Trace: CanTp_SUD_API_083 */
          (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

          /* Set return Value (Std_ReturnType) E_NOT_OK */
          returnValue = (Std_ReturnType)E_NOT_OK;
        } /*
           * End of if (((Value > CANTP_STMIN_DIRECT_VALUE_RANGE) &&
           * Accept the new Value if it is valid
           */
        
        else
        #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
        {
          /* @Trace: CanTp_SUD_API_084 */
          /* @Trace: SWS_CanTp_00338 */
          /* When CanTp_ChangeParameter is called for an N-SDU with MetaData (indicating a generic connection),
          * the change shall be applied to all generic connections */
          #ifdef CANTP_DYNID_SUPPORT
          #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
          for (index = (uint8)CANTP_ZERO; index < (uint8)CANTP_NO_OF_RXSDUSTATIC; index++)
          {
            /* @Trace: CanTp_SUD_API_365 */
            /* If support PostBuild */
            #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
              (Variant_Select->PtrSTminBs)[index].STMin = (uint8)Value;
            #else
              CanTp_STminBs[index].STMin = (uint8)Value;
            #endif /* End of if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
          }
          #endif
          #else
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          /* Store new CanTp_STMin Value */
          (Variant_Select->PtrSTminBs)[id].STMin = (uint8)Value;
          #else
          /* Store new CanTp_STMin Value */
		  	  CanTp_STminBs[id].STMin = (uint8)Value;
          #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
          #endif
        }
      } /*
         * if(parameter == TP_STMIN)
         * If request is for 'CanTp_BS' parameter
         */
      else
      {
        #if (STD_ON == CANTP_DEV_ERROR_DETECT)
        /* @Trace: CanTp_SUD_API_085 */
        /* @Trace: SWS_CanTp_00305 */
        /* Check the new Value of parameter 'CanTp_BS' is within a range */
        if (Value > (uint16)CANTP_MAX_BS_VAL)
        {
          /* Report to DET  */
          /* @Trace: CanTp_SUD_API_086 */
          (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

          /* Set return returnValue (Std_ReturnType) E_NOT_OK */
          returnValue = (Std_ReturnType)E_NOT_OK;
        } /* if(Value > CANTP_MAX_BS_VAL) */
        else
        #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
        {
          /* @Trace: CanTp_SUD_API_087 */
          /* @Trace: SWS_CanTp_00338 */
          /* When CanTp_ChangeParameter is called for an N-SDU with MetaData (indicating a generic connection),
          * the change shall be applied to all generic connections */
          #ifdef CANTP_DYNID_SUPPORT
          #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
          for (index = (uint8)CANTP_ZERO; index < (uint8)CANTP_NO_OF_RXSDUSTATIC; index++)
          {
            /* If support PostBuild */
            #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
            (Variant_Select->PtrSTminBs)[index].BlockSize = (uint8)Value;
            #else
            CanTp_STminBs[index].BlockSize = (uint8)Value;
            #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
          }
          #endif
          #else
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          /* Store new BS Value */
          (Variant_Select->PtrSTminBs)[id].BlockSize = (uint8)Value;
          #else
          /* Store new BS Value */
          CanTp_STminBs[id].BlockSize = (uint8)Value;
          #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
        #endif
        }
      } /* if(parameter == CANTP_BS) */
    } /*
       * if((ptrChannelRam->ChannelState < CANTP_MAX_TX_STATE) ||...
       * Check change parameter confirmation is enabled
       */
    else
    {
      /* @Trace: CanTp_SUD_API_273 */
      /* @Trace: SWS_CanTp_00304 */
      /* Change of a parameter for an N-SDU that is on process */
      /* Set return returnValue (Std_ReturnType) E_NOT_OK */
      returnValue = (Std_ReturnType)E_NOT_OK;
    }
  } /* if(returnValue = (uint8) (uint8) E_OK) */

  return (returnValue);
} /* End of CanTp_ChangeParameter(PduIdType id, TPParameterType parameter,
   * uint16 Value) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /*   #if(CANTP_CHANGE_PARAMETER_API) */

/*******************************************************************************
** Function Name       : CanTp_ReadParameter                                  **
**                                                                            **
** Service ID          : 0x0b                                                 **
**                                                                            **
** Description         : This service primitive is used to Read               **
**                       the value of the TP_STMIN or TP_BS                   **
**                       parameter. The value is stored in poiner value.      **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : id,                                                  **
**                       parameter,                                           **
**                       Pointer where the parameter LpValue will be provided.**
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : E_OK                                                 **
**                       E_NOT_OK                                             **
**                                                                            **
** Preconditions       : The CanTp module must be initialized before this call**
**                                                                            **
** Remarks             : Global Variable(s)     : CanTp_InitStatus,        **
**                                                CanTp_RxSduStatic,       **
**                                                CanTp_GaaSTminBs            **
**                             CANTP_MAX_RX_SDUID         **
**                       Function(s) invoked    : Det_ReportError             **
*******************************************************************************/
#if ((STD_ON == CANTP_READ_PARAMETER_API)\
  && (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id,
  TPParameterType parameter, P2VAR(uint16, AUTOMATIC, CANTP_APPL_DATA) ptrValue)
{
  #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu;

  /* Initializes the default value */
  ptrRxNSdu = NULL_PTR;
  #endif
  Std_ReturnType returnValue;

  /* Initialize return status with (Std_ReturnType) E_OK */
  returnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* @Trace: CanTp_SUD_API_088 */
  /* @Trace: SWS_CanTp_00199 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  /* Check whether CanTp module initialization has not been done*/
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* Report to DET  */
    /* @Trace: CanTp_SUD_API_286 */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_READPRAM_SID, CANTP_E_UNINIT);

    /* Set return returnValue (Std_ReturnType) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_InitStatus) */

  /* @Trace: SWS_CanTp_00324 */
  /* Check the validity of rxSduId */
  if (id > (PduIdType)CANTP_MAX_RX_SDUID)
  {
    /* Report to DET */
    /* @Trace: CanTp_SUD_API_089 */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_READPRAM_SID, CANTP_E_PARAM_ID);

    /* Set return returnValue (Std_ReturnType) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (id > (PduIdType)CANTP_MAX_RX_SDUID) */
  else if (NULL_PTR == ptrValue)
  {
    /* @Trace: CanTp_SUD_API_090 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_READPRAM_SID, CANTP_E_PARAM_POINTER);

    /* Set return returnValue (Std_ReturnType) E_NOT_OK */
    returnValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* @Trace: CanTp_SUD_API_091 */
    /* If the RxNsdu supports Functional addressing */
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)

    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Get the pointer to current TxNSdu */
    ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[id];
    #else
    /* Get the pointer to current TxNSdu */
    ptrRxNSdu = &CanTp_RxSduStatic[id];
    #endif
    /* If the RxNsdu supports Functional addressing */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType)
    {
      /* Report to DET */
      /* @Trace: CanTp_SUD_API_092 */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_READPRAM_SID, CANTP_E_PARAM_ID);

      /* Set return LpValue (Std_ReturnType) E_NOT_OK */
      returnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType) */
    #endif /* #if(CANTP_RX_FUNCTIONAL_ADDRESSING == STD_ON)  */
  } /* End of else */
  
  /* Check if no Det error detected */
  if ((Std_ReturnType)E_OK == returnValue)
  #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: CanTp_SUD_API_093 */
    /* @Trace: SWS_CanTp_00324 */
    /* Check the validity of parameter */
    if ((uint8)parameter > (uint8)0x01)
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      /* Report to DET  */
      /* @Trace: CanTp_SUD_API_094 */
      (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
              CANTP_READPRAM_SID, CANTP_E_PARAM_ID);
      #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
      /* Set return returnValue E_NOT_OK */
      returnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (parameter > 0x01) */
    /* Check request is for 'TP_STMIN' parameter */
    if ((uint8)parameter == CANTP_STMIN)
    {
      /* @Trace: CanTp_SUD_API_095 */
      /* If support PostBuild */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      /* Store CanTp_STMin Value */
      /* polyspace +4 MISRA2012:D4.14 [Not a defect:Low] "This Value cover by generation" */
      *ptrValue = (uint16)(Variant_Select->PtrSTminBs)[id].STMin;
      #else
      /* Store CanTp_STMin Value */
      *ptrValue = (uint16)CanTp_STminBs[id].STMin;
      #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    } /*
       * if(parameter == CANTP_STMIN)
       * If request is for 'CanTp_BS' parameter
       */
    else
    {
      /* @Trace: CanTp_SUD_API_096 */
      /* If support PostBuild */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      /* Store CanTp_STMinBs Value */
      /* polyspace +4 MISRA2012:D4.14 [Not a defect:Low] "This Value cover by generation" */
      *ptrValue = (uint16)(Variant_Select->PtrSTminBs)[id].BlockSize;
      #else
      /* Store CanTp_STMinBs Value */
      *ptrValue = (uint16)CanTp_STminBs[id].BlockSize;
      #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    } /* if(parameter == CANTP_BS) */
  } /* if(returnValue = E_OK) */
  return (returnValue);
} /* End of CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16
   **LpValue) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /*   #if(CANTP_READ_PARAMETER_API) */

/*******************************************************************************
** Function Name       : CanTp_TimeoutProcessing                              **
**                                                                            **
** Service ID          : NA                                                   **
**                                                                            **
** Description         : This service primitive is used to read/modify        **
**                       the timer                                            **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : ptrChannelRam                                        **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : None                                                 **
**                                                                            **
** Preconditions       : The CanTp module must be initialized before this call**
**                                                                            **
** Remarks             : Global Variable(s)     : CanTp_GaaRxNotifSts         **
**                                                CanTp_GaaTxNotifSts         **
**                       Function(s) invoked    :                             **
**                                          SchM_Exit_CanTp_TIMER_PROTECTION  **
**                                          SchM_Enter_CanTp_TIMER_PROTECTION **
**                                          CanTp_ReceptionComplete           **
**                                          CanTp_TransmissionComplete        **
*******************************************************************************/
/* @Trace: SRS_Can_01081 */
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void,
  CANTP_VAR) CanTp_TimeoutProcessing(VAR(uint8, CANTP_VAR) rxTxInstances)
{
  uint16 LusTimerVal;
  uint8 LucTimer;
  VAR(uint8,AUTOMATIC) channel;
  VAR(uint16, AUTOMATIC) nbrTimer;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelTxRam;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRxRam;
  P2VAR(uint16, AUTOMATIC, CANTP_VAR) ptrTimersLc;
  ptrTimersLc = &CanTp_Timers[rxTxInstances][CANTP_ZERO];
  /* Make number of timers equal to zero */
  LucTimer = (uint8)CANTP_ZERO;

  ptrChannelTxRam = &CanTp_ChannelTxRam[rxTxInstances];
  ptrChannelRxRam = &CanTp_ChannelRxRam[rxTxInstances];
  /* @Trace: CanTp_SUD_API_097 */
  /* Check all the timers of the channel whether it is running */
  SchM_Enter_CanTp_TIMER_PROTECTION();
  do
  {
    /* Get the current timer */
    LusTimerVal = *ptrTimersLc;

    /* Check if the timer is running */
    if (LusTimerVal != (uint8)CANTP_ZERO)
    {
      /* @Trace: CanTp_SUD_API_098 */
      /* Decrement the timer value */
      LusTimerVal--;

      /* Update the timer variable */
      *ptrTimersLc = LusTimerVal;

      /* Check if the timer is expired */
      if ((uint8)CANTP_ZERO == LusTimerVal)
      {
        #if (STD_ON == CANTP_RX_NSDU)
        /* @Trace: CanTp_SUD_API_099 */
        /* Check if the communication is for reception */
        if (LucTimer > (uint8)CANTP_NCS_TIMER)
        {
          /* @Trace: CanTp_SUD_API_357 */
          /* Invoke the reception complete with corresponding result
           * Timer N_Ar -- error result NTFRSLT_E_TIMEOUT_A
           * Timer N_Br -- error result NTFRSLT_E_WFT_OVRN
           * Timer N_Cr -- error result NTFRSLT_E_TIMEOUT_CR
           */
          /* @Trace: SWS_CanTp_00341 */
          /* Send FC(WAIT) when N_Br timeout expires */
          /* @Trace: SWS_CanTp_00311 */
          /* Note: In case of N_Ar timeout occurrence (no confirmation
           * from CAN driver for any of the FC frame sent) the CanTp module
           * shall abort reception and notify the upper layer of this failure
           * by calling the indication function PduR_CanTpRxIndication() with
           * the result E_NOT_OK. */
          /* @Trace: SWS_CanTp_00313 */
          /* Note: In case of N_Cr timeout occurrence the CanTp module shall
           * abort reception and notify the upper layer of this failure by
           * calling the indication function PduR_CanTpRxIndication() with
           * the result E_NOT_OK. */
          if (CANTP_NBR_TIMER != LucTimer)
          {
            /* @Trace: CanTp_SUD_API_100 */
            /* If timer is not Br, then reception is completed */
            CanTp_ReceptionComplete(ptrChannelRxRam,
              CANTP_E_RX_COM);
          }
          else
          {
        	  /* @Trace: CanTp_SUD_API_101 */
        	  if ((uint16)CANTP_ZERO == ptrChannelRxRam->RxWftMax)
            {
              /* @Trace: CanTp_SUD_API_102 */
              CanTp_ReceptionComplete(ptrChannelRxRam,
                CANTP_E_RX_COM);
            }
            else
            {
              /* @Trace: CanTp_SUD_API_103 */
              /* Update the flow status as wait */
              ptrChannelRxRam->FlowStatus = (uint8)CANTP_FS_WT;

              /* Transmit FC if Tx confirmation is not awaited
               * for previous Transmission*/
              if ((uint8)CANTP_TX_CONF_IDLE == ptrChannelRxRam->TxConfirmState)
              {
                /* Transmit the flow control frame */
                CanTp_TransmitFc(ptrChannelRxRam);
              }
              /* If support Postbuild */
              #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
              /* Get the channel according to receive SDU structure */
              /* polyspace-begin RTE:OBAI [Not a defect:Low] "configured memory access index"*/
              channel = (Variant_Select->PtrRxNSduStatic)[ptrChannelRxRam->ActivePduId].ChannelId;
              /* polyspace-end RTE:OBAI [Not a defect:Low] "configured memory access index"*/
              /* Reload the N_Br */
              nbrTimer = (Variant_Select->PtrRxNSduDynamic)[ptrChannelRxRam->ActivePduId].NbrTimeoutValue;
              #else
              /* Get the channel according to receive SDU structure */
              /* polyspace-begin RTE:OBAI [Not a defect:Low] "configured memory access index"*/
              channel = CanTp_RxSduStatic[ptrChannelRxRam->ActivePduId].ChannelId;
              /* polyspace-end RTE:OBAI [Not a defect:Low] "configured memory access index"*/
              /* Reload the N_Br */
              nbrTimer = CanTp_RxSduDynamic[ptrChannelRxRam->ActivePduId].NbrTimeoutValue;
              #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

              CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NBR_TIMER, nbrTimer);

              (ptrChannelRxRam->RxWftMax)--;
            }
          }
        } /* if(LucTimer > (uint8)CANTP_NCS_TIMER  ) */
        #endif /* #if (CANTP_RX_NSDU == STD_ON) */

        #if (STD_ON == CANTP_TX_NSDU)
        /* Communication is for transmission */
        if (LucTimer <= (uint8)CANTP_NCS_TIMER )
        {
          /* @Trace: CanTp_SUD_API_104 */
          /* Invoke the transmission complete with corresponding result
           * Timer N_As -- error result CANTP_E_TX_COM
           * Timer N_Bs -- error result CANTP_E_TX_COM
           * Timer N_Cs -- error result CANTP_E_TX_COM
           */

          /* @Trace: SWS_CanTp_00310 */
           /* In case of N_As timeout occurrence */
           /* @Trace: SWS_CanTp_00280 */
           /* If data is not available within N_Cs timeout */
           /* @Trace: SWS_CanTp_00316 */ 
           /* In case of N_Bs timeout occurrence the CanTp module shall
            * abort transmission of this message */
           /* @Trace: SWS_CanTp_00075 */
           /* When the transmit confirmation is not received after a
            * maximum time (equal to N_As), the CanTp module shall abort the corresponding session */
            /* Transmission is completed */
          CanTp_TransmissionComplete(ptrChannelTxRam, CANTP_E_TX_COM);
        }
        #endif /* #if (CANTP_TX_NSDU == STD_ON) */
      } /* Timer is expired */
    } /* Timer is running */
    /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation */
    ptrTimersLc++;
    /* increment timer count */
    LucTimer++;
  } while (LucTimer < (uint8)CANTP_SIX);
  SchM_Exit_CanTp_TIMER_PROTECTION();
} /* End of CanTp_TimeoutProcessing(P2VAR(CanTp_ChannelRamType, AUTOMATIC, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

