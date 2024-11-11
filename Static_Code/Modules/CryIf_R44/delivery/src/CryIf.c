/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Define all functions of module CryIf                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.1.0   20-Mar-2021        TamTV6       Fix #18131,#18132,#18326,#18461, **
**                                           Add trace SUD                    **
** 1.0.4.0   01-Dec-2022        DienTC1      #CP44-996                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* For module header */
#include "CryIf.h"
/* For global variables */
#include "CryIf_Globals.h"
/* For internal functions */
#include "CryIf_IntFunc.h"
/* Enable to detect development errors */
#if (STD_ON == CRYIF_DEV_ERROR_DETECT)
  /* For Det functions */
  #include "Det.h"
#endif

#define CRYIF_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CryIf_Init                                          **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Initializes the CRYIF module.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : configPtr: Pointer to a selected configuration      **
**                                   structure                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_BSW_00101 SWS_BSW_00050 SRS_BSW_00358 SRS_BSW_00414 SRS_BSW_00388 */
FUNC(void, CRYIF_CODE) CryIf_Init(\
  P2CONST(CryIf_ConfigType, AUTOMATIC, CRYIF_APPL_CONST) configPtr)
{
  /* Check pointer because it shall always have a null pointer value */
  if ((NULL_PTR != configPtr) || (TRUE == CryIf_ModuleInitialized))
  {
    /* @Trace: CryIf_SUD_FUNC_002 */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_INIT_SID, CRYIF_E_INIT_FAILED);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_001 */
    /* Unused parameter */
    CRYIF_UNUSED(configPtr);
    /* Initialize the global variables */
    CryIf_ModuleInitialized = TRUE;
  }
} /* End of CryIf_Init */

/*******************************************************************************
** Function Name        : CryIf_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Returns the version information of this module.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : versioninfo: Pointer to where to store the version  **
**                          information of this module.                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_BSW_00407 SRS_BSW_00402 */
/* If enable to support Version information */
#if (STD_ON == CRYIF_VERSION_INFO_API)
  FUNC(void, CRYIF_CODE) CryIf_GetVersionInfo(\
    P2VAR(Std_VersionInfoType, AUTOMATIC, CRYIF_APPL_DATA) versioninfo)
  {
    if (NULL_PTR == versioninfo)
    {
      /* @Trace: CryIf_SUD_FUNC_004 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the parameter job is a null pointer */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_GETVERSIONINFO_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_003 */
      /* Copy the vendor Id */
      versioninfo->vendorID = CRYIF_VENDOR_ID;
      /* Copy the module Id */
      versioninfo->moduleID = CRYIF_MODULE_ID;
      /* Copy Software Major Version */
      versioninfo->sw_major_version = CRYIF_SW_MAJOR_VERSION;
      /* Copy Software Minor Version */
      versioninfo->sw_minor_version = CRYIF_SW_MINOR_VERSION;
      /* Copy Software Patch Version */
      versioninfo->sw_patch_version = CRYIF_SW_PATCH_VERSION;
    }
  } /* End of CryIf_GetVersionInfo */
#endif

