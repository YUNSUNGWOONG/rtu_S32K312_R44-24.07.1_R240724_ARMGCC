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
**  FILE-NAME : EcuM_Callout_Stubs.c                                          **
**                                                                            **
**  TARGET    : S32G2x                                                         **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   :  Callouts implementation for EcuM module                      **
**               EcuM_AL_DriverInitZero                                       **
**               EcuM_AL_DriverInitOne                                        **
**               EcuM_AL_DriverRestart                                        **
**               EcuM_OnGoOffOne                                              **
**               EcuM_OnGoOffTwo                                              **
**               EcuM_AL_SwitchOff                                            **
**               EcuM_AL_Reset                                                **
**               EcuM_EnableWakeupSources                                     **
**               EcuM_DisableWakeupSources                                    **
**               EcuM_CheckWakeup                                             **
**               EcuM_StartWakeupSources                                      **
**               EcuM_StopWakeupSources                                       **
**               EcuM_CheckValidation                                         **
**               EcuM_GenerateRamHash                                         **
**               EcuM_SleepActivity                                           **
**               EcuM_CheckRamHash                                            **
**               EcuM_DeterminePbConfiguration                                **
**               EcuM_ErrorHook                                               **
**               EcuM_SetMode                                                 **
**               EcuM_Enable_MPU                                              **
**               EcuM_PreInit                                                 **
**               EcuM_PostInit                                                **
**               EcuM_PreSleep                                                **
**               EcuM_PostSleep                                               **
**               EcuM_RequestSleep                                            **
**               EcuM_RequestReset                                            **
**               EcuM_RequestOff                                              **
**               EcuM_StartCheckWakeup                                        **
**               EcuM_EndCheckWakeup                                          **
**               EcuM_AL_DriverInitCoreWise_PreOs                             **
**               EcuM_AL_DriverInitCoreWise_PostOs                            **
**               Init_McuSetMode                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0      23-Oct-2023   Eugean Kim    CP44-3079                           **
** 1.2.1      11-Aug-2023   Eugean Kim    CP44-2699                           **
** 1.2.0      25-Jul-2023   Eugean Kim    CP44-2600                           **
** 1.1.0      07-Jul-2023   Eugean Kim    CP44-2365                           **
** 1.0.6      29-Mar-2023   Manje Woo     CP44-1919                           **
** 1.0.5      18-Nov-2022   Manje Woo     CP44-1137                           **
** 1.0.4      08-Aug-2022   Manje Woo     CP44-727                            **
** 1.0.3.1    19-Jul-2022   Manje Woo     CP44-624                            **
** 1.0.3      24-Feb-2022   TriBD         R44_2021 #23445                     **
** 1.0.2      17-Jan-2022   TriBD         R44_2021 #23275                     **
** 1.0.1      28-Sep-2021   TriBD         R44_2021 #20029                     **
** 1.0.0      28-Sep-2021   TriBD         Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.4 [Justified:Low] Justify with annotations */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Generated_Callouts.h"
#include "EcuM_Ram.h"
#include "BswM_EcuM.h"
#include "Mcu.h"
#include "SchM_EcuM.h"
#include "Rte_EcuM.h"
#include "WdgM.h"

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
#define RTE_ALLOW_CROSS_HEADER_INCLUSION
#include "Rte_EcuM_Slave1.h"
#endif

#if (OS_FPU_SUPPORT == STD_ON)
#include "Os_Arch_Regs.h"
#endif

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#include "Gpt.h"
#endif

#include "HwResource.h"
//#include "arm_ghs.h"

#if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
#include "LowPower_Callout.h"
#endif

#if (SWP_USE_DATALOG == STD_ON)
#include "CDD_DataLog.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
#if (HWRESOURCE_MCU(HWRESOURCE_S32K312)||HWRESOURCE_MCU(HWRESOURCE_S32K314))
#define CPU_MPU_MEMORY_COUNT (7U)
#endif

#define ECUM_MPU_A_COUNT     (3U)

