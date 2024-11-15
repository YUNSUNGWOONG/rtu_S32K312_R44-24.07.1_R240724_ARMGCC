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
**  FILE-NAME: Os_Cfg.h                                                       **
**                                                                            **
**  MODULE-NAME: AUTOSAR Os Module                                            **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                               **
**  Module version : 1.6.0.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml    
*                  Configuration\Ecu\Ecud_Os.arxml              
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml  
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
* @Trace: SRS_BSW_00334 SRS_BSW_00423
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C:8.9:Not a defect:Justify with annotations> This variable is defined in .lsl file. So external definition is not visible in Polyspace */
/* polyspace:begin<MISRA-C:19.4:Not a defect:Justify with annotations> It does not affect system. Code is manually checked */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Macro is needed to improving performance */

#ifndef OS_CFG_H
#define OS_CFG_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00318 SRS_BSW_00374 SRS_BSW_00379 */
#define    OS_AR_RELEASE_MAJOR_VERSION             0x04u
#define    OS_AR_RELEASE_MINOR_VERSION             0x04u
#define    OS_AR_RELEASE_REVISION_VERSION          0x00u
#define    OS_SW_MAJOR_VERSION                     0x01u
#define    OS_SW_MINOR_VERSION                     0x03u
#define    OS_SW_PATCH_VERSION                     0x00u
#define    OS_VENDOR_ID                            0x004Cu
#define    OS_MODULE_ID                            0x0001u
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Configuration Set Handles                             **
*******************************************************************************/

/*******************************************************************************
**                      Pre-compile options/Macros                            **
*******************************************************************************/
/*Allow non-trusted OS-application have full read access to memory.*/
/* @Trace: SafeOs_SUD_API_000072 */
#define OS_NON_TRUSTED_APP_FULL_READ_ACCESS   STD_OFF


/*Enable or Disable OS PERIPHERAL API */
/* @Trace: SafeOs_SUD_API_000420 */
#define OS_PERIPHERAL                         STD_OFF


/* Enable or Disable Error hook */
/* @Trace: SafeOs_SUD_API_000008 */
#define OS_ERROR_HOOK                         STD_ON


/* Enable or Disable Pre task hook  */
/* @Trace: SafeOs_SUD_API_000009 */
#define OS_PRETASK_HOOK                       STD_OFF


/* Enable or Disable Startup hook */
/* @Trace: SafeOs_SUD_API_000010 */
#define OS_STARTUP_HOOK                       STD_ON


/* Enable or Disable Post task hook */
/* @Trace: SafeOs_SUD_API_000011 */
#define OS_POSTTASK_HOOK                      STD_OFF


/* Enable or Disable Shutdown hook */
/* @Trace: SafeOs_SUD_API_000012 */
#define OS_SHUTDOWN_HOOK                      STD_ON


/* Enable or Disable Protection hook */
/* @Trace: SafeOs_SUD_API_000013 */
#define OS_PROTECTION_HOOK                    STD_OFF


/* Provide hook functions for profiling Task and CAT2 ISR state */
/* @Trace: SafeOs_SUD_API_000014 */
#define OS_PROFILING_HOOK                     STD_ON


/* memory protection */
/* @Trace: SafeOs_SUD_API_000015 */
#define OS_MEMORY_PROTECTION                  STD_OFF


/* application  */
/* @Trace: SafeOs_SUD_API_000016 */
#define OS_APPLICATION                        STD_OFF


/* restart task  */
/* @Trace: SafeOs_SUD_API_000017 */
#define OS_RESTART_TASK                       STD_OFF


/* Enable or Disable Tasks  */
/* @Trace: SafeOs_SUD_API_000018 */
#define OS_TASK                               STD_ON


/* Enable or Disable Events */
/* @Trace: SafeOs_SUD_API_000019 */
#define OS_EVENT                              STD_ON


/* Enable or Disable Schedule Table */
/* @Trace: SafeOs_SUD_API_000020 */
#define OS_SCHEDTABLE                         STD_OFF


