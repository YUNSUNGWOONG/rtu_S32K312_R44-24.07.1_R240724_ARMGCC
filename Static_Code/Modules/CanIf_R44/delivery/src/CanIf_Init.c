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
**  SRC-MODULE: CanIf_Init.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Initialization and version control functionality **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2947                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008                          **
** 1.0.9     03-Oct-2022   HieuTM8        #CP44-832                           **
** 1.0.6     25-Jul-2022   HieuTM8        #CP44-444                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130, #CP44-444                **
** 1.0.2     25-Mar-2022   HieuTM8        #25534                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891,#19106                       **
** 1.0.0.3   23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* Module header file */
#include "CanIf_Ram.h"           /* Module RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Init.h"          /* Initialization header */
#include "CanIf_Tx.h"            /* Tx Interface header file */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_Error.h"         /*  header file for Det */

#if (STD_ON == CANIF_VERSION_INFO_API)
#include "CanIf_Version.h"       /* Module Version header file */
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_INIT_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_INIT_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_INIT_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_INIT_C_SW_MAJOR_VERSION       1
#define CANIF_INIT_C_SW_MINOR_VERSION       1
#define CANIF_INIT_C_SW_REVISION_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_INIT_AR_RELEASE_MAJOR_VERSION != \
  CANIF_INIT_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_INIT_AR_RELEASE_MINOR_VERSION != \
  CANIF_INIT_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_INIT_AR_RELEASE_REVISION_VERSION != \
  CANIF_INIT_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_INIT.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_INIT_SW_MAJOR_VERSION != CANIF_INIT_C_SW_MAJOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Software Major Version"
#endif
#if (CANIF_INIT_SW_MINOR_VERSION != CANIF_INIT_C_SW_MINOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Software Minor Version"
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_Init                                          **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service Initializes internal and external      **
**                        interfaces of the CAN Interface for the further     **
**                        processing.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                             CanIf_Controller               **
**                                             CanIf_HrhInit                  **
**                                             CanIf_OperMode                 **
**                                             CanIf_TrcvMode                 **
**                                             CanIf_TxQueue                  **
**                        Function(s) invoked: SchM_Enter_CanIf_TX_QUEUE_     **
**                                             PROTECTION                     **
**                                             SchM_Exit_CanIf_TX_QUEUE_      **
**                                             PROTECTION                     **
**                                                                            **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00405, SRS_BSW_00101, SRS_BSW_00414, SRS_Can_01021,
           SRS_Can_01022, SRS_BSW_00358, SRS_Can_01016, SRS_Can_01023
