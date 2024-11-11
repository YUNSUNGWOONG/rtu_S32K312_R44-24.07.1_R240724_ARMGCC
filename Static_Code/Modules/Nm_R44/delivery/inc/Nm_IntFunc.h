/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_IntFunc.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provision of header file for Nm_IntFunc.c                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

#ifndef NM_INTFUNC_H
#define NM_INTFUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of Nm Header File */
#include "Nm.h"

/*******************************************************************************
**                       Version Information                                  **
*******************************************************************************/
#define NM_INTFUNC_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define NM_INTFUNC_AR_RELEASE_MINOR_VERSION       (0x04u)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(boolean, NM_CODE) Nm_GetChannelIndex(
  VAR(NetworkHandleType, NM_APPL_DATA) chnlId,
  P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) ptrChnlIdx);

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_CheckShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_DelayShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_StartShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_PerformShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
extern FUNC(void, NM_CODE) Nm_AbortShutdown(
  VAR(uint8, NM_APPL_DATA) startIdx,
  VAR(uint8, NM_APPL_DATA) clusterIdx,
  VAR(uint8, NM_APPL_DATA) clusterSize);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, NM_CODE) Nm_SetRequest(
  VAR(NetworkHandleType, NM_APPL_DATA) networkHandle,
  VAR(uint8, NM_APPL_DATA) networkIdx);
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* NM_INTFUNC_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
