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
**  SRC-MODULE: Det.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Default Error Tracer Module                           **
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
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     30-Sep-2019   DanhLT2      Initial Version                       **
** 0.0.2     13-Oct-2020   DanhLT2      Add unuse macro, #16382               **
*******************************************************************************/
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA C:2012 Amendment 1 - D4.14[Not a Defect] */     
/* polyspace-end MISRA C:2012 Amendment 1 - D4.14 */


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Det.h"                    /* Header file of DET */
#include "Det_Cfg.h"                /* Det Cfg header file */
#include "Det_PCTypes.h"            /* Det PCTypes file */
#include "Det_Ram.h"                /* Det Ram header file */
#include "Rte_Det.h"
#if (DET_RAM_BUFFER == STD_ON)
#include "SchM_Det.h"                /* Header file of SCHM */
#endif
#include "Det_Version.h"            /* Det Version header file */
#if (DET_FORWARD_TO_DLT == STD_ON)
#include "Dlt.h"                    /* Header file of DLT */
#endif
/* @Trace: SWS_Det_00037*/
/* @Trace: SRS_BSW_00346*/
/* @Trace: Det_SUD_FILE_001 File Structure*/
/*******************************************************************************
**                      Global Types                                          **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name       : Det_GetVersionInfo                                   **
**                                                                            **
** Service ID          : 0x03                                                 **
**                                                                            **
** Description         : This service gives version information of the Det    **
**                       module. The version information includes module Id,  **
**                       vendor Id, InstanceId & vendor specific version no's **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Reentrant                                            **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut Parameters    : versioninfo                                          **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : None                                                 **
**                                                                            **
** Preconditions       : DET_VERSION_INFO_API = STD_ON                        **
**                                                                            **
** Remarks             : Global Variable(s)  : None                           **
**                       Function(s) invoked : Det_ReportError                **
*******************************************************************************/
/* Check Pre-compile option enabled for versioninfo API */
#if (DET_VERSION_INFO_API == STD_ON)
#define DET_START_SEC_CODE
#include "MemMap.h"

FUNC(void, DET_CODE) Det_GetVersionInfo(P2VAR(Std_VersionInfoType,
  AUTOMATIC, DET_APPL_DATA) versioninfo)
/* @Trace: SWS_Det_00011*/
/* @Trace: SRS_BSW_00310*/
/* @Trace: SRS_BSW_00318*/
{
  /* Check whether the pointer passed to API is Null Pointer */
  if (NULL_PTR == versioninfo)
  /* @Trace: SWS_Det_00052*/
  /* @Trace: SRS_BSW_00480*/
  /* @Trace: Det_SUD_API_003*/
  {
    /* The Development Error Tracer shall not deliver the version information */
    /* if the received version info pointer is NULL and shall raise the Error */
    /* DET_E_PARAM_POINTER and return without any further action  */
    (void)Det_ReportError(DET_MODULE_ID, DET_INSTANCE_ID,
      DET_GETVERSIONINFO_SID, DET_E_PARAM_POINTER);
    /* @Trace: SWS_Det_00301*/
    /* @Trace: SRS_BSW_00337*/
  }
  else
  /* @Trace: Det_SUD_API_004*/
  {
    /* Copy the vendor Id */
    /* polyspace-begin MISRA C:2012 Amendment 1 - D4.14 [Not a Defect] This value is validate and generate by Generation tool */
    versioninfo->vendorID = DET_VENDOR_ID;      
    /* polyspace-end MISRA C:2012 Amendment 1 - D4.14 */

    /* Copy the module Id */
    versioninfo->moduleID = DET_MODULE_ID;

    /* Copy Software Major Version */
    versioninfo->sw_major_version = DET_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = DET_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = DET_SW_PATCH_VERSION;
  } /* End of else */
} /* End of Det_GetVersionInfo */

#define DET_STOP_SEC_CODE
#include "MemMap.h"
#endif /* DET_VERSION_INFO_API == STD_ON */

/*******************************************************************************
** Function Name      : Det_Init                                              **
**                                                                            **
** Service ID         : 0x00                                                  **
**                                                                            **
** Description        : This function is used to clear the logged errors and  **
**                      the reported error count.                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ConfigPtr                                             **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :Det_GusErrorsBuffIndex,           **
**                                          Det_GblInitStatus                 **
**                      Function(s) invoked:None                              **
*******************************************************************************/
#define DET_START_SEC_CODE
#include "MemMap.h"