/*******************************************************************************
** Function Name        : CryIf_ProcessJob                                    **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This interface dispatches the received jobs to the  **
**                        configured crypto driver object.                    **
**                                                                            **
** Sync/Async           : Sync or Async, depends on the configuration         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : channelId: Holds the identifier of the crypto       **
**                                   channel.                                 **
**                                                                            **
** InOut Parameters     : job: Pointer to the configuration of the job.       **
**                             Contains structures with user and primitive    **
**                             relevant information.                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_NOT_VALID: Request failed,           **
**                            the key is not valid                            **
**                          CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key **
**                            element has the wrong size                      **
**                          CRYPTO_E_QUEUE_FULL: Request failed,              **
**                            the queue is full                               **
**                          CRYPTO_E_KEY_READ_FAIL: The service request failed**
**                            because key element extraction is not allowed   **
**                          CRYPTO_E_KEY_WRITE_FAIL: The service request      **
**                            failed because the writing access failed        **
**                          CRYPTO_E_KEY_NOT_AVAILABLE: The service request   **
**                            failed because the key is not available         **
**                          CRYPTO_E_SMALL_BUFFER: The provided buffer is too **
**                            small to store the result                       **
**                          CRYPTO_E_JOB_CANCELED: The service request failed **
**                            because the synchronous Job has been canceled   **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_ChannelList[]           **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_ProcessJobPtr[]         **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexChannel()       **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_ProcessJob()           **
**                                              CryIf_DispatchKey()           **
**                                              CryIf_RedirectKey()           **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00015 SRS_CryptoStack_00009 SRS_CryptoStack_00075 SRS_CryptoStack_00076 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_ProcessJob(\
  VAR(uint32, AUTOMATIC) channelId,\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of channel id array */
  VAR(uint32, AUTOMATIC) indexArrChannel;
  /* Variable holds information of channel */
  P2CONST(CryIf_ChannelType, AUTOMATIC, CRYIF_APPL_CONST) channelPtr;
  /* Variable holds index of key id array for source key */
  VAR(uint32, AUTOMATIC) cryIfKeyTemp;
  /* Variable holds service of job */
  VAR(Crypto_ServiceInfoType, AUTOMATIC) serviceJob;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_005 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_PROCESSJOB_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_006 */
    /* Get index of channel id array from channelId */
    indexArrChannel = CryIf_GetIndexChannel(channelId);
    if (CRYIF_TOTAL_CHANNEL_ID_NUMBER <= indexArrChannel)
    {
      /* @Trace: CryIf_SUD_FUNC_007 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the parameter channelId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_PROCESSJOB_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if (NULL_PTR == job)
    {
      /* @Trace: CryIf_SUD_FUNC_008 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the parameter job is a null pointer */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_PROCESSJOB_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else if ((NULL_PTR == job->jobPrimitiveInfo) || \
      (NULL_PTR == job->jobPrimitiveInfo->primitiveInfo))
    {
      /* Return E_NOT_OK */
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_009 */
      /* Get service of job from pointer job */
      serviceJob = job->jobPrimitiveInfo->primitiveInfo->service;
      cryIfKeyTemp = job->jobPrimitiveInfo->cryIfKeyId;
      /* Dispatch key */
      retVal = CryIf_DispatchKey(job, serviceJob, cryIfKeyTemp);
      if (E_OK == retVal)
      {
        /* @Trace: CryIf_SUD_FUNC_011 */
        /* Adapt key redirection */
        retVal = CryIf_RedirectKey(job);
        if (E_OK == retVal)
        {
          /* @Trace: CryIf_SUD_FUNC_012 */
          channelPtr = &CryIf_ChannelList[indexArrChannel];
          /* Call Crypto_ProcessJob() of underlying crypto driver */
          retVal = CryIf_ProcessJobPtr[channelPtr->IndexFunc](\
            channelPtr->ObjectId, job);
        }
      }
      else
      {
        /* @Trace: CryIf_SUD_FUNC_010 */
        #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
          /* Report error to Det if targetCryIfKeyId is out of range */
          (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
            CRYIF_PROCESSJOB_SID, CRYIF_E_PARAM_HANDLE);
        #endif
      }
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_ProcessJob() */

/*******************************************************************************
** Function Name        : CryIf_CancelJob                                     **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This interface dispatches the job cancellation      **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : channelId: Holds the identifier of the crypto       **
**                                   channel.                                 **
**                                                                            **
** InOut Parameters     : job: Pointer to the configuration of the job.       **
**                             Contains structures with user and primitive    **
**                             relevant information.                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful, job has been removed    **
**                          E_NOT_OK: Request failed, job couldn't be removed **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_ChannelList[]           **
**                                              CryIf_CancelJobPtr[]          **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexChannel()       **
**                                              Crypto_CancelJob()            **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CancelJob(\
  VAR(uint32, AUTOMATIC) channelId,\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of channel id array */
  VAR(uint32, AUTOMATIC) indexArrChannel;
  /* Variable holds information of channel */
  P2CONST(CryIf_ChannelType, AUTOMATIC, CRYIF_APPL_CONST) channelPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_013 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_CANCELJOB_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_014 */
    /* Get index of channel id array from channelId */
    indexArrChannel = CryIf_GetIndexChannel(channelId);
    if (CRYIF_TOTAL_CHANNEL_ID_NUMBER <= indexArrChannel)
    {
      /* @Trace: CryIf_SUD_FUNC_015 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the parameter channelId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_CANCELJOB_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if (NULL_PTR == job)
    {
      /* @Trace: CryIf_SUD_FUNC_016 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the parameter job is a null pointer */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_CANCELJOB_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_017 SRS_CryptoStack_00014 */
      channelPtr = &CryIf_ChannelList[indexArrChannel];
      /* Call Crypto_CancelJob() of corresponding crypto driver */
      retVal = CryIf_CancelJobPtr[channelPtr->IndexFunc](\
        channelPtr->ObjectId, job);
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_CancelJob */

/*******************************************************************************
** Function Name        : CryIf_KeyElementSet                                 **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This function shall dispatch the set key element    **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key         **
**                          whose key element shall be set.                   **
**                        keyElementId: Holds the identifier of the key       **
**                          element which shall be set.                       **
**                        keyPtr: Holds the pointer to the key data           **
**                          which shall be set as key element.                **
**                        keyLength: Contains the length of the key element   **
**                          in bytes.                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_WRITE_FAIL: Request failed because   **
**                            write access was denied                         **
**                          CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the   **
**                            key  is not available                           **
**                          CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key **
**                           element size does not match size of provided data**
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyElementSetPtr[]      **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_KeyElementSet()        **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementSet(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  P2CONST(uint8, AUTOMATIC, CRYIF_APPL_CONST) keyPtr,\
  VAR(uint32, AUTOMATIC) keyLength)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_018 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYELEMENTSET_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_019 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      /* @Trace: CryIf_SUD_FUNC_020 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the cryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTSET_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if (NULL_PTR == keyPtr)
    {
      /* @Trace: CryIf_SUD_FUNC_021 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the parameter keyPtr is a null pointer */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTSET_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else if (CRYIF_ZERO_VALUE == keyLength)
    {
      /* @Trace: CryIf_SUD_FUNC_022 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the keyLength is zero */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTSET_SID, CRYIF_E_PARAM_VALUE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_023 */
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      /* Call Crypto_KeyElementSet() of corresponding crypto driver */
      retVal = CryIf_KeyElementSetPtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId, keyElementId, keyPtr, keyLength);
    }
  }

  return retVal;
} /* End of CryIf_KeyElementSet */

/*******************************************************************************
** Function Name        : CryIf_KeySetValid                                   **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This function shall dispatch the set key valid      **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key         **
**                          whose key element shall be set to valid.          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeySetValidPtr[]        **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              Crypto_KeySetValid()          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeySetValid(\
  VAR(uint32, AUTOMATIC) cryIfKeyId)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  cryIfKeyPtr = NULL_PTR;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_024 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYSETVALID_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_025 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER;
    while ((CRYIF_ZERO_VALUE < indexArrKey) && (E_OK != retVal))
    {
      indexArrKey--;
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      if (cryIfKeyPtr->CryIfKeyId == cryIfKeyId)
      {
        retVal = E_OK;
      }
    }
    if (E_OK != retVal)
    {
      /* @Trace: CryIf_SUD_FUNC_026 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the cryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYSETVALID_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_027 */
      /* Call Crypto_KeySetValid() of corresponding crypto driver */
      retVal = CryIf_KeySetValidPtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId);
    }
  }

  return retVal;
} /* End of CryIf_KeySetValid */

