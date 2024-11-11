/*******************************************************************************
**                                                                            **
**  (C) 2023 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Os_Arch_Types.h                                                **
**                                                                            **
**  TARGET    : ORINX-FSI (Functional Safety Island)                          **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for types/definitions/macros for ORINX-FSI        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:     Yes                                      **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
*******************************************************************************/
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Inline functions are needed for performance and Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> Prototype declaration of inline function is not needed */
/* polyspace:begin<MISRA-C:8.5:Not a defect:Justify with annotations> Inline functions should be implemented in header file  */
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */

#ifndef OS_ARCH_TYPES_H
#define OS_ARCH_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"
//#include "arm_ghs.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/**
 * @addtogroup OS_S32K31X_ESDD
 * @{ */
/* @Trace: SRS_BSW_00357 */
/* Types for address/size of memory object
*/
typedef int               Os_Sint_T;
typedef int               Os_Address_T;
typedef unsigned int      Os_Int_T;
typedef unsigned int      Os_Size_T;

/** Types for integer type 
 *  \n{Ref: SWR_OS_S32K31X_011} */
typedef uint32    Os_OldLevel_T;
/** Types for size of memory object
 *  \n{Ref: SWR_OS_S32K31X_011} */
typedef unsigned int Os_IntStatus_T;
/** Types for bit filed of 8bit register
 *  \n{Ref: SWR_OS_S32K31X_011} */
typedef unsigned char Os_Reg8;
/** Types for bit filed of 16bit register
 *  \n{Ref: SWR_OS_S32K31X_011} */
typedef unsigned short Os_Reg16;
/** Types for bit filed of 32bit register
 *  \n{Ref: SWR_OS_S32K31X_011} */
typedef unsigned int Os_Reg32;

/** Types for returning from context save/load function
 *  \n{Ref: SWR_OS_S32K31X_006} */
typedef struct STagTdd_Os_ContextSwitch
{
  #if (OS_FPU_SUPPORT == STD_ON)
  float64 dbD0;    /**< D0:   VFP double-precision register 0           */
  float64 dbD1;    /**< D1:   VFP double-precision register 1           */
  float64 dbD2;    /**< D2:   VFP double-precision register 2           */
  float64 dbD3;    /**< D3:   VFP double-precision register 3           */
  float64 dbD4;    /**< D4:   VFP double-precision register 4           */
  float64 dbD5;    /**< D5:   VFP double-precision register 5           */
  float64 dbD6;    /**< D6:   VFP double-precision register 6           */
  float64 dbD7;    /**< D7:   VFP double-precision register 7           */
  float64 dbD8;    /**< D8:   VFP double-precision register 8           */
  float64 dbD9;    /**< D9:   VFP double-precision register 9           */
  float64 dbD10;   /**< D10:  VFP double-precision register 10          */
  float64 dbD11;   /**< D11:  VFP double-precision register 11          */
  float64 dbD12;   /**< D12:  VFP double-precision register 12          */
  float64 dbD13;   /**< D13:  VFP double-precision register 13          */
  float64 dbD14;   /**< D14:  VFP double-precision register 14          */
  float64 dbD15;   /**< D15:  VFP double-precision register 15          */
  uint32  ulFPSCR; /**< FPSCR:Floating-Point Status and Control Register*/
  uint32  ulDummy; /**< Dummy:for 8byte-alibned                         */
  #endif /* if (OS_FPU_SUPPORT == STD_ON) */
  /*------------SW Context (4*1)--------------*/
  uint32 ulR4;   /* Expression register, preserved by child function */
  uint32 ulR5;   /* Expression register, preserved by child function */
  uint32 ulR6;   /* Expression register, preserved by child function */
  uint32 ulR7;   /* Expression register, argument pointer(AP), preserved by child function */
  uint32 ulR8;   /* Expression register, preserved by child function */
  uint32 ulR9;   /* Expression register, preserved by child function */
  uint32 ulR10;  /* Expression register, preserved by child function */
  uint32 ulR11;  /* Expression register, preserved by child function */
  uint32 ulSP;   /* Stack Pointer(R13)  */
  uint32 ulEXC_RETURN;
  /*------------HW Context (4*8)--------------*/
  uint32 ulR0;   /* Argument register, return register, expression register, preserved by parent function  */
  uint32 ulR1;   /* Argument register, return register, expression register, preserved by parent function  */
  uint32 ulR2;   /* Argument register, return register, preserved by parent function  */
  uint32 ulR3;   /* Argument register, return register, preserved by parent function  */
  uint32 ulR12;  /* Expression register, instruction pointer(IP), preserved by parent function */
  uint32 ulLR;   /* Link register, expression register (R14) */
  uint32 ulPC;   /* Program counter, not preserved */
  uint32 ulPSR;  /* Program status register, preserved by child function */
  /* Address of current stack frame of Task or CAT2 ISR */
  P2VAR(Os_StackType, AUTOMATIC, OS_VAR) pPowerOnSP;
} Tdd_Os_ContextSwitch;

/** Types for structure of Os ISR priority configuration
 *  \n{Ref: SWR_OS_S32K31X_001} */
/* @Trace: SRS_BSW_00410 */
typedef struct STagTdd_Os_ISRPriority
{
  /* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
  P2VAR(volatile uint8, AUTOMATIC, OS_VAR) pICRAddress;
                                    /**< Variable to Interrupt Control Register(INTC_PSR) address of interrupt */
  volatile uint8 usISRPriorityMask; /**< Variable to indicate priority of interrupt along with processor select bits */
  uint8 ucISRType;                  /**< Type of ISR */

  #if (OS_APPLICATION == STD_ON)
  ApplicationType ddAppId;          /**< Application ID */
  #endif
  TaskType ddTaskId;                /**< Task Identifier */
} Tdd_Os_ISRPriority;

/** Types for structure of Os ISR index configuration
 *  \n{Ref: SWR_OS_S32K31X_001} */
typedef struct STagTdd_Os_ISRIndex
{
  uint8 ucIsrCount;         /**< Variable to give total no of ISR */
  uint8 ucIsrStartIdx;      /**< Variable to give start Index of ISR */
} Tdd_Os_ISRIndex;
/** @} */

/** Types for structure of Category 1 ISR function pointer
 *  \n{Ref: SWR_OS_S32K31X_001} */
typedef void (*Os_Cat1IsrPtrType)(void);

/*
 * Exceptions
 */

/** Enum for Trap(Exception) category
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef enum ETag_Os_TrapType
{
  OS_TRAP_NONE             = 0U,
  OS_TRAP_RESET            = 1U,
  OS_TRAP_NMI              = 2U,
  OS_TRAP_HARD_FAULT       = 3U,
  OS_TRAP_MEMORY_MNG_FAULT = 4U,
  OS_TRAP_BUS_FAULT        = 5U,
  OS_TRAP_USAGE_FAULT      = 6U,
  OS_TRAP_UNDEFINED        = 256U
} Os_TrapType;

/** Types for structure of HardFault Status
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef volatile struct STag_Os_HardFaultStatusType
{
  Os_Reg32 Reserved1:  1; /**< Reserved */
  Os_Reg32 VECTTBL:    1; /**< BusFault on vector table reading during exception processing */
  Os_Reg32 Reserved2: 28; /**< Reserved */
  Os_Reg32 FORCED:     1; /**< Forced hard fault from Configurable priority that can not be handles, either because of priority or because it is disabled */
  Os_Reg32 DEBUGEVT:   1; /**< Reserved for Debug use */
} Os_HardFaultStatusType;