FUNC(void, DET_CODE) Det_Init(P2CONST(Det_ConfigType,
  AUTOMATIC, DET_APPL_CONST)ConfigPtr)
/* @Trace: SWS_Det_00210*/
/* @Trace: SWS_Det_00008*/
/* @Trace: SRS_BSW_00310*/
/* @Trace: SRS_BSW_00414*/
/* @Trace: SRS_BSW_00358*/
{
  /* polyspace-begin MISRA-C3:11.8 [Justified:Low] "Not a Defect" */
  P2VAR(Det_ErrorStatusType, AUTOMATIC, DET_APPL_DATA)ptrErrorStatus;
  DET_UNUSED_PTR(ConfigPtr);
  /* polyspace-end MISRA-C3:11.8 */
  /* @Trace: Det_SUD_API_002*/
  {
    ptrErrorStatus = &Det_GaaErrorStatus;

    #if (DET_RAM_BUFFER == STD_ON)
    /* Initialize RAM buffer index */
    ptrErrorStatus->ErrorCount = DET_ZERO;
    #endif /* DET_RAM_BUFFER == STD_ON */

    #if ((DET_ERROR_HOOK == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
    /* Initialize RAM buffer index */
    ptrErrorStatus->ErrorHook = DET_ERROR_HOOK_IDLE;
    #endif /* ((DET_ERROR_HOOK == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON)) */

    #if ((DET_ERROR_RUNTIME == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
    /* Initialize RAM buffer index */
    ptrErrorStatus->RuntimeError = DET_ERROR_HOOK_IDLE;
    #endif /* ((DET_ERROR_RUNTIME == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON)) */

    #if ((DET_ERROR_FAULT_TRANSIENT == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
    /* Initialize RAM buffer index */
    ptrErrorStatus->TransientFault = DET_ERROR_HOOK_IDLE;
    #endif /* ((DET_ERROR_FAULT_TRANSIENT == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON)) */

    /* Update the module init status variable */
    Det_GblInitStatus = DET_INITIALIZED;
    /* @Trace: SWS_Det_00020*/
    /* @Trace: SRS_BSW_00101*/
    /* @Trace: Det_SUD_API_001*/
  }
} /* End of Det_Init */

#define DET_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Det_ReportError                                       **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : Development Error Tracer to report errors.            **
**                                                                            **
** Sync/Async         : Depending on implemented functionality: 1. Breakpoint **
**                      set: no return 2. Internal error counting/logging in  **
**                      RAM: synchronous 3. External error logging via        **
**                      communication interface: asynchronous                 **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : uint16 ModuleId                                       **
**                      uint8 InstanceId                                      **
**                      uint8 ApiId                                           **
**                      uint8 ErrorId                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :Det_GaaErrorStatus                **
**                                          Det_GaaErrors                     **
**                                          Det_GblInitStatus                 **
**                      Function(s) invoked:Dlt_DetForwardErrorTrace(),       **
**                                       SchM_Enter_Det_RAM_DATA_PROTECTION(),**
**                                       SchM_Exit_Det_RAM_DATA_PROTECTION()  **
*******************************************************************************/
#define DET_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, DET_CODE) Det_ReportError(uint16 ModuleId, uint8
  InstanceId, uint8 ApiId, uint8 ErrorId)
