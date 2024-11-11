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
**  SRC-MODULE: Dcm_DslManageSecurity.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Manage the security level in Dcm                              **
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
** 0.0.1     31-Dec-2019   HueKM          Initial version                     **
** 0.0.2     15-Jan-2020   SonDT1         Refactor code                       **
** 0.0.3     16-Aug-2020   SonDT1         Changes made as per #14836          **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     02-Nov-2020   HueKM          Changes made as per #16832          **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE                           **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1763                    **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-3035                    **
*******************************************************************************/

/*******************************************************************************
**                           Include Section                                  **
*******************************************************************************/
#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dcm_Config.h"
#include "Dcm_DslManageSecurity.h"
#include "Dcm_Validate.h"
#include "Dcm_Timer.h"
#include "Dcm_Ram.h"

/*******************************************************************************
**                           Internal macros and data types                   **
*******************************************************************************/
#if (DCM_DSP_SECURITY_SERVICE == STD_ON)
#define SECURITY_SERVICE_ENABLED

#if (DCM_NUM_OF_ATTEMPT_COUNTER_ENABLE != DCM_ZERO)
#define SECURITY_ATTEMPT_COUNTER_ENABLED
#endif
#endif

/* Max write time is hard to three times of main function */
#define DCM_MAX_ATTEMPT_COUNTER_WRITEOUT_TIME (3 * DCM_TASK_TIME)

typedef P2FUNC(void, DCM_CODE, Dcm_Internal_GetSecurityAttemptCounterFunType)(
  uint8 SecLvlIdx);

typedef P2FUNC(void, DCM_CODE, Dcm_Internal_SetSecurityAttemptCounterFunType)(
  uint8 SecLvlIdx);

typedef struct
{
  Dcm_SecLevelType SecurityLevel;

  #ifdef SECURITY_SERVICE_ENABLED
  uint8 SecurityLevelIndex;
  #endif

} Dcm_SecurityLevelInfoType;

#ifdef SECURITY_SERVICE_ENABLED
typedef struct
{
  uint8 ucAttCounter;

  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  boolean blGetAttPending;

  boolean blSetAttPending;
  #endif

} Dcm_SecurityLevStateType;

static VAR(Dcm_SecurityLevStateType, DCM_VAR) Dcm_GaaSecLevState[
  DCM_NUM_OF_SECURITYLEVELCONFIG];
#endif

#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
typedef struct STagDcm_AttCounterControlType
{
  uint8 ucGetAttPendingCount;

  uint8 ucSetAttPendingCount;

} Dcm_AttCounterControlType;

static VAR(Dcm_AttCounterControlType, DCM_VAR) Dcm_GddAttCounterControl;
#endif

static VAR(Dcm_SecurityLevelInfoType, DCM_VAR) Dcm_GddSecurityLevelInfo;

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                           Static functions declaration                     **
*******************************************************************************/
#ifdef SECURITY_SERVICE_ENABLED
static FUNC(void, DCM_CODE) Dcm_InitSecurityLevelState(
  Dcm_ConfigConstPtrType pConfig);
#endif

#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
static FUNC(void, DCM_CODE) Dcm_InitSecurityAttemptCounterControl(
  Dcm_ConfigConstPtrType pConfig);
#endif

#ifdef SECURITY_SERVICE_ENABLED
static FUNC(boolean, DCM_CODE) IsSecurityLevelIndexValid(
  uint8 SecLvlIdx);
#endif

#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounters(
  Dcm_OpStatusType OpStatus);

