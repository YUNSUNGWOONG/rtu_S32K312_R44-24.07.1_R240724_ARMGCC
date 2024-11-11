/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   : Provide definition of Fls's function                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                        Description              **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Cfg.h"
#include "Mem_76_Pfls_Types.h"
#include "Mem_76_Pfls_Globals.h"
#include "Mem_76_Pfls_IntFunc.h"
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#include "SchM_Mem_76_Pfls.h"
#endif
#if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Stub */

/*******************************************************************************
**                      Function Declare                                      **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint8, MEM_76_PFLS_CODE) Mem_76_Pfls_CheckValidAddress( \
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) address, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length, \
  P2CONST(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) srcPtr, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) destPtr, \
  VAR(uint8, AUTOMATIC) servId);

static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetFlashAlignment(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_ToolBox_Active_Service(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);
#endif
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetSectorSize(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetAltAddress(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Cancel(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

static FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) \
  Mem_76_Pfls_JobReadProcess(Mem_76_Pfls_InstanceIdType InstanceId);

static FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) \
  Mem_76_Pfls_JobWriteProcess(Mem_76_Pfls_InstanceIdType InstanceId);

static FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) \
  Mem_76_Pfls_JobEraseProcess(Mem_76_Pfls_InstanceIdType InstanceId);

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_Init                                    **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Initialization function - initializes all variables **
**                        and sets the module state to initialized            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to the configuration             **
**                          data structure - since Mem driver is a precompile **
**                          module this parameter is typically not used       **
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14037 SRS_Mem_BSW_00050 SRS_Mem_MemHwAb_14047 */
/* @Trace: SWS_BSW_00050 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_Init(\
  P2CONST(Mem_76_Pfls_ConfigType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) ConfigPtr)
{
  VAR(uint16, AUTOMATIC) indexOfInstance;
  VAR(uint32, AUTOMATIC) indexOfSector;
  #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
  VAR(uint8, AUTOMATIC) toolBoxActiveServiceCheckValue;
  VAR(uint32, AUTOMATIC) toolBoxActiveServiceCheckSize;
  #endif
  P2VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
    instanceInfoPtr;

  if (NULL_PTR == ConfigPtr)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_001 */
    Mem_76_Pfls_InitDone  = MEM_76_PFLS_TRUE;

    #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
    Mem_76_Pfls_ToolBox_Active    = MEM_76_PFLS_FALSE;
    #endif
    /* @Trace: Mem_76_Pfls_SUD_MACRO_007 */
    for (indexOfInstance = MEM_76_PFLS_ZERO; \
      indexOfInstance < MEM_76_PFLS_NUMBER_OF_INSTANCES; indexOfInstance++)
    {
      instanceInfoPtr = &Mem_76_Pfls_InstanceInfo[indexOfInstance];
      /* Current job */
      instanceInfoPtr->CurrentJob = MEM_76_PFLS_JOB_IDLE;
      /* Job result */
      instanceInfoPtr->JobResult = MEM_JOB_OK;
      /* Number of sectors */
      instanceInfoPtr->NumberOfSectorRemain = MEM_76_PFLS_ZERO;
      /* Alt Address Access */
      instanceInfoPtr->AltAddressAccess = FALSE;
      /* Cancel Job */
      instanceInfoPtr->CancelJob = FALSE;
      /* Sector Index */
      instanceInfoPtr->SectorIndex = MEM_76_PFLS_ZERO;
      /* @Trace: Mem_76_Pfls_SUD_MACRO_006 */
      for (indexOfSector = MEM_76_PFLS_ZERO; \
        indexOfSector < MEM_76_PFLS_MAX_NUMBER_OF_SECTOR_PER_INSTANCE; \
        indexOfSector++)
      {
        /* Source address */
        instanceInfoPtr->SectorInfo[indexOfSector].SrcAddress = \
          MEM_76_PFLS_ZERO;
        /* Destination address */
        instanceInfoPtr->SectorInfo[indexOfSector].DestAddress = \
          MEM_76_PFLS_ZERO;
        /* Length */
        instanceInfoPtr->SectorInfo[indexOfSector].Length = \
          MEM_76_PFLS_ZERO;
        /* Normal size */
        instanceInfoPtr->SectorInfo[indexOfSector].NormalSize = \
          MEM_76_PFLS_ZERO;
        /* Burst size */
        instanceInfoPtr->SectorInfo[indexOfSector].BurstSize = \
          MEM_76_PFLS_ZERO;
        /* Source Pointer */
        instanceInfoPtr->SectorInfo[indexOfSector].SrcPtr = NULL_PTR;
        /* Destination pointer */
        instanceInfoPtr->SectorInfo[indexOfSector].DestPtr = NULL_PTR;
      }
    }
    #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
    (void)Mem_76_Pfls_HwSpecificService(MEM_76_PFLS_ZERO, MEM_76_PFLS_TOOLBOX_ACTIVE_SERVICE, \
                                        &toolBoxActiveServiceCheckValue, &toolBoxActiveServiceCheckSize);
    #endif
    /* Initial Flash */
    Mem_76_Pfls_InternalInitialize();
  }
  else
  {
    /* Post-build reserved */
  }

}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_DeInit                                  **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : De-initialize module. If there is still an access   **
**                        job pending, it is immediately terminated (using    **
**                        hardware cancel operation) and the Mem driver       **
**                        module state is set to unitialized. Therefore, Mem  **
**                        must be re-initialized before it will accept any    **
**                        new job requests after this service is processed.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14037 SRS_Mem_MemHwAb_14031 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_DeInit(void)
{
  VAR(uint16, AUTOMATIC) indexOfInstance;
  VAR(uint32, AUTOMATIC) indexOfSector;
  P2VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
    instanceInfoPtr;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_002 */
  Mem_76_Pfls_InitDone  = MEM_76_PFLS_FALSE;

  #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
  Mem_76_Pfls_ToolBox_Active    = MEM_76_PFLS_FALSE;
  #endif
  /* loop for all instances */
  for (indexOfInstance = MEM_76_PFLS_ZERO; \
      indexOfInstance < MEM_76_PFLS_NUMBER_OF_INSTANCES; indexOfInstance++)
  {
    instanceInfoPtr = &Mem_76_Pfls_InstanceInfo[indexOfInstance];
    /* reset all variables */
    /* Current job */
    instanceInfoPtr->CurrentJob = MEM_76_PFLS_JOB_IDLE;
    /* Job result */
    instanceInfoPtr->JobResult  = MEM_JOB_OK;
    /* Number of sectors */
    instanceInfoPtr->NumberOfSectorRemain  = MEM_76_PFLS_ZERO;
    /* Alt Address Access */
    instanceInfoPtr->AltAddressAccess = FALSE;
    /* Cancel Job */
    instanceInfoPtr->CancelJob = FALSE;
    /* Sector Index */
    instanceInfoPtr->SectorIndex = MEM_76_PFLS_ZERO;

    /* loop for all sectors each instance */
    for (indexOfSector = MEM_76_PFLS_ZERO; \
      indexOfSector < MEM_76_PFLS_MAX_NUMBER_OF_SECTOR_PER_INSTANCE; \
      indexOfSector++)
    {
      /* Source address */
      instanceInfoPtr->SectorInfo[indexOfSector].SrcAddress = \
        MEM_76_PFLS_ZERO;
      /* Destination address */
      instanceInfoPtr->SectorInfo[indexOfSector].DestAddress = \
        MEM_76_PFLS_ZERO;
      /* Length */
      instanceInfoPtr->SectorInfo[indexOfSector].Length = \
        MEM_76_PFLS_ZERO;
      /* Normal size */
      instanceInfoPtr->SectorInfo[indexOfSector].NormalSize = \
        MEM_76_PFLS_ZERO;
      /* Burst size */
      instanceInfoPtr->SectorInfo[indexOfSector].BurstSize = \
        MEM_76_PFLS_ZERO;
      /* Source Pointer */
      instanceInfoPtr->SectorInfo[indexOfSector].SrcPtr = NULL_PTR;
      /* Destination pointer */
      instanceInfoPtr->SectorInfo[indexOfSector].DestPtr = NULL_PTR;
    }
  }
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_GetVersionInfo                          **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Service to return the version information of the    **
**                        Mem module                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : VersioninfoPtr: Pointer to standard version         **
**                          information structure.                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_BSW_00003 SRS_Mem_BSW_00323 SRS_Mem_BSW_00004 SRS_Mem_BSW_00101 SRS_Mem_BSW_00102 SRS_Mem_BSW_00103 SRS_Mem_BSW_00171 SRS_Mem_BSW_00452 */
/* @Trace: Mem_76_Pfls_SUD_DATATYPE_008  */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_GetVersionInfo(\
  P2VAR(Std_VersionInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) versionInfoPtr)
{
  if (NULL_PTR == versionInfoPtr)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_003 Mem_76_Pfls_SUD_MACRO_003 */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_GETVERSIONINFO_SID, MEM_76_PFLS_E_PARAM_POINTER);
    #endif /* MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_004 */
    /* Copy the vendor Id */
    versionInfoPtr->vendorID          = MEM_76_PFLS_VENDOR_ID;
    /* Copy the module Id */
    versionInfoPtr->moduleID          = MEM_76_PFLS_MODULE_ID;
    /* Copy Software Major Version */
    versionInfoPtr->sw_major_version  = MEM_76_PFLS_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versionInfoPtr->sw_minor_version  = MEM_76_PFLS_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versionInfoPtr->sw_patch_version  = MEM_76_PFLS_SW_PATCH_VERSION;
  }
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_GetJobResult                            **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Service to return results of the most recent job.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Mem_76_Pfls_JobResultType: Most recent job result.  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14040 SRS_Mem_BSW_00452 SRS_Mem_MemHwAb_14050 */
FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetJobResult(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId)
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC) jobResult;

  /* wrong instanceId */
  if (MEM_76_PFLS_NUMBER_OF_INSTANCES <= instanceId)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_005 */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_GETJOBRESULT_SID, MEM_76_PFLS_E_PARAM_INSTANCE_ID);
    #endif
    jobResult = MEM_JOB_FAILED;
  }
  else if (MEM_JOB_OK == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_006 */
    jobResult = MEM_JOB_OK;
  }
  else if (MEM_JOB_PENDING == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_007 */
    jobResult = MEM_JOB_PENDING;
  }
  else if (MEM_INCONSISTENT == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_008 */
    jobResult = MEM_INCONSISTENT;
  }
  else if (MEM_ECC_UNCORRECTED == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_009 */
    jobResult = MEM_ECC_UNCORRECTED;
  }
  else if (MEM_ECC_CORRECTED == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_010 */
    jobResult = MEM_ECC_CORRECTED;
  }
  else
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_011 */
    jobResult = MEM_JOB_FAILED;
  }

  return (jobResult);
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_Suspend                                 **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : Suspend active memory operation using hardware      **
**                        mechanism.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
/* @Trace: SRS_Mem_MemHwAb_14034 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Suspend(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  /* @Trace: Mem_76_Pfls_SUD_FUNC_064 */
  /* Not support yet */

  return (E_MEM_SERVICE_NOT_AVAIL);
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_Resume                                  **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Resume suspended memory operation using hardware    **
**                        mechanism.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
/* @Trace: SRS_Mem_MemHwAb_14034 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Resume(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  /* @Trace: Mem_76_Pfls_SUD_FUNC_065 */
  /* Not support yet */

  return (E_MEM_SERVICE_NOT_AVAIL);
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_PropagateError                          **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : This service can be used to report an access error  **
**                        in case the Mem driver cannot provide the access    **
**                        error information - typically for ECC faults. It    **
**                        is called by the system ECC handler to propagate    **
**                        an ECC error to the memory upper layers.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14053 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_PropagateError(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId)
{
  /* Not support yet */
  /* @Trace: Mem_76_Pfls_SUD_FUNC_066 */
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_Read                                    **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Triggers a read job to copy the from the source     **
**                        address into the referenced destination data        **
**                        buffer. The result of this service can be           **
**                        etrieved using the Mem_GetJobResult API. If         **
**                        the read operation was successful, the result of    **
**                        the job is MEM_JOB_OK. If the read operation        **
**                        failed, the result of the job is either             **
**                        MEM_JOB_FAILED in case of a general error or        **
**                        MEM_ECC_CORRECTED/MEM_ECC_UNCORRECTED in case of    **
**                        a correctable/uncorrectable ECC error.              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
**                        sourceAddress: Physical address to read data from   **
**                        length: Read length in bytes.                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : destinationDataPtr: Destination memory pointer to   **
**                          store the read data.                              **
**                                                                            **
** Return parameter     : Std_ReturnType:                                     **
**                        - E_OK: The requested job has been accepted by      **
**                          the module.                                       **
**                        - E_NOT_OK: The requested job has not been accepted **
**                          by the module.                                    **
**                        - E_MEM_SERVICE_NOT_AVAIL: The service function is  **
**                          not implemented.                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_BSW_00406 SRS_Mem_BSW_00323 SRS_Mem_BSW_00004 SRS_Mem_BSW_00167 */
/* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Read(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) sourceAddress, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) destinationDataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  VAR(uint8, AUTOMATIC)          errorCode;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_012 */
  retVal = E_NOT_OK;
  if (MEM_76_PFLS_FALSE == Mem_76_Pfls_InitDone)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_013 */
    /* API service called without module initialization */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_UNINIT);
    #endif
  }
  #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
  else if (MEM_76_PFLS_FALSE == Mem_76_Pfls_ToolBox_Active)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_014 */
    /* Tool Box is not activated */
  }
  #endif
  else if (MEM_76_PFLS_NUMBER_OF_INSTANCES <= instanceId)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_015 */
    /* Wrong instance ID */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_READ_SID, MEM_76_PFLS_E_PARAM_INSTANCE_ID);
    #endif
  }
  else if (NULL_PTR == destinationDataPtr)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_016 */
    /* Wrong destination */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_READ_SID, MEM_76_PFLS_E_PARAM_POINTER);
    #endif
  }
  else if (MEM_76_PFLS_ZERO == length)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_017 */
    /* Wrong length */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_READ_SID, MEM_76_PFLS_E_PARAM_LENGTH);
    #endif
  }
  else if (MEM_JOB_PENDING == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_018 */
    /* Out of range */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_READ_SID, MEM_76_PFLS_E_JOB_PENDING);
    #endif
  }
  else
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_019 */
    /* Check valid of address and length */
    errorCode = Mem_76_Pfls_CheckValidAddress(instanceId, sourceAddress, \
      length, NULL_PTR, destinationDataPtr, MEM_76_PFLS_READ_SID);
    if (MEM_76_PFLS_E_PARAM_ADDRESS == errorCode)
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_020 */
      /* Wrong source address */
      #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
          MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_PARAM_ADDRESS);
      #endif
    }
    else if (MEM_76_PFLS_E_PARAM_LENGTH == errorCode)
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_021 */
      /* Out of range */
      #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
          MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_PARAM_LENGTH);
      #endif
    }
    else
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_022 */
      /* Set Job result */
      Mem_76_Pfls_InstanceInfo[instanceId].JobResult  = MEM_JOB_PENDING;
      /* Set current job */
      Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob = MEM_76_PFLS_JOB_READ;
      /* return OK */
      retVal                                          = E_OK;
    }
  }

  return (retVal);
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_Write                                   **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Triggers a write job to store the passed data to the**
**                        provided address area with given address and length.**
**                        The result of this service can be retrieved using   **
**                        the Mem_GetJobResult API. If the write operation    **
**                        was successful, the job result is MEM_JOB_OK. If    **
**                        there was an issue writing the data, the result is  **
**                        MEM_FAILED.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
**                        targetAddress: Physical write address               **
**                          (aligned to page size).                           **
**                        sourceDataPtr: Source data pointer                  **
**                          (aligned to page size).                           **
**                        length: Write length in bytes (aligned to page size)**
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType:                                     **
**                        - E_OK: The requested job has been accepted by the  **
**                            module.                                         **
**                        - E_NOT_OK: The requested job has not been accepted **
**                            by the module.                                  **
**                        - E_MEM_SERVICE_NOT_AVAIL: The service function is  **
**                            not implemented.                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_BSW_00406 SRS_Mem_BSW_00323 SRS_Mem_BSW_00004 SRS_Mem_BSW_00167 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Write(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) targetAddress, \
  P2CONST(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) sourceDataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC)  retVal;
  VAR(uint8, AUTOMATIC)           errorCode;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_023 */
  retVal = E_NOT_OK;
  if (MEM_76_PFLS_FALSE == Mem_76_Pfls_InitDone)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_024 */
    /* API service called without module initialization */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_UNINIT);
    #endif
  }
  #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
  else if (MEM_76_PFLS_FALSE == Mem_76_Pfls_ToolBox_Active)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_025 */
    /* Tool Box is not activated */
  }
  #endif
  else if (MEM_76_PFLS_NUMBER_OF_INSTANCES <= instanceId)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_026 */
    /* Wrong instance ID */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_WRITE_SID, MEM_76_PFLS_E_PARAM_INSTANCE_ID);
    #endif
  }
  else if (NULL_PTR == sourceDataPtr)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_027 */
    /* Wrong destination */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_WRITE_SID, MEM_76_PFLS_E_PARAM_POINTER);
    #endif
  }
  else if (MEM_76_PFLS_ZERO == length)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_028 */
    /* Wrong length */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_WRITE_SID, MEM_76_PFLS_E_PARAM_LENGTH);
    #endif
  }
  else if (MEM_JOB_PENDING == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_029 */
    /* Out of range */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_WRITE_SID, MEM_76_PFLS_E_JOB_PENDING);
    #endif
  }
  else
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_030 */
    /* Check valid of address and length */
    errorCode = Mem_76_Pfls_CheckValidAddress(instanceId, targetAddress, \
      length, sourceDataPtr, NULL_PTR, MEM_76_PFLS_WRITE_SID);
    if (MEM_76_PFLS_E_PARAM_ADDRESS == errorCode)
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_031 */
      /* Wrong source address */
      #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
          MEM_76_PFLS_WRITE_SID, MEM_76_PFLS_E_PARAM_ADDRESS);
      #endif
    }
    else if (MEM_76_PFLS_E_PARAM_LENGTH == errorCode)
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_032 */
      /* Out of range */
      #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
          MEM_76_PFLS_WRITE_SID, MEM_76_PFLS_E_PARAM_LENGTH);
      #endif
    }
    else
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_033 */
      /* Set Job result */
      Mem_76_Pfls_InstanceInfo[instanceId].JobResult  = MEM_JOB_PENDING;
      /* Set current job */
      Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob = MEM_76_PFLS_JOB_WRITE;
      /* return OK */
      retVal                                          = E_OK;
    }
  }

  return (retVal);
}
/*******************************************************************************
** Function Name        : Mem_76_Pfls_Erase                                   **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Triggers an erase job of the given sector/sector    **
**                        batch defined by targetAddress and length. The      **
**                        result of this service can be retrieved using the   **
**                        Mem_GetJobResult API. If the erase operation was    **
**                        successful, the result of the job is MEM_JOB_OK. If **
**                        the erase operation failed, e.g. due to a hardware  **
**                        issue, the result of the job is MEM_JOB_FAILED.     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
**                        targetAddress: Physical erase address               **
**                          (aligned to sector size)                          **
**                        length: Erase length in bytes                       **
**                          (aligned to sector size)                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType:                                     **
**                        - E_OK: The requested job has been accepted by the  **
**                            module.                                         **
**                        - E_NOT_OK: The requested job has not been accepted **
**                            by the module.                                  **
**                        - E_MEM_SERVICE_NOT_AVAIL: The service function is  **
**                            not implemented.                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_BSW_00406 SRS_Mem_BSW_00323 SRS_Mem_BSW_00004 SRS_Mem_BSW_00167*/
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Erase(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) targetAddress, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC)  retVal;
  VAR(uint8, AUTOMATIC)           errorCode;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_034 */
  retVal = E_NOT_OK;

  if (MEM_76_PFLS_FALSE == Mem_76_Pfls_InitDone)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_035 */
    /* API service called without module initialization */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_UNINIT);
    #endif
  }
  #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
  else if (MEM_76_PFLS_FALSE == Mem_76_Pfls_ToolBox_Active)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_036 */
    /* Tool Box is not activated */
  }
