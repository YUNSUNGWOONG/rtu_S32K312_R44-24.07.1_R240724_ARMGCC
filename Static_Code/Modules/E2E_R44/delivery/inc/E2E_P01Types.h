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
**  SRC-MODULE: E2E_P01Types.h                                                **
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
** 0.0.1    03-Sep-2019    DucNV19         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
*******************************************************************************/

#ifndef E2E_P01TYPES_H
#define E2E_P01TYPES_H

#include "Std_Types.h"

/* @Trace: E2E_SUD_DATATYPE_001 E2E_SUD_MACRO_002 */
/* Maximum limit of counter value for E2E profile 1*/
#define E2E_P01_CNT_LIMIT (0x0FU)

/* Maximum value of counter for E2E profile 1 */
#define E2E_P01_CNT_MAX (0x0EU)

/* Xor value of crc profile 1 */
#define E2E_P01_CRC_XOR_VAL (0xFFU)

/* Start value of crc profile 1 */
#define E2E_P01_CRC_START_VAL (0xFFU)

/* Maximmum data length for E2E Profile 1 */
#define E2E_P01_MAX_DATA_LENGTH_LIMIT (240U)

/* DataId value limit for E2E Profile 1 */
#define E2E_P01_DATAID_LOW_LIMIT (0xFFU)

/*polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */
/* Enum E2E_P01DataIDModeType contains DataIDMode for CRC calculation */
typedef enum
{
	/* CRC calculation should be done on both high and low bytes */
	E2E_P01_DATAID_BOTH = 0U,

	/* CRC calculation should be done on either high or low byte */
	E2E_P01_DATAID_ALT = 1U,

	/* CRC calculation should be done on low byte only */
	E2E_P01_DATAID_LOW = 2U,

	/* The low byte is included in the implicit CRC calculation, the low nibble of the high byte is transmitted along with the data (i.e. it is explicitly includedUU, the high nibble of the high byte is not used */
	E2E_P01_DATAID_NIBBLE = 3U

} E2E_P01DataIDMode;

/*
 * Structure E2E_P01ConfigType contains configuration of transmitted data for
 * E2E_Profile1
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
	/* Bit offset of Counter */
	uint16 CounterOffset;

	/* Bit offset of CRC */
	uint16 CRCOffset;

	/* A unique identifier, for protection against masquerading */
	uint16 DataID;

	/*Bit offset of the low nibble of the high byte of Data ID*/
	uint16 DataIDNibbleOffset;

	/* Inclusion mode of ID in CRC computation */
	E2E_P01DataIDMode DataIDMode;

	/* Length of data, in bits */
	uint16 DataLength;

	/* Initial maximum allowed gap between two counter values of two consecutively received valid Data */
	uint8 MaxDeltaCounterInit;

	/* The maximum amount of missing or repeated Data which the receiver does not expect to exceed under normal communication conditions */
	uint8 MaxNoNewOrRepeatedData;

	/* Number of Data required for validating the consistency of the counter that must be received with a valid counter (i.e. counter within the allowed lock-in rangeU after the detection of an unexpected behavior of a received counter */
	uint8 SyncCounterInit;

	/*
  ** Inital maximum allowed gap between two counter values of two consecutively
  ** received valid data
  */
} E2E_P01ConfigType;

/*
 * Structure E2E_P01ProtectStateType contains state of the sender for a Data
 * protected with E2E Profile 1.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
	/* Counter to be used for protecting the next Data */
	uint8 Counter;
} E2E_P01ProtectStateType;

/*
 * Enum E2E_P01CheckStatusType is for result of the verification of the Data
 * in E2E Profile 1, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef enum
{
	/* The new data has been received according to communication medium */
	E2E_P01STATUS_OK = 0x0U,

	/*
   * The Check function has been invoked but no new Data is not available since
   * the last call
   */
	E2E_P01STATUS_NONEWDATA = 0x1U,

	/*
   * The data has been received according to communication medium, but the CRC
   * is incorrect
   */
	E2E_P01STATUS_WRONGCRC = 0x2U,

	/*
   * The new data has been received after detection of an unexpected behavior of counter. 
   * The data has a correct CRC and a counter within the expected range with respect to the most recent Data receivedU, 
   * but the determined continuity check for the counter is not finalized yet
   */
	E2E_P01STATUS_SYNC = 0x3U,

	/*
   * This is the first Data since the receiver's initialization or
   * reinitialization
   */
	E2E_P01STATUS_INITIAL = 0x4U,

	/*
   * The new data has been received according to communication medium, the CRC
   * is correct, but the Counter is identical to the most recent Data
   * received
   */
	E2E_P01STATUS_REPEATED = 0x8U,

	/*
   * some Data in the sequence have been probably lost since the last
   * correct/initial reception
   */
	E2E_P01STATUS_OKSOMELOST = 0x20U,

	/*
   * The new data has been received according to communication medium, the CRC
   * is correct, but the Counter Delta is too big
   */
	E2E_P01STATUS_WRONGSEQUENCE = 0x40U

} E2E_P01CheckStatusType;

/*
 * Structure E2E_P01CheckStateType contains State of the receiver for a Data
 * protected with E2E Profile 1.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
	/* Counter value most recently received */
	uint8 LastValidCounter;

	/*
   * MaxDeltaCounter specifies the maximum allowed difference between two
   * counter values of consecutively received valid messages
   */
	uint8 MaxDeltaCounter;

	/*
   * If true means that no correct data has been yet received after the
   * receiver initialization or reinitialization
   */
	boolean WaitForFirstData;

	/*
   * Indicates to E2E Library that a new data is available for Library to be
   * checked
   */
	boolean NewDataAvailable;

	/* Number of data (messages) lost since reception of last valid one */
	uint8 LostData;

	/* Result of the verification of the Data, determined by the Check function */
	E2E_P01CheckStatusType Status;

	/* Number of Data required for validating the consistency of the counter that must be received with a valid counter */
	uint8 SyncCounter;

	/*Amount of consecutive reception cycles in which either (1) there was no new data, or (2) when the data was repeated */
	uint8 NoNewOrRepeatedDataCounter;

} E2E_P01CheckStateType;

/*polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

#endif
