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
**  SRC-MODULE: CanSM.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Implemetation for CanSM's features:                           **
**                Initialization and de-initialization                        **
**                Start and Stop WakeUP source                                **
**                version information                                         **
**                ECU passive                                                 **
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
** 1.0.6     12-Dec-2022   HieuTM8        #CP44-1312                          **
** 1.0.3     25-Jul-2022   HieuTM8        CP44-511                            **
** 1.0.2     24-Mar-2022   HieuTM8        R44-Redmine #25572                  **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"               /* Inclusion of CanSM header */
#if(STD_ON == CANSM_DEM_STATUS)
#include "Dem.h" /* Dem header file */
#endif

#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h" /* Det header file */
#endif
#include "CanIf.h" /* CanIf header file */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#include "CanNm.h" /* CanNm header file */
#endif
#include "SchM_CanSM.h" /* SchM Header File*/
#include "CanSM_Ram.h"  /* CanSM_Ram header file */
#include "BswM_CanSM.h" /* BswM_CanSM.h header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_C_AR_RELEASE_MAJOR_VERSION 0x04u
#define CANSM_C_AR_RELEASE_MINOR_VERSION 0x04u
#define CANSM_C_AR_RELEASE_REVISION_VERSION 0x00u

/* CANSM software version information */
#define CANSM_C_SW_MAJOR_VERSION 0x01u
#define CANSM_C_SW_MINOR_VERSION 0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_C_AR_RELEASE_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_C_AR_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_C_AR_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanSM_Init                                          **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This function initializes internal and external     **
**                        interfaces and variables of the CANSM Module for    **
**                        further processing.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_InitStatus              **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00405 SRS_BSW_00101 SRS_BSW_00406 SRS_BSW_00358 SRS_BSW_00414 SRS_BSW_00404 SRS_BSW_00400 SRS_BSW_00438 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_001 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_Init(P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST) ConfigPtr)
{
  
  if((CanSM_StateType)CANSM_UNINITED == CanSM_InitStatus)
  {
    VAR(NetworkHandleType, CANSM_VAR) canSmNwIndex;
    VAR(CanSM_ConfigType, CANSM_VAR) selectedConfig;
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    VAR(Std_ReturnType, CANSM_VAR) result;
    #endif

    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)



    if(NULL_PTR == ConfigPtr )
    {
      #if(STD_ON == CANSM_DEV_ERROR_DETECT)

      /* @Trace: CanSM_SUD_API_067 */
      /* report development Error to DET */
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID,
                             CANSMSERVICEID_INIT, CANSM_E_PARAM_POINTER);
      #endif
      /* set result to E_NOT_OK */
      result = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* set result to E_OK */
      result = (Std_ReturnType)E_OK;

      /* get the address which is passed via CanSM_init to local variable */
      selectedConfig = *ConfigPtr;
    }
    #else
    /* polyspace +7 RTE:UNR [Not a defect:Low] "It depend on the configuration, no impact" */
    if(NULL_PTR != ConfigPtr)
    {
        /* get the address which is passed via CanSM_init to local variable */
        /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The validity of pointer is already checked to ensure not a NULL pointer" */
        selectedConfig = *ConfigPtr;
        /* set result to E_OK */
    }
    else
    {
        /* get default value for local config */
        selectedConfig = CanSM_Config[0];
        /* set result to E_OK */
    }
    #endif

    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    if((Std_ReturnType)E_OK == result)
    #endif
    {

     /* initialize all general parameters */
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     /* number of networks per configuration */
     CanSM_NWPerCfg = (uint8)selectedConfig.CanSMNWPerCfg;

     /* the number of controllers in the current configuration */
     CanSM_CtrlPerCfg = (uint8)selectedConfig.CanSMStaticController;

     /* the largest controllerId in the current configuration */
     CanSM_LastCtrlHandle = (uint8)selectedConfig.CanSMLastCtrlHandle;

     /* the largest id of communication network handle */
     CanSM_LastNWHandle = (uint8)selectedConfig.CanSMLastNetworkHandle;

     /* mapping controller index to network */
     CanSM_CtrlIDToNW = selectedConfig.pCtrlIDToNW;

     /* mapping network in to network index */
     CanSM_NwIdToIndex = selectedConfig.pNwIdToIndex;

     /* mapping controller id to controller index */
     CanSM_CtrlIndexToId =selectedConfig.pCtrlIndexToId;

     /* set local variable to number of network */
     canSmNwIndex = (uint8)CanSM_NWPerCfg;
     #else
     canSmNwIndex = (uint8)CANSM_NUMBER_OF_STATIC_NWS;
     #endif

     #if((STD_ON == CANSM_CANTRCV_SUPPORT)&&(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT))
     /* the last transceiver id */
     CanSM_LastTrcvHandle = (uint8)selectedConfig.CanSMLastTrcvHandle;

     /* mapping controller id to network index */
     CanSM_TrcvIdToNwIndex = selectedConfig.pTrcvIdToNwIndex;
     #endif

     /* mapping Trcv id to transceiver index */
     #if(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY)
     /* values provided by call out function */
     CanSM_BusOffDelayTime = (uint8)CANSM_ZERO;
     #endif
     /*CanSMModeRequestRepetitionMax */
     CanSm_ModeReqMax = (uint8)selectedConfig.ModeReqRptMax;

     /* CanSMModeRequestRepetitionTime */
     CanSm_ModeReqRepeatTime = (uint16)selectedConfig.ModeReqRptTime;

     /* network management container */
     CanSM_StaticNw = selectedConfig.pStaticNetwork;

     /* Loop for all the networks */

     /* #7877 - do ~ while --> while */
     while ((NetworkHandleType)CANSM_ZERO != canSmNwIndex)
     {
      /* Decrement the network index */
      canSmNwIndex = canSmNwIndex - (CANSM_ONE);
      /* #7877 - Add Feature */

      /* Initialize the ModeStatus as Zero */
      CanSM_Network[canSmNwIndex].ModeStatus = (uint8)CANSM_ZERO;

      /* Initialize busOffCounter as Zero*/
      CanSM_Network[canSmNwIndex].BusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

      /* Initialize Internal SubState as Zero*/
      CanSM_Network[canSmNwIndex].CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* Initialize Controller Count as Zero*/
      CanSM_Network[canSmNwIndex].CanSMCtrlCount = (uint8)CANSM_ZERO;

      /* Initialize Mode Request Repetition Max Count as Zero */
      CanSM_Network[canSmNwIndex].CanSMModeReqReptMax =(uint8)CanSm_ModeReqMax;

      /* Initialize Mode Request Repetition Time Count as Zero */
      CanSM_Network[canSmNwIndex].CanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Initialize Bus Off Repetition Count Flag */
      /* Bug #703 - Add to check duplicate Bus off Event while Bus Off Recovery */
      CanSM_Network[canSmNwIndex].BusOffRep = (uint8)CANSM_ZERO;
    }

    /* Set the Passive state to Non Passive*/
    CanSM_ECUPassive = (CanSM_ECUPassiveType)CANSM_ECU_NOT_PASSIVE;

    /* Set the initialization state to  CANSM_INITED */
    CanSM_InitStatus = (CanSM_StateType)CANSM_INITED;

    }
  }
  /* polyspace +3 RTE:UNR [Not a defect:Low] "It depend on the configuration, no impact" */
  else
  {
      CANSM_UNUSED_PTR(ConfigPtr);
  }
} /* End of CanSM_Init(P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST)
   *ConfigPtr) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_DeInit                                        **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : This service de-initializes the CanSM module.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : none                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_InitStatus              **
**                                              CanSM_StaticNw                **
**                        Function(s) invoked : Det_ReportError               **
**                                              BswM_CanSM_CurrentState       **
*******************************************************************************/
/* @Trace: SRS_Can_01164 SRS_BSW_00336 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_002 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_DeInit(void)
{

    P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
    P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

    VAR(NetworkHandleType, CANSM_VAR) canSmNwIndex;
    VAR(Std_ReturnType, CANSM_VAR) result;


    #if (STD_ON == CANSM_DEV_ERROR_DETECT)
    /* @Trace: CanSM_SUD_API_003 */
    /*  De-initalization function shall not be allowed to call unless it is already initialized */
    CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_DEINITIALIZE);
    /* CanSM is already initialized */
    if ((Std_ReturnType)E_OK == result)
    #endif
    {

      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      /* get total number of CanSM network */
      canSmNwIndex = (NetworkHandleType)CanSM_NWPerCfg;
      #else
      /* get total number of CanSM network */
      canSmNwIndex= (NetworkHandleType)CANSM_NUMBER_OF_STATIC_NWS;
      #endif

      do
      {
        /* Decrement of CanSM Index */
        canSmNwIndex = canSmNwIndex - (CANSM_ONE);

        /* get CanSM_Network to local pointer variable */
        ptrNetwork = &CanSM_Network[canSmNwIndex];

        /* get CanSM_StaticNw to local pointer */
        ptrStaticNetwork = &CanSM_StaticNw[canSmNwIndex];

        /* Source code below aims at checking whether there are any network not in full communication mode  */
        /* @Trace: CanSM_SUD_API_095 */
        if ((uint8)CANSM_NOCOMMUNICATION != ptrNetwork->ModeStatus)
        {
          #if (STD_ON == CANSM_DEV_ERROR_DETECT)
          /*report error to Det in case any Networks are not in No Communication */
          CANSM_NOT_IN_NO_COM_INDICATION(CANSMSERVICEID_DEINITIALIZE);
          #endif
          /* set result to E_NOT_OK */
          result = (Std_ReturnType)E_NOT_OK;
        }
        else
        {

          /* report CANSM_BSWM_NO_COMMUNICATION to BswM */
          /* @Trace: CanSM_SUD_API_094 */
          /* polyspace +1 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */  
          BswM_CanSM_CurrentState((NetworkHandleType)(ptrStaticNetwork->CanSmNetworkHandle), (CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);
          /*   MISRA C:2012 Rule   : D4.14
           *   Message             : the pointer could be a NULL pointer
           *   Reason              : In case of NULL pointer, the first configuration set shall be selected
           *   Verification        : the pointer shall be compared to NULL and assigned the first configuration set if the pointer is NULL
           *                         Otherwise, the pointer shall be accepted
           */
        }

      } while (((NetworkHandleType)CANSM_ZERO < canSmNwIndex) && ((uint8)E_OK == result));

      if ((Std_ReturnType)E_OK == result)
      {
        /* Set CanSM_InitStatus to CANSM_UNINITED */
        CanSM_InitStatus = (CanSM_StateType)CANSM_UNINITED;

      }

    }
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_StartWakeupSource                             **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This function shall be called by EcuM when a wakeup
**                      source shall be started.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) network            **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_InternalNetwork         **
**                                              CanSM_Network                 **
**                        Function(s) invoked :
**                                Det_ReportError                             **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_012 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_StartWakeupSource(VAR(NetworkHandleType, CANSM_VAR) network)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;
  VAR(Std_ReturnType, CANSM_VAR) result;

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* @Trace: CanSM_SUD_API_013 */
  /* Note: the initialization shall be checked and error shall be reported in case it is not initialized */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_STARTWAKEUPSOURCE);


  /* Note: CanSM shall return E_NOT_OK and report to Det in case network is invalid */
  if ((Std_ReturnType)E_OK == result)
  {
	  /* @Trace: CanSM_SUD_API_014 */
    CANSM_CHECK_INVALID_NETWORK(result, network, CANSMSERVICEID_STARTWAKEUPSOURCE);
  }

  if ((Std_ReturnType)E_OK == result)
  {
     /* get the index of the network */
     /* @Trace: CanSM_SUD_API_015 */
     /* polyspace +4 RTE:UNR [Justified: Low] It can not be reach with this configuration */
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_NwIdToIndex[network],CANSMSERVICEID_STARTWAKEUPSOURCE);
     #else
     CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_InternalNetwork[network],CANSMSERVICEID_STARTWAKEUPSOURCE);
     #endif
     /*   MISRA C:2012 Rule   : D4.14
      *   Message             : the array is not out of bounds
      *   Reason              : the input fit the defined length of above array
      *   Verification        : However, network is already checked in advanced already
      */
  }
  if ((Std_ReturnType)E_OK == result)
  #endif /*end of (STD_ON == CANSM_DEV_ERROR_DETECT)*/
  {
    /* get the index of network in case DET is Off  */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_NwIdToIndex[network];
    #else
    networkHandle = CanSM_InternalNetwork[network];
    #endif


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : network is already checked in advanced with a macro expansion
     */
    /* Get the address of network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* @Trace: CanSM_SUD_API_016 */
    /* Note: CanSM_StartWakeupSource shall be considered as trigger for CANSM_BSM_WUVALIDATION */
    if (((uint8)CANSM_NOCOMMUNICATION == ptrNetwork->ModeStatus) || ((uint8)CANSM_DEINITPNSUPPORTED == ptrNetwork->ModeStatus) || ((uint8)CANSM_DEINITPNNOTSUPPORTED == ptrNetwork->ModeStatus))
    {
      /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

      /* Update the internal sub state */
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* Enter protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /*Change Mode to wake up validation */
      ptrNetwork->ModeStatus = (uint8)CANSM_WAKEUPVALIDATION;

      /* Exit protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* set result to E_OK */
      result = (Std_ReturnType)E_OK;
    }
    else
    {
      /* set result to E_NOT_OK */
      result = (Std_ReturnType)E_NOT_OK;
    }
  }

  /* Check Whether Network is valid or not*/
  return result;
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : P2VAR(Std_VersionInfoType,AUTOMATIC,                **
**                        CANSM_APPL_DATA) versionInfo                        **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: SRS_BSW_00407 SRS_BSW_00003 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_022 */
#if (STD_ON == CANSM_VERSION_INFO_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANSM_APPL_DATA) versionInfo)
{
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANSM_VAR) result;


  /* @Trace: CanSM_SUD_API_023 */
  CANSM_CHECK_INVALID_POINTER(result, versionInfo, CANSMSERVICEID_GETVERSIONINFO);
  /* MISRA C:2012  Rule : D4.14
   * Message            : the pointer can not be NULL
   * verification       : the external pointer is check by function
   *                      Error shall be reported to DET to stop the function if it is a NULL pointer
   *                      */

  if ((Std_ReturnType)E_OK == result)
  #endif
  {
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "The pointer is already checked NULL before it is used " */
    /* Copy the vendor Id */
    versionInfo->vendorID = (uint16)CANSM_VENDOR_ID;

    /* Copy the module Id */
    versionInfo->moduleID = (uint16)CANSM_MODULE_ID;

    /* Copy Software Major Version */
    versionInfo->sw_major_version = (uint8)CANSM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versionInfo->sw_minor_version = (uint8)CANSM_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versionInfo->sw_patch_version = (uint8)CANSM_SW_PATCH_VERSION;
    /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "The pointer is already checked NULL before it is used " */
  }
} /* End of CanSM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   *CANSM_APPL_DATA) versionInfo) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_VERSION_INFO_API) */

