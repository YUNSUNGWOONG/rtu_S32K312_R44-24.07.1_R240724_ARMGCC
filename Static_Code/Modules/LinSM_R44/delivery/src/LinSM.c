/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually and has no impact" */
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
**  SRC-MODULE: LinSM.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinSM APIs                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.6.1        29-Dec-2022           TruongND18       #CP44-1366, CP44-1379**
** 1.0.6          25-Nov-2022           TruongND18       #CP44-1089           **
** 1.0.5.1        25-Oct-2022           KhaLN1           #CP44-564            **
** 1.0.5          03-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          26-Apr-2022           DuyNHP2          R44-Redmine #26483   **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: Com_SUD_FILE_001 */
#include "LinSM.h"                /* LinSM header */
#include "LinSM_Ram.h"            /* LinSM_Ram header */
#include "LinSM_InternalFunc.h"   /* LinSM Internal header */
#include "LinSM_PCTypes.h"        /* LinSM Precompile config header */
/* @Trace: SRS_BSW_00384 */
#include "LinIf.h"                /* Redmine #9471: Include LinIf.h for calling LinIf_SetTrcvMode*/
/* @Trace: SRS_BSW_00384 */
/* @Trace: Com_SUD_FILE_001 */
#include "ComM.h"                 /* ComM header file */
/* @Trace: SRS_BSW_00384 */
/* @Trace: Com_SUD_FILE_001 */
#include "BswM_LinSM.h"           /* BswM header file */
#if (LINSM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: SRS_BSW_00384 */
#include "Det.h"                  /* Det header file */
#endif




/*The purpose of adding these ID SRSs is to full fill for traceability and maintain the Testcases IDs QTC_006_00005 ~ QTC_006_00010.
because this SRSs ID does not support the LinSM module */

/* @Trace: LinSM_SUD_QTC_001 */
/* @Trace: SRS_ES90600_10E_00005 */

/* @Trace: LinSM_SUD_QTC_002 */
/* @Trace: SRS_ES90600_10E_00007 */
 
/* @Trace: LinSM_SUD_QTC_003 */
/* @Trace: SRS_ES90600_10E_00010 */
 
/* @Trace: LinSM_SUD_QTC_004 */
/* @Trace: SRS_ES90600_10E_00011*/
 
/* @Trace: LinSM_SUD_QTC_005 */
/* @Trace: SRS_ES90600_10E_00012 */
 
/* @Trace: LinSM_SUD_QTC_006 */
/* @Trace: SRS_ES90600_10E_00013 */
 
/* @Trace: LinSM_SUD_QTC_007 */
/* @Trace: SRS_ES90600_10E_00014 */
 
