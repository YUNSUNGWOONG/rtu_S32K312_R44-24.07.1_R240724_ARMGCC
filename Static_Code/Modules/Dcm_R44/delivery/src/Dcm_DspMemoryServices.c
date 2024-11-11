/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_DspMemoryServices.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Main processing for service related to memory                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   HueKM          AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Changes made as per #14836          **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

/* polyspace:begin<RTE: OVFL : Not a defect : No Action Planned > Overflow can not occur */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Externals.h"
#include "Dcm_DspMemoryServices.h"
#include "Dcm_ReqRespHandling.h"
#include "Dcm_Utils.h"
#include "Dcm_Validate.h"

/*******************************************************************************
**                      Macros Definitions                                    **
*******************************************************************************/
#define UNUSED_MEM_ID (0)

/*******************************************************************************
**                      Function Declarations                                 **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)

static FUNC(boolean, DCM_CODE) Dcm_IsReqReadDataLenValid(
  uint32 ReqDataLen
  , uint32 MemAddrBytes
  , uint32 MemSizeBytes);

#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)

static FUNC(boolean, DCM_CODE) Dcm_IsReqWriteDataLenValid(
  uint32 ReqDataLen
  , uint32 MemAddrBytes
  , uint32 MemSizeBytes
  , uint32 MemSize);

static FUNC(boolean, DCM_CODE) Dcm_IsWriteMemoryRangeValid(
  uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_Uint8PtrType pFoundMemRngIndex);

#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_DcmReadMemoryByAddress                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : ReadMemoryByAddress service is used to get data     **
**                        from requested memory address.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_ServiceForcePendingStatus                       **
**                        Dcm_GddOpStatus , Dcm_GddNegRespError               **
**                        Dcm_GusMaxNoOfForceRespPend,Dcm_GaaReadMemRngConfig **
**                        Dcm_GaaAddressAndLengthFormatIds ,                  **
**                        Dcm_GulRMBAMemoryAddress, Dcm_GaaModeRuleConfig     **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSecurity,                            **
**                        Dcm_DcmReadMemoryCall, Dcm_ExternalSetNegResponse , **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/* @Trace: SWS_Dcm_00492 */
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadMemoryByAddress(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  boolean IsReadMemoryApiInvoked = DCM_FALSE;

  Dcm_GddOpStatus = DCM_INITIAL;
  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_GusMaxNoOfForceRespPend = 0;

  Dcm_Uint8PtrType pReqData = pMsgContext->reqData;
  uint8 AddressLenFormatId = pReqData[0];

  boolean IsItemFound = DCM_TRUE;

  /* 3 = AddressLenFormatId(1) + memoryAddress(1) + memorySize(1) */
  if (pMsgContext->reqDataLen < DCM_THREE)
  {
  	IsItemFound = DCM_FALSE;
  }
  CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  
  if (DCM_TRUE == IsItemFound)
  {
    /* @Trace: SWS_Dcm_00853 */
    /* @Trace: Dcm_SUD_API_31101 */
    #if (0 < DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG)
    IsItemFound = Dcm_IsAddrLenFormatIdSupported(AddressLenFormatId);
    CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
    if (DCM_TRUE == IsItemFound)
    #endif
    {
      /* @Trace: Dcm_SUD_API_31102 */
      uint8 MemAddrBytes = (AddressLenFormatId & DCM_SIG_BYTE_MASK_VALUE);
      uint8 MemSizeBytes = ((AddressLenFormatId & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);
	
      IsItemFound = Dcm_IsReqReadDataLenValid(pMsgContext->reqDataLen, MemAddrBytes, MemSizeBytes);
      CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      if (DCM_TRUE == IsItemFound)
      {
        /* @Trace: Dcm_SUD_API_31103 */
        #if (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON)
        uint8 MemoryIdentifier = pReqData[1];
        #endif
        uint32 MemoryAddress = Dcm_ReadMemoryAddressFromReqData(&pReqData[1], MemAddrBytes);
        uint32 MemorySize = Dcm_ReadMemorySizeFromReqData(&pReqData[1 + MemAddrBytes], MemSizeBytes);

        uint8 FoundMemRngIdx;
        /* @Trace: SWS_Dcm_00493 */
        IsItemFound = Dcm_IsReadMemoryRangeValid(MemoryAddress, MemorySize, &FoundMemRngIdx);
        CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
        if (DCM_TRUE == IsItemFound)
        {
          /* @Trace: Dcm_SUD_API_31104 */
          #if ((DCM_IS_SESSION_IN_READ_MEMORY_RANGE_CONFIGURED == STD_ON) || \
              (DCM_IS_SECURITY_IN_READ_MEMORY_RANGE_CONFIGURED == STD_ON) || \
              (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON) || \
              (DCM_MODE_RULE == STD_ON))
          Dcm_ReadMemRngInfoConfigConstPtrType pReadMemRngInfoCfg;
          pReadMemRngInfoCfg = &Dcm_GaaReadMemRngConfig[FoundMemRngIdx];
          boolean SearchResult = DCM_TRUE;
          #endif

          #if (DCM_IS_SECURITY_IN_READ_MEMORY_RANGE_CONFIGURED == STD_ON)
          if (NULL_PTR != pReadMemRngInfoCfg->pReadMemRngSec)
          {
            /* @Trace: SWS_Dcm_00494 */
            /* @Trace: Dcm_SUD_API_31105 */
            SearchResult = Dcm_DsdValidateSecurity(
              pReadMemRngInfoCfg->pReadMemRngSec, pReadMemRngInfoCfg->ucReadMemSecCount);
            CHK_RET_VAL(DCM_FALSE == SearchResult, Dcm_GddNegRespError, DCM_E_SECURITYACCESSDENIED);
          }
          #endif

          #if (DCM_IS_SESSION_IN_READ_MEMORY_RANGE_CONFIGURED == STD_ON)
          if ((DCM_TRUE == SearchResult) && (NULL_PTR != pReadMemRngInfoCfg->pReadMemRngSes))
          {
            /* @Trace: SWS_Dcm_01359 */
            /* @Trace: Dcm_SUD_API_31106 */
            SearchResult = Dcm_DsdValidateSession(
              pReadMemRngInfoCfg->pReadMemRngSes, pReadMemRngInfoCfg->ReadMemSesCount);
            CHK_RET_VAL(DCM_FALSE == SearchResult, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
          }
          #endif

          #if (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON)
          if ((DCM_TRUE == SearchResult) && (DCM_TRUE == pReadMemRngInfoCfg->blUseMemoryValue))
          {
            /* @Trace: SWS_Dcm_01053 */
            uint8 MemIdVal = pReadMemRngInfoCfg->ucReadMemoryIdentifier;

            /* @Trace: Dcm_SUD_API_31109 Dcm_SUD_API_31108 */
            SearchResult = (MemoryIdentifier == MemIdVal) ? DCM_TRUE : DCM_FALSE;
            CHK_RET_VAL(DCM_FALSE == SearchResult, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
          }
          #endif

          #if (DCM_MODE_RULE == STD_ON)
          /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
          if (DCM_TRUE == SearchResult)
          {
            /* @Trace: SWS_Dcm_00826 */
            /* @Trace: Dcm_SUD_API_31111 */
            boolean ModeRuleConfigured = pReadMemRngInfoCfg->blModeRuleConfigured;
            Dcm_ModeType ModeIndex = pReadMemRngInfoCfg->ucDIDmoderuleArrayindex;
            Dcm_GddNegRespError = Dcm_CheckModeRule(ModeRuleConfigured, ModeIndex);
          }
          #endif

          if (DCM_POS_RESP == Dcm_GddNegRespError)
          {
            Dcm_GulRMBAMemoryAddress = MemoryAddress;
            Dcm_GusRMBAMemorySize = MemorySize;

            /* @Trace: Dcm_SUD_API_31114 Dcm_SUD_API_31113 */
            #if (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON)
            Dcm_GucRMBAMemoryIdentifier = (DCM_TRUE == pReadMemRngInfoCfg->blUseMemoryValue) ? MemoryIdentifier : UNUSED_MEM_ID;
            #else
            Dcm_GucRMBAMemoryIdentifier = UNUSED_MEM_ID;
            #endif

            IsReadMemoryApiInvoked = DCM_TRUE;
            Dcm_DcmReadMemoryCall(pMsgContext);
          }
        }
      }
    }
  }
  
  if (DCM_FALSE == IsReadMemoryApiInvoked)
  {
    /* @Trace: Dcm_SUD_API_31116 */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_DcmReadMemoryCall                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmReadMemoryCall function is used to call      **
**                        Dcm_ReadMemory callout.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError           **
**                        Dcm_MemServicePendingStatus,Dcm_GddOpStatus         **
**                        Dcm_GulRMBAMemoryAddress , Dcm_GusRMBAMemorySize    **
**                        Dcm_ServiceForcePendingStatus,Dcm_GpMsgContext      **
**                        Dcm_GusRMBAMemorySize , Dcm_GusMaxNoOfForceRespPend,**
**                        Dcm_TxRespStatus                                    **
**                        Function(s) invoked :                               **
**                        Dcm_ReadMemory, Dcm_DslPduRTransmit ,               **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmReadMemoryCall(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_GddNegRespError = DCM_POS_RESP;

  Dcm_MemServicePendingStatus.ucReadMemPendingStatus = DCM_FALSE;
  Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus = DCM_FALSE;

  uint8 MemoryIdentifier = Dcm_GucRMBAMemoryIdentifier;
  uint32 MemoryAddress = Dcm_GulRMBAMemoryAddress;
  uint32 MemorySize = Dcm_GusRMBAMemorySize;

  /* @Trace: SWS_Dcm_00495 */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00539, the function Dcm_ReadMemory has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_ReadMemory." */
  Dcm_ReturnReadMemoryType RetVal = Dcm_ReadMemory(Dcm_GddOpStatus, MemoryIdentifier,
    MemoryAddress, MemorySize, pMsgContext->resData, &Dcm_GddNegRespError);

  if (DCM_CANCEL != Dcm_GddOpStatus)
  {
    if (DCM_READ_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_31119 */
      Dcm_GddOpStatus = DCM_INITIAL;
      pMsgContext->resDataLen = MemorySize;
    }
    else if (DCM_READ_PENDING == RetVal)
    {
      /* @Trace: Dcm_SUD_API_31120 */
      Dcm_GddOpStatus = DCM_PENDING;
      Dcm_MemServicePendingStatus.ucReadMemPendingStatus = DCM_TRUE;
    }
    else if (DCM_READ_FORCE_RCRRP == RetVal)
    {
      /* @Trace: SWS_Dcm_00839 */
      /* @Trace: Dcm_SUD_API_31118 */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus = DCM_TRUE;
      Dcm_GusMaxNoOfForceRespPend++;

      /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
      /* 0xFF : limit threshold is unused */
      if (DCM_FALSE == Dcm_ChkNumRespPend(DCM_READ_MEMORY_SID, Dcm_GusMaxNoOfForceRespPend))
      {
        /* @Trace: Dcm_SUD_API_31121 */
        Dcm_GddOpStatus = DCM_INITIAL;
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        Dcm_GusMaxNoOfForceRespPend = 0;

        (void)Dcm_ReadMemory(DCM_CANCEL, MemoryIdentifier,
          MemoryAddress, MemorySize, pMsgContext->resData, &Dcm_GddNegRespError);

        Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus = DCM_FALSE;
      }
    }
    else
    {
      /* @Trace: SWS_Dcm_00644 */
      /* @Trace: Dcm_SUD_API_31122 */
      CHK_ERRCODE_IN_FAIL_CASE(DCM_READ_MEMORY_SID, Dcm_GddNegRespError);
    }
  }

  /* To send positive and negative response */
  if ((DCM_FALSE == Dcm_MemServicePendingStatus.ucReadMemPendingStatus)
      && (DCM_FALSE == Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus)
      && (DCM_CANCEL != Dcm_GddOpStatus))
  {
    /* @Trace: Dcm_SUD_API_31123 */
    Dcm_GddOpStatus = DCM_INITIAL;
    Dcm_GblSendResponse = DCM_TRUE;
  }
  /* To send response pending */
  else if (DCM_TRUE == Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus)
  {
    /* @Trace: Dcm_SUD_API_31124 */
    Dcm_SetNegResp(pMsgContext->idContext & DCM_BIT6_AND_MASK
      , DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00539, the function Dcm_ReadMemory has return 4 values.
   So, Dcm must be implement to cover all return value of function Dcm_ReadMemory." */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmWriteMemoryByAddress                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmWriteMemoryByAddress service is used to      **
**                        write data using a physical memory address          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GusMaxNoOfForceRespPend,    **
**                        Dcm_GddNegRespError , Dcm_GddOpStatus,              **
**                        Dcm_GaaAddressAndLengthFormatIds ,Dcm_GpWriteData   **
**                        Dcm_GucMemAddrSizeBytes, Dcm_GaaWriteMemRngConfig   **
**                        Dcm_GulWriteMemoryAddress, Dcm_GusWriteMemorySize   **
**                        Dcm_GucMemoryIdentifier, Dcm_GaaModeRuleConfig      **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSecurity,                            **
**                        Dcm_DcmWriteMemoryCall, Dcm_ExternalSetNegResponse ,**
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/* @Trace: SWS_Dcm_00488 */
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmWriteMemoryByAddress(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  boolean IsWriteMemoryApiInvoked = DCM_FALSE;

  Dcm_GusMaxNoOfForceRespPend = DCM_POS_RESP;
  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_GddOpStatus = DCM_INITIAL;

  Dcm_Uint8PtrType pReqData = pMsgContext->reqData;
  uint8 AddressLenFormatId = pReqData[0];

  boolean IsItemFound = DCM_TRUE;

  /* 4 = AddressLenFormatId(1) + memoryAddress(1) + memorySize(1) + dataRecord(1) */
  if (pMsgContext->reqDataLen < DCM_FOUR)
  {
  	IsItemFound = DCM_FALSE;
  }
  CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  
  if (DCM_TRUE == IsItemFound)
  {
    /* @Trace: SWS_Dcm_00855 */
    /* @Trace: Dcm_SUD_API_31126 */
    #if (0 < DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG)
    IsItemFound = Dcm_IsAddrLenFormatIdSupported(AddressLenFormatId);
    CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
    if (DCM_TRUE == IsItemFound)
    #endif
    {
      /* @Trace: Dcm_SUD_API_31127 */
      uint8 MemAddrBytes = (AddressLenFormatId & DCM_SIG_BYTE_MASK_VALUE);
      uint8 MemSizeBytes = ((AddressLenFormatId & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);
      #if (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON)
      uint8 MemoryIdentifier = pReqData[1];
      #endif
      
      uint32 MemoryAddress = Dcm_ReadMemoryAddressFromReqData(&pReqData[1], MemAddrBytes);
      uint32 MemorySize = Dcm_ReadMemorySizeFromReqData(&pReqData[1 + MemAddrBytes], MemSizeBytes);
      Dcm_GucMemAddrSizeBytes = MemAddrBytes + MemSizeBytes + 1;
      Dcm_GpWriteData = &pReqData[Dcm_GucMemAddrSizeBytes];

      IsItemFound = Dcm_IsReqWriteDataLenValid(pMsgContext->reqDataLen, MemAddrBytes, MemSizeBytes, MemorySize);
      CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      if (DCM_TRUE == IsItemFound)
      {
        /* @Trace: Dcm_SUD_API_31128 */
        uint8 FoundMemRngIdx;

        /* @Trace: SWS_Dcm_00489 */
        IsItemFound = Dcm_IsWriteMemoryRangeValid(MemoryAddress, MemorySize, &FoundMemRngIdx);
        CHK_RET_VAL(DCM_FALSE == IsItemFound, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
        if (DCM_TRUE == IsItemFound)
        {
          /* @Trace: Dcm_SUD_API_31129 */
          #if ((DCM_IS_SESSION_IN_WRITE_MEMORY_RANGE_CONFIGURED == STD_ON) || \
              (DCM_IS_SECURITY_IN_WRITE_MEMORY_RANGE_CONFIGURED == STD_ON) || \
              (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON) || \
              (DCM_MODE_RULE == STD_ON))
          Dcm_WriteMemRngInfoConfigConstPtrType pWriteMemRngInfoCfg;
          pWriteMemRngInfoCfg = &Dcm_GaaWriteMemRngConfig[FoundMemRngIdx];

          boolean SearchResult = DCM_TRUE;
          #endif

          #if (DCM_IS_SECURITY_IN_WRITE_MEMORY_RANGE_CONFIGURED == STD_ON)
          if (NULL_PTR != pWriteMemRngInfoCfg->pWriteMemRngSec)
          {
            /* @Trace: SWS_Dcm_00490 */
            /* @Trace: Dcm_SUD_API_31130 */
            SearchResult = Dcm_DsdValidateSecurity(
              pWriteMemRngInfoCfg->pWriteMemRngSec, pWriteMemRngInfoCfg->ucWriteMemSecCount);
            CHK_RET_VAL(DCM_FALSE == SearchResult, Dcm_GddNegRespError, DCM_E_SECURITYACCESSDENIED);
          }
          #endif

          #if (DCM_IS_SESSION_IN_WRITE_MEMORY_RANGE_CONFIGURED == STD_ON)
          if ((DCM_TRUE == SearchResult) && (NULL_PTR != pWriteMemRngInfoCfg->pWriteMemRngSes))
          {
            /* @Trace: SWS_Dcm_01358 */
            /* @Trace: Dcm_SUD_API_31131 */
            SearchResult = Dcm_DsdValidateSession(
              pWriteMemRngInfoCfg->pWriteMemRngSes, pWriteMemRngInfoCfg->WriteMemSesCount);
            CHK_RET_VAL(DCM_FALSE == SearchResult, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
          }
          #endif

          #if (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON)
          if ((DCM_TRUE == SearchResult) && (DCM_TRUE == pWriteMemRngInfoCfg->blUseMemoryValue))
          {
            /* @Trace: SWS_Dcm_01052 */
            uint8 MemIdVal = pWriteMemRngInfoCfg->ucWriteMemoryIdentifier;

            /* @Trace: Dcm_SUD_API_31133 Dcm_SUD_API_31134 */
            SearchResult = (MemoryIdentifier == MemIdVal) ? DCM_TRUE : DCM_FALSE;
            CHK_RET_VAL(DCM_FALSE == SearchResult, Dcm_GddNegRespError, DCM_E_REQUESTOUTOFRANGE);
          }
          #endif

          #if (DCM_MODE_RULE == STD_ON)
          if (DCM_TRUE == SearchResult)
          {
            /* @Trace: SWS_Dcm_00825 */
            /* @Trace: Dcm_SUD_API_31136 */
            boolean ModeRuleConfigured = pWriteMemRngInfoCfg->blModeRuleConfigured;
            Dcm_ModeType ModeIndex = pWriteMemRngInfoCfg->ucDIDmoderuleArrayindex;
            Dcm_GddNegRespError = Dcm_CheckModeRule(ModeRuleConfigured, ModeIndex);
          }
          #endif

          if (DCM_POS_RESP == Dcm_GddNegRespError)
          {
            Dcm_GulWriteMemoryAddress = MemoryAddress;
            Dcm_GusWriteMemorySize = MemorySize;

            /* @Trace: Dcm_SUD_API_31139 Dcm_SUD_API_31138 */
            #if (DCM_IS_MEMORY_IDVALUE_CONFIGURED == STD_ON)
            Dcm_GucMemoryIdentifier = (DCM_TRUE == pWriteMemRngInfoCfg->blUseMemoryValue) ? MemoryIdentifier : UNUSED_MEM_ID;
            #else
            Dcm_GucMemoryIdentifier = UNUSED_MEM_ID;
            #endif

            IsWriteMemoryApiInvoked = DCM_TRUE;
            Dcm_DcmWriteMemoryCall(pMsgContext);
          }
        }
      }
    }
  }

  if (DCM_FALSE == IsWriteMemoryApiInvoked)
  {
    /* @Trace: Dcm_SUD_API_31141 */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_DcmWriteMemoryCall                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmWriteMemoryCall function is used to call     **
**                        Dcm_WriteMemory call out.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :Dcm_GddNegRespError,           **
**                        Dcm_MemServicePendingStatus ,Dcm_GddOpStatus        **
**                        Dcm_GulWriteMemoryAddress ,Dcm_GusWriteMemorySize , **
**                        Dcm_GucMemoryIdentifier, Dcm_GucMemAddrSizeBytes    **
**                        Dcm_ServiceForcePendingStatus ,                     **
**                        Dcm_GusMaxNoOfForceRespPend,                        **
**                        Dcm_TxRespStatus                                    **
**                        Function(s) invoked :                               **
**                        Dcm_WriteMemory, Dcm_DslPduRTransmit ,              **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmWriteMemoryCall(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_GddNegRespError = DCM_POS_RESP;

  Dcm_MemServicePendingStatus.ucWriteMemPendingStatus = DCM_FALSE;
  Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus = DCM_FALSE;

  uint8 MemoryIdentifier = Dcm_GucMemoryIdentifier;
  uint32 MemoryAddress = Dcm_GulWriteMemoryAddress;
  uint32 MemorySize = Dcm_GusWriteMemorySize;

  /* @Trace: SWS_Dcm_00491 */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00540, the function Dcm_WriteMemory has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_WriteMemory." */
  Dcm_ReturnWriteMemoryType RetVal = Dcm_WriteMemory(Dcm_GddOpStatus, MemoryIdentifier,
    MemoryAddress, MemorySize, Dcm_GpWriteData, &Dcm_GddNegRespError);

  if (DCM_CANCEL != Dcm_GddOpStatus)
  {
    if (DCM_WRITE_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_31144 */
      pMsgContext->resDataLen = Dcm_GucMemAddrSizeBytes;
      Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, Dcm_GucMemAddrSizeBytes);
      Dcm_GddOpStatus = DCM_INITIAL;
    }
    else if (DCM_WRITE_PENDING == RetVal)
    {
      /* @Trace: Dcm_SUD_API_31145 */
      Dcm_GddOpStatus = DCM_PENDING;
      Dcm_MemServicePendingStatus.ucWriteMemPendingStatus = DCM_TRUE;
    }
    else if (DCM_WRITE_FORCE_RCRRP == RetVal)
    {
      /* @Trace: SWS_Dcm_00837 */
      /* @Trace: Dcm_SUD_API_31147 */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus = DCM_TRUE;
      Dcm_GusMaxNoOfForceRespPend++;

      /* Check for Dcm_GusMaxNoOfForceRespPend */
      /* 0xFF : limit threshold is unused */
      if (DCM_FALSE == Dcm_ChkNumRespPend(DCM_WRITE_MEMORY_SID, Dcm_GusMaxNoOfForceRespPend))
      {
        /* @Trace: Dcm_SUD_API_31148 */
        Dcm_GddOpStatus = DCM_INITIAL;
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        Dcm_GusMaxNoOfForceRespPend = 0;

        (void) Dcm_WriteMemory(DCM_CANCEL, MemoryIdentifier,
          MemoryAddress, MemorySize, Dcm_GpWriteData, &Dcm_GddNegRespError);

        Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus = DCM_FALSE;
      }
    }
    else
    {
      /* @Trace: SWS_Dcm_00643 */
      /* @Trace: Dcm_SUD_API_31146 */
      CHK_ERRCODE_IN_FAIL_CASE(DCM_WRITE_MEMORY_SID, Dcm_GddNegRespError);
    }
  }

  /* To send positive and negative response */
  if ((DCM_FALSE == Dcm_MemServicePendingStatus.ucWriteMemPendingStatus)
      && (DCM_FALSE == Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus)
      && (DCM_CANCEL != Dcm_GddOpStatus))
  {
    /* @Trace: Dcm_SUD_API_31149 */
    Dcm_GddOpStatus = DCM_INITIAL;
    Dcm_GblSendResponse = DCM_TRUE;
  }
  /* To send response pending */
  else if (DCM_TRUE == Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus)
  {
    /* @Trace: Dcm_SUD_API_31150 */
    Dcm_SetNegResp(pMsgContext->idContext & DCM_BIT6_AND_MASK
      , DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00540, the function Dcm_WriteMemory has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_WriteMemory." */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"


#define DCM_START_SEC_CODE
#include "MemMap.h"

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
/*******************************************************************************
** Function Name        : Dcm_IsAddrLenFormatIdSupported                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the address and length format identifier   **
**                        from the request message is valid or not            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : AddressLenFormatId                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04120 */
#if (0 < DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG)
FUNC(boolean, DCM_CODE) Dcm_IsAddrLenFormatIdSupported(
  uint8 AddressLenFormatId)
{
  /* @Trace: Dcm_SUD_API_31157 */
  boolean ChkVal = DCM_FALSE;

  for (uint8 idx = 0; idx < DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG; idx++)
  {
    if (AddressLenFormatId == Dcm_GaaAddressAndLengthFormatIds[idx])
    {
      /* @Trace: Dcm_SUD_API_31156 */
      ChkVal = DCM_TRUE;
      break;
    }
  }

  return ChkVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ReadMemoryAddressFromReqData                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the memory address from request message         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pReqData, MemAddrBytes                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_ReadMemoryAddressFromReqData(
  Dcm_Uint8ConstPtrType pReqData
  , uint8 MemAddrBytes)
{
  /* @Trace: Dcm_SUD_API_31176 */
  uint32 MemoryAddress = 0;

  for (uint8 idx = 0; idx < MemAddrBytes; idx++)
  {
    MemoryAddress <<= 8;
    MemoryAddress |= pReqData[idx];
  }

  return MemoryAddress;
}

/*******************************************************************************
** Function Name        : Dcm_ReadMemorySizeFromReqData                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the memory size from request message            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pReqData, MemSizeBytes                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_ReadMemorySizeFromReqData(
  Dcm_Uint8ConstPtrType pReqData
  , uint8 MemSizeBytes)
{
  /* @Trace: Dcm_SUD_API_31180 */
  uint32 MemorySize = 0;

  for (uint8 idx = 0; idx < MemSizeBytes; idx++)
  {
    MemorySize <<= 8;
    MemorySize |= pReqData[idx];
  }

  return MemorySize;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsReqReadDataLenValid                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the read data length is valid or not       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ReqDataLen, MemAddrBytes, MemSizeBytes              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_IsReqReadDataLenValid(
  uint32 ReqDataLen
  , uint32 MemAddrBytes
  , uint32 MemSizeBytes)
{
  /* @Trace: Dcm_SUD_API_31165 */
  boolean ChkVal = DCM_FALSE;
  uint32 ValidReqDataLen = (MemAddrBytes + MemSizeBytes + 1);

  if (ReqDataLen == ValidReqDataLen)
  {
    /* @Trace: Dcm_SUD_API_31166 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}
#endif

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
/*******************************************************************************
** Function Name        : Dcm_IsReadMemoryRangeValid                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the read memory range is valid or not      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : MemoryAddress, MemorySize                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pFoundMemRngIndex                                   **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01158 will be implemented in generator */
FUNC(boolean, DCM_CODE) Dcm_IsReadMemoryRangeValid(
  uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_Uint8PtrType pFoundMemRngIndex)
{
  /* @Trace: Dcm_SUD_API_31159 */
  boolean ChkVal = DCM_FALSE;

  if ((0 != MemoryAddress) && (0 != MemorySize))
  {
    /* @Trace: Dcm_SUD_API_31160 */
    uint32 HighAddress = ((MemoryAddress + MemorySize) - 1);
    uint32 LowAddress = MemoryAddress;
    Dcm_ReadMemRngInfoConfigConstPtrType pReadMemRngInfoCfg;

    for (uint8 idx = 0; idx < DCM_TOTAL_NUM_READ_MEMORY_CONFIGURED; idx++)
    {
      /* @Trace: Dcm_SUD_API_31161 */
      pReadMemRngInfoCfg = &Dcm_GaaReadMemRngConfig[idx];
      if ((pReadMemRngInfoCfg->ulReadMemRngLow <= LowAddress)
          && (HighAddress <= pReadMemRngInfoCfg->ulReadMemRngHigh))
      {
        /* @Trace: Dcm_SUD_API_31162 */
        ChkVal = DCM_TRUE;
        *pFoundMemRngIndex = idx;
        break;
      }
    }
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetMemoryIdByRange                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the memory identifier for source memory         **
**                        by the range                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ulMemoryAddr, ulMemorySize                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_GetMemoryIdByRange(
  uint32 ulMemoryAddr,
  uint32 ulMemorySize)
{
  /* @Trace: Dcm_SUD_API_31151 */
  uint8 LucMemoryId = DCM_ZERO;
  uint8 LucRangeIndex = DCM_ZERO;

  boolean LblResult;
  Dcm_ReadMemRngInfoConfigConstPtrType LpReadMemRange = NULL_PTR;

  LblResult = Dcm_IsReadMemoryRangeValid(
    ulMemoryAddr, ulMemorySize, &LucRangeIndex);

  if (DCM_TRUE == LblResult)
  {
    /* @Trace: Dcm_SUD_API_31152 */
    LpReadMemRange = &Dcm_GaaReadMemRngConfig[LucRangeIndex];

    /* @Trace: Dcm_SUD_API_31153 */
    /* because when blUseMemoryValue = FALSE, ucReadMemoryIdentifier will be zero due to generator*/
    LucMemoryId = LpReadMemRange->ucReadMemoryIdentifier;

  }

  return LucMemoryId;
}

#endif

#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
/*******************************************************************************
** Function Name        : Dcm_IsReqWriteDataLenValid                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the write memory length is valid or not    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ReqDataLen, MemAddrBytes, MemSizeBytes, MemSize     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsReqWriteDataLenValid(
  uint32 ReqDataLen
  , uint32 MemAddrBytes
  , uint32 MemSizeBytes
  , uint32 MemSize)
{
  /* @Trace: Dcm_SUD_API_31168 */
  boolean ChkVal = DCM_FALSE;
  uint32 ValidReqDataLen = (MemAddrBytes + MemSizeBytes + MemSize + 1);

  if (ReqDataLen == ValidReqDataLen)
  {
    /* @Trace: Dcm_SUD_API_31169 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsWriteMemoryRangeValid                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the write memory range is valid or not     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : MemoryAddress, MemorySize                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pFoundMemRngIndex                                   **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01056 will be implemented in generator */
static FUNC(boolean, DCM_CODE) Dcm_IsWriteMemoryRangeValid(
  uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_Uint8PtrType pFoundMemRngIndex)
{
  /* @Trace: Dcm_SUD_API_31171 */
  boolean ChkVal = DCM_FALSE;
  uint32 HighAddress = (MemoryAddress + MemorySize - 1);
  uint32 LowAddress = MemoryAddress;
  Dcm_WriteMemRngInfoConfigConstPtrType pWriteMemRngInfoCfg;

  /* @Trace : ISO-14229-1 11.8.4 */
  if (MemorySize == DCM_ZERO)
  {
    return ChkVal;
  }

  for (uint8 idx = 0; idx < DCM_TOTAL_NUM_WRITE_MEMORY_CONFIGURED; idx++)
  {
    /* @Trace: Dcm_SUD_API_31172 */
    pWriteMemRngInfoCfg = &Dcm_GaaWriteMemRngConfig[idx];
    if ((pWriteMemRngInfoCfg->ulWriteMemRngLow <= LowAddress)
        && (HighAddress <= pWriteMemRngInfoCfg->ulWriteMemRngHigh))
    {
      /* @Trace: Dcm_SUD_API_31174 */
      ChkVal = DCM_TRUE;
      *pFoundMemRngIndex = idx;
      break;
    }
  }

  return ChkVal;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: OVFL : Not a defect : No Action Planned > Overflow can not occur */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