/*******************************************************************************
** Function Name        : CanSM_StopWakeUpSource                              **
** Service ID           : 0x12                                                **
** Description          : This function shall be called by EcuM when a wakeup **
**                      source shall be stopped.                              **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_Network             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                Det_ErrorReport                             **
**                                BswM_CanSM_CurrentState()                   **
**                                SchM_Enter_CanSM_MODE_STATUS_PROTECTION()   **
**                                SchM_Exit_CanSM_MODE_STATUS_PROTECTION()    **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_017 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_StopWakeupSource(VAR(NetworkHandleType, CANSM_VAR) network)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;
  VAR(Std_ReturnType, CANSM_VAR) result;


  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  VAR(boolean, CANSM_VAR) pnSupported;
  #endif

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* @Trace: CanSM_SUD_API_018 */
  /* Note: Check whether CanSM is initialized and report to Det in case of possible error */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_STOPWAKEUPSOURCE);


  /* Note: CanSM shall return E_NOT_OK and report to Det in case network is invalid */
  if ((Std_ReturnType)E_OK == result)
  {
	  /* @Trace: CanSM_SUD_API_019 */
    CANSM_CHECK_INVALID_NETWORK(result, network, CANSMSERVICEID_STOPWAKEUPSOURCE);
  }
  if ((Std_ReturnType)E_OK == result)
  {
    /* get the index of network */
    /* @Trace: CanSM_SUD_API_020 */
    /* polyspace +4 RTE:UNR [Justified: Low] It can not be reach with this configuration */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_NwIdToIndex[network],CANSMSERVICEID_STOPWAKEUPSOURCE);
    #else
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_InternalNetwork[network],CANSMSERVICEID_STOPWAKEUPSOURCE);
    #endif

    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, network is already checked in advanced already
     */
  }
  if ((Std_ReturnType)E_OK == result)
  #endif /* end of (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
     /* get the index of the network */
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     networkHandle = CanSM_NwIdToIndex[network];
     #else
     networkHandle = CanSM_InternalNetwork[network];
     #endif


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, network is already checked in advanced already
     */
    /* get the address of network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];


    /* Note: CanSM_StopWakeupSource shall return E_OK and  be considered as trigger for sub state machine */
    /* @Trace: CanSM_SUD_API_021 */
    if ((uint8)CANSM_WAKEUPVALIDATION == ptrNetwork->ModeStatus)
    {
      /* get address of Static Network to local variable */
      ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

      /* Update Internal Substate as Zero*/
      ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

      /* reset requested repeat time */
      ptrNetwork->CanSMModeReqReptTime = (CanSM_TimerType)CanSm_ModeReqRepeatTime;

      /* Reset the Mode repetition request*/
      ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;


      /* Note: E_PRE_NOCOM */
      /*Notify BswM the change of mode*/
      /* polyspace +1 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
      BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle, (CanSM_BswMCurrentStateType)CANSM_BSWM_NO_COMMUNICATION);

      /* Enter protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();


      #if (STD_ON == CANSM_PNC_AVAILABILITY)
      /* get PnSupported status from StaticNw */
      pnSupported = CanSM_StaticNw[CANSM_NETWORKHANDLE].pnSupported;


      if ((Std_ReturnType)CANSM_TRUE == pnSupported)
      {
        /* set ModeSatus to CANSM_DEINITPNSUPPORTED in case Pn is supported */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNSUPPORTED;
      }
      else
      {
        /* set ModeSatus to CANSM_DEINITPNNOTSUPPORTED in case Pn is not supported */
        ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
      }

      #else
      /* set ModeSatus to CANSM_DEINITPNNOTSUPPORTED in case Pn is not available */
      ptrNetwork->ModeStatus = (uint8)CANSM_DEINITPNNOTSUPPORTED;
      #endif

      /* Exit protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      /* set result to E_OK */
      result = (Std_ReturnType)E_OK;
    }
    else
    {
      /* set result to E_OK */
      result = (Std_ReturnType)E_NOT_OK;
    }

  }
  return result;
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SetIcomConfiguration                          **
** Service ID           : 0x0F                                                **
**                      a CAN network to the requested one.                   **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        VAR(IcomConfigIdType,CANSM_VAR) ConfigurationId     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)    :  CanSM_StaticNw             **
**                                                 CanSM_Network              **
**                                                                            **
**                        Function(s) invoked   :                             **
**                                CanIf_SetIcomConfiguration()                **
**                                BswM_CanSM_CurrentIcomConfiguration         **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_030 */
#if (STD_ON == CANSM_ICOM_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetIcomConfiguration(VAR(NetworkHandleType, CANSM_VAR) Network, VAR(IcomConfigIdType, CANSM_VAR) ConfigurationId)
{

  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;
  VAR(NetworkHandleType, CANSM_VAR) networkHandle;
  VAR(Std_ReturnType, CANSM_VAR) result;


  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  /*Set result to E_OK */
  result = (uint8)E_OK;
  #endif

  VAR(uint8,CANSM_VAR) controllerIndex;
  VAR(uint8,CANSM_VAR) noOfController;

   #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* Det check for CanSM Initialization */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_SETICOMCONFIGURATION);


  /* Note: E_NOT_OK shall be returned and error shall be reported to Dem in case network is invalid */
  if ((Std_ReturnType)E_OK == result)
  {
	  /* @Trace: CanSM_SUD_API_032 */
    CANSM_CHECK_INVALID_NETWORK(result, Network, CANSMSERVICEID_SETICOMCONFIGURATION);
  }
  /* If Network is valid */
  if ((Std_ReturnType)E_OK == result)
  {

    /* get the index of the network */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_NwIdToIndex[Network],CANSMSERVICEID_SETICOMCONFIGURATION);
    #else
    /* Det check whether networkHandle is invalid */
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_InternalNetwork[Network],CANSMSERVICEID_SETICOMCONFIGURATION);
    #endif


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, Network is already checked in advanced already
     */
  }
  if ((Std_ReturnType)E_OK == result)
  #endif
  {
    /* get the index of network in case DET is Off  */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_NwIdToIndex[Network];
    #else
    networkHandle = CanSM_InternalNetwork[Network];
    #endif


    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the value of network fits the defined length of above array
     *   Verification        : the value of network is checked in advanced with a macro expansion which is CANSM_CHECK_INVALID_NETWORK
     */
    /* get the address of CanSM_StaticNw to local pointer */
    ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];


    /* CanSM shall invoked CanIf_SetIcomConfiguration to activate or deactivate ICOM */
    /* @Trace: CanSM_SUD_API_061 */
    noOfController  = ptrStaticNetwork->NumberOfController;
    controllerIndex = ptrStaticNetwork->ControllerIndex;
    do
    {
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      if((Std_ReturnType)E_NOT_OK == CanIf_SetIcomConfiguration(CanSM_CtrlIndexToId[controllerIndex],ConfigurationId))
      {
         result = (Std_ReturnType)E_NOT_OK;
      }
      #else
      if((Std_ReturnType)E_NOT_OK == CanIf_SetIcomConfiguration(CanSM_StaticController[controllerIndex],ConfigurationId))
      {
         result = (Std_ReturnType)E_NOT_OK;
      }
      #endif
      /* @Trace: CanSM_SUD_API_201 */
       --noOfController;
       ++controllerIndex;
    }while(noOfController != CANSM_ZERO);

  }
  /* Note: The return of the API shall rely on the return value of  CanIf_SetIcomConfiguration */
  return result;
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* end if (STD_ON == CANSM_ICOM_SUPPORT) */

