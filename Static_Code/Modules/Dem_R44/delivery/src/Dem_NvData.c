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
**  SRC-MODULE: Dem_NvData.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of NvM related functionality                        **
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
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_EventMemory.h"
#include "Dem_NvData.h"
#include "Dem_Config.h"


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if ((DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > DEM_ZERO) || \
     (DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID > DEM_ZERO) )
static FUNC(boolean, DEM_CODE) Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
  const Dem_DTCOriginType DTCOrigin,
  const uint8 Filter,
  const boolean Direction);
#endif

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 ** Function Name       : Dem_NvData_GetNvMBlockId                            **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Get NvM blockId to write non-volatile data in NvRam **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCOrigin, DTCOrigin, MemLocation                   **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : BlockId                                             **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)     : None                       **
 **                       Dem_ListOfPrimaryNvmBlockId                         **
 **                       Function(s) invoked    : None                       **
 *******************************************************************************/
/* @Trace: SRS_BSW_00301
 */
/* @Trace: Dem_SUD_MACRO_022 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvData_GetNvMBlockId(
  const Dem_NvDataIdType NvDataId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_NumOfEventMemoryEntryType MemLocation,
  P2VAR(NvM_BlockIdType, AUTOMATIC, DEM_APPL_DATA) BlockId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  *BlockId = DEM_ZERO;
  if (DEM_NVDATA_EVENT_MEMORY_ID == NvDataId)
  {
    switch(DTCOrigin)
    {
    /* @Trace: Dem_SUD_API_11899 */
    #if (DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11900 */
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
       /* polyspace<RTE:UNR:Not a defect:No action planned>
        * If-condition always evaluates to true. Avoid the runtime error of the
        * polyspace */
      /* @Trace: Dem_SUD_API_11883 */
      if (MemLocation < Dem_Num_Of_Primary_EventMemory_NvBlockId)
      {
        /* @Trace: Dem_SUD_API_11884 */
        *BlockId = Dem_PrimaryEventMemoryNvmBlockId[MemLocation];
        LddRetVal = E_OK;
      }
      break;
    #endif
      /* @Trace: Dem_SUD_API_11885 */
    #if (DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11886 */
    DEM_DTCORGIN_USER_DEFINED_CASE
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true. Avoid the runtime error of the
       * polyspace */
      /* @Trace: Dem_SUD_API_11887 */
      if (MemLocation < DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID)
      {
        /* @Trace: Dem_SUD_API_11888 */
        *BlockId = Dem_UserDefinedEventMemoryNvmBlockId[MemLocation];
        LddRetVal = E_OK;
      }
      break;
    #endif

    #if (DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true. Avoid the runtime error of the
       * polyspace */
      if (MemLocation < Dem_Num_Of_Permanent_EventMemory_NvBlockId)
      {
        *BlockId = Dem_PermanentEventMemoryNvmBlockId[MemLocation];
        LddRetVal = E_OK;
      }
      break;
    #endif
     /* @Trace: Dem_SUD_API_11889 */
    #if (DEM_NUM_OF_MIRROR_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11890 */
    case DEM_DTC_ORIGIN_MIRROR_MEMORY:
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true. Avoid the runtime error of the
       * polyspace */
      /* @Trace: Dem_SUD_API_11891 */
      if (MemLocation < DEM_NUM_OF_MIRROR_EVENTMEMORY_NVBLOCKID)
      {
        /* @Trace: Dem_SUD_API_11892 */
        *BlockId = Dem_MirrorEventMemoryNvmBlockId[MemLocation];
        LddRetVal = E_OK;
      }
      break;
    #endif

    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * Default switch clause is unreachable. switch-expression */
    default :
      DEM_UNUSED(MemLocation);
      break;
    }
  }
  else if (DEM_NVDATA_ALL_EVENT_STATUS_ID == NvDataId)
  {
    /* @Trace: Dem_SUD_API_11882 */
    #if defined(DEM_NVM_BLK_ID_EVENT_STATUS)
    /* @Trace: Dem_SUD_API_11893 */
    #if (DEM_NVM_BLK_ID_EVENT_STATUS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11894 */
    *BlockId = Dem_EventStatusNvRamBlkId;
    LddRetVal = E_OK;
    #endif
    #endif
  }
  else if (DEM_NVDATA_GENERIC_NVRAM_DATA_ID == NvDataId)
  {
    /* @Trace: Dem_SUD_API_11896 */
    #if defined(DEM_NVM_BLK_ID_NON_VOLATILE_DATA)
    /* @Trace: Dem_SUD_API_11897 */
    #if (DEM_NVM_BLK_ID_NON_VOLATILE_DATA > DEM_ZERO)
    /* @Trace: Dem_SUD_API_11898 */
    *BlockId = Dem_NonVolatileDataBlkId;
    LddRetVal = E_OK;
    #endif
    #endif
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition evaluates to true or false according to configuration */
  {
    /* @Trace: Dem_SUD_API_11895 */
    /* Nothing to do */
  }

  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_ReadNonVolatileData                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Read the stored data from nv block                  **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : NvDataId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_ReadNonVolatileData(
  const Dem_NvDataIdType NvDataId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  switch(NvDataId)
  {
    case DEM_NVDATA_ALL_EVENT_STATUS_ID:
      #ifdef DEM_NVM_BLK_ID_EVENT_STATUS    
      if (E_OK ==
            NvM_ReadBlock(Dem_EventStatusNvRamBlkId, &Dem_EventStatusNvRamData))
      {
        /* @Trace: Dem_SUD_API_11879 */
        /* Write request is accepted. */
        LddRetVal = E_OK;
      }
      else
      {
       /* @Trace: Dem_SUD_API_11880 */
        LddRetVal = DEM_E_PENDING;
      }
      #else
      /* @Trace: Dem_SUD_API_11881 */
      /* returns E_NOT_OK to initialize event memory */
      LddRetVal = E_NOT_OK;
      #endif

      break;
   case DEM_NVDATA_GENERIC_NVRAM_DATA_ID:
      #ifdef DEM_NVM_BLK_ID_NON_VOLATILE_DATA    
      if (E_OK == NvM_ReadBlock(Dem_NonVolatileDataBlkId, &Dem_NonVolatileData))
      {
        /* Write request is accepted. */
        /* @Trace: Dem_SUD_API_11877 */
        LddRetVal = E_OK;
      }
      else
      {
        /* @Trace: Dem_SUD_API_11876 */
        LddRetVal = DEM_E_PENDING;
      }
      #else
      /* @Trace: Dem_SUD_API_11878 */
      /* returns E_NOT_OK to initialize event memory */
      LddRetVal = E_NOT_OK;
      #endif
      
      break;
     
    /* case Xxx_ID */
    /* case Yyy_ID */
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * Default switch clause is unreachable. switch-expression */
    default:
      /* @Trace: Dem_SUD_API_11875 */
      /* Do Nothing */
      break;
  }
   
  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_WriteNonVolatileData                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Write the data to nv block                          **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : NvDataId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_WriteNonVolatileData(
  const Dem_NvDataIdType NvDataId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  NvM_RequestResultType LddNvResult = NVM_REQ_PENDING;
 
  switch(NvDataId)
  {
    case DEM_NVDATA_ALL_EVENT_STATUS_ID:
      #ifdef DEM_NVM_BLK_ID_EVENT_STATUS
      /* @Trace: Dem_SUD_API_11869 */
      if (E_OK == NvM_GetErrorStatus(Dem_EventStatusNvRamBlkId, &LddNvResult))
      {
        /* polyspace<MISRA-C:13.7:Not a defect:No action planned>
         * This is output parameter of NvM Api */
        if (NVM_REQ_PENDING != LddNvResult)
        {
          if (E_OK ==
                NvM_WriteBlock(
                    Dem_EventStatusNvRamBlkId, &Dem_EventStatusNvRamData))
          {
            /* @Trace: Dem_SUD_API_11871 */
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_11870 */
            LddRetVal = DEM_E_PENDING;
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_11868 */
          LddRetVal = DEM_E_PENDING;
        }
      } 
      #else
      /* @Trace: Dem_SUD_API_11867 */
      DEM_UNUSED(LddNvResult);
      /* returns E_NOT_OK to initialize event memory */
      LddRetVal = E_NOT_OK;
      #endif
      break;

    case DEM_NVDATA_GENERIC_NVRAM_DATA_ID:
      #ifdef DEM_NVM_BLK_ID_NON_VOLATILE_DATA
    	/* @Trace: Dem_SUD_API_11873 */
      if (E_OK == NvM_GetErrorStatus(Dem_NonVolatileDataBlkId, &LddNvResult))
      {
        /* polyspace<MISRA-C:13.7:Not a defect:No action planned>
         * This is output parameter of NvM Api */
        if (NVM_REQ_PENDING != LddNvResult)
        { 
          if (E_OK ==
                NvM_WriteBlock(Dem_NonVolatileDataBlkId, &Dem_NonVolatileData))
          {
            /* @Trace: Dem_SUD_API_11866 */
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_11865 */
            LddRetVal = DEM_E_PENDING;
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_11874 */
          LddRetVal = DEM_E_PENDING;
        }
      } 
      #else
      /* @Trace: Dem_SUD_API_11872 */
      DEM_UNUSED(LddNvResult);
      /* returns E_NOT_OK to initialize event memory */
      LddRetVal = E_NOT_OK;
      #endif
      break;
      
    /* case Xxx_ID */
    /* case Yyy_ID */
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * Default switch clause is unreachable. switch-expression */
    default:
      /* @Trace: Dem_SUD_API_11864 */
      /* Do Nothing */
      break;
  }
   
  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_RequestNvmFinishJobOnDTCOrigin           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Wait until writing jobs are finished                **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : Dem_DTCOriginType DTCOrigin                         **
 **                       uint8 Filter                                        **
 **                       boolean Directio                                    **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_BSW_00301
 */
#if ((DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > DEM_ZERO) || \
     (DEM_NUM_OF_USERDEFINED_EVENTMEMORY_NVBLOCKID > DEM_ZERO) )
static FUNC(boolean, DEM_CODE) Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
  const Dem_DTCOriginType DTCOrigin,
  const uint8 Filter,
  const boolean Direction)
{
  boolean LblPending = DEM_FALSE;

  NvM_BlockIdType LddBlockId = DEM_ZERO;
  NvM_RequestResultType LddNvDataResult = NVM_REQ_OK;
  
  Dem_NumOfEventMemoryEntryType LddMemLoc;
  /* @Trace: Dem_SUD_API_11857 */
  for (LddMemLoc = DEM_ZERO;
       LddMemLoc < Dem_SizeOfEventMemory[DTCOrigin];
       LddMemLoc++)
  {
    /* @Trace: Dem_SUD_API_11858 */
    if ((boolean)DEM_TRUE ==
          Dem_EvMem_IsEvMemNvBlockStatusFilter(DTCOrigin, LddMemLoc, Filter))
    {      
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true  */
      /* @Trace: Dem_SUD_API_11859 */
      if (E_OK ==
            Dem_NvData_GetNvMBlockId(
                DEM_NVDATA_EVENT_MEMORY_ID, DTCOrigin, LddMemLoc, &LddBlockId))
      {
        LddNvDataResult = Dem_NvData_GetNvMErrorStatus(LddBlockId);
        if ((NVM_REQ_OK == LddNvDataResult) ||
            (NVM_REQ_BLOCK_SKIPPED == LddNvDataResult))
        {
          /* @Trace: Dem_SUD_API_11861 */
          Dem_EvMem_ClearEvMemNvBlockStatus(DTCOrigin, LddMemLoc, Filter);
        }
        else if (NVM_REQ_PENDING == LddNvDataResult)
        {
          /* Dcm will invoke NvM_GetErrorStatus on next mainfunction call
           * again */
          /* @Trace: Dem_SUD_API_11860 */
          LblPending = DEM_TRUE;
          break;
        }          
        else if (NVM_REQ_NV_INVALIDATED == LddNvDataResult) /* Read */
        {
          /* @Trace: Dem_SUD_API_11862 */
          /* At least one block is not written, event memory entry shall be
           * initialized. */
          Dem_EvMem_ClearEvMemNvBlockStatus(DTCOrigin, LddMemLoc, Filter);
        }      
        else 
        { 
          /* @Trace: Dem_SUD_API_11863 */
          /* if result is any fault, block will be skipped */
          DEM_REPORT_ERROR(DEM_MAINFUNCTION_SID, DEM_E_NODATAAVAILABLE);
          Dem_EvMem_ClearEvMemNvBlockStatus(DTCOrigin, LddMemLoc, Filter);
          Dem_EvMem_SetNvmResult(E_NOT_OK);
        }
      }
    } 
  } /* @else {} */ 

  DEM_UNUSED(Direction);
  
  /* Wait to read all event status from NvM */
  return LblPending;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_NvData_WaitNvmFinishJob                         **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Wait until writing jobs are finished (all blocks)   **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : uint8 Filter                                        **
 **                       boolean Direction                                   **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_BSW_00301
 */
FUNC(boolean, DEM_CODE) Dem_NvData_WaitNvmFinishJob(
  const uint8 Filter,
  const boolean Direction)
{
  boolean LblPending = DEM_FALSE;
  Dem_NvDataIdType LddIdx;
  /* @IF_REQ x 100, NOTE, @IF_REQ
   *
   * EventMemory[Num primary entry + num secondary entry...]
   * Regardles of DTCOrigin, only shall use MemLocation 
   */
  Dem_EvMem_SetNvmResult(E_OK);

  #if (DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
  LblPending =
      Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
          DEM_DTC_ORIGIN_PRIMARY_MEMORY, Filter,Direction);
  #endif

  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  #if (DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
  LblPending |=
      Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
          DEM_DTC_ORIGIN_PERMANENT_MEMORY, Filter,Direction);
  #endif
  #endif
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
  #if (DEM_NUM_OF_MIRROR_EVENTMEMORY_NVBLOCKID > DEM_ZERO)
  LblPending |=
      Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
          DEM_DTC_ORIGIN_MIRROR_MEMORY, Filter,Direction);
  #endif
  #endif
  for (LddIdx = DEM_ZERO; LddIdx < Dem_NumOfSupportedSingleNvBlocks; LddIdx++)
  {
    Dem_NvDataIdType LddDataId = Dem_DataIdOfSingleNvBlocks[LddIdx];
    /* @Trace: Dem_SUD_API_11852 */
    if ((boolean)DEM_TRUE ==
          Dem_EvMem_NonVolatieDataStatusFilter(LddDataId, Filter))
    {
      NvM_BlockIdType LddBlockId;
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition evaluates to true or false according to configuration */
      /* @Trace: Dem_SUD_API_11853 */
      if (E_OK ==
            Dem_NvData_GetNvMBlockId(
                LddDataId, DEM_ZERO, DEM_ZERO, &LddBlockId))
      {
        NvM_RequestResultType LddNvDataResult = NVM_REQ_OK;
        
        LddNvDataResult = Dem_NvData_GetNvMErrorStatus(LddBlockId);
        if ((NVM_REQ_OK == LddNvDataResult) ||
            (NVM_REQ_BLOCK_SKIPPED == LddNvDataResult))
        {
          /* @Trace: Dem_SUD_API_13310 */
          Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
        }
        else if (NVM_REQ_PENDING == LddNvDataResult)
        {
          /* @Trace: Dem_SUD_API_11854 */
          /* Dcm will invoke NvM_GetErrorStatus on next mainfunction call
           * again */
          LblPending = DEM_TRUE;
        }
        else if (NVM_REQ_NV_INVALIDATED == LddNvDataResult)
        {
          /* @Trace: Dem_SUD_API_11855 */
          /* At least one block is not written, event memory entry shall be
           * initialized. */
          Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
        }      
        else 
        { 
          /* @Trace: Dem_SUD_API_11856 */
          DEM_REPORT_ERROR(DEM_MAINFUNCTION_SID, DEM_E_NODATAAVAILABLE);
          /* if result is any fault, block will be skipped */
          Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
          Dem_EvMem_SetNvmResult(E_NOT_OK);
        }
      }
      /* @Unreachable code
      @else
      {
        @Dem_EvMem_ClearNonVolatieDataStatus(LddDataId, Filter);
      }
      */
    }
  }
  /* @Trace: Dem_SUD_API_11851 */
  DEM_UNUSED(Direction);

  /* Wait to read all event status from NvM */
  return LblPending;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_GetNvMErrorStatus                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Get the status of the block                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : NvM_BlockIdType BlockId                             **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : NvM_RequestResultType                               **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_BSW_00301
 */
FUNC(NvM_RequestResultType, DEM_CODE)
Dem_NvData_GetNvMErrorStatus(NvM_BlockIdType BlockId)
{
  NvM_RequestResultType LddNvStatus = NVM_REQ_OK;
  NvM_RequestResultType LddRetVal = NVM_REQ_NOT_OK;
  /* @Trace: Dem_SUD_API_11843 */
  if (DEM_ZERO != BlockId)
  {
    /* get status from NvM of DEM memory block */
    /* @Trace: Dem_SUD_API_11844 */
    if (E_OK == NvM_GetErrorStatus(BlockId, &LddNvStatus))
    {
      switch(LddNvStatus)
      {
      case NVM_REQ_OK:
        /* @Trace: Dem_SUD_API_11845 */
        LddRetVal = NVM_REQ_OK;
        break;
      case NVM_REQ_RESTORED_FROM_ROM:
        /* @Trace: Dem_SUD_API_11846 */
        LddRetVal = NVM_REQ_OK;
        break;
      case NVM_REQ_PENDING :
        /* @Trace: Dem_SUD_API_11847 */
        LddRetVal = NVM_REQ_PENDING;
        break;   
      case NVM_REQ_NV_INVALIDATED:
        /* @Trace: Dem_SUD_API_11848 */
        LddRetVal = NVM_REQ_NV_INVALIDATED;
      break; 
      
      #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
      case NVM_REQ_BLOCK_SKIPPED: /* Skpped NvMReadAll or NvMWriteAll */
        /* @Trace: Dem_SUD_API_11849 */
        LddRetVal = NVM_REQ_BLOCK_SKIPPED;
        break;
      #else
        /* NVM_REQ_NOT_OK : failed */
      #endif

      default:
        /* @Trace: Dem_SUD_API_11850 */
        /* NVM_REQ_REDUNDANCY_FAILED */
        /* NVM_REQ_NOT_OK : Failed */
        /* NVM_REQ_INTEGRITY_FAILED : Failed */
        /* NVM_REQ_CANCELED : N/A */
        LddRetVal = NVM_REQ_NOT_OK;
        break;
      }
    }
  }
  
  return LddRetVal;
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