/*******************************************************************************
** Function Name        : CryIf_KeyElementGet                                 **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This function shall dispatch the get key element    **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key         **
**                          whose key element shall be returned.              **
**                        keyElementId: Holds the identifier of the key       **
**                          element which shall be returned                   **
**                                                                            **
** InOut Parameters     : resultLengthPtr: Holds a pointer to a memory        **
**                          location in which the length information is stored**
**                          On calling this function this parameter shall     **
**                          contain the size of the buffer provided by        **
**                          resultPtr. If the key element is configured to    **
**                          allow partial access, this parameter contains the **
**                          amount of data which should be read from the key  **
**                          element. The size may not be equal to the size of **
**                          the provided buffer anymore. When the request has **
**                          finished, the amount of data that has been stored **
**                          shall be stored.                                  **
**                                                                            **
** Output Parameters    : resultPtr: Holds the pointer of the buffer for the  **
**                          returned key element                              **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the   **
**                            requested key element is not available          **
**                          CRYPTO_E_KEY_READ_FAIL: Request failed because    **
**                            read access was denied                          **
**                          CRYPTO_E_SMALL_BUFFER: The provided buffer is too **
**                            small to store the result                       **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyElementGetPtr[]      **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_KeyElementGet()        **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementGet(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) resultPtr,\
  P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) resultLengthPtr)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_028 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYELEMENTGET_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_029 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      /* @Trace: CryIf_SUD_FUNC_030 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the cryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTGET_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if ((NULL_PTR == resultPtr) || (NULL_PTR == resultLengthPtr))
    {
      /* @Trace: CryIf_SUD_FUNC_031 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /*
         * Report error to Det if the parameter resultPtr or resultLengthPtr
         * is a null pointer
         */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTGET_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else if (CRYIF_ZERO_VALUE == (*resultLengthPtr))
    {
      /* @Trace: CryIf_SUD_FUNC_032 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the Length value is zero */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTGET_SID, CRYIF_E_PARAM_VALUE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_033 */
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      /* Call Crypto_KeyElementGet() of corresponding crypto driver */
      retVal = CryIf_KeyElementGetPtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId, keyElementId, resultPtr, resultLengthPtr);
    }
  }

  return retVal;
} /* End of CryIf_KeyElementGet */

/*******************************************************************************
** Function Name        : CryIf_KeyElementCopy                                **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This function shall copy a key elements from one key**
**                        to a target key                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for the same cryIfKeyId          **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key whose   **
**                          key element shall be the source element.          **
**                        keyElementId: Holds the identifier of the key       **
**                          element which shall be the source for the copy    **
**                          operation.                                        **
**                        targetCryIfKeyId: Holds the identifier of the key   **
**                          whose key element shall be the destination element**
**                        targetKeyElementId: Holds the identifier of the key **
**                          element which shall be the destination for the    **
**                          copy operation.                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_NOT_AVAILABLE:  Request failed, the  **
**                            requested key element is not available          **
**                          CRYPTO_E_KEY_READ_FAIL: Request failed,           **
**                            not allowed to extract key element              **
**                          CRYPTO_E_KEY_WRITE_FAIL: Request failed,          **
**                            not allowed to write key element                **
**                          CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key **
**                            element sizes are not compatible                **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyElementList[]        **
**                                              CryIf_KeyElementCopyPtr[]     **
**                                              CryIf_KeyElementGetPtr[]      **
**                                              CryIf_KeyElementSetPtr[]      **
**                                              CryIf_KeySourceData[]         **
**                                              CryIf_TargetElementArray[]    **
**                                              CryIf_KeyElementIdsGetPtr[]   **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              CryIf_GetIndexKeyElement()    **
**                                              Crypto_KeyElementGet()        **
**                                              Crypto_KeyElementSet()        **
**                                              Crypto_KeyElementCopy()       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopy(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetKeyElementId)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for source key */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds index of key id array for target key */
  VAR(uint32, AUTOMATIC) indexArrTargetKey;
  /* Variable holds index of key element id array for targetKeyElementId */
  VAR(uint32, AUTOMATIC) indexSourceElement;
  /* Variable holds index of key element id array for targetKeyElementId */
  VAR(uint32, AUTOMATIC) indexTargetElement;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeySource;
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyTarget;
  /* Variable holds buffer length of key */
  VAR(uint32, AUTOMATIC) keyLength;
  /* Variable holds number of key elements */
  VAR(uint32, AUTOMATIC) numElementSource;
  VAR(uint32, AUTOMATIC) numElementTarget;

  /* Set value for variable */
  retVal = E_NOT_OK;
  numElementSource = CRYIF_MAX_KEY_ELEMENT_NUMBER;
  numElementTarget = CRYIF_MAX_KEY_ELEMENT_NUMBER;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_034 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYELEMENTCOPY_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_035 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    /* Get index of key id array from targetCryIfKeyId */
    indexArrTargetKey = CryIf_GetIndexKey(targetCryIfKeyId);
    if ((CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey) || \
      (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrTargetKey))
    {
      /* @Trace: CryIf_SUD_FUNC_036 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report to Det if the cryIfKeyId, targetCryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTCOPY_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_037 */
      /* Update key information */
      cryIfKeySource = &CryIf_CryIfKeyList[indexArrKey];
      cryIfKeyTarget = &CryIf_CryIfKeyList[indexArrTargetKey];
      /* Get key element id of crypto driver */
      retVal = CryIf_KeyElementIdsGetPtr[cryIfKeySource->IndexFunc](\
        cryIfKeySource->CryptoKeyId, CryIf_SourceElementArray, \
        &numElementSource);
      indexSourceElement = CRYIF_TOTAL_KEY_ELEMENT_NUMBER;
      indexTargetElement = CRYIF_TOTAL_KEY_ELEMENT_NUMBER;
      /* @Trace: CryIf_SUD_FUNC_038 */
      if ((E_OK == retVal) && \
        (CRYIF_MAX_KEY_ELEMENT_NUMBER >= numElementSource))
      {
        /* Get key element id of crypto driver */
        retVal = CryIf_KeyElementIdsGetPtr[cryIfKeyTarget->IndexFunc](\
          cryIfKeyTarget->CryptoKeyId, CryIf_TargetElementArray, \
          &numElementTarget);
        if ((E_OK == retVal) && \
          (CRYIF_MAX_KEY_ELEMENT_NUMBER >= numElementTarget))
        {
          /* Get index of key element id structure from crypto driver */
          indexSourceElement = CryIf_GetIndexKeyElement(indexArrKey,\
            keyElementId, numElementSource);
          indexTargetElement = CryIf_GetIndexKeyElement(indexArrTargetKey,\
            targetKeyElementId, numElementTarget);
        }
      }
      /* @Trace: CryIf_SUD_FUNC_039 */
      if ((CRYIF_TOTAL_KEY_ELEMENT_NUMBER <= indexSourceElement) || \
        (CRYIF_TOTAL_KEY_ELEMENT_NUMBER <= indexTargetElement))
      {
        /* Return E_NOT_OK */
        retVal = E_NOT_OK;
      }
      else
      {
        /* Set keyLength value from key element structure */
        keyLength = CRYIF_MAX_KEY_ELEMENT_SIZE;
        /* Call Crypto_KeyElementGet of corresponding crypto driver */
        retVal = CryIf_KeyElementGetPtr[cryIfKeySource->IndexFunc](\
          cryIfKeySource->CryptoKeyId, keyElementId, \
          CryIf_KeySourceData, &keyLength);
        /* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on key list configuration. In reality, it is variant as the IT/QT testing proves." */
        /* If called Crypto_KeyElementGet() returns OK  */
        if (E_OK == retVal)
        {
          if (CryIf_KeyElementList[indexTargetElement].MaxSize < keyLength)
          {
            /* @Trace: CryIf_SUD_FUNC_040 */
            /* If development error detection is enabled */
            #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
              /* Report error to Det if the key element size doesn't match */
              (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
                CRYIF_KEYELEMENTCOPY_SID, CRYIF_E_KEY_SIZE_MISMATCH);
            #endif
            retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
          }
          else if (cryIfKeySource->IndexFunc == cryIfKeyTarget->IndexFunc)
          {
            /* @Trace: CryIf_SUD_FUNC_041 */
            /* The parameter keys are located in a Crypto Driver */
            /* Call Crypto_KeyElementCopy() of corresponding crypto driver */
            retVal = CryIf_KeyElementCopyPtr[cryIfKeySource->IndexFunc](\
              cryIfKeySource->CryptoKeyId, keyElementId,\
              cryIfKeyTarget->CryptoKeyId, targetKeyElementId);
          }
          else
          {
            /* @Trace: CryIf_SUD_FUNC_042 */
            /* The parameter keys are located in different Crypto Drivers */
            /* Call Crypto_KeyElementSet of corresponding crypto driver */
            retVal = CryIf_KeyElementSetPtr[cryIfKeyTarget->IndexFunc](\
              cryIfKeyTarget->CryptoKeyId, targetKeyElementId, \
              (const uint8*)CryIf_KeySourceData, keyLength);
          }
        } /* End of if (E_OK == retVal) */
        /* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 */
      } /* End of else */
    } /* End of else */
  } /* End of else */

  return retVal;
} /* End of CryIf_KeyElementCopy */

