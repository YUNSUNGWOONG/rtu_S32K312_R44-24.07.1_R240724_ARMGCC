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
**  SRC-MODULE: CanSM_Mode.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of the funtionality of CanSM_GetCurrentComMode()    **
**              and CanSM_RequestComMode()                                    **
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
** 1.0.6       12-Dec-2022   HieuTM8        #CP44-1312                        **
** 1.0.3       25-Jul-2022   HieuTM8        CP44-511                          **
** 1.0.2       24-Mar-2022   HieuTM8        R44-Redmine #25572                **
** 1.0.1       14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306         **
** 1.0.0       04-Dec-2020   SMKwon         Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_Internal.h"       /* CanSM_Main header */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanSM_Error.h"          /* CanSM_Error header */  
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_MODE_C_RELEASE_MAJOR_VERSION       0x04u
#define CANSM_MODE_C_RELEASE_MINOR_VERSION       0x04u
#define CANSM_MODE_C_RELEASE_REVISION_VERSION    0x00u

/* CANSM software version information */
#define CANSM_MODE_C_SW_MAJOR_VERSION            0x01u
#define CANSM_MODE_C_SW_MINOR_VERSION            0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_MODE_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_MODE_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_MODE_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_MODE_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_MODE_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanSM_GetCurrentComMode                             **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service puts out the current communication     **
**                        mode for the network handle to the pointer of type  **
**                        ComM_ModeType.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
**  Re-entrancy         : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle,     **
**                        P2VAR(ComM_ModeType, AUTOMATIC,                     **
**                               CANSM_APPL_DATA) ComM_ModePtr                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_Network                 **
**                                              CanSM_InternalNetwork         **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09084 SRS_Can_01142 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_008 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComMode(VAR(NetworkHandleType,CANSM_VAR) network,
 P2VAR(ComM_ModeType, AUTOMATIC,CANSM_APPL_DATA) ComM_ModePtr)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;
  VAR(NetworkHandleType,CANSM_VAR) networkHandle;
  VAR(Std_ReturnType, CANSM_VAR) result;
  VAR(uint8,CANSM_VAR) modeStatus;
  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  result = (uint8)E_OK;
  #endif
  /* polyspace +4 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* @Trace: CanSM_SUD_API_009 */
  result = CanSM_GetCurrentComModeDetCheck(network, ComM_ModePtr);
  if ((Std_ReturnType)E_OK == result)
  #endif
  {
    /* get the index of the network */
    /* @Trace: CanSM_SUD_API_010 */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_NwIdToIndex[network];
    #endif

    #if(STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT)
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The validity of variable 'network' which is used as array index is already checked" */
    networkHandle = CanSM_InternalNetwork[network];
    #endif

    /* Get the address of CanSM_Network to local pointer */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* Get the current mode status */
    modeStatus = ptrNetwork->ModeStatus;

    /* @Trace: CanSM_SUD_API_011 */
    switch (modeStatus)
    {
      /* Current network mode is COMM_NO_COMMUNICATION */
      case CANSM_NOCOMMUNICATION:
      case CANSM_NOTOFULLCOMMREQUESTED:
      case CANSM_DEINITPNNOTSUPPORTED:
      case CANSM_DEINITPNSUPPORTED:
      case CANSM_WAKEUPVALIDATION:
      case CANSM_WAKEUPTOFULLCOMREQUESTED:
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The validity of pointer is already checked before It is used " */
        *ComM_ModePtr = (ComM_ModeType)COMM_NO_COMMUNICATION;


        break;

      /* Current network mode is COMM_SILENT_COMMUNICATION */
      case CANSM_SILENTCOMMUNICATION:
      case CANSM_SILENTTOFULLCOMMREQUESTED:
      case CANSM_FULLTOSILENTCOMMREQUESTED:
      case CANSM_SILENTCOMMUNICATION_BOR:
      case CANSM_BORSTART:
      case CANSM_BORWAIT:
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The validity of pointer is already checked before It is used " */
        *ComM_ModePtr = (ComM_ModeType)COMM_SILENT_COMMUNICATION;

        break;

      /* Current network mode is COMM_FULL_COMMUNICATION */
      case CANSM_BAUDRATEENDFULLCOM:
      case CANSM_BAUDRATEENDSILENTCOM:
      case CANSM_FULLCOMMUNICATION:
      case CANSM_CHECKBUSOFF:
      case CanSM_SetBaudrateSERVICE:
      case CANSM_TXTIMEOUTEXCEPTION:
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The validity of pointer is already checked before It is used " */
    	*ComM_ModePtr = (ComM_ModeType)COMM_FULL_COMMUNICATION;

    	break;
      default:
          result = (Std_ReturnType)E_NOT_OK;
          /* polyspace +1 RTE:UNR [Justified: Low] "It can not be reach with this configuration" */
          CANSM_UNUSED_PTR(ComM_ModePtr);

        break;
    } /* End of switch (modeStatus) */
  } /* End of if ((Std_ReturnType)E_OK == result) */
  return (result);
} /*End of CanSM_GetCurrentComMode*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanSM_RequestComMode                                **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service stores the requested                   **
**                        communication mode for the network handle and shall **
**                        execute the corresponding network mode state        **
**                        machine.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                        VAR(ComM_ModeType,CANSM_VAR) ComM_Mode              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_InternalNetwork         **
**                                              CanSM_StaticNw                **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_Can_01142 SRS_BSW_00406 SRS_BSW_00369 */
/* @Trace: CanSM_SUD_API_004 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComMode(VAR(NetworkHandleType,CANSM_VAR) network,
  VAR(ComM_ModeType,CANSM_VAR) ComM_Mode)
{
  P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;

  VAR(NetworkHandleType,CANSM_VAR) networkHandle;

  VAR(Std_ReturnType, CANSM_VAR) result;

  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  result = (uint8)E_OK;
  #else
  /* @Trace: CanSM_SUD_API_006 */
  result = CanSM_RequestComModeDetCheck(network);
  /* polyspace +1 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
  if ((Std_ReturnType)E_OK == result)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {

    /* get the index of the network */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    networkHandle = CanSM_NwIdToIndex[network];
    #endif

    #if(STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT)
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The validity of variable 'network' which is used as array index is already checked" */  
    networkHandle = CanSM_InternalNetwork[network];
    #endif

    /* Load the address of Network in local variable */
    ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

    /* Note: request shall be accepted in case of no errors and store in CanSM_Network */
    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
    /* if the input value equal COMM_NO_COMMUNICATION */

    /* @Trace: CanSM_SUD_API_007 */
    /* @Trace: CanSM_SUD_API_200 */
    if((uint8)COMM_NO_COMMUNICATION == ComM_Mode)
    {
      /* Note: requested mode shall be stored as a trigger for sub state machine */
      ptrNetwork->ReqModeStatus = (uint8)COMM_NO_COMMUNICATION;
    }

    /* if the input value equal COMM_SILENT_COMMUNICATION */
    /* @Trace: CanSM_SUD_API_079 */
    else if((uint8)COMM_SILENT_COMMUNICATION  == ComM_Mode)
    {
      /* the requested mode shall be stored and considered as a trigger */
      ptrNetwork->ReqModeStatus = (uint8)COMM_SILENT_COMMUNICATION;
    }
    /* polyspace +3 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
    /* if the input value equal COMM_FULL_COMMUNICATION */
    /* @Trace: CanSM_SUD_API_068 */
    else if((uint8)COMM_FULL_COMMUNICATION  == ComM_Mode)
    {
      /* the requested mode shall be stored and considered as a trigger */
      ptrNetwork->ReqModeStatus = (uint8)COMM_FULL_COMMUNICATION;
    }
    /* result  shall be set to E_NOT_OK if input ComM_Mode is not equal to any configured value */
    else
    {
       result = (Std_ReturnType)E_NOT_OK;
    }

    /* Exit Protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }
  return (result);
} /*End of CanSM_RequestComMode*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_GetCurrentComModeDetCheck                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service performs the Det check for API         **
**                        CanSM_GetCurrentComMode.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) networkHandle      **
**                   P2VAR(ComM_ModeType, AUTOMATIC, CANSM_VAR) ComM_ModePtr  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_InitStatus              **
**                                              CanSM_InternalNetwork         **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
/* @Trace: SRS_Can_01142 SRS_BSW_00369 */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComModeDetCheck
                                    (VAR(NetworkHandleType,CANSM_VAR) network, 
                    P2CONST(ComM_ModeType, AUTOMATIC, CANSM_VAR) ComM_ModePtr)
{

  VAR(Std_ReturnType, CANSM_VAR) result;

  /* polyspace +9 RTE:UNR [Not a defect:Low] "According to requirements, the init status should be checked before any further processing" */
  /* Report the error to DET with CANSM_E_UNINIT */
  /* polyspace<MISRA-C:16.10 : Low : Justify with annotations> Known issue */
  /* @Trace: CanSM_SUD_API_062 */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_GETCURRENTCOMMODE);

  /* Check if CanSM is greater than last network handle */
  /* polyspace<MISRA-C:16.10 : Low : Justify with annotations> Known issue */
  /* @Trace: CanSM_SUD_API_063 */
  if((Std_ReturnType)E_OK == result)
  {
    /* polyspace +4 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
    CANSM_CHECK_INVALID_NETWORK(result, network, CANSMSERVICEID_GETCURRENTCOMMODE);
  }

  if ((Std_ReturnType)E_OK == result)
  {
    /* polyspace +5 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
    /* Check if network handle is Invalid */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_NwIdToIndex[network],CANSMSERVICEID_GETCURRENTCOMMODE);
    #else
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_InternalNetwork[network],CANSMSERVICEID_GETCURRENTCOMMODE);
    #endif
    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, NetworkHandle is already checked in advanced already
     */
  }

  /* @Trace: CanSM_SUD_API_064 */
  /* Note: check pointer validity */
  /* polyspace +4 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
  if ((Std_ReturnType)E_OK == result)
  {
    /* Check if the pointer is NULL pointer */
    CANSM_CHECK_INVALID_POINTER(result, ComM_ModePtr,CANSMSERVICEID_GETCURRENTCOMMODE);
  }

  return (result);
} /*End Of CanSM_GetCurrentComModeDetCheck*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : CanSM_RequestComModeDetCheck                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service performs the Det check for API         **
**                        CanSM_RequestComMode.                               **
**                                                                            **
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
** Remarks              : Global Variable(s)  : CanSM_InitStatus              **
**                                              CanSM_InternalNetwork         **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
/* @Trace: SRS_Can_01145 SRS_Can_01142 SRS_BSW_00406  SRS_BSW_00369 */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComModeDetCheck(VAR(NetworkHandleType,CANSM_VAR) network)
{
  VAR(Std_ReturnType, CANSM_VAR) result;
  /* Report the error to DET with CANSM_E_UNINIT */
  /* if CanSM is in the state CANSM_BSM_S_NOT_INITIALIZED*/
  /* @Trace: CanSM_SUD_API_065 */
  /* polyspace +1 RTE:UNR [Not a defect:Low] "According to requirements, the init status should be checked before any further processing" */
  CANSM_INITED_DET_CHECK(result, CANSMSERVICEID_REQCOMMODE);

  /* Note: check network validity and report  errors to DET if any  */
  /* @Trace: CanSM_SUD_API_066 */
  /* polyspace +3 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
  if((Std_ReturnType)E_OK == result)
  {
    CANSM_CHECK_INVALID_NETWORK(result, network,CANSMSERVICEID_REQCOMMODE);
  }

  /* Note: check network validity and report  errors to DET if any  */
  /* polyspace +7 RTE:UNR [Not a defect:Low] "It depends on the configuration, no impact" */
  if ((Std_ReturnType)E_OK == result)
  {
    /* Check if network handle is Invalid */
    #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_NwIdToIndex[network],CANSMSERVICEID_REQCOMMODE);
    #else
    CANSM_CHECK_INVALID_NETWORK_HANDLE(result, CanSM_InternalNetwork[network],CANSMSERVICEID_REQCOMMODE);
    #endif

    /*   MISRA C:2012 Rule   : D4.14
     *   Message             : the array is not out of bounds
     *   Reason              : the input fit the defined length of above array
     *   Verification        : However, NetworkHandle is already checked in advanced already
     */
  }
  return (result);
} /*End Of CanSM_RequestComModeDetCheck*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