/** Types for structure of UsageFault Status
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef volatile struct STag_Os_UsageFaultStatusType
{
  Os_Reg32 UNDEFINSTR: 1; /**< Reserved */
  Os_Reg32 INVSTATE:   1; /**< Invalid state UsageFault, execute an instruction that makes illegal usage of the EPSR. */
  Os_Reg32 INVPC:      1; /**< Invalid PC load UsageFault, caused by an invalid PC loaded by EXC_RETURN */
  Os_Reg32 NOCP:       1; /**< No coprocessor UsageFault */
  Os_Reg32 UNALIGNED:  1; /**< Unaligned access UsageFault */
  Os_Reg32 DIVBYZERO:  1; /**< Divide by Zero UsageFault */
  Os_Reg32 Reserved:   6; /**< Reserved */
} Os_UsageFaultStatusType;

/** Types for structure of BusFault Status
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef volatile struct STag_Os_BusFaultStatusType
{
  Os_Reg32 IBUSERR:    1; /**< Instruction bus error */
  Os_Reg32 PRECISERR:  1; /**< PC value stacked for the exception return points to the instruction that caused the fault. (BFAR) */
  Os_Reg32 IMPRECISERR:1; /**< Imprecise data bus error */
  Os_Reg32 UNSTKERR:   1; /**< BusFault from unstacking for a return from exception */
  Os_Reg32 STKERR:     1; /**< BusFault from stacking for an exception entry */
  Os_Reg32 LSPERR:     1; /**< BusFault from floating-point lazy state preservation */
  Os_Reg32 Reserved:   1; /**< Reserved */
  Os_Reg32 BFARVALID:  1; /**< BusFault Address Register(BFAR) valid flag */
} Os_BusFaultStatusType;

