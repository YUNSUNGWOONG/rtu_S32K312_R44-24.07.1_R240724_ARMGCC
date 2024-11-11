/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: E2E.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : Header for global Data types and function prototypes          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date           By              Description                        **
********************************************************************************
** 1.0.1.1  27-Jun-2022    Gongbin Lim     #CP44-320                          **
** 0.0.1    04-Sep-2019    CuongLX         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
*******************************************************************************/

#ifndef E2E_H /* ifndef E2E_H */
#define E2E_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "E2E_P01Types.h"
#include "E2E_P02Types.h"
#include "E2E_P04Types.h"
#include "E2E_P05Types.h"
#include "E2E_P06Types.h"
#include "E2E_P07Types.h"
#include "E2E_P11Types.h"
#include "E2E_P22Types.h"
#include "E2E_SMTypes.h"
#include "Crc.h"

/*******************************************************************************
**                      Global DataPtr Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Macro definitions                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00003 SRS_BSW_00004  */
/* @Trace: E2E_SUD_FILE_001 E2E_SUD_DT_009 E2E_SUD_DT_010 E2E_SUD_MACRO_001 */
/* AUTOSAR SPECIFICATION VERSION */

#define   E2E_AR_RELEASE_MAJOR_VERSION             (4U)/*polyspace MISRA2012:2.5 [Justified:Low] "Need this macro to provide unambiguous version identification"*/
#define   E2E_AR_RELEASE_MINOR_VERSION             (4U)/*polyspace MISRA2012:2.5 [Justified:Low] "Need this macro to provide unambiguous version identification"*/
#define   E2E_AR_RELEASE_REVISION_VERSION          (0U) /*polyspace MISRA2012:2.5 [Justified:Low] "Need this macro to provide unambiguous version identification"*/

/* SOFTWARE VERSION INFORMATION */ 

/* E2E software major version number */
#define E2E_SW_MAJOR_VERSION                        (1U)

/* E2E software minor version number */
#define E2E_SW_MINOR_VERSION                        (0U)

/* E2E software patch version */
#define E2E_SW_PATCH_VERSION                        (0U)

/* Module ID for the E2E */
#define E2E_MODULE_ID                               (0x00CFU)

/* Vendor ID for E2E */
#define E2E_VENDOR_ID                               (0x0076U)

/* Version information of CRC module */
#define E2E_CRC_AR_RELEASE_MAJOR_VERSION            (4U)
#define E2E_CRC_AR_RELEASE_MINOR_VERSION            (4U)

/* Macro for masking higher nibble */
#define E2E_HIGH_NIBBLE_MASK                        (0xF0U)

/* Macro for masking lower nibble */
#define E2E_LOW_NIBBLE_MASK                         (0x0FU)

/* Macro for masking whole byte */
#define E2E_FOUR_BYTE_BYTE_MASK                     (0x000000FFUL)

/* Macro for masking whole byte */
#define E2E_LOW_BYTE_MASK                           (0x00FFU)

/* Macro for masking whole byte */
#define E2E_HIGH_BYTE_MASK                          (0xFF00U)

/* Function completed successfully */
#define E2E_E_OK                                    ((Std_ReturnType)0x00U)

/* At least one input pointer is NULL */
#define E2E_E_INPUTERR_NULL                         ((Std_ReturnType)0x13U)

/* At least one parameter is wrong */
#define E2E_E_INPUTERR_WRONG                        ((Std_ReturnType)0x17U)

/* An internal library error has occured */
#define E2E_E_INTERR                                ((Std_ReturnType)0x19U)/*polyspace MISRA2012:2.5 [Justified:Low] "Need this macro to provide unambiguous version identification"*/

/* Any input parameter is invalid */
#define E2E_E_INVALID                               ((Std_ReturnType)0xFFU)/*polyspace MISRA2012:2.5 [Justified:Low] "Need this macro to provide unambiguous version identification"*/

/* Function executed in wrong StatePtr */
#define E2E_E_WRONGSTATE                            ((Std_ReturnType)0x1AU)


/*******************************************************************************
**                      E2E StatePtr machine types                               **
*******************************************************************************/
/*
 * Enum E2E_P02ReceiverStatusType is Profile-independent status of the
 * reception on one single DataPtr in one cycle.
 */
typedef enum 
{
  /*
   * OK: the checks of the DataPtr in this cycle were successful (including counter
   * check).
   */
  E2E_P_OK = 0x00U,

  /* DataPtr has a repeated counter. */
  E2E_P_REPEATED = 0x01U,

  /*
   * The checks of the DataPtr in this cycle were successful, with the exception of
   * counter jump, which changed more than the allowed delta.
   */
  E2E_P_WRONGSEQUENCE = 0x02U,

  /*
   * Error not related to counters occurred (e.g. wrong crc, wrong length, wrong
   * DataPtr ID) or the return of the check function was not OK.
   */
  E2E_P_ERROR = 0x03U,

  /*
   * No value has been received yet (e.g. during initialization). This is used
   * as the initialization value for the buffer, it is not returned by any E2E
   * profile.
   */
  E2E_P_NOTAVAILABLE = 0x04U,

  /* No new DataPtr is available. */
  E2E_P_NONEWDATA = 0x05U

} E2E_PCheckStatusType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P01Protect (
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P01ProtectInit (
  P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P01Check (
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckInit (
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P01MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P01CheckStatusType, AUTOMATIC) Status,
  VAR(boolean, AUTOMATIC) ProfileBehavior);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect (
  P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02ProtectInit (
  P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02Check (
  P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02CheckInit (
  P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P02MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P02CheckStatusType, AUTOMATIC) Status,
  VAR(boolean, AUTOMATIC) ProfileBehavior);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04Protect (
  P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04ProtectInit (
  P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04Check (
  P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckInit (
  P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P04MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P04CheckStatusType, AUTOMATIC) Status);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P05Protect (
  P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P05ProtectInit (
  P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P05Check (
  P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P05CheckInit (
  P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P05MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P05CheckStatusType, AUTOMATIC) Status);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P06Protect (
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P06ProtectInit (
  P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P06Check (
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckInit (
  P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P06MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P06CheckStatusType, AUTOMATIC) Status);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P07Protect (
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint32, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P07ProtectInit (
  P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P07Check (
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint32, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P07CheckInit (
  P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P07MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P07CheckStatusType, AUTOMATIC) Status);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P11Protect (
  P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P11ProtectInit (
  P2VAR(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P11Check (
  P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P11CheckInit (
  P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P11MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P11CheckStatusType, AUTOMATIC) Status);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P22Protect (
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P22ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P22ProtectInit (
  P2VAR(E2E_P22ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P22Check (
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P22CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P22CheckInit (
  P2VAR(E2E_P22CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);

extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P22MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P22CheckStatusType, AUTOMATIC) Status);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck(
    VAR(E2E_PCheckStatusType, AUTOMATIC) ProfileStatus,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr);  

extern FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckInit(
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr);

extern FUNC(void, E2E_CODE) E2E_GetVersionInfo (
  P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfoPtr);

#define E2E_STOP_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

#endif /* endif E2E_H */
