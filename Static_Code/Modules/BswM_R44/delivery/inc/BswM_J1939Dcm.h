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
**  FILE-NAME : BswM_J1939Dcm.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  PURPOSE   : Providing interface to FrSM                                   **
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

#ifndef BSWM_J1939DCM_H
#define BSWM_J1939DCM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "J1939Dcm.h"

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
/* Extern for BswM_J1939DcmBroadcastStatus */
extern FUNC(void, BSWM_CODE) BswM_J1939DcmBroadcastStatus
 (uint16 NetworkMask);
#define BSWM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* BSWM_J1939DCM_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
