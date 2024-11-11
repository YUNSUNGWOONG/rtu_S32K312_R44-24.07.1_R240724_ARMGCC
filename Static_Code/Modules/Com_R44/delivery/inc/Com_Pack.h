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
**  SRC-MODULE: Com_Pack.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of pack functions.                   **
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

#ifndef COM_PACK_H
#define COM_PACK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**          Function Prototypes for Tx Signal                                 **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackOneByte
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackBytes
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackFiveBytes
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackEightBytes
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackEightByteOrdering
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackNineBytes
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackNineByteOrdering
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackByteOrdering
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackFiveByteOrdering
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackNBytes
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Pack16bit
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Pack32bit
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Write_8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Write_16
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Write_32
 (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
   P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Write_64
 (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_Write_NBytes
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
   P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_PackAndValidateSigGrp
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpMaskingDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_PackSigGrp
                      (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpMaskingDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"  

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_PackAndValidateSigGrpArray
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"  

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_PackSigGrpArray
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"                

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_Validate_NBytes
                           (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                            P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                            PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_Validate_32
                           (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                            P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                            PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_Validate_64
                           (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                            P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                            PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_Validate_16
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpTarget, PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_Validate_8
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
  PduLengthType LddSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackBytes64bit
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackBytes64bitOrdering
                 (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* COM_PACK_H */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