/** Types for structure of MemFault Status
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef volatile struct STag_Os_MemFaultStatusType
{
  Os_Reg32 IACCVIOL:   1; /**< Instruction access violation */
  Os_Reg32 DACCVIOL:   1; /**< Data access violation, the processor attempted a load/store at a location that does not permit the operation (MMAR)*/
  Os_Reg32 Reserved1:  1; /**< Reserved */
  Os_Reg32 MUNSTKERR:  1; /**< MemFault from unstacking for exception entry */
  Os_Reg32 MSTKERR:    1; /**< MemFault from stacking for exception entry */
  Os_Reg32 MLSPERR:    1; /**< MemFault from floating-poin lazy state perservation */
  Os_Reg32 Reserved2:  1; /**< Reserved */
  Os_Reg32 MMARVALID:  1; /**< MemManage Fault Address(MMFAR) valid flag */
} Os_MemFaultStatusType;

/** Types for structure of ConfigFault Status
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef volatile struct STag_Os_ConfigFaultStatusType
{
  Os_MemFaultStatusType   MMFSR; /**< MemFault */
  Os_BusFaultStatusType   BFSR;  /**< BusFault */
  Os_UsageFaultStatusType UFSR;  /**< UsageFault */
} Os_ConfigFaultStatusType;

/** Macro to define the address of CFSR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_FAULT_STATUS_ADDR      (0xE000ED28UL)
/** Macro to define the address of MMFSR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_MMFSR_STATUS_ADDR      (0xE000ED28UL)
/** Macro to define the address of BFSR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_BFSR_STATUS_ADDR       (0xE000ED29UL)
/** Macro to define the address of UFSR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_UFSR_STATUS_ADDR       (0xE000ED2AUL)
/** Macro to define the address of HFSR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_HARD_FAULT_STATUS_ADDR        (0xE000ED2CUL)
/** Macro to define the address of MMFAR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_MMFAR_ADDR             (0xE000ED34UL)
/** Macro to define the address of BFAR
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_BFAR_ADDR              (0xE000ED38UL)
/** Macro to define the mask of HardFault status
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_HARD_FAULT_STATUS_MASK        (0xC0000003UL)
/** Macro to define the mask of MemManage status
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_MMFSR_FAULT_STATUS_MASK       (0xFFU)
/** Macro to define the mask of BusFault status
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_BFSR_FAULT_STATUS_MASK        (0xFFU)
/** Macro to define the mask of UsageFault status
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_CONFIG_UFSR_FAULT_STATUS_MASK      (0x030FU)

/**
  * @typedef Os_InterCoreEventType
  *
  * identifies the type of Os internal event
  *
  */
typedef enum
{
  UNKNOW_EVENT = 0,
  OS_MULTICORE_MESSAGE = 1,
  OS_SCHETABLE_SYNC = 2
} Os_InterCoreEventType;

/** Types for structure of saving exception information
 *  \n{Ref: SWR_OS_S32K31X_004} */
typedef struct STag_Os_TrapInfoType
{
  Os_TrapType               enTrapClass;  /* Exception category */
  uint32                    HFSR;         /* HardFault Status Register */
  uint32                    CFSR;         /* Configurable Fault Status Register */
  Tdd_Os_ContextSwitch      ExecCtxt;     /* Exception Context */
  MemoryStartAddressType    pExecAddr;    /* Exception occurred Address */
  MemoryStartAddressType    pMMFAR;       /* Memory Fault Address */
  MemoryStartAddressType    pBFAR;        /* Bus Fault Address */
} Os_TrapInfoType;

