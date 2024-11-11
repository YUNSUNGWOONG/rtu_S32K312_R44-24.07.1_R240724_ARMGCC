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
**  SRC-MODULE: Os_Arch_MemPro.c                                              **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of memory protection specific functionality         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.0.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
**            5-Jul-2023    HJ.Kim       Jira    CP44-2457                    **
**           27-Jun-2023    HJ.Kim       Jira    CP44-1874                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> configured array index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:11.3:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:11.5:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:11.8:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:begin<MISRA-C3:18.4:Not a defect:Justify with annotations> Operators on pointer is used for better performance */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotaitons> Pointer not access out of array*/
/* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotations> This conversion cannot be modified to handle memory */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#include "Os_kernel.h"
#endif
#include "Os_Arch_Interrupt.h"    /* Os Interrupt header file */
#include "Os_Arch_Multicore.h"    /* Os Multi-core header file */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
#include "Os_Arch_Regs.h"
#include "Os_Arch_MemPro.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if(OS_MEMORY_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_EnableMPU(void);
static FUNC(void, OS_CODE) Os_DisableMPU(void);
#if(OS_APP_MEMBLK_CNT != OS_ZERO)
static FUNC(void, OS_CODE) Os_EnableMemBlock(ApplicationType LddAppId);
static FUNC(void, OS_CODE) Os_DisableMemBlock(ApplicationType LddAppId);
#endif
static FUNC(void, OS_CODE) Os_InitSpvsrMemBlock(void);
static FUNC(void, OS_CODE) Os_InitializeStackMemoryBlock(uint32 LulStackIndex);
static FUNC(os_en_mpu_region_size_t, OS_CODE) Os_ConvMpuRegion(uint32 LulSize);
static FUNC(void, OS_CODE) Os_SetMpuRegion(
                                                      const uint32 LuiRegionNumber, 
                                                      const uint32 LuiRegionBaseAddress, 
                                                      const uint32 LuiRegionSizeAndEnable);
#endif
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(AccessType, OS_CODE) Os_CheckMemoryRWPermission(uint8 LucStartIndex, 
                                                     uint8 LucEndIndex, 
                                                     uint32 LulTagetAddr, 
                                                     MemorySizeType LulSize);
FUNC(AccessType, OS_CODE) Os_CheckMemoryTrustedRWPermission(uint8 LucStartIndex, 
                                                     uint8 LucEndIndex, 
                                                     uint32 LulTagetAddr, 
                                                     MemorySizeType LulSize);
#endif

/***************************************************************************//**
 * Function Name        : Os_DisableAppInterrupts
 *
 * Service ID           : NA
 *
 * Description          : This function is called to Disable All interrupts of
 *                        current application.
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            Application Application ID
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaISRPriority
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
FUNC(void, OS_CODE) Os_DisableAppInterrupts (ApplicationType Application)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_PRIVATE_CONST)LpISRPriority;
  uint32 LucCount;
  LucCount = Os_ISR_Count;

  while(LucCount != OS_ZERO)
  {
    LucCount--;
    /* Take a pointer to the structure */
    LpISRPriority = &Os_GaaISRPriority[LucCount];
    /* Check if the interrupt is category 2 and it belongs to current
      application */
    if((LpISRPriority->ucISRType == OS_CAT2_ISR) &&
                                        (LpISRPriority->ddAppId == Application))
    {
      Os_IntSetDisable((uint32)(LpISRPriority->pICRAddress)
                                                         - OS_ARM_M_IRQ_IPR_START);
    }
  }
}
#endif

/***************************************************************************//**
 * Function Name        : Os_EnableAppInterrupts
 *
 * Service ID           : NA
 *
 * Description          : This function is called to Enable All interrupts of
 *                        current application.
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaISRPriority, Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
FUNC(void, OS_CODE) Os_EnableAppInterrupts (void)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_PRIVATE_CONST)LpISRPriority;
  uint32 LucCount;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get the current core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  LucCount = Os_ISR_Count;
  while(LucCount != OS_ZERO)
  {
    LucCount--;
    /* Take a pointer to the structure */
    LpISRPriority = &Os_GaaISRPriority[LucCount];
    /* Check if the interrupt is category 2 and it belongs to current
      application */
    if((LpISRPriority->ucISRType == OS_CAT2_ISR) &&
                           (LpISRPriority->ddAppId == Os_GddAppId[OS_CORE_ID]))
    {
      Os_IntSetEnable((uint32)(LpISRPriority->pICRAddress) -
                                                           OS_ARM_M_IRQ_IPR_START);
    }
  }
}
#endif

