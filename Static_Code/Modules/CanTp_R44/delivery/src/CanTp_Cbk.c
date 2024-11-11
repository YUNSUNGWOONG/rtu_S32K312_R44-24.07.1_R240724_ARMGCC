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
**  SRC-MODULE: CanTp_Cbk.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Callback functions implementation for CanTp module.           **
**              CanTp_RxIndication                                            **
**              CanTp_TxConfirmation                                          **
**              CanTp_RxDetCheck                                              **
**              CanTp_CbkTxDetCheck                                           **
**              CanTp_ProcessRxData                                           **
**              CanTp_ProcessRxCF                                             **
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
** 1.1.0     31-Oct-2023   HieuTM8        #CP44-2819, #CP44-3153, #CP44-3154  **
** 1.0.12    01-Aug-2023   MJKim          #CP44-2079                          **
** 1.0.11    12-Jun-2023   HieuTM8        #CP44-2333                          **
** 1.0.9     12-Dec-2022   HieuTM8        #CP44-1244                          **
** 1.0.8     25-Nov-2022   HieuTM8        #CP44-1199                          **
** 1.0.7     31-Oct-2022   HieuTM8        #CP44-892                           **
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.2     18-Apr-2022   HieuTM8        R44-Redmine #25679, #25515          **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344          **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp Module Header File */
#include "CanTp_Cbk.h"            /* CanTp Cbk Header File */
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_RxInternal.h"     /* CanTp RxInternal Header File */
#include "CanTp_TxInternal.h"     /* CanTp TxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Global RAM variables header file */
#include "PduR_CanTp.h"           /* PduR header for CAN TP */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
/* @Trace: SWS_CanTp_00217 */
/* Include DET header */
#include "Det.h"                  /* DET header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_CBK_C_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_CBK_C_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_CBK_C_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_CBK_C_SW_MAJOR_VERSION            0x01u
#define CANTP_CBK_C_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_CBK_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_CBK_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_CBK_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_Cbk.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_CBK_C_SW_MAJOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_CBK_C_SW_MINOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

static FUNC(void, CANTP_CODE) CanTp_TxConfirmationErrorCheck(CanTp_ChannelType channel);

/*******************************************************************************
** Function Name        : CanTp_RxIndication                                  **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : This function is called by the CAN Interface after  **
**                        successful reception of a Rx CAN L-PDU.             **
**                        This callback service is called by the CanIf and    **
**                        implemented by the CanTp                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 CanTp_RxExtPdus,           **
**                                                 CanTp_RxExtFcPdus,         **
**                                                 CanTp_NSaOrNAeSduMapping   **
**                                                 Cantp_Rx_Fcpdu_start       **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_RxBinarySearch       **
**                                                 CanTp_ProcessRxFc          **
**                                                 CanTp_RxDetCheck           **
*******************************************************************************/
#if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) || (STD_ON == CANTP_RX_NSDU))
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
 * SRS_ES95486_50E_SWP00023, SRS_ES95486_50E_SWP00035, SRS_ISO_15765_00001,   SRS_ISO_15765_00002,   SRS_ISO_15765_00003
 * SRS_ISO_15765_00004, SRS_ISO_15765_00005, SRS_ISO_15765_00006, SRS_ISO_15765_00007, SRS_ISO_15765_00008
 * SRS_ISO_15765_00009, SRS_ISO_15765_00010, SRS_ISO_15765_00011, SRS_ISO_15765_00012, SRS_ISO_15765_00013
 * SRS_ISO_15765_00014, SRS_ISO_15765_00015, SRS_ISO_15765_00016, SRS_ISO_15765_00018, SRS_ISO_15765_00019
 * SRS_ISO_15765_00020, SRS_ISO_15765_00021, SRS_ISO_15765_00022 
