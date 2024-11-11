/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm_IntFunc.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : APIs implementation for CanNm module                          **
**            CanNm_IntCollectTxData                                          **
**            CanNm_IntGetChannelIndexFromTransmitHandleId                    **
**            CanNm_IntGetChannelIndexFromNmHandleId                          **
**            CanNm_IntUpdateERA                                              **
**            CanNm_IntUpdateEIRA                                             **
**            CanNm_IntCanIfTransmit                                          **
**            (void)Det_ReportError                                           **
**            CanNm_IntGetChannelIdFromCanNmTxConfirmationHandleId            **
**            CanNm_IntGetChannelIdFromCanNmRxIndicationHandleId              **
**            CanNm_IntGetChannelIdFromTriggerTransmitHandleId                **
**            CanNm_IntGetRxHandlingMethod                                    **
**            CanNm_IntProcessMsgTimeOutTime                                  **
**            CanNm_IntGetNmStateTypeFromCanNmModeState                       **
**            CanNm_IntStateChangeNotification                                **
**            CanNm_IntNetworkModeEntry                                       **
**            CanNm_IntEntryRepeatMessageState                                **
**            CanNm_IntEntryNormalOperationState                              **
**            CanNm_IntEntryReadySleepState                                   **
**            CanNm_IntEntryPrepareBusSleepMode                               **
**            CanNm_IntEntryBusSleepMode                                      **
**            CanNm_IntExitNetworkMode                                        **
**            CanNm_IntExitRepeatMessageState                                 **
**            CanNm_IntExitNormalOperationState                               **
**            CanNm_IntExitReadySleepState                                    **
**            CanNm_IntExitPrepareBusSleepMode                                **
**            CanNm_IntPrepareBusSleepMode                                    **
**            CanNm_IntReadySleepState                                        **
**            CanNm_IntNormalOperationState                                   **
**            CanNm_IntRepeatMessageState                                     **
**            CanNm_IntProcessEIRATimer                                       **
**            CanNm_IntProcessERATimer                                        **
**            CanNm_IntProcessNmMessage                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By         Description                            **
********************************************************************************
** 1.2.0_HF1  08-Mar-2024   JH Yang    CP44 #3241                             **
** 1.2.0      22-Feb-2024   JH Kim     CP44 #3027, #3894, #3754               **
** 1.1.5      28-Apr-2023   NamNT1     CP44 #1725                             **
** 1.1.4      31-Jan-2023   NamNT1     CP44 #1151, #1098, #873, #1471,        **
                                       #1472                                  **
** 1.1.1      07-Oct-2022   NamNT1     CP44 #785, #786, #610, #838, #842      **
**                                     #887                                   **
** 1.1.0      09-Jun-2022   SMKwon     R44-Redmine #28017                     **
** 1.0.2.1    20-Jun-2022   SM Kwon    CP44-120                               **
** 1.0.2      29-Apr-2022   ThuanVT    R44-Redmine #25513, #25678             **
** 1.0.1      15-Mar-2022   TuanNLH    R44-Redmine #17009, #17463             **
** 1.0.0      16-Dec-2020   SHKim      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanNm_IntFunc.h"        /* CanNm Internal functions header file */
#include "CanNm.h"                /* CanNm APIs header */

#include "SchM_CanNm.h"           /* Schedule Manager header */

#include "PduR_CanNm.h"           /* PduR Header File */

#include "CanIf.h"                /* CanIf Header File */

#include "Nm.h"                   /* Nm Header */

#include "Det.h"                   /* Nm Header */

#include "CanSM_CanIf.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANNM_INTFUNC_C_AR_RELEASE_MAJOR_VERSION    (0x04u)
#define CANNM_INTFUNC_C_AR_RELEASE_MINOR_VERSION    (0x04u)
#define CANNM_INTFUNC_C_AR_RELEASE_REVISION_VERSION (0x00u)

/* CanNm software version information */
#define CANNM_INTFUNC_C_SW_MAJOR_VERSION            (0x01u)
#define CANNM_INTFUNC_C_SW_MINOR_VERSION            (0x02u)
#define CANNM_INTFUNC_C_SW_PATCH_VERSION            (0x00u)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (CANNM_AR_RELEASE_MAJOR_VERSION != CANNM_INTFUNC_C_AR_RELEASE_MAJOR_VERSION)
#error "CanNm_IntFunc.c : Mismatch in Specification Major Version"
#endif

#if (CANNM_AR_RELEASE_MINOR_VERSION != CANNM_INTFUNC_C_AR_RELEASE_MINOR_VERSION)
#error "CanNm_IntFunc.c : Mismatch in Specification Minor Version"
#endif

#if (CANNM_AR_RELEASE_REVISION_VERSION != CANNM_INTFUNC_C_AR_RELEASE_REVISION_VERSION)
#error "CanNm_IntFunc.c : Mismatch in Specification Revision Version"
#endif

#if (CANNM_SW_MAJOR_VERSION != CANNM_INTFUNC_C_SW_MAJOR_VERSION)
#error "CanNm_IntFunc.c : Mismatch in Software Major Version"
#endif

#if (CANNM_SW_MINOR_VERSION != CANNM_INTFUNC_C_SW_MINOR_VERSION)
#error "CanNm_IntFunc.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define CANNM_START_SEC_CODE
#include "MemMap.h"

