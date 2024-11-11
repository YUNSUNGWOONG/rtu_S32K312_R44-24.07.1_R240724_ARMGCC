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
**  SRC-MODULE: Dem.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of Dem interface functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"                   /* Dem module header file */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Det module header file */
#endif
#include "Dem_Ram.h"              /* Dem global Ram variables header file */

#if (DEM_FIM_INTEGRATED == STD_ON)
#include "FiM_Dem.h"                  /* FiM module header file */
#endif


#include "NvM.h"                  /* NvM module  header File */

#include "EcuM.h"               /* Reset Reason */
#include "Mcu.h"

#include "Rte_Dem.h"
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */

#include "Dem_EventMemory.h"
#include "Dem_Event.h"
#include "BswM.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_Component.h"


#include "Dem_Indicator.h"

#if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
#include "Dcm.h" /* Dcm_ProgConditionsType */
#include "Dcm_CallOuts.h" /* for Dcm_GetProgConditions */
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This Service returns the version information of     **
**                        Diagnostic Event Manager Module.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00402 SRS_BSW_00407
 */
/* @Trace: Dem_SUD_MACRO_002 */
#if (DEM_VERSION_INFO_API == STD_ON)
FUNC(void, DEM_CODE) Dem_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)versioninfo)
{
  /* @Trace: SWS_Dem_00177
   */
  /* check NULL pointer */
  if (versioninfo == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_00001 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_GETVERSIONINFO_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_00002 */
    /* Load the vendor Id */
    /* @Trace: Dem_SUD_MACRO_129 */
    versioninfo->vendorID = DEM_VENDOR_ID;
    /* Load the module Id */
    /* @Trace: Dem_SUD_MACRO_130 */
    versioninfo->moduleID = DEM_MODULE_ID;
    /* Load Software Major Version */
    /* @Trace: Dem_SUD_MACRO_126 */
    versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    /* @Trace: Dem_SUD_MACRO_127 */
    versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    /* @Trace: Dem_SUD_MACRO_128 */
    versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;
  }
}
#endif /* (DEM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : Dem_PreInit                                         **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This API shall be used to initialize the internal   **
**                        states necessary to process events reported by      **
**                        BSW-modules.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_ConfigPtr                                       **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00406 SRS_Diag_04068
 */