/*******************************************************************************
 * Function             : Os_EnableMPU
 *
 * Service ID           : NA
 *
 * Description          : This function is used to enable or disable MPU
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LblEnable : OS_TRUE - Enable, OS_FALSE - Disable
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if (OS_MEMORY_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_EnableMPU(void)
{
  /* polyspace:begin<MISRA-C3:D4.3,1.1:Not a defect:Justify with annotation> need to use assembly code*/
  /* Ensure all memory accesses are completed before new memory access is committed */
  __asm("dsb");

  /* Enable the MPU */
  OS_MPU.ulCtrl |= OS_MPU_CTRL_ENABLE_MSK;

  /* Ensure all memory accesses are completed before next instruction is executed */
  __asm("dsb");

  /* Flush the pipeline and ensure all previous instructions are completed before executing new instructions */
  __asm("isb");
  /* polyspace:end<MISRA-C3:D4.3,1.1:Not a defect:Justify with annotation> need to use assembly code*/
}
#endif

/*******************************************************************************
 * Function             : Os_DisableMPU
 *
 * Service ID           : NA
 *
 * Description          : This function is used to enable or disable MPU
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LblEnable : OS_TRUE - Enable, OS_FALSE - Disable
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if (OS_MEMORY_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_DisableMPU(void)
{
  /* Ensure all memory accesses are completed before new memory access is committed */
  /*polyspace:begin<MISRA-C3:D4.3,1.1:Not a defect:Justify with annotation> need to use assembly code*/
  __asm("dsb");

  /* Disable the MPU */
  OS_MPU.ulCtrl &= (~OS_MPU_CTRL_ENABLE_MSK);

  /* Ensure all memory accesses are completed before next instruction is executed */
  __asm("dsb");

  /* Flush the pipeline and ensure all previous instructions are completed before executing new instructions */
  __asm("isb");
   /*polyspace:end<MISRA-C3:D4.3,1.1:Not a defect:Justify with annotation> need to use assembly code*/
}
#endif