/* Enable or Disable Alarms */
/* @Trace: SafeOs_SUD_API_000021 */
#define OS_ALARM                              STD_ON


/* ScheduleTableSynch strategy Implicit */
/* @Trace: SafeOs_SUD_API_000022 */
#define OS_SCHED_IMPLICIT_SYNC                STD_OFF


/* ScheduleTableSynch strategy Explicit */
/* @Trace: SafeOs_SUD_API_000023 */
#define OS_SCHED_EXPLICIT_SYNC                STD_OFF


/* Os Multicore Support  */
/* @Trace: SafeOs_SUD_API_000024 */
#define OS_MULTICORE                          STD_OFF


/* Multiple activation support for task */
/* @Trace: SafeOs_SUD_API_000025 */
#define OS_MULTIPLE_ACTIVATION                STD_OFF


/* Enable or Disable Resources */
/* @Trace: SafeOs_SUD_API_000026 */
#define OS_RESOURCE                           STD_ON


/* Enable or Disable Counters */
/* @Trace: SafeOs_SUD_API_000027 */
#define OS_COUNTER                            STD_ON


/* Enable or Disable Timing protection structures */
/* @Trace: SafeOs_SUD_API_000028 */
#define OS_TIMING_PROTECTION                  STD_OFF


/* Enable or Disable Spinlocks */
/* @Trace: SafeOs_SUD_API_000029 */
#define OS_SPINLOCK                           STD_OFF


/* Os Resource Timing Protection Execution Budget */
/* @Trace: SafeOs_SUD_API_000030 */
#define OS_RES_TP_EB                          STD_OFF



/* Os Task Timing Protection Execution Budget */
/* @Trace: SafeOs_SUD_API_000031 */
#define OS_TASK_TP_EB                         STD_OFF



/*  Os Task Timing Protection Time Frame  */
/* @Trace: SafeOs_SUD_API_000032 */
#define OS_TASK_TP_TF                         STD_OFF



/* Os Interrupt Lock Timing Protection Execution Budget */
/* @Trace: SafeOs_SUD_API_000033 */
#define OS_INTLOCK_TP_EB                      STD_OFF



/* Os All Interrupt Lock Timing Protection Execution Budget  */
/* @Trace: SafeOs_SUD_API_000034 */
#define OS_ALLINTLOCK_TP_EB                   STD_OFF



/* Precompile option to indicate that resource is used by an ISR */
/* @Trace: SafeOs_SUD_API_000035 */
#define OS_RES_INT_SHARE                      STD_OFF


/* Os Isr Timing Protection Execution Budget */
/* @Trace: SafeOs_SUD_API_000036 */
#define OS_ISR_TP_EB                          STD_OFF



/* Os Isr Timing Protection Time Frame */
/* @Trace: SafeOs_SUD_API_000037 */
#define OS_ISR_TP_TF                          STD_OFF



/* Enable or Disable Startup hook */
/* @Trace: SafeOs_SUD_API_000038 */
#define OS_APP_STARTUP_HOOK                   STD_OFF



/* Enable or Disable Shutdown hook  */
/* @Trace: SafeOs_SUD_API_000039 */
#define OS_APP_SHUTDOWN_HOOK                  STD_OFF



/* Enable or Disable Error hook */
/* @Trace: SafeOs_SUD_API_000040 */
#define OS_APP_ERROR_HOOK                     STD_OFF



/* STANDARD or EXTENDED Error */
/* @Trace: SafeOs_SUD_API_000041 */
#define OS_STATUS                             EXTENDED


/* Processor name */
/* @Trace: SafeOs_SUD_API_000042 */
#define OS_PROCESSOR                          S32K312


/* Processor series name */
/* @Trace: SafeOs_SUD_API_000043 */
#define OS_PROCESSOR_SERIES                   S32K31x


/* Use get service Id  */
/* @Trace: SafeOs_SUD_API_000044 */
#define OS_USE_GET_SERVICE_ID                 STD_ON


