/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted with **
**  Hyundai Autoever, and any other use is prohibited.                        **
**  If you use it for other  purposes or change the source code, you may take **
**  legal responsibility.                                                     **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: WdgIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDGIF                                 **
**                                                                            **
**  PURPOSE   : AutoEver Custom Watchdog Interface API Header of Functionality**
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 0.0.1     23-Sep-2019 <Tungdt39>         R44-Redmine <#1440>               **
** 0.0.2     11-Mar-2020 <Tungdt39>         R44-Redmine <#11479>              **
** 1.3.1.0   10-Aug-2022 <TriBD>            CP44-323                          **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef WDGIF_H
#define WDGIF_H
/* @Trace: SRS_BSW_00304 SRS_MemHwAb_14024*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgIf_Types.h"
#include "Std_Types.h"
#include "WdgIf_Cfg.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Define SINGLE Device                                  **
*******************************************************************************/
#define  WDGIF_SINGLE_DEVICE                                      0x01U
#if (WDGIF_NUMBER_OF_DEVICES == WDGIF_SINGLE_DEVICE)
/*******************************************************************************
**                      Define var unused                                     **
*******************************************************************************/

/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "macro is used for improving performance" */
#define WDGIF_UNUSED(x)                                         (void)(x)
#endif /* end of #if (WDGIF_NUMBER_OF_DEVICES == WDGIF_SINGLE_DEVICE) */

#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define WDGIF_INSTANCE_ID                                      ((uint8) 0x00U)
/*******************************************************************************

**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00327*/
#if (WDGIF_NUMBER_OF_DEVICES > WDGIF_SINGLE_DEVICE)
#define WDGIF_E_PARAM_DEVICE                                  ((uint8) 0x01U)
#endif /* end of #if (WDGIF_NUMBER_OF_DEVICES > WDGIF_SINGLE_DEVICE) */

#define WDGIF_E_INV_POINTER                                   ((uint8) 0x02U)

/*******************************************************************************
**                        API service ids                                     **
*******************************************************************************/
#if (WDGIF_NUMBER_OF_DEVICES > WDGIF_SINGLE_DEVICE)
#define WDGIF_SETMODE_SID                                      ((uint8) 0x01U)
#define WDGIF_SETTRIGGERCONDITION_SID                          ((uint8) 0x02U)
#endif /* end of #if (WDGIF_NUMBER_OF_DEVICES > WDGIF_SINGLE_DEVICE) */

#define WDGIF_GETVERSIONINFO_SID                               ((uint8) 0x03U)

#endif /* end of #if (WDGIF_DEV_ERROR_DETECT == STD_ON) */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "This macro is necessary for Memory mapping" */
/* polyspace-begin MISRA-C3:20.1 [Not a Defect:Low] "See SWS_MemMap_00003 of AUTOSAR" */
#define WDGIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetMode \
    (VAR(uint8, WDGIF_VAR) DeviceIndex, VAR(WdgIf_ModeType, WDGIF_VAR) WdgMode);

#define WDGIF_STOP_SEC_CODE
#include "MemMap.h"

#define WDGIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGIF_CODE) WdgIf_SetTriggerCondition \
       (VAR(uint8, WDGIF_VAR) DeviceIndex, VAR(uint16, WDGIF_VAR) Pra_Timeout);

#define WDGIF_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == WDGIF_VERSION_INFO_API)
#define WDGIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGIF_CODE) WdgIf_GetVersionInfo \
       (P2VAR(Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA)VersionInfoPtr);
#define WDGIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* end of #if (STD_ON == WDGIF_VERSION_INFO_API) */

/* polyspace-end MISRA-C3:2.5 */
/* polyspace-end MISRA-C3:20.1 */
#endif /* End of WDGIF_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

