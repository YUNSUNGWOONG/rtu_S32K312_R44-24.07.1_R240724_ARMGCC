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
**  SRC-MODULE: E2E_P05.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 5 driver            **
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
** 0.0.1    05-Sep-2019    CuongLX         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
** 0.0.3    01-Oct-2020    MinhNQ26        Fix code review comments (#15965)  **
** 1.0.1    28-Dec-2021    HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include file for StatePtr Machine implementation */
#include "E2E.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

static FUNC(uint16, E2E_CODE) E2E_P05CalculateCRC(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
    VAR(uint16, AUTOMATIC) Length);

static FUNC(void, E2E_CODE) E2E_P05CheckStatus(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    VAR(boolean, AUTOMATIC) NewDataAvailable,
    VAR(boolean, AUTOMATIC) IsCorrectCRC,
    VAR(uint8, AUTOMATIC) Counter);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P05Protect                                      **
**                                                                            **
** Service ID           : 0x26                                                **
**                                                                            **
** Description          : This function shall write counter in Data,and       **
**                        finally compute CRC over DataID and Data and write  **
**                        CRC in Data. And then it shall increment the        **
**                        counter.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr, Length                                   **
**                                                                            **
** InOut Parameters     : StatePtr, DataPtr                                   **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_P05CalculateCRC        **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P05Protect(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offset;
  /* Local variable to store Crc value */
  VAR(uint16, AUTOMATIC) crcValue;

  returnValue = E2E_E_OK;
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  /* Verify inputs of the protect function */
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr) && \
      (NULL_PTR != DataPtr))
  {
      /* check correct for value of Length data 
        1. The offset shall be a multiple of 8 and 0 <= Offset <= DataLength-(3*8).
        2. The dataLength shall be <= 4096*8 (4kB) and shall be>= 3*8.
      */
    if ((ConfigPtr->DataLength == (Length*8)) && \
        (E2E_P05_MIN_DATA_LENGTH_LIMIT <= ConfigPtr->DataLength) && \
        (E2E_P05_MAX_DATA_LENGTH_LIMIT >= ConfigPtr->DataLength) && \
        ((ConfigPtr->Offset % 8U) == 0) && \
        (ConfigPtr->Offset <= (ConfigPtr->DataLength - E2E_P05_MIN_DATA_LENGTH_LIMIT)))
    
    /* @Trace: SafeE2E_SUD_MF_300 SafeE2E_SUD_MF_301*/
    {
      /* Compute offset */
      offset = ConfigPtr->Offset / 0x08U;

      /* Write Counter */
      DataPtr[offset + E2E_P05_CNT_OFS] = StatePtr->Counter;

      /* Compute CRC */
      crcValue = E2E_P05CalculateCRC(ConfigPtr, \
        (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST))DataPtr, Length);

      /* Write CRC in little endian order */
      DataPtr[offset + E2E_P05_CRC_OFS_HIGH_BYTE] = \
        (uint8)((crcValue >> 0x08U) & E2E_LOW_BYTE_MASK);

      DataPtr[offset] = \
        (uint8)(crcValue & E2E_LOW_BYTE_MASK);

      /* Increment Counter */
      StatePtr->Counter++;
    }

    /* @Trace: SafeE2E_SUD_MF_302 */
    else
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
  }
  /* @Trace: SafeE2E_SUD_MF_300 */
  else
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P05ProtectInit                                  **
**                                                                            **
** Service ID           : 0x27                                                **
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
** InOut Parameters     : StatePtr                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05ProtectInit(
    P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;

  /* @Trace: SafeE2E_SUD_MF_303 */
  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    /* Set Counter to 0 */
    
    StatePtr->Counter = 0x00U;
    
  } /* End of if-else */
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P05Check                                        **
**                                                                            **
** Service ID           : 0x28                                                **
**                                                                            **
** Description          : This function shall check counter, CRC over         **
**                        received Data and determine the check status.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr, DataPtr, Length                          **
**                                                                            **
** InOut Parameters     : StatePtr                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_P05CalculateCRC        **
**                                                 E2E_P05CheckStatus         **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05Check(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
    /* Local variable to store return value */
    VAR(Std_ReturnType, AUTOMATIC) returnValue;
    /* Local variable to store received counter value */
    VAR(uint8, AUTOMATIC) rcvdCntrVal;
    /* Local variable to store offset value */
    VAR(uint16, AUTOMATIC) offset;
    /* Local variable to store the high bytes of CRC value on received DataPtr */
    VAR(uint16, AUTOMATIC) rcvdCrcHighByteVal;
     /* Local variable to store low bytes of CRC value on received DataPtr */
    VAR(uint16, AUTOMATIC) rcvdCrcLowByteVal;
    /* Local variable to store received crc value */
    VAR(uint16, AUTOMATIC) rcvdCrcVal;
    /* Local variable to store calculated value */
    VAR(uint16, AUTOMATIC) cptdCrcVal;
    /* Local variable to store flag check whether data is available */
    VAR(boolean, AUTOMATIC) newDataAvailable;

    /* @Trace: SafeE2E_SUD_MF_304 */
    /* Set new DataPtr available to False */
    newDataAvailable = FALSE;
    rcvdCntrVal = 0x00U;
    returnValue = E2E_E_OK;

    /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
    /* Verify inputs of the check function */
    if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr))
    {
      returnValue = E2E_E_INPUTERR_NULL;
    }
    else if ((NULL_PTR == DataPtr) && (0x00U != Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((NULL_PTR != DataPtr) && (0x00U == Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((Length < ((ConfigPtr->Offset / 0x0008U) + E2E_P05_CNT_OFS)) && \
	  (Length != 0))
	{
      returnValue = E2E_E_INPUTERR_WRONG;
    }	
    else if (NULL_PTR != DataPtr)
    { 
      /* check correct for value of Length data 
        1. The offset shall be a multiple of 8 and 0 <= Offset <= DataLength-(3*8).
        2. The dataLength shall be <= 4096*8 (4kB) and shall be>= 3*8.
      */
      if ((ConfigPtr->DataLength != (Length * 8)) || \
          (E2E_P05_MIN_DATA_LENGTH_LIMIT > ConfigPtr->DataLength) || \
          (E2E_P05_MAX_DATA_LENGTH_LIMIT < ConfigPtr->DataLength) || \
          ((ConfigPtr->Offset % 8U) != 0) || \
          (ConfigPtr->Offset > (ConfigPtr->DataLength - E2E_P05_MIN_DATA_LENGTH_LIMIT)))
      {
        returnValue = E2E_E_INPUTERR_WRONG;
      }
      else
      {
        newDataAvailable = TRUE;
      }
    }
    else
    {
        
    }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

    /* @Trace: SafeE2E_SUD_MF_305 */
    if (TRUE == newDataAvailable)
    {
      /* Compute offset */
      offset = (ConfigPtr->Offset) / 0x08U;

      /* Read Counter */
      rcvdCntrVal = DataPtr[offset + E2E_P05_CNT_OFS];

      /* Read CRC */

      /* Get the high byte of CRC value on the received DataPtr */
      rcvdCrcHighByteVal =  \
        ((uint16)(DataPtr[offset + E2E_P05_CRC_OFS_HIGH_BYTE])) << 0x08U;

      /* Get the low byte of CRC value on the received DataPtr */
      rcvdCrcLowByteVal = (uint16)(DataPtr[offset]);

      /* 
       * Get the CRC value from high and low byte of CRC position on received 
       * DataPtr 
       */
      rcvdCrcVal = (rcvdCrcHighByteVal & E2E_HIGH_BYTE_MASK) | \
        (rcvdCrcLowByteVal & E2E_LOW_BYTE_MASK);

      /* Compute CRC */
      cptdCrcVal = E2E_P05CalculateCRC(ConfigPtr, DataPtr, Length);

      /* Do checks */
      if (rcvdCrcVal != cptdCrcVal)
      {
        E2E_P05CheckStatus(ConfigPtr, StatePtr, newDataAvailable, \
          FALSE, rcvdCntrVal);
      }
      else
      {
        E2E_P05CheckStatus(ConfigPtr, StatePtr, newDataAvailable, \
          TRUE, rcvdCntrVal);
      }
    }
    else
    {
      if(E2E_E_OK == returnValue)
      {
        E2E_P05CheckStatus(ConfigPtr, StatePtr, newDataAvailable, FALSE, \
          rcvdCntrVal);
      }  
    }

    return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P05CheckInit                                    **
**                                                                            **
** Service ID           : 0x29                                                **
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
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05CheckInit (
  P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  returnValue = E2E_E_OK;

  /* @Trace: SafeE2E_SUD_MF_306 */
  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    /* Set Counter to 0xFF */
    
    StatePtr->Counter = E2E_P05_CNT_MAX;

    /* Set Status to E2E_P05STATUS_ERROR */
    StatePtr->Status = E2E_P05STATUS_ERROR;
    
  } /* End of if-else */
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P05MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x2a                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 5 to a generic check status, which can be   **
**                        used by E2E State machine check function. The E2E   **
**                        Profile 5 delivers a more fine-granular status, but **
**                        this is not relevant for the E2E State machine.     **
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
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P05MapStatusToSM (
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P05CheckStatusType, AUTOMATIC) Status)
{
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) checkStatus;
  
  /* @Trace: SafeE2E_SUD_MF_307 */
  /* Verify inputs of the protect function */
  if (E2E_E_OK != CheckReturn)
  {
    checkStatus = E2E_P_ERROR;
  }
  else
  {
    switch (Status)
    {
      case E2E_P05STATUS_OK: /* walk through */
      case E2E_P05STATUS_OKSOMELOST:
        checkStatus = E2E_P_OK;
        break;
        
      case E2E_P05STATUS_ERROR:
        checkStatus = E2E_P_ERROR;
        break;
        
      case E2E_P05STATUS_REPEATED:
        checkStatus = E2E_P_REPEATED;
        break;
        
      case E2E_P05STATUS_NONEWDATA:
        checkStatus = E2E_P_NONEWDATA;
        break;
        
      case E2E_P05STATUS_WRONGSEQUENCE:
        checkStatus = E2E_P_WRONGSEQUENCE;
        break;
        
      default:
        checkStatus = E2E_P_ERROR;
        break;
    }
  } /* End of if-else */
  
  return checkStatus;
} 

/*******************************************************************************
** Function Name        : E2E_P05CalculateCRC                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function calculate CRC over received Data.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr, DataPtr, Length                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : Crc_CalculateCRC16         **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
static FUNC(uint16, E2E_CODE) E2E_P05CalculateCRC(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store crc value */
  VAR(uint16, AUTOMATIC) crcValue = 0x0000U;
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offset;
  /* Local variable to store length data after Crc byte */
  VAR(uint16, AUTOMATIC) lengthAftCrc;
  /* Local variable to store high byte value of DataPtr ID*/
  VAR(uint8, AUTOMATIC) dataIDHighByte;
  /* Local variable to store low byte value of DataPtr ID*/
  VAR(uint8, AUTOMATIC) dataIDLowByte;

  /* @Trace: SafeE2E_SUD_MF_308 */
  /* Compute offset */
  offset = ConfigPtr->Offset / 0x08U;

  /* The validity of LengthForCRC has been checked before. Checking again just only for polyspace */

  /* DataPtr length after the position where CRC value exist */
  lengthAftCrc = (Length - offset) - E2E_P05_CNT_OFS;


  /* when E2E header does not exist in the beginning of the DataPtr */
  if (0x00U < offset)
  {
    /* calculate CRC before CRC position */
    crcValue = Crc_CalculateCRC16(&DataPtr[0x00U], (uint32)offset, \
       E2E_P05_CRC_START_VAL, TRUE);

    /* calculate CRC after the CRC position */
    crcValue = Crc_CalculateCRC16(&DataPtr[offset + E2E_P05_CNT_OFS], \
      (uint32)lengthAftCrc, crcValue, FALSE);
  } /* End of if  */
  else
  {
    /* calculate CRC for the CRC position */
    crcValue = Crc_CalculateCRC16(&DataPtr[offset + E2E_P05_CNT_OFS], \
      (uint32)lengthAftCrc, E2E_P05_CRC_START_VAL, 
      TRUE);
  } /* End of else */

  /* Get the value of low byte of DataPtr ID */
  dataIDLowByte = (uint8)(ConfigPtr->DataID & E2E_LOW_BYTE_MASK);

  /* Calculate CRC for low byte of DataPtr ID */
  crcValue = Crc_CalculateCRC16(&dataIDLowByte, (uint32)0x01U, \
    crcValue, FALSE);

  /* Get the value of high byte of DataPtr ID */
  dataIDHighByte = (uint8)(((ConfigPtr->DataID) >> 0x08U) & \
    E2E_LOW_BYTE_MASK);

  /* Calculate CRC for high byte of DataPtr ID */
  crcValue = Crc_CalculateCRC16(&dataIDHighByte, (uint32)0x01U, \
    crcValue, FALSE);

  /* return the result value of CRC calculation */
  return crcValue;
}

/*******************************************************************************
** Function Name        : E2E_P05CheckStatus                                  **
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
** Return value         : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */
static FUNC(void, E2E_CODE) E2E_P05CheckStatus(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    VAR(boolean, AUTOMATIC) NewDataAvailable,
    VAR(boolean, AUTOMATIC) IsCorrectCRC,
    VAR(uint8, AUTOMATIC) Counter)
{
  /* Local variable to store delta counter */
  VAR(uint8, AUTOMATIC) deltaCounter;

  /* @Trace: SafeE2E_SUD_MF_309 */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NewDataAvailable != TRUE)
  {
    
    StatePtr->Status = E2E_P05STATUS_NONEWDATA;
    
  }
  else if (IsCorrectCRC != TRUE)
  {
    StatePtr->Status = E2E_P05STATUS_ERROR;
  }
  else
  {
    /* Compute local variable Delta Counter */
    if (Counter >= StatePtr->Counter)
    {
      deltaCounter = Counter - StatePtr->Counter;
    }
    else
    {
      deltaCounter = E2E_P05_CNT_MAX - StatePtr->Counter + Counter + 0x01U;
    }

    /* When the delta counter value is greater than max delta counter value */
    if (ConfigPtr->MaxDeltaCounter < deltaCounter)
    {
      StatePtr->Status = E2E_P05STATUS_WRONGSEQUENCE;
    }
    /* When the delta counter value is zero */
    else if (0x00U == deltaCounter)
    {
      StatePtr->Status = E2E_P05STATUS_REPEATED;
    }
    /* When the delta counter value is one */
    else if (0x01U == deltaCounter)
    {
      StatePtr->Status = E2E_P05STATUS_OK;
    }
    /* 
    * When the delta counter value is greater than one and 
    * equal to or less than the max delta counter
    */
    else
    {
      StatePtr->Status = E2E_P05STATUS_OKSOMELOST;
    }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

    /* Update the counter value */
    StatePtr->Counter = Counter;
  }
}
#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
