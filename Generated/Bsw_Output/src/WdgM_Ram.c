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
**  SRC-MODULE: WdgM_Ram.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Watchdog Manager RAM variable definitions                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 0.0.1     16-Sep-2019   ThanhNT      Initial version                       **
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.4     24-Oct-2019   ThanhNT      Update coding convention              **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.6     12-Nov-2019   ThanhNT      Add Deactivated state checking in APIs**
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     11-Mar-2020   TienVD       Update traceability                   **
** 0.0.9     12-Sep-2020   LanBT        To remove WdgM_PtrConfig global       **
**                                      variable and use locally only (#15485)**
** 0.0.10    21-Sep-2020   ThanhNH5     Fixed memory sections issue(#15934)   **
** 0.0.11    05-Oct-2020   ThanhNH5     Merge variables in single and         **
**                                      multi core (#15485)                   **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Global variable used within WdgM module" */

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
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_Ram.h"         /* WdgM Ram variables header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
/* @Trace: SRS_WdgM_CUS_00014 */
#define WDGM_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the overall supervision status */
VAR(WdgM_GlobalStatusType, WDGM_VAR_POWER_ON_INIT)
  WdgM_PlatformGlobalSupervisionStatus = 
  (WdgM_GlobalStatusType)WDGM_GLOBAL_STATUS_DEACTIVATED;
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define WDGM_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the inverse overall supervision status */
VAR(WdgM_GlobalStatusType, WDGM_VAR_POWER_ON_INIT)
  WdgM_InvPlatformGlobalSupervisionStatus = 
  (WdgM_GlobalStatusType)(WDGM_INV_GLOBAL_STATUS_DEACTIVATED_DEFAULT);
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_WdgM_CUS_00008 */
#define WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"
/* Global variable to store first expired SE id status of WdgM */
VAR(boolean, WDGM_VAR_NOINIT) WdgM_FirstExpSEIDStatus;
#define WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"

/* @Trace: SRS_WdgM_CUS_00008 */
#define WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the SEID of first expired SE */
VAR(WdgM_SupervisedEntityIdType, WDGM_VAR_NOINIT) WdgM_FirstExpiredSEID;
#define WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_WdgM_CUS_00008 */
#define WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the inverse SEID value of first expired SE */
VAR(WdgM_SupervisedEntityIdType, WDGM_VAR_NOINIT) WdgM_InvFirstExpiredSEID;
#define WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 SRS_ModeMgm_09110 SRS_BSW_00323 */
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
VAR(WdgM_ModeType, WDGM_VAR_POWER_ON_INIT) WdgM_CurrentMode_0;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"


#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"
VAR(uint8, WDGM_VAR_POWER_ON_INIT) WdgM_SEStatus_300;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"

/* @Trace: SRS_ModeMgm_09112 */
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the overall supervision status */
VAR(WdgM_GlobalStatusType, WDGM_VAR_POWER_ON_INIT)
  WdgM_GlobalSupStatus_0 = 
  (WdgM_GlobalStatusType)WDGM_GLOBAL_STATUS_DEACTIVATED;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the overall supervision status */
VAR(WdgM_GlobalStatusType, WDGM_VAR_POWER_ON_INIT)
  WdgM_InvGlobalSupStatus_0 = 
  (WdgM_GlobalStatusType)(WDGM_INV_GLOBAL_STATUS_DEACTIVATED_DEFAULT);
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: WdgM_SRS_ECUC_00329 */
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the amount of expired supervision cycles for how
  long the blocking of watchdog triggering shall be postponed in a given mode */
VAR(WdgM_ExpSupCycleTolType, WDGM_VAR_POWER_ON_INIT)
  WdgM_ExpSupCycleCounter_0;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_ModeMgm_09112 */

/* Global variable to store the WdgM_MainFunction call count */
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"
VAR(uint32, WDGM_VAR_POWER_ON_INIT) WdgM_FreeRunningCounter_0;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

/* @Trace: WdgM_SRS_ECUC_00327 */
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
VAR(WdgM_FailureTolType, WDGM_VAR_POWER_ON_INIT)
               WdgM_FailedRefCycleCounter_300;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"


#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"
VAR(boolean, WDGM_VAR_POWER_ON_INIT) WdgM_AlreadyUpdated_300;
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"

/* @Trace: SRS_ModeMgm_09112 SRS_ModeMgm_09160 SRS_ModeMgm_09221 SRS_ModeMgm_09143 */
/* Global variable to store Alive Indication status */
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
VAR(WdgM_ExAliveIndicationsCountType, WDGM_VAR_POWER_ON_INIT)
 WdgM_AliveIndStatus_0[WDGM_MAX_ALIVESUPERVISIONS];
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"



/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end VARIABLE:ALL */
/* polyspace-end MISRA-C3:20.1 */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
