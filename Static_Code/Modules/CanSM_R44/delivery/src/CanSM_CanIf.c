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
**  SRC-MODULE: CanSM_CanIf.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
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
** 1.0.9_HF1   23-Feb-2024   MU Kim         CP44-2851                         **
** 1.0.8       02-Mar-2023   HieuTM8        #CP44-1771                        **
** 1.0.7       03-Feb-2023   HieuTM8        #CP44-1630                        **
** 1.0.6       12-Dec-2022   HieuTM8        #CP44-1312                        **
** 1.0.3       25-Jul-2022   HieuTM8        CP44-511                          **
** 1.0.2       24-Mar-2022   HieuTM8        R44-Redmine #25572                **
** 1.0.1       14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306         **
** 1.0.0       04-Dec-2020   SMKwon         Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_CanIf.h"          /* CanSM Cbk header file */
#include "CanSM_Internal.h"       /* CanSM Main header file */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanSM_Error.h"          /* CanSM_Error header file */
#include "BswM_CanSM.h"           /* BswM_CanSM header file */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#include "CanNm.h"                 /* CanNm header file */
#endif
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_CANIF_C_RELEASE_MAJOR_VERSION       0x04u
#define CANSM_CANIF_C_RELEASE_MINOR_VERSION       0x04u
#define CANSM_CANIF_C_RELEASE_REVISION_VERSION    0x00u

/* CANSM software version information */
#define CANSM_CANIF_C_SW_MAJOR_VERSION            0x01u
#define CANSM_CANIF_C_SW_MINOR_VERSION            0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_CANIF_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_CANIF_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_CANIF_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_CANIF_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_CANIF_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/