/** The following enum is defined for HW Timer channel id */
typedef enum ETag_Os_TimerIdType
{
  OS_SYSTICK = 0u,   /* OS Counter */
  OS_RTC,            /* Timing Protection - TimeFrame */
  OS_STM0,            /* Timing Protection - TimeBudget */
  OS_INVALID_TIMER
} Os_TimerIdType;

struct STagTdd_Os_HardwareCounter
{
  /* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
  P2VAR(volatile uint32, AUTOMATIC, OS_VAR) pNextInterruptTick;
                              /**< Pointer
                                   to the next timer interrupt tick(HW) */
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) pStaticCounter;
                              /**< Pointer to counter object */
  TickType ddNextCount;       /**< The next counter tick value
                                   at next timer interrupt */
  TickType ddTicksPerBase;    /**< HW timer ticks to raise 1 Counter tick */
  Os_TimerIdType enChannelId; /**< Timer Channel ID*/
};


/** The following structure is defined for Memory Block configuration */
typedef struct
{
  Os_Reg32 ddRegionNumber; /**< Selects the region currently accessed by MPU_RBAR and MPU_RASR. */
  Os_Reg32 ddRegionBaseAddress; /**< Holds the base address of the region identified by MPU_RNR. */
  Os_Reg32 ddRegionSizeAndEnable; /**< Defines the size and access behavior of the region identified by MPU_RNR, and enables that region. */
  boolean blEnabledOnStart; /**< Enables a memory region before OS starts */
} Tdd_Os_MemoryBlock;
/* System Handler controls */
/** Macro to define SHCSR (System Handler Control and State Register)
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_SYSHANDLER_CTRL_ADDR        (0xE000ED24U)
/** Macro to define the mask of USGFAULTENA
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_USAGE_F_ENA                 (0x00040000U)
/** Macro to define the mask of BUSFAULTENA
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_BUS_F_ENA                   (0x00020000U)
/** Macro to define the mask of MEMFAULTENA
 *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_ARM_M_MEM_F_ENA                   (0x00010000U)

/* IRQ controls */
/** Macro to define S32K311
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define S32K311 1
/** Macro to define S32K312
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define S32K312 2
/** Macro to define S32K346
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define S32K314 3

/** Macro to define the number of External Interrupt
 *  \n{Ref: SWR_OS_S32K31X_001} */
/* @Trace: SRS_BSW_00410 */
#if (OS_PROCESSOR == S32K311)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (239U)
#elif (OS_PROCESSOR == S32K312)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (239U)
#elif (OS_PROCESSOR == S32K314)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (239U)
#else
#error "Specified MCU is not supported."
#endif
/** Macro to define the start address of ISER (Interrupt Set-Enable Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_EN_SET_START            (0xE000E100U)
/** Macro to define the end address of ISER (Interrupt Set-Enable Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_EN_SET_END              (OS_ARM_M_IRQ_EN_SET_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of ICER (Interrupt Clear-Enable Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_EN_CLR_START            (0xE000E180U)
/** Macro to define the end address of ICER (Interrupt Clear-Enable Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_EN_CLR_END              (OS_ARM_M_IRQ_EN_CLR_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of ICPR (Interrupt Clear-Pending Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_CLEAR_PENDING_START     (0xE000E280U)
/** Macro to define the end address of ICPR (Interrupt Clear-Pending Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_CLEAR_PENDING_END       (OS_ARM_M_IRQ_CLEAR_PENDING_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of IABR (Interrupt Active Bit Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_ACTIVE_START            (0xE000E300U)
/** Macro to define the end address of IABR (Interrupt Active Bit Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_ACTIVE_END              (OS_ARM_M_IRQ_ACTIVE_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of IPR (Interrupt Priority Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_IPR_START               (0xE000E400U)
/** Macro to define the end address of IPR (Interrupt Priority Register)
 *  \n{Ref: SWR_OS_S32K31X_001} */