/* Stack monitoring */
/* @Trace: SafeOs_SUD_API_000045 */
#define OS_STACK_MONITORING                   STD_ON


/* Resource Scheduler */
/* @Trace: SafeOs_SUD_API_000046 */
#define OS_RES_SCHEDULER                      STD_ON


/* Scalability class */
/* @Trace: SafeOs_SUD_API_000047 */
#define OS_SCALABILITY_CLASS                  OS_SC1


/* User parameter access */
/* @Trace: SafeOs_SUD_API_000048 */
#define OS_USER_PARAMETER_ACCESS              STD_ON


/* Scheduling Policy */
/* @Trace: SafeOs_SUD_API_000049 */
#define OS_SCHEDULE_POLICY                    OS_PREEMPTIVE


/* Os Max Timing Protection Index */
/* @Trace: SafeOs_SUD_API_000050 */
#define OS_MAX_TP_INDEX                       0


/* Maximum priority of Task */
/* @Trace: SafeOs_SUD_API_000051 */
#define OS_MAX_PRIORITY                       10


/* Total number of Schedule actions across all Schedule Tables */
/* @Trace: SafeOs_SUD_API_000054 */
#define OS_ACTION_COUNT                       0


/* Total number of Counters */
/* @Trace: SafeOs_SUD_API_000055 */
#define OS_COUNTER_COUNT                      1


/* Total number of Application Modes */
/* @Trace: SafeOs_SUD_API_000056 */
#define OS_APPLMODE_COUNT                     1


/* Total number of Set event Alarm actions */
/* @Trace: SafeOs_SUD_API_000057 */
#define OS_SETEVENT_COUNT                     4


/* Total number of Callback Alarm actions */
/* @Trace: SafeOs_SUD_API_000058 */
#define OS_ACTIVATETASK_COUNT                 4


/* Total number of Resources */
/* @Trace: SafeOs_SUD_API_000059 */
#define OS_RESOURCE_COUNT                     1


/* Total number of Auto start Tasks */
/* @Trace: SafeOs_SUD_API_000060 */
#define OS_AUTOSTARTTASK_COUNT                2


/* Total number of Callback Alarm actions */
/* @Trace: SafeOs_SUD_API_000061 */
#define OS_CALLBACK_COUNT                     0


/* Total number of Scheduled WatchDogs */
/* @Trace: SafeOs_SUD_API_000062 */
#define OS_SCHWDG_COUNT                       0
  

/* Total number of Auto start Alarms */
/* @Trace: SafeOs_SUD_API_000063 */
#define OS_AUTOSTARTALARM_COUNT               0


/* Total number of PeripheralArea */
/* @Trace: SafeOs_SUD_API_000401 */
#define OS_AREA_COUNT                         0


/* Total number of Timing protections */
/* @Trace: SafeOs_SUD_API_000064 */
#define OS_AUTOSTART_SCHED_COUNT              0


/* Total number of Schedule Tables */
/* @Trace: SafeOs_SUD_API_000065 */
#define OS_SCHEDULE_COUNT                     0


/* Total number of Timing protections */
/* @Trace: SafeOs_SUD_API_000066 */
#define OS_TIMINGPROTECTION_COUNT             0


/* Total number of Increment counter Alarm actions */
/* @Trace: SafeOs_SUD_API_000067 */
#define OS_INCCOUNTER_COUNT                   0


/* Total number of Internal resources  */
/* @Trace: SafeOs_SUD_API_000068 */
#define OS_INTERNAL_RESOURCE_COUNT            3


/* Total number of IOC callback function */
/* @Trace: SafeOs_SUD_API_000069 */
#define OS_IOC_CALLBACK_COUNT                 0


/* Total number of IOC */
/* @Trace: SafeOs_SUD_API_000070 */
#define OS_IOC_COUNT                          0