/*******************************************************************************
** Function Name        : CanSM_ControllerBusOff                              **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : The CanSM is notified about a bus-off event on a    **
**                        certain CAN controller with this call out function. **
**                        It shall execute the bus-off recovery state machine **
**                        for the corresponding network handle.               **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(uint8,CANSM_VAR) Controller                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_InitStatus              **
**                                              CanSM_StaticNw                **
**                                              CanSM_Network                 **
**                        Function(s) invoked :                               **
**                                Det_ReportError()                           **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
/* @Trace: SRS_BSW_00359 SRS_BSW_00333 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_033 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(VAR(uint8,CANSM_VAR) Controller)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  /*add by jslim*/
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

  VAR(NetworkHandleType,CANSM_VAR) networkHandle;

  /* MISRA Rule    : 14.2
     Message       : This statement has no side affect
     Reason        : ConfigPtr is not used since its pre compile
     Verification  : However, part of the code is verified manually and it
                     is not having any impact.
  */

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* Check if CanSM is uninitialised */
  /* polyspace<MISRA-C:16.10 : Low : Justify with annotations> Known issue */

  /* polyspace +5 RTE:UNR [Not a defect:Low] "According to requirements, the init status should be checked before any further processing" */
  /* Note: check initialization and report Errors to DET if any */
  /* @Trace: CanSM_SUD_API_034 */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_CONTROLLERBUSOFF);
  
  if((Std_ReturnType)E_OK == result)
  {
    /* polyspace +5 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
    /* Note: check network validity and Report errors if any */
    /* @Trace: CanSM_SUD_API_035 */
    CANSM_CHECK_INVALID_CONTROLLER(result, Controller,CANSMSERVICEID_CONTROLLERBUSOFF);
  }
  if ((Std_ReturnType)E_OK == result)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {

    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : Controller is already checked in advanced with a macro expansion which is CANSM_CHECK_INVALID_CONTROLLER
     */
     /* get the network id which contain the controller */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_CtrlIDToNW[Controller];
    #else
    networkHandle = CanSM_InternalController[Controller];
    #endif
    /* Get the address of the Network corresponding to the controller */
    ptrNetwork = &CanSM_Network[networkHandle];

    /* Get the address of CanSM_StaticNw to local pointer */
    ptrStaticNetwork = &CanSM_StaticNw[networkHandle];

    /* Note: CanSM_ControllerBusOff shall trigger CANSM_BSM_S_FULLCOM with T_BUS_OFF */
    /* @Trace: CanSM_SUD_API_060 */
    if (((uint8)CANSM_BORSTART == ptrNetwork->ModeStatus)
        ||((uint8)CANSM_BORWAIT == ptrNetwork->ModeStatus)
        ||((uint8)CANSM_FULLCOMMUNICATION == ptrNetwork->ModeStatus)
        ||((uint8)CANSM_CHECKBUSOFF == ptrNetwork->ModeStatus))
    {
    /* if COMM_NO_COMMUNICATION is the latest requested mode */
    if ((uint8)COMM_NO_COMMUNICATION == ptrNetwork->ReqModeStatus)
    {

      /* Update Internal Substate as Zero*/
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      /* Update Internal Timer as Zero*/
      ptrNetwork->Timer = (CanSM_TimerType)CANSM_ZERO;

      /* Update Internal BusOffCounter as Zero*/
      ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

      /* polyspace +2 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
      /* Notify the network mode to the BswM */
      BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);

      /* Enter Protection Area */
      SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();

      #if (STD_ON == CANSM_PNC_AVAILABILITY)
    
        /* Check if PN is supported */
      if ((boolean)CANSM_TRUE == CanSM_StaticNw[networkHandle].pnSupported)
      {

        /* Note: guarding condition CANSM_BSM_G_PN_SUPPORTED */
        /* Update the Mode status as DeInitPnSupported */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;

      }
      else
      {
        /* Update the mode status as CANSM_DEINITPNNOTSUPPORTED */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;

      }
      #else /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */

      /* Update the mode status as CANSM_DEINITPNNOTSUPPORTED */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;

      #endif /* End of if (STD_ON == CANSM_PNC_AVAILABILITY) */

      /* Exit protection Area */
       SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
    }
    else if((uint8)CANSM_SILENTCOMMUNICATION == ptrNetwork->ReqModeStatus)
    {
        /* reset requested repeat time */
        ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

        /* Reset the Mode repetition request*/
        ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

        /* Update Internal Substate as Zero*/
        ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

        /* reset BusOff counter value to CANSM_ZERO */
        ptrNetwork->BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

        /* Update Internal Timer as Zero*/
        ptrNetwork->Timer = (CanSM_TimerType)CANSM_ZERO;

        /*Enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /*Update a change of Mode status*/
        ptrNetwork->ModeStatus = (uint8)CANSM_SILENTCOMMUNICATION_BOR;

        /*Exit protection area*/
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    }
    else if(ptrNetwork->ModeStatus <= CANSM_CHECKBUSOFF)
    {

      /* Bug #703 - Add to check duplicate Bus off Event while Bus Off Recovery */
      if(CANSM_BORSTART != ptrNetwork->ModeStatus)
      {    
        /* Update Internal Substate as Zero*/
        ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

        /* reset requested repeat time */
        ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

        /* Reset the Mode repetition request*/
        ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;


        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();

        /* Set the BusOff status to True */
        ptrNetwork->ModeStatus = (uint8)CANSM_BORSTART;

        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      }
      else
      {

        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();

        ptrNetwork->BusOffRep = ptrNetwork->BusOffRep + CANSM_ONE;
              
        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      }

    }
    else
    {
      
    }

  }

  }
} /* End of CanSM_ControllerBusOff(uint8 Controller) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_ConfirmPnAvailability                         **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : The CanSM is notified about the availability of     **
**                        Partial networking foa a certain CAN Transceiver    **
**                        It shall intern call the CanNm_ConfirmPnAvailability**
**                        with the related CAN network as channel to confirm  **
**                        the PN availability to the CanNm module.            **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(uint8,CANSM_VAR) Transceiver                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_InitStatus              **
**                                              CanSM_StaticNw                **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CanNm_ConfirmPnAvailability   **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_052 */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(VAR(uint8,CANSM_VAR) Transceiver)
{
  VAR(NetworkHandleType,CANSM_VAR) networkHandle;
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANSM_VAR) result;


  /* Note: Check Initialization and report errors to DET if any */
  /* @Trace: CanSM_SUD_API_053 */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_CONFIRMPNAVAILABILTY);


  if((Std_ReturnType)E_OK == result)
  {
     /* check the invalidity of TransceiverId */
	 /* @Trace: CanSM_SUD_API_054 */
     CANSM_CHECK_INVALID_TRANSCEIVERID(result,Transceiver, CANSMSERVICEID_CONFIRMPNAVAILABILTY);

  }
  if ((Std_ReturnType)E_OK == result)
  {
      /* check the validity of network Id */
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      CANSM_VALID_TRCV_NETWORK_CHECK(result,CanSM_TrcvIdToNwIndex[Transceiver],CANSMSERVICEID_CONFIRMPNAVAILABILTY);
      #else
      CANSM_VALID_TRCV_NETWORK_CHECK(result,CanSM_StaticTrvToNw[Transceiver],CANSMSERVICEID_CONFIRMPNAVAILABILTY);
      #endif
  }
  if ((Std_ReturnType)E_OK == result)
  #endif
  {
    /* get network index which contain the transceiver */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_TrcvIdToNwIndex[Transceiver];
    #else
    networkHandle = CanSM_StaticTrvToNw[Transceiver];
    #endif
    /* notify CanNm Module with appropriate channel */
    /* @Trace: CanSM_SUD_API_055 */
    CanNm_ConfirmPnAvailability(CanSM_StaticNw[networkHandle].CanSmNetworkHandle);


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Transceiver is already checked in advanced already
     */

  }
} /* End of CanSM_ConfirmPnAvailability(uint8 Transceiver) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANSM_PNC_AVAILABILITY ) */


