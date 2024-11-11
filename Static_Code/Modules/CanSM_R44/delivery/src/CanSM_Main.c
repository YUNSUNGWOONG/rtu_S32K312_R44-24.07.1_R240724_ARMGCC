/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
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
**  SRC-MODULE: CanSM_Main.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of the functionality of CanSM_MainFunction()        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By             Description                       **
********************************************************************************
** 1.0.9_HF1   23-Feb-2024   MU Kim         CP44-2851, CP44-3367              **
** 1.0.9       07-Jun-2023   HieuTM8        #CP44-2208, #CP44-2207            **
** 1.0.8       02-Mar-2023   HieuTM8        #CP44-1771                        **
** 1.0.6       12-Dec-2022   HieuTM8        #CP44-1312                        **
** 1.0.4       10-Oct-2022   HieuTM8        CP44-876                          **
** 1.0.3       01-Aug-2022   HieuTM8        CP44-511, CP44-680                **
** 1.0.2       24-Mar-2022   HieuTM8        R44-Redmine #25572,#25635         **
** 1.0.1       14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306         **
** 1.0.0       04-Dec-2020   SMKwon         Initial Version                   **
********************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "BswM.h"                 /* BswM header file */
#include "CanSM.h"
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanIf.h"                /* CanIf header file */
#include "CanSM_Internal.h"       /* CanSM Main header file */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#include "CanSM_CanIf.h"
#endif  
#include "ComM.h"                 /* ComM header file */
#include "BswM_CanSM.h"           /* BswM_CanSM header file */
#if(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY)
#include CANSM_GET_BUS_OFF_DELAY_HEADER           /* BswM_CanSM header file */
#endif
#if(STD_ON == CANSM_DEM_STATUS)
#include "Dem.h"
#endif

#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_MAIN_C_RELEASE_MAJOR_VERSION       0x04u
#define CANSM_MAIN_C_RELEASE_MINOR_VERSION       0x04u
#define CANSM_MAIN_C_RELEASE_REVISION_VERSION    0x00u

/* CANSM software version information */
#define CANSM_MAIN_C_SW_MAJOR_VERSION            0x01u
#define CANSM_MAIN_C_SW_MINOR_VERSION            0x00u



/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_MAIN_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_MAIN_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_MAIN_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_MAIN_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_MAIN_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Array of function pointer to handle main function switch */
#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"/* Memmap header file */
CONST(CanSM_TransFuncPtrType, CANSM_CONST) CanSM_TransFuncPtr[] =
{
  {
    &CanSM_NoCommunication
  },
  {
    &CanSM_SilentCommunication
  },
  {
    &CanSM_FullCommunication
  },
  {
    &CanSM_BORStart
  },
  {
    &CanSM_BORWait
  },
  {
    &CanSM_CheckBusOff
  },
  {
    &CanSM_NoToFullCommRequested
  },
  {
    &CanSM_SilentToFullCommRequested
  },
  {
    &CanSM_FullToSilentCommRequested
  },

  {
    &CanSM_SilentCommunication_BOR
  },
  #if (STD_ON == CANSM_SET_BAUDRATE_API)
  {
    &CanSM_SetBaudrateService
  },
  {
    &CanSM_ChangeBaudrateEndFullCom
  },
  {
    &CanSM_ChangeBaudrateEndSilentCom
  },
  #else
  {
    NULL_PTR
  },
  {
    NULL_PTR
  },
  {
    NULL_PTR
  },
  #endif
  {
    &CanSM_WakeUpValidation
  },
  {
    &CanSM_WakeUpToFullComRequested
  },
  {
    &CanSM_DeInitPnNotSupported
  },
  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  {
    &CanSM_DeInitPnSupported
  },
  {
    &CanSM_TxTimeoutException
  }
  #endif
};
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"/* Memmap header file */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanSM_MainFunction                                  **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service executes the bus-off recovery          **
**                        state machines of each network handle, which        **
**                        is configured for the CanSM.                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_InitStatus              **
**                        Function(s) invoked :                               **
**                                             CanSM_NoCommunication          **
**                                             CanSM_DeInitPnNotSupported     **
**                                             CanSM_DeInitPnSupported        **
**                                             CanSM_FullCommunication        **
**                                             CanSM_BORWait                  **
**                                             CanSM_BORStart                 **
**                                             CanSM_CheckBusOff              **
**                                             CanSM_NoToFullCommRequested    **
**                                             CanSM_SilentToFullCommRequested**
**                                             CanSM_FullToSilentCommRequested**
**                                             CanSM_SilentCommunication      **
**                                             CanSM_WakeUpValidation         **
**                                             CanSM_WakeUpToFullComRequested **
**                                             CanSM_TxTimeoutException       **
**                                             CanSM_SetBaudrateService        **
**                                             CanSM_ChangeBaudrateEndFullCom  **
**                                             CanSM_ChangeBaudrateEndSilentCom**
*******************************************************************************/
/* @Trace: SRS_BSW_00425 SRS_BSW_00424 SRS_Can_01145 SRS_Can_01142 */
/* @Trace: CanSM_SUD_API_056 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_MainFunction(void)
{


  if((CanSM_StateType)CANSM_INITED == CanSM_InitStatus)
  {
    VAR(NetworkHandleType,CANSM_VAR) canSmNwIndex;

    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    /* get total number of CanSM network */
    canSmNwIndex = (NetworkHandleType)CanSM_NWPerCfg;
    #else
    /* get total number of CanSM network */
    canSmNwIndex= (NetworkHandleType)CANSM_NUMBER_OF_STATIC_NWS;
    #endif

    /* Loop for all the networks */

    do
    {
      /* @Trace: CanSM_SUD_API_057 */
      /* Decrement the network index */
      --canSmNwIndex;

      /* Process the current CanSM request */
      /* polyspace:begin<RTE: COR : Not a defect : No Action Planned > configured memory access index */
      /* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > Its boundary is pre-defined */
      (CanSM_TransFuncPtr[CanSM_Network[canSmNwIndex].ModeStatus].pTransFuncPtr)(canSmNwIndex);
      /* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > Its boundary is pre-defined */
      /* polyspace:end<RTE: COR : Not a defect : No Action Planned > configured memory access index */
    } while ((NetworkHandleType)CANSM_ZERO != canSmNwIndex);
    /* Process the current CanSM request */

  }/* @ The end of ((CanSM_StateType)CANSM_UNINITED == CanSM_InitStatus) */


} /* End of CanSM_MainFunction(void) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_BORStart                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts the bus of recovery procedure  **
**                        on bus off Occurence.                               **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 SRS_BSW_00422 SRS_Can_01144 SRS_Can_01146 SRS_BSW_00466 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_BORStart(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean,CANSM_VAR) pnSupported;
  #endif

  VAR(Std_ReturnType, CANSM_VAR) result;
  /* initialize result as CANSM_E_WAITSATE */
  result = (uint8)CANSM_E_WAITSTATE;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* @Trace: CanSM_SUD_API_172 */
  if ((uint8)COMM_NO_COMMUNICATION == ptrNetwork->ReqModeStatus)
  {
    /* Update Internal Substate as Zero*/
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* Update Internal Timer as Zero*/
    ptrNetwork->Timer = (CanSM_TimerType)CANSM_ZERO;

    /* Update Internal BusOffCounter as Zero*/
    ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

    /* Notify the network mode to the BswM */
    /* @Trace: CanSM_SUD_API_173 */
    BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle, (CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);
    
    /*Enter protection area*/
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    #if (STD_ON == CANSM_PNC_AVAILABILITY)
    pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;

    /* Check if Partial Networking is Available */
    if ((boolean)CANSM_TRUE == pnSupported)
    {
      /* Set Mode status to CANSM_DEINITPNSUPPORTED  */
      /* @Trace: CanSM_SUD_API_175 */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;
    }
    else
    {
      /* Update the Mode status to CANSM_DEINITNOTSUPPORT */
      /* @Trace: CanSM_SUD_API_174 */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
    }
    #else /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */

    /* Update the Mode status to CANSM_DEINITNOTSUPPORT */
    /* @Trace: CanSM_SUD_API_197 */
    ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
    #endif /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */
        
    /*Exit protection area*/
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }
  else
  {
	  /* @Trace: CanSM_SUD_API_191 */
    if ((uint8)CANSM_FULL_T_BUSOFF == ptrNetwork->CanSMNWIntSubState)
    {
      CanSM_BORStart_FULL_T_BUSOFF(networkHandle);
    } /* End of if (CANSM_FULL_T_BUSOFF == ptrNetwork->CanSMNWIntSubState) */

    /* Check if the Internal subsate is CANSM_FULL_RESTART_CC */
    /* @Trace: CanSM_SUD_API_179 */
    if ((uint8)CANSM_FULL_RESTART_CC == ptrNetwork->CanSMNWIntSubState)
    {
      /* set controller mode to CAN_CS_STARTED */
      ptrNetwork->Mode = (uint8)CAN_CS_STARTED;

      /* Set the controller mode as CAN_CS_STARTED */
      result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STARTED);
    }
    /* Check if the Internal subsate is CANSM_FULL_TX_OFF */
    /* @Trace: CanSM_SUD_API_184 */
    if ((uint8)CANSM_FULL_TX_OFF == ptrNetwork->CanSMNWIntSubState)
    {
      CanSM_BORStart_FULL_TX_OFF(networkHandle);
    } /* End of if (CANSM_FULL_TX_OFF == ptrNetwork->CanSMNWIntSubState) */
    /* Note: guarding condition G_RESTART_CC_OK is passed */
    if ((Std_ReturnType)E_OK == result)
    {
      /* load the Request Time into local variable */
      ptrNetwork->CanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_ModeReqRepeatTime;
    }
    /* Note: T_RESTART_CC_TIMEOUT is triggered */
    else
    {
      /* Call the TimeOut Processing Function */
      /* @Trace: CanSM_SUD_API_183 */
      CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
    }
  }
} /* End of CanSM_BORStart(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */


#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_BORWait                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function waits the bus of recovery timer to    **
**                        elapse for bus off recovery                         **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_StaticNw                **
**                        Function(s) invoked :
**                                 SchM_Enter_CanSM_MODE_STATUS_PROTECTION()  **
**                                 SchM_Exit_CanSM_MODE_STATUS_PROTECTION()   **
**                                 BswM_CanSM_CurrentState()                  **
**                                 ComM_BusSM_ModeIndication()                **
*******************************************************************************/
/* @Trace: SRS_Can_01158 SRS_Can_01145 SRS_Can_01142 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_BORWait(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;
  VAR(Std_ReturnType, CANSM_VAR) result;


  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];
  /* Fixed Bug #1962 */
  if ((CanSM_TimerType)CANSM_ZERO != ptrNetwork->Timer)
  {
    /* Decrement the timer */
    (ptrNetwork->Timer)--;
  }
  /* Exit BOR wait if timer becomes ZERO */
  if ((CanSM_TimerType)CANSM_ZERO == ptrNetwork->Timer)
  {
    result = (Std_ReturnType)E_OK;
    /* Note: Set Pdu Mode When ECUPassive is false */
    if((CanSM_ECUPassiveType)CANSM_ECU_NOT_PASSIVE == CanSM_ECUPassive)
    {
      /* Set the Pdu mode to online */
      /* @Trace: CanSM_SUD_API_186 */
      /* polyspace +8 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
      CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex, CANIF_ONLINE);
    }
    /* Note: Set Pdu Mode When ECUPassive is true */
    else
    {
      /*Set the Pdu mode to offline active*/
      /* @Trace: CanSM_SUD_API_187 */
      CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_TX_OFFLINE_ACTIVE);
    }
    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
    if (ptrNetwork->ModeStatus != CANSM_BORSTART)
    {
      if ((Std_ReturnType)E_OK == result)
      {
        /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
        ptrNetwork->ModeStatus = (uint8)CANSM_CHECKBUSOFF;

        /* Load TX_ENSURED Timer  to network timer */
        ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIME_TXENSURED;
        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION(); 
        /* Notify the current network mode to the BsWM */
        /* @Trace: CanSM_SUD_API_188 */
        BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_FULL_COMMUNICATION);

        /* Set the current mode of the network */
        /* @Trace: CanSM_SUD_API_189 */
        currentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

        /* Notify the current network mode to the ComM*/
        ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle, currentState);
      }
      else /* @ (Std_ReturnType)E_OK == result) */
      {
        /* Load timer with CANSM_ONE */
        ptrNetwork->Timer = (CanSM_TimerType)CANSM_ONE;
        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();  
      }
    }
    else /* (ptrNetwork->ModeStatus != CANSM_BORSTART) */
    {
      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    }
  } /* @ End of if ((CanSM_TimerType)CANSM_ZERO == ptrNetwork->Timer) */
} /* End of CanSM_BORWait(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */


#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_CheckBusOff                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function check the end of bus of recovery      **
**                        procedure and any new bus off Occurence             **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked :                               **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
**                                Dem_SetEventStatus()                        **
**                                CanSM_GetTxConfirmationState()              **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 SRS_BSW_00422 SRS_BSW_00466 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_CheckBusOff(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  #if(STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean,CANSM_VAR) pnSupported;
  #endif
  CanSM_TimerType BORTimerTxEnsured;

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* if Requested communication mode is no communication mode  */
  if ((uint8)COMM_NO_COMMUNICATION == ptrNetwork->ReqModeStatus)
  {
    /* @Trace: CanSM_SUD_API_192 */
    /* Update Internal Substate as Zero*/
    ptrNetwork->CanSMNWIntSubState = CANSM_ZERO;

    /* Update Internal Timer as Zero*/
    ptrNetwork->Timer = (CanSM_TimerType)CANSM_ZERO;

    /* Update Internal BusOffCounter as Zero*/
    ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

    /* Notify the network mode to the BswM */
    BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,
      (CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);
    
    /* Enter Protection Area */
    SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();
    #if(STD_ON == CANSM_PNC_AVAILABILITY)
    /* Update the local variable with Pnsupported value from Structure*/
    pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;

    /* Check if PN is supported */
    if ((boolean)CANSM_TRUE == pnSupported)
    {
      /* Update the Mode status as DeInitPnSupported */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;
    }
    else
    {
      /* Update the Mode status as DeInitPnSupported */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
    }
    #else
    /* Update the Mode status as DeInitPnSupported */
    ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
    #endif
    /* Exit Protection Area */
    SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
  }
  else
  {
    /* Load the TX ENSURED timer to local variable */
    BORTimerTxEnsured = ptrNetwork->Timer;
  
    /* Fixed Bug #1962 */
    if ((CanSM_TimerType)CANSM_ZERO != BORTimerTxEnsured)
    {
      /* Decrement the timer */
      --BORTimerTxEnsured;
    }

    /* Load the timer back from local variable */
    ptrNetwork->Timer = (CanSM_TimerType)BORTimerTxEnsured;


    #if((STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)&&(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT))
    if(CANSM_TRUE == CanSM_NwTxConfirmationPolling[CANSM_NETWORKHANDLE].CanSMBorTxConfirmationPolling)
    {
      /* Call CanSM_GetTxConfirmationState function  */
      if ((CanIf_NotifStatusType)CANIF_TX_RX_NOTIFICATION == CanSM_GetTxConfirmationState(CANSM_NETWORKHANDLE))
      {
         /* Enter the effect E_BUS_OFF_PASSIVE mode */
         CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
      }
      else
      {
        /* check whether TxEnsured counter is ZERO */
        if ((CanSM_TimerType)CANSM_ZERO == BORTimerTxEnsured)
        {
          /* Enter the effect E_BUS_OFF_PASSIVE mode */
          CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
        }
      }
    }
    else
    {
      /* check whether TxEnsured counter is ZERO */
      if ((CanSM_TimerType)CANSM_ZERO == BORTimerTxEnsured)
      {
         /* Enter the effect E_BUS_OFF_PASSIVE mode */
         CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
      }
    }
    #endif /* end of (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)&&(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT) */
    /* @Trace: CanSM_SUD_API_193 CanSM_SUD_API_194 */
    #if((STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)&&(STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT))
    if((boolean)CANSM_TRUE == ptrStaticNetwork->CanSMTxConfirmationPolling)
    {
      /* Call CanSM_GetTxConfirmationState function  */
      if ((CanIf_NotifStatusType)CANIF_TX_RX_NOTIFICATION == CanSM_GetTxConfirmationState(CANSM_NETWORKHANDLE))
      {
        /* Enter the effect E_BUS_OFF_PASSIVE mode */
        CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
      }
      else
      {
        /* check whether TxEnsured counter is ZERO */
        if ((CanSM_TimerType)CANSM_ZERO == BORTimerTxEnsured)
        {
          /* Enter the effect E_BUS_OFF_PASSIVE mode */
          CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
        }
      }
    }
    else
    {
      /* check whether TxEnsured counter is ZERO */
      if ((CanSM_TimerType)CANSM_ZERO == BORTimerTxEnsured)
      {
        /* Enter the effect E_BUS_OFF_PASSIVE mode */
        CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
      }
    }
    #endif /* end of (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)&&(STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT) */
    #if(STD_OFF == CANSM_BOR_TX_CONFIRMATION_POLLING)
    if ((CanSM_TimerType)CANSM_ZERO == BORTimerTxEnsured)
    {
        /* Enter the effect E_BUS_OFF_PASSIVE mode */
        CanSM_EBusOffPassive(CANSM_NETWORKHANDLE);
    }
    #endif /*End of (STD_OFF == CANSM_BOR_TX_CONFIRMATION_POLLING) */
  }
} /* End of CanSM_CheckBusOff(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_FullCommunication                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function indicates Full Communication          **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_StaticNw                **
**                        Function(s) invoked :                               **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
**                                CanSM_FullToSilentCommRequested             **
**                                CanSM_DeInitPnSupported                     **
**                                CanSM_DeInitPnNotSupported                  **
**
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_FullCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean,CANSM_VAR) pnSupported;
  #endif


  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Check if request Mode is not equal to Full Communication */
  if ((uint8)COMM_FULL_COMMUNICATION != ptrNetwork->ReqModeStatus)
  {
    /* Update Internal Substate as Zero*/
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* reset requested repeat time */
    ptrNetwork->CanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /* Check if request Mode is equal to No Communication */
    if ((uint8)COMM_SILENT_COMMUNICATION == ptrNetwork->ReqModeStatus)
    {
      /* Enter protection status */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
      /* Check if Mode is equal to Silent*/
      /* @Trace: CanSM_SUD_API_185 */
      ptrNetwork->ModeStatus = (uint8)CANSM_FULLTOSILENTCOMMREQUESTED;
      
      /* Enter protection status */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* Call the SilentComRequested function */
      CanSM_FullToSilentCommRequested(CANSM_NETWORKHANDLE);
    }
    else
    {
      /* Notify the network mode to the BswM */
      /* @Trace: CanSM_SUD_API_202 */
      BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,
        (CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);


      #if (STD_ON == CANSM_PNC_AVAILABILITY)

      /* Update the local variable with Pnsupported value from Structure*/
      pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;

      /* Check if PN is supported */
      if ((boolean)CANSM_TRUE == pnSupported)
      {
        /* Enter protection status */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Update mode status as CANSM_DEINITPNSUPPORTED */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;
        /* Enter protection status */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

        /* Initiate Partial Networking */
        CanSM_DeInitPnSupported(CANSM_NETWORKHANDLE);
      }
      else
      {
        /* Enter protection status */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* update mode status as CANSM_DEINITPNNOTSUPPORTED */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;

        /* Enter protection status */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

        /* Call PN not supported function */
        CanSM_DeInitPnNotSupported(CANSM_NETWORKHANDLE);
      }
      #else /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */
      /* Enter protection status */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Update mode status as CANSM_DEINITPNNOTSUPPORTED */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;

      /* Enter protection status */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      /* Call PN not supported function */
      CanSM_DeInitPnNotSupported(CANSM_NETWORKHANDLE);
      #endif /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */
    } /* End of else */
  } /* End of if ((uint8)COMM_FULL_COMMUNICATION != ptrNetwork->ReqModeStatus)
     **/
} /* End of CanSM_FullCommunication(NetworkHandleType */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > 
                                        Its boundary is pre-defined           */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_GetTxConfirmationState                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine checks the Occurence of bus off        **
**                        in case of POLLING.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                             CanIf_GetTxConfirmationState() **
*******************************************************************************/

#if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(CanIf_NotifStatusType, CANSM_CODE) CanSM_GetTxConfirmationState(
  VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  VAR(CanIf_NotifStatusType,CANSM_VAR) retVal;
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;

  
  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
  /* polyspace +2 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
  /* Get Tx Confirmation State of all controllers in designated network */
  CANIF_GETTXCONFIRMATIONSTATE(ptrStaticNetwork->ControllerIndex);



  return (retVal);
} /* End of CanSM_GetTxConfirmationState(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING ) */