/*******************************************************************************
** Function Name        : CanSM_CurrentIcomConfiguration                      **
** Service ID           : 0x10                                                **
** Description          : This service shall inform about the change of       **
**                      the Icom Configuration of a CAN network.              **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        VAR(IcomConfigIdType,CANSM_VAR) ConfigurationId     **
**                        VAR(IcomSwitch_ErrorType,CANSM_VAR) Error           **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_InternalController  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                  BswM_CanSM_CurrentIcomConfiguration()     **
**                                  Det_ReportError                           **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_058 */
#if (STD_ON == CANSM_ICOM_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_CurrentIcomConfiguration(VAR(uint8, CANSM_VAR) ControllerId, VAR(IcomConfigIdType, CANSM_VAR) ConfigurationId,
                               VAR(IcomSwitch_ErrorType, CANSM_VAR) Error)
{

  VAR(Std_ReturnType, CANSM_VAR) result;

  VAR(NetworkHandleType, CANSM_VAR) networkHandle;

  /*set result to E_NOT_OK */
  result = (uint8)E_NOT_OK;

  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  CANSM_UNUSED(result);
  #endif

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* Det check for CanSM Initialization */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_CURRENTICOMCONFIGURATION);

  if ((Std_ReturnType)E_OK == result)
  {
    /* Det check for controller invalidity */
    CANSM_CHECK_INVALID_CONTROLLER(result, ControllerId, CANSMSERVICEID_CURRENTICOMCONFIGURATION);
  }
  if ((Std_ReturnType)E_OK == result)
  #endif
  {
     /* get the network index which contain the ControllerId */
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     networkHandle = CanSM_CtrlIDToNW[ControllerId];
     #else
     networkHandle = CanSM_InternalController[ControllerId];
     #endif

     /* notify BswM the activation of de-activation  of CanSM current network */
     /* @Trace: CanSM_SUD_API_059 */
     BswM_CanSM_CurrentIcomConfiguration(networkHandle, ConfigurationId, Error);

     /*   MISRA C:2012 Rule   : D4.14
      *   Message             : the array is not out of bounds
      *   Reason              : the input fit the defined length of above array
      *   Verification        : However, ControllerId is already checked in advanced already
      */

  }
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* end if (STD_ON == CANSM_ICOM_SUPPORT) */