/* Total number of Queued IOC */
/* @Trace: SafeOs_SUD_API_000071 */
#define OS_IOC_COUNT_QUEUED                   0

/* Total number of UnQueued IOC */
#define OS_IOC_COUNT_UNQUEUED                 0



/* Total number of Restart Tasks */
/* @Trace: SafeOs_SUD_API_000073 */
#define OS_RESTART_TASK_COUNT                 0


/* Os Number of cores */
/* @Trace: SafeOs_SUD_API_000074 */
#define OS_CORE_COUNT                         1


/* Os Number of spinlocks */
/* @Trace: SafeOs_SUD_API_000075 */
#define OS_SPINLOCK_COUNT                     0


/* Total number of Tasks */
/* @Trace: SafeOs_SUD_API_000076 */
#define OS_TASK_COUNT                         12


/* Total number of Hardware counters */
/* @Trace: SafeOs_SUD_API_000077 */
#define OS_HARDWARE_COUNTER_COUNT             1


/* Total number of Applications  */
/* @Trace: SafeOs_SUD_API_000078 */
#define OS_APPLICATION_COUNT                  0


/* Total Number of Trusted Functions */
/* @Trace: SafeOs_SUD_API_000079 */
#define OS_TRUSTED_FUNC_COUNT                 0


/* Total Number of Alarms */
/* @Trace: SafeOs_SUD_API_000080 */
#define OS_ALARM_COUNT                        8


/* Maximum activation count for Task */
/* @Trace: SafeOs_SUD_API_000081 */
#define OS_MAX_ACTIVATION_COUNT               1


/* Total number of Resources */
/* @Trace: SafeOs_SUD_API_000082 */
#define OS_RES_NESTING_COUNT                  6


/* Start Index for trusted protection application */
/* @Trace: SafeOs_SUD_API_000087 */
#define OS_TRUSTED_APP_WITH_PROTECTION_START_INDX 0

/* Start Index for trusted application */
/* @Trace: SafeOs_SUD_API_000083 */
#define OS_TRUSTED_START_INDX                 0



/* Maximum number of memory blocks used for an Application */
/* @Trace: SafeOs_SUD_API_000084 */
#define OS_MAX_USED_MEMBLK                    0


/* User Stack Size */
 /* @Trace: SafeOs_SUD_API_000086 */
#define OS_USER_STACK_SIZE                    1024u
 

/* Total number of Stack */
/* @Trace: SafeOs_SUD_API_000088 */
#define OS_STACK_COUNT                        6u


/* Total application or task stack size each core */
/* @Trace: SafeOs_SUD_API_000402 */
#define OS_TASK_STACK_SIZE0                   4500u


/* The number of OsEvent */
/* @Trace: SafeOs_SUD_API_000470 */
#define OS_EVENT_COUNT                        5u


/*******************************************************************************
**                      Handle IDs                                            **
*******************************************************************************/
/*Resource macro*/
/* @Trace: SafeOs_SUD_API_000404 */
#define RES_SCHEDULER                         ((ResourceType)0)

#define RES_SCHEDULER0                        ((ResourceType)RES_SCHEDULER)



/*Alarm Handles*/
/* @Trace: SafeOs_SUD_API_000089 */
#define OsAlarm_ASW_100ms                     ((AlarmType)0)
#define OsAlarm_ASW_10ms                      ((AlarmType)1)
#define OsAlarm_BG_Fota                       ((AlarmType)2)
#define OsAlarm_BSW_10ms                      ((AlarmType)3)
#define OsAlarm_BSW_5ms_Com                   ((AlarmType)4)
#define OsAlarm_BSW_BG_Crypto_Main            ((AlarmType)5)
#define OsAlarm_BSW_BG_KeyM_Main              ((AlarmType)6)
#define OsAlarm_BSW_Mem_Process               ((AlarmType)7)


/*AppMode Handles*/
/* @Trace: SafeOs_SUD_API_000090 */
#define OsAppMode0                            ((AppModeType)0)


