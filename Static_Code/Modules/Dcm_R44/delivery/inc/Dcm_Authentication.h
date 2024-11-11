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
**  SRC-MODULE: Dcm_Authentication.h                                          **
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
** Revision     Date            By             Description                    **
********************************************************************************
** 0.0.1        15-Jun-2020     LanhLT         Initial Version                **
** 0.0.2        16-Aug-2020     LanhLT         Changes made as per #14836     **
** 0.0.3        13-Oct-2020     LanhLT         Changes made as per #15766     **
** 0.0.4        02-Nov-2020     LanhLT         Changes made as per #16832     **
** 0.0.5        04-Dec-2020     LanhLT         Polyspace fixing as per #15175 **
** 1.0.9        31-Mar-2023     LanhLT         Refer #CP44-1739               **
** 1.1.0        12-Oct-2023     SY Kim         Refer #CP44-3106, #CP44-2676   **
*******************************************************************************/

#ifndef DCM_AUTHENTICATION_H
#define DCM_AUTHENTICATION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_PCTypes.h"
#include "Dcm_Cfg.h"

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
#if (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
#include "Csm.h"
#endif
#endif

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)

typedef enum {
  DCM_DEAUTHENTICATED
  , DCM_AUTHENTICATED
} Dcm_AuthenticationStateType;

typedef uint8 Dcm_AuthenticationProcessingStateType;

#define VERIFY_CERTIFICATE_INITIAL                ((Dcm_AuthenticationProcessingStateType) 0x00)
#define VERIFY_CERTIFICATE                        ((Dcm_AuthenticationProcessingStateType) 0x01)

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
typedef uint8 Dcm_AuthenticationESProcessingStateType;
#define DCM_AUTHENTICATION_IDLE                       ((Dcm_AuthenticationESProcessingStateType) 0x00)
#define DCM_UNIDIRECTIONAL_PENDING                    ((Dcm_AuthenticationESProcessingStateType) 0x01)
#define DCM_UNIDIRECTIONAL_SUCCESSFULLY               ((Dcm_AuthenticationESProcessingStateType) 0x02)
#define DCM_PROOFOFOWNERSHIP_PENDING                  ((Dcm_AuthenticationESProcessingStateType) 0x03)
#define DCM_PROOFOFOWNERSHIP_SUCCESSFULLY             ((Dcm_AuthenticationESProcessingStateType) 0x04)

#define AUTHENTICAITON_PROCESSING_MAX_STATE       ((Dcm_AuthenticationESProcessingStateType) 0x05)


typedef struct STagDcm_AuthenticationConnectionESInfoType
{
  /* Authenticattion role */
  Dcm_AuthenticationRoleType Role;

  /* Authentication State */
  Dcm_AuthenticationESProcessingStateType ESProcessingState;

  /* Authentication State */
  Dcm_AuthenticationStateType State;

} Dcm_AuthenticationConnectionESInfoType;

