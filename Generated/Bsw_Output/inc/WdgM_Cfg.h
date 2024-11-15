
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
**  FILE-NAME: WdgM.cfg                                                       **
**                                                                            **
**  MODULE-NAME: AUTOSAR Watchdog Manager Module                              **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Tool Version: 1.3.3.0                                                     **
**  Framework Version: 1.1.5                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
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

#ifndef WDGM_CFG_H
#define WDGM_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#define RTE_ALLOW_CROSS_HEADER_INCLUSION
#include "Rte_WdgM.h"



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define WDGM_AR_RELEASE_MAJOR_VERSION                      (4)
#define WDGM_AR_RELEASE_MINOR_VERSION                      (4)
#define WDGM_AR_RELEASE_REVISION_VERSION                   (0)
#define WDGM_SW_MAJOR_VERSION                              (1)
#define WDGM_SW_MINOR_VERSION                              (0)
#define WDGM_SW_PATCH_VERSION                              (0)
#define WDGM_VENDOR_ID                                     ((uint16)76)
#define WDGM_MODULE_ID                                     ((uint16)13)

/*******************************************************************************
**                      Data Types                                            **
*******************************************************************************/
/* Type definition for Checkpoint mapping array index type */
typedef     uint8     WdgM_CpMapArrayIndexType;

 /* Type definition for Supervised Entity mapping array index type */
typedef     uint8     WdgM_SupervisedEntityIndexType;

/*Type based on maximum number of WdgMInternalTransition configured */
typedef     uint8     WdgM_IntLogicSupStatArrIndexType;


/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/

/* Development error detection Enable or Disable */
#define WDGM_DEV_ERROR_DETECT                         (STD_ON)

/* Enable or Disable Alive supervision */
#define WDGM_ENABLE_ALIVE_SUPERVISION                 (STD_ON)

/* Enable or Disable Deadline supervision */
#define WDGM_ENABLE_DEADLINE_SUPERVISION              (STD_OFF)

/* Enable or Disable Internal Transition */
#define WDGM_ENABLE_INTERNAL_TRANSITION               (STD_OFF)

/* Enable or Disable External Transition */
#define WDGM_ENABLE_EXTERNAL_TRANSITION               (STD_OFF)

 /* Enable or Disable Logical supervision */
#define WDGM_ENABLE_LOGICAL_SUPERVISION               (STD_OFF) 

/* Enable or Disable DemEventParameter */
#define WDGM_DEM_ERROR_REPORT                         (STD_ON)

/* Enable or Disable Dem notification */
#define WDGM_DEM_STOPPED_SUPERVISION_REPORT           (STD_ON)

/* Immediate reset feature Enable or Disable */
#define WDGM_IMMEDIATE_RESET                          (STD_ON)

/* Enable or Disable selection of the OffMode */
#define WDGM_OFF_MODE_ENABLED                         (STD_ON)

/* Enable or Disable OS application */
#define WDGM_ENABLE_OS_APPLICATION                    (STD_ON)

/* Enable or Disable Trigger */
#define WDGM_ENABLE_TRIGGER                           (STD_ON)

/* Enable or Disable WdgM_GetVersionInfo API */
#define WDGM_VERSION_INFO_API                         (STD_ON)

/* Enable or Disable Pre-Compile configuration */
#define WDGM_PRECOMPILE_ENABLED                       (STD_ON)

/* Total number of core configured */
#define WDGM_TOTAL_CORES                          		(1)

/* The master core ID */
#define WDGM_MASTER_CORE_ID	                          0x00U

/* Total Number of Modes */
#define WDGM_TOTAL_MODES                          ((WdgM_ModeType)2)


/* Total Number of Supervised Entities */
#define WDGM_TOTAL_SES                                ((WdgM_SupervisedEntityIndexType)2)

/* Maximum number of Alive Supervisions configured */
#define WDGM_MAX_ALIVESUPERVISIONS                    ((uint16)1)

/* Timeout value for WdgM_DeInit process */
#define WDGM_DEINIT_TIMEOUT                    ((uint16)4000)

/* Total Number of Watchdog instances */
#define WDGM_TOTAL_WATCHDOG_INSTANCES                 ((uint8)2)




/*******************************************************************************
**                      Computed Macros                                       **
*******************************************************************************/

/* Number of Alive supervision */
#define WDGM_MODE0ALIVESUPERVISION_TOTAL_COUNT   ((uint16)1) 
/* Number of Alive supervision */
#define WDGM_MODE1ALIVESUPERVISION_TOTAL_COUNT   ((uint16)1) 



#define WDGM_MODE0ACTIVESE_TOTAL_COUNT   ((uint16)1)
#define WDGM_MODE1ACTIVESE_TOTAL_COUNT   ((uint16)1)

/* Number of trigger */
#define WDGM_MODE0TRIGGER_TOTAL_COUNT   ((uint8)2)
/* Number of trigger */
#define WDGM_MODE1TRIGGER_TOTAL_COUNT   ((uint8)2)

/* Number of check point of SE 300 */
#define WDGM_SE300CHECKPOINTS_TOTAL_COUNT  ((uint32)3)
/* Number of check point of SE 400 */
#define WDGM_SE400CHECKPOINTS_TOTAL_COUNT  ((uint32)3)


/*******************************************************************************
**                      Configuration Set Handles                             **
*******************************************************************************/

#define WdgMConf_WdgMMode_WdgMMode0 ((WdgM_ModeType)0)
#define WdgMConf_WdgMMode_WdgMMode1 ((WdgM_ModeType)1)

#define WdgMConf_WdgMSupervisedEntity_SE_Init ((WdgM_SupervisedEntityIdType)300)
#define WdgMConf_WdgMSupervisedEntity_SE_WdgMTest ((WdgM_SupervisedEntityIdType)400)

#define WdgMConf_WdgMWatchdog_WdgMWatchdog_Int (Watchdog_Int)
#define WdgMConf_WdgMWatchdog_WdgMWatchdog_Ext (Watchdog_Ext)

#define WdgMConf_WdgMCheckpoint_SE_Init_CP_Init_AS0 ((WdgM_CheckpointIdType)0)
#define WdgMConf_WdgMCheckpoint_SE_Init_CP_Init_ILS_0 ((WdgM_CheckpointIdType)1)
#define WdgMConf_WdgMCheckpoint_SE_Init_CP_Init_ILS_1 ((WdgM_CheckpointIdType)2)
#define WdgMConf_WdgMCheckpoint_SE_WdgMTest_CP_WdgMTest_AS0 ((WdgM_CheckpointIdType)0)
#define WdgMConf_WdgMCheckpoint_SE_WdgMTest_CP_WdgMTest_ILS_0 ((WdgM_CheckpointIdType)1)
#define WdgMConf_WdgMCheckpoint_SE_WdgMTest_CP_WdgMTest_ILS_1 ((WdgM_CheckpointIdType)2)


#endif /* WDGM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