#define OS_ARM_M_IRQ_IPR_END                 (OS_ARM_M_IRQ_IPR_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 2) * 4U))
/*
 * CPU, TOOL, OS Definition
 */
/* OS_CACHE_MODE must be set to one of these in the architecture. Other
 * macros (like OS_CACHE_LINE_LEN) need to be set, and the architecture must supply
 * primitives for cache operations.
 * See kern-cacheflush.c/kern-cacheinvalidate.c/kern-cacheflushinvalidate.c for details.
*/
/** Macro to define no Cache operation
 *  \n{Ref: SWR_OS_S32K31X_011} */
#define OS_CACHE_MODE_NONE    1   /* No cache, or no cache operations. */
/** Macro to define Cache operations performed on single line
 *  \n{Ref: SWR_OS_S32K31X_011} */
#define OS_CACHE_MODE_LINE    2   /* Cache operations performed on single line. */
/** Macro to define Cache operation mode
 *  \n{Ref: SWR_OS_S32K31X_011} */
#define OS_CACHE_MODE       OS_CACHE_MODE_NONE
/** Macro to define Cache line length
 *  \n{Ref: SWR_OS_S32K31X_011} */
#define OS_CACHE_LINE_LEN     32
/** Macro to define SafeyKernel usage
 *  \n{Ref: SWR_OS_S32K31X_011} */
#define OS_SAFETY_KERNEL      STD_OFF

#if (OS_MULTICORE == STD_ON)
/** Structure of CPUSS_IDENTITY register
 *  \n{Ref: SWR_OS_S32K31X_011} */
typedef volatile union
{
  struct
  {
    Os_Reg32          :30;
    Os_Reg32 MS       :2;
  } B;
  sint32 I;
  uint32 U;
} OS_CPUSS_IDENTITY_type;

/** CPUSS_IDENTITY Register
 *  \n{Ref: SWR_OS_S32K31X_011} */
#define OS_CPUSS_IDENTITY            (*(volatile OS_CPUSS_IDENTITY_type*) 0x40260000UL)
/* Macro to define core id for CM7_0 */
#define CM7_0                 0u
/* Macro to define core id for CM7_1 */
#define CM7_1                 1u
/** Macro to define core id for CM7_1 */
#define CM7_2                 2u
/** Macro to define core id for CM7_1 */
#define CM7_3                 3u
/** Macro to get current core id
 *  \n{Ref: SWR_OS_CYTXXX_009} */
/* DataSheet 23 BusMasters Table 23-1 */
#define Os_MyCore()\
           (OS_CPUSS_IDENTITY.B.MS == 0 ? CM7_0 : \
            OS_CPUSS_IDENTITY.B.MS == 1 ? CM7_1 : \
            OS_CPUSS_IDENTITY.B.MS == 2 ? CM7_2 : \
            OS_CPUSS_IDENTITY.B.MS == 3 ? CM7_3 : \
            CM7_0 /* DEFAULT */ )
/** Macro to get Core ID
 *  \n{Ref: SWR_OS_S32K31X_009} */
#define OS_GET_CORE_ID(OS_CORE_ID)\
    do{\
    OS_CORE_ID = Os_MyCore();\
    }while(0)
#else
/** Macro to get current core id
 *  \n{Ref: SWR_OS_S32K31X_009} */
#define Os_MyCore()           0u
/** Macro to get Core ID
 *  \n{Ref: SWR_OS_S32K31X_009} */
#define OS_GET_CORE_ID(OS_CORE_ID)
#endif
/** Macro to define the core id of core 0
 *  \n{Ref: SWR_OS_S32K31X_009} */
#define OS_CORE_ZERO                    0u
/** Macro to define the core id of Master core (OS628)
 *  \n{Ref: SWR_OS_S32K31X_009} */
#define OS_CORE_ID_MASTER               ((CoreIDType)0)

/*
 * Timer
 */
 /** Macro to define margine(50us) to prevent missing System Timer interrupt
  *  It used updating Timer compare register
  *  \n{Ref: SWR_OS_S32K31X_007} */
#define OS_STM_MARGINE                  ((Os_GulStmClock >> 6) * 50u) //62.5

 /** Macro to define size of exception vector table
  *  \n{Ref: SWR_OS_S32K31X_004} */