FUNC(void, DEM_CODE) Dem_PreInit(P2CONST(Dem_ConfigType,
  AUTOMATIC, DEM_APPL_CONST)Dem_ConfigPtr)
{
  /* @Trace: SWS_Dem_00169
   * The Dem module shall distinguish between a pre-initialization
   * mode and a full-initialized mode (operation mode).
   */
  /* @Trace: SWS_Dem_00180
   * The function Dem_PreInit shall initialize the internal states
   * of the Dem module necessary to process events and reset debounce
   * counters reported by SW-C or BSW modules by using Dem_SetEventStatus
   * and Dem_ResetEventDebounceStatus.
   */
  /*To avoid compilation warning*/
  DEM_UNUSED_PTR(Dem_ConfigPtr);

  /* Set the module to pre-initialized state */
  Dem_GucInit = DEM_UNINIT;
  
  /* BswEventQueue(Dem_InitBswEventQueue) is alrealy set to 0 */
  /* Dem_EventState(Dem_EvInitProcState) is  already set to 0 */
  /* @Trace: Dem_SUD_API_11908 */
  /* @Trace: Dem_SUD_MACRO_018 */
  #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11912 */
  Dem_InitBswEventQueue();
  #endif
  /* @Trace: Dem_SUD_MACRO_082 */
  #if (DEM_NUMBER_OF_EVENTS > DEM_ZERO)
  Dem_InitEventQueue();
  #endif

  /* page.91 of Dem SWS v4.2.0
   * During initialization of the Dem module,
   * the API Dem_SetEventStatus supports debouncing (pre-failed and pre-passed).
   * The corresponding debounce counters will be initialized by calling
   * Dem_PreInit. */
  /* @Trace: SWS_Dem_00438
   * If Dem-internal debouncing is configured, the Dem module shall reset the
   * Dem-internal debounce algorithm when Dem_PreInit has been called.
   */
  Dem_InitDebounce();  
  /* @Trace: Dem_SUD_API_11914 */
  #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
  /* @Trace: Dem_SUD_API_11913 */
  Dem_InitEnableConditionStatus();
  #endif    
  
  /* Initialize the storage conditions */
  /* @Trace: Dem_SUD_API_11916 */
  #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
  /* @Trace: Dem_SUD_API_11915 */
  Dem_InitStorageConditionStatus();
  #endif

  Dem_EvMem_PreInit();

  Dem_InitEventFailureThreshold();

  #if ((DEM_NUMBER_OF_EVENTS > DEM_ZERO) && \
       (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY))
  Dem_EventAvailable_Init();
  #endif
  /* @Trace: Dem_SUD_API_11917 */
  #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
  {
    Dcm_ProgConditionsType LddProgCondition;
    
    LddProgCondition.ApplUpdated = DEM_FALSE;
    Dem_DoReadFromNv = DEM_TRUE;
    /* @Trace: Dem_SUD_API_11918 */
    if (DCM_WARM_START == Dcm_GetProgConditions(&LddProgCondition))
    {
      /* @Trace: Dem_SUD_API_11919 */
      if (DCM_TRUE != LddProgCondition.ApplUpdated)
      {
        Mcu_ResetType LddResetReason = MCU_POWER_ON_RESET;
        /* polyspace<MISRA-C:11.4:Not a defect:No action planned  defect>
         * EcuM_GetResetReason issue */
        /* @Trace: Dem_SUD_API_11909 */
        if (E_OK == EcuM_GetResetReason(&LddResetReason))
        {
          /* @Trace: Dem_SUD_API_11910 */
          if (MCU_SW_RESET == LddResetReason)
          {
            /* @Trace: Dem_SUD_API_11911 */
            Dem_DoReadFromNv = DEM_FALSE;
          }
        }
      }
    }
  }
  #endif

  /* Set the module to pre-initialized state */
  Dem_GucInit = DEM_PREINIT;
}

/*******************************************************************************
** Function Name        : Dem_WriteNvData                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Write Nv data to nv block                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : 1. This function is called after Dem_PreInit is     **
**                           called by BswM                                   **
**                        2. This function is able to be called by Cdd        **
**                        3. This function is called after Dem_Shutdown is    **
**                           called by BswM                                   **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_WriteNvData(void)
{
  /* progressing or  shutdown  */
  if ((DEM_INIT != Dem_GucInit) && (DEM_DEINIT != Dem_GucInit))
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false */
  {
    /* @Trace: Dem_SUD_API_10653 */
    DEM_REPORT_ERROR(DEM_INIT_SID, DEM_E_WRONG_CONDITION);
  }
  else
  {
    /* @Trace: Dem_SUD_API_10652 */
    uint8 LucIndex;
    for (uint8 LucClientId = DEM_ZERO;
               LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
               LucClientId++)
    {
      /* @Trace: Dem_SUD_API_13268 */
      /* @Trace: Dem_SUD_API_13269 */
      for (LucIndex = DEM_ZERO;
           LucIndex < Dem_NumOfSupportedDTCOrigins;
           LucIndex++)
      {
        /* @Trace: Dem_SUD_API_13270 */
        Dem_DTCOriginType LddDTCOrigin = Dem_SupportedDTCOrigins[LucIndex];
        Dem_NumOfEventMemoryEntryType LddMemLoc;

        Dem_NumOfEventMemoryEntryType LddSizeOfMem =
            Dem_EvMem_GetSizeOfEventMemory(LucClientId, LddDTCOrigin);
        Dem_NumOfEventMemoryEntryType LddStartIndex =
            Dem_EvMem_GetStartIndexEvMemory(LucClientId, LddDTCOrigin);
        LddSizeOfMem = LddSizeOfMem + LddStartIndex;
        /* @Trace: Dem_SUD_API_13271 */
        for (LddMemLoc = DEM_ZERO; LddMemLoc < LddSizeOfMem; LddMemLoc++)
        {
          /* @Trace: Dem_SUD_API_11901 */
          Dem_EvMem_SetEvMemNvBlockStatus(LddDTCOrigin, LddMemLoc,
          DEM_EVMEM_STATUS_TRIGGER_NVM | DEM_EVMEM_STATUS_FINISH_NVM);
        }
      }
    }
    /* @Trace: Dem_SUD_API_13267 */
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
        DEM_EVMEM_STATUS_TRIGGER_NVM | DEM_EVMEM_STATUS_FINISH_NVM);

    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
        DEM_EVMEM_STATUS_TRIGGER_NVM | DEM_EVMEM_STATUS_FINISH_NVM);

    Dem_EvMem_RequestWriteAllBlocks();
  }
}


