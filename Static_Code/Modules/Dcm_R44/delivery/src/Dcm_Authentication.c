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
**  SRC-MODULE: Dcm_Authentication.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains interfaces for service Authentication      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision     Date            By           Description                      **
********************************************************************************
** 0.0.1        15-Jun-2020     LanhLT       Initial Version                  **
** 0.0.2        16-Aug-2020     LanhLT       Changes made as per #14836       **
** 0.0.3        13-Oct-2020     LanhLT       Changes made as per #15766       **
** 0.0.4        02-Nov-2020     LanhLT       Changes made as per #16832       **
** 0.0.5        04-Dec-2020     LanhLT       Polyspace fixing as per #15175   **
** 0.0.6        14-Dec-2020     HueKM        Fix inclusion KeyM as per #17446 **
** 0.0.7        16-Dec-2020     HueKM        Mapping SUD API ID as per #17448 **
** 1.0.9        31-Mar-2023     LanhLT       Refer #CP44-1739                 **
** 1.1.0        12-Oct-2023   SY Kim         Refer #CP44-2768, #CP44-2676     **
** 1.2.0        06-Nov-2023   SY Kim         Refer #CP44-3194                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "Dcm_Authentication.h"
#include "Dcm_PCTypes.h"
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Utils.h"
#include "Dcm_Validate.h"
#include "Dcm_Timer.h"

#if (DCM_AUTHENTICATION_SERVICE == STD_ON) 

#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
#include "KeyM.h"
#elif (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
#include "Dcm_Callout_SecureService.h"
#else
/* nothing */
#endif /* DCM_STANDARD_SUPPORT */

#endif /* (DCM_AUTHENTICATION_SERVICE == STD_ON) in Include */

#include "Dcm_KeyM.h"
#include "Dcm_Csm.h"
#include "Dcm_Externals.h"


/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)

#define AUTHENTICATION_STATE_READOUT_TIME (3 * DCM_TASK_TIME)
#define AUTHENTICATION_STATE_WRITEOUT_TIME (3 * DCM_TASK_TIME)

#define GENERAL_NRC (Dcm_AuthenticationConfig.GeneralNrc)
#define NVM_BLOCK_ID (Dcm_AuthenticationConfig.PersistStateNvMBlockId)
#define RAM_DATA_BLOCK (Dcm_GaaAuthenticationElementData)

#define AUTHENTICATION_CONNECTION_ID_NOT_CONFIGURED (0xFF)

#define UDS_SERVICE_ID_RANGE_LOW (0x10)
#define UDS_SERVICE_ID_AUTHENTICATION (0x29)

#define SUPPORT_COMUNICATION_CONFIGURATION (0x00)
#define AUTHENTICATION_DATA_MIN_LENGTH (0x0000)

/*AuthenticationReturnParameter*/
#define REQUEST_ACCEPTED (0x00)
#define GENERAL_REJECT (0x01)
#define AUTHENTICATION_CONFIGURATION_APCE (0x02)
#define AUTHENTICATION_CONFIGURATION_ARC_ASYM_CRYPTOGRAPHY (0x03)
#define AUTHENTICATION_CONFIGURATION_ARC_SYM_CRYPTOGRAPHY (0x04)
#define DE_AUTHENTICATION_SUCCESSFUL (0x10)
#define CERTIFICATE_VERIFIED_OWNERSHIP_VERIFICATION_NECESSERY (0x11)
#define OWNERSHIPVERIFIED_AUTHENTICATIONCOMPLETE  (0x12)
#define CERTIFICATE_VERIFIED (0x13)


#define DEFAULT_ASYNC_JOBID (0xFFFF)

enum {
  DE_AUTHENTICATE
  , VERIFY_CERTIFICATE_UNIDIRECTIONAL
  , VERIFY_CERTIFICATE_BIDIRECTIONAL
  , PROOF_OF_OWNERSHIP
  , TRANSMIT_CERTIFICATE
  , REQUEST_CHALLENGE_FOR_AUTHENTICATION
  , VERIFY_PROOF_OF_OWNERSHIP_UNIDIRECTIONAL
  , VERIFY_PROOF_OF_OWNERSHIP_BIDIRECTIONAL
  , AUTHENTICATION_CONFIGURATION
  , SUBFUNCTION_MAX_NUM
};

typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_AuthProcessingFuncType) (
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(Dcm_AuthenticationConnectionESInfoType, DCM_VAR) Dcm_GaaAuthenConnectionESInfo
  [DCM_AUTHENTICATION_CONNECTION_ES_NUM];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* SWS_Dcm_01477 SWS_Dcm_01479 */
VAR(Dcm_AuthenticationConnectionInfoType, DCM_VAR) Dcm_GaaAuthenConnectionInfo
  [DCM_AUTHENTICATION_CONNECTION_NUM];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* DCM_STANDARD_SUPPORT */
#endif /* (DCM_AUTHENTICATION_SERVICE == STD_ON) in Types*/

/*******************************************************************************
**                      Static Functions Declaration                          **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(Dcm_DiagnosticServiceFunType, DCM_CODE) Dcm_GetAuthenServiceFunPtr(
  Dcm_SubServiceIdConfigConstPtrType pSubServiceCfg);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessDeAuthenticate(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessAuthenticationConfiguration(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessNotSupport(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(boolean, DCM_CODE) Dcm_IsServiceBypassAuthenticationCheck(
  Dcm_ServiceIdConfigConstPtrType pServiceCfg);

static FUNC(boolean, DCM_CODE) Dcm_VerifyAuthenticationRole(
  Dcm_AuthenticationRoleType AssignedRole
  , Dcm_AuthenticationRoleType ProvidedRole);

static FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLServices(void);

static FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLSubServices(void);

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_AuthenticationESPendingProcessing(  
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)

#if (DCM_AUTHENTICATION_GENERAL_NRC_MODE_RULE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_CheckGeneralNrcModeRule(
  Dcm_NrcPtrType pErrorCode);
#endif /*(DCM_AUTHENTICATION_GENERAL_NRC_MODE_RULE == STD_ON)*/

#if (DCM_AUTHENTICATION_TARGET_ID_MODE_RULE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_CheckTargetIdModeRule(
  Dcm_NrcPtrType pErrorCode);
#endif /*(DCM_AUTHENTICATION_TARGET_ID_MODE_RULE == STD_ON)*/

static FUNC(void, DCM_CODE) Dcm_ResetAuthenticationElement(
  Dcm_AuthenticationElementPtrType pAuthEle);

static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementRole(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg);

static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLServices(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg);

static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLDid(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg);

static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLMemorySelection(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg);

static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLRid(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg);

static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWhiteList(
  KeyM_CertificateIdType CertId
  , Dcm_AuthenticationElementPtrType pAuthEle
  , uint32 WLMaxSize);