/* ECUM_MPU - Register Layout Typedef */
typedef struct {
  uint8  ECUM_RESERVED0[3472U];
  uint32 ECUM_TYPE;                  /**< MPU Type Register, offset: 0xD90 */
  uint32 ECUM_CTRL;                  /**< MPU Control Register, offset: 0xD94 */
  uint32 ECUM_RNR;                   /**< MPU Region Number Register, offset: 0xD98 */
  uint32 ECUM_RBAR;                  /**< MPU Region Base Address Register, offset: 0xD9C */
  uint32 ECUM_RASR;                  /**< MPU Region Attribute and Size Register, offset: 0xDA0 */
  struct {                           /* offset: 0xDA4, array step: 0x8 */
    uint32 ECUM_RBAR;                /**< Alias of RBAR0..Alias of RBAR2, array offset: 0xDA4, array step: 0x8 */
    uint32 ECUM_RASR;                /**< Alias of RASR0..Alias of RASR2, array offset: 0xDA8, array step: 0x8 */
  } ECUM_Alias[ECUM_MPU_A_COUNT];
} ECUM_MPU_Type;

/* ECUM_MPU - Peripheral instance base addresses */
/* Peripheral ECUM_MPU base address */
#define ECUM_MPU_BASE                             (0xE000E000UL)
/* CTRL Bit Fields */
#define ECUM_MPU_CTRL_ENABLE_MASK                 0x1U

#if (HWRESOURCE_MCU(HWRESOURCE_S32K312) && (SWP_USE_DUALM == STD_OFF) )
/**
  \brief  S32K312 Memory region tables. (Single Bank)

  Region  Description                   Start       End           Size[KB]  permission                attribute                 execute              srd     enable
--------  ----------------------------  ----------  ----------  ----------  ------------------------  ------------------------  -------------------  ------  ----------
       0  BACKGROUND_REGION             0x0         0xFFFFFFFF     4194304  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_STR_ORD_DEV      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       1  CM7_SELF_ITCM_REGION          0x0         0x00007FFF          32  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       2  PROGRAM_FLASH_REGION_ADDR     0x00400000  0x005FFFFF        2048  MPU_ACCESS_P_PRIV_RO      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       3  DATA_FLASH_REGION_ADDR        0x10000000  0x1001FFFF         128  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       4  CM7_SELF_DTCM_REGION_ADDR     0x20000000  0x2000FFFF          64  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       5  SRAM_REGION_ADDR              0x20400000  0x20417FFF          96  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       6  PERI_REGISTER_REGION_ADDR     0x40008000  0x40807FFF        8192  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_SHR_DEV          MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
*/
static const uint32 EcuM_Rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x00400000UL, 0x10000000UL, 0x20000000UL, 0x20400000UL, 0x40008000UL};
static const uint32 EcuM_Rasr[CPU_MPU_MEMORY_COUNT] = {0x1100003FUL, 0x0102001DUL, 0x05020029UL, 0x11020021UL, 0x1102001FUL, 0x0102F821UL, 0x1101002DUL};
#endif

#if (HWRESOURCE_MCU(HWRESOURCE_S32K312) && (SWP_USE_DUALM == STD_ON) )
/**
  \brief  S32K312 Memory region tables. (Dual Bank)

  Region  Description                   Start       End           Size[KB]  permission                attribute                 execute              srd     enable
--------  ----------------------------  ----------  ----------  ----------  ------------------------  ------------------------  -------------------  ------  ----------
       0  BACKGROUND_REGION             0x0         0xFFFFFFFF     4194304  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_STR_ORD_DEV      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       1  CM7_SELF_ITCM_REGION          0x0         0x00007FFF          32  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       2  PROGRAM_FLASH_REGION_ADDR     0x00400000  0x004FFFFF        1024  MPU_ACCESS_P_PRIV_RO      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       3  DATA_FLASH_REGION_ADDR        0x10000000  0x1001FFFF         128  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       4  CM7_SELF_DTCM_REGION_ADDR     0x20000000  0x2000FFFF          64  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       5  SRAM_REGION_ADDR              0x20400000  0x20417FFF          96  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       6  PERI_REGISTER_REGION_ADDR     0x40008000  0x40807FFF        8192  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_SHR_DEV          MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
*/
static const uint32 EcuM_Rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x00400000UL, 0x10000000UL, 0x20000000UL, 0x20400000UL, 0x40008000UL};
static const uint32 EcuM_Rasr[CPU_MPU_MEMORY_COUNT] = {0x1100003FUL, 0x0102001DUL, 0x05020027UL, 0x11020021UL, 0x1102001FUL, 0x0102F821UL, 0x1101002DUL};
#endif