#endif
  else if (MEM_76_PFLS_NUMBER_OF_INSTANCES <= instanceId)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_037 */
    /* Wrong instance ID */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_PARAM_INSTANCE_ID);
    #endif
  }
  else if (MEM_76_PFLS_ZERO == length)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_038 */
    /* Wrong length */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_PARAM_LENGTH);
    #endif
  }
  else if (MEM_JOB_PENDING == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_039 */
    /* Out of range */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_JOB_PENDING);
    #endif
  }
  else
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_040 */
    /* Check valid of address and length */
    errorCode = Mem_76_Pfls_CheckValidAddress(instanceId, targetAddress, \
      length, NULL_PTR, NULL_PTR, MEM_76_PFLS_ERASE_SID);
    if (MEM_76_PFLS_E_PARAM_ADDRESS == errorCode)
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_041 */
      /* Wrong source address */
      #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
          MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_PARAM_ADDRESS);
      #endif
    }
    else if (MEM_76_PFLS_E_PARAM_LENGTH == errorCode)
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_042 */
      /* Out of range */
      #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
          MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_PARAM_LENGTH);
      #endif
    }
    else
    {
      /* @Trace: Mem_76_Pfls_SUD_FUNC_043 */
      /* Set Job result */
      Mem_76_Pfls_InstanceInfo[instanceId].JobResult  = MEM_JOB_PENDING;
      /* Set current job */
      Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob = MEM_76_PFLS_JOB_ERASE;
      /* return OK */
      retVal                                          = E_OK;
    }
  }

  return (retVal);
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_BlankCheck                              **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : Triggers a job to check the erased state of the page**
**                        which is referenced by targetAddress. The result    **
**                        of this service can be retrieved using the          **
**                        Mem_GetJobResult API. If the checked page is blank, **
**                        the result of the job is MEM_JOB_OK. Otherwise,     **
**                        if the page is not blank, the result is             **
**                        MEM_INCONSISTENT.                                   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
**                        targetAddress: Physical blank check address.        **
**                        length: Blank check length.                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType:                                     **
**                        - E_OK: The requested job has been accepted by the  **
**                          module.                                           **
**                        - E_NOT_OK: The requested job has not been accepted **
**                          by the module.                                    **
**                        - E_MEM_SERVICE_NOT_AVAIL: The service function is  **
**                          not implemented.                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 */
/* @Trace: Mem_76_Pfls_SUD_DATATYPE_008  */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_BlankCheck(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) targetAddress, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_104 */  
  /* Not support yet */
  retVal = E_MEM_SERVICE_NOT_AVAIL;

  return (retVal);
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_HwSpecificService                       **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : Triggers a hardware specific memory driver job.     **
**                        dataPtr can be used to pass and return data to/from **
**                        this service. This service is just a dispatcher to  **
**                        the hardware specific service implementation        **
**                        referenced by hwServiceId. The result of this       **
**                        service can be retrieved using the Mem_GetJobResult **
**                        API. If the hardware specific operation was         **
**                        successful, the result of the job is MEM_JOB_OK.    **
**                        If the hardware specific operation failed,          **
**                        the result of the job is MEM_JOB_FAILED.            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId: ID of the related memory driver instance**
**                        hwServiceId: Hardware specific service request      **
**                          identifier for dispatching the request.           **
**                        dataPtr: Request specific data pointer              **
**                        lengthPtr: Size pointer of the data passed          **
**                          by dataPtr                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType:                                     **
**                        - E_OK: The requested job has been accepted by the  **
**                          module.                                           **
**                        - E_NOT_OK: The requested job has not been accepted **
**                          by the module.                                    **
**                        - E_MEM_SERVICE_NOT_AVAIL: The service function is  **
**                          not implemented.                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 SRS_Mem_BSW_00406 SRS_Mem_BSW_00323 SRS_Mem_BSW_00004 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_HwSpecificService(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_HwServiceIdType, AUTOMATIC) hwServiceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_044 */
  retVal = E_NOT_OK;
  if (MEM_76_PFLS_FALSE == Mem_76_Pfls_InitDone)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_045 */
    /* API service called without module initialization */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_ERASE_SID, MEM_76_PFLS_E_UNINIT);
    #endif
  }
  else if (MEM_76_PFLS_NUMBER_OF_INSTANCES <= instanceId)
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_046 */
    /* Wrong instance ID */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_READ_SID, MEM_76_PFLS_E_PARAM_INSTANCE_ID);
    #endif
  }
  else if ((dataPtr == NULL_PTR) || (lengthPtr == NULL_PTR))
  {
    /* @Trace: Mem_76_Pfls_SUD_FUNC_047 */
    /* Wrong instance ID */
    #if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
      (void) Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, \
        MEM_76_PFLS_READ_SID, MEM_76_PFLS_E_PARAM_POINTER);
    #endif
  }
  else
  {
    switch(hwServiceId)
    {
      case MEM_76_PFLS_ACTIVE_BANK_CHECK:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_048 */
        retVal = Mem_76_Pfls_ActiveBankCheck(dataPtr, lengthPtr);
        break;
      case MEM_76_PFLS_GET_FLASH_ALIGNMENT:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_049 */
        retVal = Mem_76_Pfls_GetFlashAlignment(instanceId, dataPtr, lengthPtr);
        break;
      case MEM_76_PFLS_GET_SECTOR_SIZE:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_050 */
        retVal = Mem_76_Pfls_GetSectorSize(instanceId, dataPtr, lengthPtr);
        break;
      #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
      case MEM_76_PFLS_TOOLBOX_ACTIVE_SERVICE:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_051 */
        retVal = Mem_76_Pfls_ToolBox_Active_Service(instanceId, dataPtr, lengthPtr);
        break;
      #endif
      case MEM_76_PFLS_SWAP_ACTIVE:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_052 Mem_76_Pfls_SUD_MACRO_010 */
        retVal = Mem_76_Pfls_SwapActive(instanceId, dataPtr, lengthPtr);
        break;
      case MEM_76_PFLS_DIRECT_ADDRESS_ACCESS:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_053 */
        retVal = Mem_76_Pfls_DirectAddressAccess(instanceId, dataPtr, lengthPtr);
        break;
      case MEM_76_PFLS_ALT_ADDRESS_ACCESS:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_054 */
        retVal = Mem_76_Pfls_AltAddressAccess(instanceId, dataPtr, lengthPtr);
        break;
      case MEM_76_PFLS_GET_OFFSET_STD_ALT:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_055 */
        retVal = Mem_76_Pfls_GetAltAddress(instanceId, dataPtr, lengthPtr);
        break;
      case MEM_76_PFLS_CANCEL_JOB:
        retVal = Mem_76_Pfls_Cancel(instanceId, dataPtr, lengthPtr);
        break;
      default:
        /* @Trace: Mem_76_Pfls_SUD_FUNC_056 */
        retVal = E_MEM_SERVICE_NOT_AVAIL;
        break;
    }
  }
  return (retVal);
}
/*******************************************************************************
** Function Name        : Mem_76_Pfls_MainFunction                            **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Service to handle the requested jobs and the        **
**                        internal management operations.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_BSW_00172 */
#if (MEM_76_PFLS_USE_NVM == STD_ON)
FUNC(NvM_OpStatusType, MEM_76_PFLS_CODE) Mem_76_Pfls_MainFunction(void)
#else
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_MainFunction(void)
#endif
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC)   jobResult;
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC)  instanceId;

  #if (MEM_76_PFLS_USE_NVM == STD_ON)
  NvM_OpStatusType userJobReport = NVM_OPSTATUS_IDLE;
  static NvM_OpStatusType instanceJobReport[MEM_76_PFLS_NUMBER_OF_INSTANCES] = {NVM_OPSTATUS_IDLE,};
  #endif

  /* loop to do for each instance job */
  for (instanceId = MEM_76_PFLS_ZERO; \
      instanceId < MEM_76_PFLS_NUMBER_OF_INSTANCES; instanceId++)
  {
    #if (MEM_76_PFLS_USE_NVM == STD_ON)
    if ((MEM_JOB_PENDING == Mem_76_Pfls_InstanceInfo[instanceId].JobResult) && \
      (NVM_OPSTATUS_IDLE==NvM_CddGetStatus()))
    #else
    if (MEM_JOB_PENDING == Mem_76_Pfls_InstanceInfo[instanceId].JobResult)
    #endif
    {
      #if (MEM_76_PFLS_USE_NVM == STD_ON)
      if (NVM_OPSTATUS_BUSY == instanceJobReport[instanceId])
      #endif
      {
        switch (Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob)
        {
          case MEM_76_PFLS_JOB_READ:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_057 */
            jobResult = Mem_76_Pfls_JobReadProcess(instanceId);
            break;
          case MEM_76_PFLS_JOB_WRITE:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_058 */
            jobResult = Mem_76_Pfls_JobWriteProcess(instanceId);
            break;
          case MEM_76_PFLS_JOB_ERASE:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_059 Mem_76_Pfls_SUD_MACRO_004 */
            jobResult = Mem_76_Pfls_JobEraseProcess(instanceId);
            break;
          case MEM_76_PFLS_JOB_SWAP:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_060 */
            jobResult = Mem_76_Pfls_JobSwapProcess(instanceId);
            break;
          default:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_061 */
            jobResult = MEM_JOB_FAILED;
            break;
        }
  
        switch (jobResult)
        {
          case MEM_JOB_OK:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_062 */
            Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob = \
              MEM_76_PFLS_JOB_IDLE;
            Mem_76_Pfls_InstanceInfo[instanceId].JobResult = \
              MEM_JOB_OK;
            break;
          case MEM_JOB_FAILED:
          case MEM_INCONSISTENT:
          case MEM_ECC_UNCORRECTED:
          case MEM_ECC_CORRECTED:
			/* @Trace: Mem_76_Pfls_SUD_FUNC_063 */
            Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob = \
              MEM_76_PFLS_JOB_IDLE;
            Mem_76_Pfls_InstanceInfo[instanceId].JobResult = \
              MEM_JOB_FAILED;
            break;
          default:
            /* Do Nothing */
            break;
        }
      }

      #if (MEM_76_PFLS_USE_NVM == STD_ON)
      instanceJobReport[instanceId] = NVM_OPSTATUS_BUSY;
      #endif
    }
    else
    {
      #if (MEM_76_PFLS_USE_NVM == STD_ON)
      instanceJobReport[instanceId] = NVM_OPSTATUS_IDLE;
      #endif
    }

    #if (MEM_76_PFLS_USE_NVM == STD_ON)
	userJobReport |= instanceJobReport[instanceId];
    #endif
  }

  #if (MEM_76_PFLS_USE_NVM == STD_ON)
  return userJobReport;
  #endif
}