/*******************************************************************************
** Function Name        : CanSM_TxTimeoutException                            **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : The CanSM is notified that the CanNm has detected   **
**                        for the affected partial CAN network a tx timeout   **
**                        exception.                                          **
**                        The CanSM shall recover this a transition to no     **
**                        communication and back to the requested             **
**                        communication mode again.                           **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) Channel            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_InitStatus              **
**                                              CanSM_Network                 **
**                        Function(s) invoked :                               **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
**                                Det_ReportError()                           **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_Can_01145 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_043 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(VAR(NetworkHandleType,CANSM_VAR) Channel)
{
  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;
  VAR(ComM_ModeType,CANSM_VAR) currentState;
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

  VAR(Std_ReturnType, CANSM_VAR) result;
  
  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;
  
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* polyspace +5 RTE:UNR [Not a defect:Low] "According to requirements, the init status should be checked before any further processing" */
  /* @Trace: CanSM_SUD_API_044 */
  /* Note: check initialization and report errors to DET if any */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_TXTIMEOUTEXCEPTION);

  if((Std_ReturnType)E_OK == result)
  {
    /* polyspace +5 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
    /* @Trace: CanSM_SUD_API_045 */
    /* Note: Check the invalidity of the input */
    CANSM_CHECK_INVALID_NETWORK(result, Channel,CANSMSERVICEID_TXTIMEOUTEXCEPTION);
  }
  if ((Std_ReturnType)E_OK == result)
  {
      /* polyspace +14 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
      /* check the validity of the network  */
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_NwIdToIndex[Channel],CANSMSERVICEID_TXTIMEOUTEXCEPTION);
      #else
      CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_InternalNetwork[Channel],CANSMSERVICEID_TXTIMEOUTEXCEPTION);
      #endif
    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Channel is already checked in advanced already
     */
  }

  if ((Std_ReturnType)E_OK == result)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
     /* get the network index which contain the controller */
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     networkHandle = CanSM_NwIdToIndex[Channel];
     #else
     networkHandle = CanSM_InternalNetwork[Channel];
     #endif

    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : Channel is already checked in advanced with a macro expansion which is CANSM_CHECK_INVALID_NETWORK
     */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* Note: trigger Full Communication sub state machine */
    /* @Trace: CanSM_SUD_API_086 */
    if((uint8)CANSM_FULLCOMMUNICATION == ptrNetwork->ModeStatus)
    {

      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Load the mode status to the network variable */
      ptrNetwork->ModeStatus = (uint8)CANSM_TXTIMEOUTEXCEPTION;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  
    }

    if((uint8)CANSM_TXTIMEOUTEXCEPTION == ptrNetwork->ModeStatus)
    {
      /* #14496 */
      /* Get the address of CanSM_StaticNw to local pointer */
      ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

      /* initialize result as E_NOT_OK */
      result = (uint8)E_NOT_OK;
  
      /* Set the current mode of the network */
      currentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;
  
      /* Notify the current network mode to the ComM */
      ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

      /* Check if Internal State is equal to CANSM_TIMEOUT_CC_STOPPED  */
      if ((uint8)CANSM_TIMEOUT_CC_STOPPED == ptrNetwork->CanSMNWIntSubState)
      {
        /* @Trace: CanSM_SUD_API_083 */
        ptrNetwork->Mode = (uint8)CAN_CS_STOPPED;
        /* Set the Controller mode as CAN_CS_STOPPED */
        result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STOPPED);
      }
  
      /* Check if Internal State is equal to CANSM_TIMEOUT_CC_STARTED  */
      if ((uint8)CANSM_TIMEOUT_CC_STARTED == ptrNetwork->CanSMNWIntSubState)
      {
        /* @Trace: CanSM_SUD_API_084 */
        ptrNetwork->Mode = (uint8)CAN_CS_STARTED;
        /* Set the Controller mode as CAN_CS_STARTED */
        result = CanSM_SetCanControllerMode(CANSM_NETWORKHANDLE, CAN_CS_STARTED);
      }
  
      /* Check if Internal State is equal to CANSM_TIMEOUT_CC_ONLINE  */
      /* @Trace: CanSM_SUD_API_085 */
      if ((uint8)CANSM_TIMEOUT_CC_ONLINE == ptrNetwork->CanSMNWIntSubState)
      {
        /* Set the current mode of the network */
        currentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;
    
        /* Notify the current network mode to the ComM */
        ComM_BusSM_ModeIndication(ptrStaticNetwork->CanSmNetworkHandle,currentState);

        ptrNetwork->CanSMModeReqReptTime =
          (CanSM_TimerType)CanSm_ModeReqRepeatTime;

        /* Reset the Mode repetition request*/
        ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

        /* Update the Internal SubState with the value as Zero*/
        ptrNetwork->CanSMNWIntSubState = CANSM_ZERO;

        /* #14496 */
        /* @Trace: CanSM_SUD_API_093 */
        CANIF_SETPDUMODE(ptrStaticNetwork->ControllerIndex, CANIF_ONLINE)

        /* Enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Set the mode of the CanSM to ONLINE state */
        ptrNetwork->ModeStatus = CANSM_FULLCOMMUNICATION;

        /* Exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

        /* Initiate the Full Communication for the network */
        CanSM_FullCommunication(CANSM_NETWORKHANDLE);
      } /* End of if (CANSM_TIMEOUT_CC_ONLINE == ptrNetwork->CanSMNWIntSubState) */
      
      else
      {
        /* update result as wait state */
        result = (uint8)CANSM_E_WAITSTATE;
      }

      if ((Std_ReturnType)E_OK == result)
      {
        /* Load the request Repetition Time value in the Local variable */
        ptrNetwork->CanSMModeReqReptTime =
          (CanSM_TimerType)CanSm_ModeReqRepeatTime;
      }

      else
      {
        /* Call the function for Time Out Processing */
        /* @Trace: CanSM_SUD_API_082 */
        CanSM_TimeoutProcessing(CANSM_NETWORKHANDLE, result);
      }	
    }
  } 
  #else
  CANSM_UNUSED(Channel);
  #endif /* End of #if (STD_ON == CANSM_PNC_AVAILABILITY)*/
} /* End of CanSM_TxTimeoutException(NetworkHandleType Channel) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_TransceiverModeIndication                     **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service notifies about the mode Indication.    **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(uint8,CANSM_VAR) Transceiver                    **
**                        VAR(CanTrcv_TrcvModeType,CANSM_VAR) TransceiverMode **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :  CanSM_Network                **
**                                               CanSM_Initstatus             **
**                        Function(s) invoked :                               **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                chM_Exit_CanSM_MODE_STATUS_PROTECTION()     **
**                                Dem_SetEventStatus                          **
**                                Det_ReportError()                           **
*******************************************************************************/

