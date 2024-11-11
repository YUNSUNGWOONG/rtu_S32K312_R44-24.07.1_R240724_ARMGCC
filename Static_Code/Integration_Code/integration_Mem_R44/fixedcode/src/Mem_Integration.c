/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_Integration.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.4,20.9,D4.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */
/* polyspace-begin RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Not a defect" */
/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Os.h"
#include "Mem_Integration.h" /* NvM.h */
#include "SchM_NvM.h"

/* NvM R40 file name */
#if ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 0U))
  #include "NvM_Ram.h"
/* NvM R44 file name */
#elif ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U))
  #include "NvM_IntTypes.h"
  #include "NvM_Globals.h"
#else
  #error "NvM version is not support"
#endif

/* backward compatibility for Dem */
#if (NVM_BSWM_DEM_WRITENVDATA_CALL == STD_ON)
#include "Dem_EventMemory.h"
#endif

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (MEM_FLS_USED == STD_ON)
#include "Fls.h"

/* not declared Fls_MainFunction in the Fls.h */
#if (\
  (defined(HWRESOURCE_S32G2X) && HWRESOURCE_FAMILY(HWRESOURCE_S32G2X)) || \
  (defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
  (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
  (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
  (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)) || \
  (defined(__INCLUDE_SCHM_FEE_FLS__)) || \
  (defined(HWRESOURCE_S32K31X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))\
  )
/* TriCore ASR 4.2.2 ~ */
#if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
#if ((FLS_AR_RELEASE_MAJOR_VERSION == 4) && (FLS_AR_RELEASE_MINOR_VERSION >= 2))
#include "SchM_Fls_17_Dmu.h"

#else
#include "SchM_Fls_17_Pmu.h"
	
#endif /* End of FLS_AR_RELEASE_MAJOR_VERSION */

#else
#include "SchM_Fls.h"

#endif /* End of HWRESOURCE_INFINEON */
#endif /* End of __INCLUDE_SCHM_FEE_FLS__ */

#if ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
#include "Fls_PBcfg.h"
#include "Fls_CfgDer.h"

#define FAULT_REG(ADDR)                             (*(volatile uint32 *)(ADDR))

#define FAULT_STRUCT_CTL                                ((uint32)FLS_FAULT_ADDR)
#define FAULT_STRUCT_STATUS                    ((uint32)(FLS_FAULT_ADDR+0x0CUL))
#define FAULT_STRUCT_DATA0                     ((uint32)(FLS_FAULT_ADDR+0x10UL))
#define FAULT_STRUCT_DATA1                     ((uint32)(FLS_FAULT_ADDR+0x14UL))
#define FAULT_STRUCT_DATA2                     ((uint32)(FLS_FAULT_ADDR+0x18UL))
#define FAULT_STRUCT_DATA3                     ((uint32)(FLS_FAULT_ADDR+0x1CUL))
#define FAULT_STRUCT_INTR                      ((uint32)(FLS_FAULT_ADDR+0xC0UL))
#define FAULT_STRUCT_INTR_SET                  ((uint32)(FLS_FAULT_ADDR+0xC0UL))
#define FAULT_STRUCT_INTR_MASK                 ((uint32)(FLS_FAULT_ADDR+0xC8UL))
#define FAULT_STRUCT_MASK1                     ((uint32)(FLS_FAULT_ADDR+0x54UL))
#define FAULT_VALID_MASK                                ((uint32)(0x80000000UL))
#define FAULT_INDEX_MASK                                ((uint32)(0x0000007FUL))
#define FAULT_RESET_REQ_EN                              ((uint32)(0x00000004UL))
#define FAULT_OUT_EN                                    ((uint32)(0x00000002UL))
#define FAULT_TR_EN                                     ((uint32)(0x00000001UL))
#define FAULT_DATA0_MASK                                ((uint32)(0x07FFFFFFUL))
/* Flash controller work flash bus error */
#define CY_SYSFLT_FLASHC_WORK_BUS_ERROR                         ((uint32)(51UL))
/* Flash controller work flash cache correctable ECC violation */
#define CY_SYSFLT_FLASHC_WORK_C_ECC                             ((uint32)(52UL))
/* Flash controller work flash cache non-correctable ECC violation */
#define CY_SYSFLT_FLASHC_WORK_NC_ECC                            ((uint32)(53UL))


static FUNC(void, NVM_CODE) Fls_EccFaultPreInit(void);
static FUNC(void, NVM_CODE) Fls_EccFaultPostInit(void);
static FUNC(void, NVM_CODE) Fls_EccFaultHandler(void);
#endif 

#endif /* (MEM_FLS_USED == STD_ON) */

#if (MEM_FEE_USED == STD_ON)
#include "Fee.h" /* Fee_Version.h */

#if (\
    (defined(HWRESOURCE_S32G2X) && HWRESOURCE_FAMILY(HWRESOURCE_S32G2X)) || \
    (defined(__INCLUDE_SCHM_FEE_FLS__)) || \
    (defined(HWRESOURCE_S32K31X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K31X)) \
    )
#include "SchM_Fee.h"
#endif

#endif /* (MEM_FEE_USED == STD_ON) */