/*******************************************************************************
** Function Name        : Dem_ReadNvData                                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Read Nv data from nv block                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_ReadNvData(void)
{
  if (DEM_PREINIT != Dem_GucInit)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false */
  {
    /* @Trace: Dem_SUD_API_10651 */
    DEM_REPORT_ERROR(DEM_INIT_SID, DEM_E_UNINIT);
  }
  else
  {
    #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
    if (DEM_FALSE == Dem_DoReadFromNv)
    {
      /* @Trace: Dem_SUD_API_11902 */
      /* [NOTE]
       *
       * There is a high probability that ram and non-vatile data will not match
       * Therefore, we should inform the user of this fact.  */

       /* Dem_NonVolatileDataState,Dem_EventMemoryState
        * are cleared as 0(zero) by 'VAR CLEARED SECTION' */
    }
    else
    #endif
    {
      /* @Trace: Dem_SUD_API_11903 */
      for (uint8 LucClientId = DEM_ZERO; LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
          LucClientId++)
      {
        for (uint8 LucOrgIdx = DEM_ZERO;
                   LucOrgIdx < Dem_NumOfSupportedDTCOrigins;
                   LucOrgIdx++)
        {
          /* @Trace: Dem_SUD_API_11904 */
          Dem_DTCOriginType LddDTCOrigin = Dem_SupportedDTCOrigins[LucOrgIdx];

          Dem_NumOfEventMemoryEntryType LddMemLoc;
          Dem_NumOfEventMemoryEntryType LddStartIdx = DEM_ZERO;
          Dem_NumOfEventMemoryEntryType LddStopIdx = DEM_ZERO;
          LddStartIdx = Dem_EvMem_GetStartIndexEvMemory(LucClientId, LddDTCOrigin);
          LddStopIdx = Dem_EvMem_GetStopIndexEvMemory(LucClientId, LddDTCOrigin);
          /* @Trace: Dem_SUD_API_11905 */
          for (LddMemLoc = LddStartIdx; LddMemLoc < LddStopIdx; LddMemLoc++)
          {
            Dem_EvMem_ClearEventMemoryEntry(
                Dem_EvMem_GetEmEntryByMemPosition(LddDTCOrigin, LddMemLoc));
            #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                 (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
            /* @Trace: Dem_SUD_API_11906 */
            if (DEM_DTC_ORIGIN_PERMANENT_MEMORY == LddDTCOrigin)
            {
              /* @Trace: Dem_SUD_API_11907 */
              Dem_EventIdType EventId =
                  Dem_EvMem_GetEventIdByEvMemEntry(LddDTCOrigin,LddMemLoc);
              #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
              /* Trace: DEM_COMB_01 */
              Dem_EvMem_ClearPermanentDTCAllCbEvents(EventId, DEM_TRUE);
              #else
              Dem_EvMem_ClearPermanentDTC(EventId, DEM_TRUE);
              #endif
            }
            #endif

            Dem_EvMem_InitEvMemNvBlockStatus(
                LddDTCOrigin, LddMemLoc, DEM_EVMEM_STATUS_INVALID);
          }
        }
      }
      Dem_EvMem_ResetEventStatusNvRamBlock();
      Dem_EvMem_InitNonVolatieDataStatus(
          DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_INVALID);
    }
    /*
     * else : Don't read the EventStatusBlock, EventMemoryEntryBlocks
     */

    /* Dem shoud read a FootPrint Block regardless of whether S/W Reset or
     * PowerOnReset. */
    Dem_EvMem_ResetManagementBlock(DEM_FALSE);
    Dem_EvMem_InitNonVolatieDataStatus(
        DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_INVALID);
    Dem_EvMem_RequestReadAllBlocks();

    Dem_GucInit = DEM_READNVDATA;
  }
}