*/
FUNC(void, CANIF_CODE) CanIf_Init (P2CONST(CanIf_ConfigType, AUTOMATIC,
                                                    CANIF_APPL_CONST) ConfigPtr)
{
  /* @Trace: SWS_CANIF_00001 SWS_CANIF_00085 */
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  #if (STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_SETDYNAMICTXID_API)
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  #endif
  #endif
  /* @Trace: CanIf_SUD_API_001 */
  VAR(uint16, CANIF_VAR) count;

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  VAR(CanIf_ConfigType, CANIF_VAR) Select_variant;
  if (NULL_PTR == ConfigPtr)
  {
    /* @Trace: CanIf_SUD_API_152 */
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* report to Det */
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, 
                                     CANIF_INIT_SID,CANIF_E_PARAM_POINTER); 
    #endif                                 
  }
  else
  {
    /* @Trace: CanIf_SUD_API_153 */ 
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "Its value is pre-defined" */
    Select_variant = *ConfigPtr; 
    /* Get value from select variant */

    /* Get number of Rx Lpdu */
    CanIf_NoofRxLpdu = Select_variant.NoofRxLpdu;

    /* Get number of Tx Lpdu */
    CanIf_NoofTxLpdu = Select_variant.NoofTxLpdu;

    #if (STD_ON == CANIF_TX_QUEUE)
    /* Get number of Tx queue */
    CanIf_Noofqueue = Select_variant.Noofqueue;

    /* Get number of Tx buffer */
    CanIf_Noofbuffer = Select_variant.Noofbuffer;

    /* Get number of Tx basic */
    CanIf_NoofBasictxlpdu = Select_variant.NoofBasictxlpdu;
    #endif

    /* Get CanIf Config from selected variant*/
    CanIfControllerConfig = Select_variant.pCanIf_ControllerConfig;

    #if ((CANIF_DEV_ERROR_DETECT == STD_ON) || CANIF_MULTIPLE_CANDRV_SUPPORT )
    /* Get HRH Init from selected variant*/
    CanIfHrhInit = Select_variant.pCanIf_HrhInit;
    #endif

    /* Get Rx L-PDU from selected variant*/
    CanIfRxLpdu = Select_variant.pCanIf_RxLpdu;

    /* Get HRH from selected variant*/
    CanIfHrh = Select_variant.pCanIf_Hrh;

    #if (CANIF_TX_QUEUE == STD_ON)
    /* Get Tx Buffer from selected variant*/
    CanIfTxBuffer = Select_variant.pCanIf_TxBuffer;
    #endif

    /* Get Tx L-PDU from selected variant*/
    CanIfTxLpdu = Select_variant.pCanIf_TxLpdu;

    /* Get Hrh Mapping Array from selected variant*/
    CanIfHrhMapArray = Select_variant.pCanIf_HrhMapArray;

    /* Get Tx Basic index mapping from selected variant*/
    CanIfTxBasicPduIndexMapping = Select_variant.pCanIf_TxBasicPduIndexMapping;

    #if (STD_ON == CANIF_SETDYNAMICTXID_API)
    /* Get Tx Dynamic array from selected variant*/
    CanIfCanId = Select_variant.pCanIf_CanId;
    #endif

  #else /* #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT) */
  {
    CANIF_UNUSED(ConfigPtr);
  #endif
    /* Get the pointer to first Controller */
    ptrController =  &CanIf_Controller[CANIF_ZERO];
    /* Get the number of Controllers into local variable */
    count = (uint16)CANIF_ZERO;
    do
    {
      /* @Trace: CanIf_SUD_API_002 */
      /* Put the Controller Mode to Stopped State (CAN_CS_STOPPED) */
      ptrController->ControllerMode = CANIF_STOPPED;

      /* @Trace: SWS_CANIF_00864 */
      /* Initialize Pdu mode */ 
      ptrController->PduMode = (uint8)CANIF_OFFLINE;

      #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
      CanIf_TxMsgCnt[count] = CANIF_ZERO;
      CanIf_RxMsgCnt[count] = CANIF_ZERO;
      #endif

      /* Enable PnTxFilter */
      /* @Trace: CanIf_SUD_API_003 */
      #if (STD_ON == CANIF_PN_SUPPORT)
      /* @Trace: SWS_CANIF_00863 PnTxFilter shall be enabled during initialization */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      if (CanIfControllerConfig[count].PartialNWEnabled == CANIF_TRUE)
      #else
      if (CanIf_ControllerConfig[count].PartialNWEnabled == CANIF_TRUE)
      #endif
      {
        /* @Trace: CanIf_SUD_API_154 */
        CANIF_SET_TX_PNENABLED(ptrController->PduMode);
      }
      #endif

      #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
      /* Initialize Bus Mirrorring Active*/
      ptrController->MirroringActive = CANIF_FALSE;
      #endif

      /* Increment ptrController Index by one */
      ptrController++;
      /* Increment the count by one */
      count++;
    } while ((uint16)CANIF_NO_OF_CONTROLLER != count);
    #if (STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_SETDYNAMICTXID_API)
    /* Get the number of Controllers into local variable */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    count = (uint16)CanIf_NoofTxLpdu;

    /* Get the pointer to the first Tx-LPDU */
    ptrTxLpdu = &CanIfTxLpdu[CANIF_ZERO];

    do {
      /* @Trace: CanIf_SUD_API_004 */
      if (CANIF_INVALID_DYNCANID != ptrTxLpdu->DynCanIdIndex) {
        /* @Trace: SWS_CANIF_00857 Initializes the CanIds of the dynamic Transmit L-PDUs with CanIfTxPduType
          to the value configured via CanIfTxPduCanId  */
        CanIfCanId[ptrTxLpdu->DynCanIdIndex] = ptrTxLpdu->CanId;
      }
      else
      {
        /* Do nothing */
      }
      ptrTxLpdu++;
      count--;
    } while ((uint16)CANIF_ZERO < count);
    #endif /* #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT) */
    #endif /* #if (STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_SETDYNAMICTXID_API) */

    #if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_DEV_ERROR_DETECT))
    #if (CANIF_ONE == CANIF_NO_OF_TRANSCEIVER)
    /* Set the Transceiver state to CANIF_TRCV_E_TRCV_NOT_STANDBY */
    CanIf_OperMode[CANIF_ZERO] = (uint8)CANTRCV_TRCVMODE_STANDBY;
    #else

    /* Get the number of Transceivers into local variable */
    count = (uint16)CANIF_NO_OF_TRANSCEIVER;
    do
    {
      /* Decrement the number of Transceivers */
      count--;

      /* Set the Transceiver state to CANIF_TRCV_E_TRCV_NOT_STANDBY */
      CanIf_OperMode[count] = (uint8)CANTRCV_TRCVMODE_STANDBY;

    } while ((uint16)CANIF_ZERO != count);
    #endif/*#if (CANIF_ONE == CANIF_NO_OF_TRANSCEIVER)*/
    #endif/*#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (...))*/

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Change the CAN Interface Global status to "initialized" */
    CanIf_CanIfStatus = CANIF_INITIALISED;
    #endif

    #if (STD_ON == CANIF_TX_LPDU)
    CanIf_InitQueue();
    #endif /* (STD_ON == CANIF_TX_LPDU) */

    #if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_TX_RX_MONITORING_SUPPORT))
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    for(count = CANIF_ZERO; count < CanIf_NoofRxLpdu; count++)
    #else
    for(count = CANIF_ZERO; count < CANIF_NO_OF_RXLPDU; count++)
    #endif
    {
      /* Init data for array CanIf_ReceiveCnt */
      CanIf_ReceiveCnt[count] = (uint8)CANIF_ZERO;
    }
    #endif

    #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
    /* Set default value for Bit array */
    for(count = CANIF_ZERO; count < CANIF_BITARRAY_SIZE ; count++)
    {
      /* @Trace: CanIf_SUD_API_160 */
      CanIf_BitArray[count] = 0x00;
    }
    #endif

    #if (STD_ON == CANIF_CANTRCV_SUPPORT)
    count = (uint16)CANIF_ZERO;
    do
    {
      /* @Trace: CanIf_SUD_API_161 */
      /* Set the mode for CanTrCv */
      CanIf_TrcvMode[count] = CANIF_TRCV_INIT_MODE;
      /* increment the count */
      count++;
    } while ((uint16)CANIF_NO_OF_TRANSCEIVER != count);
    #endif
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
/*******************************************************************************
** Function Name        : CanIf_DeInit                                        **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : De-initializes the CanIf module                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): None                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01168, SRS_BSW_00336 */
FUNC(void, CANIF_CODE) CanIf_DeInit (void)
{
  /* @Trace: SWS_CANIF_91002 */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Change the CAN Interface Global status to "uninitialized" */
  /* @Trace: CanIf_SUD_API_006 */
  CanIf_CanIfStatus = CANIF_UNINITIALISED;
  #endif
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        CanIf module.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : VersionInfo                                         **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_CanIfStatus              **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANIF_VERSION_INFO_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00407, SRS_BSW_00411 */
FUNC(void, CANIF_CODE)CanIf_GetVersionInfo
             (P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA)VersionInfo)
{
  /* @Trace: SWS_CANIF_00158 */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  retVal = (uint8) E_OK;

  /* Check whether Version Information is equal to NULL Pointer */
  CANIF_NULL_PTR_ERROR(CANIF_GET_VERSIONNFO_SID, retVal, VersionInfo);

  /* Is any DET Error Invoked*/
  if ((uint8) E_OK == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_007 */
    /* Copy the vendor Id */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "It's value checked by Det" */
    VersionInfo->vendorID = CANIF_VENDOR_ID;

    /* Copy the module Id */
    VersionInfo->moduleID = CANIF_MODULE_ID;

    /* Copy Software Major Version */
    VersionInfo->sw_major_version = (uint8)CANIF_VERSION_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    VersionInfo->sw_minor_version = (uint8)CANIF_VERSION_SW_MINOR_VERSION;
  }
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_InitQueue                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service Initializes internal and external      **
**                        interfaces of the CAN Interface for the further     **
**                        processing.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                             CanIf_Controller               **
**                                             CanIf_HrhInit                  **
**                                             CanIf_OperMode                 **
**                                             CanIf_TrcvMode                 **
**                                             CanIf_TxQueue                  **
**                        Function(s) invoked: SchM_Enter_CanIf_TX_QUEUE_     **
**                                             PROTECTION                     **
**                                             SchM_Exit_CanIf_TX_QUEUE_      **
**                                             PROTECTION                     **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_InitQueue(void)
{
  VAR(uint16, CANIF_VAR) count;

  #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))
  /* Disabling relevant interrupts */
  /* @Trace: SWS_CANIF_00033 */
  /* @Trace: CanIf_SUD_API_005 */
  SchM_Enter_CanIf_TX_QUEUE_PROTECTION();
  
  /* Init data for array CanIf TxQueue */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  for(count = (uint16)CANIF_ZERO; count < CanIf_Noofqueue; count++)
  #else
  for(count = (uint16)CANIF_ZERO; count < CANIF_NO_OF_TXQUEUE; count++)
  #endif
  {
    /* @Trace: CanIf_SUD_API_155 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    CanIf_TxQueue[count].Dlc = (uint8)CANIF_ZERO;
    CanIf_TxQueue[count].TxNextQueue = NULL_PTR;
  }
  
  /* Init data for array CanIf TxPduToQueueMapping */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  for(count = (uint16)CANIF_ZERO; count < CanIf_NoofBasictxlpdu; count++)
  #else
  for(count = (uint16)CANIF_ZERO; count < CANIF_NO_OF_BASIC_TXLPDU; count++)
  #endif
  {
    /* @Trace: CanIf_SUD_API_156 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    CanIf_TxPduToQueueMapping[count] =
                                  (CanIf_TxPduIdType)CANIF_INVALID_TXQUEUE;
  }

  /* Init data for array CanIf TxBuffer */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  for(count = (uint16)CANIF_ZERO; count < CanIf_Noofbuffer; count++)
  {
    /* @Trace: CanIf_SUD_API_157 */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    *CanIfTxBuffer[count].TxFirstQueue = NULL_PTR;
  }
  #else
  for(count = (uint16)CANIF_ZERO; count < CANIF_NO_OF_TXBUFFER; count++)
  {
    /* @Trace: CanIf_SUD_API_158 */
    *CanIf_TxBuffer[count].TxFirstQueue = NULL_PTR;
  }
  #endif

  /* Enabling relevant interrupts */
  SchM_Exit_CanIf_TX_QUEUE_PROTECTION();

  #endif /* (STD_ON ==CANIF_BASIC_CAN_TXPDU) */

  /* Init data */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  for(count = CANIF_ZERO; count < CanIf_NoofTxLpdu; count++)
  #else
  for(count = CANIF_ZERO; count < CANIF_NO_OF_TXLPDU; count++)
  #endif
  {
    /* @Trace: CanIf_SUD_API_159 */
    /* Init data for array CanIf_TxPduGwStatus */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    CanIf_TxPduGwStatus[count] = CANIF_GW_NOREQUEST;
    #if (STD_ON == CANIF_TX_RX_MONITORING_SUPPORT)
    /* Init data for array CanIf_TransmitCnt */
    CanIf_TransmitCnt[count] = (uint8)CANIF_ZERO;
    #endif
    #if (CANIF_BUS_MIRRORING_SUPPORT == STD_ON)
    /* Init data for array CanIf_RamInit8Bit */
    CanIf_RamInit8Bit[count] = 0x00;

    /* Init data for array CanIf_TxPduInfoPtr */
    CanIf_TxPduInfoPtr[count].SduDataPtr = &CanIf_RamInit8Bit[count];
    CanIf_TxPduInfoPtr[count].MetaDataPtr = NULL_PTR;
    CanIf_TxPduInfoPtr[count].SduLength = 0x0000;
    #endif
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANIF_TX_LPDU) */

/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
