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
**  SRC-MODULE: WdgM.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Header file to publish Watchdog Manager function prototypes   **
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
** 0.0.2     23-Sep-2019   ThanhNT      Added function prototypes             **
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.4     24-Oct-2019   ThanhNT      Update coding convention              **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     11-Mar-2020   TienVD       Update traceability                   **
** 0.0.16    26-Mar-2020   ThanhNT      Fix misra defect                      **
** 0.0.17    10-Aug-2020   LanBT        Fix misra defect (refs #15163)        **
** 0.0.30    16-Oct-2020   ThanhNT      Update MemMap ASIL_D (#16306)         **
** 1.0.2     22-Mar-2021   HiepVT1      Deleted #include "WdgM_Workthrough.h" **
**                                      (#18339)                              **
** 1.2.0     01-Dec-2021   HiepVT1      Include WdgM_Partitions.h             **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */

#ifndef WDGM_H
#define WDGM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_IntTypes.h"            /* WdgM Types Header file */
#include "Std_Types.h"                /* Standars types Header file */


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00310 SRS_BSW_00358 SRS_ModeMgm_09107 SRS_BSW_00336 SRS_ModeMgm_09110 SRS_ModeMgm_09232 SRS_WdgM_CUS_00008 SRS_BSW_00373 */
/* Service Id of WdgM_Init */
#define WDGM_INIT_SID                             0x00U
/* Service Id of WdgM_DeInit */
#define WDGM_DEINIT_SID                           0x01U
/* Service Id of WdgM_GetVersionInfo */
#define WDGM_GETVERSIONINFO_SID                   0x02U
/* Service Id of WdgM_SetMode */
#define WDGM_SETMODE_SID                          0x03U
/* Service Id of WdgM_GetMode */
#define WDGM_GETMODE_SID                          0x0bU
/* Service Id of WdgM_CheckpointReached */
#define WDGM_CHECKPOINTREACHED_SID                0x0eU
/* Service Id of WdgM_GetAliveSupevisionStatus */
#define WDGM_GETLOCALSTATUS_SID                   0x0cU
/* Service Id of WdgM_GetGlobalStatus */
#define WDGM_GETGLOBALSTATUS_SID                  0x0dU
/* Service Id of WdgM_GetGlobalStatus */
#define WDGM_PERFORMRESET_SID                     0x0fU
/* Service Id of WdgM_GetFirstExpiredSEID */
#define WDGM_GETFIRSTEXPIRED_SEID_SID             0x10U
/* Service Id of WdgM_Mainfunction */
#define WDGM_MAINFUNCTION_SID                     0x08U

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00310 SRS_BSW_00358 SRS_ModeMgm_09107 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_Init(
  P2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) ConfigPtr
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 SRS_BSW_00336 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_DeInit(void);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 */
#if(WDGM_VERSION_INFO_API == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, WDGM_APPL_DATA) VersionInfo
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/* @Trace: SRS_BSW_00310 SRS_ModeMgm_09110 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_SetMode(
  VAR(WdgM_ModeType, AUTOMATIC) Mode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetMode(
  P2VAR(WdgM_ModeType, WDGM_DATA, WDGM_APPL_DATA) Mode
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_CheckpointReached(
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SEID, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) CheckpointID
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetLocalStatus(
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SEID,
  P2VAR(WdgM_LocalStatusType, WDGM_DATA, WDGM_APPL_DATA) Status
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetGlobalStatus(
  P2VAR(WdgM_GlobalStatusType, WDGM_DATA, WDGM_APPL_DATA) Status
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 SRS_ModeMgm_09232 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformReset(void);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_WdgM_CUS_00008 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetFirstExpiredSEID(
  P2VAR(WdgM_SupervisedEntityIdType, WDGM_DATA, WDGM_APPL_DATA) SEID
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* WDGM_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