#if (MEM_EA_USED == STD_ON)
#include "Ea.h"
#if ((EA_AR_RELEASE_MAJOR_VERSION == 4U) && (EA_AR_RELEASE_MINOR_VERSION == 4U))
#include "SchM_Ea.h" /* AR44 declaration */
#endif /* (EA_AR_RELEASE_MAJOR_VERSION == 4U) && (EA_AR_RELEASE_MINOR_VERSION == 4U) */
#include "SchM_Eep.h"
#endif /* (MEM_EA_USED == STD_ON) */

#if (MEM_FLS_USED == STD_ON)
#if ((defined(HWRESOURCE_S6J32XX) && HWRESOURCE_FAMILY(HWRESOURCE_S6J32XX)) || \
    (defined(HWRESOURCE_S6J33XX) && HWRESOURCE_FAMILY(HWRESOURCE_S6J33XX)))
#include "mcu_settings.h"
#endif
#endif /* (MEM_FLS_USED == STD_ON) */

/* S32G RTD 2.0.0 need NULL_PTR for Fls_init, Fee_Init when using Pre-configuration*/
#if ( defined(HWRESOURCE_S32G2X) && HWRESOURCE_FAMILY(HWRESOURCE_S32G2X) )

#if ( defined(FEE_SW_MAJOR_VERSION) && (FEE_SW_MAJOR_VERSION >= 2) )
#define FEE_CONFIGSET NULL_PTR
#endif

#if ( defined(FLS_SW_MAJOR_VERSION) && (FLS_SW_MAJOR_VERSION >= 2) )
#define FLS_CONFIGSET NULL_PTR
#endif

#endif

#if(NVM_DRV_MODE_SWITCH == STD_OFF)
#error "1 NvMDrvModeSwitch should be true."
#error "2 FlsDefaultMode should be configured as MEMIF_MODE_FAST"
#error "3 FlsSetModeApi should be true."
#error "4 FeeSetModeSupported should be true."
#error "5 EepDefaultMode should be configured as MEMIF_MODE_FAST"
#error "6 EaSetModeSupported should be true."
#endif

#if (MEM_FEE_USED == STD_ON)

#if ( HWRESOURCE_VENDOR(HWRESOURCE_ST) )

/* To avoid MISRA C:2012 20.9 : 'FEE_SW_MAJOR_VERSION, FLS_SW_MAJOR_VERSION' is not defined. */
#if ( (FEE_SW_MAJOR_VERSION >= 1) && (FLS_SW_MAJOR_VERSION >= 1) )
#define MEM_FEE_INIT_WHILE_LOOP  (STD_OFF)

#else
#define MEM_FEE_INIT_WHILE_LOOP  (STD_ON)

#endif

#else
#define MEM_FEE_INIT_WHILE_LOOP  (STD_ON)

#endif

#endif /* (MEM_FEE_USED == STD_ON) */

#if (MEM_EA_USED == STD_ON)

#if ((EA_AR_RELEASE_MAJOR_VERSION == 4) && (EA_AR_RELEASE_MINOR_VERSION == 4))
#define MEM_EA_INIT_WHILE_LOOP  (STD_ON)
#else
#define MEM_EA_INIT_WHILE_LOOP  (STD_OFF)
#endif

#endif /* (MEM_EA_USED == STD_ON) */

#if defined(NVM_USER_JOB_FUNCTION)
FUNC(NvM_OpStatusType, NVM_CODE) NVM_USER_JOB_FUNCTION(void); /* polyspace MISRA-C3:8.5 [Justified:Low] "The function can be invoked by ASW layer, therefore Mem_Integration code also declare it" */
#endif

#if defined(NVM_OS_ALARM)
static FUNC(TickType, NVM_CODE) Mem_GetAlarmOffset(void);
#endif

#if (MEM_FEE_USED == STD_ON)
#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
/* polyspace +1 MISRA-C3:8.5 [Justified:Low] "The function can be invoked by Fee, , therefore Mem_Integration code also declare it" */
FUNC(void, NVM_CODE) Fee_IllegalStateNotification (void);
#endif
#endif /* (MEM_FEE_USED == STD_ON) */

#if defined(NVM_USER_WDG_TOGGLE_FUNCTION)
void NVM_USER_WDG_TOGGLE_FUNCTION(void);
#endif /* defined(NVM_USER_WDG_TOGGLE_FUNCTION) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

uint8 ConfigIDRamBlock[2];
/* Block Descriptor in R40 */
#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock1
uint8 NvMBlock_IntTst_TestBlock1_Ram_Block[10];
#endif /* NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock1 */

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock2
uint8 NvMBlock_IntTst_TestBlock2_Ram_Block[10];
#endif /* NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock2 */

#ifdef NvMBlock_IntTst_TestBlock1
uint8 NvMBlock_IntTst_TestBlock1_Ram_Block[10];
#endif /* NvMBlock_IntTst_TestBlock1 */

