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
**  SRC-MODULE: Os_Config.c                                                   **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of constant specific functionality.                 **
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
** 1.3.0     26-Feb-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.1.0      8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"
#include "Os_Arch_Init.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_APPLICATION == STD_ON)
#include "Os_IocInternalTypes.h"
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Arch_MemPro.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* FIXME: Move to Common part. Remove unused variable */
/** This global const variable is used to define Application Mode Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(AppModeType, OS_CONST) Os_ApplMode_Count = (AppModeType)OS_APPLMODE_COUNT;
/** This global const variable is used to define Task Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(TaskType, OS_CONST) Os_Task_Count = (TaskType)OS_TASK_COUNT;
/** This global const variable is used to define Category 2 ISR Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ISRType, OS_CONST) Os_CAT2_ISR_Count = (ISRType)OS_CAT2_ISR_COUNT;
/** This global const variable is used to define Category 1 ISR Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ISRType, OS_CONST) Os_CAT1_ISR_Count = (ISRType)OS_CAT1_ISR_COUNT;
/** This global const variable is used to define All ISR Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ISRType, OS_CONST) Os_ISR_Count = (ISRType)OS_ISR_COUNT;
/** This global const variable is used to define Maximum CAT2 ISR Priority
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(uint16, OS_CONST) Os_CAT2_Max_Priority = (uint16)OS_CAT2_MAX_PRIORITY;
/** This global const variable is used to define Minimum CAT1 ISR Priority
 *  \n{Ref: SWR_OS_S32K31X_010} */
CONST(uint16, OS_CONST) Os_CAT1_Least_Priority = (uint16)OS_CAT1_LEAST_PRIORITY;
/** This global const variable is used to define Maximum CAT2 ISR Nesting
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ISRType, OS_CONST) Os_Max_Nest_Level = (ISRType)OS_MAX_NEST_LEVEL;
/** This global const variable is used to define Resource Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ResourceType, OS_CONST) OS_Resource_Count =
                                                (ResourceType)OS_RESOURCE_COUNT;
/** This global const variable is used to define Counter Count
 *  \n{Ref: SWR_OS_S32K31X_010} */
CONST(CounterType, OS_CONST) Os_Counter_Count = (CounterType)OS_COUNTER_COUNT;
/** This global const variable is used to define Alarm Count
 *  \n{Ref: SWR_OS_S32K31X_010} */
CONST(AlarmType, OS_CONST) Os_Alarm_Count = (AlarmType)OS_ALARM_COUNT;
/** This global const variable is used to define ScheduleTable Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ScheduleTableType, OS_CONST) Os_Schedule_Count =
                                           (ScheduleTableType)OS_SCHEDULE_COUNT;
/** This global const variable is used to define CPU Core Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(uint8, OS_CONST) Os_Core_Count = (uint8)OS_CORE_COUNT;
/** This global const variable is used to define Spinlock Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(SpinlockIdType, OS_CONST) Os_Spinlock_Count =
                                              (SpinlockIdType)OS_SPINLOCK_COUNT;
/** This global const variable is used to define IOC Callback Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(uint16, OS_CONST) Os_Ioc_Callback_Count = (uint16)OS_IOC_CALLBACK_COUNT;
/** This global const variable is used to define IOC Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(uint16, OS_CONST) Os_Ioc_Count = (uint16)OS_IOC_COUNT;
/** This global const variable is used to define OS-Application Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ApplicationType, OS_CONST) Os_Application_Count =
                                          (ApplicationType)OS_APPLICATION_COUNT;
/** Trusted OS Application With Protection Start index */
CONST(ApplicationType, OS_CONST) Os_Trusted_App_With_Protection_Start_Indx =
                     (ApplicationType)OS_TRUSTED_APP_WITH_PROTECTION_START_INDX;
/** This global const variable is used to define Trusted OS Applications start index
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(ApplicationType, OS_CONST) Os_Trusted_Start_Indx =
                                         (ApplicationType)OS_TRUSTED_START_INDX;
/** This global const variable is used to define Trusted Function Count
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(TrustedFunctionIndexType, OS_CONST) Os_Trusted_Func_Count =
                                (TrustedFunctionIndexType)OS_TRUSTED_FUNC_COUNT;
/** This global const variable is used to define Memory Block Count for Memory Protection
 *  \n{Ref: SWR_OS_S32K31X_010} */ 
CONST(uint16, OS_CONST) Os_App_MemBlk_Cnt = (uint16)OS_APP_MEMBLK_CNT;

#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Arch_MemPro.h"
/** Total number of Memory Blocks(MPU Regions)
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint32, OS_CONST) Os_MemBlk_Count = (uint32)OS_MEMBLK_COUNT;
#endif /*#if (OS_MEMORY_PROTECTION == STD_ON)*/

/** Total number of Queued IOC */
CONST(uint16, OS_CONST) Os_Ioc_Count_Queued = (uint16)OS_IOC_COUNT_QUEUED;
/** Total number of Unqueued IOC */
CONST(uint16, OS_CONST) Os_Ioc_Count_Unqueued = (uint16)OS_IOC_COUNT_UNQUEUED;
/** Area count */
CONST(AreaIdType, OS_CONST) OS_Area_Count = (AreaIdType)OS_AREA_COUNT;

#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"
/** This global const variable is used to define size of user stack
 *  \n{Ref: SWR_OS_S32K31X_009} */ 
CONST(uint32, OS_CONST) Os_User_Stack_Size = (uint32)(OS_USER_STACK_SIZE * sizeof(Os_StackType));
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"

/* Dummy variables for IOC library function */
#if (OS_APPLICATION == STD_ON)

#if (OS_IOC_COUNT_UNQUEUED == OS_PRE_ZERO)
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
CONST(Os_IocUnqueuedCfgType, OS_CONST) Os_GaaIocUnqueuedCfg[] =
{
  /* Unqueued Ioc Buffer info : 0 - Dummy */
  {
    /* *pBuffer */
    NULL_PTR,

    /* ulDataCount */
    0u
  }
};
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif /* if (OS_IOC_COUNT_UNQUEUED == OS_PRE_ZERO) */

#if (OS_IOC_COUNT_QUEUED == OS_PRE_ZERO)
#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
VAR(Os_IocQueuedCfgType, OS_VAR) Os_GaaIocQueuedCfg[] =
{
  /* Queued Ioc Buffer info : 0 - Dummy */
  {
    /* *pBuffer */
    NULL_PTR,

    /* ulDataCount */
    0u,

    /* ulQueueLen */
    0u,

    /* ulQueueRead */
    0u,

    /* ulQueueWrite */
    0u,

    /* ulQueueCount */
    0u,

    /* blDataLost */
    FALSE
  }
};
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif /* if (OS_IOC_COUNT_QUEUED == OS_PRE_ZERO) */

#endif /* if (OS_APPLICATION == STD_ON) */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
