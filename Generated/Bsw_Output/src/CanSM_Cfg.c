/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
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
**  SRC-MODULE: CanSM_Cfg.c                                                   **
**                                                                            **                                        
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : This file contain function body for generic public API's.     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
**                                                                            **
********************************************************************************
********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version: 1.1.5                                                  **
**  Module version:    1.0.9.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_Com.arxml             
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml 
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanSM_InternalTypes.h"
#include "CanSM.h"


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR SPECIFICATION VERSION INFORMATION */
#define    CANSM_CFG_C_AR_RELEASE_MAJOR_VERSION          0x04u
#define    CANSM_CFG_C_AR_RELEASE_MINOR_VERSION          0x04u
#define    CANSM_CFG_C_AR_RELEASE_REVISION_VERSION       0x00u
#define    CANSM_CFG_C_SW_MAJOR_VERSION                  0x01u
#define    CANSM_CFG_C_SW_MINOR_VERSION                  0x00u
#define    CANSM_CFG_C_SW_PATCH_VERSION                  0x09u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (CANSM_INTERNALTYPES_AR_RELEASE_MAJOR_VERSION != \
  CANSM_CFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "CanSM_Cfg.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_INTERNALTYPES_AR_RELEASE_MINOR_VERSION != \
  CANSM_CFG_C_AR_RELEASE_MINOR_VERSION)
  #error "CanSM_Cfg.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_INTERNALTYPES_AR_RELEASE_REVISION_VERSION != \
  CANSM_CFG_C_AR_RELEASE_REVISION_VERSION)
  #error "CanSM_Cfg.c : Mismatch in Specification Revision Version"
#endif

#if (CANSM_INTERNALTYPES_SW_MAJOR_VERSION != CANSM_CFG_C_SW_MAJOR_VERSION)
  #error "CanSM_Cfg.c : Mismatch in Software Major Version"
#endif

#if (CANSM_INTERNALTYPES_SW_MINOR_VERSION != CANSM_CFG_C_SW_MINOR_VERSION)
  #error "CanSM_Cfg.c : Mismatch in Software Minor Version"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
CONST(CanSM_ConfigType, CANSM_CONST) CanSM_Config[CANSM_NUMBER_OF_CONFIGURATION] =
{
  /* Config 0 - CanSMConfiguration */
  {
    /* ucModeReqRptMax */
    0x03,
    
    /* ddModeReqRptTime */
    0x0003,
    
    /* Pointer to First network*/
    &CanSM_StaticNetwork[0]
    
  }
  
};
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"


#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
CONST(uint8, CANSM_CONST) CanSM_InternalController[CANSM_LAST_CTRL_HANDLE + 1] =
{
  /* InternalController 0 - CanSMManagerNetwork_FD_CAN1_CanSMController_ECU1_FD_CAN1 */
  0x00
  
};
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"


#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
CONST(uint8, CANSM_CONST) CanSM_InternalNetwork[CANSM_LAST_NW_HANDLE + 1] =
{
  /* InternalNetwork 0_CanSMConfiguration_ComM_Handle_Id_'0' */
  0
  
};
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"


#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
CONST(uint8, CANSM_CONST) CanSM_StaticController[CANSM_NUMBER_OF_STATIC_CTRL] =
{
  /* Controller 0 - CanSMConfiguration_CanSMManagerNetwork_FD_CAN1_CanSMController_ECU1_FD_CAN1 */
  0x00
  
};
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"


#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
CONST(CanSM_StaticNetworkType, CANSM_CONST) CanSM_StaticNetwork[CANSM_NUMBER_OF_STATIC_NWS] =
{
  /* Network 0 - CanSMConfiguration_CanSMManagerNetwork_FD_CAN1 */
  {
    /* ucCanSmNetworkHandle */
    0x00,
    
    /* pnSupported */
    CANSM_FALSE,
    
    /* DemStatusFlag */
    CANSM_TRUE,
    
    /* ucCanSmTranceiverId */
    0x00,
    
    /* ucNumberOfController */
    0x01,
    
    /* ucControllerIndex */
    0x00,
    
    /* ddBorCounterL1ToL2 */
    0x03,
    
    /* ddCanSMBorTimeL1 */
    0x0060,
    
    /* ddCanSMBorTimeL1 */
    0x0060,
    
    /* ddBorTimeTxEnsured */
    0x0002,
    
    /* BusOffEventId */
    0x2D,
    
    /* TimeOutEventId */
    0x5F
    
  }
  
};
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"


#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
CONST(uint8, CANSM_CONST) CanSM_StaticTrvToNw[CANSM_LAST_TRCV_HANDLE + 1] =
{
  /* TransceiverToNetwork 0 - CanSMConfiguration-_Trcv_Id-'0' */
  0
  
};
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"






/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