static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounterInitial(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounterPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounterCancel(
  uint8 SecLvlIdx);

static FUNC(boolean, DCM_CODE) Dcm_IsGetSecurityAttemptCountersPending(
  void);

static FUNC(void, DCM_CODE) Dcm_TriggerGetAttPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_ClearGetAttPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounters(
  Dcm_OpStatusType OpStatus);

static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounterInitial(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounterPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounterCancel(
  uint8 SecLvlIdx);

static FUNC(boolean, DCM_CODE) Dcm_IsSetSecurityAttemptCountersPending(
  void);

static FUNC(void, DCM_CODE) Dcm_TriggerSetAttPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_ClearSetAttPending(
  uint8 SecLvlIdx);
#endif

#ifdef SECURITY_SERVICE_ENABLED
static FUNC(uint8, DCM_CODE) Dcm_ReadAttCounter(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_WriteAttCounter(
  uint8 SecLvlIdx, 
  uint8 AttCounter);
#endif

#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
static FUNC(boolean, DCM_CODE) Dcm_IsGetAttPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_WriteGetAttPending(
  uint8 SecLvlIdx, 
  boolean GetAttPending);

static FUNC(boolean, DCM_CODE) Dcm_IsSetAttPending(
  uint8 SecLvlIdx);

static FUNC(void, DCM_CODE) Dcm_WriteSetAttPending(
  uint8 SecLvlIdx, 
  boolean SetAttPending);

static FUNC(uint8, DCM_CODE) Dcm_ReadGetAttPendingCount(
  void);

static FUNC(void, DCM_CODE) Dcm_WriteGetAttPendingCount(
  uint8 GetAttPendingCount);

static FUNC(uint8, DCM_CODE) Dcm_ReadSetAttPendingCount(
  void);

static FUNC(void, DCM_CODE) Dcm_WriteSetAttPendingCount(
  uint8 SetAttPendingCount);
#endif

/*******************************************************************************
**                           Functions definition                             **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Dcm_InitManageSecurity                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for manage security level features  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_InitManageSecurity(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: SWS_Dcm_00020 SWS_Dcm_00033 */
  /* @Trace: Dcm_SUD_API_00961 */
  DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);

  #ifdef SECURITY_SERVICE_ENABLED
  Dcm_InitSecurityLevelState(pConfig);
  #endif

  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  Dcm_InitSecurityAttemptCounterControl(pConfig);
  #endif

  Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityLevel                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function provides the active security level    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : SecLevel                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04011 */
/* @Trace: SWS_Dcm_00338 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel
  (P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel)
{
  /* @Trace: Dcm_SUD_API_00940 */
  Std_ReturnType RetVal = E_OK;
  uint8 ApiId = DCM_GET_SECURITY_LEVEL_SID;

  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, SecLevel));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_00939 */
    *SecLevel = DslInternal_GetSecurityLevel();
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsSecurityLevelLocked                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the current security level is in lock state**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsSecurityLevelLocked(void)
{
  /* @Trace: Dcm_SUD_API_00989 */
  boolean retVal = DCM_FALSE;

  if (DCM_SEC_LEV_LOCKED == DslInternal_GetSecurityLevel())
  {
    /* @Trace: Dcm_SUD_API_00988 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : DslInternal_GetSecurityLevel                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Getter function to get the current security level   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_SecLevelType                                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_SecLevelType, DCM_CODE) DslInternal_GetSecurityLevel(void)
{
  /* @Trace: Dcm_SUD_API_01052 */
  return Dcm_GddSecurityLevelInfo.SecurityLevel;
}

/*******************************************************************************
** Function Name        : DslInternal_SetSecurityLevel                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setter function to set the current security level   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecurityLevel                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) DslInternal_SetSecurityLevel(
  Dcm_SecLevelType SecurityLevel)
{
  /* @Trace: Dcm_SUD_API_01053 */
  Dcm_GddSecurityLevelInfo.SecurityLevel = SecurityLevel;
}

/*******************************************************************************
** Function Name        : Dcm_IsSecurityLevelIndexValid                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the index of current security level index  **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsSecurityLevelIndexValid(void)
{
  /* @Trace: Dcm_SUD_API_00986 */
  boolean Valid = DCM_FALSE;

  #ifdef SECURITY_SERVICE_ENABLED
  Valid = IsSecurityLevelIndexValid(Dcm_GetSecurityLevelIndex());
  #endif

  return Valid;
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityLevelIndex                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Getter function to get the current index            **
**                        of security level                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_GetSecurityLevelIndex(void)
{
  /* @Trace: Dcm_SUD_API_00954 */
  uint8 SecLvlIdx = DCM_ZERO;

  #ifdef SECURITY_SERVICE_ENABLED
  SecLvlIdx = Dcm_GddSecurityLevelInfo.SecurityLevelIndex;
  #endif

  return SecLvlIdx;
}