#define NUM_ELE_VECTOR_TABLE            256
 /** Macro to define Invalid index value of ISR Table
  *  \n{Ref: SWR_OS_S32K31X_004} */
#define OS_INVALID_ISR_ID               (uint16)0xFFFFu

/** @} */

#define OS_DEBUG                        STD_ON

#ifndef UNUSED
  /* Check for unused parameter warnings*/
  #define UNUSED(variable)              (void) variable
#endif

/*
 * Inline function for system call
 */
 
#if (OS_TIMING_PROTECTION == STD_ON)
/** The highest ISR priority value supported by the hardware.
 *  When Timing Protection enabled, MAX Priority value will decreased 1.
 *  Because MAXIMUM value is reserved for Timing Protection interrupt */
#define OS_INT_MAX_PRIORITY              (2U)  
#else
#define OS_INT_MAX_PRIORITY              (1U) /* Used for Os_SuspendInterrupt */
#endif

/*
 * Memory Protection
 */

/* Macro to define number of memory region */
#define OS_MPU_RGD_COUNT     16u

/* Macro to define supervisor's access right for read,write,execute */
#define OS_MPU_SM_RWX        (0u << 3)

/* Macro to define supervisor's access right for read,execute */
#define OS_MPU_SM_RX         (1u << 3)

/* Macro to define supervisor's access right for read,write */
#define OS_MPU_SM_RW         (2u << 3)

/* Macro to define supervisor's same access right with user */
#define OS_MPU_SM_USER       (3u << 3)

/* Macro to define user's no access right */
#define OS_MPU_UM_NOACCESS   0u

/* Macro to define user's access right for execute */
#define OS_MPU_UM_X          1u

/* Macro to define user's access right for write */
#define OS_MPU_UM_W          2u

/* Macro to define user's access right for read */
#define OS_MPU_UM_R          4u

/* Macro to define user's access right for execute */
#define OS_MPU_UM_XO         OS_MPU_UM_X

/* Macro to define user's access right for write */
#define OS_MPU_UM_WO         OS_MPU_UM_W

/* Macro to define user's access right for read */
#define OS_MPU_UM_RO         OS_MPU_UM_R

/* Macro to define user's access right for execute */
#define OS_MPU_UM_RX         OS_MPU_UM_R | OS_MPU_UM_X

/* Macro to define user's access right for read,write */
#define OS_MPU_UM_RW         OS_MPU_UM_R | OS_MPU_UM_W

/* Macro to define user's access right for read,write,execute */
#define OS_MPU_UM_RWX        OS_MPU_UM_R | OS_MPU_UM_W | OS_MPU_UM_X

/* Macro to define mask of supervisor and user's access right */
#define OS_MPU_M0_MASK       0x1Fu

#define OS_MPU_CESR_ERR_MASK 0xF8000000u

#ifndef OS_INLINE
#define OS_INLINE inline __attribute__((always_inline))
#endif

#ifndef OS_LOCAL_INLINE
#define OS_LOCAL_INLINE static inline __attribute__((always_inline))
#endif

/* Os_WriteSizeType should be 4bytes or 8bytes size */
typedef unsigned long long Os_WriteSizeType;
#define OS_WRITESIZE sizeof(Os_WriteSizeType)

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
/* little-endian */
#define OS_WORD_LEFTSIDE(WORD, SHIFTSIZE) ((WORD) >> (SHIFTSIZE))
#define OS_WORD_RIGHTSIDE(WORD, SHIFTSIZE) ((WORD) << (SHIFTSIZE))
#else
/* big-endian */
#define OS_WORD_LEFTSIDE(WORD, SHIFTSIZE) ((WORD) << (SHIFTSIZE))
#define OS_WORD_RIGHTSIDE(WORD, SHIFTSIZE) ((WORD) >> (SHIFTSIZE))
#endif

#define SYSCALLTYPE(ptrtype, memclass, ptrclass)
#define OS_NUM_OF_BIT_UINT32     32u

#endif /* End of ifndef OS_ARCH_TYPES_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Inline functions are needed for performance and Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> Prototype declaration of inline function is not needed */
/* polyspace:end<MISRA-C:8.5:Not a defect:Justify with annotations> Inline functions should be implemented in header file  */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
