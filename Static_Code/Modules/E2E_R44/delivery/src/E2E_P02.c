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
**  SRC-MODULE: E2E_P02.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 2 driver            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 1.0.1.1   27-Jun-2022   Gongbin Lim     #CP44-320                          **
** 0.0.1     02-Sep-2019   VuHB            Initial Version                    **
** 0.0.2     20-Feb-2020   CuongLX         Remove marcro less meaning         **
** 1.0.1     28-Dec-2021   HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "E2E.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

static FUNC(void,E2E_CODE) E2E_P02CheckStatus( \
    P2CONST(E2E_P02ConfigType,AUTOMATIC,E2E_APPL_DATA) ConfigPtr, \
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, \
    VAR(uint8, AUTOMATIC) ReceivedCounterVal);

static FUNC(Std_ReturnType, AUTOMATIC) E2E_P02CheckParams( \
  P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr);
    
/*******************************************************************************
**                      Global DataPtr Types                                  **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/


/*******************************************************************************
** Function Name        : E2E_P02CheckParams                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Verify data of ConfigPtr parameters of profile 02   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType:                                     **
**                        E2E_E_INPUTERR_WRONG                                **
**                        E2E_E_OK                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
static FUNC(Std_ReturnType, AUTOMATIC) E2E_P02CheckParams(
  P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr)
{ 
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  /* @Trace: SafeE2E_SUD_MF_107 */
  /* Check for the ranges of input parameters */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((E2E_P02_MIN_DATA_LENGTH_LIMIT > ConfigPtr->DataLength) || \
      (E2E_P02_MAX_DATA_LENGTH_LIMIT < ConfigPtr->DataLength) || \
      (0x0000U != (ConfigPtr->DataLength % 0x0008U)))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else if (E2E_P02_CNT_MAX < ConfigPtr->MaxDeltaCounterInit)
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else
  {
    returnValue = E2E_E_OK;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}