#if (HWRESOURCE_MCU(HWRESOURCE_S32K314) && (SWP_USE_DUALM == STD_OFF))
/**
  \brief  S32K314 Memory region tables. (Single Bank)

  Region  Description                   Start       End           Size[KB]  permission                attribute                 execute              srd     enable
--------  ----------------------------  ----------  ----------  ----------  ------------------------  ------------------------  -------------------  ------  ----------
       0  BACKGROUND_REGION             0x0         0xFFFFFFFF     4194304  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_STR_ORD_DEV      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       1  CM7_SELF_ITCM_REGION          0x0         0x00007FFF          32  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       2  PROGRAM_FLASH_REGION_ADDR     0x00400000  0x007FFFFF        4096  MPU_ACCESS_P_PRIV_RO      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       3  DATA_FLASH_REGION_ADDR        0x10000000  0x1001FFFF         128  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       4  CM7_SELF_DTCM_REGION_ADDR     0x20000000  0x2000FFFF          64  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       5  SRAM_REGION_ADDR              0x20400000  0x20427FFF         160  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       6  PERI_REGISTER_REGION_ADDR     0x40008000  0x40807FFF        8192  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_SHR_DEV          MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
*/
static const uint32 EcuM_Rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x00400000UL, 0x10000000UL, 0x20000000UL, 0x20400000UL, 0x40008000UL};
static const uint32 EcuM_Rasr[CPU_MPU_MEMORY_COUNT] = {0x1100003FUL, 0x0102001DUL, 0x0502002BUL, 0x11020021UL, 0x1102001FUL, 0x0102E025UL, 0x1101002DUL};
#endif