/*******************************************************************************
** Function Name        : Dcm_SetSecurityLevelIndex                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setter function to set the current index            **
**                        of security level                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SetSecurityLevelIndex(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01027 */
  #ifdef SECURITY_SERVICE_ENABLED
  Dcm_GddSecurityLevelInfo.SecurityLevelIndex = SecLvlIdx;
  #else
  DCM_UNUSED(SecLvlIdx);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityLevelConfig                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the configuration of current security level     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_SecurityLevConfigConstPtrType                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_SecurityLevConfigConstPtrType, DCM_CODE) Dcm_GetSecurityLevelConfig(
  void)
{
  /* @Trace: Dcm_SUD_API_00942 */
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg = NULL_PTR;

  #ifdef SECURITY_SERVICE_ENABLED
  pSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(Dcm_GetSecurityLevelIndex());
  #endif

  return pSecLvlCfg;
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityLevelConfigByIndex                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security configuration by index value       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_SecurityLevConfigConstPtrType                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_SecurityLevConfigConstPtrType, DCM_CODE) Dcm_GetSecurityLevelConfigByIndex(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00944 */
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg = NULL_PTR;

  #ifdef SECURITY_SERVICE_ENABLED
  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_00945 */
    pSecLvlCfg = &Dcm_GaaSecurityLevConfig[SecLvlIdx];
  }
  #else
  DCM_UNUSED(SecLvlIdx);
  #endif

  return pSecLvlCfg;
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityLevelConfigByLevel                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security configuration by security level    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SecLvl                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_SecurityLevConfigConstPtrType                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_SecurityLevConfigConstPtrType, DCM_CODE) Dcm_GetSecurityLevelConfigByLevel(
  Dcm_SecLevelType SecLvl)
{
  /* @Trace: Dcm_SUD_API_00948 */
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg = NULL_PTR;

  #ifdef SECURITY_SERVICE_ENABLED
  uint8 LucIdx;
  for (LucIdx = DCM_ZERO; LucIdx < DCM_NUM_OF_SECURITYLEVELCONFIG; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_00950 */
    if (Dcm_GaaSecurityLevConfig[LucIdx].ddSecLevel == SecLvl)
    {
      /* @Trace: Dcm_SUD_API_00951 */
      Dcm_SetSecurityLevelIndex(LucIdx);
      LpSecLvlCfg = &Dcm_GaaSecurityLevConfig[LucIdx];
      break;
    }
  }
  #else
  DCM_UNUSED(SecLvl);
  #endif

  return LpSecLvlCfg;
}