/***************************************************************************//**
 * Function Name        : Os_EnableMemBlock
 *
 * Service ID           : NA
 *
 * Description          : This function enables the MPU regions belonging to an
 *                        OS-Application
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddAppId    Id of an OS-Application
 *                                    (range : 0 ~ OS_APPLICATION_COUNT - 1)
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticApplication, Os_GaaStaticMemBlock
 *
 *                        Function(s) invoked    : __asm("dsb"), __asm("isb")
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if ((OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_MEMBLK_CNT != OS_ZERO))
static FUNC(void, OS_CODE) Os_EnableMemBlock(ApplicationType LddAppId)
{
  uint8 LucIndex;
  uint8 LucCount;
  uint8 LucMemBlkIdx;

  LucMemBlkIdx = Os_GaaStaticApplication[LddAppId].ucBaseMemBlockIndex;
  LucCount = Os_GaaStaticApplication[LddAppId].ucNoOfMemBlk;

  for(LucIndex = LucMemBlkIdx; LucIndex < (LucMemBlkIdx + LucCount); LucIndex++)
  {
    Os_SetMpuRegion(Os_GaaStaticMemBlock[LucIndex].ddRegionNumber, 
                    Os_GaaStaticMemBlock[LucIndex].ddRegionBaseAddress, 
                    Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable);
  }
}
#endif

/***************************************************************************//**
 * Function Name        : Os_DisableMemBlock
 *
 * Service ID           : NA
 *
 * Description          : This function disables the MPU regions belonging to
 *                        an OS-Application
 *
  * Sync/Async          : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddAppId    Id of an OS-Application
 *                                    (range : 0 ~ OS_APPLICATION_COUNT - 1)
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticApplication, Os_GaaStaticMemBlock
 *
 *                        Function(s) invoked    : __asm("dsb"), __asm("isb")
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if ((OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_MEMBLK_CNT != OS_ZERO))
static FUNC(void, OS_CODE) Os_DisableMemBlock(ApplicationType LddAppId)
{
  uint8 LucIndex;
  uint8 LucCount;
  uint8 LucMemBlkIdx;

  LucMemBlkIdx = Os_GaaStaticApplication[LddAppId].ucBaseMemBlockIndex;
  LucCount = Os_GaaStaticApplication[LddAppId].ucNoOfMemBlk;

  for(LucIndex = LucMemBlkIdx; LucIndex < (LucMemBlkIdx + LucCount); LucIndex++)
  {
    Os_SetMpuRegion(Os_GaaStaticMemBlock[LucIndex].ddRegionNumber, 
                    (Os_GaaStaticMemBlock[LucIndex].ddRegionBaseAddress), 
                    Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable & (~OS_MPU_RASR_ENABLE_MSK));
  }
}
#endif

/*******************************************************************************
 * Function             : Os_InitializeStackMemoryBlock
 *
 * Service ID           : NA
 *
 * Description          : This function is used to initialize MPU region of
 *                        the stack memory.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LulStackIndex    Index of stack info array
 *
 * @return              : void
 *
 * @pre                 : Address must be aligned 32byte
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        Os_ConvMpuRegion(), Os_SetMpuRegion()
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if(OS_MEMORY_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_InitializeStackMemoryBlock(uint32 LulStackIndex)
{
  Os_Reg32 LulRegionBaseAddress;
  Os_Reg32 LulRegionSizeAndEnable;
  os_en_mpu_region_size_t LddRegSize;
  uint32 LulStackSize;

  LulRegionBaseAddress = (Os_Reg32)Os_GaaStack[LulStackIndex].pStackArea;

  /* LulStackSize should be power of 2 */
  LulStackSize = Os_GaaStack[LulStackIndex].usStackSize * sizeof(Os_StackType);
  LddRegSize = Os_ConvMpuRegion(LulStackSize);

  LulRegionSizeAndEnable = ((uint32) LddRegSize |
                            (uint32) OS_MPU_ACCESS_P_FULL_ACCESS |
                            (uint32) OS_MPU_ATTR_NORM_MEM_WB |
                            (uint32) OS_MPU_INST_ACCESS_DIS |
                            (uint32) 0x0 |
                            (uint32) OS_MPU_ENABLE);

  Os_SetMpuRegion(OS_MPU_REGION_STACK, LulRegionBaseAddress, LulRegionSizeAndEnable);
}
#endif

/*******************************************************************************
 * Function             : Os_InitSpvsrMemBlock
 *
 * Service ID           : NA
 *
 * Description          : This service is used to Initialize and access
 *                        the supervisor memory block
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticMemBlock
 *
 *                        Function(s) invoked    :
 *                        Os_SetMpuRegion(), 
 *                        Os_EnableMPU(), Os_DisableMPU(), 
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if(OS_MEMORY_PROTECTION == STD_ON)
static FUNC(void, OS_CODE) Os_InitSpvsrMemBlock(void)
{
  uint8 LucIdx;

  for (LucIdx = 0u; LucIdx < Os_MemBlk_Count; LucIdx++)
  {
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "condition is depend on configuration" */
    if (Os_GaaStaticMemBlock[LucIdx].blEnabledOnStart == TRUE)
    {
      Os_SetMpuRegion(Os_GaaStaticMemBlock[LucIdx].ddRegionNumber, 
                      Os_GaaStaticMemBlock[LucIdx].ddRegionBaseAddress, 
                      Os_GaaStaticMemBlock[LucIdx].ddRegionSizeAndEnable);
    }
  }
}
#endif /* #if(OS_MEMORY_PROTECTION == STD_ON) */

