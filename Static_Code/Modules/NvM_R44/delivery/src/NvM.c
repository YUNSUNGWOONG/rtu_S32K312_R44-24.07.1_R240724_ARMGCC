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
**  SRC-MODULE: NvM.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : API Function Definitions of NVRAM Module                      **
**              NvM_Init                                                      **
**              NvM_SetDataIndex                                              **
**              NvM_GetDataIndex                                              **
**              NvM_SetBlockProtection                                        **
**              NvM_GetErrorStatus                                            **
**              NvM_SetRamBlockStatus                                         **
**              NvM_SetBlockLockStatus                                        **
**              NvM_WriteBlock                                                **
**              NvM_ReadBlock                                                 **
**              NvM_WritePRAMBlock                                            **
**              NvM_ReadPRAMBlock                                             **
**              NvM_RestoreBlockDefaults                                      **
**              NvM_RestorePRAMBlockDefaults                                  **
**              NvM_EraseNvBlock                                              **
**              NvM_CancelWriteAll                                            **
**              NvM_InvalidateNvBlock                                         **
**              NvM_CancelJobs                                                **
**              NvM_ReadAll                                                   **
**              NvM_WriteAll                                                  **
**              NvM_ValidateAll                                               **
**              NvM_FirstInitAll                                              **
**              NvM_MainFunction                                              **
**              NvM_GetVersionInfo                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 0.0.1       06-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
** 1.1.2       12-Aug-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-76>                 **
** 1.2.0       03-Nov-2022    ThuanLD5    Improvement mobilegence             **
**                                          Classic <CP44-869>                **
**                                          <CP44-895> <CP44-955>             **
** 1.3.0       20-Dec-2022    ThuanLD5    Fix MISRA-C violations              **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "Pointer and bound are checked with DET on" */
/* polyspace-begin MISRA2012:11.5 [Not a defect:Low] "Pointer cast is valid" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: NvM_SUD_FILE_001 SRS_BSW_00383 SRS_BSW_00384 */
#include "NvM.h"                            /* NvM header file */
#include "Rte_NvM.h"                        /* Rte_NvM header header file */
#include "NvM_IntTypes.h"
#include "NvM_Globals.h"                    /* Global variables header file */
#include "MemIf.h"                          /* MemIf header file */
#if(STD_ON == NVM_DEMERROR_REPORT)
#include "NvM_Dem_Cfg.h"                    /* Dem header file */
#endif
#include "BswM.h"
#include "Det.h"                            /* Det header file */
#include "BswM_NvM.h"                       /* BswM_NvM header header file */
#include "SchM_NvM.h"                       /* SchM_NvM header file */
#include "NvM_IntFunc.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : NvM_Init                                            **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic NVRAM Manager Initialization      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_InitStatus,               **
**                        NvM_StdQueueBuffer, NvM_ImmQueueBuffer,             **
**                        NvM_ImmFreeIndx, NvM_StdFreeIndx,                   **
**                        NvM_DataBuffer, NvM_StdQueStartPos,                 **
**                        NvM_ImmQueStartPos, NvM_PrevReqImm,                 **
**                        NvM_HighPriorityRequest, NvM_BlkDescTbls,           **
**                        NvM_RamIndex, NvM_RamStatus, NvM_WriteAllRequest,   **
**                        NvM_ReadAllRequest, NvM_ValidateAllRequest,         **
**                        NvM_FirstInitAllRequest, NvM_State, NvM_SubState,   **
**                        NvM_ReadAllState, NvM_WriteAllSubState, NvM_PMCount,**
**                        NvM_FirstBlock, NvM_NotifiedGlobalStatus            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_Mem_08009 SRS_BSW_00414 SRS_Mem_00135 */
/* @Trace: NvM_SUD_DATATYPE_013 SWS_BSW_00047 */
FUNC(void, NVM_CODE) NvM_Init(
  P2CONST(NvM_ConfigType, AUTOMATIC, NVM_APPL_CONST) ConfigPtr)
{
  #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    VAR(uint16, AUTOMATIC) stdIndx1;
    /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 */
    #if((STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
      VAR(uint16, AUTOMATIC) immIndx1;
    #endif
  #endif
    VAR(uint16, AUTOMATIC) indexCnt;
    /* @Trace: NvM_SUD_FUNC_001 */
    NVM_UNUSED(ConfigPtr);

    NvM_DataBuffer = &NvM_DataBufferSource[4U];

  /* if the NVM_API_CONFIG_CLASS is equal to NVM_API_CONFIG_CLASS_1 then
   * the global standard queue variables updating
   */
  /* @Trace: NvM_SUD_FUNC_002 NvM_SUD_MACRO_039 */
  #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    NvM_StdFreeIndx = NVM_SIZE_STANDARD_JOB_QUEUE;
    for(stdIndx1 = NVM_ZERO; stdIndx1 < NVM_SIZE_STANDARD_JOB_QUEUE; stdIndx1++)
    {
      NvM_StdQueueBuffer[stdIndx1].ddBlock_Idx = NVM_ZERO;
    }
    NvM_StdQueStartPos = NVM_ZERO;
    NvM_StdQueEndPos = NVM_ZERO;
    /* Std Queue does not needed to clear */
    /* @Trace: NvM_SUD_MACRO_039 */
    NvM_StdFreeSlotsAvail = NVM_SIZE_STANDARD_JOB_QUEUE;

    /* if the NVM_JOB_PRIORITIZATION is ON and NVM_IMM_JOB_PRIORITY also ON
     * the global immediate queue variables updating
     */
    /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 */
    #if((STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
      /* @Trace: NvM_SUD_MACRO_038 */
      NvM_ImmFreeIndx = NVM_SIZE_IMMEDIATE_JOB_QUEUE;
      for(immIndx1 = NVM_ZERO; immIndx1 < NVM_SIZE_IMMEDIATE_JOB_QUEUE;
        immIndx1++)
      {
        NvM_ImmQueueBuffer[immIndx1].ddBlock_Idx = NVM_ZERO;
      }
      NvM_ImmQueStartPos = NVM_ZERO;
      NvM_ImmQueEndPos = NVM_ZERO;
      /* @Trace: NvM_SUD_MACRO_038 */
      /* Imm Queue does not needed to clear */
      NvM_ImmFreeSlotsAvail = NVM_SIZE_IMMEDIATE_JOB_QUEUE;
      NvM_PrevReqImm = NVM_FALSE;
      NvM_HighPriorityRequest = NVM_FALSE;
    #endif
  #endif

    for(indexCnt = 0; indexCnt < NVM_TOTAL_NUM_OF_NVRAM_BLOCKS; indexCnt++)
    {
      /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
      #if(STD_ON == NVM_DATASET_PRESENT)
        /* @Trace: NvM_SUD_FUNC_003 */
        if(NVM_BLOCK_DATASET == NvM_BlkDescTbls[indexCnt].enBlkMngmntType)
        {
          NvM_RamIndex[indexCnt] = (uint8)NVM_ZERO;
        }
      #endif
      if(NVM_BLOCK_WRITE_PROT == (NvM_BlkDescTbls[indexCnt].usBlkParams & 
        NVM_BLOCK_WRITE_PROT))
      {
        /* @Trace: NvM_SUD_FUNC_004 */
        NvM_RamStatus[indexCnt] |= NVM_WRITE_PROTECT_MASK;
      }
    }
    /* @Trace: NvM_SUD_FUNC_005 */
    NvM_WriteAllRequest = NVM_MULTIBLK_UNREQUESTED;
    NvM_ReadAllRequest = NVM_MULTIBLK_UNREQUESTED;
    #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
      NvM_ValidateAllRequest = NVM_MULTIBLK_UNREQUESTED;
    #endif
    #if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
      NvM_FirstInitAllRequest = NVM_MULTIBLK_UNREQUESTED;
    #endif
    NvM_State = NVM_IDLE;
    NvM_SubState = NVM_SUB_IDLE;
    NvM_ReadAllState = NVM_IDLE;
    NvM_WriteAllSubState = NVM_WRITE_ALL_IDLE;
    NvM_NotifiedGlobalStatus = NVM_REQ_OK;
    NvM_FirstBlock = NVM_RE_ORIGINAL_FIRST;

    NvM_PMCount = (uint8)NVM_ZERO;

    /* Set flag to indicate initialization is complete */
    NvM_InitStatus = NVM_TRUE;
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_WriteBlock                                      **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId,     **
**                        NvM_SrcPtr and Service Id to 'Write' the            **
**                        RAM block data to its corresponding NV block.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, NvM_SrcPtr                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_RamIndex,       **
**                        NvM_PMCount                                         **
**                        Function(s) invoked    : Det_ReportError()          **
**                        Dem_SetEventStatus(), NvM_ImmQueueWrite(),          **
**                        NvM_StdQueueWrite(), BswM_NvM_CurrentBlockMode(),   **
**                        Det_ReportRuntimeError(), BswM_RequestMode(),       **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_LIBS_08535 SRS_Mem_00017 SRS_Mem_00038 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
/* @Trace: NvM_SUD_DATATYPE_006 */
FUNC(Std_ReturnType, NVM_CODE) NvM_WriteBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint8, AUTOMATIC) ramIndex;
  #endif
    VAR(NvM_JobQueue, AUTOMATIC) varJobQueue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
    ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_240 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_241 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_242 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of Block comment - 2 */
          /* @Trace: NvM_SUD_FUNC_489 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);

          /* Start of Block comment- 2 */
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            ramIndex = NvM_RamIndex[BlockId];
          #endif

          /*
           * If the permanent RAM block is not configured, NULL pointer is passed
           * as parameter and Mirror is disabled report error to DET
           */
            if(
              /* @Trace: NvM_SUD_MACRO_034 */
              #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                (NULL_PTR == (ptrBlkDescTbl->pRamBlkData)) &&
              #endif
                (NULL_PTR == NvM_SrcPtr)
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                && (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE != 
                (ptrBlkDescTbl->usBlkParams & 
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
              #endif
            )
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_243 */
                varDetErrorId = NVM_E_PARAM_ADDRESS;
              #endif
            }
            else
            { /* Start of Block comment - 3 */
              /* @Trace: NvM_SUD_FUNC_244 */
              ptrRamStatus = &NvM_RamStatus[BlockId];
              /* Check if the block is write protected */
              if(NVM_WRITE_PROTECT_MASK == 
                (*ptrRamStatus & NVM_WRITE_PROTECT_MASK))
              {
                /* @Trace: NvM_SUD_MACRO_021 */
                #if(STD_ON == NVM_DEMERROR_REPORT)
                  /* @Trace: NvM_SUD_FUNC_245 */
                  /* @Trace: NvM_SUD_MACRO_003 */
                  /* Report the write protected to DEM */
                  (void)Dem_SetEventStatus(NVM_E_WRITE_PROTECTED, 
                    DEM_EVENT_STATUS_FAILED);
                #endif
              }
              /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
              /* Check if index is not pointing to ROM area in case of Dataset block */
              #if(STD_ON == NVM_DATASET_PRESENT)
                /* if DataIndex is pointing to ROM */
                else if(
                  (NVM_BLOCK_DATASET == ptrBlkDescTbl->enBlkMngmntType) &&
                  (ptrBlkDescTbl->ucNumOfNvBlks <= ramIndex)
                )
                {
                  /* @Trace: NvM_SUD_FUNC_246 */
                }
              #endif
              /* Report DET error if block is locked */
                else if(NVM_LOCK_RAM_MASK == 
                  (*(ptrRamStatus) & NVM_LOCK_RAM_MASK))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_247 */
                    varDetErrorId = NVM_E_BLOCK_LOCKED;
                  #endif
                }
              /*
               * Report DET error whenever a job is pending and ReadAll is not taken
               * for processing and whenever ReadAll is in progress and block is
               * configured to be of standard type
               */
                else if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
                {
                  /*
                   * If the request for the block is present in queue or currently in
                   * progress, report error to DET
                   */
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_492 */
                    varDetErrorId = NVM_E_BLOCK_PENDING;
                  #endif
                }
                /* If the parameter NVM_WRITE_BLOCK_ONCE = NVM_TRUE, report error to DET */
                else if((NVM_WRITE_BLOCK_ONCE == (ptrBlkDescTbl->usBlkParams & 
                  NVM_WRITE_BLOCK_ONCE)) && (NVM_CHECK_READ_PRIOR != 
                  (*ptrRamStatus & NVM_CHECK_READ_PRIOR)))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_248 */
                    varDetErrorId = NVM_E_WRITE_ONCE_STATUS_UNKNOWN;
                  #endif
                }
                else
                { /* Start of Block comment - 5 */
                  /* @Trace: NvM_SUD_FUNC_249 */
                  /* Load the Service Id, Block Id and RAM buffer pointer */
                  varJobQueue.ucService_Id = NVM_WRITEBLOCK_SID;
                  varJobQueue.ddBlock_Idx = BlockId;
                  varJobQueue.pTempRamBlkData = (uint8 *)NvM_SrcPtr;  /* polyspace MISRA2012:11.8 [Not a defect:Low] "NvM_SrcPtr cast to avoid complexity" */
                  /* @Trace: NvM_SUD_MACRO_025 */
                  #if(STD_ON == NVM_JOB_PRIORITIZATION)
                    /* @Trace: NvM_SUD_FUNC_250 */
                    varJobQueue.ucPriority = ptrBlkDescTbl->ucBlkJobPriority;
                  #endif
                  /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 */
                  #if((STD_ON == NVM_JOB_PRIORITIZATION) && \
                    (STD_ON == NVM_IMM_JOB_PRIORITY))
                    if(NVM_IMM_PRIORITY == (ptrBlkDescTbl->ucBlkJobPriority))
                    {
                      /*
                       * Queue the request in immediate Queue, if block 
                       * is configured of type immediate priority
                       */
                      /* @Trace: NvM_SUD_FUNC_251 */
                      returnValue = NvM_ImmQueueWrite(&varJobQueue);
                    }
                    else
                  #endif
                  /* @(NVM_JOB_PRIORITIZATION==STD_ON) &&(NVM_IMM_JOB_PRIORITY==STD_ON) */
                    {
                      /*
                       * Queue the request in Standard Queue, if block is configured of
                       * type standard priority or if Prioritization is disabled
                       */
                      /* @Trace: NvM_SUD_FUNC_252 */
                      returnValue = NvM_StdQueueWrite(&varJobQueue);
                    }

                  /* Check if the queue write is not successful */
                    if(E_NOT_OK == returnValue)
                    {
                      /* @Trace: NvM_SUD_FUNC_253 */
                      /* The run-time error NVM_E_QUEUE_FULL shall be reported to Det */
                      (void)Det_ReportRuntimeError(
                        NVM_MODULE_ID, NVM_INSTANCE_ID,
                        NVM_WRITEBLOCK_SID, NVM_E_QUEUE_FULL);
                    }
                    else if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                      (ptrBlkDescTbl->usBlkParams & 
                      NVM_BSWM_BLOCK_STATUS_INFORMATION))
                    {
                      /* @Trace: NvM_SUD_FUNC_254 */
                      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                    }
                    else
                    {
                    }
                } /* end of Block comment - 5 */
            } /* end of Block comment - 3 */

            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount--;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* end of Block comment - 2 */
        /* Report error to DET */
        /* @Trace: NvM_SUD_FUNC_255 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_WRITEBLOCK_SID, varDetErrorId);
        }
      #endif
    } /* end else part of if(NVM_ONE == BlockId) */
  /* Inform the BswM about the accepted single block operation as being pending */
    return(returnValue);
}

