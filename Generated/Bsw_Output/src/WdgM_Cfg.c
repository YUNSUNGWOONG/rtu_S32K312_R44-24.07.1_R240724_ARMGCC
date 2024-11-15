/* polyspace +1 MISRA2012:1.1 [Not a Defect:Low] "Macro definitions are needed for performance and file size" */
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
**  FILE-NAME: WdgM_Cfg.c                                                     **
**                                                                            **
**  MODULE-NAME: AUTOSAR Watchdog Manager Module                              **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Tool Version: 1.3.3.0                                                     **
**  Framework Version: 1.1.5                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            */

/*******************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_Os.arxml              
*                  Configuration\Ecu\Ecud_Rte.arxml             
*                  Configuration\Ecu\Ecud_WdgIf.arxml           
*                  Configuration\Ecu\Ecud_WdgM.arxml            
*                  Configuration\Ecu\Mcal\Ecud_Mcu.arxml        
*                  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml  
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml
*                  Static_Code\Modules\WdgIf_R44\generator\WdgIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\WdgM_R44\generator\WdgM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Global variable used within WdgM module" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM.h"
#include "Rte_WdgM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Internal variables                                    **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00345 SRS_WdgM_CUS_00011 SRS_WdgM_CUS_00014*/


#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
/* Array of check points of SE 300 */
static CONST(WdgM_CheckpointGraphType, WDGM_CONST) WdgM_SE300Checkpoints[WDGM_SE300CHECKPOINTS_TOTAL_COUNT]=
{
  {
    /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
    WDGM_CP_BI
  },
  {
    /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
    WDGM_CP_INITIAL
  },
  {
    /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
    WDGM_CP_FINAL
  }
};
/* Array of check points of SE 400 */
static CONST(WdgM_CheckpointGraphType, WDGM_CONST) WdgM_SE400Checkpoints[WDGM_SE400CHECKPOINTS_TOTAL_COUNT]=
{
  {
    /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
    WDGM_CP_BI
  },
  {
    /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
    WDGM_CP_INITIAL
  },
  {
    /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
    WDGM_CP_FINAL
  }
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* Alive supervision configuration of Mode */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
static CONST(WdgM_AliveSupervisionType, WDGM_CONST) WdgM_Mode0AliveSupervision[WDGM_MODE0ALIVESUPERVISION_TOTAL_COUNT] = 
{
  /* Alive supervision 0 */
  {
    /* Supervised entity to be supervised */
    300,
    /* Index to the SE array WdgM_SupervisedEntity */
    0,
    /* Checkpoint to be supervised */
    0,
    /* Expected alive indications of the Checkpoint */
    1,
    /* Reference supervision cycles to perform the checkup with counted alive indications */
    800,
    /* Allowed additional to the expected alive indications */
    0,
    /* Allowed missing expected alive indications */
    0
  }
};
static CONST(WdgM_AliveSupervisionType, WDGM_CONST) WdgM_Mode1AliveSupervision[WDGM_MODE1ALIVESUPERVISION_TOTAL_COUNT] = 
{
  /* Alive supervision 0 */
  {
    /* Supervised entity to be supervised */
    300,
    /* Index to the SE array WdgM_SupervisedEntity */
    0,
    /* Checkpoint to be supervised */
    0,
    /* Expected alive indications of the Checkpoint */
    10,
    /* Reference supervision cycles to perform the checkup with counted alive indications */
    10,
    /* Allowed additional to the expected alive indications */
    1,
    /* Allowed missing expected alive indications */
    1
  }
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* Mode trigger configuration */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
static CONST(WdgM_TriggerType, WDGM_CONST) 
    WdgM_Mode0Trigger[WDGM_MODE0TRIGGER_TOTAL_COUNT] =
{
/* Trigger 0 - 0 */
  {
    /* WdgIf mode for the corresponding WdgM mode */
    WDGIF_SLOW_MODE,
    /* Wdg Trigger Timeout */
    500,
    /* WdgIf Device Id */
    0
  },
/* Trigger 0 - 1 */
  {
    /* WdgIf mode for the corresponding WdgM mode */
    WDGIF_SLOW_MODE,
    /* Wdg Trigger Timeout */
    500,
    /* WdgIf Device Id */
    1
  }
};
static CONST(WdgM_TriggerType, WDGM_CONST) 
    WdgM_Mode1Trigger[WDGM_MODE1TRIGGER_TOTAL_COUNT] =
{
/* Trigger 1 - 0 */
  {
    /* WdgIf mode for the corresponding WdgM mode */
    WDGIF_FAST_MODE,
    /* Wdg Trigger Timeout */
    200,
    /* WdgIf Device Id */
    0
  },
/* Trigger 1 - 1 */
  {
    /* WdgIf mode for the corresponding WdgM mode */
    WDGIF_FAST_MODE,
    /* Wdg Trigger Timeout */
    200,
    /* WdgIf Device Id */
    1
  }
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* Configuration of the Supervised Entities */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
CONST(WdgM_SupervisedEntityType, WDGM_CONST)
  WdgM_SupervisedEntity[WDGM_TOTAL_SES] =
{
  /* Supervised entity 0 - 300 */
  {
    /* Pointer to corresponding WdgM_SE300Checkpoints */
    WdgM_SE300Checkpoints,
    /* Pointer to Rte function pointer switch */
    Rte_Switch_mode_SE_Init_currentMode,
    /* Total configured check points for a supervised entity */
    3,
    /* Supervised Entity Id */
    300,
    /* OS Application ID */
    0xFF,
    /* OS Application Trusted type */
    WDGM_OS_APPLICATION_TRUSTED,
    
    /* Supervision algorithms applicable for SE */
        0x01
  },
  /* Supervised entity 1 - 400 */
  {
    /* Pointer to corresponding WdgM_SE400Checkpoints */
    WdgM_SE400Checkpoints,
    /* Pointer to Rte function pointer switch */
      NULL_PTR,
    /* Total configured check points for a supervised entity */
    3,
    /* Supervised Entity Id */
    400,
    /* OS Application ID */
    0xFF,
    /* OS Application Trusted type */
    WDGM_OS_APPLICATION_TRUSTED,
    
    /* Supervision algorithms applicable for SE */
        0x00
  }
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"


/* List of activated SEs of Modes */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
static CONST(WdgM_ActiveSEType, WDGM_CONST) 
    WdgM_Mode0ActiveSE[WDGM_MODE0ACTIVESE_TOTAL_COUNT] =
{
/* Active SE 0 - 0 */
  {
    /* Supervised entity to be supervised */
    300,
    /* Index to the SE array WdgM_SupervisedEntity */
    0,
    /* Failed Alive supervision tolerance */
    0
  }
};
static CONST(WdgM_ActiveSEType, WDGM_CONST) 
    WdgM_Mode1ActiveSE[WDGM_MODE1ACTIVESE_TOTAL_COUNT] =
{
/* Active SE 1 - 0 */
  {
    /* Supervised entity to be supervised */
    300,
    /* Index to the SE array WdgM_SupervisedEntity */
    0,
    /* Failed Alive supervision tolerance */
    1
  }
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* Modes configuration */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h" 
static CONST(WdgM_ModePropertyType, WDGM_CONST) WdgM_Modes[WDGM_TOTAL_MODES] = 
{
/* Mode 0 */
  {
    /* Pointer to corresponding WdgM_Mode0AliveSupervisions[] */
    WdgM_Mode0AliveSupervision,
    /* Pointer to corresponding  WdgM_Mode0ActiveSE */
    WdgM_Mode0ActiveSE,
    /* Pointer to corresponding  WdgM_Mode0Triggers */
    WdgM_Mode0Trigger,
    /* Duration in which the blocking of watchdog triggering shall be postponed */
    0,
    /* MainFunction period */
    0,
    /* Total Configured Alive Supervisions */
    1,
    /* Total number of active SE's in the current mode */
    1,
    /* Total Configured Triggers */
    2
  },
/* Mode 1 */
  {
    /* Pointer to corresponding WdgM_Mode1AliveSupervisions[] */
    WdgM_Mode1AliveSupervision,
    /* Pointer to corresponding  WdgM_Mode1ActiveSE */
    WdgM_Mode1ActiveSE,
    /* Pointer to corresponding  WdgM_Mode1Triggers */
    WdgM_Mode1Trigger,
    /* Duration in which the blocking of watchdog triggering shall be postponed */
    2,
    /* MainFunction period */
    0,
    /* Total Configured Alive Supervisions */
    1,
    /* Total number of active SE's in the current mode */
    1,
    /* Total Configured Triggers */
    2
  }
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* Configuration Sets */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
static CONST(WdgM_ConfigType, WDGM_CONST) WdgM_Config_0=
{
  /* WdgMDemEventParameterRefs*/
  {
    TRUE,
    DemConf_DemEventParameter_WDGM_E_SET_MODE,
    TRUE,
    DemConf_DemEventParameter_WDGM_E_MONITORING
  },
  /* Initial mode of this variant */
  0,
  /* Total mode configured in this variant */
  WDGM_TOTAL_MODES,
  /* Pointer to configured mode */
  WdgM_Modes,
  /* Maximum alive supervision reference cycle */
  800
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* The module configuration set */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
CONSTP2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_CONST) WdgM_Config[WDGM_TOTAL_CORES] =
{
  &WdgM_Config_0
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16
#include "MemMap.h"
/* Timeout value for WdgM_DeInit process */
CONST(uint16, WDGM_CONST) WdgM_DeInitTimeout[WDGM_TOTAL_CORES] =
{
  WDGM_DEINIT_TIMEOUT
};
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16
#include "MemMap.h"

#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
/* WDGM_TOTAL_SES */
CONST(WdgM_SupervisedEntityIndexType, WDGM_CONST) WdgM_TotalSEs = WDGM_TOTAL_SES;
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */
/* polyspace-end VARIABLE:ALL */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