/*******************************************************************************
**                          Global Data                                       **
*******************************************************************************/
#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Com modes */
/* polyspace +1 VARIABLE:ALL [Not a defect] "This variable do not interfere with each other." */
static CONST(ComM_ModeType, LINSM_CONST) LinSM_GaaComMModes[LINSM_THREE] =
{
  COMM_NO_COMMUNICATION,
  COMM_FULL_COMMUNICATION,
  COMM_NO_COMMUNICATION
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : LinSM_Init                                          **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes the LIN State Manager.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GaaCurrentState, LinSM_GblInitStatus          **
**                        Function(s) invoked : Det_ReportError()             **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_LinSM_00155 SWS_LinSM_00166 SWS_LinSM_00164
 * SWS_LinSM_00204 SWS_LinSM_00152 SWS_LinSM_00216 SRS_BSW_00161
 * SWS_LinSM_00025 SWS_LinSM_00043 SWS_LinSM_00161 SRS_BSW_00162
 * SRS_BSW_00101 SRS_BSW_00358 SRS_BSW_00414 SRS_Lin_01576
 * SRS_Lin_01560 SRS_Lin_01590 SRS_BSW_00005 SRS_BSW_00010
 * SRS_BSW_00333 SRS_BSW_00334 SRS_BSW_00341 SRS_BSW_00343 SRS_BSW_00359
 * SRS_BSW_00432 SRS_BSW_00433 SRS_BSW_00437 SRS_BSW_00438 SRS_BSW_00439
 */
#define LINSM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, LINSM_CODE) LinSM_Init(P2CONST(LinSM_ConfigType, AUTOMATIC,
    LINSM_APPL_CONST) ConfigPtr)
{
  /* @Trace: LinSM_SUD_API_001 */
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  NetworkHandleType LddLocalChannelId;
  /* Initialize the channel id with zero*/
  LddLocalChannelId = (NetworkHandleType)LINSM_ZERO;

  #if (LINSM_DEV_ERROR_DETECT == STD_ON)

  if (NULL_PTR != ConfigPtr)
  {
    /* @Trace: LinSM_SUD_API_002 */
    /* @Trace: SRS_BSW_00167 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_INIT_SID, LINSM_E_PARAM_POINTER);
  }
  else
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
	/* @Trace: LinSM_SUD_API_003 */
    /* polyspace-begin RTE:UNR [Justified:Low] "The statement is used only to avoid compilation warning." */
    /*Justify:
      Message      : This statements has no side effects it can be removed.
      Reason       : The statement is used only to avoid compilation warning.
      Verification : However, part of the code is verified manually
                     and it is not having any impact.
    */
    LINSM_UNUSED_PTR(ConfigPtr);
    /* polyspace-end RTE:UNR [Justified:Low] "The statement is used only to avoid compilation warning." */

    #if (LINSM_SINGLE_CHANNEL == STD_OFF)

    /* Check for all channels*/
    do
    {
    #endif
        /* @Trace: SRS_Lin_01577 */
        /* Get pointer to channel structure */
        /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    	LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
        /* Set channel state to LINSM_NO_COM */
        LinSM_GaaCurrentState[LddLocalChannelId] = LINSM_NO_COM;
        #if(LINSM_TIMEOUT_FUNC == STD_ON)
        /* Reset the Timer value */
        LpChannel->usScheduleReqTimerCount = LINSM_ZERO;
        /* Reset the Timer value */
        LpChannel->usModeReqTimerCount = LINSM_ZERO;
        #endif
        /* Reset request flag */
        LpChannel->ucModeScheduleReqStatus = LINSM_ZERO;
        #if (LINSM_MASTER_SUPPORT == STD_ON)
        /* Reset current schedule flag */
        LpChannel->ddCurrSchedule = (LinIf_SchHandleType)LINSM_ZERO;
        #endif
        /* Reset the Timer value */
        LpChannel->ucModeRequestRepetitionCount = LINSM_ZERO;
        #if (LINSM_SLAVE_SUPPORT == STD_ON)
        /* Reset the Timer value */
        LpChannel->ucSilenceAfterWakeupTimeoutCount = LINSM_ZERO;
        #endif
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
        /* Increment the channel ID */
        LddLocalChannelId++;
    }while (LddLocalChannelId < LINSM_NO_OF_CHANNELS);
    
    #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_OFF) */
    
    #if (LINSM_DEV_ERROR_DETECT == STD_ON)
      /* @Trace: LinSM_SUD_API_004 */
      /* Set Module state to LINSM_INIT */
      /* @Trace: SRS_Lin_01577 */
      LinSM_GblInitStatus = LINSM_INIT;
    #endif
  }
}
#define LINSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinSM_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : *versioninfo                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        None                                                **
**                        Function(s) invoked :                               **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SWS_LinSM_00117 SWS_LinSM_00119 SWS_LinSM_00208
 * SRS_BSW_00004 SRS_BSW_00407
 */