#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_Driver_StartUp                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic Memory Stack Initialization       **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Eep_Init, Ea_Init             **
**                             Fls_17_Pmu_Init, Mem_FlsInitPerform, Fee_Init  **
**                             Mem_FeeInitPerform, NvM_Init, NvM_ReadAll      **
**                             Mem_Call_NvM_BITP                              **
*******************************************************************************/
FUNC(void, NVM_CODE) Mem_Driver_StartUp(void)
{
  #if (MEM_EA_USED == STD_ON)
    Eep_Init(NULL_PTR);

    Mem_EaInitPerform();
  #endif /* (MEM_EA_USED == STD_ON) */

  #if (MEM_FLS_USED == STD_ON)
    Mem_FlsInitPerform();
  #endif

  #if (MEM_FEE_USED == STD_ON)
    Mem_FeeInitPerform();
  #endif

  #if ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U))
    NvM_Init();             /* NvM R40 */

  #elif ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U))
    NvM_Init(NULL_PTR);     /* NvM R44 */
  #else
    #error "NvM version is not support"
  #endif
  NvM_ReadAll();

  if (E_OK != ActivateTask(OsTask_BSW_Mem_Process))
  {
    MEM_REPORT_ERROR(MEM_OSTASK_BSW_MEM_PROCESS_SID, MEM_E_ALARM);
  }
}
/*******************************************************************************
** Function Name        : Mem_Driver_ShutDown                                 **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for WriteAll Perform                        **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : NvM_WriteAll,                 **
**                             Mem_Call_NvM_BITP                              **
*******************************************************************************/
FUNC(void, NVM_CODE) Mem_Driver_ShutDown(void)
{
  /* Reset the task sequence control variable */
  NvM_WriteAll();
}
/*******************************************************************************
** Function Name        : Mem_FlsInitPerform                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic FLS Initialization                **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Fls_GetStatus, Fls_MainFunction*
*******************************************************************************/
#if (MEM_FLS_USED == STD_ON)
FUNC(void, NVM_CODE) Mem_FlsInitPerform(void)
{
  uint32 timeOut = 0xFFFFU;

  /* ASR 4.2.2 ~ */
  #if ((FLS_AR_RELEASE_MAJOR_VERSION == 4) && (FLS_AR_RELEASE_MINOR_VERSION >= 2))
    #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
      Fls_17_Dmu_Init(&Fls_17_Dmu_Config);

    /* Cypress Traveo II */
    #elif ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))

      Fls_EccFaultPreInit();

      Fls_Init(NULL_PTR);
    #else
      /* ex) SCons : DefaultDefineOption : FLS_CONFIGSET = FlsConfigSet_0 */
      #ifdef FLS_CONFIGSET
        Fls_Init(FLS_CONFIGSET);

      #else
        #error "MCU is not supported yet"

      #endif
    #endif
  /* ~ ASR 4.1.2 */
  #else
    #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
      Fls_17_Pmu_Init(&Fls_17_Pmu_ConfigRoot[0]);

    /* Freescale(NXP) or ST mpc family */
    #elif (HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE) || HWRESOURCE_VENDOR(HWRESOURCE_ST))
      Fls_Init(&FlsConfigSet_0);

    #elif ((defined(HWRESOURCE_S6J32XX) && HWRESOURCE_FAMILY(HWRESOURCE_S6J32XX)) || \
           (defined(HWRESOURCE_S6J33XX) && HWRESOURCE_FAMILY(HWRESOURCE_S6J33XX)) )
      #ifndef MEM_DISABLE_WFCFG_EMENR_LIMITATION
      /* Fee Limitation
       *
       * Set WFCFG_EMENR(WorkFLASH Extra Mode Enable Register:) : AEE "1". */
      /* [bit8] AEE: Read Arbitration Error Enable = 1 */
      WFCFG_EMENR |= 0x00000100;
      #endif

      Fls_Init(NULL_PTR);

    #elif HWRESOURCE_VENDOR(HWRESOURCE_NXP)
      Fls_Init(&FlsConfigSet_0);

    #else
      #error "MCU is not supported yet"
    #endif
  #endif

  while( (Fls_GetStatus() != MEMIF_IDLE) && (timeOut > 0U) )
  {
    MEM_MAINFUNCTION_FLS(); /* polyspace MISRA-C3:8.3 [Justified:Low] "The code generated by Rte is the result of user configuration. The user's name definition can be changed for convenience." */
    timeOut--;
  };

}
#endif
/*******************************************************************************
** Function Name        : Mem_FeeInitPerform                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic FEE Initialization                **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Fee_GetStatus                 **
**                             Fls_MainFunction, Fee_MainFunctions            **
*******************************************************************************/
#if (MEM_FEE_USED == STD_ON)
FUNC(void, NVM_CODE) Mem_FeeInitPerform(void)
{
  #if (MEM_FEE_INIT_WHILE_LOOP == STD_ON)
  boolean loopBrk = MEM_TRUE;
  uint32 timeout = 0xFFFFFFUL;
  #endif

  /* polyspace +2 MISRA-C3:2.2 [Justified:Low] "This function is implemented by user." */
  Mem_PostFeeInitCallback();

  /* ASR 4.2.2 ~  : void Fee_Init(const Fee_ConfigType* ConfigPtr) */
  #if ((FEE_AR_RELEASE_MAJOR_VERSION == 4) && (FEE_AR_RELEASE_MINOR_VERSION >= 2))

    #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
      Fee_Init(NULL_PTR);

    #elif (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
      Fee_Init(&Fee_Config);

    /* Cypress Traveo II */
    #elif ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
      Fee_Init(NULL_PTR);

    #else
      /* ex) SCons : DefaultDefineOption : FEE_CONFIGSET = FlsConfigSet_0 */
      #ifdef FEE_CONFIGSET
        Fee_Init(FEE_CONFIGSET);

      #else
        #error "MCU is not supported yet"

      #endif /* #ifdef FEE_CONFIGSET */
    #endif /* #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP)) */
  /* ~ ASR 4.1.2 : void Fee_Init( void ) */
  #else
    Fee_Init();

  #endif /* #if((FEE_AR_RELEASE_MAJOR_VERSION == 4)&&(FEE_AR_RELEASE_MINOR_VERSION >= 2))*/

  #if (MEM_FEE_INIT_WHILE_LOOP == STD_ON)
  while(MEM_TRUE == loopBrk)
  {
    MEM_MAINFUNCTION_FLS();
    MEM_MAINFUNCTION_FEE(); /* polyspace MISRA-C3:8.3 [Justified:Low] "The code generated by Rte is the result of user configuration. The user's name definition can be changed for convenience." */
#if defined (NVM_USER_WDG_TOGGLE_FUNCTION)
    NVM_USER_WDG_TOGGLE_FUNCTION();
#endif
    timeout--;

    if (timeout == 0U)
    {
      loopBrk = MEM_FALSE;
    }
    else if (Fee_GetStatus() == MEMIF_IDLE)
    {
      loopBrk = MEM_FALSE;
    }

    #if HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS)
    else if (Fee_GetStatus() == MEMIF_UNINIT)
    {
      loopBrk = Mem_Cypress_IllegalStateCallback();
    }
    #endif
    else
    {
      /* do nothing */
    }
  }
  #endif
  /* Cypress Traveo II WorkFlash ECC Detect*/
  #if ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
  /* Post Init of WorkFlash ECC Detction must be done after init of Fee and Fls */
  Fls_EccFaultPostInit(); 

  #endif
}
#endif