/*******************************************************************************
 * Function             : Os_HandleMemoryBlock
 *
 * Service ID           : NA
 *
 * Description          : This service switch memory blocks for non-trusted
 *                        OS-Application
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LpStaticTask : Pointer of new Task struct
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticApplication, Os_GaaStaticMemBlock,
 *                        Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        Os_EnableMPU(),
 *                        Os_InitializeStackMemoryBlock()
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if(OS_MEMORY_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_HandleMemoryBlock(P2CONST(Tdd_Os_StaticTask,
                                              AUTOMATIC, OS_CONST) LpStaticTask)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Disable MPU */
  Os_DisableMPU();

  if(Os_GddPrevAppId[OS_CORE_ID] != LpStaticTask->ddAppId)
  {
    #if(OS_APP_MEMBLK_CNT != OS_ZERO)
    /* Clear the previously configured Memory Blocks */
    /* If current Application is non-trusted, disable used MPU regions */
    if (Os_GddPrevAppId[OS_CORE_ID] < Os_Trusted_Start_Indx)
    {
      Os_DisableMemBlock(Os_GddPrevAppId[OS_CORE_ID]);
    }

    /* Set the Memory Blocks for a newly executed Application */
    if (LpStaticTask->ddAppId < Os_Trusted_Start_Indx)
    {
      Os_EnableMemBlock(LpStaticTask->ddAppId);
    }
    #endif

    /* Update the application Id */
    Os_GddPrevAppId[OS_CORE_ID] = LpStaticTask->ddAppId;
  }

  /* If LddNewAppId is INVALID_OSAPPLICATION, User Stack is used */
  if (LpStaticTask->ddAppId != (ApplicationType)INVALID_OSAPPLICATION)
  {
    /* Switch stack memory block */
    Os_InitializeStackMemoryBlock(LpStaticTask->ucStackIndex);
  }

  /* Enable MPU */                                
  Os_EnableMPU();
} /* End of Os_HandleMemoryBlock(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   * OS_CONST) LpStaticTask) */
#endif /* End of if ((OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_MEMBLK_CNT !=
        *OS_ZERO)) */

/*******************************************************************************
 * Function             : Os_InitializeDedicatedMemBlock
 *
 * Service ID           : NA
 *
 * Description          : This function initializes dedicated memory blocks
 *                        during  StartOS
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_012}
 *
 * @ingroup               OS_CYTXXX_ESDD_008
 ******************************************************************************/
