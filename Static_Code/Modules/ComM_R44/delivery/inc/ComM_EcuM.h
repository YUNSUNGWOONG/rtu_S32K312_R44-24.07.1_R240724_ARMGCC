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
**  INC-MODULE: ComM_EcuM.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of EcuM                     **
**              Indication API's                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef COMM_ECUM_H
#define COMM_ECUM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Cfg.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_EcuM_WakeUpIndication */
extern FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication(NetworkHandleType
  Channel);
#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))

#define COMM_START_SEC_CODE
#include "MemMap.h"
/* Extern for ComM_EcuM_WakeUpIndication */
extern FUNC(void, COMM_CODE) ComM_EcuM_PNCWakeUpIndication(PNCHandleType
  PNCid);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#endif
#endif /* COMM_ECUM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