/*******************************************************************************
** Function Name        : Mem_76_Pfls_CheckValidAddress                       **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          :                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_BSW_00323 SRS_Mem_BSW_00004 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint8, MEM_76_PFLS_CODE) Mem_76_Pfls_CheckValidAddress( \
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) address, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length, \
  P2CONST(Mem_76_Pfls_DataType , AUTOMATIC, MEM_76_PFLS_APPL_CONST) srcPtr, \
  P2VAR(Mem_76_Pfls_DataType , AUTOMATIC, MEM_76_PFLS_APPL_DATA) destPtr, \
  VAR(uint8, AUTOMATIC) servId)
{
  VAR(uint8, AUTOMATIC)                   errCode;
  VAR(uint8, AUTOMATIC)                   addressValid;
  VAR(uint32, AUTOMATIC)                  numberOfSectors;
  VAR(uint32, AUTOMATIC)                  index;
  VAR(uint32, AUTOMATIC)                  jobQueueIndex;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)  totalLength;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) userReqStartAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) userReqEndAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) userReqStdStartAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) userReqStdEndAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) startAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) endAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) stdStartAddr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) stdEndAddr;

  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) startAddrValid;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) endAddrValid;

  P2CONST(Mem_76_Pfls_InstanceType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) \
    instancePtr;
  P2VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
    instanceInforPtr;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_068 */ 
  addressValid      = MEM_76_PFLS_FALSE;
  errCode           = MEM_76_PFLS_ZERO;
  totalLength       = MEM_76_PFLS_ZERO;

  userReqStdStartAddr  = address;
  userReqStdEndAddr    = MEM_76_PFLS_GET_END_ADDRESS(userReqStdStartAddr, length);

  userReqStartAddr  = address;
  userReqEndAddr    = MEM_76_PFLS_GET_END_ADDRESS(userReqStartAddr, length);

  instancePtr       = &Mem_76_Pfls_InstancesConfiguration[instanceId];
  instanceInforPtr  = &Mem_76_Pfls_InstanceInfo[instanceId];
  jobQueueIndex     = MEM_76_PFLS_ZERO;
  /* verify the valid range */
  numberOfSectors = instancePtr->NumberOfSectors;

  startAddrValid = instancePtr->SectorBatchesInfo[MEM_76_PFLS_ZERO].StartAddress;
  endAddrValid = instancePtr->SectorBatchesInfo[(numberOfSectors-1)].EndAddress;

  if ((userReqStdStartAddr >= startAddrValid) && (userReqStdEndAddr <= endAddrValid))
  {
    addressValid = MEM_76_PFLS_TRUE;
  }

  /* loop all sector batches */
  for (index = (uint32)MEM_76_PFLS_ZERO; index < numberOfSectors; index++)
  {
    /* check sector include User Req Addr */
    if ((instancePtr->SectorBatchesInfo[index].EndAddress >= userReqStdStartAddr) && \
      ((instancePtr->SectorBatchesInfo[index].StartAddress <= userReqStdEndAddr)))
    {
      /* get start address */
      stdStartAddr = ((instancePtr->SectorBatchesInfo[index].StartAddress <= userReqStdStartAddr) ? \
        (userReqStdStartAddr) : (instancePtr->SectorBatchesInfo[index].StartAddress));
      /* get end address */
      stdEndAddr = ((instancePtr->SectorBatchesInfo[index].EndAddress >= userReqStdEndAddr) ? \
        (userReqStdEndAddr) : (instancePtr->SectorBatchesInfo[index].EndAddress));

      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
      if(instanceInforPtr->AltAddressAccess==TRUE)
      {/* Convert Address for FOTA */
        startAddr = stdStartAddr + (instancePtr->SectorBatchesInfo[index].AltStartAddress - instancePtr->SectorBatchesInfo[index].StartAddress);
        endAddr = stdEndAddr + (instancePtr->SectorBatchesInfo[index].AltEndAddress - instancePtr->SectorBatchesInfo[index].EndAddress);
        userReqStartAddr = userReqStdStartAddr + (instancePtr->SectorBatchesInfo[index].AltStartAddress - instancePtr->SectorBatchesInfo[index].StartAddress);
        userReqEndAddr = userReqStdEndAddr + (instancePtr->SectorBatchesInfo[index].AltEndAddress - instancePtr->SectorBatchesInfo[index].EndAddress);
      }
      else
      {
        startAddr = stdStartAddr;
        endAddr = stdEndAddr;
        userReqStartAddr = userReqStdStartAddr;
        userReqEndAddr = userReqStdEndAddr;
      }
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

      /* put infor to queue */
      instanceInforPtr->SectorInfo[jobQueueIndex].Length = \
        MEM_76_PFLS_GET_LENGTH(startAddr, endAddr);

      totalLength += MEM_76_PFLS_GET_LENGTH(startAddr, endAddr);

      /* get type of request */
      switch (servId)
      {
        /* @Trace: Mem_76_Pfls_SUD_FUNC_105 */ 
        case MEM_76_PFLS_READ_SID:
          if (MEM_76_PFLS_ZERO != \
            (startAddr % (instancePtr->SectorBatchesInfo[index].ReadPageSize)))
          {
            errCode = MEM_76_PFLS_E_PARAM_ADDRESS;
          }
          else if (MEM_76_PFLS_ZERO != \
            (MEM_76_PFLS_GET_LENGTH(startAddr, endAddr) % \
            (instancePtr->SectorBatchesInfo[index].ReadPageSize)))
          {
            errCode = MEM_76_PFLS_E_PARAM_LENGTH;
          }
          else
          {
            errCode = MEM_76_PFLS_ZERO;

            instanceInforPtr->SectorInfo[jobQueueIndex].SrcAddress = startAddr;
            instanceInforPtr->SectorInfo[jobQueueIndex].NormalSize = \
              instancePtr->SectorBatchesInfo[index].ReadPageSize;
            if (NULL_PTR != instancePtr->SectorBatchesInfo[index].BurstSettingsPtr)
            {
              instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
                instancePtr->SectorBatchesInfo[index].BurstSettingsPtr->ReadBurstSize;
            }
            else
            {
              /* not support */
              instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
                MEM_76_PFLS_ZERO;
            }

            instanceInforPtr->SectorInfo[jobQueueIndex].SrcPtr = NULL_PTR;

            instanceInforPtr->SectorInfo[jobQueueIndex].DestPtr = \
              &(destPtr[startAddr - userReqStartAddr]);
          }
          break;
        /* @Trace: Mem_76_Pfls_SUD_FUNC_106 */ 
        case MEM_76_PFLS_WRITE_SID:
          if (MEM_76_PFLS_ZERO != \
            (startAddr % (instancePtr->SectorBatchesInfo[index].WritePageSize)))
          {
            errCode = MEM_76_PFLS_E_PARAM_ADDRESS;
          }
          else if (MEM_76_PFLS_ZERO != \
            (MEM_76_PFLS_GET_LENGTH(startAddr, endAddr) % \
            (instancePtr->SectorBatchesInfo[index].WritePageSize)))
          {
            errCode = MEM_76_PFLS_E_PARAM_LENGTH;
          }
          else
          {
            errCode = MEM_76_PFLS_ZERO;

            instanceInforPtr->SectorInfo[jobQueueIndex].DestAddress = startAddr;
            instanceInforPtr->SectorInfo[jobQueueIndex].NormalSize = \
              instancePtr->SectorBatchesInfo[index].WritePageSize;
            if (NULL_PTR != instancePtr->SectorBatchesInfo[index].BurstSettingsPtr)
            {
              instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
                instancePtr->SectorBatchesInfo[index].BurstSettingsPtr->WriteBurstSize;
            }
            else
            {
              /* not support */
              instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
                MEM_76_PFLS_ZERO;
            }

            instanceInforPtr->SectorInfo[jobQueueIndex].SrcPtr = \
              &(srcPtr[startAddr - userReqStartAddr]);
            instanceInforPtr->SectorInfo[jobQueueIndex].DestPtr = NULL_PTR;
          }
          break;
        /* @Trace: Mem_76_Pfls_SUD_FUNC_107 */ 
        case MEM_76_PFLS_ERASE_SID:
          if (MEM_76_PFLS_ZERO != \
            (startAddr % (instancePtr->SectorBatchesInfo[index].EraseSectorSize)))
          {
            errCode = MEM_76_PFLS_E_PARAM_ADDRESS;
          }
          else if (MEM_76_PFLS_ZERO != \
            (MEM_76_PFLS_GET_LENGTH(startAddr, endAddr) % \
            (instancePtr->SectorBatchesInfo[index].EraseSectorSize)))
          {
            errCode = MEM_76_PFLS_E_PARAM_LENGTH;
          }
          else
          {
            errCode = MEM_76_PFLS_ZERO;

            instanceInforPtr->SectorInfo[jobQueueIndex].DestAddress = startAddr;
            instanceInforPtr->SectorInfo[jobQueueIndex].NormalSize = \
              instancePtr->SectorBatchesInfo[index].EraseSectorSize;
            if (NULL_PTR != instancePtr->SectorBatchesInfo[index].BurstSettingsPtr)
            {
              instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
                instancePtr->SectorBatchesInfo[index].BurstSettingsPtr->EraseBurstSize;
            }
            else
            {
              /* not support */
              instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
                MEM_76_PFLS_ZERO;
            }
            /* no need to know SrcPtr & DestPtr */
            instanceInforPtr->SectorInfo[jobQueueIndex].SrcPtr  = NULL_PTR;
            instanceInforPtr->SectorInfo[jobQueueIndex].DestPtr = NULL_PTR;
          }
          break;

        default:
          errCode = MEM_76_PFLS_E_PARAM_ADDRESS;

          instanceInforPtr->SectorInfo[jobQueueIndex].BurstSize = \
            MEM_76_PFLS_ZERO;

          instanceInforPtr->SectorInfo[jobQueueIndex].NormalSize = \
            MEM_76_PFLS_ZERO;
          break;
      }
      jobQueueIndex++;
    }

    if (MEM_76_PFLS_ZERO != errCode)
    {
      break;
    }
  }
  /* @Trace: Mem_76_Pfls_SUD_FUNC_108 */ 
  if (addressValid ==  MEM_76_PFLS_FALSE) {
    errCode = MEM_76_PFLS_E_PARAM_ADDRESS;
  }

  /* remain = 0 => accept */
  if (MEM_76_PFLS_ZERO == errCode)
  {
    instanceInforPtr->NumberOfSectorRemain = jobQueueIndex;
    instanceInforPtr->SectorIndex = MEM_76_PFLS_ZERO;
  }

  return errCode;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_JobReadProcess                          **
