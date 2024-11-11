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
**  SRC-MODULE: Os_Ram.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Declaration of the global variables.                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**            9-Jun-2023   HJ.Kim           Jira CP44-2325                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Ram.h"               /* Os Ram header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"
/** Variable for OS Global Initialization */
VAR(boolean, OS_VAR) Os_GblOsInitialized[OS_CORE_COUNT];
/** Boolean Variable for Interrupt Lock */
VAR(boolean, OS_VAR) Os_GblISRLock[OS_CORE_COUNT];
/** Variable for OS Global Initialization for Multi Core */
VAR(boolean, OS_VAR) Os_GblStartOs[OS_CORE_COUNT];
/** This global Variable used to check that 'wait' instruction is not called */
VAR(boolean, OS_VAR) Os_GblBeforeHalt[OS_CORE_COUNT];
VAR(boolean, OS_VAR) Os_GblInterCoreInt[OS_CORE_COUNT];
VAR(boolean, OS_VAR) Os_GblCoreShutdown[OS_CORE_COUNT];
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
/** Flag for Application Mode */
VAR(boolean, OS_VAR) Os_GblAppModeCheck;
/** Variable to hold Global Shutdown */
VAR(boolean, OS_VAR) Os_GblShutdownFlag[OS_CORE_COUNT];
#endif /*OS_MULTICORE == STD_ON */
#if (OS_TIMING_PROTECTION == STD_ON)
VAR(boolean, OS_VAR) Os_GblTPSFlag[OS_CORE_COUNT];
#endif
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
VAR(boolean, OS_VAR) Os_GblTimeViolationDelayed[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"
/** Nesting Variable for Interrupt Lock */
VAR(Os_IsrLockType, OS_VAR) Os_GddISRLock[OS_CORE_COUNT];
/** Nesting Variable for CAT2 interrupt Lock */
VAR(Os_IsrLockType, OS_VAR) Os_GddISR2Lock[OS_CORE_COUNT];
/** Variable to hold running Mode */
VAR(AppModeType, OS_VAR) Os_GddAppMode;
/** This global variable used to save Idle Task ID. */
VAR(TaskType, OS_VAR) Os_GddIdleTaskId[OS_CORE_COUNT];
#if (OS_MULTICORE == STD_ON)
/** Variable for synchronization between cores */
volatile VAR(uint8, OS_VAR) Os_GucSync1;
/** Variable for number of active cores */
VAR(uint8, OS_VAR) Os_GucActivateCore;
#endif /*OS_MULTICORE == STD_ON */
#if(OS_APPLICATION == STD_ON)
VAR(ApplicationType, OS_VAR) Os_GddAppId[OS_CORE_COUNT];
VAR(ApplicationType, OS_VAR) Os_GddCurAppId[OS_CORE_COUNT];
#endif
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
VAR(uint8, OS_VAR) Os_GucTrustedFuncCount[OS_CORE_COUNT];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
VAR(uint8, OS_VAR) Os_GucExecFail[OS_CORE_COUNT];
/** To save Task or ISR id when TPS trap occured in kernel mode */
VAR(TaskType, OS_VAR) Os_GddFaultyTask[OS_CORE_COUNT];
#endif /* OS_TIMING_PROTECTION == STD_ON */
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"
VAR(uint16, OS_VAR) Os_GusCallevelCheck[OS_CORE_COUNT];

#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

#if (OS_TIMING_PROTECTION == STD_ON)
VAR(uint32, OS_VAR) Os_GulBudgetTimerCount[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulTFTimerCount[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
VAR(Tdd_Os_Task, OS_VAR) Os_GaaTask
    [OS_TASK_COUNT + OS_CAT2_ISR_COUNT + OS_CORE_COUNT];
/** Variable to hold link lists */
VAR(TaskType, OS_VAR) Os_GaaLinkIndex
    [OS_TASK_COUNT + OS_CAT2_ISR_COUNT + OS_CORE_COUNT];
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
/** Variable to hold running Task */
P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) Os_GpStaticTask[OS_CORE_COUNT];
/** Variable to hold running link lists */
P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR)Os_GpLinkTask[OS_CORE_COUNT];
VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendOs[OS_CORE_COUNT];
VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendAll[OS_CORE_COUNT];
/** Variable to check current Idle mode. */
VAR(IdleModeType, OS_VAR) Os_GddCurIdleMode[OS_CORE_COUNT];
#if (OS_ERROR_HOOK == STD_ON)
VAR(Tdd_Os_ServiceCall, OS_VAR) Os_GddServiceCall[OS_CORE_COUNT];
#endif /* End of if (OS_ERROR_HOOK == STD_ON) */
#if (OS_COUNTER_COUNT != OS_PRE_ZERO)
VAR(Tdd_Os_Counter, OS_VAR) Os_GaaCounter[OS_COUNTER_COUNT];
#endif /*OS_COUNTER_COUNT != OS_PRE_ZERO*/
#if (OS_APPLICATION == STD_ON)
/** Variable to dynamic Application Variable */
VAR(Tdd_Os_ApplicationData, OS_VAR) Os_GaaApplication[OS_APPLICATION_COUNT];
#endif /* OS_APPLICATION == STD_ON*/
#if (OS_MULTICORE == STD_ON)
/** Array to hold dynamic Variable for cores */
VAR(Tdd_Os_Core, OS_VAR) Os_GaaCore[OS_CORE_COUNT];
#endif /*OS_MULTICORE == STD_ON*/
#if (OS_TIMING_PROTECTION == STD_ON)
/** Variable to hold running schedule Wdg */
P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR)
                                              Os_GpSchedWatchdog[OS_CORE_COUNT];
