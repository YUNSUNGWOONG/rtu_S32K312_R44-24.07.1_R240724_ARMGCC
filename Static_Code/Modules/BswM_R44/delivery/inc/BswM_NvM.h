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
**  FILE-NAME : BswM_NvM.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  PURPOSE   : Providing interface to NvM                                    **
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
** 0.0.1     27-Feb-2020   ThangMA           R44-Redmine #4579, #10093        **
*******************************************************************************/

#ifndef BSWM_NVM_H
#define BSWM_NVM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"
#include "NvM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define BSWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, BSWM_CODE) BswM_NvM_CurrentJobMode
  (NvM_MultiBlockRequestType MultiBlockRequest,
   NvM_RequestResultType CurrentJobMode);

extern FUNC(void, BSWM_CODE) BswM_NvM_CurrentBlockMode
(NvM_BlockIdType Block, NvM_RequestResultType CurrentBlockMode);
#define BSWM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* BSWM_NVM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