/*Application Handles*/
/* @Trace: SafeOs_SUD_API_000091 */
#define OsApplication0                        ((ApplicationType)0)


/*Counter Handles*/
/* @Trace: SafeOs_SUD_API_000092 */
#define OsCounter_Main                        ((CounterType)0)


/*Resource Handles*/
/* @Trace: SafeOs_SUD_API_000403 */
#define OsResource_FG1                        ((ResourceType)0)
#define OsResource_FG2                        ((ResourceType)1)
#define OsResource_BG                         ((ResourceType)2)




/*Event Handles*/
/* @Trace: SafeOs_SUD_API_000093 */
#define OsEvent_BSW_Mem_Process               ((EventMaskType)1)
#define OsEvent_BG_Fota                       ((EventMaskType)8192)
#define OsEvent_BSW_KeyM_Main                 ((EventMaskType)16384)
#define OsEvent_BSW_Crypto_Main               ((EventMaskType)32768)
#define OsEvent_BSW_BswM_Action_Main          ((EventMaskType)65536)


/*Isr Handles*/
/* @Trace: SafeOs_SUD_API_000094 */
#define Adc_Sar_0_Isr                         ((ISRType)13)
#define Adc_Sar_1_Isr                         ((ISRType)14)
#define CAN0_ORED_0_31_MB_IRQHandler          ((ISRType)15)
#define CAN0_ORED_32_63_MB_IRQHandler         ((ISRType)16)
#define CAN0_ORED_IRQHandler                  ((ISRType)17)
#define EMIOS0_1_IRQ                          ((ISRType)18)
#define EMIOS0_4_IRQ                          ((ISRType)19)
#define EMIOS0_5_IRQ                          ((ISRType)20)
#define EMIOS1_5_IRQ                          ((ISRType)21)
#define LPUART0_LIN_IP_RxTx_IRQHandler        ((ISRType)22)
#define Mu_Ip_Mu0_OredGP_Isr                  ((ISRType)23)
#define Mu_Ip_Mu0_OredRx_Isr                  ((ISRType)24)
#define Mu_Ip_Mu1_OredGP_Isr                  ((ISRType)25)
#define Mu_Ip_Mu1_OredRx_Isr                  ((ISRType)26)
#define PIT_0_ISR                             ((ISRType)27)
#define PIT_1_ISR                             ((ISRType)28)
#define STM_0_ISR                             ((ISRType)29)
#define LPUART5_LIN_IP_RxTx_IRQHandler        ((ISRType)30)
#define WKPU_EXT_IRQ_SINGLE_ISR               ((ISRType)31)
#define OsIsrOsCounter_Main                   ((ISRType)32)




/*Task Handles*/
/* @Trace: SafeOs_SUD_API_000096 */
#define OsTask_ASW_FG1_100ms                  ((TaskType)1)
#define OsTask_ASW_FG1_10ms                   ((TaskType)2)
#define OsTask_BSW_FG1_10ms                   ((TaskType)3)
#define OsTask_BSW_Init                       ((TaskType)4)
#define OsTask_BSW_Mem_Process                ((TaskType)5)
#define OsTask_BSW_FG1_5ms_Com                ((TaskType)6)
#define OsTask_BSW_FG3_ComMModeRequest        ((TaskType)7)
#define OsTask_BSW_BG_KeyM_Main               ((TaskType)8)
#define OsTask_BSW_BG_Crypto_Main             ((TaskType)9)
#define OsTask_BSW_FG3_BswM_Action_Main       ((TaskType)10)
#define OsTask_BSW_FG2_LinScheduleRequest     ((TaskType)11)
#define OsTask_BSW_BG_Fota                    ((TaskType)12)




/*Core_Macros*/
/* @Trace: SafeOs_SUD_API_000097 */
#define OS_CORE_ID_MASTER                     ((CoreIDType)0)
#define OS_CORE_ID_0                          ((CoreIDType)0)