/*******************************************************************************
** Function Name        : CanSM_DeInitPnNotSupported                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine handles the De initialization          **
**                        process for partial netowrk                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_Network             **
**                                                                            **
**                        Function(s) invoked   : CanIf_SetControllerMode()   **
**                                                CanIf_SetTransceiverMode()  **
**                                                BswM_CanSM_CurrentState()   **
**                                                ComM_BusSM_ModeIndication() **
**                                                CanIf_ClearTrcvWufFlag()    **
**                                                CanIf_CheckTrcvWakeFlag()   **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_DeInitPnNotSupported(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* initialize result as CANSM_E_WAITSTATE */
  result = (uint8)CANSM_E_WAITSTATE;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Check the Internal Substate as CANSM_WOPN_CS_STOPPED */
  if ((uint8)CANSM_WOPN_CS_STOPPED == ptrNetwork->CanSMNWIntSubState)
  {
	  /* @Trace: CanSM_SUD_API_129 */
    ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
    /* Set the controller mode as CAN_CS_STOPPED */
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STOPPED);

  }

  /* Check the Internal Substate as CANSM_WOPN_CS_SLEEP */
  if ((uint8)CANSM_WOPN_CS_SLEEP == ptrNetwork->CanSMNWIntSubState)
  {
	  /* @Trace: CanSM_SUD_API_130 */
    ptrNetwork->Mode = (uint8)CAN_CS_SLEEP;
    /* Set the controller mode as CAN_CS_SLEEP */
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_SLEEP);

  }


  /* Check the Internal Substate as CANSM_WOPN_TRCV_MODE_NORMAL */
  if ((uint8)CANSM_WOPN_TRCV_MODE_NORMAL == ptrNetwork->CanSMNWIntSubState)
  {
	  /* @Trace: CanSM_SUD_API_131 */
    ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    /* Set the Transceiver mode as CANTRCV_TRCVMODE_NORMAL */
    result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE, CANTRCV_TRCVMODE_NORMAL);

  }
  /* Check the Internal Substate as CANSM_WOPN_TRCV_MODE_STANDBY */
  if ((uint8)CANSM_WOPN_TRCV_MODE_STANDBY == ptrNetwork->CanSMNWIntSubState)
  {
	  /* @Trace: CanSM_SUD_API_132 */
    ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_STANDBY;
    /* Set the Transceiver mode as CANTRCV_TRCVMODE_STANDBY */
    result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE, CANTRCV_TRCVMODE_STANDBY);

  }
  /* Check the Internal Substate as CANSM_WOPN_NO_COMMUNICATION */
  /* @Trace: CanSM_SUD_API_133 */
  if ((uint8)CANSM_WOPN_NO_COMMUNICATION == ptrNetwork->CanSMNWIntSubState)
  {
    /* reset the value of Mode repetition time */
    ptrNetwork->CanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;
    /* update internal sub state machine as CANSM_ZERO */

    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* Change internal status */
    ptrNetwork->ModeStatus = (uint8)CANSM_NOCOMMUNICATION;

    /* Current state as COMM_SILENT_COMMUNICATION */
    /* @Trace: CanSM_SUD_API_134 */
    currentState = (ComM_ModeType)COMM_NO_COMMUNICATION;

    /* Notify internally stored network mode to the ComM*/
    ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);
    
    /* Notify bus-off node to the BswM */
    /* polyspace +2 MISRA-C3:10.3 [Not a defect:Low] "The violation is acceptable because AUTOSAR specification does not support the type of argument " */
    BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(ptrStaticNetwork->CanSmNetworkHandle),
                                                      CANSM_BSWM_BOR_COMPLETE);

    /* Update Internal BusOffCounter as Zero*/
    ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;
    
  } /* End of if (CANSM_WOPN_NO_COMMUNICATION ==
     *ptrNetwork->CanSMNWIntSubState) */

  /* CanSMModeReqReptTime is set to default value */
  if ((Std_ReturnType)E_OK == result)
  {
    /* Load the request Repetition Time value in the Local variable */
    ptrNetwork->CanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_ModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
	/* @Trace: CanSM_SUD_API_135 */
    CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
  }
} /* End of CanSM_DeInitPnNotSupported(NetworkHandleType */
/*  polyspace:end<MISRA-C:16.2:Low:Investigate> No action planned yet */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_DeInitPnSupported                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine handles the De initialization          **
**                        process for partial netowrk                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_Network             **
**                                                                            **
**                        Function(s) invoked   : CanIf_SetControllerMode()   **
**                                                CanIf_SetTransceiverMode()  **
**                                                BswM_CanSM_CurrentState()   **
**                                                ComM_BusSM_ModeIndication() **
**                                                CanIf_ClearTrcvWufFlag()    **
**                                                CanIf_CheckTrcvWakeFlag()   **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_DeInitPnSupported(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(Std_ReturnType, CANSM_VAR) result;

  
  /* initialized value as CANSM_E_WAITSTATE  */
  result = (uint8)CANSM_E_WAITSTATE;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];


  /* Clear the Wake up Flag  */
  if ((uint8)CANSM_PN_TRCV_CLEAR_WUF == ptrNetwork->CanSMNWIntSubState)
  {
    /* Note: S_PN_CLEAR_WUF is handled */
    result = CanSM_ClearTrcvWuf(CANSM_NETWORKHANDLE);
  }
  /* Note: T_CLEAR_WUF_INDICATED is detected */
  /* Set the Transceiver Mode to Stop */
  if (CANSM_PN_CC_STOPPED == ptrNetwork->CanSMNWIntSubState)
  {
    /* Note: S_CC_STOPPED is handled */
	/* @Trace: CanSM_SUD_API_071 */
    ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
    /* set the controllerMode as CAN_CS_STOPPED */
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STOPPED);
  }
  /* Set the Transceiver Mode to Normal */
  if ((uint8)CANSM_PN_TRCV_NORMAL == ptrNetwork->CanSMNWIntSubState)
  {
    /* Note: S_TRCV_NORMAL is handled  */
	/* @Trace: CanSM_SUD_API_073 */
    ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    /* set the transceiver mode  as CANTRCV_TRCVMODE_NORMAL */
    result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE, CANTRCV_TRCVMODE_NORMAL);

  }

  /* Note: T_TRCV_NORMAL_INDICATED is handled */
  /* Set the Transceiver Mode to StandBy */
  if ((uint8)CANSM_PN_TRCV_STANDBY == ptrNetwork->CanSMNWIntSubState)
  {

    /* Note: S_TRCV_STANDBY  is handled */
	/* @Trace: CanSM_SUD_API_075 */
    ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_STANDBY;
    /* set the transceiver mode  as CANTRCV_TRCVMODE_STANDBY */
    result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE, CANTRCV_TRCVMODE_STANDBY);

  }

  /* Note: T_TRCV_STANDBY_INDICATED is detected */
  /* Set the Controller Mode to Sleep */
  if ((uint8)CANSM_PN_CS_SLEEP == ptrNetwork->CanSMNWIntSubState)
  {
	/* @Trace: CanSM_SUD_API_076 */
    ptrNetwork->Mode = (uint8)CAN_CS_SLEEP;
    /* set the controller mode  as CAN_CS_SLEEP */
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_SLEEP);
  }

  /* Check the Transceiver Wake Up Flag  */
  if (((uint8)CANSM_PN_TRCV_CHECK_WUF == ptrNetwork->CanSMNWIntSubState)||((uint8)CANSM_PN_WFLAG_IN_NOT_CC_SLEEP == ptrNetwork->CanSMNWIntSubState))
  {
	  /* @Trace: CanSM_SUD_API_077 */
      /* Note: S_CHECK_WFLAG_IN_CC_SLEEP is handled */
      result = CanSM_CheckTrcvWuf(CANSM_NETWORKHANDLE);
  }
  /* Reset the Substate to Initial Sunstate and update
   *                                             Mode of the network as No COMM
   * */
  /* @Trace: CanSM_SUD_API_078 */
  if (((uint8)CANSM_PN_IN_NOT_CC_SLEEP_NOCOMM == ptrNetwork->CanSMNWIntSubState) ||((uint8)CANSM_PN_NO_COMMUNICATION == ptrNetwork->CanSMNWIntSubState))
  {

    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    if (CANSM_PN_NO_COMMUNICATION == ptrNetwork->CanSMNWIntSubState)
    {
      /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      /* Update the SubState as Zero */
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* Enter protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Change internal status */
      ptrNetwork->ModeStatus = (uint8)CANSM_NOCOMMUNICATION;

      /* Exit protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();


      /* Current state as COMM_SILENT_COMMUNICATION */
      currentState = (ComM_ModeType)COMM_NO_COMMUNICATION;

      /* Notify internally stored network mode to the ComM*/
      ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

    } /* End of if (CANSM_PN_NO_COMMUNICATION ==*ptrNetwork->CanSMNWIntSubState) */

    /* #14519 Notify bus-off node to the BswM */
    /* polyspace +2 MISRA-C3:10.3 [Not a defect:Low] "The violation is acceptable because AUTOSAR specification does not support the type of argument " */
    BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(ptrStaticNetwork->CanSmNetworkHandle),
                                                      CANSM_BSWM_BOR_COMPLETE);

    /* Update the SubState as Zero */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;


  } /* End of if ((CANSM_PN_IN_NOT_CC_SLEEP_NOCOMM ==
  *ptrNetwork->CanSMNWIntSubState) || */



  /* Check if result is equal to E_OK */
  if ((Std_ReturnType)E_OK == result)
  {
    /* Load the request Repetition Time value in the Local variable */
    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;
  }

  /* Note: Time out processing has to be handled */
  else
  {
	/* @Trace: CanSM_SUD_API_074 */
    /* Call the function for Time Out Processing */
    CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
  }


} /* End of CanSM_DeInitPnSupported(NetworkHandleType */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */

/*******************************************************************************
** Function Name        : CanSM_NoToFullCommRequested                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION for the corresponding      **
**                        network handle.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_Network             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                CanIf_SetTransceiverMode()                  **
**                                CanIf_SetControllerMode()                   **
**                                CanIf_SetPduMode()                          **
**                                BswM_CanSM_CurrentState()                   **
**                                ComM_BusSM_ModeIndication()                 **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 SRS_Can_01158 */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_NoToFullCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Initial value as Wait State */
  result = (uint8)CANSM_E_WAITSTATE;

  /* Set the Transceiver Mode to Normal */
  if ((uint8)CANSM_PREFULL_TRCV_NORMAL == ptrNetwork->CanSMNWIntSubState)
  {
    /* @Trace: CanSM_SUD_API_136 */
    ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE, CANTRCV_TRCVMODE_NORMAL);
  }

  /* Set the Controller Mode to StandBy */
  if ((uint8)CANSM_PREFULL_CC_STOPPED == ptrNetwork->CanSMNWIntSubState)
  {
    /* Note: state operation is in S_CC_STOPPED */
    /* @Trace: CanSM_SUD_API_137 */
    ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STOPPED);
  }

  /* Set the Controller Mode to Sleep */
  if ((uint8)CANSM_PREFULL_CC_STARTED == ptrNetwork->CanSMNWIntSubState)
  {
	/* @Trace: CanSM_SUD_API_138 */
    ptrNetwork->Mode = (uint8)CAN_CS_STARTED;
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STARTED);
  }

  /* Note: The sub state is triggered with T_CC_STARTED_INDICATED */
  /* @Trace: CanSM_SUD_API_139 */
  if ((uint8)CANSM_PREFULL_CC_ONLINE == ptrNetwork->CanSMNWIntSubState)
  {
    result |= CanSM_NoToFullCommRequested_PREFULL_CC_ONLINE(networkHandle);
  } /* End of if (CANSM_PREFULL_CC_ONLINE == ptrNetwork->CanSMNWIntSubState) */

  if ((Std_ReturnType)E_OK == result)
  {
    /* Load the request Repetition Time value in the Local variable */
    ptrNetwork->CanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_ModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
    /* @Trace: CanSM_SUD_API_142 */
    CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
  }
} /* End of CanSM_NoToFullCommRequested(NetworkHandleType */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SetBaudrateService                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION or CANSM_NO_COMMUNICATION  **
**                        for the corresponding network handle.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked :                               **
**                                CanIf_SetTransceiverMode()                  **
**                                CanIf_SetControllerMode()                   **
**                                CanIf_SetPduMode()                          **
**                                BswM_CanSM_CurrentState()                   **
**                                ComM_BusSM_ModeIndication()                 **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_Can_01142 */
#if (STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_SetBaudrateService(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(Std_ReturnType, CANSM_VAR) result;
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;


  
  #if(STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean,CANSM_VAR) pnSupported;
  #endif

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];
 if((CanSM_BaudrateDirect)CANSM_UNIDENTIFIED_BAUDRATE == ptrNetwork->Baudrate)
 {
    /* check the feasibility of set baudrate direct */
	/* @Trace: CanSM_SUD_API_116 */
	/* @Trace: CanSM_SUD_API_117 */
    CanSM_SetBaudrateDirect(CANSM_NETWORKHANDLE);
 }



  /* unable to set baudrate directly so It is needed to operate sub state machine */
  if((CanSM_BaudrateDirect)CANSM_NOT_DIRECT_BAUDRATE == ptrNetwork->Baudrate)
  {

	/* @Trace: CanSM_SUD_API_118 */
    /* Check if Internal State is equal to CANSM_BR_CC_STOPPED  */
    if ((uint8)CANSM_BR_CC_STOPPED == ptrNetwork->CanSMNWIntSubState)
    {
    	/* @Trace: CanSM_SUD_API_119 */
      ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
      /* Set the Controller mode as CAN_CS_STOPPED */
      result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STOPPED);

    }


    /* Check if Internal State is equal to CANSM_BR_STARTED  */
    /* @Trace: CanSM_SUD_API_120 */
    else if ((uint8)CANSM_BR_STARTED == ptrNetwork->CanSMNWIntSubState)
    {
      /* @Trace: CanSM_SUD_API_121 */
      /* Set the current mode of the network as No Communication in order to change baudrate */
      currentState = (ComM_ModeType)COMM_NO_COMMUNICATION;

      /* Notify COMM_NO_COMMUNICATION to ComM */
      ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);


      /* polyspace +3 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
      /* change the baudrate of the respective controllers */
      /* @Trace: CanSM_SUD_API_122 */
      CANIF_SETBAUDRATE(ptrStaticNetwork->ControllerIndex,ptrNetwork->BaudRateConfigID);

      /* @Trace: CanSM_SUD_API_123 */
      ptrNetwork->Mode = (uint8)CAN_CS_STARTED;
      /* Set the Controller mode as CAN_CS_STARTED */
      result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STARTED);


    } /* End of if (CANSM_BR_STARTED == ptrNetwork->CanSMNWIntSubState) */


    /* Check if Internal State is equal to CANSM_BR_CC_ONLINE  */
    /* @Trace: CanSM_SUD_API_124 */
    else if (CANSM_BR_CC_ONLINE == ptrNetwork->CanSMNWIntSubState)
    {
      /* set result to E_OK */
      result = (uint8)E_OK;

      /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime =
          (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      /* Update the Internal State as Zero */
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* @Trace: CanSM_SUD_API_126 */
      if ((uint8)COMM_FULL_COMMUNICATION == ptrNetwork->ReqModeStatus)
      {

        /* Enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Enter Full Communication after baudrate setting */
        ptrNetwork->ModeStatus = (uint8)CANSM_BAUDRATEENDFULLCOM;

        /* Exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      }

      else if((uint8)COMM_SILENT_COMMUNICATION == ptrNetwork->ReqModeStatus)
      {
        /* enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Enter Silent Communication mode after Baudrate setting */
        ptrNetwork->ModeStatus = (uint8)CANSM_BAUDRATEENDSILENTCOM;

        /* exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      }
      else
      {
    	/* @Trace: CanSM_SUD_API_125 */
        /*Notify BswM the change of mode*/
        BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);

        /* enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        #if(STD_ON == CANSM_PNC_AVAILABILITY)
        /* get PnSupported Status from CanSm_StaticNw */
        pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;

        if((boolean)CANSM_TRUE == pnSupported)
        {
          /* set mode status to CANSM_DEINITPNSUPPORTED */
          ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;
        }
        else
        {
          /* set mode status to CANSM_DEINITPNNOTSUPPORTED */
          ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
        }
        #else
        /* set mode status to CANSM_DEINITPNNOTSUPPORTED */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
        #endif

        /* exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      }
    }/* End of if (CANSM_BR_CC_ONLINE == ptrNetwork->CanSMNWIntSubState) */
    else
    {
        result = (uint8)CANSM_E_WAITSTATE;
    }

    if ((Std_ReturnType)E_OK == result)
    {
      /* Load the request Repetition Time value in the Local variable */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;
    }
    else
    {
      /* Call the function for Time Out Processing */
      /* @Trace: CanSM_SUD_API_128 */
      CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
    }
  }

  /* @Trace: CanSM_SUD_API_127 */
  else  /* direct baudrate setting is successful */
  {
    /* reset requested repeat time */
    ptrNetwork->CanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /* update internal state to zero */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    if((uint8)COMM_FULL_COMMUNICATION == ptrNetwork->ReqModeStatus)
    {

      /* enter protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* update mode status to CANSM_BAUDRATEENDFULLCOM */
      ptrNetwork->ModeStatus = (uint8)CANSM_BAUDRATEENDFULLCOM;

      /* exit protection area*/
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    }

    if((uint8)COMM_SILENT_COMMUNICATION == ptrNetwork->ReqModeStatus)
    {
      /* enter protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* update mode status to CANSM_BAUDRATEENDSILENTCOM */
      ptrNetwork->ModeStatus = (uint8)CANSM_BAUDRATEENDSILENTCOM;

      /* enter protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    }


  }
} /* End of CanSM_SetBaudrateService(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanSM_ChangeBaudrateEndFullCom                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CanSM_SetBaudrateSERVICE to CANSM_FULLCOMMUNICATION **
**                        for the corresponding network handle.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked :
**                                CanIf_SetPduMode()                          **
**                                BswM_CanSM_CurrentState()                   **
**                                ComM_BusSM_ModeIndication()                 **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
/* @Trace: CanSM_SUD_API_115 */
#if (STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void,CANSM_CODE) CanSM_ChangeBaudrateEndFullCom(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
    P2VAR(CanSM_NetworkType,AUTOMATIC,CANSM_VAR) ptrNetwork;
    P2CONST(CanSM_StaticNetworkType,AUTOMATIC,CANSM_CONST) ptrStaticNetwork;
    VAR(ComM_ModeType,CANSM_VAR) currentState;
    VAR(Std_ReturnType, CANSM_VAR) result;
    result = (Std_ReturnType)E_OK;
    VAR(uint8,CANSM_VAR) controllerIndex;
    VAR(uint8,CANSM_VAR) noOfController;

    /* get address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* get address of CanSM_StaticNw to local pointer*/
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

    /* reset requested repeat time */
    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /*enter protection area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* set the mode of the CanSM to CANSM_CHECKBUSOFF */
    ptrNetwork->ModeStatus = (uint8)CANSM_CHECKBUSOFF;

    /* exit protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    /* check status of CanSM_ECUPassive */
    if((CanSM_ECUPassiveType)CANSM_ECUPASSIVE == CanSM_ECUPassive)
    {
      /* polyspace +7 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
      /* set pdu mode of multiple controller to CANIF_TX_OFFLINE_ACTIVE */
      CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_TX_OFFLINE_ACTIVE);
    }
    else
    {
      /* set pdu mode of multiple controller to CANIF_ONLINE */
      CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_ONLINE);

    }

    /* set currentState to COMM_FULL_COMMUNICATION */
    currentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;


    /* Notify ComM with COMM_FULL_COMMUNICATION */
    ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);


    /* Notify BswM with network handle and  CANSM_BSWM_FULL_COMMUNICATION*/
    BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_FULL_COMMUNICATION);

}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if (STD_ON == CANSM_SET_BAUDRATE_API) */


/*******************************************************************************
** Function Name        : CanSM_ChangeBaudrateEndSilentCom                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CanSM_SetBaudrateSERVICE to                         **
**                        CANSM_SILENTCOMMUNICATION                           **
**                        for the corresponding network handle.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
/* @Trace: CanSM_SUD_API_114 */
#if (STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void,CANSM_CODE) CanSM_ChangeBaudrateEndSilentCom(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
    P2CONST(CanSM_StaticNetworkType,AUTOMATIC,CANSM_CONST) ptrStaticNetwork;
    P2VAR(CanSM_NetworkType,AUTOMATIC,CANSM_VAR) ptrNetwork;
    VAR(ComM_ModeType,CANSM_VAR) currentState;
    VAR(Std_ReturnType, CANSM_VAR) result;
    result = (Std_ReturnType)E_OK;
    VAR(uint8,CANSM_VAR) controllerIndex;
    VAR(uint8,CANSM_VAR) noOfController;

    /* get address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* get address of CanSM_StaticNw to local pointer */
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

    /* reset requested repeat time */
    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /*enter protection area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /*set mode status to Silent Com */
    ptrNetwork->ModeStatus = (uint8)CANSM_SILENTCOMMUNICATION;

    /*exit protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();


    /* Notify CANSM_BSWM_SILENT_COMMUNICATION to BswM */
    BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,CANSM_BSWM_SILENT_COMMUNICATION);
    /* polyspace +2 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
    /* set Pdu mode to CANIF_TX_OFFLINE for multiple controller */
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_TX_OFFLINE);


    /* set currentState of ComM to COMM_SILENT_COMMUNICATION */
    currentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;


    /* notify COMM_SILENT_COMMUNICATION to ComM */
    ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if (STD_ON == CANSM_SET_BAUDRATE_API) */