/*******************************************************************************
** Function Name        : Mem_EaInitPerform                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Service for EA Initialization                       **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Ea_GetStatus                  **
**                             Eep_MainFunction, Ea_MainFunctions             **
*******************************************************************************/
#if (MEM_EA_USED == STD_ON)
FUNC(void, NVM_CODE) Mem_EaInitPerform(void)
{
  #if (MEM_EA_INIT_WHILE_LOOP == STD_ON)
  boolean loopBrk = MEM_TRUE;
  uint32  timeout = 0xFFFFFFUL;
  MemIf_StatusType eaStatus;
  #endif /* (MEM_EA_INIT_WHILE_LOOP == STD_ON) */

  #if ((EA_AR_RELEASE_MAJOR_VERSION == 4U) && (EA_AR_RELEASE_MINOR_VERSION < 4U))
    Ea_Init();         /* R40 Ea_Init */

  #elif ((EA_AR_RELEASE_MAJOR_VERSION == 4U) && (EA_AR_RELEASE_MINOR_VERSION == 4U))
    Ea_Init(NULL_PTR); /* R44 Ea_Init */

  #else
    #error "Ea version is not support"
  #endif

  #if (MEM_EA_INIT_WHILE_LOOP == STD_ON)
  while(MEM_TRUE == loopBrk)
  {
    MEM_MAINFUNCTION_EA();
    MEM_MAINFUNCTION_EEP();
#if defined (NVM_USER_WDG_TOGGLE_FUNCTION)
    NVM_USER_WDG_TOGGLE_FUNCTION();
#endif
    timeout--;

    eaStatus = Ea_GetStatus();

    if (0U == timeout)
    {
      loopBrk = MEM_FALSE;
    }
    else if (MEMIF_IDLE == eaStatus)
    {
      loopBrk = MEM_FALSE;
    }
    else
    {
      /* Do nothing */
    }

  }
  #endif /* (MEM_EA_INIT_WHILE_LOOP == STD_ON) */
}
#endif /* (MEM_EA_USED == STD_ON) */

/*******************************************************************************
** Function Name        : Mem_GetAlarmOffset                                  **
**                                                                            **
** Service ID           : N/a                                                 **
**                                                                            **
** Description          : Get alarm offset according to the current job status**
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
** Return parameter     : Alarm offset                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if defined(NVM_OS_ALARM)
static FUNC(TickType, NVM_CODE) Mem_GetAlarmOffset(void)
{
  TickType alarmOffset;

  if (
#if (NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U)
    /* NvM naming rule in R40 */
    (NVM_IDLE != NvM_GucState) ||    /* block is in progress */
    (0U       != NvM_GucStdQueEnDis) /* queue is not empty */
    #if (MEM_WRITEALL_FAST_MODE == STD_OFF)
    || (NVM_MULTIBLK_UNREQUESTED != NvM_GucWriteAllRequest)
    #endif /* (MEM_WRITEALL_FAST_MODE == STD_OFF) */
#elif (NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U)
    /* NvM naming rule in R44 */
    (NVM_IDLE != NvM_State) ||                              /* block is in progress */
    (NVM_SIZE_STANDARD_JOB_QUEUE != NvM_StdFreeSlotsAvail)  /* queue is not empty */
    #if (MEM_WRITEALL_FAST_MODE == STD_OFF)
    || (NVM_MULTIBLK_UNREQUESTED != NvM_WriteAllRequest)
    #endif /* (MEM_WRITEALL_FAST_MODE == STD_OFF) */
#else
  #error "NvM version is not support"
#endif /* (NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U) */
  )
  { /* about 1ms~3ms */
    alarmOffset = NVM_TICKS_BURST_MODE;
  }
  else
  {
    /* about 5ms~6ms */
    alarmOffset = NVM_TICKS_NORMAL_MODE;
  }

  return alarmOffset;
}
#endif