#if (LINSM_VERSION_INFO_API == STD_ON)
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_CODE) LinSM_GetVersionInfo(P2VAR(Std_VersionInfoType,
    AUTOMATIC,
    LINSM_APPL_DATA) versioninfo)
{
  /* Check if versioninfo pointer is equal to Null */
  if (NULL_PTR == versioninfo)
  {
	#if (LINSM_DEV_ERROR_DETECT == STD_ON)
    /* @Trace: LinSM_SUD_API_005 */
    /* @Trace: SRS_BSW_00167 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GETVERSIONINFO_SID, LINSM_E_PARAM_POINTER);
	#endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
    /* @Trace: LinSM_SUD_API_006 */
    /* Copy the vendor Id */
    versioninfo->vendorID = LINSM_VENDOR_ID; /* polyspace MISRA-C3:D4.14 [Justified:Low] "The pointer has checked for not NULL." */
    /* Copy the module Id */
    versioninfo->moduleID = LINSM_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = LINSM_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = LINSM_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = LINSM_SW_PATCH_VERSION;
  } /* End if (versioninfo == NULL_PTR) is not true  */
} /* End of LinSM_GetVersionInfo*/

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : LinSM_GetCurrentComMode                             **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service returns the current communication mode **
**                        of channel.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : network                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : *mode                                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GaaComMModes, LinSM_GaaCurrentState,          **
**                        LinSM_GblInitStatus                                 **
**                        Function(s) invoked :                               **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SWS_LinSM_00122 SWS_LinSM_00125 SWS_LinSM_00182
 * SWS_LinSM_00123 SWS_LinSM_00124 SWS_LinSM_00180
 * SWS_LinSM_00181 SRS_BSW_00369 SRS_BSW_00406
 * SRS_BSW_00168 SRS_BSW_00170 SRS_BSW_00321 SRS_BSW_00331
 */
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINSM_CODE) LinSM_GetCurrentComMode(
  NetworkHandleType network, P2VAR(ComM_ModeType, AUTOMATIC,
    LINSM_APPL_DATA) mode)
{
  /* @Trace: LinSM_SUD_API_151 */
  NetworkHandleType LddLocalChannelId;
  Std_ReturnType LddReturnValue;

  /* Set return value with E_OK */
  LddReturnValue = E_OK;

  /* Check if mode pointer is Null */
  if (NULL_PTR == mode)
  {
    /* @Trace: LinSM_SUD_API_007 */
	#if (LINSM_DEV_ERROR_DETECT == STD_ON)
	  /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GETCURRENTCOMMODE_SID, LINSM_E_PARAM_POINTER);
	#endif
    /* Set return value with E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  } /* End of if (mode == NULL_PTR) */

  #if (LINSM_DEV_ERROR_DETECT == STD_ON)

  /* Check if module is not initialized */
  if ((LINSM_UNINIT == LinSM_GblInitStatus) && (E_OK == LddReturnValue))
  {
    
    /* @Trace: LinSM_SUD_API_008 */
    /* @Trace: SRS_Lin_01577 */
    /* Report to DET  with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GETCURRENTCOMMODE_SID, LINSM_E_UNINIT);
    /* Set return value with E_NOT_OK*/
    LddReturnValue = E_NOT_OK;
    /*the state COMM_NO_COMMUNICATION shall be returned*/
    *mode = COMM_NO_COMMUNICATION; /* polyspace MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */

  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
	/* @Trace: LinSM_SUD_API_009 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GETCURRENTCOMMODE_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set return value with E_NOT_OK*/
    LddReturnValue = E_NOT_OK;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */
  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */
  /* Check network index is out of bounds */
  /*LINSM_CHECK_FOR_INVALID_NETWORK(network, LINSM_GETCURRENTCOMMODE_SID);*/
  if ((network) > (LINSM_MAX_CHANNEL_ID))
  {
	/* @Trace: LinSM_SUD_API_009 */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
        LINSM_GETCURRENTCOMMODE_SID, LINSM_E_NONEXISTENT_NETWORK);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
    (LddLocalChannelId) = (network) - (network);
    #endif
    if ((LddLocalChannelId) == (LINSM_INACTIVE_CHANNEL))
    {
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
          LINSM_GETCURRENTCOMMODE_SID, LINSM_E_NONEXISTENT_NETWORK);
      LddReturnValue = E_NOT_OK;
    }
  }
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  /* Check if return value is E_OK */
  if (E_OK == LddReturnValue)
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
	/* @Trace: LinSM_SUD_API_010 */
    /* Get the Channel Id from the Internal Channel Map array */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
    (LddLocalChannelId) = (network) - (network);
    #endif
    /*
     *   MISRA Rule        : 1.2
     *   Message           : Dereferencing pointer value that is
     *                       apparently NULL.
     *   Reason            : "mode" pointer is checked and verified when
     *                       DET is switched STD_ON.
     *   Verification      : However, the part of the code is verified
     *                       manually and it is not having any impact on
     *                       code.
     */
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
    /* polyspace-begin MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* Justify comment:
    * 1. Size of LinSM_GaaCurrentState array is LINSM_NO_OF_CHANNELS and
    * LddLocalChannelId has been checked in range of LINSM_NO_OF_CHANNELS
    * => Array index is not outside bounds.
    * 2. Size of LinSM_GaaComMModes array is LINSM_THREE and LinSM_GaaCurrentState
    * only store LINSM_NO_COM and LINSM_FULL_COM value in run time
    * => Array index is not outside bounds.
    * */
    /* Copy the communication mode of channel */
    *mode = LinSM_GaaComMModes[(uint8)LinSM_GaaCurrentState[LddLocalChannelId]];
    /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-end MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
  } /* if (LddReturnValue = E_OK) */
  return (LddReturnValue);
} /* End of LinSM_GetCurrentComMode*/

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinSM_RequestComMode                                **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service is used to change the communication    **
**                        mode of a channel through LinIf module.             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : network, mode                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GaaSchMEnterFuncPtr, LinSM_GaaSchMExitFuncPtr,**
**                        LinSM_GaaModeFuncPtr, LinSM_GblInitStatus           **
**                        LinSM_GaaCurrentState, LinSM_GaaComMModes           **
**                        Function(s) invoked :                               **
**                        Det_ReportError(), LinIf_WakeUp(),LinIf_GotoSleep(),**
**                        LinSM_DetRequestComMode, LinSM_SlaveRequestComMode  **
*******************************************************************************/
/* @Trace: SWS_LinSM_00126 SWS_LinSM_00128 SWS_LinSM_00127
 * SWS_LinSM_00191 SWS_LinSM_00183 SWS_LinSM_00205
 * SWS_LinSM_00035 SWS_LinSM_10208 SWS_LinSM_00047
 * SWS_LinSM_10209 SWS_LinSM_00036 SWS_LinSM_00232
 * SWS_LinSM_00100 SWS_LinSM_00302 SWS_LinSM_00223
 * SWS_LinSM_00177 SWS_LinSM_00230 SWS_LinSM_00231
 * SWS_LinSM_00164 SWS_LinSM_00176 SWS_LinSM_00173
 * SRS_Lin_01504 SRS_Lin_01598 SRS_BSW_00369
 * SRS_BSW_00406 
 */
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINSM_CODE) LinSM_RequestComMode(NetworkHandleType network,
  ComM_ModeType mode)
{
  /* @Trace: LinSM_SUD_API_152 */
  NetworkHandleType LddLocalChannelId;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  #if ((LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) || (LINSM_TIMEOUT_FUNC == STD_ON))
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  #endif
  Std_ReturnType LddReturnValue;
  ComM_ModeType LddComMMode;

  /* Array of function pointer to handle the LinSM mode changes */
  VAR(LinSM_ModeReqPtr, LINSM_VAR) LinSM_GaaModeFuncPtr[LINSM_THREE] =
  {
    NULL_PTR,
    LinIf_GotoSleep,
    LinIf_Wakeup
  };

  /* Set return value to E_OK */
  LddReturnValue = E_OK;

  #if (LINSM_DEV_ERROR_DETECT == STD_ON)

 LddReturnValue = LinSM_DetRequestComMode(LddReturnValue,mode, network);

  /* Check if return value is E_OK */
  if (E_NOT_OK != LddReturnValue)
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinSM_SUD_API_014 */
    /* Get local channel id from internal channel map array */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "The pointer has checked for not NULL." */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
    (LddLocalChannelId) = (network) - (network);
    #endif
    /* Get pointer to channel structure */
    /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
    /* Get the current communication mode */
    /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-begin MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Array index is not outside bounds." */
    /* Justify:
     * 1. Size of LinSM_GaaCurrentState array is LINSM_NO_OF_CHANNELS and
     * LddLocalChannelId has been checked in range of LINSM_NO_OF_CHANNELS
     * => Array index is not outside bounds.
     * 2. Size of LinSM_GaaComMModes array is LINSM_THREE and LinSM_GaaCurrentState
     * only store LINSM_NO_COM and LINSM_FULL_COM value in run time
     * => Array index is not outside bounds.
     * */
    LddComMMode = LinSM_GaaComMModes[(uint8)LinSM_GaaCurrentState[LddLocalChannelId]];
     /* polyspace-end MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */

    /* Check if the requested mode is not same as current mode and mode
     *   requested is not silent communication and mode request is not pending
     * */
    if ((mode != LddComMMode) && (COMM_SILENT_COMMUNICATION != mode) &&
        ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ) == LINSM_ZERO))
    {
      #if ((LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) || (LINSM_TIMEOUT_FUNC == STD_ON))
      /* Get pointer to static channel structure */
      /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
      LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
      #endif /* ((LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) || (LINSM_TIMEOUT_FUNC == STD_ON)) */

      #if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON)
      /* Redmine #9471: Change the mode of transceiver to Normal before calling LinIf_Wakeup() */
      if(COMM_FULL_COMMUNICATION == mode)
      {
        /* Check if LinSMTransceiverPassiveMode is configured */
        /* polyspace-begin DEFECT:USELESS_IF MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
        if (LinSM_GaaTrcvPassiveMode[LddLocalChannelId] !=
            LINSM_TRCV_NOTCONFIGURED)
        {
          /* @Trace: LinSM_SUD_API_016 */
          /* Invoke LinIf_SetTrcvMode with Normal */
          (void)LinIf_SetTrcvMode(LpStaticChannel->ddLinSMChannelId,
            LINTRCV_TRCV_MODE_NORMAL);
        }
        /* polyspace-end DEFECT:USELESS_IF MISRA-C3:14.3 [Justified:Low] "It depends on configuration" */
      }
      #endif /* End of if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) */

      /* polyspace-begin DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
      if (LINSM_MASTER_NODE == LinSM_CurrentNodeType[LddLocalChannelId])
      {
        /* Invoke the API LinIf_WakeUp or LinIf_GotoSleep */
        /* polyspace<RTE: COR : Justified : Justify with annotations > function pointer may not point to a valid function */
        if (((LinSM_GaaCurrentState[LddLocalChannelId] == LINSM_FULL_COM) &&
             (LinSM_CurrentSubState[LddLocalChannelId] == LINSM_RUN_COMMUNICATION)) ||
            (LinSM_GaaCurrentState[LddLocalChannelId] == LINSM_NO_COM))
        {
          LddReturnValue = (LinSM_GaaModeFuncPtr[(uint8)LinSM_GaaCurrentState[LddLocalChannelId]])(network);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }

        /* Check if the return value is E_OK */
        if (LddReturnValue == E_OK)
        {
		  /* @Trace: LinSM_SUD_API_018 */
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Start Timer By loading the timeout value */
          #if (LINSM_TIMEOUT_FUNC == STD_ON)

          if (LpStaticChannel->usLinSMConfirmationTimeout != LINSM_ZERO)
          {
            LpChannel->usModeReqTimerCount =
              LpStaticChannel->usLinSMConfirmationTimeout;
          }
          #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

          /*Set sub-state to LINSM_GOTOSLEEP if the LinIf_GotoSleep returns E_OK*/
          if (LinSM_GaaCurrentState[LddLocalChannelId] == LINSM_FULL_COM)
          {
              LinSM_CurrentSubState[LddLocalChannelId] = LINSM_GOTO_SLEEP;
          }
            /* @Trace: LinSM_SUD_API_018 */
          /* Set the mode request status to true */
          LpChannel->ucModeScheduleReqStatus =
            LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ;
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        } /* @ End if (LddReturnValue == E_OK) */
        else
        {
	      /* @Trace: LinSM_SUD_API_017 */
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Set mode request to LinIf was not invoked */
          LpChannel->ucModeScheduleReqStatus =
            LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED;
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        } /* End of else */
      }
      /* polyspace-end DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
      #if (LINSM_SLAVE_SUPPORT == STD_ON)
      LddReturnValue = LinSM_SlaveRequestComMode(network);

      #endif /* (LINSM_SLAVE_SUPPORT == STD_ON) */
      /* Else case to avoid wrong value of variable LinSM_CurrentNodeType in run time.
       * Polyspace tool has detected this is a defect and else case is never performed with current
       * configuration.
       * => Just remove!
       * */
      /*else*/ /* Value is out of scope */
      /*{*/
          /* Enter protection area */
          /*(LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();*/
          /* Set mode request as unsuccessful */
          /*LpChannel->ucModeScheduleReqStatus = LpChannel->ucModeScheduleReqStatus |
                                               LINSM_MODE_REQ_FAILED;*/
          /* Exit protection area */
          /*(LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();*/
          /* Set the return value E_NOT_OK */
          /*LddReturnValue = E_NOT_OK;

      }*/
    } /* If the requested mode is same as current mode or mode requested is
       *   silent communication or mode */
    else
    {
      /* @Trace: LinSM_SUD_API_015 */
      /* Enter protection area */
      (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
      /* Set mode request as unsuccessful */
      LpChannel->ucModeScheduleReqStatus = LpChannel->ucModeScheduleReqStatus |
                                           LINSM_MODE_REQ_FAILED;
      /* Exit protection area */
      (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
      /* Set the return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    } /* End of else */
  } /* @ End if (LddReturnValue == E_OK) */
  return (LddReturnValue);
} /* End of LinSM_RequestComMode **/

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinSM_MainFunction                                  **
**                                                                            **
** Service ID           : 0x30                                                **
**                                                                            **
** Description          : This service shall be invoked for scheduled         **
**                        intervals based on the "LinSMMainProcessingPeriod"  **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        LinSM_GblInitStatus, LinSM_GaaSchMEnterFuncPtr,     **
**                        LinSM_GaaSchMExitFuncPtr, LinSM_GaaCurrentState,    **
**                        LinSM_GaaComMModes                                  **
**                        Function(s) invoked :                               **
**                        Det_ReportError(), BswM_LinSM_CurrentSchedule(),    **
**                        ComM_BusSM_ModeIndication(), LinSM_ProcessTimer(),  **
**                        BswM_LinSM_CurrentState(),LinSM_SlaveMainFunc       **
*******************************************************************************/
/* @Trace: SWS_LinSM_00156 SWS_LinSM_00162
 * SWS_LinSM_00177 SWS_LinSM_00202 SWS_LinSM_00203
 * SWS_LinSM_00213 SWS_LinSM_00214 SWS_LinSM_00233
 * SWS_LinSM_00234 SWS_LinSM_00102 SWS_LinSM_00170
 * SWS_LinSM_00215 SWS_LinSM_00304 SWS_LinSM_00307
 * SWS_LinSM_00235 SWS_LinSM_00236 SWS_LinSM_00237
 * SWS_LinSM_00164 SWS_LinSM_00103 SWS_LinSM_00154
 * SWS_LinSM_00101 SWS_LinSM_00019
 * SRS_BSW_00373
 */
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_CODE) LinSM_MainFunction(void)
{
  /* @Trace: LinSM_SUD_API_024 */
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  NetworkHandleType LddLocalChannelId;
  #if (LINSM_TIMEOUT_FUNC == STD_ON)
  #if (LINSM_SLAVE_SUPPORT == STD_ON)
  P2CONST(LinSM_ConfigType, AUTOMATIC, LINSM_CONST) LpConfigType;
  NetworkHandleType network;
  #endif
  uint16 LscModeTimerCount;
  uint16 LscScheduleTimerCount;
  #endif

  ComM_ModeType LddComMode;

  /* Initialize channel id  with zero */
  LddLocalChannelId = (NetworkHandleType)LINSM_ZERO;

  #if (LINSM_SINGLE_CHANNEL == STD_OFF)

  /* Check for all configured channels*/
  do
  {
    #endif
    /* @Trace: LinSM_SUD_API_025 */
    /* Get pointer to channel structure */
    /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
    /* Get pointer to static channel structure */
    /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
    LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
        #if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON))

    /* @Trace: LinSM_SUD_API_026 */
    /* Get pointer to network id */
    /*LINSM_GET_LOCAL_CHANNEL_ID_TO_NETWORK();*/
    network = LinSM_GaaStaticChannel[LddLocalChannelId].ddLinSMChannelId;
    #endif

    #if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON))

    /* Get pointer to config type structure */
    /*LINSM_GET_PTR_TO_CONFIG_TYPE_CHANNEL();*/
    LpConfigType = &LinSM_GaaConfigType[LddLocalChannelId];
    #endif

    /* @Trace: LinSM_SUD_API_027 */
    /* Get the current mode */
    /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-begin MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Array index is not outside bounds." */
    /* Justify: Size of LinSM_GaaCurrentState is LINSM_NO_OF_CHANNELS and
     * LddLocalChannelId has been checked in range of LINSM_NO_OF_CHANNELS
     * => Array index is not outside bounds.
     * */
    LddComMode = LinSM_GaaComMModes[(uint8)LinSM_GaaCurrentState[LddLocalChannelId]];
    /* polyspace-end MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Array index is not outside bounds." */
    /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */

    /* polyspace-begin DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
    if (LINSM_MASTER_NODE == LinSM_CurrentNodeType[LddLocalChannelId])
    {
      #if (LINSM_TIMEOUT_FUNC == STD_ON)

      /* Check if timeout configured for particular channel */
      if (LINSM_ZERO != LpStaticChannel->usLinSMConfirmationTimeout)
      {
        /* Check if mode request is in progress */
        if ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ) ==
            LINSM_MODE_REQ)
        {
          /* @Trace: LinSM_SUD_API_028 */
          /* Get the timer value configured for this channel */
          LscModeTimerCount = LpChannel->usModeReqTimerCount;
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Process the mode req timer by invoking LinSM_ProcessTimer */
          LpChannel->usModeReqTimerCount = LinSM_ProcessTimer(LddLocalChannelId,
            LscModeTimerCount, LINSM_MODE_REQ_TIMER);
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        } /* End of if ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ) ==
           **/

        /* Check if schedule request is in progress */
        if ((LpChannel->ucModeScheduleReqStatus & LINSM_SCHEDULE_REQ) ==
            LINSM_SCHEDULE_REQ)
        {
          /* @Trace: LinSM_SUD_API_029 */
          /* Get the schedule req timer value configured for this channel*/
          LscScheduleTimerCount = LpChannel->usScheduleReqTimerCount;
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Process the schedule req timer by invoking LinSM_ProcessTimer */
          LpChannel->usScheduleReqTimerCount =
            LinSM_ProcessTimer(LddLocalChannelId, LscScheduleTimerCount,
              LINSM_SCHEDULE_REQ_TIMER);
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        } /*End of if ((LpChannel->ucModeScheduleReqStatus & LINSM_SCHEDULE_REQ)
           * == LINSM_SCHEDULE_REQ)*/
      } /* End if (LpStaticChannel->usLinSMConfirmationTimeout != LINSM_ZERO) */

      #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

      /*
         Check if mode request was unsuccessful - for following reasons
           1) Failed to send 'goto-sleep command' or 'wakeup signal'
           2) Confirmation Timeout has been expired
      */
      if ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ_FAILED) ==
          LINSM_MODE_REQ_FAILED)
      {
        /* @Trace: LinSM_SUD_API_030 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        /* Reset the flag */
        LpChannel->ucModeScheduleReqStatus =
          LpChannel->ucModeScheduleReqStatus & LINSM_RESET_MODE_REQ_FAILED;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Invoke ComM_BusSM_ModeIndication */
        ComM_BusSM_ModeIndication(LpStaticChannel->ddLinSMChannelId,
          LddComMode);
        /* Invoke BswM_LinSM_CurrentState */
        BswM_LinSM_CurrentState(LpStaticChannel->ddLinSMChannelId,
          LinSM_GaaCurrentState[LddLocalChannelId]);

        /* Redmine #9471: When the transmission of wakeup signal was failed,
          revert the mode of the transceiver */
        /* Check if LinSMTransceiverPassiveMode is configured */
        #if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON)
        if(LINSM_NO_COM == LinSM_GaaCurrentState[LddLocalChannelId])
        {
          /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "It depends on configuration" */
          /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
          /*Check if LinSMTransceiverPassiveMode is configured true */
          if (LinSM_GaaTrcvPassiveMode[LddLocalChannelId] ==
              LINSM_TRCV_CONFIGURED_TRUE)
          {
            /* @Trace: LinSM_SUD_API_031 */
            /* Invoke LinIf_SetTrcvMode with Standby */
            (void)LinIf_SetTrcvMode(LpStaticChannel->ddLinSMChannelId,
            LINTRCV_TRCV_MODE_STANDBY);
          }
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
          /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "It depends on configuration" */
          else
          {
             /* @Trace: LinSM_SUD_API_032 */
            /* Invoke LinIf_SetTrcvMode with Sleep */
            (void)LinIf_SetTrcvMode(LpStaticChannel->ddLinSMChannelId,
            LINTRCV_TRCV_MODE_SLEEP);
          }
        } /* If Current state of LinSM is 'LINSM_NO_COM' */
        #endif
      } /* End checking mode request was successful */

      #if (LINSM_MASTER_SUPPORT == STD_ON)
      /* Check if schedule request was unsuccessful */
      if ((LpChannel->ucModeScheduleReqStatus & LINSM_SCHEDULE_REQ_FAILED) ==
          LINSM_SCHEDULE_REQ_FAILED)
      {
        /* @Trace: LinSM_SUD_API_033 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        /* Reset the flag */
        LpChannel->ucModeScheduleReqStatus =
          LpChannel->ucModeScheduleReqStatus & LINSM_RESET_SCHEDULE_REQ_FAILED;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Invoke BswM_LinSM_CurrentSchedule */
        BswM_LinSM_CurrentSchedule(LpStaticChannel->ddLinSMChannelId,
          LpChannel->ddCurrSchedule);
      } /* End of if ((LpChannel->ucModeScheduleReqStatus &
         *LINSM_SCHEDULE_REQ_FAILED) == */
      #endif
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
    /* polyspace-end DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
    #if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON))
   
      LinSM_SlaveMainFunc(LpChannel, LpStaticChannel, LpConfigType, network, LddLocalChannelId, LddComMode);

    #endif /* End of if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON)) */
    /*Just remove do nothing case*/
    /*else
    {*/
    	/* Do nothing */
    /*}*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
    /* @Trace: LinSM_SUD_API_044 */
    /* Increment the Channel ID*/
    LddLocalChannelId++;

  }while (LddLocalChannelId < LINSM_NO_OF_CHANNELS);
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_OFF) */
} /* End of LinSM_MainFunction */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinSM_ScheduleRequest                               **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This function is used to request for change of      **
**                         schedule table when requested by upper layer.      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrant           : Re-entrant                                          **
**                                                                            **
** Input Parameters     : channel, schedule                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GaaSchMExitFuncPtr, LinSM_GaaSchMEnterFuncPtr,**
**                        LinSM_GblInitStatus, LinSM_GaaCurrentState          **
**                        Function(s) invoked :                               **
**                        Det_ReportError(), LinIf_ScheduleRequest(),         **
*******************************************************************************/
/* @Trace: SWS_LinSM_00241 SWS_LinSM_00113 SWS_LinSM_00116
 * SWS_LinSM_00114 SWS_LinSM_00115 SWS_LinSM_10211
 * SWS_LinSM_00163 SWS_LinSM_00079 SWS_LinSM_00168
 * SRS_BSW_00369 SRS_BSW_00406 SRS_BSW_00360
 * SRS_BSW_00375 SRS_BSW_00399 SRS_BSW_00400 SRS_BSW_00404
 * SRS_BSW_00405 SRS_BSW_00416 SRS_BSW_00417 SRS_BSW_00422 SRS_BSW_00425
 */