#endif /* DCM_STANDARD_SUPPORT */

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessVerifyCertificateUnidirectional(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(boolean, DCM_CODE) Dcm_ChkCommunicationConfiguration(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(boolean, DCM_CODE) Dcm_ChkLengthOfUnidirectional(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_CanncelProofOfOwnerShipClientProcessing(void);

static FUNC(void, DCM_CODE) Dcm_CanncelUniDirectionalProcessing(void);

#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_StoreCertificate(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_UniDirectionalInitial(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(boolean, DCM_CODE) Dcm_VerifyCertificate(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CreatingServerChallenge(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(void, DCM_CODE) Dcm_VerifyCertificateUnidirectionalSuccessfully(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkCsm_SignatureVerify(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(void, DCM_CODE) Dcm_CanncelAsyncFuntionCall(void);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyProofofOwnerShipClient(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

#endif /* DCM_STANDARD_SUPPORT */

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessProofofOwnershipClient(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkProofofOwnerShipClientLength(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_OwnerShipVerificationSuccess(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)

static FUNC(Dcm_AuthenticationProcessingStateType, DCM_CODE)
  Dcm_GetAuthProcessingState(void);

static FUNC(void, DCM_CODE) Dcm_SetAuthProcessingState(
  Dcm_AuthenticationProcessingStateType state);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_UniDirectionalResponse(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthentationNegativeResponse(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationAsynWaitingCallBack(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyCertificateInitial(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessVerifyCertificateBidirectional(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_BiDirectionalInitial(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(boolean, DCM_CODE) Dcm_ChkLengthOfBidirectional(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CreatingServerChallengeDone(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_SigningChallengeClient(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProvidingServerCertificate(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_BiDirectionalResponse(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(void, DCM_CODE) Dcm_VerifyCertificateBidirectionalSuccessfully(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyTargetIdentification(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode);

static FUNC(void, DCM_CODE) Dcm_ResetAuthProcessingState(
Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo);

static FUNC(uint32, DCM_CODE) Dcm_AuthenticationGetAsyncJobId(
  Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo);

static FUNC(void, DCM_CODE) Dcm_AuthenticationSetAsyncJobId(
  uint32 JobId
  , Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo);

#if ((DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON) \
     || (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON))
static FUNC(boolean, DCM_CODE) Dcm_ExtendValidateAccessRightsWithWhiteList(
  Dcm_Uint8ConstPtrType pData
  , uint32 DataLen
  , Dcm_AuthenticationElementPtrType pAuthEle);
#endif /* WHITE LIST */
#endif /* DCM_STANDARD_SUPPORT */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) Dcm_AuthenticationReProcessing(void);

static FUNC(uint16, DCM_CODE) Dcm_AuthenticationGet2ByteData(
  uint8 HighByte
  , uint8 LowByte);

static FUNC(uint8, DCM_CODE) Dcm_GetFirstByteFrom4ByteData(uint32 buffer);

static FUNC(uint8, DCM_CODE) Dcm_GetSecondByteFrom4ByteData(uint32 buffer);

#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
static CONST(Dcm_AuthProcessingFuncType, DCM_CONST) AuthDispatchTable[
  AUTHENTICAITON_PROCESSING_MAX_STATE] =
{
  Dcm_VerifyCertificateInitial // KeyM_SetCertificate
  , Dcm_VerifyCertificate // KeyM_VerifyCertificate
  , Dcm_AuthenticationAsynWaitingCallBack
  , Dcm_VerifyTargetIdentification
  , Dcm_CreatingServerChallenge //Csm_RandomGenerate
  , Dcm_AuthenticationAsynWaitingCallBack
  , Dcm_CreatingServerChallengeDone
  , Dcm_UniDirectionalResponse

  , Dcm_SigningChallengeClient
  , Dcm_AuthenticationAsynWaitingCallBack
  , Dcm_ProvidingServerCertificate
  , Dcm_BiDirectionalResponse

  , Dcm_ChkProofofOwnerShipClientLength
  , Dcm_VerifyProofofOwnerShipClient
  , Dcm_AuthenticationAsynWaitingCallBack
  , Dcm_ChkCsm_SignatureVerify
  , Dcm_OwnerShipVerificationSuccess
  , Dcm_AuthentationNegativeResponse
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* DCM_STANDARD_SUPPORT */

#endif /*(DCM_AUTHENTICATION_SERVICE == STD_ON) in Static Functions*/
/*******************************************************************************
**                              Function definition                           **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_InitAuthentication                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for UDS Authentication Service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON) /*Precompile option for Authentication*/
FUNC(void, DCM_CODE) Dcm_InitAuthentication(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_20000 */
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  for (uint8 idx = 0; idx < DCM_AUTHENTICATION_CONNECTION_ES_NUM; idx++)
  {
    Dcm_GaaAuthenConnectionESInfo[idx].State = DCM_DEAUTHENTICATED;
    Dcm_GaaAuthenConnectionESInfo[idx].ESProcessingState = DCM_AUTHENTICATION_IDLE;
    Dcm_MemCopy(Dcm_GaaAuthenConnectionESInfo[idx].Role, 
      Dcm_AuthenticationConfig.DeauthenticatedRole, DCM_AUTHENTICATION_ROLE_SIZE);
  }
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  for (uint8 idx = 0; idx < DCM_AUTHENTICATION_CONNECTION_NUM; idx++)
  {
    /* @Trace: SWS_Dcm_01480 SWS_Dcm_01489 */
    Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo;
    pAuthConInfo = &Dcm_GaaAuthenConnectionInfo[idx];
    pAuthConInfo->State = DCM_DEAUTHENTICATED;

    Dcm_MemCopy(pAuthConInfo->Role, 
      Dcm_AuthenticationConfig.DeauthenticatedRole, DCM_AUTHENTICATION_ROLE_SIZE);

    Dcm_ResetAuthProcessingState(pAuthConInfo);
  }
  #endif

  Dcm_InitTimers(pConfig);

}
/*******************************************************************************
** Function Name        : Dcm_StartRestorePersistedAuthenticationState        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Start Restore Persisted Authentication State        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04077 SRS_Diag_04171 */
#if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
FUNC(void, DCM_CODE) Dcm_StartRestorePersistedAuthenticationState(void)
{
  /* @Trace: Dcm_SUD_API_20005 */
  uint8 ModeRuleIndex = Dcm_AuthenticationConfig.PersistStateModeRuleIndex;
  if (DCM_POS_RESP ==  Dcm_CheckModeRule(DCM_TRUE, ModeRuleIndex))
  {
    /* @Trace: Dcm_SUD_API_20004 */
    Std_ReturnType RetVal = NvM_ReadBlock(NVM_BLOCK_ID, RAM_DATA_BLOCK);
    if (E_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20006 */
      Dcm_StartTimerExt(
        DCM_PERSIST_AUTHENTICATION_STATE_TIMER
        , AUTHENTICATION_STATE_READOUT_TIME
        , Dcm_WaitRestorePersistedAuthenticationState
        , Dcm_CancelRestorePersistedAuthenticationState);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_WaitRestorePersistedAuthenticationState         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Wait Restore Persisted Authentication State         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_WaitRestorePersistedAuthenticationState(void)
{
  NvM_RequestResultType ReqResult;

  /* @Trace: Dcm_SUD_API_20008 */
  Std_ReturnType RetVal = NvM_GetErrorStatus(NVM_BLOCK_ID, &ReqResult);

  /* @Trace: SWS_Dcm_01187 SWS_Dcm_01188 */
  if ((E_OK == RetVal) && (NVM_REQ_OK == ReqResult))
  {
    /* @Trace: Dcm_SUD_API_20010 */
    Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo;
    Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;

    for (uint8 idx = 0; idx < DCM_AUTHENTICATION_CONNECTION_NUM; idx++)
    {
      /* @Trace: Dcm_SUD_API_20011 */
      pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[idx];
      Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pRole;

      if (0 == *(pAuthEle->pDataLen))
      {
        /* @Trace: Dcm_SUD_API_20012 */
        continue;
      }

      pAuthConInfo = &Dcm_GaaAuthenConnectionInfo[idx];
      pAuthConInfo->State = DCM_AUTHENTICATED;

      Dcm_MemCopy(pAuthConInfo->Role, 
        pAuthEle->pData, DCM_AUTHENTICATION_ROLE_SIZE);
    }

    Dcm_StopTimer(DCM_PERSIST_AUTHENTICATION_STATE_TIMER);
  }
}

/*******************************************************************************
** Function Name        : Dcm_CancelRestorePersistedAuthenticationState       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel Restore Persisted Authentication State       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CancelRestorePersistedAuthenticationState(void)
{
  /* @Trace: Dcm_SUD_API_20015 */
  NvM_CancelJobs(NVM_BLOCK_ID);
}

/*******************************************************************************
** Function Name        : Dcm_StartPersistAuthenticationState                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Start Persist Authentication State                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04077 */
FUNC(void, DCM_CODE) Dcm_StartPersistAuthenticationState(void)
{
  uint8 ModeRuleIndex = Dcm_AuthenticationConfig.PersistStateModeRuleIndex;

  if (DCM_POS_RESP == Dcm_CheckModeRule(DCM_TRUE, ModeRuleIndex))
  {
    /* @Trace: Dcm_SUD_API_20019 */
    NvM_SetBlockLockStatus(NVM_BLOCK_ID, DCM_FALSE);
    Std_ReturnType RetVal = NvM_WriteBlock(NVM_BLOCK_ID, RAM_DATA_BLOCK);

    if (E_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20021 */
      Dcm_StartTimerExt(
        DCM_PERSIST_AUTHENTICATION_STATE_TIMER
        , AUTHENTICATION_STATE_WRITEOUT_TIME
        , Dcm_WaitPersistAuthenticationState
        , Dcm_CancelPersistAuthenticationState);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_WaitPersistAuthenticationState                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Wait Persist Authentication State                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_WaitPersistAuthenticationState(void)
{
  NvM_RequestResultType ReqResult;
  Std_ReturnType RetVal = NvM_GetErrorStatus(NVM_BLOCK_ID, &ReqResult);

  /* @Trace: SWS_Dcm_01189 */
  /* @Trace: Dcm_SUD_API_20023 */
  if ((E_OK == RetVal) && (NVM_REQ_OK == ReqResult))
  {
    /* @Trace: Dcm_SUD_API_20025 */
    NvM_SetBlockLockStatus(NVM_BLOCK_ID, DCM_TRUE);
    Dcm_StopTimer(DCM_PERSIST_AUTHENTICATION_STATE_TIMER);
  }
}

/*******************************************************************************
** Function Name        : Dcm_CancelPersistAuthenticationState                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel Persist Authentication State                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CancelPersistAuthenticationState(void)
{
  /* @Trace: Dcm_SUD_API_20027 */
  NvM_CancelJobs(NVM_BLOCK_ID);
  NvM_SetBlockLockStatus(NVM_BLOCK_ID, DCM_TRUE);
}
#endif /* DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE */
/*******************************************************************************
** Function Name        : Dcm_TriggerTimerFallbackToDeauthenticatedState      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Trigger Timer Fallback To Deauthenticated State     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04171 */
FUNC(boolean, DCM_CODE) Dcm_TriggerTimerFallbackToDeauthenticatedState(void)
{
  boolean RetVal = DCM_FALSE;

  #if (0 < DCM_AUTHENTICATION_DEFAULT_SESSION_TIMEOUT)
  if (DCM_TRUE == Dcm_IsNonDefaultSession())
  {
    /* @Trace: Dcm_SUD_API_20030 */
    Dcm_StopTimer(DCM_AUTHENTICATION_DEFAULT_SESSION_TIMER);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20032 */
    Dcm_StartTimerExt(
      DCM_AUTHENTICATION_DEFAULT_SESSION_TIMER
      , DCM_AUTHENTICATION_DEFAULT_SESSION_TIMEOUT
      , NULL_PTR
      , Dcm_FallbackToDeauthenticatedState);

    RetVal = DCM_TRUE;
  }
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_FallbackToDeauthenticatedState                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fallback To Deauthenticated State                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_FallbackToDeauthenticatedState(void)
{
  /* @Trace: Dcm_SUD_API_20033 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->usMainConnectionId;

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    /* @Trace: Dcm_SUD_API_20036 */
    (void)Dcm_ResetToDeauthenticatedState(ConnectionId);
  }
}

/*******************************************************************************
** Function Name        : Dcm_ValidateServiceAccessRights                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Service Access Rights                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pServiceCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01537 SWS_Dcm_01540 SWS_Dcm_01541 SWS_Dcm_01542 SWS_Dcm_01524 */
FUNC(boolean, DCM_CODE) Dcm_ValidateServiceAccessRights(
  Dcm_ServiceIdConfigConstPtrType pServiceCfg)
{
  boolean ChkVal = DCM_TRUE;

  /* @Trace: Dcm_SUD_API_20038 */
  if ((DCM_FALSE == Dcm_IsServiceBypassAuthenticationCheck(pServiceCfg))
      && (DCM_FALSE == pServiceCfg->blSubFunctionAvailable))
  {
    /* @Trace: Dcm_SUD_API_20040 */
    Dcm_AuthenticationRoleType AssignedRole;

    Dcm_MemCopy(AssignedRole, 
      pServiceCfg->ServiceRole, DCM_AUTHENTICATION_ROLE_SIZE);

    ChkVal = Dcm_ValidateAccessRights(AssignedRole);

    CHK_RET_VAL(DCM_FALSE == ChkVal, ChkVal, \
      Dcm_ValidateAccessRightsWithWLServices());
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateSubServiceAccessRights                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Sub Service Access Rights                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pServiceCfg, pSubServiceCfg                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ValidateSubServiceAccessRights(
  Dcm_ServiceIdConfigConstPtrType pServiceCfg
  , Dcm_SubServiceIdConfigConstPtrType pSubServiceCfg)
{
  boolean ChkVal = DCM_TRUE;

  /* @Trace: Dcm_SUD_API_50900 */
  if (DCM_FALSE == Dcm_IsServiceBypassAuthenticationCheck(pServiceCfg))
  {
    /* @Trace: Dcm_SUD_API_20043 */
    Dcm_AuthenticationRoleType AssignedRole;
    Dcm_MemCopy(AssignedRole, 
      pServiceCfg->ServiceRole, DCM_AUTHENTICATION_ROLE_SIZE);

    ChkVal = Dcm_ValidateAccessRights(AssignedRole);

    if (DCM_FALSE == ChkVal)
    {
      /* @Trace: Dcm_SUD_API_20044 */
      Dcm_MemCopy(AssignedRole, 
        pSubServiceCfg->SubServiceRole, DCM_AUTHENTICATION_ROLE_SIZE);

      ChkVal = Dcm_ValidateAccessRights(AssignedRole);
    }

    CHK_RET_VAL(DCM_FALSE == ChkVal, ChkVal, \
      Dcm_ValidateAccessRightsWithWLSubServices());
  }
  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsValidCertificateElementCondition              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Is Valid Certificate Element Condition              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pModeCondCfg                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01119 */
#if (DCM_MODE_CONDITION == STD_ON)
FUNC(boolean, DCM_CODE) Dcm_IsValidCertificateElementCondition(
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg)
{
  boolean ChkVal = DCM_FALSE;

  /* @Trace: Dcm_SUD_API_20046 */
  #if (DCM_AUTHENTICATION_TARGET_ID_MODE_RULE == STD_ON)
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

  uint16 ConnectionId = pPduIdTable->RxConnectionId;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if ((AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
      && (NULL_PTR != pModeCondCfg))
  {
    /* @Trace: Dcm_SUD_API_20049 */
    Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];

    KeyM_CertificateIdType CertId = pAuthConCfg->CertId;
    KeyM_CertElementIdType CertEleId = pAuthConCfg->CompareCertId;
    uint8 CertEleData[DCM_AUTHENTICATION_CERT_COMPARE_ELEMENT_MAX_LEN];
    uint32 CertEleDataLen = DCM_AUTHENTICATION_CERT_COMPARE_ELEMENT_MAX_LEN;

    Std_ReturnType Res = KeyM_CertElementGet(
      CertId, CertEleId, CertEleData, &CertEleDataLen);

    Dcm_ConditionType Condition = pModeCondCfg->ConditionType;
    if ((E_OK == Res)
        && (pAuthConCfg->CompareDataLen == CertEleDataLen))
    {
      /* @Trace: Dcm_SUD_API_20051 */
      ChkVal =  Dcm_MemCompare(pAuthConCfg->pCompareData, 
          CertEleData, CertEleDataLen, Condition);
    }
  }
  #else
  DCM_UNUSED(pModeCondCfg);
  #endif

  return ChkVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_SetDeauthenticatedRole                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sets a new role used in deauthenticated state       **
**                        for that connection. The set role is valid until    **
**                        the connection switches into authenticated state    **
**                        or the ECU is reset.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId, DeauthenticatedRole                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_91069 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetDeauthenticatedRole(
  uint16 ConnectionId
  , Dcm_AuthenticationRoleType DeauthenticatedRole)
{
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    Dcm_AuthenticationConnectionESInfoType AuthConESInfo;
    boolean ChkVal = Dcm_GetAuthenticationConnectionESInfo(
      ConnectionId, &AuthConESInfo);

    if ((DCM_TRUE == ChkVal)
        && (DCM_DEAUTHENTICATED == AuthConESInfo.State))
    {
      Dcm_MemCopy(AuthConESInfo.Role, 
        DeauthenticatedRole, DCM_AUTHENTICATION_ROLE_SIZE);

      (void)Dcm_SetAuthenticationConnectionESInfo(ConnectionId, &AuthConESInfo);
    }
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  /* @Trace: Dcm_SUD_API_20053 */
  Dcm_AuthenticationConnectionInfoType AuthConInfo;
  boolean ChkVal = Dcm_GetAuthenticationConnectionInfo(
    ConnectionId, &AuthConInfo);

  /* @Trace: SWS_Dcm_01486 SWS_Dcm_01487 SWS_Dcm_01488 */
  if ((DCM_TRUE == Dcm_ChkInit(DCM_SET_DEAUTHENTICATED_ROLE))
      && (DCM_TRUE == ChkVal)
      && (DCM_DEAUTHENTICATED == AuthConInfo.State))
  {
    /* @Trace: Dcm_SUD_API_20052 */
    Dcm_MemCopy(AuthConInfo.Role, 
      DeauthenticatedRole, DCM_AUTHENTICATION_ROLE_SIZE);

    (void)Dcm_SetAuthenticationConnectionInfo(ConnectionId, &AuthConInfo);
  }
  #endif

  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_DcmAuthentication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process UDS 0x29 service           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04230 SRS_Diag_04238 SRS_Diag_04240 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmAuthentication(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType RetVal = E_OK;

  Dcm_SubServiceIdConfigConstPtrType pSubServiceCfg;
  pSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if (NULL_PTR == pSubServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_20054 */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic sub-service processing */
  else if (NULL_PTR != pSubServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_20056 */
    RetVal = pSubServiceCfg->pSubServiceFnc(OpStatus, pMsgContext, pErrorCode);
  }
  /* Internal diagnostic sub-service processing */
  else
  {
    /* @Trace: Dcm_SUD_API_20057 */
    Dcm_DiagnosticServiceFunType pAuthenServiceFun;
    pAuthenServiceFun = Dcm_GetAuthenServiceFunPtr(pSubServiceCfg);

    RetVal = pAuthenServiceFun(OpStatus, pMsgContext, pErrorCode);

    /* this function added for User callout  */
    if ((DCM_POS_RESP != Dcm_GddNegRespError) && (RetVal != E_OK))
    {
      Dcm_Authentication_User_CallOut(OpStatus, pMsgContext, &Dcm_GddNegRespError);
    }

  }

  return RetVal;
}
/*******************************************************************************
** Function Name        : Dcm_ValidateAccessRights                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Access Rights                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : AssignedRole                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04233 */
FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRights(
  Dcm_AuthenticationRoleType AssignedRole)
{
  boolean RetVal = DCM_FALSE;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->usMainConnectionId;

  /* @Trace: SWS_Dcm_01538 */
  /* @Trace: Dcm_SUD_API_20059 */
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    Dcm_AuthenticationConnectionESInfoType AuthConInfo;
    boolean ChkVal = Dcm_GetAuthenticationConnectionESInfo(
    ConnectionId, &AuthConInfo);
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    Dcm_AuthenticationConnectionInfoType AuthConInfo;
    boolean ChkVal = Dcm_GetAuthenticationConnectionInfo(
    ConnectionId, &AuthConInfo);
  #endif

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_20058 */
    RetVal = Dcm_VerifyAuthenticationRole(AssignedRole, AuthConInfo.Role);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetAuthenServiceFunPtr                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the process function according sub service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pSubServiceCfg                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_DiagnosticServiceFunType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01559 SWS_Dcm_01551 */
static FUNC(Dcm_DiagnosticServiceFunType, DCM_CODE) Dcm_GetAuthenServiceFunPtr(
  Dcm_SubServiceIdConfigConstPtrType pSubServiceCfg)
{
  uint8 Id = pSubServiceCfg->ucSubServiceId;

  Dcm_DiagnosticServiceFunType DispatchTable[SUBFUNCTION_MAX_NUM] =
  {
    /* 0x00 */ Dcm_ProcessDeAuthenticate
    /* 0x01 */ , Dcm_ProcessVerifyCertificateUnidirectional
	#if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
    /* 0x02 */ , Dcm_ProcessVerifyCertificateBidirectional
	#else
	/* 0x02 */ , Dcm_ProcessNotSupport
    #endif
    /* 0x03 */ , Dcm_ProcessProofofOwnershipClient
    /* 0x04 */ , Dcm_ProcessNotSupport
    /* 0x05 */ , Dcm_ProcessNotSupport
    /* 0x06 */ , Dcm_ProcessNotSupport
    /* 0x07 */ , Dcm_ProcessNotSupport
    /* 0x08 */ , Dcm_ProcessAuthenticationConfiguration
  };

  /* @Trace: Dcm_SUD_API_20067 Dcm_SUD_API_20068 */
  Dcm_DiagnosticServiceFunType pServiceFun = (Id < SUBFUNCTION_MAX_NUM) ?
    DispatchTable[Id] : Dcm_ProcessNotSupport;

  return pServiceFun;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessDeAuthenticate                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for sub function              **
**                        deAuthenticate                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04239 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessDeAuthenticate(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType RetVal = E_OK;

  if (1 != pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_20069 */
    Dcm_InternalSetNegResponse(pMsgContext, 
      DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);

    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  else
  {
    /* @Trace: SWS_Dcm_01561 */
    /* @Trace: Dcm_SUD_API_20070 */
    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
    uint16 ConnectionId = pPduIdTable->usMainConnectionId;
    
    #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
    if((Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].ucAuthenticationUsePort == USE_ASYNCH_CLIENT_SERVER) ||
        (Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].ucAuthenticationUsePort == USE_ASYNCH_FNC))
    {
      /* @Trace: Dcm_SUD_API_22005 */
      if (NULL_PTR != Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pAsyncDeauthenticationFailedFun)
      {
        RetVal = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pAsyncDeauthenticationFailedFun
        (OpStatus, pMsgContext, &Dcm_GddNegRespError);
      }
    }
    else
    {
      /* Nothing */
    }
    #endif

    if ((DCM_POS_RESP != Dcm_GddNegRespError) && (RetVal != E_OK))
    {
      Dcm_InternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
    }
    else
    {
      if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
      {
        /* @Trace: Dcm_SUD_API_20072 */
        (void)Dcm_ResetToDeauthenticatedState(ConnectionId);
      }
	
      pMsgContext->resDataLen = 2;
      pMsgContext->resData[0] = pMsgContext->reqData[0];

      /* @Trace: SWS_Dcm_01565 */
      pMsgContext->resData[1] = DE_AUTHENTICATION_SUCCESSFUL;
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessAuthenticationConfiguration              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for sub function              **
**                        authenticationConfiguration                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01533 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessAuthenticationConfiguration(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType RetVal = E_OK;

  if (1 != pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_20073 */
    Dcm_InternalSetNegResponse(pMsgContext, 
      DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20074 */
    pMsgContext->resDataLen = 2;
    pMsgContext->resData[0] = pMsgContext->reqData[0];
    pMsgContext->resData[1] = AUTHENTICATION_CONFIGURATION_APCE;

    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessNotSupport                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function in case the sub function      **
**                        is not supported by Dcm module                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessNotSupport(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20075 */
  Std_ReturnType RetVal = E_OK;

  Dcm_InternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
  Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsServiceBypassAuthenticationCheck              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the service can be bypass                  **
**                        the authentication check or not                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pServiceCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01536 SWS_Dcm_01558 */
static FUNC(boolean, DCM_CODE) Dcm_IsServiceBypassAuthenticationCheck(
  Dcm_ServiceIdConfigConstPtrType pServiceCfg)
{
  boolean ChkVal = DCM_FALSE;
  uint8 ServiceId = pServiceCfg->ucServiceId;

  /* @Trace: Dcm_SUD_API_20077 */
  if ((ServiceId < UDS_SERVICE_ID_RANGE_LOW)
      || (UDS_SERVICE_ID_AUTHENTICATION == ServiceId)
      || (DCM_TESTERPRESENT == ServiceId))
  {
    /* @Trace: Dcm_SUD_API_20076 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateAccessRightsWithWLDid                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate access rights with white list for did      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pData, DataLen                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLDid(
  Dcm_Uint8ConstPtrType pData
  , uint32 DataLen)
{
  boolean RetVal = DCM_FALSE;

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
  uint8 AuthConIdx;
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->usMainConnectionId ;
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  uint32 LulMaxLength;
  uint32 LucIndex;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpWL;

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    /*WL DID fomat: DIDHighByte DIDLowByte AccessByte */
    AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
    LulMaxLength =  Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].ucWLDidSize;
    LpWL = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pWLDid;
    LucIndex = 0;

    while (LucIndex < LulMaxLength)
    {
      /* check 2 bytes DID */
      if (DCM_TRUE == Dcm_MemCompare(pData, LpWL, DCM_TWO, DCM_EQUALS))
      {
        /* check the access byte */
        if ((pData[DCM_TWO] & LpWL[DCM_TWO]) != 0U)
        {
          RetVal = DCM_TRUE;

          /*exit loop*/
          LucIndex = LulMaxLength;
        }
      }
      /* move to the next DID */
      LucIndex = LucIndex + 3; /* 2B DID + 1B Read/WriteID */
      LpWL = &LpWL[LucIndex];
    }
  }
  DCM_UNUSED(DataLen);
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)

  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
  Dcm_AuthenticationElementPtrType pAuthEle;

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];

    pAuthEle = pAuthConCfg->pWLDid;
    if (NULL_PTR != pAuthEle)
    {
      RetVal = Dcm_ExtendValidateAccessRightsWithWhiteList(
        pData, DataLen, pAuthEle);
    }
  }
#endif /* DCM_STANDARD_SUPPORT */
  #else
  DCM_UNUSED(pData);
  DCM_UNUSED(DataLen);
  #endif /* DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON */


  return RetVal;
}
/*******************************************************************************
** Function Name        : Dcm_ValidateAccessRightsWithWLRid                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate access rights with white list for rid      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pData, DataLen                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLRid(
  Dcm_Uint8ConstPtrType pData
  , uint32 DataLen)
{
  boolean RetVal = DCM_FALSE;

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->usMainConnectionId ;
  uint8 AuthConIdx;
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  uint32 LulMaxLength;
  uint32 LucIndex;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpWL;

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    /*WL DID fomat: RIDHighByte RIDLowByte AccessByte */
    AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
    LulMaxLength =  Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].ucWLRidSize;
    LpWL = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pWLRid;
    LucIndex = 0;

    while (LucIndex < LulMaxLength)
    {
      /* check 2 bytes RID */
      if (DCM_TRUE == Dcm_MemCompare(pData, LpWL, DCM_TWO, DCM_EQUALS))
      {
        /* check the access byte */
        if ((pData[DCM_TWO] & LpWL[DCM_TWO]) != 0U)
        {
          RetVal = DCM_TRUE;

          /*exit loop*/
          LucIndex = LulMaxLength;
        }
      }
      /* move to the next DID */
      LucIndex = LucIndex + 3;
      LpWL = &LpWL[LucIndex];
    }
  }
  DCM_UNUSED(DataLen);
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
  Dcm_AuthenticationElementPtrType pAuthEle;

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];
    pAuthEle = pAuthConCfg->pWLRid;

    if (NULL_PTR != pAuthEle)
    {
      RetVal = Dcm_ExtendValidateAccessRightsWithWhiteList(
        pData, DataLen, pAuthEle);
    }
  }
  #endif /* DCM_STANDARD_SUPPORT */
  #else
  DCM_UNUSED(pData);
  DCM_UNUSED(DataLen);
  #endif /*DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON*/

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateAccessRightsWithWLMemorySelection       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate access rights with white list              **
**                        for memory selection of read dtc service            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pData, DataLen                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLMemorySelection(
  Dcm_Uint8ConstPtrType pData)
{
  boolean RetVal = DCM_FALSE;

  /* @Trace: Dcm_SUD_API_20090 */
  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA)  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->RxConnectionId ;
  uint8 AuthConIdx;
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
  Dcm_AuthenticationElementPtrType pAuthEle;
  uint8 idx;

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];
    pAuthEle = pAuthConCfg->pWLMemorySelection;
    if (NULL_PTR != pAuthEle)
    {
        for (idx = 0; idx < DCM_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_MAX_SIZE; idx++)
        {
            /* Checks on service 0x19 parameter MemorySelection */
          if (pData[0] == pAuthEle->pData[idx])
          {
            RetVal = DCM_TRUE;
            break;
          }
        }

    }
  }
  #else
  DCM_UNUSED(pData);
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsAuthenticatedConnection                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the connection is authenticated or not     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsAuthenticatedConnection(
  uint16 ConnectionId)
{
  boolean RetVal = DCM_FALSE;
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)

  uint8 AuthenticationIdIndex;
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    if ((Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].State == DCM_AUTHENTICATED)||\
      (Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState != DCM_AUTHENTICATION_IDLE))
    {
      RetVal = DCM_TRUE;
    }
  }
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  /* @Trace: Dcm_SUD_API_20097 */
  Dcm_AuthenticationConnectionInfoType AuthConInfo;
  boolean ChkVal = Dcm_GetAuthenticationConnectionInfo(
    ConnectionId, &AuthConInfo);

  if ((DCM_TRUE == ChkVal)
      && (DCM_AUTHENTICATED == AuthConInfo.State))
  {
    /* @Trace: Dcm_SUD_API_20096 */
    RetVal = DCM_TRUE;
  }
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetAuthConnectionIndex                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the configuration index of authentication       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
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
FUNC(uint8, DCM_CODE) Dcm_GetAuthConnectionIndex(
  uint16 ConnectionId)
{
  uint8 AuthConIdx = AUTHENTICATION_CONNECTION_ID_NOT_CONFIGURED;
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  for (uint8 idx = 0; idx < DCM_AUTHENTICATION_CONNECTION_ES_NUM; idx++)
  {
    if (ConnectionId == Dcm_GaaAuthenticationConnectionESConfig[idx].usConnectionId)
    {
      AuthConIdx = idx;
      break;
    }
  }
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  for (uint8 idx = 0; idx < DCM_AUTHENTICATION_CONNECTION_NUM; idx++)
  {
    /* @Trace: Dcm_SUD_API_20098 */
    if (ConnectionId == Dcm_GaaAuthConnectionIds[idx])
    {
      /* @Trace: Dcm_SUD_API_20100 */
      AuthConIdx = idx;
      break;
    }
  }
#endif

  return AuthConIdx;
}

/*******************************************************************************
** Function Name        : Dcm_GetAuthenticationConnectionInfo                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get Authentication Connection Information           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pAuthConInfo                                        **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
FUNC(boolean, DCM_CODE) Dcm_GetAuthenticationConnectionInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo)
{
  /* @Trace: Dcm_SUD_API_20103 */
  boolean RetVal = DCM_FALSE;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20102 */
    Dcm_AuthenticationConnectionInfoPtrType pMyAuthConInfo;
    pMyAuthConInfo = &Dcm_GaaAuthenConnectionInfo[AuthConIdx];

    pAuthConInfo->State = pMyAuthConInfo->State;
    Dcm_MemCopy(pAuthConInfo->Role, 
      pMyAuthConInfo->Role, DCM_AUTHENTICATION_ROLE_SIZE);

    RetVal = DCM_TRUE;
  }

  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_SetAuthenticationConnectionInfo                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set Authentication Connection Information           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId, pAuthConInfo                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
FUNC(boolean, DCM_CODE) Dcm_SetAuthenticationConnectionInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionInfoConstPtrType pAuthConInfo)
{
  /* @Trace: Dcm_SUD_API_20105 */
  boolean RetVal = DCM_FALSE;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20104 */
    Dcm_AuthenticationConnectionInfoPtrType pMyAuthConInfo;
    pMyAuthConInfo = &Dcm_GaaAuthenConnectionInfo[AuthConIdx];

    pMyAuthConInfo->State = pAuthConInfo->State;
    Dcm_MemCopy(pMyAuthConInfo->Role, 
      pAuthConInfo->Role, DCM_AUTHENTICATION_ROLE_SIZE);

    RetVal = DCM_TRUE;
  }

  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_ResetToDeauthenticatedState                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset To Deauthenticated State                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01485 SRS_Diag_04239 */
FUNC(boolean, DCM_CODE) Dcm_ResetToDeauthenticatedState(
  uint16 ConnectionId)
{
  /* @Trace: Dcm_SUD_API_20107 */
  boolean RetVal = DCM_FALSE;
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    Dcm_GaaAuthenConnectionESInfo[AuthConIdx].State = DCM_DEAUTHENTICATED;
    Dcm_GaaAuthenConnectionESInfo[AuthConIdx].ESProcessingState = DCM_AUTHENTICATION_IDLE;
    Dcm_MemCopy(Dcm_GaaAuthenConnectionESInfo[AuthConIdx].Role, 
      Dcm_AuthenticationConfig.DeauthenticatedRole, DCM_AUTHENTICATION_ROLE_SIZE);
    (void)Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pSchMSwitchAuthenticationStateFun
      (DCM_DEAUTHENTICATED);
    RetVal = DCM_TRUE;
  }
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo;
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    pAuthConInfo = &Dcm_GaaAuthenConnectionInfo[AuthConIdx];
    pAuthConInfo->State = DCM_DEAUTHENTICATED;

    Dcm_MemCopy(pAuthConInfo->Role, 
      Dcm_AuthenticationConfig.DeauthenticatedRole, DCM_AUTHENTICATION_ROLE_SIZE);

    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];

    (void)pAuthConCfg->pSchMSwitchAuthenticationStateFun(DCM_DEAUTHENTICATED);

    Dcm_ResetAuthenticationElement(pAuthConCfg->pRole);
    Dcm_ResetAuthenticationElement(pAuthConCfg->pWLServices);

    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
    Dcm_ResetAuthenticationElement(pAuthConCfg->pWLDid);
    #endif

    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
    Dcm_ResetAuthenticationElement(pAuthConCfg->pWLMemorySelection);
    #endif

    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
    Dcm_ResetAuthenticationElement(pAuthConCfg->pWLRid);
    #endif

    /* @Trace: SWS_Dcm_01484 */
    #if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
    Dcm_StartPersistAuthenticationState();
    #endif

    Dcm_ResetAuthProcessingState(pAuthConInfo);

    RetVal = DCM_TRUE;
  }
#endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_TransitIntoAuthenticatedState                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Transit Into Authenticated State                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01528 SWS_Dcm_01531 SWS_Dcm_01532 */
FUNC(boolean, DCM_CODE) Dcm_TransitIntoAuthenticatedState(
  uint16 ConnectionId)
{
  /* @Trace: Dcm_SUD_API_20115 */
  boolean RetVal = DCM_FALSE;
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    Dcm_GaaAuthenConnectionESInfo[AuthConIdx].State = DCM_AUTHENTICATED;
    (void)Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pSchMSwitchAuthenticationStateFun
      (DCM_AUTHENTICATED);
    Dcm_MemCopy(Dcm_GaaAuthenConnectionESInfo[AuthConIdx].Role, 
      Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].AuthenticatedRole, 
      DCM_AUTHENTICATION_ROLE_SIZE);
    RetVal = DCM_TRUE;
  }
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
  Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];

    RetVal = Dcm_ReadAuthenticationElementRole(pAuthConCfg);

    /* @Trace: SWS_Dcm_01516 SWS_Dcm_01517 */
    CHK_RET_VAL(DCM_TRUE == RetVal, RetVal, \
      Dcm_ReadAuthenticationElementWLServices(pAuthConCfg));

    CHK_RET_VAL(DCM_TRUE == RetVal, RetVal, \
      Dcm_ReadAuthenticationElementWLDid(pAuthConCfg));

    CHK_RET_VAL(DCM_TRUE == RetVal, RetVal, \
      Dcm_ReadAuthenticationElementWLMemorySelection(pAuthConCfg));

    CHK_RET_VAL(DCM_TRUE == RetVal, RetVal, \
      Dcm_ReadAuthenticationElementWLRid(pAuthConCfg));

    if (DCM_TRUE == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20116 */
      pAuthConInfo = &Dcm_GaaAuthenConnectionInfo[AuthConIdx];
      pAuthConInfo->State = DCM_AUTHENTICATED;

      (void)pAuthConCfg->pSchMSwitchAuthenticationStateFun(DCM_AUTHENTICATED);

      /* @Trace: SWS_Dcm_01514 */
      Dcm_MemCopy(pAuthConInfo->Role, 
        pAuthConCfg->pRole->pData, DCM_AUTHENTICATION_ROLE_SIZE);

      /* @Trace: SWS_Dcm_01530 */
      #if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
      Dcm_StartPersistAuthenticationState();
      #endif
    }
    else
    {
      Dcm_SetAuthProcessingState(AUTHENTICATION_NEGATIVE_RESPONSE);
    }
  }
#endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_VerifyAuthenticationRole                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the authentication role is accepted or not **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : AssignedRole, ProvidedRole                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01522 SWS_Dcm_01523 */
static FUNC(boolean, DCM_CODE) Dcm_VerifyAuthenticationRole(
  Dcm_AuthenticationRoleType AssignedRole
  , Dcm_AuthenticationRoleType ProvidedRole)
{
  /* @Trace: Dcm_SUD_API_20119 */
  boolean ChkVal = DCM_FALSE;

  for (uint8 idx = 0; idx < DCM_AUTHENTICATION_ROLE_SIZE; idx++)
  {
    if (0 < (AssignedRole[idx] & ProvidedRole[idx]))
    {
      /* @Trace: Dcm_SUD_API_20120 */
      ChkVal = DCM_TRUE;
      break;
    }
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateAccessRightsWithWLServices              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Access Rights With white list for services **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01562 */
static FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLServices(void)
{
  /* @Trace: Dcm_SUD_API_20123 */
  boolean RetVal = DCM_FALSE;
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->usMainConnectionId;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
  uint8 LucChkValue = DCM_FALSE;
  uint8 RxBufferId = pPduIdTable->ucRxBufferId;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pReqData = Dcm_GaaBufferConfig[RxBufferId].pBufferArea;
  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);
  
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  uint8 wlSID;
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  Dcm_AuthenticationElementPtrType pAuthEle;
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
#endif

  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    LucChkValue = DCM_TRUE;
  }

  if (LucChkValue == DCM_TRUE)
  {
    LucChkValue = DCM_FALSE;

    /* @Trace: Dcm_SUD_API_20122 */
    if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      LucChkValue = DCM_TRUE;
    }
  }

  if (LucChkValue == DCM_TRUE)
  {
    LucChkValue = DCM_FALSE;

  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  #endif /* DCM_STANDARD_SUPPORT */
    {
      LucChkValue = DCM_TRUE;
    }
  }

  if (LucChkValue == DCM_TRUE)
  {
    #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    uint32 element_MaxLen = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].ucWLSidWithoutSubfuncSize;
    uint32 index_AuthEleData = 0;
    while (index_AuthEleData < element_MaxLen)
    {
      wlSID = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pWLSidsWithoutSubfunction[index_AuthEleData];
      if (*pReqData == wlSID)
      {
        RetVal = DCM_TRUE;
        
        // exit loop
        index_AuthEleData = element_MaxLen;
      }
      else
      {
        index_AuthEleData++;
      }
    }
    #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];
    pAuthEle = pAuthConCfg->pWLServices;

    for (uint8 idx = 0; idx < DCM_AUTHENTICATION_WHITE_LIST_SERVICES_MAX_SIZE; idx++)
    {
      /* Checks on service ID level */
      /* SRS_Diag_04234 */
      if (pReqData[0] == pAuthEle->pData[idx])
      {
        RetVal = DCM_TRUE;
        break;
      }
    }
    #endif /* DCM_STANDARD_SUPPORT */

  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ExtendValidateAccessRightsWithWhiteList         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Extend Validate Access Rights With White List       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pData, DataLen, pAuthEle                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
#if ((DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON) \
     || (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON))
static FUNC(boolean, DCM_CODE) Dcm_ExtendValidateAccessRightsWithWhiteList(
  Dcm_Uint8ConstPtrType pData
  , uint32 DataLen
  , Dcm_AuthenticationElementPtrType pAuthEle)
{
  boolean ChkVal = DCM_FALSE;
  uint32 EleDataLen = 0;
  uint32 EleDataIdx = 0;

  /* @Trace: Dcm_SUD_API_20133 */
  for (uint8 idx = 0; idx < DCM_AUTHENTICATION_WHITE_LIST_MAX_ELEMENT; idx++)
  {
    /* @Trace: Dcm_SUD_API_20132 */
    EleDataLen = pAuthEle->pDataEleLen[idx];
    if ((0 < EleDataLen) && (EleDataLen <= DataLen))
    {
      /* @Trace: Dcm_SUD_API_20134 */
      ChkVal = Dcm_MemCompare(pData,
        &pAuthEle->pData[EleDataIdx], EleDataLen-1, DCM_EQUALS);

      if (DCM_TRUE == ChkVal)
      {
        /* @Trace: Dcm_SUD_API_20136 */
        ChkVal = DCM_FALSE;

        if(((pData[EleDataLen - 1]) & \
            (pAuthEle->pData[EleDataIdx + EleDataLen - 1])) > 0)
        {
          /* @Trace: Dcm_SUD_API_20138 */
          ChkVal = DCM_TRUE;
        }
      }

      if (DCM_TRUE == ChkVal)
      {
        /* @Trace: Dcm_SUD_API_20140 */
        break;
      }

      // CHK_RET_VAL(ChkVal, idx, DCM_AUTHENTICATION_WHITE_LIST_MAX_ELEMENT);
    }

    EleDataIdx += EleDataLen;
  }

  return ChkVal;
}
#endif /*DCM_STANDARD_SUPPORT*/
#endif

/*******************************************************************************
** Function Name        : Dcm_CheckGeneralNrcModeRule                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check General Nrc Mode Rule                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01560 */
#if (DCM_AUTHENTICATION_GENERAL_NRC_MODE_RULE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_CheckGeneralNrcModeRule(
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20142 */
  
  uint8 ModeRuleIndex = Dcm_AuthenticationConfig.GeneralNrcModeRuleIndex;
  if ((DCM_POS_RESP == Dcm_CheckModeRule(DCM_TRUE, ModeRuleIndex))
      && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_20144 */
    *pErrorCode = GENERAL_NRC;
  }
}
#endif
/*******************************************************************************
** Function Name        : Dcm_CheckTargetIdModeRule                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Target Id Mode Rule                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01490 SWS_Dcm_01491 SWS_Dcm_01492 */
#if (DCM_AUTHENTICATION_TARGET_ID_MODE_RULE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_CheckTargetIdModeRule(
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_22002 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->RxConnectionId;

  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_22003 */
    Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];

    uint8 ModeRuleIndex = pAuthConCfg->TargetIdModeRuleIndex;
    if ((DCM_POS_RESP != Dcm_CheckModeRule(DCM_TRUE, ModeRuleIndex))
        && (NULL_PTR != pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_22004 */
      *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE;
    }
  }
}
#endif
/*******************************************************************************
** Function Name        : Dcm_ResetAuthenticationElement                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset Authentication Element                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pAuthEle                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_ResetAuthenticationElement(
  Dcm_AuthenticationElementPtrType pAuthEle)
{
  /* @Trace: Dcm_SUD_API_20147 */
  if (NULL_PTR != pAuthEle)
  {
    /* @Trace: Dcm_SUD_API_20146 */
    Dcm_MemClear(
      pAuthEle->pData, pAuthEle->DataMaxLen);

    Dcm_MemClear(
      (Dcm_Uint8PtrType)pAuthEle->pDataEleLen
      , DCM_AUTHENTICATION_WHITE_LIST_MAX_ELEMENT * sizeof(uint32));

    *(pAuthEle->pDataLen) = 0;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ReadAuthenticationElementRole                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Authentication Element Role                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementRole(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg)
{
  /* @Trace: Dcm_SUD_API_20149 */
  boolean RetVal = DCM_FALSE;

  if ((NULL_PTR != pAuthConCfg) && (NULL_PTR != pAuthConCfg->pRole))
  {
    /* @Trace: Dcm_SUD_API_20148 */
    KeyM_CertificateIdType CertId = pAuthConCfg->CertId;
    Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pRole;
    KeyM_CertElementIdType CertEleId = pAuthEle->Id;
    Dcm_Uint8PtrType CertEleData = pAuthEle->pData;
    uint32 CertEleDataLen = pAuthEle->DataMaxLen;

    Std_ReturnType Res = KeyM_CertElementGet(
      CertId, CertEleId, CertEleData, &CertEleDataLen);

    /* @Trace: SWS_Dcm_01515 */
    if ((E_OK == Res)
        && (DCM_AUTHENTICATION_ROLE_SIZE == CertEleDataLen))
    {
      /* @Trace: Dcm_SUD_API_20150 */
      *(pAuthEle->pDataLen) = CertEleDataLen;
      RetVal = DCM_TRUE;
    }
  }

  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_ReadAuthenticationElementWLServices             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Authentication Element white list for Services **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLServices(
    Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg)
{
  /* @Trace: Dcm_SUD_API_20153 */
  boolean RetVal = DCM_FALSE;

  if ((NULL_PTR != pAuthConCfg) && (NULL_PTR != pAuthConCfg->pWLServices))
  {
    /* @Trace: Dcm_SUD_API_20152 */
    KeyM_CertificateIdType CertId = pAuthConCfg->CertId;
    Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pWLServices;
    uint32 WLMaxSize = DCM_AUTHENTICATION_WHITE_LIST_SERVICES_MAX_SIZE;

    RetVal = Dcm_ReadAuthenticationElementWhiteList(CertId, pAuthEle, WLMaxSize);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ReadAuthenticationElementWLDid                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Authentication Element White List for Did      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLDid(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg)
{
  boolean RetVal = DCM_TRUE;

  /* @Trace: Dcm_SUD_API_20154 */
  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
  if ((NULL_PTR != pAuthConCfg) && (NULL_PTR != pAuthConCfg->pWLDid))
  {
    /* @Trace: Dcm_SUD_API_20156 */
    KeyM_CertificateIdType CertId = pAuthConCfg->CertId;
    Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pWLDid;
    uint32 WLMaxSize = DCM_AUTHENTICATION_WHITE_LIST_DID_MAX_SIZE;

    RetVal = Dcm_ReadAuthenticationElementWhiteList(CertId, pAuthEle, WLMaxSize);
  }
  #else
  DCM_UNUSED(pAuthConCfg);
  #endif

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ReadAuthenticationElementWLMemorySelection      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Authentication Element White List for          **
**                        Memory Selection of Read DTC Service                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLMemorySelection(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg)
{
  boolean RetVal = DCM_TRUE;

  /* @Trace: Dcm_SUD_API_20158 */
  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
  if ((NULL_PTR != pAuthConCfg) && (NULL_PTR != pAuthConCfg->pWLMemorySelection))
  {
    /* @Trace: Dcm_SUD_API_20160 */
    KeyM_CertificateIdType CertId = pAuthConCfg->CertId;
    Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pWLMemorySelection;
    uint32 WLMaxSize = DCM_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_MAX_SIZE;

    RetVal = Dcm_ReadAuthenticationElementWhiteList(CertId, pAuthEle, WLMaxSize);
  }
  #else
  DCM_UNUSED(pAuthConCfg);
  #endif

  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_ReadAuthenticationElementWLRid                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Authentication Element White List for Rid      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConCfg                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWLRid(
  Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg)
{
  boolean RetVal = DCM_TRUE;

  /* @Trace: Dcm_SUD_API_20162 */
  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
  if ((NULL_PTR != pAuthConCfg) && (NULL_PTR != pAuthConCfg->pWLRid))
  {
    /* @Trace: Dcm_SUD_API_20164 */
    KeyM_CertificateIdType CertId = pAuthConCfg->CertId;
    Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pWLRid;
    uint32 WLMaxSize = DCM_AUTHENTICATION_WHITE_LIST_RID_MAX_SIZE;

    RetVal = Dcm_ReadAuthenticationElementWhiteList(CertId, pAuthEle, WLMaxSize);
  }
  #else
  DCM_UNUSED(pAuthConCfg);
  #endif

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ReadAuthenticationElementWhiteList              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Authentication Element White List              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : CertId, WLMaxSize                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pAuthEle                                            **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ReadAuthenticationElementWhiteList(
  KeyM_CertificateIdType CertId
  , Dcm_AuthenticationElementPtrType pAuthEle
  , uint32 WLMaxSize)
{
  boolean RetVal = DCM_FALSE;

  if (NULL_PTR != pAuthEle)
  {
    /* @Trace: Dcm_SUD_API_20166 */
    // reset data if re-enter authenticated state
    if (0 < *(pAuthEle->pDataLen))
    {
      /* @Trace: Dcm_SUD_API_20168 */
      Dcm_ResetAuthenticationElement(pAuthEle);
    }

    KeyM_CertElementIdType CertEleId = pAuthEle->Id;
    KeyM_CertElementIteratorType CertEleIte;
    Dcm_Uint8PtrType CertEleData = pAuthEle->pData;
    uint32 CertEleDataLen = pAuthEle->DataMaxLen;
    uint8 EleNum = 0;

    Std_ReturnType Res = KeyM_CertElementGetFirst(
      CertId, CertEleId, &CertEleIte, CertEleData, &CertEleDataLen);

    if (E_OK == Res)
    {
      /* @Trace: Dcm_SUD_API_20170 */
      while (E_OK == Res)
      {
        EleNum = EleNum + 1U;
        /* @Trace: Dcm_SUD_API_20172 */
        *(pAuthEle->pDataLen) += CertEleDataLen;
        pAuthEle->pDataEleLen[EleNum - 1] = CertEleDataLen;

        CertEleData = &pAuthEle->pData[*(pAuthEle->pDataLen)];
        CertEleDataLen = pAuthEle->DataMaxLen - *(pAuthEle->pDataLen);

        Res = KeyM_CertElementGetNext(&CertEleIte, CertEleData, &CertEleDataLen);
      }

      RetVal = DCM_TRUE;
    }

    /* @Trace: SWS_Dcm_01518 */
    CHK_RET_VAL(WLMaxSize < *(pAuthEle->pDataLen), RetVal, FALSE);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ProcessVerifyCertificateUnidirectional          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Verify Certificate Unidirectional           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessVerifyCertificateUnidirectional(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20175 */
  Std_ReturnType RetVal = E_NOT_OK;
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pNrcCode;
  uint8 ResultVal  = DCM_FALSE;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) LpCertificateData;
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) pPduIdTable = NULL_PTR;
  uint8 AuthenticationIdIndex;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pResData;
  pNrcCode = &Dcm_GddNegRespError;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(pPduIdTable->usMainConnectionId);
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    /*
     * new subfunction UniDirectional can be processed with below cases:
     *  - Dcm in idle processing state (Authentication timeout or deauthenticate state)
     *  - UniDirectional -> ProofOfOwerShipClient -> UniDirectional
    */
    if ((Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState == DCM_AUTHENTICATION_IDLE) || 
        (Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState == DCM_PROOFOFOWNERSHIP_SUCCESSFULLY))
    {
      ResultVal = DCM_TRUE;
    }
  }

  if (DCM_TRUE == ResultVal)
  {
    ResultVal = Dcm_ChkCommunicationConfiguration(pMsgContext, pNrcCode);
  }

  if (DCM_TRUE == ResultVal)
  {
    ResultVal = Dcm_ChkLengthOfUnidirectional(pMsgContext, pNrcCode);
  }

  if (DCM_TRUE == ResultVal)
  {
    LpCertificateData = &pMsgContext->reqData[4];
    pResData = &pMsgContext->resData[4]; 

    if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
    {
      #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
      Dcm_GaaCRLLength = pMsgContext->reqDataLen - PLAINDATA - DCM_CERTIFICATE_SIGNATURE - 1U - 5U;
      #endif

      RetVal = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pUniDirectionalFun
        (LpCertificateData, OpStatus, pResData, pNrcCode);

      if (DCM_E_PENDING == RetVal)
      {
        Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState = DCM_UNIDIRECTIONAL_PENDING;

        Dcm_StartTimerExt(
          DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER
          , DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIME
          , Dcm_AuthenticationReProcessing
          , Dcm_CanncelUniDirectionalProcessing);

        /* Authentication service has own pending processing, no need using common pending logic*/
        RetVal = E_OK;
      }
      else
      {
        if (*pNrcCode != DCM_POS_RESP)
        {
          Dcm_InternalSetNegResponse(pMsgContext, *pNrcCode);
          Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
        }
      }
    }
  }
  else
  {
    Dcm_InternalSetNegResponse(pMsgContext, *pNrcCode);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  Dcm_AuthenticationProcessingStateType UniDirectionalState;
  UniDirectionalState = Dcm_GetAuthProcessingState();

  if (UniDirectionalState == VERIFY_CERTIFICATE_INITIAL)
  {
    /* @Trace: Dcm_SUD_API_20174 */
    Dcm_StartTimerExt(
      DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER
      , DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIME
      , Dcm_AuthenticationReProcessing
      , Dcm_CanncelAsyncFuntionCall);
  }

  RetVal = AuthDispatchTable[UniDirectionalState](
    pMsgContext, &Dcm_GddNegRespError);

  if (E_OK != RetVal)
  {
    /* @Trace: Dcm_SUD_API_20176 */
    Dcm_SetAuthProcessingState(AUTHENTICATION_NEGATIVE_RESPONSE);
  }
  #endif /* DCM_STANDARD_SUPPORT */
  
  DCM_UNUSED(pErrorCode);
  DCM_UNUSED(OpStatus);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetAuthProcessingState                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get Authentication Processing State                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_AuthenticationProcessingStateType               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Dcm_AuthenticationProcessingStateType, DCM_CODE) Dcm_GetAuthProcessingState(void)
{
  Dcm_AuthenticationProcessingStateType RetVal = AUTHENTICAITON_PROCESSING_MAX_STATE;
  uint8 AuthenticationIdIndex;

  /* @Trace: Dcm_SUD_API_20179 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20178 */
    RetVal = Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].AuthenticationProcessingState;
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_SetAuthProcessingState                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set Authentication Processing State                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : state                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_SetAuthProcessingState(
  Dcm_AuthenticationProcessingStateType state)
{
  uint8 AuthenticationIdIndex;
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  /* @Trace: Dcm_SUD_API_20181 */
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20180 */
    Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].AuthenticationProcessingState = state;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ChkCommunicationConfiguration                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Communication Configuration                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01459 */
static FUNC(boolean, DCM_CODE) Dcm_ChkCommunicationConfiguration(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  boolean RetVal = DCM_TRUE;
  uint8 COCO = pMsgContext->reqData[1U];

  /* @Trace: Dcm_SUD_API_20183 */
  if (SUPPORT_COMUNICATION_CONFIGURATION != COCO)
  {
    /* @Trace: Dcm_SUD_API_20182 */
    RetVal = DCM_FALSE;
    *pNrcCode = DCM_E_REQUESTOUTOFRANGE;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkLengthOfUnidirectional                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Length Of Unidirectional                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01460*/
static FUNC(boolean, DCM_CODE) Dcm_ChkLengthOfUnidirectional(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20184 */
  boolean RetVal = DCM_TRUE;
  uint16 ChallengeClientLength;
  uint16 CertClientLength;

  uint16 RequestLength;
  RequestLength = (uint16)pMsgContext->reqDataLen;

  uint8 HighByteCertClient = pMsgContext->reqData[2U];
  uint8 LowByteCertClient = pMsgContext->reqData[3U];
  CertClientLength = 
    Dcm_AuthenticationGet2ByteData(HighByteCertClient,LowByteCertClient);

  uint8 HighByteChallengeClient = pMsgContext->reqData[CertClientLength + 4U];
  uint8 LowByteChallengeClient = pMsgContext->reqData[CertClientLength + 5U];
  ChallengeClientLength = Dcm_AuthenticationGet2ByteData(
    HighByteChallengeClient
    , LowByteChallengeClient);

  CHK_RET_VAL(CertClientLength == AUTHENTICATION_DATA_MIN_LENGTH, \
    RetVal, DCM_FALSE);

  CHK_RET_VAL(ChallengeClientLength != AUTHENTICATION_DATA_MIN_LENGTH, \
    RetVal, DCM_FALSE);

  CHK_RET_VAL(RequestLength != (CertClientLength + 6U), \
    RetVal, DCM_FALSE);

  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  /*For ES95489-01. NRC 54 returned when certificate could not be evaluated because the format requirement has not been met.*/
  CHK_RET_VAL(RetVal == DCM_FALSE, *pNrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT);
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  CHK_RET_VAL(RetVal == DCM_FALSE, *pNrcCode, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_AuthenticationReProcessing                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Authentication Re Processing                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_AuthenticationReProcessing(void)
{
  /* @Trace: Dcm_SUD_API_20185 */
#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  Dcm_AuthenticationESPendingProcessing(
    DCM_PENDING, &Dcm_GstMsgContext);
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  (void)Dcm_DcmAuthentication(
    DCM_INITIAL, &Dcm_GstMsgContext, NULL_PTR);
#endif
}

/*******************************************************************************
** Function Name        : Dcm_StoreCertificate                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Store Certificate                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04231 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_StoreCertificate(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  boolean RetVal = DCM_FALSE;
  KeyM_CertificateIdType CertificateId;
  KeyM_CertDataType CertificateDataInfo;
  Std_ReturnType KeyMReturnVal;
  uint8 AuthenticationIdIndex;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  /* @Trace: Dcm_SUD_API_20187 */
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20186 */
    CertificateId = Dcm_GaaAuthenticationConnectionConfig[AuthenticationIdIndex].CertId;

    uint16 CertDataLength;
    uint8 HighByteLength = pMsgContext->reqData[2U];
    uint8 LowByteLength = pMsgContext->reqData[3u];  
    CertDataLength = Dcm_AuthenticationGet2ByteData(HighByteLength, LowByteLength);

    CertificateDataInfo.certDataLength = (uint32) CertDataLength;
    CertificateDataInfo.certData = &pMsgContext->reqData[4U];

    /* @Trace: SWS_Dcm_01463 */
    KeyMReturnVal = KeyM_SetCertificate(CertificateId, &CertificateDataInfo);

    CHK_RET_VAL(E_OK == KeyMReturnVal, RetVal, DCM_TRUE);

    /* @Trace: SWS_Dcm_01464 */
    CHK_RET_VAL(KEYM_E_KEY_CERT_SIZE_MISMATCH == KeyMReturnVal, \
      *pNrcCode, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);

    CHK_RET_VAL(E_OK != KeyMReturnVal && KEYM_E_KEY_CERT_SIZE_MISMATCH != KeyMReturnVal, \
      *pNrcCode, DCM_E_GENERALREJECT);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_UniDirectionalInitial                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Uni Directional Initial                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_UniDirectionalInitial(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20189 */
  Std_ReturnType RetVal = E_NOT_OK;

  uint8 ResultVal = Dcm_ChkCommunicationConfiguration(pMsgContext, pNrcCode);

  CHK_RET_VAL(DCM_TRUE == ResultVal, ResultVal, \
    Dcm_ChkLengthOfUnidirectional(pMsgContext, pNrcCode));

  CHK_RET_VAL(DCM_TRUE == ResultVal, ResultVal, \
    Dcm_StoreCertificate(pMsgContext, pNrcCode));

  if (DCM_TRUE == ResultVal)
  {
    /* @Trace: Dcm_SUD_API_20188 */
    RetVal = E_OK;
    Dcm_SetAuthProcessingState(VERIFY_CERTIFICATE);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_UniDirectionalResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Uni Directional Response                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_UniDirectionalResponse(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20191 */
  Std_ReturnType RetVal = E_NOT_OK;

  if ( DCM_POS_RESP == *pNrcCode)
  {
    /* @Trace: Dcm_SUD_API_20190 */
    RetVal = E_OK;
    Dcm_SetAuthProcessingState(PROOFOFOWNERSHIP_INITIAL);
    Dcm_VerifyCertificateUnidirectionalSuccessfully(pMsgContext);

    Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_VerifyCertificate                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Verify Certificate                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04235 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyCertificate(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  Std_ReturnType RetVal = E_NOT_OK;
  KeyM_CertificateIdType CertificateId;
  uint8 AuthenticationIdIndex;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    CertificateId = Dcm_GaaAuthenticationConnectionConfig[AuthenticationIdIndex].CertId;

    /* @Trace: SWS_Dcm_01468 */
    RetVal = KeyM_VerifyCertificate(CertificateId);

    if (E_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20194 */
      Dcm_SetAuthProcessingState(VERIFY_CERTIFICATE_WAITTING_CALLBACK);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_20195 */
      /* @Trace: SWS_Dcm_01465 */
      CHK_RET_VAL(KEYM_E_BUSY == RetVal, *pNrcCode, \
        DCM_E_BUSYREPEATREQUEST);

      /* @Trace: SWS_Dcm_01466 */
      CHK_RET_VAL(KEYM_E_BUSY != RetVal, *pNrcCode, \
        DCM_E_GENERALREJECT);
    }
  }

  DCM_UNUSED(pMsgContext);
  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CanncelAsyncFuntionCall                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Canncel Async Funtion Call                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01467 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_CanncelAsyncFuntionCall(void)
{
  /* @Trace: Dcm_SUD_API_20197 */
  Dcm_PduIdTablePtrType pPduIdTable;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

  (void)Dcm_ResetToDeauthenticatedState(pPduIdTable->RxConnectionId);

  uint8 AuthenticationIdIndex;
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20196 */
    uint32 JobId;
    JobId = Dcm_AuthenticationGetAsyncJobId(
      &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex]);

    (void) Csm_CancelJob(JobId, CRYPTO_OPERATIONMODE_SINGLECALL);
  }

  Dcm_GblSendResponse = DCM_TRUE;
  Dcm_GddNegRespError = DCM_E_GENERALREJECT;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CreatingServerChallenge                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Creating Server Challenge                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01493 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CreatingServerChallenge(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 CsmJobId;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint8 AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if ((AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
      && (DCM_POS_RESP == *pNrcCode))
  {
    /* @Trace: Dcm_SUD_API_20198 */
    CsmJobId = Dcm_GaaAuthenticationConnectionConfig[AuthenticationIdIndex].RandomJobId;
    Dcm_AuthenticationSetAsyncJobId(CsmJobId, &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex]);

    RetVal = Csm_RandomGenerate(
      CsmJobId
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerData[0U]
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerDataLength);

    if (E_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20200 */
      Dcm_SetAuthProcessingState(CREATE_CHALLENGE_SERVER_WAITTING_CALLBACK);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_20201 */
      /* @Trace: SWS_Dcm_01465 */
      CHK_RET_VAL (CRYPTO_E_BUSY == RetVal, *pNrcCode, DCM_E_BUSYREPEATREQUEST);

      /* @Trace: SWS_Dcm_01466*/
      CHK_RET_VAL(CRYPTO_E_BUSY != RetVal, *pNrcCode, DCM_E_GENERALREJECT);
    }
  }

  DCM_UNUSED(pMsgContext);
  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_VerifyCertificateUnidirectionalSuccessfully     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Verify Certificate Unidirectional Successfully      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01503 */
static FUNC(void, DCM_CODE) Dcm_VerifyCertificateUnidirectionalSuccessfully(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_20203 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint8 AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(pPduIdTable->RxConnectionId);
  uint32 DataLength;

  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    DataLength = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].ulChallengeServerSize;

    pMsgContext->resDataLen = DataLength + 6U;

    pMsgContext->resData[0U] = pMsgContext->reqData[0];
    pMsgContext->resData[1U] = CERTIFICATE_VERIFIED_OWNERSHIP_VERIFICATION_NECESSERY;

    pMsgContext->resData[2U] = Dcm_GetSecondByteFrom4ByteData(DataLength);
    pMsgContext->resData[3U] = Dcm_GetFirstByteFrom4ByteData(DataLength);
    /*
	 @pMsgContext->resData[4~~(4+DataLength)]  = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pUniDirectionalFun
	*/
    pMsgContext->resData[DataLength + 4U] = 0U;
    pMsgContext->resData[DataLength + 5U] = 0U;
  }
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20202 */
    DataLength = Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerDataLength;

    Dcm_MemCopy(&pMsgContext->resData[4U]
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerData[0U]
      , DataLength);

    pMsgContext->resDataLen = DataLength + 6U;

    pMsgContext->resData[0U] = pMsgContext->reqData[0];
    pMsgContext->resData[1U] = CERTIFICATE_VERIFIED_OWNERSHIP_VERIFICATION_NECESSERY;

    pMsgContext->resData[2U] = Dcm_GetSecondByteFrom4ByteData(DataLength);
    pMsgContext->resData[3U] = Dcm_GetFirstByteFrom4ByteData(DataLength);

    pMsgContext->resData[DataLength + 4U] = 0U;
    pMsgContext->resData[DataLength + 5U] = 0U;
  }
  #endif /* DCM_STANDARD_SUPPORT */
}

/*******************************************************************************
** Function Name        : Dcm_ProcessProofofOwnershipClient                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Proof of Ownership Client                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessProofofOwnershipClient(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20205 */
  Std_ReturnType RetVal = E_NOT_OK;

  uint8 AuthenticationIdIndex;
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpProofOfOwnerShipClientData;
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pNrcCode;
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  Dcm_AuthenticationProcessingStateType AuthProcessingState;
  #endif /* DCM_STANDARD_SUPPORT */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    if (Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState == DCM_UNIDIRECTIONAL_SUCCESSFULLY)
    {
      pNrcCode = &Dcm_GddNegRespError;
      RetVal = Dcm_ChkProofofOwnerShipClientLength(pMsgContext, pNrcCode);

      if (E_OK == RetVal)
      {
        LpProofOfOwnerShipClientData = &pMsgContext->reqData[3];
        RetVal = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pProofOfOwnerShipClientFun
          (LpProofOfOwnerShipClientData, OpStatus, pNrcCode);

        if (DCM_E_PENDING == RetVal)
        {
          Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState = DCM_PROOFOFOWNERSHIP_PENDING;

          Dcm_StartTimerExt(
            DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER
            , DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIME
            , Dcm_AuthenticationReProcessing
            , Dcm_CanncelProofOfOwnerShipClientProcessing);
          
          /* Authentication service has own pending processing, no need using common pending logic*/
          RetVal = E_OK;
        }
        else
        {
          if (RetVal == E_NOT_OK)
          {
            Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
            Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
          }
        }
      }
      else 
      {
        Dcm_InternalSetNegResponse(pMsgContext, *pNrcCode);
        Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
      }
    }
    else
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
      Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
    }
  }
  #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20204 */
    AuthProcessingState = Dcm_GetAuthProcessingState();

    /* @Trace: SWS_Dcm_01509 */
    if (PROOFOFOWNERSHIP_INITIAL == AuthProcessingState)
    {
      /* @Trace: Dcm_SUD_API_20206 */
      Dcm_StartTimerExt(
        DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER
        , DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIME
        , Dcm_AuthenticationReProcessing
        , Dcm_CanncelAsyncFuntionCall);
    }

    if (PROOFOFOWNERSHIP_INITIAL > AuthProcessingState)
    {
      /* @Trace: Dcm_SUD_API_20208 */
      Dcm_GddNegRespError = DCM_E_REQUESTSEQUENCEERROR;
      AuthProcessingState = AUTHENTICATION_NEGATIVE_RESPONSE;
    }

    RetVal = AuthDispatchTable[AuthProcessingState](
      pMsgContext, &Dcm_GddNegRespError);
  }

  if (E_OK != RetVal)
  {
    /* @Trace: Dcm_SUD_API_20210 */
    Dcm_SetAuthProcessingState(AUTHENTICATION_NEGATIVE_RESPONSE);
  }
  #endif /* DCM_STANDARD_SUPPORT */

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkProofofOwnerShipClientLength                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Proof of OwnerShip Client Length              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01510 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkProofofOwnerShipClientLength(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  uint8 RetVal = E_OK;

  uint16 LengthOfProofofOwnerShipClient;
  uint8 HighByteProofofOwnerShipClient;
  uint8 LowbyteProofofOwnerShipClient;

  uint16 LengthOfEphemeralPublicKeyClient;
  uint8 HighByteEphemeralPublicKeyClient;
  uint8 LowbyteEphemeralPublicKeyClient;
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  uint8 AuthenticationIdIndex;
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) pPduIdTable;
  #endif /* DCM_STANDARD_SUPPORT */

  uint32 RequestLength;
  RequestLength = pMsgContext->reqDataLen;

  HighByteProofofOwnerShipClient = pMsgContext->reqData[1U];
  LowbyteProofofOwnerShipClient = pMsgContext->reqData[2U];
  LengthOfProofofOwnerShipClient = Dcm_AuthenticationGet2ByteData(
    HighByteProofofOwnerShipClient
    , LowbyteProofofOwnerShipClient);

  HighByteEphemeralPublicKeyClient = pMsgContext->reqData[
    LengthOfProofofOwnerShipClient + 3U];

  LowbyteEphemeralPublicKeyClient = pMsgContext->reqData[
    LengthOfProofofOwnerShipClient + 4U];

  LengthOfEphemeralPublicKeyClient = Dcm_AuthenticationGet2ByteData(
    HighByteEphemeralPublicKeyClient
    , LowbyteEphemeralPublicKeyClient);

  uint16 CompareDataLen = (LengthOfProofofOwnerShipClient + LengthOfEphemeralPublicKeyClient + 5U);

  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->usMainConnectionId );
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    if (Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].ulProofOfOwnerShipClientSize != 
        LengthOfProofofOwnerShipClient)
    {
      RetVal = E_NOT_OK;
      *pNrcCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  #endif /* DCM_STANDARD_SUPPORT */
  if (RequestLength != (uint32)CompareDataLen)
  {
    /* @Trace: Dcm_SUD_API_20212 */
    RetVal = E_NOT_OK;
    *pNrcCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20213 */
    #if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    Dcm_SetAuthProcessingState(VERIFY_PROOFOFOWNERSHIP);
	  #endif /* DCM_STANDARD_SUPPORT */
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_VerifyProofofOwnerShipClient                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Verify Proof of OwnerShip Client                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01511 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyProofofOwnerShipClient(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20215 */
  uint8 RetVal = E_NOT_OK;

  Std_ReturnType CsmRetVal;
  uint32 JobId;
  uint8 AuthenticationIdIndex;
  Dcm_PduIdTablePtrType pPduIdTable;
  uint16 LengthOfProofofOwnerShipClient;
  uint8 HighByteLength;
  uint8 LowByteLength;
  
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20214 */
    JobId = Dcm_GaaAuthenticationConnectionConfig[AuthenticationIdIndex].ProofofOwnerShipClientJobId;
    
    HighByteLength = pMsgContext->reqData[1U];
    LowByteLength = pMsgContext->reqData[2U];
    LengthOfProofofOwnerShipClient = Dcm_AuthenticationGet2ByteData(
      HighByteLength
      , LowByteLength);

    Dcm_AuthenticationSetAsyncJobId(JobId, &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex]);

    CsmRetVal = Csm_SignatureVerify(
      JobId
      , CRYPTO_OPERATIONMODE_SINGLECALL
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerData[0U]
      , Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerDataLength
      , &pMsgContext->reqData[3U]
      , LengthOfProofofOwnerShipClient
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].CsmSignatureVerifyResult);

    if (E_OK == CsmRetVal)
    {
      /* @Trace: Dcm_SUD_API_20216 */
      RetVal = E_OK;
      Dcm_SetAuthProcessingState(VERIFY_PROOFOFOWNERSHIP_WAITTING_CALLBACK);
    }
    else
    {
      /* @Trace: SWS_Dcm_01465 */
      /* @Trace: Dcm_SUD_API_20217 */
      CHK_RET_VAL (CRYPTO_E_BUSY == CsmRetVal, *pNrcCode, DCM_E_BUSYREPEATREQUEST);

      /* @Trace: SWS_Dcm_01466*/
      CHK_RET_VAL(CRYPTO_E_BUSY != CsmRetVal, *pNrcCode, DCM_E_GENERALREJECT);
    }
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ChkCsm_SignatureVerify                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Csm_SignatureVerify                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkCsm_SignatureVerify(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20219 */
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 AuthenticationIdIndex;
  Dcm_PduIdTablePtrType pPduIdTable;

  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20218 */
    Crypto_VerifyResultType CsmResult;
    CsmResult = Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].CsmSignatureVerifyResult;

    /* @Trace: SWS_Dcm_01529 */
    if (CRYPTO_E_VER_OK == CsmResult)
    {
      /* @Trace: Dcm_SUD_API_20220 */
      RetVal = E_OK;
      Dcm_SetAuthProcessingState(PROOFOFOWNERSHIP_RESPONSE);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_20221 */
      /* @Trace: SWS_Dcm_01512 */
      *pNrcCode = DCM_E_OWNERSHIPVERIFICATIONFAILED;
    }
  }

  DCM_UNUSED(pMsgContext);
  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_OwnerShipVerificationSuccess                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : OwnerShip Verification Success                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_OwnerShipVerificationSuccess(
    Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Dcm_PduIdTablePtrType pPduIdTable;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

  if (DCM_TRUE == Dcm_TransitIntoAuthenticatedState(pPduIdTable->RxConnectionId))
  {
    /* @Trace: Dcm_SUD_API_20222 */
    pMsgContext->resDataLen = 4U;
    pMsgContext->resData[0U] = pMsgContext->reqData[0];
    pMsgContext->resData[1U] = OWNERSHIPVERIFIED_AUTHENTICATIONCOMPLETE;

    /* @Trace: SWS_Dcm_01513 */
    pMsgContext->resData[2U] = 0U;
    pMsgContext->resData[3U] = 0U;

    RetVal = E_OK;
	
	#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    Dcm_SetAuthProcessingState(PROOFOFOWNERSHIP_INITIAL);

    Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);

    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
	#endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20223 */
    *pNrcCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT;
  }
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_AuthentationNegativeResponse                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Authentation Negative Response                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthentationNegativeResponse(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20225 */
  if ( DCM_POS_RESP != *pNrcCode)
  {
    /* @Trace: Dcm_SUD_API_20224 */
    Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);

    uint8 AuthConIdx;
    Dcm_PduIdTablePtrType pPduIdTable;
    pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

    AuthConIdx = Dcm_GetAuthConnectionIndex(
      pPduIdTable->RxConnectionId);

    if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
    {
      /* @Trace: Dcm_SUD_API_20226 */
      Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo;
      pAuthConInfo = &Dcm_GaaAuthenConnectionInfo[AuthConIdx];
      Dcm_ResetAuthProcessingState(pAuthConInfo);
    }

    Dcm_InternalSetNegResponse(pMsgContext, *pNrcCode);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_AuthenticationAsynWaitingCallBack               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Authentication Asyn Waiting CallBack                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationAsynWaitingCallBack(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20228 */
  DCM_UNUSED(pNrcCode);
  DCM_UNUSED(pMsgContext);
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ProcessVerifyCertificateBidirectional           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Verify Certificate Bidirectional            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessVerifyCertificateBidirectional(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20230 */
  Std_ReturnType RetVal = E_NOT_OK;

  Dcm_AuthenticationProcessingStateType AuthProcessingState;
  AuthProcessingState = Dcm_GetAuthProcessingState();

  if (AuthProcessingState == VERIFY_CERTIFICATE_INITIAL)
  {
    /* @Trace: Dcm_SUD_API_20229 */
    Dcm_StartTimerExt(
      DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER
      , DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIME
      , Dcm_AuthenticationReProcessing
      , Dcm_CanncelAsyncFuntionCall);
  }

  RetVal = AuthDispatchTable[AuthProcessingState](
    pMsgContext, &Dcm_GddNegRespError);

  if (E_OK != RetVal)
  {
    /* @Trace: Dcm_SUD_API_20231 */
    Dcm_SetAuthProcessingState(AUTHENTICATION_NEGATIVE_RESPONSE);
  }

  DCM_UNUSED(pErrorCode);
  DCM_UNUSED(OpStatus);
  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_VerifyCertificateInitial                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Verify Certificate Initial                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyCertificateInitial(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 AuthenticationSubFunction;
  AuthenticationSubFunction = pMsgContext->reqData[0U];

  /* @Trace: Dcm_SUD_API_20233 Dcm_SUD_API_20234 */
  RetVal = (VERIFY_CERTIFICATE_BIDIRECTIONAL == AuthenticationSubFunction) ?
    Dcm_BiDirectionalInitial(pMsgContext, pErrorCode) :
    Dcm_UniDirectionalInitial(pMsgContext, pErrorCode);

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_BiDirectionalInitial                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Bi Directional Initial                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_BiDirectionalInitial(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20236 */
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 ResultVal = Dcm_ChkCommunicationConfiguration(pMsgContext, pNrcCode);

  CHK_RET_VAL(DCM_TRUE == ResultVal, ResultVal, \
    Dcm_ChkLengthOfBidirectional(pMsgContext, pNrcCode));

  CHK_RET_VAL(DCM_TRUE == ResultVal, ResultVal, \
    Dcm_StoreCertificate(pMsgContext, pNrcCode));

  if (DCM_TRUE == ResultVal)
  {
    /* @Trace: Dcm_SUD_API_20235 */
    RetVal = E_OK;
    Dcm_SetAuthProcessingState(VERIFY_CERTIFICATE);
  }
  return RetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_ChkLengthOfBidirectional                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Length Of Bidirectional                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01461 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(boolean, DCM_CODE) Dcm_ChkLengthOfBidirectional(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20237 */
  boolean RetVal = DCM_TRUE;
  uint16 ChallengeClientLength;
  uint16 CertClientLength;

  uint16 RequestLength;
  RequestLength = (uint16)pMsgContext->reqDataLen;

  uint8 HighByteCertClient = pMsgContext->reqData[2U];
  uint8 LowByteCertClient = pMsgContext->reqData[3U];
  CertClientLength = Dcm_AuthenticationGet2ByteData(
    HighByteCertClient
    , LowByteCertClient);

  uint8 HighByteChallengeClient = pMsgContext->reqData[CertClientLength + 4U];
  uint8 LowByteChallengeClient = pMsgContext->reqData[CertClientLength + 5U];  
  ChallengeClientLength = Dcm_AuthenticationGet2ByteData(
    HighByteChallengeClient
    , LowByteChallengeClient);

  CHK_RET_VAL(CertClientLength == AUTHENTICATION_DATA_MIN_LENGTH, \
    RetVal, DCM_FALSE);

  CHK_RET_VAL(ChallengeClientLength == AUTHENTICATION_DATA_MIN_LENGTH, \
    RetVal, DCM_FALSE);

  CHK_RET_VAL(RequestLength != (CertClientLength + ChallengeClientLength + 6U), \
    RetVal, DCM_FALSE);

  CHK_RET_VAL(RetVal == DCM_FALSE, *pNrcCode, \
    DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CreatingServerChallengeDone                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Creating Server Challenge Done                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CreatingServerChallengeDone(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  uint8 AuthenticationSubFunction;
  AuthenticationSubFunction = pMsgContext->reqData[0U];

  if (VERIFY_CERTIFICATE_BIDIRECTIONAL == AuthenticationSubFunction)
  {
    /* @Trace: Dcm_SUD_API_20238 */
    Dcm_SetAuthProcessingState(SIGN_CHALLENGE_CLIENT);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20239 */
    Dcm_SetAuthProcessingState(UNIDIRECTIONAL_RESPONSE);
  }

  DCM_UNUSED(pNrcCode);
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_SigningChallengeClient                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Signing Challenge Client                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01504 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_SigningChallengeClient(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 JobId;
  uint8 AuthenticationIdIndex;
  Dcm_PduIdTablePtrType pPduIdTable;

  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  uint16 CertClientLength;
  uint8 HighByteCertClient = pMsgContext->reqData[2U];
  uint8 LowByteCertClient = pMsgContext->reqData[3U];
  CertClientLength = Dcm_AuthenticationGet2ByteData(
    HighByteCertClient
    , LowByteCertClient);

  uint16 ChallengeClientLength;
  uint8 HighByteChallengeClient = pMsgContext->reqData[CertClientLength + 4U];
  uint8 LowByteChallengeClient = pMsgContext->reqData[CertClientLength + 5U];
  ChallengeClientLength = Dcm_AuthenticationGet2ByteData(
    HighByteChallengeClient
    , LowByteChallengeClient);

  Dcm_Uint8ConstPtrType pChallengeClientData;
  pChallengeClientData = &pMsgContext->reqData[CertClientLength + 6U];

  /* @Trace: Dcm_SUD_API_20241 */
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20240 */
    JobId = Dcm_GaaAuthenticationConnectionConfig[
      AuthenticationIdIndex].ClientChallengeSignJobId;

    Dcm_AuthenticationSetAsyncJobId(JobId, 
      &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex]);

    RetVal = Csm_SignatureGenerate(
      JobId
      , CRYPTO_OPERATIONMODE_SINGLECALL
      , pChallengeClientData
      , ChallengeClientLength
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ProofOfOwnerShipServer[0U]
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].LengthOfProofOfOwnershipServer
    );

    if (E_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20242 */
      Dcm_SetAuthProcessingState(SIGN_CHALLENGE_CLIENT_WAITTING_CALLBACK);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_20243 */
      /* @Trace: SWS_Dcm_01465 */
      CHK_RET_VAL (CRYPTO_E_BUSY == RetVal, *pNrcCode, DCM_E_BUSYREPEATREQUEST);

      /* @Trace: SWS_Dcm_01466*/
      CHK_RET_VAL(CRYPTO_E_BUSY != RetVal, *pNrcCode, DCM_E_GENERALREJECT);
    }
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ProvidingServerCertificate                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Providing Server Certificate                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01506 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ProvidingServerCertificate(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 EcuCertId;
  KeyM_CertDataType CertificateServerInfo;

  uint8 AuthenticationIdIndex;
  Dcm_PduIdTablePtrType pPduIdTable;

  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  /* @Trace: Dcm_SUD_API_20245 */
  if(AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20244 */
    EcuCertId = Dcm_GaaAuthenticationConnectionConfig[
      AuthenticationIdIndex].ECUCertificateId;

    CertificateServerInfo.certDataLength = AUTHENTICATION_MAX_DATALENGTH;

    CertificateServerInfo.certData = &Dcm_GaaAuthenConnectionInfo[
      AuthenticationIdIndex].CertificateServerData[0U];

    RetVal = KeyM_GetCertificate((KeyM_CertificateIdType)EcuCertId, &CertificateServerInfo);

    if (E_OK == RetVal)
    {
      /* @Trace: Dcm_SUD_API_20246 */
      Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].
      LengthOfCertificateServer = CertificateServerInfo.certDataLength;

      Dcm_SetAuthProcessingState(BIDIRECTIONAL_RESPONSE);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_20247 */
      /* @Trace: SWS_Dcm_01507 */
      CHK_RET_VAL(KEYM_E_KEY_CERT_SIZE_MISMATCH == RetVal, \
        *pNrcCode, DCM_E_RESPONSETOOLONG);

      /* @Trace: SWS_Dcm_01466*/
      CHK_RET_VAL(KEYM_E_KEY_CERT_SIZE_MISMATCH != RetVal, \
        *pNrcCode, DCM_E_GENERALREJECT);
    }
  }

  DCM_UNUSED(pMsgContext);
  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_BiDirectionalResponse                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Bi Directional Response                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_BiDirectionalResponse(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  /* @Trace: Dcm_SUD_API_20249 */
  Std_ReturnType RetVal = E_NOT_OK;

  if ( DCM_POS_RESP == *pNrcCode)
  {
    /* @Trace: Dcm_SUD_API_20248 */
    RetVal = E_OK;
    Dcm_SetAuthProcessingState(PROOFOFOWNERSHIP_INITIAL);
    Dcm_VerifyCertificateBidirectionalSuccessfully(pMsgContext);

    Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_VerifyCertificateBidirectionalSuccessfully      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Verify Certificate Bidirectional Successfully       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01508 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_VerifyCertificateBidirectionalSuccessfully(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_20251 */
  uint8 AuthenticationIdIndex;
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->RxConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20250 */
    uint32 LengthOfChallengeServer;
    uint32 LengthOfCertificateServer;
    uint32 LengthOfProofOfOwnershipServer;

    pMsgContext->resData[0U] = pMsgContext->reqData[0];
    pMsgContext->resData[1U] = CERTIFICATE_VERIFIED_OWNERSHIP_VERIFICATION_NECESSERY;

    LengthOfChallengeServer = Dcm_GaaAuthenConnectionInfo[
      AuthenticationIdIndex].ChallengeServerDataLength;

    LengthOfCertificateServer = Dcm_GaaAuthenConnectionInfo[
      AuthenticationIdIndex].LengthOfCertificateServer;

    LengthOfProofOfOwnershipServer = Dcm_GaaAuthenConnectionInfo[
      AuthenticationIdIndex].LengthOfProofOfOwnershipServer;

    pMsgContext->resDataLen = LengthOfChallengeServer + \
      LengthOfCertificateServer + LengthOfProofOfOwnershipServer + 10U;

    /*update challengeServer*/
    pMsgContext->resData[3U] = Dcm_GetFirstByteFrom4ByteData(LengthOfChallengeServer);
    pMsgContext->resData[2U] = Dcm_GetSecondByteFrom4ByteData(LengthOfChallengeServer);

    Dcm_MemCopy(&pMsgContext->resData[4U]
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ChallengeServerData[0U]
      , LengthOfChallengeServer);

    /*update certificateServer*/
    pMsgContext->resData[LengthOfChallengeServer + 5U] = Dcm_GetFirstByteFrom4ByteData(
      LengthOfCertificateServer);
    pMsgContext->resData[LengthOfChallengeServer + 4U] = Dcm_GetSecondByteFrom4ByteData(
      LengthOfCertificateServer);

    Dcm_MemCopy(&pMsgContext->resData[LengthOfChallengeServer + 6U]
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].CertificateServerData[0U]
      , LengthOfCertificateServer);

    /*update ProofOfOnwerShipServer*/
    pMsgContext->resData[LengthOfChallengeServer + LengthOfCertificateServer + 7U] = Dcm_GetFirstByteFrom4ByteData(
      LengthOfProofOfOwnershipServer);
    pMsgContext->resData[LengthOfChallengeServer + LengthOfCertificateServer + 6U] = Dcm_GetSecondByteFrom4ByteData(
      LengthOfProofOfOwnershipServer);

    Dcm_MemCopy(
      &pMsgContext->resData[LengthOfChallengeServer + LengthOfCertificateServer + 8U]
      , &Dcm_GaaAuthenConnectionInfo[AuthenticationIdIndex].ProofOfOwnerShipServer[0U]
      , LengthOfProofOfOwnershipServer);

    /*update LengthOfEphemeralPublicKeyServer*/
    pMsgContext->resData[LengthOfProofOfOwnershipServer + \
      LengthOfChallengeServer + LengthOfCertificateServer + 8U] = 0x00;

    pMsgContext->resData[LengthOfProofOfOwnershipServer + \
      LengthOfChallengeServer + LengthOfCertificateServer + 9U] = 0x00;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_VerifyTargetIdentification                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Verify Target Identification                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pNrcCode                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04236 */
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_VerifyTargetIdentification(
  Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pNrcCode)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if (DCM_POS_RESP == *pNrcCode)
  {
    /* @Trace: Dcm_SUD_API_20252 */
    #if (DCM_AUTHENTICATION_TARGET_ID_MODE_RULE == STD_ON)
    Dcm_CheckTargetIdModeRule(pNrcCode);
    #endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20253 */
    #if (DCM_AUTHENTICATION_GENERAL_NRC_MODE_RULE == STD_ON)
    Dcm_CheckGeneralNrcModeRule(pNrcCode);
    #endif
  }

  if (DCM_POS_RESP == *pNrcCode)
  {
    /* @Trace: Dcm_SUD_API_20254 */
    RetVal = E_OK;
    Dcm_SetAuthProcessingState(CREATE_CHALLENGE_SERVER);
  }

  DCM_UNUSED(pMsgContext);
  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ResetAuthProcessingState                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset Authentication Processing State               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConInfo                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_ResetAuthProcessingState(
Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo)
{
  /* @Trace: Dcm_SUD_API_20257 */
  if (NULL_PTR != pAuthConInfo)
  {
    /* @Trace: Dcm_SUD_API_20256 */
    pAuthConInfo->AuthenticationProcessingState = VERIFY_CERTIFICATE_INITIAL;
    pAuthConInfo->CsmAsyncJobId = DEFAULT_ASYNC_JOBID;
    pAuthConInfo->CsmSignatureVerifyResult = CRYPTO_E_VER_NOT_OK;

    pAuthConInfo->ChallengeServerDataLength = AUTHENTICATION_MAX_DATALENGTH;
    Dcm_MemClear(pAuthConInfo->ChallengeServerData
      , AUTHENTICATION_MAX_DATALENGTH);

    pAuthConInfo->LengthOfProofOfOwnershipServer = AUTHENTICATION_MAX_DATALENGTH;
    Dcm_MemClear(pAuthConInfo->ProofOfOwnerShipServer
      , AUTHENTICATION_MAX_DATALENGTH);

    pAuthConInfo->LengthOfCertificateServer = AUTHENTICATION_MAX_DATALENGTH;
    Dcm_MemClear(pAuthConInfo->CertificateServerData
      , AUTHENTICATION_MAX_DATALENGTH);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_AuthenticationSetAsyncJobId                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Authentication Set Async Job Id                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : JobId, pAuthConInfo                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(void, DCM_CODE) Dcm_AuthenticationSetAsyncJobId(
  uint32 JobId
  , Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo)
{
  /* @Trace: Dcm_SUD_API_20259 */
  if (NULL_PTR != pAuthConInfo)
  {
    /* @Trace: Dcm_SUD_API_20258 */
    pAuthConInfo->CsmAsyncJobId = JobId;
  }
}
#endif
/*******************************************************************************
** Function Name        : Dcm_AuthenticationGetAsyncJobId                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Authentication Get Async Job Id                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pAuthConInfo                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
static FUNC(uint32, DCM_CODE) Dcm_AuthenticationGetAsyncJobId(
  Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo)
{
  /* @Trace: Dcm_SUD_API_20261 */
  uint32 JobId = DEFAULT_ASYNC_JOBID;

  if (NULL_PTR != pAuthConInfo)
  {
    /* @Trace: Dcm_SUD_API_20260 */
    JobId = pAuthConInfo->CsmAsyncJobId;
  }
  return JobId;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_AuthenticationGet2ByteData                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get uint16 data from 2 uint8 data                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : HighByte, LowByte                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(uint16, DCM_CODE) Dcm_AuthenticationGet2ByteData(
  uint8 HighByte
  , uint8 LowByte)
{
  /* @Trace: Dcm_SUD_API_20262 */
  uint16 Value;
  Value = (uint16) HighByte << DCM_EIGHT;
  Value = Value | (uint16) LowByte;

  return Value;
}

/*******************************************************************************
** Function Name        : Dcm_GetFirstByteFrom4ByteData                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get first byte of uint32 data                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer                                              **
**                                                                            **
** InOut Parameters     : None                                                **
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
static FUNC(uint8, DCM_CODE) Dcm_GetFirstByteFrom4ByteData(uint32 buffer)
{
  /* @Trace: Dcm_SUD_API_20263 */
  uint8 Value;
  Value = (uint8) (buffer & 0xFFu);
  return Value;
}

/*******************************************************************************
** Function Name        : Dcm_GetSecondByteFrom4ByteData                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get second byte of uint32 data                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer                                              **
**                                                                            **
** InOut Parameters     : None                                                **
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
static FUNC(uint8, DCM_CODE) Dcm_GetSecondByteFrom4ByteData(uint32 buffer)
{
  /* @Trace: Dcm_SUD_API_20264 */
  uint8 Value;
  Value = (uint8) (((buffer >> 8U) & 0xFFu));
  return Value;
}


/*******************************************************************************
** Function Name        : Dcm_KeyMAsyncCertificateVerifyFinished              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Can be called from KeyM upon                        **
**                        finishing an asynchronous certificate verification  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Result, CertId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API   **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_91077*/
/*inconsistent with KeyM_CertificateVerifyCallbackNotification*/
/*https:jira.autosar.org/browse/AR-92614*/
/*https:jira.autosar.org/browse/AR-93855*/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
FUNC(Std_ReturnType, DCM_CODE) Dcm_KeyMAsyncCertificateVerifyFinished(
  KeyM_CertificateIdType  CertId
  , KeyM_CertificateStatusType Result)
{
  /* @Trace: Dcm_SUD_API_20266 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->RxConnectionId;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
  Dcm_NegativeResponseCodeType NrcCode;

  NrcCode = DCM_POS_RESP;

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    /* @Trace: Dcm_SUD_API_20265 */
    Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
    pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];

    Dcm_AuthenticationProcessingStateType CurrentAuthProcessingState;
    CurrentAuthProcessingState = Dcm_GetAuthProcessingState();

    CurrentAuthProcessingState++;
    Dcm_SetAuthProcessingState(CurrentAuthProcessingState);

    if (pAuthConCfg->CertId == CertId)
    {
      /* @Trace: SWS_Dcm_01469*/
      CHK_RET_VAL(KEYM_E_CERTIFICATE_SIGNATURE_FAIL == Result, \
        NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE);

      /* @Trace: SWS_Dcm_01470 */
      CHK_RET_VAL(KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST == Result, \
       NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCHAINOFTRUST);

      /* @Trace: SWS_Dcm_01471 */
      CHK_RET_VAL(KEYM_E_CERTIFICATE_INVALID_TYPE == Result, \
        NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTYPE);

      /* @Trace: SWS_Dcm_01472 */
      CHK_RET_VAL(KEYM_E_CERTIFICATE_INVALID_FORMAT == Result, \
        NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT);

      /* @Trace: SWS_Dcm_01473 */
      CHK_RET_VAL(KEYM_E_CERTIFICATE_INVALID_CONTENT == Result, \
        NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT);

      /* @Trace: SWS_Dcm_01475 */
      CHK_RET_VAL(KEYM_E_CERTIFICATE_REVOKED == Result, \
        NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCERTIFICATE);

      /* @Trace: SWS_Dcm_01476*/
      CHK_RET_VAL(KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL == Result, \
        NrcCode, DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD);

      Dcm_GddNegRespError = NrcCode;
    }
  }

  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CsmAsyncJobFinished                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Can be called from Csm upon                         **
**                        finishing an asynchronous job processing.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Result                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API   **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/*https:jira.autosar.org/browse/AR-93854*/
/* @Trace: SWS_Dcm_91076 */
/*inconsistent with Csm_ApplicationCallbackNotification*/
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
FUNC(Std_ReturnType, DCM_CODE) Dcm_CsmAsyncJobFinished(
  /*uint32 JobId*/
  Csm_ResultType Result)
{
  /* @Trace: Dcm_SUD_API_20268 */
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint16 ConnectionId = pPduIdTable->RxConnectionId;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  Dcm_AuthenticationProcessingStateType AuthProcessingState;
  AuthProcessingState = Dcm_GetAuthProcessingState();

  // uint32 CsmAsyncJobId = Dcm_AuthenticationGetAsyncJobId(&AuthConInfo->CsmAsyncJobId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
  {
    
    if (E_OK == Result
        /*JobId == CsmAsyncJobId*/)
    {
      /* @Trace: Dcm_SUD_API_50901 */
      AuthProcessingState++;
      Dcm_SetAuthProcessingState(AuthProcessingState);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_20269 */
      Dcm_SetAuthProcessingState(AUTHENTICATION_NEGATIVE_RESPONSE);

      /* @Trace: SWS_Dcm_01466 SWS_Dcm_01467*/
      Dcm_GddNegRespError = DCM_E_GENERALREJECT;
    }
  }

  return E_OK;
}
#endif


/*******************************************************************************
** Function Name        : Dcm_ValidateAccessRightsWithWLSubServices           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Access Rights With white list for services **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLSubServices(void)
{
  boolean RetVal = DCM_FALSE;
  uint8 ProtocolIdx;

  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA)  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  uint8 RxBufferId = pPduIdTable->ucRxBufferId;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pReqData = Dcm_GaaBufferConfig[RxBufferId].pBufferArea;
  uint16 ConnectionId = pPduIdTable->usMainConnectionId;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
  uint8 LucChkValue;

  LucChkValue = DCM_FALSE;
  if (DCM_TRUE == Dcm_IsAuthenticatedConnection(ConnectionId))
  {
    LucChkValue = DCM_TRUE;
  }

  if (LucChkValue == DCM_TRUE)
  {
    LucChkValue = DCM_FALSE;
    ProtocolIdx = Dcm_GetProtocolTypeIndex(pPduIdTable->ProtocolType);

    if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      LucChkValue = DCM_TRUE;
    }
  }

  if (LucChkValue == DCM_TRUE)
  {
    LucChkValue = DCM_FALSE;
    
    #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
    #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_NUM)
    #endif /* DCM_STANDARD_SUPPORT */
    {
      LucChkValue = DCM_TRUE;
    }
  }

    if (LucChkValue == DCM_TRUE)
  {
    #if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
    uint32 element_MaxLen = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].ucWLSidWithSubfuncSize;
    uint32 index_AuthEleData = 0;

    /*data format: SID SUB SID SUB SID SUB*/
    while (index_AuthEleData < element_MaxLen)
    {
      //check SID
      uint8 LucWLData = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pWLSidWithSubfunction[index_AuthEleData];
      if (pReqData[0] == LucWLData)
      {
        //check Subfunction
        index_AuthEleData++;
        LucWLData = Dcm_GaaAuthenticationConnectionESConfig[AuthConIdx].pWLSidWithSubfunction[index_AuthEleData];
        if (pReqData[1] == LucWLData)
        {
          RetVal = DCM_TRUE;

          //exit loop
          index_AuthEleData = element_MaxLen;
        }
        else 
        {
          /* move to the next SID SUB */
          index_AuthEleData++;
        }
      }
      else
      {
        /*if SID is not matched, no need check subfunction */
        /* move to the next SID SUB */
        index_AuthEleData = index_AuthEleData + 2;
      }
    }
    #elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
    {
      Dcm_AuthenticationConnectionConfigConstPtrType pAuthConCfg;
      pAuthConCfg = &Dcm_GaaAuthenticationConnectionConfig[AuthConIdx];
      Dcm_AuthenticationElementPtrType pAuthEle = pAuthConCfg->pWLServices;

      /* @Trace: SRS_Diag_04234 */
      for (uint8 idx = 0; idx < (DCM_AUTHENTICATION_WHITE_LIST_SERVICES_MAX_SIZE - 1U); idx ++)
      {
        if ((pReqData[0U] == pAuthEle->pData[idx])
            && (pReqData[1U] == pAuthEle->pData[idx + 1U]))
        {
          RetVal = DCM_TRUE;
          break;
        }
      }
    }
    #endif /* DCM_STANDARD_SUPPORT */
  }
  return RetVal;
}

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
/*******************************************************************************
** Function Name        : Dcm_GetAuthenticationConnectionESInfo               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get Authentication Connection ES Information        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_GetAuthenticationConnectionESInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionESInfoPtrType pAuthConInfo)
{
  boolean RetVal = DCM_FALSE;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);
  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    pAuthConInfo->State = Dcm_GaaAuthenConnectionESInfo[AuthConIdx].State;

    Dcm_MemCopy(pAuthConInfo->Role, 
      Dcm_GaaAuthenConnectionESInfo[AuthConIdx].Role, 
      DCM_AUTHENTICATION_ROLE_SIZE);

    RetVal = DCM_TRUE;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_SetAuthenticationConnectionESInfo               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set Authentication Connection ES Information        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConnectionId, pAuthConInfo                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/

FUNC(boolean, DCM_CODE) Dcm_SetAuthenticationConnectionESInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionESInfoConstPtrType pAuthConInfo)
{
  boolean RetVal = DCM_FALSE;
  Dcm_AuthenticationConnectionESInfoPtrType pMyAuthConInfo;
  uint8 AuthConIdx = Dcm_GetAuthConnectionIndex(ConnectionId);

  if (AuthConIdx < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    pMyAuthConInfo = &Dcm_GaaAuthenConnectionESInfo[AuthConIdx];
    pMyAuthConInfo->State = pAuthConInfo->State;

    Dcm_MemCopy(pMyAuthConInfo->Role, 
      pAuthConInfo->Role, DCM_AUTHENTICATION_ROLE_SIZE);

    RetVal = DCM_TRUE;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_AuthenticationESPendingProcessing               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Authentication ES Pending Processing                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/

static FUNC(void, DCM_CODE) Dcm_AuthenticationESPendingProcessing(  
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType RetVal = E_NOT_OK;
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) pPduIdTable = NULL_PTR;
  uint8 AuthenticationIdIndex;
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pNrcCode;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) LpCertificateData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pResData;
  Dcm_AuthenticationESProcessingStateType LddState;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) LpProofOfOwnerShipClientData;

  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(pPduIdTable->usMainConnectionId);
  
  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    LddState = Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState;
    pNrcCode = &Dcm_GddNegRespError;

    switch (LddState)
    {
      case DCM_UNIDIRECTIONAL_PENDING:
      {
        LpCertificateData = &pMsgContext->reqData[4];
        pResData = &pMsgContext->resData[4]; // challenge data start from byte 4
        RetVal = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pUniDirectionalFun
          (LpCertificateData, OpStatus, pResData, pNrcCode);

        if (E_OK == RetVal)
        {
          Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState = DCM_UNIDIRECTIONAL_SUCCESSFULLY;
          // prepare response data
          Dcm_VerifyCertificateUnidirectionalSuccessfully(pMsgContext);

          Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);
          Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
        }
        else
        {
          if (*pNrcCode != DCM_POS_RESP)
          {
            Dcm_InternalSetNegResponse(pMsgContext, *pNrcCode);
            Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);
            Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
            Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState = DCM_AUTHENTICATION_IDLE;
          }
        }
      }
      break;

      case DCM_PROOFOFOWNERSHIP_PENDING:
      {
        LpProofOfOwnerShipClientData = &pMsgContext->reqData[3];
        RetVal = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pProofOfOwnerShipClientFun
          (LpProofOfOwnerShipClientData, OpStatus, pNrcCode);

        if (E_OK == RetVal)
        {
          Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState = DCM_PROOFOFOWNERSHIP_SUCCESSFULLY;
          // prepare response data
          (void)Dcm_OwnerShipVerificationSuccess(pMsgContext, pNrcCode);

          Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);

          if (*pNrcCode != DCM_POS_RESP)
          {
            Dcm_InternalSetNegResponse(pMsgContext, *pNrcCode);
          }
          
          Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
        }
        else
        {
          if (E_NOT_OK == RetVal)
          {
            Dcm_InternalSetNegResponse(pMsgContext, DCM_E_OWNERSHIPVERIFICATIONFAILED);
            Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);
            Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
            Dcm_GaaAuthenConnectionESInfo[AuthenticationIdIndex].ESProcessingState = DCM_AUTHENTICATION_IDLE;
          }
        }
      }
      break;

      default:
        /*do nothing*/
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_CanncelUniDirectionalProcessing                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel process function for UniDirectional          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_CanncelUniDirectionalProcessing(void)
{
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA)  pPduIdTable;
  uint8 AuthenticationIdIndex;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pNrcCode = &Dcm_GddNegRespError;

  (void)Dcm_ResetToDeauthenticatedState(pPduIdTable->usMainConnectionId );

  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->usMainConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    (void)Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pProofOfOwnerShipClientFun
          (NULL_PTR, DCM_CANCEL, pNrcCode);
  }

  Dcm_InternalSetNegResponse(&Dcm_GstMsgContext, DCM_E_GENERALREJECT);
  Dcm_InternalProcessingDone(&Dcm_GstMsgContext, DCM_SYNC_DONE);

}

/*******************************************************************************
** Function Name        : Dcm_CanncelProofOfOwnerShipClientProcessing         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel process function for ProofOfOwnerShipClient  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_CanncelProofOfOwnerShipClientProcessing(void)
{
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA)  pPduIdTable;
  uint8 AuthenticationIdIndex;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  (void)Dcm_ResetToDeauthenticatedState(pPduIdTable->usMainConnectionId );

  AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(
    pPduIdTable->usMainConnectionId);

  if (AuthenticationIdIndex < DCM_AUTHENTICATION_CONNECTION_ES_NUM)
  {
    (void)Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pUniDirectionalFun
          (NULL_PTR, DCM_CANCEL, NULL_PTR, NULL_PTR);
  }

  Dcm_InternalSetNegResponse(&Dcm_GstMsgContext, DCM_E_GENERALREJECT);
  Dcm_InternalProcessingDone(&Dcm_GstMsgContext, DCM_SYNC_DONE);
}

#endif /* DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT */
#endif /*Precompile option for Authentication*/

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
********************************************************************************/