#if (HWRESOURCE_MCU(HWRESOURCE_S32K314) && (SWP_USE_DUALM == STD_ON))
/**
  \brief  S32K314 Memory region tables. (Dual Bank)

  Region  Description                   Start       End           Size[KB]  permission                attribute                 execute              srd     enable
--------  ----------------------------  ----------  ----------  ----------  ------------------------  ------------------------  -------------------  ------  ----------
       0  BACKGROUND_REGION             0x0         0xFFFFFFFF     4194304  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_STR_ORD_DEV      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       1  CM7_SELF_ITCM_REGION          0x0         0x00007FFF          32  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       2  PROGRAM_FLASH_REGION_ADDR     0x00400000  0x005FFFFF        2048  MPU_ACCESS_P_PRIV_RO      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       3  DATA_FLASH_REGION_ADDR        0x10000000  0x1001FFFF         128  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       4  CM7_SELF_DTCM_REGION_ADDR     0x20000000  0x2000FFFF          64  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
       5  SRAM_REGION_ADDR              0x20400000  0x20427FFF         160  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_NORM_MEM_WT      MPU_INST_ACCESS_EN   0x00    MPU_ENABLE
       6  PERI_REGISTER_REGION_ADDR     0x40008000  0x40807FFF        8192  MPU_ACCESS_P_PRIV_RW      MPU_ATTR_SHR_DEV          MPU_INST_ACCESS_DIS  0x00    MPU_ENABLE
*/
static const uint32 EcuM_Rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x00400000UL, 0x10000000UL, 0x20000000UL, 0x20400000UL, 0x40008000UL};
static const uint32 EcuM_Rasr[CPU_MPU_MEMORY_COUNT] = {0x1100003FUL, 0x0102001DUL, 0x05020029UL, 0x11020021UL, 0x1102001FUL, 0x0102E025UL, 0x1101002DUL};
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : EcuM_AL_DriverInitZero                              **
**                                                                            **
** Service ID           : 0x31                                                **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup activities for   **
**                        loading the post-build configuration data. Note:    **
**                        Here only pre-compile and link-time configurable    **
**                        modules may be used.                                **
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
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverInitZero                          **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09120 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitZero(void)
{
  /* @Trace: EcuM_SUD_API_121 */
  #if (STD_ON == ECUM_DRIVER_INIT_ZERO)
  EcuM_Gen_AL_DriverInitZero();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_DriverInitOne                               **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup activities in    **
**                        case of a power on reset                            **
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
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverInitOne                           **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09120 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitOne(void)
{
  /* @Trace: EcuM_SUD_API_122 */
  #if (ECUM_DRIVER_INIT_ONE == STD_ON)
  EcuM_Gen_AL_DriverInitOne();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_DriverRestart                               **
**                                                                            **
** Service ID           : 0x45                                                **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup activities in    **
**                        the wakeup case.                                    **
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
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverRestart                           **
*******************************************************************************/
/* @Trace: SRS_EcuM_AR_00003 SRS_ModeMgm_09120 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverRestart(void)
{
  /* @Trace: EcuM_SUD_API_123 */
  #if (ECUM_DRIVER_RESTART == STD_ON)
  EcuM_Gen_AL_DriverRestart();
  #endif
} /* End of EcuM_AL_DriverRestart */

/*******************************************************************************
** Function Name        : EcuM_OnGoOffOne                                     **
**                                                                            **
** Service ID           : 0x3C                                                **
**                                                                            **
** Description          : This call allows the system designer to notify that **
**                        the GO OFF I state is about to be entered.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)     : EcuM_State                 **
**                        Function(s) invoked    :                            **
**                        GetCoreID(), BswM_EcuM_CurrentState(),              **
**                        EcuM_Gen_AL_DriverDeInitCoreWise_PostOs()           **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09127 SRS_ModeMgm_09147 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffOne(void)
{
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  CoreIdType coreId;
  /* Get core Id */
  coreId = GetCoreID();
  /* @Trace: EcuM_SUD_API_125 */
  #if(STD_ON == ECUM_DRIVER_DEINIT_CORE_WISE_POST_OS)
  /* Driver De-Initialize modules per cores */
  EcuM_Gen_AL_DriverDeInitCoreWise_PostOs(coreId);
  #endif /* End of if (STD_ON == ECUM_DRIVER_DEINIT_CORE_WISE_POST_OS) */
  /* Check curent core is master or not */
  if (OS_CORE_ID_MASTER == coreId)
  {
    EcuM_State = ECUM_STATE_GO_OFF_ONE;
    /* Indicate state change to BswM */
    BswM_EcuM_CurrentState(EcuM_State);
  }
  else
  {
    /* Do nothing */
  }
  #else /* else if (STD_OFF == ECUM_MULTI_CORE_SUPPORT) */
  EcuM_State = ECUM_STATE_GO_OFF_ONE;
  /* Indicate state change to BswM */
  BswM_EcuM_CurrentState(EcuM_State);
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_OnGoOffTwo                                     **
**                                                                            **
** Service ID           : 0x3D                                                **
**                                                                            **
** Description          : This call allows the system designer to notify that **
**                        the GO OFF II state is about to be entered.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)     : EcuM_State                 **
**                        Function(s) invoked    :                            **
**                        GetCoreID(),                                        **
**                        EcuM_Gen_AL_DriverDeInitCoreWise_OffOs()            **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09127 SRS_ModeMgm_09147 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffTwo(void)
{
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  CoreIdType coreId;
  /* Get core Id */
  coreId = GetCoreID();
  #if(STD_ON == ECUM_DRIVER_DEINIT_CORE_WISE_OFF_OS)
  /* Driver De-Initialize modules per cores */
  EcuM_Gen_AL_DriverDeInitCoreWise_OffOs(coreId);
  #endif /* End of if (STD_ON == ECUM_DRIVER_DEINIT_CORE_WISE_OFF_OS) */
  /* Set state to ECUM_STATE_GO_OFF_TWO if core is master*/
  if (OS_CORE_ID_MASTER == coreId)
  {
    /* @Trace: EcuM_SUD_API_126 */
    /* Sitch EcuM State to GO OFF TWO */
    EcuM_State = ECUM_STATE_GO_OFF_TWO;
  }
  else
  {
    /*Do nothing */
  }
  #else /* else if (STD_OFF == ECUM_MULTI_CORE_SUPPORT) */
  EcuM_State = ECUM_STATE_GO_OFF_TWO;
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_SwitchOff                                   **
**                                                                            **
** Service ID           : 0x3E                                                **
**                                                                            **
** Description          : This callout shall take the code for shutting off   **
**                        the power supply of the ECU. If the ECU cannot      **
**                        unpower itself, a reset may be an adequate reaction.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)     : EcuM_State                 **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09127 SRS_ModeMgm_09147 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SwitchOff(void)
{
  /* @Trace: EcuM_SUD_API_127 */
  /* Switch EcuM state to OFF */
  EcuM_State = ECUM_STATE_OFF;
}