/* @Trace: SWS_Det_00009*/
/* @Trace: SRS_BSW_00310*/
/* @Trace: SRS_Diag_04086*/
/* @Trace: SRS_Diag_04085*/
/* @Trace: SRS_BSW_00312*/
/* @Trace: SRS_Diag_04087*/
/* @Trace: SRS_Diag_04089*/
{
  P2VAR(Det_ErrorStatusType, AUTOMATIC, DET_APPL_DATA)ptrErrorStatus;
  #if (DET_RAM_BUFFER == STD_ON)
  P2VAR(Det_ErrorType, AUTOMATIC, DET_APPL_DATA) LpErrors;
  #endif
  Std_ReturnType LddReturnVal;
  #if (DET_ERROR_HOOK == STD_ON)
  uint8 LucErrCount;
  #endif

  /* This API call will be always success */
  LddReturnVal = E_OK;
  /* Module state after Initialization function */
  if (DET_INITIALIZED == Det_GblInitStatus)
  /* @Trace: SWS_Det_00024*/
  /* @Trace: SRS_BSW_00406*/
  /* @Trace: Det_SUD_API_006*/
  {
    ptrErrorStatus = &Det_GaaErrorStatus;
    #if((DET_ERROR_HOOK == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
    if(DET_ERROR_HOOK_IDLE == ptrErrorStatus->ErrorHook)
    /* @Trace: SWS_Det_00026 */
    /* @Trace: SRS_BSW_00337 */
  /* @Trace: Det_SUD_API_007*/
    {
      /* DET is not called recursively */
      ptrErrorStatus->ErrorHook = DET_ERROR_HOOK_BUSY;
      /* Invoke configured Error Hook Functions */
      #if (DET_ERROR_HOOK == STD_ON)
      for(LucErrCount = DET_ZERO;
              LucErrCount < DET_TOTAL_ERROR_HOOKS; LucErrCount++)
      /* @Trace: SWS_Det_00014 */
      /* @Trace: SWS_Det_00018 */
      /* @Trace: SRS_BSW_00345 */
      /* @Trace: SRS_BSW_00403 */
      {
        (void)(*Det_GaaErrorHook[LucErrCount]) (
                ModuleId, InstanceId, ApiId, ErrorId);
        /* @Trace: SWS_Det_00035 */
        /* @Trace: SWS_Det_00501 */
        /* @Trace: SWS_Det_00180 */
        /* @Trace: SWS_Det_00181 */
        /* @Trace: SRS_BSW_00167 */
        /* @Trace: SRS_BSW_00392 */
        /* @Trace: SRS_BSW_00394 */
        /* @Trace: SRS_BSW_00345 */
        /* @Trace: SRS_BSW_00463 */
        /* @Trace: Det_SUD_API_008*/
      }
      #endif /* DET_ERROR_HOOK == STD_ON */
      /* @Trace: SWS_Det_00015 */
      /* @Trace: SRS_BSW_00171 */
      /* Forward error to Dlt */
      #if (DET_FORWARD_TO_DLT == STD_ON)
      Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
      /* @Trace: SWS_Det_00034*/
      /* @Trace: SWS_Det_00211*/
      /* @Trace: SRS_Diag_04101*/
      /* @Trace: Det_SUD_API_009*/
      #endif /* DET_FORWARD_TO_DLT == STD_ON */
      ptrErrorStatus->ErrorHook = DET_ERROR_HOOK_IDLE;
    }
    else
    {
      /* To avoid QAC warning */
    }
    #endif /* (DET_ERROR_HOOK == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON) */
    #if (DET_RAM_BUFFER == STD_ON)
    /* @Trace: Det_SUD_API_010*/
    /* Invoke function to enable data protection */
    SchM_Enter_Det_RAM_DATA_PROTECTION();
    /* check if Det_GusErrorsBuffIndex is over of ram buffer size */
    if((ptrErrorStatus->ErrorCount) >= DET_RAM_BUFFER_SIZE)
    {
      /* Initialize array of structure index */
      ptrErrorStatus->ErrorCount = DET_ONE;
    }
    else
    {
      /* To avoid QAC warning */
      /* Increment array of structure index */
      (ptrErrorStatus->ErrorCount)++;
    }
    /* Get a pointer to point global structure Det_GaaErrors */
    LpErrors = &Det_GaaErrors[ptrErrorStatus->ErrorCount-DET_ONE];
    /* Store development error parameter got through Det_ReportError function */
    LpErrors->usModuleId = ModuleId;
    LpErrors->ucInstanceId = InstanceId;
    LpErrors->ucApiId = ApiId;
    LpErrors->ucErrorId = ErrorId;
    /* Invoke function to disable data protection */
    SchM_Exit_Det_RAM_DATA_PROTECTION();
    #endif /* DET_RAM_BUFFER == STD_ON */
  } /* End of if (Det_GblInitStatus == DET_INITIALIZED) */
  else
  {
    /* If the Default Error Tracer has not been initialized before */ 
    /* Det reporting functions are called, the reporting functions shall */
    /* return immediately without any other action */
  }
  return (LddReturnVal);
} /* End of Det_ReportError */

