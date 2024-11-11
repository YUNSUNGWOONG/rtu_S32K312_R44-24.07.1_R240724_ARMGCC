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
**  SRC-MODULE: E2E_P07Types.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : Header for global data types and function prototypes          **
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
** 0.0.1    11-Sep-2019    DucNV19         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
** 0.0.3    01-Oct-2020    MinhNQ26        Fix code review comments (#15965)  **
*******************************************************************************/

#ifndef E2E_P07TYPES_H
#define E2E_P07TYPES_H

#include "Std_Types.h"

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/
/* @Trace: E2E_SUD_MACRO_007, E2E_SUD_DATATYPE_006 */
/* Offset of Length for E2E profile 7 */
#define E2E_P07_LEN_OFS_BYTE_ONE                        (0x08U)

/* Offset of Counter for E2E profile 7 */
#define E2E_P07_CNT_OFS_BYTE_ONE                        (0x0CU)

/* Offset of Counter for E2E profile 7 */
#define E2E_P07_DATAID_OFS_BYTE_ONE                     (0x10U)

/* The max value of counter */
#define E2E_P07_CNT_MAX                                 (0xFFFFFFFFUL)

/* The start value for Crc calculation */
#define E2E_P07_CRC_START_VAL                           (0xFFFFFFFFFFFFFFFFULL)

/* The minimal length of data in bit */
#define E2E_P07_MIN_DATA_LENGTH_LIMIT                   (160U)

/* The macro use for loop: 4 byte data */
#define E2E_P07_FOUR_BYTE                               (0x04U)

/* The macro use for loop: 8 byte data */
#define E2E_P07_EIGHT_BYTE                              (0x08U)

/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR."  */
/*
 * Structure E2E_P07ConfigType contains configuration of transmitted data for
 * E2E_Profile 7.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct
{
  /* A system-unique identifier of the Data */
  uint32 DataID;

  /* 
   * Bit offset of the first bit of the E2E header from the beginning of the 
   * Data (bit numbering: bit 0 is the least important). The offset shall be
   * a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(20*8).
   * Example: If Offset equals 8, then the high byte of the E2E Length (32 bit)
   * is written to Byte 1, the low Byte is written to Byte 2.
   */
  uint32 Offset;

  /* 
   * Minimal Length of Data, in bits.
   * E2E checks that Length is ≥ MinDataLength.
   * The value shall be >= 20*8 (4kB) and shall be <= MaxDataLength
   */
  uint32 MinDataLength;

  /* 
   * Maximal Length of Data, in bits.
   * E2E checks that DataLength is ≤ MaxDataLength.
   * MaxDataLength shall be ≥ MinDataLength.
   */
  uint32 MaxDataLength;

  /* 
   * Maximum allowed gap between two counter values of two consecutively
   * received valid Data. For example, if the receiver gets Data with counter 1
   * and MaxDeltaCounter is 3, then at the next reception the receiver can 
   * accept Counters with values 2, 3 or 4.
   */
  uint32 MaxDeltaCounter;

} E2E_P07ConfigType;

/*
 * Structure E2E_P07ProtectStateType contains state of the sender for a Data
 * protected with E2E Profile 7.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct
{
  /* 
   * Counter to be used for protecting the next Data. The initial value is 0,
   * which means that in the first cycle, Counter is 0. Each time
   * E2E_P07Protect() is called, it increments the counter up to 0xFFFFFFFF.
   */
  uint32 Counter;
} E2E_P07ProtectStateType;

/*
 * Enum E2E_P07CheckStatusType is for result of the verification of the Data
 * in E2E Profile 7, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed
 */
typedef enum
{
  /* 
   * OK: the checks of the Data in this cycle were successful (including counter
   * check, which was incremented by 1). 
   */
  E2E_P07STATUS_OK = 0x0U,

  /* 
   * Error: the Check function has been invoked but no new Data is not available
   * since the last call, according to communication medium (e.g. RTE, COM). As
   * a result, no E2E checks of Data have been consequently executed.
   * 
   * This may be considered similar to E2E_P07STATUS_REPEATED.
   */
  E2E_P07STATUS_NONEWDATA = 0x1U,

  /* 
   * Error: error not related to counters occurred (e.g. wrong crc, wrong 
   * length,wrong options, wrong data id).
   */
  E2E_P07STATUS_ERROR = 0x2U,

  /* 
   * Error: the checks of the Data in this cycle were successful, with the 
   * exception of the repetition.
   */
  E2E_P07STATUS_REPEATED = 0x8U,

  /* 
   * OK: the checks of the Data in this cycle were successful (including counter
   * check, which was incremented within the allowed configured delta). 
   */
  E2E_P07STATUS_OKSOMELOST = 0x20U,

  /* 
   * Error: the checks of the Data in this cycle were successful, with the
   * exception of counter jump, which changed more than the allowed delta.
   */
  E2E_P07STATUS_WRONGSEQUENCE = 0x40U

} E2E_P07CheckStatusType;

/*
 * Structure E2E_P07CheckStateType contains State of the receiver for a Data
 * protected with E2E Profile 7.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed
 */
typedef struct
{
  /* 
   * Result of the verification of the Data in this cycle, determined by the
   * Check function.
   */
  E2E_P07CheckStatusType Status;

  /* Counter of the data in previous cycle. */
  uint32 Counter;

} E2E_P07CheckStateType;
/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

#endif