/* @Trace: SRS_Can_01145 SRS_Can_01142 SRS_BSW_00466 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_040 */
#if (STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(VAR(uint8,CANSM_VAR) Transceiver,
    VAR(CanTrcv_TrcvModeType,CANSM_VAR) TransceiverMode)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;

  #if(STD_ON == CANSM_DEM_STATUS)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC,CANSM_CONST) ptrStaticNetwork;
  #endif


  VAR(Std_ReturnType, CANSM_VAR) result;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* Note: check module initialization */
  /* @Trace: CanSM_SUD_API_041 */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_TRCVMODEINDICATION);

  /* @Trace: CanSM_SUD_API_042 */
  if ((Std_ReturnType)E_OK == result)
  {
    CANSM_CHECK_INVALID_TRANSCEIVERID(result, Transceiver,CANSMSERVICEID_TRCVMODEINDICATION);
  }
  if ((Std_ReturnType)E_OK == result)
  {
    /* Check the validity of networkhandle */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    CANSM_VALID_TRCV_NETWORK_CHECK(result, (CanSM_TrcvIdToNwIndex[Transceiver]),CANSMSERVICEID_TRCVMODEINDICATION);
    #else
    CANSM_VALID_TRCV_NETWORK_CHECK(result, (CanSM_StaticTrvToNw[Transceiver]),CANSMSERVICEID_TRCVMODEINDICATION);
    #endif
  }
  /* Check if E_OK is returned */
  if ((Std_ReturnType)E_OK == result)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {

    /* get the network id which contains the Transceiver */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_TrcvIdToNwIndex[Transceiver];
    #else
    networkHandle = CanSM_StaticTrvToNw[Transceiver];
    #endif

    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];
    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Transceiver is already checked in advanced already
     */

    #if(STD_ON == CANSM_DEM_STATUS)
    /*Get address of static Network */
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
    #endif

    /* Check if requested mode is equal to indicated mode */
    if ((uint8)TransceiverMode == ptrNetwork->Mode)
    {
      /* Load the Maximun repeated times to local variable */
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* clear internal mode indication  */
      ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + CANSM_ONE;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      /* check whether Dem is supported */
      #if(STD_ON == CANSM_DEM_STATUS)
      /* polyspace +1 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
      if((uint16)CANSM_DEM_NO_EVENT != ptrStaticNetwork->TimeOutEventId)
      {
        (void)Dem_SetEventStatus(ptrStaticNetwork->TimeOutEventId,DEM_EVENT_STATUS_PREPASSED);
      }
      #endif

    } /* End of if (LMode == ptrNetwork->Mode) */
    else
    {
      /* set result to E_NOT _OK */
      result = (Std_ReturnType)E_NOT_OK;

      /* Load the request Repetition Time value in the Local variable */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      CanSM_TimeoutProcessing(networkHandle,result);
    }
  }
} /* End of CanSM_TransceiverModeIndication(uint8 Transceiver, uint8 LMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if(STD_ON == CANSM_CANTRCV_SUPPORT) */