/*******************************************************************************
** Function Name        : EcuM_AL_Reset                                       **
**                                                                            **
** Service ID           : 0x4C                                                **
**                                                                            **
** Description          : This callout shall take the code for shutting off   **
**                        the power supply of the ECU. If the ECU cannot      **
**                        unpower itself, a reset may be an adequate reaction.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : reset                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_State                 **
**                        Function(s) invoked    : Mcu_PerformReset()         **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09127 SRS_ModeMgm_09147 SRS_ModeMgm_09116 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_Reset(EcuM_ResetType reset)
{
  /* @Trace: EcuM_SUD_API_128 */
  EcuM_State = ECUM_STATE_RESET;

  if ((reset == ECUM_RESET_MCU) || (reset == ECUM_INVALID_SHUTDOWN))
  {
    Mcu_PerformReset();
  }
  else if (reset == ECUM_RESET_WDG)
  {
    /* Indicate reset WdgM module */
    /* Redmine #17239 */
    WdgM_PerformReset();
  }
  else
  {
    /* Do nothing */
  }
}

/*******************************************************************************
** Function Name        : EcuM_EnableWakeupSources                            **
**                                                                            **
** Service ID           : 0x3F                                                **
**                                                                            **
** Description          : The ECU Manager Module calls EcuM_EnableWakeupSource**
**                        to allow the system designer to notify wakeup       **
**                        sources defined in the wakeupSource bitfield that   **
**                        SLEEP will be entered and to adjust their source    **
**                        accordingly.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                        EcuM_Gen_EnableWakeupSources(), isMasterCore(),     **
**                        DataLog_SetSleepOKLog(),                            **
**                        EcuM_H2LTransition_Callout_Swp(),                   **
**                        EcuM_H2LTransition_Callout_App()                    **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 */
FUNC(void, ECUM_CODE) EcuM_EnableWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  boolean isMasterCore;
  /* @Trace: EcuM_SUD_API_129 */
  /* execute enable wakeup resource */
  isMasterCore = EcuM_IsMasterCore();
  /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
  if (TRUE == isMasterCore)
  {
    /* polyspace +1 MISRA-C3:2.2 [Not a defect:Low] "EcuM_Gen_EnableWakeupSources function will be written by customer and then it will not be a deadcode" */
    EcuM_Gen_EnableWakeupSources(wakeupSource);
    #if (SWP_USE_DATALOG == STD_ON)
    DataLog_SetSleepOKLog();
    #endif
  }
  /* polyspace-end MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  /* Callout For Platform */
  EcuM_H2LTransition_Callout_Swp();

  /* Callout For User */
  /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "Scope to be implemented by user" */
  EcuM_H2LTransition_Callout_App();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_DisableWakeupSources                           **
**                                                                            **
** Service ID           : 0x44                                                **
**                                                                            **
** Description          : The callout shall set up the given wakeup source(s) **
**                        so that they are not able to wakeup the ECU.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                        EcuM_Gen_DisableWakeupSources(), isMasterCore(),    **
**                        DataLog_SetWakeupEventLog(),                        **
**                        EcuM_L2HTransition_Callout_Swp(),                   **
**                        EcuM_L2HTransition_Callout_App()                    **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CODE) EcuM_DisableWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  boolean isMasterCore;
  /* @Trace: EcuM_SUD_API_130 */
  /* Execute disable wakeup soucer */
  isMasterCore = EcuM_IsMasterCore();
  /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
  if (TRUE == isMasterCore)
  {
    /* polyspace +1 MISRA-C3:2.2 [Not a defect:Low] "EcuM_Gen_DisableWakeupSources function will be written by customer and then it will not be a deadcode" */
    EcuM_Gen_DisableWakeupSources(wakeupSource);
    #if (SWP_USE_DATALOG == STD_ON)
    DataLog_SetWakeupEventLog();
    #endif
  }
  /* polyspace-end MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  /* Callout For Platform */
  EcuM_L2HTransition_Callout_Swp();
  /* Callout For User */
  /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "Scope to be implemented by user" */
  EcuM_L2HTransition_Callout_App();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_CheckWakeup                                    **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : This callout is called by the EcuM to poll a wakeup **