/*******************************************************************************
** Function Name        : OsTask_BSW_Mem_Process                              **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for Call MemoryStack Mainfunction           **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : This function is invoked by OsAlarm                 **
**                                                                            **
*******************************************************************************/
TASK( OsTask_BSW_Mem_Process ) /* polyspace MISRA-C3:8.3 [Justified:Low] "The code generated by Rte is the result of user configuration. The user's name definition can be changed for convenience." */
{
  static boolean callSeq = MEM_FALSE;
  EventMaskType eventMask;
  #if defined(NVM_OS_ALARM)
  TickType alarmOffset;
  #endif
  /* polyspace-begin MISRA-C3:14.3 DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "It depends on Os code, currently Os does not implement return E_NOT_OK" */
  if (E_OK ==  SetEvent(OsTask_BSW_Mem_Process, OsEvent_BSW_Mem_Process))
  {
  /* polyspace-end MISRA-C3:14.3 DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "It depends on Os code, currently Os does not implement return E_NOT_OK" */
    /* for ReadAll function */
    MEM_MAINFUNCTION_NVM();
    MEM_MAINFUNCTION_NVM();

    while (1)
    {
      (void)WaitEvent(OsEvent_BSW_Mem_Process);
      (void)GetEvent(OsTask_BSW_Mem_Process, &eventMask);
      (void)ClearEvent(OsEvent_BSW_Mem_Process);

      /*************************************************************************
       *           1. User Job Operation
       ************************************************************************/
      #if defined(NVM_USER_JOB_FUNCTION)
      if ( NVM_OPSTATUS_IDLE != NVM_USER_JOB_FUNCTION() )
      {
        /* about 1ms~3ms */
        #if defined(NVM_OS_ALARM)        
        alarmOffset = NVM_TICKS_BURST_MODE;
        #endif
      }
      else
      #endif
      {
        do
        {
          if (MEM_FALSE == callSeq)
          {
            MEM_MAINFUNCTION_NVM();
            MEM_MAINFUNCTION_FEE();
            MEM_MAINFUNCTION_FLS();
            MEM_MAINFUNCTION_EA();
            MEM_MAINFUNCTION_EEP();
            callSeq = MEM_TRUE;
          }
          else
          {
            MEM_MAINFUNCTION_FLS(); /* polyspace MISRA-C3:8.5 [Justified:Low] "The function can be invoked by ASW layer, therefore Mem_Integration code also declare it" */
            MEM_MAINFUNCTION_FEE(); /* polyspace MISRA-C3:8.5 [Justified:Low] "The function can be invoked by ASW layer, therefore Mem_Integration code also declare it" */
              MEM_MAINFUNCTION_EEP();
              MEM_MAINFUNCTION_EA();
              MEM_MAINFUNCTION_NVM();
              callSeq = MEM_FALSE;
            }
          }
          while(
            #if ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U))
                (NVM_MULTIBLK_UNREQUESTED != NvM_GucReadAllRequest) /* NvM naming rule R40 */
            #elif ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U))
                (NVM_MULTIBLK_UNREQUESTED != NvM_ReadAllRequest)    /* NvM naming rule R44 */
            #else
                #error "NvM version is not support"
            #endif
          #if (MEM_WRITEALL_FAST_MODE == STD_ON)
            #if ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U))
            || (NVM_MULTIBLK_UNREQUESTED != NvM_GucWriteAllRequest) /* NvM naming rule R40 */
            #elif ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U))
            || (NVM_MULTIBLK_UNREQUESTED != NvM_WriteAllRequest)    /* NvM naming rule R44 */
            #else
              #error "NvM version is not support"
            #endif
            #if (NVM_BSWM_DEM_WRITENVDATA_CALL == STD_ON)
            || (DEM_JOB_TRIGGER == Dem_EvMem_WriteNvDataEndModeTriggered())
            #endif
          #endif
          );

          #if defined(NVM_OS_ALARM)
          alarmOffset = Mem_GetAlarmOffset();
          #endif        
      }

      #if defined(NVM_OS_ALARM)
      /* polyspace-begin MISRA-C3:2.1,14.3 DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "It depends on Os code, currently Os does not implement return E_NOT_OK" */
      if (E_OK != SetRelAlarm(NVM_OS_ALARM, alarmOffset, 0))
      {
        MEM_REPORT_ERROR(MEM_OSTASK_BSW_MEM_PROCESS_SID, MEM_E_ALARM);
        break;
      }
      /* polyspace-end MISRA-C3:2.1,14.3 DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "It depends on Os code, currently Os does not implement return E_NOT_OK" */
      #endif
    }
  /* polyspace-begin MISRA-C3:2.1 DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "It depends on Os code, currently Os does not implement return E_NOT_OK" */    
  }
  else
  {
    MEM_REPORT_ERROR(MEM_OSTASK_BSW_MEM_PROCESS_SID, MEM_E_EVENT);
  }
  /* polyspace-end MISRA-C3:2.1 DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "It depends on Os code, currently Os does not implement return E_NOT_OK" */

  (void)TerminateTask();
}

/*******************************************************************************
** Function Name        : Fee_IllegalStateNotification                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Aurix Fee IllegalStateNotification                  **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
*******************************************************************************/
#if (MEM_FEE_USED == STD_ON)
#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
FUNC(void, NVM_CODE) Fee_IllegalStateNotification (void)
{
  #if (NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U)
    /* Indicate job is completed with error */
    NvM_GddJobResultLowLevel = NVM_REQ_NOT_OK;  /* NvM naming rule R40 */
  #elif (NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U)
    /* Indicate job is completed with error */
    NvM_JobResultLowLevel = NVM_REQ_NOT_OK;     /* NvM naming rule R44 */
  #else
    #error "NvM version is not support"
  #endif
  /* Because application user could modify Fee_IllegalStateCallback function */
  Mem_Infineon_IllegalStateCallback();
}
#endif  
#endif /* (MEM_FEE_USED == STD_ON) */