/*******************************************************************************
** Function Name        : CryIf_KeyElementCopyPartial                         **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : Copies a key element to another key element. The    **
**                        keyElementOffsets and keyElementCopyLength allows to**
**                        copy just parts of the source key element into the  **
**                        destination key element.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for the same cryIfKeyId          **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key whose   **
**                          key element shall be the source element.          **
**                        keyElementId: Holds the identifier of the key       **
**                          element which shall be the source for the copy    **
**                          operation.                                        **
**                        keyElementSourceOffset: This is the offset of the   **
**                          source key element indicating the start index of  **
**                          the copy operation.                               **
**                        keyElementTargetOffset: This is the offset of the   **
**                          target key element indicating the start index of  **
**                          the copy operation.                               **
**                        keyElementCopyLength: Specifies the number of bytes **
**                          that shall be copied                              **
**                        targetCryIfKeyId: Holds the identifier of the key   **
**                          whose key element shall be the destination element**
**                        targetKeyElementId: Holds the identifier of the key **
**                          element which shall be the destination for the    **
**                          copy operation.                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_NOT_AVAILABLE:  Request failed, the  **
**                            requested key element is not available          **
**                          CRYPTO_E_KEY_READ_FAIL: Request failed,           **
**                            not allowed to extract key element              **
**                          CRYPTO_E_KEY_WRITE_FAIL: Request failed,          **
**                            not allowed to write key element                **
**                          CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key **
**                            element sizes are not compatible                **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyElementList[]        **
**                                              CryIf_KeyElementCopyPartialPtr**
**                                              CryIf_KeyElementGetPtr[]      **
**                                              CryIf_KeyElementSetPtr[]      **
**                                              CryIf_SourceElementArray[]    **
**                                              CryIf_TargetElementArray[]    **
**                                              CryIf_KeySourceData[]         **
**                                              CryIf_KeyTargetData[]         **
**                                              CryIf_KeyElementIdsGetPtr[]   **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              CryIf_GetIndexKeyElement()    **
**                                              Crypto_KeyElementGet()        **
**                                              Crypto_KeyElementSet()        **
**                                              Crypto_KeyElementCopyPartial()**
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopyPartial(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  VAR(uint32, AUTOMATIC) keyElementSourceOffset,\
  VAR(uint32, AUTOMATIC) keyElementTargetOffset,\
  VAR(uint32, AUTOMATIC) keyElementCopyLength,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetKeyElementId)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for source key */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds index of key id array for target key */
  VAR(uint32, AUTOMATIC) indexArrTargetKey;
  /* Variable holds index of key element id array for keyElementId */
  VAR(uint32, AUTOMATIC) indexElement;
  /* Variable holds index of key element id array for targetKeyElementId */
  VAR(uint32, AUTOMATIC) indexTargetElement;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeySource;
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyTarget;
  /* Variable holds buffer length of key */
  VAR(uint32, AUTOMATIC) keyLength;
  /* Variable holds index for a loop */
  VAR(uint8, AUTOMATIC) indexCnt;
  /* Variable holds number of key elements */
  VAR(uint32, AUTOMATIC) numElementSource;
  VAR(uint32, AUTOMATIC) numElementTarget;

  /* Set value for variable */
  retVal = E_NOT_OK;
  numElementSource = CRYIF_MAX_KEY_ELEMENT_NUMBER;
  numElementTarget = CRYIF_MAX_KEY_ELEMENT_NUMBER;
  indexTargetElement = CRYIF_ZERO_VALUE;
  cryIfKeySource = NULL_PTR;
  cryIfKeyTarget = NULL_PTR;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_043 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYELEMENTCOPYPARTIAL_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_044 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    /* Get index of key id array from targetCryIfKeyId */
    indexArrTargetKey = CryIf_GetIndexKey(targetCryIfKeyId);
    if ((CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey) || \
      (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrTargetKey))
    {
      /* @Trace: CryIf_SUD_FUNC_045 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /*
        * Report error to Det if the cryIfKeyId,
        * targetCryIfKeyId is out of range.
        */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYELEMENTCOPYPARTIAL_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_046 */
      /* Update key information */
      cryIfKeySource = &CryIf_CryIfKeyList[indexArrKey];
      cryIfKeyTarget = &CryIf_CryIfKeyList[indexArrTargetKey];
      /* Get key element id of crypto driver */
      retVal = CryIf_KeyElementIdsGetPtr[cryIfKeySource->IndexFunc](\
        cryIfKeySource->CryptoKeyId, CryIf_SourceElementArray, \
        &numElementSource);
      /* @Trace: CryIf_SUD_FUNC_047 */
      if ((E_OK == retVal) && \
        (CRYIF_MAX_KEY_ELEMENT_NUMBER >= numElementSource))
      {
        retVal = CryIf_KeyElementIdsGetPtr[cryIfKeyTarget->IndexFunc](\
          cryIfKeyTarget->CryptoKeyId, CryIf_TargetElementArray, \
          &numElementTarget);
        if ((E_OK == retVal) && \
        (CRYIF_MAX_KEY_ELEMENT_NUMBER >= numElementTarget))
        {
          /* Get index of key element structure array from cryIfKeyId */
          indexElement = CryIf_GetIndexKeyElement(indexArrKey, \
            keyElementId, numElementSource);
          /* Get index of key element structure array from targetKeyElementId */
          indexTargetElement = CryIf_GetIndexKeyElement(indexArrTargetKey,\
            targetKeyElementId, numElementTarget);
          if ((CRYIF_TOTAL_KEY_ELEMENT_NUMBER <= indexElement) || \
            (CRYIF_TOTAL_KEY_ELEMENT_NUMBER <= indexTargetElement))
          {
            /* If development error detection is enabled */
            #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
              /*
              * Report error to Det if the keyElementId,
              * targetKeyElementId is out of range.
              */
              (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
                CRYIF_KEYELEMENTCOPYPARTIAL_SID, CRYIF_E_PARAM_HANDLE);
            #endif
            retVal = E_NOT_OK;
          }
        } /* End of if (E_OK == retVal) */
        else
        {
          retVal = E_NOT_OK;
        }
      } /* End of if (E_OK == retVal) */
      else
      {
        retVal = E_NOT_OK;
      }
    } /* End of else */
  } /* End of else */
  if (E_OK == retVal)
  {
    /* @Trace: CryIf_SUD_FUNC_048 */
    /* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on key list configuration. In reality, it is variant as the IT/QT testing proves." */
    if (cryIfKeySource->IndexFunc == cryIfKeyTarget->IndexFunc)
    {
      /* The parameter keys are located in a Crypto Driver */
      /* Call Crypto_KeyElementCopyPartial() of corresponding crypto driver */
      retVal = CryIf_KeyElementCopyPartialPtr[cryIfKeySource->IndexFunc](\
        cryIfKeySource->CryptoKeyId, keyElementId,\
        keyElementSourceOffset, keyElementTargetOffset, keyElementCopyLength,\
        cryIfKeyTarget->CryptoKeyId, targetKeyElementId);
    }
    else
    {
      /*
      * The parameter keys are located in different Crypto Drivers:
      * Get element of source key.
      * Set keyLength from key element structure
      */
      keyLength = CRYIF_MAX_KEY_ELEMENT_SIZE;
      /* Call Crypto_KeyElementGet of corresponding crypto driver */
      retVal = CryIf_KeyElementGetPtr[cryIfKeySource->IndexFunc](\
        cryIfKeySource->CryptoKeyId, keyElementId, \
        CryIf_KeySourceData, &keyLength);
      /* Call Crypto_KeyElementGet successfully */
      if (E_OK == retVal)
      {
        /* @Trace: CryIf_SUD_FUNC_049 */
        if (((keyElementSourceOffset + keyElementCopyLength) > keyLength) || \
          ((keyElementTargetOffset + keyElementCopyLength) > \
          CryIf_KeyElementList[indexTargetElement].MaxSize))
        {
          retVal = E_NOT_OK;
        }
        else
        {
          /*
          * Get element of target key
          * Set keyLength from key element structure
          */
          keyLength = CRYIF_MAX_KEY_ELEMENT_SIZE;
          /* Call Crypto_KeyElementGet of corresponding crypto driver */
          retVal = CryIf_KeyElementGetPtr[cryIfKeyTarget->IndexFunc](\
            cryIfKeyTarget->CryptoKeyId, targetKeyElementId, \
            CryIf_KeyTargetData, &keyLength);
          /* Call Crypto_KeyElementGet successfully */
          if (E_OK == retVal)
          {
            for (indexCnt = CRYIF_ZERO_VALUE; \
              indexCnt < keyElementCopyLength; indexCnt++)
            {
              /* Copy partially element from source key to target key */
              CryIf_KeyTargetData[keyElementTargetOffset + indexCnt] = \
              CryIf_KeySourceData[keyElementSourceOffset + indexCnt];
            }
            if (keyLength >= (keyElementTargetOffset + keyElementCopyLength))
            {
              /* No change */
            }
            else
            {
              /* Update length of data */
              keyLength = keyElementTargetOffset + keyElementCopyLength;
            }
            /*
            * Set element buffer keyTargetPtr to corresponding crypto driver
            * Call Crypto_KeyElementSet of corresponding crypto driver
            */
            retVal = CryIf_KeyElementSetPtr[cryIfKeyTarget->IndexFunc](\
              cryIfKeyTarget->CryptoKeyId, targetKeyElementId, \
              (const uint8*)CryIf_KeyTargetData, keyLength);
          } /* End of if (retVal == E_OK) */
        } /* End of else */
      } /* End of if (retVal == E_OK) */
    } /* End of else */
    /* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 */
  } /* End of if (retVal == E_OK) */

  return retVal;
} /* End of CryIf_KeyElementCopyPartial */