*/
FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType rxPduId , P2CONST(
    PduInfoType, AUTOMATIC, CANTP_APPL_CONST) ptrPduInfo)
{
  /* @Trace: CanTp_SUD_API_105 */
  #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS) \
    || (STD_ON == CANTP_TX_MIXED_ADDRESS) || \
    (STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (STD_ON == CANTP_RX_MIXED_ADDRESS) \
    || (STD_ON == CANTP_DEV_ERROR_DETECT) \
    || (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) \
    || (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) \
    || (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) \
    || (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
  P2CONST(CanTp_RxExtPdusType, AUTOMATIC, CANTP_CONST) ptrExtPdu;
  #endif
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) || \
  (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS) \
  || (STD_ON == CANTP_TX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) \
  || (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) || (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) \
  || (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
  P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CONST) ptrSduMap;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc;
  #endif
  PduIdType rxSduId;
  #if ((STD_ON == CANTP_RX_NSDU) || ((STD_ON == CANTP_TX_NSDU) &&\
  (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)))
  uint8 bytePos;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
  uint8 frame;
  #endif
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  boolean detErrorFlag;
  #endif

  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu;
  #endif

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_OFF == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if((CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
  (CANTP_RX_NORMALFIXED_ADDRESS == STD_ON) ||\
  (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
  (CANTP_TX_NORMALFIXED_ADDRESS == STD_ON))
  VAR(CanTp_LongAccessType, AUTOMATIC) longAccess;
  #endif
  #endif
  #endif

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  detErrorFlag = CanTp_RxDetCheck(rxPduId , ptrPduInfo);

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_OFF == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if((CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
  (CANTP_RX_NORMALFIXED_ADDRESS == STD_ON) ||\
  (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
  (CANTP_TX_NORMALFIXED_ADDRESS == STD_ON))
  longAccess.WholeLong = (uint32)CANTP_ZERO;
  #endif
  #endif
  #endif

  /* Check if no development errors has occurred */
  if (CANTP_FALSE == detErrorFlag)
  #endif /* #if(STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS) \
        || (STD_ON == CANTP_TX_MIXED_ADDRESS) || \
        (STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (STD_ON == CANTP_RX_MIXED_ADDRESS) \
        || (STD_ON == CANTP_DEV_ERROR_DETECT) \
        || (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) \
        || (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) \
        || (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) \
        || (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    /* Get the RxNSdu structure pointer for Addressing Mode */
    /* If support Postbuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    ptrExtPdu = &(Variant_Select->PtrRxExtPdus)[rxPduId];
    #else
    ptrExtPdu = &CanTp_RxExtPdus[rxPduId];
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    #endif /* End of if ((STD_ON == CANTP_RX_NSDU) ||*/
    #endif /*   (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||
            *   (CANTP_TX_MIXED_ADDRESS) ||
            *   (STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
            *   (CANTP_RX_MIXED_ADDRESS == STD_ON) ||
            *   (STD_ON == CANTP_DEV_ERROR_DETECT)) */
    /* polyspace +3 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTp. No impact" */
    /* polyspace +5 RTE:IDP [Not a defect:Low] "The pointer ptrExtPdu-> AddressingMode can not outside its bounds. Because the maximum value of AddressingMode is 3 while the  the  . So, This warning not impact" */
    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    #if (STD_OFF == CANTP_ADDRESSING_MODE_ALL)
    if(CANTP_INVALID != ptrExtPdu->AddressingMode)
    #endif
    {
      /* @Trace: CanTp_SUD_API_106 */
      bytePos = CanTp_BytePos[ptrExtPdu->AddressingMode];
    }
    #if (STD_OFF == CANTP_ADDRESSING_MODE_ALL)
    else
    {
      /* @Trace: CanTp_SUD_API_107 */
      /* If support Postbuild */
      #if (STD_OFF == CANTP_RX_FCPDU_START)
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      ptrExtPdu = &(Variant_Select->PtrRxExtFcPdus)[rxPduId];
      #else
      ptrExtPdu = &CanTp_RxExtFcPdus[rxPduId];
      #endif
      #else /* (STD_OFF == CANTP_RX_FCPDU_START) */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      ptrExtPdu = &(Variant_Select->PtrRxExtFcPdus)[rxPduId - 
                            (PduIdType)CANTP_RX_FCPDU_START];
      #else
      ptrExtPdu = &CanTp_RxExtFcPdus[rxPduId - 
                            (PduIdType)CANTP_RX_FCPDU_START];
      #endif
      #endif
      bytePos = CanTp_BytePos[ptrExtPdu->AddressingMode];
    }
    #endif /* (STD_OFF == CANTP_ADDRESSING_MODE_ALL) */
    #endif /* ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)) */

    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    /* polyspace +4 RTE:NIV [Not a defect:Low] "The value of ptrRxSrc has been gotten from PDU, no impact" */
    /* polyspace +3 RTE:IDP [Not a defect:Low] "ptrRxSrc[bytePos] can not outside its bounds. Because the value maximum of bytePos is 3. So, this warning not impact." */
    /* Get the Frame type */
    ptrRxSrc = ptrPduInfo->SduDataPtr;
    frame = (uint8)((ptrRxSrc[bytePos]) & (uint8)CANTP_PCI_MASK);
    #endif
    
    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
    /* Check if the frame is a flow control frame */
    if ((uint8)CANTP_FC_PCI == frame)
    {
      /* @Trace: CanTp_SUD_API_108 */
      #if ((STD_ON == CANTP_TX_NSDU) ||\
        (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
        (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
        (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
      /* If support Postbuild */
      #if (STD_OFF == CANTP_RX_FCPDU_START)
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      /* Initialize Pdu structure for flow control frame */
      ptrExtPdu = &(Variant_Select->PtrRxExtFcPdus)[rxPduId];
      #else
      /* Initialize Pdu structure for flow control frame */
      ptrExtPdu = &CanTp_RxExtFcPdus[rxPduId];
      #endif /* End if of (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
      #else /* (STD_OFF == CANTP_RX_FCPDU_START) */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      /* Initialize Pdu structure for flow control frame */
      ptrExtPdu = &(Variant_Select->PtrRxExtFcPdus)[rxPduId -
                            (PduIdType)CANTP_RX_FCPDU_START];
      #else
      /* Initialize Pdu structure for flow control frame */
      ptrExtPdu = &CanTp_RxExtFcPdus[rxPduId -
                            (PduIdType)CANTP_RX_FCPDU_START];
      #endif /* End if of (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
      #endif /* End if of (STD_OFF == CANTP_RX_FCPDU_START) */
      #endif
    } /* End of if (CANTP_FC_PCI == frame) */
    else
    #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
    {
      /* @Trace: CanTp_SUD_API_109 */
      #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS) \
          || (STD_ON == CANTP_TX_MIXED_ADDRESS) || \
          (STD_ON == CANTP_RX_EXTENDED_ADDRESS) || \
          (STD_ON == CANTP_RX_MIXED_ADDRESS) || \
          (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) || \
          (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) || \
          (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) || \
          (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
      /* If support Postbuild */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      /* Initialize Pdu structure for normal frame */
      ptrExtPdu = &(Variant_Select->PtrRxExtPdus)[rxPduId];
      #else
      /* Initialize Pdu structure for normal frame */
      ptrExtPdu = &CanTp_RxExtPdus[rxPduId];
      #endif /* End if of (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
      #endif
    }

    /* @Trace: SWS_CanTp_00336 */
    /* When CanTp_RxIndication is called for
     * an FC on a generic connection (N-PDU with MetaData),
     * the CanTp module shall check the addressing information contained
     * in the MetaData against the stored values.
     *
     * - Case 1: If Dynamic ID is supported, Normal fixed and Mixed 29bit
     *  can be configured, this is verified by tool gen.
     *   + If Generic connection is not enable, request shall be produce
     *  like one specific connection. The Addressing information shall be
     *  check by Internal before notify to upper.
     *   + If Generic connection is enable, only CF or FC frame is verified
     *  before notify to upper layer.
     *
     *  Following the condition, tool gen shall optimize the configuration set
     *  while generating.
     *
     * - Case 2: If Dynamic ID is not supported, that mean Normal fixed and
     *   Mixed 29bit is handled same as Normal addressing and Mixed.
     */
    #ifdef CANTP_DYNID_SUPPORT
    /* @Trace: SWS_CanTp_00328 */
    /* The same NPdu may only be referenced by more than one NSdu */
    /* @Trace: SWS_CanTp_00284 */
    /* @Trace: SWS_CanTp_00095 */
    /* Determine the relevant N-SDU */
    /* N_AI shall be verified for Ext, Mixed, Normalfixed, Mixed29bit.
     *
     * For details as below:
     * - Extended: N_TA in the SduData shall be verified.
     * - Mixed: N_AE in the SduData shall be verified.
     * - Normal fixed: Both of N_SA, N_TA shall be verified.
     * - Mixed29bit: N_SA, N_TA and N_AE shall be verified.
     *
     * For specific connection RxN_TA shall be unique for each of channels.
     * And at the same time, only one RxN_SA is income.
     * Therefore, with Normal fixed and Mixed29bit to optimize performance
     * N_SA shall be finding first. If RxSdu is found, then CanTp check against the
     * value of N_TA to make sure the request be to ECU itself.
     */
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||  \
        (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)  \
        || (STD_ON == CANTP_TX_MIXED_ADDRESS) ||  \
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||  \
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||  \
        (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||  \
        (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS))
    /* Check if the requested Pdu is configured for extended addressing */
    if (ptrExtPdu->AddressingMode != (uint8)CANTP_STANDARD_ADDRESS)
    {
      /* @Trace: CanTp_SUD_API_110 */
      #if((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||  \
          (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||  \
          (STD_ON == CANTP_RX_MIXED_ADDRESS) ||  \
          (STD_ON == CANTP_TX_MIXED_ADDRESS) ||  \
          (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||  \
          (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
      if (((uint8)CANTP_EXTENDED_ADDRESS == ptrExtPdu->AddressingMode) ||  \
          ((uint8)CANTP_MIXED_ADDRESS == ptrExtPdu->AddressingMode) ||  \
        /* Consider mixed29bit is same as mixed 11 bit
        * In-case: Pdu has not configured with metaData or
        * metaDataPtr is not available */
          (((uint8)CANTP_MIXED29BIT_ADDRESS == ptrExtPdu->AddressingMode) &&  \
          ((NULL_PTR == ptrPduInfo->MetaDataPtr) ||  \
          (CANTP_TRUE != ptrExtPdu->InPduwithMetaDataSts))))
      {
        /* @Trace: CanTp_SUD_API_111 */
        /* Check if more than one NPdus are extended */
        if (ptrExtPdu->NoOfPdusOrSduId != (PduIdType)CANTP_ONE)
        {
          /* @Trace: CanTp_SUD_API_112 */
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          /* Search the Nsdu index based on the unique combination of NPduId and N_AI */
          ptrSduMap = CanTp_RxBinarySearch(
                            &(Variant_Select->PtrNSaOrNAeSduMapping)[ptrExtPdu->RxNSaOrNAeSduMapIndex],
                            (uint8)(ptrExtPdu->NoOfPdusOrSduId), *(ptrPduInfo->SduDataPtr));
          #else
          /* Search the Nsdu index based on the unique combination of NPduId and N_AI */
          ptrSduMap = CanTp_RxBinarySearch(
                            &CanTp_NSaOrNAeSduMapping[ptrExtPdu->RxNSaOrNAeSduMapIndex],
                            (uint8)(ptrExtPdu->NoOfPdusOrSduId), *(ptrPduInfo->SduDataPtr));
          #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
          /* Check if requested Pdu has no NSA mapping. */
          if (NULL_PTR == ptrSduMap)
          {
            /* @Trace: CanTp_SUD_API_113 */
            rxSduId = (PduIdType)CANTP_ZERO;
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            detErrorFlag = CANTP_TRUE;
            #endif
          } /* End of if (NULL_PTR == LpSduMapPtr) */
          else
          {
            /* @Trace: CanTp_SUD_API_114 */
            /* Initialize RxNSDuId */
            rxSduId = ptrSduMap->SduIndex;
          }
        } /* if(LpExtPduPtr->ddNoOfPdusOrSduId != CANTP_ONE) */
        else
        {
          /* @Trace: CanTp_SUD_API_115 */
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          /* Access the address of the structure which contains the NSDU index */
          ptrSduMap = &(Variant_Select->PtrNSaOrNAeSduMapping)
                        [ptrExtPdu->RxNSaOrNAeSduMapIndex];
          #else
          /* Access the address of the structure which contains the NSDU index */
          ptrSduMap = &CanTp_NSaOrNAeSduMapping
                        [ptrExtPdu->RxNSaOrNAeSduMapIndex];
          #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
          /* Check RxNTa (TxNSa) mapping */
          if (ptrSduMap->RxNTaOrNAe != (uint8)*(ptrPduInfo->SduDataPtr))
          {
            /* @Trace: CanTp_SUD_API_116 */
            rxSduId = (PduIdType)CANTP_ZERO;
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            detErrorFlag = CANTP_TRUE;
            #endif
          }
          else
          {
            /* @Trace: CanTp_SUD_API_117 */
            /* Initialize RxNSDuId */
            rxSduId = ptrSduMap->SduIndex;
          }
        } /* End of else */
      }
      #endif /* #if((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS)) */
    #if((CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
    (CANTP_RX_NORMALFIXED_ADDRESS == STD_ON) ||\
    (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
    (CANTP_TX_NORMALFIXED_ADDRESS == STD_ON))
    else
    {
      /* @Trace: CanTp_SUD_API_118 */
      /* Check if Pdu with metaData and valid metaData from CanIf */
      if(CANTP_TRUE == ptrExtPdu->InPduwithMetaDataSts)
      {
        /* @Trace: CanTp_SUD_API_119 */
        #if(STD_OFF == CANTP_GENERIC_CONNECTION_SUPPORT)
        longAccess.WholeLong = (uint32)*((uint32*)&ptrPduInfo->MetaDataPtr[(uint8)CANTP_ZERO]);
        /* Check if more than one NPdus are extended */
        if (ptrExtPdu->NoOfPdusOrSduId != (PduIdType)CANTP_ONE)
        {
          /* @Trace: CanTp_SUD_API_120 */
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          /* Search the Nsdu index based on the unique combination of NPduId and N_AI */
          ptrSduMap = CanTp_RxSpecificBinarySearch(
                      &(Variant_Select->PtrNSaOrNAeSduMapping)[ptrExtPdu->RxNSaOrNAeSduMapIndex],
                      (uint8)(ptrExtPdu->NoOfPdusOrSduId), ptrExtPdu->AddressingMode,
                      longAccess.byte_val.LSByte, longAccess.byte_val.Byte_1,
                      *(ptrPduInfo->SduDataPtr));
          #else
          ptrSduMap = CanTp_RxSpecificBinarySearch(
                      &CanTp_NSaOrNAeSduMapping[ptrExtPdu->RxNSaOrNAeSduMapIndex],
                      (uint8)(ptrExtPdu->NoOfPdusOrSduId), ptrExtPdu->AddressingMode,
                      longAccess.byte_val.LSByte, longAccess.byte_val.Byte_1,
                      *(ptrPduInfo->SduDataPtr));
          #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
          /* Check if requested Pdu has no NSA mapping. */
          if (NULL_PTR == ptrSduMap)
          {
            /* @Trace: CanTp_SUD_API_121 */
            rxSduId = (PduIdType)CANTP_ZERO;
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            detErrorFlag = CANTP_TRUE;
            #endif
          } /* End of if (NULL_PTR == LpSduMapPtr) */
          else
          {
            /* @Trace: CanTp_SUD_API_122 */
            /* Initialize RxNSDuId */
            rxSduId = ptrSduMap->SduIndex;
          }
        } /* if(LpExtPduPtr->ddNoOfPdusOrSduId != CANTP_ONE) */
        else
        {
          /* @Trace: CanTp_SUD_API_123 */
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          /* Access the address of the structure which contains the NSDU index */
          ptrSduMap = &(Variant_Select->PtrNSaOrNAeSduMapping)
                        [ptrExtPdu->RxNSaOrNAeSduMapIndex];
          #else
          /* Access the address of the structure which contains the NSDU index */
          ptrSduMap = &CanTp_NSaOrNAeSduMapping
                        [ptrExtPdu->RxNSaOrNAeSduMapIndex];
          #endif
          /* Check RxNTa (TxNSa) mapping */
          if (ptrSduMap->RxNTa != longAccess.byte_val.Byte_1)
          {
            /* @Trace: CanTp_SUD_API_124 */
            rxSduId = (PduIdType)CANTP_ZERO;
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            detErrorFlag = CANTP_TRUE;
            #endif
          }
          else if (ptrSduMap->RxNSa != longAccess.byte_val.LSByte)
          {
            /* @Trace: CanTp_SUD_API_125 */
            rxSduId = (PduIdType)CANTP_ZERO;
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            detErrorFlag = CANTP_TRUE;
            #endif
          }
          #if (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)
          else if (((uint8)CANTP_MIXED29BIT_ADDRESS == ptrExtPdu->AddressingMode) &&\
              (ptrSduMap->RxNTaOrNAe != *(ptrPduInfo->SduDataPtr)))
          {
            /* @Trace: CanTp_SUD_API_126 */
            rxSduId = (PduIdType)CANTP_ZERO;
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            detErrorFlag = CANTP_TRUE;
            #endif
          }
          #endif /* End of #if (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) */
          else
          {
            /* @Trace: CanTp_SUD_API_127 */
            /* Initialize RxNSDuId */
            rxSduId = ptrSduMap->SduIndex;
          }
        } /* End of else */
        #else
        /* If support PostBuild */
        #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          ptrSduMap = &(Variant_Select->PtrNSaOrNAeSduMapping)
                      [ptrExtPdu->RxNSaOrNAeSduMapIndex];
        #else
          ptrSduMap = &CanTp_NSaOrNAeSduMapping
                      [ptrExtPdu->RxNSaOrNAeSduMapIndex];
        #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

        rxSduId = ptrSduMap->SduIndex;
        #endif
      }
      /* Pdu is not configured with metaData*/
      else
      {
        /* @Trace: CanTp_SUD_API_128 */
        /* Initialize RxNSDuId */
        rxSduId = ptrExtPdu->NoOfPdusOrSduId;
      }
    }
    #endif /* #if((CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
      (CANTP_RX_NORMALFIXED_ADDRESS == STD_ON) ||\
      (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
      (CANTP_TX_NORMALFIXED_ADDRESS == STD_ON)) */
    }
    else /* End of (ptrExtPdu->AddressingMode != (uint8)CANTP_STANDARD_ADDRESS) */
    {
      /* @Trace: CanTp_SUD_API_129 */
      /* Initialize Receive NSDu Id If Receive pdu is not configured for
        * extended address */
      rxSduId = ptrExtPdu->NoOfPdusOrSduId;
    }
    #elif (STD_ON == CANTP_RX_NSDU)

    /* Initialize Receive NSDu Id If Receive pdu is not configured for
      *   extended address */
    rxSduId = ptrExtPdu->NoOfPdusOrSduId;
    #endif /* #if(STD_ON == CANTP_EXTENDED_ADDRESS) */

    #else /* CANTP_DYNID_SUPPORT */
    /* @Trace: SWS_CanTp_00328 */
    /* The same NPdu may only be referenced by more than one NSdu */
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||  \
        (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)  \
        || (STD_ON == CANTP_TX_MIXED_ADDRESS) ||  \
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||  \
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)||  \
        (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||  \
        (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS))
      /* Check if the requested Pdu is configured for extended addressing */
      /* @Trace: SWS_CanTp_00284 */
      /* @Trace: SWS_CanTp_00095 */
      /* Determine the relevant N-SDU */
    if ((ptrExtPdu->AddressingMode != (uint8)CANTP_STANDARD_ADDRESS) &&\
        (ptrExtPdu->AddressingMode != (uint8)CANTP_NORMALFIXED_ADDRESS))
    {
      /* @Trace: CanTp_SUD_API_130 */
      /* Check if more than one NPdus are extended */
      if (ptrExtPdu->NoOfPdusOrSduId != (PduIdType)CANTP_ONE)
      {
        /* If support PostBuild */
        #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
        /* Search the Nsdu index based on the unique combination of NPduId and N_AI */
        ptrSduMap = CanTp_RxBinarySearch(
                      &(Variant_Select->PtrNSaOrNAeSduMapping)[ptrExtPdu->RxNSaOrNAeSduMapIndex],
                      (uint8)(ptrExtPdu->NoOfPdusOrSduId), *(ptrPduInfo->SduDataPtr));
        #else
        /* Search the Nsdu index based on the unique combination of NPduId and
                  *   N_AI */
        ptrSduMap = CanTp_RxBinarySearch(
                    &CanTp_NSaOrNAeSduMapping[ptrExtPdu->RxNSaOrNAeSduMapIndex],
                    (uint8)(ptrExtPdu->NoOfPdusOrSduId), *(ptrPduInfo->SduDataPtr));
        #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

        /* Check if requested Pdu has no NSA mapping. */
        if (NULL_PTR == ptrSduMap)
        {
          /* @Trace: CanTp_SUD_API_132 */
          rxSduId = (PduIdType)CANTP_ZERO;
          #if (STD_ON == CANTP_DEV_ERROR_DETECT)
          detErrorFlag = CANTP_TRUE;
          #endif
        } /* End of if (NULL_PTR == LpSduMapPtr) */
        else
        {
          /* @Trace: CanTp_SUD_API_133 */
          /* Initialize RxNSDuId */
          rxSduId = ptrSduMap->SduIndex;
        }
      } /* if(LpExtPduPtr->ddNoOfPdusOrSduId != CANTP_ONE) */
      else
      {
        /* If support PostBuild */
        #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
        /* Access the address of the structure which contains the NSDU index */
        ptrSduMap = &(Variant_Select->PtrNSaOrNAeSduMapping)
                    [ptrExtPdu->RxNSaOrNAeSduMapIndex];
        #else
        /* Access the address of the structure which contains the NSDU index */
        ptrSduMap = &CanTp_NSaOrNAeSduMapping
                    [ptrExtPdu->RxNSaOrNAeSduMapIndex];
        #endif
        /* Check RxNTa (TxNSa) mapping */
        if (ptrSduMap->RxNTaOrNAe != (uint8)*(ptrPduInfo->SduDataPtr))
        {
          /* @Trace: CanTp_SUD_API_135 */
          rxSduId = (PduIdType)CANTP_ZERO;
          #if (STD_ON == CANTP_DEV_ERROR_DETECT)
          detErrorFlag = CANTP_TRUE;
          #endif
        }
        else
        {
          /* @Trace: CanTp_SUD_API_136 */
          /* Initialize RxNSDuId */
          rxSduId = ptrSduMap->SduIndex;
        }
      } /* End of else */
    }
    else
    {
      /* @Trace: CanTp_SUD_API_137 */
      /* Initialize Receive NSDu Id If Receive pdu is not configured for
      *   extended address */
      rxSduId = ptrExtPdu->NoOfPdusOrSduId;
    }
    #elif (STD_ON == CANTP_RX_NSDU)

    /* Initialize Receive NSDu Id If Receive pdu is not configured for extended address */
    rxSduId = ptrExtPdu->NoOfPdusOrSduId;
    #endif /* #if(STD_ON == CANTP_EXTENDED_ADDRESS) */
    #endif /* End of #ifdef CANTP_DYNID_SUPPORT */

    #if (STD_ON == CANTP_DEV_ERROR_DETECT)
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
    (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
    (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
    (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS))
    if (CANTP_FALSE == detErrorFlag)
    #endif
    #endif /* #if(STD_ON == CANTP_DEV_ERROR_DETECT) */
    {
      /* @Trace: CanTp_SUD_API_138 */
      #if ((STD_ON == CANTP_TX_NSDU) &&\
      (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))

      /* Check that received frame is a FC frame or not */
      if ((uint8)CANTP_FC_PCI == frame)
      {  
        #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)

        /* If support Postbuild */
        #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
        /* Get the pointer to current TxNSdu */
        ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[rxSduId];
        #else
        /* Get the pointer to current TxNSdu */
        ptrTxNSdu = &CanTp_TxSduStatic[rxSduId];
        #endif /* (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
        /* If the RxNsdu supports Functional addressing */
        if ((uint8)CANTP_FUNCTIONAL_ADDRESS == ptrTxNSdu->TaType)
        {
          /* @Trace: CanTp_SUD_API_139 */
          #if (STD_ON == CANTP_DEV_ERROR_DETECT)
          /* Report to DET */          
          (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_RXINDICATION_SID, CANTP_E_PARAM_ID);
          #endif 
        }
        else /* End of if (CANTP_FUNCTIONAL_ADDRESS == ptrTxNSdu->TaType) */
        #endif /* STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING */
        {
          /* @Trace: CanTp_SUD_API_140 */
          /* If frame is Flow control then process it for RxFc */
          CanTp_ProcessRxFc(rxSduId, ptrPduInfo);
        }
      } /* End of if (CANTP_FC_PCI == frame) */
      else /* Received frame is not a FC frame */
      #endif /* #if(STD_ON == CANTP_TX_NSDU) && \
              * (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)*/
      {
        /* @Trace: CanTp_SUD_API_141 */
        #if (STD_ON == CANTP_RX_NSDU)
        #if (((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)) ||\
        ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS)))
        bytePos = (uint8)CanTp_BytePos[ptrExtPdu->AddressingMode];
        #else
        /* Get the N_PCI position */
        bytePos = (uint8)CANTP_ZERO;
        #endif
        
        CanTp_ProcessRxData(rxSduId, ptrPduInfo, bytePos);
        #endif /* End of if (STD_ON == CANTP_RX_NSDU) */
      } /* Received frame is not a FC frame */
    } /* @ if(detErrorFlag == CANTP_FALSE) */
  } /* @ if(detErrorFlag == CANTP_FALSE) */

  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  {
    CANTP_UNUSED(ptrTxNSdu);
  }
  #endif
} /* End of CanTp_RxIndication(PduIdType RxPduId , P2CONST(PduInfoType,
   * AUTOMATIC, CANTP_APPL_CONST) PduInfoPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) || (CANTP_RX_NSDU
        * == STD_ON)) */

/*******************************************************************************
** Function Name        : CanTp_ProcessRxData                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_RxIndication   **
**                        to process the Rx data frame received               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : rxSduId                                             **
**                        ptrPduInfo                                          **
**                        LpExtPduPtr                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : detErrFlag                                          **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :   CANTP_CHANNEL_ID         **
**                        CanTp_RxSduDynamic                                  **
**                        CANTP_MAXNO_RX_NPDU                                 **
**                        Function(s) invoked    : CanTp_RequestRxBuffer      **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01065 SRS_Can_01082 SRS_Can_01066 SRS_Can_01116 */
FUNC(void, CANTP_CODE) CanTp_ProcessRxData(PduIdType rxSduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_CONST) ptrPduInfo, VAR(
    uint8, AUTOMATIC) bytePos)
{
  /* @Trace: CanTp_SUD_API_057 */
  #if (STD_ON == CANTP_RX_NSDU)
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  #endif
  VAR(uint8, AUTOMATIC) bytePosLc;
  bytePosLc = bytePos;
  #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  #endif
  #if (STD_ON == CANTP_RX_NSDU)
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc;
  CanTp_ChannelType channel;
  #endif
  #if (STD_ON == CANTP_RX_NSDU)
  uint8 receivedDlc;
  uint8 channelRxState;
  uint8 pci;
  uint8 frame;
  #endif

  #if (STD_ON == CANTP_RX_NSDU)
  boolean dlcErrorFlag;
  boolean newFrameFlag;
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS)&&(STD_ON == CANTP_RX_NPDU_METADATA))
  VAR(CanTp_WordAccessType, AUTOMATIC) wordAccess;
  #endif
  #if((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  P2VAR(uint16, AUTOMATIC, CANTP_VAR) ptrWordAccess;
  VAR(boolean,AUTOMATIC) invalidMetaData;
  #endif
  
  #endif /* End of #if(STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)) &&\
  (STD_ON == CANTP_RX_NPDU_METADATA)
  VAR(CanTp_LongAccessType, AUTOMATIC) longAccess;
  #endif /* End of ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)) */
  #endif /* End of #ifdef CANTP_DYNID_SUPPORT */
  #endif /* End of (STD_ON == CANTP_RX_NSDU) */


  #if (STD_ON == CANTP_RX_NSDU)
  ptrRxSrc = ptrPduInfo->SduDataPtr;
  /* polyspace +3 RTE:NIV [Not a defect:Low] "The value of ptrRxSrc has been gotten from PDU, no impact" */
  /* polyspace +2 RTE:IDP [Not a defect:Low] "ptrRxSrc[bytePosLc] can not outside its bounds. Because the value maximum of bytePos is 3. So, this warning not impact." */
  /* Get the Frame type */
  frame = (uint8)((ptrRxSrc[bytePosLc]) & (uint8)CANTP_PCI_MASK);

  /* Set the status of the new frame received to the default */
  newFrameFlag = CANTP_FALSE;

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS)&&(STD_ON == CANTP_RX_NPDU_METADATA))
  /* Set the invalid status of MetaData check to the default*/
  wordAccess.WholeWord = (uint16)CANTP_ZERO;
  #endif
  #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  invalidMetaData = CANTP_FALSE;
  #endif /* End of #if((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)) */
  #endif /* End of #if(STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #endif /* End of #ifdef CANTP_DYNID_SUPPORT */
  #endif /* End of if (STD_ON == CANTP_RX_NSDU) */
  #if (STD_ON == CANTP_RX_NSDU)

  /* If support Postbuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Initialize RxNSdu static structure according to RxNSduId */
  ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[rxSduId];
  #else
  /* Initialize RxNSdu static structure according to RxNSduId */
  ptrRxNSdu = &CanTp_RxSduStatic[rxSduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
  /* polyspace +2 RTE:IDP [Not a defect:Low] "ptrRxNSdu->ChannelId can not outside its bounds. It is covered by generation. So, this warning not impact." */
  /* Initialize Channel according to RXNSDu structure channel */
  channel = ptrRxNSdu->ChannelId;

  /* Initialize Channel RAM structure according to addressing mode */
  ptrChannelRam = &CanTp_ChannelRxRam[channel];

  /* Initialize Channel state according RAM structure Channel */
  channelRxState = ptrChannelRam->ChannelState;

  /* Get the N_PCI position
   * Initialize byte position according structure addressing mode */
  bytePosLc = (uint8)CanTp_BytePos[ptrRxNSdu->AddressingMode];

  /* Update the data source pointer address */
  ptrRxSrc = &ptrRxSrc[bytePosLc];
  /* polyspace +2 RTE:NIV [Not a defect:Low] "The value of ptrRxSrc has been gotten from PDU, no impact" */
  /* Decode the N_PCI byte */
  pci = (uint8)((*ptrRxSrc) & (uint8)CANTP_PCI_MASK);

  /* @Trace: SWS_CanTp_00330 */
  /* When CanTp_RxIndication is called for a SF or FF N-PDU
   * with MetaData (indicating a generic connection), the CanTp module shall store the
   * addressing information contained in the MetaData of the PDU and use this
   * information for the initiation of the connection to the upper layer, for transmission of
   * FC N-PDUs and for identification of CF N-PDUs. The addressing information in the
   * MetaData depends on the addressing format:
   *  + Normal, Extended, Mixed 11 bit: none
   *  + Normal fixed, Mixed 29 bit: N_SA, N_TA
   */
  /* @Trace: SWS_CanTp_00337 */
  /* When an SF or FF N-PDU with MetaData (indicating a generic connection) is received, and the corresponding
   * connection channel is currently receiving, the SF or FF shall be ignored. */
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  /*When an SF or FF N-PDU with MetaData*/
  #if (STD_ON == CANTP_RX_NPDU_METADATA)
  if ((((uint8)CANTP_SF_PCI == pci) ||((uint8)CANTP_FF_PCI == pci)) &&\
    ((CANTP_TRUE == ptrRxNSdu->InPduwithMetaDataSts) && \
   (NULL_PTR != ptrPduInfo->MetaDataPtr)) &&\
   /*the corresponding connection channel is currently receiving*/
   ((channelRxState == CANTP_RX_CF)||(channelRxState == CANTP_FC_TXCONF))\
   )
  {
    /* @Trace: CanTp_SUD_API_366 */
    /* the SF or FF shall be ignored.*/
  }
  else
  #endif /* (STD_ON == CANTP_RX_NPDU_METADATA) */
  #endif /* End of #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #endif /* End of #ifdef CANTP_DYNID_SUPPORT */
  {
    #ifdef CANTP_DYNID_SUPPORT
    /* Check if Pdu with metaData is configured */
    #if (STD_ON == CANTP_RX_NPDU_METADATA)
    if(CANTP_TRUE == ptrRxNSdu->InPduwithMetaDataSts)
    {
      /* @Trace: CanTp_SUD_API_380 */
      /* @Trace: SWS_CanTp_00330 */
      /* When CanTp_RxIndication is called for a SF or FF N-PDU with MetaData (indicating a generic connection) */
      switch (ptrRxNSdu->AddressingMode)
      {
        #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
        #if (STD_ON == CANTP_RX_EXTENDED_ADDRESS)
        case (uint8)CANTP_EXTENDED_ADDRESS:
        
          /* If  receiver frame is SF or FF,
          * store the addressing information contained into the MetaData
          * to forward to upper layer (only for Pdu is configured with metaData ) */
          if ((CANTP_TRUE == ptrRxNSdu->OutPduwithMetaDataSts) &&\
          (((uint8)CANTP_SF_PCI == pci) ||\
          ((uint8)CANTP_FF_PCI == pci)))
          {
            /* @Trace: CanTp_SUD_API_142 */
            /* Indicate that metaData available for Extended */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;
            /* Store N_TA to local metaData buffer */
            #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
            ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO] = wordAccess.byte_val.MSByte;
            ptrChannelRam->UpMetaData[(uint8)CANTP_ONE] = wordAccess.byte_val.LSByte;
            #else
            ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO] = wordAccess.byte_val.LSByte;
            ptrChannelRam->UpMetaData[(uint8)CANTP_ONE] = wordAccess.byte_val.MSByte;
            #endif
          }
          else
          {
            /* @Trace: CanTp_SUD_API_143 */
            /* Do nothing */
          }
          break;
        #endif /* #if (STD_ON == CANTP_RX_EXTENDED_ADDRESS) */
        #if (STD_ON == CANTP_RX_MIXED_ADDRESS)
        case (uint8)CANTP_MIXED_ADDRESS:
        
          /* @Trace: CanTp_SUD_API_144 */
          /* If  receiver frame is SF or FF,
          * store the addressing information contained into the MetaData
          * to forward to upper layer (only for Pdu is configured with metaData ) */
          if ((CANTP_TRUE == ptrRxNSdu->OutPduwithMetaDataSts) &&\
          (((uint8)CANTP_SF_PCI == pci) ||\
          ((uint8)CANTP_FF_PCI == pci)))
          {
            /* @Trace: CanTp_SUD_API_145 */
            /* Indicate that metaData available for Mixed */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;

            /* Store N_Ae to local metaData buffer
              * to Forward to upper layer.
              * MetaDatalen of Address extension is one byte.
              */
            ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO] =\
                ptrPduInfo->SduDataPtr[(uint8)CANTP_ZERO];
          }
          break;
        #endif /* #if (STD_ON == CANTP_RX_MIXED_ADDRESS) */
        #endif /* STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT */
        #if (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)
        /* With Normal fixed addressing mode.
        * CanTp shall copy metaData which provide by Lower layer (CAN_ID_32)
        * into local to forward to Upper layer.
        * CanTp will copy sequence one byte N_SA, N_TA (in CAN_ID_32)
        * to 2byte SOURCE_ADDRESS_16, TARGET_ADDRESS_16..
        * */
        case (uint8)CANTP_NORMALFIXED_ADDRESS:
        
          /* @Trace: CanTp_SUD_API_148 */
          /* If  receiver frame is SF or FF,
          * store the addressing information contained into the MetaData
          */
          if (((uint8)CANTP_SF_PCI == pci) ||\
            ((uint8)CANTP_FF_PCI == pci))
          {
            /* @Trace: CanTp_SUD_API_146 */
            /* Indicate that metaData available Normalfixed */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;

            /* Use local pointer to access to LometaData*/
            longAccess.WholeLong = (uint32)*((uint32*)&ptrPduInfo->MetaDataPtr[(uint8)CANTP_ZERO]);

            /* Store CAN_ID_32 to local Ram for check CF*/
            ptrChannelRam->LoMetaData.WholeLong = longAccess.WholeLong;

            #if(STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
            /* Don't assign value to UpMetaData when Pdu not configured */
            if(CANTP_TRUE == ptrRxNSdu->OutPduwithMetaDataSts)
            {
                /* @Trace: CanTp_SUD_API_147 */
                /* Point to N_SA in Upper metaData */
                ptrWordAccess = (uint16*)&ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO];

                /* Copy the N_SA first */
                *ptrWordAccess = longAccess.byte_val.LSByte;

                /* Point to N_TA in Upper metaData */
                ptrWordAccess = (uint16*)&ptrChannelRam->UpMetaData[(uint8)CANTP_TWO];

                /* Then, copy the N_TA */
                *ptrWordAccess = (uint16)longAccess.byte_val.Byte_1;
            }
            else
            {
              /* Do nothing */
            }
            #endif /* #if(STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
          }
          /* @Trace: SWS_CanTp_00333 */
          /* Check the N_TA in CF with FF */
          else if ((uint8)CANTP_CF_PCI == pci)
          {
            longAccess.WholeLong = (uint32)*((uint32*)&ptrPduInfo->MetaDataPtr[(uint8)CANTP_ZERO]);

            /* Check against N_Sa and N_Ta with metaData of CF if addressing type is Mixed*/
            /* @Trace: CanTp_SUD_API_149 */
            if (ptrChannelRam->LoMetaData.WholeLong != longAccess.WholeLong)
            {
              #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
              invalidMetaData = CANTP_TRUE;
              #endif
            }
          }
          else
          {
            
            /* Do nothing*/
          }
          break;
        #endif /* #if (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) */
        #if (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)
        /* With mixed29 bit addressing mode.
        * CanTp shall copy metaData which provide by Lower layer (CAN_ID_32)
        * and N_Ae into local to forward to Upper layer.
        * CanTp will copy sequence one byte N_SA, N_TA(in CAN_ID_32) and N_Ae
        * to 2byte SOURCE_ADDRESS_16, TARGET_ADDRESS_16. ADDRESS_EXTENSION_8.
        * */
        case (uint8)CANTP_MIXED29BIT_ADDRESS:
          /* @Trace: CanTp_SUD_API_150 */
          /* If  receiver frame is SF or FF,
          * store the addressing information contained into the MetaData
          */
          if (((uint8)CANTP_SF_PCI == pci) ||\
                ((uint8)CANTP_FF_PCI == pci))
          {
            /* @Trace: CanTp_SUD_API_151 */
            /* Indicate that metaData available Mixed29bit */
            ptrChannelRam->AvlMetaDt = CANTP_TRUE;

            /* Use local pointer to access to LometaData*/
            longAccess.WholeLong = (uint32)*((uint32*)&ptrPduInfo->MetaDataPtr[(uint8)CANTP_ZERO]);

            /* Store CAN_ID_32 to local Ram for check CF*/
            ptrChannelRam->LoMetaData.WholeLong = longAccess.WholeLong;

            #if(STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
            /* Don't assign value to UpMetaData when Pdu not configured */
            if(CANTP_TRUE == ptrRxNSdu->OutPduwithMetaDataSts)
            {
              /* @Trace: CanTp_SUD_API_152 */
              /* Point to N_SA in Upper metaData */
              ptrWordAccess = (uint16*)&ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO];

              /* Copy the N_SA first */
              *ptrWordAccess = longAccess.byte_val.LSByte;

              /* Point to N_TA in Upper metaData */
              ptrWordAccess = (uint16*)&ptrChannelRam->UpMetaData[(uint8)CANTP_TWO];

              /* Then, copy the N_TA */
              *ptrWordAccess = (uint16)longAccess.byte_val.Byte_1;

              /* finally, N_Ae is copied */
              ptrChannelRam->UpMetaData[(uint8)CANTP_FOUR] = ptrPduInfo->SduDataPtr[(uint8)CANTP_ZERO];
            }
            else
            {
              /* @Trace: CanTp_SUD_API_153 */
              ptrChannelRam->UpMetaData[CANTP_ZERO] = ptrPduInfo->SduDataPtr[(uint8)CANTP_ZERO];
            }
            #endif
          }
          /* @Trace: SWS_CanTp_00333 */
          /* Check the N_TA in CF with FF */
          else if ((uint8)CANTP_CF_PCI == pci)
          {
            /* @Trace: CanTp_SUD_API_154 */
            longAccess.WholeLong = (uint32)*((uint32*)&ptrPduInfo->MetaDataPtr[(uint8)CANTP_ZERO]);
            /* @Trace: SWS_CanTp_00332 */
            /* Use MetaData from FF to identify an corresponding CF */
            /* Check against N_Sa and N_Ta with metaData of CF if addressing type is Mixed*/
            if ((ptrChannelRam->LoMetaData.WholeLong != longAccess.WholeLong)
            #if(STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
              /*If Pdu (CanTp2PduR) with metaData*/
              ||((CANTP_TRUE == ptrRxNSdu->OutPduwithMetaDataSts) &&
              (ptrChannelRam->UpMetaData[(uint8)CANTP_FOUR] != ptrPduInfo->SduDataPtr[(uint8)CANTP_ZERO]))
              /*If Pdu (CanTp2PduR) without metaData*/
              ||((CANTP_TRUE != ptrRxNSdu->OutPduwithMetaDataSts) &&\
              (ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO] != ptrPduInfo->SduDataPtr[(uint8)CANTP_ZERO]))
            #endif
            )
            {
              /* @Trace: CanTp_SUD_API_155 */
              #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
              invalidMetaData = CANTP_TRUE;
              #endif
            }
          }
          else
          {
            /* Do nothing*/
          }
          break;
        #endif /* #if (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) */
        default: /* CANTP_STANDARD_ADDRESS */
          /* Do nothing*/
          break;
      }  
      /* Prepare MetaData for FC */
      /* Transmit an FC with MetaData */
      #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||\
          (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
      if ((((uint8)CANTP_FF_PCI == pci) &&\
          ((ptrRxNSdu->AddressingMode == CANTP_MIXED29BIT_ADDRESS)||\
          (ptrRxNSdu->AddressingMode == CANTP_NORMALFIXED_ADDRESS))))
      {
        /* @Trace: CanTp_SUD_API_156 */
        /* If receiver Sdu is FF, CanTp shall produces the CAN_ID_32
          * for FC from CAN_ID_32 of FF by swaps N_TA and N_SA */
        /* N_TA of FF is N_SA of FC frame*/
        ptrChannelRam->LoFcMetaData.byte_val.LSByte =\
            ptrChannelRam->LoMetaData.byte_val.Byte_1;

        /* N_SA of FF is N_TA of FC frame*/
        ptrChannelRam->LoFcMetaData.byte_val.Byte_1 =\
              ptrChannelRam->LoMetaData.byte_val.LSByte;

        /* Copy the two remaining byte */
        ptrChannelRam->LoFcMetaData.byte_val.MSByte =\
                ptrChannelRam->LoMetaData.byte_val.MSByte;
        ptrChannelRam->LoFcMetaData.byte_val.Byte_2 =\
                ptrChannelRam->LoMetaData.byte_val.Byte_2;

        /* In case of Mixed29bit the N_Ae shall be copy from UpMetaData to dataBuffer
          * when proceed one transmit FC frame. */
      }
      #endif /* End of (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||\
              (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) */
    } /* if CANTP_TRUE == ptrRxNSdu->InPduwithMetaDataSts */
    #endif /* STD_ON == CANTP_RX_NPDU_METADATA */
    #endif /* End of Dynamic support */

    /* Get the received data length of the PDU */
    receivedDlc = (uint8)(ptrPduInfo->SduLength);
    #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

    /* If support Postbuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Initialize RxNSdu dynamic structure according to RxNSduId */
    ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[rxSduId];
    #else
    /* Initialize RxNSdu dynamic structure according to RxNSduId */
    ptrRxNSduDyna = &CanTp_RxSduDynamic[rxSduId];
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
    #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

    switch (channelRxState)
    {
      case (uint8)CANTP_WAIT:
        /* @Trace: CanTp_SUD_API_157 */
        /* Check if the received frame is SF or FF */
        if (((uint8)CANTP_SF_PCI == pci) || ((uint8)CANTP_FF_PCI == pci))
        {
          /* Start a new reception */ 
          newFrameFlag = CANTP_TRUE;
        }
        break;
      /* Unexpected messages coming while processing one reception */
      case (uint8)CANTP_RX_CF:
        /* @Trace: CanTp_SUD_API_158 */
        #ifdef CANTP_DYNID_SUPPORT
        #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
        #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||\
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
        if (CANTP_TRUE == invalidMetaData)
        {
          /* The reception is completed */
          CanTp_ReceptionComplete(ptrChannelRam,
            (CanTp_NotifResultType)CANTP_E_INVALID_RX_ID);
          /* Reject a new reception */
          newFrameFlag = CANTP_FALSE;
        }
        else
        #endif
        #endif /* End of #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
        #endif /* End of CANTP_DYNID_SUPPORT */
        {
          #if ((STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)&& (STD_ON == CANTP_RX_NSDU))
          newFrameFlag = CanTp_ProcessRxCF(rxSduId, ptrRxSrc,
            ptrPduInfo, channel);
          #endif /* #if(STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)*/
        }
        break;

      case (uint8)CANTP_RXBUF_WAIT:
      case (uint8)CANTP_RX_NORMAL:
      case (uint8)CANTP_FC_TXCONF:

        /* Start one new reception if segmented reception is in progress */
        /* When an SF or FF N-PDU without MetaData is received for another connection (different N_AI)
         * on an active connection channel, the SF or FF shall be ignored. */
        if ((((uint8)CANTP_SF_PCI == pci) || ((uint8)CANTP_FF_PCI == pci)) \
              && (ptrChannelRam->ActivePduId == rxSduId) )
        {
          /* The reception is completed */
          CanTp_ReceptionComplete(ptrChannelRam,
                    (CanTp_NotifResultType)E_NOT_OK);
          /* Start a new reception */
          newFrameFlag = CANTP_TRUE;
        }

        /* Ignore the CF,FC if in transmission progress */
        break;

      default:
        /* Do Nothing */
        break;
    } /* End of switch case */

    /* Check if the new frame is received - Single Frame or First Frame */
    if (CANTP_TRUE == newFrameFlag)
    {
      /* @Trace: CanTp_SUD_API_161 */
      /* Initialize PDuId according to received RX NSduId */
      ptrChannelRam->ActivePduId = rxSduId;
      /* @Trace: SWS_CanTp_00350 */
      /* The received data link layer data length (RX_DL) shall be derived
      * from the first received payload length of the CAN frame/PDU (CAN_DL) as follows
      * + For CAN_DL values less than or equal to eight bytes the RX_DL value shall be eight.
      * + For CAN_DL values greater than eight bytes the RX_DL value equals the CAN_DL value.
      * */
      if ((uint8)CANTP_EIGHT > receivedDlc )
      {
        /* @Trace: CanTp_SUD_API_162 */
        ptrChannelRam->RxDl = (uint8)CANTP_EIGHT;
      }
      else
      {
        /* @Trace: CanTp_SUD_API_163 */
        /* For CAN2.0 and CAN_FD with CANDL >= 8 */
        ptrChannelRam->RxDl = receivedDlc;
      }

      /* Validate the received DLC */
      dlcErrorFlag = CanTp_RxNewframeDlcCheck(ptrRxNSdu,
        (P2CONST(uint8, AUTOMATIC, CANTP_CONST))ptrRxSrc,
        receivedDlc);

      /* Check if no DLC errors are occurred */
      if (dlcErrorFlag == CANTP_FALSE)
      {
        /* @Trace: CanTp_SUD_API_164 */
        /* Update the frame type */
        ptrChannelRam->FrameType = frame;
        #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

        /* Initialize the frame counter for new frame */
        ptrChannelRam->FrameCounter = (uint8)CANTP_ZERO;
        #endif

        /* Update the channel status to Rx Normal for new frame */
        ptrChannelRam->ChannelState = (uint8)CANTP_RX_NORMAL;

        /* Initialize the CanTp local data byte length */
        ptrChannelRam->LocalDataByteIndex = (uint8)CANTP_ZERO;

        /* Update the flow status to new frame */
        ptrChannelRam->NewFrameFlag = (uint8)CANTP_ONE;

        /* Update the buffer length
        * In case of Single Frame */
        if ((uint8)CANTP_SF_PCI == pci)
        {
          #if (CANTP_FD_SUPPORT == STD_ON)
          ptrChannelRam->CurrentFrameLen = (uint8)ptrChannelRam->SduLength;

          /* Store source data address in upper layer buffer pointer */
          if(CANTP_EIGHT >= receivedDlc)
          {
            /* @Trace: CanTp_SUD_API_166 */
            ptrChannelRam->ptrUpLayerBuff = &ptrRxSrc[CANTP_ONE];
          }
          else
          {
            /* @Trace: CanTp_SUD_API_167 */
            ptrChannelRam->ptrUpLayerBuff = &ptrRxSrc[CANTP_TWO];
          }          

          /* Request for a new buffer */
          CanTp_RequestRxBuffer(ptrChannelRam);
          #else
          /* Get the number of data bytes into local buffer */
          ptrChannelRam->CurrentFrameLen = (uint8)ptrChannelRam->SduLength;
                
          /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation */ 
          ptrRxSrc++;

          /* Store source address in channel ptr for upperlayer buffer */
          ptrChannelRam->ptrUpLayerBuff = ptrRxSrc;

          /* Request for a new buffer */
          CanTp_RequestRxBuffer(ptrChannelRam);
          #endif /* end check CANTP_FD_SUPPORT */
        } /* End Single Frame */

        #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
        /* In case of First Frame */
        else
        {
          /* Initialize Channel RAM according to RX NSdu dynamic structure
           * wftmax value */
          ptrChannelRam->RxWftMax = ptrRxNSduDyna->RxWftMax;

          /*Initialize the BS variable to default value*/
          ptrChannelRam->BSVar = (uint8)CANTP_ZERO;
          /* polyspace +3 RTE:NIV [Not a defect:Low] "The value of ptrRxSrc has been gotten from PDU, no impact" */
          /* In case of FF_DL > 4095 Byte */
          if (((uint8)CANTP_ZERO == ptrRxSrc[CANTP_ONE])
              && ((ptrRxSrc[CANTP_ZERO] & (uint8)CANTP_FF_LEN_MASK) == (uint8)CANTP_ZERO))
          {
            /* @Trace: CanTp_SUD_API_169 */
            /* Get the number of data bytes into local buffer */
            ptrChannelRam->CurrentFrameLen = (receivedDlc - bytePosLc) - CANTP_SIX;

            /* Store source data address in upper layer buffer pointer */
            ptrChannelRam->ptrUpLayerBuff = &ptrRxSrc[CANTP_SIX];
          }
          /* In case of FF_DL <= 4095 Byte */
          else
          {
            /* @Trace: CanTp_SUD_API_170 */
            /* Get the number of data bytes into local buffer */
            ptrChannelRam->CurrentFrameLen = (receivedDlc - bytePosLc) - CANTP_TWO;

            /* Store source data address in upper layer buffer pointer */
            ptrChannelRam->ptrUpLayerBuff = &ptrRxSrc[CANTP_TWO];
          }

          /* Request for a new buffer */
          CanTp_RequestRxBuffer(ptrChannelRam);
        } /* End of else */
        #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
      } /* Check if no DLC errors are occurred */
    } /* Check if the new frame is received */
    #endif /* #if ((STD_ON == CANTP_RX_NSDU) */
  } /* @ End of if (((channelState == CANTP_RX_CF)||(channelState == CANTP_FC_TXCONF))\
       &&(((uint8)CANTP_SF_PCI == pci) ||((uint8)CANTP_FF_PCI == pci)))*/
  #if (STD_ON == CANTP_RX_NSDU)
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS)||(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  CANTP_UNUSED_PTR(ptrWordAccess);
  #endif
  #endif /* (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #endif /* ifdef CANTP_DYNID_SUPPORT */
  #endif /* if (STD_ON == CANTP_RX_NSDU) */
} /* End of CanTp_ProcessRxData(PduIdType rxSduId,
   * P2CONST(PduInfoType, AUTOMATIC, CANTP_CONST) ptrPduInfo,
   * P2CONST(CanTp_RxExtPdus, AUTOMATIC, CANTP_CONST) LpExtPduPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) ||
        * (STD_ON == CANTP_RX_NSDU)) */