#endif  /*(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_WritePRAMBlock                                  **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId,     **
**                        Service to copy the data of the RAM block           **
**                        to its corresponding permanent RAM block.           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_RamIndex,       **
**                        NvM_PMCount                                         **
**                        Function(s) invoked    : Det_ReportError()          **
**                        Dem_SetEventStatus(), NvM_ImmQueueWrite(),          **
**                        NvM_StdQueueWrite(), BswM_NvM_CurrentBlockMode(),   **
**                        Det_ReportRuntimeError(), BswM_RequestMode(),       **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_LIBS_08535 SRS_Mem_00017 SRS_Mem_00038 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_WritePRAMBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint8, AUTOMATIC) ramIndex;
  #endif
    VAR(NvM_JobQueue, AUTOMATIC) varJobQueue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
    ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_256 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_257 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_258 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of Block comment - 2 */
          /* @Trace: NvM_SUD_FUNC_490 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          /* Start of Block comment- 2 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            ramIndex = NvM_RamIndex[BlockId];
          #endif
          /*
           * If the permanent RAM block is not configured, NULL pointer is passed
           * as parameter and Mirror is disabled report error to DET
           */
            if(
              /* @Trace: NvM_SUD_MACRO_034 */
              #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                (NULL_PTR == (ptrBlkDescTbl->pRamBlkData)) &&
              #endif
                (NVM_TRUE == NVM_TRUE)
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                && (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE != 
                (ptrBlkDescTbl->usBlkParams & 
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
              )
              #endif
            )
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_259 */
                varDetErrorId = NVM_E_PARAM_ADDRESS;
              #endif
            }
            else
            { /* Start of Block comment - 3 */
              ptrRamStatus = &NvM_RamStatus[BlockId];

              /* Check if the block is write protected */
              if(NVM_WRITE_PROTECT_MASK == 
                (*ptrRamStatus & NVM_WRITE_PROTECT_MASK))
              {
                /* @Trace: NvM_SUD_MACRO_021 */
                #if(STD_ON == NVM_DEMERROR_REPORT)
                  /* @Trace: NvM_SUD_FUNC_260 */
                  /* Report the write protected to DEM */
                  (void)Dem_SetEventStatus(
                    NVM_E_WRITE_PROTECTED, DEM_EVENT_STATUS_FAILED);
                #endif
                  returnValue = E_NOT_OK;
              }
              /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
              /* Check if index is not pointing to ROM area in case of Dataset block */
              #if(STD_ON == NVM_DATASET_PRESENT)
                /* if DataIndex is pointing to ROM */
                else if(
                  (NVM_BLOCK_DATASET == ptrBlkDescTbl->enBlkMngmntType) &&
                  (ptrBlkDescTbl->ucNumOfNvBlks <= ramIndex)
                )
                {
                  /* @Trace: NvM_SUD_FUNC_261 */
                }
              #endif
                /* Report DET error if block is locked */
                else if(NVM_LOCK_RAM_MASK == 
                  (*(ptrRamStatus) & NVM_LOCK_RAM_MASK))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_262 */
                    varDetErrorId = NVM_E_BLOCK_LOCKED;
                  #endif
                }
              /*
               * Report DET error whenever a job is pending and ReadAll is not taken
               * for processing and whenever ReadAll is in progress and block is
               * configured to be of standard type
               */
                else if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
                {
                  /*
                   * If the request for the block is present in queue or 
                   * currently in progress, report error to DET
                   */
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_493 */
                    varDetErrorId = NVM_E_BLOCK_PENDING;
                  #endif
                }
              /* If the parameter NVM_WRITE_BLOCK_ONCE = NVM_TRUE, report error to DET */
                else if((NVM_WRITE_BLOCK_ONCE == (ptrBlkDescTbl->usBlkParams & 
                  NVM_WRITE_BLOCK_ONCE)) && (NVM_CHECK_READ_PRIOR != 
                  (*ptrRamStatus & NVM_CHECK_READ_PRIOR)))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_263 */
                    varDetErrorId = NVM_E_WRITE_ONCE_STATUS_UNKNOWN;
                  #endif
                }
                else
                { /* Start of Block comment - 5 */
                  /* @Trace: NvM_SUD_FUNC_264 */
                  /* Load the Service Id, Block Id and RAM buffer pointer */
                  varJobQueue.ucService_Id = NVM_WRITEPRAMBLOCK_SID;
                  varJobQueue.ddBlock_Idx = BlockId;
                  varJobQueue.pTempRamBlkData = (uint8*)NULL_PTR;
                  /* @Trace: NvM_SUD_MACRO_025 */
                  #if(STD_ON == NVM_JOB_PRIORITIZATION)
                    /* @Trace: NvM_SUD_FUNC_265 */
                    varJobQueue.ucPriority = ptrBlkDescTbl->ucBlkJobPriority;
                  #endif
                  /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 */
                  #if((STD_ON == NVM_JOB_PRIORITIZATION) && \
                    (STD_ON == NVM_IMM_JOB_PRIORITY))
                    if(NVM_IMM_PRIORITY == (ptrBlkDescTbl->ucBlkJobPriority))
                    {
                      /*
                       * Queue the request in immediate Queue, if block is 
                       * configured of type immediate priority
                       */
                      /* @Trace: NvM_SUD_FUNC_266 */
                      returnValue = NvM_ImmQueueWrite(&varJobQueue);
                    }
                    else
                  #endif
                  /* @(NVM_JOB_PRIORITIZATION==STD_ON) &&(NVM_IMM_JOB_PRIORITY==STD_ON) */
                    {
                      /*
                       * Queue the request in Standard Queue, if block is configured of
                       * type standard priority or if Prioritization is disabled
                       */
                      /* @Trace: NvM_SUD_FUNC_267 */
                      returnValue = NvM_StdQueueWrite(&varJobQueue);
                    }

                  /* Check if the queue write is not successful */
                    if(E_NOT_OK == returnValue)
                    {
                      /* @Trace: NvM_SUD_FUNC_268 */
                      /* The run-time error NVM_E_QUEUE_FULL shall be reported to Det */
                      (void)Det_ReportRuntimeError(
                        NVM_MODULE_ID, NVM_INSTANCE_ID,
                        NVM_WRITEPRAMBLOCK_SID, NVM_E_QUEUE_FULL);
                    }
                    else if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                      (ptrBlkDescTbl->usBlkParams & 
                      NVM_BSWM_BLOCK_STATUS_INFORMATION))
                    {
                      /* @Trace: NvM_SUD_FUNC_269 */
                      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                    }
                    else
                    {
                    }
                } /* end of Block comment - 5 */
            } /* end of Block comment - 3 */

            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount--;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* end of Block comment - 2 */
        /* @Trace: NvM_SUD_FUNC_270 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_WRITEPRAMBLOCK_SID, varDetErrorId);
        }
      #endif
    }
    /* Inform the BswM about the accepted single block operation as being pending */
    return(returnValue);
}

#endif  /*(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_ValidateAll                                     **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Initiates a multi block validation request          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Void                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus             **
**                        NvM_RamStatus, NvM_PMCount, NvM_ValidateAllRequest  **
**                                                                            **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        BswM_RequestMode(), BswM_NvM_CurrentJobMode()       **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00137 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(void, NVM_CODE) NvM_ValidateAll(void)
{
  /* @Trace: NvM_SUD_MACRO_043 */
  #if(0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS)
    P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) ptrRamStatus;
    VAR(uint16, AUTOMATIC) blockId;
  #endif
  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_FALSE == NvM_InitStatus)
    {
      /* @Trace: NvM_SUD_FUNC_118 */
      /* Report non initialization */
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_VALIDATEALL_SID, NVM_E_UNINIT);
    }
    else
  #endif
    { /* Start of block commend 1 */
      /* @Trace: NvM_SUD_FUNC_119 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount++;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                      (BswM_ModeType)NVM_LOWPOWER_PREVENT);

      if(NVM_MULTIBLK_UNREQUESTED == NvM_ValidateAllRequest)
      {
        /* @Trace: NvM_SUD_MACRO_043 */
        #if(0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS)
          for(blockId = NVM_ZERO; blockId < 
            NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS; blockId++)
          {
            ptrRamStatus = &NvM_RamStatus[NvM_ValidateAllBlocks[blockId]];
            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            /* Update the RAM block status to 'Valid and Changed' */
            *ptrRamStatus = ((*(ptrRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
              NVM_VALID_CHANGED);
            /* Invoke function to disable data protection */
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          }
        #endif
          /* @Trace: NvM_SUD_FUNC_120 */
          NvM_ValidateAllRequest = NVM_MULTIBLK_REQUESTED;
          NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_PENDING);
        #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
          /* @Trace: NvM_SUD_FUNC_121 */
          (void)BswM_NvM_CurrentJobMode(NVM_VALIDATE_ALL, NVM_REQ_PENDING);
        #endif
      } /* @End of if(NvM_ValidateAllRequest == NVM_MULTIBLK_UNREQUESTED) */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount--;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    } /* End of block commend 1 */
} /* End of function body */