#if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_IntCollectTxData                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Update Tx Data                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : canNmChannelIndex                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_Memcpy                                        **
*******************************************************************************/
/* @Trace: SRS_Nm_02505 SRS_Nm_02503 */
FUNC(void, CANNM_CODE) CanNm_IntCollectTxData(uint32 canNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Initial data */
  uint8 txUserData[CANNM_MAX_PDU_SIZE];

  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  
  PduInfoType userDataPduInfo;

  /* Point the SduDataPtr to the user data address of the TxUserData array */
  userDataPduInfo.SduDataPtr = &txUserData[ptrStaticChannel->userDataPosition];

  /* Copy the PduLength into the SduLength */
  userDataPduInfo.SduLength = ptrStaticChannel->userDataLength;

  if (E_OK == PduR_CanNmTriggerTransmit(ptrStaticChannel->txTriggerUserPduId, &userDataPduInfo))
  {
    /* @Trace: CanNm_SUD_API_165 */
    (void)CanNm_Memcpy(&(ptrChannel->txUserData[ptrStaticChannel->userDataPosition]),
                      userDataPduInfo.SduDataPtr,
                      userDataPduInfo.SduLength);
  }
  else
  {
      /* keep as current user data */
  }
}
#endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_InternalGetCanNmChannelIndexFromCanNmTransmit **
**                        HandleId                                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get CanNmChannelIndex                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NmHandleId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : CanNmChannelIndex                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIndexFromTransmitHandleId(
  PduIdType canNmTransmitHandleId,
  P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex)
{
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #else
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  Std_ReturnType returnValue = E_NOT_OK;
  uint32 arrIdx;

  /* Searching matched value for PduId */
  /* polyspace +1 MISRA2012:14.2 [Justified:Low] "canNmChannelIndex have been reviewed, no overflow here" */
  for (arrIdx = CANNM_ZERO; (E_OK != returnValue) && (arrIdx < CANNM_NUMBER_OF_CHANNEL); arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_166 */
    /* Get channel configuration data*/
    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    ptrPostBuildChannel = &CanNm_ChannelsDataPtr[*ptrCanNmChannelIndex];
    #else
    ptrStaticChannel = &CanNm_ArrayStaticChannel[arrIdx];
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */

    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    if (ptrPostBuildChannel->canNmTransmitHandleId == canNmTransmitHandleId)
    #else
    if (ptrStaticChannel->canNmTransmitHandleId == canNmTransmitHandleId)
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
    {
      /* @Trace: CanNm_SUD_API_167 */
      *ptrCanNmChannelIndex = arrIdx;
      returnValue = E_OK;
    }
    else
    {
      /* Do nothing */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_IntGetChannelIndexFromNmHandleId              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get CanNmChannelIndex                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NmHandleId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : CanNmChannelIndex                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIndexFromNmHandleId(
    NetworkHandleType nmHandleId,
    P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 arrIdx;

  /* polyspace +1 MISRA2012:14.2 [Justified:Low] "canNmChannelIndex have been reviewed, no overflow here" */
  for (arrIdx = CANNM_ZERO; (E_OK != returnValue) && (arrIdx < CANNM_NUMBER_OF_CHANNEL); arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_168 */
    /* Get channel configuration data */
    ptrStaticChannel = &CanNm_ArrayStaticChannel[arrIdx];

    if (ptrStaticChannel->comMChannelId == nmHandleId)
    {
      /* @Trace: CanNm_SUD_API_169 */
      *ptrCanNmChannelIndex = arrIdx;
      returnValue = E_OK;
    }
    else
    {
      /* Do nothing */
    }
  }

  return returnValue;
}

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_IntUpdateERA                                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Update ERA                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrPnInfo                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ChannelsDataPtr                               **
**                        CanNm_PnFilterMaskBytesPtr                          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        PduR_CanNmRxIndication                              **
*******************************************************************************/
/* @Trace: SRS_Nm_02523 */
FUNC(void, CANNM_CODE) CanNm_IntUpdateERA(
  uint32 canNmChannelIndex, 
  P2CONST(uint8, AUTOMATIC, CANNM_CONST) ptrPnInfo)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2VAR(CanNm_TimeType, AUTOMATIC, CANNM_VAR) ptrTimer;

  uint8 arrIdx;
  boolean eRAChange = CANNM_FALSE;
  /* Buffer to store the previous ERA data */
  uint8 prevERA;
  /* Mask of PN */
  uint8 mask;
  /* PN timeout timer */
  uint8 pnTimer;
  /* PN ERA result value */
  uint8 setERA;
  PduInfoType pnPduInfo;

  /* Variable for PN timer */
  uint16 pnTimerBit;

  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  if (CANNM_TRUE == ptrStaticChannel->pnEraCalcEnabled)
  {
    /* Loop through all the PN bytes configured */
    for (arrIdx = CANNM_ZERO; arrIdx < CanNm_structPnInfo.pnInfoLength; arrIdx++)
    {
      /* @Trace: CanNm_SUD_API_170 */    
      /* Get the ERA array to local variable */
      /* ERA only need to store the era pnc status bits. Not the bytes before pnc informations. */
      prevERA = ptrChannel->eRA[arrIdx];

      /* Take the PN mask byte into local variable */
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      mask = CanNm_PnFilterMaskBytesPtr[arrIdx];
      #else
      mask = CanNm_ArrayPnMaskByte[arrIdx];
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

      /* Check if message contains Partial NW information */
      if (CANNM_ZERO != mask)
      {
        /* @Trace: CanNm_SUD_API_171 */
        /* Check if PN enabled using the mask byte */
        /* polyspace +3 RTE:IDP [Justified:Low] "CanNm_structPnInfo.pnInfoOffset have been generated and checked by generation tool so pointer can not be outside" */
        /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "CanNm_structPnInfo.pnInfoOffset have been generated and checked by generation tool so pointer can not be outside" */
        /* polyspace +1 MISRA2012:18.1 [Justified:Low] "CanNm_structPnInfo.pnInfoOffset have been generated and checked by generation tool so pointer can not be outside" */
        setERA = ptrPnInfo[(CanNm_structPnInfo.pnInfoOffset + arrIdx)] & mask;

        /* Loop through all the eight bits of each PN byte */
        for (pnTimer = CANNM_ZERO; pnTimer < CANNM_EIGHT; pnTimer++)
        {
          /* @Trace: CanNm_SUD_API_172 */
          pnTimerBit = (((uint16)arrIdx * (uint16)CANNM_EIGHT) + ((uint16)CANNM_SEVEN - (uint16)pnTimer));
          /* Check if any bit set */
          if (CANNM_ZERO != (setERA & CANNM_ONE))
          {
            /* @Trace: CanNm_SUD_API_173 */
            /* Get the pointer to timer channel arrIdx */
            ptrTimer = &ptrChannel->eRATimer[pnTimerBit];
  
            /* Load the timer value for each bit that is set */
            *ptrTimer = CANNM_PN_RESET_TIME;
          }
          else
          {
            /* Do nothing */
          }

          /* @Trace: CanNm_SUD_API_174 */
          /* Check for the next bit */
          setERA = (setERA >> CANNM_ONE);
        }
      }
      else
      {
        /* Do nothing */
      }

      /* Check if there's any change in the received PN data 
         => We just need to check if a pnc status is changed from released(0) to requested(1) from received value
         => Refer to SWS_CanNm_00437. CanNm do not care about received value '0'. */
      if (prevERA != (prevERA | (ptrPnInfo[(CanNm_structPnInfo.pnInfoOffset + arrIdx)] & mask)))
      {
        /* @Trace: CanNm_SUD_API_175 */
        /* Set the flag in order to indicate the change to upper layer */
        eRAChange = CANNM_TRUE;
        /* We have to "OR" the information, because we should not apply received '0' value to the stored value.*/
        ptrChannel->eRA[arrIdx] |= ptrPnInfo[(CanNm_structPnInfo.pnInfoOffset + arrIdx)];
      }
      else
      {
        /* Do nothing */
      }
    }

    /* Check if there is change in any byte of the received PN data */
    if (CANNM_TRUE == eRAChange)
    {
      /* @Trace: CanNm_SUD_API_177 */
      /* Assign the PDU Length */
      pnPduInfo.SduLength = CanNm_structPnInfo.pnInfoLength;
      /* Assign the base address of the PDU */
      pnPduInfo.SduDataPtr = &ptrChannel->eRA[CANNM_BYTE0];
      /* Assign data for metadata*/
      if(ptrChannel->rxMetaDataCheck == CANNM_TRUE)
      {
        /* @Trace: CanNm_SUD_API_178 */
        pnPduInfo.MetaDataPtr = &ptrChannel->rxMetaData[CANNM_BYTE0];
      }
      else
      {
        /* @Trace: CanNm_SUD_API_179 */
        pnPduInfo.MetaDataPtr = NULL_PTR;
      }

      /* @Trace: CanNm_SUD_API_180 */
      /* Invoke the upper layer with the changed data */
      PduR_CanNmRxIndication(ptrStaticChannel->pnEraRxNSduHandleId, &pnPduInfo);
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    /* Do nothing */
  }
}
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_IntUpdateEIRA                                 **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Update EIRA                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrPnInfo                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ChannelsDataPtr                               **
**                        CanNm_PnFilterMaskBytesPtr                          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        PduR_CanNmRxIndication                              **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntUpdateEIRA(
  P2CONST(uint8, AUTOMATIC, CANNM_CONST) ptrPnInfo)
{
  P2VAR(CanNm_TimeType, AUTOMATIC, CANNM_VAR) ptrTimer;

  uint16 arrIdx;
  boolean eIRAChange = CANNM_FALSE;
  /* Buffer to store the previous EIRA data */
  uint8 prevEIRA;
  /* Mask of PN */
  uint8 mask;
  /* PN timeout timer */
  uint8 pnTimer;
  /* PN EIRA result value */
  uint8 setEIRA;
  PduInfoType pnPduInfo;
  /* EIRA Sdu handle ID */
  PduIdType pnEiraRxNSduHandleId;
  /* Variable for PN timer */
  uint16 pnTimerBit;


  /* Loop through all the PN bytes configured */
  for (arrIdx = CANNM_ZERO; arrIdx < CanNm_structPnInfo.pnInfoLength; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_262 */
    /* Get the EIRA array to local variable */
    /* EIRA array should store only EIRA pnc status, not the bytes before */
    SchM_Enter_CanNm_INTERNAL_STATUS();
    prevEIRA = CanNm_ArrayPnEIRAPdu[arrIdx];

    /* Take the PN mask byte into local variable */
    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    mask = CanNm_PnFilterMaskBytesPtr[arrIdx];
    #else
    mask = CanNm_ArrayPnMaskByte[arrIdx];
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

    /* Check if message contains Partial NW information */
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
    if (CANNM_ZERO != mask)
    {
      /* @Trace: CanNm_SUD_API_263 */     
      /* Check if PN enabled using the mask byte */
      /* polyspace +4 MISRA2012:D4.1 [Justified:Low] "CanNm_structPnInfo.pnInfoOffset have been generated and checked by generation tool so pointer can not be outside" */
      /* polyspace +3 RTE:IDP [Justified:Low] "CanNm_structPnInfo.pnInfoOffset have been generated and checked by generation tool so pointer can not be outside" */
      /* polyspace +2 RTE:NIV [Justified:Low] "ptrPnInfo is input argument" */
      /* polyspace +1 MISRA2012:18.1 [Justified:Low] "CanNm_structPnInfo.pnInfoOffset have been generated and checked by generation tool so pointer can not be outside" */
      setEIRA = ptrPnInfo[(CanNm_structPnInfo.pnInfoOffset + arrIdx)] & mask;

      /* Loop through all the eight bits of each PN byte */
      for (pnTimer = CANNM_ZERO; pnTimer < CANNM_EIGHT; pnTimer++)
      {
        pnTimerBit = ((arrIdx * CANNM_EIGHT) + ((uint16)CANNM_SEVEN - (uint16)pnTimer));
        /* Check if any bit set */
        if (CANNM_ZERO != (setEIRA & CANNM_ONE))
        {
          /* @Trace: CanNm_SUD_API_264 */
          /* Get the pointer to timer channel arrIdx */
          ptrTimer = &CanNm_ArrayPnEIRATimer[pnTimerBit];
            
          /* Load the timer value for each bit that is set */
          *ptrTimer = CANNM_PN_RESET_TIME;
        }
        else
        {
          /* Do nothing */
        }

        /* @Trace: CanNm_SUD_API_265 */
        /* Check for the next bit */
        setEIRA = (setEIRA >> CANNM_ONE);
      }
    }
    else
    {
      /* Do nothing */
    }

    /* Check if there's any change in the received PN data */
    /*   => We just need to check if a pnc status is changed from released(0) to requested(1) from received value
         => Refer to SWS_CanNm_00426. CanNm do not care about received value '0'. */
    /* polyspace +1 RTE:NIV [Justified:Low] "ptrPnInfo is input argument" */
    if (prevEIRA != (prevEIRA | (ptrPnInfo[(CanNm_structPnInfo.pnInfoOffset + arrIdx)] & mask)))
    {
      /* @Trace: CanNm_SUD_API_266 */
      /* Set the flag in order to indicate the change to upper layer */
      eIRAChange = CANNM_TRUE;
      /* We have to "OR" the information, because we should not apply received '0' value to the stored value.*/
      CanNm_ArrayPnEIRAPdu[arrIdx] |= (ptrPnInfo[(CanNm_structPnInfo.pnInfoOffset + arrIdx)] & mask);
    }
    else
    {
      /* Do nothing */
    }
    SchM_Exit_CanNm_INTERNAL_STATUS();
  }

  /* Check if there is change in any byte of the received PN data */
  if (CANNM_TRUE == eIRAChange)
  {
    /* @Trace: CanNm_SUD_API_267 */
    /* Set Sdu  Index */
    pnEiraRxNSduHandleId = CANNM_PN_EIRA_RXNSDU;

    /* Assign the PDU Length */
    pnPduInfo.SduLength = CanNm_structPnInfo.pnInfoLength;
    /* Assign the base address of the PDU */
    pnPduInfo.SduDataPtr = &CanNm_ArrayPnEIRAPdu[CANNM_BYTE0];

    SchM_Enter_CanNm_INTERNAL_STATUS();
    /* Assign data for metadata*/
    if(CanNm_RxMetaDataCheck == CANNM_TRUE)
    {
      /* @Trace: CanNm_SUD_API_268 */
      pnPduInfo.MetaDataPtr = &CanNm_RxMetaData[CANNM_BYTE0];
    }
    else
    {
      /* @Trace: CanNm_SUD_API_269 */
      pnPduInfo.MetaDataPtr = NULL_PTR;
    }
    SchM_Exit_CanNm_INTERNAL_STATUS();
    
    /* @Trace: CanNm_SUD_API_270 */
    /* Invoke the upper layer with the changed data */
    PduR_CanNmRxIndication(pnEiraRxNSduHandleId, &pnPduInfo);
  }
  else
  {
    /* Do nothing */
  }
}
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : CanNm_IntCanIfTransmit                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Send NM Pdu                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : canNmChannelIndex, PduInfoPtr                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : N/a                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntCollectTxData                              **
**                        CanNm_IntUpdateEIRA                                 **
**                        CanIf_Transmit                                      **
*******************************************************************************/
/* @Trace: SRS_Nm_00137 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntCanIfTransmit(
  uint32 canNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  Std_ReturnType returnValue = E_NOT_OK;

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  PduInfoType structPduInfoType;
  uint8 arrayTxData[CANNM_MAX_PDU_SIZE];
  
  if ((ptrChannel->modeStatus != CANNM_REPEAT_MESSAGE_STATE) && (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE))
  {
    /* Return E_NOT_OK */
  }
  else
  {
    #if (CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT == STD_ON)
    if (ptrStaticChannel->canIfTriggerTransmit == CANNM_TRUE)
    {
      /* @Trace: CanNm_SUD_API_181 */
      /* copy the PduLength into the SduLength */
      structPduInfoType.SduLength = ptrStaticChannel->pduLength;
      structPduInfoType.SduDataPtr = ptrChannel->txUserData;
    }
    else
    #endif
    {
      /* @Trace: CanNm_SUD_API_182 */
      #if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
      CanNm_IntCollectTxData(canNmChannelIndex);
      #endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */

      (void)CanNm_Memcpy(arrayTxData,
                        ptrChannel->txUserData,
                        ptrStaticChannel->pduLength);

      /* copy the PduLength into the SduLength */
      structPduInfoType.SduLength = ptrStaticChannel->pduLength;
      structPduInfoType.SduDataPtr = arrayTxData;
    }

    /* @Trace: CanNm_SUD_API_183 */
    #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
    CanNm_IntUpdateEIRA(&structPduInfoType.SduDataPtr[CANNM_BYTE0]);
    #endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    if (E_OK == CanIf_Transmit(ptrPostBuildChannel->txPduId, &structPduInfoType))
    #else
    if (E_OK == CanIf_Transmit(ptrStaticChannel->txPduId, &structPduInfoType))
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
    {
      /* @Trace: CanNm_SUD_API_185 */
      /* CanNm shall not perform transmission error handling */
      #if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
      #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if(ptrPostBuildChannel->pnEnabled == CANNM_TRUE)
      {
        if((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) && (ptrChannel->noOfImmediateNmTx > CANNM_ZERO))
        {
          ptrChannel->msgTimeOutTime = ptrStaticChannel->immMsgCycleTime;
        }
        else
        {
          ptrChannel->msgTimeOutTime = ptrPostBuildChannel->msgTimeOutTime;
        }
      }
      #else
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
      if(ptrStaticChannel->pnEnabled == CANNM_TRUE)
      {
        if((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) && (ptrChannel->noOfImmediateNmTx > CANNM_ZERO))
        {
          ptrChannel->msgTimeOutTime = ptrStaticChannel->immMsgCycleTime;
        }
        else
        {
          ptrChannel->msgTimeOutTime = ptrStaticChannel->msgTimeOutTime;
        }
      }
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
      else
      {
        /* Do nothing */
      }
        #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
        #endif /* #if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */
        returnValue = E_OK;
      }
      else
      {
        /* Do nothing */
      }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_IntGetChannelIdFromCanNmTxConfirmationHandleId**
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get CanNmChannelIndex                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : canNmTxConfirmationHandleId                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : CanNmChannelIndex                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayTxPdu                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        N/A                                                 **
*******************************************************************************/

FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIdFromCanNmTxConfirmationHandleId(
  PduIdType canNmTxConfirmationHandleId,
  P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex)
{
  P2CONST(CanNm_TxPdu, AUTOMATIC, CANNM_CONST) ptrTxPdu;
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 arrIdx;

  /* polyspace +1 MISRA2012:14.2 [Justified:Low] "canNmChannelIndex have been reviewed, no overflow here" */
  for (arrIdx = CANNM_ZERO; (E_OK != returnValue) && (arrIdx < CANNM_NUMBER_OF_TXPDU); arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_186 */ 
    ptrTxPdu = &CanNm_ArrayTxPdu[arrIdx];

    if (ptrTxPdu->canNmTxPduId == canNmTxConfirmationHandleId)
    {
      /* @Trace: CanNm_SUD_API_187 */
      *ptrCanNmChannelIndex = ptrTxPdu->canNmChannelIndex;
      returnValue = E_OK;
    }
    else
    {
      /* Do nothing */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_IntGetChannelIdFromCanNmRxIndicationHandleId  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get CanNmChannelIndex                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : CanNmChannelIndex                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayRxPdu                                    **
**                        CanNm_RxPduId                                       **
**                        CanNm_NumberOfRxPdu                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        N/A                                                 **
*******************************************************************************/

FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIdFromCanNmRxIndicationHandleId(
    PduIdType RxPduId,
    P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex)
{
  #if (CANNM_POSTBUILD_SUPPORTED != STD_ON)
  P2CONST(CanNm_RxPdu, AUTOMATIC, CANNM_CONST) ptrRxPdu;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED != STD_ON) */
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 arrIdx;

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  for (arrIdx = CANNM_ZERO; (E_OK != returnValue) && (arrIdx < CanNm_NumberOfRxPdu); arrIdx++)
  {
    if (CanNm_RxPduId[arrIdx].canNmRxPduId == RxPduId)
    {
      /* @Trace: CanNm_SUD_API_188 */
      *ptrCanNmChannelIndex = CanNm_RxPduId[arrIdx].canNmChannelIndex;
      returnValue = E_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  #else
  for (arrIdx = CANNM_ZERO; (E_OK != returnValue) && (arrIdx < CANNM_NUMBER_OF_RXPDU); arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_189 */
    ptrRxPdu = &CanNm_ArrayRxPdu[arrIdx];

    if (ptrRxPdu->canNmRxPduId == RxPduId)
    {
      /* @Trace: CanNm_SUD_API_190 */
      *ptrCanNmChannelIndex = ptrRxPdu->canNmChannelIndex;
      returnValue = E_OK;
    }
    else
    {
      /* Do nothing */
    }
  }
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanNm_IntGetChannelIdFromTriggerTransmitHandleId    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get CanNmChannelIndex                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanNmTriggerTransmitHandleId                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : canNmChannelIndex                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayTxPdu                                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        N/A                                                 **
*******************************************************************************/

FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIdFromTriggerTransmitHandleId(
  PduIdType canNmTriggerTransmitHandleId,
  P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex)
{
  P2CONST(CanNm_TxPdu, AUTOMATIC, CANNM_CONST) ptrTxPdu;
  Std_ReturnType returnValue = E_NOT_OK;
  uint32 arrIdx;

  /* polyspace +1 MISRA2012:14.2 [Justified:Low] "canNmChannelIndex have been reviewed, no overflow here" */
  for (arrIdx = CANNM_ZERO; (E_OK != returnValue) && (arrIdx < CANNM_NUMBER_OF_TXPDU); arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_191 */  
    ptrTxPdu = &CanNm_ArrayTxPdu[arrIdx];

    if (ptrTxPdu->canNmTxPduId == canNmTriggerTransmitHandleId)
    {
      /* @Trace: CanNm_SUD_API_192 */ 
      *ptrCanNmChannelIndex = ptrTxPdu->canNmChannelIndex;
      returnValue = E_OK;
    }
    else
    {
      /* Do nothing */
    }
  }

  return returnValue;
}

#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_IntGetRxHandlingMethod                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get Rx Handling Method                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : canNmChannelIndex, ptrArrayRxPdu                    **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : CANNM_RX_HANDLING_METHOD                            **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayPnMaskByte                               **
**                        CanNm_ChannelsDataPtr                               **
**                        CanNm_PnFilterMaskBytesPtr                          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Nm_02518 SRS_Nm_02520 SRS_Nm_02521 SRS_Nm_02522 SRS_Nm_02538 */
FUNC(CANNM_RX_HANDLING_METHOD, CANNM_CODE) CanNm_IntGetRxHandlingMethod(
  uint32 canNmChannelIndex,
  P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) ptrArrayRxPdu)
{

  CANNM_RX_HANDLING_METHOD rxHandlingMethod = CANNM_RX_HANDLING_METHOD_IGNORE;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  boolean pNIBitIsSet;
  CanNm_PduPositionType pduCbvPosition;
  #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
  uint8 arrIdx;
  uint8 mask;
  uint8 pnInfo;
  uint8 releatedPnInfo;
  #endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
    
  pduCbvPosition = ptrStaticChannel->pduCbvPosition;
  
  /* Check PNI bit in incoming Nm PDU */
  if ((pduCbvPosition != CANNM_PDU_OFF) && ((ptrArrayRxPdu[pduCbvPosition] & CANNM_PNI_BIT) == CANNM_PNI_BIT))
  {
    /* @Trace: CanNm_SUD_API_193 */
    pNIBitIsSet = CANNM_TRUE;
  }
  else
  {
    /* @Trace: CanNm_SUD_API_194 */
    pNIBitIsSet = CANNM_FALSE;
  }
  
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  if(ptrPostBuildChannel->pnEnabled == CANNM_FALSE)
  {
    /* @Trace: CanNm_SUD_API_195 */
    rxHandlingMethod = CANNM_RX_HANDLING_METHOD_PROCESS_WITHOUT_PARTIAL_NETWORK;
  }
  else if ((pNIBitIsSet == CANNM_TRUE) &&
                                        (ptrChannel->pnStatusBit == CANNM_TRUE))
  {
    /* Loop through all the PN bytes configured */
    for (arrIdx = CANNM_ZERO; arrIdx < CanNm_structPnInfo.pnInfoLength; arrIdx++)
    {
      /* @Trace: CanNm_SUD_API_196 */
      /* Take the PN mask byte into local variable */
      mask = CanNm_PnFilterMaskBytesPtr[arrIdx];
    
      /* Take PN user data */
      pnInfo = ptrArrayRxPdu[CanNm_structPnInfo.pnInfoOffset + arrIdx];

      /* Check if PN enabled using the mask byte */
      releatedPnInfo = pnInfo & mask;
      if (releatedPnInfo != CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_197 */
        rxHandlingMethod = CANNM_RX_HANDLING_METHOD_PROCESS_WITH_PARTIAL_NETWORK;
      }
      else
      {
        /* Do nothing */
      }
    }
  }
  else
  {
    /* Do nothing */
  }
  #else
  #if ((CANNM_PN_DISABLED_PRESENT == STD_ON) || (CANNM_ALL_NM_MESSAGES_KEEP_AWAKE_PRESENT == STD_ON))
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
  if((ptrStaticChannel->pnEnabled == CANNM_FALSE) || (ptrStaticChannel->allNmMessagesKeepAwake == CANNM_TRUE))
  {
    /* @Trace: CanNm_SUD_API_195 */
    rxHandlingMethod = CANNM_RX_HANDLING_METHOD_PROCESS_WITHOUT_PARTIAL_NETWORK;
  }
  #endif

  /* PN Filter ê¸°ëŠ¥ ONì�´ë�˜ OFFë�˜, PN Enableì�´ê³  PNIBitì�€ setë�œ ìƒ�íƒœë�¼ë©´? ìš°ì„  Handling without PNìœ¼ë¡œ í• ë‹¹.*/
  /* Should not ignore Rx in this case. Refer to below spec*/
  /* [SWS_CanNm_00412] âŒˆIf CanNmPnEnabled is TRUE and the PNI bit in the received NM-PDU is 1,
     CanNm module shall process the Partial Networking Information of the NM-PDU as described 
     in chapter 7.11.3 NM PDU Filter Algorithm.âŒ‹ (SRS_Nm_02517, SRS_Nm_02518, SRS_Nm_02520)*/
  /*
   * [SWS_CanNm_00411] âŒˆIf CanNmPnEnabled is TRUE, the PNI bit in the received NM-PDU is 0
   * and CanNmAllNmMessagesKeepAwake is FALSE, the CanNm module shall ignore the received NM-PDU.âŒ‹
   * (SRS_Nm_02517, SRS_Nm_02518, SRS_Nm_02520)
   *
   * [SWS_CanNm_00404] âŒˆIf the CanSm calls CanNm_ConfirmPnAvailability the NM-PDU filter algorithm shall be enabled on the indicated channel.âŒ‹ (SRS_Nm_02517, SRS_Nm_02527)
     Rationale: This is required to allow a malfunctioning PN transceiver to shut down synchronously with the remaining network.
     Note: If the NM-PDU filter algorithm is not enabled (e.g. due to malfunctioning PN transceiver) the CanNm restarts the NM-Timeout Timer when receiving a NM-PDU.
           Therefore normal shutdown behavior is performed.
   * */
  if((ptrStaticChannel->pnEnabled == CANNM_TRUE) && (pNIBitIsSet == CANNM_TRUE) && (ptrChannel->pnStatusBit == CANNM_FALSE))
  {
    rxHandlingMethod = CANNM_RX_HANDLING_METHOD_PROCESS_WITHOUT_PARTIAL_NETWORK;
  }

  if ((pNIBitIsSet == CANNM_TRUE) &&
                                    (ptrChannel->pnStatusBit == CANNM_TRUE))
  {
    /* Loop through all the PN bytes configured */
    for (arrIdx = CANNM_ZERO; arrIdx < CanNm_structPnInfo.pnInfoLength; arrIdx++)
    {
      /* @Trace: CanNm_SUD_API_196 */
      /* Take the PN mask byte into local variable */
      mask = CanNm_ArrayPnMaskByte[arrIdx];
    
      /* Take PN user data */
      pnInfo = ptrArrayRxPdu[CanNm_structPnInfo.pnInfoOffset + arrIdx];

      /* Check if PN enabled using the mask byte */
      releatedPnInfo = pnInfo & mask;
      if (releatedPnInfo != CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_197 */
        rxHandlingMethod = CANNM_RX_HANDLING_METHOD_PROCESS_WITH_PARTIAL_NETWORK;
      }
      else
      {
        /* Do nothing */
      }
    }
  }
  else
  {
    /* Do nothing */
  }  
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  return rxHandlingMethod;
}
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

/* CanNm shall not perform transmission error handling */
#if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_IntProcessMsgTimeOutTime                      **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get Nm State From CanNm Mode State                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Nm_TxTimeoutException                               **
**                        CanSM_TxTimeoutException                            **
*******************************************************************************/
/* @Trace: SRS_Nm_02529 */
FUNC(void, CANNM_CODE) CanNm_IntProcessMsgTimeOutTime(void)
{
  uint32 canNmChannelIndex;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;

  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  for (canNmChannelIndex = CANNM_ZERO; canNmChannelIndex < CANNM_NUMBER_OF_CHANNEL; canNmChannelIndex++)
  {
    /* @Trace: CanNm_SUD_API_198 */
    /* Get channel configuration data and channel internal data */
    ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
    ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
    if(ptrPostBuildChannel->pnEnabled == CANNM_TRUE)
    #else
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
    if(ptrStaticChannel->pnEnabled == CANNM_TRUE)
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
    {
      if (ptrChannel->msgTimeOutTime > CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_199 */
        ptrChannel->msgTimeOutTime--;

        if (ptrChannel->msgTimeOutTime == CANNM_ZERO)
        {
          /* @Trace: CanNm_SUD_API_200 */
          Nm_TxTimeoutException(ptrStaticChannel->comMChannelId);

          CanSM_TxTimeoutException(ptrStaticChannel->comMChannelId);
        }
        else
        {
          /* Do nothing */
        }    
      }
      else
      {
        /* Do nothing */
      }
    }
    
  }
}
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
#endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */

#if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_IntGetNmStateTypeFromCanNmModeState           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get Nm State From CanNm Mode State                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(boolean, CANNM_CODE) CanNm_IntGetNmStateTypeFromCanNmModeState(
  CanNm_ModeState canNmModeState,
  P2VAR(Nm_StateType, AUTOMATIC, CANNM_VAR) ptrNmState)
{
  boolean result = CANNM_TRUE;
  
  if (canNmModeState == CANNM_BUS_SLEEP_MODE)
  {
    /* @Trace: CanNm_SUD_API_201 */
    *ptrNmState = NM_STATE_BUS_SLEEP;
  }
  else if (canNmModeState == CANNM_PREPAREBUS_SLEEP_MODE)
  {
    /* @Trace: CanNm_SUD_API_202 */
    *ptrNmState = NM_STATE_PREPARE_BUS_SLEEP;
  }
  else if (canNmModeState == CANNM_READY_SLEEP_STATE)
  {
    /* @Trace: CanNm_SUD_API_203 */
    *ptrNmState = NM_STATE_READY_SLEEP;
  }
  else if (canNmModeState == CANNM_NORMAL_OPERATION_STATE)
  {
    /* @Trace: CanNm_SUD_API_204 */
    *ptrNmState = NM_STATE_NORMAL_OPERATION;
  }
  else if (canNmModeState == CANNM_REPEAT_MESSAGE_STATE)
  {
    /* @Trace: CanNm_SUD_API_205 */
    *ptrNmState = NM_STATE_REPEAT_MESSAGE;
  }
  else
  {
    /* @Trace: CanNm_SUD_API_206 */
    result = CANNM_FALSE;
  }

  return result;
}
#endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */ 

#if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_IntStateChangeNotification                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Process State Change Notification                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntGetNmStateTypeFromCanNmModeState           **
**                        Nm_StateChangeNotification                          **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_IntStateChangeNotification(
  uint32 canNmChannelIndex,
  CanNm_ModeState canNmPreviousState,
  CanNm_ModeState canNmCurrentState)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;

  /* Get channel configuration data */
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  NetworkHandleType nmNetworkHandle;
  Nm_StateType nmPreviousState;
  Nm_StateType nmCurrentState;
  boolean nmPreviousStateResult;
  boolean nmCurrentStateResult;

  nmNetworkHandle = ptrStaticChannel->comMChannelId;
      
  nmPreviousStateResult = CanNm_IntGetNmStateTypeFromCanNmModeState(canNmPreviousState, &nmPreviousState);
  nmCurrentStateResult = CanNm_IntGetNmStateTypeFromCanNmModeState(canNmCurrentState, &nmCurrentState);

  /* @Trace: CanNm_SUD_API_207 */
  /* Notify the upper layer */
  if ((nmPreviousStateResult == CANNM_TRUE) && (nmCurrentStateResult == CANNM_TRUE))
  {
    Nm_StateChangeNotification(nmNetworkHandle,
                                  nmPreviousState,
                                  nmCurrentState);
  }
  else
  {
    /* Do nothing */
  }
}
#endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : CanNm_IntNetworkModeEntry                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Entry function for Network-Mode                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Nm_NetworkMode                                      **
**                        CanNm_IntCanIfTransmit                              **
*******************************************************************************/
/* @Trace: SRS_Nm_00051 */
FUNC(void, CANNM_CODE) CanNm_IntNetworkModeEntry(uint32 canNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;

  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  if ((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) ||
        (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE) ||
        (ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE))
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_208 */
    Nm_NetworkMode(ptrStaticChannel->comMChannelId);

    ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;

    #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
    #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
    #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON)
    if (ptrStaticChannel->activeWakeupBitEnabled == CANNM_TRUE)
    {
    #endif
    if ((ptrChannel->txActiveWakeUpBit == CANNM_TRUE)
      && (CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition))
    {
      /* @Trace: CanNm_SUD_API_209 */
      ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
        = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                                | CANNM_ACTWKP_BIT;
    }
    #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON)
    }
    else
    {
      /* Do nothing */
    }
    #endif
    #endif
    #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */

    /* Transmit a Nm PDU */
    #if (CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON)
    if (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE)
    {
      /* @Trace: CanNm_SUD_API_210 */
      CanNm_IntCanIfTransmit(canNmChannelIndex);
    }
    else
    {
      /* Do nothing */
    }
    #endif /* #if (CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntEntryRepeatMessageState                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Entry function for Repeat-Message-State             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntStateChangeNotification                    **
**                        Nm_RemoteSleepCancellation                          **
*******************************************************************************/
/* @Trace: SRS_Nm_02510 */
FUNC(void, CANNM_CODE) CanNm_IntEntryRepeatMessageState(uint32 canNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
  CanNm_ModeState prevState;
  #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
  #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

  if (ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_211 */
    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    prevState = ptrChannel->modeStatus;
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

    /*Update the mode status */
    ptrChannel->modeStatus = CANNM_REPEAT_MESSAGE_STATE;

    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    CanNm_IntStateChangeNotification(canNmChannelIndex, prevState, CANNM_REPEAT_MESSAGE_STATE);
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
    #if (CANNM_BUSLOAD_REDUCTION_ACTIVE_PRESENT == STD_ON)
    if (ptrStaticChannel->busLoadRedActive == CANNM_TRUE)
    /* polyspace +1 RTE:UNR [Justified:Low] "This branch will be covered when bus load reduction is enabled" */
    {
      /* @Trace: CanNm_SUD_API_212 */
      ptrChannel->busLoadReductionEnabled = CANNM_FALSE;
    }
    else
    {
      /* Do nothing */
    }
    #endif

    #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
    if (ptrChannel->remoteSlpDetect == CANNM_TRUE)
    {
      /* @Trace: CanNm_SUD_API_213 */
      ptrChannel->remoteSlpDetect = CANNM_FALSE;
      Nm_RemoteSleepCancellation(ptrStaticChannel->comMChannelId);
    }
    else
    {
      /* Do nothing */
    }
    #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

    #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    /* polyspace +3 MISRA2012:D4.1 [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    /* polyspace +2 MISRA2012:18.1 [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    /* polyspace +1 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    if ((CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition) \
        && ((ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] \
        & CANNM_SETSLEEP_BIT) == CANNM_SETSLEEP_BIT))
    {
      /* @Trace: CanNm_SUD_API_214 */
      /* Clear NM Coordinator Sleep Ready Bit */
      ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
        = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                        & ~(CANNM_SETSLEEP_BIT);
    }
    else
    {
      /* Do nothing */
    }
    #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */

    ptrChannel->repeatMessageTime = ptrStaticChannel->repeatMsgTime;
    
    if ((ptrChannel->networkRequested == CANNM_TRUE) && (ptrStaticChannel->noOfImmediateNmTx > CANNM_ZERO))
    {
       /* @Trace: CanNm_SUD_API_215 */
      ptrChannel->noOfImmediateNmTx = ptrStaticChannel->noOfImmediateNmTx;
      ptrChannel->msgCycleTime = CANNM_ONE;
    }
    else
    {
      /* @Trace: CanNm_SUD_API_216 */
      #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
      ptrChannel->msgCycleTime = ptrPostBuildChannel->msgCycleOffset + CANNM_ONE;
      #else
      ptrChannel->msgCycleTime = ptrStaticChannel->msgCycleOffset + CANNM_ONE;
      #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
    }
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntEntryNormalOperationState                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Entry function for Normal-Operation-State           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntStateChangeNotification                    **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntEntryNormalOperationState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if ((CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) ||\
    (CANNM_NODE_DETECTION_ENABLED == STD_ON) ||\
    (CANNM_BUSLOAD_REDUCTION_ACTIVE_PRESENT == STD_ON))
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif
  CanNm_ModeState prevState;
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  #if ((CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) ||\
    (CANNM_NODE_DETECTION_ENABLED == STD_ON) ||\
    (CANNM_BUSLOAD_REDUCTION_ACTIVE_PRESENT == STD_ON))
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  #endif

  if (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_217 */
    prevState = ptrChannel->modeStatus;

    /*Update the mode */
    ptrChannel->modeStatus = CANNM_NORMAL_OPERATION_STATE;
    
    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    CanNm_IntStateChangeNotification(canNmChannelIndex, prevState, CANNM_NORMAL_OPERATION_STATE);
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
    
    #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
    /* Start the remote sleep indication timer */
    ptrChannel->remoteSleepIndTime = ptrStaticChannel->remoteSleepIndTime;
    #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
    
    if (prevState == CANNM_READY_SLEEP_STATE)
    {
      /* @Trace: CanNm_SUD_API_218 */
      ptrChannel->msgCycleTime = CANNM_ONE;

      #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
      /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
      /* polyspace +3 MISRA2012:D4.1 [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
      /* polyspace +2 MISRA2012:18.1 [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
      /* polyspace +1 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
      if ((CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition) \
          && ((ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition] \
          & CANNM_SETSLEEP_BIT) == CANNM_SETSLEEP_BIT))
      {
        /* @Trace: CanNm_SUD_API_219 */
        /* Clear NM Coordinator Sleep Ready Bit */
        ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
          = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                        & ~(CANNM_SETSLEEP_BIT);
      }
      else
      {
        /* Do nothing */
      }
      #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
    }
    else
    {
      /* Do nothing */
    }
    #if (CANNM_BUSLOAD_REDUCTION_ACTIVE_PRESENT == STD_ON)
    if (ptrStaticChannel->busLoadRedActive == CANNM_TRUE)
    /* polyspace +1 RTE:UNR [Justified:Low] "This branch will be covered when bus load reduction is enabled" */
    {
      /* @Trace: CanNm_SUD_API_220 */
      ptrChannel->busLoadReductionEnabled = CANNM_TRUE;
    }
    else
    {
      /* Do nothing */
    }
    #endif
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntEntryReadySleepState                       **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Entry function for Ready-Sleep-State                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntStateChangeNotification                    **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntEntryReadySleepState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
  CanNm_ModeState prevState;
  #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
  
  /* Get channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_221 */
    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    prevState = ptrChannel->modeStatus;
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

    /*Update the mode */
    ptrChannel->modeStatus = CANNM_READY_SLEEP_STATE;

    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    CanNm_IntStateChangeNotification(canNmChannelIndex, prevState, CANNM_READY_SLEEP_STATE);
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

    ptrChannel->msgCycleTime = CANNM_ZERO;
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntEntryPrepareBusSleepMode                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Entry function for Prepare-Bus-Sleep-Mode           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntStateChangeNotification                    **
**                        Nm_PrepareBusSleepMode                              **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntEntryPrepareBusSleepMode(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
  CanNm_ModeState prevState;
  #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_222 */
    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    prevState = ptrChannel->modeStatus;
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

    /*Update the mode */
    ptrChannel->modeStatus = CANNM_PREPAREBUS_SLEEP_MODE;

    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    CanNm_IntStateChangeNotification(canNmChannelIndex, prevState, CANNM_PREPAREBUS_SLEEP_MODE);
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

    /* Notify the Upper Layer that Prepare Bus sleep mode has been entered */
    Nm_PrepareBusSleepMode(ptrStaticChannel->comMChannelId);
    
    /* Start wait Bus Sleep Timer */
    ptrChannel->waitBusSleepTime = ptrStaticChannel->waitBusSleepTime;
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntEntryBusSleepMode                          **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Entry function for Bus-Sleep-Mode                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntStateChangeNotification                    **
**                        Nm_BusSleepMode                                     **
*******************************************************************************/
/* @Trace: SRS_Nm_00054 SRS_Nm_00149 */
FUNC(void, CANNM_CODE) CanNm_IntEntryBusSleepMode(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
  CanNm_ModeState prevState;
  #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus == CANNM_BUS_SLEEP_MODE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_223 */
    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    prevState = ptrChannel->modeStatus;
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */
    
    /*Update the mode */
    ptrChannel->modeStatus = CANNM_BUS_SLEEP_MODE;

    #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
    CanNm_IntStateChangeNotification(canNmChannelIndex, prevState, CANNM_BUS_SLEEP_MODE);
    #endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

    /* Notify the Upper Layer that Bus sleep mode has been entered */
    Nm_BusSleepMode(ptrStaticChannel->comMChannelId);
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntExitNetworkMode                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Exit function for Network-Mode                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayChannel                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntExitNetworkMode(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if ((CANNM_NODE_DETECTION_ENABLED == STD_ON) && (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON))
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  #if ((CANNM_NODE_DETECTION_ENABLED == STD_ON) && (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON))
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) && (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)*/

  /* Stop the Network Timer */
  ptrChannel->ntwkTimeOutTime = CANNM_ZERO;

  if ((ptrChannel->modeStatus != CANNM_REPEAT_MESSAGE_STATE) &&
          (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE) &&
          (ptrChannel->modeStatus != CANNM_READY_SLEEP_STATE))
  {
    /* Do nothing */
  }
  else
  { 
    /* @Trace: CanNm_SUD_API_224 */
    #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
    #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
    #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON)
    if (ptrStaticChannel->activeWakeupBitEnabled == CANNM_TRUE)
    {
    #endif
      if ((ptrChannel->txActiveWakeUpBit == CANNM_TRUE)
        && (CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition))
      {
        ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
          = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                              & ~(CANNM_ACTWKP_BIT);

      ptrChannel->txActiveWakeUpBit = CANNM_FALSE;
      }
    #if(CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED == STD_ON)
    }
    else
    {
      /* Do nothing */
    }
    #endif
    #endif
    #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntExitRepeatMessageState                     **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Exit function for Repeat-Message-State              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntExitRepeatMessageState(uint32 canNmChannelIndex)
{
  #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */

  if (ptrChannel->modeStatus != CANNM_REPEAT_MESSAGE_STATE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_225 */
    ptrChannel->repeatMessageTime = CANNM_ZERO;
    
    #if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
    if ((CANNM_PDU_OFF != ptrStaticChannel->pduCbvPosition))
    {
    /* Clear the repeat message request bit of status bits */
    /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    /* polyspace +4 MISRA2012:D4.1 [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    /* polyspace +3 MISRA2012:18.1 [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
    /* polyspace +2 RTE:OBAI [Justified:Low] "Value of pduCbvPosition have been generated by generation tool and got value as 0 or 1 only" */
      ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
          = ptrChannel->txUserData[ptrStaticChannel->pduCbvPosition]
                                              & ~(CANNM_REPTMSG_BIT);
    }
    else
    {
      // Avoid MISRA C Violation.
    }
    #endif /* #if (CANNM_NODE_DETECTION_ENABLED == STD_ON) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntExitNormalOperationState                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Exit function for Normal-Operation-State            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntExitNormalOperationState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_226 */
    #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
    /* Start the remote sleep indication timer */
    ptrChannel->remoteSleepIndTime = CANNM_ZERO;
    #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntExitReadySleepState                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Exit function for Ready-Sleep-State                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntExitReadySleepState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus != CANNM_READY_SLEEP_STATE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_227 */
    #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
    ptrChannel->remoteSlpDetect = CANNM_FALSE;
    #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntExitPrepareBusSleepMode                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Exit function for Prepare-Bus-Sleep-Mode            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntExitPrepareBusSleepMode(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus != CANNM_PREPAREBUS_SLEEP_MODE)
  {
    /* Do nothing */
  }
  else
  {
    /* @Trace: CanNm_SUD_API_228 */
    ptrChannel->waitBusSleepTime = CANNM_ZERO;
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntPrepareBusSleepMode                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Main function for Prepare-Bus-Sleep-Mode            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntPrepareBusSleepMode(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus != CANNM_PREPAREBUS_SLEEP_MODE)
  {
    /* Do nothing */
  }
  else
  {
    if (ptrChannel->waitBusSleepTime > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_229 */
      ptrChannel->waitBusSleepTime--;
    }
    else
    {
      /* Do nothing */
    }

    if (ptrChannel->waitBusSleepTime == CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_230 */
      ptrChannel->nextModeState = CANNM_BUS_SLEEP_MODE;
    }
    else
    {
      /* Do nothing */
    }
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntReadySleepState                          **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Main function for Normal-Operation-State            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_ArrayChannel                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Nm_RemoteSleepIndication                            **
*******************************************************************************/
/* @Trace: SRS_Nm_00053 */
FUNC(void, CANNM_CODE) CanNm_IntReadySleepState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  
  /* Get channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  if (ptrChannel->ntwkTimeOutTime > CANNM_ZERO)
  {
    /* @Trace: CanNm_SUD_API_231 */
    ptrChannel->ntwkTimeOutTime--;
      
    if (ptrChannel->ntwkTimeOutTime == CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_232 */
      ptrChannel->nextModeState = CANNM_PREPAREBUS_SLEEP_MODE;
      ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    /* Do nothing */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntNormalOperationState                       **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Main function for Normal-Operation-State            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Nm_RemoteSleepIndication                            **
*******************************************************************************/
/* @Trace: SRS_Nm_00052 */
FUNC(void, CANNM_CODE) CanNm_IntNormalOperationState(uint32 canNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus != CANNM_NORMAL_OPERATION_STATE)
  {
    /* Do nothing */
  }
  else
  {
    if (ptrChannel->ntwkTimeOutTime > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_233 */
      ptrChannel->ntwkTimeOutTime--;
      
      if (ptrChannel->ntwkTimeOutTime == CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_234 */
        (void)Det_ReportRuntimeError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_MAINFUNCTION_SID, CANNM_E_NETWORK_TIMEOUT);
        ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
    
    #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
    if (ptrChannel->remoteSleepIndTime > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_235 */
      ptrChannel->remoteSleepIndTime--;
      
      if (ptrChannel->remoteSleepIndTime == CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_236 */
        ptrChannel->remoteSlpDetect = CANNM_TRUE;
        
        Nm_RemoteSleepIndication(ptrStaticChannel->comMChannelId);
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
    #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_IntRepeatMessageState                         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Main function for Repeat-Message-State              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntRepeatMessageState(uint32 canNmChannelIndex)
{
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  
  /* Get channel configuration data and channel internal data */
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  if (ptrChannel->modeStatus != CANNM_REPEAT_MESSAGE_STATE)
  {
    /* Do nothing */
  }
  else
  {
    if (ptrChannel->ntwkTimeOutTime > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_237 */
      ptrChannel->ntwkTimeOutTime--;
      
      if (ptrChannel->ntwkTimeOutTime == CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_238 */
        (void)Det_ReportRuntimeError(CANNM_MODULE_ID, CANNM_INSTANCE_ID,
                              CANNM_MAINFUNCTION_SID, CANNM_E_NETWORK_TIMEOUT);
        ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;
      }
      else
      {
        /* Do nothing */
      }
    }

    if (ptrChannel->repeatMessageTime > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_239 */
      ptrChannel->repeatMessageTime--;
    }
    else
    {
      /* Do nothing */
    }

    if (ptrChannel->repeatMessageTime == CANNM_ZERO)
    {
      if (ptrChannel->networkRequested == CANNM_TRUE)
      {
        /* @Trace: CanNm_SUD_API_240 */
        ptrChannel->nextModeState = CANNM_NORMAL_OPERATION_STATE;
      }
      else
      {
        /* @Trace: CanNm_SUD_API_241 */
        ptrChannel->nextModeState = CANNM_READY_SLEEP_STATE;
      }
    }
    else
    {
      /* Do nothing */
    }
  }
}

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_IntProcessEIRATimer                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Process EIRA Timer                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanNm_structPnInfo.pnInfoLength                     **
**                        CanNm_ArrayPnEIRATimer                              **
**                        CanNm_ArrayPnEIRAPdu                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        PduR_CanNmRxIndication                              **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntProcessEIRATimer(void)
{
  uint16 arrIdx;
  boolean eIRAChanged;
  uint16 byteIndex;
  uint8 bitIndex;
  PduInfoType structPduInfo;
  PduIdType pnEiraRxNSduHandleId;
  const uint16 eiraTimerSize = ((uint16)CanNm_structPnInfo.pnInfoLength * (uint16)CANNM_EIGHT);

  /* @Trace: CanNm_SUD_API_242 */
  /* EIRA Change should be detected for all eira bits */
  eIRAChanged = CANNM_FALSE; 

  for (arrIdx = CANNM_ZERO; arrIdx < eiraTimerSize; arrIdx++)
  {
    if (CanNm_ArrayPnEIRATimer[arrIdx] > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_243 */
      CanNm_ArrayPnEIRATimer[arrIdx]--;

      if (CanNm_ArrayPnEIRATimer[arrIdx] == CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_244 */
        /* Get byte arrIdx */
        /* EIRA contains EIRA information from the first byte */
        byteIndex = (arrIdx / CANNM_EIGHT);
        /* Get bit arrIdx */
        bitIndex = (uint8)(arrIdx % CANNM_EIGHT);
  
        CanNm_ArrayPnEIRAPdu[byteIndex] &= ~(uint8)(CANNM_ONE << (CANNM_SEVEN - bitIndex));
  
        eIRAChanged = CANNM_TRUE;
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
  }

  if (eIRAChanged == CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_245 */
    /* Set Sdu  Index */
    pnEiraRxNSduHandleId = CANNM_PN_EIRA_RXNSDU;

    /* Assign the PDU Length */
    /* Com module's I-PDU length should be the same with User Data Length. Refer to below spec. */
    /*[SWS_CanNm_00332] âŒˆIf CanNmComUserDataSupport is enabled and
      the number of available user data bytes does not match to 
      the length of the referenced I-PDU an error shall be reported at generation time.*/
    structPduInfo.SduLength = CanNm_structPnInfo.pnInfoLength;
    /* Assign the base address of the PDU */
    structPduInfo.SduDataPtr = CanNm_ArrayPnEIRAPdu;
    /* Assign data for metadata*/
    structPduInfo.MetaDataPtr = NULL_PTR;

    PduR_CanNmRxIndication(pnEiraRxNSduHandleId, &structPduInfo);
  }
  else
  {
    /* Do nothing */
  }
}
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_IntProcessERATimer                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Process ERA Timer                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        (void)Det_ReportError                               **
**                        PduR_CanNmRxIndication                              **
*******************************************************************************/
/* @Trace: SRS_Nm_02524 */
FUNC(void, CANNM_CODE) CanNm_IntProcessERATimer(void)
{
  uint32 canNmChannelIndex;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  uint8 byteIndex;
  uint8 bitIndex;
  uint16 arrIdx;
  PduInfoType structPduInfo;
  boolean eRAChanged;
  
  for (canNmChannelIndex = CANNM_ZERO; canNmChannelIndex < CANNM_NUMBER_OF_CHANNEL; canNmChannelIndex++)
  {
    /* @Trace: CanNm_SUD_API_246 */
    /* Get channel configuration data and channel internal data */
    ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
    ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

    eRAChanged = CANNM_FALSE;

    for (arrIdx = CANNM_ZERO; arrIdx < ((uint16)CanNm_structPnInfo.pnInfoLength * (uint16)CANNM_EIGHT); arrIdx++)
    {
      if (ptrChannel->eRATimer[arrIdx] > CANNM_ZERO)
      {
        /* @Trace: CanNm_SUD_API_247 */
        ptrChannel->eRATimer[arrIdx]--;

        if (ptrChannel->eRATimer[arrIdx] == CANNM_ZERO)
        {
          /* @Trace: CanNm_SUD_API_248 */
          /* Get byte arrIdx */
          /* ERA information is started from the first byte of eRA */
          byteIndex = (uint8)(arrIdx / CANNM_EIGHT);
          /* Get bit arrIdx */
          bitIndex = (uint8)(arrIdx % CANNM_EIGHT);
    
          ptrChannel->eRA[byteIndex] &= ~(uint8)(CANNM_ONE << (CANNM_SEVEN - bitIndex));
    
          eRAChanged = CANNM_TRUE;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {
        /* Do nothing */
      }
    }

    if (eRAChanged == CANNM_TRUE)
    {
      /* @Trace: CanNm_SUD_API_249 */
      /* Assign the PDU Length */
      structPduInfo.SduLength = CanNm_structPnInfo.pnInfoLength;
      /* Assign the base address of the PDU */
      structPduInfo.SduDataPtr = ptrChannel->eRA;
      /* Assign data for metadata*/
      structPduInfo.MetaDataPtr = NULL_PTR;

      PduR_CanNmRxIndication(ptrStaticChannel->pnEraRxNSduHandleId , &structPduInfo);
    }
    else
    {
      /* Do nothing */
    }
  }
}
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : CanNm_IntProcessNmMessage                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Process transmission of NM PDU                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : CanNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntCanIfTransmit                              **
*******************************************************************************/

FUNC(void, CANNM_CODE) CanNm_IntProcessNmMessage(void)
{
  uint32 canNmChannelIndex;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  boolean needCanNmTransmit;
  #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
  
  for (canNmChannelIndex = CANNM_ZERO; canNmChannelIndex < CANNM_NUMBER_OF_CHANNEL; canNmChannelIndex++)
  {
    /* @Trace: CanNm_SUD_API_250 */
    /* Get channel configuration data and channel internal data */
    ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
    ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

    #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    needCanNmTransmit = CANNM_FALSE;
    #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

    if (ptrChannel->msgCycleTime > CANNM_ZERO)
    {
      /* @Trace: CanNm_SUD_API_251 */
      ptrChannel->msgCycleTime--;
        
      if (ptrChannel->msgCycleTime == CANNM_ZERO)
      {
        if ((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) && (ptrChannel->noOfImmediateNmTx > CANNM_ONE))
        {
          /* @Trace: CanNm_SUD_API_252 */
          ptrChannel->msgCycleTime = ptrStaticChannel->immMsgCycleTime;
        }
        else
        {
          /* @Trace: CanNm_SUD_API_253 */
          ptrChannel->msgCycleTime = ptrStaticChannel->msgCycleTime;
        }
        /* @Trace: CanNm_SUD_API_254 */
        #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
        needCanNmTransmit = CANNM_TRUE;
        #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
      
    if (ptrChannel->transmissionRequestFailed == CANNM_TRUE)
    {
      /* @Trace: CanNm_SUD_API_255 */
      ptrChannel->transmissionRequestFailed = CANNM_FALSE;
      #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      needCanNmTransmit = CANNM_TRUE;
      #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
    }
    else
    {
      /* Do nothing */
    }
    
    #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    if ((ptrChannel->communicationEnabled == CANNM_TRUE) &&
        (needCanNmTransmit == CANNM_TRUE))
    {
      #if(CANNM_PASSIVE_NODE_ENABLED != STD_ON)
      /* @Trace: CanNm_SUD_API_311 */
      if ((ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE) ||
          (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE))

      #else
      /* @Trace: CanNm_SUD_API_310 */
      if (ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE)
        
      #endif /* #if(CANNM_PASSIVE_NODE_ENABLED != STD_ON) */
      {
        /* Check if immediate transmission request to Canif fails */
        if ((CanNm_IntCanIfTransmit(canNmChannelIndex) != E_OK) &&
                                  (ptrChannel->noOfImmediateNmTx > CANNM_ZERO))
        {
          /* @Trace: CanNm_SUD_API_256 */
          ptrChannel->transmissionRequestFailed = CANNM_TRUE;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
    #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
  }
}

/*******************************************************************************
** Function Name        : CanNm_Memset                                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Set value to target memory                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : bufferptr                                           **
**                      : value                                               **
**                      : size                                                **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_Memset(uint8 *bufferptr, uint8 value, uint32 size)
{
  uint32 arrIdx;
  /* Checking whether valid input */
  if(NULL_PTR != bufferptr)
  {
    /* Set value follow length */
    for(arrIdx = CANNM_ZERO; arrIdx < size; arrIdx++)
    {
      /* @Trace: CanNm_SUD_API_257 */
      /* Set value */
      bufferptr[arrIdx] = value;
    }
  }
  else
  /* polyspace +3 RTE:UNR [Justified:Low] "Else branch to follow coding rule" */
  {
    /* @Trace: CanNm_SUD_API_297 */
    #if (CANNM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NODEIDENTIFIER_SID, CANNM_E_PARAM_POINTER);
    #endif
  }
}

/*******************************************************************************
** Function Name        : CanNm_Memcpy                                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Copy value to target memory                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : bufferDest                                          **
**                      : bufferSource                                        **
**                      : byteNumber                                          **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_Memcpy (uint8 *bufferDest, const uint8 *bufferSource, uint32 byteNumber)
{
  uint32 arrIdx;

  /* Checking whether valid input */
  if((NULL_PTR != bufferDest) && (NULL_PTR != bufferSource))
  {
    for(arrIdx = CANNM_ZERO; arrIdx < byteNumber; arrIdx++)
    {
      /* @Trace: CanNm_SUD_API_258 */
      /* polyspace +4 RTE:NIV [Justified:Low] "They are input parameters." */
      /* polyspace +3 RTE:IDP [Justified:Low] "The length have been generated and checked by generation tool so pointer can not be outside" */
      /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "bufferDest and bufferSource are already checked null before" */
      /* polyspace +1 MISRA2012:18.1 [Justified:Low] "The length have been generated and checked by generation tool so pointer can not be outside" */
      bufferDest[arrIdx] = bufferSource[arrIdx];
    }
  }
  /* polyspace +5 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
  else
  {
    /* @Trace: CanNm_SUD_API_298 */
    #if (CANNM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NODEIDENTIFIER_SID, CANNM_E_PARAM_POINTER);
    #endif
  }
}

#if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
/*******************************************************************************
** Function Name        : CanNm_CarWakeupProcess                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Implement car wakeup process                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChannelIdx                                          **
**                      : PduPtr                                              **
**                      : ptrChannel                                          **
**                      : ptrStaticChannel                                    **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        NA                                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_Memcpy                                        **
**                        Nm_CarWakeUpIndication                              **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_CarWakeupProcess(
  P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduPtr,
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel,
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel)
{
  #if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace +2 RTE:UNR [Justified:Low] "They are input parameters." */
  if ((PduPtr == NULL_PTR) || (ptrChannel == NULL_PTR) || (ptrStaticChannel == NULL_PTR))
  {
    /* @Trace: CanNm_SUD_API_299 */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_GET_NODEIDENTIFIER_SID, CANNM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANNM_DEV_ERROR_DETECT == STD_ON) */
  {
  /* If the Car Wakeup bit within any received NM-PDU is 1 */
  /* polyspace +3 RTE:IDP [Justified:Low] "The length have been generated and checked by generation tool so pointer can not be outside" */
  /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "ptrStaticChannel->carWakeupByte have been generated and checked by generation tool so pointer can not be outside" */
  /* polyspace +1 MISRA2012:18.1 [Justified:Low] "ptrStaticChannel->carWakeupByte have been generated and checked by generation tool so pointer can not be outside" */
  if((PduPtr->SduDataPtr[ptrStaticChannel->carWakeupByte] & \
    (CANNM_ONE << ptrStaticChannel->carWakeupMask)) == (CANNM_ONE << ptrStaticChannel->carWakeupMask))
  { 
    /* @Trace: CanNm_SUD_API_259 */
    /* Create Nm data to store wake up Nm data */
    CanNm_Memcpy(ptrChannel->carWakeUpPdu, ptrChannel->txUserData, ptrStaticChannel->pduLength);

    /* Store data that causes the call of Nm_CarWakeUpIndication */
    CanNm_Memcpy(&(ptrChannel->carWakeUpPdu[CANNM_BYTE0]),
                PduPtr->SduDataPtr,
                PduPtr->SduLength);
    /* CanNmCarWakeUpFilterEnabled is FALSE */
    if(ptrStaticChannel->carWakeUpFilterEnabled == CANNM_FALSE)
    {
      /* @Trace: CanNm_SUD_API_260 */
      /* CanNm shall call Nm_CarWakeUpIndication */
      Nm_CarWakeUpIndication(ptrStaticChannel->comMChannelId);

      ptrChannel->carWakeUpBit = CANNM_TRUE;
    }
    else
    {
      /* CheckCanNmCarWakeUpFilterEnabled is TRUE */
      /* The Node ID in the received NM-PDU is equal to CanNmCarWakeUpFilterNodeId
        the CanNm module shall call Nm_CarWakeUpIndication */
      /* polyspace +4 RTE:IDP [Justified:Low] "The length have been generated and checked by generation tool so pointer can not be outside" */
      /* polyspace +3 MISRA2012:18.1 [Justified:Low] "ptrStaticChannel->pduNidPosition have been generated and checked by generation tool so pointer can not be outside" */
      /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "ptrStaticChannel->pduNidPosition have been generated and checked by generation tool so pointer can not be outside" */
	  /* polyspace +12 RTE:UNR [Justify:Low] "This branch can be reached base on input parameters" */
      if((CANNM_PDU_OFF != ptrStaticChannel->pduNidPosition) &&
        (PduPtr->SduDataPtr[ptrStaticChannel->pduNidPosition] == ptrStaticChannel->carWkpNodeId))
      {
        /* @Trace: CanNm_SUD_API_261 */
        /* CanNm shall call Nm_CarWakeUpIndication */
        Nm_CarWakeUpIndication(ptrStaticChannel->comMChannelId);

        ptrChannel->carWakeUpBit = CANNM_TRUE;
      }
      else
      {
        /* Do nothing */
      }
    }
  }
  else
  {
    /* Do nothing */
  }
  }
}
#endif /* #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_InitERA                                       **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of CanNm_Init() that reset all    **
**                        ERA data.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint32: canNmChannelIndex                           **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : (CANNM_GLOBAL_PN_SUPPORT == STD_ON) &&              **
**                        (CANNM_PN_ERA_CALC_ENABLED == STD_ON)               **
**                                                                            **
** Remarks              : Global Variable(s): CanNm_ArrayChannel              **
**                                                                            **
**                        Function(s) invoked: N/A                            **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_InitERA(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  uint32 arrIdx;

  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  /* Clear ERA Pdu data */
  for (arrIdx = CANNM_ZERO; arrIdx < CanNm_structPnInfo.pnInfoLength; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_004 */
    ptrChannel->eRA[arrIdx] = CANNM_ZERO;
  }

  /* Reset ERA timer */
  for (arrIdx = CANNM_ZERO; arrIdx < CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE * CANNM_EIGHT; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_005 */
    ptrChannel->eRATimer[arrIdx] = CANNM_ZERO;
  }

  /* Set default value for Rx meta data flag */
  ptrChannel->rxMetaDataCheck = CANNM_FALSE;
  /* Set default value for Rx meta data */
  for (arrIdx = CANNM_ZERO; arrIdx < CANNM_METADATA_LENGTH; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_006 */
    ptrChannel->rxMetaData[arrIdx] = CANNM_ZERO;
  }
}
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_InitEIRA                                      **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of CanNm_Init() that reset all    **
**                        EIRA data.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : N/A                                                 **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : N/A                                                 **
**                                                                            **
** Preconditions        : (CANNM_GLOBAL_PN_SUPPORT == STD_ON) &&              **
**                        (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)              **
**                                                                            **
** Remarks              : Global Variable(s): CanNm_structPnInfo              **
**                        CanNm_ArrayPnEIRAPdu                                **
**                        CanNm_ArrayPnEIRATimer                              **
**                        CanNm_RxMetaDataCheck                               **
**                        CanNm_RxMetaData                                    **
**                                                                            **
**                        Function(s) invoked: N/A                            **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_InitEIRA(void)
{
  uint32 arrIdx;
  /* Clear EIRA Pdu data */
  for (arrIdx = CANNM_ZERO; arrIdx < CanNm_structPnInfo.pnInfoLength; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_011 */
    CanNm_ArrayPnEIRAPdu[arrIdx] = CANNM_ZERO;
  }

  /* Reset EIRA timer */
  for (arrIdx = CANNM_ZERO; arrIdx < CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE * CANNM_EIGHT; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_012 */
    CanNm_ArrayPnEIRATimer[arrIdx] = CANNM_ZERO;
  }

  /* Set default value for Rx meta data flag */
  CanNm_RxMetaDataCheck = CANNM_FALSE;
  /* Set default value for Rx meta data */
  for (arrIdx = CANNM_ZERO; arrIdx < CANNM_METADATA_LENGTH; arrIdx++)
  {
    /* @Trace: CanNm_SUD_API_013 */
    CanNm_RxMetaData[arrIdx] = CANNM_ZERO;
  }
}
#endif

/*******************************************************************************
** Function Name        : CanNm_ExitCurrentState                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of CanNm_MainFunction() that      **
**                        check current mode, state to call the corresponding **
**                        exit functions.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint32: canNmChannelIndex                           **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : N/A                                                 **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s): N/A                             **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntExitPrepareBusSleepMode                    **
**                        CanNm_IntExitReadySleepState                        **
**                        CanNm_IntExitNetworkMode                            **
**                        CanNm_IntExitNormalOperationState                   **
**                        CanNm_IntExitRepeatMessageState                     **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_ExitCurrentState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];

  switch (ptrChannel->modeStatus)
  {
    case CANNM_BUS_SLEEP_MODE:
      /* Do nothing */
      break;

    case CANNM_PREPAREBUS_SLEEP_MODE:
      /* @Trace: CanNm_SUD_API_149 */
      CanNm_IntExitPrepareBusSleepMode(canNmChannelIndex);
      break;

    case CANNM_READY_SLEEP_STATE:
      /* @Trace: CanNm_SUD_API_150 */
      CanNm_IntExitReadySleepState(canNmChannelIndex);

      if (ptrChannel->nextModeState == CANNM_PREPAREBUS_SLEEP_MODE)
      {
        /* @Trace: CanNm_SUD_API_151 */
        CanNm_IntExitNetworkMode(canNmChannelIndex);
      }
      else
      {
        /* Do nothing */
      }
      break;

    case CANNM_NORMAL_OPERATION_STATE:
      /* @Trace: CanNm_SUD_API_152 */
      CanNm_IntExitNormalOperationState(canNmChannelIndex);
      break;

    case CANNM_REPEAT_MESSAGE_STATE:
      /* @Trace: CanNm_SUD_API_153 */
      CanNm_IntExitRepeatMessageState(canNmChannelIndex);
      break;

    default:
      /* Do nothing */
      break;
  }
}


/*******************************************************************************
** Function Name        : CanNm_EntryNextState                                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of CanNm_MainFunction() that      **
**                        check next mode, state to call the corresponding    **
**                        entry functions.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint32: canNmChannelIndex                           **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : N/A                                                 **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s): CanNm_ArrayChannel              **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntEntryBusSleepMode                          **
**                        CanNm_IntEntryPrepareBusSleepMode                   **
**                        CanNm_IntEntryReadySleepState                       **
**                        CanNm_IntEntryNormalOperationState                  **
**                        CanNm_IntNetworkModeEntry                           **
**                        CanNm_IntEntryRepeatMessageState                    **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_EntryNextState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  switch (ptrChannel->nextModeState)
  {
    case CANNM_BUS_SLEEP_MODE:
      /* @Trace: CanNm_SUD_API_154 */
      CanNm_IntEntryBusSleepMode(canNmChannelIndex);
      break;

    case CANNM_PREPAREBUS_SLEEP_MODE:
      /* @Trace: CanNm_SUD_API_155 */
      CanNm_IntEntryPrepareBusSleepMode(canNmChannelIndex);
      break;

    case CANNM_READY_SLEEP_STATE:
      /* @Trace: CanNm_SUD_API_156 */
      CanNm_IntEntryReadySleepState(canNmChannelIndex);
      break;

    case CANNM_NORMAL_OPERATION_STATE:
      /* @Trace: CanNm_SUD_API_157 */
      CanNm_IntEntryNormalOperationState(canNmChannelIndex);
      break;

    case CANNM_REPEAT_MESSAGE_STATE:
      if ((ptrChannel->modeStatus == CANNM_BUS_SLEEP_MODE) ||
          (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE))
      {
        /* @Trace: CanNm_SUD_API_158 */
        CanNm_IntNetworkModeEntry(canNmChannelIndex);
      }
      else
      {
        /* Do nothing */
      }
      /* @Trace: CanNm_SUD_API_159 */
      CanNm_IntEntryRepeatMessageState(canNmChannelIndex);
      break;

    default:
      /* Do nothing */
      break;
  }
}

/*******************************************************************************
** Function Name        : CanNm_ImplementCurrentState                         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of CanNm_MainFunction() that      **
**                        check the mode, state change to call the            **
**                        corresponding process functions.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint32: canNmChannelIndex                           **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : N/A                                                 **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s): N/A                             **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanNm_IntPrepareBusSleepMode                        **
**                        CanNm_IntReadySleepState                            **
**                        CanNm_IntNormalOperationState                       **
**                        CanNm_IntRepeatMessageState                         **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_ImplementCurrentState(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  switch (ptrChannel->modeStatus)
  {
    case CANNM_BUS_SLEEP_MODE:
      /* Do nothing */
      break;

    case CANNM_PREPAREBUS_SLEEP_MODE:
      /* @Trace: CanNm_SUD_API_160 */
      CanNm_IntPrepareBusSleepMode(canNmChannelIndex);
      break;

    case CANNM_READY_SLEEP_STATE:
      /* @Trace: CanNm_SUD_API_161 */
      CanNm_IntReadySleepState(canNmChannelIndex);
      break;

    case CANNM_NORMAL_OPERATION_STATE:
      /* @Trace: CanNm_SUD_API_162 */
      CanNm_IntNormalOperationState(canNmChannelIndex);
      break;

    case CANNM_REPEAT_MESSAGE_STATE:
      /* @Trace: CanNm_SUD_API_163 */
      CanNm_IntRepeatMessageState(canNmChannelIndex);
      break;

    default:
      /* Do nothing */
      break;
  }
}


/*******************************************************************************
** Function Name        : CanNm_RxIndicationSetInternalStatus                 **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of CanNm_RxIndication() that set  **
**                        internal status.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint32: canNmChannelIndex                           **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : N/A                                                 **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s): CanNm_ArrayChannel              **
**                        CanNm_ArrayStaticChannel                            **
**                                                                            **
**                        Function(s) invoked:                                **
**                        SchM_Enter_CanNm_INTERNAL_STATUS                    **
**                        Det_ReportRuntimeError                              **
**                        Nm_NetworkStartIndication                           **
**                        Nm_RepeatMessageIndication                          **
**                        Nm_CoordReadyToSleepIndication                      **
**                        Nm_RemoteSleepCancellation                          **
**                        SchM_Exit_CanNm_INTERNAL_STATUS                     **
*******************************************************************************/
FUNC(void, CANNM_CODE) CanNm_RxIndicationSetInternalStatus(uint32 canNmChannelIndex)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;

  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];

  SchM_Enter_CanNm_INTERNAL_STATUS();
  /* Notify to upper layer to start passive start up if CanNm is current in bus sleep mode */
  if (ptrChannel->modeStatus == CANNM_BUS_SLEEP_MODE)
  {
    /* @Trace: CanNm_SUD_API_130 */
    (void)Det_ReportRuntimeError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_RX_INDICATION_SID, CANNM_E_NET_START_IND);

    Nm_NetworkStartIndication(ptrStaticChannel->comMChannelId);
  }
  else if (ptrChannel->modeStatus == CANNM_PREPAREBUS_SLEEP_MODE)
  {
    /* @Trace: CanNm_SUD_API_131 */
    ptrChannel->nextModeState = CANNM_REPEAT_MESSAGE_STATE;
  }
  else if ((ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE) ||
           (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE) ||
           (ptrChannel->modeStatus == CANNM_REPEAT_MESSAGE_STATE))
  {
  #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  if (ptrChannel->communicationEnabled == CANNM_TRUE)
  {
    /* @Trace: CanNm_SUD_API_132 */
    ptrChannel->ntwkTimeOutTime = ptrStaticChannel->ntwkTimeOutTime;
  }
  else
  {
    /* Do nothing */
  }
  #endif /* #if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

  /* Change state to repeat message state if repeat message bit received in Rx have been set to 1 */
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "This condition be false with different configruation" */
  if (ptrStaticChannel->nodeDetectionEnabled == CANNM_TRUE)
  {
	/* polyspace +1 RTE:OBAI [Justified:Low] "The length have been generated and checked by generation tool so pointer can not be outside" */
    if (((ptrChannel->rxUserData[ptrStaticChannel->pduCbvPosition]) & CANNM_REPTMSG_BIT) != CANNM_ZERO)
    {
      if ((ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE) || (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE))
    {
      /* @Trace: CanNm_SUD_API_133 */
      ptrChannel->nextModeState = CANNM_REPEAT_MESSAGE_STATE;
    }
    else
    {
      /* Do nothing */
    }

      /* @Trace: CanNm_SUD_API_134 */
      #if (CANNM_REPEAT_MSG_IND_ENABLED == STD_ON)
      Nm_RepeatMessageIndication(ptrStaticChannel->comMChannelId);
      #endif /* #if (CANNM_REPEAT_MSG_IND_ENABLED == STD_ON) */
    }
    else
    {
      /* Do nothing */
    }
  }
    else
    {
    /* Do nothing */
    }

  #if (CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON)
    if (((ptrChannel->rxUserData[ptrStaticChannel->pduCbvPosition]) & CANNM_SETSLEEP_BIT) != CANNM_ZERO)
    {
      /* Check if Nm_CoordReadyToSleepIndication have not been invoked before */
      if (ptrChannel->nmCoordReadyToSleepIndicationCalled == CANNM_FALSE)
      {
        /* @Trace: CanNm_SUD_API_135 */
      /* Notify to upper layer */
      Nm_CoordReadyToSleepIndication(ptrStaticChannel->comMChannelId);
      /* Update status for received in the 1st time */
      ptrChannel->nmCoordReadyToSleepIndicationCalled = CANNM_TRUE;
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Check if Nm_CoordReadyToSleepIndication have been invoked before */
      if (ptrChannel->nmCoordReadyToSleepIndicationCalled == CANNM_TRUE)
      {
      /* @Trace: CanNm_SUD_API_136 */
      /* Notify to upper layer */
      Nm_CoordReadyToSleepCancellation(ptrStaticChannel->comMChannelId);
      /* Update status for received in the 1st time */
      ptrChannel->nmCoordReadyToSleepIndicationCalled = CANNM_FALSE;
      }
      else
      {
        /* Do nothing */
      }
    }
  #endif /* #if (CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

  #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
  if (ptrChannel->remoteSlpDetect == CANNM_TRUE)
  {
    if ((ptrChannel->modeStatus == CANNM_READY_SLEEP_STATE) || (ptrChannel->modeStatus == CANNM_NORMAL_OPERATION_STATE))
    {
    /* @Trace: CanNm_SUD_API_137 */
    ptrChannel->remoteSlpDetect = CANNM_FALSE;

    Nm_RemoteSleepCancellation(ptrStaticChannel->comMChannelId);
    }
    else
    {
    /* Do nothing */
    }
  }
  else
  {
    /* Do nothing */
  }
  #endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */
  }
  else
  {
    /* Do nothing */
  }
  SchM_Exit_CanNm_INTERNAL_STATUS();
}

#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON))
/*******************************************************************************
** Function Name        : CanNm_RequestBusSynTransmit                         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Internal function of                                **
**                        CanNm_RequestBusSynchronization() that transmit     **
**                        Pdu information through CanIf.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint32: canNmChannelIndex                           **
**                        PduInfoType *structPduInfoType                      **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) &&          **
**                        (CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)       **
**                                                                            **
** Remarks              : Global Variable(s): CanNm_ArrayChannel              **
**                        CanNm_ArrayStaticChannel                            **
**                                                                            **
**                        Function(s) invoked:                                **
**                        CanIf_Transmit                                      **
*******************************************************************************/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynTransmit(
    uint32 canNmChannelIndex,
    P2CONST(PduInfoType, AUTOMATIC, CANNM_CONST) structPduInfoType)
{
  P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel;
  P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel;
  Std_ReturnType returnValue = E_NOT_OK;
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_CONST) ptrPostBuildChannel;
  #endif

  ptrChannel = &CanNm_ArrayChannel[canNmChannelIndex];
  ptrStaticChannel = &CanNm_ArrayStaticChannel[canNmChannelIndex];
  #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
  ptrPostBuildChannel = &CanNm_ChannelsDataPtr[canNmChannelIndex];
  #endif

  #if(CANNM_COM_CONTROL_ENABLED == STD_ON)
  /* polyspace +2 DEFECT:USELESS_IF [Justified:Low] "Value of communicationEnabled can be changed to FALSE by API CanNm_DisableCommunication" */
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of communicationEnabled can be changed to FALSE by API CanNm_DisableCommunication" */
  if(ptrChannel->communicationEnabled == CANNM_TRUE)
  #endif /* #if(CANNM_COM_CONTROL_ENABLED == STD_ON) */
  {
  /* @Trace: CanNm_SUD_API_099 */
    #if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
    returnValue = CanIf_Transmit(ptrPostBuildChannel->txPduId,
                      structPduInfoType);
    #else
    returnValue = CanIf_Transmit(ptrStaticChannel->txPduId,
                    structPduInfoType);
    #endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
  }
  #if(CANNM_COM_CONTROL_ENABLED == STD_ON)
  else
  {
    /* Do nothing */
  }
  #endif /* #if(CANNM_COM_CONTROL_ENABLED == STD_ON) */
  return returnValue;
}
#endif /* #if ((CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON) && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)) */

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