/*******************************************************************************
** Function Name        : CanTp_ProcessRxCF                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_RxIndication   **
**                        to process the Rx data frame received               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : rxSduId                                             **
**                        ptrRxSrc                                            **
**                        ptrPduInfo                                          **
**                        channel                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : detErrFlag                                          **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                        Function(s) invoked    : CanTp_RxCfDlcCheck         **
**                                                 CanTp_ReceptionComplete    **
**                                                 CanTp_CopyRxFrame          **
*******************************************************************************/
#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01073 SRS_Can_01082 SRS_Can_01066 SRS_Can_01116 */
FUNC(boolean, CANTP_CODE) CanTp_ProcessRxCF(PduIdType rxSduId, P2VAR(
    uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc, P2CONST(PduInfoType, AUTOMATIC,
    CANTP_CONST) ptrPduInfo, CanTp_ChannelType channel)
{
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptRrxSrcLc;
  ptRrxSrcLc = ptrRxSrc;
  uint16 ncrTimer;
  uint8 frameCount;
  uint8 receivedDlc;
  uint8 pci;
  boolean dlcErrorFlag;
  boolean newFrameFlag;

  newFrameFlag = CANTP_FALSE;

  /* Initialize Channel RAM structure according to addressing mode */
  ptrChannelRam = &CanTp_ChannelRxRam[channel];
  /* polyspace +8 RTE:NIV [Not a defect:Low] "The value of ptRrxSrcLc has been gotten from PDU, no impact" */
  /* Decode the N_PCI byte */
  pci = (uint8)((*ptRrxSrcLc) & (uint8)CANTP_PCI_MASK);

  /* Check if the received frame PCI is for Consecutive frame */
  if ((uint8)CANTP_CF_PCI == pci)
  {
    /* Get the consecutive frame sequence number */
    frameCount = (*ptRrxSrcLc) & (uint8)CANTP_FF_LEN_MASK;

    /* Check if the expected*/
    if (ptrChannelRam->FrameCounter < (uint8)CANTP_MAX_FRAME_COUNTER)
    {
      /* @Trace: CanTp_SUD_API_171 */
      /* Expected Frame sequence */
      ptrChannelRam->FrameCounter++;
    }
    else
    {
      /* @Trace: CanTp_SUD_API_172 */
      /* Expected Frame sequence */
      ptrChannelRam->FrameCounter = (uint8)CANTP_ZERO;
    }
    /* Update the flow status to new frame */
    ptrChannelRam->NewFrameFlag = (uint8)CANTP_ZERO;

    /* @Trace: SWS_CanTp_00057 */
    /* Check if the correct Sequence number is received */
    if (frameCount == ptrChannelRam->FrameCounter)
    {
      /* @Trace: CanTp_SUD_API_173 */
      /* Validate the received DLC */
      /* Get the received data length of the PDU */
      receivedDlc = (uint8)(ptrPduInfo->SduLength);

      /* If support PostBuild */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      dlcErrorFlag = CanTp_RxCfDlcCheck(&(Variant_Select->PtrRxNSduStatic)[rxSduId],
                                                 receivedDlc);
      #else
      dlcErrorFlag = CanTp_RxCfDlcCheck(&CanTp_RxSduStatic[rxSduId],
                                                 receivedDlc);
      #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

      if (CANTP_FALSE == dlcErrorFlag)
      {
        /* @Trace: CanTp_SUD_API_174 */
        /*  polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation */
        ptRrxSrcLc++;

        if (((uint16)CANTP_ZERO != ptrChannelRam->BSVar) 
          && (CANTP_INFINITE_BS != ptrChannelRam->BSVar))
        {
          /* Decrement the block size variable */
          ptrChannelRam->BSVar--;
        }
        /* Update the frame type */
        ptrChannelRam->FrameType = (uint8)CANTP_CF_PCI;

        /* Copy the received frame from lower layer */
        CanTp_CopyRxFrame(ptrChannelRam, ptRrxSrcLc);
      } /* @ if(CANTP_FALSE == dlcErrorFlag) */
      else
      {
        /* @Trace: CanTp_SUD_API_175 */
        /* @Trace: SWS_CanTp_00344 */
        /* CanTp shall only accept SF or last CF Rx N-PDUs with a length of eight bytes */
        /* @Trace: SWS_CanTp_00346 */
        /* Abort the ongoing last CF */
        /* Complete the reception */
        CanTp_ReceptionComplete(ptrChannelRam,
          (CanTp_NotifResultType)CANTP_E_PADDING);
      }
      /* Check if the TP message is received completely */
      if ((uint32)CANTP_ZERO == ptrChannelRam->ByteCounter)
      {
        /* @Trace: CanTp_SUD_API_176 */
        /* Update the Tp Buffer status */
        ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;

        /* Invoke upper layer Rx Indication for the ongoing Rx frame */
        CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_OK);
      } /* End of if (CANTP_ZERO == ptrChannelRam->usByteCounter) */
      else
      {
        /* If support PostBuild */
        #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
        ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[rxSduId];
        #else
    	  ptrRxNSduDyna = &CanTp_RxSduDynamic[rxSduId];
        #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

        /* Check if all the CFs are received in the block  */
        if ((uint8)CANTP_ZERO == ptrChannelRam->BSVar)
        {
          /* @Trace: CanTp_SUD_API_178 */
          /* Stop N_Cr timer */
          ncrTimer = (uint16)CANTP_ZERO;

          /* Initialize Channel RAM according to RX NSdu dynamic
           *   structure wftmax value */
          ptrChannelRam->RxWftMax = ptrRxNSduDyna->RxWftMax;
        } /* End of if ((CANTP_ZERO == ptrChannelRam->BSVar) && */
        else
        {
          /* @Trace: CanTp_SUD_API_179 */
          /* Start N_Cr timer */
          ncrTimer = ptrRxNSduDyna->NcrTimeoutValue;
        }
        /* @Trace: SWS_CanTp_00312 */
        /* The CanTp module shall start a time-out N_Cr at each indication of CF
         * reception (except the last one in a block) */
        CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NCR_TIMER,
          ncrTimer);
      } /* if(ptrChannelRam->usByteCounter != CANTP_ZERO) */
    } /* @ if(ptrChannelRam->FrameCounter - framecount) */
    else
    { 
      /* @Trace: CanTp_SUD_API_375 */
      /* @Trace: SWS_CanTp_00314 */ 
      /* Ignore wrong sequence number of
       * the received CF by calling PduR_CanTpRxIndication()\
         with the result E_NOT_OK. */
      /* Expected Frame sequence */
      /* Call the upper layer to abort the reception */
      CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
    }
  } /* @ if(pci == CANTP_CF_PCI) */
  else
  {
	  /* @Trace: CanTp_SUD_API_180 */
    /* @Trace: SWS_CanTp_00124 */
    if ((((uint8)CANTP_SF_PCI == pci) || ((uint8)CANTP_FF_PCI == pci))
    /* When an SF or FF N-PDU without MetaData is received for another
     * connection (different N_AI) on an active connection channel,
     * the SF or FF shall be ignored */
      && (rxSduId == ptrChannelRam->ActivePduId))
    {
      /* @Trace: CanTp_SUD_API_317 */
      #ifndef CANTP_DYNID_SUPPORT
      newFrameFlag = CANTP_TRUE;

      /* The current reception is completed to start new reception */
      CanTp_ReceptionComplete(ptrChannelRam,
            (CanTp_NotifResultType)E_NOT_OK);
      #else /* CANTP_DYNID_SUPPORT is defined. */
      #if (STD_OFF == CANTP_GENERIC_CONNECTION_SUPPORT)
      newFrameFlag = CANTP_TRUE;

      /* The current reception is completed to start new reception */
      CanTp_ReceptionComplete(ptrChannelRam,
            (CanTp_NotifResultType)E_NOT_OK);
      #else
      /* Ignore the SF or FF when generic connection is configured */
      #endif
      #endif
    } /* @ End of if (((uint8)CANTP_SF_PCI == pci) || ((uint8)CANTP_FF_PCI == pci)) */
  } /* @ else if((pci == CANTP_SF_PCI) */

  return (newFrameFlag);
} /* End of CanTp_ProcessRxCF(PduIdType rxSduId, P2VAR( */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
** Function Name        : CanTp_RxDetCheck                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_RxIndication   **
**                        to indicate errors which may be due to invalid      **
**                        input data, or data length or buffer                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : rxPduId                                             **
**                        ptrPduInfo                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : detErrFlag                                          **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                                                 Cantp_Max_Indic_Id         **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, CANTP_CODE) CanTp_RxDetCheck(PduIdType rxPduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_VAR) ptrPduInfo)
{
  boolean detErrFlag = CANTP_FALSE;

  #ifdef CANTP_DYNID_SUPPORT
  #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
        (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
  P2CONST(CanTp_RxExtPdusType, AUTOMATIC, CANTP_CONST) ptrRxExtPdu;
  #endif
  #endif
  /* polyspace +11 RTE:UNR [Not a defect:Low] "according to requirements, CanTp init status should be checked before any further processing" */
  /* Call CanTp_Init before using the CanTp module for further processing */
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* @Trace: CanTp_SUD_API_182 */
    /* Report to DET */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_UNINIT);
    detErrFlag = CANTP_TRUE;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  if ((rxPduId > (PduIdType)CANTP_MAX_INDIC_ID) &&
      (CANTP_FALSE == detErrFlag))
  {
    /* @Trace: CanTp_SUD_API_183 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_INVALID_RX_ID);
    detErrFlag = CANTP_TRUE;
  } /* @ End of if ((rxPduId > (PduIdType)CANTP_MAX_INDIC_ID) &&
      (CANTP_FALSE == detErrFlag)) */
  /* polyspace +10 RTE:UNR [Not a defect:Low] "It depends on the configuration of CanTp, no impact" */
  /* @Trace: SWS_CanTp_00322 */
  /* The argument PduInfoPtr is a NULL pointer */
  if ((NULL_PTR == ptrPduInfo) && (CANTP_FALSE == detErrFlag))
  {
    /* @Trace: CanTp_SUD_API_184 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_PARAM_POINTER);
    detErrFlag = CANTP_TRUE;
  } /* End of if (NULL_PTR == ptrPduInfo) */
  else
  {
	  /* @Trace: CanTp_SUD_API_185 */
    if (CANTP_FALSE == detErrFlag)
    {
      /* @Trace: CanTp_SUD_API_258 */
      /* Check if the received data buffer is NULL pointer */
      /* polyspace +18 RTE:UNR [Not a defect:Low] "the value received from external sources should be checked" */
      /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "By passed the condition (NULL_PTR == ptrPduInfoPt), the value received from external sources already checked." */
      if (NULL_PTR == ptrPduInfo->SduDataPtr)
      {
        /* @Trace: CanTp_SUD_API_187 */
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_PARAM_POINTER);
        detErrFlag = CANTP_TRUE;
      } /* End of if (NULL_PTR == ptrPduInfo->SduDataPtr) */

      /* Check if the data length is invalid */
      if ((uint16)CANTP_ZERO == ptrPduInfo->SduLength)
      {
        /* @Trace: CanTp_SUD_API_188 */
        /* Report to DET */
        (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_PADDING);
        detErrFlag = CANTP_TRUE;
      } /* End of if (CANTP_ZERO == ptrPduInfo->SduLength) */
    } /* End of if (CANTP_FALSE == detErrFlag) */
  } /* if ptrPduInfo is not NULL_PTR */

  #ifdef CANTP_DYNID_SUPPORT 
  #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
        (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  ptrRxExtPdu = &(Variant_Select->PtrRxExtPdus)[rxPduId];
  #else
  ptrRxExtPdu = &CanTp_RxExtPdus[rxPduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  if ((CANTP_FALSE == detErrFlag) &&\
	  (CANTP_MIXED29BIT_ADDRESS <= ptrRxExtPdu->AddressingMode))
  {
	  /* @Trace: CanTp_SUD_API_189 */ 
    if ((NULL_PTR == ptrPduInfo->MetaDataPtr)&&(CANTP_TRUE == ptrRxExtPdu->InPduwithMetaDataSts))
    {
        /* @Trace: CanTp_SUD_API_190 */
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_PARAM_POINTER);
        detErrFlag = CANTP_TRUE;
    }
  }
  #endif
  #endif

  return (detErrFlag);
} /* End of CanTp_RxDetCheck(PduIdType rxPduId, P2CONST(PduInfoType, AUTOMATIC,
   * CANTP_VAR) ptrPduInfoPt) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : CanTp_TxConfirmation                                **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : This function is called by the CAN Interface after  **
**                        successful transmission of a Rx CAN N-PDU.          **
**                        This callback service is called by the CanIf and    **
**                        implemented by the CanTp                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant for   **
**                        the same PduId.                                     **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                        result                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 CanTp_TxSduStatic,         **
**                                                 CanTp_ChannelMode,         **
**                                                 CanTp_ChannelRam,          **
**                                                 CanTp_StMinTimers,         **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : CanTp_CbkTxDetCheck        **
**                                                 CanTp_TransmissionComplete **
*******************************************************************************/
#if ((STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) || (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01081 */
FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType txPduId, Std_ReturnType result)
{
  #if (STD_ON == CANTP_TX_NSDU)
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu = NULL_PTR;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  #endif
  #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
  uint16 narTimerValue;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  CanTp_ChannelType channel;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  uint8 txConfirmState;
  uint8 channelState;
  #endif
  #if (STD_ON == CANTP_TX_NSDU)
  uint8 actualChan;
  #endif

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  boolean detErrorFlag;

  /* DET error check */
  detErrorFlag = CanTp_CbkTxDetCheck(txPduId);

  /* Check whether Det Error occured */
  if (CANTP_FALSE == detErrorFlag)
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanTp_SUD_API_191 */
    #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
    /* polyspace +5 RTE:OBAI [Not a defect:Low] "It is covered by generation so, This warning not impact." */
    /* polyspace +4 MISRA-C3:D4.14 [Not a defect:Low] "The value of txPduId variable is checked in CanTp_CbkTxDetCheck() function. Thus, the error related to "Index may be negative or too big" is not occur" */
    #if (CANTP_VARIANT_POSTBUILD_SUPPORT == STD_ON)
    channel = (CanTp_ChannelType)((Variant_Select->PtrRxSduMap)[txPduId]);
    #else
    channel = (CanTp_ChannelType)(CanTp_RxSduMap[txPduId]);
    #endif

    /* polyspace-end RTE:OBAI [Not a defect:Low] "configured memory access index"*/

    /* Get the channel ram according to transmit or receive channel */
    ptrChannelRam = &CanTp_ChannelRxRam[channel];

    /* Assign Tx confirm state according to channel RAM */
    txConfirmState = ptrChannelRam->TxConfirmState;

    /* Initialize Channel state according RAM structure Channel */
    channelState = ptrChannelRam->ChannelState;

    /* Check whether the confirmation is awaited for FC Frame */
    if ((uint8)CANTP_FC_TX_CONF == txConfirmState)
    {
      /* @Trace: CanTp_SUD_API_192 */
      if (channelState != CANTP_WAIT)
      {
        /* @Trace: CanTp_SUD_API_193 */
        /* @Trace: SWS_CanTp_00355 */
        /* CanTp shall abort the correcsponding session,
         * when CanTp_TxConfirmation() is called with the result E_NOT_OK */
        if (E_NOT_OK != result)
        {
          /* @Trace: CanTp_SUD_API_194 */
          /* Stop N_Ar timer */
          narTimerValue = (uint16)CANTP_ZERO;

          /* Update the Channel Confirmation State */
          ptrChannelRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;

          /* Check whether FS is continue to send */
          if ((uint8)CANTP_FS_CTS == ptrChannelRam->FlowStatus)
          {
            /* @Trace: CanTp_SUD_API_195 */
            /* Change the channel state */
            ptrChannelRam->ChannelState = (uint8)CANTP_RX_CF;

            /* @Trace: SWS_CanTp_00312 */
            /* Start N_Cr timer at each confirmation of a FC transmission with FS=CTS */
            /* polyspace-begin RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined " */
            /* If support PostBuild */
            #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
            CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NCR_TIMER,
              (Variant_Select->PtrRxNSduDynamic)[ptrChannelRam->ActivePduId].NcrTimeoutValue);
            #else
            CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NCR_TIMER,
              CanTp_RxSduDynamic[ptrChannelRam->ActivePduId].NcrTimeoutValue);
            #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

            /* polyspace-end RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined "*/
          } /* @
            * if(ptrChannelRam->ucFlowStatus == CANTP_FS_CTS)
            * Reload N_Ar Timer
            */
          CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NAR_TIMER, narTimerValue);
        }
        else
        {
          /* @Trace: CanTp_SUD_API_196 */
          CanTp_ReceptionComplete(ptrChannelRam, E_NOT_OK);
        }
      }
    } /*
       * if(txConfirmState == CANTP_FC_TX_CONF)
       * End of confirmation is over for FcNpdu
       */
    #endif /* #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    /* If FC confirmation is not awaited , check for Tx confirmations */
    #if ((STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (STD_ON == CANTP_TX_NSDU))
    else
    #endif
    {
      /* @Trace: CanTp_SUD_API_197 */
      /* Check if confirmation is for TxNpdu */
      #if (STD_ON == CANTP_TX_NSDU)

      /* If support PostBuild */
      #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
      /* Get the Tp Tx Nsdu structure */
      ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[txPduId];
      #else
      /* Get the Tp Tx Nsdu structure */
      ptrTxNSdu = &CanTp_TxSduStatic[txPduId];
      #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

      /* polyspace:begin<RTE: IDP : Not a defect : Low > Its bound is pre-defined */
      /* Get the connection channel structure address */
      channel = ptrTxNSdu->ChannelId;

      /* Get ID for Tx ChannelRam */
      actualChan = CanTp_ChannelMapping[channel];

      /* Get channel ram*/
      ptrChannelRam = &CanTp_ChannelTxRam[actualChan];

      /* Initialize Channel state according RAM structure Channel */
      channelState = ptrChannelRam->ChannelState;

      if (channelState != CANTP_WAIT)
      {
        /* @Trace: CanTp_SUD_API_198 */
        /* @Trace: SWS_CanTp_00355 */
        /* CanTp shall abort the correcsponding session,
         * when CanTp_TxConfirmation() is called with the result E_NOT_OK */
        if (E_NOT_OK != result)
        {
          CanTp_TxConfirmationErrorCheck(channel);
        }
        else
        {
          /* @Trace: CanTp_SUD_API_207 */
          CanTp_TransmissionComplete(ptrChannelRam, E_NOT_OK);
        }
      } /* Check channelState != CANTP_WAIT */
      #endif /* #if (STD_ON == CANTP_TX_NSDU) */
    }
  } /* No DET Error */
} /* End of CanTp_TxConfirmation(PduIdType TxPduId) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif 
/*******************************************************************************
** Function Name        : CanTp_CbkTxDetCheck                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_TxConfirmatiom **
**                        to indicate errors which may be due to invalid      **
**                        input data, or data length or buffer                **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : detErrFlag                                          **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                                                 Cantp_Max_Confirm_Id       **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CANTP_CODE) CanTp_CbkTxDetCheck(PduIdType txPduId)
{
  boolean detErrFlag;
  detErrFlag = CANTP_FALSE;
  /* polyspace +13 RTE:UNR [Not a defect:Low] "according to requirements, CanTp init status should be checked before any further processing" */
  /* If module is not initialise */
  /* @Trace: SWS_CanTp_00199 */
  /* Call CanTp_Init before using the CanTp module for further processing */
  if (CANTP_FALSE == CanTp_InitStatus)
  {
    /* @Trace: CanTp_SUD_API_208 */
    /* Report to DET */
    /* @Trace: SWS_CanTp_00031 */
    /* Enabled the CanTp module shall raise an error (CANTP_E_UNINIT) */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_UNINIT);
    detErrFlag = CANTP_TRUE;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */
  /* polyspace +1 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
  if (CANTP_FALSE == detErrFlag)
  {
	  /* @Trace: CanTp_SUD_API_209 */
    /* polyspace +1 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
    if (txPduId > (PduIdType)CANTP_MAX_CONFIRM_ID)
    {
      /* @Trace: CanTp_SUD_API_210 */
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_ID);
      detErrFlag = CANTP_TRUE;
    } /* End of if (txPduId > (PduIdType)CANTP_MAX_CONFIRM_ID) */
  } /* End of if (CANTP_FALSE == detErrFlag) */
  return (detErrFlag);
} /* End of CanTp_CbkTxDetCheck(PduIdType TxPduID) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : CanTp_TxConfirmationErrorCheck                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_TxConfirmation **
**                        to indicate errors which may be due to invalid      **
**                        input data, or data length or buffer                **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : detErrFlag                                          **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                                                 Cantp_Max_Confirm_Id       **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_TxConfirmationErrorCheck(CanTp_ChannelType channel)
{
  /* @Trace: CanTp_SUD_API_199 */
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  uint8 txConfirmState;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  #endif
  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  uint8 npciPos;
  #endif
  #if (STD_ON == CANTP_TX_NSDU)
  uint8 actualChan;
  #endif

  ptrChannelRam = &CanTp_ChannelTxRam[channel];
  actualChan = CanTp_ChannelMapping[channel];

  /* Assign Tx confirm state according to channel RAM */
  txConfirmState = ptrChannelRam->TxConfirmState;

  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  /* Get the current addressing */
  npciPos = ptrChannelRam->CurrentBytePosition;

  #if(STD_ON == CANTP_DEV_ERROR_DETECT)
  if(npciPos > (ptrChannelRam->CurrentFrameLen - CANTP_ONE))
  {
    /* @Trace: CanTp_SUD_API_200 */    
    /* Report to DET */
    (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_PADDING);
  }
  else if(ptrChannelRam->ActivePduId > CANTP_MAX_TX_SDUID )
  {
    /* @Trace: CanTp_SUD_API_201 */
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_ID);
  }
  else
  #endif
  #endif
  {
    /* @Trace: CanTp_SUD_API_202 */
    /* Check FC confirmation is not awaited  */
    if (txConfirmState != (uint8)CANTP_TX_CONF_IDLE)
    {
      /* @Trace: CanTp_SUD_API_203 */
      /* Check if the Tx confirmation is for SF or last frame of TP message */
      if ((uint8)CANTP_SF_LF_TX_CONF == txConfirmState)
      {
        /* @Trace: CanTp_SUD_API_316 */
        /* @Trace: SWS_CanTp_00090 */ 
        /* When the transport transmission session is successfully completed */
          /* Process the transmission complete function */
        CanTp_TransmissionComplete(ptrChannelRam, (CanTp_NotifResultType)E_OK);

        /* Clear N_As Timer  */
        CANTP_TIMER_UPDATE_MACRO(actualChan, CANTP_NAS_TIMER,
          ((uint16)CANTP_ZERO));
      } /* End of if (CANTP_SF_LF_TX_CONF == txConfirmState) */
      #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

      /* Check if the Tx confirmation is for FF or last CF of a block */
      else if ((uint8)CANTP_CF_TX_CONF == txConfirmState)
      {
        SchM_Enter_CanTp_TIMER_PROTECTION();
        /* @Trace: CanTp_SUD_API_204 */
        /* Update the N_PCI byte */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "The maximum value of npciPos is assigned equal maximum of CanTp_BytePos[ptrRxNSdu->AddressingMode] is 4, but array DataBuffe[]r is declared with array index is CANTP_EIGHT. So, This warning not impact." */
        ptrChannelRam->DataBuffer[npciPos] =
          (ptrChannelRam->FrameCounter | (uint8)CANTP_CF_PCI);

        /* Update the Frame Type */
        ptrChannelRam->FrameType = CANTP_CF_PCI;

        /* Start STmin timer */
        /* Redmine 11124 */
        CanTp_StMinTimers[actualChan] = ptrChannelRam->StMinValue;

        /* Set the channel buffer state to request the buffer */
        ptrChannelRam->BufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;
        SchM_Exit_CanTp_TIMER_PROTECTION();
        /* Clear N_As Timer  */
        CANTP_TIMER_UPDATE_MACRO(actualChan, CANTP_NAS_TIMER,
          (uint16)CANTP_ZERO);
      } /*
        * else if(txConfirmState == CANTP_CF_TX_CONF)
        * Check if the Tx confirmation is for last CF of a block
        */
      else
      {
        /* @Trace: CanTp_SUD_API_205 */
        if ((uint8)CANTP_LAST_CF_TX_CONF == txConfirmState)
        {
          /* @Trace: CanTp_SUD_API_206 */
          /* Update the N_PCI byte */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "The maximum value of npciPos is assigned equal maximum of CanTp_BytePos[ptrRxNSdu->AddressingMode] is 4, but array DataBuffe[]r is declared with array index is CANTP_EIGHT. So, This warning not impact." */
          ptrChannelRam->DataBuffer[npciPos] =
            (ptrChannelRam->FrameCounter | (uint8)CANTP_CF_PCI);

          /* Update the Frame Type */
          ptrChannelRam->FrameType = CANTP_CF_PCI;

          /* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > Its boundary is pre-defined */
          /* @Trace: SWS_CanTp_00315 */
          /* Start N_Bs timer after confirmation of last CF or FF */

          SchM_Enter_CanTp_TIMER_PROTECTION();
          /* If support PostBuild */
          #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
          CANTP_TIMER_UPDATE_MACRO(actualChan, CANTP_NBS_TIMER,
            (Variant_Select->PtrTxNSduDynamic)[ptrChannelRam->ActivePduId].NbsTimeoutValue);
          #else
          CANTP_TIMER_UPDATE_MACRO(actualChan, CANTP_NBS_TIMER,
            CanTp_TxSduDynamic[ptrChannelRam->ActivePduId].NbsTimeoutValue);
          #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
          SchM_Exit_CanTp_TIMER_PROTECTION();

          /* polyspace-end RTE:OBAI [Not a defect:Low] "Its bound is pre-defined"*/
          /* Set channel state to "waiting for Rx indication for FC" */
          ptrChannelRam->ChannelState = (uint8)CANTP_RX_FC;

          /* Clear N_As Timer  */
          CANTP_TIMER_UPDATE_MACRO(actualChan, CANTP_NAS_TIMER,
            (uint16)CANTP_ZERO);
        } /* End of if (CANTP_LAST_CF_TX_CONF == txConfirmState) */
      } /* Frame is of type FF or CF */
      #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
    } /* Check that confirmation state is Tx flow control or Tx Ideal */
  }
}
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