/*******************************************************************************
** Function Name        : CryIf_KeyCopy                                       **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This function shall copy all key elements from the  **
**                        source key to a target key.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for the same cryIfKeyId          **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key         **
**                          whose key element shall be the source element.    **
**                        targetCryIfKeyId: Holds the identifier of the key   **
**                          whose key element shall be the destination element**
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_NOT_AVAILABLE:  Request failed, the  **
**                            requested key element is not available          **
**                          CRYPTO_E_KEY_READ_FAIL: Request failed,           **
**                            not allowed to extract key element              **
**                          CRYPTO_E_KEY_WRITE_FAIL: Request failed,          **
**                            not allowed to write key element                **
**                          CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key **
**                            element sizes are not compatible                **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyElementList[]        **
**                                              CryIf_KeyCopyPtr[]            **
**                                              CryIf_KeyElementGetPtr[]      **
**                                              CryIf_KeyElementSetPtr[]      **
**                                              CryIf_SourceElementArray[]    **
**                                              CryIf_TargetElementArray[]    **
**                                              CryIf_KeySourceData[]         **
**                                              CryIf_KeyElementIdsGetPtr[]   **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              CryIf_GetIndexKeyElement()    **
**                                              Crypto_KeyElementGet()        **
**                                              Crypto_KeyElementSet()        **
**                                              Crypto_KeyElementIdsGet()     **
**                                              Crypto_KeyCopy()              **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyCopy(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for source key */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds index of key id array for target key */
  VAR(uint32, AUTOMATIC) indexArrTargetKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeySource;
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyTarget;
  /* Variable holds element counter for loop */
  VAR(uint8, AUTOMATIC) indexSource;
  VAR(uint8, AUTOMATIC) indexTarget;
  /* Variable holds index of key element array */
  VAR(uint32, AUTOMATIC) indexElementTarget;
  /* Variable holds max value of number key element in a source key */
  VAR(uint32, AUTOMATIC) maxKeyElement;
  /* Variable holds max value of number key element in a target key */
  VAR(uint32, AUTOMATIC) maxTargetKeyElement;
  /* Variable holds the length of key element */
  VAR(uint32, AUTOMATIC) keyLength;

  /* Variable holds return value */
  retVal = E_NOT_OK;
  maxKeyElement = CRYIF_MAX_KEY_ELEMENT_NUMBER;
  maxTargetKeyElement = CRYIF_MAX_KEY_ELEMENT_NUMBER;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_052 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYCOPY_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_053 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    /* Get index of key id array from targetCryIfKeyId */
    indexArrTargetKey = CryIf_GetIndexKey(targetCryIfKeyId);
    if ((CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey) || \
      (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrTargetKey))
    {
      /* @Trace: CryIf_SUD_FUNC_054 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report to Det if the cryIfKeyId, targetCryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYCOPY_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_055 */
      /* Update key information */
      cryIfKeySource = &CryIf_CryIfKeyList[indexArrKey];
      cryIfKeyTarget = &CryIf_CryIfKeyList[indexArrTargetKey];
      /* Get key element id of crypto driver */
      retVal = CryIf_KeyElementIdsGetPtr[cryIfKeySource->IndexFunc](\
        cryIfKeySource->CryptoKeyId, CryIf_SourceElementArray, &maxKeyElement);
      /* @Trace: CryIf_SUD_FUNC_056 */
      if (E_OK == retVal)
      {
        retVal = CryIf_KeyElementIdsGetPtr[cryIfKeyTarget->IndexFunc](\
          cryIfKeyTarget->CryptoKeyId, CryIf_TargetElementArray, \
          &maxTargetKeyElement);
      }
      if (E_OK == retVal)
      {
        /* @Trace: CryIf_SUD_FUNC_057 */
        if ((CRYIF_ZERO_VALUE == maxKeyElement) || \
          (CRYIF_ZERO_VALUE == maxTargetKeyElement) || \
          (CRYIF_MAX_KEY_ELEMENT_NUMBER < maxKeyElement) || \
          (CRYIF_MAX_KEY_ELEMENT_NUMBER < maxTargetKeyElement) || \
          (maxKeyElement != maxTargetKeyElement))
        {
          retVal = E_NOT_OK;
        }
        /* @Trace: CryIf_SUD_FUNC_061 */
        /* polyspace+1 DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on input passed by other module, component or test. In reality, it is variant instead of a constant." */            
        else if (cryIfKeySource->IndexFunc == cryIfKeyTarget->IndexFunc)
        {
          /* The parameter keys are located in a Crypto Drivers */
          /* Call Crypto_KeyCopy() of corresponding crypto driver */
          retVal = CryIf_KeyCopyPtr[cryIfKeySource->IndexFunc](\
            cryIfKeySource->CryptoKeyId, cryIfKeyTarget->CryptoKeyId);
          /* @Trace: CryIf_SUD_FUNC_059 */
          /* If development error detection is enabled */
          #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
            if (CRYPTO_E_KEY_SIZE_MISMATCH == retVal)
            {
              /* Report error to Det if key element size doesn't match */
              (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
                CRYIF_KEYCOPY_SID, CRYIF_E_KEY_SIZE_MISMATCH);
            }            
          #endif
        /* polyspace+1 DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on input passed by other module, component or test. In reality, it is variant instead of a constant." */
        }
        else
        {
          /* Initialize value */
          indexSource = CRYIF_ZERO_VALUE;
          while ((indexSource < maxKeyElement) && (E_OK == retVal))
          {
            /* Set keyLength */
            keyLength = CRYIF_MAX_KEY_ELEMENT_SIZE;
            indexTarget = CRYIF_ZERO_VALUE;
            retVal = E_NOT_OK;
            while ((indexTarget < maxTargetKeyElement) && \
              (E_OK != retVal))
            {
              /* Get indexTarget of target key element */
              if (CryIf_SourceElementArray[indexSource] == \
                CryIf_TargetElementArray[indexTarget])
              {
                retVal = E_OK;
              }
              else
              {
                indexTarget++;
              }
            } /* End of while */
            /* @Trace: CryIf_SUD_FUNC_058 */
            if (E_OK == retVal)
            {
              /* Call Crypto_KeyElementGet of corresponding crypto driver */
              retVal = CryIf_KeyElementGetPtr[cryIfKeySource->IndexFunc](\
                cryIfKeySource->CryptoKeyId, CryIf_SourceElementArray[indexSource], \
                CryIf_KeySourceData, &keyLength);
              /* Get index element */
              indexElementTarget = CryIf_GetIndexKeyElement(indexArrTargetKey, \
                CryIf_TargetElementArray[indexTarget], maxTargetKeyElement);
              if (CRYIF_TOTAL_KEY_ELEMENT_NUMBER > indexElementTarget)
              {
                /* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on key list configuration. In reality, it is variant as the IT/QT testing proves." */
                if(CryIf_KeyElementList[indexElementTarget].MaxSize < keyLength)
                {
                  /* @Trace: CryIf_SUD_FUNC_059 */
                  /* If development error detection is enabled */
                  #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
                    /* Report error to Det if key element size doesn't match */
                    (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
                      CRYIF_KEYCOPY_SID, CRYIF_E_KEY_SIZE_MISMATCH);
                  #endif
                  retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
                }
                else
                {
                  /* @Trace: CryIf_SUD_FUNC_060 */
                  /* Set all information of target key element to driver */
                  /* Call Crypto_KeyElementSet of corresponding crypto driver */
                  retVal = CryIf_KeyElementSetPtr[cryIfKeyTarget->IndexFunc](\
                    cryIfKeyTarget->CryptoKeyId, \
                    CryIf_TargetElementArray[indexTarget], \
                    (const uint8*)CryIf_KeySourceData, keyLength);
                }
                /* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 */
              }
            } /* End if (E_OK == retVal) */
            /* Increase counter */
            indexSource++;
          } /* End of while */
        } /* End of else */
      } /* End of if (E_OK == retVal) */
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_KeyCopy() */

/*******************************************************************************
** Function Name        : CryIf_RandomSeed                                    **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This function shall dispatch the random seed        **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Sync or Async, depends on the configuration         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key for     **
**                          which a new seed shall be generated.              **
**                        seedPtr: Holds a pointer to the memory location     **
**                          which contains the data to feed the seed.         **
**                        seedLength: Contains the length of the seed in bytes**
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_RandomSeedPtr[]         **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_RandomSeed()           **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_RandomSeed(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  P2CONST(uint8, AUTOMATIC, CRYIF_APPL_CONST) seedPtr,\
  VAR(uint32, AUTOMATIC) seedLength)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_062 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_RANDOMSEED_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_063 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      /* @Trace: CryIf_SUD_FUNC_064 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the cryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_RANDOMSEED_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if (NULL_PTR == seedPtr)
    {
      /* @Trace: CryIf_SUD_FUNC_065 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the seedPtr is a null pointer. */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_RANDOMSEED_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else if (CRYIF_ZERO_VALUE == seedLength)
    {
      /* @Trace: CryIf_SUD_FUNC_066 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the seedLength is zero */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_RANDOMSEED_SID, CRYIF_E_PARAM_VALUE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_067 */
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      /* Call Crypto_RandomSeed() of corresponding crypto driver */
      retVal = CryIf_RandomSeedPtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId, seedPtr, seedLength);
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_RandomSeed */

/*******************************************************************************
** Function Name        : CryIf_KeyGenerate                                   **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This function shall dispatch the key generate       **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Sync or Async, depends on the configuration         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key which is**
**                          to be updated with the generated value.           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyGeneratePtr[]        **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              Crypto_KeyGenerate()          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyGenerate(\
  VAR(uint32, AUTOMATIC) cryIfKeyId)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  cryIfKeyPtr = NULL_PTR;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_068 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYGENERATE_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_069 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER;
    while ((CRYIF_ZERO_VALUE < indexArrKey) && (E_OK != retVal))
    {
      indexArrKey--;
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      if (cryIfKeyPtr->CryIfKeyId == cryIfKeyId)
      {
        retVal = E_OK;
      }
    }
    if (E_OK != retVal)
    {
      /* @Trace: CryIf_SUD_FUNC_070 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the cryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYGENERATE_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_071 */
      /* Call Crypto_KeyGenerate() of corresponding crypto driver */
      retVal = CryIf_KeyGeneratePtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId);
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_KeyGenerate */