**                                                                            **
** Description          : This function used to read data from memory to data **
**                        buffer                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : Lpst_FlashParam                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"

static FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_JobReadProcess(\
  Mem_76_Pfls_InstanceIdType InstanceId)
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC) retVal;
  VAR(uint32, AUTOMATIC)                    numberOfSectorBatches;
  VAR(uint32, AUTOMATIC)                    sectorBatchIndex;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)    remainLength;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC)   targetAddress;
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
                                            dataPtr;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)    unitSize;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)    burstUnitSize;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)    currentUnitSize;
  VAR(uint8, AUTOMATIC)                     burstEnable;
  VAR(uint32, AUTOMATIC)                    totalReadCycles;
  P2VAR(Mem_76_Pfls_SectorInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
                                            sectorInforPtr;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_069 */ 
  retVal          = MEM_JOB_FAILED;
  sectorInforPtr  = &Mem_76_Pfls_InstanceInfo[InstanceId].SectorInfo[MEM_76_PFLS_ZERO];
  numberOfSectorBatches = Mem_76_Pfls_InstanceInfo[InstanceId].NumberOfSectorRemain;

  for (sectorBatchIndex = 0UL; sectorBatchIndex < numberOfSectorBatches; \
    sectorBatchIndex++)
  {
    /* target sector batch is assigned at job request */
    remainLength  = sectorInforPtr[sectorBatchIndex].Length;
    targetAddress = Mem_76_Pfls_CalBankAddress(InstanceId,\
      sectorInforPtr[sectorBatchIndex].SrcAddress);
    dataPtr       = sectorInforPtr[sectorBatchIndex].DestPtr;

    /* find sector configuration */
    unitSize      = sectorInforPtr[sectorBatchIndex].NormalSize;
    burstUnitSize = sectorInforPtr[sectorBatchIndex].BurstSize;
    /* remain length update - reserve for future */
    while (MEM_76_PFLS_ZERO < remainLength)
    {
      if ((MEM_76_PFLS_ZERO != burstUnitSize) && \
        (MEM_76_PFLS_ZERO == (targetAddress % burstUnitSize)) && \
        (remainLength >= burstUnitSize ) )
      {
        /* Do burst erase */
        currentUnitSize = burstUnitSize;
        burstEnable     = MEM_76_PFLS_TRUE;
      }
      else
      {
        /* Do normal erase */
        currentUnitSize = unitSize;
        burstEnable     = MEM_76_PFLS_FALSE;
      }
      /* calculate total cycle to read all data with current unit size */
      totalReadCycles   = (remainLength / (Mem_76_Pfls_LengthType)currentUnitSize);
      while (MEM_76_PFLS_ZERO < totalReadCycles)
      {
        /* Do memcpy */
        #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
        retVal = (Mem_76_Pfls_InternalReadRamFunction)(\
                  targetAddress, \
                  dataPtr, \
                  currentUnitSize, \
                  burstEnable);
        #else
        retVal = (Mem_76_Pfls_InternalRead)(\
                  targetAddress, \
                  dataPtr, \
                  currentUnitSize, \
                  burstEnable);
        #endif

        totalReadCycles--;

        if (MEM_JOB_OK == retVal)
        {
          remainLength  -= (currentUnitSize);
          targetAddress += (currentUnitSize);
          dataPtr        = &dataPtr[currentUnitSize];
        }
        else
        {
          break;
        }
      }
      if (MEM_JOB_OK != retVal)
      {
        break;
      }
    }
  }

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_JobWriteProcess                         **
**                                                                            **
** Description          :                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : InstanceId                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"

static FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_JobWriteProcess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) InstanceId)
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC)     retVal;
  VAR(uint8, AUTOMATIC)                         index;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)        remainLength;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC)       targetAddress;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)        unitSize;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)        burstUnitSize;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)        currentUnitSize;
  VAR(uint8, AUTOMATIC)                         burstEnable;
  VAR(uint32, AUTOMATIC)                        sectorBatchIndex;
  VAR(uint32, AUTOMATIC)                        numberOfSectorBatches;
  VAR(uint32, AUTOMATIC)                        totalWriteCycles;
  P2CONST(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA)  dataPtr;
  P2VAR(Mem_76_Pfls_SectorInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
                                                sectorInforPtr;

  VAR(Mem_76_Pfls_InstanceType, AUTOMATIC)      instance;
  P2CONST(Mem_76_Pfls_PreCalloutType, AUTOMATIC, MEM_76_PFLS_APPL_DATA)      preCalloutInfo;
  P2CONST(Mem_76_Pfls_PostCalloutType, AUTOMATIC, MEM_76_PFLS_APPL_DATA)     postCalloutInfo;
  VAR(uint8, AUTOMATIC) 						dataPtrTemp[512];
  /* @Trace: Mem_76_Pfls_SUD_FUNC_070 */ 
  retVal                = MEM_JOB_FAILED;
  sectorInforPtr        = &Mem_76_Pfls_InstanceInfo[InstanceId].SectorInfo[MEM_76_PFLS_ZERO];
  numberOfSectorBatches = Mem_76_Pfls_InstanceInfo[InstanceId].NumberOfSectorRemain;

  instance              = Mem_76_Pfls_InstancesConfiguration[InstanceId];
  preCalloutInfo        = instance.PreCalloutInfo;
  postCalloutInfo       = instance.PostCalloutInfo;


  for (sectorBatchIndex = 0UL; sectorBatchIndex < numberOfSectorBatches; \
    sectorBatchIndex++)
  {
    /* target sector batch is assigned at job request */
    remainLength  = sectorInforPtr[sectorBatchIndex].Length;
    targetAddress = Mem_76_Pfls_CalBankAddress(InstanceId,\
      sectorInforPtr[sectorBatchIndex].DestAddress);
    dataPtr       = sectorInforPtr[sectorBatchIndex].SrcPtr;
    /* find sector configuration */
    unitSize      = sectorInforPtr[sectorBatchIndex].NormalSize;
    burstUnitSize = sectorInforPtr[sectorBatchIndex].BurstSize;
    /* remain length update - reserve for future */
    while (MEM_76_PFLS_ZERO < remainLength)
    {
      if ((MEM_76_PFLS_ZERO != burstUnitSize) && \
        (MEM_76_PFLS_ZERO == (targetAddress % burstUnitSize)) && \
        (remainLength >= burstUnitSize ) )
      {
        /* Do burst erase */
        currentUnitSize = burstUnitSize;
        burstEnable     = MEM_76_PFLS_TRUE;
      }
      else
      {
        /* Do normal erase */
        currentUnitSize = unitSize;
        burstEnable     = MEM_76_PFLS_FALSE;
      }
      /* calculate total cycle to write all data with current unit size */
      totalWriteCycles = (remainLength / (Mem_76_Pfls_LengthType)currentUnitSize);

      while (MEM_76_PFLS_ZERO < totalWriteCycles)
      {
        /* @Trace: Mem_76_Pfls_SUD_MACRO_011 Mem_76_Pfls_SUD_MACRO_012 */
        #if (MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON)
        if(NULL_PTR != preCalloutInfo)
        {
          for(index = 0u; index < preCalloutInfo->NumberOfPreCallout; index++)
          {
            if(NULL_PTR != preCalloutInfo->PreCalloutFunction[index])
            {
              preCalloutInfo->PreCalloutFunction[index](InstanceId);
            }
          }
        }
        #endif /* MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON */

        (void)MEM_76_PFLS_MEMCPY(dataPtrTemp, dataPtr, currentUnitSize);

        #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
        SchM_Enter_Mem_76_Pfls_CRITICAL_SECTION();

        /* 32 Bytes per cycle - normal */
        /* 256 Bytes per cycle - burst */
        retVal = (Mem_76_Pfls_InternalWriteRamFunction)(\
                  targetAddress, dataPtrTemp, unitSize, burstUnitSize, burstEnable);

        SchM_Exit_Mem_76_Pfls_CRITICAL_SECTION();

        #else
        retVal = (Mem_76_Pfls_InternalWrite)(\
                  targetAddress, dataPtrTemp, unitSize, burstUnitSize, burstEnable);
        #endif

		/* @Trace: Mem_76_Pfls_SUD_MACRO_013 */
        #if (MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON)
        if(NULL_PTR != postCalloutInfo)
        {
          for(index = 0; index < postCalloutInfo->NumberOfPostCallout; index++)
          {
        	if(NULL_PTR != postCalloutInfo->PostCalloutFunction[index])
        	{
              postCalloutInfo->PostCalloutFunction[index](InstanceId);
        	}
          }
        }
        #endif /* MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON */

        totalWriteCycles--;

        if (MEM_JOB_OK == retVal)
        {
          remainLength  -= (currentUnitSize);
          targetAddress += (currentUnitSize);
          dataPtr        = &dataPtr[currentUnitSize];
        }
        else
        {
          break;
        }
      }
      if (MEM_JOB_OK != retVal)
      {
        break;
      }
    }
  }

  return retVal;
}

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_JobEraseProcess                         **
**                                                                            **
** Description          : This function used to set erase job from queue      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : InstanceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
static FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_JobEraseProcess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) InstanceId)
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC)     retVal;
  VAR(uint8, AUTOMATIC)                         index;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC)       targetAddress;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)        remainLength;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)        unitSize;
  VAR(uint32, AUTOMATIC)                        sectorBatchIndex;
  VAR(Mem_76_Pfls_DataType, AUTOMATIC)          numberOfSectorBeErased;

  P2VAR(Mem_76_Pfls_SectorInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA)  \
                                                sectorInforPtr;

  VAR(Mem_76_Pfls_InstanceType, AUTOMATIC)      instance;
  P2CONST(Mem_76_Pfls_PreCalloutType, AUTOMATIC, MEM_76_PFLS_APPL_DATA)      preCalloutInfo;
  P2CONST(Mem_76_Pfls_PostCalloutType, AUTOMATIC, MEM_76_PFLS_APPL_DATA)     postCalloutInfo;

  sectorBatchIndex       = Mem_76_Pfls_InstanceInfo[InstanceId].SectorIndex;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_071 */ 
  retVal                 = MEM_JOB_FAILED;
  sectorInforPtr         = &Mem_76_Pfls_InstanceInfo[InstanceId].SectorInfo[0];
  instance               = Mem_76_Pfls_InstancesConfiguration[InstanceId];
  preCalloutInfo         = instance.PreCalloutInfo;
  postCalloutInfo        = instance.PostCalloutInfo;
  numberOfSectorBeErased = MEM_76_PFLS_ONE;


  /* Verify address */
  /* get information from structure */
  targetAddress = Mem_76_Pfls_CalBankAddress(InstanceId,\
    sectorInforPtr[sectorBatchIndex].DestAddress);
  remainLength  = sectorInforPtr[sectorBatchIndex].Length;
  unitSize      = sectorInforPtr[sectorBatchIndex].NormalSize;

  #if (MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON)
  if(NULL_PTR != preCalloutInfo)
  {
    for(index = 0u; index < preCalloutInfo->NumberOfPreCallout; index++)
    {
      if(NULL_PTR != preCalloutInfo->PreCalloutFunction[index])
      {
        preCalloutInfo->PreCalloutFunction[index](InstanceId);
      }
    }
  }
  #endif /* MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON */

  #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
  /* DI is not used in OTA mode */
  SchM_Enter_Mem_76_Pfls_CRITICAL_SECTION();

  retVal = (Mem_76_Pfls_InternalEraseRamFunction)(\
            targetAddress, &numberOfSectorBeErased, remainLength, MEM_76_PFLS_FALSE);
  /* DI is not used in OTA mode */
  SchM_Exit_Mem_76_Pfls_CRITICAL_SECTION();
  #else
  retVal = (Mem_76_Pfls_InternalErase)(\
            targetAddress, &numberOfSectorBeErased, remainLength, MEM_76_PFLS_FALSE);
  #endif

  #if (MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON)
  if(NULL_PTR != postCalloutInfo)
  {
    for(index = 0; index < postCalloutInfo->NumberOfPostCallout; index++)
    {
      if(NULL_PTR != postCalloutInfo->PostCalloutFunction[index])
      {
         postCalloutInfo->PostCalloutFunction[index](InstanceId);
      }
    }
  }
  #endif /* MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON */

  if(Mem_76_Pfls_InstanceInfo[InstanceId].CancelJob==TRUE)
  {
  	Mem_76_Pfls_InstanceInfo[InstanceId].CancelJob=FALSE;
  	retVal=MEM_JOB_FAILED;
  }
  else
  {
    if (MEM_JOB_OK == retVal)
    {
      Mem_76_Pfls_InstanceInfo[InstanceId].SectorInfo[sectorBatchIndex].Length -= (numberOfSectorBeErased*unitSize);
      if (Mem_76_Pfls_InstanceInfo[InstanceId].SectorInfo[sectorBatchIndex].Length > MEM_76_PFLS_ZERO)
      {
        Mem_76_Pfls_InstanceInfo[InstanceId].SectorInfo[sectorBatchIndex].DestAddress += (numberOfSectorBeErased*unitSize);
        retVal = MEM_JOB_PENDING;
      }
      else
      {
        if (sectorBatchIndex < (Mem_76_Pfls_InstanceInfo[InstanceId].NumberOfSectorRemain - MEM_76_PFLS_ONE))
        {
          Mem_76_Pfls_InstanceInfo[InstanceId].SectorIndex++;
          retVal = MEM_JOB_PENDING;
        }
      }
    }  
  }
  return retVal;
}
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_GetFlashAlignment                       **
**                                                                            **
** Description          : This function used to get flash alignment size from **
**                        pfls                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None	                                              **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetFlashAlignment(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_008  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  VAR(Mem_76_Pfls_InstanceType, AUTOMATIC) instanceInfo;
  VAR(Mem_76_Pfls_SectorBatchType, AUTOMATIC) sectorBatchInfo;
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) lengthAlignment;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_073 */ 
  retVal = E_OK;
  instanceInfo = Mem_76_Pfls_InstancesConfiguration[instanceId];
  sectorBatchInfo = instanceInfo.SectorBatchesInfo[MEM_76_PFLS_ZERO];

  lengthAlignment = sectorBatchInfo.WritePageSize;

  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    dataPtr[MEM_76_PFLS_ZERO]  = (Mem_76_Pfls_DataType)(lengthAlignment & 0xFFu);
    dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((lengthAlignment >> 8) & 0xFFu);
    dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((lengthAlignment >> 16) & 0xFFu);
    dataPtr[MEM_76_PFLS_THREE] = (Mem_76_Pfls_DataType)((lengthAlignment >> 24) & 0xFFu);
  #else
    dataPtr[MEM_76_PFLS_THREE] = (Mem_76_Pfls_DataType)(lengthAlignment & 0xFFu);
    dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((lengthAlignment >> 8) & 0xFFu);
    dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((lengthAlignment >> 16) & 0xFFu);
    dataPtr[MEM_76_PFLS_ZERO]  = (Mem_76_Pfls_DataType)((lengthAlignment >> 24) & 0xFFu);
  #endif

  *lengthPtr = MEM_76_PFLS_FOUR;

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_GetSectorSize                           **
**                                                                            **
** Description          : This function used to get sector size from pfls     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None	                                              **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetSectorSize(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;

  VAR(Mem_76_Pfls_InstanceType,AUTOMATIC) instanceInfo;

  VAR(Mem_76_Pfls_SectorBatchType,AUTOMATIC) sectorBatchInfo;

  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) sectorSize;
  uint32 numberOfSectors;
  uint32 addressOfSector;
  uint8 sectorBatchIndex;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_074 */ 
  retVal = E_NOT_OK;

  instanceInfo = Mem_76_Pfls_InstancesConfiguration[instanceId];

  numberOfSectors = instanceInfo.NumberOfSectors;

  /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  addressOfSector =  (uint32)(dataPtr[MEM_76_PFLS_ZERO] & 0xFFu) |
                      ((uint32)(dataPtr[MEM_76_PFLS_ONE] & 0xFFu) << 8) |
                      ((uint32)(dataPtr[MEM_76_PFLS_TWO] & 0xFFu) << 16) |
                      ((uint32)(dataPtr[MEM_76_PFLS_THREE] & 0xFFu) << 24);
  #else
  addressOfSector =  (uint32)(dataPtr[MEM_76_PFLS_THREE] & 0xFFu) |
                      ((uint32)(dataPtr[MEM_76_PFLS_TWO] & 0xFFu) << 8) |
                      ((uint32)(dataPtr[MEM_76_PFLS_ONE] & 0xFFu) << 16) |
                      ((uint32)(dataPtr[MEM_76_PFLS_ZERO] & 0xFFu) << 24);
  #endif
  /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */

  for (sectorBatchIndex = 0u; sectorBatchIndex < numberOfSectors; \
    sectorBatchIndex++)
  {
    sectorBatchInfo = instanceInfo.SectorBatchesInfo[sectorBatchIndex];

    if ((addressOfSector >= sectorBatchInfo.StartAddress) &&
      (addressOfSector <= sectorBatchInfo.EndAddress))
    {
      sectorSize = sectorBatchInfo.EraseSectorSize;

      #if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        dataPtr[MEM_76_PFLS_ZERO]  = (Mem_76_Pfls_DataType)(sectorSize & 0xFFu);
        dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((sectorSize >> 8) & 0xFFu);
        dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((sectorSize >> 16) & 0xFFu);
        dataPtr[MEM_76_PFLS_THREE] = (Mem_76_Pfls_DataType)((sectorSize >> 24) & 0xFFu);
      #else
        dataPtr[MEM_76_PFLS_THREE] = (Mem_76_Pfls_DataType)(sectorSize & 0xFFu);
        dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((sectorSize >> 8) & 0xFFu);
        dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((sectorSize >> 16) & 0xFFu);
        dataPtr[MEM_76_PFLS_ZERO]  = (Mem_76_Pfls_DataType)((sectorSize >> 24) & 0xFFu);
      #endif
      *lengthPtr = MEM_76_PFLS_FOUR;
      retVal = E_OK;
      break;
    }
  }
  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_GetSectorSize                           **