/*******************************************************************************
** Function Name        : E2E_P02Protect                                      **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Protects the array/buffer to be transmitted using   **
**                        the E2E profile 2.This includes checksum            **
**                        calculation, handling of sequence counter and       **
**                        Data ID.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state  **
**                        DataPtr: Pointer to the data to be protected.       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType:                                     **
**                        E2E_E_INPUTERR_NULL                                 **
**                        E2E_E_INPUTERR_WRONG                                **
**                        E2E_E_INTERR                                        **
**                        E2E_E_OK                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_P02CheckParams         **
**                                                 Crc_CalculateCRC8H2F       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect (
  P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to store calculated CRC value */
  VAR(uint8, AUTOMATIC) calculateCrc = 0x00U;
  /* Local variable to store data length */
  VAR(uint16, AUTOMATIC) dataLength;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  /* @Trace: SafeE2E_SUD_MF_100 */    
  /* Check for the invalid input parameters */
  if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if((ConfigPtr->DataLength / 0x0008U) < 0x01U)
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }  
  else
  {
    returnValue = E2E_P02CheckParams(ConfigPtr);
  }
  /* @Trace: SafeE2E_SUD_MF_101 */
  if (E2E_E_OK == returnValue)
  {
    /* Update the StatePtr Counter */
    
    if (E2E_P02_CNT_MAX > StatePtr->Counter) 
    {
      StatePtr->Counter++;
    }
    else
    {
      StatePtr->Counter = E2E_P02_CNT_MIN;
    }
    /* Update the Counter Byte */
    
    DataPtr[0x01U] = (DataPtr[0x01U] & E2E_HIGH_NIBBLE_MASK) | \
                        (uint8)(StatePtr->Counter & E2E_LOW_NIBBLE_MASK);

    /* 
      *	Calculate the CRC for the DataPtr and the counter and 
      *	update the CRC byte */
     
    dataLength = ConfigPtr->DataLength / 0x0008U;
    
    calculateCrc = Crc_CalculateCRC8H2F( \
      (P2CONST(uint8, AUTOMATIC, E2E_CONST)) & DataPtr[0x01U], \
      (uint32)((uint32)dataLength - (uint32)0x01U), \
      E2E_P02_CRC_INIT_VALUE, TRUE);

    /* Calculate the CRC for the DataId and update the CRC byte */
    calculateCrc = Crc_CalculateCRC8H2F( \
      (P2CONST(uint8, AUTOMATIC, E2E_CONST)) & \
      (ConfigPtr->DataIDList[StatePtr->Counter]), \
      (uint32)0x01U, calculateCrc, FALSE);

    DataPtr[0x00U] = calculateCrc;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P02Check                                        **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This function shall check counter, CRC over         **
**                        received Data and determine the check status.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          ** 
                          DataPtr:                                            **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state. **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType:                                     **
**                        E2E_E_INPUTERR_NULL                                 **
**                        E2E_E_INPUTERR_WRONG                                **
**                        E2E_E_INTERR                                        **
**                        E2E_E_OK                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_P02CheckParams         **
**                                                 Crc_CalculateCRC8H2F       **
**                                                 E2E_P02CheckStatus         **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P02Check (
  P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to store counter value */
  VAR(uint8, AUTOMATIC) counterValue;
  /* Local variable to store calculated CRC  */
  VAR(uint8, AUTOMATIC) calculateCrc;
  /* Local variable to store data length  */
  VAR(uint16, AUTOMATIC) dataLength;

  /* @Trace: SafeE2E_SUD_MF_102 */    
  /* Check for the invalid input parameters */
  if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  else if((ConfigPtr->DataLength / 0x0008U) < 0x01U)
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else
  {
    returnValue = E2E_P02CheckParams(ConfigPtr);
  }

  /* @Trace: SafeE2E_SUD_MF_103 */
  if (E2E_E_OK == returnValue)
  {
    
    if (E2E_P02_CNT_MAX > StatePtr->MaxDeltaCounter)
    {
      StatePtr->MaxDeltaCounter++;
    }
    if (TRUE == StatePtr->NewDataAvailable)
    {
      /* polyspace +2 DEFECT:OUT_BOUND_PTR MISRA2012:18.1 CERT-C:MEM35-C,ARR30-C  [Justified:Low] "Pointer at index is checked before access." */
      /* Get the counter value from the Received DataPtr bytes */      
      counterValue = (DataPtr[0x01U] & E2E_LOW_NIBBLE_MASK);
      
      /*
        * Calculate the CRC for the DataPtr and the counter and update the
        * CRC byte
        */
      
      dataLength = ConfigPtr->DataLength / 0x0008U;      

      calculateCrc = Crc_CalculateCRC8H2F( \
          (P2CONST(uint8, AUTOMATIC, E2E_CONST)) & DataPtr[0x01U], \
          (uint32)((uint32)dataLength - (uint32)0x01U), \
          E2E_P02_CRC_INIT_VALUE, TRUE);

      /* Calculate the CRC for the DataId and update the CRC byte */
      calculateCrc = Crc_CalculateCRC8H2F( \
          (P2CONST(uint8, AUTOMATIC, E2E_CONST)) & \
          (ConfigPtr->DataIDList[counterValue]), \
          (uint32)0x01U, calculateCrc, FALSE);

      /*
        * check the CRC present in the Received DataPtr and 
        * the calculated CRC are equal
        */
      if (DataPtr[0x00U] == calculateCrc)
      {
        E2E_P02CheckStatus(ConfigPtr, StatePtr, counterValue);
      }
      else
      {
        /* 
          *	Update the status to indicate the received DataPtr is not correct */
        StatePtr->Status = E2E_P02STATUS_WRONGCRC;
      }
    }
    else
    {
      /* Update the status to indicate that the there are no new DataPtr */
      if (StatePtr->NoNewOrRepeatedDataCounter < E2E_P02_CNT_MAX)
      {
        StatePtr->NoNewOrRepeatedDataCounter++;
      }
      StatePtr->Status = E2E_P02STATUS_NONEWDATA;
    }
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P02ProtectInit                                  **
**                                                                            **
** Service ID           : 0x1E                                                **
**                                                                            **
** Description          : This function shall initializes the protection      **
**                        State.                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state. **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType:                                     **
**                        E2E_E_INPUTERR_NULL - null pointer passed           **
**                        E2E_E_OK                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02ProtectInit(
    P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;

  /* @Trace: SafeE2E_SUD_MF_104 */
  /* Check for the invalid input parameters */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    /* Set Counter to 0 */
    StatePtr->Counter = 0x00U;
    
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P02CheckInit                                    **
**                                                                            **
** Service ID           : 0x1F                                                **
**                                                                            **
** Description          : This function shall initializes the check State.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : StatePtr                                            **
**                                                                            **
** Output Parameters    : StatePtr: Pointer to port/data communication state. **
**                                                                            **
** Return value         : Std_ReturnType:                                     **
**                        E2E_E_INPUTERR_NULL - null pointer passed           **
**                        E2E_E_OK                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02CheckInit(
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;

  /* @Trace: SafeE2E_SUD_MF_105 */
  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    /*Initialize the state structure*/
    StatePtr->LastValidCounter = 0x00U;
    StatePtr->MaxDeltaCounter = 0x00U;
    StatePtr->WaitForFirstData = TRUE;
    StatePtr->NewDataAvailable = TRUE;
    StatePtr->LostData = 0x00U;
    StatePtr->Status = E2E_P02STATUS_NONEWDATA;
    StatePtr->NoNewOrRepeatedDataCounter = 0x00U;
    StatePtr->SyncCounter = 0x00U;
    
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P02MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 2 to a generic check status, which can be   **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 2 delivers a more fine-granular status, but **
**                        this is not relevant for the E2E state machine.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CheckReturn, Status                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : E2E_PCheckStatusType                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P02MapStatusToSM(
    VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
    VAR(E2E_P02CheckStatusType, AUTOMATIC) Status,
    VAR(boolean, AUTOMATIC) ProfileBehavior)
{
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) returnValue;

  /* @Trace: SafeE2E_SUD_MF_106 */
  /* Verify inputs of the protect function */
  if (E2E_E_OK != CheckReturn)
  {
    returnValue = E2E_P_ERROR;
  }
  else
  {
    switch (Status)
    {
      case E2E_P02STATUS_OK: /* walk through */
      case E2E_P02STATUS_OKSOMELOST:
        returnValue = E2E_P_OK;
        break;
      case E2E_P02STATUS_SYNC:
      {
        if (TRUE == ProfileBehavior)
        {
          returnValue = E2E_P_OK;
        }
        else
        {
          returnValue = E2E_P_WRONGSEQUENCE;
        }
        break;
      }
      case E2E_P02STATUS_WRONGCRC:
        returnValue = E2E_P_ERROR;
        break;
      case E2E_P02STATUS_NONEWDATA:
        returnValue = E2E_P_NONEWDATA;
        break;
      case E2E_P02STATUS_REPEATED:
        returnValue = E2E_P_REPEATED;
        break;
      case E2E_P02STATUS_WRONGSEQUENCE:
        returnValue = E2E_P_WRONGSEQUENCE;
        break;

      case E2E_P02STATUS_INITIAL:
      {
        if (TRUE == ProfileBehavior)
        {
          returnValue = E2E_P_WRONGSEQUENCE;
        }
        else
        {
          returnValue = E2E_P_OK;
        }
        break;
      }
      default:
        returnValue = E2E_P_ERROR;
        break;
    }
  }
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P02CheckStatus                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function check status of received Data.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Counter, ConfigPtr                                  **
**                                                                            **
** InOut Parameters     : StatePtr                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
static FUNC(void,E2E_CODE) E2E_P02CheckStatus(
    P2CONST(E2E_P02ConfigType,AUTOMATIC,E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    VAR(uint8, AUTOMATIC) ReceivedCounterVal)
{
  /* Local variable to store delta counter */
  VAR(uint8, AUTOMATIC) deltaCounter;

  /* Check whether the DataPtr received is the first DataPtr */
  if (TRUE == StatePtr->WaitForFirstData)
  {
    /* Change the status of the first DataPtr flag to FALSE */
    StatePtr->WaitForFirstData = FALSE;

    /* Reset the MaxDeltaCounter */
    StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;

    /* 
    *	Update the LastValidCounter with the currently 
    * received counter values */
    StatePtr->LastValidCounter = ReceivedCounterVal;

    /* Set the status to E2E_P02STATUS_INITIAL */
    StatePtr->Status = E2E_P02STATUS_INITIAL;
  }
  else
  {

    /* @Trace: SafeE2E_SUD_MF_108 */
    /*
      * Find the difference in counter value from the received one and the
      * last valid counter received
      */
    if (ReceivedCounterVal >= (StatePtr->LastValidCounter))
    {
      deltaCounter = ReceivedCounterVal - (StatePtr->LastValidCounter);
    }
    else
    {
      deltaCounter =
        (E2E_P02_CNT_LIMIT + ReceivedCounterVal) - (StatePtr->LastValidCounter);
    }

    /*
      * If there are no difference in counter value then the DataPtr is
      * repeated
      */
    if (0x00U == deltaCounter)
    {
      /* Increment NoNewOrRepeatedDataCounter */
      if (E2E_P02_CNT_MAX > StatePtr->NoNewOrRepeatedDataCounter)
      {
        StatePtr->NoNewOrRepeatedDataCounter++;
      }

      StatePtr->Status = E2E_P02STATUS_REPEATED;
    }
    /* If the difference is one then a new DataPtr is avaialble */
    else if (0x01U == deltaCounter)
    {

      /* Reset the Delta counter */
      StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;

      /* Update the last valid counter with the current counter value */
      StatePtr->LastValidCounter = ReceivedCounterVal;

      /* Update the lost DataPtr count to Zero */
      StatePtr->LostData = 0x00U;

      if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData)
      {
        StatePtr->NoNewOrRepeatedDataCounter = E2E_P02_CNT_MIN;

        if (0x00U < StatePtr->SyncCounter)
        {
          StatePtr->SyncCounter--;
          /* Set the status to E2E_P02STATUS_SYNC */
          StatePtr->Status = E2E_P02STATUS_SYNC;
        }
        else
        {
          /* Set the status to E2E_P02STATUS_OK */
          StatePtr->Status = E2E_P02STATUS_OK;
        }
      }
      else
      {
        StatePtr->NoNewOrRepeatedDataCounter = E2E_P02_CNT_MIN;
        StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
        StatePtr->Status = E2E_P02STATUS_SYNC;
      }
    }
    /* If the difference is more than ONE then some DataPtr is lost */
    else if (deltaCounter <= StatePtr->MaxDeltaCounter)
    {
      /* Reset the Delta counter */
      StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;

      /* Update the last valid counter with the current counter value */
      StatePtr->LastValidCounter = ReceivedCounterVal;

      /* Update the lost DataPtr count */
      StatePtr->LostData = deltaCounter - 0x01U;

      if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData)
      {
        StatePtr->NoNewOrRepeatedDataCounter = E2E_P02_CNT_MIN;

        if (0x00U < StatePtr->SyncCounter)
        {
          StatePtr->SyncCounter--;
          /* Set the status to E2E_P02STATUS_SYNC */
          StatePtr->Status = E2E_P02STATUS_SYNC;
        }
        else
        {
          /* Set the status to E2E_P02STATUS_OKSOMELOST*/
          StatePtr->Status = E2E_P02STATUS_OKSOMELOST;
        }
      }
      else
      {
        StatePtr->NoNewOrRepeatedDataCounter = E2E_P02_CNT_MIN;
        StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
        StatePtr->Status = E2E_P02STATUS_SYNC;
      }
    }
    /* Check If the difference is more than the allowed value */
    else
    {
      StatePtr->NoNewOrRepeatedDataCounter = 0x00U;
      StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
      if (0x00U < StatePtr->SyncCounter)
      {
        StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
        StatePtr->LastValidCounter = ReceivedCounterVal;
      }
      /* 
      * Update the status to indicate that 
      * the DataPtr sequence is not correct */
      StatePtr->Status = E2E_P02STATUS_WRONGSEQUENCE;
    }
  }
}
    
#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
