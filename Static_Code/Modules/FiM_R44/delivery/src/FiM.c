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
**  SRC-MODULE: FiM.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of FiM APIs                                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 0.0.6     28-Oct-2020   ThienVT1        Changes made As per Redmine #16674 **
** 0.0.5    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.4     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.3    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM.h"                     /* FiM Header File */
/* @Trace: SWS_Fim_00081 */                  
/* @Trace: SWS_Fim_00079 */
#include "SchM_FiM.h"                /* SchM Header File */
#include "Rte_FiM.h"                 /* Rte Header File */
#if (FIM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                     /* Det header file */
/* @Trace: SWS_Fim_00080 */
#endif
#include "FiM_InternalFunc.h"        /* Internal Func header file */

/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Define the mask value for each type of MASK */
CONST(uint8, FIM_CONST) FiM_GaaMaskValues[FIM_FOUR] =
{
  FIM_MASK_LAST_FAILED,
  FIM_MASK_NOT_TESTED,
  FIM_MASK_TESTED,
  FIM_MASK_TESTED_AND_FAILED
};
#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Define the expected result for each type of MASK */
CONST(uint8, FIM_CONST) FiM_GaaExpMaskedResult[FIM_FOUR] =
{
  FIM_EXP_STS_LAST_FAILED,
  FIM_EXP_STS_NOT_TESTED,
  FIM_EXP_STS_TESTED,
  FIM_EXP_STS_TESTED_AND_FAILED
};
#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*
  MISRA Rule         : 19.4
  Message            : C macros shall only expand to a braced initialiser,
                       a constant, a parenthesised expression, a type
                       qualifier, a storage class specifier, or a do-while-zero
                       construct.
  Reason             : To avoid Compilation Warning "Dead Assignment to
                       LddReturn" FIM_RETURN_VALUE macro is defined.
  Verification       : However, part of the code is
                       verified manually and it is not
                       having any impact.
*/


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : FiM_Init                                            **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service shall initialize the permission states **
**                        of the FIDs based on the event data of the Dem.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : FiMConfigPtr                                        **
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
**                        FiM_GblInitStatus                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void,FIM_CODE)FiM_Init(
  P2CONST(FiM_ConfigType, AUTOMATIC, FIM_APPL_CONST) FiMConfigPtr)
/* @Trace: SWS_Fim_00077 */
{
  /* @Trace: FiM_SUD_API_001 */
  FiM_FidsSizeType LddFid;
  UNUSED(FiMConfigPtr); /* POSTBUILD is not supported yet*/
  /* set the static status variable to a value not equal to 0 */
  FiM_GucInitStatus = FIM_INITIALIZING;
  /* Enter Data Protection */
  SchM_Enter_FiM_REQUEST_FID_PROTECTION();
  /* Reset FID counters for all the configured Fids */
  /* @Trace: SRS_BSW_00406 */
  /* @Trace: SWS_Fim_00059 */
  #if (FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO)
  /* @Trace: FiM_SUD_API_002 */
  for (LddFid = FIM_ZERO; LddFid < FIM_TOTAL_NUM_OF_FIDS; LddFid++)
  {
    /* @Trace: FiM_SUD_API_003 */
    FiM_GaaFidInhibitCounter[LddFid] = FIM_ZERO;
    /* Clear permission state */
    /* @Trace: SWS_Fim_00018 */
    /* @Trace: SRS_Fim_04712 */
    FiM_GaaFidPermissionState[LddFid] = FIM_FALSE;
    /* Set all FID is Available */
    #if (FIM_AVAILABILITY_SUPPORT == STD_ON)
    /* @Trace: FiM_SUD_API_004 */
    FiM_GaaFidAvailableState[LddFid] = FIM_TRUE;
    #endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */
  }
  #endif
  /* Exit Data Protection*/
  /* @Trace: FiM_SUD_API_005 */
  SchM_Exit_FiM_REQUEST_FID_PROTECTION();
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_MainFunction                                    **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service shall initialize the permission states **
**                        of the FIDs based on the event data of the Dem when **
**                        pre-compile option FIM_EVENT_UPDATE_TRIGGERED_BY_DEM**
**                        is STD_OFF                                          **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                        FiM_GblInitStatus                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_CalcAllFidsPermissions         **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_MainFunction(void)
/* @Trace: SWS_Fim_00060 */
{
  #if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF)
  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: SWS_Fim_00045 */
  if (FiM_GucInitStatus != FIM_INITIALIZED)
  {
    /* @Trace: FiM_SUD_API_028 */

  }
  else
  #endif /* #if(FIM_DEV_ERROR_DETECT == STD_ON) */
  {
    /*
     * Calculate all the configured Fid inhibition status.
     * Return value is not used
     */
    /* @Trace: SWS_Fim_00070 */
    /* @Trace: FiM_SUD_API_029 */
    (void)FiM_CalcAllFidsPermissions();
  }
  #endif /* (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF) */
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_GetFunctionPermission                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service is used for reporting the permission   **
**                        state of FID to the SWC.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : FiM_FunctionIdType FID                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : boolean *Permission                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus, FiM_GaaFidPermissionState        **
**                                                                            **
**                        Function(s) invoked : Det_ReportError, FiM_FidSearch**
**                        SchM_Enter_FiM_REQUEST_FID_PROTECTION,              **
**                        SchM_Exit_FiM_REQUEST_FID_PROTECTION                **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, FIM_CODE) FiM_GetFunctionPermission(
  FiM_FunctionIdType FID, P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA)Permission)
