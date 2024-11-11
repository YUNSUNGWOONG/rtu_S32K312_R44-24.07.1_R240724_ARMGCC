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
**  SRC-MODULE: E2E_P06Types.h                                                **
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
** 0.0.1    07-Sep-2019    DucNV19         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
** 0.0.3    01-Oct-2020    MinhNQ26        Fix code review comments (#15965)  **
*******************************************************************************/

#ifndef E2E_P06TYPES_H
#define E2E_P06TYPES_H

#include "Std_Types.h"

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/
/* @Trace: E2E_SUD_MACRO_006, E2E_SUD_DATATYPE_005 */
/* Maximum value of counter for E2E profile 6 */
#define E2E_P06_CNT_MAX                                           (0xFFU)

/* Counter offset */
#define E2E_P06_CNT_OFS                                           (0x04U)

/* The offset value of high byte of Length */
#define E2E_P06_LEN_OFS_HIGH_BYTE                                 (0x02U)

/* The offset value of low byte of Length */
#define E2E_P06_LEN_OFS_LOW_BYTE                                  (0x03U)

/* The offset value of low byte of CRC */
#define E2E_P06_CRC_OFS_LOW_BYTE                                  (0x1U)

/* The start value for Crc calculation */
#define E2E_P06_CRC_START_VAL                                     (0xFFFFU)

/* The minimal length of data in bits  */
#define E2E_P06_MIN_DATA_LENGTH_LIMIT                             (40U)

/* The maximum length of data */
#define E2E_P06_MAX_DATA_LENGTH_LIMIT                             (32768U)

/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR."  */
/*
 * Structure E2E_P06ConfigType contains configuration of transmitted data for
 * E2E_Profile 6.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct
{
  /* 
   * Bit offset of the first bit of the E2E header from the beginning of the 
   * Data (bit numbering: bit 0 is the least important). The offset shall be
   * a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(5*8).
   * Example: If Offset equals 8, then the high byte of the E2E Crc (16 bit) is
   * written to Byte 1, the low Byte is written to Byte 2.
   */
  uint16 Offset;

  /* 
   * Minimal Length of Data, in bits.
   * E2E checks that Length is ≥ MinDataLength.
   * The value shall be = 4096*8 (4kB) and shall be ≥ 5*8 
   */
  uint16 MinDataLength;

  /* 
   * Maximal Length of Data, in bits.
   * E2E checks that DataLength is ≤ MaxDataLength.
   * The value shall be = 4096*8 (4kB).
   * MaxDataLength shall be ≥ MinDataLength.
   */
  uint16 MaxDataLength;

  /* A system-unique identifier of the Data */
  uint16 DataID;

  /* 
   * Maximum allowed gap between two counter values of two consecutively
   * received valid Data. For example, if the receiver gets Data with counter 1
   * and MaxDeltaCounter is 3, then at the next reception the receiver can 
   * accept Counters with values 2, 3 or 4.
   */
  uint8 MaxDeltaCounter;

} E2E_P06ConfigType;

/*
 * Structure E2E_P06ProtectStateType contains state of the sender for a Data
 * protected with E2E Profile 6.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct
{
  /* 
   * Counter to be used for protecting the next Data. The initial value is 0,
   * which means that in the first cycle, Counter is 0. Each time
   * E2E_P06Protect() is called, it increments the counter up to 0xFF.
   * After the maximum value is reached, the next value is 0x0. The overflow
   * is not reported to the caller.
   */
  uint8 Counter;
} E2E_P06ProtectStateType;

/*
 * Enum E2E_P06CheckStatusType is for result of the verification of the Data
 * in E2E Profile 6, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed
 */
typedef enum
{
  /* 
   * OK: the checks of the Data in this cycle were successful (including counter
   * check, which was incremented by 1). 
   */
  E2E_P06STATUS_OK = 0x0U,

  /* 
   * Error: the Check function has been invoked but no new Data is not available
   * since the last call, according to communication medium (e.g. RTE, COMU. As
   * a result, no E2E checks of Data have been consequently executed.
   * 
   * This may be considered similar to E2E_P06STATUS_REPEATED.
   */
  E2E_P06STATUS_NONEWDATA = 0x1U,

  /* 
   * Error: error not related to counters occurred (e.g. wrong crc, wrong 
   * lengthU.
   */
  E2E_P06STATUS_ERROR = 0x7U,

  /* 
   * Error: the checks of the Data in this cycle were successful, with the 
   * exception of the repetition.
   */
  E2E_P06STATUS_REPEATED = 0x8U,

  /* 
   * OK: the checks of the Data in this cycle were successful (including counter
   * check, which was incremented within the allowed configured deltaU. 
   */
  E2E_P06STATUS_OKSOMELOST = 0x20U,

  /* 
   * Error: the checks of the Data in this cycle were successful, with the
   * exception of counter jump, which changed more than the allowed delta.
   */
  E2E_P06STATUS_WRONGSEQUENCE = 0x40U

} E2E_P06CheckStatusType;

/*
 * Structure E2E_P06CheckStateType contains State of the receiver for a Data
 * protected with E2E Profile 6.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed
 */
typedef struct
{
  /* 
   * Result of the verification of the Data in this cycle, determined by the
   * Check function.
   */
  E2E_P06CheckStatusType Status;

  /* Counter of the data in previous cycle. */
  uint8 Counter;

} E2E_P06CheckStateType;
/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

#endif
