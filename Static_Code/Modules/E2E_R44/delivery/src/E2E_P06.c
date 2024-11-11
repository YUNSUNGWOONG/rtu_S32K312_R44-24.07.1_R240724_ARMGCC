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
**  SRC-MODULE: E2E_P06.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 6 driver            **
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
** 1.0.1    28-Dec-2021    HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include file for Profile 6 implementation */
#include "E2E.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Internal Function Declarations                        **
*******************************************************************************/

static FUNC(uint16, E2E_CODE) E2E_P06CalculateCRC(
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length);

static FUNC(void, E2E_CODE) E2E_P06CheckStatus(
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  VAR(boolean, AUTOMATIC) NewDataAvailable,
  VAR(boolean, AUTOMATIC) IsCorrectData,
  VAR(uint8, AUTOMATIC) Counter);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P06ProtectInit                                  **
**                                                                            **
** Service ID           : 0x2c                                                **
**                                                                            **
** Description          : Initializes the protection state                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
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
/* @Trace:  SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */

FUNC(Std_ReturnType, E2E_CODE) E2E_P06ProtectInit(
  P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_407 */
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  returnValue = E2E_E_OK;
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  /* Check for the invalid input parameters */
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    StatePtr->Counter = 0x00U; 
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P06CheckInit                                    **
**                                                                            **
** Service ID           : 0x2e                                                **
**                                                                            **
** Description          : Initializes the check state                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckInit(
  P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_402 */
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;
  /* Check for the invalid input parameters */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    
    StatePtr->Counter = E2E_P06_CNT_MAX;
    StatePtr->Status = E2E_P06STATUS_ERROR;
    
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P06MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x2f                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 6 to a generic check status, which can be   **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 6 delivers a more fine-granular status, but **
**                        this is not relevant for the E2E state machine.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CheckReturn: Return value of E2E_P06Check function  **
**                        Status: Status determined by E2E_P06Check function  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : E2E_PCheckStatusType: Profile-independent status    **
**                        of the reception on one single Data in one cycle    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */

FUNC(E2E_PCheckStatusType, AUTOMATIC) E2E_P06MapStatusToSM(
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P06CheckStatusType, AUTOMATIC) Status)
{
  /* @Trace: SafeE2E_SUD_MF_403 */
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) returnValue;

  returnValue = E2E_P_ERROR;

  if (E2E_E_OK == CheckReturn)
  {
    switch (Status)
    {
      case E2E_P06STATUS_OK: /* walk through */
      case E2E_P06STATUS_OKSOMELOST:
        returnValue = E2E_P_OK;
        break;

      case E2E_P06STATUS_ERROR:
        returnValue = E2E_P_ERROR;
        break;

      case E2E_P06STATUS_REPEATED:
        returnValue = E2E_P_REPEATED;
        break;

      case E2E_P06STATUS_NONEWDATA:
        returnValue = E2E_P_NONEWDATA;
        break;

      case E2E_P06STATUS_WRONGSEQUENCE:
        returnValue = E2E_P_WRONGSEQUENCE;
        break;

      default:
        returnValue = E2E_P_ERROR;
        break;
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P06Protect                                      **
**                                                                            **
** Service ID           : 0x2b                                                **
**                                                                            **
** Description          : Protects the array/buffer to be transmitted using   **
**                        the E2E profile 6. This includes checksum           **
**                        calculation, handling of counter and Data ID.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                        Length: Length of the data in bytes.                **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state  **
**                        DataPtr: Pointer to Data to be transmitted          **
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
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/

FUNC(Std_ReturnType, AUTOMATIC) E2E_P06Protect(
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offset;
  /* Local variable to store crc value */
  VAR(uint16, AUTOMATIC) crcValue;
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;

  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || \
      (NULL_PTR == DataPtr))
  /* @Trace: SafeE2E_SUD_MF_404 */
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  /* Check for the invalid input parameters SWS_E2E_00441
    1. The offset shall be a multiple of 8 and 0 <= Offset <= MaxDataLength-(5*8).
    2. Length is >= MinDataLength. The MinDataLength value shall be <= 4096*8 (4kB) and shall be => 5*8.
    3. The MaxDataLength shall be <= 4096*8 (4kB).
  */
  else if ((ConfigPtr->MinDataLength > (Length * 8U)) || \
          (ConfigPtr->MaxDataLength < (Length * 8U))  || \
          ((0x00U != (ConfigPtr->Offset % 0x08U)))  || \
          (E2E_P06_MIN_DATA_LENGTH_LIMIT > ConfigPtr->MinDataLength) || \
          (E2E_P06_MAX_DATA_LENGTH_LIMIT < ConfigPtr->MaxDataLength) || \
          (ConfigPtr->Offset > (ConfigPtr->MaxDataLength - E2E_P06_MIN_DATA_LENGTH_LIMIT)))
  /* @Trace: SafeE2E_SUD_MF_405 */
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else if (Length < ((ConfigPtr->Offset / 0x0008U) + E2E_P06_LEN_OFS_HIGH_BYTE))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else
  /* @Trace: SafeE2E_SUD_MF_406 */
  {
    /* Compute offset */
    offset = ConfigPtr->Offset / 0x08U;

    /* Write Length in big endian order */
    DataPtr[offset + E2E_P06_LEN_OFS_HIGH_BYTE] = \
      (uint8)((Length >> 0x08U) & E2E_LOW_BYTE_MASK);

    DataPtr[offset + E2E_P06_LEN_OFS_LOW_BYTE] = \
      (uint8)(Length & E2E_LOW_BYTE_MASK);

    /* Write Counter */
    DataPtr[offset + E2E_P06_CNT_OFS] = StatePtr->Counter;

    /* Compute CRC */
    crcValue = E2E_P06CalculateCRC( \
      ConfigPtr,(P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) DataPtr, Length);

    /* Write CRC in big endian order */
    DataPtr[offset] = \
      (uint8)((crcValue >> 0x08U) & E2E_LOW_BYTE_MASK);

    DataPtr[offset + E2E_P06_CRC_OFS_LOW_BYTE] = \
      (uint8)(crcValue & E2E_LOW_BYTE_MASK);

    /* Increment Counter */
    if(E2E_P06_CNT_MAX > StatePtr->Counter)
    {
      StatePtr->Counter++;
    }
    else
    {
      StatePtr->Counter = 0x00U;
    }
  } /* End of if-elseif-else */
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P06Check                                        **
**                                                                            **
** Service ID           : 0x2d                                                **
**                                                                            **
** Description          : Checks the Data received using the E2E profile 6    **
**                        This includes checksum calculation, handling of     **
**                        counter and Data ID.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                        DataPtr: Pointer to received data                   **
**                        Length: Length of the data in bytes                 **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state  **
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
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */

FUNC(Std_ReturnType, AUTOMATIC) E2E_P06Check(
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offset;
  /* Local variable to store calculated crc value */
  VAR(uint16, AUTOMATIC) calculatedCRC;
  /* Local variable to store calculated crc value */
  VAR(uint16, AUTOMATIC) receivedCRC;
  /* Local variable to store received crc value */
  VAR(uint16, AUTOMATIC) receivedLength;
  /* Local variable to store received counter value */
  VAR(uint8, AUTOMATIC) receivedCounter;
  /* Local variable to store flag check whether data is available */
  VAR(boolean, AUTOMATIC) newDataAvailable;
  /* Local variable to store flag check whether data is correct */
  VAR(boolean, AUTOMATIC) isCorrectData;
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  receivedCounter = 0x00U; 
  newDataAvailable = FALSE;
  isCorrectData = FALSE;
  returnValue = E2E_E_OK;

  /* Verify inputs of the check function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr))
  /* @Trace: SafeE2E_SUD_MF_401 */
  {
    /* Both data and length mean */
    if ((NULL_PTR == DataPtr) && (0x00U != Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((NULL_PTR != DataPtr) && (0x00U == Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((Length < ((ConfigPtr->Offset / 0x0008U) + E2E_P06_LEN_OFS_HIGH_BYTE)) && \
	  (Length != 0))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }	
    else
    {
      /* Change status to true when data is valid */
      if (NULL_PTR != DataPtr)
      {
        /* Check for the invalid input parameters SWS_E2E_00441
          1. The offset shall be a multiple of 8 and 0 <= Offset <= MaxDataLength-(5*8).
          2. Length is >= MinDataLength. The MinDataLength value shall be <= 4096*8 (4kB) and shall be => 5*8.
          3. The MaxDataLength shall be <= 4096*8 (4kB).
        */
        if  ((ConfigPtr->MinDataLength <= (Length * 8U)) && \
            (ConfigPtr->MaxDataLength >= (Length * 8U))  && \
            ((0x00U == (ConfigPtr->Offset % 0x08U)))  && \
            (E2E_P06_MIN_DATA_LENGTH_LIMIT <= ConfigPtr->MinDataLength) && \
            (E2E_P06_MAX_DATA_LENGTH_LIMIT >= ConfigPtr->MaxDataLength) && \
            (ConfigPtr->Offset <= (ConfigPtr->MaxDataLength - E2E_P06_MIN_DATA_LENGTH_LIMIT)))
        {
          /* Change data status */
          newDataAvailable = TRUE;

          /* Compute offset */
          offset = ConfigPtr->Offset / 0x08U;

          /* Read Length in big endian order */
          receivedLength = \
            (((uint16)(DataPtr[offset + E2E_P06_LEN_OFS_HIGH_BYTE]) << \
              0x08U) & E2E_HIGH_BYTE_MASK) | \
            ((uint16)(DataPtr[offset + E2E_P06_LEN_OFS_LOW_BYTE]) & \
              E2E_LOW_BYTE_MASK);
          
          /* Read Counter */
          receivedCounter = DataPtr[offset + E2E_P06_CNT_OFS];
          
          /* Compute CRC */
          receivedCRC = \
            (((uint16)(DataPtr[offset]) << \
              0x08U) & E2E_HIGH_BYTE_MASK) | \
            ((uint16)DataPtr[offset + E2E_P06_CRC_OFS_LOW_BYTE] & \
              E2E_LOW_BYTE_MASK);

          /* Calculate CRC */
          calculatedCRC = E2E_P06CalculateCRC(ConfigPtr, DataPtr, Length);

          /* Check received crc, data id, length is correct */
          if ((calculatedCRC == receivedCRC) && (receivedLength == Length))
          {
            isCorrectData = TRUE;
          }
          else
          {
            isCorrectData = FALSE;
          }

          /* Call function to check status */
          E2E_P06CheckStatus(ConfigPtr, StatePtr, newDataAvailable, \
            isCorrectData, receivedCounter);
        }
        else
        {
          returnValue = E2E_E_INPUTERR_WRONG;
        }
      }
      else
      {
        /* Call function to check status */
        E2E_P06CheckStatus(ConfigPtr, StatePtr, newDataAvailable, \
          isCorrectData, receivedCounter);
      }
    }
  }
  else
  /* @Trace: SafeE2E_SUD_MF_400 */
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P06CheckStatus                                  **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : Check status over received data                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                        StatePtr: Pointer to port/data communication state  **
**                        NewDataAvailable: new data is available             **
**                        IsCorrectData: Data contains correct header         **
**                        Counter: received counter                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */

static FUNC(void, E2E_CODE) E2E_P06CheckStatus(
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  VAR(boolean, AUTOMATIC) NewDataAvailable,
  VAR(boolean, AUTOMATIC) IsCorrectData,
  VAR(uint8, AUTOMATIC) Counter)
{
  /* @Trace: SafeE2E_SUD_MF_409 */
  /* Local variable to store delta counter */
  VAR(uint8, AUTOMATIC) deltaCounter;
  
  /* Check new data is available */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if(TRUE == NewDataAvailable)
  {
    /* Check data error */
    if(TRUE == IsCorrectData)
    {
      /* When the received counter is equal to greater than the previous cnt */
      if(Counter >= StatePtr->Counter)
      {
        deltaCounter = Counter - StatePtr->Counter;
      }
      else
      /* When the received counter is less than the previous counter */
      {
        deltaCounter = \
          ((E2E_P06_CNT_MAX - StatePtr->Counter) + Counter) + 0x01U;
      }

      /* Verify delta counter value */
      if (deltaCounter <= ConfigPtr->MaxDeltaCounter)
      {
        /* When delta counter is greater than 0 */
        if (0x00U < deltaCounter)
        {
          /* Delta counter is 1 */
          if (0x01U == deltaCounter)
          {
            StatePtr->Status = E2E_P06STATUS_OK;
          }
          else
          {
            StatePtr->Status = E2E_P06STATUS_OKSOMELOST;
          }
        }
        else
        {
          StatePtr->Status = E2E_P06STATUS_REPEATED;
        }
      }
      else
      {
        StatePtr->Status = E2E_P06STATUS_WRONGSEQUENCE;
      }

      /* Save counter value in previous cycle */
      StatePtr->Counter = Counter;
    }
    else
    {
      StatePtr->Status = E2E_P06STATUS_ERROR;
    }
  }
  else
  {
    StatePtr->Status = E2E_P06STATUS_NONEWDATA;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
}

/*******************************************************************************
** Function Name        : E2E_P06CalculateCRC                                 **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : Calculate CRC over received data                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                        DataPtr: Pointer to received data                   **
**                        Length: Length of the data in bytes                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/

static FUNC(uint16, E2E_CODE) E2E_P06CalculateCRC(
  P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length)
{
  /* @Trace: SafeE2E_SUD_MF_408 */
  /* Local variable to store result value */
  VAR(uint16, AUTOMATIC) crcValue = 0x0000U;
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offset;
  /* Local variable to store length data after Crc byte */
  VAR(uint16, AUTOMATIC) lengthAfterCrc = 0x0000U;
  /* Local variable to store high byte of data id */
  VAR(uint8, AUTOMATIC) dataIDHighByte;
  /* Local variable to store low byte of data id */
  VAR(uint8, AUTOMATIC) dataIDLowByte;

  /* Compute offset */
  offset = ConfigPtr->Offset / 0x08U;

  /* The validity of LengthForCRC has been checked before. Checking again just only for polyspace */
  if(Length > (offset + E2E_P06_LEN_OFS_HIGH_BYTE))
  {
    /* DataPtr length after the position where CRC value exist */
    lengthAfterCrc = (Length - offset) - E2E_P06_LEN_OFS_HIGH_BYTE;
  }

  /* When E2E header does not exist in the beginning of the data */
  if (0x00U < offset)
  {
    /* Calculate CRC before CRC position */
    crcValue = Crc_CalculateCRC16( \
      &DataPtr[0x00U], (uint32)offset, E2E_P06_CRC_START_VAL, TRUE);

    /* Calculate CRC after the CRC position */
    crcValue = Crc_CalculateCRC16( \
      &DataPtr[offset + E2E_P06_LEN_OFS_HIGH_BYTE], \
      (uint32)lengthAfterCrc, crcValue, FALSE);
  } 
  else
  {
    /* Calculate CRC for the CRC position */
    crcValue = Crc_CalculateCRC16( \
      &DataPtr[offset + E2E_P06_LEN_OFS_HIGH_BYTE], \
      (uint32)lengthAfterCrc, E2E_P06_CRC_START_VAL, TRUE);
  } /* End of else */

  /* Get the value of high byte of DataPtr ID */
  dataIDHighByte = \
    (uint8)(((ConfigPtr->DataID) >> 0x08U) & E2E_LOW_BYTE_MASK);

  /* Calculate CRC for high byte of DataPtr ID */
  crcValue = Crc_CalculateCRC16( \
    &dataIDHighByte, (uint32)0x01U, crcValue, FALSE);

  /* Get the value of low byte of DataPtr ID */
  dataIDLowByte = (uint8)(ConfigPtr->DataID & E2E_LOW_BYTE_MASK);

  /* Calculate CRC for low byte of DataPtr ID */
  crcValue = Crc_CalculateCRC16( \
    &dataIDLowByte, (uint32)0x01U, crcValue, FALSE);

  /* Return the result value of CRC calculation */
  return crcValue;
}

#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