#if (OS_MEMORY_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_InitializeDedicatedMemBlock(void)
{
  #if(OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Initialize application id with invalid value */
  Os_GddAppId[OS_CORE_ID] = (ApplicationType)INVALID_OSAPPLICATION;
  #if (OS_TRUSTED_START_INDX != OS_ZERO)
  Os_GddPrevAppId[OS_CORE_ID] = (ApplicationType)INVALID_OSAPPLICATION; 
  #endif
  /* Enable MPU */
  Os_DisableMPU();

  /* Ensure all memory accesses are completed before new memory access is committed */
  __asm("dsb");

  /* Enables the default memory map */
  OS_MPU.ulCtrl |= OS_MPU_CTRL_PRIVDEFENA_MSK;

  /* Ensure all memory accesses are completed before next instruction is executed */
  __asm("dsb");

  /* Flush the pipeline and ensure all previous instructions are completed before executing new instructions */
  __asm("isb");

  /* Initialize Supervisor Memory Block */
  Os_InitSpvsrMemBlock();

  /* Diable MPU */
  Os_EnableMPU();
}
#endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_CheckMemoryAccessService
 *
 * Service ID           : NA
 *
 * Description          : This service returns the access rights of the Memory
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LddTaskID    Task or CAT2 ISR reference
 *                                     (range : 0 ~ OS_TASK_COUNT
 *                                                  + OS_CAT2_ISR_COUNT
 *                                                  + OS_CORE_COUNT - 1)
 * @param[in]             LddStartAddr Start of memory area
 *                                     (range : 0u ~ 0xFFFFFFFFu)
 * @param[in]             LulSize      Size of memory area
 *                                     (range : 0u ~ 0xFFFFFFFFu)
 *
 * @return              : AccessType
 *                        - OS_READ_ONLY
 *                        - OS_READ_WRITE
 *                        - OS_EXECUTE
 *
 * @pre                 : LddTaskID should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticMemBlock, Os_GaaStaticApplication,
 *                        Os_GaaStaticTask, Os_GaaStack, Os_GulOsAppSPBtm,
 *                        Os_GulOsAppSPTop, Os_GulUserSPBtm, Os_GulUserSPTop
 *
 *                        Function(s) invoked    :
 *                        Os_CheckMemoryRWPermission
 *
 * {Ref: SWR_OS_S32K14X_012}
 *
 * @ingroup               OS_S32K14X_ESDD_008
 ******************************************************************************/
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(AccessType, OS_CODE) Os_CheckMemoryAccessService(ObjectTypeType
         LddTaskID, MemoryStartAddressType LddStartAddr, MemorySizeType LulSize)
{
  P2CONST(Tdd_Os_Application, AUTOMATIC, OS_CONST) LpStaticApplication;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  uint32 LulStartAddr;
  AccessType LucReturnVal;
  uint32 LulStackTop;
  uint32 LulStackBtm;
  uint8 LucCount;
  uint8 LucMemBlkIdx;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get the core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LulStartAddr = (uint32)LddStartAddr;

  LpStaticTask = &Os_GaaStaticTask[LddTaskID];
  /* polyspace<RTE:IDP: Not a defect : Justify with annotations > configured memory access index */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
  LpStaticApplication = &Os_GaaStaticApplication[LpStaticTask->ddAppId];

  /* Check if the application is Trusted */
  /* polyspace<RTE:IDP: Not a defect : Justify with annotations > configured memory access index */

  /* Store the pointer to the stack area of the task in the local pointer */
  #if (OS_EVENT == STD_ON)
  if(LpStaticTask->usType == OS_TASK_EXTENDED)
  {
    /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
    /* polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> Pointer arithmatic used to achieve better throughput. */
    /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
    LulStackBtm = (uint32)(&Os_GaaStack[LpStaticTask->ucStackIndex].pStackArea[Os_GaaStack[LpStaticTask->ucStackIndex].usStackSize]);
    /* polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> Pointer arithmatic used to achieve better throughput. */
    /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
    LulStackTop = (uint32)Os_GaaStack[LpStaticTask->ucStackIndex].pStackArea;
  }
  else /* BASIC TASK, CAT2 ISR */
  #endif
  {
    if(LpStaticTask->ddTaskId != OS_CORE_ID)
    {
      /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
      LulStackBtm = Os_GulOsAppSPBtm[LpStaticTask->ddAppId];
      LulStackTop = Os_GulOsAppSPTop[LpStaticTask->ddAppId];
    }
    else
    {
      LulStackBtm = Os_GulUserSPBtm[OS_CORE_ID];
      LulStackTop = Os_GulUserSPTop[OS_CORE_ID];
    }
  }

  /* Check if the memory belongs to the stack area */
  if ((LulStartAddr >= LulStackTop) && ((LulStartAddr + LulSize) < LulStackBtm))
  {
    /* Return Read Write access */
    /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
    LucReturnVal = (AccessType) OS_READ_WRITE | (AccessType) OS_STACKSPACE;
  }
  /* Else check Application Memory Blocks */
   /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
  else if (LpStaticApplication->ucType != OS_TRUSTED)
  {
  /*Check if the application is Trusted with protection*/
    LucMemBlkIdx = LpStaticApplication->ucBaseMemBlockIndex;
    LucCount = LpStaticApplication->ucNoOfMemBlk;

    LucReturnVal = Os_CheckMemoryRWPermission(LucMemBlkIdx, LucMemBlkIdx + LucCount, LulStartAddr, LulSize);

    if(LucReturnVal == NO_ACCESS)
    {
      LucReturnVal = Os_CheckMemoryRWPermission((uint8)OS_APP_MEMBLK_CNT, (uint8)OS_MEMBLK_COUNT, LulStartAddr, LulSize);
    }
  } /* End of if (LpStaticApplication->ucType != OS_TRUSTED) */
  else
  {
    /* Return Full access */
    LucReturnVal = Os_CheckMemoryTrustedRWPermission((uint8)OS_APP_MEMBLK_CNT, (uint8)OS_MEMBLK_COUNT, LulStartAddr, LulSize);
  }


  return (LucReturnVal);
} /* End of Os_CheckMemoryAccessService(ObjectTypeType LddTaskID,
   *MemoryStartAddressType LddStartAddr, MemorySizeType LulSize) */


/***************************************************************************//**
 * Function Name        : Os_CheckMemoryRWAccess
 *
 * Service ID           : NA
 *
 * Description          : This service returns the Read Write permission of the Memory
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LucStartIndex Start of memory area
 *                                      (range : 0u ~ OS_MEMBLK_COUNT)
 * @param[in]             LucEndIndex   Start of memory area
 *                                      (range : 0u ~ OS_MEMBLK_COUNT)
 * @param[in]             LulTagetAddr  Start of memory area
 *                                      (range : 0u ~ 0xFFFFFFFFu)
 * @param[in]             LulSize       Size of memory area
 *                                      (range : 0u ~ 0xFFFFFFFFu)
 *
 * @return              : AccessType
 *                        - OS_READ_ONLY
 *                        - OS_READ_WRITE
 *                        - NO_ACCESS
 *
 * @pre                 : LddTaskID should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticMemBlock
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K14X_012}
 *
 * @ingroup               OS_S32K14X_ESDD_008
 ******************************************************************************/
