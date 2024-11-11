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
**  SRC-MODULE: Dcm_ActiveDiag.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Manage ComM active diagnostic state                           **
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
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.3     04-Dec-2020   LanhLT         Polyspace fixing as per #15175      **
** 0.0.4     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_ComM.h"
#include "ComM_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_ActiveDiag.h"

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
typedef enum
{
  DCM_COMM_ACTIVE
  , DCM_COMM_NOT_ACTIVE
} Dcm_ActiveDiagnosticStateType;

typedef P2FUNC(void, DCM_CODE, Dcm_TriggerEventActiveDiagnosticFunType)(void);

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static Dcm_ActiveDiagnosticStateType ActiveDiagnosticState;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Static Functions Declaration                          **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) Dcm_TriggerEventSessionChange(void);

static FUNC(void, DCM_CODE) Dcm_TriggerEventReceiveRequest(void);

static FUNC(void, DCM_CODE) Dcm_TriggerEventFinishRequest(void);

static FUNC(void, DCM_CODE) Dcm_TriggerEvent_ActiveDiagnostic(void);

static FUNC(void, DCM_CODE) Dcm_TriggerEvent_InActiveDiagnostic(void);

static FUNC(boolean, DCM_CODE) Dcm_IsActiveDiagnostic(void);

/*******************************************************************************
** Function Name        : Dcm_InitActiveDiagnostic                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function initialize Active Diagnostic feature       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_SetActiveDiagnostic        **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01069 */
FUNC(void, DCM_CODE) Dcm_InitActiveDiagnostic(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_30426 */
  (void) Dcm_SetActiveDiagnostic(DCM_TRUE);

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_IsActiveDiagnostic                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check status of ActiveDiagnostic           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : ActiveDiagnosticState          **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsActiveDiagnostic(void)
{
  /* @Trace: Dcm_SUD_API_30427 */
  boolean retVal = DCM_FALSE;

  if (ActiveDiagnosticState == DCM_COMM_ACTIVE)
  {
    /* @Trace: Dcm_SUD_API_30428 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_TriggerEventActivationDiagnostic                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check event to trigger corresponding       **
**                        ActiveDiagnostic  state                             **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Event                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_TriggerEventSessionChange         **
**                                      Dcm_TriggerEvent_ActiveDiagnostic     **
**                                      Dcm_TriggerEvent_InActiveDiagnostic   **
**                                      Dcm_TriggerEventFinishRequest         **
**                                      Dcm_TriggerEventReceiveRequest        **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_TriggerEventActivationDiagnostic(
  Dcm_ActiveDiagnosticTriggerEventType LucEvent)
{
  if (LucEvent < AD_TE_MAX_NUM)
  {
    /* @Trace: Dcm_SUD_API_30431 */
    Dcm_TriggerEventActiveDiagnosticFunType DispatchTable[AD_TE_MAX_NUM] =
    {
      Dcm_TriggerEventSessionChange
      , Dcm_TriggerEvent_ActiveDiagnostic
      , Dcm_TriggerEvent_InActiveDiagnostic
      , Dcm_TriggerEventReceiveRequest
      , Dcm_TriggerEventFinishRequest
      , Dcm_TriggerEvent_InActiveDiagnostic
    };

    DispatchTable[LucEvent]();
  }
}

/*******************************************************************************
** Function Name        : Dcm_TriggerEventReceiveRequest                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to trigger ActiveDiagnostic                **
**                        when Dcm receive  request                           **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GddCurrentSession         **
**                                                                            **
**                        Function(s) : Dcm_TriggerEvent_ActiveDiagnostic     **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerEventReceiveRequest(void)
{
  /* @Trace: Dcm_SUD_API_30447 */
  if (CHECK_DEFAULT_SESSION(Dcm_GddCurrentSession))
  {
    /* @Trace: Dcm_SUD_API_30433 */
    Dcm_TriggerEvent_ActiveDiagnostic();
  }
}

/*******************************************************************************
** Function Name        : Dcm_TriggerEventFinishRequest                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to trigger ActiveDiagnostic                **
**                        when Dcm finish request processing                  **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GddCurrentSession         **
**                                                                            **
**                        Function(s) : Dcm_TriggerEvent_InActiveDiagnostic   **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerEventFinishRequest(void)
{
  /* @Trace: Dcm_SUD_API_30446 */
  if (CHECK_DEFAULT_SESSION(Dcm_GddCurrentSession))
  {
    /* @Trace: Dcm_SUD_API_30432 */
    Dcm_TriggerEvent_InActiveDiagnostic();
  }
}

/*******************************************************************************
** Function Name        : Dcm_TriggerEvent_ActiveDiagnostic                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to trigger ComM ActiveDiagnostic           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GulChannelIdentifier      **
**                                                                            **
**                        Function(s) : ComM_DCM_ActiveDiagnostic             **
**                                       Dcm_IsActiveDiagnostic               **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01376 */
static FUNC(void, DCM_CODE) Dcm_TriggerEvent_ActiveDiagnostic(void)
{
  if (DCM_TRUE == Dcm_IsActiveDiagnostic())
  {
    /* @Trace: Dcm_SUD_API_30436 */
    ComM_DCM_ActiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
  }
}

/*******************************************************************************
** Function Name        : Dcm_TriggerEvent_InActiveDiagnostic                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to trigger ComM InActiveDiagnostic         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GulChannelIdentifier      **
**                                                                            **
**                        Function(s) : ComM_DCM_InactiveDiagnostic           **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerEvent_InActiveDiagnostic(void)
{
  /* @Trace: Dcm_SUD_API_30437 */
  ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
}

/*******************************************************************************
** Function Name        : Dcm_TriggerEventSessionChange                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to trigger ActiveDiagnostic                **
**                        when Dcm session changed                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GddOldSession             **
**                                              Dcm_GulChannelIdentifier      **
**                                                                            **
**                        Function(s) : Dcm_TriggerEvent_ActiveDiagnostic     **
**                                      ComM_DCM_InactiveDiagnostic           **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerEventSessionChange(void)
{
  if (CHECK_DEFAULT_SESSION(Dcm_GddOldSession))
  {
    /* Switch from default session to non-default session */
    if (CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
    {
      /* this code for FBL */
      /* Update with default value 5ms */
      Dcm_GstCurrentTimingValue.Timer_S3Server = DCM_TIMSTR_S3_SERVER; 

      /* @Trace: Dcm_SUD_API_30434 */
      Dcm_TriggerEvent_ActiveDiagnostic();
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30448 */
    /* Switch from non-default session to default session */
    if (CHECK_DEFAULT_SESSION(Dcm_GddCurrentSession))
    {
      /* @Trace: SWS_Dcm_01377 */
      /* @Trace: Dcm_SUD_API_30435 */
      (void) ComM_DCM_InactiveDiagnostic((NetworkHandleType) Dcm_GulChannelIdentifier);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_SetActiveDiagnostic                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to set statust of ActiveDiagnostic         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : active.                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  ActiveDiagnosticState         **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01070 SWS_Dcm_01071 SWS_Dcm_01068 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetActiveDiagnostic(boolean active)
{
  /* @Trace: Dcm_SUD_API_30430 Dcm_SUD_API_30444 */
  ActiveDiagnosticState = (DCM_TRUE == active) ? DCM_COMM_ACTIVE : DCM_COMM_NOT_ACTIVE;
  return E_OK;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