#if (LINSM_MASTER_SUPPORT == STD_ON)
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINSM_CODE) LinSM_ScheduleRequest(
  NetworkHandleType network, LinIf_SchHandleType schedule)
{
  /* @Trace: LinSM_SUD_API_045 */
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  #if (LINSM_TIMEOUT_FUNC == STD_ON)
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  #endif
  NetworkHandleType LddLocalChannelId;
  Std_ReturnType LddReturnValue;

  /* @Trace: LinSM_SUD_API_046 */
  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddScheduleReturn;

  /* Set to default value */
  LddReturnValue = E_OK;
  /* Check if module is initialized or not */
  if (LINSM_UNINIT == LinSM_GblInitStatus)
  {
    /* @Trace: LinSM_SUD_API_047 */
    /* Report to DET with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUEST_SID, LINSM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */

  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
	/* @Trace: LinSM_SUD_API_048 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUEST_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set return value with E_NOT_OK*/
    LddReturnValue = E_NOT_OK;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */
  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  /* Check network index is out of bounds */
  if (network > LINSM_MAX_CHANNEL_ID)
  {
	/* @Trace: LinSM_SUD_API_049 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUEST_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set return value with E_NOT_OK*/
    LddReturnValue = E_NOT_OK;
  } /* End of if (network > LINSM_MAX_CHANNEL_ID) */
  #endif /* LINSM_SINGLE_CHANNEL */
  else
  {
    /* Redmine #8174 Remove dead assignment
    LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
    /* Redmine #8174 Get the Channel Id from the Internal Channel Map array */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_050 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_051 */
    (LddLocalChannelId) = (network) - (network);
    #endif
    /* Check network is valid */
    if (LINSM_INACTIVE_CHANNEL == LddLocalChannelId)
    {
	  /* @Trace: LinSM_SUD_API_052 */
      /* Report to DET */
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUEST_SID, LINSM_E_NONEXISTENT_NETWORK);
      /* Set return value with E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    } /* End of if (LddLocalChannelId == LINSM_INACTIVE_CHANNEL) */
    else
    #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_OFF) */
    {
      /* @Trace: LinSM_SUD_API_053 */
      LddScheduleReturn = LinSM_CheckSchedule(network, schedule);
      if(E_NOT_OK == LddScheduleReturn)
      {
        /* @Trace: LinSM_SUD_API_054 */
        /* Set return value with E_NOT_OK */
        LddReturnValue = E_NOT_OK;
      }
    } /* if network is valid */
  } /* if network is within range */

  /* Check if the return value is E_OK */
  if (E_NOT_OK != LddReturnValue)
  #endif /* LINSM_DEV_ERROR_DETECT */
  {
    /* Get the Channel Id from the Internal Channel Map array */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_055 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_056 */
    (LddLocalChannelId) = (network) - (network);
    #endif
    /* polyspace-begin DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
    if (LINSM_MASTER_NODE == LinSM_CurrentNodeType[LddLocalChannelId])
    {
	  /* @Trace: LinSM_SUD_API_057 */
      /* Get pointer to channel structure */
      /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
      LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
      #if (LINSM_TIMEOUT_FUNC == STD_ON)
	  /* @Trace: LinSM_SUD_API_058 */
      /* Get pointer to static channel structure */
      /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
      LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
      #endif

      /* Check if current mode is FULL_COM and there is no pending request */
      if ((LINSM_FULL_COM == LinSM_GaaCurrentState[LddLocalChannelId]) &&
          (LINSM_RUN_COMMUNICATION == LinSM_CurrentSubState[LddLocalChannelId]) &&
          ((LpChannel->ucModeScheduleReqStatus & LINSM_SCHEDULE_REQ) ==
            LINSM_ZERO))
      {
	    /* @Trace: LinSM_SUD_API_059 */
        /* Invoke LinIf_ScheduleRequest API and store Return value */
        LddReturnValue = LinIf_ScheduleRequest(network, schedule);

        /* Check if the schedule request success or not*/
        if (E_OK == LddReturnValue)
        {
           /* @Trace: LinSM_SUD_API_060 */
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          #if (LINSM_TIMEOUT_FUNC == STD_ON)

          /* Check if timer is configured */
          if (LINSM_ZERO != LpStaticChannel->usLinSMConfirmationTimeout)
          {
			/* @Trace: LinSM_SUD_API_061 */
            /* Start Timer By loading the timeout value */
            LpChannel->usScheduleReqTimerCount =
              LpStaticChannel->usLinSMConfirmationTimeout;
          }
          #endif /* End of if  (LINSM_TIMEOUT_FUNC == STD_ON) */
		  /* @Trace: LinSM_SUD_API_062 */
          /* Copy the current schedule to be started */
          LpChannel->ddReqSchedule = schedule;
          /* Set the schedule request status to true */
          LpChannel->ucModeScheduleReqStatus =
            LpChannel->ucModeScheduleReqStatus | LINSM_SCHEDULE_REQ;
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        } /* @ End if (LddReturnValue == E_OK) */
        else
        {
		  /* @Trace: LinSM_SUD_API_063 */
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Set the schedule request failure flag */
          LpChannel->ucModeScheduleReqStatus =
            (LpChannel->ucModeScheduleReqStatus) | LINSM_SCHEDULE_REQ_FAILED;
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        } /* End of else */
      } /* End if ((LinSM_GaaCurrentState[LddLocalChannelId]... */
      else
      {
		/* @Trace: LinSM_SUD_API_064 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        /* Set the schedule request failure flag */
        LpChannel->ucModeScheduleReqStatus =
          (LpChannel->ucModeScheduleReqStatus) | LINSM_SCHEDULE_REQ_FAILED;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Set return value to E_NOT_OK */
        LddReturnValue = E_NOT_OK;
      } /* End of else */
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
    /* polyspace-end DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
    #if (LINSM_SLAVE_SUPPORT == STD_ON)
    else //Current Node is not MASTER NODE
    {
        /* @Trace: LinSM_SUD_API_065 */
        LddReturnValue = E_NOT_OK;
    }
    #endif /* (LINSM_SLAVE_SUPPORT == STD_ON) */
  } /* @ End if (LddReturnValue == E_OK) */
  return (LddReturnValue);
} /* End of LinSM_ScheduleRequest*/

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_MASTER_SUPPORT == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
