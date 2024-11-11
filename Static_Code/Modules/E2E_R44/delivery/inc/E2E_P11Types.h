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
**  SRC-MODULE: E2E_P11Types.h                                                **
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
** Revision Date                By              Description                   **
********************************************************************************
** 1.0.1.1  27-Jun-2022         Gongbin Lim          #CP44-320                **
** 0.0.1    02-Sep-2019         VuHB            Initial Version               **
** 0.0.2    20-Feb-2020         CuongLX         Remove marcro less meaning    **
*******************************************************************************/
#ifndef E2E_P11TYPES_H
#define E2E_P11TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Standard types header file */
#include "Std_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/******************************************************************************
**                define macro for profile 11                                 **
*******************************************************************************/
/* @Trace: E2E_SUD_MACRO_008, E2E_SUD_DATATYPE_007 */
/* Maximum value of counter for E2E profile 11 */
#define  E2E_P11_CNT_MAX                                         (0x0EU)

/* Limit value of counter for E2E profile 11 */
#define  E2E_P11_CNT_LIMIT                                       (0x0FU)

/* The initial value for Crc calculation */
#define  E2E_P11_CRC_INIT_VALUE                                  (0xFFU)

/* Limit value of data length for E2E profile 11 */
#define  E2E_P11_MAX_DATA_LENGTH_LIMIT                           (240U)

/**********************************************************************/
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR."  */

/* Enum E2E_P11DataIDModeType contains DataIDMode for CRC calculation */

typedef enum 
{
  /* CRC calculation should be done on both high and low bytes */
  E2E_P11_DATAID_BOTH = 0U,

  /* CRC calculation should be done on low byte only */
  E2E_P11_DATAID_NIBBLE = 3U
} E2E_P11DataIDMode;

/*
 * Structure E2E_P11ConfigType contains configuration of transmitted data for
 * E2E_Profile 11.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct 
{
  /*
   * Length of Data, in bits.
   *
   * The value shall be a multiple of 8 and shall be <= 240.
   */
  uint16 DataLength;

  /* A system-unique identifier of the Data */
  uint16 DataID;

  /*
   * Maximum allowed gap between two counter values of two consecutively
   * received valid Data. For example, if the receiver gets Data with counter 1
   * and MaxDeltaCounter is 3, then at the next reception the receiver can
   * accept Counters with values 2, 3 or 4.
   */
  uint8 MaxDeltaCounter;

  /* Inclusion mode of ID in CRC computation */
  E2E_P11DataIDMode DataIDMode;

  /* Bit offset of CRC in MSB first order. 
   * The offset shall be a multiple of 8. 
   */
  uint16 CRCOffset;

  /* Bit offset of Counter in MSB first order. 
   * The offset shall be a multiple of 4. 
   */
  uint16 CounterOffset;

  /* Bit offset of the low nibble of the high byte of Data ID. */
  uint16 DataIDNibbleOffset;

} E2E_P11ConfigType;

/*
 * Structure E2E_P11ProtectStateType contains state of the sender for a Data
 * protected with E2E Profile 11.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct 
{
  /*
   * Counter to be used for protecting the next Data. The initial value is 0,
   * which means that in the first cycle, Counter is 0. Each time
   * E2E_P11Protect() is called, it increments the counter up to 0xE.
   */
  uint8 Counter;

} E2E_P11ProtectStateType;

/*
 * Enum E2E_P05CheckStatusType is for result of the verification of the Data
 * in E2E Profile 5, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed
 */
typedef enum 
{
  /*
   * OK: the checks of the Data in this cycle were successful (including counter
   * check, which was incremented by 1).
   */
  E2E_P11STATUS_OK = 0x0U,

  /*
   * Error: the Check function has been invoked but no new Data is not available
   * since the last call, according to communication medium (e.g. RTE, COM). As
   * a result, no E2E checks of Data have been consequently executed.
   *
   * This may be considered similar to E2E_P11STATUS_REPEATED.
   */
  E2E_P11STATUS_NONEWDATA = 0x1U,

  /*
   * Error: error not related to counters occurred (e.g. wrong crc, wrong
   * length).
   */
  E2E_P11STATUS_ERROR = 0x7U,

  /*
   * Error: the checks of the Data in this cycle were successful, with the
   * exception of the repetition.
   */
  E2E_P11STATUS_REPEATED = 0x8U,

  /*
   * OK: the checks of the Data in this cycle were successful (including counter
   * check, which was incremented within the allowed configured delta).
   */
  E2E_P11STATUS_OKSOMELOST = 0x20U,

  /*
   * Error: the checks of the Data in this cycle were successful, with the
   * exception of counter jump, which changed more than the allowed delta.
   */
  E2E_P11STATUS_WRONGSEQUENCE = 0x40U
} E2E_P11CheckStatusType;

/*
 * Structure E2E_P11CheckStateType contains State of the receiver for a Data
 * protected with E2E Profile 11.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed
 */
typedef struct 
{

  /* Counter of the data in previous cycle. */
  uint8 Counter;
    /*
   * Result of the verification of the Data in this cycle, determined by the
   * Check function.
   */
  E2E_P11CheckStatusType Status;

} E2E_P11CheckStateType;

/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

#endif /* E2E_P11TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