**                        source. It shall also be called by the ISR of a     **
**                        wakeup source to set up the PLL and check other     **
**                        wakeup sources that may be connected to the same    **
**                        interrupt.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    : Gpt_CheckWakeup(),         **
**                        EcuM_Gen_CheckWakeup(),                             **
**                        SchM_Enter_EcuM_ALARM_TIME_PROTECTION(),            **
**                        SchM_Exit_EcuM_ALARM_TIME_PROTECTION()              **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckWakeup
    (EcuM_WakeupSourceType wakeupSource)
{
  /* @Trace: EcuM_SUD_API_131 */
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  if (ECUM_ZERO != (wakeupSource & ECUM_ALARM_WAKEUP_SOURCE_ID))
  {
    SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
    /* Check wakeup source ID in Gpt */
    Gpt_CheckWakeup(ECUM_ALARM_WAKEUP_SOURCE_ID);

    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
  }
  else
  #endif
  {
    /* check EcuM wakeup of request source */
    EcuM_Gen_CheckWakeup(wakeupSource);
  }
}

/*******************************************************************************
** Function Name        : EcuM_StartWakeupSources                             **
**                                                                            **
** Service ID           : 0x46                                                **
**                                                                            **
** Description          : The callout shall start the given wakeup source(s)  **
**                        so that they are ready to perform wakeup validation.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_StopWakeupSources                              **
**                                                                            **
** Service ID           : 0x48                                                **
**                                                                            **
** Description          : The callout shall stop the given wakeup source(s)   **
**                        after unsuccessful wakeup validation.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_StopWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_CheckValidation                                **
**                                                                            **
** Service ID           : 0x47                                                **
**                                                                            **
** Description          : This callout is called by the EcuM to validate a    **
**                        wakeup source. If a valid wakeup has been detected, **
**                        it shall be reported to EcuM via                    **
**                        EcuM_ValidateWakeupEvent().                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckValidation
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_GenerateRamHash                                **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : Used just before Putting the ECU physically to sleep**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_EcuM_AR_00002 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_GenerateRamHash(void)
{
  /* Callout shall be filled by the system designer */
}

/*******************************************************************************
** Function Name        : EcuM_SleepActivity                                  **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : This callout is invoked periodically in all reduced **
**                        clock sleep modes. It is explicitly allowed to poll **
**                        wakeup sources from this callout and to call wakeup **
**                        notification functions to indicate the end of the   **
**                        sleep state to the ECU State Manager.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09118 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_SleepActivity(void)
{
  /* Callout shall be filled by the system designer */
}

/*******************************************************************************
** Function Name        : EcuM_CheckRamHash                                   **
**                                                                            **
** Service ID           : 0x43                                                **
**                                                                            **
** Description          : This callout is intended to provide a RAM integrity **
**                        test.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8 - 0: RAM integrity test failed                **
**                              - else: RAM integrity test passed             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_EcuM_AR_00002 */
FUNC(uint8, ECUM_CALLOUT_CODE) EcuM_CheckRamHash(void)
{
  return (1);
}

/*******************************************************************************
** Function Name        : EcuM_DeterminePbConfiguration                       **
**                                                                            **
** Service ID           : 0x32                                                **
**                                                                            **
** Description          : This callout should evaluate some condition,        **
**                        like port pin or NVRAM value, to determine which    **
**                        post-build configuration shall be used in the       **
**                        remainder of the startup process. It shall load     **
**                        this configuration data into a piece of memory that **
**                        is accessible by all BSW modules and shall return a **
**                        pointer to the EcuM post-build configuration as a   **
**                        base for all BSW module post-build configurations.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_ConfigType*                                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_Config_<PredefinedVariant.shortName>           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09120 SRS_BSW_00414 */
const EcuM_ConfigType* EcuM_DeterminePbConfiguration(void)
{
  P2CONST(EcuM_ConfigType, ECUM_CONST, ECUM_CONST) ptrConfigPtr;

  /* @Trace: EcuM_SUD_API_138 */
  /* The return value is updated only for compilation purpose. Valid address
   * of EcuM_Config structure needs to be provided here.
   * - Name of EcuM_Config structure: EcuM_Config_<PredefinedVariant.shortName>
   *   A list of 'PredefinedVariant.shortName' can be found in
   *   'EcuC/EcucPostBuildVariants' in the Ecud_EcuC.arxml file */
  ptrConfigPtr = &EcuM_Config_Variant_FL;
  return (ptrConfigPtr);
}