/*******************************************************************************
** Function Name        : Dem_Init                                            **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Initialization of Dem                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00406 SRS_Diag_04124 SRS_Diag_04178
 */
FUNC(void, DEM_CODE) Dem_Init(void)
{
  /* @Trace: SWS_Dem_00169
   * The Dem module shall distinguish between a pre-initialization
   * mode and a full-initialized mode (operation mode).
   */
  /*Dem_DTCOriginType DTCOrigin = DEM_ZERO;*/

  if ((DEM_PREINIT != Dem_GucInit) && (DEM_READNVDATA != Dem_GucInit))
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false */
  {
    /* @Trace: Dem_SUD_API_11920 */
    DEM_REPORT_ERROR(DEM_INIT_SID, DEM_E_UNINIT);
  }
  else
  {  
    Dem_EvMem_VerifyAllEventMemories();
    Dem_EvMem_Init();

    /* @Trace: SWS_Dem_00675
     * If the configuration parameter DemDebounceCounterStorage
     * is set to True, the Dem module shall re-store the current value of the
     * internal debounce counter during each startup (latest in Dem_Init).
     * */
    /* @Trace: Dem_SUD_API_11931 */
    #if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO) && \
        (DEM_DEBOUNCE_COUNTER_STORAGE_CONFIGURED == STD_ON))
    Dem_EventIdType LddEventId;
    Dem_EventParameterPCType LddEvent;
    Dem_NumOfDebounceType LddDebounceId;
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb;
    uint8 LucDebounceType;
    /* @Trace: Dem_SUD_API_11934 */
    for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
    {
      /* @Trace: Dem_SUD_API_11937 */
      LddEvent = &Dem_Event[LddEventId - DEM_ONE];
      LucDebounceType =
          DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA);
      LddDebounceId = LddEvent->ucIndexOfDebounceAry;
      LddDcb = &Dem_GaaPreDebounceCounter[LddDebounceId];
      /* @Trace: Dem_SUD_API_11935 */
      if ((DEM_TRUE == (LddDcb->blDemDebounceCounterStorage)) &&
          (DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType))
      {
        /* @Trace: Dem_SUD_API_11936 */
        Dem_GssTempCounter[LddDebounceId] =
            Dem_EventStatusNvRamData.InternalDebouneCnt[LddDebounceId];
      }
    }
    #endif

    /* Dem_GaaDisableDtcSettingGroupDTC, Dem_GblDisableDtcSettingAllDTC
     * are already set to 0(Enable all DTC settings)
     * Dem_GstRecordDisableDTC is already set to 0 */

    /* Dem_FilteredFFRecord is already set 0 */  
    /* Dem_GaaPrestoreBuffer is already set 0 */
    /* @Trace: Dem_SUD_API_11939 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_11938 */
    Dem_InitOBD();
    #endif

    /* Dem_GucInit shall be initialized before FiM_DemInit is called */
    Dem_GucInit = DEM_INIT;

    /* @IF_REQ: SWS_Dem_01189
     * In case the Fim is used, the Dem shall call Fim_DemInit during Dem_Init
     * to trigger the initalization of the permissions inside the Fim
     * (independent of trigger or polling mode). The Fim_DemInit shall not be
     * called at any other point in time. */
    /* @Trace: Dem_SUD_API_11921 */
    #if (DEM_FIM_INTEGRATED == STD_ON)
    /* @Trace: Dem_SUD_API_11940 */
    FiM_DemInit();
    #endif

    /* @IF_REQ: in case of ASR 4.2.2
     * 
     * Note: All events which are reported via Dem_SetEventStatus before
     * Dem_Init should use a operation cycle which is auto started
     * (DemOperationCycleAutostart set to true) or persistently stored
     * (DemOperationCycleStatusStorage set to true). */
    /* @Trace: Dem_SUD_API_11923 */
    #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11922 */
    Dem_MainfunctionBswEvents();
    #endif

    Dem_MainfunctionEvents();
    /* @Trace: Dem_SUD_API_11925 */
    #if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11924 */
    Dem_Component_Init();
    #endif
    /* @Trace: Dem_SUD_API_11927 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11926 */
    Dem_InitProtectedRecord();
    #endif

    /* @Trace: SWS_Dem_01318
     * Calling the function Dem_RestartOperationCycle shall be allowed only
     * after Dem_PreInit. In case an operation cycle is restarted before
     * Dem_Init, the processing of the restart shall be done after Dem_Init.*/
    /* @Trace: Dem_SUD_API_11928 */
    /* @Trace: Dem_SUD_MACRO_088 */
    #if (DEM_NUMBER_OPERATION_CYCLES > DEM_ZERO)
    uint8 LucOperationCycleId;
    /* @Trace: Dem_SUD_API_11929 */
    for (LucOperationCycleId = DEM_ZERO;
         LucOperationCycleId < DEM_NUMBER_OPERATION_CYCLES;
         LucOperationCycleId++)
    {
      /* @Trace: Dem_SUD_API_11930 */
      if (DEM_TRUE == Dem_OperationCycleBuffer[LucOperationCycleId])
      {
        Dem_OperationCycleBuffer[LucOperationCycleId] = DEM_FALSE;
        /* @Trace: Dem_SUD_API_11932 */
        if (E_NOT_OK == Dem_RestartOperationCycle(LucOperationCycleId))
        {
          /* @Trace: Dem_SUD_API_11933 */
          Dem_OperationCycleBuffer[LucOperationCycleId] = DEM_TRUE;
        }
      }
    }
    #endif

  }
}

