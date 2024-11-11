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
**  SRC-MODULE: E2E_P07.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 7 driver            **
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
** 1.0.1    28-Dec-2021    HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include file for Profile 7 implementation */
#include "E2E.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Internal Function Declarations                        **
*******************************************************************************/

static FUNC(uint64, E2E_CODE) E2E_P07CalculateCRC(
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint32, AUTOMATIC) Length);

static FUNC(void, E2E_CODE) E2E_P07CheckStatus(
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  VAR(boolean, AUTOMATIC) NewDataAvailable,
  VAR(boolean, AUTOMATIC) IsCorrectData,
  VAR(uint32, AUTOMATIC) Counter);

static FUNC(void, E2E_CODE) E2E_P07WriteEightByte(
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, 
  VAR(uint64, AUTOMATIC) Value,
  VAR(uint32, AUTOMATIC) StartOffset);

static FUNC(void, E2E_CODE) E2E_P07WriteFourByte(
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, 
  VAR(uint32, AUTOMATIC) Value,
  VAR(uint32, AUTOMATIC) StartOffset);

static FUNC(uint64, E2E_CODE) E2E_P07ReadEightByte(
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr, 
  VAR(uint32, AUTOMATIC) StartOffset);

static FUNC(uint32, E2E_CODE) E2E_P07ReadFourByte(
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr, 
  VAR(uint32, AUTOMATIC) StartOffset);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P07ProtectInit                                  **
**                                                                            **
** Service ID           : 0x22                                                **
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
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */

FUNC(Std_ReturnType, E2E_CODE) E2E_P07ProtectInit(
  P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_507 */
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
    StatePtr->Counter = 0x00U; 
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P07CheckInit                                    **
**                                                                            **
** Service ID           : 0x24                                                **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P07CheckInit(
  P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_502 */
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
    
    StatePtr->Counter = E2E_P07_CNT_MAX;
    StatePtr->Status = E2E_P07STATUS_ERROR;
    
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P07MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 7 to a generic check status, which can be   **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 7 delivers a more fine-granular status, but **
**                        this is not relevant for the E2E state machine.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CheckReturn: Return value of E2E_P07Check function  **
**                        Status: Status determined by E2E_P07Check function  **
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

FUNC(E2E_PCheckStatusType, AUTOMATIC) E2E_P07MapStatusToSM(
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P07CheckStatusType, AUTOMATIC) Status)
{
  /* @Trace: SafeE2E_SUD_MF_503 */
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) returnValue;
  
  returnValue = E2E_P_ERROR;

  if (E2E_E_OK == CheckReturn)
  {
    switch (Status)
    {
      case E2E_P07STATUS_OK: /* walk through*/
      case E2E_P07STATUS_OKSOMELOST:
        returnValue = E2E_P_OK;
        break;

      case E2E_P07STATUS_ERROR:
        returnValue = E2E_P_ERROR;
        break;

      case E2E_P07STATUS_REPEATED:
        returnValue = E2E_P_REPEATED;
        break;

      case E2E_P07STATUS_NONEWDATA:
        returnValue = E2E_P_NONEWDATA;
        break;

      case E2E_P07STATUS_WRONGSEQUENCE:
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
** Function Name        : E2E_P07Protect                                      **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : Protects the array/buffer to be transmitted using   **
**                        the E2E profile 7. This includes checksum           **
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

FUNC(Std_ReturnType, AUTOMATIC) E2E_P07Protect(
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint32, AUTOMATIC) Length)
{
  /* Local variable to store offset value */
  VAR(uint32, AUTOMATIC) offset;
  /* Local variable to store crc value */
  VAR(uint64, AUTOMATIC) crcValue;
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;

  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || \
      (NULL_PTR == DataPtr))
  /* @Trace: SafeE2E_SUD_MF_504 */
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  /* Check for the invalid input parameters SWS_E2E_00544 
    1. The offset shall be a multiple of 8 and 0 <= Offset <= MaxDataLength-(20*8).
    2. Length is>= MinDataLength. The MinDataLength value shall be>= 20*8 and <= MaxDataLength.
    3. that DataLength is <= MaxDataLength. The MaxDataLength value shall be>= MinDataLength.
  */
  else if ((ConfigPtr->MinDataLength > (Length * 8)) || \
           (ConfigPtr->MaxDataLength < (Length * 8)) || \
           ((0x00U != (ConfigPtr->Offset % 0x08U))) || \
           (E2E_P07_MIN_DATA_LENGTH_LIMIT > ConfigPtr->MinDataLength) || \
           (ConfigPtr->Offset > (ConfigPtr->MaxDataLength - E2E_P07_MIN_DATA_LENGTH_LIMIT)) || \
		   (Length < (((uint32)ConfigPtr->Offset / 0x0008U) + 0x08U)))
  /* @Trace: SafeE2E_SUD_MF_506 */
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else
  /* @Trace: SafeE2E_SUD_MF_505 */
  {
    /* Compute offset */
    offset = ConfigPtr->Offset / 0x08U;

    /* Write Length in big endian order */
    E2E_P07WriteFourByte(DataPtr, Length, offset + E2E_P07_LEN_OFS_BYTE_ONE);

    /* Write Counter in big endian order */
    E2E_P07WriteFourByte( \
      DataPtr, StatePtr->Counter, offset + E2E_P07_CNT_OFS_BYTE_ONE);

    /* Write DataID in big endian order */
    E2E_P07WriteFourByte( \
      DataPtr, ConfigPtr->DataID, offset + E2E_P07_DATAID_OFS_BYTE_ONE);

    /* Compute CRC */
    crcValue = E2E_P07CalculateCRC( \
      ConfigPtr, (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) DataPtr, Length);

    /* Write CRC in big endian order */
    E2E_P07WriteEightByte(DataPtr, crcValue, offset);

    /* Increment Counter */
    if(E2E_P07_CNT_MAX > StatePtr->Counter)
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
** Function Name        : E2E_P07Check                                        **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : Checks the Data received using the E2E profile 7    **
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

FUNC(Std_ReturnType, AUTOMATIC) E2E_P07Check(
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint32, AUTOMATIC) Length)
{
  /* Local variable to store offset value */
  VAR(uint32, AUTOMATIC) offset;
  /* Local variable to store received length value */
  VAR(uint32, AUTOMATIC) receivedLength;
  /* Local variable to store received data id value */
  VAR(uint32, AUTOMATIC) receivedDataID;
  /* Local variable to store received counter value */
  VAR(uint32, AUTOMATIC) receivedCounter;
  /* Local variable to store received crc value */
  VAR(uint64, AUTOMATIC) receivedCrc;
  /* Local variable to store calculated crc value */
  VAR(uint64, AUTOMATIC) calculatedCrc;
  /* Local variable to store flag check whether data is correct */
  VAR(boolean, AUTOMATIC) isCorrectData;
  /* Local variable to store flag check whether data is available */
  VAR(boolean, AUTOMATIC) newDataAvailable;
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  receivedCounter = 0x00U;
  isCorrectData = FALSE;
  newDataAvailable = FALSE;
  returnValue = E2E_E_OK;

  /* Verify inputs of the check function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr))
  /* @Trace: SafeE2E_SUD_MF_501 */
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
    else if ((Length < (((uint32)ConfigPtr->Offset / 0x0008U) + 0x08U)) && \
	  (Length != 0))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    } 	
    else
    {
      /* Check data is available */
      if (NULL_PTR != DataPtr)
      {
        /* Check for the invalid input parameters SWS_E2E_00544 
          1. The offset shall be a multiple of 8 and 0 <= Offset <= MaxDataLength-(20*8).
          2. Length is>= MinDataLength. The MinDataLength value shall be>= 20*8 and <= MaxDataLength.
          3. that DataLength is <= MaxDataLength. The MaxDataLength value shall be>= MinDataLength.
        */
        if ((ConfigPtr->MinDataLength <= (Length * 8)) && \
           (ConfigPtr->MaxDataLength >= (Length * 8)) && \
           ((0x00U == (ConfigPtr->Offset % 0x08U))) && \
           (E2E_P07_MIN_DATA_LENGTH_LIMIT <= ConfigPtr->MinDataLength) && \
           (ConfigPtr->Offset <= (ConfigPtr->MaxDataLength - E2E_P07_MIN_DATA_LENGTH_LIMIT)))
        {
          /* Change status to true when data is valid */
          newDataAvailable = TRUE;
          
          /* Compute offset */
          offset = ConfigPtr->Offset / 0x08U;

          /* Read Length in big endian order */
          receivedLength = \
            E2E_P07ReadFourByte(DataPtr, offset + E2E_P07_LEN_OFS_BYTE_ONE);
          
          /* Read Counter */
          receivedCounter = \
            E2E_P07ReadFourByte(DataPtr, offset + E2E_P07_CNT_OFS_BYTE_ONE);
          
          /* Compute DataID */
          receivedDataID = \
            E2E_P07ReadFourByte(DataPtr, offset + E2E_P07_DATAID_OFS_BYTE_ONE);
          
          /* Compute CRC */
          receivedCrc = \
            E2E_P07ReadEightByte(DataPtr, offset);

          /* Calculate CRC */
          calculatedCrc = E2E_P07CalculateCRC(ConfigPtr, DataPtr, Length);

          /* Check received crc, data id, length is correct */

          if ((calculatedCrc == receivedCrc) && (receivedLength == Length) &&
              (receivedDataID == ConfigPtr->DataID))
          {
            isCorrectData = TRUE;
          }
          else
          {
            isCorrectData = FALSE;
          }

          /* Call function to check status */
          E2E_P07CheckStatus(ConfigPtr, StatePtr, newDataAvailable, \
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
        E2E_P07CheckStatus(ConfigPtr, StatePtr, newDataAvailable, \
          isCorrectData, receivedCounter);
      }
    }
  }
  else
  /* @Trace: SafeE2E_SUD_MF_500 */
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P07CheckStatus                                  **
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
**                        Counter: received counter                           **
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

static FUNC(void, E2E_CODE) E2E_P07CheckStatus(
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  VAR(boolean, AUTOMATIC) NewDataAvailable,
  VAR(boolean, AUTOMATIC) IsCorrectData,
  VAR(uint32, AUTOMATIC) Counter)
{
  /* @Trace: SafeE2E_SUD_MF_509 */
  /* Local variable to store delta counter */
  VAR(uint32, AUTOMATIC) deltaCounter;

  /* Check data is available */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if(TRUE == NewDataAvailable)
  {
    /* Check data header: received crc, length, data id is correct */
    if(TRUE == IsCorrectData)
    {
      /* When the received counter is equal or greater than the previous cnt */
      if (Counter >= StatePtr->Counter)
      {
        deltaCounter = Counter - StatePtr->Counter;
      }
      else
      /* When the received counter is less than the previous counter */
      {
        deltaCounter = \
          ((E2E_P07_CNT_MAX - StatePtr->Counter) + Counter) + 0x01U;
      }

      /* Verify delta counter value */
      if (deltaCounter <= ConfigPtr->MaxDeltaCounter)
      {
        /* Delta counter is greater than 0 */
        if (0x00U < deltaCounter)
        {
          /* Delta counter is 1 */
          if (0x01U == deltaCounter)
          {
            StatePtr->Status = E2E_P07STATUS_OK;
          }
          else
          {
            StatePtr->Status = E2E_P07STATUS_OKSOMELOST;
          }
        }
        else
        {
          StatePtr->Status = E2E_P07STATUS_REPEATED;
        }
      }
      else
      {
        StatePtr->Status = E2E_P07STATUS_WRONGSEQUENCE;
      }

      /* Save counter value in previous cycle */
      StatePtr->Counter = Counter;
    }
    else
    {
      StatePtr->Status = E2E_P07STATUS_ERROR;
    }
  }
  else
  {
    StatePtr->Status = E2E_P07STATUS_NONEWDATA; 
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
}

/*******************************************************************************
** Function Name        : E2E_P07CalculateCRC                                 **
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
** Return value         : uint64                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */

static FUNC(uint64, E2E_CODE) E2E_P07CalculateCRC(
  P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint32, AUTOMATIC) Length)
{
  /* @Trace: SafeE2E_SUD_MF_508 */
  /* Local variable to store offset value */
  VAR(uint32, AUTOMATIC) offset;
  /* Local variable to store length data after Crc byte */
  VAR(uint32, AUTOMATIC) lengthAfterCrc = 0x00000000U;
  /* Local variable to store crc value */
  VAR(uint64, AUTOMATIC) crcValue;

  crcValue = E2E_P07_CRC_START_VAL;

  /* Compute offset */
  offset = ConfigPtr->Offset / 0x08U;
  
  /* The validity of LengthForCRC has been checked before. Checking again just only for polyspace */
  if(Length > (offset + 0x08U))
  {  
    /* Compute length of input after crc */
    lengthAfterCrc = Length - offset - 0x08U;
  }

  /* Check offset is  */
  if (0x00U < offset)
  {
    /* Calculate CRC before CRC position */
    crcValue = Crc_CalculateCRC64( \
      &DataPtr[0x00U], offset, E2E_P07_CRC_START_VAL, TRUE);
  } 
  
  /* Compute crc over bytes that are after crc */
  crcValue = Crc_CalculateCRC64( \
    &DataPtr[offset + 0x08U], lengthAfterCrc, crcValue, FALSE);

  return crcValue;
}

/*******************************************************************************
** Function Name        : E2E_P07WriteFourByte                                **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : Write four byte from value to data                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DataPtr: Pointer to received data                   **
**                        Value: value shall write to data                    **
**                        StartOffset: start offset in data                   **
**                                                                            **
** InOut Parameters     : DataPtr: Pointer to received data                   **
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

static FUNC(void, E2E_CODE) E2E_P07WriteFourByte(
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, 
  VAR(uint32, AUTOMATIC) Value,
  VAR(uint32, AUTOMATIC) StartOffset)
{
  /* @Trace: SafeE2E_SUD_MF_513 */
  /* Local variable to store index byte of array data */
  VAR(uint8, AUTOMATIC) idx;
  /* Local variable to store shift value that is used to get byte in array */
  VAR(uint8, AUTOMATIC) shiftValue;

  for(idx = 0x00U; idx < E2E_P07_FOUR_BYTE; idx++)
  {
    /* Calculate shift value to get 1 byte in 4 byte value */
    shiftValue = (0x03U - idx) << 0x03U;
    /* Write 1 byte to data pointer */
    /* polyspace-begin RTE:IDP MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Size of DataPtr is reprented in Length input prarmeter of API is assured by caller for valid range" */
    DataPtr[StartOffset + idx] = (uint8)(Value >> shiftValue);
    /* polyspace-end RTE:IDP MISRA-C3:D4.1 MISRA-C3:18.1 */
  }
}

/*******************************************************************************
** Function Name        : E2E_P07WriteEightByte                               **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : Write eight byte from value to data                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DataPtr: Pointer to received data                   **
**                        Value: value shall write to data                    **
**                        StartOffset: start offset in data                   **
**                                                                            **
** InOut Parameters     : DataPtr: Pointer to received data                   **
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

static FUNC(void, E2E_CODE) E2E_P07WriteEightByte(
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, 
  VAR(uint64, AUTOMATIC) Value,
  VAR(uint32, AUTOMATIC) StartOffset)
{
  /* @Trace: SafeE2E_SUD_MF_512 */
  /* Local variable to store index byte of array data */
  VAR(uint8, AUTOMATIC) idx;
  /* Local variable to store shift value that is used to get byte in array */
  VAR(uint8, AUTOMATIC) shiftValue;

  for(idx = 0x00U; idx < E2E_P07_EIGHT_BYTE; idx++)
  {
    /* Calculate shift value to get 1 byte in 8 byte value */
    shiftValue = (0x07U - idx) << 0x03U;
    /* Write 1 byte to data pointer */
    DataPtr[StartOffset + idx] = (uint8)(Value >> shiftValue);
  }
}

/*******************************************************************************
** Function Name        : E2E_P07ReadFourByte                                 **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : Read four  byte from data                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DataPtr: Pointer to received data                   **
**                        StartOffset: start offset in data                   **
**                                                                            **
** InOut Parameters     : none                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

static FUNC(uint32, E2E_CODE) E2E_P07ReadFourByte(
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint32, AUTOMATIC) StartOffset)
{
  /* @Trace: SafeE2E_SUD_MF_511 */
  /* Local variable to store return value */
  VAR(uint32, AUTOMATIC) returnValue;
  /* Local variable to store index byte of array data */
  VAR(uint8, AUTOMATIC) idx;
  /* Local variable to store shift value that is used to get byte in array */
  VAR(uint8, AUTOMATIC) shiftValue;

  returnValue = 0x00U;

  for(idx = 0x00U; idx < E2E_P07_FOUR_BYTE; idx++)
  {
    /* Calculate shift value to get 1 byte in 4 byte value */
    shiftValue = (0x03U - idx) << 0x03U;
    /* Add 1 byte in data pointer to returnValue */
    /* polyspace-begin RTE:IDP MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "Size of DataPtr is reprented in Length input prarmeter of API is assured by caller for valid range" */
    returnValue = returnValue | \
      ((uint32)(DataPtr[StartOffset + idx]) << shiftValue);
    /* polyspace-end RTE:IDP MISRA-C3:D4.1 MISRA-C3:18.1*/
  }
  
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P07ReadEightByte                                **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : Read eight byte from data                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DataPtr: Pointer to received data                   **
**                        StartOffset: start offset in data                   **
**                                                                            **
** InOut Parameters     : none                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : uint64                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

static FUNC(uint64, E2E_CODE) E2E_P07ReadEightByte(
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint32, AUTOMATIC) StartOffset)
{
  /* @Trace: SafeE2E_SUD_MF_510 */
  /* Local variable to store return value */
  VAR(uint64, AUTOMATIC) returnValue;
  /* Local variable to store index byte of array data */
  VAR(uint8, AUTOMATIC) idx;
  /* Local variable to store shift value that is used to get byte in array */
  VAR(uint8, AUTOMATIC) shiftValue;

  returnValue = 0x00U;

  for(idx = 0x00U; idx < E2E_P07_EIGHT_BYTE; idx++)
  {
    /* Calculate shift value to get 1 byte in 8 byte value */
    shiftValue = (0x07U - idx) << 0x03U;
    /* Add 1 byte in data pointer to returnValue */
    returnValue = returnValue | \
      ((uint64)(DataPtr[StartOffset + idx]) << shiftValue);
  }

  return returnValue;
}

#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