FUNC(AccessType, OS_CODE) Os_CheckMemoryRWPermission(uint8 LucStartIndex, 
                                                     uint8 LucEndIndex, 
                                                     uint32 LulTagetAddr, 
                                                     MemorySizeType LulSize)
{
  uint8 LucIndex;
  uint32 LulBaseAddr;
  uint32 LulMpuRegionSize;
  uint32 LulRegionAccess;
  uint32 LulBaseXNAddr;
  AccessType LucReturnVal = NO_ACCESS;
  uint32 LulMaxAddress = 0xFFFFFFFFu;

  for (LucIndex = LucStartIndex; LucIndex < LucEndIndex; LucIndex++)
  {
    LulBaseAddr = Os_GaaStaticMemBlock[LucIndex].ddRegionBaseAddress;
    /* MPU Region Size = 2^(x+1), x is a MPU region size bits */
    LulMpuRegionSize = Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable;
    LulMpuRegionSize = (LulMpuRegionSize & OS_MPU_RASR_SIZE_MSK) >> 1;
    if(LulMpuRegionSize == OS_MPU_MAX_SIZE_MSK)
    {
      LulMpuRegionSize = OS_MPU_MAX_SIZE;
    }
    else
    {
      LulMpuRegionSize = (uint32)1 << (LulMpuRegionSize + 1u);
    }

    /* Check if target size and MPU region size are overflow */
    if (((LulMaxAddress - LulSize) >= LulTagetAddr) && ((LulMaxAddress - LulMpuRegionSize) >= LulBaseAddr))
    {
      /* Check if the memory belongs to the descriptor configured */
      if ((LulTagetAddr >= LulBaseAddr) && ((LulTagetAddr + LulSize) < (LulBaseAddr + LulMpuRegionSize)))
      {
        LulRegionAccess = Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable;
        LulRegionAccess &= OS_MPU_RASR_AP_MSK;
        if (LulRegionAccess == (uint32) OS_MPU_ACCESS_P_FULL_ACCESS)
        {
          LucReturnVal = OS_READ_WRITE;
        }
        else if ((LulRegionAccess ==  (uint32) OS_MPU_ACCESS_P_PRIV_RW_USER_RO) ||
                (LulRegionAccess == (uint32) OS_MPU_ACCESS_P_RO))
        {
          LucReturnVal = OS_READ_ONLY;
        }
        else
        {
          /* continue loop */
        }
        if (LucReturnVal != NO_ACCESS)
        {
          LulBaseXNAddr = Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable;
          LulBaseXNAddr = LulBaseXNAddr & OS_MPU_RASR_XN_MSK;
          if(LulBaseXNAddr == (uint32)OS_ZERO)
          {
            LucReturnVal |= (AccessType)OS_EXECUTE;
          }
          break;
        }
      }
    }
  }
  return LucReturnVal;
}

/***************************************************************************//**
 * Function Name        : Os_CheckMemoryRWAccess
 *
 * Service ID           : NA
 *
 * Description          : This service returns the Read Write permission of the Memory
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LucStartIndex Start of memory area
 *                                      (range : 0u ~ OS_MEMBLK_COUNT)
 * @param[in]             LucEndIndex   Start of memory area
 *                                      (range : 0u ~ OS_MEMBLK_COUNT)
 * @param[in]             LulTagetAddr  Start of memory area
 *                                      (range : 0u ~ 0xFFFFFFFFu)
 * @param[in]             LulSize       Size of memory area
 *                                      (range : 0u ~ 0xFFFFFFFFu)
 *
 * @return              : AccessType
 *                        - OS_READ_ONLY
 *                        - OS_READ_WRITE
 *                        - NO_ACCESS
 *
 * @pre                 : LddTaskID should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticMemBlock
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K14X_012}
 *
 * @ingroup               OS_S32K14X_ESDD_008
 ******************************************************************************/
