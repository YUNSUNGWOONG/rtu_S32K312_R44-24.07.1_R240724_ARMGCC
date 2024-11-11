/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_IntFunc.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Declare all internal functions of CryIf module                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.3.0   12-Aug-2022        DienTC1      #595                             **
*******************************************************************************/

#ifndef CRYIF_INTFUNC_H
#define CRYIF_INTFUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For standard types */
#include "CryIf_IntTypes.h"

#define CRYIF_START_SEC_CODE
#include "MemMap.h"

/* API declaration for get index of channel array function */
extern FUNC(uint32, CRYIF_CODE) CryIf_GetIndexChannel(\
  VAR(uint32, AUTOMATIC) Channel);

/* API declaration for get index of key array function */
extern FUNC(uint32, CRYIF_CODE) CryIf_GetIndexKey(\
  VAR(uint32, AUTOMATIC) KeyId);

/* API declaration for get index of key element array function */
extern FUNC(uint32, CRYIF_CODE) CryIf_GetIndexKeyElement(\
  VAR(uint32, AUTOMATIC) IndexKey,\
  VAR(uint32, AUTOMATIC) ElementId, \
  VAR(uint32, AUTOMATIC) numberElement);
/* API declaration for dispatch key of process job function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_DispatchKey(\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) ptrJob,\
  VAR(Crypto_ServiceInfoType, AUTOMATIC) serJob,\
  VAR(uint32, AUTOMATIC) keyInfo);
/* API declaration for redirect key of process job function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_RedirectKey(\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) ptrJob);

#define CRYIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CRYIF_INTFUNC_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
