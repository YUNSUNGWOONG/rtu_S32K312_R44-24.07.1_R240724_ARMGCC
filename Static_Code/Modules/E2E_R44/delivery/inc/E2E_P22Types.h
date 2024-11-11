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
**  SRC-MODULE: E2E_P22Types.h                                                **
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
** 1.0.1.1  27-Jun-2022    Gongbin Lim      #CP44-320                         **
** 0.0.1    12-Sep-2019    TruongBX         Initial Version                   **
** 0.0.2    20-Feb-2020    CuongLX          Remove marcro less meaning        **
** 0.0.3    01-Oct-2020    MinhNQ26         Fix code review comments (#15965) **
*******************************************************************************/

#ifndef E2E_P22TYPES_H
#define E2E_P22TYPES_H

#include "Std_Types.h"

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/
/* @Trace: E2E_SUD_MACRO_009, E2E_SUD_DATATYPE_008 */
#define E2E_P22_CNT_ZERO                (0x00U)

#define E2E_P22_CNT_BYTE_ONE            (0x01U)

#define E2E_P22_CNT_MAX                 (0x0FU)

#define E2E_P22_CNT_MAX_VL_CYCLE        (0x0FU +0x01U)

#define E2E_P22_CRC_INIT_VALUE          (0xFFU)

#define E2E_P22_LEN_OFS_BYTE_ONE        (0x01U)

/* The minimal length of data in bit */
#define E2E_P22_MIN_DATA_LENGTH_LIMIT   (16U)

/* Length of data id list */
#define E2E_P22_LENGTH_OF_DATA_ID_LIST  (16U)

/*******************************************************************************
**                      Types Definitions                                     **
*******************************************************************************/
/*
 * Structure E2E_P22ConfigType contains configuration of transmitted data for
 * E2E_Profile 22
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not followed
 */
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR."  */
typedef struct
{
    
    /* length of data in bits */
    uint16 DataLength;

    /* List of  DataID of Data */
    uint8 DataIDList[E2E_P22_LENGTH_OF_DATA_ID_LIST];

    /* Maximum allowed difference between the counter value of the current message and the previous valid message */
    uint8 MaxDeltaCounter;

    /* Offset of the E2E header in the Data[] array in bit */
    uint16 Offset;

} E2E_P22ConfigType;

/*
 * Structure E2E_P22ProtectStateType contains state of the sender for a Data
 * protected with E2E Profile 22.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef struct
{
    
    /* Counter to be used for protecting the next Data */
    uint8 Counter;

} E2E_P22ProtectStateType;

/*
 * Enum E2E_P22CheckStatusType is for result of the verification of the Data
 * in E2E Profile 22, determined by the Check function.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not follwed
 */
typedef enum
{
    
    /* The new data has been received according to communication medium */
    E2E_P22STATUS_OK = 0x00U,

    /*
    * The Check function has been invoked but no new Data is not available since
    * the last call
    */
    E2E_P22STATUS_NONEWDATA = 0x01U,

    /*
    * The data has been received have CRC or DataID or Length is incorrect
    */
    E2E_P22STATUS_ERROR = 0x07U,

    /*
    * The new data has been received according to communication medium, the CRC
    * is correct, but the Counter is identical to the most recent Data
    * received
    */
    E2E_P22STATUS_REPEATED = 0x08U,

    /*
    * some Data in the sequence have been probably lost since the last
    * correct/initial reception
    */
    E2E_P22STATUS_OKSOMELOST = 0x20U,

    /*
    * The new data has been received according to communication medium, the CRC
    * is correct, but the Counter Delta is too big
    */
    E2E_P22STATUS_WRONGSEQUENCE = 0x40U

} E2E_P22CheckStatusType;

/*
 * Structure E2E_P22CheckStateType contains State of the receiver for a Data
 * protected with E2E Profile 22.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI AUTOEVER
 * coding style is not followed
 */
typedef struct
{
    
    /* Counter of the data in previous cycle */
    uint8 Counter;

    /* Result of the verification of the Data, determined by the Check function */
    E2E_P22CheckStatusType Status;

} E2E_P22CheckStateType;
/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

#endif /* E2E_P22TYPES_H */