#if ((defined(HWRESOURCE_S32K14X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)) || \
     (defined(HWRESOURCE_S32K31X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K31X)))
/* polyspace +4 MISRA-C3:8.5 [Justified:Low] "This function is invoked by Os." */
/* polyspace +3 MISRA-C3:8.4 [Justified:Low] "This function is invoked by Os." */
FUNC(boolean, NVM_CODE) Fls_DataEccHandler(uint8 ** instr_pt2pt, volatile uint32 * addr_CFSR, uint32 * addr_BFAR)
{
  boolean skipOrRetry = FALSE;
  
/* Fs_DataEccHandler can be called from the Os */
#if (MEM_FLS_USED == STD_ON)
  InsPtrType tempInsPtr;
  Fls_InstructionAddressType instr_pt;
  Fls_DataAddressType data_pt;
  uint32 syndrome;
  Fls_ExceptionDetailsType excDetails;
  Fls_CompHandlerReturnType specificHandlerResult = FLS_UNHANDLED;
  uint16 instrOpcode;     /* The instruction opcode(or the first 16 bits) value, stored in memory, for the instruction which caused the fault */
  uint8 thumbInstrSize;   /* Size of the instruction opcode stored in memory, 2 or 4 bytes */

  instr_pt = *instr_pt2pt;
  /* polyspace +1 CERT-C:INT36-C [Justified:Low] "This function is called from MCAL Fls via OS trap. The type Fls_DataAddressType is also declared by MCAL Fls and cannot be modified" */
#if (defined(HWRESOURCE_S32K14X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K14X))
  data_pt = (void const *)(*((uint32*)addr_BFAR));
#else
  data_pt = *((uint32*)addr_BFAR);
#endif
  /* polyspace +1 MISRA-C3:11.8 [Justified:Low] "This function is called from MCAL Fls via OS trap. The structure Fls_ExceptionDetailsType and parameter  addr_CFSR are also declared by MCAL Fls and cannot be modified" */
  syndrome = *((uint32*)addr_CFSR);

  /* Compute the instruction opcode size for the instruction which caused the hardfault. *
   * The value will be used to compute the address of the following instruction */
  /* polyspace +4 MISRA-C3:11.3 [Justified:Low] "Not a defect." */
  /* polyspace +3 MISRA-C3:11.8 [Justified:Low] "Not a defect." */  
  tempInsPtr.u_uint8[0] = (instr_pt[0]);
  tempInsPtr.u_uint8[1] = (instr_pt[1]);
  instrOpcode = tempInsPtr.u_uint16;

  /* Compute the size of the instruction which caused the fault */
  if (((instrOpcode & (uint16)0xE800) == (uint16)0xE800) ||   /* 0b11101x... */
      ((instrOpcode & (uint16)0xF000) == (uint16)0xF000) ||   /* 0b11110x... */
      ((instrOpcode & (uint16)0xF800) == (uint16)0xF800))     /* 0b11111x... */
  {
    /* Instruction size is 32 bits, 4 bytes */
    thumbInstrSize = 4;
  }
  else
  {
    /* Instruction size is 16 bits, 2 bytes */
    thumbInstrSize = 2;
  }

  excDetails.instruction_pt = instr_pt;
  excDetails.data_pt        = data_pt;
  excDetails.syndrome_u32   = syndrome;

  specificHandlerResult = Fls_DsiHandler(&excDetails);
  switch(specificHandlerResult)
  {
    case FLS_HANDLED_SKIP:
      /* exception was handled by one of the functions called above,                       *
       * continue execution, skipping the causing instruction                              *
       * In the test code we assume that the exception was caused by 16-bit/32-bit         *
       * load Thumb instruction => increment return address by the size of the instruction */
      /* polyspace +3 MISRA-C3:18.4 [Justified:Low] "Not a defect." */
      *((Fls_InstructionAddressType *)instr_pt2pt) = &instr_pt[thumbInstrSize];
      /* clear the flags and address register */
      *((volatile uint32*)addr_CFSR) = *((volatile uint32*)addr_CFSR);
      *((uint32*)addr_BFAR) = 0x0;
      skipOrRetry = OS_TRUE;
      break;
    /* polyspace-begin DEFECT:DEAD_CODE CERT-C:EXP39-C,MSC12-C [Justified:Low] "Although MCAL has this but it does not return FLS_HANDLED_RETRY. It depends on MCAL" */
    /* this enum type is defined in Fls_Flash_Types.h but Integration Fls does not implement */
    case FLS_HANDLED_RETRY:
      /* exception was handled by one of the functions called above,                          *
       * Continue execution, retrying the causing instruction                                 *
       * Thus, we don't need to modify instr_pt                                               */
      skipOrRetry = OS_TRUE;
      break;
    /* polyspace-end DEFECT:DEAD_CODE CERT-C:EXP39-C,MSC12-C [Justified:Low] "Although MCAL has this but it does not return FLS_HANDLED_RETRY. It depends on MCAL" */
    case FLS_UNHANDLED:
      /* special handling: try to store some info that nobody handled this exception          *
       * Then, try to shut-down in a controlled way. For this purpose we just fall through ...*/
    case FLS_HANDLED_STOP:
      /* Try to shut-down in a controlled way.                                               */
      /* If there's no chance to shut down in a controlled way, just fall through ...        */
    default:
      /* unexpected return - we end in an endless loop                                       */
      break;
  }
#endif

  return skipOrRetry;
}
#endif /* defined(HWRESOURCE_S32K14X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K14X) */

