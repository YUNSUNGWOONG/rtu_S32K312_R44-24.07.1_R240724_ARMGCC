/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: FiM.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
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
** 0.0.3    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

#ifndef FIM_H
#define FIM_H

/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "FiM_Types.h"     /* FiM Types Definition Header File */
#include "Dem_Types.h"     /* Dem Types Definition Header File */
#include "FiM_Cfg.h"       /* FiM Cfg Definition Header File */
#include "FiM_Config.h"
#include "FiM_PCTypes.h"
#include "FiM_Version.h"
#include "Dem.h"
#include "Rte_Dem_Type.h"
/* @Trace: FiM_SUD_MACRO_005*/
/* @Trace: FiM_SUD_MACRO_002*/
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Service ID for FiM_Init */
/* @Trace: FiM_SUD_MACRO_003*/
#define FIM_INIT_SID                               0x00U
/* Service ID for FiM_GetFunctionPermission */
#define FIM_GETFUNCTIONPERMISSION_SID              0x01U
/* Service ID for FiM_SetFunctionAvailable */
#define FIM_SETFUNCTIONAVAILABLE_SID               0x07U
/* Service ID for FiM_DemTriggerOnMonitorStatus */
#define FIM_DEMTRIGGERONMONITORSTATUS_SID          0x02U
/* Service ID for FiM_DemTriggerOnComponentStatus */
#define FIM_DEMTRIGGERONCOMPONENTSTATUS_SID        0x06U
/* Service ID for FiM_DemInit */
#define FIM_DEMINIT_SID                            0x03U
/* Service ID for FiM_GetVersionInfo */
#define FIM_GETVERSIONINFO_SID                     0x04U
/* Service ID for FiM_MainFunction */
#define FIM_MAINFUNCTION_SID                       0x05U
/* FIM instance ID */
#define FIM_INSTANCE_ID                            0x00U

/* Standard Development error codes */
/* @Trace: FiM_SUD_MACRO_006*/
#define FIM_E_UNINIT                               0x01U
#define FIM_E_FID_OUT_OF_RANGE                     0x02U
#define FIM_E_EVENTID_OUT_OF_RANGE                 0x03U
#define FIM_E_PARAM_POINTER                        0x04U
#define FIM_E_INIT_FAILED                          0x05U




/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
/* Extern for FiM_Init */
extern FUNC(void,FIM_CODE) FiM_Init(
  P2CONST(FiM_ConfigType,AUTOMATIC,FIM_APPL_CONST)FiMConfigPtr);

#ifndef RTE_FIM_H
/* Extern for FiM_GetFunctionPermission */
/* polyspace +1 MISRA-C3:8.5 [Justified:Low] "Not a Defect" */
extern FUNC(Std_ReturnType, FIM_CODE) FiM_GetFunctionPermission(
  FiM_FunctionIdType FID, P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA)Permission);

  /* Extern for FiM_MainFunction */
  /* polyspace +1 MISRA-C3:8.5 [Justified:Low] "Not a Defect" */
 extern FUNC(void, FIM_CODE) FiM_MainFunction(void);

  #if (FIM_AVAILABILITY_SUPPORT == STD_ON)
  /* Extern for FiM_SetFunctionAvailable */
  /* polyspace +1 MISRA-C3:8.5 [Justified:Low] "Not a Defect" */
  extern FUNC(Std_ReturnType, FIM_CODE) FiM_SetFunctionAvailable(
      FiM_FunctionIdType FID, VAR(boolean, AUTOMATIC)Availability);
  #endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */

#endif /* RTE_FIM_H*/
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Extern for mask value for each type of MASK */
extern CONST(uint8, FIM_CONST)FiM_GaaMaskValues[FIM_FOUR];

/* Extern for expected result for each type of MASK */
extern CONST(uint8, FIM_CONST)FiM_GaaExpMaskedResult[FIM_FOUR];

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */

#endif /* FIM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