/*******************************************************************************
** Function Name        : CanSM_WakeUpValidation                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service operate the WUVALIDATION
**                       sub state machine                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void,CANSM_CODE) CanSM_WakeUpValidation(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{

  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(Std_ReturnType, CANSM_VAR) result;



  /* Initialize result as CANSM_E_WAITSTATE*/
  result = (uint8)CANSM_E_WAITSTATE;

  /* get the address of CanSM Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* set the transceiver mode to stop */
  /* @Trace: CanSM_SUD_API_199 */
  if((uint8)CANSM_WUV_TRCV_NORMAL == ptrNetwork->CanSMNWIntSubState)
  {

      ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_NORMAL;
      result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE,CANTRCV_TRCVMODE_NORMAL);
  }


  /* Set the controller mode to CAN_CS_STOPPED */
  /* @Trace: CanSM_SUD_API_110 */
  if((uint8)CANSM_WUV_CC_STOPPED == ptrNetwork->CanSMNWIntSubState)
  {

      ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
      result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE,CAN_CS_STOPPED);
  }

  /* Set the controller mode to CAN_CS_STARTED*/
  /* @Trace: CanSM_SUD_API_111 */
  if((uint8)CANSM_WUV_CC_STARTED == ptrNetwork->CanSMNWIntSubState)
  {

      ptrNetwork->Mode = (uint8)CAN_CS_STARTED;
      result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE,CAN_CS_STARTED);
  }

  /* @Trace: CanSM_SUD_API_112 */
  if((uint8)CANSM_WUV_WAIT_LEAVE == ptrNetwork->CanSMNWIntSubState)
  {
      /* Check whether Full com is requested by ComM or Not */
      if((uint8)COMM_FULL_COMMUNICATION == ptrNetwork->ReqModeStatus)
      {

        /* Reset the Mode repetition request*/
        ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

        /* reset requested repeat time */
        ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

        /* Update CanSM Init Sub state to ZERO */
        ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

        /* Enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Update Mode status to CANSM_WAKEUPTOFULLCOMREQUESTED*/
        ptrNetwork->ModeStatus = (uint8)CANSM_WAKEUPTOFULLCOMREQUESTED;

        /* Exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
       }
  }

  if((Std_ReturnType)E_OK == result)
  {
      /* Load the request repetition */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;
  }
  else
  {
	  /* @Trace: CanSM_SUD_API_113 */
      /* Call the function for Time Out processing */
      CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
  }

} /* End of CanSM_WakeUpValidation */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_WakeUpToFullComRequested                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION from WUVALIDATION          **
**                        for the corresponding network handle.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 SRS_Can_01158 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void,CANSM_CODE) CanSM_WakeUpToFullComRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* initialize result as CANSM_E_WAITSTATE */
  result = (uint8)CANSM_E_WAITSTATE;

  /* get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Set the Transceiver Mode to Normal */
  /* @Trace: CanSM_SUD_API_100 */
  if((uint8)CANSM_PREFULL_TRCV_NORMAL == ptrNetwork->CanSMNWIntSubState)
  {
    ptrNetwork->Mode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    result = CanSM_SetCanTrcvMode(CANSM_NETWORKHANDLE,CANTRCV_TRCVMODE_NORMAL);
  }
  /* Set the controller mode to CAN_CS_STOPPED */
  /* @Trace: CanSM_SUD_API_101 */
  if((uint8)CANSM_PREFULL_CC_STOPPED == ptrNetwork->CanSMNWIntSubState)
  {
    ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE,CAN_CS_STOPPED);
  }
  /* @Trace: CanSM_SUD_API_102 */
  /* Set the controller mode to CAN_CS_STARTED */
  if((uint8)CANSM_PREFULL_CC_STARTED == ptrNetwork->CanSMNWIntSubState)
  {
    ptrNetwork->Mode = (uint8)CAN_CS_STARTED;
    result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE,CAN_CS_STARTED);
  }
  /* Set the controller mode to */
  /* @Trace: CanSM_SUD_API_109 */
  if((uint8)CANSM_PREFULL_CC_ONLINE == ptrNetwork->CanSMNWIntSubState)
  {
    result |= CanSM_WakeUpToFullComRequested_PREFULL_CC_ONLINE(networkHandle);
  }
  if((Std_ReturnType)E_OK == result)
  {
    /* Load the request repetition time value in the local variable */
    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;
  }
  else
  {
    /* Call the function for time out processing */
    /* @Trace: CanSM_SUD_API_108 */
    CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE,result);
  }
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SilentToFullCommRequested                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION for the corresponding      **
**                        network handle.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_Can_01158 SRS_Can_01142 SRS_Can_01145 */
/* @Trace: CanSM_SUD_API_190 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_SilentToFullCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;
  VAR(Std_ReturnType, CANSM_VAR) result;
  result = (Std_ReturnType)E_OK;
  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Set the Pdu Mode to CANIF_TX_OFFLINE_ACTIVE in case ECU is passive */
  if((CanSM_ECUPassiveType)CANSM_ECUPASSIVE == CanSM_ECUPassive)
  {
    /* @Trace: CanSM_SUD_API_146 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex, CANIF_TX_OFFLINE_ACTIVE);
  }
  /* Set the Pdu Mode to Online in case ECU is not passive */
  else
  {
    /* @Trace: CanSM_SUD_API_145 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex, CANIF_ONLINE);

  }

  if ((Std_ReturnType)E_OK == result)
  {
    /* reset requested repeat time */
    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /* update internal sub state machine as CANSM_ZERO */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
    ptrNetwork->ModeStatus = (uint8)CANSM_CHECKBUSOFF;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    /* Load the timer with value One */
    ptrNetwork->Timer = (CanSM_TimerType)CANSM_ONE;

    /* @Trace: CanSM_SUD_API_147 */
    /* Current state as COMM_FULL_COMMUNICATION */
    currentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

    ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

    /* @Trace: CanSM_SUD_API_148 */
    /* Notify internally stored network mode to the BsWM*/
    BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_FULL_COMMUNICATION);

    /* Call the BusOff Function */
    CanSM_CheckBusOff(CANSM_NETWORKHANDLE);
  }
} /* End of CanSM_SilentToFullCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
   **/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_FullToSilentCommRequested                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_SILENT_COMMUNICATION for the corresponding    **
**                        network handle.                                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_FullToSilentCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(Std_ReturnType, CANSM_VAR) result;
  result = (Std_ReturnType)E_OK;
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;
  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* @Trace: CanSM_SUD_API_149 */
  /* Notify internally stored network mode to the BsWM */
  BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_SILENT_COMMUNICATION);

  /* @Trace: CanSM_SUD_API_150 */
  /* Set Pdu Mode as Offline */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
  CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex, CANIF_TX_OFFLINE);


  /* Enter Protection area */
  SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

  /* Set the mode of the CanSM to SILENT state */
  ptrNetwork->ModeStatus = (uint8)CANSM_SILENTCOMMUNICATION;

  /* Exit Protection area */
  SchM_Exit_CanSM_MODE_STATUS_PROTECTION();


  /* Current state as COMM_SILENT_COMMUNICATION */
  currentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;

  /* Notify internally stored network mode to the ComM*/
  /* @Trace: CanSM_SUD_API_151 */
  ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);
  CANSM_UNUSED(result);
} /* End of CanSM_FullToSilentCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_NoCommunication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicates the current state as         **
**                        CANSM_NO_COMMUNICATION for the corresponding        **
**                        network handle.                                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : NA                            **
*******************************************************************************/