/*Counter Function Macros*/
/* @Trace: SRS_Frt_00047 */
/* @Trace: SafeOs_SUD_API_000098 */
#define OS_TICKS2MS_OsCounter_Main(Value)     (((PhysicalTimeType)((Value)*1250000 / 1000000)))
#define OS_TICKS2NS_OsCounter_Main(Value)     (((PhysicalTimeType)((Value)*1250000)))
#define OS_TICKS2SEC_OsCounter_Main(Value)    (((PhysicalTimeType)((Value)*1250000 / 1000000000)))
#define OS_TICKS2US_OsCounter_Main(Value)     (((PhysicalTimeType)((Value)*1250000 / 1000)))


/* CounterMaxAllVal Macros */
/* @Trace: SafeOs_SUD_API_000099 */
#define OSMAXALLOWEDVALUE_OsCounter_Main      (4294967295)




/*CounterMinCycle_Macros*/
/* @Trace: SafeOs_SUD_API_000100 */
#define OSMINCYCLE_OsCounter_Main             (1)


/*CounterTick Macros*/
/* @Trace: SafeOs_SUD_API_000101 */
#define OSTICKSPERBASE_OsCounter_Main         (1)




/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#ifndef VAR_CHECK
/*Extern declarations for Isr*/
/* @Trace: SafeOs_SUD_API_000103 */
extern void ISR_OsCounter_Main(void);
extern void ISR_Adc_Sar_0_Isr(void);
extern void ISR_Adc_Sar_1_Isr(void);
extern void ISR_CAN0_ORED_0_31_MB_IRQHandler(void);
extern void ISR_CAN0_ORED_32_63_MB_IRQHandler(void);
extern void ISR_CAN0_ORED_IRQHandler(void);
extern void ISR_EMIOS0_1_IRQ(void);
extern void ISR_EMIOS0_4_IRQ(void);
extern void ISR_EMIOS0_5_IRQ(void);
extern void ISR_EMIOS1_5_IRQ(void);
extern void ISR_LPUART0_LIN_IP_RxTx_IRQHandler(void);
extern void ISR_Mu_Ip_Mu0_OredGP_Isr(void);
extern void ISR_Mu_Ip_Mu0_OredRx_Isr(void);
extern void ISR_Mu_Ip_Mu1_OredGP_Isr(void);
extern void ISR_Mu_Ip_Mu1_OredRx_Isr(void);
extern void ISR_PIT_0_ISR(void);
extern void ISR_PIT_1_ISR(void);
extern void ISR_STM_0_ISR(void);
extern void ISR_LPUART5_LIN_IP_RxTx_IRQHandler(void);
extern void ISR_WKPU_EXT_IRQ_SINGLE_ISR(void);
 

/*Extern declarations for Task*/
/* @Trace: SafeOs_SUD_API_000104 */
extern void TASK_OsTask_ASW_FG1_100ms(void);
extern void TASK_OsTask_ASW_FG1_10ms(void);
extern void TASK_OsTask_BSW_FG1_10ms(void);
extern void TASK_OsTask_BSW_Init(void);
extern void TASK_OsTask_BSW_Mem_Process(void);
extern void TASK_OsTask_BSW_FG1_5ms_Com(void);
extern void TASK_OsTask_BSW_FG3_ComMModeRequest(void);
extern void TASK_OsTask_BSW_BG_KeyM_Main(void);
extern void TASK_OsTask_BSW_BG_Crypto_Main(void);
extern void TASK_OsTask_BSW_FG3_BswM_Action_Main(void);
extern void TASK_OsTask_BSW_FG2_LinScheduleRequest(void);
extern void TASK_OsTask_BSW_BG_Fota(void);


 

 
 
 

#endif
#endif /* OS_CFG_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:8.9:Not a defect:Justify with annotations> This variable is defined in .lsl file. So external definition is not visible in Polyspace */
/* polyspace:end<MISRA-C:19.4:Not a defect:Justify with annotations> It does not affect system. Code is manually checked */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Macro is needed to improving performance */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