**                                                                            **
** Description          : This function used to get sector size from pfls     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetAltAddress(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  P2CONST(Mem_76_Pfls_InstanceType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) \
    instancePtr;
  VAR(Mem_76_Pfls_SectorBatchType,AUTOMATIC) sectorBatchInfo;
  VAR(uint32, AUTOMATIC)                        sectorBatchIndex;
  uint32 numberOfSectors;
  uint32 stdStartAddress;
  uint32 stdEndAddress;
  uint32 altStartAddress;
  uint32 dataSize;
  uint32 offsetStdAlt;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_075 */ 
  retVal = E_NOT_OK;

  instancePtr = &Mem_76_Pfls_InstancesConfiguration[instanceId];

  numberOfSectors = instancePtr->NumberOfSectors;
  /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
  #if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  stdStartAddress =  (uint32)(dataPtr[MEM_76_PFLS_ZERO] & 0xFFu) |
                      ((uint32)(dataPtr[MEM_76_PFLS_ONE] & 0xFFu) << 8) |
                      ((uint32)(dataPtr[MEM_76_PFLS_TWO] & 0xFFu) << 16) |
                      ((uint32)(dataPtr[MEM_76_PFLS_THREE] & 0xFFu) << 24);
  #else
  stdStartAddress =  (uint32)(dataPtr[MEM_76_PFLS_THREE] & 0xFFu) |
                      ((uint32)(dataPtr[MEM_76_PFLS_TWO] & 0xFFu) << 8) |
                      ((uint32)(dataPtr[MEM_76_PFLS_ONE] & 0xFFu) << 16) |
                      ((uint32)(dataPtr[MEM_76_PFLS_ZERO] & 0xFFu) << 24);
  #endif
  /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
  dataSize = *lengthPtr;
  stdEndAddress = stdStartAddress + dataSize - MEM_76_PFLS_ONE;
  /* Verify address */
  for (sectorBatchIndex = 0UL; sectorBatchIndex < numberOfSectors; \
    sectorBatchIndex++)
  {
    sectorBatchInfo = instancePtr->SectorBatchesInfo[sectorBatchIndex];

    if ((stdStartAddress >= sectorBatchInfo.StartAddress) &&
      (stdStartAddress <= sectorBatchInfo.EndAddress))
    {
    	if(stdEndAddress>sectorBatchInfo.EndAddress)
    	{
    		*lengthPtr = sectorBatchInfo.EndAddress - stdStartAddress + MEM_76_PFLS_ONE;
    	}

        offsetStdAlt = sectorBatchInfo.AltStartAddress - sectorBatchInfo.StartAddress;
        altStartAddress = stdStartAddress + offsetStdAlt;

		#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
		  dataPtr[MEM_76_PFLS_ZERO]  = (Mem_76_Pfls_DataType)(altStartAddress & 0xFFu);
		  dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((altStartAddress >> 8) & 0xFFu);
		  dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((altStartAddress >> 16) & 0xFFu);
		  dataPtr[MEM_76_PFLS_THREE] = (Mem_76_Pfls_DataType)((altStartAddress >> 24) & 0xFFu);
		#else
		  dataPtr[MEM_76_PFLS_THREE]  = (Mem_76_Pfls_DataType)(altStartAddress & 0xFFu);
		  dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((altStartAddress >> 8) & 0xFFu);
		  dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((altStartAddress >> 16) & 0xFFu);
		  dataPtr[MEM_76_PFLS_ZERO] = (Mem_76_Pfls_DataType)((altStartAddress >> 24) & 0xFFu);
		#endif
	    retVal = E_OK;
	    break;
    }
  }
  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_Cancel                                  **
**                                                                            **
** Description          : This function used to cancel job process from pfls  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None	                                              **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Cancel(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  P2VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) instanceInforPtr;
  retVal = E_OK;

  instanceInforPtr  = &Mem_76_Pfls_InstanceInfo[instanceId];

  instanceInforPtr->CancelJob = TRUE;

  *dataPtr=(Mem_76_Pfls_DataType)instanceInforPtr->CancelJob;
  *lengthPtr=sizeof(boolean);

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_ToolBox_Active                          **
**                                                                            **
** Description          : Function to Copy flash driver from ROM to RAM       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* Function to Copy Flash driver from ROM to RAM  */
/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
static FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_ToolBox_Active_Service(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_076 */ 
  retVal = E_OK;
  Mem_76_Pfls_ToolBox_Active = MEM_76_PFLS_TRUE;
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "It depends on the configuration." */
  Mem_76_Pfls_ToolBox_InternalActive();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "It depends on the configuration." */
  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