/*******************************************************************************
** Function Name        : EcuM_ErrorHook                                      **
**                                                                            **
** Service ID           : 0x30                                                **
**                                                                            **
** Description          : In unrecoverable error situations, the ECU State    **
**                        Manager will call this callout. It is up the        **
**                        system integrator to react accordingly              **
**                        (reset, halt, restart, safe state etc. )            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : reason                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00327 SRS_EcuM_AR_00008 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_ErrorHook(uint16 reason)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(reason);
}

/*******************************************************************************
** Function Name        : EcuM_SetMode                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Callout used for Set Mcu Mode                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                        Mcu_SetMode()                                       **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_SetMode
  (Mcu_ModeType McuMode)
{
  Mcu_SetMode(McuMode);
}

#if (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
/*******************************************************************************
** Function Name        : EcuM_Enable_MPU                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Enable MPU of each cores                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
*******************************************************************************/
static FUNC(void, ECUM_CALLOUT_CODE) EcuM_Enable_MPU(void)
{
  /* Peripheral ECUM_MPU base pointer */
  /* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
  volatile ECUM_MPU_Type *ECUM_MPU = ((ECUM_MPU_Type *)ECUM_MPU_BASE);
  /* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
  uint8 EcuM_LddRegionNum = 0U;
  //__DMB();
  __asm("dmb");

  /* Set default memory regions */
    for (EcuM_LddRegionNum = 0U; EcuM_LddRegionNum < CPU_MPU_MEMORY_COUNT; EcuM_LddRegionNum++)
    {
        ECUM_MPU->ECUM_RNR  = EcuM_LddRegionNum;
        ECUM_MPU->ECUM_RBAR = EcuM_Rbar[EcuM_LddRegionNum];
        ECUM_MPU->ECUM_RASR = EcuM_Rasr[EcuM_LddRegionNum];
    }
    /* Enable MPU */
    ECUM_MPU->ECUM_CTRL |= ECUM_MPU_CTRL_ENABLE_MASK;

    //__asm("dsb");
    //__asm("isb");
    __asm("dsb");
    __asm("isb");

}
#endif

/*******************************************************************************
** Function Name        : EcuM_PreInit                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Callout used for before EcuM Init                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_ResetReason           **
**                        Function(s) invoked    : EcuM_IsMasterCore()        **
**                        EcuM_Enable_Pcache(), EcuM_Enable_Dcache()          **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PreInit(void)
{
  boolean isMasterCore;
  /* Check current core is master core */
  isMasterCore = EcuM_IsMasterCore();

  /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
  if (TRUE == isMasterCore)
  {
    /* Set default reset reason */
    EcuM_ResetReason = MCU_POWER_ON_RESET;
  }
  /* polyspace-end MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
 #if (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
  /* Enable FPU */
  #if (OS_FPU_SUPPORT == STD_ON)
  OS_SCB_CPACR.B.CP10 = OS_SCB_CPACR_CP10_FULL_ACCESS;
  OS_SCB_CPACR.B.CP11 = OS_SCB_CPACR_CP11_FULL_ACCESS;

  OS_FPU_FPCCR.B.LSPEN = OS_FPU_FPCCR_LSPEN_DISABLE;
  OS_FPU_FPCCR.B.ASPEN = OS_FPU_FPCCR_ASPEN_DISABLE;

  __asm("dsb");
  __asm("isb");
  #endif
  EcuM_Enable_MPU();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_PostInit                                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Callout used for after Mcal Init                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PostInit(void)
{
}

/*******************************************************************************
** Function Name        : EcuM_PreSleep                                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Pre Callout for Go Halt Sequence                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    : EcuM_ClearWakeupEvent      **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PreSleep(void)
{
  /* Clear All Wakeup Sources */
  EcuM_ClearWakeupEvent(ECUM_WKSOURCE_ALL_SOURCES);
}

/*******************************************************************************
** Function Name        : EcuM_PostSleep                                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Post Callout for Go Halt Sequence                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : GoHaltResult                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PostSleep
  (Std_ReturnType GoHaltResult)
{
  ECUM_UNUSED(GoHaltResult);
}

/*******************************************************************************
** Function Name        : EcuM_RequestSleep                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Sleep using Release    **
**                        Run API                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_trEcuMConfigPtr       **
**                                                                            **
**                        Function(s) invoked    : EcuM_SelectShutdownTarget  **
**                        BswM_RequestMode, EcuM_ReleaseRUN,                  **
**                        DataLog_SetSleepConditionLog()                      **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_RequestSleep(EcuM_UserType user)
{
  Std_ReturnType stdRetVal;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Medium] "Pointer is initialized in EcuM_Init" */
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_SLEEP,
    EcuM_ptrEcuMConfigPtr->EcuMDefaultSleepMode);
  /* polyspace-end MISRA2012:D4.14 */

  #if (SWP_USE_DATALOG == STD_ON)
  DataLog_SetSleepConditionLog();
  #endif
  stdRetVal = EcuM_ReleaseRUN(user);

  if(E_OK == stdRetVal)
  {
    /* Update shutdown or sleep request state */
    if(ECUM_REQUEST_SLEEP != EcuM_ShutdownOrSleepRequested)
    {
      SchM_Enter_EcuM_STATE_PROTECTION();
      EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_SLEEP;
      SchM_Exit_EcuM_STATE_PROTECTION();
    }
  }
  return stdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_RequestReset                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Reset using Release    **