/*******************************************************************************
** Function Name        : CryIf_KeyDerive                                     **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This function shall dispatch the key derive         **
**                        function to the configured crypto driver object.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key which is**
**                          used for key derivation.                          **
**                        targetCryIfKeyId: Holds the identifier of the key   **
**                          which is used to store the derived key.           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyDerivePtr[]          **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_KeyDerive()            **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009 */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyDerive(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for source key */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds index of key id array for target key */
  VAR(uint32, AUTOMATIC) indexArrTargetKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeySource;
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyTarget;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_072 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYDERIVE_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_073 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    /* Get index of key id array from targetCryIfKeyId */
    indexArrTargetKey = CryIf_GetIndexKey(targetCryIfKeyId);
    if ((CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey) || \
      (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrTargetKey))
    {
      /* @Trace: CryIf_SUD_FUNC_074 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report to Det if the cryIfKeyId, targetCryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYDERIVE_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_075 */
      /* Update key information */
      cryIfKeySource = &CryIf_CryIfKeyList[indexArrKey];
      cryIfKeyTarget = &CryIf_CryIfKeyList[indexArrTargetKey];
      /* Call Crypto_KeyDerive() of corresponding crypto driver */
      retVal = CryIf_KeyDerivePtr[cryIfKeySource->IndexFunc](\
        cryIfKeySource->CryptoKeyId, cryIfKeyTarget->CryptoKeyId);
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_KeyDerive */

/*******************************************************************************
** Function Name        : CryIf_KeyExchangeCalcPubVal                         **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : This function shall dispatch the key exchange public**
**                        value calculation function to the configured crypto **
**                        driver object.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key which   **
**                          shall be used for the key exchange protocol.      **
**                                                                            **
** InOut Parameters     : publicValueLengthPtr: Holds a pointer to the memory **
**                          location in which the public value length         **
**                          information is stored. On calling this function,  **
**                          this parameter shall contain the size of the      **
**                          buffer provided by publicValuePtr. When the       **
**                          request has finished, the actual length of the    **
**                          returned value shall be stored.                   **
**                                                                            **
** Output Parameters    : publicValuePtr: Contains the pointer to the data    **
**                          where the public value shall be stored.           **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_SMALL_BUFFER: The provided buffer is too **
**                            small to store the result                       **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyExchangeCalcPubValPtr**
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_KeyExchangeCalcPubVal()**
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009*/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcPubVal(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) publicValuePtr,\
  P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) publicValueLengthPtr)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_076 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYEXCHANGECALCPUBVAL_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_077 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      /* @Trace: CryIf_SUD_FUNC_078 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the cryIfKeyId is out of range */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYEXCHANGECALCPUBVAL_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if ((NULL_PTR == publicValuePtr) || (NULL_PTR == publicValueLengthPtr))
    {
      /* @Trace: CryIf_SUD_FUNC_079 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report to Det if publicValuePtr, publicValueLengthPtr is a null */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYEXCHANGECALCPUBVAL_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else if (CRYIF_ZERO_VALUE == (*publicValueLengthPtr))
    {
      /* @Trace: CryIf_SUD_FUNC_080 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /*
        * Report error to Det if the value, which is pointed
        * by pubValueLengthPtr, is zero
        */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYEXCHANGECALCPUBVAL_SID, CRYIF_E_PARAM_VALUE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_081 */
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      /* Call Crypto_KeyExchangeCalcPubVal() of corresponding crypto driver */
      retVal = CryIf_KeyExchangeCalcPubValPtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId, publicValuePtr, publicValueLengthPtr);
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_KeyExchangeCalcPubVal */

/*******************************************************************************
** Function Name        : CryIf_KeyExchangeCalcSecret                         **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This function shall dispatch the key exchange common**
**                        shared secret calculation function to the configured**
**                        crypto driver object.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cryIfKeyId: Holds the identifier of the key which   **
**                          shall be used for the key exchange protocol.      **
**                        partnerPublicValuePtr: Holds the pointer to the     **
**                          memory location which contains the partner's      **
**                          public value.                                     **
**                        partnerPublicValueLength: Contains the length of    **
**                          the partner's public value in bytes.              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType:                                     **
**                          E_OK: Request successful                          **
**                          E_NOT_OK: Request failed                          **
**                          CRYPTO_E_BUSY: Request failed,                    **
**                            Crypro Driver Object is busy                    **
**                          CRYPTO_E_SMALL_BUFFER: The provided buffer is too **
**                            small to store the result                       **
**                          CRYPTO_E_KEY_EMPTY: Request failed because of     **
**                            uninitialized source key element                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                              CryIf_CryIfKeyList[]          **
**                                              CryIf_KeyExchangeCalcSecretPtr**
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CryIf_GetIndexKey()           **
**                                              Crypto_KeyExchangeCalcSecret()**
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_CryptoStack_00009*/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcSecret(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  P2CONST(uint8, AUTOMATIC, CRYIF_APPL_CONST) partnerPublicValuePtr,\
  VAR(uint32, AUTOMATIC) partnerPublicValueLength)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for cryIfKeyId */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds information of cryIfKey */
  P2CONST(CryIf_KeyType, AUTOMATIC, CRYIF_APPL_CONST) cryIfKeyPtr;

  /* Set value for variable */
  retVal = E_NOT_OK;
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_082 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_KEYEXCHANGECALCSECRET_SID, CRYIF_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_083 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(cryIfKeyId);
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      /* @Trace: CryIf_SUD_FUNC_084 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the cryIfKeyId is out of range */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYEXCHANGECALCSECRET_SID, CRYIF_E_PARAM_HANDLE);
      #endif
    }
    else if (NULL_PTR == partnerPublicValuePtr)
    {
      /* @Trace: CryIf_SUD_FUNC_085 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if the partnerPublicValuePtr is a null pointer */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYEXCHANGECALCSECRET_SID, CRYIF_E_PARAM_POINTER);
      #endif
    }
    else if (CRYIF_ZERO_VALUE == partnerPublicValueLength)
    {
      /* @Trace: CryIf_SUD_FUNC_086 */
      /* If development error detection is enabled */
      #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
        /* Report error to Det if partnerPubValueLength is zero */
        (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
          CRYIF_KEYEXCHANGECALCSECRET_SID, CRYIF_E_PARAM_VALUE);
      #endif
    }
    else
    {
      /* @Trace: CryIf_SUD_FUNC_087 */
      cryIfKeyPtr = &CryIf_CryIfKeyList[indexArrKey];
      /* Call Crypto_KeyExchangeCalcSecret() of corresponding crypto driver */
      retVal = CryIf_KeyExchangeCalcSecretPtr[cryIfKeyPtr->IndexFunc](\
        cryIfKeyPtr->CryptoKeyId, partnerPublicValuePtr, \
        partnerPublicValueLength);
    }
  } /* End of else */

  return retVal;
} /* End of CryIf_KeyExchangeCalcSecret */