/*******************************************************************************
** Function Name        : Dem_Shutdown                                        **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Shutdown functionality of Dem                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04124 SRS_BSW_00336
 */
FUNC(void, DEM_CODE) Dem_Shutdown(void)
{
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00032 */
    DEM_REPORT_ERROR(DEM_SHUTDOWN_SID, DEM_E_UNINIT);
  }
  else
  {  
    /*
     * [Dem102] The API Dem_Shutdown shall finalize all pending operations in
     * the Dem module to prepare the internal states and data for transfer to
     * the NVRAM. The event  memory shall be locked and not modified until the
     * API Dem_Init is recalled. (BSW101)
     *
     * The ECU State Manager is responsible to initiate the copying process of
     * data from RAM to NVRAM (refer to API NvM_WriteAll).
     *
     * [Dem341] For individual non-volatile blocks the API NvM_WriteBlock shall
     * be called within the API Dem_Shutdown.
     *
     * If the ECU power supply is disconnected before the NvM has finished
     * copying all data to NVRAM, these data will be incomplete/inconsistent or
     * not stored. At next startup, the events of the last operating cycle could
     * not be found anymore. Therefore, the NVRAM Manager configuration provides
     * mechanisms for data consistency, like redundant data blocks.
     */

    /* if Dem_WriteNvData was called by Application, Bsw mode shall be
     * initilaized to call Dem_WriteNvData again */
    /* @Trace: Dem_SUD_API_00031 */
    BswM_RequestMode(DEM_MODULE_ID, DEM_BSWM_MODE_DEFAULT);

    /* @Trace: SWS_Dem_00674
     * If the configuration parameter DemDebounceCounterStorage
     * is set to True, the Dem module shall store the current value of the
     * internal debounce counter non-volatile (refer to [SWS_Dem_00341]).
     * */
    /* @Trace: Dem_SUD_API_11941 */
    #if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO) && \
        (DEM_DEBOUNCE_COUNTER_STORAGE_CONFIGURED == STD_ON))
    Dem_EventIdType LddEventId;
    Dem_EventParameterPCType LddEvent;
    Dem_NumOfDebounceType LddDebounceId;
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb;
    uint8 LucDebounceType;
    /* @Trace: Dem_SUD_API_11943 */
    for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
    {
      LddEvent = &Dem_Event[LddEventId - DEM_ONE];
      LucDebounceType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA);
      LddDebounceId = LddEvent->ucIndexOfDebounceAry;
      LddDcb = &Dem_GaaPreDebounceCounter[LddDebounceId];
      /* @Trace: Dem_SUD_API_11944 */
      if ((DEM_TRUE == (LddDcb->blDemDebounceCounterStorage)) &&
                       (DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType))
      {
        /* @Trace: Dem_SUD_API_11945 */
        Dem_EventStatusNvRamData.InternalDebouneCnt[LddDebounceId] =
            Dem_GssTempCounter[LddDebounceId];
        Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
          DEM_EVMEM_STATUS_DIRTY_NVM);
        Dem_EvMem_TriggerWriteAllBlocks();
      }
    }
    #endif
    /* @Trace: SWS_Dem_01320
     * If DemFFPrestorageInNvm is set to TRUE, the Dem shall store pre-stored
     * freeze-frame data for this event on in Nvm.
     */
    /* @Trace: SWS_Dem_01321
     * If the Dem is configured to store pre-stored freezeframe data in non-
     * volatile memory according to  [SWS_Dem_01320], the Dem shall store the
     * data once and latest during Dem_Shutdown.
     */
    /* @Trace: SWS_Dem_01322
     * If the Dem is configured to store pre-stored freezeframe data in non-
     * volatile memory according to [SWS_Dem_01320], the Dem shall restore the
     * pre-stored data before Dem_Init has returned.
     */
    /* @Trace: SWS_Dem_01323
     * If the Dem is restoring pre-stored data according to [SWS_Dem_01322], the
     * Dem shall only restore this data if it is consistent to the current
     * configuration. If after reprogramming or calibration, the data layout has
     * changed, the Dem shall skip the pre-stored data.
     */
    /* @Trace: Dem_SUD_API_11946 */
    #if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11947 */
    Dem_NumOfPrestoredFFType LddIndex;
    for (LddIndex = DEM_ZERO;
         LddIndex < DEM_MAX_NUMBER_PRESTORED_FF;
         LddIndex++)
    {
      if ((DEM_NUMBER_OF_EVENTS >= Dem_GaaPrestoreBuffer[LddIndex].EventIdRef) &&
          (DEM_NO_EVENT != Dem_GaaPrestoreBuffer[LddIndex].EventIdRef))
      {
        /* @if (DEM_TRUE ==
         *      Dem_Event[Dem_GaaPrestoreBuffer[index].EventIdRef - DEM_ONE].
         *        blFFPrestorageInNvm)*/
        {
          #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
          uint32 LulIndexData;
          /* @Trace: Dem_SUD_API_11942 */
          /* polyspace +2 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
          for (LulIndexData = DEM_ZERO;
               LulIndexData < DEM_SIZE_OF_PRESTORED_FF;
               LulIndexData++)
          {
            /* @Trace: Dem_SUD_API_11950 */
            Dem_NonVolatileData.DataPrestored[LddIndex].data[LulIndexData] =
                Dem_GaaPrestoreBuffer[LddIndex].data[LulIndexData];
          }
          #endif
          Dem_NonVolatileData.EvIdPrestored[LddIndex] =
              Dem_GaaPrestoreBuffer[LddIndex].EventIdRef;
        }
      }
      else
      {
        #if (DEM_SIZE_OF_PRESTORED_FF > DEM_ZERO)
        uint32 LulIndexData;
        /* @Trace: Dem_SUD_API_11949 */
        /* polyspace +2 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        for (LulIndexData = DEM_ZERO;
             LulIndexData < DEM_SIZE_OF_PRESTORED_FF;
             LulIndexData++)
        {
          /* @Trace: Dem_SUD_API_11948 */
          Dem_NonVolatileData.DataPrestored[LddIndex].data[LulIndexData] =
              DEM_SET_BYTE;
        }
        #endif
        Dem_NonVolatileData.EvIdPrestored[LddIndex] = DEM_NO_EVENT;
      }

    }
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
      DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks();
    #endif
    Dem_GucInit = DEM_DEINIT;
  }
}


