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
**  SRC-MODULE: E2E_P02Types.h                                                **
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
** 0.0.1    02-September-2010    VuHB            Initial Version              **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
*******************************************************************************/
#ifndef E2E_P02TYPES_H
#define E2E_P02TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Standard types header file */
#include "Std_Types.h"

/******************************************************************************
**                define macro for profile 2                                 **
*******************************************************************************/
/* @Trace: E2E_SUD_DATATYPE_002 E2E_SUD_MACRO_003 */
/* Limit value of counter for E2E profile 2 */
#define E2E_P02_CNT_LIMIT (0x10U)

/* Maximum value of counter for E2E profile 2*/
#define E2E_P02_CNT_MAX (0x0FU)

/* Initil value for E2E_Profile 2 for CRC */
#define E2E_P02_CRC_INIT_VALUE (0xFFU)

/* Minimum value of counter for E2E profile 2*/
#define E2E_P02_CNT_MIN (0x00U)

/* Minimum data length for E2E Profile 2 */
#define E2E_P02_MIN_DATA_LENGTH_LIMIT (16U)

/* Maximmum data length for E2E Profile 2 */
#define E2E_P02_MAX_DATA_LENGTH_LIMIT (256U)

/* Length of data id list */
#define E2E_P02_LENGTH_OF_DATA_ID_LIST (16U)

/*******************************************************************************
**                      E2E Profile 2 types                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR."  */
/*
 * Structure E2E_P02ConfigType contains configuration of transmitted data for
 * E2E_Profile2
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
	/* Length of data, in bits */
	uint16 DataLength;
	/* Array of Data ID */
	uint8 DataIDList[E2E_P02_LENGTH_OF_DATA_ID_LIST];
	/*
   * Initial maximum allowed gap between two counter values of two consecutively
   * received valid data
   */
	uint8 MaxDeltaCounterInit;
	/*The maximum amount of missing or repeated Data which the receiver does not
   * expect to exceed under normal communication conditions
  */
	uint8 MaxNoNewOrRepeatedData;
	/*Number of Data required forvalidating the consistency of the counter that
   * must be received with avalid counter
   */
	uint8 SyncCounterInit;
	/*Offset of the E2E header in the Data[]array in bits.
   *It shall be:0 ≤ Offset ≤ DataLength-(2*8)
   */
	uint16 Offset;

} E2E_P02ConfigType;
/*
 * Structure E2E_P02ProtectStateType contains state of the sender for a Data
 * protected with E2E Profile 2.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
	/* Counter to be used for protecting the Data. The initial value is 0. As the
   * counter is incremented before sending, the first Data will have the counter value 1
   */
	uint8 Counter;

} E2E_P02ProtectStateType;
/*
 * Enum E2E_P02ReceiverStatusType is for result of the verification of the Data
 * in E2E Profile 2, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */

typedef enum
{
	/* The new data has been received according to communication medium */
	E2E_P02STATUS_OK = 0x00U,

	/*
   * The Check function has been invoked but no new Data is not available since
   * the last call
   */
	E2E_P02STATUS_NONEWDATA = 0x01U,

	/*
   * The data has been received according to communication medium, but the CRC
   * is incorrect
   */
	E2E_P02STATUS_WRONGCRC = 0x02U,

	/*
   * This is the first Data since the receiver's initialization or
   * reinitialization
   */
	E2E_P02STATUS_INITIAL = 0x04U,
	/*
  *The new data has been received after detection of an unexpectedbehavior of counter. 
  *The data has a correct CRC and a counter within the expected range with 
  *respect to the most recent Data received, but the determined continuity 
  *check for the counter is not finalized yet.
  */
	E2E_P02STATUS_SYNC = 0x03U,
	/*
   * The new data has been received according to communication medium, the CRC
   * is correct, but the Counter is identical to the most recent Data received
   */
	E2E_P02STATUS_REPEATED = 0x08U,

	/*
   * The new data has been received according to communication medium, the CRC
   * is correct, but the Counter Delta is too big
   */
	E2E_P02STATUS_OKSOMELOST = 0x20U,

	/*
   * The new data has been received according to communication medium, the CRC
   * is correct, but the Counter Delta is too big
   */
	E2E_P02STATUS_WRONGSEQUENCE = 0x40U
} E2E_P02CheckStatusType;

/*
 * Enum E2E_P02CheckStateType is for result of the verification of the Data
 * in E2E Profile 2, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
	/* Counter value most recently received */
	uint8 LastValidCounter;
	/* Number of data (messages) lost since reception of last valid one */
	uint8 LostData;
	/*
	 * MaxDeltaCounter specifies the maximum allowed difference between two
	 * counter values of consecutively received valid messages
	 */
	uint8 MaxDeltaCounter;
	/* Indicates to E2E Library that a new data is available for Library to be checked*/
	boolean NewDataAvailable;
	/* Amount of consecutive reception cycles in which either (1) there was no new data,
 	 * or (2) when the data was repeated.*/
	uint8 NoNewOrRepeatedDataCounter;
	/* Result of the verification of the Data, determined by the Check function */
	E2E_P02CheckStatusType Status;
	/* Number of Data required for validating the consistency of the counter that
	 * must be received with a valid counter
	 */
	uint8 SyncCounter;
	/*
	 * If true means that no correct data has been yet received after the
	 * receiver initialization or reinitialization
	 */
	boolean WaitForFirstData;
} E2E_P02CheckStateType;

/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

#endif /* E2E_P02TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