FUNC(AccessType, OS_CODE) Os_CheckMemoryTrustedRWPermission(uint8 LucStartIndex, 
                                                     uint8 LucEndIndex, 
                                                     uint32 LulTagetAddr, 
                                                     MemorySizeType LulSize)
{
  uint8 LucIndex;
  uint32 LulBaseAddr;
  uint32 LulMpuRegionSize;
  uint32 LulRegionAccess;
  uint32 LulBaseXNAddr;
  AccessType LucReturnVal = NO_ACCESS;
  uint32 LulMaxAddress = 0xFFFFFFFFu;

  for (LucIndex = LucStartIndex; LucIndex < LucEndIndex; LucIndex++)
  {
    LulBaseAddr = Os_GaaStaticMemBlock[LucIndex].ddRegionBaseAddress;
    /* MPU Region Size = 2^(x+1), x is a MPU region size bits */
    LulMpuRegionSize = Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable;
    LulMpuRegionSize = (LulMpuRegionSize & OS_MPU_RASR_SIZE_MSK) >> 1;
    if(LulMpuRegionSize == OS_MPU_MAX_SIZE_MSK)
    {
      LulMpuRegionSize = OS_MPU_MAX_SIZE;
    }
    else
    {
      LulMpuRegionSize = (uint32)1 << (LulMpuRegionSize + 1u);
    }
    
    /* Check if target size and MPU region size are overflow */
    if (((LulMaxAddress - LulSize) >= LulTagetAddr) && ((LulMaxAddress - LulMpuRegionSize) >= LulBaseAddr))
    {
    /* Check if the memory belongs to the descriptor configured */
      if ((LulTagetAddr >= LulBaseAddr) && ((LulTagetAddr + LulSize) < (LulBaseAddr + LulMpuRegionSize)))
      {
        LulRegionAccess = Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable;
        LulRegionAccess &= OS_MPU_RASR_AP_MSK;
        if ((LulRegionAccess == (uint32)OS_MPU_ACCESS_P_PRIV_RW) ||
            (LulRegionAccess == (uint32)OS_MPU_ACCESS_P_PRIV_RW_USER_RO) ||
            (LulRegionAccess == (uint32)OS_MPU_ACCESS_P_FULL_ACCESS))
        {
          LucReturnVal = OS_READ_WRITE;
        }
        else if ((LulRegionAccess == (uint32)OS_MPU_ACCESS_P_PRIV_RO) ||
                (LulRegionAccess == (uint32)OS_MPU_ACCESS_P_RO))
        {
          LucReturnVal = OS_READ_ONLY;
        }
        else
        {
          /* continue loop */
        }
        if (LucReturnVal != NO_ACCESS)
        {
          LulBaseXNAddr = Os_GaaStaticMemBlock[LucIndex].ddRegionSizeAndEnable;
          LulBaseXNAddr = LulBaseXNAddr & OS_MPU_RASR_XN_MSK;
          if(LulBaseXNAddr == (uint32)OS_ZERO)
          {
            LucReturnVal |= (AccessType)OS_EXECUTE;
          }
          break;
        }
      }
    }
  }
  return LucReturnVal;
}
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