#endif /*(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name      : NvM_GetVersionInfo                                    **
**                                                                            **
** Service ID         : 0x0F                                                  **
**                                                                            **
** Description        : This function returns the version information of      **
**                      NvM module.                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** InputParameters(in): None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : versioninfo                                           **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Precondition       : NA                                                    **
**                                                                            **
** Remarks            : Global Variable(s)     : None                         **
**                                                                            **
**                      Function(s) invoked    : Det_ReportError              **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 NvM_SUD_MACRO_045 */
#if(STD_ON == NVM_VERSION_INFO_API)
/* @Trace: NvM_SUD_DATATYPE_007 */
FUNC(void, NVM_CODE) NvM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) versioninfo)
{
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NULL_PTR == versioninfo)
    {
      /* @Trace: NvM_SUD_FUNC_006 */
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_GETVERSIONINFO_SID, NVM_E_PARAM_POINTER);
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_FUNC_007 */
      (versioninfo->vendorID) = NVM_VENDOR_ID;
      (versioninfo->moduleID) = NVM_MODULE_ID;
      (versioninfo->sw_major_version) = NVM_SW_MAJOR_VERSION;
      (versioninfo->sw_minor_version) = NVM_SW_MINOR_VERSION;
      (versioninfo->sw_patch_version) = NVM_SW_PATCH_VERSION;
    }
} /* End of function body */

#endif  /* (STD_ON == NVM_VERSION_INFO_API) */

/*******************************************************************************
** Function Name        : NvM_SetBlockLockStatus                              **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : Service for setting the lock status of a permanent  **
**                        RAM block of an NVRAM block                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, BlockLocked                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus                      **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_08546 SRS_Mem_08014 */
FUNC(void, NVM_CODE) NvM_SetBlockLockStatus(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(boolean, AUTOMATIC) BlockLocked)
{
  /* @Trace: NvM_SUD_MACRO_007 NvM_SUD_MACRO_034 */
  #if((STD_ON == NVM_DEV_ERROR_DETECT) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) || \
    (STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS))
    P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  #endif
  /* @Trace: NvM_SUD_MACRO_034 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) || \
    (STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
    P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  #endif
  /* @Trace: NvM_SUD_MACRO_007 */
  #if((STD_ON == NVM_DEV_ERROR_DETECT) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
    VAR(uint16, AUTOMATIC) blkParams;
  #endif
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_036 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_037 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_038 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of block comment 1 */
          /* @Trace: NvM_SUD_FUNC_478 NvM_SUD_MACRO_007 NvM_SUD_MACRO_034 */
          #if((STD_ON == NVM_DEV_ERROR_DETECT) || \
            (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) \
            || (STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS))
            ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          #endif
          /* @Trace: NvM_SUD_MACRO_007 */
          #if((STD_ON == NVM_DEV_ERROR_DETECT) || \
            (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
            blkParams = ptrBlkDescTbl->usBlkParams;
          #endif
          /* @Trace: NvM_SUD_MACRO_007 */
          #if(STD_ON == NVM_DEV_ERROR_DETECT)
            /* If the parameter NVM_WRITE_BLOCK_ONCE == TRUE
            report error to the DET */
            if(NVM_WRITE_BLOCK_ONCE == (blkParams & NVM_WRITE_BLOCK_ONCE))
            {
              /* @Trace: NvM_SUD_FUNC_039 */
              varDetErrorId = NVM_E_BLOCK_CONFIG;
            }
            else
          #endif
            { /* Start of block comment 2 */
              /* Check Block is pending*/
              if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
              {
                /* @Trace: NvM_SUD_MACRO_007 */
                #if(STD_ON == NVM_DEV_ERROR_DETECT)
                  /* @Trace: NvM_SUD_FUNC_040 */
                  varDetErrorId = NVM_E_BLOCK_PENDING;
                #endif
              }
              /* @Trace: NvM_SUD_MACRO_034 */
              /* Check permanent ram or explicit synchronous */
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) || \
                (STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                else if(
                  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                    (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == (blkParams & 
                    NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
                  #endif
                  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) && \
                    (STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                    ||
                  #endif
                  #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                    (NULL_PTR != ptrBlkDescTbl->pRamBlkData)
                  #endif
                )
                { /* Start of block comment 3 */
                  ptrRamStatus = &NvM_RamStatus[BlockId];
                  /* Invoke function to enable data protection */
                  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                  /* @Trace: NvM_SUD_FUNC_041 */
                  if(NVM_TRUE == BlockLocked)
                  {
                    /* Lock the permanent RAM block of an NVRAM block */
                    *(ptrRamStatus) |= NVM_LOCK_RAM_MASK;
                  }
                  else
                  {
                    /* UnLock the permanent RAM block of an NVRAM block */
                    *(ptrRamStatus) &= NVM_UNLOCK_RAM_MASK;
                  }
                  /* Invoke function to disable data protection */
                  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                } /* End of block comment 3 */
                else
                {
                  /* Nothing */
                }
              #else
                NVM_UNUSED(BlockLocked);
              #endif
            } /* End of block comment 2 */
        } /* End of block comment 1 */
        /* @Trace: NvM_SUD_FUNC_042 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_SETBLOCKLOCKSTATUS_SID, varDetErrorId);
        }
      #endif
    }
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_EraseNvBlock                                    **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId and  **
**                        Service Id to 'Erase' the NV block data             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NVRAM Manager should be initialized.                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus             **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_PMCount,        **
**                        NvM_RamIndex                                        **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        Dem_SetEventStatus(), NvM_StdQueueWrite(),          **
**                        Det_ReportRuntimeError(), BswM_RequestMode(),       **
**                        BswM_NvM_CurrentBlockMode(),                        **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00038 SRS_Mem_08015 SRS_Mem_08544 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_EraseNvBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(NvM_JobQueue, AUTOMATIC) varJobQueue;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint8, AUTOMATIC) ramIndex;
  #endif
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_148 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        /* @Trace: NvM_SUD_MACRO_025 */
        #if(STD_ON == NVM_JOB_PRIORITIZATION)
          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
        #endif
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_149 */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_150 */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        /* return E_NOT_OK when DevErrorDetect enabled and the referenced NVRAM block
         * is configured with standard priority
         */
        /* @Trace: NvM_SUD_MACRO_025 */
        #if(STD_ON == NVM_JOB_PRIORITIZATION)
          else if(NVM_IMM_PRIORITY != ptrBlkDescTbl->ucBlkJobPriority)
          {
            /* @Trace: NvM_SUD_FUNC_151 */
            varDetErrorId = NVM_E_BLOCK_CONFIG;
          }
        #endif /* NVM_JOB_PRIORITIZATION == STD_ON */
          else
      #endif
          {
            /* Start of Block comment - 2 */
            /* @Trace: NvM_SUD_FUNC_486 */
            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount++;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
            BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                            (BswM_ModeType)NVM_LOWPOWER_PREVENT);
            /* @Trace: NvM_SUD_MACRO_007 NvM_SUD_MACRO_025 */
            #if((STD_OFF == NVM_DEV_ERROR_DETECT) || \
              (STD_OFF == NVM_JOB_PRIORITIZATION))
              ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
            #endif
            ptrRamStatus = &NvM_RamStatus[BlockId];
            /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
            #if(STD_ON == NVM_DATASET_PRESENT)
              ramIndex = NvM_RamIndex[BlockId];
            #endif
              /*
               * Check if the block is write protected or DataIndex is pointing to ROM
               */
              if(NVM_WRITE_PROTECT_MASK == (*(ptrRamStatus) & 
                NVM_WRITE_PROTECT_MASK))
              {
                /* @Trace: NvM_SUD_MACRO_021 */
                #if(STD_ON == NVM_DEMERROR_REPORT)
                  /* @Trace: NvM_SUD_FUNC_152 */
                  /* Report the write protected to DEM */
                  (void)Dem_SetEventStatus(NVM_E_WRITE_PROTECTED, 
                    DEM_EVENT_STATUS_FAILED);
                #endif
              }
            /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
            /* If a ROM block of a dataset NVRAM block is referenced, report to DET */
            #if(STD_ON == NVM_DATASET_PRESENT)
              else if((NVM_BLOCK_DATASET == (ptrBlkDescTbl->enBlkMngmntType)) &&
                (ptrBlkDescTbl->ucNumOfNvBlks <= ramIndex))
              {
                /* @Trace: NvM_SUD_FUNC_153 */
              } 
            #endif /* NVM_DATASET_PRESENT == STD_ON */
              else
              { /* Start of block comment 3 */
                /* Report DET error if block is locked */
                if(NVM_LOCK_RAM_MASK == (*(ptrRamStatus) & NVM_LOCK_RAM_MASK))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_154 */
                    varDetErrorId = NVM_E_BLOCK_LOCKED;
                  #endif
                }
                else if((NVM_WRITE_BLOCK_ONCE == (ptrBlkDescTbl->usBlkParams & 
                  NVM_WRITE_BLOCK_ONCE)) && (NVM_CHECK_READ_PRIOR != 
                  (*ptrRamStatus & NVM_CHECK_READ_PRIOR)))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_155 */
                    varDetErrorId = NVM_E_WRITE_ONCE_STATUS_UNKNOWN;
                  #endif
                }
                else if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
                {
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_156 */
                    varDetErrorId = NVM_E_BLOCK_PENDING;
                  #endif
                }
                else
                { /* Start of block comment 4 */
                  /* Load the Service Id, Block Id and RAM buffer pointer */
                  /* @Trace: NvM_SUD_FUNC_157 */
                  varJobQueue.ucService_Id = NVM_ERASENVBLOCK_SID;
                  varJobQueue.ddBlock_Idx = BlockId;
                  varJobQueue.pTempRamBlkData = (uint8*)NULL_PTR;
                  /* @Trace: NvM_SUD_MACRO_025 */
                  #if (STD_ON == NVM_JOB_PRIORITIZATION)
                    /* @Trace: NvM_SUD_FUNC_158 */
                    varJobQueue.ucPriority = 
                      NvM_BlkDescTbls[BlockId].ucBlkJobPriority;
                  #endif
                  /* @Trace: NvM_SUD_FUNC_159 */
                  /* Queue the request in standard Queue */
                  returnValue = NvM_StdQueueWrite(&varJobQueue);

                  /* Inform the BswM about the accepted single block operation as being pending */
                  if(E_OK == returnValue)
                  {
                    if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                    (NvM_BlkDescTbls[BlockId].usBlkParams &
                    NVM_BSWM_BLOCK_STATUS_INFORMATION))
                    {
                      /* @Trace: NvM_SUD_FUNC_161 */
                      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                    }
                  }
                  else
                  {
                    /* @Trace: NvM_SUD_FUNC_160 */
                    /* Report run-time error (QUEUE FULL) to the DET */
                    (void)Det_ReportRuntimeError(
                      NVM_MODULE_ID, NVM_INSTANCE_ID,
                      NVM_ERASENVBLOCK_SID, NVM_E_QUEUE_FULL);
                  }
                } /* End of block comment 4 */
              } /* End of block comment 3 */
              SchM_Enter_NvM_RAM_STATUS_PROTECTION();
              NvM_PMCount--;
              SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          } /* @End of block comment 2 */
          /* @Trace: NvM_SUD_FUNC_162 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_ERASENVBLOCK_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */
#endif /* NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 */

/*******************************************************************************
** Function Name      : NvM_SetBlockProtection                                **
**                                                                            **
** Service ID         : 0x03                                                  **
**                                                                            **
** Description        : This function enables/disables the write block        **
**                      protection bit in the RAM block attribute/error       **
**                      /status field.                                        **
**                      This function is available only if API                **
**                      Configuration Class 3 is enabled.                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** Input Parameters   : BlockId, ProtectionEnabled                            **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : returnValue                                           **
**                                                                            **
** Precondition       : NVRAM Manager should be initialized.                  **
**                                                                            **
** Remarks            : Global Variable(s) : NvM_InitStatus,                  **
**                      NvM_RamStatus, NvM_BlkDescTbls                        **
**                      Function(s) invoked: Det_ReportError(),               **
**                      SchM_Enter_NvM_RAM_STATUS_PROTECTION(),               **
**                      SchM_Exit_NvM_RAM_STATUS_PROTECTION()                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00127 */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_SetBlockProtection(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(boolean, AUTOMATIC) ProtectionEnabled)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(uint16, AUTOMATIC) blkParams;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_066 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        /* check non initialization */
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_067 */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* Check BlockId is out of range */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_068 */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of block comment 1 */
          /* @Trace: NvM_SUD_FUNC_481 */
          ptrRamStatus = &NvM_RamStatus[BlockId];
          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          blkParams = ptrBlkDescTbl->usBlkParams;
          /* report if Block is locked */
          if(NVM_LOCK_RAM_MASK == (*(ptrRamStatus) & NVM_LOCK_RAM_MASK))
          {
            /* @Trace: NvM_SUD_MACRO_007 */
            #if(STD_ON == NVM_DEV_ERROR_DETECT)
              /* @Trace: NvM_SUD_FUNC_069 */
              varDetErrorId = NVM_E_BLOCK_LOCKED;
            #endif
          }
          /* report if NVRAM Block is configured with NvMWriteBlockOnce == TRUE */
          else if(NVM_WRITE_BLOCK_ONCE == (blkParams & NVM_WRITE_BLOCK_ONCE))
          {
            /* @Trace: NvM_SUD_MACRO_007 */
            #if(STD_ON == NVM_DEV_ERROR_DETECT)
              /* @Trace: NvM_SUD_FUNC_070 */
              varDetErrorId = NVM_E_BLOCK_CONFIG;
            #endif
          }
          else
          { /* Start of block comment 2 */
            /* Check Block is pending */
            if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_071 */
                varDetErrorId = NVM_E_BLOCK_PENDING;
              #endif
            }
            else 
            { /* Start of block comment 3 */
              /* @Trace: NvM_SUD_FUNC_072 */
              if(NVM_TRUE == ProtectionEnabled)
              {
                /* Invoke function to enable data protection */
                SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                /*
                 * Activate write protection by setting write lock bit in
                 * administrative part of RAM block
                 */
                *(ptrRamStatus) |= NVM_WRITE_PROTECT_MASK;
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
              }
              else
              {
                SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                *(ptrRamStatus) &= NVM_NOT_WRITE_PROTECT_MASK;
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
              }
              returnValue = E_OK;
            } /* End of block comment 3 */
          } /* End of block comment 2 */
        } /* End of block comment 1 */

      /* @Trace: NvM_SUD_FUNC_073 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_SETBLOCKPROTECTION_SID, varDetErrorId); 
        }
      #endif
    }
    return(returnValue);
} /* End of function body */
#endif /* NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 */

/*******************************************************************************
** Function Name        : NvM_InvalidateNvBlock                               **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId      **
**                        and Service Id to 'Invalidate' the NV block data.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM  should be initialized                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_RamIndex,       **
**                        NvM_PMCount                                         **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        BswM_NvM_CurrentBlockMode(), Dem_SetEventStatus(),  **
**                        Det_ReportRuntimeError(), BswM_RequestMode(),       **
**                        NvM_StdQueueWrite(),                                **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00038 SRS_Mem_08011 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_InvalidateNvBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint8, AUTOMATIC) ramIndex;
  #endif
    P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
    P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
    VAR(NvM_JobQueue, AUTOMATIC) varJobQueue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_122 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_123 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_124 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of block comment 1 */
          /* @Trace: NvM_SUD_FUNC_485 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
            (BswM_ModeType)NVM_LOWPOWER_PREVENT);

          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            ramIndex = NvM_RamIndex[BlockId];
          #endif
            ptrRamStatus = &NvM_RamStatus[BlockId];
          /* check block protect */
            if(NVM_WRITE_PROTECT_MASK == 
              (*(ptrRamStatus) & NVM_WRITE_PROTECT_MASK))
            {
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                /* @Trace: NvM_SUD_FUNC_125 */
                /* report to the DEM */
                (void)Dem_SetEventStatus(
                  NVM_E_WRITE_PROTECTED, DEM_EVENT_STATUS_FAILED);
              #endif
            }
          /* check if a ROM block of 
           * a dataset NVRAM block is referenced by the BlockId parameter 
           */
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            else if((NVM_BLOCK_DATASET == (ptrBlkDescTbl->enBlkMngmntType)) &&
              (ptrBlkDescTbl->ucNumOfNvBlks <= ramIndex))
            {
              /* @Trace: NvM_SUD_FUNC_126 */
            }
          #endif
          /* report if Block is locked */
            else if(NVM_LOCK_RAM_MASK == (*(ptrRamStatus) & NVM_LOCK_RAM_MASK))
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_127 */
                varDetErrorId = NVM_E_BLOCK_LOCKED;
              #endif
            }
            else if((NVM_WRITE_BLOCK_ONCE == (ptrBlkDescTbl->usBlkParams & 
              NVM_WRITE_BLOCK_ONCE)) && (NVM_CHECK_READ_PRIOR != 
              (*ptrRamStatus & NVM_CHECK_READ_PRIOR)))
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_128 */
                varDetErrorId = NVM_E_WRITE_ONCE_STATUS_UNKNOWN;
              #endif
            }
            /* check block is pending */
            else if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_129 */
                varDetErrorId = NVM_E_BLOCK_PENDING;
              #endif
            }
            else
            { /* Start of block comment 2 */
              /* @Trace: NvM_SUD_FUNC_130 */
              /* Load the Service Id, Block Id and RAM buffer pointer */
              varJobQueue.ucService_Id = NVM_INVALIDATENVBLOCK_SID;
              varJobQueue.ddBlock_Idx = BlockId;
              varJobQueue.pTempRamBlkData = (uint8*) NULL_PTR;
              /* @Trace: NvM_SUD_MACRO_025 */
              #if (STD_ON == NVM_JOB_PRIORITIZATION)
                /* @Trace: NvM_SUD_FUNC_131 */
                varJobQueue.ucPriority = 
                  NvM_BlkDescTbls[BlockId].ucBlkJobPriority;
              #endif
                /* @Trace: NvM_SUD_FUNC_132 */
                /* Queue the request in standard Queue */
                returnValue = NvM_StdQueueWrite(&varJobQueue);

              /* Inform the BswM about the accepted single block operation as being pending */
                if(E_OK == returnValue)
                {
                  if(NVM_BSWM_BLOCK_STATUS_INFORMATION == (
                    NvM_BlkDescTbls[BlockId].usBlkParams &
                    NVM_BSWM_BLOCK_STATUS_INFORMATION))
                  {
                    /* @Trace: NvM_SUD_FUNC_134 */
                    BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                  }
                }
                /* report if the queue write is not successful */
                else
                {
                  /* @Trace: NvM_SUD_FUNC_133 */
                  /* Report the queue overflow runtime error to DET */
                  (void)Det_ReportRuntimeError(
                    NVM_MODULE_ID, NVM_INSTANCE_ID,
                    NVM_INVALIDATENVBLOCK_SID, NVM_E_QUEUE_FULL);
                }
            } /* End of block comment 2 */
            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount--;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* End of block comment 1 */
      /* @Trace: NvM_SUD_FUNC_135 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_INVALIDATENVBLOCK_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */
#endif /* NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3 */

/*******************************************************************************
** Function Name        : NvM_CancelJobs                                      **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : Service to cancel all jobs pending for a NV block   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_PMCount         **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_ImmQueueCancel(), NvM_StdQueueCancel()          **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        BswM_NvM_CurrentBlockMode(), BswM_RequestMode()     **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_08558 SRS_Mem_08560 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_CancelJobs(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_326 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_327 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_328 */
          /* assign errorId to  invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif /* NVM_DEV_ERROR_DETECT == STD_ON */
        { /* Start of block comment 1 */
          /* @Trace: NvM_SUD_FUNC_491 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);

          ptrRamStatus = &NvM_RamStatus[BlockId];
          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          /* Check block is pending */
          if(NVM_REQ_PENDING != NVM_GET_JOB_RESULT(BlockId))
          {
          }
          else
          { /* Start of block comment 2 */
            /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 */
            #if((STD_ON == NVM_JOB_PRIORITIZATION) && \
              (STD_ON == NVM_IMM_JOB_PRIORITY))
              if(NVM_IMM_PRIORITY == (ptrBlkDescTbl->ucBlkJobPriority))
              {
                /*
                 * Cancel the request in immediate Queue, if block is configured of
                 * type immediate priority
                 */
                /* @Trace: NvM_SUD_FUNC_329 */
                returnValue = NvM_ImmQueueCancel(BlockId);
              }

              if(E_NOT_OK == returnValue)
            #endif
              {
                /*
                 * Cancel the request in Standard Queue, if block is configured of
                 * type standard priority or if Prioritization is disabled
                 */
                /* @Trace: NvM_SUD_FUNC_330 */
                returnValue = NvM_StdQueueCancel(BlockId);
              }
              if(E_OK == returnValue)
              {
                /* updates request status of this block */
                /* @Trace: NvM_SUD_FUNC_331 */
                SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                *(ptrRamStatus) = (*ptrRamStatus & NVM_NOT_ERROR_BIT_MASK) | 
                  NVM_REQ_CANCELED;
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                if(NVM_BSWM_BLOCK_STATUS_INFORMATION == (
                  ptrBlkDescTbl->usBlkParams & 
                  NVM_BSWM_BLOCK_STATUS_INFORMATION))
                {
                  /* @Trace: NvM_SUD_FUNC_332 */
                  BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_CANCELED);
                }
              }
          } /* End of block comment 2 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount--;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* End of block comment 1 */
        /* @Trace: NvM_SUD_FUNC_333 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_CANCELJOBS_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */
#endif /* NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1 */

/*******************************************************************************
** Function Name        : NvM_WriteAll                                        **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Request to synchronize the contents of RAM blocks to**
**                        their corresponding NV blocks during shutdown.      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NVRAM Manager should be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_InitStatus, NvM_PMCount,  **
**                        NvM_WriteAllRequest                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError(), BswM_NvM_CurrentJobMode(),       **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        BswM_RequestMode()                                  **
*******************************************************************************/