**                        Run API                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    : EcuM_SelectShutdownTarget  **
**                                                 EcuM_ReleaseRUN            **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_RequestReset
  (EcuM_UserType user)
{
  Std_ReturnType stdRetVal;
  /* invoke callout select shutdown target */
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET, ECUM_RESET_MCU);

  /* invoke EcuM release mode Run */
  stdRetVal = EcuM_ReleaseRUN(user);

  if(E_OK == stdRetVal)
  {
    /* Update shutdown or sleep request state */
    if(ECUM_REQUEST_RESET != EcuM_ShutdownOrSleepRequested)
    {
      SchM_Enter_EcuM_STATE_PROTECTION();
      EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_RESET;
      SchM_Exit_EcuM_STATE_PROTECTION();
    }
  }

  return stdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_RequestOff                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Off using Release Run  **
**                        API                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    : EcuM_SelectShutdownTarget  **
**                        BswM_RequestMode, EcuM_ReleaseRUN                   **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_RequestOff
  (EcuM_UserType user)
{
  Std_ReturnType stdRetVal;
  /* select shutdown target OFF */
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_OFF, ECUM_ZERO);

  /* Indicate EcuM release mode RUN */
  stdRetVal = EcuM_ReleaseRUN(user);

  if(E_OK == stdRetVal)
  {
    /* Update shutdown or sleep request state */
    if(ECUM_REQUEST_OFF != EcuM_ShutdownOrSleepRequested)
    {
      SchM_Enter_EcuM_STATE_PROTECTION();
      EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_OFF;
      SchM_Exit_EcuM_STATE_PROTECTION();
    }
  }

  return stdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_StartCheckWakeup                               **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This API is called by the ECU Firmware to start the **
**                        CheckWakeupTimer for the corresponding WakeupSource.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartCheckWakeup
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_EndCheckWakeup                                 **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This API is called by any SW Module whose wakeup    **
**                        source is checked asynchronously and the Check of   **
**                        the Wakeup returns a negative Result.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: "SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CALLOUT_CODE) EcuM_EndCheckWakeup
           (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_Gen_AL_DriverInitCoreWise_PostOs               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup postOs activities**
**                        in case of multi-core support                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : CoreIdType CoreId                                   **
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
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverIniCoreWise_PreOs()               **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitCoreWise_PreOs(CoreIdType CoreId)
{
  #if (ECUM_DRIVER_INIT_CORE_WISE_PRE_OS == STD_ON)
  EcuM_Gen_AL_DriverInitCoreWise_PreOs(CoreId);
  #else
  ECUM_UNUSED(CoreId);
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_DriverIniCoreWise_PostOs                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup postOs activities**
**                        in case of multi-core support                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : CoreIdType CoreId                                   **
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
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverInitCoreWise_PostOs()             **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitCoreWise_PostOs(CoreIdType CoreId)
{
  #if (ECUM_DRIVER_INIT_CORE_WISE_POST_OS == STD_ON)
  EcuM_Gen_AL_DriverInitCoreWise_PostOs(CoreId);
  #else
  ECUM_UNUSED(CoreId);
  #endif
}

/*******************************************************************************
** Function Name        : Init_McuSetMode                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : User callout function                               **
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
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.4 MISRA-C3:8.5 [Not a defect:Low] "Scope to be implemented by user" */
FUNC(void, ECUM_CODE) Init_McuSetMode(void)
{
  Mcu_SetMode(McuModeSettingConf_RUN);
}
/* polyspace-end MISRA-C3:8.4 MISRA-C3:8.5 [Not a defect:Low] "Scope to be implemented by user" */

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:D4.4 [Justified:Low] Justify with annotations */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