#if (OS_MEMORY_PROTECTION == STD_ON)
/* polyspace +2 CODE-METRIC:FXLN [Justified:Low] "The display of specific values of the number of Executable Lines is justified" */
/* polyspace +1 CODE-METRIC:LEVEL [Justified:Low] "The display of specific values of the number of Executable Lines is justified" */
static FUNC(os_en_mpu_region_size_t, OS_CODE) Os_ConvMpuRegion(uint32 LulSize)
{
  os_en_mpu_region_size_t LddRegSize = OS_MPU_SIZE_2B;

  switch(LulSize)
  {
    case 0x00000020u:
      LddRegSize = OS_MPU_SIZE_32B;
      break;
    case 0x00000040u:
      LddRegSize = OS_MPU_SIZE_64B;
      break;
    case 0x00000080u:
      LddRegSize = OS_MPU_SIZE_128B;
      break;
    case 0x00000100u:
      LddRegSize = OS_MPU_SIZE_256B;
      break;
    case 0x00000200u:
      LddRegSize = OS_MPU_SIZE_512B;
      break;
    case 0x00000400u:
      LddRegSize = OS_MPU_SIZE_1KB;
      break;
    case 0x00000800u:
      LddRegSize = OS_MPU_SIZE_2KB;
      break;
    case 0x00001000u:
      LddRegSize = OS_MPU_SIZE_4KB;
      break;
    case 0x00002000u:
      LddRegSize = OS_MPU_SIZE_8KB;
      break;
    case 0x00004000u:
      LddRegSize = OS_MPU_SIZE_16KB;
      break;
    case 0x00008000u:
      LddRegSize = OS_MPU_SIZE_32KB;
      break;
    case 0x00010000u:
      LddRegSize = OS_MPU_SIZE_64KB;
      break;
    case 0x00020000u:
      LddRegSize = OS_MPU_SIZE_128KB;
      break;
    case 0x00040000u:
      LddRegSize = OS_MPU_SIZE_256KB;
      break;
    case 0x00080000u:
      LddRegSize = OS_MPU_SIZE_512KB;
      break;
    case 0x00100000u:
      LddRegSize = OS_MPU_SIZE_1MB;
      break;
    case 0x00200000u:
      LddRegSize = OS_MPU_SIZE_2MB;
      break;
    case 0x00400000u:
      LddRegSize = OS_MPU_SIZE_4MB;
      break;
    case 0x00800000u:
      LddRegSize = OS_MPU_SIZE_8MB;
      break;
    case 0x01000000u:
      LddRegSize = OS_MPU_SIZE_16MB;
      break;
    case 0x02000000u:
      LddRegSize = OS_MPU_SIZE_32MB;
      break;
    case 0x04000000u:
      LddRegSize = OS_MPU_SIZE_64MB;
      break;
    case 0x08000000u:
      LddRegSize = OS_MPU_SIZE_128MB;
      break;
    case 0x10000000u:
      LddRegSize = OS_MPU_SIZE_256MB;
      break;
    case 0x20000000u:
      LddRegSize = OS_MPU_SIZE_512MB;
      break;
    case 0x40000000u:
      LddRegSize = OS_MPU_SIZE_1GB;
      break;
    case 0x80000000u:
      LddRegSize = OS_MPU_SIZE_2GB;
      break;
    default :
      LddRegSize = OS_MPU_SIZE_4GB;
      break;
  }

  return LddRegSize;
}

static FUNC(void, OS_CODE) Os_SetMpuRegion(
                                                      const uint32 LuiRegionNumber, 
                                                      const uint32 LuiRegionBaseAddress, 
                                                      const uint32 LuiRegionSizeAndEnable)
{
  volatile os_en_mpu_status_t LddReturnvalue = OS_MPU_SUCCESS;

  if (OS_MPU.ulType == 0x0u)
  {
    LddReturnvalue = OS_MPU_FAILURE;
  }

  if (LddReturnvalue == OS_MPU_SUCCESS)
  {
    if (LuiRegionNumber >= OS_MPU_MAX_NUM)
    {
      LddReturnvalue = OS_MPU_FAILURE;
    }
  }

  if (LddReturnvalue == OS_MPU_SUCCESS)
  {
    /* polyspace:begin<MISRA-C3:D4.3:Not a defect:Justify with annotations> need to use assembly code */
    /* polyspace:begin<MISRA-C3:1.1:Not a defect:Justify with annotations> need to use assembly code */
    /* Ensure all memory accesses are completed before new memory access is committed */
    __DMB();

    /* Select which MPU region to configure */
    OS_MPU.ulRnr = LuiRegionNumber;

    /* Configure  region  base  address register */
    /* VALID and REGION field of RBAR register will be 0 since this function sets RNR register manually. */
    OS_MPU.ulRbar = (LuiRegionBaseAddress & OS_MPU_RBAR_ADDR_MSK);

    /* Configure region attribute and size register */
    OS_MPU.ulRasr = LuiRegionSizeAndEnable;

    /* Ensure all memory accesses are completed before next instruction is executed */
    __asm("dsb");

    /* Flush the pipeline and ensure all previous instructions are completed before executing new instructions */
    __asm("isb");
    /* polyspace:end<MISRA-C3:D4.3> */
    /* polyspace:end<MISRA-C3:1.1> */
  }
}
#endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_MEMBLK_CNT != OS_ZERO) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END(MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotations> This conversion cannot be modified to handle memory */
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<RTE:OBAI:Not a defect:Justify with annotations> configured array index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:11.3:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:11.5:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:11.8:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:end<MISRA-C3:18.4:Not a defect:Justify with annotations> Operators on pointer is used for better performance */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotaitons> Pointer not access out of array*/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