#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_NoCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];
  
  /* Check if Requested Mode Status is equal to No communication */
  if ((uint8)COMM_NO_COMMUNICATION != ptrNetwork->ReqModeStatus)
  {
    /* Reset the request repeated time to Configured value */
    ptrNetwork->CanSMModeReqReptTime =(CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /* Update the Internal Substate as Zero */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* Enter Protection area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Update the Mode status to CANSM_NOTOFULLCOMMREQUESTED */
    ptrNetwork->ModeStatus = (uint8)CANSM_NOTOFULLCOMMREQUESTED;
    /* Exit Protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    CanSM_NoToFullCommRequested(CANSM_NETWORKHANDLE);
  }
} /* End of CanSM_NoCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SilentCommunication                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicates the current state as         **
**                        CANSM_SILENT_COMMUNICATION for the corresponding    **
**                        network handle.                                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                        Function(s) invoked : BswM_CanSM_CurrentState()     **
**                                              CanSM_DeInitPnSupported()     **
**                                              CanSM_DeInitPnNotSupported()  **
**                                           CanSM_SilentToFullCommRequested()**
*******************************************************************************/

/* @Trace: SRS_Can_01145 SRS_Can_01142 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_SilentCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean,CANSM_VAR) pnSupported;
  #endif


  
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];


  /* Check if Requested Mode Status is not equal to Silent Communication */
  if ((uint8)COMM_SILENT_COMMUNICATION != ptrNetwork->ReqModeStatus)
  {
    /* Update Internal Substate as zero */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* @Trace: CanSM_SUD_API_152 */
    /* Check if Requested Mode Status is not equal to Full Communication */
    if ((uint8)COMM_FULL_COMMUNICATION == ptrNetwork->ReqModeStatus)
    {
      /* set internal sub state machine to CANSM_ZERO*/
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;


      /* Enter Protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Update Internal Substate as CANSM_SILENTTOFULLCOMMREQUESTED */
      ptrNetwork->ModeStatus = (uint8)CANSM_SILENTTOFULLCOMMREQUESTED;

      /* Enter Protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* Call the function CanSM_SilentToFullCommRequested */
      CanSM_SilentToFullCommRequested(CANSM_NETWORKHANDLE);
    }
    else
    {
      /* @Trace: CanSM_SUD_API_153 */
      /* Notify the network mode to the BswM */
      BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);

      /* set internal sub state machine to CANSM_ZERO*/
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

        /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime =
          (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      #if (STD_ON == CANSM_PNC_AVAILABILITY)
      pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;

      /* Check if Partial Networking is Available */
      if ((boolean)CANSM_TRUE == pnSupported)
      {
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    	/* @Trace: CanSM_SUD_API_154 */
        /* Set Mode status to CANSM_DEINITPNSUPPORTED  */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;

        /*Exit protection area*/
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

        /* Call the CanSM_DeInitPnSupported funcion  */
        CanSM_DeInitPnSupported(CANSM_NETWORKHANDLE);
      }

      else
      {
    	/* @Trace: CanSM_SUD_API_155 */
        /*Enter protection area*/
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Update the Mode status to CANSM_DEINITPNNOTSUPPORTED */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;

        /*Exit protection area*/
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();


        /* Call the CanSM_DeInitPnNotSupported funcion  */
        CanSM_DeInitPnNotSupported(CANSM_NETWORKHANDLE);
      }
      #else /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */
      /*Enter protection area*/
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Update the Mode status to CANSM_DEINITNOTSUPPORT */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;

      /*Exit protection area*/
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();


      /* Call the CanSM_DeInitPnNotSupported funcion  */
      CanSM_DeInitPnNotSupported(CANSM_NETWORKHANDLE);

      #endif /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */


    } /* End of else */
  } /* End of if ((uint8)COMM_SILENT_COMMUNICATION !=
     *ptrNetwork->ReqModeStatus) */


} /* End of CanSM_SilentCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_ClearTrcvWuf                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Clearing the transceiver **
**                        flag.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle                     **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType  result                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_ClearTrcvWufFlag()      **
*******************************************************************************/
#if(STD_ON == CANSM_PNC_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(Std_ReturnType, CANSM_CODE) CanSM_ClearTrcvWuf(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #endif
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* @Trace: CanSM_SUD_API_069 */
  result = CanIf_ClearTrcvWufFlag(ptrStaticNetwork->CanSmTranceiverId);
  /* polyspace +1 DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
  if ((Std_ReturnType)E_OK == result)
  {
    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Update the Internal Substate*/
    ptrNetwork->CanSMNWIntSubState = CANSM_PN_CLEAR_WUF_WAIT;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }

  return (result);
} /* End of CanSM_ClearTrcvWuf(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if(STD_ON == CANSM_PNC_AVAILABILITY) */
/*******************************************************************************
** Function Name        : CanSM_CheckTrcvWuf                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Checking the transceiver **
**                        flag.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : VAR(Std_ReturnType, CANSM_VAR) result               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanSM_StaticNw             **
**                                                 CanSM_Network              **
**                        Function(s) invoked    : CanIf_CheckTrcvWufFlag()   **
*******************************************************************************/
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckTrcvWuf(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #endif
  VAR(Std_ReturnType, CANSM_VAR) result;


  
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];



  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];



  /*Check whether flag is cleared*/
  result = CanIf_CheckTrcvWakeFlag(ptrStaticNetwork->CanSmTranceiverId);

  /* Check if E_OK is returned */
  if ((Std_ReturnType)E_OK == result)
  {

      /* Increment the internal Substate by one */
      ptrNetwork->CanSMNWIntSubState =  ptrNetwork->CanSMNWIntSubState + CANSM_ONE;
  }

  return (result);
} /* End of CanSM_CheckTrcvWuf(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANSM_PNC_AVAILABILITY) */
/*******************************************************************************
** Function Name        : CanSM_SetCanControllerMode                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for setting the controller   **
**                        mode.                                               **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        CanIf_ControllerModeType LenMode                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanSM_StaticNw             **
**                                                 CanSM_Network              **
**                        Function(s) invoked    : CanIf_SetControllerMode()  **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(uint8, CANSM_CODE) CanSM_SetCanControllerMode(VAR(NetworkHandleType,CANSM_VAR) networkHandle,
  VAR(Can_ControllerStateType,CANSM_VAR) LenMode)
{

  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(Std_ReturnType, CANSM_VAR) result;
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
    (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))  
  VAR(Can_ControllerStateType,CANSM_VAR) lenMode;
  #else
  VAR(CanIf_ControllerModeType,CANSM_VAR) lenMode;
  #endif

  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;


  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Initialize the variable with E_OK */
  result = (uint8)E_OK;

  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
    (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  lenMode = LenMode;
  #else
  switch (LenMode)
  {
    case CAN_CS_SLEEP:
      lenMode = CANIF_CS_SLEEP;
      break;
    case CAN_CS_STARTED:
      lenMode = CANIF_CS_STARTED;
      break;
    case CAN_CS_STOPPED:
      lenMode = CANIF_CS_STOPPED;
      break;
    /* polyspace +1 RTE:UNR [Justified:Low] "No impact" */
    default:
      lenMode = CANIF_CS_UNINIT;
      break;
  }
  #endif

  /* polyspace +2 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
  /* Set the controller mode to sleep */
  CANIF_SETCONTROLLERMODE(ptrStaticNetwork->ControllerIndex, lenMode);

  /* Check if result is equal to E_OK */
  if ((Std_ReturnType)E_OK == result)
  {

    /* Get the address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* Update the Internal Substate*/
    ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + (uint8)CANSM_ONE;
  }

  return (result);
} /* End of CanSM_SetCanControllerMode(VAR(NetworkHandleType,CANSM_VAR) networkHandle,
   *Can_ControllerStateType LenMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SetCanTrcvMode                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for setting the transceiver  **
**                        mode.                                               **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        VAR(CanTrcv_TrcvModeType,CANSM_VAR) LenMode         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanSM_Network              **
**                                                 CanSM_StaticNw             **
**                        Function(s) invoked    : CanIf_SetTrcvMode()        **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_Can_01142 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetCanTrcvMode(VAR(NetworkHandleType,CANSM_VAR) networkHandle,
 VAR(CanTrcv_TrcvModeType,CANSM_VAR) LenMode)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #endif
  VAR(Std_ReturnType, CANSM_VAR) result;

  #if (STD_OFF == CANSM_CANTRCV_SUPPORT)
  CANSM_UNUSED(LenMode);
  #endif


  
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Initialize the variable with E_OK */
  result = (uint8)E_OK;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  if ((uint8)CANSM_CANTRCV_INVALID_ID != ptrStaticNetwork->CanSmTranceiverId)
  {
    /*Check whether the mode is set*/
    result = CanIf_SetTrcvMode(ptrStaticNetwork->CanSmTranceiverId, LenMode);

    /* Check if result is equal to E_OK */
    if ((Std_ReturnType)E_OK == result)
    {

      /* Update the Internal Substate*/
      ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + CANSM_ONE;
    }
  } /* End of if ((uint8)CANSM_CANTRCV_INVALID_ID !=
     *ptrStaticNetwork->CanSmTranceiverId) */


  else
  #endif /* End of if (STD_ON == CANSM_CANTRCV_SUPPORT) */
  {
    /* Update the Internal Substate*/
	/* @Trace: CanSM_SUD_API_156 */
    ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + CANSM_TWO;
  }
  return (result);
} /* End of CanSM_SetCanTrcvMode(VAR(NetworkHandleType,CANSM_VAR) networkHandle,
   *CanTrcv_TrcvModeType LenMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_TimeoutProcessing                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Processing the time      **
**                        required to srvice the requested mode change.       **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        VAR(Std_ReturnType, CANSM_VAR) result               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                        Function(s) invoked : CanIf_SetTrcvMode()           **
**                                              Dem_SetEventStatus()          **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_Can_01142 SRS_BSW_00466 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_TimeoutProcessing(VAR(NetworkHandleType,CANSM_VAR) networkHandle, VAR(Std_ReturnType, CANSM_VAR) result)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;

  VAR(CanSM_TimerType,CANSM_VAR) LddReqReptTime;
  
  #if(STD_ON == CANSM_DEM_STATUS)
  /* #4509 */
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
  #endif
  

  
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  if ((uint8)E_NOT_OK == result)
  {
    /* Decrement the counter */
    ptrNetwork->CanSMModeReqReptMax = ptrNetwork->CanSMModeReqReptMax - CANSM_ONE;
  }
  else
  {
    /* Load Request Repeat time in Local variable */
    LddReqReptTime = ptrNetwork->CanSMModeReqReptTime;

    /* Check if Request Repeat time is zero */
    if ((CanSM_TimerType)CANSM_ZERO != LddReqReptTime)
    {
      /* Decrement the Request Repeat time */
      LddReqReptTime--;
    }
    /* Check if Request Repeat time is zero */
    if ((CanSM_TimerType)CANSM_ZERO == LddReqReptTime)
    {
        /* Load Request Repeat time in Local variable */
        LddReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

        /* Check if Internal Substate is CANSM_PN_CS_SLEEP_WAIT */
        if ((uint8)CANSM_PN_CS_SLEEP_WAIT == ptrNetwork->CanSMNWIntSubState)
        {
          /* Update Internal Substate as CANSM_PN_WFLAG_IN_NOT_CC_SLEEP */
          ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_PN_WFLAG_IN_NOT_CC_SLEEP;

        }
        else
        {
          /* Decrement the Internal Substate by one */
          ptrNetwork->CanSMNWIntSubState =
            ptrNetwork->CanSMNWIntSubState - CANSM_ONE;
        }
        /* Decrement the counter */
        ptrNetwork->CanSMModeReqReptMax =
          ptrNetwork->CanSMModeReqReptMax - CANSM_ONE;

        /* Check if Internal Substate CANSM_PN_WFLAG_IN_NOT_CC_SLEEP */
        if((uint8)CANSM_PN_WFLAG_IN_NOT_CC_SLEEP == ptrNetwork->CanSMNWIntSubState)
        {
           /* Reset CanSMModeReqReptMax value of CanSM_Network to the original one */
           ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;
        }

     } /* End of if ((CanSM_TimerType)CANSM_ZERO == LddReqReptTime) */

     /* Load Request Repeat time in Local variable */
     ptrNetwork->CanSMModeReqReptTime = (uint8)LddReqReptTime;

  } /* End of else */

  /* Check if Mode Request max is equal to zero */
  /* @Trace: CanSM_SUD_API_157 */
  if ((uint8)CANSM_ZERO == ptrNetwork->CanSMModeReqReptMax)
  {
    #if (STD_ON == CANSM_USER_TIMEOUT_SUPPORT)
    CANSM_USER_TIMEOUT_FUNCTION(CANSM_NETWORKHANDLE);
    #endif
    /* AUTOEVER_CANSM_DEFINE this function is not used in HKMC ES Spec */
    /* Reset the Sub Mode to initial Mode */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /* Reset the Request Repetition Time */
    ptrNetwork->CanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_ModeReqRepeatTime;

    /* check whether DEM is supported */
    #if(STD_ON == CANSM_DEM_STATUS)
    /* @Trace: CanSM_SUD_API_161 */
    if((Dem_EventIdType)CANSM_DEM_NO_EVENT != ptrStaticNetwork->TimeOutEventId)
    {
      /* @Trace: CanSM_SUD_API_162 */
      (void)Dem_SetEventStatus(ptrStaticNetwork->TimeOutEventId,DEM_EVENT_STATUS_PREFAILED);
    }
    #endif
  } /* End of if (CANSM_ZERO == ptrNetwork->CanSMModeReqReptMax) */
} /* End of CanSM_TimeoutProcessing(VAR(NetworkHandleType,CANSM_VAR) networkHandle, uint8
   *result) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_SilentCommunication_BOR                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Processing the bus off
**                      recovery sub state machine from silent com            **
**
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        VAR(Std_ReturnType, CANSM_VAR) result               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : BswM_CanSM_CurrentState       **
**                                              Dem_SetEventStatus            **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
**
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 SRS_Can_01144 SRS_BSW_00422  SRS_Can_01146 SRS_BSW_00466 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > Its boundary is pre-defined */
FUNC(void, CANSM_CODE) CanSM_SilentCommunication_BOR(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;

  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;

  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;


  #if(STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean,CANSM_VAR) pnSupported;
  #endif




  /*Get the address of Network to the local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /*Get the address of Static Network to the local pointer*/
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  VAR(Std_ReturnType, CANSM_VAR) result;
  /* initialize result as E_NOT_OK */
  result = (Std_ReturnType)E_NOT_OK;


  if((uint8)COMM_NO_COMMUNICATION == ptrNetwork->ReqModeStatus)
  {


    /*Update internal sub state as Zero*/
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* make the bus off counter zero */
    ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

    /* Reset the Mode repetition request*/
    ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

    /* Reset the Request Repetition Time */
    ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;


    /*Notify BswM the change of mode*/
    /* @Trace: CanSM_SUD_API_163 */
    BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);

    /*Enter protection area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /*Update the change of mode status*/
    #if(STD_ON == CANSM_PNC_AVAILABILITY)

    pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;

    if((boolean)CANSM_TRUE == pnSupported)
    {

        /* Update ModeStatus to CANSM_DEINITPNSUPPORTED */
    	/* @Trace: CanSM_SUD_API_165 */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;
    }
    else
    {
        /* Update ModeStatus to CANSM_DEINITPNNOTSUPPORTED */
    	/* @Trace: CanSM_SUD_API_164 */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
    }

    #else
    /* Update ModeStatus to CANSM_DEINITPNNOTSUPPORTED */
    /* @Trace: CanSM_SUD_API_196 */
    ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
    #endif
    /* Exit protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }
  else
  {

    /* check whether DEM is supported */
    #if(STD_ON == CANSM_DEM_STATUS)

    if((Dem_EventIdType)CANSM_DEM_NO_EVENT != ptrStaticNetwork->TimeOutEventId )
    {
        /* Report the error to DEM with event id and DEM_EVENT_STATUS_PREFAILED */
    	/* @Trace: CanSM_SUD_API_166 */
        (void)Dem_SetEventStatus(ptrStaticNetwork->BusOffEventId, (Dem_EventStatusType)DEM_EVENT_STATUS_PREFAILED);
    }

    #endif
    if((uint8)CANSM_SILENT_BOR_RESTART_CC == ptrNetwork->CanSMNWIntSubState)
    {
      /* @Trace: CanSM_SUD_API_167	 */
      /* set Mode to CAN_CS_STARTED */
      ptrNetwork->Mode = (uint8)CAN_CS_STARTED;
      /*Set controller mode as CAN_CS_STARTED */
      result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE,CAN_CS_STARTED);
    }

    /* @Trace: CanSM_SUD_API_168 */
    else if((uint8)CANSM_SILENT_BOR_TX_OFF == ptrNetwork->CanSMNWIntSubState)
    {
      /* set Pdu Mode to  CANIF_TX_OFFLINE */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
      CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex, CANIF_TX_OFFLINE);

      /* @Trace: CanSM_SUD_API_169 */
      BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle, CANSM_BSWM_SILENT_COMMUNICATION);

      /* Set the change of Internal sub state */
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      /* Reset the Request Repetition Time */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* make the bus off counter zero */
      ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

      /*Enter protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Enter Silent communication */
      ptrNetwork->ModeStatus = (uint8)CANSM_SILENTCOMMUNICATION;

      /* Exit protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* Current state as COMM_SILENT_COMMUNICATION */
      /* @Trace: CanSM_SUD_API_170 */
      currentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;

      /* Notify internally stored network mode to the ComM*/
      ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

      /* Notify bus-off node to the BswM */
      /* polyspace +2 MISRA-C3:10.3 [Not a defect:Low] "The violation is acceptable because AUTOSAR specification does not support the type of argument " */
      BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(ptrStaticNetwork->CanSmNetworkHandle),
                                                      CANSM_BSWM_BOR_COMPLETE);
    }
    else
    {
      result = (Std_ReturnType)CANSM_E_WAITSTATE;
    }


    if((Std_ReturnType)E_OK == result)
    {
       /*Load the request time to local variable*/
       ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;
    }
    else
    {
    	/* @Trace: CanSM_SUD_API_171 */
        CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE,result);
    }

  }

}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SetBaudrateDirect                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The aim of the function is to determine the methodology
**                        of Set baudrate feature (direct or indirect)        **
**
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetBaudrate             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_Can_01142 */
/* extern for CanSM_SetCanTrcvMode */
#if(STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
FUNC(void, CANSM_CODE) CanSM_SetBaudrateDirect(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  VAR(Std_ReturnType,CANSM_VAR) result;

  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;

  VAR(uint8,CANSM_VAR) noOfController;
  VAR(uint8,CANSM_VAR) controllerIndex;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* set result to E_NOT_OK in the first place */
  result = (Std_ReturnType)E_OK;

  /* number of controller  */
  noOfController = (uint8)ptrStaticNetwork->NumberOfController;

  /* controller index */
  controllerIndex = (uint8)ptrStaticNetwork->ControllerIndex;


  /* check the feasibility of set baudrate directly  */
  do
    {
      /* polyspace +7 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      if((Std_ReturnType)E_NOT_OK == CanIf_SetBaudrate(CanSM_CtrlIndexToId[controllerIndex], ptrNetwork->BaudRateConfigID))
      {
        result = (Std_ReturnType)E_NOT_OK;
      }
      #else
      if((Std_ReturnType)E_NOT_OK == CanIf_SetBaudrate(CanSM_StaticController[controllerIndex], ptrNetwork->BaudRateConfigID))
      {
        result = (Std_ReturnType)E_NOT_OK;
      }
      #endif
      --noOfController;
      ++controllerIndex;
  }while(noOfController != CANSM_ZERO);


  /* determine set baudrate direct or not direct */
  if((Std_ReturnType)E_NOT_OK == result)
  {
     /* set baudrate not direct */
     ptrNetwork->Baudrate = (CanSM_BaudrateDirect)CANSM_NOT_DIRECT_BAUDRATE;
  }
  else
  {
     /* set baudrate direct */
     ptrNetwork->Baudrate = (CanSM_BaudrateDirect)CANSM_DIRECT_BAUDRATE;
  }

}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end of comparation of STD_ON to CANSM_SET_BAUDRATE_API) */
/*******************************************************************************
** Function Name        : CanSM_EBusOffPassive                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The aim of the function is execute the effect       **
**                        E_BUS_OFF_PASSIVE
**
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : BswM_RequestMode              **
**                                              Dem_SetEventStatus            **
**                                                                            **
*******************************************************************************/
/* definition for  for CanSM_EBusOffPassive */
/* @Trace: SRS_Can_01145 SRS_Can_01142 SRS_BSW_00466 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
FUNC(void, CANSM_CODE) CanSM_EBusOffPassive(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
    P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
    P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;

    /* Get the address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* Get the address of CanSM_StaticNw to local pointer */
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Check whether ModeStatus is CANSM_BORSTART */
    if((uint8)CANSM_BORSTART != ptrNetwork->ModeStatus)
    {

      /* Set the mode of the CanSM to CANSM_FULLCOMMUNICATION state */
      ptrNetwork->ModeStatus = (uint8)CANSM_FULLCOMMUNICATION;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* Check Bus Off Event occurred */
      if((CanSM_BusOffCntType)CANSM_ZERO != ptrNetwork->BusOffCounter)
      {
        /* Notify bus-off node to the BswM */
        /* polyspace +2 MISRA-C3:10.3 [Not a defect:Low] "The violation is acceptable because AUTOSAR specification does not support the type of argument " */
        BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(ptrStaticNetwork->CanSmNetworkHandle),
                                                      CANSM_BSWM_BOR_COMPLETE);
      }

      /* make the bus off counter zero */
      ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

      /* set bus off timer as CANSM_ZERO*/
      ptrNetwork->Timer = (CanSM_TimerType)CANSM_ZERO;


      #if(STD_ON == CANSM_DEM_STATUS)
      /* Notify DEM_EVENT_STATUS_PASSED to Dem*/
      if((uint16)CANSM_DEM_NO_EVENT != ptrStaticNetwork->BusOffEventId)
      {
        /* Report the error to DEM with event id and DEM_EVENT_STATUS_PASSED */
        (void)Dem_SetEventStatus(ptrStaticNetwork->BusOffEventId, (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
      }
      #endif
      /* Redmine 6235 */
    }
    else
    {
      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    }
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/*******************************************************************************
** Function Name        : CanSM_BORStart_FULL_T_BUSOFF                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts the bus of recovery procedure  **
**                        on bus off Occurence.                               **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                                                            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                                              BswM_CanSM_CurrentState()     **
**                                                                            **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BORStart_FULL_T_BUSOFF(
  VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Notify the network mode to the BswM */
  /* @Trace: CanSM_SUD_API_176 */
  BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_BUS_OFF);

  /* Notify bus-off node to the BswM */
  /* polyspace +2 MISRA-C3:10.3 [Not a defect:Low] "The violation is acceptable because AUTOSAR specification does not support the type of argument " */
  BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(ptrStaticNetwork->CanSmNetworkHandle),
                                                  CANSM_BSWM_BOR_START);
  /* Note: Notify BswM current Communication Mode */
  /* @Trace: CanSM_SUD_API_177 */
  currentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;
  /* Notify the current network mode to the ComM */
  ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle, currentState);

  /* check whether Dem is supported */
  #if(STD_ON == CANSM_DEM_STATUS)
  if((uint8)CANSM_DEM_NO_EVENT != ptrStaticNetwork->BusOffEventId)
  {
    /* @Trace: CanSM_SUD_API_178 */
    (void)Dem_SetEventStatus(ptrStaticNetwork->BusOffEventId,DEM_EVENT_STATUS_PREFAILED);
  }
  #endif/*End of if (STD_ON == CANSM_DEM_STATUS)*/
  /* Update the Internal Substate */
  ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_FULL_RESTART_CC;
} /* End of CanSM_BORStart_FULL_T_BUSOFF(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_BORStart_FULL_TX_OFF                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts the bus of recovery procedure  **
**                        on bus off Occurence.                               **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                                                            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                                              BswM_CanSM_CurrentState()     **
**                                                                            **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BORStart_FULL_TX_OFF(
  VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #if(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY)
  VAR(uint8,CANSM_VAR) BusOffDelayTime;
  #endif

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Update the Internal State as Zero */
  ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

  #if(STD_OFF == CANSM_ENABLE_BUS_OFF_DELAY)
  /* Check the counter value is equal to ZERO */

  /* Bus Off count is lower then CanSMBorCounterL1ToL2 */
  if (ptrStaticNetwork->BorCounterL1ToL2 != CANSM_ZERO)
  {
    /* Check the counter value to load Timer */
    if (ptrNetwork->BusOffCounter < (CanSM_BusOffCntType)(CANSM_BOR_L1TOL2 - CANSM_ONE))
    {
      /* Load CanSMBorTimeLVinay 1 Timer */
    /* @Trace: CanSM_SUD_API_181 */
      ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL1;

      /* Increment Bus Off Counter */
      ptrNetwork->BusOffCounter++;
    }
    /* Bus Off count is greater then CanSMBorCounterL1ToL2 */
    else
    {
      /* Load CanSMBorTimeL2 Timer */
    /* @Trace: CanSM_SUD_API_180 */
      ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2;

      /* Increment of BusOffCounter */
      ptrNetwork->BusOffCounter++;
    }
  }
  /* Bus Off count is greater then CanSMBorCounterL1ToL2 */
  else
  {
    /* Load CanSMBorTimeL2 Timer */
    /* @Trace: CanSM_SUD_API_198 */
    ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2;
    /* Bug #4872 */
    /* Increment of BusOffCounter */
    ptrNetwork->BusOffCounter++;
  }
  /* CanSMEnableBusOffDelay is TRUE */
  #else
  /* @Trace: CanSM_SUD_API_182 */
  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  if(CANSM_TRUE == CanSM_NwEnableBusOffDelay[CANSM_NETWORKHANDLE].CanSMEnableBusOffDelay)
  {
    /* call out to get bus off delay time */
    CANSM_GET_BUS_OFF_DELAY_FUNCTION(CANSM_NETWORKHANDLE,&BusOffDelayTime);

    /* assign bus off delay timer to to glocal variable */
    CanSM_BusOffDelayTime = (uint8)BusOffDelayTime;
  }
  else
  {
    /* set delay cycles to ZERO */
    CanSM_BusOffDelayTime= (uint8)CANSM_ZERO;
  }
  #else
  if((boolean)CANSM_TRUE == ptrStaticNetwork->CanSMEnableBusOffDelay)
  {
      /* call out to get bus off delay time */
      CANSM_GET_BUS_OFF_DELAY_FUNCTION(CANSM_NETWORKHANDLE,&BusOffDelayTime);

      /* assign bus off delay timer to to glocal variable */
      CanSM_BusOffDelayTime = (uint8)BusOffDelayTime;
  }
  else
  {
      /* set bus off delay cycle to ZERO */
      CanSM_BusOffDelayTime = (uint8)CANSM_ZERO;
  }
  #endif
  /* Check the counter value is equal to ZERO */
  if((CanSM_BusOffCntType)CANSM_ZERO != ptrStaticNetwork->BorCounterL1ToL2)
  {
    /* Bus Off count is lower then CanSMBorCounterL1ToL2 */
    /* Check the counter value to load Timer */
    if (ptrNetwork->BusOffCounter < (CanSM_BusOffCntType)(CANSM_BOR_L1TOL2 - CANSM_ONE))
    {
        #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
        if((boolean)CANSM_TRUE == CanSM_NwEnableBusOffDelay[CANSM_NETWORKHANDLE].CanSMEnableBusOffDelay)
        {
          /* Load CanSMBorTimeLVinay 1 Timer */
          ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL1 + CanSM_BusOffDelayTime;
        }
        else
        {
          /* Load CanSMBorTimeLVinay 1 Timer */
          ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL1;
        }
        #else
        if((boolean)CANSM_TRUE == ptrStaticNetwork->CanSMEnableBusOffDelay)
        {
            /* Load CanSMBorTimeLVinay 1 Timer */
            ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL1 + CanSM_BusOffDelayTime;
        }
        else
        {
            /* Load CanSMBorTimeLVinay 1 Timer */
            ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL1;
        }
        #endif
        /* Increment Bus Off Counter */
        ptrNetwork->BusOffCounter++;
    }
      /* Bus Off count is greater then CanSMBorCounterL1ToL2 */
    else
    {
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      if((boolean)CANSM_TRUE == CanSM_NwEnableBusOffDelay[CANSM_NETWORKHANDLE].CanSMEnableBusOffDelay)
      {
        /* Load CanSMBorTimeL2 Timer */
        ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2 + (CanSM_TimerType)CanSM_BusOffDelayTime;
      }
      else
      {
        /* Load CanSMBorTimeLVinay 1 Timer */
        ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2;
      }
      #else
      if((boolean)CANSM_TRUE == ptrStaticNetwork->CanSMEnableBusOffDelay)
      {
          /* Load CanSMBorTimeLVinay 1 Timer */
          ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2 + (CanSM_TimerType)CanSM_BusOffDelayTime;
      }
      else
      {
          /* Load CanSMBorTimeLVinay 1 Timer */
          ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2;
      }
      #endif

      /* Increment of Bus Off counter */
      ptrNetwork->BusOffCounter++;
      }
  }
    /* Bus Off count is greater then CanSMBorCounterL1ToL2 */
  else
  {
      /* Load CanSMBorTimeL2 Timer */
      ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIMEL2 + CanSM_BusOffDelayTime;

      /* Increment of Bus Off counter */
      ptrNetwork->BusOffCounter++;
  }
  #endif
  /* Redmine 6235 */
  /* Enter Protection Area */
  SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
  if(ptrNetwork->BusOffRep != 1)
  {
    /* Change internal status */
    ptrNetwork->ModeStatus = (uint8)CANSM_BORWAIT;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }
  else
  {
    /* Change internal status */
    ptrNetwork->ModeStatus = (uint8)CANSM_BORSTART;

    /* update internal sub state machine as CANSM_ZERO */
    ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

    /* reset Bus Off repetition to CANSM_ZERO */
    ptrNetwork->BusOffRep = (uint8)CANSM_ZERO;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();  
  }
} /* End of CanSM_BORStart_FULL_TX_OFF(VAR(NetworkHandleType,CANSM_VAR) networkHandle) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_NoToFullCommRequested_PREFULL_CC_ONLINE       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION for the corresponding      **
**                        network handle.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_Network             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                CanIf_SetPduMode()                          **
**                                BswM_CanSM_CurrentState()                   **
**                                ComM_BusSM_ModeIndication()                 **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_NoToFullCommRequested_PREFULL_CC_ONLINE(
  VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* Get the address of CanSM_StaticNw to local pointer */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  /* Get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* Initial value as Wait State */
  result = (uint8)CANSM_E_WAITSTATE;

  /* reset requested repeat time */
  ptrNetwork->CanSMModeReqReptTime =
    (CanSM_TimerType)CanSm_ModeReqRepeatTime;

  /* Reset the Mode repetition request*/
  ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

  /* update internal sub state machine as CANSM_ZERO */
  ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

  /* Enter Protection Area */
  SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

  /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
  ptrNetwork->ModeStatus = (uint8)CANSM_CHECKBUSOFF;

  /* Exit Protection Area */
  SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

  /* set Pdu Mode to CANIF_TX_OFFLINE_ACTIVE in case ECU is passive */
  if((CanSM_ECUPassiveType)CANSM_ECUPASSIVE == CanSM_ECUPassive)
  {
    /* @Trace: CanSM_SUD_API_141 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_TX_OFFLINE_ACTIVE);
  }
  /* set Pdu Mode to CANIF_ONLINE in case ECU is not passive */
  else
  {
    /* @Trace: CanSM_SUD_API_140 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_ONLINE);
  }
  /* Internal state COMM_FULL_COMMUNICATION */
  /* @Trace: CanSM_SUD_API_143 */
  currentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

  /* Notify internally stored network mode to the ComM */
  ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

  /* Notify internally stored network mode to the BsWM */
  /* @Trace: CanSM_SUD_API_144 */
  BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_FULL_COMMUNICATION);
  
  #if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)
  /* Load timer as CANSM_ONE */
  ptrNetwork->Timer = (CanSM_TimerType)CANSM_ONE;
  #else
  /* Load TX_ENSURED Timer to network timer */
  ptrNetwork->Timer = (CanSM_TimerType)CANSM_BOR_TIME_TXENSURED;
  #endif
  return(result);
} /* End of CanSM_NoToFullCommRequested_PREFULL_CC_ONLINE */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_WakeUpToFullComRequested_PREFULL_CC_ONLINE    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION from WUVALIDATION          **
**                        for the corresponding network handle.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                       SchM_Enter_CanSM_MODE_STATUS_PROTECTION()            **
**                       SchM_Exit_CanSM_MODE_STATUS_PROTECTION()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType,CANSM_CODE) CanSM_WakeUpToFullComRequested_PREFULL_CC_ONLINE(VAR(NetworkHandleType,CANSM_VAR) networkHandle)
{
  P2CONST(CanSM_StaticNetworkType,AUTOMATIC,CANSM_CONST) ptrStaticNetwork;
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  VAR(Std_ReturnType, CANSM_VAR) result;

  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;

  /* initialize result as CANSM_E_WAITSTATE */
  result = (uint8)CANSM_E_WAITSTATE;

  /* get the address of CanSM_Network to local pointer */
  ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

  /* get the address of CanSM_StaticNw */
  ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

  ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

  /* Reset the mode repetition request */
  ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

  /* set internal sub state to Zero */
  ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

  /* Enter protection area */
  SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

  /* Set the mode status of CanSM to CANSM_CHECKBUSOFF */
  ptrNetwork->ModeStatus = (uint8)CANSM_CHECKBUSOFF;

  /* Exit protection area */
  SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

  /* Check status of CanSM_ECUPassive*/
  if((CanSM_ECUPassiveType)CANSM_ECUPASSIVE == CanSM_ECUPassive)
  {
    /* @Trace: CanSM_SUD_API_104 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_TX_OFFLINE_ACTIVE);
  }
  else
  {
    /* @Trace: CanSM_SUD_API_105 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] It has been cover by geneeration code */ 
    CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex,CANIF_ONLINE);
  }
  /* Set currentState to COM_FULL_COMMUNICATION */
  currentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

  /* Notify ComM with COMM_FULL_COMMUNICATION */
  /* @Trace: CanSM_SUD_API_106 */
  ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

  /* Notify BswM with Network handle and CANSM_BSWM_FULL_COMMUNICATION */
  /* @Trace: CanSM_SUD_API_107 */
  BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_FULL_COMMUNICATION);
  
  return(result);
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