/*******************************************************************************
** Function Name        : Dcm_IncSecurityAttemptCounter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Increase the security attempt counter value         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_IncSecurityAttemptCounter(void)
{
  #ifdef SECURITY_SERVICE_ENABLED
  /* @Trace: Dcm_SUD_API_00956 */
  if (DCM_TRUE == Dcm_IsSecurityLevelIndexValid())
  {
    /* @Trace: Dcm_SUD_API_00958 */
    uint8 AttCounter = Dcm_GetSecurityAttemptCounter();
    Dcm_SecurityLevConfigConstPtrType pSecLvlCfg = Dcm_GetSecurityLevelConfig();

    if ((NULL_PTR != pSecLvlCfg) && 
        (AttCounter < pSecLvlCfg->ucSecNumMaxAttDelay))
    {
      /* @Trace: Dcm_SUD_API_00959 */
      AttCounter++;
      Dcm_SetSecurityAttemptCounter(AttCounter);
    }
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DecSecurityAttemptCounter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Decrease the security attempt counter value         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DecSecurityAttemptCounter(void)
{
  /* @Trace: Dcm_SUD_API_00912 */
  #ifdef SECURITY_SERVICE_ENABLED
  if (DCM_TRUE == Dcm_IsSecurityLevelIndexValid())
  {
    /* @Trace: Dcm_SUD_API_00913 */
    uint8 AttCounter = Dcm_GetSecurityAttemptCounter();

    if (AttCounter > DCM_ZERO)
    {
      /* @Trace: Dcm_SUD_API_00916 */
      AttCounter--;
      Dcm_SetSecurityAttemptCounter(AttCounter);
    }
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_IsSecurityAttemptCounterExceeded                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the current security attempt counter value **
**                        is exceed the configured value or not               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsSecurityAttemptCounterExceeded(void)
{
  /* @Trace: Dcm_SUD_API_00975 */
  boolean Exceeded = DCM_FALSE;

  #ifdef SECURITY_SERVICE_ENABLED
  if (DCM_TRUE == Dcm_IsSecurityLevelIndexValid())
  {
    /* @Trace: Dcm_SUD_API_00977 */
    uint8 AttCounter = Dcm_GetSecurityAttemptCounter();
    Dcm_SecurityLevConfigConstPtrType pSecLvlCfg = Dcm_GetSecurityLevelConfig();

    if ((NULL_PTR != pSecLvlCfg) && 
        (pSecLvlCfg->ucSecNumMaxAttDelay <= AttCounter))
    {
      /* @Trace: Dcm_SUD_API_00978 */
      Exceeded = DCM_TRUE;
    }
  }
  #endif

  return Exceeded;
}

/*******************************************************************************
** Function Name        : Dcm_ResetSecurityAttemptCounter                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset the value of security attempt counter         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ResetSecurityAttemptCounter(void)
{
  /* @Trace: Dcm_SUD_API_00998 */
  #ifdef SECURITY_SERVICE_ENABLED
  uint8 SecLvlIdx = Dcm_GetSecurityLevelIndex();
  Dcm_WriteAttCounter(SecLvlIdx, DCM_ZERO);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityAttemptCounter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security attempt counter value of           **
**                        current security level                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_GetSecurityAttemptCounter(void)
{
  /* @Trace: Dcm_SUD_API_00917 */
  uint8 AttCounter = DCM_ZERO;

  #ifdef SECURITY_SERVICE_ENABLED
  AttCounter = Dcm_ReadAttCounter(Dcm_GetSecurityLevelIndex());
  #endif

  return AttCounter;
}

/*******************************************************************************
** Function Name        : Dcm_SetSecurityAttemptCounter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the security attempt counter value of           **
**                        current security level                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : AttCounter                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounter(
  uint8 AttCounter)
{
  /* @Trace: Dcm_SUD_API_01011 */
  #ifdef SECURITY_SERVICE_ENABLED
  uint8 SecLvlIdx = Dcm_GetSecurityLevelIndex();
  Dcm_WriteAttCounter(SecLvlIdx, AttCounter);
  #else
  DCM_UNUSED(AttCounter);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_StartRestoreSecurityAttemptCounters             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Restore the value of security attempt counter       **
**                        of all security level configured                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StartRestoreSecurityAttemptCounters(void)
{
  /* @Trace: Dcm_SUD_API_01033 */
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  /* @Trace: SWS_Dcm_01154 */
  Dcm_GetSecurityAttemptCounters(DCM_INITIAL);

  if (DCM_TRUE == Dcm_IsGetSecurityAttemptCountersPending())
  {
    /* @Trace: Dcm_SUD_API_50903 */
    Dcm_StartTimerExt(
      DCM_READ_ATTEMPT_COUNTER_TIMER
      , DCM_MAX_ATTEMPT_COUNTER_READOUT_TIME
      , Dcm_WaitRestoreSecurityAttemptCounters
      , Dcm_CancelRestoreSecurityAttemptCounters);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_WaitRestoreSecurityAttemptCounters              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pending process function in case restore            **
**                        security attempt counter value                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_WaitRestoreSecurityAttemptCounters(void)
{
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  if (DCM_TRUE == Dcm_IsGetSecurityAttemptCountersPending())
  {
    /* @Trace: Dcm_SUD_API_01043 */
    Dcm_GetSecurityAttemptCounters(DCM_PENDING);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01042 */
    Dcm_StopTimer(DCM_READ_ATTEMPT_COUNTER_TIMER);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_CancelRestoreSecurityAttemptCounters            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel process function in case restore             **
**                        security attempt counter value                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CancelRestoreSecurityAttemptCounters(void)
{
  /* @Trace: Dcm_SUD_API_00906 */
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  if (DCM_TRUE == Dcm_IsGetSecurityAttemptCountersPending())
  {
    /* @Trace: SWS_Dcm_01352 */
    /* @Trace: Dcm_SUD_API_00908 */
    Dcm_GetSecurityAttemptCounters(DCM_CANCEL);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_RestoreSecurityAttemptCountersDone              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process action in case all         **
**                        security attempt counters are restored successfully **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_RestoreSecurityAttemptCountersDone(void)
{
  /* @Trace: Dcm_SUD_API_01001 */
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  uint8 LucIdx;
  uint8 LucAttCounter;

  uint32 LusDelayTime;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  if (DCM_FALSE == Dcm_IsGetSecurityAttemptCountersPending())
  {
    /* @Trace: Dcm_SUD_API_01003 */
    for (LucIdx = DCM_ZERO; LucIdx < DCM_NUM_OF_SECURITYLEVELCONFIG; LucIdx++)
    {
      /* @Trace: Dcm_SUD_API_01004 */
      LucAttCounter = Dcm_ReadAttCounter(LucIdx);
      LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(LucIdx);

      if ((NULL_PTR != LpSecLvlCfg) && 
          (LucAttCounter >= LpSecLvlCfg->ucSecNumMaxAttDelay))
      {
        /* @Trace: Dcm_SUD_API_01007 */
        /* @Trace: SWS_Dcm_01355 SWS_Dcm_01356 */
        LusDelayTime = LpSecLvlCfg->usSecDelayTime;

        if (LusDelayTime < LpSecLvlCfg->usSecurityDelayTimeOnBoot)
        {
          /* @Trace: Dcm_SUD_API_01008 */
          LusDelayTime = LpSecLvlCfg->usSecurityDelayTimeOnBoot;
        }

        /* Start security timer */
        Dcm_StartTimer(DCM_SECURITY_TIMER, LusDelayTime);

        /* @Trace: SWS_Dcm_01357 */
        Dcm_WriteAttCounter(LucIdx, DCM_ZERO);
      }
    }
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_IsSecurityAttemptCounterRestored                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if all security attempt coutners are restored **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : ServiceId, SubServiceId                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(boolean, DCM_CODE) Dcm_IsSecurityAttemptCounterRestored(
  uint8 ServiceId, 
  uint8 SubServiceId, 
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_00981 */
  boolean Restored = DCM_TRUE;

  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  if ((DCM_TRUE == Dcm_IsGetSecurityAttemptCountersPending()) && 
      (DCM_SECURITYACCESS == ServiceId) && 
      (DCM_ZERO != (SubServiceId & DCM_BIT0_AND_MASK)))
  {
    /* @Trace: Dcm_SUD_API_00983 */
    Restored = DCM_FALSE;

    if (pErrorCode != NULL_PTR)
    {
      /* @Trace: SWS_Dcm_01354 */
      /* @Trace: Dcm_SUD_API_00985 */
      *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  #else
  DCM_UNUSED(ServiceId);
  DCM_UNUSED(SubServiceId);
  DCM_UNUSED(pErrorCode);
  #endif

  return Restored;
}

/*******************************************************************************
** Function Name        : Dcm_StartInformSecurityAttemptCounters              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Inform the new security attempt counter value       **
**                        to the application                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StartInformSecurityAttemptCounters(void)
{
  /* @Trace: Dcm_SUD_API_01029 */
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  Dcm_SetSecurityAttemptCounters(DCM_INITIAL);

  if (DCM_TRUE == Dcm_IsSetSecurityAttemptCountersPending())
  {
    /* @Trace: Dcm_SUD_API_01031 */
    Dcm_StartTimerExt(
      DCM_WRITE_ATTEMPT_COUNTER_TIMER
      , DCM_MAX_ATTEMPT_COUNTER_WRITEOUT_TIME
      , Dcm_WaitInformSecurityAttemptCounters
      , Dcm_CancelInformSecurityAttemptCounters);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_WaitInformSecurityAttemptCounters               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pending function in case set new security           **
**                        attempt counter value to the application            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_WaitInformSecurityAttemptCounters(void)
{
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  if (DCM_TRUE == Dcm_IsSetSecurityAttemptCountersPending())
  {
    /* @Trace: Dcm_SUD_API_01039 */
    Dcm_SetSecurityAttemptCounters(DCM_PENDING);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01038 */
    Dcm_StopTimer(DCM_WRITE_ATTEMPT_COUNTER_TIMER);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_CancelInformSecurityAttemptCounters             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel function in case set new security            **
**                        attempt counter value to the application            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CancelInformSecurityAttemptCounters(void)
{
  /* @Trace: Dcm_SUD_API_00904 */
  #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
  if (DCM_TRUE == Dcm_IsSetSecurityAttemptCountersPending())
  {
    /* @Trace: Dcm_SUD_API_00903 */
    Dcm_SetSecurityAttemptCounters(DCM_CANCEL);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_InitSecurityLevelState                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize the value for the state of security level**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#ifdef SECURITY_SERVICE_ENABLED
static FUNC(void, DCM_CODE) Dcm_InitSecurityLevelState(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_00966 */
  uint8 LucIdx;
  Dcm_SetSecurityLevelIndex(DCM_ZERO);

  for (LucIdx = DCM_ZERO; LucIdx < DCM_NUM_OF_SECURITYLEVELCONFIG; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_00967 */
    Dcm_WriteAttCounter(LucIdx, DCM_ZERO);

    #ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
    Dcm_WriteGetAttPending(LucIdx, DCM_FALSE);
    Dcm_WriteSetAttPending(LucIdx, DCM_FALSE);
    #endif
  }

  DCM_UNUSED(pConfig);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_InitSecurityAttemptCounterControl               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize the value of security attempt counter    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
static FUNC(void, DCM_CODE) Dcm_InitSecurityAttemptCounterControl(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_00965 */
  Dcm_WriteGetAttPendingCount(DCM_ZERO);
  Dcm_WriteSetAttPendingCount(DCM_ZERO);

  DCM_UNUSED(pConfig);
}
#endif

/*******************************************************************************
** Function Name        : IsSecurityLevelIndexValid                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether the index of security configuration   **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#ifdef SECURITY_SERVICE_ENABLED
static FUNC(boolean, DCM_CODE) IsSecurityLevelIndexValid(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01055 */
  boolean retVal = DCM_FALSE;

  /* polyspace +1 RTE:UNR [Justify:Low] "The index value is always less than maximun configuration security level" */
  if (SecLvlIdx < DCM_NUM_OF_SECURITYLEVELCONFIG)
  {
    /* @Trace: Dcm_SUD_API_01054 */
    retVal = DCM_TRUE;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetSecurityAttemptCounters                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to get the security attempt counter   **
**                        for all security level                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounters(
  Dcm_OpStatusType OpStatus)
{
  uint8 LucIdx;

  Dcm_Internal_GetSecurityAttemptCounterFunType GetSecurityAttemptCounterFun[] = 
  {
    Dcm_GetSecurityAttemptCounterInitial
    , Dcm_GetSecurityAttemptCounterPending
    , Dcm_GetSecurityAttemptCounterCancel
  };

  for (LucIdx = DCM_ZERO; LucIdx < DCM_NUM_OF_SECURITYLEVELCONFIG; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_00937 */
    GetSecurityAttemptCounterFun[OpStatus](LucIdx);
  }

  /* @Trace: Dcm_SUD_API_00938 */
  Dcm_RestoreSecurityAttemptCountersDone();
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityAttemptCounterInitial                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security level attempt counter              **
**                        in case the operation status is DCM_INITIAL         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounterInitial(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00923 */
  Std_ReturnType LddRetVal;
  uint8 LucAttCounter = DCM_ZERO;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(SecLvlIdx);

  if ((NULL_PTR != LpSecLvlCfg) && 
      (DCM_TRUE == LpSecLvlCfg->blSecAttCounterEnable))
  {
    /* @Trace: Dcm_SUD_API_00924 */
    LddRetVal = LpSecLvlCfg->pGetSecurityAttemptCounterFun(
      DCM_INITIAL, &LucAttCounter);

    if (LddRetVal == DCM_E_PENDING)
    {
      /* @Trace: SWS_Dcm_01351 */
      /* @Trace: Dcm_SUD_API_00925 */
      Dcm_TriggerGetAttPending(SecLvlIdx);
    }
    else
    {
      /* @Trace: SWS_Dcm_01156 */
      /* @Trace: Dcm_SUD_API_00927 Dcm_SUD_API_00928 */
      Dcm_WriteAttCounter(
        SecLvlIdx,
        (LddRetVal == E_OK) ? LucAttCounter : LpSecLvlCfg->ucSecNumMaxAttDelay);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityAttemptCounterPending                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security level attempt counter              **
**                        in case the operation status is DCM_PENDING         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounterPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00929 */
  Std_ReturnType LddRetVal;
  uint8 LucAttCounter = DCM_ZERO;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  if (DCM_TRUE == Dcm_IsGetAttPending(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_00930 */
    LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(SecLvlIdx);

    if (NULL_PTR != LpSecLvlCfg)
    {
      /* @Trace: Dcm_SUD_API_00931 */
      LddRetVal = LpSecLvlCfg->pGetSecurityAttemptCounterFun(
        DCM_PENDING, &LucAttCounter);

      if (LddRetVal != DCM_E_PENDING)
      {
        /* Clear pending operation for specific security level */
        Dcm_ClearGetAttPending(SecLvlIdx);

        /* @Trace: Dcm_SUD_API_00935 Dcm_SUD_API_00936 */
        Dcm_WriteAttCounter(
          SecLvlIdx,
          (LddRetVal == E_OK) ? LucAttCounter : LpSecLvlCfg->ucSecNumMaxAttDelay);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityAttemptCounterCancel                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security level attempt counter              **
**                        in case the operation status is DCM_CANCEL          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_GetSecurityAttemptCounterCancel(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00920 */
  uint8 LucAttCounter = DCM_ZERO;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  if (DCM_TRUE == Dcm_IsGetAttPending(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_00919 */
    LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(SecLvlIdx);

    if (NULL_PTR != LpSecLvlCfg)
    {
      /* @Trace: Dcm_SUD_API_00922 */
      /* Do not check return value in case cancel */
      (void) LpSecLvlCfg->pGetSecurityAttemptCounterFun(
        DCM_CANCEL, &LucAttCounter);

      /* @Trace: SWS_Dcm_01353 */
      Dcm_ClearGetAttPending(SecLvlIdx);
      Dcm_WriteAttCounter(SecLvlIdx, LpSecLvlCfg->ucSecNumMaxAttDelay);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsGetSecurityAttemptCountersPending             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the restore operation is remain            **
**                        pending state or not                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsGetSecurityAttemptCountersPending(void)
{
  /* @Trace: Dcm_SUD_API_00973 */
  boolean LblRetVal = DCM_FALSE;

  if (DCM_ZERO != Dcm_ReadGetAttPendingCount())
  {
    /* @Trace: Dcm_SUD_API_00972 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_TriggerGetAttPending                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Trigger the pending state of get                    **
**                        the security attempt counter operation              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerGetAttPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01036 */
  Dcm_WriteGetAttPending(SecLvlIdx, DCM_TRUE);

  uint8 GetAttPendingCount = Dcm_ReadGetAttPendingCount();

  GetAttPendingCount++;
  Dcm_WriteGetAttPendingCount(GetAttPendingCount);
}

/*******************************************************************************
** Function Name        : Dcm_ClearGetAttPending                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear the pending state of get                      **
**                        the security attempt counter operation              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ClearGetAttPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00909 */
  Dcm_WriteGetAttPending(SecLvlIdx, DCM_FALSE);

  uint8 GetAttPendingCount = Dcm_ReadGetAttPendingCount();

  GetAttPendingCount--;
  Dcm_WriteGetAttPendingCount(GetAttPendingCount);
}

/*******************************************************************************
** Function Name        : Dcm_SetSecurityAttemptCounters                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to set the security attempt counter   **
**                        for all security level                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounters(
  Dcm_OpStatusType OpStatus)
{
  /* @Trace: Dcm_SUD_API_01025 */
  Dcm_Internal_SetSecurityAttemptCounterFunType SetSecurityAttemptCounterFun[] = 
  {
    Dcm_SetSecurityAttemptCounterInitial
    , Dcm_SetSecurityAttemptCounterPending
    , Dcm_SetSecurityAttemptCounterCancel
  };

  /* @Trace: SWS_Dcm_01155 */
  uint8 SecLvlIdx = Dcm_GetSecurityLevelIndex();
  SetSecurityAttemptCounterFun[OpStatus](SecLvlIdx);
}

/*******************************************************************************
** Function Name        : Dcm_SetSecurityAttemptCounterInitial                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the security level attempt counter              **
**                        in case the operation status is DCM_INITIAL         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounterInitial(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01015 */
  Std_ReturnType LddRetVal;
  uint8 LucAttCounter = DCM_ZERO;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(SecLvlIdx);

  if ((NULL_PTR != LpSecLvlCfg) && 
      (DCM_TRUE == LpSecLvlCfg->blSecAttCounterEnable))
  {
    /* @Trace: Dcm_SUD_API_01016 */
    LucAttCounter = Dcm_ReadAttCounter(SecLvlIdx);

    LddRetVal = LpSecLvlCfg->pSetSecurityAttemptCounterFun(
      DCM_INITIAL, LucAttCounter);

    if (LddRetVal == DCM_E_PENDING)
    {
      /* @Trace: Dcm_SUD_API_01017 */
      Dcm_TriggerSetAttPending(SecLvlIdx);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_SetSecurityAttemptCounterPending                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pending process function of set new security        **
**                        attempt counter value to the application            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounterPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01019 */
  Std_ReturnType LddRetVal;
  uint8 LucAttCounter = DCM_ZERO;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  if (DCM_TRUE == Dcm_IsSetAttPending(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_01020 */
    LucAttCounter = Dcm_ReadAttCounter(SecLvlIdx);
    LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(SecLvlIdx);

    if (NULL_PTR != LpSecLvlCfg)
    {
      /* @Trace: Dcm_SUD_API_01021 */
      LddRetVal = LpSecLvlCfg->pSetSecurityAttemptCounterFun(
        DCM_PENDING, LucAttCounter);

      if (LddRetVal != DCM_E_PENDING)
      {
        /* @Trace: Dcm_SUD_API_01024 */
        Dcm_ClearSetAttPending(SecLvlIdx);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_SetSecurityAttemptCounterCancel                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel process function of set new security         **
**                        attempt counter value to the application            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounterCancel(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01012 */
  uint8 LucAttCounter = DCM_ZERO;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  if (DCM_TRUE == Dcm_IsSetAttPending(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_50902 */
    LucAttCounter = Dcm_ReadAttCounter(SecLvlIdx);
    LpSecLvlCfg = Dcm_GetSecurityLevelConfigByIndex(SecLvlIdx);

    if (NULL_PTR != LpSecLvlCfg)
    {
      /* @Trace: Dcm_SUD_API_01013 */
      (void) LpSecLvlCfg->pSetSecurityAttemptCounterFun(DCM_CANCEL, LucAttCounter);

      Dcm_ClearSetAttPending(SecLvlIdx);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsSetSecurityAttemptCountersPending             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the set operation is remain                **
**                        pending state or not                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsSetSecurityAttemptCountersPending(void)
{
  /* @Trace: Dcm_SUD_API_00993 */
  boolean LblRetVal = DCM_FALSE;

  if (DCM_ZERO != Dcm_ReadSetAttPendingCount())
  {
    /* @Trace: Dcm_SUD_API_00992 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_TriggerSetAttPending                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Trigger the pending state of set                    **
**                        the security attempt counter operation              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerSetAttPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_01035 */
  Dcm_WriteSetAttPending(SecLvlIdx, DCM_TRUE);

  uint8 SetAttPendingCount = Dcm_ReadSetAttPendingCount();

  SetAttPendingCount++;
  Dcm_WriteSetAttPendingCount(SetAttPendingCount);
}

/*******************************************************************************
** Function Name        : Dcm_ClearSetAttPending                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear the pending state of set                      **
**                        the security attempt counter operation              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ClearSetAttPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00910 */
  Dcm_WriteSetAttPending(SecLvlIdx, DCM_FALSE);

  uint8 SetAttPendingCount = Dcm_ReadSetAttPendingCount();

  SetAttPendingCount--;
  Dcm_WriteSetAttPendingCount(SetAttPendingCount);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ReadAttCounter                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the security attempt counter value              **
**                        by index of the security level configuration        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#ifdef SECURITY_SERVICE_ENABLED
static FUNC(uint8, DCM_CODE) Dcm_ReadAttCounter(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00995 */
  uint8 AttCounter = DCM_ZERO;

  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_00994 */
    AttCounter = Dcm_GaaSecLevState[SecLvlIdx].ucAttCounter;
  }

  return AttCounter;
}

/*******************************************************************************
** Function Name        : Dcm_WriteAttCounter                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the security attempt counter value              **
**                        by index of the security level configuration        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx, AttCounter                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_WriteAttCounter(
  uint8 SecLvlIdx, 
  uint8 AttCounter)
{
  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_01044 */
    Dcm_GaaSecLevState[SecLvlIdx].ucAttCounter = AttCounter;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01045 */
    /* Do nothing in this case */
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsGetAttPending                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the pending state of the get security         **
**                        attempt counter by index of security configuration  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
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
#ifdef SECURITY_ATTEMPT_COUNTER_ENABLED
static FUNC(boolean, DCM_CODE) Dcm_IsGetAttPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00971 */
  boolean GetAttPending = DCM_FALSE;

  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_00970 */
    GetAttPending = Dcm_GaaSecLevState[SecLvlIdx].blGetAttPending;
  }

  return GetAttPending;
}

/*******************************************************************************
** Function Name        : Dcm_WriteGetAttPending                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the pending state of get attempt counter        **
**                        operation by index of security configuration        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx, GetAttPending                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_WriteGetAttPending(
  uint8 SecLvlIdx, 
  boolean GetAttPending)
{
  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_01046 */
    Dcm_GaaSecLevState[SecLvlIdx].blGetAttPending = GetAttPending;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01047 */
    /* Do nothing in this case */
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsSetAttPending                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the pending state of the set security         **
**                        attempt counter by index of security configuration  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx                                           **
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
static FUNC(boolean, DCM_CODE) Dcm_IsSetAttPending(
  uint8 SecLvlIdx)
{
  /* @Trace: Dcm_SUD_API_00991 */
  boolean SetAttPending = DCM_FALSE;

  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_00990 */
    SetAttPending = Dcm_GaaSecLevState[SecLvlIdx].blSetAttPending;
  }

  return SetAttPending;
}

/*******************************************************************************
** Function Name        : Dcm_WriteSetAttPending                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the pending state of set attempt counter        **
**                        operation by index of security configuration        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SecLvlIdx, SetAttPending                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_WriteSetAttPending(
  uint8 SecLvlIdx, 
  boolean SetAttPending)
{
  if (DCM_TRUE == IsSecurityLevelIndexValid(SecLvlIdx))
  {
    /* @Trace: Dcm_SUD_API_01049 */
    Dcm_GaaSecLevState[SecLvlIdx].blSetAttPending = SetAttPending;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01050 */
    /* Do nothing in this case */
  }
}

/*******************************************************************************
** Function Name        : Dcm_ReadGetAttPendingCount                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the number pending state of get security        **
**                        attempt counter operation                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_ReadGetAttPendingCount(void)
{
  /* @Trace: Dcm_SUD_API_00996 */
  return Dcm_GddAttCounterControl.ucGetAttPendingCount;
}

/*******************************************************************************
** Function Name        : Dcm_WriteGetAttPendingCount                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the number pending state of get security        **
**                        attempt counter operation                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : GetAttPendingCount                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_WriteGetAttPendingCount(
  uint8 GetAttPendingCount)
{
  /* @Trace: Dcm_SUD_API_01048 */
  Dcm_GddAttCounterControl.ucGetAttPendingCount = GetAttPendingCount;
}

/*******************************************************************************
** Function Name        : Dcm_ReadSetAttPendingCount                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the number pending state of set security        **
**                        attempt counter operation                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_ReadSetAttPendingCount(void)
{
  /* @Trace: Dcm_SUD_API_00997 */
  return Dcm_GddAttCounterControl.ucSetAttPendingCount;
}

/*******************************************************************************
** Function Name        : Dcm_WriteSetAttPendingCount                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the number pending state of set security        **
**                        attempt counter operation                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SetAttPendingCount                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_WriteSetAttPendingCount(
  uint8 SetAttPendingCount)
{
  /* @Trace: Dcm_SUD_API_01051 */
  Dcm_GddAttCounterControl.ucSetAttPendingCount = SetAttPendingCount;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