#define DET_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Det_Start                                             **
**                                                                            **
** Service ID         : 0x02                                                  **
**                                                                            **
** Description        : This functionality is defined when development errors **
**                      are logged via communication interface                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :None                              **
**                      Function(s) invoked:None                              **
*******************************************************************************/
#define DET_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DET_CODE) Det_Start(void)
/* @Trace: SWS_Det_00010*/
/* @Trace: SRS_BSW_00310*/
/* @Trace: Det_SUD_API_005*/
/* @Trace: SRS_BSW_00350*/
{
  /* Empty function */
}

#define DET_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Det_ReportRuntimeError                                **
**                                                                            **
** Service ID         : 0x04                                                  **
**                                                                            **
** Description        : Development Error Tracer to report errors.            **
**                                                                            **
** Sync/Async         : Depending on implemented functionality: 1. Breakpoint **
**                      set: no return 2. Internal error counting/logging in  **
**                      RAM: synchronous 3. External error logging via        **
**                      communication interface: asynchronous                 **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : uint16 ModuleId                                       **
**                      uint8 InstanceId                                      **
**                      uint8 ApiId                                           **
**                      uint8 ErrorId                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :Det_GaaErrorStatus                **
**                                          Det_GaaErrors                     **
**                                          Det_GblInitStatus                 **
**                      Function(s) invoked:Dlt_DetForwardErrorTrace(),       **
**                                       SchM_Enter_Det_RAM_DATA_PROTECTION(),**
**                                       SchM_Exit_Det_RAM_DATA_PROTECTION()  **
*******************************************************************************/
#define DET_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, DET_CODE) Det_ReportRuntimeError(uint16 ModuleId, uint8
  InstanceId, uint8 ApiId, uint8 ErrorId)
/* @Trace: SWS_Det_01001*/
/* @Trace: SRS_BSW_00310*/
/* @Trace: SRS_Diag_04086*/
/* @Trace: SRS_Diag_04143*/
/* @Trace: SRS_BSW_00312*/
/* @Trace: SRS_Diag_04087*/
/* @Trace: SRS_Diag_04089*/
{
  P2VAR(Det_ErrorStatusType, AUTOMATIC, DET_APPL_DATA)ptrErrorStatus;
  #if (DET_RAM_BUFFER == STD_ON)
  P2VAR(Det_ErrorType, AUTOMATIC, DET_APPL_DATA) LpErrors;
  #endif
  Std_ReturnType LddReturnVal;
  #if (DET_ERROR_RUNTIME == STD_ON)
  uint8 LucErrRuntimeCount;
  #endif

  /* This API call will be always success */
  LddReturnVal = E_OK;
  /* Module state after Initialization function */
  if (Det_GblInitStatus == DET_INITIALIZED)
  /* @Trace: SWS_Det_00024*/
  /* @Trace: SRS_BSW_00406*/
  /* @Trace: Det_SUD_API_011*/
  {
    ptrErrorStatus = &Det_GaaErrorStatus;
    #if((DET_ERROR_RUNTIME == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
    if(DET_ERROR_HOOK_IDLE == ptrErrorStatus->RuntimeError)
    /* @Trace: SWS_Det_00026 */
    /* @Trace: SRS_BSW_00337 */
    /* @Trace: Det_SUD_API_012*/
    {
      ptrErrorStatus->RuntimeError = DET_ERROR_HOOK_BUSY;
      /* Invoke configured ReportRuntimeErrorCallout Functions */
      #if (DET_ERROR_RUNTIME == STD_ON)
      for(LucErrRuntimeCount = DET_ZERO;
              LucErrRuntimeCount < DET_TOTAL_ERROR_RUNTIME;
              LucErrRuntimeCount++)
      /* @Trace: SWS_Det_00014 */
      /* @Trace: SWS_Det_00018 */
      /* @Trace: SRS_BSW_00345 */
      /* @Trace: SRS_BSW_00403 */
      {
          (void)(*Det_GaaRuntimeErrorCallout[LucErrRuntimeCount]) (
                          ModuleId, InstanceId, ApiId, ErrorId);
          /* @Trace: SWS_Det_00035 */
          /* @Trace: SWS_Det_00503 */
          /* @Trace: SWS_Det_00180 */
          /* @Trace: SWS_Det_00184 */
          /* @Trace: SRS_BSW_00167 */
          /* @Trace: SRS_BSW_00392 */
          /* @Trace: SRS_BSW_00394 */
          /* @Trace: SRS_BSW_00345 */
          /* @Trace: SRS_BSW_00463 */
          /* @Trace: Det_SUD_API_013*/
      }
      #endif /* DET_ERROR_RUNTIME == STD_ON */
      /* @Trace: SWS_Det_00015 */
      /* @Trace: SRS_BSW_00171 */
      /* Forward error to Dlt */
      #if (DET_FORWARD_TO_DLT == STD_ON)
      Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
      /* @Trace: SWS_Det_00034*/
      /* @Trace: SWS_Det_00211*/
      /* @Trace: SRS_Diag_04101*/
      /* @Trace: Det_SUD_API_014*/
      #endif /* DET_FORWARD_TO_DLT == STD_ON */
      ptrErrorStatus->RuntimeError = DET_ERROR_HOOK_IDLE;
    }
    else
    {
      /* To avoid QAC warning */
    }
    #endif /* (DET_ERROR_RUNTIME == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON) */
    #if (DET_RAM_BUFFER == STD_ON)
    /* @Trace: Det_SUD_API_015*/
    /* Invoke function to enable data protection */
    SchM_Enter_Det_RAM_DATA_PROTECTION();
    /* check if Det_GusErrorsBuffIndex is over of ram buffer size */
    if ((ptrErrorStatus->ErrorCount) >= DET_RAM_BUFFER_SIZE)
    {
      /* Initialize array of structure index */
      ptrErrorStatus->ErrorCount = DET_ONE;
    }
    else
    {
      /* To avoid QAC warning */
      /* Increment array of structure index */
      (ptrErrorStatus->ErrorCount)++;
    }
    /* Get a pointer to point global structure Det_GaaErrors */
    LpErrors = &Det_GaaErrors[ptrErrorStatus->ErrorCount-DET_ONE];
    /* Store development error parameter got through Det_ReportError function */
    LpErrors->usModuleId = ModuleId;
    LpErrors->ucInstanceId = InstanceId;
    LpErrors->ucApiId = ApiId;
    LpErrors->ucErrorId = ErrorId;
    /* Invoke function to disable data protection */
    SchM_Exit_Det_RAM_DATA_PROTECTION();
    #endif /* DET_RAM_BUFFER == STD_ON */
  } /* End of if (Det_GblInitStatus == DET_INITIALIZED) */
  else
  {
    /* To avoid QAC warning */
  }
  return (LddReturnVal);
} /* End of Det_ReportError */