/* @Trace: SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_LIBS_08535 SRS_Mem_08535 SRS_NvM_CUS_00434 */
FUNC(void, NVM_CODE) NvM_WriteAll(void)
{
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_FALSE == NvM_InitStatus)
    {
      /* @Trace: NvM_SUD_FUNC_442 */
      /* Report non initialization */
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_WRITEALL_SID, NVM_E_UNINIT);
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_FUNC_443 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount++;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                      (BswM_ModeType)NVM_LOWPOWER_PREVENT);

      if(NVM_MULTIBLK_UNREQUESTED == NvM_WriteAllRequest)
      {
        /* @Trace: NvM_SUD_FUNC_444 */
        NvM_WriteAllRequest = NVM_MULTIBLK_REQUESTED;
        NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_PENDING);

        /* Inform multi-block request acceptance status to the BswM */
        #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
          (void)BswM_NvM_CurrentJobMode(NVM_WRITE_ALL, NVM_REQ_PENDING);
        #endif
      }
      /* @Trace: NvM_SUD_FUNC_445 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount--;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    }
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_GetErrorStatus                                  **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Description          : This API reads the attribute field bits from the RAM**
**                        block attribute/ error/ status field and returns the**
**                        error/status information to the application.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RequestResultPtr                                    **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Precondition         : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus             **
**                                                                            **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00020 */
/* @Trace: NvM_SUD_DATATYPE_008 */
/* @Trace: NvM_SUD_DATATYPE_009 */
FUNC(Std_ReturnType, NVM_CODE) NvM_GetErrorStatus(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    /* @Trace: NvM_SUD_FUNC_480 */
    varDetErrorId = NVM_E_NO_ERROR;
    /* If DET is off, return value always is E_OK */
    returnValue = E_NOT_OK;
  #endif
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_FALSE == NvM_InitStatus)
    {
      /* @Trace: NvM_SUD_FUNC_061 */
      /* Report non initialization */
      varDetErrorId = NVM_E_UNINIT;
    }
    /* If Block Identifier is not configured, report error to DET */
    else if(NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_062 */
      /* Report invalid Block Identifier */
      varDetErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    /* If passed pointer is NULL, report error to DET */
    else if(NULL_PTR == RequestResultPtr)
    {
      /* @Trace: NvM_SUD_FUNC_063 */
      varDetErrorId = NVM_E_PARAM_DATA;
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_FUNC_064 */
      /* Read error bits from RAM Attr/Error/Status field */
      *RequestResultPtr = NVM_GET_JOB_RESULT(BlockId);
      returnValue = E_OK;
    }

    /* @Trace: NvM_SUD_FUNC_065 NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_E_NO_ERROR != varDetErrorId)
    {
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_GETERRORSTATUS_SID, varDetErrorId);
    }
  #endif
    return(returnValue);
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_ReadBlock                                       **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId and  **
**                        NvM_DstPtr and Service Id to 'Read' the             **
**                        NV/ROM block data to its corresponding RAM block.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NvM_DstPtr                                          **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_PMCount         **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_StdQueueWrite(), Det_ReportRuntimeError(),      **
**                        BswM_NvM_CurrentBlockMode(), BswM_RequestMode(),    **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_LIBS_08533 SRS_Mem_00016 SRS_Mem_00038 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_ReadBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
  /*
   * If start address of the RAM block data is configured permanent RAM data block is 
   * available for selected block management type 
   * Check whether an explicit synchronization mechanism with a RAM
   * mirror and callback routiness for transferring data to and from NvM
   * module's RAM mirror is used for NV block. true if synchronization
   * mechanism is used, false otherwise.
   */
  /* Application SW-C accessing NVRAM blocks */
  /* which have Permanent RAM blocks, use RAM Mirror */
  /* @Trace: NvM_SUD_MACRO_034 */
  #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)) 
    /* Declare pointer to NvMBlockDescritor table */
    P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  #endif

    /* Declare local pointer to read the block dependent error/status information 
     * in the administrative part of a NVRAM block
     */
    P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;

    /* Declare variable queue the read request in the job queue */
    VAR(NvM_JobQueue, AUTOMATIC) varStdQueue;

    VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
  /* Declare return variable for request is accepted or not */
    returnValue = E_NOT_OK;
  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_166 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_167 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_168 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        {
          /* @Trace: NvM_SUD_FUNC_487 */
          /* Invoke function to enable data protection */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();

          /* Generic Request mode Enabled */
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);

          /* start of block comment - 2 */
          /* @Trace: NvM_SUD_MACRO_034 */
          #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
            (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
            ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          #endif
          /* 
           * If the permanent RAM block is not configured, NULL pointer is passed
           * as parameter, and Mirror is disabled report error to DET
           */
          if(
            /* @Trace: NvM_SUD_MACRO_034 */
            #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
              (NULL_PTR == (ptrBlkDescTbl->pRamBlkData)) &&
            #endif
              (NULL_PTR == NvM_DstPtr)
            #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
              && (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE != 
              (ptrBlkDescTbl->usBlkParams & 
              NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
            #endif
          )
          {
            /* @Trace: NvM_SUD_MACRO_007 */
            #if(STD_ON == NVM_DEV_ERROR_DETECT)
              /* @Trace: NvM_SUD_FUNC_169 */
              varDetErrorId = NVM_E_PARAM_ADDRESS;
            #endif
          }
          else
          {
            ptrRamStatus = &NvM_RamStatus[BlockId];
            if(NVM_REQ_PENDING == (*(ptrRamStatus) & NVM_ERROR_BIT_MASK))
            {
              /*
               * If the request for the block is present in queue or currently in
               * progress, report error to DET
               */
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_170 */
                varDetErrorId = NVM_E_BLOCK_PENDING;
              #endif
            }
            else
            { /* Start of block comment 4 */
              /*
               * Load the Service Id, Block Id and the passed pointer to the
               * corresponding elements of the Standard queue
               */
              /* @Trace: NvM_SUD_FUNC_171 */
              varStdQueue.ucService_Id = NVM_READBLOCK_SID;
              varStdQueue.ddBlock_Idx = BlockId;
              /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
              varStdQueue.pTempRamBlkData = (uint8*)NvM_DstPtr;
              /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
              /* @Trace: NvM_SUD_MACRO_025 */
              #if (STD_ON == NVM_JOB_PRIORITIZATION)
                /* @Trace: NvM_SUD_FUNC_172 */
                varStdQueue.ucPriority = 
                  NvM_BlkDescTbls[BlockId].ucBlkJobPriority;
              #endif

                /* Put the read request in the queue */
                /* @Trace: NvM_SUD_FUNC_173 */
                returnValue = NvM_StdQueueWrite(&varStdQueue);
                /* Check if the queue write is not successful */
                if(E_NOT_OK == returnValue)
                {
                  /* Report the queue overflow to DEM */
                  /* @Trace: NvM_SUD_FUNC_174 */
                  (void)Det_ReportRuntimeError(NVM_MODULE_ID, NVM_INSTANCE_ID,
                    NVM_READBLOCK_SID, NVM_E_QUEUE_FULL);
                }
                else if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                  (NvM_BlkDescTbls[BlockId].usBlkParams & 
                  NVM_BSWM_BLOCK_STATUS_INFORMATION))
                {
                  /* @Trace: NvM_SUD_FUNC_175 */
                  BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                }
                else
                {
                  /* Nothing */
                }
            }
            /* End of block comment 4 */
          } /* end of block comment - 3 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount--;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* end of block comment - 2 */
        /* @Trace: NvM_SUD_FUNC_176 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_READBLOCK_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */

#endif /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_ReadPRAMBlock                                   **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId and  **
**                        Service Id to 'Read' the                            **
**                        NV/ROM block data to its corresponding PRAM block.  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus, NvM_PMCount         **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_StdQueueWrite(), Det_ReportRuntimeError(),      **
**                        BswM_NvM_CurrentBlockMode(), BswM_RequestMode(),    **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_LIBS_08533 SRS_Mem_00016 SRS_Mem_00038 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_ReadPRAMBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId)
{ /* @Trace: NvM_SUD_MACRO_034 */
  #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
  /* Declare pointer to NvMBlockDescritor table */
    P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  #endif
    P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
    VAR(NvM_JobQueue, AUTOMATIC) varStdQueue;
    VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_177 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_178 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /*
           * Report invalid Block Identifier
           */
          /* @Trace: NvM_SUD_FUNC_179 */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        {
          /* @Trace: NvM_SUD_FUNC_488 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);
          /* start of block comment - 2 */
          /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_034 */
          #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
            (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
            ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          #endif
          /*
           * If the permanent RAM block is not configured, NULL pointer is passed
           * as parameter, and Mirror is disabled report error to DET
           */
            if(
              /* @Trace: NvM_SUD_MACRO_034 */
              #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                (NULL_PTR == (ptrBlkDescTbl->pRamBlkData)) &&
              #endif
              (NVM_TRUE == NVM_TRUE)
              /* when no permanent RAM block and no explicit synchronization are configured */
              /* @Trace: NvM_SUD_MACRO_005 */
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
              /* no explicit synchronization are configured */
                && (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE != 
                (ptrBlkDescTbl->usBlkParams & 
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
              #endif
            )
            {
              /*
               * when no permanent RAM block and 
               * no explicit synchronization are configured, for the received block ID
               */
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_180 */
                varDetErrorId = NVM_E_PARAM_ADDRESS;
              #endif
            }
            else
            { /* start of block comment - 3*/
              ptrRamStatus = &NvM_RamStatus[BlockId];
              /* Start of Block comment */
              if(NVM_REQ_PENDING == (*(ptrRamStatus) & NVM_ERROR_BIT_MASK))
              {
                /*
                 * If the request for the block is present in queue or currently in
                 * progress, report error to DET
                 */
                /* @Trace: NvM_SUD_MACRO_007 */
                #if(STD_ON == NVM_DEV_ERROR_DETECT)
                  /* @Trace: NvM_SUD_FUNC_181 */
                  varDetErrorId = NVM_E_BLOCK_PENDING;
                #endif
              }
              else
              { /* Start of block comment 4 */
                /*
                 * Load the Service Id, Block Id and the passed pointer to the
                 * corresponding elements of the Standard queue
                 */
                /* @Trace: NvM_SUD_FUNC_182 */
                varStdQueue.ucService_Id = NVM_READPRAMBLOCK_SID;
                varStdQueue.ddBlock_Idx = BlockId;
                varStdQueue.pTempRamBlkData = NULL_PTR;
                /* @Trace: NvM_SUD_MACRO_025 */
                #if(STD_ON == NVM_JOB_PRIORITIZATION)
                  /* @Trace: NvM_SUD_FUNC_183 */
                  varStdQueue.ucPriority = 
                    NvM_BlkDescTbls[BlockId].ucBlkJobPriority;
                #endif
                  /* @Trace: NvM_SUD_FUNC_184 */
                  /* Put the read request in the queue */
                  returnValue = NvM_StdQueueWrite(&varStdQueue);
                  /* Check if the queue write is not successful */
                  if(E_NOT_OK == returnValue)
                  {
                    /* @Trace: NvM_SUD_FUNC_185 */
                    /* Report the queue overflow to DET */
                    (void)Det_ReportRuntimeError(NVM_MODULE_ID, NVM_INSTANCE_ID,
                      NVM_READPRAMBLOCK_SID, NVM_E_QUEUE_FULL);
                  }
                  else if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                    (NvM_BlkDescTbls[BlockId].usBlkParams & 
                    NVM_BSWM_BLOCK_STATUS_INFORMATION))
                  {
                    /* @Trace: NvM_SUD_FUNC_186 */
                    BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                  }
                  else
                  {
                    /* Nothing */
                  }
              } /* End of block comment 4 */
            } /* end of block comment - 3 */

            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount--;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* end of block comment - 2 */
        /* @Trace: NvM_SUD_FUNC_187 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_READPRAMBLOCK_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */

#endif /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_CancelWriteAll                                  **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : Cancels a running NvM_WriteAll request.             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NVRAM Manager should be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s)     :  NvM_InitStatus,           **
**                        NvM_WriteAllRequest, NvM_CancelWriteAllRequest,     **
**                        NvM_PMCount                                         **
**                        Function(s) invoked    :  Det_ReportError(),        **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        BswM_RequestMode()                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_08540 */
FUNC(void, NVM_CODE) NvM_CancelWriteAll(void)
{
  /* function shall only be used by the BSW Mode Manager */
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_FALSE == NvM_InitStatus)
    {
      /* @Trace: NvM_SUD_FUNC_324 */
      /* Report non initialization */
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_CANCELWRITEALL_SID, NVM_E_UNINIT);
    }
    else
  #endif
    { /* Start of block comment 1 */
      /* @Trace: NvM_SUD_FUNC_325 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount++;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                      (BswM_ModeType)NVM_LOWPOWER_PREVENT);

      if((NVM_MULTIBLK_UNREQUESTED != NvM_WriteAllRequest) &&
        (NVM_FALSE == NvM_CancelWriteAllRequest))
      {
        /*
         * Flag is set, which is checked in 'WriteAll' processing function to
         * cancel the 'WriteAll' request that is in progress
         */
        NvM_CancelWriteAllRequest = NVM_TRUE;
      }

      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount--;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    } /* End of block comment 1 */
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_ReadAll                                         **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This call signals the request to the NVRAM Manager  **
**                        and returns                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NVRAM Manager should be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s) : NvM_InitStatus,                **
**                        NvM_ReadAllRequest, NvM_PMCount                     **
**                                                                            **
**                        Function(s) invoked: Det_ReportError(),             **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        BswM_RequestMode(), BswM_NvM_CurrentJobMode()       **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_08533 SRS_NvM_CUS_00433 */
FUNC(void, NVM_CODE) NvM_ReadAll(void)
{
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_FALSE == NvM_InitStatus)
    {
      /* @Trace: NvM_SUD_FUNC_163 */
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_READALL_SID, NVM_E_UNINIT);
    }
    else
  #endif
    { /* Start of block comment 1 */
      /* @Trace: NvM_SUD_FUNC_164 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount++;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                      (BswM_ModeType)NVM_LOWPOWER_PREVENT);

      if(NVM_MULTIBLK_UNREQUESTED == NvM_ReadAllRequest)
      {
        NvM_ReadAllRequest = NVM_MULTIBLK_REQUESTED;
        NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_PENDING);
        #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
          (void)BswM_NvM_CurrentJobMode(NVM_READ_ALL, NVM_REQ_PENDING);
        #endif
      }
      /* @Trace: NvM_SUD_FUNC_165 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount--;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    } /* End of block comment 1 */
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_SetDataIndex                                    **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : The function sets the association of Dataset NV     **
**                        block with its corresponding RAM block by storing   **
**                        the 8 bit DataIndex passed by the application to    **
**                        the index field of the RAM block.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, DataIndex                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        NvM_InitStatus, NvM_BlkDescTbls,                    **
**                        NvM_RamStatus, NvM_RamIndex                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError(), SchM_Enter_NvM_RAM_INDEX(),      **
**                        SchM_Exit_NvM_RAM_INDEX()                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_08007 */
/* @Trace: SRS_Mem_08528 */
/* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_DATASET_PRESENT))
FUNC(Std_ReturnType, NVM_CODE) NvM_SetDataIndex(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(uint8, AUTOMATIC) DataIndex)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrRamIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    P2CONST(uint8, NVM_CONFIG_DATA, NVM_APPL_CONST)ptrRomBlkDataAddr;
    VAR(uint8, AUTOMATIC) numOfNvBlks;
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif

    returnValue = E_OK;
  /*
  * If Development error detection is enabled, validation of input parameters
  * is done and initialization is checked.
  */
 /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_043 */
      returnValue = E_NOT_OK;
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_044 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
          returnValue = E_NOT_OK;
        }
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_045 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
          returnValue = E_NOT_OK;
        }
        else
      #endif
        { /* Start of Block comment - 2 */
          /* @Trace: NvM_SUD_FUNC_477 */
          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          ptrRamIndex = &NvM_RamIndex[BlockId];
          /* @Trace: NvM_SUD_MACRO_007 */
          #if(STD_ON == NVM_DEV_ERROR_DETECT)
            numOfNvBlks = ptrBlkDescTbl->ucNumOfNvBlks;
            ptrRomBlkDataAddr = ptrBlkDescTbl->pRomBlkData;
          #endif

          /* If the Block Management Type is equal to Native or Redundant Management
           * Type, report error to DET
           */
            if(NVM_BLOCK_DATASET != (ptrBlkDescTbl->enBlkMngmntType))
            {
              /* @Trace: NvM_SUD_FUNC_047 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                varDetErrorId = NVM_E_PARAM_BLOCK_TYPE;
              #endif
              returnValue = E_NOT_OK;
            }
          /* If the Dataset Management Type block is not configured with ROM but
           * the passed data index value is greater than the number of NV blocks
           * or If the Dataset Management Type block is configured with ROM but the
           * passed data index value is greater than the number of NV blocks and
           * number of ROM blocks, report error to DET
           */
          /* @Trace: NvM_SUD_MACRO_007 */
          #if(STD_ON == NVM_DEV_ERROR_DETECT)
            else if(((NULL_PTR == ptrRomBlkDataAddr) && (numOfNvBlks <=
              DataIndex)) || ((NULL_PTR != ptrRomBlkDataAddr) &&
              ((numOfNvBlks + ptrBlkDescTbl->ucNumOfRomBlks) <= DataIndex)))
            {
              /* @Trace: NvM_SUD_FUNC_046 */
              varDetErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
              returnValue = E_NOT_OK;
            }
            else
          #endif
            { /* Start of block comment 3 */
              /* @Trace: NvM_SUD_FUNC_476 */
              ptrRamStatus = &NvM_RamStatus[BlockId];
              if(NVM_REQ_PENDING == (*(ptrRamStatus) & NVM_ERROR_BIT_MASK))
              {
                /* @Trace: NvM_SUD_MACRO_007 */
                #if(STD_ON == NVM_DEV_ERROR_DETECT)
                  /* If the request for the block is present in queue or currently in
                   * progress, report error to DET
                   */
                  /* @Trace: NvM_SUD_FUNC_048 */
                  varDetErrorId = NVM_E_BLOCK_PENDING;
                #endif
                returnValue = E_NOT_OK;
              }
              else
              {
                /* @Trace: NvM_SUD_FUNC_049 */
                SchM_Enter_NvM_RAM_INDEX();
                /* Store the data index into the RAM index */
                *(ptrRamIndex) = DataIndex;
                SchM_Exit_NvM_RAM_INDEX();
              }
            } /* End of block comment 3 */
        } /* end of Block comment - 2 */

        /* @Trace: NvM_SUD_FUNC_050 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if (NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_SETDATAINDEX_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_GetDataIndex                                    **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This function reads the index (association of NV    **
**                        block with its corresponding RAM block) from        **
**                        the RAM block index field.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DataIndexPtr                                        **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamIndex                       **
**                                                                            **
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_08528 */
/* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_DATASET_PRESENT))
FUNC(Std_ReturnType, NVM_CODE) NvM_GetDataIndex(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    /* @Trace: NvM_SUD_FUNC_028 */
    returnValue = E_NOT_OK;

  /* If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_029 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_030 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* start of Block comment - 2 */
          /* If passed pointer is NULL, report error to DET */
          /* @Trace: NvM_SUD_MACRO_007 */
          #if(STD_ON == NVM_DEV_ERROR_DETECT)
            if(NULL_PTR == DataIndexPtr)
            {
              /* @Trace: NvM_SUD_FUNC_031 */
              varDetErrorId = NVM_E_PARAM_DATA;
            }
            else
          #endif
            { /* start of Block comment - 3 */
              ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
              /*
               * If the Block Management Type is equal to Native or Redundant
               * Management Type, report error to the DET
               */
              /* @Trace: NvM_SUD_FUNC_032 */
              if(NVM_BLOCK_DATASET != ptrBlkDescTbl->enBlkMngmntType)
              {
                *DataIndexPtr = (uint8)NVM_ZERO;
                /* @Trace: NvM_SUD_MACRO_007 */
                #if(STD_ON == NVM_DEV_ERROR_DETECT)
                  /* @Trace: NvM_SUD_FUNC_033 */
                  varDetErrorId = NVM_E_PARAM_BLOCK_TYPE;
                #endif
              }
              else
              {
                /* @Trace: NvM_SUD_FUNC_034 */
                /* Return the stored data index */
                *DataIndexPtr = NvM_RamIndex[BlockId];
                returnValue = E_OK;
              }
            } /* end of Block comment - 3 */
        } /* end of Block comment - 2 */
        /* @Trace: NvM_SUD_FUNC_035 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if (NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_GETDATAINDEX_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
}/* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_SetRamBlockStatus                               **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This API recalculates the CRC (if configured) for   **
**                        the RAM block data and sets the state of the        **
**                        RAM block to valid/invalid.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, BlockChanged                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_RamStatus                      **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00038 SRS_Mem_08545 SRS_Mem_08550 */
/* @Trace: NvM_SUD_MACRO_036 */
#if(STD_ON == NVM_SET_RAM_BLOCK_STATUS_API)
FUNC(Std_ReturnType, NVM_CODE) NvM_SetRamBlockStatus(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(boolean, AUTOMATIC) BlockChanged)
{
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  /* @Trace: NvM_SUD_MACRO_034 */
  #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
    VAR(uint16, AUTOMATIC) blkParams;
    P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  #endif
    VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif

    returnValue = E_NOT_OK;
  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_051 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_052 */
          /* Report non initialization */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_053 */
          /* Report invalid Block Identifier */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* start of Block comment - 2 */
          /* @Trace: NvM_SUD_MACRO_034 */
          #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
            (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
            /* @Trace: NvM_SUD_FUNC_479 */
            ptrBlkDescTbl =  &NvM_BlkDescTbls[BlockId];
            blkParams = ptrBlkDescTbl->usBlkParams;
          #endif
            ptrRamStatus = &NvM_RamStatus[BlockId];
            if(NVM_REQ_PENDING == (*(ptrRamStatus) & NVM_ERROR_BIT_MASK))
            {
              /*
               * If the request for the block is present in queue or currently in
               * progress, report error to DET
               */
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_054 */
                varDetErrorId = NVM_E_BLOCK_PENDING;
              #endif
            }
          /* Check if Permanent RAM block is configured or explicit 
           * synchronization is configured and block use set ram block status
           */
          /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_034 */
          #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
            (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
            /* Report DET error if block is locked*/
            else if(NVM_LOCK_RAM_MASK == (*(ptrRamStatus) & NVM_LOCK_RAM_MASK))
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_055 */
                varDetErrorId = NVM_E_BLOCK_LOCKED;
              #endif
            }
            else if((NVM_BLOCK_USE_SETRAMBLOCKSTATUS == (blkParams & 
              NVM_BLOCK_USE_SETRAMBLOCKSTATUS)) && (
              /* @Trace: NvM_SUD_MACRO_034 */
              #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                (NULL_PTR != ptrBlkDescTbl->pRamBlkData)
              #endif
              /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_034 */
              #if((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) && \
                (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
                ||
              #endif
              /* @Trace: NvM_SUD_MACRO_005 */
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == (blkParams & 
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
              #endif
              )
            )
            { /* start of Block comment - 3 */
              /* @Trace: NvM_SUD_FUNC_057 */
              returnValue = E_OK;
              if(NVM_TRUE == BlockChanged)
              {
                /* @Trace: NvM_SUD_FUNC_058 */
                /* Invoke function to enable data protection */
                SchM_Enter_NvM_RAM_STATUS_PROTECTION();

                /* Update the RAM block status to 'Valid and Changed' */
                *ptrRamStatus = ((*(ptrRamStatus) & 
                  NVM_CLEAR_RAM_INTERNAL_STATE) | NVM_VALID_CHANGED);

                /* Invoke function to disable data protection */
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
              }
              else
              {
                /* @Trace: NvM_SUD_FUNC_059 */
                /* Invoke function to enable data protection */
                SchM_Enter_NvM_RAM_STATUS_PROTECTION();

                /* Update the RAM block status to 'Unchanged' */
                *ptrRamStatus = ((*(ptrRamStatus) & 
                  NVM_CLEAR_RAM_INTERNAL_STATE) | NVM_INVALID_UNCHANGED);

                /* Invoke function to disable data protection */
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
              }
            } /* end of Block comment - 3 */
            else
            {
              /* To avoid QAC warning */
              returnValue = E_OK;
            }
          #else
            else
            {
              /* @Trace: NvM_SUD_FUNC_056 */
              returnValue = E_OK;
              NVM_UNUSED(BlockChanged);
            }
          #endif
        } /* end of Block comment - 2 */

        /* @Trace: NvM_SUD_FUNC_060 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if (NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_SETRAMBLOCKSTATUS_SID, varDetErrorId);
        }
      #endif
    }
    return(returnValue);
} /* End of function body */

#endif /* (STD_ON == NVM_SET_RAM_BLOCK_STATUS_API) */

/*******************************************************************************
** Function Name        : NvM_RestoreBlockDefaults                            **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId,     **
**                        NvM_DestPtr and Service Id to 'Restore' the         **
**                        ROM block default data to its corresponding RAM     **
**                        block.                                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NvM_DestPtr                                         **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_PMCount, NvM_RamIndex          **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_StdQueueWrite(), Dem_ReportErrorStatus(),       **
**                        BswM_RequestMode(), BswM_NvM_CurrentBlockMode(),    **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00018 SRS_Mem_00038 SRS_Mem_08542 SRS_BSW_00457 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_RestoreBlockDefaults(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST)ptrBlkDescTbl;
  VAR(NvM_JobQueue, AUTOMATIC) varStdQueue;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint8, AUTOMATIC) ramIndex;
  #endif
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_074 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_075 */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_076 */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of block comment 1 */
          /* @Trace: NvM_SUD_FUNC_482 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);

          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            ramIndex = NvM_RamIndex[BlockId];
          #endif
          /*
           * If the permanent RAM block is not configured and NULL pointer is passed
           * as parameter and explicit callbacks are not configured, report error to DET
           */
            if(
              /* @Trace: NvM_SUD_MACRO_034 */
              #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                (NULL_PTR == (ptrBlkDescTbl->pRamBlkData)) &&
              #endif
              (NULL_PTR == NvM_DestPtr)
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                && (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE != 
                (ptrBlkDescTbl->usBlkParams & 
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
              #endif
            )
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_077 */
                varDetErrorId = NVM_E_PARAM_ADDRESS;
              #endif
            }
            /*
             * Check if ROM block and Initblockcallback are not configured for the
             * block
             */
            else if((NULL_PTR == ptrBlkDescTbl->pRomBlkData)
              /* @Trace: NvM_SUD_MACRO_024 */
              #if(STD_ON == NVM_INIT_CALLBACK)
                && (NULL_PTR == ptrBlkDescTbl->pNvMInitNotification_BlockId)
              #endif
            )
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_078 */
                varDetErrorId = NVM_E_BLOCK_WITHOUT_DEFAULTS;
              #endif
            }
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          /* Check if index is not pointing to ROM area in case of Dataset block */
          #if(STD_ON == NVM_DATASET_PRESENT)
            else if(
              (NVM_BLOCK_DATASET == ptrBlkDescTbl->enBlkMngmntType) &&
              (ptrBlkDescTbl->ucNumOfNvBlks > ramIndex)
            )
            {
              /* @Trace: NvM_SUD_FUNC_079 */
            }
          #endif
            else if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
            {
              /*
               * If the request for the block is present in queue or currently
               * in progress, report error to DET
               */
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_080 */
                varDetErrorId = NVM_E_BLOCK_PENDING;
              #endif
            }
            else
            { /* Start of block comment 2 */
              /*
               * Load the Service Id, Block Id and the passed pointer to the
               * corresponding elements of the Standard queue
               */
              /* @Trace: NvM_SUD_FUNC_081 */
              varStdQueue.ucService_Id = NVM_RESTOREBLOCKDEFAULTS_SID;
              varStdQueue.ddBlock_Idx = BlockId;
              /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
              varStdQueue.pTempRamBlkData = (uint8*)NvM_DestPtr;
              /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
              /* @Trace: NvM_SUD_MACRO_025 */
              #if (STD_ON == NVM_JOB_PRIORITIZATION)
                /* @Trace: NvM_SUD_FUNC_082 */
                varStdQueue.ucPriority = 
                  NvM_BlkDescTbls[BlockId].ucBlkJobPriority;
              #endif
                /* @Trace: NvM_SUD_FUNC_083 */
                /* Put the restore request in the queue  */
                returnValue = NvM_StdQueueWrite(&varStdQueue);
                /* Check if the queue write is not successful */
                if(E_NOT_OK == returnValue)
                {
                  /* @Trace: NvM_SUD_FUNC_084 */
                  /* Report the queue overflow to DET */
                  (void)Det_ReportRuntimeError(NVM_MODULE_ID, NVM_INSTANCE_ID,
                    NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_QUEUE_FULL); 
                }
                else if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                  (ptrBlkDescTbl->usBlkParams & 
                  NVM_BSWM_BLOCK_STATUS_INFORMATION))
                {
                  /* @Trace: NvM_SUD_FUNC_085 */
                  BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                }
                else
                {
                }
            } /* End of block comment 2 */

            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount--;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* End of block comment 1 */
        /* @Trace: NvM_SUD_FUNC_086 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_RESTOREBLOCKDEFAULTS_SID, varDetErrorId);
        }
      #endif
    }
    return (returnValue);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_RestorePRAMBlockDefaults                        **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId      **
**                        and Service Id to 'Restore' the ROM block default   **
**                        data to its corresponding RAM block.                **
**                                                                            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_BlkDescTbls, NvM_PMCount, NvM_RamIndex          **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_StdQueueWrite(), Dem_ReportErrorStatus(),       **
**                        BswM_RequestMode(), BswM_NvM_CurrentBlockMode(),    **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 SRS_Mem_00018 SRS_Mem_00038 SRS_Mem_08542 SRS_BSW_00457 SRS_Mem_08014 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_RestorePRAMBlockDefaults(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  VAR(NvM_JobQueue, AUTOMATIC) varStdQueue;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint8, AUTOMATIC) ramIndex;
  #endif
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif
    returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_008 */
  #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
    if(NVM_ONE == BlockId)
    {
      /* @Trace: NvM_SUD_FUNC_087 */
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_FALSE == NvM_InitStatus)
        {
          /* @Trace: NvM_SUD_FUNC_088 */
          varDetErrorId = NVM_E_UNINIT;
        }
        /* If Block Identifier is not configured, report error to DET */
        else if((NVM_ZERO == BlockId) || 
          (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS <= BlockId))
        {
          /* @Trace: NvM_SUD_FUNC_089 */
          varDetErrorId = NVM_E_PARAM_BLOCK_ID;
        }
        else
      #endif
        { /* Start of block comment 1 */
          /* @Trace: NvM_SUD_FUNC_483 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_PMCount++;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                          (BswM_ModeType)NVM_LOWPOWER_PREVENT);

          ptrBlkDescTbl = &NvM_BlkDescTbls[BlockId];
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            ramIndex = NvM_RamIndex[BlockId];
          #endif
          /*
           * If the permanent RAM block is not configured and explicit callbacks are 
           * not configured, report error to DET
           */
            if(
              /* @Trace: NvM_SUD_MACRO_034 */
              #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                (NULL_PTR == (ptrBlkDescTbl->pRamBlkData)) &&
              #endif
                (NVM_TRUE == NVM_TRUE)
              #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                && (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE != 
                ((ptrBlkDescTbl->usBlkParams) & 
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
              #endif
            )
            {
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                /* @Trace: NvM_SUD_FUNC_090 */
                varDetErrorId = NVM_E_PARAM_ADDRESS;
              #endif
            }
            else
            { /* Start of block comment 2 */
              /*
               * Check if ROM block and Initblockcallback are not configured for the
               * block
               */
              if((NULL_PTR == ptrBlkDescTbl->pRomBlkData)
                /* @Trace: NvM_SUD_MACRO_024 */
                #if(STD_ON == NVM_INIT_CALLBACK)
                  && (NULL_PTR == ptrBlkDescTbl->pNvMInitNotification_BlockId)
                #endif
              )
              {
                /* @Trace: NvM_SUD_MACRO_007 */
                #if(STD_ON == NVM_DEV_ERROR_DETECT)
                  /* @Trace: NvM_SUD_FUNC_091 */
                  varDetErrorId = NVM_E_BLOCK_WITHOUT_DEFAULTS;
                #endif
              }
              /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
              /* Check if index is not pointing to ROM area in case of Dataset block */
              #if(STD_ON == NVM_DATASET_PRESENT)
                else if(
                  (NVM_BLOCK_DATASET == ptrBlkDescTbl->enBlkMngmntType) &&
                  (ptrBlkDescTbl->ucNumOfNvBlks > ramIndex)
                )
                {
                  /* @Trace: NvM_SUD_FUNC_092 */
                }
              #endif
                else if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(BlockId))
                {
                  /*
                   * If the request for the block is present in queue or currently
                   * in progress, report error to DET
                   */
                  /* @Trace: NvM_SUD_MACRO_007 */
                  #if(STD_ON == NVM_DEV_ERROR_DETECT)
                    /* @Trace: NvM_SUD_FUNC_093 */
                    varDetErrorId = NVM_E_BLOCK_PENDING;
                  #endif
                }
                else
                { /* Start of block comment 2 */
                  /*
                   * Load the Service Id, Block Id and the passed pointer to the
                   * corresponding elements of the Standard queue
                   */
                  /* @Trace: NvM_SUD_FUNC_094 */
                  varStdQueue.ucService_Id = NVM_RESTOREPRAMBLOCKDEFAULTS_SID;
                  varStdQueue.ddBlock_Idx = BlockId;
                  varStdQueue.pTempRamBlkData = (uint8*)NULL_PTR;
                  /* @Trace: NvM_SUD_MACRO_025 */
                  #if (STD_ON == NVM_JOB_PRIORITIZATION)
                    /* @Trace: NvM_SUD_FUNC_095 */
                    varStdQueue.ucPriority = 
                      NvM_BlkDescTbls[BlockId].ucBlkJobPriority;
                  #endif
                    /* @Trace: NvM_SUD_FUNC_096 */
                    /* Put the restore request in the queue */
                    returnValue = NvM_StdQueueWrite(&varStdQueue);
                    /* Check if the queue write is not successful */
                    if(E_NOT_OK == returnValue)
                    {
                      /* @Trace: NvM_SUD_FUNC_097 */
                      /* Report the queue overflow to DET */
                      (void)Det_ReportRuntimeError(
                        NVM_MODULE_ID, NVM_INSTANCE_ID,
                        NVM_RESTOREPRAMBLOCKDEFAULTS_SID, NVM_E_QUEUE_FULL);
                    }
                    else if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
                      (ptrBlkDescTbl->usBlkParams & 
                      NVM_BSWM_BLOCK_STATUS_INFORMATION))
                    {
                      /* @Trace: NvM_SUD_FUNC_098 */
                      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
                    }
                    else
                    {
                    }
                } /* End of block comment 3 */
            } /* End of block comment 2 */
            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_PMCount--;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        } /* End of block comment 1 */
        /* @Trace: NvM_SUD_FUNC_099 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        if(NVM_E_NO_ERROR != varDetErrorId)
        {
          (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
            NVM_RESTOREPRAMBLOCKDEFAULTS_SID, varDetErrorId);
        }
      #endif
    }
    return (returnValue);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_FirstInitAll                                    **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : The function initiates a multi block first          **
**                        initialization request. The job of the function     **
**                        does not care if a block exists in the non-volatile **
**                        memory or not OR if it is valid (i.e. not           **
**                        corrupted) or not, when processing it.              **
**                                                                            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_WriteAllRequest, NvM_FirstInitAllRequest,       **
**                        NvM_ReadAllRequest, NvM_ValidateAllRequest,         **
**                        NvM_PMCount                                         **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        BswM_NvM_CurrentJobMode(), BswM_RequestMode(),      **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00386 SRS_BSW_00406 */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)

FUNC(void, NVM_CODE) NvM_FirstInitAll(void)
{
  /* @Trace: NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    VAR(uint8, AUTOMATIC) varDetErrorId;
    varDetErrorId = NVM_E_NO_ERROR;
  #endif

    if(NVM_FALSE == NvM_InitStatus)
    {
      /* @Trace: NvM_SUD_FUNC_008 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        varDetErrorId = NVM_E_UNINIT;
      #endif
    }
    /* Get the multi block request result */
    else if((NVM_MULTIBLK_UNREQUESTED != NvM_WriteAllRequest) ||
      (NVM_MULTIBLK_UNREQUESTED != NvM_ReadAllRequest) ||
      (NVM_MULTIBLK_UNREQUESTED != NvM_FirstInitAllRequest) ||
      (NVM_MULTIBLK_UNREQUESTED != NvM_ValidateAllRequest))
    {
      /* @Trace: NvM_SUD_FUNC_009 NvM_SUD_MACRO_007 */
      #if(STD_ON == NVM_DEV_ERROR_DETECT)
        varDetErrorId = NVM_E_BLOCK_PENDING;
      #endif
    }
    /* Check if FirstInitAll is not requested or in progress */
    else
    {
      /* @Trace: NvM_SUD_FUNC_010 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount++;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                      (BswM_ModeType)NVM_LOWPOWER_PREVENT);
      /* Signal to Mainfunction and return */
      NvM_FirstInitAllRequest = NVM_MULTIBLK_REQUESTED;

      NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_PENDING);

      /* @Trace: NvM_SUD_FUNC_011 */
      #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
        (void)BswM_NvM_CurrentJobMode(NVM_FIRST_INIT_ALL, NVM_REQ_PENDING);
      #endif

      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_PMCount--;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    }
    /* @Trace: NvM_SUD_FUNC_012 NvM_SUD_MACRO_007 */
  #if(STD_ON == NVM_DEV_ERROR_DETECT)
    if(NVM_E_NO_ERROR != varDetErrorId)
    {
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
        NVM_FIRSTINITALL_SID, varDetErrorId);
    }
  #endif
} /* End of function body */