/*******************************************************************************
** Function Name        : Fls_EccFaultPreInit                                 **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Initialize the Fault Register for Fee/Fls init      **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Fee, Fls initalization should not be invoked        **
**                                                                            **
** Remarks              : This function is invoked  before Fee/Fls Init       **
**                                                                            **
*******************************************************************************/
#if (MEM_FLS_USED == STD_ON)
#if ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
static FUNC(void, NVM_CODE) Fls_EccFaultPreInit(void)
{
  /* u1RESET_REQ_EN = 0*/
  FAULT_REG(FAULT_STRUCT_CTL) &= ~(FAULT_RESET_REQ_EN);
  /* u1OUT_EN = 0*/
  FAULT_REG(FAULT_STRUCT_CTL) &= ~(FAULT_OUT_EN);
  /* u1TR_EN = 0*/
  FAULT_REG(FAULT_STRUCT_CTL) &= ~(FAULT_TR_EN);
  /* Disable Interrupt */
  FAULT_REG(FAULT_STRUCT_INTR_MASK) = 0u;
}
#endif

/*******************************************************************************
** Function Name        : Fls_EccFaultPostInit                                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Fault Struct init for Work Flash Error              **
**                        (Bus Error, Correctable, Non-Correctable ECC Error) **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Fee, Fls initalization should be invoked            **
**                                                                            **
** Remarks              : This function is invoked at the end of              **
**                        Mem_FeeInitPerform                                  **
**                                                                            **
*******************************************************************************/
#if ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
static FUNC(void, NVM_CODE) Fls_EccFaultPostInit(void)
{
  volatile uint32 faultDelay = 0u;

  /* Disable Interrupt for Initialization of Fault_Struct */
  FAULT_REG(FAULT_STRUCT_INTR_MASK) = 0u;
  /* Enable Work Flash Bus Error */
  FAULT_REG(FAULT_STRUCT_MASK1) |= \
    (1UL << ((uint32)CY_SYSFLT_FLASHC_WORK_BUS_ERROR - 32UL));
  /* Enable WorkFlash Correctable ECC Error */
  FAULT_REG(FAULT_STRUCT_MASK1) |= \
    (1UL << ((uint32)CY_SYSFLT_FLASHC_WORK_C_ECC - 32UL));
  /* Enable WorkFlash Non-Correctable ECC Error */
  FAULT_REG(FAULT_STRUCT_MASK1) |= \
    (1UL << ((uint32)CY_SYSFLT_FLASHC_WORK_NC_ECC - 32UL));

  /* Clear all fault status of STRUCT*/
  do{
    /* Clear Fault Interupt Flag */
    FAULT_REG(FAULT_STRUCT_INTR) = 0x00000001UL;    
    /* Clear Existing Fault */
    FAULT_REG(FAULT_STRUCT_STATUS) = 0x00000000UL;
    /* Wait short time for clear status */
    for(faultDelay = 0; faultDelay < 10; faultDelay++)
    {
      /* Do Nothing. Just for delay of H/W */
    }
  } while(FAULT_VALID_MASK == \
  ((FAULT_REG(FAULT_STRUCT_STATUS)) & FAULT_VALID_MASK));

  /* Clear Fault Struct Status (Interrupt to CPU) */
  FAULT_REG(FAULT_STRUCT_STATUS) = 0u;
  /* Enable Interrupt */
  FAULT_REG(FAULT_STRUCT_INTR_MASK) = 1u;
}
#endif