/** Variable to hold schedule Wdg */
VAR(Tdd_Os_TPWatchdog, OS_VAR) Os_GaaRunningWdg[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Os_MemCopy                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to copy data from source       **
**                        memory to destination memory                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : dstAddr                                             **
**                        srcAddr                                             **
**                        cntData                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dstAddr                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
FUNC(void, OS_CODE) Os_MemCopy(void *dstAddr, const void *srcAddr, const uint32 cntData)
{
  uint8 *dst = NULL_PTR;
  const uint8 *src;
  uint32 len;
  uint32 cnt;
  uint32 tmpData;
  uint32 tmpLData;
  uint32 tmpRData;
  uint8 dstDiff;
  uint8 srcDiff;

  cnt = cntData;

  if((dstAddr == srcAddr) || (cnt == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_55501 */
    /* Do nothing */
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_55502 */
    /* polyspace +3 MISRA-C3:11.5 [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
    /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory set." */
    dst = (uint8 *)dstAddr;
    src = (const uint8 *)srcAddr;
    /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The integer value represents the misalignment. The value is used for 4bytes-alignment." */
    dstDiff = (uint8)((uint32)dst & (uint8) OS_THREE); /* & 0x00000003 */

    /* Copy data by 1byte size until destination address is 4bytes-aligned */
    if((cnt >= OS_FOUR) && (dstDiff != OS_ZERO))
    {
      /* @Trace: SafeOs_SUD_API_55503 */
      len = (uint32)OS_FOUR - dstDiff;
      cnt = cnt - len;
      while(len != OS_ZERO)
      {
        /* @Trace: SafeOs_SUD_API_55504 */
        /* polyspace +2 DEFECT:OUT_BOUND_PTR [Justified:Low] "Pointer not access out of array." */
        /* polyspace +1 MISRA-C3:18.1 CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Medium] "Pointer not access out of array." */
        *dst = *src;
        dst++;
        src++;
        len--;
      }
    }
    /* @Trace: SafeOs_SUD_API_55505 */
    /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The integer value represents the misalignment. The value is used for 4bytes-alignment." */
    srcDiff = (uint8)((uint32)src & (uint8) OS_THREE); /* & 0x00000003 */

    /* Make 4bytes data from not 4bytes-aligned source address and Copy the data if source address is not 4bytes-aligned */
    if((cnt >= OS_FOUR) && (srcDiff != OS_ZERO))
    {
      /* Byte copy for first 4 bytes - To avoid accessing the address out of range */
      for(len = OS_FOUR; len != OS_ZERO; len--)
      {
        /* @Trace: SafeOs_SUD_API_55506 */
        *dst = *src;
        dst++;
        src++;
        cnt--;
      }

      if(cnt >= OS_EIGHT)
      {
        /* @Trace: SafeOs_SUD_API_55507 */
        /* polyspace +3 DEFECT:OUT_BOUND_PTR [Justified:Low] "Pointer not access out of array." */
        /* polyspace +2 MISRA-C3:18.1 CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Medium] "Pointer not access out of array." */
        /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
        tmpLData = OS_WORD_LEFTSIDE((*(const uint32 *)(src - srcDiff)), (OS_EIGHT * srcDiff));

        for(len = (cnt/OS_FOUR)-OS_ONE; len != OS_ZERO; len--)
        {
          /* @Trace: SafeOs_SUD_API_55508 */
          /* polyspace +3 DEFECT:OUT_BOUND_PTR [Justified:Low] "Pointer not access out of array." */
          /* polyspace +2 MISRA-C3:18.1 CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Medium] "Pointer not access out of array." */
          /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
          tmpData = *(const uint32 *)((src + OS_FOUR) - srcDiff);
          tmpRData = OS_WORD_RIGHTSIDE(tmpData, (OS_EIGHT * (OS_FOUR - srcDiff)));
          /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to store the value combined with L and R data" */
          *(uint32 *)dst = tmpLData | tmpRData;
          tmpLData = OS_WORD_LEFTSIDE(tmpData, (OS_EIGHT * srcDiff));

          /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
          dst += OS_FOUR;
          src += OS_FOUR;
          cnt -= OS_FOUR;
        }
      }

      /* Byte copy for last bytes */
      for(len = cnt; len != OS_ZERO; len--)
      {
        /* @Trace: SafeOs_SUD_API_55509 */
        /* polyspace +2 DEFECT:OUT_BOUND_PTR [Justified:Low] "Pointer not access out of array." */
        /* polyspace +1 MISRA-C3:18.1 CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Medium] "Pointer not access out of array." */
        *dst = *src;
        dst++;
        src++;
      }
    }
    else /* destination & source address is 4bytes-aligned */
    {
      /* Copy in OS_WRITESIZE units 
       * : Os_WriteSizeType and OS_WRITESIZE has MCU core dependency 
       *   So, those definitions are defined in Os_PortTypes.h */
      for(len = cnt / OS_WRITESIZE; len != OS_ZERO; len--)
      {
        /* @Trace: SafeOs_SUD_API_55510 */
        /* polyspace +3 DEFECT:OUT_BOUND_PTR [Justified:Low] "Pointer not access out of array." */
        /* polyspace +2 MISRA-C3:18.1 CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Medium] "Pointer not access out of array." */
        /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 [Justified:Low] "A cast used to achieve better throughput." */
        *(Os_WriteSizeType *)dst = *(const Os_WriteSizeType *)src;
        /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
        dst += OS_WRITESIZE;
        src += OS_WRITESIZE;
      }

      /* Copy remainder after copying OS_WRITESIZE units */
      for(len = cnt % OS_WRITESIZE; len != OS_ZERO; len--)
      {
        /* @Trace: SafeOs_SUD_API_55511 */
        /* polyspace +2 DEFECT:OUT_BOUND_PTR [Justified:Low] "Pointer not access out of array." */
        /* polyspace +1 MISRA-C3:18.1 CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Medium] "Pointer not access out of array." */
        *dst = *src;
        dst++;
        src++;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Os_MemSet                                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to set memory with a data      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : dstAddr                                             **
**                        data                                                **
**                        cntData                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dstAddr                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
FUNC(void, OS_CODE) Os_MemSet(void *dstAddr, const uint8 data, const uint32 cntData)
{
  uint8 *dst;
  uint32 len;
  uint32 cnt;
  uint8 dstDiff;
  Os_WriteSizeType writeData;
  Os_WriteSizeType tmpData;

  cnt = cntData;

  if((dstAddr == NULL_PTR) || (cnt == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_55601 */
    /* Do nothing */
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_55602 */
    /* polyspace +2 MISRA-C3:11.5 [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
    /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory set." */
    dst = (uint8 *)dstAddr;
    /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The integer value represents the misalignment. The value is used for 4bytes-alignment." */
    dstDiff = (uint8)((uint32)dst & (uint8)OS_THREE); /* & 0x00000003 */

    /* Copy data by 1byte size until it makes 4bytes-aligned */
    if((dstDiff != OS_ZERO) && (cnt >= OS_FOUR))
    {
      /* @Trace: SafeOs_SUD_API_55603 */
      len = (uint32)OS_FOUR - dstDiff;
      cnt = cnt - len;
      while(len != OS_ZERO)
      {
        /* @Trace: SafeOs_SUD_API_55604 */
        *dst = data;
        dst++;
        len--;
      }
    }

    /* Copy data by OS_WRITESIZE size */
    if(cnt >= OS_WRITESIZE)
    {
      /* @Trace: SafeOs_SUD_API_55605 */
      tmpData = (Os_WriteSizeType)data;
      writeData = tmpData;

      for(len = OS_ONE; len < OS_WRITESIZE; len++)
      {
        /* @Trace: SafeOs_SUD_API_55606 */
        tmpData = (tmpData << OS_EIGHT); 
        writeData |= tmpData;
      }

      /* Copy in OS_WRITESIZE units 
       * : Os_WriteSizeType and OS_WRITESIZE has MCU core dependency 
       *   So, those definitions are defined in Os_PortTypes.h */
      for(len = cnt / OS_WRITESIZE; len != OS_ZERO; len--)
      {
        /* @Trace: SafeOs_SUD_API_55607 */
        /* polyspace +3 DEFECT:OUT_BOUND_PTR [Not a defect:Low] "The pointers bound is checked." */
        /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */  
        /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 [Justified:Low] "A cast used to achieve better throughput." */
        *(Os_WriteSizeType *)dst = writeData;
        /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
        dst += OS_WRITESIZE;
      }
    }

    /* Copy remainder by 1byte size */
    for(len = cnt % OS_WRITESIZE; len != OS_ZERO; len--)
    {
      /* @Trace: SafeOs_SUD_API_55608 */
      /* polyspace +2 DEFECT:OUT_BOUND_PTR [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
      /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
      *dst = data;
      dst++;
    }
  }
}

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