/*******************************************************************************
** Function Name        : CanSM_ControllerModeIndication                      **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service notifies about the mode Indication.    **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(uint8,CANSM_VAR) Controller                     **
**                        VAR(Can_ControllerStateType,CANSM_VAR)              **
**                          ControllerMode                                    **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_Initstatus              **
**                        Function(s) invoked :
**                                 SchM_Enter_CanSM_MODE_STATUS_PROTECTION()  **
**                                 SchM_Exit_CanSM_MODE_STATUS_PROTECTION()   **
**                                 Dem_SetEventStatus                         **
**                                 Det_ReportError()                          **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_BSW_00466 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_037 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(VAR(uint8,CANSM_VAR) Controller, VAR(Can_ControllerStateType,CANSM_VAR) ControllerMode)
{

  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(uint8, CANSM_VAR) noOfController;
  VAR(Std_ReturnType, CANSM_VAR) result;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;


  #if(STD_ON == CANSM_DEM_STATUS)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #endif




  /* Note: check module initialization and report errors to DET if any */
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* Check if CanSM is uninitialized  */
  /* polyspace<MISRA-C:16.10 : Low : Justify with annotations> Known issue */
  /* @Trace: CanSM_SUD_API_038 */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_CHECKCONTRLMODEINDICATON);
  
  if((Std_ReturnType)E_OK == result)
  {

    /* Note: check network validity and report errors to DET if any */
	/* @Trace: CanSM_SUD_API_039 */
    CANSM_CHECK_INVALID_CONTROLLER(result, Controller,CANSMSERVICEID_CHECKCONTRLMODEINDICATON);
  }
  /* Check if E_OK is returned */
  if ((Std_ReturnType)E_OK == result)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
    /* get the network index which contain the controller */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_CtrlIDToNW[Controller];
    #else
    networkHandle = CanSM_InternalController[Controller];
    #endif

    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Controller is already checked in advanced already
     */
    /* Get the addres of the Network corresponding to the controller */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    #if(STD_ON == CANSM_DEM_STATUS)
    /* Get the address of Static network */
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

    #endif

    /* Check if requested mode is equal to indicated mode */
    if ((uint8)ControllerMode == ptrNetwork->Mode)
    {
      /* polyspace +2 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
      /* Get the number of controller for the corresponding network */
      noOfController = CanSM_StaticNw[CANSM_NETWORKHANDLE].NumberOfController;

      /* if there is only one controller in the network */
      if((uint8)CANSM_ONE != noOfController)
      {
        /* Increment the Controller count */
        ptrNetwork->CanSMCtrlCount++;

        /* Check if Number of controller is equal to controller in the Network*/
        if (noOfController == ptrNetwork->CanSMCtrlCount)
        {
          /* Assign zero value to the Controller count */
          ptrNetwork->CanSMCtrlCount = (uint8)CANSM_ZERO;

          /* Load the Maximun repeated times to local variable */
          ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

          /* Enter Protection Area */
          SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

          /* Upadte the Internal Network SubState */
          ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + CANSM_ONE;

          /* Exit Protection Area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
        } /* End of if (noOfController == ptrNetwork->CanSMCtrlCount) */

      }
      else
      {
        /* Load the Maximun repeated times to local variable */
        ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

        /* Enter Protection Area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Upadte the Internal Network SubState */
        ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + CANSM_ONE;

        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      }
      /* check whether Dem is supported */
      #if(STD_ON == CANSM_DEM_STATUS)
      /* Note: Notify DEM_EVENT_STATUS_PREPASSED event to DEM */
      /* polyspace +1 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
      if((uint16)CANSM_DEM_NO_EVENT != ptrStaticNetwork->TimeOutEventId)
      {
        (void)Dem_SetEventStatus(ptrStaticNetwork->TimeOutEventId,DEM_EVENT_STATUS_PREPASSED);
      }
      #endif
    } /* End of if (ControllerMode == ptrNetwork->Mode) */
    else
    {
      /* set result to E_NOT_OK */
      result = (Std_ReturnType)E_NOT_OK;
      /* Load the request Repetition Time value in the Local variable */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      CanSM_TimeoutProcessing(networkHandle,result);
    }
  }
} /* End of CanSM_ControllerModeIndication(uint8 Controller,
   *Can_ControllerStateType ControllerMode) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_CheckTransceiverWakeFlagIndication            **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : This callback function indicates the                **
**                      CanIf_CheckTrcvWakeFlag API process end               **
**                      for the notified CAN Transceiver.                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(uint8,CANSM_VAR) Transceiver                    **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_StaticNw                **
**                                              CanSM_Initstatus              **
**                        Function(s) invoked :                               **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
**                                Dem_SetEventStatus                          **
**                                Det_ReportError()                           **
*******************************************************************************/

