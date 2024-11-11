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
**  SRC-MODULE: Com_Filter.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of filter functions.                 **
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

#ifndef COM_FILTER_H
#define COM_FILTER_H

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

extern FUNC(boolean, COM_CODE) Com_FNever
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_16
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_32
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_16
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_32
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:begin<MISRA-C3:5.1:Not a defect:Low> Identifiers are distinct by the postfix */
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_EIGHT
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_SIXTEEN
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_THIRTYTWO
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C3:5.1:Not a defect:Low> Identifiers are distinct by the postfix */

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsWithin_u8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsWithin_s8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsWithin_u16
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsWithin_s16
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsWithin_u32
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsWithin_s32
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsOutside_u8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsOutside_s8
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsOutside_u16
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsOutside_s16
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsOutside_u32
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FNewIsOutside_s32
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_FOneEveryN
                          (P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                      P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod);

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* COM_FILTER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