/*******************************************************************************
** Function Name        : CanSM_SetEcuPassive                                 **
** Service ID           : 0x13                                                **
** Description          : This function can be used to set all CanSM channels **
**                      of the ECU to a receive only mode. This mode will be  **
**                      kept either until it is set back, or the ECU is reset **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(boolean,CANSM_VAR) CanSM_Passive                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_StaticNw            **
**                                                  CanSM_Network             **
**                                                  CanSM_ECUPassive          **
**                                                                            **
**                        Function(s) invoked    : CanIf_SetPduMode()         **
**                                                 Det_ReportError()          **
*******************************************************************************/
/* @Trace: SRS_Can_01158 */
/* @Trace: CanSM_SUD_API_087 */
#if (STD_ON == CANSM_TX_OFFLINE_ACTIVE_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetEcuPassive(VAR(boolean, CANSM_VAR) CanSM_Passive)
{
  P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST)  ptrStaticNetwork;

  VAR(NetworkHandleType, CANSM_VAR) canSmNwIndex;

  VAR(uint8, CANSM_VAR) canSmControllerIndex;
  VAR(uint8, CANSM_VAR) canSmNoOfController;

  VAR(CanIf_PduModeType, CANSM_VAR) PduMode;

  VAR(Std_ReturnType, CANSM_VAR) result;



  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* Det check for CanSM Initialization */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_SETECUPASSIVE);

  if ((uint8)E_OK == result)
  #endif
  {
    /* intialize the local variable which is PduMode */
    PduMode = (CanIf_PduModeType)CANIF_OFFLINE;

    /* Get address CanSm GetPduMode to  local PduMode pointer */

    if ((boolean)CANSM_TRUE == CanSM_Passive )
    {
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     /* get total number of CanSM network */
     canSmNwIndex = (NetworkHandleType)CanSM_NWPerCfg;
     #else
     /* get total number of CanSM network */
     canSmNwIndex= (NetworkHandleType)CANSM_NUMBER_OF_STATIC_NWS;
     #endif
      do
      {
        /* decrement of canSmNwIndex */
        canSmNwIndex--;
        /* get CanSM_StaticNw to local pointer */
        ptrStaticNetwork = &CanSM_StaticNw[canSmNwIndex];

        /* get number of CanSM controller */
        /* polyspace +1 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
        canSmNoOfController = (uint8)(ptrStaticNetwork->NumberOfController);

        /* get controllerIndex in case single controller is not support */
        canSmControllerIndex = (uint8)(ptrStaticNetwork->ControllerIndex);
        do
        {
          /* get the current pdu mode */
        	/* @Trace: CanSM_SUD_API_091 */
          (void)CanIf_GetPduMode(canSmControllerIndex,&PduMode);

          /* Pdu mode shall be changed in case the current mode is CANIF_ONLINE */
          if((CanIf_PduModeType)CANIF_ONLINE == PduMode)
          {
            /* set Pdu mode CANIF_ONLINE at the moment to CANIF_TX_OFFLINE_ACTIVE */
        	  /* @Trace: CanSM_SUD_API_089 */
            result = CanIf_SetPduMode(canSmControllerIndex, CANIF_TX_OFFLINE_ACTIVE);
          }
          else
          {
            result = (Std_ReturnType)E_NOT_OK;
          }
          /* decrement of number of CanSm controller */
          --canSmNoOfController;

          /* increment of CanSm controller index  */
          ++canSmControllerIndex;

        /* end of loop for controller index */
        } while ((CANSM_ZERO != canSmNoOfController)&&((Std_ReturnType)E_OK == result));

       /* end of loop for Network index */
      } while ((CANSM_ZERO != canSmNwIndex) && ((Std_ReturnType)E_OK == result));

      /* Store the state of the requested ECU passive mode */
      if ((Std_ReturnType)E_OK == result)
      {
        /* Set CanSM_ECUPassive to CANSM_ECUPASSIVE */
    	  /* @Trace: CanSM_SUD_API_088 */
        CanSM_ECUPassive = (CanSM_ECUPassiveType)CANSM_ECUPASSIVE;
      }

    }
    /* Note: Pdu mode is set to TX_OFFLINE_ACTIVE in case CanSM_Passive is false */
    else if((boolean)CANSM_FALSE == CanSM_Passive)
    {
     #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
     /* get total number of CanSM network */
     canSmNwIndex = (NetworkHandleType)CanSM_NWPerCfg;
     #else
     /* get total number of CanSM network */
     canSmNwIndex= (NetworkHandleType)CANSM_NUMBER_OF_STATIC_NWS;
     #endif
      do
      {
        /* decrement of canSmNwIndex */
        canSmNwIndex--;

        /* get CanSM_StaticNw to local pointer*/
        ptrStaticNetwork = &CanSM_StaticNw[canSmNwIndex];
        /* polyspace +2 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
        /* get number of CanSM controller */
        canSmNoOfController = (uint8)(ptrStaticNetwork->NumberOfController);

        /* get number of CanSM controller index */
        canSmControllerIndex = (uint8)(ptrStaticNetwork->ControllerIndex);

        do
        {
          /* get the current pdu mode */
        	/* @Trace: CanSM_SUD_API_092 */
          (void)CanIf_GetPduMode(canSmControllerIndex,&PduMode);

          if((CanIf_PduModeType)CANIF_TX_OFFLINE_ACTIVE == PduMode)
          {
            /* set Pdu mode CANIF_TX_OFFLINE_ACTIVE at the moment to CANIF_ONLINE */
        	  /* @Trace: CanSM_SUD_API_090 */
            result = CanIf_SetPduMode(canSmControllerIndex, CANIF_ONLINE);
          }
          else
          {
            result = (Std_ReturnType)E_NOT_OK;
          }
          /* increment of controller index */
          ++canSmControllerIndex;

          /* decrement of number of controllers*/
          --canSmNoOfController;
        /* end of loop for controller index */
        } while ((CANSM_ZERO != canSmNoOfController) && ((Std_ReturnType)E_OK == result));

      /* end of loop for network index */
      } while ((CANSM_ZERO != canSmNwIndex) && ((Std_ReturnType)E_OK == result));

      /* store the state of the requested ECU passive mode */
      if ((Std_ReturnType)E_OK == result)
      {

         /* Note: CanSM_ECUPassive shall be stored as  CANSM_ECU_NOT_PASSIVE */
         CanSM_ECUPassive = (CanSM_ECUPassiveType)CANSM_ECU_NOT_PASSIVE;
      }
    }
    else
    {
        result = (Std_ReturnType)E_NOT_OK;
    }
  }
  /* return result */
  return result;
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* end if (STD_OFF == CANSM_TX_OFFLINE_ACTIVE_SUPPORT) */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