/* @Trace: SRS_Can_01145 SRS_BSW_00466 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_049 */
#if((STD_ON == CANSM_CANTRCV_SUPPORT)&&(STD_ON == CANSM_PNC_AVAILABILITY))
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
FUNC(void,CANSM_CODE) CanSM_CheckTransceiverWakeFlagIndication(VAR(uint8,CANSM_VAR) Transceiver)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;
  #if(STD_ON == CANSM_DEM_STATUS)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #endif


  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  VAR(Std_ReturnType, CANSM_VAR) result;


  /* Note: check module initialization */
  /* @Trace: CanSM_SUD_API_050 */
  CANSM_INITED_DET_CHECK(result,CANSMSERVICEID_CHKTRCVWUFFLAGINDCN);
  if((Std_ReturnType)E_OK == result)
  {
      /* check the invalidity of TransceiverId */
	  /* @Trace: CanSM_SUD_API_051 */
      CANSM_CHECK_INVALID_TRANSCEIVERID(result,Transceiver, CANSMSERVICEID_CHKTRCVWUFFLAGINDCN);
  }
  if((Std_ReturnType)E_OK == result)
  {
      /* Det check for invalidity of network index */
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      CANSM_VALID_TRCV_NETWORK_CHECK(result,CanSM_TrcvIdToNwIndex[Transceiver],CANSMSERVICEID_CHKTRCVWUFFLAGINDCN);
      #else
      CANSM_VALID_TRCV_NETWORK_CHECK(result,CanSM_StaticTrvToNw[Transceiver],CANSMSERVICEID_CHKTRCVWUFFLAGINDCN);
      #endif
  }
  if((Std_ReturnType)E_OK == result)
  #endif
  {
    /* get network index which contain the transceiver */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_TrcvIdToNwIndex[Transceiver];
    #else
    networkHandle = CanSM_StaticTrvToNw[Transceiver];
    #endif


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Transceiver is already checked in advanced already
     */
    /* check whether Dem is supported */
    #if(STD_ON == CANSM_DEM_STATUS)
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
    #endif

     /* get address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];


    if((uint8)CANSM_DEINITPNSUPPORTED == ptrNetwork->ModeStatus)
    {
        if(((uint8)CANSM_PN_TRCV_CLEAR_WUF_WAIT == ptrNetwork->CanSMNWIntSubState)
                ||(((uint8)CANSM_PN_WFLAG_IN_NOT_CC_SLEEP_WAIT)== ptrNetwork->CanSMNWIntSubState))
        {
          /* Load the Maximun repeated times to local variable */
          ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;
          /* Enter protection area */
          SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

          /* set internal substate to CANSM_PN_NO_COMMUNICATION */
          ptrNetwork->CanSMNWIntSubState = ptrNetwork->CanSMNWIntSubState + CANSM_ONE;

          /* Exit protection area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

          /* check whether Dem is supported */
          #if(STD_ON == CANSM_DEM_STATUS)
          /* DEM_EVENT_STATUS_PREPASSED event status shall be notified to DEM */

          if((uint16)CANSM_DEM_NO_EVENT != ptrStaticNetwork->TimeOutEventId)
          {
            (void)Dem_SetEventStatus(ptrStaticNetwork->TimeOutEventId,DEM_EVENT_STATUS_PREPASSED);
          }

          #endif

       }
    }
  }
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if (STD_ON == CANSM_CANTRCV_SUPPORT) and (STD_ON == CANSM_PNC_AVAILABILITY) */


