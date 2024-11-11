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
**  SRC-MODULE: E2E_SMTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : Header for E2E State Machine driver                           **
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
********************************************************************************
** 1.0.1.1  27-Jun-2022    Gongbin Lim     #CP44-320                          **
** 0.0.1    05-Sep-2019    CuongLX         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
*******************************************************************************/
#ifndef E2E_SMTYPES_H
#define E2E_SMTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include for E2E External API's */
#include "Std_Types.h"

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR."  */
/*
 * Structure E2E_SMStateType contains state of the protection of a communication
 * channel.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
 /* @Trace: E2E_SUD_DATATYPE_009 */
typedef enum 
{
  /* 
   * Communication functioning properly according to E2E, data can be used.
   */
  E2E_SM_VALID = 0x00U,
  
  /* 
   * State before E2E_SMCheckInit() is invoked, data cannot be used.
   */
  E2E_SM_DEINIT = 0x01U,
  
  /*
   * No data from the sender is available since the initialization,
   * data cannot be used.
   */
  E2E_SM_NODATA = 0x02U,
  
  /*
   * There has been some data received since startup, but it is not yet
   * possible use it, data cannot be used.
   */
  E2E_SM_INIT = 0x03U,
  
  /*
   * Communication not functioning properly, data cannot be used.
   */
  E2E_SM_INVALID = 0x4U,
  
  /*
   * reserved for runtime errors (shall not be ued for any state in future)
   */
  reserved = 0x07U
} E2E_SMStateType;

/*
 * Structure E2E_SMConfigType contains configuration of communication channel
 * for exchanging data.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */

typedef struct 
{
  /* 
   Size of the monitoring window for the state machine.
   */
  uint8 WindowSize;
 
  /* 
   * Minimal number of checks in which ProfileStatus equal to E2E_P_OK was
   * determined within the last WindowSize checks (for the state E2E_SM_INIT)
   * required to change to state E2E_SM_VALID.
   */
  uint8 MinOkStateInit;
  
  /* 
   * Maximal number of checks in which ProfileStatus equal to E2E_P_ERROR was
   * determined, within the last WindowSize checks (for the state E2E_SM_INIT). 
   */
  uint8 MaxErrorStateInit;
  
  /* 
   * Minimal number of checks in which ProfileStatus equal to E2E_P_OK was
   * determined within the last WindowSize checks (for the state E2E_SM_VALID)
   * required to keep in state E2E_SM_VALID.
   */
  uint8 MinOkStateValid;
  
  /*
   * Maximal number of checks in which ProfileStatus equal to E2E_P_ERROR was
   * determined, within the last WindowSize checks (for the state E2E_SM_VALID)
   .
   */
  uint8 MaxErrorStateValid;
  
  /*
   * Minimum number of checks in which ProfileStatus equal to E2E_P_OK was
   * determined within the last WindowSize checks (for the state E2E_SM_INVALID)
   * required to change to state E2E_SM_VALID.
   */
  uint8 MinOkStateInvalid;
  
  /*
   * Maximal number of checks in which ProfileStatus equal to E2E_P_ERROR was
   * determined, within the last WindowSize checks (for the state E2E_SM_INVALID)
   .
   */
  uint8 MaxErrorStateInvalid;
} E2E_SMConfigType;

/*
 * Structure E2E_SMCheckStateType contains state of the protection of a
 * communication channel.
 * Since this is E2E library so others vendors also can use this so here HYUNDAI
 * AUTOEVER coding style is not follwed.
 */
typedef struct 
{
  /* 
   * Pointer to an array, in which the ProfileStatus-es of the last E2Echecks
   * are stored. The array size shall be WindowSize
   */ 
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) ProfileStatusWindow;
  
  /*
   * Index in the array, at which the next ProfileStatus is to be written.
   */
  uint8 WindowTopIndex;
  
  /*
   * Count of checks in which ProfileStatus equal to E2E_P_OK was determined,
   * within the last WindowSize checks.
   */
  uint8 OkCount;
  
  /*
   * Count of checks in which ProfileStatus equal to E2E_P_ERROR was determined,
   * within the last WindowSize checks.
   */
  uint8 ErrorCount;
  
  /*
   * The current state in the state machine. The value is not explicitly used in
   * the pseudocode of the state machine, because it is expressed in UML as UML
   * states.
   */
  E2E_SMStateType SMState;
} E2E_SMCheckStateType;

/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "This is not a defect and refer SWS_COMPILER_00013 of AUTOSAR." */

/*******************************************************************************
**                      E2E State Machine types                               **
*******************************************************************************/

#endif /*E2E_SMTYPES_H*/