#define DET_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Det_ReportTransientFault                              **
**                                                                            **
** Service ID         : 0x05                                                  **
**                                                                            **
** Description        : Development Error Tracer to report errors.            **
**                                                                            **
** Sync/Async         : Depending on implemented functionality: 1. Breakpoint **
**                      set: no return 2. Internal error counting/logging in  **
**                      RAM: synchronous 3. External error logging via        **
**                      communication interface: asynchronous                 **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : uint16 ModuleId                                       **
**                      uint8 InstanceId                                      **
**                      uint8 ApiId                                           **
**                      uint8 ErrorId                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :Det_GaaErrorStatus                **
**                                          Det_GaaErrors                     **
**                                          Det_GblInitStatus                 **
**                      Function(s) invoked:Dlt_DetForwardErrorTrace(),       **
**                                       SchM_Enter_Det_RAM_DATA_PROTECTION(),**
**                                       SchM_Exit_Det_RAM_DATA_PROTECTION()  **
*******************************************************************************/
#define DET_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, DET_CODE) Det_ReportTransientFault(uint16 ModuleId, uint8
  InstanceId, uint8 ApiId, uint8 ErrorId)
/* @Trace: SWS_Det_01003*/
/* @Trace: SRS_BSW_00310*/
/* @Trace: SRS_Diag_04086*/
/* @Trace: SRS_Diag_04144*/
/* @Trace: SRS_BSW_00312*/
/* @Trace: SRS_Diag_04087*/
/* @Trace: SRS_Diag_04089*/
{
  P2VAR(Det_ErrorStatusType, AUTOMATIC, DET_APPL_DATA)ptrErrorStatus;
  #if (DET_RAM_BUFFER == STD_ON)
  P2VAR(Det_ErrorType, AUTOMATIC, DET_APPL_DATA) LpErrors;
  #endif
  Std_ReturnType LddReturnVal;
  #if (DET_ERROR_FAULT_TRANSIENT == STD_ON)
  uint8 LucErrTransientFaultCount;
  #endif

  /* This API call will be always success */
  LddReturnVal = E_OK;
  /* Module state after Initialization function */
  if (Det_GblInitStatus == DET_INITIALIZED)
  /* @Trace: SWS_Det_00024*/
  /* @Trace: SRS_BSW_00406*/
  /* @Trace: Det_SUD_API_016*/
  {
    ptrErrorStatus = &Det_GaaErrorStatus;
    #if((DET_ERROR_FAULT_TRANSIENT == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
    if(DET_ERROR_HOOK_IDLE == ptrErrorStatus->TransientFault)
    /* @Trace: SWS_Det_00026 */
    /* @Trace: SRS_BSW_00337 */
    /* @Trace: Det_SUD_API_017*/
    {
      ptrErrorStatus->TransientFault = DET_ERROR_HOOK_BUSY;
      /* Invoke configured ReportTransientFault Functions */
      #if (DET_ERROR_FAULT_TRANSIENT == STD_ON)
      for(LucErrTransientFaultCount = DET_ZERO;
              LucErrTransientFaultCount < DET_TOTAL_ERROR_FAULT_TRANSIENT;
              LucErrTransientFaultCount++)
      /* @Trace: SWS_Det_00014 */
      /* @Trace: SWS_Det_00018 */
      /* @Trace: SRS_BSW_00345 */
      /* @Trace: SRS_BSW_00403 */
      {
          LddReturnVal |= (Std_ReturnType)(
                  *Det_GaaTransientFaultCallout[LucErrTransientFaultCount]) (
                          ModuleId, InstanceId, ApiId, ErrorId);
          /* @Trace: SWS_Det_00035 */
          /* @Trace: SWS_Det_00502 */
          /* @Trace: SWS_Det_00180 */
          /* @Trace: SWS_Det_00187 */
          /* @Trace: SRS_BSW_00167 */
          /* @Trace: SRS_BSW_00392 */
          /* @Trace: SRS_BSW_00394 */
          /* @Trace: SRS_BSW_00345 */
          /* @Trace: SRS_BSW_00463 */
          /* @Trace: Det_SUD_API_018*/
      }
      #endif /* DET_ERROR_FAULT_TRANSIENT == STD_ON */
      /* @Trace: SWS_Det_00015 */
      /* @Trace: SRS_BSW_00171 */
      /* Forward error to Dlt */
      #if (DET_FORWARD_TO_DLT == STD_ON)
      Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
      /* @Trace: SWS_Det_00034*/
      /* @Trace: SWS_Det_00211*/
      /* @Trace: SRS_Diag_04101*/
      /* @Trace: Det_SUD_API_019*/
      #endif /* DET_FORWARD_TO_DLT == STD_ON */
      ptrErrorStatus->TransientFault = DET_ERROR_HOOK_IDLE;
    }
    else
    {
      /* To avoid QAC warning */
    }
    #endif /* (DET_ERROR_FAULT_TRANSIENT == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON) */
    #if (DET_RAM_BUFFER == STD_ON)
    /* @Trace: Det_SUD_API_020*/
    /* Invoke function to enable data protection */
    SchM_Enter_Det_RAM_DATA_PROTECTION();
    /* check if Det_GusErrorsBuffIndex is over of ram buffer size */
    if (ptrErrorStatus->ErrorCount >= DET_RAM_BUFFER_SIZE)
    {
      /* Initialize array of structure index */
      ptrErrorStatus->ErrorCount = DET_ONE;
    }
    else
    {
      /* Increment array of structure index */
      (ptrErrorStatus->ErrorCount)++;
    }
    /* Get a pointer to point global structure Det_GaaErrors */
    LpErrors = &Det_GaaErrors[ptrErrorStatus->ErrorCount-DET_ONE];
    /* Store development error parameter got through Det_ReportError function */
    LpErrors->usModuleId = ModuleId;
    LpErrors->ucInstanceId = InstanceId;
    LpErrors->ucApiId = ApiId;
    LpErrors->ucErrorId = ErrorId;
    /* Invoke function to disable data protection */
    SchM_Exit_Det_RAM_DATA_PROTECTION();
    #endif /* DET_RAM_BUFFER == STD_ON */
  } /* End of if (Det_GblInitStatus == DET_INITIALIZED) */
  else
  {
    /* To avoid QAC warning */
  }
  return (LddReturnVal);
} /* End of Det_ReportError */

#define DET_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