#endif /* (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_MainFunction                                    **
**                                                                            **
** Service ID           : 0x0E                                                **
**                                                                            **
** Description          : Function performs the processing of the NVM Manager **
**                        jobs. This function has to be called cyclically in  **
**                        every case.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_InitStatus,            **
**                        NvM_State, NvM_CancelWriteAllRequest,               **
**                        NvM_NotifiedGlobalStatus, NvM_NvmBlkDescTbl         **
**                        NvM_JobResultLowLevel, NvM_WriteAllSubState,        **
**                        NvM_WriteAllRequest, NvM_SetModeStatus              **
**                                                                            **
**                        Function(s) invoked :NvM_ProcessWriteBlock(),       **
**                        NvM_ProcessWriteAllBlocks(), MemIf_GetJobResult(),  **
**                        NvM_ProcessReadAllBlocks(), NvM_ProcessReadBlock(), **
**                        NvM_ProcessEraseInvalidBlk(), MemIf_GetStatus()     **
**                        NvM_ProcessRestoreBlock(), NVM_MULTI_BLOCK_CBK(),   **
**                        BswM_NvM_CurrentJobMode(),                          **
**                        NvM_MainFunctionProcessImmediate(),                 **
**                        NvM_MainFunctionMultiProcess()                      **
*******************************************************************************/
/* @Trace: SRS_Mem_08534 SRS_Mem_08541 SRS_NvM_CUS_00681 SRS_NvM_CUS_00430 SRS_NvM_CUS_00431 SRS_BSW_00429 */
/* @Trace: SRS_NvM_CUS_00426 SRS_BSW_00425 SRS_Mem_00011 SRS_BSW_00172 SRS_BSW_00373 SRS_Mem_00041 */
/* @Trace: NvM_SUD_MACRO_026 */
FUNC(void, NVM_CODE) NvM_MainFunction(void)
{
  /* @Trace: NvM_SUD_MACRO_033 NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 */
  /* check the initialization is completed */
  #if((STD_ON == NVM_POLLING_MODE) && ((NVM_API_CONFIG_CLASS_1 != \
    NVM_API_CONFIG_CLASS) || (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || \
    (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)))
    /* @Trace: NvM_SUD_DATATYPE_003 */
    VAR(MemIf_JobResultType, AUTOMATIC) result;
  #endif

    if(NVM_TRUE == NvM_InitStatus)
    {
      /*
       * This section performs the polling of job status of the MEMIF layer and
       * is available only if NVM_POLLING_MODE is enabled
       */
      /* @Trace: NvM_SUD_MACRO_033 NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 */
      #if((STD_ON == NVM_POLLING_MODE) && ((NVM_API_CONFIG_CLASS_1 != \
        NVM_API_CONFIG_CLASS) || (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || \
        (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)))
        if(((NULL_PTR != NvM_NvmBlkDescTbl)
          /* @Trace: NvM_SUD_MACRO_022 */
          #if(STD_ON == NVM_DRV_MODE_SWITCH)
          && (NVM_FALSE == NvM_SetModeStatus)
          #endif
          ) && (NVM_REQ_PENDING == NvM_JobResultLowLevel))
        {
          /* @Trace: NvM_SUD_FUNC_336 */
          result = MemIf_GetJobResult(NvM_NvmBlkDescTbl->ucNvramDeviceId);
          if (MEMIF_JOB_OK == result)
          {
            /* @Trace: NvM_SUD_FUNC_337 */
            NvM_JobResultLowLevel = NVM_REQ_OK;
          }
          else if (MEMIF_JOB_PENDING != result)
          {
            /* @Trace: NvM_SUD_FUNC_338 */
            NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
          }
          else
          {
            /* Else loop added to avoid QAC warning */
          }
        }
      #endif

      /*
       * This section performs the processing of immediate priority requests and
       * is available only if NVM_JOB_PRIORITIZATION is enabled
       */
      #if(STD_ON == NVM_JOB_PRIO)
        if(NVM_TRUE == NvM_MainFunctionProcessImmediate(NVM_WRITE_IMM_JOB))
        {
          /* @Trace: NvM_SUD_FUNC_515 */
        } /* @End of if(NVM_TRUE == NvM_MainFunctionProcessImmediate(NVM_WRITE_IMM_JOB)) */
        else
      #endif
        {
          #if(STD_ON == NVM_JOB_PRIO)
          /* @Trace: NvM_SUD_FUNC_516 */
          if(NVM_FALSE == NvM_MainFunctionProcessImmediate(NVM_WRITE_START_IMM))
          #endif
          {
            switch (NvM_State)
            {
              /* @Trace: NvM_SUD_MACRO_043 */
              #if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
                (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
              case NVM_VALIDATEALL_SID:
              #endif
              /* @Trace: NvM_SUD_MACRO_041 */
              #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
                (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
              case NVM_FIRSTINITALL_SID:
              #endif
              /* @Trace: NvM_SUD_MACRO_042 */
              #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
              case NVM_READALL_SID:
              #endif
              case NVM_IDLE:
                /* @Trace: NvM_SUD_FUNC_517 */
                NvM_MainFunctionMultiProcess();
              break;

              #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
                case NVM_READBLOCK_SID:
                case NVM_READPRAMBLOCK_SID:
                  /* @Trace: NvM_SUD_FUNC_362 */
                  NvM_ProcessReadBlock();
                break;

                case NVM_WRITEBLOCK_SID:
                case NVM_WRITEPRAMBLOCK_SID:
                  /* @Trace: NvM_SUD_FUNC_363 */
                  NvM_ProcessWriteBlock();
                break;

                case NVM_RESTOREPRAMBLOCKDEFAULTS_SID: /* Add code for restore block */
                case NVM_RESTOREBLOCKDEFAULTS_SID:
                  /* @Trace: NvM_SUD_FUNC_364 */
                  NvM_ProcessRestoreBlock();
                break;
              #endif

              #if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
                case NVM_ERASENVBLOCK_SID:
                case NVM_INVALIDATENVBLOCK_SID:
                  /* @Trace: NvM_SUD_FUNC_365 */
                  NvM_ProcessEraseInvalidBlk();
                break;
              #endif

              case NVM_WRITEALL_SID:
                /* @Trace: NvM_SUD_MACRO_044 */
                #if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
                  /* @Trace: NvM_SUD_FUNC_366 */
                  NvM_ProcessWriteAllBlocks();
                  /* Check if writing of all blocks are complete */
                  if((NVM_WRITE_ALL_IDLE == NvM_WriteAllSubState)
                    /* @Trace: NvM_SUD_MACRO_022 */
                    #if(STD_ON == NVM_DRV_MODE_SWITCH)
                      /* wait until Setmode job is complete */
                      && (NVM_REQ_PENDING != NvM_JobResultLowLevel)
                    #endif
                  )
                #endif
                  {
                    /*
                     * Wait for the MEMIF status to become idle before completion of
                     * WriteAll request
                     */
                    #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
                      /* @Trace: NvM_SUD_FUNC_367 */
                      NvM_State = NVM_IDLE;
                      NvM_WriteAllRequest = NVM_MULTIBLK_UNREQUESTED;
                      NVM_SET_JOB_RESULT(
                        NVM_RESERVED_BLOCK_ID, NvM_NotifiedGlobalStatus);
                      if(NVM_TRUE == NvM_CancelWriteAllRequest)
                      {
                        (void)BswM_NvM_CurrentJobMode(NVM_CANCEL_WRITE_ALL, 
                          NvM_NotifiedGlobalStatus);
                        NvM_CancelWriteAllRequest = NVM_FALSE;
                      }
                      else
                      {
                        (void)BswM_NvM_CurrentJobMode(NVM_WRITE_ALL, 
                          NvM_NotifiedGlobalStatus);
                      }
                    #else
                      if (MEMIF_BUSY_INTERNAL != 
                        MemIf_GetStatus(MEMIF_BROADCAST_ID))
                      {
                        /* Invoke the callback function, if configured */
                        NVM_SET_JOB_RESULT(
                        NVM_RESERVED_BLOCK_ID, NvM_NotifiedGlobalStatus);
                        /* @Trace: NvM_SUD_MACRO_029 */
                        #if(STD_ON == NVM_MULTIBLKCBK_ENABLE)
                          /* @Trace: NvM_SUD_FUNC_368 */
                          if(NVM_TRUE == NvM_CancelWriteAllRequest)
                          {
                            (void)BswM_NvM_CurrentJobMode(NVM_CANCEL_WRITE_ALL, 
                              NvM_NotifiedGlobalStatus);
                          }
                          else
                          {
                            /* @Trace: NvM_SUD_MACRO_031 */
                            (void)NVM_MULTI_BLOCK_CBK(NVM_WRITE_ALL,
                                                NvM_NotifiedGlobalStatus);
                          }
                        #endif
                        /* @Trace: NvM_SUD_FUNC_369 */
                        NvM_State = NVM_IDLE;
                        NvM_WriteAllRequest = NVM_MULTIBLK_UNREQUESTED;
                        NvM_CancelWriteAllRequest = NVM_FALSE;
                      }
                    #endif
                  } /* @End of if(NVM_WRITE_ALL_IDLE == NvM_WriteAllSubState) */
              break;

              /* polyspace-begin RTE:UNR [Justified:Low] " Default case to avoid misra and warning" */
              default:
                /* Do nothing */
                break;
              /* polyspace-end RTE:UNR */
            }  /* end of switch (NvM_State) */
          }
        } /* end else part of if(NVM_TRUE == 
              NvM_MainFunctionProcessImmediate(NVM_WRITE_IMM_JOB)) */
    } /* @End of if(NVM_TRUE == NvM_InitStatus) */
} /* End of function body */

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:11.5 */
/* polyspace-end MISRA2012:D4.14 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