/* @Trace: SWS_Fim_00011 */
/* @Trace: SRS_Fim_04700 */
/* @Trace: SRS_Fim_04709 */
{
  /* @Trace: FiM_SUD_API_006 */
  boolean LblFidExists;
  Std_ReturnType LddReturn = E_NOT_OK;
  FiM_FidsSizeType LddFidArrayIndex;
  /* @Trace: SWS_Fim_00104 */
  /* FiM_GetFunctionPermission  shall  not  be  used  before  full
   * initialization of FIM (Fim_DemInit).  */
  /* Check whether the module is initialized or not */
  if (FiM_GucInitStatus != FIM_INITIALIZED)
  {
    /* Report to DET indicating wrong permission request */
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: SWS_Fim_00056 */
    /* @Trace: FiM_SUD_API_007 */
    FiM_Report_Error(FIM_GETFUNCTIONPERMISSION_SID, FIM_E_UNINIT);
  }
  /* Check if Permission pointer is equal to Null */
  else if (Permission == NULL_PTR)
  {
    /* Report to DET indicating Invalid Pointer */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: FiM_SUD_API_008 */
    FiM_Report_Error(FIM_GETFUNCTIONPERMISSION_SID, FIM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: SWS_Fim_00066 */
    /* @Trace: FiM_SUD_API_009 */
    LblFidExists = FiM_FidSearch(FID, &LddFidArrayIndex);
    /* Check if FID is within the configured range */
    if (FIM_TRUE == LblFidExists)
    {
      /* If a function (FID) is set to not available using the interface */
      /* FiM_SetFunctionAvailable, its permission state */
      /* FiM_GetFunctionPermission shall always return FALSE */
      #if (FIM_AVAILABILITY_SUPPORT == STD_ON)
      if (FIM_TRUE == FiM_GaaFidAvailableState[LddFidArrayIndex])
      #endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */
      {
        /* @Trace: FiM_SUD_API_010 */
        /* Data Protection ON */
        SchM_Enter_FiM_REQUEST_FID_PROTECTION();
        /* NULL pointer is already checked */
        /* Get Permission Status */
        *Permission = FiM_GaaFidPermissionState[LddFidArrayIndex];
        /*
          MISRA Rule : 1.2
          Message       : Dereferencing pointer value that is apparently NULL.
          Reason        : Permission is checked and verified when DET
                          is switched OFF.
          Verification  : However, part of the code is verified manually
                          and it is not having any impact.
        */
        /* Data Protection OFF */
        SchM_Exit_FiM_REQUEST_FID_PROTECTION();
      }
      #if(FIM_AVAILABILITY_SUPPORT == STD_ON)
      else
      {
        /* @Trace: FiM_SUD_API_012 */
        /* @Trace: SWS_Fim_00105 */
        /* @Trace: SRS_Fim_04723 */
        /* NULL pointer is already checked */
        /* FiM_GetFunctionPermission shall always return FALSE */
        *Permission = FIM_FALSE;
      }
      #endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */
      /* @Trace: FiM_SUD_API_013 */
      LddReturn = E_OK;
    }
    else
    {
      /* FiM_GetFunctionPermission called with wrong FID */
      /* @Trace: SRS_BSW_00406 */
      /* @Trace: SWS_Fim_00076 */
      /* @Trace: SWS_Fim_00055 */
      /* @Trace: FiM_SUD_API_011 */
      FiM_Report_Error(FIM_GETFUNCTIONPERMISSION_SID, FIM_E_FID_OUT_OF_RANGE);
    }
  }
  /* @Trace: FiM_SUD_API_014  */
  return LddReturn;
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_SetFunctionAvailable                            **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service sets the availability of a function.   **
**                        The function is only available if                   **
**                        FiMAvailabilitySupport is configured as True.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : FiM_FunctionIdType FID                              **
**                        boolean Availability                                **
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
**                        FiM_GblInitStatus, FiM_GaaFidAvailableState         **
**                                                                            **
** Function(s) invoked :  Det_ReportError, FiM_FidSearch,                     **
**                        SchM_Enter_FiM_REQUEST_FID_PROTECTION,              **
**                        SchM_Exit_FiM_REQUEST_FID_PROTECTION                **
*******************************************************************************/
#if (FIM_AVAILABILITY_SUPPORT == STD_ON)

#define FIM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, FIM_CODE) FiM_SetFunctionAvailable(
  FiM_FunctionIdType FID, VAR(boolean, AUTOMATIC)Availability)
/* @Trace: SWS_Fim_00106 */
/* @Trace: SRS_Fim_04723 */
{
  /* @Trace: FiM_SUD_API_015 */
  boolean LblFidExists;
  Std_ReturnType LddReturn;
  FiM_FidsSizeType LddFidArrayIndex;
  LddReturn = E_NOT_OK;

  if (FiM_GucInitStatus != FIM_INITIALIZED)
  {
    /* Report to DET indicating wrong permission request */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: FiM_SUD_API_016 */
    FiM_Report_Error(FIM_SETFUNCTIONAVAILABLE_SID, FIM_E_UNINIT);
  }
  else
  {
    /* @Trace: FiM_SUD_API_017 */
    LblFidExists = FiM_FidSearch(FID, &LddFidArrayIndex);
    /* Check if FID is within the configured range */
    if (FIM_TRUE == LblFidExists)
    {
      /* Data Protection ON */
      /* @Trace: FiM_SUD_API_018 */
      SchM_Enter_FiM_REQUEST_FID_PROTECTION();
      /* Set Availability Status */
      FiM_GaaFidAvailableState[LddFidArrayIndex] = Availability;
      /* Data Protection OFF */
      SchM_Exit_FiM_REQUEST_FID_PROTECTION();
      LddReturn = E_OK;
    }
    else
    {
      /* FiM_GetFunctionPermission called with wrong FID */
      /* @Trace: SWS_Fim_00076 */
      /* @Trace: FiM_SUD_API_019 */
      FiM_Report_Error(FIM_SETFUNCTIONAVAILABLE_SID, FIM_E_FID_OUT_OF_RANGE);
    }
  }
  /* @Trace: FiM_SUD_API_020 */

  return LddReturn;
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