typedef P2VAR(Dcm_AuthenticationConnectionESInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_AuthenticationConnectionESInfoPtrType;

typedef P2CONST(Dcm_AuthenticationConnectionESInfoType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_AuthenticationConnectionESInfoConstPtrType;

#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)

#define VERIFY_CERTIFICATE_WAITTING_CALLBACK      ((Dcm_AuthenticationProcessingStateType) 0x02)
#define VERIFY_CERTIFICATE_TARGET_ID              ((Dcm_AuthenticationProcessingStateType) 0x03)
#define CREATE_CHALLENGE_SERVER                   ((Dcm_AuthenticationProcessingStateType) 0x04)
#define CREATE_CHALLENGE_SERVER_WAITTING_CALLBACK ((Dcm_AuthenticationProcessingStateType) 0x05)
#define CREATE_CHALLENGE_SERVER_DONE              ((Dcm_AuthenticationProcessingStateType) 0x06)
#define UNIDIRECTIONAL_RESPONSE                   ((Dcm_AuthenticationProcessingStateType) 0x07)
#define SIGN_CHALLENGE_CLIENT                     ((Dcm_AuthenticationProcessingStateType) 0x08)
#define SIGN_CHALLENGE_CLIENT_WAITTING_CALLBACK   ((Dcm_AuthenticationProcessingStateType) 0x09)
#define PROVIDE_SERVER_CERTIFICATE                ((Dcm_AuthenticationProcessingStateType) 0x0A)
#define BIDIRECTIONAL_RESPONSE                    ((Dcm_AuthenticationProcessingStateType) 0x0B)
#define PROOFOFOWNERSHIP_INITIAL                  ((Dcm_AuthenticationProcessingStateType) 0x0C)
#define VERIFY_PROOFOFOWNERSHIP                   ((Dcm_AuthenticationProcessingStateType) 0x0D)
#define VERIFY_PROOFOFOWNERSHIP_WAITTING_CALLBACK ((Dcm_AuthenticationProcessingStateType) 0x0E)
#define VERIFY_PROOFOFOWNERSHIP_RESULT            ((Dcm_AuthenticationProcessingStateType) 0x0F)
#define PROOFOFOWNERSHIP_RESPONSE                 ((Dcm_AuthenticationProcessingStateType) 0x10)
#define AUTHENTICATION_NEGATIVE_RESPONSE          ((Dcm_AuthenticationProcessingStateType) 0x11)
#define AUTHENTICAITON_PROCESSING_MAX_STATE       ((Dcm_AuthenticationProcessingStateType) 0x12)

typedef struct STagDcm_AuthenticationConnectionInfoType
{
  uint32 CsmAsyncJobId;
  uint32 ChallengeServerDataLength;
  uint32 LengthOfCertificateServer;
  uint32 LengthOfProofOfOwnershipServer;

  uint8 ChallengeServerData[AUTHENTICATION_MAX_DATALENGTH];
  uint8 ProofOfOwnerShipServer[AUTHENTICATION_MAX_DATALENGTH];
  uint8 CertificateServerData[AUTHENTICATION_MAX_DATALENGTH];
  Dcm_AuthenticationRoleType Role;

  Crypto_VerifyResultType CsmSignatureVerifyResult;
  Dcm_AuthenticationStateType State;
  Dcm_AuthenticationProcessingStateType AuthenticationProcessingState;

} Dcm_AuthenticationConnectionInfoType;

typedef P2VAR(Dcm_AuthenticationConnectionInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_AuthenticationConnectionInfoPtrType;

typedef P2CONST(Dcm_AuthenticationConnectionInfoType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_AuthenticationConnectionInfoConstPtrType;

#endif /* DCM_STANDARD_SUPPORT */
#endif /* DCM_AUTHENTICATION_SERVICE == STD_ON */

/*******************************************************************************
**                      Function  Definitions                                 **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_InitAuthentication(
  Dcm_ConfigConstPtrType pConfig);

#if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_StartPersistAuthenticationState(void);

extern FUNC(void, DCM_CODE) Dcm_WaitRestorePersistedAuthenticationState(void);

extern FUNC(void, DCM_CODE) Dcm_CancelRestorePersistedAuthenticationState(void);

extern FUNC(void, DCM_CODE) Dcm_WaitPersistAuthenticationState(void);

extern FUNC(void, DCM_CODE) Dcm_CancelPersistAuthenticationState(void);

extern FUNC(void, DCM_CODE) Dcm_StartRestorePersistedAuthenticationState(void);
#endif

extern FUNC(boolean, DCM_CODE) Dcm_TriggerTimerFallbackToDeauthenticatedState(void);

extern FUNC(void, DCM_CODE) Dcm_FallbackToDeauthenticatedState(void);

extern FUNC(boolean, DCM_CODE) Dcm_ValidateServiceAccessRights(
  Dcm_ServiceIdConfigConstPtrType pServiceCfg);

extern FUNC(boolean, DCM_CODE) Dcm_ValidateSubServiceAccessRights(
  Dcm_ServiceIdConfigConstPtrType pServiceCfg
  , Dcm_SubServiceIdConfigConstPtrType pSubServiceCfg);

#if (DCM_MODE_CONDITION == STD_ON)
extern FUNC(boolean, DCM_CODE) Dcm_IsValidCertificateElementCondition(
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg);
#endif

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmAuthentication(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

// public for future use in DSP (some special services) if have configured role
extern FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRights(
  Dcm_AuthenticationRoleType AssignedRole);

// public for future use in DSP (some special services) after failed to validate role
/* @Trace: SWS_Dcm_01525 */
extern FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLDid(
  Dcm_Uint8ConstPtrType pData
  , uint32 DataLen);

/* @Trace: SWS_Dcm_01526 */
extern FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLRid(
  Dcm_Uint8ConstPtrType pData
  , uint32 DataLen);

/* @Trace: SWS_Dcm_01527 */
extern FUNC(boolean, DCM_CODE) Dcm_ValidateAccessRightsWithWLMemorySelection(
  Dcm_Uint8ConstPtrType pData);

extern FUNC(boolean, DCM_CODE) Dcm_IsAuthenticatedConnection(
  uint16 ConnectionId);

extern FUNC(uint8, DCM_CODE) Dcm_GetAuthConnectionIndex(
  uint16 ConnectionId);

extern FUNC(boolean, DCM_CODE) Dcm_ResetToDeauthenticatedState(
  uint16 ConnectionId);

extern FUNC(boolean, DCM_CODE) Dcm_TransitIntoAuthenticatedState(
  uint16 ConnectionId);

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)
extern FUNC(boolean, DCM_CODE) Dcm_SetAuthenticationConnectionESInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionESInfoConstPtrType pAuthConInfo);

extern FUNC(boolean, DCM_CODE) Dcm_GetAuthenticationConnectionESInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionESInfoPtrType pAuthConInfo)  ;
#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
extern FUNC(boolean, DCM_CODE) Dcm_GetAuthenticationConnectionInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionInfoPtrType pAuthConInfo);

extern FUNC(boolean, DCM_CODE) Dcm_SetAuthenticationConnectionInfo(
  uint16 ConnectionId
  , Dcm_AuthenticationConnectionInfoConstPtrType pAuthConInfo);
#endif /* DCM_STANDARD_SUPPORT */

#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