/*******************************************************************************
** Function Name        : Dem_MainFunction                                    **
**                                                                            **
** Service ID           : 0x55                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                                                                            **
** Timing:              : FIXED_CYCLIC                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
**                        Dem_GucInit                                         **
**                        Dem_GblMilStarted                                   **
**                        Dem_GulTimeSinceMilOn                               **
**                        Dem_GucMilonFlag                                    **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GulDemClearTimeCount                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        Dem_ProcessDebounceTimer                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04069 SRS_BSW_00373
 */
FUNC(void, DEM_CODE) Dem_MainFunction(void)
{
  switch(Dem_GucInit)
  {
    /* main function after Dem is initialieze */
    case DEM_INIT:    
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      Dem_MainFunctionOBD();
      #endif

      #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
      Dem_MainfunctionBswEvents();
      #endif

      Dem_MainfunctionEvents();

      #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
      Dem_ProcessDebounceTimer();
      #endif
      /* @Trace: SWS_Dem_01285
       * The Dem shall process the UDS status asynchronously. This means it
       * is calculated outside the context of the calling Dem_SetEventStatus
       * function.
       */
      Dem_ProcessUDSStatus();
      /* Apply the filter mask and get the number of filtered DTC */

      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      /* @Trace: Dem_SUD_API_12544 */
      for (uint8 LucClientId = DEM_ZERO;
                 LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
                 LucClientId++)
      {
        /* @Trace: Dem_SUD_API_12545 */
        if (Dem_DTCFilterState[LucClientId].dfs_JobAction == DEM_JOB_TRIGGER)
        {
          /* @Trace: Dem_SUD_API_12546 */
          SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
          Dem_DTCFilterState[LucClientId].dfs_JobAction = DEM_JOB_RUNNING;
          SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
          Dem_CountAndStoreFilterDtc(LucClientId);
        }
        #if (DEM_J1939_SUPPORT == STD_ON)
        Dem_J1939MainFunction(LucClientId);
        #endif
      }
      #endif

      /* Dem_EvMem_MainFunctionClearDtc shall be processed before
       * Dem_EvMem_MainFunctionWriteAll to get the valid the result of NvM jobs
       * (Dem_EvMem_GetNvmResult) */
      Dem_EvMem_MainFunctionClearDtc();

      /* Dem_WriteNvData can be called by application during Dem is running */
      Dem_EvMem_MainFunctionWriteAll();

      /* @Trace: SWS_Dem_01303
       * The Dem shall process a call of the Dem_SetWIRStatus asynchronously.
       * This means that the final result is available at a later point in time.
       */
      Dem_ProcessWIRStatus();

      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      Dem_DeactivateMIL();
      #endif

      break;
    /* Dem PostInit is used, Conditions : Dem_ReadNvData shall be invoked by
     * BswM */
    case DEM_READNVDATA:
      /* @Trace: Dem_SUD_API_12542 */
      Dem_EvMem_MainFunctionReadAll();
      break;
    case DEM_DEINIT:
      /* @Trace: Dem_SUD_API_12543 */
      Dem_EvMem_MainFunctionWriteAll();
      break;
    /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause
     * is unreachable. switch-expression */
    default:
      /* @Trace: Dem_SUD_API_12547 */
      /* Do Nothing */
      break;
  }
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
