/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_UnPack.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of unpack functions.                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

#ifndef COM_UNPACK_H
#define COM_UNPACK_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackOneByte
             (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                          P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackBytes
             (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                          P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"


#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackFiveBytes
             (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                          P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackNBytes
             (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                          P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackFiveByteOrdering
             (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                          P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackByteOrdering
             (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                          P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackEightByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackEightBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackNineByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackNineBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackBytes64bit
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackBytes64bitOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"




#endif /* COM_UNPACK_H */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