/*******************************************************************************
** Function Name        : Fls_EccFaultHandler                                 **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Set Fls_Fault_Handling to Fls for notifying         **
**                        Ded ECC Error. Only the address which configured in **
**                          fls (SWP fls uses)is valid.                       **
**                                                                            **
**                        HOST Fls Area (defined by Ecud_fls.arxml)           **
**                         - Start Addr : FEE_FLS_BASE_ADDRESS                **
**                         - End Addr   : FEE_FLS_BASE_ADDRESS +              **
**                                        FEE_WORK_FLASH_RELATIVE_END_ADDRESS **
**                          --------------------------------                  **
**                          | Large Sector [2KB / Sector]  |                  **
**                          | -----------------------------|                  **
**                          | -----------------------------|                  **
**                          | Small Sector [128B / Sector] |                  **
**                          --------------------------------                  **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : This function is invoked by                         **
**                         ISR(Fls_Isr_DataEccHandler_Cat2)                   **
**                                                                            **
*******************************************************************************/
#if ((defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
     (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
     (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
     (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
static FUNC(void, NVM_CODE) Fls_EccFaultHandler(void)
{
  uint32 eccTargetAddr = 0U;
  uint32 configuredStartAddr = 0U;
  uint32 configuredEndAddr = 0U;

  /* Check Valid Bit of Fault Struct */
  if(FAULT_VALID_MASK == \
    ((FAULT_REG(FAULT_STRUCT_STATUS) & FAULT_VALID_MASK)))
  {
    /* Check Fault Struct Index. Only considering workflash related Error */
    switch(FAULT_REG(FAULT_STRUCT_STATUS) & FAULT_INDEX_MASK)
    {
      case CY_SYSFLT_FLASHC_WORK_BUS_ERROR: /* No Break */
      case CY_SYSFLT_FLASHC_WORK_C_ECC: /* No Break */
      case CY_SYSFLT_FLASHC_WORK_NC_ECC:
        /* 
         * Host Fls considers only Host's work flash sector 
         * Valid Address : ECC Address < Configured Address in Ecud_Fls.arxml
         */
        eccTargetAddr = ((FAULT_REG(FAULT_STRUCT_DATA0) & FAULT_DATA0_MASK) | (uint32)(0x10000000)); 
        configuredEndAddr = Fls_MemoryMap_0[0].physical + Fls_Config_0.TotalSize;
        configuredStartAddr = Fls_MemoryMap_0[0].physical;

        if ((eccTargetAddr < configuredEndAddr) && (eccTargetAddr >= configuredStartAddr))
        {
         /* 
          * When Fls_Fault_Handling() is called, then callback function which configured 
          * in Ecud_Fls.arxml - FlsConfigSet_0 - Error Notification is called.
          * The Ecc error correction is finally excuted in the Error CallBack.
          * Reference : UsersGuide_Fls_1_0_TraveoII_Autosar.pdf chapter of Fault.
          */
          Fls_Fault_Handling();
        }
        else
        {
         /* 
          * If ECC Error target address is not located in the area of host, do nothing 
          * Because M0+ does not use Fault_Struct (using Flash DMA Bus Error),
          * it's ok to clear the Fault Status.
          */
        }
        break;

      default:
        /*
         * When Error is not related to WorkFlash, 
         * do Nothing 
         */
        break;
    }
  }
  else
  {
    /* If valid bit is not set, do noting (Fail-Safety for H/W error) */
  }
  /* Clear Fault Interupt Flag */
  FAULT_REG(FAULT_STRUCT_INTR) = 1u;
  /* Clear Fault Struct Status */
  FAULT_REG(FAULT_STRUCT_STATUS) = 0u;
}
#endif

#if (\
  (defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
  (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
  (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
  (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
ISR(Fls_Isr_DataEccHandler_Cat2)
{
  Fls_EccFaultHandler();
}
#endif

#endif /* Cypress (MEM_FLS_USED == STD_ON) */

/*******************************************************************************
** Function Name      : NvM_CddGetStatus                                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Service to return the status                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : MemIf_StatusType                                      **
**                                                                            **
**                     MEMIF_UNINIT:The memory stack has not been initialized.**
**                     MEMIF_IDLE:The memory stack is currently idle.         **
**                     MEMIF_BUSY:The memory stack is currently busy.         **
**                                                                            **
** Remarks            : Mem_GetStatus and memory stack operations and cannot  **
**                      execute simultaneously. In order to avoid conflicts   ** 
**                      this API should be used in the exclusive area         **
*******************************************************************************/
FUNC(NvM_OpStatusType, NVM_CODE) NvM_CddGetStatus(void)
{
  NvM_OpStatusType retVal = NVM_OPSTATUS_UNINIT;

#if ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U))
  if(NvM_GblInitDone == NVM_TRUE)   /* NvM naming rule R40 */
#elif ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U))
  if(NvM_InitStatus == NVM_TRUE)    /* NvM naming rule R44 */
#else
  #error "NvM version is not support"
#endif
  {
    #if (MEM_FLS_USED == STD_ON)
    if(Fls_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    #endif

    #if (MEM_FEE_USED == STD_ON)
    if(Fee_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    #endif
    /* The state of external epromes should also be checked. 
     * If a user job is performed without checking the status, 
     * it is possible that ea/eep/nvm mainfunction are not called in task.
     * during a user job is performing.*/
    #if (MEM_EA_USED == STD_ON)
    if(Ea_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else if(Eep_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    #endif
    if (
#if ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION < 4U))
      /* NvM naming rule R40 */
      (NVM_MULTIBLK_UNREQUESTED != NvM_GucReadAllRequest)   ||
      (NVM_MULTIBLK_UNREQUESTED != NvM_GucWriteAllRequest)  ||
      (NVM_IDLE != NvM_GucState)                            ||
      (0U       != NvM_GucStdQueEnDis)
#elif ((NVM_AR_RELEASE_MAJOR_VERSION == 4U) && (NVM_AR_RELEASE_MINOR_VERSION == 4U))
      /* NvM naming rule R44 */
      (NVM_MULTIBLK_UNREQUESTED != NvM_ReadAllRequest)   ||
      (NVM_MULTIBLK_UNREQUESTED != NvM_WriteAllRequest)  ||
      (NVM_IDLE != NvM_State)                            ||
      (NVM_SIZE_STANDARD_JOB_QUEUE != NvM_StdFreeSlotsAvail)
#else
  #error "NvM version is not support"
#endif
    )
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    {
      retVal = NVM_OPSTATUS_IDLE;
    }
  }

  return retVal;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-end VARIABLE:ALL [Not a defect:Low] "Not a defect" */
/* polyspace-end MISRA-C3:11.4,20.9,D4.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */
/*******************************************************************************
**                         End of File                                        **
*******************************************************************************/