/*******************************************************************************
** Function Name        : CanSM_ClearTrcvWufFlagIndication                    **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This callback function shall indicate the           **
**                      CanIf_ClearTrcvWufFlag API process end                **
**                      for the notified CAN Transceiver.                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(uint8,CANSM_VAR) Transceiver                    **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_StaticNw                **
**                                              CanSM_Initstatus              **
**                        Function(s) invoked :
**                            SchM_Enter_CanSM_MODE_STATUS_PROTECTION()       **
**                            SchM_Exit_CanSM_MODE_STATUS_PROTECTION()        **
**                            Dem_SetEventStatus                              **
**                            Det_ReportError()                               **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_BSW_00466 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_046 */
#if((STD_ON == CANSM_CANTRCV_SUPPORT)&&(STD_ON == CANSM_PNC_AVAILABILITY))
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
FUNC(void,CANSM_CODE) CanSM_ClearTrcvWufFlagIndication(VAR(uint8,CANSM_VAR) Transceiver)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;

  #if(STD_ON == CANSM_DEM_STATUS)
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  #endif

  #if(STD_ON == CANSM_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANSM_VAR) result;

  /* Note: check module initialization */
  /* @Trace: CanSM_SUD_API_047 */
  CANSM_INITED_DET_CHECK(result,CANSMSERVICEID_CLRTRCVWUFFLAGINDCN);
  if((Std_ReturnType)E_OK == result)
  {
     /* check the invalidity of TransceiverId */
	  /* @Trace: CanSM_SUD_API_048 */
     CANSM_CHECK_INVALID_TRANSCEIVERID(result,Transceiver, CANSMSERVICEID_CLRTRCVWUFFLAGINDCN);

  }
  /* Note: check network validity */
  if((Std_ReturnType)E_OK == result)
  {
    /* Det check for the validity of network index */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    CANSM_VALID_TRCV_NETWORK_CHECK(result,CanSM_TrcvIdToNwIndex[Transceiver],CANSMSERVICEID_CLRTRCVWUFFLAGINDCN);
    #else
    CANSM_VALID_TRCV_NETWORK_CHECK(result,CanSM_StaticTrvToNw[Transceiver],CANSMSERVICEID_CLRTRCVWUFFLAGINDCN);
    #endif
  }
  if((Std_ReturnType)E_OK == result)
  #endif
  {
    /* get network index which contain the transceiver */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_TrcvIdToNwIndex[Transceiver];
    #else
    networkHandle = CanSM_StaticTrvToNw[Transceiver];
    #endif


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Transceiver is already checked in advanced already
     */

    #if(STD_ON == CANSM_DEM_STATUS)
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];
    #endif
    /* get address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];
    /* @Trace: CanSM_SUD_API_070 */
    if((uint8)CANSM_DEINITPNSUPPORTED == ptrNetwork->ModeStatus)
    {
      if((uint8)CANSM_PN_CLEAR_WUF_WAIT == ptrNetwork->CanSMNWIntSubState)
      {
        /* Load the Maximun repeated times to local variable */
        ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

        /* Enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* set internal substate to CANSM_PN_NO_COMMUNICATION */
        ptrNetwork->CanSMNWIntSubState = CANSM_PN_CC_STOPPED;

        /* Exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

        /* check whether Dem is supported */
        #if(STD_ON == CANSM_DEM_STATUS)
        /* Note: DEM_EVENT_STATUS_PREPASSED Event status shall be notified to DEM */
        if((uint16)CANSM_DEM_NO_EVENT != ptrStaticNetwork->TimeOutEventId)
        {
        	/* @Trace: CanSM_SUD_API_072 */
          (void)Dem_SetEventStatus(ptrStaticNetwork->TimeOutEventId,DEM_EVENT_STATUS_PREPASSED);
        }
        #endif
      } 
      else if((uint8)CANSM_PN_TRCV_CLEAR_WUF == ptrNetwork->CanSMNWIntSubState)
      {
        /* Enter protection area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* set internal substate to CANSM_PN_NO_COMMUNICATION */
        ptrNetwork->CanSMNWIntSubState = CANSM_PN_CC_STOPPED;

        /* Exit protection area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      }
      else
      {
        /* Nothing to do */
      }
    }
 }
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if (STD_ON == CANSM_CANTRCV_SUPPORT) and (STD_ON == CANSM_PNC_AVAILABILITY) */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
