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
**  SRC-MODULE: Dcm_DslManageSecurity.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DslManageSecurity                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   HueKM          AR440 Implementation                **
** 0.0.2     13-Oct-2020   HueKM          Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DSLMANAGESECURITY_H
#define DCM_DSLMANAGESECURITY_H

/*******************************************************************************
**                           Include Section                                  **
*******************************************************************************/
#include "Dcm_PCTypes.h"

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_InitManageSecurity(
  Dcm_ConfigConstPtrType pConfig);

extern FUNC(boolean, DCM_CODE) Dcm_IsSecurityLevelLocked(
  void);

extern FUNC(Dcm_SecLevelType, DCM_CODE) DslInternal_GetSecurityLevel(
  void);

extern FUNC(void, DCM_CODE) DslInternal_SetSecurityLevel(
  Dcm_SecLevelType SecurityLevel);

extern FUNC(boolean, DCM_CODE) Dcm_IsSecurityLevelIndexValid(
  void);

extern FUNC(uint8, DCM_CODE) Dcm_GetSecurityLevelIndex(
  void);

extern FUNC(void, DCM_CODE) Dcm_SetSecurityLevelIndex(
  uint8 SecLvlIdx);

extern FUNC(Dcm_SecurityLevConfigConstPtrType, DCM_CODE) 
  Dcm_GetSecurityLevelConfig(void);

extern FUNC(Dcm_SecurityLevConfigConstPtrType, DCM_CODE) 
  Dcm_GetSecurityLevelConfigByIndex(uint8 SecLvlIdx);

extern FUNC(Dcm_SecurityLevConfigConstPtrType, DCM_CODE) 
  Dcm_GetSecurityLevelConfigByLevel(Dcm_SecLevelType SecLvl);

extern FUNC(void, DCM_CODE) Dcm_IncSecurityAttemptCounter(void);

extern FUNC(void, DCM_CODE) Dcm_DecSecurityAttemptCounter(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsSecurityAttemptCounterExceeded(void);

extern FUNC(void, DCM_CODE) Dcm_ResetSecurityAttemptCounter(void);

extern FUNC(uint8, DCM_CODE) Dcm_GetSecurityAttemptCounter(void);

extern FUNC(void, DCM_CODE) Dcm_SetSecurityAttemptCounter(
  uint8 AttCounter);

extern FUNC(void, DCM_CODE) Dcm_StartRestoreSecurityAttemptCounters(void);

extern FUNC(void, DCM_CODE) Dcm_WaitRestoreSecurityAttemptCounters(void);

extern FUNC(void, DCM_CODE) Dcm_CancelRestoreSecurityAttemptCounters(void);

extern FUNC(void, DCM_CODE) Dcm_RestoreSecurityAttemptCountersDone(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsSecurityAttemptCounterRestored(
  uint8 ServiceId, 
  uint8 SubServiceId, 
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_StartInformSecurityAttemptCounters(void);

extern FUNC(void, DCM_CODE) Dcm_WaitInformSecurityAttemptCounters(void);

extern FUNC(void, DCM_CODE) Dcm_CancelInformSecurityAttemptCounters(void);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
