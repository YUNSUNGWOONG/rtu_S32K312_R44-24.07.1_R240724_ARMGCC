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
**  INC-MODULE: ComM_Nm.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of Network Management       **
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

#ifndef COMM_NM_H
#define COMM_NM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_Nm_NetworkStartIndication */
extern FUNC(void, COMM_CODE) ComM_Nm_NetworkStartIndication(NetworkHandleType
  Channel);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_Nm_NetworkMode */
extern FUNC(void, COMM_CODE) ComM_Nm_NetworkMode(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_Nm_PrepareBusSleepMode */
extern FUNC(void, COMM_CODE) ComM_Nm_PrepareBusSleepMode(NetworkHandleType
  Channel);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_Nm_BusSleepMode */
extern FUNC(void, COMM_CODE) ComM_Nm_BusSleepMode(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_Nm_RestartIndication  */
extern FUNC(void, COMM_CODE) ComM_Nm_RestartIndication(NetworkHandleType
  Channel);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* COMM_NM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