/*******************************************************************************
** Function Name        : CryIf_CallbackNotification                          **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : Notifies the CRYIF about the completion of the      **
**                        request with the result of the cryptographic        **
**                        operation.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : job: Points to the completed job's information      **
**                          structure. It contains a callbackID to identify   **
**                          which job is finished.                            **
**                        result: Contains the result of the cryptographic    **
**                          operation.                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ModuleInitialized       **
**                                                                            **
**                        Function(s) invoked : Det_ReportError()             **
**                                              Csm_CallbackNotification()    **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00034 SRS_BSW_00323 SRS_BSW_00359 SRS_BSW_00360 */
FUNC(void, CRYIF_CODE) CryIf_CallbackNotification(\
  P2CONST(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job,\
  VAR(Csm_ResultType, AUTOMATIC) result)
{
  if (FALSE == CryIf_ModuleInitialized)
  {
    /* @Trace: CryIf_SUD_FUNC_088 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the module is not yet initialized */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_CALLBACKNOTIFICATION_SID, CRYIF_E_UNINIT);
    #endif
  }
  else if (NULL_PTR == job)
  {
    /* @Trace: CryIf_SUD_FUNC_089 */
    /* If development error detection is enabled */
    #if (STD_ON == CRYIF_DEV_ERROR_DETECT)
      /* Report error to Det if the parameter job is a null pointer */
      (void)Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID,\
        CRYIF_CALLBACKNOTIFICATION_SID, CRYIF_E_PARAM_POINTER);
    #endif
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_090 */
    if ((NULL_PTR != job->jobPrimitiveInfo) && \
      (CRYPTO_PROCESSING_ASYNC == job->jobPrimitiveInfo->processingType))
    {
      /* Call back to Csm call back notification */
      Csm_CallbackNotification(job, result);
    }
  }
} /* End of CryIf_CallbackNotification */

#define CRYIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
